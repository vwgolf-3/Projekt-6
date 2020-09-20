/*
 * pin_defs.h
 *
 * Created: 13.05.2020 14:24:54
 *  Author: kimsc
 */ 


#ifndef PIN_DEFS_H_
#define PIN_DEFS_H_

#include <avr/io.h>

// ************************    A       ***************************************//

#define PUMPE_PORT PORTA						// Namensgebung Timerregister H
#define PUMPE_DDR DDRA							// Namensgebung Timer Register
#define PUMPE_PIN PINA

#define FLUSS10_BIT (1<<0)						// FLUSS10 PIN0
#define FLUSS10_PORT PORTA						// FLUSS1o PORTA
#define FLUSS10_DDR DDRA						// FLUSS10 DDRA
#define FLUSS10_PIN PINA						// FLUSS10 PINA

#define FLUSS11_BIT (1<<1)						// FLUSS11 PIN1
#define FLUSS11_PORT PORTA						// FLUSS1o PORTA
#define FLUSS11_DDR DDRA						// FLUSS10 DDRA
#define FLUSS11_PIN PINA						// FLUSS10 PINA

#define PUMPE0_BIT (1<<2)						// PUMPE0 PIN2
#define PUMPE0_PORT PORTA						// PUMPE0 PORTA
#define PUMPE0_DDR DDRA							// PUMPE0 DDRA
#define PUMPE0_PIN PINA							// PUMPE0 PINA

#define PUMPE1_BIT (1<<3)						// PUMPE1 PIN2
#define PUMPE1_PORT PORTA						// PUMPE1 PORTA
#define PUMPE1_DDR DDRA							// PUMPE1 DDRA
#define PUMPE1_PIN PINA							// PUMPE1 PINA

#define PUMPE2_BIT (1<<4)						// PUMPE2 PIN2
#define PUMPE2_PORT PORTA						// PUMPE2 PORTA
#define PUMPE2_DDR DDRA							// PUMPE2 DDRA
#define PUMPE2_PIN PINA							// PUMPE2 PINA

#define PUMPE3_BIT (1<<5)						// PUMPE3 PIN2
#define PUMPE3_PORT PORTA						// PUMPE3 PORTA
#define PUMPE3_DDR DDRA							// PUMPE3 DDRA
#define PUMPE3_PIN PINA							// PUMPE3 PINA

#define PUMPE4_BIT (1<<6)						// PUMPE4 PIN2
#define PUMPE4_PORT PORTA						// PUMPE4 PORTA
#define PUMPE4_DDR DDRA							// PUMPE4 DDRA
#define PUMPE4_PIN PINA							// PUMPE4 PINA

#define PUMPE5_BIT (1<<7)						// PUMPE5 PIN2
#define PUMPE5_PORT PORTA						// PUMPE5 PORTA
#define PUMPE5_DDR DDRA							// PUMPE5 DDRA
#define PUMPE5_PIN PINA							// PUMPE5 PINA

#define PUMPE_OUTPUT_MASK (PUMPE0_BIT|PUMPE1_BIT|PUMPE2_BIT|PUMPE3_BIT|PUMPE4_BIT|PUMPE5_BIT)
//
// ************************    B       ***************************************//
//
#define SPI_PORT PORTB							// Namensgebung Ausgaberegister B
#define SPI_DDR DDRB							// Namensgebung DataDirection Register
#define SPI_PIN PINB
//
#define SPI_CS_BIT (1<<0)						// Bit-Zuweisung PB5 (Arduino: 49, Pinnr: 23)
#define SPI_CS_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_CS_DDR DDRB							// SPI_CS_RC522 DDRB
#define SPI_CS_PIN PINB							// SPI_CS_RC522 PINB
//
#define SPI_CLK_BIT (1<<1)						// Bit-Zuweisung PB1 (Arduino: 52, Pinnr: 20)
#define SPI_CLK_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_CLK_DDR DDRB						// SPI_CS_RC522 DDRB
#define SPI_CLK_PIN PINB						// SPI_CS_RC522 PINB
//
#define SPI_MOSI_BIT (1<<2)						// Bit-Zuweisung PB2 (Arduino: 51, Pinnr: 21)
#define SPI_MOSI_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_MOSI_DDR DDRB						// SPI_CS_RC522 DDRB
#define SPI_MOSI_PIN PINB						// SPI_CS_RC522 PINB
//
#define SPI_MISO_BIT (1<<3)						// Bit-Zuweisung PB3 (Arduino: 50, Pinnr: 22)
#define SPI_MISO_PORT PORTB						// SPI_CS_RC522 PORTB
#define SPI_MISO_DDR DDRB						// SPI_CS_RC522 DDRB
#define SPI_MISO_PIN PINB						// SPI_CS_RC522 PINB
//
#define SPI_OUTPUT_MASK (SPI_CS_BIT|SPI_CLK_BIT|SPI_MOSI_BIT)
//
// ************************    G       ***************************************//
//
#define PUMPE_PORT2 PORTG						// Namensgebung Timerregister H
#define PUMPE_DDR2 DDRG							// Namensgebung Timer Register
#define PUMPE_PIN2 PING

#define SPI_CS_SD_CARD_BIT (1<<5)				// SPI_CS_SD_CARD PIN5
#define SPI_CS_SD_CARD_PORT PORTG				// SPI_CS_SD_CARD PORTG
#define SPI_CS_SD_CARD_DDR DDRG					// SPI_CS_SD_CARD DDRG
#define SPI_CS_SD_CARD_PIN PING					// SPI_CS_SD_CARD PING
//
#define PUMPE2_OUTPUT_MASK (SPI_CS_SD_CARD_BIT)


#endif /* PIN_DEFS_H_ */