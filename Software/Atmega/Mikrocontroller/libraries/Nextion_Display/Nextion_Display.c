/*
 * Nextion_Display.c
 *
 * Created: 02.01.2020 18:13:59
 *  Author: kimsc
 */ 

#include "Nextion_Display.h"

void nextion_change_page(unsigned char * page)
{
	unsigned char * ch1 = (unsigned char *) "page ";
	unsigned char * ch2 = page;

	Uart_Transmit_IT_Display(ch1,strlen((const char*)ch1));
	Uart_Transmit_IT_Display(ch2,strlen((const char*)ch2));
	endConversation(1);

	Uart_Transmit_IT_PC(ch1,strlen((const char*)ch1));
	Uart_Transmit_IT_PC(ch2,strlen((const char*)ch2));
	Uart_Transmit_IT_PC((unsigned char *)"\r\n",strlen((const char*)"\r\n"));
}

void nextion_setText(unsigned char * object, unsigned char * text, char UART_PORT)
{
	const char * ch1 = (const char *) object;
	const char * ch2 = (const char *) ".txt=";
	const char * ch3 = (const char *) "\"";
	const char * ch4 = (const char *) text;
	const char * ch5 = (const char *) "\"";

	if(UART_PORT==0)
	{
		Uart_Transmit_IT_PC((unsigned char *)ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_PC((unsigned char *)ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_PC((unsigned char *)ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_PC((unsigned char *)ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_PC((unsigned char *)ch5,(unsigned char)strlen((const char *)ch5));
		endConversation(UART_PORT);
	}
	if(UART_PORT==1)
	{
		Uart_Transmit_IT_Display((unsigned char *)ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_Display((unsigned char *)ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_Display((unsigned char *)ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_Display((unsigned char *)ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_Display((unsigned char *)ch5,(unsigned char)strlen((const char *)ch5));
		
		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC((unsigned char *)ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC((unsigned char *)ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC((unsigned char *)ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC((unsigned char *)ch4,(unsigned char)strlen((const char *)ch4));
// 		Uart_Transmit_IT_PC((unsigned char *)ch5,(unsigned char)strlen((const char *)ch5));
	}
	if(UART_PORT==2)
	{
		Uart_Transmit_IT_ESP((unsigned char *)ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_ESP((unsigned char *)ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_ESP((unsigned char *)ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_ESP((unsigned char *)ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_ESP((unsigned char *)ch5,(unsigned char)strlen((const char *)ch5));

		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC((unsigned char *)ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC((unsigned char *)ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC((unsigned char *)ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC((unsigned char *)ch4,(unsigned char)strlen((const char *)ch4));
// 		Uart_Transmit_IT_PC((unsigned char *)ch5,(unsigned char)strlen((const char *)ch5));
	}
}


void nextion_setValue(unsigned char * object, unsigned char * value, char UART_PORT)
{
	unsigned char * ch1 = object;
	unsigned char * ch2 = (unsigned char *) ".val=";
	unsigned char * ch3 = value;
	if(UART_PORT==0)
	{
		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));

		endConversation(UART_PORT);
	}
	if(UART_PORT==1)
	{
		Uart_Transmit_IT_Display(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_Display(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_Display(ch3,(unsigned char)strlen((const char *)ch3));

		
		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC((unsigned char *)"\r\n",(unsigned char)strlen((const char *)ch3));

	}
	if(UART_PORT==2)
	{
		Uart_Transmit_IT_ESP(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_ESP(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_ESP(ch3,(unsigned char)strlen((const char *)ch3));


		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC((unsigned char *)"\r\n",(unsigned char)strlen((const char *)ch3));
	}
}

void nextion_setPicture(unsigned char * x, unsigned char * y, unsigned char * picture, char UART_PORT)
{
	unsigned char * ch1 = (unsigned char *) "pic ";
	unsigned char * ch2 = x;
	unsigned char * ch3 = (unsigned char *) ",";
	unsigned char * ch4 = y;
	unsigned char * ch5 = (unsigned char *) ",";
	unsigned char * ch6 = picture;

	if(UART_PORT==0)
	{
		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_PC(ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_PC(ch5,(unsigned char)strlen((const char *)ch5));
		Uart_Transmit_IT_PC(ch6,(unsigned char)strlen((const char *)ch6));

		endConversation(UART_PORT);
	}
	if(UART_PORT==1)
	{
		Uart_Transmit_IT_Display(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_Display(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_Display(ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_Display(ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_Display(ch5,(unsigned char)strlen((const char *)ch5));
		Uart_Transmit_IT_Display(ch6,(unsigned char)strlen((const char *)ch6));
		
		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC(ch4,(unsigned char)strlen((const char *)ch4));
// 		Uart_Transmit_IT_PC(ch5,(unsigned char)strlen((const char *)ch5));
// 		Uart_Transmit_IT_PC(ch6,(unsigned char)strlen((const char *)ch6));
// 		Uart_Transmit_IT_PC((unsigned char *)"\r\n",(unsigned char)strlen((const char *)ch3));

	}
	if(UART_PORT==2)
	{
		Uart_Transmit_IT_ESP(ch1,(unsigned char)strlen((const char *)ch1));
		Uart_Transmit_IT_ESP(ch2,(unsigned char)strlen((const char *)ch2));
		Uart_Transmit_IT_ESP(ch3,(unsigned char)strlen((const char *)ch3));
		Uart_Transmit_IT_ESP(ch4,(unsigned char)strlen((const char *)ch4));
		Uart_Transmit_IT_ESP(ch5,(unsigned char)strlen((const char *)ch5));
		Uart_Transmit_IT_ESP(ch6,(unsigned char)strlen((const char *)ch6));

		endConversation(UART_PORT);
		
// 		Uart_Transmit_IT_PC(ch1,(unsigned char)strlen((const char *)ch1));
// 		Uart_Transmit_IT_PC(ch2,(unsigned char)strlen((const char *)ch2));
// 		Uart_Transmit_IT_PC(ch3,(unsigned char)strlen((const char *)ch3));
// 		Uart_Transmit_IT_PC(ch4,(unsigned char)strlen((const char *)ch4));
// 		Uart_Transmit_IT_PC(ch5,(unsigned char)strlen((const char *)ch5));
// 		Uart_Transmit_IT_PC(ch6,(unsigned char)strlen((const char *)ch6));
// 		Uart_Transmit_IT_PC((unsigned char *)"\r\n",(unsigned char)strlen((const char *)ch3));
	}
}


void endConversation(char UART_PORT)
{
	unsigned char ch2 [3]= {255,255,255};
	if (UART_PORT == 0)
	{
		Uart_Transmit_IT_PC((unsigned char *)ch2,3);
	}
	
	if (UART_PORT == 1)
	{
		Uart_Transmit_IT_Display((unsigned char *)ch2,3);
	}
	
	if (UART_PORT == 2)
	{
		Uart_Transmit_IT_ESP((unsigned char *)ch2,3);
	}
	_delay_ms(5);
}