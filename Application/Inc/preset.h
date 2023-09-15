/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/preset.h_v   1.30   Jun 07 2017 16:49:18   RJamloki  $ */
#ifndef PRESET_H
#define PRESET_H
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/preset.h_v  $
 * 
 *    Rev 1.30   Jun 07 2017 16:49:18   RJamloki
 * change config variable to LowerFlowValveFlag
 * 
 *    Rev 1.29   Jun 07 2017 15:27:26   RJamloki
 * change config variable to PressureStepDownFlag
 * 
 *    Rev 1.28   May 25 2017 17:48:48   RJamloki
 * Update configuration structures for new hardware version
 * 
 *    Rev 1.27   29 Aug 2016 12:51:56   RJamloki
 * Declare PressureStepDown flag in setup struct
 * 
 *    Rev 1.26   08 Apr 2015 13:55:18   AnPawar
 * Function and variable declaration added for Pressure Stepping.
 * 
 *    Rev 1.25   27 Mar 2015 11:14:46   amaurya
 * Removed Old Preset Structure.
 * 
 *    Rev 1.24   11 Mar 2015 09:23:06   amaurya
 * Setup limit parameters added to Ver1200Setups structure.
 * 
 *    Rev 1.23   30 Jan 2015 08:07:32   amaurya
 * HoldPressureFlag variable added.
 * 
 *    Rev 1.22   08 Jan 2015 03:11:46   AnPawar
 * Macros changed Down speed min , max , default in percent
 * 
 *    Rev 1.21   14 Nov 2014 05:23:48   rjamloki
 * DOWNSPEED_DEFAULT macro added.
 * 
 *    Rev 1.20   10 Nov 2014 04:41:46   AnPawar
 * In Ver1200Setups struct old 32 bit VQS member split into two 16 bit.
 * 
 *    Rev 1.19   20 Oct 2014 06:40:06   AnPawar
 * added define MAX_POSSIBLE_PRESET_BELOW_C
 * 
 *    Rev 1.18   03 Oct 2014 06:27:04   rjamloki
 *  AmpDecayPercent changed to Reserved
 * 
 *    Rev 1.17   26 Sep 2014 02:59:52   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.16   25 Sep 2014 14:14:08   tayars
 * Added flag in preset to know whether tuning has been done on a particular preset or not.
 * 
 *    Rev 1.15   11 Sep 2014 11:25:20   rjamloki
 * coverity and review fixes
 * 
 *    Rev 1.14   05 Sep 2014 04:29:58   rjamloki
 * Removed Compressed preset. Added function prototypes to support 1000 presets.
 * 
 *    Rev 1.13   07 Aug 2014 16:05:22   tayars
 * Added DownspeedTune to config setup and TunedFlowValue to preset and changed variable names.
 * 
 *    Rev 1.12   28 Jul 2014 13:00:38   rjamloki
 * bbram to fram renaming
 * 
 *    Rev 1.11   15 Jul 2014 17:12:42   hasanchez
 * Changes related to Absolute limits (Reject and Suspect).
 * 
 *    Rev 1.10   09 Jul 2014 15:17:30   rjamloki
 * Added CurrbatchCount in preset. Adde HW verify setup enum.
 * 
 *    Rev 1.9   11 Jun 2014 12:59:26   rjamloki
 * Renamed DigPot to Digtune
 * 
 *    Rev 1.8   27 May 2014 10:16:24   amaurya
 * Added WeldHistory setup in current setup
 * 
 *    Rev 1.7   21 May 2014 10:50:14   rjamloki
 * Added Define.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:22   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:48   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------------ REVISIONS ------------------------------------

 --------------------------- INCLUDE FILES ----------------------------------
 */

#include "portable.h"
#include "menu.h"
#include "rtclock.h"
#include "version_change.h"
/*
 ------------------------------ LOCAL DEFINES ----------------------------------
 */
#define POWER_MIN       10      /*     10 =     1.0 %  */
#define POWER_MAX     1000      /*   1000 =   100.0 %  */
#define ENERGY_MIN      10      /*     10 =     1.0 j  */
#define ENERGY_MAX  990000      /* 990000 =  99,000 j  */
#define TIME_MIN        10      /*     10 =   0.010 s  */
#define TIME_MAX     30000      /*  30000 =  30.000 s  */
#define PRETRG_MAX   10000      /*  10000 =  10.000 s  */
#define EB_TIME_MAX   1000      /*   1000 =   1.000 s  */
#define COL_MIN          4      /*      4 =  0.0004 in */
#define COL_MAX      10000      /*  10000 =  1.0000 in */
#define ABS_MIN       1250      /*   1250 =  0.1250 in */
#define AMP_MIN         10      /*     10 =      10 %  */
#define AMP_MAX        100      /*    100 =     100 %  */
#define TEST_AMP        50      /*     50 =      50 %  */
#define COUNTER_MAX  99999      /*  99999 =   99999    */
#define SHIFT_MIN        0      /* Shift algorithm for f0 test code - min shift */
#define SHIFT_MAX        6      /* Shift algorithm for f0 test code - max shift */
#define FIVE_LBS        50      /* 5 pounds force      */
#define TEN_LBS        100      /* 10 pounds force     */
#define FIFTEEN_LBS    150      /* 15 pounds force     */
#define EB_DEF_TIME     20      /*     20 =   0.020 s  */
#define MAX_CYCLETIME 65000     /* 65000  =  65 s      */
#define BATCHCNTR_MIN 1
#define BATCHCNTR_MAX 100000
#define FLOWCNTRL_MIN 0 //steps
#define FLOWCNTRL_MAX 125 //steps
#define HOLDPRESSURE_MIN 100 //10PSI
#define HOLDPRESSURE_MAX 1000 //100PSI
#define WELDPRESSURE_MIN 100 //10PSI
#define WELDPRESSURE_MAX 1000 //100PSI
#define MPRESSURELIM_MIN 100 //10PSI
#define MPRESSURELIM_MAX 1000 //100PSI
#define PPRESSURELIM_MIN 100 //10PSI
#define PPRESSURELIM_MAX 1000 //100PSI
#define TRIGDIST_MIN 1250//0.125in

