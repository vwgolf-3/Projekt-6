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
	//	      1, if file is already existing and flag = VERIFY
	//		  2, if file name is incompatible
	
	readFile( READ, (unsigned char *)buff);
		
	// Trennungszeichen definieren, Pointer initialisiern für Abschnitte
	char delimiter[] = ":,{}\r\n";
	char *ptr;
	// initialisieren und ersten Abschnitt erstellen (1. Kopf)
	
	ptr = strtok((char *)buffer, delimiter);
	
	//	Abschnitt in buffer extrahieren:
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
		
		if (pruefe_kopf(ptr, "Mengen"))
		{
			ptr = strtok(NULL, delimiter);
			uint8_t counter = 0;

			while(*ptr != ';' && counter < 13)
			{

				uint8_t count = 0;
				uint8_t run = 1;
				aktuelleZutatInMaschine = tail_zut_in_Maschine;
				
				while (run)
				{
					if((compare_string((char *)ptr, (char *)aktuelleZutatInMaschine->name) == 0))
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
					aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
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
	
/**************************************************************************************************************

			- Initialisierungen

**************************************************************************************************************/

	head_getraenk_file = NULL;
	getraenk_file_t * tmp2;

/**************************************************************************************************************

			- Ab hier werden die Getränke gesucht, welche sich auf der SD-Karte befinden. (0.txt bis 100.txt)
			- Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
			- Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

**************************************************************************************************************/
	for ( int8_t count = 0 ; count <= 100; count++)
	{
		char buff[15] = {'\0'};
		itoa(count, (char *)buff,10);
		strcat((char *)buff, (const char *)".txt");
		if(readFile(VERIFY, (unsigned char *)buff)==1)
		{
			if(check_existence(count))
			{
				tmp2 = create_new_getraenk_file(count);
				head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
			}
		}
	}
		
/**************************************************************************************************************

			- Für ein Getränk wird eine Struktur werdendet. Hier wird solch eine Struktur
			  des Typs getraenk_t initialisiert
			- Werden Daten benötigt, wird zuerst ein File in diese eine Getränke-Struktur eingelesen
			  und erst dann verarbeitet.

**************************************************************************************************************/

	aktuellesGetraenk = create_new_getraenk("12345678901234567890",0,0,0);

/**************************************************************************************************************

			- Hier wird der aktuelle Pointer auf den Listeneintrag gesetzt und das aktuelle File in die
			  Struktur des Type getraenk_t geladen.

**************************************************************************************************************/

	aktuellesGetraenk_file = tail_getraenk_file;
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t alkohol, uint8_t picture)
{
	getraenk_t *newGetraenk = calloc(1,sizeof(getraenk_t));
	size_t n1 = strlen((const char *)name)+1;
	size_t n2 = 13;
	
	newGetraenk->name = calloc(n1,sizeof(char));
	newGetraenk->mengen = calloc(n2,sizeof(uint8_t));
	
	newGetraenk->alkohol = alkohol;
	
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



void add_drink_to_eeprom(uint8_t * add, char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol)
{
	int i = 0;
	uint8_t n = strlen((const char *) name );
	char temp_name[n];
	char temp_mengen[12];
	
	strncpy(temp_name, (const char *)name, n);
	strncpy(temp_mengen, (const char *)mengen, 12);
	
	eeprom_write_byte(add,n);
	
	for(i = 0; i<n ; i++)
	{
		eeprom_write_byte((add+i+1), temp_name[i]);
		_delay_ms(5);
	}

	for(i = n; i<(n+12) ; i++)
	{
		eeprom_write_byte((add+i+1), temp_mengen[i]);
		_delay_ms(5);
	}
		
	
	i++;
	eeprom_write_byte((add+i+1),value);
	
	i++;
	eeprom_write_byte((add+i+1),alkohol);
	
	_delay_ms(5);

	i++;
	eeprom_write_byte((add+i+1),'\0');
	
	address_getraenk = add+i+1;
}

int8_t count_eeprom_drinks(uint8_t * add)
{
	int8_t cnt = 0;
	int8_t val = 0;
	int8_t n = 0;
	do 
	{
		cnt++;
		val = eeprom_read_byte(add+n);
		if(n == '\0')
		{
			return cnt;
		}
		n += val + 15 + 1;
		add += n;
	}while (n !='\0');
	return 0;
}

getraenk_t * read_drink_from_eemprom(uint8_t * add)
{
	getraenk_t * drink;
	
	int i = 0;
	uint8_t n = eeprom_read_byte(add);					// Schauen, wie lang der String ist
	char name[n];
	uint8_t mengen [12];
	uint8_t alkohol = 0;
	
	for (i = 0; i<n ; i++)
	{
		*(name+i) = eeprom_read_byte(add+i+1);			// Schreibe Name Byte für Byte in übergebenen Speicher-Pointer (uint8_t name *)
		_delay_ms(5);
	}
	*(name+i)='\0';										// Beende Array mit Terminator '\0'
	_delay_ms(5);

	for(i = n; i<(n+12) ; i++)
	{
		*(mengen+i) = eeprom_read_byte((add+i+1));		// Schreibe Mengen Byte für Byte in üergebenen Speicher-Pointer (uint8_t mengen *)
		_delay_ms(5);
	}
	*(mengen+i)='\0';									// Beende Array mit Terminator '\0'
	_delay_ms(5);
		
	i++;
	alkohol = eeprom_read_byte(add+i+1);				// Alkoholgehalt aus EEPROM lesen und in Variable ablegen
	
	_delay_ms(5);
	
	drink = create_new_getraenk(name, mengen, alkohol, 24);
	
	i++;
	address_getraenk = add+i+1;
	
	return drink;
}

void add_EEPROM_drinks_to_list(uint8_t * add)
{
// 	getraenk_t * drink = 0;
	
// 	while (eeprom_read_byte(address_getraenk) != '\0')
// 	{
// 		drink = read_drink_from_eemprom(address_getraenk);
// 		insert_at_head(&head_getraenk, drink);
// 	}
}

void delete_EEPROM (uint8_t * add)
{
	for(int i = 0 ; i<4059 ; i++)
	{
		eeprom_write_byte(add+i,'\0');
	}
}

getraenk_file_t *create_new_getraenk_file(uint8_t file_to_create)
{
	getraenk_file_t *newFile = calloc(1,sizeof(getraenk_file_t));
	newFile->file = file_to_create;
	return newFile;
}

getraenk_file_t *insert_file_at_head(getraenk_file_t **head, getraenk_file_t *file_to_insert)
{	
		file_to_insert->next = *head;
		file_to_insert->prev = NULL;
		
		if((*head) == NULL)
		{
			tail_getraenk_file = file_to_insert;
		} else
		{
			(*head)->prev = file_to_insert;
			file_to_insert->prev = tail_getraenk_file;
		}
		*head = file_to_insert;
		tail_getraenk_file->next = *head;
		return file_to_insert;
}