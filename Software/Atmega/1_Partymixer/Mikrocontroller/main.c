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

// *****************************************************************************************************************


// MainLoop
int main(void)
{
    interfaces_init();			// IO, UART, SPI
//     init_LED();					// PWM
	schalte_pumpe_ein(0);
	_delay_ms(500);
	schalte_pumpe_aus(0);
    devices_init();				// SD-Card, Motor
    speicher_init();			// Cocktails, Zutaten Tags
    ramp_init();				// Software-Ramp


    ramp_pwm_init();

    Position = 0;
    compute = 0;

    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);                  // Startanzeige des Displays setzen
	Liste = ALLE;
	
    // Mainroutine
    while (1)
    {
        periodic_jobs(ramp);
    }
    return 0;                                               // Loop erneut beginnen
}
