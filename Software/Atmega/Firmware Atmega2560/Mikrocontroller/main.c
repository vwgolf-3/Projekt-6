/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einfügen der Standardbibliotheken
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Einbinden der eigenen Bibliotheken
#include "pin_defs.h"

#include "main_variables.h"

#include "Main_Func/Main_Func.h"
#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"
#include "libraries/TMC4671/TMC4671.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/RC522/mfrc522.h"

#include "libraries/SD-Karte/SD_routines.h"
#include "libraries/SD-Karte/FAT32.h"



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

	unsigned char option, error, data, FAT32_active;
	unsigned int i;
	unsigned char fileName[13];

	_delay_ms(100);  //delay for VCC stabilization

	PORTD |= 0x04; //switching ON the LED (for testing purpose only)

	TX_NEWLINE;
	TX_NEWLINE;
	transmitString_F ((char*)PSTR("*********************************************"));
	TX_NEWLINE;
	transmitString_F ((char*)PSTR("    Dharmani's microSD Card Testing..  "));
	TX_NEWLINE;
	transmitString_F ((char*)PSTR("*********************************************"));
	TX_NEWLINE;

	cardType = 0;

	for (i=0; i<10; i++)
	{
		error = SD_init();
		if(!error) break;
	}

	if(error)
	{
		if(error == 1) transmitString_F((char*)PSTR("SD card not detected.."));
		if(error == 2) transmitString_F((char*)PSTR("Card Initialization failed.."));

// 		while(1);  //wait here forever if error in SD init
	}else{
		
	switch (cardType)
	{
		case 1:transmitString_F((char*)PSTR("Standard Capacity Card (Ver 1.x) Detected!"));
		break;
		case 2:transmitString_F((char*)PSTR("High Capacity Card Detected!"));
		break;
		case 3:transmitString_F((char*)PSTR("Standard Capacity Card (Ver 2.x) Detected!"));
		break;
		default:transmitString_F((char*)PSTR("Unknown SD Card Detected!"));
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
		transmitString_F ((char*)PSTR("FAT32 not found!\r\n"));  //FAT32 incompatible drive
		FAT32_active = 0;
	}
			findFiles(GET_LIST,0);
			TX_NEWLINE

	readFile( READ, (unsigned char *)"hoi.txt");
	
	Uart_Transmit_IT_PC("\r\n");
	Uart_Transmit_IT_PC("\r\n");
	Uart_Transmit_IT_PC((char *)buffer);

	// Mainroutine
	while (1)
	{		// Check Communication MFRC522// 		check_Communication_Input_MFRC522();
		// Check Communication UART		check_Communication_Input_UART();

		//Testloop Blink LED
  	heartbeat_LED();
// 		_delay_ms(10);
	}
	return 0;
}