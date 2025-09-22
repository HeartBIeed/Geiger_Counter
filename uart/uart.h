#ifndef UART_H_
#define UART_H_

#include "../main.h"

ISR(USART_RXC_vect);
void USART_ini(uint16_t speed);
void USART_TX(unsigned int data);
void UART_read_data();

extern volatile uint8_t received_byte;
extern volatile uint8_t data_ready;
extern volatile uint8_t uart_rx_buffer[32];
extern volatile uint8_t uart_rx_index;

#endif /* UART_H_ */