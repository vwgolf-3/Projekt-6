/*
 * Motor.c
 *
 * Created: 15.07.2020 20:34:28
 * Author : kimsc
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include "pin_defs.h"
#include "main_variables.h"							// "Global" includbare Variabeln deklarieren
#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"
#include "libraries/Main_functions/Main_Func.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/TMC4671/TMC4671.h"

int main(void)
{
	// Gate Treiber disable (active high)
// 	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;						// Disable TMC6200 (Active High)
	
	IO_init();												// Ein-/Ausgangspins initialisieren
	SPI_init();												// SPI-Schnittstelle initialisieren
	UART_init();											// UART-Schnittstelle initialisieren
// 	initTMC6200();											// Gate-Treiber initialisieren
	TMC4671_init();											// FOC-Treiber initialisieren

    /* Replace with your application code */
    while (1) 
    {
		Uart_Transmit_IT_PC("Hallo\r");
		check_Communication_Input_UART();
// 		read_registers_TMC6200();
//  		read_registers_TMC4671();
		_delay_ms(2000);
    }
}