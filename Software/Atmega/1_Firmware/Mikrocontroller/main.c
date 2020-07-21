/*
* Mikrocontroller.c
*
* Created: 29.11.2019 20:37:01
* Author : kimsc
*/

// Einbinden der eigenen Bibliotheken
#include "utils/main_variables.h"							// "Global" includbare Variabeln deklarieren
#include "libraries/Main_functions/Main_Func.h"				// Wird ben�tigt f�r Funktionen, welche im Hauptprogrammfluss aufgerufen werden (z. B IO_init, Check_communication, SD_Startup(), zutaten_init(), cocktails_init()...)

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
	{		check_Communication_Input_UART();					// Pr�fen. ob �ber UART einen Befehl geesendet wurde
// 		heartbeat_LED();									// Loop-Delay und Pr�f-LED, ob uC h�ngen bleibt
// 		check_Communication_Input_MFRC522();				// Pr�fen, ob ein RFID-Tag erkannt wurde
	}
	return 0;												// Loop erneut beginnen
}