/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FrontPanelKeypadTask.cpp_v   1.19   16 Feb 2015 01:16:04   amaurya  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FrontPanelKeypadTask.cpp_v  $
 * 
 *    Rev 1.19   16 Feb 2015 01:16:04   amaurya
 * change in function FrontPanelKeypadTask::Tick() to fix continuous alarm beep on reset key press
 * 
 *    Rev 1.18   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.17   10 Nov 2014 04:49:56   AnPawar
 * Removed CPLD extern
 * 
 *    Rev 1.16   06 Oct 2014 06:33:02   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.15   03 Oct 2014 06:03:28   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.14   26 Sep 2014 03:14:24   rjamloki
 * Removed psos references
 * 
 *    Rev 1.13   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.12   09 Jul 2014 13:28:22   rjamloki
 * Added authority check before resetting alarm.
 * 
 *    Rev 1.11   11 Jun 2014 11:29:42   rjamloki
 * fpsmngr file globals here and the fpsmngr.cpp removed
 * 
 *    Rev 1.10   21 May 2014 10:47:56   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 03:05:28   rjamloki
 * Logic 1 check on Row 0 and 1 for test and reset.
 * 
 *    Rev 1.8   14 Apr 2014 09:40:02   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.7   26 Mar 2014 12:14:14   rjamloki
 * FrontPanelKeypadTask::FrontPanelKeypadTask() , FrontPanelKeypadTask::Tick() function changed 
 * 
 *    Rev 1.6   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:24   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:36   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.3   03 Jan 2014 08:45:26   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Module name:

 Filename:        FrontPanelKeypadTask.cpp

 Function name:

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
 */
#include "FrontPanelKeypadTask.h"
#include "FIFO.h"
#include "qdef.h"
#include "beep.h"
#include "snsrcalb.h"
#include "state.h"
#include "inports.h"
#include "fpkp_msg.h"
#include "statedrv.h"
#include "digout.h"
#include "fpled.h"
#include "getmsg.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "CPLD.h"
#include "Keypad.h"
#include "command.h"
#include "Alarms.h"
#include "WeldManagerTask.h"

#define FPKTASK_FIFOSIZE 10
#define MESSAGE_DELAY    400
#define ALLKEYSENABLED   0xffffffff

extern UINT16 CalibrationPassed;
extern UINT16 EstopHistoryFlag;
extern UINT8 PowerUpColdStart;


static GENERIC_MSG WeldMsgOut;

FrontPanelKeypadTask *FrontPanelKeypadTask::thisPtr;
UINT32 KeyMask;
UINT8    HS_KeyPressed;
BOOLEAN  HS_status;
UINT8 KeyLockOutFlag = TRUE;
UINT32 FpkpQid;
UINT32 KeyBitAssigned[] = { KEY_0MASK, KEY_1MASK, KEY_2MASK, KEY_3MASK,
         KEY_4MASK, KEY_5MASK, KEY_6MASK, KEY_7MASK, KEY_8MASK, KEY_9MASK,
         DPOINTKEYMASK, INCKEYMASK, DECKEYMASK, CLEARKEYMASK, ENTERKEYMASK,
         SETUPKEYMASK, RESETKEYMASK, TESTKEYMASK, MAINKEYMASK, GOBACKKEYMASK,
         OFFKEYMASK, PRINTKEYMASK, HORNDOWNKEYMASK, RUNKEYMASK, SELECT1KEYMASK,
         SELECT2KEYMASK, SELECT3KEYMASK, UNASSIGNED3MASK, RIGHTKEYMASK,
         LEFTKEYMASK, UPKEYMASK, DOWNKEYMASK};



FrontPanelKeypadTask::FrontPanelKeypadTask() :
      Task("FPKT", T_SIZE_1024), FrontPanelKeypadTaskQ(FPKTASK_FIFOSIZE, "FpktQ")
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   FpkpQid = (UINT32) &FrontPanelKeypadTaskQ;
   ResetPressedFlag = FALSE;
}

FrontPanelKeypadTask::~FrontPanelKeypadTask()
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask destructor                                              */
/****************************************************************************/
{

}

