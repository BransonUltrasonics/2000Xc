/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/pwrcalb.h_v   1.3   05 Mar 2014 13:57:28   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1997                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Power Calibration                                           */
/*                                                                          */
/*                                                                          */
/*          Written by:   Laura Markure                                     */
/*                Date:   07-28-97                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void SelectPowerCalSequence(void);
void PowerCalInit(void);
void CheckPower(UINT32);
void PowerCleanupArg(UINT32);
void PowerCleanup(void);
void TurnOffSonics(UINT32);
void RequestCalPower(UINT32);
void ClearPwrFlg(void);
void ReadingPower(void);
void RecordPower1(UINT32);
void RecordPower2(UINT32);
void BuildPowerTable(UINT32);
UINT16 UpdatePowerTable(SINT16 TableVals[], UINT16 Y1, UINT16 Y2,
	  UINT16 X1, UINT16 X2);
void InitPwr(void);
void PowerCalAbort(void);
