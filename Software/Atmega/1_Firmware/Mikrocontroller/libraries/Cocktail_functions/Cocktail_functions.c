/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */ 

#include "Cocktail_functions.h"

void cocktail_test_command(unsigned char INPUT[256])
{
/*
	Diese Funktion ist eine Testfunktion, welche ausgel�st wird, wenn etwas �ber UART0 (PC) ankommt
*/
	Uart_Transmit_IT_PC("Test Command: ");
	Uart_Transmit_IT_PC((char *)INPUT);
	Uart_Transmit_IT_PC("\r\n");
}

void bearbeite_Cocktail(uint8_t cocktail)
{
	choose_aktuellesGetraenk(cocktail);
	nextion_change_page(CEINSTANZEIGE);
	erstelle_Liste_zutat("zutat");
	i_Liste = 0;
}

void zubereitung_getraenk(uint32_t Menge)
{
	nextion_change_page(ZUBBILDSCHIRM);
	nextion_setText("zufallstxt", "Do stoht denn irgend e Text zum Getr�nk.");
	_delay_ms(1000);
	fuelle_getraenk(Menge);
	nextion_change_page(BEREITANZEIGE);
	_delay_ms(2000);
	nextion_change_page(STARTANZEIGE);
	setze_startanzeige(aktuellesGetraenk);
}

void schreibe_Menge_in_Getraenk(uint8_t zutat)
{
	uint8_t val = 0;
	char buff[15] = {0};
	char buff2[5];
	char buff3[5];
	
	uint8_t totval = 0;
	uint8_t restval = 0;
	// Alle Werte aus den anderen Mengen holen
	
	for (int count = 0 ; count < 12 ; count++)
	{
		if (count != (zutat + i_Liste))
		{
			totval += *(aktuellesGetraenk->mengen + count);
		}
	}
	restval = 100 - totval;
	
	// String, um Slider auszuw�hlen
	strcpy((char *)buff, (const char *)"slider");
	itoa((zutat + 1), (char *)buff2, 10);
	strcat((char *)buff, (const char *)buff2);
	
	// Wert aus Slider holen und in Getr�nkeliste eintragen
	val = nextion_getSliderValue(buff, (unsigned char *)INPUT_UART_1);
	if (val > restval)
	{
		val = restval;
	}
	
	*(aktuellesGetraenk->mengen+(i_Liste+zutat)) = val;
			
	// String um Text zu Setzen
	itoa((int)val, (char *)buff2, 10);
	strcat((char *)buff2, "%");
	
	// String um Textfeld auszuw�hlen
	strcpy((char *)buff, (const char *)"menge");
	itoa((zutat+1), (char *) buff3, 10);
	strcat((char *)buff, (const char *)buff3);
	
	// Text schreiben
	nextion_setText(buff,buff2);
	
	// String um Text zu Setzen
	itoa((int)val, (char *)buff2, 10);
	
	// String um Textfeld auszuw�hlen
	strcpy((char *)buff, (const char *)"slider");
	itoa((zutat +1), (char *) buff3, 10);
	strcat((char *)buff, (const char *)buff3);
	
	// Text schreiben
	nextion_setValue(buff,buff2);
}

void choose_aktuellesGetraenk(uint8_t nr)
{
	aktuellesGetraenk_file = tail_getraenk_file;
	for (int i = 0 ; i < (i_Liste + nr) ; i++)
	{
		aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
	}
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
	Uart_Transmit_IT_PC(aktuellesGetraenk->name);
	Uart_Transmit_IT_PC("\r");
	block_list_hoch = 0;
	block_list_runter = 0;
	i_Liste = 0;
}

