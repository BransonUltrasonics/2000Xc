/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/PortManagerTask.h_v   1.5   27 Mar 2015 11:14:34   amaurya  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/PortManagerTask.h_v  $
 * 
 *    Rev 1.5   27 Mar 2015 11:14:34   amaurya
 * SBC_SERIAL_TIMEOUT added to keep the time interval of how long WC should wait before stopping cycles if SBC is not sending any thing.on serial. define value is in microseconds.
 * 
 *    Rev 1.4   11 Jun 2014 12:58:44   rjamloki
 * removed redundant tick function
 * 
 *    Rev 1.3   05 Mar 2014 13:57:24   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:39:32   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:12:01  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 06:56:38   amaurya
 * Initial revision.
 *

 */

#ifndef PORT_MANAGERTASK_H_
#define PORT_MANAGERTASK_H_

#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "Dups_api.h"
#include "Serial.h"

#define START_OF_MESSAGE 0x10  /* DLE */
#define DLE              0x10  /* DLE */
#define STX              0x02  /* STX */
#define END_OF_MESSAGE   0x03  /* ETX */
#define ETX              0x03  /* ETX */

#define SBC_SERIAL_TIMEOUT (5 * 1000 * 1000)//how long WC should wait before stopping cycles if SBC is not sending any thing.
									  //on serial. define value is in microseconds.
class PortManagerTask : public Task
{
public:
   PortManagerTask();
   static PortManagerTask*thisptr;
   ~PortManagerTask();
   Serial Port;
   BOOLEAN CheckSBCTimeOut;//tells when we should start checking for time out
   SINT32 SbcTimeOutCounter;//counts the time out time in tick
   BOOLEAN LatchSBCReady;//what was sbc ready at timeout
   BOOLEAN SbcTimedOut;//timed out
protected:
   void Run();
   void Tick();
};

#endif
