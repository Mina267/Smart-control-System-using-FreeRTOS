#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART.h"

//static void (*ptr_Empty)(void)=NULL_PTR;
static void(*UART_RX_Fptr)(void)=NULL_PTR;
static void(*UART_TX_Fptr)(void)=NULL_PTR;

void UART_Init(void)
{
	// baud rate
	UBRRL=51;
	
	// Normal Speed
	CLR_BIT(UCSRA,U2X);
	
	// frame data bit , parity , stop 
	
	// 8 data , no parity , 1 stop ---> defualt 
	
	// enable
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	
}



void UART_Send(u8 data)
{
	//check the flag -- busy wait
	while(!READ_BIT(UCSRA,UDRE));
	
	UART_BUFFER=data;
	
}

u8 UART_Receive(void)
{
	while(!READ_BIT(UCSRA,RXC));

	return UART_BUFFER;
}

u8 UART_ReceivePerodic(u8* pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UART_BUFFER;
		return 1;		
	}
		return 0;
}


void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceiveNoBlock(void)
{
	return UDR;
}

void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULL_PTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULL_PTR)
	{
		UART_TX_Fptr();
	}
}

