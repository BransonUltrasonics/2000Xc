/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/NetworkManagerTask.h_v   1.11   27 Mar 2015 11:14:20   amaurya  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/NetworkManagerTask.h_v  $
 * 
 *    Rev 1.11   27 Mar 2015 11:14:20   amaurya
 * SBC_TIMEOUT macro changed to SBC_UDP_TIMEOUT as per review comment.UDP timeout increased to 10sec.
 * 
 *    Rev 1.10   21 Jan 2015 09:47:08   amaurya
 * LatchSBCReady and  SbcTimedOut member added to the networkmanager class to check SBC timeout.
 * 
 *    Rev 1.9   02 Jan 2015 04:17:04   rjamloki
 * SBC_TIMEOUT reduced to 5 seconds
 * 
 *    Rev 1.8   17 Nov 2014 10:12:34   RJamloki
 * Defined SBC Idle time out
 * 
 *    Rev 1.7   11 Jun 2014 12:57:52   rjamloki
 * MenuResponse size defined
 * 
 *    Rev 1.6   21 May 2014 10:49:12   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   07 May 2014 10:48:04   rjamloki
 * NetworkManagerTask class changed    
 * 
 *    Rev 1.4   05 Mar 2014 13:57:20   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:48:38   rjamloki
 * Header Fix.
 * 
 *    Rev 1.2   18 Dec 2013 10:04:50   rjamloki
 * Initial Test version.SBC to WC serial communication.
 * 
 *    Rev 1.1   05 Jun 2013 08:39:24   amaurya
 * Initial revision 2.
 * 
 *    Rev 1.0   03 Apr 2013 06:53:26   amaurya
 * Initial revision.
 *

 */

#ifndef NETWORK_MANAGERTASK_H_
#define NETWORK_MANAGERTASK_H_

#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "Dups_api.h"
#include "Serial.h"
#include "TcpIp.h"
#include "Ethernet.h"

//#define WCSBC_ONSERIAL

#define SOURCE_UDPPORT 46000
#define VGA_MENU_RESPONSEBUFF_SIZE 4096//make it big enough so that nobody never have to chase what's going where
#define SBC_UDP_TIMEOUT (10 * 1000 * 1000)//how long WC should wait before stopping cycles if SBC is not sending any thing.
									  //on UDP. value in define is in microseconds
class NetworkManagerTask : public Task
{
public:
   NetworkManagerTask(SINT32 Intf);
   static NetworkManagerTask *thisptr;
   ~NetworkManagerTask();
   SINT32 InterfaceNum;
   BOOLEAN CheckSBCTimeOut;//tells when we should start checking for time out
   SINT32 SbcTimeOutCounter;//counts the time out time in tick
   BOOLEAN LatchSBCReady;//what was sbc ready at timeout
   BOOLEAN SbcTimedOut;//timed out
protected:
   void Run();
   void Tick();
};
extern UINT8 * VGAMenuResponseBuff;
#endif
