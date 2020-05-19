/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */ 

#include "Cocktail_functions.h"

void cocktail_check_command(uint8_t page, uint8_t button)
{


	getraenk_t * tmp_getraenk = head_getraenk;
	
	switch (page)
	{
	case STARTANZEIGE:
	
		switch (button)
		{
			
			case ZUTATEN:
/*
				- Wechsle auf Zutatenseite
				- Setze Überschrift
				
				- Erstelle lokale Variable für itoa-Buffer
				- Erstelle lokale Variable für Stringkette
				- Erstelle lokale Variable für Zutaten
				
				- für 0 ... Anzahl Getränke
					- Wenn die Menge des aktuellen Getränkes > 0
						- Hänge Zutat an Kette
						- Hänge Zeilenumbruch an Kette
						- Switche zur nächsten Zutat
						
				- Schreibe Zutatenkette in Textfeld
*/
				nextion_change_page(ZUTATENANZEIGE);
				nextion_setText("cocktailname",aktuellesGetraenk->name);


				zutat_t * tmp_zutat = head_zut;
			 	char string[256] = {'\0'};
					char buff[4] = {0};
				for (int i = 0 ; i<12 ; i++)
				{
					if (*(uint8_t *)(aktuellesGetraenk->mengen + i) != (unsigned char)0)
					{
						strcat((char *)string, (const char *)tmp_zutat->name);
						for (int i = 0 ; i<(20-strlen(tmp_zutat->name)) ; i++)
						{
							strcat((char *)string, "-");
						}
						strcat((char *)string, (const char *)"(");
						itoa(*(uint8_t *)(aktuellesGetraenk->mengen + i),buff,10);
						strcat((char *)string, (const char *)buff);
						strcat((char *)string, (const char *)"%)");
						strcat((char *)string, (const char *)"\\r");
					}
						tmp_zutat = tmp_zutat->next;
				}
				nextion_setText("zutatenliste",string);

			break;
			
			case LINKS:
/*
				- Wähle vorgehendes Getränk aus
				- Schreibe Name des Getränks
				- Integer to ASCI
				- Setze Bild des Getränks
*/
				aktuellesGetraenk = aktuellesGetraenk->prev;
				nextion_setText("cocktailname",aktuellesGetraenk->name);
				itoa(aktuellesGetraenk->picture,(char *)buff,10);
				nextion_setPicture("235","80",(char *)buff);
				
			break;
			
			case B3:
				
				
				
			break;
			
			case RECHTS:
/*
				- Wähle nächstes Getränk aus
				- Schreibe Name des Getränks
				- Setze Bild des Getränks
*/
				aktuellesGetraenk = aktuellesGetraenk->next;
				nextion_setText("cocktailname",aktuellesGetraenk->name);
				itoa(aktuellesGetraenk->picture,(char *)buff,10);
				nextion_setPicture("235","80",( char *)buff);						
			break;
			
			case LISTE:
			
				nextion_change_page(LISTENANZEIGE);
				
				for (int i = 1 ; i < 9 ; i++)
				{
					char string[20] = {'\0'};
					char buff[4] = {0};
					strcat((char *)string, (const char *)"cocktail");
					itoa(i,buff,10);
					strcat((char *)string, (const char *)buff);
					nextion_setText(string,aktuellesGetraenk->name);
					aktuellesGetraenk = aktuellesGetraenk->next;
				}

			break;
			
			case MENU:
			
			break;
			
			case ALKOHOLJANEIN:
			
			break;
		}
		
		break;
		
	case ZUTATENANZEIGE:
		
		switch(button)
		{
			case OKZUTATEN:
			
				nextion_change_page(STARTANZEIGE);
				nextion_setText("cocktailname",aktuellesGetraenk->name);
				char buff[4] = {0};
				itoa(aktuellesGetraenk->picture,(char *)buff,10);
				nextion_setPicture("235","80",(char *)buff);			
			break;
			
			case ZUTATENLISTE:
			
			break;
		}
		
		break;
		
	case LISTENANZEIGE:
	
		switch (button)
		{
			case COCKTAIL1:
			
				nextion_change_page(STARTANZEIGE);
			
			break;
			
			case COCKTAIL2:
			
			break;
			
			case COCKTAIL3:
			
			break;
			
			case COCKTAIL4:
			
			break;
			
			case COCKTAIL5:
			
			break;
			
			case COCKTAIL6:
			
			break;
			
			case COCKTAIL7:
			
			break;
			
			case COCKTAIL8:
			
			break;
			
			case RAUFLIST:
			
			break;
			
			case RUNTERLIST:
			
			break;
		}
	
	break;
	
	case ZUBABFRAGE:
	
	switch (button)
	{
		case KLEIN:
		
		break;
		
		case GROSS:
		
		break;
		
		case ABBRUCHZUBAB:
		
		break;
	}
	
	break;
	
	case ZUBBILDSCHIRM:
	
	switch (button)
	{
		case ZUFALLSTEXT:
		
		break;
		
		case ABBRUCHZUB:
		
		break;
	}
	
	break;
	
	case BREITANZEIGE:
	
	switch (button)
	{
		case BEREIT:
		
		break;
	}
	
	break;
	
	case MENUANZEIGE:
	
	break;
	
	case BEARBEITUNGSANZEIGE:
	
	break;
	
	case CEINSTANZEIGE:
	
	break;
	
	case REINANZEIGE1:
	
	break;
	
	case REINANZEIGE2:
	
	break;
	
	case REINANZEIGE3:
	
	break;
	
	case INFOANZEIGE:
	
	break;
	
	case ABBRUCHANZEIGE:
	
	break;
	
	case FEHLERANZEIGE:
	
	break;
	
	case ERSTANZEIGE1:
	
	break;
	
	case ERSTANZEIGE2:
	
	break;
	}
}

