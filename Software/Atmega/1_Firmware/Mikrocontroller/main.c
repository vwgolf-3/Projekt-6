/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einbinden der eigenen Bibliotheken
#include "utils/main_variables.h"							// "Global" includbare Variabeln deklarieren
#include "libraries/Main_functions/Main_Func.h"				// Wird benötigt für Funktionen, welche im Hauptprogrammfluss aufgerufen werden (z. B IO_init, Check_communication, SD_Startup(), zutaten_init(), cocktails_init()...)

// MainLoop
int main(void)
{
	// Gate Treiber disable (active high)
 	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;						// Disable TMC6200 (Active High)

	interfaces_init();
	devices_init();
	speicher_init();
	
	setze_startanzeige(aktuellesGetraenk);
		
// Mainroutine
	while (1)
	{		check_Communication_Input_UART();					// Prüfen. ob über UART einen Befehl geesendet wurde
// 		heartbeat_LED();									// Loop-Delay und Prüf-LED, ob uC hängen bleibt
// 		check_Communication_Input_MFRC522();				// Prüfen, ob ein RFID-Tag erkannt wurde
	}
	return 0;												// Loop erneut beginnen
}