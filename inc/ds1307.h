#ifndef DS1307_H_
#define DS1307_H_



#include "main.h"

void i2c_init(void);
void set_time(uint32_t h,uint32_t m);
void time_to_lcd();

extern unsigned char hour,min,sec;


#endif /* DS1307_H_ */