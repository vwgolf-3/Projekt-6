/*
 * Getraenk.c
 *
 * Created: 05.04.2020 22:46:46
 *  Author: kimsc
 */

#include "Getraenk.h"
#include "../Cocktail_functions/Cocktail_functions.h"

// https://www.youtube.com/watch?v=VOpjAHCee7c


void cocktails_init(void)
{
    Liste = ALLE;
    number_getraenk_alle_ = 0;
    number_getraenk_alle = &number_getraenk_alle_;
	
	number_list_getraenke_alle_val = 0;
	number_list_getranke_alle = &number_list_getraenke_alle_val;
	
    /**************************************************************************************************************

                - Initialisierungen

    **************************************************************************************************************/

    head_getraenk_file_alle = NULL;

    /**************************************************************************************************************

                - Ab hier werden die Getränke gesucht, welche sich auf der SD-Karte befinden. (0.txt bis 100.txt)
                - Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
                - Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

    **************************************************************************************************************/
    for (int8_t count = 0 ; count <= COUNT_UNTIL; count++)
    {
        char buff[15] = {'\0'};
        itoa(count, (char *)buff,10);
        strcat((char *)buff, (const char *)".txt");
        if(readFile(VERIFY, (unsigned char *)buff)==1)
        {
            if(check_existence(count))
            {
				insert_at_end(count, &number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);
            }
        }
    }
	Uart_Transmit_IT_PC("Cocktails: ");
    display_from_beg(number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);
	Uart_Transmit_IT_PC("\r");

    /**************************************************************************************************************

                - Für ein Getränk wird eine Struktur werdendet. Hier wird solch eine Struktur
                  des Typs getraenk_t initialisiert
                - Werden Daten benötigt, wird zuerst ein File in diese eine Getränke-Struktur eingelesen
                  und erst dann verarbeitet.

    **************************************************************************************************************/

    aktuellesGetraenk = create_new_getraenk("12345678901234567890",0,0,0,0);

    /**************************************************************************************************************

                - Hier wird der aktuelle Pointer auf den Listeneintrag gesetzt und das aktuelle File in die
                  Struktur des Type getraenk_t geladen.

    **************************************************************************************************************/

    actual_getraenk_file_alle = head_getraenk_file_alle;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
	
	insert_at_end_3(actual_getraenk_file_alle, &number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
    display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
}

getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t alkohol, uint8_t kohlensaeure, uint8_t picture)
{
    getraenk_t *newGetraenk = calloc(1,sizeof(getraenk_t));

    newGetraenk->name = calloc(21,sizeof(char));

    newGetraenk->alkohol = alkohol;

    newGetraenk->kohlensaeure = kohlensaeure;

    newGetraenk->picture = picture;

    // Setze den Wert, auf den der Pointer newGetraenk->name an der Stelle i zeigt, auf den Wert, auf den der Pointer name an der Stelle i zeigt.
    int i = 0;
    for (i=0; i<21; i++)
    {
        *(char *)(newGetraenk->name + i) = '\0';
    }
    return newGetraenk;
}

file_node_t *create_new_getraenk_file(uint8_t file_to_create)
{
    file_node_t *newFile = calloc(1,sizeof(file_node_t));
    newFile->file = file_to_create;
    return newFile;
}

file_node_t *create_new_getraenk_file_2(uint8_t file_to_create)
{
    file_node_t *newFile = calloc(1,sizeof(file_node_t));
    newFile->file = file_to_create;
    return newFile;
}

file_node_t *insert_file_at_head(file_node_t **head, file_node_t *file_to_insert)
{
	file_to_insert->next = *head;
	file_to_insert->prev = NULL;

	if((*head) == NULL)
	{
		tail_getraenk_file_alle = file_to_insert;
	} else
	{
		(*head)->prev = file_to_insert;
		file_to_insert->prev = tail_getraenk_file_alle;
	}
		file_to_insert->prev = tail_getraenk_file_alle;
	*head = file_to_insert;
	tail_getraenk_file_alle->next = *head;
	return file_to_insert;
}

file_list_node_t *create_new_list_node_file(file_node_t * getraenk_to_point_on)
{
	file_list_node_t *newFile = calloc(1,sizeof(file_list_node_t));
	newFile->_file = getraenk_to_point_on;
	return newFile;
}

file_list_node_t *insert_list_node_at_head(file_list_node_t **head, file_list_node_t *file_to_insert)
{
	file_to_insert->next = *head;
	file_to_insert->prev = NULL;

	if((*head) == NULL)
	{
		tail_list_node_getraenk = file_to_insert;
	} else
	{
		(*head)->prev = file_to_insert;
		file_to_insert->prev = tail_list_node_getraenk;
	}
	*head = file_to_insert;
	tail_list_node_getraenk->next = *head;
	return file_to_insert;
}