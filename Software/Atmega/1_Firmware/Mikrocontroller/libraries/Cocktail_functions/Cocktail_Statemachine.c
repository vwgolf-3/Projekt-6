

#include "Cocktail_Statemachine.h"

void init_Getraenke_func()
{
	nextion_change_page(STARTANZEIGE);
	setze_startanzeige(aktuellesGetraenk);
	test2 = 0;
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
	case RFIDANZEIGE1:
	check_RFIDAnzeige1(button);
	break;
	
	/*0x17 = 0d23*/
	case RFIDANZEIGE2:
	check_RFIDAnzeige2(button);
	break;
	
	/*0x18 = 0d24*/
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
			- Schreibe File in aktuelles Getränk
			- Setze Startanzeige
*/
			aktuellesGetraenk_file = tail_getraenk_file;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			switch(Liste)
			{
				case ALLE:
				Liste = ALKOHOL;
				while (aktuellesGetraenk->alkohol == 0)
				{
					schiebe_file_prev();
				}
				break;
				
				case ALKOHOL:
				Liste = ALKOHOLFREI;
				while (aktuellesGetraenk->alkohol == 1)
				{
					schiebe_file_prev();
				}
				break;
				
				case ALKOHOLFREI:
				Liste = ALLE;
				break;
			}
			setze_startanzeige(aktuellesGetraenk);
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
	for (uint32_t i = 0 ; i < 12 ; i ++)
	{
		*(aktuellesGetraenk->mengen + i) = '\0';
	}
	*(aktuellesGetraenk->mengen + test2) = (uint8_t)100;
	zubereitung_getraenk((uint32_t)3);
	test2++;
		break;
		
		case GROSS:
/*		0x02 = 0b02
			- Getränk mit 5dl zubereiten
*/
		
	for (uint32_t i = 0 ; i < 12 ; i ++)
	{
		*(aktuellesGetraenk->mengen + i) = '\0';
	}
	*(aktuellesGetraenk->mengen + test2) = (uint8_t)100;
	zubereitung_getraenk((uint32_t)5);
	test2++;
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
			- Setze Startabzeige
*/
		nextion_change_page(POSANZEIGE);
		break;
		
		case RFID:
/*		0x07 = 0b07
			- Setze Startabzeige
*/
		nextion_change_page(RFIDANZEIGE1);
		erstelle_Liste_name("cocktail");
		break;


	}
}

void check_bearbeitungsanzeige(uint8_t button)
{
	switch (button)
	{
		case BEARBCOCKTAIL1:
			bearbeite_Cocktail(0);
		break;
		
		case BEARBCOCKTAIL2:
			bearbeite_Cocktail(1);
		break;
		
		case BEARBCOCKTAIL3:
			bearbeite_Cocktail(2);
		break;
		
		case BEARBCOCKTAIL4:
			bearbeite_Cocktail(3);
		break;
		
		case BEARBCOCKTAIL5:
			bearbeite_Cocktail(4);
		break;
		
		case BEARBCOCKTAIL6:
			bearbeite_Cocktail(5);
		break;
		
		case BEARBCOCKTAIL7:
			bearbeite_Cocktail(6);
		break;
		
		case BEARBCOCKTAIL8:
			bearbeite_Cocktail(7);
		break;
		
		case RAUFLIST2:
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}
		break;
		
		case RUNTERLIST2:
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
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 4;
				erstelle_Liste_zutat("zutat");
			}
		break;
		
		case RUNTERLIST3:
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 4;
				erstelle_Liste_zutat("zutat");
			}
		break;
		
		case STANDARDEINST:
			block_list_hoch = 0;
			block_list_runter = 0;
			nextion_change_page(STARTANZEIGE);
		break;
		
		case SPEICHERN1:
			block_list_hoch = 0;
			block_list_runter = 0;
			i_Liste = 0;
			loesche_FIle(aktuellesGetraenk_file->file);
			erstelle_File(aktuellesGetraenk_file->file, aktuellesGetraenk->name, 1);
			nextion_change_page(STARTANZEIGE);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case SLIDER01:
			schreibe_Menge_in_Getraenk(0);
		break;
		
		case SLIDER02:
			schreibe_Menge_in_Getraenk(1);
		break;
		
		case SLIDER03:
			schreibe_Menge_in_Getraenk(2);
		break;
		
		case SLIDER04:
			schreibe_Menge_in_Getraenk(3);
		break;
	}
}

void check_reinanzeige1(uint8_t button)
{
	switch(button){
		
		case ABBRECHEN1:
			nextion_change_page(MENUANZEIGE);
		break;
		
		case WEITER1:
			nextion_change_page(REINANZEIGE2);
		break;
	}
}

