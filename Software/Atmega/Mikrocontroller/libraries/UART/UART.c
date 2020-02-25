/*
 * UART.c
 *
 * Created: 01.12.2019 14:29:56
 *  Author: kimsc
 */ 
#include "UART.h"

void (*ptr_tx_completed_0)(void);
void (*ptr_tx_completed_1)(void);
void (*ptr_tx_completed_2)(void);

void UART_init()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);	
	
	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
	
	UBRR2H = UBRRH_VALUE;
	UBRR2L = UBRRL_VALUE;
	UCSR2B = (1<<RXEN2)|(1<<TXEN2)|(1<<RXCIE2);
	UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
	
	RB_init(&rb_tx_PC);
	RB_init(&rb_rx_PC);
	
	RB_init(&rb_tx_Display);
	RB_init(&rb_rx_Display);
	
	RB_init(&rb_tx_ESP);
	RB_init(&rb_rx_ESP);
	
	Uart_EnableRxIT_0();
	
	Uart_EnableRxIT_1();

	Uart_EnableRxIT_2();

	sei();
	
	ptr_tx_completed_0=tx_completed;
	ptr_tx_completed_1=tx_completed;
	ptr_tx_completed_2=tx_completed;
}

void Uart_Transmit_IT_PC(unsigned char *data, unsigned char nbytes )
{
	RB_write(&rb_tx_PC, data, nbytes);
	Uart_EnableTransmitIT_0();
}

void Uart_Transmit_IT_Display(unsigned char *data, unsigned char nbytes )
{
	RB_write(&rb_tx_Display, data, nbytes);
	Uart_EnableTransmitIT_1();
}

void Uart_Transmit_IT_ESP(unsigned char *data, unsigned char nbytes )
{
	RB_write(&rb_tx_ESP, data, nbytes);
	Uart_EnableTransmitIT_2();
}

void tx_completed(){	asm("nop");	asm("nop");}

ISR(USART0_UDRE_vect)
{
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
	RB_writeByte(&rb_rx_PC,UDR0);
}

ISR(USART1_UDRE_vect)
{
	if (RB_length(&rb_tx_Display) > 0)
	{
		UDR1 = RB_readByte(&rb_tx_Display);
	}
	else
	{
		Uart_DisableTransmitIT_1();
		if(ptr_tx_completed_1 != 0)
		ptr_tx_completed_1();
	}
}

ISR(USART1_RX_vect)
{
	char ch = UDR1;
	RB_writeByte(&rb_rx_Display,ch);
}

ISR(USART2_UDRE_vect)
{
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
	char ch = UDR2;
	RB_writeByte(&rb_rx_ESP,ch);
}