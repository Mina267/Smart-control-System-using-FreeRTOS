/*  MCAL */
#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "UART_Interface.h"
#include "Timers.h"
#include "EEPROM_intrface.h"

/* HAL */

#include "LCD_interface.h"
#include "Keypad_interface.h"
#include "Servo_Interface.h"

/*  RTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "stack_macros.h"
#include "timers.h"


# define F_CPU 8000000
#include <util/delay.h>


// String Compare enum.
typedef enum
{
	STR_NOMATCH,
	STR_MATCH,
}STR_Status;

typedef enum
{
	TASK_NOT_FOUND,
	TASK_FOUND,
}TASKS_Status_t;

#define  PASSWORD_STR_SIZE	7
#define START_PASS_ADDRESS  0x3f8
#define FIRST_PASS_INDEX	0
#define _0_POSITION			1
#define _180_POSITION		2

static bool_t New_Pass_flag = FALSE;
static bool_t DoorOpen_flag = FALSE;
static bool_t Long_press_flag = FALSE;

static u8 Pass_Array[PASSWORD_STR_SIZE];
static u8 DoorPass[PASSWORD_STR_SIZE] = "123456";
static u8 Position = 0;

static bool_t Fan_Open_flag = FALSE;

#define TX_BUFFER_END_PATTERN	0x0d
#define TX_FRAME_SIZE			20
#define RX_FRAME_SIZE			20
#define FIRST_FRAME_INDEX		0
#define MAX_SAMPLE				5

static xSemaphoreHandle LCD_sem;
static xSemaphoreHandle ADC_SynSem;
static xSemaphoreHandle ADC_Sem;
static xSemaphoreHandle TX_Sem;
static xSemaphoreHandle Key_sem;
static xTaskHandle  KeyTaskHandle = NULL;
static xQueueHandle RX_Queue;
static xQueueHandle TX_Queue;
static xQueueHandle KeyPad_Queue;


static u8 row;
static u8 col;
static u16 temp;
static u16 LDR_Read;
static volatile u16 flag;
static u8 Tx_buffer[TX_FRAME_SIZE];
static volatile bool_t Send_flag = FALSE;

static void Str_toUpper(u8 *str);
static STR_Status Str_cmp_Caseless(u8 *strReceive, u8 *StrExpected);




static void CloseDoor(void)
{
	Position = _0_POSITION;
	DoorOpen_flag = FALSE;
	xQueueSend(TX_Queue, "Door closed", 0);
}

static void OpenDoor(void)
{
	Position = _180_POSITION;
	DoorOpen_flag = TRUE;
	xQueueSend(TX_Queue, "Door Opened", 0);
}

static void CloseFan(void)
{
	Fan_Open_flag = FALSE;
	xQueueSend(TX_Queue, "Fan closed", 0);
}


static void OpenFan(void)
{

	Fan_Open_flag = TRUE;
	xQueueSend(TX_Queue, "Fan Opened", 0);
}



#define TASK_NUM	5
typedef struct
{
	c8 *str;
	void (*Fptr) (void);
}SmartHome_task_t;


static const SmartHome_task_t TasksArray[TASK_NUM] = {
	{"OPENDOOR", OpenDoor},
	{"CLOSEDOOR", CloseDoor},
	{"OPENFAN", OpenFan},
	{"CLOSEFAN", CloseFan},
	
};

static TASKS_Status_t SearchForTaskOrder(u8 *TaskIndex, u8 * StrCommand)
{
	TASKS_Status_t taskStatus = TASK_NOT_FOUND;
	u8 Index;
	for (Index = 0; Index < TASK_NUM; Index++)
	{
		if (Str_cmp_Caseless(StrCommand, (u8*)TasksArray[Index].str) == STR_MATCH)
		{
			*TaskIndex = Index;
			taskStatus = TASK_FOUND;
		}
	}
	return taskStatus;
}




void UART_Send_Task(void *Pvparama)
{
	u8 Qstate;
	while(1)
	{
		if (Send_flag == FALSE)
		{
			Qstate = xQueueReceive(TX_Queue, &Tx_buffer[FIRST_FRAME_INDEX], 0);
			if (Qstate == pdPASS)
			{
				Send_flag = TRUE;
				UART_SendNoBlock(Tx_buffer[FIRST_FRAME_INDEX]);
			}
		}		
		vTaskDelay(1000);
	}
}


void TX_CallBack(void)
{
	static u8 i = 1;	
	if (Send_flag)
	{
		if ((Tx_buffer[i] == 0) || (i == TX_FRAME_SIZE - 1))
		{
			i = 1;
			Send_flag = FALSE;
			UART_SendNoBlock(TX_BUFFER_END_PATTERN);
		}
		else
		{
			UART_SendNoBlock(Tx_buffer[i]);
			i++;
		}
	}
	
}



void UART_Receive_Task(void *Pvparama)
{
	u8 state;
	u8 buffer[20];
	u8 TaskIndex;
	while(1)
	{	
		state = xQueueReceive(RX_Queue, &buffer, 0);
		if (state == pdPASS)
		{
			TASKS_Status_t status = SearchForTaskOrder(&TaskIndex, buffer);
			if (status == TASK_FOUND)
			{
				TasksArray[TaskIndex].Fptr();
			}
			else
			{
				xQueueSend(TX_Queue, "Task Not Found!", 0);
			}
		}
		vTaskDelay(1000);
	}
}



void RX_CallBack(void)
{
	static u8 i = 0;
	static u8 buffer[RX_FRAME_SIZE];
	u8 data = UART_ReciveNoBlock();
	
	if (data != 0x0d)
	{
		buffer[i] = data;
		i++;
	}
	else
	{

		buffer[i] = 0;
		xQueueSendFromISR(RX_Queue, &buffer[0], 0);
		i = 0;
	}
}


/************************************************** ADC *****************************************************************/

