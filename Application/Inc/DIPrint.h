/*
 * DIPrint.h
 *
 *  Created on: Mar 16, 2020
 *      Author: rvite
 */

#ifndef INC_DIPRINT_H_
#define INC_DIPRINT_H_
#include "portable.h"

#define DEBUGING_MODE
#define TESTING_MODE
#define SHOW_DATAx

/*************************************************************************************************/
void PrintString(char *Buffer);
BOOLEAN ischar(char Byte);
void PrintBufferf(SINT8 *Buffer, SINT16 n);
#endif /* INC_DIPRINT_H_ */
