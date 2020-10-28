/*
 * TMC4671.h
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMC4671_H_
#define TMC_IC_TMC4671_H_

#define STATE_NOTHING_TO_DO    0
#define STATE_START_INIT       1
#define STATE_WAIT_INIT_TIME   2
#define STATE_ESTIMATE_OFFSET  3

#define DEFAULT_MOTOR  0
#define TMC4671_MOTORS 1
#define USE_LINEAR_RAMP
#define POSITION_SCALE_MAX  (int32_t)65536



#include "../TMC-API/tmc/helpers/API_Header.h"
#include "TMC4671_Register.h"
#include "TMC4671_Constants.h"
#include "TMC4671_Fields.h"
#include "../SPI/SPI.h"
#include "../Software_SPI/Software_SPI.h"
#include "../UART/UART.h"

typedef struct
{
	uint16_t  startVoltage;
	uint16_t  initWaitTime;
	uint16_t  actualInitWaitTime;
	uint8_t   initState;
	uint8_t   initMode;
	uint16_t  torqueMeasurementFactor;  // uint8_t.uint8_t
	uint8_t	  motionMode;
	int32_t   actualVelocityPT1;
	int64_t	  akkuActualVelocity;
	int16_t   actualTorquePT1;
	int64_t   akkuActualTorque;
	int32_t   positionScaler;
} TMinimalMotorConfig;

TMinimalMotorConfig motorConfig[TMC4671_MOTORS];


void encoder_testdrive(void);

// SPI-Wrapper
void tmc4671_writeDatagram(unsigned int motor, unsigned char address, unsigned int x1, unsigned int x2, unsigned int x3, unsigned int x4);
void tmc4671_writeInt(unsigned int motor, unsigned char address, unsigned long value);
int32_t tmc4671_readInt(unsigned int motor, unsigned char address);
void tmc40bit_writeInt(unsigned int motor, unsigned char address, unsigned long value);
int32_t tmc40bit_readInt(unsigned int motor, unsigned char address);
void TMC4671_init(void);
void resetTMC4671_Encoder(void);
void initTMC4671_Encoder(void);
void initTMC4671_Openloop(void);
// SPI

void read_registers_TMC4671(void);



// TMC4671 Direktbefehle

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1

// Helper macros
#define TMC4671_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc4671_readInt(tdef, address), mask, shift)
#define TMC4671_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc4671_writeInt(tdef, address, FIELD_SET(tmc4671_readInt(tdef, address), mask, shift, value)))

// int32_t tmc4671_readInt(uint8_t motor, uint8_t address);
// void tmc4671_writeInt(uint8_t motor, uint8_t address, int32_t value);
uint16_t tmc4671_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel);
void tmc4671_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value);

// do cyclic tasks
void tmc4671_periodicJob(uint8_t motor, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage);

// initialization functions
void tmc4671_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState);
void tmc4671_updatePhiSelectionAndInitialize(uint8_t motor, uint8_t actualPhiESelection, uint8_t desiredPhiESelection, uint8_t initMode, uint8_t *initState);

// === modes of operation ===
void tmc4671_switchToMotionMode(uint8_t motor, uint8_t mode);

// torque mode
void tmc4671_setTargetTorque_raw(uint8_t motor, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_raw(uint8_t motor);
int32_t tmc4671_getActualTorque_raw(uint8_t motor);
int32_t tmc4671_getActualRampTorque_raw(uint8_t motor);

void tmc4671_setTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getTargetTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualRampTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// flux
void tmc4671_setTargetFlux_raw(uint8_t motor, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_raw(uint8_t motor);
int32_t tmc4671_getActualFlux_raw(uint8_t motor);

void tmc4671_setTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// torque/flux limit
void tmc4671_setTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t max);
int32_t tmc4671_getTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// velocity mode
void tmc4671_setTargetVelocity(uint8_t motor, int32_t targetVelocity);
int32_t tmc4671_getTargetVelocity(uint8_t motor);
int32_t tmc4671_getActualVelocity(uint8_t motor);
int32_t tmc4671_getActualRampVelocity(uint8_t motor);

// position mode
void tmc4671_setAbsolutTargetPosition(uint8_t motor, int32_t targetPosition);
void tmc4671_setRelativeTargetPosition(uint8_t motor, int32_t relativePosition);
int32_t tmc4671_getTargetPosition(uint8_t motor);
void tmc4671_setActualPosition(uint8_t motor, int32_t actualPosition);
int32_t tmc4671_getActualPosition(uint8_t motor);
int32_t tmc4671_getActualRampPosition(uint8_t motor);

// pwm control
void tmc4671_disablePWM(uint8_t motor);

// motor settings
uint8_t tmc4671_getMotorType(uint8_t motor);
void tmc4671_setMotorType(uint8_t motor, uint8_t motorType);

uint8_t tmc4671_getPolePairs(uint8_t motor);
void tmc4671_setPolePairs(uint8_t motor, uint8_t polePairs);

uint16_t tmc4671_getAdcI0Offset(uint8_t motor);
void tmc4671_setAdcI0Offset(uint8_t motor, uint16_t offset);

uint16_t tmc4671_getAdcI1Offset(uint8_t motor);
void tmc4671_setAdcI1Offset(uint8_t motor, uint16_t offset);

void tmc4671_setTorqueFluxPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);
void tmc4671_setVelocityPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);
void tmc4671_setPositionPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);

#endif /* TMC_IC_TMC4671_H_ */
