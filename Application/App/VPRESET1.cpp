/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET1.cpp_v   1.26   Nov 17 2017 17:04:28   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/VPRESET1.cpp_v  $
 * 
 *    Rev 1.26   Nov 17 2017 17:04:28   RJamloki
 * Fix step pressure alarm issue when activating that option
 * 
 *    Rev 1.25   Nov 06 2017 16:53:38   RJamloki
 * Hard code numbers and default settings
 * 
 *    Rev 1.24   Oct 10 2017 15:06:20   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.23   08 Apr 2015 13:47:32   AnPawar
 *  CheckForStepping() function now check Pressure Stepping.
 * 
 *    Rev 1.22   08 Jan 2015 03:18:30   AnPawar
 * printf removed
 * 
 *    Rev 1.21   11 Dec 2014 08:38:00   AnPawar
 * batch complete will affect validated preset 
 * 
 *    Rev 1.20   28 Nov 2014 07:42:20   rjamloki
 * VerifyPreset() CHANGED.
 * 
 *    Rev 1.19   11 Nov 2014 06:11:00   AnPawar
 * checking batch count enabled before raising batch count setup alarm
 * 
 *    Rev 1.18   20 Oct 2014 06:32:54   AnPawar
 * removed VQS limit check from VerifyPreset().
 * 
 *    Rev 1.17   06 Oct 2014 06:48:10   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.16   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.15   26 Sep 2014 03:11:10   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.14   05 Sep 2014 05:26:44   rjamloki
 * Added UpdateOnBatchCountChange flag to not write whole preset every time the batch count changes
 * 
 *    Rev 1.13   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.12   28 Jul 2014 12:36:46   rjamloki
 * psos.h removed
 * 
 *    Rev 1.11   09 Jul 2014 13:44:54   rjamloki
 * Added Batch Count Setup Alarm.
 * 
 *    Rev 1.10   11 Jun 2014 12:37:06   rjamloki
 * psos include fix
 * 
 *    Rev 1.9   21 May 2014 10:48:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:55:10   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   26 Mar 2014 12:40:28   rjamloki
 * removed macro and printf enabled.
 * 
 *    Rev 1.6   06 Mar 2014 11:04:02   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:48   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:58   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:56   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name:   VERIFY_PRESET_MODEL1  

   Filename:      vpreset1.c     

   Function Name: VerifyPresetModel1
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"
 ----------------------------- DESCRIPTION -------------------------------*/


/* ------------------------------ INCLUDE FILES ----------------------------*/

#include "qdef.h"
#include "portable.h"

#include "preset.h"
#include "param.h"
#include "limits.h"
#include "names.h"
#include "alarms.h"
#include "ready.h"
#include "weld_obj.h"
#include "wldstate.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"
#include "alsetup.h"
#include "graphs.h"
#include "statedrv.h"
#include "battram.h"
#include "menu3.h"
#include "menu.h"
#include "DUPS_api.h"
#include "menu7.h"
#include "menu7a.h"
#include "inports.h"
#include "outports.h"
#include "stdio.h"
#include "SystemManagerTask.h"

/*------------------------------ WELD OBJECT DATA --------------------------*/

#define POWERMULTIPLIER        10 /* Multiply to get .1 resolution          */
#define POWERROUNDOFF           5 /* Subtract 1/2 of multiply to round off  */   
#define INPUT_COUNT             7

#define WELDMODES_1  (TIMEMODE | GRDDETECTMODE | CONTINUOUSMODE)
#define WELDMODES_2  (WELDMODES_1 | ENERGYMODE | PKPOWERMODE)
#define WELDMODES_3  (WELDMODES_2 | COLLAPSEMODE | ABSOLUTEMODE)
#define WELDMODES_4  (WELDMODES_3)
#define WELDMODES_5  (WELDMODES_4)
#define WELDMODES_6  (WELDMODES_5)
#define WELDMODES_7  (WELDMODES_6)

