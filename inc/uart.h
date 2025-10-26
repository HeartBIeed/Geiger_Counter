#ifndef UART_H_
#define UART_H_


#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Прототипы

void USART_init(uint16_t speed);
void USART_send_str(const char *str); // Отправка строки
void USART_echo(); //эхо

*/


#endif /* UART_H_ */
