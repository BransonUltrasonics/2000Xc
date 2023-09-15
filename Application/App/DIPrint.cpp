/*
 * DIPrint.cpp
 *
 *  Created on: Mar 16, 2020
 *      Author: rvite
 */
#include "DIPrint.h"
#include "CyGOS.h"

/*************************************************************************************************/
void PrintString(char *Buffer)
{
#ifdef DEBUGING_MODE
	if (!*Buffer)
		return;
	while (*Buffer)
	{	CyGOS::EnableDebug();
		putchar(*Buffer++);
		CyGOS::DisableDebug();
	}
	CyGOS::DelayMs(10);
#endif
}
/*************************************************************************************************/
/*************************************************************************************************/
BOOLEAN ischar(char Byte)
{
	return (Byte == ' ') || ((Byte >='0')&&(Byte <='9'))  || ((Byte >='A')&&(Byte <='Z'))  || ((Byte >='a')&&(Byte <='z'));
}

/*************************************************************************************************/
void PrintBufferf(SINT8 *Buffer, SINT16 n)
{	int i;
char PrintBuffer[1024], CharToNum[1024], Byte;
	if (!*Buffer)
		return;

	strcpy(PrintBuffer, "Printing: Preamble + Header: (20) Bytes ");
	PrintString(PrintBuffer);

#ifdef SHOW_DATA
	strcpy(PrintBuffer, "");
	for (i= 0; i< 20; i++) //Preamble + Header
	{	Byte= *(SINT8 *)(Buffer+i) & 0xFF;
		sprintf(CharToNum, "%u ", (unsigned char)Byte);
		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");
	PrintString(PrintBuffer);
#endif


	if (n >= 20)
	{	sprintf(PrintBuffer, "+ Load: (%d) Bytes\n", n - 20);
		PrintString(PrintBuffer);
#ifdef SHOW_DATA
		strcpy(PrintBuffer, "");
		for (i= 20; i < n; i++) //BuffLen
		{	Byte= *(SINT8 *)(Buffer+i) & 0xFF;
			sprintf(CharToNum, ischar(Byte)? "'%c' " : "%u ", Byte);
			strcat(PrintBuffer, CharToNum);
		}
		strcat(PrintBuffer, "\n");
		PrintString(PrintBuffer);
#endif
	}

	return;
}

/*************************************************************************************************/



