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
//  	EN_TMC6200_PORT |= EN_TMC6200_BIT;						// Disable TMC6200 (Active High)
	
// Initialisierungen Interfaces
	IO_init();												// Ein-/Ausgangspins initialisieren
	SPI_init();												// SPI-Schnittstelle initialisieren
	UART_init();											// UART-Schnittstelle initialisieren
	nextion_change_page(FEHLERANZEIGE);
	nextion_setText("fehlertxt","Initialisierung SD-Karte...");
	mfrc522_init();											// RFID initialisieren
	SD_startup();											// SD-Karte initialisieren
// 	initTMC6200();											// Gate-Treiber initialisieren
// 	TMC4671_init();											// FOC-Treiber initialisieren
// 	initTMC4671_Openloop();									// FOC-Treiber im Openloop laufen lassen

// Initialisierungen Speicher
	Uart_Transmit_IT_PC("\r");
	nextion_setText("fehlertxt","Initialisierung Zutaten...");
	Uart_Transmit_IT_PC("Initialisierung Zutaten...");
	Uart_Transmit_IT_PC("\r");
	zutaten_init();											// Zutaten initialisieren
	nextion_setText("fehlertxt","Initialisierung Cocktails...");
	Uart_Transmit_IT_PC("Initialisierung Cocktails...");
	Uart_Transmit_IT_PC("\r");
	cocktails_init();										// Cocktails initialisieren
	nextion_setText("fehlertxt","Initialisierung RFID...");
	Uart_Transmit_IT_PC("Initialisierung RFID...");
	Uart_Transmit_IT_PC("\r");
	RFID_init();

// Initialisierungen Display
	setze_startanzeige(aktuellesGetraenk);					// Startanzeige des Displays setzen
	Grossschreib = 1;										// Initialisiere Grossschreibung Display mit gross (gibt kein Display init();)
	i_Liste = 0;											// Listenabschnitt auf 0 vordefinieren
	i_Liste_test_cnt = 0;
	i_Liste_test[i_Liste_test_cnt] = 0;
	block_list_hoch = 0;									// Blockierung der Listen aufheben
	block_list_runter = 0;									// Blockierung der Listen aufheben
				
// Mainroutine
	while (1)
	{		check_Communication_Input_UART();					// Prüfen. ob über UART einen Befehl geesendet wurde
// 		heartbeat_LED();									// Loop-Delay und Prüf-LED, ob uC hängen bleibt
		check_Communication_Input_MFRC522();				// Prüfen, ob ein RFID-Tag erkannt wurde
		_delay_ms(1000);
	}
	return 0;												// Loop erneut beginnen
}