void fuelle_getraenk(uint32_t fuellmenge)
{

	// Switche durch alle Getr�nke
	for (uint32_t i = 0 ; i < 12 ; i++)
	{
		// Falls das Getr�nk vorkommt
		if ((*(uint8_t *)(aktuellesGetraenk->mengen + i) > 0) && (stop == 0))
		{
			// Bewege Motor an stelle XY
/*
	Gebe Motor Position vor
	
	While momentane Position != vorgegebene Position
		warten

	Weiter mit Programmm
			
*/			
// 			uint32_t pulse_prp_1dl[12] = {477, 474, 483, 479, 486, 474, 479, 483, 474, 466, 477, 479};
//			uint32_t pulse_prp_3dl[12] = {499, 496, 499, 499, 499, 496, 500, 500, 496, 499, 502, 501};
			uint32_t pulse_prp_5dl[12] = {501, 500, 501, 500, 502, 500, 500, 502, 498, 501, 503, 506};
						
			// Berechne Menge, schalte Pumpe ein und beginne mit f�llen
			uint32_t Menge = (((uint32_t)fuellmenge * (uint32_t)pulse_prp_5dl[i]) * (uint32_t)*(uint8_t *)(aktuellesGetraenk->mengen + i)/(uint16_t)100);

			uint8_t fuellen = 1;
			uint8_t newval = lese_sensor(i);

			schalte_pumpe_ein(i);
			while (fuellen)
			{
				// Polle PWM-Signal des Durchflusssensor
				static uint8_t oldval=0;
				static uint32_t count=0;
			
				// Lese Sensor ein
				newval = oldval ^ 0b00000001;
// 				newval = lese_sensor(i);

				// Falls ein Flankenwechsel stattgefunden hat, z�hle hoch
				if( !oldval && newval)
				{
					// Falls erw�nschte Menge erreicht wurde, breche aus Schleife aus und setze Z�hler zur�ck
					if(count++ > Menge)
					{
						schalte_pumpe_aus(i);
						count = 0;
						fuellen = 0;
					}
//*************************************************************************
//					Delay entfernen wenn mit Sensor gearbeitet wird.
				_delay_ms(2);
					if (check_Communication_Input_UART_1())
					{
						proceed_Communication_INPUT_UART_1();
						if (stop == 1)
						{
							for (int k = 0 ; k < 12 ; k++)
							{
								schalte_pumpe_aus(k);
							}
							nextion_change_page(ABBRUCHANZEIGE);
							_delay_ms(2000);
							setze_startanzeige(aktuellesGetraenk);
							count = 0;
							fuellen = 0;
						}
					}
				}
			// Aktueller Sensorwert speichern
			oldval = newval;
			}
		}
	}	
/*
	Fahre zur�ck bis Home-Schalter bet�tigt wird
*/	
	stop = 0;
}

void schalte_pumpe_ein(uint8_t Pumpe)
{
	switch (Pumpe)
	{
		case 0:
		PUMPE0_PORT|=PUMPE0_BIT;
		break;
		case 1:
		PUMPE1_PORT|=PUMPE1_BIT;
		break;
		case 2:
		PUMPE2_PORT|=PUMPE2_BIT;
		break;
		case 3:
		PUMPE3_PORT|=PUMPE3_BIT;
		break;
		case 4:
		PUMPE4_PORT|=PUMPE4_BIT;
		break;
		case 5:
		PUMPE5_PORT|=PUMPE5_BIT;
		break;
		case 6:
		PUMPE6_PORT|=PUMPE6_BIT;
		break;
		case 7:
		PUMPE7_PORT|=PUMPE7_BIT;
		break;
		case 8:
		PUMPE8_PORT|=PUMPE8_BIT;
		break;
		case 9:
		PUMPE9_PORT|=PUMPE9_BIT;
		break;
		case 10:
		PUMPE10_PORT|=PUMPE10_BIT;
		break;
		case 11:
		PUMPE11_PORT|=PUMPE11_BIT;
		break;
	}
}

void schalte_pumpe_aus(uint8_t Pumpe)
{
	switch (Pumpe)
	{
		case 0:
		PUMPE0_PORT &= ~PUMPE0_BIT;
		break;
		case 1:
		PUMPE1_PORT &= ~PUMPE1_BIT;
		break;
		case 2:
		PUMPE2_PORT &= ~PUMPE2_BIT;
		break;
		case 3:
		PUMPE3_PORT &= ~PUMPE3_BIT;
		break;
		case 4:
		PUMPE4_PORT &= ~PUMPE4_BIT;
		break;
		case 5:
		PUMPE5_PORT &= ~PUMPE5_BIT;
		break;
		case 6:
		PUMPE6_PORT &= ~PUMPE6_BIT;
		break;
		case 7:
		PUMPE7_PORT &= ~PUMPE7_BIT;
		break;
		case 8:
		PUMPE8_PORT &= ~PUMPE8_BIT;
		break;
		case 9:
		PUMPE9_PORT &= ~PUMPE9_BIT;
		break;
		case 10:
		PUMPE10_PORT &= ~PUMPE10_BIT;
		break;
		case 11:
		PUMPE11_PORT &= ~PUMPE11_BIT;
		break;
	}
}

