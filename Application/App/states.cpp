/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/states.cpp_v   1.26   27 Mar 2015 11:11:32   amaurya  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/states.cpp_v  $
 * 
 *    Rev 1.26   27 Mar 2015 11:11:32   amaurya
 * Changed ConfirmRejectST state from NOP to CONFIRMREJECTSTATE.
 * 
 *    Rev 1.25   11 Mar 2015 09:19:28   amaurya
 * RejectAlarmSST[] name chaged to ConfirmRejectSST[].
 * 
 *    Rev 1.24   11 Feb 2015 06:39:00   amaurya
 * hanges for reject confirm input
 * 
 *    Rev 1.23   21 Jan 2015 09:37:40   amaurya
 * True Action of SSTATES WaitPartClampInput,CalWaitUls1,WaitUls1,PreTrigger,WaitTrs1,WaitTrs1PT,WaitTrs2,WaitTrs2PT changed to ABORT.
 * 
 *    Rev 1.22   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.21   28 Nov 2014 07:41:16   rjamloki
 * Code clean up.Removed unused variables.
 * 
 *    Rev 1.20   17 Nov 2014 10:41:26   RJamloki
 * Not checking for uls abort in trigger state
 * 
 *    Rev 1.19   06 Oct 2014 06:46:38   AnPawar
 * DUPS_ManagerTask.h file included.Using cygos function for queue read write.
 * 
 *    Rev 1.18   03 Oct 2014 05:58:02   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.17   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.16   05 Sep 2014 05:13:40   rjamloki
 * Using EQ alarms instead of NC for Part Present and Part Clamp active after cycle.
 * 
 *    Rev 1.15   07 Aug 2014 15:45:36   tayars
 * Added new state for the downspeed tuning
 * 
 *    Rev 1.14   28 Jul 2014 12:55:14   rjamloki
 * Added support for udi scan and horn clamp
 * 
 *    Rev 1.13   09 Jul 2014 11:41:56   rjamloki
 * Renamed svinterlock to part clamp. Added suuport for Part Present.
 * 
 *    Rev 1.12   20 Jun 2014 14:22:48   rjamloki
 * Added Force and Pressure calibration states for AES.
 * 
 *    Rev 1.11   11 Jun 2014 12:13:02   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   21 May 2014 10:52:48   rjamloki
 * Added Substates for trigger by distance
 * 
 *    Rev 1.9   21 May 2014 03:41:52   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.8   14 Apr 2014 10:18:16   rjamloki
 * Removed unused QSMmap from TestPO5
 * 
 *    Rev 1.7   26 Mar 2014 12:37:40   rjamloki
 * removed macro
 * 
 *    Rev 1.6   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:46   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:52   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module Name: States                                                      */
/*                                                                          */
/* Filename:    States.c                                                    */
/*                                                                          */
/* Function name: Weld Sequence State Machine                               */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/  
                                                                              

                                                                            
/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define ONE_SECOND         1000 /* 1 second in ms                           */
#define AMPCHANGE             2 /* Min change in percent for seek           */
#define FREQCHANGE           10 /* Min change in hertz for freq during seek */
#define SEEK_ON_TIME         20 /* Power up seek on time                    */
#define SEEK_OFF_TIME        30 /* Power up seek off time                   */
#define SEEK_RETRIGGER_TIME  (SEEK_ON_TIME + SEEK_OFF_TIME)
#define SEEK_TIME          1000 /* Amount of time to retrigger seek         */
#define LONG_SEEK_TIME      250 /* Min amount to be considered long         */ 
#define SHORT_SEEK_TIME      50 /* Min amount to be considered short        */ 
#define SAFETY_SEEK_TIME   2000 /* Make sure we dont get stuck              */
#define ACTUATOR_TIME      2000 /* 2 seconds needed for pressure averaging  */

/*------------------------------ INCLUDES ----------------------------------*/

#define  STATES
#include "portable.h"
#include "state.h"
#include "keyPad.h"
#include "selctkey.h"
#include "mansensr.h"
#include "preset.h"
#include "states.h"
#include "command.h"
#include "qsm.h"
#include "digout.h"
#include "fpled.h"
#include "beep.h"
#include "weld_obj.h"
#include "weld.h"
#include "genalarm.h"
#include "getmsg.h"
#include "powrdwn.h"
#include "weldhold.h"
#include "spidd.h"
#include "menuhorn.h"
#include "menucalb.h"
#include "util.h"
#include "dups_api.h"
#include "rdyweld1.h"
#include "spidd.h"
#include "outports.h"
#include "menu7.h"
#include "stdio.h"
#include "snsrcalb.h"
#include "UndefPrintf.h"
#include "DUPS_ManagerTask.h"

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern INBITS  Inp;
extern BOOLEAN UlsTimeout;
extern SINT16  CalTimer;
extern SINT16  NumberOfBeeps;    
extern UINT16 AlarmCounter;

extern BOOLEAN PlsWaitTimerFlag;                  /* Please Wait Timer Flag */
extern BOOLEAN TriggerLostFlag;
extern BOOLEAN PoweredUp;
extern BOOLEAN JustPoweredUpFlag;

extern BOOLEAN DiagStopFlag;

extern SINT32  CurrentFreqIn;
extern UINT32  ActualPeakPower;
extern UINT16  TenVoltRef,FreqControlExternal;
extern BOOLEAN MissingPartFlag;
extern BOOLEAN AdvanceMenuFlag;
extern SINT32    FreqChg;
extern UINT16 MicroHomeForce;
  
UINT16 PowerUpTimer;
UINT16 PowerUpSeekTimer;
UINT16 PowerSupplyOk; 
UINT16 MenuSyncTimer;
UINT16 JustPoweredUpTimer;
UINT16 SeekTime;              /* Actual time for seek vs dip switch setting */
UINT16 PressureCounter = 0;
UINT16 PressureTimer = 0;
UINT16 PressureFlag;
//DUPS_MSGBUF DUPS_MsgBuf;

BOOLEAN  ActDone, PSDone;
BOOLEAN  ControlsDone, StackDone;
static BOOLEAN PowerUpOL = FALSE;
UINT16 PSFailCode = 0x07;    /* BIT0, BIT1 and BIT2 Assume all will fail */


UINT32 PowerUpFreq;

BOOLEAN ParamUpdateFlag;
BOOLEAN PowerDownAborted = FALSE;

extern BOOLEAN ReadyOK;
extern BOOLEAN ECycleHistFlag;
extern BOOLEAN TrgDelayTimeout;
extern BOOLEAN PartClampTimeout;

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

extern BOOLEAN   IsThereAGraphPrinting;
extern BOOLEAN WaitForRejectConfirm;

/*-------------------------- Function Prototypes ---------------------------*/

#include "states.h"
#include "ready.h"
#include "weldhold.h"
#include "statedrv.h"
#include "mansensr.h"
#include "snsrcalb.h"
#include "psnvram.h"
#include "sc.h"
#include "display.h"


/*-------------------------------- CODE ------------------------------------*/

/*---------------------------  Data Structures  ----------------------------*/


/*****     *****     Here is an actual test weld cycle     *****     *****/

/*                         Variable           TRUE    FALSE   Alarm   Trace  */
/*                         pointer            Action  Action  Code    Code   */
/*                         ----------         ------- ------- ------- ------ */
SSTATES Initial[]       = {{&SystemOK,         JUMP,   ALJUMP, NONE,   100},
                           {&TimerFlag,        END,    END,    NONE,   101}  };

SSTATES Ready[]         = {{&StopFlag,         ABORT,  NORM,   NONE,   202},
                           {&Inp.uls,          NORM,   ABORT,  EQ2,    203},
                           {&AlarmsReset,      NORM,   ABORT,  NONE,   204},
                           {&Inp.OnePB,        JUMP,   NORM,   NONE,   205},
                           {&Inp.BothPB,       JUMP,   NORM,   NONE,   206},
                           {&ReadyOK,          NORM,   ABORT,  NONE,   207},
                           {&DUPSChangePending,ABORT,  NORM,   NONE,   209},
                           {&DiagStopFlag,     ABORT,  NORM,   NONE,   210},
                           {&UDIScanRecived,   NORM,   ABORT,   NONE,  211},
                           {&TimerFlag,        END,    END,    NONE,   212}  };

SSTATES ReadyHH[]       = {{&StopFlag,         ABORT,  NORM,   NONE, 10000},
                           {&AlarmsReset,      NORM,   ABORT,  NONE, 10001},
                           {&Inp.SingleStart,  JUMP,   NORM,   NONE, 10002},
                           {&ReadyOK,          NORM,   ABORT,  NONE, 10003},
                           {&DUPSChangePending,ABORT,  NORM,   NONE, 10005},
                           {&DiagStopFlag,     ABORT,  NORM,   NONE, 10006},
                           {&TimerFlag,        END,    END,    NONE, 10007}  };

