#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_


/*       Digital I/O Directions 

        DIO_u8PIN_INPUTDIR   0
        DIO_u8PIN_OUTPUTDIR  1
		
*/
/* Pin Initial Direction  */
/**********************PORTA***************************************/
#define DIO_u8Pin0_INITDIR		DIO_u8PIN_INPUTDIR // Port A Pin 0  ADC0
#define DIO_u8Pin1_INITDIR		DIO_u8PIN_OUTPUTDIR // Port A Pin 1  ADC1
#define DIO_u8Pin2_INITDIR		DIO_u8PIN_OUTPUTDIR // Port A Pin 2
#define DIO_u8Pin3_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port A Pin 3
#define DIO_u8Pin4_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port A Pin 4
#define DIO_u8Pin5_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port A Pin 5
#define DIO_u8Pin6_INITDIR		DIO_u8PIN_OUTPUTDIR // Port A Pin 6
#define DIO_u8Pin7_INITDIR	    DIO_u8PIN_INPUTDIR // Port A Pin 7  ADC7
/**********************PORTB***************************************/
#define DIO_u8Pin8_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 0
#define DIO_u8Pin9_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 1
#define DIO_u8Pin10_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 2  INT2
#define DIO_u8Pin11_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 3  OC0
#define DIO_u8Pin12_INITDIR		DIO_u8PIN_OUTPUTDIR // Port B Pin 4  ss
#define DIO_u8Pin13_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 5  mosi
#define DIO_u8Pin14_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 6  miso
#define DIO_u8Pin15_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port B Pin 7  clk
/**********************PORTC**************************************/
#define DIO_u8Pin16_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port C Pin 0
#define DIO_u8Pin17_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port C Pin 1
#define DIO_u8Pin18_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port C Pin 2
#define DIO_u8Pin19_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port C Pin 3
#define DIO_u8Pin20_INITDIR	    DIO_u8PIN_OUTPUTDIR // Port C Pin 4
#define DIO_u8Pin21_INITDIR		DIO_u8PIN_OUTPUTDIR // Port C Pin 5
#define DIO_u8Pin22_INITDIR		DIO_u8PIN_OUTPUTDIR // Port C Pin 6
#define DIO_u8Pin23_INITDIR		DIO_u8PIN_OUTPUTDIR // Port C Pin 7
/**********************PORTD***************************************/
#define DIO_u8Pin24_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 0 RX
#define DIO_u8Pin25_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 1 TX
#define DIO_u8Pin26_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 2  INT0
#define DIO_u8Pin27_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 3  INT1
#define DIO_u8Pin28_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 4  OC1B
#define DIO_u8Pin29_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 5  OC1A
#define DIO_u8Pin30_INITDIR		DIO_u8PIN_INPUTDIR // Port D Pin 6  ICP
#define DIO_u8Pin31_INITDIR		DIO_u8PIN_OUTPUTDIR // Port D Pin 7





/* Pin Initial Value  */

/*        Directions 

        DIO_u8LOWVAL   0
        DIO_u8HIGHVAL  1
		
*/
/**********************PORTA***************************************/
#define DIO_u8Pin0_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin1_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin2_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin3_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin4_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin5_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin6_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin7_INITVAL	    DIO_u8LOWVAL
/**********************PORTB***************************************/
#define DIO_u8Pin8_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin9_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin10_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin11_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin12_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin13_INITVAL	    DIO_u8HIGHVAL
#define DIO_u8Pin14_INITVAL	    DIO_u8HIGHVAL
#define DIO_u8Pin15_INITVAL	    DIO_u8HIGHVAL
/**********************PORTC****************************************/
#define DIO_u8Pin16_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin17_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin18_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin19_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin20_INITVAL	    DIO_u8LOWVAL
#define DIO_u8Pin21_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin22_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin23_INITVAL		DIO_u8LOWVAL
/**********************PORTD***************************************/
#define DIO_u8Pin24_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin25_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin26_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin27_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin28_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin29_INITVAL		DIO_u8HIGHVAL
#define DIO_u8Pin30_INITVAL		DIO_u8LOWVAL
#define DIO_u8Pin31_INITVAL		DIO_u8HIGHVAL




#endif /* DIO_CONFIG_H_ */