uint8_t lese_sensor(uint8_t Sensor)
{
	uint8_t val = 0;

	switch (Sensor)
	{
		case 0:
		val = FLUSS0_PIN & FLUSS0_BIT;
		break;
		case 1:
		val = FLUSS1_PIN & FLUSS1_BIT;
		break;
		case 2:
		val = FLUSS2_PIN & FLUSS2_BIT;
		break;
		case 3:
		val = FLUSS3_PIN & FLUSS3_BIT;
		break;
		case 4:
		val = FLUSS4_PIN & FLUSS4_BIT;
		break;
		case 5:
		val = FLUSS5_PIN & FLUSS5_BIT;
		break;
		case 6:
		val = FLUSS6_PIN & FLUSS6_BIT;
		break;
		case 7:
		val = FLUSS7_PIN & FLUSS7_BIT;
		break;
		case 8:
		val = FLUSS8_PIN & FLUSS8_BIT;
		break;
		case 9:
		val = FLUSS9_PIN & FLUSS9_BIT;
		break;
		case 10:
		val = FLUSS10_PIN & FLUSS10_BIT;
		break;
		case 11:
		val = FLUSS11_PIN & FLUSS11_BIT;
		break;
	}
	return val;
}

void erstelle_Liste_name(char * name_button)
{
	// Getr�nkedurchwahr bei Tail starten.
	aktuellesGetraenk_file = tail_getraenk_file;

	// Shifte aktuelles Getr�nk auf bestimmte Seite
	// (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
	for (int i = 0 ; i < i_Liste ; i++)
	{
		aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
	}

	// F�r alle Buttons auf der Seite ...
		
		// Initialisierungen
	char button[21] = {'\0'};
	char buff[4] = {0};
			
	for (int i = 0 ; i < 8 ; i++)
	{
		// Schreibe Zahl und Name des Buttons in String
		itoa((i + 1),buff,10);
		strcpy((char *)button, (const char *)name_button);
		strcat((char *)button, (const char *)buff);
		
		// Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
		// runterscrollen, blockieren und letzter Name einschreiben.
		if (aktuellesGetraenk_file == head_getraenk_file && !block_list_runter)
		{
			block_list_runter = 1;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			nextion_setText(button,aktuellesGetraenk->name);
		}
		
		// Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
		// die Buttons disablen
		else if (block_list_runter)
		{
			// leerer String
			nextion_setText(button,"");
			
			// Sicherheitsdelay, Programm st�rzt sonst ab
			_delay_ms(10);
			
			// Schreibe Text und Buttonnummer f�r disable in String
			char buff10[20] = {'\0'};
			strcat((char *)buff10, (const char *)name_button);
			itoa((i + 1), (char *)buff, 10);
			strcat((char *)buff10, (const char *)buff);
			
			// Disable Button
			nextion_disableButton(buff10);
			aktuellesGetraenk_file = aktuellesGetraenk_file->next;
		}
		
		//Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
		else
		{
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			nextion_setText(button,aktuellesGetraenk->name);
		}
		
		// Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde 
		// (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "�berl�uft" und so beide
		// Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
		
		if(aktuellesGetraenk_file == tail_getraenk_file && !block_list_runter)
		{
			block_list_hoch = 1;
		}
		
			// Ein Getraenk weiter Scrollen.
			aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
		
		// Sicherheitsdelay, Programm st�rzt sonst ab
		_delay_ms(1);
		}
}

