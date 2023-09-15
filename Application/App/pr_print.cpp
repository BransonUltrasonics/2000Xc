/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/pr_print.cpp_v   1.19   Nov 06 2017 15:02:54   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/pr_print.cpp_v  $
 * 
 *    Rev 1.19   Nov 06 2017 15:02:54   RJamloki
 * Applying updated for serial output port to micro c actuator and sunrise
 * 
 *    Rev 1.18   Oct 10 2017 12:52:08   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.17   29 Mar 2016 11:33:54   RJamloki
 * Removing 
 * define ASCIILENGTH 132
 * define SPACE 32
 * FormatDataLine
 * FOR SUNRISE V12.1S
 * 
 *    Rev 1.16   22 Mar 2016 14:14:46   RJamloki
 * Added function to format the serial output for the special software
 * 
 *    Rev 1.15   16 Apr 2015 07:26:56   rjamloki
 * Fix for Coverity issue 12535
 * 
 *    Rev 1.14   08 Apr 2015 13:44:52   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.13   28 Nov 2014 07:39:08   rjamloki
 * Removed unused function defination FormatDataLine();
 * 
 *    Rev 1.12   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.11   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   07 Aug 2014 15:51:40   tayars
 * Changed variable name for downspeed.
 * 
 *    Rev 1.9   28 Jul 2014 12:40:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.8   09 Jul 2014 11:17:38   rjamloki
 * Menu4.h removed.
 * 
 *    Rev 1.7   11 Jun 2014 12:00:36   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:34:52   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:48   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: pr_print.c
 ---------------------------- DESCRIPTION ----------------------------------**/
#include <stdlib.h>
#include "graphs.h"
#include "string.h"
#include "weld_obj.h"
#include "util.h"
#include "ticks.h"
#include "keypad.h"
#include "selctkey.h"
#include "battram.h"
#include "menu7a.h"
#include "alarms.h"
#include "menu.h"
#include "dups_api.h"
#include "rtclock.h"
#include "stdio.h"

#define EMPTYLINESATBOTTOM 3
#define ALARMMESS 0
#define NOTEMESS  1

#define POSBUFFERLEN 11
#define POSITIONMULTIPLIER 30.0
#define INCREMENTSPERINCH 57.0
#define DECIPOINTSPERINCH 720.0
#define COMMANDLEN 10
#define RASTERLEN 53

/**-------------------------EXTERNAL DATA------------------------------------**/

extern UINT16         VGATickmarks[];
extern UINT16         VGATickInfo[];
extern WELD_OBJECT    *MsPointer;

/**-------------------------LOCAL GLOBAL DATA---------------------------------**/
struct SummaryStruct SummaryInfo  = {1,0,1,4};
#define GRAPH_LENGTH  402
#define HASH_MARK 40
#define TICKMARKS 6
#define HS_GRAPHHEIGHT 136                /* 136 pixels from rail to rail */

UINT16    Tickmarks[TICKMARKS];
UINT16    LineLength  = LINE135;
UINT32    UILines     = 0;                /*--  Line counter, every CR increments      --*/
UINT32    UIAlarms    = 0;                /*--  Number of Alarms                       --*/
SINT32    SizeToPtr   = 0;                /*--  weldHistory variable                   --*/ 
SINT32    AddrFram = 0;                /*--  weldHistory variable                   --*/ 
SINT32    bytecount   = 0, checkcount= 0; /*--  counter variables                      --*/ 
UINT8     *PUCLine;                       /*--  pointer to 1 line data array           --*/ 
SINT8     DateString[DATESIZE];           /*--  Stores the date section of 1 line data --*/ 
UINT8     *FramHistoryPtr;             /*--  pointer to BATTRAM                     --*/ 
UINT16    NumSize = 0;                    /*--  no. of of weldhisory records up to cur.--*/ 
UINT16    HistoryActive = FALSE;          /*--  Printing weld History                  --*/ 
UINT16    InitPrinterOnceOnPowerup = TRUE;/*--  TRUE: Printer init. once               --*/ 
UINT16    ColdStartDone = FALSE;          /*--  FALSE: cold start not done             --*/ 
UINT16    CheckUnitChanged = FALSE;       /*--  FALSE: unit was not changed            --*/ 
UINT16    PresetCheck = 0;                /*--  Check if preset was changed            --*/ 
UINT16    ResetCounterCheck = 0;          /*--  Check if preset was changed            --*/ 
double    TempValue , TempValue2;         /*--  Both used to cal.Ticks marks           --*/
WELD_DATA TotalResults[HISTORYDATA];      /*--  Store 50 weldhistory data              --*/ 
UINT8     TickMarkerLine[FIELD_LENGTH+1]; /*--  buffer line of the graph printing      --*/ 
SINT32    WeldCounter;                    /*--  Counts the weld cycles        --*/
UINT16    TempPrinter = SINTINEL;         /*--  temp printer type: 0 = epson, 1 = ibm, 3 = sentinal --*/
UINT16    CheckPageSizeFlag = FALSE;      /*--  TRUE: Page size was changed            --*/
UINT16    PrintCPIMode;                   /*-- CPI12 = 12 cpi, CPI10, CPI17            --*/
UINT16    TempCPIMode;                    /*-- CPI12(1)  = 12 cpi, CPI10(0), CPI17(2)  --*/
                                          /*-- (100) sentinel value                    --*/
