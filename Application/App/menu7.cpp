/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu7.cpp_v   1.23   Jun 07 2017 13:44:38   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu7.cpp_v  $
 * 
 *    Rev 1.23   Jun 07 2017 13:44:38   RJamloki
 * Fixes from code review 5/29/2017 bucket 3
 * 
 *    Rev 1.22   Jun 07 2017 13:28:26   RJamloki
 * Fix case default stament in the end
 * 
 *    Rev 1.21   09 May 2016 14:51:40   RJamloki
 * Updated GetRS232Index & SetRS232Index functionality
 * 
 *    Rev 1.20   16 Apr 2015 07:26:06   rjamloki
 * PartClamp output status is deactivated as soon as both input and output clamp signals are configured.
 * 
 *    Rev 1.19   27 Mar 2015 11:08:48   amaurya
 * DoorOpen Removed
 * 
 *    Rev 1.18   11 Mar 2015 09:16:50   amaurya
 * INPUT_REJECT_ALARM changed to INPUT_CONFIRM_REJECT.
 * 
 *    Rev 1.17   11 Feb 2015 06:37:10   amaurya
 * GetInput() and SetInputSelection() function changed for reject confirm input
 * 
 *    Rev 1.16   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.15   28 Nov 2014 07:37:52   rjamloki
 * VGAResetWeldCounterOk () changed to remove record event of EVENT_PARAMETER_CHANGED_ONVALIDATEDPS.
 * 
 *    Rev 1.14   11 Nov 2014 06:08:30   AnPawar
 * Removed extra event as WeldCount clear is parameter change event
 * 
 *    Rev 1.13   03 Oct 2014 06:10:02   rjamloki
 *  UserCfgOutputOn(OUTPUT_AMPDECAY) removed
 * 
 *    Rev 1.12   26 Sep 2014 03:35:40   rjamloki
 * Removed J38 and J336 swapping
 * 
 *    Rev 1.11   11 Sep 2014 11:01:30   rjamloki
 * Added weld counter clear event
 * 
 *    Rev 1.10   28 Jul 2014 12:36:40   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   15 Jul 2014 18:04:12   hasanchez
 * Changes about configurable outputs
 * 
 *    Rev 1.8   09 Jul 2014 10:56:42   rjamloki
 * SvInterlock renamed to PartClamp
 * 
 *    Rev 1.7   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:09:34   rjamloki
 * extern variables clean up and coverity fixes
 * 
 *    Rev 1.4   05 Mar 2014 13:56:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:44   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:36   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu7.c

   Function name:

 ------------------------------- DESCRIPTION ---------------------------------
 
   This file will deal with System Options, such as language, beepers,
   units, printer setup, etc.

 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include "time.h"
#include "menu.h"
#include "menu0.h"
#include "display.h"
#include "preset.h"
#include "param.h"
#include "psnvram.h"
#include "selctkey.h"
#include "weld_obj.h"
#include "rtclock.h"
#include "menu7a.h"
#include "ready.h"
#include "alarms.h"
#include "keypad.h"
#include "getmsg.h"
#include "serial.h"
#include "graphs.h"
#include "statedrv.h"
#include "rdyweld1.h"
#include "inports.h"
#include "outports.h"
#include "beep.h"
#include "digout.h"
#include "battram.h"
#include "command.h"
#include "Events.h"
/* ----------------------------- EXTERNAL DATA ------------------------------ */

extern UINT16  RadioIndex;
extern INBITS Inp;
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UINT16 AmplitudeFixedEnableFlag;

/*--------------------------- EXTERNAL FUNCTIONS ----------------------------*/

BOOLEAN* GetInputPtr(UINT16 InputBit);

/*------------------------------ GLOBAL DATA --------------------------------*/
/*                     (scope is global to ALL files)                        */


