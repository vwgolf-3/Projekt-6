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
#define    STEP        1

#define PWM_DUTY_WHITE OCR1B
#define PWM_DUTY_RED OCR3B
#define PWM_DUTY_GREEN OCR4B
#define PWM_DUTY_BLUE OCR5B

#define PWM_PERIOD_WHITE OCR1A
#define PWM_PERIOD_RED OCR3A
#define PWM_PERIOD_GREEN OCR4A
#define PWM_PERIOD_BLUE OCR5A

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