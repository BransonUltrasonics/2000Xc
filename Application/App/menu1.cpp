/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu1.cpp_v   1.16   Oct 10 2017 10:46:44   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu1.cpp_v  $
 * 
 *    Rev 1.16   Oct 10 2017 10:46:44   RJamloki
 * added MICROC id, for evaluate actuator id's
 * 
 *    Rev 1.15   08 Apr 2015 13:44:08   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.14   08 Jan 2015 02:58:00   AnPawar
 * included ascii.h file
 * 
 *    Rev 1.13   28 Nov 2014 07:37:06   rjamloki
 * removed unused extern variables.
 * 
 *    Rev 1.12   22 Aug 2014 07:00:18   rjamloki
 * Changes to add hold force in weld result
 * 
 *    Rev 1.11   18 Aug 2014 01:36:04   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   07 Aug 2014 15:36:16   tayars
 * Changed Velocity to Downspeed
 * 
 *    Rev 1.9   11 Jun 2014 11:50:34   rjamloki
 * Enabled all History parameters in RunScreensParamMenu.
 * Weld history columns display will be based on Selection from WeldHistory setup
 * 
 *    Rev 1.8   27 May 2014 10:13:00   amaurya
 * Added support for madatory colums in weld history
 * 
 *    Rev 1.7   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:08:30   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   26 Mar 2014 12:21:44   rjamloki
 * function ExitWeldSetupMenu() declaration changed,some extern removed, GetCurrentWeldData(),SelectWeldSetupMenu(),SoundBeeper() function changed
 * 
 *    Rev 1.4   05 Mar 2014 13:56:30   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:42   rjamloki
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
   Filename: menu1.c

   Function name:

  ------------------------------- DESCRIPTION ---------------------------------

       This file will deal with the Run Screen and all its glory.


 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "string.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "keypad.h"
#include "selctkey.h"
#include "weld_obj.h"
#include "display.h"
#include "beep.h"
#include "graphs.h"
#include "menu3.h"
#include "menu1.h"
#include "getmsg.h"
#include "alarms.h"
#include "menu7a.h"
#include "stdlib.h"
#include "WeldManagerTask.h"
#include "ascii.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT8 RunScreenFlag = FALSE;

UINT16 AdjustWeldSetupMenuFlag=0; /* TRUE:Adjust Weld Setup selected from Run Screen */
                                  /* FALSE:when Main Menu, Go Back, Run or Setup key pressed */


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

BIT_FLAGS BitFlags;


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/
static void SetRunScreenFlag(void);


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SINT8 ScrollBuffer[SCROLLBUFFERSIZE];

extern UINT8 MainKeyFlag;
extern SINT16 BlankMenuCounter;
extern WELD_OBJECT *MsDataPtr;

MENUEND endlist1 = { TRUE };

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/


