#ifndef BUTTON_H_
#define BUTTON_H_

#define BUTPORT PORTC
#define BUTPIN PINC


#include "main.h"

enum button_state{
    RELEASED,
    PRESSED
    };


void buttons();
void buttons_init();
int debounce(uint8_t pin);
void edit_light();

extern volatile int light;

#endif /* BUTTON_H_ */