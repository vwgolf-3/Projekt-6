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
	
	address  = (uint8_t *)0;

	char standardGetraenke[21][50] = {
		"7 & 7",
		"Blue Kamikaze",
		"Blue Lagoon",
		"Buck Cocktails",
		"Gimlet",
		"Gin Sin",
		"Highball",
		"Whisky Cola",
		"Kamikaze",
		"Martini Lemon Drop",
		"Monkey Gland",
		"Screwdriver",
		"Silver Bullet",
		"Ward 8",
		"WhiteLady",
		"7-Up",
		"Coca Cola",
		"Orangensaft",
		"Spezi",
		"Roy Rogers",
		"Shirley Temple"
	};

	uint8_t standardZutaten[21][12] = {
		{75,0,0,0,0,0,0,0,0,0,0,25},
		{0,0,0,0,33,0,0,34,0,0,0,33},
		{66,0,0,0,0,0,0,17,0,0,0,17},
		{0,0,60,0,7,0,0,0,0,0,0,33},
		{0,0,0,0,15,0,15,0,70,0,0,0},
		{0,0,0,40,0,15,5,0,40,0,0,0},
		{0,0,70,0,0,0,0,0,0,0,30,0},
		{0,70,0,0,0,0,0,0,0,0,30,0},
		{0,0,0,0,35,0,0,0,0,35,0,30},
		{0,0,0,0,0,25,0,0,0,34,0,41},
		{0,0,0,35,0,0,5,0,60,0,0,0},
		{0,0,0,65,0,0,0,0,0,0,0,35},
		{0,0,0,0,0,10,0,0,60,0,30,0},
		{0,0,0,15,0,10,5,0,0,0,70,0},
		{0,0,0,0,0,15,0,0,50,35,0,0},
		{100,0,0,0,0,0,0,0,0,0,0,0},
		{0,100,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,100,0,0,0,0,0,0,0,0},
		{50,50,0,0,0,0,0,0,0,0,0,0},
		{0,95,0,0,0,0,5,0,0,0,0,0},
		{45,0,45,0,0,0,10,0,0,0,0,0}
	};

	uint8_t standardAlkohol[21] = {
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		0,
		0,
		0,
		0,
		0,
		0
	};

// 	char zutaten[12][50] = {
// 		"7Up",
// 		"Coca-Cola",
// 		"Ginger-Ale",
// 		"Orangensaft",
// 		"Limettensaft",
// 		"Zitronensaft",
// 		"Grenadinensirup",
// 		"Blue Curacao",
// 		"Gin",
// 		"Triple Sec",
// 		"Whisky",
// 		"Wodka",
// 	};

	head = NULL;
	getraenk_t * tmp;
	
	for (int8_t i=0; i<21;i++)
	{
		tmp = create_new_getraenk(standardGetraenke[i],i,(uint8_t *)standardZutaten[i],standardAlkohol[i]);
		head = insert_at_head(&head, tmp);
	}
	
	add_EEPROM_drinks_to_list((uint8_t *) 0);

	showlist();
}

void showlist(void)
{
	getraenk_t * temporary= head;
 	char buff[3] = {0};
	char buff2[3] = {0};
	while (temporary != 0)
	{
		Uart_Transmit_IT_PC((uint8_t *)"Name: ");
		Uart_Transmit_IT_PC((uint8_t *)temporary->name);
		_delay_ms(1);
	
 		itoa(temporary->value,buff,10);
		Uart_Transmit_IT_PC((uint8_t *)": Wert = ");
		Uart_Transmit_IT_PC((uint8_t *)buff);
		
 		Uart_Transmit_IT_PC((uint8_t *)", Mengen = ");
		Uart_Transmit_IT_PC((uint8_t *)temporary->mengen);
		
		Uart_Transmit_IT_PC((uint8_t *)", Alkohol = ");
 		itoa(temporary->alkohol,buff2,10);
		Uart_Transmit_IT_PC((uint8_t *)buff2);
		
 		Uart_Transmit_IT_PC((uint8_t *)".\n\r");
		_delay_us(500);

		temporary = temporary->next;
	}

}

