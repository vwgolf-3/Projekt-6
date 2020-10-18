/*
 * TMC4671.c
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */
#include "TMC4671.h"


// ===>>SPI-Wrapper

void tmc4671_writeDatagram(unsigned int motor, unsigned char address, unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4)
{
    int value = x1;
    value <<= 8;
    value |= x2;
    value <<= 8;
    value |= x3;
    value <<= 8;
    value |= x4;

    tmc40bit_writeInt(motor, address, value);
}

void tmc4671_writeInt(unsigned int motor, unsigned char address, unsigned long value)
{
    tmc40bit_writeInt(motor, address, value);
}

int32_t tmc4671_readInt(unsigned int motor, unsigned char address)
{
    return tmc40bit_readInt(motor, address);
}

void tmc40bit_writeInt(unsigned int debug_message, unsigned char address, unsigned long value)
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

    if (debug_message == 1)
    {

        // Show received data via serial port

        // itoa-Buffer (Debug)
        char buff[5] = {'\0'};

        // Show transmitted data via serial port

        Uart_Transmit_IT_PC("Write TMC4671 data: ");
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
    enable_Slave(TMC4671);

    // Transmit address and data
    for (int count = 0 ; count < 5; count ++)
    {
        softspi_write_uint8(tbuf[count]);
    }

    // CS TMC6200 HIGH
    disable_Slave(TMC4671);
}

int32_t tmc40bit_readInt(unsigned int debug_message, unsigned char address)
{
    // Read-Buffer (Array uint8_t)
    char rbuf[6] = {'\0'};

    // Return-Value (uint32_t)
    int32_t value = 0;

    // Read-Mode (First Bit = 0)
    address &= 0x7F;

    rbuf[0] = (char)address;

    // CS TMC6200 LOW
    enable_Slave(TMC4671);

    // write address
    softspi_write_uint8(address);

    // read 4 Bytes data
    for(int k = 1 ; k<5 ; k++)
    {
        rbuf[k] = softspi_read_uint8();
    }

    // CS TMC600 HIGH
    disable_Slave(TMC4671);

    // Generate uint32_t return value
    value |= rbuf[1];
    value <<= 8;
    value |= rbuf[2];
    value <<= 8;
    value |= rbuf[3];
    value <<= 8;
    value |= rbuf[4];

    if (debug_message == 1)
    {
        // Show received data via serial port
        Uart_Transmit_IT_PC("Read TMC4671 data: ");
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

    // Return int32_t value
    return value;
}


void initTMC4671_Openloop(void)
{
// Motor type &  PWM configuration
tmc4671_writeInt(0, TMC4671_PWM_POLARITIES, 0x00000000);
tmc4671_writeInt(0, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, 0x00030003);
tmc4671_writeInt(0, TMC4671_PWM_MAXCNT, 0x00000F9F);
tmc4671_writeInt(0, TMC4671_PWM_BBM_H_BBM_L, 0x00001919);
tmc4671_writeInt(0, TMC4671_PWM_SV_CHOP, 0x00000007);

// Open loop settings
tmc4671_writeInt(0, TMC4671_OPENLOOP_MODE, 0x00000000);
tmc4671_writeInt(0, TMC4671_OPENLOOP_ACCELERATION, 0x0000003C);
tmc4671_writeInt(0, TMC4671_OPENLOOP_VELOCITY_TARGET, 0xFFFFFFF6);

// Feedback selection
tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000002);
tmc4671_writeInt(0, TMC4671_UQ_UD_EXT, 0x00000FA0);

// ===== Open loop test drive =====

// Switch to open loop velocity mode
tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000008);

// Rotate right
tmc4671_writeInt(0, TMC4671_OPENLOOP_VELOCITY_TARGET, 0x0000003C);
_delay_ms(2000);

// Rotate left
tmc4671_writeInt(0, TMC4671_OPENLOOP_VELOCITY_TARGET, 0xFFFFFFC4);
_delay_ms(4000);

// Stop
tmc4671_writeInt(0, TMC4671_OPENLOOP_VELOCITY_TARGET, 0x00000000);
_delay_ms(2000);
tmc4671_writeInt(0, TMC4671_UQ_UD_EXT, 0x00000000);
}

