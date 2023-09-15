/*
 * DITask.cpp
 *
 *  Created on: Mar 14, 2020
 *      Author: rvite
 *  Implementation for DITask class
 *  for multithreading on 2000Xc
 */
#include "DITask.h"
#include "DIComm.h"
#include "CyGOS.h"
#include "DIPrint.h"
/**********************************************************************************
 * Constructor
 * Initialize the DICom class attributes
 */
DITask::DITask(SINT32 Interface) : Task("DI_Task", 1024)
{
	DIComPtr= new DIComm(Interface);
}
/**********************************************************************************
 * Destructor
 * Finalize the DICom class attributes
 */
DITask::~DITask()
{
	delete DIComPtr;
}
/**********************************************************************************
 * Run
 * Calls Loop method for TCP communication
 */
void DITask::Run()
{	SINT32 i= 0;
	char TempBuffer[32];

#ifdef DEBUGING_MODE
	sprintf(DIComPtr->PrintBuffer, "DATE:TIME(%s)\n", DateTimeFormated);
	PrintString(DIComPtr->PrintBuffer);
#endif
	strcpy(DIComPtr->PrintBuffer, "");
	while (TRUE)
	{	DelayMs(10);
		DIComPtr->Loop();
#ifdef DEBUGING_MODE
//		sprintf(TempBuffer, " - %d\n", ++i);
//		strcat(DIComPtr->PrintBuffer, TempBuffer);
		PrintString(DIComPtr->PrintBuffer);
#endif

	}
}
/**********************************************************************************
 * Tick
 */
void DITask::Tick()
{
	DIComPtr->Timer();
}
