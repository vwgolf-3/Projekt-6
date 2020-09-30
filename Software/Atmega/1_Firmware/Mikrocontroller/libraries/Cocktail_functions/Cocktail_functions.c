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
    choose_aktuellesGetraenk(cocktail);
    nextion_change_page(CEINSTANZEIGE);
    erstelle_Liste_zutat("zutat");
    i_Liste = 0;
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
    nextion_setText("t0", "");
    uint8_t val = 0;
    char buff[15] = {0};
    char buff2[5];
    char buff3[5];

    uint8_t totval = 0;
    uint8_t restval = 0;
    // Alle Werte aus den anderen Mengen holen

    for (int count = 0 ; count < 12 ; count++)
    {
        if (count != (zutat + i_Liste))
        {
            totval += *(aktuellesGetraenk->mengen + count);
        }
    }
    restval = 100 - totval;

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

    *(aktuellesGetraenk->mengen+(i_Liste+zutat)) = val;

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
}

void choose_aktuellesGetraenk(uint8_t nr)
{
    aktuellesGetraenk_file = actual_list_node_file->getraenk_x;
    for (int i = 0 ; i < (nr) ; i++)
    {
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;
    }
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
    Uart_Transmit_IT_PC(aktuellesGetraenk->name);
    Uart_Transmit_IT_PC("\r");
    block_list_hoch = 0;
    block_list_runter = 0;
    i_Liste = 0;
}

