/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/beep.cpp_v   1.11   16 Apr 2015 07:17:58   rjamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/beep.cpp_v  $
 * 
 *    Rev 1.11   16 Apr 2015 07:17:58   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.10   11 Feb 2015 06:30:52   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.9   21 Jan 2015 09:39:06   amaurya
 * Fix for Estop Beep.
 * 
 *    Rev 1.8   26 Sep 2014 03:14:22   rjamloki
 * Removed psos references
 * 
 *    Rev 1.7   21 May 2014 10:47:46   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 02:50:44   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   21 Apr 2014 13:25:26   rjamloki
 * preset parameter Estop Alarm initialised
 * 
 *    Rev 1.4   05 Mar 2014 13:56:18   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:20   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: beep.c

 ---------------------------- DESCRIPTION -----------------------------------
 */

#include "portable.h"
#include "beep.h"
#include "preset.h"
#include "state.h"
#include "statedrv.h"
#include "digout.h"
#include "outports.h"
#include "stdio.h"
#include "CPLD.h"
#include "UndefPrintf.h"
#include "inputtask.h"


#define INCLUDE_BEEP_UNIT_TEST

/**  **  Variables and things for beeper  **  **/
/*  This module contains the routines for dealing with the beeper.         */
/*                                                                         */
/*     Beep -  high level routine to indicate which beeper should */
/*        sound and also turns on beeper                                   */

/* Number of beeps in queue   */
SINT16 NumberOfBeeps;
SINT16 BeepOnTime; /* Flag for timer routine to clear       */
static UINT16 BeeperOn = FALSE; /* Flag for timer routine to clear   */
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
void Beep(enum BEEPS Type)
/**************************************************************************/
/*                                                                         */
/*  This function will take the passed parameters and saved them so that   */
/*  ProcessBeeper can actually turn the beeper on and off.   The first     */
/*  parameter, nmbr, is the number of times the beeper should beep.  The   */
/*  second parameter is what kind of sound is it(ALARM, ERROR or TRIGGER). */
/*  The beeper will not sound if this kind of sound has been disabled.     */
/*                                                                         */
/***************************************************************************/
{
      switch (Type) {
         case ALARMBEEP:
			if( (CurrentSetup.BeeperAlarm & BIT0) == BIT0 ) {
               BeepOnTime = ALARMBEEPTIME;
               CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
               UserCfgOutputOn(OUTPUT_EXT_BEEPER);
               NumberOfBeeps = 5;
               BeeperOn = TRUE;
            }
            break;

         case SYSTEMBEEP:
            BeepOnTime = SYSTEMBEEPTIME;
            CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
            NumberOfBeeps = 1;
            BeeperOn = TRUE;
            break;

         case ERRORBEEP:
            if ((CurrentSetup.BeeperError & BIT0) == BIT0) {
               BeepOnTime = ERRORBEEPTIME;
               CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
               UserCfgOutputOn(OUTPUT_EXT_BEEPER);
               NumberOfBeeps = 3;
               BeeperOn = TRUE;
            }
            break;

         case TRIGGERBEEP:
            if (((CurrentSetup.BeeperTrigger & BIT0) == BIT0)
                 || (CurrentSequence == CALIBRATION)) /* Beep during calibration*/
            {                                         /* even when disabled     */
               BeepOnTime = TRIGGERBEEPTIME;
               CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
               UserCfgOutputOn(OUTPUT_EXT_BEEPER);
               NumberOfBeeps = 1;
               BeeperOn = TRUE;
            }
            break;

         case CONFIRMBEEP:
               BeepOnTime = CONFIRMBEEPTIME;
               CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
               NumberOfBeeps = 3;
               BeeperOn = TRUE;
               UserCfgOutputOn(OUTPUT_EXT_BEEPER);
               break;

          case ESTOPBEEP:
            if ((CurrentSetup.BeeperEstop & BIT0) == BIT0) {
                BeepOnTime = ESTOPBEEPTIME;
                CPLD::thisPtr->SetBuzzer(TRUE);
                UserCfgOutputOn(OUTPUT_EXT_BEEPER);
                NumberOfBeeps = 1;
                BeeperOn = TRUE;
             }
            break;
         default:
            BeepOnTime = 0;
            BeeperOn = FALSE;
            break;
      }
}

void CheckBeeper(void)
{
   if (NumberOfBeeps > 0)
   {
      if (--BeepOnTime <= 0)
      {
         TurnOffBeeper();
      }
   }
}

void TurnOffBeeper(void)
{

      if(NumberOfBeeps-- <= 1){
         CPLD::thisPtr->SetBuzzer(FALSE);      /* Turn Beeper off       */
         BeepOnTime = 0;
         BeeperOn = FALSE;
         NumberOfBeeps = 0;
         UserCfgOutputOff(OUTPUT_EXT_BEEPER);
      }
      else{
         BeepOnTime = ERRORBEEPTIME;
         if(BeeperOn == TRUE){
            CPLD::thisPtr->SetBuzzer(FALSE);       /* Turn Beeper off       */
            BeeperOn = FALSE;
            UserCfgOutputOff(OUTPUT_EXT_BEEPER);
         }
         else{
            CPLD::thisPtr->SetBuzzer(TRUE);    /* Turn Beeper on         */
            BeeperOn = TRUE;
            UserCfgOutputOn(OUTPUT_EXT_BEEPER);
         }
      }
}

/* Include for Unit test */
#ifdef INCLUDE_BEEP_UNIT_TEST
/*    #include "..\ut\beep.ut"   */
#endif
/* End of include for unit test */
