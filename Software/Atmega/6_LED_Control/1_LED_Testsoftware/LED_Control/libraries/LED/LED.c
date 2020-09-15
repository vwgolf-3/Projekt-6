/*
 * LED.c
 *
 * Created: 12.08.2020 20:23:37
 *  Author: kimsc
 */

#include "LED.h"
#include <util/delay.h>
#include "../UART/UART.h"

void init_LED(void)
{
    state = 6;
    rainbow_i = 0;
    light = RAINBOW_LED;
    PWM_init();
}

void PWM_init(void)
{
    TIMER_CONTROL_REGISTER_A_RAINBOW |= (1<<WGM01);                 // CTC-Mode
    TIMER_CONTROL_REGISTER_B_RAINBOW |= (1<<CS02)|(1<<CS00);        // Prescaler 1024
    PWM_PERIOD_RAINBOW = 48;                                        // 160Hz
    INTERRUPT_MASK_REGISTER_RAINBOW |= (1<<OCIE0A);                 // Interrupt OCR0A

    TIMER_CONTROL_REGISTER_B_WHITE |= (1 << WGM12);     // CTC-Mode, disabled
	LEDW_PORT &= ~LEDW_BIT;
    INTERRUPT_MASK_REGISTER_WHITE |= (1 << OCIE1A);     // Interrupt OCR1A, Interupt OCR1B
    PWM_PERIOD_WHITE = MAX_STEPS;                                   // 10kHz
    PWM_DUTY_WHITE = 0;                                             // Duty Cycle = 0;
	_delay_us(25);

    TIMER_CONTROL_REGISTER_B_RED |= (1 << WGM32)|(1 << CS30);       // CTC-Mode, prescaler 1
    INTERRUPT_MASK_REGISTER_RED |= (1 << OCIE3A)|(1<<OCIE3B);       // Interrupt OCR3A, Interrupt OCR3B
    PWM_PERIOD_RED = MAX_STEPS;                                     // 10kHz
    PWM_DUTY_RED = 0;                                               // Duty-Cycle = 0;
	_delay_us(25);

    TIMER_CONTROL_REGISTER_B_GREEN |= (1 << WGM42)|(1 << CS40);     // CTC-Mode, prescaler 1
    INTERRUPT_MASK_REGISTER_GREEN |= (1 << OCIE4A)|(1<<OCIE4B);     // Interrupt OCR4A, Interrupt OCR4B
    PWM_PERIOD_GREEN = MAX_STEPS;
    PWM_DUTY_GREEN = 0;
	_delay_us(25);

    TIMER_CONTROL_REGISTER_B_BLUE |= (1 << WGM52)|(1 << CS50);      // CTC-Mode, prescaler 1
    INTERRUPT_MASK_REGISTER_BLUE |= (1 << OCIE5A)|(1<<OCIE5B);      // Interrupt OCR5A, Interrupt OCR5B
    PWM_PERIOD_BLUE = MAX_STEPS;                                    // 10kHz
    PWM_DUTY_BLUE = 0;                                              // Duty-Cycle = 0;
}

ISR(TIMER1_COMPA_vect)
{
    LEDW_PORT |= (LEDW_BIT);
}

ISR(TIMER1_COMPB_vect)
{
    LEDW_PORT &= ~LEDW_BIT;
}

ISR(TIMER3_COMPA_vect)
{
    LEDR_PORT |= (LEDR_BIT);
}

ISR(TIMER3_COMPB_vect)
{
    LEDR_PORT &= ~LEDR_BIT;
}

ISR(TIMER4_COMPA_vect)
{
    LEDG_PORT |= (LEDG_BIT);
}

ISR(TIMER4_COMPB_vect)
{
    LEDG_PORT &= ~LEDG_BIT;
}

ISR(TIMER5_COMPA_vect)
{
    LEDB_PORT |= (LEDB_BIT);
}

ISR(TIMER5_COMPB_vect)
{
    LEDB_PORT &= ~LEDB_BIT;
}
void rainbow (void)
{
    switch (state)
    {
    case 0:
        rainbow_i += STEP;
        PWM_DUTY_RED = rainbow_i;
        if (rainbow_i == MAX_CNT)
        {
            state = 1;
        }
        break;

    case 1:
        rainbow_i -= STEP;
        PWM_DUTY_GREEN = rainbow_i;
        if (rainbow_i == 0)
        {
            state = 2;
        }
        break;

    case 2:
        rainbow_i += STEP;
        PWM_DUTY_BLUE = rainbow_i;
        if (rainbow_i == MAX_CNT)
        {
            state = 3;
        }
        break;

    case 3:
        rainbow_i -= STEP;
        PWM_DUTY_RED = rainbow_i;
        if (rainbow_i == 0)
        {
            state = 4;
        }
        break;

    case 4:
        rainbow_i += STEP;
        PWM_DUTY_GREEN = rainbow_i;
        if (rainbow_i == MAX_CNT)
        {
            state = 5;
        }
        break;

    case 5:
        rainbow_i -= STEP;
        PWM_DUTY_BLUE = rainbow_i;
        if (rainbow_i == 0)
        {
            state = 0;
        }
        break;

    case 6:
        rainbow_i += STEP;
        PWM_DUTY_GREEN = rainbow_i;
        if (rainbow_i == MAX_CNT)
        {
            state = 0;
            rainbow_i = 0;
        }
        break;
    }
}

ISR(TIMER0_COMPA_vect)
{
    switch (light)
    {
    case RAINBOW_LED:
        // Rainbow-Algorithmus
        rainbow();
        break;
		
    case WEISS_LED:
        break;
    }
}

void PWM_BrightDim(uint16_t red, uint16_t green, uint16_t blue)
{
    PWM_DUTY_RED = red;
    PWM_DUTY_GREEN = green;
    PWM_DUTY_BLUE = blue;
}