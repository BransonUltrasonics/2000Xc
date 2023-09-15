/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/preset.cpp_v   1.43   Nov 16 2017 16:11:26   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/preset.cpp_v  $
 * 
 *    Rev 1.43   Nov 16 2017 16:11:26   RJamloki
 * Apply formula slow when micro c actuator is active
 * 
 *    Rev 1.42   Oct 10 2017 12:58:12   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.41   09 May 2016 14:21:42   RJamloki
 * Added CurrentSetup.SerialPort with RS232DISABLED
 * 
 *    Rev 1.40   08 Apr 2015 13:45:06   AnPawar
 * Changes for Pressure Stepping. 
 * 
 *    Rev 1.39   27 Mar 2015 11:09:16   amaurya
 * Readpreset() change ,NUM_USERPRESETS_FRAM macro is defined against numeric value of 32.
 * 
 *    Rev 1.38   11 Mar 2015 09:17:48   amaurya
 * SetMaxMinValues() changed to assign default values to setup limit parameters.
 * 
 *    Rev 1.37   30 Jan 2015 08:10:28   amaurya
 * Default min and max limit for HoldPressureFlag added.
 * 
 *    Rev 1.36   08 Jan 2015 02:52:30   AnPawar
 * change in function SetMaxMinValues() for velocity MLR and PLR limits
 * 
 *    Rev 1.35   02 Jan 2015 04:07:06   rjamloki
 * changes related to preset revesion number
 * 
 *    Rev 1.34   11 Dec 2014 08:36:30   AnPawar
 * delay removed and changes to get correct status of cold start completion.
 * 
 *    Rev 1.33   28 Nov 2014 07:39:20   rjamloki
 * PreparePrstSaveTitle() changed to add condition that technician can not overwrit the locked preset.
 * 
 *    Rev 1.32   14 Nov 2014 10:27:18   AnPawar
 * change in function SetMaxMinValues() for down speed tuning bit mask.
 * 
 *    Rev 1.31   14 Nov 2014 05:28:44   rjamloki
 * DOWNSPEED_DEFAULT macro added.
 * 
 *    Rev 1.30   10 Nov 2014 04:55:46   AnPawar
 * SetPresetClearFlags() and PreparePrstSaveTitle() changed .Changes for setting min max value to downpeed reject limit variables.
 * 
 *    Rev 1.29   20 Oct 2014 06:22:28   AnPawar
 * HOLDPRESSURE_DEFAULT define changed
 * 
 *    Rev 1.28   06 Oct 2014 06:41:40   AnPawar
 * removed ck_qsend.h file inclusion.function SetDefaultValues() changed.Using cygos function for queue read write.
 * 
 *    Rev 1.27   03 Oct 2014 05:53:42   rjamloki
 *  function renamed q_send() to SendMessage() and using RTOS::DelayMs() in place of tm_wkafter()
 * 
 *    Rev 1.26   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.25   25 Sep 2014 14:12:12   tayars
 * Added the TunedPreset variable so new defaults, min, and max needed to be added.
 * 
 *    Rev 1.24   11 Sep 2014 16:53:22   rjamloki
 * Taken care the just in case wrong preset number case in CalculatePresetAddress function.
 * 
 *    Rev 1.23   11 Sep 2014 11:02:36   rjamloki
 * Coverity and review comment fixes
 * 
 *    Rev 1.22   05 Sep 2014 05:04:52   rjamloki
 * Removed statc preset name array. Removed compressed preset.
 * 
 *    Rev 1.21   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.20   07 Aug 2014 15:56:40   tayars
 * Added default, min, max values for downspeed and flow counts.
 * 
 *    Rev 1.19   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.18   17 Jul 2014 12:43:48   hasanchez
 * Changes about special menu
 * 
 *    Rev 1.17   15 Jul 2014 16:41:46   hasanchez
 * Changes about the special menu
 * 
 *    Rev 1.16   09 Jul 2014 13:36:00   rjamloki
 * Flow control max value is changed to 125
 * 
 *    Rev 1.15   16 Jun 2014 08:42:00   rjamloki
 * Merged changes from vgapreset.cpp and removed vgapreset.cpp.
 * 
 *    Rev 1.14   11 Jun 2014 12:04:12   rjamloki
 * Min max updated on cylinder dia change from SBC
 * 
 *    Rev 1.13   27 May 2014 10:13:30   amaurya
 * Forcing MinMax initialization on FramInit
 * 
 *    Rev 1.12   21 May 2014 10:52:30   rjamloki
 * Moved Define to Preset.h
 * 
 *    Rev 1.11   21 May 2014 03:35:08   rjamloki
 * added rev number to preset
 * 
 *    Rev 1.10   07 May 2014 10:25:16   rjamloki
 * ReadPreset() changed.SetDefaultValues() assigning default value to idlelogout.Removed DigPotKey
 * 
 *    Rev 1.9   28 Apr 2014 14:59:08   lmarkure
 * Changed minimum pressure to 10PSI, removed unused variables and commented out code
 *
 *    Rev 1.8   21 Apr 2014 13:41:54   rjamloki
 * Max and Min velocity macros are updated
 * 
 *    Rev 1.7   14 Apr 2014 10:15:34   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.6   07 Mar 2014 11:11:10   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:56   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:38   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.3   10 Feb 2014 04:59:48   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.2   03 Jan 2014 08:45:44   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 --------------------------- MODULE DESCRIPTION ---------------------------

 Module name: Preset

 Filename:    Preset.c

 Function Name: Save/Recall Presets

 ----------------------------- DESCRIPTION --------------------------------

 This module contains all the code to deal with preset 0 - 10 (the current
 preset).  All references to the preset will be done through this module.
 This includes the following functions:

 WritePreset-take current preset and save it into FRAM
 ReadPreset-read the preset from FRAM into the current preset

 ----------------------------- PSEUDO CODE --------------------------------*/

/*---------------------------- LOCAL_EQUATES -------------------------------*/



#define WELDTRIGGER_MIN TRIGGERBY_FORCE//1-FORCE,2- DISTANCE
#define WELDTRIGGER_MAX TRIGGERBY_DISTANCE//1-FORCE,2- DISTANCE
#define WELDPRESSURE_DEFAULT  200 //20PSI
#define HOLDPRESSURE_DEFAULT  200 //20PSI
#define NUM_USERPRESETS_FRAM   32
/*------------------------------ INCLUDES ----------------------------------*/

#include "qdef.h"
#include "opcodes.h"                  /* intertask opcodes definitions      */
#include "nvm_msg.h"
#include "util.h"
#include "preset.h"
#include "battram.h"
#include "menu.h"
#include "menu3.h"
#include "menu7a.h"
#include "menu7.h"
#include "menu1.h"
#include "getmsg.h"
#include "selctkey.h"
#include "ready.h"
#include "serial.h"
#include "weld_obj.h"
#include "alsetup.h"
#include "fpled.h"
#include "actnvram.h"
#include "alarms.h"
#include "spidd.h"
#include "beep.h"
#include "digout.h"
#include "dups_api.h"
#include "string.h"
#include "dups.h"
#include "inports.h"
#include "outports.h"
#include "statedrv.h"
#include "version.h"
#include "SystemManagerTask.h"
#include "RVTSHandlerTask.h"
#include "NandFlash.h"
#include "RTOS.h"
#include "ticks.h"
#include "FlowLookupTable.h"
/*------------------------------ LOCAL DEFINES -----------------------------*/
#define EXT_CLAMPDELAY_TIMEOUT 5000

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/
void RecallColdstartPreset(UINT32 MenuExtra);
BOOLEAN* GetInputPtr(UINT16 InputBit);
void InitSBL(void);

void RefreshDUPSParam ();
void UseSameNamePreset(UINT32 Cond);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
void FormatDateStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year );
void FormatTimeStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute );
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
SETUPS_Ver1200 RunningPreset;
Ver1200Setups LocalPresetCopyOfFlash;

UINT16 ColdStartInProcess;
UINT16 PressureStepEnable, AmpStepEnable;
SETUPS_Ver1200 CurrentPreset;
SETUPS_Ver1200 MinLimit, MaxLimit;
UINT32 VGASavePresetOption = 0;
UINT8 ReadOnlyFlag = FALSE;     /* Presets updating Running Preset in nvmanger */

STR InfoLine2[VGA_LINESIZE];	  /* Validated line       */
STR InfoLine3[VGA_LINESIZE];      /* Verified line      */
STR InfoLine4[VGA_LINESIZE];      /* Date line         */
STR InfoLine5[VGA_LINESIZE];      /* Time */
STR InfoLine6[VGA_LINESIZE];      /* Cycle Run      */
/* ---------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                          (scope is global to THIS file)                  */

/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT8 ColdStartFlag;
extern UINT8 MainKeyFlag;
extern UINT16 ColdStartDone;
extern BOOLEAN  CSCompleteFlag;
extern UINT16 SetupAlarmFlag;
extern UINT16 PresetHasBeenOKed;
extern SINT16 BlankMenuCounter;
extern void LastDatePresetWasSaved(void);

// set these variables appropriately when recalling presets
// these flags have positive logic, no matter how the flags are
// stored in presets
extern UINT16 FlagPretriggerOff;
extern UINT16 FlagPretriggerAuto;
extern UINT16 FlagPretriggerDist;
extern UINT16 FlagPretriggerTime;
extern UINT16 FlagPretriggerAmpl; // this flag is for pretrigger amplitude
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UINT16 AmplitudeFixedEnableFlag;

extern UINT16 PressureFixedEnableFlag;
extern UNION_BOOL_UINT16 PressureStepEnableFlag;
extern DUPS_CURRENTPARAMSET DUPS_MaxParamSet;
extern DUPS_CURRENTPARAMSET DUPS_MinParamSet, DUPS_Default15KParamSet,
      DUPS_Default20KParamSet, DUPS_Default30KParamSet, DUPS_Default40KParamSet;
extern UINT8 ActivePreset;
extern SINT8 AssignNamePresetBuffer[MESSAGESIZE];
extern UINT16 PresetEnableFlags[MAX_POSSIBLE_PRESET+1];
extern SINT32 InfoMonth;
extern SINT32 InfoDay;
extern SINT32 InfoYear;
extern SINT32 InfoHour;
extern SINT32 InfoMinute;
extern SINT32 InfoCount;
extern BOOLEAN IsGraphDrawing;
extern UINT8 UpdateRunningPreset;
extern enum WELDSTATES WeldState;
extern UINT16 LangIndex;
extern UINT8  LimitChanged;
extern BOOLEAN ResetRecall_UpdateFlag;
extern UINT16  PresetNeedsToBeUpdated;
extern STR *PresetBuffer[];
extern SINT32 SetFlowValue;

SINT32    MaxSampleValue = COUNTER_MAX;
SINT32 MinSampleValue = 1;
UINT16 FlagTriggerByDist, FlagTriggerByForce;
UINT16 VGAPresetNum = 1;
UINT16 TempSequenceNos;
BOOLEAN VGAPresetSaveAborted = FALSE;

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

NVM_ACCESS_MSG NvmAccessMsg;

/*----------------------------- GLOBAL DATA --------------------------------*/
/*                      (scope is global to ALL files)                      */

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

/*-------------------------------- CODE ------------------------------------*/

void WritePreset(UINT16 PresetNumber, BOOLEAN ChangePrestUpdate)
/***************************************************************************/
/*                                                                         */
/*  This function will pass the current preset to the system manger to     */
/*  save in the battery backup RAM                                         */
/*                                                                         */
/***************************************************************************/
{

   NvmAccessMsg.common.source_task = FPSC_SOURCE_TASK;
   NvmAccessMsg.common.opcode = OP_BATTRAM_WRITE_PRESET;

   if (PresetNumber <= MAX_POSSIBLE_PRESET)
   {
   	  //Flag ChangePrestUpdate is handy if we only want the FRAM slot passed in  PresetNumber argument
	  //to be modified and not the active preset slot with current preset
	  if(ChangePrestUpdate)
      		CurrentPreset.PresetUpdateComplete = TRUE;
      NvmAccessMsg.offset = PresetNumber;
      /* Have message queue data point to new buffer */
      SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &NvmAccessMsg), 100);
   }
}

