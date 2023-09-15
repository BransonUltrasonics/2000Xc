/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weld.h_v   1.8   16 Apr 2015 07:36:38   rjamloki  $ */
#ifndef WELD_H
#define WELD_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weld.h_v  $
 * 
 *    Rev 1.8   16 Apr 2015 07:36:38   rjamloki
 * Old trig_sw_signal is renamed to e_stop2_signal
 * 
 *    Rev 1.7   03 Mar 2015 15:41:24   rjamloki
 * included A1025.h for ESTOP_NEW_HW checking
 * 
 *    Rev 1.6   02 Jan 2015 04:18:40   rjamloki
 * e_stop hardware related changes
 * 
 *    Rev 1.5   21 May 2014 10:49:20   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------ MODULE DESCRIPTION -------------------------------

   Module name:

   Filename:      weld.h


            Written by: Laura Markure
                  Date: 3/18/96
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------




 ------------------------------- DESCRIPTION -----------------------------------


 Current values of welder ADC and DAC

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"
#include "A1025R.h"
/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*****     *****     General purpose variables     *****     *****/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/


// Inputs to the 332

extern UINT32 CurrentPowerIn;         /* Value being read by 7890          */
extern UINT32 CurrentAmpIn;           /* Value being read by 7890          */
extern UINT32 CurrentMemIn;           /* Value being read by 7890          */
extern SINT32 CurrentFreqIn;          /* Value being read by 7890          */
extern SINT32 CurrentPressure;        /* Current pressure                  */
extern SINT32 HomePressure;           /* Home pressure                  */
extern SINT32 CurrentForce;           /* Current pressure                  */
extern SINT16 ExtFreqOffset;          /* external frequency offset         */
extern UINT16 ExtAmp;                 /* external amplitude control        */





/*=======================================*/
/* INPUT PORT 0 BIT STRUCTURE DEFINITION */
/*=======================================*/

struct PORT0
 {
   UINT8      missing_part_signal     : 1,
              power_off_signal        : 1,
              power_on_signal         : 1,
              overload_input_signal   : 1,
              mem_clear_signal        : 1,
              mem_store_signal        : 1,
              seek_signal             : 1,
              run_signal              : 1;
 } ;

extern struct PORT0 Port0;
#define  MISSPARTINBIT (Port0.b7)
#define  PWROFFBIT     (Port0.b6)
#define  PWRONBIT      (Port0.b5)
#define  OLINBIT       (Port0.b4)
#define  MEMCLRBIT     (Port0.b3)
#define  MEMSTORBIT    (Port0.b2)
#define  SEEKBIT       (Port0.b1)
#define  RUNBIT        (Port0.b0)


/*=======================================*/
/* INPUT PORT 1 BIT STRUCTURE DEFINITION */
/*=======================================*/

struct PORT1
 {
   UINT8      spar_bite         : 1,  /* bit 7,  */
              e_stop_signal     : 1,  /* bit 6,  */
              pb2_signal        : 1,  /* bit 5,  */
              pb1_signal        : 1,  /* bit 4,  */
              ext_ls_signal     : 1,  /* bit 1,  */
              e_stop2_signal    : 1,  /* bit 0,  */
              uls_signal        : 1,  /* bit 2,  */
              int_ls_signal     : 1;  /* bit 3,  */
 } ;
 extern struct PORT1 Port1;
#define  SV4BIT        (PortB1.b7)
#define  SV3BIT        (PortB1.b6)
#define  SV2BIT        (PortB1.b5)
#define  SV1BIT        (PortB1.b4)
#define  TESTBIT       (PortB1.b3)
#define  OLRESETBIT    (PortB1.b2)
#define  RUNSONICBIT   (PortB1.b1)
#define  EXTSEEKBIT    (PortB1.b0)



/*=======================================*/
/* INPUT PORT 2 BIT STRUCTURE DEFINITION */
/*=======================================*/

struct PORT2
 {
    UINT8     cycle_abort_signal    : 1,  /* bit 7,  */
              user_input3_signal    : 1,  /* bit 6,  */
              user_input2_signal    : 1,  /* bit 5,  */
              user_input1_signal    : 1,  /* bit 4,  */
              external_reset_signal : 1,  /* bit 3,  */
              display_lock_signal   : 1,  /* bit 2,  */
              start_signal          : 1,  /* bit 1,  */
              ext_profile_tag_signal: 1;  /* bit 0,  */
 } ;

 extern struct PORT2 Port2;
#define  UNUSEDBIT     (Port2.b7)
#define  ESTOPBIT      (Port2.b6)
#define  PB2BIT        (Port2.b5)
#define  PB1BIT        (Port2.b4)
#define  EXTLLSBIT     (Port2.b3)
#define  TRIGSWBIT     (Port2.b2)
#define  ULSBIT        (Port2.b1)
#define  INTLLSBIT     (Port2.b0)



/*-----  Frequency  -----*/

extern SINT32  ActualFreqEnd;
#endif

/*
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/



/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/






