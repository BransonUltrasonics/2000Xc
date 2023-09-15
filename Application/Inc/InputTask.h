/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/InputTask.h_v   1.6   16 Apr 2015 07:31:14   rjamloki  $
*/
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/InputTask.h_v  $
 * 
 *    Rev 1.6   16 Apr 2015 07:31:14   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.5   16 Feb 2015 01:25:38   amaurya
 * diagnostics added to trace recalibrate actuator alarm
 * 
 *    Rev 1.4   11 Feb 2015 06:40:52   amaurya
 * changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.3   05 Mar 2014 13:57:10   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:39:06   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:12:03  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 06:47:06   amaurya
 * Initial revision.
 * 

 */

#ifndef INPUTTASK_H_
#define INPUTTASK_H_
#include "Task.h"
#include "portable.h"

//struct ADCData;
class InputTask: public Task
{
public:
	InputTask();
	void Tick();
protected:
	void PrintHelp();
	void Run();
	void ProgramFlash(int intf);
	void ProgramBootFlash(int intf);

};
void SetDefaultConfigAll();

#endif
