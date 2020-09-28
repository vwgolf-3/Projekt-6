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
#include "../SD-Karte/FAT32.h"

struct getraenk {
    char * name;
    uint8_t alkohol;
    uint8_t kohlensaeure;
    uint8_t * mengen;
    uint8_t picture;
};
typedef struct getraenk getraenk_t;

struct getraenk_file {
    uint8_t file;
    struct getraenk_file * next;
    struct getraenk_file * prev;
};
typedef struct getraenk_file getraenk_file_t;

struct getraenk_file_2 {
	uint8_t file;
	struct getraenk_file_2 * next;
	struct getraenk_file_2 * prev;
};
typedef struct getraenk_file_2 getraenk_file_2_t;

struct getraenk_file_3 {
	getraenk_file_t * getraenk_x;
	struct getraenk_file_3 * next;
	struct getraenk_file_3 * prev;
};
typedef struct getraenk_file_3 getraenk_file_3_t;

getraenk_file_t *aktuellesGetraenk_file;
getraenk_file_t *bufferGetraenk_file;
getraenk_file_t *buffer2Getraenk_file;
getraenk_file_t * head_getraenk_file;
getraenk_file_t * tail_getraenk_file;

getraenk_file_t * liste_vorher_getraenk_file;
getraenk_file_t * liste_start_getraenk_file;
getraenk_file_t * liste_nacher_getraenk_file;

getraenk_file_2_t *aktuellesGetraenk_file_2;
getraenk_file_2_t * head_getraenk_file_2;
getraenk_file_2_t * tail_getraenk_file_2;

getraenk_t *aktuellesGetraenk;
getraenk_t *head_getraenk;  // Getr�nk-Pointer
getraenk_t *tail_getraenk;

getraenk_file_3_t * tail_list_node_file;
getraenk_file_3_t * head_list_node_file;
getraenk_file_3_t * actual_list_node_file;

uint8_t * address_getraenk; // EEprom address-Pointer

uint8_t check_existence(uint8_t file);
void cocktails_init(void);
void printlist(void);

// Getr�nk struct
getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t alkohol, uint8_t kohlensaeure, uint8_t picture);
void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t *newnode);
void showlist (void);
int8_t length_list(void);

// EEPROM
void add_drink_to_eeprom(uint8_t * add, char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol, uint8_t kohlensaeure);
getraenk_t* read_drink_from_eemprom(uint8_t * add);
int8_t count_eeprom_drinks(uint8_t * add);
void add_EEPROM_drinks_to_list(uint8_t * add);
void delete_EEPROM (uint8_t * add);

// File struct
getraenk_file_t *insert_file_at_head(getraenk_file_t **head, getraenk_file_t *file_to_insert);
getraenk_file_t *create_new_getraenk_file(uint8_t file_to_create);

getraenk_file_2_t *insert_file_at_head_2(getraenk_file_2_t **head, getraenk_file_2_t *file_to_insert);
getraenk_file_2_t *create_new_getraenk_file_2(uint8_t file_to_create);

getraenk_file_3_t *create_new_list_node_file(getraenk_file_t * getraenk_to_point_on);
getraenk_file_3_t *insert_list_node_at_head(getraenk_file_3_t **head, getraenk_file_3_t *file_to_insert);
getraenk_file_3_t *delete_head_list_node_file(getraenk_file_3_t **head);

#endif /* GETRAENK_H_ */