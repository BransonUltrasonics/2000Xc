/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/statedrv.cpp_v   1.29   30 Apr 2015 12:07:58   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/statedrv.cpp_v  $
 * 
 *    Rev 1.29   30 Apr 2015 12:07:58   rjamloki
 * Downspeed tune cycle is incremented in Entry function of StopDataTune state to enable save button on tuning screen
 * 
 *    Rev 1.28   16 Apr 2015 07:18:08   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.27   27 Mar 2015 11:11:22   amaurya
 * Header comment modified for StopDataTuningHD().
 * 
 *    Rev 1.26   13 Mar 2015 06:09:36   amaurya
 * Comments updated as per Branson standard for StopDataTuningHD().Updates comment for StopDataTuningHD() as per Branson standard.
 * 
 *    Rev 1.24   16 Feb 2015 01:20:00   amaurya
 * diagnostics added to trace recalibrate actuator alarm
 * 
 *    Rev 1.23   11 Feb 2015 06:30:56   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.22   21 Jan 2015 09:37:52   amaurya
 * StateMachine() changed.
 * 
 *    Rev 1.21   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.20   12 Dec 2014 05:31:36   RJamloki
 * Changes to persist tweak flow values at the end of downspeed cycle
 * 
 *    Rev 1.19   28 Nov 2014 07:41:08   rjamloki
 * ResetStateMachineDebug() changed to remove warning "unused variable".
 * 
 *    Rev 1.18   06 Oct 2014 06:46:08   AnPawar
 * Using cygos function for queue read write.
 * 
 *    Rev 1.17   03 Oct 2014 06:13:28   rjamloki
 * STATE    *CurrentState added and function renamed q_send() to SendMessage()
 * 
 *    Rev 1.16   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.15   18 Aug 2014 01:46:40   rjamloki
 * Exluded NC and EQ alarms check in ABORT case to bring the Horn up.
 * 
 *    Rev 1.14   07 Aug 2014 15:44:50   tayars
 * Added new state for the downspeed tuning. This state updates flow after each cycle.
 * 
 *    Rev 1.13   28 Jul 2014 12:53:02   rjamloki
 * SvOff changes after Horn Clamp Implementation
 * 
 *    Rev 1.12   09 Jul 2014 11:40:20   rjamloki
 * Menu4.h removed.
 * 
 *    Rev 1.11   11 Jun 2014 12:12:18   rjamloki
 * Change to start statemachine after user log in
 * 
 *    Rev 1.10   21 May 2014 10:48:12   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 03:41:44   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.8   07 May 2014 10:45:20   rjamloki
 * DigPotKey removed
 * 
 *    Rev 1.7   26 Mar 2014 12:37:12   rjamloki
 * variable PrintTrace declaration.
 * 
 *    Rev 1.6   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:44   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:52   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Statedrv                                                    */
/*                                                                          */
/* Filename:    Statedrv.c                                                  */
/*                                                                          */
/* Function Name: StateMachine                                              */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*----------------------------- DESCRIPTION -----------------------------------*/


/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define STATEDRV_UT                     


#define MAX_STATE_PASSES  25            /* Prevent infinite hang up */



/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include "qdef.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "alarms.h"
#include "keypad.h"
#include "selctkey.h"
#include "ticks.h"
#include "ready.h"
#include "weldhold.h"
#include "timer.h"
#include "snsrcalb.h"
#include "inports.h"
#include "mansensr.h"
#include "timemode.h"
#include "energy.h"
#include "peakpwr.h"
#include "collapse.h"
#include "absolute.h"
#include "grd_det.h"
#include "cont.h"
#include "util.h"
#include "digout.h"
#include "graphs.h"
#include "FrontPanelKeypadTask.h"
#include "menuhorn.h"
#include "actnvram.h"
#include "battram.h"
#include "state.h"
#include "stdio.h"
#include "WeldManagerTask.h"
#include "InputTask.h"
#include "TaskManager.h"
//#include "UndefPrintf.h"

/*------------------------- LOCAL_TYPE_DECLARATIONS ------------------------*/

#define PTSAFTERHOLD 99 /* points after hold collected */

/*-------------------------EXTERNAL DATA------------------------------------*/

extern UINT16      ColdStartDone;
extern UINT16      CycleTimer;
extern UINT16      OkToDisplayAlarms;
extern SINT32      EncoderPos;
extern SINT32      CurrentForce;
extern UINT32      CurrentAmpIn;
extern SINT32      CurrentFreqIn;
extern UINT32      CurrentPowerIn;         /*-- Value being read by 7890         --*/
extern WELD_OBJECT *MsPointer;
extern INBITS      Inp;
extern BOOLEAN     LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern UINT16      PrinterTotalCount;
extern double      PrinterIncPoints;
extern UINT16      PrinterCopyPts;
extern double      PrinterNewInc;

extern UINT8       VGALatchPSStore;  
extern BUCMENU_1200 BUCMenuRAM;
extern UINT16  AlarmFlag;
extern SINT32 DownspeedTuneCycles;
/*-------------------------- PRIVATE GLOBAL DATA -----------------------------*/

/* Data collection variables */

UINT16      NewDurCt, NewPostCt;               /* global counters                                 */
UINT16      StopPts;                           /* Don't exceeded the points limit                 */
UINT16      DataGetValue = 0;
UINT16      CopyEndPts;               /* number of records to copy before TRIGGEREDSTATE */
UINT16      PreTrigCt, DurTrigCt;     /* counters                                        */
UINT16      PostHoldCt, PostEndCt;    /* counters                                        */
UINT16      DataCount;
UINT16      SonicsCt = 0;    /* Data count at end of Sonics */

UINT16		CheckPrintFull = 0;
UINT16      Update5ms = 0;
static      SINT16   SafetyTimerId = 0;         /* Id of watchdog timer assigned    */
static      SINT16   CurrentIndex, PushedIndex; /* Index to current state pointer*/
SINT16 		*CurrentIndexPointer = &CurrentIndex;

