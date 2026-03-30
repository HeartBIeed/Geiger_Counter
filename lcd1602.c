#include "lcd1602.h"

void send_nibble(uint8_t byte);
void send_byte(uint8_t c,uint8_t mode);

void LCD1602_init(void){

	SETPORT
	MODEPORT
		
		_delay_ms(15);
	send_nibble(0x3);  
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

void send_nibble(uint8_t byte){ 
	
	byte<<=4; 

	E1
	_delay_us(50);

	PORTA &= 0xF; 
	PORTA |=byte; 

	E0
	_delay_us(50);
}

void send_byte(uint8_t c,uint8_t mode){

	if (mode ==0) {RS0} // команда 0
	else {RS1}// данные 1
	
	uint8_t hc=0;
	hc = c >> 4;

	send_nibble(hc); // H nibble
	send_nibble(c);	// L  nibble
}

void LCD1602_sendChar(uint8_t c){
	
	send_byte(c,1);
	_delay_ms(10);
}

void LCD1602_setPos(uint8_t x, uint8_t y){ // установка позиции Х 0-15, У 0-1.
	
	uint8_t address;

	address=(0x40*y+x)|0b10000000; // адреса символов 2ой строки идут от 40, 8й бит передает команду установки позиции
	send_byte(address, 0);
}


void LCD1602_sendString(uint8_t *str){ 

	while (*str) LCD1602_sendChar(*str++); 
}


void LCD1602_createSymb(uint8_t index_symb, const uint8_t *data) {

	uint8_t address;
	uint8_t i;

	address=0x40|(index_symb << 3); //<< 3 = умножить на 8.
	send_byte(address, 0);

	for (i = 0; i < 8; i++)
	{
	send_byte(data[i], 1);
	}
}

