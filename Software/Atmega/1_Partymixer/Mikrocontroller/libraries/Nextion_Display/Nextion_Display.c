/*
 * Nextion_Display.c
 *
 * Created: 02.01.2020 18:13:59
 *  Author: kimsc
 */

#include "Nextion_Display.h"

void nextion_change_page(char page)
{
    char * pge = "page ";
    char buff[3] = {0};
    itoa((page-1),(char *)buff,10);
    Uart_Transmit_IT_Display(pge);
    Uart_Transmit_IT_Display((char *)buff);

    endConversation();
}

void nextion_setText(char * object, char * text)
{
    char * txt = ".txt=";
    char * slash = "\"";
    Uart_Transmit_IT_Display(object);
    Uart_Transmit_IT_Display(txt);
    Uart_Transmit_IT_Display(slash);
    Uart_Transmit_IT_Display(text);
    Uart_Transmit_IT_Display(slash);

    endConversation();
}

void nextion_setValue( char * object,  char * value)
{
    char * val = ".val=";
    Uart_Transmit_IT_Display(object);
    Uart_Transmit_IT_Display(val);
    Uart_Transmit_IT_Display(value);

    endConversation();
}

void nextion_setPicture( char * x,  char * y,  char * picture)
{
    char * pic = "pic ";
    char * komma = ",";
    Uart_Transmit_IT_Display(pic);
    Uart_Transmit_IT_Display(x);
    Uart_Transmit_IT_Display(komma);
    Uart_Transmit_IT_Display(y);
    Uart_Transmit_IT_Display(komma);
    Uart_Transmit_IT_Display(picture);

    endConversation();
}

uint8_t nextion_getSliderValue(char * object, unsigned char * INPUT)
{
    uint8_t ret = 0;

    char buff[30] = {0};
    char * get_slider = "get ";
    char * val = ".val";

    strcat((char *)buff, (const char *)get_slider);
    strcat((char *)buff, (const char *)object);
    strcat((char *)buff, (const char *)val);
    Uart_Transmit_IT_Display((char *) buff);
    endConversation();

    while (check_Communication_Input_UART_1()==0)
        ;

    if (INPUT_UART_1[1]==255)
    {
        ret = 0;
    }
    else
    {
        ret = INPUT_UART_1[1];
    }
    return ret;
}

void nextion_disableButton(char * object)
{
    char buff10[20] = {'\0'};
    strcpy((char *)buff10, (const char *)"tsw ");
    strcat((char *)buff10, (const char *)object);
    strcat((char *)buff10, (const char *)",0");

    Uart_Transmit_IT_Display((char *)buff10);

    endConversation();
}

void nextion_enableButton(char * object)
{
    char buff10[20] = {'\0'};
    strcpy((char *)buff10, (const char *)"tsw ");
    strcat((char *)buff10, (const char *)object);
    strcat((char *)buff10, (const char *)",1");

    Uart_Transmit_IT_Display((char *)buff10);

    endConversation();
}

void nextion_visible_off(char * object)
{
    char buff10[20] = {'\0'};
    strcpy((char *)buff10, (const char *)"vis ");
    strcat((char *)buff10, (const char *)object);
    strcat((char *)buff10, (const char *)",0");

    Uart_Transmit_IT_Display((char *)buff10);

    endConversation();
}

void nextion_visible_on(char * object)
{
    char buff10[20] = {'\0'};
    strcpy((char *)buff10, (const char *)"vis ");
    strcat((char *)buff10, (const char *)object);
    strcat((char *)buff10, (const char *)",1");

    Uart_Transmit_IT_Display((char *)buff10);

    endConversation();
}


void endConversation(void)
{
    unsigned char end [4]= {255,255,255,'\0'};
    Uart_Transmit_IT_Display(( char *)end);
}