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
	Diese Funktion ist eine Testfunktion, welche ausgelöst wird, wenn etwas über UART0 (PC) ankommt
*/
	Uart_Transmit_IT_PC((char *)INPUT);
	Uart_Transmit_IT_PC("\r\n");
	
	tmc6200_readInt(MOTOR0, TMC6200_GSTAT);
}

void bearbeite_Cocktail(uint8_t cocktail)
{
	aktuellesGetraenk_file = tail_getraenk_file;
	for (int i = 0 ; i < (i_Liste + cocktail) ; i++)
	{
		aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
	}
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
	nextion_change_page(CEINSTANZEIGE);
	i_Liste = 0;
	block_list_hoch = 0;
	block_list_runter = 0;
	aktuelleZutat = head_zut;
	erstelle_Liste_zutat("zutat");
}

void zubereitung_getraenk(uint16_t Menge)
{
	nextion_change_page(ZUBBILDSCHIRM);
	nextion_setText("zufallstxt", "Do stoht denn irgend e Text zum Getränk, Schwul.");
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
	
	for (int i = 0 ; i < 12 ; i++)
	{
		if (i != (zutat + i_Liste - 1))
		{
			totval += *(aktuellesGetraenk->mengen + i);
		}
	}
	restval = 100 - totval;
	
	
	// String, um Slider auszuwählen
	strcpy((char *)buff, (const char *)"slider");
	itoa(zutat, (char *)buff2, 10);
	strcat((char *)buff, (const char *)buff2);
	
	// Wert aus Slider holen und in Getränkeliste eintragen
	val = nextion_getSliderValue(buff, (unsigned char *)INPUT_UART_1);
	if (val > restval)
	{
		val = restval;
	}
	
	*(aktuellesGetraenk->mengen+i_Liste+zutat) = val;
	
	// String um Text zu Setzen
	itoa((int)val, (char *)buff2, 10);
	strcat((char *)buff2, "%");
	
	// String um Textfeld auszuwählen
	strcpy((char *)buff, (const char *)"menge");
	itoa(zutat, (char *) buff3, 10);
	strcat((char *)buff, (const char *)buff3);
	
	// Text schreiben
	nextion_setText(buff,buff2);
	
	// String um Text zu Setzen
	itoa((int)val, (char *)buff2, 10);
	
	// String um Textfeld auszuwählen
	strcpy((char *)buff, (const char *)"slider");
	itoa(zutat, (char *) buff3, 10);
	strcat((char *)buff, (const char *)buff3);
	
	// Text schreiben
	nextion_setValue(buff,buff2);
}


void choose_drink(uint8_t nr)
{
	lese_textfile_in_getraenk(i_Liste + nr);
	setze_startanzeige(aktuellesGetraenk);
	block_list_hoch = 0;
	block_list_runter = 0;
}

