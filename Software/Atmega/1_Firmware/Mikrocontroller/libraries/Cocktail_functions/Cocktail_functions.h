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

unsigned char option, error, data, FAT32_active;
unsigned int i;
unsigned char fileName[13];

// Variable für Liste
uint8_t i_Liste;
uint8_t block_list_hoch;
uint8_t block_list_runter;

// Initialisierungen
void init_Getraenke_func();

// Commands Display/ESP
void cocktail_check_command(int8_t page_in, int8_t button_in);

// Zubereitung
void fuelle_getraenk(uint16_t fuellmenge);
void schalte_pumpe_aus(uint8_t Pumpe);
void schalte_pumpe_ein(uint8_t Pumpe);

// Anzeige Display
void setze_startanzeige(getraenk_t * anzeige_getraenk);
void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk);

// Getränke-Pointer
void erstelle_Liste_name(char * input);
void erstelle_Liste_zutat(char * input);

// SD-Karte
void SD_startup(void);
uint8_t compare_string(char *first, char *second);
uint8_t pruefe_kopf(char * beginn, char string[]);
void lese_textfile_in_getraenk(uint8_t file);

// Testfunktion
void cocktail_test_command(unsigned char INPUT[256]);

// Subfunktionen
void check_startseite(uint8_t button);
void check_zutatenanzeige(uint8_t button);
void check_listenanzeige(uint8_t button);
void choose_drink(uint8_t nr);
void check_zubabfrage(uint8_t button);
void check_zubbildschirm(uint8_t button);
void check_menuanzeige(uint8_t button);
void check_bearbeitungsanzeige(uint8_t button);
void check_ceinstanzeige(uint8_t button);
void check_reinanzeige1(uint8_t button);
void check_reinanzeige2(uint8_t button);
void check_reinanzeige3(uint8_t button);
void check_infoanzeige(uint8_t button);
void check_abbruchanzeige(uint8_t button);
void check_fehleranzeige(uint8_t button);
void check_erstanzeige1(uint8_t button);
void check_erstanzeige2(uint8_t button);
void erstelle_File(uint8_t filename, char * name, uint8_t alkohol);
void loesche_FIle(uint8_t filename);

extern unsigned char INPUT_UART_1[256];

#endif /* COCKTAIL_FUNCTIONS_H_ */