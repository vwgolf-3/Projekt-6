/*
 * LED.h
 *
 * Created: 12.08.2020 20:23:49
 *  Author: kimsc
 */


#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include "../../utils/pin_defs.h"

/* Rainbow settings */
#define STEP        1
#define	MAX_STEPS 1599
#define	MAX_CNT 1549

/* Period definitions OCRxA*/
#define PWM_PERIOD_RAINBOW OCR0A
#define PWM_PERIOD_WHITE OCR1A
#define PWM_PERIOD_RED OCR3A
#define PWM_PERIOD_GREEN OCR4A
#define PWM_PERIOD_BLUE OCR5A

/* Duty-Cycle definitions OCRxB*/
#define PWM_DUTY_WHITE OCR1B
#define PWM_DUTY_RED OCR3B
#define PWM_DUTY_GREEN OCR4B
#define PWM_DUTY_BLUE OCR5B

/* Timer-Control definitions TCCRxA*/
#define TIMER_CONTROL_REGISTER_A_RAINBOW TCCR0A

/* Timer-Control definitions TCCRxB*/
#define TIMER_CONTROL_REGISTER_B_RAINBOW TCCR0B
#define TIMER_CONTROL_REGISTER_B_WHITE TCCR1B
#define TIMER_CONTROL_REGISTER_B_RED TCCR3B
#define TIMER_CONTROL_REGISTER_B_GREEN TCCR4B
#define TIMER_CONTROL_REGISTER_B_BLUE TCCR5B

/* Interrupt definitions TIMSKx*/
#define INTERRUPT_MASK_REGISTER_RAINBOW TIMSK0
#define INTERRUPT_MASK_REGISTER_WHITE TIMSK1
#define INTERRUPT_MASK_REGISTER_RED TIMSK3
#define INTERRUPT_MASK_REGISTER_GREEN TIMSK4
#define INTERRUPT_MASK_REGISTER_BLUE TIMSK5

/* Global variables */
volatile uint16_t state;
volatile uint16_t rainbow_i;

void init_LED(void);
void algorithm(void);
void rainbow (void);

void PWM_init(void);
void milliS_timer(uint8_t milliS);

void PWM_BrightDim(uint16_t red, uint16_t green, uint16_t blue);

enum LED_Bez {WEISS_LED, RAINBOW_LED, USER_LED};

uint8_t light;

#endif /* LED_H_ */