void read_registers_TMC4671(void)
{
    uint8_t deb = 1;
    tmc4671_readInt(deb, TMC4671_MOTOR_TYPE_N_POLE_PAIRS);
    tmc4671_readInt(deb, TMC4671_PWM_POLARITIES);
    tmc4671_readInt(deb, TMC4671_PWM_MAXCNT);
    tmc4671_readInt(deb, TMC4671_PWM_BBM_H_BBM_L);
    tmc4671_readInt(deb, TMC4671_PWM_SV_CHOP);
    tmc4671_readInt(deb, TMC4671_OPENLOOP_MODE);
    tmc4671_readInt(deb, TMC4671_OPENLOOP_ACCELERATION);
    tmc4671_readInt(deb, TMC4671_OPENLOOP_VELOCITY_TARGET);
}

void encoder_testdrive(void)
{
// ===== ABN encoder test drive =====

// Init encoder (mode 0)
    tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000008);
    tmc4671_writeInt(0, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, 0x00000000);
    tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000001);
    tmc4671_writeInt(0, TMC4671_PHI_E_EXT, 0x00000000);
    tmc4671_writeInt(0, TMC4671_UQ_UD_EXT, 0x000007D0);
    tmc4671_writeInt(0, TMC4671_ABN_DECODER_COUNT, 0x00000000);

// Feedback selection
    tmc4671_writeInt(0, TMC4671_PHI_E_SELECTION, 0x00000003);
    tmc4671_writeInt(0, TMC4671_VELOCITY_SELECTION, 0x00000009);

// Switch to torque mode
    tmc4671_writeInt(0, TMC4671_MODE_RAMP_MODE_MOTION, 0x00000001);

// Rotate right
    tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0x03E80000);
    _delay_ms(500);

// Rotate left
    tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0xFC180000);
    _delay_ms(500);

//Stop
    tmc4671_writeInt(0, TMC4671_PID_TORQUE_FLUX_TARGET, 0x00000000);
}

