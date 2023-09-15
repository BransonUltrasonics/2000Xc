/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/PEAKPWR.cpp_v   1.16   Oct 10 2017 12:44:32   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/PEAKPWR.cpp_v  $
 * 
 *    Rev 1.16   Oct 10 2017 12:44:32   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.15   16 Mar 2015 06:18:44   rjamloki
 * Moved INPUT_CONFIRM_REJECT test to limits.cpp
 * 
 *    Rev 1.14   11 Mar 2015 09:17:26   amaurya
 * SelectPeakPowerWeldSequence() changed to add rejectconfirminput to weldsequence.
 * 
 *    Rev 1.13   11 Feb 2015 06:37:40   amaurya
 * change in SelectPeakPowerWeldSequence() function reject confirm
 * 
 *    Rev 1.12   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.11   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 11:16:06   rjamloki
 * SvInterlock renamed to PartClamp
 * 
 *    Rev 1.8   11 Jun 2014 12:00:30   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:52:20   rjamloki
 * Changes related to Weld Trigger by Distance
 * 
 *    Rev 1.6   21 May 2014 03:34:32   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   26 Mar 2014 12:27:50   rjamloki
 * SelectPeakPowerWeldSequence() function changed
 * 
 *    Rev 1.4   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:46   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION ---------------------------

   Module name: Peak Power Mode

   Filename:    Peakpwr.c

   Function Name: SelectPeakPowerWeldSequence

            Written by:   Barry E. Kymer
                  Date:   06-18-96
              Language:   "C"
  ----------------------------- DESCRIPTION --------------------------------
                                        
  ----------------------------- PSEUDO CODE --------------------------------


  ---------------------------- LOCAL_EQUATES -------------------------------

//#define TIME_UT                        For use as an aid in unit test

  ------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include "qdef.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "weldhold.h"
#include "inports.h"
#include "outports.h"
#include "limits.h"

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

/*-------------------------- Function Prototypes ---------------------------*/

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

/*-------------------------------- CODE ------------------------------------*/

void SelectPeakPowerWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Peak Power Mode Weld sequence will be based on level and           */
/* options selected from the menus.                                        */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16  i = 0;


   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &TopOfList; /* \   All weld sequences must start with*/
   WeldSequence[i++] = &PreReady;  /*  \  these 5 states, in this order.    */
   WeldSequence[i++] = &ReadySt;   /*   > Otherwise, when preset is verified*/
   WeldSequence[i++] = &PBState;   /*  /  forcing a different sequence, all */
                                   /* /   hell will break loose.            */
   
   if(IsConfigured(INPUT_PART_CLAMPED) && IsOutConfigured(OUTPUT_PART_CLAMPED))
      WeldSequence[i++] = &WaitPartClampST;  /* Wait for PartClamp signal in this state. */
      
   WeldSequence[i++] = &WaitUls;
   
   WeldSequence[i++] = &StartData;
   
/*--------------------------------------------------------------------------*/
/*  Determine if downspeed LEVEL_e or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and put that one first in the list.  */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AES) ||
		   (CurrentSetup.Actuator == MICROC) ||
           (CurrentSetup.Actuator == MICRO)) {                        /* and we have an encoder (AED,AES)*/
       	 if  ((RunningPreset.RTFlag & BIT0) == BIT0) {                 /* If Rapid Traverse is on                   */
            if (RunningPreset.PreTriggerDistanceFlag == FALSE) {              /* Pretrigger on distance ( FALSE=On )       */
               if (RunningPreset.RTDist > RunningPreset.PreTriggerDistance) { /* Pretrigger occurs before rapid traverse   */
                  WeldSequence[i++] = &PreTrsDST;
                  WeldSequence[i++] = &WaitTrs1DSTPT;
                  WeldSequence[i++] = &WaitTrs2DSTPT;
               }
               else {                                                  /* Rapid traverse occurs before pretrigger   */   
                  WeldSequence[i++] = &WaitTrs1DSTPT;
                  WeldSequence[i++] = &PreTrsDST;
                  WeldSequence[i++] = &WaitTrs2DSTPT;
               }
            }   
            else {                                                     /* Auto pretrigger, then rapid traverse      */      
               WeldSequence[i++] = &PreTrsDST;
               WeldSequence[i++] = &WaitTrs1DSTPT;
               WeldSequence[i++] = &WaitTrs2DSTPT;
            }
         }   
         else {                                                        /* No rapid traverse, pretrigger on          */      
            WeldSequence[i++] = &PreTrsDST;
            WeldSequence[i++] = &WaitTrs1DSTPT;
            WeldSequence[i++] = &WaitTrs2DSTPT;
         }
      }      
      else {                                                           /* No encoder, so pretrigger is auto, no R/T */
         WeldSequence[i++] = &PreTrsST;
         WeldSequence[i++] = &WaitTrs1STPT;
         WeldSequence[i++] = &WaitTrs2STPT;
      }
   }
   else {
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == MICRO) ) {                        /* and we have an encoder (AED,AES)*/
         WeldSequence[i++] = &WaitTrs1DST;
         WeldSequence[i++] = &WaitTrs2DST;
      }
      else{
         WeldSequence[i++] = &WaitTrs1ST;
         WeldSequence[i++] = &WaitTrs2ST;
      }
   }

   WeldSequence[i++] = &TriggerST;              /* Cause the beeper to beep */

   /* If ExtTrgDelay is selected in WeldSetup */
   if(RunningPreset.ExtTrgDelay == TRUE){
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &ExtTrigDelayST;
	   else
		   WeldSequence[i++] = &ExtTrigDelaySTDist;
   }
