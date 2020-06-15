/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einbinden der eigenen Bibliotheken
#include "utils/pin_defs.h"
#include "utils/main_variables.h"
#include "libraries/Main_functions/Main_Func.h"

#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"

#include "libraries/TMC4671/TMC4671.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/RC522/mfrc522.h"

// MainLoop
int main(void)
{
	// Gate Treiber disable (active high)
 	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;

	Grossschreib = 1;
//Initialisierungen
	IO_init();
	SPI_init();
	UART_init();
	SD_startup();
// 	initTMC6200();
// 	TMC4671_init();
// 	initTMC4671_Openloop();
// 	mfrc522_init();

	zutaten_init();
	cocktails_init();
	init_Getraenke_func();
		
// Mainroutine
	while (1)
	{// 		check_Communication_Input_MFRC522();
		check_Communication_Input_UART();
  		heartbeat_LED();
	}
	return 0;
}