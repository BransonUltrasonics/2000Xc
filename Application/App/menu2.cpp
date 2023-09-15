/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu2.cpp_v   1.20   16 Apr 2015 07:24:58   rjamloki  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu2.cpp_v  $
 * 
 *    Rev 1.20   16 Apr 2015 07:24:58   rjamloki
 * Removed unused functions to fix warning
 * 
 *    Rev 1.19   08 Apr 2015 13:44:20   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.18   27 Mar 2015 11:08:18   amaurya
 * SetPresetValidated() change,Updated comment as per code review.
 * 
 *    Rev 1.17   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.16   02 Jan 2015 04:05:26   rjamloki
 * SetPresetValidated() function changed for preset revesion
 * 
 *    Rev 1.15   28 Nov 2014 07:37:16   rjamloki
 * SetSetupFlag() changed to initialize the passed argument.
 * 
 *    Rev 1.14   10 Nov 2014 04:52:12   AnPawar
 * commented code removed from ChangeDUPSSubParamList() ,12.F review change.
 * 
 *    Rev 1.13   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.12   11 Sep 2014 10:59:18   rjamloki
 * Added preset validation events
 * 
 *    Rev 1.11   05 Sep 2014 04:50:24   rjamloki
 * Copying Assembly numbers to current and running preset if active preset is validated.
 * 
 *    Rev 1.10   28 Jul 2014 12:36:40   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 13:29:52   rjamloki
 * Added functions to support preset validation and lock changes from menu.
 * 
 *    Rev 1.8   11 Jun 2014 11:54:30   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:08:32   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:30   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:42   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:34   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------
                        
   Module name:

   Filename: menu2.c

   Function name:                      

 ------------------------------- DESCRIPTION ---------------------------------

       This file will deal with the sub menus for AllModes.

------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "keypad.h"
#include "selctkey.h"
#include "beep.h"
#include "getmsg.h"
#include "ready.h"
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"
#include "dups_api.h"
#include "state.h"
#include "ticks.h"
#include "dups.h"
#include "command.h"
#include "UndefPrintf.h"
#include "stdio.h"
#include "command.h"
#include "battram.h"
#include "Events.h"
#include "util.h"

/*
 ----------------------------- EXTERNAL FUNCTIONS ----------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT16 RadioIndex;
extern BOOLEAN VerifyPresetRequired;

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT8 SetupFlag = FALSE;

UINT16 FlagPretriggerOff;
UINT16 FlagPretriggerAuto;
UINT16 FlagPretriggerTime;
UINT16 FlagPretriggerDist;
UINT16 FlagPretriggerAmpl;
UINT16 pretriggerMode;
UINT16 AmplitudeMode;
UINT16 PressureMode;

UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
UINT16 AmplitudeFixedEnableFlag;

UNION_BOOL_UINT16 PressureStepEnableFlag;
UINT16 PressureFixedEnableFlag;

UINT8  LimitChanged = FALSE;
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

#define AMPSTEPMASK 0xFFFE   /* Changed from 7C to FFFE V11.2.44 BEK 05-09-97 */
#define PRESSURESTEPMASK 0xFFFE

void ChangeDUPSSubParamList(void);
void SetupPretriggerFlags(void);
void SetupAmplitudeStepFlag(void);
void SetupPressureStepFlag(void);
void SetupAmpModeStepFlag(void);

/*
 ---------------------------------- CODE -------------------------------------
*/

void SetAmplitudeMode(void)
{
   if (AmplitudeMode == RADIO_0)
      CurrentPreset.Amp2Flag |= BIT0;
   if (AmplitudeMode == RADIO_1)
      CurrentPreset.Amp2Flag &= 0xFFFE;
   SetupAmplitudeStepFlag();
   UpdateCurrentPreset(AMPLITUDESTEPFLAG, NULL, NULL);
}

void SetAmplitudeModes(void)
{
   switch(RadioIndex){
   case 0:
      AmplitudeMode = RADIO_0;
      break;
   case 1:
      AmplitudeMode = RADIO_1;
      break;
   }

   if (AmplitudeMode == RADIO_0)
      CurrentPreset.Amp2Flag |= BIT0;
   if (AmplitudeMode == RADIO_1)
      CurrentPreset.Amp2Flag &= 0xFFFE;
   SetupAmpModeStepFlag();
}

