

#include "Cocktail_Statemachine.h"

void init_Getraenke_func()
{
	nextion_change_page(STARTANZEIGE);
	setze_startanzeige(aktuellesGetraenk);
}


void cocktail_check_command(int8_t page, int8_t button)
{
/*
	Diese Funktion checkt, von welcher Seiter der Befehl kommt
*/
	switch (page)
	{
		/*0x01 = 0d01*/
	case STARTANZEIGE:
		check_startseite(button);	
	break;
		
		/*0x02 = 0d02*/
	case ZUTATENANZEIGE:
		check_zutatenanzeige(button);		
	break;
		
		/*0x03 = 0d03*/
	case LISTENANZEIGE:
		check_listenanzeige(button);
	break;
	
		/*0x04 = 0d04*/
	case ZUBABFRAGE:
		check_zubabfrage(button);	
	break;
	
		/*0x05 = 0d05*/
	case ZUBBILDSCHIRM:
		check_zubbildschirm(button);	
	break;
		
		/*0x07 = 0d07*/
	case MENUANZEIGE:
		check_menuanzeige(button);
	break;
	
		/*0x08 = 0d08*/
	case BEARBEITUNGSANZEIGE:
		check_bearbeitungsanzeige(button);
	break;
	
		/*0x09 0d09*/
	case CEINSTANZEIGE:
		check_ceinstanzeige(button);
	break;
	
		/*0x0A = 0d10*/
	case REINANZEIGE1:
		check_reinanzeige1(button);	
	break;
		
		/*0x0B = 0d11*/
	case REINANZEIGE2:
		check_reinanzeige2(button);	
	break;
	
		/*0x0C = 0d12*/
	case REINANZEIGE3:
		check_reinanzeige3(button);
	break;
		/*0x0D = 0d13*/
	case INFOANZEIGE:
		check_infoanzeige(button);
	break;
	
// 		/*0x0E = 0d14*/
// 	case ABBRUCHANZEIGE:
// 		check_abbruchanzeige(button);
// 	break;
	
		/*0x0F = 0d15*/
	case FEHLERANZEIGE:
		check_fehleranzeige(button);
	break;
	
		/*0x10 = 0d16*/
	case ERSTANZEIGE1:
		check_erstanzeige1(button);
	break;
	
		/*0x11 = 0d17*/
		case ERSTANZEIGE2:
		check_erstanzeige2(button);
	break;
		
		/*0x12 = 0d18*/
	case LOESCHABFRAGE:
	check_loeschanzeige(button);
	break;
	
		/*0x13 = 0d19*/
	case POSANZEIGE:
	check_posanzeige(button);
	break;
	
	/*0x14 = 0d20*/
	case FLUESSANZEIGE1:
	check_fluessanzeige1(button);
	break;
	
	/*0x15 = 0d21*/
	case FLUESSANZEIGE2:
	check_fluessanzeige2(button);
	break;
	
	/*0x16 = 0d22*/
	case FLUESSANZEIGE3:
	check_fluessanzeige3(button);
	break;
	
	/*0x17 = 0d23*/
	case RFIDANZEIGE1:
	check_RFIDAnzeige1(button);
	break;
	
	/*0x18 = 0d24*/
	case RFIDANZEIGE2:
	check_RFIDAnzeige2(button);
	break;
	
	/*0x19 = 0d25*/
	case RFIDFEHLER:
	check_RFIDFehler(button);
	break;
	}
}

