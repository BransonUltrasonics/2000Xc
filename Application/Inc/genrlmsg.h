/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/genrlmsg.h_v   1.3   05 Mar 2014 13:57:08   rjamloki  $ */
#ifndef GENERIC_MSG_H
#define GENERIC_MSG_H
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

   Module name: GENERIC_MSG

   Filename: genrlmsg.h 

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
    ULONG lword1;
    ULONG lword2;
    ULONG lword3;
    } GENERIC_MSG;

#endif /*  GENERIC_MSG_H */