#define WELDTRIGGER_MIN TRIGGERBY_FORCE//1-FORCE,2- DISTANCE
#define WELDTRIGGER_MAX TRIGGERBY_DISTANCE//1-FORCE,2- DISTANCE
#define WELDPRESSURE_DEFAULT  200 //20PSI
#define HOLDPRESSURE_DEFAULT  200 //20PSI

#define TRIGGERBY_FORCE 0
#define TRIGGERBY_DISTANCE 1
#define PRESETLEN           12
#define MAX_CAL_PTS         10+1
#define SPRING_RATE_TABLE   64
#define FORCE_MIN           100      /*    100 =    10.0 lb */
#define NMBRPOINTS          20       /* Maximum number points in profile      */
#define WRITEINLEN          12       /* (10 characters, 1 term, 1 to keep word aligned) */

#define CURRENT_SETUP       0

#define PageS11             1  
#define PageS14             2
#define PageSA4             4

#define MAX_PRESETS         16     /* For Version 8.00, the limit is 16 */
#define PASS_SIZE           7      /* Size of password including null */
#define PMCDATAPOINTS       402
#define MAX_SEQUENCE_NOS    30 

#define PRESET_0 0
#define PRESET_RUNNING 		36 // FRAM Preset Max
#define PRESET_COLDSTART 	PRESET_RUNNING - 1
#define PRESET_MAX   		PRESET_COLDSTART - 1
#define PRESET_MIN   		PRESET_MAX - 1
#define MAXSERIALNUMBER_LEN 13

#define CURRENT_PRESET_INDEX     PRESET_0
#define MAX_POSSIBLE_PRESET_BELOW_C	 16 //Max available user presets below control level C
#define MAX_POSSIBLE_PRESET      1000
#define PRESET_COLDSTART_INDEX   (MAX_POSSIBLE_PRESET+1)
#define PRESET_MIN_INDEX         (PRESET_COLDSTART_INDEX+1)
#define PRESET_MAX_INDEX         (PRESET_MIN_INDEX+1)
#define PRESET_RUNNING_INDEX 	 (PRESET_MAX_INDEX+1)
#define SIZE_OF_PRESET           (sizeof(SETUPS_Ver1200))
#define NUM_SPECIAL_PRESET		 4

//Down speed min , max , default in percent. These indicate the percent opening of flow valve.
#define MAX_DOWNSPEED 100
#define MIN_DOWNSPEED 1
#define DOWNSPEED_DEFAULT  20

#define VELOCITYMLR_MIN  30//0.3in/s
#define VELOCITYMLR_MAX  700//7in/s
#define VELOCITYMLR_DEFAULT  30 // .3in/s
#define VELOCITYPLR_MIN  30//0.3in/s
#define VELOCITYPLR_MAX  700//7in/s
#define VELOCITYPLR_DEFAULT  700 // 7in/s

/*DUPS current parameter set contains the values of the parameter set in COP's
 current preset's format*/
typedef struct /* ParamIDs */
{
   SINT32 Frequency;
   SINT32 Power;
   SINT32 Variant;
   UINT16 DipFlag; /* DUPS_DIPFLAG */
   SINT32 SWDipSetting; /*DUPS_SWDIPSETTING  */
   SINT32 SeekAmplitude; /*DUPS_SEEKAMPLITUDE*/
   SINT32 SeekRampTime; /*DUPS_SEEKRAMPTIME milisecons*/
   SINT32 SeekTime; /* DUPS_SEEKTIME  miliseconds*/
   SINT32 SeekFreqLimitHigh; /*DUPS_SEEKFLIMH  hertz*/
   SINT32 SeekFreqLimitLow; /* DUPS_SEEKFLIML hertz*/
   SINT32 SeekPhaseLoop; /* DUPS_SEEKPHLOOPI */
   SINT32 SeekPhaseLoopCF; /* DUPS_SEEKPHLOOPCF */
   SINT32 SeekAmplitudeLoopC1;/* DUPS_SEEKAMPLOOPC1 */
   SINT32 SeekAmplitudeLoopC2;/*DUPS_SEEKAMPLOOPC2 */
   SINT32 WeldAmplitude; /*DUPS_WELDAMPLITUDE */
   SINT32 WeldRampTime; /* DUPS_WELDRAMPTIME */
   SINT32 WeldPhaseLoop; /* DUPS_WELDPHLOOPI */
   SINT32 WeldPhaseLoopCF; /* DUPS_WELDPHLOOPCF */
   SINT32 WeldAmplitudeLoopC1;/*DUPS_WELDAMPLOOPC1 */
   SINT32 WeldAmplitudeLoopC2;/* DUPS_WELDAMPLOOPC2 */
   SINT32 WeldFreqLimitHigh; /* DUPS_WELDFLIMH  hertz*/
   SINT32 WeldFreqLimitLow; /* DUPS_WELDFLIML  hertz*/
   SINT32 WeldPhaseLimit; /* DUPS_WELDPHLIM */
   SINT32 WeldPhaseLimitTime; /* DUPS_WELDPHLIMTIME  milliseconds*/
} DUPS_CURRENTPARAMSET;

