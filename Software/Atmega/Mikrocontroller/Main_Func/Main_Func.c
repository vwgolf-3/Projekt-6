/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */ 

#include "Main_Func.h"

//Init_IO

void IO_init(void)
{
	SPI_DDR = SPI_OUTPUT_MASK;
	TIMER_DDR = TIMER_OUTPUT_MASK;
}

void TIMER_init(void)
{
	OCR4A = 0;
	TCCR4A = 0;
	TCCR4B = 0;
	TCNT4 = 0;

	// 16000 Hz = (16000000/((124+1)*8)) == Match-Frequenz ==> PWM = 8000
	// output compare register, compare timer to 124
	OCR4A = 124;
	// CTC = Clear Timer on Compare Match (Timer Zählt nur bis Match)
	TCCR4B |= (1 << WGM42);
	// Prescaler 8
	TCCR4B |= (1 << CS41);
	// Toggle OC4B pin on match
	/*	TCCR4A = (1<<COM4B0);*/
}


void heartbeat_LED(void)
{
	toggle_LED();
   		_delay_ms(1000);
}

void toggle_LED(void)
{
   		SPI_PORT = SPI_PORT ^ (HEARTBEAT_LED);				// Toggelt nur HEARTBEAT_LED
}

char check_Communication_Input_UART_0(void)
{
	char ret = 0;
	// Check Buffer auf Einkommende Daten
	while(RB_length(&rb_rx_PC)>0)
	{
		unsigned char ch = RB_readByte(&rb_rx_PC);
		if (ch == 13)
		{
			INPUT_UART_0[cntr_UART_0] = 0;
			cntr_UART_0 = 0;
			cntr_End_UART_0 = 0;
			ret = 1;
			toggle_LED();
		}
		else
		{
			INPUT_UART_0[cntr_UART_0]=ch;
			cntr_UART_0++;
			ret = 0;
			toggle_LED();
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_0(void)
{
	Uart_Transmit_IT_PC((unsigned char *)"Empfangen0:",strlen((const char*)"Empfangen0:"));
	Uart_Transmit_IT_PC((unsigned char *)INPUT_UART_0,strlen((const char*)INPUT_UART_0));
	Uart_Transmit_IT_PC((unsigned char *)"\r\n",strlen((const char*)"\r\n"));
	UART_recieved_finished_0 = 0;
	toggle_LED();
}

char check_Communication_Input_UART_1(void)
{
	char ret = 0;
	while(RB_length(&rb_rx_Display)>0)					// UART_1
	{
		unsigned char ch = RB_readByte(&rb_rx_Display);
		// Verbesserung oder Verschlimmbesserung: Falls cntr_UART_1 >=2 dann schauen ob die letzten drei Übertragungen [cntr_UART_1], [cntr_UART_1-1], [cntr_UART_1-2] 0xFF sind
		if (ch == 0xFF)
		{
			if (cntr_End_UART_1==0)
			{
				cntr_End_UART_1++;
			}
			if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF))
			{
				cntr_End_UART_1++;
			}
			if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] != 0xFF))
			{
				cntr_End_UART_1=0;
			}
			if (cntr_End_UART_1==2 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF) && (INPUT_UART_1[cntr_UART_1-2] == 0xFF))
			{
				cntr_End_UART_1++;
			}
			if (cntr_End_UART_1==2 && ((INPUT_UART_1[cntr_UART_1-1] != 0xFF) || (INPUT_UART_1[cntr_UART_1-2] != 0xFF)))
			{
				cntr_End_UART_1 = 0;
			}
		}
		if (cntr_End_UART_1 == 3)
		{
			INPUT_UART_1[cntr_UART_1] = 0;
			INPUT_UART_1[cntr_UART_1-1]=0;
			INPUT_UART_1[cntr_UART_1-2]=0;
			cntr_UART_1 = 0;
			cntr_End_UART_1 = 0;
			ret = 1;
			toggle_LED();
		}
		else
		{
			INPUT_UART_1[cntr_UART_1]=ch;
			cntr_UART_1++;
			ret = 0;
			toggle_LED();
		}
	}
	return ret;
}

