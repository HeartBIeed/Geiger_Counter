#ifndef I2C_H_
#define I2C_H_

#define TIMEOUT 100000

#include "main.h"

void I2C_init(void);
int I2C_start(void);
void I2C_stop(void);
void I2C_tx(uint8_t data);
uint8_t I2C_rx(void);
uint8_t I2C_rx_NOACK(void); 


#endif /* I2C_H_ */