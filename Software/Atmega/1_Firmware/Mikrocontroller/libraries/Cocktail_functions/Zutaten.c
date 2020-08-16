/*
 * Zutaten.c
 *
 * Created: 19.05.2020 20:10:22
 *  Author: kimsc
 */ 

#include "Zutaten.h"
#include <util/delay.h>

void zutaten_init(void)
{
// Beim Initialisierungsvorgang der Zutaten werden zuerst alle verf�gbaren gespeicherten Zutaten auf der SD-Karte
// gesucht und deren Nummer in einer File-Liste gespeichert. Anhand dieser Liste (des Typs zutat_file_t) k�nnen 
// die Zutaten-Files w�hrend des Programmflusses stets aufgerufen, gespeichert und zur Verarbeitung in den
// Programmspeicher geladen werden. Die Daten werden zur Verwendung in ein Struct (des Typs zutat_t) geladen und
// von dort aus wieder aufgerufen.

// Beim Initialisierungsvorgang der Zutaten, welche sich effektiv in der Maschine befinden, wird nur ein File von
// der SD-Karte in den Programmspeicher geladen. Darin befinden sich eingestellten Zutaten, sodass der User die
// Einstellungen nicht jedes Mal einstellen muss, bevor er die Maschine braucht. Im Gegensatz zur vorhergehenden
// Initialisierung werden alle Informationen im Programmspeicher abgelegt. Das File wird nur noch aufgerufen, um
// eventualle �nderungen der in der Maschine befindenden Zutaten im File anzupassen.

// Die Standardeinstellungen werden im EEPROM abgelegt. Bei einer Werkseinstellung werden die Files auf der
// SD-Karte gel�scht und neue Files gem�ss den im EEPROM vorhandenen Getr�nke und Zutaten wiederhergestellt.
	
	address_Standardwiederherstellung  = (uint8_t *)0;
	
/******************************************************************************************************************
*******************************************************************************************************************
**	                                       ************************************************************************
**	- Initialisierungen f�r Zutaten-Liste  ************************************************************************
**	                                       ************************************************************************
*******************************************************************************************************************
*******************************************************************************************************************
Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.		 */

	head_zutat_file = NULL;								// Erstes hinzugef�gtes File auf NULL
	tail_zutat_file = NULL;								// Letztes hinzugef�gtes File auf NULL
	
	zutat_file_t * tmp;									// Tempor�rer Zutaten-File-Pointer f�r Hinzuf�gen der Zutat
	
	// Buffer
	char buff_init_textfiles_zutat[21] = {'\0'};		// Buffer f�r Filename
	char buff2_init_textfiles_zutat[5] = {'\0'};		// Buffer f�r Integer to ASCI umwandlung
		
/******************************************************************************************************************

	- Ab hier werden die Zutaten gesucht, welche sich auf der SD-Karte befinden. (Z0.txt bis Z100.txt)
	- F�r jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
	- Im Eintrag ist der Name des Files gespeichert, und erm�glicht einen sp�teren Aufruf.

******************************************************************************************************************/
		
	for (int8_t count = 0 ; count <= 30; count++)
	{
		// String mit Name des Textfiles erstellen (Z0.txt bis Z199.txt)
		strcpy((char *)buff_init_textfiles_zutat, (const char *)"Z");
		itoa(count, (char *)buff2_init_textfiles_zutat, 10);
		strcat((char *)buff_init_textfiles_zutat, (const char *)buff2_init_textfiles_zutat);
		strcat((char *)buff_init_textfiles_zutat, (const char *)".txt");
		
		// Pr�fen ob File existiert
		if(readFile(VERIFY, (unsigned char *)buff_init_textfiles_zutat)==1)
		{
			// Nummer des Existierenden Files in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
			tmp = create_new_zutat_file(count);
			head_zutat_file = insert_zutat_file_at_head(&head_zutat_file, tmp);
		}
 	}

/******************************************************************************************************************

	- F�r eine Zutat wird eine Struktur werdendet. Mittels create_zutat wird Speicherplatz daf�r alloziiert.
	- Werden Daten ben�tigt, wird mittels lese_textfile_in_zutat ein File in diese eine Zutaten-Struktur
	  eingelesen. Die ben�tigten Infos werden daraus extrahiert und im Speicher abgelegt.
	- Damit die aktuelle Zutat auf das File1 zeigt, zeigt es auf den Tail der Liste (Erstes hinzugef�gt).

******************************************************************************************************************/

	aktuelle_zutat = create_zutat();
	aktuelles_zutat_file = tail_zutat_file;

/******************************************************************************************************************
*******************************************************************************************************************
**																	  *********************************************
**	- Initialisierungen f�r die in der Maschine vorhandenen Zutaten.  *********************************************
**																	  *********************************************
*******************************************************************************************************************
*******************************************************************************************************************
Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.		 */

	head_zut_in_Maschine = NULL;						// Erste hinzugef�gte Zutat auf NULL
	tail_zut_in_Maschine = NULL;						// Letzte hinzugef�gte Zutat auf NULL
	
	zutatMaschine_t * tmp_zutat_Maschine;				// Tempor�rer Zutaten-File-Pointer f�r Hinzuf�gen der Zutat
	
	char delimiter[] = ",\r\n";							// Trennungszeichen definieren				(strtok)
	char *ptr;											// Pointer f�r Abschnitte initialisieren	(strtok)
	
	char buff1[21] = {'\0'};							// Buffer f�r Name der Zutat
	uint8_t buff2;										// Buffer f�r Status der Zutat
	uint8_t buff3;										// Buffer f�r Alkohol Ja/Nein der Zutat
	
	char buff4[20] = {'\0'};							// Buffer f�r Filename "M.txt"

	uint8_t position = 0;								// Variable, welche die Position des Getr�nks hochz�hlt.

/******************************************************************************************************************

	- String des Filenames wird in Buffer geschrieben	"M.txt"
	- File wird gelesen und in buffer geschrieben		"M.txt"
	
	Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
	********************************************************************
	(Getraenkename1),Status1,(Alkohol ja=1, nein=0)
	(Getraenkename2),Status2,(Alkohol ja=1, nein=0)
	(Getraenkename3),Status3,(Alkohol ja=1, nein=0)
	...
	(Getraenkename12),Status12,(Alkohol ja=1, nein=0)

******************************************************************************************************************/

	strcpy((char *)buff4, (const char *)"M.txt");
	readFile(READ, (unsigned char *)buff4);
	
/******************************************************************************************************************

	- Ab hier wird das File "M.txt" zerlegt und die eingeschriebenen Getr�nke, sowie deren Status und
	  Alkoholgehalt Ja/Nein in die Liste geschrieben.
	- Die Daten sind dann jederzeit verf�gbar, der alloziierte Speicher reicht, um die Zutaten umzuschreiben
	  w�hrend des Betriebs. (20 Zeichen maximum)
	- Damit die aktuelle Zutat auf das File1 zeigt, zeigt es auf den Tail der Liste (Erstes hinzugef�gt).

******************************************************************************************************************/
	
	// Extrahiere erstes Maschinen-Zutat aus File "M.txt"
	ptr = strtok((char *)buffer, delimiter);							// Abschnitt Name Zutat
	strcpy((char *)buff1,ptr);											// Kopiere Name in Buffer
	ptr = strtok(NULL, delimiter);										// Abschnitt Status
	buff2 = atoi(ptr);													// Schreibe ASCI-Status in Integer-Buffer
	ptr = strtok(NULL, delimiter);										// Abschnitt Alkohol Ja/Nein
	buff3 = atoi(ptr);													// Schreibe ASCI-JA//Nein in Integer-Buffer
	
	// Speicher alloziieren
	tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, position);
	
	// Zutat in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
	head_zut_in_Maschine = insert_zutat_Maschine_at_head(&head_zut_in_Maschine,&tail_zut_in_Maschine, tmp_zutat_Maschine);

	// Position inkrementieren
	position++;

	while(ptr != NULL)
	{
		ptr = strtok(NULL, delimiter);									// Abschnitt Name Zutat
		strcpy((char *)buff1,ptr);										// Kopiere Name in Buffer
		ptr = strtok(NULL, delimiter);									// Abschnitt Status
		buff2 = atoi(ptr);												// Schreibe ASCI-Status in Integer-Buffer
		ptr = strtok(NULL, delimiter);									// Abschnitt Alkohol Ja/Nein
		buff3 = atoi(ptr);												// Schreibe ASCI-JA//Nein in Integer-Buffer
		
		// Falls der Name des Getr�nkes >=1 ist, erstelle neue Zutat in Maschine
		if (strlen((const char *)buff1)>=1)
		{
			// Speicher alloziieren
			tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, position);
			
			// Zutat in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
			head_zut_in_Maschine = insert_zutat_Maschine_at_head(&head_zut_in_Maschine,&tail_zut_in_Maschine, tmp_zutat_Maschine);

			// Position inkrementieren
			position++;
		}
	}
	
	// Aktuelle Zutat auf Tail zeigen lassen (Erstes hinzugef�gt)
	aktuelleZutatInMaschine = tail_zut_in_Maschine;
}



