/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ready.cpp_v   1.45   Oct 10 2017 13:16:26   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ready.cpp_v  $
 * 
 *    Rev 1.45   Oct 10 2017 13:16:26   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.44   27 Nov 2015 13:27:22   RJamloki
 * Apply ext tooling or part clamp output when lost PB's don't turn off bug fix
 * 
 *    Rev 1.43   16 Apr 2015 07:18:04   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.42   09 Apr 2015 05:25:20   RJamloki
 * AlarmEQ25 flag is renamed to PressureStepEnable
 * 
 *    Rev 1.41   08 Apr 2015 13:45:36   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.40   30 Mar 2015 05:48:26   rjamloki
 * Dooropen removed
 * 
 *    Rev 1.39   16 Mar 2015 06:21:24   rjamloki
 * Added check to disable pressure inaccuracy check during calibration in Test ready function.
 * 
 *    Rev 1.38   16 Feb 2015 02:30:26   amaurya
 * ommented  PBReleaseOn() function for recalibrate actuator alarm testing
 * 
 *    Rev 1.37   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.36   30 Jan 2015 08:10:46   amaurya
 * ClearFinalResults() changed.
 * 
 *    Rev 1.35   08 Jan 2015 02:44:24   AnPawar
 * TestReady function changed to update the flow and pressure live
 * 
 *    Rev 1.34   12 Dec 2014 05:31:18   RJamloki
 * Disabled PartPresent and clamp active alarms for downspeed tune cycles
 * 
 *    Rev 1.33   11 Dec 2014 08:36:48   AnPawar
 * changes for part present and clamp alarm.
 * 
 *    Rev 1.32   28 Nov 2014 07:39:46   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.31   17 Nov 2014 10:04:24   RJamloki
 * Checking Pressure to be within +=10 psi of setvalue in PB state.
 * 
 *    Rev 1.30   14 Nov 2014 05:28:22   rjamloki
 * PASSES_BEFORE_REGFAILURE macro added.
 * 
 *    Rev 1.29   10 Nov 2014 04:56:42   AnPawar
 * PreReadyJump() , PreReadyAlJump() ,SendFData() changed.TestRegulatorPressure function added.
 * 
 *    Rev 1.28   20 Oct 2014 06:23:18   AnPawar
 * TriggerBeep() function changed 
 * 
 *    Rev 1.27   06 Oct 2014 06:43:24   AnPawar
 * TestReady() function changed.removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.26   03 Oct 2014 05:58:02   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.25   26 Sep 2014 03:38:38   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.24   11 Sep 2014 11:03:22   rjamloki
 * removed redundant extern
 * 
 *    Rev 1.23   18 Aug 2014 05:44:18   rjamloki
 * Fixed SendFData function to use running preset parameters.
 * 
 *    Rev 1.22   18 Aug 2014 01:45:14   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.21   07 Aug 2014 15:54:10   tayars
 * Variable name change and removed flow being updated in pre ready - this is not needed.
 * 
 *    Rev 1.20   28 Jul 2014 12:50:34   rjamloki
 * UDI scan added in run results
 * 
 *    Rev 1.19   17 Jul 2014 12:45:32   hasanchez
 * Changes related to the freq offset.
 * 
 *    Rev 1.18   15 Jul 2014 17:56:48   hasanchez
 * Changes related to the freq offset.
 * 
 *    Rev 1.17   09 Jul 2014 12:18:12   rjamloki
 * Added Batch count increment in SendFData function. SvInterlock renamed to PartClamp.
 * 
 *    Rev 1.16   20 Jun 2014 14:34:48   rjamloki
 * Updating global pressure value at preready entry.
 * 
 *    Rev 1.15   11 Jun 2014 12:07:48   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.14   05 Jun 2014 14:25:50   lmarkure
 * Enabled Rapid Traverse Solenoid valve
 * 
 *    Rev 1.13   27 May 2014 10:13:58   amaurya
 * Initialized mandatory colums for weld history
 * 
 *    Rev 1.12   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.11   21 May 2014 03:36:58   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.10   07 May 2014 10:39:52   rjamloki
 * RecordSetupAlarm() RecordAlarm() function changed.
 * 
 *    Rev 1.9   21 Apr 2014 13:48:30   rjamloki
 * Alarm Logging implementation added
 * 
 *    Rev 1.8   14 Apr 2014 11:59:10   rjamloki
 * Corrected driving memstore output to low.
 * 
 *    Rev 1.7   14 Mar 2014 13:16:38   lmarkure
 * Merged 11.33 changes in, deleted unused code in collectvelocitydata function
 * 
 *    Rev 1.6   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:42   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:52   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:48   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 --------------------------- MODULE DESCRIPTION ---------------------------

 Module name: Ready

 Filename:    Ready.cpp(Created from ready.c Version 11.33Final)

 Function Name: State machine code

----------------------------- DESCRIPTION --------------------------------

 This module contains the code for the ready state, downstroke state and
 the return to ready state.

----------------------------- PSEUDO CODE --------------------------------

---------------------------- LOCAL_EQUATES -------------------------------*/

/*#define READY_UT                   For use as an aid in unit testing */
//#define VELOCITY_DEBUG
//#define TRIGGER_FORCE_TEST        /* This allows the actual trigger force   */
/* to be displayed as set trigger force & */
/* trigger distance to be displayed as    */
/* the absolute distance (testing only)   */

#define VELOCITY_OFFSET       500 /* Back off from trigger this distance    */
#define VELOCITY_DISTANCE    1250 /* This is the distance over which we use */
#define VELOCITY_SAMPLE_RATE    1 /* How often (in ms) we sample distance   */
#define VELOCITY_POINTS      2000 /* The maximum number of collected points */
#define VELOCITY_MINIMUM       10 /* If any movement beyond VELOCITY_OFFSET */
/* then this is minimum value 10=.00010"  */
#define MIN_POINTS              2 /* Minimum # of points needed for calc    */
#define VELOCITY_DIST_MIN     125 /* Movement before any readings are used  */
#define PARTCONTACTTIME      5000 /* Min time which part contact is checked */
#define PARTCONTACTDISTANCE     1 /* Distance which part contact is checked */
#define MAX_POS_INC           127 /* Max size for positive increment        */
#define MAX_NEG_INC          -127 /* Max size for negative increment        */

#define READYDELAYTIME         10 /* Time to delay actual ready output      */
/* An attempt to fix 'Upper Limit Timeout'*/
#define PSRESETDELAY           10 /* Length of time PS reset remains active */
#define PTS_TIMEOUT         10000 /* Time in which pretrigger must start    */
#define TRIGGERBOUNCETIME      20 /* Time after ULS before checking trigger */
#define PASSES_BEFORE_FAILURE   2 /* How many times in ready a bad pressure */
#define PASSES_BEFORE_REGFAILURE   19 /* How many times in ready system pressure is not +=3 psi of regulator pressure bad*/

/* is accepted before an alarm is created */
//#define PRESSUREDELAY         500 /* How often in ready to read pressure    */
//#define PRESSUREOFFSET        300 /* Allowed pressure change before recal   */

#define EXT_TRGDELAY_TIMEOUT  30000

#define FilterIndex8 8
#define FilterIndex16 16
/*------------------------------ INCLUDES ----------------------------------*/

#include "qdef.h"
#include <string.h>
#include "names.h"
#include "state.h"
#include "menu.h"
#include "preset.h"
#include "beep.h"
#include "wldstate.h"
#include "weld_obj.h"
#include "alarms.h"
#include "statedrv.h"
#include "keypad.h"
#include "selctkey.h"
#include "util.h"
#include "weldhold.h"
#include "display.h"
#include "genalarm.h"
#include "alsetup.h"
#include "battram.h"
#include "menu1.h"
#include "graphs.h"
#include "menuhorn.h"
#include "getmsg.h"
#include "encoder.h"     // jz added for VelocityEstimater()
#include "dups_api.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "CPLD.h"
#include "WeldManagerTask.h"
#include "psnvram.h"
#include "Events.h"
#include "InputTask.h"
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "ready.h"
#include "digout.h"
#include "statedrv.h"
#include "mansensr.h"
#include "fpled.h"
#include "timer.h"
#include "outports.h"
#include "inports.h"
#include "encoder.h"
#include "limits.h"
#include "weld.h"
#include "FlowLookupTable.h"
#include "spidd.h"

#define MAX_HISTORY   2
SINT16 PartContactDistance[MAX_HISTORY];/*  Keep track of last MAX_HISTORY */
UINT16 C1 = 0; /*  cycles for debugging           */

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

static SINT32 FrequencyStart;
static SINT32 FirstDistance;
static UINT16 RTAlreadySetFlag;
UINT16 TestTimerCounter, AlarmFlag;
UINT16 TestModeAllowed = TRUE;
UINT16 OkToDisplayAlarms; /* TRUE:cycle is complete, display ok */
UINT16 SystemPressureCheck;

SINT8 VelocityData[VELOCITY_POINTS][MAX_HISTORY];

#ifdef VELOCITY_DEBUG
UINT16 VelocityTrigger = 128; /* For debugging, stop when velocity greater */
#endif

UINT16 NextValueIndex, PointCounter, SampleCount;
UINT16 StopSamplingFlag, StartSamplingFlag;
UINT16 NegVelocityCounter;

UINT16 ReadyDelay, ReadyAlreadySet;
UINT16 PSResetDelay, PBExitTimer, ULSExitTimer;
UINT16 PartPresentExitTimer, PartClampExitTimer;
//UINT16 PressureReadDelay;

UINT16 SetupAlarmFlag;
//UINT16 DontPrintGraph;   /* Disable Print Now whenever cycle is aborted   */
UINT16 PrinterTotalCount;
double PrinterIncPoints;
double PrinterNewInc;
UINT16 PrinterCopyPts;
UINT16 PTSFlag; /* TRUE:pre-trigger has started */

SINT32 FreqChg, TestTime;
SINT32 OldDistance;
SINT32 SaveTriggerDistance;
SINT32 PTSTimer;
//SINT32 LastPressureReading = -1;

SINT16 TriggerDelayTimer;
SINT16 PeakPower, PeakTestPower;
SINT32 PowerTest;
SINT32 OverloadFreq; /* Value stored when pre-trigger O/L occurs */
SINT32 OverloadPower; /* Value stored when pre-trigger O/L occurs */

UINT16 StaggerWatchDogTimer, ExternalCycleAbortGoneFlag;
UINT16 ResetReceivedFlag, UpperLimitTimer;
BOOLEAN ECycleHistFlag;

BOOLEAN JustPoweredUpFlag = TRUE;
BOOLEAN PoweredUp = FALSE;
BOOLEAN UlsTimeout;
BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;

BOOLEAN MissingPartFlag = FALSE; //J.B
BOOLEAN TrgDelayTimeout, PartClampTimeout;
BOOLEAN PartClampActive;
UINT16 ExtTriggerDelayTimer, PartClampTimer;
//Below flags decides whether to check for PartPresent active and Part Clamp active alarm in Pre ready state.
//They are made false in ReadyEntry and true in Trigger State normal exit.
BOOLEAN CheckForPartPresentAlarm = FALSE, CheckForPartClampAlarm = FALSE;

static UINT32 BuffPwrTst[FilterIndex16] = { 0 }; //Power Buffer During Test
static UINT32 *ptst = &BuffPwrTst[0];
static UINT32 TestPwrSum = 0;

SINT32 DistanceAtULS = IDLE_TO_DOWNSPEED_DISTANCE; /* Start with a default value  */
SINT32 DistanceAtHome;
extern enum WELDSTATES WeldState;

UINT32 CurrentVelocity;
extern BOOLEAN DistFlag;
extern BOOLEAN ReadyFlag;
extern BOOLEAN SonicDisabledFlag;
extern SINT32 EncoderPos;
extern SINT32 AccumulatedEnergy, EnergyInJoules;
extern SINT32 CurrentFreqIn; /* Value being read by 7890          */
extern UINT16 PowerUpTimer;
extern UINT16 JustPoweredUpTimer;

