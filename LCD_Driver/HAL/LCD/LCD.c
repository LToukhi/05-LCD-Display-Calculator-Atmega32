/*
 * LCD.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Al-toukhi
 */
#include"../../MCAL/DIO/DIO.h"
#include<util/delay.h>
#include"LCD.h"

void HLCD_voidSendCommand(u8 A_u8Cmd)
{
	MDIO_voidPinValue(LCD_ControlPort , PIN0 , LOW) ;
	MDIO_voidPinValue(LCD_ControlPort , PIN1 , LOW) ;
	MDIO_voidPortValue(LCD_DataPort , A_u8Cmd) ;
	MDIO_voidPinValue(LCD_ControlPort , PIN2 , HIGH) ;
	_delay_ms(1);
	MDIO_voidPinValue(LCD_ControlPort , PIN2 , LOW) ;
}

void HLCD_voidSendData(u8 A_u8Data)
{
	MDIO_voidPinValue(LCD_ControlPort , PIN0 , HIGH) ;
	MDIO_voidPinValue(LCD_ControlPort , PIN1 , LOW) ;
	MDIO_voidPortValue(LCD_DataPort , A_u8Data) ;
	MDIO_voidPinValue(LCD_ControlPort , PIN2 , HIGH) ;
	_delay_ms(1);
	MDIO_voidPinValue(LCD_ControlPort , PIN2 , LOW) ;
}


void HLCD_voidLcdInit()
{
	MDIO_voidPortMode(PORTA , OUTPUT) ;
	MDIO_voidPortMode(PORTB , OUTPUT) ;
	_delay_ms(30) ;
	HLCD_voidSendCommand(LCD_FuncSet)  ;
	_delay_ms(1) ;
	HLCD_voidSendCommand(LCD_DisplayControl) ;
	_delay_ms(1) ;
	HLCD_voidSendCommand(LCD_DisplayClear) ;
	_delay_ms(2) ;
	HLCD_voidSendCommand(LCD_EntryMode) ;
}

void HLCD_voidLCDClr()
{
	HLCD_voidSendCommand(LCD_DisplayClear) ;
	_delay_ms(2) ;
}

void HLCD_voidSetCursor(u8 A_u8RowID , u8 A_u8ColIndex)
{
	switch(A_u8RowID)
	{
		case LCD_Line1 : HLCD_voidSendCommand(LCD_Row1_ID + A_u8ColIndex) ; break ;
		case LCD_Line2 : HLCD_voidSendCommand(LCD_Row2_ID + A_u8ColIndex) ; break ;
	}

}

void HLCD_voidSendStr(u8 *PtrStr)
{
	u8 L_u8Counter=0 ;
	while(*PtrStr >0)
		{
			L_u8Counter++ ;
			HLCD_voidSendData(*PtrStr ++) ;
			_delay_ms(50) ;
			if(L_u8Counter == 16)
			{
				HLCD_voidSendCommand(LCD_EntryModeShift)  ;
			}
		}
	HLCD_voidSendCommand(LCD_EntryMode)  ;
}

void HLCD_voidDisplayNum(s32 A_s32Num)
{
	s32 L_u32Store = 1 ;
	if(A_s32Num == 0)
	{
		HLCD_voidSendData('0') ;
	}
	if(A_s32Num < 0)
	{

		HLCD_voidSendData('-') ;
		A_s32Num = A_s32Num * -1 ;
	}
	while(A_s32Num != 0)
	{
		L_u32Store = (L_u32Store*10) + (A_s32Num%10) ;
		A_s32Num = A_s32Num/10 ;
	}
	while(L_u32Store != 1)
	{
		HLCD_voidSendData((L_u32Store%10) + 48) ;
		L_u32Store = L_u32Store/10 ;
	}
}

void HLCD_voidSaveCustomChar(u8 A_u8CGRAMIndex , u8 *A_u8Char)
{
	HLCD_voidSendCommand(0x40+(A_u8CGRAMIndex*8)) ;
	for(u8 L_u8Location = 0 ; L_u8Location < 8 ; L_u8Location++)
	{
	HLCD_voidSendData(A_u8Char[L_u8Location]) ;
	}
	HLCD_voidSendCommand(0x80) ;
}

void HLCD_voidDisplayCustomChar(u8 A_u8CGRAMIndex)
{
	if(A_u8CGRAMIndex <8)
	{
	HLCD_voidSendData(A_u8CGRAMIndex) ;
	}
}

void HLCD_voidRtrnHome()
{
	HLCD_voidSendCommand(LCD_RtrnHome) ;
	_delay_ms(2) ;
}