/*----------------------------------------------------------------------------------------------*/
/*  This typedef defines the structure used to hold the running preset and the current preset.  */
/*  Whenever a change is made to this structure, a corresponding change needs to be made to the */
/*  CompressedSetups structure and to the code in functions Convert600to800() and Convert702to  */
/*  800().  The functions CompressPreset() and UncompressPreset() need to be updated as well.   */
/*----------------------------------------------------------------------------------------------*/
typedef struct Ver1200Setups
{ /***  THIS COPY IS TO RETAIN THE DEFINITION FOR VER 8.00    ***/
   SINT32 AbAmp;
   SINT32 AbDelay;
   UINT16 AbFlag;
   SINT32 AbTime;
   SINT32 ABSCutoffDist;
   UINT16 ABSCutoffFlag;
   SINT32 AbsDist;
   SINT32 AbsMLR;
   SINT32 AbsMLS;
   SINT32 AbsPLR;
   SINT32 AbsPLS;
   SINT32 ActClrDistance;
   UINT16 ActClrFlag;
   SINT32 Amp1;
   SINT32 AmpTrigAbsValue;
   SINT32 AmpTrigColValue;
   UINT16 AmpTrigExtFlag;
   SINT32 AmpTrigTimeValue;
   SINT32 AmpTrigEnerValue;
   SINT32 AmpTrigPowerValue;
   UINT16 Amp2Flag;
   SINT32 Amp2;
   SINT32 AmpScrubTime;
   UINT16 AutoScaleFlag;
   UINT16 AutoTrigFlag;
   UINT16 BatchFunction;
   UINT16 BatchCountWithAlarm;
   UINT16 BatchCountReset;
   SINT32 BatchCount;
   SINT32 CurrBatchCount;
   SINT8 ActAssemblyNum[12];
   SINT8 PSAssemblyNum[12];
   SINT8 StackAssemblyNum[12];
   SINT32 Downspeed;
   UINT16 ColCutoffFlag;
   SINT32 ColCutoffDist;
   SINT32 ColDist;
   SINT32 ColMLR;
   SINT32 ColMLS;
   SINT32 ColPLR;
   SINT32 ColPLS;
   UINT16 ControlLimitsFlag;
   UINT16 CycleAbortFlag;
   RTCTime PS_DateTime;
   UINT16 DigitalFilterFlag; /* Global name change */
   SINT32 EBTime; /* V9 new variable - VARIABLE */
   UINT16 EnergyBraking; /* V9 new variable - CHOICE */
   UINT16 EnergyCompFlag;
   //Added for vel limit old /*EnergyMaxVQS*/
   UINT16 RVelLimitMask;  
   UINT16 RVelLimitFlag;
   UINT16 HoldPressureFlag;
   UINT16 SetupLimits;
   SINT32 EnergyML;
   SINT32 EnergyMLR;
   SINT32 EnergyMLS;
   SINT32 EnergyPL;
   SINT32 EnergyPLR;
   SINT32 EnergyPLS;
   UINT16 ExtTrgDelay; /* External trigger delay - added in V9  CHOICE */
   SINT32 FreqMLR;
   SINT32 FreqMLS;
   SINT32 FreqPLR;
   SINT32 FreqPLS;
   SINT32 FreqOffset;
   UINT16 FreqOffsetFlag;
   SINT32 SBLMinFreqLim; /* Minimum frequency limit. Value is calculated every time when SBL is enabled or horn scan is run. */
   SINT32 SBLMaxFreqLim; /* Maximum frequency limit, same as above applies. */
   SINT32 SBLMinFreq; /* Initially copied from SBLMinFreqLim. Operator can change within limits. */
   SINT32 SBLMaxFreq; /* Same as SBLMinFreq */
   UINT16 SBLFreqFlags; /* SBL + and - enable flags. */
   UINT16 GeneralAlarmLFlag; /* Global Name Change */
   UINT16 GndDetectFlag;
   SINT32 HoldForce;
   SINT32 WeldPressure;
   SINT32 HoldPressure;
   UINT16 HoldTimeFlag;
   SINT32 HoldTime;
   SINT8 HornID[12];
   SINT32 MaxTimeout;
   UINT16 MissingPartFlag;
   UINT16 MissingMinFlag;
   UINT16 MissingMaxFlag;
   SINT32 MissingPartMin;
   SINT32 MissingPartMax;
   SINT32 PeakPwr;
   SINT32 PeakPwrCutoff;
   UINT16 PeakPwrCutoffFlag;
   SINT32 TrigForcePLT;
   SINT32 TrigForceMLT;
   SINT8 PresetID[PRESETLEN];
   SINT32 PowerMLR;
   SINT32 PowerMLS;
   SINT32 PowerPLR;
   SINT32 PowerPLS;
   SINT32 MPressureLimit;
   SINT32 PPressureLimit;
   UINT16 PressureLimitFlag;
   UINT16 PressureLimits;
   UINT16 PresetUpdateComplete;
   UINT16 PreTrigFlag;
   SINT32 PreTrigAmp;
   SINT32 PreTrigDelay;
   UINT16 PreTrigDelayFlag;
   SINT32 PreTriggerDistance;
   UINT16 PreTriggerDistanceFlag;
   UINT16 RejectLimits;
   UINT16 RejectLimitsFlag;
   UINT16 RejResetRequiredFlag; /* Global Name Change */
   SINT32 RTDist;
   UINT16 RTFlag;
   SINT32 ScrubTime;
   UINT16 ScrubTimeFlag;
   UINT16 SeekFunFlag; /* Global Name Change */
   UINT16 SetPressure;
   UINT16 SuspectLimits;
   UINT16 SuspectLimitsFlag;
   UINT16 SusResetRequired;
   SINT32 TestAmp;
   SINT32 TimeMLR;
   SINT32 TimeMLS;
   SINT32 TimePLR;
   SINT32 TimePLS;
   SINT32 TriggerDelay; /* used for timed trigger delay - not implemented as yet */
   SINT32 TrsDistMLR;
   SINT32 TrsDistMLS;
   SINT32 TrsDistPLR;
   SINT32 TrsDistPLS;
   BOOLEAN WeldTrigger;
   SINT32 TriggerDistance;
   SINT32 TriggerForce;
   UINT16 TriggerDelayFlag;
   SINT32 WeldPressurePLT;
   SINT32 WeldPressureMLT;
   SINT32 HoldPressurePLT;
   SINT32 HoldPressureMLT;
   SINT32 HoldTimePLT;
   SINT32 HoldTimeMLT;
   UINT16 Validated;
   UINT16 Locked;
   SINT32 VelocityMLR;
   SINT32 VelocityPLR;
   UINT16 Verified;
   SINT32 AmpAPLT;
   SINT32 AmpAMLT;
   SINT32 WeldCount;
   SINT32 WeldEnergy;
   UINT16 WeldMode;
   SINT32 WeldTime;
   SINT8 WriteIn1[WRITEINLEN];
   SINT8 WriteIn2[WRITEINLEN];
   SINT32 WeldForceMLR; /* Global Name Change Max->Weld */
   SINT32 WeldForceMLS; /* Global Name Change Max->Weld */
   SINT32 WeldForcePLR; /* Global Name Change Max->Weld */
   SINT32 WeldForcePLS; /* Global Name Change Max->Weld */
   SINT32 DownspeedPLT;
   SINT32 DownspeedMLT;
   BOOLEAN WeldStatusFlag;
   SINT32 XScaleTime;
   SINT32 WeldTimePLT;
   SINT32 WeldTimeMLT;
   SINT32 PresetConfigNum;
   UINT32 HwCnfg;
   SINT32 PMCHighLimit;
   SINT32 PMCLowLimit;
   SINT32 PMCTimeout;
   UINT16 PMCCycleCount;
   UINT16 PMCEnabled;
   UINT16 PMCPlusBandFlag;
   UINT16 PMCMinusBandFlag;
   UINT16 VQSLimit;
   DUPS_CURRENTPARAMSET DUPS_HostParamSet;
   UINT8 PMCData[PMCDATAPOINTS];
   UINT8 TunedFlowValue;
	BOOLEAN TunedPreset;
	UINT16 Rev;
	SINT32 WeldEnergyPLT;
	SINT32 WeldEnergyMLT;
	SINT32 PeakPowerPLT;
	SINT32 PeakPowerMLT;
	SINT32 CollapseDistPLT;
	SINT32 CollapseDistMLT;
	SINT32 AbsDistPLT;
	SINT32 AbsDistMLT;
	SINT32 ScrubTimePLT;
	SINT32 ScrubTimeMLT;
	SINT32 ScrubAmpPLT;
	SINT32 ScrubAmpMLT;
	SINT32 TrigDistancePLT;
	SINT32 TrigDistanceMLT;
	UINT16 SetupLimits2;
	SINT32 Spare2;
	SINT32 PressureTrigColValue;
	UINT16 PressureTrigExtFlag;
	SINT32 PressureTrigTimeValue;
	SINT32 PressureTrigEnerValue;
	SINT32 PressureTrigPowerValue;
	UINT16 Pressure2Flag;
	SINT32 Pressure2;
	UINT8 spareArr[31];
}__attribute__((__packed__)) SETUPS_Ver1200;