void erstelle_Liste_zutat(char * input)
{
	char string[21] = {'\0'};
	char string2[21] = {'\0'};
	char string3[21] = {'\0'};
	char buff[5] = {0};
	aktuelles_zutat_file = tail_zutat_file;
	for (int i = 0 ; i < i_Liste ; i++)
	{
		aktuelles_zutat_file = aktuelles_zutat_file->prev;
	}

	for (int count = 0 ; count < 4 ; count++)
	{
		// Schreibe Buttonname, Slidername und Anzeiename in einen String
		itoa((count+1),buff,10);
		strcpy((char *)string, (const char *)input);
		strcat((char *)string, (const char *)buff);
		
		strcpy((char *)string2, (const char *)"slider");
		strcat((char *)string2, (const char *)buff);
		
		strcpy((char *)string3, (const char *)"menge");
		strcat((char *)string3, (const char *)buff);
		
		// Falls das Ende der Liste erreicht ist und Liste noch nicht blockiert,
		// Weiteres Scrollen blockieren,
		// Letzter Eintrag eintragen
		
		if (aktuelles_zutat_file == head_zutat_file && !block_list_runter)
		{
			block_list_runter = 1;
			lese_textfile_in_zutat(aktuelles_zutat_file->file);
			nextion_setText(string,aktuelle_zutat->name);
			itoa(*(aktuellesGetraenk->mengen+(count+i_Liste)),buff,10);
			nextion_setValue(string2,buff);
			strcat(buff, "%");
			nextion_setText(string3,buff);
		}
		// Sonst, wenn Liste Blockiert
		// Leerer String in Feld schreiben
		else if (block_list_runter)
		{
			nextion_setText(string,"");
			nextion_setValue(string2,"0");
		}
		// Im Normalbetrieb Zutat in Feld schreiben,
		// Auf n�chste Zutat zeigen
		else
		{
			lese_textfile_in_zutat(aktuelles_zutat_file->file);
			nextion_setText(string,aktuelle_zutat->name);
			itoa(*(aktuellesGetraenk->mengen+(count+i_Liste)),buff,10);
			nextion_setValue(string2,buff);
			strcat(buff, "%");
			nextion_setText(string3,buff);
		}
		
		if(aktuelles_zutat_file == tail_zutat_file)
		{
			block_list_hoch = 1;
		}
		aktuelles_zutat_file = aktuelles_zutat_file->prev;
		
		_delay_ms(10);
	}
}

void erstelle_bearb_Cocktailliste(void)
{
	for (int i = i_Liste ; i < (9 + i_Liste) ; i++)
	{
		char string[21] = {'\0'};
		char buff[4] = {0};
		itoa((i-i_Liste),buff,10);
		strcat((char *)string, (const char *)"bearbcocktail");
		strcat((char *)string, (const char *)buff);
		
		if (i == head_getraenk_file->file && !block_list_runter)
		{
			block_list_runter = 1;
			lese_textfile_in_getraenk(i);
			nextion_setText(string,aktuellesGetraenk->name);
		}
		else if (block_list_runter)
		{
			nextion_setText(string,"");
			Uart_Transmit_IT_Display("tsw bearbcocktail8,0");
			endConversation();
		}
		else
		{
			lese_textfile_in_getraenk(i);
			nextion_setText(string,aktuellesGetraenk->name);
		}
		_delay_ms(10);
	}
}

void setze_startanzeige(getraenk_t * anzeige_getraenk)
{
	char buff[4];
	nextion_change_page(STARTANZEIGE);
	nextion_setText("cocktailname",anzeige_getraenk->name);
	itoa(anzeige_getraenk->picture,(char *)buff,10);
	nextion_setPicture("235","80",(char *)buff);
	switch(Liste)
	{
		case ALLE:
		nextion_setText("alkoholjanein", "Alkoholisch");
		break;
		
		case ALKOHOL:
		nextion_setText("alkoholjanein", "Alkoholfrei");
		break;
		
		case ALKOHOLFREI:
		nextion_setText("alkoholjanein", "Alle");
		break;
	}
}

