/*
 * Cocktail_functions.h
 *
 * Created: 07.03.2020 13:45:25
 *  Author: kimsc
 */ 


#ifndef COCKTAIL_FUNCTIONS_H_
#define COCKTAIL_FUNCTIONS_H_

enum GUI_Pages{STARTANZEIGE = 1, ZUTATENANZEIGE, LISTENANZEIGE, ZUBABFRAGE, ZUBBILDSCHIRM, BREITANZEIGE, MENUANZEIGE, BEARBEITUNGSANZEIGE, CEINSTANZEIGE, REINANZEIGE1, REINANZEIGE2, REINANZEIGE3, INFOANZEIGE, ABBRUCHANZEIGE, FEHLERANZEIGE, ERSTANZEIGE1, ERSTANZEIGE2}gui_pages;
enum Startaneige_Buttons{COCKTAILNAME = 1, ZUTATEN, LINKS, B3, RECHTS, LISTE, MENU, ALKOHOLJANEIN}gui_buttons_0;


#define OKZUTATEN 2
#define ZUTATENLISTE 3
#define COCKTAIL1 1
#define COCKTAIL2 2
#define COCKTAIL3 3
#define COCKTAIL4 4
#define COCKTAIL5 5
#define COCKTAIL6 6
#define COCKTAIL7 7
#define COCKTAIL8 8
#define RAUFLIST 9
#define RUNTERLIST 10
#define KLEIN 1
#define GROSS 2
#define ABBRUCHZUBAB 3
#define ZUFALLSTEXT 1
#define ABBRUCHZUB 2
#define BEREIT 1



#include "../../pin_defs.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../../Zutaten.h"
#include "../Getraenk/Getraenk.h"
#include "../TMC6200/TMC6200.h"

void init_Getraenke_func();
void cocktail_check_command(uint8 page, uint8 button);
void cocktail_test_command(unsigned char INPUT[256]);
void fuelle_getraenk(uint16_t fuellmenge);
void setze_port(void);
void schalte_pumpe_aus(uint8_t Pumpe);
void schalte_pumpe_ein(uint8_t Pumpe);

#endif /* COCKTAIL_FUNCTIONS_H_ */