SSTATES ReadyTest[]     = {{&StartTestFlag,    JUMP,   NORM,   NONE,   222},
                           {&AlarmsReset,      NORM,   FAIL,   NONE,   223},
                           {&FailFlag,         FAIL,   NORM,   NONE,   224},
                           {&TimerFlag,        END,    END,    NONE,   225}  };

SSTATES CheckReady[]    = {{&StopFlag,         FAIL,   NORM,   NONE,   301},
                           {&StartingSensorCal,FAIL,   NORM,   NONE,   321},
                           {&Inp.OnePB,        FAIL,   NORM,   NONE,   302},
                           {&Inp.uls,          NORM,   FAIL,   NONE,   303},
                           {&ULSExitFlag,      FAIL,   NORM,   EQ2,    304},
                           {&PartClampInpStatus,FAIL,  NORM,   NONE,   305},
                           {&PartClampExitFlag,FAIL,   NORM,   EQ22,   306},
                           {&PartPresentInpStatus, FAIL, NORM,   NONE, 307},
                           {&PartPresentExitFlag,  FAIL, NORM,   EQ26, 308},
                           {&AlarmsReset,      NORM,   FAIL,   NONE,   309},
                           {&PoweredUp,        NORM,   FAIL,   NONE,   310},
                           {&ReadyOK,          NORM,   FAIL,   NONE,   311},
                           {&PBExitFlag,       FAIL,   NORM,   EQ17,   312},
                           {&DUPSOkFlag,       NORM,   FAIL,   NONE,   313},
                           {&DepotLevel,       FAIL,   NORM,   NONE,   314},
                           {&DUPSChangePending,FAIL,   NORM,   NONE,   315},
                           {&DiagStopFlag,     FAIL,   NORM,   NONE,   316},
                           {&SBCReadyFlag,     NORM,   FAIL,   NONE,   317},
                           {&UDIScanRecived,   NORM,   FAIL,   NONE,   318},
                           {&FailFlag,         FAIL,   JUMP,   NONE,   319},
                           {&TimerFlag,        END,    END,    NONE,   320} };

SSTATES CheckReadyHH[]  = {{&StopFlag,         FAIL,   NORM,   NONE, 10100},
                           {&Inp.SingleStart,  FAIL,   NORM,   NONE, 10101},
                           {&AlarmsReset,      NORM,   FAIL,   NONE, 10102},
                           {&PoweredUp,        NORM,   FAIL,   NONE, 10103},
                           {&ReadyOK,          NORM,   FAIL,   NONE, 10104},
                           {&PBExitFlag,       FAIL,   NORM,   EQ17, 10106},
                           {&DUPSOkFlag,       NORM,   FAIL,   NONE, 10107},
                           {&DepotLevel,       FAIL,   NORM,   NONE, 10108},
                           {&DUPSChangePending,FAIL,   NORM,   NONE, 10109},
                           {&DiagStopFlag,     FAIL,   NORM,   NONE, 10110},
                           {&FailFlag,         FAIL,   JUMP,   NONE, 10111},
                           {&TimerFlag,        END,    END,    NONE, 10112} };

SSTATES PalmButtons[]   = {{&Inp.OnePB,        NORM,   NORM,   NONE,   400},
//                         {&CycleAbort,       JUMP,   NORM,   NONE,   402},
                           {&CycleAbort,       ABORT,  NORM,   NONE,   402},
                           {&Inp.uls,          NORM,   ABORT,  EQ2,    404},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   405},
                           {&OKToAdvance,      JUMP,   NORM,   NONE,   406},
                           {&StaggerFlag,      ABORT,  NORM,   EQ12,   407},
                           {&Inp.Trigger,      ABORT,  NORM,   EQ4,    408},
                           {&TimerFlag,        END,    END,    NONE,   410}  };   /*Test State*/

SSTATES PBHH[]          = {{&Inp.SingleStart,  NORM,   ABORT,  CM14, 10200},
                           {&ECycleHistFlag,   ABORT,  NORM,   NC7,  10201},
                           {&CycleAbort,       ABORT,  NORM,   NONE, 10202},
                           {&OKToAdvance,      JUMP,   NORM,   NONE, 10203},
                           {&TimerFlag,        END,    END,    NONE, 10204}  };
                         
// continuous mode
SSTATES PalmButton[]    = {{&Inp.PartPresent,  NORM,   ABORT,  EQ2,    404},
						   {&Inp.OnePB,        JUMP,   ABORT,  EQ23,   440},
                           {&Inp.uls,          NORM,   ABORT,  EQ2,    441},
                           {&CycleAbort,       ABORT,  NORM,   NONE,   442},
                           {&TimerFlag,        END,    END,    NONE,   443}  };   /*Test State*/

SSTATES WaitPartClampInput[]  = {
						  {&AbortFlag,          ABORT, NORM,   NONE,  11500},
                          {&CycleAbort,         ABORT,  NORM,   NONE,  11501},
                          {&Inp.PartPresent,    NORM,   ABORT,  NC18,   404},
                          {&Inp.BothPB,         NORM,  ABORT,  EQ23,  11502},
                          {&Inp.PartClamped,    JUMP,  NORM,   NONE,  11503},
                          {&PartClampTimeout,   ABORT, NORM,   NC15,  11505},
                          {&ECycleHistFlag,     ABORT, NORM,   NC7,   11506},
                          {&TimerFlag,          END,   END,    NONE,  11507}   };

SSTATES CalWaitUls1[]   = {{&AbortFlag,        ABORT,  NORM,   NONE,   3600},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   3601},
                           {&Inp.BothPB,       NORM,   JUMP,   NONE,   3602},
                           {&Inp.uls,          NORM,   JUMP,   NONE,   3603},
                           {&UlsTimeout,       ABORT,  NORM,   NC1,    3605},
                           {&ECycleHistFlag,   ABORT,  NORM,   NC7,    3606},
                           {&TimerFlag,        END,    END,    NONE,   3607}  };

SSTATES WaitUls1[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   500},
                           {&CycleAbort,       ABORT,   NORM,   NONE,   501},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&Inp.BothPB,       NORM,   JUMP,   NONE,   502},
                           {&Inp.uls,          NORM,   JUMP,   NONE,   503},
                           {&UlsTimeout,       ABORT,  NORM,   NC1,    505},
                           {&ECycleHistFlag,   ABORT,  NORM,   NC7,    506},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   507},
                           {&TimerFlag,        END,    END,    NONE,   508}  };

SSTATES WaitUls2[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   510},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   511},
//                         {&Inp.uls,          JUMP,   NORM,   NONE,   512}, // commented because changing pressure between cycles was causing ULS alarm
                           {&HornReturnFlag,   NORM,   ABORT,  EQ9,    514},
                           {&OKToAdvance,      JUMP,   NORM,   NONE,   515},
                           {&TimerFlag,        END,    END,    NONE,   516} };

SSTATES PreTrigger[]    = {{&AbortFlag,        ABORT,  NORM,   NONE,  2100},
                           {&CycleAbort,       ABORT,   NORM,   NONE,  2101},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,   2102},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,  2103},
                           {&Inp.Trigger,      ABORT,  NORM,   NC3,   2104},
                           {&DistFlag,         JUMP,   NORM,   NONE,  2105},
                           {&PTSTimerFlag,     ALJUMP, NORM,   EQ18,  2106},
                           {&Inp.OL,           ABORT,  NORM,   OL2,   2107},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,  2108},
                           {&TimerFlag,        END,    END,    NONE,  2109}  };   /*Test State*/


/*-- Use this if pretrigger is off  --*/

SSTATES ExtTrigDelay[] = {{&AbortFlag,          ABORT, NORM,   NONE,   11600},
                          {&CycleAbort,         JUMP,  NORM,   NONE,   11601},
                          {&Inp.PartPresent,  NORM,   ABORT,   NC18,     404},
                          {&Inp.ExtTrgDelay,    NORM,  JUMP,   NONE,   11602},
                          {&TriggerLostFlag,    ALJUMP,NORM,   CM14,   11603},
                          {&TrgDelayTimeout,    ABORT, NORM,   NC13,   11604},
                          {&Inp.PartClamped,    NORM,  ABORT,  NC14,   11605},
                          {&ECycleHistFlag,     ABORT, NORM,   NC7,    11606},
                          {&TimerFlag,          END,   END,    NONE,   11607} };