void check_reinanzeige2(uint8_t button)
{
	switch(button)
	{
		case ABBRECHEN2:
			nextion_change_page(MENUANZEIGE);
		break;
		
		case WEITER2:
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
		nextion_change_page(MENUANZEIGE);
		stop = 1;
		break;
		
		case WEITER3:

		break;
	}
}

void check_infoanzeige(uint8_t button)
{
	switch(button)
	{
		case ZURUECK2:
			nextion_change_page(MENUANZEIGE);
		break;
	}
}

void check_fehleranzeige(uint8_t button)
{
	
}

void check_erstanzeige1(uint8_t button)
{	
	char wechsel = 0;
	switch (button)
	{
	case A:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'A';
	}else
	{
		buff_name[counter] = 'a';
	}
	counter++;
	break;

	case B:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'B';
	}else
	{
		buff_name[counter] = 'b';
	}
	counter++;
	break;

	case C:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'C';
	}else
	{
		buff_name[counter] = 'C';
	}
	counter++;
	break;

	case D:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'D';
	}else
	{
		buff_name[counter] = 'd';
	}
	counter++;
	break;

	case E:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'E';
	}else
	{
		buff_name[counter] = 'e';
	}
	counter++;
	break;

	case F:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'F';
	}else
	{
		buff_name[counter] = 'f';
	}
	counter++;
	break;

	case G:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'G';
	}else
	{
		buff_name[counter] = 'g';
	}
	counter++;
	break;

	case H:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'H';
	}else
	{
		buff_name[counter] = 'h';
	}
	counter++;
	break;

	case I:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'I';
	}else
	{
		buff_name[counter] = 'i';
	}
	counter++;
	break;

	case J:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'J';
	}else
	{
		buff_name[counter] = 'j';
	}
	counter++;
	break;

	case K:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'K';
	}else
	{
		buff_name[counter] = 'k';
	}
	counter++;
	break;

	case L:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'L';
	}else
	{
		buff_name[counter] = 'l';
	}
	counter++;
	break;

	case M:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'M';
	}else
	{
		buff_name[counter] = 'm';
	}
	counter++;
	break;

	case N:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'N';
	}else
	{
		buff_name[counter] = 'n';
	}
	counter++;
	break;

	case O:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'O';
	}else
	{
		buff_name[counter] = 'o';
	}
	counter++;
	break;

	case P:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'P';
	}else
	{
		buff_name[counter] = 'p';
	}
	counter++;
	break;

	case Q:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'Q';
	}else
	{
		buff_name[counter] = 'q';
	}
	counter++;
	break;

	case R:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'R';
	}else
	{
		buff_name[counter] = 'r';
	}
	counter++;
	break;

	case S:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'S';
	}else
	{
		buff_name[counter] = 's';
	}
	counter++;
	break;

	case T:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'T';
	}else
	{
		buff_name[counter] = 't';
	}
	counter++;
	break;

	case U:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'U';
	}else
	{
		buff_name[counter] = 'u';
	}
	counter++;
	break;

	case V:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'V';
	}else
	{
		buff_name[counter] = 'v';
	}
	counter++;
	break;

	case W:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'W';
	}else
	{
		buff_name[counter] = 'w';
	}
	counter++;
	break;

	case X:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'X';
	}else
	{
		buff_name[counter] = 'x';
	}
	counter++;
	break;

	case Y:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'Y';
	}else
	{
		buff_name[counter] = 'y';
	}
	counter++;
	break;

	case Z:
	if (Grossschreib == 1)
	{
		buff_name[counter] = 'Z';
	}else
	{
		buff_name[counter] = 'z';
	}
	counter++;
	break;

	case Fs:
		wechsel = 1;
	break;

	case DEL:
		counter--;
		buff_name[counter] = '\0';
	break;

	case ABBRECHEN4:
		lese_textfile_in_getraenk(tail_getraenk_file->file);
		counter = 0;
		for (int i = 0 ; i <20 ; i ++)
		{
			buff_name[i] = '\0';
		}
		nextion_change_page(STARTANZEIGE);
		setze_startanzeige(aktuellesGetraenk);
	break;

	case LEERZEICHEN:
		buff_name[counter]= ' ';
	break;

	case OK:
		nextion_change_page(ERSTANZEIGE2);
		for (int i = 0 ; i < 12 ; i++)
		{
			*(aktuellesGetraenk->mengen + i) = 0;
		}
		i_Liste = 0;
		erstelle_Liste_zutat("zutat");
		counter = 0;
	break;
	}
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
	getraenk_file_t * tmp2;
	char save = 1;

	switch (button)
	{
	case 4:
	
// Speicherattribute in aktuellesGetraenk übertragen.
	
	// buff_name kommt aus Textfeld der vorherigen Seiten.
	strcpy(aktuellesGetraenk->name, (const char *)buff_name);
	
	// Die Mengen kommen auch aus der vorherigen Seiten.
	
	
	// Ob Alkohol oder nicht, kann nicht gesagt werden. (default = 1)
	
	// Das Bild wird defaultmässig auf 24 gestellt (Custom Cocktail).
		aktuellesGetraenk->picture = 24;
		
// Speichervorgang
		// Suche von 1 bis 100 durch die Files
		for (int8_t i = 1 ; i <= 100; i++){
			
			// Während gesucht werden soll gilt save = 1.
			if (save)
			{
				// Text erstellen, um File-Nr. zu suchen.
				char buff[15] = {'\0'};
				itoa(i, (char *)buff,10);
				strcat((char *)buff, (const char *)".txt");
				
				// File Suchen
				if(readFile(VERIFY, (unsigned char *)buff)!=1)
				{
					erstelle_File(i, buff_name, 1);
					tmp2 = create_new_getraenk_file(i);
					head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
					save = 0;
					aktuellesGetraenk_file = head_getraenk_file;
					lese_textfile_in_getraenk(head_getraenk_file->file);
				}
			}
		}
		nextion_change_page(STARTANZEIGE);
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
		aktuellesGetraenk_file->prev->next = aktuellesGetraenk_file->next;
		aktuellesGetraenk_file->next->prev = aktuellesGetraenk_file->prev;
		char buff[20];
		itoa(aktuellesGetraenk_file->file, (char *)buff, 10);
		strcat((char *) buff,(const char *)".txt");
		deleteFile((unsigned char *)buff);
		aktuellesGetraenk_file = aktuellesGetraenk_file->next;
		lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
		setze_startanzeige(aktuellesGetraenk);
	break;
	case NEIN:
		nextion_change_page(STARTANZEIGE);
		setze_startanzeige(aktuellesGetraenk);
	break;
	}
}

