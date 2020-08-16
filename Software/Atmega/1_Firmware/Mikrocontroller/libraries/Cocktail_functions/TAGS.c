/*
 * RFID.c
 *
 * Created: 25.06.2020 20:45:35
 *  Author: kimsc
 */ 

#include "TAGS.h"

void RFID_init(void)
{
/******************************************************************************************************************
*******************************************************************************************************************
**	                                       ************************************************************************
**	- Initialisierungen für Zutaten-Liste  ************************************************************************
**	                                       ************************************************************************
*******************************************************************************************************************
*******************************************************************************************************************
Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.		 */

	head_tag = NULL;									// Erster Tag auf NULL
	tail_tag = NULL;									// Letzter Tag auf NULL
	
	rfid_tag_t * tmp;									// Temporärer RFID-Pointer für Hinzufügen der Tags
	
/******************************************************************************************************************

	- Ab hier werden die Zutaten gesucht, welche sich auf der SD-Karte befinden. (Z0.txt bis Z100.txt)
	- Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
	- Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

******************************************************************************************************************/
		
	for (int8_t count = 0 ; count <= 12; count++)
	{
	// String mit Name des Textfiles erstellen (Z0.txt bis Z199.txt)
		// Nummer des Existierenden Files in der Liste ablegen (head_zutat = letzt hinzugefügtes Getränk)
		tmp = create_new_tag("Hoi", count, count);
		head_tag = insert_tag_at_head(&head_tag, tmp);
 	}
}

rfid_tag_t *create_new_tag(char * cocktail_name, uint8_t tag_nummer, uint8_t tag_ID)
{
	// Alloziiere Speicher für die Struct-Variabeln gemäss Struct zutatMaschine_t
	rfid_tag_t *newTag = calloc(1,sizeof(rfid_tag_t));
	
	// Alloziiere Speicher für den Namen und setze den Struct-Pointer name darauf
	newTag->cocktail_name = calloc(21,sizeof(char));
	
	// Schreibe die Werte in entsprechende Variabeln des Structs
	newTag->tag_nummer = tag_nummer;
	newTag->tag_ID = tag_ID;
	newTag->prev = NULL;
	newTag->next = NULL;
	
	strcpy((char *)newTag->cocktail_name,(const char *)cocktail_name);

	return newTag;
}



rfid_tag_t *insert_tag_at_head(rfid_tag_t **head_tag, rfid_tag_t *tag_to_insert)
{
	/*****************************************************************************
	**==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
	**             **   *   *   *   *   *| |*   *   *   *   *   **              **
	**	Head-Zutat ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-Zutat	**
	**             **   *   *   *   *   *| |*   *   *   *   *   **              **
	**<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
	******************************************************************************/

	// Setze die vorhergehende und nachkommende Zutat der einzufügenden Zutat
	tag_to_insert->next = (*head_tag);				// (1. Zutat = NULL)
	tag_to_insert->prev = NULL;
	
	// Falls keine head-Zutat besteht, ist die einzufügende Zutat die tail-Zutat
	if((*head_tag) == NULL)
	{
		(tail_tag) = tag_to_insert;
	}
	
	// Besteht eine head-Zutat, ist deren zuvorkommende Zutat die einzufügende Zutat
	// und die zuvorkommende Zutat der einzufügenden Zutat ist die tail-Zutat
	else
	{
		(*head_tag)->prev = tag_to_insert;
		tag_to_insert->prev = (tail_tag);
	}
	
	// head-Zutat ist jetzt die einzufügende Zutat
	// Das nachkommende File der tail-Zutat ist jetzt die neue head-Zutat
	(*head_tag) = tag_to_insert;
	(tail_tag)->next = (*head_tag);
	
	return tag_to_insert;
}
