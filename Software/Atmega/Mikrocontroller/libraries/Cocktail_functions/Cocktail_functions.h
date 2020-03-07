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

void check_command(char page, char button);
void do_command1(void);
void do_command2(void);



#endif /* COCKTAIL_FUNCTIONS_H_ */