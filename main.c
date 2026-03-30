#include "main.h"



int main(void)
{
	sei();

	I2C_init();
	Timer0_init();
	Buttons_init();
	LCD1602_init();
	PWM_BLCD_init(); 
	INT_init();
	USART_init(103); //9600

	USART_send_str("UART EN");


// ШИМ HV генератора 

	uint16_t top = freq(2000,8); // 2 КГц / 8 предделитель для F_CPU 8 МГц
		PWM_HV_init(top);//шим HV генератора (PD4,PD5)
		
	uint16_t dt1 = proc2num(20); // скважность
		PWM_SetDuty(dt1,dt1); // PD4

uint32_t start = 0; 

while(1) {	

	USART_cmdHandler();
	Buttons_Handler();

	if (ms_cnt - start >= 500)// time to lcd 
	{		
	DS1307_time2LCD(4,0);	
	start = get_mills();
	}


	GAMMA_counter();

	} // end while

} // end main