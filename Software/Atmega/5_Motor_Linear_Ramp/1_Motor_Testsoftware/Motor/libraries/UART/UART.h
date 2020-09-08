/*
 * UART.h
 *
 * Created: 01.12.2019 14:27:08
 *  Author: kimsc
 */ 


#ifndef UART_H_
#define UART_H_

/******************************************************************************************************************************/
#include "../RingBuffer/ring_buffer.h"					// Wird benötigt für den Ring-Buffer (z.B RB_init(), RB_readByte, ...)
#include <avr/interrupt.h>								// Wird benötigt für UART-Interrupts (z.B ISR(USART0_RX_vect), ...)
#include <string.h>										// Wird benötigt für Stringoperationen (z.B strcpy(), strcat(), ...)
#include <avr/io.h>										// Wird benötigt für AVR-Registernamen (z.B F_CPU, UCSRnB, UDRIEn, ...)
/******************************************************************************************************************************/

/******************************************************************************************************************************/
#define		Uart_EnableTransmitIT_0()		UCSR0B |= (1<<UDRIE0)		// Enable TX-Interrupt: Data Register empty UART 0
#define		Uart_DisableTransmitIT_0()	UCSR0B &= ~(1<<UDRIE0)			// Disable TX-Interrupt: Data Register empty UART 0

#define		Uart_EnableRxIT_0()		UCSR0B |= (1<<RXCIE0)				// Enable RX-Interrupt: Receive Complete UART 0
#define		Uart_DisableRxIT_0()		UCSR0B &= ~(1<<RXCIE0)			// Disable RX-Interrupt: Receive Complete UART 0
/******************************************************************************************************************************/


/******************************************************************************************************************************/
void UART_init();														// Initialisiert die Uart-Schnittstellen

void Uart_Transmit_IT_PC(char *data);									// Sende Daten über UART an PC (UART 0)

void tx_completed();													// Übertragung abgeschlossen (Kurzes Warten)
void (*ptr_tx_completed_0)(void);										// UART0-Pointer auf Übertragung abgeschlossen
/******************************************************************************************************************************/
#endif /* UART_H_ */