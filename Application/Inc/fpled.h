/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/fpled.h_v   1.0   14 Apr 2014 06:27:50   rjamloki  $ */
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

   Module name:

   Filename:      led.h


            Written by: Laura Markure
                  Date: 5/13/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/
#ifndef LED_APP_H
#define LED_APP_H

/*------------------------------- DEFINES ----------------------------------*/

enum LEDS {

   RESETLED = 0,
   UPLED,
   DOWNLED,
   RIGHTLED,
   LEFTLED,
   OFFLED,
   LEFTRIGHTLEDON,
   ZEROPERCENTLED,
   ALLLEDS        };        /* This must be last, it is used as index check */


#define UPLEDBIT     0x200
#define DOWNLEDBIT   0x400

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/


/*
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


void InitBarGraph(void);
void WriteBarGraph(void);
void UpdateLED(enum LEDS, UINT8 OffOn);
void UpdateBarGraph(SINT16 PowerPercent);
void SetBanks(UINT16 Value);
void SetSegs(UINT16 Value);
void GetLedStatus(void);
BOOLEAN GetLedStatus(enum LEDS led);

extern UINT16 ResetLedRequiredState;

#endif
