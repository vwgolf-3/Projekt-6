/*
 * Zutaten.h
 *
 * Created: 19.05.2020 20:10:36
 *  Author: kimsc
 */ 


#ifndef ZUTATEN_H_
#define ZUTATEN_H_

#include <avr/eeprom.h>
#include <stdlib.h>
#include <util/delay.h>
#include "../UART/UART.h"
#include "../Cocktail_functions/Cocktail_functions.h"
#include "../SD-Karte/SD_routines.h"
#include "../SD-Karte/FAT32.h"

struct zutat{
	char * name;
	char nr;
	struct zutat* next;
	struct zutat* prev;
};
typedef struct zutat zutat_t;

zutat_t *aktuelleZutat;

uint8_t * address_zut;	// EEprom address-Pointer

zutat_t *head_zut;	// Getränk-Pointer
zutat_t *tail_zut;






//*************************************************************
struct zutat_test{
	char * name;
	uint8_t alkohol;
	struct zutat_test* next;
	struct zutat_test* prev;
};
typedef struct zutat_test zutat_test_t;

// Pointer für Getränkeliste (alle)
zutat_test_t *aktuelle_zutat_test;
zutat_test_t *head_zutat_test;	// Getränk-Pointer
zutat_test_t *tail_zutat_test;

//**************************************************************
struct zutat_Maschine{
	char * name;
	uint8_t status;
	uint8_t alkohol;
	uint8_t position;
	struct zutat_Maschine* next;
	struct zutat_Maschine* prev;
};
typedef struct zutat_Maschine zutatMaschine_t;

// Pointer für Getränke in der Maschine
zutatMaschine_t *aktuelleZutatInMaschine;
zutatMaschine_t *head_zut_in_Maschine;
zutatMaschine_t *tail_zut_in_Maschine;

//**********************************************************
struct zutat_file{
	uint8_t file;
	struct zutat_file * next;
	struct zutat_file * prev;
};
typedef struct zutat_file zutat_file_t;

zutat_file_t * aktuelles_zutat_file;
zutat_file_t * head_zutat_file;
zutat_file_t * tail_zutat_file;

//**********************************************************


void zutaten_init(void);

// Cocktail-Liste
zutat_t *insert_zutat_at_head(zutat_t **head_zut, zutat_t *zutat_to_insert);
zutat_t *create_neue_zutat(char * name, char k);

zutat_test_t *insert_zutat_at_head_test(zutat_test_t **head_zutat, zutat_test_t ** tail_zutat, zutat_test_t *zutat_to_insert);
zutat_test_t *create_neue_zutat_test(char * name, uint8_t alkohol);

zutatMaschine_t *insert_zutat_Maschine_at_head(zutatMaschine_t **head_zutat, zutatMaschine_t **tail_zutat, zutatMaschine_t *zutat_to_insert);
zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t k);

zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t *file_to_insert);
zutat_file_t *create_new_zutat_file(uint8_t file_to_create);

#endif /* ZUTATEN_H_ */