/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/outports.cpp_v   1.10   11 Mar 2015 09:17:18   amaurya  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/outports.cpp_v  $
 * 
 *    Rev 1.10   11 Mar 2015 09:17:18   amaurya
 * comments added for InitializeOutputPorts().
 * 
 *    Rev 1.9   26 Jan 2015 20:03:08   rjamloki
 * Setting latch values before enabling them
 * 
 *    Rev 1.8   10 Nov 2014 04:54:44   AnPawar
 * Removed CPLD extern.
 * 
 *    Rev 1.7   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.6   21 May 2014 03:34:22   rjamloki
 * outputs are set to inactive state once at powerup
 * 
 *    Rev 1.5   21 Apr 2014 13:40:20   rjamloki
 * Code cleanup and initialisation code updated
 * 
 *    Rev 1.4   14 Apr 2014 10:22:12   rjamloki
 * Commented redundant InitializeOutputPorts.
 * 
 *    Rev 1.3   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

    Module name:

    Filename: outports.cpp

    Function name:

 ------------------------------- DESCRIPTION -----------------------------------

    This routine will write given value to the requested output port and also to
    the shadow register.

 ------------------------------- PSEUDO CODE -----------------------------------

   

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "qdef.h"
#include "outports.h"                      /* defs and function prototype for write/read */
#include "CPLD.h"
#include "digout.h"

/*  
 ------------------------------- LOCAL DEFINES ---------------------------------
*/

#define SYS_STARTUP_PASS 0
#define SYS_STARTUP_FAIL 1
#define NUM_CTRL_PORTS 3


/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/


UINT8 PortRegisterA;
UINT8 PortRegisterB;
UINT8 PortRegisterC;



/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/



/*
------------------------------------ CODE ---------------------------------------
*/

 
/*
 ------------------------------- DESCRIPTION -----------------------------------

     Enable Output Hardware Latches and set defaults.

*/

void InitializeOutputPorts(void)
{
	//Set the default output on latches.
	cpld->SetLatch(2, 0x00);
	//Set outputs to inactive at power up
	cpld->SetLatch(4, 0x39);//check Dout5 enum in CPLD.h file
	cpld->SetLatch(5, 0xE7);//check Dout6 enum in CPLD.h file
	//Enable latches
	cpld->SetDout(Latch_OE, false);
}

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "outports.ut"
#endif
/* FOR UNIT TEST ONLY */
