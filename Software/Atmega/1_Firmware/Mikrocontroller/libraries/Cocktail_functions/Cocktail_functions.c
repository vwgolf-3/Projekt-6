/*
 * Cocktail_functions.c
 *
 * Created: 07.03.2020 13:45:39
 *  Author: kimsc
 */

#include "Cocktail_functions.h"

void cocktail_test_command(unsigned char INPUT[256])
{
    /*
        Diese Funktion ist eine Testfunktion, welche ausgelöst wird, wenn etwas über UART0 (PC) ankommt
    */
    Uart_Transmit_IT_PC("Test Command: ");
    Uart_Transmit_IT_PC((char *)INPUT);
    Uart_Transmit_IT_PC("\r\n");
    send_List_Zutaten();
}

void bearbeite_Cocktail(uint8_t cocktail)
{
//     choose_aktuellesGetraenk(cocktail);

    // Wähle geklickten Cocktail aus und schreibe ihn von SD in physikalischen Speicher
    getraenk_file_t * tmp = actual_list_node_file->getraenk_x;
    for (uint8_t cnt = 0 ; cnt < cocktail; cnt++)
    {
        tmp = tmp->prev;
    }
    aktuellesGetraenk_file = tmp;
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);

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
    nextion_change_page(CEINSTANZEIGE);
    buffer_zut_in_Maschine_ohne_KS = erstelle_Liste_zutat(tmp_file, "zutat");

    // Erweitere die neue Liste, deren Elemente einen Pointer auf die erste Zutat ohne Kohlensäure besitzt, um ein Element.
    tmp_node = create_new_list_node_zutMaschine_file(buffer_zut_in_Maschine_ohne_KS);
    head_zutatMaschine_list_node = insert_zutatMaschine_list_node_at_head(&head_zutatMaschine_list_node, tmp_node);
}

void zubereitung_getraenk(uint32_t Menge)
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

