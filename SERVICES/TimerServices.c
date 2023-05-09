#include "TimerServices.h"
#include "Timers.h"

static u8 counter_set = 0;
static void(*fp_oc)(void) = NULLPTR;
volatile u16 t1 = 0, t2 = 0, t3 = 0;
volatile u8 flag = 0;
static void Func_ICU(void);


void Timer0_SetInterrupt_us(u8 time, void(*pf_local)(void))
{
	Timer0_init(TIMER0_CTC_MODE, TIMER0_SCALER_8, OC0_TOGGLE);
	OCR0 = time - 1;
	Timer0_OC_SetCallBack(pf_local);
	Timer0_OC_InterruptEnable();
}

void Timer1_SetInterrupt_ms(u8 time, void(*pf_local)(void))
{
	// *1000 => milli to micro
	OCR1A = (time * 1000) - 1;
	
}

void Timer0_SetInterrupt_us_noOverFlow(u16 time, void(*pf_local)(void))
{
	counter_set = time/100;
	fp_oc = pf_local;
	OCR0 = 99;
	Timer0_OC_SetCallBack(func_oc);
	Timer0_OC_InterruptEnable();
}

void func_oc(void)
{
	static u8 c = 0;
	c++;
	if (c == counter_set)
	{
		fp_oc();
	}
}

/* The function bellow  works when :
1 - Timer 1 is in normal mode.
2 - Interrupts are enabled for ICP pin.
3 - Global interrupts are enabled.
4 - when you want to use the Overflow ISR of timer 1 , use it here .. Extremely important
*/
void PWM_Measure(u32 *Pfreq , u8 *Pduty)
{
	u16 time_on = 0 , time_off = 0 , time_total = 0;
	//Timer1_OVF_SetCallBack(ovf_func);
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_ICU_InterruptEnable();
	Timer1_InputCaptureEdge(RISING);
	
	while(flag < 3) ; // the function won't return unless it gets the correct reading
	time_on = t2 - t1;
	time_off = t3 - t2;
	time_total = (u32) time_on + (u32)time_off;
	*Pduty = ((u32)time_on * 100) / time_total;
	*Pfreq = (u32)1000000 / (u32)time_total ;
	//ovf_counter = 0 ;
	Timer1_ICU_InterruptEnable();
	flag = 0;
	
	
}

static void Func_ICU(void)
{
	if(flag == 0) // a rising edge occurred.
	{
		t1 = ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag = 1;
	}
	else if(flag == 1) // a falling edge occurred
	{
		t2 = ICR1;
		Timer1_InputCaptureEdge(RISING);
		flag = 2;
	}
	else if(flag == 2) // a rising edge occurred
	{
		t3 = ICR1;
		// keep the edge as it is
		flag = 3;
		Timer1_ICU_InterruptDisable(); // Disable useless interrupts when flag = 3 and I haven't read t1 , t2 , t3 yet
	}
}