SINT16 DebugCurrIndx;
static      SINT16   LastTrace;
static      BOOLEAN  StopAtEndOfCycleFlag;
static      BOOLEAN  GeneralAlarmStateBeforeEstop;
static      UINT16   StateMachineFlag;

SINT16      FailTrace;
SINT16      LastFailTrace;
SINT32      EnergyNeeded;
SINT32      EnergyCalc;
SINT32      AccumulatedEnergy, EnergyInJoules;
static      STATE    *CurrentPtr;               /* Current state pointer         */
STATE       *WeldSequence[NMBR_OF_STATES];      /* Current weld cycle definition */
static      SSTATES  *SSptr;                    /* Current sub state pointer     */
enum        WELDSTATES WeldState;
WELD_OBJECT DataGroup0;
WELD_OBJECT DataGroup1;
WELD_OBJECT *MsDataPtr;
UINT16      ToggleFlag = 0;   /* 0:DataGroup0  1:DataGroup1 */

static      WELD_STATE_MSG msg;
static      BOOLEAN DataSendFlag = FALSE;
enum        WELD_SEQUENCE_TYPE CurrentSequence = NONEDEFINED;
static      UINT16 PowerDownMsgSent;
UINT16      EstopHistoryFlag = FALSE;
UINT32      ConvNewInc;

#ifdef STATEDRV_UT
void   DefaultPreset(void);
#endif

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


extern void UpdateFlow();
extern void UpdateFlowHD();
extern BOOLEAN DownspeedTuneFlag, WasTweaked;

/*-------------------------------- CODE ------------------------------------*/


void SendData(enum WELDSTATES State)
{
/* mask off states are do nothing in the weld manager */
   if((State != NOP) && (State != ENDOFSONICS) &&
      (State != WAITFORULSCLEARSTATE)){
      msg.common.opcode = OP_WELDER_STATE_CHANGE;
      msg.common.source_task = WC_ISR_TASK;
      msg.state = State;
      msg.weld_samples = MsDataPtr->count;
      msg.weld_object_ptr = MsDataPtr;
      WeldManagerTask::thisPtr->WELDMNGRTaskQ.Write(0, *((WMGR_MSG_QUEUE_TYPE*) &msg), 0);
   }
}