void check_startseite(uint8_t button)
{
	switch (button)
	{
		
		case ZUTATEN:
/*		0x02 = 0b02
			- Wechsle auf Zutatenanzeige
			- Setze Name des aktuellen Getränks
			- Erstelle Zutatenliste des Getränks
*/
			nextion_change_page(ZUTATENANZEIGE);
			nextion_setText("cocktailname",aktuellesGetraenk->name);
			erstelle_Zutatenliste(aktuellesGetraenk);
		break;
			
		case LINKS:
/*		0x03 = 0b03
			- Wähle je nach Kriterium nächstes Getränk aus
				- Wenn alle Getränke ausgewählt wurden, durch alle Files Switchen
				- Wenn alkoholische Getränke ausgewählt wurden, alkoholfreie Files überspringen
				- Wenn alkoholfreie Getränke ausgewählt wurden, alkoholische Files überspringen
			- Schreibe File in aktuelles Getränk
			- Setze Startanzeige
*/
			switch (Liste)
			{
				case ALLE:				
//				0x00 = 0b00
					schiebe_file_next();
				break;
				
				case ALKOHOL:
//				0x01 = 0b01
					schiebe_file_next();
					while(aktuellesGetraenk->alkohol == 0)
					{
					schiebe_file_next();
					}
				break;
				
				case ALKOHOLFREI:
//				0x02 = 0b02
					schiebe_file_next();
					while(aktuellesGetraenk->alkohol == 1)
					{
					schiebe_file_next();
					}
				break;
			}
		setze_startanzeige(aktuellesGetraenk);			
		break;
		
		case B33:
/*		0x04 = 0b04
			- Wechsle auf Zubereitungsabfrage (Menge)
			- Schreibe File in aktuelles Getränk
*/
			nextion_change_page(ZUBABFRAGE);
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
		break;
		
		case RECHTS:
/*		0x05 = 0b05
			- Wähle je nach Kriterium vorhergehendes Getränk aus
				- Wenn alle Getränke ausgewählt wurden, durch alle Files Switchen
				- Wenn alkoholische Getränke ausgewählt wurden, alkoholfreie Files überspringen
				- Wenn alkoholfreie Getränke ausgewählt wurden, alkoholische Files überspringen
			- Schreibe File in aktuelles Getränk
			- Setze Startanzeige
*/
			switch (Liste)
			{
				case ALLE:
//				0x00 = 0b00
					schiebe_file_prev();
				break;
				
				case ALKOHOL:
//				0x01 = 0b01
					schiebe_file_prev();
					while(aktuellesGetraenk->alkohol == 0)
					{
						schiebe_file_prev();
					}
				break;
				case ALKOHOLFREI:
//				0x02 = 0b02
					schiebe_file_prev();
					while(aktuellesGetraenk->alkohol == 1)
					{
						schiebe_file_prev();
					}
				break;
			}
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case LISTE:
/*		0x06 = 0b06
			- Setze Listenanzeige
			- Variable für Listenseite auf 0 setzen
			- Erstelle ersten Listenabschnitt mit Cocktailnamen
*/
			nextion_change_page(LISTENANZEIGE);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
			break;
		
		case MENU:
/*		0x07 = 0b07
			- Setze Menuanzeige
*/
			nextion_change_page(MENUANZEIGE);
		break;
		
		case ALKOHOLJANEIN:
/*		0x08 = 0b08
			- Lese erstes Getränk ein
			- Wechsle Modus: Alle Getränke/Alkoholisch/Alkoholfrei
			- Schreibe erstes File gemäss Modus in aktuelles Getränk
			- Setze Startanzeige
*/
			aktuellesGetraenk_file = tail_getraenk_file;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			switch(Liste)
			{
				case ALLE:
				Liste = ALKOHOL;							// Modus-Wechsel
				while (aktuellesGetraenk->alkohol == 0)		// File Suchen mit Alkohol
				{
					schiebe_file_prev();
				}
				break;
				
				case ALKOHOL:
				Liste = ALKOHOLFREI;						// Modus-Wechsel
				while (aktuellesGetraenk->alkohol == 1)		// File suchen ohne Alkohol
				{
					schiebe_file_prev();
				}
				break;
				
				case ALKOHOLFREI:
				Liste = ALLE;								// Modus-Wechsel
				break;
			}
			setze_startanzeige(aktuellesGetraenk);			// Startanzeige setzen
		break;
		
		case LOESCHEN:
/*		0x09 = 0b09
			- Setze Löschabfrage
*/
			nextion_change_page(LOESCHABFRAGE);
		break;
	}
}

void check_zutatenanzeige(uint8_t button)
{
	switch(button)
	{
		case OKZUTATEN:
/*		0x01 = 0b01
			- Setze Startanzeige
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case ZUTATENLISTE:
/*		0x02 = 0b02
			- Setze Startanzeige
*/
			setze_startanzeige(aktuellesGetraenk);	
		break;
	}
}

void check_listenanzeige(uint8_t button)
{
	switch (button)
	{
/*		0x01 bis 0x08 = 0b01 bis 0b08
			- Wähle x-ten Cocktail des aktuellen Listenabschnitts
			- Setze Startanzeige
*/
		case COCKTAIL1:
			choose_aktuellesGetraenk(0);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL2:
			choose_aktuellesGetraenk(1);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL3:
			choose_aktuellesGetraenk(2);	
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL4:
			choose_aktuellesGetraenk(3);		
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL5:
			choose_aktuellesGetraenk(4);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL6:
			choose_aktuellesGetraenk(5);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL7:
			choose_aktuellesGetraenk(6);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case COCKTAIL8:
			choose_aktuellesGetraenk(7);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case RAUFLIST1:
/*		0x09 = 0b09
			- Untere Blockierung aufheben
			- Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}		
		break;
		
		case RUNTERLIST1:
/*		0x0A = 0b10
			- Obere Blockierung aufheben
			- Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 8;
				erstelle_Liste_name("cocktail");
			}	
		break;
	}
	
}

void check_zubabfrage(uint8_t button)
{
	switch (button)
	{
		case KLEIN:		
/*		0x01 = 0b01
			- Getränk mit 3dl zubereiten
*/
			zubereitung_getraenk((uint32_t)3);
		break;
		
		case GROSS:
/*		0x02 = 0b02
			- Getränk mit 5dl zubereiten
*/
			zubereitung_getraenk((uint32_t)5);
	break;
		
		case ABBRUCHZUBAB:
/*		0x03 = 0b03
			- Setze Startanzeige
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
	}
}

void check_zubbildschirm(uint8_t button)
{
	switch (button)
	{
/*		0x01 = 0b01
			- Setze stop-Flag = 1 im Zubereitungsprozess
*/
		case ABBRUCHZUB:
			stop = 1;
		break;
	}
}