void SetOneLineDataBit(UINT16 OneLineIndex, UINT8 ActiveFlag)
{

   switch(OneLineIndex)
   {
      case WELDRESULTS:
         if(!ActiveFlag)
            BitFlags.WRbit = TRUE;
         else
            BitFlags.WRbit = FALSE;
         break;

      case RCYCLECOUNT:
         if(!ActiveFlag)
            BitFlags.Cyclebit = TRUE;
         else
            BitFlags.Cyclebit = FALSE;
         break;

      case RPRESETNUM:
         if(!ActiveFlag)
            BitFlags.PresetNum = TRUE;
         else
            BitFlags.PresetNum = FALSE;
         break;

      case RTIME:
         if(!ActiveFlag)
            BitFlags.Timebit = TRUE;
         else
            BitFlags.Timebit = FALSE;
         break;

      case RPKPWR:
         if(!ActiveFlag)
            BitFlags.PkPwrbit = TRUE;
         else
            BitFlags.PkPwrbit = FALSE;
         break;

      case RENERGY:
         if(!ActiveFlag)
            BitFlags.Energybit = TRUE;
         else
            BitFlags.Energybit = FALSE;
         break;

      case RVELOCITY_AED:
         if(!ActiveFlag)
            BitFlags.VelocityAedbit = TRUE;
         else
            BitFlags.VelocityAedbit = FALSE;
         break;

      case RVELOCITY_AEF:
         if(!ActiveFlag)
            BitFlags.VelocityAefbit = TRUE;
         else
            BitFlags.VelocityAefbit = FALSE;
         break;

      case RWABSDIST:
         if(!ActiveFlag)
            BitFlags.WeldAbsbit = TRUE;
         else
            BitFlags.WeldAbsbit = FALSE;
         break;

      case RTABSDIST:
         if(!ActiveFlag)
            BitFlags.Absbit = TRUE;
         else
            BitFlags.Absbit = FALSE;
         break;

      case RWCOLDIST:
         if(!ActiveFlag)
            BitFlags.WeldCollbit = TRUE;
         else
            BitFlags.WeldCollbit = FALSE;
         break;

      case RTCOLDIST:
         if(!ActiveFlag)
            BitFlags.TtlCollbit = TRUE;
         else
            BitFlags.TtlCollbit = FALSE;
         break;

      case RAMPSTART:
         if(!ActiveFlag)
            BitFlags.AmpAbit = TRUE;
         else
            BitFlags.AmpAbit = FALSE;
         break;

      case RAMPEND:
         if(!ActiveFlag)
            BitFlags.AmpBbit = TRUE;
         else
            BitFlags.AmpBbit = FALSE;
         break;

      case RPRESSUREA:
         if(!ActiveFlag)
            BitFlags.SetPAbit = TRUE;
         else
            BitFlags.SetPAbit = FALSE;
         break;

      case RPRESSUREB:
         if(!ActiveFlag)
            BitFlags.SetPBbit = TRUE;
         else
            BitFlags.SetPBbit = FALSE;
         break;

      case RFORCE:
         if(!ActiveFlag)
            BitFlags.SetFEndbit = TRUE;
         else
            BitFlags.SetFEndbit = FALSE;
         break;

      case RSYSPRESS:
         if(!ActiveFlag)
            BitFlags.Pressbit = TRUE;
         else
            BitFlags.Pressbit = FALSE;
         break;

      case RFREQMIN:
         if(!ActiveFlag)
            BitFlags.FreqMinbit = TRUE;
         else
            BitFlags.FreqMinbit = FALSE;
         break;

      case RFREQMAX:
         if(!ActiveFlag)
            BitFlags.FreqMaxbit = TRUE;
         else
            BitFlags.FreqMaxbit = FALSE;
         break;

      case RFREQSTART:
         if(!ActiveFlag)
            BitFlags.FreqStartbit = TRUE;
         else
            BitFlags.FreqStartbit = FALSE;
         break;

      case RFREQEND:
         if(!ActiveFlag)
            BitFlags.FreqEndbit = TRUE;
         else
            BitFlags.FreqEndbit = FALSE;
         break;

      case RFREQCHG:
         if(!ActiveFlag)
            BitFlags.FreqChgbit = TRUE;
         else
            BitFlags.FreqChgbit = FALSE;
         break;

      case RCYCLETIME:
         if(!ActiveFlag)
            BitFlags.CycleTimebit = TRUE;
         else
            BitFlags.CycleTimebit = FALSE;
         break;
      case RUSERID:
		if (!ActiveFlag)
			BitFlags.UserId = TRUE;
		else
			BitFlags.UserId = FALSE;
		break;
	case RUDISCAN:
		if (!ActiveFlag)
			BitFlags.UdiScan = TRUE;
		else
			BitFlags.UdiScan = FALSE;
		break;

	case RPRESETREV:
		if (!ActiveFlag)
			BitFlags.PresetRev = TRUE;
		else
			BitFlags.PresetRev = FALSE;
		break;

	case RPRESETVALIDATED:
		if (!ActiveFlag)
			BitFlags.PresetValidated = TRUE;
		else
			BitFlags.PresetValidated = FALSE;
		break;

	case RACTASSEMBLYNUM:
		if (!ActiveFlag)
			BitFlags.ActAssemblyNum = TRUE;
		else
			BitFlags.ActAssemblyNum = FALSE;
		break;
	case RPSASSEMBLYNUM:
		if (!ActiveFlag)
			BitFlags.PsAssemblyNum = TRUE;
		else
			BitFlags.PsAssemblyNum = FALSE;
		break;
	case RSTACKASSEMBLYNUM:
		if (!ActiveFlag)
			BitFlags.StackAssemblyNum = TRUE;
		else
			BitFlags.StackAssemblyNum = FALSE;
		break;
	case RHOLDFORCEMAX:
	    if(!ActiveFlag)
	        BitFlags.HoldForceMax = TRUE;
	    else
	        BitFlags.HoldForceMax = FALSE;
	    break;


      default:
         break;
   }
}


