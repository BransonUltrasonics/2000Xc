/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/limits.cpp_v   1.22   Oct 10 2017 10:34:16   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/limits.cpp_v  $
 * 
 *    Rev 1.22   Oct 10 2017 10:34:16   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.21   16 Apr 2015 07:23:10   rjamloki
 * Fix for technician weld setup limits change not allowed in locked preset issue
 * 
 *    Rev 1.19   09 Apr 2015 05:20:30   RJamloki
 * Checking PMC limits from CheckProcessLimits
 * 
 *    Rev 1.18   08 Apr 2015 13:43:36   AnPawar
 * Pressure Stepping implementation in CheckProcessLimits() function.
 * 
 *    Rev 1.17   27 Mar 2015 11:07:50   amaurya
 * Coverity fix 12565.
 * 
 *    Rev 1.16   16 Mar 2015 05:56:36   rjamloki
 * Added is INPUT_CONFIRM_REJECT condition in IsRejectLLimitEnabled function.
 * 
 *    Rev 1.15   13 Mar 2015 06:09:56   amaurya
 * Changed to fix one setup limits issue, on changing any one limit other limit was getting changed automatically to current value even if the other limit was already on.Comments added for PreSetupLimitMinMax() & SetSetupLimits()
 * 
 *    Rev 1.13   14 Nov 2014 10:24:30   AnPawar
 * bit mask changed for +/- r down speed tuning alarms
 * 
 *    Rev 1.12   10 Nov 2014 04:51:32   AnPawar
 * changes for downspeed reject limits.
 * 
 *    Rev 1.11   26 Sep 2014 03:14:26   rjamloki
 * Removed psos references
 * 
 *    Rev 1.10   11 Sep 2014 10:58:56   rjamloki
 * Fixed limit mask for control level c
 * 
 *    Rev 1.9   18 Aug 2014 01:36:04   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.8   28 Jul 2014 12:46:24   rjamloki
 * Added support for horn clamp on alarm feature
 * 
 *    Rev 1.7   11 Jun 2014 11:44:52   rjamloki
 * removed commented code
 * 
 *    Rev 1.6   21 May 2014 10:52:10   rjamloki
 * Applied all limits in all weld modes
 * 
 *    Rev 1.5   21 May 2014 03:07:54   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:28   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:40   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*
 --------------------------- MODULE DESCRIPTION ---------------------------

   Module name: PROCESS_LIMITS  

   Filename:    limits.c     

   Function Name: 
  
   Written by:   Barry E. Kymer
         Date:         04/18/96
         Language:     "C"

 ----------------------------- DESCRIPTION -------------------------------*/


/* ------------------------------ INCLUDE FILES ----------------------------*/

#include "qdef.h"
#include "preset.h"
#include "param.h"
#include "wldstate.h"
#include "state.h"
#include "limits.h"
#include "alarms.h"
#include "ready.h"
#include "menu.h"
#include "weldhold.h"
#include "inports.h"


/*------------------------------ WELD OBJECT DATA --------------------------*/


extern WELD_DATA   WeldingResults;
extern BOOLEAN SBLMinLimitReached;
extern BOOLEAN SBLMaxLimitReached;
extern BOOLEAN PressureStepReachedFlag;
UINT16 CheckForDups(void);
extern void CheckPMCWithPwrGraph(void);

SINT32 MinSetupLim;
SINT32 MaxSetupLim;

