/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/SC.H_v   1.4   06 Oct 2014 11:44:36   rjamloki  $ */
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

   Filename:      sc.h


            Written by: Laura Markure 
                  Date: 6/20/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define MANUAL 1
#define STARTSWITCHES 2
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void SCInit(UINT32);
void ManualSCInit(UINT32);
void SCEnterReady(void);
void RequestActCal(UINT32);
void InitSpringRate(void);
void WaitForSpringRate(void);
void CreateSpringRate(void);
void UpdateMessage(void);
void GetY2Dist(void);
void InitY2Deflection(void);
void CalDeflection(void);
void VerifyCalib(void);
void UpdateSpringRateTable(void);
void SelectManualSCSequence(void);
void SelectSCSequence(void);
void SCFinalCleanupArg(UINT32);
void SCFinalCleanup(void);
void StartCalPB(void);
void TestCalPB(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