void fuelle_getraenk(uint16_t fuellmenge)
{

	// Switche durch alle Getränke
	for (uint8_t i = 0 ; i < 12 ; i++)
	{
		// Falls das Getränk vorkommt
		if ((*(uint8_t *)(aktuellesGetraenk->mengen + i) > 0) && (stop ==0))
		{
			char buff[5];
			itoa(*(uint16_t *)(aktuellesGetraenk->mengen + i), buff, 10);
			Uart_Transmit_IT_PC(buff);
			Uart_Transmit_IT_PC("\r");
			// Bewege Motor an stelle XY
/*
	Gebe Motor Position vor
	
	While momentane Position != vorgegebene Position
		warten
	
	Weiter mit Programmm
			
*/			
			// Berechne Menge, schalte Pumpe ein und beginne mit füllen
			uint16_t Menge = (fuellmenge * *(uint16_t *)(aktuellesGetraenk->mengen + i))/100;
			
			char buff2[10];
			itoa(Menge, buff2, 10);
			Uart_Transmit_IT_PC(buff2);
			Uart_Transmit_IT_PC("\r");
						
			uint8_t fuellen = 1;
			schalte_pumpe_ein(i);
			while (fuellen)
			{
				// Polle PWM-Signal des Durchflusssensor
				static uint8_t oldval=0;
				static uint32_t count=0;
			
				// Lese Sensor ein
				uint8_t newval = oldval ^ 0b00000001;
				
// 				uint8_t newval = lese_sensor(i);

				// Falls ein Flankenwechsel stattgefunden hat, zähle hoch
				if( !oldval && newval)
				{
					// Falls erwünschte Menge erreicht wurde, breche aus Schleife aus und setze Zähler zurück
					if(count++ > Menge)
					{
						schalte_pumpe_aus(i);
						count = 0;
						fuellen = 0;
					}
//*************************************************************************
					_delay_ms(5);
//					Delay entfernen wenn mit Sensor gearbeitet wird.

				
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
	Fahre zurück bis Home-Schalter betätigt wird
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
	// Getränkedurchwahr bei Tail starten.
	aktuellesGetraenk_file = tail_getraenk_file;
	
	// Shifte aktuelles Getränk auf bestimmte Seite
	// (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
	for (int i = 0 ; i < i_Liste ; i++)
	{
		aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
	}

	// Für alle Buttons auf der Seite ...
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
		if ((i + i_Liste + 1) == head_getraenk_file->file && !block_list_runter)
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
			
			// Sicherheitsdelay, Programm stürzt sonst ab
			_delay_ms(10);
			
			// Schreibe Text und Buttonnummer für disable in String
			char buff10[20] = {'\0'};
			strcat((char *)buff10, (const char *)name_button);
			itoa((i + 1), (char *)buff, 10);
			strcat((char *)buff10, (const char *)buff);
			
			// Disable Button
			nextion_disableButton(buff10);
		}
		
		//Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
		else
		{
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			nextion_setText(button,aktuellesGetraenk->name);
		}
		
		// Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
		if((i + i_Liste + 1) == tail_getraenk_file->file)
		{
			block_list_hoch = 1;
		}
		
		// Ein Getraenk weiter Scrollen
		aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
		
		// Sicherheitsdelay, Programm stürzt sonst ab
		_delay_ms(1);
		}
}

void erstelle_Liste_zutat(char * input)
{
	aktuelleZutat = head_zut;
	char string[21] = {'\0'};
	char string2[21] = {'\0'};
	char string3[21] = {'\0'};
	char buff[5] = {0};

	for (int i = i_Liste ; i < (4 + i_Liste) ; i++)
	{
		// Schreibe Buttonname, Slidername und Anzeiename in einen String
		itoa((i-i_Liste+1),buff,10);
		strcpy((char *)string, (const char *)input);
		strcat((char *)string, (const char *)buff);
		
		strcpy((char *)string2, (const char *)"slider");
		strcat((char *)string2, (const char *)buff);
		
		strcpy((char *)string3, (const char *)"menge");
		strcat((char *)string3, (const char *)buff);
				
		// Falls das Ende der Liste erreicht ist und Liste noch nicht blockiert,
		// Weiteres Scrollen blockieren,
		// Letzter Eintrag eintragen
		int run = 1;
		while (run)
		{
			aktuelleZutat = aktuelleZutat->next;
			if (aktuelleZutat->nr == i)
			{
				run = 0;
			}
		}
		
		
		if (i == head_zut->nr && !block_list_runter)
		{
			block_list_runter = 1;
			nextion_setText(string,aktuelleZutat->name);
			itoa(*(aktuellesGetraenk->mengen+i),buff,10);
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
		// Auf nächste Zutat zeigen
		else
		{
			nextion_setText(string,aktuelleZutat->name);
			itoa(*(aktuellesGetraenk->mengen+i),buff,10);
			nextion_setValue(string2,buff);
			strcat(buff, "%");
			nextion_setText(string3,buff);
		}
		
		if(i == tail_zut->nr)
		{
			block_list_hoch = 1;
		}
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
	
// 					- Erstelle lokale Variable für itoa-Buffer
// 					- Erstelle lokale Variable für Stringkette
// 					- Erstelle lokale Variable für Zutaten
// 					
// 					- für 0 ... Anzahl Getränke
// 					- Wenn die Menge des aktuellen Getränkes > 0
// 					- Hänge Zutat an Kette
// 					- Hänge Zeilenumbruch an Kette
// 					- Switche zur nächsten Zutat
// 					
// 					- Schreibe Zutatenkette in Textfeld
					
	zutat_t * tmp_zutat = head_zut;
	
	char string[512] = {'\0'};
	char buff[4] = {0};
	for (int i = 0 ; i<12 ; i++)
	{
		int run = 1;
		while (run)
		{
			tmp_zutat = tmp_zutat->next;
			if (tmp_zutat->nr == i)
			{
				run = 0;
			}
		}
		if (*(uint8_t *)(anzeige_getraenk->mengen + i) != (unsigned char)0)
		{
			strcat((char *)string, (const char *)tmp_zutat->name);
			for (int i = 0 ; i<(20-strlen(tmp_zutat->name)) ; i++)
			{
				strcat((char *)string, "-");
			}
			strcat((char *)string, (const char *)"(");
			itoa(*(uint8_t *)(anzeige_getraenk->mengen + i),buff,10);
			strcat((char *)string, (const char *)buff);
			strcat((char *)string, (const char *)"%)");
			strcat((char *)string, (const char *)"\\r");
		}
		tmp_zutat = tmp_zutat->next;
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
	char buff[20];
	itoa((int)file,(char *)buff,10);
	char * txt = ".txt";	
	strcat((char *)buff,txt);
	
	// "file.txt" lesen (File wird in char buffer[512] geschrieben)
	//return: 0, if normal operation or flag is READ
	//	      1, if file is already existing and flag = VERIFY
	//		  2, if file name is incompatible
	
	readFile( READ, (unsigned char *)buff);
		
	// Trennungszeichen definieren, Pointer initialisiern für Abschnitte
	char delimiter[] = ":,{}\r\n";
	char *ptr;
	// initialisieren und ersten Abschnitt erstellen (1. Kopf)
	
	ptr = strtok(buffer, delimiter);
	
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
	// Kopf prüfen und jeweilige Aktion ausführen
		if (pruefe_kopf(ptr, "Name"))
		{
			ptr = strtok(NULL, delimiter);
			strcpy(aktuellesGetraenk->name,ptr);
		}
		
		if (pruefe_kopf(ptr, "Mengen"))
		{		
			for (int i = 0 ; i < 12 ; i++)
			{
				ptr = strtok(NULL,delimiter);
				*(aktuellesGetraenk->mengen + i) = atoi(ptr);
			}
			ptr = strtok(NULL, delimiter);
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
	nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte vorhanden.\\rBitte einfügen und\\rneu starten.");
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
		TX_NEWLINE;
		Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
		FAT32_active = 0;
	}
// 	findFiles(GET_LIST,0);
	TX_NEWLINE
	TX_NEWLINE

}

void erstelle_File(uint8_t filename, char * name, uint8_t alkohol)
{
	char buff[128] = {0};
	char * ptr = buff;
	strcat(ptr, "Name:");
	strcat(ptr, name);

	strcat(ptr, "\rMengen:{");
	char buff2[5]  = {0};
	
	int i = 0;
	itoa(*(aktuellesGetraenk->mengen + i), (char *)buff2, 10);
	strcat(ptr, buff2);
	for (i = 1 ; i < 12 ; i++)
	{
		strcat(ptr,",");
		itoa(*(aktuellesGetraenk->mengen + i), (char *)buff2, 10);
		strcat(ptr, buff2);
	}
	strcat(ptr, "}\r");
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
	// Getränkedurchwahr bei Tail starten.
	aktuelleZutat = tail_zut;
	
	// Shifte aktuelles Getränk auf bestimmte Seite
	// (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
	for (int i = 0 ; i < i_Liste ; i++)
	{
		aktuelleZutat = aktuelleZutat->prev;
	}

	// Für alle Buttons auf der Seite ...
	// Initialisierungen
	char button[21] = {'\0'};
	char buff[4] = {0};
	
	for (int i = 0 ; i < 6 ; i++)
	{
		// Schreibe Zahl und Name des Buttons in String
		itoa((i + 1),buff,10);
		strcpy((char *)button, (const char *)name_button);
		strcat((char *)button, (const char *)buff);
		
		// Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
		// runterscrollen, blockieren und letzter Name einschreiben.
		if ((i + i_Liste ) == head_zut->nr && !block_list_runter)
		{
			block_list_runter = 1;
			nextion_setText(button,aktuelleZutat->name);
		}
		
		// Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
		// die Buttons disablen
		else if (block_list_runter)
		{
			// leerer String
			nextion_setText(button,"");
			
			// Sicherheitsdelay, Programm stürzt sonst ab
			_delay_ms(10);
			
			// Schreibe Text und Buttonnummer für disable in String
			char buff10[20] = {'\0'};
			strcat((char *)buff10, (const char *)name_button);
			itoa((i + 1), (char *)buff, 10);
			strcat((char *)buff10, (const char *)buff);
			
			// Disable Button
			nextion_disableButton(buff10);
		}
		
		//Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
		else
		{
			nextion_setText(button,aktuelleZutat->name);
		}
		
		// Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
		if((i + i_Liste) == tail_zut->nr)
		{
			block_list_hoch = 1;
		}
		
		// Ein Getraenk weiter Scrollen
		aktuelleZutat = aktuelleZutat->prev;
		
		// Sicherheitsdelay, Programm stürzt sonst ab
		_delay_ms(1);
	}
}