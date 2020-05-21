/*
 * Nextion_Display.h
 *
 * Created: 02.01.2020 18:14:22
 *  Author: kimsc
 */ 


#ifndef NEXTION_DISPLAY_H_
#define NEXTION_DISPLAY_H_

#include <stdlib.h>

#include "../../libraries/UART/UART.h"

#define UART_PORT_PC 0
#define UART_PORT_DISPLAY 1
#define UART_PORT_ESP 2
#define UART_PORT_RFID 3

#define DEBUG_DISPLAY 0

enum GUI_Pages{STARTANZEIGE = 1, ZUTATENANZEIGE, LISTENANZEIGE, ZUBABFRAGE, ZUBBILDSCHIRM, BEREITANZEIGE, MENUANZEIGE, BEARBEITUNGSANZEIGE, CEINSTANZEIGE, REINANZEIGE1, REINANZEIGE2, REINANZEIGE3, INFOANZEIGE, ABBRUCHANZEIGE, FEHLERANZEIGE, ERSTANZEIGE1, ERSTANZEIGE2}gui_pages;
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

void endConversation(void);
void nextion_setText(char * object, char * text);
void nextion_change_page(char page);
void nextion_setValue( char * object,  char * text);
void nextion_setPicture( char * x,  char * y,  char * picture);


#endif /* NEXTION_DISPLAY_H_ */