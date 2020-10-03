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
    aktuelle_zutat = create_zutat();

    /******************************************************************************************************************
    *******************************************************************************************************************
    **                                         ************************************************************************
    **  - Initialisierungen f�r Zutaten-Liste  ************************************************************************
    **                                         ************************************************************************
    *******************************************************************************************************************
    *******************************************************************************************************************
    Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.       */

    head_Zutat_file_in_Maschine_ohne_KS = NULL;                             // Erstes hinzugef�gtes File auf NULL
    tail_Zutat_file_in_Maschine_ohne_KS = NULL;                             // Letztes hinzugef�gtes File auf NULL
	
    head_Zutat_file_ausser_Maschine_mit_KS = NULL;                          // Erstes hinzugef�gtes File auf NULL
    tail_Zutat_file_ausser_Maschine_mit_KS = NULL;                          // Letztes hinzugef�gtes File auf NULL

    zutat_file_t * tmp;                                 // Tempor�rer Zutaten-File-Pointer f�r Hinzuf�gen der Zutat

    // Buffer
    char buff_init_textfiles_zutat[21] = {'\0'};        // Buffer f�r Filename
    char buff2_init_textfiles_zutat[5] = {'\0'};        // Buffer f�r Integer to ASCI umwandlung

    /******************************************************************************************************************

        - Ab hier werden die Zutaten gesucht, welche sich auf der SD-Karte befinden. (Z0.txt bis Z100.txt)
        - F�r jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
        - Im Eintrag ist der Name des Files gespeichert, und erm�glicht einen sp�teren Aufruf.

    ******************************************************************************************************************/

    for (int8_t count = 1 ; count <= 30; count++)
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
            lese_textfile_in_zutat(count);
//             Uart_Transmit_IT_PC("Einlesen: ");
//             Uart_Transmit_IT_PC(aktuelle_zutat->name);
//             Uart_Transmit_IT_PC(", ");
//             char buff[5] = {'\0'};
//             itoa(aktuelle_zutat->kohlensaeure, (char *)buff,10);
//             Uart_Transmit_IT_PC((char *)buff);
//             Uart_Transmit_IT_PC("\r");
            if (aktuelle_zutat->kohlensaeure == 0)
            {
                head_Zutat_file_in_Maschine_ohne_KS = insert_zutat_file_at_head(&head_Zutat_file_in_Maschine_ohne_KS, &tail_Zutat_file_in_Maschine_ohne_KS, tmp);
//                 Uart_Transmit_IT_PC("Head ohne: ");
//                 Uart_Transmit_IT_PC(aktuelle_zutat->name);
//                 Uart_Transmit_IT_PC("\r");
            }
            else
            {
                head_Zutat_file_ausser_Maschine_mit_KS = insert_zutat_file_at_head(&head_Zutat_file_ausser_Maschine_mit_KS, &tail_Zutat_file_ausser_Maschine_mit_KS, tmp);
//                 Uart_Transmit_IT_PC("Head mit: ");
//                 Uart_Transmit_IT_PC(aktuelle_zutat->name);
//                 Uart_Transmit_IT_PC("\r");
            }
        }
    }

    /******************************************************************************************************************

        - F�r eine Zutat wird eine Struktur werdendet. Mittels create_zutat wird Speicherplatz daf�r alloziiert.
        - Werden Daten ben�tigt, wird mittels lese_textfile_in_zutat ein File in diese eine Zutaten-Struktur
          eingelesen. Die ben�tigten Infos werden daraus extrahiert und im Speicher abgelegt.
        - Damit die aktuelle Zutat auf das File1 zeigt, zeigt es auf den Tail der Liste (Erstes hinzugef�gt).

    ******************************************************************************************************************/

