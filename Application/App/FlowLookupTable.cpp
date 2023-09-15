/*
 $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FlowLookupTable.cpp_v   1.37   Nov 29 2017 12:12:58   RJamloki  $
 */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 2015                    */
/*   This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FlowLookupTable.cpp_v  $
 * 
 *    Rev 1.37   Nov 29 2017 12:12:58   RJamloki
 * Update 1.5" & 2"  formula for normal sunrise actuator
 * 
 *    Rev 1.36   Nov 16 2017 14:41:20   RJamloki
 * Arrange lookup table formulas and coding option for micro c actuator
 * 
 *    Rev 1.35   Nov 07 2017 15:14:08   RJamloki
 * Added formula condition adjustment for FLOWLOOKUP
 * 
 *    Rev 1.34   Nov 06 2017 13:52:46   RJamloki
 * Arrange hard code issues in micro c formula code
 * 
 *    Rev 1.33   Oct 09 2017 16:06:02   RJamloki
 * Update Mexico and china flow control formulas for micro c
 * 
 *    Rev 1.32   Jun 07 2017 16:45:08   RJamloki
 * Fixes from code review 5/29/2017 bucket 3
 * 
 *    Rev 1.31   Jun 07 2017 13:01:32   RJamloki
 * Update small flow valve config variable
 * 
 *    Rev 1.30   May 31 2017 14:52:02   RJamloki
 * Apply code review standard to small flow valve formula
 * 
 *    Rev 1.29   May 29 2017 13:59:10   RJamloki
 * Added small flow vale macro formula
 * 
 *    Rev 1.28   May 25 2017 17:14:56   RJamloki
 * Applying small valve formula for 15% downspeed offset
 * 
 *    Rev 1.27   30 Apr 2015 12:07:14   rjamloki
 * Setting DownspeedTuneCycles to 0 on speed up and speed down clicks to force down speed cycle before Save button gets enabled on tuning menu
 * 
 *    Rev 1.26   16 Apr 2015 07:21:36   rjamloki
 * Removed static from PushPopPresetValues function as it needs to be called after esotp generated during down speed tuning
 * 
 *    Rev 1.25   09 Apr 2015 05:13:28   RJamloki
 * Tweak up/down functions remaned to speed up/down
 * 
 *    Rev 1.24   01 Apr 2015 13:02:06   amaurya
 * PushPopPresetValues() function change to support cycling at downspeed tuning screen if udi is enabled.
 * 
 *    Rev 1.23   27 Mar 2015 11:07:02   amaurya
 * Updated comment as per code review.
 * 
 *    Rev 1.22   16 Mar 2015 05:51:52   rjamloki
 * Corrected ExitDownSpeedTuneHd to not update running preset
 * 
 *    Rev 1.21   13 Mar 2015 06:07:06   amaurya
 * Comments added for UpdateFlowHD(),SetDownspeedTuneFlagHD(),SaveDownSpeedTuneHD(),ExitDownSpeedTuneHD(),TweakUpHD(),TweakDownHD() as per Branson coding standard.
 * 
 *    Rev 1.19   16 Feb 2015 01:15:06   amaurya
 * change in TweakUp and TweakDown functions to display correct downspeed
 * 
 *    Rev 1.18   11 Feb 2015 06:34:52   amaurya
 * change in tweakup function
 * 
 *    Rev 1.17   03 Feb 2015 07:22:22   amaurya
 *  SetDownspeedTuneFlag() changed for downspeed change event.
 * 
 *    Rev 1.16   02 Feb 2015 07:08:14   amaurya
 * Changed to log event on Value changed only.
 * 
 *    Rev 1.15   30 Jan 2015 08:09:56   amaurya
 * SaveDownSpeedTune() changed to prepare event on holdpressure change.
 * 
 *    Rev 1.14   08 Jan 2015 03:01:46   AnPawar
 * removed arrays DownspeedLUT3in and DownspeedLUT2_5in because now flowvalue calculation is cylinder independent
 * 
 *    Rev 1.13   02 Jan 2015 04:01:58   rjamloki
 * PushPopPresetValues() function changed to disable sequencing and external presets on tuning screen
 * 
 *    Rev 1.12   12 Dec 2014 05:29:32   RJamloki
 * Added support for TweakUp and Down from tuning menu
 * 
 *    Rev 1.11   28 Nov 2014 07:35:16   rjamloki
 * RealHoldTimeFlag - unused variable removed.
 * 
 *    Rev 1.10   14 Nov 2014 10:23:40   AnPawar
 * changes for automated down speed tuning and horn down screen
 * 
 *    Rev 1.9   14 Nov 2014 05:29:32   rjamloki
 * etDownspeedTuneFlag() changed.EXIT_HD macro added.
 * 
 *    Rev 1.8   12 Nov 2014 17:04:16   tayars
 * Made fix to use the preset values for tuning instead of predefined values.
 * 
 *    Rev 1.7   03 Nov 2014 11:45:50   tayars
 * Changes for code review.
 * 
 *    Rev 1.6   03 Oct 2014 06:05:48   rjamloki
 * included file digout.h and SaveDownSpeedTune() and ExitDownSpeed() functions changed
 * 
 *    Rev 1.5   25 Sep 2014 14:09:30   tayars
 * Made correction to fix preset recall downspeed issue. Also added some changes to the algorithm for small cylinder sizes.
 * 
 *    Rev 1.4   11 Sep 2014 14:30:56   tayars
 * Added support for all cylinder sizes.
 * Also tweaked the UpdateFlow algorithm to make smaller step changes as the Proportional loop approaches the target.
 * 
 *    Rev 1.3   05 Sep 2014 04:43:50   rjamloki
 * Added tune ability while cycling fast
 * 
 *    Rev 1.2   18 Aug 2014 09:31:44   rjamloki
 * Added StartStateMachine call on DownSpeed tune save ad exit.
 * 
 *    Rev 1.1   07 Aug 2014 16:08:34   tayars
 * Fixed compile error.
 */

