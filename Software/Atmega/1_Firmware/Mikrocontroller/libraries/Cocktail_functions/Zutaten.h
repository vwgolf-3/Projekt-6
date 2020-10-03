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



/******************************************************************************************************************************/
// Aufgrund des Problems mit Kohlens�ure Ja/Nein, wird in zwei Listen unterteilt: Zutaten in und ausserhab der Maschine
/******************************************************************************************************************************/
struct zutat_Maschine {                                     // Struckt f�r Zutaten in Maschine (wird 12 Mal initialisiert)
    char * name;                                            // Pointer auf den Speicher f�r den Namen der Zutat in Maschine
    uint8_t status;                                         // Speicher f�r den Status (KEINGETRAENK=0, VOLL=1, LEER=2)
    uint8_t alkohol;                                        // Speicher f�r Alkohol Ja/Nein
    uint8_t kohlensaeure;                                   // Speicher f�r Alkohol Ja/Nein
    uint8_t stelle;                                         // Speicher f�r Position der Zutat in der Maschine
    uint8_t menge;                                          // Speicher f�r Menge der Zutat in der Maschine
    uint32_t position_motor;                                // Speicher f�r Position der Zutat in der Maschine
    struct zutat_Maschine* next;                            // Pointer auf das zuvor eingef�gte Getr�nk
    struct zutat_Maschine* prev;                            // Pointer auf das danach eingef�gte Getr�nk
};
typedef struct zutat_Maschine zutatMaschine_t;              // Typedef f�r Struct zutat_t

zutatMaschine_t *aktuelle_Zutat_in_Maschine_ohne_KS;        // Pointer auf aktuelle Zutat (ohne Kohlens�ure) in Maschine
zutatMaschine_t *buffer_zut_in_Maschine_ohne_KS;              // Pointer auf zuletzt in die Liste eingef�gte Zutat (ohne Kohlens�ure) in der Maschine
zutatMaschine_t *head_zut_in_Maschine_ohne_KS;              // Pointer auf zuletzt in die Liste eingef�gte Zutat (ohne Kohlens�ure) in der Maschine
zutatMaschine_t *tail_zut_in_Maschine_ohne_KS;              // Pointer auf erstes in die Liste eingef�gte Zutat (ohne Kohlens�ure) in der Maschine

zutatMaschine_t *aktuelle_Zutat_ausser_Maschine_mit_KS;     // Pointer auf aktuelle Zutat (mit Kohlens�ure) in Maschine
zutatMaschine_t *buffer_zut_ausser_Maschine_mit_KS;           // Pointer auf zuletzt in die Liste eingef�gte Zutat (mit Kohlens�ure) in der Maschine
zutatMaschine_t *head_zut_ausser_Maschine_mit_KS;           // Pointer auf zuletzt in die Liste eingef�gte Zutat (mit Kohlens�ure) in der Maschine
zutatMaschine_t *tail_zut_ausser_Maschine_mit_KS;           // Pointer auf erstes in die Liste eingef�gte Zutat (mit Kohlens�ure) in der Maschine



/******************************************************************************************************************************/
// Die Zutaten Files werden auch nach Kohens�ure sortiert.
/******************************************************************************************************************************/
struct zutat_file {                                         // Struckt f�r Zutaten-Files (wird nach Anzahl Files initialisiert)
    uint8_t file;                                           // Speicher f�r Variable des Filenamens
    struct zutat_file * next;                               // Pointer auf zuletzt in die Liste eingef�gtes Zutaten-File
    struct zutat_file * prev;                               // Pointer auf erstes in die Liste eingef�gtes Zutaten-File
};
typedef struct zutat_file zutat_file_t;                     // Typedef f�r Struct zutat_file_t

zutat_file_t * buffer_zutat_file;                           // Pointer auf aktuelle Zutat in Maschine

zutat_file_t * aktuelles_Zutat_file_in_Maschine_ohne_KS;                        // Pointer auf aktuelle Zutat in Maschine
zutat_file_t * head_Zutat_file_in_Maschine_ohne_KS;                             // Pointer auf zuletzt in die Liste eingef�gtes Zutaten-File
zutat_file_t * tail_Zutat_file_in_Maschine_ohne_KS;                             // Pointer auf erstes in die Liste eingef�gtes Zutaten-File

zutat_file_t * aktuelles_Zutat_file_ausser_Maschine_mit_KS;                        // Pointer auf aktuelle Zutat in Maschine
zutat_file_t * head_Zutat_file_ausser_Maschine_mit_KS;                             // Pointer auf zuletzt in die Liste eingef�gtes Zutaten-File
zutat_file_t * tail_Zutat_file_ausser_Maschine_mit_KS;                             // Pointer auf erstes in die Liste eingef�gtes Zutaten-File



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
struct zutat_list_node {                                    // Struckt f�r die aktuelle Zutat (wird nur 1 Mal initialisiert)
	zutat_file_t * zutat_xy;                                // Pointer auf den Speicher f�r den Namen der aktuellen Zutat
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
	zutatMaschine_t * zutat_xy;                                // Pointer auf den Speicher f�r den Namen der aktuellen Zutat
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
// Listen-Funktionen Zutat in und ausserhalb der Maschinen
/******************************************************************************************************************************/
// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutatMaschine_t (Eingrag wird am head eingef�gt)
zutatMaschine_t *insert_zutat_Maschine_at_head(zutatMaschine_t **head_zutat, zutatMaschine_t **tail_zutat, zutatMaschine_t *zutat_to_insert);

// Funktion zur Alloziierung des Speicherplatzes f�r zutatMaschine_t
zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor);



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Files mit/ohne Kohlens�ure
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes f�r zutat_file_t
zutat_file_t *create_new_zutat_file(uint8_t file_to_create);

// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_file_t (Eingrag wird am head eingef�gt)
zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t **tail, zutat_file_t *file_to_insert);



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes f�r zutat_list_node_t
zutat_list_node_t *create_new_list_node_zut_file( zutat_file_t * file_to_link);

// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_list_node_t (Eingrag wird am head eingef�gt)
zutat_list_node_t *insert_zutat_list_node_at_head(zutat_list_node_t **head, zutat_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Listen-Funktionen f�r die Listen-Anzeige (schnelleres Finden der aktuellen Position)
/******************************************************************************************************************************/
// Funktion zur Alloziierung des Speicherplatzes f�r zutat_list_node_t
zutatMaschine_list_node_t *create_new_list_node_zutMaschine_file( zutatMaschine_t * file_to_link);

// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_list_node_t (Eingrag wird am head eingef�gt)
zutatMaschine_list_node_t *insert_zutatMaschine_list_node_at_head(zutatMaschine_list_node_t **head, zutatMaschine_list_node_t *file_to_insert);



/******************************************************************************************************************************/
// Eeprom-Variable
/******************************************************************************************************************************/
uint8_t * address_Standardwiederherstellung;                // EEprom address-Pointer f�r die Standardwiederherstellung



#endif /* ZUTATEN_H_ */