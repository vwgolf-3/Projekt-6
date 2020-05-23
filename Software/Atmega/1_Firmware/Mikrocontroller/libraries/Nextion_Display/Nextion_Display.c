/*
 * Nextion_Display.c
 *
 * Created: 02.01.2020 18:13:59
 *  Author: kimsc
 */ 

#include "Nextion_Display.h"

void nextion_change_page(char page)
{
	char * pge = "page ";
 	char buff[3] = {0};
	itoa((page-1),(char *)buff,10);
	Uart_Transmit_IT_Display(pge);
	Uart_Transmit_IT_Display((char *)buff);

	if (DEBUG_DISPLAY)
	{
		Uart_Transmit_IT_PC(pge);
		Uart_Transmit_IT_PC((char *)buff);
	}
	
	endConversation();
}

void nextion_setText(char * object, char * text)
{
	char * txt = ".txt=";
	char * slash = "\"";
	Uart_Transmit_IT_Display(object);
	Uart_Transmit_IT_Display(txt);
	Uart_Transmit_IT_Display(slash);
	Uart_Transmit_IT_Display(text);
	Uart_Transmit_IT_Display(slash);

	
	if (DEBUG_DISPLAY)
	{
		Uart_Transmit_IT_PC(object);
		Uart_Transmit_IT_PC(txt);
		Uart_Transmit_IT_PC(slash);
		Uart_Transmit_IT_PC(( char *)text);
		Uart_Transmit_IT_PC(slash);
	}
	
	endConversation();
}


void nextion_setValue( char * object,  char * value)
{
	 char * val = "val=";
	Uart_Transmit_IT_Display(object);
	Uart_Transmit_IT_Display(val);
	Uart_Transmit_IT_Display(value);

	if(DEBUG_DISPLAY)
	{
		Uart_Transmit_IT_PC(object);
		Uart_Transmit_IT_PC(val);
		Uart_Transmit_IT_PC(value);
	}
	endConversation();
}

void nextion_setPicture( char * x,  char * y,  char * picture)
{
	 char * pic = "pic ";
	 char * komma = ",";
	Uart_Transmit_IT_Display(pic);
	Uart_Transmit_IT_Display(x);
	Uart_Transmit_IT_Display(komma);
	Uart_Transmit_IT_Display(y);
	Uart_Transmit_IT_Display(komma);
	Uart_Transmit_IT_Display(picture);

	if(DEBUG_DISPLAY)
	{	
		Uart_Transmit_IT_PC((char *)pic);
		Uart_Transmit_IT_PC((char *)x);
		Uart_Transmit_IT_PC((char *)komma);
		Uart_Transmit_IT_PC((char *)y);
		Uart_Transmit_IT_PC((char *)komma);
		Uart_Transmit_IT_PC((char *)picture);
	}
		endConversation();
}


void endConversation(void)
{
	unsigned char end [4]= {255,255,255,'\0'};
	Uart_Transmit_IT_Display(( char *)end);
	
	if (DEBUG_DISPLAY)
	{
		Uart_Transmit_IT_PC((char *)end);
		Uart_Transmit_IT_PC("\r\n");
	}
}