void PrepareAmplitudeRadioMenu(void)
{
   AmplitudeMode = RADIO_0;
   RadioIndex    = 0;
   if ((CurrentPreset.Amp2Flag & BIT0) == BIT0)
   {
      AmplitudeMode = RADIO_0;
      RadioIndex = 0;
   } 
   else
   {
      AmplitudeMode = RADIO_1;
      RadioIndex = 1;
   } 
   RadioIndexOld = RadioIndex;
}

/***************************************************************************
*                                                                         
*   Purpose:
*                                                                          
*   This function is called before Pressure mode selection. Function
*   initialize RadioIndex based on the Pressure2 Flag.
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void PreparePressureRadioMenu(void)
{
   PressureMode = RADIO_0;
   RadioIndex    = 0;
   if ((CurrentPreset.Pressure2Flag & BIT0) == BIT0)
   {
      PressureMode = RADIO_0;
      RadioIndex = 0;
   }
   else
   {
      PressureMode = RADIO_1;
      RadioIndex = 1;
   }
   RadioIndexOld = RadioIndex;
}

/***************************************************************************
*                                                                         
*   Purpose:
*                                                                          
*   This function is called when Pressure mode is selected. Function
*   set Pressure2Flag bits based on the RadioIndex received from SBC
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SetPressureMode(void)
{
	if (PressureMode == RADIO_0)
      CurrentPreset.Pressure2Flag |= BIT0;
    if (PressureMode == RADIO_1)
      CurrentPreset.Pressure2Flag &= 0xFFFE;
    SetupPressureStepFlag();
}

void SetPressureModes(void)
{
	switch(RadioIndex){
    case 0:
         PressureMode = RADIO_0;
         break;
    case 1:
         PressureMode = RADIO_1;
         break;
    }

    if (PressureMode == RADIO_0)
       CurrentPreset.Pressure2Flag |= BIT0;
    if (PressureMode == RADIO_1)
       CurrentPreset.Pressure2Flag &= 0xFFFE;
    SetupPressureFixedOrStepFlag();
}

void SetSetupFlag(UINT32 MenuExtra)   /*  IT APPEARS SetupFlag IS NOT USED BEK 09-19-01 */
{
	MenuExtra = 0;
	SetupFlag = TRUE;
}


void ClearSetupFlag(void)
{
   SetupFlag = FALSE;
}

void SelectAmpTriggerTime(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) != /*AmpStepAtTime.BitMask*/BIT2)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtTime.BitMask*/BIT2)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGTIMEVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtTime.BitMask*/BIT2)) | BIT0;
}

void SelectAmpTriggerEnergy(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) != /*AmpStepAtEner.BitMask*/BIT3)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtEner.BitMask*/BIT3)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGENERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtEner.BitMask*/BIT3)) | BIT0;
}


void SelectAmpTriggerPower(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) != /*AmpStepAtPower.BitMask*/BIT4)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtPower.BitMask*/BIT4)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGPOWERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtPower.BitMask*/BIT4)) | BIT0;
}


void SelectAmpTriggerDist(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) != /*AmpStepAtDist.BitMask*/BIT5)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtDist.BitMask*/BIT5)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGDISTVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtDist.BitMask*/BIT5)) | BIT0;
}


void SelectAmpTriggerForce(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtForce.BitMask*/BIT6) != /*AmpStepAtForce.BitMask*/BIT6)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtForce.BitMask*/BIT6)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGFORCEVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtForce.BitMask*/BIT6)) | BIT0;
}


void SelectAmpTriggerExt(void)
{
   if(CurrentPreset.AmpTrigExtFlag == FALSE)
   {
      CurrentPreset.AmpTrigExtFlag = TRUE;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;                                                 
   }
   else if(CurrentPreset.AmpTrigExtFlag)
   {
      /* Disable all bits BIT0 enabled */
      CurrentPreset.Amp2Flag = (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT0);
      UpdateCurrentPreset(AMPTRIGEXTFLAG, NULL, NULL);
   }
   else if( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK)
           CurrentPreset.AmpTrigExtFlag = TRUE;
           
   VerifyPresetRequired = TRUE; 
}