static UINT16 ControlLevelMask;
SETUP_DATA_ALARMS *SetupDataPtr;
static START_WELD_MSG    StartWeldMsg;

extern UINT16 SetupAlarmFlag;
extern BOOLEAN UlsTimeout;
extern BOOLEAN PartClampActive;

UINT16 PresetHasBeenOKed;
UINT16 VerifyPresetInProcess;
BOOLEAN UpdateOnBatchCountChange = FALSE;//Flag to check that Only good reason to verify the preset is that
										//the batch count is enabled and may exceed the set limit in next
										//weld cycle.

/*------------------------- EXTERNAL FUNCTIONS -----------------------------*/

UINT32 GetCurrentHwCnfg (void);
UINT16 CheckUserIOAlarm (void);

UINT32 VerifyPreset(void)
/***************************************************************************/
/*                                                                         */
/*  This function will determine what control level is currently configured*/
/*  and will then call the proper VerifyPresetModel function.              */
/*                                                                         */
/*  The value returned will be FALSE if the preset is okay and can be run. */
/*  An error code will be returned if any problems are found.  The         */
/*  problems will be logged in PresetProblems array.  See Problems enum    */
/*  for list.                                                              */
/*                                                                         */
/***************************************************************************/
{
   UINT32 Retval = FALSE;
   UINT32 TempRetval;
   UINT16 PresetFailed = FALSE;        /* Start off assuming preset is okay */
   
   SETUPS_Ver1200 * PresetPtr;
// UINT16 TempVerified;

   VerifyPresetInProcess = TRUE;
   ClearSetupAlarms();

/* Here check for things which are not actuator or control level dependent */

   if (CheckForDups())
      {

         if (DUPSChangePending == TRUE) {
            DUPS_DownloadCurrPS();
            DUPSChangePending = FALSE;
      }
   }

   switch (CurrentSetup.ControlLevel) {
        case LEVEL_a:
         ControlLevelMask = WELDMODES_3;
         TempRetval = VerifyPresetModel3();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AES) ||
			  (CurrentSetup.Actuator == MICROC) ||
			  (CurrentSetup.Actuator == MICRO)) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_TEST:
      case LEVEL_f:
         ControlLevelMask = WELDMODES_5;
         TempRetval = VerifyPresetModel5();        
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         break;

      case LEVEL_d:
	  case LEVEL_c:
         ControlLevelMask = WELDMODES_4;
         TempRetval = VerifyPresetModel5();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         break;

      case LEVEL_ea:
         ControlLevelMask = WELDMODES_3;
         TempRetval = VerifyPresetModel3();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AES) ||
			  (CurrentSetup.Actuator == MICROC) ||
			  (CurrentSetup.Actuator == MICRO)) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_e:
         ControlLevelMask = WELDMODES_2;
         TempRetval = VerifyPresetModel2();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AES) ||
			  (CurrentSetup.Actuator == MICROC) ||
			  (CurrentSetup.Actuator == MICRO)) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_t:
         ControlLevelMask = WELDMODES_1;
         TempRetval = VerifyPresetModel1();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode((ERRORCODE_ARG)TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AES) ||
			  (CurrentSetup.Actuator == MICROC) ||
			  (CurrentSetup.Actuator == MICRO)) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      default:
         ControlLevelMask = WELDMODES_1;
         TempRetval = VerifyPresetModel1();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         break;
   }

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
             break;

      case ENERGYMODE:
             break;

      case PKPOWERMODE:
             break;

      case COLLAPSEMODE:
             break;

      case ABSOLUTEMODE:
             break;

      case GRDDETECTMODE:
             break;

      case CONTINUOUSMODE:
             break;

      default:
             break;

   }

/*---  Make sure selected weld mode is valid for control level  ---*/

   if ((RunningPreset.WeldMode & ControlLevelMask) != RunningPreset.WeldMode) {
         RecordErrorCode( ERRORCODE4_SE268 );
         Retval = SE268;
      RecordSetupAlarm(Retval);
   }