#include "menu7a.h"
#include "ready.h"
#include "portable.h"
#include "actnvram.h"
#include "FlowLookupTable.h"
#include "stdio.h"
#include "statedrv.h"
#include "digout.h"
#include "menu.h"
#include "menuhorn.h"
#include "Events.h"
#include "selctkey.h"
#include "beep.h"
#include "limits.h"
#include "mansensr.h"

extern UINT16 DryCycleFlag;
extern SINT32 SetFlowValue;
extern SINT32 LastDownSpeedValue;

extern void SelectWeldSequence();
extern void SelectTimeWeldSequence();
extern void UpdateRPreset();
#define EXIT_HD        1   /* Causes exit from HD mode */
#define ROUNDED_20PSI_INDEX                  0
#define ROUNDED_40PSI_INDEX                  1
#define ROUNDED_60PSI_INDEX                  2
#define ROUNDED_80PSI_INDEX                  3
#define PSI_30                               300
#define PSI_50                               500
#define PSI_70                               700
#define TWO_SECONDS                          2000
#define LARGE_LEAP_CUTOFF                    100
#define WAY_LOW                              -100
#define WAY_HIGH                             100
#define SLIGHTLY_HIGH                        20
#define SLIGHTLY_LOW                         -20
#define MAX_FLOW_VALUE                       125
#define LARGE_FLOW_CHANGE_BIGGER_CYLINDER    20
#define LARGE_FLOW_CHANGE_SMALL_CYLINDER     9
#define SMALL_FLOW_CHANGE_BIGGER_CYLINDER    5
#define SMALL_FLOW_CHANGE_SMALL_CYLINDER     1
#define PUSH_VALUES                          TRUE
#define POP_VALUES                           FALSE
#define MAX_SKIPS                            4
#define MAX_ALLOWED_TOTAL_ABS                3
#define POINT_3_INCHES_PER_SECOND            3
#define SINGLE_MOTOR_STEP                    1

#define NUM_STROKE_LENGTH_OPTIONS            4
#define NUM_PRESSURE_OPTIONS                 4
#define NUM_VALVE_POSITIONS                  73
#define DEFAULT_TUNE_WELD_TIME               200

