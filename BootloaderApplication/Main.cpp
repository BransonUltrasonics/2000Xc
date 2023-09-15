// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/BootloaderApplication/Main.cpp_v   1.0   14 Apr 2014 05:38:50   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2008, 2013
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3 MultiBoot loader.
//
// This is the main module for MultiBoot loader.

#include "stdio.h"
#include "CyGOS.h"
#include "LED.h"
#include "DebugNew.h"

#include "CPU.h"

void SetLeds(int slow, int fast)
{
	LED::Set(1, slow);
	LED::Set(2, fast);
}

char * buildDate = __DATE__;
char * buildTime = __TIME__;

int main()
{

	CyGOS::EnableDebug();
	printf("\x0C" "Boot loader ver. 2.0.1\n");
	printf("Build Date: %s %s\n\n", buildDate, buildTime);

	CyGOS::Init();
	CyGOS::CreateLedTasks(1, 1, SetLeds);

	int priority = 20;
	CyGOS::CreateSerialBootTask(priority);
	CyGOS::Start(1000);

	return 0;
}
