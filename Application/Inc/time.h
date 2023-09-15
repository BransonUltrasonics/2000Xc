/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/time.h_v   1.5   21 May 2014 10:49:18   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/time.h_v  $
 * 
 *    Rev 1.5   21 May 2014 10:49:18   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:28   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

 -------------------------------- REVISIONS ------------------------------------



 ------------------------------- DESCRIPTION -----------------------------------

   This file defines prototypes for the real time clock

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

#ifndef TIME_H
#define TIME_H


/*********************************************************************/
/*  Timer structures                                                 */
/*********************************************************************/

struct t_date        {
        UINT16 year;  /* Year, A.D. */
        UINT8 month; /* Month, 1->12 */
        UINT8 day;   /* Day, 1->31 */
};

struct t_time        {
        UINT16 hour;    /* Hour, 0->23 */
        UINT8 minute;  /* Minute, 0->59 */
        UINT8 second;  /* Second, 0->59 */
};

struct time_ds        {
        struct t_date date;    /* Date */
        struct t_time time;    /* Time */
        UINT32 ticks;   /* Current Elapsed Ticks Between Seconds */
};


#endif     /* TIME_H */