void ChangeFreqOffsetSign(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when the "Change Sign(-,+)" line on the Frequency*/
/* Offset screen is selected.  It flips the sign of the variable containing */
/* the frequency offset, updates the preset, and causes the new value to be */
/* displayed on the screen.                                                 */
/*                                                                          */
/****************************************************************************/
{
   if (CurrentPreset.FreqOffset)
   {
      CurrentPreset.FreqOffset = -CurrentPreset.FreqOffset;
   }
   else
      Beep(ERRORBEEP);  /* If zero, can't change sign */
}



void ChangeDUPSSubParamList(void)
/****************************************************************************/
/*                                                                          */
/*  If any Recall preset is called prior, Update "DUPS_CurrentParamSet" from*/
/*  DUPS before downloading modified parameter set to the DUPS.             */
/*                                                                          */
/****************************************************************************/

{
   DUPS_QueuedDownloadPS();
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called when trigger at time is selected in Pressure
*   Stepping menu.Set bit for trigger at time.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SelectPressureTriggerTime(void)
{
   if ((CurrentPreset.Pressure2Flag & /*PressureStepAtTime.BitMask*/BIT2)
         != /*ForceStepAtTime.BitMask*/BIT2) {
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtTime.BitMask*/BIT2))
            | BIT0;
      CurrentPreset.PressureTrigExtFlag = FALSE;
   }
   else if (((CurrentPreset.Pressure2Flag & PRESSURESTEPMASK)
         == PRESSURESTEPMASK) && CurrentPreset.PressureTrigExtFlag == FALSE) {
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtTime.BitMask*/BIT2))
            | BIT0;
   }
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called when trigger at energy is selected in Pressure
*   Stepping menu.Set bit for trigger at energy.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SelectPressureTriggerEnergy(void)
{
   if ((CurrentPreset.Pressure2Flag & /*PressureStepAtEner.BitMask*/BIT3)
         != /*PressureStepAtEner.BitMask*/BIT3) {
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtEner.BitMask*/BIT3))
            | BIT0;
      CurrentPreset.PressureTrigExtFlag = FALSE;
   }
   else if (((CurrentPreset.Pressure2Flag & PRESSURESTEPMASK)
         == PRESSURESTEPMASK) && CurrentPreset.PressureTrigExtFlag == FALSE)
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtEner.BitMask*/BIT3))
            | BIT0;
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called when trigger at power is selected in Pressure
*   Stepping menu.Set bit for trigger at power.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SelectPressureTriggerPower(void)
{
   if ((CurrentPreset.Pressure2Flag & /*PressureStepAtPower.BitMask*/BIT4)
         != /*PressureStepAtPower.BitMask*/BIT4) {
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtPower.BitMask*/BIT4))
            | BIT0;
      CurrentPreset.PressureTrigExtFlag = FALSE;

   }
   else if (((CurrentPreset.Pressure2Flag & PRESSURESTEPMASK)
         == PRESSURESTEPMASK) && CurrentPreset.PressureTrigExtFlag == FALSE)
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtPower.BitMask*/BIT4))
            | BIT0;
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called when trigger at collapse distance is selected
*   in Pressure Stepping menu.Set bit for trigger at collapse distance.
*   And the other trigger points are set to OFF.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SelectPressureTriggerDist(void)
{
   if ((CurrentPreset.Pressure2Flag & /*PressureStepAtCol.BitMask*/BIT5)
         != /*PressureStepAtCol.BitMask*/BIT5) {
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtCol.BitMask*/BIT5))
            | BIT0;
      CurrentPreset.PressureTrigExtFlag = FALSE;
   }
   else if (((CurrentPreset.Pressure2Flag & PRESSURESTEPMASK)
         == PRESSURESTEPMASK) && CurrentPreset.PressureTrigExtFlag == FALSE)
      CurrentPreset.Pressure2Flag = (~(/*PressureStepAtCol.BitMask*/BIT5))
            | BIT0;
}

