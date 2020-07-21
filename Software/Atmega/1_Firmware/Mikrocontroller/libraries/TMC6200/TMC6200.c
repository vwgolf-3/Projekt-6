/*
 * TMC6200.c
 *
 *  Created on: 14.03.2018
 *      Author: ED
 */

#include "TMC6200.h"
#include <util/delay.h>
// => SPI wrapper
extern uint8_t tmc6200_readwriteByte(uint8_t motor, uint8_t data, uint8_t lastTransfer);
// <= SPI wrapper

// spi access
int tmc6200_readInt(uint8_t motor, uint8_t address)
{	
	unsigned char rbuf[5];
	int value;
	
	enable_Slave(TMC6200);
	// write address
//  	spi_transmit_IT((unsigned char *)tbuf, 1, TMC6200);
	spi_transmit(address & 0x7F);
	// read data
	for(int k = 0 ; k<4 ; k++)
	{
		rbuf[k] = spi_transmit(0x00);
	}
	disable_Slave(TMC6200);
	value =rbuf[0];
	value <<= 8;
	value |= rbuf[1];
	value <<= 8;
	value |= rbuf[2];
	value <<= 8;
	value |= rbuf[3];
	return value;
}

void tmc6200_writeInt(uint8_t motor, uint8_t address, uint32_t value)
{
	unsigned char tbuf[5];

	//set Write-Bit
	tbuf[0] = address | 0x80;
	
	tbuf[1] = 0xFF & (value>>24);
	tbuf[2] = 0xFF & (value>>16);
	tbuf[3] = 0xFF & (value>>8);
	tbuf[4] = 0xFF & value;
	enable_Slave(TMC6200);
	
	spi_transmit_IT(tbuf, 5, TMC6200);
	
	disable_Slave(TMC6200);
}

void initTMC6200(void)
{
	tmc6200_writeInt(MOTOR0, TMC6200_GCONF, 0x00000000);
	tmc6200_writeInt(MOTOR0, TMC6200_OTP_PROG, 0x00000000);
	tmc6200_writeInt(MOTOR0, TMC6200_FACTORY_CONF, 0x0000000C);
	tmc6200_writeInt(MOTOR0, TMC6200_SHORT_CONF, 0x12010606);
	tmc6200_writeInt(MOTOR0, TMC6200_DRV_CONF, 0x00080004);
	_delay_ms(100);
 	EN_TMC6200_PORT |= EN_TMC6200_BIT;
}