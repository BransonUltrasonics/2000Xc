/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu0.h_v   1.5   28 Nov 2014 07:56:00   rjamloki  $ */
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

   Filename: menu0.h

   Function name:


 --------------------------------- REVISIONS --------------------------------



 ----------------------------- DEFINES------------------------------------
*/
#define USERIO       BIT1
#define ACTUATOR     BIT2
#define FRAM          BIT3
#define PRINTING     BIT4
#define TOUCHSCREEN  BIT5
#define GLOBAL       BIT6

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/
void RestoreDefaultConfirmScrn(UINT32 Default);
void SelectProperDefault(UINT32 Default);