UINT16    PrinterType;                    /*--  Epson, IBM pro etc.                    --*/
//UINT16    WeldOnceOnPowerup = TRUE;       /*--  TRUE: reset WeldsPerPage               --*/
WELD_DATA TempFinalResults;
SINT16    HistoryPageCt;
UINT16    LastHistoryCycle;
WELD_DATA *PrintFinalPtr;
WELD_DATA *LastPrintResultPtr;
BOOLEAN   IsThereAGraphPrinting = FALSE;
BOOLEAN   ActuatorChanged = FALSE;
UINT16    testAlarm;
UINT32    TempUIAlarms = 0;  /*--  temp storage for the number of Alarms                       --*/
UINT16    ShouldWeFormfeedFirst;
UINT16    GraphCurrentlySelected;
UINT16    mytest;
UINT8     UCLine[FIELD_LENGTH+1]; /*--  buffer line of the graph printing--*/
WELD_DATA TestResults;

/**-------------------------------------------------------------------------------------**/




void VGAPrepTickMarks(void)
{
   UINT16 index;
   UINT16 TickMarkIndex     = 0;                /*--  index position on graph line           --*/  
   UINT16 TriggerOffset;
   TempValue = 400.0 / (double)UIHmaxlabel;
   
   /*-- save tick marks for bottom of graph --*/
   for(index=0; index < TICKMARKS; index++)
      VGATickmarks[index] = 0;

   if (CurrentSetup.HandHeld == FALSE) {       /* Only print this tick mark if no handheld */
      TickMarkIndex = ((double)PRETRIGMAXLIM * TempValue);
      if(TickMarkIndex < ENDGRAPH)         
         VGATickmarks[TICKTRIG] = TickMarkIndex;      
      TriggerOffset = PRETRIGMAXLIM;
      VGATickInfo[TICKTRIG] = 0;     // Trigger starts at 0 sec
   }
   else {
      TriggerOffset = 0;
      VGATickInfo[TICKTRIG] = 0xFFFE;  // Show the trigger value as OFF
   }
   /*-- If there were no alarm print tick mark --*/
   if(CurrentSetup.ControlLevel >= LEVEL_ea){
      if((PrintFinalPtr->PSActControlFlags & BIT1) == BIT1){ /* STEP */
         if(!(MsPointer->PrintBottomFlags & AMPSTEPALARMMASK)){
            TickMarkIndex = (((double)(MsPointer->AmpStepAtTime + TriggerOffset)) * TempValue);
            if(TickMarkIndex < ENDGRAPH)         
               VGATickmarks[TICKAMP] = TickMarkIndex;
            VGATickInfo[TICKAMP] = (UINT16)MsPointer->AmpStepAtTime;         
         }
         else
            VGATickInfo[TICKAMP] = 0xFFFD;
      }
      else
         VGATickInfo[TICKAMP] = 0xFFFE;
   }
   else
      VGATickInfo[TICKAMP] = 0xFFFF; 
   
   if((CurrentSetup.ControlLevel == LEVEL_c || CurrentSetup.ControlLevel == LEVEL_TEST)
      && (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)){
      if((PrintFinalPtr->PSActControlFlags & BIT4) == BIT4){
         if(!(MsPointer->PrintBottomFlags & PRESSURESTEPALARMMASK)){
            TickMarkIndex = (((double)(MsPointer->PressureStepAtTime + TriggerOffset)) * TempValue);
            if(TickMarkIndex < ENDGRAPH)
               VGATickmarks[TICKPRESSURE] = TickMarkIndex;
            VGATickInfo[TICKPRESSURE] = (UINT16)MsPointer->PressureStepAtTime;
         }
         else
            VGATickInfo[TICKPRESSURE] = 0xFFFD;
      }
      else
         VGATickInfo[TICKPRESSURE] = 0xFFFE;
   }
   else
      VGATickInfo[TICKPRESSURE] = 0xFFFF;


   if(PrintFinalPtr->ActualWeldTime){
      TickMarkIndex = (((double)(PrintFinalPtr->ActualWeldTime + TriggerOffset)) * TempValue);
      if(TickMarkIndex < ENDGRAPH)         
         VGATickmarks[TICKSONIC] = TickMarkIndex;
      VGATickInfo[TICKSONIC] = (UINT16)PrintFinalPtr->ActualWeldTime;         
   }
   else
      VGATickInfo[TICKSONIC] = 0xFFFE;


   if((MsPointer->HoldEndAtTime != PrintFinalPtr->ActualWeldTime)){
      if(!(MsPointer->PrintBottomFlags & HOLDALARMMASK)){
         TickMarkIndex = (((double)(MsPointer->HoldEndAtTime + TriggerOffset)) * TempValue);
         if(TickMarkIndex < ENDGRAPH)            
            VGATickmarks[TICKHOLD] = TickMarkIndex; 
         VGATickInfo[TICKHOLD] = (UINT16)MsPointer->HoldEndAtTime;           
      }
      else
         VGATickInfo[TICKHOLD] = 0xFFFD;
   }
   else
      VGATickInfo[TICKHOLD] = 0xFFFE;
   

   if(MsPointer->SeekEndAtTime != 0){
     /*-- 1300ms is the delay time for seek and 10ms is minimum holdtime--*/
      if(!(MsPointer->PrintBottomFlags & SEEKALARMMASK)){
         TickMarkIndex = (((double)(MsPointer->SeekEndAtTime + TriggerOffset)) * TempValue);
         if(TickMarkIndex < ENDGRAPH)            
            VGATickmarks[TICKSEEK] = TickMarkIndex;         
         VGATickInfo[TICKSEEK] = (UINT16)MsPointer->SeekEndAtTime;           
      }
      else
         VGATickInfo[TICKSEEK] = 0xFFFD;
   }
   else
      VGATickInfo[TICKSEEK] = 0xFFFE;

   if((RunningPreset.WeldMode==GRDDETECTMODE)&&(MsPointer->ScrubStartAtTime)){
      TickMarkIndex = (((double)(MsPointer->ScrubStartAtTime + TriggerOffset)) * TempValue);
      if(TickMarkIndex < ENDGRAPH)
         VGATickmarks[TICKSCRUB] = TickMarkIndex;
      VGATickInfo[TICKSCRUB] = (UINT16)MsPointer->ScrubStartAtTime;//Coverity-12535
   }
   else
   {
      VGATickmarks[TICKSCRUB] = 0;
      VGATickInfo[TICKSEEK] = 0xFFFE;
   }
}


void GetLastWeldData( WELD_DATA *Results )
/****************************************************************************/
/*                                                                          */
/* Fetches the last weld's data from the history buffer, copies to          */
/* "Results".                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT8  *NextWeld, *LastWeld;

   /*-- Calculate where Weld History starts in FRAM --*/
   NextWeld = (UINT8 *)(FRAM1200_HISTORY_START);

   /*-- Get the last data position --*/
   if (((UINT8*)CurrentSetup.WeldHistoryPtr) != NextWeld)
      LastWeld = (((UINT8*)CurrentSetup.WeldHistoryPtr) - (sizeof(WELD_DATA)));
   else
      LastWeld = NextWeld + ((HISTORYDATA-1) * sizeof(WELD_DATA));

   /*--  Instantly copy last cycle weld results --*/ 
   memcpy( Results, LastWeld, (sizeof(WELD_DATA)));

   /*-- Always print time mode after cold start --*/
   /*-- Also print 0 for Amp A and Amp B        --*/
   if(!Results->CycleCount){
      Results->Weldmode = TIMEMODE;
      Results->PSActControlFlags |= (BIT0 | BIT1 | BIT2);
      Results->ActualAmplitudeStart = 0;
      Results->ActualAmplitudeEnd = 0;
   }
}

