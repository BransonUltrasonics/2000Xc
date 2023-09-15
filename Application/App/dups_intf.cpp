/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_intf.cpp_v   1.16   08 Jan 2015 03:18:20   AnPawar  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_intf.cpp_v  $
 * 
 *    Rev 1.16   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.15   10 Nov 2014 04:47:42   AnPawar
 * Comments added in getbyte()
 * 
 *    Rev 1.14   03 Oct 2014 05:55:12   rjamloki
 * DupsBid variable removed
 * 
 *    Rev 1.13   05 Sep 2014 04:40:04   rjamloki
 * getbyte function changed to substarct the right timeout value
 * 
 *    Rev 1.12   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.11   11 Jun 2014 11:28:56   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   21 May 2014 02:59:18   rjamloki
 * removed redundant file inclusions and code
 * 
 *    Rev 1.9   23 Apr 2014 13:47:02   akaushal
 * Removed unused variable
 * 
 *    Rev 1.8   21 Apr 2014 13:27:58   rjamloki
 * Code Cleanup
 * 
 *    Rev 1.7   14 Apr 2014 09:55:32   rjamloki
 * Commented DUPS QSPI functions
 * 
 *    Rev 1.6   26 Mar 2014 12:05:28   rjamloki
 * removed two unused macros.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:46   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:20   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:45:22   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Module name:   DUPS interface

 Filename:      dups_intf.c

 Function name:

 Written by: Ashish Sharma
 Date: 6/7/00
 Language:  "C"

 ------------------------------ DESCRIPTION -------------------------------

 This file deals with DUPS interface

 ----------------------------- INCLUDE FILES ------------------------------*/

#include "qdef.h"           /* general hardware defines, etc..   */
#include "dups_api.h"
#include "dups.h"

#include "portable.h"
#include "qsm.h"
#include "ascii.h"
#include "stdio.h"
#include "Serial.h"
#include "DUPS_ManagerTask.h"
#include "UndefPrintf.h"

/*---------------------------- EXTERNAL DATA -------------------------------*/

extern DUPS_CMDBUF DUPS_CmdBuf;
extern DUPS_RESPONSEBUF DUPS_RspBuf;
extern UINT16 OneMilTimer;

/*----------------------------- LOCAL DEFINES ------------------------------*/

/* M3100 local defines. These are bitmaps in configuration register of M3100 */
/* ls 4 bits for baud rate */
#define M3100_Baud19_2k 0x0009

/* Bit 4 - clear for 8 bits/word, set for 7 bits/word */
#define M3100_WordLen8  0x0000
#define M3100_WordLen7  0x0010

/* Bit 5 - clear for parity disabled */
#define M3100_PEen      0x0020
#define M3100_PEdis     0x0000

/* Bit 6 - clear for 1 stop bit, set for 2 stop bits */
#define M3100_ST1       0x0000
#define M3100_ST2       0x0040

/* Bit 7 - clear for disabling IrDA timing mode */
#define M3100_IRen      0x0080
#define M3100_IRdis     0x0000

/* Bit 8 - interrupt enable on transition on RX when in shutdown */
#define M3100_RAMen     0x0100
#define M3100_RAMdis    0x0000

/* Bit 9 - interrupt enable on received parity 1 */
#define M3100_PMen      0x0200
#define M3100_PMdis     0x0000

/* Bit 10 - interrupt enable on new data available in M3100 receive reg/FIFO */
#define M3100_RMen      0x0400
#define M3100_RMdis     0x0000

/* Bit 11 - interrupt enable on transmit buffer empty  */
#define M3100_TMen      0x0800
#define M3100_TMdis     0x0000

/* No interrupts enabled, bits 8-11 cleared */
#define M3100_IntsDis   0x0000

/* Bit 12 - set to enable software shutdown */
#define M3100_SHDN      0x1000

/* Bit 13 - receive FIFO enable */
#define M3100_FEN       0x0000

/* Bit 14 - transmit buffer empty when set */
#define M3100_TBE       0x4000

/* Bit 15 - new data available when set */
#define M3100_DA        0x8000

/* Bits 14 & 15 - define operation being performed with M3100 */
#define M3100_WConf     0xC000 /* Set both for write config */
#define M3100_RConf     0x4000 /* Bit 14 set for read config */
#define M3100_WData     0x8000 /* Bit 15 set for write data */
#define M3100_RData     0x0000 /* Clear both for read data */

/* Define constants for writing config bytes to M3100 */

#define M3100_InitConf  (M3100_Baud19_2k | M3100_WordLen8 | M3100_PEdis | M3100_ST1 | M3100_IRdis | M3100_IntsDis | M3100_FEN | M3100_WConf)
// Baud 19.2k,     8 bit word,      No parity,   1 stop bit, IR disabled,  Ints disabled,  Rx FIFO enabled,Write to config reg

#define M3100_RecInt    (M3100_Baud19_2k | M3100_WordLen8 | M3100_PEdis | M3100_ST1 | M3100_IRdis | M3100_RMen | M3100_FEN | M3100_WConf)
// Baud 19.2k,     8 bit word,      No parity,   1 stop bit, IR disabled,  Rec Int,   Rx FIFO enabled,Write to config reg

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

/*----------------------------- GLOBAL DATA --------------------------------*/

//Serial Port(1536*2, 1536);

/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/

/* Save QSPI registers */
UINT16 QSMRx[16];
UINT16 QSMTx[16];


UINT16 SavSpcr0;
UINT16 SavSpcr1;
UINT16 SavSpcr2;
UINT16 SavSpcr3;

UINT8 DupsCommStatus = 0;
UINT8 BytesToReceive;

/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/

/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/

