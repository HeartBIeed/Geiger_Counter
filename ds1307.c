#include "ds1307.h"

uint8_t hour,min,sec;

uint8_t DecToBSD(uint8_t chin){ // 10 >> 0x10
	
	uint8_t chout = ((chin / 10)<<4)|(chin % 10);
	return chout;
}

uint8_t BSDtoDec(uint8_t chin){ // 0x10 >> 10
	
	uint8_t chout = ((chin >> 4 )*10) + (0b00001111 & chin);
	return chout;
}

void lcd_print_number(uint8_t num) {
	LCD1602_sendChar((num / 10) + '0');  // десятки
	LCD1602_sendChar((num % 10) + '0');  // единицы
}

void DS1307_setTime(int h,int m){ // настройка времени
	
	I2C_start(); 
		I2C_tx(0b11010000); // адрес 0x68 + 0 - бит отправки
		I2C_tx(0);
		I2C_tx(DecToBSD(0)); //секунды
		I2C_tx(DecToBSD(m)); //минуты
		I2C_tx(DecToBSD(h)); //часы
	I2C_stop();
} 



int DS1307_time2LCD(int x,int y){

	if (I2C_start()){

	I2C_tx(0b11010000);
	I2C_tx(0);
	I2C_stop();

	} else {

	return 0;
	}

	I2C_start();
		I2C_tx(0b11010001); // адрес 0x68 + 0 - бит read
		sec = I2C_rx();
		min = I2C_rx();
		hour =I2C_rx_NOACK();
	I2C_stop();
		
	sec = BSDtoDec(sec);
	min = BSDtoDec(min);
	hour =BSDtoDec(hour);

	LCD1602_setPos(x,y);

	lcd_print_number(hour);
	LCD1602_sendChar(0x3A); // :
	lcd_print_number(min);
	LCD1602_sendChar(0x3A);
	lcd_print_number(sec);

}


