/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/WeldManagerTask.h_v   1.9   10 May 2016 16:19:22   RJamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/WeldManagerTask.h_v  $
 * 
 *    Rev 1.9   10 May 2016 16:19:22   RJamloki
 * Define function for RS232
 * 
 *    Rev 1.7   09 Jul 2014 13:25:08   rjamloki
 * Removed redundant function from class.
 * 
 *    Rev 1.6   11 Jun 2014 13:01:50   rjamloki
 * moved declarations from there weldmngr.h and weldmngr.h removed
 * 
 *    Rev 1.5   21 May 2014 10:49:22   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.4   06 Mar 2014 11:04:04   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.3   05 Mar 2014 13:57:44   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:40:08   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:11:58  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 07:10:12   amaurya
 * Initial revision.
 *

 */

#ifndef WELDMANAGERTASK_H_
#define WELDMANAGERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "genrlmsg.h"
#include "prsetmsg.h"
#include "ipscdmsg.h"
#include "wldstate.h"
#include "portable.h"
#include "preset.h"
#include "weld_obj.h"

/* this union is comprised of the expected messages that will be sent */
/*  to this task */

typedef union
{
   GENERIC_MSG                     GenericMsg;
   PRESET_TABLE_MSG                PresetTablePtrMsg;
   HOST_COMMAND_MSG                host_cmd;
   WELD_STATE_MSG                  WeldMsg;
} WMGR_MSG_QUEUE_TYPE;


class WeldManagerTask: public Task {
public:
   WeldManagerTask();
   ~WeldManagerTask();
   static WeldManagerTask *thisPtr;
   Fifo<WMGR_MSG_QUEUE_TYPE> WELDMNGRTaskQ;
protected:
   void Run();
};
void WeldManager(void);
void UpdateRPreset(void);
void FormatRunScreenTopLine(void);
void ClearWeldingResultsAlarms(void);
void ClearFinalResultsAlarms(void);
void FormatDataLine(STR *DataLine, WELD_DATA *Results, UINT16 Metric);
void SendSerialPort(UINT16 Delimit);

extern UINT32 WmgrQid;
extern WELD_DATA FinalResults;
#endif
