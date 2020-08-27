/*
 * TMC6200.h
 *
 *  Created on: 14.03.2018
 *      Author: ed
 */

#ifndef TMC_IC_TMC6200_H_
#define TMC_IC_TMC6200_H_
#include <stdlib.h>

#include "TMC6200_Register.h"
#include "../SPI/SPI.h"
#include "../UART/UART.h"

int tmc6200_readInt(uint8_t motor, uint8_t address);
void tmc6200_writeInt(uint8_t motor, uint8_t address, uint32_t value);
void initTMC6200(void);
void read_registers_TMC6200(void);

#define MOTOR0 0

#endif /* TMC_IC_TMC6630_H_ */