static void SetRunScreenFlag(void)
{
   RunScreenFlag = TRUE;
}

void ClearRunScreenFlag(void)
{
   RunScreenFlag = FALSE;
}


void GetCurrentWeldData(UINT32 )
{
   strcpy(ScrollBuffer, "");         /* Initial 1st position in buffer */

   SetRunScreenFlag();

   if(CurrentSetup.HmenuIndex >= RMAXPARAMETERS)
      CurrentSetup.HmenuIndex = 0;
}



void UpdateParam(void)
{
   if(!MainKeyFlag)
   {
      SendFakeKeyPress(GoBackKey);
      SendFakeKeyPress(Select2Key);
      BlankMenuCounter = 2;
   }
}


void SoundBeeper(UINT32 )
{
   Beep(ERRORBEEP);
}


void ClearWeldData(void)
{
   FinalResults.ActualFreqEnd = 0;
   FinalResults.ActualFreqStart = 0;
   FinalResults.FrequencyChange = 0;
   FinalResults.FrequencyMin = 0;
   FinalResults.FrequencyMax = 0;
   FinalResults.TotalEnergy = 0;
   FinalResults.ActualWeldAbs = 0;
   FinalResults.ActualTotalAbs = 0;
   FinalResults.ActualTriggerDistance = 0;
   FinalResults.ActualWeldCollapse = 0;
   FinalResults.ActualTotalCollapse = 0;
   FinalResults.ActualDownspeed = 0;
   FinalResults.WeldForceEnd = 0;
   FinalResults.ActualAmplitudeStart = 0;
   FinalResults.ActualAmplitudeEnd = 0;
   FinalResults.PeakPower = 0;
   FinalResults.ActualWeldTime = 0;
   FinalResults.RejectBitResult = 0;
   FinalResults.SuspectBitResult = 0;
   FinalResults.NoCycleAlarms = 0;
   FinalResults.OverloadAlarms = 0;
   FinalResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   FinalResults.CycleModifiedAlarms = 0;
   FinalResults.CalibrateAlarms = 0;
   FinalResults.Warnings = 0;
   FinalResults.PresetNum = 0;
   FinalResults.PresetName[0] = NUL;
   FinalResults.CycleTimeResult = 0;

   MsDataPtr->AmpStepAtTime = 0;
   MsDataPtr->PressureStepAtTime = 0;
   MsDataPtr->HoldEndAtTime = 0;
   MsDataPtr->SeekEndAtTime = 0;
}


const RSPARAMETER WeldResultsItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    WELDRESULTS };                /* Identifier for run parameter          */

const RSPARAMETER CycleCounters = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RCYCLECOUNT };                /* Identifier for run parameter          */

const RSPARAMETER WeldTimeItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTIME };                      /* Identifier for run parameter          */

const RSPARAMETER PeakPowerItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPKPWR };                     /* Identifier for run parameter          */

const RSPARAMETER EnergyItems = {
    LEVEL_e,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RENERGY };                    /* Identifier for run parameter          */

const RSPARAMETER VelocityItem_aed = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED | AES | MICRO | MICROC),                /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RVELOCITY_AED };              /* Identifier for run parameter          */

const RSPARAMETER VelocityItem_aef = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    (AEF),                        /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    VEL,                          /* what conditions are required   Mask2  */
    VEL,                          /* to display this menu           Cond2  */
    RVELOCITY_AEF };              /* Identifier for run parameter          */

const RSPARAMETER WeldAbsDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RWABSDIST };                  /* Identifier for run parameter          */

const RSPARAMETER AbsDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTABSDIST };                  /* Identifier for run parameter          */

const RSPARAMETER WeldColDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RWCOLDIST };                  /* Identifier for run parameter          */

const RSPARAMETER TtlColDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTCOLDIST };                  /* Identifier for run parameter          */

const RSPARAMETER AmpStartItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    (ACTUATOR)DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RAMPSTART };                  /* Identifier for run parameter          */

const RSPARAMETER AmpEndItems = {
    LEVEL_ea,                     /* Lowest model to be displayed on       */
    (ACTUATOR)DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RAMPEND };                    /* Identifier for run parameter          */


