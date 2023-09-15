/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET4.cpp_v   1.15   Oct 10 2017 15:15:24   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET4.cpp_v  $
 * 
 *    Rev 1.15   Oct 10 2017 15:15:24   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.14   08 Apr 2015 13:47:44   AnPawar
 * VerifyPresetModel4() function check Pressure Stepping.
 * 
 *    Rev 1.13   28 Nov 2014 07:42:46   rjamloki
 * Warning Fix.
 * 
 *    Rev 1.12   03 Oct 2014 06:16:12   rjamloki
 * VerifyPresetModel4() function changed
 * 
 *    Rev 1.11   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.10   18 Aug 2014 01:36:10   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.9   28 Jul 2014 12:36:46   rjamloki
 * psos.h removed
 * 
 *    Rev 1.8   15 Jul 2014 17:00:26   hasanchez
 * Changes related to Absolute limits (Reject and Suspect).
 * 
 *    Rev 1.7   11 Jun 2014 12:39:36   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:55:20   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:50   rjamloki
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

 Module name:   VERIFY_PRESET_MODEL4

 Filename:      vpreset4.c

 Function Name: VerifyPresetModel4

 Written by:    Barry E. Kymer
 Date:          07-07-97
 Language:      "C"
----------------------------------------------------------------------------*/
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
#include "actnvram.h"
#include "util.h"

/*------------------------------ WELD OBJECT DATA --------------------------*/

SINT32 MaximumForce;