void ReadPreset(UINT16 PresetNumber, UINT16 AlarmSuppressFlag)
/***************************************************************************/
/*                                                                         */
/*  This function will call the nvmmanager to read the specified preset    */
/*  and copy it to the Current Preset                                      */
/*                                                                         */
/*  The AlarmSuppressFlag if TRUE will prevent the W9 (Cal suggested)      */
/*  alarm from being created (as is the case when a preset is cleared). If */
/*  FALSE, the alarm will be created.                                      */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
{
   NvmAccessMsg.common.source_task = FPSC_SOURCE_TASK;
   NvmAccessMsg.common.opcode = OP_BATTRAM_READ_PRESET;
   NvmAccessMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;

   if (PresetNumber <= MAX_POSSIBLE_PRESET)
   {
      NvmAccessMsg.offset = PresetNumber;
   }

   CheckFramDefaults(); /* See if FRAM is initialized & working */

   SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &NvmAccessMsg), 50);

   if ((CurrentSetup.ControlLevel >= LEVEL_d) && (AlarmSuppressFlag == FALSE)
         && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) ||
        		 (CurrentSetup.Actuator == MICRO)))
   {
      ErrorCodeFlag = FALSE; /* Turn off error codes for this alarm */
   }
}

void SetMaxMinValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the min and max preset values in battram       */
/*                                                                           */
/*****************************************************************************/
{
   SINT32 MaxStrokeLength;
   SINT32 MaxEnergy;
   UINT32 MaxForce = 0;
   SINT32 Indx = 0;

   MaxForce = GetMaxForce();
   MaxEnergy = CurrentSetup.PSWatt * 300;
   if (MaxEnergy > ENERGY_MAX)
      MaxEnergy = ENERGY_MAX; /* Max value even for 4000 Watt   */
   MaxStrokeLength = GetMaxStrokeLength();
   if(FramInitialized == TRUE)//Need to cross check defaults once the Power and freq is received from Dups
   {
	   SetDefaultValues();
	    for (Indx =0; Indx <= MAX_POSSIBLE_PRESET; Indx++) {
	      SavePreset(Indx, &CurrentPreset);
	    }
   }

   if ((FramInitialized == TRUE) || strcmp(MinLimit.PresetID, "MINIMUM") != 0)
   {
      MinLimit.WeldTime = TIME_MIN; /*                                */
      MinLimit.WeldEnergy = ENERGY_MIN; /* 50 = 5.0 J                     */
      MinLimit.EnergyPL = ENERGY_MIN; /* energy plus limit              */
      MinLimit.EnergyML = ENERGY_MIN; /* energy minus limit             */
      MinLimit.ScrubTime = 1; /* Grd det mode, scrub time       */
      MinLimit.AmpScrubTime = AMP_MIN; /* Amp for Ground Detect Mode     */
      MinLimit.PeakPwr = POWER_MIN; /*                                */
      MinLimit.PeakPwrCutoff = POWER_MIN; /*                                */
      MinLimit.ColDist = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.AbsDist = ABS_MIN; /* 1250 = 0.1250"                 */
      MinLimit.ABSCutoffDist = ABS_MIN; /* 1250 = 0.1250"                 */
      MinLimit.ColCutoffDist = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.HoldTime = TIME_MIN; /*                                */
      MinLimit.AbDelay = 50; /*Tracker 3948. Min can be 50ms   */
      MinLimit.AbTime = 100; /*                                */
      MinLimit.AbAmp = AMP_MIN; /*                                */
      MinLimit.MaxTimeout = 50; /*                                */
      MinLimit.TriggerDelay = TIME_MIN; /*                                */
      MinLimit.FreqOffset = 0; /* Limit specifies min abs. value */
      MinLimit.EnergyPLS = ENERGY_MIN; /*                                */
      MinLimit.EnergyMLS = ENERGY_MIN; /*                                */
      MinLimit.EnergyPLR = ENERGY_MIN; /*                                */
      MinLimit.EnergyMLR = ENERGY_MIN; /*                                */
      MinLimit.TimePLS = TIME_MIN; /*                                */
      MinLimit.TimeMLS = TIME_MIN; /*                                */
      MinLimit.TimePLR = TIME_MIN; /*                                */
      MinLimit.TimeMLR = TIME_MIN; /*                                */
      MinLimit.PowerPLS = POWER_MIN; /*                                */
      MinLimit.PowerMLS = POWER_MIN; /*                                */
      MinLimit.PowerPLR = POWER_MIN; /*                                */
      MinLimit.PowerMLR = POWER_MIN; /*                                */
      MinLimit.ColPLS = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.ColMLS = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.ColPLR = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.ColMLR = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.AbsPLS = ABS_MIN; /*                                */
      MinLimit.AbsMLS = ABS_MIN; /*                                */
      MinLimit.AbsPLR = ABS_MIN; /*                                */
      MinLimit.AbsMLR = ABS_MIN; /*                                */
      MinLimit.TrsDistPLS = ABS_MIN; /*                                */
      MinLimit.TrsDistMLS = ABS_MIN; /*                                */
      MinLimit.TrsDistPLR = ABS_MIN; /*                                */
      MinLimit.TrsDistMLR = ABS_MIN; /*                                */
      MinLimit.WeldForcePLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                                */
      MinLimit.WeldForceMLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                                */
      MinLimit.WeldForcePLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                                */
      MinLimit.WeldForceMLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                                */


      switch (CurrentSetup.PSFreq)
      {
      default:
      case FREQ20KHZ:
         MinLimit.FreqPLS = -FREQ20_OFF; /*                                */
         MinLimit.FreqMLS = -FREQ20_OFF; /*                                */
         MinLimit.FreqPLR = -FREQ20_OFF; /*                                */
         MinLimit.FreqMLR = -FREQ20_OFF; /*                                */
         MinLimit.TriggerForce = CurrentSetup.MinTrigForce; /*               */
         break;

      case FREQ40KHZ:
         MinLimit.FreqPLS = -FREQ40_OFF; /*                                */
         MinLimit.FreqMLS = -FREQ40_OFF; /*                                */
         MinLimit.FreqPLR = -FREQ40_OFF; /*                                */
         MinLimit.FreqMLR = -FREQ40_OFF; /*                                */
         MinLimit.TriggerForce = CurrentSetup.MinTrigForce; /*             */
         break;

      case FREQ15KHZ:
         MinLimit.FreqPLS = -FREQ15_OFF; /*                                */
         MinLimit.FreqMLS = -FREQ15_OFF; /*                                */
         MinLimit.FreqPLR = -FREQ15_OFF; /*                                */
         MinLimit.FreqMLR = -FREQ15_OFF; /*                                */
         MinLimit.TriggerForce = CurrentSetup.MinTrigForce; /*              */
         break;

      case FREQ30KHZ:
         MinLimit.FreqPLS = -FREQ30_OFF; /*                                */
         MinLimit.FreqMLS = -FREQ30_OFF; /*                                */
         MinLimit.FreqPLR = -FREQ30_OFF; /*                                */
         MinLimit.FreqMLR = -FREQ30_OFF; /*                                */
         MinLimit.TriggerForce = CurrentSetup.MinTrigForce; /*              */
         break;

      case FREQ60KHZ:
         MinLimit.FreqPLS = -FREQ60_OFF; /*                                */
         MinLimit.FreqMLS = -FREQ60_OFF; /*                                */
         MinLimit.FreqPLR = -FREQ60_OFF; /*                                */
         MinLimit.FreqMLR = -FREQ60_OFF; /*                                */
         MinLimit.TriggerForce = CurrentSetup.MinTrigForce; /*              */
         break;
      }

      MinLimit.Amp1 = AMP_MIN; /*                                */
      MinLimit.AmpTrigTimeValue = TIME_MIN; /*                                */
      MinLimit.AmpTrigEnerValue = ENERGY_MIN; /* 10 = 1.0 J                     */
      MinLimit.AmpTrigPowerValue = POWER_MIN; /*                                */
      MinLimit.AmpTrigColValue = COL_MIN; /* 4 = 0.0004"                    */
      MinLimit.Amp2 = AMP_MIN; /*                                */
      MinLimit.PreTriggerDistance = ABS_MIN; /* 1250 = 0.1250"                 */
      MinLimit.PreTrigDelay = TIME_MIN; /* 0.010 seconds                  */
      MinLimit.PreTrigAmp = AMP_MIN; /*                                */
      MinLimit.ActClrDistance = ABS_MIN;
      MinLimit.MissingPartMin = ABS_MIN; /* 1250 = 0.1250"                 */
      MinLimit.MissingPartMax = ABS_MIN; /* 1250 = 0.1250"                 */
      MinLimit.RTDist = 1000; /*                                */
      MinLimit.WeldCount = 0; /*                                */
      MinLimit.TestAmp = AMP_MIN; /*                                */
      MinLimit.PS_DateTime.Years = 0; /*                                */
      MinLimit.PS_DateTime.Century_Month = 1; /*                                */
      MinLimit.PS_DateTime.Day = 1; /*                                */
      MinLimit.PS_DateTime.Hour = 0; /*                                */
      MinLimit.PS_DateTime.Minute = 0; /*                                */
      MinLimit.XScaleTime = XSCALEMINVALUE; /* min value of x-axis scale      */
      MinLimit.EBTime = TIME_MIN; /* Min value for energy braking   */
      MinLimit.PMCLowLimit = 1; /* Min % value for PMC Low Limit  */
      MinLimit.PMCHighLimit = 1; /* Min % value for PMC High Limit */
      MinLimit.PMCTimeout = 1; /* Min PMC Timeout                */
      MinLimit.WeldMode = TIMEMODE; /* Set weld mode                 */
      MinLimit.ScrubTimeFlag = 1; /* Turn scrub time OFF           */
      MinLimit.ControlLimitsFlag = 0; /* CHOICE structure, so 1 = on   */
      MinLimit.PeakPwrCutoffFlag = 1; /* Off                           */
      MinLimit.ABSCutoffFlag = 1; /* VARIABLE structure, so 1= off */
      MinLimit.ColCutoffFlag = 1; /* 1 = off                       */
      MinLimit.HoldTimeFlag = 0; /* VARIABLE structure, so 0=On   */
      MinLimit.AbFlag = 0; /* CHOICE structure, so 0 = off  */
      MinLimit.TriggerDelayFlag = 1; /* VARIABLE structure, so 1= Off */
      MinLimit.FreqOffsetFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.SuspectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.RejectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.RVelLimitFlag = TRUE;
      MinLimit.SuspectLimits = 0x7ffe; /* VARIABLE 1 = off              */
      MinLimit.PressureLimits = 0x7ffe; /* VARIABLE 1 = off              */
      MinLimit.RejectLimits = 0x7ffe; /* VARIABLE 1 = off              */
      MinLimit.RVelLimitMask = 0x06;
      MinLimit.SetupLimits = 0xfffe;
      MinLimit.SetupLimits2 = 0xfffe;
      MinLimit.SeekFunFlag = 0; /*                               */
      MinLimit.Amp2Flag = 0xfffa; /* CHOICE structure, so 0=Off    */
      MinLimit.AmpTrigExtFlag = 0; /*                               */
      MinLimit.AutoTrigFlag = TRUE; /* Acts like Radio Button        */
      MinLimit.PreTrigFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.RTFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.HoldPressureFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.EnergyCompFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.SuspectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.RejectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.CycleAbortFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.GndDetectFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.SusResetRequired = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.RejResetRequiredFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.PresetUpdateComplete = TRUE;
      MinLimit.ActClrFlag = 0; /* Choice structure so 0=off    */
      MinLimit.MissingPartFlag = 0;
      MinLimit.MissingMinFlag = 1; /* Pointer to disable/enable flag    */
      MinLimit.MissingMaxFlag = 1; /* Pointer to disable/enable flag    */
      strcpy(MinLimit.PresetID, "DEFAULT");
      MinLimit.BatchFunction = 0;
      MinLimit.BatchCountWithAlarm = 0;
      MinLimit.BatchCountReset = 0;
      MinLimit.BatchCount = BATCHCNTR_MIN;
      strcpy(MinLimit.ActAssemblyNum, "DEFAULT");
      strcpy(MinLimit.PSAssemblyNum, "DEFAULT");
      strcpy(MinLimit.StackAssemblyNum, "DEFAULT");
      MinLimit.Downspeed = MIN_DOWNSPEED;
      CurrentPreset.TunedPreset = FALSE; // Flag to know whether preset has been tuned or not
      // This needs to be called to set the flow to the new value
      CurrentPreset.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
      SetFlowValue = CurrentPreset.TunedFlowValue;
      MinLimit.HoldPressure = HOLDPRESSURE_MIN;
      MinLimit.WeldPressure = WELDPRESSURE_MIN;


      strcpy(MinLimit.HornID, "DEFAULT");
      MinLimit.MPressureLimit = MPRESSURELIM_MIN;
      MinLimit.PPressureLimit = PPRESSURELIM_MIN;
      MinLimit.PressureLimitFlag = 0; /* CHOICE structure, so 0=Off    */
      MinLimit.PresetConfigNum = 0;
      MinLimit.TriggerDistance = TRIGDIST_MIN;
      MinLimit.Validated = 0;
      MinLimit.Locked = 0;
      MinLimit.VelocityMLR = VELOCITYMLR_MIN;
      MinLimit.VelocityPLR = VELOCITYPLR_MIN;
      MinLimit.WeldTrigger = WELDTRIGGER_MIN;
      MinLimit.DUPS_HostParamSet = DUPS_MinParamSet;
      MinLimit.DUPS_HostParamSet.Power = CurrentSetup.PSWatt;
      MinLimit.DUPS_HostParamSet.Frequency = CurrentSetup.PSFreq;
      MinLimit.TrigForcePLT = CurrentSetup.MinTrigForce;
      MinLimit.TrigForceMLT = CurrentSetup.MinTrigForce;
      MinLimit.TrigDistancePLT = TRIGDIST_MIN;
      MinLimit.TrigDistanceMLT = TRIGDIST_MIN;
      MinLimit.AmpAPLT = AMP_MIN;
      MinLimit.AmpAMLT = AMP_MIN;
      MinLimit.HoldTimePLT = TIME_MIN;
      MinLimit.HoldTimeMLT = TIME_MIN;
      MinLimit.DownspeedPLT = MIN_DOWNSPEED;
      MinLimit.DownspeedMLT = MIN_DOWNSPEED;
      MinLimit.WeldPressurePLT = WELDPRESSURE_MIN;
      MinLimit.WeldPressureMLT = WELDPRESSURE_MIN;
      MinLimit.HoldPressurePLT = HOLDPRESSURE_MIN;
      MinLimit.HoldPressureMLT = HOLDPRESSURE_MIN;
      MinLimit.WeldTimePLT = TIME_MIN;
      MinLimit.WeldTimeMLT = TIME_MIN;
      MinLimit.WeldEnergyPLT = ENERGY_MIN;
      MinLimit.WeldEnergyMLT = ENERGY_MIN;
      MinLimit.PeakPowerPLT = POWER_MIN;
      MinLimit.PeakPowerMLT = POWER_MIN;
      MinLimit.CollapseDistPLT = COL_MIN;
      MinLimit.CollapseDistMLT = COL_MIN;
      MinLimit.AbsDistPLT = ABS_MIN;
      MinLimit.AbsDistMLT = ABS_MIN;
      MinLimit.ScrubTimePLT = 1;
      MinLimit.ScrubTimeMLT = 1;
      MinLimit.ScrubAmpPLT = AMP_MIN;
      MinLimit.ScrubAmpMLT = AMP_MIN;

  	  //Assign Pressure min here
      MinLimit.PressureTrigColValue = COL_MIN;
      MinLimit.PressureTrigExtFlag = OFF;
      MinLimit.PressureTrigTimeValue = TIME_MIN;
      MinLimit.PressureTrigEnerValue = ENERGY_MIN;
      MinLimit.PressureTrigPowerValue = POWER_MIN;
      MinLimit.Pressure2Flag = 0xFFFA;
      MinLimit.Pressure2 = WELDPRESSURE_MIN;
	  SavePreset(PRESET_MIN_INDEX, &MinLimit);
   }
   else
   {
   		memcpy(&RunningPreset,&CurrentPreset,sizeof(SETUPS_Ver1200));           /* It copy CurrentPreset to runningPreset to save these values*/ 		
   		Readpreset(PRESET_MIN_INDEX, &CurrentPreset);                 /*  loading the Preset_min_start on current preset*/
   		memcpy(&MinLimit,&CurrentPreset,sizeof(SETUPS_Ver1200)); 		     /*moving the values of Preset_min_start to minlimit */	
    	memcpy(&CurrentPreset,&RunningPreset,sizeof(SETUPS_Ver1200));  	     /*Recovering the currentpreset*/	
   }
   /*----  Now do the Max limits  ----*/
   if ((FramInitialized == TRUE) || strcmp(MaxLimit.PresetID, "MAXIMUM") != 0)
   {
      MaxLimit.WeldTime = TIME_MAX; /*                              */
      MaxLimit.WeldEnergy = MaxEnergy; /* 10 = 1.0 J                   */
      MaxLimit.EnergyPL = MaxEnergy; /* TEC mode energy plus limit   */
      MaxLimit.EnergyML = MaxEnergy; /* TEC mode energy minus limit  */
      MaxLimit.ScrubTime = 500; /* Ground detect, scrub tim     */
      MaxLimit.AmpScrubTime = AMP_MAX; /* Ground Detect Amplitude      */
      MaxLimit.PeakPwr = POWER_MAX; /*                              */
      MaxLimit.PeakPwrCutoff = POWER_MAX; /*                              */
      MaxLimit.ColDist = COL_MAX; /* 1 = 0.0001"                  */
      MaxLimit.AbsDist = MaxStrokeLength; /* 40000 = 4.0"                 */
      MaxLimit.ABSCutoffDist = MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.ColCutoffDist = COL_MAX; /* 1000 = 0.1"                  */
      MaxLimit.HoldTime = TIME_MAX; /*                              */
      MaxLimit.AbDelay = 2000; /*                              */
      MaxLimit.AbTime = 2000; /*                              */
      MaxLimit.AbAmp = AMP_MAX; /*                              */
      MaxLimit.MaxTimeout = TIME_MAX; /*                              */
      MaxLimit.TriggerDelay = TIME_MAX; /*                              */
      MaxLimit.EnergyPLS = MaxEnergy; /*                              */
      MaxLimit.EnergyMLS = MaxEnergy; /*                              */
      MaxLimit.EnergyPLR = MaxEnergy; /*                              */
      MaxLimit.EnergyMLR = MaxEnergy; /*                              */
      MaxLimit.TimePLS = TIME_MAX; /*                              */
      MaxLimit.TimeMLS = TIME_MAX; /*                              */
      MaxLimit.TimePLR = TIME_MAX; /*                              */
      MaxLimit.TimeMLR = TIME_MAX; /*                              */
      MaxLimit.PowerPLS = POWER_MAX; /*                              */
      MaxLimit.PowerMLS = POWER_MAX; /*                              */
      MaxLimit.PowerPLR = POWER_MAX; /*                              */
      MaxLimit.PowerMLR = POWER_MAX; /*                              */
      MaxLimit.ColPLS = COL_MAX; /*                              */
      MaxLimit.ColMLS = COL_MAX; /*                              */
      MaxLimit.ColPLR = COL_MAX; /*                              */
      MaxLimit.ColMLR = COL_MAX; /*                              */
      MaxLimit.AbsPLS = MaxStrokeLength; /*                              */
      MaxLimit.AbsMLS = MaxStrokeLength; /*                              */
      MaxLimit.AbsPLR = MaxStrokeLength; /*                              */
      MaxLimit.AbsMLR = MaxStrokeLength; /*                              */
      MaxLimit.TrsDistPLS = MaxStrokeLength; /*                              */
      MaxLimit.TrsDistMLS = MaxStrokeLength; /*                              */
      MaxLimit.TrsDistPLR = MaxStrokeLength; /*                              */
      MaxLimit.TrsDistMLR = MaxStrokeLength; /*                              */


      switch (CurrentSetup.PSFreq)
      {
      default:
      case FREQ20KHZ:
         MaxLimit.FreqPLS = +FREQ20_OFF; /*                              */
         MaxLimit.FreqMLS = +FREQ20_OFF; /*                              */
         MaxLimit.FreqPLR = +FREQ20_OFF; /*                              */
         MaxLimit.FreqMLR = +FREQ20_OFF; /*                              */
         MaxLimit.FreqOffset = +FREQ20_OFF; /*                              */
         break;

      case FREQ40KHZ:
         MaxLimit.FreqPLS = +FREQ40_OFF; /*                              */
         MaxLimit.FreqMLS = +FREQ40_OFF; /*                              */
         MaxLimit.FreqPLR = +FREQ40_OFF; /*                              */
         MaxLimit.FreqMLR = +FREQ40_OFF; /*                              */
         MaxLimit.FreqOffset = +FREQ40_OFF; /*                              */
         break;

      case FREQ15KHZ:
         MaxLimit.FreqPLS = +FREQ15_OFF; /*                              */
         MaxLimit.FreqMLS = +FREQ15_OFF; /*                              */
         MaxLimit.FreqPLR = +FREQ15_OFF; /*                              */
         MaxLimit.FreqMLR = +FREQ15_OFF; /*                              */
         MaxLimit.FreqOffset = +FREQ15_OFF; /*                              */
         break;

      case FREQ30KHZ:
         MaxLimit.FreqPLS = +FREQ30_OFF; /*                              */
         MaxLimit.FreqMLS = +FREQ30_OFF; /*                              */
         MaxLimit.FreqPLR = +FREQ30_OFF; /*                              */
         MaxLimit.FreqMLR = +FREQ30_OFF; /*                              */
         MaxLimit.FreqOffset = +FREQ30_OFF; /*                              */
         break;

      case FREQ60KHZ:
         MaxLimit.FreqPLS = +FREQ60_OFF; /*                              */
         MaxLimit.FreqMLS = +FREQ60_OFF; /*                              */
         MaxLimit.FreqPLR = +FREQ60_OFF; /*                              */
         MaxLimit.FreqMLR = +FREQ60_OFF; /*                              */
         MaxLimit.FreqOffset = +FREQ60_OFF; /*                              */
         break;
      }

      MaxLimit.Amp1 = AMP_MAX; /*                              */
      MaxLimit.AmpTrigTimeValue = TIME_MAX; /*                              */
      MaxLimit.AmpTrigEnerValue = MaxEnergy; /*                              */
      MaxLimit.AmpTrigPowerValue = POWER_MAX; /*                              */
      MaxLimit.AmpTrigColValue = COL_MAX; /*                              */
      MaxLimit.Amp2 = AMP_MAX; /*                              */
      MaxLimit.PreTriggerDistance = MaxStrokeLength; /*                              */
      MaxLimit.PreTrigDelay = PRETRG_MAX; /* 10 seconds for now           */
      MaxLimit.PreTrigAmp = AMP_MAX; /*                              */
      MaxLimit.RTDist = MaxStrokeLength; /*                              */
      MaxLimit.ActClrDistance = MaxStrokeLength;/*                              */
      MaxLimit.MissingPartMin = MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.MissingPartMax = MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.WeldCount = 999999999; /*                              */
      MaxLimit.TestAmp = AMP_MAX; /*                              */
      MaxLimit.PS_DateTime.Years = 99; /*                              */
      MaxLimit.PS_DateTime.Century_Month = 12; /*                              */
      MaxLimit.PS_DateTime.Day = 31; /*                              */
      MaxLimit.PS_DateTime.Hour = 23; /*                              */
      MaxLimit.PS_DateTime.Minute = 59; /*                              */
      MaxLimit.XScaleTime = XSCALEMAXVALUE; /*  max x-axis scale value      */

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         MaxForce = GetMaxForce();
         if (CurrentSetup.Actuator == MICRO)
            MaxLimit.TriggerForce = MICRO_MAXFORCE_40MM;/*Restrict the max trigger force to 135 lbs.*/
         else
            MaxLimit.TriggerForce = MaxForce; /*                              */
         MaxLimit.WeldForcePLS = MaxForce; /*                              */
         MaxLimit.WeldForceMLS = MaxForce; /*                              */
         MaxLimit.WeldForcePLR = MaxForce; /*                              */
         MaxLimit.WeldForceMLR = MaxForce; /*                              */
      }
      MaxLimit.EBTime = EB_TIME_MAX; /* Max value for energy braking */
      MaxLimit.PMCLowLimit = 100; /* Max % value for PMC Low Limit  */
      MaxLimit.PMCHighLimit = 100; /* Max % value for PMC High Limit */
      MaxLimit.PMCTimeout = 400; /* Max PMC Timeout                */

      MaxLimit.WeldMode = GRDDETECTMODE;
      MaxLimit.ScrubTimeFlag = 1;
      MaxLimit.ControlLimitsFlag = 0;
      MaxLimit.PeakPwrCutoffFlag = 1;
      MaxLimit.ABSCutoffFlag = 1;
      MaxLimit.ColCutoffFlag = 1;
      MaxLimit.HoldTimeFlag = 0;
      MaxLimit.AbFlag = 0;
      MaxLimit.TriggerDelayFlag = 1;
      MaxLimit.FreqOffsetFlag = 0;
      MaxLimit.SuspectLimitsFlag = 0;
      MaxLimit.RejectLimitsFlag = 0;
      MaxLimit.RVelLimitFlag = TRUE;
      MaxLimit.SuspectLimits = 0x7ffe;
      MaxLimit.PressureLimits = 0x7ffe;
      MaxLimit.RejectLimits = 0x7ffe;
      MaxLimit.RVelLimitMask = 0x06;
      MaxLimit.SetupLimits = 0xfffe;
      MaxLimit.SetupLimits2 = 0xfffe;
      MaxLimit.SeekFunFlag = 0;
      MaxLimit.Amp2Flag = 0xfffa;
      MaxLimit.AmpTrigExtFlag = 0;
      MaxLimit.AutoTrigFlag = TRUE;
      MaxLimit.PreTrigFlag = 0;
      MaxLimit.RTFlag = 0;
      MaxLimit.HoldPressureFlag = 0; /* CHOICE structure, so 0=Off    */
      MaxLimit.EnergyCompFlag = 0;
      MaxLimit.SuspectLimitsFlag = 0;
      MaxLimit.RejectLimitsFlag = 0;
      MaxLimit.CycleAbortFlag = 0;
      MaxLimit.GndDetectFlag = 0;
      MaxLimit.SusResetRequired = 0;
      MaxLimit.RejResetRequiredFlag = 0;
      MaxLimit.PresetUpdateComplete = TRUE;
      MaxLimit.ActClrFlag = 0;
      MaxLimit.MissingPartFlag = 0;
      MaxLimit.MissingMinFlag = 1;
      MaxLimit.MissingMaxFlag = 1;
      strcpy(MaxLimit.PresetID, "DEFAULT");
      MaxLimit.BatchFunction = 0;
      MaxLimit.BatchCountWithAlarm = 0;
      MaxLimit.BatchCountReset = 0;
      MaxLimit.BatchCount = BATCHCNTR_MAX;
      strcpy(MaxLimit.ActAssemblyNum, "DEFAULT");
      strcpy(MaxLimit.PSAssemblyNum, "DEFAULT");
      strcpy(MaxLimit.StackAssemblyNum, "DEFAULT");
      MaxLimit.Downspeed = MAX_DOWNSPEED;
      CurrentPreset.TunedPreset = TRUE;
      // This needs to be called to set the flow to the new value
      CurrentPreset.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
      SetFlowValue = CurrentPreset.TunedFlowValue;
      MaxLimit.HoldPressure = HOLDPRESSURE_MAX;
      MaxLimit.WeldPressure = WELDPRESSURE_MAX;

      strcpy(MaxLimit.HornID, "DEFAULT");
      MaxLimit.MPressureLimit = MPRESSURELIM_MAX;
      MaxLimit.PPressureLimit = PPRESSURELIM_MAX;
      MaxLimit.PressureLimitFlag = 0; /* CHOICE structure, so 0=Off    */
      MaxLimit.PresetConfigNum = 0;
      MaxLimit.TriggerDistance = MaxStrokeLength;
      MaxLimit.Validated = 0;
      MaxLimit.Locked = 0;
      MaxLimit.VelocityMLR = VELOCITYMLR_MAX;
      MaxLimit.VelocityPLR = VELOCITYPLR_MAX;
      MaxLimit.WeldTrigger = WELDTRIGGER_MAX;
      MaxLimit.DUPS_HostParamSet = DUPS_MaxParamSet;
      MaxLimit.DUPS_HostParamSet.Power = CurrentSetup.PSWatt;
      MaxLimit.DUPS_HostParamSet.Frequency = CurrentSetup.PSFreq;
      MaxLimit.TrigForcePLT = MaxForce;
      MaxLimit.TrigForceMLT = MaxForce;
      MaxLimit.TrigDistancePLT = MaxStrokeLength;
      MaxLimit.TrigDistanceMLT = MaxStrokeLength;
      MaxLimit.AmpAPLT = AMP_MAX;
      MaxLimit.AmpAMLT = AMP_MAX;
      MaxLimit.HoldTimePLT = TIME_MAX;
      MaxLimit.HoldTimeMLT = TIME_MAX;
      MaxLimit.DownspeedPLT = MAX_DOWNSPEED;
      MaxLimit.DownspeedMLT = MAX_DOWNSPEED;
      MaxLimit.WeldPressurePLT = WELDPRESSURE_MAX;
      MaxLimit.WeldPressureMLT = WELDPRESSURE_MAX;
      MaxLimit.HoldPressurePLT = HOLDPRESSURE_MAX;
      MaxLimit.HoldPressureMLT = HOLDPRESSURE_MAX;
      MaxLimit.WeldTimePLT = TIME_MAX;
      MaxLimit.WeldTimeMLT = TIME_MAX;
      MaxLimit.WeldEnergyPLT = MaxEnergy;
      MaxLimit.WeldEnergyMLT = MaxEnergy;
      MaxLimit.PeakPowerPLT = POWER_MAX;
      MaxLimit.PeakPowerMLT = POWER_MAX;
      MaxLimit.CollapseDistPLT = COL_MAX;
      MaxLimit.CollapseDistMLT = COL_MAX;
      MaxLimit.AbsDistPLT = MaxStrokeLength;
      MaxLimit.AbsDistMLT = MaxStrokeLength;
      MaxLimit.ScrubTimePLT = 500;
      MaxLimit.ScrubTimeMLT = 500;
      MaxLimit.ScrubAmpPLT = AMP_MAX;
      MaxLimit.ScrubAmpMLT = AMP_MAX;

  	  //Assign Pressure min here
      MaxLimit.PressureTrigColValue = COL_MAX;
      MaxLimit.PressureTrigExtFlag = ON;
      MaxLimit.PressureTrigTimeValue = TIME_MAX;
      MaxLimit.PressureTrigEnerValue = ENERGY_MAX;
      MaxLimit.PressureTrigPowerValue = POWER_MAX;
      MaxLimit.Pressure2Flag = 0xFFFA;
      MaxLimit.Pressure2 = WELDPRESSURE_MAX;
      SavePreset(PRESET_MAX_INDEX, &MaxLimit);
   }
   else 
   {
	 
	 /*The lines below fix the issue relate to the max trigger force, and enable to recall the customized Max preset *H. Sanchez*/
	  memcpy(&RunningPreset,&CurrentPreset,sizeof(SETUPS_Ver1200));           /* It copy CurrentPreset to runningPreset to save these values*/ 	
      Readpreset(PRESET_MAX_INDEX, &CurrentPreset);                   /*  loading the Preset_max_start on current preset*/
      memcpy(&MaxLimit,&CurrentPreset,sizeof(SETUPS_Ver1200));                /*moving the values of Preset_min_start to minlimit */
      memcpy(&CurrentPreset,&RunningPreset,sizeof(SETUPS_Ver1200));           /*Recovering the currentpreset*/
      
   }

}

void SetDefaultValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the current preset with default values when    */
/*  a cold start is executed                                                 */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x;
   SINT32 MaxEnergy;
   SINT32 MaxStrokeLength;
   UINT32 MaxForce = 0;

   MaxForce = GetMaxForce();
   MaxEnergy = CurrentSetup.PSWatt * 300;
   MaxStrokeLength = GetMaxStrokeLength();
   	   
	CurrentPreset.WeldMode = TIMEMODE; /*                               */
	CurrentPreset.WeldTime = 10; /*                               */
	CurrentPreset.WeldEnergy = ENERGY_MIN; /* 50 = 5.0 J                    */
	CurrentPreset.EnergyPL = MaxEnergy; /* TEC mode energy plus limit    */
	CurrentPreset.EnergyML = ENERGY_MIN; /* TEC mode energy minus limit   */
	CurrentPreset.ScrubTime = 1; /* Ground detect mode, scrub time*/
	CurrentPreset.ScrubTimeFlag = 1; /* Turn scrub time OFF           */
	CurrentPreset.PeakPwr = 100; /*                               */
	CurrentPreset.ControlLimitsFlag = 0; /* CHOICE structure, so 1 = on   */
	CurrentPreset.PeakPwrCutoffFlag = 1; /* Off                           */
	CurrentPreset.PeakPwrCutoff = POWER_MIN;/*                               */
	CurrentPreset.ColDist = 4; /* 4 = 0.0004"                   */
	CurrentPreset.AbsDist = ABS_MIN; /*                               */
	CurrentPreset.ABSCutoffFlag = 1; /* VARIABLE structure, so 1= off */
	CurrentPreset.ABSCutoffDist = ABS_MIN; /*                               */
	CurrentPreset.ColCutoffFlag = 1; /* 1 = off                       */
	CurrentPreset.ColCutoffDist = 4; /* 1000 = 0.1"                   */
	CurrentPreset.HoldTimeFlag = 0; /* VARIABLE structure, so 0=On   */
	CurrentPreset.HoldTime = 10; /*                               */
	CurrentPreset.AbFlag = 0; /* CHOICE structure, so 0 = off  */
	CurrentPreset.AbDelay = 100; /*                               */
	CurrentPreset.AbTime = 100; /*                               */
	CurrentPreset.AbAmp = 100; /*                               */
	CurrentPreset.PresetID[0] = 0; /*                               */
	CurrentPreset.MaxTimeout = 6000; /*                               */
	CurrentPreset.TriggerForce = TEN_LBS; /* Issue 3276                    */
	CurrentPreset.TriggerDelayFlag = 1; /* VARIABLE structure, so 1= Off */
	CurrentPreset.TriggerDelay = 10; /*                               */
	CurrentPreset.FreqOffset = 0; /*                               */
	CurrentPreset.FreqOffsetFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.SuspectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.RejectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.RVelLimitFlag = TRUE;
	CurrentPreset.SuspectLimits = 0x7ffe; /* VARIABLE 1 = off              */
	CurrentPreset.PressureLimits = 0x7ffe; /* VARIABLE 1 = off              */
	CurrentPreset.RejectLimits = 0x7ffe; /* VARIABLE 1 = off              */
	CurrentPreset.RVelLimitMask = 0x06;
	CurrentPreset.SetupLimits = 0xfffe;
	CurrentPreset.SetupLimits2 = 0xfffe;
	CurrentPreset.EnergyPLS = ENERGY_MIN; /*                               */
	CurrentPreset.EnergyMLS = ENERGY_MIN; /*                               */
	CurrentPreset.EnergyPLR = ENERGY_MIN; /*                               */
	CurrentPreset.EnergyMLR = ENERGY_MIN; /*                               */
	CurrentPreset.TimePLS = 10; /*                               */
	CurrentPreset.TimeMLS = 10; /*                               */
	CurrentPreset.TimePLR = 10; /*                               */
	CurrentPreset.TimeMLR = 10; /*                               */
	CurrentPreset.PowerPLS = POWER_MIN; /*                               */
	CurrentPreset.PowerMLS = POWER_MIN; /*                               */
	CurrentPreset.PowerPLR = POWER_MIN; /*                               */
	CurrentPreset.PowerMLR = POWER_MIN; /*                               */
	CurrentPreset.ColPLS = 4; /*                               */
	CurrentPreset.ColMLS = 4; /*                               */
	CurrentPreset.ColPLR = 4; /*                               */
	CurrentPreset.ColMLR = 4; /*                               */
	CurrentPreset.AbsPLS = ABS_MIN; /*                               */
	CurrentPreset.AbsMLS = ABS_MIN; /*                               */
	CurrentPreset.AbsPLR = ABS_MIN; /*                               */
	CurrentPreset.AbsMLR = ABS_MIN; /*                               */
	CurrentPreset.TrsDistPLS = ABS_MIN; /*                               */
	CurrentPreset.TrsDistMLS = ABS_MIN; /*                               */
	CurrentPreset.TrsDistPLR = ABS_MIN; /*                               */
	CurrentPreset.TrsDistMLR = ABS_MIN; /*                               */
	CurrentPreset.WeldForcePLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */
	CurrentPreset.WeldForceMLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */
	CurrentPreset.WeldForcePLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */
	CurrentPreset.WeldForceMLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */
	CurrentPreset.SeekFunFlag = 0; /*                               */
	CurrentPreset.XScaleTime = 2000; /*                               */
	CurrentPreset.FreqPLS = 0; /*                               */
	CurrentPreset.FreqMLS = 0; /*                               */
	CurrentPreset.FreqPLR = 0; /*                               */
	CurrentPreset.FreqMLR = 0; /*                               */
	CurrentPreset.Amp2Flag = 0xfffa; /* CHOICE structure, so 0=Off    */
	CurrentPreset.Amp1 = 100; /*                               */
	CurrentPreset.AmpScrubTime = 100; /* Ground detect mode, Amplitude */
	CurrentPreset.AmpTrigTimeValue = TIME_MIN;/*                               */
	CurrentPreset.AmpTrigEnerValue = ENERGY_MIN;/* 50 = 5.0 J                  */
	CurrentPreset.AmpTrigPowerValue = POWER_MIN;/*                             */
	CurrentPreset.AmpTrigColValue = 4; /* 4  = 0.0004"                  */
	CurrentPreset.AmpTrigExtFlag = 0; /*                               */
	CurrentPreset.Amp2 = 100; /*                               */
	CurrentPreset.AutoTrigFlag = TRUE; /* Acts like Radio Button        */
	CurrentPreset.PreTriggerDistanceFlag = TRUE; /* True = off Radio Button       */
	CurrentPreset.PreTriggerDistance = ABS_MIN; /* 1250 = 0.1250"                */
	CurrentPreset.PreTrigAmp = 100; /*                               */
	CurrentPreset.PreTrigFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.PreTrigDelayFlag = TRUE; /* Pretrigger as time mode off   */
	CurrentPreset.PreTrigDelay = TIME_MIN; /* Pretrigger time delay         */
	CurrentPreset.ExtTrgDelay = 0; /*Ext Delay disabled, By default */
	CurrentPreset.EnergyBraking = 0; /*Energy Braking is disabled     */
	CurrentPreset.RTFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.HoldPressureFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.RTDist = 1000; /*                               */
	CurrentPreset.WeldCount = 0; /*                               */
	CurrentPreset.TestAmp = TEST_AMP; /*                               */
	CurrentPreset.EnergyCompFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.SuspectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.RejectLimitsFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.CycleAbortFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.GndDetectFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.SusResetRequired = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.RejResetRequiredFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.Verified = FALSE;
	CurrentPreset.Validated = FALSE;
	CurrentPreset.Locked = FALSE;
	CurrentPreset.PresetUpdateComplete = TRUE;
	CurrentPreset.HwCnfg = 0;
	//Initialize Write In Fields
	for (x = 0; x < WRITEINLEN - 2; x++)
	{ /* Clear write in fields */
  		CurrentPreset.WriteIn1[x] = ' ';
  		CurrentPreset.WriteIn2[x] = ' ';
	}
	CurrentPreset.WriteIn2[WRITEINLEN - 2] = 0;
	CurrentPreset.WriteIn2[WRITEINLEN - 1] = 0;
	CurrentPreset.WriteIn1[WRITEINLEN - 2] = 0;
	CurrentPreset.WriteIn1[WRITEINLEN - 1] = 0;
	CurrentPreset.EBTime = EB_DEF_TIME; /* Def value for energy braking   */
	CurrentPreset.Rev=0;//new added for rev number
	CurrentSetup.ActivePreset = 0;
	CurrentSetup.AdvanceCounters = 1; /* 1 = all  */
	CurrentSetup.AmpControl = 1; /* 1 = internal  */
	CurrentSetup.FreqControl = 1; /* 1 = internal  */
	CurrentSetup.DigTuneFlag = FALSE;
	CurrentSetup.DigTune = 0;
	CurrentSetup.SecurityLevel = BRANSON;
	CurrentSetup.PwrOutTable[0] = 0; /* need to remove when calibration working */
	CurrentSetup.PwrOutTable[1] = 167;
	CurrentSetup.PwrOutTable[2] = 333;
	CurrentSetup.PwrOutTable[3] = 500;
	CurrentSetup.PwrOutTable[4] = 667;
	CurrentSetup.PwrOutTable[5] = 833;
	CurrentSetup.PwrOutTable[6] = 1000;
	CurrentSetup.PwrOutTable[7] = 1167;
	CurrentSetup.PwrOutTable[8] = 1333;
	CurrentSetup.PwrOutTable[9] = 1500;
	CurrentSetup.PwrOutTable[10] = 1500;
	CurrentPreset.GeneralAlarmLFlag = FALSE;
	CurrentPreset.DigitalFilterFlag = TRUE;
	CurrentPreset.ActClrDistance = ABS_MIN;
	CurrentPreset.ActClrFlag = 0; /* Choice structure so 0=off    */
	CurrentPreset.MissingPartFlag = 0;
	CurrentPreset.MissingMinFlag = 1; /* Pointer to disable/enable flag    */
	CurrentPreset.MissingMaxFlag = 1; /* Pointer to disable/enable flag    */
	CurrentPreset.MissingPartMin = ABS_MIN; /* 1250 = 0.1250"              */
	CurrentPreset.MissingPartMax = ABS_MIN; /* 1250 = 0.1250"              */
	CurrentPreset.PMCLowLimit = 5; /* Def % value for PMC Low Limit  */
	CurrentPreset.PMCHighLimit = 5; /* Def % value for PMC High Limit */
	CurrentPreset.PMCTimeout = 5; /* Default PMC Timeout                */
	CurrentPreset.PMCCycleCount = 0;
	CurrentPreset.PMCEnabled = FALSE; /* Power match Curve Disabled*/
	CurrentPreset.PMCPlusBandFlag = TRUE;
	CurrentPreset.PMCMinusBandFlag = TRUE;
	// Initialize PMC data points
	for (x = 0; x < PMCDATAPOINTS; x++)
	{
  		CurrentPreset.PMCData[x] = 0xFF;
	}
	CurrentSetup.TestMultiplier = TESTTIMEx1;
	CurrentSetup.TimeMultiplier = WELDTIMEx1;
	CurrentSetup.HornDownSpd = 15;
	CurrentSetup.BeeperAlarm = TRUE;
	CurrentSetup.BeeperTrigger = TRUE;
	CurrentSetup.BeeperRelease = FALSE;
	CurrentSetup.BeeperError = TRUE;
	CurrentSetup.CustomAct = FALSE; /* Choice structure so 0=off  */
	CurrentSetup.PartClampDelay = EXT_CLAMPDELAY_TIMEOUT;
	CurrentSetup.PLCControlMenuFlag = FALSE; /* Remove entry from menu */
	CurrentSetup.PLCControlFlag = FALSE; /* Now make sure its off  */


	CurrentPreset.BatchFunction = 0;
	CurrentPreset.BatchCountWithAlarm = 0;
	CurrentPreset.BatchCountReset = 0;
	CurrentPreset.BatchCount = BATCHCNTR_MAX;
	CurrentPreset.CurrBatchCount = 0;
	strcpy(CurrentPreset.ActAssemblyNum, "DEFAULT");
	strcpy(CurrentPreset.PSAssemblyNum, "DEFAULT");
	strcpy(CurrentPreset.StackAssemblyNum, "DEFAULT");

	/* New values for 2000XC */
	CurrentPreset.Downspeed = DOWNSPEED_DEFAULT;
	CurrentPreset.HoldPressure = HOLDPRESSURE_DEFAULT; //OFF
	CurrentPreset.WeldPressure = WELDPRESSURE_DEFAULT;
	CurrentPreset.TrigForcePLT = CurrentSetup.MinTrigForce;
	CurrentPreset.TrigForceMLT = CurrentSetup.MinTrigForce;
	CurrentPreset.TrigDistancePLT = TRIGDIST_MIN;
	CurrentPreset.TrigDistanceMLT = TRIGDIST_MIN;
	CurrentPreset.AmpAPLT = AMP_MIN;
	CurrentPreset.AmpAMLT = AMP_MIN;
	CurrentPreset.HoldTimePLT = TIME_MIN;
	CurrentPreset.HoldTimeMLT = TIME_MIN;
	CurrentPreset.DownspeedPLT = MIN_DOWNSPEED;
	CurrentPreset.DownspeedMLT = MIN_DOWNSPEED;
	CurrentPreset.WeldPressurePLT = WELDPRESSURE_MIN;
	CurrentPreset.WeldPressureMLT = WELDPRESSURE_MIN;
	CurrentPreset.HoldPressurePLT = HOLDPRESSURE_MIN;
	CurrentPreset.HoldPressureMLT = HOLDPRESSURE_MIN;
	CurrentPreset.WeldTimePLT = TIME_MIN;
	CurrentPreset.WeldTimeMLT = TIME_MIN;
	CurrentPreset.WeldEnergyPLT = ENERGY_MIN;
	CurrentPreset.WeldEnergyMLT = ENERGY_MIN;
	CurrentPreset.PeakPowerPLT = POWER_MIN;
	CurrentPreset.PeakPowerMLT = POWER_MIN;
	CurrentPreset.CollapseDistPLT = COL_MIN;
	CurrentPreset.CollapseDistMLT = COL_MIN;
	CurrentPreset.AbsDistPLT = ABS_MIN;
	CurrentPreset.AbsDistMLT = ABS_MIN;
	CurrentPreset.ScrubTimePLT = 1;
	CurrentPreset.ScrubTimeMLT = 1;
	CurrentPreset.ScrubAmpPLT = AMP_MIN;
	CurrentPreset.ScrubAmpMLT = AMP_MIN;

	strcpy(CurrentPreset.HornID, "DEFAULT");
	CurrentPreset.MPressureLimit = MPRESSURELIM_MAX;
	CurrentPreset.PPressureLimit = PPRESSURELIM_MAX;
	CurrentPreset.PressureLimitFlag = 0; /* CHOICE structure, so 0=Off    */
	CurrentPreset.PresetConfigNum = 0;
	CurrentPreset.TriggerDistance = TRIGDIST_MIN;
	CurrentPreset.Validated = 0;
	CurrentPreset.Locked = 0;
	CurrentPreset.VelocityMLR = VELOCITYMLR_DEFAULT;
	CurrentPreset.VelocityPLR = VELOCITYPLR_DEFAULT;
	CurrentPreset.WeldTrigger = TRIGGERBY_FORCE;

	// This needs to be called to set the flow to the new value
	CurrentPreset.TunedPreset = FALSE;
	CurrentPreset.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
	SetFlowValue = CurrentPreset.TunedFlowValue;

	//Assign Pressure defaults here
	CurrentPreset.PressureTrigColValue = COL_MIN;
	CurrentPreset.PressureTrigExtFlag = OFF;
	CurrentPreset.PressureTrigTimeValue = TIME_MIN;
	CurrentPreset.PressureTrigEnerValue = ENERGY_MIN;
	CurrentPreset.PressureTrigPowerValue = POWER_MIN;
	CurrentPreset.Pressure2Flag = 0xFFFA;
	CurrentPreset.Pressure2 = WELDPRESSURE_MAX;

	switch (CurrentSetup.PSFreq)
	{
	case FREQ15KHZ:
  		CurrentPreset.DUPS_HostParamSet = DUPS_Default15KParamSet;
  		break;
	default:
	case FREQ20KHZ:
  		CurrentPreset.DUPS_HostParamSet = DUPS_Default20KParamSet;
  	break;
	case FREQ30KHZ:
  		CurrentPreset.DUPS_HostParamSet = DUPS_Default30KParamSet;
  		break;
	case FREQ40KHZ:
  		CurrentPreset.DUPS_HostParamSet = DUPS_Default40KParamSet;
  		break;
	}
	CurrentPreset.DUPS_HostParamSet.Power = CurrentSetup.PSWatt;
   /**  **  Set user definable I/O back to factory default  **  **/
   SetUserIOToFactoryDefault();

   /**  **  Set actuator switches back to factory default  **  **/

   SetActuatorSwitchesToFactoryDefault();

   CurrentPreset.WeldStatusFlag = TRUE;
   CurrentSetup.ExtPresets = FALSE;
   DealWithExtPresetChange();

   /**  **  Set USB parameters back to factory defaults  **  **/
   SetUSBToFactoryDefault();

   /** SBL initialization**/
   InitSBL();

   CurrentSetup.WelderAddrFlag = 1; /* VARIABLE structure, so 1=Off   */
   CurrentSetup.WelderAddrValue = 100; /* Default = ID of 100            */

   CurrentSetup.HmenuIndex = 0;

   CurrentSetup.BasicExpert = EXPERT;
   CurrentSetup.HornClamp = OFF;
   CurrentSetup.UDIScan = OFF;
   CurrentSetup.Automation = OFF;
   CurrentSetup.MemoryFull = STOP;
   CurrentSetup.UserIDTable = WELDER;
   CurrentSetup.AuthorityCheck = OFF;
   strcpy(CurrentSetup.BarcodeStart, "#");
   strcpy(CurrentSetup.StackAssemblyNum, "DEFAULT");
   strcpy(CurrentSetup.ActAssemblyNum, "DEFAULT");
   strcpy(CurrentSetup.PSAssemblyNum, "DEFAULT");
   
   CurrentSetup.HWVerify = 0;
   //CurrentSetup.WeldStorageFormat = BINARY;
   CurrentSetup.BeeperEstop = ON;
   CurrentSetup.Reserved = OFF;
   CurrentSetup.IdleLogoutTime = 1440;
   ColdStartDone = TRUE;
   CurrentSetup.DUPS_WorkingPreset = DUPS_CURRPARAMSET;
   /*-- Get Date of last saved preset --*/
   LastDatePresetWasSaved();

}