UNION_BOOL_UINT16 AmpControlInternal;
UINT16 AmpCntrlExt;
UINT16 AmpCntrlInt;
UNION_BOOL_UINT16 FreqControlInternal;
UINT16 FreqControlExternal;
UINT16 FreqControlInt,EnableStepForce;
UINT16 LanguageChanged;
BOOLEAN VerifyPresetRequired = FALSE;
BOOLEAN DispLockConfigured;
BOOLEAN PartPresentConfigured;
UINT16 HHInactive1 =FALSE;

/* The following variable will be replaced by a legit variable later on */

SINT32 WelderAddrMinValue = 1;
SINT32 WelderAddrMaxValue = 9999;


/*--------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                     (scope is global to THIS file)                        */
   

enum INPUT_PINS ActiveInput;                      /* Contains enum of currently changing I/O */
enum OUTPUT_PINS ActiveOutput;                    /* Contains enum of currently changing I/O */
UINT16 GlobalInputs, GlobalOutputs;               /* Contains bit assignment for current I/O */
UINT16 OutputPin;
/*---------------------------------- CODE ----------------------------------*/


void GetInput(void)
/****************************************************************************/
/* Retrieve original selection for selected input based on CommandID        */
/* so menu can display the proper selection.                                */
/****************************************************************************/
{
   switch (GlobalCommandID) {
   case J3_32IN:
      GlobalInputs = CurrentSetup.J3_32In;
      break;

   case J3_33IN:
      GlobalInputs = CurrentSetup.J3_33In;
      break;

   case J3_19IN:
      GlobalInputs = CurrentSetup.J3_19In;
      break;

   case J3_17IN:
      GlobalInputs = CurrentSetup.J3_17In;
      break;

   case J3_31IN:
      GlobalInputs = CurrentSetup.J3_31In;
      break;

   case J3_1IN:
      GlobalInputs = CurrentSetup.J3_1In;
      break;
   }

   switch (GlobalInputs) {
   case INPUT_DISABLED:
      RadioIndex = 0;
      break;

   case INPUT_PRESET1:
      RadioIndex = 1;
      break;

   case INPUT_PRESET2:
      RadioIndex = 2;
      break;

   case INPUT_PRESET3:
      RadioIndex = 3;
      break;

   case INPUT_PRESET4:
      RadioIndex = 4;
      break;

   case INPUT_PRESET5:
      RadioIndex = 5;
      break;

   case INPUT_EXT_TRIGDELAY:
      RadioIndex = 6;
      break;

   case INPUT_DISP_LOCK:
      RadioIndex = 7;
      break;

   case INPUT_EXT_TRIGGER:
      RadioIndex = 8;
      break;

   case INPUT_SONICS_DISABLE:
      RadioIndex = 9;
      break;

   case INPUT_MEM_RESET:
      RadioIndex = 10;
      break;

   case INPUT_PART_CLAMPED:
      RadioIndex = 11;
      break;

   case INPUT_SYNC_IN:
      RadioIndex = 12;
      break;
   case INPUT_PART_PRESENT:
      RadioIndex = 13;
      break;
   case INPUT_CONFIRM_REJECT:
         RadioIndex = 14;
         break;
   }

}

