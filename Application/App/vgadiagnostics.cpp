/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgadiagnostics.cpp_v   1.3   28 Nov 2014 07:42:00   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgadiagnostics.cpp_v  $
 * 
 *    Rev 1.3   28 Nov 2014 07:42:00   rjamloki
 * Changes to avoid warnings.
 * 
 *    Rev 1.2   11 Sep 2014 11:11:04   rjamloki
 * Added ActColdStart event
 * 
 *    Rev 1.1   09 Jul 2014 11:49:36   rjamloki
 * Removed Dataprinting checks.
 * 
 *    Rev 1.0   11 Jun 2014 13:21:26   rjamloki
 * Initial revision.
 * 
 *    Rev 1.6   21 May 2014 10:48:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:35:54   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:40   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:50   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:46   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  ---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: VGADiagnostics.c

      Written by: JOY MD 
            Date: 04/17/2003 
        Language: "C"

 ------------------------------- DESCRIPTION ---------------------------------


 ------------------------------ INCLUDE FILES --------------------------------
*/
#include <string.h>
#include "beep.h"
#include "menu.h"
#include "menu5.h"
#include "dups_api.h"
#include "digout.h"
#include "statedrv.h"
#include "spidd.h"
#include "preset.h"
#include "param.h"
#include "util.h"
#include "selctkey.h"
#include "state.h"
#include "ticks.h"
#include "snsrcalb.h"
#include "inports.h"
#include "command.h"
#include "Events.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/

/*------------------------------- GLOBAL DATA ------------------------------*/
BOOLEAN VGAHornScanOLD = FALSE;    // Horn Scan Overload 
BOOLEAN VGAAbortHornScan = FALSE;  // Abort the Horn Scan.
BOOLEAN VGADigitalChoiceWaitFlag = FALSE;
BOOLEAN VGADigitalChoiceTestFlag = FALSE;
BOOLEAN VGAColdStartFlag = FALSE;
BOOLEAN VGAColdStartErrorFlag = FALSE;
BOOLEAN VGAActStartFlag = FALSE;
BOOLEAN VGAActStartErrorFlag = FALSE;
UINT16 BransonFunctionFlag = FALSE;
UINT8 AbortScanButtonState;
UINT8 PrevHornState = 0;
UINT16 ShowHSAbort = FALSE;
MENUEND endlistDiag = { TRUE };
BOOLEAN VGARunSelected, VGAClearSelected, VGASeekSelected, VGAStoreSelected;

BOOLEAN  ForceDigitalTuneTest = FALSE; /* TRUE if user must press Test to exit */
SINT32   SaveDigTuneValue;   /* Used to determine if user changed value */

/*--------------------------- EXTERN FUNCTION PROTOTYPES --------------------*/

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/
void UpdateFrequencyResonance(void);
void GetRunSelection(void);
void GetClearSelection(void);
void GetSeekSelection(void);
void GetStoreSelection(void);

/*---------------------------- EXTERNAL DATA -------------------------------*/

extern BOOLEAN NextMenuFlag;
extern BOOLEAN HSStartFlag;
extern UINT8  LimitChanged;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern UINT8 VGALatchPSStore;
extern BOOLEAN HSNotStarted;
extern BOOLEAN IsGraphDrawing;
extern UINT16 OrigDigTuneFlag;        /* Initial DigTune On/Off state */
extern SINT32 OrigDigTuneValue;       /* Initial DigTune value before editing */
extern SINT32 DigTuneValue;           /* This is what user edits */
extern SINT32 MinDigTuneValue;        /* Min value allowed in editing */
extern SINT32 MaxDigTuneValue;        /* Max value allowed in editing */
extern UINT16 DiagFlag;

extern enum WELDSTATES WeldState;

extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN StateMachineDisabled;
void  ExitMenuAndEnableWeld (void);
/*
 ---------------------------------- CODE -------------------------------------
*/

void VGADigitalPotChoiceDone(void)
/****************************************************************************/
/*Description:                                                              */
/* This function is called after the user has selected On or Off for        */
/* Digital Tune.                                                            */
/* This function needs to take action only if current setting is Off.       */
/* If it was originally Off, just restart state machine.  If it was         */
/* originally On, user will be forced to press the Test key.                */
/****************************************************************************/
{
   UINT32  FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   if (!(CurrentSetup.DigTuneFlag & BIT0))  /* If now Off ... */
   {
      /* If was originally On and DigTune position changed, make */
      /* user push Test key */

      if (OrigDigTuneFlag && (FreqAtCenter != (UINT32)OrigDigTuneValue))
      {
         CenterDigTune();
         VGADigitalChoiceWaitFlag = TRUE;   /* Wait for pot to center */
         
         VGADigitalChoiceTestFlag = TRUE;         
      }
      else     /* No change, just allow welding & go */
      {
         ResetStateMachine();
         StartStateMachine();
      }
   }
   else
   {
      ResetStateMachine();   /* Covers On + GoBack case and anything */
      StartStateMachine();   /* else we haven't thought of. */
   }
}


