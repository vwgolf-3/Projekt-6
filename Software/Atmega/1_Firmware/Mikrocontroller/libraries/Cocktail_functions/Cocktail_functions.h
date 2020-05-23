/*
 * Cocktail_functions.h
 *
 * Created: 07.03.2020 13:45:25
 *  Author: kimsc
 */ 


#ifndef COCKTAIL_FUNCTIONS_H_
#define COCKTAIL_FUNCTIONS_H_

#include "../../utils/pin_defs.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "Zutaten.h"
#include "Getraenk.h"
#include "../TMC6200/TMC6200.h"
#include "../SD-Karte/SD_routines.h"
#include "../SD-Karte/FAT32.h"

// Initialisierungen
void init_Getraenke_func();

// Commands Display/ESP
void cocktail_check_command(char page, char button);

// Zubereitung
void fuelle_getraenk(uint16_t fuellmenge);
void schalte_pumpe_aus(uint8_t Pumpe);
void schalte_pumpe_ein(uint8_t Pumpe);

// Anzeige Display
void setze_startanzeige(getraenk_t * anzeige_getraenk);
void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk);

// Getränke-Pointer
getraenk_t * shift_getraenk(getraenk_t *getraenk_to_shift, uint8_t ngetr, uint8_t down_up);

// SD-Karte
uint8_t compare_string(char *first, char *second);
uint8_t pruefe_kopf(char * beginn, char string[]);
void lese_textfile_in_getraenk(uint8_t file);

// Testfunktion
void cocktail_test_command(unsigned char INPUT[256]);

#endif /* COCKTAIL_FUNCTIONS_H_ */