void CheckProcessLimits(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check ALL process limits. When all are checked,      */
/*  those which are not valid for the current weld mode and those not       */
/*  enabled,  will then be masked out of the Alarm value                    */
/*  (SuspectLimitAlarm and RejectLimitAlarm).                               */
/*                                                                          */
/****************************************************************************/
{
UINT32   SuspectLimitAlarm = 0;              /* Clear out last cycle data   */
UINT32   RejectLimitAlarm = 0 ;              /* Clear out last cycle data   */
UINT16   LocalModelMask;

   switch (CurrentSetup.ControlLevel) {
      case LEVEL_t:
         LocalModelMask = CTRL_LEVEL_tMASK;
         break;

      case LEVEL_e:
         LocalModelMask = CTRL_LEVEL_eMASK;
         break;

      case LEVEL_ea:
      case LEVEL_a:
         LocalModelMask = CTRL_LEVEL_eaMASK;
         break;

      case LEVEL_d:
      case LEVEL_c:
         LocalModelMask = CTRL_LEVEL_dMASK;
         break;

      case LEVEL_f:
      case LEVEL_TEST:
         LocalModelMask = CTRL_LEVEL_fMASK;
         break;

      case LEVEL_DEPOT:
      default:
         LocalModelMask = CTRL_LEVEL_tMASK;
         break;
   }

   /* All Limits are avialable in All modes. */
   LocalModelMask &= ALLMODEMASK;
   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) {

/**  **  First we deal with Energy (alarms PS1 & PS2)  **  **/

      if (RunningPreset.EnergyMLS > WeldingResults.TotalEnergy) SuspectLimitAlarm |= MENERGYBIT;
      if (RunningPreset.EnergyPLS < WeldingResults.TotalEnergy) SuspectLimitAlarm |= PENERGYBIT;


/**  **  Next we deal with Peak Power  (alarms PS3 & PS4)  **  **/

      if (RunningPreset.PowerMLS > WeldingResults.PeakPower) SuspectLimitAlarm |= MPKPOWERBIT;
      if (RunningPreset.PowerPLS < WeldingResults.PeakPower) SuspectLimitAlarm |= PPKPOWERBIT;
         

/**  **  Next we deal with Collapse Distance  (alarms PS5 & PS6)  **  **/

      if (RunningPreset.ColMLS > WeldingResults.ActualTotalCollapse) SuspectLimitAlarm |= MCOLDISTBIT;
      if (RunningPreset.ColPLS < WeldingResults.ActualTotalCollapse) SuspectLimitAlarm |= PCOLDISTBIT;


/**  **  Next we deal with Absolute Distance  (alarms PS7 & PS8)  **  **/

      if (RunningPreset.AbsMLS > WeldingResults.ActualTotalAbs) SuspectLimitAlarm |= MABSDISTBIT;
      if (RunningPreset.AbsPLS < WeldingResults.ActualTotalAbs) SuspectLimitAlarm |= PABSDISTBIT;


/**  **  Next we deal with Trigger Distance  (alarms PS9 & PS1)  **  **/

      if (RunningPreset.TrsDistMLS > WeldingResults.ActualTriggerDistance) SuspectLimitAlarm |= MTRIGDISTBIT;
         if (RunningPreset.TrsDistPLS < WeldingResults.ActualTriggerDistance) SuspectLimitAlarm |= PTRIGDISTBIT;


/**  **  Next we deal with Maximum Force  (alarms PS11 & PS12)  **  **/

      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AES) ||
		   (CurrentSetup.Actuator == MICROC) ||
           (CurrentSetup.Actuator == MICRO)) {
         if (RunningPreset.WeldForceMLS > WeldingResults.WeldForceEnd) SuspectLimitAlarm |= MFORCEBIT;
            if (RunningPreset.WeldForcePLS < WeldingResults.WeldForceEnd) SuspectLimitAlarm |= PFORCEBIT;
      }

/**  **  Finally we deal with Time  (alarms PS13 & PS14)  **  **/

      if (RunningPreset.TimeMLS > WeldingResults.ActualWeldTime) SuspectLimitAlarm |= MTIMEBIT;
         if (RunningPreset.TimePLS < WeldingResults.ActualWeldTime) SuspectLimitAlarm |= PTIMEBIT;


/***  Now remove those which are not allowed in current mode & model  ***/

      SuspectLimitAlarm &= ((~RunningPreset.SuspectLimits) & LocalModelMask);
   }
   if (SuspectLimitAlarm != 0) {
      SuspectLimitAlarm |= PSG1;
      RecordAlarm(SuspectLimitAlarm);
   }

   
   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) {

/**  **  First we deal with Energy (alarms PR1 & PR2)  **  **/

      if (RunningPreset.EnergyMLR > WeldingResults.TotalEnergy) RejectLimitAlarm |= MENERGYBIT;
      if (RunningPreset.EnergyPLR < WeldingResults.TotalEnergy) RejectLimitAlarm |= PENERGYBIT;


/**  **  Next we deal with Peak Power  (alarms PR3 & PR4)  **  **/

      if (RunningPreset.PowerMLR > WeldingResults.PeakPower) RejectLimitAlarm |= MPKPOWERBIT;
      if (RunningPreset.PowerPLR < WeldingResults.PeakPower) RejectLimitAlarm |= PPKPOWERBIT;


/**  **  Next we deal with Collapse Distance  (alarms PR5 & PR6)  **  **/

      if (RunningPreset.ColMLR > WeldingResults.ActualTotalCollapse) RejectLimitAlarm |= MCOLDISTBIT;
      if (RunningPreset.ColPLR < WeldingResults.ActualTotalCollapse) RejectLimitAlarm |= PCOLDISTBIT;


/**  **  Next we deal with Absolute Distance  (alarms PR7 & PR8)  **  **/

      if (RunningPreset.AbsMLR > WeldingResults.ActualTotalAbs) RejectLimitAlarm |= MABSDISTBIT;
      if (RunningPreset.AbsPLR < WeldingResults.ActualTotalAbs) RejectLimitAlarm |= PABSDISTBIT;


/**  **  Next we deal with Trigger Distance  (alarms PR9 & PR1)  **  **/

      if (RunningPreset.TrsDistMLR > WeldingResults.ActualTriggerDistance) RejectLimitAlarm |= MTRIGDISTBIT;
      if (RunningPreset.TrsDistPLR < WeldingResults.ActualTriggerDistance) RejectLimitAlarm |= PTRIGDISTBIT;


/**  **  Next we deal with Maximum Force  (alarms PR11 & PR12)  **  **/

      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AES) ||
		   (CurrentSetup.Actuator == MICROC) ||
           (CurrentSetup.Actuator == MICRO)) {
         if (RunningPreset.WeldForceMLR > WeldingResults.WeldForceEnd) RejectLimitAlarm |= MFORCEBIT;
         if (RunningPreset.WeldForcePLR < WeldingResults.WeldForceEnd) RejectLimitAlarm |= PFORCEBIT;
      }

