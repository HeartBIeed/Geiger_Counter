#ifndef LCD1602_H_
#define LCD1602_H_

#include "main.h"

// ------- Выбрать и настроить порт: ------- 

#define	SETPORT	DDRA=0xFE;
#define	MODEPORT PORTA=0x00;

#define E1 PORTA|=0x8; // установка линии E в 1 стробирующая шина
#define E0 PORTA &=0xF7; // установка линии E в 0
#define RS1 PORTA|=0x4; // установка линии RS в 1 (данные)
#define RS0 PORTA &=0xFB; // установка линии RS в 0 (команда)


// ------- Конец настроек порта ------- 

void LCD1602_init(void);

void LCD1602_setPos(uint8_t x, uint8_t y); 
void LCD1602_sendChar(uint8_t c);
void LCD1602_sendString(uint8_t *str);
void LCD1602_createSymb(uint8_t index_symb, const uint8_t *data); 

#endif /* LCD1602_H_ */