void checktime(SINT16 *);
BOOLEAN getbyte(UINT8 *, SINT16 *);
enum DUPS_RESULTS DUPS_ReadP(UINT8*, SINT16*);
enum DUPS_RESULTS DUPS_WriteP(UINT8*, SINT16*);

/*------------------------------ CODE --------------------------------------*/

#define RETRY_COUNT 3
#define RETRY_TIMEOUT 500 /* milliseconds */

enum DUPS_RESULTS DUPS_DataXfer(void)
{
   enum DUPS_RESULTS Status;

   for (UINT8 Retry = 0; Retry < RETRY_COUNT; Retry++) {
      SINT16 Timeout = RETRY_TIMEOUT;
      Status = DUPS_WriteP((UINT8 *) &DUPS_CmdBuf, &Timeout);
      if (Status == DUPS_SUCCESS)
         Status = DUPS_ReadP((UINT8 *) &DUPS_RspBuf, &Timeout);
      if (Status == DUPS_SUCCESS)
         break;
   }

   return Status;
}

/*********************************************************************************/

#define DUPS_CMDHDRLEN 2

enum DUPS_RESULTS DUPS_WriteP(UINT8 *Outbuf, SINT16 *Time)
{
   DUPS_CMDBUF *CmdBuf = (DUPS_CMDBUF *) Outbuf;
   UINT8 Checksum = 0;
   UINT16 Cnt = 0;
   UINT16 outptr = 0;
    enum DUPS_RESULTS status = DUPS_SUCCESS;

   Cnt = CmdBuf->Count;

   for (outptr = DUPS_CMDHDRLEN; outptr < (Cnt + DUPS_CMDHDRLEN); outptr++)
      Checksum ^= Outbuf[outptr];

   Outbuf[outptr++] = Checksum;
   Outbuf[outptr++] = DLE;
   Outbuf[outptr++] = ETX;
   Cnt = outptr;
   outptr = 0;

   while ((*Time > 0) && (outptr < Cnt)) {
      if (DUPS_ManagerTask::thisPtr->Port.Send(0, Outbuf[outptr], -1)) {
         outptr++;
      }
      checktime(Time);
   } // while time left and data remains

   if (*Time > 0)
      status = DUPS_SUCCESS;
   else
      status = DUPS_TIMEOUT;
   return status;
} // end of DUPS_WRITE



/***********************************************************************************************/

#define DUPS_RESPHDR 5  /* ACK/NAK DLE STX Cnt Cnt */
#define DUPS_RESPCRC 3  /* CRC bytes start from 3rd */
#define DUPS_RESPTAIL 3 /* CRC DLE ETX - not counted in count field */

enum DUPS_RESULTS DUPS_ReadP(UINT8 *InBuf, SINT16 *time)
{
   DUPS_RESPONSEBUF *RespBuf = (DUPS_RESPONSEBUF *) InBuf;
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 inptr = 0;
   UINT8 inbyte;
   UINT8 chksum = 0;
   UINT16 cnt = 0;
   BOOLEAN BadLength = FALSE;
   RespBuf->Count = 0;
   InBuf[0] = 0;
   while ((inptr < DUPS_RESPHDR) && (*time > 0)) {
      if (getbyte(&inbyte, time)) {
         InBuf[inptr] = inbyte;
         if ((InBuf[0] == ACK) || (InBuf[0] == NAK)) //discard bytes till ACK/NACK received
               {
            inptr++;
         }
      }
      checktime(time);
   }
   /* limit maximum receive count to what's left in the receive buffer */
   /* ignore 3 first bytes that are not included in CRC */
   /* ignore 3 last bytes - CRC and trailer */
   RespBuf->Count &= 0xFFF; /* just mask off some bits that don't make sense at all */
   if (RespBuf->Count > (sizeof(DUPS_RESPONSEBUF) - DUPS_RESPCRC - DUPS_RESPTAIL)) {
      RespBuf->Count = sizeof(DUPS_RESPONSEBUF) - DUPS_RESPCRC - DUPS_RESPTAIL;
      BadLength = TRUE;
   }
   cnt = RespBuf->Count + DUPS_RESPTAIL - sizeof(RespBuf->Count);
   while ((*time > 0) && (cnt > 0)) {
      if (getbyte(&inbyte, time)) {
         InBuf[inptr++] = inbyte;
         cnt--;
      }
      checktime(time);
   }
   /* calculate CRC only if not bad data and no timeout */
   if ((BadLength == FALSE) && (*time > 0)) {
      for (inptr = DUPS_RESPCRC; inptr < DUPS_RESPCRC + RespBuf->Count; inptr++)
         chksum ^= InBuf[inptr];
   }
   if (*time <= 0)
      status = DUPS_TIMEOUT;
   else if (RespBuf->ACK_NACK == NAK)
      status = DUPS_NACK;
   else if ((chksum != InBuf[DUPS_RESPCRC + RespBuf->Count]) || (BadLength == TRUE))
      status = DUPS_CHECKSUM;
   return status;
} // end of readP

void checktime(SINT16 *inval)
{
   static UINT16 lasttime = 0;
   if (lasttime != OneMilTimer)
      (*inval)--;
   lasttime = OneMilTimer;
} // end of checktime



BOOLEAN getbyte(unsigned char *indata, SINT16 *time)
{
   BOOLEAN status = TRUE;
   unsigned char ch = 0;
   /* declared to reduce the waiting time by 9ms if a character is not received*/
   int TimeOut = 10;//ms while waiting for character from serial driver
   status = DUPS_ManagerTask::thisPtr->Port.Receive(0, ch, TimeOut);
   *indata = ch;
   /*reduce the waiting time per command by 9ms if a character is not received
   other 1 ms is reducing in checktime function*/
   if(!status)
	   *time -= (TimeOut - 1);

   return status;
}