void StopAtEndOfCycle(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set a bit which can be tested at the end of a weld   */
/*  cycle.  If this bit is set, then the state machine should be stopped.   */
/*                                                                          */
/****************************************************************************/
{
   StopAtEndOfCycleFlag = TRUE;  /* Stop at end of current cycle            */
   StopFlag = TRUE;              /* If not cycling, then stop now           */
}


void StartDataCollection(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set a bit which will be tested in the function to    */
/*  send the 1ms data to the weld manager.                                  */
/*                                                                          */
/****************************************************************************/
{
   DataSendFlag = TRUE;
}


void StopDataTuning(void)
/****************************************************************************/
/*                                                                          */
/*  This function will clear a bit which will be tested in the function to  */
/*  send the 1ms data to the weld manager. It also will update the flow     */
/*  valve during the tuning process. This state is only called during       */
/*  tuning process.                                                         */
/*                                                                          */
/****************************************************************************/
{
   DataSendFlag = FALSE;
   if(DownspeedTuneFlag == TRUE){
      if(WasTweaked == FALSE)
         UpdateFlow();
      else{
         WasTweaked = FALSE;
         LastDownSpeedValue = WeldingResults.ActualDownspeed;
      }
      ++DownspeedTuneCycles;
      CurrentPresetParameterChanged = TRUE;  //This will tell SBC to update
   }
}


void StopDataTuningHD(void)
/***************************************************************************
*                                                                         
*   Purpose:
*
*  This is a Entry code for StopDataTuneHd state which is called only for tuning cycles initiated from horn down.
*  Function gets called by SM when down speed cycle is ran. It updates the LastDownSpeed and number of cycles ran.
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
{
   DataSendFlag = FALSE;
   if(DownspeedTuneFlag == TRUE){
      if(WasTweaked == FALSE)
         UpdateFlowHD();
      else{
         WasTweaked = FALSE;
         LastDownSpeedValue = WeldingResults.ActualDownspeed;
      }
      ++DownspeedTuneCycles;
      CurrentPresetParameterChanged = TRUE;  //This will tell SBC to update
   }
}

void StopDataCollection(void)
/****************************************************************************/
/*                                                                          */
/*  This function will clear a bit which will be tested in the function to  */
/*  send the 1ms data to the weld manager.                                  */
/*                                                                          */
/****************************************************************************/
{
   DataSendFlag = FALSE;
}

void StateMachine(void)
/****************************************************************************/
/*                                                                          */
/* See notes (state.doc) for overview of how this function works.  The      */
/* while loop will continue until EndFlag is set TRUE.  This can happen by  */
/* one of several ways: 1) the action END was executed, 2) the action JUMP  */
/* was executed, 3) the action ALJUMP was executed or 4) more sub states    */
/* then MAX_STATE_PASSES have been tested in a row (as counted by the       */
/* variable SafetyNet).                                                     */
/*                                                                          */
/* NOTES:Instead of safety net approach consider using hardware (PIT)       */
/*       timer on the 332 (122 us resolution).  It would be retriggered     */
/*       before each call to the state machine.  An interrupt would occur   */
/*       if too much time elapsed before each retriggering.  The interrupt  */
/*       handler would record an error (for later viewing) and then set     */
/*       EndFlag to TRUE (except EndFlag is local!?).                       */
/*                                                                          */
/*       If ALJUMP is the cause of leaving one state and entering the       */
/*       next, the Entry Code for the new state WILL NOT be executed.       */
/*       This means in an abort situation, the next state code will not     */
/*       be run, i.e. hold time will not start if the weld was aborted.     */
/*                                                                          */
/*       If ABORT is the cause of leaving one state and entering the        */
/*       next, the Entry Code for the new state and the exit code for the   */
/*       old state WILL NOT be executed.  This means in an abort situation, */
/*       the next state code will not be run, i.e. hold time will not start */
/*       if the weld was aborted.  Further, no state entry code will be     */
/*       executed until the AbortFlag is reset.  All exit code will con-    */
/*       tinue to be executed.                                              */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN EndFlag = FALSE;
   BOOLEAN TestValue;
   SINT16  Cond;
   SINT16  SafetyNet = 0;
   CONFIGSETUP  *SetupPtr;
   STATE    *CurrentState;
   SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;


/*----------  The next thing to do is check for Emergency Stop  ----------*/

   /* Don't allow ESTOP while powering up, powering down, or adjusting digital pot */
   if((CurrentSequence != POWERDOWN) && (CurrentSequence != POWERUP)){
      if (Inp.Estop == TRUE) {
         if (EstopHistoryFlag == FALSE) {/* Did we already deal with Estop?    */
            SendData(EMERGENCYSTOP);
            AbortFlag = TRUE;
            GeneralAlarmStateBeforeEstop = CheckGeneralAlarmFlag();

            /* Inc alarm counter if this is first alarm on cycle */
            /* attempt or if cycle attempt not in progress now. */

            if (!GeneralAlarmStateBeforeEstop || OkToDisplayAlarms){
               CurrentSetup.GenAlarmCount++;
               SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount;  /* Update FRAM */
            }
            AlarmFlag = TRUE;
            SetGeneralAlarm();
            ClearSAS();                        /* Reset Sonics Active signal            */
            ClearReady();
            StopDataCollection();              /* Stop 1ms data while in estop */
            if(ClampOnAlarm == TRUE){
            	PushIndex();
            	ResetStateMachine();               /* Stop & reset weld cycle      */

         	 	PopIndex();
			 	
            }
            else
            	ResetStateMachine();               /* Stop & reset weld cycle      */
            SVOff();                           /* Release SV, send horn home   */
            PSIdle();                          /* Turn off the sonics          */
            EstopHistoryFlag = TRUE;
         }
      }
      else {
         if (EstopHistoryFlag == TRUE) { /* Did we already deal with no ESTOP? */
            SendData(EMERGENCYSTOPRESET);
            EstopHistoryFlag = FALSE;
            InitTimer();
            if (GeneralAlarmStateBeforeEstop == FALSE) {
               ClearGeneralAlarm();
            }
         }
      }
   }
/*----------  Check to see if a power down has been requested  ----------*/

   if (Inp.PwrOff == TRUE) {
      if (EstopHistoryFlag == TRUE) { /* Did we already deal with no ESTOP? */
         PowerDownSystem();
      }
      else if (PowerDownMsgSent == FALSE) {
         PowerDownMsgSent = TRUE;       /* Make sure message sent only once */
         if(CurrentSequence != POWERUP){
            AbortFlag = FALSE; /* If not clear, won't run EPowerDown() */
            SelectPowerDownSequence();
         }
         else{
            PowerDownSystem();
         }
      }
   }

/*----------  This section gets executed every ms  ---------*/

   TestActClr();         /* Check actuator clear so multiple individual */
                         /* states dont have to do it.  This ensures it */
                         /* work even in abort situations.              */ 



/*----------  The next thing to do is collect the 1ms data  ----------*/
    if (StateMachineFlag == TRUE) {
      if(CollectEnergyFlag == TRUE){
         AccumulatedEnergy += CurrentPowerIn;
         if (EnergyCalc != 0)
            EnergyInJoules = (AccumulatedEnergy / EnergyCalc);
      }

      if(Update5ms++ >= 4){
         Update5ms = 0;
      }


   
/**---------------------------------------------------------**
 ** This block of instruction involves accumulating the 400 **
 ** points we need for the printing of the graphs.  It is   **
 ** executed if it's ok to collect data. This decision is   **
 ** based on DataSendFlag being TRUE and the data increment.**
 ** The 400 points are stored at DataGroup0 and then toggled**
 ** to DataGroup1. After the 400 points have been collected **
 ** Graph points are generated if PRINT NOW is pressed or a **
 ** print selection has been made.                          **
 **---------------------------------------------------------**/


      /*-- Convert float to long --*/
      ConvNewInc = (UINT32)MsDataPtr->NewInc;
      
      /*-- Stop collecting data if        --*/
      /*-- there is a collection overflow --*/

      if(ConvNewInc == 0)
         DataSendFlag = FALSE;

      /*-- First time in HOLDTIMESTATE grab the count --*/
      if((CurrentPtr->state == HOLDTIMESTATE) && (SonicsCt == 0)){
         MsDataPtr->EndOfSonicCt = DataCount;
         MsDataPtr->PointsUpTillHold = DataCount;
         SonicsCt++;
      }

      /*-- Refresh count until end of HOLDTIMESTATE --*/
      if(CurrentPtr->state <= HOLDTIMESTATE){
        MsDataPtr->PointsUpTillHold = DataCount;
      }


      if(CurrentPtr->state == WELDTIMESTATE){
        MsDataPtr->DontPrintGraph = FALSE;       /* TRS not reached as yet  */
      }
   
   
      if(DataSendFlag == TRUE){
         if((DataGetValue++ % ConvNewInc) == 0){

           MsDataPtr->NewInc += MsDataPtr->IncrementPts;

           switch (CurrentPtr->state)
           {

               case DOWNSTROKESTATE:
                    PreTrigState();
                    break;

               case WAITFORPTSSTATE:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE1:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE2:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE3:
                    PreTrigState();
                    break;

               case EXTTRIGDELAYSTATE:
                    PreTrigState();
                    break;

               case TRIGGERDELAYSTATE:
                    DurTrigWeldHoldState();
                    break;

               case WELDTIMESTATE:
               case WELDTIME2STATE:
                    DurTrigWeldHoldState();
                    break;

               case ENDOFSONICS:
                    DurTrigWeldHoldState();
                    MsDataPtr->EndOfSonicCt = MsDataPtr->count;
                    break;

               case HOLDTIMESTATE:
                    DurTrigWeldHoldState();
                    break;

               case AFTERBURSTDELAYSTATE:
                    PostHoldtimeState();
                    break;

               case AFTERBURSTTIMESTATE:
                    PostHoldtimeState();
                    break;

               case UPSTROKESTATE:
                    PostHoldtimeState();
                    break;

               case WAITFORULSMADESTATE:
                    PostHoldtimeState();
                    break;

               case WAITFORCONTINUE:
                    PostHoldtimeState();
                    break;

               case SEEKSTATE:
                    PostHoldtimeState();
                    break;

               case RAMPSONICSSTATE:
                    PostHoldtimeState();
                    break;

                 default:
                    break;
              }
         }

      }
/*----------  Now finally run through the state cycles  ----------*/
      CurrentPtr = WeldSequence[CurrentIndex];
      SSptr = CurrentPtr->ptr;                 /* Get sub state pointer    */
      CurrentPtr->PassPtr();                   /* Execute this pass code   */
      FailFlag = FALSE;
      while (EndFlag == FALSE) {

         TestValue = *(SSptr->ValuePtr);
         if (TestValue == FALSE) {             /* Test the value           */
            Cond = SSptr->False;               /* Was FALSE, use FALSE cmd */
         }
         else {
            Cond = SSptr->True;                /* Was TRUE, use TRUE cmd   */
         }

         switch (Cond) {
   
            case NORM:
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               break;
   
            case PUSH:
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               PushedIndex = CurrentIndex;
               break;
   
            case FAIL:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               FailFlag = TRUE;
               LastFailTrace = FailTrace; 
               FailTrace = SSptr->Trace; 
               break;
   
            case ABORT:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
			   	   SSptr++;
//               AbortFlag = TRUE;

			   LastTrace = SSptr->Trace;
			   CurrentState = WeldSequence[CurrentIndex];// Added to check if the state from where the
			   // ABORT is initiated is after Trigger or not.
			   CurrentIndex++;                         /* Increment index   */
			   CurrentPtr = WeldSequence[CurrentIndex];
			   if (CurrentPtr->state != NOP)
				  WeldState = CurrentPtr->state;       /* Update state variable  */
			   if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
				  StopTimer(SafetyTimerId);            /* Stop last timer*/
			   }
			   if (*CurrentPtr->STimer != 0) {
				  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
			   }
			   else SafetyTimerId = 0;

			   if((CurrentSetup.HornClamp == TRUE) && (CurrentSequence == WELD)
				 && (CurrentState->state >= TRIGGEREDSTATE)){
				   if ((WeldingResults.OverloadAlarms == 0)
					&& (WeldingResults.CycleModifiedAlarms == 0)
					&& (WeldingResults.CalibrateAlarms == 0) && (WeldingResults.SuspectBitResult == 0)
					&& (WeldingResults.RejectBitResult == 0) && (WeldingResults.Warnings == 0))
					SVOff();  /* Bring up horn in all abort situations */
			   }
			   else
				   SVOff();

			   ClearSAS();         /* Reset Sonics Active signal            */
			   PSIdle();           /* Stop sonics                           */
			   ResetStateMachineIndex();
			   CoolValOff();       /* Turn off cooling valve (08-30-00)     */
			   EndFlag = TRUE;

/*---- End of new abort code ----*/

/*---  If we aborted, lets assume something went wrong somewhere, so     ---*/
/*---  lets reset everything and reselect the weld sequence to recover.  ---*/

			   TrigSwActv();                  /* safety circuit input       */
			   if ( (GetCurrentSequenceType() == WELD) &&
					(HornDownFlag == FALSE) ) {
				   SelectWeldSequence();      /* Try redoing weld sequence  */
				   StartStateMachine();
			   }
			   break;
   
            case ALNORM:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               break;
   
            case JUMP:
               CurrentPtr->NextPtr();                  /* Execute exit code */
               LastTrace = SSptr->Trace;
               CurrentIndex++;                         /* Increment index   */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
//                  if (SafetyTimerId == FAILED1)
//                     LogError(TIMERFAILED1);
//                  else if (SafetyTimerId == FAILED2)
//                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;
   
            case ALJUMPNORM:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               CurrentPtr->AlarmPtr();                 /* Execute exit code   */
               CurrentPtr->NextPtr();                  /* Execute exit code */
               LastTrace = SSptr->Trace; 
               CurrentIndex++;                         /* Increment index   */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
//                  if (SafetyTimerId == FAILED1)
//                     LogError(TIMERFAILED1);
//                  else if (SafetyTimerId == FAILED2)
//                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;

            case POP:
               CurrentPtr->AlarmPtr();                /* Execute alarm code */
               LastTrace = SSptr->Trace; 
               CurrentIndex = PushedIndex;            /* Reset index        */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
//                  if (SafetyTimerId == FAILED1)
//                     LogError(TIMERFAILED1);
//                  else if (SafetyTimerId == FAILED2)
//                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               break;
   
            case ALJUMP:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               CurrentPtr->AlarmPtr();                 /* Execute exit code   */
               LastTrace = SSptr->Trace; 
               CurrentIndex++;                         /* Increment index     */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 2);
//                  if (SafetyTimerId == FAILED1)
//                     LogError(TIMERFAILED1);
//                  else if (SafetyTimerId == FAILED2)
//                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;
   
            case END:

               EndFlag = TRUE;
               break;

            default:
               EndFlag = TRUE;
               break;
         }
       }
   }
   DebugCurrIndx = CurrentIndex;
}



