/*
 * Ramp1.h
 *
 * Created: 07.09.2020 10:43:55
 *  Author: kimsc
 */


#ifndef RAMP1_H_
#define RAMP1_H_

#include <stdint.h>
#include <math.h>
#include <util/delay.h>

#include "../UART/UART.h"
#include "../TMC4671/TMC4671.h"

enum ramp_states {IDLE, ACCELERATING, FULLSPEED, BREAKING};
enum ramp_states states;

struct linear_ramp {
    volatile uint8_t ramp_enable;

    volatile float ramp_timer;
    volatile float ramp_timer_iteration;

    volatile float ramp_acceleration_time;
    volatile float ramp_fullspeed_time;
    volatile float ramp_total_time;

    volatile float ramp_x_0;
    volatile float ramp_v_0;

    volatile float ramp_acceleration;
    volatile float ramp_velocity;
    volatile float ramp_position;

    volatile float target_acceleration;
    volatile float target_velocity;
    volatile float target_position_absolute;

    volatile float max_velocity;
    volatile float max_acceleration;

    volatile float motor_faktor_eine_umdrehung;
    volatile float motor_umdrehungen_komplette_verschiebung;
    volatile float motor_umdrehungen_teilverschiebung;
};
typedef struct linear_ramp volatile linear_ramp_t;

linear_ramp_t *ramp;
linear_ramp_t aRamp;

void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);
void ramp_pwm_init(void);

void linear_ramp_init(void);
void linear_ramp_set_defaults(volatile linear_ramp_t * ramp);
void calculateRamp(float acceleration, float velocity, float start_position, float end_position, volatile linear_ramp_t * ramp);
void computeRamp(volatile linear_ramp_t * ramp);
void iterate_timer(volatile linear_ramp_t * ramp);
void position_func(linear_ramp_t * ramp);
void velocity_func(linear_ramp_t * ramp);

float get_beschleunigungszeit(float velocity, float acceleration);
float get_volle_geschwindigkeitszeit(float Position, float acceleration, float beschleunigungszeit, float max_velocity);

void ramp_pwm_init(void);

#endif /* RAMP1_H_ */