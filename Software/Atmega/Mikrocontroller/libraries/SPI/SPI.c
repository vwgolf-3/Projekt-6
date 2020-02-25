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
	(1<<SPIE)|              // SPI Interupt Enable			(1 = Enable, 0 = Disable)					Datasheet S. 197 (Kapitel 21.2.1)
	(0<<DORD)|              // Data Order					(0 = MSB first, 1 = LSB first)				Datasheet S. 197 (Kapitel 21.2.1)
	(1<<MSTR)|              // Master/Slave select			(0 = Slave, 1 = Master)						Datasheet S. 197 (Kapitel 21.2.1)
	(0<<SPR1)|(1<<SPR0)|    // SPI Clock Rate				(Divider Systemclock 16MHz)					Datasheet S. 198 (Kapitel 21.2.1)
	(1<<CPOL)|              // Clock Polarity when idle		(0 = low, 1 = SCK high)						Datasheet S. 197 (Kapitel 21.2.1)
	(1<<CPHA));             // Clock Phase edge sampling	(0 = leading, 1 = trailing edge sampling)	Datasheet S. 197 (Kapitel 21.2.1)

	SPSR = (0<<SPI2X);      // Double Clock Rate			(0 = Disable, 1 = Enable)					Datasheet S. 198 (Kapitel 21.2.1)

	RB_init(&rb_SPI_w);
	RB_init(&rb_SPI_r);

	sei();

	ptr_SPI_w_completed=SPI_w_completed;

	DISABLE_CS(SPI_PORT,SPI_CS_TMC4671);
}

void SPI_Transmit_IT_TMC( unsigned char *data, unsigned char nbytes)
{
#ifndef ACTUAL_PORT
#define ACTUAL_PORT SPI_PORT
#endif
#ifdef ACTUAL_PORT
#undef ACTUAL_PORT
#define ACTUAL_PORT SPI_PORT
#endif
#ifndef ACTUAL_PIN
#define ACTUAL_PIN SPI_CS_TMC4671
#endif
#ifdef ACTUAL_PIN
#undef ACTUAL_PIN
#define ACTUAL_PIN SPI_CS_TMC4671
#endif
	ENABLE_CS(ACTUAL_PORT,ACTUAL_PIN);
	RB_write(&rb_SPI_w, data, nbytes);
	SPDR=RB_readByte(&rb_SPI_w);
}

void SPI_w_completed(){	asm("nop");	asm("nop");}

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
		DISABLE_CS(ACTUAL_PORT,ACTUAL_PIN);
	}
}