/*****************************************************************************/
/*                                                                           */
/*  The following chunk of stuff allows the compiler to check the size of    */
/*  the compressed preset to ensure it remains at 454 bytes.  Don't ask me   */
/*  how it works.  I stole it from the Diab compiler manual and modified it  */
/*  until it worked.  It's static so it's not multiply defined.  I know it   */
/*  will be created once for every 'C' file, but according to the manual it  */
/*  won't generate any code if all is okay.                                  */
/*                                                                           */
/*  The argument for the __ERROR__ call (2) is supposed to create an error   */
/*  and stop the compile.  It doesn't and I don't know why.  It will only    */
/*  create a warning, so pay attention.                                      */
/*                                                                           */
/*****************************************************************************/

extern void __ERROR__(char *, ...);

#define CHECK_PRESET(test) if (!(test)) __ERROR__("COMPRESSED PRESET NOT 454 BYTES..", 2)

//static void CheckPresetSize(void)
//{
//   CHECK_PRESET(sizeof(PRESET_COMPRESSED) == SIZE_OF_COMPRESSED_PRESET-4);
//}

/************************  End of chunk of stuff  ****************************/

typedef struct __attribute__((__packed__)) CONFIGSETUP_1208
{
   UINT16 ActivePreset; /*                                             */
   SINT32 ActLifetime; /*                                             */
   SINT8 ActSerialNumber[13];//configurable only from BUC menu
   UINT16 Actuator; /*                                             */
   UINT16 AdvanceCounters; /* TRUE:all cycles   FALSE:good cycles only    */
   BOOLEAN AmpControl; /* TRUE:internal control FALSE:external control*/
   UINT16 BeeperAlarm; /* TRUE:beep on any process alarms             */
   UINT16 BeeperError; /* TRUE:beep on data entry errors              */
   UINT16 BeeperRelease; /* TRUE:beep ok to release start, H/H only     */
   UINT16 BeeperTrigger; /* TRUE:beep when trigger occurs               */
   UINT16 BaudRate; /* this is active baudrate                     */
   UINT16 FRAMInitialized; /* When FRAM is initialized: set to 0x5555      */
   UINT16 CustomAct; /* TRUE:custom is turned on                    */
   UINT16 ControlLevel; /* LEVEL_t, LEVEL_e, LEVEL_a, LEVEL_ea, LEVEL_d, LEVEL_f & LEVEL_TEST    */
   UINT16 CycleStart; /* BIT1:2Start  BIT2:1Start  BIT3:TrgSw  BIT4:ExtSig */
   UINT16 CylinDiameter;
   SINT32 DigTune; /* Dig Tune scaled value * 20, -999 to 1000         */
   UINT16 DigTuneFlag; /*                                             */
   BOOLEAN ExtraCooling; /* TRUE:Extra cooling on                       */
   BOOLEAN ExtPresets; /* TRUE:External Presets is On                 */
   BOOLEAN FreqControl; /* TRUE:internal control FALSE:external control*/
   SINT32 GenAlarmCount; /*                                             */
   SINT32 GainFactor;
   BOOLEAN GndDetLogicCustom; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 HmenuIndex; /* Current selection on current HSUBMENU       */
   SINT32 HornDownSpd; /*    */
   SINT16 HornWeightOffset;
   BOOLEAN USEncoder; /* TRUE = US, FALSE = METRIC                   */
   SINT32 IdleSpeed;
   UINT16 Language; /*                                             */
   SINT32 MinTrigForce;
   SINT32 Overload; /*                                             */
   /* Next 2 variables (PasswordFlag 7 PasswordID) must stay in sequential order (because of sysmangr)*/
   UINT16 PassWordFlag; /* TRUE:passwords are required                 */
   SINT8 PassWordID[PASS_SIZE]; /* Alpha/Numeric string of approved password   */
   /* Next 2 variables (PSFreq & PSWatt)  must stay in sequential order (because of sysmangr) */
   UINT16 PSFreq;
   SINT32 PSWatt;
   SINT32 PSLifetime; /*                                             */
   SINT8 PSSerialNumber[MAXSERIALNUMBER_LEN];//configurable only from BUC menu
   BOOLEAN PSType; /* TRUE: DUPS, FALSE: Analog                   */
   SINT16 PwrOutTable[MAX_CAL_PTS];
   UINT16 Spare2; /*                                             */
   UINT16 SecurityLevel; /* OPERATOR, SETUP, MAINTAINENCE, BRANSON      */
   UINT16 Spare3;
   UINT16 SerialPort; /* TRUE:serial port on and setup               */
   UINT16 SpringRateTable[SPRING_RATE_TABLE];
   BOOLEAN StartScreen;
   UINT16 StrokeLen; /*                                             */
   UINT16 TestMultiplier; /* TRUE:indicates power bargraph max = 100%    */
   UINT16 TimeMultiplier; /* TRUE:indicates power bargraph max = 100%    */
   BOOLEAN Units; /* Currently selected units SI:TRUE USCS:FALSE */
   BOOLEAN ULSLogicCustom; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 J3_32In; /* Input J3_32                                 */
   UINT16 J3_33In; /* Input J3_33                                 */
   UINT16 J3_19In; /* Input J3_19                                 */
   UINT16 J3_17In; /* Input J3_17                                 */
   UINT16 UserInLogic; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 J3_36Out; /* Output J3_36                                */
   UINT16 J3_8Out; /* Output J3_8                                 */
   SINT32 VelocityTable[2]; /*                                             */
   SINT32 WeldHistoryPtr; /* Last Fram Pointer Address                */
   BOOLEAN HandHeld; /* TRUE: Handheld is On                        */
   UINT16 WeldParamOption[5]; /* Weld Result Parameter options */
   UINT16 DUPS_WorkingPreset; /* DUPS Working Preset Number */
   UINT16 J3_31In; /* Input J3_31                                 */
   UINT16 J3_1In; /* Input J3_01                                 */
   UINT16 J3_22Out; /* Output J3_22                                */
   BOOLEAN *J3_32Ptr; /* Pointer to selected item on J3_32           */
   BOOLEAN *J3_33Ptr; /* Pointer to selected item on J3_33           */
   BOOLEAN *J3_19Ptr; /* Pointer to selected item on J3_19           */
   BOOLEAN *J3_17Ptr; /* Pointer to selected item on J3_17           */
   BOOLEAN *J3_31Ptr; /* Pointer to selected item on J3_31           */
   BOOLEAN *J3_1Ptr; /* Pointer to selected item on J3_2            */
   UINT32 Dummy1; /* Just a place holder can be used in future   */
   UINT16 WelderAddrFlag; /* Welder ID On/Off                            */
   SINT32 WelderAddrValue; /* Welder ID value                             */
   UINT8 Sclk7890Act; /* Clock speed for actuator a/d                */
   UINT8 ClockPhase; /* Phase needs to be inverter at high speed    */
   UINT8 SystemControllerFlag; /* J3_8 and J3_36 switching based on this flag  */
   SINT32 PartClampDelay; /* Sv interlock Delay                          */
   BOOLEAN AutoRefresh; /* Auto Refresh of graph on VGA*/
   BOOLEAN Metric3Flag; /* TRUE if metric distance must have 3 decimals*/
   UINT16 DistanceULS; /* True to reset encoder on ULS, false on start switches */
   UINT16 SBLEnable; /* Global SBL enable/disable flag.            */
   BOOLEAN USBGlobalFlag; /* Global USB On/Off flag                     */
   UINT16 USBWDSampleFlag; /* Weld Summary SendOnSample Flag.            */
   UINT16 USBPGSampleFlag; /* Power Graph SendOnSample Flag.             */
   UINT16 USBAGSampleFlag; /* Amplitude Graph SendOnSample Flag.         */
   UINT16 USBFreqGSampleFlag; /* Frequency Graph SendOnSample Flag.         */
   UINT16 USBCDGSampleFlag; /* CollapseDistance Graph SendOnSample Flag.  */
   UINT16 USBVGSampleFlag; /* Velocity Graph SendOnSample Flag.          */
   UINT16 USBFGSampleFlag; /* Force Graph SendOnSample Flag.             */
   BOOLEAN USBWDAlarmFlag; /* Weld Summary SendOnAlarm flag.             */
   BOOLEAN USBPGAlarmFlag; /* Power Graph SendOnAlarm flag.              */
   BOOLEAN USBAGAlarmFlag; /* Amplitude Graph SendOnAlarm flag.          */
   BOOLEAN USBFreqGAlarmFlag; /* Frequency Graph SendOnAlarm flag.          */
   BOOLEAN USBCDGAlarmFlag; /* Collapse Distance Graph SendOnAlarm flag.  */
   BOOLEAN USBVGAlarmFlag; /* Velocity Graph SendOnAlarm flag.           */
   BOOLEAN USBFGAlarmFlag; /* Force Graph SendOnAlarm flag.              */
   SINT32 USBWDSampleValue; /* Weld Summary SendOnSample value.           */
   SINT32 USBPGSampleValue; /* Power Graph SendOnSample value.            */
   SINT32 USBAGSampleValue; /* Amplitude Graph SendOnSample value.        */
   SINT32 USBFreqGSampleValue; /* Frequency Graph SendOnSample value.        */
   SINT32 USBCDGSampleValue; /* Collapse Distance Graph SendOnSample value.*/
   SINT32 USBVGSampleValue; /* Velocity Graph SendOnSample value.         */
   SINT32 USBFGSampleValue; /* Force Graph SendOnSample value.            */
   BOOLEAN SequenceEnable; /* Sequencing preset enable/disable           */
   UINT8 SequenceCount; /* Total sequencing items                     */
   UINT16 SequenceList[MAX_SEQUENCE_NOS]; /* Sequence List                      */
   UINT16 SequenceNos; /* Current Sequence number                    */
   UINT16 VGAHWPresent; /* True if VGA hardware detected once         */
   BOOLEAN PLCControlFlag; /* TRUE:PLC Control feature is on             */
   BOOLEAN PLCControlMenuFlag; /* TRUE:PLC Control menu option is displayed  */
   //New
   BOOLEAN BasicExpert;
   BOOLEAN HornClamp;
   BOOLEAN UDIScan;
   BOOLEAN Automation;
   BOOLEAN MemoryFull;
   UINT16 UserIDTable;
   BOOLEAN AuthorityCheck;
   SINT8 BarcodeStart[2];
   //H/W Part numbers configurable from System config
   SINT8 StackAssemblyNum[12];
   SINT8 ActAssemblyNum[12];
   SINT8 PSAssemblyNum[12];
   ////////////////////////
   UINT16 HWVerify;
   UINT16 WeldStorageFormat;
   UINT16 BeeperEstop;
   UINT16 Reserved;
   UINT32 IdleLogoutTime;
   UINT32 WeldHistSetup;
   BOOLEAN DownspeedTune;
   //
};