SSTATES ExtTrigDelayDist[] = {
						  {&AbortFlag,          ABORT, NORM,   NONE,   11600},
                          {&CycleAbort,         JUMP,  NORM,   NONE,   11601},
                          {&Inp.PartPresent,  NORM,   ABORT,   NC18,     404},
                          {&Inp.BothPB,       NORM,   ABORT,   EQ23,    2103},
                          {&Inp.ExtTrgDelay,    NORM,  JUMP,   NONE,   11602},
                          {&TriggerLostFlag,    ALJUMP,NORM,   CM14,   11603},
                          {&TrgDelayTimeout,    ABORT, NORM,   NC13,   11604},
                          {&Inp.PartClamped,    NORM,  ABORT,  NC14,   11605},
                          {&ECycleHistFlag,     ABORT, NORM,   NC7,    11606},
                          {&TimerFlag,          END,   END,    NONE,   11607} };

SSTATES WaitTrs1[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   600},
                           {&CycleAbort,       ABORT,   NORM,   NONE,   601},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,   602},
                           {&DistFlag,         JUMP,   NORM,   NONE,   603},
//                         {&Inp.uls,          ALJUMP, NORM,   EQ3,    604}, // commented because changing pressure between cycles was causing ULS alarm
//                         {&Inp.uls,          ABORT,  NORM,   EQ3,    604},
//                         {&ForceStepFlag,    NORM,   JUMP,   NONE,   605},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    606},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   607},
                           {&TimerFlag,        END,    ALJUMP, NC4,    608}  };   /*Test State*/

/*--  Use this if pretrigger is on  --*/

SSTATES WaitTrs1PT[]    = {{&AbortFlag,        ABORT,  NORM,   NONE,   600},
                           {&CycleAbort,       ABORT,   NORM,   NONE,   601},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,   602},
                           {&DistFlag,         JUMP,   NORM,   NONE,   603},
//                         {&Inp.uls,          ALJUMP, NORM,   EQ3,    604},
//                         {&Inp.uls,          ABORT,  NORM,   EQ3,    604}, //commented because changing pressure between cycles was causing ULS alarm
//                         {&ForceStepFlag,    NORM,   JUMP,   NONE,   605},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    606},
                           {&Inp.OL,           ABORT,  NORM,   OL2,    607},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   608},
                           {&TimerFlag,        END,    ALJUMP, NC4,    609}  };   /*Test State*/

/*-- Use this if pretrigger is off  --*/

SSTATES WaitTrs2[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   800},
                           {&CycleAbort,       ABORT,   NORM,   NONE,   801},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,   802},
                           {&Inp.Trigger,      JUMP,   NORM,   NONE,   803},
//                         {&Inp.uls,          ABORT,  NORM,   EQ3,    804}, //commented because changing pressure between cycles was causing ULS alarm
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    805},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   806},
                           {&TimerFlag,        END, 	ABORT, NC4,    807} };

/*--  Use this if pretrigger is on  --*/

SSTATES WaitTrs2PT[]    = {{&AbortFlag,        ABORT,  NORM,   NONE,   800},
                           {&CycleAbort,       ABORT,   NORM,   NONE,   801},
                           {&Inp.PartPresent,  NORM,   ABORT,  NC18,   404},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,   802},
                           {&Inp.Trigger,      JUMP,   NORM,   NONE,   803},
//                         {&Inp.uls,          ABORT,  NORM,   EQ3,    804}, //commented because changing pressure between cycles was causing ULS alarm
//                         {&Inp.uls,          ALJUMP, NORM,   EQ3,    804},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    805},
                           {&Inp.OL,           ABORT,  NORM,   OL2,    806},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   607},
                           {&TimerFlag,        END,    ABORT,  NC4,    808}  };

SSTATES WaitTrs4[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   2400},
                           {&PlsWaitTimerFlag, NORM,   JUMP,   NONE,   2402},
                           {&StaggerFlag,      JUMP,   NORM,   NONE,   2403},
                           {&TimerFlag,        END,    END,    NONE,   2404} };

SSTATES TrigDelay[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   2700},
						   {&Inp.PartPresent,  NORM,   ABORT,  NC18,    404},
                           {&TriggerDelayFlag, NORM,   JUMP,   NONE,   2701},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2702},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2703},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2704},
                           {&TimerFlag,        END,    JUMP,   NONE,   2705} };

SSTATES TrigDelayDist[]     = {
						   {&AbortFlag,        ABORT,  NORM,   NONE,   2700},
						   {&Inp.PartPresent,  NORM,   ABORT,  NC18,    404},
                           {&TriggerDelayFlag, NORM,   JUMP,   NONE,   2701},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2702},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2703},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2704},
                           {&TimerFlag,        END,    JUMP,   NONE,   2705} };

SSTATES Weld1HH[]       = {{&AbortFlag,        ABORT,  NORM,   NONE,  10300},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   10301},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,  10302},
                           {&CycleAbort,       ALJUMPNORM,NORM,NONE,  10303},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,  10304},
                           {&SonicsAbort,      ALJUMPNORM,NORM,NONE,  10305},
                           {&TimerFlag,        END,    JUMP,   NONE,  10306}  };

SSTATES PLC1HH[]        = {{&AbortFlag,        ABORT,  NORM,   NONE,  10350},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   10351},
                           {&TriggerLostFlag,  JUMP,   NORM,   NONE,  10352},
                           {&CycleAbort,       ALJUMPNORM,NORM,NONE,  10353},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,  10354},
                           {&SonicsAbort,      ALJUMPNORM,NORM,NONE,  10355},
                           {&TimerFlag,        END,    JUMP,   NONE,  10356}  };

SSTATES Weld1[]         = {{&AbortFlag,        ABORT,  NORM,   NONE,   900},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    901},
//                         {&CycleAbort,       JUMP,   NORM,   NONE,   902},
                           {&CycleAbort,       ALJUMPNORM,NORM,NONE,   902},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   903},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,   904},
//                         {&SonicsAbort,      JUMP,   NORM,   NONE,   905},
                           {&SonicsAbort,      ALJUMPNORM,NORM,NONE,   905},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    906},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   907},
                           {&TimerFlag,        END,    JUMP,   NONE,   908}  };

SSTATES Weld1Dist[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   900},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    901},
                           {&CycleAbort,       ALJUMPNORM,NORM,NONE,   902},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,   802},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   903},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,   904},
                           {&SonicsAbort,      ALJUMPNORM,NORM,NONE,   905},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    906},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   907},
                           {&TimerFlag,        END,    JUMP,   NONE,   908}  };

SSTATES Weld1A[]        = {{&Inp.OnePB,        NORM,   JUMP,   NONE,   950},
                           {&AbortFlag,        ABORT,  NORM,   NONE,   951},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    952},
                           {&CycleAbort,       ABORT,  NORM,   NONE,   953},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   954},
                           {&TimerFlag,        END,    END,    NONE,   955}  };

SSTATES Weld2[]         = {{&AbortFlag,        ABORT,  NORM,   NONE,   1000},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    1001},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1002},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   1003},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,   1004},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1005},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1006},
                           {&TimerFlag,        END,    JUMP,   NONE,   1007} };

SSTATES Weld2Dist[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   1000},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    1001},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1002},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   1003},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,   1004},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1005},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1006},
                           {&TimerFlag,        END,    JUMP,   NONE,   1007} };

SSTATES Weld2HH[]       = {{&AbortFlag,        ABORT,  NORM,   NONE,  10800},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   10801},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10802},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,  10803},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,  10804},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,  10805},
                           {&TimerFlag,        END,    JUMP,   NONE,  10806} };
                                            
SSTATES PLC2HH[]        = {{&AbortFlag,        ABORT,  NORM,   NONE,  10850},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   10851},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10852},
                           {&TriggerLostFlag,  JUMP,   NORM,   NONE,  10853},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,  10854},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,  10855},
                           {&TimerFlag,        END,    JUMP,   NONE,  10856}};

SSTATES Weld3[]         = {{&AbortFlag,        ABORT,  NORM,   NONE,   2500},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    2501},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2502},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2503},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,   2504},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    2505},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   2506},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2507},
                           {&TimerFlag,        END,    JUMP,   NONE,   2508}};

SSTATES Weld3Dist[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   2500},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    2501},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2502},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2503},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,   2504},
                           {&MissingPartFlag,  ABORT,  NORM,   NC8,    2505},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   2506},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2507},
                           {&TimerFlag,        END,    JUMP,   NONE,   2508} };


SSTATES Weld3HH[]       = {{&AbortFlag,        ABORT,  NORM,   NONE,  11100},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   11101},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  11102},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,  11103},
                           {&StepTimeFlag,     NORM,   JUMP,   NONE,  11104},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,  11105},
                           {&TimerFlag,        END,    JUMP,   NONE,  11106} };

SSTATES Weld4[]         = {{&AbortFlag,        ABORT,  NORM,   NONE,   2600},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    2601},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2602},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2603},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,   2604},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   2605},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2606},
                           {&TimerFlag,        END,    JUMP,   NONE,   2607} };

