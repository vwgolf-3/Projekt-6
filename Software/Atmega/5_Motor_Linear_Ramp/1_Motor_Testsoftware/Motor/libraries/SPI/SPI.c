/*
 * SPI.c
 *
 * Created: 02.12.2019 01:17:39
 *  Author: kimsc
 */ 
#include "SPI.h"

void (*ptr_SPI_w_completed)(void);

void SPI_init(void)
{
	// Einstellungen für TMC4671: CLK = 1MHz, SPI-Mode = 3, MSB first)

	SPCR = ((1<<SPE)|       // SPI Enable					(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<SPIE)|              // SPI Interupt Enable			(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<DORD)|              // Data Order					(0 = MSB first, 1 = LSB first)				Datasheet S. 197 (Kapitel 21.2.1)
	(1<<MSTR)|              // Master/Slave select			(0 = Slave, 1 = Master)						Datasheet S. 197 (Kapitel 21.2.1)
	(1<<SPR1)|(1<<SPR0)|    // SPI Clock Rate				(Divider Systemclock 16MHz)					Datasheet S. 198 (Kapitel 21.2.1)
	(1<<CPOL)|              // Clock Polarity when idle		(0 = low, 1 = SCK high)						Datasheet S. 197 (Kapitel 21.2.1)
	(1<<CPHA));             // Clock Phase edge sampling	(0 = leading, 1 = trailing edge sampling)	Datasheet S. 197 (Kapitel 21.2.1)

	SPSR = (0<<SPI2X);      // Double Clock Rate			(0 = Disable, 1 = Enable)					Datasheet S. 198 (Kapitel 21.2.1)

	disable_Slave(SDCARD);
	disable_Slave(TMC4671);
	disable_Slave(TMC6200);
	disable_Slave(MFRC522);
	
}

void spi_transmit_IT( unsigned char *data, unsigned char nbytes, uint8_t Slave)
{
	for (int i = 0 ; i < nbytes ; i++)
	{
		SPDR = *(uint8_t *)(data + i);
		while(!(SPSR & (1<<SPIF)));
	}
}

uint8_t spi_transmit(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return data;
}

char spi_receive(void)
{
	char data;
	// Wait for reception complete
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	data = SPDR;
	// Return data register
	return data;
}

void enable_Slave(uint8_t Slave)
{
	switch (Slave)
	{
		case TMC4671:
		SPI_CS_TMC4671_PORT &= ~SPI_CS_TMC4671_BIT;
		break;
		
		case TMC6200:
		SPI_CS_TMC6200_PORT &= ~SPI_CS_TMC6200_BIT;
		break;
	}
}

void disable_Slave(uint8_t Slave)
{
	switch (Slave)
	{
		case TMC4671:
		SPI_CS_TMC4671_PORT |= SPI_CS_TMC4671_BIT;
		break;
		
		case TMC6200:
		SPI_CS_TMC6200_PORT |= SPI_CS_TMC6200_BIT;
		break;
	}
}