#ifndef DS1307_H_
#define DS1307_H_

#include "main.h"

void DS1307_setTime(int h,int m);
int DS1307_time2LCD();

extern uint8_t hour,min,sec;


#endif /* DS1307_H_ */