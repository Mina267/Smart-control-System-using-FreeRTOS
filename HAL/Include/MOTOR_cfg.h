
#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_


#define  NUMBER_MOTORS   4

/******************PIN config ***********************************/


#define   M1_IN1	PIN_B0
#define   M1_IN2	PIN_B1
#define   M1_EN		PIN_B3
					   
#define   M2_IN1	PIN_C3
#define   M2_IN2	PIN_C4
#define   M2_EN		PIN_D7
					   
#define   M3_IN1	PIN_C4
#define   M3_IN2	PIN_C5
#define   M3_EN		PIN_B2
					   
#define   M4_IN1	PIN_C6
#define   M4_IN2	PIN_C7
#define   M4_EN		PIN_B3

#define M1_PWM_PIN	OCR0
#define M2_PWM_PIN	OCR2
#define M3_PWM_PIN	OCR1A
#define M4_PWM_PIN	OCR1B



#endif /* MOTOR_CFG_H_ */