/*
 * UART.h
 *
 * Created: 01.12.2019 14:27:08
 *  Author: kimsc
 */


#ifndef UART_H_
#define UART_H_

/******************************************************************************************************************************/
#include "../RingBuffer/ring_buffer.h"                  // Wird benötigt für den Ring-Buffer (z.B RB_init(), RB_readByte, ...)
#include <avr/interrupt.h>                              // Wird benötigt für UART-Interrupts (z.B ISR(USART0_RX_vect), ...)
#include <string.h>                                     // Wird benötigt für Stringoperationen (z.B strcpy(), strcat(), ...)
#include <avr/io.h>                                     // Wird benötigt für AVR-Registernamen (z.B F_CPU, UCSRnB, UDRIEn, ...)
/******************************************************************************************************************************/


/******************************************************************************************************************************/
#define CHAR 0                                                          // Define für SD-Karten-Library
#define INT  1                                                          // Define für SD-Karten-Library
#define LONG 2                                                          // Define für SD-Karten-Library
/******************************************************************************************************************************/


/******************************************************************************************************************************/
#define     Uart_EnableTransmitIT_0()       UCSR0B |= (1<<UDRIE0)       // Enable TX-Interrupt: Data Register empty UART 0
#define     Uart_DisableTransmitIT_0()  UCSR0B &= ~(1<<UDRIE0)          // Disable TX-Interrupt: Data Register empty UART 0
#define     Uart_EnableTransmitIT_1()       UCSR1B |= (1<<UDRIE1)       // Enable TX-Interrupt: Data Register empty UART 1
#define     Uart_DisableTransmitIT_1()  UCSR1B &= ~(1<<UDRIE1)          // Disable TX-Interrupt: Data Register empty UART 1
#define     Uart_EnableTransmitIT_2()       UCSR2B |= (1<<UDRIE2)       // Enable TX-Interrupt: Data Register empty UART 2
#define     Uart_DisableTransmitIT_2()  UCSR2B &= ~(1<<UDRIE2)          // Disable TX-Interrupt: Data Register empty UART 2
#define     Uart_EnableTransmitIT_3()       UCSR3B |= (1<<UDRIE3)       // Enable TX-Interrupt: Data Register empty UART 3
#define     Uart_DisableTransmitIT_3()  UCSR3B &= ~(1<<UDRIE3)          // Disable TX-Interrupt: Data Register empty UART 3

#define     Uart_EnableRxIT_0()     UCSR0B |= (1<<RXCIE0)               // Enable RX-Interrupt: Receive Complete UART 0
#define     Uart_DisableRxIT_0()        UCSR0B &= ~(1<<RXCIE0)          // Disable RX-Interrupt: Receive Complete UART 0
#define     Uart_EnableRxIT_1()     UCSR1B |= (1<<RXCIE1)               // Enable RX-Interrupt: Receive Complete UART 1
#define     Uart_DisableRxIT_1()        UCSR1B &= ~(1<<RXCIE1)          // Disable RX-Interrupt: Receive Complete UART 1
#define     Uart_EnableRxIT_2()     UCSR2B |= (1<<RXCIE2)               // Enable RX-Interrupt: Receive Complete UART 2
#define     Uart_DisableRxIT_2()        UCSR2B &= ~(1<<RXCIE2)          // Disable RX-Interrupt: Receive Complete UART 2
#define     Uart_EnableRxIT_3()     UCSR3B |= (1<<RXCIE3)               // Enable RX-Interrupt: Receive Complete UART 3
#define     Uart_DisableRxIT_3()        UCSR3B &= ~(1<<RXCIE3)          // Disable RX-Interrupt: Receive Complete UART 3
/******************************************************************************************************************************/


/******************************************************************************************************************************/
void UART_init();                                                       // Initialisiert die Uart-Schnittstellen

void Uart_Transmit_IT_PC(char *data);                                   // Sende Daten über UART an PC (UART 0)
void Uart_Transmit_IT_Display(char *data);                              // Sende Daten über UART an Display (UART 1)
void Uart_Transmit_IT_ESP(char *data);                                  // Sende Daten über UART an ESP (UART 2)
void Uart_Transmit_IT_RFID(char *data);                                 // Sende Daten über UART an RC522 (UART 3)

void tx_completed();                                                    // Übertragung abgeschlossen (Kurzes Warten)
void (*ptr_tx_completed_0)(void);                                       // UART0-Pointer auf Übertragung abgeschlossen
void (*ptr_tx_completed_1)(void);                                       // UART1-Pointer auf Übertragung abgeschlossen
void (*ptr_tx_completed_2)(void);                                       // UART2-Pointer auf Übertragung abgeschlossen
void (*ptr_tx_completed_3)(void);                                       // UART3-Pointer auf Übertragung abgeschlossen

unsigned char receiveByte(void);                                        // Byte über UART empfangen und zurückgeben (SD)
void transmitByte(unsigned char);                                       // Byte über UART senden (FAT/SD)
void transmitString(unsigned char*);                                    // String über UART senden (FAT)
/******************************************************************************************************************************/
#define CHAR 0
#define INT  1
#define LONG 2

#define TX_NEWLINE {transmitByte(0x0d); transmitByte(0x0a);}

unsigned char receiveByte(void);
void transmitByte(unsigned char);
void transmitString_F(char*);
void transmitString(unsigned char*);
void transmitHex( unsigned char dataType, unsigned long data );
#endif /* UART_H_ */