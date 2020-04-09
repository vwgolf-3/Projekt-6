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
char standardGetraenke[21][50] = {
	"sevenSeven",
	"blueKamikaze",
	"blueLagoon",
	"buckCocktails",
	"gimlet",
	"ginSin",
	"highball",
	"whiskyCola",
	"kamikaze",
	"martiniLemonDrop",
	"monkeyGland",
	"screwdriver",
	"silverBullet",
	"ward eight",
	"whiteLady",
	"sevenUp",
	"cocaCola",
	"orangensaft",
	"spezi",
	"royRogers",
	"shirleyTemple"
};	
	head = NULL;
	getraenk_t * tmp;
	for (int8_t i=0; i<21;i++)
	{
		tmp = create_new_getraenk(standardGetraenke[i],i);
		head = insert_at_head(&head, tmp);
	}
}

void showlist(void)
{
	getraenk_t * temporary= head;
	while (temporary != 0)
	{
		Uart_Transmit_IT_PC((unsigned char *)temporary->name,strlen((const char *)temporary->name));
		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		_delay_ms(50);		
		temporary = temporary->next;
	}

}

void printlist(void)
{
	getraenk_t *temporary2 = head;
	char buff[3] = {0};
	while (temporary2 != NULL){
		Uart_Transmit_IT_PC((unsigned char *)temporary2->name,strlen((const char *)temporary2->name));
		itoa(temporary2->value,buff,10);
		Uart_Transmit_IT_PC((uint8_t *)buff,strlen((const char *)buff));
		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		_delay_ms(1);
		temporary2 = temporary2->next;
	}
}

int8_t length_list(void)
{
	getraenk_t *tmp = head;
	int8_t n = 0;
	while (tmp != NULL){
		n++;
		tmp = tmp->next;
	}
// 		char buff[3] = {0};
// 		itoa(n,buff,10);
// 		Uart_Transmit_IT_PC((uint8_t *)buff,strlen((const char *)buff));
// 		Uart_Transmit_IT_PC((uint8_t *)"\n\r",strlen((const char *)"\n\r"));
		return n;
}


getraenk_t *create_new_getraenk(char * name, int8_t value)
{
	getraenk_t *result = calloc(1,sizeof(getraenk_t));
	size_t n = strlen((const char *)name)+1;
	result->name = calloc(n,sizeof(char));
	result->value = value;
	result->next = NULL;
	
    int i;
    for (i=0; i<(n); i++)
	{
    *(char *)(result->name + i) = *(char *)(name + i);
	}
	return result;
}

getraenk_t *insert_at_head(getraenk_t **head, getraenk_t *getraenk_to_insert)
{
	getraenk_to_insert->next = *head;
	*head = getraenk_to_insert;
	return getraenk_to_insert;
}

getraenk_t *find_getraenk(getraenk_t *head, char * name)
{
	getraenk_t *tmp = head;
	while (tmp != NULL)
	{
		if(tmp->name == name)	return tmp;
		tmp = tmp->next;
	}
	return NULL;
}

void insert_after_getraenk(getraenk_t *getraenk_to_insert_after, getraenk_t* newgetraenk)
{
	newgetraenk->next = getraenk_to_insert_after->next;
	getraenk_to_insert_after->next = newgetraenk;
}