SSTATES Weld4Dist[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   2600},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,    2601},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   2602},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   2603},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,   2604},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   2605},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   2606},
                           {&TimerFlag,        END,    JUMP,   NONE,   2607} };

SSTATES Weld4HH[]       = {{&AbortFlag,        ABORT,  NORM,   NONE,  11200},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL4,   11201},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  11202},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,  11203},
                           {&WTimeFlag,        NORM,   JUMP,   NONE,  11204},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,  11205},
                           {&TimerFlag,        END,    JUMP,   NONE,  11206} };

SSTATES EnerBrake[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   1300},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL10,   1301},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1302},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   1303},
                           {&EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1304},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1305},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1306},
                           {&TimerFlag,        END,    END,    NONE,   1307} };

SSTATES EnerBrakeDist[] = {{&AbortFlag,        ABORT,  NORM,   NONE,   1300},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL10,   1301},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1302},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   1303},
                           {&EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1304},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1305},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1306},
                           {&TimerFlag,        END,    END,    NONE,   1307} };

SSTATES EnerBrakeHH[]   = {{&AbortFlag,        ABORT,  NORM,   NONE,   1310},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL10,   1311},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1312},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,   1313},
                           {&EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1314},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1315},
                           {&TimerFlag,        END,    END,    NONE,   1316} };

SSTATES PLCBrakeHH[]    = {{&AbortFlag,        ABORT,  NORM,   NONE,   1350},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL10,   1351},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1352},
                           {&TriggerLostFlag,  JUMP,   NORM,   NONE,   1353},
                           {&EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1354},
                           {&SonicsAbort,      JUMP,   NORM,   NONE,   1355},
                           {&TimerFlag,        END,    END,    NONE,   1356} };
                                            
                                                                                        
SSTATES SonicsOff[]     = {{&TimerFlag,        JUMP,   JUMP,   NONE,   1750} };


SSTATES Hold[]          = {{&AbortFlag,        ABORT,  NORM,   NONE,   1100},
                           {&Inp.OL,           ALNORM, NORM,   OL4,    1101},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1102},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1103},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,   1104},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM1,    1105},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1106},
                           {&TimerFlag,        END,    JUMP,   NONE,   1107} };

SSTATES HoldDist[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,   1100},
                           {&Inp.OL,           ALNORM, NORM,   OL4,    1101},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1102},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1103},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,   1104},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM1,    1105},
                           {&Inp.PartClamped,  NORM,   ABORT,  NC14,   1106},
                           {&TimerFlag,        END,    JUMP,   NONE,   1107} };

SSTATES PLCHoldHH[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,  10750},
                           {&Inp.OL,           ALNORM, NORM,   OL4,   10751},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10752},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,  10753},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,  10754},
//                         {&Inp.SingleStart,  NORM,   ALJUMP, CM1,   10755},
//                         {&TriggerLostFlag,  JUMP,   NORM,   NONE,  10755},
                           {&TimerFlag,        END,    JUMP,   NONE,  10756} };

SSTATES HoldHH[]        = {{&AbortFlag,        ABORT,  NORM,   NONE,  10700},
                           {&Inp.OL,           ALNORM, NORM,   OL4,   10701},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10702},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,  10703},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,  10704},
//                         {&Inp.SingleStart,  NORM,   ALJUMP, CM1,   10705},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM1,   10705},
                           {&TimerFlag,        END,    JUMP,   NONE,  10706} };

SSTATES AlterHold[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,   1110},
                           {&Inp.OL,           ALNORM, NORM,   OL4,    1111},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1112},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1113},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,   1114},
                           {&TimerFlag,        END,    JUMP,   NONE,   1116} };

SSTATES AlterHoldDist[] = {{&AbortFlag,        ABORT,  NORM,   NONE,   1110},
                           {&Inp.OL,           ALNORM, NORM,   OL4,    1111},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1112},
                           {&Inp.BothPB,       NORM,   ABORT,  EQ23,    802},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1113},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,   1114},
                           {&TimerFlag,        END,    JUMP,   NONE,   1116} };

SSTATES AlterHoldHH[]   = {{&AbortFlag,        ABORT,  NORM,   NONE,  10400},
                           {&Inp.OL,           ALNORM, NORM,   OL4,   10401},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10402},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,  10403},
                           {&HTimeFlag,        NORM,   JUMP,   NONE,  10404},
//                         {&Inp.SingleStart,  NORM,   ALJUMP, NONE,  10405},
                           {&TriggerLostFlag,  ALJUMP, NORM,   CM14,  10405},
                           {&TimerFlag,        END,    JUMP,   NONE,  10406} };

SSTATES Limits[]        = {{&ClampOnAlarm,      NORM,  JUMP,   NONE,   1200},
							{&TimerFlag,        END,   END,   NONE,   1201} };

SSTATES ABDelay[]       = {{&AbortFlag,        ABORT,  NORM,   NONE,   1500},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1501},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1502},
//                         {&ABTimeFlag,       NORM,   JUMP,   NONE,   1503},
                           {&ABTimeDelayFlag,  NORM,   JUMP,   NONE,   1503},
                           {&HornReturnFlag,   NORM,   ABORT,  EQ9,    1504},
                           {&TimerFlag,        END,    JUMP,   NONE,   1505} };

SSTATES ABDelayHH[]     = {{&AbortFlag,        ABORT,  NORM,   NONE,  10500},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10501},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,  10502},
                           {&ABTimeDelayFlag,  NORM,   JUMP,   NONE,  10503},
                           {&Inp.SingleStart,  NORM,   ALJUMP, NONE,  10504},
                           {&TimerFlag,        END,    JUMP,   NONE,  10505} };

SSTATES ABTime[]        = {{&AbortFlag,        ABORT,  NORM,   NONE,   1600},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1601},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,   1602},
                           {&ABTimeFlag,       NORM,   JUMP,   NONE,   1603},
                           {&HornReturnFlag,   NORM,   ABORT,  EQ9,    1604},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL6,    1605},
                           {&TimerFlag,        END,    JUMP,   NONE,   1606} };

SSTATES ABTimeHH[]      = {{&AbortFlag,        ABORT,  NORM,   NONE,  10600},
                           {&CycleAbort,       JUMP,   NORM,   NONE,  10601},
                           {&ECycleHistFlag,   ABORT,  NORM,   CM15,  10602},
                           {&ABTimeFlag,       NORM,   JUMP,   NONE,  10603},
                           {&HornReturnFlag,   NORM,   ABORT,  EQ9,   10604},
                           {&Inp.OL,           ALJUMPNORM,NORM,OL6,   10605},
                           {&Inp.SingleStart,  NORM,   ALJUMP, NONE,  10606},
                           {&TimerFlag,        END,    JUMP,   NONE,  10607} };

SSTATES RampSonics[]    = {{&RampEndFlag,      JUMP,   NORM,   NONE,   1900},
                           {&CycleAbort,       JUMP,   NORM,   NONE,   1901},
                           {&HornReturnFlag,   NORM,   ABORT,  EQ9,    1902},
                           {&Inp.OL,           ALJUMPNORM,NORM,NONE,   1903},
                           {&TimerFlag,        END,    END,    NONE,   1904} };


SSTATES Nop[]           = {{&TimerFlag,        JUMP,   JUMP,   NONE,   1200} };


SSTATES PowerDown[]     = {{&Inp.PwrOff,       NORM,   NORM, NONE,     9900},
                           {&PDownDelay,       JUMP,   NORM,   NONE,   9901},
//                         {&PowerDownAborted, ALJUMP, NORM,   NONE,   9902},
                           {&TimerFlag,        END,    END,    NONE,   9903}  };

/*---  This state is meant to never, NEVER, Ever exit ---*/

SSTATES PowerDown1[]    = {{&TimerFlag,        END,    END,    NONE,   9904}  };




SSTATES SCComp[]        = {{&PlsWaitTimerFlag, NORM,   JUMP,   NONE,   3405},
                           {&TimerFlag,         END,   END,    NONE,   3406}};

SSTATES CalbPBs[]       = {{&Inp.OnePB,        NORM,   NORM,   NONE,   3500},
                           {&Inp.uls,          NORM,   ABORT,  EQ2,    3501},
                           {&StaggerFlag,      JUMP,   NORM,   NONE,   3502},
                           {&Inp.BothPB,       JUMP,   NORM,   NONE,   3503},
                           {&TimerFlag,        END,    END,    NONE,   3504}  };   /*Test State*/


SSTATES SeekWait[]      = {{&SeekEndFlag,       JUMP,  NORM,   NONE,   1700},
                           {&CycleAbort,        JUMP,  NORM,   NONE,   1701},
                           {&HornReturnFlag,    NORM,  ABORT,  EQ9,    1702},
                           {&TimerFlag,         END,   END,    NONE,   1703} };

