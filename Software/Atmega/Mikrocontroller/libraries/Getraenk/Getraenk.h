/*
 * Getraenk.h
 *
 * Created: 05.04.2020 22:46:11
 *  Author: kimsc
 */ 


#ifndef GETRAENK_H_
#define GETRAENK_H_
#define ANZAHL_ZUTATEN 12
#include <avr/eeprom.h>
#include "../SPI/SPI_Defines.h"
#include "../UART/UART.h"
#include "../SPI/SPI.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../../Main_Func/Main_Func.h"

struct getraenk{
	char * name;
	uint8_t value;
	uint8_t alkohol;
	char * mengen;
	struct getraenk* next;
};
typedef struct getraenk getraenk_t;

uint8_t * address;	// EEprom address-Pointer
getraenk_t *head;	// Getr�nk-Pointer
uint8_t * zutat;	// Zutaten-Pointer

void cocktails_init(void);
void printlist(void);

getraenk_t * find_getraenk(getraenk_t *head, char * name);
getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert);
getraenk_t *create_new_getraenk(char * name, uint8_t value, uint8_t * mengen, uint8_t alkohol);
void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t *newnode);
void showlist (void);
int8_t length_list(void);
void add_drink_to_eeprom(uint8_t * add, char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol);
getraenk_t* read_drink_from_eemprom(uint8_t * add);
int8_t count_eeprom_drinks(uint8_t * add);
void add_EEPROM_drinks_to_list(uint8_t * add);
void delete_EEPROM (uint8_t * add);

#endif /* GETRAENK_H_ */