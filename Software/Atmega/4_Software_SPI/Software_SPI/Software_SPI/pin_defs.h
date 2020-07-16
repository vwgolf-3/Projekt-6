/*
 * pin_defs.h
 *
 * Created: 15.07.2020 12:08:36
 *  Author: kimsc
 */ 


#ifndef PIN_DEFS_H_
#define PIN_DEFS_H_

#include <avr/io.h>

/* default pins */
#define SOFTSPI_CLK_DDR DDRC
#define SOFTSPI_CLK_PORT PORTC
#define SOFTSPI_CLK_MASK (1 << 4)

#define SOFTSPI_MOSI_DDR DDRC
#define SOFTSPI_MOSI_PORT PORTC
#define SOFTSPI_MOSI_MASK (1 << 2)

#define SOFTSPI_CS_DDR DDRC
#define SOFTSPI_CS_PORT PORTC
#define SOFTSPI_CS_MASK (1 << 1)

#ifndef SOFTSPI_DONT_USE_MISO
#define SOFTSPI_DONT_USE_MISO 0
#endif

#if (SOFTSPI_DONT_USE_MISO == 0)
#define SOFTSPI_MISO_DDR DDRC
#define SOFTSPI_MISO_PIN PINC
#define SOFTSPI_MISO_MASK (1 << 3)
#endif


#endif /* PIN_DEFS_H_ */