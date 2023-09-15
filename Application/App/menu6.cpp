/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu6.cpp_v   1.12   Oct 10 2017 10:51:12   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu6.cpp_v  $
 * 
 *    Rev 1.12   Oct 10 2017 10:51:12   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.11   16 Apr 2015 07:25:40   rjamloki
 * LoadActuatorType function is not calling GetActId function now to fix Start Switch Time issue on system information click
 * 
 *    Rev 1.10   26 Sep 2014 03:29:28   rjamloki
 * GetControlLevel fixed to show right control level in setup pdf
 * 
 *    Rev 1.9   05 Sep 2014 04:53:06   rjamloki
 * Added level c case in GetControllevel function
 * 
 *    Rev 1.8   20 Jun 2014 14:40:16   rjamloki
 * Updated LoadActuator type function for AES.
 * 
 *    Rev 1.7   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:09:10   rjamloki
 * coverity fixes
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

   Filename: menu6.c

   Function name:

  ------------------------------- DESCRIPTION ---------------------------------


    This file will deal with System Info options.  This is an output only
    set of data to indicate information such as version number, type of
    actuator, cylinder size, power supply wattage, etc.


 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "display.h"
#include "preset.h"
#include "param.h"
#include "string.h"
#include "actnvram.h"
#include "rtclock.h"
#include "dups_api.h"
#include "dups.h"
#include "command.h"
#include "stdlib.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/
#define CENTURY         2000

/*
 ------------------------------ GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
STR SysBuf1Name[VGA_LINESIZE];
SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH+1];
STR ps_ver[8];
STR PSFreqTxt[8];

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT16 RadioIndex;
extern UINT8 DateArr[3];
                           
void GetCalData(void);
void FormatIntToAscii(SINT8 Str[], UINT8 length, UINT16 val);
SINT8 * TrimLeadingBlanks(SINT8 Str_temp[]);
/*
 ------------------------------- LOCAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------------- CODE -------------------------------------
*/



void GetPowerSupplyInfo(void)
{
   SINT8 temp[LINESIZE];
   SINT8 temp1[LINESIZE];
   STR *str_temp;

   switch (CurrentSetup.PSFreq)
   {
      case FREQ20KHZ:
         strcpy(PSFreqTxt,"20KHz");
         break;
      case FREQ40KHZ:
         strcpy(PSFreqTxt,"40KHz");
         break;
      case FREQ15KHZ:
         strcpy(PSFreqTxt,"15KHz");
         break;
      case FREQ30KHZ:
         strcpy(PSFreqTxt,"30KHz");
         break;
      case FREQ60KHZ:
         strcpy(PSFreqTxt,"60KHz");
         break;
      default:
         strcpy(PSFreqTxt,"Unknown");
         break;
   }

   FormatIntToAscii(temp, LINESIZE, CurrentSetup.PSWatt);
   str_temp = TrimLeadingBlanks(temp);
   strncpy(temp1, str_temp, LINESIZE - 1);
   strncat(temp1, "W", LINESIZE - strlen(temp1) - 1);
   strncpy(SysBuf1Name, temp1, VGA_LINESIZE - 1);

}

/*******************************************************************************
 * This is a handler function for enable ID 21 and called on system information
 * button click on menu. It provides the current actuator information to display on menu.
 * Entry Condition:
 * Nvr.ActId- Actuator ID read from Actuator Novram at power up
 * ExitCondition:
 * RadioIndex- An index based on which SBC Application determines the actuator type
 * string to display
 *******************************************************************************/
void LoadActuatorType(void)
{

   if(CurrentSetup.CustomAct)
   {
      RadioIndex = 0;
   }
   else
   {
	   switch (NVR.ActId) {
	    case NVR_AE:
	    	RadioIndex = 1; // ae
	        break;
	    case NVR_AED:
	    	RadioIndex = 3;//AED
	        break;
	    case NVR_MICRO:
	    	RadioIndex = 7; //MICRO
	        break;
	    case NVR_AES:
	    	RadioIndex = 8; //AES
	        break;
	    case NVR_MICROC:
	    	RadioIndex = 9; //MICROC
	        break;
	 	default:
	 		RadioIndex = 0; //AE
	        break;
	    }
   }
}


void GetControlLevel(void)
{
   switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         RadioIndex = 0;
         break;
      case LEVEL_e:
         RadioIndex = 1;
         break;
      case LEVEL_ea:
          RadioIndex = 2;
         break;
      case LEVEL_d:
         RadioIndex = 3;
         break;
      case LEVEL_f:
         RadioIndex = 4;
         break;
      case LEVEL_a:
         RadioIndex = 5;
         break;
      case LEVEL_TEST:
         RadioIndex = 6;
         break;
      case LEVEL_c:
         RadioIndex = 8;
		 break;
      default:
         RadioIndex = 9;
         break;
   }
}

void GetSerialNumbers(void)
{
   SINT32 pid = DUPS_Info.ProgramId;
   ps_ver[6] = pid % 10 + '0';
   pid = pid/10;

   ps_ver[5] = pid%10 + '0';
   pid = pid/10;

   ps_ver[3] = pid % 10 + '0';
   ps_ver[4] = '.';
   ps_ver[7] = NULL;
   ps_ver[0] = ps_ver[1] = ps_ver[2] =  ' ';
    
}


void GetCalStatus(void)
{
   if(NVR.CalibPass == CALIBPASSED)
      RadioIndex = 1;
   else if(NVR.CalibPass == CALIBFAILED)
      RadioIndex = 2;
   else
      RadioIndex = 3;
}

void GetCalData(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the system information menu is displayed    */
/*                                                                          */
/* Inputs :  NVR.CalibPass - if default display default date else display   */
/*           pass/fail date                                                 */
/*                                                                          */
/* Outputs : CalPassStr - either pass, fail, or factory                     */
/*                                                                          */
/****************************************************************************/ 
{
   RTCTime RTCCal;
   if((NVR.CalibPass == CALIBPASSED) || (NVR.CalibPass == CALIBFAILED))
   {
      RTCCal.Day = NVR.CalDate[1]; 
      RTCCal.Century_Month = NVR.CalDate[0];
      RTCCal.Years = NVR.CalDate[2];
   }
   else
   {
      RTCCal.Day = NVR.DefCalDate[1]; 
      RTCCal.Century_Month = NVR.DefCalDate[0];
      RTCCal.Years = NVR.DefCalDate[2];
   }
 if(CurrentSetup.Units == TRUE) /*Display Time in the DD/MM/YY format.*/
   {

      DateArr[0] = (UINT8)RTCCal.Day;
      DateArr[1] = (UINT8)RTCCal.Century_Month;
      DateArr[2] = (UINT8)RTCCal.Years;
   }
   else                       /*Display Time in MM/DD/YY format*/
   {
      DateArr[0] = (UINT8)RTCCal.Century_Month;
      DateArr[1] = (UINT8)RTCCal.Day;
      DateArr[2] = (UINT8)RTCCal.Years;
   }
}

                               
/*==========================================================================*/
/**********************************END***************************************/
/*==========================================================================*/