void cocktail_test_command(unsigned char INPUT[256])
{
// 	int8_t array[12] = {1,2,3,4,5,6,7,8,9,0,1,2};
// 	getraenk_t * tmp;
	Uart_Transmit_IT_PC((char *)INPUT);
	Uart_Transmit_IT_PC("\r\n");
	
// 	delete_EEPROM((uint8_t *)0);
// 	
// 	add_drink_to_eeprom(address,(char *)INPUT,(uint8_t *)array,1,1);
// 	
// 	tmp = read_drink_from_eemprom(address);
// 	head = insert_at_head(&head, tmp);
	
// 	showlist();
	fuelle_getraenk(20);
	
}

void fuelle_getraenk(uint16_t fuellmenge)
{
	// Switche durch alle Getränke
	for (uint8_t i = 0 ; i < 12 ; i++)
	{
		// Falls das Getränk vorkommt
		if (*(uint8_t *)(aktuellesGetraenk->mengen + i) != 0)
		{
			// Bewege Motor an stelle XY
/*
	Gebe Motor Position vor
	
	While momentane Position != vorgegebene Position
		warten
	
	Weiter mit Programmm
			
*/			
			// Berechne Menge, schalte Pumpe ein und beginne mit füllen
			uint16_t Menge = fuellmenge * *(uint16_t *)(aktuellesGetraenk->mengen + i);
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
				if( !oldval && newval){
					// Falls erwünschte Menge erreicht wurde, breche aus Schleife aus und setze Zähler zurück
					if(count++ > Menge){
						schalte_pumpe_aus(i);
						count = 0;
						fuellen = 0;
					}

//*************************************************************************
				_delay_ms(1);
//				Delay entfernen wenn mit Sensor gearbeitet wird.
				}
			// Aktueller Sensorwert speichern
			oldval = newval;
			}
		}
	}
	aktuellesGetraenk = aktuellesGetraenk->next;
	
/*
	Fahre zurück bis Home-Schalter betätigt wird
*/		
	
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


void init_Getraenke_func()
{
	aktuellesGetraenk = head_getraenk;
	nextion_change_page(STARTANZEIGE);
	nextion_setText("cocktailname",aktuellesGetraenk->name);
}