void SetInputSelection(void)
/****************************************************************************/
/* This function takes the current selection in GlobalInputs according to   */
/* RadioIndex and moves it to the proper Input register based on funcID.    */
/****************************************************************************/
{
   switch (RadioIndex) {
   case 0:
      GlobalInputs = INPUT_DISABLED;
      break;

   case 1:
      GlobalInputs = INPUT_PRESET1;
      break;

   case 2:
      GlobalInputs = INPUT_PRESET2;
      break;

   case 3:
      GlobalInputs = INPUT_PRESET3;
      break;

   case 4:
      GlobalInputs = INPUT_PRESET4;
      break;

   case 5:
      GlobalInputs = INPUT_PRESET5;
      break;

   case 6:
      GlobalInputs = INPUT_EXT_TRIGDELAY;
      break;

   case 7:
      GlobalInputs = INPUT_DISP_LOCK;
      break;

   case 8:
      GlobalInputs = INPUT_EXT_TRIGGER;
      break;

   case 9:
      GlobalInputs = INPUT_SONICS_DISABLE;
      break;

   case 10:
      GlobalInputs = INPUT_MEM_RESET;
      break;

   case 11:
      GlobalInputs = INPUT_PART_CLAMPED;
      break;

   case 12:
      GlobalInputs = INPUT_SYNC_IN;
      break;

   case 13:
      GlobalInputs = INPUT_PART_PRESENT;
      break;

   case 14:
	  GlobalInputs = INPUT_CONFIRM_REJECT;
	  break;
   }

   switch (GlobalCommandID) {
   case J3_32IN:
      CurrentSetup.J3_32In = GlobalInputs;
      CurrentSetup.J3_32Ptr = GetInputPtr(GlobalInputs);
      break;

   case J3_33IN:
      CurrentSetup.J3_33In = GlobalInputs;
      CurrentSetup.J3_33Ptr = GetInputPtr(GlobalInputs);
      break;

   case J3_19IN:
      CurrentSetup.J3_19In = GlobalInputs;
      CurrentSetup.J3_19Ptr = GetInputPtr(GlobalInputs);
      break;

   case J3_17IN:
      CurrentSetup.J3_17In = GlobalInputs;
      CurrentSetup.J3_17Ptr = GetInputPtr(GlobalInputs);
      break;

   case J3_31IN:
      CurrentSetup.J3_31In = GlobalInputs;
      CurrentSetup.J3_31Ptr = GetInputPtr(GlobalInputs);
      break;

   case J3_1IN:
      CurrentSetup.J3_1In = GlobalInputs;
      CurrentSetup.J3_1Ptr = GetInputPtr(GlobalInputs);
      break;
   }
   VerifyPresetRequired = TRUE;
   //Reset part clamp output if configured as default value.
   if (IsConfigured(INPUT_PART_CLAMPED) && IsOutConfigured(OUTPUT_PART_CLAMPED))
	   PartClampOutOff();
}

void UpdateAllUserOutputs(void)
/****************************************************************************/
/*  This function will cycle through all user defind functions and adjust   */
/*  the output pin that is assigned to that function. This should be called */
/*  at power up and any time a pin is assigned to a different function or   */
/*  disabled.                                                               */
/****************************************************************************/
{
   UserCfgOutputOn(OUTPUT_DISABLED);
   UserCfgOutputOn(OUTPUT_CFMPRESET);
   UserCfgOutputOff(OUTPUT_EXT_BEEPER);
   UserCfgOutputOn(OUTPUT_CYCLE_OK);
   UserCfgOutputOn(OUTPUT_NO_CYCLEALARM);
   UserCfgOutputOff(OUTPUT_OLDALARM);
   UserCfgOutputOn(OUTPUT_MDFY_ALARM);
   UserCfgOutputOn(OUTPUT_NOTE);
   UserCfgOutputOn(OUTPUT_MISSING_PART);
   UserCfgOutputOn(OUTPUT_PART_CLAMPED);
   UserCfgOutputOn(OUTPUT_SYNC_OUT);
   UserCfgOutputOn(OUTPUT_UDIREADY);
}

void SetOutPinAccordtoBoard(void)
/****************************************************************************/
/* This function sets output pin according to new or old controller         */
/* board.                                                                   */
/****************************************************************************/
{
      if (GlobalCommandID == J3_8OUT)
         OutputPin = J3PIN8;
      else if (GlobalCommandID == J3_36OUT)
         OutputPin = J3PIN36;
      else
         OutputPin = J3PIN22;
}

