
#include "UART_Services.h"


void UART_SendInt(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num >> 8));
	UART_Send((u8)(num >> 16));
	UART_Send((u8)(num >> 24));
}

u32 UART_ReceiveInt(void)
{
	u8 Byte_1 = UART_Receive();
	u8 Byte_2 = UART_Receive();
	u8 Byte_3 = UART_Receive();
	u8 Byte_4 = UART_Receive();
	u32 num = Byte_1 | ((u32)Byte_2 << 8) | ((u32)Byte_3 << 16) | ((u32)Byte_4 << 24);
	return num;
} 


void UART_SendString(u8 *str)
{
	for (u8 i = 0; str[i]; i++)
	{
		UART_Send(str[i]);
	}
	UART_Send('#');
}


void UART_ReceiveString(u8 *str)
{
	u8 i = 0;
	str[i] = UART_Receive();
	while (str[i] != '#')
	{
		i++;
		str[i] = UART_Receive();
	}
	str[i] = 0; //To delete #
}



