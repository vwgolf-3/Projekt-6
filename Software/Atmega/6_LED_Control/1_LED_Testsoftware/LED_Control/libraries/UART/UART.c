/*
 * UART.c
 *
 * Created: 01.12.2019 14:29:56
 *  Author: kimsc
 */
#include "UART.h"




void UART_init()
{

    /******************************************************************************************************************************/
#define BAUD9600 9600                                   // Define für Baudrate-Register
#define BRC9600 ((F_CPU/16/BAUD9600) -1)                // Define für Baudrate-Register

#define BAUD57600 57600                                   // Define für Baudrate-Register
#define BRC57600 ((F_CPU/16/BAUD57600) -1)                // Define für Baudrate-Register

#define BAUD38400 38400
#define BRC38400 ((F_CPU/16/BAUD38400) -1)

#define BAUD74880 74880
#define BRC74880 ((F_CPU/16/BAUD74880) -1)
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    UBRR0H = (BRC57600>>8);                                      // Baudrate Register1 (9600) UART0
    UBRR0L = (BRC57600);                                         // Baudrate Register2 (9600) UART0
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);                             // Enable RX und TX UART 0
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);                           // Übertragene Bits: 8 und parity disabled UART0

    UBRR1H = (BRC9600>>8);                                      // Baudrate Register1 (9600) UART1
    UBRR1L = BRC9600;                                           // Baudrate Register2 (9600) UART1
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);                             // Enable RX und TX UART 1
    UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);                           // Übertragene Bits: 8 und parity disabled UART1

    UBRR2H = (BRC74880>>8);                                     // Baudrate Register1 (9600) UART2
    UBRR2L = BRC74880;                                          // Baudrate Register2 (9600) UART2
    UCSR2B = (1<<RXEN2)|(1<<TXEN2);                             // Enable RX und TX UART 2
    UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);                           // Übertragene Bits: 8 und parity disabled UART2

    UBRR3H = (BRC9600>>8);                                      // Baudrate Register1 (9600) UART3
    UBRR3L = BRC9600;                                           // Baudrate Register2 (9600) UART3
    UCSR3B = (1<<RXEN3)|(1<<TXEN3);                             // Enable RX und TX UART 3
    UCSR3C = (1<<UCSZ30)|(1<<UCSZ31);                           // Übertragene Bits: 8 und parity disabled UART3
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    RB_init(&rb_tx_PC);                                         // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART0
    RB_init(&rb_rx_PC);                                         // Initialisiere Ring-Buffer (head = 0, tail = 0) RX UART0
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    Uart_EnableRxIT_0();                                        // Enable RX-Interrupt: Receive Complete UART 0
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    sei();                                                      // Enable globale Interrupts
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    ptr_tx_completed_0=tx_completed;                            // Pointer tx Completed UART0 auf Funktion (Kurz warten) setzen
    /******************************************************************************************************************************/

}

void Uart_Transmit_IT_PC(char *data)
{
    /*
        - Ermittle Länge des Strings
        - Schreibe n Bytes in den Buffer für PC
        - Enable Interrupt wenn Datenregister leer ist

        PROBLEM: Buffer overflow wenn lange Strings gesendet werden.
    */
    uint8_t nbytes = strlen((const char *)data);
    RB_write(&rb_tx_PC, data, nbytes);
    Uart_EnableTransmitIT_0();
}

void tx_completed()
{
    /*
        - Warte zwei Arbeitsschritte (Nulloperation) wenn Übertragung zu Ende
    */
    asm("nop");
    asm("nop");
}

ISR(USART0_UDRE_vect)
{
    /*
        - Befinden sich Daten im Buffer, wird das nächste Byte aus dem Buffer gesendet
        - Ansonsten wird das Interrupt deaktiviert und zwei Schritte gewartet
    */
    if (RB_length(&rb_tx_PC) > 0)
    {
        UDR0 = RB_readByte(&rb_tx_PC);
    }
    else
    {
        Uart_DisableTransmitIT_0();
        if(ptr_tx_completed_0 != 0)
            ptr_tx_completed_0();
    }
}

ISR(USART0_RX_vect)
{
    /*
        - Wird ein Empfangs-Interrupt seitens PC ausgelöst, wird das empfangene Byte in den PC-Buffer geschrieben
    */
    char ch = UDR0;
    RB_writeByte(&rb_rx_PC,ch);
}