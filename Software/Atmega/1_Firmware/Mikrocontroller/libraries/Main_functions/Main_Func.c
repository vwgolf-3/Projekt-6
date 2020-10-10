/*
 * Main_Func.c
 *
 * Created: 19.01.2020 14:04:18
 *  Author: kimsc
 */

#include "Main_Func.h"
//Init_IO

void IO_init(void)
{
    LED_DDR = LED_OUTPUT_MASK;
    SPI_DDR = SPI_OUTPUT_MASK;
    SPI2_DDR = SPI2_OUTPUT_MASK;
    PUMPE_DDR = PUMPE_OUTPUT_MASK;
    PUMPE_DDR2 = PUMPE2_OUTPUT_MASK;
    PUMPE_DDR3 = PUMPE3_OUTPUT_MASK;
    RFID_DDR = RFID_OUTPUT_MASK;
    FLUSS_DDR = 0b00000000;
    SOFTSPI_DDR = SOFTSPI_OUTPUT_MASK;
    Position = 0;
    count_bla =0;
}

void interfaces_init(void)
{
// Initialisierungen Interfaces
    IO_init();                                              // Ein-/Ausgangspins initialisieren
    SPI_init();                                             // SPI-Schnittstelle initialisieren
    UART_init();                                            // UART-Schnittstelle initialisieren
}

void devices_init(void)
{
    nextion_change_page(25);
    nextion_setText("fehlertxt", "SD-Initialisieren");
    SD_startup();                                           // SD-Karte initialisieren
    _delay_ms(100);
    EN_TMC6200_PORT &= ~EN_TMC6200_BIT;                     // Enable TMC6200 (Active High)

    initTMC4671_Encoder();                                  // FOC-Treiber initialisieren
    initTMC6200();                                          // Gate-Treiber initialisieren
    read_registers_TMC6200();
    read_registers_TMC4671();
    encoder_testdrive();
}

void speicher_init()
{
    // Initialisierungen Speicher
    Uart_Transmit_IT_PC("Zutaten einkaufen...");
    nextion_change_page(25);
    nextion_setText("fehlertxt", "Zutaten einkaufen...");
    zutaten_init();                                         // Zutaten initialisieren

    Uart_Transmit_IT_PC("Cocktailbuch lesen...");
    nextion_setText("fehlertxt", "Cocktailbuch lesen...");
    cocktails_init();                                       // Cocktails initialisieren

    Uart_Transmit_IT_PC("RFID-Tags sammeln...");
    nextion_setText("fehlertxt", "RFID-Tags sammeln...");
    RFID_init();                                            // Tags initialisieren
}

void ramp_init(void)
{
    linear_ramp_init();
    linear_ramp_set_defaults(ramp);

    states = IDLE;
}

void periodic_jobs(linear_ramp_t * ramp)
{
    check_Communication_Input_UART();                   // Prüfen. ob über UART einen Befehl geesendet wurde
	computeRamp(ramp);
}

void heartbeat_LED(void)
{
    toggle_LED();
    _delay_ms(1000);
}

void toggle_LED(void)
{
    LED_PORT = LED_PORT ^ (LEDW_BIT);
}

void my_itoa( int64_t z, char* buffer )
{
    // Reference to: https://www.mikrocontroller.net/attachment/highlight/305548

    int      i = 0;
    int      j;
    char     tmp;
    int64_t  u;    // In u bearbeiten wir den Absolutbetrag von z.
    char     sflag= 0;

    u= z;
    // ist die Zahl negativ?
    // gleich mal ein - hinterlassen und die Zahl positiv machen
    // die einzelnen Stellen der Zahl berechnen
    if (u< 0)
    {
        u= u*(-1);
        sflag= 1;
    }
    do
    {
        buffer[i++] = '0' + (u % 10);
        u /= 10;
    }
    while( u > 0 );
    if (sflag)  {
        buffer[i++]= '-';
    }

    // den String in sich spiegeln
    for( j = 0; j < i / 2; ++j )
    {
        tmp = buffer[j];
        buffer[j] = buffer[i-j-1];
        buffer[i-j-1] = tmp;
    }

    buffer[i] = '\0';
}

