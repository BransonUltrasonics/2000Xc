/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET5.cpp_v   1.19   Oct 10 2017 15:20:16   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET5.cpp_v  $
 * 
 *    Rev 1.19   Oct 10 2017 15:20:16   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.18   Jun 07 2017 15:19:50   RJamloki
 * change config variable to PressureStepDownFlag
 * 
 *    Rev 1.17   29 Aug 2016 12:07:20   RJamloki
 * Adding a CurrentSetup.PressureStepDown flag in the setup structure for enable/disabled hold and step pressure alarms
 * 
 *    Rev 1.16   26 May 2016 13:42:10   RJamloki
 * Disabled hold and step pressure alarms
 * 
 *    Rev 1.15   08 Apr 2015 13:47:58   AnPawar
 * VerifyPressureStepping() function check Pressure Stepping.
 * 
 *    Rev 1.14   20 Oct 2014 06:33:20   AnPawar
 * VerifyPresetModel5() function changed.
 * 
 *    Rev 1.13   03 Oct 2014 06:16:46   rjamloki
 * VerifyPresetModel5() function changed
 * 
 *    Rev 1.12   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.11   18 Aug 2014 01:36:10   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   28 Jul 2014 12:36:46   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 11:54:50   rjamloki
 * Enabled Rapid Traverse alarm for AES.
 * 
 *    Rev 1.8   11 Jun 2014 12:39:36   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:55:24   rjamloki
 * extern variables clean up
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
/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name:   VERIFY_PRESET_MODEL5  

   Filename:      vpreset5.c     

   Function Name: VerifyPresetModel5
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"
 ----------------------------- DESCRIPTION -------------------------------*/

/* ------------------------------ INCLUDE FILES ----------------------------*/

#include "qdef.h"
#include "state.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "ready.h"
#include "alarms.h"
#include "sc.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "menu1.h"
#include "weld_obj.h"
#include "inports.h"



/*------------------------------ WELD OBJECT DATA --------------------------*/

extern SINT32 MaximumForce;

UINT32 VerifyPresetModel5(void)
/***************************************************************************/
/*                                                                         */
/*  This function will verify the preset against itself and the system     */
/*  configuration.  It will check the following things:                    */
/*                                                                         */
/*    1) Make sure the required forces and downspeeds are achievable based */
/*       on the current regulator pressure.                                */
/*    2) Check all upper and lower limits for min/max cross.               */
/*    3) If any distance mode is required, make sure the linear encoder    */
/*       is available.                                                     */
/*    4) Check EP/AE requirements against actual actuator installed.       */
/*    5) After the preset is verified a state sequence will be generated   */
/*       to run the selected weld cycle.                                   */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*  The value returned will be FALSE if the preset is okay and can be run. */
/*  An error code will be returned if any problems are found.  The         */
/*  problems will be logged in PresetProblems array.  See Problems enum    */
/*  for list.                                                              */
/*                                                                         */
/***************************************************************************/
{
   UINT32 RetVal = FALSE;
   UINT32 RetValSteppingCheck;

   RetVal = VerifyPresetModel4();
   MaximumForce = GetMaxForce();

 /* Rapid Traverse conflicts with -Reject Absolute Distance Limit   */
 
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsMLR) ) {
      RetVal = SE177;
      RecordSetupAlarm(RetVal);
   }
       
 /* RT Conflicts with -Suspect Absolute Distance Limit */
 
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits &/* MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsMLS) ) {
      RetVal = SE179;
      RecordSetupAlarm(RetVal);
   }
 /* RT Conflicts with + Reject Absolute Distance limit */
 
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsPLR) ) {
      RetVal = SE181;
      RecordSetupAlarm(RetVal);
    }
  
  /* RT Conflicts with +Suspect Absolute Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsPLS) ) {
      RetVal = SE183;
      RecordSetupAlarm(RetVal);
   }
  
  /* RT Conflicts with +Reject Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits &/*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistPLR) ) {
      RetVal = SE184;
      RecordSetupAlarm(RetVal);
   }
                             
  /*  RT Conflicts with +Suspect Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistPLS) ) {
      RetVal = SE185;
      RecordSetupAlarm(RetVal);
   }

  /* RT Conflicts with -Reject Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistMLR) ) {
      RetVal = SE186;
      RecordSetupAlarm(RetVal);
   }
 
 /* RT Conflicts with -Suspect Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistMLS) ) {
      RetVal = SE187;
      RecordSetupAlarm(RetVal);
   }

/* RT Conflicts with Absolute Cutoff Distance Limit */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      ((RunningPreset.ABSCutoffFlag & /*ABSCutoff.BitMask*/BIT0) == 0)&&
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.RTDist >= RunningPreset.ABSCutoffDist ) ) {
      RetVal = SE193;
      RecordSetupAlarm(RetVal);
   }

