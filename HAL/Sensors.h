 
#ifndef SENSORS_H_
#define SENSORS_H_

#include "StdTypes.h"
#include "ADC.h"


#define POT_CH		CH_0
#define LM35		CH_1

f32 POT_Read(void);
u16 POT_VoltRead(void);
u16 TEMP_Read(void);



#endif /* SENSORS_H_ */