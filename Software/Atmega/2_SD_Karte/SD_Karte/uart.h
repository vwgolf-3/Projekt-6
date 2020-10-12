/*
 * 	Doku, siehe http://www.mikrocontroller.net/articles/AVR_FAT32
 *  Neuste Version: http://www.mikrocontroller.net/svnbrowser/avr-fat32/
 *	Autor: Daniel R.
 */


#ifndef _UART_H

  #define _UART_H  
//   #define F_CPU 16000000
  #define BAUD 9600l
  #define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD57600 57600                                   // Define für Baudrate-Register
#define BRC57600 ((F_CPU/16/BAUD57600) -1)                // Define für Baudrate-Register

  #if defined (__AVR_ATmega168__)
	#define UDR   		UDR0  
	#define UCSRA    	UCSR0A  
	#define UDRE  		UDRE0  
	#define UCSRB		UCSR0B  
	#define RXC	 		RXC0
	#define UCSRC		UCSR0C
	#define UCSZ0		UCSZ00
	#define RXEN		RXEN0
	#define TXEN		TXEN0
	#define UBRRH		UBRR0H
	#define UBRRL		UBRR0L
  #endif

  //#######################################################################################################################
  // funktionen

  extern void uinit(void);				//Initialisiert uart
  extern void uputc(uint8_t c);
  extern void uputs (uint8_t *s);
  extern void ugets( int8_t*,uint8_t);
  extern uint8_t ugetc(void);

#endif


/*
Terminal VT100 zeichen

uputc(0x1B);		//steuer zeichen ESC (hex 0x1B, dez 27) Achtung, wird erst gesendet wenn danach ein string gesendet wird !! siehe uputs uputc

uputs("[1K");		//links vom cursor zeile löschen
uputs("[K");		//rechts vom cursor zeile löschen
uputs("[2J");		//vom cursor abwärts schirm löschen
uputs("[J");		//vom cursor aufwärts schirm löschen

uputs("[01;01H");	//position cursor zeile 1, spalte 1

    * die Zeilennummer 1-24
    * die Spalternummer 1-80 oder 1-132 		


<ESC>[paramm     '-(das ist ein kleines "m" am Schluß)-'

Mögliche "param" sind:

    * 0 = Normal
    * 1 = Heller (bold)
    * 4 = Unterstrichen
    * 5 = Blinkend
    * 7 = Reverse (dunkel auf hell bzw. umgekehrt) 

Dabei können mehrere Attribute angegeben werden, dann aber mit Semikolon getrennt:

<ESC>[param1;param2;param3m 
*/
