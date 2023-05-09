
#include "Servo.h"


void SERVO_Init(void)
{
	ICR1 = 19999;
	SERVO_PIN = 999;
}

void SERVO_SetAngle(u8 angle)
{
	SERVO_PIN = ((u32)angle * 1000) / 180 + 999;
}