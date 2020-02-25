/*
 * SPI_Slave.h
 *
 * Created: 17.01.2020 16:12:00
 *  Author: kimsc
 */ 


#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

#define RING_BUFFER_SIZE	256

typedef struct
{
	unsigned char PORT;
	unsigned char PIN;
}slave_SPI_t;


void			SPI_slave_init(slave_SPI_t *spi_sl, char PORT, char PIN);
unsigned char	SPI_slave_port(slave_SPI_t *spi_sl);
unsigned char	SPI_slave_pin(slave_SPI_t *spi_sl);

#endif /* SPI_SLAVE_H_ */