void check_menuanzeige(uint8_t button)
{
	switch (button)
	{
		case COCKTAILBEARBEITEN:
/*		0x01 = 0b01
			- Setze Bearbeitungsanzige
			- Setze Listenabschnitt auf 1. Abschnitt
			- Erstelle ersten Listenabschnitt mit Cocktailnamen
*/
			nextion_change_page(BEARBEITUNGSANZEIGE);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case COCKTAILERSTELLEN:
/*		0x02 = 0b02
			- Setze Erstellungsanzeige (Namenseingabe neuer Cocktail)
			- Setze Grossschreibe-Flag = 1 für erster Buchstabe gross
			- Setze counter für Buchstabenindex des neuen Cocktail-Namens = 0
			- Initialisiere neuen Cocktailname auf '\0'
*/
			nextion_change_page(ERSTANZEIGE1);
			Grossschreib = 1;
			counter = 0;
			char len = strlen(buff_name);
			for (int i = 0 ; i < len ; i ++)
			{
				buff_name[i] = '\0';
			}	
		break;
		
		case MASCHINEREINIGEN:
/*		0x03 = 0b03
			- Setze Reinigungsanzeige1
*/
		nextion_change_page(REINANZEIGE1);
		break;
		
		case MASCHINENINFO:
/*		0x04 = 0b04
			- Setze Infoanzeige
*/
		nextion_change_page(INFOANZEIGE);
		break;
		
		case ZURUECK1:
/*		0x05 = 0b05
			- Setze Startabzeige
*/
		setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSPOS:
/*		0x06 = 0b06
			- Setze Posanzeige
			- Färbe die Nummern der Positionen gemäss Status
*/
		nextion_change_page(POSANZEIGE);
		setze_Posanzeige_Rot_Gruen();
		break;
		
		case RFID:
/*		0x07 = 0b07
			- Setze RFIDANZEIGE1
*/
		nextion_change_page(RFIDANZEIGE1);
		break;
	}
}

void check_bearbeitungsanzeige(uint8_t button)
{
	switch (button)
	{
		case BEARBCOCKTAIL1:
/*		0x01 = 0b01
			- Bearbeite Cocktail an Stelle 0 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(0);
		break;
		
		case BEARBCOCKTAIL2:
/*		0x02 = 0b02
			- Bearbeite Cocktail an Stelle 1 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(1);
		break;
		
		case BEARBCOCKTAIL3:
/*		0x03 = 0b03
			- Bearbeite Cocktail an Stelle 2 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(2);
		break;
		
		case BEARBCOCKTAIL4:
/*		0x04 = 0b04
			- Bearbeite Cocktail an Stelle 3 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(3);
		break;
		
		case BEARBCOCKTAIL5:
/*		0x05 = 0b05
			- Bearbeite Cocktail an Stelle 4 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(4);
		break;
		
		case BEARBCOCKTAIL6:
/*		0x06 = 0b06
			- Bearbeite Cocktail an Stelle 5 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(5);
		break;
		
		case BEARBCOCKTAIL7:
/*		0x07 = 0b07
			- Bearbeite Cocktail an Stelle 6 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(6);
		break;
		
		case BEARBCOCKTAIL8:
/*		0x08 = 0b08
			- Bearbeite Cocktail an Stelle 7 im aktuellen Listenabschnitt
*/
			bearbeite_Cocktail(7);
		break;
		
		case RAUFLIST2:
/*		0x09 = 0b09
			- Untere Blockierung aufheben
			- Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}

		break;
		
		case RUNTERLIST2:
/*		0x0A = 0b10
			- Obere Blockierung aufheben
			- Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 8;
				erstelle_Liste_name("cocktail");
			}
		break;		
	}	
}

void check_ceinstanzeige(uint8_t button)
{
	switch(button)
	{
		case RAUFLIST3:
/*		0x01 = 0b01
			- Untere Blockierung aufheben
			- Gehe Liste um 4 Zutaten hoch, falls nicht schon am oberen Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 4;
				erstelle_Liste_zutat("zutat");
			}
		break;
		
		case RUNTERLIST3:
/*		0x02 = 0b02
			- Obere Blockierung aufheben
			- Gehe Liste um 4 Zutaten runter, falls nicht schon am untern Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 4;
				erstelle_Liste_zutat("zutat");
			}
		break;
		
		case STANDARDEINST:
/*		0x03 = 0b03
			- ***************************************************************************************************************************************************************************************************3
*/
			block_list_hoch = 0;
			block_list_runter = 0;
			nextion_change_page(STARTANZEIGE);
		break;
		
		case SPEICHERN1:
/*		0x04 = 0b04
			- Listenblockierungen aufheben und Listenabschnitt auf 0 setzen
			- Bestehendes Getränke-File löschen
			- Aktuelles Getränke-File erstellen und speichern
			- Startanzeige setzen
*/
			block_list_hoch = 0;
			block_list_runter = 0;
			i_Liste = 0;
			loesche_FIle(aktuellesGetraenk_file->file);
			erstelle_File(aktuellesGetraenk_file->file, aktuellesGetraenk->name, aktuellesGetraenk->alkohol);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case SLIDER01:
/*		0x05 = 0b05
			- Auf drücken oder sliden aktueller Wert aus Slider 1 (Pos 0) lesen und in Menge des Getränkes schreiben
*/
			schreibe_Menge_in_Getraenk(0);
		break;
		
		case SLIDER02:
/*		0x06 = 0b06
			- Auf drücken oder sliden aktueller Wert aus Slider 2 (Pos 1) lesen und in Menge des Getränkes schreiben
*/
			schreibe_Menge_in_Getraenk(1);
		break;
		
		case SLIDER03:
/*		0x07 = 0b07
			- Auf drücken oder sliden aktueller Wert aus Slider 3 (Pos 2) lesen und in Menge des Getränkes schreiben
*/
			schreibe_Menge_in_Getraenk(2);
		break;
		
		case SLIDER04:
/*		0x08 = 0b08
			- Auf drücken oder sliden aktueller Wert aus Slider 4 (Pos 3) lesen und in Menge des Getränkes schreiben
*/
			schreibe_Menge_in_Getraenk(3);
		break;
	}
}

