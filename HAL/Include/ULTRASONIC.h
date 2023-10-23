

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "DIO_interface.h"


#define  US1   PIN_C0
#define  US2   PIN_C1
#define  US3   PIN_C2
#define  US4   PIN_C3

typedef   DIO_enuPinNum ULTRASONIC_type;

typedef enum{
	ULTRASONIC_1=PIN_D2,
	ULTRASONIC_2=PIN_D6,
	ULTRASONIC_3=PIN_D3,
	ULTRASONIC_4=PIN_D5,
	}ULTRASONIC_type2;


typedef enum
{
	ULTRA_NEW_DISTANCE,
	ULTRA_OLD_DISTANCE,
	}ULTRASONIC_Distance_t;

// OCRA Adjust with TOP of OCRA for Servo Motor.
#define TOP_OCRA	19999

void ULTRASONIC_Init(void);


u8 ULTRASONIC_GetDistance(ULTRASONIC_type us,u16*pdistance);
/*u16 ULTRASONIC_GetDistance2(ULTRASONIC_type2 us);*/


void ULTRASONICInt_Init(void);
void ULTRASONIC_StartRead(ULTRASONIC_type us);
u16 ULTRASONIC_DistanceGetter(void);
ULTRASONIC_Distance_t ULTRASONIC_DistanceGetterCheck(u16 *Pdistance);

#endif /* ULTRASONIC_H_ */