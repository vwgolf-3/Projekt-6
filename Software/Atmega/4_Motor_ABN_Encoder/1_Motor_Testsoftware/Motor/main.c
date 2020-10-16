/*
 * Motor.c
 *
 * Created: 15.07.2020 20:34:28
 * Author : kimsc
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include "pin_defs.h"
#include "main_variables.h"                         // "Global" includbare Variabeln deklarieren
#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"
#include "libraries/Main_functions/Main_Func.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/TMC4671/TMC4671.h"

uint32_t cntrr = 0;
uint8_t show_serial_port = 1;
void read_Position_TMC4671(void);


int main(void)
{
    IO_init();                                              // Ein-/Ausgangspins initialisieren
    SPI_init();                                             // SPI-Schnittstelle initialisieren
    UART_init();                                            // UART-Schnittstelle initialisieren
    initTMC6200();                                          // Gate-Treiber initialisieren
    initTMC4671_Encoder();                                  // FOC-Treiber initialisieren

    while (1)
    {
        // Wird ein CR eingegeben durch dücken der Enter-Taste, inkrementiert die Position
        // Wird '0' eingegeben, so Springt der Motor auf Position 0 wie zu Beginn.
		// WIrd '1' eingegeben, so läuft ein Testskript durch 12 Positionen und dann wieder an die Startposition.

        check_Communication_Input_UART();
		
		read_registers_TMC4671();
		read_registers_TMC6200();
		_delay_ms(5000);
    }
}

