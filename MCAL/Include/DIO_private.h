/*
 * DIO_private.h
 *
 * Created: 5/16/2023 8:32:58 PM
 *  Author: mohamed
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_


#include "DIO_reg.h"
#include "DIO_config.h"

#define concByteHelper(x7,x6,x5,x4,x3,x2,x1,x0) 0b##x7##x6##x5##x4##x3##x2##x1##x0
#define concByte(x7,x6,x5,x4,x3,x2,x1,x0) concByteHelper(x0,x1,x2,x3,x4,x5,x6,x7)

#define DDRA_INITVAL concByte(DIO_u8Pin0_INITDIR, DIO_u8Pin1_INITDIR, DIO_u8Pin2_INITDIR, DIO_u8Pin3_INITDIR, DIO_u8Pin4_INITDIR, DIO_u8Pin5_INITDIR, DIO_u8Pin6_INITDIR, DIO_u8Pin7_INITDIR);
#define DDRB_INITVAL concByte(DIO_u8Pin8_INITDIR, DIO_u8Pin9_INITDIR, DIO_u8Pin10_INITDIR, DIO_u8Pin11_INITDIR, DIO_u8Pin12_INITDIR, DIO_u8Pin13_INITDIR, DIO_u8Pin14_INITDIR, DIO_u8Pin15_INITDIR);
#define DDRC_INITVAL concByte(DIO_u8Pin16_INITDIR, DIO_u8Pin17_INITDIR, DIO_u8Pin18_INITDIR, DIO_u8Pin19_INITDIR, DIO_u8Pin20_INITDIR, DIO_u8Pin21_INITDIR, DIO_u8Pin22_INITDIR, DIO_u8Pin23_INITDIR);
#define DDRD_INITVAL concByte(DIO_u8Pin24_INITDIR, DIO_u8Pin25_INITDIR, DIO_u8Pin26_INITDIR, DIO_u8Pin27_INITDIR, DIO_u8Pin28_INITDIR, DIO_u8Pin29_INITDIR, DIO_u8Pin30_INITDIR, DIO_u8Pin31_INITDIR);
#define PORTA_INITVAL concByte(DIO_u8Pin0_INITVAL, DIO_u8Pin1_INITVAL, DIO_u8Pin2_INITVAL, DIO_u8Pin3_INITVAL, DIO_u8Pin4_INITVAL, DIO_u8Pin5_INITVAL, DIO_u8Pin6_INITVAL, DIO_u8Pin7_INITVAL);
#define PORTB_INITVAL concByte(DIO_u8Pin8_INITVAL, DIO_u8Pin9_INITVAL, DIO_u8Pin10_INITVAL, DIO_u8Pin11_INITVAL, DIO_u8Pin12_INITVAL, DIO_u8Pin13_INITVAL, DIO_u8Pin14_INITVAL, DIO_u8Pin15_INITVAL);
#define PORTC_INITVAL concByte(DIO_u8Pin16_INITVAL, DIO_u8Pin17_INITVAL, DIO_u8Pin18_INITVAL, DIO_u8Pin19_INITVAL, DIO_u8Pin20_INITVAL, DIO_u8Pin21_INITVAL, DIO_u8Pin22_INITVAL, DIO_u8Pin23_INITVAL);
#define PORTD_INITVAL concByte(DIO_u8Pin24_INITVAL, DIO_u8Pin25_INITVAL, DIO_u8Pin26_INITVAL, DIO_u8Pin27_INITVAL, DIO_u8Pin28_INITVAL, DIO_u8Pin29_INITVAL, DIO_u8Pin30_INITVAL, DIO_u8Pin31_INITVAL);



#endif /* DIO_PRIVATE_H_ */