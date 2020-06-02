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

void zutaten_init(void);

// Cocktail-Liste
zutat_t *insert_zutat_at_head(zutat_t **head_zut, zutat_t *zutat_to_insert);
zutat_t *create_neue_zutat(char * name, char k);

#endif /* ZUTATEN_H_ */