void Read_TemperatureTask(void *Pvparama)
{
	u8 state;
	u8 state2;
	while(1)
	{
		state2 = xSemaphoreTake(ADC_Sem, 2);
		
		if (state2 == pdPASS)
		{
			ADC_StartConversion(CH_0);
			state = xSemaphoreTake(ADC_SynSem, 2);
			if ((state == pdPASS))
			{
				temp = (u16)(((u32)ADC_ReadNoBlock() * (u32)1500) / (u32)308);
			}
			else
			{
				/* Do nothing */
			}
			
			xSemaphoreGive(ADC_Sem);
		}
		vTaskDelay(1000);
	}
}



void Read_LDR_Task(void *Pvparama)
{
	u8 state;
	u8 state2;
	while(1)
	{
		
		state2 = xSemaphoreTake(ADC_Sem, 2);
		
		if (state2 == pdPASS)
		{
			ADC_StartConversion(CH_7);
			state = xSemaphoreTake(ADC_SynSem, 2);
			if ((state == pdPASS))
			{
				u16 adc = ADC_ReadNoBlock();
				LDR_Read = (u16)(((u32)adc * (u32)5000) / (u32)1024);
			}
			else
			{
				/* Do nothing */
			}
			xSemaphoreGive(ADC_Sem);
		}
		vTaskDelay(1000);
	}
}


void ADC_callBack_func(void)
{
	xSemaphoreGiveFromISR(ADC_SynSem, NULL);
}



static bool_t LDR_Control_Flag = TRUE;

void Leds_task(void *Pvparama)
{
	
	while (1)
	{
		if (LDR_Control_Flag)
		{
			if (LDR_Read < 1000)
			{
				DIO_WritePin(PIN_C0, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C1, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C2, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C3, DIO_u8HIGHVAL);
			}
			else if (LDR_Read < 1800)
			{
				DIO_WritePin(PIN_C0, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C1, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C2, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C3, DIO_u8LOWVAL);
			}
			else if (LDR_Read < 2500)
			{
				DIO_WritePin(PIN_C0, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C1, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C2, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C3, DIO_u8LOWVAL);
			}
			else if (LDR_Read < 3000)
			{
				DIO_WritePin(PIN_C0, DIO_u8HIGHVAL);
				DIO_WritePin(PIN_C1, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C2, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C3, DIO_u8LOWVAL);
			}
			else
			{
				DIO_WritePin(PIN_C0, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C1, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C2, DIO_u8LOWVAL);
				DIO_WritePin(PIN_C3, DIO_u8LOWVAL);
			}
		}
		
		
		vTaskDelay(300);
	}
}