void printlist(void)
{
	getraenk_t *temporary2 = head;
	char buff[3] = {0};
	while (temporary2 != NULL){
		Uart_Transmit_IT_PC((unsigned char *)temporary2->name);
		itoa(temporary2->value,buff,10);
		Uart_Transmit_IT_PC((uint8_t *)buff);
		Uart_Transmit_IT_PC((uint8_t *)"\n\r");
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


getraenk_t *create_new_getraenk(char * name, uint8_t value, uint8_t * mengen, uint8_t alkohol)
{
	getraenk_t *result = calloc(1,sizeof(getraenk_t));
	
	size_t n1 = strlen((const char *)name)+1;
	size_t n2 = strlen((const char *)mengen)+1;
	
	result->name = calloc(n1,sizeof(char));
	result->mengen = calloc(n2,sizeof(char));
	
	result->alkohol = alkohol;
	result->value = value;
	
	result->next = NULL;
	
	int i = 0;
    for (i=0; i<(n1-1); i++)
    {
	    *(char *)(result->name + i) = *(char *)(name + i);
    }
	*(char *)(result->name + (i+1)) = *(char *)(name + (i+1));
	
	
    for (i=0; i<(n2-1); i++)
    {
	    *(char *)(result->mengen + i) = *(char *)(mengen + i);
    }
	*(char *)(result->mengen + (i+1)) = *(char *)(mengen + (i+1));

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



void add_drink_to_eeprom(uint8_t * add, char * name, uint8_t * mengen, uint8_t value, uint8_t alkohol)
{
	int i = 0;
	uint8_t n = strlen((const char *) name );
	char temp_name[n];
	char temp_mengen[12];
	
	strncpy(temp_name, (const char *)name, n);
	strncpy(temp_mengen, (const char *)mengen, 12);
	
	eeprom_write_byte(add,n);
	
	for(i = 0; i<n ; i++)
	{
		eeprom_write_byte((add+i+1), temp_name[i]);
		_delay_ms(5);
	}

	for(i = n; i<(n+12) ; i++)
	{
		eeprom_write_byte((add+i+1), temp_mengen[i]);
		_delay_ms(5);
	}
		
	
	i++;
	eeprom_write_byte((add+i+1),value);
	
	i++;
	eeprom_write_byte((add+i+1),alkohol);
	
	_delay_ms(5);

	i++;
	eeprom_write_byte((add+i+1),'\0');
	
	address = add+i+1;
}

int8_t count_eeprom_drinks(uint8_t * add)
{
	int8_t cnt = 0;
	int8_t val = 0;
	int8_t n = 0;
	do 
	{
		cnt++;
		val = eeprom_read_byte(add+n);
		if(n == '\0')
		{
			return cnt;
		}
		n += val + 15 + 1;
		add += n;
	}while (n !='\0');
	return 0;
}

getraenk_t * read_drink_from_eemprom(uint8_t * add)
{
	
	getraenk_t * drink;
	
	int i = 0;
	uint8_t n = eeprom_read_byte(add);					// Schauen, wie lang der String ist
	char name[n];
	uint8_t mengen [12];
	uint8_t value = 0;
	uint8_t alkohol = 0;
	
	for (i = 0; i<n ; i++)
	{
		*(name+i) = eeprom_read_byte(add+i+1);			// Schreibe Name Byte für Byte in übergebenen Speicher-Pointer (uint8_t name *)
		_delay_ms(5);
	}
	*(name+i)='\0';										// Beende Array mit Terminator '\0'
	_delay_ms(5);

	for(i = n; i<(n+12) ; i++)
	{
		*(mengen+i) = eeprom_read_byte((add+i+1));		// Schreibe Mengen Byte für Byte in üergebenen Speicher-Pointer (uint8_t mengen *)
		_delay_ms(5);
	}
	*(mengen+i)='\0';									// Beende Array mit Terminator '\0'
	_delay_ms(5);
	
	i++;
	value = eeprom_read_byte(add+i+1);					// Value aus EEPROM lesen und in Variable ablegen
	
	i++;
	alkohol = eeprom_read_byte(add+i+1);				// Alkoholgehalt aus EEPROM lesen und in Variable ablegen
	
	_delay_ms(5);
	
	drink = create_new_getraenk(name, value, mengen, alkohol);
	
	i++;
	address = add+i+1;
	
	return drink;

}

void add_EEPROM_drinks_to_list(uint8_t * add)
{
	getraenk_t * drink = 0;
	
	while (eeprom_read_byte(address) != '\0')
	{
		drink = read_drink_from_eemprom(address);
		insert_at_head(&head, drink);
	}
}

void delete_EEPROM (uint8_t * add)
{
	for(int i = 0 ; i<4059 ; i++)
	{
		eeprom_write_byte(add+i,'\0');
	}
}