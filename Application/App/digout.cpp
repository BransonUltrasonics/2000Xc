/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/digout.cpp_v   1.19   16 Apr 2015 07:21:08   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/digout.cpp_v  $
 * 
 *    Rev 1.19   16 Apr 2015 07:21:08   rjamloki
 * Added PartCalmpOff function to turn off read for clamp output. Calling it on actuator clear
 * 
 *    Rev 1.17   27 Mar 2015 11:32:10   amaurya
 * DoorOpen Removed
 * 
 *    Rev 1.16   08 Jan 2015 03:18:18   AnPawar
 * printf removed
 * 
 *    Rev 1.15   11 Nov 2014 06:06:10   AnPawar
 * Added support for cooling valve in FCC_TEST for future
 * 
 *    Rev 1.14   10 Nov 2014 04:47:22   AnPawar
 * Removed CPLD extern
 * 
 *    Rev 1.13   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.12   09 Jul 2014 10:45:18   rjamloki
 * SvInterlock renamed to PartClamp
 * 
 *    Rev 1.11   11 Jun 2014 11:28:54   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   05 Jun 2014 14:26:30   lmarkure
 * Added RapidTraverseOff and RapidTraverseOn functions
 * 
 *    Rev 1.9   21 May 2014 10:47:52   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 02:58:46   rjamloki
 * outputs going to u22 and u29 are reversed
 * 
 *    Rev 1.7   14 Apr 2014 09:55:00   rjamloki
 * Fixed SV driver for A1025 board, Added trigger_sw_active and trsenable. Cleaned up further to remove commented code.
 * 
 *    Rev 1.6   06 Mar 2014 11:03:46   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:20   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:32   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:22   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 -------------------------- MODULE DESCRIPTION -------------------------------
 Name: digout.c
 ----------------------------- DESCRIPTION -----------------------------------


 --------------------------- INCLUDE FILES ----------------------------------
 */
#include "portable.h"
#include "preset.h"
#include "outports.h"
#include "fpled.h"
#include "mansensr.h"
#include "menu.h"
#include "digout.h"
#include "state.h"
#include "ticks.h"
#include "qdef.h"
#include "alarms.h"
#include "weld_obj.h"
#include "CPLD.h"
#include "stdio.h"
#include "RTOS.h"
#include "A1025R.h"
#include "ready.h"

#define NUM_CTRL_PORTS  3    // j.b
#define AMPOFFVAL      10    // Amplitude Off Value; Percent.
#define UNKNOWN 		2   //Power up value for Actuator clear status

BOOLEAN SonicsOnFlag;
static BOOLEAN GeneralAlarmLFlag = 0;

extern UINT16 DryCycleFlag;
extern enum WELDSTATES WeldState;
UINT16 ThermalOLFlag;
extern BOOLEAN PartClampActive;
extern UINT16 MemoryResetFlag;
extern BOOLEAN ConfirmPresetFlag;

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
 */

// #define DIGOUT_UNIT_TEST 0
//#define  FCC_TEST
BOOLEAN SonicDisabledFlag = FALSE;
UINT8 ActClearStatus = UNKNOWN;
/*
 ----------------------------- LOCAL FUNCTIONS ----------------------------------
 */

/*
 ------------------------------- LOCAL DATA ------------------------------------
 */

BOOLEAN ReadyFlag = FALSE;
extern INBITS Inp;

#ifdef FCC_TEST
UINT16 FCCTestFlag = FALSE;
#endif

/*
 ---------------------------------- CODE ---------------------------------------
 */

void LockPowerOn(void)
{
	cpld->SetDout(Pwr_Off_Delay, true);
}

void PowerDownSystem(void)
{
	cpld->SetDout(Pwr_Off_Delay, false);
}

void SetGeneralAlarm(void)
{
	GeneralAlarmLFlag = TRUE;
	cpld->SetDout(Gen_Alarm, false);
}