/*--- Check for conflict of AE actuator and welding mode ---*/
   if((CurrentSetup.Actuator == AE) && (RunningPreset.WeldMode == COLLAPSEMODE || RunningPreset.WeldMode == ABSOLUTEMODE))
   {
      RecordErrorCode( ERRORCODE4_SE268 );
      Retval = SE268;
      RecordSetupAlarm(Retval);
   }






/*--  Further refine this mask by checking for optional encoder  --*/

   if(CurrentSetup.Actuator == AE) {
      if (CheckForDistanceParameters() == TRUE) {
         PresetFailed = TRUE;
         Retval = SE259;
         RecordSetupAlarm(Retval);
      }
   }
   /* Checks for the User Configurable input/output related alarms.*/
   if((TempRetval = CheckUserIOAlarm()) != 0)
   {
      Retval = TempRetval;
      PresetFailed = TRUE;
   }
   /*If both the Pretrigger and External trigger delay are 
      selected, record the 'TrgDelayConflct' alarm.*/
   if((RunningPreset.PreTrigFlag == TRUE) && (RunningPreset.ExtTrgDelay == TRUE))
   {
      Retval = SE289;
      RecordSetupAlarm(Retval);
      PresetFailed = TRUE;
   }
   
   if((CurrentSetup.ControlLevel >= LEVEL_ea) && ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
      (CurrentSetup.AmpControl == TRUE) && (RunningPreset.Amp2Flag == AMP_STEP_AT_EXTERNAL) &&
      !IsConfigured(INPUT_EXT_TRIGGER))
   {
      Retval = SE296;
      RecordSetupAlarm(Retval);
      PresetFailed = TRUE;
   }
   
	if(!((PresetFailed == FALSE) && (CurrentPreset.Verified == TRUE) && (UpdateOnBatchCountChange == TRUE)))
	 UpdateOnBatchCountChange = FALSE;

	BOOLEAN BatchInvalidate = TRUE;
	if((RunningPreset.BatchFunction == TRUE) && (RunningPreset.CurrBatchCount >= RunningPreset.BatchCount))
	{
	 Retval = SE300;
	 RecordSetupAlarm(Retval);
	 if(PresetFailed == FALSE)
		 BatchInvalidate = FALSE;
	 PresetFailed = TRUE;
	}

         
   if (PresetFailed == TRUE) {
      SendSetupData();           /* Notify display system of impending doom */
      PresetHasBeenOKed = FALSE;
      AlarmDetectedFlag = TRUE;
      CountSetupAlarms();
      if(BatchInvalidate) {
    	  CurrentPreset.Verified = FALSE;
		  RunningPreset.Verified = FALSE;
		  CurrentPreset.Validated = FALSE;
		  CurrentPreset.Locked = FALSE;
		  RunningPreset.Validated = FALSE;
      	  RunningPreset.Locked = FALSE;
      }
      UpdateOnBatchCountChange = FALSE;
   }
   else {
     /*------------------------------------------------------*
      * Calculate IncrementPts (WeldTime+HoldTime+200)/400.  *
      * or (WeldTime+HoldTime+TriggerDelay+200)/400.         *
      *------------------------------------------------------*/
      GetPtsIncrement();

/*---   Here we need to modify power readings   ---*/

//      RunningPreset.ForceTrigAmpValue *= POWERMULTIPLIER;
//      RunningPreset.ForceTrigAmpValue -= POWERROUNDOFF;
      PresetHasBeenOKed = TRUE;
      AlarmDetectedFlag = FALSE;
      SetupAlarmFlag = FALSE;
      PushIndex();
      SelectWeldSequence();                      /* Create new weld sequence*/
      PopIndex();
      CurrentPreset.Verified = TRUE;
      RunningPreset.Verified = TRUE;
   }

   CurrentPreset.HwCnfg = GetCurrentHwCnfg();
   RunningPreset.HwCnfg = CurrentPreset.HwCnfg;
   /*Store the verified result in preset 0*/
   PresetPtr  = (SETUPS_Ver1200*)CalculatePresetAddress(CURRENT_PRESET_INDEX);
   PresetPtr->Verified = CurrentPreset.Verified;
   PresetPtr->Validated = CurrentPreset.Validated;
   PresetPtr->Locked = CurrentPreset.Locked;
   FRAMPresetInfo[CURRENT_PRESET_INDEX].Verified = CurrentPreset.Verified;
   FRAMPresetInfo[CURRENT_PRESET_INDEX].Validated = CurrentPreset.Validated;
   FRAMPresetInfo[CURRENT_PRESET_INDEX].Locked = CurrentPreset.Locked;
   PresetPtr->HwCnfg = CurrentPreset.HwCnfg;
   if((CurrentPreset.PresetUpdateComplete == TRUE) && (UpdateOnBatchCountChange == FALSE))
      WritePreset(CurrentSetup.ActivePreset);  /* Save Current Preset */

