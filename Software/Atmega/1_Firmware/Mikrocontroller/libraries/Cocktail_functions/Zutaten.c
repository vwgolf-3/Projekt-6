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
// Beim Initialisierungsvorgang der Zutaten werden zuerst alle verfügbaren gespeicherten Zutaten auf der SD-Karte
// gesucht und deren Nummer in einer File-Liste gespeichert. Anhand dieser Liste (des Typs file_node_t) können
// die Zutaten-Files während des Programmflusses stets aufgerufen, gespeichert und zur Verarbeitung in den
// Programmspeicher geladen werden. Die Daten werden zur Verwendung in ein Struct (des Typs zutat_t) geladen und
// von dort aus wieder aufgerufen.

// Beim Initialisierungsvorgang der Zutaten, welche sich effektiv in der Maschine befinden, wird nur ein File von
// der SD-Karte in den Programmspeicher geladen. Darin befinden sich eingestellten Zutaten, sodass der User die
// Einstellungen nicht jedes Mal einstellen muss, bevor er die Maschine braucht. Im Gegensatz zur vorhergehenden
// Initialisierung werden alle Informationen im Programmspeicher abgelegt. Das File wird nur noch aufgerufen, um
// eventualle Änderungen der in der Maschine befindenden Zutaten im File anzupassen.

// Die Standardeinstellungen werden im EEPROM abgelegt. Bei einer Werkseinstellung werden die Files auf der
// SD-Karte gelöscht und neue Files gemäss den im EEPROM vorhandenen Getränke und Zutaten wiederhergestellt.

    address_Standardwiederherstellung  = (uint8_t *)0;
    aktuelle_zutat = create_zutat();

    number_zutaten_ohne_ = 0;
    number_zutaten_mit_ = 0;
    number_zutaten_mit = &number_zutaten_mit_;
    number_zutaten_ohne = &number_zutaten_ohne_;

    number_zutaten_maschine_ohne_ = 0;
    number_zutaten_maschine_mit_ = 0;
    number_zutaten_maschine_mit = &number_zutaten_maschine_mit_;
    number_zutaten_maschine_ohne = &number_zutaten_maschine_ohne_;

    /******************************************************************************************************************
    *******************************************************************************************************************
    **                                         ************************************************************************
    **  - Initialisierungen für Zutaten-Liste  ************************************************************************
    **                                         ************************************************************************
    *******************************************************************************************************************
    *******************************************************************************************************************
    Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.       */

    // Buffer
    char buff_init_textfiles_zutat[21] = {'\0'};        // Buffer für Filename
    char buff2_init_textfiles_zutat[5] = {'\0'};        // Buffer für Integer to ASCI umwandlung

    /******************************************************************************************************************

        - Ab hier werden die Zutaten gesucht, welche sich auf der SD-Karte befinden. (Z0.txt bis Z100.txt)
        - Für jedes gefundene File wird ein dynamisch gelinkter Eintrag in einer Liste generiert.
        - Im Eintrag ist der Name des Files gespeichert, und ermöglicht einen späteren Aufruf.

    ******************************************************************************************************************/

    for (int8_t count = 1 ; count <= 30; count++)
    {
        // String mit Name des Textfiles erstellen (Z0.txt bis Z199.txt)
        strcpy((char *)buff_init_textfiles_zutat, (const char *)"Z");
        itoa(count, (char *)buff2_init_textfiles_zutat, 10);
        strcat((char *)buff_init_textfiles_zutat, (const char *)buff2_init_textfiles_zutat);
        strcat((char *)buff_init_textfiles_zutat, (const char *)".txt");

        // Prüfen ob File existiert
        if(readFile(VERIFY, (unsigned char *)buff_init_textfiles_zutat)==1)
        {
            // Nummer des Existierenden Files in der Liste ablegen (head_zutat = letzt hinzugefügtes Getränk)
            lese_textfile_in_zutat(count);

            if (aktuelle_zutat->kohlensaeure == 0)
            {
                insert_at_end(count, &number_zutaten_ohne, &head_zutat_file_ohne, &tail_zutat_file_ohne);
            }
            else
            {
                insert_at_end(count, &number_zutaten_mit, &head_zutat_file_mit, &tail_zutat_file_mit);
            }
        }
    }
    display_from_beg(number_zutaten_ohne, &head_zutat_file_ohne, &tail_zutat_file_ohne);
    display_from_beg(number_zutaten_mit, &head_zutat_file_mit, &tail_zutat_file_mit);

    /******************************************************************************************************************
    *******************************************************************************************************************
    **                                                                    *********************************************
    **  - Initialisierungen für die in der Maschine vorhandenen Zutaten.  *********************************************
    **                                                                    *********************************************
    *******************************************************************************************************************
    *******************************************************************************************************************
    Diese werden von der/auf die SD-Karte geladen, damit Sie nach einem Neustart wieder gleich sind wie davor.       */

    char delimiter[] = ",\r\n";                         // Trennungszeichen definieren              (strtok)
    char *ptr;                                          // Pointer für Abschnitte initialisieren   (strtok)

    char buff1[21] = {'\0'};                            // Buffer für Name der Zutat
    uint8_t buff2;                                      // Buffer für Status der Zutat
    uint8_t buff3;                                      // Buffer für Alkohol Ja/Nein der Zutat
    uint8_t buff4;                                      // Buffer für Kohlensäure Ja/Nein der Zutat

    char buff5[20] = {'\0'};                            // Buffer für Filename "M.txt"

    uint8_t position = 0;                               // Variable, welche die Position des Getränks hochzählt.

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

        - Ab hier wird das File "M.txt" zerlegt und die eingeschriebenen Getränke, sowie deren Status und
          Alkoholgehalt Ja/Nein in die Liste geschrieben.
        - Die Daten sind dann jederzeit verfügbar, der alloziierte Speicher reicht, um die Zutaten umzuschreiben
          während des Betriebs. (20 Zeichen maximum)
        - Damit die aktuelle Zutat auf das File1 zeigt, zeigt es auf den Tail der Liste (Erstes hinzugefügt).

    ******************************************************************************************************************/

    // Extrahiere erstes Maschinen-Zutat aus File "M.txt"
    ptr = strtok((char *)buffer, delimiter);                            // Abschnitt Name Zutat
    strcpy((char *)buff1,ptr);                                          // Kopiere Name in Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Status
    buff2 = atoi(ptr);                                                  // Schreibe ASCI-Status in Integer-Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Alkohol Ja/Nein
    buff3 = atoi(ptr);                                                  // Schreibe ASCI-JA//Nein in Integer-Buffer
    ptr = strtok(NULL, delimiter);                                      // Abschnitt Kohlensäure Ja/Nein
    buff4 = atoi(ptr);                                                  // Schreibe ASCI-JA//Nein in Integer-Buffer

    // Speicher alloziieren

    // Zutat in der Liste ablegen (head_zutat = letzt hinzugefügtes Getränk)
            insert_at_end_2((char *)buff1, buff2, buff3, buff4, position, abstand*position, &number_zutaten_maschine_ohne, &head_zutat_maschine_ohne, &tail_zutat_maschine_ohne);

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
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
        buff4 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer

        // Falls der Name des Getränkes >=1 ist, erstelle neue Zutat in Maschine
        if (strlen((const char *)buff1)>=1)
        {
            // Speicher alloziieren
            insert_at_end_2((char *)buff1, buff2, buff3, buff4, position, abstand*position, &number_zutaten_maschine_ohne, &head_zutat_maschine_ohne, &tail_zutat_maschine_ohne);

            // Position inkrementieren
            position++;
        }
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat
    }

    // Aktuelle Zutat auf Tail zeigen lassen (Erstes hinzugefügt)
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zutat_maschine_ohne;

    position = 0;

    ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat

    while(strcmp(ptr, ";")!=0)
    {
        strcpy((char *)buff1,ptr);                                      // Kopiere Name in Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        buff2 = atoi(ptr);                                              // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        buff3 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
        buff4 = atoi(ptr);                                              // Schreibe ASCI-JA//Nein in Integer-Buffer

        // Falls der Name des Getränkes >=1 ist, erstelle neue Zutat in Maschine
        if (strlen((const char *)buff1)>=1)
        {
            // Speicher alloziieren
            insert_at_end_2((char *)buff1, buff2, buff3, buff4, position, abstand*position, &number_zutaten_maschine_mit, &head_zutat_maschine_mit, &tail_zutat_maschine_mit);

            // Position inkrementieren
            position++;
        }

        ptr = strtok(NULL, delimiter);                                  // Abschnitt Name Zutat
    }
    aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zutat_maschine_mit;
    display_from_beg_2(number_zutaten_maschine_ohne, &head_zutat_maschine_ohne, &tail_zutat_maschine_ohne);
    display_from_beg_2(number_zutaten_maschine_mit, &head_zutat_maschine_mit, &tail_zutat_maschine_mit);
}

