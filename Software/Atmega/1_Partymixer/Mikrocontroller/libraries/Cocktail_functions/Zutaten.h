/*
 * Zutaten.h
 *
 * Created: 19.05.2020 20:10:36
 *  Author: kimsc
 */


#ifndef ZUTATEN_H_
#define ZUTATEN_H_

/******************************************************************************************************************************/
#include <avr/eeprom.h>                                     // Wird ben�tigt um in das EEPROM zu schreiben
#include <stdlib.h>                                         // Wird ben�tigt f�r Variabelnumwandlungen (z.B itoa(), atoi(), ...)
#include <string.h>                                         // Wird ben�tigt w�rd Stringoperationen (z.B strcpy(), strcat(), ...)
#include "../SD-Karte/SD_Karte.h"                              // Wird ben�tigt f�r Lese- und Schreiboperationen auf die SD-Karte
#include "../Lists/Lists.h"

/******************************************************************************************************************************/
// Physikalisch vorhandener Speicher f�r eine Zutat (Wird nur 1x initialisiert)
/******************************************************************************************************************************/
struct zutat {                                              // Struckt f�r die aktuelle Zutat (wird nur 1 Mal initialisiert)
	char * name;                                            // Pointer auf den Speicher f�r den Namen der aktuellen Zutat
	uint8_t alkohol;                                        // Speicher f�r Alkohol Ja/Nein
	uint8_t kohlensaeure;                                   // Speicher f�r Alkohol Ja/Nein
};
typedef struct zutat zutat_t;                               // Typedef f�r Struct zutat_t

zutat_t *aktuelle_zutat;                                    // Pointer auf aktuelle Zutat

// Files f�r alle Zutaten ohne Kohlens�ure.
file_node_t *head_zutat_file_ohne, *tail_zutat_file_ohne;
int number_zutaten_ohne_val;
int *number_zutaten_ohne;

// Files f�r alle Zutaten mit Kohlens�ure.
file_node_t *head_zutat_file_mit, *tail_zutat_file_mit;
int number_zutaten_mit_val;
int *number_zutaten_mit;

// Pointer auf die Listeneintr�ge f�r Zutaten in der Maschine
file_list_node_t * tail_list_node_zutaten, * head_list_node_zutaten, * actual_list_node_zutaten;
int number_list_zutaten_val;
int *number_list_zutaten;

// Structs f�r alle ausgew�hlten Zutaten in der Maschine. (ohne Kohlens�ure)
zutat_maschine_node_t *head_zutat_maschine_ohne, *tail_zutat_maschine_ohne;
int number_zutaten_maschine_ohne_val;
int *number_zutaten_maschine_ohne;

// Structs f�r alle ausgew�hlten Zutaten ausserhalb der Maschine. (mit Kohlens�ure)
zutat_maschine_node_t *head_zutat_maschine_mit, *tail_zutat_maschine_mit, *buffer_zutat_maschine;
int number_zutaten_maschine_mit_val;
int *number_zutaten_maschine_mit;

// Pointer auf die Listeneintr�ge f�r Zutaten in der Maschine
zutat_maschine_list_node_t * tail_list_node_zutat_maschine, * head_list_node_zutat_maschine, * actual_list_node_zutat_maschine;
int number_list_zutat_maschine_val;
int *number_list_zutat_maschine;

// Tempor�r f�r Concentrate/deconcentrate List
zutat_maschine_node_t * tmp_ohne_KS_head;
zutat_maschine_node_t * tmp_mit_KS_head;
zutat_maschine_node_t * tmp_ohne_KS_tail;
zutat_maschine_node_t * tmp_mit_KS_tail;
zutat_maschine_node_t * tmp_zut_Maschine_head;
zutat_maschine_node_t * tmp_zut_Maschine_tail;
zutat_maschine_node_t * tmp_zut_Maschine_actual;

zutat_maschine_node_t *aktuelle_Zutat_in_Maschine_ohne_KS;        // Pointer auf aktuelle Zutat (ohne Kohlens�ure) in Maschine
zutat_maschine_node_t *buffer_zut_in_Maschine_ohne_KS;              // Pointer auf zuletzt in die Liste eingef�gte Zutat (ohne Kohlens�ure) in der Maschine

zutat_maschine_node_t *aktuelle_Zutat_ausser_Maschine_mit_KS;     // Pointer auf aktuelle Zutat (mit Kohlens�ure) in Maschine
zutat_maschine_node_t *buffer_zut_ausser_Maschine_mit_KS;           // Pointer auf zuletzt in die Liste eingef�gte Zutat (mit Kohlens�ure) in der Maschine

file_node_t * buffer_zutat_file;                           // Pointer auf aktuelle Zutat in Maschine
file_node_t * buffer2_zutat_file;                           // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_in_Maschine_ohne_KS;                        // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_ausser_Maschine_mit_KS;                        // Pointer auf aktuelle Zutat in Maschine


/******************************************************************************************************************************/
// Initialisierung des physikalischen speichers und der Listen
/******************************************************************************************************************************/
void zutaten_init(void);                                    // Funktion f�r die Initialisierung der Zutaten und deren Speicher



/******************************************************************************************************************************/
// Physikalischer Speicher f�r die aktuelle Zutat
/******************************************************************************************************************************/
zutat_t *create_zutat();                                    // Funktion zur Alloziierung des Speicherplatzes f�r zutat_t


/******************************************************************************************************************************/
// Eeprom-Variable
/******************************************************************************************************************************/
uint8_t * address_Standardwiederherstellung;                // EEprom address-Pointer f�r die Standardwiederherstellung



#endif /* ZUTATEN_H_ */