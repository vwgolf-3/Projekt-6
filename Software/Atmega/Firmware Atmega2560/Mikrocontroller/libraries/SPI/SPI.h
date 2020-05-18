/*
 * SPI.h
 *
 * Created: 02.12.2019 01:14:58
 *  Author: kimsc
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/interrupt.h>

#include "../../pin_defs.h"
#include "../RingBuffer/ring_buffer.h"

void SPI_init(void);
void SPI_Transmit_IT( unsigned char *data, unsigned char nbytes, uint8_t Slave);
uint8_t spi_transmit(uint8_t data);
// void SPI_w_completed();

enum SPI_Slaves{TMC4671, TMC6200, MFRC522}SPI_Slave;
enum SPI_States{ON, OFF}SPI_State;

void enable_Slave(uint8_t Slave);
void disable_Slave(uint8_t Slave);

#define ACTUALPORT PUMPE1_PORT
#define ACTUALPIN PUMPE1_PIN
#define ACTUALDDR PUMPE1_DDR
#define ACTUALBIT PUMPE1_BIT

#endif /* SPI_H_ */