#include "uart.h"

volatile uint8_t data_ready = 0; //флаг получения данных uart
volatile uint8_t data_buffer[32]; //буффер uart
volatile uint8_t index_buffer =0;

void USART_init(uint16_t speed)
	{

	UBRRH =(speed>>8);	
	UBRRL = speed;

	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE); //RXCIE - вкл прерывания
	UCSRA |= (1<<U2X); // x2 (9600 -> 103 -> 8 MHz)
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); //асинхронный /8 bit 
	}

void USART_TX(uint8_t data)
	{
	
	while (!(UCSRA&(1<<UDRE))); //проверяем UDRE бит что он 0 - это готовность к записи	
	UDR = data; // send data

	}


ISR(USART_RXC_vect) 
	{
	volatile uint8_t received_byte = 0;
	received_byte = UDR;  // сохраняем байт в переменную

	if (received_byte == '\r' || index_buffer >= sizeof(data_buffer)-1) //если конец строки или переполнение
		{
			data_buffer[index_buffer] = '\0'; //вставляем 0-терминатор
			index_buffer = 0;
			data_ready = 1;

		}		
		
	else	
		{
			data_buffer[index_buffer] = received_byte;
			index_buffer++;

		}
	}


void USART_send_str(const char *str) // TX string
	{
		while (*str) USART_TX(*str++); //отправка стороки до "/0"
	}

void USART_echo()
	{
		USART_send_str((char*)data_buffer);
		data_ready = 0; 
	}

	
void get_usart_command()
{
		if (data_ready)
		{
			if (strncmp((char*)data_buffer,"gamma",5) == 0) // сравниваем первые символы
			{

				char string[32];
				sprintf(string, "Gamma: %d uR\r\n",(int)num_gm_cnt);
				USART_send_str(string);

				data_ready = 0;

			}

			if (strncmp((char*)data_buffer,"time",4) == 0) 
			{
				char string[9];
				sprintf(string, "%02d:%02d:%02d\r\n", hour, min, sec);
				USART_send_str(string);

				data_ready = 0;

			}


			if (strncmp((char*)data_buffer,"st",2) == 0) 
			{

				char *command = strtok(data_buffer," ");
				char *st_hour = strtok(NULL, ",");
				char *st_min = strtok(NULL, ",");

				int hour = atoi(st_hour);
				int minute = atoi(st_min);

				set_time(hour,minute);

				char string[32];
				sprintf(string, "set time -> %02d:%02d\r\n", hour, minute);
				USART_send_str(string);

				data_ready = 0;

			}


			if (strncmp((char*)data_buffer,"snd",3) == 0) 
			{

				char *command = strtok(data_buffer," ");
				char *sound_mode = strtok(NULL, ",");


				if (strcmp(sound_mode, "on"))
				{
					PORTC |= (1<<7);
					USART_send_str("Sound ON\r\n");
				}
				else if (strcmp(sound_mode, "off"))
				{
					PORTC &= ~(1<<7);
					USART_send_str("Sound OFF\r\n");
				}

				data_ready = 0;

			}


			else
			{
				USART_send_str("GET: ");
				USART_send_str((char*)data_buffer);
				USART_send_str("\r\n");
			}				

		data_ready = 0;

		}		

}
