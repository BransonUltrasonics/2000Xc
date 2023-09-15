/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/RVTSHandlerTask.cpp_v   1.23   16 Apr 2015 07:18:04   rjamloki  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/RVTSHandlerTask.cpp_v  $
 * 
 *    Rev 1.23   16 Apr 2015 07:18:04   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.22   27 Mar 2015 11:10:42   amaurya
 * Allocating memory for VGAAckBuf dynamically for 50 weld cycle.
 * 
 *    Rev 1.21   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.20   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.19   28 Nov 2014 07:40:24   rjamloki
 * VGAEstopLoginFlag variable added.
 * 
 *    Rev 1.18   17 Nov 2014 10:06:04   RJamloki
 * Fixed if condition in RVTS Run
 * 
 *    Rev 1.17   10 Nov 2014 04:57:46   AnPawar
 * RVTSHandlerTask::Run() function changed.
 * 
 *    Rev 1.16   06 Oct 2014 06:43:46   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.15   26 Sep 2014 03:14:26   rjamloki
 * Removed psos references
 * 
 *    Rev 1.14   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.13   09 Jul 2014 11:33:38   rjamloki
 * Fixed Task Queue name. Removed Tick function.
 * 
 *    Rev 1.12   11 Jun 2014 12:07:50   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.11   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:37:50   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.9   23 Apr 2014 13:55:42   akaushal
 * Added a condition for sending data on serial .
 * 
 *    Rev 1.8   14 Apr 2014 09:40:04   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.7   26 Mar 2014 12:33:42   rjamloki
 * RVTSHandlerTask::RVTSHandlerTask(),RVTSHandlerTask::Run() changed
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

        Filename: RVTSHandlerTask.cpp
 -------------------------------- DESCRIPTION --------------------------------

 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "RVTSHandlerTask.h"
#include "FIFO.h"
#include "qdef.h"
#include "names.h"
#include "opcodes.h"
#include "commnmsg.h"                     /* Common message definition        */
#include "beep.h"
#include "keypad.h"
#include "root.h"
#include "ticks.h"
#include "util.h"
#include "menu.h"
#include "fpled.h"
#include "stdio.h"
#include "PortManagerTask.h"
#include "UndefPrintf.h"
#include "genrlmsg.h"
#include "weld_msg.h"
#include "param.h"
#include "rtclock.h"
#include "ascii.h"
#include "getmsg.h"
#include "command.h"
#include "ipsatype.h"
#include "NetworkManagerTask.h"

#define RVTSTASK_FIFOSIZE 10

RVTS_MSG_QUEUE_TYPE RvtsMsgQueue;
UINT32 RvtsQid;
UINT8 * VGAAckBuf;
UINT32 VgaQid;
BOOLEAN StartwithRunMenu;
BOOLEAN VGAWelderStateChange = FALSE;
BOOLEAN VGATestKeyPressed = FALSE;
BOOLEAN VGAEstopOn = FALSE;
BOOLEAN VGAEstopOff = FALSE;
BOOLEAN VGAEstopLoginFlag = FALSE;
BOOLEAN VGAEstopReset = FALSE;
BOOLEAN VGACalibKey = FALSE;
BOOLEAN VGACalAborted = FALSE;
BOOLEAN VGAWeldStartData = FALSE;
BOOLEAN VGACommStarted = FALSE;
BOOLEAN VGAColdStart;
BOOLEAN VGAPowerUpDelay;
extern UINT32 RvtsQid;
extern RVTS_MSG_QUEUE_TYPE RvtsMsgQueue;
extern BOOLEAN ForceDigitalTuneTest;
extern BOOLEAN VGAWelderStateChange;
extern BOOLEAN VGATestKeyPressed;
extern BOOLEAN VGAEstopOn;
extern BOOLEAN VGAEstopOff;
extern BOOLEAN VGAEstopReset;
extern BOOLEAN VGACalibKey;
extern BOOLEAN VGACalAborted;
extern BOOLEAN VGACommStarted;

extern void VGAAlarmReset (UINT32 dummy);
extern void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage);
extern void VgaSerialMessageQueue(UART_CHANNEL * channel, UINT8 * data, UINT16 length);
void SerialSend(UART_CHANNEL * channel, UINT8 * data, UINT16 length);
RVTSHandlerTask *RVTSHandlerTask::thisPtr;

RVTSHandlerTask::RVTSHandlerTask() :
   Task("RVTS", T_SIZE_1024), RVTSTaskQ(RVTSTASK_FIFOSIZE, "RVTSQ")
