/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menucalb.cpp_v   1.17   Oct 10 2017 11:30:56   RJamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menucalb.cpp_v  $
 * 
 *    Rev 1.17   Oct 10 2017 11:30:56   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.16   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.15   10 Nov 2014 04:53:36   AnPawar
 * Function InitPressureCalMenus(),InitForceCalMenus() and ResetSensorCalb() changed , 12.F review change.
 * 
 *    Rev 1.14   03 Oct 2014 06:10:44   rjamloki
 * using RTOS::DelayMs() in place of tm_wkafter()
 * 
 *    Rev 1.13   18 Aug 2014 01:43:30   rjamloki
 * Cleaned up as per review comments. Removed checking for Actuator recalibrate alarm.
 * 
 *    Rev 1.12   28 Jul 2014 12:48:28   rjamloki
 * psos.h removed, review fixes
 * 
 *    Rev 1.11   09 Jul 2014 11:15:10   rjamloki
 * Added MICRO support.
 * 
 *    Rev 1.10   20 Jun 2014 14:39:04   rjamloki
 * Seperated Sync Menu sequences for pressure and force calibration.
 * 
 *    Rev 1.9   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 03:33:18   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.6   06 Mar 2014 11:03:52   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:44   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION ---------------------------

   Module name: Menucalb

   Filename:    Menucalb.c

   Function Name: Menus for calibration

          Written by:   Barry E. Kymer
                Date:   04-20-96
            Language:   "C"

  ----------------------------- DESCRIPTION --------------------------------

   This file will deal with the Calibrate and Verify menus.

  ----------------------------- PSEUDO CODE --------------------------------




  ---------------------------- LOCAL_EQUATES -------------------------------



  ------------------------------ INCLUDES ----------------------------------*/

#include "qdef.h"
#include "menu.h"
#include "menucalb.h"
#include "actnvram.h"
#include "menu5.h"
#include "menu7a.h"
#include "param.h"
#include "ticks.h"
#include "snsrcalb.h"
#include "rtclock.h"
#include "string.h"
#include "FrontPanelKeypadTask.h"
#include "preset.h"
#include "selctkey.h"
#include "getmsg.h"
#include "ready.h"
#include "alarms.h"
#include "statedrv.h"
#include "state.h"
#define MENUDELAY 50
/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

/***   ***   Variables needed   ***   ***/
extern BOOLEAN VGASnsrCalibAllowed;
SINT32  UserPressure[3];

UINT8 CalMenus[MAX_MENUS];
UINT16 MenuPointer = 0;

SINT32  ForceGaugeReadingMin = 0;     /* Lowest acceptable force reading    */
SINT32  ForceGaugeReadingMax = 999;   /* Highest acceptable force reading   */
SINT32  LoadCellReadingMin = 0;       /* Lowest acceptable loadcell reading */
SINT32  LoadCellReadingMax = 72000;   /* Highest acceptable reading         */
const SINT32  PowerReadingMin = 1;          /* Lowest acceptable force reading    */
const SINT32  PowerReadingMax = 3500;       /* Highest acceptable force reading   */
UINT8 MenuNxtPointer = 0;

/*-------------------------- Function Prototypes ---------------------------*/

void ResetSensorCalb(void);

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN VGACalAllowed;

extern BOOLEAN AdvanceMenuFlag;
/*-------------------------------- CODE ------------------------------------*/

void InitPressureCalMenus(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when the calibration is allowed. This initializes*/
/* the menu array and sets up the string for the first loadcell point       */
/*                                                                          */
/* Inputs :  StrMX_9G - Set to 15PSI                                        */
/*           StrMX_9H - Set to 25PSI                                        */
/*           CurrentSetup.CylinDiameter                                     */
/*                                                                          */
/* Outputs : FirstPointStr - displayed when the pressure calibration passes */
/*           CalMenus - array of the calibration menus                      */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 i = 0;
   MenuNxtPointer = 0;
   if (CurrentSetup.Actuator == AED || CurrentSetup.Actuator == MICRO)
   {
	  //Total number of different screens(menus) user can see after hitting the cal Pressure sensors button from menu
      //are numbered starting from 1 and put in gui file. These numbers represent the screen user is currently in during
	  //calibration and assigned to cal array. SBC receives these numbers from WC and decides the next menu to display.
	  //By using these numbers WC and SBC remains in sync during calibration.
      CalMenus[i++] = 1;
      CalMenus[i++] = 2;
      CalMenus[i++] = 3;
      CalMenus[i++] = 4;
      CalMenus[i++] = 5;
   }
   else if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
      CalMenus[i++] = 2;
      CalMenus[i++] = 2;
      CalMenus[i++] = 4;
      CalMenus[i++] = 4;
   }

   MenuPointer = 0;
}

