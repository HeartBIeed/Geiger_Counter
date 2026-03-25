#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcd1602.h"
#include "ds1307.h"
#include "pwm.h"
#include "uart.h"
#include "timer.h"
#include "button.h"

int num_ones(unsigned char array[]);   
extern uint8_t gamma_array[5];

#endif /* MAIN_H_ */

