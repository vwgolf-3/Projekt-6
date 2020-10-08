/*
 * Getraenk.c
 *
 * Created: 05.04.2020 22:46:46
 *  Author: kimsc
 */

#include "Getraenk.h"
#include "../Cocktail_functions/Cocktail_functions.h"

// https://www.youtube.com/watch?v=VOpjAHCee7c

uint8_t check_existence(uint8_t file)
{
    uint8_t exists = 1;

    // Erstellen eines Strings in Form von: "file.txt"
    char buff[20];
    itoa((int)file,(char *)buff,10);
    char * txt = ".txt";
    strcat((char *)buff,txt);

    // "file.txt" lesen (File wird in char buffer[512] geschrieben)
    //return: 0, if normal operation or flag is READ
    //        1, if file is already existing and flag = VERIFY
    //        2, if file name is incompatible

    readFile( READ, (unsigned char *)buff);

    // Trennungszeichen definieren, Pointer initialisiern für Abschnitte
    char delimiter[] = ":,{}\r\n";
    char *ptr;
    // initialisieren und ersten Abschnitt erstellen (1. Kopf)

    ptr = strtok((char *)buffer, delimiter);

    //  Abschnitt in buffer extrahieren:
    /*
        Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
        ********************************************************************
        Name:Getraenk1
        Mengen:
        Zutat1:75
        Zutat2:25
        ;
        Alkohol:1
        Bild:2
    */
    while(ptr != NULL) {
        // Kopf prüfen und jeweilige Aktion ausführen

        if (strcmp(ptr, "Mengen")==0)
        {
            ptr = strtok(NULL, delimiter);
            uint8_t counter = 0;

            while(*ptr != ';' && counter < 13)
            {

                uint8_t count = 0;
                uint8_t run = 1;

                while (run)
                {
                    if((strcmp((char *)ptr, (char *)aktuelle_Zutat_in_Maschine_ohne_KS->name) == 0)||(strcmp((char *)ptr, (char *)aktuelle_Zutat_ausser_Maschine_mit_KS->name) == 0))
                    {
                        run = 0;
                        ptr = strtok(NULL, delimiter);
                    }
                    if (count >=12)
                    {
                        run = 0;
                        exists = 0;
                    }
                    count ++;
                    aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->next;
                    aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->next;
                }
                ptr = strtok(NULL, delimiter);
                counter ++;
            }
        }

        // Neuer Kopf suchen und ptr darauf zeigen lassen
        ptr = strtok(NULL, delimiter);
    }
    return exists;
}


void cocktails_init(void)
{
    Liste = ALLE;
    number_getraenk_alle_ = 0;
    number_getraenk_alle = &number_getraenk_alle_;
	number_list_ = 0;
	number_list = &number_list_;
    /**************************************************************************************************************

                - Initialisierungen

    **************************************************************************************************************/

    head_getraenk_file_alle = NULL;

    /**************************************************************************************************************

                - Ab hier werden die Getränke gesucht, welche sich auf der SD-Karte befinden. (0.txt bis 100.txt)
                - Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
                - Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

    **************************************************************************************************************/
    for (int8_t count = 0 ; count <= 50; count++)
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
    display_from_beg(number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);

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
}

getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t alkohol, uint8_t kohlensaeure, uint8_t picture)
{
    getraenk_t *newGetraenk = calloc(1,sizeof(getraenk_t));
    size_t n1 = strlen((const char *)name)+1;
    size_t n2 = 25;

    newGetraenk->name = calloc(n1,sizeof(char));
    newGetraenk->mengen = calloc(n2,sizeof(uint8_t));

    newGetraenk->alkohol = alkohol;

    newGetraenk->kohlensaeure = kohlensaeure;

    newGetraenk->picture = picture;

    // Setze den Wert, auf den der Pointer newGetraenk->name an der Stelle i zeigt, auf den Wert, auf den der Pointer name an der Stelle i zeigt.
    int i = 0;
    for (i=0; i<(n1-1); i++)
    {
        *(char *)(newGetraenk->name + i) = *(char *)(name + i);
    }
    *(char *)(newGetraenk->name + (i+1)) = *(char *)(name + (i+1));

    // Setze den Wert, auf den der Pointer newGetraenk->mengern an der Stelle i zeigt, auf den Wert, auf den der Pointer mengen an der Stelle i zeigt.
    for (i=0; i<(n2-1); i++)
    {
        *(char *)(newGetraenk->mengen + i) = *(char *)(mengen + i);
    }
    *(char *)(newGetraenk->mengen + (i+1)) = '\0';

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
	newFile->getraenk_file = getraenk_to_point_on;
	return newFile;
}

file_list_node_t *delete_
(file_list_node_t **head)
{
	file_list_node_t * newHead = (*head);
	newHead = newHead->next;
	free(*head);
	newHead->prev=tail_list_node_getraenk;
	tail_list_node_getraenk->next = newHead;
	Uart_Transmit_IT_PC("delete: ");
	lese_textfile_in_getraenk((*head)->getraenk_file->file);
	Uart_Transmit_IT_PC(aktuellesGetraenk->name);
	Uart_Transmit_IT_PC("\r");
	Uart_Transmit_IT_PC("Newhead: ");
	lese_textfile_in_getraenk(newHead->getraenk_file->file);
	Uart_Transmit_IT_PC(aktuellesGetraenk->name);
	Uart_Transmit_IT_PC("\r");
	return newHead;
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