typedef struct __attribute__((__packed__)) CONFIGSETUP_1209
{
   UINT16 ActivePreset; /*                                             */
   SINT32 ActLifetime; /*                                             */
   SINT8 ActSerialNumber[13];//configurable only from BUC menu
   UINT16 Actuator; /*                                             */
   UINT16 AdvanceCounters; /* TRUE:all cycles   FALSE:good cycles only    */
   BOOLEAN AmpControl; /* TRUE:internal control FALSE:external control*/
   UINT16 BeeperAlarm; /* TRUE:beep on any process alarms             */
   UINT16 BeeperError; /* TRUE:beep on data entry errors              */
   UINT16 BeeperRelease; /* TRUE:beep ok to release start, H/H only     */
   UINT16 BeeperTrigger; /* TRUE:beep when trigger occurs               */
   UINT16 BaudRate; /* this is active baudrate                     */
   UINT16 FRAMInitialized; /* When FRAM is initialized: set to 0x5555      */
   UINT16 CustomAct; /* TRUE:custom is turned on                    */
   UINT16 ControlLevel; /* LEVEL_t, LEVEL_e, LEVEL_a, LEVEL_ea, LEVEL_d, LEVEL_f & LEVEL_TEST    */
   UINT16 CycleStart; /* BIT1:2Start  BIT2:1Start  BIT3:TrgSw  BIT4:ExtSig */
   UINT16 CylinDiameter;
   SINT32 DigTune; /* Dig Tune scaled value * 20, -999 to 1000         */
   UINT16 DigTuneFlag; /*                                             */
   BOOLEAN ExtraCooling; /* TRUE:Extra cooling on                       */
   BOOLEAN ExtPresets; /* TRUE:External Presets is On                 */
   BOOLEAN FreqControl; /* TRUE:internal control FALSE:external control*/
   SINT32 GenAlarmCount; /*                                             */
   SINT32 GainFactor;
   BOOLEAN GndDetLogicCustom; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 HmenuIndex; /* Current selection on current HSUBMENU       */
   SINT32 HornDownSpd; /*    */
   SINT16 HornWeightOffset;
   BOOLEAN USEncoder; /* TRUE = US, FALSE = METRIC                   */
   SINT32 IdleSpeed;
   UINT16 Language; /*                                             */
   SINT32 MinTrigForce;
   SINT32 Overload; /*                                             */
   /* Next 2 variables (PasswordFlag 7 PasswordID) must stay in sequential order (because of sysmangr)*/
   UINT16 PassWordFlag; /* TRUE:passwords are required                 */
   SINT8 PassWordID[PASS_SIZE]; /* Alpha/Numeric string of approved password   */
   /* Next 2 variables (PSFreq & PSWatt)  must stay in sequential order (because of sysmangr) */
   UINT16 PSFreq;
   SINT32 PSWatt;
   SINT32 PSLifetime; /*                                             */
   SINT8 PSSerialNumber[MAXSERIALNUMBER_LEN];//configurable only from BUC menu
   BOOLEAN PSType; /* TRUE: DUPS, FALSE: Analog                   */
   SINT16 PwrOutTable[MAX_CAL_PTS];
   UINT16 Spare2; /*                                             */
   UINT16 SecurityLevel; /* OPERATOR, SETUP, MAINTAINENCE, BRANSON      */
   UINT16 Spare3;
   UINT16 SerialPort; /* TRUE:serial port on and setup               */
   UINT16 SpringRateTable[SPRING_RATE_TABLE];
   BOOLEAN StartScreen;
   UINT16 StrokeLen; /*                                             */
   UINT16 TestMultiplier; /* TRUE:indicates power bargraph max = 100%    */
   UINT16 TimeMultiplier; /* TRUE:indicates power bargraph max = 100%    */
   BOOLEAN Units; /* Currently selected units SI:TRUE USCS:FALSE */
   BOOLEAN ULSLogicCustom; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 J3_32In; /* Input J3_32                                 */
   UINT16 J3_33In; /* Input J3_33                                 */
   UINT16 J3_19In; /* Input J3_19                                 */
   UINT16 J3_17In; /* Input J3_17                                 */
   UINT16 UserInLogic; /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16 J3_36Out; /* Output J3_36                                */
   UINT16 J3_8Out; /* Output J3_8                                 */
   SINT32 VelocityTable[2]; /*                                             */
   SINT32 WeldHistoryPtr; /* Last Fram Pointer Address                */
   BOOLEAN HandHeld; /* TRUE: Handheld is On                        */
   UINT16 WeldParamOption[5]; /* Weld Result Parameter options */
   UINT16 DUPS_WorkingPreset; /* DUPS Working Preset Number */
   UINT16 J3_31In; /* Input J3_31                                 */
   UINT16 J3_1In; /* Input J3_01                                 */
   UINT16 J3_22Out; /* Output J3_22                                */
   BOOLEAN *J3_32Ptr; /* Pointer to selected item on J3_32           */
   BOOLEAN *J3_33Ptr; /* Pointer to selected item on J3_33           */
   BOOLEAN *J3_19Ptr; /* Pointer to selected item on J3_19           */
   BOOLEAN *J3_17Ptr; /* Pointer to selected item on J3_17           */
   BOOLEAN *J3_31Ptr; /* Pointer to selected item on J3_31           */
   BOOLEAN *J3_1Ptr; /* Pointer to selected item on J3_2            */
   UINT32 PressureStepDownFlag; /* Just a place holder can be used in future   */
   UINT16 WelderAddrFlag; /* Welder ID On/Off                            */
   SINT32 WelderAddrValue; /* Welder ID value                             */
   UINT8 Sclk7890Act; /* Clock speed for actuator a/d                */
   UINT8 ClockPhase; /* Phase needs to be inverter at high speed    */
   UINT8 SystemControllerFlag; /* J3_8 and J3_36 switching based on this flag  */
   SINT32 PartClampDelay; /* Sv interlock Delay                          */
   BOOLEAN AutoRefresh; /* Auto Refresh of graph on VGA*/
   BOOLEAN Metric3Flag; /* TRUE if metric distance must have 3 decimals*/
   UINT16 DistanceULS; /* True to reset encoder on ULS, false on start switches */
   UINT16 SBLEnable; /* Global SBL enable/disable flag.            */
   BOOLEAN USBGlobalFlag; /* Global USB On/Off flag                     */
   UINT16 USBWDSampleFlag; /* Weld Summary SendOnSample Flag.            */
   UINT16 USBPGSampleFlag; /* Power Graph SendOnSample Flag.             */
   UINT16 USBAGSampleFlag; /* Amplitude Graph SendOnSample Flag.         */
   UINT16 USBFreqGSampleFlag; /* Frequency Graph SendOnSample Flag.         */
   UINT16 USBCDGSampleFlag; /* CollapseDistance Graph SendOnSample Flag.  */
   UINT16 USBVGSampleFlag; /* Velocity Graph SendOnSample Flag.          */
   UINT16 USBFGSampleFlag; /* Force Graph SendOnSample Flag.             */
   BOOLEAN USBWDAlarmFlag; /* Weld Summary SendOnAlarm flag.             */
   BOOLEAN USBPGAlarmFlag; /* Power Graph SendOnAlarm flag.              */
   BOOLEAN USBAGAlarmFlag; /* Amplitude Graph SendOnAlarm flag.          */
   BOOLEAN USBFreqGAlarmFlag; /* Frequency Graph SendOnAlarm flag.          */
   BOOLEAN USBCDGAlarmFlag; /* Collapse Distance Graph SendOnAlarm flag.  */
   BOOLEAN USBVGAlarmFlag; /* Velocity Graph SendOnAlarm flag.           */
   BOOLEAN USBFGAlarmFlag; /* Force Graph SendOnAlarm flag.              */
   SINT32 USBWDSampleValue; /* Weld Summary SendOnSample value.           */
   SINT32 USBPGSampleValue; /* Power Graph SendOnSample value.            */
   SINT32 USBAGSampleValue; /* Amplitude Graph SendOnSample value.        */
   SINT32 USBFreqGSampleValue; /* Frequency Graph SendOnSample value.        */
   SINT32 USBCDGSampleValue; /* Collapse Distance Graph SendOnSample value.*/
   SINT32 USBVGSampleValue; /* Velocity Graph SendOnSample value.         */
   SINT32 USBFGSampleValue; /* Force Graph SendOnSample value.            */
   BOOLEAN SequenceEnable; /* Sequencing preset enable/disable           */
   UINT8 SequenceCount; /* Total sequencing items                     */
   UINT16 SequenceList[MAX_SEQUENCE_NOS]; /* Sequence List                      */
   UINT16 SequenceNos; /* Current Sequence number                    */
   UINT16 VGAHWPresent; /* True if VGA hardware detected once         */
   BOOLEAN PLCControlFlag; /* TRUE:PLC Control feature is on             */
   BOOLEAN PLCControlMenuFlag; /* TRUE:PLC Control menu option is displayed  */
   //New
   BOOLEAN BasicExpert;
   BOOLEAN HornClamp;
   BOOLEAN UDIScan;
   BOOLEAN Automation;
   BOOLEAN MemoryFull;
   UINT16 UserIDTable;
   BOOLEAN AuthorityCheck;
   SINT8 BarcodeStart[2];
   //H/W Part numbers configurable from System config
   SINT8 StackAssemblyNum[12];
   SINT8 ActAssemblyNum[12];
   SINT8 PSAssemblyNum[12];
   ////////////////////////
   UINT16 HWVerify;
   UINT16 WeldStorageFormat;
   UINT16 BeeperEstop;
   UINT16 Reserved;
   UINT32 IdleLogoutTime;
   UINT32 WeldHistSetup;
   BOOLEAN DownspeedTune;
   //
   //New Rellocate Memory FRAM
   BOOLEAN LowerFlowValveFlag; /* Just a place holder can be used in future   */
   BOOLEAN WebServiceAutomation;
   BOOLEAN WebServiceAutorityCheck;
};

