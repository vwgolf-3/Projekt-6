/*
 * Software_SPI.h
 *
 * Created: 15.07.2020 12:11:16
 *  Author: kimsc
 */ 


#ifndef SOFTWARE_SPI_H_
#define SOFTWARE_SPI_H_

#include "pin_defs.h"
#define F_CPU 16000000UL

#include <util/delay.h>

void softspi_setup_master(void);
void softspi_clk_low(void);
void softspi_clk_high(void);
void softspi_mosi_low(void);
void softspi_mosi_high(void);
void softspi_write_bit(uint8_t x, uint8_t m);
void softspi_write_uint8(uint8_t x);
void softspi_write_uint16(uint16_t x);
void softspi_read_bit(uint8_t* x, uint8_t i);
uint8_t softspi_read_uint8(void);
uint16_t softspi_read_uint16(void);


#endif /* SOFTWARE_SPI_H_ */
