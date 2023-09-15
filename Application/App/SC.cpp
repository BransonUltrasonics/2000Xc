/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/SC.cpp_v   1.23   Nov 06 2017 15:56:18   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/SC.cpp_v  $
 * 
 *    Rev 1.23   Nov 06 2017 15:56:18   RJamloki
 * Set pressure for quick calibration to 31PSI
 * 
 *    Rev 1.22   Oct 10 2017 13:41:54   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.21   09 Apr 2015 05:27:46   RJamloki
 * Fix for recal 990..Made InitForceEstimateBuffer true at places where Partcontact flag is getting initialized to falsefalse
 * 
 *    Rev 1.20   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.19   28 Nov 2014 07:40:42   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.18   17 Nov 2014 10:03:10   RJamloki
 * CalActErrorFlag is made False in ScfinalCleanUp as Pressure Calibration after incomplete Short Calib was going into Infinite Please Wait.
 * 
 *    Rev 1.17   14 Nov 2014 05:28:10   rjamloki
 * Calibration passed or failed event removed.
 * 
 *    Rev 1.16   10 Nov 2014 04:58:58   AnPawar
 * SCInitialize() ,ManualSCInitialize() ,UpdateMessage() function changed.
 * 
 *    Rev 1.15   06 Oct 2014 06:44:36   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.14   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.13   11 Sep 2014 11:05:20   rjamloki
 * Added actuator calibration event
 * 
 *    Rev 1.12   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.11   20 Jun 2014 14:28:02   rjamloki
 * Minor tweaks for AES actuator calibration.
 * 
 *    Rev 1.10   11 Jun 2014 12:07:50   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:37:56   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   26 Mar 2014 12:34:22   rjamloki
 * SelectManualSCSequence(),WaitForSpringRate(),StartCalPB() changed
 * 
 *    Rev 1.6   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:44   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.3   03 Jan 2014 08:45:50   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION -----------------------------

 Module name: sc

 Filename:    Sc      .c

 Function Name: SC

          Written by:   Laura Markure
                Date:   06-20-96
            Language:   "C"
  ----------------------------- DESCRIPTION --------------------------------*/


/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define MAX_TABLE_PTS 11    
#define MANUALDOWNSPD 20   /* downspeed = 20% */
/*------------------------------ INCLUDES ----------------------------------*/

#include "preset.h"
#include "keypad.h"
#include "param.h"
#include "wldstate.h"
#include "weld.h"
#include "digout.h"
#include "ready.h"
#include "beep.h"
#include "genrlmsg.h"
#include "alarms.h"
#include "interpol.h"
#include "mansensr.h"
#include "menucalb.h"
#include "display.h"
#include "sc.h"
#include "snsrcalb.h"
#include "spidd.h"
#include "states.h"
#include "state.h"
#include "statedrv.h"
#include "selctkey.h"
#include "SystemManagerTask.h"
#include "util.h"
#include "weld_obj.h"
#include "menu5.h"
#include "getmsg.h"
#include "FrontPanelKeypadTask.h"
#include "actnvram.h"
#include "encoder.h"
#include "string.h"
#include "stdio.h"
#include "SystemManagerTask.h"
#include "Events.h"


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                       (scope is global to ALL files)                     */


BOOLEAN SpringRateComplete = TRUE,DeflectionComplete;
UINT16 Y1Distance,Y2Distance;
SINT32 Vel1Pt,Vel2Pt;
double Atop;
UINT16 Mode;
UINT16 PVPCountDown,VelCount;
UINT32 Velocity,Deflection;
UINT32 CalbAve[20];
BOOLEAN CalActErrorFlag =FALSE;