/* RT Conflicts with Absolute Distance Setting */  
  
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((/*AbsoluteAbs.mode*/ABSOLUTEMODE & RunningPreset.WeldMode) == RunningPreset.WeldMode)&&
      (RunningPreset.RTDist >= RunningPreset.AbsDist ) ) {
      RetVal = SE194;
      RecordSetupAlarm(RetVal);
   }

  /* Check for incorrect trigger force */

   if ( ( (CurrentSetup.Actuator == AED) ||
          (CurrentSetup.Actuator == AES) ||
		  (CurrentSetup.Actuator == MICROC) ||
		  (CurrentSetup.Actuator == MICRO)) &&
        (RunningPreset.TriggerForce < CurrentSetup.MinTrigForce || RunningPreset.TriggerForce > MaxLimit.TriggerForce) )
   {
      RetVal = SE298;
      RecordSetupAlarm(RetVal);
   }

   /* Check if pressure step down is disabled to verify   */
   /* that all pressure steps are made to a pressure that */
   /* is equal-to or higher-than the previous pressure.   */
   if (CurrentSetup.PressureStepDownFlag == FALSE){
    /* Check for incorrect Weld & Hold Pressure Settings*/
    /*Check for Weld Pressure bigger than hold pressure in case of AES actuator.*/
    if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (RunningPreset.WeldPressure > RunningPreset.HoldPressure))
    {
      RetVal = SE196;
      RecordSetupAlarm(RetVal);
    }
    if((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && ((RunningPreset.Pressure2Flag & BIT0) == BIT0)){
      /*Check for Weld Pressure2 bigger than hold pressure in case of AES actuator & Stepping ON.*/
      if(RunningPreset.Pressure2 > RunningPreset.HoldPressure){
        RetVal = SE197;
        RecordSetupAlarm(RetVal);
      }
      /*Check for Weld Pressure bigger than Weld pressure2 in case of AES actuator & Stepping ON.*/
      if(RunningPreset.WeldPressure >= RunningPreset.Pressure2){
        RetVal = SE198;
        RecordSetupAlarm(RetVal);
      }
    }
   }

   //Call function to verify Pressure stepping conditions.
   RetValSteppingCheck = VerifyPressureStepping();
   if(RetValSteppingCheck)
	   RetVal = RetValSteppingCheck;
   return(RetVal);
}

/***************************************************************************
 *
 *   Purpose:
 *
 *   This function will check Pressure stepping which might be enabled.
 *   It will then check the actuator type to see if stepping is allowed.
 *   It will then verifies various conditions applicable while stepping is ON
 *   It will return an ERRORCODE in case of any failure in verification or
 *   FALSE in case of no failure.
 *
 *   Entry condition:
 *	void
 *
 *   Exit condition:
 *	UINT32
 *
 ***************************************************************************/
