/*
 * Motor.c
 *
 * Created: 15.07.2020 20:34:28
 * Author : kimsc
 */

#include "pin_defs.h"
#include "main_variables.h"                         // "Global" includbare Variabeln deklarieren
#include "libraries/SPI/SPI.h"
#include "libraries/UART/UART.h"
#include "libraries/Main_functions/Main_Func.h"
#include "libraries/TMC6200/TMC6200.h"
#include "libraries/TMC4671/TMC4671.h"
#include "libraries/Software_Ramp/ramp1.h"

int main(void)
{
    IO_init();                                              // Ein-/Ausgangspins initialisieren
    SPI_init();                                             // SPI-Schnittstelle initialisieren
    UART_init();                                            // UART-Schnittstelle initialisieren
    initTMC6200();                                          // Gate-Treiber initialisieren
    initTMC4671_Openloop();                                  // FOC-Treiber initialisieren

    Position = 0;

    linear_ramp_t Ramp;
    linear_ramp_t * ramp = &Ramp;

    linear_ramp_init(ramp);
    linear_ramp_set_defaults(ramp);
    states = IDLE;

    while (1)
    {
        // Wird ein CR eingegeben durch dücken der Enter-Taste, inkrementiert die Position
        // Wird '0' eingegeben, so Springt der Motor auf Position 0 wie zu Beginn.
        // WIrd '1' eingegeben, so läuft ein Testskript durch 12 Positionen und dann wieder an die Startposition.
        // WIrd '2' eingegeben, so wird die Variable Position = 1 gesetzt und die Software-Ramp in der Main-Routine aktiviert.
		// Wird nur ein '\r' eingegeben, so springt der Motor jeweils um 10000000 Schritte.

        if ((Position == 1) && (ramp->ramp_enable == 0))
        {
            tmc4671_writeInt(0, 0x6B,                0x00000000);        // writing value 0x00000003 = 3 = 0.0 to address 67 = 0x63(MODE_RAMP_MODE_MOTION)
            tmc4671_setAbsolutTargetPosition(0, 0x00000000);            // Überprüfen der Maximalwerte, bei zu hohen Eingaben wird automatisch
            calculateRamp(1000, 1000, 5000, ramp);
            Position = 0;
        }
		if (ramp->ramp_enable)
		{
	       computeRamp(ramp);
	       tmc4671_setAbsolutTargetPosition(0, (uint32_t)(ramp->ramp_position * 1000));
		}
		read_registers_TMC4671();
        check_Communication_Input_UART();
		_delay_ms(2000);
    }
}