/*------  Determine if trigger delay is needed  ------*/

   if ((RunningPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == 0) {/* Is it disabled?*/
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &TrigDelayST;
	   else
		   WeldSequence[i++] = &TrigDelaySTDist;
   }   


/*------  Here we turn on some sonics  ------*/

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES) ||
		(CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == MICRO)) {                        /* and we have an encoder (AED,AES)*/
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn3CDST;
	   else
		   WeldSequence[i++] = &SonicsOn3CDSTDist;
   }
   else{
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn3CST;
	   else
		   WeldSequence[i++] = &SonicsOn3CSTDist;
   }

/*------  Determine if stepping is needed  ------*/

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES) ||
		(CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == MICRO)) {                        /* and we have an encoder (AED,AES)*/
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn7DST;
	   else
		   WeldSequence[i++] = &SonicsOn7DSTDist;
   }
   else{/* Amplitude step is off  */
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn7ST;
	   else
		   WeldSequence[i++] = &SonicsOn7STDist;
   }
   if (RunningPreset.EnergyBraking == TRUE){     /* Energy braking needed */
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &EnerBrakeST;
	   else
		   WeldSequence[i++] = &EnerBrakeSTDist;
   }
      
   WeldSequence[i++] = &WeldOffST;           /* End of sonics, key to do end of weld stuff */



/*------  Determine if a hold state is needed  ------*/

   if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) {
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &FakeHold;
	   else
		   WeldSequence[i++] = &FakeHoldDist;
   }
   else{
    if ( (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == AES) ||
		 (CurrentSetup.Actuator == MICROC) ||
         (CurrentSetup.Actuator == MICRO))  {
    	if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &HoldTimeDST;
	   else
		   WeldSequence[i++] = &HoldTimeDSTDist;
      }
      else{
    	  if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
			   WeldSequence[i++] = &HoldTimeST;
		   else
			   WeldSequence[i++] = &HoldTimeSTDist;
      }
   }


/*------  Always squirt in a state to check process alarms  ------*/

   WeldSequence[i++] = &CheckLimitsST;


/*------  Determine if an after burst state is needed  ------*/

   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
      WeldSequence[i++] = &ABDelayST;
      WeldSequence[i++] = &ABTimeST;
      WeldSequence[i++] = &RampSonicsST;
   }


/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekState;
   }   

/*------  Finally get back to the ready state  ------*/

   WeldSequence[i++] = &WaitUlsUp;    /* \ All weld sequences must end with*/
   /* Stop data collection */         /*  \  */ 
   WeldSequence[i++] = &StopData;     /*   \ */   
   // WeldSequence[i++] = &ClearMemST;/*    \*/
   WeldSequence[i++] = &FinalDataST;  /*    /*/
   if(IsRejectLimitsEnabled())
	   WeldSequence[i++] = &ConfirmRejectST;
   WeldSequence[i++] = &PreReady;     /*   / */
   WeldSequence[i++] = &NopList;      /*  /  */
   WeldSequence[i++] = &EndOfList;    /* /   */


/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME;
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}



void SelectPeakPowerWeldSequenceHH(void)
/***************************************************************************/
/*                                                                         */
/* This Peak Power Mode Weld sequence for handheld will be based on        */
/* LEVEL and options selected from the menus.                              */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16  i = 0;

   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &TopOfList;   
   WeldSequence[i++] = &PreReadyHHST;
   WeldSequence[i++] = &ReadyHHST; 
   WeldSequence[i++] = &PBStateHHST; 

   WeldSequence[i++] = &StartData;

/*------  Here we turn on some sonics  ------*/

   WeldSequence[i++] = &SonicsOnPP1ST;
   WeldSequence[i++] = &SonicsOnPP2ST;
   if (RunningPreset.EnergyBraking == TRUE)
      WeldSequence[i++] = &EnerBrakeHHST;      /* Energy braking needed */
      
   WeldSequence[i++] = &WeldOffHHST;  /* End of sonics, key to do end of weld stuff */


/*------  Determine if a hold state is needed  ------*/

   if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
      WeldSequence[i++] = &FakeHoldHHST;
   else  
      WeldSequence[i++] = &HoldTimeHHST;


/*------  Always squirt in a state to check process alarms  ------*/

   WeldSequence[i++] = &CheckLimitsST;


/*------  Determine if an after burst state is needed  ------*/

   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
      WeldSequence[i++] = &ABDelayHHST;
      WeldSequence[i++] = &ABTimeHHST;
      WeldSequence[i++] = &RampSonicsST;
   }


/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekStateHH;
   }   

   WeldSequence[i++] = &TriggerHHST;              /* Cause the beeper to beep */


/*------  Finally get back to the ready state  ------*/

   WeldSequence[i++] = &StopData;
   // WeldSequence[i++] = &ClearMemST;
   WeldSequence[i++] = &FinalDataST;
   WeldSequence[i++] = &PreReadyHHST;    
   WeldSequence[i++] = &NopList;
   WeldSequence[i++] = &EndOfList;


/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME;
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}

