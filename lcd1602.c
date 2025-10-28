#include "lcd1602.h"


void LCD1602_ini(void)
	{

		SETPORT
		MODEPORT
		
			_delay_ms(15);
		send_nibble(0x3);  // 0b00000011 включает 4 битный режим
			_delay_ms(4);
		send_nibble(0x3);
			_delay_us(100);
		send_nibble(0x3);
			_delay_ms(1);
		send_nibble(0x2);
			_delay_ms(1);


		send_byte(0b00101000, 0); // отправка команд
			_delay_ms(1);

		send_byte(0b00001100, 0);	
			_delay_ms(1);

		send_byte(0b00000110, 0);	
			_delay_ms(1);

	}

void send_nibble(uint8_t byte) // отправка полубайта
	{
		
		byte<<=4; // сдвигаем байт младшей тетрадой к старшей

		E1
		_delay_us(50);

		PORTA &= 0xF; // отчистка старшей тетрады порта
		PORTA |=byte; 

		E0
		_delay_us(50);
			
	}

void send_byte(uint8_t c,uint8_t mode)
	{

		if (mode ==0) {RS0} // команда 0
		else {RS1}// данные 1
		
		uint8_t hc=0;
		hc = c >> 4;

		send_nibble(hc); // H nibble
		send_nibble(c);	// L  nibble
	}

void send_lcd_char(uint8_t c) // отправка 1 символа
	{
		send_byte(c,1);
			_delay_ms(10);
	}

void set_lcd_pos(uint8_t x, uint8_t y) // установка позиции Х 0-15, У 0-1.
	{
		uint8_t adress;

		adress=(0x40*y+x)|0b10000000; // адреса символов 2ой строки идут от 40, 8й бит передает команду установки позиции

		send_byte(adress, 0);

	}


void send_lcd_ptr_str(uint8_t *str) // отправка строки по указателю массива
	{
		while (*str) {

		send_lcd_char(*str++); //посимвольная передача до нуля
		
		}

	}


void create_symb(uint8_t index_symb, const uint8_t *data) 
	{
		uint8_t adress;
		uint8_t i;

		adress=0x40|(index_symb << 3); //<< 3 = умножить на 8.

		send_byte(adress, 0);

		for (i = 0; i < 8; i++)
			{
				send_byte(data[i], 1);
			}

	}

