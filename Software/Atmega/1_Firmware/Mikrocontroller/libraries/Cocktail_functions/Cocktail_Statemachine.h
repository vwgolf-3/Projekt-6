/*
 * Cocktail_Statemachine.h
 *
 * Created: 07.06.2020 17:09:08
 *  Author: kimsc
 */ 



#ifndef COCKTAIL_STATEMACHINE_H_
#define COCKTAIL_STATEMACHINE_H_

#include "Cocktail_functions.h"

// Initialisierungen
void init_Getraenke_func();

// Commands Display/ESP
void cocktail_check_command(int8_t page_in, int8_t button_in);

// Subfunktionen
void check_startseite(uint8_t button);
void check_zutatenanzeige(uint8_t button);
void check_listenanzeige(uint8_t button);
void choose_aktuellesGetraenk(uint8_t nr);
void check_zubabfrage(uint8_t button);
void check_zubbildschirm(uint8_t button);
void check_menuanzeige(uint8_t button);
void check_bearbeitungsanzeige(uint8_t button);
void check_ceinstanzeige(uint8_t button);
void check_reinanzeige1(uint8_t button);
void check_reinanzeige2(uint8_t button);
void check_reinanzeige3(uint8_t button);
void check_infoanzeige(uint8_t button);
void check_fehleranzeige(uint8_t button);
void check_erstanzeige1(uint8_t button);
void check_erstanzeige2(uint8_t button);
void check_loeschanzeige(uint8_t button);
void check_posanzeige(uint8_t button);
void check_fluessanzeige1(uint8_t button);
void check_fluessanzeige2(uint8_t button);
void check_fluessanzeige3(uint8_t button);
void check_RFIDAnzeige1(uint8_t button);
void check_RFIDAnzeige2(uint8_t button);
void check_RFIDFehler(uint8_t button);
void check_ESP32(uint8_t button);


uint8_t test2;

#endif /* COCKTAIL_STATEMACHINE_H_ */