extern UINT16 PresetNeedsToBeUpdated;

extern UINT8 AETrigger;
extern UINT32 CurrentPowerIn; /* Value being read by 7890          */
extern SINT32 HomePressure;

extern UINT16 PartContactFlag;
extern BOOLEAN UpdateFlag;

static END_WELD_MSG end_weld_msg;

WELD_DATA WeldingResults;
WELD_DATA *WeldingResultsPtr;

extern enum WELD_SEQUENCE_TYPE CurrentSequence;

UINT16 ClearedHardwareAlarm = FALSE;
UINT16 AlarmCounter = 0;

extern UINT16 PresetHasBeenOKed;
extern UINT16 AdjustWeldSetupMenuFlag;
extern BOOLEAN PartPresentConfigured;
extern INBITS Inp;
//extern SINT8  *TestBuffer1[[MESSAGESIZE];
#define MAXTESTTIME 700  /* Max time sonics allowed on in test mode */
SINT16 TestCountDown = 250;

extern WELD_OBJECT *MsDataPtr;
extern BOOLEAN DownspeedTuneFlag;

void SendKeyToWeldMngr(MSG_OPCODE_TYPE Opcode, BOOLEAN State);
void WriteAlarmLog(UINT32 AlarmCode, bool SetupAlarm);
/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

extern BOOLEAN CycleAbort;

extern UINT8 VGALatchPSStore;
UINT16 HornReturnCount = 0;
UINT16 TriggerBounceTimer;

UINT32 TotalCycleTime;


BOOLEAN TotalCycleTimeAssigned;

SINT32 PretriggerDelayTimer;

BOOLEAN SBLMinLimitReached;
BOOLEAN SBLMaxLimitReached;
BOOLEAN PressureUpdateEnable = TRUE;//becomes true in ready entry and pressure change. Becomes false in TestRegulatorPressure function.
BOOLEAN WaitForRejectConfirm = FALSE;

/*-------------------------- LOCAL FUNCTION PROTOTYPES ---------------------*/

/*-------------------------------- CODE ------------------------------------*/

#ifdef READY_UT

#include "..\ut\ready.ut"

#endif

void SetAlarmFlag(void)
{
   AlarmFlag = TRUE;
   SetGeneralAlarm();
   Beep(ALARMBEEP);
}

void ClearAlarmFlag(void)
{
   AlarmFlag = FALSE;
}

UINT16 CheckAlarmFlag(void)
{
   return (AlarmFlag);
}

void ClearAbort(void)
{
   AbortFlag = FALSE;
   ExternalCycleAbortGoneFlag = FALSE;
   PBExitTimer = 0; /* Reset palm button uls timer      */
   PBExitFlag = FALSE; /* Clear palm buttom home flag      */
   ULSExitTimer = 0; /* Reset upper limit timer          */
   ULSExitFlag = FALSE; /* Clear upper limit home flag      */
   Inp.Trigger = FALSE; /* Clear trigger from last cycle    */
   PartPresentExitFlag = FALSE;
   PartClampExitFlag = FALSE;
   ReadyAlreadySet = FALSE;
   PartClampExitTimer = 0;
   PartPresentExitTimer = 0;
}

/***************************************************************************
*
*  This is the normal exit code of PreReady State. It deactivates PartID ready
*  Output and force menu update by initializing VgaUDiStatus.
*
***************************************************************************/
void PreReadyJump(void)
{
	UserCfgOutputOff(OUTPUT_UDIREADY);//Make UDIReady output Deactivate.
	if(CurrentSetup.UDIScan == ON)
	    VgaUDiStatus = UDISCAN_RECEIVED;
	else
		VgaUDiStatus = UDISCAN_OFF;
	ClearAbort();
}

/****************************************************************************
*
*  This is the alarm exit code of PreReady State. It deactivates PartID ready
*  Output and force menu update by initializing VgaUDiStatus.
*
****************************************************************************/
void PreReadyAlJump(void)
{
	UserCfgOutputOff(OUTPUT_UDIREADY);//Make UDIReady output Deactivate.
	if(CurrentSetup.UDIScan == ON)
	    VgaUDiStatus = UDISCAN_RECEIVED;
	else
		VgaUDiStatus = UDISCAN_OFF;
}

void InitVelocityData(void)
/***************************************************************************/
/*                                                                         */
/*  This function will clear out the velocity array and all values in      */
/*  preparation for a new cycle.                                           */
/*                                                                         */
/***************************************************************************/
{
   PointCounter = 0; /* Set number of points in buffer to zero     */
   NextValueIndex = 0; /* Start putting points into index zero       */
   OldDistance = 0; /* Make last distance reading zero            */
   SampleCount = 0; /* Reset sample counter to zero               */
   StopSamplingFlag = FALSE; /* Dont stop sampling yet                     */
   StartSamplingFlag = FALSE;/* But dont start yet either,dist not reached */
   if (C1 >= (MAX_HISTORY - 1))
   {
      C1 = 0;
   } else
      C1++;
   PartContactDistance[C1] = 0;
   NegVelocityCounter = 0;
}

void CollectVelocityData(SINT32 NewDistance)
/***************************************************************************/
/*                                                                         */
/*  This function will collect distance data in order to calculate the     */
/*  final velocity.  The velocity will be calculated by backing off from   */
/*  the trigger distance by a distance specified by the define VELOCITY_   */
/*  OFFSET.  It will be calculated over a distance defined by VELOCITY_    */
/*  DISTANCE.  Data will be collected at a rate set by the define VELOCITY_*/
/*  SAMPLE_RATE.  The maximum number of points which will be collected is  */
/*  defined by VELOCITY_POINTS.  VELOCITY_SAMPLE_RATE times VELOCITY_POINTS*/
/*  is the length of time (ms) which velocity will be calculated over.     */
/*  Points will be collected until one of two things happens:  Thing 1 -   */
/*  The distance traveled slowed down to less than PARTCONTACTDISTANCE     */
/*  over PARTCONTACTTIME.  Thing 2 - The current force is equal to or      */
/*  greater than the minimum trigger force.                                */
/*                                                                         */
/*  How this function works:                                               */
/*  ------------------------                                               */
/*                                                                         */
/*  A circular buffer will be used to save the data.  The data will be     */
/*  compressed into a UINT8.  Each data point will represent the difference*/
/*  in distance from this reading to the previous reading.  This means     */
/*  there are some limits: 1) between readings the distance can change no  */
/*  more then 0.0255", 2) the distance cannot go negative.                 */
/*                                                                         */
/*  The following variables will keep track of things:                     */
/*  NextValueIndex       Where in the array the next difference will go    */
/*  PointCounter         Number of points collected in buffer so far       */
/*  OldDistance          The reading from the last sample                  */
/*  SampleCount          How many ms since the last sample                 */
/*                                                                         */
/***************************************************************************/
{
   SINT16 TempDistance;
   UINT16 TempTime, TempIndex;

   if ((NewDistance >= VELOCITY_DIST_MIN) && /* Dont start until min dist reached */
   (NewDistance < 10000))
   { /* Make sure distance is not negative  */
      StartSamplingFlag = TRUE;
   }
   if ((StopSamplingFlag == FALSE) && (StartSamplingFlag == TRUE))
   {
      SampleCount++;
      if (SampleCount >= VELOCITY_SAMPLE_RATE)
      {
         SampleCount = 0;
         TempDistance = (NewDistance - OldDistance);
         if (TempDistance > MAX_POS_INC)
         {
            TempDistance = MAX_POS_INC; /* Cant be bigger then a signed byte */
         } else if (TempDistance < MAX_NEG_INC)
         {
            TempDistance = MAX_NEG_INC; /* Cant be smaller then a signed byte */
            NegVelocityCounter++; /* Count # of times negative   */
         }
         VelocityData[NextValueIndex][C1] = (SINT8) (TempDistance);
         TempIndex = NextValueIndex;
         OldDistance += TempDistance;

         NextValueIndex++;
         if (NextValueIndex >= VELOCITY_POINTS)
            NextValueIndex = 0;
         else if (PointCounter < VELOCITY_POINTS)
         {
            PointCounter++;
         }
         TempTime = PARTCONTACTTIME;
         TempDistance = 0;
      }
   }
   CurrentVelocity = VelocityEstimator(EncoderPos);
}

SINT32 CalculateVelocity(void)
/***************************************************************************/
/*                                                                         */
/*  This function will do the actual velocity calculation using the data   */
/*  which was collected in CollectVelocityData.  It is assumed that when   */
/*  trigger has occurred the NextValueIndex will be pointing to the last   */
/*  collected piece of data.  From this point we need to go back for a     */
/*  distance of VELOCITY_OFFSET.  Here is our last data point.  From here, */
/*  go back another distance of VELOCITY_DISTANCE and where we find this   */
/*  value represents our total distance and time for velocity.             */
/*                                                                         */
/*  Two types of errors can be generated.  Error 1 means from VELOCITY_    */
/*  DIST_MIN to part contact (or trigger) there is less then VELOCITY_     */
/*  OFFSET distance.  Error 2 means from VELOCITY_DIST_MIN to part contact */
/*  (or trigger) there is less then VELOCITY_DISTANCE plus VELOCITY_OFFSET.*/
/*  Error 1 will result in a velocity of VELOCITY_MINIMUM.  Error 2 will   */
/*  result in a valid velocity for whatever distance the horn did travel.  */
/*                                                                         */
/***************************************************************************/
{
   SINT32 Distance = 0;
   SINT32 RetVelocity;
   UINT16 ExitFlag = FALSE;
   UINT16 Counter = 0;
   UINT16 LastTimeValue = 1;
   UINT16 ErrorFlag = 0;
   UINT16 ActualPointCounter = 0;

   /*---  First determine if part contact was ever reached, or just trigger ---*/

   if (StopSamplingFlag == FALSE)
   { /* If FALSE we never reached part contact */
      PartContactDistance[C1] = EncoderPos; /* Make current dist part contact  */
   }

   /*---  First find out how much data to throw away (VELOCITY_OFFSET)      ---*/

   while (ExitFlag == FALSE)
   {
      if (NextValueIndex != 0)
         NextValueIndex--;
      else
         NextValueIndex = VELOCITY_POINTS - 1;
      Distance += VelocityData[NextValueIndex][C1];
      Counter++;
      if (Distance >= VELOCITY_OFFSET)
      { /* We have enough offset now     */
         ExitFlag = TRUE;
      }
      if (Counter > PointCounter)
      {
         ErrorFlag = 1; /* Out of points, cycle must     */
         ExitFlag = TRUE; /* have been too short           */
      }
   }
   if (ErrorFlag == 0)
   { /* We have proper offset, so get */
      LastTimeValue = NextValueIndex; /* final time value              */
      /* check for divide by zero */
      //      if(LastTimeValue == 0) LastTimeValue = 1;
      Distance = 0;

      /*---  Now find where velocity calculation starts (VELOCITY_DISTANCE)    ---*/

      ExitFlag = FALSE;
      while (ExitFlag == FALSE)
      {
         if (NextValueIndex != 0)
            NextValueIndex--;
         else
            NextValueIndex = VELOCITY_POINTS - 1;
         Distance += VelocityData[NextValueIndex][C1];
         Counter++;
         ActualPointCounter++;
         if (Distance >= VELOCITY_DISTANCE)
         {
            ExitFlag = TRUE; /* We have enough distance now   */
         }
         if (Counter > PointCounter)
         {
            ErrorFlag = 2; /* Out of points, cycle must     */
            ExitFlag = TRUE; /* have been too short           */
         }
      }
   }

   Distance *= 10; /* Multiply by 10 to get tenth's in final velocity */
   switch (ErrorFlag)
   {
   case 0: /* Normal cycle data is okay             */
      if ((ActualPointCounter < MIN_POINTS) || (PartContactDistance[C1] == 0))
      {
         RetVelocity = VELOCITY_MINIMUM;/* Error for now, not enough points */
      } else
      {
         RetVelocity = (Distance / (ActualPointCounter * VELOCITY_SAMPLE_RATE));
         if (RetVelocity < VELOCITY_MINIMUM)
         {
            RetVelocity = VELOCITY_MINIMUM;
         }
      }
      break;

   case 1: /* Cycle less then VELOCITY_OFFSET       */
      RetVelocity = VELOCITY_MINIMUM;
      break;

   case 2: /* Cycle < VELOCITY_DISTANCE, deal with it */
      if ((ActualPointCounter < MIN_POINTS) || (PartContactDistance[C1] == 0))
      {
         RetVelocity = VELOCITY_MINIMUM;/* Error for now, not enough points */
      } else
      {
         RetVelocity = (Distance / (ActualPointCounter * VELOCITY_SAMPLE_RATE));
         if (RetVelocity < VELOCITY_MINIMUM)
         {
            RetVelocity = VELOCITY_MINIMUM;
         }
      }
      break;

   default:
      break;
   }
#ifdef VELOCITY_DEBUG

   if (RetVelocity > VelocityTrigger)
   {
      while(1);
   }
#endif

   return (RetVelocity);
}

