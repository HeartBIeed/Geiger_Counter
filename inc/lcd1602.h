#ifndef LCD1602_H_
#define LCD1602_H_

#include "main.h"

// ------- Выбрать и настроить порт: ------- 

#define	SETPORT	DDRA=0xFF;
#define	MODEPORT PORTA=0x01;

#define E1 PORTA|=0x8; // установка линии E в 1 стробирующая шина
#define E0 PORTA&=0x4; // установка линии E в 0
#define RS1 PORTA|=0xF7; // установка линии RS в 1 (данные)
#define RS0 PORTA&=0xFB; // установка линии RS в 0 (команда)

#define	SNDBYTE PORTA=byte; // отправляем старшую тетраду в функции send_nibble

// ------- Конец настроек порта ------- 

void LCD1602_ini(void);
void send_byte(uint8_t c,uint8_t mode); 
void send_nibble(uint8_t c);

void send_lcd_char(uint8_t c); 
// отправка 1 символа
void set_lcd_pos(uint8_t x, uint8_t y); 
// установка позиции Х 0-15, У 0-1.
void send_lcd_ptr_str(uint8_t *str);
// отправка строки по указателю массива
void create_symb(uint8_t index_symb, const uint8_t *data); 
//пользовательский символ

#endif /* LCD1602_H_ */
