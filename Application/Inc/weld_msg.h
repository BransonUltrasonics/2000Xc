/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weld_msg.h_v   1.3   05 Mar 2014 13:57:44   rjamloki  $ */

#ifndef WELD_DATA_MSG_H
#define WELD_DATA_MSG_H
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: WELD_STATE_MSG

   Filename: wldstate.h 

 -------------------------------- REVISIONS ------------------------------------



 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"
#include "state.h"  
#include "weld_obj.h"  

/*
 ------------------------------- DEFINES ---------------------------------------
*/

								       

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/



typedef struct
    {  
    COMMON_MSG_FIELD_TYPE common;             
    UINT16                word1;
    UINT16                word2;
    WELD_DATA             *weld_data_ptr;
    UINT32                lword3;
    }__attribute__((__packed__))  WELD_DATA_MSG;

#endif /*  WELD_STATE_MSG_H */