void FAN_Task(void *Pvparama)
{
	u8 Qstate;
	while(1)
	{
		if (Fan_Open_flag)
		{
			if (temp > 250 && temp <= 270)
			{
				OCR2 = ((u16)40 * 256 / 100);
			}
			else if (temp > 270 && temp <= 280)
			{
				OCR2 = ((u16)60 * 256 / 100);
			}
			else if (temp > 280 && temp <= 300)
			{
				OCR2 = ((u16)90 * 256 / 100);
			}
			else if (temp > 300)
			{
				OCR2 = 255;
			}
			else
			{
				OCR2 = (30 * 256 / 100);
			}
		}
		vTaskDelay(1000);
	}
}


/********************************************** keypad ****************************************************/



/*************************** Edit And Read password Functions *********************/
static void Save_Password(void)
{
	u16 PassAddress = START_PASS_ADDRESS;
	for (u8 Index = FIRST_PASS_INDEX; Index < PASSWORD_STR_SIZE - 1; Index++)
	{
		EEPROM_writeBusy(PassAddress, DoorPass[Index]);
		PassAddress++;
	}
}

static void Read_Password(void)
{
	u16 PassAddress = START_PASS_ADDRESS;
	for (u8 Index = FIRST_PASS_INDEX; Index < PASSWORD_STR_SIZE - 1; Index++)
	{
		DoorPass[Index] = EEPROM_readBusy(PassAddress);
		PassAddress++;
	}
}



static void Clear_pass(void)
{
	for (u8 Index = FIRST_PASS_INDEX; Index < PASSWORD_STR_SIZE - 1; Index++)
	{
		DoorPass[Index] = '0';
		Pass_Array[Index] = '0';
		Save_Password();
	}
}


static u8 Str_cmp(u8 *str)
{
	for (u8 Index = 0; DoorPass[Index] || str[Index]; Index++)
	{
		if (DoorPass[Index] != str[Index])
		{
			return 0;
		}
	}
	return 1;
}

static void str_Copy (u8 *str_ToCopy, u8 *str_Paste)
{
	u8 i;
	for (i = 0; str_ToCopy[i]; i++)
	{
		str_Paste[i] = str_ToCopy[i];
	}
	str_Paste[i] = 0;
}

static void PassWord_Analysis(void)
{
	LCD_ClearCell(1, 0, 16);
	if (New_Pass_flag)
	{
		str_Copy(Pass_Array, DoorPass);
		LCD_SetCursor(1,0);
		LCD_WriteString("Pass changed");
		New_Pass_flag = FALSE;
		Save_Password();
	}
	else
	{
		u8 r = Str_cmp(Pass_Array);
		if (r == 1)
		{
			if (DoorOpen_flag)
			{
				LCD_SetCursor(1,0);
				LCD_WriteString("Door Already Open");
				xQueueSend(TX_Queue, "Open Already", 0);
				DoorOpen_flag = TRUE;
			}
			else
			{
				LCD_SetCursor(1,0);
				LCD_WriteString("OpenDoor");
				xQueueSend(TX_Queue, "OpenDoor", 0);
				DoorOpen_flag = TRUE;
				Position = _180_POSITION;
			}
			
		}
		else
		{
			LCD_SetCursor(1,0);
			LCD_WriteString("Wrong!");
			xQueueSend(TX_Queue, "Wrong!", 0);
		}
	}
}

