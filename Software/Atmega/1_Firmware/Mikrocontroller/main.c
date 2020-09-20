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
void ramp_pwm_init(void)
{
	TCCR2B |= (1 << WGM21)|(1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	OCR2A = 250;
}
// MainLoop
int main(void)
{
    init_LED();

    interfaces_init();

    devices_init();

//     speicher_init();
	
    Position = 0;

linear_ramp_t Ramp;
linear_ramp_t * ramp = &Ramp;

    linear_ramp_init(ramp);
    linear_ramp_set_defaults(ramp);
	
    states = IDLE;

    nextion_change_page(STARTANZEIGE);

    setze_startanzeige(aktuellesGetraenk);                  // Startanzeige des Displays setzen
// 	ramp_pwm_init();
    // Mainroutine
    while (1)
    {
        if ((Position == 1) && (ramp->ramp_enable == 0))
        {
	        tmc4671_writeInt(0, 0x6B,                0x00000000);        // writing value 0x00000003 = 3 = 0.0 to address 67 = 0x63(MODE_RAMP_MODE_MOTION)
	        tmc4671_setAbsolutTargetPosition(0, 0x00000000);            // Überprüfen der Maximalwerte, bei zu hohen Eingaben wird automatisch
	        calculateRamp(2000, 2000, count_bla * 10 * ramp->motor_eine_umdrehung, ramp);
	        Position = 0;
        }
	if (ramp->ramp_enable)
	{
		computeRamp(ramp);
	}
	check_Communication_Input_UART();                   // Prüfen. ob über UART einen Befehl geesendet wurde
    }
    return 0;                                               // Loop erneut beginnen
}
// 
// ISR(TIMER2_COMPA_vect)
// {
// 		computeRamp(ramp);
// }