UINT32 VerifyPressureStepping(void)
{
   UINT32 RetVal = FALSE;
   /* Pressure Step Conflicts with Collapse Cutoff */
   if ((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
         && ((RunningPreset.Pressure2Flag & BIT0) == BIT0)) {
      if ((RunningPreset.Pressure2Flag == PRESSURE_STEP_AT_EXTERNAL) &&   //If pressure stepping is on external
            !IsConfigured(INPUT_EXT_TRIGGER))   //but external input is not configured
                  {
         RetVal = SE296;
         RecordSetupAlarm(RetVal);
      }
      /* Pressure Step Conflicts with +Reject Peak Power Limit */
      if (((RunningPreset.RejectLimits & PPKPOWERBIT) == 0)
            && ((RunningPreset.Pressure2Flag & BIT4) == 0)
            && ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.PowerPLR <= RunningPreset.PressureTrigPowerValue)) {
         RetVal = SE208;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with +Suspect Peak Power Limit */
      if (((RunningPreset.SuspectLimits & PPKPOWERBIT) == 0)
            && ((RunningPreset.Pressure2Flag & BIT4) == 0)
            && ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.PowerPLS <= RunningPreset.PressureTrigPowerValue)) {
         RetVal = SE209;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with +Reject Energy Limit */
      if (((RunningPreset.RejectLimits & PENERGYBIT) == 0)
            && ((RunningPreset.Pressure2Flag & BIT3) == 0)
            && ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.EnergyPLR <= RunningPreset.PressureTrigEnerValue)) {
         RetVal = SE214;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with +Suspect Energy Limit */
      if (((RunningPreset.SuspectLimits & PENERGYBIT) == 0)
            && ((RunningPreset.Pressure2Flag & BIT3) == 0)
            && ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.EnergyPLS <= RunningPreset.PressureTrigEnerValue)) {
         RetVal = SE217;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with -Reject Collapse Distance Limit */
      if (((RunningPreset.Pressure2Flag & BIT5) == 0)
            && ((RunningPreset.RejectLimits & MCOLDISTBIT) == 0)
            && ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.ColMLR >= RunningPreset.PressureTrigColValue)) {
         RetVal = SE219;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with -Suspect Collapse Distance Limit */
      if (((RunningPreset.Pressure2Flag & BIT5) == 0)
            && ((RunningPreset.SuspectLimits & MCOLDISTBIT) == 0)
            && ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.ColMLS >= RunningPreset.PressureTrigColValue)) {
         RetVal = SE227;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with +Reject Collapse Distance Limit */
      if (((RunningPreset.Pressure2Flag & BIT5) == 0)
            && ((RunningPreset.RejectLimits & PCOLDISTBIT) == 0)
            && ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.ColPLR <= RunningPreset.PressureTrigColValue)) {
         RetVal = SE230;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with +Suspect Collapse Distance Limit */
      if (((RunningPreset.Pressure2Flag & BIT5) == 0)
            && ((RunningPreset.SuspectLimits & PCOLDISTBIT) == 0)
            && ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
            && (RunningPreset.ColPLS <= RunningPreset.PressureTrigColValue)) {
         RetVal = SE233;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Collapse Distance setting in collapse mode */
      if ((RunningPreset.WeldMode == COLLAPSEMODE)
            && ((RunningPreset.Pressure2Flag & BIT5) == 0) &&
            (RunningPreset.PressureTrigColValue >= RunningPreset.ColDist)) {
         RetVal = SE235;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Peak Power Cutoff */
      if ((RunningPreset.ControlLimitsFlag == TRUE)
            && (RunningPreset.PeakPwrCutoffFlag == FALSE)
            && ((RunningPreset.Pressure2Flag & BIT4) == 0)
            && (RunningPreset.WeldMode != PKPOWERMODE)
            && (RunningPreset.PeakPwrCutoff
                  <= RunningPreset.PressureTrigPowerValue)) {
         RetVal = SE239;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Peak Power Settings */
      if ((RunningPreset.WeldMode == PKPOWERMODE)
            && ((RunningPreset.Pressure2Flag & BIT4) == 0)
            && (RunningPreset.PeakPwr <= RunningPreset.PressureTrigPowerValue)) {
         RetVal = SE240;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Energy Settings */
      if ((RunningPreset.WeldMode == ENERGYMODE)
            && ((RunningPreset.Pressure2Flag & BIT3) == 0)
            && (RunningPreset.WeldEnergy <= RunningPreset.PressureTrigEnerValue)) {
         RetVal = SE241;
         RecordSetupAlarm(RetVal);
      }
      /* Pressure Step Conflicts with Energy Compensation */
      if ((RunningPreset.WeldMode == TIMEMODE)
            && ((RunningPreset.Pressure2Flag & BIT3) == 0)
            && (RunningPreset.EnergyCompFlag == TRUE)
            && (RunningPreset.ControlLimitsFlag == TRUE) &&
            (RunningPreset.EnergyPL <= RunningPreset.PressureTrigEnerValue)) {
         RetVal = SE242;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Weld Time */
      if ((RunningPreset.WeldMode == TIMEMODE)
            && ((RunningPreset.Pressure2Flag & BIT2) == 0)
            && (RunningPreset.WeldTime <= RunningPreset.PressureTrigTimeValue)) {
         RetVal = SE243;
         RecordSetupAlarm(RetVal);
      }

      /* Pressure Step Conflicts with Maximum Weld Time */
      if ((RunningPreset.WeldMode != TIMEMODE)
            && ((RunningPreset.Pressure2Flag & BIT2) == 0)
            && (RunningPreset.MaxTimeout <= RunningPreset.PressureTrigTimeValue)) {
         RetVal = SE260;
         RecordSetupAlarm(RetVal);
      }

   }
   return RetVal;
}