SSTATES SeekWaitHH[]    = {{&SeekEndFlag,       JUMP,  NORM,   NONE,  10900},
                           {&CycleAbort,        JUMP,  NORM,   NONE,  10901},
                           {&Inp.SingleStart,   NORM,  ALJUMP, NONE,  10902},
                           {&TimerFlag,         END,   END,    NONE,  10903} };

SSTATES ParamUpdate[]   = {{&ParamUpdateFlag,   NORM,  NORM,   NONE,   1800},
                           {&TimerFlag,         END,   END,    NONE,   1801} };
                          

/*                         Variable           TRUE    FALSE   Alarm   Trace */
/*                         pointer            Action  Action  Code    Code  */
/*                         ----------         ------- ------- ------- ------*/

SSTATES WaitTime[]       = {{&PlsWaitTimerFlag,NORM,   JUMP,   NONE,   2100},
                            {&TimerFlag,       END,    END,    NONE,   2101}  };

SSTATES Trigger[]        = {{&Inp.PartPresent,  NORM,   ABORT,  EQ2,    404},//fix alarm code
							{&Inp.Trigger,     NORM,   ALJUMP, NONE,   2200},
                            {&Inp.PartClamped, NORM,   ABORT,  NC14,   2201},
                            {&TimerFlag,       JUMP,   JUMP,   NONE,   2202} };

SSTATES CalTrigger[]     = {{&Inp.Trigger,     NORM,   ALJUMP, NONE,   3700},
                            {&TimerFlag,       JUMP,   JUMP,   NONE,   3701} };

SSTATES TriggerHH[]      = {{&Inp.SingleStart, NORM,   ALJUMP, NONE,  11001},
                            {&TimerFlag,       JUMP,   JUMP,   NONE,  11002} };


SSTATES MenuSync[]       = {{&AdvanceMenuFlag, JUMP,   NORM,   NONE,   2000},
                            {&TimerFlag,       END,    END,    NONE,   2002} };

SSTATES CalibPressure[]   ={{&AdvanceMenuFlag, JUMP,   NORM,   NONE,    2004},
                            {&TimerFlag,       END,    END,    NONE,    2005} };

SSTATES CalibForce[] = 	   {{&AdvanceMenuFlag, JUMP,   NORM,   NONE,   2006},
                            {&TimerFlag,       END,    END,    NONE,   2007}};

SSTATES FinalData[]      = {{&IsThereAGraphPrinting,NORM,JUMP, NONE,   9998},
                            {&TimerFlag,       END,    END,    NONE,   9999} };

SSTATES ConfirmRejectSST[]= {{&WaitForRejectConfirm,NORM,JUMP, NONE,   9017},
							{&Inp.ConfirmReject,JUMP,NORM, NONE,   9018},
                            {&TimerFlag,       END,    END,    NONE,   9019} };

SSTATES DebugState[]     = {{&TimerFlag,       NORM,   JUMP,   NONE,   9000},
                            {&TimerFlag,       END,    END,    NONE,   9001} };


SSTATES TestMode[]       = {{&TestTimerFlag,   JUMP,   NORM,   NONE,   4000},
                            {&Inp.uls,         NORM,   ALJUMP, EQ2,    4001},
                            {&Inp.OL,          ALJUMPNORM,NORM,OL1,    4003},
                            {&TimerFlag,       END,    END,    NONE,   4004} };


/*-----  Here are the power up sub states  -----*/

SSTATES PInitial[]      = {{&SystemOK,         JUMP,   NORM,   NONE,   150},
//                           &Inp.OL,           ALJUMPNORM,NORM,OL3,    151,
                           {&TimerFlag,        END,    END,    NONE,   152}  };

SSTATES PChkAct[]       = {{&ActDone,          JUMP,   NORM,   NONE,   160},
                           {&TimerFlag,        END,    END,    NONE,   162}  };

SSTATES PChkPwrSup[]    = {{&PSDone,           JUMP,   NORM,   NONE,   170},
                           {&TimerFlag,        END,    END,    NONE,   172}  };

SSTATES PChkCntrls[]    = {{&ControlsDone,     JUMP,   NORM,   NONE,   180},
                           {&TimerFlag,        END,    END,    NONE,   183}  };

SSTATES PChkStack[]     = {{&StackDone,        JUMP,   NORM,   NONE,   190},
                           {&TimerFlag,        END,    END,    NONE,   191}  };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */
STATE TopOfList    = {Initial,    &TimeOff,   Nothing,      Nothing,      Restart,      NeverStart,   NOP       };

STATE ReadySt      = {Ready,      &TimeOff,   TestReady,    EnterReady,   ExitReady,    ExitAlReady,      READYSTATE          };
STATE ReadyHHST    = {ReadyHH,    &TimeOff,   TestReady,    EnterReady,   ExitReady,    Nothing,      READYSTATE          };

STATE PBState      = {PalmButtons,&Stagger,   TestPB,       StartPB,      ExitPB,       AlarmExitPB,  PBSTATE             };
STATE PBStateHHST  = {PBHH,       &Stagger,   TestPBHH,     StartPB,      ExitPBHH,     AlarmExitPB,  PBSTATE             };
/*----- ParClamp  -----*/
STATE WaitPartClampST     = {WaitPartClampInput,&MaxWTime,  TestPartClampInput,   EnterPartClamp,     ExitPartClampState,  Nothing,      WAITFORPARTCLAMPINPUTSTATE };

// continuous mode
STATE OnePBState   = {PalmButton, &TimeOff,   Nothing,      StartPB,      Nothing,      AlarmExitPB,  PBSTATE             };
STATE WaitUls      = {WaitUls1,   &UlsTime,   TestUls,      EnterUls,     ExitULS,      AlarmUls,     WAITFORULSCLEARSTATE};
STATE WaitUlsUp    = {WaitUls2,   &TimeOff,   TestUlsUp,    EnterUlsUp,   ExitUlsUp,    AlarmUls,     WAITFORULSMADESTATE };

/*--  This first group is used when pretrigger is off  --*/

