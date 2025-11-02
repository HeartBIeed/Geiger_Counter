#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"

extern volatile uint32_t ms_cnt;

void timer_ini(void); // timer0 1 мс
uint32_t get_mills(); // счетчик мс

#endif /* TIMER_H_ */