/*
 * Zutaten.h
 *
 * Created: 19.05.2020 20:10:36
 *  Author: kimsc
 */


#ifndef ZUTATEN_H_
#define ZUTATEN_H_

/******************************************************************************************************************************/
#include <avr/eeprom.h>                                     // Wird benötigt um in das EEPROM zu schreiben
#include <stdlib.h>                                         // Wird benötigt für Variabelnumwandlungen (z.B itoa(), atoi(), ...)
#include <string.h>                                         // Wird benötigt würd Stringoperationen (z.B strcpy(), strcat(), ...)
#include "../SD-Karte/FAT32.h"                              // Wird benötigt für Lese- und Schreiboperationen auf die SD-Karte
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
// Physikalisch vorhandener Speicher für eine Zutat (Wird nur 1x initialisiert)
/******************************************************************************************************************************/
struct zutat {                                              // Struckt für die aktuelle Zutat (wird nur 1 Mal initialisiert)
    char * name;                                            // Pointer auf den Speicher für den Namen der aktuellen Zutat
    uint8_t alkohol;                                        // Speicher für Alkohol Ja/Nein
    uint8_t kohlensaeure;                                   // Speicher für Alkohol Ja/Nein
};
typedef struct zutat zutat_t;                               // Typedef für Struct zutat_t

zutat_t *aktuelle_zutat;                                    // Pointer auf aktuelle Zutat



zutat_maschine_node_t *aktuelle_Zutat_in_Maschine_ohne_KS;        // Pointer auf aktuelle Zutat (ohne Kohlensäure) in Maschine
zutat_maschine_node_t *buffer_zut_in_Maschine_ohne_KS;              // Pointer auf zuletzt in die Liste eingefügte Zutat (ohne Kohlensäure) in der Maschine

zutat_maschine_node_t *aktuelle_Zutat_ausser_Maschine_mit_KS;     // Pointer auf aktuelle Zutat (mit Kohlensäure) in Maschine
zutat_maschine_node_t *buffer_zut_ausser_Maschine_mit_KS;           // Pointer auf zuletzt in die Liste eingefügte Zutat (mit Kohlensäure) in der Maschine

file_node_t * buffer_zutat_file;                           // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_in_Maschine_ohne_KS;                        // Pointer auf aktuelle Zutat in Maschine
file_node_t * aktuelles_Zutat_file_ausser_Maschine_mit_KS;                        // Pointer auf aktuelle Zutat in Maschine




/******************************************************************************************************************************/
// Listen-Funktionen für die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
struct zutat_list_node {                                    // Struckt für die aktuelle Zutat (wird nur 1 Mal initialisiert)
	file_node_t * zutat_xy;                                // Pointer auf den Speicher für den Namen der aktuellen Zutat
	struct zutat_list_node * prev;                          // Speicher für Alkohol Ja/Nein
	struct zutat_list_node * next;                          // Speicher für Alkohol Ja/Nein
};
typedef struct zutat_list_node zutat_list_node_t;           // Typedef für Struct zutat_t

zutat_list_node_t *aktuelle_zutat_list_node;                // Pointer auf aktuelle Zutat
zutat_list_node_t *buffer_zutat_list_node;                  // Pointer auf aktuelle Zutat
zutat_list_node_t *tail_zutat_list_node;                    // Pointer auf aktuelle Zutat
zutat_list_node_t *head_zutat_list_node;                    // Pointer auf aktuelle Zutat


/******************************************************************************************************************************/
// Listen-Funktionen für die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
struct zutatMaschine_list_node {                                    // Struckt für die aktuelle Zutat (wird nur 1 Mal initialisiert)
	zutat_maschine_node_t * zutat_xy;                                // Pointer auf den Speicher für den Namen der aktuellen Zutat
	struct zutatMaschine_list_node * prev;                          // Speicher für Alkohol Ja/Nein
	struct zutatMaschine_list_node * next;                          // Speicher für Alkohol Ja/Nein
};
typedef struct zutatMaschine_list_node zutatMaschine_list_node_t;           // Typedef für Struct zutat_t

zutatMaschine_list_node_t *aktuelle_zutatMaschine_list_node;                // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *buffer_zutatMaschine_list_node;                  // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *tail_zutatMaschine_list_node;                    // Pointer auf aktuelle Zutat
zutatMaschine_list_node_t *head_zutatMaschine_list_node;                    // Pointer auf aktuelle Zutat



/******************************************************************************************************************************/
// Initialisierung des physikalischen speichers und der Listen
/******************************************************************************************************************************/
void zutaten_init(void);                                    // Funktion für die Initialisierung der Zutaten und deren Speicher



/******************************************************************************************************************************/
// Physikalischer Speicher für die aktuelle Zutat
/******************************************************************************************************************************/
zutat_t *create_zutat();                                    // Funktion zur Alloziierung des Speicherplatzes für zutat_t



/******************************************************************************************************************************/
// Listen-Funktionen für die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes für zutat_list_node_t
zutat_list_node_t *create_new_list_node_zut_file( file_node_t * file_to_link);

// Funktion für das aneinanderreihen der Listeneinträge für zutat_list_node_t (Eingrag wird am head eingefügt)
zutat_list_node_t *insert_zutat_list_node_at_head(zutat_list_node_t **head, zutat_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Listen-Funktionen für die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes für zutat_list_node_t
zutatMaschine_list_node_t *create_new_list_node_zutMaschine_file( zutat_maschine_node_t * file_to_link);

// Funktion für das aneinanderreihen der Listeneinträge für zutat_list_node_t (Eingrag wird am head eingefügt)
zutatMaschine_list_node_t *insert_zutatMaschine_list_node_at_head(zutatMaschine_list_node_t **head, zutatMaschine_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Eeprom-Variable
/******************************************************************************************************************************/
uint8_t * address_Standardwiederherstellung;                // EEprom address-Pointer für die Standardwiederherstellung



#endif /* ZUTATEN_H_ */