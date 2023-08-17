/*
 * DIO.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Al-toukhi
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include "../../LIB/STD_TYPES.h"

#define PORTA   0
#define PORTB   1
#define PORTC   2
#define PORTD   3

#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7

#define INPUT   0x00
#define OUTPUT  0xff

#define LOW     0x00
#define HIGH    0xff

void MDIO_voidPortMode(u8 port_ID , u8 mode) ;
void MDIO_voidPortValue(u8 port_ID  , u8 value) ;

void MDIO_voidPinMode(u8 port_ID , u8 pin_ID , u8 mode) ;
void MDIO_voidPinValue(u8 port_ID , u8 pin_ID , u8 value) ;

u8 MDIO_u8PinRead(u8 port_ID , u8 pin_ID ) ;


#endif /* MCAL_DIO_DIO_H_ */
