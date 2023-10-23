#ifndef WATCHDOG_H_
#define WATCHDOG_H_

typedef enum {
	WDT_TIMEOUT_16MS = 0,
	WDT_TIMEOUT_32MS,
	WDT_TIMEOUT_65MS,
	WDT_TIMEOUT_130MS,
	WDT_TIMEOUT_260MS,
	WDT_TIMEOUT_520MS,
	WDT_TIMEOUT_1S,
	WDT_TIMEOUT_2S
} watchdog_timeout_t;

 
void watchdog_set(watchdog_timeout_t time);
void watchdog_stop(void);
 

 


#endif /* WATCHDOG_H_ */