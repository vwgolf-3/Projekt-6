/*
 * SPI.h
 *
 * Created: 02.12.2019 01:14:58
 *  Author: kimsc
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/interrupt.h>

#include "../../utils/pin_defs.h"
#include "../RingBuffer/ring_buffer.h"

#define SPI_SD             SPCR = 0x52
#define SPI_HIGH_SPEED     SPCR = 0x50; SPSR |= (1<<SPI2X)


void SPI_init(void);
void spi_transmit_IT( unsigned char *data, unsigned char nbytes, uint8_t Slave);
uint8_t spi_transmit(uint8_t data);
unsigned char spi_receive(void);

// void SPI_w_completed();

enum SPI_Slaves{TMC4671, TMC6200, MFRC522, SDCARD}SPI_Slave;
enum SPI_States{ON, OFF}SPI_State;

void enable_Slave(uint8_t Slave);
void disable_Slave(uint8_t Slave);

#endif /* SPI_H_ */