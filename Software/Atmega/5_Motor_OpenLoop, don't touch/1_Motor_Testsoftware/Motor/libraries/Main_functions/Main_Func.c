/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */ 

#include "Main_Func.h"

//Init_IO

void IO_init(void)
{
	LED_DDR = LED_OUTPUT_MASK;
	SPI_DDR = SPI_OUTPUT_MASK;
	SPI2_DDR = SPI2_OUTPUT_MASK;
	PUMPE_DDR = PUMPE_OUTPUT_MASK;
	PUMPE_DDR2 = PUMPE2_OUTPUT_MASK;
	PUMPE_DDR3 = PUMPE3_OUTPUT_MASK;
	RFID_DDR = RFID_OUTPUT_MASK;
	SOFTSPI_DDR = SOFTSPI_OUTPUT_MASK;
	FLUSS_DDR = 0b00000000;
	SOFTSPI_CLK_PORT |= SOFTSPI_CLK_BIT;
}

void heartbeat_LED(void)
{
	toggle_LED();
   		_delay_ms(1000);
}

void toggle_LED(void)
{
		LED_PORT = LED_PORT ^ (LEDR_BIT|LEDG_BIT|LEDB_BIT|LEDW_BIT);
}

char check_Communication_Input_UART_0(void)
{
	char ret = 0;
	// Check Buffer auf Einkommende Daten
	while(RB_length(&rb_rx_PC)>0)
	{
		unsigned char ch = RB_readByte(&rb_rx_PC);
		if (ch == 13)
		{
			INPUT_UART_0[cntr_UART_0] = 0;
			cntr_UART_0 = 0;
			cntr_End_UART_0 = 0;
			ret = 1;
		}
		else
		{
			INPUT_UART_0[cntr_UART_0]=ch;
			cntr_UART_0++;
			ret = 0;
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_0(void)
{
	char * ch = "Proceed UART 0: \n\r";
	Uart_Transmit_IT_PC(ch);
}


void check_Communication_Input_UART(void)
{
	if (check_Communication_Input_UART_0())				// Check UART_0 (USB), ob vollständige Übertragung stattgefunden hat (Ende = "\r")
	{
		proceed_Communication_Input_UART_0();				// Vollständige Übertragung des USB verarbeiten
	}
}