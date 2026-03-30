#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTPORT PORTC
#define BUTPIN PINC


#include "main.h"

enum button_state{
    RELEASED,
    PRESSED
    };


void Buttons_Handler();
void Buttons_init();
int Debounce(uint8_t pin);
void Edit_LCD_bright();

extern volatile int light;

#endif /* BUTTON_H_ */