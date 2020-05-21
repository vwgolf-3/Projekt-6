/*
 * Cocktail_functions.h
 *
 * Created: 07.03.2020 13:45:25
 *  Author: kimsc
 */ 


#ifndef COCKTAIL_FUNCTIONS_H_
#define COCKTAIL_FUNCTIONS_H_



#include "../../pin_defs.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../../Zutaten.h"
#include "../Getraenk/Getraenk.h"
#include "../TMC6200/TMC6200.h"

void init_Getraenke_func();
void cocktail_check_command(char page, char button);
void cocktail_test_command(unsigned char INPUT[256]);
void fuelle_getraenk(uint16_t fuellmenge);
void setze_port(void);
void schalte_pumpe_aus(uint8_t Pumpe);
void schalte_pumpe_ein(uint8_t Pumpe);
getraenk_t * shift_getraenk(getraenk_t *getraenk_to_shift, uint8_t ngetr, uint8_t down_up);
void setze_startanzeige(getraenk_t * anzeige_getraenk);
void erstelle_Zutatenliste(getraenk_t * anzeige_getraenk);

#endif /* COCKTAIL_FUNCTIONS_H_ */