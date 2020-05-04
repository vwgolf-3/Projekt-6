/*
 * Cocktail_functions.h
 *
 * Created: 07.03.2020 13:45:25
 *  Author: kimsc
 */ 


#ifndef COCKTAIL_FUNCTIONS_H_
#define COCKTAIL_FUNCTIONS_H_

#include "../SPI/SPI_Defines.h"
#include "../UART/UART.h"
#include "../SPI/SPI.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../../Main_Func/Main_Func.h"
#include "../Getraenk/Getraenk.h"
#include <string.h>
#include <avr/eeprom.h>

void cocktail_check_command(char page, char button);
void cocktail_do_command1(void);
void cocktail_do_command2(void);
void cocktail_test_command(unsigned char INPUT[256]);
void fuelle_getraenk(uint8_t * mengen, uint16_t fuellmenge);
void butt(void);
void evalSensor(void);
#endif /* COCKTAIL_FUNCTIONS_H_ */