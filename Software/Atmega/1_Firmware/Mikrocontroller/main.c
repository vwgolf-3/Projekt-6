/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einfügen der Standardbibliotheken
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
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

// 	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;


//Initialisierungen
	IO_init();
	SPI_init();
	UART_init();
	heartbeat_LED();
// 	TMC4671_init();
// 	initTMC6200();
// 	initTMC4671_Openloop();
// 	mfrc522_init();
	zutaten_init();
	cocktails_init();
	init_Getraenke_func();

	cardType = 0;

	for (i=0; i<10; i++)
	{
		error = SD_init();
		if(!error) break;
	}

	if(error)
	{
		if(error == 1) Uart_Transmit_IT_PC((char*)("SD card not detected..\r"));
		if(error == 2) Uart_Transmit_IT_PC((char*)("Card Initialization failed..\r"));

// 		while(1);  //wait here forever if error in SD init
	}else{
		
	switch (cardType)
	{
		case 1:Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 1.x) Detected!\r"));
		break;
		case 2:Uart_Transmit_IT_PC(("High Capacity Card Detected!\r"));
		break;
		case 3:Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 2.x) Detected!\r"));
		break;
		default:Uart_Transmit_IT_PC(("Unknown SD Card Detected!\r"));
		break;
	}
	}

	SPI_HIGH_SPEED;	//SCK - 4 MHz
	_delay_ms(1);   //some delay


	FAT32_active = 1;
	error = getBootSectorData (); //read boot sector and keep necessary data in global variables
	if(error)
	{
		TX_NEWLINE;
		Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
		FAT32_active = 0;
	}
	findFiles(GET_LIST,0);
	TX_NEWLINE
	TX_NEWLINE

	// Mainroutine
	while (1)
	{		// Check Communication MFRC522// 		check_Communication_Input_MFRC522();
		// Check Communication UART	check_Communication_Input_UART();

		//Testloop Blink LED
  	heartbeat_LED();
// 		_delay_ms(10);
	}
	return 0;
}