void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk)
{

// 					- Erstelle lokale Variable f�r itoa-Buffer
// 					- Erstelle lokale Variable f�r Stringkette
// 					- Erstelle lokale Variable f�r Zutaten
// 					
// 					- f�r 0 ... Anzahl Getr�nke
// 					- Wenn die Menge des aktuellen Getr�nkes > 0
// 					- H�nge Zutat an Kette
// 					- H�nge Zeilenumbruch an Kette
// 					- Switche zur n�chsten Zutat
// 					
// 					- Schreibe Zutatenkette in Textfeld
	char buff[10] = {'\0'};
	char string[512] = {'\0'};
		
	aktuelleZutatInMaschine = tail_zut_in_Maschine;
	
	for (uint8_t count = 0 ; count<12 ; count++)
	{
		if (*(aktuellesGetraenk->mengen + count) > (uint8_t)0)
		{
			strcat((char *)string, (const char *)aktuelleZutatInMaschine->name);
			for (int count2 = 0 ; count2<(20-strlen(aktuelleZutatInMaschine->name)) ; count2++)
			{
				strcat((char *)string,(const char *)"-");
			}
			strcat((char *)string, (const char *)"(");
			itoa(*(aktuellesGetraenk->mengen + count),(char *)buff, 10);
			strcat((char *)string, (const char *)buff);
			strcat((char *)string, (const char *)"%)\\r");
		}
		aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
	}
	nextion_setText("zutatenliste",string);
}

void schiebe_file_next(void)
{
	aktuellesGetraenk_file = aktuellesGetraenk_file->next;
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

void schiebe_file_prev(void)
{
	aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

void lese_textfile_in_getraenk(uint8_t file)
{
	// Erstellen eines Strings in Form von: "file.txt"
	char buff[50];
	itoa((int)file,(char *)buff,10);
	char * txt = ".txt";	
	strcat((char *)buff,txt);
	
	// "file.txt" lesen (File wird in char buffer[512] geschrieben)
	//return: 0, if normal operation or flag is READ
	//	      1, if file is already existing and flag = VERIFY
	//		  2, if file name is incompatible
	
	readFile( READ, (unsigned char *)buff);
		
	// Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
	char delimiter[] = ":,{}\r\n";
	char *ptr;
	// initialisieren und ersten Abschnitt erstellen (1. Kopf)
	
	ptr = strtok((char *)buffer, delimiter);
	
	//	Abschnitt in buffer extrahieren:
/*
	Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
	********************************************************************
	Name:Getraenk 1
	Mengen:{0,0,0,0,0,0,0,0,0,0}
	Alkohol:1
	Bild:2
*/ 
	while(ptr != NULL) {
	// Kopf pr?fen und jeweilige Aktion ausf?hren
		if (pruefe_kopf(ptr, "Name"))
		{
			ptr = strtok(NULL, delimiter);
			strcpy(aktuellesGetraenk->name,ptr);
		}
		
		if (pruefe_kopf(ptr, "Mengen"))
		{		
			ptr = strtok(NULL, delimiter);
			
			aktuelleZutatInMaschine = tail_zut_in_Maschine;
			
			do
			{
				*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->position) = (uint8_t) 0;
				aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
			}while(aktuelleZutatInMaschine != head_zut_in_Maschine);

			// Suche Zutaten im File
			while(*ptr != ';')
			{
				aktuelleZutatInMaschine = tail_zut_in_Maschine;
				
				// Suche nach richtiger Position der Zutat in der Maschine
				do
				{
					// Vergleiche daf�r den Namen der Zutat im File mit dem Namen der Zutat in der Maschine
					if(compare_string((char *)ptr, (char *)aktuelleZutatInMaschine->name) == 0)
					{
						ptr = strtok(NULL, delimiter);
						
						// Und schreibe Wert in die richtige Position
						*(uint8_t *)(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->position) = atoi(ptr);
					}
					aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
				}while(aktuelleZutatInMaschine != tail_zut_in_Maschine);
				
				ptr = strtok(NULL, delimiter);
			}
		}
		
		if (pruefe_kopf(ptr, "Alkohol"))
		{
			ptr = strtok(NULL, delimiter);
			aktuellesGetraenk->alkohol = atoi(ptr);
		}
		
		if (pruefe_kopf(ptr, "Bild"))
		{
			ptr = strtok(NULL, delimiter);
			(aktuellesGetraenk->picture) = atoi(ptr);
		}
		
	// Neuer Kopf suchen und ptr darauf zeigen lassen
		ptr = strtok(NULL, delimiter);
	}
}

uint8_t pruefe_kopf(char * beginn, char string[])
{
	uint8_t kopf = 0;
	if (compare_string(beginn,string)==0)
	{
		kopf = 1;
	}	
	return kopf;
}

uint8_t compare_string(char *first, char *second)
{
	while(*first==*second)
	{
		if ( *first == '\0' || *second == '\0' )
		{
			break;
		}
		
		first++;
		second++;
	}
	if( *first == '\0' && *second == '\0' )
	{
		return 0;
	}
	else
	{
	return -1;
	}
}

void SD_startup(void)
{
	cardType = 0;

	for (i=0; i<10; i++)
	{
		error = SD_init();
		if(!error) break;
	}

	if(error)
	{
		if(error == 1) Uart_Transmit_IT_PC((char*)("SD card not detected..\r"));
		if(error == 2) Uart_Transmit_IT_PC((char*)("Card Initialization failed..\r"));
	nextion_change_page(FEHLERANZEIGE);
	nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte vorhanden.\\rBitte einf�gen und\\rneu starten.");
		// 		while(1);  //wait here forever if error in SD init
		}else{
		
		switch (cardType)
		{
			case 1:Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 1.x) Detected!\r"));
			break;
			case 2:Uart_Transmit_IT_PC(("High Capacity Card Detected!\r"));
			break;
			case 3:Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 2.x) Detected!\r"));
			break;
			default:Uart_Transmit_IT_PC(("Unknown SD Card Detected!\r"));
			break;
		}
	}

	SPI_HIGH_SPEED;	//SCK - 4 MHz
	_delay_ms(1);   //some delay


	FAT32_active = 1;
	error = getBootSectorData (); //read boot sector and keep necessary data in global variables
	if(error)
	{
		Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
		FAT32_active = 0;
	}