void initTMC4671_Encoder(void)
{
    uint8_t deb = 0;

//====================================================================================================//
// Status Information
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_CHIPINFO_ADDR,                      0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 0 = 0x01(CHIPINFO_ADDR)
//  tmc4671_writeInt(deb, TMC4671_STATUS_FLAGS,                       0xC0788088);        // writing value 0xC0788088 = 0 = 0.0 to address 83 = 0x7C(STATUS_FLAGS)
//  tmc4671_writeInt(deb, TMC4671_STATUS_MASK,                        0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 84 = 0x7D(STATUS_MASK)

//====================================================================================================//
// Motor type &  PWM configuration
//====================================================================================================//

    tmc4671_writeInt(deb, TMC4671_PWM_POLARITIES,                     0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 15 = 0x17(PWM_POLARITIES)
    tmc4671_writeInt(deb, TMC4671_MOTOR_TYPE_N_POLE_PAIRS,            0x00030003);        // writing value 0x00030003 = 196611 = 0.0 to address 19 = 0x1B(MOTOR_TYPE_N_POLE_PAIRS)
    tmc4671_writeInt(deb, TMC4671_PWM_MAXCNT,                         0x00000F9F);        // writing value 0x00000F9F = 3999 = 0.0 to address 16 = 0x18(PWM_MAXCNT)
    tmc4671_writeInt(deb, TMC4671_PWM_BBM_H_BBM_L,                    0x00001919);        // writing value 0x00001919 = 6425 = 0.0 to address 17 = 0x19(PWM_BBM_H_BBM_L)
    tmc4671_writeInt(deb, TMC4671_PWM_SV_CHOP,                        0x00000007);        // writing value 0x00000007 = 7 = 0.0 to address 18 = 0x1A(PWM_SV_CHOP)

//====================================================================================================//
// General settings
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_PHI_E_EXT,                          0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 20 = 0x1C(PHI_E_EXT)
//  tmc4671_writeInt(deb, TMC4671_PHI_M_EXT,                          0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 21 = 0x1D(PHI_M_EXT)
//  tmc4671_writeInt(deb, TMC4671_POSITION_EXT,                       0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 22 = 0x1E(POSITION_EXT)
//  tmc4671_writeInt(deb, TMC4671_VELOCITY_SELECTION,                 0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 53 = 0x50(VELOCITY_SELECTION)
//  tmc4671_writeInt(deb, TMC4671_POSITION_SELECTION,                 0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 54 = 0x51(POSITION_SELECTION)
//  tmc4671_writeInt(deb, TMC4671_PHI_E_SELECTION,                    0x00000003);        // writing value 0x00000003 = 3 = 0.0 to address 55 = 0x52(PHI_E_SELECTION)
//  tmc4671_writeInt(deb, TMC4671_UART_BPS,                           0x00009600);        // writing value 0x00009600 = 38400 = 0.0 to address 80 = 0x79(UART_BPS)
//  tmc4671_writeInt(deb, TMC4671_UART_ADDRS,                         0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 81 = 0x7A(UART_ADDRS)

//====================================================================================================//
// ADC configuration
//====================================================================================================//

    tmc4671_writeInt(deb, TMC4671_ADC_I_SELECT,                       0x24000100);        // writing value 0x24000100 = 603980032 = 0.0 to address 8 = 0x0A(ADC_I_SELECT)
    tmc4671_writeInt(deb, TMC4671_dsADC_MCFG_B_MCFG_A,                0x00100010);        // writing value 0x00100010 = 1048592 = 0.0 to address 2 = 0x04(dsADC_MCFG_B_MCFG_A)
    tmc4671_writeInt(deb, TMC4671_dsADC_MCLK_A,                       0x20000000);        // writing value 0x20000000 = 536870912 = 0.0 to address 3 = 0x05(dsADC_MCLK_A)
    tmc4671_writeInt(deb, TMC4671_dsADC_MCLK_B,                       0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 4 = 0x06(dsADC_MCLK_B)
    tmc4671_writeInt(deb, TMC4671_dsADC_MDEC_B_MDEC_A,                0x014E014E);        // writing value 0x014E014E = 21889358 = 0.0 to address 5 = 0x07(dsADC_MDEC_B_MDEC_A)
    tmc4671_writeInt(deb, TMC4671_ADC_I0_SCALE_OFFSET,                0xFF008073);        // writing value 0xFF008234 = 0 = 0.0 to address 7 = 0x09(ADC_I0_SCALE_OFFSET)
    tmc4671_writeInt(deb, TMC4671_ADC_I1_SCALE_OFFSET,                0xFF008E1B);        // writing value 0xFF00890A = 0 = 0.0 to address 6 = 0x08(ADC_I1_SCALE_OFFSET)

//  tmc4671_writeInt(deb, TMC4671_ADC_RAW_ADDR,                       0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 1 = 0x03(ADC_RAW_ADDR)
//  tmc4671_writeInt(deb, TMC4671_ADC_I1_I0_EXT,                      0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 9 = 0x0B(ADC_I1_I0_EXT)
//  tmc4671_writeInt(deb, TMC4671_DS_ANALOG_INPUT_STAGE_CFG,          0x00044400);        // writing value 0x00044400 = 279552 = 0.0 to address 10 = 0x0C(DS_ANALOG_INPUT_STAGE_CFG)
//  tmc4671_writeInt(deb, TMC4671_AENC_0_SCALE_OFFSET,                0x01000000);        // writing value 0x01000000 = 16777216 = 0.0 to address 11 = 0x0D(AENC_0_SCALE_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_AENC_1_SCALE_OFFSET,                0x01000000);        // writing value 0x01000000 = 16777216 = 0.0 to address 12 = 0x0E(AENC_1_SCALE_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_AENC_2_SCALE_OFFSET,                0x01000000);        // writing value 0x01000000 = 16777216 = 0.0 to address 13 = 0x0F(AENC_2_SCALE_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_AENC_SELECT,                        0x03020100);        // writing value 0x03020100 = 50462976 = 0.0 to address 14 = 0x11(AENC_SELECT)
//  tmc4671_writeInt(deb, TMC4671_WATCHDOG_CFG,                       0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 77 = 0x74(WATCHDOG_CFG)
//  tmc4671_writeInt(deb, TMC4671_ADC_VM_LIMITS,                      0xFFFFFFFF);        // writing value 0xFFFFFFFF = 0 = 0.0 to address 78 = 0x75(ADC_VM_LIMITS)

//====================================================================================================//
// Openloop settings
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_OPENLOOP_MODE,                      0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 23 = 0x1F(OPENLOOP_MODE)
//  tmc4671_writeInt(deb, TMC4671_OPENLOOP_ACCELERATION,              0x0000003C);        // writing value 0x0000003C = 60 = 0.0 to address 24 = 0x20(OPENLOOP_ACCELERATION)
//  tmc4671_writeInt(deb, TMC4671_OPENLOOP_VELOCITY_TARGET,           0xFFFFFFF6);        // writing value 0xFFFFFFF6 = 0 = 0.0 to address 25 = 0x21(OPENLOOP_VELOCITY_TARGET)
//  tmc4671_writeInt(deb, TMC4671_OPENLOOP_VELOCITY_ACTUAL,           0xFFFFFFF6);        // writing value 0xFFFFFFF6 = 0 = 0.0 to address 26 = 0x22(OPENLOOP_VELOCITY_ACTUAL)
//  tmc4671_writeInt(deb, TMC4671_OPENLOOP_PHI,                       0x0000AE11);        // writing value 0x0000AE11 = 44561 = 0.0 to address 27 = 0x23(OPENLOOP_PHI)


//====================================================================================================//
// ABN encoder settings
//====================================================================================================//

    tmc4671_writeInt(deb, TMC4671_ABN_DECODER_MODE,                   0x0000100A);        // writing value 0x00001000 = 4096 = 0.0 to address 29 = 0x25(ABN_DECODER_MODE)
    tmc4671_writeInt(deb, TMC4671_ABN_DECODER_PPR,                    0x00002000);        // writing value 0x00002000 = 8192 = 0.0 to address 30 = 0x26(ABN_DECODER_PPR)
    tmc4671_writeInt(deb, TMC4671_ABN_DECODER_COUNT,                  0x00000000);        // writing value 0x000013A9 = 5033 = 0.0 to address 31 = 0x27(ABN_DECODER_COUNT)
    tmc4671_writeInt(deb, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET,     0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 33 = 0x29(ABN_DECODER_PHI_E_PHI_M_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_ABN_DECODER_COUNT_N,                0x00001FE7);        // writing value 0x00001FE7 = 8167 = 0.0 to address 32 = 0x28(ABN_DECODER_COUNT_N)

//====================================================================================================//
// ABN2 encoder settings
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_ABN_2_DECODER_MODE,                 0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 34 = 0x2C(ABN_2_DECODER_MODE)
//  tmc4671_writeInt(deb, TMC4671_ABN_2_DECODER_PPR,                  0x00010000);        // writing value 0x00010000 = 65536 = 0.0 to address 35 = 0x2D(ABN_2_DECODER_PPR)
//  tmc4671_writeInt(deb, TMC4671_ABN_2_DECODER_COUNT,                0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 36 = 0x2E(ABN_2_DECODER_COUNT)
//  tmc4671_writeInt(deb, TMC4671_ABN_2_DECODER_COUNT_N,              0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 37 = 0x2F(ABN_2_DECODER_COUNT_N)
//  tmc4671_writeInt(deb, TMC4671_ABN_2_DECODER_PHI_M_OFFSET,         0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 38 = 0x30(ABN_2_DECODER_PHI_M_OFFSET)

//====================================================================================================//
// HALL settings
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_HALL_MODE,                          0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 39 = 0x33(HALL_MODE)
//  tmc4671_writeInt(deb, TMC4671_HALL_POSITION_060_000,              0x2AAA0000);        // writing value 0x2AAA0000 = 715784192 = 0.0 to address 40 = 0x34(HALL_POSITION_060_000)
//  tmc4671_writeInt(deb, TMC4671_HALL_POSITION_180_120,              0x80005555);        // writing value 0x80005555 = 0 = 0.0 to address 41 = 0x35(HALL_POSITION_180_120)
//  tmc4671_writeInt(deb, TMC4671_HALL_POSITION_300_240,              0xD555AAAA);        // writing value 0xD555AAAA = 0 = 0.0 to address 42 = 0x36(HALL_POSITION_300_240)
//  tmc4671_writeInt(deb, TMC4671_HALL_PHI_E_PHI_M_OFFSET,            0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 43 = 0x37(HALL_PHI_E_PHI_M_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_HALL_DPHI_MAX,                      0x00002AAA);        // writing value 0x00002AAA = 10922 = 0.0 to address 44 = 0x38(HALL_DPHI_MAX)

//====================================================================================================//
// AENC settings
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_MODE,                  0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 45 = 0x3B(AENC_DECODER_MODE)
//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_N_MASK_N_THRESHOLD,    0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 46 = 0x3C(AENC_DECODER_N_THRESHOLD)
//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_PHI_A_OFFSET,          0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 47 = 0x3E(AENC_DECODER_PHI_A_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_PPR,                   0x00000001);        // writing value 0x00000001 = 1 = 0.0 to address 48 = 0x40(AENC_DECODER_PPR)
//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_COUNT_N,               0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 49 = 0x42(AENC_DECODER_COUNT_N)
//  tmc4671_writeInt(deb, TMC4671_AENC_DECODER_PHI_E_PHI_M_OFFSET,    0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 50 = 0x45(AENC_DECODER_PHI_E_PHI_M_OFFSET)

//====================================================================================================//
// Inputs/Outputs
//====================================================================================================//

//  tmc4671_writeInt(deb, TMC4671_STEP_WIDTH,                         0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 79 = 0x78(STEP_WIDTH)
//  tmc4671_writeInt(deb, TMC4671_GPIO_dsADCI_CONFIG,                 0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 82 = 0x7B(GPIO_dsADCI_CONFIG)

//====================================================================================================//
// Limits
//====================================================================================================//

    tmc4671_writeInt(deb, TMC4671_PID_TORQUE_FLUX_TARGET_DDT_LIMITS,  0x00007FFF);        // writing value 0x00007FFF = 32767 = 0.0 to address 60 = 0x5C(PID_TORQUE_FLUX_TARGET_DDT_LIMITS)
    tmc4671_writeInt(deb, TMC4671_PIDOUT_UQ_UD_LIMITS,                0x00005A81);        // writing value 0x00005A81 = 23169 = 0.0 to address 61 = 0x5D(PIDOUT_UQ_UD_LIMITS)
    tmc4671_writeInt(deb, TMC4671_PID_TORQUE_FLUX_LIMITS,             0x000009C4);        // writing value 0x000007D0 = 2000 = 0.0 to address 62 = 0x5E(PID_TORQUE_FLUX_LIMITS)
    tmc4671_writeInt(deb, TMC4671_PID_ACCELERATION_LIMIT,             0x000000C8);        // writing value 0x0000001E = 30 = 0.0 to address 63 = 0x5F(PID_ACCELERATION_LIMIT)
    tmc4671_writeInt(deb, TMC4671_PID_VELOCITY_LIMIT,                 0x000005DC);        // writing value 0x000000C8 = 200 = 0.0 to address 64 = 0x60(PID_VELOCITY_LIMIT)
    tmc4671_writeInt(deb, TMC4671_PID_POSITION_LIMIT_LOW,             0x80000001);        // writing value 0x80000001 = 0 = 0.0 to address 65 = 0x61(PID_POSITION_LIMIT_LOW)
    tmc4671_writeInt(deb, TMC4671_PID_POSITION_LIMIT_HIGH,            0x7FFFFFFF);        // writing value 0x7FFFFFFF = 2147483647 = 0.0 to address 66 = 0x62(PID_POSITION_LIMIT_HIGH)
//====================================================================================================//
// PI settings
//====================================================================================================//

    tmc4671_writeInt(deb, TMC4671_PID_TORQUE_P_TORQUE_I,              0x01F403E8);        // writing value 0x01F403E8 = 32769000 = 0.0 to address 57 = 0x56(PID_TORQUE_P_TORQUE_I)
    tmc4671_writeInt(deb, TMC4671_PID_FLUX_P_FLUX_I,                  0x01F403E8);        // writing value 0x01F403E8 = 32769000 = 0.0 to address 56 = 0x54(PID_FLUX_P_FLUX_I)
    tmc4671_writeInt(deb, TMC4671_PID_VELOCITY_P_VELOCITY_I,          0x05DC01F4);        // writing value 0x05DC01F4 = 98304500 = 0.0 to address 58 = 0x58(PID_VELOCITY_P_VELOCITY_I)
    tmc4671_writeInt(deb, TMC4671_PID_POSITION_P_POSITION_I,          0x01F40000);        // writing value 0x01F40000 = 32768000 = 0.0 to address 59 = 0x5A(PID_POSITION_P_POSITION_I)

//  tmc4671_writeInt(deb, TMC4671_CONFIG_DATA,                        0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 51 = 0x4D(CONFIG_DATA)
//  tmc4671_writeInt(deb, TMC4671_CONFIG_ADDR,                        0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 52 = 0x4E(CONFIG_ADDR)
//  tmc4671_writeInt(deb, TMC4671_PID_TORQUE_FLUX_TARGET,             0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 68 = 0x64(PID_TORQUE_FLUX_TARGET)
//  tmc4671_writeInt(deb, TMC4671_PID_TORQUE_FLUX_OFFSET,             0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 69 = 0x65(PID_TORQUE_FLUX_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_PID_VELOCITY_TARGET,                0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 70 = 0x66(PID_VELOCITY_TARGET)
//  tmc4671_writeInt(deb, TMC4671_PID_VELOCITY_OFFSET,                0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 71 = 0x67(PID_VELOCITY_OFFSET)
//  tmc4671_writeInt(deb, TMC4671_PID_POSITION_TARGET,                0x00000000);        // writing value 0x0111D7CA = 17946570 = 0.0 to address 72 = 0x68(PID_POSITION_TARGET)
//  tmc4671_writeInt(deb, TMC4671_PID_POSITION_ACTUAL,                0x00000000);        // writing value 0x0111D7D8 = 17946584 = 0.0 to address 73 = 0x6B(PID_POSITION_ACTUAL)
//  tmc4671_writeInt(deb, TMC4671_PID_ERROR_ADDR,                     0x00000000);        // writing value 0x00000000 = 0 = 0.0 to address 74 = 0x6D(PID_ERROR_ADDR)
//  tmc4671_writeInt(deb, TMC4671_INTERIM_DATA,                       0xFF030085);        // writing value 0xFF030085 = 0 = 0.0 to address 75 = 0x6E(INTERIM_DATA)
//  tmc4671_writeInt(deb, TMC4671_INTERIM_ADDR,                       0x00000011);        // writing value 0x00000011 = 17 = 0.0 to address 76 = 0x6F(INTERIM_ADDR)

	encoder_testdrive();

    tmc4671_switchToMotionMode(0, TMC4671_MOTION_MODE_POSITION);
	tmc4671_setActualPosition(0, 0x00000000);
    tmc4671_setAbsolutTargetPosition(deb, 0x00000000);
    tmc4671_setAbsolutTargetPosition(deb, 100000);
}


uint16_t tmc4671_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel)
{
    int32_t registerValue = tmc4671_readInt(motor, address);

    // read one channel
    switch(channel)
    {
    case BIT_0_TO_15:
        return (registerValue & 0xFFFF);
        break;
    case BIT_16_TO_31:
        return ((registerValue >> 16) & 0xFFFF);
        break;
    }
    return 0;
}

void tmc4671_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value)
{
    // read actual register content
    int32_t registerValue = tmc4671_readInt(motor, address);

    // update one channel
    switch(channel)
    {
    case BIT_0_TO_15:
        registerValue &= 0xFFFF0000;
        registerValue |= value;
        break;
    case BIT_16_TO_31:
        registerValue &= 0x0000FFFF;
        registerValue |= (value << 16);
        break;
    }
    // write the register
    tmc4671_writeInt(motor, address, registerValue);
}

void tmc4671_switchToMotionMode(uint8_t motor, uint8_t mode)
{
    // switch motion mode
    uint32_t actualModeRegister = tmc4671_readInt(motor, TMC4671_MODE_RAMP_MODE_MOTION);
    actualModeRegister &= 0xFFFFFF00;
    actualModeRegister |= mode;
    tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, actualModeRegister);
}

