/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ShutDownTask.h_v   1.0   14 Apr 2014 06:33:58   rjamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ShutDownTask.h_v  $
 * 
 *    Rev 1.0   14 Apr 2014 06:33:58   rjamloki
 * Initial revision.
 */
#ifndef SHUTDOWNTASK_H_
#define SHUTDOWNTASK_H_
#include "Task.h"
#include "portable.h"

class ShutDownTask: public Task
{
public:
   ShutDownTask();
   static BOOLEAN RTOSShutDown;
protected:
   virtual void Run(void);
   void ShutDown(void);
};
void CheckForPowerSensor(void);
#endif /* SHUTDOWNTASK_H_ */