#define ROUND_NUMBER_ADJUSTMENT              5
#define SMALL_FLOW_VALVE_FORMULA_AES_20INCH_15INCH_CYLINDER(Value)  (MAX_FLOW_VALUE - ((  (((Value * 4) + 120 + ROUND_NUMBER_ADJUSTMENT) / 10) * MAX_FLOW_VALUE) / 100))
#define SMALL_FLOW_VALVE_FORMULA_MICROC_32MM_CYLINDER(Value)        (MAX_FLOW_VALUE - ((Value * MAX_FLOW_VALUE) / 750) - 20)
#define SMALL_FLOW_VALVE_FORMULA_MICROC_40MM_CYLINDER(Value)        (MAX_FLOW_VALUE - ((Value * MAX_FLOW_VALUE) / 450) - 17)
#define NORMAL_FLOW_VALVE_FORMULA(Value)                            (MAX_FLOW_VALUE - ((Value * MAX_FLOW_VALUE) / 100)) //0 is max 125 is min

#define MIN_SMALL_FLOW_VALVE_VALUE           1

BOOLEAN DownspeedTuneFlag = FALSE, DownspeedTuneFlagHD = FALSE;
SINT32 DownspeedTuneCycles = 0;
SINT32 InitialFlowValue = 0, InitialDownSpeedValue = 0;
UINT32 DownspeedTuneCounter = 0;
static UINT32 LastMillisecondCount;
BOOLEAN WasTweaked = FALSE;
extern UINT16 PresetNeedsToBeUpdated;
extern UINT16 PresetHasBeenOKed;
extern BOOLEAN UpdateFlag;

/*********************************************************************************************/
/*                                                                                           */
/* This function is the main function that is used to convert a set downspeed from the SBC   */
/* into flow counts for the valve to be sent to the AES board. It simply updates downspeed   */
/* values 0 to 100 percent to flow count 125 to 0. It must be called everywhere the downspeed*/
/* is changed in order to update the counts on AES board.                                    */
/*                                                                                           */
/*   Entry condition:                                                                        */
/*	 signal int value from 0-100 % downspeed                                                 */
/*                                                                                           */
/*   Exit condition:                                                                         */
/*	 signal int value return the number of steps                                             */
/*   0 is max 125 is min                                                                     */
/*                                                                                           */
/* Note: If small flow valve adjustment is enabled and 2.0 or smaller cylinder               */
/* is installed, the flow setting is adjusted by a formula to emulate aed small              */
/* flow valve operation.                                                                     */
/* Adjust formula for small flow valve (used on systems with 2.0 in and smaller cyl)         */
/*                                                                                           */
/*********************************************************************************************/
SINT32 FlowLookup(SINT32 Val)
{
   SINT32 FlowValue = 0;

   if( (CurrentSetup.LowerFlowValveFlag == TRUE) && ((CurrentSequence != SC) && (CurrentSequence != CALIBRATION)) )
   {

	   if(CurrentSetup.Actuator == AES)
	   {
		   switch (CurrentSetup.CylinDiameter)
		   {
		    case SIZE1_5: //1.5" Cylinder Size
		    case SIZE2_0: //2.0" Cylinder Size
		       FlowValue = SMALL_FLOW_VALVE_FORMULA_AES_20INCH_15INCH_CYLINDER(Val);
	           break;
		    case SIZE2_5: //2.5" Cylinder Size
		    case SIZE3_0: //3.0" Cylinder Size
		    case SIZE3_25: //3.25" Cylinder Size
	        default:
	           FlowValue = NORMAL_FLOW_VALVE_FORMULA(Val);
	           break;
		   }
	   }
	   else if(CurrentSetup.Actuator == MICROC)
	   {
		   switch (CurrentSetup.CylinDiameter)
		   {
			case SIZE_32:
			   FlowValue = SMALL_FLOW_VALVE_FORMULA_MICROC_32MM_CYLINDER(Val);
			   break;
			case SIZE_40:
			   FlowValue = SMALL_FLOW_VALVE_FORMULA_MICROC_40MM_CYLINDER(Val);
		       break;
		    default:
		       FlowValue = NORMAL_FLOW_VALVE_FORMULA(Val);
		       break;
		   }
		   if(Val == MIN_SMALL_FLOW_VALVE_VALUE) FlowValue = MAX_FLOW_VALUE;
	   }
	   else
	   {

	       FlowValue = NORMAL_FLOW_VALVE_FORMULA(Val);
       }

   }
   else
   {
	   FlowValue = NORMAL_FLOW_VALVE_FORMULA(Val);
   }

   if(FlowValue < 0)
      FlowValue = 0;
   else if(FlowValue > MAX_FLOW_VALUE)
      FlowValue = MAX_FLOW_VALUE;

   return (FlowValue);
}

