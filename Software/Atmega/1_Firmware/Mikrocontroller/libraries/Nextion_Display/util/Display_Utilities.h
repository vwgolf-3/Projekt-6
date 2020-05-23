/*
 * Display_Utilities.h
 *
 * Created: 19.01.2020 20:43:23
 *  Author: kimsc
 */ 


#ifndef DISPLAY_UTILITIES_H_
#define DISPLAY_UTILITIES_H_
// /*******************************************************************************
//  * TYPES
//  *******************************************************************************/
// typedef short int8_t;
// typedef unsigned short uint8_t;
// typedef int int16_t;
// typedef unsigned int uint16_t;
// typedef long int32_t;
// typedef unsigned long uint32_t;
#include <stdint.h>

/*******************************************************************************
 * MACROS
 *******************************************************************************/
#define ClearArray(arr) memset(arr, 0, sizeof(arr) / sizeof(arr[0]))
#define ClearString(str) memset(str, 0, strlen((const char *)str))
#define ArrayCopy(d, s, l) \
    ClearArray(d);         \
    memcpy(d, s, l)
#define StringCopy(d, s) \
    ClearString(d);      \
    memcpy(d, s, strlen(s))
#define StringAppend(d, s) strcat(d, s)

/*******************************************************************************
 * FUNCTIONS
 *******************************************************************************/
uint8_t ArrayLength(char *arr);
char *my_utoa(char *str, unsigned long value, int radix);

#endif /* DISPLAY_UTILITIES_H_ */