zutat_t *create_zutat()
{
	// Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutat_t
	zutat_t *newZutat = calloc(1,sizeof(zutat_t));

	// Alloziiere Speicher f�r den Namen und setze den Struct-Pointer name darauf
	newZutat->name = calloc(21,sizeof(char));
	
	// Schreibe 0 in die alloziierte Struct-Variable alkohol
	newZutat->alkohol = 0;

	// Initialisiere den Speicher, auf den der Pointer zeigt mit '\0'
	for (int i=0; i<(21); i++)
	{
		*(char *)(newZutat->name + i) = '\0';
	}
	
	return newZutat;
}



zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t k)
{
	// Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutatMaschine_t
	zutatMaschine_t *newZutat = calloc(1,sizeof(zutatMaschine_t));
	
	// Alloziiere Speicher f�r den Namen und setze den Struct-Pointer name darauf
	newZutat->name = calloc(21,sizeof(char));
	
	// Schreibe die Werte in entsprechende Variabeln des Structs
	newZutat->status = status;
	newZutat->position = k;
	newZutat->alkohol = alkohol;
	newZutat->prev = NULL;
	newZutat->next = NULL;
	
	// Initialisiere den Speicher, auf den der Pointer zeigt mit '\0'
	for (int i=0; i<21; i++)
	{
		*(char *)(newZutat->name + i) = *(char *)(name + i);
	}

	return newZutat;
}



