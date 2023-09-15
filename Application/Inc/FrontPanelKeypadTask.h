/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FrontPanelKeypadTask.h_v   1.8   16 Feb 2015 01:24:34   amaurya  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FrontPanelKeypadTask.h_v  $
 * 
 *    Rev 1.8   16 Feb 2015 01:24:34   amaurya
 * BOOLEAN ResetPressedFlag added in Frontpanelkeypad task to fix continuous alarm beep on reset key press
 * 
 *    Rev 1.7   11 Jun 2014 12:47:40   rjamloki
 * moved enums from FPK_TASK.h and removed FPK_TASK.h
 * 
 *    Rev 1.6   21 May 2014 10:49:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   06 Mar 2014 11:04:04   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:57:06   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 05:00:10   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:04   rjamloki
 * Header Fix.
 * 
 *    Rev 1.1   05 Jun 2013 08:39:00   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:11:55  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 06:44:32   amaurya
 * Initial revision.
 *

 */

#ifndef FRONTPANELKEYPADTASK_H_
#define FRONTPANELKEYPADTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"
#include "genrlmsg.h"
#include "keypad.h"

typedef union
{
   GENERIC_MSG                generic;
   FP_KEY_PRESSED_MSG         FpKeyPressedMsg;
}  FPKP_MSG_QUEUE_TYPE;

enum KEYMODE {
     WELDMODEMASK,                /* Any weld sequence                      */
     CALMODEMASK,                 /* Force or distance calibration          */
     SCMODEMASK,                  /* added actuator system calibration      */
     POWERCALMODEMASK,            /* added power calibration                */
     POWERABORTMASK,              /* added power abort                      */
     HDMODEMASK,                  /* Horn down sequence                     */
     TESTMODEMASK,                /* Test Mode sequence                     */
     POWERDOWNMODEMASK,           /* Power down sequence                    */
     DIGTUNEMASK,                  /* Power down sequence                    */
     DISABLESEL3,                 /* disable during calibration             */
     POWERUPMODEMASK,             /* Power up sequence                      */
     HSSUBMENUMASK,               /* Horn Scan Submenu Mask                 */
     HSMASK,                      /* Horn Scan abort                        */
     ESTOPMASK  };                /* Estop mask                             */

class FrontPanelKeypadTask: public Task
{
public:
   FrontPanelKeypadTask();
   ~FrontPanelKeypadTask();
   void Tick();
   static FrontPanelKeypadTask *thisPtr;
   Fifo<FPKP_MSG_QUEUE_TYPE> FrontPanelKeypadTaskQ;
protected:
   FPKP_MSG_QUEUE_TYPE message;
   BOOLEAN ResetPressedFlag;
   void Run();
};
void UpdateKeyMask(UINT32 KeyMode);
#endif
