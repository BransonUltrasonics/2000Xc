/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ABSOLUTE.cpp_v   1.15   Nov 06 2017 09:06:52   RJamloki  $ */
/****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/ABSOLUTE.cpp_v  $
 * 
 *    Rev 1.15   Nov 06 2017 09:06:52   RJamloki
 * Added MICROC ID to every Actuator ID’s Validation
 * 
 *    Rev 1.14   Oct 09 2017 14:05:42   RJamloki
 * added CurrentSetup.Actuator=MICROC in if stament that, evaluae actuartor id's
 * 
 *    Rev 1.13   16 Mar 2015 05:45:58   rjamloki
 * Moved INPUT_CONFIRM_REJECT test to limits.cpp
 * 
 *    Rev 1.12   11 Mar 2015 09:14:26   amaurya
 * INPUT_REJECT_ALARM changed to INPUT_CONFIRM_REJECT.
 * 
 *    Rev 1.11   11 Feb 2015 06:32:38   amaurya
 * changes in function SelectAbsoluteWeldSequence reject confirm input
 * 
 *    Rev 1.10   18 Aug 2014 01:32:38   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.9   28 Jul 2014 12:36:36   rjamloki
 * psos.h removed
 * 
 *    Rev 1.8   09 Jul 2014 10:33:44   rjamloki
 * SvInterlock renamed to PartClamp
 * 
 *    Rev 1.7   11 Jun 2014 11:17:18   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:47:44   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 02:49:34   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:14   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:28   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:16   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/


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
#include "weldhold.h"
#include "inports.h"
#include "outports.h"
#include "limits.h"


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

/*-------------------------- Function Prototypes ---------------------------*/

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

/*-------------------------------- CODE ------------------------------------*/

void SelectAbsoluteWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Absolute Mode Weld sequence will be based on LEVEL number and      */
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
      WeldSequence[i++] = &WaitPartClampST;  /* / Wait for Part clamp signal in this state. */
      
   WeldSequence[i++] = &WaitUls;   

   WeldSequence[i++] = &StartData;   


/*--------------------------------------------------------------------------*/
/*  Determine if downspeed 2 or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and put that one first in the list.  */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ((CurrentSetup.Actuator == AED)    ||                           /* and we have an encoder (AED or AES)       */
          (CurrentSetup.Actuator == AES)    ||
		  (CurrentSetup.Actuator == MICROC) ||
          (CurrentSetup.Actuator == MICRO))
        {                        /*                              */
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
      WeldSequence[i++] = &WaitTrs1DST;
      WeldSequence[i++] = &WaitTrs2DST;
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
   if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE){
	   WeldSequence[i++] = &SonicsOn3A;
	   WeldSequence[i++] = &SonicsOn5;
   }
   else{
	   WeldSequence[i++] = &SonicsOn3ADist;
	   WeldSequence[i++] = &SonicsOn5Dist;
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
      if(RunningPreset.WeldTrigger == TRIGGERBY_FORCE)
		   WeldSequence[i++] = &HoldTimeDST;
	   else
		   WeldSequence[i++] = &HoldTimeDSTDist;
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
   WeldSequence[i++] = &WaitUlsUp;     /* \ All weld sequences must end with*/
   /* Stop data collection */          /*  \  */
   WeldSequence[i++] = &StopData;      /*   \ */
   // WeldSequence[i++] = &ClearMemST; /*    \*/
   WeldSequence[i++] = &FinalDataST;   /*    /*/
   if(IsRejectLimitsEnabled())
	   WeldSequence[i++] = &ConfirmRejectST;
   WeldSequence[i++] = &PreReady;      /*   / */
   WeldSequence[i++] = &NopList;       /*  /  */
   WeldSequence[i++] = &EndOfList;     /* /   */

   /*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i > NMBR_OF_STATES) {
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



