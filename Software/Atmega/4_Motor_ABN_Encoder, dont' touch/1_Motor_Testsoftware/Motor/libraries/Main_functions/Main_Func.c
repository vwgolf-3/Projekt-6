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
	else if (INPUT_UART_0[0]=='1')
	{
		uint32_t Position = 1000000;
		for (int i = 1 ; i <= 12 ; i++)
		{
			tmc4671_setAbsolutTargetPosition(0, i * Position);
			while(((tmc4671_getActualPosition(0) <= (i* Position-200))||(tmc4671_getActualPosition(0)>= (i*Position+200))))
			{
				read_Position_TMC4671();
			}
			
			Uart_Transmit_IT_PC("Position ");
			char buff[5] = {'\0'};
			itoa(i, (char *)buff, 10);
			Uart_Transmit_IT_PC((char *)buff);
			Uart_Transmit_IT_PC(" erreicht\r");
			_delay_ms(1000);
		}
		tmc4671_setAbsolutTargetPosition(0,0);
			while((tmc4671_getActualPosition(0) >= (200)))
			{
				read_Position_TMC4671();
			}
		Uart_Transmit_IT_PC("Ausgangspunkt erreicht.");
	}
	else if (INPUT_UART_0[0] == 0)
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

void my_itoa( int64_t z, char* buffer )
{
	// Reference to: https://www.mikrocontroller.net/attachment/highlight/305548

	int      i = 0;
	int      j;
	char     tmp;
	int64_t  u;    // In u bearbeiten wir den Absolutbetrag von z.
	char     sflag= 0;

	u= z;
	// ist die Zahl negativ?
	// gleich mal ein - hinterlassen und die Zahl positiv machen
	// die einzelnen Stellen der Zahl berechnen
	if (u< 0)
	{
		u= u*(-1);
		sflag= 1;
	}
	do
	{
		buffer[i++] = '0' + (u % 10);
		u /= 10;
	}
	while( u > 0 );
	if (sflag)  { buffer[i++]= '-'; }

	// den String in sich spiegeln
	for( j = 0; j < i / 2; ++j )
	{
		tmp = buffer[j];
		buffer[j] = buffer[i-j-1];
		buffer[i-j-1] = tmp;
	}

	buffer[i] = '\0';
}

void read_Position_TMC4671(void)
{
	// +/- alle 100ms Position abfragen und über Seiriellen Port ausgeben
	static uint8_t cntrr = 0;
	if (cntrr == 10)
	{
		cntrr = 0;
		int64_t val = tmc4671_getActualPosition(0);
		char testarray[100] = {'\0'};
		my_itoa(val, (char *)testarray);
		Uart_Transmit_IT_PC((char *)testarray);
		Uart_Transmit_IT_PC("\r");
	}
	cntrr++;
	_delay_ms(1);
}