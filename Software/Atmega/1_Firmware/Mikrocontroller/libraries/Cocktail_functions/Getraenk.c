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
	
	
/**************************************************************************************************************

			- Initialisierungen

**************************************************************************************************************/

	head_getraenk = NULL;
	getraenk_t * tmp;
	head_getraenk_file = NULL;
	getraenk_file_t * tmp2;

/**************************************************************************************************************

			- Ab hier werden die Getränke gesucht, welche sich auf der SD-Karte befinden. (0.txt bis 100.txt)
			- Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
			- Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

**************************************************************************************************************/

	for ( uint8_t i = 0 ; i<100;i++){
		char buff[15] = {'\0'};
		itoa(i, (char *)buff,10);
		strcat((char *)buff, (const char *)".txt");
		if(readFile(VERIFY, (unsigned char *)buff)==1)
		{
			tmp2 = create_new_getraenk_file(i);
			head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
		}
	}
	
/**************************************************************************************************************

			- Für ein Getränk wird eine Struktur werdendet. Hier wird solch eine Struktur
			  des Typs getraenk_t initialisiert
			- Werden Daten benötigt, wird zuerst ein File in diese eine Getränke-Struktur eingelesen
			  und erst dann verarbeitet.

**************************************************************************************************************/

	tmp = create_new_getraenk("12345678901234567890",0,0,0,0);
	aktuellesGetraenk = insert_at_head(&head_getraenk, tmp);

/**************************************************************************************************************

			- Hier wird der aktuelle Pointer auf den Listeneintrag gesetzt und das aktuelle File in die
			  Struktur des Type getraenk_t geladen.

**************************************************************************************************************/

	aktuellesGetraenk_file = tail_getraenk_file;
	lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

void showlist(void)
{
	getraenk_t * temporary= head_getraenk;
 	char buff[3] = {0};
	char buff2[3] = {0};
		
	while (temporary != 0)
	{
		Uart_Transmit_IT_PC("Name: ");
		Uart_Transmit_IT_PC((char *)temporary->name);
		_delay_ms(2);
	
 		itoa(temporary->value,buff,10);
		Uart_Transmit_IT_PC(": Wert = ");
		Uart_Transmit_IT_PC((char *)buff);
		_delay_ms(2);
		
 		Uart_Transmit_IT_PC(", Mengen = ");
		
		uint8_t buff[3] = {0};
		
		for (int i = 0; i <12 ; i++)
		{
			itoa(temporary->mengen[i],(char *)buff, 10);
			Uart_Transmit_IT_PC((char *) buff);
			Uart_Transmit_IT_PC(", ");
			_delay_ms(2);
		}
		_delay_ms(2);
		
		Uart_Transmit_IT_PC(", Alkohol = ");
 		itoa(temporary->alkohol,(char *)buff2,10);
		Uart_Transmit_IT_PC((char *)buff2);
 		Uart_Transmit_IT_PC(".\n\r");
		_delay_ms(2);
		temporary = temporary->next;
	}
_delay_ms(2);
}

void printlist(void)
{
	getraenk_t *temporary2 = head_getraenk;
	char buff[3] = {0};
		
	while (temporary2 != NULL){
		Uart_Transmit_IT_PC((char *)temporary2->name);
		itoa(temporary2->value,buff,10);
		Uart_Transmit_IT_PC((char *)buff);
		Uart_Transmit_IT_PC("\n\r");
		_delay_ms(1);
		
		temporary2 = temporary2->next;
	}
}

int8_t length_list(void)
{
	getraenk_t *tmp = head_getraenk;
	int8_t n = 0;
	
	while (tmp != NULL)
	{
		n++;
		
		tmp = tmp->next;
	}
	
		return n;
}

getraenk_t *create_new_getraenk(char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol, uint8_t picture)
{
	getraenk_t *newGetraenk = calloc(1,sizeof(getraenk_t));
	size_t n1 = strlen((const char *)name)+1;
	size_t n2 = 13;
	
	newGetraenk->name = calloc(n1,sizeof(char));
	newGetraenk->mengen = calloc(n2,sizeof(uint8_t));
	
	newGetraenk->alkohol = alkohol;
	newGetraenk->value = value;
	
	newGetraenk->picture = picture;
	
	int i = 0;
	for (i=0; i<(n1-1); i++)
	{
		*(char *)(newGetraenk->name + i) = *(char *)(name + i);
	}
	*(char *)(newGetraenk->name + (i+1)) = *(char *)(name + (i+1));
	
	
	for (i=0; i<(n2-1); i++)
	{
		*(char *)(newGetraenk->mengen + i) = *(char *)(mengen + i);
	}
	*(char *)(newGetraenk->mengen + (i+1)) = '\0';

	return newGetraenk;
}


getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert)
{
	getraenk_to_insert->next = *head;
	getraenk_to_insert->prev = NULL;
	
	if((*head) == NULL)
	{
		tail_getraenk = getraenk_to_insert;
	} else
	{
		(*head)->prev = getraenk_to_insert;
		getraenk_to_insert->prev = tail_getraenk;
	}
	*head = getraenk_to_insert;
	tail_getraenk->next = *head;
	return getraenk_to_insert;
}

getraenk_t *find_getraenk(getraenk_t *head, char * name)
{
	getraenk_t *tmp = head;
	while (tmp != NULL)
	{
		if(tmp->name == name)	return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t* newgetraenk)
{
	newgetraenk->next = getraenk_to_insert_after->next;
	getraenk_to_insert_after->next = newgetraenk;
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
	uint8_t value = 0;
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
	value = eeprom_read_byte(add+i+1);					// Value aus EEPROM lesen und in Variable ablegen
	
	i++;
	alkohol = eeprom_read_byte(add+i+1);				// Alkoholgehalt aus EEPROM lesen und in Variable ablegen
	
	_delay_ms(5);
	
	drink = create_new_getraenk(name, mengen, value, alkohol, 24);
	
	i++;
	address_getraenk = add+i+1;
	
	return drink;
}

void add_EEPROM_drinks_to_list(uint8_t * add)
{
	getraenk_t * drink = 0;
	
	while (eeprom_read_byte(address_getraenk) != '\0')
	{
		drink = read_drink_from_eemprom(address_getraenk);
		insert_at_head(&head_getraenk, drink);
	}
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