/*
 * TMC6200.c
 *
 *  Created on: 14.03.2018
 *      Author: ED
 */

#include "TMC6200.h"
#include <util/delay.h>

// spi access
int tmc6200_readInt(uint8_t debug_message, uint8_t address)
{	
	// Read-Buffer (Array uint8_t)
	char rbuf[6] = {'\0'};
	
	// Return-Value (uint32_t)
	int value;
	
	// Read-Mode (First Bit = 0)
	address &= 0x7F;
	
	rbuf[0] = address;
	
	// CS TMC6200 LOW
	enable_Slave(TMC6200);

	// write address
	spi_transmit(address);
	
	// read 4 Bytes data
	for(int k = 1 ; k<5 ; k++)
	{
		rbuf[k] = spi_receive();
	}
	
	// CS TMC600 HIGH
	disable_Slave(TMC6200);
	
	// Generate uint32_t return value
	value = rbuf[1];
	value <<= 8;
	value |= rbuf[2];
	value <<= 8;
	value |= rbuf[3];
	value <<= 8;
	value |= rbuf[4];
	
	if (debug_message == 1)
	{
		// Show received data via serial port
		Uart_Transmit_IT_PC("Read TMC6200 data: ");
		for (int count = 0 ; count < 5 ; count++)
		{
			// itoa-Buffer (Debug)
			char buff[5] = {'0'};
			
			if (rbuf[count] == 0)
			{
				Uart_Transmit_IT_PC("00");
			}
			else if (rbuf[count] < 0x10)
			{
				Uart_Transmit_IT_PC("0");
				itoa(rbuf[count],(char *)buff, 16);
				Uart_Transmit_IT_PC((char *)buff);
			}
			else
			{
				itoa(rbuf[count],(char *)buff, 16);
				Uart_Transmit_IT_PC((char *)buff);
			}
			if (count <4)
			{
				Uart_Transmit_IT_PC(",");
			}
		}
		_delay_ms(10);
		Uart_Transmit_IT_PC("\r");
	}
	
	// Return uint32_t value
	return value;
}

void tmc6200_writeInt(uint8_t debug_message, uint8_t address, uint32_t value)
{
	// Buffer transmit Data
	char tbuf[6] = {'\0'};

	// Write-mode (first Bit = 1)
	address |= 0x80;
	
	// Write address at first place
	tbuf[0] = address;
	
	// Generate Array out of data
	tbuf[1] = 0xFF & (value>>24);
	tbuf[2] = 0xFF & (value>>16);
	tbuf[3] = 0xFF & (value>>8);
	tbuf[4] = 0xFF & value;
	
	// Show transmitted data via serial port

	if (debug_message==1)
	{
		// itoa-Buffer (Debug)
		char buff[5] = {'\0'};
		
		Uart_Transmit_IT_PC("Write TMC6200 data: ");
		for (int count = 0 ; count < 5 ; count++)
		{
			if (tbuf[count] == 0)
			{
				Uart_Transmit_IT_PC("00");
			}
			else if (tbuf[count] < 0x10)
			{
				Uart_Transmit_IT_PC("0");
				itoa(tbuf[count],(char *)buff, 16);
				Uart_Transmit_IT_PC((char *)buff);
			}
			else
			{
				itoa(tbuf[count],(char *)buff, 16);
				Uart_Transmit_IT_PC((char *)buff);
			}
			if (count <4)
			{
				Uart_Transmit_IT_PC(",");
			}
		}
		_delay_ms(10);
		Uart_Transmit_IT_PC("\r");
	}

	// CS TMC6200 LOW
	enable_Slave(TMC6200);
	
	// Transmit address and data
	spi_transmit_IT((unsigned char *)tbuf, 5, TMC6200);
	
	// CS TMC6200 HIGH
	disable_Slave(TMC6200);
}

void initTMC6200(void)
{

	EN_TMC6200_PORT |= EN_TMC6200_BIT;						// Enable TMC6200 (Active High)
	_delay_ms(100);
	EN_TMC6200_PORT &= ~EN_TMC6200_BIT;						// Enable TMC6200 (Active High)
	_delay_ms(100);
	EN_TMC6200_PORT |= EN_TMC6200_BIT;						// Enable TMC6200 (Active High)
	_delay_ms(1000);
	
	tmc6200_writeInt(0, TMC6200_GCONF, 0x00000000);		// current amplification: 20
	tmc6200_writeInt(0, TMC6200_GSTAT, 0x00000000);		// current amplification: 20
	tmc6200_writeInt(0, TMC6200_OTP_PROG, 0x00000000);     //
	tmc6200_writeInt(0, TMC6200_FACTORY_CONF, 0x0000000F); // clock frequency: 12MHz
	tmc6200_writeInt(0, TMC6200_SHORT_CONF, 0x13010606);	// default
	tmc6200_writeInt(0, TMC6200_DRV_CONF, 0x00080004);		// DRVSTRENGTH = 2 (medium), BBMCLKS: 4

// 		tmc6200_writeInt(MOTOR0, TMC6200_GCONF, 0x00000010);// current amplification: 10
// 		tmc6200_writeInt(0, TMC6200_OTP_PROG, 0x00000000);
// 		tmc6200_writeInt(0, TMC6200_FACTORY_CONF, 0x0000000F); // clock frequency: 12MHz
// 		tmc6200_writeInt(MOTOR0, TMC6200_SHORT_CONF, 0x13010606);
// 		tmc6200_writeInt(MOTOR0, TMC6200_DRV_CONF, 0x00080004);
}

void read_registers_TMC6200(void)
{	
	tmc6200_readInt(1, TMC6200_GCONF);
	tmc6200_readInt(1, TMC6200_GSTAT);
	tmc6200_readInt(1, TMC6200_IOIN_OUTPUT);
	tmc6200_readInt(1, TMC6200_OTP_PROG);
	tmc6200_readInt(1, TMC6200_OTP_READ);
	tmc6200_readInt(1, TMC6200_FACTORY_CONF);
	tmc6200_readInt(1, TMC6200_SHORT_CONF);
	tmc6200_readInt(1, TMC6200_DRV_CONF);
	_delay_ms(100);
}