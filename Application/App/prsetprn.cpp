/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/prsetprn.cpp_v   1.41   Nov 06 2017 15:39:14   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/prsetprn.cpp_v  $
 * 
 *    Rev 1.41   Nov 06 2017 15:39:14   RJamloki
 * Fix hard code number in strokes and cylinder sizes functions
 * 
 *    Rev 1.40   Oct 10 2017 13:06:48   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.39   16 Apr 2015 07:27:38   rjamloki
 * Fix for coverity issue 12524
 * 
 *    Rev 1.38   08 Apr 2015 13:45:18   AnPawar
 * Changes for Pressure Stepping and Rapid Traverse.
 * 
 *    Rev 1.37   03 Apr 2015 07:13:36   amaurya
 * change in  PrintSetup0018A() and  ViewPresetSetup0018A() functions to correct step @ ext signal in view current setup and pdf.
 * 
 *    Rev 1.36   27 Mar 2015 11:09:26   amaurya
 * CurrentPreset changed to CurrentViewPreset.
 * 
 *    Rev 1.35   16 Mar 2015 03:10:26   amaurya
 * SystemPresetReport3() and SystemViewPresetReport() changed  to reorder the setup limit parameters in WeldSetup PDF and USB Preset screen as per requirement.
 * 
 *    Rev 1.34   11 Mar 2015 09:17:58   amaurya
 * INPUT_REJECT_ALARM changed to INPUT_CONFIRM_REJECT.SystemPresetReport5() changed to print setup limit on WeldSetup PDF.
 * 
 *    Rev 1.33   11 Feb 2015 06:38:14   amaurya
 * changes to correct pretrigger amplitude and preset name in view current setup
 * 
 *    Rev 1.32   05 Feb 2015 07:08:52   amaurya
 * PrintConfig0078() function added to display USB status in WeldSetup PDF.
 * 
 *    Rev 1.31   03 Feb 2015 16:23:16   rjamloki
 * Corrections for pressure limit display.
 * 
 *    Rev 1.30   30 Jan 2015 08:10:38   amaurya
 * ViewPresetSetup0329() addedto display holdpressure stats(default/on) on viewcurrentsetup and pdf.
 * 
 *    Rev 1.29   26 Jan 2015 20:06:26   rjamloki
 * chnage Pressure format for view setup to non decimal value.
 * 
 *    Rev 1.28   08 Jan 2015 02:45:36   AnPawar
 * downspeed format changed to percent in function ViewPresetSetup0312() and in function ViewPresetSetup0085() bitmask condition checked against correct bit
 * 
 *    Rev 1.27   02 Jan 2015 04:07:48   rjamloki
 * current preset changed to current view preset to display the highlighted preset data
 * 
 *    Rev 1.26   28 Nov 2014 07:39:28   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.25   14 Nov 2014 10:28:14   AnPawar
 * bit mask changed for down speed tuning printing.
 * 
 *    Rev 1.24   10 Nov 2014 04:56:06   AnPawar
 * Defines added to Val_ID variable.Removed VQS functions . 12.F review change.
 * 
 *    Rev 1.23   20 Oct 2014 06:22:54   AnPawar
 * Changes for View Current setup and Weld setup PDF
 * 
 *    Rev 1.22   06 Oct 2014 06:42:14   AnPawar
 * PrintConfig0178(),ViewPresetSetup0312(),SystemPresetReport1(),SystemPresetReport2() function changed
 * 
 *    Rev 1.21   03 Oct 2014 06:12:04   rjamloki
 *  OUTPUT_AMPDECAY removed
 * 
 *    Rev 1.20   26 Sep 2014 03:37:00   rjamloki
 * Removed J38 and J336 swapping
 * 
 *    Rev 1.19   11 Sep 2014 11:02:56   rjamloki
 * Added events.h include
 * 
 *    Rev 1.18   05 Sep 2014 05:05:58   rjamloki
 * Changes to support level C.
 * 
 *    Rev 1.17   18 Aug 2014 05:46:46   rjamloki
 * Disabled Actuator specfic printing on view current setup screen as it is redundant.
 * 
 *    Rev 1.16   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.15   07 Aug 2014 15:51:44   tayars
 * Changed variable name for downspeed.
 * 
 *    Rev 1.14   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.13   09 Jul 2014 13:38:56   rjamloki
 * Fixed for view current setup for AES.
 * 
 *    Rev 1.12   11 Jun 2014 12:04:50   rjamloki
 * Removed plus and minus R band limits from Setup
 * 
 *    Rev 1.11   21 May 2014 10:48:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:35:22   rjamloki
 * PrintLineHeight is made variable for pdf printing purpose
 * 
 *    Rev 1.9   07 May 2014 10:37:44   rjamloki
 * RecallViewCompressedPreset() function changed.
 * 
 *    Rev 1.8   21 Apr 2014 13:43:02   rjamloki
 * Event and Alarm data handling routines added
 * 
 *    Rev 1.7   26 Mar 2014 12:28:34   rjamloki
 * ProcessUserIdData() changed to send userid list correctly.
 * 
 *    Rev 1.6   07 Mar 2014 11:11:10   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:38   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.3   10 Feb 2014 04:59:48   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.2   03 Jan 2014 08:45:44   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 --------------------------- MODULE DESCRIPTION ---------------------------

 Module name        :   Prsetprn

 Filename           :   Prsetprn.c

 Function Name      :   Allow Preset printing capabilities
 Function Prototypes:

 void SystemPresetReport(void);
 void FormatString( SINT8 *, SINT8 *, SINT8 *)
 void FormatHeader( SINT8 *, SINT8 *)
 void FormatNumber( SINT8 *, SINT32, SINT8 *)
 void SendACharToPrint(UINT8);
 void InitMessage(UINT8);
 SINT32 SeqToPrinter(const UINT8 *, SINT32);
 void InitPresetPrinter(void);
 void FormatRightJ(SINT8 *, SINT8 *);

 Written by:   Paul M. Garvey
 Date:   08-01-96
 Language:   "C"

 ----------------------------- DESCRIPTION --------------------------------*/

/*----------------------------- GLOBAL FUNCTION ----------------------------*/
void LastDatePresetWasSaved(void);

/*---------------------------- LOCAL EQUATES-------------------------------*/

/*----------------------------INCLUDES--------------------------------------*/

#include "qdef.h"
#include "string.h"
#include "preset.h"  /* Defines structs for 1000 series                      */
#include "menu.h"    /* Variable types, structs, enum types for 1000 series  */
#include "util.h"
#include "limits.h"
#include "menu7a.h"
#include "graphs.h"
#include "prsetprn.h"   
#include "limarray.h"
#include "weld_obj.h"
#include "actnvram.h"
#include "rtclock.h"
#include "dups_api.h"
#include "battram.h"
#include "dups_api.h"
#include "inports.h"
#include "outports.h"
#include "command.h"
#include "stdio.h"
#include "Events.h"

/**-------------------------FUNCTION PROTOTYPE-----------------------------**/
void VGA_PresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID);
void VGA_PresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID);
void VGA_RejLimPresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID);
void VGA_SusLimPresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID);
void SetDefaultUserData(void);
void ViewPresetSetup0012(void);
void ViewPresetSetup0013(void);

/**-------------------------EXTERNAL DATA----------------------------------**/
extern UINT16 ViewDupsPresent;
extern UINT16 GlobalFunctionCode;
extern DEPOT_FLAGS *DepotFlag;
extern UINT16 PresetCheck; /*-- Checks for preset change       --*/
extern SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH + 1];
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH + 1];
/**------------------------------------------**
 **       SETUPS CONSTANT STRINGS            **
 **------------------------------------------**/
/*--------------------------LOCAL DATA--------------------------------------*/


SINT32 PrintLineHeight = 23;

UINT16 GetArrayValue = 0;
SINT8 buffer[LINELEN]; /*-- Holds string to be printed         --*/
SINT8 AltString[LINELEN]; /*-- Holds string to be printed         --*/
SINT8 indentbuf[LINELEN]; /*-- Holds string to be printed         --*/
SINT8 datestr[DATELEN]; /*-- Stores date string                 --*/
SINT8 timestr[TIMELEN]; /*-- Stores time string                 --*/
SINT8 misc[MISCLEN]; /*-- Stores miscelaneous string         --*/
UINT16 blockArraySize = 0; /*-- Larger of SetupCt1 or SetupCt2     --*/
UINT16 SetupCt1 = 0; /*-- Counter for PresetSetup1 array     --*/
UINT16 SetupCt2 = 0; /*-- Counter for PresetSetup2 array     --*/
UINT16 SusRejFlag = SUSACTIVE; /*-- REJACTIVE: Printing reject limits  --*/
/*-- SUSACTIVE: Printing suspect limits --*/
UINT16 PageNumber = 1; /*-- Inital page# = 1, incremented as pages print --*/
UINT16 LangIndex = 0; /*-- Language array index               --*/
SINT8 LangText[15];
SINT32 LastSavedYear;
SINT32 LastSavedMonth;
SINT32 LastSavedDay;
WELD_DATA SetupPrint; /*--  Store last weld history cycle     --*/
SINT8 VGABuffer[LINELEN * 2];
SINT8 TempVGABuffer[LINELEN * 2];
SINT8 VGAIndentBuf[LINELEN * 2];
SINT8 VGAMisc[VGAMISCLEN + 2];
UINT8 Font_Print;
UINT16 LeftPrintXCoordinate;
UINT16 LeftPrintYCoordinate;
UINT16 RightPrintXCoordinate;
UINT16 RightPrintYCoordinate;
UINT16 VGAPrintLength;
UINT16 VGAPrintParam;
SETUPS_Ver1200 CurrentViewPreset;
UINT8 Value;
BOOLEAN ValueFlag;
UINT16 Val_ID;

#define MAXSTRLEN 28


/*------------------------------------------------------------------------------*/
/* These are needed to reference into the arrays in limarray.h */
#define INDEX_t 0
#define INDEX_e 1
#define INDEX_ea 2
#define INDEX_d 3
#define INDEX_f 4
#define INDEX_c 5
#define VGAPRESETNOSTART 4
#define VGAPRESETNAMESTART 16
#define VGAPRESETMODESTART 33
#define VGAPRESETVALUESTART  55
/**------------------------- EXTERNAL FUNCTION -------------------------------**/

UINT16 LangStrLen(SINT8 * str);
void LangStrCpy(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr);
void PrintPresetName(void);

/**-----------------------------------------------------------**
 ** This function prints the preset name in view current setup.**
 **-----------------------------------------------------------**/
void PrintPresetName(void)
{
   SINT8 TempStr[20];

   /* format PRESET =, etc. */
   if(GlobalFunctionCode == PSPRESET_COMMAND)
   {
	   if(PresetCheck == 0)
		   PresetCheck = CurrentSetup.ActivePreset;

	   if (PresetCheck)
	   {
		  strcpy(TempVGABuffer, "Prst");
		  sprintf(TempStr, "%d - ", PresetCheck);
		  strcat(TempVGABuffer, TempStr);
		  strcat(TempVGABuffer, CurrentViewPreset.PresetID);
	   } else
		  strcpy(TempVGABuffer, "Preset0 ");
   }
   else{ //View USB Preset
	   strcpy(TempVGABuffer, "Prst");
	   strcpy(TempStr, " - ");
	   strcat(TempVGABuffer, TempStr);
	   strcat(TempVGABuffer, CurrentViewPreset.PresetID);
   }

   /* if preset not updated then flag it with an "*" */
   if (!CurrentViewPreset.PresetUpdateComplete)
      strcat(TempVGABuffer, "*");


   /* print PRESET =, etc. */
   strcpy(VGABuffer, TempVGABuffer);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = SELECTNAME_TXT;
   VGAPrintParam = PSELECTNAME;


}

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void PrintSetupSystemPressure(void)
{
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = SYSTEMPRESSURE_PRNT;
   VGAPrintParam = ALWAYS;
}

/**----------------------------------------------**
 ** This function displays the Scrub Amplitude.  **
 **----------------------------------------------**/
void ViewPresetSetup0003A(void)
{
   FormatVariables(CurrentViewPreset.AmpScrubTime, PERCENT, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = SCRUBAMP_TXT;
   VGAPrintParam = PSCRUBAMPLITUDE;
}

void PrintForceRamps(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = FORCERAMPS_PRNT;
   VGAPrintParam = ALWAYS; /* Print in right half-page */
}

/**-----------------------------------------------**
 ** This function gets the time and date strings. **
 **-----------------------------------------------**/
void GetDateTime(void)
{
   RTCTime RTCPrinter;
   /* Get the current time and date from clock in FRAM */
   RTClock::GetCurrentTime(&RTCPrinter);

   if (SummaryInfo.b_unit)
      sprintf(datestr, "%02u/%02u/%02u", RTCPrinter.Day,
            RTCPrinter.Century_Month, RTCPrinter.Years);
   else
      sprintf(datestr, "%02u/%02u/%02u", RTCPrinter.Century_Month,
            RTCPrinter.Day, RTCPrinter.Years);

   sprintf(timestr, "%02u:%02u", RTCPrinter.Hour, RTCPrinter.Minute);
}
/**----------------------------------------------**
 ** This function displays the Scrub Amplitude.  **
 **----------------------------------------------**/
void PrintSetup0003A(void)
{
   FormatVariables(CurrentPreset.AmpScrubTime, PERCENT, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = SCRUBAMP_PRNT;
   VGAPrintParam = PSCRUBAMPLITUDE;
}
/**-----------------------------**
 **  Array Group 1 and Group 2  **
 **-----------------------------**/

/**------------------------------------------**
 ** This function  Checks an array structure **
 ** to see what parameters should print.     **
 **------------------------------------------**/
UINT16 CheckIfPrintable(UINT16 VarType)
{

   switch (CurrentSetup.ControlLevel)
   {
   case LEVEL_t:
      GetArrayValue = parameterControlLevel[VarType][INDEX_t];
      break;

   case LEVEL_e:
      GetArrayValue = parameterControlLevel[VarType][INDEX_e];
      break;

   case LEVEL_ea:
   case LEVEL_a:
      GetArrayValue = parameterControlLevel[VarType][INDEX_ea];
      break;

   case LEVEL_d:
      GetArrayValue = parameterControlLevel[VarType][INDEX_d];
      break;

   case LEVEL_f:
      GetArrayValue = parameterControlLevel[VarType][INDEX_f];
      break;

   case LEVEL_c:
         GetArrayValue = parameterControlLevel[VarType][INDEX_c];
         break;

   case LEVEL_TEST:
      GetArrayValue = AVAIL;
      break;

   default:
      GetArrayValue = parameterControlLevel[VarType][INDEX_t];
      break;
   }

   switch (GetArrayValue)
   {
   case ACTDF: // Print if:  aed|aod|aef|aof|MICRO
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES)
    		  || (CurrentSetup.Actuator == MICROC)
    		  || (CurrentSetup.Actuator == MICRO))
         VarType = TRUE;
      else
         VarType = FALSE;
      break;
   case AVAIL:
      VarType = TRUE;
      break;
   case AVAILLE:
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC)
    		  || (CurrentSetup.Actuator == MICRO))
         VarType = TRUE;
      else
         VarType = FALSE;
      break;

   case NOTAVAIL:
      VarType = FALSE;
      break;

   case TMODONLY:
      if (CurrentPreset.WeldMode == TIMEMODE)
         VarType = TRUE;
      else
         VarType = FALSE;
      break;
   default:
      VarType = FALSE;
      break;
   }
   return (VarType);
}

/**---------------------------------------------**
 ** This function checks an array structure     **
 ** to see what Limits should print.            **
 ** Based on the controllevels, weldmodes and   **
 ** and the Limits. It then returns a selection **
 ** from the array table.                       **
 **---------------------------------------------**/
UINT16 ControlLevelLimit(UINT16 Limit)
{
   UINT16 ControlLevel = 1, Weldmode = 0;
   UINT16 RetVal = 0;

   // Must setup array index values to correspond to the Control Level tables
   // ControlLevels     0..9  -> 5 levels  0..5 -> Suspect, 6-11 -> Reject
   // Weldmodes         0..6  -> 7 weldmodes
   // Limits            0..15 -> 16 limits


   /* First get Control Level index into the table */
   /* based on the if limit is reject or suspect   */
   switch (CurrentSetup.ControlLevel)
   {
   case LEVEL_t:
      ControlLevel = INDEX_t;
      break;

   case LEVEL_e:
      ControlLevel = INDEX_e;
      break;

   case LEVEL_ea:
      ControlLevel = INDEX_ea;
      break;

   case LEVEL_d:
      ControlLevel = INDEX_d;
      break;

   case LEVEL_f:
      ControlLevel = INDEX_f;
      break;

   case LEVEL_TEST:
      ControlLevel = INDEX_f;
      break;

   case LEVEL_c:
      ControlLevel = INDEX_c;
      break;
   default:
      ControlLevel = INDEX_t;
      break;
   }

   if (SusRejFlag != SUSACTIVE)
      ControlLevel += SUSREJDIFF;

   /* Next get the Weldmode index into the table */
   switch (CurrentPreset.WeldMode)
   {
   case TIMEMODE:
      Weldmode = TIMEMLIM;
      break;

   case ENERGYMODE:
      Weldmode = ENERGYMLIM;
      break;

   case PKPOWERMODE:
      Weldmode = PKPOWERMLIM;
      break;

   case COLLAPSEMODE:
      Weldmode = COLMLIM;
      break;

   case ABSOLUTEMODE:
      Weldmode = ABSMLIM;
      break;

   case GRDDETECTMODE:
      Weldmode = GRDDETMLIM;
      break;

   case CONTINUOUSMODE:
      Weldmode = CONTMLIM;
      break;

   default:
      Weldmode = TIMEMLIM;
      break;
   }

   /* Value is selected from the TABLE */
   GetArrayValue = controlLevel[ControlLevel][Limit][Weldmode];
  /* Should we print this string? */
   switch (GetArrayValue)
   {
   case ACTDF: // Print if:  aed|aod|aef|aof|MICRO
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         RetVal = TRUE;
      else
         RetVal = FALSE;
      break;

   case AVAIL:
      RetVal = TRUE;
      break;

   case AVAILLE:

      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         RetVal = TRUE;
      else
         RetVal = FALSE;
      break;

   case NOTAVAIL:

      RetVal = FALSE;
      break;

   case TMODONLY:
      if (CurrentPreset.WeldMode == TIMEMODE)
         RetVal = TRUE;
      else
         RetVal = FALSE;
      break;

   default:
      RetVal = FALSE;
      break;
   }
   return (RetVal);
}

void LastDatePresetWasSaved(void)
{
   RTCTime RTCPrinter;

   RTClock::GetCurrentTime(&RTCPrinter);
   CurrentPreset.PS_DateTime.Years = RTCPrinter.Years;
   CurrentPreset.PS_DateTime.Century_Month = RTCPrinter.Century_Month;
   CurrentPreset.PS_DateTime.Day = RTCPrinter.Day;
   CurrentPreset.PS_DateTime.Hour = RTCPrinter.Hour;
   CurrentPreset.PS_DateTime.Minute = RTCPrinter.Minute;
}

/**----------------------------------------------**
 ** This function displays the current weld mode.**
 **----------------------------------------------**/
UINT16 PrintSetup0002(void)
{
   UINT16 param;
   switch (CurrentPreset.WeldMode)
   {
   case TIMEMODE:
      Value = 0;
      param = PWELDTIME;
      break;

   case ENERGYMODE:
      Value = 1;
      param = PENERGY;
      break;

   case PKPOWERMODE:
      Value = 2;
      param = PPEAKPOWER;
      break;

   case COLLAPSEMODE:
      Value = 3;
      param = PCOLDIST;
      break;

   case ABSOLUTEMODE:
      Value = 4;
      param = PABSDIST;
      break;

   case GRDDETECTMODE:
      Value = 5;
      param = PGROUNDDETECTCUTOFF;
      break;

   case CONTINUOUSMODE:
      Value = 6;
      param = PCONTINUOUS;
      break;

   default:
      Value = 0;
      param = PWELDTIME;
      break;
   }
   ValueFlag = TRUE;
   Val_ID = WELD_MODE_PRNT;
   VGAPrintParam = param;
   return (param);
}

/**-----------------------------------------------**
 ** This function displays the current Hold Time. **
 **-----------------------------------------------**/
