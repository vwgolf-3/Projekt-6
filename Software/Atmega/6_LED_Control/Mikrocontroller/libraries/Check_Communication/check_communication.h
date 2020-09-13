/*
 * check_communication.h
 *
 * Created: 17.06.2020 12:26:38
 *  Author: kimsc
 */ 


#ifndef CHECK_COMMUNICATION_H_
#define CHECK_COMMUNICATION_H_

#include <stdint.h>

char check_Communication_Input_UART_0(void);
void proceed_Communication_Input_UART_0(void);
char check_Communication_Input_UART_1(void);
void proceed_Communication_INPUT_UART_1(void);
char check_Communication_Input_UART_2(void);
void proceed_Communication_Input_UART_2(void);
// char check_Communication_Input_UART_3(void);
// void proceed_Communication_Input_UART_3(void);
void check_Communication_Input_MFRC522(void);


#endif /* CHECK_COMMUNICATION_H_ */