/*********************************************************************************************/
/*                                                                                           */
/* This function is the main function that is used to make changes in the flow steps during  */
/* tuning. This is called from the StopDataTuning state at the end of the cycle. It looks    */
/* at the measured downspeed versus the set downspeed and increments or decrements the       */
/* flow counts accordingly. At the end it updates the values to be sent to the SBC for       */
/* updating the screen.                                                                      */
/*                                                                                           */
/*********************************************************************************************/
void UpdateFlow()
{
   LastDownSpeedValue = WeldingResults.ActualDownspeed;
   SetFlowValue = CurrentPreset.TunedFlowValue;
}

/*********************************************************************************************/
/*                                                                                           */
/* This function is called when the downspeed tuning screen is initialized. It saves the     */
/* current settings of weld time and hold time to be recalled when the screen is exited.     */
/* This function will force a timed weld sequence with the tune flag set so data is not      */
/* collected.                                                                                */
/*                                                                                           */
/*********************************************************************************************/
void SetDownspeedTuneFlag()
{
   DownspeedTuneFlag = TRUE;
   if(CurrentPreset.TunedPreset == TRUE)
      InitialFlowValue = SetFlowValue = CurrentPreset.TunedFlowValue;
   else
      InitialFlowValue = SetFlowValue = CurrentPreset.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
   InitialDownSpeedValue = CurrentPreset.Downspeed;
   LastMillisecondCount = 0;
   PushPopPresetValues(PUSH_VALUES);
   // If the weld mode is not Time Mode (although it doesn't matter if it is), then use the weld time
   // reported from the results as the time mode value to use for tuning.
   if(CurrentPreset.WeldMode != TIMEMODE){
      if(WeldingResults.ActualWeldTime != 0)
         CurrentPreset.WeldTime = WeldingResults.ActualWeldTime;
      else
         CurrentPreset.WeldTime = DEFAULT_TUNE_WELD_TIME;
      CurrentPreset.WeldMode = TIMEMODE;
   }
   LastDownSpeedValue = WeldingResults.ActualDownspeed;
   UpdateRPreset();
   WasTweaked = FALSE;
   DownspeedTuneCycles = 0;
   SelectTimeWeldSequence();
}


/*********************************************************************************************/
/*                                                                                           */
/* This function is called when the Save button is pressed on the SBC downspeed tuning screen*/
/* It resets variables and most importantly if sets the preset values back to what they      */
/* were before the tuning process began.                                                     */
/*                                                                                           */
/*********************************************************************************************/
void SaveDownSpeedTune(void)
{

   CurrentPreset.TunedPreset = TRUE;
   DownspeedTuneCycles = 0;
   DownspeedTuneFlag = FALSE;
   PushPopPresetValues(POP_VALUES);
   UpdateRPreset();  // This must be called to reset the preset values.
   SVOff();// Bring horn in Home position if not done yet.
   SelectWeldSequence();  // Reset the weld sequence with the previous mode.
   StartStateMachine();
   if(EventReasonFlag)
   	  VGAEventReasonFlag = TRUE;
   if(CurrentPreset.Downspeed != InitialDownSpeedValue)
   {
   	EventParameterID = FLOWCONTROL;
   	Type = sint32;
   	memset(ParamNewVal, 0, sizeof(ParamNewVal));
   	memset(ParamOldVal, 0, sizeof(ParamOldVal));
   	memcpy(ParamOldVal, (UINT32*)&InitialDownSpeedValue, sizeof(UINT32));
   	memcpy(ParamNewVal, (UINT32*)&CurrentPreset.Downspeed, sizeof(UINT32));
	GlobalCommandID = FLOW_CONTROL_ID;
   	UpdateCurrentPresetAndSetup(FLOWCONTROL);
   }

}