void PrintSetup0004(void)
{

   /* Hold Time */
   if ((CurrentPreset.HoldTimeFlag & BIT0) == FALSE)
   {

      FormatVariables(CurrentPreset.HoldTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = HOLDTIME_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = HOLDTIME_OFF_PRNT;
   }
   VGAPrintParam = PHOLDTIME;
}

////////////////////////////////////////////////////////////////////////////
//					FUNCTION TO CONVERT VALUE TO A STRING                    //
////////////////////////////////////////////////////////////////////////////

void ConvertNumberToString(SINT32 Value)
{
   SINT16 i, j;
   SINT32 Temp;
   SINT8 NumDisplayChar = DISPLAYCHAR;
   UINT16 StringEnd, neg = 0;
   StringEnd = PRINTSPACEPAGE;

   if (Value < 0)
   {
      neg = 1;
      Value = (Value * (-1));
   }

   for (i = 0; i < StringEnd; i++)
      VGABuffer[i] = FILLCHAR;

   VGABuffer[StringEnd] = '\0';
   i = StringEnd - 1;
   if (Value > 0)
   {
      while ((NumDisplayChar > 0) && (Value != 0))
      {
         Temp = Value % 10;
         VGABuffer[i--] = Temp + '0';
         Value /= 10;
         NumDisplayChar--;
      }
      if (neg)
         VGABuffer[i] = '-';
   } else
   {
      VGABuffer[StringEnd - 1] = '0';
   }

   j = 0;
   while (VGABuffer[j++] == FILLCHAR)
      ;
   j--;

   for (i = 0; j <= StringEnd; i++)
   {
      VGABuffer[i] = VGABuffer[j];
      j++;
   }
   for (; i <= StringEnd; i++)
      VGABuffer[i] = FILLCHAR;
}

/**------------------------------------------------**
 ** This function displays the current value based **
 ** on the weld mode.                              **
 **------------------------------------------------**/
UINT16 PrintSetup0003(void)
{
   UINT16 param = 0;

   switch (CurrentPreset.WeldMode)
   {
   case TIMEMODE:
      FormatVariables(CurrentPreset.WeldTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PWELDTIME;
      Val_ID = TIME_PRNT;
      break;

   case ENERGYMODE:
      FormatVariables(CurrentPreset.WeldEnergy,
            /* cont'd */CurrentPreset.WeldEnergy > ENERGYPOINT ? ENERGYDIV10
                  : ENERGY,
            /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PENERGY;
      Val_ID = ENRGY_PRNT;
      break;

   case PKPOWERMODE:
      FormatVariables(CurrentPreset.PeakPwr, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PPEAKPOWER;
      Val_ID = PKPOWR_PRNT;
      break;

   case COLLAPSEMODE:
      FormatVariables(CurrentPreset.ColDist, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      LangStrCpy(VGABuffer, VGAMisc);
      param = PCOLDIST;
      Val_ID = COLLAPSE_PRNT;
      break;

   case ABSOLUTEMODE:
      FormatVariables(CurrentPreset.AbsDist, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PABSDIST;
      Val_ID = ABSOLUTE_PRNT;
      break;

   case GRDDETECTMODE:
      FormatVariables(CurrentPreset.ScrubTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PSCRUBTIME;
      Val_ID = GRDDETECT_PRNT;
      break;

   case CONTINUOUSMODE:
      param = ALWAYS;
      Val_ID = CONTINOUS_PRNT;
      break;

   default:
      param = ALWAYS;
      Val_ID = ALLMODE_PRNT;
      break;
   }
   Value = 0;
   ValueFlag = FALSE;
   VGAPrintParam = param;
   return (param);
}

/**----------------------------------------**
 ** This function displays the Afterburst. **
 **----------------------------------------**/
void PrintSetup0022(void)
{
   Value = (UINT8) CurrentPreset.AbFlag;
   ValueFlag = TRUE;
   Val_ID = ABRUST_PRNT;
   VGAPrintParam = PAFTERBURST;
}

/**----------------------------------------**
 ** This function displays the Amplitude.  **
 **----------------------------------------**/
void PrintSetup0015(void)
{
   if (CurrentSetup.AmpControl == TRUE)
   {

      /* BIT0 = FIXED, BIT2-BIT6 = STEP */
      if ((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      {
         Value = CurrentSetup.AmpControl;
         ValueFlag = TRUE;
         Val_ID = AMPLITUDE_PRNT;
      } else
      {
         ConvertNumberToString(CurrentPreset.Amp1);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = AMPLITUDE_PERCENT_PRNT;
      }
   } else
   {
      Value = CurrentSetup.AmpControl;
      ValueFlag = TRUE;
      Val_ID = AMPLITUDE_PRNT;
   }
   VGAPrintParam = PAMPLITUDEA;
}

/**----------------------------------------------**
 ** This function displays the Afterburst Delay. **
 **----------------------------------------------**/
void PrintSetup0023(void)
{
   FormatVariables(CurrentPreset.AbDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   LangStrCpy(VGABuffer, VGAMisc);
   ValueFlag = FALSE;
   Val_ID = ABRUST_DLY_PRNT;
   VGAPrintParam = PAFTERBURSTDELAY;
}

/**-----------------------------------------**
 ** This function displays the Amplitude(A) **
 ** indented if the Amplitude is ON.        **
 **-----------------------------------------**/
void PrintSetup0016(void)
{
   if (((CurrentPreset.Amp2Flag & BIT0) == TRUE) && ((CurrentSetup.AmpControl
         & BIT0) == TRUE))
   { // Internal
      ConvertNumberToString(CurrentPreset.Amp1);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = AMPA_PRNT;
      VGAPrintParam = PAMPLITUDEA1;

   }
}

/**--------------------------------------------**
 ** This function displays the Afterburst time **
 ** indented if Afterburst is on.              **
 **--------------------------------------------**/
void PrintSetup0024(void)
{
   FormatVariables(CurrentPreset.AbTime, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   ValueFlag = FALSE;
   Val_ID = ABTIME_PRNT;
   VGAPrintParam = PAFTERBURSTTIME;
}

/**-----------------------------------------**
 ** This function displays the Amplitude(B) **
 ** indented if Amplitude Step is on.       **    
 **-----------------------------------------**/
void PrintSetup0017(void)
{
   if (((CurrentPreset.Amp2Flag & BIT0) == TRUE) && ((CurrentSetup.AmpControl
         & BIT0) == TRUE))
   { // Internal
      ConvertNumberToString(CurrentPreset.Amp2);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = AMPB_PRNT;
      VGAPrintParam = PAMPLITUDEB;
   }
}

/**-----------------------------------------**
 ** This function displays the Afterburst   **
 **  Amplitude indented if Afterburst is on.**
 **
 -----------------------------------------**/
void PrintSetup0025(void)
{
   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal
      ConvertNumberToString(CurrentPreset.AbAmp);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = ABAMP_PRNT;
      VGAPrintParam = PAFTERBURSTAMP;
   }
}

/**---------------------------------------------**
 ** This function displays the Energy Braking   **
 ** state - On or Off                           **
 **---------------------------------------------**/
void PrintSetup0025A(void)
{
   Value = (UINT8) CurrentPreset.EnergyBraking;
   ValueFlag = TRUE;
   Val_ID = ENRGYBRAKING_PRNT;
   VGAPrintParam = PENERGYBRAKING;
}

/**-----------------------------------------------**
 ** This function displays the Amplitude Step  At.**
 **-----------------------------------------------**/
UINT16 PrintSetup0018A(void)
{
   UINT16 param = PAMPLITUDEA;

   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal

      if ((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      {
         /* Stepping enabled on time          */
         if ((CurrentPreset.Amp2Flag & BIT2) == FALSE)
         {
            FormatVariables(CurrentPreset.AmpTrigTimeValue, TIME, VGAMisc, 6,
                  CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_TIME_PRNT;
         }
         /* Stepping enabled on energy        */
         else if ((CurrentPreset.Amp2Flag & BIT3) == FALSE)
         {
            FormatVariables(CurrentPreset.AmpTrigEnerValue,
                  CurrentPreset.AmpTrigEnerValue > ENERGYPOINT ? ENERGYDIV10
                        : ENERGY, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_ENRGY_PRNT;
         }
         /* Stepping enabled on peak power    */
         else if ((CurrentPreset.Amp2Flag & BIT4) == FALSE)
         {
            FormatVariables(CurrentPreset.AmpTrigPowerValue, PERCENTX10,
                  VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_PKPOWEER_PRNT;
         }
         /* Stepping enabled on collapse dist */
         else if ((CurrentPreset.Amp2Flag & BIT5) == FALSE)
         {
            FormatVariables(CurrentPreset.AmpTrigColValue, DISTANCE, VGAMisc,
                  6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_COLDIST_PRNT;
         }
         /* Stepping enabled on External Signal */
         else if ((CurrentPreset.Amp2Flag & BIT7) == FALSE)
         {
            Value = 1;
            ValueFlag = TRUE;
            Val_ID = STEP_EXTSIGNAL_PRNT;
         } else
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = STEP_OFF_PRNT;
         }
         VGAPrintParam = param;
      }
   }
   return (param);
}

/**--------------------------------------------**
 ** This function displays the Post Weld Seek. **
 **-------------------------------------------**/
void PrintSetup0026(void)
{
   Value = (UINT8) (CurrentPreset.SeekFunFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = POSTWELD_PRNT;
   VGAPrintParam = PPOSTWELDSEEK;
}

/**---------------------------------------------**
 ** This function displays the Pretrigger flag. **
 **---------------------------------------------**/
void PrintSetup0019(void)
{
   Value = (UINT8) CurrentPreset.PreTrigFlag;
   ValueFlag = TRUE;
   Val_ID = PRETRIG_PRNT;
   VGAPrintParam = PPRETRIGGER;
}

/**----------------------------------------------**
 ** This function displays the Frequency Offset. **
 **----------------------------------------------**/
void PrintSetup0027(void)
{
   if (CurrentSetup.FreqControl == TRUE)
   {
      if ((CurrentPreset.FreqOffsetFlag & BIT0) == BIT0)
      {
         ConvertNumberToString(CurrentPreset.FreqOffset);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = FREQ_OFFSET_VAL_PRNT;
      } else
      {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = FREQ_OFFSET_PRNT;
      }
   } else
   {
      Value = 1;
      ValueFlag = TRUE;
      Val_ID = FREQ_OFFSET_PRNT;

   }
   VGAPrintParam = PFREQCONTROL;
}

/**-------------------------------------------------**
 ** This function displays the Pretrigger mode.     **
 **-------------------------------------------------**/
void PrintSetup0019B(void)
{
   if (CurrentViewPreset.PreTriggerDistanceFlag == FALSE) // Pretrigger off
   {
      Value = 0;
      Val_ID = PRETRIG_TYPE_PRNT;
   } else if (CurrentViewPreset.PreTrigDelayFlag == FALSE) // Pretrigger on delay
   {
      Value = 1;
      Val_ID = PRETRIG_TYPE_PRNT;
   } else // None of the above, auto
   {
      Value = 2;
      Val_ID = PRETRIG_TYPE_PRNT;
   }
   ValueFlag = TRUE;

   VGAPrintParam = PAUTOPRETRIGGER;
}

/**----------------------------------------**
 ** This function displays the Max Timeout **
 **----------------------------------------**/
void PrintSetup0070(void)
{
   if ((CurrentPreset.WeldMode == GRDDETECTMODE) || (((CurrentPreset.WeldMode
         == ENERGYMODE) || (CurrentPreset.WeldMode == COLLAPSEMODE))
         && (CurrentSetup.ControlLevel >= LEVEL_e)) ||

   (((CurrentPreset.WeldMode == PKPOWERMODE) || (CurrentPreset.WeldMode
         == ABSOLUTEMODE)) && (CurrentSetup.ControlLevel >= LEVEL_ea)))
   {
      FormatVariables(CurrentPreset.MaxTimeout, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MAX_TIMEOUT_PRNT;
      VGAPrintParam = PMAXTIMEOUT;
   }
}

/**----------------------------------------**
 ** This function displays the External    **
 ** Trigger Delay - on or off              **
 **----------------------------------------**/
void PrintSetup0070A(void)
{
   Value = (UINT8) (CurrentPreset.ExtTrgDelay);
   ValueFlag = TRUE;
   Val_ID = EXTTRIG_DLY_PRNT;
   VGAPrintParam = PEXTTRIGDLY;
}

/**--------------------------------------------**
 ** This function displays the Digital Tune    **
 **--------------------------------------------**/
void PrintConfig0081(void)
{
   UINT32 DigTuneVal;

   DigTuneVal = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
   case FREQ15KHZ:
      DigTuneVal += CurrentSetup.DigTune / 8;
      break;
   case FREQ20KHZ:
      DigTuneVal += CurrentSetup.DigTune / 6;
      break;
   case FREQ30KHZ:
      DigTuneVal += CurrentSetup.DigTune / 4;
      break;
   case FREQ60KHZ:
      DigTuneVal += CurrentSetup.DigTune / 2;
      break;
   case FREQ40KHZ:
   default:
      DigTuneVal += CurrentSetup.DigTune / 2;
      break;
   }

   if (CurrentSetup.DigTuneFlag == TRUE)
   {
      ConvertNumberToString(DigTuneVal);
      Value = 2;
      ValueFlag = FALSE;
      Val_ID = DIGITALTUNE_PRNT;
   } else
   {
      Value = (UINT8) CurrentSetup.DigTuneFlag;
      ValueFlag = TRUE;
      Val_ID = DIGITALTUNE_PRNT;
   }
   VGAPrintParam = DIGITALTUNE;
}

/**--------------------------------------------------------**
 ** This function displays the Pretrigger At Distance/Time **
 **--------------------------------------------------------**/
void PrintSetup0019A(void)
{
	VGAPrintParam = PPRETRIGGERDISTANCE;
    if ((CurrentPreset.PreTriggerDistanceFlag & BIT0) == FALSE)
    {
        FormatVariables(CurrentPreset.PreTriggerDistance, DISTANCE, VGAMisc, 6,
               CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DIST_PRNT;
    } else if ((CurrentPreset.PreTrigDelayFlag & BIT0) == FALSE)
    {
       FormatVariables(CurrentPreset.PreTrigDelay, TIME, VGAMisc, 6,
              CurrentSetup.Units);
        strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DLY_PRNT;
    } else {
      Value = 0;
      Val_ID = BLANK_PRNT;
      VGAPrintParam = 0;
    }
}

/**--------------------------------------------**
 ** This function displays the Test Amplitude. **
 **--------------------------------------------**/
void PrintSetup0067(void)
{
   ConvertNumberToString(CurrentPreset.TestAmp);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TESTAMP_PRNT;
   VGAPrintParam = PTESTAMPLITUDE;
}

/**--------------------------------------------------**
 ** This function displays the Pretrigger Amplitude. **
 **--------------------------------------------------**/
void PrintSetup0021(void)
{
   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal
      ConvertNumberToString(CurrentPreset.PreTrigAmp);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRETRIG_AMP_PRNT;
      VGAPrintParam = PPRETRIGGERAMP;
   }
}

/**-------------------------------------------**
 ** This function displays the Rapid Traverse **
 **-------------------------------------------**/
void PrintSetup0012(void)
{
   Value = (UINT8) CurrentPreset.RTFlag;
   ValueFlag = TRUE;
   Val_ID = RAPIDTRAVS_PRNT;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------**
 ** This function displays the R/T At Distance. **
 **---------------------------------------------**/
void PrintSetup0013(void)
{
   FormatVariables(CurrentViewPreset.RTDist, DISTANCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = RAPIDTRAVS_DIST_PRNT;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------------**
 ** This function displays the Actuator Clear Output. **
 **---------------------------------------------------**/
void PrintConfig0033(void)
{
   Value = (UINT8) (CurrentPreset.ActClrFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = ACTCLEAR_OUT_PRNT;
   VGAPrintParam = PACTCLEAROUTPUT;
}

/**--------------------------------------**
 ** This function displays the Distance. **
 **--------------------------------------**/
void PrintConfig0033A(void)
{
   if (CurrentSetup.HandHeld == FALSE)
   {
      FormatVariables(CurrentPreset.ActClrDistance, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = ACTCLEAR_DIST_PRNT;
      VGAPrintParam = PACTCLEARDISTANCE;
   } else
   {
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight;
   }
}

/**----------------------------------------------**
 ** This function displays the Cycle Abort Flag. **
 **----------------------------------------------**/
void PrintSetup0071(void)
{ // ae

   if (!((CurrentPreset.WeldMode == GRDDETECTMODE) && (CurrentSetup.Actuator
         == AE)))
   {
      Value = (UINT8) CurrentPreset.CycleAbortFlag;
      ValueFlag = TRUE;
      Val_ID = CYCLEABORT_PRNT;
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight; /* leave right half-page blank */
      VGAPrintParam = PCYCLEABORTS;
   }
}

/**------------------------------------------------------**
 ** This function displays the Ground Detect Abort Flag. **
 **------------------------------------------------------**/
void PrintSetup0033(void)
{
   if (CurrentPreset.WeldMode != GRDDETECTMODE)
   {
      Value = (UINT8) CurrentPreset.GndDetectFlag;
      ValueFlag = TRUE;
      Val_ID = GRDDETECT_ABORT_PRNT;
      VGAPrintParam = PSCRUBTIME;
   }
}

/**-----------------------------------------------**
 ** This function displays the Missing Part Flag. **
 **-----------------------------------------------**/
void PrintConfig0071(void)
{
   Value = (UINT8) CurrentPreset.MissingPartFlag;
   ValueFlag = TRUE;
   Val_ID = MISSINGPART_PRNT;
   VGAPrintParam = PMISSINGPARTFLAG;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Max **
 **---------------------------------------------------**/
void PrintConfig0073(void)
{
   if (CurrentPreset.MissingMaxFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MISSINGPART_MAXOFF_PRNT;
   } else
   {
      FormatVariables(CurrentPreset.MissingPartMax, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MISSINGPART_MAX_PRNT;
   }
   VGAPrintParam = PMISSINGPARTMAX;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Min **
 **---------------------------------------------------**/
void PrintConfig0072(void)
{
   if (CurrentPreset.MissingMinFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MISSINGPART_MINOFF_PRNT;
   } else
   {
      FormatVariables(CurrentPreset.MissingPartMin, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MISSINGPART_MIN_PRNT;
   }
   VGAPrintParam = PMISSINGPARTMIN;
}

/**--------------------------------------------**
 ** This function displays the Control Limits. **
 **--------------------------------------------**/
void PrintSetup0028(void)
{ // ae
   if (!((CurrentPreset.WeldMode == PKPOWERMODE) && (CurrentSetup.Actuator
         == AE)))
   {
      Value = (UINT8) (CurrentPreset.ControlLimitsFlag & BIT0);
      ValueFlag = TRUE;
      Val_ID = CTRL_LIMITS_PRNT;
      VGAPrintParam = PCONTROLLIMITS;
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight; /* leave right half-page blank */
   }
}

/**---------------------------------------------**
 ** This function displays the Collapse Cutoff. **
 **---------------------------------------------**/
void PrintSetup0034B(void)
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
      if (CurrentPreset.WeldMode != COLLAPSEMODE)
      {
         if (CurrentPreset.ColCutoffFlag)
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = COLCUTOFF_PRNT;
         } else
         {
            FormatVariables(CurrentPreset.ColCutoffDist, DISTANCE, VGAMisc, 6,
                  CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = COLCUTOFF_DIST_PRNT;
         }
      }
      VGAPrintParam = PCOLLAPSECUTOFF;
   }
}

/**-------------------------------------------------**
 ** This function displays the Energy Compensation. **
 **-------------------------------------------------**/
void PrintSetup0029(void)
{
   if (CurrentPreset.WeldMode != PKPOWERMODE)
   { // until 2.5
      if (CurrentPreset.WeldMode == TIMEMODE)
      {
         Value = (UINT8) (CurrentPreset.EnergyCompFlag & BIT0);
         ValueFlag = TRUE;
         Val_ID = ENRGYCOMP_PRNT;
         VGAPrintParam = PENERGYCOMP;
      }
   }
}

/**---------------------------------------------**
 ** This function displays the Absolute Cutoff. **
 **---------------------------------------------**/
void PrintSetup0034A(void)
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator==MICRO) || (CurrentSetup.Actuator==MICROC))
   {
      if (CurrentPreset.WeldMode != ABSOLUTEMODE)
      {
         if (CurrentPreset.ABSCutoffFlag)
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = ABSCUTOFF_PRNT;
         } else
         {
            FormatVariables(CurrentPreset.ABSCutoffDist, DISTANCE, VGAMisc, 6,
                  CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = ABSCUTOFF_DIST_PRNT;
         }
         VGAPrintParam = PABSOLUTECUTOFF;
      }
   }
}

void PrintSetup0031(void)
{
   if (CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentPreset.EnergyPL,
         /* cont'd */CurrentPreset.EnergyPL > ENERGYPOINT ? ENERGYDIV10
               : ENERGY,
         /* cont'd */VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = MAXENRGY_PRNT;
         VGAPrintParam = PENERGYMAX;
      }
   }
}

/**-----------------------------------------------**
 ** This function displays the Peak Power Cutoff. **
 **-----------------------------------------------**/
void PrintSetup0032(void)
{
   if (CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentPreset.PeakPwrCutoffFlag) /* FALSE = on */
      {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = PKPOWERCUTOFF_PRNT;
      } else
      {
         FormatVariables(CurrentPreset.PeakPwrCutoff, PERCENTX10, VGAMisc, 6,
               CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PKPOWERCUTOFF_VAL_PRNT;
      }
      VGAPrintParam = PPKPOWERCUTOFF;
   }
}

/**----------------------------------------**
 ** This function displays the Min Energy. **
 **----------------------------------------**/
void PrintSetup0030(void)
{
   if (CurrentPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentPreset.EnergyML,
         /* cont'd */CurrentPreset.EnergyML > ENERGYPOINT ? ENERGYDIV10
               : ENERGY,
         /* cont'd */VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = MINENRGY_PRNT;
         VGAPrintParam = PENGERGYMIN;
      }
   }
}

/**--------------------------------------------------**
 ** This function displays the aef Settings message. **
 **--------------------------------------------------**/
void PrintAEFSetting(void)
{

   Value = 0;
   ValueFlag = TRUE;
   Val_ID = AEF_SETTINGS_PRNT;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PrintLineHeight;
}

/**-------------------------------------------**
 ** This function displays the Trigger Force. **
 **-------------------------------------------**/
void PrintSetup0005(void)
{
   FormatVariables(CurrentPreset.TriggerForce, FORCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TRIGFORCE_PRNT;
   VGAPrintParam = PTRIGGERFORCE;
}

/**---------------------------------------**
 ** This function displays the Downspeed. **
 **---------------------------------------**/
void PrintSetup0014(void)
{
//   ConvertNumberToString(CurrentPreset.DownSpdStart);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = DOWNSPEED_PRNT;
   VGAPrintParam = PDOWNSPEED;
}

/**-------------------------------------------**
 ** This function displays the Trigger Delay. **
 **-------------------------------------------**/ 
void PrintSetup0006(void)
{
   if ((CurrentPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == FALSE)
   {
      FormatVariables(CurrentPreset.TriggerDelay, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PKPOWERCUTOFF_VAL_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PKPOWERCUTOFF_TXT;
   }

   VGAPrintParam = PTRIGGERDELAY;
}

/**---------------------------------------**
 ** This function displays the Weld Pressure 
 ** Step or Value
 **---------------------------------------**/
void PrintSetup0007(void)
{
   if ((CurrentPreset.Pressure2Flag & BIT0) == TRUE) {
      Value = (UINT8) (CurrentPreset.Pressure2Flag & BIT0);
      ValueFlag = TRUE;
      Val_ID = PRESSURE_STEP_TXT;
   }
   else {
      FormatVariables(CurrentPreset.WeldPressure, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELD_PRESSURE_TXT;
   }
   VGAPrintParam = PPRESSUREA;
}

/**------------------------------------------**
 ** This function displays the Weld Pressure(A).**
 **------------------------------------------**/
void PrintSetup0008(void)
{
   if ((CurrentPreset.Pressure2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentPreset.WeldPressure, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_A_TXT;

      VGAPrintParam = PPRESSUREA1;
   }
}


/**------------------------------------------**
 ** This function displays the Weld Pressure(B).**
 **------------------------------------------**/
void PrintSetup0009(void)
{
   if ((CurrentPreset.Pressure2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentPreset.Pressure2, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_B_TXT;

      VGAPrintParam = PPRESSUREB;
   }
}

/**--------------------------------**
 ** This function display Pressure
 ** Stepping trigger points and its
 ** value.
 **--------------------------------**/
UINT16 PrintSetup0018B(void)
{
   UINT16 param = PPRESSUREA1;

   if ((CurrentPreset.Pressure2Flag & BIT0) == TRUE) {
      /* Stepping enabled on time          */
      if ((CurrentPreset.Pressure2Flag & BIT2) == FALSE) {
         FormatVariables(CurrentPreset.PressureTrigTimeValue, TIME, VGAMisc, 6,
               CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_TIME_TXT;
      }
      /* Stepping enabled on energy        */
      else if ((CurrentPreset.Pressure2Flag & BIT3) == FALSE) {
         FormatVariables(CurrentPreset.PressureTrigEnerValue,
               CurrentPreset.PressureTrigEnerValue > ENERGYPOINT ?
                     ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_ENRGY_TXT;
      }
      /* Stepping enabled on peak power    */
      else if ((CurrentPreset.Pressure2Flag & BIT4) == FALSE) {
         FormatVariables(CurrentPreset.PressureTrigPowerValue, PERCENTX10,
               VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_PKPOWER_TXT;
      }
      /* Stepping enabled on collapse dist */
      else if ((CurrentPreset.Pressure2Flag & BIT5) == FALSE) {
         FormatVariables(CurrentPreset.PressureTrigColValue, DISTANCE, VGAMisc,
               6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_COLDIST_TXT;
      }
      /* Stepping enabled on external signal */
      else if ((CurrentPreset.Pressure2Flag & BIT7) == FALSE) {
         Value = 1;
         ValueFlag = TRUE;
         Val_ID = PRESSURE_STEP_EXTSIGNAL_TXT;
      }
      else {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = PRESSURE_STEP_OFF_TXT;
      }
      VGAPrintParam = param;
   }
   return (param);
}

void PrintAEDTrigForce(void)
{
   FormatVariables(CurrentViewPreset.TriggerForce, FORCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PRETRIG_FORCE_PRNT;
   VGAPrintParam = PTRIGGERFORCE;
}

/**----------------------------------------------------**
 ** This function displays the System (gauge) Pressure.**
 **----------------------------------------------------**/
void PrintSystemGaugePressure(void)
{
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = GAUGEPRESSURE_PRNT;
   VGAPrintParam = ALWAYS;
}

/**------------------------------------------**
 ** This function displays the Reject Limits.**
 **------------------------------------------**/
void PrintSetup0051(void)
{
   Value = (UINT8) (CurrentPreset.RejectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJLIMITS_PRNT;
   VGAPrintParam = PREJECTLIMITS;
}

/**-------------------------------------------**
 ** This function displays the Suspect Limits.**
 **-------------------------------------------**/
void PrintSetup0035(void)
{
   Value = (UINT8) (CurrentPreset.SuspectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = SUSPTLIMITS_PRNT;
   VGAPrintParam = PSUSPECTLIMITS;
}

/**--------------------------------------------------**
 ** This function displays the Reject Reset Required.**
 **--------------------------------------------------**/
void PrintSetup0052(void)
{
   Value = (UINT8) (CurrentPreset.RejResetRequiredFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJRESET_PRNT;
   VGAPrintParam = PREJRESETREQ;
}

/**---------------------------------------------------**
 ** This function displays the Suspect Reset Required.**
 **---------------------------------------------------**/
void PrintSetup0036(void)
{
   Value = (UINT8) (CurrentPreset.SusResetRequired & BIT0);
   ValueFlag = TRUE;
   Val_ID = SUSPTRESET_PRNT;
   VGAPrintParam = PSUSPRESETREQ;
}

/**-----------------------------------------------**
 ** This function displays the + Collapse R Limit.**
 **-----------------------------------------------**/
void PrintSetup0059(void)
{
   if ((CurrentPreset.RejectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the + Collapse S Limit.**
 **-----------------------------------------------**/
void PrintSetup0043(void)
{
   if ((CurrentPreset.SuspectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse R Limit.**
 **-----------------------------------------------**/
void PrintSetup0060(void)
{
   if ((CurrentPreset.RejectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LCOLLAPSEMINUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse S Limit.**
 **-----------------------------------------------**/
void PrintSetup0044(void)
{
   if ((CurrentPreset.SuspectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentPreset.ColMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_SLIMT_PRNT;
   } else

   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LCOLLAPSEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Energy R Limit.**
 **---------------------------------------------**/
void PrintSetup0055(void)
{
   if ((CurrentPreset.RejectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyPLR,
      /* cont'd */CurrentPreset.EnergyPLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the + Energy S Limit.**
 **---------------------------------------------**/
void PrintSetup0039(void)
{
   if ((CurrentPreset.SuspectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyPLS,
      /* cont'd */CurrentPreset.EnergyPLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy R Limit.**
 **---------------------------------------------**/
void PrintSetup0056(void)
{
   if ((CurrentPreset.RejectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyMLR,
      /* cont'd */CurrentPreset.EnergyMLR > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy S Limit.**
 **---------------------------------------------**/
void PrintSetup0040(void)
{
   if ((CurrentPreset.SuspectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentPreset.EnergyMLS,
      /* cont'd */CurrentPreset.EnergyMLS > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute R Limit.**
 **-----------------------------------------------**/
void PrintSetup0061(void)
{
   if ((CurrentPreset.RejectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute S Limit.**
 **-----------------------------------------------**/
void PrintSetup0045(void)
{
   if ((CurrentPreset.SuspectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute R Limit.**
 **-----------------------------------------------**/
void PrintSetup0062(void)
{
   if ((CurrentPreset.RejectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LABSOLUTEMINUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute S Limit.**
 **-----------------------------------------------**/
void PrintSetup0046(void)
{
   if ((CurrentPreset.SuspectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentPreset.AbsMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LABSOLUTEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Power  R Limit.**
 **---------------------------------------------**/
void PrintSetup0057(void)
{
   if ((CurrentPreset.RejectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerPLR, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the + Power  S Limit.**
 **---------------------------------------------**/
void PrintSetup0041(void)
{
   if ((CurrentPreset.SuspectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerPLS, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  R Limit.**
 **---------------------------------------------**/
void PrintSetup0058(void)
{
   if ((CurrentPreset.RejectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerMLR, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  S Limit.**
 **---------------------------------------------**/
void PrintSetup0042(void)
{
   if ((CurrentPreset.SuspectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentPreset.PowerMLS, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   R Limit.**
 **---------------------------------------------**/
void PrintSetup0053(void)
{
   if ((CurrentPreset.RejectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimePLR, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   S Limit.**
 **---------------------------------------------**/
void PrintSetup0037(void)
{
   if ((CurrentPreset.SuspectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimePLS, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   R Limit.**
 **---------------------------------------------**/
void PrintSetup0054(void)
{
   if ((CurrentPreset.RejectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimeMLR, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_RLIMT_OFF_PRNT;
   }
  VGAPrintParam = LTIMEMINUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   S Limit.**
 **---------------------------------------------**/
void PrintSetup0038(void)
{
   if ((CurrentPreset.SuspectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentPreset.TimeMLS, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTIMEMINUS;
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force R Limit.**
 **-------------------------------------------------**/
void PrintSetup0065(void)
{
   if ((CurrentPreset.RejectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForcePLR, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LRMAXFORCE; // LCOLLAPSEPLUS the same group
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force S Limit.**
 **-------------------------------------------------**/
void PrintSetup0049(void)
{
   if ((CurrentPreset.SuspectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForcePLS, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LMAXFORCEPLUS;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force R Limit.**
 **-------------------------------------------------**/
void PrintSetup0066(void)
{
   if ((CurrentPreset.RejectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForceMLR, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LRMAXFORCE;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force S Limit.**
 **-------------------------------------------------**/
void PrintSetup0050(void)
{
   if ((CurrentPreset.SuspectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentPreset.WeldForceMLS, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LMAXFORCEMINUS;
}
/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0063(void)
{
   if ((CurrentPreset.RejectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   {
      FormatVariables(CurrentPreset.TrsDistPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void PrintSetup0047(void)
{
   if ((CurrentPreset.SuspectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   {
      FormatVariables(CurrentPreset.TrsDistPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0064(void)
{
   if ((CurrentPreset.RejectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   {
      FormatVariables(CurrentPreset.TrsDistMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Power Band R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0081(void)
{
   if (!CurrentPreset.PMCPlusBandFlag)
   {
      ConvertNumberToString(CurrentPreset.PMCHighLimit);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPOWERBAND_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPOWERBAND_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - Power Band R Limit.**
 **-------------------------------------------------------**/
void PrintSetup0082(void)
{
   if (!CurrentPreset.PMCMinusBandFlag)
   {
      ConvertNumberToString(CurrentPreset.PMCLowLimit);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPOWERBAND_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPOWERBAND_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0083(void)
{
   if (!(CurrentPreset.SBLFreqFlags & BIT1))
   {
      ConvertNumberToString(CurrentPreset.SBLMaxFreq);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PSBLFREQ_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PSBLFREQ_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0084(void)
{
   if (!(CurrentPreset.SBLFreqFlags & BIT0))
   {
      ConvertNumberToString(CurrentPreset.SBLMinFreq);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MSBLFREQ_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MSBLFREQ_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R Downspeed Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0085(void)
{
	if ((CurrentPreset.RVelLimitMask & BIT2) != BIT2) {
	  FormatVariables(CurrentPreset.VelocityPLR, VELOCITY, VGAMisc, 6,
			 	               CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = PDOWNSPEED_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PDOWNSPEED_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LDOWNSPEEDPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - R Downspeed Limit.   **
 **-------------------------------------------------------**/
void PrintSetup0086(void)
{
	if ((CurrentPreset.RVelLimitMask & BIT1) != BIT1) {
	  FormatVariables(CurrentPreset.VelocityMLR, VELOCITY, VGAMisc, 6,
		 	               CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
	  Value = 0;
      ValueFlag = FALSE;
      Val_ID = MDOWNSPEED_RLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MDOWNSPEED_RLIMT_OFF_PRNT;
   }
   VGAPrintParam = LDOWNSPEEDMINUS;
}
/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void PrintSetup0048(void)
{
   if ((CurrentPreset.SuspectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   {
      FormatVariables(CurrentPreset.TrsDistMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_SLIMT_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_SLIMT_OFF_PRNT;
   }
   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-----------------------------------------------------**
 ** This function prints the page number left justified **
 ** at top of page.                                     **
 **-----------------------------------------------------**/
void PrintHeader1(UINT8 PageNumber)
{
   SINT8 TempStr[20];

   /* print page number */
   sprintf(TempStr, " %d", PageNumber);
   strcpy(VGABuffer, TempStr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PAGE_NO_PRNT;
   VGAPrintParam = ALWAYS;
}

/**------------------------------------------------------------------**
 ** This function prints date                                        **
 **------------------------------------------------------------------**/
void PrintHeader2(void)
{
   /* send date strings */
   GetDateTime();
   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = DATE_PRNT;
   VGAPrintParam = ALWAYS;
}

/**------------------------------------------------------------------**
 ** This function prints preset number and date                      **
 **------------------------------------------------------------------**/
void PrintSubHeader2(void)
{
   SINT8 TempStr[20];

   /* format PRESET =, etc. */
   PresetCheck = CurrentSetup.ActivePreset;
   if (PresetCheck)
   {
      strcpy(TempVGABuffer, "PRESET = [ ");
      strcat(TempVGABuffer, "Preset");
      sprintf(TempStr, "%d - ", PresetCheck);
      strcat(TempVGABuffer, TempStr);
      strcat(TempVGABuffer, CurrentPreset.PresetID);
   } else
      strcpy(TempVGABuffer, "Preset0 ");

   /* if preset not updated then flag it with an "*" */
   if (!CurrentPreset.PresetUpdateComplete)
      strcat(TempVGABuffer, "*");
   strcat(TempVGABuffer, " ]");

   /* print PRESET =, etc. */
   strcpy(VGABuffer, TempVGABuffer);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PRESET_NUM_PRNT;
   VGAPrintParam = ALWAYS;

}

/**------------------------------------------------------------------**
 ** This function prints time and preset creation date               **
 **------------------------------------------------------------------**/
void PrintHeader3(void)
{
   /* print time string, left-adjusted */
   strcpy(VGABuffer, timestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TIME_CREATED_DATE_PRNT;
   VGAPrintParam = ALWAYS;
}

/**------------------------------------------------------------------**
 ** This function prints time and preset creation date               **
 **------------------------------------------------------------------**/
void PrintSubHeader3(void)
{
   /* print Created On:... */
   strcpy(VGABuffer, datestr);

   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TIME_CREAT_DATE_SUB_PRNT;
   VGAPrintParam = ALWAYS;
}

void AssignYCoordinate(void)
{
   if (RightPrintYCoordinate > LeftPrintYCoordinate)
      LeftPrintYCoordinate = RightPrintYCoordinate;
   else if (RightPrintYCoordinate < LeftPrintYCoordinate)
      RightPrintYCoordinate = LeftPrintYCoordinate;
}

/********************************** SystemPresetReport3 *********************************/

/**----------------------------------------------**
 ** This function returns the input string ptr,  **
 ** selected on the input port.                  ** 
 **----------------------------------------------**/
UINT8 GetSelectInStr(UINT16 InputBit)
{
   UINT8 Value;

   switch (InputBit)
   {
   case INPUT_DISABLED:
      Value = 0;
      break;
   case INPUT_PRESET1:
      /* If 'Select Preset1' is selcted to J3_32 port pin.*/
      Value = 1;
      break;
   case INPUT_PRESET2:
      /* If 'Select Preset2' is selcted to J3_33 port pin.*/
      Value = 2;
      break;
   case INPUT_PRESET3:
      /* If 'Select Preset4' is selcted to J3_19 port pin.*/
      Value = 3;
      break;
   case INPUT_PRESET4:
      /* If 'Select Preset8' is selcted to J3_17 port pin.*/
      Value = 4;
      break;
   case INPUT_PRESET5:
      /* If 'Select Preset16' is selcted to J3_31 port pin.*/
      Value = 5;
      break;
   case INPUT_EXT_TRIGDELAY:
      /* Return External Trigger Delay pointer */
      Value = 6;
      break;
   case INPUT_DISP_LOCK:
      /* Return DisplayLock pointer */
      Value = 7;
      break;
   case INPUT_EXT_TRIGGER:
      /* Return Ext Cycle Abort ponter. */
      Value = 8;
      break;
   case INPUT_SONICS_DISABLE:
      /* Return SonicDisable pointer*/
      Value = 9;
      break;
   case INPUT_MEM_RESET:
      /* Return Menmory Reset pointer. */
      Value = 10;
      break;
   case INPUT_PART_CLAMPED:
      /* Return PartClamped pointer. */
      Value = 11;
      break;
   case INPUT_SYNC_IN:
      /* Return SyncIn pointer. */
      Value = 12;
      break;
   case INPUT_PART_PRESENT:
      Value = 13;
      break;
   case INPUT_CONFIRM_REJECT:
	  Value = 14;
	  break;
   default:
      Value = 0;
      break;

   }
   return (Value);
}

/**----------------------------------------------**
 ** This function returns the output string ptr, **
 ** selected on the output port.                 ** 
 **----------------------------------------------**/
UINT8 GetSelectOutStr(UINT16 OutputBit)
{
   UINT8 Value;

   switch (OutputBit)
   { /* Get the selected output string. */
   case OUTPUT_DISABLED:
      Value = 0;
      break;
   case OUTPUT_CFMPRESET:
      Value = 1;
      break;
   case OUTPUT_EXT_BEEPER:
      Value = 3;
      break;
   case OUTPUT_CYCLE_OK:
      Value = 4;
      break;
   case OUTPUT_NO_CYCLEALARM:
      Value = 5;
      break;
   case OUTPUT_OLDALARM:
      Value = 6;
      break;
   case OUTPUT_MDFY_ALARM:
      Value = 7;
      break;
   case OUTPUT_NOTE:
      Value = 8;
      break;
   case OUTPUT_MISSING_PART:
      Value = 9;
      break;
   case OUTPUT_PART_CLAMPED:
      Value = 10;
      break;
   case OUTPUT_SYNC_OUT:
      Value = 11;
      break;
   case OUTPUT_UDIREADY:
      Value = 12;
      break;
   default:
      Value = 0;
      break;
   }
   return (Value);
}

void GetCylinderStr(void)
/****************************************************************************/
/*                                                                          */
/* Update Cylinder diameter strings. Same algorithm applies to stroke       */
/* length strings.                                                          */
/*                                                                          */
/****************************************************************************/
{
	   switch (CurrentSetup.CylinDiameter)
	   {
	   case CUSTOMSIZE:
	      Value = ELEVEN;
	      break;

	   case SIZE1_5:
	      Value = ZERO;
	      break;

	   case SIZE2_0:
	      Value = ONE;
	      break;

	   case SIZE2_5:
	      Value = TWO;
	      break;

	   case SIZE3_0:
	      Value = THREE;
	      break;

	   case SIZE3_25:
	      Value = FOUR;
	      break;

	   case SIZE4_0:
	      Value = FIVE;
	      break;

	   case SIZE_32:
	      Value = SIX;
	      break;

	   case SIZE_40:
	      Value = SEVEN;
	      break;

	   case SIZE_50:
	      Value = EIGHT;
	      break;

	   case SIZE_63:
	      Value = NINE;
	      break;

	   case SIZE_80:
	      Value = TEN;
	      break;

	   default:
	      break;
	   }
}

void GetStrokeLenStr(void)
{
   switch (CurrentSetup.StrokeLen)
   {
   case LENGTH_4:
      Value = ZERO;
      break;

   case LENGTH_5:
      Value = ONE;
      break;

   case LENGTH_6:
      Value = TWO;
      break;

   case LENGTH_2:
      Value = THREE;
      break;

   case LENGTH_8:
      Value = FOUR;
      break;

   case LENGTH_70:
      Value = FIVE;
      break;

   case LENGTH_80:
      Value = SIX;
      break;

   case LENGTH_100:
      Value = SEVEN;
      break;

   case LENGTH_125:
      Value = EIGHT;
      break;

   case LENGTH_50:
      Value = NINE;
      break;

   case CUSTOMLEN:
      Value = TEN;
      break;

   case LENGTH_75:
      Value = ELEVEN;
      break;

   default:
      break;
   }
}

/**-----------------------------------------------**
 ** This function displays  the selected Language **
 **-----------------------------------------------**/
void PrintConfig0018(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = LANG_PRNT;
   VGAPrintParam = PLANGUAGE;
}
/**-----------------------------------**
 ** This function displays  the Units **
 **-----------------------------------**/
void PrintConfig0019(void)
{
   Value = (UINT8) (CurrentSetup.Units);
   ValueFlag = TRUE;
   Val_ID = UNITS_PRNT;
   VGAPrintParam = PUNITS;
}
/**--------------------------------------**
 ** This function displays  the Password **
 **--------------------------------------**/
void PrintConfig0020(void)
{
   Value = (UINT8) (CurrentSetup.PassWordFlag);
   ValueFlag = TRUE;
   Val_ID = PASSWORD_PRNT;
   VGAPrintParam = PPASSWORD;
}
// --------------------------------------------
//  This function displays  the Srart Screen 
// --------------------------------------------

void PrintStartScreen(void)
{
   Value = (UINT8) (CurrentSetup.StartScreen);
   ValueFlag = TRUE;
   Val_ID = START_SCREEN_PRNT;
   VGAPrintParam = STRTSCREEN;
}

/**---------------------------------------**
 ** This function displays  General Alarm **
 ** Reset Required                        **
 **---------------------------------------**/
void PrintConfig0027(void)
{
   Value = (UINT8) (CurrentPreset.GeneralAlarmLFlag);
   ValueFlag = TRUE;
   Val_ID = RESET_REQ_PRNT;
   VGAPrintParam = PGENALARMRESET;
}
/**-------------------------------------------**
 ** This function displays the Trigger Beeper **
 **-------------------------------------------**/
UINT16 PrintConfig0028(void)
{
   UINT16 param;
   if (CurrentSetup.HandHeld == FALSE)
   {
      Value = (UINT8) (CurrentSetup.BeeperTrigger);
      ValueFlag = TRUE;
      Val_ID = TRIGGER_BEEP_PRNT;
      param = PTRIGGERBEEPER;
   } else
   {
      Value = (UINT8) (CurrentSetup.BeeperRelease);
      ValueFlag = TRUE;
      Val_ID = RELEASE_BRRP_PRNT;
      param = PRELEASEBEEPER;
   }
   VGAPrintParam = param;
   return (param);
}
/**------------------------------------------**
 ** This function displays  the Error Beeper **
 **------------------------------------------**/
void PrintConfig0029(void)
{
   Value = (UINT8) (CurrentSetup.BeeperError);
   ValueFlag = TRUE;
   Val_ID = ERROR_BEEP_PRNT;
   VGAPrintParam = PERRORBEEPER;
}
/**------------------------------------------**
 ** This function displays  the Alarm Beeper **
 **------------------------------------------**/
void PrintConfig0030(void)
{
   Value = (UINT8) (CurrentSetup.BeeperAlarm);
   ValueFlag = TRUE;
   Val_ID = ALARM_BEEP_PRNT;
   VGAPrintParam = PALARMBEEPER;
}
/**------------------------------------------**
 ** This function displays  the Estop Beeper **
 **------------------------------------------**/
void PrintConfig0178(void)
{
   Value = (UINT8) (CurrentSetup.BeeperEstop);
   ValueFlag = TRUE;
   Val_ID = ESTOP_BEEP_PRNT;
   VGAPrintParam = PESTOPBEEP;
}
/**-----------------------------------------------**
 ** This function displays  the Amplitude Control **
 **-----------------------------------------------**/
void PrintConfig0032(void)
{
   Value = (UINT8) (CurrentSetup.AmpControl);
   ValueFlag = TRUE;
   Val_ID = AMP_CONTROL_PRNT;
   VGAPrintParam = PAMPCONTROL;
}
/**---------------------------------------------------**
 ** This function displays the extra cooling.         **
 **---------------------------------------------------**/
void PrintConfig0040(void)
{
   Value = (UINT8) (CurrentSetup.AmpControl);
   ValueFlag = TRUE;
   Val_ID = EXTRA_COOL_PRNT;
   VGAPrintParam = PEXTRACOOLING;
}

/**----------------------------------------**
 ** This function displays  the Weld Scale **
 **----------------------------------------**/
void PrintConfig0041(void)
{
   if (CurrentSetup.TimeMultiplier == WELDTIMEx1)
      Value = 0;
   else if (CurrentSetup.TimeMultiplier == WELDTIMEx2)
      Value = 1;
   else
      Value = 2;
   ValueFlag = TRUE;
   Val_ID = WELD_SCALE_PRNT;
   VGAPrintParam = PWELDSCALE;
}
/**----------------------------------------**
 ** This function displays  the Test Scale **
 **----------------------------------------**/
void PrintConfig0042(void)
{
   if (CurrentSetup.TestMultiplier == TESTTIMEx1)
      Value = 0;
   else if (CurrentSetup.TestMultiplier == TESTTIMEx2)
      Value = 1;
   else
      Value = 2;
   ValueFlag = TRUE;
   Val_ID = TEST_SCALE_PRNT;
   VGAPrintParam = PTESTSCALE;
}
/**--------------------------------------------**
 ** This function displays  the Digital Filter **
 **--------------------------------------------**/
void PrintConfig0043(void)
{
   Value = (UINT8) (CurrentPreset.DigitalFilterFlag);
   ValueFlag = TRUE;
   Val_ID = DIG_FILT_PRNT;
   VGAPrintParam = PDIGFILTER;
}
/**---------------------------------------------------**
 ** This function displays the Ext Presets.           **
 **---------------------------------------------------**/
void PrintConfig0045(void)
{
   Value = (UINT8) (CurrentSetup.ExtPresets);
   ValueFlag = TRUE;
   Val_ID = EXT_PRESET_PRNT;
   VGAPrintParam = PEXTPRESETS;
}
/**---------------------------------------------**
 ** This function displays Decimal place 2 or 3 **
 **---------------------------------------------**/
void PrintConfig0099(void)
{
   Value = (UINT8) (CurrentSetup.Metric3Flag);
   ValueFlag = TRUE;
   Val_ID = METRIC_DECI_PRNT;
   VGAPrintParam = ALWAYS;
}
/**-------------------------------------------**
 ** This function displays  Sequencing on/off **
 **-------------------------------------------**/
void PrintConfig0098(void)
{
   Value = (UINT8) (CurrentSetup.SequenceEnable);
   ValueFlag = TRUE;
   Val_ID = SEQ_PRESET_PRNT;
   VGAPrintParam = ALWAYS;
}
/**--------------------------------------------**
 ** This function displays  Input J3_32        **
 **--------------------------------------------**/
void PrintConfig0085(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_32In);
   ValueFlag = TRUE;
   Val_ID = J3_32_IN_PRNT;
   VGAPrintParam = PUSERIO;
}
/**--------------------------------------------**
 ** This function displays  Input J3_33        **
 **--------------------------------------------**/
void PrintConfig0086(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_33In);
   ValueFlag = TRUE;
   Val_ID = J3_33_IN_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Input J3_19        **
 **--------------------------------------------**/
void PrintConfig0087(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_19In);
   ValueFlag = TRUE;
   Val_ID = J3_19_IN_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Input J3_17        **
 **--------------------------------------------**/
void PrintConfig0088(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_17In);
   ValueFlag = TRUE;
   Val_ID = J3_17_IN_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Input J3_31        **
 **--------------------------------------------**/
void PrintConfig0089(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_31In);
   ValueFlag = TRUE;
   Val_ID = J3_31_IN_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Input J3_1        **
 **--------------------------------------------**/
void PrintConfig0090(void)
{
   Value = GetSelectInStr(CurrentSetup.J3_1In);
   ValueFlag = TRUE;
   Val_ID = J3_1_IN_PRNT;
   VGAPrintParam = PUSERIO;
}
/**--------------------------------------------**
 ** This function displays  Output J3_36       **
 **--------------------------------------------**/
void PrintConfig0091(void)
{
   UINT16 OutputBit;
   OutputBit = CurrentSetup.J3_36Out;//for old controller board
   Value = GetSelectOutStr(OutputBit);
   ValueFlag = TRUE;
   Val_ID = J3_36_OUT_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Output J3_8        **
 **--------------------------------------------**/
void PrintConfig0092(void)
{
   UINT16 OutputBit;
   OutputBit = CurrentSetup.J3_8Out;
   Value = GetSelectOutStr(OutputBit);
   ValueFlag = TRUE;
   Val_ID = J3_8_OUT_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Output J3_22       **
 **--------------------------------------------**/
void PrintConfig0093(void)
{
   Value = GetSelectOutStr(CurrentSetup.J3_22Out);
   ValueFlag = TRUE;
   Val_ID = J3_22_OUT_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  User Input Logic   **
 **--------------------------------------------**/
void PrintConfig0094(void)
{
   /* display user inputs */
   Value = (UINT8) (CurrentSetup.UserInLogic);
   ValueFlag = TRUE;
   Val_ID = USER_IN_PRNT;
   VGAPrintParam = PUSERIO;
}

/**--------------------------------------------**
 ** This function displays  Ext.Start Delay    **
 **--------------------------------------------**/
void PrintConfig0094A(void)
{
   FormatVariables(CurrentSetup.PartClampDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PART_CLAMP_PRNT;
   VGAPrintParam = ALWAYS;
}
/**--------------------------------------------**
 ** This function displays  Upper Limit Switch **
 **--------------------------------------------**/
void PrintConfig0034(void)
{
   Value = (UINT8) (CurrentSetup.ULSLogicCustom);
   ValueFlag = TRUE;
   Val_ID = ULS_PRNT;
   VGAPrintParam = PULSLOGIC;
}
/**----------------------------------------**
 ** This function displays  Gnd Det Switch **
 **----------------------------------------**/
void PrintConfig0095(void)
{
   /* display user inputs */
   Value = (UINT8) (CurrentSetup.GndDetLogicCustom);
   ValueFlag = TRUE;
   Val_ID = GND_DETECT_PRNT;
   VGAPrintParam = PCUSTOMACT;
}

/**----------------------------------------**
 ** This function displays  Welder Address **
 **----------------------------------------**/
void PrintConfig0096(void)
{

   if ((CurrentSetup.WelderAddrFlag & BIT0) == FALSE)
   {

      FormatVariables(CurrentSetup.WelderAddrValue, INTEGER, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELDER_ADDR_PRNT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = WELDER_ADDR_OFF_PRNT;
   }
   VGAPrintParam = ALWAYS;
}
/**-------------------------------------------**
 ** This function displays  Frequency Offset  **
 **-------------------------------------------**/
void PrintConfig0044(void)
{
   Value = (UINT8) (CurrentSetup.FreqControl);
   ValueFlag = TRUE;
   Val_ID = FREQ_CONTROL_PRNT;
   VGAPrintParam = PFREQCONTROL;
}
/**----------------------------------------**
 ** This function displays  Handheld       **
 **----------------------------------------**/
void PrintConfig0097(void)
{
   /* display user inputs */
   Value = (UINT8) (CurrentSetup.HandHeld);
   ValueFlag = TRUE;
   Val_ID = HAND_HELD_PRNT;
   VGAPrintParam = PHANDHELDSYSTEM;
}
/**-------------------------------------------------**
 ** This function displays Distance as ULS/Start Sw **
 **-------------------------------------------------**/
void PrintConfig0100(void)
{
   Value = (UINT8) (CurrentSetup.DistanceULS);
   ValueFlag = TRUE;
   Val_ID = DIST_ULD_PRNT;
   VGAPrintParam = ALWAYS;
}
/**----------------------------------------**
 ** This function displays CalibrationInfo **
 **----------------------------------------**/
void PrintCalibrationInfo(void)
{
   if (NVR.CalibPass == CALIBPASSED)
      Value = 1; /* Pass */
   else if (NVR.CalibPass == CALIBFAILED)
      Value = 2; /* Fail */
   else
      Value = 3; /* Factory */
   ValueFlag = TRUE;
   Val_ID = CALIB_PRNT;
   VGAPrintParam = PCALINFO; /* Print in left half-page */
}

/**-------------------------------------**
 ** This function displays Power Supply **
 **-------------------------------------**/
void PrintConfig0009(void)
{
   ConvertNumberToString(CurrentSetup.PSWatt);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PS_PRNT;
   VGAPrintParam = PPSSUPPLY;
}
/**--------------------------------------**
 ** This function displays Control Level **
 **--------------------------------------**/
void PrintConfig0011(void)
{

   if (DepotFlag->IsADepot)
      Value = 7;
   else
   {
      switch (CurrentSetup.ControlLevel)
      {
      case LEVEL_t:
         Value = 0;
         break;

      case LEVEL_e:
         Value = 1;
         break;

      case LEVEL_ea:
         Value = 2;
         break;

      case LEVEL_a:
         Value = 3;
         break;

      case LEVEL_d:
         Value = 4;
         break;

      case LEVEL_f:
         Value = 5;
         break;

      case LEVEL_TEST:
         Value = 6;
         break;

      case LEVEL_c:
         Value = 8;
         break;

      default:
         Value = 0;
         break;
      }
   }
   ValueFlag = TRUE;
   Val_ID = CONTROL_LVL_PRNT;
   VGAPrintParam = PCONTROLLEVEL;
}
/**----------------------------------**
 ** This function displays Frequency **
 **----------------------------------**/
void PrintConfig0008(void)
{
   switch (CurrentSetup.PSFreq)
   {
   case FREQ15KHZ:
      Value = 0;
      break;
   case FREQ20KHZ:
      Value = 1;
      break;
   case FREQ30KHZ:
      Value = 2;
      break;
   case FREQ40KHZ:
      Value = 3;
      break;
   case FREQ60KHZ:
      Value = 4;
      break;
   default:
      Value = 1;
      break;
   }

   ValueFlag = TRUE;
   Val_ID = FREQ_PRNT;
   VGAPrintParam = PFREQUENCY;
}
/**-----------------------------------**
 ** This function displays SW Version **
 **-----------------------------------**/
void PrintConfig0012(void)
{
   Value = 0;
   ValueFlag = FALSE;
   strcpy(VGABuffer, SWVersionLabel);
   Val_ID = SW_VER_PRNT;
   VGAPrintParam = PSWVERSION;
}
/**---------------------------------------**
 ** This function displays SBC SW Version **
 **---------------------------------------**/
void PrintConfig0012A(void)
{
   Value = 0;
   ValueFlag = FALSE;
   strcpy(VGABuffer, SBCVersionLabel);
   Val_ID = SBC_VER_PRNT;
   VGAPrintParam = PSWVERSION;
}
void PrintCalibrationDate(void)
{
   RTCTime RTCPrinter;

   if (NVR.CalibPass == CALIBPASSED || NVR.CalibPass == CALIBFAILED)
   {
      RTCPrinter.Day = NVR.CalDate[1];
      RTCPrinter.Century_Month = NVR.CalDate[0];
      RTCPrinter.Years = NVR.CalDate[2];
   } else
   {
      RTCPrinter.Day = NVR.DefCalDate[1];
      RTCPrinter.Century_Month = NVR.DefCalDate[0];
      RTCPrinter.Years = NVR.DefCalDate[2];
   }

   if (SummaryInfo.b_unit)
      sprintf((SINT8 *) datestr, "%02u/%02u/%02u", RTCPrinter.Day,
            RTCPrinter.Century_Month, RTCPrinter.Years);
   else
      sprintf((SINT8 *) datestr, "%02u/%02u/%02u", RTCPrinter.Century_Month,
            RTCPrinter.Day, RTCPrinter.Years);

   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = CALIB_DATE_PRNT;
   VGAPrintParam = PCALDATE; /* Print in right half-page */
}
/**---------------------------------**
 ** This function displays Actuator **
 **---------------------------------**/
void PrintConfig0010(void)
{

   switch (CurrentSetup.Actuator)
   {
   case AE:
      Value = 0;
      break;

   case AO:
      Value = 1;
      break;

   case AED:
      Value = 2;
      break;

   case AOD:
      Value = 3;
      break;

   case AEF:
      Value = 4;
      break;

   case AOF:
      Value = 5;
      break;

   case MICRO:
      Value = 7; /* MICRO_11.10A */
      break;

   case AES:
      Value = 8;
      break;

   case MICROC:
      Value = 9;
      break;

   default:
      Value = 0;
      break;
   }
   if (CurrentSetup.CustomAct)
      Value = 6;
   ValueFlag = TRUE;
   Val_ID = ACT_PRNT;
   VGAPrintParam = PACTUATOR;
}
/**-------------------------------------------**
 ** This function displays  Cylinder Diameter **
 **-------------------------------------------**/
void PrintConfig0016(void)
{
   GetCylinderStr();
   ValueFlag = TRUE;
   Val_ID = CYCLINDER_DIA_PRNT;
   VGAPrintParam = PCYLDIAMETER;
}
/**----------------------------------------**
 ** This function displays Cylinder Stroke **
 **----------------------------------------**/
void PrintConfig0017(void)
{
   GetStrokeLenStr();
   ValueFlag = TRUE;
   Val_ID = CYCLINDER_STROKE_PRNT;
   VGAPrintParam = PCYLSTROKE;
}

/********************************** end of SystemPresetReport3 *********************************/

/********************************** SystemPresetReport4 *********************************/

/**--------------------------------------------**
 ** This function displays PS Lifetime Counter **
 **--------------------------------------------**/
void PrintConfig0004(void)
{
   ConvertNumberToString(CurrentSetup.PSLifetime);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PSLIFE_PRNT;
   VGAPrintParam = PPSLIFETIME;
}
/**---------------------------------------**
 ** This function displays Preset Counter **
 **---------------------------------------**/
void PrintConfig0022(void)
{
   ConvertNumberToString(CurrentPreset.WeldCount);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WELD_COUNT_PRNT;
   VGAPrintParam = PPRESETCOUNTER;
}
/**-----------------------------------------**
 ** This function displays Actuator Counter **
 **-----------------------------------------**/
void PrintConfig0077(void)
{
   ConvertNumberToString(CurrentSetup.ActLifetime);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = ACTLIFE_PRNT;
   VGAPrintParam = PACTLIFETIME;
}

/**----------------------------------**
 ** This function displays Overloads **
 **----------------------------------**/
void PrintConfig0005(void)
{
   ConvertNumberToString(CurrentSetup.Overload);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = OVERLOAD_COUNT_PRNT;
   VGAPrintParam = POVERLCOUNTER;
}
/**--------------------------------------**
 ** This function displays General Alarm **
 **--------------------------------------**/
void PrintConfig0006(void)
{
   ConvertNumberToString(CurrentSetup.GenAlarmCount);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = GEN_ALARM_PRNT;
   VGAPrintParam = PGENALARMCNTR;
}
/**-----------------------------------------**
 ** This function displays PS Serial Number **
 **-----------------------------------------**/
void PrintConfig0014(void)
{
   strcpy(VGABuffer, CurrentSetup.PSSerialNumber);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = PSSERIAL_PRNT;
   VGAPrintParam = PPSSERNUM;
}

/**------------------------------------------**
 ** This function displays ACT Serial Number **
 **------------------------------------------**/
void PrintConfig0015(void)
{
   strcpy(VGABuffer, CurrentSetup.ActSerialNumber);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = ACTSERIAL_PRNT;
   VGAPrintParam = PACTSERNUM;
}

/**-----------------------------------------------**
 ** This function displays Weld Summary On Sample **
 **-----------------------------------------------**/
void PrintConfig0055(void)
{
    if((CurrentSetup.USBWDSampleFlag) == FALSE)
    {
    	ConvertNumberToString(CurrentSetup.USBWDSampleValue);
    	Value = 0;
    	ValueFlag = FALSE;
    	Val_ID = WELD_SAMP_PRNT;

    }
    else
    {
    	Value = 0;
        ValueFlag = TRUE;
    	Val_ID = WELD_SAMP_OFF_PRNT;
    }
    VGAPrintParam = PWELDDATA;

}
/**----------------------------------------------**
 ** This function displays Power Graph On Sample **
 **----------------------------------------------**/
void PrintConfig0057(void)
{
	if(CurrentSetup.USBPGSampleFlag == FALSE)
	{
		ConvertNumberToString(CurrentSetup.USBPGSampleValue);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = PWR_GRAPH_PRNT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = PWR_GRAPH_OFF_PRNT;
	}
   VGAPrintParam = PPOWERGRAPH;
}

/**-------------------------------------------------**
 ** This function displays Amplitude Graph On Sample**
 **-------------------------------------------------**/
void PrintConfig0059(void)
{
	if(CurrentSetup.USBAGSampleFlag == FALSE)
	{
		ConvertNumberToString(CurrentSetup.USBAGSampleValue);
		Value = 0;
	    ValueFlag = FALSE;
		Val_ID = AMP_GRAPH_PRNT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
		Val_ID = AMP_GRAPH_OFF_PRNT;
	}
	VGAPrintParam = PAMPLITUDEGRAPH;
}

/**-------------------------------------------------**
 ** This function displays Frequency Graph On Sample**
 **-------------------------------------------------**/
void PrintConfig0061(void)
{
	if((CurrentSetup.USBFreqGSampleFlag) == FALSE)
	{
		ConvertNumberToString(CurrentSetup.USBFreqGSampleValue);
		Value = 0;
	    ValueFlag = FALSE;
		Val_ID = FREQ_GRAPH_PRNT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
		Val_ID = FREQ_GRAPH_OFF_PRNT;
	}
	VGAPrintParam = PFREQUENCYGRAPH;
}

/**-----------------------------------------------------**
 ** This function displays Col Distance Graph On Sample **
 **-----------------------------------------------------**/
void PrintConfig0062B(void)
{
	if((CurrentSetup.USBCDGSampleFlag) == FALSE)
	{
		ConvertNumberToString(CurrentSetup.USBCDGSampleValue);
		Value = 0;
		ValueFlag = FALSE;
		Val_ID = DIST_GRAPH_PRNT;
	}
	else
	{
		Value = 0;
		ValueFlag = TRUE;
		Val_ID = DIST_GRAPH_OFF_PRNT;
	}
   VGAPrintParam = PDISTANCEGRAPH;
}

/**------------------------------------------------**
 ** This function displays Velocity Graph On Sample**
 **------------------------------------------------**/
void PrintConfig0065(void)
{
	if((CurrentSetup.USBVGSampleFlag) == FALSE)
	{
		ConvertNumberToString(CurrentSetup.USBVGSampleValue);
		Value = 0;
		ValueFlag = FALSE;
		Val_ID = VEL_GRAPH_PRNT;
	}
	else
	{
		Value = 0;
		ValueFlag = TRUE;
		Val_ID = VEL_GRAPH_OFF_PRNT;
	}
   VGAPrintParam = PVELOCITYGRAPH;
}
/**----------------------------------------------**
 ** This function displays Force Graph On Sample **
 **----------------------------------------------**/
void PrintConfig0067(void)
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator==MICRO) || (CurrentSetup.Actuator==MICROC))
   {
	   if((CurrentSetup.USBFGSampleFlag) == FALSE)
	   {
		   ConvertNumberToString(CurrentSetup.USBFGSampleValue);
		   Value = 0;
		   ValueFlag = FALSE;
		   Val_ID = FORCE_GRAPH_PRNT;
	   }
	   else
	   {
		   Value = 0;
		   ValueFlag = TRUE;
		   Val_ID = FORCE_GRAPH_OFF_PRNT;
	   }
      VGAPrintParam = PFORCEGRAPH;
   }
}
/**----------------------------------------------**
 ** This function displays Weld History On Sample**
 **----------------------------------------------**/
void PrintConfig0053(void)
{
   /* Print the Global Sample Value if external preset is enabled. */
   Val_ID = WELD_HIST_SAMP_PRNT;
   VGAPrintParam = PWELDHISTORY;
}
/**----------------------------------------**
 ** This function displays Setup On Sample **
 **----------------------------------------**/
void PrintConfig0051(void)
{
   Val_ID = WELD_HIST_SAMP_PRNT;
   VGAPrintParam = PSETUP;
}
/**-----------------------------------------------**
 ** This function displays status of global USB Flag  **
 **-----------------------------------------------**/
void PrintConfig0078(void)
{
	Value = (UINT8) (CurrentSetup.USBGlobalFlag);
	ValueFlag = TRUE;
	Val_ID = USB_OFF_PRNT;
	VGAPrintParam = PUSBFLAG;
}

/**-----------------------------------------------**
 ** This function displays Weld Summary On Alarm  **
 **-----------------------------------------------**/
void PrintConfig0054(void)
{
	Value = (UINT8) (CurrentSetup.USBWDAlarmFlag);
	ValueFlag = TRUE;
	Val_ID = WELD_DATA_ALARM_PRNT;
	VGAPrintParam = PWELDDATA;
}

/**----------------------------------------------**
 ** This function displays Power Graph On Alarm  **
 **----------------------------------------------**/
void PrintConfig0056(void)
{
   Value = (UINT8) (CurrentSetup.USBPGAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = PWR_GRAPH_ALARM_PRNT;
   VGAPrintParam = PPOWERGRAPH;
}
/**-------------------------------------------------**
 ** This function displays Amplitude Graph On Alarm **
 **-------------------------------------------------**/
void PrintConfig0058(void)
{
   Value = (UINT8) (CurrentSetup.USBAGAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = AMP_GRAPH_ALARM_PRNT;
   VGAPrintParam = PAMPLITUDEGRAPH;
}
/**-------------------------------------------------**
 ** This function displays Frequency Graph On Alarm **
 **-------------------------------------------------**/
void PrintConfig0060(void)
{
   Value = (UINT8) (CurrentSetup.USBFreqGAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = FREQ_GRAPH_ALARM_PRNT;
   VGAPrintParam = PFREQUENCYGRAPH;
}
/**----------------------------------------------------**
 ** This function displays Col Distance Graph On Alarm **
 **----------------------------------------------------**/
void PrintConfig0062A(void)
{
   Value = (UINT8) (CurrentSetup.USBCDGAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = DIST_GRAPH_ALARM_PRNT;
   VGAPrintParam = PDISTANCEGRAPH;
}
/**------------------------------------------------**
 ** This function displays Velocity Graph On Alarm **
 **------------------------------------------------**/
void PrintConfig0064(void)
{
   Value = (UINT8) (CurrentSetup.USBVGAlarmFlag);
   ValueFlag = TRUE;
   Val_ID = VEL_GRAPH_ALARM_PRNT;
   VGAPrintParam = PVELOCITYGRAPH;
}
/**---------------------------------------------**
 ** This function displays Force Graph On Alarm **
 **---------------------------------------------**/
void PrintConfig0066(void)
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
	  Value = (UINT8) (CurrentSetup.USBFGAlarmFlag);
      ValueFlag = TRUE;
      Val_ID = FORCE_GRAPH_ALARM_PRNT;
      VGAPrintParam = PFORCEGRAPH;
   }
}

/**----------------------------------------------**
 ** This function displays Weld History On Alarm **
 **----------------------------------------------**/
void PrintConfig0052(void)
{
   ValueFlag = TRUE;
   Val_ID = WELD_HIST_ALARM_PRNT;
   VGAPrintParam = PWELDHISTORY;
}

/**------------------------------------------**
 ** This function displays X Axis Auto Scale **
 **------------------------------------------**/
void PrintSetup0079(void)
{
   Value = (UINT8) (CurrentPreset.AutoScaleFlag);
   ValueFlag = TRUE;
   Val_ID = XAXIS_AUTOSCALE_PRNT;
   VGAPrintParam = PAUTOXSCALE;
}
/**-------------------------------------**
 ** This function displays X Axis Scale **
 **-------------------------------------**/
void PrintSetup0080(void)
{

   /*-- TIMEMODE and Auto scale inactive--*/
   if ((CurrentPreset.WeldMode == TIMEMODE) && CurrentPreset.AutoScaleFlag)
   /* Auto scale on */
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = XAXIS_SCALE_PRNT;
   } else
   { /* Auto scale off */
      FormatVariables(CurrentPreset.XScaleTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = XAXIS_SCALE_OFF_PRNT;
   }

   VGAPrintParam = PXSCALE;
}


//flow control
void ViewPresetSetup0312(void)
{
	FormatVariables(CurrentViewPreset.Downspeed, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = FLOW_CONTROL_TXT;
	VGAPrintParam = PDOWNSPEED;
}
/**-----------------------------------------------------**
 ** This function displays the Hold pressure default/on.**
 **-----------------------------------------------------**/
void ViewPresetSetup0329(void)
{
   Value = CurrentViewPreset.HoldPressureFlag;
   ValueFlag = TRUE;
   Val_ID = HOLD_PRESSURE_FLAG_PRINT;
   VGAPrintParam = PHOLDPRESSURE;
}


//hold pressure
void ViewPresetSetup0315(void)
{
	FormatVariables(CurrentViewPreset.HoldPressure, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = HOLD_PRESSURE;
	VGAPrintParam = PHOLDPRESSURE;
}


//weld pressure
void ViewPresetSetup0316(void)
{
	FormatVariables(CurrentViewPreset.WeldPressure, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = WELD_PRESSURE;
	VGAPrintParam = PWELDPRESSURE;
}


//trigger distance
void ViewPresetSetup0318(void)
{
	FormatVariables(CurrentViewPreset.TriggerDistance, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = TRIGGER_DIST;
	VGAPrintParam = PTRIGGERDIST;
}
//Batch count
void ViewPresetSetup0300(void)
{
	Value = (UINT8)(0);
	ValueFlag = TRUE;
	Val_ID = BATCH_COUNT_TXT;
	VGAPrintParam = PBATCHCOUNTENABLED;
}

//Batch count enabled
void ViewPresetSetup0301(void)
{
	Value = (UINT8)(CurrentViewPreset.BatchFunction);
	ValueFlag = TRUE;
	Val_ID = BATCH_COUNT_ENABLED;
	VGAPrintParam = PBATCHCOUNTENABLED;
}

//Count with alarm
void ViewPresetSetup0302(void)
{
	Value = (UINT8)(CurrentViewPreset.BatchCountWithAlarm);
	ValueFlag = TRUE;
	Val_ID = B_COUNT_WITH_ALARM;
	VGAPrintParam = PBCOUNTWITHALARM;
}

//Reset to Zero
void ViewPresetSetup0303(void)
{
	Value = (UINT8)(CurrentViewPreset.BatchCountReset);
	ValueFlag = TRUE;
	Val_ID = B_RESET_TO_ZERO;
	VGAPrintParam = PBCOUNTRESETTOZERO;
}

//Batch count value
void ViewPresetSetup0304(void)
{
	FormatVariables(CurrentViewPreset.BatchCount, INTEGER, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = BATCH_COUNT_VALUE;
	VGAPrintParam = PBATCHCOUNT;
}

//Pressure Limits
void ViewPresetSetup0305(void)
{
	Value = (UINT8)(0);
	ValueFlag = TRUE;
	Val_ID = PRESSURE_LIMITS_TXT;
	VGAPrintParam = PPRESSURELIMIT;
}
//Pressure limits on off
void ViewPresetSetup0306(void)
{
	Value = (UINT8)(CurrentViewPreset.PressureLimitFlag);
	ValueFlag = TRUE;
	Val_ID = PRESSURE_LIMIT_FLAG;
	VGAPrintParam = PPRESSURELIMIT;
}

//Pressure limit plus
void ViewPresetSetup0307(void)
{
	FormatVariables(CurrentViewPreset.PPressureLimit, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = PRESSURE_LIMIT_PLUS;
	VGAPrintParam = PPRESSURELIMITPLUS;
}

void PrintSetup0330(void)
{
   if ((CurrentPreset.PressureLimits & PPRESSURELIMITBIT) != PPRESSURELIMITBIT)
   {
	  FormatVariables(CurrentViewPreset.PPressureLimit, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_LIMIT_PLUS;

   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPRESSURE_LIM_OFF_TXT;
   }
   VGAPrintParam = PPRESSURELIMITPLUS;
}

//pressure limit minus
void ViewPresetSetup0308(void)
{
	FormatVariables(CurrentViewPreset.MPressureLimit, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	strcpy(VGABuffer, VGAMisc);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = PRESSURE_LIMIT_MINUS;
	VGAPrintParam = PPRESSURELIMITMINUS;
}

void PrintSetup0331(void)
{
   if ((CurrentPreset.PressureLimits & MPRESSURELIMITBIT) != MPRESSURELIMITBIT)
   {
	  FormatVariables(CurrentViewPreset.MPressureLimit, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_LIMIT_MINUS;

   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPRESSURE_LIM_OFF_TXT;
   }
   VGAPrintParam = PPRESSURELIMITMINUS;
}

// Actuator assembly number
void ViewPresetSetup0309(void)
{
	strcpy(VGABuffer, CurrentViewPreset.ActAssemblyNum);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = ACT_ASSEMBLY_TXT;
	VGAPrintParam = PACTASSEMBLTNUM;
}

// P/S assembly number
void ViewPresetSetup0310(void)
{
	strcpy(VGABuffer, CurrentViewPreset.PSAssemblyNum);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = PS_ASSEMBLY_TXT;
	VGAPrintParam = PPSASSEMBLYNUM;
}

//Stack assembly number
void ViewPresetSetup0311(void)
{
	strcpy(VGABuffer, CurrentViewPreset.StackAssemblyNum);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = STACK_ASSEMBLY_TXT;
	VGAPrintParam = PPSTACKASSEMBLYNUM;
}
//validated/locked
UINT16 ViewPresetSetup0313(void)
{
	UINT16 Param = PUNVALIDUNCLOKED;
	if(CurrentViewPreset.Locked && CurrentViewPreset.Validated)
	{

		Param = PVALIDLOCK;
		Val_ID = VALIDATED_LOCKED_TXT;
	}
	else if(CurrentViewPreset.Validated && CurrentViewPreset.Locked == FALSE)
	{
		Param = PVALIDUNLOCKED;
		Val_ID = VALIDATED_UNLOCKED_TXT;
	}
	else if(CurrentViewPreset.Locked == FALSE && CurrentViewPreset.Validated == FALSE)
	{
		Param = PUNVALIDUNCLOKED;
		Val_ID = UNVALIDATED_UNLOCKED_TXT;
	}
	Value = 0;
	VGAPrintParam = Param;
	return (Param);
}


void ViewPresetSetup0319()
{
	sprintf(VGABuffer,"%d",CurrentViewPreset.Rev);
	Value = 0;
	ValueFlag = FALSE;
	Val_ID = PRESETREV_TXT;
	VGAPrintParam = PPRESETREV;
}
//SetupLimit +weld pressure
void ViewPresetSetup0320(void)
{
	if (!(CurrentViewPreset.SetupLimits & WELDPRESSURE_PBIT))
	{
		FormatVariables(CurrentViewPreset.WeldPressurePLT, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDPRESSURE_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDPRESSURE_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -weld pressure
void ViewPresetSetup0335(void)
{
	if (!(CurrentViewPreset.SetupLimits & WELDPRESSURE_MBIT))
	{
		FormatVariables(CurrentViewPreset.WeldPressureMLT, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDPRESSURE_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDPRESSURE_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Down Speed
void ViewPresetSetup0321(void)
{
	if (!(CurrentViewPreset.SetupLimits & DOWNSPEED_PBIT))
	{
		FormatVariables(CurrentViewPreset.DownspeedPLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = DOWNSPEED_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = DOWNSPEED_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Down Speed
void ViewPresetSetup0336(void)
{
	if (!(CurrentViewPreset.SetupLimits & DOWNSPEED_MBIT))
	{
		FormatVariables(CurrentViewPreset.DownspeedMLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = DOWNSPEED_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = DOWNSPEED_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Hold Pressure
void ViewPresetSetup0322(void)
{
	if (!(CurrentViewPreset.SetupLimits & HOLDPRESSURE_PBIT))
	{
		FormatVariables(CurrentViewPreset.HoldPressurePLT, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = HOLDPRESSURE_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = HOLDPRESSURE_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Hold Pressure
void ViewPresetSetup0337(void)
{
	if (!(CurrentViewPreset.SetupLimits & HOLDPRESSURE_MBIT))
	{
		FormatVariables(CurrentViewPreset.HoldPressureMLT, PRESSURE2, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = HOLDPRESSURE_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = HOLDPRESSURE_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Hold Time
void ViewPresetSetup0323(void)
{
	if (!(CurrentViewPreset.SetupLimits & HOLDTIME_PBIT))
	{
		FormatVariables(CurrentViewPreset.HoldTimePLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = HOLDTIME_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = HOLDTIME_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Hold Time
void ViewPresetSetup0338(void)
{
	if (!(CurrentViewPreset.SetupLimits & HOLDTIME_MBIT))
	{
		FormatVariables(CurrentViewPreset.HoldTimeMLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = HOLDTIME_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = HOLDTIME_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Amp A
void ViewPresetSetup0324(void)
{
	if (!(CurrentViewPreset.SetupLimits & AMPA_PBIT))
	{
		FormatVariables(CurrentViewPreset.AmpAPLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = AMPA_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = AMPA_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Amp A
void ViewPresetSetup0339(void)
{
	if (!(CurrentViewPreset.SetupLimits & AMPA_MBIT))
	{
		FormatVariables(CurrentViewPreset.AmpAMLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = AMPA_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = AMPA_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Trig Force
void ViewPresetSetup0325(void)
{
	if (!(CurrentViewPreset.SetupLimits & TRIGFORCE_PBIT))
	{
		FormatVariables(CurrentViewPreset.TrigForcePLT, FORCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = TRIGFORCE_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = TRIGFORCE_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Trig Force
void ViewPresetSetup0340(void)
{
	if (!(CurrentViewPreset.SetupLimits & TRIGFORCE_MBIT))
	{
		FormatVariables(CurrentViewPreset.TrigForceMLT, FORCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = TRIGFORCE_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = TRIGFORCE_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Weld Time
void ViewPresetSetup0326(void)
{
	if (!(CurrentViewPreset.SetupLimits & WELDTIME_PBIT))
	{
		FormatVariables(CurrentViewPreset.WeldTimePLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDTIME_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDTIME_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Weld Time
void ViewPresetSetup0341(void)
{
	if (!(CurrentViewPreset.SetupLimits & WELDTIME_MBIT))
	{
		FormatVariables(CurrentViewPreset.WeldTimeMLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDTIME_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDTIME_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Trigger Distance
void ViewPresetSetup0327(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & TRIGDIST_PBIT))
	{
		FormatVariables(CurrentViewPreset.TrigDistancePLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = TRIGDIST_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = TRIGDIST_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Trigger Distance
void ViewPresetSetup0342(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & TRIGDIST_MBIT))
	{
		FormatVariables(CurrentViewPreset.TrigDistanceMLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = TRIGDIST_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = TRIGDIST_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Weld Energy
void ViewPresetSetup0328(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & WELDENERGY_PBIT))
	{
		FormatVariables(CurrentViewPreset.WeldEnergyPLT,
				      /* cont'd */CurrentViewPreset.WeldEnergyPLT > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
				      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDENERGY_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDENERGY_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Weld Energy
void ViewPresetSetup0343(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & WELDENERGY_MBIT))
	{
		FormatVariables(CurrentViewPreset.WeldEnergyMLT,
		      /* cont'd */CurrentViewPreset.WeldEnergyMLT > ENERGYPOINT ? ENERGYDIV10 : ENERGY,
		      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = WELDENERGY_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = WELDENERGY_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Peak Power
void ViewPresetSetup0330(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & PEAKPWR_PBIT))
	{
		FormatVariables(CurrentViewPreset.PeakPowerPLT, PERCENTX10, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = PEAKPOWER_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = PEAKPOWER_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Peak Power
void ViewPresetSetup0344(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & PEAKPWR_MBIT))
	{
		FormatVariables(CurrentViewPreset.PeakPowerMLT, PERCENTX10, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = PEAKPOWER_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = PEAKPOWER_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Collapse Disatance
void ViewPresetSetup0331(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & COLDIST_PBIT))
	{
		FormatVariables(CurrentViewPreset.CollapseDistPLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = COLLAPSEDIST_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = COLLAPSEDIST_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Collapse Disatance
void ViewPresetSetup0345(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & COLDIST_MBIT))
	{
		FormatVariables(CurrentViewPreset.CollapseDistMLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = COLLAPSEDIST_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = COLLAPSEDIST_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Absolute Disatance
void ViewPresetSetup0332(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & ABSDIST_PBIT))
	{
		FormatVariables(CurrentViewPreset.AbsDistPLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = ABSDIST_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = ABSDIST_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Absolute Disatance
void ViewPresetSetup0346(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & ABSDIST_MBIT))
	{
		FormatVariables(CurrentViewPreset.AbsDistMLT, DISTANCE, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = ABSDIST_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = ABSDIST_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Scrub Time
void ViewPresetSetup0333(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & SCRUBTIME_PBIT))
	{
		FormatVariables(CurrentViewPreset.ScrubTimePLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = SCRUBTIME_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = SCRUBTIME_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Scrub Time
void ViewPresetSetup0347(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & SCRUBTIME_MBIT))
	{
		FormatVariables(CurrentViewPreset.ScrubTimeMLT, TIME, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = SCRUBTIME_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = SCRUBTIME_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit +Scrub Amplitude
void ViewPresetSetup0334(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & AMPSCRUBTIME_PBIT))
	{
		FormatVariables(CurrentViewPreset.ScrubAmpPLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = SCRUBAMP_PLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = SCRUBAMP_PLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}
//SetupLimit -Scrub Amplitude
void ViewPresetSetup0348(void)
{
	if (!(CurrentViewPreset.SetupLimits2 & AMPSCRUBTIME_MBIT))
	{
		FormatVariables(CurrentViewPreset.ScrubAmpMLT, PERCENT, VGAMisc, 6,CurrentSetup.Units);
	    strcpy(VGABuffer, VGAMisc);
	    Value = 0;
	    ValueFlag = FALSE;
	    Val_ID = SCRUBAMP_MLT_TXT;
	}
	else
	{
		Value = 0;
	    ValueFlag = TRUE;
	    Val_ID = SCRUBAMP_MLT_OFF_TXT;
	}
	VGAPrintParam = PSETUPLIMIT;
}


/********************************** end of SystemPresetReport4 *********************************/

UINT16 SystemPresetReport1(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 1st preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 1;
   UINT16 param;
   memcpy(&CurrentViewPreset,&CurrentPreset,sizeof(SETUPS_Ver1200));
   VGAPrintLength = 0;
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   PrintHeader1(VGAPageNumber);
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintHeader2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintHeader3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate = RightPrintYCoordinate + 1;
   RightPrintXCoordinate = MID_XCOORDINATE - 40;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = WELD_COND_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE + 20;
   PrintSubHeader2();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE;
   PrintSubHeader3();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   /* Left half-page */
   LeftPrintYCoordinate += (PrintLineHeight);
   RightPrintYCoordinate += (PrintLineHeight);
   Font_Print = FONT_PRINT;

   param = PrintSetup0002(); /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   param = PrintSetup0003(); /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   if (CurrentPreset.WeldMode == GRDDETECTMODE)
   {
      PrintSetup0003A();
      VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBAMPLITUDE, Value, Val_ID);
   }
   Value = (UINT8)CurrentPreset.WeldTrigger;
   ValueFlag = TRUE;
   Val_ID = WELD_TRIG_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   if(CurrentPreset.WeldTrigger)
   {
	   ViewPresetSetup0318(); /*Trigger distance*/
   	   VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERDIST, Value, Val_ID);
   }
   else
   {
	   PrintAEDTrigForce(); /* Trigger Force */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERFORCE, Value, Val_ID);
   }
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /*Amplitude stepping on PDF*/

   PrintSetup0015(); /* Amplitude */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA, Value, Val_ID);
   VGAPrintParam = ALWAYS;
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0016(); /* Amplitude(A) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA1, Value, Val_ID);
   PrintSetup0017(); /* Amplitude(B) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEB, Value, Val_ID);
   param = PrintSetup0018A(); /* Amplitude Step at Time, Step at Energy, ... */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);

   /*Pressure stepping on PDF*/
   if (CurrentSetup.ControlLevel >= LEVEL_c) {
      LeftPrintXCoordinate = LEFT_XCOORDINATE;
      PrintSetup0007(); /* Pressure */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREA, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      PrintSetup0008(); /* Pressure(A) if Pressure step is on */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREA1, Value, Val_ID);
      PrintSetup0009();  /* Pressure(B) if Pressure step is on */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREB, Value, Val_ID);
      param = PrintSetup0018B(); /* Pressure Step at Time, Step at Energy, ... */
      VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   }

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   PrintSetup0019(); /* Pretrigger Flag - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGER, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   if(CurrentPreset.PreTrigFlag)
   {
	   PrintSetup0019B(); /* Auto Pretrigger Flag - On or Off, indented */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOPRETRIGGER, Value, Val_ID);
	   PrintSetup0019A(); /* Pretrigger Distance, indented */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERDISTANCE, Value, Val_ID);
   }
   PrintSetup0021(); /* Pretrigger Amplitude, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERAMP, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   PrintSetup0070(); /* Max Timeout */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PMAXTIMEOUT, Value, Val_ID);
   PrintSetup0070A(); /* External Trigger Delay */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTTRIGDLY, Value, Val_ID);

   /* Right half-page */
   PrintSetup0004(); /* Hold Time */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDTIME, Value, Val_ID);
   PrintSetup0022(); /* Afterburst - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURST, Value, Val_ID);

   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintSetup0023(); /* Afterburst Delay, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTDELAY, Value, Val_ID);
   PrintSetup0024(); /* Afterburst Time, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTTIME, Value, Val_ID);
   PrintSetup0025(); /* Afterburst Amplitude, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTAMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   PrintSetup0025A(); /* Energy Braking - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYBRAKING, Value, Val_ID);
   PrintSetup0026(); /* Post Weld Seek - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPOSTWELDSEEK, Value, Val_ID);
   PrintSetup0027(); /* Frequency Offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL, Value, Val_ID);
   PrintConfig0081(); /* Digital Tune */
   VGA_PresetSetup2(&AckBuf, VGABuffer, DIGITALTUNE, Value, Val_ID);
   PrintSetup0067(); /* Test Amplitude */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTESTAMPLITUDE, Value, Val_ID);
   PrintConfig0033(); /* Actuator Clear Output - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEAROUTPUT, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0033A(); /* Actuator Clear Distance, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEARDISTANCE, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /* Left half-page */
   PrintSetup0071(); /* Cycle Abort - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCYCLEABORTS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0033(); /* Ground Detect Abort - On or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBTIME, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   PrintConfig0071(); /* Missing Part - On or Off or N/A */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTFLAG, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0072(); /* Missing Part Abort Min - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMIN, Value, Val_ID);
   PrintConfig0073(); /* Missing Part Abort Max - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMAX, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /* Left half-page */
   PrintSetup0028(); /* Control Limits - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLIMITS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   PrintSetup0034B(); /* Collapse Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCOLLAPSECUTOFF, Value, Val_ID);
   PrintSetup0034A(); /* Absolute Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PABSOLUTECUTOFF, Value, Val_ID);
   PrintSetup0032(); /* Peak Power Cutoff - Percent or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPKPOWERCUTOFF, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   PrintSetup0029(); /* Energy Compensation - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYCOMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintSetup0031(); /* Max. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAX, Value, Val_ID);
   PrintSetup0030(); /* Min. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENGERGYMIN, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
	   /* Left half-page */
	         /* AES message (forces blank line in right half-page) */

	   	 Value = 0;
	   	 ValueFlag = TRUE;
	   	 Val_ID = AEC_SETTING_PRNT;               //AES setting
	   	 VGAPrintParam = ALWAYS;
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

	   	 ViewPresetSetup0012();//Rapid Traverse On/Off
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);

	   	 ViewPresetSetup0013();//Rapid Traverse Distance
	     VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);


	   	 ViewPresetSetup0312(); /*Flow control*/
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, PDOWNSPEED, Value, Val_ID);

	   	 ViewPresetSetup0329(); /*Hold Pressure flag*/
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, PHOLDPRESSURE, Value, Val_ID);

	   	 ViewPresetSetup0315(); /*Hold Pressure*/
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, PHOLDPRESSURE, Value, Val_ID);

	   	 ViewPresetSetup0316(); /*Weld Pressure*/
	   	 VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDPRESSURE, Value, Val_ID);
   }
   else if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO))
   {
	   Value = 0;
	   ValueFlag = TRUE;
	   if(CurrentSetup.Actuator == MICRO)
	   		Val_ID = MICRO_SET_PRNT;
	   else
		   Val_ID = AED_AOD_SET_PRNT;
	   VGAPrintParam = ALWAYS;  //AED Setting
	   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

	   /* Velocity ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = VEL_PRNT;
      VGAPrintParam = DRAWLINEFIELD;
      strcpy(VGABuffer, DRAWLINE);
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Column Position __________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = COL_POS_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Horn _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = HORN_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Booster _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = BOOSTER_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);

      RightPrintYCoordinate += PrintLineHeight;
      /* Right half-page */
      /* Downspeed Setting ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = DOWNSPEED_SETTING_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Set Gauge Pressure ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = SET_GAUGE_PESS_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Act. Gauge Pressure */
      PrintSystemGaugePressure();
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Fixture _____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = FIXTURE_PRNT;
      VGAPrintParam = DRAWLINEFIELD;
      strcpy(VGABuffer, DRAWLINE);
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
   }
   else
   {

      /* Left half-page */
      /* ae/ao message (forces blank line in right half-page) */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = AED_SETTINGS_TXT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Trigger Setting ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = TRIG_SETTING_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Velocity _______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = VEL_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Column Position ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = COL_POS_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Horn ________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = HORN_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Booster _________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = BOOSTER_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup1(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);

      /* Right half-page */
      /* Downspeed Setting ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = DOWNSPEED_SETTING_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* Gauge Pressure ____________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = GAUAGE_PRESSURE_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
      /* MPS Switch Flag1 ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPS_SWITCH_FLAG1_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = PMPSLOGIC;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PMPSLOGIC, Value, Val_ID);
      /* MPS Switch Flag2 ______________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPS_SWITCH_FLAG2_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = PMPSLOGIC;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PMPSLOGIC, Value, Val_ID);
      /* Fixture _________________ */
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = FIXTURE_PRNT;
      strcpy(VGABuffer, DRAWLINE);
      VGAPrintParam = DRAWLINEFIELD;
      VGA_PresetSetup2(&AckBuf, VGABuffer, DRAWLINEFIELD, Value, Val_ID);
   }

   return (VGAPrintLength);

}
UINT16 SystemPresetReport2(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of 1st preset page report       **
 **------------------------------------------------------------------**/
{
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if (DUPS_Info.DUPSFlag)
   {
      /* Print Digital UPS subheading */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = DUPS_PRNT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Put blank line in right half-page */
      RightPrintYCoordinate += PrintLineHeight;

      /*--           *left half-page*           --*/
      /* Ramp Time */
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      FormatVariables(CurrentPreset.DUPS_HostParamSet.WeldRampTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = DUPS_RAMPTIME_PRNT;
      VGAPrintParam = PDUPSRAMPTIME;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDUPSRAMPTIME, Value, Val_ID);

      /* Memory - On or Off */
      Value = (UINT8) DUPS_Info.DUPSMemFlag;
      ValueFlag = TRUE;
      Val_ID = DUPS_MEMRY_PRNT;
      VGAPrintParam = PMEMORY;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PMEMORY, Value, Val_ID);

      /* Weld Status - On or Off */
      Value = (UINT8) CurrentPreset.WeldStatusFlag;
      ValueFlag = TRUE;
      Val_ID = WELDSTATUS_PRNT;
      VGAPrintParam = PWELDSTATUS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSTATUS, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_XCOORDINATE;

      /* Seek Time */
      FormatVariables(CurrentPreset.DUPS_HostParamSet.SeekTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = SEEKTIME_PRNT;
      VGAPrintParam = PSEEKTIME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSEEKTIME, Value, Val_ID);

      /* Timed Seek - On or Off */
      Value = DUPS_Info.DUPSSeekFlag;
      ValueFlag = TRUE;
      Val_ID = TIMEDSEEK_PRNT;
      VGAPrintParam = PTIMEDSEEK;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PTIMEDSEEK, Value, Val_ID);

   }

   /* Print Write In Fields for both Analog/Digital PS */
   /* WriteIn Field1 */
   strcpy(VGABuffer, CurrentPreset.WriteIn1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD1_PRNT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);

   /* WriteIn Field2 */
   strcpy(VGABuffer, CurrentPreset.WriteIn2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD2_PRNT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if (CurrentSetup.ControlLevel > LEVEL_t)
   {
      Font_Print = FONT_PRINTBOLD;
      RightPrintXCoordinate = MID_XCOORDINATE;
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = LIMITS_PRNT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      RightPrintXCoordinate = RIGHT_XCOORDINATE;
      AssignYCoordinate();
   }

   /* Left half-page */
   Font_Print = FONT_PRINT;
   PrintSetup0051(); /* Reject Limits - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJECTLIMITS, Value, Val_ID);
   PrintSetup0052(); /* Reject Reset Required - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJRESETREQ, Value, Val_ID);

   /* Right half-page */
   PrintSetup0035(); /* Suspect Limits - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPECTLIMITS, Value, Val_ID);
   PrintSetup0036(); /* Suspect Reset Required - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPRESETREQ, Value, Val_ID);

   /* left half-page */
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE - 25;
   PrintSetup0059(); /* display the + Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   PrintSetup0060(); /* display the - Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   PrintSetup0055(); /* display the + Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   PrintSetup0056(); /* display the - Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   PrintSetup0061(); /* display the + Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   PrintSetup0062(); /* display the - Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   PrintSetup0057(); /* display the + Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   PrintSetup0058(); /* display the - Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   PrintSetup0053(); /* display the + Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   PrintSetup0054(); /* display the - Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   PrintSetup0065(); /* display the + Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   PrintSetup0066(); /* display the - Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   PrintSetup0063(); /* display the + Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   PrintSetup0064(); /* display the - Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);

   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* right half-page */
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE - 25;
   PrintSetup0043(); /* display the + Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   PrintSetup0044(); /* display the - Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   PrintSetup0039(); /* display the + Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   PrintSetup0040(); /* display the - Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   PrintSetup0045(); /* display the + Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   PrintSetup0046(); /* display the - Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   PrintSetup0041(); /* display the + Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   PrintSetup0042(); /* display the - Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   PrintSetup0037(); /* display the + Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   PrintSetup0038(); /* display the - Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   PrintSetup0049(); /* display the + Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEPLUS, Value, Val_ID);
   PrintSetup0050(); /* display the - Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEMINUS, Value, Val_ID);
   PrintSetup0047(); /* display the + Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   PrintSetup0048(); /* display the - Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   return (VGAPrintLength);
}

UINT16 SystemPresetReport3(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 2ndt preset page report          **
 **------------------------------------------------------------------**/
{
   UINT8 VGAPageNumber = 2;
   UINT16 param;

   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;

   PrintHeader1(VGAPageNumber);
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintHeader2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintHeader3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate = RightPrintYCoordinate + 1;
   RightPrintXCoordinate = MID_XCOORDINATE - 40;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = WELD_COND_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE + 20;
   PrintSubHeader2();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintXCoordinate = MID_XCOORDINATE;
   PrintSubHeader3();
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   PrintSetup0081(); /* display the +Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintSetup0082(); /* display the - Power band R Limit */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   if (DUPS_Info.DUPSFlag && CurrentSetup.SBLEnable)
   {
      PrintSetup0083(); /* display the +SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      PrintSetup0084(); /* display the -SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   PrintSetup0085(); /* display the +Downspeed R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LDOWNSPEEDPLUS, Value, Val_ID);
   //VGA_PresetSetup1(&AckBuf, VGABuffer, , Value, Val_ID);
   PrintSetup0086(); /* display the -Downspeed R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LDOWNSPEEDMINUS, Value, Val_ID);
   //VGA_PresetSetup1(&AckBuf, VGABuffer, , Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if (CurrentSetup.ControlLevel >= LEVEL_c)
   {
	   //only string is here.
	   Font_Print = FONT_PRINTBOLD;
	   RightPrintXCoordinate = MID_XCOORDINATE;
	   Value = 0;
	   ValueFlag = TRUE;
	   Val_ID = SETUPLIMIT_TXT;
	   VGAPrintParam = PSETUPLIMIT;
	   VGA_PresetSetup2(&AckBuf, 0, PSETUPLIMIT, Value, Val_ID);
	   RightPrintXCoordinate = RIGHT_XCOORDINATE;
	   AssignYCoordinate();

	   Font_Print = FONT_PRINT;
	   if(CurrentViewPreset.WeldMode == TIMEMODE)
	   {
		   ViewPresetSetup0326(); /* display the + WeldTime SetupLimitt */
	  	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	   ViewPresetSetup0341(); /* display the - WeldTime SetupLimitt */
	  	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	  if(CurrentViewPreset.WeldMode == ENERGYMODE)
	  {
		  ViewPresetSetup0328(); /* display the + Weld Energy SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0343(); /* display the - Weld Energy SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  if(CurrentViewPreset.WeldMode == PKPOWERMODE)
	  {
		  ViewPresetSetup0330(); /* display the + Peak Power SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0344(); /* display the - Peak Power SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  if(CurrentViewPreset.WeldMode == COLLAPSEMODE)
	  {
		  ViewPresetSetup0331(); /* display the + Collapse Distance SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0345(); /* display the - Collapse Distance SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  if(CurrentViewPreset.WeldMode == ABSOLUTEMODE)
	  {
		  ViewPresetSetup0332(); /* display the + Absolute Distance SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0346(); /* display the - Absolute Distance SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  if(CurrentViewPreset.WeldMode == GRDDETECTMODE)
	  {
		  ViewPresetSetup0333(); /* display the + Scrub Time SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0334(); /* display the + Scrub Amplitude SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0347(); /* display the - Scrub Time SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0348(); /* display the - Scrub Amplitude SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  ViewPresetSetup0321(); /* display the + DownSpeed SetupLimitt */
	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0336(); /* display the - DownSpeed SetupLimitt */
	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0320(); /* display the + Weldpressure SetupLimit */
	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0335(); /* display the - Weldpressure SetupLimit */
	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0324(); /* display the + Amp A SetupLimitt */
	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0339(); /* display the - Amp A SetupLimitt */
	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0323(); /* display the + HoldTime SetupLimitt */
	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0338(); /* display the - HoldTime SetupLimitt */
	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0322(); /* display the + HoldPressure SetupLimitt */
	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  ViewPresetSetup0337(); /* display the - HoldPressure SetupLimitt */
	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  if(CurrentViewPreset.WeldTrigger)
	  {
		  ViewPresetSetup0327(); /* display the + Trigger Distance SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0342(); /* display the - Trigger Distance SetupLimitt */
	  	  VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }
	  else
	  {
		  ViewPresetSetup0325(); /* display the + TrigForce SetupLimitt */
	  	  VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	  ViewPresetSetup0340(); /* display the - TrigForce SetupLimitt */
	      VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  }

	   LeftPrintYCoordinate += PrintLineHeight;
	   RightPrintYCoordinate += PrintLineHeight;
   }

   ViewPresetSetup0300(); /*Batch count*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNTENABLED, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0301(); /*Batch count enabled*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNTENABLED, Value, Val_ID);
   ViewPresetSetup0302(); /*Count with alarm */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBCOUNTWITHALARM, Value, Val_ID);
   ViewPresetSetup0303(); /*Reset to zero*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBCOUNTRESETTOZERO, Value, Val_ID);
   ViewPresetSetup0304(); /*Batch count value*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNT, Value, Val_ID);

   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0305(); /*Pressure limits*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMIT, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0306();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMIT, Value, Val_ID);
   PrintSetup0330();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMITPLUS, Value, Val_ID);
   PrintSetup0331();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMITMINUS, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   ViewPresetSetup0309(); /*Assembly number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PACTASSEMBLTNUM, Value, Val_ID);

   ViewPresetSetup0310(); /*P/S number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSASSEMBLYNUM, Value, Val_ID);

   ViewPresetSetup0311(); /*Stack number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSTACKASSEMBLYNUM, Value, Val_ID);

   LeftPrintYCoordinate += PrintLineHeight;
   param = ViewPresetSetup0313(); /*Validated/locked*/
   VGA_PresetSetup1(&AckBuf, 0, param, Value, Val_ID);

   if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
  	  ViewPresetSetup0319();
   	  VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESETREV, Value, Val_ID);
   }


   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = STSEM_CONF_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINT;

   /* left half-page */

   PrintConfig0019(); /* display the units - metric or english */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PUNITS, Value, Val_ID);
   PrintConfig0020(); /* display password - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPASSWORD, Value, Val_ID);
   PrintStartScreen(); /* display start screen - run or main */
   VGA_PresetSetup1(&AckBuf, VGABuffer, STRTSCREEN, Value, Val_ID);
     LeftPrintXCoordinate = LEFT_XCOORDINATE;

   PrintConfig0027(); /* display general alarm reset required - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PGENALARMRESET, Value, Val_ID);
   param = PrintConfig0028(); /* display trigger beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   PrintConfig0029(); /* display error beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PERRORBEEPER, Value, Val_ID);
   PrintConfig0030(); /* dispaly alarm beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PALARMBEEPER, Value, Val_ID);
   PrintConfig0178(); /* dispaly Estop beeper - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PESTOPBEEP, Value, Val_ID);
   PrintConfig0032(); /* display amplitude control */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPCONTROL, Value, Val_ID);
   PrintConfig0040(); /* display extra cooling */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTRACOOLING, Value, Val_ID);
   PrintConfig0041(); /* display weld scale */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSCALE, Value, Val_ID);
   PrintConfig0042(); /* display test scale */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PTESTSCALE, Value, Val_ID);
   PrintConfig0043(); /* display digital filter - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PDIGFILTER, Value, Val_ID);
   PrintConfig0045(); /* display Ext Presets - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTPRESETS, Value, Val_ID);
   PrintConfig0099(); /* Decimal place 2 or 3*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0098(); /* display Sequencing - on or off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* right half-page */

   PrintConfig0085(); /* display Input J3_32 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0086(); /* display Input J3_33 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0087(); /* display Input J3_19 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0088(); /* display Input J3_17 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0089(); /* display Input J3_31 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0090(); /* display Input J3_2 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0091(); /* display Output J3_36 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0092(); /* display Output J3_8 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0093(); /* display Output J3_22 */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0094(); /* display User Input Logic */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PUSERIO, Value, Val_ID);
   PrintConfig0094A(); /* display Ext.Start Delay */
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0034(); /* display Upper Limit Switch */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PULSLOGIC, Value, Val_ID);
   PrintConfig0095(); /* display Gnd Det Switch */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCUSTOMACT, Value, Val_ID);
   PrintConfig0096(); /* display Welder address */
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintConfig0044(); /* display frequency offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL, Value, Val_ID);
   if (CurrentSetup.Actuator == AE)// hand held will not come for AEC or AED
   {
	   PrintConfig0097(); /* display HandHeld - Off/On*/
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PHANDHELDSYSTEM, Value, Val_ID);
   }
   PrintConfig0100(); /* display Distance as ULS/ Start Sw*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINTBOLD;

   /*System Information Header*/
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = SYSTEM_INFO_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINT;

   /* left half-page */
   PrintCalibrationInfo(); /* display calibration status - pass/fail/factory */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCALINFO, Value, Val_ID);
   PrintConfig0009(); /* display power supply watts */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSSUPPLY, Value, Val_ID);
   PrintConfig0011(); /* display control level */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLEVEL, Value, Val_ID);
   PrintConfig0008(); /* display power supply frequency */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PFREQUENCY, Value, Val_ID);
   PrintConfig0012(); /* display software version */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSWVERSION, Value, Val_ID);
   PrintConfig0012A(); /* display SBC software version */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSWVERSION, Value, Val_ID);

   /* right half-page */
   PrintCalibrationDate(); /* display year, month, and day of calibration */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCALDATE, Value, Val_ID);
   PrintConfig0010(); /* display actuator type */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTUATOR, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   PrintConfig0016(); /* display cylinder diameter, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCYLDIAMETER, Value, Val_ID);
   PrintConfig0017(); /* display cylinder stroke, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PCYLSTROKE, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   return (VGAPrintLength);
}

UINT16 SystemPresetReport4(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of 2nd preset page report       **
 **------------------------------------------------------------------**/
{
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /* left half-page */
   PrintConfig0004(); /* display power supply lifetime counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSLIFETIME, Value, Val_ID);
   PrintConfig0022(); /* display weld cycle counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESETCOUNTER, Value, Val_ID);
   PrintConfig0077(); /* display actuator lifetime counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PACTLIFETIME, Value, Val_ID);
   PrintConfig0005(); /* display overload counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, POVERLCOUNTER, Value, Val_ID);
   PrintConfig0006(); /* display general alarm counter */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PGENALARMCNTR, Value, Val_ID);

   /* right half-page */
   PrintConfig0014(); /* display power supply serial number */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPSSERNUM, Value, Val_ID);
   PrintConfig0015(); /* display actuator serial number */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTSERNUM, Value, Val_ID);

   /* display power supply type */
   Value = (UINT8) (DUPS_Info.DUPSFlag);
   ValueFlag = TRUE;
   Val_ID = PWR_SUPPLY_PRNT;
   VGAPrintParam = ALWAYS;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   return (VGAPrintLength);
}

/**-----------------------------------------------------**
 ** This function prints the page number left justified **
 ** at top of page.                                     **
 **-----------------------------------------------------**/
void PrintDupsPageNumber1(void)
{
   SINT8 TempStr[20];

   sprintf(TempStr, " %d", 1);
   strcpy(VGABuffer, TempStr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_PAGE1_NUM_ID;
}

void PrintDupsPageNumber2(void)
{
   GetDateTime();
   strcpy(VGABuffer, datestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_PAGE2_NUM_ID;
}

void PrintDupsPageNumber3(void)
{
   strcpy(VGABuffer, timestr);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_TIME_ID;
}

UINT16 DupsPresetReport1(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of Dups  preset page report        **
 **------------------------------------------------------------------**/
{
   UINT16 DupsPresetNum = DUPS_CURRPARAMSET + 1;
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAPrintParam = ALWAYS;

   PrintDupsPageNumber1();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate += (PrintLineHeight * 2);
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_CREATED_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Print current DUPS preset number */
   sprintf(TempVGABuffer, " %d", DupsPresetNum);
   strcpy(VGABuffer, TempVGABuffer);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_PRESET_NUM_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Print Weld Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_WELD_HEAD_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINT;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_AMP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldPhaseLoop);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_PAHSE_LOOP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C1 */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldAmplitudeLoopC1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_AMP_LOOP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Weld High */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldFreqLimitHigh);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_FREQ_HIGH_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Limit */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldPhaseLimit);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_PHASE_LIM_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   /* Ramp Time */
   FormatVariables(CurrentPreset.DUPS_HostParamSet.WeldRampTime, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_RAMP_TIME_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop CF */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldPhaseLoopCF);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_PHASE_LOOPC_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C2 */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldAmplitudeLoopC2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_AMP_LOOP2_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Weld Low */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.WeldFreqLimitLow);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_FREQ_LOW_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Limit */
   FormatVariables(CurrentPreset.DUPS_HostParamSet.WeldPhaseLimitTime, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_PHASE_TIME_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Horn Scan Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_HORNSCAN_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINT;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(HornScanInfo.MaximumAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_HORN_MAX_AMP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq Start */
   ConvertNumberToString(HornScanInfo.StartFreq);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_HORN_START_FREQ_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Limit *///fixme: AT - no phase limit? onlu time delay
   FormatVariables(HornScanInfo.TimeDelay, TIME, VGAMisc, 6, CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_HORN_TIME_DLY_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   ConvertNumberToString(HornScanInfo.MaximumCurrent);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_HORN_MAX_CUR_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   ConvertNumberToString(HornScanInfo.StopFreq);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_HORN_STOP_FREQ_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Seek Functions header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_SEEK_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   Font_Print = FONT_PRINT;
   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /*--           *left half-page*           --*/
   /* Amplitude */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekAmplitude);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_AMP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Phase Loop CF*/
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekPhaseLoopCF);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_PHASE_LOOP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq High */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekFreqLimitHigh);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_FREQ_LIM_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C2 */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekAmplitudeLoopC2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_AMP_LOOP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   /* Phase Loop */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekPhaseLoop);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_PHASE_LOOP2_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Freq Low */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekFreqLimitLow);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_FREQ_LOW_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Amp Loop C1 */
   ConvertNumberToString(CurrentPreset.DUPS_HostParamSet.SeekAmplitudeLoopC1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_AMP_LOOP2_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   return (VGAPrintLength);
}

UINT16 DupsPresetReport2(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints second half of Dups  preset page report     **
 **------------------------------------------------------------------**/
{
   UINT16 i;
   VGAPrintLength = 0;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   /* Print Software DIP Settings header */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_DIP_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   Font_Print = FONT_PRINT;
   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /*--           *left half-page*           --*/
   /* Memory - On or Off */
   Value = (UINT8) (DUPS_Info.DUPSMemFlag);
   ValueFlag = TRUE;
   Val_ID = D_MEM_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Timed Seek - On or Off */
   Value = (UINT8) (DUPS_Info.DUPSMemFlag);
   ValueFlag = TRUE;
   Val_ID = D_TIMEDSEEK_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /*--           *right half-page*           --*/
   /* Ramp Time */
   FormatVariables(CurrentPreset.DUPS_HostParamSet.WeldRampTime, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_WELD_RAMP_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   /* Seek Time */
   FormatVariables(CurrentPreset.DUPS_HostParamSet.SeekTime, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = D_SEEK_TIME_ID;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINTBOLD;

   /**********************************************************************************/

   /* Print comments/status header for other DUPS presets */
   LeftPrintXCoordinate = MID_XCOORDINATE;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = D_STATUS_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   Font_Print = FONT_PRINT;

   for (i = 0; i < 20; i++)
   {
      sprintf(TempVGABuffer, "%d", i + 1); /*Index no. */
      strcpy(VGABuffer, TempVGABuffer);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = D_TEXT_ID;
      if (i % 2)
      {
         VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         RightPrintYCoordinate -= PrintLineHeight;
      } else
      {
         VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
         LeftPrintYCoordinate -= PrintLineHeight;
      }
   }

   LeftPrintYCoordinate += (PrintLineHeight * 4);
   RightPrintYCoordinate += (PrintLineHeight * 4);
   Font_Print = FONT_PRINTBOLD;
   /**********************************************************************************/

   Value = 0; /*Comments */
   ValueFlag = TRUE;
   Val_ID = D_NUM_ID;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   return (VGAPrintLength);
}

UINT8 GetWeldMode_Str(UINT16 WeldMode)
/*--------------------------------------------*
 * Prpare the Preset Header string to display *
 * WeldMode,PresetNum & PresetName.           *
 *--------------------------------------------*/
{
   UINT8 Value;

   switch (WeldMode)
   { /* Get the weld mode string.  */
   case TIMEMODE:
      Value = 0;
      break;

   case ENERGYMODE:
      Value = 1;
      break;

   case PKPOWERMODE:
      Value = 2;
      break;

   case COLLAPSEMODE:
      Value = 3;
      break;

   case ABSOLUTEMODE:
      Value = 4;
      break;

   case GRDDETECTMODE:
      Value = 5;
      break;

   case CONTINUOUSMODE:
      Value = 6;
      break;

   default:
      Value = 7;
      break;
   }
   return (Value);
}

void GetWeldMode_Value(SETUPS_Ver1200* TempPreset, UINT16 WeldMode)
/****************************************************************************/
/*                                                                          */
/* Creates the text that should appear on the top line of the run screen.   */
/* StrTopLine must be updated for all the languages                      */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Index;
   SINT8 Str[VGA_LINESIZE];

   for (Index = 0; Index < LINESIZE; Index++)
      Str[Index] = FILLCHAR;
   Str[LINESIZE] = 0;

   switch (WeldMode)
   {
   case TIMEMODE:
      FormatVariables(TempPreset->WeldTime, TIME, Str, LINESIZE,
            CurrentSetup.Units);
      strcpy(TempVGABuffer, Str);
      break;

   case ENERGYMODE:
      if (TempPreset->WeldEnergy < 10000)
         FormatVariables(TempPreset->WeldEnergy, ENERGY, Str, LINESIZE,
               CurrentSetup.Units);
      else
         FormatVariables(TempPreset->WeldEnergy, ENERGYDIV10, Str, LINESIZE,
               CurrentSetup.Units);
      strcpy(TempVGABuffer, Str);
      break;

   case PKPOWERMODE:
      FormatVariables(TempPreset->PeakPwr, PERCENTX10, Str, LINESIZE,
            CurrentSetup.Units);
      strcpy(TempVGABuffer, Str);
      break;

   case COLLAPSEMODE:
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         FormatVariables(TempPreset->ColDist, DISTANCE, Str, LINESIZE,
               CurrentSetup.Units);
         strcpy(TempVGABuffer, Str);
      } else
         strcpy(TempVGABuffer, " ");
      break;

   case ABSOLUTEMODE:
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         FormatVariables(TempPreset->AbsDist, DISTANCE, Str, LINESIZE,
               CurrentSetup.Units);
         strcpy(TempVGABuffer, Str);
      } else
         strcpy(TempVGABuffer, " ");
      break;

   case GRDDETECTMODE:
      strcpy(TempVGABuffer, " ");
      break;

   case CONTINUOUSMODE:
      strcpy(TempVGABuffer, " ");
      break;

   default:
      strcpy(TempVGABuffer, " ");
      break;
   }
}

UINT16 PrintSeqPresetInfo(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints Sequence Preset information                **
 **------------------------------------------------------------------**/
{
   UINT16 Index, Index1;
   UINT16 Coloumn1XCoordinate;
   UINT16 Coloumn2XCoordinate;
   UINT16 Coloumn3XCoordinate;
   UINT16 Coloumn4XCoordinate;
   SETUPS_Ver1200 *TempPreset;
   VGAPrintLength = 0;

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAPrintParam = ALWAYS;

   Coloumn1XCoordinate = LeftPrintXCoordinate + 80;
   Coloumn2XCoordinate = LeftPrintXCoordinate + 250;
   Coloumn3XCoordinate = LeftPrintXCoordinate + 550;
   Coloumn4XCoordinate = LeftPrintXCoordinate + 800;

   PrintDupsPageNumber1();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber2();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   PrintDupsPageNumber3();
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   RightPrintYCoordinate += (PrintLineHeight * 2);
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = TIME_CREATED_DATE_PRNT;
   VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += (PrintLineHeight * 3);
   RightPrintYCoordinate += (PrintLineHeight * 3);
   Font_Print = FONT_PRINT;

   /*Prepare Sequence Setup Header*/
   LeftPrintXCoordinate = Coloumn1XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = TIME_CREATED_DATE_PRNT;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PrintLineHeight;

   LeftPrintXCoordinate = Coloumn2XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = WELD_MODE_PRNT;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PrintLineHeight;

   LeftPrintXCoordinate = Coloumn3XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = TIME_PRNT;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   LeftPrintYCoordinate -= PrintLineHeight;

   LeftPrintXCoordinate = Coloumn4XCoordinate;
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = ENRGY_PRNT;
   VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   for (Index = 0; Index < CurrentSetup.SequenceCount; Index++)
   {
      Index1 = CurrentSetup.SequenceList[Index];
      /*Index No.*/
      LeftPrintXCoordinate = LEFT_XCOORDINATE;
      Numout1(Index + 1, 10, '0', 2, TempVGABuffer);
      strcpy(VGABuffer, TempVGABuffer);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PKPOWR_PRNT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PrintLineHeight;

      /* Preset No.*/
      Numout1(Index1, 10, '0', 4, TempVGABuffer);
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn1XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = COLLAPSE_PRNT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PrintLineHeight;

      /*Preset  Name */
      TempPreset = Readpreset(Index1);
      StrCpyTwoBytes(TempVGABuffer, TempPreset->PresetID);
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn2XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = ABSOLUTE_PRNT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PrintLineHeight;

      /*Weld Mode */
      //LeftPrintXCoordinate = Coloumn3XCoordinate;
      LeftPrintXCoordinate = Coloumn2XCoordinate - 40;
      Value = GetWeldMode_Str(TempPreset->WeldMode);
      ValueFlag = TRUE;
      Val_ID = GRDDETECT_PRNT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      LeftPrintYCoordinate -= PrintLineHeight;

      /*Value */
      GetWeldMode_Value(TempPreset, TempPreset->WeldMode);
      strcpy(VGABuffer, TempVGABuffer);
      LeftPrintXCoordinate = Coloumn4XCoordinate;
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = CONTINOUS_PRNT;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   return (VGAPrintLength);
}



/**----------------------------------------------**
 ** This function displays the current weld mode.**
 **----------------------------------------------**/
UINT16 ViewPresetSetup0002(void)
{
   UINT16 param;

   switch (CurrentViewPreset.WeldMode)
   {
   case TIMEMODE:
      Value = 0;
      param = PWELDTIME;
      break;

   case ENERGYMODE:
      Value = 1;
      param = PENERGY;
      break;

   case PKPOWERMODE:
      Value = 2;
      param = PPEAKPOWER;
      break;

   case COLLAPSEMODE:
      Value = 3;
      param = PCOLDIST;
      break;

   case ABSOLUTEMODE:
      Value = 4;
      param = PABSDIST;
      break;

   case GRDDETECTMODE:
      Value = 5;
      param = PGROUNDDETECTCUTOFF;
      break;

   case CONTINUOUSMODE:
      Value = 6;
      param = PCONTINUOUS;
      break;

   default:
      Value = 0;
      param = PWELDTIME;
      break;
   }
   ValueFlag = TRUE;
   Val_ID = WELDMODE_TXT;
   VGAPrintParam = param;
   return (param);
}
/**------------------------------------------------**
 ** This function displays the current value based **
 ** on the weld mode.                              **
 **------------------------------------------------**/
UINT16 ViewPresetSetup0003(void)
{
   UINT16 param = 0;

   switch (CurrentViewPreset.WeldMode)
   {
   case TIMEMODE:
      FormatVariables(CurrentViewPreset.WeldTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PWELDTIME;
      Val_ID = TIME_TXT;
      break;

   case ENERGYMODE:
      FormatVariables(CurrentViewPreset.WeldEnergy,
      /* cont'd */CurrentViewPreset.WeldEnergy > ENERGYPOINT ? ENERGYDIV10
            : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PENERGY;
      Val_ID = ENRGY_TXT;
      break;

   case PKPOWERMODE:
      FormatVariables(CurrentViewPreset.PeakPwr, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PPEAKPOWER;
      Val_ID = PKPOWR_TXT;
      break;

   case COLLAPSEMODE:
      FormatVariables(CurrentViewPreset.ColDist, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PCOLDIST;
      Val_ID = COLLAPSE_TXT;
      break;

   case ABSOLUTEMODE:
      FormatVariables(CurrentViewPreset.AbsDist, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PABSDIST;
      Val_ID = ABSOLUTE_TXT;
      break;

   case GRDDETECTMODE:
      FormatVariables(CurrentViewPreset.ScrubTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      param = PSCRUBTIME;
      Val_ID = GRDDETECT_TXT;
      break;

   case CONTINUOUSMODE:
      param = ALWAYS;
      Val_ID = CONTINOUS_TXT;
      break;

   default:
      param = ALWAYS;
      Val_ID = ALLMODE_TXT;
      break;
   }
   Value = 0;
   ValueFlag = FALSE;
   VGAPrintParam = param;
   return (param);
}

/**----------------------------------------**
 ** This function displays the Amplitude.  **  
 **----------------------------------------**/
void ViewPresetSetup0015(void)
{
   if (CurrentSetup.AmpControl == TRUE)
   {

      /* BIT0 = FIXED, BIT2-BIT6 = STEP */
      if ((CurrentViewPreset.Amp2Flag & BIT0) == TRUE)
      {
         Value = CurrentSetup.AmpControl;
         ValueFlag = TRUE;
         Val_ID = AMPLITUDE_TXT;
      } else
      {
         ConvertNumberToString(CurrentViewPreset.Amp1);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = AMP_PERCENT_VAL_TXT;
      }
   } else
   {
      Value = CurrentSetup.AmpControl;
      ValueFlag = TRUE;
      Val_ID = AMPLITUDE_TXT;
   }
   VGAPrintParam = PAMPLITUDEA;
}

/**-----------------------------------------**
 ** This function displays the Amplitude(A) **
 ** indented if the Amplitude is ON.        **
 **-----------------------------------------**/
void ViewPresetSetup0016(void)
{
   if (((CurrentViewPreset.Amp2Flag & BIT0) == TRUE)
         && ((CurrentSetup.AmpControl & BIT0) == TRUE))
   { // Internal
      ConvertNumberToString(CurrentViewPreset.Amp1);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = AMPA_TXT;
      VGAPrintParam = PAMPLITUDEA1;

   }
}

/**-----------------------------------------**
 ** This function displays the Amplitude(B) **
 ** indented if Amplitude Step is on.       **    
 **-----------------------------------------**/
void ViewPresetSetup0017(void)
{
   if (((CurrentViewPreset.Amp2Flag & BIT0) == TRUE)
         && ((CurrentSetup.AmpControl & BIT0) == TRUE))
   { // Internal
      ConvertNumberToString(CurrentViewPreset.Amp2);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = AMPB_TXT;
      VGAPrintParam = PAMPLITUDEB;
   }
}

/**-----------------------------------------------**
 ** This function displays the Amplitude Step  At.**
 **-----------------------------------------------**/
UINT16 ViewPresetSetup0018A(void)
{
   UINT16 param = PAMPLITUDEA;

   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal

      if ((CurrentViewPreset.Amp2Flag & BIT0) == TRUE)
      {
         /* Stepping enabled on time          */
         if ((CurrentViewPreset.Amp2Flag & BIT2) == FALSE)
         {
            FormatVariables(CurrentViewPreset.AmpTrigTimeValue, TIME, VGAMisc,
                  6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_TIME_TXT;
         }
         /* Stepping enabled on energy        */
         else if ((CurrentViewPreset.Amp2Flag & BIT3) == FALSE)
         {
            FormatVariables(
                  CurrentViewPreset.AmpTrigEnerValue,
                  CurrentViewPreset.AmpTrigEnerValue > ENERGYPOINT ? ENERGYDIV10
                        : ENERGY, VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_ENRGY_TXT;
         }
         /* Stepping enabled on peak power    */
         else if ((CurrentViewPreset.Amp2Flag & BIT4) == FALSE)
         {
            FormatVariables(CurrentViewPreset.AmpTrigPowerValue, PERCENTX10,
                  VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_PKPOWEER_TXT;
         }
         /* Stepping enabled on collapse dist */
         else if ((CurrentViewPreset.Amp2Flag & BIT5) == FALSE)
         {
            FormatVariables(CurrentViewPreset.AmpTrigColValue, DISTANCE,
                  VGAMisc, 6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = STEP_COLDIST_TXT;
         }
         else if ((CurrentViewPreset.Amp2Flag & BIT7) == FALSE)
         {
        	Value = 1;
            ValueFlag = TRUE;
            Val_ID = STEP_EXTSIGNAL_TXT;
         } else
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = STEP_OFF_TXT;
         }
         VGAPrintParam = param;
      }
   }
   return (param);
}

/**---------------------------------------------**
 ** This function displays the Pretrigger flag. ** 
 **---------------------------------------------**/
void ViewPresetSetup0019(void)
{
   Value = (UINT8) CurrentViewPreset.PreTrigFlag;
   ValueFlag = TRUE;
   Val_ID = PRETRIG_TXT;
   VGAPrintParam = PPRETRIGGER;
}

/**-------------------------------------------------**
 ** This function displays the Pretrigger mode.     **
 **-------------------------------------------------**/
void ViewPresetSetup0019B(void)
{
	  if (CurrentViewPreset.PreTriggerDistanceFlag == FALSE) // Pretrigger on distance
	   {
		  Value = 0;
		  Val_ID = PRETRIG_TYPE_TXT;
	   } else if (CurrentViewPreset.PreTrigDelayFlag == FALSE) // Pretrigger on delay
	   {
		  Value = 1;
		  Val_ID = PRETRIG_TYPE_TXT;
	   } else // None of the above, auto
	   {
		  Value = 2;
		  Val_ID = PRETRIG_TYPE_TXT;

	   }

	ValueFlag = TRUE;

   VGAPrintParam = PAUTOPRETRIGGER;
}

/**--------------------------------------------------------**
 ** This function displays the Pretrigger At Distance/Time **
 **--------------------------------------------------------**/
void ViewPresetSetup0019A(void)
{
      if ((CurrentViewPreset.PreTriggerDistanceFlag & BIT0) == FALSE)
      {
         FormatVariables(CurrentViewPreset.PreTriggerDistance, DISTANCE, VGAMisc, 6,
               CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DIST_TXT;
         VGAPrintParam = PPRETRIGGERDISTANCE;
      } else if ((CurrentViewPreset.PreTrigDelayFlag & BIT0) == FALSE)
      {
         FormatVariables(CurrentViewPreset.PreTrigDelay, TIME, VGAMisc, 6,
               CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRETRIG_DLY_TXT;
         VGAPrintParam = PPRETRIGGERDISTANCE;
      } else {
    	  Value = 0;
    	  Val_ID = BLANK_PRNT;
    	  VGAPrintParam = 0;
      }
}

/**--------------------------------------------------**
 ** This function displays the Pretrigger Amplitude. **
 **--------------------------------------------------**/
void ViewPresetSetup0021(void)
{
   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal
      ConvertNumberToString(CurrentViewPreset.PreTrigAmp);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRETRIG_AMP_TXT;
      VGAPrintParam = PPRETRIGGERAMP;
   }
}

/**----------------------------------------**
 ** This function displays the Max Timeout **
 **----------------------------------------**/
void ViewPresetSetup0070(void)
{
   if ((CurrentViewPreset.WeldMode == GRDDETECTMODE)
         || (((CurrentViewPreset.WeldMode == ENERGYMODE)
               || (CurrentViewPreset.WeldMode == COLLAPSEMODE))
               && (CurrentSetup.ControlLevel >= LEVEL_e)) ||

   (((CurrentViewPreset.WeldMode == PKPOWERMODE) || (CurrentViewPreset.WeldMode
         == ABSOLUTEMODE)) && (CurrentSetup.ControlLevel >= LEVEL_ea)))
   {
      FormatVariables(CurrentViewPreset.MaxTimeout, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MAX_TIMEOUT_TXT;
      VGAPrintParam = PMAXTIMEOUT;
   }
}

/**----------------------------------------**
 ** This function displays the External    **
 ** Trigger Delay - on or off              **
 **----------------------------------------**/
void ViewPresetSetup0070A(void)
{
   Value = (UINT8) CurrentViewPreset.ExtTrgDelay;
   ValueFlag = TRUE;
   Val_ID = EXTTRIG_DLY_TXT;
   VGAPrintParam = PEXTTRIGDLY;
}

/* -------------------------------------------------------Right Half Page functions---------------------------------- */

/**-----------------------------------------------**
 ** This function displays the current Hold Time. **
 **-----------------------------------------------**/
void ViewPresetSetup0004(void)
{
   /* Hold Time */
   if ((CurrentViewPreset.HoldTimeFlag & BIT0) == FALSE)
   {

      FormatVariables(CurrentViewPreset.HoldTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = HOLDTIME_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = HOLDTIME_OFF_TXT;
   }
   VGAPrintParam = PHOLDTIME;
}

/**----------------------------------------**
 ** This function displays the Afterburst. **
 **----------------------------------------**/
void ViewPresetSetup0022(void)
{
   Value = (UINT8) CurrentViewPreset.AbFlag;
   ValueFlag = TRUE;
   Val_ID = ABRUST_TXT;
   VGAPrintParam = PAFTERBURST;
}

/**----------------------------------------------**
 ** This function displays the Afterburst Delay. **
 **----------------------------------------------**/
void ViewPresetSetup0023(void)
{
   FormatVariables(CurrentViewPreset.AbDelay, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   ValueFlag = FALSE;
   Val_ID = ABRUST_DLY_TXT;
   VGAPrintParam = PAFTERBURSTDELAY;
}

/**--------------------------------------------**
 ** This function displays the Afterburst time **
 ** indented if Afterburst is on.              **
 **--------------------------------------------**/
void ViewPresetSetup0024(void)
{
   FormatVariables(CurrentViewPreset.AbTime, TIME, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   ValueFlag = FALSE;
   Val_ID = ABTIME_TXT;
   VGAPrintParam = PAFTERBURSTTIME;
}

/**-----------------------------------------**
 ** This function displays the Afterburst   **
 **  Amplitude indented if Afterburst is on.**
 **
 -----------------------------------------**/
void ViewPresetSetup0025(void)
{
   if ((CurrentSetup.AmpControl & BIT0) == TRUE)
   { // Internal
      ConvertNumberToString(CurrentViewPreset.AbAmp);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = ABAMP_TXT;
      VGAPrintParam = PAFTERBURSTAMP;
   }
}

/**---------------------------------------------**
 ** This function displays the Energy Braking   **
 ** state - On or Off                           **
 **---------------------------------------------**/
void ViewPresetSetup0025A(void)
{
   Value = (UINT8) CurrentViewPreset.EnergyBraking;
   ValueFlag = TRUE;
   Val_ID = ENRGYBRAKING_TXT;
   VGAPrintParam = PENERGYBRAKING;
}

/**--------------------------------------------**
 ** This function displays the Post Weld Seek. **
 **-------------------------------------------**/
void ViewPresetSetup0026(void)
{
   Value = (UINT8) (CurrentViewPreset.SeekFunFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = POSTWELD_TXT;
   VGAPrintParam = PPOSTWELDSEEK;
}

/**----------------------------------------------**
 ** This function displays the Frequency Offset. **  
 **----------------------------------------------**/
void ViewPresetSetup0027(void)
{
   if (CurrentSetup.FreqControl == TRUE)
   {
      if ((CurrentViewPreset.FreqOffsetFlag & BIT0) == BIT0)
      {
         ConvertNumberToString(CurrentViewPreset.FreqOffset);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = FREQ_OFFSET_VAL_TXT;
      } else
      {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = FREQ_OFFSET_TXT;
      }
   } else
   {
      Value = 1;
      ValueFlag = TRUE;
      Val_ID = FREQ_OFFSET_TXT;

   }
   VGAPrintParam = PFREQCONTROL;
}

/**--------------------------------------------**
 ** This function displays the Digital Tune    **
 **--------------------------------------------**/
void ViewPresetConfig0081(void)
{
   UINT32 DigTuneVal;

   DigTuneVal = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
   case FREQ15KHZ:
      DigTuneVal += CurrentSetup.DigTune / 8;
      break;
   case FREQ20KHZ:
      DigTuneVal += CurrentSetup.DigTune / 6;
      break;
   case FREQ30KHZ:
      DigTuneVal += CurrentSetup.DigTune / 4;
      break;
   case FREQ60KHZ:
      DigTuneVal += CurrentSetup.DigTune / 2;
      break;
   case FREQ40KHZ:
   default:
      DigTuneVal += CurrentSetup.DigTune / 2;
      break;
   }

   if (CurrentSetup.DigTuneFlag == TRUE)
   {
      ConvertNumberToString(DigTuneVal);
      Value = 2;
      ValueFlag = FALSE;
      Val_ID = DIGITALTUNE_TXT;
   } else
   {
      Value = (UINT8) CurrentSetup.DigTuneFlag;
      ValueFlag = TRUE;
      Val_ID = DIGITALTUNE_TXT;
   }
   VGAPrintParam = DIGITALTUNE;
}

/**--------------------------------------------**
 ** This function displays the Test Amplitude. **
 **--------------------------------------------**/
void ViewPresetSetup0067(void)
{
   ConvertNumberToString(CurrentViewPreset.TestAmp);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TESTAMP_TXT;
   VGAPrintParam = PTESTAMPLITUDE;
}

/**---------------------------------------------------**
 ** This function displays the Actuator Clear Output. **
 **---------------------------------------------------**/
void ViewPresetConfig0033(void)
{
   Value = (UINT8) (CurrentViewPreset.ActClrFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = ACTCLEAR_OUT_TXT;
   VGAPrintParam = PACTCLEAROUTPUT;
}

/**--------------------------------------**
 ** This function displays the Distance. **
 **--------------------------------------**/
void ViewPresetConfig0033A(void)
{
   if (CurrentSetup.HandHeld == FALSE)
   {
      FormatVariables(CurrentViewPreset.ActClrDistance, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = ACTCLEAR_DIST_TXT;
      VGAPrintParam = PACTCLEARDISTANCE;
   } else
   {
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight;
   }
}

/**----------------------------------------------**
 ** This function displays the Cycle Abort Flag. **
 **----------------------------------------------**/
void ViewPresetSetup0071(void)
{ // ae

   if (!((CurrentViewPreset.WeldMode == GRDDETECTMODE)
         && (CurrentSetup.Actuator == AE)))
   {
      Value = (UINT8) CurrentViewPreset.CycleAbortFlag;
      ValueFlag = TRUE;
      Val_ID = CYCLEABORT_TXT;
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight; /* leave right half-page blank */
      VGAPrintParam = PCYCLEABORTS;
   }
}

/**------------------------------------------------------**
 ** This function displays the Ground Detect Abort Flag. **
 **------------------------------------------------------**/
void ViewPresetSetup0033(void)
{
   if (CurrentViewPreset.WeldMode != GRDDETECTMODE)
   {
      Value = (UINT8) CurrentViewPreset.GndDetectFlag;
      ValueFlag = TRUE;
      Val_ID = GRDDETECT_ABORT_TXT;
      VGAPrintParam = PSCRUBTIME;
   }
}

/**-----------------------------------------------**
 ** This function displays the Missing Part Flag. **
 **-----------------------------------------------**/
void ViewPresetConfig0071(void)
{
   Value = (UINT8) CurrentViewPreset.MissingPartFlag;
   ValueFlag = TRUE;
   Val_ID = MISSINGPART_TXT;
   VGAPrintParam = PMISSINGPARTFLAG;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Min **
 **---------------------------------------------------**/
void ViewPresetConfig0072(void)
{
   if (CurrentViewPreset.MissingMinFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MISSINGPART_MINOFF_TXT;
   } else
   {
      FormatVariables(CurrentViewPreset.MissingPartMin, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MISSINGPART_MIN_TXT;
   }
   VGAPrintParam = PMISSINGPARTMIN;
}

/**---------------------------------------------------**
 ** This function displays the Missing Part Abort Max **
 **---------------------------------------------------**/
void ViewPresetConfig0073(void)
{
   if (CurrentViewPreset.MissingMaxFlag)
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MISSINGPART_MAXOFF_TXT;
   } else
   {
      FormatVariables(CurrentViewPreset.MissingPartMax, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MISSINGPART_MAX_TXT;
   }
   VGAPrintParam = PMISSINGPARTMAX;
}

/* ----------- Left Half Page ----------------- */

/**--------------------------------------------**
 ** This function displays the Control Limits. **
 **--------------------------------------------**/
void ViewPresetSetup0028(void)
{ // ae
   if (!((CurrentViewPreset.WeldMode == PKPOWERMODE) && (CurrentSetup.Actuator
         == AE)))
   {
      Value = (UINT8) (CurrentViewPreset.ControlLimitsFlag & BIT0);
      ValueFlag = TRUE;
      Val_ID = CTRL_LIMITS_TXT;
      VGAPrintParam = PCONTROLLIMITS;
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight; /* leave right half-page blank */
   }
}

/**---------------------------------------------**
 ** This function displays the Collapse Cutoff. **
 **---------------------------------------------**/
void ViewPresetSetup0034B(void)
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
      if (CurrentViewPreset.WeldMode != COLLAPSEMODE)
      {
         if (CurrentViewPreset.ColCutoffFlag)
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = COLCUTOFF_TXT;
         } else
         {
            FormatVariables(CurrentViewPreset.ColCutoffDist, DISTANCE, VGAMisc,
                  6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = COLCUTOFF_DIST_TXT;
         }
      }
      VGAPrintParam = PCOLLAPSECUTOFF;
   }
}

void ViewPresetSetup0034A(void)
/**---------------------------------------------**
 ** This function displays the Absolute Cutoff. **
 **---------------------------------------------**/
{
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
      if (CurrentViewPreset.WeldMode != ABSOLUTEMODE)
      {
         if (CurrentViewPreset.ABSCutoffFlag)
         {
            Value = 0;
            ValueFlag = TRUE;
            Val_ID = ABSCUTOFF_TXT;
         } else
         {
            FormatVariables(CurrentViewPreset.ABSCutoffDist, DISTANCE, VGAMisc,
                  6, CurrentSetup.Units);
            strcpy(VGABuffer, VGAMisc);
            Value = 0;
            ValueFlag = FALSE;
            Val_ID = ABSCUTOFF_DIST_TXT;
         }
         VGAPrintParam = PABSOLUTECUTOFF;
      }
   }
}

/**-----------------------------------------------**
 ** This function displays the Peak Power Cutoff. **
 **-----------------------------------------------**/
void ViewPresetSetup0032(void)
{
   if (CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentViewPreset.PeakPwrCutoffFlag) /* FALSE = on */
      {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = PKPOWERCUTOFF_TXT;
      } else
      {
         FormatVariables(CurrentViewPreset.PeakPwrCutoff, PERCENTX10, VGAMisc,
               6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PKPOWERCUTOFF_VAL_TXT;
      }
      VGAPrintParam = PPKPOWERCUTOFF;
   }
}

/* ----------- Right Half Page ----------------- */

/**-------------------------------------------------**
 ** This function displays the Energy Compensation. **
 **-------------------------------------------------**/
void ViewPresetSetup0029(void)
{
   if (CurrentViewPreset.WeldMode != PKPOWERMODE)
   { // until 2.5
      if (CurrentViewPreset.WeldMode == TIMEMODE)
      {
         Value = (UINT8) (CurrentViewPreset.EnergyCompFlag & BIT0);
         ValueFlag = TRUE;
         Val_ID = ENRGYCOMP_TXT;
         VGAPrintParam = PENERGYCOMP;
      }
   }
}

/**----------------------------------------**
 ** This function displays the Max Energy. **
 **----------------------------------------**/

void ViewPresetSetup0031(void)
{
   if (CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentViewPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentViewPreset.EnergyPL,
         /* cont'd */CurrentViewPreset.EnergyPL > ENERGYPOINT ? ENERGYDIV10
               : ENERGY,
         /* cont'd */VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = MAXENRGY_TXT;
         VGAPrintParam = PENERGYMAX;
      }
   }
}

/**----------------------------------------**
 ** This function displays the Min Energy. **
 **----------------------------------------**/
void ViewPresetSetup0030(void)
{
   if (CurrentViewPreset.WeldMode != PKPOWERMODE)
   {
      if (CurrentViewPreset.WeldMode == TIMEMODE)
      {
         FormatVariables(CurrentViewPreset.EnergyML,
         /* cont'd */CurrentViewPreset.EnergyML > ENERGYPOINT ? ENERGYDIV10
               : ENERGY,
         /* cont'd */VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = MINENRGY_TXT;
         VGAPrintParam = PENGERGYMIN;
      }
   }
}

/**--------------------------------------------------**
 ** This function displays the aef Settings message. **
 **--------------------------------------------------**/
void DisplayAEFSetting(void)
{

   Value = 0;
   ValueFlag = TRUE;
   Val_ID = AEF_SETTINGS_TXT;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PrintLineHeight;
}

/**-------------------------------------------**
 ** This function displays the Rapid Traverse **
 **-------------------------------------------**/
void ViewPresetSetup0012(void)
{
   Value = (UINT8) CurrentViewPreset.RTFlag;
   ValueFlag = TRUE;
   Val_ID = RAPIDTRAVERSE_PRINT_OFF;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------------**
 ** This function displays the R/T At Distance. **
 **---------------------------------------------**/
void ViewPresetSetup0013(void)
{
   FormatVariables(CurrentViewPreset.RTDist, DISTANCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = RAPIDTRAVERSE_PRINT_DISTANCE;
   VGAPrintParam = PRAPIDTRAVS;
}

/**---------------------------------------**
 ** This function displays the Downspeed. **
 **---------------------------------------**/
void ViewPresetSetup0014(void)
{
//   ConvertNumberToString(CurrentViewPreset.DownSpdStart);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = DOWNSPEED_TXT;
   VGAPrintParam = PDOWNSPEED;
}

/**-------------------------------------------**
 ** This function displays the Trigger Force. **
 **-------------------------------------------**/
void ViewPresetSetup0005(void)
{
   FormatVariables(CurrentViewPreset.TriggerForce, FORCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = TRIGFORCE_TXT;
   VGAPrintParam = PTRIGGERFORCE;
}

/**---------------------------------------**
 ** This function displays the Weld Pressure
 ** Step or Value.
 **---------------------------------------**/
void ViewPresetSetup0007(void)
{
   /* BIT0 = FIXED, BIT2-BIT6 = STEP */
   if ((CurrentViewPreset.Pressure2Flag & BIT0) == TRUE) {
      Value = (UINT8) (CurrentViewPreset.Pressure2Flag & BIT0);
      ValueFlag = TRUE;
      Val_ID = PRESSURE_STEP_TXT;
   }
   else {
      FormatVariables(CurrentViewPreset.WeldPressure, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = WELD_PRESSURE;
   }
   VGAPrintParam = PPRESSUREA;
}

/**------------------------------------------**
 ** This function displays the Weld Pressure(A).**
 **------------------------------------------**/
void ViewPresetSetup0008(void)
{
   if ((CurrentViewPreset.Pressure2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentViewPreset.WeldPressure, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_A_TXT;

      VGAPrintParam = PPRESSUREA1;
   }
}

/**------------------------------------------**
 ** This function displays the Weld Pressure(B).**
 **------------------------------------------**/
void ViewPresetSetup0009(void)
{
   if ((CurrentViewPreset.Pressure2Flag & BIT0) == TRUE) {

      FormatVariables(CurrentViewPreset.Pressure2, PRESSURE2, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PRESSURE_B_TXT;

      VGAPrintParam = PPRESSUREB;
   }
}

/**--------------------------------**
 ** This function display Pressure
 ** Stepping trigger point and its
 ** value.
 **--------------------------------**/
UINT16 ViewPresetSetup0018B(void)
{
   UINT16 param = PPRESSUREA1;

   if ((CurrentViewPreset.Pressure2Flag & BIT0) == TRUE) {
      /* Stepping enabled on time          */
      if ((CurrentViewPreset.Pressure2Flag & BIT2) == FALSE) {
         FormatVariables(CurrentViewPreset.PressureTrigTimeValue, TIME, VGAMisc,
               6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_TIME_TXT;
      }
      /* Stepping enabled on energy        */
      else if ((CurrentViewPreset.Pressure2Flag & BIT3) == FALSE) {
         FormatVariables(CurrentViewPreset.PressureTrigEnerValue,
               CurrentViewPreset.PressureTrigEnerValue > ENERGYPOINT ?
                     ENERGYDIV10 : ENERGY, VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_ENRGY_TXT;
      }
      /* Stepping enabled on peak power    */
      else if ((CurrentViewPreset.Pressure2Flag & BIT4) == FALSE) {
         FormatVariables(CurrentViewPreset.PressureTrigPowerValue, PERCENTX10,
               VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_PKPOWER_TXT;
      }
      /* Stepping enabled on collapse dist */
      else if ((CurrentViewPreset.Pressure2Flag & BIT5) == FALSE) {
         FormatVariables(CurrentViewPreset.PressureTrigColValue, DISTANCE,
               VGAMisc, 6, CurrentSetup.Units);
         strcpy(VGABuffer, VGAMisc);
         Value = 0;
         ValueFlag = FALSE;
         Val_ID = PRESSURE_STEP_COLDIST_TXT;
      }
      else if ((CurrentViewPreset.Pressure2Flag & BIT7) == FALSE) {
         Value = 1;
         ValueFlag = TRUE;
         Val_ID = PRESSURE_STEP_EXTSIGNAL_TXT;
      }
      else {
         Value = 0;
         ValueFlag = TRUE;
         Val_ID = PRESSURE_STEP_OFF_TXT;
      }
      VGAPrintParam = param;
   }
   return (param);
}

void PrintForceRamp(void)
{
   Value = 0;
   ValueFlag = TRUE;
   Val_ID = FORCERAMPS_TXT;
   VGAPrintParam = ALWAYS; /* Print in right half-page */
}

/**-----------------------------------------**
 ** This function displays the aed Settings. **
 **-----------------------------------------**/
void PrintAEDSetting(void)
{
   Value = 0;
   ValueFlag = TRUE;
	if(CurrentSetup.Actuator == MICRO)
		Val_ID = MICRO_SETTINGS_TXT;
	else
   		Val_ID = AED_SETTINGS_TXT;
   VGAPrintParam = ALWAYS;
   RightPrintYCoordinate += PrintLineHeight;
}

/**----------------------------------------------**
 ** This function displays the aed Trigger Force.**
 **----------------------------------------------**/
void ViewPresetAEDTrigForce(void)
{
   FormatVariables(CurrentViewPreset.TriggerForce, FORCE, VGAMisc, 6,
         CurrentSetup.Units);
   strcpy(VGABuffer, VGAMisc);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = AEDTRIGFORCE_TXT;
   VGAPrintParam = ALWAYS;
}
///////////////////////////////////////////////////////////////////////////////////////
//                      SYSTEM VIEW PRESET REPORT2                                   //
///////////////////////////////////////////////////////////////////////////////////////

/**------------------------------------------**
 ** This function displays the Reject Limits.**
 **------------------------------------------**/
void ViewPresetSetup0051(void)
{
   Value = (UINT8) (CurrentViewPreset.RejectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJLIMITS_TXT;
   VGAPrintParam = PREJECTLIMITS;
}

/**--------------------------------------------------**
 ** This function displays the Reject Reset Required.**
 **--------------------------------------------------**/
void ViewPresetSetup0052(void)
{
   Value = (UINT8) (CurrentViewPreset.RejResetRequiredFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = REJRESET_TXT;
   VGAPrintParam = PREJRESETREQ;
}

/**-------------------------------------------**
 ** This function displays the Suspect Limits.**
 **-------------------------------------------**/
void ViewPresetSetup0035(void)
{
   Value = (UINT8) (CurrentViewPreset.SuspectLimitsFlag & BIT0);
   ValueFlag = TRUE;
   Val_ID = SUSPTLIMITS_TXT;
   VGAPrintParam = PSUSPECTLIMITS;
}

/**---------------------------------------------------**
 ** This function displays the Suspect Reset Required.**
 **---------------------------------------------------**/
void ViewPresetSetup0036(void)
{
   Value = (UINT8) (CurrentViewPreset.SusResetRequired & BIT0);
   ValueFlag = TRUE;
   Val_ID = SUSPTRESET_TXT;
   VGAPrintParam = PSUSPRESETREQ;
}

// Left page---
/**-----------------------------------------------**
 ** This function displays the + Collapse R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0059(void)
{
   if ((CurrentViewPreset.RejectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0060(void)
{
   if ((CurrentViewPreset.RejectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LCOLLAPSEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Energy R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0055(void)
{
   if ((CurrentViewPreset.RejectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyPLR,
      /* cont'd */CurrentViewPreset.EnergyPLR > ENERGYPOINT ? ENERGYDIV10
            : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0056(void)
{
   if ((CurrentViewPreset.RejectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyMLR,
      /* cont'd */CurrentViewPreset.EnergyMLR > ENERGYPOINT ? ENERGYDIV10
            : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0061(void)
{
   if ((CurrentViewPreset.RejectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute R Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0062(void)
{
   if ((CurrentViewPreset.RejectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_RLIMT_OFF_TXT;
   }
   VGAPrintParam = LABSOLUTEMINUS;
}
/**---------------------------------------------**
 ** This function displays the + Power  R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0057(void)
{
   if ((CurrentViewPreset.RejectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerPLR, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0058(void)
{
   if ((CurrentViewPreset.RejectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerMLR, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERMINUS;
}
/**---------------------------------------------**
 ** This function displays the + Time   R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0053(void)
{
   if ((CurrentViewPreset.RejectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimePLR, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   R Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0054(void)
{
   if ((CurrentViewPreset.RejectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimeMLR, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEMINUS;
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force R Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0065(void)
{
   if ((CurrentViewPreset.RejectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForcePLR, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LRMAXFORCE; // LCOLLAPSEPLUS the same group
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force R Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0066(void)
{
   if ((CurrentViewPreset.RejectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForceMLR, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LRMAXFORCE;
}

/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0063(void)
{
   if ((CurrentViewPreset.RejectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   {
      FormatVariables(CurrentViewPreset.TrsDistPLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0064(void)
{
   if ((CurrentViewPreset.RejectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   {
      FormatVariables(CurrentViewPreset.TrsDistMLR, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Power Band R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0081(void)
{
   if (!CurrentViewPreset.PMCPlusBandFlag)
   {
      ConvertNumberToString(CurrentViewPreset.PMCHighLimit);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPOWERBAND_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPOWERBAND_RLIMT_OFF_TXT;
   }
   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - Power Band R Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0082(void)
{
   if (!CurrentViewPreset.PMCMinusBandFlag)
   {
      ConvertNumberToString(CurrentViewPreset.PMCLowLimit);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPOWERBAND_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPOWERBAND_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0083(void)
{
   if (!(CurrentViewPreset.SBLFreqFlags & BIT1))
   {
      ConvertNumberToString(CurrentViewPreset.SBLMaxFreq);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PSBLFREQ_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PSBLFREQ_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the - R SBL Frequency Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0084(void)
{
   if (!(CurrentViewPreset.SBLFreqFlags & BIT0))
   {
      ConvertNumberToString(CurrentViewPreset.SBLMinFreq);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MSBLFREQ_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MSBLFREQ_RLIMT_OFF_TXT;
   }

   VGAPrintParam = ALWAYS;
}

/**-------------------------------------------------------**
 ** This function displays the + R Downspeed Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0085(void)
{
   if ((CurrentViewPreset.RVelLimitMask & BIT2) != BIT2)
   {
	  FormatVariables(CurrentViewPreset.VelocityPLR, VELOCITY, VGAMisc, 6,
	               CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PDOWNSPEED_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PDOWNSPEED_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LDOWNSPEEDPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - R Downspeed Limit.   **
 **-------------------------------------------------------**/
void ViewPresetSetup0086(void)
{
   if ((CurrentViewPreset.RVelLimitMask & BIT1) != BIT1)
   {
	  FormatVariables(CurrentViewPreset.VelocityMLR, VELOCITY, VGAMisc, 6,
	   	               CurrentSetup.Units);
	  strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MDOWNSPEED_RLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MDOWNSPEED_RLIMT_OFF_TXT;
   }

   VGAPrintParam = LDOWNSPEEDMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Collapse S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0043(void)
{
   if ((CurrentViewPreset.SuspectLimits & PCOLDISTBIT) != PCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PCOL_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PCOL_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LCOLLAPSEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Collapse S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0044(void)
{
   if ((CurrentViewPreset.SuspectLimits & MCOLDISTBIT) != MCOLDISTBIT)
   {
      FormatVariables(CurrentViewPreset.ColMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MCOL_SLIMT_TXT;
   } else

   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MCOL_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LCOLLAPSEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Energy S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0039(void)
{
   if ((CurrentViewPreset.SuspectLimits & PENERGYBIT) != PENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyPLS,
      /* cont'd */CurrentViewPreset.EnergyPLS > ENERGYPOINT ? ENERGYDIV10
            : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PENRGY_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PENRGY_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LENERGYPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Energy S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0040(void)
{
   if ((CurrentViewPreset.SuspectLimits & MENERGYBIT) != MENERGYBIT)
   {
      FormatVariables(CurrentViewPreset.EnergyMLS,
      /* cont'd */CurrentViewPreset.EnergyMLS > ENERGYPOINT ? ENERGYDIV10
            : ENERGY,
      /* cont'd */VGAMisc, 6, CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MENRGY_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MENRGY_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LENERGYMINUS;
}

/**-----------------------------------------------**
 ** This function displays the + Absolute S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0045(void)
{
   if ((CurrentViewPreset.SuspectLimits & PABSDISTBIT) != PABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PABSOLUTE_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PABSOLUTE_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEPLUS;
}

/**-----------------------------------------------**
 ** This function displays the - Absolute S Limit.**
 **-----------------------------------------------**/
void ViewPresetSetup0046(void)
{
   if ((CurrentViewPreset.SuspectLimits & MABSDISTBIT) != MABSDISTBIT)
   {
      FormatVariables(CurrentViewPreset.AbsMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MABSOLUTE_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MABSOLUTE_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LABSOLUTEMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Power  S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0041(void)
{
   if ((CurrentViewPreset.SuspectLimits & PPKPOWERBIT) != PPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerPLS, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PPKPOWER_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PPKPOWER_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Power  S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0042(void)
{
   if ((CurrentViewPreset.SuspectLimits & MPKPOWERBIT) != MPKPOWERBIT)
   {
      FormatVariables(CurrentViewPreset.PowerMLS, PERCENTX10, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MPKPOWER_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MPKPOWER_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LPOWERMINUS;
}

/**---------------------------------------------**
 ** This function displays the + Time   S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0037(void)
{
   if ((CurrentViewPreset.SuspectLimits & PTIMEBIT) != PTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimePLS, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTIME_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTIME_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEPLUS;
}

/**---------------------------------------------**
 ** This function displays the - Time   S Limit.**
 **---------------------------------------------**/
void ViewPresetSetup0038(void)
{
   if ((CurrentViewPreset.SuspectLimits & MTIMEBIT) != MTIMEBIT)
   {
      FormatVariables(CurrentViewPreset.TimeMLS, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTIME_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTIME_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTIMEMINUS;
}

/**-------------------------------------------------**
 ** This function displays the + Weld Force S Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0049(void)
{
   if ((CurrentViewPreset.SuspectLimits & PFORCEBIT) != PFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForcePLS, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PWELDFORCE_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PWELDFORCE_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LMAXFORCEPLUS;
}

/**-------------------------------------------------**
 ** This function displays the - Weld Force S Limit.**
 **-------------------------------------------------**/
void ViewPresetSetup0050(void)
{
   if ((CurrentViewPreset.SuspectLimits & MFORCEBIT) != MFORCEBIT)
   {
      FormatVariables(CurrentViewPreset.WeldForceMLS, FORCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MWELDFORCE_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MWELDFORCE_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LMAXFORCEMINUS;
}

/**-------------------------------------------------------**
 ** This function displays the + Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0047(void)
{
   if ((CurrentViewPreset.SuspectLimits & PTRIGDISTBIT) != PTRIGDISTBIT)
   {
      FormatVariables(CurrentViewPreset.TrsDistPLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = PTRIGDIST_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = PTRIGDIST_SLIMT_OFF_TXT;
   }

   VGAPrintParam = LTRIGGERDISTPLUS;
}

/**-------------------------------------------------------**
 ** This function displays the - Trigger Distance S Limit.**
 **-------------------------------------------------------**/
void ViewPresetSetup0048(void)
{
   if ((CurrentViewPreset.SuspectLimits & MTRIGDISTBIT) != MTRIGDISTBIT)
   {
      FormatVariables(CurrentViewPreset.TrsDistMLS, DISTANCE, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = MTRIGDIST_SLIMT_TXT;
   } else
   {
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = MTRIGDIST_SLIMT_OFF_TXT;
   }
   VGAPrintParam = LTRIGGERDISTMINUS;
}

/**------------------------------------------------------------------**
 ** This function prepares left section of preset parameter printing **
 **------------------------------------------------------------------**/
void VGA_PresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID)
{
   if (CheckIfPrintable(param) && (VGAPrintParam == param))
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID));
      VGAPrintLength
            += AddToBuffer(AckBuf, (UINT8) (LeftPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (LeftPrintXCoordinate));
      VGAPrintLength
            += AddToBuffer(AckBuf, (UINT8) (LeftPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (LeftPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

      if (ValueFlag == TRUE)
      {
         VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
      } else
      {
         if (Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
         VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));
         VGAPrintLength
               += AddToBufferString(AckBuf, String, LangStrLen(String));
      }
      LeftPrintYCoordinate = LeftPrintYCoordinate + PrintLineHeight;
   }
}

/**------------------------------------------------------------------**
 ** This function prepares right section of preset parameter printing **
 **------------------------------------------------------------------**/
void VGA_PresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID)
{
   if (CheckIfPrintable(param) && (VGAPrintParam == param))
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID));
      VGAPrintLength += AddToBuffer(AckBuf,
            (UINT8) (RightPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (RightPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf,
            (UINT8) (RightPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (RightPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

      if (ValueFlag == TRUE)
      {
         VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
      } else
      {
         if (Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));

         VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));
         VGAPrintLength
               += AddToBufferString(AckBuf, String, LangStrLen(String));
      }
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight;

   }
}

/**------------------------------------------------------------------**
 ** This function prepares Reject limit parameter printing section   **
 **------------------------------------------------------------------**/
void VGA_RejLimPresetSetup1(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID)
{
   if (ControlLevelLimit(param) && (VGAPrintParam == param))
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID));

      VGAPrintLength
            += AddToBuffer(AckBuf, (UINT8) (LeftPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (LeftPrintXCoordinate));
      VGAPrintLength
            += AddToBuffer(AckBuf, (UINT8) (LeftPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (LeftPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

      if (ValueFlag)
         VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
      else
      {
         if (Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
         VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));
         VGAPrintLength
               += AddToBufferString(AckBuf, String, LangStrLen(String));
      }
      LeftPrintYCoordinate = LeftPrintYCoordinate + PrintLineHeight;
   }
}

void VGA_SusLimPresetSetup2(UINT8 * *AckBuf, SINT8 String[], UINT16 param,
      UINT8 Data, UINT16 ID)
/**------------------------------------------------------------------**
 ** This function prepares Suspect limit parameter printing section  **
 **------------------------------------------------------------------**/
{
   if (ControlLevelLimit(param) && (VGAPrintParam == param))
   {
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (ID));

      VGAPrintLength += AddToBuffer(AckBuf,
            (UINT8) (RightPrintXCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (RightPrintXCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf,
            (UINT8) (RightPrintYCoordinate >> 8));
      VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (RightPrintYCoordinate));
      VGAPrintLength += AddToBuffer(AckBuf, Font_Print);

      if (ValueFlag)
         VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));
      else
      {
         if (Data == 2)
            VGAPrintLength += AddToBuffer(AckBuf, (UINT8) (Data));

         VGAPrintLength += AddToBuffer(AckBuf, LangStrLen(String));
         VGAPrintLength
               += AddToBufferString(AckBuf, String, LangStrLen(String));
      }
      RightPrintYCoordinate = RightPrintYCoordinate + PrintLineHeight;
   }
}

UINT16 SystemPresetReport5(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 3rdt preset page report          **
 **------------------------------------------------------------------**/
{
	UINT8 VGAPageNumber = 3;

	VGAPrintLength = 0;
	VGAMisc[VGAMISCLEN] = 0x00;
	VGAMisc[VGAMISCLEN + 1] = 0x00;

	LeftPrintXCoordinate = LEFT_XCOORDINATE;
	RightPrintXCoordinate = RIGHT_XCOORDINATE;
	LeftPrintYCoordinate = LEFT_YCOORDINATE;
	RightPrintYCoordinate = RIGHT_YCOORDINATE;
	Font_Print = FONT_PRINTBOLD;

	PrintHeader1(VGAPageNumber);
	VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	PrintHeader2();
	VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	PrintHeader3();
	VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	RightPrintYCoordinate = RightPrintYCoordinate + 1;
	RightPrintXCoordinate = MID_XCOORDINATE - 40;
	Value = 0;
	ValueFlag = TRUE;
	Val_ID = 1;
	VGAPrintParam = ALWAYS;
	VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	RightPrintXCoordinate = MID_XCOORDINATE + 20;
	PrintSubHeader2();
	VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	RightPrintXCoordinate = MID_XCOORDINATE;
	PrintSubHeader3();
	VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	LeftPrintXCoordinate = LEFT_XCOORDINATE;
	RightPrintXCoordinate = RIGHT_XCOORDINATE;

	AssignYCoordinate();
	LeftPrintYCoordinate += PrintLineHeight;
	RightPrintYCoordinate += PrintLineHeight;

	Font_Print = FONT_PRINTBOLD;
	/* Print "PRINTER" header. */
	RightPrintXCoordinate = MID_XCOORDINATE;
	Value = 0;
	ValueFlag = TRUE;
	Val_ID = STREAMING_SETUP_PRNT;
	VGAPrintParam = ALWAYS;
	VGA_PresetSetup2(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	RightPrintXCoordinate = RIGHT_XCOORDINATE;

	AssignYCoordinate();
	LeftPrintYCoordinate += PrintLineHeight;
	RightPrintYCoordinate += PrintLineHeight;
	Font_Print = FONT_PRINT;

	AssignYCoordinate();
	LeftPrintYCoordinate += PrintLineHeight;
	RightPrintYCoordinate += PrintLineHeight;

	PrintConfig0078(); /* display weld summary on alarm - on or off */
	VGA_PresetSetup1(&AckBuf, 0, PUSBFLAG, Value, Val_ID);
	PrintConfig0055(); /* display weld summary on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDDATA, Value, Val_ID);
	PrintConfig0054(); /* display weld summary on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, 0, PWELDDATA, Value, Val_ID);
	PrintConfig0057(); /* display power graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PPOWERGRAPH, Value, Val_ID);
	PrintConfig0056(); /* display power graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PPOWERGRAPH, Value, Val_ID);
	PrintConfig0059(); /* display amplitude graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEGRAPH, Value, Val_ID);
	PrintConfig0058(); /* display amplitude graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PAMPLITUDEGRAPH, Value, Val_ID);
	PrintConfig0061(); /* display frequency graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PFREQUENCYGRAPH, Value, Val_ID);
	PrintConfig0060(); /* display frequency graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQUENCYGRAPH, Value, Val_ID);
	PrintConfig0062B(); /* display collapse distance graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PDISTANCEGRAPH, Value, Val_ID);
	PrintConfig0062A(); /* display collapse distance graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PDISTANCEGRAPH, Value, Val_ID);
	PrintConfig0065(); /* display velocity graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PVELOCITYGRAPH, Value, Val_ID);
	PrintConfig0064(); /* display velocity graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PVELOCITYGRAPH, Value, Val_ID);
	PrintConfig0067(); /* display force graph on sample - count or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PFORCEGRAPH, Value, Val_ID);
	PrintConfig0066(); /* display force graph on alarm - on or off */
	VGA_PresetSetup2(&AckBuf, VGABuffer, PFORCEGRAPH, Value, Val_ID);

	AssignYCoordinate();
	LeftPrintYCoordinate += PrintLineHeight;
	RightPrintYCoordinate += PrintLineHeight;
	/* left half-page */
	PrintSetup0079(); /* display x-axis auto scale - on or off */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOXSCALE, Value, Val_ID);
	LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
	PrintSetup0080(); /* display x-axis time or ***, indented */
	VGA_PresetSetup1(&AckBuf, VGABuffer, PXSCALE, Value, Val_ID);
	LeftPrintXCoordinate = LEFT_XCOORDINATE;

	return (VGAPrintLength);
}

/**********************************************************************/

UINT16 SystemViewPresetReport(UINT8 * AckBuf)
/**------------------------------------------------------------------**
 ** This function prints one half of 1st preset page report          **
 **------------------------------------------------------------------**/
{
   UINT16 param;

   VGAPrintLength = 0;
   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   RightPrintXCoordinate = RIGHT_XCOORDINATE;
   LeftPrintYCoordinate = LEFT_YCOORDINATE;
   RightPrintYCoordinate = RIGHT_YCOORDINATE;
   Font_Print = FONT_PRINTBOLD;
   VGAMisc[VGAMISCLEN] = 0x00;
   VGAMisc[VGAMISCLEN + 1] = 0x00;

   /* Left half-page */
   LeftPrintYCoordinate += (PrintLineHeight * 4);
   RightPrintYCoordinate += (PrintLineHeight * 4);
   Font_Print = FONT_PRINT;

   param = ViewPresetSetup0002(); /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   param = ViewPresetSetup0003(); /* Weld Time or Weld Energy or ..., based on Weld Mode */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   if (CurrentViewPreset.WeldMode == GRDDETECTMODE)
   {
      ViewPresetSetup0003A();
      VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBAMPLITUDE, Value, Val_ID);
   }

   Value = (UINT8)CurrentViewPreset.WeldTrigger;
	ValueFlag = TRUE;
	Val_ID = TRIGGER_FORCE_OR_DIST;
	VGAPrintParam = ALWAYS;
	VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
	//LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
	if(CurrentViewPreset.WeldTrigger){
		ViewPresetSetup0318(); /*Trigger distance*/
		VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERDIST, Value, Val_ID);
	}
	else{
		PrintAEDTrigForce(); /* Trigger Force */
		VGA_PresetSetup1(&AckBuf, VGABuffer, PTRIGGERFORCE, Value, Val_ID);
	}
	//LeftPrintXCoordinate = LEFT_XCOORDINATE;

	/*Amplitude stepping on view current setup*/
   ViewPresetSetup0015(); /* Amplitude */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA, Value, Val_ID);
   VGAPrintParam = ALWAYS;
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0016(); /* Amplitude(A) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEA1, Value, Val_ID);
   ViewPresetSetup0017(); /* Amplitude(B) if amplitude step is on */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PAMPLITUDEB, Value, Val_ID);
   param = ViewPresetSetup0018A(); /* Amplitude Step at Time, Step at Energy, ... */
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);

   /*Pressure stepping on view current setup*/
   if (CurrentSetup.ControlLevel >= LEVEL_c) {
      LeftPrintXCoordinate = LEFT_XCOORDINATE;
      ViewPresetSetup0007(); /* Pressure */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREA, Value, Val_ID);
      LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
      ViewPresetSetup0008(); /* Pressure(A) if Pressure step is on */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREA1, Value, Val_ID);
      ViewPresetSetup0009(); /* Pressure(B) if Pressure step is on */
      VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESSUREB, Value, Val_ID);
      param = ViewPresetSetup0018B(); /* Pressure Step at Time, Step at Energy, ... */
      VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);
   }

   LeftPrintXCoordinate = LEFT_XCOORDINATE;
   ViewPresetSetup0019(); /* Pretrigger Flag - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGER, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   if(CurrentViewPreset.PreTrigFlag)
   {
	   ViewPresetSetup0019B(); /* Auto Pretrigger Flag - On or Off, indented */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PAUTOPRETRIGGER, Value, Val_ID);
	   ViewPresetSetup0019A(); /* Pretrigger Distance, indented */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERDISTANCE, Value, Val_ID);

   }
   ViewPresetSetup0021(); /* Pretrigger Amplitude, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRETRIGGERAMP, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   ViewPresetSetup0070(); /* Max Timeout */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PMAXTIMEOUT, Value, Val_ID);
   ViewPresetSetup0070A(); /* External Trigger Delay */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PEXTTRIGDLY, Value, Val_ID);

   /* Right half-page */
   ViewPresetSetup0004(); /* Hold Time */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PHOLDTIME, Value, Val_ID);
   ViewPresetSetup0022(); /* Afterburst - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURST, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0023(); /* Afterburst Delay, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTDELAY, Value, Val_ID);
   ViewPresetSetup0024(); /* Afterburst Time, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTTIME, Value, Val_ID);
   ViewPresetSetup0025(); /* Afterburst Amplitude, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PAFTERBURSTAMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   ViewPresetSetup0025A(); /* Energy Braking - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYBRAKING, Value, Val_ID);
   ViewPresetSetup0026(); /* Post Weld Seek - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPOSTWELDSEEK, Value, Val_ID);
   ViewPresetSetup0027(); /* Frequency Offset */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PFREQCONTROL, Value, Val_ID);
   ViewPresetConfig0081(); /* Digital Tune */
   VGA_PresetSetup2(&AckBuf, VGABuffer, DIGITALTUNE, Value, Val_ID);
   ViewPresetSetup0067(); /* Test Amplitude */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PTESTAMPLITUDE, Value, Val_ID);
   ViewPresetConfig0033(); /* Actuator Clear Output - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEAROUTPUT, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetConfig0033A(); /* Actuator Clear Distance, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PACTCLEARDISTANCE, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /* Left half-page */
   ViewPresetSetup0071(); /* Cycle Abort - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCYCLEABORTS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0033(); /* Ground Detect Abort - On or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PSCRUBTIME, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   ViewPresetConfig0071(); /* Missing Part - On or Off or N/A */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTFLAG, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetConfig0072(); /* Missing Part Abort Min - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMIN, Value, Val_ID);
   ViewPresetConfig0073(); /* Missing Part Abort Max - Distance or Off or N/A, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PMISSINGPARTMAX, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /* Left half-page */
   ViewPresetSetup0028(); /* Control Limits - On or Off (forces blank line in right half-page) */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCONTROLLIMITS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0034B(); /* Collapse Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PCOLLAPSECUTOFF, Value, Val_ID);
   ViewPresetSetup0034A(); /* Absolute Cutoff - Distance or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PABSOLUTECUTOFF, Value, Val_ID);
   ViewPresetSetup0032(); /* Peak Power Cutoff - Percent or Off or N/A, indented */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPKPOWERCUTOFF, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   /* Right half-page */
   ViewPresetSetup0029(); /* Energy Compensation - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYCOMP, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0031(); /* Max. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENERGYMAX, Value, Val_ID);
   ViewPresetSetup0030(); /* Min. Energy - in Joules, indented */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PENGERGYMIN, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   /*---------------------------------- SystemViewPresetReport2------------------------ */
   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if ((DUPS_Info.DUPSFlag) && (ViewDupsPresent))
   {
      /* Print Digital UPS subheading */
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = DUPS_TXT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      /* Put blank line in right half-page */
      RightPrintYCoordinate += PrintLineHeight;

      /*--           *left half-page*           --*/
      /* Ramp Time */
      FormatVariables(CurrentViewPreset.DUPS_HostParamSet.WeldRampTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = DUPS_RAMPTIME_TXT;
      VGAPrintParam = PDUPSRAMPTIME;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PDUPSRAMPTIME, Value, Val_ID);

      /* Memory - On or Off */
      Value = (UINT8) DUPS_Info.DUPSMemFlag;
      ValueFlag = TRUE;
      Val_ID = DUPS_MEMRY_TXT;
      VGAPrintParam = PMEMORY;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PMEMORY, Value, Val_ID);

      /* Weld Status - On or Off */
      Value = (UINT8) CurrentViewPreset.WeldStatusFlag;
      ValueFlag = TRUE;
      Val_ID = WELDSTATUS_TXT;
      VGAPrintParam = PWELDSTATUS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDSTATUS, Value, Val_ID);

      /*--           *right half-page*           --*/
      /* Select - Name */
      PrintPresetName();
    
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSELECTNAME, Value, Val_ID);

      /* Seek Time */
      FormatVariables(CurrentPreset.DUPS_HostParamSet.SeekTime, TIME, VGAMisc, 6,
            CurrentSetup.Units);
      strcpy(VGABuffer, VGAMisc);
      Value = 0;
      ValueFlag = FALSE;
      Val_ID = SEEKTIME_TXT;
      VGAPrintParam = PSEEKTIME;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PSEEKTIME, Value, Val_ID);

      /* Timed Seek - On or Off */
      Value = DUPS_Info.DUPSSeekFlag;
      ValueFlag = TRUE;
      Val_ID = TIMEDSEEK_TXT;
      VGAPrintParam = PTIMEDSEEK;
      VGA_PresetSetup2(&AckBuf, VGABuffer, PTIMEDSEEK, Value, Val_ID);
   }
   /* Print Write In Fields for both Analog/Digital PS */
    /* WriteIn Field1 */
   strcpy(VGABuffer, CurrentViewPreset.WriteIn1);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD1_TXT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);

   /* WriteIn Field2 */
   strcpy(VGABuffer, CurrentViewPreset.WriteIn2);
   Value = 0;
   ValueFlag = FALSE;
   Val_ID = WRITEINFLD2_TXT;
   VGAPrintParam = PWRITEINFIELD;
   VGA_PresetSetup2(&AckBuf, VGABuffer, PWRITEINFIELD, Value, Val_ID);

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if (CurrentSetup.ControlLevel > LEVEL_t)
   { //only string is here.
      Value = 0;
      ValueFlag = TRUE;
      Val_ID = LIMITS_TXT;
      VGAPrintParam = ALWAYS;
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      AssignYCoordinate();
   }

   /* Left half-page */
   ViewPresetSetup0051(); /* Reject Limits - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJECTLIMITS, Value, Val_ID);
   ViewPresetSetup0052(); /* Reject Reset Required - On or Off */
   VGA_PresetSetup1(&AckBuf, VGABuffer, PREJRESETREQ, Value, Val_ID);

   /* Right half-page */
   ViewPresetSetup0035(); /* Suspect Limits - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPECTLIMITS, Value, Val_ID);
   ViewPresetSetup0036(); /* Suspect Reset Required - On or Off */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PSUSPRESETREQ, Value, Val_ID);

   /* left half-page */
   ViewPresetSetup0059(); /* display the + Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   ViewPresetSetup0060(); /* display the - Collapse R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   ViewPresetSetup0055(); /* display the + Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   ViewPresetSetup0056(); /* display the - Energy R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   ViewPresetSetup0061(); /* display the + Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   ViewPresetSetup0062(); /* display the - Absolute R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   ViewPresetSetup0057(); /* display the + Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   ViewPresetSetup0058(); /* display the - Power  R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   ViewPresetSetup0053(); /* display the + Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   ViewPresetSetup0054(); /* display the - Time   R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   ViewPresetSetup0065(); /* display the + Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   ViewPresetSetup0066(); /* display the - Weld Force R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LRMAXFORCE, Value, Val_ID);
   ViewPresetSetup0063(); /* display the + Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   ViewPresetSetup0064(); /* display the - Trigger Distance R Limit */
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);
   ViewPresetSetup0081();/*displays the + PMC Band Limit*/
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   ViewPresetSetup0082();/*displays the - PMC Band Limit*/
     VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   if (DUPS_Info.DUPSFlag && CurrentSetup.SBLEnable)
   {
      ViewPresetSetup0083(); /* display the +SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
      ViewPresetSetup0084(); /* display the -SBL Freq R Limit */
      VGA_PresetSetup1(&AckBuf, VGABuffer, ALWAYS, Value, Val_ID);
   }

   ViewPresetSetup0085();
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LDOWNSPEEDPLUS, Value, Val_ID);
   ViewPresetSetup0086();
   VGA_RejLimPresetSetup1(&AckBuf, VGABuffer, LDOWNSPEEDMINUS, Value, Val_ID);

   /* right half-page */
   ViewPresetSetup0043(); /* display the + Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEPLUS, Value, Val_ID);
   ViewPresetSetup0044(); /* display the - Collapse S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LCOLLAPSEMINUS, Value, Val_ID);
   ViewPresetSetup0039(); /* display the + Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYPLUS, Value, Val_ID);
   ViewPresetSetup0040(); /* display the - Energy S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LENERGYMINUS, Value, Val_ID);
   ViewPresetSetup0045(); /* display the + Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEPLUS, Value, Val_ID);
   ViewPresetSetup0046(); /* display the - Absolute S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LABSOLUTEMINUS, Value, Val_ID);
   ViewPresetSetup0041(); /* display the + Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERPLUS, Value, Val_ID);
   ViewPresetSetup0042(); /* display the - Power  S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LPOWERMINUS, Value, Val_ID);
   ViewPresetSetup0037(); /* display the + Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEPLUS, Value, Val_ID);
   ViewPresetSetup0038(); /* display the - Time   S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTIMEMINUS, Value, Val_ID);
   ViewPresetSetup0049(); /* display the + Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEPLUS, Value, Val_ID);
   ViewPresetSetup0050(); /* display the - Weld Force S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LMAXFORCEMINUS, Value, Val_ID);
   ViewPresetSetup0047(); /* display the + Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTPLUS, Value, Val_ID);
   ViewPresetSetup0048(); /* display the - Trigger Distance S Limit */
   VGA_SusLimPresetSetup2(&AckBuf, VGABuffer, LTRIGGERDISTMINUS, Value, Val_ID);

   /* left half-page */

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;
   RightPrintXCoordinate = RIGHT_SUB_XCOORDINATE;
   ViewPresetSetup0300(); /*Batch count*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNTENABLED, Value, Val_ID);
   ViewPresetSetup0301(); /*Batch count enabled*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNTENABLED, Value, Val_ID);
   ViewPresetSetup0302(); /*Count with alarm */
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBCOUNTWITHALARM, Value, Val_ID);
   ViewPresetSetup0303(); /*Reset to zero*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBCOUNTRESETTOZERO, Value, Val_ID);
   ViewPresetSetup0304(); /*Batch count value*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PBATCHCOUNT, Value, Val_ID);
   RightPrintXCoordinate = RIGHT_XCOORDINATE;

   LeftPrintXCoordinate = LEFT_SUB_XCOORDINATE;
   ViewPresetSetup0305(); /*Pressure limits*/
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMIT, Value, Val_ID);
   ViewPresetSetup0306();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMIT, Value, Val_ID);
   //ViewPresetSetup0307();
   PrintSetup0330();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMITPLUS, Value, Val_ID);
   PrintSetup0331();
   //ViewPresetSetup0308();
   VGA_PresetSetup2(&AckBuf, VGABuffer, PPRESSURELIMITMINUS, Value, Val_ID);
   LeftPrintXCoordinate = LEFT_XCOORDINATE;

   ViewPresetSetup0309(); /*Assembly number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PACTASSEMBLTNUM, Value, Val_ID);

   ViewPresetSetup0310(); /*P/S number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSASSEMBLYNUM, Value, Val_ID);

   ViewPresetSetup0311(); /*Stack number*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PPSTACKASSEMBLYNUM, Value, Val_ID);
   if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
	   ViewPresetSetup0012();//Rapid Traverse On/Off
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);

	   ViewPresetSetup0013();//Rapid Traverse Distance
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PRAPIDTRAVS, Value, Val_ID);


	   ViewPresetSetup0312(); /*Flow control*/
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PDOWNSPEED, Value, Val_ID);
   }

   param = ViewPresetSetup0313(); /*Validated/locked*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, param, Value, Val_ID);

   if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
	   ViewPresetSetup0319();
 	   VGA_PresetSetup1(&AckBuf, VGABuffer, PPRESETREV, Value, Val_ID);
   }
   if (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
    ViewPresetSetup0329(); /*Hold Pressure flag*/
	VGA_PresetSetup1(&AckBuf, VGABuffer, PHOLDPRESSURE, Value, Val_ID);

   ViewPresetSetup0315(); /*Hold Pressure*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PHOLDPRESSURE, Value, Val_ID);

   ViewPresetSetup0316(); /*Weld Pressure*/
   VGA_PresetSetup1(&AckBuf, VGABuffer, PWELDPRESSURE, Value, Val_ID);
   }

   AssignYCoordinate();
   LeftPrintYCoordinate += PrintLineHeight;
   RightPrintYCoordinate += PrintLineHeight;

   if (CurrentSetup.ControlLevel == LEVEL_c)
   {
	   //only string is here.
	   Value = 0;
	   ValueFlag = TRUE;
	   Val_ID = SETUPLIMIT_TXT;
	   VGAPrintParam = PSETUPLIMIT;
	   VGA_PresetSetup1(&AckBuf, 0, PSETUPLIMIT, Value, Val_ID);
	   AssignYCoordinate();

	   if(CurrentViewPreset.WeldMode == TIMEMODE)
	   {
		   ViewPresetSetup0326(); /* display the + WeldTime SetupLimitt */
	  	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	   ViewPresetSetup0341(); /* display the - WeldTime SetupLimitt */
	  	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   if(CurrentViewPreset.WeldMode == ENERGYMODE)
	   {
		   ViewPresetSetup0328(); /* display the + Weld Energy SetupLimitt */
	   	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   	   ViewPresetSetup0343(); /* display the - Weld Energy SetupLimitt */
	   	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   if(CurrentViewPreset.WeldMode == PKPOWERMODE)
	   {
		   ViewPresetSetup0330(); /* display the + Peak Power SetupLimitt */
	  	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	   ViewPresetSetup0344(); /* display the - Peak Power SetupLimitt */
	  	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   if(CurrentViewPreset.WeldMode == COLLAPSEMODE)
	   {
		   ViewPresetSetup0331(); /* display the + Collapse Distance SetupLimitt */
	   	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   	   ViewPresetSetup0345(); /* display the - Collapse Distance SetupLimitt */
	   	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   if(CurrentViewPreset.WeldMode == ABSOLUTEMODE)
	   {
		   ViewPresetSetup0332(); /* display the + Absolute Distance SetupLimitt */
	  	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	  	   ViewPresetSetup0346(); /* display the - Absolute Distance SetupLimitt */
	  	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   if(CurrentViewPreset.WeldMode == GRDDETECTMODE)
	   {
		   ViewPresetSetup0333(); /* display the + Scrub Time SetupLimitt */
	   	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   	   ViewPresetSetup0334(); /* display the + Scrub Amplitude SetupLimitt */
	   	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   	   ViewPresetSetup0347(); /* display the - Scrub Time SetupLimitt */
	   	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   	   ViewPresetSetup0348(); /* display the - Scrub Amplitude SetupLimitt */
	   	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   ViewPresetSetup0321(); /* display the + DownSpeed SetupLimitt */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0336(); /* display the - DownSpeed SetupLimitt */
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0320(); /* display the + Weldpressure SetupLimit */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0335(); /* display the - Weldpressure SetupLimit */
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0324(); /* display the + Amp A SetupLimitt */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0339(); /* display the - Amp A SetupLimitt */
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0323(); /* display the + HoldTime SetupLimitt */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0338(); /* display the - HoldTime SetupLimitt */
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0322(); /* display the + HoldPressure SetupLimitt */
	   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   ViewPresetSetup0337(); /* display the - HoldPressure SetupLimitt */
	   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   if(CurrentViewPreset.WeldTrigger)
	   {
		   ViewPresetSetup0327(); /* display the + Trigger Distance SetupLimitt */
		   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
		   ViewPresetSetup0342(); /* display the - Trigger Distance SetupLimitt */
		   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
	   else
	   {
		   ViewPresetSetup0325(); /* display the + TrigForce SetupLimitt */
		   VGA_PresetSetup1(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
		   ViewPresetSetup0340(); /* display the - TrigForce SetupLimitt */
		   VGA_PresetSetup2(&AckBuf, VGABuffer, PSETUPLIMIT, Value, Val_ID);
	   }
   }

   return (VGAPrintLength);

}


UINT16 ProcessUserIdData(UINT8 * AckBuf, UINT8* UserData, SINT32 Count)
{
   static SINT32 CountSent = 0 ;
   SINT32 DataLeft = 0;
   UINT8 * Address = NULL;
   UINT16 length = 0;
   UINT16 USERID_HEADER = 8;//8 byte Header + 4byte User Data Count
   Count = DATAINONEPACKET;

   if(FRAMUserIdObj.UserIDGlobalCount == 0 )
        SetDefaultUserData();

   if(CountSent >= FRAMUserIdObj.UserIDGlobalCount) // all the data send, so send 0 in count
   {
      CountSent = 0;
      *((UINT32*)(AckBuf+USERID_HEADER)) = 0; // write 0 in the 4bytes of count
      length += sizeof(UINT32);
   }
   else // Still more data to send
   {
	   if(CountSent != 0)
		   Address = UserData + (CountSent)*sizeof(UserID); // present address = past + data send
   		else
		   Address = UserData;
      if(CountSent <= (FRAMUserIdObj.UserIDGlobalCount - (SINT32)DATAINONEPACKET)) // if Global Count > 100, send 100 at a time
      {
         DataLeft = DATAINONEPACKET;
         memcpy((AckBuf+USERID_HEADER),&DataLeft,sizeof(UINT32));
         memcpy((AckBuf+USERID_HEADER+4),Address,sizeof(UserID)*DataLeft);
         length += sizeof(UserID)*DataLeft+sizeof(UINT32);
         CountSent = CountSent + DataLeft;
      }
      else // if Global count < 100, sent available data
      {
         DataLeft = (FRAMUserIdObj.UserIDGlobalCount - CountSent);
         memcpy((AckBuf+USERID_HEADER),&DataLeft,sizeof(UINT32));
         memcpy((AckBuf+USERID_HEADER+4),Address,sizeof(UserID)*DataLeft);
         length += sizeof(UserID)*DataLeft+sizeof(UINT32);
         CountSent = 0;
      }
   }
   return length;
}

UINT16 ProcessEventHistoryDataCommand(UINT8 * AckBuf, UINT32 LogsCount, UINT32 EventCounter)
/* this function prepares the response of the command that is sent by the SBC
 * It copies LogCount number of Event Log Entries starting with EventCounter Index in the FRAM Structure.
 *
 * @parameter Ackbuf : response buffer
 * @parameter LogCounts : Number of Logs that we need to send
 * @parameter EventCounter : Count from where we have to get the logs.
 *
 * @return Length : total count of bytes that we have packed in the AckBuf
 */
{
	UINT16 length = 0;
	UINT32 RecordCount = 0;
	UINT16 EVENTHISTORY_HEADER = ACKBUF_HEADER;//8 byte Header
#define ALARMDEBUG_ENABLE
#ifdef ALARMDEBUG_ENABLE
   if((LogsCount > MAX_EVENT_IN_ONE_PACKET)) {
   }
#endif

   if(LogsCount > FRAMEventHistoryObj.EventHistoryCount) //more than available data
      LogsCount = FRAMEventHistoryObj.EventHistoryCount;

   if(LogsCount > MAX_EVENT_IN_ONE_PACKET) //more than data that can be send in one packet
      LogsCount = MAX_EVENT_IN_ONE_PACKET;

   if(LogsCount > 0) { // copy whatever data you have asked for
      RecordCount = ReadEventHistory((Event_Log*)(AckBuf+EVENTHISTORY_HEADER+4),LogsCount,EventCounter);
      length+=RecordCount*sizeof(Event_Log);
   }
   memcpy((AckBuf+EVENTHISTORY_HEADER),&(RecordCount),sizeof(RecordCount)); //send the total count
   length+=sizeof(UINT32);
   return length;
}

UINT16 ProcessAlarmLogDataCommand(UINT8* AckBuf, UINT32 LogsCount, UINT32 AlarmCounter)
/* this function prepares the response of the command that is sent by the SBC
 * It copies LogCount number of Alarm Log Entries starting with AlarmCounter Index in the FRAM Structure.
 *
 * @parameter Ackbuf : response buffer
 * @parameter LogCounts : Number of Logs that we need to send
 * @parameter AlarmCounter : Count from where we have to get the logs.
 *
 * @return Length : total count of bytes that we have packed in the AckBuf
 */
{
   static AlarmLog locBuffer[MAX_ALARM_ENTRIES] = {};
   UINT32 length = 0;
   UINT16 ALARMLOG_HEADER = ACKBUF_HEADER;
   UINT32 ReadLogCount = 0;
   if(AlarmCounter == 0) { //First request from SBC
      ReadLogCount = ReadAlarmLog(locBuffer,(UINT32)MAX_ALARM_ENTRIES); // Read Alarm in Local Buffer
      if(LogsCount > FRAMAlarmLogObj.AlarmLogCount) //Check if requested data is more than total Available data
         LogsCount = FRAMAlarmLogObj.AlarmLogCount;

      memcpy((AckBuf+ALARMLOG_HEADER),&(FRAMAlarmLogObj.AlarmLogCount),sizeof(FRAMAlarmLogObj.AlarmLogCount)); //send the total count of Alarm Logs
      length+=sizeof(UINT32);
   }
   else if(AlarmCounter >= MAX_ALARM_ENTRIES)
   {
      LogsCount = 0;
      AlarmCounter = 0;
      memcpy((AckBuf+ALARMLOG_HEADER),&(LogsCount),sizeof(LogsCount)); //send the total count of Alarm Logs

   }
   else { //for rest of the data packet
      if(LogsCount > (FRAMAlarmLogObj.AlarmLogCount - AlarmCounter)){
         LogsCount = FRAMAlarmLogObj.AlarmLogCount - AlarmCounter;
      }
      memcpy((AckBuf+ALARMLOG_HEADER),&LogsCount,sizeof(LogsCount)); //send the total count of Alarm Logs
      length+=sizeof(UINT32);
   }

   if(LogsCount > 0) {
      memcpy((AckBuf+ALARMLOG_HEADER+4),locBuffer+AlarmCounter,LogsCount*sizeof(AlarmLog));
      length+=LogsCount*sizeof(AlarmLog);
   }
   return length;
}
