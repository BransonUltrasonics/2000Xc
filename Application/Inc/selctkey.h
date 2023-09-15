/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/selctkey.h_v   1.6   09 Jul 2014 13:21:24   rjamloki  $ */
#ifndef SELCTKEY_H
#define SELCTKEY_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/selctkey.h_v  $
 * 
 *    Rev 1.6   09 Jul 2014 13:21:24   rjamloki
 * Added PARAM argument in UpdateCUrrentPresetAndSetup function.
 * 
 *    Rev 1.5   21 May 2014 10:49:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:28   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:12   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      selctkey.h



 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"
#include "menu.h"
#include "param.h"
#include "keypad.h"


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           



typedef struct
   {
   COMMON_MSG_FIELD_TYPE    common;
   EDIT_PARAM_TYPE          param_id;
   SINT32                   value1;
   UINT16                   value2;
   UINT16                   value3;
   } EDIT_PARAM_MSG_QUEUE_TYPE;

/*
 --------------------------- GLOBAL VARIABLES ----------------------------------
*/


/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void UpdateCurrentPreset(enum PARAM Id, SINT32 Value1, UINT16 Value2);
void UpdateCurrentPresetAndSetup(enum PARAM Id = PRSTPARMDEFID);
#endif