void fuelle_getraenk(uint32_t fuellmenge, linear_ramp_t *ramp)
{
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    externes_Getraenk_flag = 0;

    // Switche durch alle Getränke
    do
    {
        Uart_Transmit_IT_PC(aktuelleZutatInMaschine->name);
        Uart_Transmit_IT_PC("\r");

        *(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle) = 20;

        // Falls das Getränk vorkommt
        if ((*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle) > 0) && (stop == 0))
        {
            Uart_Transmit_IT_PC(aktuelleZutatInMaschine->name);
            Uart_Transmit_IT_PC("\r");
            aktuelleZutatInMaschine->kohlensaeure = 0;
            if (aktuelleZutatInMaschine->kohlensaeure == 0)
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
                uint8_t newval = lese_sensor(aktuelleZutatInMaschine->stelle);

                schalte_pumpe_ein(aktuelleZutatInMaschine->stelle);
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
                            schalte_pumpe_aus(aktuelleZutatInMaschine->stelle);
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
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    } while(aktuelleZutatInMaschine != tail_zut_in_Maschine);

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
    getraenk_file_t * tmp = head_getraenk_file;
    // Für alle Buttons auf der Seite ...
    // Initialisierungen
    char button[21] = {'\0'};
    char buff[4] = {0};
    char buff10[20] = {'\0'};

    strcat((char *)buff10, (const char *)name_button);
    itoa((i + 1), (char *)buff, 10);
    strcat((char *)buff10, (const char *)buff);

    nextion_enableButton(buff10);

    aktuellesGetraenk_file = beginn_file;

    for (int i = 0 ; i < 6 ; i++)
    {
        // Schreibe Zahl und Name des Buttons in String
        itoa((i + 1),buff,10);
        strcpy((char *)button, (const char *)name_button);
        strcat((char *)button, (const char *)buff);

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen blockieren und letzter Name einschreiben.
        if (aktuellesGetraenk_file == head_getraenk_file && !block_list_runter)
        {
            block_list_runter = 1;
            lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
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

            // Schreibe Text und Buttonnummer für disable in String
            strcpy((char *)buff10, (const char *)name_button);
            itoa((i + 1), (char *)buff, 10);
            strcat((char *)buff10, (const char *)buff);

            // Disable Button
            nextion_disableButton(buff10);
        }

        //Falls Eintrag dazwischen, Name einschreiben (Normalbetrieb)
        else
        {
            lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
            nextion_setText(button,aktuellesGetraenk->name);
        }

        // Falls das obere Ende der Liste erreicht wird, hochscrollen blockieren
        if(aktuellesGetraenk_file == tail_getraenk_file && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        // Ein Getraenk weiter Scrollen
        aktuellesGetraenk_file = aktuellesGetraenk_file->prev;

        if (i == 5 && block_list_runter == 0)
        {
            tmp = aktuellesGetraenk_file;
        }



        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }
    return tmp;
}

void erstelle_Liste_zutat(char * input)
{
    char string[21] = {'\0'};
    char string2[21] = {'\0'};
    char string3[21] = {'\0'};
    char buff[5] = {0};
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    for (int i = 0 ; i < i_Liste ; i++)
    {
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    }

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

        // Falls das Ende der Liste erreicht ist und Liste noch nicht blockiert,
        // Weiteres Scrollen blockieren,
        // Letzter Eintrag eintragen

        if (aktuelleZutatInMaschine == head_zut_in_Maschine && !block_list_runter)
        {
            block_list_runter = 1;
            nextion_setText(string,aktuelleZutatInMaschine->name);
            itoa(*(aktuellesGetraenk->mengen+aktuelleZutatInMaschine->stelle),buff,10);
            nextion_setValue(string2,buff);
            strcat(buff, "%");
            nextion_setText(string3,buff);
        }
        // Sonst, wenn Liste Blockiert
        // Leerer String in Feld schreiben
        else if (block_list_runter)
        {
            nextion_setText(string,"");
            nextion_setValue(string2,"0");
        }
        // Im Normalbetrieb Zutat in Feld schreiben,
        // Auf nächste Zutat zeigen
        else
        {
            nextion_setText(string,aktuelleZutatInMaschine->name);
            itoa(*(aktuellesGetraenk->mengen+aktuelleZutatInMaschine->stelle),buff,10);
            nextion_setValue(string2,buff);
            strcat(buff, "%");
            nextion_setText(string3,buff);
        }

        if(aktuelleZutatInMaschine == tail_zut_in_Maschine)
        {
            block_list_hoch = 1;
        }
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    }
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

    aktuelleZutatInMaschine = tail_zut_in_Maschine;

    for (uint8_t count = 0 ; count<12 ; count++)
    {
        if (*(aktuellesGetraenk->mengen + count) > (uint8_t)0)
        {
            strcat((char *)string, (const char *)aktuelleZutatInMaschine->name);
            for (int count2 = 0 ; count2<(20-strlen(aktuelleZutatInMaschine->name)) ; count2++)
            {
                strcat((char *)string,(const char *)"-");
            }
            strcat((char *)string, (const char *)"(");
            itoa(*(aktuellesGetraenk->mengen + count),(char *)buff, 10);
            strcat((char *)string, (const char *)buff);
            strcat((char *)string, (const char *)"%)\\r");
        }
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    }
    nextion_setText("zutatenliste",string);
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

            aktuelleZutatInMaschine = tail_zut_in_Maschine;

            do
            {
                *(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle) = (uint8_t) 0;
                aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
            } while(aktuelleZutatInMaschine != tail_zut_in_Maschine);

            // Suche Zutaten im File
            while(*ptr != ';')
            {
                aktuelleZutatInMaschine = tail_zut_in_Maschine;

                // Suche nach richtiger Position der Zutat in der Maschine
                do
                {
                    // Vergleiche dafür den Namen der Zutat im File mit dem Namen der Zutat in der Maschine
                    if(strcmp((char *)ptr, (char *)aktuelleZutatInMaschine->name) == 0)
                    {
                        ptr = strtok(NULL, delimiter);

                        // Und schreibe Wert in die richtige Position
                        *(uint8_t *)(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle) = atoi(ptr);
                        aktuelleZutatInMaschine = tail_zut_in_Maschine;
                    }

                    aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
                } while(aktuelleZutatInMaschine != tail_zut_in_Maschine);

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
        nextion_setText("fehlertxt","Fehler festgestellt!\\rKeine SD-Karte vorhanden.\\rBitte einfügen und\\rneu starten.");
        //      while(1);  //wait here forever if error in SD init
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
        Uart_Transmit_IT_PC (("FAT32 not found!\r\n"));  //FAT32 incompatible drive
        FAT32_active = 0;
    }
//  findFiles(GET_LIST,0);

}

