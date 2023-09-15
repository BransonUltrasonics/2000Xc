/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/qsm.h_v   1.7   21 May 2014 10:49:14   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/qsm.h_v  $
 * 
 *    Rev 1.7   21 May 2014 10:49:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:24   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:02   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:  

   Filename:      qsm.h


            Written by: Laura Markure  
                  Date: 3/14/96  
              Language:  "C"

 -------------------------------- REVISIONS ---------------------------------

 ------------------------------- DESCRIPTION --------------------------------


 

 ------------------------------ INCLUDE FILES -------------------------------
*/  
#ifndef QSM_H_
#define QSM_H_

#include "portable.h"
#include "assert.h"
#include "TLV5604.h"
#include "AT93C66.h"
#include "AD7890.h"
#include "LPC1758.h"
#include "AD7689.h"
#include "SPI.h"
#include "ADC.h"
#include "DAC.h"
/*
 ------------------------------- DEFINES ------------------------------------
*/
 
/*
 --------------------------- TYPE DECLARATIONS ------------------------------
*/                           

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void InitQsm(void);
//A1095R
class AD7689A1025: public AD7689 {
	  int TempChVals[8];
   public:
	  AD7689A1025(SPI *spi, int cs, int ctar, int MaxChNumForSequencing) :
		  AD7689(spi, cs, ctar, MaxChNumForSequencing)
      {
		  memset(TempChVals, 0, sizeof(TempChVals));
      }
      int ReadInput(int ch);
      void ReadInputsThroughSequencing(int * RawVal);
      //for testing voltage corresponding to raw values
      static double Volts(int ch, int RawVal);
};

class TLV5604A1025: public TLV5604 {
   public:
	  TLV5604A1025(SPI * spi, int cs, int ctar) :
            TLV5604(spi, cs, ctar)
      {
      }
      void WriteOutput(int ch, int raw);
      void WriteOutputs(int ch, int * raw);
};

extern AT93C66 * ActNvRam;
extern ADC * ActAdc;
extern DAC * PsDac;
extern ADC * PsAdc;
extern LPC1758 * ActLpc;
#endif
