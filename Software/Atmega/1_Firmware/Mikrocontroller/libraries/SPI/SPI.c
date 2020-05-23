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
	// Einstellungen f�r TMC4671: CLK = 1MHz, SPI-Mode = 3, MSB first)

	SPCR = ((1<<SPE)|       // SPI Enable					(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<SPIE)|              // SPI Interupt Enable			(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<DORD)|              // Data Order					(0 = MSB first, 1 = LSB first)				Datasheet S. 197 (Kapitel 21.2.1)
	(1<<MSTR)|              // Master/Slave select			(0 = Slave, 1 = Master)						Datasheet S. 197 (Kapitel 21.2.1)
	(1<<SPR1)|(1<<SPR0)|    // SPI Clock Rate				(Divider Systemclock 16MHz)					Datasheet S. 198 (Kapitel 21.2.1)
	(0<<CPOL)|              // Clock Polarity when idle		(0 = low, 1 = SCK high)						Datasheet S. 197 (Kapitel 21.2.1)
	(0<<CPHA));             // Clock Phase edge sampling	(0 = leading, 1 = trailing edge sampling)	Datasheet S. 197 (Kapitel 21.2.1)

	SPSR = (0<<SPI2X);      // Double Clock Rate			(0 = Disable, 1 = Enable)					Datasheet S. 198 (Kapitel 21.2.1)

	RB_init(&rb_SPI_w);
	RB_init(&rb_SPI_r);

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
	return SPDR;
}

unsigned char spi_receive(void)
{
	unsigned char data;
	// Wait for reception complete

	SPDR = 0xff;
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
		
		case MFRC522:
		SPI_CS_RC522_PORT &= ~SPI_CS_RC522_BIT;
		break;
		
		case SDCARD:
		SPI_CS_SD_CARD_PORT &= ~SPI_CS_SD_CARD_BIT;
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
		
		case MFRC522:
		SPI_CS_RC522_PORT |= SPI_CS_RC522_BIT;
		break;
		
		case SDCARD:
		SPI_CS_SD_CARD_PORT |= SPI_CS_SD_CARD_BIT;
		break;
	}
}

/*
void SPI_w_completed()
{
	asm("nop");
	asm("nop");
}



ISR (SPI_STC_vect)
{

	if(RB_length(&rb_SPI_w) > 0)

	{

		SPDR = RB_readByte(&rb_SPI_w);

	}

	else

	{

		if(ptr_SPI_w_completed != 0)

		{

			ptr_SPI_w_completed();

		}

		disable_Slave(TMC4671);

		SPI_active = 0;

	}

}*/