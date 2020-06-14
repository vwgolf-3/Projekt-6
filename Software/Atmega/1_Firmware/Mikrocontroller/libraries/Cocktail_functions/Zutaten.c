/*
 * Zutaten.c
 *
 * Created: 19.05.2020 20:10:22
 *  Author: kimsc
 */ 

#include "Zutaten.h"


void zutaten_init(void)
{
	address_zut  = (uint8_t *)0;
	 
	char zutaten[12][20] =
	{
		"7Up",
		"Coca-Cola",
		"Ginger-Ale",
		"Orangensaft",
		"Limettensaft",
		"Zitronensaft",
		"Grenadinensirup",
		"Blue Curacao",
		"Gin",
		"Triple Sec",
		"Whisky",
		"Wodka"
	};

	head_zut = NULL;
	zutat_t *tmp;
	for ( int i = 0 ; i<12;i++)
	{
		tmp = create_neue_zutat(zutaten[i], i);
		head_zut = insert_zutat_at_head(&head_zut, tmp);
	}
	aktuelleZutat = head_zut;
	 
/**************************************************************************************************************

			- Initialisierungen

**************************************************************************************************************/

	head_zutat_test = NULL;
	zutat_test_t * tmp3;
	head_zutat_file = NULL;
	zutat_file_t * tmp4;

/**************************************************************************************************************

			- Ab hier werden die Getr?nke gesucht, welche sich auf der SD-Karte befinden. (0.txt bis 100.txt)
			- F?r jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
			- Im Eintrag ist der Name des Files gespeichert, und erm?glicht einen sp?teren Aufruf.

**************************************************************************************************************/
	char buff_init_textfiles_zutat[21] = {'\0'};
	char buff2_init_textfiles_zutat[5] = {'\0'};
		
	for (int8_t count = 0 ; count <= 100; count++)
	{
		strcpy((char *)buff_init_textfiles_zutat, (const char *)"Z");
		itoa(count, (char *)buff2_init_textfiles_zutat, 10);
		strcat((char *)buff_init_textfiles_zutat, (const char *)buff2_init_textfiles_zutat);
		strcat((char *)buff_init_textfiles_zutat, (const char *)".txt");
		char filename[25] = {'\0'};
		strcpy((char *)filename, (const char *)buff_init_textfiles_zutat);
		
		if(readFile(VERIFY, (unsigned char *)filename)==1)
		{
			tmp4 = create_new_zutat_file(count);
			head_zutat_file = insert_zutat_file_at_head(&head_zutat_file, tmp4);
		}

 	}

/**************************************************************************************************************

			- F?r ein Getr?nk wird eine Struktur werdendet. Hier wird solch eine Struktur
			  des Typs getraenk_t initialisiert
			- Werden Daten ben?tigt, wird zuerst ein File in diese eine Getr?nke-Struktur eingelesen
			  und erst dann verarbeitet.

**************************************************************************************************************/

	tmp3 = create_neue_zutat_test("12345678901234567890",0);
	aktuelle_zutat_test = insert_zutat_at_head_test(&head_zutat_test, &tail_zutat_test, tmp3);

/**************************************************************************************************************

			- Hier wird der aktuelle Pointer auf den Listeneintrag gesetzt und das aktuelle File in die
			  Struktur des Type getraenk_t geladen.

**************************************************************************************************************/

	lese_textfile_in_zutat(aktuelles_zutat_file->file);
	aktuelles_zutat_file = tail_zutat_file;







	// Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
	char delimiter[] = ",\r\n";
	char *ptr;
	// initialisieren und ersten Abschnitt erstellen (1. Kopf)
	
	char buff1[21] = {'\0'};
	uint8_t buff2;
	uint8_t buff3;
	// "Zutaten.txt" lesen (File wird in char buffer[512] geschrieben)
	//return: 0, if normal operation or flag is READ
	//	      1, if file is already existing and flag = VERIFY
	//		  2, if file name is incompatible
	
	char buff33[20] = {'\0'};
	strcpy((char *)buff33, (const char *)"Maschine.txt");
	readFile(READ, (unsigned char *)buff33);

	//	Abschnitt in buffer extrahieren:
/*
	Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
	********************************************************************
	(Getraenkename1),(Alkohol ja=1, nein=0)
	(Getraenkename2),(Alkohol ja=1, nein=0)
	(Getraenkename3),(Alkohol ja=1, nein=0)
	.
	.
	.
	(GetraenkenameX),(Alkohol ja=1, nein=0)
*/ 

	head_zut_in_Maschine = NULL;
	zutatMaschine_t * tmp_zutat_Maschine;
	
	// Extrahiere erstes Maschinen-Getraenk aus File "Maschine.txt"
	ptr = strtok((char *)buffer, delimiter);
	strcpy((char *)buff1,ptr);
	ptr = strtok(NULL, delimiter);
	buff2 = atoi(ptr);
	ptr = strtok(NULL, delimiter);
	buff3 = atoi(ptr);
	
	uint8_t k = 0;
	tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, k);
	k++;
	head_zut_in_Maschine = insert_zutat_Maschine_at_head(&head_zut_in_Maschine,&tail_zut_in_Maschine, tmp_zutat_Maschine);
	
	while(ptr != NULL)
	{
		ptr = strtok(NULL, delimiter);
		strcpy((char *)buff1,ptr);
		ptr = strtok(NULL, delimiter);
		buff2 = atoi(ptr);
		ptr = strtok(NULL, delimiter);
		buff3 = atoi(ptr);
		if (strlen((const char *)buff1)>=1)
		{
		tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, k);
		k++;
		head_zut_in_Maschine = insert_zutat_Maschine_at_head(&head_zut_in_Maschine,&tail_zut_in_Maschine, tmp_zutat_Maschine);
			Uart_Transmit_IT_PC(head_zut_in_Maschine->name);
			Uart_Transmit_IT_PC("\r");
		}
	}
	aktuelleZutatInMaschine = head_zut_in_Maschine;
	 
	 
}

