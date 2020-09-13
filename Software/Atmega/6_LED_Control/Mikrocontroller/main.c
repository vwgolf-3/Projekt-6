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
    init_LED();

    interfaces_init();

    // Mainroutine
    while (1)
    {

        check_Communication_Input_UART();                   // Prüfen. ob über UART einen Befehl geesendet wurde
        if (process == 1)
        {
            light = RAINBOW_LED;
            // Timer 1 wird von System Clock abgehängt und zugehörige LED ausgeschaltet
            TIMER_CONTROL_REGISTER_B_WHITE &= ~(1 << CS10);        // CTC-Mode, prescaler 1
            LEDW_PORT &= ~LEDW_BIT;

            // Timer 3/4/5 wird an System Clock angehängt
            TIMER_CONTROL_REGISTER_B_RED |= (1 << CS30);        // CTC-Mode, prescaler 1
            TIMER_CONTROL_REGISTER_B_GREEN |= (1 << CS40);      // CTC-Mode, prescaler 1
            TIMER_CONTROL_REGISTER_B_BLUE |= (1 << CS50);       // CTC-Mode, prescaler 1
			process = 0;
        }
        if (process == 2)
        {
            // Timer 1 wird an System Clock angehängt
            TIMER_CONTROL_REGISTER_B_WHITE |= (1<<CS10);        // Prescaler 1024

            // Timer 3/4/5 wird von System Clock angehängt und zugehörige LEDs ausgeschaltet
            TIMER_CONTROL_REGISTER_B_RED &= ~(1 << CS30);
            TIMER_CONTROL_REGISTER_B_GREEN &= ~(1 << CS40);
            TIMER_CONTROL_REGISTER_B_BLUE &= ~(1 << CS50);
            LEDR_PORT &= ~LEDR_BIT;
            LEDG_PORT &= ~LEDG_BIT;
            LEDB_PORT &= ~LEDB_BIT;
 			process = 0;
       }
    }
    return 0;                                               // Loop erneut beginnen
}