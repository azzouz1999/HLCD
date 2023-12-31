/************************************/
/* Author		: Ali Azzouz		*/
/* SWC			: HLCD				*/
/* Layer		: HAL			    */
/* Version		: 1.1				*/
/* Date			: December 15,2023	*/
/* Last Edit	: N/A			 	*/
/************************************/
#define F_CPU 8000000UL
#include<util/delay.h>

#include "LBIT_math.h"
#include "LSTD_types.h"

#include"MDIO_interface.h"

#include "HLCD_interface.h"
#include "HLCD_private.h"
#include "HLCD_config.h"

void HLCD_voidInit(void)
{
	MDIO_voidSetPortDirection(HLCD_Data_Port,0xFF);   /*initialize data port output*/
	MDIO_voidSetPinDirection(HLCD_Ctrl_Port,HLCD_RS_Pin,MDIO_OUTPUT);/*initialize RS pin output*/
	MDIO_voidSetPinDirection(HLCD_Ctrl_Port,HLCD_RW_Pin,MDIO_OUTPUT);/*initialize RW pin output*/
	MDIO_voidSetPinDirection(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_OUTPUT);/*initialize EN pin output*/
	_delay_ms(30);
	HLCD_voidWriteCmd(0x3F);  /*function set */
	_delay_us(40);
	HLCD_voidWriteCmd(0x0F); /*Display command*/
	_delay_us(40);
	HLCD_voidClearScreen();
	HLCD_voidWriteCmd(0x06);/*Entry mode set*/
	_delay_us(40);
}

void HLCD_voidWriteCmd(u8 ARG_u8Cmd)
{
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_RS_Pin,MDIO_LOW); /*command*/
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_RW_Pin,MDIO_LOW); /*write*/
	MDIO_voidSetPortValue(HLCD_Data_Port,ARG_u8Cmd);
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_LOW); /*toggle enable to send*/
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_HIGH);
	_delay_us(1);
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_LOW);
}


void HLCD_voidWriteChar(char ARG_charChar)
{

	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_RS_Pin,MDIO_HIGH);  /*data*/
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_RW_Pin,MDIO_LOW);	 /*write*/
	MDIO_voidSetPortValue(HLCD_Data_Port,ARG_charChar);
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_LOW); /*toggle enable to send*/
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_HIGH);
	_delay_us(1);
	MDIO_voidSetPinValue(HLCD_Ctrl_Port,HLCD_EN_Pin,MDIO_LOW);

}
void HLCD_voidClearScreen(void)
{
	HLCD_voidWriteCmd(0x01);
	_delay_ms(2);
}

void HLCD_voidWriteString(const char* ARG_ccharpString)
{
	u8 L_u8i=0;
	do{
		HLCD_voidWriteChar(ARG_ccharpString[L_u8i]);
		L_u8i++;

	}while(ARG_ccharpString[L_u8i]!='\0');
}

void HLCD_voidSetCursor(u8 ARG_u8Row,u8 ARG_u8Col)
{
	HLCD_voidWriteCmd((128+(ARG_u8Row*64)+ARG_u8Col));
}

u32 HLCD_u32ReverseNum(u32 ARG_u32Num)
{
	u32 reverse=1;
	while(ARG_u32Num!=0)
	{
		reverse=(reverse*10)+(ARG_u32Num%10);
		ARG_u32Num/=10;
	}
	return reverse;
	}
	
void HLCD_voidWriteNum(u32 ARG_u32Num)
{
	if(ARG_u32Num==0)
	{
		HLCD_voidWriteChar((ARG_u32Num%10)+48);
	}
	else
	{
		u32 reverse=1;
		reverse=HLCD_u32ReverseNum(ARG_u32Num);
		while(reverse!=1)
		{
			HLCD_voidWriteChar((reverse%10)+48);
			reverse/=10;
		}
	}
}

void HLCD_voidCreateChar(u8 ARG_u8AddressData,u8 * ARG_CharArr)
{
	HLCD_voidWriteCmd(0x40|(ARG_u8AddressData*8)); //setting the CGRAM
	for(u8 i=0;i<8;i++)
	{
		HLCD_voidWriteChar(ARG_CharArr[i]);
	}
	HLCD_voidWriteCmd(0x80); //return to DDRAM
}