/*---   Now check the condition of the battery backed ram (FRAM)   ---*/

  // FramIdPtr =(UINT16 *)BATTRAM_INIT_ADDRESS;
  // DefaultSet = *FramIdPtr;
  // if (DefaultSet != 0x5555) {
  //    CheckFramDefaults();
  //    RecordAlarm(EQ8);              /* Let user know FRAM was bad          */
  // }
  
   UlsTimeout = 0;               /* Reset ULS timer to start after verify   */
   VerifyPresetInProcess = FALSE;
   return(Retval);
}



UINT32 VerifyPresetModel1(void)
/****************************************************************************/
/*                                                                          */
/*  This function will verify the preset against itself and the system      */
/*  configuration.  It will check the following things:                     */
/*                                                                          */
/*    1) Only those things whic are unique to control model 1.              */
/*    2) After the preset is verified a state sequence will be generated    */
/*       to run the selected weld cycle.                                    */
/*                                                                          */
/*                                                                          */
/*  The value returned will be FALSE if the preset is okay and can be run.  */
/*  An error code will be returned if any problems are found.  The          */
/*  problems will be logged in PresetProblems array.  See Problems enum     */
/*  for list.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT32 RetVal = FALSE;

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/



/*---  Checking if the there is at least one item to print.         ---*/
/*---  If so, check if the printer is offline or disconnected.      ---*/
/*---  If the above is TRUE then clear the Record Alarm with reset. ---*/
//
//   if(PrintEveryCycleFlag){
//      if(PrintIsOffline){
//        RetVal = SE270;
//        RecordSetupAlarm(RetVal);
//      }
//   }




/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 2 or above.                                     ----*/
/*----                                                                  ----*/
/*----    Remember, this function is called by ALL VerifyPreset levels. ----*/
/*----                                                                  ----*/
/*----                                                                  ----*/
/*--------------------------------------------------------------------------*/

   return(RetVal);
}