// 	findFiles(GET_LIST,0);

}

void erstelle_File(uint8_t filename, char * name, uint8_t alkohol)
{
	char buff[128] = {0};
	char * ptr = buff;
	strcat(ptr, "Name:");
	strcat(ptr, name);

	strcat(ptr, "\rMengen:\r");
	char buff2[5]  = {0};
	
	aktuelleZutatInMaschine = tail_zut_in_Maschine;
	do 
	{
		if (*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->position) > (uint8_t) 0)
		{
			strcat(ptr,aktuelleZutatInMaschine->name);
			strcat(ptr, (const char *)":");
			itoa(*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->position), (char *)buff2, 10);
			strcat(ptr, (const char *)buff2);
			strcat(ptr, (const char *)"\r");
		}
		aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
	} while (aktuelleZutatInMaschine != tail_zut_in_Maschine);
	
	strcat(ptr, ";\r");
	strcat(ptr, "Alkohol:");
	itoa(alkohol, (char *)buff2, 10);
	strcat(ptr, (char *)buff2);
	strcat(ptr, "\r");

	strcat(ptr, "Bild:");
	if (aktuellesGetraenk->picture != 24)
	{
		char buff[5];
		itoa(aktuellesGetraenk->picture,(char *)buff, 10);
		strcat(ptr, (char *)buff);
	}
	else
	{
		strcat(ptr, "24");
	}
	
	strcat(ptr, "~");

	char buff3[15] = {'\0'};
	itoa(filename, (char *)buff3, 10);
	strcat((char *)buff3, (const char *)".txt");
	writeFile((unsigned char *)buff3,(unsigned char *)ptr);
}

void loesche_FIle(uint8_t filename)
{
	unsigned char buff[20] = {'\0'};
	itoa(filename, (char *)buff, 10);
	strcat((char *)buff,".txt");
	deleteFile((unsigned char *)buff);
	
}

