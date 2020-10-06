

#include "Cocktail_Statemachine.h"

void init_Getraenke_func()
{
    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}


void cocktail_check_command(int8_t page, int8_t button)
{
    /*
        Diese Funktion checkt, von welcher Seiter der Befehl kommt
    */
    switch (page)
    {
    /*0x01 = 0d01*/
    case STARTANZEIGE:
        check_startseite(button);
        break;

    /*0x02 = 0d02*/
    case ZUTATENANZEIGE:
        check_zutatenanzeige(button);
        break;

    /*0x03 = 0d03*/
    case LISTENANZEIGE:
        check_listenanzeige(button);
        break;

    /*0x04 = 0d04*/
    case ZUBABFRAGE:
        check_zubabfrage(button);
        break;

    /*0x05 = 0d05*/
    case ZUBBILDSCHIRM:
        check_zubbildschirm(button);
        break;

    /*0x07 = 0d07*/
    case MENUANZEIGE:
        check_menuanzeige(button);
        break;

    /*0x08 = 0d08*/
    case BEARBEITUNGSANZEIGE:
        check_bearbeitungsanzeige(button);
        break;

    /*0x09 0d09*/
    case CEINSTANZEIGE:
        check_ceinstanzeige(button);
        break;

    /*0x0A = 0d10*/
    case REINANZEIGE1:
        check_reinanzeige1(button);
        break;

    /*0x0B = 0d11*/
    case REINANZEIGE2:
        check_reinanzeige2(button);
        break;

    /*0x0C = 0d12*/
    case REINANZEIGE3:
        check_reinanzeige3(button);
        break;
    /*0x0D = 0d13*/
    case INFOANZEIGE:
        check_infoanzeige(button);
        break;

//      /*0x0E = 0d14*/
//  case ABBRUCHANZEIGE:
//      check_abbruchanzeige(button);
//  break;

    /*0x0F = 0d15*/
    case FEHLERANZEIGE:
        check_fehleranzeige(button);
        break;

    /*0x10 = 0d16*/
    case ERSTANZEIGE1:
        check_erstanzeige1(button);
        break;

    /*0x11 = 0d17*/
    case ERSTANZEIGE2:
        check_erstanzeige2(button);
        break;

    /*0x12 = 0d18*/
    case LOESCHABFRAGE:
        check_loeschanzeige(button);
        break;

    /*0x13 = 0d19*/
    case POSANZEIGE:
        check_posanzeige(button);
        break;

    /*0x14 = 0d20*/
    case FLUESSANZEIGE1:
        check_fluessanzeige1(button);
        break;

    /*0x15 = 0d21*/
    case FLUESSANZEIGE2:
        check_fluessanzeige2(button);
        break;

    /*0x16 = 0d22*/
    case FLUESSANZEIGE3:
        check_fluessanzeige3(button);
        break;

    /*0x17 = 0d23*/
    case RFIDANZEIGE1:
        check_RFIDAnzeige1(button);
        break;

    /*0x18 = 0d24*/
    case RFIDANZEIGE2:
        check_RFIDAnzeige2(button);
        break;

    /*0x19 = 0d25*/
    case RFIDFEHLER:
        check_RFIDFehler(button);
        break;

    /*0x1A = 0d26*/
    case ESP32_PAGE:
        check_ESP32(button);
        break;

    /*0x1B = 0d27*/
    case LED_PAGE:
        check_LED(button);
        break;

    /*0x1C = 0d28*/
    case FLUESSANZEIGE4:
        check_fluessanzeige4(button);
        break;
    }
}

void check_startseite(uint8_t button)
{
    switch (button)
    {

    case ZUTATEN:
        /*      0x02 = 0b02
                    - Wechsle auf Zutatenanzeige
                    - Setze Name des aktuellen Getränks
                    - Erstelle Zutatenliste des Getränks
        */
        nextion_change_page(ZUTATENANZEIGE);
        nextion_setText("cocktailname",aktuellesGetraenk->name);
        erstelle_Zutatenliste(aktuellesGetraenk);
        break;

    case LINKS:
        /*      0x03 = 0b03
                    - Wähle je nach Kriterium nächstes Getränk aus
                        - Wenn alle Getränke ausgewählt wurden, durch alle Files Switchen
                        - Wenn alkoholische Getränke ausgewählt wurden, alkoholfreie Files überspringen
                        - Wenn alkoholfreie Getränke ausgewählt wurden, alkoholische Files überspringen
                    - Schreibe File in aktuelles Getränk
                    - Setze Startanzeige
        */
        switch (Liste)
        {
        case ALLE:
//              0x00 = 0b00
            schiebe_file_next();
            break;

        case ALKOHOL:
//              0x01 = 0b01
            schiebe_file_next();
            while(aktuellesGetraenk->alkohol == 0)
            {
                schiebe_file_next();
            }
            break;

        case ALKOHOLFREI:
//              0x02 = 0b02
            schiebe_file_next();
            while(aktuellesGetraenk->alkohol == 1)
            {
                schiebe_file_next();
            }
            break;
        }
        setze_startanzeige(aktuellesGetraenk);
        break;

    case B33:
        /*      0x04 = 0b04
                    - Wechsle auf Zubereitungsabfrage (Menge)
                    - Schreibe File in aktuelles Getränk
        */
        nextion_change_page(ZUBABFRAGE);
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        break;

    case RECHTS:
        /*      0x05 = 0b05
                    - Wähle je nach Kriterium vorhergehendes Getränk aus
                        - Wenn alle Getränke ausgewählt wurden, durch alle Files Switchen
                        - Wenn alkoholische Getränke ausgewählt wurden, alkoholfreie Files überspringen
                        - Wenn alkoholfreie Getränke ausgewählt wurden, alkoholische Files überspringen
                    - Schreibe File in aktuelles Getränk
                    - Setze Startanzeige
        */
        switch (Liste)
        {
        case ALLE:
//              0x00 = 0b00
            schiebe_file_prev();
            break;

        case ALKOHOL:
//              0x01 = 0b01
            schiebe_file_prev();
            while(aktuellesGetraenk->alkohol == 0)
            {
                schiebe_file_prev();
            }
            break;
        case ALKOHOLFREI:
//              0x02 = 0b02
            schiebe_file_prev();
            while(aktuellesGetraenk->alkohol == 1)
            {
                schiebe_file_prev();
            }
            break;
        }
        setze_startanzeige(aktuellesGetraenk);
        break;

    case LISTE:
        /*      0x06 = 0b06
                    - Setze Listenanzeige
                    - Variable für Listenseite auf 0 setzen
                    - Erstelle ersten Listenabschnitt mit Cocktailnamen
        */

        bufferGetraenk_file = aktuellesGetraenk_file;

        aktuellesGetraenk_file = tail_getraenk_file;
        getraenk_file_3_t * tmp;
        head_list_node_file = NULL;
        tail_list_node_file = NULL;
        tmp = create_new_list_node_file(aktuellesGetraenk_file);
        head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);
        actual_list_node_file = head_list_node_file;
        lese_textfile_in_getraenk(actual_list_node_file->getraenk_x->file);

        nextion_change_page(LISTENANZEIGE);

        buffer2Getraenk_file = erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");

        // Zweiten Listenabschnitt erstellen
        tmp = create_new_list_node_file(buffer2Getraenk_file);
        head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);

        break;

    case MENU:
        /*      0x07 = 0b07
                    - Setze Menuanzeige
        */
        nextion_change_page(MENUANZEIGE);
        break;

    case ALKOHOLJANEIN:
        /*      0x08 = 0b08
                    - Lese erstes Getränk ein
                    - Wechsle Modus: Alle Getränke/Alkoholisch/Alkoholfrei
                    - Schreibe erstes File gemäss Modus in aktuelles Getränk
                    - Setze Startanzeige
        */
        aktuellesGetraenk_file = tail_getraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        switch(Liste)
        {
        case ALLE:
            Liste = ALKOHOL;                            // Modus-Wechsel
            while (aktuellesGetraenk->alkohol == 0)     // File Suchen mit Alkohol
            {
                schiebe_file_prev();
            }
            break;

        case ALKOHOL:
            Liste = ALKOHOLFREI;                        // Modus-Wechsel
            while (aktuellesGetraenk->alkohol == 1)     // File suchen ohne Alkohol
            {
                schiebe_file_prev();
            }
            break;

        case ALKOHOLFREI:
            Liste = ALLE;                               // Modus-Wechsel
            break;
        }
        setze_startanzeige(aktuellesGetraenk);          // Startanzeige setzen
        break;

    case LOESCHEN:
        /*      0x09 = 0b09
                    - Setze Löschabfrage
        */
        nextion_change_page(LOESCHABFRAGE);
        break;
    }
}