UINT32 VerifyPresetModel4(void)
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
   UINT32 TempRetVal = FALSE;
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag = FALSE;
   SINT32 Stroke;

   RetVal = VerifyPresetModel3();
   if (CurrentSetup.Units == FALSE)
   { /*     this removes the tenths from the force */
      RunningPreset.TriggerForce /= 10; /*     in USCS only */
      RunningPreset.TriggerForce *= 10;
   }
   Stroke = GetMaxStrokeLength();
   TempRetVal = CheckForValidDistances(Stroke);
   if (TempRetVal == FALSE)
   {
      RecordErrorCode(ERRORCODE5_SE268);
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }

   MaximumForce = GetMaxForce();
   TempRetVal = CheckForValidForces(MaximumForce);
   if (TempRetVal == FALSE)
   {
      RecordErrorCode(ERRORCODE6_SE268);
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }

   /*--------------------------------------------------------------------------*/
   /*----    Here check for things which are mode specific                 ----*/
   /*--------------------------------------------------------------------------*/

   /*----   Make sure step values are less then control values   ----*/

   switch (RunningPreset.WeldMode)
   {
   default:
   case TIMEMODE:
      /*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.ColCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist))
      {
         RetVal = SE41;
         RecordSetupAlarm(RetVal);
      }
      break;

   case ENERGYMODE:
      /*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.ColCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist))
      {
         RetVal = SE41;
         RecordSetupAlarm(RetVal);
      }
      break;

   case PKPOWERMODE:
      /*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.ColCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist))
      {
         RetVal = SE41;
         RecordSetupAlarm(RetVal);
      }
      break;

   case ABSOLUTEMODE:
      /*----   Check absolute distance against maximum stroke length    ----*/

      if (((CurrentSetup.Actuator == AED) ||
	  	  (CurrentSetup.Actuator == AES) ||
		  (CurrentSetup.Actuator == MICROC) ||
		  (CurrentSetup.Actuator == MICRO))
            && (RunningPreset.AbsDist > Stroke))
      {
         RecordErrorCode(ERRORCODE5_SE268);
         RetVal = SE268;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check pretrigger distance with absolute distance    ----*/

      if ((RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.PreTriggerDistance >= RunningPreset.AbsDist))
      {
         RetVal = SE137;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check absolute distance with missing part min distance    ----*/

      if ((RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.AbsDist))
      {
         RetVal = SE168;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check absolute distance with missing part max distance    ----*/
      //  Removed during mh testing for version 9
      //         if ( (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
      //            (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      //            (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
      //            ((CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == AED)||
      //        (CurrentSetup.Actuator == AES)) &&
      //            (RunningPreset.MissingPartMax >= RunningPreset.AbsDist) )
      //         {
      //            RetVal = SE169;
      //            RecordSetupAlarm(RetVal);
      //         }

      /*----   Cross check amplitude stepping with abs distance  ----*/
      //AmpStepAtDist must be renamed    to AmpStepAtAbs
      //AmpTrigDistValue must be renamed    AmpTrigAbsValue

      //             if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
      //                    ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
      //                     (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsDist) ) {
      //                   RetVal = SE47;
      //                   RecordSetupAlarm(RetVal);
      //             }

      /*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.ColCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist))
      {
         RetVal = SE41;
         RecordSetupAlarm(RetVal);
      }

      /*---    Cross check amplitude step on power with peak power cutoff   ---*/
      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtPower.BitMask*/BIT4) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff))
      {
         RetVal = SE40;
         RecordSetupAlarm(RetVal);
      }
      break;

   case GRDDETECTMODE:
      /*---    Cross check amplitude step on power with peak power cutoff   ---*/
      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtPower.BitMask*/BIT4) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff))
      {
         RetVal = SE40;
         RecordSetupAlarm(RetVal);
      }

      /*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.ColCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist))
      {
         RetVal = SE41;
         RecordSetupAlarm(RetVal);
      }
      break;

   case COLLAPSEMODE:
      /*----   Cross check amplitude stepping with collapse distance  ----*/
      //AmpStepAtDist must be renamed    to AmpStepAtCol
      //AmpTrigDistValue must be renamed    AmpTrigColValue

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtDist.BitMask*/BIT5) == 0)
            && (RunningPreset.AmpTrigColValue >= RunningPreset.ColDist))
      {
         RetVal = SE42;
         RecordSetupAlarm(RetVal);
      }

      /*---    Cross check amplitude step on power with peak power cutoff   ---*/
      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtPower.BitMask*/BIT4) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff))
      {
         RetVal = SE40;
         RecordSetupAlarm(RetVal);
      }
      break;

   case CONTINUOUSMODE:
      /*---    Cross check amplitude step on power with peak power cutoff   ---*/
      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) && ((RunningPreset.Amp2Flag
            & /*AmpStepAtPower.BitMask*/BIT4) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff))
      {
         RetVal = SE40;
         RecordSetupAlarm(RetVal);
      }
      break;
   }

   /*--------------------------------------------------------------------------*/
   /*---  Here check for things which are not mode specific or not related  ---*/
   /*---  to either suspect or reject limits.                               ---*/
   /*--------------------------------------------------------------------------*/

   /*----   Check pretrigger distance with absolute cutoff distance    ----*/

   if ((RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
   ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE
         | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode)
         && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.PreTriggerDistance >= RunningPreset.ABSCutoffDist))
   {
      RetVal = SE136;
      RecordSetupAlarm(RetVal);
   }

   /*----   Check absolute distance cutoff with missing part min distance    ----*/

   if ((RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
   ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE
         | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode)
         && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
			  && (RunningPreset.MissingPartMin >= RunningPreset.ABSCutoffDist))
   {
      RetVal = SE166;
      RecordSetupAlarm(RetVal);
   }

   /*----  Check missing part max distance with missing part min distance  ----*/

   if ((RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
   ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.MissingPartMin >= RunningPreset.MissingPartMax))
   {
      RetVal = SE120;
      RecordSetupAlarm(RetVal);
   }

   /*----   Check absolute distance cutoff with missing part max distance    ----*/

   if ((RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
   ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE
         | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode)
         && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.MissingPartMax >= RunningPreset.ABSCutoffDist))
   {
      RetVal = SE167;
      RecordSetupAlarm(RetVal);
   }

   /*--------------------------------------------------------------------------*/
   /*--  Here are tests which are only valid when Suspect Limits are enabled --*/
   /*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
         && (RunningPreset.WeldMode != CONTINUOUSMODE))
   {
      SuspectFlag = TRUE;
      /*- Check minus suspect trigger distance with minus suspect absolute distance -*/
      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.SuspectLimits  & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistMLS >= RunningPreset.AbsMLS))
      {
         RetVal = SE54;
         RecordSetupAlarm(RetVal);
      }

      /*- Check plus suspect trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.TrsDistPLS >= RunningPreset.AbsPLS))
      {
         RetVal = SE55;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus suspect trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0)
            && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLS >= RunningPreset.AbsPLS))
      {
         RetVal = SE271;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus suspect trigger distance with absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
			&& (RunningPreset.TrsDistMLS >= RunningPreset.AbsDist))
      {
         RetVal = SE275;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check absolute distance cutoff with minus suspect trigger distance limit --*/

      if (((RunningPreset.SuspectLimits
            & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistMLS))
      {
         RetVal = SE141;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check absolute distance cutoff with plus suspect absolute distance limit --*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT)== 0) && 
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
       (RunningPreset.ABSCutoffDist <= RunningPreset.AbsPLS))
      {
         RetVal = SE144;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check absolute distance cutoff with plus suspect trigger distance limit --*/

      if (((RunningPreset.SuspectLimits
            & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistPLS))
      {
         RetVal = SE145;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check absolute distance cutoff with minus suspect absolute distance limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT)== 0) &&
         (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
         ((CurrentSetup.Actuator == AED) || 
         (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
          (RunningPreset.AbsMLS >= RunningPreset.ABSCutoffDist))
      {
         RetVal = SE140;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus suspect absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.AbsMLS))
      {
         RetVal = SE129;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.AbsPLS))
      {
         RetVal = SE131;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
         (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.PreTriggerDistance >= RunningPreset.TrsDistPLS))
      {
         RetVal = SE133;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus suspect trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.TrsDistMLS))
      {
         RetVal = SE135;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus Suspect absolute limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT)
            == 0) && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.AbsMLS))
      {
         RetVal = SE150;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus Suspect trigger limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits
            & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.TrsDistMLS))
      {
         RetVal = SE152;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus Suspect trigger limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits
            & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax <= RunningPreset.TrsDistMLS))
      {
         RetVal = SE151;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect absolute limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT)
            == 0) && (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.MissingPartMin >= RunningPreset.AbsPLS))
      {
         RetVal = SE163;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect absolute limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT)
            == 0) && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax <= RunningPreset.AbsPLS))
      {
         RetVal = SE162;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect trigger limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits
            & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO))
            && (RunningPreset.MissingPartMin >= RunningPreset.TrsDistPLS))
      {
         RetVal = SE165;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus suspect trigger limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits
            & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax <= RunningPreset.TrsDistPLS))
      {
         RetVal = SE164;
         RecordSetupAlarm(RetVal);
      }

      /*--  Check amplitude step at absolute distance with plus suspect limit  --*/
      //AmpStepAtDist must be renamed    to AmpStepAtAbs
      //AmpTrigDistValue must be renamed    AmpTrigAbsValue

      //      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
      //          ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
      //           (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsPLS) ) {
      //         RetVal = SE21;
      //         RecordSetupAlarm(RetVal);
      //      }


      /*----   Check plus suspect max force with minus suspect max force   ----*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0)
        	&& ((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0)
            && (RunningPreset.WeldForcePLS <= RunningPreset.WeldForceMLS))
         {
            RetVal = SE14;
            RecordSetupAlarm(RetVal);
         }
      }

      /*----   Check trigger force with plus suspect max force   ----*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.SuspectLimits
               & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0)
               && (RunningPreset.TriggerForce >= RunningPreset.WeldForcePLS))
         {
            RetVal = SE251;
            RecordSetupAlarm(RetVal);
         }
      }

   }

   /*--------------------------------------------------------------------------*/
   /*--  Here are tests which are only valid when Reject Limits are enabled  --*/
   /*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
         && (RunningPreset.WeldMode != CONTINUOUSMODE))
   {

      RejectFlag = TRUE;

      /*- Check minus reject trigger distance with minus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistMLR >= RunningPreset.AbsMLR))
      {
         RetVal = SE56;
         RecordSetupAlarm(RetVal);
      }

      /*- Check plus reject trigger distance with plus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistPLR >= RunningPreset.AbsPLR))
      {
         RetVal = SE57;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus reject trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0)
            && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLR >= RunningPreset.AbsPLR))
      {
         RetVal = SE274;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus reject trigger distance with absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLR >= RunningPreset.AbsDist))
      {
         RetVal = SE276;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check absolute distance cutoff with plus reject absolute distance limit --*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) && 
         (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.ABSCutoffDist <= RunningPreset.AbsPLR))
      {
         RetVal = SE142;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check absolute distance cutoff with plus reject trigger distance limit --*/

      if (((RunningPreset.RejectLimits
            & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistPLR))
      {
         RetVal = SE143;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check absolute distance cutoff with minus reject absolute distance limit  ---*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.AbsMLR >= RunningPreset.ABSCutoffDist))
      {
         RetVal = SE138;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check absolute distance cutoff with minus reject trigger limit  ---*/

      if (((RunningPreset.RejectLimits
            & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.ABSCutoffFlag
            == FALSE) && /*FALSE=On*/
      (RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistMLR))
      {
         RetVal = SE139;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus reject absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.AbsMLR))
      {
         RetVal = SE123;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.AbsPLR))
      {
         RetVal = SE130;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.TrsDistPLR))
      {
         RetVal = SE132;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus reject trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
    	 (RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.PreTriggerDistance >= RunningPreset.TrsDistMLR))
      {
         RetVal = SE134;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus reject absolute limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT)
            == 0) && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.AbsMLR))
      {
         RetVal = SE147;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus reject absolute limit with missing part max distance    ----*/

      //  This alarm removed on 09-03-98 by agreement with Bob Jalbert and
      //  Kevin Klein after reviewing DCS issue # 2837.

      //      if (((RunningPreset.RejectLimits & MAbsDistRLimit.BitMask) == 0) &&
      //          ((MAbsDistRLimit.mode & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      //           (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
      //           (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      //           (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
      //          ((CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == AED)||
      //      (CurrentSetup.Actuator == AES)) &&
      //              (RunningPreset.MissingPartMax <= RunningPreset.AbsMLR) ) {
      //            RetVal = SE146;
      //           RecordSetupAlarm(RetVal);
      //      }

      /*----   Check minus reject trigger limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits
            & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.TrsDistMLR))
      {
         RetVal = SE149;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check minus reject trigger limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits
            & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax <= RunningPreset.TrsDistMLR))
      {
         RetVal = SE148;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject absolute limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT)
            == 0) && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.AbsPLR))
      {
         RetVal = SE154;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject absolute limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT)
            == 0) && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax >= RunningPreset.AbsPLR))
      {
         RetVal = SE153;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject trigger limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits
            & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMin >= RunningPreset.TrsDistPLR))
      {
         RetVal = SE161;
         RecordSetupAlarm(RetVal);
      }

      /*----   Check plus reject trigger limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits
            & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0)
            && (RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
      ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.MissingPartMax <= RunningPreset.TrsDistPLR))
      {
         RetVal = SE155;
         RecordSetupAlarm(RetVal);
      }

      /*--  Check amplitude step at absolute distance with plus reject limit  --*/
      //AmpStepAtDist must be renamed    to AmpStepAtAbs
      //AmpTrigDistValue must be renamed    AmpTrigAbsValue

      //      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
      //          ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
      //           (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsPLR) ) {
      //         RetVal = SE20;
      //         RecordSetupAlarm(RetVal);
      //      }


      /*----   Check plus reject max force with minus reject max force    ----*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {

         if (((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0)
               && ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0)
               && (RunningPreset.WeldForcePLR <= RunningPreset.WeldForceMLR))
         {
            RetVal = SE13;
            RecordSetupAlarm(RetVal);
         }
      }

      /*----   Check trigger force with plus reject max force   ----*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.RejectLimits
               & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0)
               && (RunningPreset.TriggerForce >= RunningPreset.WeldForcePLR))
         {
            RetVal = SE257;
            RecordSetupAlarm(RetVal);
         }
      }

   }

   /*--------------------------------------------------------------------------*/
   /*----  Here are tests for when BOTH reject and suspect limits are on.  ----*/
   /*--------------------------------------------------------------------------*/

   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE))
   {

      /*---  Check plus reject absolute limit with minus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) && 
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsMLS))
      {
         RetVal = SE86;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus suspect absolute limit with minus reject absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) && 
         ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) && 
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.AbsPLS <= RunningPreset.AbsMLR))
      {
         RetVal = SE87;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus reject absolute limit with plus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) && 
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) && 
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsPLS))
      {
         RetVal = SE88;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check minus reject absolute limit with minus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) && 
         ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&  
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.AbsMLR >= RunningPreset.AbsMLS))
      {
         RetVal = SE89;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus reject collapse limit with minus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.ColPLR <= RunningPreset.ColMLS))
      {
         RetVal = SE90;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus suspect collapse limit with minus reject collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits  & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.ColPLS <= RunningPreset.ColMLR))
      {
         RetVal = SE91;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus reject collapse limit with plus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.ColPLR <= RunningPreset.ColPLS))
      {
         RetVal = SE97;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check minus reject collapse limit with minus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.ColMLR >= RunningPreset.ColMLS))
      {
         RetVal = SE98;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus reject trigger limit with minus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistMLS))
      {
         RetVal = SE107;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus suspect trigger limit with minus reject trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistPLS <= RunningPreset.TrsDistMLR))
      {
         RetVal = SE108;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check plus reject trigger limit with plus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistPLS))
      {
         RetVal = SE109;
         RecordSetupAlarm(RetVal);
      }

      /*---  Check minus reject trigger limit with minus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.TrsDistMLS))
      {
         RetVal = SE110;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus suspect trigger distance with plus reject absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) && 
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) && 
         ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.TrsDistMLS >= RunningPreset.AbsPLR))
      {
         RetVal = SE272;
         RecordSetupAlarm(RetVal);
      }

      /*- Check minus reject trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0)
            && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLR >= RunningPreset.AbsPLS))
      {
         RetVal = SE273;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check plus reject max force limit with minus suspect max force limit --*/

      if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.WeldForcePLR <= RunningPreset.WeldForceMLS))
      {
         RetVal = SE99;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check plus suspect max force limit with minus reject max force limit --*/

      if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.WeldForcePLS <= RunningPreset.WeldForceMLR))
      {
         RetVal = SE100;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check plus reject max force limit with plus suspect max force limit  --*/

      if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.WeldForcePLR <= RunningPreset.WeldForcePLS))
      {
         RetVal = SE101;
         RecordSetupAlarm(RetVal);
      }

      /*-- Check minus reject max force limit with minus suspect max force limit -*/

      if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
    	 ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
    	 ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) &&
    	 (RunningPreset.WeldForceMLR >= RunningPreset.WeldForceMLS))
      {
         RetVal = SE102;
         RecordSetupAlarm(RetVal);
      }
   }

   /*--------------------------------------------------------------------------*/
   /*----    Finally check for things which are only allowed in            ----*/
   /*----    control level 5 or above.                                     ----*/
   /*--------------------------------------------------------------------------*/

   /*---  Check for Pressure stepping  ---*/

   if (CurrentSetup.ControlLevel < LEVEL_c) {
      if ((RunningPreset.Pressure2Flag & BIT0) == BIT0) {
         RecordErrorCode(ERRORCODE3_SE268);
         RetVal = SE268;
         RecordSetupAlarm(RetVal);
      }
   }

   return (RetVal);
}

