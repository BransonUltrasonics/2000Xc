/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/statedrv.h_v   1.13   16 Apr 2015 07:31:16   rjamloki  $ */
#ifndef STATEDRV_H
#define STATEDRV_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/statedrv.h_v  $
 * 
 *    Rev 1.13   16 Apr 2015 07:31:16   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.12   11 Mar 2015 09:24:42   amaurya
 * StopDataTuningHD() declaration added.
 * 
 *    Rev 1.11   11 Feb 2015 06:40:52   amaurya
 * changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.10   08 Jan 2015 03:09:26   AnPawar
 * Macro commented SM_DEBUG
 * 
 *    Rev 1.9   03 Oct 2014 06:28:18   rjamloki
 * extern declarations for  SINT16 *CurrentIndexPointer; and  enum WELD_SEQUENCE_TYPE CurrentSequence
 * 
 *    Rev 1.8   07 Aug 2014 16:07:02   tayars
 * Added now state for downspeed tune.
 * 
 *    Rev 1.7   20 Jun 2014 13:35:42   rjamloki
 * Removed SelectSensorCalSequence function
 * 
 *    Rev 1.6   21 May 2014 10:49:18   rjamloki
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
-------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      statedrv.h



------------------------------ REVISIONS ------------------------------------


----------------------------- DESCRIPTION -----------------------------------




---------------------------- INCLUDE FILES ----------------------------------
*/  
#include "state.h"

/*
----------------------------- DEFINES ---------------------------------------
*/


/*-------------------------- Function Prototypes ---------------------------*/

void   StopAtEndOfCycle(void);
void   StartDataCollection(void);
void   StopDataCollection(void);
void   StopDataTuning(void);
void   StopDataTuningHD(void);
void   SendData(enum WELDSTATES State);
void   StateMachine(void);
void   PushIndex(void);
void   PopIndex(void);
void   SetIndex(SINT16);

UINT16 CheckStateMachine(void);

UINT16 GetStateMachineFlag(void);

void   ResetStateMachineIndex(void);
void   SetCurrentSequenceType(enum WELD_SEQUENCE_TYPE Type);
enum   WELD_SEQUENCE_TYPE GetCurrentSequenceType(void);
void   ResetCycleTimer(void);
void   InitWeldSequencer(void);
void   SelectWeldSequence(void);
void   SelectTestSequence(void);
void   Restart(void);
void   Nothing(void);
void   SelectDistanceCalSequence(void);
void   SelectPowerDownSequence(void);
void   ChangeDataStorage(void);
void   Init1msPts(void);
void ResetStateMachine(void);
void StopStateMachine(void);
UINT16 SetStateMachineFlag(UINT16 Flag);
void StartStateMachine(void);
extern SINT16 *CurrentIndexPointer;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern STATE    *WeldSequence[NMBR_OF_STATES];/* Current weld cycle definition */
#endif
