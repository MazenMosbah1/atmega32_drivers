
#define F_CPU		8000000UL
#include <util/delay.h>

#include "MemoryMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "Stepper.h"
#include "LCD.h"
#include "KeyPad.h"
#include "ADC.h"
#include "Sensors.h"
#include "EXInterrupt.h" 
#include "Timers.h"
#include "TimerServices.h"
#include "Servo.h"
#include "Ultrasonic.h"
#include "UART.h"
#include "UART_Services.h"

#define SEGMENT_PORT	PORTB
#define EN1		0
#define EN2		1
#define ENABLE_PORT		PORTA



u8 segNumbers[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	
#define		UP		PINA0
#define		DOWN	PINA1
#define		Right	PINA2
#define		LEFT	PINA3

/* shared variable between code and interrupt should be volatile */


static volatile u8 flag = 0;
static volatile u16 t1 = 0, t2 = 0;
static volatile u16 x  = 0;

void func1(void)
{
	OCR0 += 10;
}

void func2(void)
{
	OCR0 -= 10;
}

void updateOCR0(u16 potValue)
{
	// Map the potentiometer value to a range of OCR0 values
	u16 ocrValue = ((u32)potValue) / 4;  /* divided by 4 to match the mapping between 1024(ADC) and 256 (Timer0) */
	OCR0 = ocrValue;
}

//static void icu_func(void);

int main(void)
{
	
	sei(); 
	//u32 x, y = 0;
	DIO_Init();
	LCD_Init();
	UART_Init();
	//u8 str[100] = {0};
	
	while(1)
	{
		
	}
}

