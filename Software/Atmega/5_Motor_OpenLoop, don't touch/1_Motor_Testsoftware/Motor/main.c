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
	IO_init();												// Ein-/Ausgangspins initialisieren
	SPI_init();												// SPI-Schnittstelle initialisieren
	UART_init();											// UART-Schnittstelle initialisieren
	_delay_ms(5000);
	initTMC6200();											// Gate-Treiber initialisieren
	_delay_ms(5000);
	initTMC4671_Openloop();									// FOC-Treiber initialisieren

    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(5000);
		read_registers_TMC6200();
		_delay_ms(5000);
		read_registers_TMC4671();
    }
}