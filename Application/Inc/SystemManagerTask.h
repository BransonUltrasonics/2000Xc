/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/SystemManagerTask.h_v   1.8   11 Jun 2014 13:01:16   rjamloki  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/SystemManagerTask.h_v  $
 * 
 *    Rev 1.8   11 Jun 2014 13:01:16   rjamloki
 * moved declarations from sysmngr.h and sysmngr.h removed
 * 
 *    Rev 1.7   21 May 2014 10:49:18   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   26 Mar 2014 12:45:50   rjamloki
 * removed Tick() from class
 * 
 *    Rev 1.5   06 Mar 2014 11:04:04   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:57:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 05:00:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:24   rjamloki
 * Header Fix.
 * 
 *    Rev 1.1   05 Jun 2013 08:39:56   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:11:59  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 07:05:52   amaurya
 * Initial revision.
 *

 */
#ifndef SYSTEMMANAGERTASK_H_
#define SYSTEMMANAGERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "commnmsg.h"
#include "genrlmsg.h"
#include "nvm_msg.h"
#include "prsetmsg.h"
#include "weld_msg.h"
#include "selctkey.h"

union SYSM_MSG_QUEUE_TYPE {
   GENERIC_MSG                     generic_msg;
   NVM_ACCESS_MSG                  NvmAccessMsg;
   PRESET_TABLE_MSG                PresetTablePtrMsg;
   WELD_DATA_MSG                   WeldMsg;
   EDIT_PARAM_MSG_QUEUE_TYPE       EditParamMsg;
};


extern UINT32 SysmQueueId;
class SystemManagerTask: public Task {
   public:
      SystemManagerTask();
      ~SystemManagerTask();
      static SystemManagerTask *thisPtr;
      Fifo<SYSM_MSG_QUEUE_TYPE> SysMNGRTaskQ;
   protected:
      void Run();
};

void SystemManager(void);
void BackupCurrentSetupChange(void);
void CheckHistoryPtrBound(void);
#endif