void GetOutput(void)
/****************************************************************************/
/* Retrieve original selection for selected output based on CommandID       */
/* so menu can display the proper selection.                                */
/****************************************************************************/
{
   SetOutPinAccordtoBoard();
   switch (OutputPin) {
   case J3PIN36:
      GlobalOutputs = CurrentSetup.J3_36Out;
      break;

   case J3PIN8:
      GlobalOutputs = CurrentSetup.J3_8Out;
      break;

   case J3PIN22:
      GlobalOutputs = CurrentSetup.J3_22Out;
      break;
   }

   switch (GlobalOutputs) {
   case OUTPUT_DISABLED:
      RadioIndex = 0;
      break;

   case OUTPUT_CFMPRESET:
      RadioIndex = 1;
      break;

   case OUTPUT_EXT_BEEPER:
      RadioIndex = 3;
      break;

   case OUTPUT_CYCLE_OK:
      RadioIndex = 4;
      break;

   case OUTPUT_NO_CYCLEALARM:
      RadioIndex = 5;
      break;

   case OUTPUT_OLDALARM:
      RadioIndex = 6;
      break;

   case OUTPUT_MDFY_ALARM:
      RadioIndex = 7;
      break;

   case OUTPUT_NOTE:
      RadioIndex = 8;
      break;

   case OUTPUT_MISSING_PART:
      RadioIndex = 9;
      break;

   case OUTPUT_PART_CLAMPED:
      RadioIndex = 10;
      break;

   case OUTPUT_SYNC_OUT:
      RadioIndex = 11;
      break;
   case OUTPUT_UDIREADY:
      RadioIndex = 12;
      break;
   }
}

void SetOutputSelection(void)
/***************************************************************************/
/* This function takes the current selection in GlobalOutputs according to */
/* RadioIndex and moves it to the proper Output register based on funcID.  */
/***************************************************************************/
{
   switch (RadioIndex) {
   case 0:
      GlobalOutputs = OUTPUT_DISABLED;
      break;

   case 1:
      GlobalOutputs = OUTPUT_CFMPRESET;
      break;

   case 3:
      GlobalOutputs = OUTPUT_EXT_BEEPER;
      break;

   case 4:
      GlobalOutputs = OUTPUT_CYCLE_OK;
      break;

   case 5:
      GlobalOutputs = OUTPUT_NO_CYCLEALARM;
      break;

   case 6:
      GlobalOutputs = OUTPUT_OLDALARM;
      break;

   case 7:
      GlobalOutputs = OUTPUT_MDFY_ALARM;
      break;

   case 8:
      GlobalOutputs = OUTPUT_NOTE;
      break;

   case 9:
      GlobalOutputs = OUTPUT_MISSING_PART;
      break;

   case 10:
      GlobalOutputs = OUTPUT_PART_CLAMPED;
      break;

   case 11:
      GlobalOutputs = OUTPUT_SYNC_OUT;
      break;
   case 12:
      GlobalOutputs = OUTPUT_UDIREADY;
      break;
   }
   SetOutPinAccordtoBoard();
   switch (OutputPin) {
   case J3PIN36:
      CurrentSetup.J3_36Out = GlobalOutputs;
      break;

   case J3PIN8:
      CurrentSetup.J3_8Out = GlobalOutputs;
      break;

   case J3PIN22:
      CurrentSetup.J3_22Out = GlobalOutputs;
      break;
   }
   UpdateAllUserOutputs();
   VerifyPresetRequired = TRUE;
   //Rest Part Clamp output if configured as default value.
   if (IsConfigured(INPUT_PART_CLAMPED) && IsOutConfigured(OUTPUT_PART_CLAMPED))
	   PartClampOutOff();
}

void GetPSFreq(void) {
   switch (CurrentSetup.PSFreq) {
   case FREQ15KHZ:
      RadioIndex = 0;
      break;
   case FREQ20KHZ:
      RadioIndex = 1;
      break;
   case FREQ30KHZ:
      RadioIndex = 2;
      break;
   case FREQ40KHZ:
      RadioIndex = 3;
      break;
   case FREQ60KHZ:
      RadioIndex = 4;
      break;
   default:
      RadioIndex = 1;
      break;
   }
}

