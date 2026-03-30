#ifndef PWM_H_
#define PWM_H_

#include "main.h"


void PWM_HV_init(uint16_t top);
void PWM_BLCD_init(void);
void PWM_SetDuty(uint16_t A,uint16_t B);
int proc2num(int p);
uint16_t freq(uint16_t f_pwm,  uint16_t prescaler);

#endif /* PWM_H_ */



