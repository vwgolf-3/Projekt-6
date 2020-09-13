/*
 * Nextion_Display.h
 *
 * Created: 02.01.2020 18:14:22
 *  Author: kimsc
 */


#ifndef NEXTION_DISPLAY_H_
#define NEXTION_DISPLAY_H_

#include <stdlib.h>
#include "../Main_functions/Main_Func.h"
#include "../../libraries/UART/UART.h"

#define UART_PORT_PC 0
#define UART_PORT_DISPLAY 1
#define UART_PORT_ESP 2
#define UART_PORT_RFID 3

#define DEBUG_DISPLAY 0

enum GUI_Pages {STARTANZEIGE = 1, ZUTATENANZEIGE, LISTENANZEIGE, ZUBABFRAGE, ZUBBILDSCHIRM, BEREITANZEIGE, MENUANZEIGE, BEARBEITUNGSANZEIGE, CEINSTANZEIGE, REINANZEIGE1, REINANZEIGE2, REINANZEIGE3, INFOANZEIGE, ABBRUCHANZEIGE, FEHLERANZEIGE, ERSTANZEIGE1, ERSTANZEIGE2, LOESCHABFRAGE, POSANZEIGE, FLUESSANZEIGE1, FLUESSANZEIGE2, FLUESSANZEIGE3, RFIDANZEIGE1, RFIDANZEIGE2, RFIDFEHLER, ESP32_PAGE, LED_PAGE, FLUESSANZEIGE4} gui_pages;
enum Startaneige_Buttons {COCKTAILNAME = 1, ZUTATEN, LINKS, B33, RECHTS, LISTE, MENU, ALKOHOLJANEIN, LOESCHEN};
enum Zutatenanzeige_Buttons {OKZUTATEN = 1, ZUTATENLISTE};
enum Listenanzeige_Buttons {COCKTAIL1 = 1, COCKTAIL2, COCKTAIL3, COCKTAIL4, COCKTAIL5, COCKTAIL6, RAUFLIST1, RUNTERLIST1, ZURUECK9};
enum Zubabfrage_Buttons {KLEIN = 1, GROSS, ABBRUCHZUBAB};
enum Zubbildschirm_Buttons {ABBRUCHZUB = 1};
enum Menuanzeige_Buttons {COCKTAILBEARBEITEN = 1, COCKTAILERSTELLEN, MASCHINEREINIGEN, MASCHINENINFO, ZURUECK1, FLUESSPOS, RFID, LED_BUTTON};
enum Bearbeitungsanzeige {BEARBCOCKTAIL1 = 1, BEARBCOCKTAIL2, BEARBCOCKTAIL3, BEARBCOCKTAIL4, BEARBCOCKTAIL5, BEARBCOCKTAIL6, RAUFLIST2, RUNTERLIST2, ZURUECK10, STANDARDEINST};
enum Ceinstanzeige_Buttons {RAUFLIST3= 1, RUNTERLIST3, SPEICHERN1, SLIDER01, SLIDER02, SLIDER03, SLIDER04, ABBRECHEN6};
enum Reinanzeige1_Buttons {ABBRECHEN1 = 1, WEITER1};
enum Reinanzeige2_Buttons {ABBRECHEN2 = 1, WEITER2};
enum Reinanzeige3_Buttons {ABBRECHEN3 = 1, WEITER3};
enum Infoanzeige_Buttons {ZURUECK2 = 1};
enum Fehleranzeige_Buttons {ERLEDIGT = 1};
enum Erstanzeige1_Buttons {A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Fs, DEL, ABBRECHEN4, LEERZEICHEN, OK};
enum Erstanzeige2_Buttons {ABBRECHEN5 = 1, SPEICHERN2};
enum Erstanzeige3_Buttons {JA1 = 1, NEIN1, ZURUECK7};
enum Erstanzeige4_Buttons {JA2 = 1, NEIN2, ZURUECK11};
enum Loeschabfrage {JA = 1, NEIN};
enum Posanzeige {B0 = 1, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, ZURUECK3};
enum Fluessanzeige1 {FLUESSIGKEIT1 = 1, FLUESSIGKEIT2, FLUESSIGKEIT3, FLUESSIGKEIT4, FLUESSIGKEIT5, FLUESSIGKEIT6, RAUFLIST5, RUNTERLIST5, NEUEFLUESSIGKEIT, KEINEFLUESSIGKEIT, ZURUECK4};
enum RFIDanzeige1 {RFID1 = 1, RFID2, RFID3, RFID4, RFID5, RFID6, RAUFLIST6, RUNTERLIST6, ZURUECK5};
enum RFIDFehler {ZURUECK6 = 1};
enum ESP32 {TAGNR = 1, GETRAENKE, ZUTATEN2, XXX, YYY};
enum LED {WEISS = 1, RAINBOW, CUSTOM, ZURUECK8, SLIDER11, SLIDER12, SLIDER13, SLIDER14};

void endConversation(void);
void nextion_change_page(char page);
void nextion_setText(char * object, char * text);
void nextion_setValue( char * object,  char * text);
void nextion_setPicture( char * x,  char * y,  char * picture);
uint8_t nextion_getSliderValue(char * object, unsigned char * INPUT);
void nextion_disableButton(char * object);
void nextion_enableButton(char * object);
void nextion_visible_off(char * object);
void nextion_visible_on(char * object);

#endif /* NEXTION_DISPLAY_H_ */