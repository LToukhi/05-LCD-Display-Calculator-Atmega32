/*
 * KPD.c

 *
 *  Created on: Aug 14, 2023
 *      Author: Al-toukhi
 */
#include <util/delay.h>
#include "KPD.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"

u8 KPD_Matrix[KPD_Row][KPD_Col]={{ 7 , 8 , 9 , '/'} ,
		                         { 4 , 5 , 6 , '*'} ,
								 { 1 , 2 , 3 , '-'} ,
								 {'C', 0 ,'=', '+'}
};

void HKPD_voidKeyPadInit()
{
	MDIO_voidPortMode(KPD_Port , 0x0f) ;
	MDIO_voidPortValue(KPD_Port , 0xff);
}

u8 HKPD_u8GetPressedKey()
{
	u8 L_u8PressedKey ;
	u8 L_u8Stop=1 ;
	while(L_u8Stop)
	{
	for(u8 col = 0 ; col < KPD_Col ; col++)
	{
		MDIO_voidPinValue(KPD_Port , col , LOW) ;
		for(u8 row = 0 ; row < KPD_Row ; row++)
		{
			if(MDIO_u8PinRead(KPD_Port , row+4) == 0)
			{
				while(MDIO_u8PinRead(KPD_Port , row+4) == 0){}
				_delay_ms(20) ;
				L_u8PressedKey = KPD_Matrix[row][col] ;
				L_u8Stop = 0 ;
				break ;
			}
		}
	MDIO_voidPinValue(KPD_Port , col , HIGH) ;
	}
	}
return L_u8PressedKey ; }