void check_zutatenanzeige(uint8_t button)
{
    switch(button)
    {
    case OKZUTATEN:
        /*      0x01 = 0b01
                    - Setze Startanzeige
        */
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case ZUTATENLISTE:
        /*      0x02 = 0b02
                    - Setze Startanzeige
        */
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_listenanzeige(uint8_t button)
{
    switch (button)
    {
    /*      0x01 bis 0x08 = 0b01 bis 0b08
                - Wähle x-ten Cocktail des aktuellen Listenabschnitts
                - Setze Startanzeige
    */
    case COCKTAIL1:
        choose_aktuellesGetraenk(0);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case COCKTAIL2:
        choose_aktuellesGetraenk(1);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case COCKTAIL3:
        choose_aktuellesGetraenk(2);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case COCKTAIL4:
        choose_aktuellesGetraenk(3);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case COCKTAIL5:
        choose_aktuellesGetraenk(4);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case COCKTAIL6:
        choose_aktuellesGetraenk(5);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case RAUFLIST1:
        /*      0x09 = 0b09
                    - Untere Blockierung aufheben
                    - Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
                    - Schreibe Cocktailnamen in die Liste
        */

        if (!block_list_hoch)
        {
            nextion_change_page(LISTENANZEIGE);
            block_list_runter = 0;
            actual_list_node_file = actual_list_node_file->next;
            erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");
        }
        break;

    case RUNTERLIST1:
        /*      0x0A = 0b10
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_runter)
        {
            block_list_hoch = 0;
            nextion_change_page(LISTENANZEIGE);
            actual_list_node_file = actual_list_node_file->prev;
            buffer2Getraenk_file = erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");
            if (actual_list_node_file->getraenk_x->file == head_list_node_file->getraenk_x->file)
            {
                getraenk_file_3_t * tmp = create_new_list_node_file(buffer2Getraenk_file);
                head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);
            }
        }
        break;

    case ZURUECK9:
        /*      0x0B = 0b11
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        block_list_hoch = 0;
        block_list_runter = 0;

        actual_list_node_file = tail_list_node_file;
        getraenk_file_3_t * tmp = NULL;
        do
        {
            tmp = actual_list_node_file;
            free(actual_list_node_file);
            actual_list_node_file = tmp->prev;
        } while (actual_list_node_file!=tail_list_node_file);


        aktuellesGetraenk_file = bufferGetraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;
    }

}

void check_zubabfrage(uint8_t button)
{
    switch (button)
    {
    case KLEIN:
        /*      0x01 = 0b01
                    - Getränk mit 3dl zubereiten
        */
        zubereitung_getraenk((uint32_t)3);
        break;

    case GROSS:
        /*      0x02 = 0b02
                    - Getränk mit 5dl zubereiten
        */
        zubereitung_getraenk((uint32_t)5);
        break;

    case ABBRUCHZUBAB:
        /*      0x03 = 0b03
                    - Setze Startanzeige
        */
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_zubbildschirm(uint8_t button)
{
    switch (button)
    {
    /*      0x01 = 0b01
                - Setze stop-Flag = 1 im Zubereitungsprozess
    */
    case ABBRUCHZUB:
        stop = 1;
        break;
    }
}

void check_menuanzeige(uint8_t button)
{
    switch (button)
    {
    case COCKTAILBEARBEITEN:
        /*      0x01 = 0b01
                    - Setze Bearbeitungsanzige
                    - Setze Listenabschnitt auf 1. Abschnitt
                    - Erstelle ersten Listenabschnitt mit Cocktailnamen
        */
        bufferGetraenk_file = aktuellesGetraenk_file;

        aktuellesGetraenk_file = tail_getraenk_file;
        getraenk_file_3_t * tmp;
        head_list_node_file = NULL;
        tail_list_node_file = NULL;
        tmp = create_new_list_node_file(aktuellesGetraenk_file);
        head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);
        actual_list_node_file = head_list_node_file;

        nextion_change_page(BEARBEITUNGSANZEIGE);

        buffer2Getraenk_file = erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");

        // Zweiten Listenabschnitt erstellen
        tmp = create_new_list_node_file(buffer2Getraenk_file);
        head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);
        break;

    case COCKTAILERSTELLEN:
        /*      0x02 = 0b02
                    - Setze Erstellungsanzeige (Namenseingabe neuer Cocktail)
                    - Setze Grossschreibe-Flag = 1 für erster Buchstabe gross
                    - Setze counter für Buchstabenindex des neuen Cocktail-Namens = 0
                    - Initialisiere neuen Cocktailname auf '\0'
        */

        nextion_change_page(ERSTANZEIGE1);
// Aneinanderreihen zweier Listen

// Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
        zutatMaschine_t * tmp_zut_Maschine_tail;
//     zutatMaschine_t * tmp_zut_Maschine_head;
        zutatMaschine_t * tmp_zut_Maschine_actual;

// Speichern der Momentanen Pointer.
        zutatMaschine_t * tmp_ohne_KS_head = head_zut_in_Maschine_ohne_KS->prev;
        zutatMaschine_t * tmp_mit_KS_head = head_zut_ausser_Maschine_mit_KS->prev;
        zutatMaschine_t * tmp_ohne_KS_tail = tail_zut_in_Maschine_ohne_KS->next;
        zutatMaschine_t * tmp_mit_KS_tail = tail_zut_ausser_Maschine_mit_KS->next;

// Anfang und Ende der gesamten Liste
        tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
//     tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

// Äussere Verbindungen
        tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
        head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

// Innere Verbindungen
        tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
        head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

        tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
        do
        {
            tmp_zut_Maschine_actual->menge = 0;
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
        } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

        head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
        head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
        tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
        tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;

        char buff10[20] = {'\0'};
        strcpy((char *)buff10, "Fs");
        strcat((char *)buff10, (const char *)".pco=2016");
        Uart_Transmit_IT_Display((char *)buff10);
        endConversation();

        Grossschreib = 1;
        counter = 0;

        char len = strlen(buff_name);
        for (int i = 0 ; i < len ; i ++)
        {
            buff_name[i] = '\0';
        }
        break;

    case MASCHINEREINIGEN:
        /*      0x03 = 0b03
                    - Setze Reinigungsanzeige1
        */
        nextion_change_page(REINANZEIGE1);
        break;

    case MASCHINENINFO:
        /*      0x04 = 0b04
                    - Setze Infoanzeige
        */
        nextion_change_page(INFOANZEIGE);
        break;

    case ZURUECK1:
        /*      0x05 = 0b05
                    - Setze Startabzeige
        */
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case FLUESSPOS:
        /*      0x06 = 0b06
                    - Setze Posanzeige
                    - Färbe die Nummern der Positionen gemäss Status
        */
        nextion_change_page(POSANZEIGE);
        setze_Posanzeige_Rot_Gruen();
        break;

    case RFID:
        /*      0x07 = 0b07
                    - Setze RFIDANZEIGE1
        */
        nextion_change_page(RFIDANZEIGE1);
        for(int count = 0 ; count < 6 ; count++)
        {
            char string[10] = {'\0'};
            char buff[5] = {'\0'};
            strcpy((char *)string, (const char *) "rfid");
            itoa((count + 1), (char *)buff, 10);
            strcat((char *)string, buff);
            itoa((count + i_Liste + 1), (char *)buff, 10);
            nextion_setText((char *)string, (char *)buff);
        }
        break;

    case LED_BUTTON:
        nextion_change_page(LED_PAGE-1);
        break;
    }
}

void check_bearbeitungsanzeige(uint8_t button)
{
    switch (button)
    {
    case BEARBCOCKTAIL1:
        /*      0x01 = 0b01
                    - Bearbeite Cocktail an Stelle 0 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(0);
        break;

    case BEARBCOCKTAIL2:
        /*      0x02 = 0b02
                    - Bearbeite Cocktail an Stelle 1 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(1);
        break;

    case BEARBCOCKTAIL3:
        /*      0x03 = 0b03
                    - Bearbeite Cocktail an Stelle 2 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(2);
        break;

    case BEARBCOCKTAIL4:
        /*      0x04 = 0b04
                    - Bearbeite Cocktail an Stelle 3 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(3);
        break;

    case BEARBCOCKTAIL5:
        /*      0x05 = 0b05
                    - Bearbeite Cocktail an Stelle 4 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(4);
        break;

    case BEARBCOCKTAIL6:
        /*      0x06 = 0b06
                    - Bearbeite Cocktail an Stelle 5 im aktuellen Listenabschnitt
        */
        bearbeite_Cocktail(5);
        break;

    case RAUFLIST2:
        /*      0x09 = 0b09
                    - Untere Blockierung aufheben
                    - Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
                    - Schreibe Cocktailnamen in die Liste
        */

        if (!block_list_hoch)
        {
            nextion_change_page(BEARBEITUNGSANZEIGE);
            block_list_runter = 0;
            actual_list_node_file = actual_list_node_file->next;
            erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");
        }
        break;

    case RUNTERLIST2:
        /*      0x0A = 0b10
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_runter)
        {
            block_list_hoch = 0;
            nextion_change_page(BEARBEITUNGSANZEIGE);
            actual_list_node_file = actual_list_node_file->prev;
            buffer2Getraenk_file = erstelle_Liste_name(actual_list_node_file->getraenk_x, "cocktail");
            if (actual_list_node_file->getraenk_x->file == head_list_node_file->getraenk_x->file)
            {
                getraenk_file_3_t * tmp = create_new_list_node_file(buffer2Getraenk_file);
                head_list_node_file = insert_list_node_at_head(&head_list_node_file, tmp);
            }
        }
        break;

    case ZURUECK10:
        /*      0x0B = 0b11
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        aktuellesGetraenk_file  = bufferGetraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        block_list_hoch = 0;
        block_list_runter = 0;
        i_Liste = 0;
        nextion_change_page(MENUANZEIGE);
        break;

    case STANDARDEINST:

        setze_standardeinstellungen();

        break;
    }
}

void check_ceinstanzeige(uint8_t button)
{
// Aneinanderreihen zweier Listen

// Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
    zutatMaschine_t * tmp_zut_Maschine_tail;
// zutatMaschine_t * tmp_zut_Maschine_head;
    zutatMaschine_t * tmp_zut_Maschine_actual;

// Speichern der Momentanen Pointer.
    zutatMaschine_t * tmp_ohne_KS_head = head_zut_in_Maschine_ohne_KS->prev;
    zutatMaschine_t * tmp_mit_KS_head = head_zut_ausser_Maschine_mit_KS->prev;
    zutatMaschine_t * tmp_ohne_KS_tail = tail_zut_in_Maschine_ohne_KS->next;
    zutatMaschine_t * tmp_mit_KS_tail = tail_zut_ausser_Maschine_mit_KS->next;

    uint8_t val = 0;

    switch(button)
    {
    case RAUFLIST3:
        /*      0x07 = 0b07c
                    - Untere Blockierung aufheben
                    - Gehe Liste um 6 Getränke hoch, falls nicht schon am oberen Ende
                    - Schreibe Cocktailnamen in die Liste*/
        if (!block_list_hoch)
        {
            block_list_runter = 0;
            aktuelle_zutatMaschine_list_node = aktuelle_zutatMaschine_list_node->next;
            erstelle_Liste_zutat(aktuelle_zutatMaschine_list_node->zutat_xy, "zutat");
        }
        break;

    case RUNTERLIST3:
        /*      0x08 = 0b08
                    - Obere Blockierung aufheben
                    - Gehe Liste um 6 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_runter)
        {

            block_list_hoch = 0;
            aktuelle_zutatMaschine_list_node = aktuelle_zutatMaschine_list_node->prev;
            buffer_zut_in_Maschine_ohne_KS = erstelle_Liste_zutat(aktuelle_zutatMaschine_list_node->zutat_xy, "zutat");
            if (aktuelle_zutatMaschine_list_node==head_zutatMaschine_list_node)
            {
                zutatMaschine_list_node_t * tmp = create_new_list_node_zutMaschine_file(buffer_zut_in_Maschine_ohne_KS);
                head_zutatMaschine_list_node = insert_zutatMaschine_list_node_at_head(&head_zutatMaschine_list_node, tmp);
            }
        }
        break;

    case STANDARDEINST:
        /*      0x03 = 0b03
                    - ***************************************************************************************************************************************************************************************************3
        */
        block_list_hoch = 0;
        block_list_runter = 0;
        nextion_change_page(STARTANZEIGE);
        break;

    case SPEICHERN1:
        /*      0x04 = 0b04
                    - Listenblockierungen aufheben und Listenabschnitt auf 0 setzen
                    - Bestehendes Getränke-File löschen
                    - Aktuelles Getränke-File erstellen und speichern
                    - Startanzeige setzen
        */

// Anfang und Ende der gesamten Liste
        tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
// tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

// Äussere Verbindungen
        tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
        head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

// Innere Verbindungen
        tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
        head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

        tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
        do
        {
            val += tmp_zut_Maschine_actual->menge;
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
        } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

        if (val == 100)
        {
            block_list_hoch = 0;
            block_list_runter = 0;
            nextion_change_page(RFIDFEHLER);
            nextion_setText("fehlertxt", "Wird gespeichert...");
            loesche_FIle(aktuellesGetraenk_file->file);
            erstelle_File(aktuellesGetraenk_file->file, aktuellesGetraenk->name, aktuellesGetraenk->alkohol, aktuellesGetraenk->kohlensaeure);
            nextion_change_page(STARTANZEIGE);
            setze_startanzeige(aktuellesGetraenk);
        }
        else
        {
            nextion_setText("t0", "Noch nicht 100% ausgewählt.");
        }
        head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
        head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
        tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
        tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
        break;

    case SLIDER01:
        /*      0x05 = 0b05
                    - Auf drücken oder sliden aktueller Wert aus Slider 1 (Pos 0) lesen und in Menge des Getränkes schreiben
        */
        schreibe_Menge_in_Getraenk(0);
        break;

    case SLIDER02:
        /*      0x06 = 0b06
                    - Auf drücken oder sliden aktueller Wert aus Slider 2 (Pos 1) lesen und in Menge des Getränkes schreiben
        */
        schreibe_Menge_in_Getraenk(1);
        break;

    case SLIDER03:
        /*      0x07 = 0b07
                    - Auf drücken oder sliden aktueller Wert aus Slider 3 (Pos 2) lesen und in Menge des Getränkes schreiben
        */
        schreibe_Menge_in_Getraenk(2);
        break;

    case SLIDER04:
        /*      0x08 = 0b08
                    - Auf drücken oder sliden aktueller Wert aus Slider 4 (Pos 3) lesen und in Menge des Getränkes schreiben
        */
        schreibe_Menge_in_Getraenk(3);
        break;

    case ABBRECHEN6:
        block_list_hoch = 0;
        block_list_runter = 0;
        nextion_change_page(STARTANZEIGE);
        aktuellesGetraenk_file =bufferGetraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_reinanzeige1(uint8_t button)
{
    switch(button) {

    case ABBRECHEN1:
        /*      0x01 = 0b01
                    - Menuanzeige setzen
        */
        nextion_change_page(MENUANZEIGE);
        break;

    case WEITER1:
        /*      0x02 = 0b02
                    - Reinigungsanzeige 2 setzen
        */
        nextion_change_page(REINANZEIGE2);
        break;
    }
}

void check_reinanzeige2(uint8_t button)
{
    switch(button)
    {
    case ABBRECHEN2:
        /*      0x01 = 0b01c
                    - Menuanzeige setzen
        */
        nextion_change_page(MENUANZEIGE);
        break;

    case WEITER2:
        /*      0x02 = 0b02
                    - Reinigungsanzeige 3 setzen
                    - Durch alle Pumpen durchschalten und jeweils plus/minus 2 Sekunden durchspülen lassen
                    - Während des Durchspül-Prozesses die Kommunikation prüfen auf einkommende Befehle
                    - Erstes Getränk setzen und Startanzeige anzeigen
        */
        nextion_change_page(REINANZEIGE3);
        for (int i = 0 ; i < 12 ; i++)
        {
            if (stop == 0)
            {
                schalte_pumpe_ein(i);
                uint16_t cnt = 0;
                while ((cnt < 2000))
                {
                    if(check_Communication_Input_UART_1())
                    {
                        proceed_Communication_INPUT_UART_1();
                    }
                    cnt++;
                    _delay_ms(1);
                }
            }
            schalte_pumpe_aus(i);
        }
        stop = 0;
        nextion_change_page(STARTANZEIGE);
        aktuellesGetraenk_file = tail_getraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_reinanzeige3(uint8_t button)
{
    switch(button)
    {
    case ABBRECHEN3:
        /*      0x01 = 0b01
                    - Menuanzeige setzen
                    - Stop-Flag für Flüssigkeits-Abbruch auf 1
        */
        nextion_change_page(MENUANZEIGE);
        stop = 1;
        break;
    }
}

void check_infoanzeige(uint8_t button)
{
    switch(button)
    {
    case ZURUECK2:
        /*      0x01 = 0b01
                    - Menuanzeige setzen
        */
        nextion_change_page(MENUANZEIGE);
        break;
    }
}

void check_fehleranzeige(uint8_t button)
{

}

void check_erstanzeige1(uint8_t button)
{
    // Initialisierung für Gross-/Kleinschreib-Wechsel
    char wechsel = 0;
    char buff10[50] = {'0'};
    uint8_t vorhanden = 0;

    switch (button)
    {
    case A:
        /*      0x01 = 0b01
                    - Buchstabe A gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'A';
        }
        else
        {
            buff_name[counter] = 'a';
        }
        counter++;
        break;

    case B:
        /*      0x02 = 0b02
                    - Buchstabe B gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'B';
        }
        else
        {
            buff_name[counter] = 'b';
        }
        counter++;
        break;

    case C:
        /*      0x03 = 0b03
                    - Buchstabe C gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'C';
        }
        else
        {
            buff_name[counter] = 'c';
        }
        counter++;
        break;

    case D:
        /*      0x04 = 0b04
                    - Buchstabe D gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'D';
        }
        else
        {
            buff_name[counter] = 'd';
        }
        counter++;
        break;

    case E:
        /*      0x05 = 0b05
                    - Buchstabe E gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'E';
        }
        else
        {
            buff_name[counter] = 'e';
        }
        counter++;
        break;

    case F:
        /*      0x06 = 0b06
                    - Buchstabe F gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'F';
        }
        else
        {
            buff_name[counter] = 'f';
        }
        counter++;
        break;

    case G:
        /*      0x07 = 0b07
                    - Buchstabe G gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'G';
        }
        else
        {
            buff_name[counter] = 'g';
        }
        counter++;
        break;

    case H:
        /*      0x08 = 0b08
                    - Buchstabe H gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'H';
        }
        else
        {
            buff_name[counter] = 'h';
        }
        counter++;
        break;

    case I:
        /*      0x09 = 0b09
                    - Buchstabe I gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'I';
        }
        else
        {
            buff_name[counter] = 'i';
        }
        counter++;
        break;

    case J:
        /*      0x0A = 0b10
                    - Buchstabe J gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'J';
        }
        else
        {
            buff_name[counter] = 'j';
        }
        counter++;
        break;

    case K:
        /*      0x0B = 0b11
                    - Buchstabe K gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'K';
        }
        else
        {
            buff_name[counter] = 'k';
        }
        counter++;
        break;

    case L:
        /*      0x0C = 0b12
                    - Buchstabe L gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'L';
        }
        else
        {
            buff_name[counter] = 'l';
        }
        counter++;
        break;

    case M:
        /*      0x0D = 0b13
                    - Buchstabe M gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'M';
        }
        else
        {
            buff_name[counter] = 'm';
        }
        counter++;
        break;

    case N:
        /*      0x0E = 0b14
                    - Buchstabe N gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'N';
        }
        else
        {
            buff_name[counter] = 'n';
        }
        counter++;
        break;

    case O:
        /*      0x0F = 0b15
                    - Buchstabe O gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'O';
        }
        else
        {
            buff_name[counter] = 'o';
        }
        counter++;
        break;

    case P:
        /*      0x10 = 0b16
                    - Buchstabe P gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'P';
        }
        else
        {
            buff_name[counter] = 'p';
        }
        counter++;
        break;

    case Q:
        /*      0x11 = 0b17
                    - Buchstabe Q gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'Q';
        }
        else
        {
            buff_name[counter] = 'q';
        }
        counter++;
        break;

    case R:
        /*      0x12 = 0b18
                    - Buchstabe R gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'R';
        }
        else
        {
            buff_name[counter] = 'r';
        }
        counter++;
        break;

    case S:
        /*      0x13 = 0b19
                    - Buchstabe S gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'S';
        }
        else
        {
            buff_name[counter] = 's';
        }
        counter++;
        break;

    case T:
        /*      0x14 = 0b20
                    - Buchstabe T gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'T';
        }
        else
        {
            buff_name[counter] = 't';
        }
        counter++;
        break;

    case U:
        /*      0x15 = 0b21
                    - Buchstabe U gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'U';
        }
        else
        {
            buff_name[counter] = 'u';
        }
        counter++;
        break;

    case V:
        /*      0x16 = 0b22
                    - Buchstabe V gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'V';
        }
        else
        {
            buff_name[counter] = 'v';
        }
        counter++;
        break;

    case W:
        /*      0x17 = 0b23
                    - Buchstabe W gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'W';
        }
        else
        {
            buff_name[counter] = 'w';
        }
        counter++;
        break;

    case X:
        /*      0x18 = 0b24
                    - Buchstabe X gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'X';
        }
        else
        {
            buff_name[counter] = 'x';
        }
        counter++;
        break;

    case Y:
        /*      0x19 = 0b25
                    - Buchstabe Y gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'Y';
        }
        else
        {
            buff_name[counter] = 'y';
        }
        counter++;
        break;

    case Z:
        /*      0x1A = 0b26
                    - Buchstabe Z gross/klein in buff_name[counter] schreiben
                    - Counter inkrementieren für nächste Buchstabenposition des Namens
        */
        if (Grossschreib == 1)
        {
            buff_name[counter] = 'Z';
        }
        else
        {
            buff_name[counter] = 'z';
        }
        counter++;
        break;

    case Fs:
        /*      0x1B = 0b27
                    - Gross-/Kleinschreibung am Ende der Routine wechseln
        */
        wechsel = 1;
        break;

    case DEL:
        /*      0x1C = 0b28
                    - Counter vorverschieben
                    - String-Terminator setzen
        */
        counter--;
        buff_name[counter] = '\0';
        break;

    case ABBRECHEN4:
        /*      0x1D = 0b29
                    - Erstes File aus der Liste holen und in aktuellesGetraenk speichern
                    - Buffer für neuen Cocktail-Name rücksetzen
                    - Startanzeige setzen
        */
        aktuellesGetraenk_file  = bufferGetraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        counter = 0;
        for (int i = 0 ; i <20 ; i ++)
        {
            buff_name[i] = '\0';
        }
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case LEERZEICHEN:
        /*      0x1E = 0b30
                    - Leerzeichen in buff_name[counter] schreiben
        */
        buff_name[counter]= ' ';
        counter++;
        break;

    case OK:
        /*      0x1F = 0b31
                    - Erstanzeige2 setzen
                    - Mengen des neuen Getränks auf 0 setzen
                    - Counter für Buchstaben auf 0 setzen
                    - Listenabschnitt auf den Ersten setzen
                    - Zutaten in Liste schreiben
        */

        if (strlen(buff_name) == 0)
        {
            nextion_setText("nameeingtxt", "Bitte mindestens ein Zeichen eingeben.");
        }
        else
        {
            // Aneinanderreihen zweier Listen
            nextion_setText("nameeingtxt", "Überprüfe, ob Getränk exisiert.");

            // Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
            zutat_file_t * tmp_zut_file_tail;
            // zutatMaschine_t * tmp_zut_Maschine_head;
            zutat_file_t * tmp_zut_file_actual;

            // Speichern der Momentanen Pointer.
            zutat_file_t * tmp_ohne_KS_head = head_Zutat_file_in_Maschine_ohne_KS->prev;
            zutat_file_t * tmp_mit_KS_head = head_Zutat_file_ausser_Maschine_mit_KS->prev;
            zutat_file_t * tmp_ohne_KS_tail = tail_Zutat_file_in_Maschine_ohne_KS->next;
            zutat_file_t * tmp_mit_KS_tail = tail_Zutat_file_ausser_Maschine_mit_KS->next;

            // Anfang und Ende der gesamten Liste
            tmp_zut_file_tail = tail_Zutat_file_in_Maschine_ohne_KS;
            // tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

            // Äussere Verbindungen
            tail_Zutat_file_in_Maschine_ohne_KS->next = head_Zutat_file_ausser_Maschine_mit_KS;
            head_Zutat_file_ausser_Maschine_mit_KS->prev = tail_Zutat_file_in_Maschine_ohne_KS;

            // Innere Verbindungen
            tail_Zutat_file_ausser_Maschine_mit_KS->next = head_Zutat_file_in_Maschine_ohne_KS;
            head_Zutat_file_in_Maschine_ohne_KS->prev = tail_Zutat_file_ausser_Maschine_mit_KS;

            tmp_zut_file_actual = tmp_zut_file_tail;
            do
            {
                lese_textfile_in_zutat(tmp_zut_file_actual->file);
                if (strcmp(aktuelle_zutat->name, (char *)buff_name)==0)
                {
                    vorhanden = 1;
                    nextion_setText("neuefluesstxt", "Name schon vorhanden.");

                }
                tmp_zut_file_actual = tmp_zut_file_actual->prev;
            } while (tmp_zut_file_actual != tmp_zut_file_tail);

            head_Zutat_file_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
            head_Zutat_file_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
            tail_Zutat_file_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
            tail_Zutat_file_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;

        }

        if (vorhanden == 0)
        {
            bufferGetraenk_file = aktuellesGetraenk_file;

            // Aneinanderreihen zweier Listen

            // Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
            zutatMaschine_t * tmp_zut_Maschine_tail;
            //     zutatMaschine_t * tmp_zut_Maschine_head;
            zutatMaschine_t * tmp_zut_Maschine_actual;

            // Speichern der Momentanen Pointer.
            zutatMaschine_t * tmp_ohne_KS_head = head_zut_in_Maschine_ohne_KS->prev;
            zutatMaschine_t * tmp_mit_KS_head = head_zut_ausser_Maschine_mit_KS->prev;
            zutatMaschine_t * tmp_ohne_KS_tail = tail_zut_in_Maschine_ohne_KS->next;
            zutatMaschine_t * tmp_mit_KS_tail = tail_zut_ausser_Maschine_mit_KS->next;

            // Anfang und Ende der gesamten Liste
            tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
            //     tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

            // Äussere Verbindungen
            tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
            head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

            // Innere Verbindungen
            tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
            head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

            tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
            do
            {
                tmp_zut_Maschine_actual->menge = 0;
                tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
            } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

            head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
            tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
            tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
            head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;

            // Neue Liste beginnt == Blockierung aufheben
            block_list_hoch = 0;
            block_list_runter = 0;

            zutatMaschine_list_node_t * tmp_node;
            zutatMaschine_t * tmp_file;

            // Die Zutaten werden ab Beginn gesucht.
            tmp_file = tail_zut_in_Maschine_ohne_KS;

            // Die Listen-Pointer werden mit 0 initialisiert
            head_zutatMaschine_list_node = NULL;
            tail_zutatMaschine_list_node = NULL;

            // Erstelle eine neue Liste, deren Elemente einen Pointer auf die erste Zutat ohne Kohlensäure besitzt. Erste Zutat = Erster Eintrag des jeweiligen Listenabschnitts.
            tmp_node = create_new_list_node_zutMaschine_file(tmp_file);
            head_zutatMaschine_list_node = insert_zutatMaschine_list_node_at_head(&head_zutatMaschine_list_node, tmp_node);

            // Initialisiere den Pointer auf den aktuellen ersten Eintrag der Liste (welche den Pointer auf die erste Zutat ohne Kohlensäure beinhaltet)
            aktuelle_zutatMaschine_list_node = head_zutatMaschine_list_node;

            // Screibe die erste Seite der Liste. Return value = Erster Eintrag der nächsten Seite. (Sind keine weiteren Einträge vorhanden, wird der letzte Eintrag zurückgegeben. ==> head_Zutat_file_in_Maschine_ohne_KS)
            nextion_change_page(ERSTANZEIGE2);
            buffer_zut_in_Maschine_ohne_KS = erstelle_Liste_zutat(tmp_file, "zutat");

            // Erweitere die neue Liste, deren Elemente einen Pointer auf die erste Zutat ohne Kohlensäure besitzt, um ein Element.
            tmp_node = create_new_list_node_zutMaschine_file(buffer_zut_in_Maschine_ohne_KS);
            head_zutatMaschine_list_node = insert_zutatMaschine_list_node_at_head(&head_zutatMaschine_list_node, tmp_node);
        }
        break;
    }

    /*      Immer ausführen
                - Falls goss/klein-Wechsel ansteht, Gross/Klein-Variable ändern
                - Gesamter bisheriger name (buff_name) anzeigen
                - Enthält der Name 20 Buchstaben, bleibt der counter, der letzte Buchstabe wird immer überschrieben vom nächsten
    */
    if (wechsel == 1)
    {

        if (Grossschreib == 1)
        {
            Grossschreib = 0;
            strcpy((char *)buff10, "Fs");
            strcat((char *)buff10, (const char *)".pco=0");
            Uart_Transmit_IT_Display((char *)buff10);
            endConversation();
        }
        else
        {
            Grossschreib = 1;
            strcpy((char *)buff10, "Fs");
            strcat((char *)buff10, (const char *)".pco=2016");
            Uart_Transmit_IT_Display((char *)buff10);
            endConversation();
        }
    }

    nextion_setText("neuername",(char *)buff_name);

    if (counter >= 19)
    {
        counter = 19;
    }
}

void check_erstanzeige2(uint8_t button)
{
    /*
        Die hier vorkommenden Einstellungsmöglichkeiten dieser Seite besitzen
        gemäss Nextion-Editor dieselben Slider/Textfelder etc wie auf der
        Seite Ceinstanzeige. Bis auf den Speichern-Button haben alle die selbe
        Funktion. Deswegen werden auch die selben ID's gesendet, wie auf der
        Ceinstanzeigen-seite und somit auch diese schon geschriebenen
        Funktionen. Der Speichern-Button wird im folgenden aufgeführt.
    */

    uint8_t val = 0;
// Aneinanderreihen zweier Listen

// Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
    zutatMaschine_t * tmp_zut_Maschine_tail;
//     zutatMaschine_t * tmp_zut_Maschine_head;
    zutatMaschine_t * tmp_zut_Maschine_actual;

// Speichern der Momentanen Pointer.
    zutatMaschine_t * tmp_ohne_KS_head = head_zut_in_Maschine_ohne_KS->prev;
    zutatMaschine_t * tmp_mit_KS_head = head_zut_ausser_Maschine_mit_KS->prev;
    zutatMaschine_t * tmp_ohne_KS_tail = tail_zut_in_Maschine_ohne_KS->next;
    zutatMaschine_t * tmp_mit_KS_tail = tail_zut_ausser_Maschine_mit_KS->next;


    switch (button)
    {
    case ABBRECHEN5:
        /*      0x01 = 0b01
                    - Startanzeige setzen
                    - Listenabschnitt auf 0 setzen
        */
        aktuellesGetraenk_file  = bufferGetraenk_file;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        asm("nop");
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        i_Liste = 0;
        break;

    case SPEICHERN2:
        /*      0x02 = 0b02
                    - buff_name in aktuellesGetraenk kopieren (vorherige Seite)
                    - (Mengen sind schon in aktuellemGetraenk (vorherige Setie))
                    - Bild aktuellesGetranenk für User-Cocktail default auf 24
                    - Falls eine der Zutaten alkoholhaltig ist, ist alkohol = 1
                    - Nummer des nächsten nicht existierenden Files finden
                    - AktuellesGetraenk in File abspeichern und auf SD ablegen
                    - Auf Startanzeige wechseln
                    - counter für buff_name auf 0 setzen
                    - i_Liste für Listenabschnitt auf 0 setzen
                    - buff_name auf '\0' initialisieren für nächstes Getränk
        */
// Anfang und Ende der gesamten Liste
        tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
// tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

// Äussere Verbindungen
        tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
        head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

// Innere Verbindungen
        tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
        head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

        tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
        do
        {
            val += tmp_zut_Maschine_actual->menge;
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
        } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);


        if (val == 100)
        {

            nextion_change_page(RFIDFEHLER);
            nextion_setText("fehlertxt", "Wird gespeichert...");
            strcpy(aktuellesGetraenk->name, (const char *)buff_name);
            aktuellesGetraenk->picture = 32;

            uint8_t alkohol = 0;
            uint8_t kohlensaeure = 0;

            tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
            do
            {
                if (tmp_zut_Maschine_actual->menge > 0)
                {
                    if (tmp_zut_Maschine_actual->alkohol == 1)
                    {
                        alkohol = 1;
                    }

                    if (tmp_zut_Maschine_actual->kohlensaeure == 1)
                    {
                        kohlensaeure = 1;
                    }
                }
                tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
            } while (tmp_zut_Maschine_actual!= tmp_zut_Maschine_tail);
            aktuellesGetraenk->alkohol = alkohol;

            // Suche von 1 bis 100 durch die Files
            for (int8_t count = 1 ; count < 100; count++) {

                // Text erstellen, um File-Nr. zu suchen.
                char buff[15] = {'\0'};
                itoa(count, (char *)buff,10);
                strcat((char *)buff, (const char *)".txt");

                // Erstes nicht existierendes File suchen
                if(readFile(VERIFY, (unsigned char *)buff)!=1)
                {
                    // File speichern
                    erstelle_File(count, buff_name, alkohol, kohlensaeure);
                    getraenk_file_t * tmp2;
                    tmp2 = create_new_getraenk_file(count);
                    head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
                    getraenk_file_t * tmp3;
                    tmp3 = create_new_getraenk_file_2(count);
                    head_getraenk_file_2 = insert_file_at_head_2(&head_getraenk_file_2, tmp3);
                    count = 100;
                    aktuellesGetraenk_file = head_getraenk_file;
                    aktuellesGetraenk_file_2 = head_getraenk_file_2;
                }
            }
            lese_textfile_in_getraenk(head_getraenk_file->file);
            nextion_change_page(STARTANZEIGE);
            setze_startanzeige(aktuellesGetraenk);
            counter = 0;
            for (int i = 0 ; i <20 ; i ++)
            {
                buff_name[i] = '\0';
            }
        }
        else
        {
            nextion_setText("t0", "Noch nicht 100% ausgewählt.");
        }
        break;
    }
    head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
}

void check_loeschanzeige(uint8_t button)
{
    switch (button)
    {
    case JA:
        /*      0x01 = 0b01
                    - Wenn das File das tail-File ist, muss das File vor dem tail-File das neue tail-File werden
                    - Wenn das File das head-File ist, muss das File nach dem head-File das neue head-File werden
                    - Die folgenden/vorausgehenden Files werden reorganisiert
                    - String für zu löschendes File wird generiert
                    - Das File wird gelöscht
                    - Das nächste Getränk wird in das aktuelleGetraenk geladen
                    - Startanzeige setzen
        */
        if (aktuellesGetraenk_file == tail_getraenk_file)
        {
            tail_getraenk_file = aktuellesGetraenk_file->prev;
        }
        else if (aktuellesGetraenk_file == head_getraenk_file)
        {
            head_getraenk_file = aktuellesGetraenk_file->next;
        }
        (aktuellesGetraenk_file->prev)->next = aktuellesGetraenk_file->next;
        (aktuellesGetraenk_file->next)->prev = aktuellesGetraenk_file->prev;

        char buff[20];
        itoa(aktuellesGetraenk_file->file, (char *)buff, 10);
        strcat((char *) buff,(const char *)".txt");

        deleteFile((unsigned char *)buff);

        aktuellesGetraenk_file = aktuellesGetraenk_file->next;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;

    case NEIN:
        /*      0x02 = 0b02
                    - Startanzeige setzen
        */
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_posanzeige(uint8_t button)
{
    switch (button)
    {
    case B0:
        /*      0x01 = 0b01
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 0 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        // Setzt die Zutat, welche Beschrieben werden soll.
        setze_aktuelle_Zutat_in_Maschine_prev(0);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B1:
        /*      0x02 = 0b02
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 1 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(1);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B2:
        /*      0x03 = 0b03
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 2 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(2);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B3:
        /*      0x04 = 0b04
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 3 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(3);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B4:
        /*      0x05 = 0b05
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 4 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(4);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B5:
        /*      0x06 = 0b06
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 5 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(5);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B6:
        /*      0x07 = 0b07
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 6 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(6);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B7:
        /*      0x08 = 0b08
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 7 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(7);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B8:
        /*      0x09 = 0b09
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 8 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(8);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B9:
        /*      0x0A = 0b10
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 9 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(9);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B10:
        /*      0x0B = 0b11
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 10 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(10);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case B11:
        /*      0x0C = 0b12
                    - Wechsle auf Flüssigkeitsanzeige1
                    - Auf ausgewählte Position zeigen (Pos 11 in Liste), damit die Zutat darin abgelegt werden kann
                    - Liste erstellen für Zutatenauswahl, welche in die Maschine gestellt wird
        */
        kohlensaeure_mode = 0;
        setze_aktuelle_Zutat_in_Maschine_prev(11);
        begin_erstelle_Liste_Zutat_Pos();
        break;

    case ZURUECK3:
        /*      0x0D = 0b13
                    - Wechsle auf Menuanzeige
        */
        renew_list();
        break;

    case KOHLENSAEURE:
        /*      0x0E = 0b14
                    - Wechsle auf Menuanzeige
        */
        kohlensaeure_mode = 1;
        begin_erstelle_Liste_Zutat_Pos();
        break;
    }
}


void check_fluessanzeige1(uint8_t button)
{
    switch (button)
    {
    case FLUESSIGKEIT1:
        /*      0x01 = 0b01
                    - Lese File an Stelle 0 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(0, VOLL);
        }
        if (kohlensaeure_mode == 1)
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(0, VOLL);
        }
        break;

    case FLUESSIGKEIT2:
        /*      0x02 = 0b02
                    - Lese File an Stelle 1 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(1, VOLL);
        }
        else
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(1, VOLL);
        }
        break;

    case FLUESSIGKEIT3:
        /*      0x03 = 0b03
                    - Lese File an Stelle 2 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(2, VOLL);
        }
        else
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(2, VOLL);
        }
        break;

    case FLUESSIGKEIT4:
        /*      0x04 = 0b04
                    - Lese File an Stelle 3 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(3, VOLL);
        }
        else
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(3, VOLL);
        }
        break;

    case FLUESSIGKEIT5:
        /*      0x05 = 0b05
                    - Lese File an Stelle 4 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(4, VOLL);
        }
        else
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(4, VOLL);
        }
        break;

    case FLUESSIGKEIT6:
        /*      0x06 = 0b06
                    - Lese File an Stelle 5 der Liste und setze Status VOLL
        */
        if (kohlensaeure_mode == 0)
        {
            setze_Fluessgkeit_in_Position(5, VOLL);
        }
        else
        {
            block_list_runter = 0;
            setze_Fluessgkeit_in_Position_Aussen(5, VOLL);
        }
        break;

    case RAUFLIST5:
        /*      0x07 = 0b07c
                    - Untere Blockierung aufheben
                    - Gehe Liste um 6 Getränke hoch, falls nicht schon am oberen Ende
                    - Schreibe Cocktailnamen in die Liste*/
        if (!block_list_hoch)
        {
            block_list_runter = 0;
            aktuelle_zutat_list_node = aktuelle_zutat_list_node->next;
            erstelle_Liste_Zutat_Pos(aktuelle_zutat_list_node->zutat_xy, "fluessigkeit");
        }
        break;

    case RUNTERLIST5:
        /*      0x08 = 0b08
                    - Obere Blockierung aufheben
                    - Gehe Liste um 6 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_runter)
        {

            block_list_hoch = 0;
            aktuelle_zutat_list_node = aktuelle_zutat_list_node->prev;
            lese_textfile_in_zutat(aktuelle_zutat_list_node->zutat_xy->file);
            Uart_Transmit_IT_PC(aktuelle_zutat->name);
            Uart_Transmit_IT_PC("\r");
            buffer_zutat_file = erstelle_Liste_Zutat_Pos(aktuelle_zutat_list_node->zutat_xy, "fluessigkeit");
            if (aktuelle_zutat_list_node==head_zutat_list_node)
            {
                zutat_list_node_t * tmp = create_new_list_node_zut_file(buffer_zutat_file);
                head_zutat_list_node = insert_zutat_list_node_at_head(&head_zutat_list_node, tmp);
            }
        }
        break;

    case NEUEFLUESSIGKEIT:
        /*      0x09 = 0b09
                    - Fluessanzeige2 setzen
                    - i_Liste für Listenabschnitt auf 0 setzen
        */
        nextion_change_page(FLUESSANZEIGE2);
        i_Liste = 0;
        break;

    case KEINEFLUESSIGKEIT:
        /*      0x0A = 0b10
                    - Flüssigkeit ausserhalb des Listenbereichs bedeutet keine Flüssigkeit, deshalb 6
                    - Der Status der Flüssigkeit ist KEINGETRAENK
        */
        setze_Fluessgkeit_in_Position(6, KEINGETRAENK);
        break;

    case ZURUECK4:
        /*      0x0B = 0b11
                    - Posanzeige setzen
                    - Färbe die Nummern der Positionen gemäss Status
                    - i_Liste für Listenabschnitt auf 0 setzen
        */
        block_list_hoch = 0;
        block_list_runter = 0;
        nextion_change_page(POSANZEIGE);
        setze_Posanzeige_Rot_Gruen();
        break;
    }
}

void check_fluessanzeige2(uint8_t button)
{
    uint8_t vorhanden = 0;

    /*
        Die hier vorkommenden Einstellungsmöglichkeiten dieser Seite besitzen
        gemäss Nextion-Editor dieselben Buttons wie auf der
        Seite Erstanzeige1. Bis auf den Weiter-Button haben alle die selbe
        Funktion. Deswegen werden auch die selben ID's gesendet, wie auf der
        Erstanzeige1-seite und somit auch diese schon geschriebenen
        Funktionen. Der Weiter-Button wird im folgenden aufgeführt.
    */
    switch (button)
    {
    case 1:
        /*      0x01 = 0b01
                    - FLUESSANZEIGE3 setzen
                    - Name in aktuellesGetraenk schreiben
                    - i_Liste für Listenabschnitt auf 0 setzen
        */

        // Wurde kein Name eingegeben, wird user darüber informiert.
        if (strlen(buff_name) == 0)
        {
            nextion_setText("neuefluesstxt", "Bitte mindestens ein Zeichen eigeben.");
        }
        else
        {
// Aneinanderreihen zweier Listen
            nextion_setText("neuefluesstxt", "Überprüfe, ob Zutat exisiert.");

// Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
            zutat_file_t * tmp_zut_file_tail;
// zutatMaschine_t * tmp_zut_Maschine_head;
            zutat_file_t * tmp_zut_file_actual;

// Speichern der Momentanen Pointer.
            zutat_file_t * tmp_ohne_KS_head = head_Zutat_file_in_Maschine_ohne_KS->prev;
            zutat_file_t * tmp_mit_KS_head = head_Zutat_file_ausser_Maschine_mit_KS->prev;
            zutat_file_t * tmp_ohne_KS_tail = tail_Zutat_file_in_Maschine_ohne_KS->next;
            zutat_file_t * tmp_mit_KS_tail = tail_Zutat_file_ausser_Maschine_mit_KS->next;

// Anfang und Ende der gesamten Liste
            tmp_zut_file_tail = tail_Zutat_file_in_Maschine_ohne_KS;
// tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

// Äussere Verbindungen
            tail_Zutat_file_in_Maschine_ohne_KS->next = head_Zutat_file_ausser_Maschine_mit_KS;
            head_Zutat_file_ausser_Maschine_mit_KS->prev = tail_Zutat_file_in_Maschine_ohne_KS;

// Innere Verbindungen
            tail_Zutat_file_ausser_Maschine_mit_KS->next = head_Zutat_file_in_Maschine_ohne_KS;
            head_Zutat_file_in_Maschine_ohne_KS->prev = tail_Zutat_file_ausser_Maschine_mit_KS;

            tmp_zut_file_actual = tmp_zut_file_tail;
            do
            {
                lese_textfile_in_zutat(tmp_zut_file_actual->file);
                if (strcmp(aktuelle_zutat->name, (char *)buff_name)==0)
                {
                    vorhanden = 1;
                    nextion_setText("neuefluesstxt", "Name schon vorhanden.");

                }
                tmp_zut_file_actual = tmp_zut_file_actual->prev;
            } while (tmp_zut_file_actual != tmp_zut_file_tail);

            head_Zutat_file_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
            head_Zutat_file_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
            tail_Zutat_file_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
            tail_Zutat_file_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;

        }

        if (vorhanden == 0)
            // Weiter zur nächsten Seite, der Name wird in der aktuellen Zutat gespeichert.
        {
            nextion_change_page(FLUESSANZEIGE4-1);
            strcpy(aktuelle_zutat->name,(const char *)buff_name);
        }
        break;
    }
}

void check_fluessanzeige3(uint8_t button)
{
    char buff_filename[15] = {'\0'};
    char buff_string[50] = {'\0'};
    char * ptr = buff_string;
    char buff_itoa[5] = {'\0'};
    zutat_file_t * tmp;

    switch (button)
    {
    case JA1:
    case NEIN2:
        /*      0x01/0x02 = 0b01/0b02
                    - String erstellen für Zutatenspeicherung
                        Format: Zn.txt (n = Zahl)
                        ****************************************************
                        Name:Getraenk1
                        Alkohol:1/0
                        ****************************************************
                    - Erstellte Zutat in der Liste einfügen
                    - Freies File suchen, erstellen und auf SD-Karte ablegen
                    - i_Liste für Listenabschnitt auf 0 setzen
                    - Untere Blockierung aufheben
                    - Obere Blockierung aufheben
                    - Liste mit Zutaten erstellen
                    - Name der aktuellen Zutat auf 0 initialisieren
        */

        // Zeige dem User, was geschieht
        nextion_change_page(RFIDFEHLER);
        nextion_setText("fehlertxt", "Zutat wird probiert und \\rgespeichert...");

        // Überprüfe ob Ja/Nein
        if (button == JA1)
        {
            aktuelle_zutat->alkohol = 1;
        }
        if (button == NEIN2)
        {
            aktuelle_zutat->alkohol = 0;
        }

        // Erstelle String, um Zutat zu speichern
        strcpy(ptr, (const char *)"Name:");
        strcat(ptr, (const char *)aktuelle_zutat->name);
        strcat(ptr, (const char *)"\rAlkohol:");
        itoa(aktuelle_zutat->alkohol, (char *)buff_itoa, 10);
        strcat(ptr, (const char *)buff_itoa);
        strcat(ptr, (const char *)"\rKohlensaeure:");
        itoa(aktuelle_zutat->kohlensaeure, (char *)buff_itoa, 10);
        strcat(ptr, (const char *)buff_itoa);
        strcat(ptr, (const char *)"~");

        // Suche nächste freie Nummer für File.
        uint8_t stop_suche = 0;
        int8_t count = 1;

        while (stop_suche == 0)
        {
            // String mit Name des Textfiles erstellen (Z0.txt bis Z199.txt)
            strcpy((char *)buff_filename, (const char *)"Z");
            itoa(count, (char *)buff_itoa, 10);
            strcat((char *)buff_filename, (const char *)buff_itoa);
            strcat((char *)buff_filename, (const char *)".txt");

            // Prüfen ob File existiert
            if(readFile(VERIFY, (unsigned char *)buff_filename)!=1)
            {
                // File abspeichern
                strcpy((char *)buff_filename, (const char *)"Z");
                itoa(count, (char *)buff_itoa, 10);
                strcat((char *)buff_filename, (const char *)buff_itoa);
                strcat((char *)buff_filename, (const char *)".txt");
                writeFile((unsigned char *)buff_filename, (unsigned char *)ptr);

                tmp = create_new_zutat_file(count);
                lese_textfile_in_zutat(count);
                if (aktuelle_zutat->kohlensaeure == 0)
                {
                    head_Zutat_file_in_Maschine_ohne_KS = insert_zutat_file_at_head(&head_Zutat_file_in_Maschine_ohne_KS, &tail_Zutat_file_in_Maschine_ohne_KS, tmp);
                }
                else
                {
                    head_Zutat_file_ausser_Maschine_mit_KS = insert_zutat_file_at_head(&head_Zutat_file_ausser_Maschine_mit_KS, &tail_Zutat_file_ausser_Maschine_mit_KS, tmp);
                }
                stop_suche = 1;
            }
            count++;
        }

        // Resetten des buff_name und counter
        uint8_t len = strlen((const char *)buff_name);
        for (uint8_t kk = 0 ; kk <= len ; kk++)
        {
            buff_name[kk] = '\0';
        }

        counter = 0;

        // Falls neue Zutat im Kohensäuremodus gestartet wurde
        if (kohlensaeure_mode == 0)
        {
            if (aktuelle_zutat->kohlensaeure == 0)
            {
                setze_Fluessgkeit_in_Position(7, VOLL);
            }
            else
            {
                setze_Fluessgkeit_in_Position(8, VOLL);
            }
        }
        else
        {
            if (aktuelle_zutat->kohlensaeure == 1)
            {
                nextion_change_page(POSANZEIGE);
                nextion_setText("zubabfrage", "Wird geprüft.");
//                 erstelle_Liste_Zutat_Pos(aktuelle_zutat_list_node->zutat_xy, "fluessigkeit");
                setze_Fluessgkeit_in_Position_Aussen(8, VOLL);
            }
            else
            {
                nextion_change_page(POSANZEIGE);
                nextion_setText("zubabfrage", "Bitte separat setzen.");
//                 erstelle_Liste_Zutat_Pos(aktuelle_zutat_list_node->zutat_xy, "fluessigkeit");
            }
        }
        break;

    case ZURUECK7:
        /*      0x0A = 0b10
                    - FLUESSANZEIGE2 setzen
        */
        nextion_change_page(FLUESSANZEIGE4-1);
        break;
    }
}

void check_fluessanzeige4(uint8_t button)
{
    switch (button)
    {
    case JA2:
        nextion_change_page(FLUESSANZEIGE3);
        aktuelle_zutat->kohlensaeure = 1;
        break;

    case NEIN2:
        nextion_change_page(FLUESSANZEIGE3);
        aktuelle_zutat->kohlensaeure = 0;
        break;

    case ZURUECK11:
        /*      0x0A = 0b10
                    - FLUESSANZEIGE2 setzen
        */
        nextion_change_page(FLUESSANZEIGE2);
        nextion_setText("neuername", (char *)buff_name);
        break;
    }
}

void check_RFIDAnzeige1(uint8_t button)
{
    switch (button)
    {
    case RFID1:
        /*      0x01 = 0b01
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 0 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RFID2:
        /*      0x02 = 0b02
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 1 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RFID3:
        /*      0x03 = 0b03
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 2 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RFID4:
        /*      0x04 = 0b04
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 3 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RFID5:
        /*      0x05 = 0b05
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 4 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RFID6:
        /*      0x06 = 0b06
                    - Wechsle auf Zutatenanzeige
                    -
        */
        aktueller_tag = tail_tag;
        for (int i = 0 ; i < i_Liste + 5 ; i++)
        {
            aktueller_tag = aktueller_tag->prev;
        }
        nextion_change_page(RFIDANZEIGE2);
        i_Liste = 0;
        block_list_hoch = 0;
        block_list_runter = 0;
        erstelle_Liste_name(tail_getraenk_file, "cocktail");
        break;

    case RAUFLIST6:
        /*      0x07 = 0b07
                    - Wechsle auf Zutatenanzeige
                    -
        */
        if (!block_list_hoch)
        {
            block_list_runter = 0;
            i_Liste -=6;

            // Getränkedurchwahr bei Tail starten.
            aktueller_tag = tail_tag;

            // Shifte aktuelles Getränk auf bestimmte Seite
            // (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
            for (int i = 0 ; i < i_Liste ; i++)
            {
                aktueller_tag = aktueller_tag->prev;
            }

            // Für alle Buttons auf der Seite ...
            // Initialisierungen
            char button[21] = {'\0'};
            char buff[4] = {0};
            char buff10[20] = {'\0'};
            strcat((char *)buff10, "rfid");
            itoa((i + 1), (char *)buff, 10);
            strcat((char *)buff10, (const char *)buff);

            nextion_enableButton(buff10);

            for (int i = 0 ; i < 6 ; i++)
            {
                // Schreibe Zahl und Name des Buttons in String
                itoa((i + 1),buff,10);
                strcpy((char *)button, "rfid");
                strcat((char *)button, (const char *)buff);

                // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
                // runterscrollen blockieren und letzter Name einschreiben.
                if (aktueller_tag == head_tag && !block_list_runter)
                {
                    block_list_runter = 1;
                    itoa(aktueller_tag->tag_nummer, (char *)buff, 10);
                    nextion_setText(button, buff);
                }

                // Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
                // die Buttons disablen
                else if (block_list_runter)
                {
                    // leerer String
                    nextion_setText(button,"");

                    // Sicherheitsdelay, Programm stürzt sonst ab
                    _delay_ms(10);

                    // Schreibe Text und Buttonnummer für disable in String
                    strcpy((char *)buff10, "rfid");
                    itoa((i + 1), (char *)buff, 10);
                    strcat((char *)buff10, (const char *)buff);

                    // Disable Button
                    nextion_disableButton(buff10);
                }

                //Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
                else
                {
                    itoa(aktueller_tag->tag_nummer, (char *)buff, 10);
                    nextion_setText(button, buff);
                }

                // Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
                if(aktueller_tag == tail_tag && !block_list_runter)
                {
                    block_list_hoch = 1;
                }

                // Ein Getraenk weiter Scrollen
                aktueller_tag = aktueller_tag->prev;

                // Sicherheitsdelay, Programm stürzt sonst ab
                _delay_ms(10);
            }
        }
        break;

    case RUNTERLIST6:
        /*      0x08 = 0b08
                    - Wechsle auf Zutatenanzeige
                    -
        */
        if (!block_list_runter)
        {
            block_list_hoch = 0;
            i_Liste +=6;
            // Getränkedurchwahr bei Tail starten.
            aktueller_tag = tail_tag;

            // Shifte aktuelles Getränk auf bestimmte Seite
            // (1. Seite: i_Liste = 0; 2. Seite: i_Liste = 8; ...)
            for (int i = 0 ; i < i_Liste ; i++)
            {
                aktueller_tag = aktueller_tag->prev;
            }

            // Für alle Buttons auf der Seite ...
            // Initialisierungen
            char button[21] = {'\0'};
            char buff[4] = {0};
            char buff10[20] = {'\0'};
            strcat((char *)buff10, "rfid");
            itoa((i + 1), (char *)buff, 10);
            strcat((char *)buff10, (const char *)buff);

            nextion_enableButton(buff10);

            for (int i = 0 ; i < 6 ; i++)
            {
                // Schreibe Zahl und Name des Buttons in String
                itoa((i + 1),buff,10);
                strcpy((char *)button, "rfid");
                strcat((char *)button, (const char *)buff);

                // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
                // runterscrollen blockieren und letzter Name einschreiben.
                if (aktueller_tag == head_tag && !block_list_runter)
                {
                    block_list_runter = 1;
                    itoa(aktueller_tag->tag_nummer, (char *)buff, 10);
                    nextion_setText(button, buff);
                }

                // Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
                // die Buttons disablen
                else if (block_list_runter)
                {
                    // leerer String
                    nextion_setText(button,"");

                    // Sicherheitsdelay, Programm stürzt sonst ab
                    _delay_ms(10);

                    // Schreibe Text und Buttonnummer für disable in String
                    strcpy((char *)buff10, "rfid");
                    itoa((i + 1), (char *)buff, 10);
                    strcat((char *)buff10, (const char *)buff);

                    // Disable Button
                    nextion_disableButton(buff10);
                }

                //Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
                else
                {
                    itoa(aktueller_tag->tag_nummer, (char *)buff, 10);
                    nextion_setText(button, buff);
                }

                // Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
                if(aktueller_tag == tail_tag && !block_list_runter)
                {
                    block_list_hoch = 1;
                }

                // Ein Getraenk weiter Scrollen
                aktueller_tag = aktueller_tag->prev;

                // Sicherheitsdelay, Programm stürzt sonst ab
                _delay_ms(10);
            }

        }
        break;

    case ZURUECK5:
        /*      0x09 = 0b09
                    - Wechsle auf Zutatenanzeige
                    -
        */
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        i_Liste = 0;
        break;
    }
}

void check_RFIDAnzeige2(uint8_t button)
{
    switch (button)
    {
    /*      0x01 bis 0x08 = 0b01 bis 0b08
                - Wähle x-ten Cocktail des aktuellen Listenabschnitts
    */
    case COCKTAIL1:
        schreibe_Getraenk_in_tag(0);
        break;

    case COCKTAIL2:
        schreibe_Getraenk_in_tag(1);
        break;

    case COCKTAIL3:
        schreibe_Getraenk_in_tag(2);
        break;

    case COCKTAIL4:
        schreibe_Getraenk_in_tag(3);
        break;

    case COCKTAIL5:
        schreibe_Getraenk_in_tag(4);
        break;

    case COCKTAIL6:
        schreibe_Getraenk_in_tag(5);
        break;

    case RAUFLIST1:
        /*      0x09 = 0b09
                    - Untere Blockierung aufheben
                    - Gehe Liste um 8 Getränke hoch, falls nicht schon am oberen Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_hoch)
        {
            block_list_runter = 0;
            i_Liste -= 1;
            erstelle_Liste_name(liste_vorher_getraenk_file, "cocktail");
        }
        break;

    case RUNTERLIST1:
        /*      0x0A = 0b10
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        if (!block_list_runter)
        {
            block_list_hoch = 0;
            i_Liste += 1;
            erstelle_Liste_name(liste_nacher_getraenk_file, "cocktail");
        }
        break;

    case ZURUECK9:
        /*      0x0B = 0b11
                    - Obere Blockierung aufheben
                    - Gehe Liste um 8 Getränke runter, falls nicht schon am unteren Ende
                    - Schreibe Cocktailnamen in die Liste
        */
        block_list_hoch = 0;
        block_list_runter = 0;
        i_Liste = 0;
        nextion_change_page(RFIDANZEIGE1);
        break;
    }
}

void check_RFIDFehler(uint8_t button)
{
    switch (button)
    {
    case 1:
        setze_startanzeige(aktuellesGetraenk);
        break;
    }
}

void check_ESP32(uint8_t button)
{
    // Block RFID during zubereitung
    switch (button)
    {
    // Sende Anzahl Tags
    case TAGNR:
        Getraenk_erstellt();
        break;

    case GETRAENKE:
        send_List_Getraenke();
        break;

    case ZUTATEN2:
        send_List_Zutaten();
        break;

    case XXX:
        ESP_Getraenk();
        break;
    }
}

void check_LED(uint8_t button)
{
    asm("nop");
    switch (button)
    {
    case WEISS:
        light = WEISS_LED;
        break;

    case RAINBOW:
        light = RAINBOW_LED;
        break;

    case CUSTOM:
        light = USER_LED;
        char val[20] = {'\0'};
        itoa(OCR3B / 7, (char *) val, 10);
        nextion_setValue("slider1", (char *)val);
        itoa(OCR4B / 7, (char *) val, 10);
        nextion_setValue("slider2", (char *)val);
        itoa(OCR5B / 7, (char *) val, 10);
        nextion_setValue("slider3", (char *)val);
        itoa(OCR1B / 7, (char *) val, 10);
        nextion_setValue("slider4", (char *)val);
        break;

    case SLIDER11:
        OCR3B = 7 * nextion_getSliderValue("slider1", (unsigned char *)INPUT_UART_1);
        break;

    case SLIDER12:
        OCR4B = 7 * nextion_getSliderValue("slider2", (unsigned char *)INPUT_UART_1);
        break;

    case SLIDER13:
        OCR5B = 7 * nextion_getSliderValue("slider3", (unsigned char *)INPUT_UART_1);
        break;

    case SLIDER14:
        OCR1B = 7 * nextion_getSliderValue("slider4", (unsigned char *)INPUT_UART_1);
        break;

    case ZURUECK8:
        nextion_change_page(MENUANZEIGE);
        break;
    }
}