void check_reinanzeige1(uint8_t button)
{
	switch(button){
		
		case ABBRECHEN1:
/*		0x01 = 0b01
			- Menuanzeige setzen
*/
			nextion_change_page(MENUANZEIGE);
		break;
		
		case WEITER1:
/*		0x02 = 0b02
			- Reinigungsanzeige 2 setzen
*/
			nextion_change_page(REINANZEIGE2);
		break;
	}
}

void check_reinanzeige2(uint8_t button)
{
	switch(button)
	{
		case ABBRECHEN2:
/*		0x01 = 0b01
			- Menuanzeige setzen
*/
			nextion_change_page(MENUANZEIGE);
		break;
		
		case WEITER2:
/*		0x02 = 0b02
			- Reinigungsanzeige 3 setzen
			- Durch alle Pumpen durchschalten und jeweils plus/minus 2 Sekunden durchspülen lassen
			- Während des Durchspül-Prozesses die Kommunikation prüfen auf einkommende Befehle
			- Erstes Getränk setzen und Startanzeige anzeigen
*/
			nextion_change_page(REINANZEIGE3);
			for (int i = 0 ; i < 12 ; i++)
			{
				if (stop == 0)
				{
					schalte_pumpe_ein(i);
					uint16_t cnt = 0;
					while ((cnt < 2000))
					{
						if(check_Communication_Input_UART_1())
						{
							proceed_Communication_INPUT_UART_1();
						}
						cnt++;
						_delay_ms(1);
					}
				}
				schalte_pumpe_aus(i);
			}
			stop = 0;
			nextion_change_page(STARTANZEIGE);
			aktuellesGetraenk_file = tail_getraenk_file;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			setze_startanzeige(aktuellesGetraenk);
		break;
	}
}

void check_reinanzeige3(uint8_t button)
{
	switch(button)
	{
		case ABBRECHEN3:
/*		0x01 = 0b01
			- Menuanzeige setzen
			- Stop-Flag für Flüssigkeits-Abbruch auf 1
*/
			nextion_change_page(MENUANZEIGE);
			stop = 1;
		break;
	}
}

void check_infoanzeige(uint8_t button)
{
	switch(button)
	{
		case ZURUECK2:
/*		0x01 = 0b01
			- Menuanzeige setzen
*/
			nextion_change_page(MENUANZEIGE);
		break;
	}
}

void check_fehleranzeige(uint8_t button)
{
	
}

