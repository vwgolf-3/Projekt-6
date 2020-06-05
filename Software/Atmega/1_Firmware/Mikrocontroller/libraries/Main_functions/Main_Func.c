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
	LED_DDR = LED_OUTPUT_MASK;
	SPI_DDR = SPI_OUTPUT_MASK;
	SPI2_DDR = SPI2_OUTPUT_MASK;
	PUMPE_DDR = PUMPE_OUTPUT_MASK;
	PUMPE_DDR2 = PUMPE2_OUTPUT_MASK;
	PUMPE_DDR3 = PUMPE3_OUTPUT_MASK;
	RFID_DDR = RFID_OUTPUT_MASK;
	FLUSS_DDR = 0b00000000;
	SPI_PORT |= SPI_MISO_PIN;
}

void heartbeat_LED(void)
{
	toggle_LED();
   		_delay_ms(1000);
}

void toggle_LED(void)
{
		LED_PORT = LED_PORT ^ (LEDR_BIT|LEDG_BIT|LEDB_BIT|LEDW_BIT);
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
		}
		else
		{
			INPUT_UART_0[cntr_UART_0]=ch;
			cntr_UART_0++;
			ret = 0;
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_0(void)
{
// 	char * ch = "Proceed UART 0: \n\r";
// 	Uart_Transmit_IT_PC(ch);
	cocktail_test_command(INPUT_UART_0);
}

char check_Communication_Input_UART_1(void)
{
	char ret = 0;
	while(RB_length(&rb_rx_Display)>0)					// UART_1
	{

		unsigned char ch = RB_readByte(&rb_rx_Display);

		if (ch == 0xFF && INPUT_UART_1[0] != 'q')
		{
			if (cntr_End_UART_1==0)
			{
				cntr_End_UART_1++;
			}
			else if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF))
			{
				cntr_End_UART_1++;
			}
			else if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] != 0xFF))
			{
				cntr_End_UART_1=0;
			}
			else if (cntr_End_UART_1==2 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF) && (INPUT_UART_1[cntr_UART_1-2] == 0xFF))
			{
				cntr_End_UART_1++;
			}
			else if (cntr_End_UART_1==2 && ((INPUT_UART_1[cntr_UART_1-1] != 0xFF) || (INPUT_UART_1[cntr_UART_1-2] != 0xFF)))
			{
				cntr_End_UART_1 = 0;
			}
		}
		if (INPUT_UART_1[0] == 'q' && strlen((const char *)INPUT_UART_1) >=4)
		{
			INPUT_UART_1[0] = 255;
		}
		if (cntr_End_UART_1 == 3)
		{
			INPUT_UART_1[cntr_UART_1] = 0;
			INPUT_UART_1[cntr_UART_1-1]=0;
			INPUT_UART_1[cntr_UART_1-2]=0;
			cntr_UART_1 = 0;
			cntr_End_UART_1 = 0;
			ret = 1;
		}
		else
		{
			INPUT_UART_1[cntr_UART_1]=ch;
			cntr_UART_1++;
			ret = 0;
		}
	}
	return ret;
}

void proceed_Communication_INPUT_UART_1(void)
{
	Uart_Transmit_IT_PC("Proceed UART 1: ");
	Uart_Transmit_IT_PC((char *)INPUT_UART_1);
	Uart_Transmit_IT_PC("\r");
	
	cocktail_check_command(INPUT_UART_1[0], INPUT_UART_1[1]);
}

char check_Communication_Input_UART_2(void)
{
	char ret = 0;
	while(RB_length(&rb_rx_ESP)>0)					// UART_2
	{
		unsigned char ch = RB_readByte(&rb_rx_ESP);
		// Verbesserung oder Verschlimmbesserung: Falls cntr_UART_1 >=2 dann schauen ob die letzten drei �bertragungen [cntr_UART_1], [cntr_UART_1-1], [cntr_UART_1-2] 0xFF sind
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
		}
		else
		{
			INPUT_UART_2[cntr_UART_2]=ch;
			cntr_UART_2++;
			ret = 0;
			
		}
	}
	return ret;
}

void proceed_Communication_Input_UART_2(void)
{
	Uart_Transmit_IT_PC("Proceed UART 2: ");
	Uart_Transmit_IT_PC((char *)INPUT_UART_2);
	Uart_Transmit_IT_PC("\r\n");
	
	cocktail_check_command(4,1);
}

// char check_Communication_Input_UART_3(void)
// {
// 	char ret = 0;
// 	
// 	while(RB_length(&rb_rx_RFID)>0)
// 	{
// 		
// 		unsigned char ch = RB_readByte(&rb_rx_RFID);
// 
// 		if (ch == 0xFF)
// 		{
// 			if (cntr_End_UART_3==0)
// 			{
// 				cntr_End_UART_3++;
// 			}
// 			if (cntr_End_UART_3==1 && (INPUT_UART_3[cntr_UART_3-1] == 0xFF))
// 			{
// 				cntr_End_UART_3++;
// 			}
// 			if (cntr_End_UART_3==1 && (INPUT_UART_3[cntr_UART_3-3] != 0xFF))
// 			{
// 				cntr_End_UART_3=0;
// 			}
// 			if (cntr_End_UART_3==2 && (INPUT_UART_3[cntr_UART_3-1] == 0xFF) && (INPUT_UART_3[cntr_UART_3-2] == 0xFF))
// 			{
// 				cntr_End_UART_3++;
// 			}
// 			if (cntr_End_UART_3==2 && ((INPUT_UART_3[cntr_UART_3-1] != 0xFF) || (INPUT_UART_3[cntr_UART_3-2] != 0xFF)))
// 			{
// 				cntr_End_UART_3 = 0;
// 			}
// 		}
// 		if (cntr_End_UART_3 == 3)
// 		{
// 			INPUT_UART_3[cntr_UART_3] = 0;
// 			INPUT_UART_3[cntr_UART_3-1]=0;
// 			INPUT_UART_3[cntr_UART_3-2]=0;
// 			cntr_UART_3 = 0;
// 			cntr_End_UART_3 = 0;
// 			ret = 1;
// 		}
// 		else
// 		{
// 			INPUT_UART_3[cntr_UART_3]=ch;
// 			cntr_UART_3++;
// 			ret = 0;
// 		}
// 	}
// 	return ret;
// }
// 
// void proceed_Communication_Input_UART_3(void)
// {
// 	Uart_Transmit_IT_PC("Proceed UART 3: ");
// 	Uart_Transmit_IT_PC((char *)INPUT_UART_3);
// 	Uart_Transmit_IT_PC("\r\n");
// 	
// 	cocktail_check_command(INPUT_UART_3[0],INPUT_UART_3[1]);
// }

void check_Communication_Input_UART(void)
{
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
// 	if (check_Communication_Input_UART_3())				// Check UART_3 (RFID), ob vollst�ndige �bertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
// 	{
// 		proceed_Communication_Input_UART_3();				// Vollst�ndige �bertragung des ESP's verarbeiten
// 	}
}