#include "main.h"

volatile uint32_t ms_cnt= 0;// счетчик ms

// timer0 for mills 

void Timer0_init(void){ // timer0 1 мс при 8 MHz

	TCCR0 = (1<<WGM01)|(1<<CS00)|(1<<CS01); 
	TIMSK |=(1<<OCIE0);
	OCR0 = 125;
}

ISR(TIMER0_COMP_vect){

	ms_cnt++;
}

uint32_t get_mills(){ 

	return ms_cnt;
}