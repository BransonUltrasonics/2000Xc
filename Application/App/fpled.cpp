/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/fpled.cpp_v   1.3   10 Nov 2014 04:49:10   AnPawar  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/fpled.cpp_v  $
 * 
 *    Rev 1.3   10 Nov 2014 04:49:10   AnPawar
 * WriteBarGraph() changed
 * 
 *    Rev 1.2   11 Jun 2014 11:28:56   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.1   21 May 2014 03:04:34   rjamloki
 * removed redundant file inclusions
 * 
 *    Rev 1.0   14 Apr 2014 06:25:30   rjamloki
 * Initial revision.
 * 
 *    Rev 1.4   05 Mar 2014 13:56:28   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------
  Name: led.c
 ------------------------------- DESCRIPTION -----------------------------------

  UpdateLed is called from the Display Manager. CheckLedStatus is called from
  the welder ISR.

 ----------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"

#include "qsm.h"
#include "fpled.h"
#include "CPLD.h"

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

#define RESETBLINKRATE     480   /* # of calls Reset led is on/off   */
#define BARGRAPHBLINKRATE   5   /* # of calls Bargraph is on/off    */


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/
UINT8 ScrollingDown;
UINT8 ScrollingUp;
UINT16 DTLEDBits;

UINT16 ResetLedRequiredState = FALSE; /* FALSE:off   TRUE:on */

static BOOLEAN PowerUPBGraph;
static UINT16 LedUpperBits;
static UINT16 LedLowBits;
static UINT16 ResetLedCurrentState = FALSE; /* FALSE:off   TRUE:on */
static UINT16 ResetTimer;
static SINT16 LedCount = 0;//contains count of %d led to lit
static UINT16 LedIndex = 0;//index of table LedTable

static SINT16 GlobalPowerPercent = 0;


static UINT16 LedOn[] = { 0x0020, /* Reset Led                 */
   UPLEDBIT, /* Scroll Up Led             */
   DOWNLEDBIT, /* Scroll Down Led           */
   0x4000, /* Scroll Right Led          */
   0x2000, /* Scroll Left Led           */
   0x0800, /* Off Led                   */
   0x6000, /* Scroll Left/Right Led on  */
   0x0010, /* 0% On                     */
   (0x0020 | 0x0200 | 0x0400 | 0x4000 | 0x2000 | 0x0800 | 0x6000 | 0x0010), /* All leds (except bar) on  */
};

static UINT16 LedOff[] = { 0xffdf, /* Reset Led                 */
   ~UPLEDBIT, /* Scroll Up Led             */
   ~DOWNLEDBIT, /* Scroll Down Led           */
   0x0bfff, /* Scroll Right Led          */
   0x0dfff, /* Scroll Left Led           */
   0x0f7ff, /* Off Led                   */
   0x09fff, /* Scroll Left/Right Led off */
   0x0ffef, /* 0% Off                    */
   (0x0ffdf | 0xfdff | 0xfbff | 0x0bfff | 0x0dfff | 0x0f7ff | 0x09fff | 0x0ffef), /* All leds (except bar) off *//* All leds (except bar) off */
};

/*                            [14]   [15]                */
/*                            ----   ----                */

//Drive single led at once table
UINT16 LedTable[21][2] = { { 0x0080, 0x0000 }, /* 0%  off */
{ 0x0001, 0x001e }, /* 5%  */
{ 0x0002, 0x001e }, /* 10%  */
{ 0x0004, 0x001e }, /* 15%  */
{ 0x0008, 0x001e }, /* 20%  */
{ 0x0001, 0x001d }, /* 25%  */
{ 0x0002, 0x001d }, /* 30%  */
{ 0x0004, 0x001d }, /* 35%  */
{ 0x0008, 0x001d }, /* 40%  */
{ 0x0001, 0x001b }, /* 44%  */
{ 0x0002, 0x001b }, /* 50%  */
{ 0x0004, 0x001b }, /* 55%  */
{ 0x0008, 0x001b }, /* 60%  */
{ 0x0001, 0x0017 }, /* 65%  */
{ 0x0002, 0x0017 }, /* 70%  */
{ 0x0004, 0x0017 }, /* 75%  */
{ 0x0008, 0x0017 }, /* 80%  */
{ 0x0001, 0x000f }, /* 85%  */
{ 0x0002, 0x000f }, /* 90%  */
{ 0x0004, 0x000f }, /* 95%  */
{ 0x0008, 0x000f }/* 100%  */
};


/*
 ---------------------------------- CODE ---------------------------------------
*/
//#define INCLUDE_UNIT_TEST 1



#if INCLUDE_UNIT_TEST
void TestBarGraph(void);

#endif

void InitBarGraph(void)
{
   PowerUPBGraph = TRUE;
}