//     aktuelles_Zutat_file_in_Maschine_ohne_KS = tail_Zutat_file_in_Maschine_ohne_KS;
//     Uart_Transmit_IT_PC("In Maschine: \r");
//     do
//     {
//         lese_textfile_in_zutat(aktuelles_Zutat_file_in_Maschine_ohne_KS->file);
//         Uart_Transmit_IT_PC("Einlesen1: ");
//         Uart_Transmit_IT_PC(aktuelle_zutat->name);
//         Uart_Transmit_IT_PC("\r");
//         aktuelles_Zutat_file_in_Maschine_ohne_KS = aktuelles_Zutat_file_in_Maschine_ohne_KS->prev;
//     } while (aktuelles_Zutat_file_in_Maschine_ohne_KS != tail_Zutat_file_in_Maschine_ohne_KS);
//
//  aktuelles_Zutat_file_ausser_Maschine_mit_KS = tail_Zutat_file_ausser_Maschine_mit_KS;
//     Uart_Transmit_IT_PC("Ausser Maschine: \r");
//     do
//     {
//      lese_textfile_in_zutat(aktuelles_Zutat_file_ausser_Maschine_mit_KS->file);
//      Uart_Transmit_IT_PC("Einlesen1: ");
//      Uart_Transmit_IT_PC(aktuelle_zutat->name);
//      Uart_Transmit_IT_PC("\r");
//      aktuelles_Zutat_file_ausser_Maschine_mit_KS = aktuelles_Zutat_file_ausser_Maschine_mit_KS->prev;
//     } while (aktuelles_Zutat_file_ausser_Maschine_mit_KS != tail_Zutat_file_ausser_Maschine_mit_KS);

    /******************************************************************************************************************
    *******************************************************************************************************************
    **                                                                    *********************************************
    **  - Initialisierungen f�r die in der Maschine vorhandenen Zutaten.  *********************************************
    **                                                                    *********************************************
    *******************************************************************************************************************
    *******************************************************************************************************************
    Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.       */

    head_zut_in_Maschine_ohne_KS = NULL;                        // Erste hinzugef�gte Zutat auf NULL
    tail_zut_in_Maschine_ohne_KS = NULL;                        // Letzte hinzugef�gte Zutat auf NULL
    head_zut_ausser_Maschine_mit_KS = NULL;                        // Erste hinzugef�gte Zutat auf NULL
    tail_zut_ausser_Maschine_mit_KS = NULL;                        // Letzte hinzugef�gte Zutat auf NULL

    zutatMaschine_t * tmp_zutat_Maschine;               // Tempor�rer Zutaten-File-Pointer f�r Hinzuf�gen der Zutat

    char delimiter[] = ",\r\n";                         // Trennungszeichen definieren              (strtok)
    char *ptr;                                          // Pointer f�r Abschnitte initialisieren   (strtok)

    char buff1[21] = {'\0'};                            // Buffer f�r Name der Zutat
    uint8_t buff2;                                      // Buffer f�r Status der Zutat
    uint8_t buff3;                                      // Buffer f�r Alkohol Ja/Nein der Zutat
    uint8_t buff4;                                      // Buffer f�r Kohlens�ure Ja/Nein der Zutat

    char buff5[20] = {'\0'};                            // Buffer f�r Filename "M.txt"

    uint8_t position = 0;                               // Variable, welche die Position des Getr�nks hochz�hlt.

    uint32_t abstand = 1000000;

    /******************************************************************************************************************

        - String des Filenames wird in Buffer geschrieben   "M.txt"
        - File wird gelesen und in buffer geschrieben       "M.txt"

        Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
        ********************************************************************
        (Getraenkename1),Status1,(Alkohol ja=1, nein=0)
        (Getraenkename2),Status2,(Alkohol ja=1, nein=0)
        (Getraenkename3),Status3,(Alkohol ja=1, nein=0)
        ...
        (Getraenkename12),Status12,(Alkohol ja=1, nein=0)

    ******************************************************************************************************************/

    strcpy((char *)buff5, (const char *)"M.txt");
    readFile(READ, (unsigned char *)buff5);

    /******************************************************************************************************************

        - Ab hier wird das File "M.txt" zerlegt und die eingeschriebenen Getr�nke, sowie deren Status und
          Alkoholgehalt Ja/Nein in die Liste geschrieben.
        - Die Daten sind dann jederzeit verf�gbar, der alloziierte Speicher reicht, um die Zutaten umzuschreiben
          w�hrend des Betriebs. (20 Zeichen maximum)
        - Damit die aktuelle Zutat auf das File1 zeigt, zeigt es auf den Tail der Liste (Erstes hinzugef�gt).

    ******************************************************************************************************************/

    // Extrahiere erstes Maschinen-Zutat aus File "M.txt"
    ptr = strtok((char *)buffer, delimiter);                            // Abschnitt Name Zutat
    strcpy((char *)buff1,ptr);                                          // Kopiere Name in Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Status
    buff2 = atoi(ptr);                                                  // Schreibe ASCI-Status in Integer-Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Alkohol Ja/Nein
    buff3 = atoi(ptr);                                                  // Schreibe ASCI-JA//Nein in Integer-Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Kohlens�ure Ja/Nein
    buff4 = atoi(ptr);                                                  // Schreibe ASCI-JA//Nein in Integer-Buffer

    // Speicher alloziieren
    tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, buff4, position, abstand*position);

    // Zutat in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
    head_zut_in_Maschine_ohne_KS = insert_zutat_Maschine_at_head(&head_zut_in_Maschine_ohne_KS,&tail_zut_in_Maschine_ohne_KS, tmp_zutat_Maschine);

    // Position inkrementieren
    position++;

    ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat

    while(strcmp(ptr, ";")!=0)
    {
        strcpy((char *)buff1,ptr);                                      // Kopiere Name in Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        buff2 = atoi(ptr);                                              // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        buff3 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlens�ure Ja/Nein
        buff4 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer

        // Falls der Name des Getr�nkes >=1 ist, erstelle neue Zutat in Maschine
        if (strlen((const char *)buff1)>=1)
        {
            // Speicher alloziieren
            tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, buff4, position, abstand*position);

            // Zutat in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
            head_zut_in_Maschine_ohne_KS = insert_zutat_Maschine_at_head(&head_zut_in_Maschine_ohne_KS,&tail_zut_in_Maschine_ohne_KS, tmp_zutat_Maschine);

            // Position inkrementieren
            position++;
        }
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat
    }

    // Aktuelle Zutat auf Tail zeigen lassen (Erstes hinzugef�gt)
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;

    head_zut_ausser_Maschine_mit_KS = NULL;
    tail_zut_ausser_Maschine_mit_KS = NULL;
    position = 0;

    ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat

    while(strcmp(ptr, ";")!=0)
    {
        strcpy((char *)buff1,ptr);                                      // Kopiere Name in Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        buff2 = atoi(ptr);                                              // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        buff3 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlens�ure Ja/Nein
        buff4 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer

        // Falls der Name des Getr�nkes >=1 ist, erstelle neue Zutat in Maschine
        if (strlen((const char *)buff1)>=1)
        {
            // Speicher alloziieren
            tmp_zutat_Maschine = create_neue_zutat_Maschine((char *)buff1,buff2, buff3, buff4, position, abstand*position);

            // Zutat in der Liste ablegen (head_zutat = letzt hinzugef�gtes Getr�nk)
            head_zut_ausser_Maschine_mit_KS = insert_zutat_Maschine_at_head(&head_zut_ausser_Maschine_mit_KS,&tail_zut_ausser_Maschine_mit_KS, tmp_zutat_Maschine);

            // Position inkrementieren
            position++;
        }

        ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat
    }
    aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
}



