/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/runresults.cpp_v   1.32   Oct 10 2017 13:34:20   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/runresults.cpp_v  $
 * 
 *    Rev 1.32   Oct 10 2017 13:34:20   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.31   08 Apr 2015 13:46:06   AnPawar
 * Pressure A and Pressure B column added in weld results.
 * 
 *    Rev 1.30   01 Apr 2015 13:02:26   amaurya
 * change in function GetBatchCountInfo() to not display batch count on runresults screen if it is disabled.
 * 
 *    Rev 1.29   27 Mar 2015 11:10:28   amaurya
 * HoldForceMax changed to HoldForceEnd as per code review comment.
 * 
 *    Rev 1.28   30 Jan 2015 08:10:56   amaurya
 * GetUnit_Values() changed to send "___" in weldresult when hold time is disabled.
 * 
 *    Rev 1.27   09 Jan 2015 10:06:36   rjamloki
 * change in function GetUnit_Values() pressure format changed to pressure2
 * 
 *    Rev 1.26   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.25   02 Jan 2015 04:09:34   rjamloki
 * GetBatchCountInfo() function changed to display batch count in reverse order
 * 
 *    Rev 1.24   11 Dec 2014 08:37:14   AnPawar
 * sending ps sn and act sn id and string with weld data.
 * 
 *    Rev 1.23   28 Nov 2014 07:40:14   rjamloki
 * PollingCommandCounter variable moved to the structure FramVerInfo.
 * 
 *    Rev 1.22   11 Nov 2014 06:09:34   AnPawar
 * Removed Extra event as batch count clear event is parameter change event
 * 
 *    Rev 1.21   10 Nov 2014 04:57:26   AnPawar
 * Removed event from ClearCurrentBatchCount() function
 * 
 *    Rev 1.20   20 Oct 2014 06:26:36   AnPawar
 * define changed.GetUnit_Values() function changed
 * 
 *    Rev 1.19   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.18   11 Sep 2014 11:04:58   rjamloki
 * Added batch count clear event and coverity fixes
 * 
 *    Rev 1.17   05 Sep 2014 05:11:54   rjamloki
 * ClearBatchCount function change to update weldcount in preset info 
 * 
 *    Rev 1.16   22 Aug 2014 07:02:32   rjamloki
 * Hold force addition in run result format function
 * 
 *    Rev 1.15   18 Aug 2014 01:36:06   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.14   07 Aug 2014 15:51:38   tayars
 * Changed variable name for downspeed.
 * 
 *    Rev 1.13   28 Jul 2014 12:51:36   rjamloki
 * udi scan added in run results , user name is replaced with user id
 * 
 *    Rev 1.12   09 Jul 2014 11:31:52   rjamloki
 * Added Batch Count support.
 * 
 *    Rev 1.11   11 Jun 2014 12:07:50   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   27 May 2014 18:35:02   rjamloki
 * Fillied Dummy values for for Preset revision and and validation for weld history columns.
 * 
 *    Rev 1.9   27 May 2014 10:14:18   amaurya
 * Added mandatory colums in weld history
 * 
 *    Rev 1.8   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 03:37:38   rjamloki
 * extern variables clean up and coverity fixes
 * 
 *    Rev 1.6   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:42   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:52   rjamloki
 * Preset changes to support 1000 preset.
 *
 *    Rev 1.3   03 Jan 2014 08:45:50   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: runresults.c

      Written by: JOY 
            Date: 04/28/2003 
        Language: "C"
 ------------------------------- DESCRIPTION ---------------------------------

 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "string.h"
#include "menu.h"
#include "menu1.h"
#include "menu3.h"
#include "menu5.h"
#include "preset.h"
#include "prsetprn.h"
#include "display.h"
#include "dups_api.h"
#include "weld_obj.h"
#include "battram.h"
#include "graphs.h"
#include "sc.h"
#include "portable.h"
#include "ticks.h"
#include "genalarm.h"
#include "digout.h"
#include "statedrv.h"
#include "command.h"
#include "param.h" 
#include "menu7a.h"
#include "serial.h"
#include "stdio.h"
#include "preset.h"
#include "selctkey.h"
#include "Events.h"

