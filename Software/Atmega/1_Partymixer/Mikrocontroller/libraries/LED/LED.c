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
// 
//     TCCR1B |= (1 << WGM12)|(1 << CS10);
//     TIMSK1 |= (1 << OCIE1A)|(1<<OCIE1B);
//     OCR1A = 800;
//     OCR1B = 0;

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
//     TCCR0A |= (1<<WGM01);
//     TCCR0B |= (1<<CS02)|(1<<CS00);
//     OCR0A = milliS * 7.8125 - 1;
//     TIMSK0 |= (1<<OCIE0A);
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

// ISR(TIMER0_COMPA_vect)
// {
//     switch (light)
//     {
//     case WEISS_LED:
//         TCCR1B |= (1 << CS10);
//         TCCR3B &= ~(1 << CS30);
//         TCCR4B &= ~(1 << CS40);
//         TCCR5B &= ~(1 << CS50);
//         LEDB_PORT &= ~LEDB_BIT;
//         LEDG_PORT &= ~LEDG_BIT;
//         LEDR_PORT &= ~LEDR_BIT;
//         OCR1B = 700;
//         OCR3B = 0;
//         OCR4B = 0;
//         OCR5B = 0;
//         break;
//     case RAINBOW_LED:
//         TCCR1B &= ~(1 << CS10);
//         TCCR3B |= (1 << CS30);
//         TCCR4B |= (1 << CS40);
//         TCCR5B |= (1 << CS50);
//         LEDW_PORT &= ~LEDW_BIT;
//         OCR1B = 0;
//         rainbow();
//         break;
//     case USER_LED:
//         if (PWM_DUTY_WHITE > 0)
//         {
//             TCCR1B |= (1 << CS10);
//         }
//         else
//         {
//             TCCR1B &= ~(1 << CS10);
//             LEDW_PORT &= ~LEDW_BIT;
//         }
// 
//         if (PWM_DUTY_RED > 0)
//         {
//             TCCR3B |= (1 << CS30);
//         }
//         else
//         {
//             TCCR3B &= ~(1 << CS30);
//             LEDR_PORT &= ~LEDR_BIT;
//         }
// 
//         if (PWM_DUTY_GREEN > 0)
//         {
//             TCCR4B |= (1 << CS40);
//         }
//         else
//         {
//             TCCR4B &= ~(1 << CS40);
//             LEDG_PORT &= ~LEDG_BIT;
//         }
// 
//         if (PWM_DUTY_BLUE > 0)
//         {
//             TCCR5B |= (1 << CS50);
//         }
//         else
//         {
//             TCCR5B &= ~(1 << CS50);
//             LEDB_PORT &= ~LEDB_BIT;
//         }
//         asm("nop");
//         break;
//     }
// }

void PWM_BrightDim(uint16_t red, uint16_t green, uint16_t blue)
{
    PWM_DUTY_RED = red;
    PWM_DUTY_GREEN = green;
    PWM_DUTY_BLUE = blue;
}