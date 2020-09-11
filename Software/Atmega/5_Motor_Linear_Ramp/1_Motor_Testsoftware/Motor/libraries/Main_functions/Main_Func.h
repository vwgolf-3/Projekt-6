/*
 * Main_Func.h
 *
 * Created: 19.01.2020 14:02:13
 *  Author: kimsc
 */ 


#ifndef MAIN_FUNC_H_
#define MAIN_FUNC_H_

#define F_CPU 16000000UL

// Projektspezifische Pindefinitionen Cocktailmaschine<==>AVR uC
#include "../UART/UART.h"											// Wird ben�tigt f�r UART und Ring-Buffer
#include "../../pin_defs.h"
#include <util/delay.h>

void TIMER_init(void);
void IO_init(void);
void heartbeat_LED(void);
void toggle_LED(void);
char check_Communication_Input_UART_0(void);
void proceed_Communication_Input_UART_0(void);

void check_Communication_Input_UART(void);

void my_itoa( int64_t z, char* buffer );

void read_Position_TMC4671(void);

//Variabeln UART_0
extern unsigned char cntr_UART_0;
extern unsigned char INPUT_UART_0[256];
extern char UART_recieved_finished_0;
extern char cntr_End_UART_0;

extern ring_buffer_t rb_tx_PC;
extern ring_buffer_t rb_rx_PC;

uint32_t Position;


#endif /* MAIN_FUNC_H_ */