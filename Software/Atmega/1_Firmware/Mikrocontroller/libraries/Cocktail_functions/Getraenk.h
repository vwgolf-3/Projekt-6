/*
 * Getraenk.h
 *
 * Created: 05.04.2020 22:46:11
 *  Author: kimsc
 */ 


#ifndef GETRAENK_H_
#define GETRAENK_H_

#include <avr/eeprom.h>
#include <stdlib.h>
#include <util/delay.h>
#include "../UART/UART.h"

struct getraenk{
	char * name;
	uint8_t value;
	uint8_t alkohol;
	uint8_t * mengen;
	uint8_t picture;
	struct getraenk* next;
	struct getraenk* prev;
};
typedef struct getraenk getraenk_t;

struct getraenk_file{
	uint8_t file;
	struct getraenk_file * next;
	struct getraenk_file * prev;
};
typedef struct getraenk_file getraenk_file_t;

getraenk_file_t *aktuellesGetraenk_file;
getraenk_file_t * head_getraenk_file;
getraenk_file_t * tail_getraenk_file;

getraenk_t *aktuellesGetraenk;
getraenk_t *head_getraenk;	// Getränk-Pointer
getraenk_t *tail_getraenk;

uint8_t * address_getraenk;	// EEprom address-Pointer

void cocktails_init(void);
void printlist(void);

// Getränk struct
getraenk_t * find_getraenk(getraenk_t *head, char * name);
getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert);
getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol, uint8_t picture);
void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t *newnode);
void showlist (void);
int8_t length_list(void);

// EEPROM
void add_drink_to_eeprom(uint8_t * add, char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol);
getraenk_t* read_drink_from_eemprom(uint8_t * add);
int8_t count_eeprom_drinks(uint8_t * add);
void add_EEPROM_drinks_to_list(uint8_t * add);
void delete_EEPROM (uint8_t * add);

// File struct
getraenk_file_t *insert_file_at_head(getraenk_file_t **head, getraenk_file_t *file_to_insert);
getraenk_file_t *create_new_getraenk_file(uint8_t file_to_create);

#endif /* GETRAENK_H_ */