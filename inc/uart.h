#ifndef UART_H_
#define UART_H_

#include "main.h"


void USART_init(uint16_t speed);
void USART_send_str(const char *str); // Отправка строки
void USART_echo(); //эхо


#endif /* UART_H_ */
