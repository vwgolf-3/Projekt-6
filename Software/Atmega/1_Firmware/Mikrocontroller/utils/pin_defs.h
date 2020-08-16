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
#define SPI_CS_TMC4671_BIT (1<<0)				// Bit-Zuweisung PB5 (Arduino: 53, Pinnr: 23)
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

#define HEARTBEAT_LED_BIT (1<<7)					// Bit-Zuweisung PB7 (Arduino: 13, Pinnr: 26)
#define HEARTBEAT_LED_PORT PORTB					// SPI_CS_RC522 PORTB
#define HEARTBEAT_LED_DDR DDRB					// SPI_CS_RC522 DDRB
#define HEARTBEAT_LED_PIN PINB					// SPI_CS_RC522 PINB
//
#define SPI_OUTPUT_MASK (SPI_CS_TMC4671_BIT|SPI_CLK_BIT|SPI_MOSI_BIT|HEARTBEAT_LED_BIT)
//
// ************************    C       ***************************************//
//
#define RFID_PORT PORTC
#define RFID_DDR DDRC
#define RFID_PIN PINC

#define SPI_CS_RC522_BIT (1<<0)					// SPI_CS_RC522 PIN0
#define SPI_CS_RC522_PORT PORTC					// SPI_CS_RC522 PORTC
#define SPI_CS_RC522_DDR DDRC					// SPI_CS_RC522 DDRC
#define SPI_CS_RC522_PIN PINC					// SPI_CS_RC522 PINC

#define SW_SPI_CS_BIT (1<<1)					// SW_SPI_CS PIN1
#define SW_SPI_CS_PORT PORTC					// SW_SPI_CS PORTC
#define SW_SPI_CS_DDR DDRC						// SW_SPI_CS DDRC
#define SW_SPI_CS_PIN PINC						// SW_SPI_CS PINC

#define SW_SPI_MOSI_BIT (1<<2)					// SW_SPI_MOSI PIN2
#define SW_SPI_MOSI_PORT PORTC					// SW_SPI_MOSI PORTC
#define SW_SPI_MOSI_DDR DDRC					// SW_SPI_MOSI DDRC
#define SW_SPI_MOSI_PIN PINC					// SW_SPI_MOSI PINC

#define SW_SPI_MISO_BIT (1<<3)					// SW_SPI_MISO PIN3
#define SW_SPI_MISO_PORT PORTC					// SW_SPI_MISO PORTC
#define SW_SPI_MISO_DDR DDRC					// SW_SPI_MISO DDRC
#define SW_SPI_MISO_PIN PINC					// SW_SPI_MISO PINC

#define SW_SPI_CLK_BIT (1<<4)					// SW_SPI_CLK PIN4
#define SW_SPI_CLK_PORT PORTC					// SW_SPI_CLK PORTC
#define SW_SPI_CLK_DDR DDRC						// SW_SPI_CLK DDRC
#define SW_SPI_CLK_PIN PINC						// SW_SPI_CLK PINC

#define SW_SPI_CS2_BIT (1<<5)					// SW_SPI_CLK PIN4
#define SW_SPI_CS2_PORT PORTC					// SW_SPI_CLK PORTC
#define SW_SPI_CS2_DDR DDRC						// SW_SPI_CLK DDRC
#define SW_SPI_CS2_PIN PINC						// SW_SPI_CLK PINC


//
#define RFID_OUTPUT_MASK (SPI_CS_RC522_BIT|SW_SPI_CS_BIT|SW_SPI_MOSI_BIT|SW_SPI_CLK_BIT|SW_SPI_CS2_BIT)
//
// ************************    F       ***************************************//
#define LED_PORT PORTF							// Namensgebung LED/Durchfluss/Referenzschalter
#define LED_DDR DDRF							// Namensgebung
#define LED_PIN PINF

#define REF0_BIT (1<<0)							// REF0 PIN0
#define REF0_PORT PORTF							// REF0 PORTF
#define REF0_DDR DDRF							// REF0 DDRF
#define REF0_PIN PINF							// REF0 PINF

#define REF1_BIT (1<<1)							// REF0 PIN1
#define REF1_PORT PORTF							// LEDR PORTF
#define REF1_DDR DDRF							// LEDR DDRF
#define REF1_PIN PINF							// LEDR PINF

#define REF2_BIT (1<<2)							// REF0 PIN2
#define REF2_PORT PORTF							// LEDR PORTF
#define REF2_DDR DDRF							// LEDR DDRF
#define REF2_PIN PINF							// LEDR PINF

#define LEDR_BIT (1<<6)							// LEDR PIN3
#define LEDR_PORT PORTF							// LEDR PORTF
#define LEDR_DDR DDRF							// LEDR DDRF
#define LEDR_PIN PINF							// LEDR PINF