void LCD_Print_Task(void *Pvparama)
{
	u8 state;
	u8 key;
	u8 i = 0;
	u8 cell = 10;
	static u8 flag = 0;
	
	while(1)
	{
		state = xSemaphoreTake(LCD_sem, 0);
		if (state == pdPASS)
		{
			
			// Print in LCD Password
			if (New_Pass_flag)
			{
				if (flag == 1)
				{
					LCD_SetCursor(0, 0);
					LCD_WriteString("New: ");
					flag = 0;
				}
				
			}
			else
			{
				if (flag == 0)
				{
					LCD_SetCursor(0, 0);
					LCD_WriteString("Pass: ");
					flag = 1;
				}
				
			}
			

			
			// See if there is any char in Keypad Q.
			state = xQueueReceive(KeyPad_Queue, &key, 1);
			if (state == pdPASS)
			{
				// insert in array keys.
				if ((key >= '0' && key <= '9') && (i < PASSWORD_STR_SIZE - 1))
				{
					Pass_Array[i] = key;
					LCD_SetCursor(0, cell);
					LCD_WriteChar('*');
					cell++;
					i++;
				}
				// If key is '=' then check user input password.
				else if (key == '=')
				{
					LCD_ClearCell(0, 10, 10);
					Pass_Array[i] = 0;
					// Analysis user password Enter.
					PassWord_Analysis();
					cell = 10;
					i = 0;
				}
				// If user Enter 'c', user want to change password.
				else if (key == 'c')
				{
					New_Pass_flag = TRUE;
				}
				else if (key == 'r')
				{
					if (Long_press_flag)
					{
						
						Clear_pass();
						Long_press_flag = FALSE;
					}
				}
				
			}
			xSemaphoreGive(LCD_sem);
		}
		else
		{
			/* Do nothing */
		}
		vTaskDelay(300);
	}
}


void read_button_Task(void *Pvparama)
{
	static u16 SampleCnt = 0;
	static u8 Samples = 0;
	portTickType xLastWakeTime;
	u8 key;
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		// Put on detect button output LOW.
		DIO_WritePin(FIRST_OUTPUT + row, DIO_u8LOWVAL);
		
		// Check if on that column is ground until reach samples count.
		if ((DIO_ReadPin(FIRST_INPUT + col) == DIO_u8LOWVAL) && (SampleCnt != MAX_SAMPLE))
		{
			Samples++;
		}
		// If sample taken (True or false) is larger than sample needed  
		if (SampleCnt >= MAX_SAMPLE)
		{
			// Wait until user Release its hand from button
			// or if time increase specific time.
			// Then take user input.
			if ((DIO_ReadPin(FIRST_INPUT + col) == DIO_u8HIGHVAL) || (SampleCnt >= 1000))
			{
				// See if major of sample is LOW (Ground)(Pressed).
				if (Samples > MAX_SAMPLE / 2)
				{
					xSemaphoreGive(Key_sem);
					key = KEYPAD_Getter(row, col);
					xQueueSend(KeyPad_Queue, &key, 1);
				}
				if (SampleCnt >= 1000)
				{
					Long_press_flag = TRUE;
				}
				// Return Row to Zero
				DIO_WritePin(FIRST_OUTPUT + row, DIO_u8HIGHVAL);
				Samples = 0;
				SampleCnt = 0;
				// Suspend task again until anther press.
				vTaskSuspend(KeyTaskHandle);
			}
		}
		SampleCnt++;

		vTaskDelayUntil(&xLastWakeTime, 2);

	}
}

void KeyPad_Task(void *Pvparama)
{
	u8 state;	
	while (1)
	{
		// Function detect if there is any button pressed in keypad and return its location.
		state = KEYPAD_Press(&row, &col);
		if (state == 1)
		{
			// If there is button pressed resume read button task to handle denouncing and long press.
			vTaskResume(KeyTaskHandle);

		}
		// Task delay to check for keypad
		vTaskDelay(80);
	}
}


void Servo_Task(void *Pvparama)
{
	static u8 Servo_cnt = 0;
	portTickType xLastWakeTime;

	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		Servo_cnt++;
		if (Servo_cnt == 20)
		{
			DIO_WritePin(PIN_B2, DIO_u8HIGHVAL);
			Servo_cnt = 0;
		}
		if (Servo_cnt == Position)
		{
			DIO_WritePin(PIN_B2, DIO_u8LOWVAL);
		}
		vTaskDelayUntil(&xLastWakeTime, 1);

	}
}