void PushIndex(void)
{
   PushedIndex = CurrentIndex;
}



void PopIndex(void)
{
   CurrentIndex = PushedIndex;
}



void SetIndex(SINT16 Index)
{
   CurrentIndex = Index;
}


#ifdef SM_DEBUG
void StartStateMachineDebug(int x, const char * file, const char * fun, int line)
#else
void StartStateMachine(void)
#endif
{
#ifdef SM_DEBUG
   printf("\n **** StartSm from %s %s %d \n***** \n", file, fun, line);
   x = 0;
#endif
    if(UserLoggedIn == TRUE)
	{
		StateMachineFlag = TRUE;
		StopAtEndOfCycleFlag = FALSE;
		StopFlag = FALSE;
	}
}


#ifdef SM_DEBUG
void StopStateMachineDebug(int x, const char * file, const char * fun, int line)
#else
  void StopStateMachine()
#endif
{
#ifdef SM_DEBUG
   printf("\n **** stopsm from %s %s %d ****\n", file, fun, line);
   x = 0;
#endif
   StateMachineFlag = FALSE;
   ClearReady();  /* No state machine = not ready! */
}



UINT16 CheckStateMachine(void)
{
   return(StateMachineFlag);
}


#ifdef SM_DEBUG
   void  ResetStateMachineDebug(int x , const char *file, const char * fun, int line)