void schreibe_Menge_in_Getraenk(uint8_t zutat)
{
    zutatMaschine_t * tmp_zut_Maschine_actual_2 = aktuelle_zutatMaschine_list_node->zutat_xy;
    for (int count = 0 ; count < zutat; count++)
    {
        tmp_zut_Maschine_actual_2 = tmp_zut_Maschine_actual_2->prev;
    }
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

    nextion_setText("t0", "");
    uint8_t val = 0;
    char buff[15] = {0};
    char buff2[5];
    char buff3[5];

    uint8_t totval = 0;
    uint8_t restval = 0;

    // Alle Werte aus den anderen Mengen holen
    tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
    do
    {
        totval += tmp_zut_Maschine_actual->menge;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

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

    totval = 0;
    // Alle Werte aus den anderen Mengen holen
    tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
    do
    {
        totval += tmp_zut_Maschine_actual->menge;
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

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

    head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
}

void choose_aktuellesGetraenk(uint8_t nr)
{
    getraenk_file_t * tmp = actual_list_node_file->getraenk_x;
    for (uint8_t cnt = 0 ; cnt < nr; cnt++)
    {
        tmp = tmp->prev;
    }
    lese_textfile_in_getraenk(tmp->file);
    Uart_Transmit_IT_PC(aktuellesGetraenk->name);
    Uart_Transmit_IT_PC("\r");
    block_list_hoch = 0;
    block_list_runter = 0;
}

void fuelle_getraenk(uint32_t fuellmenge, linear_ramp_t *ramp)
{
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
    externes_Getraenk_flag = 0;

    // Switche durch alle Getränke
    do
    {
        Uart_Transmit_IT_PC(aktuelle_Zutat_in_Maschine_ohne_KS->name);
        Uart_Transmit_IT_PC("\r");

        *(aktuellesGetraenk->mengen + aktuelle_Zutat_in_Maschine_ohne_KS->stelle) = 20;

        // Falls das Getränk vorkommt
        if ((*(aktuellesGetraenk->mengen + aktuelle_Zutat_in_Maschine_ohne_KS->stelle) > 0) && (stop == 0))
        {
            Uart_Transmit_IT_PC(aktuelle_Zutat_in_Maschine_ohne_KS->name);
            Uart_Transmit_IT_PC("\r");
            aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure = 0;
            if (aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure == 0)
            {
                // Bewege Motor an stelle XY
                /*
                    Gebe Motor Position vor

                    While momentane Position != vorgegebene Position
                        warten

                    Weiter mit Programmm

                */
                calculateRamp(2000, 2000, tmc4671_getActualPosition(0)/1000 + ramp->motor_eine_umdrehung, ramp);
                while (ramp->ramp_enable)
                {
                    periodic_jobs(ramp);
                    _delay_ms(1);
                }
                tmc4671_writeInt(0, TMC4671_PID_POSITION_ACTUAL,                0x00000000);        // writing value 0x00000003 = 3 = 0.0 to address 67 = 0x63(MODE_RAMP_MODE_MOTION)

//              uint32_t pulse_prp_1dl[12] = {477, 474, 483, 479, 486, 474, 479, 483, 474, 466, 477, 479};
//              uint32_t pulse_prp_3dl[12] = {499, 496, 499, 499, 499, 496, 500, 500, 496, 499, 502, 501};
                uint32_t pulse_prp_5dl[12] = {501, 500, 501, 500, 502, 500, 500, 502, 498, 501, 503, 506};

                // Berechne Menge, schalte Pumpe ein und beginne mit füllen
                uint32_t Menge = (((uint32_t)fuellmenge * (uint32_t)pulse_prp_5dl[i]) * (uint32_t)*(uint8_t *)(aktuellesGetraenk->mengen + i)/(uint16_t)100);

                uint8_t fuellen = 1;
                uint8_t newval = lese_sensor(aktuelle_Zutat_in_Maschine_ohne_KS->stelle);

                schalte_pumpe_ein(aktuelle_Zutat_in_Maschine_ohne_KS->stelle);
                while (fuellen)
                {
                    // Polle PWM-Signal des Durchflusssensor
                    static uint8_t oldval=0;
                    static uint32_t count=0;

                    // Lese Sensor ein
                    newval = oldval ^ 0b00000001;
//                  newval = lese_sensor(i);

                    // Falls ein Flankenwechsel stattgefunden hat, zähle hoch
                    if( !oldval && newval)
                    {
                        // Falls erwünschte Menge erreicht wurde, breche aus Schleife aus und setze Zähler zurück
                        if(count++ > Menge)
                        {
                            schalte_pumpe_aus(aktuelle_Zutat_in_Maschine_ohne_KS->stelle);
                            count = 0;
                            fuellen = 0;
                        }
//*************************************************************************
//                  Delay entfernen wenn mit Sensor gearbeitet wird.
                        _delay_ms(1);
                        if (check_Communication_Input_UART_1())
                        {
                            proceed_Communication_INPUT_UART_1();
                            if (stop == 1)
                            {
                                for (int k = 0 ; k < 12 ; k++)
                                {
                                    schalte_pumpe_aus(k);
                                }
                                nextion_change_page(ABBRUCHANZEIGE);
                                _delay_ms(2000);

                                setze_startanzeige(aktuellesGetraenk);
                                count = 0;
                                fuellen = 0;
                            }
                        }
                    }
                    // Aktueller Sensorwert speichern
                    oldval = newval;
                }
            }
            else
            {
                externes_Getraenk_flag = 1;
            }
        }
        aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    } while(aktuelle_Zutat_in_Maschine_ohne_KS != tail_zut_in_Maschine_ohne_KS);

    /*
        Fahre zurück bis Home-Schalter betätigt wird
    */
    stop = 0;

    if (externes_Getraenk_flag == 1)
    {
        nextion_change_page(INFOANZEIGE);
        nextion_setText("infotxt", "Bitte noochfülle extärn");
        _delay_ms(2000);
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

void schreibe_Getraenk_in_tag(uint8_t nr)
{
    aktuellesGetraenk_file = tail_getraenk_file;
    for(int count = 0 ; count < (i_Liste + nr) ; count++)
    {
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
    }
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
    char buffer[512] = {'\0'};
    char * ptr = buffer;

    strcat(ptr, "tagzuweisungup:");
    char itoa_buff[5] = {'\0'};
    itoa(aktueller_tag->tag_nummer+1, itoa_buff, 10);
    strcat(ptr, itoa_buff);
    strcat(ptr, ":");
    strcat(ptr, aktuellesGetraenk->name);


    Uart_Transmit_IT_ESP(ptr);
    Uart_Transmit_IT_PC(ptr);
    strcpy((char *)aktueller_tag->cocktail_name, (const char *)aktuellesGetraenk->name);

    nextion_change_page(RFIDFEHLER);
    char * itoa_ptr = itoa_buff;

    strcpy(ptr, "Tag-Nr.");
    itoa(aktueller_tag->tag_nummer, itoa_ptr, 10);
    strcat(ptr, itoa_ptr);
    strcat(ptr, " wurde ");
    strcat(ptr, aktueller_tag->cocktail_name);
    strcat(ptr, " zugeordnet. :)");


    nextion_setText("fehlertxt",ptr);
    _delay_ms(2000);

    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}

getraenk_file_t * erstelle_Liste_name(getraenk_file_t * beginn_file, char * name_button)
{
    getraenk_file_t * tmp_file_tail;
    getraenk_file_t * tmp_file_head;
    getraenk_file_t * tmp_file_actual = beginn_file;

    tmp_file_tail = tail_getraenk_file;
    tmp_file_head = head_getraenk_file;

    // Für alle Buttons auf der Seite ...
    // Initialisierungen
    char button[50] = {'\0'};
    char buff[5] = {0};

    for (int count = 0 ; count < 6 ; count++)
    {
        // Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
        if(tmp_file_actual == tmp_file_tail && !block_list_runter)
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
        if (tmp_file_actual == tmp_file_head && !block_list_runter)
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
        tmp_file_actual = tmp_file_actual->prev;

        if (count == 5)
        {
            if (block_list_runter == 1)
            {
                return beginn_file;
            }
            else
            {
                return tmp_file_actual;
            }
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }
    return NULL;
}

zutatMaschine_t * erstelle_Liste_zutat(zutatMaschine_t * beginn_Maschine, char * input)
{
    // Strings für Name/Slider/Wert
    char string[21] = {'\0'};
    char string2[21] = {'\0'};
    char string3[21] = {'\0'};

    // Itoa-Buffer
    char buff[5] = {0};

// Aneinanderreihen zweier Listen

    // Pointer Beginn/Anfang/Aktuell/Return-(zutatMaschine_t)
    zutatMaschine_t * tmp_zut_Maschine_tail;
    zutatMaschine_t * tmp_zut_Maschine_head;
    zutatMaschine_t * tmp_zut_Maschine_actual = beginn_Maschine;
    zutatMaschine_t * tmp_zut_Maschine_return = beginn_Maschine;

    // Speichern der Momentanen Pointer.
    zutatMaschine_t * tmp_ohne_KS_head = head_zut_in_Maschine_ohne_KS->prev;
    zutatMaschine_t * tmp_mit_KS_head = head_zut_ausser_Maschine_mit_KS->prev;
    zutatMaschine_t * tmp_ohne_KS_tail = tail_zut_in_Maschine_ohne_KS->next;
    zutatMaschine_t * tmp_mit_KS_tail = tail_zut_ausser_Maschine_mit_KS->next;

    // Anfang und Ende der gesamten Liste
    tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
    tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

    // Äussere Verbindungen
    tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
    head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

    // Innere Verbindungen
    tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
    head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

// head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
// head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
// tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
// tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;

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
        if(tmp_zut_Maschine_actual == tmp_zut_Maschine_tail && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        while(tmp_zut_Maschine_actual->status == 0 && tmp_zut_Maschine_actual != tmp_zut_Maschine_head)
        {
            tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
        }

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen, blockieren und letzter Name einschreiben.
        if (tmp_zut_Maschine_actual == tmp_zut_Maschine_head && !block_list_runter)
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
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;

        if (count == 3 && block_list_runter == 0)
        {
            tmp_zut_Maschine_return = tmp_zut_Maschine_actual;
            return tmp_zut_Maschine_return;
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }

    head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
    return tmp_zut_Maschine_return;
}

void erstelle_bearb_Cocktailliste(void)
{
    for (int i = i_Liste ; i < (9 + i_Liste) ; i++)
    {
        char string[21] = {'\0'};
        char buff[4] = {0};
        itoa((i-i_Liste),buff,10);
        strcat((char *)string, (const char *)"bearbcocktail");
        strcat((char *)string, (const char *)buff);

        if (i == head_getraenk_file->file && !block_list_runter)
        {
            block_list_runter = 1;
            lese_textfile_in_getraenk(i);
            nextion_setText(string,aktuellesGetraenk->name);
        }
        else if (block_list_runter)
        {
            nextion_setText(string,"");
            Uart_Transmit_IT_Display("tsw bearbcocktail8,0");
            endConversation();
        }
        else
        {
            lese_textfile_in_getraenk(i);
            nextion_setText(string,aktuellesGetraenk->name);
        }
        _delay_ms(10);
    }
}

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
    char buff[10] = {'\0'};
    char string[512] = {'\0'};

    tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;

    do
    {
        if (tmp_zut_Maschine_actual->menge > (uint8_t)0)
        {
            strcat((char *)string, (const char *)tmp_zut_Maschine_actual->name);
            for (int count2 = 0 ; count2<(20-strlen(tmp_zut_Maschine_actual->name)) ; count2++)
            {
                strcat((char *)string,(const char *)"-");
            }
            strcat((char *)string, (const char *)"(");
            itoa(tmp_zut_Maschine_actual->menge,(char *)buff, 10);
            strcat((char *)string, (const char *)buff);
            strcat((char *)string, (const char *)"%)\\r");
        }
        tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
    } while (tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);
    nextion_setText("zutatenliste",string);
    head_zut_in_Maschine_ohne_KS->prev = tmp_ohne_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
}

void schiebe_file_next(void)
{
    aktuellesGetraenk_file = aktuellesGetraenk_file->next;
    char buff[50] = {'\0'};
    itoa(aktuellesGetraenk_file->file, (char *) buff, 10);
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

void schiebe_file_prev(void)
{
    aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
    char buff[50] = {'\0'};
    itoa(aktuellesGetraenk_file->file, (char *) buff, 10);
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
}

void lese_textfile_in_getraenk(uint8_t file)
{
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

//     head_zut_in_Maschine_ohne_KS->prev = tmp_ohne_KS_head;
//     tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
//     tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
//     head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;

    // Erstellen eines Strings in Form von: "file.txt"
    char buff[50];
    itoa((int)file,(char *)buff,10);
    char * txt = ".txt";
    strcat((char *)buff,txt);

    // "file.txt" lesen (File wird in char buffer[512] geschrieben)
    //return: 0, if normal operation or flag is READ
    //        1, if file is already existing and flag = VERIFY
    //        2, if file name is incompatible

    readFile( READ, (unsigned char *)buff);

    // Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
    char delimiter[] = ":\r\n";
    char *ptr;
    // initialisieren und ersten Abschnitt erstellen (1. Kopf)

    ptr = strtok((char *)buffer, delimiter);
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

            tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;

            do
            {
                tmp_zut_Maschine_actual->menge = (uint8_t) 0;
                tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;

            } while(tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

            // Suche Zutaten im File
            while(*ptr != ';')
            {
                tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;

                // Suche nach richtiger Position der Zutat in der Maschine
                do
                {
                    // Vergleiche dafür den Namen der Zutat im File mit dem Namen der Zutat in der Maschine
                    if(strcmp((char *)ptr, (char *)tmp_zut_Maschine_actual->name) == 0)
                    {
                        ptr = strtok(NULL, delimiter);

                        // Und schreibe Wert in die richtige Position
                        tmp_zut_Maschine_actual->menge = atoi(ptr);
                        tmp_zut_Maschine_actual = tmp_zut_Maschine_tail;
                    }

                    tmp_zut_Maschine_actual = tmp_zut_Maschine_actual->prev;
                } while(tmp_zut_Maschine_actual != tmp_zut_Maschine_tail);

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
    head_zut_in_Maschine_ohne_KS->prev = tmp_ohne_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
}

void SD_startup(void)
{
    cardType = 0;

    for (i=0; i<10; i++)
    {
        error = SD_init();
        if(!error) break;
    }

    if(error)
    {
        if(error == 1) Uart_Transmit_IT_PC((char*)("SD card not detected..\r"));
        if(error == 2) Uart_Transmit_IT_PC((char*)("Card Initialization failed..\r"));
        nextion_change_page(FEHLERANZEIGE);
        nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte erkannt.\\rBitte prüfen und\\rneu starten.");
        while(1);  //wait here forever if error in SD init
    } else {

        switch (cardType)
        {
        case 1:
            Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 1.x) Detected!\r"));
            break;
        case 2:
            Uart_Transmit_IT_PC(("High Capacity Card Detected!\r"));
            break;
        case 3:
            Uart_Transmit_IT_PC(("Standard Capacity Card (Ver 2.x) Detected!\r"));
            break;
        default:
            Uart_Transmit_IT_PC(("Unknown SD Card Detected!\r"));
            break;
        }
    }

//  SPI_HIGH_SPEED; //SCK - 4 MHz
    _delay_ms(1);   //some delay


    FAT32_active = 1;
    error = getBootSectorData (); //read boot sector and keep necessary data in global variables
    if(error)
    {
        nextion_change_page(FEHLERANZEIGE);
        nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte erkannt.\\rBitte prüfen und\\rneu starten.");
        Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
        FAT32_active = 0;
    }
//  findFiles(GET_LIST,0);

}

void erstelle_File(uint8_t filename, char * name, uint8_t alkohol, uint8_t kohlensaeure)
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

// Anfang und Ende der gesamten Liste
    tmp_zut_Maschine_tail = tail_zut_in_Maschine_ohne_KS;
// tmp_zut_Maschine_head = head_zut_ausser_Maschine_mit_KS;

// Äussere Verbindungen
    tail_zut_in_Maschine_ohne_KS->next = head_zut_ausser_Maschine_mit_KS;
    head_zut_ausser_Maschine_mit_KS->prev = tail_zut_in_Maschine_ohne_KS;

// Innere Verbindungen
    tail_zut_ausser_Maschine_mit_KS->next = head_zut_in_Maschine_ohne_KS;
    head_zut_in_Maschine_ohne_KS->prev = tail_zut_ausser_Maschine_mit_KS;

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
    writeFile((unsigned char *)buff3,(unsigned char *)ptr);

    head_zut_in_Maschine_ohne_KS->prev =tmp_ohne_KS_head;
    head_zut_ausser_Maschine_mit_KS->prev = tmp_mit_KS_head;
    tail_zut_in_Maschine_ohne_KS->next = tmp_ohne_KS_tail;
    tail_zut_ausser_Maschine_mit_KS->next = tmp_mit_KS_tail;
}

void loesche_FIle(uint8_t filename)
{
    unsigned char buff[20] = {'\0'};
    itoa(filename, (char *)buff, 10);
    strcat((char *)buff,".txt");
    deleteFile((unsigned char *)buff);

}

zutat_file_t * erstelle_Liste_Zutat_Pos(zutat_file_t * beginn_file, char * name_button)
{
    // Kohlesäuremode = 0 ==> User kann auch "keine Flüssigkeit" auswählen.

    char buff[5] = {'\0'};

    if (kohlensaeure_mode ==0 )
    {
        nextion_visible_on("b1");
    }

    zutat_file_t * tmp_file_tail;
    zutat_file_t * tmp_file_head;
    zutat_file_t * tmp_file_actual = beginn_file;
    zutat_file_t * tmp_file_return = beginn_file;

    // Die Zutaten werden ab Beginn gesucht.
    if (kohlensaeure_mode == 0)
    {
        tmp_file_tail = tail_Zutat_file_in_Maschine_ohne_KS;
        tmp_file_head = head_Zutat_file_in_Maschine_ohne_KS;
    }
    else
    {
        tmp_file_tail = tail_Zutat_file_ausser_Maschine_mit_KS;
        tmp_file_head = head_Zutat_file_ausser_Maschine_mit_KS;
    }

    // Für alle Buttons auf der Seite ...
    char button[50] = {'\0'};
    char buff10[50] = {'\0'};
	block_list_hoch = 0 ;
	block_list_runter = 0;
    for (int count = 0 ; count < 6 ; count++)
    {
        // Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde
        // (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "überläuft" und so beide
        // Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
        if(tmp_file_actual == tmp_file_tail && !block_list_runter)
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
        if (tmp_file_actual == tmp_file_head && !block_list_runter)
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
            aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
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
                    aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->prev;
                }
            } while (aktuelle_Zutat_ausser_Maschine_mit_KS != tail_zut_ausser_Maschine_mit_KS && run);
        }

        // Ein Getraenk weiter Scrollen.
        tmp_file_actual = tmp_file_actual->prev;
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

void lese_textfile_in_zutat(uint8_t file)
{
    char buff_textfiles_zutat[21] = {'\0'};
    char buff2_textfiles_zutat[5] = {'\0'};

    strcpy((char *)buff_textfiles_zutat, (const char *)"Z");
    itoa(file, (char *)buff2_textfiles_zutat, 10);
    strcat((char *)buff_textfiles_zutat, (const char *)buff2_textfiles_zutat);
    strcat((char *)buff_textfiles_zutat, (const char *)".txt");

    readFile(READ, (unsigned char *)buff_textfiles_zutat);

    // Trennungszeichen definieren, Pointer initialisiern f?r Abschnitte
    char delimiter[] = ":,{}\r\n";
    char *ptr;

    // initialisieren und ersten Abschnitt erstellen (1. Kopf)
    ptr = strtok((char *)buffer, delimiter);

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

void setze_Posanzeige_Rot_Gruen(void)
{
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
    char buff[50];
    char buff2[10];
    for (int i = 0 ; i <12 ; i++)
    {
        strcpy((char *)buff, "b");
        itoa(i,(char *) buff2, 10);
        strcat((char *)buff, (const char *)buff2);
        switch (aktuelle_Zutat_in_Maschine_ohne_KS->status)
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
        aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    }
}

void setze_aktuelle_Zutat_in_Maschine_prev(uint8_t nr)
{
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
    for (int i = 0 ; i < nr; i++)
    {
        aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    }
}

void setze_Fluessgkeit_in_Position(uint8_t nr, uint8_t status)
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
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File (kohlesaeure_mode == 0 && aktuelleZutat->kohlesaeure == 1)
    if (nr == 8)
    {
        nextion_change_page(POSANZEIGE);
    }


    // Falls innerhalb des Listenbereichs ==> Flüssigkeit aus File laden
    if (nr < 6)
    {
        nextion_change_page(POSANZEIGE);
        // Wähle Zutaten-File, auf welches gedrückt wurde und lese es ein.
        aktuelles_Zutat_file_in_Maschine_ohne_KS = aktuelle_zutat_list_node->zutat_xy;

        for (uint8_t i = 0 ; i < nr ; i++)
        {
            aktuelles_Zutat_file_in_Maschine_ohne_KS = aktuelles_Zutat_file_in_Maschine_ohne_KS->prev;
        }
        lese_textfile_in_zutat(aktuelles_Zutat_file_in_Maschine_ohne_KS->file);

        strcpy(aktuelle_Zutat_in_Maschine_ohne_KS->name, aktuelle_zutat->name);
        aktuelle_Zutat_in_Maschine_ohne_KS->status = status;
        aktuelle_Zutat_in_Maschine_ohne_KS->alkohol = aktuelle_zutat->alkohol;
        aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure = aktuelle_zutat->kohlensaeure;
    }

    // Schreibe Änderung in Titel der Positionsanzeige
    strcpy((char *)buff, "Nr.");
    itoa(aktuelle_Zutat_in_Maschine_ohne_KS->stelle+1, buff2, 10);
    strcat((char *)buff, (const char *)buff2);
    strcat((char *)buff, " = ");
    strcat((char *)buff, aktuelle_Zutat_in_Maschine_ohne_KS->name);
    nextion_setText("zubabfrage",buff);

    // Setze Status der Zahlen
    setze_Posanzeige_Rot_Gruen();

    // Initialisieren Listen-Variabeln
    block_list_hoch = 0;
    block_list_runter = 0;

    // Aktualisieren des Maschinen-Files
    char buff98[20] = {'\0'};
    strcpy((char *)buff98, (const char *)"M.txt");
    deleteFile((unsigned char *)buff98);
    char buff_file[512] = {'\0'};
    char * ptr = buff_file;

    write_M_file(ptr);

    char buff97[20] = {'\0'};
    strcpy((char *)buff97, (const char *)"M.txt");
    writeFile((unsigned char *)buff97, (unsigned char *)buff_file);

}

void setze_Fluessgkeit_in_Position_Aussen(uint8_t nr, uint8_t status)
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
            aktuelles_Zutat_file_ausser_Maschine_mit_KS = aktuelle_zutat_list_node->zutat_xy;
            // Shifte zum gedrückten File und lese es ein
            for (uint8_t i = 0 ; i < nr ; i++)
            {
                aktuelles_Zutat_file_ausser_Maschine_mit_KS = aktuelles_Zutat_file_ausser_Maschine_mit_KS->prev;
            }
            lese_textfile_in_zutat(aktuelles_Zutat_file_ausser_Maschine_mit_KS->file);
        }

        // Wenn Nr == 0 ==> Neue Flüssigkeit
        if (nr == 8)
        {
            lese_textfile_in_zutat(head_Zutat_file_ausser_Maschine_mit_KS->file);
        }

        // Vergleiche, ob Filename bereits in der Liste ist
        uint8_t run = 1;
        uint8_t count = 0;
        // Beginne bei erster Zutat ausserhalb der Maschine
        aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
        do
        {
            if (aktuelle_Zutat_ausser_Maschine_mit_KS->status == 1)
            {
                if (strcmp(aktuelle_Zutat_ausser_Maschine_mit_KS->name, aktuelle_zutat->name)==0)
                {
                    strcpy(string_ptr, aktuelle_Zutat_ausser_Maschine_mit_KS->name);
                    strcat(string_ptr, " entfernt.");
                    nextion_setText("fluessbfrage", string_ptr);
                    nextion_setText("zubabfrage", string_ptr);

                    strcpy(aktuelle_Zutat_ausser_Maschine_mit_KS->name, "(keine)");
                    aktuelle_Zutat_ausser_Maschine_mit_KS->status=0;
                    aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol = 0;
                    aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure = 0;

                    run = 0;

                    itoa((nr + 1),itoa_ptr,10);
                    strcpy(string_ptr, "fluessigkeit");
                    strcat(string_ptr, itoa_ptr);

                    strcat(string_ptr, (const char *)".pco=0");
                    Uart_Transmit_IT_Display(string_ptr);
                    endConversation();
                    count--;
                }
                count++;
            }
            aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->prev;
        } while (aktuelle_Zutat_ausser_Maschine_mit_KS != tail_zut_ausser_Maschine_mit_KS);

        if (run == 1)
        {
            aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
            do
            {
                if (aktuelle_Zutat_ausser_Maschine_mit_KS->status == 0)
                {
                    strcpy(aktuelle_Zutat_ausser_Maschine_mit_KS->name, aktuelle_zutat->name);
                    aktuelle_Zutat_ausser_Maschine_mit_KS->status=1;
                    aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol = aktuelle_zutat->alkohol;
                    aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure = aktuelle_zutat->kohlensaeure;
                    strcpy(string_ptr, aktuelle_Zutat_ausser_Maschine_mit_KS->name);
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
                    aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->prev;
                }
            } while (aktuelle_Zutat_ausser_Maschine_mit_KS != tail_zut_ausser_Maschine_mit_KS && run == 1);

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
    deleteFile((unsigned char *)buff98);
    char buff_file[512] = {'\0'};
    char * ptr = buff_file;

    write_M_file(ptr);

    char buff97[20] = {'\0'};
    strcpy((char *)buff97, (const char *)"M.txt");
    writeFile((unsigned char *)buff97, (unsigned char *)buff_file);
}

void send_List_Getraenke (void)
{
    char buff[512] = {'\0'};
    char * ptr = buff;

    char counter = 0;
    aktuellesGetraenk_file = tail_getraenk_file;

    do
    {
        counter++;
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
    } while (aktuellesGetraenk_file != tail_getraenk_file);

    strcat(ptr, "getraenkeliste:");
    char buffer[5] = {'\0'};
    itoa(counter, (char *) buffer, 10);
    strcat(ptr, (char *) buffer);
    strcat(ptr, ":");

    aktuellesGetraenk_file = tail_getraenk_file;

    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);

    strcat(ptr, aktuellesGetraenk->name);
    aktuellesGetraenk_file = aktuellesGetraenk_file->prev;

    for (int cnt = 0 ; cnt < (counter - 1); cnt++)
    {
        strcat(ptr, ",");
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        strcat(ptr, aktuellesGetraenk->name);
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
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



    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;

    strcpy(ptr2, "zutaten:");
    uint8_t first = 1;
    do
    {
        if (strcmp("(keine)", aktuelle_Zutat_in_Maschine_ohne_KS->name)!=0)
        {
            if (first == 1)
            {
                strcat(ptr, aktuelle_Zutat_in_Maschine_ohne_KS->name);
                first = 0;
            }
            else
            {
                strcat(ptr, ",");
                strcat(ptr, aktuelle_Zutat_in_Maschine_ohne_KS->name);

            }
            counter ++;
        }
        aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    } while (aktuelle_Zutat_in_Maschine_ohne_KS != tail_zut_in_Maschine_ohne_KS);
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

    aktuellesGetraenk_file = tail_getraenk_file;
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);

    while (strcmp(aktuellesGetraenk->name, ptr)!=0)
    {
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
        lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
        Uart_Transmit_IT_PC("While\r");
    }
    nextion_change_page(ZUBABFRAGE);
}

void Getraenk_erstellt()
{
    // String extrahieren und SD-Karten-File speichern (Getraenk)

    while (check_Communication_Input_UART_2()==0)
        ;
    Uart_Transmit_IT_PC((char *)INPUT_UART_2);
    char buff[256] = {'\0'};
    char string[256] = {'\0'};
    char * ptr = buff;
    char * ptr2 = string;
    char delimiter[] = ",:\r";

    strcpy(buff, (char *)INPUT_UART_2);
    //Name
    ptr = strtok(ptr, delimiter);
    Uart_Transmit_IT_PC("\rName: ");
    Uart_Transmit_IT_PC(ptr);
    strcat(ptr2, "Name:");
    strcat(ptr2, ptr);
    strcat(ptr2, "\rMengen:\r");

    char buff2[20] = {'\0'};
    char temp2[21] = {'\0'};
    char alkohol = 0;
    for (int count = 0 ; count < 12 ; count++)
    {
        // Zutat 1 Name
        Uart_Transmit_IT_PC("\rZutat");
        itoa((count + 1), (char *)buff2, 10);
        Uart_Transmit_IT_PC(buff2);
        Uart_Transmit_IT_PC(": ");
        ptr = strtok(NULL, delimiter);
        Uart_Transmit_IT_PC(ptr);
        strcpy((char *)temp2, ptr);

        // Zutat 1 Menge
        Uart_Transmit_IT_PC("\rMenge");
        itoa((count + 1), (char *)buff2, 10);
        Uart_Transmit_IT_PC(buff2);
        Uart_Transmit_IT_PC(": ");
        ptr = strtok(NULL, delimiter);
        if (atoi(ptr)>0)
        {
            aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
            for (int count2 = 0 ; count2 < 12 ; count2++)
            {
                if (strcmp(aktuelle_Zutat_in_Maschine_ohne_KS->name, temp2) == 0)
                {
                    if (aktuelle_Zutat_in_Maschine_ohne_KS->alkohol == 1)
                    {
                        alkohol = 1;
                    }
                }
                aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
            }
            strcat(ptr2, (const char *)temp2);
            strcat(ptr2, ":");
            strcat(ptr2, ptr);
            strcat(ptr2, "\r");
        }
        Uart_Transmit_IT_PC(ptr);
        _delay_ms(200);
    }
    strcat(ptr2, ";\r");
    strcat(ptr2, "Alkohol:");
    itoa(alkohol, (char *)buff2, 10);
    strcat(ptr2, (char *)buff2);
    strcat(ptr2, "\rBild:32");
    strcat(ptr2, "~");

    Uart_Transmit_IT_PC(ptr2);

    // Filename erstellen
    char buff97[20] = {'\0'};
    itoa((head_getraenk_file->file)+1, (char *)buff2, 10);
    strcpy((char *)buff97, (char *)buff2);
    strcat((char *)buff97, (const char *)".txt");
    writeFile((unsigned char *)buff97, (unsigned char *)ptr2);
    Uart_Transmit_IT_PC((char *)buff97);

    // An dynamic linked list anhängen
    getraenk_file_t * tmp2;
    tmp2 = create_new_getraenk_file((head_getraenk_file_2->file)+1);
    head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp2);
}

void free_list_getraenke(void)
{
    /* deref head_ref to get the real head */
    getraenk_file_t* current = head_getraenk_file;
    getraenk_file_t* next = current;

    while (current != tail_getraenk_file)
    {
		Uart_Transmit_IT_PC("Hoi3\r");
        next = current->next;
        free(current);
        current = next;
    }
	if (current == tail_getraenk_file)
	{
		head_getraenk_file = NULL;
		tail_getraenk_file = NULL;
		free(current);
		Uart_Transmit_IT_PC("Hoi4\r");
	}
    /* deref head_ref to affect the real head back
        in the caller. */
}

void setze_standardeinstellungen(void)
{

    nextion_change_page(RFIDFEHLER);
    nextion_setText("fehlertxt","Stelle Maschine auf den Kopf");
    _delay_ms(2000);
    // Debug
    char name[2] = {'\0'};

    // EEPROM-Beginn Standards
    address_Standardwiederherstellung = 0;

    // Iterationsvariable String
    uint8_t kk = 0;

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
    deleteFile((unsigned char *)buff5);

    // Schreibe neues M.txt-file
    strcpy((char *)buff5, (const char *)"M.txt");
    writeFile((unsigned char *)buff5, (unsigned char *)buff_string);

    char delimiter[] = ",\r\n";                         // Trennungszeichen definieren              (strtok)
    char *ptr;                                          // Pointer für Abschnitte initialisieren   (strtok)

    // Beschreibe die Maschinenzutaten gemäss Backup M.txt
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
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
	    strcpy(aktuelle_Zutat_in_Maschine_ohne_KS->name,ptr);                      // Kopiere Name in Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
	    aktuelle_Zutat_in_Maschine_ohne_KS->status = atoi(ptr);                    // Schreibe ASCI-Status in Integer-Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
	    aktuelle_Zutat_in_Maschine_ohne_KS->alkohol = atoi(ptr);                   // Schreibe ASCI-JA//Nein in Integer-Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
	    aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure = atoi(ptr);              // Schreibe ASCI-JA//Nein in Integer-Buffer

	    aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    } while(aktuelle_Zutat_in_Maschine_ohne_KS != tail_zut_in_Maschine_ohne_KS);
	
		    ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein

	    // Beschreibe die Maschinenzutaten gemäss Backup M.txt
    aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
    do
    {
		    ptr = strtok(NULL, delimiter);                        // Abschnitt Name Zutat
	    strcpy(aktuelle_Zutat_ausser_Maschine_mit_KS->name,ptr);                      // Kopiere Name in Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
	    Uart_Transmit_IT_PC(ptr);
	    aktuelle_Zutat_ausser_Maschine_mit_KS->status = atoi(ptr);                    // Schreibe ASCI-Status in Integer-Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
	    aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol = atoi(ptr);                   // Schreibe ASCI-JA//Nein in Integer-Buffer
	    ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
	    aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure = atoi(ptr);              // Schreibe ASCI-JA//Nein in Integer-Buffer

	    aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->prev;
    } while(aktuelle_Zutat_ausser_Maschine_mit_KS != tail_zut_ausser_Maschine_mit_KS);

    // Erstelle Getränkeliste neu mit gebackupten Maschinenzutaten
    renew_list();

    // Erstelle Startanzeige
    nextion_change_page(STARTANZEIGE);
    aktuellesGetraenk_file = tail_getraenk_file;
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
    setze_startanzeige(aktuellesGetraenk);
}

void renew_list(void)
{
    // Informiere User über Zustand
    nextion_change_page(RFIDFEHLER);
    nextion_setText("fehlertxt", "Mixe neue Cocktailliste.\\rVerhalten Sie sich ruhig, \\rgleich können Sie auswählen.");

    // Getränke-Liste löschen
    free_list_getraenke();

    // Getränke-Liste anhand neuer Zutaten evaluieren und generieren
    getraenk_file_t * tmp;
    aktuellesGetraenk_file_2 = tail_getraenk_file_2;
    do
    {
        if(check_existence(aktuellesGetraenk_file_2->file))
        {
            tmp = create_new_getraenk_file(aktuellesGetraenk_file_2->file);
            head_getraenk_file = insert_file_at_head(&head_getraenk_file, tmp);
        }
        aktuellesGetraenk_file_2 = aktuellesGetraenk_file_2->prev;
		Uart_Transmit_IT_PC("Hoi\r");
    } while (aktuellesGetraenk_file_2 != tail_getraenk_file_2);
		Uart_Transmit_IT_PC("Hoi2\r");

    aktuellesGetraenk_file = tail_getraenk_file;
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);
}

