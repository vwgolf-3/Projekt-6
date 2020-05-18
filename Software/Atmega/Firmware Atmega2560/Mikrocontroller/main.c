/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einfügen der Standardbibliotheken
#include <avr/io.h>

// Einbinden der eigenen Bibliotheken
#include "pin_defs.h"

#include "main_variables.h"

#include "Main_Func/Main_Func.h"
#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"
#include "libraries/TMC4671/TMC4671.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/RC522/mfrc522.h"


// MainLoop
int main(void)
{

// 	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;


//Initialisierungen
	IO_init();
	SPI_init();
	UART_init();
	heartbeat_LED();
// 	TMC4671_init();
// 	initTMC6200();
// 	initTMC4671_Openloop();
	mfrc522_init();
	heartbeat_LED();
	cocktails_init();
	init_Getraenke_func();
	
	_delay_ms(2000);
	// Mainroutine
	while (1)
	{				// Check Communication MFRC522		check_Communication_Input_MFRC522();		// Check Communication UART		check_Communication_Input_UART();

		//Testloop Blink LED
  		heartbeat_LED();
	}
}
