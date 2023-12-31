/************************************/
/* Author		: Ali Azzouz		*/
/* SWC			: HLCD				*/
/* Layer		: HAL			    */
/* Version		: 1.1				*/
/* Date			: December 15,2023	*/
/* Last Edit	: N/A			 	*/
/************************************/
#ifndef _HLCD_INTERFACE_H_
#define _HLCD_INTERFACE_H_

void HLCD_voidInit(void);
void HLCD_voidWriteCmd(u8 ARG_u8Cmd);
void HLCD_voidWriteChar(char ARG_charChar);
void HLCD_voidClearScreen(void);
void HLCD_voidWriteString(const char* ARG_ccharpString);
void HLCD_voidSetCursor(u8 ARG_u8Row,u8 ARG_u8Col);

u32 HLCD_u32ReverseNum(u32 ARG_u32Num);
void HLCD_voidWriteNum(u32 ARG_u32Num);
void HLCD_voidCreateChar(u8 ARD_u8AddressData,u8 * ARG_CharArr);

#endif /*_HLCD_INTERFACE_H_*/