void proceed_Communication_INPUT_UART_1(void)
{
	unsigned char *ch0 = (unsigned char *)"Proceed UART 1: \r\n\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
	UART_recieved_finished_1 = 0;
	
	if(INPUT_UART_1[0]==0xFF&&INPUT_UART_1[1]==0xB1)
	{
		unsigned char *ch0 = (unsigned char *)"Beginn Tests: \r\n\r\n";//************************	Start
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch0 = (unsigned char *)"Initialisiere TMC: \r\n";//******************************************	Status Beginn:		Init_SPI
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
 		TMC4671_init();//****************************************************************************	Aktion:				Initialisiere SPI
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Init_SPI

		ch0 = (unsigned char *)"Setze Text Display 1: \r\n";//***************************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		unsigned char * ch1 = (unsigned char *)"b1";//***********************************************	Button:				b1
		unsigned char * ch2 = (unsigned char *)"Lemon Soda1";//**************************************	Text:				Lemon Soda1
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 1


		ch0 = (unsigned char *)"Setze Text Display 2: \r\n";//***************************************	Status Beginn:		Test Text 2
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));

		ch1 = (unsigned char *)"b0";//***************************************************************	Button:				b0
		ch2 = (unsigned char *)"Lemon Soda2";//******************************************************	Text:				Lemon Soda2
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 2

		ch0 = (unsigned char *)"Setze Text Display 3: \r\n";//***************************************	Status Beginn:		Test Text 3
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"t0";//****************************************************************	Button:				t0
		ch2 = (unsigned char *)"Lemon Soda3";//*******************************************************	Text:				Lemon Soda3

		nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//*************************************************	Aktion:				setText
		
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Text 3
		
		ch0 = (unsigned char *)"Setze Bild 1: \r\n";//************************************************	Status Beginn:		Test Setze Bild 1
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"250";//***************************************************************	x-Koordinate:		250
		ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
		unsigned char * ch3 = (unsigned char *)"7";//*************************************************	Bild Nr.:			7

		nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_1);//******************************************	Aktion:				setPicture
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Setze Bild 1
		
		ch0 = (unsigned char *)"Setze Bild 1: \r\n";//************************************************	Status Beginn:		Test Setze Bild 2
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"0";//*****************************************************************	x-Koordinate:		0
		ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
		ch3 = (unsigned char *)"7";//*****************************************************************	Bild Nr.:			7

		nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_1);//******************************************	Aktion:				setPicture
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Setze Bild 2
		
		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED

		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// *************************************	Status Beginn:		Test 8kHz-Signal einschalten
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		PWM_ON;//*************************************************************************************	Aktion:				WPM Einschalten
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED
	}

//**************************** PAGE 0x07, BUTTON 0x01***********************(Whiskey Cola Zubereitung)	Aktionsherkunft		0.5L
	
	if(INPUT_UART_1[0]==0x07&&INPUT_UART_1[1]==0x01)
	{
		unsigned char *ch0 = (unsigned char *)"Beginn Programmablauf: \r\n\r\n\r\n";//****************	Start
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));

		ch0 = (unsigned char *)"Unterhaltungstext schreiben: \r\n";//********************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		unsigned char * ch1 = (unsigned char *)"t1";//***********************************************	Button:				b1
		unsigned char * ch2 = (unsigned char *)"Wussten Sie, dass dieser\\rDrink in unter einer Minute\\rhergestellt wird?\\rNicht?";
		//*******************************************************************************************	Text:				Lemon Soda1
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_1);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 1
				
		ch0 = (unsigned char *)"TMC im Openloop laufen lassen: \r\n";//******************************	Status Beginn:		TMC Openloop
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		initTMC4671_Openloop();//********************************************************************	Aktion:				TMC Openloop
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		TMC Openloop
		
		ch0 = (unsigned char *)"Auf Seite 9 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"9";//****************************************************************	Seite:				9
		nextion_change_page(ch1);//******************************************************************	Aktion:				changePage

		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Seite wechseln
		
		_delay_ms(2000);

		ch0 = (unsigned char *)"Auf Seite 4 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"4";// ****************************************************************	Seite:				4 (Cocktailliste)
		nextion_change_page(ch1);// ******************************************************************	Aktion:				changePage

		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));// *****************************************	Status Ende:		Seite wechseln


		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED

		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// ************************************************	Status Beginn:		Test 8kHz-Signal ausschalten
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		PWM_OFF;//************************************************************************************	Aktion:				WPM Einschalten
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test 8kHz-Signal ausschalten
	}
}

