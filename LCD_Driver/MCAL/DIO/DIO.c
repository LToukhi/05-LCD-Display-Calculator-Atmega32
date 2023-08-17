/*
 * DIO.c
 *
 *  Created on: Aug 14, 2023
 *      Author: Al-toukhi
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO.h"

//registers addresses///////////////////////////////

#define DIO_PORTA_Reg    *((volatile u8*) 0x3B)
#define DIO_DDRA_Reg     *((volatile u8*) 0x3A)
#define DIO_PINA_Reg     *((volatile u8*) 0x39)

#define DIO_PORTB_Reg    *((volatile u8*) 0x38)
#define DIO_DDRB_Reg     *((volatile u8*) 0x37)
#define DIO_PINB_Reg     *((volatile u8*) 0x36)

#define DIO_PORTC_Reg    *((volatile u8*) 0x35)
#define DIO_DDRC_Reg     *((volatile u8*) 0x34)
#define DIO_PINC_Reg     *((volatile u8*) 0x33)

#define DIO_PORTD_Reg    *((volatile u8*) 0x32)
#define DIO_DDRD_Reg     *((volatile u8*) 0x31)
#define DIO_PIND_Reg     *((volatile u8*) 0x30)

//port mode func///////////////////////////////////

void MDIO_voidPortMode(u8 A_u8Port , u8 A_u8Mode)
{
	if(A_u8Port <= PORTD)
	{
		switch(A_u8Port)
		{
			case PORTA : DIO_DDRA_Reg = A_u8Mode ; break ;
			case PORTB : DIO_DDRB_Reg = A_u8Mode ; break ;
			case PORTC : DIO_DDRC_Reg = A_u8Mode ; break ;
			case PORTD : DIO_DDRD_Reg = A_u8Mode ; break ;
		}
	}
}


//port value////////////////////////////
void MDIO_voidPortValue(u8 A_u8Port , u8 A_u8Value)
{
	if(A_u8Port <= PORTD)
	{
		switch(A_u8Port)
		{
			case PORTA : DIO_PORTA_Reg = A_u8Value ; break ;
			case PORTB : DIO_PORTB_Reg = A_u8Value ; break ;
			case PORTC : DIO_PORTC_Reg = A_u8Value ; break ;
			case PORTD : DIO_PORTD_Reg = A_u8Value ; break ;
		}
	}
}

//pin mode func///////////////////////////////////////////////

void MDIO_voidPinMode(u8 A_u8Port , u8 A_u8Pin , u8 A_u8Mode)
{
	if((A_u8Port<=PORTD) && (A_u8Pin<=7))
	{
		if ((A_u8Mode == OUTPUT) || (A_u8Mode == 1))
		{
			switch(A_u8Port)
			{
				case PORTA : LMTH_SetBit(DIO_DDRA_Reg , A_u8Pin) ; break ;
				case PORTB : LMTH_SetBit(DIO_DDRB_Reg , A_u8Pin) ; break ;
				case PORTC : LMTH_SetBit(DIO_DDRC_Reg , A_u8Pin) ; break ;
				case PORTD : LMTH_SetBit(DIO_DDRD_Reg , A_u8Pin) ; break ;
			}
		}
		else if ((A_u8Mode == INPUT) || (A_u8Mode == 0))
		{
			switch(A_u8Port)
			{
				case PORTA : LMTH_ClrBit(DIO_DDRA_Reg , A_u8Pin) ; break ;
				case PORTB : LMTH_ClrBit(DIO_DDRB_Reg , A_u8Pin) ; break ;
				case PORTC : LMTH_ClrBit(DIO_DDRC_Reg , A_u8Pin) ; break ;
				case PORTD : LMTH_ClrBit(DIO_DDRD_Reg , A_u8Pin) ; break ;
			}
		}
	}
}

//pin output func/////////////////////////////////////

void MDIO_voidPinValue(u8 A_u8Port , u8 A_u8Pin , u8 A_u8Value)
{
	if((A_u8Port<=PORTD) && (A_u8Pin<=7))
	{
		if ((A_u8Value == HIGH) || (A_u8Value == 1))
		{
			switch(A_u8Port)
			{
				case PORTA : LMTH_SetBit(DIO_PORTA_Reg , A_u8Pin) ; break ;
				case PORTB : LMTH_SetBit(DIO_PORTB_Reg , A_u8Pin) ; break ;
				case PORTC : LMTH_SetBit(DIO_PORTC_Reg , A_u8Pin) ; break ;
				case PORTD : LMTH_SetBit(DIO_PORTD_Reg , A_u8Pin) ; break ;
			}
		}
		else if ((A_u8Value == LOW) || (A_u8Value == 0))
		{
			switch(A_u8Port)
			{
				case PORTA : LMTH_ClrBit(DIO_PORTA_Reg , A_u8Pin) ; break ;
				case PORTB : LMTH_ClrBit(DIO_PORTB_Reg , A_u8Pin) ; break ;
				case PORTC : LMTH_ClrBit(DIO_PORTC_Reg , A_u8Pin) ; break ;
				case PORTD : LMTH_ClrBit(DIO_PORTD_Reg , A_u8Pin) ; break ;
			}
		}
	}
}

//pin read func////////////////////////

u8 MDIO_u8PinRead(u8 A_u8Port , u8 A_u8Pin)
{
	u8 read ;
	if((A_u8Port<=PORTD) && (A_u8Pin<=7))
	{
		switch(A_u8Port)
		{
			case PORTA : read = LMTH_GetBit(DIO_PINA_Reg , A_u8Pin) ; break ;
			case PORTB : read = LMTH_GetBit(DIO_PINB_Reg , A_u8Pin) ; break ;
			case PORTC : read = LMTH_GetBit(DIO_PINC_Reg , A_u8Pin) ; break ;
			case PORTD : read = LMTH_GetBit(DIO_PIND_Reg , A_u8Pin) ; break ;
		}
	}
return read ;}

