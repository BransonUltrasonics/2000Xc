/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/RemoteSerialCommandHandlerTask.h_v   1.4   06 Mar 2014 11:04:04   rjamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/RemoteSerialCommandHandlerTask.h_v  $
 * 
 *    Rev 1.4   06 Mar 2014 11:04:04   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.3   05 Mar 2014 13:57:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:39:44   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:11:59  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 07:01:24   amaurya
 * Initial revision.
 *

 */

#ifndef REMOTESERIALCOMMANDHANDLERTASK_H_
#define REMOTESERIALCOMMANDHANDLERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "genrlmsg.h"
#include "ipscdmsg.h"

/* inbound messages to the mich queue */
union RSCH_MSG_QUEUE_TYPE {
  GENERIC_MSG     generic;
  HOST_CMD_WELD_MSG host_cmd;
};

class RemoteSerialCommandHandlerTask: public Task {
public:
   RemoteSerialCommandHandlerTask();
   ~RemoteSerialCommandHandlerTask();
   static RemoteSerialCommandHandlerTask *thisPtr;
   Fifo<RSCH_MSG_QUEUE_TYPE> RTCHTaskQ;
   void Tick();
protected:
   void Run();
};

#endif
