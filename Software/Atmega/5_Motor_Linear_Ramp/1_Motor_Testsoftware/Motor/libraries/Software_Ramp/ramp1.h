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

enum ramp_states {IDLE, ACCELERATING, FULLSPEED, BREAKING};
enum ramp_states states;

struct linear_ramp {
    uint8_t ramp_enable;

    float ramp_timer;
    float ramp_timer_iteration;

    float ramp_acceleration_time;
    float ramp_fullspeed_time;
    float ramp_total_time;

    float ramp_x_0;
    float ramp_v_0;

    float ramp_acceleration;
    float ramp_velocity;
    float ramp_position;

    float target_acceleration;
    float target_velocity;
    float target_position_absolute;


    float max_velocity;
    float max_acceleration;
};
typedef struct linear_ramp linear_ramp_t;

void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);

void linear_ramp_init(linear_ramp_t * ramp);
void linear_ramp_set_defaults(linear_ramp_t * ramp);
void calculateRamp(float acceleration, float velocity, float position, linear_ramp_t * ramp);
void computeRamp(linear_ramp_t * ramp);
float iterate_timer(linear_ramp_t * ramp);
float position_func(float x0, float v0, float a, float t);
float velocity_func(float v0, float a, float t);
float get_beschleunigungszeit(float velocity, float acceleration);
float get_volle_geschwindigkeitszeit(float Position, float acceleration, float beschleunigungszeit, float max_velocity);
#endif /* RAMP1_H_ */