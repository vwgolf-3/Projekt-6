/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einbinden der eigenen Bibliotheken
#include "utils/main_variables.h"                           // "Global" includbare Variabeln deklarieren
#include "libraries/Main_functions/Main_Func.h"             // Wird benötigt für Funktionen, welche im Hauptprogrammfluss aufgerufen werden (z. B IO_init, Check_communication, SD_Startup(), zutaten_init(), cocktails_init()...)
#include "libraries/Cocktail_functions/Cocktail_Statemachine.h"

// MainLoop
int main(void)
{
//     init_LED();
// 
//     PWM_init();

    interfaces_init();

    devices_init();

//     speicher_init();

//     nextion_change_page(STARTANZEIGE);

//     setze_startanzeige(aktuellesGetraenk);                  // Startanzeige des Displays setzen

    // Mainroutine
    while (1)
    {
        check_Communication_Input_UART();                   // Prüfen. ob über UART einen Befehl geesendet wurde
    }
    return 0;                                               // Loop erneut beginnen
}