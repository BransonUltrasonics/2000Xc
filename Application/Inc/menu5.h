/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu5.h_v   1.3   05 Mar 2014 13:57:18   rjamloki  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu5.h

   Function name:


 --------------------------------- REVISIONS --------------------------------



 ------------------------------- DESCRIPTION ---------------------------------
*/ 

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/
extern SINT32 DebugLowValue;
extern SINT32 DebugHighValue;
void EnableWelding(void);
void InitSCMenus(void);
void InitManualSCMenus(void);
void SetCalDistanceFlag(UINT32);
void ClearCalDistanceFlag(UINT32);
void DryCycleSetup(UINT32);
void DryCycleCleanup(void);
void CancelColdStart(UINT32);
BOOLEAN DigitalPotEntry(void);
void DigitalTuneEntryScreen(void);
void IoTestData(UINT8);
extern void HornScanFunc(UINT32);
void RequestHornScan(UINT32);
BOOLEAN DigitalFreqEntry(void);
void UpdateResonanceStr(void);
