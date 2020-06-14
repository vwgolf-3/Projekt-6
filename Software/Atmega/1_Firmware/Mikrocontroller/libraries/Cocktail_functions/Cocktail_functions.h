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
#include "../Main_functions/Main_Func.h"

uint8_t lese_sensor(uint8_t Sensor);

unsigned char option, error, data, FAT32_active;
unsigned int i;
unsigned char fileName[13];

// Variable für Liste
uint8_t i_Liste;
uint8_t block_list_hoch;
uint8_t block_list_runter;
uint8_t Grossschreib;
uint8_t counter;
char buff_name[21];
char stop;

enum Liste_Startbildschirm {ALLE, ALKOHOL, ALKOHOLFREI};
uint8_t Liste;



// Zubereitung
void fuelle_getraenk(uint32_t fuellmenge);
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


void erstelle_File(uint8_t filename, char * name, uint8_t alkohol);
void loesche_FIle(uint8_t filename);
void schreibe_Menge_in_Getraenk(uint8_t zutat);

void schiebe_file_prev(void);
void schiebe_file_next(void);
void zubereitung_getraenk(uint32_t Menge);
void bearbeite_Cocktail(uint8_t cocktail);
void erstelle_Liste_Zutat_Pos(char * name_button);
void lese_textfile_in_zutat(uint8_t file);
void setze_Posanzeige_Rot_Gruen(void);

extern uint8_t test2;


extern unsigned char INPUT_UART_1[256];

#endif /* COCKTAIL_FUNCTIONS_H_ */