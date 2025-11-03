#include "main.h"


volatile uint8_t gamma_flag = 0; //флаг события

uint8_t gamma_array[5]={0}; // массив из 40 битов для гамма событий
uint8_t index_garray = 0; // индекс элемента гамма массива
uint8_t index_gbit = 0; // индекс бита

char num_gm_cnt[4]="00"; // строка числа результата гамма счетчика

ISR(INT0_vect) // внешнее прерывание (PD2) от счетчика Гейгера
{
	gamma_flag =1;
	gamma_array[index_garray] |= (1 << index_gbit);
}

//--------- Подсчет единиц в гамма массиве ------------
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

//-------------------- MAIN ------------------------

int main(void)
{
	
	sei();
	timer_ini();
	i2c_init();		
	buttons_init();
	LCD1602_ini();
	USART_init(103); //9600

	USART_send_str("UART EN");
	
//--------------------- interrupt -------------------

	MCUCR  = (1<<ISC01); // falling INT0 
	GICR |= (1<<INT0); // int0 enable (PD2)
	
//------------------ Установить время ---------------
	
//set_time(15,43);

//------------------ ШИМ HV генератора --------------

	uint16_t top = freq(2000,8); // 2 КГц / 8 предделитель для F_CPU 8 МГц
		pwm_init(top);//шим HV генератора (PD4,PD50
		
	uint16_t dt1 = pwm_proc(50); // 50% скважность
		set_duty(dt1,dt1); // PD4
		
	pwm_init_lcd(); //подсветка LCD (PB3)
//	OCR0 = pwm_proc(75);


//----------------------------------------------

uint32_t start[3] = {0}; // нулевые стартовые значения 
						 // для неблокирующих задержек



while(1)
	{	

	buttons();
	OCR0 = pwm_proc(light);

	//----------------time to lcd ----------------
	if (ms_cnt - start[1] >= 500)
		{		
			time_to_lcd(4,0);
				
			start[1] = get_mills();
		}


	//-------------- Гамма счетчик-------------------


	if (gamma_flag)
		{
			set_lcd_pos(0,0);
			send_lcd_char('G');

			set_lcd_pos(6,1);
			sprintf(num_gm_cnt,"%d",num_ones(gamma_array)); // запись int в строку
			send_lcd_ptr_str(num_gm_cnt);

			set_lcd_pos(8,1);
			send_lcd_ptr_str("uR"); //мк Рентген


			gamma_flag = 0; // сброс флага		

		}
			
	//********************************** */

	if (ms_cnt - start[0] >= 1000) // затираем G символ на LCD 
		{
				set_lcd_pos(0,0);
				send_lcd_char(' '); 
				start[0] = get_mills();

		}



	if (ms_cnt - start[2] >= 1000)
		{	

	// Перебор индексов гамма массива и запись в них нулей
	// раз в 1 сек
	// * прерывание записывает по текущим индексам единицу

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


//--------------- USART --------------- 

	get_usart_command();

	}


}