void ClearGeneralAlarm(void)
{
	cpld->SetDout(Gen_Alarm, true);

	GeneralAlarmLFlag = FALSE;
	RejectOff(); /* Also clear the Reject alarm output     */
	SuspectOff(); /* While we're at it, do Suspect also     */
	//WarningOff();                  /* Might as well do warning output too    */
	UserCfgOutputOff(OUTPUT_NOTE); /* Clear the Warning Alarm output */
	UserCfgOutputOff(OUTPUT_NO_CYCLEALARM); /* Clear the No Cycle Alarm output */
	UserCfgOutputOff(OUTPUT_OLDALARM); /* Clear the Overload Alarm output */
	UserCfgOutputOff(OUTPUT_MDFY_ALARM);/* Clear the Modified Alarm output */
	UserCfgOutputOff(OUTPUT_MISSING_PART);/* Clear the MissingPart output */
}

BOOLEAN CheckGeneralAlarmFlag(void)
{
	return (GeneralAlarmLFlag);
}


void SetReady(void)
{
	cpld->SetDout(ReadySig, false);
	ReadyFlag = TRUE;
}

void ClearReady(void)
{
	cpld->SetDout(ReadySig, true);
	ReadyFlag = FALSE;
}

BOOLEAN GetReadyStatus(void)
{
	return (ReadyFlag);
}

void ClearSAS(void)
{
	cpld->SetDout(Weld_On, true);
}

void SetSAS(void)
/***************************************************************************/
/* This function will enable the Sonics Active Signal.This signal is not   */
/* activated if 'SonicDisable' input is high.                              */
/***************************************************************************/
{
	if (SonicDisabledFlag == FALSE)
	{
		cpld->SetDout(Weld_On, false);
	}
}

void EnableSVOn(void)
{
	cpld->SetDout(SVDrive_Lo, true);
}

void SVOn(void)
{ /* Turn on SV1 */
	cpld->SetDout(SV1, true);
}

void RapidTraverseOn(void)
{
	cpld->SetDout(SV2, true);
}

void RapidTraverseOff(void)
{
	cpld->SetDout(SV2, false);
}


void CoolValOn(void)
{
	cpld->SetDout(SV3, true);
}

void SVOff(void)
{ /* Turn off SV1 */

	cpld->SetDout(SV2, false);
	cpld->SetDout(SV1, false);
	cpld->SetDout(SVDrive_Lo, false);
}

void CoolValOff(void)
{
#ifdef FCC_TEST
	if (FCCTestFlag == FALSE)
#endif
	cpld->SetDout(SV3, false);
}

void PSIdle(void)
{
#ifdef FCC_TEST
	if (FCCTestFlag == FALSE)
	{
#endif   
	cpld->SetDout(SEEK_OUT_SIG, false);
	cpld->SetDout(RUN_OUT_SIG, true);
	cpld->SetDout(OL_RESET_SIG, true);
	cpld->SetDout(TEST_OUT_SIG, true);
	SonicsOnFlag = FALSE;
	UpdateLED(ZEROPERCENTLED, OFF);
	SetCurrentAmp(AMPOFFVAL); // Initial amplitude

#ifdef FCC_TEST
}
#endif
}

/*---  Only allow reset if there really is an OL or door is open  ---*/
void PSReset(void)
{
	if (Inp.OL == TRUE)
	{
		cpld->SetDout(RUN_OUT_SIG, true);
		cpld->SetDout(TEST_OUT_SIG, true);
		ThermalOLFlag++;
		SetCurrentAmp(AMPOFFVAL); // Initial amplitude
		cpld->SetDout(OL_RESET_SIG, false);
	}
}

void EStopReset(void)
{
	/***************************************************************************/
	/* This function will send a reset signal to the power supply when the     */
	/* system is in Estop                                                      */
	/***************************************************************************/
	cpld->SetDout(RUN_OUT_SIG, true);
	cpld->SetDout(TEST_OUT_SIG, true);
	SetCurrentAmp(AMPOFFVAL); // Initial amplitude
	cpld->SetDout(OL_RESET_SIG, false);
}

