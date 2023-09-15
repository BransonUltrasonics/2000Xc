/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu7a.cpp_v   1.16   Nov 16 2017 14:51:26   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu7a.cpp_v  $
 * 
 *    Rev 1.16   Nov 16 2017 14:51:26   RJamloki
 * Added comments to case switches
 * 
 *    Rev 1.15   Nov 06 2017 14:02:50   RJamloki
 * Added MICROC ID to every Actuator ID’s Validation
 * 
 *    Rev 1.14   Oct 10 2017 10:57:14   RJamloki
 * added MICROC id, for evaluate actuator id's
 * 
 *    Rev 1.13   09 May 2016 12:39:40   RJamloki
 * remove RS232 functions SetRS232Terminal & SetRS232
 * 
 *    Rev 1.12   10 Nov 2014 04:53:18   AnPawar
 * Removed CPLD extern.
 * 
 *    Rev 1.11   18 Aug 2014 01:36:04   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 11:01:22   rjamloki
 * Removed dataprinting check
 * 
 *    Rev 1.8   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:33:08   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   21 Apr 2014 13:35:16   rjamloki
 * Diagnostic IO Stated Save and recall functions added
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

   Filename: menu7a.c

   Function name:

  ------------------------------- DESCRIPTION ---------------------------------

   This file is used in conjunction with menu7.c (system options).  The
   sub menus will be handled here.

  -----------------------------LOCAL_EQUATES---------------------------------

#define PRTMSGBUFF 24


 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "qdef.h"
#include "time.h"
#include "string.h"
#include "menu.h"
#include "rtclock.h"
#include "preset.h"
#include "param.h"
#include "selctkey.h"
#include "menu7.h"
#include "menu7a.h"
#include "SystemManagerTask.h"
#include "state.h"
#include "util.h"
#include "statedrv.h"
#include "serial.h"
#include "actnvram.h"
#include "mansensr.h"
#include "beep.h"
#include "display.h"
#include "outports.h"
#include "ready.h"
#include "alarms.h"
#include "cpld.h"
#include "battram.h"
#include "digout.h"

/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern BOOLEAN IsGraphDrawing;
extern UINT32 KeyMask;
extern UINT16 DisplayNextMenu;
extern enum WELDSTATES WeldState;
void SetWeldScaleIndex (void);
void SetTestScaleIndex (void);




/*------------------------------- GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                       */


MENUEND endlist7A = { TRUE };
BOOLEAN StateMachineDisabled = FALSE;
UINT32  TempStoreKeyMask;
UINT16  RadioIndex;
UINT32  RadioIndexL;
BOOLEAN  HHInactive = FALSE;
BOOLEAN UserIOAlarmMenu = FALSE;
BOOLEAN WeldingStopInsideMenu = FALSE;
unsigned char IOState[NumLatches];
/*---------------------------------- CODE -----------------------------------*/



/***   ***   Language Submenu   ***   ***/


void SetDumbTerminal(void)
{  //TBD
   switch(CurrentSetup.BaudRate){
      case BAUD_4800:
//         SerialIntBaud(4800);
         break;
      case BAUD_9600:
//         SerialIntBaud(9600);
         break;
      case BAUD_19200:
//         SerialIntBaud(19200);
         break;
   
      default:
//         SerialIntBaud(9600);
         break;
   }
}


void GetBaudIndex(void){
   if(CurrentSetup.BaudRate == BAUD_4800)
      RadioIndex = 0;
   else if(CurrentSetup.BaudRate == BAUD_9600)
      RadioIndex = 1;
   else if(CurrentSetup.BaudRate == BAUD_19200)
      RadioIndex = 2;
   else RadioIndex = 1;     // (CurrentSetup.BaudRate == BAUD_9600)
}


void GetCylinderIndex(void)     // For Information & PrintOut
{
   switch(CurrentSetup.CylinDiameter)
   {
      case CUSTOMSIZE:
         RadioIndex = 9;
         break;
      
      case SIZE1_5:
         RadioIndex = 0;
         break;
      
      case SIZE2_0:
         RadioIndex = 1;
         break;
     
      case SIZE2_5:
         RadioIndex = 2;
         break;
      
      case SIZE3_0:
         RadioIndex = 3;
         break;
      
      case SIZE3_25:
         RadioIndex = 4;
         break;
      
      case SIZE_40:
         RadioIndex = 5;
         break;
      
      case SIZE_50:
         RadioIndex = 6;
         break;
      
      case SIZE_63:
         RadioIndex = 7;
         break;
      
      case SIZE_80:
         RadioIndex = 8;
         break;
      
      case SIZE4_0:
         RadioIndex = 10;
         break;

      case SIZE_32:
         RadioIndex = 11;
         break;
      
      default:
         break;
   }
}


