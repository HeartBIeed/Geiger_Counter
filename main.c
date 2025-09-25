#include "main.h"


volatile uint32_t count = 0;

volatile uint32_t  ms_cnt= 0;// счетчик ms


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


ISR(INT0_vect)
{
	count++;
}
uint32_t get_mills()
{
	return ms_cnt;
}

int main(void)
{
	//------------------------ interrupt
	MCUCR  = (1<<ISC00)|(1<<ISC01); // rising INT0
	GICR |= (1<<INT0); // int 0 enable
	
	sei();
	timer_ini();
	LCD_ini_1602();
	USART_ini(103);
 	USART_TX('A');

	
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

uint32_t start = 0;
uint32_t start2 = 0;

DDRD |= (1<<6);


while(1)
	{	
		
		
		time_to_lcd();
//---------------------------------		
if (ms_cnt - start2 >= 1000)
{

 	dht_write_data(data);
 	setpos(0,1);
 	send_ptr_str(data);
		start2 = get_mills();
	}

	 
//--------------------------	 

		if (data_ready)
		{
			if (uart_rx_buffer[0]=='q')
			{
				PORTD |= (1<<PORTD6);
				data_ready = 0;
			}
			

		}
	 
if (ms_cnt - start >= 5000)
	{
		//char ch ='0' + (count % 10);
		setpos(10,0);
		sendchar('*');


		start = get_mills();
	}






	}
}