#define LEDG_BIT (1<<5)							// LEDG PIN4
#define LEDG_PORT PORTF							// LEDG PORTF
#define LEDG_DDR DDRF							// LEDG DDRF
#define LEDG_PIN PINF							// LEDG PINF

#define LEDB_BIT (1<<4)							// LEDB PIN5
#define LEDB_PORT PORTF							// LEDB PORTF
#define LEDB_DDR DDRF							// LEDB DDRF
#define LEDB_PIN PINF							// LEDB PINF

#define LEDW_BIT (1<<3)							// LEDW PIN6
#define LEDW_PORT PORTF							// LEDW PORTF
#define LEDW_DDR DDRF							// LEDW DDRF
#define LEDW_PIN PINF							// LEDW PINF

#define FLUSS0_BIT (1<<7)						// FLUSS0 PIN7
#define FLUSS0_PORT PORTF						// FLUSS0 PORTF
#define FLUSS0_DDR DDRF							// FLUSS0 DDRF
#define FLUSS0_PIN PINF							// FLUSS0 PINF
//
#define LED_OUTPUT_MASK (LEDR_BIT|LEDG_BIT|LEDB_BIT|LEDW_BIT)
//
// ************************    G       ***************************************//
//
#define PUMPE_PORT2 PORTG						// Namensgebung Timerregister H
#define PUMPE_DDR2 DDRG							// Namensgebung Timer Register
#define PUMPE_PIN2 PING

#define PUMPE6_BIT (1<<2)						// PUMPE6 PIN2
#define PUMPE6_PORT PORTG						// PUMPE6 PORTG
#define PUMPE6_DDR DDRG							// PUMPE6 DDRG
#define PUMPE6_PIN PING							// PUMPE6 PING

#define SPI_CS_SD_CARD_BIT (1<<5)				// SPI_CS_SD_CARD PIN5
#define SPI_CS_SD_CARD_PORT PORTG				// SPI_CS_SD_CARD PORTG
#define SPI_CS_SD_CARD_DDR DDRG					// SPI_CS_SD_CARD DDRG
#define SPI_CS_SD_CARD_PIN PING					// SPI_CS_SD_CARD PING
//
#define PUMPE2_OUTPUT_MASK (PUMPE6_BIT|SPI_CS_SD_CARD_BIT)
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

// Eigentlich für CS_ESP gedacht.
// #define SPI_CS_RC522_BIT (1<<5)					// SPI_CS_RC522 PIN5
// #define SPI_CS_RC522_PORT PORTH					// SPI_CS_RC522 PORTH
// #define SPI_CS_RC522_DDR DDRH					// SPI_CS_RC522 DDRH
// #define SPI_CS_RC522_PIN PINH					// SPI_CS_RC522 PINH

#define SPI_CS_TMC6200_BIT (1<<6)				// SPI_CS_TMC6200 PIN6
#define SPI_CS_TMC6200_PORT PORTH				// SPI_CS_TMC6200 PORTH
#define SPI_CS_TMC6200_DDR DDRH					// SPI_CS_TMC6200 DDRH
#define SPI_CS_TMC6200_PIN PINH					// SPI_CS_TMC6200 PINH

#define SPI2_OUTPUT_MASK (EN_TMC6200_BIT|SPI_CS_TMC6200_BIT)

// ************************    J       ***************************************//

#define PUMPE_PORT3 PORTJ						// Namensgebung Timerregister H
#define PUMPE_DDR3 DDRJ							// Namensgebung Timer Register
#define PUMPE_PIN3 PINJ

#define PUMPE11_BIT (1<<2)						// PUMPE11 PIN2
#define PUMPE11_PORT PORTJ						// PUMPE11 PORTJ
#define PUMPE11_DDR DDRJ						// PUMPE11 DDRJ
#define PUMPE11_PIN PINJ						// PUMPE11 PINJ

#define PUMPE10_BIT (1<<3)						// PUMPE10 PIN3
#define PUMPE10_PORT PORTJ						// PUMPE10 PORTJ
#define PUMPE10_DDR DDRJ						// PUMPE10 DDRJ
#define PUMPE10_PIN PINJ						// PUMPE10 PINJ

#define PUMPE9_BIT (1<<4)						// PUMPE9 PIN4
#define PUMPE9_PORT PORTJ						// PUMPE9 PORTJ
#define PUMPE9_DDR DDRJ							// PUMPE9 DDRJ
#define PUMPE9_PIN PINJ							// PUMPE9 PINJ

#define PUMPE8_BIT (1<<5)						// PUMPE8 PIN5
#define PUMPE8_PORT PORTJ						// PUMPE8 PORTJ
#define PUMPE8_DDR DDRJ							// PUMPE8 DDRJ
#define PUMPE8_PIN PINJ							// PUMPE8 PINJ