#define MAX_RUN_RESULT_PARAM     5
#define UNIT   0
#define MAX_RUNSCREEN_CYCLES 7
#define EXIT_HD 1
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                         (scope is global to THIS file)
*/
static WELD_DATA LastRunResults;
/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES -------------------------
*/
void GetCurrentPresetNames(void);
void SetRunScreenParam(void);
void GetBatchCountInfo();
void ClearCurrentBatchCount();
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void VGAAlarmReset (UINT32 dummy);
void CalibFinalCleanup(void);
void VGAExitTestSequence(void);
void ExitMenuAndEnableWeld(void);
void CheckforCalib(void);
void VGAProcessHornDownMsg (void);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT32 SWConfiguration;
extern UINT32 HWConfiguration;
extern SINT32 SecurityLevel;
extern BOOLEAN VGAHornDown;
extern BIT_FLAGS BitFlags;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN VGACalAllowed;
extern BOOLEAN VGASnsrCalibAllowed;
extern BOOLEAN VGAAbortHornScan;
extern BOOLEAN StateMachineDisabled;
extern BOOLEAN VGAHistoryData;
extern UINT8 PrevHornState;

extern UINT16 VGAAction;
extern UINT16 DiagFlag;


extern STR StrWeldStateLine[VGA_LINESIZE];

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

#define MAX_RUN_PARAMS 33
MENUEND RunMenuEnd = { TRUE };

const SINT8 tokenChars[] = "()=";
UINT16 TotalCycle;
BOOLEAN AllParamColumnFlag;
UINT16 CalibInProgress = FALSE;
//SINT32 MaxNoOfCycles = 50;
//SINT32 MinNoOfCycles = 1;
UINT8 RunParameter[MAX_RUN_PARAMS];

/*----------------------------------Menu Structures---------------------------
*/ 

STR CurrentPresetName[VGA_LINESIZE];
STR PresetNameBuffer[VGA_LINESIZE];
STR BatchCountInfo[VGA_LINESIZE];
void GetCurrentPresetNames(void)
/****************************************************************************/
/*Description:-                                                             */
/* Generate Current Preset name from the Preset ID, this Preset name is     */
/* displayed in the WELD_RESULT_SCREEN                                      */
/****************************************************************************/
{
   UINT8 ValidPreset = TRUE;
   UINT16 i;

   if(CurrentPreset.PresetID[0] != 0)
   {
      for(i = 0; i < PRESETLEN && ValidPreset; i++)
      {
         if(CurrentPreset.PresetID[i] != 0)
         {
            if(!ValidPresetCharacter(CurrentPreset.PresetID[i]))
            {
               ValidPreset =  FALSE;
               CurrentPreset.PresetID[0] = NULL; /* Invalid Name, Clear Name */
               CurrentPreset.PresetID[1] = NULL; 
            }
         }
         else
            ValidPreset = FALSE; /* Terminate Loop, Preset Valid */
      }
   }
    strcpy(PresetNameBuffer, CurrentPreset.PresetID);
    if(CurrentPreset.PresetUpdateComplete == FALSE)
       strcat(PresetNameBuffer, "*");
    strcpy(CurrentPresetName,PresetNameBuffer);
}