void SetPSFrequency(void) {
   switch (RadioIndex) {
   case 0:
      CurrentSetup.PSFreq = FREQ15KHZ;
      break;
   case 1:
      CurrentSetup.PSFreq = FREQ20KHZ;
      break;
   case 2:
      CurrentSetup.PSFreq = FREQ30KHZ;
      break;
   case 3:
      CurrentSetup.PSFreq = FREQ40KHZ;
      break;
   case 4:
      CurrentSetup.PSFreq = FREQ60KHZ;
      break;
   default:
      CurrentSetup.PSFreq = FREQ20KHZ;
      break;
   }
   StorePSFrequency();
   SetMaxMinValues(); /* Update Min/Max based on new setting */
}

void GetRS232Index(void)
/*****************************************************************************/
/*  This function will convert the bit assignment in CurrentSetup.SerialPort */
/*  to an index so the proper selection will be displayed when RADIOMENU is  */
/*  called.                                                                  */
/*                                                                           */
/*  Entry condition:                                                         */
/*	void                                                                     */
/*                                                                           */
/*  Exit condition:                                                          */
/*	void                                                                     */
/*****************************************************************************/
{
	   switch (CurrentSetup.SerialPort) {
	   case ASCIICOMMA:
	      RadioIndex = ZERO;
	      break;
	   case ASCIITAB:
	      RadioIndex = ONE;
	      break;
	   case ASCIISPACE:
	      RadioIndex = TWO;
	      break;
	   case RS232DISABLED:
	   default:
		  RadioIndex = THREE;
	   }
}

void SetRS232Index(void)
/*****************************************************************************/
/*  This function handles turning on and off the terminal and                */
/*  the ASCII output choices.  This is called from the menu system           */
/*  whenever a change is made to the serial port and what it is connected to.*/
/*  There are no arguments.  It uses the global in CurrentSetup.SerialPort   */
/*  to decide what to do.                                                    */
/*                                                                           */
/*  Entry condition:                                                         */
/*	void                                                                     */
/*                                                                           */
/*  Exit condition:                                                          */
/*	void                                                                     */
/*****************************************************************************/
{
   switch (RadioIndex) {
   case ZERO:
       CurrentSetup.SerialPort = ASCIICOMMA;
       break;
   case ONE:
       CurrentSetup.SerialPort = ASCIITAB;
       break;
   case TWO:
       CurrentSetup.SerialPort = ASCIISPACE;
       break;
   case THREE:
   default:
       CurrentSetup.SerialPort = RS232DISABLED;
   }
}

void SetAmpControlValue(void) {
   if (CurrentSetup.AmpControl == FALSE) /* FALSE if external control */
   {
      AmpControlInternal.boolEAN = FALSE;
      AmpCntrlExt = TRUE;
      VerifyPresetRequired = TRUE;
      AmpCntrlInt = FALSE;
      AmplitudeFixedEnableFlag = FALSE;
      AmplitudeStepEnableFlag.boolEAN = FALSE;
      AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
   } else {
      if ((CurrentPreset.Amp2Flag & BIT0) == TRUE) {
         AmplitudeFixedEnableFlag = FALSE;
         AmplitudeStepEnableFlag.boolEAN = TRUE;
         AmplitudeStepEnableFlag.Uint16.Hi = TRUE;
      } else {
         AmplitudeFixedEnableFlag = TRUE;
         AmplitudeStepEnableFlag.boolEAN = FALSE;
         AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
      }
      AmpControlInternal.boolEAN = TRUE;
      AmpCntrlExt = FALSE;
      AmpCntrlInt = TRUE;
   }
}

