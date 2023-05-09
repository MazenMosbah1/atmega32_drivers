#include "Ultrasonic.h"

static volatile u16 t1, t2, flag = 0, ovf_counter = 0;
static void Func_ICU(void);
static void Func_OVF(void);

void Ultrasonic_Init(void)
{
	Timer1_init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8, OCRA_DISCONNECTED, OCRB_DISCONNECTED);
	Timer1_ICU_InterruptEnable();
	Timer1_OVF_InterruptEnable();
	Timer1_ICU_SetCallBack(Func_ICU);
	Timer1_OVF_SetCallBack(Func_OVF);
}

u16 Ultrasonic_Get_Distance(DIO_Pin_type trigger_pin)
{
	u8 distance;
	u16 time;
	//TCNT1 = 0;
	ovf_counter = 0;
	flag = 0;
	Timer1_InputCaptureEdge(RISING);
	Timer1_ICU_InterruptEnable();
	DIO_WritePin(trigger_pin, HIGH);
	_delay_us(10);
	DIO_WritePin(trigger_pin, LOW);
	while (flag < 2);
	time = t2  + (u32)ovf_counter * 65535 - t1 ;
	distance = time / 58; // in cm
	ovf_counter = 0;
	Timer1_ICU_InterruptDisable();
	flag = 0;
	return distance;
}

void UltraSonic_Start_Measuring_NoBlock(DIO_Pin_type trigger_pin)
{
	if(flag == 0) // It finished the previous reading
	{
		// Triggering :
		DIO_WritePin(trigger_pin,HIGH);
		_delay_us(10);
		DIO_WritePin(trigger_pin,LOW);
		
		//Ready for Echoing :
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptEnable();
		Timer1_OVF_InterruptEnable();
	}
}

u8 Ultrasonic_GetDistanceNoBlock(u8 *Pdistance)
{
	u8 distance;
	u16 time;
	if (flag == 2)
	{
		time = t2  + (u32)ovf_counter * 65535 - t1;
		distance = time / 58;
		*Pdistance = distance;
		Timer1_OVF_InterruptEnable();
		flag = 0;
		return 1;
	}
	return 0;
}

static void Func_ICU(void)
{
	if (flag == 0)
	{
		ovf_counter = 0;
		t1 = ICR1;
		flag = 1;
		Timer1_InputCaptureEdge(FALLING);
	}
	else if (flag == 1)
	{
		t2 = ICR1;
		flag = 2;
		Timer1_InputCaptureEdge(RISING);
		Timer1_ICU_InterruptDisable();
		Timer1_OVF_InterruptDisable();
	}
}

static void Func_OVF(void)
{
	ovf_counter++;
}