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
	Uart_Transmit_IT_PC((uint8_t *)"Proceed UART 0: \n\r");
	cocktail_test_command(INPUT_UART_0);
	
	for (int i = 0; i < strlen((const char *)INPUT_UART_0);i++)
	{
		INPUT_UART_0[i] = '\0';
	}
	
}

char check_Communication_Input_UART_1(void)
{
	char ret = 0;
	
	while(RB_length(&rb_rx_Display)>0)					// UART_1
	{
		
		unsigned char ch = RB_readByte(&rb_rx_Display);

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
	unsigned char *ch0 = (unsigned char *)"Proceed UART 1: ";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	Uart_Transmit_IT_PC((unsigned char *)INPUT_UART_1);
	ch0 = (unsigned char *)"\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0);

	cocktail_check_command(INPUT_UART_1[0],INPUT_UART_1[1]);
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
	unsigned char *ch0 = (unsigned char *)"Proceed UART 2: ";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	Uart_Transmit_IT_PC((unsigned char *)INPUT_UART_2);
	ch0 = (unsigned char *)"\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	
	cocktail_check_command(INPUT_UART_2[0],INPUT_UART_2[1]);
}

char check_Communication_Input_UART_3(void)
{
	char ret = 0;
	
	while(RB_length(&rb_rx_RFID)>0)
	{
		
		unsigned char ch = RB_readByte(&rb_rx_RFID);

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
	unsigned char *ch0 = (unsigned char *)"Proceed UART 3: ";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	Uart_Transmit_IT_PC((unsigned char *)INPUT_UART_3);
	ch0 = (unsigned char *)"\r\n";//************************	Start
	Uart_Transmit_IT_PC(ch0);
	
	cocktail_check_command(INPUT_UART_3[0],INPUT_UART_3[1]);
}