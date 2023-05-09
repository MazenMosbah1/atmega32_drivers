

#ifndef UART_H_
#define UART_H_


#include "MemoryMap.h"
#include "Utils.h"
#include "StdTypes.h"


void UART_Init(void);
void UART_Send(u8 data);
u8 UART_Receive(void);
void UART_SendString(u8 *str);



#endif /* UART_H_ */