void FrontPanelKeypadTask::Run()
{
   UINT8 KeyPressed;
   UINT16 KeyFlag;
   FPKP_MSG_QUEUE_TYPE FpkpQueue;
   FRONT_PANEL_USER_REQUEST_MSG FpscMsg;

   FpscMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
   FpscMsg.common.pointer_flag = NO_DATA_PTR;
   FpscMsg.common.source_task = FPKP_SOURCE_TASK;

   /* next, install and initialize the fp keypad vector */

   DelayMs(100);
   /*----------------------------------------------------------------------*/
   /* Loop forever                                                         */
   /*----------------------------------------------------------------------*/

   while (TRUE) {

      /* block on empty queue */
      FrontPanelKeypadTaskQ.Read(this, FpkpQueue, -1);
      // this code handles Reset and ignores all other keys
      if (EStopState != ESTOPBTN_RESET) {
         // if EStop is released and alarm is active, process only Reset key
         if (EStopState == ESTOPBTN_RELEASED) {
            KeyPressed = FpkpQueue.FpKeyPressedMsg.key;
            if (KeyPressed == ResetKey) // handle only Reset key
                  {
               PSIdle();
               EStopState = ESTOPBTN_RESET;
               // if no alarms - turn the LED off
               if (TotalAlarmCount == 0)
                  UpdateLED(RESETLED, OFF);
            }
            else
               Beep(ERRORBEEP); // beep at any other key
         }
      }
      else {
         /* if estop is active donot process the key */
         if (EstopHistoryFlag == FALSE) {

            KeyPressed = FpkpQueue.FpKeyPressedMsg.key;
            HS_KeyPressed = KeyPressed;
            if ((KeyBitAssigned[KeyPressed] & KeyMask) != 0) {
               switch (FpkpQueue.generic.common.opcode) {
               /* Process FP Keypresses */
               case OP_FRONT_PANEL_KEYPRESS:
                  /* get key pad input */
                  FpscMsg.user_request = KeyPressed;
                  KeyFlag = FALSE;

                  if (KeyLockOutFlag) {
                     if (KeyPressed == ClearKey) {
                        SendFakeKeyPress(ClearKey);
                        PowerUpColdStart = TRUE;
                     }
                     else if (KeyPressed == GoBackKey) {
                        OnboardDiag = TRUE; /* diagnostics through the serial port enabled */
                     }
                  }
                  else {
                     if (KeyPressed == TestKey) {
                        WeldMsgOut.common.opcode = OP_TEST_KEY_PRESSED;
                        KeyFlag = TRUE;
                     }
                     else if (KeyPressed == ResetKey) {
                        //First check the required authority
                        if(CheckOperatorAuthority(ResetAlarm) == TRUE)
                        {
                        	WeldMsgOut.common.opcode = OP_RESET_KEY_PRESSED;
                        	KeyFlag = TRUE;
                        }
                     }
                     else if (KeyPressed == MainKey) {
                        if ((GetCurrentSequenceType() == CALIBRATION) || (GetCurrentSequenceType() == SC)) {
                           CalibrationPassed = CAL_ABORTED;
                        }
                        WeldMsgOut.common.opcode = OP_MAIN_KEY_PRESSED;
                        KeyFlag = TRUE;
                     }
                     else if (KeyPressed == GoBackKey) {
                        if ((GetCurrentSequenceType() == CALIBRATION) || (GetCurrentSequenceType() == SC)) {
                           CalibrationPassed = CAL_ABORTED;
                        }
                        WeldMsgOut.common.opcode = OP_GOBACK_KEY_PRESSED;
                        KeyFlag = TRUE;
                     }
                     else if (KeyPressed == RunKey) {
                        WeldMsgOut.common.opcode = OP_RUN_KEY_PRESSED;
                        KeyFlag = TRUE;
                     }
                     if (KeyFlag == TRUE) {
                        WeldManagerTask::thisPtr->WELDMNGRTaskQ.WriteRetry(0, *((WMGR_MSG_QUEUE_TYPE*) &WeldMsgOut), 50);
                     }
                     else {
                        SendFakeKeyPress((KEY_CODE_TYPE) KeyPressed);
                     }
                  } /* end of switch opcode */
                  break;

               default:
                  break;

               } /* end switch FpkpQueue.common.opcode */
            }
            else {
               if (HS_status == TRUE)
                  Beep(ERRORBEEP);
            }
         } // end of 'continue' workaround
      } /* estop end */

   } /* end while forever */

}

extern BOOLEAN TestTestFlag;
void FrontPanelKeypadTask::Tick()
{
   if(UserLoggedIn == TRUE)
   {
	   if (cpld->GetDin(Row1) || TestTestFlag) {
		  message.FpKeyPressedMsg.key = TestKey;
		  message.generic.common.opcode = OP_FRONT_PANEL_KEYPRESS;
		  FrontPanelKeypadTaskQ.Write(this, message, 0);
	   }
   }
   if (cpld->GetDin(Row0)) {
	   if(ResetPressedFlag == FALSE){//Fix for continuous beep on reset
			message.FpKeyPressedMsg.key = ResetKey;
			message.generic.common.opcode = OP_FRONT_PANEL_KEYPRESS;
			FrontPanelKeypadTaskQ.Write(this, message, 0);
			ResetPressedFlag = TRUE;
	   }
   }   
   else
      ResetPressedFlag = FALSE;
}

void UpdateKeyMask(UINT32 KeyMode)
{

   switch (KeyMode)
   {
      case POWERCALMODEMASK:
         HS_status = TRUE;
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK);
         break;

      case POWERABORTMASK:
         HS_status = TRUE;
         KeyMask = GOBACKKEYMASK;
         break;

      case CALMODEMASK:
         HS_status = TRUE;
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK
                     | TESTKEYMASK | LEFTKEYMASK | RIGHTKEYMASK);
         break;

      case DISABLESEL3:
         HS_status = TRUE;
         KeyMask = ~(HORNDOWNKEYMASK | SETUPKEYMASK | PRINTKEYMASK
                     | RUNKEYMASK | UPKEYMASK | DOWNKEYMASK
                     | SELECT3KEYMASK | SELECT1KEYMASK | TESTKEYMASK
                     | LEFTKEYMASK | RIGHTKEYMASK);
         break;

      case DIGTUNEMASK:
         HS_status = TRUE;
         KeyMask = GOBACKKEYMASK | SELECT2KEYMASK | SELECT3KEYMASK;
         break;

      case HDMODEMASK:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED & ~( TESTKEYMASK);//RESETKEYMASK |
         break;

      case TESTMODEMASK:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED & (~HORNDOWNKEYMASK);
         break;

      case WELDMODEMASK:
      default:
         HS_status = TRUE;
         KeyMask = ALLKEYSENABLED;
         break;

      case HSMASK:
         HS_status = FALSE;
         KeyMask =  GOBACKKEYMASK;
         break;
      case HSSUBMENUMASK:
         HS_status = TRUE;
         KeyMask =  GOBACKKEYMASK | SELECT1KEYMASK | SELECT2KEYMASK | SELECT3KEYMASK |
                    UPKEYMASK | DOWNKEYMASK ;
         break;
   }

}

