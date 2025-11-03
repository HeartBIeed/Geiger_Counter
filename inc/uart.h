#ifndef UART_H_
#define UART_H_

#include "main.h"


void USART_init(uint16_t speed);
void USART_send_str(const char *str); // Отправка строки
void USART_echo(); //эхо
void USART_TX(uint8_t data); // отправка 1 символа
void get_usart_command();


#endif /* UART_H_ */