/***************************************************************************
*
*   Purpose:
*
*   This function is called when trigger at external signal is selected
*   in Pressure Stepping menu.Set bit for trigger at external signal.
*
*   Entry condition:
*  void
*
*   Exit condition:
*  void
*
***************************************************************************/
void SelectPressureTriggerExt(void)
{
   if (CurrentPreset.PressureTrigExtFlag == FALSE) {
      CurrentPreset.PressureTrigExtFlag = TRUE;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
   else if (CurrentPreset.PressureTrigExtFlag) {
      /* Disable all bits, BIT0 enabled */
      CurrentPreset.Pressure2Flag = (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT0);
   }
   else if ((CurrentPreset.Pressure2Flag & PRESSURESTEPMASK) == PRESSURESTEPMASK)
      CurrentPreset.PressureTrigExtFlag = TRUE;

   VerifyPresetRequired = TRUE;
}

void PreparePretriggerRadioMenu(void)
{
   pretriggerMode = RADIO_1;
   RadioIndex = 1;
   if (CurrentPreset.PreTrigFlag == FALSE)
      {
         pretriggerMode = RADIO_0;
         RadioIndex = 0;
      } 
   if (CurrentPreset.PreTriggerDistanceFlag == FALSE)
      {
         pretriggerMode = RADIO_2;
         RadioIndex = 2;
      }
   if (CurrentPreset.PreTrigDelayFlag == FALSE)
      {
         pretriggerMode = RADIO_3;
         RadioIndex = 3;
      }
   RadioIndexOld = RadioIndex;
}

void SetPretriggerModes(void)
{
   // default values - pretrigger auto, from there we change one bit for
   // any other pretrigger mode
   CurrentPreset.PreTrigFlag = TRUE;
   CurrentPreset.AutoTrigFlag = FALSE;
   CurrentPreset.PreTriggerDistanceFlag = TRUE;
   CurrentPreset.PreTrigDelayFlag = TRUE;
   switch(RadioIndex){
   case 0:
      pretriggerMode = RADIO_0;
      break;
   case 1:
      pretriggerMode = RADIO_1;
      break;
   case 2:
      pretriggerMode = RADIO_2;
      break;
   case 3:
      pretriggerMode = RADIO_3;
      break;
   }
   if (pretriggerMode == RADIO_0)
      CurrentPreset.PreTrigFlag = FALSE;
   if (pretriggerMode == RADIO_1)
      CurrentPreset.AutoTrigFlag = TRUE;
   if (pretriggerMode == RADIO_2)
      CurrentPreset.PreTriggerDistanceFlag = FALSE;
   if (pretriggerMode == RADIO_3)
      CurrentPreset.PreTrigDelayFlag = FALSE;
   SetupPretriggerFlags();
}

void SetPretriggerMode(void)
{
   // default values - pretrigger auto, from there we change one bit for
   // any other pretrigger mode
   CurrentPreset.PreTrigFlag = TRUE;
   CurrentPreset.AutoTrigFlag = FALSE;
   CurrentPreset.PreTriggerDistanceFlag = TRUE;
   CurrentPreset.PreTrigDelayFlag = TRUE;
   
   if (pretriggerMode == RADIO_0)
      CurrentPreset.PreTrigFlag = FALSE;
   if (pretriggerMode == RADIO_1)
      CurrentPreset.AutoTrigFlag = TRUE;
   if (pretriggerMode == RADIO_2)
      CurrentPreset.PreTriggerDistanceFlag = FALSE;
   if (pretriggerMode == RADIO_3)
      CurrentPreset.PreTrigDelayFlag = FALSE;
   SetupPretriggerFlags();
   UpdateCurrentPreset(PRETRIGDIST, NULL, NULL);
}

void GetPresetValidated()
{
	TempPresetValidated = FRAMPresetInfo[VGAPresetNum].Validated;
}

void SetPresetValidated()
{
	SETUPS_Ver1200* PresetPtr = Readpreset(VGAPresetNum);/*May be in flash or FRAM;*/
	char Data1[MAX_EVENTDATA_LEN];
   memset(Data1, 0 , sizeof(Data1));
	if(FRAMPresetInfo[VGAPresetNum].Verified == TRUE)
	{

		FRAMPresetInfo[VGAPresetNum].Validated = TempPresetValidated;
		if(FRAMPresetInfo[VGAPresetNum].Validated == TRUE){
		   //PresetPtr->Rev++; Incrementing rev in save preset
		   PresetRevValidationEvent = PresetPtr->Rev;
		   strncpy(PresetPtr->PSAssemblyNum, CurrentSetup.PSAssemblyNum, sizeof(PresetPtr->PSAssemblyNum) -  1);
		   strncpy(PresetPtr->ActAssemblyNum, CurrentSetup.ActAssemblyNum, sizeof(PresetPtr->ActAssemblyNum) -  1);
		   strncpy(PresetPtr->StackAssemblyNum, CurrentSetup.StackAssemblyNum, sizeof(PresetPtr->StackAssemblyNum) -  1);
		   Numout2(VGAPresetNum, 10, Data1, MAX_EVENTDATA_LEN - 1);
		   RecordEvents(EVENT_PRESETVALIDATION_BITSET, Data1, "");
		}
		else
		{
			PresetRevValidationEvent = PresetPtr->Rev;
			FRAMPresetInfo[VGAPresetNum].Locked = FALSE;
			Numout2(VGAPresetNum, 10, Data1, MAX_EVENTDATA_LEN - 1);
			RecordEvents(EVENT_PRESET_VALIDATION_BIT_CLEARED, Data1, "");
		}
		PresetRevValidationEvent = 0;
	    SavePreset(VGAPresetNum);//update the preset in FRAM or Flash as per preset number
		//If active preset is getting changed and no change has been made in active preset
		//update the validated and locked status as well as HW assemblies
		if((CurrentPreset.PresetUpdateComplete == TRUE) && (VGAPresetNum == CurrentSetup.ActivePreset)){
			//Ram Copy Of running and curr preset
			CurrentPreset.Validated = FRAMPresetInfo[VGAPresetNum].Validated;
			CurrentPreset.Rev = PresetPtr->Rev;
			CurrentPreset.Locked = FRAMPresetInfo[VGAPresetNum].Locked;
			RunningPreset.Validated = FRAMPresetInfo[VGAPresetNum].Validated;
			RunningPreset.Rev = PresetPtr->Rev;
			RunningPreset.Locked = FRAMPresetInfo[VGAPresetNum].Locked;
         strncpy(CurrentPreset.PSAssemblyNum, CurrentSetup.PSAssemblyNum, sizeof(CurrentPreset.PSAssemblyNum) -  1);
         strncpy(CurrentPreset.ActAssemblyNum, CurrentSetup.ActAssemblyNum, sizeof(CurrentPreset.ActAssemblyNum) -  1);
         strncpy(CurrentPreset.StackAssemblyNum, CurrentSetup.StackAssemblyNum, sizeof(CurrentPreset.StackAssemblyNum) -  1);
         strncpy(RunningPreset.PSAssemblyNum, CurrentSetup.PSAssemblyNum, sizeof(RunningPreset.PSAssemblyNum) -  1);
         strncpy(RunningPreset.ActAssemblyNum, CurrentSetup.ActAssemblyNum, sizeof(RunningPreset.ActAssemblyNum) -  1);
         strncpy(RunningPreset.StackAssemblyNum, CurrentSetup.StackAssemblyNum, sizeof(RunningPreset.StackAssemblyNum) -  1);
			WritePreset(CURRENT_PRESET_INDEX, FALSE);	/* Save Current Preset */	
		}
	}
	else
		TempPresetValidated = FALSE;


}

void GetPresetLocked()
{
	TempPresetLocked = FRAMPresetInfo[VGAPresetNum].Locked;
}

void SetPresetLocked()
{
	if((TempPresetLocked == FALSE) || ((TempPresetLocked == TRUE) && (FRAMPresetInfo[VGAPresetNum].Validated == TRUE)))
	{
		FRAMPresetInfo[VGAPresetNum].Locked = TempPresetLocked;
		 //If active preset is getting changed update the validated and locked status in current preset slot
		if(VGAPresetNum == CurrentSetup.ActivePreset){
			CurrentPreset.Locked = FRAMPresetInfo[VGAPresetNum].Locked;
			RunningPreset.Locked = FRAMPresetInfo[VGAPresetNum].Locked;
			WritePreset(CURRENT_PRESET_INDEX);  /* Save Current Preset */
		}
	}
	else
		TempPresetLocked = FALSE;
}

void UpdateWS_Config(void)
{
  if(CurrentPreset.WeldStatusFlag)
  UpdateSWConfiguration(WS,TRUE);
  else
  UpdateSWConfiguration(WS,FALSE);
}  
