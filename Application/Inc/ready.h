/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ready.h_v   1.14   16 Apr 2015 07:31:16   rjamloki  $ */
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ready.h_v  $
 * 
 *    Rev 1.14   16 Apr 2015 07:31:16   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.13   11 Mar 2015 09:23:48   amaurya
 * RejectAlarmEntry() changed to ConfirmRejectEntry();
 * 
 *    Rev 1.12   11 Feb 2015 06:46:08   amaurya
 * new functio declared RejectAlarmEntery()
 * 
 *    Rev 1.11   08 Jan 2015 03:10:34   AnPawar
 * Macro commented RECORD_ALARM_DEBUG
 * 
 *    Rev 1.10   17 Nov 2014 10:11:18   RJamloki
 * Defined pressure check timeout for PB state
 * 
 *    Rev 1.9   28 Jul 2014 13:03:56   rjamloki
 * Added PreReadyJump and PreReadyAlJump proto types
 * 
 *    Rev 1.8   09 Jul 2014 13:17:50   rjamloki
 * SV Renamed to PartClamp
 * 
 *    Rev 1.7   27 May 2014 10:21:34   amaurya
 * Included header file.
 * 
 *    Rev 1.6   21 May 2014 10:49:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:26   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:06   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:                                                             */

/* Filename:      ready.h                                                   */


/*---------------------------- REVISIONS -----------------------------------*/


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "ALARMS.h"
#include "weld_obj.h"
#include "command.h"

#define PRESSURE_CHECK_TIME1       250    /* how long to wait in ready before */
                                          /* checking system pressure    */
#define PRESSURE_CHECK_TIME2       250    /* how long to wait in ready before */
                                          /* repeatadly checking system pressure    */
#define IDLE_TO_DOWNSPEED_DISTANCE 750    /* Distance before switch from idle to downspeed value */
#define POWERUPREADYDELAY         2500    /* Wait this time after power up before   */
                                          /* Ready can go active                    */
#define PRINTERCHECKTIME          5000    /* In Not ready check printer this often  */
#define MAXWELDTIME              30000    /* Max. selectable weld on time           */
#define POWERDIV                    10
#define PRESSURE_CHECK_TIMEOUTPB  5000 /* How long the system pressure should be checked to be within limit
										 before raising the alarm
										*/
                             
extern UINT16 ExtTriggerDelayTimer;
extern SINT16 TriggerDelayTimer;
void   SetAlarmFlag(void);
UINT16 ClearAlarm(UINT32 code);
void   ClearAlarmFlag(void);
void   ClearAbort(void);
UINT16 CheckAlarmFlag(void);
void   EnterReady(void);
void   EnterTestReady(void);
void   TestReady(void);
void   TestReadyTest(void);
void   TestActClr(void);
void   ExitReady(void);
void   ExitAlReady(void);
void   ExitReadyTest(void);
void   StartPB(void);
void   TestPB(void);
void   ExitPB(void);
void   TriggerBeep(void);
void   AlarmExitPB(void);
void   EntryTrs1(void);
void   EntryTrs2(void);
void   ExitULS(void);
void   ExitULS1(void);
void   ExitTrs1F(void);
void   ExitTrs1D(void);
void   ExitTrs1(void);
void   ExitTrs2(void);
void   ExitUlsUp(void);
void   AlarmUls(void);
void   AlarmTrs1(void);
void   EPreReady(void);
void   TestPreReady(void);
void   EnterPTS(void);
void   TestPTS(void);
void   StartPTS(void);
void   TestForOverload(void);
void   TestTrs1F(void);
void   TestTrs1D(void);
void   TestTrs1(void);
void   TestTrs2D(void);
void   TestTrs2(void);
void   EnterUls(void);
void   TestUls(void);
void   EnterUlsUp(void);
void   TestUlsUp(void);
void   TestTest(void);
void   TestTestPreReady(void);
void   EnterTest(void);
void   ExitTest(void);

void   EnterFData(void);
void   SendFData(void);
void   UpdateAlarm(void);
UINT16 CheckIfResetRequired(void);
void   ClearCalibrationAlarms(void);
void   EnterUpstroke(void);
void   ExitUpstroke(void);
void   TestUpstroke(void);
void   ClearFinalResults(void);
void   PreReadyJump(void);
void   PreReadyAlJump(void);
BOOLEAN CheckForMissingPartMin(void);
BOOLEAN CheckForMissingPartMax(void);
void RecordErrorCode(enum ERRORCODE_ARG ErrorCodeArg);

UINT32 PwrTestFilter(UINT32);  
void EnterClearMem(void);
void PassClearMem(void);

void EnterExtTrigDly(void);
void TestExtTrigDly(void);
void EnterPartClamp(void);
void TestPartClampInput(void);
void ExitPartClampState(void);

// state functions for pretrigger delay
void TestPreTrigDelay1(void);
void EnterPreTrigDelay1(void);
void ExitPreTrigDelay1(void);
void AlarmPreTrigDelay1(void);
void TestPreTrigDelay2(void);
void EnterPreTrigDelay2(void);
void ExitPreTrigDelay2(void);
void AlarmPreTrigDelay2(void);
void ConfirmRejectEntry(void);
void   RecordAlarm(UINT32 code);	
void   RecordSetupAlarm(UINT32 AlarmCode);


extern WELD_DATA WeldingResults;
