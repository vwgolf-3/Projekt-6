/*
 * Getraenk.h
 *
 * Created: 05.04.2020 22:46:11
 *  Author: kimsc
 */ 


#ifndef GETRAENK_H_
#define GETRAENK_H_

#include "../SPI/SPI_Defines.h"
#include "../UART/UART.h"
#include "../SPI/SPI.h"
#include "../TMC4671/TMC4671.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../../Main_Func/Main_Func.h"

struct getraenk{
	char * name;
	int8_t value;
	struct getraenk* next;
};
typedef struct getraenk getraenk_t;

getraenk_t *head;
char eigeneGetraenke[20][20];
void cocktails_init(void);
void printlist(void);

getraenk_t * find_getraenk(getraenk_t *head, char * name);
getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert);
getraenk_t *create_new_getraenk(char * name, int8_t value);
void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t *newnode);
void showlist (void);
int8_t length_list(void);


#endif /* GETRAENK_H_ */