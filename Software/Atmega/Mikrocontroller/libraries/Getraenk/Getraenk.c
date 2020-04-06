/*
 * Getraenk.c
 *
 * Created: 05.04.2020 22:46:46
 *  Author: kimsc
 */ 

#include "Getraenk.h"

// https://www.youtube.com/watch?v=VOpjAHCee7c

void cocktails_init(void)
{
uint8_t *standardGetraenke[] = {
	(uint8_t *)"sevenSeven",
	(uint8_t *)"blueKamikaze",
	(uint8_t *)"blueLagoon",
	(uint8_t *)"buckCocktails",
	(uint8_t *)"gimlet",
	(uint8_t *)"ginSin",
	(uint8_t *)"highball",
	(uint8_t *)"whiskyCola",
	(uint8_t *)"kamikaze",
	(uint8_t *)"martiniLemonDrop",
	(uint8_t *)"monkeyGland",
	(uint8_t *)"screwdriver",
	(uint8_t *)"silverBullet",
	(uint8_t *)"ward eight",
	(uint8_t *)"whiteLady",
	(uint8_t *)"sevenUp",
	(uint8_t *)"cocaCola",
	(uint8_t *)"orangensaft",
	(uint8_t *)"spezi",
	(uint8_t *)"royRogers",
	(uint8_t *)"shirleyTemple"
};	
	head = NULL;
	getraenk_t * tmp;
	for (int8_t i=0; i<21;i++)
	{
		tmp = create_new_getraenk(standardGetraenke[i],i);
		head = insert_at_head(&head, tmp);
	}
	showlist();
	length_list();
}

void lege_eigenes_Getraenk_ab(uint8 * getraenk_to_add)
{
uint8_t *eigeneGetraenke[20] = {0};
	int n = 0;
	while (eigeneGetraenke[n] != 0)
	{
		eigeneGetraenke[n] = getraenk_to_add;
		n++;
	}
}

void showlist(void)
{
	getraenk_t * tmp;
	int8_t len = length_list();
	for (int8_t i=0; i<len;i++)
	{
		tmp = find_getraenk(head, i);
		Uart_Transmit_IT_PC(tmp->name,strlen((const char *)tmp->name));
		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		_delay_ms(2);
	}
}

void printlist(void)
{
	getraenk_t *temporary = head;
	char buff[2] = {0};
	while (temporary != NULL){
		Uart_Transmit_IT_PC(temporary->name,strlen((const char *)temporary->name));
		itoa(temporary->value,buff,10);
		Uart_Transmit_IT_PC((uint8_t *)buff,strlen((const char *)buff));
		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		_delay_ms(1);
		temporary = temporary->next;
	}
}

int8_t length_list(void)
{
	char buff[3] = {0};
	getraenk_t *tmp = head;
	int8_t n = 0;
	while (tmp != NULL){
		n++;
		tmp = tmp->next;
	}
		itoa(n,buff,10);
		Uart_Transmit_IT_PC((uint8_t *)buff,strlen((const char *)buff));
		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		return n;
}


getraenk_t* create_new_getraenk(uint8_t * name, int8_t value)
{
	getraenk_t *result = malloc (sizeof(getraenk_t));
	result->name = name;
	result->value = value;
	result->next = NULL;
	return result;
}

getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert)
{
	getraenk_to_insert->next = *head;
	*head = getraenk_to_insert;
	return getraenk_to_insert;
}

getraenk_t *find_getraenk(getraenk_t *head, int8_t value)
{
	getraenk_t *tmp = head;
	while (tmp != NULL)
	{
		if(tmp->value == value)	return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t* newgetraenk)
{
	newgetraenk->next = getraenk_to_insert_after->next;
	getraenk_to_insert_after->next = newgetraenk;
}