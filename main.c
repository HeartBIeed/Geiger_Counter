#include "main.h"


volatile uint32_t count = 0;
volatile uint32_t  ms_cnt= 0;// счетчик ms
volatile uint8_t gamma = 0;



//------------------timer 0 for mills----------------------------------
void timer_ini(void) // timer0
{
	TCCR0 = (1<<WGM01)|(1<<CS00)|(1<<CS01); // Вкл СТС, Выбор делителя частота/64
	TIMSK |=(1<<OCIE0); // Включение прерывания по совпадению  (СТС)
	//  TIMSK |=(1<<TOIE0); // Включение прерывания по переполнению

	OCR0 = 125; // числа для сравнения
	
}

ISR(TIMER0_COMP_vect) //Обработка прерывания. В скобках вектор пр-ния по переполнению
{
	ms_cnt++;
}

uint32_t get_mills()
{
	return ms_cnt;
}

//--------------------gamma -----------
ISR(INT0_vect) // count gamma
{
	count++;
	gamma = 1;
}


int main(void)
{
	
	
	sei();
	timer_ini();
	LCD_ini_1602();
	USART_ini(103);
 	USART_TX('A');
//------------------------ interrupt--------------

	MCUCR  = (1<<ISC00)|(1<<ISC01); // rising INT0
	GICR |= (1<<INT0); // int 0 enable
	
//------------------------set ds1307-----------------
	
//set_time(23,26);

//------------------PWM---------------------

		uint16_t top = freq(3000,8);
	pwm_init(top);//шим высоковольтного ненератора
		
		uint16_t dt1 = pwm_proc(50);
		set_duty(dt1,dt1);
		
	pwm_init_lcd(); //подсветка лсд
		OCR0 = pwm_proc(10); //10%



// ------------DHT11-----------------------
 	char data[16];
	 // = "H:60% T:25\xDF" "C";
DDRD |= (1<<6); // pin PD6



//----------------------------------------------
uint32_t start = 0;
uint32_t start2 = 0;




while(1)
	{	
		
//----------------time to lcd ----------------
		
		time_to_lcd();
		
		
//------------------- dht to lcd -------------		
if (ms_cnt - start2 >= 3000)
{

 	dht_write_data(data);
 	setpos(0,1);
 	send_ptr_str(data);
		start2 = get_mills();
	}

	 
//---------------uart -------------------------	 

		if (data_ready)
		{
			if (received_byte=='q')
			{
				PORTD ^= (1<<PORTD6);
				data_ready = 0;
			}
			

		}


//--------------gamma-------------------
		setpos(12,0);
		sendchar(count);


	if (gamma)
	{
	setpos(11,0);
	sendchar('G');
		
			if (ms_cnt - start >= 1000)
			{
			setpos(11,0);
			sendchar(' ');
			gamma = 0;
			start = get_mills();
			}

	}
	
	
	
	}
}