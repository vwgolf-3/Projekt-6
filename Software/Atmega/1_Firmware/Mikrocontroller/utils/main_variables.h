/*
 * main_variables.h
 *
 * Created: 09.05.2020 01:06:32
 *  Author: kimsc
 */ 


#ifndef MAIN_VARIABLES_H_
#define MAIN_VARIABLES_H_

//Variabeln UART_0
unsigned char cntr_UART_0 = 0;
unsigned char INPUT_UART_0[256];
char UART_recieved_finished_0 = 0;
char cntr_End_UART_0 = 0;

//Variabeln UART_1
unsigned char cntr_UART_1 = 0;
unsigned char INPUT_UART_1[256];
char UART_recieved_finished_1 = 0;
char cntr_End_UART_1 = 0;
char * ptr_Uart_1;

//Variabeln UART_2
unsigned char cntr_UART_2 = 0;
unsigned char INPUT_UART_2[256];
char UART_recieved_finished_2 = 0;
char cntr_End_UART_2 = 0;

// Variabeln UART_3
unsigned char cntr_UART_3 = 0;
unsigned char INPUT_UART_3[256];
char UART_recieved_finished_3 = 0;
char cntr_End_UART_3 = 0;

#endif /* MAIN_VARIABLES_H_ */