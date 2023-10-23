#include "SPI.h"
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI_cfg.h"

// Pointer to SPI Interrupt Service Routine function
static void(*SPI_PTR)(void)=NULL_PTR;

void SPI_Init(void)
{
	// Check the SPI_MODE variable and set the Master/Slave mode accordingly
	/* Using if condition instead of #if because we want to change the state in run-time */
	if (SPI_MODE==MASTER)
	{
		// Enable Master
		SET_BIT(SPCR,MSTR);	
	}
	else
	{
		// Enable Slave
		CLR_BIT(SPCR,MSTR);
	}
	
	// Enable SPI communication
	SET_BIT(SPCR,SPE);
	/****************** DIO **********************/
	 DDRB = DDRB | 0b00001111;

}

void SPI_SendByte(u8 data)
{
	// Send data to the SPI data register
	SPDR=data;
	// Wait until SPI data transfer is completed (interrupt flag is set)
	while(!READ_BIT(SPSR,SPIF));
}

u8 SPI_ReceiveByte(void)
{
	// Wait until SPI data transfer is completed (interrupt flag is set)
	while(!READ_BIT(SPSR,SPIF));
	
	return SPDR;
}

// This Function Send Data and Wait for the  received data through SPI
u8 SPI_SendReceive(u8 data)
{
	// Send data to the SPI data register
	SPDR=data;
	
	// Busy Wait  
	// Wait until SPI data transfer is completed (interrupt flag is set)
	while(!READ_BIT(SPSR,SPIF));
	// Return the received data
	return SPDR;
}
// Send data through SPI without waiting for the transfer to complete
void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}
// Function that  receive through SPI with No Block
u8 SPI_ReceiveNoBlock(void)
{
	return SPDR;
}

// Function that Check if there is any data received through SPI for the slave
u8 SPI_ReceivePeriodic(u8* pdata)
{
	// Check if the interrupt flag is set, indicating data has been received
	if(READ_BIT(SPSR,SPIF))
	{
		// Read the data from the SPI data register
		*pdata=SPDR;
		
		// Return 1 to indicate data has been received
		return 1;
	}
	
	// Return 0 to indicate no data has been received
	return 0;
}

void SPI_SendString(u8 *str)
{
	// loop the string until you find NULL
	while(*str)
	{
		// Send data to the SPI data register
		SPI_SendByte(*str);
		// Wait until SPI data transfer is completed (interrupt flag is set)
		while( !(READ_BIT(SPSR,SPIF)) );
		_delay_us(20);
		// Move to the next index in the string
		str++;
	}
	SPI_SendByte(*str);
}

void SPI_ReceiveString(u8 *str)
{
	u8 i=0;
	str[i]=SPI_ReceiveByte();
	while(str[i]!= '\0')
	{
		i++;
		str[i]=SPI_ReceiveByte();
	}
	str[i]='\0';
}
/**************************************Interrupt*******************************************/
void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}

void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}

void SPI_SetCallBack( void(*localFptr)(void) )
{
	SPI_PTR=localFptr;
}


ISR(SPI_vect)
{
	if(SPI_PTR!=NULL_PTR)
	{
		SPI_PTR();
	}
}
