

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
	}
}

void check_startseite(uint8_t button)
{
	switch (button)
	{
		
		case ZUTATEN:
/*
				- Wechsle auf Zutatenseite
				- Setze Überschrift
*/
			nextion_change_page(ZUTATENANZEIGE);
			nextion_setText("cocktailname",aktuellesGetraenk->name);
			erstelle_Zutatenliste(aktuellesGetraenk);

		break;
			
		case LINKS:
/*
			- Wähle vorgehendes Getränk aus
			- Schreibe Name des Getränks
			- Integer to ASCI
			- Setze Bild des Getränks
*/
			switch (Liste)
			{
			case ALLE:
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			break;
			
			case ALKOHOL:
			aktuellesGetraenk_file = aktuellesGetraenk_file->next;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			while(aktuellesGetraenk->alkohol == 0)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			}
			break;
			case ALKOHOLFREI:
			aktuellesGetraenk_file = aktuellesGetraenk_file->next;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			while(aktuellesGetraenk->alkohol == 1)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			}
			break;
			}
			setze_startanzeige(aktuellesGetraenk);

			
		break;
		
		case B3:
			
			nextion_change_page(ZUBABFRAGE);
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);

		break;
		
		case RECHTS:
/*
			- Wähle nächstes Getränk aus
			- Schreibe Name des Getränks
			- Setze Bild des Getränks
*/
			switch (Liste)
			{
				case ALLE:
				aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				break;
				
				case ALKOHOL:
				aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				while(aktuellesGetraenk->alkohol == 0)
				{
					aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
					lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				}
				break;
				case ALKOHOLFREI:
				aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
				lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				while(aktuellesGetraenk->alkohol == 1)
				{
					aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
					lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				}
				break;
			}
			setze_startanzeige(aktuellesGetraenk);
				
		break;
		
		case LISTE:
		
			nextion_change_page(LISTENANZEIGE);
			i_Liste = 0;
			erstelle_Liste_name("cocktail");
			break;
		
		case MENU:
		
			nextion_change_page(MENUANZEIGE);
		
		break;
		
		case ALKOHOLJANEIN:

			aktuellesGetraenk_file = tail_getraenk_file;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
			switch(Liste)
			{
				case ALLE:
				Liste = ALKOHOL;
				while (aktuellesGetraenk->alkohol == 0)
				{
					aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
					lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				}
				break;
				
				case ALKOHOL:
				Liste = ALKOHOLFREI;
				while (aktuellesGetraenk->alkohol == 1)
				{
					aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
					lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
				}
				break;
				
				case ALKOHOLFREI:
				Liste = ALLE;
				break;
			}
			setze_startanzeige(aktuellesGetraenk);
			
		break;
		
		case LOESCHEN:
			nextion_change_page(LOESCHABFRAGE);
		break;
	}
}

void check_zutatenanzeige(uint8_t button)
{
	switch(button)
	{
		case OKZUTATEN:
			nextion_change_page(STARTANZEIGE);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case ZUTATENLISTE:
			nextion_change_page(STARTANZEIGE);
			setze_startanzeige(aktuellesGetraenk);	
		break;
	}
}

void check_listenanzeige(uint8_t button)
{
	switch (button)
	{
		case COCKTAIL1:
			choose_drink(1);
		break;
		
		case COCKTAIL2:
			choose_drink(2);
		break;
		
		case COCKTAIL3:
			choose_drink(3);	
		break;
		
		case COCKTAIL4:
			choose_drink(4);		
		break;
		
		case COCKTAIL5:
			choose_drink(5);
		break;
		
		case COCKTAIL6:
			choose_drink(6);
		break;
		
		case COCKTAIL7:
			choose_drink(7);
		break;
		
		case COCKTAIL8:
			choose_drink(8);
		break;
		
		case RAUFLIST1:
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("cocktail");
			}		
		break;
		
		case RUNTERLIST1:
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
			nextion_change_page(ZUBBILDSCHIRM);
			nextion_setText("zufallstxt", "Do stoht denn irgend e Text zum Getränk, Schwul.");
			_delay_ms(1000);
			fuelle_getraenk(5000);
			nextion_change_page(BEREITANZEIGE);
			_delay_ms(2000);
			nextion_change_page(STARTANZEIGE);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case GROSS:
			nextion_change_page(ZUBBILDSCHIRM);
			nextion_setText("zufallstxt", "Do stoht denn irgend e Text zum Getränk, Schwul.");
			_delay_ms(1000);
			fuelle_getraenk(5000);
			nextion_change_page(BEREITANZEIGE);
			_delay_ms(2000);
			nextion_change_page(STARTANZEIGE);
			setze_startanzeige(aktuellesGetraenk);
		break;
		
		case ABBRUCHZUBAB:
			nextion_change_page(STARTANZEIGE);
		break;
	}
}

void check_zubbildschirm(uint8_t button)
{
	switch (button)
	{

		case ABBRUCHZUB:
		
		break;
	}
}

void check_menuanzeige(uint8_t button)
{
	switch (button)
	{
		case COCKTAILBEARBEITEN:
		
		nextion_change_page(BEARBEITUNGSANZEIGE);
		i_Liste = 0;
		erstelle_Liste_name("bearbcocktail");
		
		break;
		
		case COCKTAILERSTELLEN:
		
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
		
		nextion_change_page(REINANZEIGE1);
		
		break;
		
		case MASCHINENINFO:
		
		nextion_change_page(INFOANZEIGE);
		
		break;
		
		case ZURUECK1:
		
		nextion_change_page(STARTANZEIGE);
		setze_startanzeige(aktuellesGetraenk);
		
		break;
	}
}

void check_bearbeitungsanzeige(uint8_t button)
{
	switch (button)
	{
		case BEARBCOCKTAIL1:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste) ; i++)
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
		break;
		
		case BEARBCOCKTAIL2:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 1) ; i++)
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
		break;
		
		case BEARBCOCKTAIL3:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 2) ; i++)
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
		break;
		
		case BEARBCOCKTAIL4:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 3) ; i++)
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
		break;
		
		case BEARBCOCKTAIL5:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 4) ; i++)
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
		break;
		
		case BEARBCOCKTAIL6:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 5) ; i++)
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
		break;
		
		case BEARBCOCKTAIL7:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 6) ; i++)
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
		break;
		
		case BEARBCOCKTAIL8:
			aktuellesGetraenk_file = tail_getraenk_file;
			for (int i = 0 ; i < (i_Liste + 7) ; i++)
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
		break;
		
		case RAUFLIST2:
			block_list_runter = 0;
			if (!block_list_hoch)
			{
				i_Liste -= 8;
				erstelle_Liste_name("bearbcocktail");
			}
		break;
		
		case RUNTERLIST2:
			block_list_hoch = 0;
			if (!block_list_runter)
			{
				i_Liste += 8;
				erstelle_Liste_name("bearbcocktail");
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
		
		case 5:
			schreibe_Menge_in_Getraenk(1);
		break;
		
		case 6:
			schreibe_Menge_in_Getraenk(2);
		break;
		
		case 7:
			schreibe_Menge_in_Getraenk(3);
		break;
		
		case 8:
			schreibe_Menge_in_Getraenk(4);
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