void SetAmpControl(void) {
   if (CurrentSetup.AmpControl == FALSE) /* FALSE if external control */
   {
      AmpControlInternal.boolEAN = FALSE;
      AmpCntrlExt = TRUE;
      VerifyPresetRequired = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
      AmplitudeStepEnableFlag.boolEAN = FALSE;
      AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
   } else {
      if ((CurrentPreset.Amp2Flag & BIT0) == TRUE) {
         AmplitudeFixedEnableFlag = FALSE;
         AmplitudeStepEnableFlag.boolEAN = TRUE;
         AmplitudeStepEnableFlag.Uint16.Hi = TRUE;
      } else {
         AmplitudeFixedEnableFlag = TRUE;
         AmplitudeStepEnableFlag.boolEAN = FALSE;
         AmplitudeStepEnableFlag.Uint16.Hi = FALSE;
      }
      AmpControlInternal.boolEAN = TRUE;
      AmpCntrlExt = FALSE;
   }
}

void SetFreqControlValue(void) {
   if (CurrentSetup.FreqControl == FALSE) /* FALSE if external control */
   {
      FreqControlInternal.boolEAN = FALSE;
      FreqControlExternal = TRUE; /* Menu needs this to display >Ext line */
      FreqControlInt = FALSE;
   } else {
      FreqControlInternal.boolEAN = TRUE;
      FreqControlExternal = FALSE;
      FreqControlInt = TRUE;
   }
}

void SetFreqControl(void) {
   if (CurrentSetup.FreqControl == FALSE) /* FALSE if external control */
   {
      FreqControlInternal.boolEAN = FALSE;
      FreqControlExternal = TRUE; /* Menu needs this to display >Ext line */
   } else {
      FreqControlInternal.boolEAN = TRUE;
      FreqControlExternal = FALSE;
   }
}

void ProduceBeep(void) {
   if (GlobalCommandID == AMP_CNTL_SET)
      CurrentSetup.AmpControl = FALSE;
   if(GlobalCommandID == FREQ_CNTL_SET)
   if (GlobalCommandID == FREQ_CNTL_SET)
   
   NackError = WELDER_PROCESS_ERROR;
   ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
   ErrorResponseMaxLimit = 0;
}

void DealWithExtPresetChange(void)
/****************************************************************************/
/*                                                                          */
/* This function Update the 'SWConfiguration' for external preset selection */
/* on powerup or when the ExtPreset value is changed.                       */
/*                                                                          */
/****************************************************************************/
{
   if (CurrentSetup.ExtPresets)
      UpdateSWConfiguration(EP_E, TRUE);  /* ExtPreset enabled */
   else
      UpdateSWConfiguration(EP_E, FALSE); /* ExtPreset disabled */
   
}


void UpdateRunTopLine(void)
/****************************************************************************/
/*                                                                          */
/* Issues a call to UpdateCurrentPreset(), which will cause the top line of */
/* the run screen to be updated.  This function is called when Units are    */
/* changed, because this affects what's shown on the run screen.  The Weld  */
/* Manager is responsible for updating this text, so we have to get an      */
/* OP_HERE_IS_PRESET sent to it, even though the preset itself hasn't       */
/* actually changed.                                                        */
/*                                                                          */
/****************************************************************************/
{
   UpdateCurrentPreset(WELDMODE, 0, 0);
}                                      

void VGAResetWeldCounterOk(void)
/****************************************************************************/
/*Description:                                                              */
/*  Refresh the Weld counter variable in case of pressing Ok button on the  */
/*  Confirm Screen.                                                         */
/****************************************************************************/
{
   UINT32 OldVal = CurrentPreset.WeldCount;
   WeldingResults.CycleCount = 0;
   CurrentPreset.WeldCount = 0;
   UpdateCurrentPresetAndSetup((PARAM)0);//Passing 0 as it should not cause preset to go invalidated
   if(OldVal)
   {
		RecordEvents(EVENT_PARAMETER_CHANGED, OldVal, CurrentPreset.WeldCount);
   }
}