int main(void)
{
	/*********** Initialization ***************/
	DIO_voidInit();
	LCD_Init();
	UART_Init( _9600_BAUDRATE);
	ADC_Init(VREF_AVCC, ADC_SCALER_64);
	ADC_SetCallBack(ADC_callBack_func);
	ADC_InterruptEnable();
	UART_RX_SetCallBack(RX_CallBack);
	UART_TX_SetCallBack(TX_CallBack);
	UART_TX_InterruptEnable();
	UART_RX_InterruptEnable();
	EEPROM_Init();
	KEYPAD_Init();
	Read_Password();
	
	TIMER2_Init(TIMER2_FASTPWM_MODE, TIMER2_SCALER_128);
	TIMER2_OC2Mode(OC2_NON_INVERTING);
		DIO_WritePin(PIN_B0, DIO_u8HIGHVAL);
		DIO_WritePin(PIN_B1, DIO_u8LOWVAL);
	
	
	LDR_Read = 5000;
	Position = _0_POSITION;
	RX_Queue = xQueueCreate(2, sizeof(u8) * RX_FRAME_SIZE);
	TX_Queue = xQueueCreate(2, sizeof(u8) * TX_FRAME_SIZE);
	KeyPad_Queue = xQueueCreate(4, sizeof(u8));
	

	// For Functions Synchronizations.
	TX_Sem = xSemaphoreCreateCounting(1, 0);
	if (TX_Sem != NULL)
	{
		
	}
	// For Functions Synchronizations.
	ADC_SynSem = xSemaphoreCreateCounting(1, 0);
	if (ADC_SynSem != NULL)
	{
		
	}
	// For shared resource ADC.
	ADC_Sem = xSemaphoreCreateCounting(1, 1);
	if (ADC_Sem != NULL)
	{
		
	}
	// For shared resource "LCD".
	LCD_sem = xSemaphoreCreateCounting(1, 1);
	if (LCD_sem != NULL)
	{
		
	}
	
	xTaskCreate(read_button_Task, NULL, 70, NULL, 9, &KeyTaskHandle);
	xTaskCreate(Servo_Task, NULL, 50, NULL, 9, NULL);
	xTaskCreate(KeyPad_Task, NULL, 70, NULL, 8, NULL);
	xTaskCreate(FAN_Task, NULL, 50, NULL, 5, NULL);
	xTaskCreate(UART_Send_Task, NULL, 50, NULL, 5, NULL);
	vTaskSuspend(KeyTaskHandle);
	xTaskCreate(Leds_task, NULL, 70, NULL, 2, NULL);
	xTaskCreate(UART_Receive_Task, NULL, 70, NULL, 3, NULL);
	xTaskCreate(Read_TemperatureTask, NULL, 70, NULL, 4, NULL);
	xTaskCreate(Read_LDR_Task, NULL, 70, NULL, 2, NULL);
	xTaskCreate(LCD_Print_Task, NULL, 70, NULL, 1, NULL);
	
	//xTimerCreate(NULL,1000,pdPASS,NULL,Read_LDR_Task);

	
	vTaskStartScheduler();
	
	
	
	while (1)
	{
		
	}
}


/*
while (1)
{
	SampleCnt++;
	
	DIO_WritePin(FIRST_OUTPUT + row, DIO_u8LOWVAL);
	if (DIO_ReadPin(FIRST_INPUT + col) == DIO_u8LOWVAL)
	{
		Samples++;
	}
	else
	{
		if ((Samples >= SampleCnt / 2) && (Samples > MIN_SAMPLE / 2))
		{
			//xSemaphoreGive(Key_sem);
			u8 key = KEYPAD_Getter(row, col);
			LCD_WriteChar(key);
		}
		DIO_WritePin(FIRST_OUTPUT + row, DIO_u8HIGHVAL);
		Samples = 0;
		SampleCnt = 0;
		vTaskSuspend(KeyTaskHandle);
	}
	vTaskDelayUntil(&xLastWakeTime, 3);
}
*/





/* Received  , Expected return STR_NOMATCH or STR_MATCH */
static STR_Status Str_cmp_Caseless(u8 *strReceive, u8 *StrExpected)
{
	Str_toUpper(strReceive);
	for (u8 Index = 0; strReceive[Index] || StrExpected[Index]; Index++)
	{
		if (strReceive[Index] != StrExpected[Index])
		{
			return STR_NOMATCH;
		}
	}
	return STR_MATCH;
}

static void Str_toUpper(u8 *str)
{
	for (u8 Index = 0; str[Index]; Index++)
	{
		if (str[Index] >= 'a' && str[Index] <= 'z')
		{
			str[Index] = str[Index] - 'a' + 'A';
		}
	}
}
