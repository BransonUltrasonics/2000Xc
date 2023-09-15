
/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/CONT.cpp_v   1.10   08 Jan 2015 03:18:18   AnPawar  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/CONT.cpp_v  $
 * 
 *    Rev 1.10   08 Jan 2015 03:18:18   AnPawar
 * printf removed
 * 
 *    Rev 1.9   28 Jul 2014 12:36:36   rjamloki
 * psos.h removed
 * 
 *    Rev 1.8   11 Jun 2014 11:28:54   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:47:52   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 02:58:24   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   26 Mar 2014 12:04:34   rjamloki
 * printf added for debugging
 * 
 *    Rev 1.4   05 Mar 2014 13:56:20   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:32   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:20   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Continuous Mode                                             */
/*                                                                          */
/* Filename:    Cont.c                                                      */
/*                                                                          */
/* Function Name: SelectContWeldSequence                                    */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-18-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/
/*                                                                          */
/*   Continuous mode will have two 'modes' of operation.  Pressing one or   */
/*   two palm buttons will determine which mode is used.                    */
/*                                                                          */
/*   Mode 1 - Pressing only ONE palm button, or pressing two palm buttons   */
/*            but exceeding the stagger time in between.                    */
/*                                                                          */
/*            If the second palm button is pressed after the stagger time,  */
/*            the sonics will remain on, the SV will NOT be activated, but  */
/*            an alarm will occur indicating stagger time error.            */
/*                                                                          */
/*            There will be NO SV drive output.  Sonics will remain on      */
/*            until the palm buttons are both released.                     */
/*                                                                          */
/*                                                                          */
/*   Mode 2 - Pressing TWO palm buttons within the stagger time (200 ms).   */
/*                                                                          */
/*            There will be an SV drive output when the 2nd palm button     */
/*            is pressed.  Sonics will start as soon as the 1st palm button */
/*            is pressed.  Both palm buttons must be maintained to keep the */
/*            SV drive on.  As soon as one is released the SV drive is      */
/*            removed.  The sonics will remain on as long as at least one   */
/*            palm button is pressed.                                       */
/*                                                                          */
/*            If "Pre Weld Seek" is enabled the SV drive output will not    */
/*            occur until 550 ms after the stagger time time was met. This  */
/*            is the seek time (+50 ms for tolerance).                      */
/*                                                                          */
/*            The force will be adjustable on the fly without pressing the  */
/*            palm buttons to start a new cycle.                            */
/*                                                                          */
/*                                                                          */
/*   Notes for both modes:                                                  */
/*   ---------------------                                                  */
/*                                                                          */
/*   "Pre Weld Seek", if enabled, will do a 500 ms seek as soon as one palm */
/*   button has been pressed.                                               */
/*                                                                          */
/*   In both modes there will be NO HOLD time, and no amplitude or force    */
/*   stepping.  The power will be checked to make sure the continuous power */
/*   rating is not exceeded.                                                */
/*                                                                          */
/*   In the event of an overload the sonics will be shut off as well as the */
/*   SV drive removed.  The palm buttons will have to be released and then  */
/*   pressed again to start another cycle.                                  */
/*                                                                          */
/*   The amplitude will be adjustable on the fly without pressing the palm  */
/*   buttons to start a new cycle.                                          */
/*                                                                          */
/*-------------------------  End of Description  ---------------------------*/



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


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

/*-------------------------- Function Prototypes ---------------------------*/

#include "weldhold.h"

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

/*-------------------------------- CODE ------------------------------------*/

void SelectContWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence will be based on model number and options  */
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
   WeldSequence[i++] = &OnePBState;/*  /  forcing a different sequence, all */
//   WeldSequence[i++] = &WaitUls;   /* /   hell will break loose.            */
   WeldSequence[i++] = &NopList;   /* Nop to replace WaitUls                */

/*------  Here we turn on some sonics  ------*/

   WeldSequence[i++] = &SonicsOn1A;


/*------  Determine if an after burst state is needed (not in 1pb mode) ------*/

//   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
//      WeldSequence[i++] = &ABDelayST;
//      WeldSequence[i++] = &ABTimeST;
//   }


/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekState;
   }   

   WeldSequence[i++] = &WaitUlsUp;   /* \   All weld sequences must end with*/
   WeldSequence[i++] = &FinalDataST; /*  \  these 5 states, in this order.  */
   WeldSequence[i++] = &PreReady;    /*   >                                 */
   WeldSequence[i++] = &NopList;     /*  /                                  */
   WeldSequence[i++] = &EndOfList;   /* /                                   */


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



