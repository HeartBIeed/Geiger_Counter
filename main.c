#include "main.h"

int main(void){

	sei();

	USART_init(103); //9600
	I2C_init();
	Timer0_init();
	PWM_BLCD_init(); 
	EXINT_init();

	LCD1602_init();
	Buttons_init();

	USART_send_str("UART EN");

// ШИМ HV генератора 

	uint16_t top = freq(2000,8); // 2 КГц / 8 предделитель для F_CPU 8 МГц
		PWM_HV_init(top);//шим HV генератора (PD4,PD5)
		
	uint16_t dt1 = proc2num(20); // скважность
		PWM_SetDuty(dt1,dt1); // PD4

uint32_t start[4]; 

while(1) {	

//*************** G symbol ***************
	if (G_flag){

		LCD1602_setPos(0,0);
		LCD1602_sendChar('G');

		if (ms_cnt - start[2] >= 700){

		LCD1602_setPos(0,0);
		LCD1602_sendChar(' ');

		start[2] = get_mills();
		G_flag = 0;
		}

	}

//*************** Handlers ***************

	if (ms_cnt - start[1] >= 20){		

	USART_cmdHandler();
	Buttons_Handler();

	start[1] = get_mills();
	}

//*********** Time And Radiation ************

	if (ms_cnt - start[0] >= 900){	

	DS1307_time2LCD(4,0);

	char num_gm_cnt[7];
	sprintf(num_gm_cnt,"%d uR",Radiation()); 

	LCD1602_setPos(6,1);
	LCD1602_sendString(num_gm_cnt);


	start[0] = get_mills();
	}


	} // end while

} // end main