STATE WaitTrs1DST  = {WaitTrs1,   &TrsTime,   TestTrs1D,    EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs1ST   = {WaitTrs1,   &TrsTime,   TestTrs1,     EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs2DST  = {WaitTrs2,   &TrsTime,   TestTrs2D,    EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };
STATE WaitTrs2ST   = {WaitTrs2,   &TrsTime,   TestTrs2,     EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };

/*--  This second group is used when pretrigger is on  --*/

STATE WaitTrs1DSTPT= {WaitTrs1PT, &TrsTime,   TestTrs1D,    EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs1STPT = {WaitTrs1PT, &TrsTime,   TestTrs1,     EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs2DSTPT= {WaitTrs2PT, &TrsTime,   TestTrs2D,    EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };
STATE WaitTrs2STPT = {WaitTrs2PT, &TrsTime,   TestTrs2,     EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };

STATE UpdateState  = {ParamUpdate,&TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      UPDATESTATE         }; 

STATE PreTrsDST    = {PreTrigger, &TimeOff,   TestPTS,      EnterPTS,     StartPTS,     Nothing,      WAITFORPTSSTATE     };
STATE PreTrsST     = {PreTrigger, &TimeOff,   TestPTS,      EnterPTS,     StartPTS,     Nothing,      WAITFORPTSSTATE     };
STATE TriggerST    = {Trigger,    &TimeOff,   Nothing,      Nothing,      TriggerBeep,  Nothing,      TRIGGEREDSTATE      };
STATE TriggerHHST  = {TriggerHH,  &TimeOff,   Nothing,      Nothing,      HHBeep,       Nothing,      TRIGGEREDSTATE      };
STATE TrigDelayST  = {TrigDelay,  &MaxWTime,  Nothing,      EnterTrigDly, ExitTrigDly,  Nothing,      TRIGGERDELAYSTATE   };
STATE TrigDelaySTDist  = {TrigDelayDist,  &MaxWTime,  Nothing,      EnterTrigDly, ExitTrigDly,  Nothing,      TRIGGERDELAYSTATE   };
STATE ExtTrigDelayST={ExtTrigDelay,&MaxWTime, TestExtTrigDly,EnterExtTrigDly, Nothing,   Nothing,      EXTTRIGDELAYSTATE   };
STATE ExtTrigDelaySTDist={ExtTrigDelayDist,&MaxWTime, TestExtTrigDly,EnterExtTrigDly, Nothing,   Nothing,      EXTTRIGDELAYSTATE   };

/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Time Mode -----*/

STATE SonicsOn1DST = {Weld1,      &MaxWTime,  CheckSonics1D,  StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn1DSTDist = {Weld1Dist,      &MaxWTime,  CheckSonics1D,  StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn1ST  = {Weld1,      &MaxWTime,  CheckSonics1,   StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn1STDist  = {Weld1Dist,      &MaxWTime,  CheckSonics1,   StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn2DST = {Weld2,      &MaxWTime,  CheckSonics2D,  StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOn2DSTDist = {Weld2Dist,      &MaxWTime,  CheckSonics2D,  StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOn2ST  = {Weld2,      &MaxWTime,  CheckSonics2,   StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOn2STDist  = {Weld2Dist,      &MaxWTime,  CheckSonics2,   StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOnHHST = {Weld1HH,    &MaxWTime,  CheckSonics1HH, StartSonic1HH,Nothing,      AlStopHH,     WELDTIMESTATE    };
STATE SonicsOn2HHST= {Weld2HH,    &MaxWTime,  CheckSonics1HH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE   };
STATE PLCOnHHST    = {PLC1HH,     &MaxWTime,  CheckSonics1HH, StartSonic1HH,Nothing,      AlStopHH,     WELDTIMESTATE    };
STATE PLCOn2HHST   = {PLC2HH,     &MaxWTime,  CheckSonics1HH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE   };


/*----- Energy Mode -----*/

STATE SonicsOn3DST = {Weld3,      &MaxWTime,  CheckSonics3D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3DSTDist = {Weld3Dist,      &MaxWTime,  CheckSonics3D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3ST  = {Weld3,      &MaxWTime,  CheckSonics3, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3STDist  = {Weld3Dist,      &MaxWTime,  CheckSonics3, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn4DST = {Weld4,      &MaxWTime,  CheckSonics4D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn4DSTDist = {Weld4Dist,      &MaxWTime,  CheckSonics4D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn4ST  = {Weld4,      &MaxWTime,  CheckSonics4, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn4STDist  = {Weld4Dist,      &MaxWTime,  CheckSonics4, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn3HHST= {Weld3HH,    &MaxWTime,  CheckEnergyHH,StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOn4HHST= {Weld4HH,    &MaxWTime,  CheckEnergyHH,CheckEnergyHH,StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*----- Absolute Mode -----*/

STATE SonicsOn3A   = {Weld3,      &MaxWTime,  CheckSonics3A,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3ADist   = {Weld3Dist,      &MaxWTime,  CheckSonics3A,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn5    = {Weld4,      &MaxWTime,  CheckSonics5, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn5Dist    = {Weld4Dist,      &MaxWTime,  CheckSonics5, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };


/*----- Collapse Mode -----*/

STATE SonicsOn3B   = {Weld3,      &MaxWTime,  CheckSonics3B,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3BDist   = {Weld3Dist,      &MaxWTime,  CheckSonics3B,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn6    = {Weld4,      &MaxWTime,  CheckSonics6, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn6Dist    = {Weld4Dist,      &MaxWTime,  CheckSonics6, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };


/*----- Peak Power Mode -----*/

STATE SonicsOn3CDST= {Weld3,      &MaxWTime,  CheckSonics3CD,StartSonic3, StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3CDSTDist= {Weld3Dist,      &MaxWTime,  CheckSonics3CD,StartSonic3, StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3CST = {Weld3,      &MaxWTime,  CheckSonics3C,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3CSTDist = {Weld3Dist,      &MaxWTime,  CheckSonics3C,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn7DST = {Weld4,      &MaxWTime,  CheckSonics7D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn7DSTDist = {Weld4Dist,      &MaxWTime,  CheckSonics7D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn7ST  = {Weld4,      &MaxWTime,  CheckSonics7, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn7STDist  = {Weld4Dist,      &MaxWTime,  CheckSonics7, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOnPP1ST= {Weld3HH,    &MaxWTime,  CheckPPHH,    StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOnPP2ST= {Weld4HH,    &MaxWTime,  CheckPPHH,    StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Ground Detect Mode -----*/

STATE SonicsOn8DST = {Weld3,      &MaxWTime,  CheckSonics8D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn8DSTDist = {Weld3Dist,      &MaxWTime,  CheckSonics8D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn8ST  = {Weld3,      &MaxWTime,  CheckSonics8, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn8STDist  = {Weld3Dist,      &MaxWTime,  CheckSonics8, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn9DST = {Weld4,      &MaxWTime,  CheckSonics9D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn9DSTDist = {Weld4Dist,      &MaxWTime,  CheckSonics9D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn9ST  = {Weld4,      &MaxWTime,  CheckSonics9, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn9STDist  = {Weld4Dist,      &MaxWTime,  CheckSonics9, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOnGD1ST= {Weld3HH,    &MaxWTime,  CheckGdDetHH, StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOnGD2ST= {Weld4HH,    &MaxWTime,  CheckGdDetHH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*----- Continuous Mode -----*/

STATE SonicsOn1A   = {Weld1A,     &TimeOff,   CheckSonics1A,StartSonic1A, StopSonic1,   AlStopSonics, WELDTIMESTATE       };


STATE WeldOffST    = {SonicsOff,  &TimeOff,   Nothing,      WeldOffStateEntry,      Nothing,      Nothing,      ENDOFSONICS         };
STATE WeldOffHHST  = {SonicsOff,  &TimeOff,   Nothing,      WeldOffHHStateEntry,      StopAllSonic, Nothing,      ENDOFSONICS         };

/*----- Energy Braking -----*/

STATE EnerBrakeST  = {EnerBrake,  &TimeOff,   CheckBrake,   StartBrake,   StopAllSonic, StopAllSonic, WELDTIME2STATE      };
STATE EnerBrakeSTDist  = {EnerBrakeDist,  &TimeOff,   CheckBrake,   StartBrake,   StopAllSonic, StopAllSonic, WELDTIME2STATE      };
STATE EnerBrakeHHST= {EnerBrakeHH,&TimeOff,   CheckBrake,   StartBrake,   StopAllSonicHH,StopAllSonicHH,WELDTIME2STATE    };
STATE PLCBrakeHHST = {PLCBrakeHH, &TimeOff,   CheckBrake,   StartBrake,   StopAllSonicHH,StopAllSonicHH,WELDTIME2STATE    };


/*----- Hold -----*/

STATE HoldTimeDST  = {Hold,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeDSTDist  = {HoldDist,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeST   = {Hold,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeSTDist   = {HoldDist,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeHHST = {HoldHH,     &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE PLCTimeHHST  = {PLCHoldHH,  &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE FakeHold     = {AlterHold,  &MaxHTime,  Nothing,      StartAHold,   StopAHold,    StopAHold,      HOLDTIMESTATE       };
STATE FakeHoldDist     = {AlterHoldDist,  &MaxHTime,  Nothing,      StartAHold,   StopAHold,    StopAHold,      HOLDTIMESTATE       };
STATE FakeHoldHHST = {AlterHoldHH,&MaxHTime,  Nothing,      StartAHold,   StopAHold,    StopAHold,      HOLDTIMESTATE       };

STATE CheckLimitsST= {Limits,     &TimeOff,   Nothing,      StartChkLimit,      ExitChkLimit,      Nothing,      PROCESSALARMSSTATE  };

/*----- Afterburst -----*/

STATE ABDelayST    = {ABDelay,    &MaxDTime,  TestABDly,    StartABDly,   StopABDly,    ALStopABD,    AFTERBURSTDELAYSTATE};
STATE ABTimeST     = {ABTime,     &MaxABTime, TestABTme,    StartABTme,   StopABTme,    ALStopABT,    AFTERBURSTTIMESTATE };
STATE RampSonicsST = {RampSonics, &TimeOff,   RampOff,      Nothing,      PSIdle,       PSIdle,       RAMPSONICSSTATE     };
STATE ABDelayHHST  = {ABDelayHH,  &MaxDTime,  TestABDlyHH,  StartABDly,   StopABDly,    ALStopABD,    AFTERBURSTDELAYSTATE};
STATE ABTimeHHST   = {ABTimeHH,   &MaxABTime, TestABTmeHH,  StartABTme,   StopABTme,    ALStopABT,    AFTERBURSTTIMESTATE };

/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Seek -----*/

STATE SeekState    = {SeekWait,   &TimeOff,   CheckSeek,    StartSeek,    StopSeek,     StopSeek,     SEEKSTATE           }; 
STATE SeekStateHH  = {SeekWaitHH, &TimeOff,   CheckSeekHH,  StartSeekHH,  StopSeek,     StopSeek,     SEEKSTATE           }; 

STATE PreReady     = {CheckReady, &TimeOff,   TestPreReady, EPreReady,    PreReadyJump, PreReadyAlJump,PREREADYSTATE       };
STATE PreReadyHHST = {CheckReadyHH,&TimeOff,  TestPreReadyHH,EPreReady,   ClearAbort,   Nothing,      PREREADYSTATE       };
STATE EndOfList    = {Nop,        &TimeOff,   Nothing,      Restart,      Restart,      Restart,      NOP                 };
STATE NopList      = {Nop,        &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      NOP                 };

STATE StartData    = {Nop,        &TimeOff,   Nothing,      StartDataCollection,Nothing,Nothing,      NOP                 };
STATE StopData     = {Nop,        &TimeOff,   Nothing,      StopDataCollection,Nothing, Nothing,      NOP                 };
STATE StopDataTune = {Nop,        &TimeOff,   Nothing,      StopDataTuning,Nothing, Nothing,      NOP                 };
//state to be used in down speed cycles initiated from Horn Down
STATE StopDataTuneHD = {Nop,        &TimeOff,   Nothing,      StopDataTuningHD,Nothing, Nothing,      NOP                 };


/*-----  Here are the Power On/Off States  -----*/

STATE PowerOn1     = {PInitial,   &TimeOff,   TestPO1,      PowerUp,      Copyright,    Nothing,      NOP                 };
STATE PowerOn2     = {PChkCntrls, &TimeOff,   TestPO2,      DispCtrl,     Nothing,      Nothing,      NOP                 };
STATE PowerOn3     = {PChkAct,    &TimeOff,   TestPO3,      DispAct,      Nothing,      Nothing,      NOP                 };
STATE PowerOn4     = {PChkPwrSup, &TimeOff,   TestPO4,      DispPS,       Nothing,      Nothing,      NOP                 };
STATE PowerOn5     = {PChkStack,  &TimeOff,   TestPO5,      DispStack,    PowerOnOK,    Nothing,      POWERUPSEEKSTATE    };
STATE PowerOn6     = {Nop,        &TimeOff,   Nothing,      Nothing,      NewState,     Nothing,      POWERUPSEEKSTATE    };



STATE PwrDown      = {PowerDown,  &TimeOff,   CheckPD,      EnterPDown,   PowerOff,     Nothing,      POWERDOWNSTATE      };
STATE PwrDown1     = {PowerDown1, &TimeOff,   Nothing,      PowerOffLock, Nothing,      Nothing,      POWERDOWNSTATE      };



/*-----  Other useful and sometimes used states  -----*/

STATE MenuSyncST   = {MenuSync,   &TimeOff,   CheckMenuSync,Nothing, UpdateCalibrationState,Nothing,      MENUSYNCSTATE       };
STATE SetCalPressureST   = {CalibPressure,   &TimeOff,   SetCalibrationPressure, SetCalibrationPressureEntry, UpdateCalibrationState,Nothing,      SETCALPRESSURESTATEAES  };
STATE SetCalForceST = {CalibForce,   &TimeOff,   SetCalibrationForce, SetCalibrationForceEntry, UpdateCalibrationState,Nothing,      SETCALFORCESTATEAES  };
/* Can't use FINALDATASTATE because it would cause two FinalResults messages to be sent */
STATE FinalDataST  = {FinalData,  &TimeOff,   Nothing,      EnterFData,   SendFData,    Nothing,      NOP                 };

STATE ConfirmRejectST  = {ConfirmRejectSST,  &TimeOff,   Nothing,      ConfirmRejectEntry,   Nothing,    Nothing,      CONFIRMREJECTSTATE                      };

STATE PreReadyTestSt= {CheckReady,&TimeOff,   TestTestPreReady, EPreReady,    ClearAbort,   Nothing,      PREREADYSTATE       };
STATE ReadyTestSt  = {ReadyTest,  &TimeOff,   TestReadyTest,EnterTestReady,ExitReadyTest,AlStopSonics, READYSTATE         };
STATE TestST       = {TestMode,   &TimeOff,   TestTest,     EnterTest,    ExitTest,     AlStopTest, TESTMODESTATE       };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

STATE CalTopOfList = {Initial,    &TimeOff,   Nothing,      Nothing,      Restart,      Restart,      PREREADYSTATE       };

STATE CalReadySt   = {Ready,      &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      CALREADYSTATE       };
STATE CalPBState2  = {CalbPBs,    &Stagger,   TestCalPB,    StartCalPB,   CalExitPB,    AlarmExitPB,  NOP         };
STATE CalWaitUls   = {CalWaitUls1,&UlsTime,   UpdateDownSpeed, Nothing,   ExitULS,      AlarmUls,     WAITFORULSCLEARSTATE};
STATE CalTriggerST = {CalTrigger, &TimeOff,   Nothing,      Nothing,      TriggerBeep,  Nothing,      TRIGGEREDSTATE      };
STATE CalWaitTrsST = {WaitTrs4,   &MaxWTime,  TestTimer,    Nothing,      Nothing,      Nothing,      WAITFORTRSSTATE2    };
STATE CalWaitTime1 = {WaitTime,   &CalTimer,  ReadLoadCell, InitForce2,   ExitCalWait,  Restart,      CALTIMERSTATE1      };
STATE CalWaitTime2 = {WaitTime,   &CalTimer,  CollectForceData,InitForce3,ExitCalWait,  Restart,      CALTIMERSTATE2      };
STATE CalEndOfList = {Nop,        &TimeOff,   Nothing,      Restart,      Restart,      Nothing,      PREREADYSTATE       };
                                                                                                                                                      
/*                      Substate    Timeout    Pass Code      Entry Code       JUMP Code     ALJUMP      State       */
/*                      Name        pointer                                                                          */
/*                      ----------  -------    ----------     ----------       ----------    --------    ------------        */
STATE SCWaitUls       = {CalWaitUls1,&UlsTime, UpdateDownSpeed, Nothing,       ExitULS,      AlarmUls,   WAITFORULSCLEARSTATE};
STATE SCWaitTrsST     = {WaitTrs4,   &TimeOff, WaitForSpringRate,Nothing,      InitCalTimer, Nothing,    WAITFORTRSSTATE2    };
                                                                                                                                             
STATE SCDone          = {SCComp,     &TimeOff, UpdateMessage, Nothing,         SCFinalCleanup,  Nothing,    NOP         };
STATE SCEndOfList     = {Nop,        &TimeOff, Nothing,       Restart,         Restart,      Restart,    NOP         };


void  CheckPD(void)
{
   PowerDownAborted = FALSE;
}


void  PowerOff(void)
{
   PowerDownSystem();
}



void PowerOffLock(void)
/****************************************************************************/
/*                                                                          */
/* This function will NEVER RETURN, used for power down only.               */
/*                                                                          */
/****************************************************************************/
{
   while(TRUE);
}



void EnterPDown(void)
{
   PDownDelay = FALSE;                 /* Write to FRAM will set to TRUE    */
   PrePowerDown();
}


void  PowerUp(void)
{

	printf("\n\n\n **************** POWERUP **************\n\n\n");
   ActDone = FALSE;
   PSDone = FALSE;
   ControlsDone = FALSE;
   StackDone = FALSE;
   PowerUpTimer = 0;
   PowerUpSeekTimer = 0;
   PowerUpOL = FALSE;
   SystemOK = FALSE;       /* TestPO1 will set this to TRUE after 1 second */
   SetCurrentFreqOffset(0);
   FreqControlInternal.boolEAN = TRUE;  /* set to internal frequency */
   FreqControlExternal = FALSE;
   WeldingResults.PSActControlFlags = BIT0;   /* set to internal amplitude */
   WeldingResults.PSActControlFlags |= BIT2;   /* set to internal frequency */
   DUPSOkFlag = FALSE;
   DUPS_MsgBuf.mt = DUPS_MSGINITINTERFACE;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, *((DUPS_MSGBUF*) &DUPS_MsgBuf), 0);
   PSReset();
}

/****************************************************************************/
/*  It must get the current preset and decide what actuator is correct and  */
/*  then see if that actuator is the one actually connected to this power   */
/*  supply.                                                                 */
/****************************************************************************/


void TestPO1(void)
/*-----   Initial conditions for power up    -----*/
{
   if ((PowerUpTimer++ >= 1500) && (DUPSOkFlag == TRUE)){
      PowerUpTimer = 500;
      if((CurrentSetup.DigTuneFlag & BIT0) == TRUE)
      {
         SetDigTune();
      }
      else{
         CenterDigTune();
      }
      SystemOK = TRUE;
   }
}

void DispCtrl(void)
{
   PowerUpTimer = 0;
}   

void TestPO2(void)
/*-----   Check controls here   -----*/
{
   if (PowerUpTimer++ >= 1800) {
      if(!CurrentSetup.VGAHWPresent)
         UpdateBarGraph(0);
      UpdateLED(UPLED, OFF);
      UpdateLED(RIGHTLED, OFF);
      UpdateLED(DOWNLED, OFF);
      UpdateLED(LEFTLED, OFF);
      UpdateLED(OFFLED, OFF);
      if(AlarmCounter == 0) 
         UpdateLED(RESETLED, OFF);
      NumberOfBeeps = 0;
      TurnOffBeeper();

/* Before we leave, set up all user definable outputs to correct state */
  
      UpdateAllUserOutputs();
      
      ControlsDone = TRUE;
   }
   else {
      UpdateBarGraph(PowerUpTimer / 17);
      if (PowerUpTimer > 1500) {
         UpdateLED(UPLED, ON);
      }
      else if (PowerUpTimer > 1250) {
         UpdateLED(RIGHTLED, ON);
      }
      else if (PowerUpTimer > 1000) {
         UpdateLED(DOWNLED, ON);
      }
      else if (PowerUpTimer > 751) {
         UpdateLED(LEFTLED, ON);
      }
      else if (PowerUpTimer > 750) {
         Beep(SYSTEMBEEP);
      }
      else if (PowerUpTimer > 500) {
         UpdateLED(OFFLED, ON);
      }
      else if (PowerUpTimer > 250) {
         UpdateLED(RESETLED, ON);
      }
   }
}


void DispAct(void)
{
   PowerUpTimer = 0;
}   

void TestPO3(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the actuator. The upper limit switch, carriage */
/*  door.                                                                   */
/*  Note: For now the SV safety circuits will not be tested.                */
/*                                                                          */
/****************************************************************************/
{
   if ( PowerUpTimer++ <= ACTUATOR_TIME) {
//      if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)) {
//         if ( PressureTimer++ >= 200 ) {
//            PressureTimer = 0;
//            if (CheckPressure( &PressureFlag, HomePressure ) == TRUE) {
//               PressureCounter++;
//            }
//            else {
//               PressureCounter = 0;
//            }
//         }
//      }
   }
   if ( PowerUpTimer > ACTUATOR_TIME){
//      if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)) {
//         if ( PressureCounter >= 3 ){
//            if(CurrentPreset.SetPressure != PressureFlag)  /* Pressure has changed */
//            {
//               CurrentPreset.SetPressure = PressureFlag;
//               CurrentPreset.PresetUpdateComplete = FALSE;    /* force asterisk */
//               PresetNeedsToBeUpdated = TRUE;                 /* need to verify the preset */
//               CurrentPreset.Verified = FALSE;
//            }
//            UpdatePressureOffset();
//         }
//         else {
//            RecordAlarm(EQ25);
//         }
//         if ( CurrentPreset.SetPressure == TRUE ){
//            SystemPres60PSI = FALSE;
//            SystemPres80PSI = TRUE;
//         }
//         else {
//            SystemPres60PSI = TRUE;
//            SystemPres80PSI = FALSE;
//         }
//      SetMaxMinValues();
//      }
/*-----   Start by looking at various signals   -----*/
      
      if (Inp.uls == FALSE) {
         RecordAlarm(EQ2);
         ActClrOff();         /* Not at home, so can't say for sure if actuator */
      }                       /* is clear or not.                               */
      else {
         ActClrOn();          /* We're home so actuator is clear                */
      }   

      if (CurrentSetup.Actuator == AE) {
         if (Inp.Trigger == TRUE)
            RecordAlarm(EQ4);
      }
      else
         CheckForHornChange(); /* Is the horn weight different from last power up */
      if (Inp.OnePB == TRUE) {
         RecordAlarm(EQ17);
      }
      ActDone = TRUE;
   }
}

void DispPS(void)
{
   PowerSupplyOk = TRUE;                    /* Assume P/S will be okay      */
   PowerUpFreq = CurrentFreqIn;             /* Read frequency at rest       */
   PSSeek();                             /* Start a seek                 */
   SetCurrentAmp(5);                     /* Limit to 5% amplitude        */
   ActualSeekTime = 0;
   ActualPeakPower = 0;
   PowerUpTimer = 0;
   PowerUpSeekTimer = 0;
}   



void TestPO4(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the power supply at power up.  It will do the  */
/*  following checks:                                                       */
/*                                                                          */
/*     - Do a seek & check for run signal back from power supply            */
/*     - While seeking check for seek signal back from power supply         */
/*     - Look for +10V reference signal from power supply                   */
/*     - This entire function will be skipped if E-stop is activated        */
/*                                                                          */
/*  The variable PSFailCode (available as entry 13 in debug quick list)     */
/*  will contain bits set to '1' to indicate the reason for failure.        */
/*       BIT0 - Seek signal did not respond from power supply module        */
/*       BIT1 - Run signal did not respond from power supply module         */
/*       BIT3 - +10Vreference was below roughly 9.0 volts                   */
/*       BIT4 - E-stop was active at power up.  Not a failure, but does     */
/*              indicate that the power up test was not run.                */
/*                                                                          */
/****************************************************************************/
{

   static BOOLEAN OverloadHistoryFlag = FALSE;
   
   if (Inp.Estop == FALSE) {
      if (PowerUpTimer++ >= ONE_SECOND) {
         if (TenVoltRef >= 900) PSFailCode &= ~BIT2;
         if (PSFailCode != 0) PowerSupplyOk = FALSE;
         if (PowerSupplyOk == FALSE)
            RecordAlarm(EQ15);
         PSIdle();                                /* Stop sonics               */
         PSDone = TRUE;                           /* Advance state machine     */
      }
      else {

/*-- For the 1st 1000ms restart the seek every 50 ms (20ms on / 30ms off) --*/
  
         if (PowerUpTimer <= SEEK_TIME) {
            PowerUpSeekTimer++;
            if (OverloadHistoryFlag == FALSE) {
               ActualSeekTime++;  
               if (Inp.OL == TRUE) OverloadHistoryFlag = TRUE;
            }
            if (PowerUpSeekTimer <= SEEK_ON_TIME) {
               PSSeek();                            /* Seek on   */
               if (Inp.PSSeek == TRUE) PSFailCode &= ~BIT0; 
            }
            else {
               PSIdle();                            /* Seek off  */
               if (PowerUpSeekTimer >= SEEK_RETRIGGER_TIME) {
                  PowerUpSeekTimer = 0;
               }
            }
         }
         else {
            PSSeek();                            /* Make sure 0% Led stays on  */
         }

         if (Inp.PSRun == TRUE) PSFailCode &= ~BIT1; 
      }
      if (CurrentPowerIn > ActualPeakPower) /* update needed for alarm additional information */
          ActualPeakPower = CurrentPowerIn;
      FreqChg = CurrentFreqIn - PowerUpFreq;
   }

/*---   Here's what we do if they powered up with E-stop active   ---*/

   else {
      PSDone = TRUE;             /* Make sure the state machine can advance */
      PowerSupplyOk = TRUE;      /* Now we lie about our results on the P/S */
      PSFailCode = BIT3;
   }
   if (Inp.OL == TRUE)
      PowerUpOL = TRUE;
}



void DispStack(void)
{
   PowerUpTimer = 0;
}   



void TestPO5(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the stack.                                     */
/*                                                                          */
/****************************************************************************/
{
   if (PowerUpTimer++ >= ONE_SECOND ){
// do not detect stack missing 
      StackDone = TRUE;
   }
   if(Inp.OL == TRUE)
      PowerUpOL = TRUE;
}



void PowerOnOK(void)
{
   LockPowerOn();
   JustPoweredUpFlag = TRUE;
   JustPoweredUpTimer = 0;
   PoweredUp = FALSE;
   if (PowerUpOL == TRUE)
   {
      RecordAlarm(OL3);
      PSReset();                 /* Attempt to reset power up seek overload */
   }   

/* Do stuff here that has to happen only at power on */

   UpdateSWConfiguration(VEL, TRUE);         /* Set velocity reporting on  */

//   if (BUCMenuRAM.MicroHomeForce == FALSE)      /* Set up Micro home leaving force */
      MicroHomeForce = LEAVINGHOMEFORCEMICROLO;  
//   else                
//      MicroHomeForce = LEAVINGHOMEFORCEMICROHI;   
   
}


void NewState(void)
{
   ResetStateMachine();
   SelectWeldSequence();
   if (!CurrentSetup.VGAHWPresent) {
      StartStateMachine();
   }
}

void NeverStart(void)
{
   Restart();
}

void Copyright(void)
/****************************************************************************/
/*                                                                          */
/* This function will be called after the copyright notice has been shown   */
/* for the proper amount of time.                                           */
/*                                                                          */
/****************************************************************************/
{
   PowerUpTimer = 0;
}


void CheckMenuSync(void)
/****************************************************************************/
/*                                                                          */
/*   This function will wait for a new menu to be displayed.  While waiting */
/*   some tests will be run.                                                */
/*                                                                          */
/****************************************************************************/
{
   if ((GetCurrentSequenceType() == SC) ||
        (GetCurrentSequenceType() == CALIBRATION)){
      ReadLoadCell();     /* Read loadcell until user types in value */
      WaitForMenu();
   }
}






