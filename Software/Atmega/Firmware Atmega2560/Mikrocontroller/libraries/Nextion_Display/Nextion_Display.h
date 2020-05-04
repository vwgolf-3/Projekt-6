/*
 * Nextion_Display.h
 *
 * Created: 02.01.2020 18:14:22
 *  Author: kimsc
 */ 


#ifndef NEXTION_DISPLAY_H_
#define NEXTION_DISPLAY_H_

#include "../../libraries/UART/UART.h"
#include "../../libraries/RingBuffer/ring_buffer.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

void endConversation(char UART_PORT);
void nextion_setText(unsigned char * object, unsigned char * text, char UART_PORT);
void nextion_change_page(unsigned char * page);
void nextion_setValue(unsigned char * object, unsigned char * text, char UART_PORT);
void nextion_setPicture(unsigned char * x, unsigned char * y, unsigned char * picture, char UART_PORT);


#endif /* NEXTION_DISPLAY_H_ */