char check_Communication_Input_UART_2(void)
{
	char ret = 0;
	while(RB_length(&rb_rx_ESP)>0)					// UART_2
	{
		unsigned char ch = RB_readByte(&rb_rx_ESP);
		// Verbesserung oder Verschlimmbesserung: Falls cntr_UART_1 >=2 dann schauen ob die letzten drei Übertragungen [cntr_UART_1], [cntr_UART_1-1], [cntr_UART_1-2] 0xFF sind
		if (ch == 0xFF)
		{
			if (cntr_End_UART_2==0)
			{
				cntr_End_UART_2++;
			}
			if (cntr_End_UART_2==1 && (INPUT_UART_2[cntr_UART_2-1] == 0xFF))
			{
				cntr_End_UART_2++;
			}
			if (cntr_End_UART_2==1 && (INPUT_UART_2[cntr_UART_2-1] != 0xFF))
			{
				cntr_End_UART_2=0;
			}
			if (cntr_End_UART_2==2 && (INPUT_UART_2[cntr_UART_2-1] == 0xFF) && (INPUT_UART_2[cntr_UART_2-2] == 0xFF))
			{
				cntr_End_UART_2++;
			}
			if (cntr_End_UART_2==2 && ((INPUT_UART_2[cntr_UART_2-1] != 0xFF) || (INPUT_UART_2[cntr_UART_2-2] != 0xFF)))
			{
				cntr_End_UART_2 = 0;
			}
		}
		if (cntr_End_UART_2 == 3)
		{
			INPUT_UART_2[cntr_UART_2] = 0;
			INPUT_UART_2[cntr_UART_2-1]=0;
			INPUT_UART_2[cntr_UART_2-2]=0;
			cntr_UART_2 = 0;
			cntr_End_UART_2 = 0;
			ret = 1;
			toggle_LED();
		}
		else
		{
			INPUT_UART_2[cntr_UART_2]=ch;
			cntr_UART_2++;
			ret = 0;
			toggle_LED();
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_2(void)
{
	unsigned char *ch0 = (unsigned char *)"Proceed UART 2: \r\n\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
	UART_recieved_finished_2 = 0;

//**************************** PAGE 0xFF, BUTTON 0xB1**************************(Gin Tonic Startseite)	Aktionsherkunft		Menu-Button
	
	if(INPUT_UART_2[0]==0xFF&&INPUT_UART_2[1]==0xB1)
	{
		unsigned char *ch0 = (unsigned char *)"Beginn Tests: \r\n\r\n";//************************	Start
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch0 = (unsigned char *)"Initialisiere TMC: \r\n";//******************************************	Status Beginn:		Init_SPI
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
 		TMC4671_init();//****************************************************************************	Aktion:				Initialisiere SPI
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Init_SPI

		ch0 = (unsigned char *)"Setze Text Display 1: \r\n";//***************************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		unsigned char * ch1 = (unsigned char *)"b1";//***********************************************	Button:				b1
		unsigned char * ch2 = (unsigned char *)"Lemon Soda1";//**************************************	Text:				Lemon Soda1
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_2);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 1


		ch0 = (unsigned char *)"Setze Text Display 2: \r\n";//***************************************	Status Beginn:		Test Text 2
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));

		ch1 = (unsigned char *)"b0";//***************************************************************	Button:				b0
		ch2 = (unsigned char *)"Lemon Soda2";//******************************************************	Text:				Lemon Soda2
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_2);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 2

		ch0 = (unsigned char *)"Setze Text Display 3: \r\n";//***************************************	Status Beginn:		Test Text 3
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"t0";//****************************************************************	Button:				t0
		ch2 = (unsigned char *)"Lemon Soda3";//*******************************************************	Text:				Lemon Soda3

		nextion_setText(ch1,ch2,NEXTION_DISPLAY_2);//*************************************************	Aktion:				setText
		
		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Text 3
		
		ch0 = (unsigned char *)"Setze Bild 1: \r\n";//************************************************	Status Beginn:		Test Setze Bild 1
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"250";//***************************************************************	x-Koordinate:		250
		ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
		unsigned char * ch3 = (unsigned char *)"7";//*************************************************	Bild Nr.:			7

		nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_2);//******************************************	Aktion:				setPicture
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Setze Bild 1
		
		ch0 = (unsigned char *)"Setze Bild 1: \r\n";//************************************************	Status Beginn:		Test Setze Bild 2
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"0";//*****************************************************************	x-Koordinate:		0
		ch2 = (unsigned char *)"80";//****************************************************************	y-Koordinate:		80
		ch3 = (unsigned char *)"7";//*****************************************************************	Bild Nr.:			7

		nextion_setPicture(ch1,ch2,ch3,NEXTION_DISPLAY_2);//******************************************	Aktion:				setPicture
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test Setze Bild 2
		
		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED

		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// *************************************	Status Beginn:		Test 8kHz-Signal einschalten
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		PWM_ON;//*************************************************************************************	Aktion:				WPM Einschalten
		
		ch0 = (unsigned char *)"\r\n";
// 		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED
	}

