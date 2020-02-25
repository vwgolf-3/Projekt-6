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
#include <util/setbaud.h>
#include <string.h>
#include <util/delay.h>

#define		Uart_EnableTransmitIT_0()		UCSR0B |= (1<<UDRIE0)
#define		Uart_DisableTransmitIT_0()	UCSR0B &= ~(1<<UDRIE0)

#define		Uart_EnableTransmitIT_1()		UCSR1B |= (1<<UDRIE1)
#define		Uart_DisableTransmitIT_1()	UCSR1B &= ~(1<<UDRIE1)

#define		Uart_EnableTransmitIT_2()		UCSR2B |= (1<<UDRIE2)
#define		Uart_DisableTransmitIT_2()	UCSR2B &= ~(1<<UDRIE2)

#define		Uart_EnableRxIT_0()		UCSR0B |= (1<<RXCIE0)
#define		Uart_DisableRxIT_0()		UCSR0B &= ~(1<<RXCIE0)

#define		Uart_EnableRxIT_1()		UCSR1B |= (1<<RXCIE1)
#define		Uart_DisableRxIT_1()		UCSR1B &= ~(1<<RXCIE1)

#define		Uart_EnableRxIT_2()		UCSR2B |= (1<<RXCIE2)
#define		Uart_DisableRxIT_2()		UCSR2B &= ~(1<<RXCIE2)

extern ring_buffer_t rb_tx_PC;
extern ring_buffer_t rb_rx_PC;

extern ring_buffer_t rb_tx_Display;
extern ring_buffer_t rb_rx_Display;

extern ring_buffer_t rb_tx_ESP;
extern ring_buffer_t rb_rx_ESP;

void UART_init();

void Uart_Transmit_IT_PC(unsigned char *data, unsigned char nbytes);

void Uart_Transmit_IT_Display(unsigned char *data, unsigned char nbytes);

void Uart_Transmit_IT_ESP(unsigned char *data, unsigned char nbytes);

void tx_completed();

#endif /* UART_H_ */