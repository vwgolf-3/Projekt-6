/*
 * Serial.h
 *
 * Created: 19.01.2020 20:46:58
 *  Author: kimsc
 */ 


#ifndef DISPLAY_SERIAL_H_
#define DISPLAY_SERIAL_H_

/*************************************************************************
* MACROS
*************************************************************************/
#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 64
#define RX_Flush() _rx_buffer_head=0;_rx_buffer_tail=0
#define TX_Flush() _tx_buffer_head=0;_tx_buffer_tail=0
/*************************************************************************
* FUNCTIONS
*************************************************************************/
void Serial_Init(long baudrate);
unsigned char Serial_Write(unsigned char c);
unsigned char Serial_Read();
unsigned char Serial_Available();
unsigned char Serial_ReadBytes(char *buf, unsigned char len);
void Serial_Print(unsigned char *txt);



#endif /* DISPLAY_SERIAL_H_ */