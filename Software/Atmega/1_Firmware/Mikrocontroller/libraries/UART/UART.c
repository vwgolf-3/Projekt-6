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

    RB_init(&rb_rx_Display);                                    // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART1

    RB_init(&rb_tx_ESP);                                        // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART2
    RB_init(&rb_rx_ESP);                                        // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART2

    RB_init(&rb_tx_RFID);                                       // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART3
    RB_init(&rb_rx_RFID);                                       // Initialisiere Ring-Buffer (head = 0, tail = 0) TX UART3
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    Uart_EnableRxIT_0();                                        // Enable RX-Interrupt: Receive Complete UART 0

    Uart_EnableRxIT_1();                                        // Enable RX-Interrupt: Receive Complete UART 1

    Uart_EnableRxIT_2();                                        // Enable RX-Interrupt: Receive Complete UART 2

    Uart_EnableRxIT_3();                                        // Enable RX-Interrupt: Receive Complete UART 3
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    sei();                                                      // Enable globale Interrupts
    /******************************************************************************************************************************/


    /******************************************************************************************************************************/
    ptr_tx_completed_0=tx_completed;                            // Pointer tx Completed UART0 auf Funktion (Kurz warten) setzen
    ptr_tx_completed_1=tx_completed;                            // Pointer tx Completed UART1 auf Funktion (Kurz warten) setzen
    ptr_tx_completed_2=tx_completed;                            // Pointer tx Completed UART2 auf Funktion (Kurz warten) setzen
    ptr_tx_completed_3=tx_completed;                            // Pointer tx Completed UART3 auf Funktion (Kurz warten) setzen
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

void Uart_Transmit_IT_Display(char *data)
{
    /*
        - Solange sich daten im Pointer befinden:
        - Warten bis die Übertragung des vorherigen Bytes fertig ist
        - Byte in UART-Senderegister schreiben
        - Auf nächstes Byte pointen
    */
    int i = 0;
    while (*(data + i) !='\0')
    {
        while (!(UCSR1A & (1<<UDRE1)));
        UDR1 = *(data+i);
        i++;
    }
}

void Uart_Transmit_IT_ESP(char *data)
{
    /*
        - Ermittle Länge des Strings
        - Schreibe n Bytes in den Buffer für das ESP
        - Enable Interrupt wenn Datenregister leer ist

        PROBLEM: Buffer overflow wenn lange Strings gesendet werden.
    */
    uint8_t nbytes = strlen((const char *)data);
    RB_write(&rb_tx_ESP, data, nbytes);
    Uart_EnableTransmitIT_2();
}

void Uart_Transmit_IT_RFID(char *data)
{
    /*
        - Ermittle Länge des Strings
        - Schreibe n Bytes in den Buffer für RFID
        - Enable Interrupt wenn Datenregister leer ist

        PROBLEM: Buffer overflow wenn lange Strings gesendet werden.
    */
    uint8_t nbytes = strlen((const char *)data);
    RB_write(&rb_tx_RFID, data, nbytes);
    Uart_EnableTransmitIT_3();
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

ISR(USART1_RX_vect)
{
    /*
        - Wird ein Empfangs-Interrupt seitens Display ausgelöst, wird das empfangene Byte in den Display-Buffer geschrieben
    */
    char ch = UDR1;
    RB_writeByte(&rb_rx_Display,ch);
}

ISR(USART2_UDRE_vect)
{
    /*
        - Befinden sich Daten im Buffer, wird das nächste Byte aus dem Buffer gesendet
        - Ansonsten wird das Interrupt deaktiviert und zwei Schritte gewartet
    */
    if (RB_length(&rb_tx_ESP) > 0)
    {
        UDR2 = RB_readByte(&rb_tx_ESP);
    }
    else
    {
        Uart_DisableTransmitIT_2();
        if(ptr_tx_completed_2 != 0)
            ptr_tx_completed_2();
    }
}

ISR(USART2_RX_vect)
{
    /*
        - Wird ein Empfangs-Interrupt seitens ESP ausgelöst, wird das empfangene Byte in den ESP-Buffer geschrieben
    */
    char ch = UDR2;
    RB_writeByte(&rb_rx_ESP,ch);
}

ISR(USART3_UDRE_vect)
{
    /*
        - Befinden sich Daten im Buffer, wird das nächste Byte aus dem Buffer gesendet
        - Ansonsten wird das Interrupt deaktiviert und zwei Schritte gewartet
    */
    if (RB_length(&rb_tx_RFID) > 0)
    {
        UDR3 = RB_readByte(&rb_tx_RFID);
    }
    else
    {
        Uart_DisableTransmitIT_3();
        if(ptr_tx_completed_3 != 0)
            ptr_tx_completed_3();
    }
}

ISR(USART3_RX_vect)
{
    /*
        - Wird ein Empfangs-Interrupt seitens RFID ausgelöst, wird das empfangene Byte in den RFID-Buffer geschrieben
    */
    char ch = UDR3;
    RB_writeByte(&rb_rx_RFID,ch);
}

// Funktionen, welche in der SD- und FAT-Library verwendet werden. Diese wurden so umgeschrieben, dass sie an die
// Initialisierungen angepasst sind. Es wurde hauptsächlich auf die Funktion geachtet.

//**************************************************
//Function to receive a single byte
//*************************************************
unsigned char receiveByte( void )
{
    unsigned char data;

    while(RB_length(&rb_rx_PC)==0);     // Wait for incomming data

    data = RB_readByte(&rb_rx_PC);

    return(data);
}

//***************************************************
//Function to transmit a single byte
//***************************************************
void transmitByte( unsigned char data )
{
    while ( !(UCSR0A & (1<<UDRE0)) )
        ;                           /* Wait for empty transmit buffer */
    UDR0 = data;                    /* Start transmition */
}

//***************************************************
//Function to transmit a string in RAM
//***************************************************
void transmitString(unsigned char* string)
{
    while (*string)
        transmitByte(*string++);
}

//************ END ***** www.dharmanitech.com *******
