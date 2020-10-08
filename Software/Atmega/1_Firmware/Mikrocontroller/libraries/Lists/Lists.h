/*
 * Lists.h
 *
 * Created: 06.10.2020 22:03:29
 *  Author: kimsc
 */


#ifndef LISTS_H_
#define LISTS_H_

#include "../UART/UART.h"

#include <stdio.h>

#include <stdlib.h>


/******************************************************************************************************************************/
// Die Zutaten Files werden auch nach Kohensäure sortiert.
/******************************************************************************************************************************/
struct file_node {                                         // Struckt für Zutaten-Files (wird nach Anzahl Files initialisiert)
	uint8_t file;                                           // Speicher für Variable des Filenamens
	struct file_node * next;                               // Pointer auf zuletzt in die Liste eingefügtes Zutaten-File
	struct file_node * prev;                               // Pointer auf erstes in die Liste eingefügtes Zutaten-File
};
typedef struct file_node file_node_t;                     // Typedef für Struct file_node_t

/******************************************************************************************************************************/
// Aufgrund des Problems mit Kohlensäure Ja/Nein, wird in zwei Listen unterteilt: Zutaten in und ausserhab der Maschine
/******************************************************************************************************************************/
struct zutat_Maschine_node {                                     // Struckt für Zutaten in Maschine (wird 12 Mal initialisiert)
	char * name;                                            // Pointer auf den Speicher für den Namen der Zutat in Maschine
	uint8_t status;                                         // Speicher für den Status (KEINGETRAENK=0, VOLL=1, LEER=2)
	uint8_t alkohol;                                        // Speicher für Alkohol Ja/Nein
	uint8_t kohlensaeure;                                   // Speicher für Alkohol Ja/Nein
	uint8_t stelle;                                         // Speicher für Position der Zutat in der Maschine
	uint8_t menge;                                          // Speicher für Menge der Zutat in der Maschine
	uint32_t position_motor;                                // Speicher für Position der Zutat in der Maschine
	struct zutat_Maschine_node* next;                            // Pointer auf das zuvor eingefügte Getränk
	struct zutat_Maschine_node* prev;                            // Pointer auf das danach eingefügte Getränk
};
typedef struct zutat_Maschine_node zutat_maschine_node_t;              // Typedef für Struct zutat_t

struct file_list_node {
	file_node_t * getraenk_file;
	struct file_list_node * next;
	struct file_list_node * prev;
};
typedef struct file_list_node file_list_node_t;


file_node_t *new_file_node, *ptr_file_node;
file_node_t* create_file_node(int file_nr, int * number);
void add_node(int file_nr, int ** number, file_node_t **first, file_node_t **last);
void insert_at_first(char file_nr, int ** number, file_node_t ** first, file_node_t ** last);
void insert_at_end(int file_nr, int ** number, file_node_t ** first, file_node_t ** last);
void insert_at_position(int file_nr, int pos, int * number, file_node_t ** first, file_node_t ** last);
void delete_node_position(int pos, int * number, file_node_t ** first, file_node_t ** last);
void sort_list(int * number, file_node_t ** first, file_node_t ** last);
void update(int oldval, int newval, int * number, file_node_t ** first, file_node_t ** last);
void search(int key, int * number, file_node_t ** first, file_node_t ** last);
void display_from_beg(int * number, file_node_t ** first, file_node_t ** last);
void display_in_rev(int * number, file_node_t ** first, file_node_t ** last);

zutat_maschine_node_t *new_zutat_maschine_node, *ptr_zutat_maschine_node;
zutat_maschine_node_t* create_zutat_maschine_node(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int * number);
void add_node_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t **first, zutat_maschine_node_t **last);
void insert_at_first_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void insert_at_end_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void insert_at_position_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int pos, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void delete_node_position_2(int pos, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void sort_list_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void update_2(int oldval, int newval, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void search_2(int key, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void display_from_beg_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);
void display_in_rev_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last);

file_list_node_t *new_list_node, *ptr_list_node;
file_list_node_t* create_list_node(file_node_t * node, int * number);
void add_node_3(file_node_t * node, int ** number, file_list_node_t **first, file_list_node_t **last);
void insert_at_first_3(file_node_t * node, int ** number, file_list_node_t ** first, file_list_node_t ** last);
void insert_at_end_3(file_node_t * node, int ** number, file_list_node_t ** first, file_list_node_t ** last);
void insert_at_position_3(file_node_t * node, int pos, int * number, file_list_node_t ** first, file_list_node_t ** last);
void delete_node_position_3(int pos, int * number, file_list_node_t ** first, file_list_node_t ** last);
void sort_list_3(int * number, file_list_node_t ** first, file_list_node_t ** last);
void update_3(int oldval, int newval, int * number, file_list_node_t ** first, file_list_node_t ** last);
void search_3(int key, int * number, file_list_node_t ** first, file_list_node_t ** last);
void display_from_beg_3(int * number, file_list_node_t ** first, file_list_node_t ** last);
void display_in_rev_3(int * number, file_list_node_t ** first, file_list_node_t ** last);

#endif /* LISTS_H_ */