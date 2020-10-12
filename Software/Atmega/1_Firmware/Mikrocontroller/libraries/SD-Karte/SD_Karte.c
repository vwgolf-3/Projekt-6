/*
 * SD_Karte.c
 *
 * Created: 12.10.2020 17:22:31
 *  Author: kimsc
 */ 
#include "SD_Karte.h"


void SD_init()
{
    // timer0 config  **************************************************
    // initialisierung, auf jeden fall vor mmc_init(),
    // denn da wird der timer benoetigt!
    timer0_init();

    Uart_Transmit_IT_PC("\nBootSD");

    // sd/mmc config  **************************************************
    if( FALSE == mmc_init() ) {
	    return;
    }

    Uart_Transmit_IT_PC("...");

    // fat config ******************************************************
    if( FALSE == fat_loadFatData() ) {
	    return;
    }

    // wenn auf dem terminal "Boot...OK" zu lesen ist, war initialisierung erfolgreich!
    Uart_Transmit_IT_PC("OK\n");
}


void timer0_init(void)
{

	TimingDelay = 0;		// initialisierung der zaehl variable

	TCCR0A = 1<<WGM01; 		// timer0 im ctc mode
	TIMSK0 = 1<<OCIE0A;		// compare interrupt an

	TCNT0 = START_TCNT;		// ab wo hochgezaehlt wird,
	OCR0A = TOP_OCR;		// maximum bis wo gezaehlt wird bevor compare match

	TCCR0B = PRESCALER;		// wenn prescaler gesetzt wird, lauft timer los
	sei();					// interrupts anschalten, wegen compare match
}

ISR (TIMER0_COMPA_vect)
{
	TimingDelay = (TimingDelay==0) ? 0 : TimingDelay-1;
}

#if (MMC_LS == TRUE)
// *****************************************************************************************************************
int8_t *ltostr(int32_t num, int8_t *string, uint16_t max_chars, uint8_t base)
{
	int8_t remainder;
	int sign = 0;   /* number of digits occupied by the sign. */

	if (base < 2 || base > 36)
	return FALSE;

	if (num < 0)
	{
		sign = 1;
		num = -num;
	}

	string[--max_chars] = '\0';

	for (max_chars--; max_chars > sign && num!=0; max_chars --)
	{
		remainder = (int8_t) (num % base);
		if ( remainder <= 9 )
		string[max_chars] = remainder + '0';
		else  string[max_chars] = remainder - 10 + 'A';
		num /= base;
	}

	if (sign)
	string[--max_chars] = '-';

	if ( max_chars > 0 )
	memset(string, ' ', max_chars+1);

	return string + max_chars;
}
#endif



void writeFile(uint8_t * file_name, uint8_t * str)
{
	#if (MMC_WRITE ==TRUE)      // create and append only if write is TRUE
	// ****************************************************
	// if file exists, it will be opened and then append to it.
	if( MMC_FILE_OPENED == ffopen(file_name,'r') ) {
		ffseek(file.length);
		ffwrites(str);
		ffwrite(0x0D);      // new line in file
		ffwrite(0x0A);
		ffclose();
	}

	// ***************************************************
	// if the file does not exist, it will be created and written to it.
	if(MMC_FILE_CREATED == ffopen(file_name,'c') ) {
		ffwrites(str);
		ffwrite(0x0D);      // new line in file
		ffwrite(0x0A);
		ffclose();
	}
	#endif
}

void readFile(uint8_t * file_name)
{
	// ***************************************************
	// read file complete and print via uart!
	if( MMC_FILE_OPENED == ffopen(file_name,'r') )
	{
		Uart_Transmit_IT_PC((char *)fat.sector);
		ffclose();
	}
}

void deleteFile(uint8_t * file_name)
{
	ffrm(file_name);
}

uint8_t verifyFile(uint8_t * file_name)
{
	uint8_t ret = 0;
	if(MMC_FILE_OPENED == ffopen(file_name,'r'))
	{
		ret = 1;
	}
	return ret;
}
