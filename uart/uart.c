#include "uart.h"

volatile uint8_t received_byte = 0;
volatile uint8_t data_ready = 0;
volatile uint8_t uart_rx_buffer[32];
volatile uint8_t uart_rx_index = 0;

void USART_ini(uint16_t speed)
{
	UBRRH =(speed>>8);
	UBRRL = speed;

	UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); //RXCIE - innterr
	UCSRA |= (1<<U2X); // 8 MGc
	UCSRC |= (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0); //sel assync umsel non 2 uscz 11 - 8 bit
}

void USART_TX(unsigned int data)
{
	while (!(UCSRA&(1<<UDRE))); //проверяем в усра удре бит что он 0 ибо это готовность к записи
	
	UDR = data; // send data

}


ISR(USART_RXC_vect) {
	received_byte = UDR;  // сохраняем байт в глобальную переменную
	data_ready = 1;
}

void echo()
{
	USART_TX(received_byte);
}

void UART_read_data()
{
	
	if (data_ready)
		{
		data_ready = 0;	
		uart_rx_buffer[uart_rx_index] = received_byte;
		uart_rx_index++;

		}
		
	if (uart_rx_index >= sizeof(uart_rx_buffer))
		{
		uart_rx_index = 0;
		}

}