extern BOOLEAN NextMenuFlag;

void DoColdStart(void)
/****************************************************************************/
/*                                                                          */
/* Performs a "cold start" by recalling the COLD START preset. It clears    */
/* alarms that can be cleared (those that don't always require a RESET) and */
/* centers the digital pot.                                                 */
/* VERY IMPORTANT: STATE MACHINE MUST BE SUSPENDED WHEN THIS FUNCTION IS    */
/* CALLED.  This is necessary to allow the digital pot position to be       */
/* changed, also prevents unfriendly activities while the cold start is     */
/* going on.                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;

   StopStateMachine(); /* Perform cold start only if not welding */
   if (CurrentPreset.PresetUpdateComplete == TRUE)
      WritePreset(CurrentSetup.ActivePreset); /* Save Current Preset */


   ColdStartInProcess = TRUE;
   CenterDigTune();
   RecallColdstartPreset(0);


   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0); /* Updates Running Preset */
   UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);

   SetAmpControl();
   SetFreqControl();

   ClearFinalResults();
   ClearWeldData();
   WeldingResults.CycleCount = 0;
   SetupAlarmFlag = FALSE; /* Clear any leftover setup alarms  */

   /*-----     Clear all setup alarms here   -----*/

   ClearSetupAlarms();
   CountAlarms();

   if (TotalAlarmCount == 0)
   {
      AlarmsReset = TRUE;
      AlarmDetectedFlag = FALSE;
      AlarmOff();
   }

   PresetHasBeenOKed = FALSE; /* Ensure a check on new start signal*/

   DUPS_Info.WeldStatusFlag = TRUE; /* Initialize weld status flag*/

   if (DUPS_Info.DUPSFlag)
   {
      //      DUPS_UploadParamSet(0); /* Upload factory default Parameter Set */
      //      DUPS_Wait4CurrPS();
      //      DUPS_CurrentParamSet.SeekTime = 500; /* Seek time and seek flag value hard coded*/
      //      DUPS_CurrentParamSet.WeldRampTime = 80; /* Seek time and seek flag value hard coded*/

      /* During Coldstart, force Memory = On and Timed Seek = Off.*/
      DUPS_Info. DUPSMemFlag = TRUE;
      DUPS_Info. DUPSSeekFlag = FALSE;
      DUPS_Info. DUPSMemRstFlag = FALSE;

      //      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN
      //            | DUPS_SWDIPSTOREMEMATWLDEND; /* external amp control */
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;
      DUPS_ModifySWDipSetting(); 
      //      CurrentPreset.DUPSPreset = 0; /* Tell RADIO menu its DUPS Parameter set 0 */
   }


   if (!ColdStartFlag) /* Special test if PowerUpColdStart   */
   {
      MainKeyFlag = TRUE;
      BlankMenuCounter = 1; /* Prevent Main Menu display */
      SendFakeKeyPress( SetupKey); /* Display Weld Setup Screen */
   }
   CurrentPreset.PresetUpdateComplete = TRUE;
   CurrentSetup.ActivePreset = 0;
   strcpy(CurrentPreset.PresetID, "Preset0 "); /* Name it Preset0  */

   for (x = 0; x < WRITEINLEN - 2; x++)
   { /* Clear write in fields */
      CurrentPreset.WriteIn1[x] = ' ';
      CurrentPreset.WriteIn2[x] = ' ';
   }
   CurrentPreset.WriteIn2[WRITEINLEN - 2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN - 1] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN - 2] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN - 1] = 0;

   /* CheckFramDefaults();    *//* See if FRAM is initialized & working */
   ColdStartInProcess = FALSE;
   CurrentSetup.BaudRate = BAUD_9600;

   CurrentSetup.SerialPort = RS232DISABLED;

   if(CurrentSetup.Actuator == MICROC)
   {
	   CurrentSetup.LowerFlowValveFlag = TRUE;
   }
   else
   {
	   CurrentSetup.LowerFlowValveFlag = FALSE;
   }

   CurrentSetup.WebServiceAutomation = TRUE;
   CurrentSetup.WebServiceAutorityCheck = TRUE;

   SetupPressureStepFlag();
   SetupAmplitudeStepFlag();

   InitSBL();

   ResetStateMachine();
   StartStateMachine();
   CSCompleteFlag = TRUE;
   NextMenuFlag = TRUE;
}