#else
   void ResetStateMachine()
#endif
{
#ifdef SM_DEBUG
      printf("\n **** reset sm from %s %s %d \n*****\n", file, fun, line);
	  x = 0;
#endif
   if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
      StopTimer(SafetyTimerId);            /* Stop last timer*/
   }
   CurrentPtr = 0;
   CurrentIndex = 0;
   StateMachineFlag = FALSE;
}



UINT16 GetStateMachineFlag(void)
{
   return(StateMachineFlag);
}


#ifdef SM_DEBUG
UINT16 SetStateMachineFlagDebug(UINT16 Flag, const char *file, const char * fun, int line)
#else
UINT16 SetStateMachineFlag(UINT16 Flag)
#endif
{
   UINT16 RetVal;
#ifdef SM_DEBUG
   printf("\n ***** SetSm from %s %s %d newflag %d currf %d \n ****\n", file, fun, line, Flag, StateMachineFlag);
#endif
   RetVal = StateMachineFlag;          /* Get old value before we change it */
   StateMachineFlag = Flag;            /* Set to new passed value           */
   return(RetVal);                     /* Return original value             */
}


void ResetStateMachineIndex(void)
{
   CurrentIndex = 0;
}



void SetCurrentSequenceType(enum WELD_SEQUENCE_TYPE Type)
{
#ifdef SM_DEBUG
	 printf("\n **** CurrentSequence %d func %s \n****\n", Type, __FUNCTION__);
#endif	 
   CurrentSequence = Type;
}



enum WELD_SEQUENCE_TYPE GetCurrentSequenceType(void)
{
   return(CurrentSequence);
}



void ResetCycleTimer(void)
/***************************************************************************/
/*                                                                         */
/*  This function will clear the cycle timer.  It should be called from    */
/*  the routine which first becomes aware that the upper limit switch is   */
/*  cleared and the cycle is about to begin.                               */
/*                                                                         */
/*  Whatever routine calls this better be from within the 1 ms interrupt.  */
/*                                                                         */
/***************************************************************************/
{
   CycleTimer = 0;
}



void InitWeldSequencer(void)
/***************************************************************************/
/*                                                                         */
/* This is where all variables relating to the weld sequencer will be      */
/* initialized.  This function must be called at least once after power    */
/* and whenever a 'warm' reset is needed.                                  */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
{
   UINT16 x;
   UINT16 i = 2;

   TimeOff = 0;                        /* Variable used when no timeout    */
   CurrentIndex = 0;                   /* Start at top of list             */

/* Set all indexes to NOP except first and last */

   for (x = 1; x < NMBR_OF_STATES - 1; x++) {
      WeldSequence[x] = &NopList;
   }
   WeldSequence[0] = &TopOfList;
   WeldSequence[x] = &EndOfList;
   StateMachineFlag = FALSE;
   StopDataCollection();
   CurrentSequence = POWERUP;
/*-----  Insert Power On Sequence Here  -----*/

   WeldSequence[i++] = &PowerOn1;
   WeldSequence[i++] = &PowerOn2;
   WeldSequence[i++] = &PowerOn3;
   WeldSequence[i++] = &PowerOn4;
   WeldSequence[i++] = &PowerOn5;
   WeldSequence[i++] = &PowerOn6;

   CycleTimer = 0;
   MsDataPtr = &DataGroup0;
   ToggleFlag = 0;

   InitTimer();                         /* Initialize state machine timers  */
   DataSendFlag = FALSE;                /* Start the 1ms data collection    */
   PowerDownMsgSent = FALSE;

#ifdef STATEDRV_UT
   DefaultPreset();          /* Define a default preset (just for Bob & Guy) */
#endif

}



void SelectWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This function will call the proper function to set up a weld sequence   */
/* based on the selected weld mode.                                        */
/*                                                                         */
/* It will also do such trivial things as set up the PSWattage variable so */
/* energy can be calculated.                                               */
/*                                                                         */
/***************************************************************************/
{
   ResetStateMachine();                /* Turn off the state machine first */
   CurrentIndex = 0;
   if(CurrentSetup.PSWatt > 0)
      EnergyCalc = (100000 / CurrentSetup.PSWatt);
   else
   {
      EnergyCalc = (100000 / 2500);
   }

   if (CurrentSetup.HandHeld == FALSE) {
      switch (RunningPreset.WeldMode) {
         case TIMEMODE:
            SelectTimeWeldSequence();
            break;
   
         case ENERGYMODE:
            SelectEnergyWeldSequence();
/* Calculate here "energy units" needed */
            if (RunningPreset.WeldEnergy >= 2000) { /* Prevent overflow, lose a little accuracy */
               EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;  /* Convert to energy units   */
            }
            else {      /* Overflow not a problem here, keep accuracy instead  */
               EnergyNeeded = RunningPreset.WeldEnergy * 100000; /* 1/10's of millejoules */
               EnergyNeeded /= CurrentSetup.PSWatt;    /* Convert to energy units   */
            }
            break;
   
         case PKPOWERMODE:
            SelectPeakPowerWeldSequence();
            break;
   
         case COLLAPSEMODE:
            SelectCollapseWeldSequence();
            break;
   
         case ABSOLUTEMODE:
            SelectAbsoluteWeldSequence();
            break;
   
         case GRDDETECTMODE:
            SelectGroundDetectWeldSequence();
            break;
   
         case CONTINUOUSMODE:
            SelectContWeldSequence();
            break;
   
         default:
            RunningPreset.WeldMode = TIMEMODE;
            SelectTimeWeldSequence();
            break;
      }
   }
   else {              /* Handheld is On */
      switch (RunningPreset.WeldMode) {
         case TIMEMODE:
            SelectTimeWeldSequenceHH();
            break;
   
         case ENERGYMODE:
            SelectEnergyWeldSequenceHH();
/* Calculate here "energy units" needed */
            if (RunningPreset.WeldEnergy >= 2000) {    /* Prevent overflow, lose a little accuracy */
               EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;  /* Convert to energy units   */
            }
            else {      /* Overflow not a problem here, keep accuracy instead  */
               EnergyNeeded = RunningPreset.WeldEnergy * 100000; /* 1/10's of millejoules */
               EnergyNeeded /= CurrentSetup.PSWatt;    /* Convert to energy units   */
            }
            break;
   
         case PKPOWERMODE:
            SelectPeakPowerWeldSequenceHH();
            break;
   
         case GRDDETECTMODE:
            SelectGroundDetectWeldSequenceHH();
            break;
   
         case COLLAPSEMODE:
//            SelectCollapseWeldSequenceHH();    /* Maybe sometime in the distant future */
            break;

         case ABSOLUTEMODE:
//            SelectAbsoluteWeldSequenceHH();    /* Maybe sometime in the distant future */
            break;

         default:
            RunningPreset.WeldMode = TIMEMODE;
            SelectTimeWeldSequenceHH();
            break;
      }
   }
   StopFlag = FALSE;
   UpdateKeyMask(WELDMODEMASK);
}




void SelectTestSequence(void)
/****************************************************************************/
/*                                                                          */
/* This is the Test mode state sequence.                                    */
/*                                                                          */
/****************************************************************************/
{
   UINT16 i = 0;

   PSReset();                          /* Reset the power supply            */
   ResetStateMachine();                /* Turn off the state machine first  */
   StopDataCollection();               /* Stop 1ms data while in test mode  */
   CurrentIndex = 0;
   WeldSequence[i++] = &TopOfList;       
   WeldSequence[i++] = &PreReadyTestSt;
   WeldSequence[i++] = &ReadyTestSt;
   WeldSequence[i++] = &TestST;       
   WeldSequence[i++] = &NopList;
   WeldSequence[i++] = &EndOfList;
   CurrentSequence = TESTMODE;
   UpdateKeyMask(TESTMODEMASK);

   LatchPSRun = LatchPSSeek = LatchPSClear = LatchPSStore = FALSE;
   VGALatchPSStore = FALSE;
   Inp.PSStore = FALSE;           /* Clear here, set by ISR */
   StartStateMachine();           /* Start the state machine here */
}