/****************************************************************************/
/* Description:-                                                            */
/* RVTSHandlerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   RvtsQid = (UINT32) &RVTSTaskQ;
   VGAAckBuf = new UINT8[MAXACKLENGTH];
}

RVTSHandlerTask::~RVTSHandlerTask()
/****************************************************************************/
/* Description:-                                                            */
/* RVTSHandlerTask destructor                                              */
/****************************************************************************/
{

}

void RVTSHandlerTask::Run()
{
   UART_CHANNEL * channel;
   UINT16          CommandCount;
   UINT16          i;
   UINT32          Value32;
   UINT32          *Host32;
   UINT16          Function;
   DelayMs(100);
   // ok, we're done with initialization
   UpdateHWConfiguration(VGA, FALSE);

   while (TRUE)
   {
      RVTSTaskQ.Read(this, RvtsMsgQueue, -1);
      switch (RvtsMsgQueue.generic.common.opcode)
      {
         case OP_TOUCH_SCRN_MSG_READY:
          if(!VGACommStarted)
          {
             VGACommStarted = TRUE;
            UpdateBarGraph(0);
         }
            channel = RvtsMsgQueue.RvtsMsg.channel;
            /* initialize queue send indicator and byte check each pass */
            NackError = 0;    /* Assume valid command */
            CommandCount = channel->length + 9;
            /* The majority of commands have 1 32-bit parameter. */
            /* Computing Value32 here saves space by not doing it repeatedly later. */
            Host32 = (UINT32 *) channel->rxbuf;
            Value32 = *Host32;

            Function = channel->code;
           if (Function < VGA_HOST_COMMAND)
            /*Welder Host command */
            i = ProcessHostCommand(Value32, Function,
                                    (UINT8 *) channel->rxbuf,
                                    CommandCount, VGAAckBuf,
                                    RvtsMsgQueue.generic.common.source_task );
            else
            /*VGA host command for display on SBC*/
            i = ProcessVGAHostCommand(Value32, Function,
                                      (UINT8 *) channel->rxbuf,
                                      CommandCount);
            if((Function == GET_NETWORK_INFO) || (Function == SEND_SOFTWARE_VERSION))
            	SerialSend(channel, VGAAckBuf, i);
            else
            	VgaSerialMessageQueue(channel, VGAAckBuf, i);
          break;

         case OP_WELDER_STATE_CHANGE:   //Welder State Change message
            VGAWelderStateChange = TRUE;
            break;

         case START_WELD_DATA:   //Send Weld data
            Host32 = (UINT32 *) RvtsMsgQueue.host_cmd.data_pointer;
            Value32 = *Host32;
            NackError = 0;
            CommandCount = (RvtsMsgQueue.host_cmd.byte_count+9);
            Function = RvtsMsgQueue.generic.common.opcode;

            ProcessHostCommand(Value32, Function,
                               (UINT8 *) RvtsMsgQueue.host_cmd.data_pointer,
                               CommandCount, VGAAckBuf,
                               RvtsMsgQueue.generic.common.source_task );
            break;

         case OP_FRONT_PANEL_KEYPRESS:

            switch (RvtsMsgQueue.FPKeyMsg.key)
            {
               case TestKey:    // Test Key Pressed
                  ForceDigitalTuneTest = FALSE;
                  VGATestKeyPressed = TRUE;
               break;

               case ESTOPMSGON:   // Emergency Stop Pressed
                  VGAAlarmReset(0);
                  VGAEstopOn = TRUE;
                  VGAEstopOff = FALSE;
                  VGAEstopReset = FALSE;
               break;

               case ESTOPMSGOFF:    // Emergency Stop Released
                  VGAEstopOn = FALSE;
                  VGAEstopOff = TRUE;
                  VGAEstopReset = FALSE;
               break;

               case ESTOPMSGRESET:    // Reset Key pressed after Emergency Stop
                  VGAEstopReset = TRUE;
                  VGAEstopOff = FALSE;
                  VGAEstopOn = FALSE;
               break;

               case VGACALIB_KEY:   // Move to next Calibration menu
                  VGACalibKey = TRUE;
               break;

               case CALIBRATION_ABORTED:  // Calibration Aborted
                  VGACalAborted = TRUE;
               break;
               default:
            	   break;
            }
            break;

         case OP_VGAMENUTASK_MSG:   // Horn Down Messages
            Value32 = RvtsMsgQueue.MenuTaskMsg.message;
            ProcessRvtsMenuTaskMsg(Value32);
            break;
         default:
        	 break;
      }
   } //End of while
}

