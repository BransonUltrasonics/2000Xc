/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/keypad.h_v   1.9   09 Jul 2014 13:07:40   rjamloki  $ */
#ifndef FP_KEY_PAD_H
#define FP_KEY_PAD_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/keypad.h_v  $
 * 
 *    Rev 1.9   09 Jul 2014 13:07:40   rjamloki
 * FakeKeyInt function removed.
 * 
 *    Rev 1.8   11 Jun 2014 12:55:06   rjamloki
 * renamed QVGA to VGA
 * 
 *    Rev 1.7   21 May 2014 10:49:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:14   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:26   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------


----------------------------- DESCRIPTIONS ------------------------------------

    
   

---------------------------- INCLUDE FILES ------------------------------------
*/
#include "portable.h"
#include "root.h"
#include "commnmsg.h"



#define KEY_0MASK       BIT0       
#define KEY_1MASK       BIT1        
#define KEY_2MASK       BIT2        
#define KEY_3MASK       BIT3        
#define KEY_4MASK       BIT4        
#define KEY_5MASK       BIT5        
#define KEY_6MASK       BIT6        
#define KEY_7MASK       BIT7        
#define KEY_8MASK       BIT8        
#define KEY_9MASK       BIT9        
#define DPOINTKEYMASK   BIT10       
#define INCKEYMASK      BIT11       
#define DECKEYMASK      BIT12       
#define CLEARKEYMASK    BIT13       
#define ENTERKEYMASK    BIT14       
#define SETUPKEYMASK    BIT15       
#define RESETKEYMASK    BIT16       
#define TESTKEYMASK     BIT17       
#define MAINKEYMASK     BIT18       
#define GOBACKKEYMASK   BIT19       
#define OFFKEYMASK      BIT20       
#define PRINTKEYMASK    BIT21       
#define HORNDOWNKEYMASK BIT22       
#define RUNKEYMASK      BIT23       
#define SELECT1KEYMASK  BIT24       
#define SELECT2KEYMASK  BIT25       
#define SELECT3KEYMASK  BIT26       
#define UNASSIGNED3MASK BIT27       
#define RIGHTKEYMASK    BIT28       
#define LEFTKEYMASK     BIT29       
#define UPKEYMASK       BIT30       
#define DOWNKEYMASK     BIT31       





/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


typedef  enum         /*  classification of errors in terms of  */
   {                            /*  hardware or software components       */

    KEY_0,                       /* 0x00 */ /* Keys 0-9 must be in sequence */
    KEY_1,                       /* 0x01 */
    KEY_2,                       /* 0x02 */
    KEY_3,                       /* 0x03 */
    KEY_4,                       /* 0x04 */
    KEY_5,                       /* 0x05 */
    KEY_6,                       /* 0x06 */
    KEY_7,                       /* 0x07 */
    KEY_8,                       /* 0x08 */
    KEY_9,                       /* 0x09 */
    DPointKey,                   /* 0x0a */
    IncKey,                      /* 0x0b */
    DecKey,                      /* 0x0c */
    ClearKey,                    /* 0x0d */
    EnterKey,                    /* 0x0e */
    SetupKey,                    /* 0x0f */
    ResetKey,                    /* 0x10 */
    TestKey,                     /* 0x11 */
    MainKey,                     /* 0x12 */
    GoBackKey,                   /* 0x13 */
    OffKey,                      /* 0x14 */
    PrintKey,                    /* 0x15 */
    HornDownKey,                 /* 0x16 */
    RunKey,                      /* 0x17 */
    Select1Key,                  /* 0x18 */  /* Select1, 2, 3 keys must be in sequence */
    Select2Key,                  /* 0x19 */
    Select3Key,                  /* 0x1a */
    UnAssigned3,                 /* 0x1b */
    RightKey,                    /* 0x1c */
    LeftKey,                     /* 0x1d */
    UpKey,                       /* 0x1e */
    DownKey,                     /* 0x1f */
    TermDataKey,                 /* 0x20 */
    TermSelectKey,               /* 0x21 */
    TermUpKey,                   /* 0x22 */
    TermDownKey,                 /* 0x23 */
    StateChangeFakeOut,          /* 0x24 */
    FIRSTCONTROLMESSAGE,         /* 0x25 */ /* Not sent, just a partition */
    NOKEY,                       /* 0x26 */
    UPDATEDISPLAY,               /* 0x27 */
    UPDATETOPLINE,               /* 0x28 */
    UPDATELINE2,                 /* 0x29 */
    UPDATELINE3,                 /* 0x2A */
    UPDATELINE4,                 /* 0x2B */
    TERMDATAOUTPUT,              /* 0x2C */
    UPDATETERMALARM,             /* 0x2D */
    ESTOPMSGON,                  /* 0x2E */
    ESTOPMSGOFF,                 /* 0x2F */
    CALIBRATION_ABORTED,         /* 0x30 */
    RestartMenu,                 /* 0x31 */
    VGACALIB_KEY,               /* 0X32 */ 
    ESTOPMSGRESET,               /* 0x33 */
    MAX_NUMBER_OF_KEY_CODES,     /* 0x33 */
   } __attribute__((__packed__))KEY_CODE_TYPE;

   typedef  struct
           {
            COMMON_MSG_FIELD_TYPE common;
            KEY_CODE_TYPE  key;
            UINT8          extra;
            UINT16         spare0;
            UINT32         spare1;
            UINT32         spare2;
           } __attribute__((__packed__))FP_KEY_PRESSED_MSG;

extern UINT32 FpkpQid;
#endif

