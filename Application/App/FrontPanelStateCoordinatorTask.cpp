/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FrontPanelStateCoordinatorTask.cpp_v   1.14   08 Jan 2015 03:18:20   AnPawar  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FrontPanelStateCoordinatorTask.cpp_v  $
 * 
 *    Rev 1.14   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.13   06 Oct 2014 06:33:32   AnPawar
 * removed ck_qsend.h file inclusion. 
 * 
 *    Rev 1.12   03 Oct 2014 06:06:42   rjamloki
 * Commented lines cleanup
 * 
 *    Rev 1.11   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.10   09 Jul 2014 10:50:26   rjamloki
 * Removed VGAHwAvail check from run function
 * 
 *    Rev 1.9   11 Jun 2014 11:30:42   rjamloki
 * UserLoggedin flag toggled before and after starting the statemachine to make sure Powerup sequence runs and Estop gets detected while at login screen
 * 
 *    Rev 1.8   21 May 2014 10:47:56   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 03:05:38   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.6   26 Mar 2014 12:15:16   rjamloki
 * FrontPanelStateCoordinatorTask::FrontPanelStateCoordinatorTask() function changed
 * 
 *    Rev 1.5   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:24   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:36   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:26   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Module name:

 Filename:        FrontPanelStateCoordinatorTask.cpp

 Function name:
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
 */

#include "FrontPanelStateCoordinatorTask.h"
#include "FIFO.h"
#include "qdef.h"
/* inbound intertask message */
#include "commnmsg.h"             /* common msg definition            */
#include "menu.h"
#include "preset.h"
#include "keypad.h"
#include "genrlmsg.h"
#include "ticks.h"
#include "menu7a.h"
#include "display.h"
#include "getmsg.h"
#include "menu7.h"
#include "selctkey.h"
#include "spidd.h"
#include "wldstate.h"
#include "statedrv.h"
#include "util.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "RVTSHandlerTask.h"
#include "command.h"

#define FPSCASK_FIFOSIZE 10
#define WAIT_FOR_WELD_SEQ_DELAY  2000  /* Max time to wait for WELD sequence */
/* to start, in ms. */

extern SINT32 ReadOnlyTimer;
extern BOOLEAN JustPoweredUpFlag;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN VGAColdStart;
extern BOOLEAN VGAPowerUpDelay;
extern UINT8 KeyLockOutFlag;
extern enum LEVEL AccessLevel;
extern UINT8 PowerUpColdStart;

UINT8 InitFlag = FALSE;
UINT8 ColdStartFlag = FALSE;
FrontPanelStateCoordinatorTask *FrontPanelStateCoordinatorTask::thisPtr;
FPSC_QUEUE_MSG_TYPE FpscQueue;
UINT32 FpscQid;

FrontPanelStateCoordinatorTask::FrontPanelStateCoordinatorTask() :
      Task("FPSC", T_SIZE_1024), FPSCTaskQ(FPSCASK_FIFOSIZE, "FpscQ")
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   FpscQid = (UINT32) &FPSCTaskQ;
}

FrontPanelStateCoordinatorTask::~FrontPanelStateCoordinatorTask()
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask destructor                                              */
/****************************************************************************/
{

}

void FrontPanelStateCoordinatorTask::Run()
{
   /* >>> -----------------  Task Initialization  -------------------- <<< */

   UINT8 FirstKey;
   SINT32 WaitStartTime; /* Used to measure time delay */

   FpscQueue.GenericMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;

   /* -------------------------------------------- */
   /* Initialize front panel for startup messaging */
   /* -------------------------------------------- */
   /* Start front panel display manager task */
   /* set interrupt mask level in mode to disable everything below level 4 */
   /* this will cause the system to start ticking */
   DelayMs(100);
   VGAColdStart = FALSE;
   VGAPowerUpDelay = TRUE;

   /* ---------------------------------------------- */
   /* suspend and let application tasks have control */
   /* ---------------------------------------------- */
   UserLoggedIn = TRUE;//Need to start state machine initially to go through the power up sequence
					   //other wise estop wont be detected.
					   //see if((CurrentSequence != POWERDOWN) && (CurrentSequence != POWERUP)) in StateMachine function
   StartStateMachine(); /* Begin start-up sequence */
   UserLoggedIn = FALSE;//Any further operation after power up sequence should be allowed only after user is
					   //logged in.
   InitFlag = TRUE;

// need to remove and change in ready
   JustPoweredUpFlag = FALSE;

   MenuCounter = -1;

   while (1) {
      KeyLockOutFlag = FALSE;

      if (PowerUpColdStart == TRUE) /* Special test for coldstart */
      {
         PowerUpColdStart = FALSE;

         /* Wait here for state machine to run WELD sequence.  This is */
         /* important before we're going to stop the state machine here to */
         /* do a cold start and we don't want to interrupt the power-up */
         /* sequence, which comes first. */

         WaitStartTime = ReadOnlyTimer; /* Provides timeout in case WELD */
         /* sequence never happens. */

         while ((CurrentSequence != WELD) && (ReadOnlyTimer - WaitStartTime < WAIT_FOR_WELD_SEQ_DELAY))
            ;
         ClearKeypadBuffer(TRUE);/* Toss ClearKey presses so not processed, */
         /* make sure room in buffer for other. */

         if (CurrentSequence == WELD) /* If still no WELD, just skip cold start */
         {
            VGAColdStart = TRUE;
            if (CurrentSetup.PassWordFlag & BIT0) /* If pwords on, make user */
            { /* enter one before clearing */
               if (AccessLevel >= MAINTENANCE) {
                  ColdStartFlag = TRUE;
                  DoColdStart();
               }
            }
            else {
               ColdStartFlag = TRUE;
               DoColdStart();
            }
         }
      }
      SetAmpControl();
      SetFreqControl();
      if (ColdStartFlag) {
         FirstKey = SetupKey; // Go to Weld Setup screen
         ColdStartFlag = FALSE;
      }
      else if (CurrentSetup.StartScreen) {
         FirstKey = RunKey;
      }
      else
         // For the Main   J.B.
         FirstKey = NOKEY;

      VGAPowerUpDelay = FALSE;
      SendFakeKeyPress((KEY_CODE_TYPE) FirstKey);
      BlankMenuCounter = 1; /* prevent DisplayMenu from displaying extra MainMenu */
      DisplayMenu((MENU*) TheMainMenu);
      Suspend();

   } /* end while FOREVER loop */
}

void FrontPanelStateCoordinatorTask::Tick()
{
}

