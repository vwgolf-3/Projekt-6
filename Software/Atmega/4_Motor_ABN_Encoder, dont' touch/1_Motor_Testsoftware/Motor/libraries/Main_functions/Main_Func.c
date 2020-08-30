/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */ 

#include "Main_Func.h"
#include "./../TMC4671/TMC4671.h"

//Init_IO

void IO_init(void)
{
	SPI_DDR = SPI_OUTPUT_MASK;
	SPI2_DDR = SPI2_OUTPUT_MASK;
	SOFTSPI_DDR = SOFTSPI_OUTPUT_MASK;
	SOFTSPI_CLK_PORT |= SOFTSPI_CLK_BIT;
	
	Position = 0;
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
	if (INPUT_UART_0[0]=='0')
	{
		tmc4671_setAbsolutTargetPosition(0,0);
		Position = 0;
	}
	else
	{
		Position += 10000000;
		tmc4671_setAbsolutTargetPosition(0,Position);
	}
}


void check_Communication_Input_UART(void)
{
	if (check_Communication_Input_UART_0())				// Check UART_0 (USB), ob vollständige Übertragung stattgefunden hat (Ende = "\r")
	{
		proceed_Communication_Input_UART_0();				// Vollständige Übertragung des USB verarbeiten
	}
}