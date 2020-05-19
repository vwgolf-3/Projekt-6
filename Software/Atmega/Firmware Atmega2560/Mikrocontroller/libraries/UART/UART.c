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
void (*ptr_tx_completed_3)(void);

void UART_init()
{
	UBRR0H = (BRC9600 >> 8);
	UBRR0L = BRC9600;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);	
	
	UBRR1H = (BRC9600>>8);
	UBRR1L = BRC9600;
	UCSR1B = (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);
	UCSR1C = (1<<UCSZ10)|(1<<UCSZ11);
	
	UBRR2H = (BRC9600>>8);
	UBRR2L = BRC9600;
	UCSR2B = (1<<RXEN2)|(1<<TXEN2)|(1<<RXCIE2);
	UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
	
// 	UBRR3H = (BRC9600>>8);
// 	UBRR3L = BRC9600;
// 	UCSR3B = (1<<RXEN3)|(1<<TXEN3)|(1<<RXCIE3);
// 	UCSR3C = (1<<UCSZ30)|(1<<UCSZ31);
	
	RB_init(&rb_tx_PC);
	RB_init(&rb_rx_PC);
	
	RB_init(&rb_tx_Display);
	RB_init(&rb_rx_Display);
	
	RB_init(&rb_tx_ESP);
	RB_init(&rb_rx_ESP);
	
// 	RB_init(&rb_tx_RFID);
// 	RB_init(&rb_rx_RFID);
	
	Uart_EnableRxIT_0();
	
	Uart_EnableRxIT_1();

	Uart_EnableRxIT_2();

// 	Uart_EnableRxIT_3();

	sei();
	
	ptr_tx_completed_0=tx_completed;
	ptr_tx_completed_1=tx_completed;
	ptr_tx_completed_2=tx_completed;
// 	ptr_tx_completed_3=tx_completed;
}

void Uart_Transmit_IT_PC(char *data)
{
	uint8_t nbytes = strlen((const char *)data);
	RB_write(&rb_tx_PC, data, nbytes);
	Uart_EnableTransmitIT_0();
}

void Uart_Transmit_IT_Display(char *data)
{
	uint8_t nbytes = strlen((const char *)data);
	RB_write(&rb_tx_Display, data, nbytes);
	Uart_EnableTransmitIT_1();
}

void Uart_Transmit_IT_ESP(char *data)
{
	uint8_t nbytes = strlen((const char *)data);
	RB_write(&rb_tx_ESP, data, nbytes);
	Uart_EnableTransmitIT_2();
}

// void Uart_Transmit_IT_RFID(char *data)
// {
// 	uint8_t nbytes = strlen((const char *)data);
// 	RB_write(&rb_tx_RFID, data, nbytes);
// 	Uart_EnableTransmitIT_3();
// }

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
	char ch = UDR0;
	RB_writeByte(&rb_rx_PC,ch);
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

/*
ISR(USART3_UDRE_vect)
{
	if (RB_length(&rb_tx_RFID) > 0)
	{
		UDR2 = RB_readByte(&rb_tx_RFID);
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
	char ch = UDR3;
	RB_writeByte(&rb_rx_RFID,ch);
}*/