void CreateColdStart(void)
/****************************************************************************/
/*                                                                          */
/* Performs a "cold start".  This involves:                                 */
/* Reseting parameters to default values, clearing alarms that can be       */
/* cleared (those that don't always require a RESET) and centering digital  */
/* pot.                                                                     */
/*                                                                          */
/* VERY IMPORTANT: STATE MACHINE MUST BE SUSPENDED WHEN THIS FUNCTION IS    */
/* CALLED.  This is necessary to allow the digital pot position to be       */
/* changed, also prevents unfriendly activities while the cold start is     */
/* going on.                                                                */
/*                                                                          */
/* WHEN FINISHED THIS FUNCTION WILL SAVE THE COLD START VALUES IN THE       */
/* COLD START PRESET.  THIS PRESET WILL BE RECALLED WHEN A COLD START IS    */
/* NEEDED BY DoColdStart() above.  This allows specials which would define  */
/* a different set of cold start values.                                    */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;

   if (CurrentPreset.PresetUpdateComplete == TRUE)
      WritePreset(CurrentSetup.ActivePreset); /* Save Current Preset */

   ColdStartInProcess = TRUE;
   CenterDigTune();
  
   strcpy(MinLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(MaxLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/	
   SetMaxMinValues(); /* This call was after SetDefaultValues.  It was moved because saving */
   
   
   strcpy(CurrentPreset.PresetID, "COLD START");                                  /*     it will allow restore the values as a factory*/
   SetDefaultValues(); /* Min/Max values now messes up the currentpreset.                    */  
   Readpreset(PRESET_COLDSTART_INDEX, &CurrentPreset);

   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0); /* Updates Running Preset */
   UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);

   SetAmpControl();
   SetFreqControl();

   ClearFinalResults();
   ClearWeldData();
   WeldingResults.CycleCount = 0;
   SetupAlarmFlag = FALSE; /* Clear any leftover setup alarms  */

   /*-----     Clear all setup alarms here   -----*/
   ClearSetupAlarms();
   CountAlarms();

   if (TotalAlarmCount == 0)
   {
      AlarmsReset = TRUE;
      AlarmDetectedFlag = FALSE;
      AlarmOff();
   }

   PresetHasBeenOKed = FALSE; /* Ensure a check on new start signal*/


   DUPS_Info.WeldStatusFlag = TRUE; /* Initialize weld status flag*/

   if (DUPS_Info.DUPSFlag)
   {
      //      DUPS_UploadParamSet(0); /* Upload factory default Parameter Set */
      //      DUPS_Wait4CurrPS();
      //      DUPS_CurrentParamSet.SeekTime = 500; /* Seek time and seek flag value hard coded*/
      //      DUPS_CurrentParamSet.WeldRampTime = 80; /* Seek time and seek flag value hard coded*/

      /* During Coldstart, force Memory = On and Timed Seek = Off.*/
      DUPS_Info. DUPSMemFlag = TRUE;
      DUPS_Info. DUPSSeekFlag = FALSE;
      DUPS_Info. DUPSMemRstFlag = FALSE;

      //      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN
      //            | DUPS_SWDIPSTOREMEMATWLDEND; /* external amp control */
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;
      DUPS_QueuedDownloadPS(); /* establish default DUPS Current Parameter Set*/
      //      CurrentPreset.DUPSPreset = 0; /* Tell RADIO menu its DUPS Parameter set 0 */
   }

   RTOS::DelayMs(SECONDS_TO_TICKS( 3 ) * MILLS_PER_TICK);

   if (!ColdStartFlag) /* Special test if PowerUpColdStart   */
   {
      MainKeyFlag = TRUE;
      BlankMenuCounter = 1; /* Prevent Main Menu display */
      SendFakeKeyPress( SetupKey); /* Display Weld Setup Screen */
   }
   CurrentPreset.PresetUpdateComplete = TRUE;

   strcpy(CurrentPreset.PresetID, "Preset0 "); /* Name it Preset0  */

   for (x = 0; x < WRITEINLEN - 2; x++)
   { /* Clear write in fields */
      CurrentPreset.WriteIn1[x] = ' ';
      CurrentPreset.WriteIn2[x] = ' ';
   }
   CurrentPreset.WriteIn2[WRITEINLEN - 2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN - 1] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN - 2] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN - 1] = 0;

   /* CheckFramDefaults();    *//* See if FRAM is initialized & working */
   ColdStartInProcess = FALSE;
   CurrentSetup.BaudRate = BAUD_9600;

   strcpy(CurrentPreset.PresetID, "COLD START"); /* Name it              */
   SavePreset(PRESET_COLDSTART_INDEX, &CurrentPreset);
}