/**  **  Finally we deal with Time  (alarms PR13 & PR14)  **  **/

      if (RunningPreset.TimeMLR > WeldingResults.ActualWeldTime) RejectLimitAlarm |= MTIMEBIT;
      if (RunningPreset.TimePLR < WeldingResults.ActualWeldTime) RejectLimitAlarm |= PTIMEBIT;


/***  Now remove those which are not allowed in current mode & model  ***/

      RejectLimitAlarm &= ((~RunningPreset.RejectLimits) & LocalModelMask);
   }
   if (RejectLimitAlarm != 0) {
      RejectLimitAlarm |= PRG1;
      RecordAlarm(RejectLimitAlarm);
   }

   UINT32   RLimAlarmDownSpeed = 0 ;
 
   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) {
	   if(!((RunningPreset.RVelLimitMask & BIT1) == BIT1))
		   if (RunningPreset.VelocityMLR > WeldingResults.ActualDownspeed)  RLimAlarmDownSpeed |= MVELOCITYBIT;  
	   
	   if(!((RunningPreset.RVelLimitMask & BIT2) == BIT2))	
		   if (RunningPreset.VelocityPLR < WeldingResults.ActualDownspeed)  RLimAlarmDownSpeed |= PVELOCITYBIT;
	
   }

    if (RLimAlarmDownSpeed != 0) {
	   RLimAlarmDownSpeed |= PRG1;
       RecordAlarm(RLimAlarmDownSpeed);
   }

/**  **  Finally we deal with amplitude step not occurring  **  **/

   if ( ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
         (CurrentSetup.AmpControl == TRUE)        &&  /* amp is internal &  */
         (AmpStepReachedFlag == FALSE) ) {            /* not stepped yet    */
            
      switch (RunningPreset.Amp2Flag) {
          case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
             RecordAlarm(CM4);
             break;
   
          case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
             RecordAlarm(CM6);
             break;
   
          case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
             RecordAlarm(CM11);
             break;
   
          case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
             RecordAlarm(CM8);
             break;
   
          case ((UINT16)~BIT6):                 /* Stepping enabled on force         */
             break;
   
          case AMP_STEP_AT_EXTERNAL:                    /* Stepping enabled on external in   */
             RecordAlarm(CM12);
             break;
      
          default:
             RecordAlarm(CM4);
             break;

      }
   }


   if ( ((RunningPreset.Pressure2Flag & BIT0) == BIT0) &&  /* If stepping on and */
         (PressureStepReachedFlag == FALSE) ) {            /* not stepped yet    */

      switch (RunningPreset.Pressure2Flag) {
         case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
            RecordAlarm(CM5);
            break;

         case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
            RecordAlarm(CM7);
            break;

         case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
            RecordAlarm(CM10);
            break;

         case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
            RecordAlarm(CM23);
            break;

         case PRESSURE_STEP_AT_EXTERNAL:                    /* Stepping enabled on external in   */
            RecordAlarm(CM13);
            break;

         default:
            RecordAlarm(CM5);
            break;

      }
   }
   if (CurrentSetup.SBLEnable && (CheckForDups() == TRUE) &&
        ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0))
   {
      if ((!(CurrentPreset.SBLFreqFlags & BIT0)) && SBLMinLimitReached)
         RecordAlarm(PR19);
      if ((!(CurrentPreset.SBLFreqFlags & BIT1)) && SBLMaxLimitReached)
         RecordAlarm(PR20);
   }

   /* checks and Record +R PMC band & -R PMC band alarms here*/
   CheckPMCWithPwrGraph();
   if (((WeldingResults.NoCycleAlarms != 0) || (WeldingResults.OverloadAlarms != 0) ||
	   (WeldingResults.EquipmentFailureAlarms != 0) || (WeldingResults.CycleModifiedAlarms != 0)
	   || (WeldingResults.CalibrateAlarms != 0) || (WeldingResults.Warnings != 0)
	   || (WeldingResults.SuspectBitResult != 0) || (WeldingResults.RejectBitResult != 0))
	   &&(CurrentSetup.HornClamp == TRUE)){
	   ClampOnAlarm = TRUE;
   }
   else{
	   ClampOnAlarm = FALSE;
   }
} 

/*
 * Function is called while defining weld sequence in different modes. Based on the return value of function the ConfirmReject state is
 * inserted in weld sequence
 * Returns TRUE if the global reject limit flag and any of the limit is enabled else returns false
 */