void tmc4671_setTargetTorque_raw(uint8_t motor, int32_t targetTorque)
{
    tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_TORQUE);
    tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, targetTorque);
}

int32_t tmc4671_getTargetTorque_raw(uint8_t motor)
{
    // remember last set index
    uint32_t lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

    // get value
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 0);
    int32_t value = (int32_t)tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

    // reset last set index
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);
    return value;
}

int32_t tmc4671_getActualTorque_raw(uint8_t motor)
{
    return (int16_t) tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL, BIT_16_TO_31);
}

int32_t tmc4671_getActualRampTorque_raw(uint8_t motor)
{
    // no ramp implemented
    UNUSED(motor);
    return 0;
}

void tmc4671_setTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetTorque)
{
    tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_TORQUE);
    tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, (targetTorque * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4671_getTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    return (tmc4671_getTargetTorque_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    return (tmc4671_getActualTorque_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getTargetTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    // remember last set index
    uint32_t lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

    // get target torque value
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 0);
    int32_t torque = (int32_t) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

    // get target flux value
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 1);
    int32_t flux = (int32_t) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

    // reset last set index
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);

    return (((int32_t)flux+(int32_t)torque) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    int32_t registerValue = tmc4671_readInt(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL);
    int16_t flux = (registerValue & 0xFFFF);
    int16_t torque = ((registerValue >> 16) & 0xFFFF);
    return (((int32_t)flux+(int32_t)torque) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualRampTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    // no ramp implemented
    UNUSED(motor);
    UNUSED(torqueMeasurementFactor);
    return 0;
}

void tmc4671_setTargetFlux_raw(uint8_t motor, int32_t targetFlux)
{
    // do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
    tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, targetFlux);
}

