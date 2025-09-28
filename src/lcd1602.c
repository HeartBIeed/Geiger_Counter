#include "../inc/lcd1602.h"

void sendbyte(unsigned char c);
void send(unsigned char c,unsigned char mode);


void LCD_ini_1602(void)
{
	//---------------настроить порт------------------
	DDRA=0xFF;
	PORTA=0x00;
	//----------------------------------------------
	_delay_ms(15);
	sendbyte(0x03);  // 0x03 -> 0b11 включает 4 битный режим
	_delay_ms(4);
	sendbyte(0x03);
	_delay_us(100);
	sendbyte(0x03);
	_delay_ms(1);
	sendbyte(0x02);
	_delay_ms(1);


	send(0b00101000, 0); // отправка команд
	_delay_ms(1);

	send(0b00001100, 0);
	_delay_ms(1);

	send(0b00000110, 0);
	_delay_ms(1);


}

void sendbyte(unsigned char c) // отправка байта
{
	c<<=4; // сдвигаем байт младшей тетрадой к старшей

	E1;
	_delay_us(50);
		
	PORTA &= 0b00001111; // отчистка старшей тетрады порта
	PORTA  |= c; // отправляем старшую тетраду
	
	E0;	
	_delay_us(50);
		
}

void send(unsigned char c,unsigned char mode)
{
	if (mode ==0) 
		{
			RS0; // команда 0
		} 
	else
		{
			RS1; // данные 1
		}
	
	unsigned char hc=0;
	hc = c >> 4;

	sendbyte(hc); // старший ниббл
	sendbyte(c);	
}



void sendchar(unsigned char c) // отправка 1 символа
{

	send(c,1);
	_delay_ms(10);
}

void setpos(unsigned char x, unsigned y) // установка позиции Х 0-15, У 0-1.
{
	char adress;

	adress=(0x40*y+x)|0b10000000; // адреса символов 2ой строки идут от 40, 8й бит передает команду установки позиции

	send(adress, 0);

}


void send_ptr_str(char *str) // отправка строки по указателю массива
{
	    while (*str) 
		{
		sendchar(*str++); //посимвольная передача до нуля
	    }
}
