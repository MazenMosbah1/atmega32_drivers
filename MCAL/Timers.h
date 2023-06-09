
#ifndef TIMERS_H_
#define TIMERS_H_

#include "Utils.h"
#include "MemoryMap.h"
#include "StdTypes.h"
#include "EXInterrupt.h"

typedef enum
{
	TIMER0_STOP = 0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
	EXTERNAL1_FALLING,
	EXTERNAL_RISING
	
}Timer0Scaler_type;

typedef enum
{
	TIMER0_NORMAL_MODE = 0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
	
}Timer0Mode_type;

typedef enum
{
	OC0_DISCONNECTED = 0,
	OC0_TOGGLE,
	OC0_NON_INVERTING,
	OC0_INVERTING
	
}OC0Mode_type;

void Timer0_init(Timer0Mode_type mode, Timer0Scaler_type scaler, OC0Mode_type oc_mode);
void Timer0_OV_InterruptEnable(void);
void Timer0_OV_InterruptDisable(void);
void Timer0_OC_InterruptEnable(void);
void Timer0_OC_InterruptDisable(void);
void Timer0_OV_SetCallBack(void(*local_pf)(void));
void Timer0_OC_SetCallBack(void(*local_pf)(void));
/*************************************************************************************/

typedef enum
{
	TIMER1_STOP = 0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
	
}Timer1Scaler_type;


typedef enum
{
	TIMER1_NORMAL_MODE = 0,
	TIMER1_CTC_ICR_TOP_MODE,
	TIMER1_CTC_OCR1A_TOP_MODE,
	TIMER1_FASTPWM_ICR_TOP_MODE,
	TIMER1_FASTPWM_OCR1A_TOP_MODE
	
}Timer1Mode_type;


typedef enum
{
	OCRA_DISCONNECTED = 0,
	OCRA_TOGGLE,
	OCRA_NON_INVERTING,
	OCRA_INVERTING
	
}OC1AMode_type;


typedef enum
{
	OCRB_DISCONNECTED = 0,
	OCRB_TOGGLE,
	OCRB_NON_INVERTING,
	OCRB_INVERTING
	
}OC1BMode_type;

typedef enum
{
	RISING,
	FALLING
	
}ICU_Edge_type;

void Timer1_init(Timer1Mode_type mode, Timer1Scaler_type scaler, OC1AMode_type oc1a_mode, OC1BMode_type oc1b_mode);
void Timer1_ICU_InterruptEnable(void);
void Timer1_ICU_InterruptDisable(void);
void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);
void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);
void Timer1_OCB_InterruptEnable(void);
void Timer1_OCB_InterruptDisable(void);
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void));
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void));
void Timer1_InputCaptureEdge(ICU_Edge_type edge);

#endif /* TIMERS_H_ */