void GetUnit_Values(SINT8 StrUnit_Value[], UINT16 Param,WELD_DATA * ResPtr)
/****************************************************************************/
/*Description:-                                                             */
/* Populates Weld Parameter Value and Unit in the input string variable     */
/*Input Parameters:-                                                        */
/* Param  : Weld Parameter                                                  */
/* Flag   : Indicates whether Unit/Value of the weld parameter needs to be  */
/*          populated in the input String variable (StrUnit_Value)          */
/****************************************************************************/
{
   SINT32 TempWeldTime;   
   switch ( Param )
   {
      case RCYCLECOUNT:
          if(BitFlags.Cyclebit)
		 {
			if(CurrentPreset.WeldMode != CONTINUOUSMODE)
			   FormatVariables( ResPtr->CycleCount, COUNTER,
								StrUnit_Value, LINESIZE, CurrentSetup.Units );
			else
			   strcpy(StrUnit_Value, "\x00");
		 }
		 else
			strcpy(StrUnit_Value, "\x00");

         break;
         
      case RPRESETNUM:

		 if(BitFlags.PresetNum)
		 {
			FormatVariables( ResPtr->PresetNum, COUNTER,
				   StrUnit_Value, LINESIZE, CurrentSetup.Units );
		 }

		 else
		   strcpy(StrUnit_Value, "\x00");

         break;
         
      case RTIME:
            if(BitFlags.Timebit)
            {
               if(CurrentPreset.WeldMode != CONTINUOUSMODE)
               {
                  TempWeldTime = ResPtr->ActualWeldTime;

                  if (TempWeldTime < 0)  /* Just in case weld time less than 0 */
                     TempWeldTime = 0;   

                  FormatVariables( TempWeldTime, TIME, StrUnit_Value, LINESIZE,
                        CurrentSetup.Units );
                }
                else
                   strcpy(StrUnit_Value, "\x00");
            }
            else
               strcpy(StrUnit_Value, "\x00");
         break;
         
         case RPKPWR:
               if(BitFlags.PkPwrbit)
                  FormatVariables( ResPtr->PeakPower, PERCENTX10,
                         StrUnit_Value, LINESIZE, CurrentSetup.Units );            
               else
                 strcpy(StrUnit_Value, "\x00");
            break;
            
         case RENERGY:
                if(BitFlags.Energybit)
                {
                   if(CurrentPreset.WeldMode != CONTINUOUSMODE)
                   {
                      if(ResPtr->TotalEnergy < 10000)
                         FormatVariables( ResPtr->TotalEnergy, ENERGY,
                            StrUnit_Value, LINESIZE, CurrentSetup.Units );
                      else
                         FormatVariables( ResPtr->TotalEnergy, ENERGYDIV10,
                                   StrUnit_Value, LINESIZE, CurrentSetup.Units );
                    }
                    else
                       strcpy(StrUnit_Value, "\x00");
                 }
                 else
                    strcpy(StrUnit_Value, "\x00");
            break;
             
         case RVELOCITY_AED:
         case RVELOCITY_AEF:
               if((CurrentSetup.Actuator == AED) ||
                   (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)                  
                     FormatVariables( ResPtr->ActualDownspeed, VELOCITY,
                                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break;
             
         case RWABSDIST:
               if(BitFlags.WeldAbsbit)               
                  FormatVariables( ResPtr->ActualWeldAbs, DISTANCE,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RTABSDIST:
               if(BitFlags.Absbit)              
                  FormatVariables( ResPtr->ActualTotalAbs, DISTANCE,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
            break;
             
         case RWCOLDIST:
               if(BitFlags.WeldCollbit)
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)            
                     FormatVariables( ResPtr->ActualWeldCollapse, DISTANCE,
                                      StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RTCOLDIST:
               if(BitFlags.TtlCollbit)
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)                 
                    FormatVariables( ResPtr->ActualTotalCollapse, DISTANCE,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RAMPSTART:
               if(BitFlags.AmpAbit)
               {
                  if(!(ResPtr->PSActControlFlags & BIT0))/* If external amplitude, use */
                  {                                         /* canned string. */
                     strcpy(StrUnit_Value, "\x00");
                  }
                  else
                  {
                     if((CurrentSetup.ControlLevel < LEVEL_ea) || (!(ResPtr->PSActControlFlags & BIT1)))
                     {
                        strcpy(StrUnit_Value, "\x00");        /* Don't say "Amp A" if stepping */
                     }
                    if(RunningPreset.WeldMode != CONTINUOUSMODE)
                       FormatVariables( ResPtr->ActualAmplitudeStart,
                                       PERCENT, StrUnit_Value, LINESIZE, CurrentSetup.Units );
                    else
                       strcpy(StrUnit_Value, "\x00");
               
                  }
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RAMPEND:
               if(BitFlags.AmpBbit)
               {
                  if((RunningPreset.WeldMode != CONTINUOUSMODE) &&
                     ((ResPtr->PSActControlFlags & (BIT1 | BIT0)) == (BIT1 | BIT0))){
                     FormatVariables( ResPtr->ActualAmplitudeEnd, PERCENT,
                          StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  }
                  else
                    strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RPRESSUREA:
               if (BitFlags.SetPAbit) {
                  if ((RunningPreset.WeldMode != CONTINUOUSMODE)
                        && (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC))
                     FormatVariables(ResPtr->SetPressureA, PRESSURE2, StrUnit_Value,
                           LINESIZE, CurrentSetup.Units);
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RPRESSUREB:
               if (BitFlags.SetPBbit) {
                  if ((RunningPreset.WeldMode != CONTINUOUSMODE)
                        && ((ResPtr->PSActControlFlags & BIT4) == BIT4)
                        && (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC))
                     FormatVariables(ResPtr->SetPressureB, PRESSURE2, StrUnit_Value,
                           LINESIZE, CurrentSetup.Units);
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RFORCE:
               if(BitFlags.SetFEndbit)
               {
                  if ( (RunningPreset.WeldMode != CONTINUOUSMODE) && 
                       ( (CurrentSetup.Actuator == AED) ||
                         (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)) )
                  {
                     FormatVariables( ResPtr->WeldForceEnd,
                               FORCE, StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  }
                  else
                     strcpy(StrUnit_Value, "\x00");
               }
               else
                  strcpy(StrUnit_Value, "\x00");
            break;
            
         case RSYSPRESS:
               if(BitFlags.Pressbit)              
                  FormatVariables( ResPtr->WeldPressure, PRESSURE2,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RFREQMIN:
               if(BitFlags.FreqMinbit)               
                  FormatVariables( ResPtr->FrequencyMin, FREQUENCY,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );            
               else
                   strcpy(StrUnit_Value, "\x00");
            break; 
            
         case RFREQMAX:
               if(BitFlags.FreqMaxbit)         
                   FormatVariables( ResPtr->FrequencyMax, FREQUENCY,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
           break; 
           
         case RFREQSTART:
               if(BitFlags.FreqStartbit)        
                  FormatVariables( ResPtr->ActualFreqStart, FREQUENCY,
                                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
           break;
           
         case RFREQEND:
                if(BitFlags.FreqEndbit)               
                   FormatVariables( ResPtr->ActualFreqEnd, FREQUENCY,
                   StrUnit_Value, LINESIZE, CurrentSetup.Units );            
                else
                   strcpy(StrUnit_Value, "\x00");
           break;
           
         case RFREQCHG:
               if(BitFlags.FreqChgbit)
                  FormatVariables( ResPtr->FrequencyChange, FREQOFFSET,
                  StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, "\x00");
           break; 
           
         case RCYCLETIME:
            TempWeldTime = ResPtr->CycleTimeResult;
            if (TempWeldTime < 0)  /* Just in case weld time less than 0 */
               TempWeldTime = 0;   

            FormatVariables( TempWeldTime, TIME, StrUnit_Value, LINESIZE,
                  CurrentSetup.Units );
            break;
         case RUSERID:
			if(BitFlags.UserId)
			{
				strncpy(StrUnit_Value,(SINT8*) ResPtr->UserId, sizeof(ResPtr->UserId));
			}
			else
			   strcpy(StrUnit_Value, "\x00");

		  break;
      	 case RUDISCAN:
			if(BitFlags.UdiScan)
			{
				strncpy(StrUnit_Value,(SINT8*) ResPtr->UDIScan,sizeof(ResPtr->UDIScan));
			}
			else
				strcpy(StrUnit_Value, "\x00");
      		 break;
      	 case RPRESETREV:
			if(BitFlags.PresetRev)
			{
				sprintf(StrUnit_Value,"%ld",ResPtr->PresetRev);
			}
			else
				strcpy(StrUnit_Value, "\x00");

      		break;
      	 case RPRESETVALIDATED:
			if(BitFlags.PresetValidated)
			{
				if(ResPtr->PresetValidated)
					strcpy(StrUnit_Value, "Yes");
				else
					strcpy(StrUnit_Value, "No");
			}
			else
				strcpy(StrUnit_Value, "\x00");

      		break;
      	 case RACTASSEMBLYNUM:
      		if(BitFlags.ActAssemblyNum)
			{
				strncpy(StrUnit_Value,(SINT8*) ResPtr->ActAssemblyNum, sizeof(ResPtr->ActAssemblyNum));
			}
			else
				strcpy(StrUnit_Value, "\x00");

      		break;
      	 case RPSASSEMBLYNUM:

			if(BitFlags.PsAssemblyNum)
			{
				strncpy(StrUnit_Value, (SINT8*)ResPtr->PSAssemblyNum, sizeof(ResPtr->PSAssemblyNum));
			}
			else
				strcpy(StrUnit_Value, "\x00");

      		break;
      	 case RSTACKASSEMBLYNUM:

			if(BitFlags.StackAssemblyNum)
			{
				strncpy(StrUnit_Value,(SINT8*) ResPtr->StackAssemblyNum, sizeof(ResPtr->StackAssemblyNum));
			}
			else
				strcpy(StrUnit_Value, "\x00");


      		break;
      	 case RHOLDFORCEMAX:
      		 if(BitFlags.HoldForceMax)
      	     {
      			 if ( (RunningPreset.WeldMode != CONTINUOUSMODE) &&
      	            ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == MICRO)) &&
      	            ( (ResPtr->PSActControlFlags & BIT5) == BIT5))//Was hold time enabled during cycle
      	            {
      				 	 FormatVariables( ResPtr->HoldForceEnd,
      	                  FORCE, StrUnit_Value, LINESIZE, CurrentSetup.Units );
      	            }
      	        else
      	        	strcpy(StrUnit_Value, "\x00");
      	     }
      	    else
      	    	strcpy(StrUnit_Value, "\x00");
      	     break;
         default:
            strcpy(StrUnit_Value, "\x00");
           break; 
             
      }  
} 

void SetRunScreenParam(void)
/****************************************************************************/
/*Description:-                                                             */
/* Sets Run screen parameters                                               */
/****************************************************************************/
{
   TotalCycle = MAX_RUNSCREEN_CYCLES;
   AllParamColumnFlag = FALSE;
   VGAHistoryData = FALSE;

}

UINT8 GetVGAPresetNameHeader(WELD_DATA *ResultsPtr, SINT8* HeaderLine)
/*--------------------------------------------*
 * Prpare the Preset Header string to display *
 * WeldMode,PresetNum & PresetName.           *
 *--------------------------------------------*/ 
{
   UINT8  VGAWeldMode;

   switch(ResultsPtr->Weldmode)
   {  /* Get the weld mode string.  */
      case TIMEMODE:
         VGAWeldMode = 1;
         break;
         
      case ENERGYMODE:
         VGAWeldMode = 2;
         break;
         
      case PKPOWERMODE:
         VGAWeldMode = 3;
         break;
         
      case COLLAPSEMODE:
         VGAWeldMode = 4;
         break;
         
      case ABSOLUTEMODE:
         VGAWeldMode = 5;
         break;
         
      case GRDDETECTMODE:
         VGAWeldMode = 6;
         break;
         
      case CONTINUOUSMODE:
         VGAWeldMode = 7;
         break;
         
      default:
         VGAWeldMode = 1;
         break;   
   }
   strcpy(HeaderLine, ResultsPtr->PresetName);
   return (VGAWeldMode);
}

UINT16 CountActiveParameters(MENU list[])
{
   UINT16 index = 0;
   UINT16 MenuIndex = 0;
   UINT16 HMaxIndex = -1;
   BOOLEAN SkipFlag;
   RSPARAMETER *menu30;

   while (list[index].type != ENDLIST)
   {
      SkipFlag = FALSE;
      menu30 = (RSPARAMETER *)list[index].ptr;

      if (CurrentSetup.ControlLevel < menu30->CtrlLevel)
         SkipFlag = TRUE;
      else if (!(menu30->act & CurrentSetup.Actuator))
         SkipFlag = TRUE;
      else if ((CurrentPreset.WeldMode != (menu30->mode & CurrentPreset.WeldMode)) &&
         (menu30->mode != ALLMODES)) SkipFlag = TRUE;
      else if ((menu30->Mask1!=0)  && ((menu30->Mask1 & menu30->Cond1)!= (HWConfiguration & menu30->Mask1)))
         SkipFlag = TRUE;
      else if ((menu30->Mask2!=0)  && ((menu30->Mask2 & menu30->Cond2)!= (SWConfiguration & menu30->Mask2)))
         SkipFlag = TRUE;
      else if (menu30->level > SecurityLevel) SkipFlag = TRUE;

      SetOneLineDataBit(menu30->Index, SkipFlag);
      HMaxIndex++;
      RunParameter[MenuIndex]= menu30->Index;
      MenuIndex++;
      index++;
   }
   return (HMaxIndex);
}

UINT16 WeldParams(UINT8  * *Response, UINT16 WeldCount, BOOLEAN ParamFlag)
/****************************************************************************/
/*Description:-                                                             */
/* Send VGARunScreen Object Line parameters                                 */
/* WeldCount - Number of weld cycle data to be sent                         */
/* ParamFlag - True if all weld parameters requested                        */
/* Returns length of the Runscreen object                                   */
/****************************************************************************/
{
   UINT8 *HistoryStart;
   UINT8 *NextHistoryPtr;
   UINT8 *SaveHistoryPtr;
   SINT8 Str[VGA_LINESIZE];
   STR *StrTemp;
   UINT8 Index1 = 0;
   signed char Index2;
   UINT16 length = 0;
   UINT8 ParamNos;
   UINT8 i;
   SINT8 StrParam[LINELEN*2];
   UINT16 ScrollItems;

   for(Index2 = 0; (Index2 < VGA_LINESIZE - 2); Index2++)
      Str[Index2] = FILLCHAR;
   Str[VGA_LINESIZE-1] = 0;
   Str[VGA_LINESIZE-2] = 0;        

   ScrollItems = CountActiveParameters((MENU*)RunScreenParamMenu);
   if (ParamFlag)
   {
      ParamNos = ScrollItems + 1; 
      if ( (CurrentSetup.ControlLevel >= LEVEL_d) &&
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
			 (CurrentSetup.Actuator == MICROC) ||
            ( CurrentSetup.Actuator == AES) ) )
         length += AddToBuffer(Response, ParamNos + 3);//+3 for Hold Force, Ps serial number and Act Serial number
      else//for AE PS serial number is valid
         length += AddToBuffer(Response, ParamNos + 1 );//+1 for ps serial number
      
      for (Index2 = 0; Index2 < ScrollItems+1; Index2++)   
      {
         length += AddToBuffer(Response, (UINT8)(RunParameter[Index2]));
      }
      if ( (CurrentSetup.ControlLevel >= LEVEL_d) && 
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
			 (CurrentSetup.Actuator == MICROC) ||
             (CurrentSetup.Actuator == AES) ) )
      {
         length += AddToBuffer(Response, TRIGFORCEPARAM );
         length += AddToBuffer(Response, PSSERIALNUMPARAM );
         length += AddToBuffer(Response, ACTSERIALNUMPARAM );
      }
      else //Ps serial number is valid for all actuators and control levels
    	  length += AddToBuffer(Response, PSSERIALNUMPARAM);

   }
   else
   {
      ParamNos = MAX_RUN_RESULT_PARAM;
      length += AddToBuffer(Response, MAX_RUN_RESULT_PARAM );
      for (Index2 = 0; Index2 < MAX_RUN_RESULT_PARAM; Index2++)
      {
         length += AddToBuffer(Response, CurrentSetup.WeldParamOption[Index2] );
      }
   }
   /*Send global ram weld counter to SBC at the present moment*/
   length += AddToBuffer(Response, (UINT8)((FramVerInfo.PollingCommandCounter)>>24)); 	  
   length += AddToBuffer(Response, (UINT8)((FramVerInfo.PollingCommandCounter)>>16));	  
   length += AddToBuffer(Response, (UINT8)((FramVerInfo.PollingCommandCounter)>>8));	  
   length += AddToBuffer(Response, (UINT8)(FramVerInfo.PollingCommandCounter));	  


   HistoryStart = (UINT8 *)(FRAM1200_HISTORY_START);
   NextHistoryPtr = (UINT8*)CurrentSetup.WeldHistoryPtr;
   if (VGAHistoryData)
   {
      NextHistoryPtr = NextHistoryPtr - (WeldCount*(sizeof(WELD_DATA)));
      if (NextHistoryPtr < HistoryStart)
         NextHistoryPtr = NextHistoryPtr + (HISTORYDATA * sizeof(WELD_DATA));
   }   
   SaveHistoryPtr = NextHistoryPtr;

   for (Index2 = 0; Index2 < WeldCount; Index2 ++){
      
      if(NextHistoryPtr != HistoryStart)
         NextHistoryPtr = NextHistoryPtr - (sizeof(WELD_DATA));
      else
         NextHistoryPtr = HistoryStart + (HISTORYDATA-1)* sizeof(WELD_DATA);
      memcpy( &LastRunResults, NextHistoryPtr, (sizeof(WELD_DATA))); 
      if (LastRunResults.CycleCount <= 0) break;
      Index1++; 
   }
   length += AddToBuffer(Response, Index1);
   NextHistoryPtr = SaveHistoryPtr;   

   for (Index2 = 0; Index2 < WeldCount; Index2 ++){
      if(NextHistoryPtr != HistoryStart)
         NextHistoryPtr = NextHistoryPtr - (sizeof(WELD_DATA));
      else
         NextHistoryPtr = HistoryStart + (HISTORYDATA-1)* sizeof(WELD_DATA);
         
      memcpy( &LastRunResults, NextHistoryPtr, (sizeof(WELD_DATA))); 
     if (LastRunResults.CycleCount <= 0) break;

     /* All the alarmed Weld cycle are Drawn in red color */
     if(LastRunResults.NoCycleAlarms || LastRunResults.OverloadAlarms ||
        LastRunResults.EquipmentFailureAlarms || LastRunResults.CycleModifiedAlarms ||
        LastRunResults.CalibrateAlarms || (LastRunResults.SuspectBitResult & SUSPECTBITRESULTMASK)||
        (LastRunResults.RejectBitResult & REJECTBITRESULTMASK))
        length += AddToBuffer(Response, COLOR_RED);  //Red Color            
     else
        length += AddToBuffer(Response, COLOR_BLACK);  //Black Color

     for (Index1 = 0; Index1 < ParamNos; Index1++)
     {
        if (!ParamFlag)
        {
           if(CurrentSetup.WeldParamOption[Index1])
           {
              GetUnit_Values(Str, CurrentSetup.WeldParamOption[Index1],&LastRunResults);
           }
           else 
           { 
              Str[0] = NULL;
              Str[1] = NULL;
           }   
        }
        else
        {
           GetUnit_Values(Str, (UINT16)(RunParameter[Index1]),&LastRunResults);
        }
        
        if (!LangCheckNull(Str))
        {
		   Str[LINESIZE] = 0;
           StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
           strncpy(StrParam, StrTemp,sizeof(StrParam)-1);
           length += AddToBuffer(Response, strlen(StrParam));            
           length += AddToBufferString(Response, StrParam, strlen(StrParam));
        }   
        else 
        { 
           strcpy(Str, "---");
           length += AddToBuffer(Response, strlen(Str));            
           length += AddToBufferString(Response, Str, strlen(Str));
        }   

     }
     if (ParamFlag)
     {
      if ( (CurrentSetup.ControlLevel >= LEVEL_d) && 
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
			 (CurrentSetup.Actuator == MICROC) ||
             (CurrentSetup.Actuator == AES)) )
        {
           FormatVariables( LastRunResults.TrigForce, FORCE,
                           Str, LINESIZE, CurrentSetup.Units );  // Trigger Force
           Str[LINESIZE] = 0;
           StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
           strncpy(StrParam, StrTemp, sizeof(StrParam) - 1);
           length += AddToBuffer(Response, strlen(StrParam));            
           length += AddToBufferString(Response, StrParam, strlen(StrParam));

           //Ps serial number
		   strncpy(StrParam, LastRunResults.PsSerialNum, sizeof( LastRunResults.PsSerialNum) - 1);
		   length += AddToBuffer(Response, strlen(StrParam));
		   length += AddToBufferString(Response, StrParam, strlen(StrParam));
           //act serial number
		   strncpy(StrParam, LastRunResults.ActSerialNum, sizeof(LastRunResults.ActSerialNum) - 1);
		   length += AddToBuffer(Response, strlen(StrParam));
		   length += AddToBufferString(Response, StrParam, strlen(StrParam));
        }    
       else
       {
    	   //Ps serial number is still valid for all actuators and control levels
		   strncpy(StrParam, LastRunResults.PsSerialNum, sizeof( LastRunResults.PsSerialNum) - 1);
		   length += AddToBuffer(Response, strlen(StrParam));
		   length += AddToBufferString(Response, StrParam, strlen(StrParam));
       }

     }

     i = GetVGAPresetNameHeader(&LastRunResults, StrParam);  //Weld mode and preset number
     length += AddToBuffer(Response, i);  // Weld Mode
     length += AddToBuffer(Response, (UINT8)LastRunResults.PresetNum);  // Preset NUmber
     length += AddToBuffer(Response, strlen(StrParam));            
     length += AddToBufferString(Response, StrParam, strlen(StrParam));

     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleDate.day);  // Cycle Date
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleDate.month);
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleDate.year)%100));

     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.hour); // Cycle Time
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.minute);
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.second);

     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.NoCycleAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.OverloadAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.EquipmentFailureAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.CycleModifiedAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.CalibrateAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.Warnings));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.RejectBitResult));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.SuspectBitResult));	  

     length += AddToBuffer(Response, (UINT8)(LastRunResults.PSActControlFlags)); 

   }
   return length;
}

