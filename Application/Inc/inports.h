/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/inports.h_v   1.12   26 Oct 2015 10:34:48   LMarkure  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/inports.h_v  $
 * 
 *    Rev 1.12   26 Oct 2015 10:34:48   LMarkure
 * Added LastInputP3 for external seek input
 * 
 *    Rev 1.11   27 Mar 2015 11:14:10   amaurya
 * Comment added for INPUT_CONFIRM_REJECT.
 * 
 *    Rev 1.10   11 Mar 2015 09:22:14   amaurya
 * INPUT_REJECT_ALARM changed to INPUT_CONFIRM_REJECT.
 * 
 *    Rev 1.9   11 Feb 2015 06:41:54   amaurya
 * changes for reject confirm input
 * 
 *    Rev 1.8   09 Jul 2014 13:06:56   rjamloki
 * SvInterlock reamed to PartClamp.
 * 
 *    Rev 1.7   21 May 2014 10:49:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:12   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:14   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

------------------------------ REVISIONS --------------------------------------


------------------------------- DESCRIPTION -----------------------------------

   This file defines language extensions for use with the Microtec "C" compiler.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#ifndef _INPORTS_H_INCLUDED_
#define _INPORTS_H_INCLUDED_

#include "portable.h"
#include "state.h"
#include "inputs.h"


typedef enum     { ESTOPBTN_RESET,              // alarm not active
                   ESTOPBTN_PRESSED,            // button pressed
                   ESTOPBTN_RELEASED            // button released but
								// alarm still active
                   } ESTOP_STATE;

extern ESTOP_STATE EStopState;

/* User Configurable Inputs */
#define INPUT_DISABLED            BIT0   // Disabled
#define INPUT_PRESET1             BIT1   // Select preset 1
#define INPUT_PRESET2             BIT2   // Select Preset 2
#define INPUT_PRESET3             BIT3   // Select Preset 3
#define INPUT_PRESET4             BIT4   // Select Preset 4
#define INPUT_PRESET5             BIT5   // Select Preset 5
#define INPUT_EXT_TRIGDELAY       BIT6   // External Trigger Delay.
#define INPUT_DISP_LOCK           BIT7   // Display Lock.
#define INPUT_EXT_TRIGGER         BIT8   // External Trigger
#define INPUT_SONICS_DISABLE      BIT9   // Sonics Disable.
#define INPUT_MEM_RESET           BIT10  // Memory Reset.
#define INPUT_PART_CLAMPED        BIT11  // Part Clamped
#define INPUT_SYNC_IN             BIT12  // Sync In 
#define INPUT_PART_PRESENT        BIT13  // Part Present
#define INPUT_CONFIRM_REJECT	  BIT14  //confirm reject


enum INPUT_PINS {
   J3PIN32 = 1,
   J3PIN33,
   J3PIN19,
   J3PIN17,
   J3PIN31,
   J3PIN1    };


/*
 --------------------------------- DEFINES -------------------------------------
*/

void  MonitorInputPorts(void);
UINT8 InitMonitorInputPorts(void);
void  GetInputData(INBITS *InputPort);
void MemStoreIntHandler(int vector, void * frame);
BOOLEAN IsConfigured (UINT16 SelectedInput);
extern INPUT_PORT_P0_UNION_TYPE LastInputP0;
extern INPUT_PORT_P1_UNION_TYPE LastInputP1;
extern INPUT_PORT_P2_UNION_TYPE LastInputP2;
extern INPUT_PORT_P3_UNION_TYPE LastInputP3;
#endif