void InitForceCalMenus(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when the calibration is allowed. This initializes*/
/* the menu array and sets up the string for the first loadcell point       */
/*                                                                          */
/* Inputs :  StrMX_9G - Set to 15PSI                                        */
/*           StrMX_9H - Set to 25PSI                                        */
/*           CurrentSetup.CylinDiameter                                     */
/*                                                                          */
/* Outputs : FirstPointStr - displayed when the pressure calibration passes */
/*           CalMenus - array of the calibration menus                      */
/*                                                                          */
/****************************************************************************/
{
   UINT16 i = 0;
   MenuNxtPointer = 0;
   if (CurrentSetup.Actuator == AED || CurrentSetup.Actuator == MICRO)
   {
	   //Total number of different screens(menus) user can see after hitting the cal Pressure sensors button from menu
	   //are numbered starting from 1 and put in gui file. These numbers represent the screen user is currently in during
	   //calibration and assigned to cal array. SBC receives these numbers from WC and decides the next menu to display.
	   //By using these numbers WC and SBC remains in sync during calibration.
      CalMenus[i++] = 7;
      CalMenus[i++] = 8;
      CalMenus[i++] = 9;
      CalMenus[i++] = 10;
      CalMenus[i] = 11;
   }
   else if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
      CalMenus[i++] = 2;
      CalMenus[i++] = 5;
      CalMenus[i++] = 5;
   }

   MenuPointer = 0;
}



void WaitForMenu(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration sequence is waiting for the menu*/
/* task. When the correct screen is displayed, then the calibration sequence*/
/* can continue.                                                            */
/*                                                                          */
/* Inputs :  CalMenus - array of the calibration menus                      */
/*                                                                          */
/* Outputs : AdvanceMenuFlag - set to TRUE when screen is displayed         */
/*                                                                          */
/****************************************************************************/ 
{
   if((VGACalAllowed || VGASnsrCalibAllowed) )
   {
	   if(CurrentSequence == CALIBRATION)
	   {
			if(MenuNxtPointer == CalMenus[MenuPointer]) 
				AdvanceMenuFlag = TRUE;
	   }
	   else
			AdvanceMenuFlag = TRUE;
   }
}



void UpdateCalibrationState(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration sequence is waiting for the menu*/
/* task. When the correct screen is displayed, then the calibration sequence*/
/* can continue.                                                            */
/*                                                                          */
/* Inputs :  CalMenus - array of the calibration menus                      */
/*                                                                          */
/* Outputs : AdvanceMenuFlag - set to TRUE when screen is displayed         */
/*                                                                          */
/****************************************************************************/ 
{
   AdvanceMenuFlag = FALSE;
   MenuPointer++;

}



void ResetSensorCalb(void) {
/****************************************************************************/ 
/*                                                                          */
/* This function copies the default calibration values into the current     */
/* values. It is called from the calibration menu entry. If the default     */
/* table was created from version 8.05, then generate Recal Alarm 1200      */
/*                                                                          */
/****************************************************************************/ 

   UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
   RTCTime RTCCal;

   RTClock::GetCurrentTime(&RTCCal);     /* Get date when calibration complete */
   DateArray[0] = RTCCal.Century_Month;
   DateArray[1] = RTCCal.Day;
   DateArray[2] = RTCCal.Years;
   SetCalibrationDate(DateArray);
   SetCalibPass((UINT16) CALIBDEFAULT);
   GetDefPressure();        /* Get defaults from the actuator novram */
   GetDefLoadCell();        /* Get defaults from the actuator novram */
   GetDefForce();
   GetDefCalStrokeLen();
   GetDefCalSysPressure();
   GetDefHomeOffset();

   SetCalSpringRateSlope(GetDefSpringRateSlope());

   SetLoadCell();           /* save them to pressure and loadcell   */
   SetPressure();
   SetForceNVR();
   SetCalStrokeLength();
   SetCalSysPressure();
   SetCalHomeOffset();

   RTOS::DelayMs( MS_TO_TICKS( MENUDELAY ) * MILLS_PER_TICK);  /* If this isn't here and user hits */
										   /* key right away, the menu will    */
										   /* jump to the next screen automatically*/
   if (!IsHWConfigured(VGA))
   {
	  ClearKeypadBuffer(TRUE);
	  SendFakeKeyPress(GoBackKey);
   }

}

