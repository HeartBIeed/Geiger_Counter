#ifndef DS1307_H_
#define DS1307_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd1602.h"

void set_time(uint32_t h,uint32_t m);
void time_to_lcd();

#endif /* DS1307_H_ */