void erstelle_Liste_Zutat_Pos(char * name_button)
{
	nextion_change_page(FLUESSANZEIGE1);

	// Getr�nkedurchwahr bei Tail starten.
	aktuelles_zutat_file = tail_zutat_file;

	// Shifte aktuelles Getr�nk auf bestimmte Seite
	// (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
	for (int i = 0 ; i < i_Liste ; i++)
	{
		aktuelles_zutat_file = aktuelles_zutat_file->prev;
	}
	
	// F�r alle Buttons auf der Seite ...
	// Initialisierungen
	char button[50] = {'\0'};
	char buff[5] = {0};
	char buff10[50] = {'\0'};

	for (int i = 0 ; i < 6 ; i++)
	{
		// Schreibe Zahl und Name des Buttons in String
		itoa((i + 1),buff,10);
		strcpy((char *)button, (const char *)name_button);
		strcat((char *)button, (const char *)buff);
		
		// Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
		// runterscrollen, blockieren und letzter Name einschreiben.
		if (aktuelles_zutat_file == head_zutat_file && !block_list_runter)
		{
			block_list_runter = 1;
			lese_textfile_in_zutat(aktuelles_zutat_file->file);
			nextion_setText(button,aktuelle_zutat->name);
		}
		
		// Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
		// die Buttons disablen
		else if (block_list_runter)
		{
			// leerer String
			nextion_setText(button,"");
			
			// Sicherheitsdelay, Programm st�rzt sonst ab
			_delay_ms(10);
			
			// Disable Button
			nextion_disableButton(button);
		}
		
		//Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
		else
		{
			lese_textfile_in_zutat(aktuelles_zutat_file->file);
			nextion_setText(button,aktuelle_zutat->name);
		}
		
		// Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde
		// (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "�berl�uft" und so beide
		// Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
		
		if(aktuelles_zutat_file == tail_zutat_file && !block_list_runter)
		{
			block_list_hoch = 1;
		}
		
		if (compare_string((char *)aktuelleZutatInMaschine->name, (char *)aktuelle_zutat->name)==0)
		{
			strcpy((char *)buff10, (const char *)button);
			strcat((char *)buff10, (const char *)".pco=2016");
			Uart_Transmit_IT_Display((char *)buff10);
			endConversation();
		}	
		
		// Ein Getraenk weiter Scrollen.
		aktuelles_zutat_file = aktuelles_zutat_file->prev;
		
		// Sicherheitsdelay, Programm st�rzt sonst ab
		_delay_ms(1);
	}
}

void lese_textfile_in_zutat(uint8_t file)
{
	char buff_textfiles_zutat[21] = {'\0'};
	char buff2_textfiles_zutat[5] = {'\0'};
	
	strcpy((char *)buff_textfiles_zutat, (const char *)"Z");
	itoa(file, (char *)buff2_textfiles_zutat, 10);
	strcat((char *)buff_textfiles_zutat, (const char *)buff2_textfiles_zutat);
	strcat((char *)buff_textfiles_zutat, (const char *)".txt");
	
	readFile(READ, (unsigned char *)buff_textfiles_zutat);
	
	// Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
	char delimiter[] = ":,{}\r\n";
	char *ptr;
	
	// initialisieren und ersten Abschnitt erstellen (1. Kopf)
	ptr = strtok((char *)buffer, delimiter);
	
	//	Abschnitt in buffer extrahieren:
	
/*	Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
	*******************************************************************
	Name:Getraenk1
	Alkohol:1/0
*/	

	while(ptr != NULL) 
	{
		// Kopf pruefen und jeweilige Aktion ausfuehren
		if (pruefe_kopf(ptr, "Name"))
		{
			ptr = strtok(NULL, delimiter);
			strcpy((char *)aktuelle_zutat->name,(const char *)ptr);
		}
		if (pruefe_kopf(ptr, "Alkohol"))
		{
			ptr = strtok(NULL, delimiter);
			aktuelle_zutat->alkohol = atoi(ptr);
		}
			
		// Neuer Kopf suchen und ptr darauf zeigen lassen
		ptr = strtok(NULL, delimiter);
	}
}

void setze_Posanzeige_Rot_Gruen(void)
{
	aktuelleZutatInMaschine = tail_zut_in_Maschine;
	char buff[50];
	char buff2[10];
	for (int i = 0 ; i <12 ; i++)
	{
		strcpy((char *)buff, "b");
		itoa(i,(char *) buff2, 10);
		strcat((char *)buff, (const char *)buff2);
		switch (aktuelleZutatInMaschine->status)
		{
			case 0:
			strcat((char *)buff, ".pco=0");
			break;
			case 1:
			strcat((char *)buff, ".pco=2016");
			break;
			case 2:
			strcat((char *)buff, ".pco=63488");
			break;
		}
		Uart_Transmit_IT_Display((char *)buff);
		endConversation();
		aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
	}
}

