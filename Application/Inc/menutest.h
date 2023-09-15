/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menutest.h_v   1.4   28 Nov 2014 07:56:30   rjamloki  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menuhorn.h

   Function name:


 --------------------------------- REVISIONS --------------------------------
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

BOOLEAN DoTestMode( UINT8 *ExitKey, BOOLEAN *DidTest );
void UpdateTestAmp(void);
void UpdateDiagScreen(void);
void InitTestBuffers(void);
