/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/interpol.h_v   1.3   05 Mar 2014 13:57:10   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      interpol.h


            Written by: Laura Markure 
                  Date: 5/15/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

SINT16 GetInterpolatedSINT16(SINT16 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedUINT16(UINT16 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedUINT32(UINT32 table_vals[], UINT16 data_in);
UINT16 GetInterpolatedSINT32(SINT32 table_vals[], UINT16 data_in, SINT16 Offset);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