void Restart(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will reset the current index to the start of */
/*  the state list.                                                        */
/*                                                                         */
/***************************************************************************/
{
   CurrentIndex = 0;   /* Reset all pointers to the top of the state list. */
}



void Nothing(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be the most used of all functions.  It  */
/*  will be the MANAGER function (i.e. it will do nothing).                */
/*                                                                         */
/*  This would be a good place to put debugging stuff, because it will get */
/*  called at somewhat regular intervals.                                  */
/*                                                                         */
/***************************************************************************/
{
}



void SelectPowerDownSequence(void)
/****************************************************************************/
/*                                                                          */
/* This is the sequence that will be run when the power is about to go down.*/
/*                                                                          */
/****************************************************************************/
{
   UINT16 i = 0;

   ResetStateMachine();                /* Turn off the state machine first  */
   StopDataCollection();               /* Stop 1ms data while in test mode  */
   CurrentIndex = 0;
   WeldSequence[i++] = &TopOfList;       
   WeldSequence[i++] = &PwrDown;
   WeldSequence[i++] = &EndOfList;
   CurrentSequence = POWERDOWN;
   StartStateMachine();                /* Start the state machine here      */
}



/**---------------------------------------------------------------------**
 ** This function calculates the increment of the  1msdata information. **
 ** That is, if weldtime is 1 sec and holdtime is 2 sec and the extra   **
 ** .1 sec before triggerstate and  .1 sec after holdstate accumulates  **
 ** to 2.2 sec (or 2.2 * 1000 = 2200 pts). Only 400 pts is needed to    **
 ** configure graph so to utilize the entire 2200 pts we find the       **
 ** increment so we can discard unneeded data. NOTE: the increment is   **
 ** strictly based on the weldtime and holdtime. As these values vary   **
 ** so does the increment. If TriggerDelayFlag is TRUE, TriggerDelay    **
 ** value is also added to the equation.                                ** 
 ** This function also initialize the mSObject struct to zeroes....     **
 **---------------------------------------------------------------------**/
void GetPtsIncrement(void)
{
   UINT16 AddedTimeValue = 0;

   /*-- reinitialize values to 0 when restart --*/
   MsDataPtr->IncrementPts = 1.0;
   MsDataPtr->TotalPts = 1; // Changed to 1 because 1ms_data.c divides this variable.
   StopPts = 0;
   MsDataPtr->CopyPts = 1;  
   CopyEndPts = 0;

/* See if energy braking is on, if so, then add smaller of BUC menu time */
/* or RunningPreset.EBTime                                               */

   if (CurrentPreset.EnergyBraking == TRUE) {
      if (BUCMenuRAM.EnergyBrakingTime < RunningPreset.EBTime)
         AddedTimeValue = BUCMenuRAM.EnergyBrakingTime;
      else
         AddedTimeValue = RunningPreset.EBTime;
   }

   if (CurrentSetup.HandHeld == TRUE)
      AddedTimeValue += 100;  /* 100 ms after hold only  */
   else
      AddedTimeValue += 200;  /* 100 ms before trigger and 100 ms after hold */
      
    /*-- TIMEMODE and manual scale active --*/
   if((RunningPreset.WeldMode == TIMEMODE) && ((RunningPreset.AutoScaleFlag & BIT0) == FALSE)){
      MsDataPtr->TotalPts = (UINT32)(RunningPreset.XScaleTime + PRETRIGMAXLIM);
     
       /* If manual scale is active therefore,  set flag */
      MsDataPtr->PrintBottomFlags |= MANUALSCALEFLAG;
   }

   /* TIMEMODE and manual scale inactive*/
   else
   if((RunningPreset.WeldMode == TIMEMODE) && ((RunningPreset.AutoScaleFlag & BIT0) == TRUE)){

      /* If manual scale is inactive the clear flag if not already cleared */
      MsDataPtr->PrintBottomFlags &= (~MANUALSCALEFLAG);

      /*-- Check if Time is extended due to Energy Compensation --*/
      /*-- if so, multiply the weldtime by 1.5 --*/
      if((RunningPreset.ControlLimitsFlag ==  TRUE) && (RunningPreset.EnergyCompFlag == TRUE)){

         MsDataPtr->TotalPts = (UINT32)(RunningPreset.WeldTime * 1.5);
         if(MsDataPtr->TotalPts > WELDTIMEMAX)  /*-- WELDTIMEMAX = 30000 --*/
             MsDataPtr->TotalPts = WELDTIMEMAX;
         
         /*-- Add 100ms before trigger and 100ms after hold --*/
         MsDataPtr->TotalPts += AddedTimeValue;
      }
      /*-- If time is NOT extended due to Energy Compensation --*/
      else
         MsDataPtr->TotalPts = (UINT32)(RunningPreset.WeldTime + AddedTimeValue);    /* 200 = 100ms before trigger */
                                                                                     /*       100ms after hold     */    
      /* Check if HoldTime is Off */
      if((RunningPreset.HoldTimeFlag & BIT0) == FALSE){
         MsDataPtr->TotalPts += (UINT32)RunningPreset.HoldTime;
      }
      
      /* Check if Trigger Delay is on */
      if((RunningPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == FALSE){
         MsDataPtr->TotalPts += (UINT32)RunningPreset.TriggerDelay;
      }
   }
   else{
     MsDataPtr->TotalPts = (UINT32)(RunningPreset.XScaleTime + PRETRIGMAXLIM);  /* ALL OTHER MODES no HH*/
     
     /* If manual scale is active therefore,  set flag */
     MsDataPtr->PrintBottomFlags |= MANUALSCALEFLAG;

   }
     
   if(MsDataPtr->TotalPts < (UINT32)MAX_WELD_SAMPLES)
      MsDataPtr->TotalPts = (UINT32)MAX_WELD_SAMPLES;

   if(MsDataPtr->TotalPts > (UINT32)COMPRESS){
     MsDataPtr->IncrementPts = ((double)MsDataPtr->TotalPts /(UINT32)COMPRESS);
   }
   else
     MsDataPtr->IncrementPts = 1;

   
   /*-- Number of records to select for last 100ms before TRIGGEREDSTATE --*/
   /*-- and first 100ms after HOLDTIMESTATE  --*/

   MsDataPtr->CopyPts = (UINT16)(PRETRIGMAXLIM / MsDataPtr->IncrementPts);
   
   if (MsDataPtr->CopyPts > PRETRIGMAXLIM) MsDataPtr->CopyPts = PRETRIGMAXLIM;
   else if (MsDataPtr->CopyPts < PRETRIGMINLIM) MsDataPtr->CopyPts = PRETRIGMINLIM;

/* If HandHeld is selected then collect the minimum number of useless pretrig points */

   if (CurrentSetup.HandHeld == TRUE) MsDataPtr->CopyPts = PRETRIGMINLIM;

   StopPts = MAX_WELD_SAMPLES - MsDataPtr->CopyPts;
   MsDataPtr->NewInc = MsDataPtr->IncrementPts;
   ConvNewInc = (UINT32)MsDataPtr->NewInc;
   
   PrinterTotalCount = MsDataPtr->TotalPts;
   PrinterIncPoints = MsDataPtr->IncrementPts;
   PrinterCopyPts = MsDataPtr->CopyPts;
   PrinterNewInc = MsDataPtr->NewInc;
   ColdStartDone = FALSE;          /*--  Reset to FALSE: cold start not done --*/ 
}
    




/**------------------------------------------------------------**
 ** This function also initializes all the key data collection **
 ** variables at the Palm button state                         **
 **------------------------------------------------------------**/
void Init1msPts(void)
{

   /* TRUE: function is used once during weld cycle */
   /* reinitialize values to 0 when restart */
   
   NewDurCt     = 0;
   NewPostCt    = 0; 
   PreTrigCt    = 0;
   DurTrigCt    = 0;
   PostHoldCt   = 0;
   PostEndCt    = 0; 
   DataCount    = 0;
   DataGetValue = 0;
   MsDataPtr->BufferWrapFlag = FALSE;
   MsDataPtr->NewPreCt = 0;
   MsDataPtr->count = 0;
   MsDataPtr->NewInc = MsDataPtr->IncrementPts;
   ConvNewInc   = (UINT32)MsDataPtr->NewInc;
   SonicsCt     = 0;                    
   MsDataPtr->EndOfSonicCt = 0;
}
 

/**-------------------------------------------------------**
 ** Function will accummulate up to 100ms of data before  **
 ** the TRIGGEREDSTATE and copy each sample to the array  **
 ** structures. If (CopyPts) samples is copied to the     **
 ** buffer is reset to form a circular buffer.If a        **
 ** wraparound occurs BufferWrapFlag will be set to TRUE  **
 ** and NewPreCt will be the number of records stored     **
 ** NewPreCt is the index which keep track of the position**
 ** one spot beyond of the last point written.            **
 **-------------------------------------------------------**/
void PreTrigState(void)
{
      MsDataPtr->Power[MsDataPtr->NewPreCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[MsDataPtr->NewPreCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[MsDataPtr->NewPreCt]  = CurrentFreqIn;
      MsDataPtr->Force[MsDataPtr->NewPreCt] = CurrentForce;
      MsDataPtr->Dist[MsDataPtr->NewPreCt]  = EncoderPos;
      MsDataPtr->NewPreCt++;
        
      if(MsDataPtr->NewPreCt >= MsDataPtr->CopyPts){   
        MsDataPtr->NewPreCt = 0;
        MsDataPtr->BufferWrapFlag = TRUE;
      }
  
      /*-- Always start trigger at CopyPts --*/
      DataCount  = MsDataPtr->CopyPts;
      NewDurCt   = MsDataPtr->CopyPts;
      MsDataPtr->count = DataCount;
      MsDataPtr->DontPrintGraph = TRUE;       /* TRS not reached as yet  */
}



/**-----------------------------------------------------**
 ** This function will accumulate  up to 400 points     **
 ** based on the TRIGGEREDSTATE thru the FINALDATASTATE.**
 **-----------------------------------------------------**/
void DurTrigWeldHoldState(void)
{

  if(NewDurCt < MAX_WELD_SAMPLES){
   
      MsDataPtr->Power[NewDurCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[NewDurCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[NewDurCt]  = CurrentFreqIn;
      MsDataPtr->Force[NewDurCt] = CurrentForce;
      MsDataPtr->Dist[NewDurCt]  = EncoderPos;
      NewDurCt++;
      NewPostCt = NewDurCt;
      DataCount = NewDurCt;
      MsDataPtr->count = DataCount;
  }

}



/**-----------------------------------------------**
 ** This function will accumulate the 100ms data  **
 ** after the HOLDTIMESTATE.                      **
 **-----------------------------------------------**/
void PostHoldtimeState(void)
{

  if(NewPostCt < MAX_WELD_SAMPLES && (PostEndCt <= MsDataPtr->CopyPts )){
  
      MsDataPtr->Power[NewPostCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[NewPostCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[NewPostCt]  = CurrentFreqIn;
      MsDataPtr->Force[NewPostCt] = CurrentForce;
      MsDataPtr->Dist[NewPostCt]  = 0;
      NewPostCt++;
      PostEndCt++;

      DataCount = NewPostCt;
      MsDataPtr->count = DataCount;
  }
  if(PostEndCt > PTSAFTERHOLD)
     StopDataCollection();              /* Stop 1ms data after hold + 100ms */

}





        
/**------------------------------------------------**
 ** This module will toggle betweem DataGroup0 and **
 ** DataGroup1. once FINALDATASTATE is reached.    **
 ** Before toggle occurs Printer pointer(MsPointer)**
 ** is first updated.                              **
 ** IMPORTANT NOTE: If a graph is printing toggle  **
 ** will not be allowed and weld will be shut off  **
 ** until the printer buffer is almost empty.      **
 **------------------------------------------------**/
void ChangeDataStorage(void)
{

   /*Update pointer before change*/
   MsPointer = MsDataPtr;

   switch (ToggleFlag) {


      case 0:
         MsDataPtr = &DataGroup1;      /* Set pointer to group 1            */
         ToggleFlag = 1;
         break;
    
      case 1:
         MsDataPtr = &DataGroup0;      /* Set pointer to group 2            */
         ToggleFlag = 0;
         break;
 
      default:
         MsDataPtr = &DataGroup0;
         ToggleFlag = 0;
         break;
   }
}


/**-----------------------------------------------------------**
 ** This function initializes key member variables from our 2 **
 ** data storage area to  zeros and  points the collection    **
 ** pointer MsDataPtr to DataGroup0. Infact it also points    **
 ** the MsPointer to DataGroup1. However is a recall preset   **
 ** is executed while printing, data will not be cleared out. **
 **-----------------------------------------------------------**/
void ClearDataStorage(void)
{
  
  /*-- If not printing or printing done clear all data storage --*/
  if(CheckPrintFull == 0){
     MsDataPtr = &DataGroup0;
     MsDataPtr->TotalPts = 0;
     MsDataPtr->IncrementPts = 0;
     MsDataPtr->CopyPts = 0;
     MsDataPtr->NewInc = 0;
     MsDataPtr->NewPreCt = 0;
     MsDataPtr->PrintBottomFlags = 0;
     MsDataPtr->BufferWrapFlag = FALSE;                    
     MsDataPtr->count = 0;

     MsPointer = &DataGroup1;
     MsPointer->TotalPts = 0;
     MsPointer->IncrementPts = 0;
     MsPointer->CopyPts= 0;
     MsPointer->NewPreCt= 0;
     MsPointer->NewInc = 0;
     MsPointer->PrintBottomFlags = 0;
     MsPointer->BufferWrapFlag = FALSE;                    
     MsPointer->count = 0;
     MsPointer->DontPrintGraph = TRUE;
  }

    PrinterTotalCount = 0;
    PrinterIncPoints = 0;
    PrinterCopyPts = 0;
    PrinterNewInc = 0;
 
}
