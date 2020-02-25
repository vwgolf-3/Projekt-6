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
#include <util/setbaud.h>
#include <string.h>
#include <stdlib.h>

// Einbinden der eigenen Bibliotheken
#include "libraries/RingBuffer/ring_buffer.h"
#include "libraries/UART/UART.h"
#include "libraries/SPI/SPI.h"
#include "libraries/TMC4671/TMC4671.h"
#include "libraries/Nextion_Display/Nextion_Display.h"
#include "Main_Func/Main_Func.h"

#include "libraries/Nextion_Display/nextion/Display_Nextion.h"
#include "libraries/Nextion_Display/util/Display_Utilities.h"

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
	
    CreateNexObject(button, buttonPageID, buttonID, "b1");
    CreateNexObject(slider, sliderPageID, sliderID, "MySlider");

    nexInit();

    NexSlider_getValue(&slider, &value);
    NexSlider_setValue(&slider, value + 20);

    NexTouch_attachPop(&button, buttonCallback, 0);
    NexTouch_attachPop(&slider, sliderCallback, 0);
	
// Mainroutine
	while (1)
	{
		        nexLoop(nex_listen_list);
		        _delay_ms(50);						
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

		//Testloop Blink LED
//  	heartbeat_LED();
	}
}

void buttonCallback(void *ptr)
{
	TOGGLE_LED();
}

void sliderCallback(void *ptr)
{
	TOGGLE_LED();
}