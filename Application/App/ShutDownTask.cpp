/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ShutDownTask.cpp_v   1.5   08 Jan 2015 03:18:28   AnPawar  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ShutDownTask.cpp_v  $
 * 
 *    Rev 1.5   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.4   20 Oct 2014 06:27:04   AnPawar
 * Event on ShutDown() function.
 * 
 *    Rev 1.3   11 Sep 2014 11:09:04   rjamloki
 * Corrected PowerDown event arguments
 * 
 *    Rev 1.2   21 May 2014 03:38:12   rjamloki
 * corrected data1 and data2
 * 
 *    Rev 1.1   07 May 2014 10:42:10   rjamloki
 * Recording an event on ShutDown() function.
 * 
 *    Rev 1.0   14 Apr 2014 06:32:40   rjamloki
 * Initial revision.
 */
#include "ShutDownTask.h"
#include "CyGOS.h"
#include "CPU.h"
#include "root.h"
#include "Alarms.h"
#include "Events.h"
//Static variable definition
BOOLEAN ShutDownTask::RTOSShutDown;

/*
 * Purpose: To detect the 24 volt status returned by sensor.
 * ExitCondition
 * Non zero: If 24 volt is intact
 * 0: If 24 volt is lost.
 */
inline BOOLEAN Get24VoltStatus()
{
 return (MCF_EPORT_EPPDR & MCF_EPORT_EPPDR_EPPD7);
}

/*  ShutDownTask Constructor
 *
 *  Purpose:
 *    This is the constructor of ShutDownTask class.
 *      It does initializes the static variables of class to default.
 *
 *  Entry condition:
 *
 *  Exit condition: None.
 */
ShutDownTask::ShutDownTask():Task("Shut Down Task", 1024)
{
   RTOSShutDown = FALSE;
}

/*  void ShutDownTask::Run(void)
 *
 *  Purpose:
 *    This function implements the forever loop of ShutDownTask Task.
 *     It checks a flag every RTOS tick to check the 24 volt is there or lost.
 *
 *  Entry condition: None.
 *
 *  Exit condition: None.
 */
void ShutDownTask::Run(void)
{
   DelayMs(100);

   for(;;){
      if(RTOSShutDown == TRUE)
         ShutDown();
      DelayMs(1);
   }
}

/*  void ShutDownTask::ShutDown(void)
 *
 *  Purpose:
 *    This function checks a global flag to stop the CyGOS and
 *    once the external power is lost. Being a low priority
 *    task it ensures the data integrity while stooping all other tasks.
 *
 *  Entry condition: Detected 24 volt lost.
 *  Exit Condition: CPU Restart.
 */
void ShutDownTask::ShutDown(void)
{
   CyGOS::Stop();
   while(true);// If 24 volt goes away CPU is anyway going to loose the
			    //power. If 24 volt doesn't go away external watchdog will reset the
			   //CPU and that is intended.

}
/*  void CheckForPowerSensor(void)
 *
 *  Purpose:
 *    This function is used to check whether 24V signal is present or not
 *    It is called by a high priority 1 ms task.
 *
 *  Entry condition:
 *    None.
 *
 *  Exit condition:
 *    if 24V is not present,RTOSShutDown flag is SET.
 */
void CheckForPowerSensor(void)
{
   if(ShutDownTask::RTOSShutDown == FALSE){
      // Set the flag and ShutDownTask will take care of this when ever it will get the time.
      if(!Get24VoltStatus())
      {
    	  DisableSafetyTimer();
    	  //CPLD::SetDout(Latch_OE, false);TODO: Do we need to disable output latches.
    	  ShutDownTask::RTOSShutDown = TRUE;
      }
   }
}