// Wurde Separat genommen, sodass das EEPROM mit aktuellen Drinks beschrieben werden kann für eine andere Standardeinstellung
void write_M_file(char * buff_file)
{
    char buff99[10] = {'\0'};
    aktuelle_Zutat_in_Maschine_ohne_KS = tail_zut_in_Maschine_ohne_KS;
    for (int count = 0 ; count < 12 ; count++)
    {
        if (count != 0)
        {
            strcat((char *)buff_file, (const char *)aktuelle_Zutat_in_Maschine_ohne_KS->name);
        }
        else
        {
            strcpy((char *)buff_file, (const char *)aktuelle_Zutat_in_Maschine_ohne_KS->name);
        }
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_in_Maschine_ohne_KS->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_in_Maschine_ohne_KS->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_in_Maschine_ohne_KS->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)"\r");
        aktuelle_Zutat_in_Maschine_ohne_KS = aktuelle_Zutat_in_Maschine_ohne_KS->prev;
    }
    strcat((char *)buff_file, (const char *)";\r");

    aktuelle_Zutat_ausser_Maschine_mit_KS = tail_zut_ausser_Maschine_mit_KS;
    for (int count = 0 ; count < 12 ; count++)
    {
        strcat((char *)buff_file, (const char *)aktuelle_Zutat_ausser_Maschine_mit_KS->name);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_ausser_Maschine_mit_KS->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_ausser_Maschine_mit_KS->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelle_Zutat_ausser_Maschine_mit_KS->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        if (aktuelle_Zutat_ausser_Maschine_mit_KS != head_zut_ausser_Maschine_mit_KS)
        {
            strcat((char *)buff_file, (const char *)"\r");
        }
        else
        {
            strcat(buff_file, "\r;\r~");
        }
        aktuelle_Zutat_ausser_Maschine_mit_KS = aktuelle_Zutat_ausser_Maschine_mit_KS->prev;
    }
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

