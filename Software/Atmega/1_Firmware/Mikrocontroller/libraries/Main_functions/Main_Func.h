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
#include "../TMC4671/TMC4671.h"
#include "../TMC6200/TMC6200.h"
#include "../LED/LED.h"
#include "../Software_Ramp/ramp1.h"
#include "../Nextion_Display/Nextion_Display.h"
#include "../Cocktail_functions/Zutaten.h"
#include "../Cocktail_functions/Getraenk.h"

extern void encoder_testdrive(void);

#include <util/delay.h>

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
void periodic_jobs(linear_ramp_t * ramp);
void check_motor_activities(linear_ramp_t * ramp);
void ramp_init(void);

extern void SD_startup(void);
extern void zutaten_init(void);
extern void cocktails_init(void);
extern void RFID_init(void);

extern void cocktail_check_command_display(int8_t page, int8_t button);
extern void cocktail_check_command_ESP(int8_t page, int8_t button);

extern void Uart_Transmit_IT_PC(char * data);


//Variabeln UART_0
extern unsigned char cntr_UART_0;
extern unsigned char INPUT_UART_0[128];
extern char UART_recieved_finished_0;
extern char cntr_End_UART_0;

//Variabeln UART_1
extern unsigned char cntr_UART_1;
extern unsigned char INPUT_UART_1[128];
extern char UART_recieved_finished_1;
extern char cntr_End_UART_1;
extern char * ptr_Uart_1;

//Variabeln UART_2
extern unsigned char cntr_UART_2;
extern unsigned char INPUT_UART_2[128];
extern char UART_recieved_finished_2;
extern char cntr_End_UART_2;

extern ring_buffer_t rb_rx_PC;

extern ring_buffer_t rb_rx_Display;

extern ring_buffer_t rb_rx_ESP;

uint32_t Position;
uint32_t count_bla;
volatile uint8_t compute;

#endif /* MAIN_FUNC_H_ */