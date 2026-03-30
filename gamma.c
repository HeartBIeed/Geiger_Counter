#include "gamma.h"

volatile uint8_t gamma_flag = 0; //флаг события

uint8_t gamma_array[5]={0}; // массив из 40 битов для гамма событий
uint8_t index_garray = 0; // индекс элемента гамма массива
uint8_t index_gbit = 0; // индекс бита
char num_gm_cnt[7]="00"; // строка числа результата гамма счетчика

void INT_init(){

	MCUCR  = (1<<ISC01); // falling INT0 
	GICR |= (1<<INT0); // int0 enable (PD2)
}

ISR(INT0_vect){ // внешнее прерывание (PD2) от счетчика Гейгера

	gamma_flag =1;
	gamma_array[index_garray] |= (1 << index_gbit);
}

uint8_t GAMMA_NumOnes(unsigned char array[]){    
// Подсчет единиц в гамма массиве 
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

void GAMMA_counter(){

static uint32_t start[2] = {0}; 

	if (gamma_flag){
		
	LCD1602_setPos(0,0);
	LCD1602_sendChar('G');

	LCD1602_setPos(6,1);
	sprintf(num_gm_cnt,"%d uR",GAMMA_NumOnes(gamma_array)); // запись int в строку
	LCD1602_sendString(num_gm_cnt);

	gamma_flag = 0; // сброс флага		
	}
			
	if (ms_cnt - start[0] >= 1000){ // затираем G символ на LCD 

	LCD1602_setPos(0,0);
	LCD1602_sendChar(' '); 
	start[0] = get_mills();
	}



	if (ms_cnt - start[1] >= 1000){	

	// Перебор индексов гамма массива и запись в них нулей
	// раз в 1 сек
	// * прерывание записывает по текущим индексам единицу

	start[2] = get_mills();
	index_gbit++;

		if (index_gbit>=8){ //предел гамма битов значений массива
			
		index_garray ++;			
		index_gbit = 0;
			
			if (index_garray>=5) index_garray =0; //предел гамма массива				
		}

	gamma_array[index_garray]&= ~(1<<index_gbit); //1 сек - обнуление бита из гамма массива		
	} // end if
}
