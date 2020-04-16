/*
 * SPI_Defines.h
 *
 * Created: 03.01.2020 18:17:46
 *  Author: kimsc
 */ 


#ifndef SPI_DEFINES_H_
#define SPI_DEFINES_H_

#include <avr/io.h>

// PORT-Defines
#define SPI_PORT PORTB							// Namensgebung Ausgaberegister B
#define TIMER_PORT PORTH						// Namensgebung Timerregister H

// DDR-Defines
#define SPI_DDR DDRB							// Namensgebung DataDirection Register
#define TIMER_DDR DDRH							// Namensgebung Timer Register

#define SPI_PIN PINB

// PIN-Defines
#define SPI_CS_RC522 (1<<0)						// Bit-Zuweisung PB5 (Arduino: 49, Pinnr: 23)
#define SPI_MISO (1<<3)							// Bit-Zuweisung PB3 (Arduino: 50, Pinnr: 22)
#define SPI_MOSI (1<<2)							// Bit-Zuweisung PB2 (Arduino: 51, Pinnr: 21)
#define SPI_CLK (1<<1)							// Bit-Zuweisung PB1 (Arduino: 52, Pinnr: 20)
#define SPI_CS_TMC4671 (1<<5)					// Bit-Zuweisung PB0 (Arduino: 53, Pinnr: 19)
#define EN_TMC4671 (1<<4)						// Bit-Zuweisung PB4 (Arduino: 12, Pinnr: 23)
#define HEARTBEAT_LED (1<<7)					// Bit-Zuweisung PB7 (Arduino: 13, Pinnr: 26)
#define TIMER_RESOLVER (1<<4)					// Bit-Zuweisung PH7 (Arduino: 7, Pinnr: 16)
#define TEST_LED (1<<6)							// Bit-Zuweisung PH7 (Arduino: 7, Pinnr: 16)

#define TOGGLE_LED() SPI_PORT = SPI_PORT ^ HEARTBEAT_LED

// Output Maske PORTH
#define TIMER_OUTPUT_MASK (TIMER_RESOLVER)

// Output Maske PORTB
#define SPI_OUTPUT_MASK (SPI_MOSI|SPI_CLK|SPI_CS_TMC4671|EN_TMC4671|HEARTBEAT_LED|SPI_CS_RC522)

//Settings UART_OUTPUTS
#define NEXTION_DISPLAY_1 1
#define NEXTION_DISPLAY_2 2

//Settings TMC4671
#define MOTOR0 0

// Timer On/Off
#define PWM_ON TCCR4A |= (1<<COM4B0)
#define PWM_OFF TCCR4A &= ~(1<<COM4B0)

// Enable / Disable TMC4671
#define ENABLE_TMC4671() SPI_PORT &= ~SPI_CS_TMC4671
#define DISABLE_TMC4671() SPI_PORT |= SPI_CS_TMC4671

#define ENABLE_RC522() SPI_PORT &= ~SPI_CS_RC522
#define DISABLE_RC522() SPI_PORT |= SPI_CS_RC522

#define ENABLE_TEST_LED() SPI_PORT &= ~TEST_LED
#define DISABLE_TEST_LED() SPI_PORT |= TEST_LED

// Enable / Disable CS
#define ENABLE_CS(PORT, CS) PORT &= ~CS
#define DISABLE_CS(PORT,CS) PORT |= CS

#endif /* SPI_DEFINES_H_ */