zutatMaschine_t *insert_zutat_Maschine_at_head(zutatMaschine_t **head_zutat, zutatMaschine_t ** tail_zutat, zutatMaschine_t *zutat_to_insert)
{
/*****************************************************************************
**==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
**             **   *   *   *   *   *| |*   *   *   *   *   **              **
**	Head-Zutat ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-Zutat	**
**             **   *   *   *   *   *| |*   *   *   *   *   **              **
**<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
******************************************************************************/

	// Setze die vorhergehende und nachkommende Zutat der einzuf�genden Zutat
	zutat_to_insert->next = (*head_zutat);				// (1. Zutat = NULL)
	zutat_to_insert->prev = NULL;
	
	// Falls keine head-Zutat besteht, ist die einzuf�gende Zutat die tail-Zutat
	if((*head_zutat) == NULL)
	{
		(*tail_zutat) = zutat_to_insert;
	}
	
	// Besteht eine head-Zutat, ist deren zuvorkommende Zutat die einzuf�gende Zutat
	// und die zuvorkommende Zutat der einzuf�genden Zutat ist die tail-Zutat
	else
	{
		(*head_zutat)->prev = zutat_to_insert;
		zutat_to_insert->prev = (*tail_zutat);
	}
	
	// head-Zutat ist jetzt die einzuf�gende Zutat
	// Das nachkommende File der tail-Zutat ist jetzt die neue head-Zutat
	(*head_zutat) = zutat_to_insert;
	(*tail_zutat)->next = (*head_zutat);
	
	return zutat_to_insert;
}



zutat_file_t *create_new_zutat_file(uint8_t file_to_create)
{
	// Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutat_file_t
	zutat_file_t *newFile = calloc(1,sizeof(zutat_file_t));
	
	// Schreibe die Nummer des Files in entsprechende Variabeln des Structs
	newFile->file = file_to_create;
	
	return newFile;
}



zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t *file_to_insert)
{
/*****************************************************************************
**==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
**             **   *   *   *   *   *| |*   *   *   *   *   **              **
**	Head-File  ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-File	**
**             **   *   *   *   *   *| |*   *   *   *   *   **              **
**<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
******************************************************************************/

	// Setze das vorhergehende und nachkommende File des einzuf�genden Files
	file_to_insert->next = *head;
	file_to_insert->prev = NULL;
	
	// Falls keine head-Zutat besteht, ist die einzuf�gende Zutat die tail-Zutat
	if((*head) == NULL)
	{
		tail_zutat_file = file_to_insert;
	}
	
	// Besteht ein head-File, ist dessen zuvorkommends File das einzuf�gende File
	// und das zuvorkommende File des einzuf�genden Files ist das tail-File
	else
	{
		(*head)->prev = file_to_insert;
		file_to_insert->prev = tail_zutat_file;
	}
	
	// head-File ist jetzt das einzuf�gende File
	// Das nachkommende File des tail-Files ist jetzt das neue head-File
	*head = file_to_insert;
	tail_zutat_file->next = *head;
	
	return file_to_insert;
}