BOOLEAN CheckForMissingPartMax(void)
/***************************************************************************/
/*                                                                         */
/*  This function will first see if cycle aborts are on, then if missing   */
/*  part is on and finally if the missing part conditions exist.  If it    */
/*  is determined that the part is missing then a TRUE will be returned    */
/*  otherwise a FALSE will be returned.                                    */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN Retval = FALSE;

   if ((RunningPreset.MissingMaxFlag == FALSE)
         && (RunningPreset.MissingPartFlag == TRUE)
         && (RunningPreset.CycleAbortFlag == TRUE))
   {
      if (EncoderPos > RunningPreset.MissingPartMax)
      {/* The horn has passed */
         Retval = TRUE; /* the allowed distance*/
      }
   }
   return (Retval);
}

BOOLEAN CheckForMissingPartMin(void)
/***************************************************************************/
/*                                                                         */
/*  This function will first see if cycle aborts are on, then if missing   */
/*  part is on and finally if the missing part conditions exist.  If it    */
/*  is determined that the part is missing then a TRUE will be returned    */
/*  otherwise a FALSE will be returned.                                    */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN Retval = FALSE;

   if ((RunningPreset.MissingMinFlag == FALSE)
         && (RunningPreset.MissingPartFlag == TRUE)
         && (RunningPreset.CycleAbortFlag == TRUE))
   {
      if (WeldingResults.ActualTriggerDistance < RunningPreset.MissingPartMin)
      {
         Retval = TRUE;
      }
   }
   return (Retval);
}

void EnterReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before entering the    */
/*  ready state.  It will do whatever good code should do before the       */
/*  ready state is entered.                                                */
/*                                                                         */
/***************************************************************************/
{
   OkToDisplayAlarms = TRUE;
   SystemPressureCheck = PRESSURE_CHECK_TIME1;
   if (Inp.Estop == FALSE)
      CycleAbort = FALSE;
   TrigSwActv(); /* safety circuit input            */
   PSIdle();
   ReadyAlreadySet = FALSE;
   DistFlag = FALSE; /* Reset last cycle distance flag  */
   HornReturnFlag = TRUE;
   HornReturnCount = 0;
   PBReleaseOff();
   StopDataCollection(); /* Stop data collection in ready   */
   PowerUpTimer = 0; /* Reset just for horndown mode    */
   MissingPartFlag = FALSE; // Clearing the flag after each cycle
   RTAlreadySetFlag = FALSE;
   CoolValOff(); // Turn Off Cooling Valve
   ConfirmPresetOff(); //Make Confirm Preset output low
   CheckForPartPresentAlarm = FALSE;
   CheckForPartClampAlarm = FALSE;
   if (!TotalCycleTimeAssigned)
   {
      FinalResults.TotalCycleTime = TotalCycleTime;
      TotalCycleTimeAssigned = TRUE;
   }
   PressureUpdateEnable = TRUE;
}

void TestRegulatorPressure()
/***************************************************************************/
/*This function checks system pressure against regulator pressure for AES
 * Actuator
 */
{
	static UINT16 PassCounter = 0;
	if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC){
		//Check system pressure is within +- 3psi of regulator pressure setting
		//if not generate alarm and update regulator pressure. Checking 20 samples in
		//250 ms interval
		if((CurrentPressure > (SetPressureValue + PRESSURE_TOLLERANCE)) ||
				(CurrentPressure < (SetPressureValue - PRESSURE_TOLLERANCE))){
			if (++PassCounter > PASSES_BEFORE_REGFAILURE){
				RecordAlarm(EQ25);
				PressureUpdateEnable = FALSE;
				SetPressureValue = CurrentPressure;
				PassCounter = 0;
			}
		}
		else
			PassCounter = 0;
	}
}


void TestReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed every time the ready state  */
/*  is called.  This will make sure we should remain in ready.  System     */
/*  pressure will be checked.  An alarm will be generated if the pressure  */
/*  fails for 3 consecutive 1/4 second readings. Any one or two bad        */
/*  readings will be tossed out.  The logic here is that if the pressure   */
/*  is really bad it will be bad for at least 3/4 second.                  */
/*                                                                         */
/***************************************************************************/
{
	 static UINT16 PassCounter = 0;
	 if ((SystemPressureCheck--) <= 0)
	 {
		SystemPressureCheck = PRESSURE_CHECK_TIME2;
		if ((CurrentSetup.ControlLevel >= LEVEL_c) && ((CurrentPreset.PressureLimitFlag
				& BIT0) == BIT0)) {
			if ((((CurrentPreset.PressureLimits & PPRESSURELIMITBIT) == 0)
					&& ((CurrentPreset.PPressureLimit + PRESSURE_TOLLERANCE) < CurrentPressure))
					|| (((CurrentPreset.PressureLimits & MPRESSURELIMITBIT)
							== 0) && ((CurrentPreset.MPressureLimit - PRESSURE_TOLLERANCE)
							> CurrentPressure))) {
				if (++PassCounter > PASSES_BEFORE_FAILURE)
					RecordAlarm(EQ25);
			} else
				PassCounter = 0;
		}
		TestRegulatorPressure();
	}

	//update the live changes of flow and pressure without waiting to go into PB state.
	if(!DownspeedTuneFlag)
	{
      if(CurrentPreset.TunedPreset)
         SetFlowValue = CurrentPreset.TunedFlowValue;
      else
         SetFlowValue = FlowLookup(CurrentPreset.Downspeed);
	}

	if(PressureUpdateEnable == TRUE)
	   SetPressureValue = CurrentPreset.WeldPressure;

   if (CheckIfResetRequired() == FALSE)
   {
      AlarmsReset = TRUE;
      TrigSwActv(); /* safety circuit input */
   }
   if (ReadyAlreadySet == FALSE)
   {
      ReadyAlreadySet = TRUE;
      SetReady();
   }
   if (Inp.PSSeek == TRUE)
   { /* Light the 0% led if external seek */
      UpdateLED(ZEROPERCENTLED, ON);
   } else
   {
      UpdateLED(ZEROPERCENTLED, OFF);
   }
}

void EnterTestReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before entering the    */
/*  ready state.  It will do whatever good code should do before the       */
/*  ready state is entered.                                                */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.Estop == FALSE)
      CycleAbort = FALSE;
   TrigSwActv(); /* safety circuit input            */
   PSReset(); /* Clear any overloads left over   */
   PSResetDelay = PSRESETDELAY; /* Start delay to insure a reset   */
   DistFlag = FALSE; /* Reset last cycle distance flag  */
   HornReturnFlag = TRUE;
   HornReturnCount = 0;
   CPLD::thisPtr->SetDout(MemStoreOut, false);/* drive memstore output low */
   StopDataCollection(); /* Stop data collection in ready   */
   PowerUpTimer = 0; /* Reset just for horndown mode    */
}

void TestTestPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are checking to see if we can      */
/*  enter the test ready state.                                            */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.PSRun == TRUE)
      LatchPSRun = TRUE;

   if (Inp.PSSeek == TRUE)
      LatchPSSeek = TRUE;

   if (Inp.PSClear == TRUE)
      LatchPSClear = TRUE;

   if (Inp.PSStore == TRUE)
   {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      VGALatchPSStore = 2;
   }

   if (--TestCountDown <= 0)
   {
      TestCountDown = 250;

      if (VGALatchPSStore)
         VGALatchPSStore--;

      SendFakeKeyPress(UPDATEDISPLAY); /* Tell menu system to update   */
   }
   if (CheckIfResetRequired() == FALSE)
      AlarmsReset = TRUE;
}