void SetBeeperCondition (void)
{
   if(CurrentSetup.HandHeld == TRUE)
      HHInactive1 = FALSE;
   else
      HHInactive1 = TRUE;
}

BOOLEAN* GetInputPtr(UINT16 InputBit)
/********************************************************************/
/*  This funtion will return a pointer to the member of INBITS      */
/*  structure, selcted on the input pin.This function will be called*/ 
/*  when the input is defined to the port pin.                      */
/********************************************************************/
{
	static BOOLEAN TempBolleanVar;//define some storage for return value if none of the case passes
 	BOOLEAN *RetVal = &TempBolleanVar;

    switch (InputBit)
    {
        case INPUT_DISABLED:
           RetVal = &Inp.BitBucket;
           break;
        case INPUT_PRESET1:
        /* If 'Select Preset1' is selcted to J3_32 port pin.*/
           RetVal = &Inp.Preset1;
           break;
        case INPUT_PRESET2:
        /* If 'Select Preset2' is selcted to J3_33 port pin.*/
           RetVal = &Inp.Preset2;
           break;       
        case INPUT_PRESET3:
        /* If 'Select Preset4' is selcted to J3_19 port pin.*/
           RetVal = &Inp.Preset4;
           break;       
        case INPUT_PRESET4:
        /* If 'Select Preset8' is selcted to J3_17 port pin.*/
           RetVal = &Inp.Preset8;
           break;       
        case INPUT_PRESET5:
        /* If 'Select Preset16' is selcted to J3_31 port pin.*/
           RetVal = &Inp.Preset16;
           break;       
        case INPUT_EXT_TRIGDELAY:
        /* Return External Trigger Delay pointer */
           RetVal = &Inp.ExtTrgDelay;
           break; 
        case INPUT_DISP_LOCK:
        /* Return DisplayLock pointer */
           RetVal = &Inp.DisplayLockFlag;
           break;     
        case INPUT_EXT_TRIGGER:
        /* Return External Trigger pointer. */
           RetVal = &Inp.ExternalTrigger;
           break;
        case INPUT_SONICS_DISABLE:
        /* Return SonicDisable pointer*/
           RetVal = &Inp.SonicDisable;
           break;
        case INPUT_MEM_RESET:
        /* Return Menmory Reset pointer. */
           RetVal = &Inp.MemReset;
           break;     
        case INPUT_PART_CLAMPED:
        /* Return PartClamped pointer. */
           RetVal = &Inp.PartClamped;
           break;
        case INPUT_SYNC_IN:
        /* Return Sync In pointer. */
           RetVal = &Inp.SyncIn;
           break;
        case INPUT_PART_PRESENT:
		/* Return PartPresent pointer. */
		   RetVal = &Inp.PartPresent;
		   break;
        case INPUT_CONFIRM_REJECT:
		/* Return RejectAlarm pointer. */
		   RetVal = &Inp.ConfirmReject;
		   break;
      }
      DispLockConfigured = IsConfigured(INPUT_DISP_LOCK);
      PartPresentConfigured = IsConfigured(INPUT_PART_PRESENT);
      
      return (RetVal);
}

void CheckForCustomAct (void)
/****************************************************************************/
/* This function Update the 'CustomAct' when the UpperLimitSwitch or Ground */
/* DetectSwitch default logic level(0V) is inverted to 24V.                 */
/****************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   if((CurrentSetup.ULSLogicCustom) &&  /* Check for ULS & GndDet default logic level.*/
      (CurrentSetup.GndDetLogicCustom))
      CurrentSetup.CustomAct = FALSE;/* Custom actuator is not configured. */
   else
      CurrentSetup.CustomAct = TRUE; /* Custom actuator is configured. */
   FRAMPtr->CustomAct = CurrentSetup.CustomAct;
}
                                   
/**************************************************************************/
/*===============================END =====================================*/
/**************************************************************************/


