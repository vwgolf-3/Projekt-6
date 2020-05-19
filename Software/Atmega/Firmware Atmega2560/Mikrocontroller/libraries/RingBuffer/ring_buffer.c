/*
 * ring_buffer.c
 *
 * Created: 14/03/2017 10:11:23
 *  Author: Jonathan
 */ 

#include "ring_buffer.h"


// Initialisiert Ring Buffer
void RB_init( ring_buffer_t *rb )
{
	rb->tail = 0;
	rb->head = 0;
}

// Gibt Anzahl freie Plätze im Buffer zurück
unsigned char RB_free( ring_buffer_t *rb )
{
	unsigned char free;
	
	if (rb->head >= rb->tail)
	{
		free = RING_BUFFER_SIZE -(rb->head - rb->tail);
	} 
	else
	{
		free = rb->tail - rb->head;
	}
	
	return free;
}

unsigned char RB_length( ring_buffer_t *rb )
{
	unsigned char len;
	
	if (rb->head >= rb->tail)
	{
		len = rb->head - rb->tail;
	} 
	else
	{
		len = RING_BUFFER_SIZE - (rb->tail - rb->head);
	}
	
	return len;
}

unsigned char RB_readByte( ring_buffer_t *rb )
{
	unsigned char tail;
	unsigned char ret;
	
	tail = rb->tail;
	
	if (RB_length(rb) == 0)
	{
		return 0;
	}
	
	ret = rb->data[tail++];
	if (tail >= RING_BUFFER_SIZE)
	{
		tail = 0;
	}
	
	rb->tail = tail;
	
	return ret;
}

unsigned char RB_writeByte( ring_buffer_t *rb, unsigned char data )
{
	unsigned char head;
	
	head = rb->head;
	
	while(RB_free(rb) < 1);	
	if(data == 0x00){
		data = 0xFF;
	}
	rb->data[head++] = data;
	if (head >= RING_BUFFER_SIZE)
	{
		head = 0;
	}
	rb->head = head;
	
	return 1;
}

unsigned char RB_read( ring_buffer_t *rb, unsigned char *data, unsigned char datal )
{
	unsigned char tail;
	
	tail = rb->tail;
	
	if (datal == 0 || RB_length(rb) == 0)
	{
		return 0;
	}
	
	if (RB_length(rb) < datal)
	{
		datal = RB_length(rb);
	}
	
	while(datal--)
	{
		*data++ = rb->data[tail++];
		if (tail >= RING_BUFFER_SIZE)
		{
			tail = 0;			
		}
	}
	rb->tail = tail;
	
	return 1;
}

unsigned char RB_write( ring_buffer_t *rb, char *data, unsigned char datal )
{
	unsigned char head;
	
	head = rb->head;
	
	if (datal == 0)
	{
		return  0;
	}
	
	while(RB_free(rb) < datal);
	
	while(datal--)
	{
		rb->data[head++] = *data++;
		if (head >= RING_BUFFER_SIZE)
		{
			head = 0;
		}
	}
	
	rb->head = head;
	
	return 1;
}