void check_erstanzeige1(uint8_t button)
{	
	// Initialisierung für Gross-/Kleinschreib-Wechsel
	char wechsel = 0;
	
	switch (button)
	{
		case A:
/*		0x01 = 0b01
			- Buchstabe A gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'A';
			}
			else
			{
				buff_name[counter] = 'a';
			}
			counter++;
		break;

		case B:
/*		0x02 = 0b02
			- Buchstabe B gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'B';
			}
			else
			{
				buff_name[counter] = 'b';
			}
			counter++;
		break;
	
		case C:
/*		0x03 = 0b03
			- Buchstabe C gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'C';
			}
			else
			{
				buff_name[counter] = 'C';
			}
			counter++;
		break;
	
		case D:
/*		0x04 = 0b04
			- Buchstabe D gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'D';
			}
			else
			{
				buff_name[counter] = 'd';
			}
			counter++;
		break;
	
		case E:
/*		0x05 = 0b05
			- Buchstabe E gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'E';
			}
			else
			{
				buff_name[counter] = 'e';
			}
			counter++;
		break;
	
		case F:
/*		0x06 = 0b06
			- Buchstabe F gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'F';
			}
			else
			{
				buff_name[counter] = 'f';
			}
			counter++;
		break;

		case G:
/*		0x07 = 0b07
			- Buchstabe G gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'G';
			}
			else
			{
				buff_name[counter] = 'g';
			}
			counter++;
		break;

		case H:
/*		0x08 = 0b08
			- Buchstabe H gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'H';
			}
			else
			{
				buff_name[counter] = 'h';
			}
			counter++;
		break;

		case I:
/*		0x09 = 0b09
			- Buchstabe I gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'I';
			}
			else
			{
				buff_name[counter] = 'i';
			}
		counter++;
		break;

		case J:
/*		0x0A = 0b10
			- Buchstabe J gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'J';
			}
			else
			{
				buff_name[counter] = 'j';
			}
			counter++;
		break;

		case K:
/*		0x0B = 0b11
			- Buchstabe K gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'K';
			}
			else
			{
				buff_name[counter] = 'k';
			}
			counter++;
		break;

		case L:
/*		0x0C = 0b12
			- Buchstabe L gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'L';
			}
			else
			{
				buff_name[counter] = 'l';
			}
			counter++;
		break;

		case M:
/*		0x0D = 0b13
			- Buchstabe M gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'M';
			}
			else
			{
				buff_name[counter] = 'm';
			}
			counter++;
		break;

		case N:
/*		0x0E = 0b14
			- Buchstabe N gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'N';
			}
			else
			{
				buff_name[counter] = 'n';
			}
			counter++;
		break;

		case O:
/*		0x0F = 0b15
			- Buchstabe O gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'O';
			}
			else
			{
				buff_name[counter] = 'o';
			}
			counter++;
		break;

		case P:
/*		0x10 = 0b16
			- Buchstabe P gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'P';
			}
			else
			{
				buff_name[counter] = 'p';
			}
		counter++;
		break;

		case Q:
/*		0x11 = 0b17
			- Buchstabe Q gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'Q';
			}
			else
			{
				buff_name[counter] = 'q';
			}
			counter++;
		break;

		case R:
/*		0x12 = 0b18
			- Buchstabe R gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'R';
			}
			else
			{
				buff_name[counter] = 'r';
			}
			counter++;
		break;

		case S:
/*		0x13 = 0b19
			- Buchstabe S gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'S';
			}
			else
			{
				buff_name[counter] = 's';
			}
			counter++;
		break;

		case T:
/*		0x14 = 0b20
			- Buchstabe T gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'T';
			}
			else
			{
				buff_name[counter] = 't';
			}
			counter++;
		break;

		case U:
/*		0x15 = 0b21
			- Buchstabe U gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'U';
			}
			else
			{
				buff_name[counter] = 'u';
			}
			counter++;
		break;

		case V:
/*		0x16 = 0b22
			- Buchstabe V gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'V';
			}
			else
			{
				buff_name[counter] = 'v';
			}
			counter++;
		break;

		case W:
/*		0x17 = 0b23
			- Buchstabe W gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'W';
			}
			else
			{
				buff_name[counter] = 'w';
			}
			counter++;
		break;

		case X:
/*		0x18 = 0b24
			- Buchstabe X gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'X';
			}
			else
			{
				buff_name[counter] = 'x';
			}
			counter++;
		break;

		case Y:
/*		0x19 = 0b25
			- Buchstabe Y gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'Y';
			}
			else
			{
				buff_name[counter] = 'y';
			}
			counter++;
		break;

		case Z:
/*		0x1A = 0b26
			- Buchstabe Z gross/klein in buff_name[counter] schreiben
			- Counter inkrementieren für nächste Buchstabenposition des Namens
*/
			if (Grossschreib == 1)
			{
				buff_name[counter] = 'Z';
			}
			else
			{
				buff_name[counter] = 'z';
			}
			counter++;
		break;

		case Fs:
/*		0x1B = 0b27
			- Gross-/Kleinschreibung am Ende der Routine wechseln
*/
			wechsel = 1;
		break;

		case DEL:
/*		0x1C = 0b28
			- Counter vorverschieben
			- String-Terminator setzen
*/
			counter--;
			buff_name[counter] = '\0';
		break;

		case ABBRECHEN4:
/*		0x1D = 0b29
			- Erstes File aus der Liste holen und in aktuellesGetraenk speichern
			- Buffer für neuen Cocktail-Name rücksetzen
			- Startanzeige setzen
*/
			lese_textfile_in_getraenk(tail_getraenk_file->file);
			counter = 0;
			for (int i = 0 ; i <20 ; i ++)
			{
				buff_name[i] = '\0';
			}
			setze_startanzeige(aktuellesGetraenk);
		break;

		case LEERZEICHEN:
/*		0x1E = 0b30
			- Leerzeichen in buff_name[counter] schreiben
*/
			buff_name[counter]= ' ';
		break;

		case OK:
/*		0x1F = 0b31
			- Erstanzeige2 setzen
			- Mengen des neuen Getränks auf 0 setzen
			- Counter für Buchstaben auf 0 setzen
			- Listenabschnitt auf den Ersten setzen
			- Zutaten in Liste schreiben
*/
			nextion_change_page(ERSTANZEIGE2);
			for (int i = 0 ; i < 12 ; i++)
			{
				*(aktuellesGetraenk->mengen + i) = 0;
			}
			counter = 0;
			i_Liste = 0;
			erstelle_Liste_zutat("zutat");
		break;
	}
	
/*		Immer ausführen
			- Falls goss/klein-Wechsel ansteht, Gross/Klein-Variable ändern
			- Gesamter bisheriger name (buff_name) anzeigen
			- Enthält der Name 20 Buchstaben, bleibt der counter, der letzte Buchstabe wird immer überschrieben vom nächsten
*/
	if (wechsel == 1)
		{
		if (Grossschreib == 1)
		{
			Grossschreib = 0;
		}
		else
		{
			Grossschreib = 1;
		}
	}
	
	nextion_setText("neuername",(char *)buff_name);
	
	if (counter >= 19)
	{
		counter = 19;
	}
}

