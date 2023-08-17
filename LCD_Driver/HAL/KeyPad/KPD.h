/*
 * KPD.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Al-toukhi
 */

#ifndef HAL_KEYPAD_KPD_H_
#define HAL_KEYPAD_KPD_H_

#include "../../LIB/STD_TYPES.h"

#define KPD_Row   4
#define KPD_Col   4

#define KPD_Port  2

void HKPD_voidKeyPadInit() ;
u8 HKPD_u8GetPressedKey() ;


#endif /* HAL_KEYPAD_KPD_H_ */
