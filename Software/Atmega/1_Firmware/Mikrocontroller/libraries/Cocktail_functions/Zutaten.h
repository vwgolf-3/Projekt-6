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
#include "../SD-Karte/FAT32.h"                              // Wird ben�tigt f�r Lese- und Schreiboperationen auf die SD-Karte
#include "../Lists/Lists.h"

file_node_t *head_zutat_file_ohne, *tail_zutat_file_ohne;
file_node_t *head_zutat_file_mit, *tail_zutat_file_mit;

zutat_maschine_node_t *head_zutat_maschine_ohne, *tail_zutat_maschine_ohne;
zutat_maschine_node_t *head_zutat_maschine_mit, *tail_zutat_maschine_mit;


int number_zutaten_ohne_;
int number_zutaten_mit_;
int *number_zutaten_ohne;
int *number_zutaten_mit;

int number_zutaten_maschine_ohne_;
int number_zutaten_maschine_mit_;
int *number_zutaten_maschine_ohne;
int *number_zutaten_maschine_mit;


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



zutat_maschine_node_t *aktuelle_Zutat_in_Maschine_ohne_KS;        // Pointer auf aktuelle Zutat (ohne Kohlens�ure) in Maschine
zutat_maschine_node_t *buffer_zut_in_Maschine_ohne_KS;              // Pointer auf zuletzt in die Liste eingef�gte Zutat (ohne Kohlens�ure) in der Maschine

zutat_maschine_node_t *aktuelle_Zutat_ausser_Maschine_mit_KS;     // Pointer auf aktuelle Zutat (mit Kohlens�ure) in Maschine
zutat_maschine_node_t *buffer_zut_ausser_Maschine_mit_KS;           // Pointer auf zuletzt in die Liste eingef�gte Zutat (mit Kohlens�ure) in der Maschine

file_node_t * buffer_zutat_file;                           // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_in_Maschine_ohne_KS;                        // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_ausser_Maschine_mit_KS;                        // Pointer auf aktuelle Zutat in Maschine




/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
struct zutat_list_node {                                    // Struckt f�r die aktuelle Zutat (wird nur 1 Mal initialisiert)
	file_node_t * zutat_xy;                                // Pointer auf den Speicher f�r den Namen der aktuellen Zutat
	struct zutat_list_node * prev;                          // Speicher f�r Alkohol Ja/Nein
	struct zutat_list_node * next;                          // Speicher f�r Alkohol Ja/Nein
};
typedef struct zutat_list_node zutat_list_node_t;           // Typedef f�r Struct zutat_t

zutat_list_node_t *aktuelle_zutat_list_node;                // Pointer auf aktuelle Zutat
zutat_list_node_t *buffer_zutat_list_node;                  // Pointer auf aktuelle Zutat
zutat_list_node_t *tail_zutat_list_node;                    // Pointer auf aktuelle Zutat
zutat_list_node_t *head_zutat_list_node;                    // Pointer auf aktuelle Zutat


/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
struct zutatMaschine_list_node {                                    // Struckt f�r die aktuelle Zutat (wird nur 1 Mal initialisiert)
	zutat_maschine_node_t * zutat_xy;                                // Pointer auf den Speicher f�r den Namen der aktuellen Zutat
	struct zutatMaschine_list_node * prev;                          // Speicher f�r Alkohol Ja/Nein
	struct zutatMaschine_list_node * next;                          // Speicher f�r Alkohol Ja/Nein
};
typedef struct zutatMaschine_list_node zutatMaschine_list_node_t;           // Typedef f�r Struct zutat_t

zutatMaschine_list_node_t *aktuelle_zutatMaschine_list_node;                // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *buffer_zutatMaschine_list_node;                  // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *tail_zutatMaschine_list_node;                    // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *head_zutatMaschine_list_node;                    // Pointer auf aktuelle Zutat



/******************************************************************************************************************************/
// Initialisierung des physikalischen speichers und der Listen
/******************************************************************************************************************************/
void zutaten_init(void);                                    // Funktion f�r die Initialisierung der Zutaten und deren Speicher



/******************************************************************************************************************************/
// Physikalischer Speicher f�r die aktuelle Zutat
/******************************************************************************************************************************/
zutat_t *create_zutat();                                    // Funktion zur Alloziierung des Speicherplatzes f�r zutat_t



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes f�r zutat_list_node_t
zutat_list_node_t *create_new_list_node_zut_file( file_node_t * file_to_link);

// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_list_node_t (Eingrag wird am head eingef�gt)
zutat_list_node_t *insert_zutat_list_node_at_head(zutat_list_node_t **head, zutat_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes f�r zutat_list_node_t
zutatMaschine_list_node_t *create_new_list_node_zutMaschine_file( zutat_maschine_node_t * file_to_link);

// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_list_node_t (Eingrag wird am head eingef�gt)
zutatMaschine_list_node_t *insert_zutatMaschine_list_node_at_head(zutatMaschine_list_node_t **head, zutatMaschine_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Eeprom-Variable
/******************************************************************************************************************************/
uint8_t * address_Standardwiederherstellung;                // EEprom address-Pointer f�r die Standardwiederherstellung



#endif /* ZUTATEN_H_ */