#ifndef SPI_H_
#define SPI_H_
#include "StdTypes.h"

// SPI modes
typedef enum {
	SPI_MODE_0 = 0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3
} spi_mode_t;

// SPI data order
typedef enum {
	SPI_MSB_FIRST = 0,
	SPI_LSB_FIRST
} spi_data_order_t;

// SPI clock frequency
typedef enum {
	SPI_FOSC_4 = 0,
	SPI_FOSC_16,
	SPI_FOSC_64,
	SPI_FOSC_128
} spi_clock_freq_t;

/************************** Function Prototypes ********************************/
void SPI_Init(void);
/***********************************************************/
void SPI_SendByte(u8 data);
u8 SPI_ReceiveByte(void);

u8 SPI_SendReceive(u8 data);
/***********************************************************/
void SPI_SendNoBlock(u8 data);
u8 SPI_ReceiveNoBlock(void);
/***********************************************************/
u8 SPI_ReceivePeriodic(u8* pdata);
/***********************************************************/
void SPI_SendString(u8 *str);
void SPI_ReceiveString(u8 *str);
/***********************************************************/
void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);

void SPI_SetCallBack( void(*localFptr)(void) );
#endif /* SPI_H_ */