void SetCylinderDiameter(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES) ||
		(CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == MICRO))
   {
      switch(RadioIndex) {
         case 9:
            CurrentSetup.CylinDiameter = CUSTOMSIZE;
            break;
      
         case 0:
            CurrentSetup.CylinDiameter = SIZE1_5;
            break;
      
         case 1:
            CurrentSetup.CylinDiameter = SIZE2_0;
            break;
     
         case 2:
            CurrentSetup.CylinDiameter = SIZE2_5;
            break;
      
         case 3:
            CurrentSetup.CylinDiameter = SIZE3_0;
            break;
      
         case 4:
            CurrentSetup.CylinDiameter = SIZE3_25;
            break;
      
         case 5:
            CurrentSetup.CylinDiameter = SIZE_40;
            break;
      
         case 6:
            CurrentSetup.CylinDiameter = SIZE_50;
            break;
      
         case 7:
            CurrentSetup.CylinDiameter = SIZE_63;
            break;
      
         case 8:
            CurrentSetup.CylinDiameter = SIZE_80;
            break;
      
         case 10:
            CurrentSetup.CylinDiameter = SIZE4_0;
            break;

         case 11:
            CurrentSetup.CylinDiameter = SIZE_32;
            break;

         default:
            break;
      }
      SetCylSize(CurrentSetup.CylinDiameter);
   }
   UpdateCylDefaults();
   SetMaxMinValues();                /* Force maximum values to be updated */
   InitializePV();                   /* Re-establish steplimit for new size*/
}



void SetCylinderIndex(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES)||
		(CurrentSetup.Actuator == MICROC)||
        (CurrentSetup.Actuator == MICRO))
   {
      SetCylSize(CurrentSetup.CylinDiameter);
   }
   UpdateCylDefaults();
   SetMaxMinValues();                /* Force maximum values to be updated */
   InitializePV();                   /* Re-establish steplimit for new size*/
}


 
void UpdateCylDefaults(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the defaults when the cylinder size is changed or when the  */
/* DoColdStartPlus function is run.                                         */
/*                                                                          */
/* Inputs :  CurrentSetup.CylinDiameter                                     */
/*                                                                          */
/****************************************************************************/ 
{ 
   switch(CurrentSetup.CylinDiameter){          /* cylinder diameter */
        case SIZE2_0:                                     /*   2"  */
        case SIZE_50:                                     /*  50mm */
        case SIZE1_5:                                     /* 1.5"  */
        case SIZE_32:                                     /* 32mm */
        case SIZE_40:                                    /*  40mm */
           CurrentSetup.MinTrigForce = MIN_TRIGGER_FORCE_DEFAULT_2IN;
           BUCMenuRAM.ForcePC = FORCE_PC_DEFAULT_2IN;
           BUCMenuFRAM->ForcePC = FORCE_PC_DEFAULT_2IN;
           break;

        case SIZE3_0:                                     /*   3"  */
        case SIZE2_5:                                     /* 2.5"  */
        case SIZE3_25:                                    /* 3.25" */
        case SIZE4_0:                                     /* 4.0"  */
        case SIZE_63:                                     /*  63mm */
        case SIZE_80:                                     /*  80mm */
        default:
           CurrentSetup.MinTrigForce = MIN_TRIGGER_FORCE_DEFAULT_3IN;
           BUCMenuRAM.ForcePC = FORCE_PC_DEFAULT_3IN;
           BUCMenuFRAM->ForcePC = FORCE_PC_DEFAULT_3IN;
           break;
   }
}

void GetStrokeLenIndex(void)
{
   switch(CurrentSetup.StrokeLen)
   {
      case LENGTH_4:
         RadioIndex = 0;
         break;
      
      case LENGTH_5:
         RadioIndex = 1;
         break;
      
      case LENGTH_6:
         RadioIndex = 2;
         break;
      
      case LENGTH_2:
         RadioIndex = 3;
         break;
     case LENGTH_8:
         RadioIndex = 4;
         break;
      
      case LENGTH_80:
         RadioIndex = 5;
         break;
      
      case LENGTH_100:
         RadioIndex = 6;
         break;
      
      case LENGTH_125:
         RadioIndex = 7;
         break;
      
      /*case LENGTH_160:
         RadioIndex = 8;
         break;*/
      case LENGTH_50:
         RadioIndex = 8;
         break;

      case CUSTOMLEN:
         RadioIndex = 9;
         break;

      case LENGTH_70:
         RadioIndex = 10;
         break;

      case LENGTH_75:
         RadioIndex = 11;
         break;

      default:
         break;
   }
}


void SetStrokeLen(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the cylinder size in the actuator novram and sets the min & */
/* max force values. If an ae is installed it updates the strings only.     */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
{
   if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == MICRO))
   {
      switch(RadioIndex)
      {

      case 0:
         CurrentSetup.StrokeLen = LENGTH_4;
         break;
      
      case 1:
        CurrentSetup.StrokeLen = LENGTH_5;
         break;
     
      case 2:
         CurrentSetup.StrokeLen = LENGTH_6;
         break;
      
      case 3:
         CurrentSetup.StrokeLen = LENGTH_2;
        break;
      
      case 4:
         CurrentSetup.StrokeLen = LENGTH_8;
         break;
      
      case 5:
         CurrentSetup.StrokeLen = LENGTH_80;
         break;
      
      case 6:
         CurrentSetup.StrokeLen = LENGTH_100;
         break;
      
      case 7:
         CurrentSetup.StrokeLen = LENGTH_125;
         break;
      
     /* case 8:
         CurrentSetup.StrokeLen = LENGTH_160;
         break;*/

      case 8:
         CurrentSetup.StrokeLen = LENGTH_50;
         break;

      case 9:
         CurrentSetup.StrokeLen = CUSTOMLEN;
         break;

      case 10:
         CurrentSetup.StrokeLen = LENGTH_70;
         break;

      case 11:
         CurrentSetup.StrokeLen = LENGTH_75;
         break;

      default:
         break;
      }
      SetStrokeLength(CurrentSetup.StrokeLen);
   }
   SetMaxMinValues();                /* Force maximum values to be updated */
}