/*
*
*   Purpose:
*   Get the address in the memory for preset. For preset numbers less than
*   32 and special presets it returns the address of preset in FRAM. For
*   presets resided in Nand flash it returns the global ram preset object
*   address.
*
*   Entry condition:
*   PresetNumber- information about the preset you want to read.
*
*   Exit condition:
*   return the address of the Preset read
*/
SETUPS_Ver1200 * CalculatePresetAddress(UINT16 PresetNumber)
{
   SETUPS_Ver1200 * RetAddress = NULL;
   if(PresetNumber <=32)
      RetAddress = PRESET_N_START(PresetNumber);
   else if(PresetNumber <= 1000)
      RetAddress = &LocalPresetCopyOfFlash;
   else if(PresetNumber == PRESET_COLDSTART_INDEX)
      RetAddress = PRESET_N_START(PRESET_COLDSTART);
   else if(PresetNumber == PRESET_MIN_INDEX)
      RetAddress = PRESET_N_START(PRESET_MIN);
   else if(PresetNumber == PRESET_MAX_INDEX)
      RetAddress = PRESET_N_START(PRESET_MAX);
   else if (PresetNumber == PRESET_RUNNING_INDEX)
	   RetAddress = PRESET_N_START(PRESET_RUNNING);
   else
   {
   	   RetAddress = &LocalPresetCopyOfFlash;//Better to point some where than crashing
   	   LocalPresetCopyOfFlash.WeldMode = 0;//but make sure it never run
   }
   return(RetAddress);
}

/*
*
*   Purpose:
*   Read Preset Object from flash or FRAM based on the preset number.
*
*   Entry condition:
*   PresetNumber- preset you want to read.
*   DestPtr- Pointer to buffer. If the argument is not null function copies the read preset object
*   from FRAM or flash in this buffer.
*
*   Exit condition:
*   Returns the address of the Preset read. If the preset lies in FRAM it returns the
*   address of preset FRAM location. If preset lies in Nand Flash it return the address of
*   preset copy read in RAM.
*/
SETUPS_Ver1200 * Readpreset(UINT16 PresetNumber,SETUPS_Ver1200 *DestPtr)
{
   SETUPS_Ver1200 * Address = CalculatePresetAddress(PresetNumber);
   UINT8 ErrorCode = 0;
   if((PresetNumber > NUM_USERPRESETS_FRAM) && (PresetNumber <= MAX_POSSIBLE_PRESET)) {
      ErrorCode  = NandFlash::NandPtr->ReadPreset(Address, PresetNumber);
      CopyInfoToPreset(Address, PresetNumber);
   }
   if((Address != NULL) &&(ErrorCode == NAND_SUCCESS) && (DestPtr != NULL))
   {
      memcpy(DestPtr, Address,sizeof(SETUPS_Ver1200));
      CopyInfoToPreset(DestPtr, PresetNumber);
   }
   return (Address);
}


/*
*   Purpose:
*   Write Preset object to FRAM or flash based on the preset number.
*
*   Entry condition:
*   PresetNumber- Preset to be changed.
*   SourcePtr- If not null contains the modified preset to be written on memory.
*
*/
void SavePreset(UINT16 PresetNumber,SETUPS_Ver1200 *SourcePtr)
{
   SETUPS_Ver1200 * Address = CalculatePresetAddress(PresetNumber);
   if(Address != NULL)
   {
      if(SourcePtr != NULL)
         memcpy(Address, SourcePtr, sizeof(SETUPS_Ver1200));
      if((PresetNumber > NUM_USERPRESETS_FRAM) && (PresetNumber <= MAX_POSSIBLE_PRESET))
         NandFlash::NandPtr->WritePreset(Address, PresetNumber);
   }
}


