/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einf�gen der Standardbibliotheken
#include <avr/io.h>
#include <stdio.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>

#include "libraries/SPI/SPI_Defines.h"

// Einbinden der eigenen Bibliotheken
#include "libraries/RingBuffer/ring_buffer.h"
#include "libraries/UART/UART.h"
#include "libraries/SPI/SPI.h"
#include "libraries/TMC4671/TMC4671.h"
#include "libraries/Nextion_Display/Nextion_Display.h"
#include "libraries/RC522/mfrc522.h"
#include "Main_Func/Main_Func.h"

#include "libraries/Getraenk/Getraenk.h"

// �bergreifende SPI-Defines
#include "libraries/SPI/SPI_Defines.h"

//Variabeln UART_0
unsigned char cntr_UART_0 = 0;
unsigned char INPUT_UART_0[256];
char UART_recieved_finished_0 = 0;
char cntr_End_UART_0 = 0;

//Variabeln UART_1
unsigned char cntr_UART_1 = 0;
unsigned char INPUT_UART_1[256];
char UART_recieved_finished_1 = 0;
char cntr_End_UART_1 = 0;

//Variabeln UART_2
unsigned char cntr_UART_2 = 0;
unsigned char INPUT_UART_2[256];
char UART_recieved_finished_2 = 0;
char cntr_End_UART_2 = 0;

//Variabeln UART_3
unsigned char cntr_UART_3 = 0;
unsigned char INPUT_UART_3[256];
char UART_recieved_finished_3 = 0;
char cntr_End_UART_3 = 0;

//Variabeln SPI_0
unsigned char cntr_SPI_0 = 0;
unsigned char INPUT_SPI_0[256];
unsigned char OUTPUT_SPI_0[256];
int SPI_received_finished_0 = 0;
char cntr_End_SPI_0 = 0;

ring_buffer_t rb_tx_PC;
ring_buffer_t rb_rx_PC;

ring_buffer_t rb_tx_Display;
ring_buffer_t rb_rx_Display;

ring_buffer_t rb_tx_ESP;
ring_buffer_t rb_rx_ESP;

ring_buffer_t rb_tx_RFID;
ring_buffer_t rb_rx_RFID;

ring_buffer_t rb_SPI_r;
ring_buffer_t rb_SPI_w;


// MainLoop
int main(void)
{
	
//Initialisierungen
	IO_init();
	SPI_init();
	UART_init();
	TMC4671_init();
	mfrc522_init();
	cocktails_init();		
	_delay_ms(1000);
	test = 0;

	// Implemetierung MFRC522
		
	//check version of the reader
	uint8_t str[MAX_LEN];
	
	char byte;
	byte = mfrc522_read(VersionReg);
	
	if(byte == 0x92)
	{
		Uart_Transmit_IT_PC((uint8_t*)"MIFARE RC522v2 \r\n");
		Uart_Transmit_IT_PC((uint8_t*)"Detected \r\n");
		
	}
	else if(byte == 0x91 || byte==0x90)
	{
		Uart_Transmit_IT_PC((uint8_t*)"MIFARE RC522v1 \r\n");
		Uart_Transmit_IT_PC((uint8_t*)"Detected \r\n");
	}
	else
	{
		Uart_Transmit_IT_PC((uint8_t*)"No reader found \r\n");
	}
	
	
	// Mainroutine
	while (1)
	{
		while (test)
		{
			static uint8_t oldval=0;
			static uint32_t count=0;
			
			uint8_t newval = (FLUSS0_PIN & FLUSS0_BIT);
	
			if( !oldval && newval){
		
			if(count++ > 50){
				PUMPE0_PORT &= ~PUMPE0_BIT;
				count = 0;
				test = 0;
			}
		}
		oldval = newval;
	}
	
	
	

	
	// Check MFRC522
		
		byte = mfrc522_read(ComIEnReg);
		
// 		ch0 = (unsigned char *)byte;
// 		Uart_Transmit_IT_PC(ch0,1);
// 		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,(unsigned char)strlen((const char *)ch0));

		mfrc522_write(ComIEnReg,byte|0x20);

		byte = mfrc522_read(DivIEnReg);
			
// 		ch0 = (unsigned char *)byte;
// 		Uart_Transmit_IT_PC(ch0,1);
// 		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,(unsigned char)strlen((const char *)ch0));
			
		mfrc522_write(DivIEnReg,byte|0x80);
				
		byte = mfrc522_request(PICC_REQALL,str);
		
// 		ch0 = (unsigned char *) byte;
// 	 	Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
// 		ch0 = (unsigned char *)"\r\n";
// 	 	Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));

		if(byte == CARD_FOUND)
		{
			byte = mfrc522_get_card_serial(str);
			Uart_Transmit_IT_PC((unsigned char *)str);
			Uart_Transmit_IT_PC((uint8_t*)" :Vorher\r\n");
			
			
			if(str[0]!=1)
			{
				if (str[2]!=2)
				{
					unsigned char * ch0 = (unsigned char *) atoi((const char *)"12");
					unsigned char len = (unsigned char )strlen((const char *) ch0);
					unsigned char * chBack = 0;
					uint32_t * data_len_Back = 0;
					mfrc522_to_card(Transceive_CMD, ch0, len, chBack, data_len_Back);			
				}
				else if (str[2]!=3)
				{
					unsigned char * ch0 = (unsigned char *) atoi((const char *)"13");
					unsigned char len = (unsigned char )strlen((const char *) ch0);
					unsigned char * chBack = 0;
					uint32_t * data_len_Back = 0;
					mfrc522_to_card(Transceive_CMD, ch0, len, chBack, data_len_Back);
				}
			}
		byte = mfrc522_get_card_serial(str);
		Uart_Transmit_IT_PC((unsigned char *)str);
		Uart_Transmit_IT_PC((uint8_t*)" : Nachher \r\n");
		}
		else
		{
// 			ch0 = (unsigned char *)" Error \r\n";
// 			Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		}
		
		if (check_Communication_Input_UART_0())				// Check UART_0 (USB), ob vollst�ndige �bertragung stattgefunden hat (Ende = "\r")
		{
			proceed_Communication_Input_UART_0();				// Vollst�ndige �bertragung des USB verarbeiten
		}
		
		if (check_Communication_Input_UART_1())				// Check UART_1 (Nextion-Display), ob vollst�ndige �bertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_INPUT_UART_1();				// Vollst�ndige �bertragung des Displays verarbeiten
		}

		if (check_Communication_Input_UART_2())				// Check UART_2 (ESP), ob vollst�ndige �bertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_Input_UART_2();				// Vollst�ndige �bertragung des ESP's verarbeiten
		}

		if (check_Communication_Input_UART_3())				// Check UART_3 (RFID), ob vollst�ndige �bertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_Input_UART_3();				// Vollst�ndige �bertragung des ESP's verarbeiten
		}

		//Testloop Blink LED
  		heartbeat_LED();
	}
}