/*------------------------------ EXTERNAL DATA -----------------------------*/
extern INBITS Inp;
extern UINT16 StaggerWatchDogTimer;
extern UINT16 OkToDisplayAlarms;          /* TRUE:cycle is complete, display ok */
extern BOOLEAN PlsWaitTimerFlag;               /* Please Wait Timer Flag */
extern UINT16 NoPressureFlag;
extern UINT16 CalibrationPassed;
extern UINT16 UpperLimitTimer;
extern BOOLEAN UlsTimeout;
extern UINT16 TimerLoopCounter;
extern UINT16 SpringRateTimeout;
extern BOOLEAN AdvanceMenuFlag;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern SINT32 EncoderPos;
extern UINT16 ADForce;
extern UINT16 TempSpringRateTable[];
extern BOOLEAN AdvanceMenuFlag;
extern UINT8  MainKeyFlag;
extern UINT16 PartContactFlag;
extern UINT32 CurrentVelocity;
extern UINT16 CheckDownSpeed; 

extern BOOLEAN VGACalAllowed;
extern UINT8 MenuNxtPointer;
extern UINT8 CalMenus[MAX_MENUS];
/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */
static bool ScreenDisplayed = FALSE;   /* make sure updatemessage only calls display message once*/
static GENERIC_MSG WeldMsgOut;

/*-------------------------------- CODE ------------------------------------*/

void SCInitialize(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when calibration is allowed.                     */
/*                                                                          */
/* Outputs : ScreenDisplayed                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   MenuNxtPointer = 0;
   memset(&CalMenus,0,(sizeof(CalMenus)));
   SelectSCSequence();         /* Initialize State Sequence for Calibration */
   if ( (CurrentSetup.Actuator != AED) && (CurrentSetup.Actuator != AES) && (CurrentSetup.Actuator != MICRO) && (CurrentSetup.Actuator != MICROC))
      UpdateKeyMask(DISABLESEL3);
   AdvanceMenuFlag = FALSE;
   Mode = STARTSWITCHES;
   SpringRateComplete = FALSE;
   PlsWaitTimerFlag = TRUE;                   /* Advance State machine Flag */
   CalibrationPassed = CAL_ABORTED;           /* Assume calibration will be aborted */

   /* the next variables for the aef actuator only */
   PVPCountDown = 1500;                       /* countdown timer */
   AdvanceMenuFlag = FALSE;
   VelCount = 0;                              /* countup timer */
   Velocity = 0;
   TimerLoopCounter = 2000;
   NoPressureFlag = TRUE;
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
   ScreenDisplayed = FALSE;
   CheckDownSpeed = 0; 
   GetDefSpringRateTable();              /* Copy current SpringRateTable to temp table */
   SpringRateTimeout = 0;
   CurrentSetup.SpringRateTable[0] = ADForce; /* save the loadcell reading */
   CurrentSetup.HornWeightOffset = (SINT16)(ADForce - NVR.CalHomeOffset) * 432/1000;
   if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
	 SetPressureValue = CAL_PRESSURE_3; //31 PSI
   	 SetFlowValue = CAL_FLOW_STEPS_2; //30% DOWNSPEED
   }
   CurrentVelocity = 0;
   Vel1Pt = 0;
   Vel2Pt = 0;
   DeflectionComplete = FALSE;
   CalActErrorFlag =TRUE;
}