int32_t tmc4671_getTargetFlux_raw(uint8_t motor)
{
    // remember last set index
    uint32_t lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

    // get value
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 1);
    int32_t value = (int32_t) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

    // reset last set index
    tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);
    return value;
}

int32_t tmc4671_getActualFlux_raw(uint8_t motor)
{
    return (int16_t) tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL, BIT_0_TO_15);
}

void tmc4671_setTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetFlux)
{
    // do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
    tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, (targetFlux * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4671_getTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    return (tmc4671_getTargetFlux_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    return (tmc4671_getActualFlux_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

void tmc4671_setTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t max)
{
    tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15, (max * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4671_getTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
    return ((int32_t) tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15) * (int32_t) torqueMeasurementFactor) / 256;
}

void tmc4671_setTargetVelocity(uint8_t motor, int32_t targetVelocity)
{
    tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_VELOCITY);
    tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_TARGET, targetVelocity);
}

int32_t tmc4671_getTargetVelocity(uint8_t motor)
{
    return (int32_t) tmc4671_readInt(motor, TMC4671_PID_VELOCITY_TARGET);
}

int32_t tmc4671_getActualVelocity(uint8_t motor)
{
    return (int32_t) tmc4671_readInt(motor, TMC4671_PID_VELOCITY_ACTUAL);
}

int32_t tmc4671_getActualRampVelocity(uint8_t motor)
{
    UNUSED(motor);
    // no ramp implemented
    return 0;
}

void tmc4671_setAbsolutTargetPosition(uint8_t motor, int32_t targetPosition)
{
    tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_POSITION);
    tmc4671_writeInt(motor, TMC4671_PID_POSITION_TARGET, targetPosition);
}

