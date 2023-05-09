#include "Stepper.h"
#define F_CPU		8000000UL
#include <util/delay.h>
/*
#if(MOTOR_TYPE == BI_POLER) // == 0

void STEPPER_CW(void)
{
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(200);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(200);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(200);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
}
void STEPPER_CCW(void)
{
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(200);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(200);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(200);
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
}

#elif(MOTOR_TYPE == UNI_POLER) // == 1
void STEPPER_CW(void)
{
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(DELAY);
}
void STEPPER_CCW(void)
{
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);	
}
void STEPPER_CW_HalfStep(void)
{
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, HIGH);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, LOW);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, HIGH);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, LOW);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(DELAY);
	DIO_WritePin(COIL1A, HIGH);
	DIO_WritePin(COIL1B, LOW);
	DIO_WritePin(COIL2A, LOW);
	DIO_WritePin(COIL2B, HIGH);
	_delay_ms(DELAY);
}
#endif
*/

/* 
void STEPPER_CW(u8 rev)
{
	u32 i;
	u32 n = NOFSTEPS * rev;
	for(i = 0; i < n; i++)
	{
		STEPPER_CW();
	}
}
 
void STEPPER_CW_ANGLE(u16 angle)
{
	u32 i;
	u32 n = (angle * NOFSTEPS) / 360;
	for (i = 0; i < n; i++)
	{
		STEPPER_CW()
	}
}
*/