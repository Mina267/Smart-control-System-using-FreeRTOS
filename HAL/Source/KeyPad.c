#define _KEYSARRAY	0
#include "StdTypes.h"
#include "KeyPad.h"

#include "FreeRTOS.h"
#include "task.h"

void KEYPAD_Init(void)
{
	// Put (1) on each row to activate them
	DIO_WritePin(FIRST_OUTPUT, DIO_u8HIGHVAL);
	DIO_WritePin(FIRST_OUTPUT + 1, DIO_u8HIGHVAL);
	DIO_WritePin(FIRST_OUTPUT + 2, DIO_u8HIGHVAL);
	DIO_WritePin(FIRST_OUTPUT + 3, DIO_u8HIGHVAL);
}

# define F_CPU 8000000
#include <util/delay.h>



// This function is used to get the pressed key from the keypad
u8 KEYPAD_GetKey(void)
{	
	u8 key = NO_KEY;
	// Loop through the rows
	for (u8 r = 0; r < ROWS; r++)
	{
		// Loop through the columns
		DIO_WritePin(FIRST_OUTPUT + r, DIO_u8LOWVAL);
		for (u8 c = 0; c < COLMS; c++)
		{
			// If a button is pressed in this position
			if (DIO_ReadPin(FIRST_INPUT + c) == DIO_u8LOWVAL)
			{
				// If a button is pressed in this position
				key = KeysArray[r][c];
				break;
				// Wait until the button is released before continuing
				//while(DIO_ReadPin(FIRST_INPUT + c) == DIO_u8LOWVAL);
			}
		}
		// Deactivate the current row
		DIO_WritePin(FIRST_OUTPUT + r, DIO_u8HIGHVAL);
	}
	// Return the pressed key value
	return key;
}

/*
1- First, the function sets all rows to high.
2- It then iterates through the rows and sets each one to low, one at a time.
3- For each row, it checks the state of each column to determine if a button has been pressed.
4- If a button is pressed, the corresponding key value is retrieved from the "KeysArray" 2D array
and stored in the "key" variable.
5- The function then waits until the button is released.
6- This process is repeated for each row and column.
7- Finally, the "key" value is returned.
*/



u8 KEYPAD_Press(u8 *row, u8 *col)
{
	u8 state = 0;
	// Loop through the rows
	
	for (u8 r = 0; r < ROWS; r++)
	{
		// Loop through the columns
		DIO_WritePin(FIRST_OUTPUT + r, DIO_u8LOWVAL);
		for (u8 c = 0; c < COLMS; c++)
		{
			// If a button is pressed in this position
			if (DIO_ReadPin(FIRST_INPUT + c) == DIO_u8LOWVAL)
			{
				// If a button is pressed in this position
				*row = r;
				*col = c;
				state = 1;
			}
		}
		// Deactivate the current row
		DIO_WritePin(FIRST_OUTPUT + r, DIO_u8HIGHVAL);
	}
	return state;
}


u8 KEYPAD_Getter(u8 r, u8 c)
{
	return KeysArray[r][c];
}