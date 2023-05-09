#ifndef STEPPER_H_
#define STEPPER_H_

#include "StdTypes.h"
#include "DIO_Interface.h"

#define		BI_POLER		0
#define		UNI_POLER		1


/*****************************STEPPER PIN CONFIG********************************/

#define MOTOR_TYPE		BI_POLER

#define		COIL1A		PINA0
#define		COIL1B		PINA1
#define		COIL2A		PINA2
#define		COIL2B		PINA3

#define		NOFSTEPS	512

#define		DELAY		5
/*******************************************************************************/

void STEPPER_CW(void);
void STEPPER_CCW(void);
void STEPPER_CW(void);
void STEPPER_CCW(void);
void STEPPER_CW_HalfStep(void);


#endif /* STEPPER_H_ */