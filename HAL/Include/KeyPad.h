
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_interface.h"
#include "StdTypes.h"

/***************************Config*******************************/
// ROWS
#define FIRST_OUTPUT PIN_B4
// Columns 
#define FIRST_INPUT  PIN_D2	

#define ROWS 4 
#define COLMS  4
/***************************Default Value*******************************/
#define NO_KEY 'T'
/***********************************************************************/
#ifdef _KEYSARRAY
static const u8 KeysArray[ROWS][COLMS] =   {	{'7', '8', '9', 'S'},
												{'4', '5', '6', 'y'},
												{'1', '2', '3', '-'},
												{'c', '0', '=', 'r'},
};
#endif // _KEYSARRAY

/****************************************************************/

/*
This function retrieves a key pressed on a 4x4 keypad and returns the corresponding key value.
*/

void KEYPAD_Init(void);

u8 KEYPAD_GetKey(void);


u8 KEYPAD_Press(u8 *row, u8 *col);
u8 KEYPAD_Getter(u8 r, u8 c);

#endif /* KEYPAD_H_ */