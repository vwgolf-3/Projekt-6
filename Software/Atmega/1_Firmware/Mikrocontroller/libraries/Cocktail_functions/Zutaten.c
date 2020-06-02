/*
 * Zutaten.c
 *
 * Created: 19.05.2020 20:10:22
 *  Author: kimsc
 */ 

#include "Zutaten.h"


void zutaten_init(void)
{
	address_zut  = (uint8_t *)0;

	uint8_t standardAlkohol[12] = {
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		1,
		1,
		1,
		1,
		1,
	};

	char zutaten[12][20] = {
		"7Up",
		"Coca-Cola",
		"Ginger-Ale",
		"Orangensaft",
		"Limettensaft",
		"Zitronensaft",
		"Grenadinensirup",
		"Blue Curacao",
		"Gin",
		"Triple Sec",
		"Whisky",
		"Wodka"
	};
	
	head_zut = NULL;
	zutat_t *tmp;
 	for ( int i = 0 ; i<12;i++){
	tmp = create_neue_zutat(zutaten[i], i);
	head_zut = insert_zutat_at_head(&head_zut, tmp);
 	}
}

zutat_t *create_neue_zutat(char * name, char k)
{
	zutat_t *newZutat = calloc(1,sizeof(zutat_t));
 	size_t n1 = strlen((const char *)name)+1;

 	newZutat->name = calloc(n1,sizeof(char));
	 
	newZutat->nr = k;
	newZutat->prev = NULL;
	newZutat->next = NULL;
	 
	int i = 0;
 	for (i=0; i<(n1-1); i++)
 	{
 		*(char *)(newZutat->name + i) = *(char *)(name + i);
 	}
	 	*(char *)(newZutat->name + (i+1)) = '\0';


	return newZutat;
}

zutat_t *insert_zutat_at_head(zutat_t **head_zut, zutat_t *zutat_to_insert)
{
	zutat_to_insert->next = (*head_zut);
	zutat_to_insert->prev = NULL;
	
	if((*head_zut) == NULL)
	{
		tail_zut = zutat_to_insert;
	} else
	{
		(*head_zut)->prev = zutat_to_insert;
		zutat_to_insert->prev = tail_zut;
	}
	*head_zut = zutat_to_insert;
	tail_zut->next = *head_zut;
	return zutat_to_insert;
}