void setze_aktuelle_Zutat_in_Maschine_prev(uint8_t nr)
{
	aktuelleZutatInMaschine = tail_zut_in_Maschine;
	for (int i = 0 ; i < nr; i++)
	{
		aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
	}
}

void setze_Fluessgkeit_in_Position(uint8_t nr, uint8_t status)
{
	// Falls nr ausserhalb des Listenbereichs ==> Keine Fl�ssigkeit
	if (nr > 5)
	{
		// Schreibe Null-Terminator �ber bestehenden Namen
		char * leer = "(keine)";
		char len1 = strlen((const char *)aktuelleZutatInMaschine->name);
		char len2 = strlen((const char *)leer);
		for (int count = 0 ; count < (len1 + 1) ; count++)
		{
			*(aktuelleZutatInMaschine->name + count) = '\0';
		}
		for (int count = 0 ; count < (len2 + 1) ; count++)
		{
			*(aktuelleZutatInMaschine->name + count) = *(leer + count);
		}
	}
	
	// Falls innerhalb des Listenbereichs ==> Fl�ssigkeit aus File laden
	else
	{
		
	// W�hle Zutaten-File, auf welches gedr�ckt wurde und lese es ein.
	aktuelles_zutat_file = tail_zutat_file;
	for (int i = 0 ; i < (i_Liste + nr) ; i++)
	{
		aktuelles_zutat_file = aktuelles_zutat_file->prev;
	}
	lese_textfile_in_zutat(aktuelles_zutat_file->file);
	
	// Schreibe Name der gefundenen Zutat in die ausgew�hlte Position.
	char len = strlen((const char *)aktuelle_zutat->name);
	for (int count = 0 ; count < (len + 1) ; count++)
	{
		*(aktuelleZutatInMaschine->name + count) = *(aktuelle_zutat->name + count);
	}
	}
	
	// Definiere den Status des Getr�nks
	aktuelleZutatInMaschine->status = status;
	
	// Zur�ck zur Positionsanzeige
	nextion_change_page(POSANZEIGE);
	
	// Schreibe �nderung in Titel der Positionsanzeige
	char buff[50] = {'\0'};
	char buff2[5] = {'\0'};
	strcpy((char *)buff, "Nr.");
	itoa(aktuelleZutatInMaschine->position+1, buff2, 10);
	strcat((char *)buff, (const char *)buff2);
	strcat((char *)buff, " = ");
	strcat((char *)buff, aktuelleZutatInMaschine->name);
	nextion_setText("zubabfrage",buff);
	setze_Posanzeige_Rot_Gruen();
	block_list_hoch = 0;
	block_list_runter = 0;
	i_Liste = 0;

	char buff98[20] = {'\0'};
	strcpy((char *)buff98, (const char *)"M.txt");
	deleteFile((unsigned char *)buff98);

	char buff_file[512] = {'\0'};
	char buff99[10];

	aktuelleZutatInMaschine = tail_zut_in_Maschine;

	for (int count = 0 ; count < 12 ; count++)
	{
		if (count != 0)
		{
			strcat((char *)buff_file, (const char *)aktuelleZutatInMaschine->name);
		}
		else
		{
			strcpy((char *)buff_file, (const char *)aktuelleZutatInMaschine->name);
		}
	strcat((char *)buff_file, (const char *)",");
	itoa(aktuelleZutatInMaschine->status, (char *)buff99, 10);
	strcat((char *)buff_file, (const char *)buff99);
	strcat((char *)buff_file, (const char *)",");
	itoa(aktuelleZutatInMaschine->alkohol, (char *)buff99, 10);
	strcat((char *)buff_file, (const char *)buff99);
	if (aktuelleZutatInMaschine != head_zut_in_Maschine)
	{
		strcat((char *)buff_file, (const char *)"\r");
	}
	else
	{
		strcat(buff_file, "~");
	}
	aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
	}
	
	char buff97[20] = {'\0'};
	strcpy((char *)buff97, (const char *)"M.txt");	
	writeFile((unsigned char *)buff97, (unsigned char *)buff_file);
}

