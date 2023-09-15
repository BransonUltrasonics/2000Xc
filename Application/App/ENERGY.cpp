/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ENERGY.cpp_v   1.16   Oct 09 2017 15:56:38   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ENERGY.cpp_v  $
 * 
 *    Rev 1.16   Oct 09 2017 15:56:38   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.15   16 Mar 2015 05:49:48   rjamloki
 * Moved INPUT_CONFIRM_REJECT test to limits.cpp
 * 
 *    Rev 1.14   11 Mar 2015 09:14:58   amaurya
 * INPUT_REJECT_ALARM changed to INPUT_CONFIRM_REJECT.
 * 
 *    Rev 1.13   11 Feb 2015 06:34:06   amaurya
 * change in function SelectEnergyWeldSequence for reject confirm input
 * 
 *    Rev 1.12   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.11   18 Aug 2014 01:36:02   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 10:48:16   rjamloki
 * SvInterlock renamed to PartClamp
 * 
 *    Rev 1.8   11 Jun 2014 11:28:56   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:51:56   rjamloki
 * Changes related to Weld Trigger by Distance
 * 
 *    Rev 1.6   21 May 2014 03:02:08   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   26 Mar 2014 12:13:24   rjamloki
 * printf added in function SelectEnergyWeldSequence() for debugging
 * 
 *    Rev 1.4   05 Mar 2014 13:56:22   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION ---------------------------

   Module name: Energy Mode

   Filename:    Energy.c
   Function Name: SelectEnergyWeldSequence

          Written by:   Barry E. Kymer
                Date:   06-18-96
            Language:   "C"

  ----------------------------- DESCRIPTION --------------------------------



  ----------------------------- PSEUDO CODE --------------------------------



  ---------------------------- LOCAL_EQUATES -------------------------------*/

//#define TIME_UT                       /* For use as an aid in unit test   */




/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include "qdef.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "inports.h"
#include "outports.h"
#include "limits.h"

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

/*-------------------------- Function Prototypes ---------------------------*/

#include "weldhold.h"

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

/*-------------------------------- CODE ------------------------------------*/

void SelectEnergyWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Energy Mode Weld sequence will be based on LEVEL number and        */
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
/*  Determine if downspeed 2 or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and put that one first in the list.  */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICROC) ||
           (CurrentSetup.Actuator == AES) || ((CurrentSetup.Actuator == MICRO))) {                        /* and we have an encoder (AED,AES)*/
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
      if ( (CurrentSetup.Actuator == AED)    ||
           (CurrentSetup.Actuator == AES)    ||
		   (CurrentSetup.Actuator == MICROC) ||
           (CurrentSetup.Actuator == MICRO)) {   /* Trigger seq if PTS off    */
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
        (CurrentSetup.Actuator == MICRO)) {
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn3DST;
	   else
		   WeldSequence[i++] = &SonicsOn3DSTDist;
   }
   else{
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn3ST;
	   else
		   WeldSequence[i++] = &SonicsOn3STDist;
   }

/*------  Determine if stepping is needed  ------*/

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES) ||
		(CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == MICRO)) {  /* Amplitude step is off  */
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
	   		   WeldSequence[i++] = &SonicsOn4DST;
	   	   else
	   		   WeldSequence[i++] = &SonicsOn4DSTDist;
   }
   else{/* Amplitude step is off  */
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn4ST;
	   else
		   WeldSequence[i++] = &SonicsOn4STDist;
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
   WeldSequence[i++] = &WaitUlsUp;   /*  \   All weld sequences must end with*/
   /* Stop data collection */        /*   \  */
   WeldSequence[i++] = &StopData;    /*    \ */   
   // WeldSequence[i++] = &ClearMemST;/*   / */
   WeldSequence[i++] = &FinalDataST; /*   /  */
   if(IsRejectLimitsEnabled())
	   WeldSequence[i++] = &ConfirmRejectST;
   WeldSequence[i++] = &PreReady;    /*  /   */
   WeldSequence[i++] = &NopList;     /* /    */
   WeldSequence[i++] = &EndOfList;   /*/     */

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


void SelectEnergyWeldSequenceHH(void)
/***************************************************************************/
/*                                                                         */
/* This Energy Mode Weld sequence for handheld devices will be based on    */
/* LEVEL number and options selected from the menus.                       */
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
   if (CurrentSetup.ExtPresets == TRUE) {
      WeldSequence[i++] = &PBStateHHST;   /* Need an extra state when both HH and   */
   }   
   WeldSequence[i++] = &StartData;

/*------  Sonics State ------*/

   WeldSequence[i++] = &SonicsOn3HHST; /* Here we turn on some sonics                */
   WeldSequence[i++] = &SonicsOn4HHST; /* Amplitude step is off                      */
   if (RunningPreset.EnergyBraking == TRUE)
      WeldSequence[i++] = &EnerBrakeHHST;      /* Energy braking needed */
      
   WeldSequence[i++] = &WeldOffHHST;   /* End of sonics, key to do end of weld stuff */

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