void SetupPretriggerFlags(void)
{
   // strange, but true: PreTrigFlag   PreTrigDistFlag  PreTrigDelayFlag
   // no pretrigger        FALSE             TRUE             TRUE
   // auto pretrigger      TRUE              TRUE             TRUE
   // distance pretrigger  TRUE              FALSE            TRUE
   // time pretrigger      TRUE              TRUE             FALSE

   FlagPretriggerOff = CurrentPreset.PreTrigFlag ? FALSE : TRUE;
   FlagPretriggerAmpl = FlagPretriggerOff ? FALSE : TRUE;
   /* Flag is used for pretrigger amplitude, if enabled and internally controlled */
   FlagPretriggerAmpl = (FlagPretriggerAmpl && CurrentSetup.AmpControl) ? TRUE
         : FALSE;
   FlagPretriggerAuto
         = (CurrentPreset.PreTrigFlag && CurrentPreset.PreTriggerDistanceFlag
               && CurrentPreset.PreTrigDelayFlag) ? TRUE : FALSE;
   FlagPretriggerTime = CurrentPreset.PreTrigDelayFlag ? FALSE : TRUE;
   FlagPretriggerDist = CurrentPreset.PreTriggerDistanceFlag ? FALSE : TRUE;
}

void SetupTriggerFlags(void)
{
   if(CurrentPreset.WeldTrigger == TRIGGERBY_FORCE){
      FlagTriggerByDist = FALSE;
      FlagTriggerByForce = TRUE;
   }
   else
   {
      FlagTriggerByDist = TRUE;
      FlagTriggerByForce = FALSE;
   }
}

void SetUserIOToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set the user definable I/O back to the factory       */
/*  defaults.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT32 FramStatus;

   CurrentSetup.J3_32In = INPUT_PRESET1; // Select preset 1
   CurrentSetup.J3_32Ptr = GetInputPtr(INPUT_PRESET1);
   CurrentSetup.J3_33In = INPUT_PRESET2; // Select Preset 2
   CurrentSetup.J3_33Ptr = GetInputPtr(INPUT_PRESET2);
   CurrentSetup.J3_19In = INPUT_PRESET3; // Select Preset 3
   CurrentSetup.J3_19Ptr = GetInputPtr(INPUT_PRESET3);
   CurrentSetup.J3_17In = INPUT_PRESET4; // Select Preset 4
   CurrentSetup.J3_17Ptr = GetInputPtr(INPUT_PRESET4);
   CurrentSetup.J3_31In = INPUT_DISP_LOCK; // Display Lock.
   CurrentSetup.J3_31Ptr = GetInputPtr(INPUT_DISP_LOCK);
   CurrentSetup.J3_1In = INPUT_EXT_TRIGGER; // Ext Trigger.
   CurrentSetup.J3_1Ptr = GetInputPtr(INPUT_EXT_TRIGGER);
   CurrentSetup.J3_36Out = OUTPUT_DISABLED; //  Disable outputs by default
   CurrentSetup.J3_8Out = OUTPUT_DISABLED; //  Disable outputs by default
   CurrentSetup.J3_22Out = OUTPUT_DISABLED; //  Disable outputs by default
   UserCfgOutputOn(OUTPUT_DISABLED); /* Write 24 volts to pins */
   CurrentSetup.UserInLogic = FALSE;
   CurrentSetup.PartClampDelay = EXT_CLAMPDELAY_TIMEOUT;//  External Start Delay

   /* Store CurrentSetup Parameter Change from DRAM to BATTRAM */
   FramStatus = FramAccess(FRAM_WRITE, CONFIG_SECTION,
         (UINT8 *) &CurrentSetup, (UINT32) FRAM1200_CONFIG_START,
         sizeof(CurrentSetup));

}

void SetActuatorSwitchesToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set the actuator switches back to the factory        */
/*  default value.                                                          */
/*                                                                          */
/****************************************************************************/
{
   CurrentSetup.GndDetLogicCustom = TRUE; /*Custom Menu Defaults.*/
   CurrentSetup.ULSLogicCustom = TRUE;
}


void SetUSBToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will turn off all USB on sample and USB on alarm          */
/*  functions.  This is the same as cold start, except only USB params are  */
/*  affected.                                                               */
/*                                                                          */
/****************************************************************************/
{
   MaxSampleValue = COUNTER_MAX;
   MinSampleValue = 1;
   CurrentSetup.USBGlobalFlag = FALSE;
   CurrentSetup.USBWDSampleFlag = TRUE;
   CurrentSetup.USBPGSampleFlag = TRUE;
   CurrentSetup.USBAGSampleFlag = TRUE;
   CurrentSetup.USBFreqGSampleFlag = TRUE;
   CurrentSetup.USBCDGSampleFlag = TRUE;
   CurrentSetup.USBVGSampleFlag = TRUE;
   CurrentSetup.USBFGSampleFlag = TRUE;
   CurrentSetup.USBWDAlarmFlag = FALSE;
   CurrentSetup.USBPGAlarmFlag = FALSE;
   CurrentSetup.USBAGAlarmFlag = FALSE;
   CurrentSetup.USBFreqGAlarmFlag = FALSE;
   CurrentSetup.USBCDGAlarmFlag = FALSE;
   CurrentSetup.USBVGAlarmFlag = FALSE;
   CurrentSetup.USBFGAlarmFlag = FALSE;
   CurrentSetup.USBWDSampleValue = 1;
   CurrentSetup.USBPGSampleValue = 1;
   CurrentSetup.USBAGSampleValue = 1;
   CurrentSetup.USBFreqGSampleValue = 1;
   CurrentSetup.USBCDGSampleValue = 1;
   CurrentSetup.USBVGSampleValue = 1;
   CurrentSetup.USBFGSampleValue = 1;

}

void SetupAmpModeStepFlag(void)
{
   if ((CurrentPreset.Amp2Flag & BIT0) == BIT0)
   {
      AmplitudeStepEnableFlag.boolEAN = TRUE;
      AmplitudeStepEnableFlag.Uint16.Hi = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
      AmpStepEnable = TRUE;
   } else
   {
      AmplitudeStepEnableFlag.boolEAN = FALSE;
      AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
      AmplitudeFixedEnableFlag = TRUE;
      AmpStepEnable = FALSE;
   }
}

void SetupAmplitudeStepFlag(void)
{
   if ((CurrentPreset.Amp2Flag & BIT0) == BIT0)
   {
      AmplitudeStepEnableFlag.boolEAN = TRUE;
      AmplitudeStepEnableFlag.Uint16.Hi = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
   } else
   {
      AmplitudeStepEnableFlag.boolEAN = FALSE;
      AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
      AmplitudeFixedEnableFlag = TRUE;
   }
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called to get the flag values for the Pressure
*   Stepping menu.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SetupPressureFixedOrStepFlag(void)
{
   if ((CurrentPreset.Pressure2Flag & BIT0) == BIT0) {
      PressureStepEnableFlag.boolEAN = TRUE;
      PressureStepEnableFlag.Uint16.Hi = TRUE;
      PressureFixedEnableFlag = FALSE;
      PressureStepEnable = TRUE;
   }
   else {
      PressureStepEnableFlag.boolEAN = FALSE;
      PressureStepEnableFlag.Uint16.Hi = FALSE;
      PressureFixedEnableFlag = TRUE;
      PressureStepEnable = FALSE;
   }
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called to initialize Pressure Stepping flags to enable
*   or disable the trigger point buttons in SBC menu.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SetupPressureStepFlag(void)
{
   if ((CurrentPreset.Pressure2Flag & BIT0) == BIT0) {
      PressureStepEnableFlag.boolEAN = TRUE;
      PressureStepEnableFlag.Uint16.Hi = TRUE;
      PressureFixedEnableFlag = FALSE;
   }
   else {
      PressureStepEnableFlag.boolEAN = FALSE;
      PressureStepEnableFlag.Uint16.Hi = FALSE;
      PressureFixedEnableFlag = TRUE;
   }
}

void GetPresetNum (void)
/*****************************************************************************/
/*Description:                                                               */
/*   This function gets current preset number                                */
/*****************************************************************************/
{
   if(CurrentSetup.ActivePreset > 0)
	   VGAPresetNum = CurrentSetup.ActivePreset;
   else
	   VGAPresetNum = 1;

}
void GetSequenceNos (void)
/*****************************************************************************/
/*Description:                                                               */
/*   This function gets current sequence number                              */
/*****************************************************************************/
{
   if (CurrentSetup.SequenceEnable == FALSE ||
       CurrentSetup.SequenceCount == 0 )
      TempSequenceNos = 0;
   else
      TempSequenceNos = CurrentSetup.SequenceNos + 1;
}

void PreparePrstInfoString (void)
/*****************************************************************************/
/*Description:                                                               */
/*   This function prepares the information strings to display in the        */
/*   Information box in Save/Recall Preset screen.                           */
/*****************************************************************************/
{
   UINT16 SelectedPresetNum;
   UINT32 i;
   Ver1200Setups *PresetPtr;
   SINT8 DisplayStr[VGA_LINESIZE];
   memset(DisplayStr, 0, VGA_LINESIZE);
   SelectedPresetNum = VGAPresetNum;
 
 
   PresetPtr = Readpreset(SelectedPresetNum); /* Preset of interest */

   InfoMonth = 0;   /* Clear stuff in case preset is cleared */
   InfoDay = 0;
   InfoYear = 0;
   InfoHour = 0;
   InfoMinute = 0;
   InfoCount = 0;

   /* Prepare Date line   */
   InfoMonth = (SINT32) PresetPtr->PS_DateTime.Century_Month;
   InfoDay = (SINT32) PresetPtr->PS_DateTime.Day;
   InfoYear = (SINT32) PresetPtr->PS_DateTime.Years;

   for(i = 0; (i < VGA_LINESIZE - 2); i++)
         DisplayStr[i] = FILLCHAR;

    if (CurrentSetup.Units == FALSE)
      /*Display Time in MM/DD/YY format*/
      FormatDateStr1(DisplayStr,0, 2, InfoMonth,
                       '/', 2, InfoDay,
                       '/', 2, InfoYear);
   else
      /*Display Time in the DD/MM/YY format.*/
      FormatDateStr1(DisplayStr,0, 2, InfoDay,
                       '/', 2, InfoMonth,
                       '/', 2, InfoYear);

   strncpy(InfoLine4,Trim_FillChar(DisplayStr),sizeof(InfoLine4)-1);


   /* Prepare Time line   */
   InfoHour = (SINT32) PresetPtr->PS_DateTime.Hour;
   InfoMinute = (SINT32) PresetPtr->PS_DateTime.Minute;

   for(i = 0; (i < VGA_LINESIZE - 2); i++)
         DisplayStr[i] = FILLCHAR;


   FormatTimeStr1(DisplayStr, 0, 2, InfoHour,':', 2, InfoMinute);
   strncpy(InfoLine5,Trim_FillChar(DisplayStr) , VGA_LINESIZE - 1);
   /* Prepare cycle count */
   if ((CurrentSetup.ActivePreset == SelectedPresetNum)
        && (CurrentPreset.PresetUpdateComplete == TRUE))
      InfoCount = FRAMPresetInfo[0].WeldCount;  /* Preset asked for is current preset so */
   else                                         /* include cycles run since recalled     */
      InfoCount = FRAMPresetInfo[SelectedPresetNum].WeldCount;

   sprintf (DisplayStr, "%ld", InfoCount );
   strcpy(InfoLine6, DisplayStr);

   /* Prepare 'Verified'  */
   if (FRAMPresetInfo[SelectedPresetNum].Verified)
      strcpy(InfoLine3, "1");    /*Yes*/
   else
      strcpy(InfoLine3, "0");     /*No*/
      
    /*Prepare 'Validated'    */
    
    if (FRAMPresetInfo[SelectedPresetNum].Validated)
    	strcpy(InfoLine2, "1");    /*Yes*/
   	else
   		strcpy(InfoLine2, "0");   /*No*/
      
      
      
}

void SetPresetClearFlags (void)
/****************************************************************************/
/*Description:                                                              */
/* Clears VGA preset clear flags                                            */
/****************************************************************************/
{
	if ((CurrentSetup.AuthorityCheck == FALSE) || (CurrentUser.UserLevel > TECHNICIAN)) {
		if (PresetEnableFlags[VGAPresetNum]) {
			NackError = WELDER_PROCESS_ERROR;
			ErrorResponseMinLimit = SHOW_MSG_SCREEN;
			ErrorResponseMaxLimit = 0;
		}

	} else {
		/*Technician cannot clear a locked Preset*/
		if ((FRAMPresetInfo[VGAPresetNum].Locked == TRUE)
				&& (CurrentSetup.SecurityLevel < SUPERVISOR)) {		
			NackError = WELDER_PROCESS_ERROR;
			ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
			ErrorResponseMaxLimit = 0;
		} else {
			if (PresetEnableFlags[VGAPresetNum]) {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = SHOW_MSG_SCREEN;
				ErrorResponseMaxLimit = 0;
			}

		}
	}

}

/****************************************************************************/
/*Description:                                                              */
/* Rearranges sequence list when a preset is deleted                        */
/* Input - preset nos                                                       */
/****************************************************************************/

void RearrangeSeqList(UINT16 PresetNos)
{
   UINT16 TempSeqList[MAX_SEQUENCE_NOS];
   UINT16 i;
   UINT8 j = 0;

   for(i = 0; i < CurrentSetup.SequenceCount; i++)
   {
      if(CurrentSetup.SequenceList[i] != PresetNos)
         TempSeqList[j++] = CurrentSetup.SequenceList[i];
   }

   CurrentSetup.SequenceCount = j;
   for(i = 0; i < CurrentSetup.SequenceCount; i++)
      CurrentSetup.SequenceList[i] = TempSeqList[i];
   if (CurrentSetup.SequenceNos >= CurrentSetup.SequenceCount)
      CurrentSetup.SequenceNos = 0;


}
void ProcessPresetClear(void)
/****************************************************************************/
/*Description:                                                              */
/* Clears selected preset                                                   */
/****************************************************************************/
{
  if(CheckOperatorAuthority(RecalPreset) == TRUE){//TODO:need seperate authority bit. Using recal authority
	   PresetEnableFlags[VGAPresetNum] = FALSE;
	   PresetClear(VGAPresetNum);
	   GetPresetNames(VGAPresetNum);
	   RearrangeSeqList(VGAPresetNum);
  }
  else{
	  NackError = WELDER_PROCESS_ERROR;
	  ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
	  ErrorResponseMaxLimit = 0;
      }
}

void ProcessPresetRecall (void)
/****************************************************************************/
/*Description:                                                              */
/* Sets selected Preset parameters to the Welder.                           */
/*NOTE: Preset is Recalled only if Welder is either Ready or Pre-ready state*/
/*      and No Graph/Data Printing is going on..                            */
/****************************************************************************/
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;
   
   if(CheckOperatorAuthority(RecalPreset) == FALSE)
   {
       NackError = WELDER_PROCESS_ERROR;
       ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
       ErrorResponseMaxLimit = 0;
   }
   else if(PresetEnableFlags[VGAPresetNum])
   {
      if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        &&(IsGraphDrawing == FALSE))
      {  // Ok to recall preset since no weld in progress
         StopStateMachine();

         if(CurrentPreset.PresetUpdateComplete == TRUE){
            WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
         }

  
        if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
        {  // if there was an associated Parameter set or if this is an analog power supply
           CurrentSetup.ActivePreset = VGAPresetNum;
           UpdateRunningPreset = TRUE;
           ReadPreset(CurrentSetup.ActivePreset, FALSE);
           WritePreset(CURRENT_PRESET_INDEX);                           /* Update Running Preset */
           UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
           DUPS_DownloadCurrPS();
           RefreshDUPSParam ();
//         FinalResults.CycleCount = CurrentPreset.WeldCount;
           ResetStateMachine();
           StartStateMachine();
           ResetRecall_UpdateFlag = TRUE;
           LimitChanged = TRUE;
           /*Go Back to the Run Result Screen*/

        }  // if there was an associated Parameter set or if this is an analog power supply
     } // end of -- Ok to recall preset since no weld in progress
     else  // can't recall preset right now because weld in progress
     {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
         ErrorResponseMaxLimit = 0;
     }  // else can't recall preset right now because weld in progress
   }
}  // end of RecallPreset( UINT16 PresetNum )