void check_erstanzeige2(uint8_t button)
{
/*
	Die hier vorkommenden Einstellungsmöglichkeiten dieser Seite besitzen
	gemäss Nextion-Editor dieselben Slider/Textfelder etc wie auf der
	Seite Ceinstanzeige. Bis auf den Speichern-Button haben alle die selbe
	Funktion. Deswegen werden auch die selben ID's gesendet, wie auf der
	Ceinstanzeigen-seite und somit auch diese schon geschriebenen
	Funktionen. Der Speichern-Button wird im folgenden aufgeführt.
*/
	
	
	// Initialisierung für Erstellung eines neuen Getränkefiles
	getraenk_file_t * tmp2;
	
	switch (button)
	{
		case ABBRECHEN5:
/*		0x01 = 0b01
			- Startanzeige setzen
			- Listenabschnitt auf 0 setzen
*/
			setze_startanzeige(aktuellesGetraenk);
			i_Liste = 0;
		break;
	
		case SPEICHERN2:
/*		0x02 = 0b02
			- buff_name in aktuellesGetraenk kopieren (vorherige Seite)
			- (Mengen sind schon in aktuellemGetraenk (vorherige Setie))
			- Bild aktuellesGetranenk für User-Cocktail default auf 24
			- Falls eine der Zutaten alkoholhaltig ist, ist alkohol = 1
			- Nummer des nächsten nicht existierenden Files finden
			- AktuellesGetraenk in File abspeichern und auf SD ablegen
			- Auf Startanzeige wechseln
			- counter für buff_name auf 0 setzen
			- i_Liste für Listenabschnitt auf 0 setzen
			- buff_name auf '\0' initialisieren für nächstes Getränk
*/
			strcpy(aktuellesGetraenk->name, (const char *)buff_name);
			aktuellesGetraenk->picture = 24;
			uint8_t alkohol = 0;
			aktuelleZutatInMaschine = tail_zut_in_Maschine;
			do 
			{
				if (*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->position) > 0)
				{
					if (aktuelleZutatInMaschine->alkohol == 1)
					{
						alkohol = 1;
					}
				}
				aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
			} while (aktuelleZutatInMaschine!= tail_zut_in_Maschine);
			aktuellesGetraenk->alkohol = alkohol;
		
			// Suche von 1 bis 100 durch die Files
			for (int8_t count = 1 ; count <= 100; count++){

			// Text erstellen, um File-Nr. zu suchen.
			char buff[15] = {'\0'};
			itoa(count, (char *)buff,10);
			strcat((char *)buff, (const char *)".txt");
				
			// Erstes nicht existierendes File suchen
			if(readFile(VERIFY, (unsigned char *)buff)!=1)
			{
				// File speichern
				erstelle_File(count, buff_name, 1);
				tmp2 = create_new_getraenk_file(count);
				head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
				count = 100;
				aktuellesGetraenk_file = head_getraenk_file;
				lese_textfile_in_getraenk(head_getraenk_file->file);
			}
		}
		setze_startanzeige(aktuellesGetraenk);
		counter = 0;
		i_Liste = 0;
		for (int i = 0 ; i <20 ; i ++)
		{
			buff_name[i] = '\0';
		}
		break;
	}
}

void check_loeschanzeige(uint8_t button)
{
	switch (button)
	{
		case JA:
/*		0x01 = 0b01
			- Wenn das File das tail-File ist, muss das File vor dem tail-File das neue tail-File werden
			- Wenn das File das head-File ist, muss das File nach dem head-File das neue head-File werden
			- Die folgenden/vorausgehenden Files werden reorganisiert
			- String für zu löschendes File wird generiert
			- Das File wird gelöscht
			- Das nächste Getränk wird in das aktuelleGetraenk geladen
			- Startanzeige setzen
*/
			if (aktuellesGetraenk_file == tail_getraenk_file)
			{
				tail_getraenk_file = aktuellesGetraenk_file->prev;
			}
			else if (aktuellesGetraenk_file == head_getraenk_file)
			{
				head_getraenk_file = aktuellesGetraenk_file->next;	
			}
			(aktuellesGetraenk_file->prev)->next = aktuellesGetraenk_file->next;
			(aktuellesGetraenk_file->next)->prev = aktuellesGetraenk_file->prev;
			
			char buff[20];
			itoa(aktuellesGetraenk_file->file, (char *)buff, 10);
			strcat((char *) buff,(const char *)".txt");
			
			deleteFile((unsigned char *)buff);
			
			aktuellesGetraenk_file = aktuellesGetraenk_file->next;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case NEIN:
/*		0x02 = 0b02
			- Startanzeige setzen
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
	}	
}

void check_posanzeige(uint8_t button)
{
	i_Liste = 0;
	switch (button)
	{
		case B0:
/*		0x01 = 0b01
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 0 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(0);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B1:
/*		0x02 = 0b02
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 1 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(1);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B2:
/*		0x03 = 0b03
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 2 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(2);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B3:
/*		0x04 = 0b04
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 3 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(3);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B4:
/*		0x05 = 0b05
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 4 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(4);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B5:
/*		0x06 = 0b06
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 5 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(5);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B6:
/*		0x07 = 0b07
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 6 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(6);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B7:
/*		0x08 = 0b08
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 7 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(7);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B8:
/*		0x09 = 0b09
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 8 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(8);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B9:
/*		0x0A = 0b10
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 9 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(9);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B10:
/*		0x0B = 0b11
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 10 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(10);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B11:
/*		0x0C = 0b12
			- Wechsle auf Flüssigkeitsanzeige1
			- Auf ausgewählte Position zeigen (Pos 11 in Liste), damit die Zutat darin abgelegt werden kann
			- Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
*/
			nextion_change_page(FLUESSANZEIGE1);
			setze_aktuelle_Zutat_in_Maschine_prev(11);
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case ZURUECK3:
/*		0x0D = 0b13
			- Wechsle auf Menuanzeige
*/
			nextion_change_page(MENUANZEIGE);
		break;
	}
}