void read_Position_TMC4671(void)
{
    // +/- alle 100ms Position abfragen und über Seiriellen Port ausgeben
    static uint8_t cntrr = 0;
    if (cntrr == 100)
    {
        cntrr = 0;
        int64_t val = tmc4671_getActualPosition(0);
        char testarray[100] = {'\0'};
        my_itoa(val, (char *)testarray);
        Uart_Transmit_IT_PC((char *)testarray);
        Uart_Transmit_IT_PC("\r");
    }
    cntrr++;
    _delay_ms(10);
}

char check_Communication_Input_UART_0(void)
{
    char ret = 0;
    // Check Buffer auf Einkommende Daten
    while(RB_length(&rb_rx_PC)>0)
    {
        unsigned char ch = RB_readByte(&rb_rx_PC);
        if (ch == 13)
        {
            INPUT_UART_0[cntr_UART_0] = 0;
            cntr_UART_0 = 0;
            cntr_End_UART_0 = 0;
            ret = 1;
        }
        else
        {
            INPUT_UART_0[cntr_UART_0]=ch;
            cntr_UART_0++;
            ret = 0;
        }
    }
    return ret;
}

void proceed_Communication_Input_UART_0(void)
{
    char buff[5] = {'\0'};
    itoa(INPUT_UART_1[0], (char *)buff, 10);
    Uart_Transmit_IT_PC("Proceed PC: ");
    Uart_Transmit_IT_PC((char *)buff);
    itoa(INPUT_UART_1[1], (char *)buff, 10);
    Uart_Transmit_IT_PC(", ");
    Uart_Transmit_IT_PC((char *)buff);
    Uart_Transmit_IT_PC("\r");
}

char check_Communication_Input_UART_1(void)
{
    char ret = 0;
    while(RB_length(&rb_rx_Display)>0)                  // UART_1
    {

        unsigned char ch = RB_readByte(&rb_rx_Display);

        if (ch == 0xFF && INPUT_UART_1[0] != 'q')
        {
            if (cntr_End_UART_1==0)
            {
                cntr_End_UART_1++;
            }
            else if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF))
            {
                cntr_End_UART_1++;
            }
            else if (cntr_End_UART_1==1 && (INPUT_UART_1[cntr_UART_1-1] != 0xFF))
            {
                cntr_End_UART_1=0;
            }
            else if (cntr_End_UART_1==2 && (INPUT_UART_1[cntr_UART_1-1] == 0xFF) && (INPUT_UART_1[cntr_UART_1-2] == 0xFF))
            {
                cntr_End_UART_1++;
            }
            else if (cntr_End_UART_1==2 && ((INPUT_UART_1[cntr_UART_1-1] != 0xFF) || (INPUT_UART_1[cntr_UART_1-2] != 0xFF)))
            {
                cntr_End_UART_1 = 0;
            }
        }
        if (INPUT_UART_1[0] == 'q' && strlen((const char *)INPUT_UART_1) >=4)
        {
            INPUT_UART_1[0] = 255;
        }
        if (cntr_End_UART_1 == 3)
        {
            INPUT_UART_1[cntr_UART_1] = 0;
            INPUT_UART_1[cntr_UART_1-1]=0;
            INPUT_UART_1[cntr_UART_1-2]=0;
            cntr_UART_1 = 0;
            cntr_End_UART_1 = 0;
            ret = 1;
        }
        else
        {
            INPUT_UART_1[cntr_UART_1]=ch;
            cntr_UART_1++;
            ret = 0;
        }
    }
    return ret;
}

