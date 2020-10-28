/*
 * Cocktail_functions.h
 *
 * Created: 07.03.2020 13:45:25
 *  Author: kimsc
 */


#ifndef COCKTAIL_FUNCTIONS_H_
#define COCKTAIL_FUNCTIONS_H_

#include <stdint.h>

// Verbindungsbibliotheken Software/Hardware
#include "../Nextion_Display/Nextion_Display.h"
#include "../TMC4671/TMC4671.h"
#include "../TMC6200/TMC6200.h"
#include "../SD-Karte/SD_Karte.h"
#include "../LED/LED.h"
#include "../Software_Ramp/Ramp1.h"
#include "../Main_functions/Main_Func.h"

// Speicherstrukturen
#include "Zutaten.h"
#include "Getraenk.h"
#include "TAGS.h"

// #include "../Lists/Lists.h"

unsigned char option, error, data, FAT32_active;
unsigned int i;
unsigned char fileName[13];

// Variable für Liste
uint8_t block_list_hoch;
uint8_t block_list_runter;
uint8_t Grossschreib;
uint8_t counter;

uint8_t kohlensaeure_mode;
uint8_t i_Liste;
char buff_name[21];
char stop;

enum Liste_Startbildschirm {ALLE, ALKOHOL, ALKOHOLFREI};
uint8_t Liste;

// Zubereitung
void fuelle_getraenk(uint32_t fuellmenge, linear_ramp_t *ramp);
void schalte_pumpe_aus(uint8_t Pumpe);
void schalte_pumpe_ein(uint8_t Pumpe);

// Anzeige Display
void setze_startanzeige(getraenk_t * anzeige_getraenk);
void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk);

// Getränke-Pointer
file_node_t * erstelle_liste_cocktails(file_node_t * beginn_file, char * name_button);
zutat_maschine_node_t * erstelle_liste_zutat(zutat_maschine_node_t * beginn_Maschine, char * input);

uint8_t lese_sensor(uint8_t Sensor);

// SD-Karte
void SD_startup(void);
void lese_textfile_in_getraenk(uint8_t file);
void erstelle_File(uint8_t filename, char * name, uint8_t alkohol, uint8_t kohlensaeure);
void loesche_FIle(uint8_t filename);
void schreibe_Menge_in_Getraenk(uint8_t zutat);

void schiebe_file_prev(void);
void schiebe_file_next(void);
void zubereitung_getraenk(uint8_t Menge);
void bearbeite_Cocktail(uint8_t cocktail);
file_node_t * erstelle_liste_zutat_pos(file_node_t * beginn_file, char * name_button);
void lese_textfile_in_zutat(uint8_t file);
void setze_Posanzeige_Rot_Gruen(void);
void setze_fluessgkeit_in_position_ohne(uint8_t nr, uint8_t status);
void setze_fluessgkeit_in_position_mit(uint8_t nr, uint8_t status);

void setze_aktuelle_Zutat_in_Maschine(uint8_t nr);
uint8_t check_existence(uint8_t file);

void send_List_Getraenke (void);
void send_List_RFID (void);
void send_List_Zutaten (void);
void setze_aktuelles_getraenk_in_maschine(uint8_t nr);

void ESP_Getraenk(void);

void Getraenk_erstellt();
void Maschineninfo_senden();

void setze_standardeinstellungen(void);
void renew_list(void);
void write_M_file(char * buff_file);
void schreibe_Getraenk_in_tag(uint8_t nr);
void display_init(void);

void prepare_empty_getraenk(void);

void speichere_bearbeiteten_cocktail(void);
void speichere_neuen_cocktail(void);

void begin_erstelle_liste_zutaten_maschine(uint8_t page, char* button);
void begin_erstelle_liste_alle_zutaten(uint8_t page, char * name);
void begin_erstelle_liste_cocktails(uint8_t page, char* button);

void delete_list_node_zutat_maschine(void);
void delete_list_node_files(uint8_t art);

void rauflist_files(uint8_t art);
void runterlist_files(uint8_t art);

void rauflist_zutat_maschine(void);
void runterlist_zutat_maschine(void);

void concentrace_zutat_maschine_list(void);
void deconcentrace_zutat_maschine_list(void);

void delete_file_node_alle(uint8_t art);

enum Zutat_in_Maschine_Status {KEINGETRAENK, VOLL, LEER};
enum file_art {ZUTAT, COCKTAIL, ZUTAT_MIT, ZUTAT_OHNE};
enum mengen {DL_1 = 1, DL_3 = 3, DL_5 = 5};
	
#endif /* COCKTAIL_FUNCTIONS_H_ */