BOOLEAN CheckForValidDistances(SINT32 MaxStroke)
/*--------------------------------------------------------------------------*/
/*  This function will check all distances against the stroke length which  */
/*  has been selected for this machine as defined by the passed argument.   */
/*  If any problems are found, a FALSE will be returned.  If all is okay    */
/*  then TRUE will be returned.                                             */
/*--------------------------------------------------------------------------*/
{
   BOOLEAN RetVal = TRUE;

   /*----------  First check things which are Suspect limits  ----------*/

   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
   {

      /*- Check minus suspect trigger distance -*/

      if (((RunningPreset.SuspectLimits
            & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE
                  | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)
                  & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLS > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check plus suspect trigger distance -*/

      if (((RunningPreset.SuspectLimits
            & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0)
            && ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE
                  | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)
                  & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistPLS > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check minus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT)
            == 0) && ((/*AbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE
            | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE)
            & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.AbsMLS
            > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT)
            == 0) && ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE
            | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE)
            & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.AbsPLS
            > MaxStroke))
      {
         RetVal = FALSE;
      }

   }

   /*----------  Next check things which are Reject limits  ----------*/

   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
   {

      /*- Check minus reject trigger distance -*/

      if (((RunningPreset.RejectLimits
            & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0)
            && ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE
                  | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)
                  & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistMLR > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check plus reject trigger distance -*/

      if (((RunningPreset.RejectLimits
            & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0)
            && ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE
                  | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)
                  & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
            && (RunningPreset.TrsDistPLR > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check minus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT)
            == 0) && ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE
            | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE)
            & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.AbsMLR
            > MaxStroke))
      {
         RetVal = FALSE;
      }

      /*- Check plus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT)
            == 0) && ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE
            | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE)
            & RunningPreset.WeldMode) == RunningPreset.WeldMode)
            && ((CurrentSetup.Actuator == AED)
                  || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.AbsPLR
            > MaxStroke))
      {
         RetVal = FALSE;
      }
   }

   /*- Check step @ distance  (for release 3.0) -*/

   /*- Check actuator clear distance -*/

   if (((RunningPreset.ActClrFlag & BIT0) == BIT0)
         && ((/*OutputAtPosSw.mode*/ALLMODES & RunningPreset.WeldMode)
               == RunningPreset.WeldMode) && ((CurrentSetup.Actuator == AED)
         || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) && (RunningPreset.ActClrDistance
         > MaxStroke))
   {
      RetVal = FALSE;
   }

   /*- Check missing part minimum distance -*/

   if ((RunningPreset.MissingMinFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
   ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.MissingPartMin > MaxStroke))
   {
      RetVal = FALSE;
   }

   /*- Check missing part maximum distance -*/

   if ((RunningPreset.MissingMaxFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.MissingPartFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.CycleAbortFlag == TRUE) && /*TRUE =On*/
   ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.MissingPartMax > MaxStroke))
   {
      RetVal = FALSE;
   }

   /*- Check absolute cutoff distance -*/

   if ((RunningPreset.ControlLimitsFlag == TRUE) && /*TRUE =On*/
   (RunningPreset.ABSCutoffFlag == FALSE) && /*FALSE=On*/
   ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE
         | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode)
         && ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.ABSCutoffDist > MaxStroke))
   {
      RetVal = FALSE;
   }

   /*- Check pre-trigger distance -*/

   if ((RunningPreset.PreTriggerDistanceFlag == FALSE) && /*FALSE=On*/
   (RunningPreset.PreTrigFlag == TRUE) && /*TRUE =On*/
   ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         && (RunningPreset.PreTriggerDistance > MaxStroke))
   {
      RetVal = FALSE;
   }

   return (RetVal);
}

