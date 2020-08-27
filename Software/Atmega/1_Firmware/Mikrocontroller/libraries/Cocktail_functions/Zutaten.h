/*
 * Zutaten.h
 *
 * Created: 19.05.2020 20:10:36
 *  Author: kimsc
 */ 


#ifndef ZUTATEN_H_
#define ZUTATEN_H_

/******************************************************************************************************************************/
#include <avr/eeprom.h>										// Wird ben�tigt um in das EEPROM zu schreiben
#include <stdlib.h>											// Wird ben�tigt f�r Variabelnumwandlungen (z.B itoa(), atoi(), ...)
#include <string.h>											// Wird ben�tigt w�rd Stringoperationen (z.B strcpy(), strcat(), ...)
#include "../SD-Karte/FAT32.h"								// Wird ben�tigt f�r Lese- und Schreiboperationen auf die SD-Karte
/******************************************************************************************************************************/


/******************************************************************************************************************************/
uint8_t * address_Standardwiederherstellung;				// EEprom address-Pointer f�r die Standardwiederherstellung
/******************************************************************************************************************************/


/******************************************************************************************************************************/
struct zutat{												// Struckt f�r die aktuelle Zutat (wird nur 1 Mal initialisiert)
	char * name;											// Pointer auf den Speicher f�r den Namen der aktuellen Zutat
	uint8_t alkohol;										// Speicher f�r Alkohol Ja/Nein
	uint8_t kohlensaeure;									// Speicher f�r Alkohol Ja/Nein
};
typedef struct zutat zutat_t;								// Typedef f�r Struct zutat_t

zutat_t *aktuelle_zutat;									// Pointer auf aktuelle Zutat
/******************************************************************************************************************************/


/******************************************************************************************************************************/
struct zutat_Maschine{										// Struckt f�r Zutaten in Maschine (wird 12 Mal initialisiert)
	char * name;											// Pointer auf den Speicher f�r den Namen der Zutat in Maschine
	uint8_t status;											// Speicher f�r den Status (KEINGETRAENK=0, VOLL=1, LEER=2)
	uint8_t alkohol;										// Speicher f�r Alkohol Ja/Nein
	uint8_t kohlensaeure;										// Speicher f�r Alkohol Ja/Nein
	uint8_t position;										// Speicher f�r Position der Zutat in der Maschine
	struct zutat_Maschine* next;							// Pointer auf das zuvor eingef�gte Getr�nk
	struct zutat_Maschine* prev;							// Pointer auf das danach eingef�gte Getr�nk
};
typedef struct zutat_Maschine zutatMaschine_t;				// Typedef f�r Struct zutat_t

zutatMaschine_t *aktuelleZutatInMaschine;					// Pointer auf aktuelle Zutat in Maschine
zutatMaschine_t *head_zut_in_Maschine;						// Pointer auf zuletzt in die Liste eingef�gte Zutat in der Maschine
zutatMaschine_t *tail_zut_in_Maschine;						// Pointer auf erstes in die Liste eingef�gte Zutat in der Maschine
/******************************************************************************************************************************/


/******************************************************************************************************************************/
struct zutat_file{											// Struckt f�r Zutaten-Files (wird nach Anzahl Files initialisiert)
	uint8_t file;											// Speicher f�r Variable des Filenamens
	struct zutat_file * next;								// Pointer auf zuletzt in die Liste eingef�gtes Zutaten-File
	struct zutat_file * prev;								// Pointer auf erstes in die Liste eingef�gtes Zutaten-File
};
typedef struct zutat_file zutat_file_t;						// Typedef f�r Struct zutat_file_t

zutat_file_t * aktuelles_zutat_file;						// Pointer auf aktuelle Zutat in Maschine
zutat_file_t * head_zutat_file;								// Pointer auf zuletzt in die Liste eingef�gtes Zutaten-File
zutat_file_t * tail_zutat_file;								// Pointer auf erstes in die Liste eingef�gtes Zutaten-File
/******************************************************************************************************************************/


/******************************************************************************************************************************/
void zutaten_init(void);									// Funktion f�r die Initialisierung der Zutaten und deren Speicher
/******************************************************************************************************************************/


/******************************************************************************************************************************/
zutat_t *create_zutat();									// Funktion zur Alloziierung des Speicherplatzes f�r zutat_t
/******************************************************************************************************************************/


/******************************************************************************************************************************/
// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutatMaschine_t (Eingrag wird am head eingef�gt)
zutatMaschine_t *insert_zutat_Maschine_at_head(zutatMaschine_t **head_zutat, zutatMaschine_t **tail_zutat, zutatMaschine_t *zutat_to_insert);

// Funktion zur Alloziierung des Speicherplatzes f�r zutatMaschine_t
zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k);
/******************************************************************************************************************************/


/******************************************************************************************************************************/
// Funktion f�r das aneinanderreihen der Listeneintr�ge f�r zutat_file_t (Eingrag wird am head eingef�gt)
zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t *file_to_insert);

// Funktion zur Alloziierung des Speicherplatzes f�r zutat_file_t
zutat_file_t *create_new_zutat_file(uint8_t file_to_create);
/******************************************************************************************************************************/

#endif /* ZUTATEN_H_ */