//**************************** PAGE 0x07, BUTTON 0x01***********************(Whiskey Cola Zubereitung)	Aktionsherkunft		0.5L
	
	if(INPUT_UART_2[0]==0x07&&INPUT_UART_2[1]==0x01)
	{
		unsigned char *ch0 = (unsigned char *)"Beginn Programmablauf: \r\n\r\n\r\n";//****************	Start
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));

		ch0 = (unsigned char *)"Unterhaltungstext schreiben: \r\n";//********************************	Status Beginn:		Test Text 1
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		unsigned char * ch1 = (unsigned char *)"t1";//***********************************************	Button:				b1
		unsigned char * ch2 = (unsigned char *)"Wussten Sie, dass dieser\\rDrink in unter einer Minute\\rhergestellt wird?\\rNicht?";
		//*******************************************************************************************	Text:				Lemon Soda1
		nextion_setText(ch1,ch2,NEXTION_DISPLAY_2);//************************************************	Aktion:				setText

		ch0 = (unsigned char *)"\r\n\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Test Text 1
				
		ch0 = (unsigned char *)"TMC im Openloop laufen lassen: \r\n";//******************************	Status Beginn:		TMC Openloop
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		initTMC4671_Openloop();//********************************************************************	Aktion:				TMC Openloop
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		TMC Openloop
		
		ch0 = (unsigned char *)"Auf Seite 9 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"9";//****************************************************************	Seite:				9
		nextion_change_page(ch1);//******************************************************************	Aktion:				changePage

		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//*****************************************	Status Ende:		Seite wechseln
		
		_delay_ms(2000);

		ch0 = (unsigned char *)"Auf Seite 4 wechseln: \r\n";//***************************************	Status Beginn:		Seite wechseln
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		ch1 = (unsigned char *)"4";// ****************************************************************	Seite:				4 (Cocktailliste)
		nextion_change_page(ch1);// ******************************************************************	Aktion:				changePage

		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));// *****************************************	Status Ende:		Seite wechseln


		ch0 = (unsigned char *)"Toggle LED: \r\n";//**************************************************	Status Beginn:		Toggle LED
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		toggle_LED();//*******************************************************************************	Aktion:				Toggle LED
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Toggle LED

		ch0 = (unsigned char *)"8kHz-Signal: \r\n";// ************************************************	Status Beginn:		Test 8kHz-Signal ausschalten
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));
		
		PWM_OFF;//************************************************************************************	Aktion:				WPM Einschalten
		
		ch0 = (unsigned char *)"\r\n";
		Uart_Transmit_IT_PC(ch0,strlen((const char*)ch0));//******************************************	Status Ende:		Test 8kHz-Signal ausschalten
	}
}

char check_Communication_Input_UART_3(void)
{
	char ret = 0;
	if(RB_length(&rb_rx_RFID)>0)					// UART_1
	{
		unsigned char ch = RB_readByte(&rb_rx_RFID);
		// Verbesserung oder Verschlimmbesserung: Falls cntr_UART_1 >=2 dann schauen ob die letzten drei Übertragungen [cntr_UART_1], [cntr_UART_1-1], [cntr_UART_1-2] 0xFF sind

// 		if (ch == 13)
// 		{
// 			INPUT_UART_3[cntr_UART_3] = 0;
// 			cntr_UART_3 = 0;
// 			cntr_End_UART_3 = 0;
// 			ret = 1;
// 			toggle_LED();
// 		}
// 		else
// 		{
// 			INPUT_UART_3[cntr_UART_3]=ch;
// 			cntr_UART_3++;
// 			ret = 0;
// 			toggle_LED();
// 		}

		if (ch == 0xFF)
		{
			if (cntr_End_UART_3==0)
			{
				cntr_End_UART_3++;
			}
			if (cntr_End_UART_3==1 && (INPUT_UART_3[cntr_UART_3-1] == 0xFF))
			{
				cntr_End_UART_3++;
			}
			if (cntr_End_UART_3==1 && (INPUT_UART_3[cntr_UART_3-3] != 0xFF))
			{
				cntr_End_UART_3=0;
			}
			if (cntr_End_UART_3==2 && (INPUT_UART_3[cntr_UART_3-1] == 0xFF) && (INPUT_UART_3[cntr_UART_3-2] == 0xFF))
			{
				cntr_End_UART_3++;
			}
			if (cntr_End_UART_3==2 && ((INPUT_UART_3[cntr_UART_3-1] != 0xFF) || (INPUT_UART_3[cntr_UART_3-2] != 0xFF)))
			{
				cntr_End_UART_3 = 0;
			}
		}
		if (cntr_End_UART_3 == 3)
		{
			INPUT_UART_3[cntr_UART_3] = 0;
			INPUT_UART_3[cntr_UART_3-1]=0;
			INPUT_UART_3[cntr_UART_3-2]=0;
			cntr_UART_3 = 0;
			cntr_End_UART_3 = 0;
			ret = 1;
			toggle_LED();
		}
		else
		{
			INPUT_UART_3[cntr_UART_3]=ch;
			cntr_UART_3++;
			ret = 0;
			toggle_LED();
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_3(void)
{
	Uart_Transmit_IT_PC((unsigned char *)"Empfangen3:",strlen((const char*)"Empfangen3:"));
	Uart_Transmit_IT_PC((unsigned char *)INPUT_UART_3,strlen((const char*)INPUT_UART_3));
	Uart_Transmit_IT_PC((unsigned char *)"\r\n",strlen((const char*)"\r\n"));
	UART_recieved_finished_3 = 0;
	toggle_LED();
}
