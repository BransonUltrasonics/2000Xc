/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/estop.cpp_v   1.11   08 Jan 2015 03:18:20   AnPawar  $ */
/****************************************************************************/ 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/estop.cpp_v  $
 * 
 *    Rev 1.11   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.10   06 Oct 2014 06:32:06   AnPawar
 * removed ck_qsend.h,RVTSHandlerTask.h file inclusion.
 * Using cygos function for queue read write.
 * 
 *    Rev 1.9   03 Oct 2014 06:02:40   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.8   11 Jun 2014 11:28:56   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:47:54   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:22   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: estop.c
 ---------------------------- DESCRIPTION -----------------------------------


 This module contains the functions for dealing with E-stop.             


 --------------------------- INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "state.h"
#include "menu.h"
#include "beep.h"
#include "digout.h"
#include "statedrv.h"
#include "keypad.h"
#include "selctkey.h"
#include "getmsg.h"
#include "ticks.h"

#include "opcodes.h"
#include "stdio.h"
#include "RVTSHandlerTask.h"

/*
  ------------------------- EXTERNAL DATA ----------------------------------
*/

extern INBITS Inp;
extern UINT16 EstopHistoryFlag;
/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              

#define ESTOPBLINKONTIME    200       /* Emergency stop blink on time      */
#define ESTOPBLINKOFFTIME   200       /* Emergency stop blink off time     */


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

SINT16 EstopCountDown = ESTOPBLINKONTIME;
SINT16 EstopState = OFF;

/*
 ------------------------------- CODE ------------------------------------
*/


void ProcessEstop(void)
/***************************************************************************/
/*                                                                         */
/*  This function will actually blink Emergency Stop on the display if it  */
/*  is needed.  All timing will be done here.                              */
/*                                                                         */
/*  Currently, the display will be restored to the previous menu when Estop*/
/*  is removed.                                                            */
/*                                                                         */
/***************************************************************************/
{

   FP_KEY_PRESSED_MSG           FPKeyMsg;
   
   if ((Inp.Estop == TRUE) && (EstopHistoryFlag == TRUE)){
      if(EstopCountDown-- < 0)
      {
         switch (EstopState)
         {
            case OFF:                            /* Estop was off          */
               EstopState = ON;
               SendFakeKeyPress(ESTOPMSGON);
               if(IsHWConfigured(VGA))
               {
                  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                  FPKeyMsg.key = ESTOPMSGON;
                  RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 10);
               }
               break;
      
            case ON:                             /* Estop was on           */
               EstopState = OFF;
               SendFakeKeyPress(ESTOPMSGOFF);
               if(IsHWConfigured(VGA))
               {
                  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                  FPKeyMsg.key = ESTOPMSGOFF;
                  RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 10);
               }
               break;
         }
         EstopCountDown = ESTOPBLINKONTIME;

      }
   }

}
