//**************************************************************
// ****** FUNCTIONS FOR SPI COMMUNICATION *******
//**************************************************************
//Controller: ATmega32 (8 Mhz internal)
//Compiler: AVR-GCC
//Author: CC Dharmani, Chennai (India)
// www.dharmanitech.com
//Date: 18 April 2009
//**************************************************************

//**************************************************
// ***** SOURCE FILE : SPI_routines.c ******
//**************************************************
#include <avr/io.h>
#include "SPI_routines.h"

//SPI initialize for SD card
//clock rate: 125Khz
void spi_init(void)
{
	SPCR = ((1<<SPE)|       // SPI Enable					(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<SPIE)|              // SPI Interupt Enable			(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<DORD)|              // Data Order					(0 = MSB first, 1 = LSB first)				Datasheet S. 197 (Kapitel 21.2.1)
	(1<<MSTR)|              // Master/Slave select			(0 = Slave, 1 = Master)						Datasheet S. 197 (Kapitel 21.2.1)
	(1<<SPR1)|(1<<SPR0)|    // SPI Clock Rate				(Divider Systemclock 16MHz)					Datasheet S. 198 (Kapitel 21.2.1)
	(0<<CPOL)|              // Clock Polarity when idle		(0 = low, 1 = SCK high)						Datasheet S. 197 (Kapitel 21.2.1)
	(0<<CPHA));             // Clock Phase edge sampling	(0 = leading, 1 = trailing edge sampling)	Datasheet S. 197 (Kapitel 21.2.1)

	SPSR = (0<<SPI2X);      // Double Clock Rate			(0 = Disable, 1 = Enable)					Datasheet S. 198 (Kapitel 21.2.1)
}

unsigned char SPI_transmit(unsigned char data)
{
// Start transmission
SPDR = data;

// Wait for transmission complete
while(!(SPSR & (1<<SPIF)));
data = SPDR;

return(data);
}

unsigned char SPI_receive(void)
{
unsigned char data;
// Wait for reception complete

SPDR = 0xff;
while(!(SPSR & (1<<SPIF)));
data = SPDR;

// Return data register
return data;
}

//******** END ****** www.dharmanitech.com *****
