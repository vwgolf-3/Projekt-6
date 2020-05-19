/*
 * Nextion_Display.h
 *
 * Created: 02.01.2020 18:14:22
 *  Author: kimsc
 */ 


#ifndef NEXTION_DISPLAY_H_
#define NEXTION_DISPLAY_H_

#include <stdlib.h>

#include "../../libraries/UART/UART.h"

#define UART_PORT_PC 0
#define UART_PORT_DISPLAY 1
#define UART_PORT_ESP 2
#define UART_PORT_RFID 3

#define DEBUG_DISPLAY 0


void endConversation(void);
void nextion_setText(char * object, char * text);
void nextion_change_page(char page);
void nextion_setValue( char * object,  char * text);
void nextion_setPicture( char * x,  char * y,  char * picture);


#endif /* NEXTION_DISPLAY_H_ */