void tmc4671_setRelativeTargetPosition(uint8_t motor, int32_t relativePosition)
{
    tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_POSITION);
    // determine actual position and add relative position ticks
    tmc4671_writeInt(motor, TMC4671_PID_POSITION_TARGET, (unsigned long)(tmc4671_getActualPosition(motor) + relativePosition));
}

int32_t tmc4671_getTargetPosition(uint8_t motor)
{
    return (int32_t) tmc4671_readInt(motor, TMC4671_PID_POSITION_TARGET);
}

void tmc4671_setActualPosition(uint8_t motor, int32_t actualPosition)
{
    tmc4671_writeInt(motor, TMC4671_PID_POSITION_ACTUAL, actualPosition);
}

int32_t tmc4671_getActualPosition(uint8_t motor)
{
    return tmc4671_readInt(motor, TMC4671_PID_POSITION_ACTUAL);
}

int32_t tmc4671_getActualRampPosition(uint8_t motor)
{
    UNUSED(motor);
    // no ramp implemented
    return 0;
}


// =====

void tmc4671_disablePWM(uint8_t motor)
{
    tmc4671_writeInt(motor, TMC4671_PWM_SV_CHOP, 0);
}

uint8_t tmc4671_getMotorType(uint8_t motor)
{
    return FIELD_GET(tmc4671_readInt(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS), TMC4671_MOTOR_TYPE_MASK, TMC4671_MOTOR_TYPE_SHIFT);
}

