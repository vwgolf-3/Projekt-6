/*
* ramp1.c
*
* Created: 07.09.2020 10:43:40
*  Author: kimsc
*/
#include "Ramp1.h"



//***********************************************//
// Init
//***********************************************//

void linear_ramp_init(void)
{
    ramp = &aRamp;

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

    ramp->motor_faktor_eine_umdrehung = 0.0;
    ramp->motor_umdrehungen_komplette_verschiebung = 0.0;
    ramp->motor_umdrehungen_teilverschiebung = 0.0;

    states = IDLE;
}

void linear_ramp_set_defaults(volatile linear_ramp_t * ramp)
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

    ramp->max_acceleration = 2 * 3.1415681 * 60 * 200.0; // (Umdrehungen/s^2)
    ramp->max_velocity = 2 * 3.1415681 * 60 * 200.0; // Umdrehungen/s;

    // Following 3 variables should be used as outputs to control the motor according to the ramp

    ramp->ramp_acceleration = 0.0;      // Ramp acceleration actual
    ramp->ramp_velocity = 0.0;          // Ramp velocity actual
    ramp->ramp_position = 0.0;          // Ramp position actual

    ramp->motor_faktor_eine_umdrehung = 196.635;
    ramp->motor_umdrehungen_komplette_verschiebung = 20.1596;
    ramp->motor_umdrehungen_teilverschiebung = 1.4801;
}



//***********************************************//
// Start Ramp
//***********************************************//

void calculateRamp(float acceleration, float velocity, float start_position, float end_position, volatile linear_ramp_t * ramp)
{
    // Beginn mit Setzen der Parameter, welche in die Funktion gegeben werden.
    ramp->target_acceleration = acceleration;
    ramp->target_velocity = velocity;
    ramp->target_position_absolute = end_position;
    ramp->ramp_x_0 = start_position;
    ramp->ramp_enable = 1;
}



//***********************************************//
// Calculation
//***********************************************//

void position_func(linear_ramp_t * ramp)
{
	ramp->ramp_position = ramp->ramp_x_0 + ramp->ramp_v_0 * ramp->ramp_timer + ramp->ramp_acceleration * ramp->ramp_timer * ramp->ramp_timer / 2;
}

void velocity_func(linear_ramp_t * ramp)
{
	ramp->ramp_velocity = ramp->ramp_v_0 + ramp->ramp_acceleration * ramp->ramp_timer;
}

float get_beschleunigungszeit(float velocity, float acceleration)
{
	return velocity / acceleration;
}

float get_volle_geschwindigkeitszeit(float Position, float acceleration, float beschleunigungszeit, float max_velocity)
{
	return (Position - acceleration * beschleunigungszeit * beschleunigungszeit)/max_velocity;
}



//***********************************************//
// Periodic Job
//***********************************************//

void computeRamp(volatile linear_ramp_t * ramp)
{
	static uint8_t forward = 1;

	if (ramp->ramp_enable == 1)
	{
		switch (states)
		{
			case IDLE:
			if (ramp->target_velocity > ramp->max_velocity)
			{
				ramp->target_velocity = ramp->max_velocity;
			}
			if (ramp->target_acceleration > ramp->max_acceleration)
			{
				ramp->target_acceleration = ramp->max_acceleration;
			}

			ramp->ramp_acceleration_time = get_beschleunigungszeit(ramp->target_velocity, ramp->target_acceleration); // Sek

			float delta_x;
			if (ramp->target_position_absolute < ramp->ramp_x_0)
			{
				delta_x = ramp->ramp_x_0 - ramp->target_position_absolute;
				forward = 0;
			}
			else
			{
				forward = 1;
				delta_x = ramp->target_position_absolute - ramp->ramp_x_0;
			}

			//             Uart_Transmit_IT_PC("Delta X: ");
			//             char ftoa_buff_3[20] = {'\0'};
			//             char * ftoa_ptr_3 = ftoa_buff_3;
			//             ftoa(delta_x, ftoa_ptr_3, 4);
			//             Uart_Transmit_IT_PC(ftoa_ptr_3);
			//             Uart_Transmit_IT_PC(")\r");

			if (delta_x < (ramp->ramp_acceleration_time * ramp->target_velocity))
			{
				ramp->ramp_fullspeed_time = 0.0;                                 // keine Zeit zur max_velocity
				ramp->ramp_acceleration_time = (float) sqrt(delta_x/ramp->target_acceleration);   // Beschleunigungszeiten
			}
			else
			{
				ramp->ramp_fullspeed_time = get_volle_geschwindigkeitszeit(delta_x, ramp->target_acceleration, ramp->ramp_acceleration_time, ramp->target_velocity); // Sek
			}
			if (forward == 1)
			{
				ramp->ramp_acceleration = ramp->target_acceleration;
			}
			else
			{
				ramp->ramp_acceleration = -ramp->target_acceleration;
			}
			ramp->ramp_v_0 = 0.0;
			states = ACCELERATING;
			break;

			case ACCELERATING:
			position_func(ramp);
			velocity_func(ramp);
			if (ramp->ramp_timer >= (ramp->ramp_acceleration_time))
			{
				states = FULLSPEED;
				ramp->ramp_x_0 = ramp->ramp_position;
				ramp->ramp_v_0 = ramp->ramp_velocity;
				ramp->ramp_acceleration = 0.0;
				ramp->ramp_timer = 0.0;
			}
			break;

			case FULLSPEED:
			position_func(ramp);
			velocity_func(ramp);
			if (ramp->ramp_timer >= (ramp->ramp_fullspeed_time))
			{
				states = BREAKING;
				ramp->ramp_timer = 0.0;
				ramp->ramp_x_0 = ramp->ramp_position;
				ramp->ramp_v_0 = ramp->ramp_velocity;
				if (forward == 1)
				{
					ramp->ramp_acceleration = - ramp->target_acceleration;
				}
				else
				{
					ramp->ramp_acceleration = ramp->target_acceleration;
				}
			}

			break;

			case BREAKING:
			position_func(ramp);
			velocity_func(ramp);
			if (ramp->ramp_timer >= (ramp->ramp_acceleration_time))
			{
				states = IDLE;
				ramp->ramp_timer =0.0;
				ramp->ramp_enable = 0.0;
				ramp->target_acceleration = 0.0;
				ramp->target_velocity = 0.0;
				ramp->target_acceleration = 0.0;
			}
			break;
		}
		tmc4671_setAbsolutTargetPosition(0, (uint32_t)(ramp->ramp_position)* 1000);
	}
}



//***********************************************//
// ISR 1000Hz
//***********************************************//

void ramp_pwm_init(void)
{
	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22);
	TIMSK2 |= (1 << OCIE2A);
	OCR2A = 250;
}

ISR(TIMER2_COMPA_vect)
{
	if (ramp->ramp_enable == 1)
	{
		iterate_timer(ramp);
	}
}

void iterate_timer(volatile linear_ramp_t * ramp)
{
	ramp->ramp_timer += ramp->ramp_timer_iteration;
}



//***********************************************//
// Debug https://www.geeksforgeeks.org/convert-floating-point-number-string/
//***********************************************//

void status_message(volatile linear_ramp_t * ramp)
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

void reverse(char* str, int len)
{
// Reverses a string 'str' of length 'len'

	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int intToStr(int x, char str[], int d)
{
// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
	
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

void ftoa(float n, char* res, int afterpoint)
{
// Converts a floating-point/double number to a string.
	
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


