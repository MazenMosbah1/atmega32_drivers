
#include "LCD.h"

void LCD_Write_Command(u8 command)
{
	DIO_WritePin(RS, LOW);
	DIO_WritePin(RW, LOW);
	DIO_WritePort(LCD_PORT, command);
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
}

void LCD_Write_Command_4Bit(u8 command)
{
	DIO_WritePin(RS, LOW);
	DIO_WritePin(RW, LOW);
	DIO_WritePin(D4, READ_BIT(command, 4));
	DIO_WritePin(D5, READ_BIT(command, 5));
	DIO_WritePin(D6, READ_BIT(command, 6));
	DIO_WritePin(D7, READ_BIT(command, 7));
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
	DIO_WritePin(D4, READ_BIT(command, 0));
	DIO_WritePin(D5, READ_BIT(command, 1));
	DIO_WritePin(D6, READ_BIT(command, 2));
	DIO_WritePin(D7, READ_BIT(command, 3));
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
}

void LCD_Write_Data(u8 data)
{
	DIO_WritePin(RS, HIGH);
	DIO_WritePin(RW, LOW);
	DIO_WritePort(LCD_PORT, data); 
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
}

void LCD_Write_Data_4Bit(u8 data)
{
	DIO_WritePin(RS, HIGH);
	DIO_WritePin(RW, LOW);
	DIO_WritePin(D4, READ_BIT(data, 4));
	DIO_WritePin(D5, READ_BIT(data, 5));
	DIO_WritePin(D6, READ_BIT(data, 6));
	DIO_WritePin(D7, READ_BIT(data, 7));
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
	DIO_WritePin(D4, READ_BIT(data, 0));
	DIO_WritePin(D5, READ_BIT(data, 1));
	DIO_WritePin(D6, READ_BIT(data, 2));
	DIO_WritePin(D7, READ_BIT(data, 3));
	DIO_WritePin(EN, HIGH);
	_delay_ms(1);
	DIO_WritePin(EN, LOW);
	_delay_ms(1);
}


void LCD_Write_String(char* str)
{
	u8 i;
	for (i = 0;str[i] != 0; i++)
	{
		LCD_Write_Data(str[i]);
	}
}

void LCD_Write_Number(s64 num) 
{
	u8 i = 0, j, rem, arr[16]= {0};
		if (num == 0)
		{
			LCD_Write_Data('0');
		}
		else
		{
			if (num < 0)
			{
				num = num * (-1);
				LCD_Write_Data('-');
			}
			
			while(num > 0)
			{
				rem = num % 10;
				arr[i] = rem + '0';
				i++;
				num = num / 10;
			}
			for (j = i; j > 0; j--)
			{
				LCD_Write_Data(arr[j-1]);
			}
		}
}

void LCD_Write_Number_4D(s64 num)
{
	LCD_Write_Data(((num % 10000) / 1000) + '0');
	LCD_Write_Data(((num % 1000) / 100) + '0');
	LCD_Write_Data(((num % 100) / 10) + '0');
	LCD_Write_Data(((num % 10) / 1) + '0');
}

void LCD_Init()
{
	_delay_ms(50);
	LCD_Write_Command(0x38); //8 bitmode, 2 line, 5*7
	_delay_ms(1);
	LCD_Write_Command(0x0C); // cursor, screen(on, off), ox0E, 0x0F
	_delay_ms(1);
	LCD_Write_Command(0x01); //clear screen
	_delay_ms(2);
	LCD_Write_Command(0x06); //increase DDRAM address
	_delay_ms(1);
}

void LCD_Init_4Bit()
{
	_delay_ms(50);
	LCD_Write_Command_4Bit(0x02);
	_delay_ms(1);
	LCD_Write_Command(0x28); //4 bitmode, 2 line, 5*7
	_delay_ms(1);
	LCD_Write_Command(0x0C); // cursor, screen(on, off), ox0E, 0x0F
	_delay_ms(1);
	LCD_Write_Command(0x01); //clear screen
	_delay_ms(2);
	LCD_Write_Command(0x06); //increase DDRAM address
	_delay_ms(1);
}

void LCD_Clear(void)
{
	LCD_Write_Command(0x01); // Deleting the display.
}

void LCD_GoTo(u8 line , u8 x)
{
	if(line == 0)
	{
		LCD_Write_Command(0x80 + x);
	}
	else if(line == 1)
	{
		LCD_Write_Command(0xC80 + 0x40 + x);
	}
}

void LCD_WriteChar(u8 ch)
{
	LCD_Write_Data(ch);
}

void LCD_Create_Character(u8* Pattern, u8 address)
{
	u8 i;
	LCD_Write_Command(0x40 + (address*8));
	for (i = 0; i < 8; i++)
	{
		LCD_Write_Data(Pattern[i]);
	}
}

void LCD_Write_Number_InBinary(u8 num)
{
	s8 i;
	for (i = 7; i >= 0; i--)
	{
		LCD_Write_Data(((num >> i) & 1) + '0');
	}
}

void LCD_Write_Number_InBinary2(u8 num)
{
	s8 i, flag = 0;
	for (i = 7; i >= 0; i--)
	{
		if ((num >> i) & 1)
		{
			flag = 1;
		}
		if(flag == 1)
		{
			LCD_Write_Data(((num >> i) & 1) + '0');
		}
		
	}
}

void LCD_Write_Number_GoTo(u8 line, u8 x, s64 num)
{
	LCD_GoTo(line, x);
	LCD_Write_Number(num);
}