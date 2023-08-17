/*
 * main.c
 *
 *  Created on: Aug 13, 2023
 *      Author: Al-toukhi
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KeyPad/KPD.h"
#include <util/delay.h>

void main()
{
	HLCD_voidLcdInit() ;
	HKPD_voidKeyPadInit() ;
	u8  G_PrssdKy = 0 ;
	u8  G_Sign = '+' ;
	u8  G_Oprtion ;
	s32 G_Operand1 = 0 ;
	s32 G_Operand2 = 0 ;
	s32 G_Result = 0 ;
	//welcome statement
	HLCD_voidSendStr("Welcome to my calculator ^_^");
	_delay_ms(500) ;
	HLCD_voidLCDClr() ;
while(1)
{
	if((G_PrssdKy != '*') && (G_PrssdKy != '+') && (G_PrssdKy != '-') && (G_PrssdKy != '/'))
	{
		while(1)
		{
		G_Sign = '+'   ;
		G_Operand1 = 0 ;
		G_Operand2 = 0 ;


		//enter operand1
		G_Sign = HKPD_u8GetPressedKey() ;
		if(G_Sign == '-')
		{
			HLCD_voidSendData(G_Sign) ;
			G_PrssdKy = HKPD_u8GetPressedKey() ;
		}
		else
		{
			G_PrssdKy = G_Sign ;
		}
		while((G_PrssdKy != '*') && (G_PrssdKy != '+') && (G_PrssdKy != '-') && (G_PrssdKy != '/') && (G_PrssdKy != '='))
		{
			if((G_PrssdKy >= 0) && (G_PrssdKy <= 9))
			{
				HLCD_voidDisplayNum(G_PrssdKy) ;
				G_Operand1 = G_Operand1*10 + G_PrssdKy ;
			}
			if(G_PrssdKy == 'C')
			{
				HLCD_voidLCDClr() ; break ;
			}
			G_PrssdKy = HKPD_u8GetPressedKey() ;
		}

		if(G_PrssdKy == 'C')
		{
			HLCD_voidLCDClr() ; break ;
		}

		//change the sign in case of  -ve number
		if(G_Sign == '-')
		{
			G_Operand1*=-1 ;
			G_Sign = '+';
		}

		//select operation
		if((G_PrssdKy == '*') || (G_PrssdKy == '+') || (G_PrssdKy == '-') || (G_PrssdKy == '/') || (G_PrssdKy == '='))
		{
			HLCD_voidSendData(' ') ;
			if(G_PrssdKy != '=')
			{
			HLCD_voidSendData(G_PrssdKy) ;
			}
			G_Oprtion = G_PrssdKy ;
			HLCD_voidSendData(' ') ;
		}

		//operand2
		if(G_PrssdKy != '=')
		{
			G_Sign = HKPD_u8GetPressedKey() ;
			if(G_Sign == '-')
			{
				HLCD_voidSendData(G_Sign) ;
				G_PrssdKy = HKPD_u8GetPressedKey() ;
			}
			else
			{
				G_PrssdKy = G_Sign ;
			}
			while(G_PrssdKy != '=')
			{
				if((G_PrssdKy >= 0) && (G_PrssdKy <= 9))
				{
					HLCD_voidDisplayNum(G_PrssdKy) ;
					G_Operand2 = G_Operand2*10 + G_PrssdKy ;
				}
				if(G_PrssdKy == 'C')
				{
					HLCD_voidLCDClr() ; break ;
				}
				G_PrssdKy = HKPD_u8GetPressedKey() ;
			}
			if(G_PrssdKy == 'C')
			{
				HLCD_voidLCDClr() ; break ;
			}

			//change the sign in case of  -ve number
			if(G_Sign == '-')
			{
				G_Operand2*=-1 ;
			}
		}

		HLCD_voidSetCursor(2,1) ;
		HLCD_voidSendData('=') ;
		HLCD_voidSendData(' ') ;
		//operation
		if(G_Oprtion == '+')
		{
			G_Result = G_Operand1 + G_Operand2 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '-')
		{
			G_Result = G_Operand1 - G_Operand2 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '*')
		{
			G_Result = G_Operand1 * G_Operand2 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '=')
		{
			G_Result = G_Operand1 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '/')
		{
			if(G_Operand2 != 0)
			{
				G_Result = G_Operand1 / G_Operand2 ;
				HLCD_voidDisplayNum(G_Result) ;
			}
			else
			{
				HLCD_voidSendStr("Math Error") ;
				_delay_ms(1000) ;
				HLCD_voidLCDClr() ;
				break ;
			}
		}
		G_PrssdKy = HKPD_u8GetPressedKey() ;
		HLCD_voidLCDClr() ;
	    break ;
	}
	}
	else
	{
		G_Operand1 = 0 ;
		HLCD_voidDisplayNum(G_Result) ;
		HLCD_voidSendData(' ') ;
		G_Oprtion = G_PrssdKy ;
		if(G_Oprtion != '=')
		{
		HLCD_voidSendData(G_Oprtion) ;
		}
		HLCD_voidSendData(' ') ;
		G_Sign = HKPD_u8GetPressedKey() ;
		if(G_Sign == '-')
		{
			HLCD_voidSendData(G_Sign) ;
			G_PrssdKy = HKPD_u8GetPressedKey() ;
		}
		else
		{
			G_PrssdKy = G_Sign ;
		}
		while((G_PrssdKy != '=') && (G_PrssdKy != '/') && (G_PrssdKy != '*') && (G_PrssdKy != '+') && (G_PrssdKy != '-'))
		{
			if((G_PrssdKy >= 0) && (G_PrssdKy <= 9))
			{
				HLCD_voidDisplayNum(G_PrssdKy) ;
				G_Operand1 = G_Operand1*10 + G_PrssdKy ;
			}
			if(G_PrssdKy == 'C')
			{
				HLCD_voidLCDClr() ; break ;
			}
			G_PrssdKy = HKPD_u8GetPressedKey() ;
		}

		if(G_Sign == '-')
		{
			G_Operand1*=-1 ;
		}

		HLCD_voidSetCursor(2,1) ;
		HLCD_voidSendData('=') ;
		HLCD_voidSendData(' ') ;
		//operation
		if(G_Oprtion == '+')
		{
			G_Result += G_Operand1 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '-')
		{
			G_Result -= G_Operand1 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '*')
		{
			G_Result *= G_Operand1 ;
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '=')
		{
			HLCD_voidDisplayNum(G_Result) ;
		}
		else if (G_Oprtion == '/')
		{
			if(G_Operand1 != 0)
			{
				G_Result /= G_Operand1 ;
				HLCD_voidDisplayNum(G_Result) ;
			}
			else
			{
				HLCD_voidSendStr("Math Error") ;
				_delay_ms(1000) ;
				HLCD_voidLCDClr() ;
				break ;
			}
		}
		G_PrssdKy = HKPD_u8GetPressedKey() ;
		HLCD_voidLCDClr() ;
	}
}
}
