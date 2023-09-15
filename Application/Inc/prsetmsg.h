/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/prsetmsg.h_v   1.3   05 Mar 2014 13:57:28   rjamloki  $ */
#ifndef PRESET_PTR_MSG_H
#define PRESET_PTR_MSG_H
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

   Module name: GENERIC_PTR_MSG

   Filename: prsetmsg.h 


            Written by: Mark Lazarewicz  
                  Date: 1/24/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
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
   UINT32                partition_id; 
   UINT16                preset_number;
   UINT16                byte_count;
   void                 *msg_pointer;
   } PRESET_TABLE_MSG; 

#endif /* PRESET_PTR_MSG_H */