BOOLEAN CheckForValidForces(UINT32 MaximumForce)
/*--------------------------------------------------------------------------*/
/*  This function will check all force values against the maximum force     */
/*  which has been selected for this machine as defined by the passed arg.  */
/*  If any problems are found, a FALSE will be returned.  If all is okay    */
/*  then TRUE will be returned.                                             */
/*--------------------------------------------------------------------------*/
{
   BOOLEAN RetVal = TRUE;

   /*----------  First check things which are Suspect limits  ----------*/

   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0)
   {

      /*- Check minus suspect weld force -*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.SuspectLimits
               & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0)
               && (RunningPreset.WeldForceMLS > (SINT32)MaximumForce))
         {
            RetVal = FALSE;
         }
      }

      /*- Check plus suspect weld force -*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.SuspectLimits
               & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0)
               && (RunningPreset.WeldForcePLS > (SINT32)MaximumForce))
         {
            RetVal = FALSE;
         }
      }
   }

   /*----------  Next check things which are reject limits  ----------*/

   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0)
   {

      /*- Check minus reject weld force -*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.RejectLimits
               & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0)
               && (RunningPreset.WeldForceMLR > (SINT32)MaximumForce))
         {
            RetVal = FALSE;
         }
      }

      /*- Check plus reject weld force -*/

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         if (((RunningPreset.RejectLimits
               & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0)
               && (RunningPreset.WeldForcePLR > (SINT32)MaximumForce))
         {
            RetVal = FALSE;
         }
      }
   }

   /*-  Check trigger force  -*/

   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
      if (RunningPreset.TriggerForce > (SINT32)MaximumForce)
      {
         RetVal = FALSE;
      }
   }
   return (RetVal);
}
