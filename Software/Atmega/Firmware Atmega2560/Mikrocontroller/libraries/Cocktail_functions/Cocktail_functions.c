/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */ 

#include "Cocktail_functions.h"
#define DEBUG_1 0

void cocktail_check_command(char page, char button)
{
	if(page==0xFF&&button==0xB1)
	{
		cocktail_do_command1();
	}
	
	if(page==0x07&&button==0x01)
	{
		cocktail_do_command2();
	}
}

void cocktail_do_command1(void)
{
	unsigned char *ch0 = (unsigned char *)"Beginn Command1: \r\n\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	
	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Initialisiere TMC: \r\n";//******************************************	Status Beginn:		Init_SPI
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		Init_SPI
		_delay_ms(50);
	}
	
	TMC4671_init();//****************************************************************************	Aktion:				Initialisiere SPI

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Setze Text Display 1: \r\n";//***************************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		Test Text 1
		_delay_ms(50);
	}
	
	unsigned char * ch1 = (unsigned char *)"b1";//***********************************************	Button:				b1
	unsigned char * ch2 = (unsigned char *)"Lemon Soda1";//**************************************	Text:				Lemon Soda1
	nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText


	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Setze Text Display 2: \r\n";//***************************************	Status Beginn:		Test Text 2
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		Test Text 2
		_delay_ms(50);
	}
	ch1 = (unsigned char *)"b0";//***************************************************************	Button:				b0
	ch2 = (unsigned char *)"Lemon Soda2";//******************************************************	Text:				Lemon Soda2
	nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Setze Text Display 3: \r\n";//***************************************	Status Beginn:		Test Text 3
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Test Text 3
		_delay_ms(50);
	}
	
	ch1 = (unsigned char *)"t0";//****************************************************************	Button:				t0
	ch2 = (unsigned char *)"Lemon Soda3";//*******************************************************	Text:				Lemon Soda3
	nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//*************************************************	Aktion:				setText

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Setze Bild 1: \r\n";//************************************************	Status Beginn:		Test Setze Bild 1
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Test Setze Bild 1
		_delay_ms(50);
	}
	
	ch1 = (unsigned char *)"250";//***************************************************************	x-Koordinate:		250
	ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
	unsigned char * ch3 = (unsigned char *)"7";//*************************************************	Bild Nr.:			7
	nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_1);//******************************************	Aktion:				setPicture
	
	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Setze Bild 2: \r\n";//************************************************	Status Beginn:		Test Setze Bild 2
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Test Setze Bild 2
		_delay_ms(50);
	}
	
	ch1 = (unsigned char *)"0";//*****************************************************************	x-Koordinate:		0
	ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
	ch3 = (unsigned char *)"7";//*****************************************************************	Bild Nr.:			7
	nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_1);//******************************************	Aktion:				setPicture
	
	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Toggle LED
		_delay_ms(50);
	}
		
	toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		

	if(DEBUG_1)
	{
		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// *************************************	Status Beginn:		Test 8kHz-Signal einschalten
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Toggle LED
		_delay_ms(50);
	}

}

void cocktail_do_command2(void)
{
	unsigned char *ch0 = (unsigned char *)"Beginn Command2: \r\n\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0);

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Unterhaltungstext schreiben: \r\n";//********************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		Test Text 1			
	}

	unsigned char * ch1 = (unsigned char *)"t1";//***********************************************	Button:				b1
	unsigned char * ch2 = (unsigned char *)"Wussten Sie, dass dieser\\rDrink in unter einer Minute\\rhergestellt wird?\\rNicht?";
	//*******************************************************************************************	Text:				Lemon Soda1
	nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText


	if (DEBUG_1)
	{			
		ch0 = (unsigned char *)"TMC im Openloop laufen lassen: \r\n";//******************************	Status Beginn:		TMC Openloop
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		TMC Openloop
	}
	
// 	initTMC4671_Openloop();//********************************************************************	Aktion:				TMC Openloop
	
	if (DEBUG_1)
	{	
		ch0 = (unsigned char *)"Auf Seite 9 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//*****************************************	Status Ende:		Seite wechseln
	}
	
	ch1 = (unsigned char *)"9";//****************************************************************	Seite:				9
	nextion_change_page(ch1);//******************************************************************	Aktion:				changePage

	_delay_ms(2000);
	
	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Auf Seite 4 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);// *****************************************	Status Ende:		Seite wechseln
	}
	
	ch1 = (unsigned char *)"4";// ****************************************************************	Seite:				4 (Cocktailliste)
	nextion_change_page(ch1);// ******************************************************************	Aktion:				changePage

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Toggle LED
	}
	
	toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		

	if (DEBUG_1)
	{
		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// ************************************************	Status Beginn:		Test 8kHz-Signal ausschalten
		Uart_Transmit_IT_PC(ch0);
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0);//******************************************	Status Ende:		Test 8kHz-Signal ausschalten
	}
	
}

void cocktail_test_command(unsigned char INPUT[256])
{
// 	int8_t array[12] = {1,2,3,4,5,6,7,8,9,0,1,2};
// 	getraenk_t * tmp;
	Uart_Transmit_IT_PC((uint8_t *)INPUT);
	Uart_Transmit_IT_PC((uint8_t *)"\r\n");
	
// 	delete_EEPROM((uint8_t *)0);
// 	
// 	add_drink_to_eeprom(address,(char *)INPUT,(uint8_t *)array,1,1);
// 	
// 	tmp = read_drink_from_eemprom(address);
// 	head = insert_at_head(&head, tmp);	

// 	PUMPE_PORT = PUMPE_PORT ^ 0b11111100;
// 	PUMPE_PORT2 = PUMPE_PORT2 ^ 0b00000100;
// 	PUMPE_PORT3 = PUMPE_PORT3 ^ 0b01111100;
	
// 	showlist();
	PUMPE0_PORT|=PUMPE0_BIT;
	test = 1;
// 	fuelle_getraenk(head->mengen, 50000);
	
}


void fuelle_getraenk(uint8_t * mengen, uint16_t fuellmenge)
{
	
}