zutat_t *create_zutat()
{
    // Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutat_t
    zutat_t *newZutat = calloc(1,sizeof(zutat_t));

    // Alloziiere Speicher f�r den Namen und setze den Struct-Pointer name darauf
    newZutat->name = calloc(21,sizeof(char));

    // Schreibe 0 in die alloziierte Struct-Variable alkohol
    newZutat->alkohol = 0;

    // Schreibe 0 in die alloziierte Struct-Variable kohlensaeure
    newZutat->kohlensaeure = 0;

    // Initialisiere den Speicher, auf den der Pointer zeigt mit '\0'
    for (int i=0; i<(21); i++)
    {
        *(char *)(newZutat->name + i) = '\0';
    }

    return newZutat;
}

zutatMaschine_t *create_neue_zutat_Maschine(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor)
{
    // Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutatMaschine_t
    zutatMaschine_t *newZutat = calloc(1,sizeof(zutatMaschine_t));

    // Alloziiere Speicher f�r den Namen und setze den Struct-Pointer name darauf
    newZutat->name = calloc(21,sizeof(char));

    // Schreibe die Werte in entsprechende Variabeln des Structs
    newZutat->status = status;
    newZutat->stelle = k;
    newZutat->position_motor = positon_motor;
    newZutat->alkohol = alkohol;
    newZutat->kohlensaeure = kohlensaeure;
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
    **  Head-Zutat ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-Zutat  **
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
    ******************************************************************************/

    // Setze die vorhergehende und nachkommende Zutat der einzuf�genden Zutat
    zutat_to_insert->next = (*head_zutat);              // (1. Zutat = NULL)
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



zutat_file_t *insert_zutat_file_at_head(zutat_file_t **head, zutat_file_t **tail, zutat_file_t *file_to_insert)
{
    /*****************************************************************************
    **==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **  Head-File  ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-File   **
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
    ******************************************************************************/

    // Setze das vorhergehende und nachkommende File des einzuf�genden Files
    file_to_insert->next = *head;
    file_to_insert->prev = NULL;

    // Falls keine head-Zutat besteht, ist die einzuf�gende Zutat die tail-Zutat
    if((*head) == NULL)
    {
        (*tail) = file_to_insert;
    }

    // Besteht ein head-File, ist dessen zuvorkommends File das einzuf�gende File
    // und das zuvorkommende File des einzuf�genden Files ist das tail-File
    else
    {
        (*head)->prev = file_to_insert;
    file_to_insert->prev = (*tail);
    }

    // head-File ist jetzt das einzuf�gende File
    // Das nachkommende File des tail-Files ist jetzt das neue head-File
    *head = file_to_insert;
    (*tail)->next = *head;

    return file_to_insert;
}

zutat_list_node_t *create_new_list_node_zut_file( zutat_file_t * file_to_link)
{
    // Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutat_file_t
    zutat_list_node_t *newFile = calloc(1,sizeof(zutat_list_node_t));

    // Schreibe die Nummer des Files in entsprechende Variabeln des Structs
    newFile->zutat_xy = file_to_link;

    return newFile;
}



zutat_list_node_t *insert_zutat_list_node_at_head(zutat_list_node_t **head, zutat_list_node_t *file_to_insert)
{
    /*****************************************************************************
    **==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **  Head-File  ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-File   **
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
    ******************************************************************************/

    // Setze das vorhergehende und nachkommende File des einzuf�genden Files
    file_to_insert->next = *head;
    file_to_insert->prev = NULL;

    // Falls keine head-Zutat besteht, ist die einzuf�gende Zutat die tail-Zutat
    if((*head) == NULL)
    {
        tail_zutat_list_node = file_to_insert;
    }

    // Besteht ein head-File, ist dessen zuvorkommends File das einzuf�gende File
    // und das zuvorkommende File des einzuf�genden Files ist das tail-File
    else
    {
        (*head)->prev = file_to_insert;
    }

    // head-File ist jetzt das einzuf�gende File
    // Das nachkommende File des tail-Files ist jetzt das neue head-File
    file_to_insert->prev = tail_zutat_list_node;
    *head = file_to_insert;
    tail_zutat_list_node->next = *head;

    return file_to_insert;
}






zutatMaschine_list_node_t *create_new_list_node_zutMaschine_file( zutatMaschine_t * file_to_link)
{
    // Alloziiere Speicher f�r die Struct-Variabeln gem�ss Struct zutatMaschine_list_node_t
    zutatMaschine_list_node_t *newFile = calloc(1,sizeof(zutatMaschine_list_node_t));

    // Schreibe die Nummer des Files in entsprechende Variabeln des Structs
    newFile->zutat_xy = file_to_link;

    return newFile;
}



zutatMaschine_list_node_t *insert_zutatMaschine_list_node_at_head(zutatMaschine_list_node_t **head, zutatMaschine_list_node_t *file_to_insert)
{
    /*****************************************************************************
    **==>**next******==>*==>*==>*==>*==>*| |*==>*==>*==>*==>*==>*******next**==>**
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **  Head-File  ** X * X * X * X * X *| |* X * X * X * X * X **  Tail-File   **
    **             **   *   *   *   *   *| |*   *   *   *   *   **              **
    **<==**prev******<==*<==*<==*<==*<==*| |*<==*<==*<==*<==*<==*******prev**<==**
    ******************************************************************************/

    // Setze das vorhergehende und nachkommende File des einzuf�genden Files
    file_to_insert->next = *head;
    file_to_insert->prev = NULL;

    // Falls keine head-Zutat besteht, ist die einzuf�gende Zutat die tail-Zutat
    if((*head) == NULL)
    {
        tail_zutatMaschine_list_node = file_to_insert;
    }

    // Besteht ein head-File, ist dessen zuvorkommends File das einzuf�gende File
    // und das zuvorkommende File des einzuf�genden Files ist das tail-File
    else
    {
        (*head)->prev = file_to_insert;
        file_to_insert->prev = tail_zutatMaschine_list_node;
    }

    // head-File ist jetzt das einzuf�gende File
    // Das nachkommende File des tail-Files ist jetzt das neue head-File
    *head = file_to_insert;
    tail_zutatMaschine_list_node->next = *head;

    return file_to_insert;
}