void check_fluessanzeige1(uint8_t button)
{
	switch (button)
	{
		case FLUESSIGKEIT1:
/*		0x01 = 0b01
			- Lese File an Stelle 0 der Liste und setze Status VOLL
*/
			setze_Fluessgkeit_in_Position(0, VOLL);
		break;
		
		case FLUESSIGKEIT2:
/*		0x02 = 0b02
			- Lese File an Stelle 1 der Liste und setze Status VOLL
*/		
			setze_Fluessgkeit_in_Position(1, VOLL);
		break;
		
		case FLUESSIGKEIT3:
/*		0x03 = 0b03
			- Lese File an Stelle 2 der Liste und setze Status VOLL
*/
			setze_Fluessgkeit_in_Position(2, VOLL);
		break;
		
		case FLUESSIGKEIT4:
/*		0x04 = 0b04
			- Lese File an Stelle 3 der Liste und setze Status VOLL
*/
			setze_Fluessgkeit_in_Position(3, VOLL);
		break;
		
		case FLUESSIGKEIT5:
/*		0x05 = 0b05
			- Lese File an Stelle 4 der Liste und setze Status VOLL
*/
			setze_Fluessgkeit_in_Position(4, VOLL);
		break;
		
		case FLUESSIGKEIT6:
/*		0x06 = 0b06
			- Lese File an Stelle 5 der Liste und setze Status VOLL
*/
			setze_Fluessgkeit_in_Position(5, VOLL);
		break;
		
		case RAUFLIST5:
/*		0x07 = 0b07
			- Untere Blockierung aufheben
			- Gehe Liste um 6 Getränke hoch, falls nicht schon am oberen Ende
			- Schreibe Cocktailnamen in die Liste*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 6;
				erstelle_Liste_Zutat_Pos("fluessigkeit");
			}
		break;
		
		case RUNTERLIST5:
/*		0x08 = 0b08
			- Obere Blockierung aufheben
			- Gehe Liste um 6 Getränke runter, falls nicht schon am unteren Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 6;
				erstelle_Liste_Zutat_Pos("fluessigkeit");
			}
		break;
		
		case NEUEFLUESSIGKEIT:
/*		0x09 = 0b09
			- Fluessanzeige2 setzen
			- i_Liste für Listenabschnitt auf 0 setzen
*/
			nextion_change_page(FLUESSANZEIGE2);
			i_Liste = 0;
		break;
		
		case KEINEFLUESSIGKEIT:
/*		0x0A = 0b10
			- Flüssigkeit ausserhalb des Listenbereichs bedeutet keine Flüssigkeit, deshalb 6
			- Der Status der Flüssigkeit ist KEINGETRAENK
*/
			setze_Fluessgkeit_in_Position(6, KEINGETRAENK);
		break;
		
		case ZURUECK4:
/*		0x0B = 0b11
			- Posanzeige setzen
			- Färbe die Nummern der Positionen gemäss Status
			- i_Liste für Listenabschnitt auf 0 setzen
*/
			i_Liste = 0;
			nextion_change_page(POSANZEIGE);
			setze_Posanzeige_Rot_Gruen();
		break;
	}
}

void check_fluessanzeige2(uint8_t button)
{
/*
	Die hier vorkommenden Einstellungsmöglichkeiten dieser Seite besitzen
	gemäss Nextion-Editor dieselben Buttons wie auf der
	Seite Erstanzeige1. Bis auf den Weiter-Button haben alle die selbe
	Funktion. Deswegen werden auch die selben ID's gesendet, wie auf der
	Erstanzeige1-seite und somit auch diese schon geschriebenen
	Funktionen. Der Weiter-Button wird im folgenden aufgeführt.
*/
	switch (button)
	{
		case 1:
/*		0x01 = 0b01
			- FLUESSANZEIGE3 setzen
			- Name in aktuellesGetraenk schreiben
			- i_Liste für Listenabschnitt auf 0 setzen
*/
			nextion_change_page(FLUESSANZEIGE3);
			uint8_t len = strlen((const char *)buff_name);
			for (int count = 0 ; count < len + 1; count++)
			{
				*(aktuelle_zutat->name + count) = *(buff_name + count);
			}
			counter = 0;
		break;
	}
}

