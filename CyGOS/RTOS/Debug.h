// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/RTOS/Debug.h_v   1.2   05 Mar 2014 13:58:40   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module implements the simplistic debugger to use after the crash.

#ifndef DEBUG_H_
#define DEBUG_H_

#include "ArchDefs.h"

class Debug
{
public:
	Debug(int stackSize);
	static void Init();
	static void Poll();
protected:
	void Run();
	void ReadLine();
	void ReadMemory(int addr, int length);
	unsigned int HexToInt(char * & ptr, int length);
	char command[20];
	static Debug * debug;
	static uint8 * stack;
};

#endif
