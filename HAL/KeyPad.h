

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "StdTypes.h"
#include "DIO_Interface.h"

#define FIRST_OUT	PINC3
#define FIRST_IN	PINB0
#define DEFAULT_KEY		'.'
#define ROWS	4
#define COL		4

u8 KEYPAD_GetEntry(void);



#endif /* KEYPAD_H_ */