void ManualSCInitialize(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when manual mode is selected                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{

   MenuNxtPointer = 0;
	memset(&CalMenus,0,(sizeof(CalMenus)));
   SelectManualSCSequence();   /* Initialize State Sequence for Calibration */
   if ( (CurrentSetup.Actuator != AED) &&
         (CurrentSetup.Actuator != AES) && (CurrentSetup.Actuator != MICRO) && (CurrentSetup.Actuator != MICROC))
      UpdateKeyMask(DISABLESEL3);
   AdvanceMenuFlag = FALSE;
   SpringRateComplete = FALSE;
   PlsWaitTimerFlag = TRUE;                   /* Advance State machine Flag */
   CalibrationPassed = CAL_ABORTED;           /* Assume calibration will be aborted */
   Mode = MANUAL;

/* the next variables for for the aef actuator only */
   PVPCountDown = 1500;                       /* countdown timer */
   VelCount = 0;                              /* countup timer */
   Velocity = 0;
   CurrentVelocity = 0;
   TimerLoopCounter = 2000;
   NoPressureFlag = TRUE;
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
   ScreenDisplayed = FALSE;
   CheckDownSpeed = 0; 
   SetPV(MANUALDOWNSPD, HOME_TO_DWNSPD);
   GetDefSpringRateTable();
   SpringRateTimeout = 0;
   CurrentSetup.SpringRateTable[0] = ADForce; /* save the loadcell reading */
   CurrentSetup.HornWeightOffset = (SINT16)(ADForce - NVR.CalHomeOffset) * 432/1000;
   ZeroEncoder();
   Vel1Pt = 0;
   Vel2Pt = 0;
   DeflectionComplete = FALSE;
}

void StartCalPB(void){
/****************************************************************************/
/*                                                                          */
/*  This function is called whenever both start switches have been pressed. */
/*                                                                          */
/****************************************************************************/

   OkToDisplayAlarms = FALSE;


/*----- Clean up trigger stuff from last cycle -----*/

   StaggerFlag = FALSE;
   StaggerWatchDogTimer = 0;
   UlsTimeout = FALSE;                  /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0;                 /* Reset timer to zero              */
   OKToAdvance = FALSE;

}

void TestCalPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed between the time one palm   */
/*  is pressed and before two palm buttons are pressed.  It will be a      */
/*  watchdog on the stagger time.                                          */
/*                                                                         */
/***************************************************************************/
{
   if(Inp.OnePB == TRUE)
   {
      if (++StaggerWatchDogTimer > PALMBUTTON_STAGGER_TIME) {
         StaggerFlag = TRUE;
         CalibrationPassed = CAL_ABORTED;   /* assume calibration will be aborted */
         SendFakeKeyPress(MainKey);
      }
   }
}

void WaitForSpringRate(void){

   if((Inp.BothPB == FALSE) && (Mode == STARTSWITCHES))
   {
      SVOff();                            /* Turn off SV to bring hown up      */
      CalibrationPassed = CAL_FAILED;
      PlsWaitTimerFlag = FALSE;               /* Advances the state machine */
   }
   CurrentVelocity = VelocityEstimator(EncoderPos);
   UpdateDownSpeed();
   if(Inp.uls == FALSE)
   {
      if(SpringRateComplete == FALSE) {
    	  CheckSpringRate();
      }
      else
      {
         PlsWaitTimerFlag = FALSE;               /* Advances the state machine */
         CalibrationPassed = CAL_PASSED;
      }
   }
   else
   {
      if(Mode == STARTSWITCHES)
      {
    	  ZeroEncoder();
      }
   }
}                                       /* end of WaitForSpringRate */


void UpdateMessage(void){
   UINT16 Index;

   if (ScreenDisplayed == FALSE)
   {
      /* Save the springratetable, loadcellathome, and clear the alarms for AEF only */
      SVOff();                            /* Turn off SV to bring hown up      */
    /* Test for Version6 AED Upgrade error */
      if ( (NVR.LoadCell[0] < NO_LOADCELL_OFFSET) &&
           ( (NVR.ActId == NVR_AED) ||
             (NVR.ActId == NVR_AES) || (NVR.ActId == NVR_MICRO) || (NVR.ActId == NVR_MICROC) ||
             (NVR.ForceGauge == SBEAM) ) )
      {
         for(Index = 0; Index < MAX_TABLE_PTS; Index++)
         {
            NVR.LoadCell[Index] += LoadCellOffset;
            if(NVR.LoadCell[Index] < 0) NVR.LoadCell[Index] = 0;
         }
         ErrorCode = (ERRORCODE_ARG)0;     /* need to clear incase calibration is run again */
         WeldMsgOut.common.opcode = OP_NVM_WRITE_UPGRADE805;
         SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldMsgOut), 20);/* 20 ms */
      }
      else if ( CalibrationPassed != CAL_PASSED)
      {
         for (Index = 1; Index < SPRING_RATE_SIZE; Index++)
         {
            CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
         }
      }                        
      DisplayNextScreen();
      ScreenDisplayed = TRUE;  
      UpdateCurrentPreset(SAVECURRENTSETUP,0,0);  /* save springrate to BBram */
   }                           
}                              /* end of UpdateMessage */

