/*
 * 	Doku, siehe http://www.mikrocontroller.net/articles/AVR_FAT32
 *  Neuste Version: http://www.mikrocontroller.net/svnbrowser/avr-fat32/
 *	Autor: Daniel R.
 */

#include "mmc_config.h"
#include "uart.h"



//***********************Funktionen**********************************
void uputc(uint8_t c){		//zeichen senden

	loop_until_bit_is_set(UCSR0A,UDRE0);	// warten bis puffer frei ist
	UDR0 = c;								// zeichen schreiben
}	

//*******************************************************************
void uputs (uint8_t *s){		//string senden
	
  while(*s) uputc(*s++);				//sendet zeichenkette, bis ende.. '\0'    
  
}

#if (!1)

// *******************************************************************
uint8_t ugetc(void){			//zeichen holen

  while (!(UCSRA & (1<<RXC))) {;}	// warten bis Zeichen verfuegbar
        
  return UDR;  		                // Zeichen aus UDR an Aufrufer zurueckgeben
}


// *******************************************************************
void ugets(int8_t* Buffer, uint8_t MaxLen){	// zeichenkette holen
  uint8_t NextChar;
  uint8_t StringLen = 0;
 
  NextChar = ugetc();         		// Warte auf und empfange das nächste Zeichen  
                                
  while( NextChar != '\n' && StringLen < MaxLen - 1 ) {		//string ende oder puffer voll
    *Buffer++ = NextChar;
    StringLen++;
    NextChar = ugetc();
  }
   
  *Buffer = '\0';					//string abschluss
}
#endif


//*******************************************************************
void uinit (void){					//init usart Tx, 8n1 ,UDRE interupt enable

      UBRR0H = (BRC57600>>8);                                      // Baudrate Register1 (9600) UART0
      UBRR0L = (BRC57600);                                         // Baudrate Register2 (9600) UART0
      UCSR0B = (1<<RXEN0)|(1<<TXEN0);                             // Enable RX und TX UART 0
      UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);                           // Übertragene Bits: 8 und parity disabled UART0
}