zutat_t *create_zutat()
{
    // Alloziiere Speicher für die Struct-Variabeln gemäss Struct zutat_t
    zutat_t *newZutat = calloc(1,sizeof(zutat_t));

    // Alloziiere Speicher für den Namen und setze den Struct-Pointer name darauf
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

zutat_list_node_t *create_new_list_node_zut_file( file_node_t * file_to_link)
{
    // Alloziiere Speicher für die Struct-Variabeln gemäss Struct file_node_t
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

    // Setze das vorhergehende und nachkommende File des einzufügenden Files
    file_to_insert->next = *head;
    file_to_insert->prev = NULL;

    // Falls keine head-Zutat besteht, ist die einzufügende Zutat die tail-Zutat
    if((*head) == NULL)
    {
        tail_zutat_list_node = file_to_insert;
    }

    // Besteht ein head-File, ist dessen zuvorkommends File das einzufügende File
    // und das zuvorkommende File des einzufügenden Files ist das tail-File
    else
    {
        (*head)->prev = file_to_insert;
    }

    // head-File ist jetzt das einzufügende File
    // Das nachkommende File des tail-Files ist jetzt das neue head-File
    file_to_insert->prev = tail_zutat_list_node;
    *head = file_to_insert;
    tail_zutat_list_node->next = *head;

    return file_to_insert;
}






zutatMaschine_list_node_t *create_new_list_node_zutMaschine_file( zutat_maschine_node_t * file_to_link)
{
    // Alloziiere Speicher für die Struct-Variabeln gemäss Struct zutatMaschine_list_node_t
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

    // Setze das vorhergehende und nachkommende File des einzufügenden Files
    file_to_insert->next = *head;
    file_to_insert->prev = NULL;

    // Falls keine head-Zutat besteht, ist die einzufügende Zutat die tail-Zutat
    if((*head) == NULL)
    {
        tail_zutatMaschine_list_node = file_to_insert;
    }

    // Besteht ein head-File, ist dessen zuvorkommends File das einzufügende File
    // und das zuvorkommende File des einzufügenden Files ist das tail-File
    else
    {
        (*head)->prev = file_to_insert;
        file_to_insert->prev = tail_zutatMaschine_list_node;
    }

    // head-File ist jetzt das einzufügende File
    // Das nachkommende File des tail-Files ist jetzt das neue head-File
    *head = file_to_insert;
    tail_zutatMaschine_list_node->next = *head;

    return file_to_insert;
}