void check_fluessanzeige3(uint8_t button)
{
	char buff_filename[15] = {'\0'};
	char buff_string[50] = {'\0'};
	char buff_itoa[5] = {'\0'};
	char * ptr = buff_string;
	zutat_file_t * tmp;
	switch (button)
	{
		case JA1:
		case NEIN2:
/*		0x01 = 0b01
			- String erstellen für Zutatenspeicherung
			- Freies File suchen, erstellen und auf SD-Karte ablegen
			- Erstellte Zutat in der Liste einfügen
*/
			strcpy(ptr, (const char *)"Name:");
			strcat(ptr, (const char *)aktuelle_zutat->name);
			strcat(ptr, (const char *)"\rAlkohol:");
			if (button == JA1)
			{
				itoa(1, (char *)buff_itoa, 10);
			}
			if (button == NEIN2)
			{
				itoa(0, (char *)buff_itoa, 10);
			}
			strcat(ptr, (const char *)buff_itoa);
			strcat(ptr, (const char *)"~");
			
			uint8_t stop_suche = 0;
			uint8_t count = 1;
			while (stop_suche == 0)
			{
				// String mit Name des Textfiles erstellen (Z0.txt bis Z199.txt)
				strcpy((char *)buff_filename, (const char *)"Z");
				itoa(count, (char *)buff_itoa, 10);
				strcat((char *)buff_filename, (const char *)buff_itoa);
				strcat((char *)buff_filename, (const char *)".txt");
				
				// Prüfen ob File existiert
				if(readFile(VERIFY, (unsigned char *)buff_filename)!=1)
				{
					// Nummer des Existierenden Files in der Liste ablegen (head_zutat = letzt hinzugefügtes Getränk)
					tmp = create_new_zutat_file(count);
					head_zutat_file = insert_zutat_file_at_head(&head_zutat_file, tmp);
					stop_suche = 1;
					count--;
				}
				count++;
			}
			strcpy((char *)buff_filename, (const char *)"Z");
			itoa(count, (char *)buff_itoa, 10);
			strcat((char *)buff_filename, (const char *)buff_itoa);
			strcat((char *)buff_filename, (const char *)".txt");
			writeFile((unsigned char *)buff_filename, (unsigned char *)ptr);
			
// 			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			block_list_runter = 0;
			block_list_hoch = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
			uint8_t len = strlen((const char *)buff_name);
			for (int count = 0 ; count < len + 1; count++)
			{
				*(aktuellesGetraenk->name + count) = '\0';
			}
		break;
		
		case ZURUECK7:
/*		0x0A = 0b10
			- FLUESSANZEIGE3 setzen
			- Name in aktuellesGetraenk schreiben
			- i_Liste für Listenabschnitt auf 0 setzen
*/
			nextion_change_page(FLUESSANZEIGE2);
		break;
	}
}

void check_RFIDAnzeige1(uint8_t button)
{
	switch (button)
	{
		case RFID1:
/*		0x01 = 0b01
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RFID2:
/*		0x02 = 0b02
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RFID3:
/*		0x03 = 0b03
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RFID4:
/*		0x04 = 0b04
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RFID5:
/*		0x05 = 0b05
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RFID6:
/*		0x06 = 0b06
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(RFIDANZEIGE2);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
		break;
		
		case RAUFLIST6:
/*		0x07 = 0b07
			- Wechsle auf Zutatenanzeige
			-
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}
		break;
		
		case RUNTERLIST6:
/*		0x08 = 0b08
			- Wechsle auf Zutatenanzeige
			-
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 8;
				erstelle_Liste_name("cocktail");
			}
		break;
		
		case ZURUECK5:
/*		0x09 = 0b09
			- Wechsle auf Zutatenanzeige
			-
*/
			nextion_change_page(STARTANZEIGE);
			i_Liste = 0;
		break;
	}
}

void check_RFIDAnzeige2(uint8_t button)
{
	switch (button)
	{
/*		0x01 bis 0x08 = 0b01 bis 0b08
			- Wähle x-ten Cocktail des aktuellen Listenabschnitts
*/
		case COCKTAIL1:
			setze_startanzeige(aktuellesGetraenk);
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
		
		case RAUFLIST1:
/*		0x09 = 0b09
			- Untere Blockierung aufheben
			- Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}		
		break;
		
		case RUNTERLIST1:
/*		0x0A = 0b10
			- Obere Blockierung aufheben
			- Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
			- Schreibe Cocktailnamen in die Liste
*/
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 8;
				erstelle_Liste_name("cocktail");
			}	
		break;
	}
	
}

void check_RFIDFehler(uint8_t button)
{
	switch (button)
	{
		case 1:
			setze_startanzeige(aktuellesGetraenk);
		break;
	}
}