UINT16 CheckForDistanceParameters(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check all distance parameters and if any distance    */
/*  parameters are turned on a TRUE will be returned, otherwise a FALSE     */
/*  will be reutrned.                                                       */
/*                                                                          */
/****************************************************************************/
{
   UINT16 RetVal = FALSE;              /* Assume no distance stuff is on    */

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
      case ENERGYMODE:
      case PKPOWERMODE:
      case GRDDETECTMODE:
      case CONTINUOUSMODE:
             break;

      case COLLAPSEMODE:
      case ABSOLUTEMODE:
               RetVal = TRUE;
             break;
   }

/*--  Check for absolute distance cutoff (FALSE means option is on) --*/

   if (RunningPreset.ABSCutoffFlag == FALSE) RetVal = TRUE;


/*--  Check for collapse distance cutoff (FALSE means option is on)--*/

   if (RunningPreset.ColCutoffFlag == FALSE) RetVal = TRUE;


/*--  Check for pre-trigger distance  (FALSE means option is on)--*/

   if (RunningPreset.PreTriggerDistanceFlag == FALSE) RetVal = TRUE;


/*--  Check for missing part distance (FALSE means option is off) --*/

   if (RunningPreset.MissingPartFlag == TRUE) RetVal = TRUE;


/*--  Check for actuator clear distance (FALSE means option is off) --*/

   if (RunningPreset.ActClrFlag == TRUE) RetVal = TRUE;


/*--  Check for rapid traverse distance (FALSE means option is off) --*/

   if (RunningPreset.RTFlag == TRUE) RetVal = TRUE;


/*--  Check for amplitude step on distance  --*/

   switch (RunningPreset.Amp2Flag) {
      case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
         break;                       
                                      
      case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
         break;                       
                                      
      case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
         break;                       
                                      
      case ((UINT16)~BIT5):                    /* Stepping enabled on absolute dist */
         RetVal = TRUE;               
         break;                       
                                      
      case ((UINT16)~BIT6):                    /* Stepping enabled on force         */
         break;                       
                                      
      case AMP_STEP_AT_EXTERNAL:                       /* Stepping enabled on external in   */
         break;

      default:
         break;
   }                                  
                                      

   return(RetVal);
}


/***************************************************************************
 *
 *   Purpose:
 *
 *   This function will check for any stepping which might be enabled.  It
 *   will then check the control level and actuator type to see if stepping
 *   is allowed.  It will return an ERRORCODE if either stepping is turn on
 *   but is not allowed and FALSE if stepping is off or is allowed if it is
 *   on.
 *
 *   Entry condition:
 *	void
 *
 *   Exit condition:
 *	UNIT32
 *
 ***************************************************************************/
UINT32 CheckForStepping(void)
{
   UINT16 Retval = FALSE;

   /**  First deal with amplitude stepping (its easier)  **/

   if ((RunningPreset.Amp2Flag & BIT0) == BIT0) { /* Amp stepping on ?   */
      switch (CurrentSetup.ControlLevel) { /* Yes it is           */
      case LEVEL_t:
      case LEVEL_e:
      case LEVEL_DEPOT:
         Retval = ERRORCODE2_SE268;
         break;
      default:
         break;
      }
   }

   /**  Now deal with Pressure stepping  **/


   if ((RunningPreset.Pressure2Flag & BIT0) == BIT0) { /* Pressure stepping on ? */
      switch (CurrentSetup.ControlLevel) {
      case LEVEL_c:
      case LEVEL_TEST:
         if (CurrentSetup.Actuator != AES && CurrentSetup.Actuator != MICROC) Retval = ERRORCODE3_SE268;
         break;/* Yes it is           */
      default:
         Retval = ERRORCODE3_SE268;
         break;
      }
   }

   return (Retval);
}



void SendSetupData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will put the results of the verify preset into a struc-  */
/*   ture and then send a pointer to that structure to the system manager.  */
/*                                                                          */
/****************************************************************************/
{
   SetupDataPtr = &SetupData;
   StartWeldMsg.common.opcode = OP_SETUP_ALARM_DATA;
   StartWeldMsg.common.source_task = WC_ISR_TASK;
   
   StartWeldMsg.setup_data_ptr =  SetupDataPtr; // It was &SetupDataPtr; 
   
   StartWeldMsg.weld_samples = 1;
   SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &StartWeldMsg), 20);
}

