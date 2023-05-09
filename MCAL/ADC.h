#ifndef ADC_H_
#define ADC_H_

#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"

typedef enum 
{
	/* Voltage Reference */
	VREF_AVCC,
	VREF_AREF,
	VREF_256 /* 2.56V */
	
}ADC_Vref_type; /* Name of enum */

typedef enum
{
	ADC_SCALER_2 = 1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128
	
}ADC_Prescaler_type; /* Name of enum */

typedef enum
{
	/* Channels => Zeros and Ones */
	CH_0 = 0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
	
}ADC_Channel_type;

/* Function to Turn ADC on once */
void ADC_Init(ADC_Vref_type vref, ADC_Prescaler_type scaler);

/* Return volt */ 
u16 ADC_Read(ADC_Channel_type ch);
void ADC_startConversion(ADC_Channel_type ch);
u16 ADC_getRead(void);
u8 ADC_getReadNoBlock(u16 *pdata);

#endif /* ADC_H_ */