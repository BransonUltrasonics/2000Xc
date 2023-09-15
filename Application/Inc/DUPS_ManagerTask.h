/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/DUPS_ManagerTask.h_v   1.8   03 Oct 2014 06:22:32   rjamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/DUPS_ManagerTask.h_v  $
 * 
 *    Rev 1.8   03 Oct 2014 06:22:32   rjamloki
 * RefreshDUPSParam () function devclared
 * 
 *    Rev 1.7   09 Jul 2014 13:04:04   rjamloki
 * Removed Tick function.
 * 
 *    Rev 1.6   21 May 2014 10:49:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   06 Mar 2014 11:04:02   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:57:02   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 05:00:08   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:47:44   rjamloki
 * Header Fix.
 * 
 *    Rev 1.1   05 Jun 2013 08:38:54   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:11:56  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 06:41:56   amaurya
 * Initial revision.
 *

 */

#ifndef DUPS_MANAGERTASK_H_
#define DUPS_MANAGERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "Dups_api.h"
#include "Serial.h"

extern UINT32 DupsQid;
//struct ADCData;
class DUPS_ManagerTask: public Task
{
public:
   DUPS_ManagerTask();
   ~DUPS_ManagerTask();
   static DUPS_ManagerTask *thisPtr;
   Fifo<DUPS_MSGBUF>DUPS_ManagerTaskQ;
   Serial Port;
protected:
   void Run();
};
void RefreshDUPSParam ();
#endif
