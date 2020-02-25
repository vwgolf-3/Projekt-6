/*
 * SPI.h
 *
 * Created: 02.12.2019 01:14:58
 *  Author: kimsc
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../RingBuffer/ring_buffer.h"
#include "SPI_Defines.h"

extern ring_buffer_t rb_SPI_r;
extern ring_buffer_t rb_SPI_w;

void SPI_init(void);
void SPI_Transmit_IT_TMC(unsigned char *data, unsigned char nbytes);
void SPI_w_completed();

#endif /* SPI_H_ */