UINT16 ProcessPresetVerify(UINT8 ** to)
/*****************************************************************************/
/*Description:                                                               */
/*   This function verify the preset in Ready or Pre-Ready state and display */
/*   the respective results for two seconds. Else this will display an error */
/*   message to wait for ready state.                                        */
/*****************************************************************************/
{
   UINT16 len = 0;
   if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        && (IsGraphDrawing == FALSE))
   {
       if(RecallAndVerifyPreset(VGAPresetNum))
       {
          if(CurrentPreset.Verified)
             len += AddToBuffer(to, 1);
          else
             len += AddToBuffer(to, 0);
       }
   }
   else
      len += AddToBuffer(to, 2);
   return (len);
}

void PreparePrstSaveTitle (void)
/****************************************************************************/
/*Description:                                                              */
/* Sets Save Preset title                                                   */
/****************************************************************************/
{
	if ((CurrentSetup.AuthorityCheck == FALSE) || (CurrentUser.UserLevel > TECHNICIAN)) {
		ActivatePreset(VGAPresetNum);
	} else {
		/* Technician Cannot Overwrite a Locked Preset*/
		if ((PresetEnableFlags[VGAPresetNum] == TRUE)
				&& (FRAMPresetInfo[VGAPresetNum].Locked == TRUE)
				&& (CurrentSetup.SecurityLevel < SUPERVISOR)) {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
				ErrorResponseMaxLimit = 0;
		} else
			ActivatePreset(VGAPresetNum);
	}
}

static void ChangePresetName(void)
/****************************************************************************/
/*Description:                                                              */
/* Save the Welder setting Automatically generated and manual Preset name   */
/****************************************************************************/
{
   UINT16 DUPS_Ascval = DUPS_SUCCESS;
   Ver1200Setups *PresetPtr;
   DUPS_Ascval = DUPS_CURRPARAMSET;
   if(DUPS_Ascval != DUPS_PARAMSETUNDEF)
   {
      if(CurrentPreset.PresetUpdateComplete == TRUE)
         WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */

      //prepare the preset name based on user selcted option. name will go in currentpreset.presetid
      if(VGASavePresetOption == NAME_MODE)
         AutoNamePreset();
      else if ((VGASavePresetOption == NAME_NEW)||
               (VGASavePresetOption == NAME_CURRENT))
         UseSameNamePreset(VGASavePresetOption);
      else
    	 strncpy(CurrentPreset.PresetID, AssignNamePresetBuffer, sizeof(CurrentPreset.PresetID) - 1);

      //update time stamp in current preset
      LastDatePresetWasSaved();
      //Here tell system manager task to write the currentpreset on slot VGAPresetNum. Before that increment revision number for the slot
      PresetPtr =  Readpreset(VGAPresetNum);
      CurrentPreset.Rev = PresetPtr->Rev + 1;
      WritePreset(VGAPresetNum);                  /* Save Active Preset */
      CurrentSetup.ActivePreset = VGAPresetNum;
      //Tell system amanger to Backup current setup changes
      UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
      //Tell system manager to write currenpreset in ram to slot 0
      WritePreset(CURRENT_PRESET_INDEX);                             /* Save Preset Zero */
      //update dups preset now
      DUPS_DownloadCurrPS();
      PresetNeedsToBeUpdated = TRUE;              /* need to verify the preset */

      PresetEnableFlags[VGAPresetNum] = TRUE;

      //PresetPtr =  Readpreset(VGAPresetNum);
      if ((VGASavePresetOption == NAME_NEW)||
          (VGASavePresetOption == NAME_CURRENT)||
          (VGASavePresetOption == NAME_MODE))
         strncpy(PresetPtr->PresetID, CurrentPreset.PresetID, PRESETLEN - 1);
      else
         strncpy(PresetPtr->PresetID,  AssignNamePresetBuffer, PRESETLEN - 1);
      GetPresetNames(VGAPresetNum);          /* Update selected preset with new name */
   }  // else DUPS Paramset was available
}//End of Function.

void SaveNamedPreset(void)
/****************************************************************************/
/*Description:                                                              */
/* Saves the Currently available Welder parameters in manually generated    */
/* generated Preset name.                                                   */
/****************************************************************************/
{
   BOOLEAN IsConfirmRqd = FALSE;
   VGAPresetSaveAborted = FALSE;
   switch(GlobalCommandID){
   case AUTO_NAME:
      VGASavePresetOption = NAME_MODE;
      break;
   case SAME_NAMEAS_OLD:
      VGASavePresetOption = NAME_CURRENT;
      break;
   case SAME_NAMEAS_NEW:
      VGASavePresetOption = NAME_NEW;
      break;
   case ASSIGN_NAME:
      VGASavePresetOption = 0;
      break;
   }
   // Ok to save preset since no weld in progress and there is a DUPS
   if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
         StopStateMachine();
      else
      {
         VGAPresetSaveAborted = TRUE;
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
         ErrorResponseMaxLimit = 0; // for sending Welding on process

      } // else can't recall preset right now because weld in progress
   }

   if( VGAPresetSaveAborted == FALSE)
   {
      if(IsPresetEnabled(VGAPresetNum))
      {
         IsConfirmRqd = TRUE;
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_MSG_SCREEN;
         ErrorResponseMaxLimit = 0;

      }
      else //Confirmation is TRUE
      {
         ChangePresetName();
      }

   }  // end of VGAPresetSaveAborted == FALSE
   if(CheckForDups() == TRUE && !IsConfirmRqd)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   }
}  // end of VGASaveAutoNamedPreset(void)

void PresetSaveOk(void)
/*****************************************************************************/
/*Description:                                                               */
/* If confirmation is OK save the Preset && make it active Preset.           */
/*****************************************************************************/
{
  ChangePresetName();
  ReadOnlyFlag = FALSE;
  if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   }
}

void PresetSaveCancel(void)
/*****************************************************************************/
/*Description:                                                               */
/* If confirmation is Cancel then don't save the preset & bring PRESET_SCREEN*/
/*****************************************************************************/
{
  ReadOnlyFlag = FALSE;
  if(CheckForDups() == TRUE)
   {
      if( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
         ClearAbort();
         ResetStateMachine();
         StartStateMachine();
      }
   }
}

void SaveSpecialPreset (UINT32 SaveCond)
/****************************************************************************/
/*Description:                                                              */
/* Saves the Currently available Welder parameters with the name of the     */
/* CurrentPreset.PresetID.                                                  */
/****************************************************************************/
{
   UINT16 DUPS_Ascval = DUPS_SUCCESS;
   Ver1200Setups *PresetPtr;
   if (DUPS_Ascval == DUPS_PARAMSETUNDEF)
   {
   }
    else
    {
       UseSameNamePreset(SaveCond);  /*Save name as CURRENT_NAME*/
       LastDatePresetWasSaved();
       WritePreset(ActivePreset);           /* Save Active Preset */
       UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
       WritePreset(CURRENT_PRESET_INDEX);                      /* Save Preset Zero */
       DUPS_DownloadCurrPS();
       PresetNeedsToBeUpdated = TRUE;        /* need to verify the preset */
       strcpy(PresetBuffer[LangIndex], CurrentPreset.PresetID);
       PresetEnableFlags[ActivePreset] = TRUE;
       PresetPtr = CalculatePresetAddress(ActivePreset);
       strncpy(PresetPtr->PresetID, PresetBuffer[LangIndex], PRESETLEN - 1);
       GetPresetNames(ActivePreset);          /* Update active preset with new name */
   }

}

void EraseSeqList (void)
{
   CurrentSetup.SequenceNos = 0;
   CurrentSetup.SequenceCount = 0;
}

void EraseSeqList1 (void)
{
   if(CurrentSetup.SequenceCount != 0)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = SHOW_MSG_SCREEN;
      ErrorResponseMaxLimit = 0;
   }
}


void CopyInfoFromPreset(SETUPS_Ver1200 * SrcPtr, UINT16 PresetNum)
/****************************************************************************/
/*Description:                                                              */
/* Copy the Info Parameters from preset to Info Structure in FRAM    		*/
/*                                                 							*/
/****************************************************************************/
{
	FRAMPresetInfo[PresetNum].CurrBatchCount = SrcPtr->CurrBatchCount;
	FRAMPresetInfo[PresetNum].Locked = SrcPtr->Locked;
	FRAMPresetInfo[PresetNum].Validated = SrcPtr->Validated;
	FRAMPresetInfo[PresetNum].Verified = SrcPtr->Verified;
	FRAMPresetInfo[PresetNum].WeldCount = SrcPtr->WeldCount;
}


void CopyInfoToPreset(SETUPS_Ver1200 *DestPtr, UINT16 PresetNum)
/****************************************************************************/
/*Description:                                                              */
/* Copy the Info parameters in FRAM to preset   							*/
/*                                                 							*/
/****************************************************************************/
{
	DestPtr->CurrBatchCount = FRAMPresetInfo[PresetNum].CurrBatchCount;
	DestPtr->Locked = FRAMPresetInfo[PresetNum].Locked;
	DestPtr->Validated = FRAMPresetInfo[PresetNum].Validated;
	DestPtr->Verified = FRAMPresetInfo[PresetNum].Verified;
	DestPtr->WeldCount = FRAMPresetInfo[PresetNum].WeldCount;
}