void erstelle_File(uint8_t filename, char * name, uint8_t alkohol, uint8_t kohlensaeure)
{
    char buff[128] = {0};
    char * ptr = buff;
    strcat(ptr, "Name:");
    strcat(ptr, name);

    strcat(ptr, "\rMengen:\r");
    char buff2[5]  = {0};

    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    do
    {
        if (*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle) > (uint8_t) 0)
        {
            strcat(ptr,aktuelleZutatInMaschine->name);
            strcat(ptr, (const char *)":");
            itoa(*(aktuellesGetraenk->mengen + aktuelleZutatInMaschine->stelle), (char *)buff2, 10);
            strcat(ptr, (const char *)buff2);
            strcat(ptr, (const char *)"\r");
        }
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    } while (aktuelleZutatInMaschine != tail_zut_in_Maschine);

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
    if (aktuellesGetraenk->picture != 24)
    {
        char buff[5];
        itoa(aktuellesGetraenk->picture,(char *)buff, 10);
        strcat(ptr, (char *)buff);
    }
    else
    {
        strcat(ptr, "24");
    }

    strcat(ptr, "~");

    char buff3[15] = {'\0'};
    itoa(filename, (char *)buff3, 10);
    strcat((char *)buff3, (const char *)".txt");
    writeFile((unsigned char *)buff3,(unsigned char *)ptr);
}

void loesche_FIle(uint8_t filename)
{
    unsigned char buff[20] = {'\0'};
    itoa(filename, (char *)buff, 10);
    strcat((char *)buff,".txt");
    deleteFile((unsigned char *)buff);

}

zutat_file_t * erstelle_Liste_Zutat_Pos(uint8_t ks, zutat_file_t * beginn_file, char * name_button)
{
    asm("nop");

    if (ks ==0 )
    {
        nextion_visible_on("b1");
    }
    zutat_file_t * tmp = beginn_file;
    kohlensaeure_mode = ks;
    // Für alle Buttons auf der Seite ...
    // Initialisierungen
    char button[50] = {'\0'};
    char buff[5] = {0};
    char buff10[50] = {'\0'};
    kohlensaeure_mode = ks;
    aktuelles_zutat_file = beginn_file;
    for (int i = 0 ; i < 6 ; i++)
    {
        // Falls das obere Ende der Liste erreicht wird, und das untere noch nicht erreicht wurde
        // (da aktuelles Getraenk auf Tail getraenk springt und sozusagen "überläuft" und so beide
        // Richtungen blockiert werden, sobald das untere Ende erreicht wird), hochscrollen blockieren
        if(aktuelles_zutat_file == tail_zutat_file && !block_list_runter)
        {
            block_list_hoch = 1;
        }

        // Beginn-File einlesen.
        lese_textfile_in_zutat(aktuelles_zutat_file->file);
        Uart_Transmit_IT_PC(aktuelle_zutat->name);
        Uart_Transmit_IT_PC("\r");


        // Getränk mit/ohne Kohlensäure finden (Abhängig von kohlesäure_mode)
        uint8_t run = 1;
        while ((aktuelle_zutat->kohlensaeure != kohlensaeure_mode)&& run == 1)
        {
            if(aktuelles_zutat_file != head_zutat_file)
            {
                aktuelles_zutat_file = aktuelles_zutat_file->prev;
            }
            else
            {
                run = 0;
            }
            lese_textfile_in_zutat(aktuelles_zutat_file->file);
        }

        // Schreibe Zahl und Name des Buttons in String
        itoa((i + 1),buff,10);
        strcpy((char *)button, (const char *)name_button);
        strcat((char *)button, (const char *)buff);

        // Falls das untere Ende der Liste erreicht wurde und liste noch nicht blockiert ist,
        // runterscrollen, blockieren und letzter Name einschreiben.
        if (aktuelles_zutat_file == head_zutat_file && !block_list_runter)
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
            if (strcmp((char *)aktuelleZutatInMaschine->name, (char *)aktuelle_zutat->name)==0)
            {
                strcpy((char *)buff10, (const char *)button);
                strcat((char *)buff10, (const char *)".pco=2016");
                Uart_Transmit_IT_Display((char *)buff10);
                endConversation();
            }
        }
        else
        {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            /*
            - 1. aktuell geschriebener Name aus aktueller Zutat vergleichen, ob vorhanden in der Liste aktuelle Zutat ausserhalb Maschine
                - 2. Falls nicht vorhanden: Freier Platz suchen in Liste zum Speichern
            */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            aktuelleZutatAusserhalbMaschine = tail_zut_Ausserhalb_Maschine;
            run = 1;
            do
            {
                if (strcmp(aktuelle_zutat->name, aktuelleZutatAusserhalbMaschine->name) == 0)
                {
                    run = 0;
                    Uart_Transmit_IT_PC(aktuelleZutatAusserhalbMaschine->name);
                    Uart_Transmit_IT_PC("\r");
                    Uart_Transmit_IT_PC(aktuelle_zutat->name);
                    Uart_Transmit_IT_PC("\r");
                    strcpy((char *)buff10, (const char *)button);
                    strcat((char *)buff10, (const char *)".pco=2016");
                    Uart_Transmit_IT_Display((char *)buff10);
                    endConversation();
                }
                else
                {
                    aktuelleZutatAusserhalbMaschine = aktuelleZutatAusserhalbMaschine->prev;
                }
            } while ((run == 1) && (aktuelleZutatAusserhalbMaschine != tail_zut_Ausserhalb_Maschine));
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        // Ein Getraenk weiter Scrollen.
        aktuelles_zutat_file = aktuelles_zutat_file->prev;

        asm("nop");

        if (i == 5 && block_list_runter == 0)
        {
            tmp = aktuelles_zutat_file;
            return tmp;
        }

        // Sicherheitsdelay, Programm stürzt sonst ab
        _delay_ms(10);
    }
    return tmp;
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
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    char buff[50];
    char buff2[10];
    for (int i = 0 ; i <12 ; i++)
    {
        strcpy((char *)buff, "b");
        itoa(i,(char *) buff2, 10);
        strcat((char *)buff, (const char *)buff2);
        switch (aktuelleZutatInMaschine->status)
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
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    }
}

