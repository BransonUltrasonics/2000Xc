/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET2.cpp_v   1.12   02 Jan 2015 04:11:44   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET2.cpp_v  $
 * 
 *    Rev 1.12   02 Jan 2015 04:11:44   rjamloki
 * VerifyPresetModel2() function changed for timeout conflict alarm
 * 
 *    Rev 1.11   03 Oct 2014 06:14:54   rjamloki
 *  VerifyPresetModel2() function changed
 * 
 *    Rev 1.10   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.9   28 Jul 2014 12:36:46   rjamloki
 * psos.h removed
 * 
 *    Rev 1.8   15 Jul 2014 16:57:52   hasanchez
 * Changes related to Absolute limits (Reject and Suspect).
 * 
 *    Rev 1.7   11 Jun 2014 12:38:02   rjamloki
 * psos include fix
 * 
 *    Rev 1.6   21 May 2014 10:48:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:55:14   rjamloki
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

   Module name:   VERIFY_PRESET_MODEL2  

   Filename:      vpreset2.c     

   Function Name: VerifyPresetModel2
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"             
 ----------------------------- DESCRIPTION -------------------------------*/

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


UINT32 VerifyPresetModel2(void)
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
   UINT32 RetVal      = FALSE;
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag  = FALSE;

   RetVal = VerifyPresetModel1();

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:

