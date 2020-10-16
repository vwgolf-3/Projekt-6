/*
 * check_communication.c
 *
 * Created: 17.06.2020 12:25:51
 *  Author: kimsc
 */ 

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

void check_Communication_Input_MFRC522(void)
{
	char byte;
	uint8_t str[MAX_LEN];
	
	byte = mfrc522_read(ComIEnReg);
	
	// 		Uart_Transmit_IT_PC((char *)byte);
	// 		Uart_Transmit_IT_PC("\r\n");

	mfrc522_write(ComIEnReg,byte|0x20);

	byte = mfrc522_read(DivIEnReg);
	
	// 		Uart_Transmit_IT_PC((char *)byte);
	// 		Uart_Transmit_IT_PC("\r\n");
	
	mfrc522_write(DivIEnReg,byte|0x80);
	
	byte = mfrc522_request(PICC_REQALL,str);
	
	// 	 	Uart_Transmit_IT_PC((char *) byte);
	// 	 	Uart_Transmit_IT_PC("\r\n");

	if(byte == CARD_FOUND)
	{
		byte = mfrc522_get_card_serial(str);
		Uart_Transmit_IT_PC(( char *)str);
		Uart_Transmit_IT_PC(" :Vorher\r\n");
		
		
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
		Uart_Transmit_IT_PC((char *)str);
		Uart_Transmit_IT_PC(" : Nachher \r\n");
	}
	else
	{
		// 		 			Uart_Transmit_IT_PC(" Error \r\n");
	}
}