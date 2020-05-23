/*
 * Display_Serial.c
 *
 * Created: 19.01.2020 20:48:45
 *  Author: kimsc
 */ 

#include "Display_Serial.h"
#include "../util/Display_Utilities.h"
#include "../../UART/UART.h"			// Benutzerspezifische Schnittstelle
#include <avr/interrupt.h>

void Serial_Init(long baudrate)
{
// 	UART_init();
}

unsigned char Serial_Write(unsigned char c)
{
	RB_writeByte(&rb_tx_ESP,c);
	return 1;
}

unsigned char Serial_Read()
{
	unsigned char ch = RB_readByte(&rb_rx_ESP);
	return ch;
}

unsigned char Serial_Available()
{
	return RB_length(&rb_rx_ESP);
}

unsigned char Serial_ReadBytes(char *buf, unsigned char len)
{
    unsigned char cnt = 0;
    if (len < RB_length(&rb_rx_ESP))
    {
// 	    ArrayCopy(buf, &rb_rx_ESP[&rb_rx_ESP->tail], len);
// 	    rb_rx_ESP.tail += len;
// 	    cnt = len;
    }
    else if (len == RB_length(&rb_rx_ESP))
    {
// 	    ArrayCopy(buf, &rb_rx_ESP[rb_rx_ESP.tail], len);
// 	    rb_rx_ESP.tail = 0;
// 	    rb_rx_ESP.head = 0;
// 	    cnt = len;
    }
    else
    {
// 	    ArrayCopy(buf, &rb_rx_ESP[rb_rx_ESP.tail], RB_length(&rb_rx_ESP));
// 	    cnt = RB_length(&rb_rx_ESP);
// 	    rb_rx_ESP->tail = 0;
// 	    rb_rx_ESP.head = 0;
    }
    return cnt;
}

void Serial_Print(unsigned char *txt)
{
// 	RB_write(&rb_tx_ESP,txt,strlen((const char *)txt));
}