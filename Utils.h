#ifndef UTILS_H_
#define UTILS_H_

#define F_CPU 8000000
#include <util/delay.h>


#define SET_BIT(REG,BIT)            (REG = ( REG | (1<<BIT) ))
#define CLR_BIT(REG,BIT)            (REG = ( REG & (~(1<<BIT))))
#define READ_BIT(REG,BIT)          ((REG>>BIT)&1)
#define TOG_BIT(REG,BIT)           ( REG ^= (1<<(BIT))  )
#define WRITE_BIT(REG, BIT, VALUE)		REG = (((REG) & (~(1 << (BIT)))) | ((VALUE) << (BIT)))

#define RESET_BIT(byte,bit_no) (byte &= ~(1<< bit_no))
#define GET_BIT(byte,bit_no) ((byte>>bit_no)& 1)
#define TOGGLE_BIT(byte,bit_no) (byte ^= (1<<bit_no))
#define ASSIGN_BIT(byte,bit_no,value)	byte = (byte & (~(1<<bit_no)))|(value<<bit_no)

 #define porta 0
 #define portb 1
 #define portc 2
 #define portd 3



#endif /* UTILS_H_ */