void display_init(void)
{
    // Initialisierungen Display
    Grossschreib = 1;                                       // Initialisiere Grossschreibung Display mit gross (gibt kein Display init();)
    i_Liste = 0;                                            // Listenabschnitt auf 0 vordefinieren
    block_list_hoch = 0;                                    // Blockierung der Listen aufheben
    block_list_runter = 0;                                  // Blockierung der Listen aufheben
    i_Liste_test_cnt = 0;
    i_Liste_test[i_Liste_test_cnt] = 0;
}


void begin_erstelle_Liste_Zutat_Pos(void)
{
    zutat_list_node_t * tmp_node;
    zutat_file_t * tmp_file;

    // Die Zutaten werden ab Beginn gesucht.
    if (kohlensaeure_mode == 0)
    {
        tmp_file = tail_Zutat_file_in_Maschine_ohne_KS;
    }
    else
    {
        tmp_file = tail_Zutat_file_ausser_Maschine_mit_KS;
    }

    // Die Listen-Pointer werden mit 0 initialisiert
    head_zutat_list_node = NULL;
    tail_zutat_list_node = NULL;

    // Suche erstes File ohne Kohensäure
    lese_textfile_in_zutat(tmp_file->file);

    // Erstelle eine neue Liste, deren Elemente einen Pointer auf die erste Zutat ohne Kohlensäure besitzt. Erste Zutat = Erster Eintrag des jeweiligen Listenabschnitts.
    tmp_node = create_new_list_node_zut_file(tmp_file);
    head_zutat_list_node = insert_zutat_list_node_at_head(&head_zutat_list_node, tmp_node);

    // Initialisiere den Pointer auf den aktuellen ersten Eintrag der Liste (welche den Pointer auf die erste Zutat ohne Kohlensäure beinhaltet)
    aktuelle_zutat_list_node = head_zutat_list_node;
    lese_textfile_in_zutat(aktuelle_zutat_list_node->zutat_xy->file);

    // Screibe die erste Seite der Liste. Return value = Erster Eintrag der nächsten Seite. (Sind keine weiteren Einträge vorhanden, wird der letzte Eintrag zurückgegeben. ==> head_Zutat_file_in_Maschine_ohne_KS)
    nextion_change_page(FLUESSANZEIGE1);
    buffer_zutat_file = erstelle_Liste_Zutat_Pos(tmp_file, "fluessigkeit");

    // Erweitere die neue Liste, deren Elemente einen Pointer auf die erste Zutat ohne Kohlensäure besitzt, um ein Element.
    tmp_node = create_new_list_node_zut_file(buffer_zutat_file);
    head_zutat_list_node = insert_zutat_list_node_at_head(&head_zutat_list_node, tmp_node);
}