/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/spidd.h_v   1.8   09 Apr 2015 04:52:32   RJamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/spidd.h_v  $
 * 
 *    Rev 1.8   09 Apr 2015 04:52:32   RJamloki
 * Added InitForceEstimateBuffer extern
 * 
 *    Rev 1.7   06 Oct 2014 06:50:18   AnPawar
 * DigFilterAmp(),DigFilterPower() function declaration changed
 * 
 *    Rev 1.6   11 Jun 2014 13:00:52   rjamloki
 * renamed DigPot to DigTune
 * 
 *    Rev 1.5   21 May 2014 10:49:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:28   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:22   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      spidd.h


            Written by: Laura Markure 
                  Date: 4/01/96  
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
#ifndef SPIDD_H
#define SPIDD_H

void WritePVP(UINT16 PVPValue);    
void InitPVP(void);
void WritePSDAC(UINT16 Freq, UINT16 Amp);
void ReadPSADC(void);
void ReadACTADC(void);
void CenterDigTune(void);
void SetDigTune(void);

UINT16 GetSpringForce(void);
void CheckForHornChange(void);

UINT32 DigFilterAmp(UINT32);
UINT32 DigFilterPower(UINT32);
UINT32 DigFilterFreq(UINT16);
UINT32 PwrTestFilter(UINT32);
extern BOOLEAN InitForceEstimateBuffer;
#endif /* PORTABLE_H_ */
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
