/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/RemoteSerialCommandHandlerTask.cpp_v   1.12   27 Mar 2015 11:10:06   amaurya  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/RemoteSerialCommandHandlerTask.cpp_v  $
 * 
 *    Rev 1.12   27 Mar 2015 11:10:06   amaurya
 * Allocating memory for VGAAckBuf dynamically for 50 weld cycle.
 * 
 *    Rev 1.11   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.10   26 Sep 2014 03:14:26   rjamloki
 * Removed psos references
 * 
 *    Rev 1.9   11 Sep 2014 11:03:42   rjamloki
 * coverity fix , Increased task stack after increasing AckBuf size.
 * 
 *    Rev 1.8   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.7   11 Jun 2014 12:07:48   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 03:37:16   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   26 Mar 2014 12:31:06   rjamloki
 * RemoteSerialCommandHandlerTask::RemoteSerialCommandHandlerTask() changed
 * 
 *    Rev 1.4   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.3   05 Mar 2014 13:56:42   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:48   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  ---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

     Filename: RemoteSerialCommandHandlerTask.cpp
  -------------------------------- DESCRIPTION --------------------------------


  ------------------------------ INCLUDE FILES --------------------------------
*/
#include "RemoteSerialCommandHandlerTask.h"
#include "FIFO.h"
#include "qdef.h"
#include "command.h"
#include "serial.h"
#include "stdio.h"
#include "UndefPrintf.h"

#define RTCHTASK_FIFOSIZE 10

extern UINT32 RschQid;
extern UINT8 *VGAAckBuf;

RemoteSerialCommandHandlerTask *RemoteSerialCommandHandlerTask::thisPtr;

RemoteSerialCommandHandlerTask::RemoteSerialCommandHandlerTask() :
   Task("RTCH", T_SIZE_4096), RTCHTaskQ(RTCHTASK_FIFOSIZE, "RTCHQ")
/****************************************************************************/
/* Description:-                                                            */
/* RemoteSerialCommandHandlerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   RschQid = (UINT32) &RTCHTaskQ;
}

RemoteSerialCommandHandlerTask::~RemoteSerialCommandHandlerTask()
/****************************************************************************/
/* Description:-                                                            */
/* RemoteSerialCommandHandlerTask destructor                                              */
/****************************************************************************/
{

}

void RemoteSerialCommandHandlerTask::Run()
{
   RSCH_MSG_QUEUE_TYPE RschMsg;

   UINT16          i;
   UINT8           AckBuf[SERIAL_MAXACKLENGTH];
   UINT16          CommandCount;
   UINT16          Function;

   /* ActionFlags are used for commands that change more than 1 variable to
      defer the actions until all parameter limit tests have been performed.
      This is to prevent partial implementation of a command with a parameter
      error.   */
   UINT32          Value32;
   UINT32         *Host32;

   DelayMs(100);
   while (1)
   {
      /* wait forever for a message */
      RTCHTaskQ.Read(0, RschMsg, -1);

      /* initialize queue send indicator and byte check each pass */
      NackError = 0;    /* Assume valid command */
      CommandCount = (RschMsg.host_cmd.byte_count+9);
      /* The majority of commands have 1 32-bit parameter. */
      /* Computing Value32 here saves space by not doing it repeatedly later. */
      Host32 = (UINT32 *) RschMsg.host_cmd.data_pointer;
      Value32 = *Host32;

      Function = RschMsg.generic.common.opcode;


      if (Function < VGA_HOST_COMMAND)
      {
         i = ProcessHostCommand(Value32, Function,
                              (UINT8 *) RschMsg.host_cmd.data_pointer,
                              CommandCount, AckBuf, RschMsg.generic.common.source_task );
         SerialMessageQueue(AckBuf, i);
      }
      else
      {
         i = ProcessVGAHostCommand(Value32, Function,
                                (UINT8 *) RschMsg.host_cmd.data_pointer,
                                CommandCount);
         SerialMessageQueue(VGAAckBuf, i);
      }

   }/* end while forever */

}

void RemoteSerialCommandHandlerTask::Tick()
{
}