#define PUMPE7_BIT (1<<6)						// PUMPE7 PIN6
#define PUMPE7_PORT PORTJ						// PUMPE7 PORTJ
#define PUMPE7_DDR DDRJ							// PUMPE7 DDRJ
#define PUMPE7_PIN PINJ							// PUMPE7 PINJ

#define FLUSS9_BIT (1<<7)						// FLUSS9 PIN7
#define FLUSS9_PORT PORTJ						// FLUSS9 PORTJ
#define FLUSS9_DDR DDRJ							// FLUSS9 DDRJ
#define FLUSS9_PIN PINJ							// FLUSS9 PINJ

#define PUMPE3_OUTPUT_MASK (PUMPE11_BIT|PUMPE10_BIT|PUMPE9_BIT|PUMPE8_BIT|PUMPE7_BIT)
//
// ************************    K       ***************************************//
//
#define FLUSS_PORT PORTK						// Namensgebung Durchflusssensoren
#define FLUSS_DDR DDRK							// Namensgebung
#define FLUSS_PIN PINK

#define FLUSS1_BIT (1<<0)						// FLUSS1 PIN0
#define FLUSS1_PORT PORTK						// FLUSS1 PORTK
#define FLUSS1_DDR DDRK							// FLUSS1 DDRK
#define FLUSS1_PIN PINK							// FLUSS1 PINK

#define FLUSS2_BIT (1<<1)						// FLUSS2 PIN0
#define FLUSS2_PORT PORTK						// FLUSS2 PORTK
#define FLUSS2_DDR DDRK							// FLUSS2 DDRK
#define FLUSS2_PIN PINK							// FLUSS2 PINK

#define FLUSS3_BIT (1<<2)						// FLUSS3 PIN0
#define FLUSS3_PORT PORTK						// FLUSS3 PORTK
#define FLUSS3_DDR DDRK							// FLUSS3 DDRK
#define FLUSS3_PIN PINK							// FLUSS3 PINK

#define FLUSS4_BIT (1<<3)						// FLUSS4 PIN0
#define FLUSS4_PORT PORTK						// FLUSS4 PORTK
#define FLUSS4_DDR DDRK							// FLUSS4 DDRK
#define FLUSS4_PIN PINK							// FLUSS4 PINK

#define FLUSS5_BIT (1<<4)						// FLUSS5 PIN0
#define FLUSS5_PORT PORTK						// FLUSS5 PORTK
#define FLUSS5_DDR DDRK							// FLUSS5 DDRK
#define FLUSS5_PIN PINK							// FLUSS5 PINK

#define FLUSS6_BIT (1<<5)						// FLUSS6 PIN0
#define FLUSS6_PORT PORTK						// FLUSS6 PORTK
#define FLUSS6_DDR DDRK							// FLUSS6 DDRK
#define FLUSS6_PIN PINK							// FLUSS6 PINK

#define FLUSS7_BIT (1<<6)						// FLUSS7 PIN0
#define FLUSS7_PORT PORTK						// FLUSS7 PORTK
#define FLUSS7_DDR DDRK							// FLUSS7 DDRK
#define FLUSS7_PIN PINK							// FLUSS7 PINK

#define FLUSS8_BIT (1<<7)						// FLUSS8 PIN0
#define FLUSS8_PORT PORTK						// FLUSS8 PORTK
#define FLUSS8_DDR DDRK							// FLUSS8 DDRK
#define FLUSS8_PIN PINK							// FLUSS8 PINK


#define SOFTSPI_CLK_DDR SW_SPI_CLK_DDR
#define SOFTSPI_CLK_PORT SW_SPI_CLK_PORT
#define SOFTSPI_CLK_MASK SW_SPI_CLK_BIT

#define SOFTSPI_MOSI_DDR SW_SPI_MOSI_DDR
#define SOFTSPI_MOSI_PORT SW_SPI_MOSI_PORT
#define SOFTSPI_MOSI_MASK SW_SPI_MOSI_BIT

#define SOFTSPI_CS_DDR SW_SPI_CS_DDR
#define SOFTSPI_CS_PORT SW_SPI_CS_PORT
#define SOFTSPI_CS_MASK SW_SPI_CS_BIT

#ifndef SOFTSPI_DONT_USE_MISO
#define SOFTSPI_DONT_USE_MISO 0
#endif

#if (SOFTSPI_DONT_USE_MISO == 0)
#define SOFTSPI_MISO_DDR SW_SPI_MISO_DDR
#define SOFTSPI_MISO_PIN SW_SPI_MISO_PIN
#define SOFTSPI_MISO_MASK SW_SPI_MISO_BIT
#endif




#endif /* PIN_DEFS_H_ */