void SCFinalCleanup(void) {
/* Called when the actuator calibration is complete or terminated */
   if(CalibrationPassed != CAL_NOT_ALLOWED)
   {
/* Put state machine back */
      SelectWeldSequence();               /* Restore proper weld sequence      */
      StartStateMachine();                /* Start the state machine here      */
      if (CalibrationPassed == CAL_PASSED){
         SetReady();
         ClearCalibrationAlarms();
      }


      SVOff();                            /* Turn off SV to bring hown up      */


/* Force Main Menu key */
      if(MainKeyFlag == FALSE && VGACalAllowed == FALSE)
         SendFakeKeyPress(MainKey);
      CalibrationPassed = CAL_NOT_ALLOWED;
   }
                                       /* end if (CalibrationPassed != CAL_NOT_ALLOWED) */
   VGACalAllowed = FALSE;
   CalActErrorFlag = FALSE;
}                                       /* end of SCFinalCleanup */


void SelectSCSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the SC state sequence.                                          */
/*                                                                         */
/***************************************************************************/{
   UINT16  SaveStateMachineFlag;
   UINT16 i = 0;

   /* Set the current state to TopOfList */
   ResetStateMachine();                /* Turn off the state machine first */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &CalTopOfList;     /* enter the sequence of states */
   /* CalForceMenu1 wait for next menu to be displayed */
                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* W/Start Switches     */
                                       /* W/Manual Overide     */
                                       /*                      */
                                       /**--------------------**/
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator==MICRO))
      WeldSequence[i++] = &MenuSyncST;  /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Set Regulator Tor    */
                                       /* Operating PSI        */
                                       /* ____________Continue */
                                       /**--------------------**/


/* wait for menu to set CalDistanceFlag wait for AEF */
//   WeldSequence[i++] = &MenuSyncST;    /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Cal. Distance        */
                                       /*                  Yes */
                                       /*                   No */
                                       /**--------------------**/

                                       /**--------------------**/
   WeldSequence[i++] = &CalPBState2;   /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCWaitUls;     /* Press Start Switches */
   WeldSequence[i++] = &SCWaitTrsST;   /*                      */
                                       /**--------------------**/


   /* aef ONLY Calculate spring rate  wait for next menu to be displayed */

//   WeldSequence[i++] = &SCDeflection;/**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCDone;        /* Calibration Comp.    */
                                       /* Release Start        */
   WeldSequence[i] = &SCEndOfList;   /* Switches             */
                                       /**--------------------**/

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i > NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   UpdateKeyMask(CALMODEMASK);
   CurrentSequence = SC;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   SetStateMachineFlag(SaveStateMachineFlag);
   ClearAbort();

   StopDataCollection();             /* Stop the weld data collection */
   StartStateMachine();              /* Start state machine      */

}


void SelectManualSCSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Manual SC state sequence.                                   */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16 i = 0;

   ResetStateMachine();                /* Turn off the state machine first */
   /* Set the current state to TopOfList */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &CalTopOfList;     /* enter the sequence of states */
   /* CalForceMenu1 wait for next menu to be displayed */
                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Set Regulator Tor    */
                                       /* Operating PSI        */
                                       /* ____________Continue */
                                       /**--------------------**/


/* wait for menu to set CalDistanceFlag wait for AEF */
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO))
      WeldSequence[i++] = &MenuSyncST; /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Cal. Distance        */
                                       /*                  Yes */
                                       /*                   No */
                                       /**--------------------**/

                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCWaitUls;     /* Use Manual           */
   WeldSequence[i++] = &SCWaitTrsST;   /* Overide on valve     */
                                       /**--------------------**/


/* aef ONLY Calculate spring rate  wait for next menu to be displayed */

//   WeldSequence[i++] = &SCDeflection;/**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCDone;        /* Calibration Comp.    */
                                       /* Release Start        */
   WeldSequence[i++] = &SCEndOfList;   /* Switches             */
                                       /**--------------------**/

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i > NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;

   UpdateKeyMask(CALMODEMASK);
   CurrentSequence = SC;
   SetStateMachineFlag(SaveStateMachineFlag);
   ClearAbort();
   StopDataCollection();             /* Stop the weld data collection */
   StartStateMachine();              /* Start state machine      */

}



