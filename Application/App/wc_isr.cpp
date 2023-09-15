/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/wc_isr.cpp_v   1.14   22 Mar 2015 17:08:38   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1996                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/wc_isr.cpp_v  $
 * 
 *    Rev 1.14   22 Mar 2015 17:08:38   rjamloki
 * Restored Hugo's changes of MsInt cleanup
 * 
 *    Rev 1.13   17 Jul 2014 13:01:08   hasanchez
 * Changes about freq offset
 * 
 *    Rev 1.12   15 Jul 2014 17:33:42   hasanchez
 * Changes about freq offset
 * 
 *    Rev 1.11   09 Jul 2014 11:55:42   rjamloki
 * Cleaned up MsInt function.
 * 
 *    Rev 1.10   11 Jun 2014 12:40:30   rjamloki
 * removed redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:48:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:55:36   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   14 Apr 2014 09:59:46   rjamloki
 * Added watchdog trigger in MinMsInt to which shall be called every tick root task execution.
 * 
 *    Rev 1.6   06 Mar 2014 11:04:02   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:50   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:58   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:58   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
-------------------------- MODULE DESCRIPTION -------------------------------

  This module sets the interrupt vector for the 1ms loop and processes the
  interrupt request.
------------------------------- DESCRIPTION -----------------------------------

----------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "encoder.h"
#include "mansensr.h"
#include "preset.h"
#include "state.h"
#include "menutest.h"
#include "statedrv.h"
#include "interpol.h"
#include "inports.h"
#include "timer.h"
#include "menuhorn.h"
#include "qsm.h"

#include "actnvram.h"
#include "spidd.h"
#include "iotest332.h"
#include "InterruptHandlerTask.h"
#include "stdio.h"
#include "root.h"
#include "A1025R.h"
#include "ticks.h"

/* This is only set for testing purposes */
//#define INCLUDE_THROUGHPUTTEST 1

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT16   OneMilTimer;
SINT32   ReadOnlyTimer;    /* Added this because tasks write to OneMilTimer */
SINT32   EncoderPos;

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/


void MsInt(void)
/****************************************************************************/ 
/*                                                                          */    
/* The interrupt is generated on every 1 ms by PIT module. It invlokes the  */
/* Interrupt Handler task by writing into the Queue of same.				*/
/****************************************************************************/ 
{
	if(Interrupt_HandlerTask::thisPtr)
		Interrupt_HandlerTask::thisPtr->Interrupt_HandlerTaskQ.Write(0 ,'a' , 0);
	OneMilTimer++;
}

void MinMsInt(void)
/****************************************************************************/ 
/*                                                                          */    
/* Minimal 1ms interrupt service routine, used during startup when not      */
/* enough of the system is initialized to call the real thing.  Provides    */
/* display and timing support.                                              */    
/*                                                                          */    
/****************************************************************************/
//called at rtos tick before root starts other tasks.
//While root does so may things at power up (specially the act nov ram communication) this
//function serves the external watchdog.Later the triggering of watchdog is handled by 1 ms task.
{
   static int TriggerCnt;
   TriggerCnt += MILLS_PER_TICK;
   if(TriggerCnt >= WD_TRIGGERCNT)
    {
		TriggerExternalWatchDog();
		TriggerCnt -= WD_TRIGGERCNT;
	}
}
