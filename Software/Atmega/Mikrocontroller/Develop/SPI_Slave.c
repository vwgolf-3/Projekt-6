/*
 * SPI_Slave.c
 *
 * Created: 17.01.2020 16:17:16
 *  Author: kimsc
 */ 

#include "SPI_Slave.h"

void SPI_slave_init(slave_SPI_t *spi_sl, char PORT, char PIN)
{
	spi_sl->PORT = PORT;
	spi_sl->PIN = PIN;
}

unsigned char SPI_slave_port(slave_SPI_t *spi_sl)
{
	unsigned char ret;
	ret = spi_sl->PORT;
	return ret;
}

unsigned char SPI_slave_pin(slave_SPI_t *spi_sl)
{
	unsigned char ret;
	ret = spi_sl->PIN;
	return ret;
}
