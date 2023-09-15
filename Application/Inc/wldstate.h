/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/wldstate.h_v   1.3   05 Mar 2014 13:57:44   rjamloki  $ */

#ifndef WELD_STATE_MSG_H
#define WELD_STATE_MSG_H
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
    enum WELDSTATES       state;
    UINT16                weld_samples;
    WELD_OBJECT          *weld_object_ptr;
    UINT32                lword3;
    } WELD_STATE_MSG;

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    enum WELDSTATES       state;
    UINT16                weld_samples;
    WELD_DATA             *weld_data_ptr;
    UINT32                lword3;
    } END_WELD_MSG;

typedef struct 
    {  
    COMMON_MSG_FIELD_TYPE common;             
    enum WELDSTATES       state;
    UINT16                weld_samples;
    SETUP_DATA_ALARMS     *setup_data_ptr;
    UINT32                lword3;
    } START_WELD_MSG;

#endif /*  WELD_STATE_MSG_H */
