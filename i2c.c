#include "i2c.h"

uint32_t timeout;

void I2C_init(void){

	DDRC &= ~((1<<PC0) | (1<<PC1));
	TWBR = 32; //частота 10kHz при тактировании 8 мГц
}

int I2C_start(void){ 
	
	timeout = TIMEOUT;

	TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);// Interrput / Start / Enable

	while(!(TWCR&(1<<TWINT)))// ждем TWINT в нуле - задание оконченно/ пока 1 - работа
	{
		if (--timeout == 0) return 0;
	}
	return 1;
}

void I2C_stop(void){
	
	 TWCR =(1<<TWINT)|(1<<TWSTO)|(1<<TWEN); // в бит стоп 1
}

void I2C_tx(uint8_t data){
	 TWDR = data;// запись данных в регистр данных
	 TWCR=(1<<TWINT)|(1<<TWEN);//вкл передача
	 while(!(TWCR&(1<<TWINT))); // TWINT ждем в нуле
}

uint8_t I2C_rx(void) {
	 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//TWEA - ведомый подтверждает АСК
	 while(!(TWCR&(1<<TWINT))); // TWINT ждем в нуле
	 return TWDR;
}

uint8_t I2C_rx_NOACK(void){ // чтение последнего байта

	 TWCR=(1<<TWINT)|(1<<TWEN); // без АСК
	 while(!(TWCR&(1<<TWINT))); 
	 return TWDR;
}


