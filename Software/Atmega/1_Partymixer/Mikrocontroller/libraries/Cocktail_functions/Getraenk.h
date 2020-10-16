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
// #include "../SD-Karte/FAT32.h"
#include "../Lists/Lists.h"


// Phsikalischer Speicher mit Pointer darauf
struct getraenk {
    char * name;
    uint8_t alkohol;
    uint8_t kohlensaeure;
    uint8_t picture;
};
typedef struct getraenk getraenk_t;

getraenk_t *aktuellesGetraenk;

// Listen für Getränkeliste (alle Getränke)
file_node_t *head_getraenk_file_alle, *tail_getraenk_file_alle, *actual_getraenk_file_alle, *buffer_getraenk_file_alle, *buffer2_getraenk_file_alle;
int number_getraenk_alle_;
int *number_getraenk_alle;

file_list_node_t * tail_list_node_getraenk, * head_list_node_getraenk, * actual_list_node_getraenk;
int number_list_getraenke_alle_val;
int *number_list_getranke_alle;

void cocktails_init(void);

// Getränk struct
getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t alkohol, uint8_t kohlensaeure, uint8_t picture);

file_list_node_t *create_new_list_node_file(file_node_t * getraenk_to_point_on);
file_list_node_t *insert_list_node_at_head(file_list_node_t **head, file_list_node_t *file_to_insert);
file_list_node_t *delete_head_list_node_getraenk(file_list_node_t **head);

#endif /* GETRAENK_H_ */