zutat_t *create_neue_zutat(char * name, char k)
{
	zutat_t *newZutat = calloc(1,sizeof(zutat_t));
 	size_t n1 = strlen((const char *)name)+1;

 	newZutat->name = calloc(n1,sizeof(char));
	 
	newZutat->nr = k;
	newZutat->prev = NULL;
	newZutat->next = NULL;
	 
 	for (int i=0; i<(n1); i++)
 	{
 		*(char *)(newZutat->name + i) = *(char *)(name + i);
 	}

	return newZutat;
}

zutat_t *insert_zutat_at_head(zutat_t **head_zut, zutat_t *zutat_to_insert)
{
	zutat_to_insert->next = (*head_zut);
	zutat_to_insert->prev = NULL;
	
	if((*head_zut) == NULL)
	{
		tail_zut = zutat_to_insert;
	} else
	{
		(*head_zut)->prev = zutat_to_insert;
		zutat_to_insert->prev = tail_zut;
	}
	*head_zut = zutat_to_insert;
	tail_zut->next = *head_zut;
	return zutat_to_insert;
}

zutat_test_t *create_neue_zutat_test(char * name, uint8_t alkohol)
{
	zutat_test_t *newZutat = calloc(1,sizeof(zutat_test_t));
	size_t n1 = strlen((const char *)name)+1;

	newZutat->name = calloc(n1,sizeof(char));
	newZutat->alkohol = alkohol;
	newZutat->prev = NULL;
	newZutat->next = NULL;
	
	for (int i=0; i<(n1); i++)
	{
		*(char *)(newZutat->name + i) = *(char *)(name + i);
	}

	return newZutat;
}

zutat_test_t *insert_zutat_at_head_test(zutat_test_t **head_zutat_test, zutat_test_t ** tail_zutat, zutat_test_t *zutat_to_insert)
{
	zutat_to_insert->next = (*head_zutat_test);
	zutat_to_insert->prev = NULL;
	
	if((*head_zutat_test) == NULL)
	{
		*tail_zutat = zutat_to_insert;
	} else
	{
		(*head_zutat_test)->prev = zutat_to_insert;
		zutat_to_insert->prev = *tail_zutat;
	}
	*head_zutat_test = zutat_to_insert;
	(*tail_zutat)->next = *head_zutat_test;
	return zutat_to_insert;
}

zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t k)
{
	zutatMaschine_t *newZutat = calloc(1,sizeof(zutatMaschine_t));
	size_t n1 = strlen((const char *)name)+1;

	newZutat->name = calloc(21,sizeof(char));

	newZutat->status = status;
	newZutat->position = k;
	newZutat->alkohol = alkohol;
	newZutat->prev = NULL;
	newZutat->next = NULL;
	
	for (int i=0; i<(n1); i++)
	{
		*(char *)(newZutat->name + i) = *(char *)(name + i);
	}

	return newZutat;
}

zutatMaschine_t *insert_zutat_Maschine_at_head(zutatMaschine_t **head_zutat, zutatMaschine_t ** tail_zutat, zutatMaschine_t *zutat_to_insert)
{
	zutat_to_insert->next = (*head_zutat);
	zutat_to_insert->prev = NULL;
	
	if((*head_zutat) == NULL)
	{
		*tail_zutat = zutat_to_insert;
	} else
	{
		(*head_zutat)->prev = zutat_to_insert;
		zutat_to_insert->prev = *tail_zutat;
	}
	*head_zutat = zutat_to_insert;
	(*tail_zutat)->next = *head_zutat;
	return zutat_to_insert;
}

zutat_file_t *create_new_zutat_file(uint8_t file_to_create)
{
	zutat_file_t *newFile = calloc(1,sizeof(zutat_file_t));
	newFile->file = file_to_create;
	return newFile;
}

zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t *file_to_insert)
{
	file_to_insert->next = *head;
	file_to_insert->prev = NULL;
	
	if((*head) == NULL)
	{
		tail_zutat_file = file_to_insert;
	} else
	{
		(*head)->prev = file_to_insert;
		file_to_insert->prev = tail_zutat_file;
	}
	*head = file_to_insert;
	tail_zutat_file->next = *head;
	return file_to_insert;
}