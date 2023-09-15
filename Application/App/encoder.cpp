/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/encoder.cpp_v   1.9   10 Nov 2014 04:48:26   AnPawar  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1996                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/encoder.cpp_v  $
 * 
 *    Rev 1.9   10 Nov 2014 04:48:26   AnPawar
 * Removed CPLD extern
 * 
 *    Rev 1.8   09 Jul 2014 13:26:22   rjamloki
 * Fixed ZeroEncoder function to zero the encoder count.
 * 
 *    Rev 1.7   11 Jun 2014 11:28:56   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 03:02:04   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   07 May 2014 10:19:38   rjamloki
 * ReadEncoder() function changed.
 * 
 *    Rev 1.4   05 Mar 2014 13:56:22   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:45:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*
  ----------------------------- DESCRIPTION -----------------------------------

   This function read the TPU quadrature decode channels and returns the
   distance.

  -------------------------- INCLUDE FILES ------------------------------------
*/
/* System include files */
#include "portable.h"
#include "preset.h"
#include "state.h"
#include "CPLD.h"
#include "digout.h"

/* Function include files */

/*
---------------------------- LOCAL DEFINES  -----------------------------------
*/   

//#define INCLUDE_UNIT_TEST
#define MAX_MOVEMENT        300       // 30mm / second max allowed
#define OVERFLOW_VALUE      65535 - MAX_MOVEMENT
#define UNDERFLOW_VALUE     MAX_MOVEMENT



/*
--------------------------LOCAL TYPE DECLARATIONS -----------------------------
*/


/*
---------------------------- PRIVATE GLOBAL DATA ---------------------------
*/
static UINT32 VelBuffer[9] = {10000,10000,10000,10000,10000,0,0,0,0};
static UINT32 LastReading = 0;
static SINT32 AbsolutePositionmm;


/*
--------------------------------- CODE ----------------------------------------
*/



UINT32 ReadEncoder(void)
/****************************************************************************/
/*                                                                          */
/*  This function will read the encoder.  Because the encoder can be metric,*/
/*  we actually need 18 bits to handle the largest number.  The TPU channel */
/*  only gives us 16 bits.  Therefore, a test will be down to determine if  */
/*  we are about to underflow or overflow the 16-bit value.  If so, special */
/*  precautions will be taken to insure accuracy.                           */
/*                                                                          */
/****************************************************************************/
{
	static UINT32 TempPosition = 0;
    TempPosition = cpld->GetEncoderValue();
    if (CurrentSetup.USEncoder)
    	return TempPosition;
    else
    {
          AbsolutePositionmm = TempPosition;    /* At ULS record distance as is */
          LastReading = TempPosition;
          return (UINT32) (AbsolutePositionmm / 2.54);
    }
}



void ZeroEncoder(void)
/****************************************************************************/
/*                                                                          */
/*   This function will set the encoder to report a distance of zero.  This */
/*   is done by setting the LastReading = 0.                                */
/*                                                                          */
/****************************************************************************/
{
   cpld->ZeroEncoderValue();
   LastReading = 0;              /* Preload with above value            */
   AbsolutePositionmm = 0;       /* Real position in mm's               */
}



UINT16 GetCycleDist(void)
{
   return(0);
}


UINT32 VelocityEstimator(UINT32 NewEncoderPosition)
/***************************************************************************/
/* Estimate velocity during horn downstroke from encoder position readings */
/* taken at 1ms intervals.  The velocity estimator is called from ready.c. */
/* The filter coefficients are [-1/16,-1/4,-3/8,-1/4,0,1/4,3/8,1/4,1/16]/4.*/
/***************************************************************************/
{
UINT32 Temp,Out;
   
   VelBuffer[0] = VelBuffer[1];
   VelBuffer[1] = VelBuffer[2];
   VelBuffer[2] = VelBuffer[3];
   VelBuffer[3] = VelBuffer[4];
   VelBuffer[4] = VelBuffer[5];
   VelBuffer[5] = VelBuffer[6];
   VelBuffer[6] = VelBuffer[7];
   VelBuffer[7] = VelBuffer[8];
   VelBuffer[8] = NewEncoderPosition;
   Out = (VelBuffer[8] - VelBuffer[0]) >>2;
   Out = (Out + VelBuffer[7] + VelBuffer[5] - VelBuffer[3] - VelBuffer[1]) >>2;
   Temp = VelBuffer[6] - VelBuffer[2];
   return ( Out + (Temp>>1) - (Temp>>3) ) >>2;
      
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\encoder.ut"
#endif
/* End of include for unit test */
