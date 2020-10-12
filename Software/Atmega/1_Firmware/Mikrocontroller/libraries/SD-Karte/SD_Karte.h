/*
 * SD_Karte.h
 *
 * Created: 12.10.2020 17:22:21
 *  Author: kimsc
 */ 


#ifndef SD_KARTE_H_
#define SD_KARTE_H_


#include <avr/interrupt.h>

#include "mmc_config.h"	// Hier werden alle noetigen Konfigurationen vorgenommen, umbedingt anschauen !
#include "file.h"
#include "fat.h"
#include "mmc.h"		// Hardware abhaengig
#include "../UART/UART.h"

void SD_init();

void readFile(uint8_t * file_name);
void deleteFile(uint8_t * file_name);
uint8_t verifyFile(uint8_t * file_name);
void writeFile(uint8_t * file_name, uint8_t * str);

// prototypen von funktionen in dieser datei
void timer0_init(void);
int8_t *ltostr(int32_t num, int8_t *string, uint16_t max_chars, uint8_t base);

// timer0 einstellungen, werte mit http://www.avrcalc.com/download.html berechnet!

// aus diesen 3 werten ergibt sich die tick zeit, hier 10ms.

// 4 = prescaler 256, 3 = prescaler 64, 5 = prescaler 1024, 2 = prescaler 8. wenn prescaler 0 = prescaler dann stoppt der timer

#if(F_CPU == 4000000)			// error 0.16%
#define TOP_OCR 0x9B
#define START_TCNT 0x64
#define PRESCALER 0x04
#endif

#if(F_CPU == 8000000)			// error 0,16%
#define TOP_OCR 0x4D
#define START_TCNT 0xB2
#define PRESCALER 0x05
#endif

#if(F_CPU == 10000000)			// error 0.351%
#define TOP_OCR 0x61
#define START_TCNT 0x9E
#define PRESCALER 0x05
#endif

#if(F_CPU == 12000000)			// error 0.16%
#define TOP_OCR 0x74
#define START_TCNT 0x8B
#define PRESCALER 0x05
#endif

#if(F_CPU == 16000000)			// error 0,16%
#define TOP_OCR 0x9B
#define START_TCNT 0x64
#define PRESCALER 0x05
#endif

#if(F_CPU == 20000000)			// error 0.16%
#define TOP_OCR 0x4D
#define START_TCNT 0xB2
#define PRESCALER 0x04
#endif



// timer0 variable
volatile uint8_t 	TimingDelay;	// fuer mmc.c





#endif /* SD_KARTE_H_ */