#ifdef FRAM_VER1208
	typedef struct CONFIGSETUP_1208 CONFIGSETUP;
#endif

#ifdef FRAM_VER1209
	typedef struct CONFIGSETUP_1209 CONFIGSETUP;
#endif

#ifdef FRAM_VER1210
	typedef struct CONFIGSETUP_1210 CONFIGSETUP;
#endif

typedef struct
{
   SINT32 EnergyBrakingAmp;
   SINT32 EnergyBrakingTime;
   UINT16 ExtSwLogicBUC;
   SINT32 ForcePC;
   UINT16 GndDetLogicBUC;
   UINT16 ULSLogicBUC;
   SINT32 VelocityPC;
   UINT16 VelocityReporting; /* Toggle via main menu secret codes */
   SINT32 Reserved;
   UINT16 RecalCode300; /* Enable/disable recal error code 300 */
   UINT16 MicroHomeForce; /* FALSE = 3  TRUE = 4   Leaving home force */
}__attribute__((__packed__)) BUCMENU_1200;

typedef struct
{
   SINT16 WasADepot; /* Was unit ever configured as a depot */
   SINT16 IsADepot;
}__attribute__((__packed__)) DEPOT_FLAGS; /* Is unit configured as a depot now   */


//Preset information structure. It has some more frequently changing things in preset.
//To minimize the Nand Flash hits its been kept in FRAM
typedef struct
{
	SINT32 CurrBatchCount;
	SINT32 WeldCount;
	UINT16 Verified;
	UINT16 Validated;
	UINT16 Locked;

}__attribute__((__packed__)) PRESETINFO;