BOOLEAN IsRejectLimitsEnabled()
{
	BOOLEAN RetVal = FALSE;
	if((CurrentSetup.ControlLevel >= LEVEL_c) && (RunningPreset.RejectLimitsFlag & BIT0) && IsConfigured(INPUT_CONFIRM_REJECT))//global reject limit flag is enabled
			RetVal = TRUE;
	return RetVal;
}

/***************************************************************************
*   Purpose:
*
* This function is called when any one of setup limit button is clicked.
* Values are set on/off collectively on the basis of mask SetupLimits
* or SetupLimits2. If a limit is set to off then both plus limit and minus
* limit are disabled.If a limit is set to on then both the limit are enabled.
*                                                                    
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SetupLimitChanged(void)
{
	UINT16 MinMask = 0;
	UINT16 MaxMask = 0;
	UINT16 MBIT = 0;
	UINT16 PBIT = 0;
	UINT16 *MaskVar = 0;
	SINT32 CurrVal = 0;
	SINT32 *MinValPtr = 0;
	SINT32 *MaxValPtr = 0;
	BOOLEAN PlusLimitChanged = FALSE;
	switch (GlobalCommandID) {
	case WELDPRESSURE_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & WELDPRESSURE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & WELDPRESSURE_PBIT;
		MBIT = WELDPRESSURE_MBIT;
		PBIT = WELDPRESSURE_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.WeldPressure;
		MinValPtr = &CurrentPreset.WeldPressureMLT;
		MaxValPtr = &CurrentPreset.WeldPressurePLT;
		PlusLimitChanged = TRUE;
		break;
	case WELDPRESSURE_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & WELDPRESSURE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & WELDPRESSURE_PBIT;
		MBIT = WELDPRESSURE_MBIT;
		PBIT = WELDPRESSURE_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.WeldPressure;
		MinValPtr = &CurrentPreset.WeldPressureMLT;
		MaxValPtr = &CurrentPreset.WeldPressurePLT;
		break;
	case DOWNSPEED_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & DOWNSPEED_MBIT;
		MaxMask = CurrentPreset.SetupLimits & DOWNSPEED_PBIT;
		MBIT = DOWNSPEED_MBIT;
		PBIT = DOWNSPEED_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.Downspeed;
		MinValPtr = &CurrentPreset.DownspeedMLT;
		MaxValPtr = &CurrentPreset.DownspeedPLT;
		PlusLimitChanged = TRUE;
		break;
	case DOWNSPEED_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & DOWNSPEED_MBIT;
		MaxMask = CurrentPreset.SetupLimits & DOWNSPEED_PBIT;
		MBIT = DOWNSPEED_MBIT;
		PBIT = DOWNSPEED_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.Downspeed;
		MinValPtr = &CurrentPreset.DownspeedMLT;
		MaxValPtr = &CurrentPreset.DownspeedPLT;
		break;
	case HOLDPRESSURE_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & HOLDPRESSURE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & HOLDPRESSURE_PBIT;
		MBIT = HOLDPRESSURE_MBIT;
		PBIT = HOLDPRESSURE_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.HoldPressure;
		MinValPtr = &CurrentPreset.HoldPressureMLT;
		MaxValPtr = &CurrentPreset.HoldPressurePLT;
		PlusLimitChanged = TRUE;
		break;
	case HOLDPRESSURE_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & HOLDPRESSURE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & HOLDPRESSURE_PBIT;
		PBIT = HOLDPRESSURE_PBIT;
		MBIT = HOLDPRESSURE_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.HoldPressure;
		MinValPtr = &CurrentPreset.HoldPressureMLT;
		MaxValPtr = &CurrentPreset.HoldPressurePLT;
		break;
	case HOLDTIME_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & HOLDTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits & HOLDTIME_PBIT;
		PBIT = HOLDTIME_PBIT;
		MBIT = HOLDTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.HoldTime;
		MinValPtr = &CurrentPreset.HoldTimeMLT;
		MaxValPtr = &CurrentPreset.HoldTimePLT;
		PlusLimitChanged = TRUE;
		break;
	case HOLDTIME_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & HOLDTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits & HOLDTIME_PBIT;
		PBIT = HOLDTIME_PBIT;
		MBIT = HOLDTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.HoldTime;
		MinValPtr = &CurrentPreset.HoldTimeMLT;
		MaxValPtr = &CurrentPreset.HoldTimePLT;
		break;
	case AMPA_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & AMPA_MBIT;
		MaxMask = CurrentPreset.SetupLimits & AMPA_PBIT;
		PBIT = AMPA_PBIT;
		MBIT = AMPA_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.Amp1;
		MinValPtr = &CurrentPreset.AmpAMLT;
		MaxValPtr = &CurrentPreset.AmpAPLT;
		PlusLimitChanged = TRUE;
		break;
	case AMPA_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & AMPA_MBIT;
		MaxMask = CurrentPreset.SetupLimits & AMPA_PBIT;
		PBIT = AMPA_PBIT;
		MBIT = AMPA_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.Amp1;
		MinValPtr = &CurrentPreset.AmpAMLT;
		MaxValPtr = &CurrentPreset.AmpAPLT;
		break;
	case TRIGFORCE_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & TRIGFORCE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & TRIGFORCE_PBIT;
		MBIT = TRIGFORCE_MBIT;
		PBIT = TRIGFORCE_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.TriggerForce;
		MinValPtr = &CurrentPreset.TrigForceMLT;
		MaxValPtr = &CurrentPreset.TrigForcePLT;
		PlusLimitChanged = TRUE;
		break;
	case TRIGFORCE_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & TRIGFORCE_MBIT;
		MaxMask = CurrentPreset.SetupLimits & TRIGFORCE_PBIT;
		MBIT = TRIGFORCE_MBIT;
		PBIT = TRIGFORCE_PBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.TriggerForce;
		MinValPtr = &CurrentPreset.TrigForceMLT;
		MaxValPtr = &CurrentPreset.TrigForcePLT;
		break;
	case WELDTIME_PLT_ID:
		MinMask = CurrentPreset.SetupLimits & WELDTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits & WELDTIME_PBIT;
		PBIT = WELDTIME_PBIT;
		MBIT = WELDTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.WeldTime;
		MinValPtr = &CurrentPreset.WeldTimeMLT;
		MaxValPtr = &CurrentPreset.WeldTimePLT;
		PlusLimitChanged = TRUE;
		break;
	case WELDTIME_MLT_ID:
		MinMask = CurrentPreset.SetupLimits & WELDTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits & WELDTIME_PBIT;
		PBIT = WELDTIME_PBIT;
		MBIT = WELDTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits;
		CurrVal = CurrentPreset.WeldTime;
		MinValPtr = &CurrentPreset.WeldTimeMLT;
		MaxValPtr = &CurrentPreset.WeldTimePLT;
		break;
	case WELDENERGY_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & WELDENERGY_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & WELDENERGY_PBIT;
		PBIT = WELDENERGY_PBIT;
		MBIT = WELDENERGY_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.WeldEnergy;
		MinValPtr = &CurrentPreset.WeldEnergyMLT;
		MaxValPtr = &CurrentPreset.WeldEnergyPLT;
		PlusLimitChanged = TRUE;
		break;
	case WELDENERGY_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & WELDENERGY_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & WELDENERGY_PBIT;
		PBIT = WELDENERGY_PBIT;
		MBIT = WELDENERGY_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.WeldEnergy;
		MinValPtr = &CurrentPreset.WeldEnergyMLT;
		MaxValPtr = &CurrentPreset.WeldEnergyPLT;
		break;
	case PEAKPOWER_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & PEAKPWR_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & PEAKPWR_PBIT;
		PBIT = PEAKPWR_PBIT;
		MBIT = PEAKPWR_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.PeakPwr;
		MinValPtr = &CurrentPreset.PeakPowerMLT;
		MaxValPtr = &CurrentPreset.PeakPowerPLT;
		PlusLimitChanged = TRUE;
		break;
	case PEAKPOWER_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & PEAKPWR_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & PEAKPWR_PBIT;
		PBIT = PEAKPWR_PBIT;
		MBIT = PEAKPWR_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.PeakPwr;
		MinValPtr = &CurrentPreset.PeakPowerMLT;
		MaxValPtr = &CurrentPreset.PeakPowerPLT;
		break;
	case COLLAPSEDIST_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & COLDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & COLDIST_PBIT;
		PBIT = COLDIST_PBIT;
		MBIT = COLDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.ColDist;
		MinValPtr = &CurrentPreset.CollapseDistMLT;
		MaxValPtr = &CurrentPreset.CollapseDistPLT;
		PlusLimitChanged = TRUE;
		break;
	case COLLAPSEDIST_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & COLDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & COLDIST_PBIT;
		PBIT = COLDIST_PBIT;
		MBIT = COLDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.ColDist;
		MinValPtr = &CurrentPreset.CollapseDistMLT;
		MaxValPtr = &CurrentPreset.CollapseDistPLT;
		break;
	case ABSDIST_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & ABSDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & ABSDIST_PBIT;
		PBIT = ABSDIST_PBIT;
		MBIT = ABSDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.AbsDist;
		MinValPtr = &CurrentPreset.AbsDistMLT;
		MaxValPtr = &CurrentPreset.AbsDistPLT;
		PlusLimitChanged = TRUE;
		break;
	case ABSDIST_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & ABSDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & ABSDIST_PBIT;
		PBIT = ABSDIST_PBIT;
		MBIT = ABSDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.AbsDist;
		MinValPtr = &CurrentPreset.AbsDistMLT;
		MaxValPtr = &CurrentPreset.AbsDistPLT;
		break;
	case SCRUBTIME_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & SCRUBTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & SCRUBTIME_PBIT;
		PBIT = SCRUBTIME_PBIT;
		MBIT = SCRUBTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.ScrubTime;
		MinValPtr = &CurrentPreset.ScrubTimeMLT;
		MaxValPtr = &CurrentPreset.ScrubTimePLT;
		PlusLimitChanged = TRUE;
		break;
	case SCRUBTIME_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & SCRUBTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & SCRUBTIME_PBIT;
		PBIT = SCRUBTIME_PBIT;
		MBIT = SCRUBTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.ScrubTime;
		MinValPtr = &CurrentPreset.ScrubTimeMLT;
		MaxValPtr = &CurrentPreset.ScrubTimePLT;
		break;
	case SCRUBAMP_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_PBIT;
		PBIT = AMPSCRUBTIME_PBIT;
		MBIT = AMPSCRUBTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.AmpScrubTime;
		MinValPtr = &CurrentPreset.ScrubAmpMLT;
		MaxValPtr = &CurrentPreset.ScrubAmpPLT;
		PlusLimitChanged = TRUE;
		break;
	case SCRUBAMP_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_PBIT;
		PBIT = AMPSCRUBTIME_PBIT;
		MBIT = AMPSCRUBTIME_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.AmpScrubTime;
		MinValPtr = &CurrentPreset.ScrubAmpMLT;
		MaxValPtr = &CurrentPreset.ScrubAmpPLT;
		break;
	case TRIGDIST_PLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & TRIGDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & TRIGDIST_PBIT;
		PBIT = TRIGDIST_PBIT;
		MBIT = TRIGDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.TriggerDistance;
		MinValPtr = &CurrentPreset.TrigDistanceMLT;
		MaxValPtr = &CurrentPreset.TrigDistancePLT;
		PlusLimitChanged = TRUE;
		break;
	case TRIGDIST_MLT_ID:
		MinMask = CurrentPreset.SetupLimits2 & TRIGDIST_MBIT;
		MaxMask = CurrentPreset.SetupLimits2 & TRIGDIST_PBIT;
		PBIT = TRIGDIST_PBIT;
		MBIT = TRIGDIST_MBIT;
		MaskVar = &CurrentPreset.SetupLimits2;
		CurrVal = CurrentPreset.TriggerDistance;
		MinValPtr = &CurrentPreset.TrigDistanceMLT;
		MaxValPtr = &CurrentPreset.TrigDistancePLT;
		break;
	}
	if(PlusLimitChanged) //PBIT CHANGED
	{
		if (MaxMask == PBIT)  //max off
			*(MaskVar) |= MBIT; //set min off
		else if(MinMask == MBIT){
			*(MaskVar) &= (~MBIT); //set min on
			*MinValPtr = CurrVal ;//make minimum value equal to current value
		}
	}
	else if(MaskVar)  //MBIT CHANGED //coverity fix 12565
	{
		if (MinMask == MBIT)  //min off
			*MaskVar |= PBIT; //set max off
		else if(MaxMask == PBIT)
		{
			*(MaskVar) &= (~PBIT); //set max on
			*MaxValPtr  = CurrVal;
		}
	}
}


/***************************************************************************
*                                                                         
*   Purpose:
*
*   This function initialize SetupMinMax structure.Parameter min and max value
*	,plus bit mask,minus bit mask,current value,SetupLimits/SetupLimits2
*	is filled in this structure.MinMap structure use this function as callback.
*                                                                      
*   Entry condition:                                                      
*   UINT16 ID:enable id of parameter
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void PreSetupLimitMinMax(UINT16 ID) {
	struct SetupMinMax ParamLim;
	memset(&ParamLim, 0, sizeof(SetupMinMax));
	if ((CurrentPreset.Validated == FALSE)||(CurrentSetup.ControlLevel<LEVEL_c))
		ParamLim.UseOriginalMinMax = TRUE;
	switch (ID) {
	case WELD_PRESSURE_ID:
	case PRESSUREMODE_SET:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & WELDPRESSURE_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & WELDPRESSURE_PBIT;
		ParamLim.MinLimit = MinLimit.WeldPressure;
		ParamLim.MaxLimit = MaxLimit.WeldPressure;
		ParamLim.MinLimMLT = CurrentPreset.WeldPressureMLT;
		ParamLim.MaxLimPLT = CurrentPreset.WeldPressurePLT;
		ParamLim.MBIT = WELDPRESSURE_MBIT;
		ParamLim.PBIT = WELDPRESSURE_PBIT;
		ParamLim.CurrentValue = CurrentPreset.WeldPressure;
		break;
	case FLOW_CONTROL_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & DOWNSPEED_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & DOWNSPEED_PBIT;
		ParamLim.MinLimit = MinLimit.Downspeed;
		ParamLim.MaxLimit = MaxLimit.Downspeed;
		ParamLim.MinLimMLT = CurrentPreset.DownspeedMLT;
		ParamLim.MaxLimPLT = CurrentPreset.DownspeedPLT;
		ParamLim.MBIT = DOWNSPEED_MBIT;
		ParamLim.PBIT = DOWNSPEED_PBIT;
		ParamLim.CurrentValue = CurrentPreset.Downspeed;
		break;
	case HOLD_PRESSURE_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & HOLDPRESSURE_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & HOLDPRESSURE_PBIT;
		ParamLim.MinLimit = MinLimit.HoldPressure;
		ParamLim.MaxLimit = MaxLimit.HoldPressure;
		ParamLim.MinLimMLT = CurrentPreset.HoldPressureMLT;
		ParamLim.MaxLimPLT = CurrentPreset.HoldPressurePLT;
		ParamLim.MBIT = HOLDPRESSURE_MBIT;
		ParamLim.PBIT = HOLDPRESSURE_PBIT;
		ParamLim.CurrentValue = CurrentPreset.HoldPressure;
		break;
	case HOLDTIME_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & HOLDTIME_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & HOLDTIME_PBIT;
		ParamLim.MinLimit = MinLimit.HoldTime;
		ParamLim.MaxLimit = MaxLimit.HoldTime;
		ParamLim.MinLimMLT = CurrentPreset.HoldTimeMLT;
		ParamLim.MaxLimPLT = CurrentPreset.HoldTimePLT;
		ParamLim.MBIT = HOLDTIME_MBIT;
		ParamLim.PBIT = HOLDTIME_PBIT;
		ParamLim.CurrentValue = CurrentPreset.HoldTime;
		break;
	case AMP1_ID:
	case AMP1_FIX_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & AMPA_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & AMPA_PBIT;
		ParamLim.MinLimit = MinLimit.Amp1;
		ParamLim.MaxLimit = MaxLimit.Amp1;
		ParamLim.MinLimMLT = CurrentPreset.AmpAMLT;
		ParamLim.MaxLimPLT = CurrentPreset.AmpAPLT;
		ParamLim.MBIT = AMPA_MBIT;
		ParamLim.PBIT = AMPA_PBIT;
		ParamLim.CurrentValue = CurrentPreset.Amp1;
		break;
	case TRIGGERFORCE_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & TRIGFORCE_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & TRIGFORCE_PBIT;
		ParamLim.MinLimit = CurrentSetup.MinTrigForce;
		ParamLim.MaxLimit = MaxLimit.TriggerForce;
		ParamLim.MinLimMLT = CurrentPreset.TrigForceMLT;
		ParamLim.MaxLimPLT = CurrentPreset.TrigForcePLT;
		ParamLim.MBIT = TRIGFORCE_MBIT;
		ParamLim.PBIT = TRIGFORCE_PBIT;
		ParamLim.CurrentValue = CurrentPreset.TriggerForce;
		break;
	case WELDTIME_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits;
		ParamLim.MinMask = CurrentPreset.SetupLimits & WELDTIME_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits & WELDTIME_PBIT;
		ParamLim.MinLimit = MinLimit.WeldTime;
		ParamLim.MaxLimit = MaxLimit.WeldTime;
		ParamLim.MinLimMLT = CurrentPreset.WeldTimeMLT;
		ParamLim.MaxLimPLT = CurrentPreset.WeldTimePLT;
		ParamLim.MBIT = WELDTIME_MBIT;
		ParamLim.PBIT = WELDTIME_PBIT;
		ParamLim.CurrentValue = CurrentPreset.WeldTime;
		break;
	case WELDENERGY_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & WELDENERGY_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & WELDENERGY_PBIT;
		ParamLim.MinLimit = MinLimit.WeldEnergy;
		ParamLim.MaxLimit = MaxLimit.WeldEnergy;
		ParamLim.MinLimMLT = CurrentPreset.WeldEnergyMLT;
		ParamLim.MaxLimPLT = CurrentPreset.WeldEnergyPLT;
		ParamLim.MBIT = WELDENERGY_MBIT;
		ParamLim.PBIT = WELDENERGY_PBIT;
		ParamLim.CurrentValue = CurrentPreset.WeldEnergy;
		break;
	case PEAKPWR_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & PEAKPWR_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & PEAKPWR_PBIT;
		ParamLim.MinLimit = MinLimit.PeakPwr;
		ParamLim.MaxLimit = MaxLimit.PeakPwr;
		ParamLim.MinLimMLT = CurrentPreset.PeakPowerMLT;
		ParamLim.MaxLimPLT = CurrentPreset.PeakPowerPLT;
		ParamLim.MBIT = PEAKPWR_MBIT;
		ParamLim.PBIT = PEAKPWR_PBIT;
		ParamLim.CurrentValue = CurrentPreset.PeakPwr;
		break;
	case COLDIST_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & COLDIST_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & COLDIST_PBIT;
		ParamLim.MinLimit = MinLimit.ColDist;
		ParamLim.MaxLimit = MaxLimit.ColDist;
		ParamLim.MinLimMLT = CurrentPreset.CollapseDistMLT;
		ParamLim.MaxLimPLT = CurrentPreset.CollapseDistPLT;
		ParamLim.MBIT = COLDIST_MBIT;
		ParamLim.PBIT = COLDIST_PBIT;
		ParamLim.CurrentValue = CurrentPreset.ColDist;
		break;
	case ABSDIST_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & ABSDIST_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & ABSDIST_PBIT;
		ParamLim.MinLimit = MinLimit.AbsDist;
		ParamLim.MaxLimit = MaxLimit.AbsDist;
		ParamLim.MinLimMLT = CurrentPreset.AbsDistMLT;
		ParamLim.MaxLimPLT = CurrentPreset.AbsDistPLT;
		ParamLim.MBIT = ABSDIST_MBIT;
		ParamLim.PBIT = ABSDIST_PBIT;
		ParamLim.CurrentValue = CurrentPreset.AbsDist;
		break;
	case SCRUBTIME_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & SCRUBTIME_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & SCRUBTIME_PBIT;
		ParamLim.MinLimit = MinLimit.ScrubTime;
		ParamLim.MaxLimit = MaxLimit.ScrubTime;
		ParamLim.MinLimMLT = CurrentPreset.ScrubTimeMLT;
		ParamLim.MaxLimPLT = CurrentPreset.ScrubTimePLT;
		ParamLim.MBIT = SCRUBTIME_MBIT;
		ParamLim.PBIT = SCRUBTIME_PBIT;
		ParamLim.CurrentValue = CurrentPreset.ScrubTime;
		break;
	case AMPSCRUBTIME_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_PBIT;
		ParamLim.MinLimit = MinLimit.AmpScrubTime;
		ParamLim.MaxLimit = MaxLimit.AmpScrubTime;
		ParamLim.MinLimMLT = CurrentPreset.ScrubAmpMLT;
		ParamLim.MaxLimPLT = CurrentPreset.ScrubAmpPLT;
		ParamLim.MBIT = AMPSCRUBTIME_MBIT;
		ParamLim.PBIT = AMPSCRUBTIME_PBIT;
		ParamLim.CurrentValue = CurrentPreset.AmpScrubTime;
		break;
	case TRIGGERDISTANCE_ID:
		ParamLim.ID = ID;
		ParamLim.MaskVar = &CurrentPreset.SetupLimits2;
		ParamLim.MinMask = CurrentPreset.SetupLimits2 & TRIGDIST_MBIT;
		ParamLim.Maxmask = CurrentPreset.SetupLimits2 & TRIGDIST_PBIT;
		ParamLim.MinLimit = MinLimit.TriggerDistance;
		ParamLim.MaxLimit = MaxLimit.TriggerDistance;
		ParamLim.MinLimMLT = CurrentPreset.TrigDistanceMLT;
		ParamLim.MaxLimPLT = CurrentPreset.TrigDistancePLT;
		ParamLim.MBIT = TRIGDIST_MBIT;
		ParamLim.PBIT = TRIGDIST_PBIT;
		ParamLim.CurrentValue = CurrentPreset.TriggerDistance;
		break;
	}
   if (ParamLim.ID > 0) {
      SetSetupLimits(&ParamLim);
      if ((CurrentSetup.AuthorityCheck == TRUE)
            && ((ParamLim.Maxmask & ParamLim.PBIT) == ParamLim.PBIT || (ParamLim.MinMask & ParamLim.MBIT) == ParamLim.MBIT)
            && (CurrentSetup.SecurityLevel == TECHNICIAN) && (CurrentPreset.Locked == TRUE)) {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
   }
}

/***************************************************************************
*                                                                         
*   Purpose:
*
*	SetSetupLimits function is called from PreSetupLimitMinMax function.
*	This function uses the SetupMinMax structure fields to set the setup
*	limits for the parameter.
*                                                                         
*   Entry condition:                                                      
*	struct SetupMinMax pointer
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SetSetupLimits(struct SetupMinMax *ParamLim) 
{
	if (ParamLim == NULL)
		return;
	if (ParamLim->UseOriginalMinMax == TRUE)
	{
		MinSetupLim = ParamLim->MinLimit;
		MaxSetupLim = ParamLim->MaxLimit;
	}
	else
	{
		if (!(ParamLim->MinMask == ParamLim->MBIT)	&& !(ParamLim->Maxmask == ParamLim->PBIT))
		{
			if ((ParamLim->CurrentValue < ParamLim->MinLimMLT) || (ParamLim->CurrentValue > ParamLim->MaxLimPLT))
			{
				MinSetupLim = MaxSetupLim = ParamLim->CurrentValue;
			}
			else
			{
				MinSetupLim = ParamLim->MinLimMLT;
				MaxSetupLim = ParamLim->MaxLimPLT;
			}
		}
		else
		{
			MinSetupLim = ParamLim->MinLimit;
			MaxSetupLim = ParamLim->MaxLimit;
		}
	}
}
