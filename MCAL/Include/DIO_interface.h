#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_
#include "StdTypes.h"
/*Digital I/O pins*/
typedef enum DIO_enuPinNum{
	DIO_enuPin0=0, // PINA0
	DIO_enuPin1,   // PINA1
	DIO_enuPin2,  // PINA2
	DIO_enuPin3,  // PINA3
	DIO_enuPin4,  // PINA4
	DIO_enuPin5,  // PINA5
	DIO_enuPin6,  // PINA6
	DIO_enuPin7,  // PINA7
	DIO_enuPin8,  // PINB0
	DIO_enuPin9,  // PINB1
	DIO_enuPin10,  // PINB2
	DIO_enuPin11,  // PINB3
	DIO_enuPin12,  // PINB4
	DIO_enuPin13,  // PINB5
	DIO_enuPin14,  // PINB6
	DIO_enuPin15,  // PINB7
	DIO_enuPin16,  // PINC0
	DIO_enuPin17,  // PINC1
	DIO_enuPin18,  // PINC2
	DIO_enuPin19,  // PINC3
	DIO_enuPin20,  // PINC4
	DIO_enuPin21,  // PINC5
	DIO_enuPin22,  // PINC6
	DIO_enuPin23,  // PINC7
	DIO_enuPin24,  // PIND0
	DIO_enuPin25,  // PIND1
	DIO_enuPin26,  // PIND2
	DIO_enuPin27,  // PIND3
	DIO_enuPin28,  // PIND4
	DIO_enuPin29,  // PIND5
	DIO_enuPin30,  // PIND6
	DIO_enuPin31  // PIND7
} DIO_enuPinNum;

typedef enum {
	PIN_A0,
	PIN_A1,
	PIN_A2,
	PIN_A3,
	PIN_A4,
	PIN_A5,
	PIN_A6,
	PIN_A7,
	PIN_B0,
	PIN_B1,
	PIN_B2,
	PIN_B3,
	PIN_B4,
	PIN_B5,
	PIN_B6,
	PIN_B7,
	PIN_C0,
	PIN_C1,
	PIN_C2,
	PIN_C3,
	PIN_C4,
	PIN_C5,
	PIN_C6,
	PIN_C7,
	PIN_D0,
	PIN_D1,
	PIN_D2,
	PIN_D3,
	PIN_D4,
	PIN_D5,
	PIN_D6,
	PIN_D7,
	TOTAL_PINS
} DIO_Pin_type;


/*Digital I/O ports*/
typedef enum DIO_enuPortNum{
	DIO_enuPortA=0,
	DIO_enuPortB,
	DIO_enuPortC,
	DIO_enuPortD
}DIO_enuPortNum;

 
/*Digital I/O Values */
#define DIO_u8HIGHVAL   1
#define DIO_u8LOWVAL    0

/*Digital I/O Directions */
#define DIO_u8PIN_INPUTDIR   0
#define DIO_u8PIN_OUTPUTDIR  1
#define DIO_u8PORT_INPUTDIR  0x00
#define DIO_u8PORT_OUTPUTDIR 0xFF

/*Digital I/O Characteristics */
#define DIO_u8NumOfPorts         4
#define DIO_u8NumOfPins          32
#define DIO_u8NumOfPinsPerPort   8

/* Digital I/O states */
typedef enum DIO_enuDioState {
	DIO_enuNormal = 0,
	DIO_enuWrongPinVal,
	DIO_enuWrongPinNum,
	DIO_enuWrongPinDir,
	DIO_enuWrongPortNum,
	DIO_enuWrongPortDir,
}DIO_enuDioState;

/* Initialize Method*/
extern void DIO_voidInit(void);

/* IO Pins */
extern u8 DIO_WritePin (u8 Copy_u8PinNum, u8 Copy_u8PinVal);

extern u8 DIO_u8GetPinValue (u8 Copy_u8PinNum,u8* u8PtrtoVal);

extern u8 DIO_ReadPin (u8 Copy_u8PinNum);

extern u8 DIO_TogglePin (u8 Copy_u8PinNum);

extern u8 DIO_u8SetPinDir (u8 Copy_u8PinNum, u8 Copy_u8PinDir);

extern u8 DIO_u8GetPinDir (u8 Copy_u8PinNum, u8* u8PtrtoDir);

/* IO Ports */

extern u8 DIO_u8SetPortValue (u8 Copy_u8PortNum, u8 Copy_u8PortVal);

extern u8 DIO_u8GetPortValue (u8 Copy_u8PortNum,u8* u8PtrtoVal);

extern u8 DIO_u8SetPortDir (u8 Copy_u8PortNum, u8 Copy_u8PortDir);

extern u8 DIO_u8GetPortDir (u8 Copy_u8PortNum, u8* u8PtrtoDir);



#endif /* DIO_INTERFACE_H_ */