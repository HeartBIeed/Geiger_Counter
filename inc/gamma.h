#ifndef GAMMA_H_
#define GAMMA_H_


#include "main.h"

void INT_init();
uint8_t GAMMA_NumOnes(unsigned char array[]);   
void GAMMA_counter();

extern uint8_t gamma_array[5];


extern volatile uint8_t gamma_flag ;
extern uint8_t index_garray; 
extern uint8_t index_gbit;


#endif /* GAMMA_H_ */