SINT8 * Trim_FillChar(SINT8 Str_temp[])
/****************************************************************************/
/*Description:-                                                             */
/* Trim the leading spaces in the Input string and returns string pointer   */
/****************************************************************************/
{
   SINT8 *StrPtr= NULL_PTR;
   UINT16 Index;
   for(Index=0; Index < LangStrLen(Str_temp); Index++)
   {
      if(Str_temp[Index]!=' ')
      {
         StrPtr = &Str_temp[Index]; 
         break;
      }
   }
   return(StrPtr); 
}

void VGAAlarmReset (UINT32 dummy)
/****************************************************************************/
/*Description:-                                                             */
/* The function wind up the processes running before entering the           */
/* the alarm Screen.                                                        */
/****************************************************************************/
{
      DiagFlag = FALSE; // Disable diagnostics
      /*If we are in TEST sequence Exit from there*/
      if(CurrentSequence == TESTMODE)
      {
         VGAExitTestSequence();
      }
      /*Wind up Horn Scan*/
      else if(HornScanInfo. ScanStatus == DUPS_SCANINPROG)
      {
          VGAAbortHornScan = TRUE;
          EnableWelding();
          HornScanInfo. ScanStatus = DUPS_NOSCAN;
          PrevHornState = SCAN_NONE;
      }
                
      /*Wind up Calibration Process */
      if(VGACalAllowed)
      {
          SCFinalCleanup();
      }
      else if(VGASnsrCalibAllowed)
      {
          CalibFinalCleanup();
      } 
      else if(StateMachineDisabled)
      {  
         ExitMenuAndEnableWeld();
      } 
      if ((VGAHornDown) && (dummy == 0))
      {
         VGAAction = EXIT_HD;
         VGAProcessHornDownMsg(); //commented

      }   
       
}