/*********************************************************************************************/
/*                                                                                           */
/* This function is called when the Exit button is pressed on the SBC downspeed tuning screen*/
/* It resets variables and most importantly if sets the preset values back to what they      */
/* were before the tuning process began as well as set the flow back to what it was.         */
/*                                                                                           */
/*********************************************************************************************/
void ExitDownSpeedTune(void)
{

   CurrentPreset.TunedPreset = FALSE;
   DownspeedTuneCycles = 0;
   DownspeedTuneFlag = FALSE;
   CurrentPreset.TunedFlowValue = InitialFlowValue;
   CurrentPreset.Downspeed = InitialDownSpeedValue;
   PushPopPresetValues(POP_VALUES);
   UpdateRPreset();
   SVOff();// Bring horn in Home position if not done yet.
   SelectWeldSequence();
   StartStateMachine();
   if(EventReasonFlag)
     	VGAEventReasonFlag = TRUE;
}

/*********************************************************************************************/
/*                                                                                           */
/* This function saves/restores (pushes/pops) the preset values that change due to the tuning*/
/* procedure.                                                                                */
/*                                                                                           */
/*********************************************************************************************/
void PushPopPresetValues(BOOLEAN PushOrPop)
{
   static SINT32 RealWeldTime;
   static UINT16 RealWeldMode;
   static UINT16 RealControlLimitsFlag;
   static BOOLEAN RealSequencEnableFlag;
   static BOOLEAN RealExtPresetsFlag;

   if(PushOrPop == PUSH_VALUES){
      RealWeldMode = CurrentPreset.WeldMode;
      RealWeldTime = CurrentPreset.WeldTime;
      RealControlLimitsFlag = CurrentPreset.ControlLimitsFlag;
      CurrentPreset.ControlLimitsFlag = FALSE;//disable control limits for tune cycles
      RealSequencEnableFlag = CurrentSetup.SequenceEnable;
      CurrentSetup.SequenceEnable = FALSE;//disable sequencing for tune cycles
      RealExtPresetsFlag = CurrentSetup.ExtPresets;
      CurrentSetup.ExtPresets = FALSE;//disable ext presets for tune cycles
      DryCycleFlag = TRUE;
      PreSetupLimitMinMax(FLOW_CONTROL_ID);
   }
   else{
      CurrentPreset.WeldTime = RealWeldTime;
      CurrentPreset.WeldMode = RealWeldMode;
      CurrentPreset.ControlLimitsFlag = RealControlLimitsFlag;
      CurrentSetup.SequenceEnable = RealSequencEnableFlag;
      CurrentSetup.ExtPresets = RealExtPresetsFlag;
      DryCycleFlag = FALSE;
   }
}

/*********************************************************************************************/
/*                                                                                           */
/* This function is called when the Speed Up button is pressed on the SBC downspeed tuning   */
/* screen. It is pressed by the user when they want to tweak the flow valve after the tuning */
/* is completed if the tuning doesn't lock in on the desired value                           */
/*                                                                                           */
/*********************************************************************************************/
void SpeedUp() 
{
	if ((CurrentPreset.TunedFlowValue - SINGLE_MOTOR_STEP) >= 0) {
		CurrentPreset.TunedFlowValue -= SINGLE_MOTOR_STEP;
		CurrentPreset.Downspeed = (MAX_FLOW_VALUE
				- CurrentPreset.TunedFlowValue) * 100 / MAX_FLOW_VALUE;
		if (CurrentPreset.Downspeed <= MinSetupLim)
			CurrentPreset.Downspeed = MinSetupLim;
		else if(CurrentPreset.Downspeed>=MaxSetupLim)
		{
			CurrentPreset.Downspeed = MaxSetupLim;
			CurrentPreset.TunedFlowValue += SINGLE_MOTOR_STEP;
			Beep(ERRORBEEP);
		}
		SetFlowValue = CurrentPreset.TunedFlowValue;
		WasTweaked = TRUE;
		DownspeedTuneCycles = 0;
	} else
		Beep(ERRORBEEP);
}