void tmc4671_setMotorType(uint8_t motor, uint8_t motorType)
{
    TMC4671_FIELD_UPDATE(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, TMC4671_MOTOR_TYPE_MASK, TMC4671_MOTOR_TYPE_SHIFT, motorType);
}

uint8_t tmc4671_getPolePairs(uint8_t motor)
{
    return FIELD_GET(tmc4671_readInt(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS), TMC4671_N_POLE_PAIRS_MASK, TMC4671_N_POLE_PAIRS_SHIFT);
}

void tmc4671_setPolePairs(uint8_t motor, uint8_t polePairs)
{
    TMC4671_FIELD_UPDATE(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, TMC4671_N_POLE_PAIRS_MASK, TMC4671_N_POLE_PAIRS_SHIFT, polePairs);
}

uint16_t tmc4671_getAdcI0Offset(uint8_t motor)
{
    return FIELD_GET(tmc4671_readInt(motor, TMC4671_ADC_I0_SCALE_OFFSET), TMC4671_ADC_I0_OFFSET_MASK, TMC4671_ADC_I0_OFFSET_SHIFT);
}

void tmc4671_setAdcI0Offset(uint8_t motor, uint16_t offset)
{
    TMC4671_FIELD_UPDATE(motor, TMC4671_ADC_I0_SCALE_OFFSET, TMC4671_ADC_I0_OFFSET_MASK, TMC4671_ADC_I0_OFFSET_SHIFT, offset);
}

