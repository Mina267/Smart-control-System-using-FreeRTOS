

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000
#include <util/delay.h>
#include "StdTypes.h"
#include "DIO_interface.h"
#include "Utils.h"

#define _4_BIT 1
#define _8_BIT 2

/************************ Pin Config ************************/
#define LCD_MODE _4_BIT

#define RS DIO_enuPin1
#define EN DIO_enuPin2

/**********4Bit mode***********/
#define D7 DIO_enuPin6
#define D6 DIO_enuPin5
#define D5 DIO_enuPin4
#define D4 DIO_enuPin3
/*****************************/

#define LCD_PORT PA

#define ASCI_LCD_0 0x30


 
 /******************* initalize ***************************/
void LCD_Init(void);

void LCD_WriteString(u8*str);
void LCD_Clear(void);


// take address of ascii in CG Ram or take char 'A'  and print them
void LCD_WriteChar(u8 ch); 
// take the number and print its ascii
void LCD_WriteNumber(s32 num); 
void LCD_WriteBinary(u8 num);
void LCD_WriteHEX(u8 num);

void LCD_WriteBinaryToDecimal(u32 num);
void LCD_WriteBinaryToHex(u32 num);
void LCD_WriteNumber_4Digit(u16 num);
void LCD_WriteHEXToDecimal(u16 num);
void LCD_WriteHEXToBinary(u8 num);

void LCD_GoTo(u8 Line,u8 cell);
void LCD_GoTo_Clear(u8 Line,u8 cell,u8 NumOfCells);
void LCD_GoTo_WriteString(u8 Line,u8 cell,u8 *str);
void LCD_GoTo_WriteNumber(u8 Line,u8 cell,s32 num);
void LCD_GoTo_WriteChar(u8 Line,u8 cell,u8 ch);

/* Function to take array contain a pattern and save it in CGRAM address (ascii) */
void LCD_CreatePattern(u8 * pattern , u8 address);



#endif /* LCD_H_ */