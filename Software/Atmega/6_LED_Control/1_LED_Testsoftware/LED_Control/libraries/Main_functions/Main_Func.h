/*
 * Main_Func.h
 *
 * Created: 19.01.2020 14:02:13
 *  Author: kimsc
 */


#ifndef MAIN_FUNC_H_
#define MAIN_FUNC_H_
// Projektspezifische Pindefinitionen Cocktailmaschine<==>AVR uC
#include "../UART/UART.h"                                           // Wird benötigt für UART und Ring-Buffer
#include "../../utils/pin_defs.h"
#include "../LED/LED.h"

#include <util/delay.h>

void TIMER_init(void);
void IO_init(void);
void speicher_init();
void devices_init(void);
void interfaces_init(void);
void heartbeat_LED(void);
void toggle_LED(void);
void my_itoa( int64_t z, char* buffer );
void read_Position_TMC4671(void);
char check_Communication_Input_UART_0(void);
void proceed_Communication_Input_UART_0(void);
char check_Communication_Input_UART_1(void);
void proceed_Communication_INPUT_UART_1(void);
char check_Communication_Input_UART_2(void);
void proceed_Communication_Input_UART_2(void);
void check_Communication_Input_UART(void);
void check_Communication_Input_MFRC522(void);

extern void SPI_init(void);
extern void SD_startup(void);
extern void zutaten_init(void);
extern void cocktails_init(void);
extern void RFID_init(void);
extern void cocktail_test_command(unsigned char INPUT[256]);
extern void cocktail_check_command(int8_t page, int8_t button);
extern void Uart_Transmit_IT_PC(char * data);

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
extern char * ptr_Uart_1;

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

extern ring_buffer_t rb_tx_PC;
extern ring_buffer_t rb_rx_PC;

extern ring_buffer_t rb_tx_Display;
extern ring_buffer_t rb_rx_Display;

extern ring_buffer_t rb_tx_ESP;
extern ring_buffer_t rb_rx_ESP;

extern ring_buffer_t rb_tx_RFID;
extern ring_buffer_t rb_rx_RFID;

// Variable für Liste
extern uint8_t i_Liste;
extern uint8_t i_Liste_test[50];
extern uint8_t i_Liste_test_cnt;
extern uint8_t block_list_hoch;
extern uint8_t block_list_runter;
extern uint8_t Grossschreib;
extern uint8_t counter;

uint32_t process;

#endif /* MAIN_FUNC_H_ */