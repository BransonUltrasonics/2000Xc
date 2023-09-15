/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/fpkp_msg.h_v   1.5   21 May 2014 10:49:04   rjamloki  $ */
#ifndef FP_USER_REQUEST_MSG_H
#define FP_USER_REQUEST_MSG_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/fpkp_msg.h_v  $
 * 
 *    Rev 1.5   21 May 2014 10:49:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:10   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:02   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:   front_panel_user_request_msg

   Filename:      fpkp_msg.h


            Written by: Mark Lazarewicz
                  Date: 1/28/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------

 This defines the FRONT_PANEL_USER_REQUEST_MSG

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

typedef struct
        {
         COMMON_MSG_FIELD_TYPE common;
         UINT8            user_request;
         UINT8                 spare_1;
         UINT16                spare_2;
         UINT32                spare_3;
         UINT32                spare_4;
        }  __attribute__((__packed__))FRONT_PANEL_USER_REQUEST_MSG;


/*
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif

