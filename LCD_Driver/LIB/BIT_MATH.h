/*
 * BIT_math.h
 *
 *  Created on: Aug 12, 2023
 *      Author: Al-toukhi
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define LMTH_SetBit(Reg,Bitnum)      Reg |= (1<<Bitnum)
#define LMTH_ClrBit(Reg,Bitnum)      Reg &= (~(1<<Bitnum))
#define LMTH_ToggleBit(Reg,Bitnum)   Reg ^= (1<<Bitnum)
#define LMTH_SetByte(Reg,Value)      Reg = Value

#define LMTH_GetBit(Reg,Bitnum)      (Reg>>Bitnum)&0x01


#endif /* BIT_MATH_H_ */