UINT32 GetCurrentHwCnfg(void)
/****************************************************************************/
/*                                                                          */
/*   This function will used to get the value of current hardware config.   */
/*   This returns the value in decimal format depending on the Actuator type*/
/*   Control level, PS freq, PS Watt, Stroke Length and cylinder diameter.  */
/*   If any of these value is changed preset needs to be verified again.    */
/*                                                                          */
/****************************************************************************/
{
   UINT32 TempCnfg = 0;
   SINT32 Temp = 0;
   SINT32 x = 1000000;
   CONFIGSETUP *FRAMPtr;


   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

/**----------  Start of Actuator Type  ----------**/
      switch(FRAMPtr->Actuator) /* actuator type */
      {
         case AED:             /* actuator = AED*/
            Temp = THREE;
            break;
         case AEF:             /* actuator = AOD*/
            Temp = FOUR;
            break;
         case MICRO:             /* actuator = MICRO (Replaced AOS)*/
            Temp = FIVE;
            break;
         case AES:             /* actuator = AES*/
            Temp = SIX;
            break;
         case MICROC:             /* actuator = MICROC */
            Temp = SEVEN;
            break;
         case AE:             /* actuator = AE*/
            Temp = NINE;
            break;
         default:
            break;
      }

   TempCnfg += Temp * x;
   x /= 10;

/**----------  Start of Stroke length  ----------**/

    if (FRAMPtr->Actuator == MICRO)
    {
 	  switch (FRAMPtr->StrokeLen) {
 	  case LENGTH_50: /*  50mm */
 	     Temp = 1;
 		 break;
 	  case CUSTOMLEN: /* CUSTOMLEN */
 	  default:
		 Temp = 0;
 		 break;
 	  }
    }
    else if (FRAMPtr->Actuator == MICROC)
    {
 	  switch (FRAMPtr->StrokeLen) {
 	  case LENGTH_70: /* 70mm */
 	     Temp = 1;
 	     break;
 	  case LENGTH_75: /* 75mm */
 		 Temp = 2;
 		 break;
 	  case CUSTOMLEN: /* CUSTOMLEN */
 	  default:
 		 Temp = 0;
 		 break;
 	  }
    }
    else
    {
         switch(FRAMPtr->StrokeLen) {         /* stroke length */
         case LENGTH_4:           /* LENGTH_4 */
            Temp = 1;
            break;
         case LENGTH_5:           /* LENGTH_5 */
            Temp = 2;
            break;
         case LENGTH_6:           /* LENGTH_6 */
            Temp = 3;
            break;
         case LENGTH_2:           /* LENGTH_2 */
            Temp = 4;
            break;
         case LENGTH_8:           /* LENGTH_8 */
         case LENGTH_80:           /* LENGTH_80 */
            Temp = 5;
            break;
         case LENGTH_100:           /* LENGTH_100 */
            Temp = 6;
            break;
         case LENGTH_125:           /* LENGTH_100 */
            Temp = 7;
            break;
         case LENGTH_50:           /* LENGTH_125 */
            Temp = 8;
            break;
         case CUSTOMLEN:           /* CUSTOMLEN */
   	     default:
            Temp = 0;
            break;
         }
    }

   TempCnfg += Temp * x;
   x /= 10;
 
/**----------  Start of Cylinder diameter  ----------**/

    if (FRAMPtr->Actuator == MICRO)
    {
 	   switch (FRAMPtr->CylinDiameter) {
 	   case SIZE_40: /*  40mm */
 		 Temp = 1;
 		 break;
  	   case CUSTOMLEN: /* CUSTOMLEN */
 	   default:
 		 Temp = 0;
 		 break;
 	   }
    }
    else if (FRAMPtr->Actuator == MICROC)
    {
 	  switch (FRAMPtr->CylinDiameter) {
 	  case SIZE_32: /* 32mm */
 	     Temp = 1;
 	     break;
 	  case SIZE_40: /* 40mm */
 		 Temp = 2;
 		 break;
 	  case CUSTOMLEN: /* CUSTOMLEN */
 	  default:
 		 Temp = 0;
 	     break;
 	  }
    }
    else
    {
       switch (FRAMPtr->CylinDiameter) { /* cylinder diameter */
       case SIZE1_5: /* 1.5" */
          Temp = 1;
          break;
       case SIZE2_0: /*   2"*/
          Temp = 2;
          break;
       case SIZE2_5: /* 2.5" */
          Temp = 3;
          break;
       case SIZE3_0: /*   3" */
          Temp = 4;
          break;
       case SIZE3_25: /* 3.25" */
          Temp = 5;
          break;
       case SIZE_40: /*  40mm */
          Temp = 6;
          break;
       case SIZE_50: /*  50mm */
          Temp = 7;
          break;
       case SIZE_63: /*  63mm */
          Temp = 8;
          break;
       case SIZE_80: /*  80mm */
          Temp = 9;
          break;
  	   case CUSTOMLEN: /* CUSTOMLEN */
  	   default:
  		  Temp = 0;
  	      break;
       }
    }

   TempCnfg += Temp * x;
   x /= 10;

/**----------  Start of Control level  ----------**/

      switch(FRAMPtr->ControlLevel){        /* control level */
         case LEVEL_DEPOT:           /* Depot */
            Temp = 1;
            break;
         case LEVEL_t:           /* LEVEL_t */
            Temp = 2;
            break;
         case LEVEL_e:           /* LEVEL_e */
            Temp = 3;
            break;
         case LEVEL_a:           /* LEVEL_a */
            Temp = 4;
            break;
         case LEVEL_ea:           /* LEVEL_ea */
            Temp = 5;
            break;
         case LEVEL_d:           /* LEVEL_d */
            Temp = 6;
            break;
         case LEVEL_f:           /* LEVEL_f */
            Temp = 7;
            break;
         case LEVEL_c:           /* LEVEL_c */
            Temp = 8;
            break;
         case LEVEL_TEST:           /* LEVEL_TEST */
            Temp = 9;
            break;
      }

   TempCnfg += Temp * x;
   x /= 10;

/**----------  Start of Frequency  ----------**/

      switch(FRAMPtr->PSFreq){        /* frequency */
         case FREQ15KHZ:           /* 15kHz */
            Temp = 1;
            break;
         case FREQ20KHZ:           /* 20kHz */
            Temp = 2;
            break;
         case FREQ30KHZ:           /* 30kHz */
            Temp = 3;
            break;
         case FREQ40KHZ:           /* 40kHz */
            Temp = 4;
            break;
         case FREQ50KHZ:           /* 50kHz */
            Temp = 5;
            break;
         case FREQ60KHZ:           /* 60kHz */
            Temp = 6;
            break;
      }
      
   TempCnfg += Temp * x;
   
/** --------------- Store PS Wattage divided / 100 as last two digits------**/   

   Temp = (FRAMPtr->PSWatt) / 100;
   TempCnfg += Temp;
   
   return (TempCnfg);      
      
} 
 
