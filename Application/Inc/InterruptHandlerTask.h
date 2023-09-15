/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/InterruptHandlerTask.h_v   1.4   11 Dec 2014 08:32:34   AnPawar  $
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/InterruptHandlerTask.h_v  $
 * 
 *    Rev 1.4   11 Dec 2014 08:32:34   AnPawar
 * CheckForClockLost function declaration in class.
 * 
 *    Rev 1.3   06 Mar 2014 11:04:04   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.2   05 Mar 2014 13:57:12   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.0   05 Jun 2013 08:46:42   amaurya
 * Initial revision.
Revision 1.2  2013/05/24 23:11:56  Ellery
*** empty log message ***

 *

 */

#ifndef INTERRUPT_HANDLERTASK_H_
#define INTERRUPT_HANDLERTASK_H_
#include "Task.h"
#include "portable.h"
#include "FIFO.h"

class Interrupt_HandlerTask: public Task
{
public:
   Interrupt_HandlerTask();
   ~Interrupt_HandlerTask();
   static Interrupt_HandlerTask *thisPtr;
   Fifo<SINT8> Interrupt_HandlerTaskQ;
protected:
   void CheckForClockLost(void);
   void Run();
};

#endif
