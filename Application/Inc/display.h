/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/display.h_v   1.4   28 Nov 2014 07:54:50   rjamloki  $ */
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

   Filename: display.h

   Function name:

 --------------------------------- REVISIONS --------------------------------


 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void ClearSync(void);
void SetSync(void);
void SetSync(void);
void DisplayResetMsg(void);
void RemoveNull(SINT8 string[]);
void UpdateScrollLEDs(SINT8 MaxIndex);
void InsertProperUnits(SINT8 text[], enum FORMAT UnitFlag);
void DisplayMenu(MENU list[]);
