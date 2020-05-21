/*
 * Main_Func.h
 *
 * Created: 19.01.2020 14:02:13
 *  Author: kimsc
 */ 


#ifndef MAIN_FUNC_H_
#define MAIN_FUNC_H_

#include "../libraries/Cocktail_functions/Cocktail_functions.h"
#include "../libraries/UART/UART.h"

void TIMER_init(void);
void IO_init(void);
void heartbeat_LED(void);
void toggle_LED(void);
char check_Communication_Input_UART_0(void);
void proceed_Communication_Input_UART_0(void);
char check_Communication_Input_UART_1(void);
void proceed_Communication_INPUT_UART_1(void);
char check_Communication_Input_UART_2(void);
void proceed_Communication_Input_UART_2(void);
// char check_Communication_Input_UART_3(void);
// void proceed_Communication_Input_UART_3(void);
void check_Communication_Input_UART(void);
void check_Communication_Input_MFRC522(void);

void testFunc(void);


//Variabeln UART_0
extern unsigned char cntr_UART_0;
extern unsigned char INPUT_UART_0[256];
extern char UART_recieved_finished_0;
extern char cntr_End_UART_0;

//Variabeln UART_1
extern unsigned char cntr_UART_1;
extern unsigned char INPUT_UART_1[256];
extern char UART_recieved_finished_1;
extern char cntr_End_UART_1;

//Variabeln UART_2
extern unsigned char cntr_UART_2;
extern unsigned char INPUT_UART_2[256];
extern char UART_recieved_finished_2;
extern char cntr_End_UART_2;

//Variabeln UART_2
extern unsigned char cntr_UART_3;
extern unsigned char INPUT_UART_3[256];
extern char UART_recieved_finished_3;
extern char cntr_End_UART_3;

//Variabeln SPI_0
extern unsigned char cntr_SPI_0;
extern unsigned char INPUT_SPI_0[256];
extern unsigned char OUTPUT_SPI_0[256];
extern int SPI_received_finished_0;
extern char cntr_End_SPI_0;

extern ring_buffer_t rb_tx_PC;
extern ring_buffer_t rb_rx_PC;

extern ring_buffer_t rb_tx_Display;
extern ring_buffer_t rb_rx_Display;

extern ring_buffer_t rb_tx_ESP;
extern ring_buffer_t rb_rx_ESP;

extern ring_buffer_t rb_tx_RFID;
extern ring_buffer_t rb_rx_RFID;

extern ring_buffer_t rb_SPI_r;
extern ring_buffer_t rb_SPI_w;


#endif /* MAIN_FUNC_H_ */