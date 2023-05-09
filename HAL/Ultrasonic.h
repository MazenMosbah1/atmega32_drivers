
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "MemoryMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Timers.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#define TRIGGER_PIN_1	PINC4
#define TRIGGER_PIN_2	PINC5
#define TRIGGER_PIN_3	PINC6
#define TRIGGER_PIN_4	PINC7


void Ultrasonic_Init(void);
u16 Ultrasonic_Get_Distance(DIO_Pin_type trigger_pin);
void UltraSonic_Start_Measuring_NoBlock(DIO_Pin_type trigger_pin);
u8 UltraSonic_GetDistance_NoBlock(u16 *pDistance);





#endif /* ULTRASONIC_H_ */