void TestReadyTest(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed every time the ready state   */
/*  is called while in the test weld sequence.                              */
/*                                                                          */
/****************************************************************************/
{
   if (CheckIfResetRequired() == FALSE)
      AlarmsReset = TRUE;

   if (Inp.PSRun == TRUE)
      LatchPSRun = TRUE;

   if (Inp.PSSeek == TRUE)
      LatchPSSeek = TRUE;

   if (Inp.PSClear == TRUE)
      LatchPSClear = TRUE;

   if (Inp.PSStore == TRUE)
   {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      VGALatchPSStore = 2;
   }

   if (--TestCountDown <= 0)
   {
      TestCountDown = 250;
      if (VGALatchPSStore)
         VGALatchPSStore--;
      SendFakeKeyPress(UPDATEDISPLAY); /* Tell menu system to update   */
   }
}

void ExitReady(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed just before leaving the      */
/*  ready state.  It will do whatever good code should do after the ready   */
/*  state is finished.                                                      */
/*  Output: WeldingResults.WeldPressure                                        */
/****************************************************************************/
{
   ClearAlarmFlag();
   if ((PresetNeedsToBeUpdated == FALSE) && (UpdateFlag == FALSE))
   {
      ClearReady(); /* Remove Welder Ready signal          */
   }
   // clear store & clear signals
   Inp.PSClear = FALSE;
   Inp.PSStore = FALSE;
   DistanceAtHome = EncoderPos;
   CPLD::thisPtr->SetDout(MemStoreOut, false);/* drive memstore output low */
   ZeroEncoder();
   SonicsAbort = FALSE; /* Reset sonics abort flag             */
   AccumulatedEnergy = 0; /* Clear out last cycle energy         */
   EnergyInJoules = 0;
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
   PeakPower = 0;
   DisplayWeldPower(PeakPower); /* Display last peak power reading */
   ResetReceivedFlag = FALSE; /* Remove any sign of reset key        */
   if (ExternalCycleAbortGoneFlag == TRUE)
   {
      ECycleHistFlag = FALSE;
   }
   InitVelocityData(); /* Prepare velocity variables          */
   WeldingResults.WeldPressure = (UINT16) HomePressure;
//   CurrentPreset.GaugePressure = (UINT16) HomePressure;
   PresetHasBeenOKed = FALSE; /* Will not allow the state machine to advance passed the */
   /* PB state until the WeldManger completes its part */
   TotalCycleTime = 0;
   TotalCycleTimeAssigned = FALSE;
   FinalResults.CycleTimeResult = 0;
   if(RunningPreset.FreqOffsetFlag == TRUE)   //HSAN update to improve the logic 
      SetCurrentFreqOffset(RunningPreset.FreqOffset);  //Enable Freq offset
   UDIScanRecived = FALSE;   
}

void  ExitAlReady(void)
{
   UDIScanRecived = FALSE;   
}

void ExitReadyTest(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed just before leaving the      */
/*  ready state on the way to sonics on in the test mode.                   */
/*                                                                          */
/****************************************************************************/
{
   ClearReady(); /* Remove Welder Ready signal          */
   SonicsAbort = FALSE; /* Reset sonics abort flag             */
   AccumulatedEnergy = 0; /* Clear out last cycle energy         */
   ResetReceivedFlag = FALSE; /* Remove any sign of reset key        */
}

void StartPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when one palm button has    */
/*  been pressed. It will do whatever good code should do after just one   */
/*  palm button has been pressed.                                          */
/*                                                                         */
/***************************************************************************/
{
   PSReset(); /* Reset power supply before we go  */
   AlarmCounter = 0;
   OkToDisplayAlarms = FALSE;

   Init1msPts();

   if ((RunScreenFlag == TRUE) && (MenuCounter > 1) && (CurrentSequence
         != HORNDOWN) && (AdjustWeldSetupMenuFlag == FALSE))
   {
      SendFakeKeyPress(RunKey); /* Return to Run Screen from alarms */
   }

   /*----- Clean up trigger stuff from last cycle -----*/

   TriggerLostHistoryFlag = FALSE;
   TriggerLostTime = 0;
   TriggerLostForce = 0;
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
   MaxForceDebounce = 0;
   NewMaxForce = 0;
   StaggerFlag = FALSE;
   StaggerWatchDogTimer = 0;
   ResetUpTimer(SONICSTIMER);
   UlsTimeout = FALSE; /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0; /* Reset timer to zero              */
   OKToAdvance = FALSE;
   ActualAfterburstTime = 0; /* Clear for seek end time          */
   ActualABDelay = 0; /* Clear for seek end time          */
   ActClrFlag = FALSE;
   SonicDisabledFlag = FALSE;
}

void TestPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed between the time one palm   */
/*  is pressed and before two palm buttons are pressed.  It will be a      */
/*  watchdog on the stagger time.                                          */
/*                                                                         */
/***************************************************************************/
{
   static UINT16 PassCounter = 0;
   if (++StaggerWatchDogTimer > PALMBUTTON_STAGGER_TIME)
   {
      StaggerFlag = TRUE;
   }

   if (PresetHasBeenOKed == TRUE)
   {
      if (ReadyFlag == TRUE)
         ClearReady(); /* Remove Welder Ready signal */
      if (Inp.BothPB == TRUE)
      {
         StaggerWatchDogTimer = 0;
         //Check if Current pressure is within the limits from Required pressure.
         //This becomes an issue when external preset has much lower weld pressure than current.
         //In this case horn starts moving but comes back to home because of lower pressure and then starts moving again.
         if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && ((CurrentPressure > (SetPressureValue + PRESSURE_TOLLERENCE_PB))
                     || (CurrentPressure < (SetPressureValue - PRESSURE_TOLLERENCE_PB))))
         {
            if (++PassCounter > PRESSURE_CHECK_TIMEOUTPB) {         //Raise the alarm if pressure does not come
                                                                    // within limits in 5 sec.
               RecordAlarm(EQ25);
               PassCounter = 0;
            }
         }
         else if((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (FlowReadValue != SetFlowValue)){}//Wait until flow setting is applied in case of AEC Actuator
         else
         {
            OKToAdvance = TRUE;
            ClearSetupAlarms();
            ClearFinalResults();
            PassCounter = 0;
         }
      }
   }

   /*---   This code to deal with horn down mode   ---*/

   if ((CurrentSequence == HORNDOWN) && (Inp.BothPB == TRUE))
   {
      OKToAdvance = TRUE;
   }
}

void ExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when both palm buttons have */
/*  been pressed.  It will do whatever good code should do after both      */
/*  palm buttons have been pressed.                                        */
/*                                                                         */
/***************************************************************************/
{
   if (PrinterTotalCount == 0)
      GetPtsIncrement();
   MsDataPtr->TotalPts = PrinterTotalCount;
   MsDataPtr->IncrementPts = PrinterIncPoints;
   MsDataPtr->CopyPts = PrinterCopyPts;
   MsDataPtr->NewInc = PrinterNewInc;

   if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
	   WeldingResults.WeldPressure = (UINT16)CurrentPressure;

   if (!IsConfigured(INPUT_PART_CLAMPED) && !IsOutConfigured(
		   OUTPUT_PART_CLAMPED))
   {
      PartClampActive = FALSE;
      EnableSVOn(); /* Enable SV valve                 */
      SVOn(); /* Turn on SV to bring down hown   */
   } else
	   PartClampActive = TRUE;

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0)
   { /* If PTS, set PT amp */
      SetCurrentAmp(RunningPreset.PreTrigAmp); /* Pretrigger amplitude  */
   } else
   {
      SetCurrentAmp(RunningPreset.Amp1);/* Prepare P/S for 1st amplitude   */
   }

   /* Here decide if extra cooling is needed  */

   if (CurrentSetup.ExtraCooling == TRUE)
   {
      CoolValOn();
   }
   UserCfgOutputOff(OUTPUT_CYCLE_OK); //Make Cycle Okay output low
   ConfirmPresetOn();//Make Confirm Preset output high if preset changed.
   if (Inp.SonicDisable)
      SonicDisabledFlag = TRUE;
   /*   AccumulatedEnergy = 0;   *//* Clear out last cycle energy     */
   EncoderFailTimer = 0; /* Clear encoder check timer       */
   OKToAdvance = FALSE;
   ErrorCodeFlag = FALSE;
   ErrorCode = (ERRORCODE_ARG) 0;
}

void TriggerBeep(void)
/***************************************************************************/
/*                                                                         */
/*  This function will unconditionally sound the trigger beeper one time.  */
/*                                                                         */
/***************************************************************************/
{
   Beep(TRIGGERBEEP);
   SaveTriggerDistance = EncoderPos;
   if((CurrentSequence == WELD) && (DownspeedTuneFlag == FALSE)){
      CheckForPartPresentAlarm = TRUE;
      CheckForPartClampAlarm = TRUE;
   }
   if((CurrentSequence == CALIBRATION) || (RunningPreset.WeldTrigger == TRIGGERBY_FORCE))
	   PBReleaseOn();
}

void AlarmExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when the palm button        */
/*  state must be exited because of some type of an alarm.                 */
/*                                                                         */
/***************************************************************************/
{
   CycleAbort = TRUE;
}

void EntryTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before waiting for     */
/*  trigger.                                                               */
/*                                                                         */
/***************************************************************************/
{
   StartUpTimer(VELOCITYTIMER); /* Start timer for velocity calc    */
   FirstDistance = EncoderPos; /* Save position for velocity calc  */
}

void EntryTrs2(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed after distflag.             */
/*  Needs to be called after TRS this is for alpha A only.                 */
/***************************************************************************/
{
   TriggerDelayFlag = TRUE;
}

void ExitULS(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the upper limit  */
/*  switch is cleared indicating the horn has left the home position.      */
/*                                                                         */
/***************************************************************************/
{

   StartUpTimer(CYCLETIMER); /* Start timer for the fun of if    */
   OKToAdvance = FALSE; /* Clear so Final Data State can use*/
   OldDistance = EncoderPos; /* Make last distance=current pos   */
   DistanceAtULS = EncoderPos;

   /**    This section of code is executed in case the upper limit switch   **/
   /**    was reached before the idle to downspeed distance was reached.    **/
   if (CurrentSequence == WELD) /* If WELD only go to downspeed */
   {
      if ((/*StepAtRTDist.BitMask*/BIT0 & RunningPreset.RTFlag)
            == /*StepAtRTDist.BitMask*/BIT0)
      {
         RapidTraverseOn();
      } else
    	  RapidTraverseOff();
   }
   if (CurrentSetup.DistanceULS)
      ZeroEncoder();
   SBLMinLimitReached = FALSE;
   SBLMaxLimitReached = FALSE;
}

void ExitULS1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the upper limit  */
/*  switch is active on the upstroke, indicating the horn has just returned*/
/*  home.  A test of door open is done here, but we are actually checking  */
/*  for trigger.  Once uls is active door open is used instead of trigger. */
/*                                                                         */
/*    60.2.120 08-01-97  BEKymer    Check for EQ4 in ExitULS1              */
/*                                                                         */
/***************************************************************************/
{

}

void ExitTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the first        */
/*  downspeed (pressure) value.                                            */
/*                                                                         */
/***************************************************************************/
{
}

void ExitTrs2(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the second       */
/*  downspeed (pressure) value.  This function will set up the first weld  */
/*  force.                                                                 */
/*                                                                         */
/***************************************************************************/
{
   WeldingResults.ActualDownspeed = CalculateVelocity();
   if(RunningPreset.FreqOffsetFlag == TRUE)
      SetCurrentFreqOffset(RunningPreset.FreqOffset);
}

void ExitUlsUp(void)
/***************************************************************************/
/*  This is the function that will be executed when the "wait for upper    */
/*  limit to clear" state has finished.                                    */
/*                                                                         */
/***************************************************************************/
{
   OKToAdvance = FALSE;

   /*--  Use ActualDistance or ActualTriggerDistance which ever is larger  --*/

   if (RunningPreset.ActClrFlag == TRUE)
   { /* Actuator Clear function is ON */
      if ((CurrentSetup.Actuator == AED)
           || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (WeldingResults.ActualTotalAbs
               > WeldingResults.ActualTriggerDistance)
         {
            if (RunningPreset.ActClrDistance > WeldingResults.ActualTotalAbs)
            {
               RecordAlarm(W1);
            }
         } else
         {
            if (RunningPreset.ActClrDistance
                  > WeldingResults.ActualTriggerDistance)
            {
               RecordAlarm(W1);
            }
         }
      }
   }
}

void AlarmUls(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when an alarm has forced    */
/*  the "wait for upper limit to clear" state to abort.                    */
/*                                                                         */
/***************************************************************************/
{
   SVOff(); /* Turn off SV to bring down hown  */
   CycleAbort = TRUE;
   OKToAdvance = FALSE;
}

void AlarmTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when an alarm has forced    */
/*  the trigger state to abort.                                            */
/*                                                                         */
/***************************************************************************/
{
   SVOff(); /* Turn off SV to bring down hown  */
   CycleAbort = TRUE;
}

void TestPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are checking to see if we can      */
/*  enter the ready state.  It will clear the ECycleAbort flag if the      */
/*  ExternalCycleAbortGoneFlag is TRUE (which is set in Inports.c).        */
/*                                                                         */
/*  The JustPoweredUpFlag delays the Ready signal until we think the front */
/*  panel has displayed the Run screen.                                    */
/*                                                                         */
/***************************************************************************/
{
   if ((SystemPressureCheck--) <= 0)
   {
      SystemPressureCheck = PRESSURE_CHECK_TIME2;
   }
   if (Inp.OnePB == TRUE)
   {
      PBExitTimer++; /* Count time until pb's released    */
      if (PBExitTimer > PBEXITTIME)
         PBExitFlag = TRUE; /* Took too long, generate alarm     */
   } else
      PBExitFlag = FALSE; /* clear alarm incase it was set    */

   if (Inp.uls == FALSE)
   { /* If still not home, then wait a bit  */
      ULSExitTimer++; /* Count until horn is home            */
      if (ULSExitTimer > UPPERLIMIT_TIMEOUT)
         ULSExitFlag = TRUE;
   } else
   {
      ULSExitFlag = FALSE;
   }

   if (PartPresentConfigured && (Inp.PartPresent == TRUE) && (CheckForPartPresentAlarm))
   {
	  PartPresentInpStatus = TRUE;
	  PartPresentExitTimer++; /* Count until part present is active */
      if (PartPresentExitTimer > PART_PRESENTCHECK_TIME)
      {
    	  PartPresentExitFlag = TRUE;
      }
   } else
   {
	   PartPresentInpStatus = FALSE;
	   PartPresentExitFlag = FALSE;
   }

   if ((PartClampActive == TRUE) && (Inp.PartClamped == TRUE) && (CheckForPartClampAlarm))
   {
	  PartClampInpStatus = TRUE;
	  PartClampExitTimer++; /* Count until part clamp signal is active */
      if (PartClampExitTimer > PART_CLAMPCHECK_TIME)
      {
    	  PartClampExitFlag = TRUE;
      }
   } else
   {
	   PartClampInpStatus = FALSE;
	   PartClampExitFlag = FALSE;
   }

   if (ExternalCycleAbortGoneFlag == TRUE)
   {
      ECycleHistFlag = FALSE; /* Clear external cycle abort in case it got set */
   }
   if (JustPoweredUpFlag == TRUE)
   {
      if (JustPoweredUpTimer >= POWERUPREADYDELAY)
      {
         if ((WeldingResults.EquipmentFailureAlarms & WRONG_ACTUATOR_FAIL)
               != WRONG_ACTUATOR_FAIL)
         {
            PoweredUp = TRUE;
            JustPoweredUpFlag = FALSE;

         }
      } else
      {
         JustPoweredUpTimer++;
      }
   }
   if (USBFullCheckFunc() == TRUE)
      RecordAlarm(EQ13);
   if (CheckIfResetRequired() == FALSE)
      AlarmsReset = TRUE;
   if (IsDUPSDataCollectionComplete() == FALSE)
   {
      DUPSOkFlag = FALSE; /* FALSE:waiting for DUPS data */
   } else
   {
      DUPSOkFlag = TRUE; /* TRUE:not waiting for DUPS data */
   }
   if(CurrentSetup.UDIScan == FALSE)
      UDIScanRecived = TRUE;
   OkToDisplayAlarms = TRUE; /* At this point allow alarms to be displayed */
}

void EPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are ready to enter the ready state.*/
/*  One of the things it will do it check for any alarms generated on this */
/*  weld cycle.                                                            */
/*                                                                         */
/***************************************************************************/
{
   SystemPressureCheck = PRESSURE_CHECK_TIME1;
   SetPressureValue = CurrentPreset.WeldPressure;
   CoolValOff(); // Turn Off Cooling Valve
   OkToDisplayAlarms = TRUE; /* Allow alarms to be displayed     */
   Inp.Trigger = FALSE;
   ReadyAlreadySet = FALSE;
   SetCurrentAmp(RunningPreset.Amp1); /* Initial amplitude                */
   if (IsConfigured(INPUT_PART_CLAMPED) && IsOutConfigured(
   		   OUTPUT_PART_CLAMPED))
       PartClampActive = TRUE;
   else
	   PartClampActive = FALSE;

   PartPresentInpStatus = FALSE;
   PartClampInpStatus = FALSE;
   if(CurrentSetup.UDIScan == TRUE){
	   UserCfgOutputOn(OUTPUT_UDIREADY);//Make UDIReady output Activate.
	   VgaUDiStatus = UDISCAN_WAITING;
   }
   else{
	   UDIScanRecived = TRUE;
	   VgaUDiStatus = UDISCAN_OFF;
   }
}

void EnterPTS(void)
/****************************************************************************/
/*                                                                          */
/*  This function will be executed when the pretrigger state is entered.    */
/*  It will clear the timer and timer flag.                                 */
/*                                                                          */
/****************************************************************************/
{
   PTSTimerFlag = FALSE; /* TRUE means pretigger took too long */
   PTSTimer = 0; /* Clear time value                   */
   PTSFlag = FALSE; /* Indicate pretrigger has not started yet */
   DistFlag = FALSE; /* Clear in case R/T already set it   */
   PretriggerDelayTimer = 0; /* Clear the timer, will be updated in TestPTS() */
}

void TestPTS(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for pre-trigger. */
/*  It will test the current distance and when the proper distance is      */
/*  reached the DistFlag will be set TRUE.                                 */
/*                                                                         */
/***************************************************************************/
{
   PTSTimer++; /* Count how long it's taking         */
   if (PTSTimer > PTS_TIMEOUT)
   { /* If too long set flag to abort      */
      PTSTimerFlag = TRUE;
   }
   if (RunningPreset.AutoTrigFlag)
      DistFlag = TRUE;
   else if (!RunningPreset.PreTriggerDistanceFlag)
   {
      if (EncoderPos >= RunningPreset.PreTriggerDistance)
         DistFlag = TRUE;
   } else if (!RunningPreset.PreTrigDelayFlag)
   {
      PretriggerDelayTimer++;
      if (PretriggerDelayTimer >= RunningPreset.PreTrigDelay)
         DistFlag = TRUE;
   }
   MissingPartFlag = CheckForMissingPartMax();
   CollectVelocityData(EncoderPos);
   CheckCycleAborts();
}

void StartPTS(void)
/***************************************************************************/
/*                                                                         */
/*  This function will start the sonics when executed.  The WeldOn external*/
/*  signal will not be activated at this time because there is no trigger  */
/*  condition (i.e. force on the part).                                    */
/*                                                                         */
/***************************************************************************/
{
   SetCurrentAmp(RunningPreset.PreTrigAmp); /* Pretrigger amplitude  */
   PSRun(); /* Start sonics          */
   PTSTimer = 0; /* Clear time value, now used for @Time for O/L*/
   DistFlag = FALSE; /* Clear flag in case downspeed stepping is on */
   PTSFlag = TRUE; /* Indicate pre-trigger has in fact started    */
}

void TestForOverload(void)
/***************************************************************************/
/*                                                                         */
/* This function check for overload while pre-trigger is on.  It will keep */
/* track of peak power an record the frequency when an overload occurs.    */
/*                                                                         */
/***************************************************************************/
{
   PTSTimer++;
   if (CurrentPowerIn > (UINT32)OverloadPower)
   {
      OverloadPower = CurrentPowerIn;
   }
   if (Inp.OL == TRUE)
   { /* If overload detected save frequency */
      OverloadFreq = CurrentFreqIn;
   }
}

void TestTrs1D(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger.  It */
/*  will test for such things as second downspeed.                         */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE)
      TestForOverload();

   if ((RunningPreset.RTFlag & BIT0) == BIT0)
   {
      if ((EncoderPos >= RunningPreset.RTDist) && (PartContactFlag == FALSE)
            && (RTAlreadySetFlag == FALSE))
      {
    	  RapidTraverseOff();
         DistFlag = TRUE;
         RTAlreadySetFlag = TRUE;

      }
   } else
      DistFlag = TRUE;
   if (Inp.Trigger == TRUE)
   {
      DistFlag = TRUE;
   }
   CheckControlLimitsD(TRUE);
   CheckCycleAborts();
   CollectVelocityData(EncoderPos);

   // Missing Part => Max ="on" AND values are enabled.

   MissingPartFlag = CheckForMissingPartMax();
}

void TestTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger.  It */
/*  will test for such things as second downspeed.                         */
/*                                                                         */
/***************************************************************************/
{
   // need to add code when rapid traverse added
   if (Inp.Trigger == TRUE)
   {
      DistFlag = TRUE;
   }
   if (PTSFlag == TRUE)
      TestForOverload();

   CheckControlLimits();
   CheckCycleAborts();
}

void TestTrs2D(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger      */
/*  after the second downspeed has gone into effect.  It will wait for     */
/*  only trigger.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE)
      TestForOverload();

   CheckControlLimitsD(TRUE);
   CheckCycleAborts();
   CollectVelocityData(EncoderPos);
   if (PartContactFlag == TRUE)
   {
      CheckForSafety();
      UpdateDistanceOffset();
//      SetPV((UINT16) RunningPreset.WeldForce, TRG_TO_FORCE_A);
   }
   // Missing Part => Max ="on"  And value are enabled

   MissingPartFlag = CheckForMissingPartMax();

}

void TestTrs2(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger      */
/*  after the second downspeed has gone into effect.  It will wait for     */
/*  only trigger.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE)
      TestForOverload();

   CheckControlLimits();
   CheckCycleAborts();
}

void EnterUls(void)
/****************************************************************************/
/*                                                                          */
/*   This function will be executed when the upstroke is started.  It will  */
/*   check to see if actuator clear output is enabled.  If not enabled,     */
/*   ActClrFlag will be set allowing the state to end.  If actuator clear   */
/*   output is enabled, TestUlsUp will test the distance and when the       */
/*   actuator is high enough the ActClrFlag will be set, again allowing the */
/*   state to end.                                                          */
/*                                                                          */
/****************************************************************************/
{
   UlsTimeout = FALSE; /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0; /* Reset timer to zero              */
   PretriggerDelayTimer = 0;
   TotalCycleTime = 0; /* reset total cycle time           */
}

void TestUls(void)
{
   if (Inp.uls == FALSE)
   {
      HornReturnCount++;
      if (HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   if (UpperLimitTimer++ > UPPERLIMIT_TIMEOUT)
   {
      UlsTimeout = TRUE;

      /*---  If we timed out lets assume something went wrong somewhere, so    ---*/
      /*---  lets reset everything and reselect the weld sequence to recover.  ---*/

      TrigSwActv(); /* safety circuit input       */
      if ((GetCurrentSequenceType() != HORNDOWN) && (HornDownFlag == FALSE))
      {
         SelectWeldSequence(); /* Try redoing weld sequence  */
         StartStateMachine();
      }
   }
   CollectVelocityData(EncoderPos); /* Collect data BEFORE we clear ULS  */

   //   if (EncoderPos >= IDLE_TO_DOWNSPEED_DISTANCE) {
   //   if (EncoderPos >= (DistanceAtULS - DOWNSPEED_DISTANCE_OFFSET)) {     /* Test for last cycle distance to ULS */
   //      WeldingResults.ActualTotalCollapse = (DistanceAtULS - DOWNSPEED_DISTANCE_OFFSET);
   if ((/*StepAtRTDist.BitMask*/BIT0 & RunningPreset.RTFlag)
         == /*StepAtRTDist.BitMask*/BIT0)
              RapidTraverseOn();
   else
             RapidTraverseOff();


   /*  End of temp test code */
}

void EnterUlsUp(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initialize the variables which will be used in Test */
/*  UlsUp.                                                                 */
/*                                                                         */
/***************************************************************************/
{
   TriggerBounceTimer = 0;
   OKToAdvance = FALSE;
}

void TestUlsUp(void)
/****************************************************************************/
/*                                                                          */
/*  This function will be executed every ms while in the upstroke.  It      */
/*  check to see if actuator clear distance has been reached or if home     */
/*  has been reached.  If either of these cases happen the ActClrFlag       */
/*  will be set allowing the state to end.                                  */
/*  It will wait TRIGGERBOUNCETIME after Inp.uls is TRUE.  If               */
/*  trigger is gone, then the state will exit, otherwise an EQ4 alarm will  */
/*  result.                                                                 */
/*                                                                          */
/****************************************************************************/
{
   //   TestActClr();
   if (Inp.uls == FALSE)
   {
      if (++HornReturnCount > UPPERLIMIT_TIMEOUT)
      {
         HornReturnFlag = FALSE;
      }
   } else
   {
      // make sure AE actuator with trigger switch
      if (CurrentSetup.Actuator == AE)
      {
         if (++TriggerBounceTimer > TRIGGERBOUNCETIME)
         {
            Inp.Trigger = FALSE;
            OKToAdvance = TRUE;
         }
      } else
      {
         OKToAdvance = TRUE;
      }
   }
}

void RecordAlarm(UINT32 AlarmCode)
/****************************************************************************/
/*                                                                          */
/*  This function will take the passed AlarmCode and set the proper bit in  */
/*  the FinalResults structure.  If needed it will also output the reject,  */
/*  suspect or system fault signals.  The UpdateAlarm function will be      */
/*  called in case the run screen is being displayed.  This will ensure     */
/*  alarm will get displayed immediately.  If the alarm bit is already set  */
/*  the UpdateDisplay function will NOT be called to prevent pSOS from      */
/*  getting backed up.                                                      */
/*                                                                          */
/****************************************************************************/
{
   UINT32 AlarmType;
   UINT16 RejectFlag = FALSE, SuspectFlag = FALSE;
   UINT16 NotReadyFlag = FALSE, WarningFlag = FALSE;
   UINT16 OverloadFlag = FALSE, NoCycleFlag = FALSE;
   UINT16 MissingPartOut = FALSE, ModifiedFlag = FALSE;
   UINT16 UpdatedDisplayFlag;
   CONFIGSETUP *SetupPtr;
   UINT32 CurrAlarmCode = AlarmCode;

   SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

   if (AlarmCounter < (MAXSUBMENUS - 1))
   {
      ResetReceivedFlag = FALSE; /* Remove evidence of reset pressed */
      UpdatedDisplayFlag = FALSE;
      AlarmType = (AlarmCode & ALARMTYPEMASK); /* Get what type of alarm     */
      AlarmCode = (AlarmCode & ALARMCODEMASK); /* Strip off type of alarm    */
      switch (AlarmType)
      {
      case PSG1: /* Process Suspect Alarms     */
         if ((AlarmPtrRam.Suspect & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.SuspectBitResult & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               /* Count bits set in AlarmCode and NOT in WeldingResults */

               WeldingResults.SuspectBitResult |= AlarmCode;
               SuspectFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case PRG1: /* Process Reject Alarms      */
         if ((AlarmPtrRam.Reject & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.RejectBitResult & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               /* Count bits set in AlarmCode and NOT in WeldingResults */

               WeldingResults.RejectBitResult |= AlarmCode;
               RejectFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case OLG1: /* Overload Alarms - Group 1  */
         if ((AlarmPtrRam.Overload & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.OverloadAlarms & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               StartDUPSDataCollection(); /* All O/L's attempt to get data from DUPS */
               WeldingResults.OverloadAlarms |= AlarmCode;
               OverloadFlag = TRUE;
               if (AlarmCode & OL_INC_COUNTER)
               { /* Increment counter if necessary */
                  CurrentSetup.Overload++;
                  SetupPtr->Overload = CurrentSetup.Overload; /* Update FRAM */
               }
               if ((OL_REJECT & AlarmCode) != FALSE)
                  RejectFlag = TRUE;
               if ((OL_CYCLE_ABORT & AlarmCode) != FALSE)
                  CycleAbort = TRUE;
               SonicsAbort = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case NCG1: /* No Cycle Alarms - Group 1  */
         if ((AlarmPtrRam.NoCycle & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.NoCycleAlarms & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               WeldingResults.NoCycleAlarms |= AlarmCode;
               NoCycleFlag = TRUE;
               if (AlarmCode == (NC8 & ALARMCODEMASK))
                  MissingPartOut = TRUE;
               RejectFlag = TRUE;
               CycleAbort = TRUE;
               AbortFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case EQG1: /* Equipment Failure Alarms   */
         if ((AlarmPtrRam.EquipmentFailure & AlarmCode) == AlarmCode)
         {
            if (((FinalResults.EquipmentFailureAlarms & AlarmCode) == AlarmCode)
                  && ((AlarmCode & EQ_UPDATE_OFTEN) == 0))
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               WeldingResults.EquipmentFailureAlarms |= AlarmCode;
               if ((EQ_NOT_READY & AlarmCode) != FALSE)
                  NotReadyFlag = TRUE;
               if ((EQ_REJECT & AlarmCode) != FALSE)
                  RejectFlag = TRUE;
               if ((EQ_NO_CYCLEABORT & AlarmCode) != FALSE)
                  CycleAbort = TRUE;
               if ((EQ_CYCLE_ABORT & AlarmCode) != FALSE)
			       AbortFlag = TRUE;
               SonicsAbort = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case CMG1: /* Cycle Modified Alarms      */
         if ((AlarmPtrRam.CycleModified & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.CycleModifiedAlarms & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               WeldingResults.CycleModifiedAlarms |= AlarmCode;
               if ((CM_CYCLE_ABORT & AlarmCode) != FALSE)
                  CycleAbort = TRUE;
               if ((CM_SONICS_ABORT & AlarmCode) != FALSE)
                  SonicsAbort = TRUE;
               RejectFlag = TRUE;
               ModifiedFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case WAG1: /* Warnings - Group 1         */
         if ((AlarmPtrRam.Warning & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.Warnings & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               WeldingResults.Warnings |= AlarmCode;
               if ((WA_SONICS_ABORT & AlarmCode) != FALSE)
                  SonicsAbort = TRUE;
               WarningFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case CAG1: /* Calibration Alarms         */
         if ((AlarmPtrRam.Calibrate & AlarmCode) == AlarmCode)
         {
            if ((WeldingResults.CalibrateAlarms & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               WeldingResults.CalibrateAlarms |= AlarmCode;
               RejectFlag = TRUE;
               NotReadyFlag = TRUE;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case 0:
         UpdatedDisplayFlag = TRUE;
         break;

      default:
         break;

      }
      if (CycleAbort == TRUE)
      {
         StopDataCollection();
         //         if (WeldingResults.ActualWeldTime <= 5) { /* No graphing unless  */
         //            DontPrintGraph = TRUE;                 /* TRS reached         */
         //         }
      }
      AlarmsReset = FALSE; /* Stop state machine until reset  */
      if (RejectFlag == TRUE)
         RejectOn(); /* Activate the Reject signal      */
      if (SuspectFlag == TRUE)
         SuspectOn(); /* Activate the Suspect signal     */
      if (NotReadyFlag == TRUE)
      {
         ClearReady(); /* Remove the Ready signal         */
      }
      if (WarningFlag == TRUE)
         UserCfgOutputOn(OUTPUT_NOTE); /* Activate the Warning output     */
      if (ModifiedFlag == TRUE)
         UserCfgOutputOn(OUTPUT_MDFY_ALARM);/* Activate the ModifiedAlarm signal */
      if (OverloadFlag == TRUE)
         UserCfgOutputOn(OUTPUT_OLDALARM);/* Activate the OverloadAlarm signal */
      if (NoCycleFlag == TRUE)
         UserCfgOutputOn(OUTPUT_NO_CYCLEALARM);/* Activate the NoCycleAlarm signal */
      if (MissingPartOut == TRUE)
         UserCfgOutputOn(OUTPUT_MISSING_PART);/* Activate the MissingPartAlarm signal */

      if (UpdatedDisplayFlag == FALSE)
      {
    	 WriteAlarmLog(CurrAlarmCode, false);
         AlarmCounter++;
         AlarmOn(); /* Turn Reset led on               */
         if (AlarmType != WAG1) /* Warnings dont SetGeneralAlarm flag*/
         {
            /* General alarm counter will increment if system isn't running */
            /* a cycle (OkToDisplayAlarms) or if PBs have been pressed but */
            /* there have been no alarms recorded so far. */

            if (OkToDisplayAlarms || !CheckGeneralAlarmFlag())
            {
               CurrentSetup.GenAlarmCount++;
               SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount; /* Update FRAM */
            }

            SetAlarmFlag(); /* Set general alarm output */
         } else
            Beep(ALARMBEEP); /* Warnings sound the beeper         */
         UpdateAlarm(); /* Send message in case screen=Run   */
      }
   }
}

void RecordSetupAlarm(UINT32 AlarmCode)
/****************************************************************************/
/*                                                                          */
/*  This function will take the passed AlarmCode and set the proper bit in  */
/*  the SetupData structure. It is assumed that the code passed to this     */
/*  function is in fact a setup alarm code.  If it isn't, this function     */
/*  has no way of knowing and it will be decoded as though it is.  So be    */
/*  careful!                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 UpdatedDisplayFlag;
   UINT32 AlarmType;
   CONFIGSETUP *SetupPtr;

   SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   UINT32 CurrAlarmCode = AlarmCode;
   if (AlarmCounter < (MAXSUBMENUS - 1))
   {
      ResetReceivedFlag = FALSE; /* Remove evidence of reset pressed */
      SetupAlarmFlag = TRUE;
      UpdatedDisplayFlag = FALSE;
      AlarmType = (AlarmCode & ALARMTYPEMASK); /* Get what type of alarm     */
      AlarmCode = (AlarmCode & ALARMCODEMASK); /* Strip off type of alarm    */
      switch (AlarmType)
      {
      case SEG1: /* Setup Alarms - Group 1     */
         if ((AlarmPtrRam.SetupGroup1 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms1 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms1 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG2: /* Setup Alarms - Group 2     */
         if ((AlarmPtrRam.SetupGroup2 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms2 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms2 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG3: /* Setup Alarms - Group 3     */
         if ((AlarmPtrRam.SetupGroup3 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms3 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms3 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG4: /* Setup Alarms - Group 4     */
         if ((AlarmPtrRam.SetupGroup4 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms4 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms4 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG5: /* Setup Alarms - Group 5     */
         if ((AlarmPtrRam.SetupGroup5 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms5 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms5 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG6: /* Setup Alarms - Group 6     */
         if ((AlarmPtrRam.SetupGroup6 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms6 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms6 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG7: /* Setup Alarms - Group 7     */
         if ((AlarmPtrRam.SetupGroup7 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms7 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms7 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG8: /* Setup Alarms - Group 8     */
         if ((AlarmPtrRam.SetupGroup8 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms8 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms8 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG9: /* Setup Alarms - Group 9     */
         if ((AlarmPtrRam.SetupGroup9 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms9 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms9 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case SEG10: /* Setup Alarms - Group 10    */
         if ((AlarmPtrRam.SetupGroup10 & AlarmCode) == AlarmCode)
         {
            if ((SetupData.SetupErrorAlarms10 & AlarmCode) == AlarmCode)
            {
               UpdatedDisplayFlag = TRUE;
            } else
            {
               SetupData.SetupErrorAlarms10 |= AlarmCode;
            }
         } else
            UpdatedDisplayFlag = TRUE;
         break;

      case 0:
         UpdatedDisplayFlag = TRUE;
         break;

      default:
         break;
      }
      AlarmsReset = FALSE; /* Stop state machine until reset  */
      if (UpdatedDisplayFlag == FALSE)
      {
         AlarmCounter++;
         WriteAlarmLog(CurrAlarmCode, true);
         AlarmOn(); /* Turn Reset led on               */
         if (!CheckGeneralAlarmFlag())
         { /* Increment only on first alarm */
            CurrentSetup.GenAlarmCount++;
            SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount; /* Update FRAM */
         }
         SetAlarmFlag();
         UpdateAlarm(); /* Send message in case screen=Run */
      }
   }
}

UINT16 ClearAlarm(UINT32 AlarmCode)
{
   /****************************************************************************/
   /*                                                                          */
   /*  This function will clear hardware resettable alarms.  A TRUE will be    */
   /*  returned if the alarm can be cleared (i.e. the hardware condition       */
   /*  causing the alarm has been fixed).  A FALSE will be returned if the     */
   /*  alarm has not been fixed.                                               */
   /*                                                                          */
   /*  2.127  08-27-97  BEKymer    Changed assumption on ClearedHardwarealarm  */
   /*  2.136  09-18-97  BEKymer    Added palm button check to ClearAlarm       */
   /*                                                                          */
   /****************************************************************************/

   UINT16 AlarmClearedThisPass = FALSE;

   ClearedHardwareAlarm = TRUE; /* Assume everything is OK for now  */

   /*---   Start checking Door switch (Dont clear unless reset pressed  ---*/

   if ((AlarmCode & DOOR_TRIG_FAIL) == DOOR_TRIG_FAIL)
   {
      if (CurrentSetup.Actuator == AE)
      {
         if (AETrigger == FALSE)
         {
            if (ResetReceivedFlag == TRUE)
            {
               WeldingResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
               FinalResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
            }
            TestModeAllowed = TRUE; /* Test mode ok now, door is shut  */
         } else
         {
            TestModeAllowed = FALSE; /* Door open, DONT ALLOW TEST MODE */
            ClearedHardwareAlarm = FALSE;
         }
      } else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) {
			if (ResetReceivedFlag == TRUE)
			{
			   WeldingResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
			   FinalResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
			}
			TestModeAllowed = TRUE; /* Test mode ok now, door is shut  */
      }
   }

   /*---   Next check for Upper limit (Only clear if reset pressed)  ---*/

   if ((AlarmCode & ULS_FAIL) == ULS_FAIL)
   {
      if (Inp.uls == TRUE)
      {
         if (ResetReceivedFlag == TRUE)
         {
            WeldingResults.EquipmentFailureAlarms &= ULS_FAIL_RESET;
            FinalResults.EquipmentFailureAlarms &= ULS_FAIL_RESET;
            AlarmClearedThisPass = TRUE;
         }
      } else
         ClearedHardwareAlarm = FALSE;
   }

   /*---   Now check for Upper limit return   ---*/

   if ((AlarmCode & ULSRETURN_FAIL) == ULSRETURN_FAIL)
   {
      if (Inp.uls == TRUE)
      {
         WeldingResults.EquipmentFailureAlarms &= ULSRETURN_FAIL_RESET;
         FinalResults.EquipmentFailureAlarms &= ULSRETURN_FAIL_RESET;
         AlarmClearedThisPass = TRUE;
      } else
      {
         ClearedHardwareAlarm = FALSE;
      }
   }

   /*---   Next check for Wrong Actuator  ---*/

   if ((AlarmCode & WRONG_ACTUATOR_FAIL) == WRONG_ACTUATOR_FAIL)
   {
      ClearedHardwareAlarm = FALSE;
   }

   /*--  Next check for overloads (Dont clear Thermal unless Reset pressed)  --*/

   if (ResetReceivedFlag == TRUE)
   {
      if (Inp.OL == TRUE)
      { /* If overload is still there,   */
         PSReset(); /* attempt to reset again        */
         ClearedHardwareAlarm = FALSE;
      } else
      {
         WeldingResults.EquipmentFailureAlarms &= THERMALOVERLOADS_RESET;
         WeldingResults.OverloadAlarms &= TESTOVERLOAD_RESET;
         WeldingResults.OverloadAlarms &= (OL_RESET_IS_NEEDED
               & OL_RESET_NOT_NEEDED);
      }
   }

   /*---   Now check for start switches still held   ---*/

   if (WeldState != PBSTATE)
   { /* Should be held in PBSTATE */
      if (Inp.OnePB == TRUE)
      {
         ClearedHardwareAlarm = FALSE;
      } else
      {
         WeldingResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
         if (ResetReceivedFlag == TRUE)
         {
            FinalResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
         }
      }
   } else
   {
      WeldingResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
      if (ResetReceivedFlag == TRUE)
      {
         FinalResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
      }
   }

   /*---   Check for Calibrate Actuator alarm (EQ20)  It cant be cleared   ---*/

   if (((FinalResults.EquipmentFailureAlarms & EQ20) != FALSE) || /* Check both FinalResults and */
   ((WeldingResults.EquipmentFailureAlarms & EQ20) != FALSE))
   { /* WeldingResults because either */
      ClearedHardwareAlarm = FALSE; /* could be set depending on   */
   } /* reason for alarm.           */

   /*--- If any alarms were cleared this time, and reset was not pressed  ---*/
   /*--- tell system manger so the run screen count can be updated.       ---*/

   if (AlarmClearedThisPass == TRUE && ResetReceivedFlag == FALSE)
   {
      UpdateAlarm();
   }

   return (ClearedHardwareAlarm);
}

void TestTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called every ms while in test mode.  It will turn off */
/*  sonics after the proper time has elapsed, if the reset key has not     */
/*  been pressed.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (CheckIfResetRequired() == FALSE)
   {
      AlarmsReset = TRUE;
   }
   if (TestModeAllowed == TRUE)
   {
      if (PSResetDelay > 0)
      {
         PSResetDelay--;
      } else if (ResetReceivedFlag == FALSE)
      { /* Dont keep sonics on if reset pressed */
         PSTest(); /* Start the sonics                */
      }
      PowerTest = PwrTestFilter(CurrentPowerIn); // Display Filtered Power during Test

      // Now they don't want to see PeakPower during test DCS-2265
      // if (PowerTest > PeakTestPower) PeakTestPower = PowerTest;

      DisplayTestPower(PowerTest); // Display test mode power reading

      if (Inp.PSRun == TRUE)
         LatchPSRun = TRUE;

      if (Inp.PSSeek == TRUE)
         LatchPSSeek = TRUE;

      if (Inp.PSClear == TRUE)
         LatchPSClear = TRUE;

      if (Inp.PSStore == TRUE)
      {
         Inp.PSStore = FALSE;
         LatchPSStore = TRUE;
         VGALatchPSStore = 2;
      }

      TestTime++;
      TestTimerCounter++;
      if (TestTimerCounter >= MAXTESTTIME)
         TestTimerFlag = TRUE;

      if (--TestCountDown <= 0)
      {
         TestCountDown = 250;
         if (VGALatchPSStore)
            VGALatchPSStore--;
         SendFakeKeyPress(UPDATEDISPLAY); /* Tell menu system to update   */
      }
   }
}

void EnterTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when test mode is first started.  It will      */
/*  start a timer which will be used to check the length of time sonics    */
/*  are on, in case the reset key is not pressed in time.                  */
/*                                                                         */
/***************************************************************************/
{
   ClearReady(); /* Remove Welder Ready signal       */
   TestCountDown = 250;
   TestTimerFlag = FALSE; /* Make sure flag is clear          */
   if (TestModeAllowed == TRUE)
   {
      FrequencyStart = CurrentFreqIn;
      TestTime = 0;
      TestTimerCounter = 0; /* Reset timer                      */
      PowerTest = 0; /* Clear old power value            */
      PeakTestPower = 0; /* Clear old peak power value       */
      TestPwrSum = 0;
   } else
   {
      PSIdle(); /* Make sure sonics are off         */
      TestTimerCounter = MAXTESTTIME; /* Reset timer                      */
   }
}

void ExitTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when sonics need to be turned off in test      */
/*  mode.  You can get here because the user pressed the reset key, the    */
/*  power supply overloaded or the test timer has expired.                 */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;
   // DisplayTestPower(PeakTestPower); DCS 2265
   for (i = 0; i <= 15; i++)
   {
      BuffPwrTst[i] = 0;
   }
   FreqChg = CurrentFreqIn - FrequencyStart;
   PSIdle();
   StartTestFlag = FALSE;
   /* Test for overload and DUPS present */
}

void EnterFData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag so SendFData can deal with       */
/*   actually sending the final data and then leaving quickly.              */
/*                                                                          */
/****************************************************************************/
{
   OkToDisplayAlarms = TRUE;
   OKToAdvance = FALSE;
   InitTimer(); /* Reset all timers for next weld cycle */
}

void ConfirmRejectEntry(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag If last weld has any Reject Alarm*/
/*   So ConfirmRejectST can wait for ConfirmReject Input. ConfirmRejectST  */
/*   state will jump immediately if there is no Reject Alarm.                 */
/****************************************************************************/
{
	WaitForRejectConfirm = FALSE;
	if(WeldingResults.RejectBitResult & REJECTBITRESULTMASK)
		WaitForRejectConfirm = TRUE;
}

void SendFData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will put the final data into a structure and then send   */
/*   a pointer to that structure to the weld manager.                       */
/*                                                                          */
/*   It will also take care of the weld counter.                            */
/*                                                                          */
/*   Final data will only be sent if we reached trigger.  This is decided   */
/*   by looking at the weld time.  If it is greater than 0, we must have    */
/*   triggered, so send the data.                                           */
/*                                                                          */
/****************************************************************************/
{
   CONFIGSETUP *SetupPtr;
   SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   if (WeldingResults.ActualWeldTime > 0)
   { /* If not 0, then we triggered */
      /*----  Here deal with incrementing the weld counters  ----*/

      CurrentSetup.PSLifetime++;
      SetupPtr->PSLifetime = CurrentSetup.PSLifetime; /* Update FRAM */
      if (CurrentSetup.AdvanceCounters == TRUE)
      { /* TRUE: all cycles */
         WeldingResults.CycleCount++;
      } else if (CheckGeneralAlarmFlag() == FALSE)
      {
         WeldingResults.CycleCount++;
      }

      //Batch Count Handling
      if(RunningPreset.BatchFunction == TRUE)//batch function enabled
      {
    	  if(CheckGeneralAlarmFlag() == FALSE)//If no alarm increment the batch count
    		  RunningPreset.CurrBatchCount++;
    	  else if(RunningPreset.BatchCountWithAlarm == TRUE)//else do it based on configuration
    		  RunningPreset.CurrBatchCount++;

    	  CurrentPreset.CurrBatchCount = RunningPreset.CurrBatchCount;

      }

      FramVerInfo.PollingCommandCounter++;
      if (CurrentSetup.SequenceEnable == TRUE && CurrentSetup.SequenceCount
            != 0)
      {
         CurrentSetup.SequenceNos++;
         CurrentSetup.SequenceNos %= CurrentSetup.SequenceCount;
      }

#ifdef TRIGGER_FORCE_TEST

      WeldingResults.TrigForce = ActualTriggerForce;
      WeldingResults.ActualWeldCollapse = WeldingResults.ActualTriggerDistance;

#endif

      strncpy((char*)&WeldingResults.PSAssemblyNum,(char*)&RunningPreset.PSAssemblyNum, sizeof(WeldingResults.PSAssemblyNum) - 1);
      strncpy((char*)&WeldingResults.ActAssemblyNum,(char*)&RunningPreset.ActAssemblyNum, sizeof(WeldingResults.ActAssemblyNum) - 1);
      strncpy((char*)&WeldingResults.StackAssemblyNum,(char*)&RunningPreset.StackAssemblyNum, sizeof(WeldingResults.StackAssemblyNum) - 1);
      if(CurrentSetup.Automation == ON)
    	  strncpy((char*)&WeldingResults.UserId,AutomationUsrId, sizeof(CurrentUser.UserId) - 1);
      else
    	  strncpy((char*)&WeldingResults.UserId,CurrentUser.UserId, sizeof(CurrentUser.UserId) - 1);
      WeldingResults.PresetValidated = RunningPreset.Validated;
      WeldingResults.PresetRev  = RunningPreset.Rev;
      strncpy(WeldingResults.UDIScan,UDIString, sizeof(WeldingResults.UDIScan) - 1);
      memcpy(&FinalResults, &WeldingResults, sizeof(WeldingResults));
      WeldingResultsPtr = &WeldingResults;
      end_weld_msg.common.opcode = OP_WELDER_STATE_CHANGE;
      end_weld_msg.common.source_task = WC_ISR_TASK;
      end_weld_msg.state = FINALDATASTATE;
      end_weld_msg.weld_samples = 1;
      end_weld_msg.weld_data_ptr = WeldingResultsPtr;

      ChangeDataStorage(); /* Change data storage address */
      WeldManagerTask::thisPtr->WELDMNGRTaskQ.Write(0, *((WMGR_MSG_QUEUE_TYPE*) &end_weld_msg), 0);
      // Activate Cycle Okay signal if no alarm is recorded.
      if (!CheckAlarmFlag())
         UserCfgOutputOn(OUTPUT_CYCLE_OK);
      /*If ultrasonics were disabled by the user input 
       signal during the weld cycle the record 'Sonic Disabled' alarm.*/
      if (SonicDisabledFlag)
         RecordAlarm(W11);
   }
   OKToAdvance = TRUE;

}

void UpdateAlarm(void)
/****************************************************************************/
/*                                                                          */
/*   This function will allow the display to be updated with new data, even */
/*   if final data is not available.  This will allow alarms to be shown    */
/*   on the run screen even if a cycle has not been completed.              */
/*                                                                          */
/****************************************************************************/
{

   end_weld_msg.common.opcode = OP_WELDER_STATE_CHANGE;
   end_weld_msg.common.source_task = WC_ISR_TASK;
   end_weld_msg.state = UPDATEALARMSTATE;
   end_weld_msg.weld_samples = 1;
   end_weld_msg.weld_data_ptr = WeldingResultsPtr;
   WeldManagerTask::thisPtr->WELDMNGRTaskQ.Write(0, *((WMGR_MSG_QUEUE_TYPE*) &end_weld_msg), 0);

}

UINT16 CheckIfResetRequired(void)
/****************************************************************************/
/*                                                                          */
/* This function will check to see if a reset is required.  If a reset is   */
/* required then a TRUE will be returned, otherwise a FALSE will be         */
/* returned.                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 ResetRequiredFlag = FALSE; /* Assume reset not required */
   UINT16 ClearFlag = TRUE; /* Assume condition is fixed */

   if (AlarmFlag == TRUE)
   {

      /*---  Here, check alarms which always require reset  ---*/

      if (((FinalResults.OverloadAlarms & OL_RESET) != 0)
            || ((FinalResults.EquipmentFailureAlarms & EQ_NO_RESET) != 0)
            || ((FinalResults.EquipmentFailureAlarms & EQ_RESET) != 0)
            || ((FinalResults.CalibrateAlarms & CA_NO_RESET) != 0))
      {
         ResetRequiredFlag = TRUE;
         if (ClearAlarm(FinalResults.EquipmentFailureAlarms) == FALSE)
         {
            ClearFlag = FALSE;
         }
      }

      /*--  Check alarms which require reset only if Reset Required = On  --*/

      if (RunningPreset.GeneralAlarmLFlag == TRUE)
      { /* See if globally required */
         if (((FinalResults.NoCycleAlarms & NC_NOT_REQ_RESET) != 0)
               || ((FinalResults.OverloadAlarms & OL_NOT_REQ_RESET) != 0)
               || ((FinalResults.EquipmentFailureAlarms & EQ_NOT_REQ_RESET)
                     != 0) || ((FinalResults.CycleModifiedAlarms
               & CM_NOT_REQ_RESET) != 0) || (FinalResults.RejectBitResult != 0)
               || (FinalResults.SuspectBitResult != 0)
               || (FinalResults.CalibrateAlarms != 0))
         {
            ResetRequiredFlag = TRUE;
         }
      }

      /*--   Here check for alarms which cant be reset as well as those which   --*/
      /*--   require reset.                                                     --*/

      if (RunningPreset.SusResetRequired == TRUE)
      {
         if (FinalResults.SuspectBitResult != 0)
         {
            ResetRequiredFlag = TRUE;
         }
      }
      if (RunningPreset.RejResetRequiredFlag == TRUE)
      {
         if (FinalResults.RejectBitResult != 0)
         {
            ResetRequiredFlag = TRUE;
         }
      }
      if (ResetReceivedFlag == TRUE)
      {
         if (ClearFlag == TRUE)
         {
            AlarmOff(); /* Turn off Reset led               */
            ClearGeneralAlarm(); /* Remove GeneralAlarm,suspect,&reject signals*/
            ResetRequiredFlag = FALSE;
            ClearAlarmFlag();
            ResetReceivedFlag = FALSE; /* Clear signs of reset press   */
         }
         ResetReceivedFlag = FALSE; /* Clear signs of reset press   */
      }
   }
   return (ResetRequiredFlag);
}

void ClearCalibrationAlarms(void)
/****************************************************************************/
/*                                                                          */
/*  This function will clear all calibration related alarms.  This should   */
/*  be called only after a successful calibration has been done.  If any    */
/*  calibration alarms exist, they will be cleared and the reset key will   */
/*  be pressed.  If any other alarms exist a reset key will be pressed to   */
/*  clear those as well. The Errorcode and Errorcodeflag need to be reset.  */
/*                                                                          */
/****************************************************************************/
{

   ErrorCode = (ERRORCODE_ARG) 0;
   ErrorCodeFlag = FALSE;
   if (((FinalResults.EquipmentFailureAlarms & EQ4) != 0) || /* If door/trg fail  */
   ((FinalResults.Warnings & W8) != 0) || /* or cal warning    */
   ((FinalResults.EquipmentFailureAlarms & EQ20) != 0) || /* or calib required */
   (AlarmFlag == TRUE)) /* or any other alarm*/
   {
      FinalResults.EquipmentFailureAlarms &= RESET_CALIBRATION_ALARMS;
      FinalResults.Warnings &= RESET_CALIBRATION_WARNINGS;

      WeldingResults.Warnings &= RESET_CALIBRATION_WARNINGS;
      WeldingResults.EquipmentFailureAlarms &= RESET_CALIBRATION_ALARMS;
      if ((WeldState != READYSTATE) && (WeldState != PREREADYSTATE))
         WeldState = PREREADYSTATE;
      SendKeyToWeldMngr(OP_RESET_KEY_PRESSED, 0);
   }
}

void TestActClr(void)
/****************************************************************************/
/*                                                                          */
/*   This function will be executed every ms.  It will check to see if the  */
/*   actuator clear distance has been reached if the actuator clear is on   */
/*   or if home has been reached if actuator clear is off.  If either of    */
/*   these cases happen the ActClrFlag will be set allowing the state to    */
/*   end.  However, if ULS is reached (and actuator clear is on) before the */
/*   distance is reached an alarm will be created.                          */
/*                                                                          */
/*    60.2.116 07-21-97  BEkymer    Change logic in TestActClr              */
/*                                                                          */
/****************************************************************************/
{
   SINT32 LocalEncoder = EncoderPos;

   if (RunningPreset.ActClrFlag == TRUE)
   { /* Actuator Clear function is ON */

      /*------------  Linear Encoder here  ------------*/

      if ((CurrentSetup.Actuator == AED)
           || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (RunningPreset.ActClrDistance > LocalEncoder)
         {
            ActClrOn();

         } else
         {
            if (Inp.uls == TRUE)
            {
               ActClrOn();
               ActClrFlag = TRUE;
            } else
            {
               ActClrOff();
            }
         }
      } else
      { /* Actuator Clear function is on, but its only an ae actuator, so use ULS */
         if (Inp.uls == TRUE)
            ActClrOn();
         else
            ActClrOff();
      }
   } else
   { /* Actuator Clear function is OFF */
      if (Inp.uls == TRUE)
         ActClrOn();
      else
         ActClrOff();
   }
}

void ClearFinalResults(void)
{
   WeldingResults.ActualFreqEnd = 0;
   WeldingResults.ActualFreqStart = 0;
   WeldingResults.FrequencyChange = 0;
   WeldingResults.FrequencyMin = 50000; /* initialize to maximum */
   WeldingResults.FrequencyMax = 0;
   WeldingResults.TotalEnergy = 0;
   WeldingResults.ActualWeldAbs = 0;
   WeldingResults.ActualTotalAbs = 0;
   WeldingResults.ActualTriggerDistance = 0;
   WeldingResults.ActualTotalCollapse = 0;
   WeldingResults.ActualWeldCollapse = 0;
   WeldingResults.ActualDownspeed = 0;
   WeldingResults.SetPressureB = RunningPreset.Pressure2;
   WeldingResults.SetPressureA = RunningPreset.WeldPressure;
   WeldingResults.HoldForceEnd = 0;
   WeldingResults.WeldForceEnd = 0;
   WeldingResults.ActualAmplitudeStart = 0;
   WeldingResults.ActualAmplitudeEnd = 0;
   WeldingResults.PeakPower = 0;
   WeldingResults.ActualWeldTime = 0;
   WeldingResults.TrigForce = RunningPreset.TriggerForce;
   WeldingResults.PSActControlFlags = CurrentSetup.AmpControl;
   if ((RunningPreset.Amp2Flag & BIT0) == BIT0)
   { /* If stepping on     */
      WeldingResults.PSActControlFlags |= BIT1; /* set BIT1           */
   }
   if ((RunningPreset.Pressure2Flag & BIT0) == BIT0)
   { /* If stepping on     */
      WeldingResults.PSActControlFlags |= BIT4; /* set BIT4           */
   }
   if ((CurrentSetup.FreqControl & BIT0) == BIT0)
   { /* If Freq=internal   */
      WeldingResults.PSActControlFlags |= BIT2; /* set BIT2           */
   }
   WeldingResults.PSActControlFlags &= ~BIT5;
   if ((RunningPreset.HoldTimeFlag & BIT0) == FALSE)//if hold time is active
	   WeldingResults.PSActControlFlags |= BIT5;
   if (ClearAlarm(WeldingResults.EquipmentFailureAlarms) == TRUE)
   {
      WeldingResults.EquipmentFailureAlarms = 0;
   }
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.CycleModifiedAlarms = 0;
   WeldingResults.Warnings = 0;
   WeldingResults.PresetNum = 0;
   WeldingResults.PresetName[0] = NULL;
   WeldingResults.CycleTimeResult = 0;

   MsDataPtr->AmpStepAtTime = 0;
   MsDataPtr->PressureStepAtTime = 0;
   MsDataPtr->HoldEndAtTime = 0;
   MsDataPtr->SeekEndAtTime = 0;
   MsDataPtr->PrintBottomFlags |= ALLALARMMASK; /* Assume all will fail */
}

//--------------------------Power Filter During Test----------------------
//
//   This function accepts CurrentPowerIn as an argument, and returnes
//   the average of the last 16 previous elements. 
// 
//------------------------------------------------------------------------

UINT32 PwrTestFilter(UINT32 Element)
{
   UINT32 temp;
   if (ptst == &BuffPwrTst[FilterIndex16 - 1])
   {
      temp = *ptst; // It was the last element
      *ptst = Element;
      ptst = &BuffPwrTst[0];
   } else
   {
      temp = *ptst; // It was the last element
      *ptst = Element;
      ++ptst;
   }
   TestPwrSum = TestPwrSum + Element - temp;// !
   return (TestPwrSum >> 4); // Devide by 16;  --> 0000
}

void RecordErrorCode(enum ERRORCODE_ARG ErrorCodeArg)
/****************************************************************************/
/*                                                                          */
/* It will take the passed argument and  put it in the public variable      */
/* ErrorCode and set ErrorCodeFlag to True, unless ErrorCode is non-zero,   */
/* but always if ErrorCodeArg is AED upgrade error, which takes precedence  */
/* over all other errors.                                                   */
/*                                                                          */
/****************************************************************************/
{
   if (ErrorCode == 0 || ErrorCodeArg == ERRORCODE1100_EQ20 || ErrorCodeArg
         == ERRORCODE1200_EQ20)
   {
      ErrorCode = ErrorCodeArg;
      ErrorCodeFlag = TRUE;
   }
}

void EnterExtTrigDly(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag so TestExtTrigDly can deal       */
/*   to wait in this state untill the Inp.ExtTrgDelay input becomes low.    */
/*                                                                          */
/****************************************************************************/
{
   ExtTriggerDelayTimer = 0;
   TrgDelayTimeout = FALSE;
   WeldingResults.ActualTriggerDistance = EncoderPos; /* Save position for coll calc */

}

void TestExtTrigDly(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for external     */
/*  trigger delay input becomes low.If the input doesn't deactivates in    */
/*  30 seconds this will record the alarm and abort the cycle.             */
/*                                                                         */
/***************************************************************************/
{
   if (ExtTriggerDelayTimer++ > EXT_TRGDELAY_TIMEOUT)
      TrgDelayTimeout = TRUE;

   TriggerLostFlag = CheckForTriggerLost();
}

void EnterPartClamp(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initialize the flag so Test PartClamp Input can check for the */
/*   Inp.PartClamped input.                                                 */
/*                                                                          */
/****************************************************************************/
{
   PartClampTimer = 0;
   PartClampTimeout = FALSE;
   /*Make PartClampled Output High*/
   PartClampOutOn();
}

void TestPartClampInput(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for PartClamped  */
/*  input becomes active.                                                  */
/*                                                                         */
/***************************************************************************/
{
   if(Inp.BothPB==FALSE){
	  PartClampOutOff();
   }
   if (PartClampTimer++ > CurrentSetup.PartClampDelay){
      PartClampTimeout = TRUE;
	  PartClampOutOff();
   }
}

void ExitPartClampState(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed when exit from the SVInterlock state.   */
/*  This fuction will cause to move the horn down.                         */
/*                                                                         */
/***************************************************************************/
{
   EnableSVOn(); /* Enable SV valve                 */
   SVOn(); /* Turn on SV to bring down hown   */
}
