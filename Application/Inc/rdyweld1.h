/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/rdyweld1.h_v   1.3   05 Mar 2014 13:57:30   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996,97        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:   Ready/Weld/Hold                                           */

/* Filename:      Rdyweld1.h                                                */


/*---------------------------- REVISIONS -----------------------------------*/
/*                                                                          */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/


void DealWithHandHeldChange(void);
void TestPBHH(void);
void ExitPBHH(void);
void TestPreReadyHH(void);
void StartSonic1HH(void);
void CheckSonics1HH(void);
void CheckEnergyHH(void);
void CheckPPHH(void);
void CheckGdDetHH(void);
void StopSonic2HH(void);
void StopAllSonicHH(void);
void AlStopHH(void);
void StartNonTimeHH(void);
void TestABDlyHH(void);
void TestABTmeHH(void);
void StartSeekHH(void);
void CheckSeekHH(void);
void HHBeep(void);

