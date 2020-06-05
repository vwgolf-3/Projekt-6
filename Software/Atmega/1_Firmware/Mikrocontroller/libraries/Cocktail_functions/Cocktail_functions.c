/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */ 

#include "Cocktail_functions.h"
#include "../Main_functions/Main_Func.h"

void cocktail_test_command(unsigned char INPUT[256])
{
/*
	Diese Funktion ist eine Testfunktion, welche ausgelöst wird, wenn etwas über UART0 (PC) ankommt
*/
	Uart_Transmit_IT_PC((char *)INPUT);
	Uart_Transmit_IT_PC("\r\n");
	
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
	
		/*0x0E = 0d14*/
	case ABBRUCHANZEIGE:
		check_abbruchanzeige(button);
	break;
	
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
			aktuellesGetraenk_file = aktuellesGetraenk_file->next;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
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
			aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
			lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
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
			for (int i = 0 ; i < (i_Liste + 1) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 2) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 3) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 4) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 5) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 6) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 7) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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
			for (int i = 0 ; i < (i_Liste + 8) ; i++)
			{
				aktuellesGetraenk_file = aktuellesGetraenk_file->next;
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

void schreibe_Menge_in_Getraenk(uint8_t zutat)
{
	uint8_t val = 0;
	char buff[15] = {0};
	char buff2[5];
	char buff3[5];
	
	// String, um Slider auszuwählen
	strcpy((char *)buff, (const char *)"slider");
	itoa(zutat, (char *)buff2, 10);
	strcat((char *)buff, (const char *)buff2);
	
	// Wert aus Slider holen und in Getränkeliste eintragen
	val = nextion_getSliderValue(buff, (unsigned char *)INPUT_UART_1);
	*(aktuellesGetraenk->mengen+i_Liste+2) = val;

	// String um Text zu Setzen
	itoa((int)val, (char *)buff2, 10);
	strcat((char *)buff2, "%");
	
	// String um Textfeld auszuwählen
	strcpy((char *)buff, (const char *)"menge");
	itoa(zutat, (char *) buff3, 10);
	strcat((char *)buff, (const char *)buff3);
	
	// Text schreiben
	nextion_setText(buff,buff2);
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

void check_abbruchanzeige(uint8_t button)
{
	
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
		if (*(uint8_t *)(aktuellesGetraenk->mengen + i) > 0)
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
// 	aktuellesGetraenk = aktuellesGetraenk->next;
	
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
	nextion_change_page(STARTANZEIGE);
	setze_startanzeige(aktuellesGetraenk);	
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
	
	for (int i = i_Liste ; i < (4 + i_Liste) ; i++)
	{
		char string[21] = {'\0'};
		char string2[21] = {'\0'};
		char string3[21] = {'\0'};
		char buff[5] = {0};
			
		itoa((i-i_Liste+1),buff,10);
		strcat((char *)string, (const char *)input);
		strcat((char *)string, (const char *)buff);
		
		strcat((char *)string2, (const char *)"slider");
		strcat((char *)string2, (const char *)buff);
		
		strcat((char *)string3, (const char *)"menge");
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
	
	char string[256] = {'\0'};
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