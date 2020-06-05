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

enum GUI_Pages{STARTANZEIGE = 1, ZUTATENANZEIGE, LISTENANZEIGE, ZUBABFRAGE, ZUBBILDSCHIRM, BEREITANZEIGE, MENUANZEIGE, BEARBEITUNGSANZEIGE, CEINSTANZEIGE, REINANZEIGE1, REINANZEIGE2, REINANZEIGE3, INFOANZEIGE, ABBRUCHANZEIGE, FEHLERANZEIGE, ERSTANZEIGE1, ERSTANZEIGE2, LOESCHABFRAGE}gui_pages;
enum Startaneige_Buttons{COCKTAILNAME = 1, ZUTATEN, LINKS, B3, RECHTS, LISTE, MENU, ALKOHOLJANEIN}gui_buttons_0;
enum Zutatenanzeige_Buttons{OKZUTATEN = 1, ZUTATENLISTE};
enum Listenanzeige_Buttons{COCKTAIL1 = 1, COCKTAIL2, COCKTAIL3, COCKTAIL4, COCKTAIL5, COCKTAIL6, COCKTAIL7, COCKTAIL8, RAUFLIST1, RUNTERLIST1};
enum Zubabfrage_Buttons{KLEIN = 1, GROSS, ABBRUCHZUBAB};
enum Zubbildschirm_Buttons{ABBRUCHZUB};
enum Menuanzeige_Buttons{COCKTAILBEARBEITEN = 1, COCKTAILERSTELLEN, MASCHINEREINIGEN, MASCHINENINFO, ZURUECK1};
enum Bearbeitungsanzeige{BEARBCOCKTAIL1 = 1, BEARBCOCKTAIL2, BEARBCOCKTAIL3, BEARBCOCKTAIL4, BEARBCOCKTAIL5, BEARBCOCKTAIL6, BEARBCOCKTAIL7, BEARBCOCKTAIL8, RAUFLIST2, RUNTERLIST2};
enum Ceinstanzeige_Buttons{RAUFLIST3= 1, RUNTERLIST3, STANDARDEINST, SPEICHERN1};
enum Reinanzeige1_Buttons{ABBRECHEN1 = 1, WEITER1};
enum Reinanzeige2_Buttons{ABBRECHEN2 = 1, WEITER2};
enum Reinanzeige3_Buttons{ABBRECHEN3 = 1, WEITER3};
enum Infoanzeige_Buttons{ZURUECK2 = 1};
enum Fehleranzeige_Buttons{ERLEDIGT = 1};
enum Erstanzeige1_Buttons{A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Fs, DEL, ABBRECHEN4, LEERZEICHEN, OK};
enum Erstanzeige2_Buttons{SLIDER11 = 1, SLIDER12, SLIDER13, SLIDER14, RAUFLIST4, RUNTERLIST4, SPEICHERN2, ABBRECHEN5};
enum Loeschabfrage{JA = 1, NEIN};	
	

void endConversation(void);
void nextion_change_page(char page);
void nextion_setText(char * object, char * text);
void nextion_setValue( char * object,  char * text);
void nextion_setPicture( char * x,  char * y,  char * picture);
uint8_t nextion_getSliderValue(char * object, unsigned char * INPUT);
void nextion_disableButton(char * object);


#endif /* NEXTION_DISPLAY_H_ */