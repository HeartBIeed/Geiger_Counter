#include "main.h"


volatile uint32_t ms_cnt= 0;// счетчик ms
volatile uint8_t gamma_fact = 0; //флаг события

uint8_t gamma_array[5]={0};
uint8_t index_garray = 0;
uint8_t index_gbit = 0;

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
	gamma_fact =1;
	gamma_array[index_garray] |= (1 << index_gbit);
}

//****************************************************** */
int num_ones(unsigned char array[])
{    
int counter =0;
		for(int ind_arr = 0;ind_arr<5;ind_arr++)
			{
			for(int ind_pos = 0;ind_pos<8;ind_pos++)
				{
				
					if (array[ind_arr] & (1 <<ind_pos))
						{
							counter++;
						}
				}
			}
	return counter;
}
//********************************************************

int main(void)
{
	


	sei();
	timer_ini();
	i2c_init();		

	LCD1602_ini();
	USART_init(103); //9600

	USART_send_str("UART EN");
	
//------------------------ interrupt--------------

	MCUCR  = (1<<ISC01); // falling INT0 
	GICR |= (1<<INT0); // int0 enable (PD2)
	
//------------------------set ds1307-----------------
	
//set_time(23,26);

//------------------PWM---------------------

	uint16_t top = freq(2000,8);
		pwm_init(top);//шим HV генератора (PD4,PD50
		
	uint16_t dt1 = pwm_proc(50);
		set_duty(dt1,dt1);
		
	pwm_init_lcd(); //подсветка LCD (PB3)
		OCR0 = pwm_proc(50);


//----------------------------------------------
uint32_t start[3] = {0};
uint32_t start_cnt = 0;

char num_gm_cnt[5]="00/n";


while(1)
	{	
		
//----------------time to lcd ----------------
if (ms_cnt - start[1] >= 500)
	{		
		time_to_lcd(4,0);
			
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


if (gamma_fact)
	{
		set_lcd_pos(0,1);
		send_lcd_char('G');

		set_lcd_pos(5,1);
		sprintf(num_gm_cnt,"%d",num_ones(gamma_array));
		send_lcd_ptr_str(num_gm_cnt);

		set_lcd_pos(7,1);
		send_lcd_ptr_str("uR");


		gamma_fact = 0; // сброс флага		

	}
		
//********************************** */

if (ms_cnt - start[0] >= 1000)
	{
			set_lcd_pos(0,1);
			send_lcd_char(' ');
			start[0] = get_mills();

	}



if (ms_cnt - start[2] >= 1000)
	{	

	start[2] = get_mills();
	index_gbit++;

	if (index_gbit>=8) //предел гамма битов значений массива
		{	

		index_garray ++;			
		index_gbit = 0;

			if (index_garray>=5) //предел гамма массива
				{
					index_garray =0;
				}
					
		}

	gamma_array[index_garray]&= ~(1<<index_gbit); //1 сек - обнуление бита из гамма массива
	
	}
}

	
}