
#ifndef LCD_H_
#define LCD_H_

#define  F_CPU		8000000UL
#include "StdTypes.h"
#include "DIO_Interface.h"
#include <util/delay.h>

#define		_4_BIT		0
#define		_8_BIT		1

/**************************************config*******************************/
/************************************Controlling****************************/
#define LCD_MODE		_4_BIT

#define		LCD_PORT		PA

#define		D4		PINC4
#define		D5		PINB5
#define		D6		PIND6
#define		D7		PIND7

#define		RS				PINC0
#define		RW				PINC1
#define		EN				PINC2

void LCD_Init(void);
void LCD_Init_4Bit();
void LCD_Write_Data(u8 data);
void LCD_Write_String(char* str);
void LCD_Write_Number(s64 num);
void LCD_Write_Number_InBinary(u8 num);
void LCD_Write_Number_InBinary2(u8 num);
void LCD_Write_Number_4D(s64 num);
void LCD_Clear(void);
void LCD_GoTo(u8 line , u8 x);
void LCD_Write_Number_GoTo(u8 line, u8 x, s64 num);
void LCD_WriteChar(u8 ch);
void LCD_Create_Character(u8* Pattern, u8 address);
void LCD_Write_Command_4Bit(u8 command);
void LCD_Write_Data_4Bit(u8 data);


#endif /* LCD_H_ */