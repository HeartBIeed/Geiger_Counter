#include "main.h"


volatile uint32_t ms_cnt= 0;// счетчик ms
volatile uint32_t gamma_cnt = 0; // счет событий
volatile uint8_t gamma_fact = 0; //флаг события



//------------- timer 0 for mills -------------------

void timer_ini(void) // timer0 1 мс
{
	TCCR0 = (1<<WGM01)|(1<<CS00)|(1<<CS01); 
	TIMSK |=(1<<OCIE0);
	OCR0 = 125;
	
}

ISR(TIMER0_COMP_vect)
{
	ms_cnt++;
}

uint32_t get_mills()
{
	return ms_cnt;
}

//-------------------- gamma ----------------------
ISR(INT0_vect) // внешнее прерывание PD2
{
	gamma_cnt++;
	gamma_fact =1;
}


int main(void)
{
	
	
	sei();
	timer_ini();
	i2c_init();		

	LCD1602_ini();
	USART_init(103);

	USART_send_str("UART EN");
	
//------------------------ interrupt--------------

	MCUCR  = /*(1<<ISC00)|*/(1<<ISC01); // falling INT0 
	GICR |= (1<<INT0); // int0 enable (PD2)
	
//------------------------set ds1307-----------------
	
//set_time(23,26);

//------------------PWM---------------------

	uint16_t top = freq(3000,8);
		pwm_init(top);//шим HV генератора (PD4,PD50
		
	uint16_t dt1 = pwm_proc(50);
		set_duty(dt1,dt1);
		
	pwm_init_lcd(); //подсветка LCD (PB3)
		OCR0 = pwm_proc(50);


//----------------------------------------------
uint32_t start[3] = {0};
uint32_t start_cnt = 0;

char num_gm_cnt[4]="00/n";


while(1)
	{	
		
//----------------time to lcd ----------------
if (ms_cnt - start[1] >= 900)
{		
		time_to_lcd(0,0);
		
		start[1] = get_mills();
	}
		
		

	 
//---------------uart -------------------------	 
/*
if (data_ready)
{
	uint32_t hour, min;
	if (strncmp((char*)data_buffer,"-st",3) == 0) //4 первых символа стравниваем
	{
		hour =nstrncmp((char*)data_buffer,"-st",2)
		min = strncmp((char*)data_buffer,"-st",2)
		set_time(hour,min);
	
	}
}
*/
//--------------gamma-------------------

	if (gamma_cnt - start_cnt >= 1)
		{

			set_lcd_pos(12,0);
			sprintf(num_gm_cnt,"%d",gamma_cnt);
			send_lcd_ptr_str(num_gm_cnt);
			start_cnt = gamma_cnt;	
		}



	if (gamma_fact)
		{
			set_lcd_pos(11,0);
			send_lcd_char('G');
			
		if (ms_cnt - start[0] >= 500)
			{
				set_lcd_pos(11,0);
				send_lcd_char(' ');
				gamma_fact = 0;
				start[0] = get_mills();
			}

		}
		
	
	
	}
}