/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/RVTSHandlerTask.h_v   1.6   28 Nov 2014 07:56:24   rjamloki  $
*/
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/RVTSHandlerTask.h_v  $
 * 
 *    Rev 1.6   28 Nov 2014 07:56:24   rjamloki
 * VGAEstopLoginFlag variable added.
 * 
 *    Rev 1.5   09 Jul 2014 13:19:38   rjamloki
 * Removed redundant function from class.
 * 
 *    Rev 1.4   11 Jun 2014 13:00:04   rjamloki
 * moved stuffs from vga_task.h and vga_task.h removed
 * 
 *    Rev 1.3   05 Mar 2014 13:57:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:39:48   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:12:01  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 07:02:50   amaurya
 * Initial revision.
 *

 */

#ifndef RVTSHANDLERTASK_H_
#define RVTSHANDLERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "NetworkManagerTask.h"
#include "root.h"
#include "genrlmsg.h"
#include "weld_msg.h"
#include "vga_uart.h"
#include "ipscdmsg.h"
#include "keypad.h"

// VGA Menu Task message.
typedef struct {
   COMMON_MSG_FIELD_TYPE  common;
   UINT32  message;
   }VGAMENUTASK_MSG;

//Message queue definition for VGA Handler
typedef union
   {
     GENERIC_MSG               generic;
     WELD_DATA_MSG             WeldMsg;
     FP_KEY_PRESSED_MSG        FPKeyMsg;
     RVTS_MSG                  RvtsMsg;
     HOST_COMMAND_MSG          host_cmd;
     VGAMENUTASK_MSG          MenuTaskMsg;
   }  RVTS_MSG_QUEUE_TYPE;

class RVTSHandlerTask: public Task
{
public:
   RVTSHandlerTask();
   ~RVTSHandlerTask();
   static RVTSHandlerTask *thisPtr;
   Fifo<RVTS_MSG_QUEUE_TYPE> RVTSTaskQ;
protected:
   void Run();
};

extern UINT32 VgaQid;
extern BOOLEAN VGAEstopLoginFlag;
#endif
