/*
 * 	Doku, siehe http://www.mikrocontroller.net/articles/AVR_FAT32
 *  Neuste Version: http://www.mikrocontroller.net/svnbrowser/avr-fat32/
 *	Autor: Daniel R.
 */

#include <avr/interrupt.h>

#include "mmc_config.h"	// Hier werden alle noetigen Konfigurationen vorgenommen, umbedingt anschauen !
#include "file.h"
#include "fat.h"
#include "mmc.h"		// Hardware abhaengig


// prototypen von funktionen in dieser datei
static void timer0_init(void);



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