void check_posanzeige(uint8_t button)
{
	switch (button)
	{
		case B0:
/*		0x01 = 0b01
			- Wechsle auf Flüssigkeitsanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B1:
/*		0x02 = 0b02
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B2:
/*		0x03 = 0b03
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B3:
/*		0x04 = 0b04
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B4:
/*		0x05 = 0b05
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B5:
/*		0x06 = 0b06
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B6:
/*		0x07 = 0b07
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B7:
/*		0x08 = 0b08
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B8:
/*		0x09 = 0b09
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B9:
/*		0x0A = 0b10
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B10:
/*		0x0B = 0b11
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case B11:
/*		0x12 = 0b12
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE1);
			i_Liste = 0;
			erstelle_Liste_Zutat_Pos("fluessigkeit");
		break;

		case ZURUECK3:
/*		0x12 = 0b12
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(STARTANZEIGE);
		break;
	}
}

void check_fluessanzeige1(uint8_t button)
{
	switch (button)
	{
		case FLUESSIGKEIT1:
/*		0x01 = 0b01
			- Wechsle auf Zutatenanzeige
			- 
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSIGKEIT2:
/*		0x02 = 0b02
			- Wechsle auf Zutatenanzeige
			- 
*/		
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSIGKEIT3:
/*		0x03 = 0b03
			- Wechsle auf Zutatenanzeige
			- 
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSIGKEIT4:
/*		0x04 = 0b04
			- Wechsle auf Zutatenanzeige
			- 
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSIGKEIT5:
/*		0x05 = 0b05
			- Wechsle auf Zutatenanzeige
			- 
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case FLUESSIGKEIT6:
/*		0x06 = 0b06
			- Wechsle auf Zutatenanzeige
			- 
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case RAUFLIST5:
/*		0x07 = 0b07
			- Wechsle auf Zutatenanzeige
			- 
*/
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 6;
				erstelle_Liste_Zutat_Pos("fluessigkeit");
			}
		break;
		
		case RUNTERLIST5:
/*		0x08 = 0b08
			- Wechsle auf Zutatenanzeige
			- 
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
			- Wechsle auf Zutatenanzeige
			- 
*/
			nextion_change_page(FLUESSANZEIGE2);
		break;
		
		case ZURUECK4:
/*		0x0A = 0b10
			- Wechsle auf Zutatenanzeige
			-
*/
			setze_startanzeige(aktuellesGetraenk);
		break;
				
	}
}


void check_fluessanzeige2(uint8_t button)
{
	switch (button)
	{
		case 31:
		nextion_change_page(FLUESSANZEIGE1);
		zutat_t * tmp;
		tmp = create_neue_zutat("12345678901234567899012",(head_zut->nr+1));
		head_zut = insert_zutat_at_head(&head_zut, tmp);
		for (int i = 0 ; i < 21 ; i++)
		{
			*(head_zut->name + i) = buff_name[i];
			buff_name[i] = '\0';
		}
		i_Liste = 0;
		erstelle_Liste_Zutat_Pos("fluessigkeit");
		counter = 0;
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