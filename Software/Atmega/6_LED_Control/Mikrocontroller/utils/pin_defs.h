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
// ************************    F       ***************************************//
#define LED_PORT PORTF                          // Namensgebung LED/Durchfluss/Referenzschalter
#define LED_DDR DDRF                            // Namensgebung
#define LED_PIN PINF

#define LEDR_BIT (1<<6)                         // LEDR PIN3
#define LEDR_PORT PORTF                         // LEDR PORTF
#define LEDR_DDR DDRF                           // LEDR DDRF
#define LEDR_PIN PINF                           // LEDR PINF

#define LEDG_BIT (1<<5)                         // LEDG PIN4
#define LEDG_PORT PORTF                         // LEDG PORTF
#define LEDG_DDR DDRF                           // LEDG DDRF
#define LEDG_PIN PINF                           // LEDG PINF

#define LEDB_BIT (1<<4)                         // LEDB PIN5
#define LEDB_PORT PORTF                         // LEDB PORTF
#define LEDB_DDR DDRF                           // LEDB DDRF
#define LEDB_PIN PINF                           // LEDB PINF

#define LEDW_BIT (1<<3)                         // LEDW PIN6
#define LEDW_PORT PORTF                         // LEDW PORTF
#define LEDW_DDR DDRF                           // LEDW DDRF
#define LEDW_PIN PINF                           // LEDW PINF

#define LED_OUTPUT_MASK (LEDR_BIT|LEDG_BIT|LEDB_BIT|LEDW_BIT)

#endif /* PIN_DEFS_H_ */