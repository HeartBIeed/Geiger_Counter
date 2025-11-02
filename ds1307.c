#include "ds1307.h"

unsigned char hour,min,sec;

//-------------- I2C --------------

void i2c_init(void)
	{
	 TWBR = 0x20; //десятичное 32 частота 10kHZ при тактировании 8 мГц
	}

void i2c_start(void) // старт I2C
	{
	 TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);// Interrput / Start / Enable
	 while(!(TWCR&(1<<TWINT))); // ждем TWINT в нуле - задание оконченно/ пока 1 - работа
	}

void i2c_stop(void) // стоп i2c
	{
	 TWCR =(1<<TWINT)|(1<<TWSTO)|(1<<TWEN); // в бит стоп 1
	}

void i2c_send(unsigned char data)
	{
	 TWDR = data;// запись данных в регистр данных
	 TWCR=(1<<TWINT)|(1<<TWEN);//вкл передача
	 while(!(TWCR&(1<<TWINT))); // TWINT ждем в нуле
	}

unsigned char i2c_read(void) 
	{
	 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//TWEA - ведомый подтверждает АСК
	 while(!(TWCR&(1<<TWINT))); // TWINT ждем в нуле
	 return TWDR;
	}

unsigned char i2c_read_lastbyte(void) // чтение последнего байта
	{
	 TWCR=(1<<TWINT)|(1<<TWEN); // без АСК
	 while(!(TWCR&(1<<TWINT))); 
	 return TWDR;

	}

//----------------------------


unsigned char DecToBSD(unsigned char chin) // 10 >> 0x10
	{
	 unsigned char chout = ((chin / 10)<<4)|(chin % 10);
	 return chout;
	}

unsigned char BSDtoDec(unsigned char chin) // 0x10 >> 10
	{
	 unsigned char chout = ((chin >> 4 )*10) + (0b00001111 & chin);
	 return chout;
	}


void set_time(uint32_t h,uint32_t m) // настройка времени
	{
	 i2c_init();

	i2c_start(); 
		i2c_send(0b11010000); // адрес 0x68 + 0 - бит отправки
		i2c_send(0);
		i2c_send(DecToBSD(0)); //секунды
		i2c_send(DecToBSD(m)); //минуты
		i2c_send(DecToBSD(h)); //часы
	i2c_stop();
	} 

void lcd_print_number(unsigned char num) 
	{
	send_lcd_char((num / 10) + '0');  // десятки
	send_lcd_char((num % 10) + '0');  // единицы
	}

void time_to_lcd(int x,int y)
	{
	i2c_init();
	
	i2c_start();
		i2c_send(0b11010000);
		i2c_send(0);
	i2c_stop();
		
	i2c_start();
		i2c_send(0b11010001); // адрес 0x68 + 0 - бит read
		sec = i2c_read();
		min = i2c_read();
		hour =i2c_read_lastbyte();
	i2c_stop();
		
	sec = BSDtoDec(sec);
	min = BSDtoDec(min);
	hour =BSDtoDec(hour);

	set_lcd_pos(x,y);

	lcd_print_number(hour);
	send_lcd_char(0x3A); // :
	lcd_print_number(min);
	send_lcd_char(0x3A);
	lcd_print_number(sec);
	
	}



