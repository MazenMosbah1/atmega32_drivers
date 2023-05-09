#ifndef TIMERSERVICES_H_
#define TIMERSERVICES_H_

#include "Timers.h"

// 1 : 2000
void Timer0_SetInterrupt_us(u8 time, void(*pf_local)(void));
void Timer1_SetInterrupt_ms(u8 time, void(*pf_local)(void));
void Timer0_SetInterrupt_us_noOverFlow(u16 time, void(*pf_local)(void));
void func_oc(void);
void PWM_Measure(u32 *Pfreq , u8 *Pduty);


#endif /* TIMERSERVICES_H_ */