uint16_t tmc4671_getAdcI1Offset(uint8_t motor)
{
    return FIELD_GET(tmc4671_readInt(motor, TMC4671_ADC_I1_SCALE_OFFSET), TMC4671_ADC_I1_OFFSET_MASK, TMC4671_ADC_I1_OFFSET_SHIFT);
}

void tmc4671_setAdcI1Offset(uint8_t motor, uint16_t offset)
{
    TMC4671_FIELD_UPDATE(motor, TMC4671_ADC_I1_SCALE_OFFSET, TMC4671_ADC_I1_OFFSET_MASK, TMC4671_ADC_I1_OFFSET_SHIFT, offset);
}

void tmc4671_setTorqueFluxPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter)
{
    tmc4671_writeInt(motor, TMC4671_PID_FLUX_P_FLUX_I, ((uint32_t)pParameter << 16) | (uint32_t)iParameter);
    tmc4671_writeInt(motor, TMC4671_PID_TORQUE_P_TORQUE_I, ((uint32_t)pParameter << 16) | (uint32_t)iParameter);
}

void tmc4671_setVelocityPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter)
{
    tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_P_VELOCITY_I, ((uint32_t)pParameter << 16) | (uint32_t)iParameter);
}

void tmc4671_setPositionPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter)
{
    tmc4671_writeInt(motor, TMC4671_PID_POSITION_P_POSITION_I, ((uint32_t)pParameter << 16) | (uint32_t)iParameter);
}
