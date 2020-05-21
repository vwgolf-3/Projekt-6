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
#include "libraries/SD-Karte/sdcard.h"
#include "libraries/SD-Karte/sdprint.h"

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
	zutaten_init();
	cocktails_init();
	init_Getraenke_func();
	
	
	
	
    // array to hold responses
    uint8_t res[5], buf[512], token;
    uint32_t addr = 0x00000000;

    // initialize sd card
    if(SD_init() != SD_SUCCESS)
    {
	    Uart_Transmit_IT_PC("Error initializaing SD CARD\r\n");
    }
    else
    {
	    Uart_Transmit_IT_PC("SD Card initialized\r\n");

	    // read sector 0
	    Uart_Transmit_IT_PC("\r\nReading sector: 0x");
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 24));
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 16));
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 8));
	    Uart_Transmit_IT_PC((uint8_t)addr);
	    res[0] = SD_readSingleBlock(addr, buf, &token);
	    Uart_Transmit_IT_PC("\r\nResponse:\r\n");
	    SD_printR1(res[0]);

	    // if no error, print buffer
	    if((res[0] == 0x00) && (token == SD_START_TOKEN))
	    SD_printBuf(buf);
	    // else if error token received, print
	    else if(!(token & 0xF0))
	    {
		    Uart_Transmit_IT_PC("Error token:\r\n");
		    SD_printDataErrToken(token);
	    }

	    // update address to 0x00000100
	    addr = 0x00000100;

	    // fill buffer with 0x55
	    for(uint16_t i = 0; i < 512; i++) buf[i] = 0x55;

	    Uart_Transmit_IT_PC("Writing 0x55 to sector: 0x");
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 24));
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 16));
	    Uart_Transmit_IT_PC((uint8_t)(addr >> 8));
	    Uart_Transmit_IT_PC((uint8_t)addr);

	    // write data to sector
	    res[0] = SD_writeSingleBlock(addr, buf, &token);

	    Uart_Transmit_IT_PC("\r\nResponse:\r\n");
	    SD_printR1(res[0]);

	    // if no errors writing
	    if(res[0] == 0x00)
	    {
		    if(token == SD_DATA_ACCEPTED)
		    Uart_Transmit_IT_PC("Write successful\r\n");
	    }
    }

	
	// Mainroutine
	while (1)
	{																		// Check Communication MFRC522		check_Communication_Input_MFRC522();		// Check Communication UART		check_Communication_Input_UART();

		//Testloop Blink LED
//   		heartbeat_LED();
_delay_ms(10);
	}
}
