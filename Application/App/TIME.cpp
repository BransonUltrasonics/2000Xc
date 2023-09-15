/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/TIME.cpp_v   1.18   Oct 10 2017 14:51:56   RJamloki  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/TIME.cpp_v  $
 * 
 *    Rev 1.18   Oct 10 2017 14:51:56   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.17   16 Mar 2015 06:18:18   rjamloki
 * Moved INPUT_CONFIRM_REJECT test to limits.cpp
 * 
 *    Rev 1.16   11 Mar 2015 09:19:38   amaurya
 * SelectTimeWeldSequence() changed for confirmrejectinput.
 * 
 *    Rev 1.15   11 Feb 2015 06:39:38   amaurya
 * change in function SelectTimeWeldSequence() for reject confirm input
 * 
 *    Rev 1.14   28 Nov 2014 07:41:42   rjamloki
 * Removed printf();
 * 
 *    Rev 1.13   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.12   07 Aug 2014 15:46:38   tayars
 * Edited the weld sequence to disregard some states in downspeed tuning process.
 * 
 *    Rev 1.11   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.10   09 Jul 2014 11:43:18   rjamloki
 * SvInterlock renamed to part clamp.
 * 
 *    Rev 1.9   11 Jun 2014 12:14:42   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:52:54   rjamloki
 * Changes related to Weld Trigger by Distance
 * 
 *    Rev 1.7   21 May 2014 03:54:16   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.6   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:46   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:56   rjamloki
 * Preset changes to support 1000 preset.
 *
 *    Rev 1.3   03 Jan 2014 08:45:56   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Time Mode                                                   */
/*                                                                          */
/* Filename:    Time.c                                                      */
/*                                                                          */
/* Function Name: SelectTimeWeldSequence                                    */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-18-96                                          */
/*            Language:   "C"                                               */
/*
----------------------------- DESCRIPTION --------------------------------*/



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define TIME_UT                       /* For use as an aid in unit test   */




/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include "qdef.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "state.h"
#include "weldhold.h"
#include "inports.h"
#include "outports.h" 
#include "stdio.h"
#include "limits.h"
/*-------------------------- Function Prototypes ---------------------------*/

           
/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

extern BOOLEAN DownspeedTuneFlag, DownspeedTuneFlagHD;

/*-------------------------------- CODE ------------------------------------*/

           
void SelectTimeWeldSequence(void)

/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence will be based on level and options  */
/* selected from the menus.                                                */
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
   
   if(!DownspeedTuneFlag)
      WeldSequence[i++] = &StartData;
   
/*------  At this point update Run Screen so alarm message goes  ------*/
/*------  away and last cycle weld results are set to 0   ------*/



/*--------------------------------------------------------------------------*/
/*  Determine if downspeed 2 or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and list that one first in the list. */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AES) ||
		   (CurrentSetup.Actuator == MICROC) ||
		   (CurrentSetup.Actuator == MICRO))  {                       /* and we have an encoder (AED, AEF)*/
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
      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AES) ||
		   (CurrentSetup.Actuator == MICROC) ||
		   (CurrentSetup.Actuator == MICRO))  {   /* Trigger seq if PTS off    */
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
		(CurrentSetup.Actuator == MICRO))  {
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn1DST;
	   else
		   WeldSequence[i++] = &SonicsOn1DSTDist;
   }
   else{
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn1ST;
	   else
		   WeldSequence[i++] = &SonicsOn1STDist;
   }
/*------  Determine if stepping is needed  ------*/

    if ( (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == AES) ||
		 (CurrentSetup.Actuator == MICROC) ||
		 (CurrentSetup.Actuator == MICRO))  {/* Amplitude step is off  */
    	if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn2DST;
	   else
		   WeldSequence[i++] = &SonicsOn2DSTDist;
   }
   else{/* Amplitude step is off  */
	   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &SonicsOn2ST;
	   else
		   WeldSequence[i++] = &SonicsOn2STDist;
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

   WeldSequence[i++] = &WaitUlsUp;     /* \   All weld sequences must end with*/
   /* Stop data collection  */         /*  \  */
   if(DownspeedTuneFlag)
   {
	   if(DownspeedTuneFlagHD){
		   WeldSequence[i++] = &StopDataTuneHD;
	   }
	   else{
		   WeldSequence[i++] = &StopDataTune;
	   }
   }
   else
      WeldSequence[i++] = &StopData;      /*   \ */
   // WeldSequence[i++] = &ClearMemST; /*    \*/
   if(!DownspeedTuneFlag)
      WeldSequence[i++] = &FinalDataST;/*    /*/
   if(IsRejectLimitsEnabled())
	   WeldSequence[i++] = &ConfirmRejectST;
   WeldSequence[i++] = &PreReady;      /*   / */
   WeldSequence[i++] = &NopList;       /*  /  */
   WeldSequence[i++] = &EndOfList;     /* /   */

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME + 1;       /* Kludge fix for DCS # 2514    */
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}


void SelectTimeWeldSequenceHH(void)
/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence is used for 1 input cycle start options    */
/* such as handheld and will be based on control level and options         */
/* selected from the menus.                                                */
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
   }                                      /* external presets are selected          */
   WeldSequence[i++] = &StartData;

/*------  Sonics State ------*/

   if (CurrentSetup.PLCControlFlag == FALSE) { /* STANDARD CONTROL            */
      WeldSequence[i++] = &SonicsOnHHST;       /* Here we turn on some sonics */
      WeldSequence[i++] = &SonicsOn2HHST;      /* Amplitude step is off       */
      if (RunningPreset.EnergyBraking == TRUE)
         WeldSequence[i++] = &EnerBrakeHHST;   /* Energy braking needed       */
   }
   else {                                      /* PLC CONTROL                 */
      WeldSequence[i++] = &PLCOnHHST;          /* Here we turn on some sonics */
      WeldSequence[i++] = &PLCOn2HHST;         /* Amplitude step is off       */
      if (RunningPreset.EnergyBraking == TRUE)
         WeldSequence[i++] = &PLCBrakeHHST;    /* Energy braking needed       */
   }
      
   WeldSequence[i++] = &WeldOffHHST;  /* End of sonics, key to do end of weld stuff */

/*------  Determine if a hold state is needed  ------*/

   if (CurrentSetup.PLCControlFlag == FALSE) { /* STANDARD CONTROL            */
      if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
         WeldSequence[i++] = &FakeHoldHHST;    /* No hold needed */
      else
         WeldSequence[i++] = &HoldTimeHHST;    /* Hold on        */
   }   
   else {                                      /* PLC CONTROL                 */
      if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
         WeldSequence[i++] = &FakeHold;        /* No hold needed */
      else   
         WeldSequence[i++] = &PLCTimeHHST;     /* Hold on        */
   }
   
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
   MaxWTime = MAX_WELD_TIME + 1;       /* Kludge fix for DCS # 2514    */
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}
