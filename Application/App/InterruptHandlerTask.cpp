/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/InterruptHandlerTask.cpp_v   1.18   13 Mar 2015 06:07:46   amaurya  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/InterruptHandlerTask.cpp_v  $
 * 
 *    Rev 1.18   13 Mar 2015 06:07:46   amaurya
 * Declaration  of the variable "TriggerCnt" moved to starting position of the function declaration as per Branson standard coding.
 * 
 *    Rev 1.17   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.16   11 Dec 2014 08:35:44   AnPawar
 * 10 second time out changes after link is lost.
 * 
 *    Rev 1.15   28 Nov 2014 07:36:18   rjamloki
 * Removed unused Variables.
 * 
 *    Rev 1.14   10 Nov 2014 04:50:54   AnPawar
 * removed unused if ,12.F review change.
 * 
 *    Rev 1.13   03 Oct 2014 06:07:40   rjamloki
 *  DupsBid variable removed 
 * 
 *    Rev 1.12   05 Sep 2014 06:29:56   rjamloki
 * Added counter for downspeed tuning fix while cycling fast
 * 
 *    Rev 1.11   28 Jul 2014 12:36:40   rjamloki
 * psos.h removed
 * 
 *    Rev 1.10   11 Jun 2014 11:46:00   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:47:58   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:07:30   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   07 May 2014 10:21:44   rjamloki
 * Interrupt_HandlerTask::Run() changed.
 * 
 *    Rev 1.6   14 Apr 2014 09:59:12   rjamloki
 * Added watchdog trigger
 * 
 *    Rev 1.5   26 Mar 2014 12:19:46   rjamloki
 * Interrupt_HandlerTask::Interrupt_HandlerTask() function changed
 * 
 *    Rev 1.4   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.3   05 Mar 2014 13:56:26   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   10 Feb 2014 04:59:38   rjamloki
 * preset changes to support 1000 preset.
 * 
 *    Rev 1.1   03 Jan 2014 08:45:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

#include "InterruptHandlerTask.h"
#include "qdef.h"
#include "preset.h"
#include "menuhorn.h"
#include "timer.h"
#include "state.h"
#include "statedrv.h"
#include "portable.h"
#include "encoder.h"
#include "mansensr.h"
#include "menutest.h"
#include "interpol.h"
#include "inports.h"
#include "qsm.h"
#include "actnvram.h"
#include "spidd.h"
#include "iotest332.h"
#include "stdio.h"
#include "Board.h"
#include "TaskManager.h"
#include "ShutDownTask.h"
#include "A1025R.h"
#include "root.h"
#include "Events.h"

#define IHTASK_FIFOSIZE 1024

Interrupt_HandlerTask *Interrupt_HandlerTask::thisPtr;
UINT32 IhQid;

extern SINT32 ReadOnlyTimer; /* Added this because tasks write to OneMilTimer */
extern SINT32 EncoderPos;
extern UINT32 DownspeedTuneCounter;

extern UINT32 TotalCycleTime;
extern BOOLEAN HornDownFlag;

extern UINT16 DiagFlag;
extern INBITS Inp;
extern BOOLEAN IOTestFlag;

//TODO:Watchdog monitoring
UINT32 WatchDogExpectedMask;//define which events need mandatory monitoring by watchdog.
							//have a bit for each event. Maximum 32 events can be monitored.
							//New Events to be monitored can be added at run time.
							//Events which no more require monitoring can be cleared at run time.

UINT32 WatchDogCurrMask;//Needs to be cleared whenever watchdog is triggered. Need to set the
						//corresponding bit when the event occurs. CurrMask and expected mask shall
						//be equal before triggering the watchdog.

Interrupt_HandlerTask::Interrupt_HandlerTask() :
      Task("IHT", T_SIZE_4096), Interrupt_HandlerTaskQ(2, "IhtQ")
/****************************************************************************/
/* Description:-                                                            */
/* Interrupt_HandlerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   IhQid = (UINT32) &Interrupt_HandlerTaskQ;
}

Interrupt_HandlerTask::~Interrupt_HandlerTask()
/****************************************************************************/
/* Description:-                                                            */
/* Interrupt_HandlerTask destructor                                              */
/****************************************************************************/
{

}

void Interrupt_HandlerTask::Run()
{
   SINT8 ch;
   static int TriggerCnt;
   while (TRUE) {
      Interrupt_HandlerTaskQ.Read(this, ch, -1);
      CheckForPowerSensor();
      ReadOnlyTimer++;
      TotalCycleTime++;
      DownspeedTuneCounter++;

      /* Read the Power supply ADC every ms */

	  if (NovramEnable == FALSE)
		ReadPSADC();


      /*--- Make sure actuator AED,AES  ---*/
      if (CurrentSetup.Actuator != AE) {
         EncoderPos = ReadEncoder();
      }
      if (HornDownFlag) /* Horn Down mode doesn't use state */
      { /* machine, instead checks for its */
         HornDownISR(); /* own events. */
      }
      else {
         if (UpdateTimers() == TRUE)
            StateMachine();
         if ((DiagFlag == TRUE) && (Inp.Estop == FALSE))
            UpdateDiagScreen();
      }
      if (IOTestFlag == TRUE)
         CheckIOTest();
      ManageSensors();

	  TriggerCnt ++;
	  if(TriggerCnt >= WD_TRIGGERCNT)
	  {
		if((WatchDogCurrMask & WatchDogExpectedMask) == WatchDogExpectedMask)
		{
			TriggerExternalWatchDog();
			TriggerCnt -= WD_TRIGGERCNT;
			WatchDogCurrMask = 0;
		}
	  }
	  CheckForClockLost();

   } /* end while forever */
}


/*  void CheckForClockLost(void)
 *
 *  Purpose:
 *     This function is responsible for checking the CPU PLL Clock
 *     status. It writes an Event in case of Clock Lost.
 *
 *  Entry condition:
 *    None.
 *
 *  Exit condition:
 *    None.
 */
void Interrupt_HandlerTask::CheckForClockLost()
{
   static BOOLEAN ClkLost = FALSE;
   if(MCF_CLOCK_PSR & MCF_CLOCK_PSR_LOCKS){
      if(ClkLost == FALSE){
         RecordEvents(EVENT_CLOCK_LOST,"","");
         ClkLost = TRUE;
       }
   }
}
