/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/selctkey.cpp_v   1.17   16 Apr 2015 07:29:12   rjamloki  $ */
/****************************************************************************/ 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/selctkey.cpp_v  $
 * 
 *    Rev 1.17   16 Apr 2015 07:29:12   rjamloki
 * UpdateCurrentPresetAndSetup function explained better as per review comment
 * 
 *    Rev 1.16   08 Apr 2015 13:46:28   AnPawar
 * Function header added in UpdateCurrentPresetAndSetup().
 * 
 *    Rev 1.15   11 Mar 2015 09:19:00   amaurya
 * UpdateCurrentPresetAndSetup() changed to remain preset validation state unchanged if preset parameter changed within tweaklimits.
 * 
 *    Rev 1.14   10 Nov 2014 04:59:20   AnPawar
 * UpdateCurrentPresetAndSetup() function changed.
 * 
 *    Rev 1.13   06 Oct 2014 06:45:00   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.12   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.11   11 Sep 2014 11:08:36   rjamloki
 * Added parameter change event
 * 
 *    Rev 1.10   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.9   09 Jul 2014 12:21:32   rjamloki
 * Fixed UpdateCurrentPresetAndSetup function to change the preset verify status only on preset parameter change.
 * 
 *    Rev 1.8   11 Jun 2014 12:07:50   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:38:00   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   14 Apr 2014 09:40:04   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.4   05 Mar 2014 13:56:44   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:50   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: selctkey.c
                                        
   Function name:

*/

/*
 ------------------------------- DESCRIPTION ---------------------------------
*/ 

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include "names.h" 
#include "menu.h"
#include "preset.h"
#include "ticks.h"
#include "keypad.h"
#include "beep.h"
#include "genrlmsg.h"           /* generic message type               */
#include "selctkey.h"
#include "SystemManagerTask.h"
#include "battram.h"
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

#include "sc.h"
#include "display.h"
#include "menu1.h"
#include "menu5.h"
#include "menu3.h"
#include "menu7.h"
#include "menu7a.h"
#include "fpled.h"
#include "util.h"
#include "getmsg.h"
#include "state.h"
#include "statedrv.h"
#include "snsrcalb.h"
#include "digout.h"
#include "spidd.h"
#include "genalarm.h"
#include "SystemManagerTask.h"
#include "serial.h"
#include "rtclock.h"
#include "Events.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                     

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT16   CurrentSetupChgedFlag = FALSE;


/*
 --------------------------- LOCAL TYPE DECLARATIONS -------------------------
*/                            
 /*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*
 ---------------------------- EXTERNAL FUNCTIONS -----------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
/*
 ---------------------------------- CODE -------------------------------------
*/

void UpdateCurrentPreset(enum PARAM Id, SINT32 Value1, UINT16 Value2)
{
   EDIT_PARAM_MSG_QUEUE_TYPE           EditParamMsg;

   if (Id != ALLEMPTY)
   {
  
      if ((Id < CURRENT_SETUP_OFFSET) || (Id > DUPS_PARAM_OFFSET))
      {
 		CurrentPreset.Validated = FALSE;
		CurrentPreset.Locked = FALSE;
        CurrentPreset.PresetUpdateComplete = FALSE;
        CurrentPreset.Verified = FALSE;
        EditParamMsg.common.opcode = OP_CHANGE_PRESET_DATA;
      }
      else
      {
         CurrentSetupChgedFlag = TRUE;
         EditParamMsg.common.opcode = OP_CHANGE_CURRENT_SETUP;
      }

      EditParamMsg.param_id = Id;          /* from param.h */
      EditParamMsg.value1 = Value1;       /* SINT32 data  */
      EditParamMsg.value2 = Value2;       /* UINT16 data  */
      SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &EditParamMsg), 20);
   }
}

/**************************************************************************************************
*
*   Purpose:
*	1- To determine that preset needs to be invalidated or not based on setup limits applicability for the parameter being changed.
*   2- To record parameter change event and invalidate the current preset in certain conditions.
*   3- Invoking System manager task to copy current preset from ram to FRAM.
*	This function is called from XmlDataResponse function. It first checks whether the modified parameter belongs to validated preset
*	If yes it checks that if the setup limit is enabled for that parameter. If both these conditions are satisfied it just sends the message
*	to SystemManager task to copy current preset in FRAM. If any of these conditions are not satisfied it calls the function
*	to record parameter change event, invalidate the validated preset and notify system manager to copy current preset in ram.
*
*   Entry condition:
*	enum PARAM id. The parameter id of modified parameter.
*
*   Exit condition:
*	void
*
****************************************************************************************************/

void UpdateCurrentPresetAndSetup(enum PARAM Id)
{
   GENERIC_MSG genericMsg;
   if ((CurrentPreset.Validated == FALSE) || (SetupValid() == FALSE))
   {
	   //First we need to confirm which parameter changes shall make the preset status invalidated and unlocked
	   if((Id != VALIDATEPS) && (Id != LOCKPS))
	   {
		   if((Id > 0) && (Id < CURRENT_SETUP_OFFSET))
		   {
			   if(memcmp(ParamOldVal, ParamNewVal,sizeof(ParamOldVal)-1) || (DisableFlagOldValue != DisableFlagNewValue))
					RecordParamChangeEvent(ParamOldVal, ParamNewVal, Type);
			   CurrentPreset.Verified = FALSE;
			   CurrentPreset.Validated = FALSE;
			   CurrentPreset.Locked = FALSE;
			   CurrentPreset.PresetUpdateComplete = FALSE;
		   }
		   genericMsg.common.opcode = OP_CHANGE_PRESET_DATA;
		   SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &genericMsg), 20);
	   }
   }
   else
   {
		   genericMsg.common.opcode = OP_CHANGE_PRESET_DATA;
		   SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &genericMsg), 20);
   }
}
