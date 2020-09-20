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

void periodic_jobs(linear_ramp_t * ramp);
void ramp_pwm_init(void);

    volatile linear_ramp_t Ramp;
    volatile linear_ramp_t * ramp = &Ramp;
	
// MainLoop
int main(void)
{
    init_LED();
	
    ramp_pwm_init();

    interfaces_init();

    devices_init();

    speicher_init();

    Position = 0;
    compute = 0;

    linear_ramp_init(ramp);
    linear_ramp_set_defaults(ramp);

    nextion_change_page(STARTANZEIGE);
    setze_startanzeige(aktuellesGetraenk);                  // Startanzeige des Displays setzen
	
    // Mainroutine
    while (1)
    {
        periodic_jobs(ramp);
    }
    return 0;                                               // Loop erneut beginnen
}

ISR(TIMER2_COMPA_vect)
{
	computeRamp(ramp);
}

void ramp_pwm_init(void)
{
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	OCR2A = 250;
}