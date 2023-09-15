/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu0.cpp_v   1.11   28 Nov 2014 07:36:48   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu0.cpp_v  $
 * 
 *    Rev 1.11   28 Nov 2014 07:36:48   rjamloki
 * CancelDefaults() changed to remove warning "unused variable".
 * 
 *    Rev 1.10   28 Jul 2014 12:40:46   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.9   09 Jul 2014 11:11:12   rjamloki
 * Menu4.h removed.
 * 
 *    Rev 1.8   11 Jun 2014 11:49:20   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:08:26   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:28   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:40   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:32   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*                             
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu0.c   

   Function name:

 ------------------------------- DESCRIPTION ---------------------------------

       This file will deal with the Main Menu, top level only.


 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "menu0.h"
#include "menu1.h"
#include "menu2.h"
#include "menu6.h"
#include "menu7.h"
#include "keypad.h"
#include "selctkey.h"
#include "state.h"
#include "statedrv.h"
#include "preset.h"
#include "weld_obj.h"
#include "rtclock.h"
#include "getmsg.h"
#include "command.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT16 WorkingPasswordFlag;

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
RTCTime RTCMenu;

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

MENUEND endlist0 = { TRUE };
static UINT32 DefaultSelection;
static UINT16 EnableUserIOCaution;
static UINT16 EnableActuatorCaution;
static UINT16 EnableFRAMCaution;
static UINT16 EnablePrintingCaution;
static UINT16 EnableGlobalCaution;


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------

 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/



void SetupOption(void)
{

   RTClock::GetCurrentTime(&RTCMenu);
   WorkingPasswordFlag = CurrentSetup.PassWordFlag;
}


void SelectProperDefault(UINT32 Default)
{
   DefaultSelection = Default;
   EnableUserIOCaution = FALSE;
   EnableActuatorCaution = FALSE;
   EnableFRAMCaution = FALSE;
   EnablePrintingCaution = FALSE;
   EnableGlobalCaution = FALSE;
   switch (Default) {
      case USERIO:            /* Put all user I/O back to factory default */
         EnableUserIOCaution = TRUE;
         break;
      case ACTUATOR:          /* Restore actuator switches back to default*/
         EnableActuatorCaution = TRUE;
         break;
      case FRAM:               /* Initialize alarms, trig force in FRAM     */
         EnableFRAMCaution = TRUE;
         break;
      case PRINTING:          /* Turn off all print on sample & alarm     */
         EnablePrintingCaution = TRUE;
         break;
      case GLOBAL:            /* Do all of the above                      */
         EnableGlobalCaution = TRUE;
         break;
   }   
   
}   

void OkToDefault(void)
/**************************************************************************/
/*                                                                        */
/*   A return to factory setting has been selected.  The Global variable  */
/*   DefaultSelection contains the define for which selection.            */
/*                                                                        */
/**************************************************************************/
{
   switch (GlobalCommandID)
   {
   case RESTORE_USERIO:     /* Put all user I/O back to factory default */
      SetUserIOToFactoryDefault();
      break;

   case RESTORE_ACTUATOR:   /* Restore actuator switches back to default*/
      SetActuatorSwitchesToFactoryDefault();
      break;

   case RESTORE_FRAM:   /* Initialize alarms, trig force in FRAM     */
      SetBucMenuToFactoryDefault();
      break;

   case RESTORE_PRINTING:   /* Turn off all print on sample & alarm     */
//         SetPrintingToFactoryDefault();
      break;

   case RESTORE_GLOBAL:   /* Do all of the above                      */
      SetUserIOToFactoryDefault();
      SetActuatorSwitchesToFactoryDefault();
      SetBucMenuToFactoryDefault();
//      SetPrintingToFactoryDefault();
      SetUSBToFactoryDefault();
      break;
   }
}

void CancelDefaults(UINT32 MenuExtra)
/**************************************************************************/
/*                                                                        */
/*   Setting factory defaults has been canceled.  This means there is     */
/*   really nothing to do.  Just return back to the original menu.        */
/*                                                                        */
/**************************************************************************/
{
   MenuExtra = 0;
   SendFakeKeyPress(GoBackKey);
}

void RestoreDefaultConfirmScrn(UINT32 Default)
/****************************************************************************/
/*Description:                                                              */
/* Draws Restore Defaults Confirmation  Screen.                             */
/****************************************************************************/
{
   
   DefaultSelection = Default;
   
}



const MENU TheMainMenu[]    = { {&endlist0,                 (MENUS) ENDLIST}  };
