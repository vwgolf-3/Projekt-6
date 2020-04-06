/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einfügen der Standardbibliotheken
#include <avr/io.h>
// #include <util/delay.h>
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

#include "libraries/Nextion_Display/nextion/Display_Nextion.h"
#include "libraries/Nextion_Display/util/Display_Utilities.h"
#include "libraries/Getraenk/Getraenk.h"

// Übergreifende SPI-Defines
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

void sliderCallback(void *ptr);

void buttonCallback(void *ptr);

struct NexObject button, slider;

unsigned long value;

struct NexObject *nex_listen_list[] = {
 	&button,
 	&slider
};

#define buttonPageID 0xFF
#define sliderPageID 0
#define buttonID 0xB1
#define sliderID 2


// MainLoop
int main(void)
{
	
//Initialisierungen
	IO_init();
	TIMER_init();
	SPI_init();
	UART_init();
	TMC4671_init();
	mfrc522_init();
	cocktails_init();		
	// Implemetierung MFRC522
	
	unsigned char * ch0;
	
	//check version of the reader
	uint8_t str[MAX_LEN];
	
	char byte;
	byte = mfrc522_read(VersionReg);
	
	if(byte == 0x92)
	{
		ch0 = (unsigned char *)"MIFARE RC522v2 \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch0 = (unsigned char *)"Detected \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
	}
	else if(byte == 0x91 || byte==0x90)
	{
		ch0 = (unsigned char *)"MIFARE RC522v1 \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		ch0 = (unsigned char *)"Detected \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
	}
	else
	{
		ch0 = (unsigned char *)"No reader found \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
	}
	
	
	// Mainroutine
	while (1)
	{
		
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
			Uart_Transmit_IT_PC((unsigned char *)str,(unsigned char)strlen((const char *)str));
			ch0 = (unsigned char *)" :Vorher\r\n";
			Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
			
			
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
		Uart_Transmit_IT_PC((unsigned char *)str,(unsigned char)strlen((const char *)str));
		ch0 = (unsigned char *)" : Nachher \r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		}
		else
		{
// 			ch0 = (unsigned char *)" Error \r\n";
// 			Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		}
						// Check Communication		
		if (check_Communication_Input_UART_0())				// Check UART_0 (USB), ob vollständige Übertragung stattgefunden hat (Ende = "\r")
		{
			proceed_Communication_Input_UART_0();				// Vollständige Übertragung des USB verarbeiten
		}
		
		if (check_Communication_Input_UART_1())				// Check UART_1 (Nextion-Display), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_INPUT_UART_1();				// Vollständige Übertragung des Displays verarbeiten
		}

		if (check_Communication_Input_UART_2())				// Check UART_2 (ESP), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_Input_UART_2();				// Vollständige Übertragung des ESP's verarbeiten
		}

		if (check_Communication_Input_UART_3())				// Check UART_3 (RFID), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
		{
			proceed_Communication_Input_UART_3();				// Vollständige Übertragung des ESP's verarbeiten
		}


		//Testloop Blink LED
  		heartbeat_LED();
	}
}

