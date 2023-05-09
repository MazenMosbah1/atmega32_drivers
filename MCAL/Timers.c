
#include "Timers.h"

static void(*Fptr_OV)(void) = NULLPTR;
static void(*Fptr_OC)(void) = NULLPTR;

/*******************Pointer to functions to be assigned to ISR**************************/
static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
static void (*Timer1_OCB_Fptr) (void)=NULLPTR;
static void (*Timer1_ICU_Fptr) (void)=NULLPTR;

void Timer0_init(Timer0Mode_type mode, Timer0Scaler_type scaler, OC0Mode_type oc_mode)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE:
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			break;
		case TIMER0_PHASECORRECT_MODE:
			SET_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);
			break;
		case TIMER0_CTC_MODE:
			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
		case TIMER0_FASTPWM_MODE:
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
		default:
			// Invalid mode
			break;
	}
	
	/*
	TCCR0 &= 0XF8; //0b11111000
	TCCR0 |= scaler 
	*/
	
	switch(scaler)
	{
		case TIMER0_STOP:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case TIMER0_SCALER_1:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case TIMER0_SCALER_8:
			CLEAR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case TIMER0_SCALER_64:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			CLEAR_BIT(TCCR0, CS02);
			break;
		case TIMER0_SCALER_256:
			CLEAR_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		case TIMER0_SCALER_1024:
			SET_BIT(TCCR0, CS00);
			CLEAR_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		case EXTERNAL1_FALLING:
			CLEAR_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
		case EXTERNAL_RISING:
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
		default:
			// Invalid mode
			break;
	}
	
	switch(oc_mode)
	{
		case OC0_DISCONNECTED:
			CLEAR_BIT(TCCR0, COM00);
			CLEAR_BIT(TCCR0, COM01);
			break;
		case OC0_TOGGLE:
			SET_BIT(TCCR0, COM00);
			CLEAR_BIT(TCCR0, COM01);
			break;
		case OC0_NON_INVERTING:
			CLEAR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;
		case OC0_INVERTING:
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;
		default:
			// Invalid mode
			break;
	}
}

void Timer0_OV_InterruptEnable(void)
{
	SET_BIT(TIMSK, TOIE0);
}

void Timer0_OV_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, TOIE0);
}

// Compare match
void Timer0_OC_InterruptEnable(void)
{
	SET_BIT(TIMSK, OCIE0);
}

void Timer0_OC_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK, OCIE0);
}

void Timer0_OV_SetCallBack(void(*local_pf)(void))
{
	Fptr_OV = local_pf;
}

void Timer0_OC_SetCallBack(void(*local_pf)(void))
{
	Fptr_OC = local_pf;
}


ISR(TIMER0_OVF_vect)
{
	Fptr_OV();
}

ISR(TIMER0_OC_vect)
{
	Fptr_OC();
}