/*********************************************************************************************/
/*                                                                                           */
/* This function is called when the Speed Down button is pressed on the SBC downspeed tuning */
/* screen. It is pressed by the user when they want to tweak the flow valve after the tuning */
/* is completed if the tuning doesn't lock in on the desired value                           */
/*                                                                                           */
/*********************************************************************************************/
void SpeedDown() 
{
	if ((CurrentPreset.TunedFlowValue + SINGLE_MOTOR_STEP) <= MAX_FLOW_VALUE) {
		CurrentPreset.TunedFlowValue += SINGLE_MOTOR_STEP;
		CurrentPreset.Downspeed = (MAX_FLOW_VALUE
				- CurrentPreset.TunedFlowValue) * 100 / MAX_FLOW_VALUE;
		if (CurrentPreset.Downspeed <= MinSetupLim)
		{
			CurrentPreset.Downspeed = MinSetupLim;
			CurrentPreset.TunedFlowValue -= SINGLE_MOTOR_STEP;
			Beep(ERRORBEEP);
		}
		else if(CurrentPreset.Downspeed>=MaxSetupLim)
			CurrentPreset.Downspeed = MaxSetupLim;
		SetFlowValue = CurrentPreset.TunedFlowValue;
		WasTweaked = TRUE;
		DownspeedTuneCycles = 0;
	} else
		Beep(ERRORBEEP);
}


