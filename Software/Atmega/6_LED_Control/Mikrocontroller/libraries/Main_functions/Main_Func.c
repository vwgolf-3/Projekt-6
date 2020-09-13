/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */

#include "Main_Func.h"
#include "../Nextion_Display/Nextion_Display.h"

//Init_IO

void IO_init(void)
{
    LED_DDR = LED_OUTPUT_MASK;
	process = 0;
}

void interfaces_init(void)
{
// Initialisierungen Interfaces
    IO_init();                                              // Ein-/Ausgangspins initialisieren
    UART_init();                                            // UART-Schnittstelle initialisieren
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
		process = 1;
	}
	else if (INPUT_UART_0[0]=='1')
	{
		process = 2;
	}
}

void check_Communication_Input_UART(void)
{
    if (check_Communication_Input_UART_0())             // Check UART_0 (USB), ob vollständige Übertragung stattgefunden hat (Ende = "\r")
    {
        proceed_Communication_Input_UART_0();               // Vollständige Übertragung des USB verarbeiten
    }
}