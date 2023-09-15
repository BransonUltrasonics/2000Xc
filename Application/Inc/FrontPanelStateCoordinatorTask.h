/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FrontPanelStateCoordinatorTask.h_v   1.5   21 May 2014 10:49:06   rjamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FrontPanelStateCoordinatorTask.h_v  $
 * 
 *    Rev 1.5   21 May 2014 10:49:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.4   05 Mar 2014 13:57:08   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:48:04   rjamloki
 * Header Fix.
 * 
 *    Rev 1.2   18 Dec 2013 10:04:50   rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1   05 Jun 2013 08:39:00   amaurya
 * Initial revision 2.
 * 
 *    Rev 1.0   03 Apr 2013 06:44:38   amaurya
 * Initial revision.
 *

 */

#ifndef FRONTPANELSTATECOORDINATORTASK_H_
#define FRONTPANELSTATECOORDINATORTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "genrlmsg.h"
#include "fpkp_msg.h"

typedef union
   {
   GENERIC_MSG                   GenericMsg;
   FRONT_PANEL_USER_REQUEST_MSG  KeyPress;
   } FPSC_QUEUE_MSG_TYPE;
   struct MenuMessage
   {
      UINT32 Msg;
      UINT32 Sender;
      UINT32 Unused1;
      UINT32 Unused2;
   };

class FrontPanelStateCoordinatorTask: public Task
{
public:
   FrontPanelStateCoordinatorTask();
   ~FrontPanelStateCoordinatorTask();
   static FrontPanelStateCoordinatorTask *thisPtr;
   Fifo<MenuMessage> FPSCTaskQ;
   void Tick();
protected:
   void Run();
};

#endif