/***************************************************************************
*                                                                         
*   Purpose:
*	This function is the main function that is used to make changes in the flow steps during  
*	tuning. This is called from the StopDataTuning state at the end of the cycle. It looks    
*	at the measured downspeed versus the set downspeed and increments or decrements the       
*	flow counts accordingly. At the end it updates the values to be sent to the SBC for       
*	updating the screen.                                                                      
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void UpdateFlowHD()
{
   LastDownSpeedValue = WeldingResults.ActualDownspeed;
   SetFlowValue = HdParams.TunedFlowValue;
}


/***************************************************************************
*                                                                         
*   Purpose:
* This function is called when the downspeed tuning screen is initialized. It saves the     
* current settings of weld time and hold time to be recalled when the screen is exited.     
* This function will force a timed weld sequence with the tune flag set so data is not      
* collected.                                                                                
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SetDownspeedTuneFlagHD()
{
	if(VGAHornDown){
	 VGAAction = EXIT_HD;
	 VGAProcessHornDownMsg();
	}
	DownspeedTuneFlag = TRUE;
	DownspeedTuneFlagHD = TRUE;
	if(HdParams.DownSpeedTuned == TRUE)
		InitialFlowValue = SetFlowValue = HdParams.TunedFlowValue;
	else
		InitialFlowValue = SetFlowValue = HdParams.TunedFlowValue = FlowLookup(HdParams.DownSpeed);
	InitialDownSpeedValue = HdParams.DownSpeed;
	LastMillisecondCount = 0;
	PushPopPresetValues(PUSH_VALUES);
	// If the weld mode is not Time Mode (although it doesn't matter if it is), then use the weld time
	// reported from the results as the time mode value to use for tuning.
	if(CurrentPreset.WeldMode != TIMEMODE)
	{
		if(WeldingResults.ActualWeldTime != 0)
			CurrentPreset.WeldTime = WeldingResults.ActualWeldTime;
		else
			CurrentPreset.WeldTime = DEFAULT_TUNE_WELD_TIME;
		CurrentPreset.WeldMode = TIMEMODE;
	}
	LastDownSpeedValue = WeldingResults.ActualDownspeed;
	///
	PresetHasBeenOKed = FALSE;
	PresetNeedsToBeUpdated = FALSE;
	memcpy(&RunningPreset, &CurrentPreset, sizeof(RunningPreset));
	UpdateFlag = TRUE;
	WasTweaked = FALSE;
	DownspeedTuneCycles = 0;
	SetPressureValue = HdParams.WeldPressure;
	SelectTimeWeldSequence();
}

/***************************************************************************
*                                                                         
*   Purpose:
* This function is called when the Save button is pressed on the SBC downspeed tuning screen
* It resets variables and most importantly if sets the preset values back to what they      
* were before the tuning process began.                                                     
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SaveDownSpeedTuneHD(void)
{
   HdParams.DownSpeedTuned = TRUE;
   DownspeedTuneCycles = 0;
   PushPopPresetValues(POP_VALUES);
   ///
   PresetHasBeenOKed = FALSE;
   PresetNeedsToBeUpdated = FALSE;
   memcpy(&RunningPreset, &CurrentPreset, sizeof(RunningPreset) );
   UpdateFlag = TRUE;
   SetFlowValue = HdParams.TunedFlowValue;
   ///
   SVOff();// Bring horn in Home position if not done yet.
   SelectWeldSequence();  // Reset the weld sequence with the previous mode.
   StartStateMachine();
}

/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when the Exit button is pressed on the SBC downspeed 
*	tuning screen during horn down It resets variables and most importantly if 
*	sets the preset values back to what they were before the tuning process began 
*	as well as set the flow back to what it was.lock in on the desired value.
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void ExitDownSpeedTuneHD(void)
{
	HdParams.DownSpeedTuned = FALSE;
	DownspeedTuneCycles = 0;
	HdParams.TunedFlowValue = InitialFlowValue;
	HdParams.DownSpeed = InitialDownSpeedValue;
	PushPopPresetValues(POP_VALUES);
	//UpdateRPreset();
	PresetHasBeenOKed = FALSE;
	PresetNeedsToBeUpdated = FALSE;
	memcpy(&RunningPreset, &CurrentPreset, sizeof(RunningPreset) );
	UpdateFlag = TRUE;
	SetFlowValue = HdParams.TunedFlowValue;
	SVOff();// Bring horn in Home position if not done yet.
	SelectWeldSequence();
	StartStateMachine();
	if(EventReasonFlag)
		  VGAEventReasonFlag = TRUE;
}


/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when the Speed Up button is pressed on the SBC
*	downspeed tuning screen initiated from HornDown. It is pressed by the user
*	when they want to tweak the flow valve after the tuning is completed if the
*	tuning doesn't lock in on the desired value
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SpeedUpHD(void)
{
	if ((HdParams.TunedFlowValue - SINGLE_MOTOR_STEP) >= 0) {
		HdParams.TunedFlowValue -= SINGLE_MOTOR_STEP;
		HdParams.DownSpeed = (MAX_FLOW_VALUE - HdParams.TunedFlowValue) * 100 / MAX_FLOW_VALUE;
		if (HdParams.DownSpeed <= MIN_DOWNSPEED)
			HdParams.DownSpeed = MIN_DOWNSPEED;
		else if(HdParams.DownSpeed >= MAX_DOWNSPEED)
		{
			HdParams.DownSpeed = MAX_DOWNSPEED;
			HdParams.TunedFlowValue += SINGLE_MOTOR_STEP;
			Beep(ERRORBEEP);
		}
		SetFlowValue = HdParams.TunedFlowValue;
		WasTweaked = TRUE;
		DownspeedTuneCycles = 0;
	} else
		Beep(ERRORBEEP);
}

/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when the Speed Down button is pressed on the SBC
*	downspeed tuning screen initiated from HornDown. It is pressed by the user
*	when they want to tweak the flow valve after the tuning is completed if the
*	tuning doesn't lock in on the desired value.
*                                                                         
*   Entry condition:                                                      
*	void
*	
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void SpeedDownHD(void)
{
	if ((HdParams.TunedFlowValue + SINGLE_MOTOR_STEP) <= MAX_FLOW_VALUE) {
		HdParams.TunedFlowValue += SINGLE_MOTOR_STEP;
		HdParams.DownSpeed = (MAX_FLOW_VALUE - HdParams.TunedFlowValue) * 100 / MAX_FLOW_VALUE;
		if (HdParams.DownSpeed <= MIN_DOWNSPEED)
		{
			HdParams.DownSpeed = MIN_DOWNSPEED;
			HdParams.TunedFlowValue -= SINGLE_MOTOR_STEP;
			Beep(ERRORBEEP);
		}
		else if(HdParams.DownSpeed >= MAX_DOWNSPEED)
			HdParams.DownSpeed = MAX_DOWNSPEED;
		SetFlowValue = HdParams.TunedFlowValue;
		WasTweaked = TRUE;
		DownspeedTuneCycles = 0;
	} else
		Beep(ERRORBEEP);
}
