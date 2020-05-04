/*
 * UART.h
 *
 * Created: 01.12.2019 14:27:08
 *  Author: kimsc
 */ 


#ifndef UART_H_
#define UART_H_

#include "../RingBuffer/ring_buffer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>


#define BAUD9600 9600
#define BRC9600 ((F_CPU/16/BAUD9600) -1)

#define BAUD115200 115200
#define BRC115200 ((F_CPU/16/BAUD115200) -1)

#define BAUD256000 256000
#define BRC256000 ((F_CPU/16/BAUD256000) -1)

#define		Uart_EnableTransmitIT_0()		UCSR0B |= (1<<UDRIE0)
#define		Uart_DisableTransmitIT_0()	UCSR0B &= ~(1<<UDRIE0)

#define		Uart_EnableTransmitIT_1()		UCSR1B |= (1<<UDRIE1)
#define		Uart_DisableTransmitIT_1()	UCSR1B &= ~(1<<UDRIE1)

#define		Uart_EnableTransmitIT_2()		UCSR2B |= (1<<UDRIE2)
#define		Uart_DisableTransmitIT_2()	UCSR2B &= ~(1<<UDRIE2)

#define		Uart_EnableTransmitIT_3()		UCSR3B |= (1<<UDRIE3)
#define		Uart_DisableTransmitIT_3()	UCSR3B &= ~(1<<UDRIE3)

#define		Uart_EnableRxIT_0()		UCSR0B |= (1<<RXCIE0)
#define		Uart_DisableRxIT_0()		UCSR0B &= ~(1<<RXCIE0)

#define		Uart_EnableRxIT_1()		UCSR1B |= (1<<RXCIE1)
#define		Uart_DisableRxIT_1()		UCSR1B &= ~(1<<RXCIE1)

#define		Uart_EnableRxIT_2()		UCSR2B |= (1<<RXCIE2)
#define		Uart_DisableRxIT_2()		UCSR2B &= ~(1<<RXCIE2)

#define		Uart_EnableRxIT_3()		UCSR3B |= (1<<RXCIE3)
#define		Uart_DisableRxIT_3()		UCSR3B &= ~(1<<RXCIE3)

extern ring_buffer_t rb_tx_PC;
extern ring_buffer_t rb_rx_PC;

extern ring_buffer_t rb_tx_Display;
extern ring_buffer_t rb_rx_Display;

extern ring_buffer_t rb_tx_ESP;
extern ring_buffer_t rb_rx_ESP;

extern ring_buffer_t rb_tx_RFID;
extern ring_buffer_t rb_rx_RFID;

void UART_init();

void Uart_Transmit_IT_PC(uint8_t *data);

void Uart_Transmit_IT_Display(uint8_t *data, uint8_t nbytes);

void Uart_Transmit_IT_ESP(uint8_t *data, uint8_t nbytes);

void Uart_Transmit_IT_RFID(uint8_t *data, uint8_t nbytes);

void tx_completed();

#endif /* UART_H_ */