typedef enum
{
   UNIQUEPRESET = 1, ALARMPRESET, COLDSTARTPRESET
} TESTING_PRESET_TYPE;

enum HW_VERIFY_SETUP
{
	PS_HW_VERIFY = BIT0,
	ACT_HW_VERIFY = BIT1,
	STACK_HW_VERIFY = BIT2,
};

#define FREQ15_OFF     300      /* 15 khz offset (80% of max swing) */
#define FREQ20_OFF     400      /* 20 khz offset (80% of max swing) */
#define FREQ30_OFF     600      /* 30 khz offset (80% of max swing) */
#define FREQ40_OFF     800      /* 40 khz offset (80% of max swing) */
#define FREQ60_OFF    1200      /* 60 khz offset (80% of max swing) */

#define EXPERT 0
#define BASIC 1
#define STOP 0
#define CONTINUE 1
#define SERVER 0
#define WELDER 1
#define PDF 0

extern SETUPS_Ver1200 RunningPreset;
extern SETUPS_Ver1200 CurrentPreset;
extern SETUPS_Ver1200 MinLimit;
extern SETUPS_Ver1200 MaxLimit;
extern CONFIGSETUP CurrentSetup;
extern UINT16 ColdStartInProcess;
extern struct SummaryStruct SummaryInfo;
extern SINT32 MaxSampleValue, MinSampleValue;
extern UINT16 FlagTriggerByDist, FlagTriggerByForce;
extern UINT16 AmpStepEnable;
extern UINT16 PressureStepEnable;
extern Ver1200Setups LocalPresetCopyOfFlash;
extern SETUPS_Ver1200 CurrentViewPreset;
extern PRESETINFO FRAMPresetInfo[1001 + NUM_SPECIAL_PRESET];
extern UINT8 UpdateRunningPreset;
/*-------------------------- FUNCTION PROTOTYPES ---------------------------*/
/*                                                                          */
/*  These prototypes must be after SETUPS so UpdatePreset will complile.    */
/*                                                             BEK 07-10-97 */
/*                                                                          */

