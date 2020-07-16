/*
 * Software_SPI.c
 *
 * Created: 15.07.2020 10:50:33
 * Author : kimsc
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

#include "pin_defs.h"
#include "Software_SPI_lib.h"
#include "RC522/mfrc522.h"

int main(void)
{
	softspi_setup_master();
	mfrc522_init();											// RFID initialisieren
    /* Replace with your application code */
    while (1) 
    {
	mfrc522_init();											// RFID initialisieren
		_delay_ms(30000);
    }
}
