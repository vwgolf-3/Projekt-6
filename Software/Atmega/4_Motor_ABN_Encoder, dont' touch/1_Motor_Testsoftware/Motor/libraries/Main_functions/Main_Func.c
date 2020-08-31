/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */ 

#include "Main_Func.h"
#include "./../TMC4671/TMC4671.h"

//Init_IO
// Function to convert hexadecimal to decimal
int hexadecimalToDecimal(char hexVal[])
{
	int len = strlen(hexVal);
	
	// Initializing base value to 1, i.e 16^0
	int base = 1;
	
	int dec_val = 0;
	
	// Extracting characters as digits from last character
	for (int i=len-1; i>=0; i--)
	{
		// if character lies in '0'-'9', converting
		// it to integral 0-9 by subtracting 48 from
		// ASCII value.
		if (hexVal[i]>='0' && hexVal[i]<='9')
		{
			dec_val += (hexVal[i] - 48)*base;
			
			// incrementing base by power
			base = base * 16;
		}
		
		// if character lies in 'A'-'F' , converting
		// it to integral 10 - 15 by subtracting 55
		// from ASCII value
		else if (hexVal[i]>='A' && hexVal[i]<='F')
		{
			dec_val += (hexVal[i] - 55)*base;
			
			// incrementing base by power
			base = base*16;
		}
	}
	
	return dec_val;
}

void my_itoa( int64_t z, char* buffer )
{
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