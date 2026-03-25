#ifndef DS1307_H_
#define DS1307_H_

#define TIMEOUT 100000

#include "main.h"

void i2c_init(void);
void set_time(int h,int m);
int time_to_lcd();

extern uint8_t hour,min,sec;


#endif /* DS1307_H_ */