void MemoryReset(void)
/***************************************************************************/
/* This function will send a reset signal to the power supply to center    */
/* the frequency, in ready or pre-ready state.                             */
/***************************************************************************/
{
	if ((WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
	{
		cpld->SetDout(RUN_OUT_SIG, true);
		cpld->SetDout(TEST_OUT_SIG, true);
		cpld->SetDout(OL_RESET_SIG, false);
		MemoryResetFlag++;
	}
}

/* Function to turn the sonics off during an HornScan Abort */
void HSReset(void)
{
	UINT8 oldport = cpld->GetLatch(2);
	cpld->SetDout(RUN_OUT_SIG, true);
	cpld->SetDout(TEST_OUT_SIG, true);
	cpld->SetDout(OL_RESET_SIG, false);
	RTOS::DelayMs(20);
	cpld->SetLatch(2, oldport);
}

void PSRun(void)
{
	if (DryCycleFlag == FALSE && SonicDisabledFlag == FALSE)
	{
		cpld->SetDout(OL_RESET_SIG, true);
		cpld->SetDout(TEST_OUT_SIG, true);
		cpld->SetDout(RUN_OUT_SIG, false);
		UpdateLED(ZEROPERCENTLED,ON);
		SonicsOnFlag = TRUE;
	}
}

void PSTest(void)
{
	if (DryCycleFlag == FALSE)
	{
		SetCurrentAmp(CurrentPreset.TestAmp);
		cpld->SetDout(OL_RESET_SIG, true);
		cpld->SetDout(TEST_OUT_SIG, false);
		cpld->SetDout(RUN_OUT_SIG, false);
		UpdateLED(ZEROPERCENTLED,ON);
		SonicsOnFlag = TRUE;
		ClearReady(); /* Remove Welder Ready signal       */
#ifdef FCC_TEST
		FCCTestFlag = TRUE;
		CoolValOn();
#endif

	}
}

void PSSeek(void)
{
	if (DryCycleFlag == FALSE && SonicDisabledFlag == FALSE)
	{
		SetCurrentAmp((SINT32) 5);
		cpld->SetDout(OL_RESET_SIG, true);
		cpld->SetDout(SEEK_OUT_SIG, true);
		UpdateLED(ZEROPERCENTLED,ON);
		SonicsOnFlag = TRUE;
	}
}

//----------------------PORT A-------------------------------------------

void RejectOff(void)
{
	cpld->SetDout(Reject, true);
}

void RejectOn(void)
{
	cpld->SetDout(Reject, false);
}

void SuspectOff(void)
{
	cpld->SetDout(Suspect, true);
}

void SuspectOn(void)
{
	cpld->SetDout(Suspect, false);
}

void PBReleaseOff(void)
{
	/*****************************************************************************/
	/*                                                                           */
	/*  This output will be active when entering Ready                           */
	/*  held mode it is when the HHBeep is called.                               */
	/*                                                                           */
	/*****************************************************************************/
	cpld->SetDout(PB_Release, true);
}

void PBReleaseOn(void)
{
	/*****************************************************************************/
	/*                                                                           */
	/*  This output will be active when an the trigger switch is made. In hand   */
	/*  held mode it is when the HHBeep is called.                               */
	/*                                                                           */
	/*****************************************************************************/
	cpld->SetDout(PB_Release, false);
}

void ActClrOn(void)
{
	/*****************************************************************************/
	/*                                                                           */
	/*  This output will not be allowed to be active when an upper limit switch  */
	/*  alarm (EQ2) exists.  This is because if this alarm occurs, it is most    */
	/*  likely at power up and the carriage is not at home.  Therefore, the      */
	/*  position of the carriage is unknown and any values read by the encoder   */
	/*  are incorrect.  Furthermore, if the alarm does occur, call ActClrOff     */
	/*  to ensure the output isn't left active                                   */
	/*                                                                           */
	/*  2.68    06-23-03  BEKymer  Condition ActClrOn with lack of EQ2           */
	/*                                                                           */
	/*****************************************************************************/
	if(ActClearStatus != ON){
		if ((WeldingResults.EquipmentFailureAlarms & EQ2) == 0)
		{
			cpld->SetDout(Act_Clear, false);
			ActClearStatus = ON;
		}
		else
			ActClrOff();
		PartClampOutOff();//release the part clamp
	}
}

void ActClrOff(void)
{
   if(ActClearStatus != OFF){
      cpld->SetDout(Act_Clear, true);
      ActClearStatus = OFF;
   }
}

void TrigSwActv(void)
{
	cpld->SetDout(Trig_Sw_Actv, true);
}

void TrigSwInactv(void)
{
	cpld->SetDout(Trig_Sw_Actv, false);
}

void TrsEnabled(void)
{
	cpld->SetDout(TRSEnable, true);
}

void TrsDisabled(void)
{
	cpld->SetDout(TRSEnable, false);
}

// -------------------PORT C---------------------------------------

//void UserCfgOutputOn (UINT16 OutputConfigured)
void UserCfgOutputOff(UINT16 OutputConfigured) /* Make active low for now */
/***************************************************************************/
/* This function will make the output enabled if the output is configured  */
/* to any of the port pin.                                                 */
/***************************************************************************/
{
	if (CurrentSetup.J3_36Out == OutputConfigured)
	{ /* Make J3_36 High. */
		cpld->SetDout(J3_36, false);
	}
	if (CurrentSetup.J3_8Out == OutputConfigured)
	{ /* Make J3_8 High. */
		cpld->SetDout(J3_8, false);
	}
	if (CurrentSetup.J3_22Out == OutputConfigured)
	{ /* Make J3_22 High. */
		cpld->SetDout(J3_22, false);
	}

}

//void UserCfgOutputOff (UINT16 OutputConfigured)
void UserCfgOutputOn(UINT16 OutputConfigured) /* Make active low for now */
/***************************************************************************/
/* This function will make the output disabled if the output is configured */
/* to any of the port pin.                                                 */
/***************************************************************************/
{
	if (CurrentSetup.J3_36Out == OutputConfigured)
	{ /* Make J3_36 Low. */
		cpld->SetDout(J3_36, true);
	}
	if (CurrentSetup.J3_8Out == OutputConfigured)
	{ /* Make J3_8 Low. */
		cpld->SetDout(J3_8, true);
	}
	if (CurrentSetup.J3_22Out == OutputConfigured)
	{ /* Make J3_22 Low. */
		cpld->SetDout(J3_22, true);
	}
}

void RefreshOutputStatus(UINT16 RefreshPin)
/***************************************************************************/
/* This function refresh the output status to disable when the output is   */
/* reselected to the port pin.                                             */
/***************************************************************************/
{
	switch (RefreshPin)
	{
	case J3PIN36:
		/* Disable J3_36 if output is changed. */
		cpld->SetDout(J3_36, false);
		break;

	case J3PIN8:
		/* Disable J3_8 if output is changed. */
		cpld->SetDout(J3_8, false);
		break;

	case J3PIN22:
		/* Disable J3_22 if output is changed. */
		cpld->SetDout(J3_22, false);
		break;
	}
}

void ConfirmPresetOn(void)
/***************************************************************************/
/* This function will make the 'ConfirmPreset'output enabled,if the preset */
/* used to run the cycle is diffrent from preset used to run previous cycle*/
/***************************************************************************/
{
	if (ConfirmPresetFlag == TRUE)
		UserCfgOutputOn(OUTPUT_CFMPRESET);
	ConfirmPresetFlag = FALSE;
}

void ConfirmPresetOff(void)
/***************************************************************************/
/* This function will make the 'ConfirmPreset'output disabled.             */
/***************************************************************************/
{
	UserCfgOutputOff(OUTPUT_CFMPRESET);
}

void PartClampOutOn(void)
/***************************************************************************/
/* This function will make the 'PartClamp'output enabled.                */
/***************************************************************************/
{
	if (PartClampActive) /* If both PartClamp input and output are selected. */
		UserCfgOutputOff(OUTPUT_PART_CLAMPED);
}

void PartClampOutOff(void)
/***************************************************************************/
/* This function will make the 'PartClamp'output disabled.                */
/***************************************************************************/
{
	UserCfgOutputOn(OUTPUT_PART_CLAMPED);
}

/* Include for Unit test */
#ifdef DIGOUT_UNIT_TEST
#include "..\ut\digout.ut"
#endif
/* End of include for unit test */

