/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET3.cpp_v   1.11   28 Nov 2014 07:42:30   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET3.cpp_v  $
 * 
 *    Rev 1.11   28 Nov 2014 07:42:30   rjamloki
 * Warning Fix.
 * 
 *    Rev 1.10   03 Oct 2014 06:15:34   rjamloki
 *  VerifyPresetModel3() function changed
 * 
 *    Rev 1.9   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.8   28 Jul 2014 12:36:46   rjamloki
 * psos.h removed
 * 
 *    Rev 1.7   11 Jun 2014 12:38:04   rjamloki
 * psos include fix
 * 
 *    Rev 1.6   21 May 2014 10:48:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:55:16   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:48   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:58   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:58   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name:   VERIFY_PRESET_MODEL3  

   Filename:      vpreset3.c     

   Function Name: VerifyPresetModel3
  
      Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"
   ------------------------------------------------------------------------*/
/* ----------------------------- DESCRIPTION -------------------------------*/

/* ------------------------------ INCLUDE FILES ----------------------------*/

#include "qdef.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "ready.h"
#include "alarms.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"


/*------------------------------ WELD OBJECT DATA --------------------------*/


UINT32 VerifyPresetModel3(void)
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
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag = FALSE;


   RetVal = VerifyPresetModel2();

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
/*----   Cross check amplitude stepping with weld time  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) == 0) &&
            (RunningPreset.AmpTrigTimeValue >= RunningPreset.WeldTime) ) {
               RetVal = SE15;
               RecordSetupAlarm(RetVal);
         }
               
/*----   Cross check amplitude step on energy with energy compensation  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
            (RunningPreset.EnergyCompFlag == TRUE) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPL) ) {
               RetVal = SE38;
               RecordSetupAlarm(RetVal);
         }

/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case ENERGYMODE:
/*----   Cross check amplitude stepping with energy setting  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
            (RunningPreset.AmpTrigEnerValue >= RunningPreset.WeldEnergy) ) {
               RetVal = SE48;
               RecordSetupAlarm(RetVal);
         }
               
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case PKPOWERMODE:
/*---    Cross check amplitude step on power with peak power value   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwr) ) {
               RetVal = SE37;
               RecordSetupAlarm(RetVal);
         }
         break;

      case ABSOLUTEMODE:
         if (CurrentSetup.ControlLevel < LEVEL_d) {
            RetVal = SE259;
            RecordSetupAlarm(RetVal);
         }
         break;

      case GRDDETECTMODE:
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case COLLAPSEMODE:
         if (CurrentSetup.ControlLevel < LEVEL_d) {
            RetVal = SE259;
            RecordSetupAlarm(RetVal);
         }
         break;

      case CONTINUOUSMODE:
         break;
   }
   

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/

/*--  Check amplitude step at time with timeout  --*/

   if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
      (CurrentSetup.AmpControl == TRUE) &&
      (RunningPreset.WeldMode != TIMEMODE) &&
      ((RunningPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) == 0) &&
      (RunningPreset.AmpTrigTimeValue >= RunningPreset.MaxTimeout) ) {
         RetVal = SE43;
         RecordSetupAlarm(RetVal);
   }


 
/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Suspect Limits are enabled --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
        (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      SuspectFlag = TRUE;

/*--  Check amplitude step at peak power with plus suspect limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
         ((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.AmpTrigPowerValue >= RunningPreset.PowerPLS) ) {
             RetVal = SE17;
             RecordSetupAlarm(RetVal);
      }

/*--  Check amplitude step at energy with plus suspect limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPLS) ) {
            RetVal = SE19;
            RecordSetupAlarm(RetVal);
      }

   }



/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Reject Limits are enabled  --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
        (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      RejectFlag = TRUE;
 
/*--  Check amplitude step at peak power with plus reject limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.AmpTrigPowerValue >= RunningPreset.PowerPLR) ) {
            RetVal = SE16;
            RecordSetupAlarm(RetVal);
      }

/*--  Check amplitude step at energy with plus reject limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPLR) ) {
            RetVal = SE18;
            RecordSetupAlarm(RetVal);
      }
   }

/*-----------------------------------------------------------------------*/
/*---  Here are tests for when BOTH reject and suspect limits are on  ---*/
/*-----------------------------------------------------------------------*/
      
   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE)) {
      ;
   }


/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 4 or above.                                     ----*/
/*--------------------------------------------------------------------------*/


   return(RetVal);
}