void setze_aktuelle_Zutat_in_Maschine_prev(uint8_t nr)
{
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    aktuelleZutatAusserhalbMaschine = tail_zut_Ausserhalb_Maschine;
    for (int i = 0 ; i < nr; i++)
    {
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
        aktuelleZutatAusserhalbMaschine = aktuelleZutatAusserhalbMaschine->prev;
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
        strcpy(aktuelleZutatInMaschine->name, "(keine)");
        aktuelleZutatInMaschine->alkohol = 0;
        aktuelleZutatInMaschine->kohlensaeure=0;
        aktuelleZutatInMaschine->status = status;
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File
    if (nr == 7)
    {
        strcpy((char *)aktuelleZutatInMaschine->name, (const char *)aktuelle_zutat->name);
        aktuelleZutatInMaschine->alkohol = aktuelle_zutat->alkohol;
        aktuelleZutatInMaschine->kohlensaeure=aktuelle_zutat->kohlensaeure;
        aktuelleZutatInMaschine->status = status;
    }

    nextion_change_page(POSANZEIGE);

    // Falls innerhalb des Listenbereichs ==> Flüssigkeit aus File laden
    if (nr < 6)
    {
        // Wähle Zutaten-File, auf welches gedrückt wurde und lese es ein.
        aktuelles_zutat_file = aktuelle_zutat_list_node->zutat_xy;
        lese_textfile_in_zutat(aktuelles_zutat_file->file);
        while ((aktuelle_zutat->kohlensaeure != kohlensaeure_mode) && (aktuelles_zutat_file != head_zutat_file))
        {
            aktuelles_zutat_file = aktuelles_zutat_file->prev;
            lese_textfile_in_zutat(aktuelles_zutat_file->file);
        }

        for (uint8_t i = 0 ; i < nr ; i++)
        {
            aktuelles_zutat_file = aktuelles_zutat_file->prev;
            lese_textfile_in_zutat(aktuelles_zutat_file->file);
            while ((aktuelle_zutat->kohlensaeure != kohlensaeure_mode) && (aktuelles_zutat_file != head_zutat_file))
            {
                aktuelles_zutat_file = aktuelles_zutat_file->prev;
                lese_textfile_in_zutat(aktuelles_zutat_file->file);
            }
        }

        strcpy(aktuelleZutatInMaschine->name, aktuelle_zutat->name);
        aktuelleZutatInMaschine->status = status;
        aktuelleZutatInMaschine->alkohol = aktuelle_zutat->alkohol;
        aktuelleZutatInMaschine->kohlensaeure = aktuelle_zutat->kohlensaeure;
    }
    // Schreibe Änderung in Titel der Positionsanzeige
    strcpy((char *)buff, "Nr.");
    itoa(aktuelleZutatInMaschine->stelle+1, buff2, 10);
    strcat((char *)buff, (const char *)buff2);
    strcat((char *)buff, " = ");
    strcat((char *)buff, aktuelleZutatInMaschine->name);
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
    // Falls nr ausserhalb des Listenbereichs ==> Keine Flüssigkeit
    if (nr == 6)
    {
        // Schreibe Null-Terminator über bestehenden Namen
        strcpy(aktuelleZutatAusserhalbMaschine->name, "(keine)");
        aktuelleZutatAusserhalbMaschine->alkohol = 0;
        aktuelleZutatAusserhalbMaschine->kohlensaeure=0;
        aktuelleZutatAusserhalbMaschine->status = status;
    }

    // Falls nr ausserhalb des Listenbereichs ==> Neues File
    if (nr == 7)
    {
        strcpy((char *)aktuelleZutatAusserhalbMaschine->name, (const char *)aktuelle_zutat->name);
        aktuelleZutatAusserhalbMaschine->alkohol = aktuelle_zutat->alkohol;
        aktuelleZutatAusserhalbMaschine->kohlensaeure=aktuelle_zutat->kohlensaeure;
        aktuelleZutatAusserhalbMaschine->status = status;
    }

    // Falls innerhalb des Listenbereichs ==> Flüssigkeit aus File laden
    else
    {
        // Wähle Zutaten-File, auf welches gedrückt wurde und lese es ein.
        aktuelles_zutat_file = aktuelle_zutat_list_node->zutat_xy;
        lese_textfile_in_zutat(aktuelles_zutat_file->file);
        while ((aktuelle_zutat->kohlensaeure != kohlensaeure_mode) && (aktuelles_zutat_file != head_zutat_file))
        {
            aktuelles_zutat_file = aktuelles_zutat_file->prev;
            lese_textfile_in_zutat(aktuelles_zutat_file->file);
        }

        for (uint8_t i = 0 ; i < nr ; i++)
        {
            aktuelles_zutat_file = aktuelles_zutat_file->prev;
            lese_textfile_in_zutat(aktuelles_zutat_file->file);
            while ((aktuelle_zutat->kohlensaeure != kohlensaeure_mode) && (aktuelles_zutat_file != head_zutat_file))
            {
                aktuelles_zutat_file = aktuelles_zutat_file->prev;
                lese_textfile_in_zutat(aktuelles_zutat_file->file);
            }
        }

        uint8_t run = 1;
        aktuelleZutatAusserhalbMaschine = tail_zut_Ausserhalb_Maschine;
        do
        {
            if (strcmp(aktuelleZutatAusserhalbMaschine->name, aktuelle_zutat->name)==0)
            {
                strcpy(aktuelleZutatAusserhalbMaschine->name, aktuelle_zutat->name);
                Uart_Transmit_IT_PC(aktuelleZutatAusserhalbMaschine->name);
            }
            aktuelleZutatAusserhalbMaschine = aktuelleZutatAusserhalbMaschine->prev;
        } while (aktuelleZutatAusserhalbMaschine != tail_zut_Ausserhalb_Maschine && run ==1);

//      char buff[50] = {'\0'};
//      char buff2[5] = {'\0'};

        // Schreibe Name der gefundenen Zutat in die ausgewählte Position.
        char len = strlen((const char *)aktuelle_zutat->name);
        for (int count = 0 ; count < (len + 1) ; count++)
        {
            *(aktuelleZutatAusserhalbMaschine->name + count) = *(aktuelle_zutat->name + count);
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



    aktuelleZutatInMaschine = tail_zut_in_Maschine;

    strcpy(ptr2, "zutaten:");
    uint8_t first = 1;
    do
    {
        if (strcmp("(keine)", aktuelleZutatInMaschine->name)!=0)
        {
            if (first == 1)
            {
                strcat(ptr, aktuelleZutatInMaschine->name);
                first = 0;
            }
            else
            {
                strcat(ptr, ",");
                strcat(ptr, aktuelleZutatInMaschine->name);

            }
            counter ++;
        }
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    } while (aktuelleZutatInMaschine != tail_zut_in_Maschine);
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
            aktuelleZutatInMaschine = tail_zut_in_Maschine;
            for (int count2 = 0 ; count2 < 12 ; count2++)
            {
                if (strcmp(aktuelleZutatInMaschine->name, temp2) == 0)
                {
                    if (aktuelleZutatInMaschine->alkohol == 1)
                    {
                        alkohol = 1;
                    }
                }
                aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
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
    getraenk_file_t* next;

    while (current != head_getraenk_file)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
        in the caller. */
    head_getraenk_file = NULL;
    tail_getraenk_file = NULL;
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
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
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
        strcpy(aktuelleZutatInMaschine->name,ptr);                      // Kopiere Name in Buffer
        Uart_Transmit_IT_PC(aktuelleZutatInMaschine->name);
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Status
        Uart_Transmit_IT_PC(ptr);
        aktuelleZutatInMaschine->status = atoi(ptr);                    // Schreibe ASCI-Status in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Alkohol Ja/Nein
        aktuelleZutatInMaschine->alkohol = atoi(ptr);                   // Schreibe ASCI-JA//Nein in Integer-Buffer
        ptr = strtok(NULL, delimiter);                                  // Abschnitt Kohlensäure Ja/Nein
        aktuelleZutatInMaschine->kohlensaeure = atoi(ptr);              // Schreibe ASCI-JA//Nein in Integer-Buffer

        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    } while(aktuelleZutatInMaschine != tail_zut_in_Maschine);

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
    nextion_change_page(RFIDFEHLER);
    nextion_setText("fehlertxt", "Mixe neue Cocktailliste.\\rVerhalten Sie sich ruhig, \\rgleich können Sie auswählen.");
    free_list_getraenke();

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
    } while (aktuellesGetraenk_file_2 != tail_getraenk_file_2);

    aktuellesGetraenk_file = tail_getraenk_file;
    lese_textfile_in_getraenk(aktuellesGetraenk_file->file);
    nextion_change_page(MENUANZEIGE);
}

// Wurde Separat genommen, sodass das EEPROM mit aktuellen Drinks beschrieben werden kann für eine andere Standardeinstellung
void write_M_file(char * buff_file)
{
    char buff99[10] = {'\0'};
    aktuelleZutatInMaschine = tail_zut_in_Maschine;
    for (int count = 0 ; count < 12 ; count++)
    {
        if (count != 0)
        {
            strcat((char *)buff_file, (const char *)aktuelleZutatInMaschine->name);
        }
        else
        {
            strcpy((char *)buff_file, (const char *)aktuelleZutatInMaschine->name);
        }
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatInMaschine->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatInMaschine->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatInMaschine->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)"\r");
        aktuelleZutatInMaschine = aktuelleZutatInMaschine->prev;
    }
    strcat((char *)buff_file, (const char *)";\r");

    aktuelleZutatAusserhalbMaschine = tail_zut_Ausserhalb_Maschine;
    for (int count = 0 ; count < 12 ; count++)
    {
        strcat((char *)buff_file, (const char *)aktuelleZutatAusserhalbMaschine->name);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatAusserhalbMaschine->status, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatAusserhalbMaschine->alkohol, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        strcat((char *)buff_file, (const char *)",");
        itoa(aktuelleZutatAusserhalbMaschine->kohlensaeure, (char *)buff99, 10);
        strcat((char *)buff_file, (const char *)buff99);
        if (aktuelleZutatAusserhalbMaschine != head_zut_Ausserhalb_Maschine)
        {
            strcat((char *)buff_file, (const char *)"\r");
        }
        else
        {
            strcat(buff_file, "\r;\r~");
        }
        aktuelleZutatAusserhalbMaschine = aktuelleZutatAusserhalbMaschine->prev;
    }
    Uart_Transmit_IT_PC((char *)buff_file);

//  uint8_t len = strlen(buff_file);
//  address_Standardwiederherstellung = 0;
//  for (uint8_t xxy = 0 ; xxy <len ; xxy++)
//  {
//      eeprom_write_byte(address_Standardwiederherstellung +xxy, *(buff_file+xxy));
//  }
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