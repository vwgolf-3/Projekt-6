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
    state = 0;
    rainbow_i = 0;
    light = RAINBOW_LED;
    PWM_init();
}

void PWM_init(void)
{
    milliS_timer(20);

    TCCR3B |= (1 << WGM32)|(1 << CS30);
    TIMSK3 |= (1 << OCIE3A)|(1<<OCIE3B);
    OCR3A = 800;
    OCR3B = 0;

    TCCR4B |= (1 << WGM42)|(1 << CS40);
    TIMSK4 |= (1 << OCIE4A)|(1<<OCIE4B);
    OCR4A = 800;
    OCR4B = 700;

    TCCR5B |= (1 << WGM52)|(1 << CS50);
    TIMSK5 |= (1 << OCIE5A)|(1<<OCIE5B);
    OCR5A = 800;
    OCR5B = 0;
}

void milliS_timer(uint8_t milliS)
{
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << CS12)|(1<<CS10);
    OCR1A = milliS * 7.8125 - 1;
    TIMSK1 |= (1<<OCIE1A);
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
        TCCR3B |= (1 << CS30);
        rainbow_i += STEP;
        PWM_DUTY_RED = rainbow_i;
        if (rainbow_i >= 700)
        {
            state = 1;
        }
        break;

    case 1:
        rainbow_i -= STEP;
        PWM_DUTY_GREEN = rainbow_i;
        if (rainbow_i <= 0)
        {
            state = 2;
        }
        break;

    case 2:
        TCCR5B |= (1 << CS50);
        rainbow_i += STEP;
        PWM_DUTY_BLUE = rainbow_i;
        if (rainbow_i >= 700)
        {
            state = 3;
        }
        break;

    case 3:
        rainbow_i -= STEP;
        PWM_DUTY_RED = rainbow_i;
        if (rainbow_i <= 0)
        {
            state = 4;
        }
        break;

    case 4:
        TCCR4B |= (1 << CS40);
        rainbow_i += STEP;
        PWM_DUTY_GREEN = rainbow_i;
        if (rainbow_i >= 700)
        {
            state = 5;
        }
        break;

    case 5:
        rainbow_i -= STEP;
        PWM_DUTY_BLUE = rainbow_i;
        if (rainbow_i <= 0)
        {
            state = 0;
        }
        break;
    }
}

ISR(TIMER1_COMPA_vect)
{
    switch (light)
    {
    case RAINBOW_LED:
        TCCR3B |= (1 << CS30);
        TCCR4B |= (1 << CS40);
        TCCR5B |= (1 << CS50);
        LEDW_PORT &= ~LEDW_BIT;
        rainbow();
        break;
    case USER_LED:
//         if (PWM_DUTY_WHITE > 0)
//         {
//             TCCR1B |= (1 << CS10);
//         }
//         else
//         {
//             TCCR1B &= ~(1 << CS10);
//             LEDW_PORT &= ~LEDW_BIT;
//         }

        if (PWM_DUTY_RED > 0)
        {
            TCCR3B |= (1 << CS30);
        }
        else
        {
            TCCR3B &= ~(1 << CS30);
            LEDR_PORT &= ~LEDR_BIT;
        }

        if (PWM_DUTY_GREEN > 0)
        {
            TCCR4B |= (1 << CS40);
        }
        else
        {
            TCCR4B &= ~(1 << CS40);
            LEDG_PORT &= ~LEDG_BIT;
        }

        if (PWM_DUTY_BLUE > 0)
        {
            TCCR5B |= (1 << CS50);
        }
        else
        {
            TCCR5B &= ~(1 << CS50);
            LEDB_PORT &= ~LEDB_BIT;
        }
        break;
    }
}

void disableLEDinterrupts(void)
{
    TCCR1B &= ~((1 << CS12)|(1<<CS10));
    TCCR3B &= ~(1 << CS30);
    TCCR4B &= ~(1 << CS40);
    TCCR5B &= ~(1 << CS50);
    LEDR_PORT |= LEDR_BIT;
    LEDG_PORT |= LEDG_BIT;
    LEDB_PORT |= LEDB_BIT;
}

void enableLEDinterrupts(void)
{
    TCCR1B |= (1 << CS12)|(1<<CS10);
    TCCR3B |= (1 << CS30);
    TCCR4B |= (1 << CS40);
    TCCR5B |= (1 << CS50);
}