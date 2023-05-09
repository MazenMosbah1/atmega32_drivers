#include "Sensors.h"

f32 POT_Read(void)
{
	u16 adc = ADC_Read(POT_CH);
	/* perc => Percentage */
	f32 perc = (adc / 1023.0) * 100;
	return perc;
}

/*u16 POT_VoltRead(void)
{
	u16 adc = ADC_Read(POT_CH);
	u16 volt = ((u32)5000* adc) / 1024;
	return volt;
}*/

u16 TEMP_Read(void)
{
	u16 adc = ADC_Read(LM35);
	u16 volt = ((u32)5000* adc) / 1024;
	u16 temp = volt;
	return temp;
}