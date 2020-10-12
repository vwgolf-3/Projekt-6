/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */

#include "Cocktail_functions.h"


//***********************************************//
// Inits
//***********************************************//

void SD_startup(void)
{
//     cardType = 0;
//
//     for (i=0; i<10; i++)
//     {
//         error = SD_init();
//         if(!error) break;
//     }
//
//     if(error)
//     {
//         if(error == 1) Uart_Transmit_IT_PC((char*)("SD card not detected..\r"));
//         if(error == 2) Uart_Transmit_IT_PC((char*)("Card Initialization failed..\r"));
//         nextion_change_page(FEHLERANZEIGE);
//         nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte erkannt.\\rBitte prüfen und\\rneu starten.");
//         while(1);  //wait here forever if error in SD init
//     } else {
//
//         switch (cardType)
//         {
//         case 1:
//             Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 1.x) Detected!\r"));
//             break;
//         case 2:
//             Uart_Transmit_IT_PC(("High Capacity Card Detected!\r"));
//             break;
//         case 3:
//             Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 2.x) Detected!\r"));
//             break;
//         default:
//             Uart_Transmit_IT_PC(("Unknown SD Card Detected!\r"));
//             break;
//         }
//     }
//
//     //  SPI_HIGH_SPEED; //SCK - 4 MHz
//     _delay_ms(1);   //some delay
//
//
//     FAT32_active = 1;
//     error = getBootSectorData (); //read boot sector and keep necessary data in global variables
//     if(error)
//     {
//         nextion_change_page(FEHLERANZEIGE);
//         nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte erkannt.\\rBitte prüfen und\\rneu starten.");
//         Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
//         FAT32_active = 0;
//     }
//     //  findFiles(GET_LIST,0);

}

void display_init(void)
{
    // Initialisierungen Display
    Grossschreib = 1;                                       // Initialisiere Grossschreibung Display mit gross (gibt kein Display init();)
    i_Liste = 0;                                            // Listenabschnitt auf 0 vordefinieren
    block_list_hoch = 0;                                    // Blockierung der Listen aufheben
    block_list_runter = 0;                                  // Blockierung der Listen aufheben
}



//***********************************************//
// List-Handling
//***********************************************//

void concentrace_zutat_maschine_list(void)
{
    // Speichern der Momentanen Pointer.
    tmp_ohne_KS_head = head_zutat_maschine_ohne->prev;
    tmp_mit_KS_head = head_zutat_maschine_mit->prev;
    tmp_ohne_KS_tail = tail_zutat_maschine_ohne->next;
    tmp_mit_KS_tail = tail_zutat_maschine_mit->next;

    // Anfang und Ende der gesamten Liste
    tmp_zut_Maschine_head = head_zutat_maschine_ohne;
    tmp_zut_Maschine_tail = tail_zutat_maschine_mit;

    // Äussere Verbindungen
    tail_zutat_maschine_ohne->next = head_zutat_maschine_mit;
    head_zutat_maschine_mit->prev = tail_zutat_maschine_ohne;

    // Innere Verbindungen
    tail_zutat_maschine_mit->next = head_zutat_maschine_ohne;
    head_zutat_maschine_ohne->prev = tail_zutat_maschine_mit;
}

void deconcentrace_zutat_maschine_list(void)
{
    head_zutat_maschine_ohne->prev =tmp_ohne_KS_head;
    head_zutat_maschine_mit->prev = tmp_mit_KS_head;
    tail_zutat_maschine_ohne->next = tmp_ohne_KS_tail;
    tail_zutat_maschine_mit->next = tmp_mit_KS_tail;
}