void WriteBarGraph(void) {
   // need to update only once
   if (PowerUPBGraph == TRUE) {
      LedUpperBits = 0xff3f;
      LedLowBits = 0x0000;
      PowerUPBGraph = FALSE;
   }
   if (LedIndex > LedCount)
      LedIndex = 0;

   if (LedIndex > 0) {
      LedUpperBits &= 0xfff0;
      LedUpperBits |= LedTable[LedIndex][0];
      LedLowBits = LedTable[LedIndex][1];
   }
   else {// zero percent led is sharing the ground with bottom four led
      LedLowBits &= 0xfffe;
   }

   LedIndex++;

   uint8 banks = (LedLowBits & 0x3F) | (LedUpperBits & BIT4 ? BIT7 : 0x00);
   // segments 0...3 in bits 0...3 and segment 2A (bit 5) in bit 4 in the latch
   uint8 segs = (LedUpperBits & 0x0F) | (LedUpperBits & BIT5 ? BIT4 : 0);
   CPLD::thisPtr->SetLatch(0, banks);
   CPLD::thisPtr->SetLatch(1, segs);

   GetLedStatus();
}

void UpdateLED(enum LEDS Led, UINT8 OffOn)
{

    if (Led <= ALLLEDS)
    {
        if (OffOn == OFF)
        {
            DTLEDBits &= (LedOff[Led]); /* BEK  05-28-97 */
        }
        else
        {
            DTLEDBits |= (LedOn[Led]);  /* BEK  05-28-97 */
        }

        LedUpperBits &= 0x008F; /* % leds */
        LedUpperBits |= (DTLEDBits & 0xFFF0);

        if (Led == RESETLED)
        {
            if (OffOn == ON)
            {
                ResetLedRequiredState = TRUE;
                ResetLedCurrentState = TRUE;
            }
            else
            {
                ResetLedRequiredState = FALSE;
                ResetLedCurrentState = FALSE;
            }
            ResetTimer = 0;
        }
    }
}

BOOLEAN GetLedStatus(enum LEDS led)
{
 return ((DTLEDBits & LedOn[led]) == LedOn[led]);
}

void GetLedStatus(void)
{

    if (ResetLedRequiredState == TRUE)
    {
        if (ResetTimer++ >= RESETBLINKRATE)
        {
            ResetTimer = 0;
            switch (ResetLedCurrentState)
            {
            case FALSE: /* Currently Off, need to turn on  */
                LedUpperBits |= LedOn[RESETLED];
                DTLEDBits |= LedOn[RESETLED];
                ResetLedCurrentState = TRUE;
                break;

            case TRUE:  /* Currently on, need to turn off  */
                LedUpperBits &= LedOff[RESETLED];
                DTLEDBits &= LedOff[RESETLED];
                ResetLedCurrentState = FALSE;
                break;
            }
        }
    }
}



void UpdateBarGraph(SINT16 PowerPercent)
{
   GlobalPowerPercent = PowerPercent;
   if (PowerPercent > 0) {
      PowerPercent = (PowerPercent / 5);
      if (PowerPercent > 20)
         PowerPercent = 20;
   } else {
      PowerPercent = 0;
   }
   LedUpperBits &= 0xfff0; /* Strip off lower bits     */
   LedCount = PowerPercent;
}

void SetBanks(UINT16 Value) {
   if ((Value & BIT0) == BIT0)
      CPLD::thisPtr->SetDout(Bank1, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank1, FALSE);

   if ((Value & BIT1) == BIT1)
      CPLD::thisPtr->SetDout(Bank2, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank2, FALSE);

   if ((Value & BIT2) == BIT2)
      CPLD::thisPtr->SetDout(Bank3, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank3, FALSE);

   if ((Value & BIT3) == BIT3)
      CPLD::thisPtr->SetDout(Bank4, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank4, FALSE);

   if ((Value & BIT4) == BIT4)
      CPLD::thisPtr->SetDout(Bank5, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank5, FALSE);

   if ((Value & BIT5) == BIT5)
      CPLD::thisPtr->SetDout(Bank6, TRUE);
   else
      CPLD::thisPtr->SetDout(Bank6, FALSE);

}

void SetSegs(UINT16 Value) {
   if ((Value & BIT0) == BIT0)
      CPLD::thisPtr->SetDout(Seg1A, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg1A, FALSE);

   if ((Value & BIT1) == BIT1)
      CPLD::thisPtr->SetDout(Seg1B, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg1B, FALSE);

   if ((Value & BIT2) == BIT2)
      CPLD::thisPtr->SetDout(Seg1C, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg1C, FALSE);

   if ((Value & BIT3) == BIT3)
      CPLD::thisPtr->SetDout(Seg1D, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg1D, FALSE);

   if ((Value & BIT4) == BIT4)
      CPLD::thisPtr->SetDout(Seg1H, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg1H, FALSE);

   if ((Value & BIT5) == BIT5)
      CPLD::thisPtr->SetDout(Seg2A, TRUE);
   else
      CPLD::thisPtr->SetDout(Seg2A, FALSE);
}

#if INCLUDE_UNIT_TEST

UINT16 PowerPercent;

void TestBarGraph(void)
{
#if INTEGRATION >= INT_P
   if (PowerPercent >= 21)
   PowerPercent = 0;
   LedCount = PowerPercent;
#endif
}

#endif