BOOLEAN CheckForMultipleInput(void)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function record the SE294 alarm if same input is configured to     */
/*   multiple pins.                                                          */
/*   Returns TRUE if same input is defined to more than one pin.             */
/*****************************************************************************/
{
   UINT8	x1, x2, Stop = 0, ExitFlag = FALSE;
   UINT16	UserCfgInput[INPUT_COUNT];
   BOOLEAN	RetVal = FALSE;

   /* If INPUT_DISABLED, then no need to check for 'Input Pin Conflict'. */

   if (CurrentSetup.J3_32In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_32In;
   if (CurrentSetup.J3_33In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_33In;
   if (CurrentSetup.J3_19In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_19In;
   if (CurrentSetup.J3_17In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_17In;
   if (CurrentSetup.J3_31In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_31In;
   if (CurrentSetup.J3_1In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_1In;

   if (Stop > 1) {	/* Only check if Input are not disabled. */
		x1 = 1;
		x2 = 2;
		while (ExitFlag == FALSE) {
		    /* Check if both are equal.*/
			if (UserCfgInput[x1] == UserCfgInput[x2] ) {
				RecordSetupAlarm(SE294);
				RetVal = TRUE;
				ExitFlag = TRUE;
			}
			else if (++x2 > Stop) {
				if (x1 < (Stop - 1)) {
					x1++;
					x2 = x1+1;
				}
				else /* All the inputs are checked.Get out of while loop.*/
				   ExitFlag = TRUE;
			}
		}
   }
   return (RetVal);
}



BOOLEAN IsConfigured (UINT16 SelectedInput)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function returns TRUE if the Selected input is configured to any   */
/*   of the input pin in User I/O menu.                                      */
/*****************************************************************************/
{
   BOOLEAN RetValue;
   /* If input is configured to any of the port pin. */
   if(SelectedInput == CurrentSetup.J3_32In ||
      SelectedInput == CurrentSetup.J3_33In ||
      SelectedInput == CurrentSetup.J3_19In ||
      SelectedInput == CurrentSetup.J3_17In ||
      SelectedInput == CurrentSetup.J3_31In ||
      SelectedInput == CurrentSetup.J3_1In )
      RetValue = TRUE;
   else
      RetValue = FALSE;
   
   return (RetValue);
}

BOOLEAN IsOutConfigured (UINT16 SelectedOutput)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function returns TRUE if the Selected output is configured to any  */
/*   of the output pin in User I/O menu.                                     */
/*****************************************************************************/
{
   BOOLEAN RetValue;
   /* If input is configured to any of the port pin. */
   if(SelectedOutput == CurrentSetup.J3_36Out ||
      SelectedOutput == CurrentSetup.J3_8Out  ||
      SelectedOutput == CurrentSetup.J3_22Out )
      RetValue = TRUE;
   else
      RetValue = FALSE;
   
   return (RetValue);
}

UINT16 CheckUserIOAlarm (void)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function Checks and record the alarms from SE290 to SE294.         */
/*****************************************************************************/
{
   UINT32 RetVal = FALSE;
   
         
   if(RunningPreset.ExtTrgDelay == TRUE && !IsConfigured(INPUT_EXT_TRIGDELAY))
   {/*Record TrgDelayConflict alarm*/
      RetVal = SE290;
      RecordSetupAlarm(RetVal);
   }
   /* Make 'Inp.PartClamped' TRUE between WaitSVST & Hold state when both the pins are
      not defined.  */   
   if(!IsConfigured(INPUT_PART_CLAMPED) && !IsOutConfigured(OUTPUT_PART_CLAMPED))
      PartClampActive = FALSE;
   else if(IsConfigured(INPUT_PART_CLAMPED) && IsOutConfigured(OUTPUT_PART_CLAMPED))
	   PartClampActive = TRUE;
   else /* one of the pin (PartClamp input and output) is not defined.*/
   {    /* Record PartClamp alarm*/
      RetVal = SE291;
      RecordSetupAlarm(RetVal);
   }
      
   /* Record Missing Part Conflict alarm */
   if ( (CurrentSetup.Actuator == AED) ||
	    (CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == AES) ) {
       if (IsOutConfigured(OUTPUT_MISSING_PART) && ((RunningPreset.CycleAbortFlag == FALSE) ||
          (RunningPreset.MissingPartFlag == FALSE) || ( RunningPreset.MissingMinFlag &&
           RunningPreset.MissingMaxFlag) ))
       {
           RetVal = SE292;
           RecordSetupAlarm(RetVal);
       }
   }  
     
   /* Record Energy Braking Setup alarm .*/
   if(RunningPreset.EnergyBraking == TRUE && CurrentSetup.AmpControl == FALSE)
   {
      RetVal = SE293;
      RecordSetupAlarm(RetVal);
   }
   /* If Same input configured to multiple pins.*/
   if (CheckForMultipleInput())
      RetVal = SE294;

   if((IsConfigured(INPUT_SYNC_IN) ^ IsOutConfigured(OUTPUT_SYNC_OUT)) )
   {    /* Record alarm*/
      RetVal = SE295;
      RecordSetupAlarm(RetVal);
   }
   
   return(RetVal);
}