/****************************************Timer 1 **********************************************/
void Timer1_init(Timer1Mode_type mode, Timer1Scaler_type scaler, OC1AMode_type oc1a_mode, OC1BMode_type oc1b_mode)
{
	switch(mode)
	{
		case TIMER1_NORMAL_MODE:
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			CLEAR_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);
			break;
		case TIMER1_CTC_ICR_TOP_MODE:
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case TIMER1_CTC_OCR1A_TOP_MODE:
			CLEAR_BIT(TCCR1A, WGM10);
			CLEAR_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);
			break;
		case TIMER1_FASTPWM_ICR_TOP_MODE:
			CLEAR_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		case TIMER1_FASTPWM_OCR1A_TOP_MODE:
			SET_BIT(TCCR1A, WGM10);
			SET_BIT(TCCR1A, WGM11);
			SET_BIT(TCCR1B, WGM12);
			SET_BIT(TCCR1B, WGM13);
			break;
		default:
			//invalid code
			break;		
	}
	
	/*
	TCCR1B &= 0XF8; //0b11111000
	TCCR1B |= scaler*/
	
	switch(scaler)
	{
		case TIMER1_STOP:
			CLEAR_BIT(TCCR1B, CS10);
			CLEAR_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS12);
			break;
		case TIMER1_SCALER_1:
			SET_BIT(TCCR1B, CS10);
			CLEAR_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS12);
			break;
		case TIMER1_SCALER_8:
			CLEAR_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS12);
			break;
		case TIMER1_SCALER_64:
			SET_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			CLEAR_BIT(TCCR1B, CS12);
			break;
		case TIMER1_SCALER_256:
			CLEAR_BIT(TCCR1B, CS10);
			CLEAR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
			break;
		case TIMER1_SCALER_1024:
			SET_BIT(TCCR1B, CS10);
			CLEAR_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
			break;
		case EXTERNAL0_FALLING:
			CLEAR_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
			break;
		case EXTERNAL0_RISING:
			SET_BIT(TCCR1B, CS10);
			SET_BIT(TCCR1B, CS11);
			SET_BIT(TCCR1B, CS12);
			break;
		default:
			//Invalid Code
			break;
	}
	
	switch(oc1a_mode)
	{
		case OCRA_DISCONNECTED:
			CLEAR_BIT(TCCR1A, COM1A0);
			CLEAR_BIT(TCCR1A, COM1A1);
			break;
		case OCRA_TOGGLE:
			SET_BIT(TCCR1A, COM1A0);
			CLEAR_BIT(TCCR1A, COM1A1);
			break;
		case OCRA_NON_INVERTING:
			CLEAR_BIT(TCCR1A, COM1A0);
			SET_BIT(TCCR1A, COM1A1);
			break;
		case OCRA_INVERTING:
			SET_BIT(TCCR1A, COM1A0);
			SET_BIT(TCCR1A, COM1A1);
			break;
		default:
			//Invalid code
			break;
	}
	
	switch(oc1b_mode)
	{
		case OCRB_DISCONNECTED:
			CLEAR_BIT(TCCR1A, COM1B0);
			CLEAR_BIT(TCCR1A, COM1B1);
			break;
		case OCRB_TOGGLE:
			SET_BIT(TCCR1A, COM1B0);
			CLEAR_BIT(TCCR1A, COM1B1);
			break;
		case OCRB_NON_INVERTING:
			CLEAR_BIT(TCCR1A, COM1B0);
			SET_BIT(TCCR1A, COM1B1);
			break;
		case OCRB_INVERTING:
			SET_BIT(TCCR1A, COM1B0);
			SET_BIT(TCCR1A, COM1B1);
			break;
		default:
			//Invalid code
			break;
	}
}

void Timer1_InputCaptureEdge(ICU_Edge_type edge)
{
	if (edge == RISING)
	{
		SET_BIT(TCCR1B, ICES1);
	}
	else if (edge == FALLING)
	{
		CLEAR_BIT(TCCR1B, ICES1);
	}
}

/****************************Timer 1 Interrupt functions**************************************/

void Timer1_ICU_InterruptEnable(void)
{
	SET_BIT(TIMSK,TICIE1);
}
void Timer1_ICU_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TICIE1);
}
void Timer1_OVF_InterruptEnable(void)
{
	SET_BIT(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,TOIE1);
}
void Timer1_OCA_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1A);
}
void Timer1_OCA_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1A);
}
void Timer1_OCB_InterruptEnable(void)
{
	SET_BIT(TIMSK,OCIE1B);
}
void Timer1_OCB_InterruptDisable(void)
{
	CLEAR_BIT(TIMSK,OCIE1B);
}

/*********************************Timer 1 Call Back functions*****************************************/

void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr = LocalFptr;
}
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCA_Fptr = LocalFptr;
}
void Timer1_OCB_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OCB_Fptr = LocalFptr;
}
void Timer1_ICU_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_ICU_Fptr = LocalFptr;
}

/*********************************Timer 1 ISR functions*********************************************/
ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}
ISR(TIMER1_OCA_vect)
{
	if(Timer1_OCA_Fptr!=NULLPTR)
	{
		Timer1_OCA_Fptr();
	}
}
ISR(TIMER1_OCB_vect)
{
	if(Timer1_OCB_Fptr!=NULLPTR)
	{
		Timer1_OCB_Fptr();
	}
}
ISR(TIMER1_ICU_vect)
{
	if(Timer1_ICU_Fptr!=NULLPTR)
	{
		Timer1_ICU_Fptr();
	}
}