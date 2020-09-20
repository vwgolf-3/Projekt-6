/*
 * pin_defs.h
 *
 * Created: 13.05.2020 14:24:54
 *  Author: kimsc
 */ 


#ifndef PIN_DEFS_H_
#define PIN_DEFS_H_

#include <avr/io.h>

//
// ************************    B       ***************************************//
//
#define SPI_PORT PORTB							// Namensgebung Ausgaberegister B
#define SPI_DDR DDRB							// Namensgebung DataDirection Register
#define SPI_PIN PINB
//
#define SPI_CS_TMC4671_BIT (1<<0)						// Bit-Zuweisung PB5 (Arduino: 49, Pinnr: 23)
#define SPI_CS_TMC4671_PORT PORTB				// SPI_CS_RC522 PORTB
#define SPI_CS_TMC4671_DDR DDRB					// SPI_CS_RC522 DDRB
#define SPI_CS_TMC4671_PIN PINB					// SPI_CS_RC522 PINB
//
#define SPI_CLK_BIT (1<<1)							// Bit-Zuweisung PB1 (Arduino: 52, Pinnr: 20)
#define SPI_CLK_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_CLK_DDR DDRB							// SPI_CS_RC522 DDRB
#define SPI_CLK_PIN PINB							// SPI_CS_RC522 PINB
//
#define SPI_MOSI_BIT (1<<2)						// Bit-Zuweisung PB2 (Arduino: 51, Pinnr: 21)
#define SPI_MOSI_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_MOSI_DDR DDRB							// SPI_CS_RC522 DDRB
#define SPI_MOSI_PIN PINB							// SPI_CS_RC522 PINB
//
#define SPI_MISO_BIT (1<<3)							// Bit-Zuweisung PB3 (Arduino: 50, Pinnr: 22)
#define SPI_MISO_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_MISO_DDR DDRB						// SPI_CS_RC522 DDRB
#define SPI_MISO_PIN PINB						// SPI_CS_RC522 PINB
//
#define SPI_OUTPUT_MASK (SPI_CS_TMC4671_BIT|SPI_CLK_BIT|SPI_MOSI_BIT)
//
// ************************    H       ***************************************

#define SPI2_PORT PORTH						// Namensgebung Timerregister H
#define SPI2_DDR DDRH							// Namensgebung Timer Register
#define SPI2_PIN PINH

#define EN_TMC6200_BIT (1<<3)					// EN_TMC6200 PIN3
#define EN_TMC6200_PORT PORTH					// EN_TMC6200 PORTH
#define EN_TMC6200_DDR DDRH						// EN_TMC6200 DDRH
#define EN_TMC6200_PIN PINH						// EN_TMC6200 PINH

#define FAULT_TMC6200_BIT (1<<4)				// DIGITAL1 PIN4
#define FAULT_TMC6200_PORT PORTH				// DIGITAL1 PORTH
#define FAULT_TMC6200_DDR DDRH					// DIGITAL1 DDRH
#define FAULT_TMC6200_PIN PINH					// DIGITAL1 PINH

#define SPI2_OUTPUT_MASK (EN_TMC6200_BIT)

//
// ************************    L       ***************************************//
//
#define SOFTSPI_PORT PORTK						// Namensgebung Durchflusssensoren
#define SOFTSPI_DDR DDRK							// Namensgebung
#define SOFTSPI_PIN PINK

#define SOFTSPI_CS_BIT (1<<0)					// FLUSS1 PIN0
#define SOFTSPI_CS_PORT PORTK						// FLUSS1 PORTK
#define SOFTSPI_CS_DDR DDRK							// FLUSS1 DDRK
#define SOFTSPI_CS_PIN PINK							// FLUSS1 PINK

#define SPI_CS_TMC6200_BIT (1<<0)				// SPI_CS_TMC6200 PIN6
#define SPI_CS_TMC6200_PORT PORTK				// SPI_CS_TMC6200 PORTH
#define SPI_CS_TMC6200_DDR DDRK					// SPI_CS_TMC6200 DDRH
#define SPI_CS_TMC6200_PIN PINK					// SPI_CS_TMC6200 PINH

#define SOFTSPI_MOSI_BIT (1<<1)						// FLUSS2 PIN0
#define SOFTSPI_MOSI_PORT PORTK						// FLUSS2 PORTK
#define SOFTSPI_MOSI_DDR DDRK							// FLUSS2 DDRK
#define SOFTSPI_MOSI_PIN PINK							// FLUSS2 PINK

#define SOFTSPI_MISO_BIT (1<<2)						// FLUSS3 PIN0
#define SOFTSPI_MISO_PORT PORTK						// FLUSS3 PORTK
#define SOFTSPI_MISO_DDR DDRK							// FLUSS3 DDRK
#define SOFTSPI_MISO_PIN PINK							// FLUSS3 PINK

#define SOFTSPI_CLK_BIT (1<<3)						// FLUSS4 PIN0
#define SOFTSPI_CLK_PORT PORTK						// FLUSS4 PORTK
#define SOFTSPI_CLK_DDR DDRK							// FLUSS4 DDRK
#define SOFTSPI_CLK_PIN PINK							// FLUSS4 PINK

#define SOFTSPI_OUTPUT_MASK (SOFTSPI_CS_BIT|SOFTSPI_MOSI_BIT|SOFTSPI_CLK_BIT|SPI_CS_TMC6200_BIT)


#define PUMPE_DDR2 DDRG                         // Namensgebung Timer Register
#define SPI_CS_SD_CARD_BIT (1<<5)               // SPI_CS_SD_CARD PIN5
#define SPI_CS_SD_CARD_PORT PORTG               // SPI_CS_SD_CARD PORTG
#define SPI_CS_SD_CARD_DDR DDRG                 // SPI_CS_SD_CARD DDRG
#define SPI_CS_SD_CARD_PIN PING                 // SPI_CS_SD_CARD PING
#define PUMPE2_OUTPUT_MASK (SPI_CS_SD_CARD_BIT)


#endif /* PIN_DEFS_H_ */