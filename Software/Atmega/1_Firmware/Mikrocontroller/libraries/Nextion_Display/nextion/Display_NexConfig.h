
#ifndef __NEXCONFIG_H__
#define __NEXCONFIG_H__
#include "Display_Serial.h"

#define nexSerial_init(b)        Serial_Init(b)
#define nexSerial_available()    Serial_Available()
#define nexSerial_read()         Serial_Read()
#define nexSerial_write(d)       Serial_Write(d)
#define nexSerial_print(p)       Serial_Print(p) 
#define nexSerial_readBytes(b,l) Serial_ReadBytes(b, l)

#include <util/delay.h>									//Benutzerdefiniertes Delay
#define nexDelay(d)              _delay_ms(d)

#endif /* #ifndef __NEXCONFIG_H__ */
