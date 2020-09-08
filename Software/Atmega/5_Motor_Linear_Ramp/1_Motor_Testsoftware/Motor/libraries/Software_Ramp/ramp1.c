/*
* ramp1.c
*
* Created: 07.09.2020 10:43:40
*  Author: kimsc
*/
#include "Ramp1.h"

void linear_ramp_init(linear_ramp_t * ramp)
{
    ramp->ramp_enable = 0;

    ramp->ramp_timer = 0.0;
    ramp->ramp_timer_iteration = 0.0;

    ramp->ramp_acceleration_time = 0.0;
    ramp->ramp_fullspeed_time = 0.0;
    ramp->ramp_x_0 = 0.0;
    ramp->ramp_v_0 = 0.0;

    ramp->ramp_acceleration = 0.0;
    ramp->ramp_velocity = 0.0;
    ramp->ramp_position = 0.0;

    ramp->target_acceleration = 0.0;
    ramp->target_velocity = 0.0;
    ramp->target_position_absolute = 0.0;

    ramp->max_acceleration = 0.0;
    ramp->max_velocity = 0.0;
}
void linear_ramp_set_defaults(linear_ramp_t * ramp)
{
    ramp->ramp_enable = 0;              // Status

    // Following variables shouldn't be edited, they are used for the calculation of the ramp

    ramp->ramp_timer = 0.0;             // Iteration trough calculations
    ramp->ramp_timer_iteration = 0.001; // Timer interrupt each

    ramp->ramp_acceleration_time = 0.0; // Acceleration time
    ramp->ramp_fullspeed_time = 0.0;    // Fullspeed time

    ramp->ramp_x_0 = 0.0;
    ramp->ramp_v_0 = 0.0;

    ramp->target_acceleration = 0.0;
    ramp->target_velocity = 0.0;
    ramp->target_position_absolute = 0.0;       // Absolute target position

    // Following 2 variables determine maximum ratings

    ramp->max_acceleration = 500.0;
    ramp->max_velocity = 500.0;

    // Following 3 variables should be used as outputs to control the motor according to the ramp

    ramp->ramp_acceleration = 0.0;      // Ramp acceleration actual
    ramp->ramp_velocity = 0.0;          // Ramp velocity actual
    ramp->ramp_position = 0.0;          // Ramp position actual
}
void calculateRamp(float acceleration, float velocity, float position, linear_ramp_t * ramp)
{
    // Beginn mit Setzen der Parameter, welche in die Funktion gegeben werden.
    ramp->target_acceleration = acceleration;
    ramp->target_velocity = velocity;
    ramp->target_position_absolute = position;
    ramp->ramp_enable = 1;
}
void status_message(linear_ramp_t * ramp)
{
    char itoa_buffer[15];
    char * ptr = itoa_buffer;
    ftoa(ramp->ramp_acceleration, ptr, 4);
    Uart_Transmit_IT_PC("Acceleration: ");
    Uart_Transmit_IT_PC(ptr);
    ftoa(ramp->ramp_velocity, ptr, 4);
    Uart_Transmit_IT_PC("\rVelocity: ");
    Uart_Transmit_IT_PC(ptr);
    ftoa(ramp->ramp_position, ptr, 4);
    Uart_Transmit_IT_PC("\rPosition: ");
    Uart_Transmit_IT_PC(ptr);
    ftoa(ramp->ramp_timer, ptr, 4);
    Uart_Transmit_IT_PC("\rtimer: ");
    Uart_Transmit_IT_PC(ptr);
    Uart_Transmit_IT_PC("\r");
    _delay_ms(10);
}
void computeRamp(linear_ramp_t * ramp)
{
    if (ramp->ramp_enable == 1)
    {
        switch (states)
        {
        case IDLE:
            // der Maximalwert eingesetzt.
            if (ramp->target_velocity > ramp->max_velocity)
            {
                //              Uart_Transmit_IT_PC("Geschwindigkeit über Maximum\r");
                ramp->target_velocity = ramp->max_velocity;
            }
            if (ramp->target_acceleration > ramp->max_acceleration)
            {
                //              Uart_Transmit_IT_PC("Beschleunigung über Maximum\r");
                ramp->target_acceleration = ramp->max_acceleration;
            }

            // Berechnen der Beschleunigungszeit
            ramp->ramp_acceleration_time = get_beschleunigungszeit(ramp->target_velocity, ramp->target_acceleration); // Sek

            // Falls die Strecke nicht ausreicht, voll zu beschleunigen, ergibt es eine
            // triangulare Geschwindigkeitskurve, woraus die Beschleunigungszeit ermittelt wird.
            if (ramp->target_position_absolute < (ramp->ramp_acceleration_time * ramp->target_velocity))
            {
                //              Uart_Transmit_IT_PC("Kein Fullspeed\r");
                ramp->ramp_fullspeed_time = 0.0;                                 // keine Zeit zur max_velocity
                ramp->ramp_acceleration_time = (float) sqrt(ramp->target_position_absolute/ramp->target_acceleration);   // Beschleunigungszeiten
            }
            else
            {
                // Falls die Strecke ausreicht, wird die gesamte Zeit auf Fullspeed berechnet.
                ramp->ramp_fullspeed_time = get_volle_geschwindigkeitszeit(ramp->target_position_absolute, ramp->target_acceleration, ramp->ramp_acceleration_time, ramp->target_velocity); // Sek
            }

            ramp->ramp_x_0 = 0.0;
            ramp->ramp_v_0 = 0.0;

            // Nach den Berechnungen wechselt der Status auf Beschleunigen
            states = ACCELERATING;
            break;

        case ACCELERATING:

            // Über die berechneten Bewegungszeiten kann nun interiert werden. Die Beschleunigung bleibt konstant,
            // die Geschwindigkeit und Position werden mit den Formeln berechnet.

            ramp->ramp_position = position_func(ramp->ramp_x_0, ramp->ramp_v_0, ramp->target_acceleration, ramp->ramp_timer);
            ramp->ramp_velocity = velocity_func(ramp->ramp_v_0, ramp->target_acceleration, ramp->ramp_timer);
            ramp->ramp_acceleration = ramp->target_acceleration;
            iterate_timer(ramp);

            if (ramp->ramp_timer >= (ramp->ramp_acceleration_time))
            {
                //              status_message(ramp);
                states = FULLSPEED;
                ramp->ramp_x_0 = ramp->ramp_position;
                ramp->ramp_v_0 = ramp->ramp_velocity;
                ramp->ramp_timer = 0.0;
            }
            break;

        case FULLSPEED:

            ramp->ramp_position = position_func(ramp->ramp_x_0, ramp->ramp_v_0, 0, ramp->ramp_timer);
            ramp->ramp_velocity = velocity_func(ramp->ramp_v_0, 0, ramp->ramp_timer);
            ramp->ramp_acceleration = ramp->ramp_acceleration;
            iterate_timer(ramp);
            if (ramp->ramp_timer >= (ramp->ramp_fullspeed_time))
            {
                //                 status_message(ramp);
                states = BREAKING;
                ramp->ramp_timer = 0.0;
                ramp->ramp_x_0 = ramp->ramp_position;
                ramp->ramp_v_0 = ramp->ramp_velocity;
            }

            break;

        case BREAKING:
            ramp->ramp_position = position_func(ramp->ramp_x_0, ramp->ramp_v_0, -ramp->target_acceleration, ramp->ramp_timer);
            ramp->ramp_velocity = velocity_func(ramp->ramp_v_0, -ramp->target_acceleration, ramp->ramp_timer);
            ramp->ramp_acceleration = -ramp->target_acceleration;

            iterate_timer(ramp);
            if (ramp->ramp_timer >= (ramp->ramp_acceleration_time))
            {
                //                 status_message(ramp);
                states = IDLE;
                ramp->ramp_timer =0.0;
                ramp->ramp_enable = 0.0;
                ramp->target_acceleration = 0.0;
                ramp->target_velocity = 0.0;
                ramp->target_acceleration = 0.0;
            }
            break;
        }
    }
}
float iterate_timer(linear_ramp_t * ramp)
{
    ramp->ramp_timer += ramp->ramp_timer_iteration;
    return ramp->ramp_timer;
}
float position_func(float x0, float v0, float a, float t)
{
    return x0 + v0 * t + a * t * t / 2;
}
float velocity_func(float v0, float a, float t)
{
    return v0 + a * t;
}
float get_beschleunigungszeit(float velocity, float acceleration)
{
    return velocity / acceleration;
}
float get_volle_geschwindigkeitszeit(float Position, float acceleration, float beschleunigungszeit, float max_velocity)
{
    return (Position - acceleration * beschleunigungszeit * beschleunigungszeit)/max_velocity;
}

// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}