void UpdateDigitalFreq(void)
/***************************************************************************/
/*Description:                                                             */
/* Update the variable'DigTuneValue'(Digital tune start Freq:) so that      */
/* actual freq: value is displayed when entering in to the DIAG_SCREEN.    */
/***************************************************************************/
{
   UINT32 FreqAtCenter;
   SINT32 CurrentDigTune;
   
   OrigDigTuneFlag = CurrentSetup.DigTuneFlag & BIT0;

   if (OrigDigTuneFlag)                        /* If not in use now, orig */
      CurrentDigTune = CurrentSetup.DigTune; /* position is "centered" */
   else
      CurrentDigTune = 0;
   FreqAtCenter = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
      case FREQ20KHZ:
         DigTuneValue = CurrentDigTune/6 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 499;
         MaxDigTuneValue = FreqAtCenter + 500;
         break;
      case FREQ15KHZ:
         DigTuneValue = CurrentDigTune/8 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 374;
         MaxDigTuneValue = FreqAtCenter + 375;
         break;
      case FREQ30KHZ:
         DigTuneValue = CurrentDigTune/4 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 749;
         MaxDigTuneValue = FreqAtCenter + 750;
         break;
      case FREQ60KHZ:
         DigTuneValue = CurrentDigTune/2 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 1499;
         MaxDigTuneValue = FreqAtCenter + 1500;
         break;   
      case FREQ40KHZ:
      default:
         DigTuneValue = CurrentDigTune/3 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 999;
         MaxDigTuneValue = FreqAtCenter + 1000;
         break;
   }
}

void EnableHornScanStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Set 'HSNotStarted' flag before entering in to the HORN SCAN SCREEN      */
/* Set Horn scan status to DUPS_NOSCAN.                                    */
/***************************************************************************/
{
   if (UserIOAlarmMenu || StateMachineDisabled)
      ExitMenuAndEnableWeld();
   if(WeldState != READYSTATE)  
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
   DiagFlag = FALSE;
   HSStartFlag = FALSE;
   HSNotStarted = TRUE;
   if(HornScanInfo. ScanStatus == DUPS_SCANINPROG)
      HornScanInfo. ScanStatus = DUPS_NOSCAN;
   PrevHornState = SCAN_NONE;
   UpdateFrequencyResonance();
}

void DisableDiagnostics(void)
{
   DiagFlag = FALSE;
}

void GetRunSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Run Selection for VGACHECK object                                  */
/***************************************************************************/
{
   VGARunSelected = LatchPSRun;
   LatchPSRun = FALSE;
}

void GetClearSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Clear Selection for VGACHECK object                                */
/***************************************************************************/
{
   VGAClearSelected = LatchPSClear;
   LatchPSClear = FALSE;
}

void GetSeekSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Seek Selection for VGACHECK object                                 */
/***************************************************************************/
{
   VGASeekSelected = LatchPSSeek;
   LatchPSSeek = FALSE;
}

void GetStoreSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Store Selection for VGACHECK object                                */
/***************************************************************************/
{
   VGAStoreSelected = (LatchPSStore || VGALatchPSStore );
   LatchPSStore = FALSE;
}

void ProcessHSAbort1 (void)
/***************************************************************************/
/*Description:                                                             */
/* Processes Horn scan by setting the Flag True                            */
/***************************************************************************/
{
   ShowHSAbort = FALSE;
   VGAAbortHornScan = TRUE;
}

void SetDigtalPot(void)
/***************************************************************************/
/*Description:                                                             */
/* Makes Digital pot setting zero if making Digital tune OFF               */
/***************************************************************************/
{
   if (!ForceDigitalTuneTest)
   {
      CurrentSetup.DigTune = 0;
      UpdateCurrentPresetAndSetup(DIGTUNEFLAG);
   }
}

void VGACheckDigitalTune(void)
/***************************************************************************/
/*Description:                                                             */
/* Performs Digital Tune                                                   */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (!CheckStateMachine())
   {
      if (SaveDigTuneValue != DigTuneValue)
      {
         SetDigTune();      /* CurrentSetup.DigTune updated already */
                               /* on exit from VARIABLE entry. */
         VGADigitalChoiceWaitFlag = TRUE;   /* Wait for pot to center */
         ForceDigitalTuneTest = TRUE;
         VGADigitalChoiceTestFlag = TRUE;         
      }
      else if (!ForceDigitalTuneTest)
      {
         ResetStateMachine();  /* Position is at original value, */
         StartStateMachine();  /* don't need to force Test.      */
      }
   }
}

void ColdStartEnable(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start if weld state is either ready/pre-ready state and     */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE))
   {
      VGAColdStartFlag = TRUE;
      LimitChanged = TRUE;
   }
   else
      VGAColdStartErrorFlag = TRUE;
}

void VGADoColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start. If VGA is present then Polling command initiates Cold*/
/* start else it will be done here                                         */
/***************************************************************************/
{
   if (IsHWConfigured(VGA))
      VGAColdStartFlag = TRUE;
   else
      DoColdStart();   
}


void VGAActColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do Actuator Cold start.                                                 */
/***************************************************************************/
{
   BuildDefaultSpringRate();    /* welding */     
   ResetStateMachine();
   StartStateMachine();
   NextMenuFlag = TRUE;
}

void EnableActColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Actuator Cold start if weld state is either ready/pre-ready state*/
/* And there is no data printing/Drawing is going on...                    */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE))
   { 
      StopStateMachine();          /* Perform cold start only if not */
      VGAActStartFlag = TRUE;
      RecordEvents(EVENT_ACTCOLD_START,"","");
   }   
   else
      VGAActStartErrorFlag = TRUE;
}

 /*=========================================================================*/
 /*******************************END*****************************************/
 /*=========================================================================*/
 