void CheckforCalib(void)
/****************************************************************************/
/*Description:-                                                             */
/* Function checks if calibration is in progress and set/reset              */
/* CalibInProgress flag.                                                    */
/****************************************************************************/
{
   CalibInProgress = FALSE;
   if (VGACalAllowed || VGASnsrCalibAllowed)
      CalibInProgress = TRUE;
}

UINT16 SendWeldState(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA weld state and preset nameto the SBC                           */
/****************************************************************************/
{
   UINT16 length = 0;
   length += AddToBuffer(&to, LangStrLen(StrWeldStateLine));            
   length += AddToBufferString(&to, StrWeldStateLine, 
                                 LangStrLen(StrWeldStateLine));
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.ActivePreset)>>8));	  
   length += AddToBuffer(&to, (UINT8)(CurrentSetup.ActivePreset));	  

   GetCurrentPresetNames();
   length += AddToBuffer(&to, LangStrLen(PresetNameBuffer));            
   length += AddToBufferString(&to, PresetNameBuffer, LangStrLen(PresetNameBuffer));
   return (length);
}

void GetBatchCountInfo()
{
	if(CurrentPreset.BatchFunction)//if batch count is enabled
		sprintf(BatchCountInfo, "%ld/%ld",  CurrentPreset.CurrBatchCount,CurrentPreset.BatchCount);
	else
		strcpy(BatchCountInfo, " ");//dont display

}

void ClearCurrentBatchCount()
{
    UINT32 OldVal;
   //First check the required authority
   if(CheckOperatorAuthority(RstBatchCount) == TRUE){
	   OldVal =  CurrentPreset.CurrBatchCount;
	   CurrentPreset.CurrBatchCount = 0;
	   UpdateCurrentPresetAndSetup((PARAM)0);//Passing 0 as it should not cause preset to go invalidated
	   if(OldVal)
         RecordEvents(EVENT_PARAMETER_CHANGED, OldVal, CurrentPreset.CurrBatchCount);
   }
}

 /*********************************END***************************************/