void SetStrokeLenIndex(void)
/****************************************************************************/ 
/*                                                                          */
/* This updates the stroke length in the actuator novram and sets the min & */
/* max stroke values. If an ae is installed it updates the strings only.    */
/*                                                                          */
/* Inputs :  CurrentSetup.Actuator                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/****************************************************************************/ 
 {
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES)||
		(CurrentSetup.Actuator == MICROC)||
        (CurrentSetup.Actuator == MICRO) )
   {
      SetStrokeLength(CurrentSetup.StrokeLen);
   }
   SetMaxMinValues();                /* Force maximum values to be updated */
}

void GetWeldScaleIndex(void)
{
   if(CurrentSetup.TimeMultiplier == WELDTIMEx1)
      RadioIndex = 0;
   else if(CurrentSetup.TimeMultiplier == WELDTIMEx2)
      RadioIndex = 1;
   else if(CurrentSetup.TimeMultiplier == WELDTIMEx3)
      RadioIndex = 2;
}

void SetWeldScaleIndex (void)
{
   if(RadioIndex == 0)
      CurrentSetup.TimeMultiplier = WELDTIMEx1;
   else if(RadioIndex == 1)
      CurrentSetup.TimeMultiplier = WELDTIMEx2;
   else if(RadioIndex == 2)
     CurrentSetup.TimeMultiplier = WELDTIMEx3;
}

void GetTestScaleIndex(void)
{
   if(CurrentSetup.TestMultiplier == TESTTIMEx1)
      RadioIndex = 0;
   else if(CurrentSetup.TestMultiplier == TESTTIMEx2)
      RadioIndex = 1;
   else if(CurrentSetup.TestMultiplier == TESTTIMEx3)
      RadioIndex = 2;
}

void SetTestScaleIndex (void)
{
   if(RadioIndex == 0)
      CurrentSetup.TestMultiplier = TESTTIMEx1;
   else if(RadioIndex == 1)
      CurrentSetup.TestMultiplier = TESTTIMEx2;
   else if(RadioIndex == 2)
     CurrentSetup.TestMultiplier = TESTTIMEx3;
}

void CheckForPrintingOrWelding(void)
/****************************************************************************/
/*Descriptions:-                                                            */
/*   This function will Check for the ready or pre-ready state. If the      */
/*   system is in ready state then stop the state machine and disable the   */
/*   HornDown and Test key and the next menu will be displayed, else the    */
/*   system will beep and don't display the next menu for selected Submenu. */  
/****************************************************************************/
{
   /* Check for the Ready or Pre-Ready state. */
   if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        && (IsGraphDrawing == FALSE))
   {
      StopStateMachine(); /* Stop the State machine*/
      StateMachineDisabled = TRUE;
      TempStoreKeyMask = KeyMask; /* Don't allow Test key  */
      KeyMask &= ~(TESTKEYMASK | HORNDOWNKEYMASK); 
      DisplayNextMenu = TRUE;   
   }
   else
      DisplayNextMenu = FALSE; // Checked  in ProcessMenuItem().
   
}


void  ExitMenuAndEnableWeld (void)
/****************************************************************************/
/*Descriptions:-                                                            */
/*   This function will Reset & Start the state machine & Enable the Test   */
/*   key, when exit from the UserIO menu or custom menu.                    */
/****************************************************************************/
{
   if(StateMachineDisabled)
   {
      KeyMask = TempStoreKeyMask;//Enable the Test and HornDown key.
      StateMachineDisabled = FALSE;
      DisplayNextMenu = TRUE; 
      if(UserIOAlarmMenu)  
         UserIOAlarmMenu = FALSE;
      ResetStateMachine(); // Reset and start the state machine.
      StartStateMachine();
   }
}

/*Saves the logic value of User io pins when Diagnostics User IO menu opens*/
void SaveUserIOState(void) {
	int i;
	for (i = 0; i < NumLatches; i++)
		IOState[i] = cpld->GetLatch(i);
}

/*Restores the logic value of User io pins when Diagnostics User IO menu is
 * closed or bottom menu is clicked*/
void RestoreUserIOState(void) {
	int i;
	for (i = 0; i < NumLatches; i++)
		cpld->SetLatch(i, IOState[i]);
}