void WritePreset(UINT16 PresetNumber, BOOLEAN ChangePrestUpdate = TRUE);
void ReadPreset(UINT16 PresetNumber, UINT16 AlarmSuppressFlag);
void SetMaxMinValues(void);
void DoColdStart(void);
void SetDefaultValues(void);
void SavePreset(UINT16 PresetNumber,SETUPS_Ver1200 *SourcePtr= (SETUPS_Ver1200 *)NULL);
SETUPS_Ver1200 * Readpreset(UINT16 PresetNumber,SETUPS_Ver1200 *DestPtr = (SETUPS_Ver1200 *)NULL);
SETUPS_Ver1200 * CalculatePresetAddress(UINT16 PresetNumber);
void SetUserIOToFactoryDefault(void);
void SetActuatorSwitchesToFactoryDefault(void);
void SetUSBToFactoryDefault(void);
void SetupTriggerFlags(void);
void CopyInfoFromPreset(SETUPS_Ver1200 * SrcPtr, UINT16 PresetNum);
void CopyInfoToPreset(SETUPS_Ver1200 *DestPtr, UINT16 PresetNum);
void SetupPressureFixedOrStepFlag(void);
void SetupPretriggerFlags(void);
void SetupAmplitudeStepFlag(void);
void SetupPressureStepFlag(void);
#endif

