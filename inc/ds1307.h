#ifndef DS1307_H_
#define DS1307_H_

#include "main.h"

void lcd_print_number(unsigned char num);
void set_time(uint32_t h,uint32_t m);
void time_to_lcd();
unsigned char hour,min,sec;


#endif /* DS1307_H_ */