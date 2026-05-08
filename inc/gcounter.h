#ifndef GCOUNTER_H_
#define GCOUNTER_H_

#include "main.h"

uint16_t Radiation();
void EXINT_init();

extern uint16_t SUMofCounts;
volatile extern uint32_t count;
volatile extern int8_t G_flag;

#endif /* GCOUNTER_H_ */