void runterlist_files(uint8_t art)
{
    if (!block_list_runter)
    {
        block_list_hoch = 0;

        switch (art)
        {
        case COCKTAIL:
            actual_list_node_getraenk = actual_list_node_getraenk->next;
            buffer2_getraenk_file_alle = erstelle_liste_cocktails(actual_list_node_getraenk->_file, "cocktail");
            if (actual_list_node_getraenk == tail_list_node_getraenk)
            {
                insert_at_end_3(buffer2_getraenk_file_alle, &number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
                display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
            }
            break;

        case ZUTAT:
            actual_list_node_zutaten = actual_list_node_zutaten->next;
            buffer2_getraenk_file_alle = erstelle_liste_zutat_pos(actual_list_node_zutaten->_file, "fluessigkeit");
            if (actual_list_node_zutaten == tail_list_node_zutaten)
            {
                insert_at_end_3(buffer2_getraenk_file_alle, &number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
                display_from_beg_3(number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
            }
            break;
        }
    }
}

void rauflist_files(uint8_t art)
{
    if (!block_list_hoch)
    {
        block_list_runter = 0;
        switch (art)
        {
        case COCKTAIL:
            actual_list_node_getraenk = actual_list_node_getraenk->prev;
            erstelle_liste_cocktails(actual_list_node_getraenk->_file, "cocktail");
            break;

        case ZUTAT:
            actual_list_node_zutaten = actual_list_node_zutaten->prev;
            erstelle_liste_zutat_pos(actual_list_node_zutaten->_file, "fluessigkeit");
            break;
        }
    }
}

void delete_list_node_files(uint8_t art)
{
    switch (art)
    {
    case COCKTAIL:
        while (*number_list_getranke_alle > 1)
        {
            delete_node_position_3(1, number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
            display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
        }
        display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
        break;

    case ZUTAT:
        while (*number_list_zutaten > 1)
        {
            delete_node_position_3(1, number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
            display_from_beg_3(number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
        }
        display_from_beg_3(number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
        break;
    }









}


void runterlist_zutat_maschine(void)
{
    if (!block_list_runter)
    {
        block_list_hoch = 0;
        actual_list_node_zutat_maschine = actual_list_node_zutat_maschine->next;
        buffer_zutat_maschine = erstelle_liste_zutat(actual_list_node_zutat_maschine->zutat_maschine, "zutat");

        if (actual_list_node_zutat_maschine == tail_list_node_zutat_maschine)
        {
            insert_at_end_4(buffer_zutat_maschine, &number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
//             display_from_beg_4(number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
        }
    }
}

void rauflist_zutat_maschine(void)
{
    if (!block_list_hoch)
    {
        block_list_runter = 0;
        actual_list_node_zutat_maschine = actual_list_node_zutat_maschine->prev;
        erstelle_liste_zutat(actual_list_node_zutat_maschine->zutat_maschine, "zutat");
    }
}

void delete_list_node_zutat_maschine(void)
{
    while (*number_list_zutat_maschine > 1)
    {
        delete_node_position_4(1, number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
//      display_from_beg_4(number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
    }
//  display_from_beg_4(number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
}


void delete_file_node_alle(uint8_t art)
{
    switch (art)
    {
    case COCKTAIL:
        while (*number_getraenk_alle > 1)
        {
            delete_node_position(1, number_getraenk_alle, &head_getraenk_file_alle, &tail_getraenk_file_alle);
            display_from_beg(number_getraenk_alle, &head_getraenk_file_alle, &tail_getraenk_file_alle);
        }
        display_from_beg(number_getraenk_alle, &head_getraenk_file_alle, &tail_getraenk_file_alle);
        break;

    case ZUTAT_OHNE:
        while (*number_zutaten_ohne > 1)
        {
            delete_node_position(1, number_zutaten_ohne, &head_zutat_file_ohne, &tail_zutat_file_ohne);
            display_from_beg(number_zutaten_ohne, &head_zutat_file_ohne, &tail_zutat_file_ohne);
        }
        display_from_beg(number_zutaten_ohne, &head_zutat_file_ohne, &tail_zutat_file_ohne);
        break;

    case ZUTAT_MIT:
        while (*number_zutaten_mit > 1)
        {
            delete_node_position(1, number_zutaten_mit, &head_zutat_file_mit, &tail_zutat_file_mit);
            display_from_beg(number_zutaten_mit, &head_zutat_file_mit, &tail_zutat_file_mit);
        }
        display_from_beg(number_zutaten_mit, &head_zutat_file_mit, &tail_zutat_file_mit);
        break;
    }
}


void begin_erstelle_liste_cocktails(uint8_t page, char* button)
{
    update_3(1, actual_getraenk_file_alle, number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
    display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
    actual_list_node_getraenk = tail_list_node_getraenk;
    nextion_change_page(page);
    buffer2_getraenk_file_alle = erstelle_liste_cocktails(actual_list_node_getraenk->_file, button);

    // Zweiten Listenabschnitt erstellen
    insert_at_end_3(buffer2_getraenk_file_alle, &number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
    display_from_beg_3(number_list_getranke_alle, &head_list_node_getraenk, &tail_list_node_getraenk);
}

void begin_erstelle_liste_zutaten_maschine(uint8_t page, char* button)
{
    // Die Zutaten werden ab Beginn gesucht.
    if (kohlensaeure_mode == 0)
    {
        buffer_zutat_file = head_zutat_file_ohne;
    }
    else
    {
        buffer_zutat_file = head_zutat_file_mit;
    }
    update_3(1, buffer_zutat_file, number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
    display_from_beg_3(number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
    actual_list_node_zutaten = head_list_node_zutaten;
    nextion_change_page(page);
    buffer_zutat_file = erstelle_liste_zutat_pos(actual_list_node_zutaten->_file, button);
    // Zweiten Listenabschnitt erstellen
    insert_at_end_3(buffer_zutat_file, &number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
    display_from_beg_3(number_list_zutaten, &head_list_node_zutaten, &tail_list_node_zutaten);
}

void begin_erstelle_liste_alle_zutaten(uint8_t page, char * name)
{
    // Ersten Listenabschnitt erstellen
    update_4(1, head_zutat_maschine_ohne, number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
    display_from_beg_4(number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
    actual_list_node_zutat_maschine = head_list_node_zutat_maschine;

    // User Reaktion Zeigen
    nextion_change_page(page);
    buffer_zutat_maschine = erstelle_liste_zutat(head_zutat_maschine_ohne, name);

    // Zweiten Listenabschnitt erstellen
    insert_at_end_4(buffer_zutat_maschine, &number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
    display_from_beg_4(number_list_zutat_maschine, &head_list_node_zutat_maschine, &tail_list_node_zutat_maschine);
}


void setze_aktuelles_getraenk_in_maschine(uint8_t nr)
{
    file_node_t * tmp = actual_list_node_getraenk->_file;

    for (uint8_t cnt = 0 ; cnt < nr; cnt++)
    {
        tmp = tmp->next;
    }
    actual_getraenk_file_alle = tmp;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
}

void setze_aktuelle_Zutat_in_Maschine(uint8_t nr)
{
    zutat_maschine_node_t * tmp = head_zutat_maschine_ohne;
    for (int i = 0 ; i < nr; i++)
    {
        tmp = tmp->next;
    }
    aktuelle_Zutat_in_Maschine_ohne_KS = tmp;
}



//***********************************************//
//Erstelle Listeninhalte
//***********************************************//

file_node_t * erstelle_liste_cocktails(file_node_t * beginn_file, char * name_button)
{
    file_node_t * tmp_file_tail;
    file_node_t * tmp_file_head;
    file_node_t * tmp_file_actual = beginn_file;

    tmp_file_tail = tail_getraenk_file_alle;
    tmp_file_head = head_getraenk_file_alle;

    // Für alle Buttons auf der Seite ...
    // Initialisierungen
    char button[50] = {'\0'};
    char buff[5] = {0};

    for (int count = 0 ; count < 6 ; count++)
    {
        // Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
        if(tmp_file_actual == tmp_file_head && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        // Schreibe Zahl und Name des Buttons in String
        itoa((count + 1), (char *)buff, 10);
        strcpy((char *)button, (const char *)name_button);
        strcat((char *)button, (const char *)buff);
        nextion_enableButton(button);

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen blockieren und letzter Name einschreiben.
        if (tmp_file_actual == tmp_file_tail && !block_list_runter)
        {
            block_list_runter = 1;
            lese_textfile_in_getraenk(tmp_file_actual->file);
            nextion_setText(button,aktuellesGetraenk->name);
        }

        // Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
        // die Buttons disablen
        else if (block_list_runter)
        {
            // leerer String
            nextion_setText(button,"");

            // Sicherheitsdelay, Programm stürzt sonst ab
            _delay_ms(10);

            // Disable Button
            nextion_disableButton(button);
        }

        //Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
        else
        {
            lese_textfile_in_getraenk(tmp_file_actual->file);
            nextion_setText(button,aktuellesGetraenk->name);
        }

        // Ein Getraenk weiter Scrollen
        tmp_file_actual = tmp_file_actual->next;

        if (count == 5 && block_list_runter == 1)
        {
            return beginn_file;
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }
    return tmp_file_actual;
}

zutat_maschine_node_t * erstelle_liste_zutat(zutat_maschine_node_t * beginn_Maschine, char * input)
{
    // Strings für Name/Slider/Wert
    char string[21] = {'\0'};
    char string2[21] = {'\0'};
    char string3[21] = {'\0'};

    // Itoa-Buffer
    char buff[5] = {0};

    zutat_maschine_node_t * tmp_zut_Maschine_return = beginn_Maschine;

    concentrace_zutat_maschine_list();

    tmp_zut_Maschine_actual = beginn_Maschine;

    for (int count = 0 ; count < 4 ; count++)
    {
        // Schreibe Buttonname, Slidername und Anzeiename in einen String
        itoa((count+1),buff,10);

        strcpy((char *)string, (const char *)input);
        strcat((char *)string, (const char *)buff);

        strcpy((char *)string2, (const char *)"slider");
        strcat((char *)string2, (const char *)buff);

        strcpy((char *)string3, (const char *)"menge");
        strcat((char *)string3, (const char *)buff);

        nextion_visible_on(string);
        nextion_visible_on(string2);
        nextion_visible_on(string3);

        // Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde
        // (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "überläuft" und so beide
        // Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
        if(tmp_zut_Maschine_actual == tmp_zut_Maschine_head && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        while(tmp_zut_Maschine_actual->status == 0 && tmp_zut_Maschine_actual != tmp_zut_Maschine_tail)
        {
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
        }

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen, blockieren und letzter Name einschreiben.
        if (tmp_zut_Maschine_actual == tmp_zut_Maschine_tail && !block_list_runter)
        {
            block_list_runter = 1;
            if (tmp_zut_Maschine_actual->status == 1)
            {
                nextion_setText(string,tmp_zut_Maschine_actual->name);
                itoa(tmp_zut_Maschine_actual->menge,buff,10);
                nextion_setValue(string2,buff);
                strcat(buff, "%");
                nextion_setText(string3,buff);
            }
            else
            {
                nextion_visible_off(string);
                nextion_visible_off(string2);
                nextion_visible_off(string3);
            }
        }

        // Sonst, wenn Liste Blockiert
        // Leerer String in Feld schreiben
        else if (block_list_runter)
        {
            nextion_visible_off(string);
            nextion_visible_off(string2);
            nextion_visible_off(string3);
        }

        // Im Normalbetrieb Zutat in Feld schreiben,
        // Auf nächste Zutat zeigen
        else
        {
            nextion_setText(string,tmp_zut_Maschine_actual->name);
            itoa(tmp_zut_Maschine_actual->menge,buff,10);
            nextion_setValue(string2,buff);
            strcat(buff, "%");
            nextion_setText(string3,buff);
        }

        // Ein Getraenk weiter Scrollen.
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;

        if (count == 3 && block_list_runter == 0)
        {
            tmp_zut_Maschine_return = tmp_zut_Maschine_actual;
            deconcentrace_zutat_maschine_list();
            return tmp_zut_Maschine_return;
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }

    deconcentrace_zutat_maschine_list();
    return tmp_zut_Maschine_return;
}

file_node_t * erstelle_liste_zutat_pos(file_node_t * beginn_file, char * name_button)
{
    char buff[5] = {'\0'};

    if (kohlensaeure_mode ==0 )
    {
        nextion_visible_on("b1");
    }

    file_node_t * tmp_file_tail;
    file_node_t * tmp_file_head;
    file_node_t * tmp_file_actual = beginn_file;
    file_node_t * tmp_file_return = beginn_file;

    // Die Zutaten werden ab Beginn gesucht.
    if (kohlensaeure_mode == 0)
    {
        tmp_file_tail = tail_zutat_file_ohne;
        tmp_file_head = head_zutat_file_ohne;
    }
    else
    {
        tmp_file_tail = tail_zutat_file_mit;
        tmp_file_head = head_zutat_file_mit;
    }

    // Für alle Buttons auf der Seite ...
    char button[50] = {'\0'};
    char buff10[50] = {'\0'};

    for (int count = 0 ; count < 6 ; count++)
    {
        // Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde
        // (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "überläuft" und so beide
        // Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
        if(tmp_file_actual == tmp_file_head && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        // Beginn-File einlesen.
        lese_textfile_in_zutat(tmp_file_actual->file);

        // Schreibe Zahl und Name des Buttons in String
        itoa((count + 1),buff,10);
        strcpy((char *)button, (const char *)name_button);
        strcat((char *)button, (const char *)buff);
        nextion_enableButton(button);

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen, blockieren und letzter Name einschreiben.
        if (tmp_file_actual == tmp_file_tail && !block_list_runter)
        {
            block_list_runter = 1;
            if (aktuelle_zutat->kohlensaeure == kohlensaeure_mode)
            {
                nextion_setText(button,aktuelle_zutat->name);
            }
            else
            {
                // leerer String
                nextion_setText(button,"");

                // Sicherheitsdelay, Programm stürzt sonst ab
                _delay_ms(10);

                // Disable Button
                nextion_disableButton(button);
            }
        }

        // Falls die Liste blockiert ist, Leeren String in das Feld schreiben und
        // die Buttons disablen
        else if (block_list_runter)
        {
            // leerer String
            nextion_setText(button,"");

            // Sicherheitsdelay, Programm stürzt sonst ab
            _delay_ms(10);

            // Disable Button
            nextion_disableButton(button);
        }

        //Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
        else
        {
            nextion_setText(button,aktuelle_zutat->name);
        }

        if (kohlensaeure_mode == 0)
        {
            if (strcmp((char *)aktuelle_Zutat_in_Maschine_ohne_KS->name, (char *)aktuelle_zutat->name)==0)
            {
                strcpy((char *)buff10, (const char *)button);
                strcat((char *)buff10, (const char *)".pco=2016");
                Uart_Transmit_IT_Display((char *)buff10);
                endConversation();
            }
            else
            {
                strcpy((char *)buff10, (const char *)button);
                strcat((char *)buff10, (const char *)".pco=0");
                Uart_Transmit_IT_Display((char *)buff10);
                endConversation();
            }
        }
        else
        {
            aktuelle_Zutat_ausser_Maschine_mit_KS = head_zutat_maschine_mit;
            uint8_t run = 1;
            do
            {
                if (strcmp((char *)aktuelle_Zutat_ausser_Maschine_mit_KS->name, (char *)aktuelle_zutat->name)==0)
                {
                    strcpy((char *)buff10, (const char *)button);
                    strcat((char *)buff10, (const char *)".pco=2016");
                    Uart_Transmit_IT_Display((char *)buff10);
                    endConversation();
                    run = 0;
                }
                else
                {
                    strcpy((char *)buff10, (const char *)button);
                    strcat((char *)buff10, (const char *)".pco=0");
                    Uart_Transmit_IT_Display((char *)buff10);
                    endConversation();
                    aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->next;
                }
            } while (aktuelle_Zutat_ausser_Maschine_mit_KS != head_zutat_maschine_mit && run);
        }

        // Ein Getraenk weiter Scrollen.
        tmp_file_actual = tmp_file_actual->next;

        if (count == 5 && block_list_runter == 0)
        {
            tmp_file_return = tmp_file_actual;
            return tmp_file_return;
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }
    return tmp_file_return;
}



//***********************************************//
// Maschineneinstellungen
//***********************************************//

void setze_fluessgkeit_in_position_ohne(uint8_t nr, uint8_t status)
{
    char buff[50] = {'\0'};
    char buff2[5] = {'\0'};

    // Falls nr ausserhalb des Listenbereichs ==> Keine Flüssigkeit
    if (nr == 6)
    {
        // Schreibe Null-Terminator über bestehenden Namen
        strcpy(aktuelle_Zutat_in_Maschine_ohne_KS->name, "(keine)");
        aktuelle_Zutat_in_Maschine_ohne_KS->alkohol = 0;
        aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure=0;
        aktuelle_Zutat_in_Maschine_ohne_KS->status = status;
        nextion_change_page(POSANZEIGE);
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File (kohlesaeure_mode == 0 && aktuelleZutat->kohlesaeure == 0)
    if (nr == 7)
    {
        strcpy((char *)aktuelle_Zutat_in_Maschine_ohne_KS->name, (const char *)aktuelle_zutat->name);
        aktuelle_Zutat_in_Maschine_ohne_KS->alkohol = aktuelle_zutat->alkohol;
        aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure=aktuelle_zutat->kohlensaeure;
        aktuelle_Zutat_in_Maschine_ohne_KS->status = status;
        nextion_change_page(POSANZEIGE);
        // Schreibe Änderung in Titel der Positionsanzeige
        strcpy((char *)buff, "Nr.");
        itoa(aktuelle_Zutat_in_Maschine_ohne_KS->stelle+1, buff2, 10);
        strcat((char *)buff, (const char *)buff2);
        strcat((char *)buff, " = ");
        strcat((char *)buff, aktuelle_Zutat_in_Maschine_ohne_KS->name);
        nextion_setText("zubabfrage",buff);
        //         tail_zutat_list_node = NULL;
        //         head_zutat_list_node = NULL;
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File (kohlesaeure_mode == 0 && aktuelleZutat->kohlesaeure == 1)
    if (nr == 8)
    {
        nextion_change_page(POSANZEIGE);
        nextion_setText("zubabfrage", "Bitte extern einsetzen.");
    }


    // Falls innerhalb des Listenbereichs ==> Flüssigkeit aus File laden
    if (nr < 6)
    {
        nextion_change_page(POSANZEIGE);
        // Wähle Zutaten-File, auf welches gedrückt wurde und lese es ein.
        file_node_t * tmp = actual_list_node_zutaten->_file;

        for (uint8_t i = 0 ; i < nr ; i++)
        {
            tmp = tmp->next;
        }
        aktuelles_Zutat_file_in_Maschine_ohne_KS = tmp;
        lese_textfile_in_zutat(aktuelles_Zutat_file_in_Maschine_ohne_KS->file);

        Uart_Transmit_IT_PC(aktuelle_zutat->name);
        Uart_Transmit_IT_PC("\r");

        strcpy(aktuelle_Zutat_in_Maschine_ohne_KS->name, aktuelle_zutat->name);
        aktuelle_Zutat_in_Maschine_ohne_KS->status = status;
        aktuelle_Zutat_in_Maschine_ohne_KS->alkohol = aktuelle_zutat->alkohol;
        aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure = aktuelle_zutat->kohlensaeure;
        // Schreibe Änderung in Titel der Positionsanzeige
        strcpy((char *)buff, "Nr.");
        itoa(aktuelle_Zutat_in_Maschine_ohne_KS->stelle+1, buff2, 10);
        strcat((char *)buff, (const char *)buff2);
        strcat((char *)buff, " = ");
        strcat((char *)buff, aktuelle_Zutat_in_Maschine_ohne_KS->name);
        nextion_setText("zubabfrage",buff);
    }



    // Setze Status der Zahlen
    setze_Posanzeige_Rot_Gruen();
    delete_file_node_alle(ZUTAT_OHNE);
    asm("nop");
    // Initialisieren Listen-Variabeln
    block_list_hoch = 0;
    block_list_runter = 0;

    // Aktualisieren des Maschinen-Files
    char buff98[20] = {'\0'};
    strcpy((char *)buff98, (const char *)"M.txt");
    ffrm((unsigned char *)buff98);
    char buff_file[512] = {'\0'};
    char * ptr = buff_file;

    write_M_file(ptr);

    char buff97[20] = {'\0'};
    strcpy((char *)buff97, (const char *)"M.txt");
    writeFile((unsigned char *)buff97, (unsigned char *)buff_file);

}

void setze_fluessgkeit_in_position_mit(uint8_t nr, uint8_t status)
{
    char buff[5] = {'\0'};
    char buff1[50] = {'\0'};
    char * string_ptr = buff1;
    char * itoa_ptr = buff;
    // Falls nr ausserhalb des Listenbereichs ==> Keine Flüssigkeit
    if (nr == 6)
    {
        // Schreibe Null-Terminator über bestehenden Namen
        strcpy(aktuelle_Zutat_ausser_Maschine_mit_KS->name, "(keine)");
        aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol = 0;
        aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure=0;
        aktuelle_Zutat_ausser_Maschine_mit_KS->status = status;
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File
    if (nr == 7)
    {
        strcpy((char *)aktuelle_Zutat_ausser_Maschine_mit_KS->name, (const char *)aktuelle_zutat->name);
        aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol = aktuelle_zutat->alkohol;
        aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure=aktuelle_zutat->kohlensaeure;
        aktuelle_Zutat_ausser_Maschine_mit_KS->status = status;
    }

    // Falls innerhalb des Listenbereichs ==> Flüssigkeit aus File laden
    if (nr<6 || nr == 8)
    {

        // Wenn nr < 6 ==> Aus Liste
        if (nr<6)
        {
            // Wähle erstes Zutaten-File des aktuellen Listenabschnitts.
            file_node_t * tmp = actual_list_node_zutaten->_file;
            // Shifte zum gedrückten File und lese es ein
            for (uint8_t i = 0 ; i < nr ; i++)
            {
                tmp = tmp->next;
            }
            aktuelles_Zutat_file_ausser_Maschine_mit_KS = tmp;
            lese_textfile_in_zutat(aktuelles_Zutat_file_ausser_Maschine_mit_KS->file);
        }

        // Wenn Nr == 0 ==> Neue Flüssigkeit
        if (nr == 8)
        {
            lese_textfile_in_zutat(tail_zutat_file_mit->file);
        }

        // Vergleiche, ob Filename bereits in der Liste ist
        uint8_t run = 1;
        // Beginne bei erster Zutat ausserhalb der Maschine
        zutat_maschine_node_t * tmp = head_zutat_maschine_mit;
        do
        {
            if (tmp->status == 1)
            {
                if (strcmp(tmp->name, aktuelle_zutat->name)==0)
                {
                    strcpy(string_ptr, tmp->name);
                    strcat(string_ptr, " entfernt.");
                    nextion_setText("fluessbfrage", string_ptr);
                    nextion_setText("zubabfrage", string_ptr);

                    strcpy(tmp->name, "(keine)");
                    tmp->status=0;
                    tmp->alkohol = 0;
                    tmp->kohlensaeure = 0;

                    run = 0;

                    itoa((nr + 1),itoa_ptr,10);
                    strcpy(string_ptr, "fluessigkeit");
                    strcat(string_ptr, itoa_ptr);

                    strcat(string_ptr, (const char *)".pco=0");
                    Uart_Transmit_IT_Display(string_ptr);
                    endConversation();
                }
            }
            tmp = tmp->next;
        } while (tmp != head_zutat_maschine_mit && run ==1);

        if (run == 1)
        {
            tmp = head_zutat_maschine_mit;
            do
            {
                if (tmp->status == 0)
                {
                    strcpy(tmp->name, aktuelle_zutat->name);
                    tmp->status=1;
                    tmp->alkohol = aktuelle_zutat->alkohol;
                    tmp->kohlensaeure = aktuelle_zutat->kohlensaeure;
                    strcpy(string_ptr, tmp->name);
                    strcat(string_ptr, " hinzugefügt.");
                    nextion_setText("fluessbfrage", string_ptr);
                    nextion_setText("zubabfrage", string_ptr);
                    run = 0;
                    itoa((nr + 1),itoa_ptr,10);
                    strcpy(string_ptr, "fluessigkeit");
                    strcat(string_ptr, itoa_ptr);

                    strcat(string_ptr, (const char *)".pco=2016");
                    Uart_Transmit_IT_Display(string_ptr);
                    endConversation();
                }
                else
                {
                    tmp = tmp->next;
                }
            } while (tmp != head_zutat_maschine_mit && run == 1);

            if (run == 1)
            {
                nextion_setText("fluessbfrage","Kei Platz...\r");
                nextion_setText("zubabfrage","Kei Platz...\r");
            }
        }
    }

    // Aktualisieren des Maschinen-Files
    char buff98[20] = {'\0'};
    strcpy((char *)buff98, (const char *)"M.txt");
//     deleteFile((unsigned char *)buff98);
    char buff_file[512] = {'\0'};
    char * ptr = buff_file;

    write_M_file(ptr);

    char buff97[20] = {'\0'};
    strcpy((char *)buff97, (const char *)"M.txt");
//     writeFile((unsigned char *)buff97, (unsigned char *)buff_file);
}

void setze_standardeinstellungen(void)
{

    nextion_change_page(RFIDFEHLER);
    nextion_setText("fehlertxt","Stelle Maschine auf den Kopf");
    // Debug
    char name[2] = {'\0'};

    // EEPROM-Beginn Standards
    address_Standardwiederherstellung = 0;

    // Iterationsvariable String
    uint16_t kk = 0;

    // Speicher für String
    char buff_string[512] = {'\0'};

    // Lese Byte-für-Byte aus EEPROM (M.txt file "Backup", Standardeinstellung)
    do
    {
        buff_string[kk] = eeprom_read_byte(address_Standardwiederherstellung+kk);
        name[0] = buff_string[kk];
        Uart_Transmit_IT_PC((char *)name);
    } while(buff_string[kk++] != '~');

    // Lösche altes M.txt-file
    char buff5[20] = {'\0'};                            // Buffer für Filename "M.txt"
    strcpy((char *)buff5, (const char *)"M.txt");
//     deleteFile((unsigned char *)buff5);

    // Schreibe neues M.txt-file
    strcpy((char *)buff5, (const char *)"M.txt");
//     writeFile((unsigned char *)buff5, (unsigned char *)buff_string);

    char delimiter[] = ",\r\n";                         // Trennungszeichen definieren              (strtok)
    char *ptr;                                          // Pointer für Abschnitte initialisieren   (strtok)

    // Beschreibe die Maschinenzutaten gemäss Backup M.txt
    zutat_maschine_node_t * tmp = head_zutat_maschine_ohne;
    uint8_t run = 0;
    do
    {
        if (run)
        {
            ptr = strtok(NULL, delimiter);                        // Abschnitt Name Zutat
        } else
        {
            ptr = strtok((char *)buff_string, delimiter);                            // Abschnitt Name Zutat
            run = 1;
        }
        strcpy(tmp->name,ptr);                      // Kopiere Name in Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        tmp->status = atoi(ptr);                    // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        tmp->alkohol = atoi(ptr);                   // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
        tmp->kohlensaeure = atoi(ptr);              // Schreibe ASCI-JA//Nein in Integer-Buffer

        tmp = tmp->next;
    } while(tmp != tail_zutat_maschine_ohne);

    ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein

    // Beschreibe die Maschinenzutaten gemäss Backup M.txt
    tmp = head_zutat_maschine_mit;
    do
    {
        ptr = strtok(NULL, delimiter);                        // Abschnitt Name Zutat
        strcpy(tmp->name,ptr);                      // Kopiere Name in Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        Uart_Transmit_IT_PC(ptr);
        tmp->status = atoi(ptr);                    // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        tmp->alkohol = atoi(ptr);                   // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
        tmp->kohlensaeure = atoi(ptr);              // Schreibe ASCI-JA//Nein in Integer-Buffer

        tmp = tmp->next;
    } while(tmp != tail_zutat_maschine_mit);

    // Erstelle Getränkeliste neu mit gebackupten Maschinenzutaten
    renew_list();

    // Erstelle Startanzeige
    nextion_change_page(STARTANZEIGE);
    actual_getraenk_file_alle = head_getraenk_file_alle;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
    setze_startanzeige(aktuellesGetraenk);
}

void renew_list(void)
{
    uint8_t first = 1;

    // Informiere User über Zustand
    nextion_change_page(RFIDFEHLER);
    nextion_setText("fehlertxt", "Mixe neue Cocktailliste.\\rVerhalten Sie sich ruhig, \\rgleich können Sie auswählen.");

    // Getränke-Liste löschen
    delete_file_node_alle(COCKTAIL);

    // Getränke-Liste anhand neuer Zutaten evaluieren und generieren
    for (int8_t count = 1 ; count <= COUNT_UNTIL; count++)
    {
        char buff[15] = {'\0'};
        itoa(count, (char *)buff,10);
        strcat((char *)buff, (const char *)".txt");
        if(MMC_FILE_OPENED == ffopen((uint8_t *)buff,'r'))
        {
            if(check_existence(count))
            {
                if (first==1)
                {
                    update(1, count, number_getraenk_alle, &head_getraenk_file_alle, &tail_getraenk_file_alle);

                    first = 0;
                }
                else
                {
                    insert_at_end(count, &number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);
                }
            }
        }
    }
    actual_getraenk_file_alle = head_getraenk_file_alle;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}

void write_M_file(char * buff_file)
{
    char buff99[10] = {'\0'};

    zutat_maschine_node_t * tmp = head_zutat_maschine_ohne;
    do
    {
        strcat((char *)buff_file, (const char *)tmp->name);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)"\r");
        tmp = tmp->next;
    } while (tmp != head_zutat_maschine_ohne);
    strcat((char *)buff_file, (const char *)";\r");

    tmp = head_zutat_maschine_mit;
    do
    {
        strcat((char *)buff_file, (const char *)tmp->name);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(tmp->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        if (tmp != tail_zutat_maschine_mit)
        {
            strcat((char *)buff_file, (const char *)"\r");
        }
        else
        {
            strcat(buff_file, "\r;\r~");
        }
        tmp = tmp->next;
    } while (tmp != head_zutat_maschine_mit);
    Uart_Transmit_IT_PC((char *)buff_file);
    //     Uart_Transmit_IT_PC("\rEEPROM:\r");
    //
    //     uint16_t len = strlen(buff_file);
    //     asm("nop");
    //     address_Standardwiederherstellung = 0;
    //     for (uint16_t xxy = 0 ; xxy <len ; xxy++)
    //     {
    //         eeprom_write_byte(address_Standardwiederherstellung +xxy, *(buff_file+xxy));
    //      uint8_t buff[5] = {'\0'};
    //      buff[0] = eeprom_read_byte(address_Standardwiederherstellung + xxy);
    //      Uart_Transmit_IT_PC((char *)buff);
    //     }
}

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

    ffopen((unsigned char *)buff, 'r');

    // Trennungszeichen definieren, Pointer initialisiern für Abschnitte
    char delimiter[] = ":,{}\r\n";
    char *ptr;
    // initialisieren und ersten Abschnitt erstellen (1. Kopf)

    ptr = strtok((char *)fat.sector, delimiter);

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



//***********************************************//
// Pumpen / Zubereitung
//***********************************************//

void zubereitung_getraenk(uint8_t Menge)
{
    nextion_change_page(ZUBBILDSCHIRM);
    nextion_setText("zufallstxt", "Do stoht denn irgend e Text zum Getränk.");
    _delay_ms(1000);
    fuelle_getraenk(Menge, ramp);
    nextion_change_page(BEREITANZEIGE);
    _delay_ms(2000);
    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}

void debug_message_1(float val, float val2)
{
    char itoa_buff[20] = {'\0'};
    char * itoa_ptr = itoa_buff;
    Uart_Transmit_IT_PC("Name Zutat: ");
    Uart_Transmit_IT_PC(tmp_zut_Maschine_actual->name);
    Uart_Transmit_IT_PC("\rStelle: ");
    itoa(tmp_zut_Maschine_actual->stelle, itoa_ptr, 10);
    Uart_Transmit_IT_PC(itoa_ptr);
    char ftoa_buff[20] = {'\0'};
    char * ftoa_ptr = ftoa_buff;
    Uart_Transmit_IT_PC("\rAktuelle Position: ");
    ftoa(val, ftoa_ptr, 4);
    Uart_Transmit_IT_PC(ftoa_ptr);
    Uart_Transmit_IT_PC(")\r");
    char ftoa_buff_2[20] = {'\0'};
    char * ftoa_ptr_2 = ftoa_buff_2;
    Uart_Transmit_IT_PC("Zielposition: ");
    ftoa(val2, ftoa_ptr_2, 4);
    Uart_Transmit_IT_PC(ftoa_ptr_2);
    Uart_Transmit_IT_PC("\r");
}

void debug_message_2()
{
    char itoa_buff[20] = {'\0'};
    char * itoa_ptr = itoa_buff;
    Uart_Transmit_IT_PC("Stelle: ");
    itoa(tmp_zut_Maschine_actual->stelle, itoa_ptr, 10);
    Uart_Transmit_IT_PC(itoa_ptr);
    Uart_Transmit_IT_PC(" erreicht. (");

    char ftoa_buff_3[20] = {'\0'};
    char * ftoa_ptr_3 = ftoa_buff_3;
    float val = (float)tmc4671_getActualPosition(0)/1000;
    ftoa(val, ftoa_ptr_3, 4);
    Uart_Transmit_IT_PC(ftoa_ptr_3);
    Uart_Transmit_IT_PC(")\r\r");
}

void check_stop()
{
    if (stop == 1)
    {
        ramp->ramp_enable = 0;
        for (int k = 0 ; k < 12 ; k++)
        {
            schalte_pumpe_aus(k);
        }
    }
}

void wait_until_position_reached(linear_ramp_t *ramp)
{
    while (ramp->ramp_enable ==1 && stop == 0)
    {
        computeRamp(ramp);
        if (check_Communication_Input_UART_1())             // Check UART_1 (Nextion-Display), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
        {
            proceed_Communication_INPUT_UART_1();               // Vollständige Übertragung des Displays verarbeiten
            check_stop();
        }
    }
}


uint32_t * set_prp(uint32_t * prp, uint8_t fuellmenge)
{
    uint32_t pulse_prp_3dl[13] = {499, 496, 499, 499, 499, 496, 500, 500, 496, 499, 502, 501}; //3dl
    uint32_t pulse_prp_5dl[13] = {501, 500, 501, 500, 502, 500, 500, 502, 498, 501, 503, 506}; //5dl
    uint32_t pulse_prp_1dl[13] = {477, 474, 483, 479, 486, 474, 479, 483, 474, 466, 477, 479}; //1dl

    for (uint8_t count = 0 ; count < 12 ; count++)
    {
        switch (fuellmenge)
        {
        case DL_1:
            prp[count] = pulse_prp_1dl[count];
            break;
        case DL_3:
            prp[count] = pulse_prp_3dl[count];
            break;
        case DL_5:
            prp[count] = pulse_prp_5dl[count];
            break;
        }
    }
    return prp;
}

void fuelle_getraenk(uint32_t fuellmenge, linear_ramp_t *ramp)
{
    // Geschwindigkeit und Beschleunigung während Zubereitung
    uint32_t geschwindigkeit = 100;
    uint32_t beschleunigung = 100;

    // Variabeln Positionsberechnung
    float ende_der_bahn = ramp->motor_umdrehungen_komplette_verschiebung * ramp->motor_faktor_eine_umdrehung;
    float position_der_pumpe;
    float val;
    float val2;

    // Variabeln Pumpenskalierung
    uint32_t pulse_prp[12] = {'\0'};
    uint32_t * ptr = pulse_prp;

    // Setzen Pumpenskalierung
    ptr = set_prp(ptr, fuellmenge);

    tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION,              0x00000003);        // writing value 0x00000003 = 3 = 0.0 to address 67 = 0x63(MODE_RAMP_MODE_MOTION)
    tmc4671_switchToMotionMode(0, TMC4671_MOTION_MODE_POSITION);

    // Aktueller Standort ist Beginn
    tmc4671_setActualPosition(0,0);

    // Iterationsbeginn am Kopf
    tmp_zut_Maschine_actual = head_zutat_maschine_ohne;

    stop = 0;

    // Switche durch alle Zutaten während stop == 0
    do
    {
        // Falls die Zutat vorkommt
        if (tmp_zut_Maschine_actual->menge > 0)
        {


            // Lese aktuelle Position Schlitten aus
            val = (float)tmc4671_getActualPosition(0)/1000;



            // Berechne Position der Pumpe
            position_der_pumpe = tmp_zut_Maschine_actual->stelle * ramp->motor_faktor_eine_umdrehung * ramp->motor_umdrehungen_teilverschiebung;
            val2 =  ende_der_bahn - position_der_pumpe;
            /*
                         debug_message_1(val, val2);
            */


            // Fahre an berechnete Position
            calculateRamp(beschleunigung, geschwindigkeit, val, val2, ramp);
            wait_until_position_reached(ramp);
            /*
            //          debug_message_2();
            */


            if (stop == 0)
            {


                // Berechne Menge, Ermittle momentanen Sensorwert, schalte Pumpe ein
                uint32_t Menge = (((uint32_t)fuellmenge * (uint32_t)pulse_prp[tmp_zut_Maschine_actual->stelle]) * (uint32_t)(tmp_zut_Maschine_actual->menge)/(uint16_t)100);
                uint8_t fuellen = 1;
                uint8_t newval = lese_sensor(tmp_zut_Maschine_actual->stelle);
                schalte_pumpe_ein(tmp_zut_Maschine_actual->stelle);

                // Während dem Füllvorgang
                while (fuellen)
                {
                    // Polle PWM-Signal des Durchflusssensor
                    static uint8_t oldval=0;
                    static uint32_t count=0;





                    newval = oldval ^ 0b00000001;




//                  newval = lese_sensor(i);






                    // Falls ein Flankenwechsel stattgefunden hat, zähle hoch
                    if( !oldval && newval)
                    {
                        // Falls erwünschte Menge erreicht wurde, breche aus Schleife aus und setze Zähler zurück
                        if(count++ > Menge)
                        {
                            schalte_pumpe_aus(tmp_zut_Maschine_actual->stelle);
                            count = 0;
                            fuellen = 0;
                        }





//                  Delay entfernen wenn mit Sensor gearbeitet wird.
                        _delay_ms(1);



                        // Check Display-Kommunikation für möglichen Abbruch
                        if (check_Communication_Input_UART_1())
                        {
                            proceed_Communication_INPUT_UART_1();
                            check_stop();
                        }
                    }
                    // Aktueller Sensorwert speichern
                    oldval = newval;
                }
            }
        }
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
    } while(tmp_zut_Maschine_actual != head_zutat_maschine_ohne && stop == 0);

    val = (float)tmc4671_getActualPosition(0)/1000;

    if (stop == 1)
    {
        stop = 0;
        nextion_change_page(ABBRUCHANZEIGE);
        calculateRamp(100, 100, tmc4671_getActualPosition(0), 0, ramp);
        wait_until_position_reached(ramp);


// Switch to torque mode
        tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000001);

//Stop
        tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0x00000000);

        lese_textfile_in_getraenk(head_getraenk_file_alle->file);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        stop = 0;
    }
    else
    {
        /*
           Fahre zurück
        */

        calculateRamp(beschleunigung, geschwindigkeit, val, 0, ramp);
        wait_until_position_reached(ramp);

        char string[256] = {'\0'};
        char * string_ptr = string;
        uint8_t externes_Getraenk_flag = 0;

        strcpy(string_ptr, "Zutaten von Hand einfüllen:\\r");
        tmp_zut_Maschine_actual = head_zutat_maschine_mit;
        do
        {
            if (tmp_zut_Maschine_actual->menge > 0)
            {
                strcat(string_ptr, tmp_zut_Maschine_actual->name);
                strcat(string_ptr, ": ");
                float val = (float)tmp_zut_Maschine_actual->menge * (float)fuellmenge / (float)100;
                char itoa_buff[10] = {'\0'};
                char * itoa_ptr = itoa_buff;
                ftoa(val, itoa_ptr, 1);
                strcat(string_ptr, itoa_ptr);
                strcat(string_ptr, "dl\\r");
                externes_Getraenk_flag = 1;
            }
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
        } while (tmp_zut_Maschine_actual != head_zutat_maschine_mit);
        if (externes_Getraenk_flag == 1)
        {
            nextion_change_page(INFOANZEIGE);
            nextion_setText("infotxt", string_ptr);
            _delay_ms(5000);
        }

    }


}

void schalte_pumpe_ein(uint8_t Pumpe)
{
    switch (Pumpe)
    {
    case 0:
        PUMPE0_PORT|=PUMPE0_BIT;
        break;
    case 1:
        PUMPE1_PORT|=PUMPE1_BIT;
        break;
    case 2:
        PUMPE2_PORT|=PUMPE2_BIT;
        break;
    case 3:
        PUMPE3_PORT|=PUMPE3_BIT;
        break;
    case 4:
        PUMPE4_PORT|=PUMPE4_BIT;
        break;
    case 5:
        PUMPE5_PORT|=PUMPE5_BIT;
        break;
    case 6:
        PUMPE6_PORT|=PUMPE6_BIT;
        break;
    case 7:
        PUMPE7_PORT|=PUMPE7_BIT;
        break;
    case 8:
        PUMPE8_PORT|=PUMPE8_BIT;
        break;
    case 9:
        PUMPE9_PORT|=PUMPE9_BIT;
        break;
    case 10:
        PUMPE10_PORT|=PUMPE10_BIT;
        break;
    case 11:
        PUMPE11_PORT|=PUMPE11_BIT;
        break;
    }
}

void schalte_pumpe_aus(uint8_t Pumpe)
{
    switch (Pumpe)
    {
    case 0:
        PUMPE0_PORT &= ~PUMPE0_BIT;
        break;
    case 1:
        PUMPE1_PORT &= ~PUMPE1_BIT;
        break;
    case 2:
        PUMPE2_PORT &= ~PUMPE2_BIT;
        break;
    case 3:
        PUMPE3_PORT &= ~PUMPE3_BIT;
        break;
    case 4:
        PUMPE4_PORT &= ~PUMPE4_BIT;
        break;
    case 5:
        PUMPE5_PORT &= ~PUMPE5_BIT;
        break;
    case 6:
        PUMPE6_PORT &= ~PUMPE6_BIT;
        break;
    case 7:
        PUMPE7_PORT &= ~PUMPE7_BIT;
        break;
    case 8:
        PUMPE8_PORT &= ~PUMPE8_BIT;
        break;
    case 9:
        PUMPE9_PORT &= ~PUMPE9_BIT;
        break;
    case 10:
        PUMPE10_PORT &= ~PUMPE10_BIT;
        break;
    case 11:
        PUMPE11_PORT &= ~PUMPE11_BIT;
        break;
    }
}

uint8_t lese_sensor(uint8_t Sensor)
{
    uint8_t val = 0;

    switch (Sensor)
    {
    case 0:
        val = FLUSS0_PIN & FLUSS0_BIT;
        break;
    case 1:
        val = FLUSS1_PIN & FLUSS1_BIT;
        break;
    case 2:
        val = FLUSS2_PIN & FLUSS2_BIT;
        break;
    case 3:
        val = FLUSS3_PIN & FLUSS3_BIT;
        break;
    case 4:
        val = FLUSS4_PIN & FLUSS4_BIT;
        break;
    case 5:
        val = FLUSS5_PIN & FLUSS5_BIT;
        break;
    case 6:
        val = FLUSS6_PIN & FLUSS6_BIT;
        break;
    case 7:
        val = FLUSS7_PIN & FLUSS7_BIT;
        break;
    case 8:
        val = FLUSS8_PIN & FLUSS8_BIT;
        break;
    case 9:
        val = FLUSS9_PIN & FLUSS9_BIT;
        break;
    case 10:
        val = FLUSS10_PIN & FLUSS10_BIT;
        break;
    case 11:
        val = FLUSS11_PIN & FLUSS11_BIT;
        break;
    }
    return val;
}



//***********************************************//
// Cocktails bearbeiten / Erstellen
//***********************************************//

void schreibe_Menge_in_Getraenk(uint8_t zutat)
{
    zutat_maschine_node_t * tmp_zut_Maschine_actual_2 = actual_list_node_zutat_maschine->zutat_maschine;
    for (int count = 0 ; count < zutat; count++)
    {
        tmp_zut_Maschine_actual_2 = tmp_zut_Maschine_actual_2->next;
    }

    concentrace_zutat_maschine_list();

    nextion_setText("t0", "");
    uint8_t val = 0;
    char buff[15] = {0};
    char buff2[5];
    char buff3[5];

    uint8_t totval = 0;
    uint8_t restval = 0;

    // Alle Werte aus den anderen Mengen holen
    tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
    do
    {
        totval += tmp_zut_Maschine_actual->menge;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

    restval = 100 - (totval - tmp_zut_Maschine_actual_2->menge);

    // String, um Slider auszuwählen
    strcpy((char *)buff, (const char *)"slider");
    itoa((zutat + 1), (char *)buff2, 10);
    strcat((char *)buff, (const char *)buff2);

    // Wert aus Slider holen und in Getränkeliste eintragen
    val = nextion_getSliderValue(buff, (unsigned char *)INPUT_UART_1);
    val -= (val % 5);
    if (val > restval)
    {
        val = restval;
        nextion_setText("t0", "Schon 100% erreicht");
    }

    tmp_zut_Maschine_actual_2->menge = val;

    // String um Text zu Setzen
    itoa((int)val, (char *)buff2, 10);
    strcat((char *)buff2, "%");


    // String um Textfeld auszuwählen
    strcpy((char *)buff, (const char *)"menge");
    itoa((zutat+1), (char *) buff3, 10);
    strcat((char *)buff, (const char *)buff3);

    // Text schreiben
    nextion_setText(buff,buff2);

    // String um Text zu Setzen
    itoa((int)val, (char *)buff2, 10);

    // String um Textfeld auszuwählen
    strcpy((char *)buff, (const char *)"slider");
    itoa((zutat +1), (char *) buff3, 10);
    strcat((char *)buff, (const char *)buff3);

    // Text schreiben
    nextion_setValue(buff,buff2);
    _delay_ms(2);

    deconcentrace_zutat_maschine_list();
}

void prepare_empty_getraenk(void)
{
    concentrace_zutat_maschine_list();
    tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
    do
    {
        tmp_zut_Maschine_actual->menge = 0;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

    deconcentrace_zutat_maschine_list();

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
}

void speichere_neuen_cocktail(void)
{
    // Aneinanderreihen zweier Listen
    uint8_t val = 0;

    concentrace_zutat_maschine_list();

    tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
    do
    {
        val += tmp_zut_Maschine_actual->menge;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

    if (val == 100)
    {

        nextion_change_page(RFIDFEHLER);
        nextion_setText("fehlertxt", "Wird gespeichert...");
        strcpy(aktuellesGetraenk->name, (const char *)buff_name);
        aktuellesGetraenk->picture = 32;

        uint8_t alkohol = 0;
        uint8_t kohlensaeure = 0;

        tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
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
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
        } while (tmp_zut_Maschine_actual!= tmp_zut_Maschine_head);
        aktuellesGetraenk->alkohol = alkohol;

        deconcentrace_zutat_maschine_list();

        uint8_t run = 1;
        // Suche von 1 bis 100 durch die Files
        for (int8_t count = 1 ; count < COUNT_UNTIL; count++) {

            // Text erstellen, um File-Nr. zu suchen.
            char buff[15] = {'\0'};
            itoa(count, (char *)buff,10);
            strcat((char *)buff, (const char *)".txt");

            // Erstes nicht existierendes File suchen
            if(verifyFile((uint8_t*)buff)!=1)
            {
                // File speichern
                erstelle_File(count, buff_name, alkohol, kohlensaeure);
                insert_at_end(count, &number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);
                count = 100;
                actual_getraenk_file_alle = tail_getraenk_file_alle;
                run = 0;
            }
        }
        if (run == 1)
        {
            nextion_setText("fehlertxt", "Zuerst Cocktails löschen, \\rkein Platz mehr.");
            _delay_ms(5000);
            actual_getraenk_file_alle = head_getraenk_file_alle;
        }
        else
        {
            actual_getraenk_file_alle = tail_getraenk_file_alle;
        }
        lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);

        block_list_hoch = 0;
        block_list_runter = 0;
        delete_list_node_zutat_maschine();
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
}

void speichere_bearbeiteten_cocktail(void)
{
    uint8_t val = 0;

    concentrace_zutat_maschine_list();

    tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
    do
    {
        val += tmp_zut_Maschine_actual->menge;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

    deconcentrace_zutat_maschine_list();

    if (val == 100)
    {
        block_list_hoch = 0;
        block_list_runter = 0;
        nextion_change_page(RFIDFEHLER);
        nextion_setText("fehlertxt", "Wird gespeichert...");
        loesche_FIle(actual_getraenk_file_alle->file);
        erstelle_File(actual_getraenk_file_alle->file, aktuellesGetraenk->name, aktuellesGetraenk->alkohol, aktuellesGetraenk->kohlensaeure);
        nextion_change_page(STARTANZEIGE);
        setze_startanzeige(aktuellesGetraenk);
        delete_list_node_files(COCKTAIL);
        delete_list_node_zutat_maschine();
    }
    else
    {
        nextion_setText("t0", "Noch nicht 100% ausgewählt.");
    }
}

void bearbeite_Cocktail(uint8_t cocktail)
{
    char buff[21] = {'\0'};

    // Wähle geklickten Cocktail aus und schreibe ihn von SD in physikalischen Speicher
    file_node_t * tmp = actual_list_node_getraenk->_file;
    for (uint8_t cnt = 0 ; cnt < cocktail; cnt++)
    {
        tmp = tmp->next;
    }
    actual_getraenk_file_alle = tmp;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);

    // Neue Liste beginnt == Blockierung aufheben
    block_list_hoch = 0;
    block_list_runter = 0;

    // Erstelle erste Anzeige und update Liste
    begin_erstelle_liste_alle_zutaten(CEINSTANZEIGE, "zutat");
    strcpy((char *)buff, aktuellesGetraenk->name);
    strcat((char *)buff, " anpassen");
    nextion_setText("bearbtext", (char *)buff);
}



//***********************************************//
// RFID
//***********************************************//

void schreibe_Getraenk_in_tag(uint8_t nr)
{
    char itoa_buff[5] = {'\0'};
    char * itoa_ptr = itoa_buff;
    char buffer[128] = {'\0'};
    char * ptr = buffer;

    actual_getraenk_file_alle = actual_list_node_getraenk->_file;
    for(uint8_t count = 0 ; count < nr ; count++)
    {
        actual_getraenk_file_alle = actual_getraenk_file_alle->next;
    }
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);


    strcat(ptr, "tagzuweisungup:");
    itoa(aktueller_tag->tag_nummer+1, itoa_buff, 10);
    strcat(ptr, itoa_buff);
    strcat(ptr, ":");
    strcat(ptr, aktuellesGetraenk->name);
    Uart_Transmit_IT_ESP(ptr);
    Uart_Transmit_IT_PC(ptr);


    strcpy((char *)aktueller_tag->cocktail_name, (const char *)aktuellesGetraenk->name);

    nextion_change_page(RFIDFEHLER);

    strcpy(ptr, "Tag-Nr.");
    itoa(aktueller_tag->tag_nummer, itoa_ptr, 10);
    strcat(ptr, itoa_ptr);
    strcat(ptr, " wurde\r");
    strcat(ptr, aktueller_tag->cocktail_name);
    strcat(ptr, "\rzugeordnet. :)");
    nextion_setText("fehlertxt",ptr);
    _delay_ms(2000);

    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
    delete_list_node_files(COCKTAIL);
}



//***********************************************//
// Display
//***********************************************//

void setze_startanzeige(getraenk_t * anzeige_getraenk)
{
    char buff[4];
    if (aktuellesGetraenk->picture >= 32)
    {
        nextion_visible_on("loeschen");
    }
    else
    {
        nextion_visible_off("loeschen");
    }
    nextion_setText("cocktailname",anzeige_getraenk->name);
    itoa(anzeige_getraenk->picture,(char *)buff,10);
    nextion_setPicture("235","80",(char *)buff);
    switch(Liste)
    {
    case ALLE:
        nextion_setText("alkoholjanein", "Alkoholisch");
        break;

    case ALKOHOL:
        nextion_setText("alkoholjanein", "Alkoholfrei");
        break;

    case ALKOHOLFREI:
        nextion_setText("alkoholjanein", "Alle");
        break;
    }
}

void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk)
{

    concentrace_zutat_maschine_list();

//                  - Erstelle lokale Variable für itoa-Buffer
//                  - Erstelle lokale Variable für Stringkette
//                  - Erstelle lokale Variable für Zutaten
//
//                  - für 0 ... Anzahl Getränke
//                  - Wenn die Menge des aktuellen Getränkes > 0
//                  - Hänge Zutat an Kette
//                  - Hänge Zeilenumbruch an Kette
//                  - Switche zur nächsten Zutat
//
//                  - Schreibe Zutatenkette in Textfeld
    char string[512] = {'\0'};
    char buff[10] = {'\0'};
    char * ftoa_ptr = buff;
    uint8_t first = 1;
    float val;
    float val2;
    tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
    char * string_ptr = string;
    do
    {
        if (tmp_zut_Maschine_actual->menge > (uint8_t)0)
        {

            if ( first == 1)
            {
                val = (((float)ceil(tmp_zut_Maschine_actual->menge * 3 / 10)) + (float)1)/(float)10 + 0.1;
                val2 = (((float)ceil(tmp_zut_Maschine_actual->menge * 5 / 10)) + (float)1)/(float)10 ;
                first = 0;
            }
            else
            {
                val = (float)round(tmp_zut_Maschine_actual->menge * 3 / 10)/(float)10;
                val2 = (float)round(tmp_zut_Maschine_actual->menge * 5 / 10)/(float)10;
            }
            if (val < 1)
            {
                strcat(string_ptr, "0");
            }


            ftoa(val, ftoa_ptr, 1);
            strcat(string_ptr, ftoa_ptr);
            strcat(string_ptr, "dl / ");
            if (val2 < 1)
            {
                strcat(string_ptr, "0");
            }
            ftoa(val2, ftoa_ptr, 1);
            strcat(string_ptr, ftoa_ptr);
            strcat(string_ptr, "dl");

            for (int count2 = 0 ; count2<5 ; count2++)
            {
                strcat(string_ptr, "-");
            }
            strcat(string_ptr, tmp_zut_Maschine_actual->name);
            strcat(string_ptr, "\\r");

        }
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);
    nextion_setText("zutatenliste",string_ptr);
    deconcentrace_zutat_maschine_list();
}


void schiebe_file_next(void)
{
    actual_getraenk_file_alle = actual_getraenk_file_alle->next;
    char buff[50] = {'\0'};
    itoa(actual_getraenk_file_alle->file, (char *) buff, 10);
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
}

void schiebe_file_prev(void)
{
    actual_getraenk_file_alle = actual_getraenk_file_alle->prev;
    char buff[50] = {'\0'};
    itoa(actual_getraenk_file_alle->file, (char *) buff, 10);
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
}


void setze_Posanzeige_Rot_Gruen(void)
{
    zutat_maschine_node_t * tmp = head_zutat_maschine_ohne;
    char buff[50];
    char buff2[10];
    for (int i = 0 ; i <12 ; i++)
    {
        strcpy((char *)buff, "b");
        itoa(i,(char *) buff2, 10);
        strcat((char *)buff, (const char *)buff2);
        switch (tmp->status)
        {
        case 0:
            strcat((char *)buff, ".pco=0");
            break;
        case 1:
            strcat((char *)buff, ".pco=2016");
            break;
        case 2:
            strcat((char *)buff, ".pco=63488");
            break;
        }
        Uart_Transmit_IT_Display((char *)buff);
        endConversation();
        tmp = tmp->next;
    }
}



//***********************************************//
// SD-Karte
//***********************************************//

void lese_textfile_in_getraenk(uint8_t file)
{
// Aneinanderreihen zweier Listen

// Pointer Beginn/Anfang/Aktuell/Return-(zutat_maschine_node_t)
//     zutat_maschine_node_t * tmp_zut_Maschine_tail;
    zutat_maschine_node_t * tmp_zut_Maschine_head;
    zutat_maschine_node_t * tmp_zut_Maschine_actual;

// Speichern der Momentanen Pointer.
    zutat_maschine_node_t * tmp_ohne_KS_head = head_zutat_maschine_ohne->prev;
    zutat_maschine_node_t * tmp_mit_KS_head = head_zutat_maschine_mit->prev;
    zutat_maschine_node_t * tmp_ohne_KS_tail = tail_zutat_maschine_ohne->next;
    zutat_maschine_node_t * tmp_mit_KS_tail = tail_zutat_maschine_mit->next;

// Anfang und Ende der gesamten Liste
//     tmp_zut_Maschine_tail = tail_zutat_maschine_ohne;
    tmp_zut_Maschine_head = head_zutat_maschine_ohne;

// Äussere Verbindungen
    tail_zutat_maschine_ohne->next = head_zutat_maschine_mit;
    head_zutat_maschine_mit->prev = tail_zutat_maschine_ohne;

// Innere Verbindungen
    tail_zutat_maschine_mit->next = head_zutat_maschine_ohne;
    head_zutat_maschine_ohne->prev = tail_zutat_maschine_mit;

//     head_zutat_maschine_ohne->prev = tmp_ohne_KS_head;
//     tail_zutat_maschine_ohne->next = tmp_ohne_KS_tail;
//     tail_zutat_maschine_mit->next = tmp_mit_KS_tail;
//     head_zutat_maschine_mit->prev = tmp_mit_KS_head;

    // Erstellen eines Strings in Form von: "file.txt"
    char buff[50];
    itoa((int)file,(char *)buff,10);
    char * txt = ".txt";
    strcat((char *)buff,txt);

    // "file.txt" lesen (File wird in char buffer[512] geschrieben)
    //return: 0, if normal operation or flag is READ
    //        1, if file is already existing and flag = VERIFY
    //        2, if file name is incompatible

    readFile((uint8_t *)buff);

    // Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
    char delimiter[] = ":\r\n";
    char *ptr;
    // initialisieren und ersten Abschnitt erstellen (1. Kopf)

    ptr = strtok((char *)fat.sector, delimiter);
	
    //  Abschnitt in buffer extrahieren:
    /*
        Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
        ********************************************************************
        Name:Getraenk 1
        Mengen:{0,0,0,0,0,0,0,0,0,0}
        Alkohol:1
        Bild:2
    */
    while(ptr != NULL) {
        // Kopf pr?fen und jeweilige Aktion ausf?hren
        if (strcmp(ptr, "Name")==0)
        {
            ptr = strtok(NULL, delimiter);
            strcpy(aktuellesGetraenk->name,ptr);
        }

        if (strcmp(ptr, "Mengen")==0)
        {
            ptr = strtok(NULL, delimiter);

            tmp_zut_Maschine_actual = tmp_zut_Maschine_head;

            do
            {
                tmp_zut_Maschine_actual->menge = (uint8_t) 0;
                tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;

            } while(tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

            // Suche Zutaten im File
            while(*ptr != ';')
            {
                tmp_zut_Maschine_actual = tmp_zut_Maschine_head;

                // Suche nach richtiger Position der Zutat in der Maschine
                do
                {
                    // Vergleiche dafür den Namen der Zutat im File mit dem Namen der Zutat in der Maschine
                    if(strcmp((char *)ptr, (char *)tmp_zut_Maschine_actual->name) == 0)
                    {
                        ptr = strtok(NULL, delimiter);

                        // Und schreibe Wert in die richtige Position
                        tmp_zut_Maschine_actual->menge = atoi(ptr);
                        tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
                    }

                    tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
                } while(tmp_zut_Maschine_actual != tmp_zut_Maschine_head);

                ptr = strtok(NULL, delimiter);
            }
        }

        if (strcmp(ptr, "Alkohol")==0)
        {
            ptr = strtok(NULL, delimiter);
            aktuellesGetraenk->alkohol = atoi(ptr);
        }

        if (strcmp(ptr, "Kohlensaeure")==0)
        {
            ptr = strtok(NULL, delimiter);
            aktuellesGetraenk->kohlensaeure = atoi(ptr);
        }

        if (strcmp(ptr, "Bild")==0)
        {
            ptr = strtok(NULL, delimiter);
            (aktuellesGetraenk->picture) = atoi(ptr);
        }

        // Neuer Kopf suchen und ptr darauf zeigen lassen
        ptr = strtok(NULL, delimiter);
    }
    head_zutat_maschine_ohne->prev = tmp_ohne_KS_head;
    tail_zutat_maschine_ohne->next = tmp_ohne_KS_tail;
    tail_zutat_maschine_mit->next = tmp_mit_KS_tail;
    head_zutat_maschine_mit->prev = tmp_mit_KS_head;
}

void lese_textfile_in_zutat(uint8_t file)
{
    char buff_textfiles_zutat[21] = {'\0'};
    char buff2_textfiles_zutat[5] = {'\0'};

    strcpy((char *)buff_textfiles_zutat, (const char *)"Z");
    itoa(file, (char *)buff2_textfiles_zutat, 10);
    strcat((char *)buff_textfiles_zutat, (const char *)buff2_textfiles_zutat);
    strcat((char *)buff_textfiles_zutat, (const char *)".txt");

    readFile((uint8_t *)buff_textfiles_zutat);

    // Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
    char delimiter[] = ":,{}\r\n";
    char *ptr;

    // initialisieren und ersten Abschnitt erstellen (1. Kopf)
    ptr = strtok((char *)fat.sector, delimiter);

    //  Abschnitt in buffer extrahieren:

    /*  Dazu muss im Textfile jeweils in folgendem Format geschrieben werden:
        *******************************************************************
        Name:Getraenk1
        Alkohol:1/0
    */

    while(ptr != NULL)
    {
        // Kopf pruefen und jeweilige Aktion ausfuehren
        if (strcmp(ptr, "Name")==0)
        {
            ptr = strtok(NULL, delimiter);
            strcpy((char *)aktuelle_zutat->name,(const char *)ptr);
        }
        if (strcmp(ptr, "Alkohol")==0)
        {
            ptr = strtok(NULL, delimiter);
            aktuelle_zutat->alkohol = atoi(ptr);
        }

        if (strcmp(ptr, "Kohlensaeure")==0)
        {
            ptr = strtok(NULL, delimiter);
            aktuelle_zutat->kohlensaeure = atoi(ptr);
        }

        // Neuer Kopf suchen und ptr darauf zeigen lassen
        ptr = strtok(NULL, delimiter);
    }
}

void erstelle_File(uint8_t filename, char * name, uint8_t alkohol, uint8_t kohlensaeure)
{

    concentrace_zutat_maschine_list();

    char buff[512] = {0};
    char * ptr = buff;
    strcat(ptr, "Name:");
    strcat(ptr, name);

    strcat(ptr, "\rMengen:\r");
    char buff2[5]  = {0};

    tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
    do
    {
        if (tmp_zut_Maschine_actual->menge > (uint8_t) 0)
        {
            Uart_Transmit_IT_PC(tmp_zut_Maschine_actual->name);
            strcat(ptr,tmp_zut_Maschine_actual->name);
            strcat(ptr, (const char *)":");
            itoa(tmp_zut_Maschine_actual->menge, (char *)buff2, 10);
            strcat(ptr, (const char *)buff2);
            strcat(ptr, (const char *)"\r");
            Uart_Transmit_IT_PC((char *)buff2);
        }
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

    strcat(ptr, ";\r");
    strcat(ptr, "Alkohol:");
    itoa(alkohol, (char *)buff2, 10);
    strcat(ptr, (char *)buff2);
    strcat(ptr, "\r");

    strcat(ptr, "Kohlensaeure:");
    itoa(kohlensaeure, (char *)buff2, 10);
    strcat(ptr, (char *)buff2);
    strcat(ptr, "\r");

    strcat(ptr, "Bild:");
    if (aktuellesGetraenk->picture != 32)
    {
        char buff[5];
        itoa(aktuellesGetraenk->picture,(char *)buff, 10);
        strcat(ptr, (char *)buff);
    }
    else
    {
        strcat(ptr, "32");
    }

    strcat(ptr, "~");

    char buff3[15] = {'\0'};
    itoa(filename, (char *)buff3, 10);
    strcat((char *)buff3, (const char *)".txt");
    writeFile((uint8_t *)buff3,(uint8_t *)ptr);

    deconcentrace_zutat_maschine_list();
}

void loesche_FIle(uint8_t filename)
{
    unsigned char buff[20] = {'\0'};
    itoa(filename, (char *)buff, 10);
    strcat((char *)buff,".txt");
    deleteFile((unsigned char *)buff);
}



//***********************************************//
// ESP
//***********************************************//

void send_List_Getraenke (void)
{
    char buff[512] = {'\0'};
    char * ptr = buff;

    char counter = 0;
    actual_getraenk_file_alle = tail_getraenk_file_alle;

    do
    {
        counter++;
        actual_getraenk_file_alle = actual_getraenk_file_alle->prev;
    } while (actual_getraenk_file_alle != tail_getraenk_file_alle);

    strcat(ptr, "getraenkeliste:");
    char buffer[5] = {'\0'};
    itoa(counter, (char *) buffer, 10);
    strcat(ptr, (char *) buffer);
    strcat(ptr, ":");

    actual_getraenk_file_alle = tail_getraenk_file_alle;

    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);

    strcat(ptr, aktuellesGetraenk->name);
    actual_getraenk_file_alle = actual_getraenk_file_alle->prev;

    for (int cnt = 0 ; cnt < (counter - 1); cnt++)
    {
        strcat(ptr, ",");
        lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
        strcat(ptr, aktuellesGetraenk->name);
        actual_getraenk_file_alle = actual_getraenk_file_alle->prev;
    }
    strcat(ptr,":");
    Uart_Transmit_IT_PC(ptr);
    Uart_Transmit_IT_ESP(ptr);
}

void send_List_Zutaten (void)
{
    char buff[512] = {'\0'};
    char buff2[512] = {'\0'};
    char itoa_buff[10] = {'\0'};
    uint8_t counter = 0;
    char * ptr = buff;
    char * ptr2 = buff2;

    concentrace_zutat_maschine_list();
    tmp_zut_Maschine_actual = head_zutat_maschine_ohne;

    strcpy(ptr2, "zutaten:");
    uint8_t first = 1;
    do
    {
        if (tmp_zut_Maschine_actual->status == 1)
        {
            if (first == 1)
            {
                strcat(ptr, tmp_zut_Maschine_actual->name);
                first = 0;
            }
            else
            {
                strcat(ptr, ",");
                strcat(ptr, tmp_zut_Maschine_actual->name);

            }
            counter ++;
        }
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
    } while (tmp_zut_Maschine_actual != head_zutat_maschine_ohne);
    deconcentrace_zutat_maschine_list();
    itoa(counter, (char *)itoa_buff, 10);
    strcat(ptr2, (char*)itoa_buff);
    strcat(ptr2,":");
    strcat(ptr2, ptr);
    strcat(ptr,":");
    Uart_Transmit_IT_ESP(ptr2);
    Uart_Transmit_IT_PC(ptr2);
}

void ESP_Getraenk(void)
{
    while (check_Communication_Input_UART_2()==0)
        ;
    char buff[256] = {'\0'};
    char * ptr = buff;
    char delimiter[] = ",:\r";

    strcpy(ptr, (const char *)INPUT_UART_2);
    //Name
    ptr = strtok(ptr, delimiter);
    Uart_Transmit_IT_PC("\rCocktail: ");
    Uart_Transmit_IT_PC(ptr);

    actual_getraenk_file_alle = tail_getraenk_file_alle;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);

    while (strcmp(aktuellesGetraenk->name, ptr)!=0)
    {
        actual_getraenk_file_alle = actual_getraenk_file_alle->prev;
        lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
        Uart_Transmit_IT_PC("While\r");
    }
    nextion_change_page(ZUBABFRAGE);
}

void Getraenk_erstellt()
{
    buffer2_getraenk_file_alle = actual_getraenk_file_alle;

    while (check_Communication_Input_UART_2()==0)
        ;
    Uart_Transmit_IT_PC((char *)INPUT_UART_2);
    char buff[256] = {'\0'};
    char string[256] = {'\0'};
    char * ptr = buff;
    char * ptr2 = string;
    char delimiter[] = ",:\r";
    char buff2[20] = {'\0'};
    char temp2[21] = {'\0'};
    char alkohol = 0;
    char kohlensaeure = 0;

    strcpy(buff, (char *)INPUT_UART_2);
    //Name
    ptr = strtok(ptr, delimiter);
    Uart_Transmit_IT_PC("\rName: ");
    Uart_Transmit_IT_PC(ptr);
    strcat(ptr2, "Name:");
    strcat(ptr2, ptr);
    strcat(ptr2, "\rMengen:\r");

    concentrace_zutat_maschine_list();
    uint8_t count = 1;
    do
    {
//         // Zutat 1 Name
//         Uart_Transmit_IT_PC("\rZutat");
//         itoa((count), (char *)buff2, 10);
//         Uart_Transmit_IT_PC(buff2);
//         Uart_Transmit_IT_PC(": ");
//         ptr = strtok(NULL, delimiter);
//         Uart_Transmit_IT_PC(ptr);
        strcpy((char *)temp2, ptr);

        // Zutat 1 Menge
//         Uart_Transmit_IT_PC("\rMenge");
//         itoa((count), (char *)buff2, 10);
//         Uart_Transmit_IT_PC(buff2);
//         Uart_Transmit_IT_PC(": ");
        ptr = strtok(NULL, delimiter);
        if (atoi(ptr)>0)
        {
            tmp_zut_Maschine_actual = tmp_zut_Maschine_head;
            do
            {
                if (strcmp(tmp_zut_Maschine_actual->name, temp2) == 0)
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
                tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->next;
            } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_head);
            strcat(ptr2, (const char *)temp2);
            strcat(ptr2, ":");
            strcat(ptr2, ptr);
            strcat(ptr2, "\r");
        }
        count++;
    } while (count < 12);
    deconcentrace_zutat_maschine_list();

    strcat(ptr2, ";\r");
    strcat(ptr2, "Alkohol:");
    itoa(alkohol, (char *)buff2, 10);
    strcat(ptr2, (char *)buff2);
    strcat(ptr2, "\rKohlensaeure:");
    itoa(kohlensaeure, (char *)buff2, 10);
    strcat(ptr2, (char *)buff2);
    strcat(ptr2, "\rBild:32");
    strcat(ptr2, "~");

    Uart_Transmit_IT_PC(ptr2);

    // Getränke-Liste anhand neuer Zutaten evaluieren und generieren
    for (count = 1 ; count < COUNT_UNTIL; count++)
    {
        char buff[15] = {'\0'};
        itoa(count, (char *)buff,10);
        strcat((char *)buff, (const char *)".txt");
//         if(readFile(VERIFY, (unsigned char *)buff)!=1)
//         {
//             itoa(count, (char *)buff,10);
//             strcat((char *)buff, (const char *)".txt");
//             writeFile((unsigned char *)buff, (unsigned char *)ptr2);
//
//             if(check_existence(count))
//             {
//                 insert_at_end(count, &number_getraenk_alle, &head_getraenk_file_alle, & tail_getraenk_file_alle);
//             }
//             count = COUNT_UNTIL;
//         }
    }
    actual_getraenk_file_alle = buffer2_getraenk_file_alle;
    lese_textfile_in_getraenk(actual_getraenk_file_alle->file);
    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}