/*--  Check energy compensation minimum with energy compensation maximum  --*/

         if ((RunningPreset.EnergyCompFlag == TRUE) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.EnergyPL <= RunningPreset.EnergyML) )
         {
            RetVal = SE119;
            RecordSetupAlarm(RetVal);
         }
         break;

      case ENERGYMODE:
         break;

      case PKPOWERMODE:
         break;

      case ABSOLUTEMODE:
         break;

      case GRDDETECTMODE:
         break;

      case COLLAPSEMODE:
         break;

      case CONTINUOUSMODE:
         break;

      default:
         break;
   }

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Suspect Limits are enabled --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.WeldMode != CONTINUOUSMODE))
   {
      SuspectFlag = TRUE;

/*----   Check Suspect Limit    TIME   ----*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLS <= RunningPreset.TimeMLS) )
      {
         RetVal = SE1;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with minus suspect time limit   ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.TimeMLS >= RunningPreset.MaxTimeout) && (RunningPreset.WeldMode!= TIMEMODE) )
      {
         RetVal = SE50;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with plus suspect time limit   ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLS >= RunningPreset.MaxTimeout) && (RunningPreset.WeldMode!= TIMEMODE) )
      {
         RetVal = SE58;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   ENERGY  ----*/

      if (((RunningPreset.SuspectLimits &/*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
    	 ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
    	 (RunningPreset.EnergyPLS <= RunningPreset.EnergyMLS))
      {
         RetVal = SE3;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   PEAK POWER    ----*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.PowerPLS <= RunningPreset.PowerMLS) )
      {
         RetVal = SE5;
         RecordSetupAlarm(RetVal);
      }

/*----   Check peak power cutoff with minus Suspect power Limit   ----*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerMLS >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE66;
         RecordSetupAlarm(RetVal);
      }

/*----   Check peak power cutoff with plus Suspect power Limit   ----*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
          (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
          (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
          (RunningPreset.PowerPLS >= RunningPreset.PeakPwrCutoff) )
      {
          RetVal = SE67;
          RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   COLLAPSE DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
         (RunningPreset.ColPLS <= RunningPreset.ColMLS) )
      {
         RetVal = SE12;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   ABSOLUTE DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         (RunningPreset.AbsPLS <= RunningPreset.AbsMLS) )
      {
         RetVal = SE10;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   TRIGGER DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         (RunningPreset.TrsDistPLS <= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE45;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLS <= RunningPreset.EnergyML) )
      {
         RetVal = SE171;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus suspect energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLS <= RunningPreset.EnergyML) )
      {
         RetVal = SE265;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus suspect energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLS >= RunningPreset.EnergyPL) )
      {
         RetVal = SE173;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLS >= RunningPreset.EnergyPL) )
      {
         RetVal = SE267;
         RecordSetupAlarm(RetVal);
      }
   }


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Reject Limits are enabled  --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.WeldMode != CONTINUOUSMODE))
   {
      RejectFlag = TRUE;

/*----   Check Reject Limit    TIME   ----*/

      if (((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLR <= RunningPreset.TimeMLR) )
      {
         RetVal = SE2;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with plus reject time limit   ---*/

      if (((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLR >= RunningPreset.MaxTimeout) && (RunningPreset.WeldMode!= TIMEMODE) )
      {
         RetVal = SE49;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with minus reject time limit   ---*/

      if (((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.TimeMLR >= RunningPreset.MaxTimeout) && (RunningPreset.WeldMode!= TIMEMODE) )
      {
         RetVal = SE51;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   ENERGY  ----*/

      if (((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyMLR) )
      {
         RetVal = SE4;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   PEAK POWER    ----*/

      if (((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerMLR) )
      {
         RetVal = SE6;
         RecordSetupAlarm(RetVal);
      }

/*---   Check peak power cutoff with minus reject power limit   ---*/

      if (((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerMLR >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE59;
         RecordSetupAlarm(RetVal);
      }

/*---   Check peak power cutoff with plus reject power limit   ---*/

      if (((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerPLR >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE65;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   COLLAPSE DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
         (RunningPreset.ColPLR <= RunningPreset.ColMLR) )
      {
         RetVal = SE11;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   ABSOLUTE DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsMLR) )
      {
         RetVal = SE9;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   TRIGGER DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE44;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyML) )
      {
         RetVal = SE170;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLR <= RunningPreset.EnergyML) )
      {
         RetVal = SE264;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLR >= RunningPreset.EnergyPL) )
      {
         RetVal = SE172;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR >= RunningPreset.EnergyPL) )
      {
         RetVal = SE266;
         RecordSetupAlarm(RetVal);
      }
   }


/*---  Here are tests for when BOTH reject and suspect limits are on  ---*/
      
   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE))
   {

/*---  Check plus reject time limit with minus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLR <= RunningPreset.TimeMLS) )
      {
         RetVal = SE74;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect time limit with minus reject time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.TimePLS <= RunningPreset.TimeMLR) )
      {
         RetVal = SE75;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject time limit with plus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.TimePLR <= RunningPreset.TimePLS) )
      {
         RetVal = SE76;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject time limit with minus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.TimeMLR >= RunningPreset.TimeMLS) )
      {
         RetVal = SE77;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with minus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyMLS) )
      {
         RetVal = SE78;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with minus reject energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLS <= RunningPreset.EnergyMLR) )
      {
         RetVal = SE79;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with plus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyPLS) )
      {
         RetVal = SE80;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with minus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits &/*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLR >= RunningPreset.EnergyMLS) )
      {
         RetVal = SE81;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject peak power limit with minus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerMLS) )
      {
         RetVal = SE82;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect peak power limit with minus reject peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         (RunningPreset.PowerPLS <= RunningPreset.PowerMLR) )
      {
         RetVal = SE84;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject peak power limit with plus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerPLS) )
      {
         RetVal = SE83;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject peak power limit with minus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         (RunningPreset.PowerMLR >= RunningPreset.PowerMLS) )
      {
         RetVal = SE85;
         RecordSetupAlarm(RetVal);
      }
   }

/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 3 or above.                                     ----*/
/*--------------------------------------------------------------------------*/


/*---  Check for amplitude stepping  ---*/

   if (CurrentSetup.ControlLevel < LEVEL_ea)
   {
      if ((RunningPreset.Amp2Flag & BIT0) == BIT0)
      {
         RecordErrorCode( ERRORCODE2_SE268 );
         RetVal = SE268;
         RecordSetupAlarm(RetVal);
      }
   }
   return(RetVal);
}