void proceed_Communication_INPUT_UART_1(void)
{
    char buff[5] = {'\0'};
    itoa(INPUT_UART_1[0], (char *)buff, 10);
    Uart_Transmit_IT_PC("Proceed Display: ");
    Uart_Transmit_IT_PC((char *)buff);
    itoa(INPUT_UART_1[1], (char *)buff, 10);
    Uart_Transmit_IT_PC(", ");
    Uart_Transmit_IT_PC((char *)buff);
    Uart_Transmit_IT_PC("\r");

    cocktail_check_command_display(INPUT_UART_1[0], INPUT_UART_1[1]);
}

char check_Communication_Input_UART_2(void)
{
    char ret = 0;
    while(RB_length(&rb_rx_ESP)>0)                  // UART_2
    {
        unsigned char ch = RB_readByte(&rb_rx_ESP);
        // Verbesserung oder Verschlimmbesserung: Falls cntr_UART_1 >=2 dann schauen ob die letzten drei Übertragungen [cntr_UART_1], [cntr_UART_1-1], [cntr_UART_1-2] 0xFF sind
        if (ch == 0xFF)
        {
            if (cntr_End_UART_2==0)
            {
                cntr_End_UART_2++;
            }
            if (cntr_End_UART_2==1 && (INPUT_UART_2[cntr_UART_2-1] == 0xFF))
            {
                cntr_End_UART_2++;
            }
            if (cntr_End_UART_2==1 && (INPUT_UART_2[cntr_UART_2-1] != 0xFF))
            {
                cntr_End_UART_2=0;
            }
            if (cntr_End_UART_2==2 && (INPUT_UART_2[cntr_UART_2-1] == 0xFF) && (INPUT_UART_2[cntr_UART_2-2] == 0xFF))
            {
                cntr_End_UART_2++;
            }
            if (cntr_End_UART_2==2 && ((INPUT_UART_2[cntr_UART_2-1] != 0xFF) || (INPUT_UART_2[cntr_UART_2-2] != 0xFF)))
            {
                cntr_End_UART_2 = 0;
            }
        }
        if (cntr_End_UART_2 == 3)
        {
            INPUT_UART_2[cntr_UART_2] = 0;
            INPUT_UART_2[cntr_UART_2-1]=0;
            INPUT_UART_2[cntr_UART_2-2]=0;
            cntr_UART_2 = 0;
            cntr_End_UART_2 = 0;
            ret = 1;
        }
        else
        {
            INPUT_UART_2[cntr_UART_2]=ch;
            cntr_UART_2++;
            ret = 0;

        }
    }
    return ret;
}

void proceed_Communication_Input_UART_2(void)
{
    char buff[5] = {'\0'};
    itoa(INPUT_UART_1[0], (char *)buff, 10);
    Uart_Transmit_IT_PC("Proceed ESP: ");
    Uart_Transmit_IT_PC((char *)buff);
    itoa(INPUT_UART_1[1], (char *)buff, 10);
    Uart_Transmit_IT_PC(", ");
    Uart_Transmit_IT_PC((char *)buff);
    Uart_Transmit_IT_PC("\r");

    cocktail_check_command_ESP((int8_t) INPUT_UART_2[0], (int8_t) INPUT_UART_2[1]);
}

void check_Communication_Input_UART(void)
{
    if (check_Communication_Input_UART_0())             // Check UART_0 (USB), ob vollständige Übertragung stattgefunden hat (Ende = "\r")
    {
        proceed_Communication_Input_UART_0();               // Vollständige Übertragung des USB verarbeiten
    }
    if (check_Communication_Input_UART_1())             // Check UART_1 (Nextion-Display), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
    {
        proceed_Communication_INPUT_UART_1();               // Vollständige Übertragung des Displays verarbeiten
    }
    if (check_Communication_Input_UART_2())             // Check UART_2 (ESP), ob vollständige Übertragung stattgefunden hat (Ende = "0xFF 0xFF 0xFF")
    {
        proceed_Communication_Input_UART_2();               // Vollständige Übertragung des ESP's verarbeiten
    }
}