const RSPARAMETER Pressure_A = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AES|MICROC),                          /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESSUREA };                    /* Identifier for run parameter          */

const RSPARAMETER Pressure_B = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AES|MICROC),                          /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESSUREB };                    /* Identifier for run parameter          */

const RSPARAMETER Force_End = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFORCE };                     /* Identifier for run parameter          */

const RSPARAMETER WeldPressureItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (ACTUATOR)(AED|AES|MICRO|MICROC),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RSYSPRESS };                  /* Identifier for run parameter          */

const RSPARAMETER FreqMinItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    (ACTUATOR)DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQMIN };                   /* Identifier for run parameter          */

const RSPARAMETER FreqMaxItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQMAX };                   /* Identifier for run parameter          */

const RSPARAMETER FreqStartItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQSTART };                 /* Identifier for run parameter          */

const RSPARAMETER FreqEndItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQEND };                   /* Identifier for run parameter          */

const RSPARAMETER FreqChgItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQCHG };                   /* Identifier for run parameter          */

const RSPARAMETER PresetNumItems = {
    LEVEL_t,                     /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESETNUM };                 /* Identifier for run parameter          */


const RSPARAMETER CycleTimes = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RCYCLETIME };                  /* Identifier for run parameter          */



const RSPARAMETER UserId = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RUSERID };                  /* Identifier for run parameter          */

const RSPARAMETER UdiScan = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RUDISCAN };                  /* Identifier for run parameter          */

const RSPARAMETER PresetRev = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESETREV };                  /* Identifier for run parameter          */

const RSPARAMETER PresetValidated = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESETVALIDATED };                  /* Identifier for run parameter          */

const RSPARAMETER ActAssemblyNum = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RACTASSEMBLYNUM };                  /* Identifier for run parameter          */

const RSPARAMETER PsAssemblyNum = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPSASSEMBLYNUM };                  /* Identifier for run parameter          */

const RSPARAMETER StackAssemblyNum = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RSTACKASSEMBLYNUM };                  /* Identifier for run parameter          */

const RSPARAMETER HoldForceMax = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RHOLDFORCEMAX };                  /* Identifier for run parameter          */








const MENU RunScreenParamMenu[] ={
									//mandatory
									{&CycleCounters,              _RSPARAMETER },
									{&UserId,                	  _RSPARAMETER },
		                            {&UdiScan,                	  _RSPARAMETER },
		                            {&PresetNumItems,             _RSPARAMETER },
		                            {&PresetRev,                  _RSPARAMETER },
		                            {&PresetValidated,            _RSPARAMETER },
		                            {&ActAssemblyNum,             _RSPARAMETER },
		                            {&PsAssemblyNum,              _RSPARAMETER },
		                            {&StackAssemblyNum,           _RSPARAMETER },
		                            //Optional
                                    {&WeldTimeItems,              _RSPARAMETER },
                                    {&PeakPowerItems,             _RSPARAMETER },
                                    {&EnergyItems,                _RSPARAMETER },
                                    {&VelocityItem_aed,           _RSPARAMETER },
                                    {&VelocityItem_aef,           _RSPARAMETER },
                                    {&WeldAbsDistItems,           _RSPARAMETER },
                                    {&AbsDistItems,               _RSPARAMETER },
                                    {&WeldColDistItems,           _RSPARAMETER },
                                    {&TtlColDistItems,            _RSPARAMETER },
                                    {&AmpStartItems,              _RSPARAMETER },
                                    {&AmpEndItems,                _RSPARAMETER },
                                    {&Pressure_A,                 _RSPARAMETER },
                                    {&Pressure_B,                 _RSPARAMETER },
                                    {&Force_End,                  _RSPARAMETER },
                                    {&WeldPressureItems,          _RSPARAMETER },
                                    {&FreqMinItems,               _RSPARAMETER },
                                    {&FreqMaxItems,               _RSPARAMETER },
                                    {&FreqStartItems,             _RSPARAMETER },
                                    {&FreqEndItems,               _RSPARAMETER },
                                    {&FreqChgItems,               _RSPARAMETER },
                                    {&CycleTimes,                 _RSPARAMETER },
                                    {&HoldForceMax,               _RSPARAMETER },
                                    {&endlist1,                   (MENUS)ENDLIST}   };

