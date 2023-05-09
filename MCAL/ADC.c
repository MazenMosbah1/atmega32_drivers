
#include "ADC.h"
#include "LCD.h"

static u8 Read_flag = 0;

/* Function to Turn ADC on once */
void ADC_Init(ADC_Vref_type vref, ADC_Prescaler_type scaler)
{
	/* VREF => Max Volt */
	switch(vref)
	{
		case VREF_AVCC:
			SET_BIT(ADMUX, REFS0);
			CLEAR_BIT(ADMUX, REFS1);
			break;
		case VREF_AREF:
			CLEAR_BIT(ADMUX, REFS0);
			CLEAR_BIT(ADMUX, REFS1);
			break;	
		case VREF_256:
			SET_BIT(ADMUX, REFS0);
			SET_BIT(ADMUX, REFS1);
			break;
	}
	
	/* CLOCK */
	/* Set first 3 bits = 0 before anything to delete any old scalar */ 
	ADCSRA = ADCSRA & 0xF8; /* 1111 1(000) */
	/* To check if other bits(except 3 first bits) = 0 */
	scaler = scaler & 0x07; /* 0000 0(111) */
	ADCSRA = ADCSRA | scaler;
	
	//read adjust right
	CLEAR_BIT(ADMUX, ADLAR);
	
	/* Enable */
	/* Turn on ADC */
	SET_BIT(ADCSRA, ADEN);
}

u16 ADC_Read(ADC_Channel_type ch)
{
	/* Select Channel */
	/* Ensure that first 5 bits == 0 */
	ADMUX = ADMUX & 0XE0; /*111 (00000)*/
	/* Set first 5 MUX in depend of channel read */
	ADMUX = ADMUX | ch;
	
	/* Start Conversion */
	SET_BIT(ADCSRA, ADSC);
	/* POLLING until ADC end conversion */
	while(READ_BIT(ADCSRA, ADSC));
	return ADC;
}

void ADC_startConversion(ADC_Channel_type ch)
{
	if(Read_flag == 0)
	{
		/* Select Channel */
		/* Ensure that first 5 bits == 0 */
		ADMUX = ADMUX & 0XE0; /*111 (00000)*/
		/* Set first 5 MUX in depend of channel read */
		ADMUX = ADMUX | ch;
		
		/* Start Conversion */
		SET_BIT(ADCSRA, ADSC);
		Read_flag = 1;
	}	
	
}

u16 ADC_getRead(void)
{
	/* POLLING (busy wait) until ADC end conversion */
	while(READ_BIT(ADCSRA, ADSC));
	Read_flag = 0;
	return ADC;
}


/* the pointer and allows the value at that memory location to be updated */
u8 ADC_getReadNoBlock(u16 *pdata) /* Define a function 
that takes a pointer to a 16-bit unsigned integer (u16) named
 "pdata" as input and returns an 8-bit unsigned integer (u8).*/
{
	// POLLING (Periodic checking) until ADC end conversion
	if(READ_BIT(ADCSRA, ADSC) == 0) // Check if the ADSC (ADC Start Conversion) bit of the ADCSRA (ADC Control and Status Register A) register is cleared (i.e., it becomes 0).
	{
		*pdata = ADC; // Store the converted ADC value in the memory location pointed to by "pdata".
		Read_flag = 0; // Set a global flag named "Read_flag" to 0 to indicate that the ADC conversion has been completed.
		return 1; // Return 1 to indicate that a value has been read successfully.
	}
	else // If the ADSC bit is not cleared yet, the conversion is not complete.
	{
		return 0; // Return 0 to indicate that no value has been read yet.
	}
}
