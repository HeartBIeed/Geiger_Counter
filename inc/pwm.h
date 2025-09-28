#ifndef PWM_H_
#define PWM_H_

#include "main.h"


void pwm_init(uint16_t top);
uint16_t freq(uint16_t f_pwm,  uint16_t prescaler);
void pwm_init_lcd(void);
void set_duty(uint16_t A,uint16_t B);
int pwm_proc(int p);

#endif /* PWM_H_ */



