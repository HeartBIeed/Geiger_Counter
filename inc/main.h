#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uart.h"
#include "i2c.h"
#include "timer.h"
#include "pwm.h"

#include "lcd1602.h"
#include "ds1307.h"

#include "button.h"
#include "gcounter.h"

#endif /* MAIN_H_ */

