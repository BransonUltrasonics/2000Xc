/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menuhorn.cpp_v   1.30   Oct 10 2017 11:58:48   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menuhorn.cpp_v  $
 * 
 *    Rev 1.30   Oct 10 2017 11:58:48   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.29   16 Apr 2015 07:26:34   rjamloki
 * Removed unnecessary UpdateOperatingPressure() function
 * 
 *    Rev 1.28   09 Apr 2015 05:24:00   RJamloki
 * Fix for recal 900. Initialized InitForceEstimateBuffer to true at places where making PartContact flag false.
 * 
 *    Rev 1.27   27 Mar 2015 14:18:30   RJamloki
 * Defauting CurrentState DoorOpen to FALSE after Inp.dooropen is removed
 * 
 *    Rev 1.26   11 Mar 2015 09:16:58   amaurya
 * PushPopMinPressure() removed.
 * 
 *    Rev 1.25   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.24   12 Dec 2014 05:30:04   RJamloki
 * Setting WeldPressure to min at Horn Down exit if th user selects below min value
 * 
 *    Rev 1.23   11 Dec 2014 08:36:16   AnPawar
 * changes for pressure changes. 
 * 
 *    Rev 1.22   28 Nov 2014 07:38:10   rjamloki
 * changed to remove warning "unused variable".
 * 
 *    Rev 1.21   14 Nov 2014 10:26:26   AnPawar
 *  change in function VGAProcessHornDownMsg() for automated down speed tuning
 * 
 *    Rev 1.20   14 Nov 2014 05:28:56   rjamloki
 * VGAProcessHornDownMsg() prototype removed.
 * 
 *    Rev 1.19   12 Nov 2014 17:04:56   tayars
 * Made fix so that tuned value is used in horn down
 * 
 *    Rev 1.18   10 Nov 2014 11:22:38   RJamloki
 * Removed operating pressure update call during horn down
 * 
 *    Rev 1.17   06 Oct 2014 06:39:58   AnPawar
 * removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.16   26 Sep 2014 03:14:26   rjamloki
 * Removed psos references
 * 
 *    Rev 1.15   11 Sep 2014 16:51:34   rjamloki
 * ExitHD changed to assert event reason menu if a reason is pending
 * 
 *    Rev 1.14   05 Sep 2014 04:56:50   rjamloki
 * Horn Down downspeed fix.
 * 
 *    Rev 1.13   18 Aug 2014 01:44:02   rjamloki
 * Added MICRO and AE support
 * 
 *    Rev 1.12   28 Jul 2014 12:48:58   rjamloki
 * Enabled pressure check during horn down as part of review comment fix
 * 
 *    Rev 1.11   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   21 May 2014 10:48:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 03:33:34   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.8   14 Apr 2014 10:15:38   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.7   26 Mar 2014 12:22:58   rjamloki
 * HornDownISR(),HDStartTimer(),DoHornDownFunc() function changed.Added printf to HDShowResult(). 
 * 
 *    Rev 1.6   06 Mar 2014 11:03:52   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:34   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:44   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION -----------------------------

   Module name:

   Filename: menuhorn.c

   Function name:

  ----------------------------- INCLUDE FILES ------------------------------*/

#include "qdef.h"
#include "actnvram.h"
#include "string.h"
#include "portable.h"
#include "menu.h"
#include "menu1.h"
#include "param.h"
#include "preset.h"
#include "weld_obj.h"
#include "genrlmsg.h"

#include "digout.h"
#include "beep.h"
#include "fpled.h"
#include "opcodes.h"
#include "display.h"
#include "keypad.h"
#include "FrontPanelKeypadTask.h"
#include "getmsg.h"
#include "state.h"
#include "statedrv.h"
#include "alarms.h"
#include "alsetup.h"
#include "ready.h"
#include "selctkey.h"
#include "menuhorn.h"
#include "util.h"
#include "mansensr.h" /* SetPV */
#include "encoder.h"
/* For VGA support */
#include "inports.h"
#include "command.h"
#include "stdio.h"
#include "weldhold.h"
#include "FlowLookupTable.h"
#include "Events.h"
#include "ticks.h"
#include "spidd.h"

void InitVelocityData(void);   /* These prototypes aren't in any .H files */
void CollectVelocityData(SINT32 NewDistance);
SINT32 CalculateVelocity(void);

extern BOOLEAN StateMachineDisabled;
/*------------------------------- LOCAL DEFINES ----------------------------*/

#define NEXT_MSG       0   /* No additional action, just get next message */
#define EXIT_HD        1   /* Causes exit from HD mode */
#define NEXT_MENU      2   /* Within HD mode, displays next screen */
#define DISPLAY_UPDATE 3
#define SCROLL_MENU    4
#define RESTART_HD     5

#define PREREADY_MSG_WAIT_TIME   50    /* Max time to wait for an event in */
                                       /* PREREADY before checking         */
                                       /* conditions again.                */

#define HD_UPDATE_RATE        250       /* Ms between screen updates */

#define MAX_TRIGGER_LOST_TIME 60000    /* Don't tell user when trigger lost */
                                       /* if more time than this. */

#define NUM_TIMERS   4      /* Only 16 timers max allowed in message format */

   /* Define event ID codes.  These guarantee that a TIMERx_EXPIRED message */
   /* was really caused by what we think it was.  Without IDs, some */
   /* function could set up a timer which expires just as the function */
   /* decides to exit for another reason.  A TIMER_EXPIRED message will go */
   /* in the queue, to be read out by the next function, which may think */
   /* the messsage means something else.  IDs allow function to identify */
   /* its own events so this won't happen. */

#define TRIGGER_LOST_EVENT 1
#define HD_DISPLAY_UPDATE  2
#define PBS_STUCK_EVENT    3
#define NO_UL_EVENT        4
#define PB_SPLIT_EVENT     5
#define NO_UL_CLEAR_EVENT  6
#define HD_CHECK_READY     7

   /* The following #defines specify in more detail what caused a change */
   /* from one HD screen to another. This information is passed to the */
   /* CloseMenu() routine for each screen. */

#define HD_RESTART   0     /* Something happened, want to restart HD mode */
#define HD_MANUAL    1     /* ULS clear before PBs, go to manual mode */
#define HD_ADVANCE   2     /* Conditions for advance to next screen met */
#define HD_RESULT    3     /* Skip ahead to result screen */

#define SYS_PRESS_ITEM  1         /* Item # of system pressure on start menus   */
#define FORCENOTREACHED 9999      /* This is used to keep horn down clamp = OFF */
                                  /* repeatadly checking system pressure        */
#define MAX_DOWN_SPEED 100                                  


/*--------------------------- LOCAL TYPE DECLARATIONS -----------------------*/

struct HornDownState {
   UINT16 OnePB :1;
   UINT16 BothPB :1;
   UINT16 Estop :1;
   UINT16 OnPart :1;
   UINT16 Trigger :1;
   UINT16 DoorOpen :1;
   UINT16 uls :1;
   UINT16 ECycleAbort :1;
   UINT16 PwrOff :1;
   UINT16 Unused :7;
};

struct MenuInfo;

union MResults
{
   struct
   {
      UINT32 ExitKey;
   } ExitHD;
   struct
   {
      UINT32 CloseParam;
      struct MenuInfo *NextMenu;
   } NextMenu;
   struct
   {
      UINT32 Devices;
   } ScrollMenu;
   struct
   {
      UINT16 StartItem;
      UINT16 EndItem;
   } DisplayUpdate;
};

struct MenuInfo
{
   UINT16   FullMenuID;              /* Points to all items on menu */
   void     (*OpenMenu)( struct MenuInfo *Menu);
   UINT16   (*ProcessMessage)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*ChrReceivedHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*SelectKeyHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*ControlMessageHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*SpecialMessageHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   void     (*CloseMenu)( UINT32 CloseParam );
};

struct HornDownTimer
{
   UINT32 Count;        /* Duration to time for */
   UINT16 Id;           /* Distinguishing ID to send with timeout msg */
};

UINT16 HDRTAlreadySetFlag; /* the real RTAlreadySetFlag is in ready.c */
BOOLEAN VGAHornDown = FALSE;
BOOLEAN VGAHDAlarm = FALSE;
BOOLEAN VGAExitHDMenu = FALSE;
BOOLEAN VGAHornVarEntry = FALSE;
UINT16 HDMenuID=0;
HdTempParamSet HdParams;
/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT16 PartContactFlag;       
extern INBITS Inp;
extern UINT16 ExternalCycleAbortGoneFlag;
extern UINT16 AlarmCounter;
extern BOOLEAN ECycleHistFlag;
extern UINT8  AETrigger;
extern enum  WELDSTATES WeldState;

extern enum WELD_SEQUENCE_TYPE CurrentSequence;

extern SINT32 EncoderPos;
extern SINT32 CurrentForce;            /* Actual horndown force */  
extern SINT32 Distance1;               /* Distance 1-3 used to determine part contact*/


extern UINT16 SystemPressureCheck;      

extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN StateMachineDisabled;
void  ExitMenuAndEnableWeld (void);

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

BOOLEAN HornDownFlag = FALSE;     /* When TRUE disables state machine */
UINT16 SystemPres60PSI;
UINT16 SystemPres80PSI;
UINT16 VGAAction;
struct MenuInfo VGAHDMenu;
union  MResults VGAMessageResults;


/*----- TEMPORARY FUNCTION PROTOTYPES -----*/

UINT16 Downspeed;

/*-------------------------- LOCAL FUNCTION PROTOTYPES ---------------------*/

void CheckForRapidTraverse(void);
static void HDProcessEstop(void);
static void GetHornDownState( struct HornDownState *CurrentState );
static void HDStartTimer( UINT8 Timer, UINT32 Count, UINT16 Id );

void StdOpenMenu( struct MenuInfo *Menu);
UINT16 StdProcessMessage( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDAESelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDAEDSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 NoSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdControlMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDCloseMenu( UINT32 CloseParam );

void HDWaitPBsAEOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPBsAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitReadyAEOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitReadyAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitPBsAEOpenMenu( struct MenuInfo *Menu);
void HDWaitPBsAECloseMenu( UINT32 CloseParam );
void HDWaitULSAEOpenMenu( struct MenuInfo *Menu);
void HDWaitULSAECloseMenu( UINT32 CloseParam );
void HDWaitTrigAECloseMenu( UINT32 CloseParam );

void HDResultCloseMenu( UINT32 CloseParam );
void HDWaitReadyAEDOpenMenu( struct MenuInfo *Menu);
//void HDWaitReadyAEFOpenMenu( struct MenuInfo *Menu);

UINT16 HDWaitReadyAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitULSAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitReadyAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitPBsAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPBsAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitTrigAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitPBsAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitULSAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitULSAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitULSAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitULSAEDAEFCloseMenu( UINT32 CloseParam );
void HDWaitPartAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPartAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitPartAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitPartAEDCloseMenu( UINT32 CloseParam );
//void HDWaitPartAEFCloseMenu( UINT32 CloseParam );

void HDWaitTrigAEDAEFOpenMenu( struct MenuInfo *Menu);

UINT16 HDWaitTrigAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitTrigAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitTrigAEDAEFCloseMenu( UINT32 CloseParam );
void HDResultAEDAEFOpenMenu( struct MenuInfo *Menu);
void HDWaitPartAEDAEFManOpenMenu( struct MenuInfo *Menu);

UINT16 HDResultAEDChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDResultAEFChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDResultAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDResultAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitPartAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitPartAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitTrigAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDWaitTrigAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDResultAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
//UINT16 HDResultAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitTrigAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitReady( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPBs( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitULS( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPart( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
UINT16 HDWaitTrigger( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
UINT16 HDShowResult( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
void HDSplitMessage( UINT32 *Message, UINT16 *Timer, UINT16 *Id );
void ProcessHDButtonPress1(void); 
void ProcessHDButtonPress2(void); 
void ProcessHDButtonPress3(void); 
void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage);


/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                      (scope is global to THIS file)                      */

STR HDBottomHalfBufName[VGA_LINESIZE];

STR *Str_HDBottomHalf[] =   { HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName };

static BOOLEAN VGAGnrlAlarmStateBeforeEstop;
static BOOLEAN VGAEstopFlag = FALSE;
static struct HornDownTimer HornDownEventTimer[NUM_TIMERS];
static struct HornDownState LastHDState; /* Compares to this, sends msgs */
UINT16 HDShowPressure;            /* Controls display of sys pressure */
UINT16 HDShowVelocity;            /* Controls display of velocity item */
UINT16 HDShowForce;               /* Controls display of force item */
static BOOLEAN HDCollectVelData,HDReadyState = TRUE;
SINT32 HornDownVelocity;
SINT32 HDPosition;             /* Same as EncoderPos but never < 0 */
static SINT32 SaveTriggerForce;       /* Save trig force for welding here */
SINT32 WorkingForceSet;        /* Temporary target pressure         */   

SINT32 RTTransitionDist;       /* Rapid Traverse Transition distance */

UNION_BOOL_UINT16 KeepHornDown;           /* TRUE to keep horn down after PB release */
UINT16 RapidTraverseState;            /* TRUE for rapid traverse */

const struct MenuInfo HornDownStartAE = {  REFRESH_MENU_AE,
                                           HDWaitReadyAEOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAESelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitReadyAESpecialMessageHandler,
                                           HDCloseMenu
                                         };

const struct MenuInfo HornDownStartAED = { REFRESH_MENU_AED, 
                                           HDWaitReadyAEDOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEDSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitReadyAEDSpecialMessageHandler,
                                           HDCloseMenu
                                         };

const struct MenuInfo HornDownWaitPBsAED = { REFRESH_MENU_AED, 
                                           HDWaitPBsAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEDSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPBsAEDSpecialMessageHandler,
                                           HDCloseMenu
                                         };

const struct MenuInfo HornDownWaitULSAED = { REFRESH_MENU_AED, 
                                           HDWaitULSAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitULSAEDSpecialMessageHandler,
                                           HDWaitULSAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAED = { RESULT_MENU,
                                           HDWaitPartAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEDSpecialMessageHandler,
                                           HDWaitPartAEDCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAED = { RESULT_MENU,
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEDSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownResultAED = { RESULT_MENU,
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           HDResultAEDChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEDSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAEDMan = { REFRESH_MENU_AEF2,
                                           HDWaitPartAEDAEFManOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEDManSpecialMessageHandler,
                                           HDWaitPartAEDCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEDMan =  { RESULT_MENU,
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEDManSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownResultAEDMan =   { RESULT_MENU,
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEDManSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownWaitPBsAE = { REFRESH_MENU_AE,
                                           HDWaitPBsAEOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAESelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPBsAESpecialMessageHandler,
                                           HDWaitPBsAECloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEMan = { RESULT_MENU_AE,
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEManSpecialMessageHandler,
                                           HDWaitTrigAECloseMenu
                                         };

const struct MenuInfo HornDownResultAEMan = { RESULT_MENU_AE,
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEManSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownWaitULSAE = { REFRESH_MENU_AE,
                                           HDWaitULSAEOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitULSAESpecialMessageHandler,
                                           HDWaitULSAECloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAE = { REFRESH_MENU_AE,
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAESpecialMessageHandler,
                                           HDWaitTrigAECloseMenu
                                         };

const struct MenuInfo HornDownResultAE = { RESULT_MENU_AE,
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           HDResultAEChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAESpecialMessageHandler,
                                           HDResultCloseMenu
                                         };
/*--------------------------------- CODE -----------------------------------*/


static void HDProcessEstop(void)
/****************************************************************************/
/*                                                                          */
/* Deals with ESTOP press.  Message "Emergency Stop" blinks on the screen   */
/* while the code waits for the ESTOP_RELEASED message.  All other messages */
/* are discareded except for POWER_OFF, which exits.  Note that if we ever  */
/* allow ESTOP to return to HD mode, we have to return something to exit on */
/* power-off!                                                               */
/*                                                                          */
/* This function also sets general alarm output and increments counter.     */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN Quit;
   BOOLEAN GeneralAlarmStateBeforeEstop;
   UINT32 NewKey;
   UINT32 TimeUntilBlink;

   GeneralAlarmStateBeforeEstop = CheckGeneralAlarmFlag();

   CurrentSetup.GenAlarmCount++;
   SetGeneralAlarm();
   SVOff();
   Quit = FALSE;

   do
   {
      ShowEstopMessageOn();
      TimeUntilBlink = MS_TO_TICKS( 200*4 );
      do
      {
         TimeUntilBlink = WaitMessage( TimeUntilBlink );
         if (TimeUntilBlink)     /* Pause interrupted by incoming message */
         {
            NewKey = RcvMsg(0) & ~MESSAGE_NEW;

            if ((NewKey == ESTOP_RELEASED) || (NewKey == POWER_OFF))
               Quit = TRUE;
         }

      } while (TimeUntilBlink && !Quit);

      ShowEstopMessageOff();

      if (!Quit)
      {
         TimeUntilBlink = MS_TO_TICKS( 200*4 );
         do
         {
            TimeUntilBlink = WaitMessage( TimeUntilBlink );
            if (TimeUntilBlink)
            {
               NewKey = RcvMsg(0) & ~MESSAGE_NEW;

               if ((NewKey == ESTOP_RELEASED) || (NewKey == POWER_OFF))
                  Quit = TRUE;
            }

         } while (TimeUntilBlink && !Quit);
      }

   } while (!Quit);

   if (!GeneralAlarmStateBeforeEstop)
      ClearGeneralAlarm();
}

void HornDownISR(void)
/****************************************************************************/
/*                                                                          */
/* This function provides 1ms interrupt support for Horn Down Mode.         */
/* includes checking for important events (ESTOP, palmbuttons, cycle abort, */
/* Tests for important events are performed and messages are sent to the    */
/* main Horn Down code in the menu task when something happens.             */
/*                                                                          */
/* Events which currently cause message output:                             */
/*                                                                          */
/*   Change in PB state                                                     */
/*   Change in ESTOP state                                                  */
/*   Timeout of event timer                                                 */
/*   Change in state of external cycle abort                                */
/*   Change in trigger state                                                */
/*   Change in DoorOpen state                                               */
/*   Change in ULS state                                                    */
/*                                                                          */
/****************************************************************************/
{
   struct HornDownState CurrentHDState;
   UINT32 Timer;
   UINT16 *Last, *Current;             /* Need this to compare structs */

   if (EncoderPos < 60000)      /* Don't display - encoder positions */
      HDPosition = EncoderPos;
   else
      HDPosition = 0;

   /* The next if () block is necessary because GetInputData() won't turn */
   /* off ECycleAbort bit.  Don't know why this is, but if it's ever */
   /* fixed this code can be removed. */

   if (ExternalCycleAbortGoneFlag)
   {
      ECycleHistFlag = FALSE;
      ExternalCycleAbortGoneFlag = FALSE;
   }

   /* Important safety check: If horn moves more than TRIGGERLOSTDISTANCE   */
   /* and still hasn't built up 35 lbs force, clear Trigger, turn off valve */
   /* so horn must come up (even if other code is not working right), send  */
   /* message to menu task telling it to quit result screen. */

   if ((CurrentSetup.Actuator == AED)
        || (CurrentSetup.Actuator == AES)
		|| (CurrentSetup.Actuator == MICROC)
        || (CurrentSetup.Actuator == MICRO)) {
      /* test at part contact */
      if ( (CurrentForce < TRIGGERLOSTFORCE) && (PartContactFlag == TRUE) &&
           (EncoderPos > (Distance1 + (SINT32) TRIGGERLOSTDISTANCE)) )
      {
         SVOff();
         PartContactFlag = FALSE;
         Inp.Trigger = FALSE;
         InitForceEstimateBuffer = TRUE;
         SendMsg( BAD_TRIGGER );
      }
      /* Test for lifting off the part */
      if (EncoderPos < (Distance1 - (SINT32) NEGTRIGGERLOSTDISTANCE) )
      {
         SVOff();
         PartContactFlag = FALSE;
         InitForceEstimateBuffer = TRUE;
         Inp.Trigger = FALSE;
         SendMsg( TRIGGER_OFF );
      }

   }

   /* The only routine to call GetHornDownState() is this one. */
   /* Within HornDownISR(), CurrentHDState is an automatic variable. */

   GetHornDownState( &CurrentHDState );   /* Get current system state */

   Last = (UINT16*)&LastHDState;
   Current = (UINT16*)&CurrentHDState;

   if (*Current != *Last)                 /* Something changed, send msg */
   {
      if ((CurrentHDState.OnePB != LastHDState.OnePB) ||
       (CurrentHDState.BothPB != LastHDState.BothPB))
      {
         if (!CurrentHDState.OnePB && !CurrentHDState.BothPB)
            SendMsg( NO_PB_PRESSED );
         else if (CurrentHDState.OnePB && !CurrentHDState.BothPB)
            SendMsg( ONE_PB_PRESSED );
         else if (CurrentHDState.BothPB)
            SendMsg( BOTH_PB_PRESSED );
      }
      if (CurrentHDState.Estop != LastHDState.Estop)
      {
         if (CurrentHDState.Estop)
            SendMsg( ESTOP_PRESSED );
         else
            SendMsg( ESTOP_RELEASED );
      }
      if (CurrentHDState.OnPart != LastHDState.OnPart)
      {
         if (CurrentHDState.OnPart)
            SendMsg( PART_CONTACT );
      }
      if (CurrentHDState.Trigger != LastHDState.Trigger)
      {
         if (CurrentHDState.Trigger)
            SendMsg( TRIGGER_ON );
         else
            SendMsg( TRIGGER_OFF );
      }

      if (CurrentHDState.DoorOpen != LastHDState.DoorOpen)
      {
         if (CurrentHDState.DoorOpen)
            SendMsg( DOOR_OPEN );
         else
            SendMsg( DOOR_CLOSED );
      }
      if (CurrentHDState.uls != LastHDState.uls)
      {
         if (CurrentHDState.uls)
            SendMsg( UPPER_LIMIT_ON );
         else
            SendMsg( UPPER_LIMIT_OFF );
      }
      if (CurrentHDState.ECycleAbort != LastHDState.ECycleAbort)
      {
         if (CurrentHDState.ECycleAbort)
            SendMsg( ECYCLE_ABORT_ON );
         else
            SendMsg( ECYCLE_ABORT_OFF );
      }
      if (CurrentHDState.PwrOff != LastHDState.PwrOff)
      {
         if (CurrentHDState.PwrOff)
            SendMsg( POWER_OFF );
      }
      LastHDState = CurrentHDState;
   }
   /* Check timers and send timeout messages if necessary */

   for (Timer = 0; Timer < NUM_TIMERS; Timer++)
   {
      if (HornDownEventTimer[Timer].Count)   /* If nonzero, timer is active */
      {
         if (!(--(HornDownEventTimer[Timer].Count)))
            SendMsg( TIMER_EXPIRED + (Timer << TIMER_NUM_BITPOS) +
             (HornDownEventTimer[Timer].Id << TIMER_ID_BITPOS));
      }
   }

   if (HDCollectVelData) /* Collect velocity data if desired */
   {
      CollectVelocityData( HDPosition );
      CheckForRapidTraverse();
   }
}

void CheckForRapidTraverse(void)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   if((RapidTraverseState & BIT0) == BIT0)
   {
      if((HDPosition >= RTTransitionDist) && (PartContactFlag == FALSE)
            && (HDRTAlreadySetFlag == FALSE))
      {
      SetPV((UINT16)CurrentSetup.HornDownSpd,RT_TO_DWNSPD);
      HDRTAlreadySetFlag = TRUE;
      }
   }
}

static void GetHornDownState( struct HornDownState *CurrentState )
/****************************************************************************/
/*                                                                          */
/* Fulfills logic required to separate door and trigger. On AED or AEF,     */
/* uses ULS to aid in decision. Also fills in the HornDownState struct      */
/* with info from current inputs.                                           */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN TrigState;


   CurrentState->OnePB = Inp.OnePB;
   CurrentState->BothPB = Inp.BothPB;
   CurrentState->Estop = Inp.Estop;

   /* Trigger & door open functions are on the same bit on AE actuator.  */
   /* The value of AETrigger reflects the state of this bit.  If at upper */
   /* limit, AETrigger is assumed to indicate the door status; if not at */
   /* upper limit, it's assumed to indicate the trigger status. */

   if (CurrentSetup.Actuator == AE)
   {
      if (!AETrigger)          /* If bit is off, can't have trigger or door */
      {
         CurrentState->Trigger = FALSE;
         CurrentState->DoorOpen = FALSE;
      }
      else
      {
         if (Inp.uls)                       /* If at U.L., it's the door */
         {
            CurrentState->Trigger = FALSE;
// sbeam level 1 build            CurrentState->DoorOpen = TRUE;
            CurrentState->DoorOpen = FALSE;

         }
         else                               /* If not at U.L., it's trigger */
         {
            CurrentState->Trigger = TRUE;
            CurrentState->DoorOpen = FALSE;
         }
      }
   }
   else     /* For non-AE actuators */ 
   {
      TrigState = Inp.Trigger;   /* Initially use same as Inp.Trigger */
      
      if (Inp.uls)      /* If at upper limit, can't have trigger */
      {
         Inp.Trigger = FALSE;
         TrigState = FALSE;
      }
      else
      {                       /* must have no ULS to read CurrentForce */

         /* Check for trigger lost.  Will clear trigger in HD state info */
         /* if force falls below MinLimit, but won't clear Inp.Trigger. */
         /* This allows force back over MinLimit to turn trigger back on. */
         /*  Code receiving TRIGGER_OFF messages will deal with brief */
         /* losses of trigger. */

         if (Inp.Trigger)
         {
				if (CurrentForce < MinLimit.TriggerForce)
					TrigState = FALSE;
         }
      }
      CurrentState->Trigger = TrigState;
      CurrentState->DoorOpen = FALSE;
   }

   if (HDCollectVelData)      /* Test flag that will indicate whether */
   {                          /* or not horn is on the part */
      if (PartContactFlag)
         CurrentState->OnPart = TRUE;
      else
         CurrentState->OnPart = FALSE;
   }
   else
      CurrentState->OnPart = FALSE;

   CurrentState->uls = Inp.uls;
   CurrentState->ECycleAbort = ECycleHistFlag;
   CurrentState->PwrOff = Inp.PwrOff;
   CurrentState->Unused = 0;        /* Same state always returns same code */
}

static void HDStartTimer( UINT8 Timer, UINT32 Count, UINT16 Id )
/****************************************************************************/
/*                                                                          */
/* Starts a timer to time an event.  The HornDownISR() will decrement any   */
/* nonzero timer, and will send an event message if the timer expires.  An  */
/* ID code, supplied here, is also sent with the event message, so that if  */
/* an event message was sent but not read by the function that set up the   */
/* timer, a later function that reads the message will know to discard it.  */
/*                                                                          */
/* Parameters:                                                              */
/*                                                                          */
/*    Timer - Which timer to use                                            */
/*    Count - Time before message send, in ms                               */
/*    Id    - ID code.  May be anything as long as it's unique              */
/*                                                                          */
/****************************************************************************/
{

   /* Must disable interrupts here while new value & id are being assigned */
   /* to the timer, otherwise, if timer expires with half of data written */
   /* (either just Id or with just new Count), ID for wrong event will be */
   /* sent.  It's probably safe to leave ints on and write new value first, */
   /* since it's unlikely that it will count all the way down before next */
   /* line of code gets to run, but we're being ultra-conservative here. */
   SR sr = EnterCritical();
   HornDownEventTimer[Timer].Count = Count;
   HornDownEventTimer[Timer].Id = Id;
   ExitCritical(sr);
}

void StdOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to open a menu. Given a menu object, it figures out */
/* which of the menu items that could potentially appear on this menu need  */
/* to be displayed now, and saves a count of how many items this is in the  */
/* menu object. Also, the current position on the output devices is set up  */
/* as specified in the object data.                                         */
/* returned, and previous menu should be displayed.                         */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Menu - Pointer to menu object                                         */
/*                                                                          */
/****************************************************************************/
{
	Menu = NULL;

}


UINT16 StdProcessMessage( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a message. All that it does is access    */
/* the message type and pass the message to the appropriate handler.        */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Menu - Pointer to menu object                                         */
/*    Message - Message to process                                          */
/*    MessageResults - Pointer to structure containing additional           */
/*                     instructions for the caller. What this contains      */
/*                     depends on this function's return value.             */
/*                                                                          */
/* Output:                                                                  */
/*                                                                          */
/*    Action code - Tells the caller what to do.  Will be one of:           */
/*                                                                          */
/*       NEXT_MSG - Just get the next message & process it                  */
/*                                                                          */
/*       EXIT_HD  - Special for HD mode, exits to old menu, menu to go to   */
/*                  (MainKey, RunKey, etc) specified in MessageResults.     */
/*                                                                          */
/*       NEXT_MENU - Changes to another menu object. MessageResults         */
/*                   contains pointer to next menu, also a parameter to     */
/*                   pass to Close routine for the current menu.            */
/*                                                                          */
/*       DISPLAY_UPDATE - Regenerate & redraw menu items specified in       */
/*                        MessageResults.                                   */
/*                                                                          */
/*       SCROLL_MENU - Redraw screen on devices indicated by MessageResults.*/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 MessageType;

   MessageType = (Message & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;

   switch( MessageType )
   {
      case CHR_RECEIVED_MSG:
         Action = Menu->ChrReceivedHandler( Menu, Message, MessageResults );
         break;

      case SELECT_MSG:
         Action = Menu->SelectKeyHandler( Menu, Message, MessageResults );
         break;

      case CONTROL_MSG:
         Action = Menu->ControlMessageHandler( Menu, Message, MessageResults );
         break;

      case SPECIAL_MSG:
         Action = Menu->SpecialMessageHandler( Menu, Message, MessageResults );
         break;

      default:
         Action = NEXT_MSG;
         break;
   }
   return( Action );
}

UINT16 StdChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process an input keystroke message. Provides     */
/* default processing for menu keys, GoBack, terminal data mode toggle,     */
/* arrow keys. Inputs & outputs same as StdProcessMessage().                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 StartLine, TermStartLine;

   switch( Message )
   {
      case MAIN_KEY:
      case RUN_KEY:
      case SETUP_KEY:
      case PRINT_KEY:
         Action = EXIT_HD;
         MessageResults->ExitHD.ExitKey = Message;
         break;

      case GOBACK_KEY:
         Action = EXIT_HD;
         MessageResults->ExitHD.ExitKey = 0;
         break;

      case PG_UP_KEY:
      case PG_DOWN_KEY:
      case UP_KEY:
      case DOWN_KEY:
         StartLine = 1;
         TermStartLine = 1;

         switch( Message )
         {
            case PG_UP_KEY:
               break;

            case PG_DOWN_KEY:
               break;

            case UP_KEY:
               break;

            case DOWN_KEY:
               break;

            default:       /* This should never happen */
               break;
         }

         MessageResults->ScrollMenu.Devices = 0;

         /* A bit of glue here between old code and new code.  By looking */
         /* at first line to update based on scroll (StartLine), can tell */
         /* whether or not screen needs to be updated.  This number will */
         /* always be 1 if the screen scrolled, meaning "update from the */
         /* top line of the screen".  It will be a number greater than */
         /* the last screen line if the device doesn't need to scroll. */

         if (StartLine == 1)
            MessageResults->ScrollMenu.Devices |= VF_DEVICE_BIT;

         if (TermStartLine == 1)
            MessageResults->ScrollMenu.Devices |= TERM_DEVICE_BIT;

         if (MessageResults->ScrollMenu.Devices)
            Action = SCROLL_MENU;   /* If any device needs to scroll, */
         else                       /* return SCROLL_MENU, otherwise */
            Action = NEXT_MSG;      /* do nothing, get another message. */
         break;

      case DATA_KEY:
         Action = SCROLL_MENU;  /* Will redraw screen without re-generating */
         MessageResults->ScrollMenu.Devices = VF_DEVICE_BIT | TERM_DEVICE_BIT;
         break;                 /* menu items. */

      default:
         Action = NEXT_MSG;
         Beep(ERRORBEEP);
   }
   Menu = NULL;
   return( Action );
}

void HDWaitTrigAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   if (CloseParam != HD_ADVANCE)
      SVOff();              /* Didn't work, bring horn back up */

   TrigSwInactv();
}

UINT16 HDResultAEChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   if (Message == HORNDOWN_KEY)
   {
      Action = NEXT_MENU;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
      MessageResults->NextMenu.CloseParam = 0;
   }
   else
      Action = StdChrReceivedHandler( Menu, Message, MessageResults );

   return( Action );
}

UINT16 HDAESelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode, AE actuator. After the      */
/* selected item is edited, system goes back to WaitReady state and waits   */
/* for READY again before advancing.                                        */
/*                                                                          */
/****************************************************************************/
{
   MessageResults->NextMenu.CloseParam = HD_RESTART;
   MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   Menu = NULL;
   Message = 0;
   return( NEXT_MENU );
}

UINT16 HDAEDSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode, AED actuator. Same as AE    */
/* version except that menu for WaitReady is different.                     */
/*                                                                          */
/****************************************************************************/
{
   MessageResults->NextMenu.CloseParam = HD_RESTART;
   MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   Menu = NULL;
   Message = 0;
   return( NEXT_MENU );
}

UINT16 NoSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode when there are no items on   */
/* the screen that can be edited. Just beeps and tells caller to process    */
/* the next message.                                                        */
/*                                                                          */
/****************************************************************************/
{
   Beep( ERRORBEEP );
   Menu = NULL;
   Message = 0;
   MessageResults = NULL;
   return( NEXT_MSG );
}

UINT16 StdControlMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a control message. Provides default      */
/* processing for messages which blink the terminal ALARM message, handle   */
/* ESTOPs and power-off. Inputs & outputs same as StdProcessMessage().      */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action = NEXT_MSG;

   switch( Message )
   {
      case TERM_DATA_OUTPUT:
         Action = NEXT_MSG;
         break;

      case UPDATE_TERM_ALARM:
         Action = NEXT_MSG;
         break;

      case ESTOP_MSG_ON:
         ShowEstopMessageOn();
         Action = NEXT_MSG;
         break;

      case ESTOP_MSG_OFF:
         ShowEstopMessageOff();
         Action = NEXT_MSG;
         break;

      case ESTOP_PRESSED:
         if(VGAHornDown)
         {
            Action = EXIT_HD;
         }
         else
         {
            HDProcessEstop();  /* Blink message until ESTOP goes away */
            Action = EXIT_HD;  /* Will cause exit from HD mode */
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;
      
      case ESTOP_RELEASED:
         if(VGAHornDown && VGAEstopFlag)
         {
            if (!VGAGnrlAlarmStateBeforeEstop)
               ClearGeneralAlarm();
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }            
         break;
          
      case POWER_OFF:
         Action = EXIT_HD;       /* Leave HD, let regular code handle this */
         MessageResults->ExitHD.ExitKey = 0;
         break;

      default:
         Action = NEXT_MSG;
         break;

   }
   Menu = NULL;
   return( Action );
}

UINT16 StdSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a "special" message. By definition, this */
/* type of message is menu-specific, so there isn't anything we can do here */
/* except throw out the message and tell the caller to get the next one.    */
/* This routine should only be used in menus that don't expect any special  */
/* messages.                                                                */
/*                                                                          */
/****************************************************************************/
{
	Message = 0;
	MessageResults = NULL;
	Menu = NULL;
	return( NEXT_MSG );
}


void HDCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/* CloseMenu() routine for horn down mode, shared by all horn down menus.   */
/* It is called as each "state" is ended, before the next state is started, */
/* to make sure any timers used by the previous state are cleared. Let the  */
/* following state allocate timers as it desires.                           */
/*                                                                          */
/****************************************************************************/
{

   HornDownEventTimer[0].Count = 0;
   HornDownEventTimer[1].Count = 0;
   HornDownEventTimer[2].Count = 0;
   HornDownEventTimer[3].Count = 0;
   CloseParam = 0;
}


/****************************************************************************/
/*                                                                          */
/*                         HORN DOWN MENU FUNCTIONS                         */
/*                         ========================                         */
/*                                                                          */
/* The following group of functions implement the horn down menus. They     */
/* call the base menu class functions when necessary and add their own      */
/* procssing on top. There are presently six lines of execution: AE auto    */
/* AE manual, AED automatic, AED manual, AEF manual, and AEF automatic.     */
/* Sometimes functions can be used in more than one line. The syntax for    */
/* function names is as follows:                                            */
/*                                                                          */
/*    HD(stage name)(actuator)[Man](function)                               */
/*                                                                          */
/* The (stage name) is either WaitReady, WaitPBs, WaitULS, WaitPart,        */
/* WaitTrigger, or ShowResult. (actuator) is AE or AED or AEF. The [Man] is */
/* included for functions specific to manual mode, and (function) is the    */
/* name of the menu member function, either OpenMenu, CloseMenu, or         */
/* SpecialMessageHandler.                                                   */
/*                                                                          */
/* Example: Using this syntax, the name of the function that handles        */
/* special messages on an AED actuator while waiting for trigger in         */
/* automatic mode is HDWaitTriggerAEDSpecialMessageHandler().               */
/*                                                                          */
/* Some parts of the name may be eliminated if a function can be used in    */
/* multiple menus. For example, the function to close the result menu is    */
/* HDResultCloseMenu(), and it is used for AE, AED, automatic, and manual.  */
/*                                                                          */
/****************************************************************************/

void HDWaitReadyAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = FALSE;

   StdOpenMenu( Menu);

   if (LastHDState.OnePB || LastHDState.BothPB) /* If PBs in, time release */
      HDStartTimer( 0, PBEXITTIME, PBS_STUCK_EVENT );

   if (!LastHDState.uls)             /* If not at upper limit, time return */
      HDStartTimer( 1, UPPERLIMIT_TIMEOUT, NO_UL_EVENT );

   /* Use timer 3 to periodically check for READY */

   HDStartTimer( 3, PREREADY_MSG_WAIT_TIME, HD_CHECK_READY );

}

UINT16 HDWaitReadyAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitReady( Message, MessageResults );

   if (Action == NEXT_MENU)
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPBsAE;
   Menu = NULL;
   return( Action );
}

UINT16 HDResultAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)   /* Happens if trigger lost, just trig again */
   {
      Inp.Trigger = FALSE;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEMan;
   }
   return( Action );
}

void HDWaitPBsAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   TrigSwActv();     /* Do this before PBs or horn won't come down */
}

UINT16 HDWaitPBsAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPBs( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_MANUAL:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEMan;
            break;

         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitULSAE;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
            break;
      }
   }
   Menu = NULL;
   return( Action );
}

void HDWaitPBsAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
      TrigSwInactv();
}

void HDWaitULSAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   HDStartTimer( 0, UPPERLIMIT_TIMEOUT, NO_UL_CLEAR_EVENT );

   EnableSVOn();     /* Turn on SV to bring down horn */
   SVOn();

   LastHDState.ECycleAbort = 0;  /* Force message if abort is on */
}

UINT16 HDWaitULSAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitULS( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAE;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   Menu = NULL;
   return( Action );
}

void HDWaitULSAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
   {
      SVOff();              /* Didn't work, bring horn back up */
      TrigSwInactv();
   }
}

UINT16 HDResultAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)   /* This should never happen */
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;

   return( Action );
}


void HDResultCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );
   SVOff();
}

UINT16 HDWaitTrigAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEMan;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   return( Action );
}

void HDWaitReadyAEDOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;

   StdOpenMenu( Menu);

   if (LastHDState.OnePB || LastHDState.BothPB) /* If PBs in, time release */
      HDStartTimer( 0, PBEXITTIME, PBS_STUCK_EVENT );

   
   if (!LastHDState.uls)             /* If not at upper limit, time return */
      HDStartTimer( 1, UPPERLIMIT_TIMEOUT, NO_UL_EVENT );

   /* Use timer 2 to update system pressure on the screen */

   HDStartTimer( 2, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   /* Use timer 3 to periodically check for READY */

   HDStartTimer( 3, PREREADY_MSG_WAIT_TIME, HD_CHECK_READY );
     /* In order to use part contact algorithm, the RunningPreset.TriggerForce must
      be changed when in Horn Down and changed back on exit from Horn Down 
      (ref. ReadACTADC) */
   if(KeepHornDown.boolEAN == TRUE)
      RunningPreset.TriggerForce = MinLimit.TriggerForce;
   else
      RunningPreset.TriggerForce = FORCENOTREACHED;  /* set trigger force to a value */
                                                     /* that cannot be reached       */
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
}

UINT16 HDWaitReadyAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitReady( Message, MessageResults );

   if (Action == NEXT_MENU)
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPBsAED;
	Menu = NULL;
   return( Action );
}

void HDWaitPBsAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);
   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDWaitPBsAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPBs( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_MANUAL:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAEDMan;
            break;

         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitULSAED;
            ZeroEncoder();
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   Menu = NULL;
   return( Action );
}

void HDWaitULSAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/* OpenMenu is the first function called for each state. It is called one   */
/* time at state entry. This version is used by both AED and AEF. This is   */
/* the place for code which will be executed once at entry to state.        */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   HDStartTimer( 0, UPPERLIMIT_TIMEOUT, NO_UL_CLEAR_EVENT );

   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   EnableSVOn();     /* Turn on SV to bring down horn */
   SVOn();

   InitVelocityData();  /* Prepare for velocity data collection */
   HDCollectVelData = TRUE;   /* Start doing it */
   LastHDState.ECycleAbort = 0;  /* Force message if abort is on */
}

UINT16 HDWaitULSAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitULS( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAED;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   Menu = NULL;
   return( Action );
}


void HDWaitULSAEDAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/* Called when ULS is cleared                                               */
/*                                                                          */
/* Inputs : RapidTraverseState                                              */
/*          CurrentPreset.SetRTComp                                         */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   if(RapidTraverseState == TRUE)
   {
      if( Downspeed > MAX_DOWN_SPEED)
      {
         Downspeed = MAX_DOWN_SPEED;
      }   
      SetPV((UINT16)Downspeed,HOME_TO_RT);
   }
   else
      SetPV((UINT16)CurrentSetup.HornDownSpd,HOME_TO_DWNSPD);
   
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
   {
      SVOff();              /* Didn't work, bring horn back up */
      HDCollectVelData = FALSE;
   }
}

void HDWaitPartAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = FALSE;
   HDShowVelocity = FALSE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 0, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   LastHDState.OnPart = FALSE;   /* Force message if on part */
}

UINT16 HDWaitPartAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAED;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAED;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   return( Action );
}


void HDWaitPartAEDCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   HDCollectVelData = FALSE;  /* Stop collecting vel data once hit part */

   if (CloseParam == HD_RESTART)
      SVOff();              /* Didn't work, bring horn back up */
   else
      HornDownVelocity = CalculateVelocity(); /* Advancing, compute vel */
}

void HDWaitPartAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/* CloseMenu functions are the last functions called when a state change is */
/* taken. A CloseMenu function handles any remaining clean up work. For the */
/* AEF actuator, it is the time to set the proportional valve for the force */
/****************************************************************************/
{
   HDWaitPartAEDCloseMenu( CloseParam );

   if (CloseParam != HD_RESTART)
   {
      UpdateDistanceOffset();
      SetPV((UINT16)WorkingForceSet, TRG_TO_FORCE_A);
   }   
}

void HDWaitTrigAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;
   //Not checking for velocity reporting flag in Buc Menu
   if((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == AES))
	   HDShowVelocity = TRUE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 0, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDWaitTrigAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAE;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   return( Action );
}

UINT16 HDWaitTrigAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAED;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   return( Action );
}

void HDWaitTrigAEDAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
      SVOff();              /* Didn't work, bring horn back up */
}

void HDResultAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;
   //Not checking for velocity reporting flag in Buc Menu
   if((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == AES))
   	 HDShowVelocity = TRUE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDResultAEDChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   if (Message == HORNDOWN_KEY)
   {
      Action = NEXT_MENU;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
      MessageResults->NextMenu.CloseParam = 0;
   }
   else
      Action = StdChrReceivedHandler( Menu, Message, MessageResults );

   return( Action );
}


UINT16 HDResultAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)   /* This should never happen */
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;

   return( Action );
}


void HDWaitPartAEDAEFManOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDWaitPartAEDAEFOpenMenu( Menu);
   InitVelocityData();  /* Prepare for velocity data collection */
   HDCollectVelData = TRUE;   /* Start doing it */
}

UINT16 HDWaitPartAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEDMan;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEDMan;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   return( Action );
}


UINT16 HDWaitTrigAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEDMan;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   return( Action );
}


UINT16 HDResultAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)   /* Happens if trigger lost, just trig again */
   {
      Inp.Trigger = FALSE;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEDMan;
   }
   return( Action );
}

UINT16 HDWaitReady( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* Routine to implement WaitReady stage of HD operation. Waits for upper    */
/* limit, door closed, no PBs before trying HD sequence again. If a PB is   */
/* pressed or horn not at upper limit on entry, this is okay, as long as    */
/* these conditions are met within appropriate time limits.  However, once  */
/* PBs are released or upper limit is on, pressing a PB or leaving upper    */
/* limit will cause an immediate alarm.                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;

   HDSplitMessage( &Message, &Timer, &Id );

   switch( Message )
   {
      case ONE_PB_PRESSED:
      case BOTH_PB_PRESSED:                 /* Unless timing already, */
         if (!HornDownEventTimer[0].Count)  /* this should alarm now. */
            RecordAlarm( EQ17 );
         break;
               
      case NO_PB_PRESSED:
         HornDownEventTimer[0].Count = 0;    /* Stop timing PBs */
         break;

      case TIMER_EXPIRED:
         switch( Timer )
         {
            case 0:
               if (Id == PBS_STUCK_EVENT)
                 RecordAlarm( EQ17 ); /* Exit unless horn should stay down */
               break;

            case 1:
               if (Id == NO_UL_EVENT)
               {
                  RecordAlarm( EQ2 );    /* No upper limit */
               }
               break;

            case 2:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[2].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            case 3:
               if (Id == HD_CHECK_READY)
               {
                  
                  /* This timer is used to force regular tests for the    */
                  /* READY condition. When READY is achieved, we want to  */
                  /* move on to the next menu. In order to be READY, all  */
                  /* the conditions tested here must be correct, and also */
                  /* there must be no pending messages (because a pending */
                  /* message might indicate that one of these conditions  */
                  /* isn't what we think it is). */

                  if (!CheckIfResetRequired())  /* Try to clear alarms */
                     AlarmsReset = TRUE;                                    
                                   
                  if (!LastHDState.OnePB && !LastHDState.BothPB &&
                   LastHDState.uls && !LastHDState.DoorOpen &&
                   !LastHDState.Trigger && 
                   (!KeyAvailable(TRUE) || VGAHornDown))
                  {
                     Action = NEXT_MENU;
                     MessageResults->NextMenu.CloseParam = HD_ADVANCE;
                  }
                  else                        /* If not ready, try again later */
                     HornDownEventTimer[3].Count = PREREADY_MSG_WAIT_TIME;
               }
               break;

            default:
               break;
         }
         break;

      case DOOR_OPEN:
         RecordAlarm( EQ4 );
         break;

      case UPPER_LIMIT_ON:
         HornDownEventTimer[1].Count = 0;   /* Stop timing ULS */
         break;

      case UPPER_LIMIT_OFF:               /* Unless timing already, */
         
         if (!HornDownEventTimer[1].Count)/* alarm now (test of */
         {                                /* timer value is overkill) */

            /* Some klunky code: It is possible to get a ULS_OFF without */
            /* yet having found the system to be ready. For example, may */
            /* have just seen ULS_ON, causing state change to WaitForReady. */
            /* Before timer that checks for ready expires, ULS may change */
            /* to OFF. This should not cause an alarm unless there is some */
            /* other problem. So here we will check to see if system is */
            /* otherwise ready, and if so, will advance to the next state */
            /* and force the ULS_OFF message to come up again. */

            if (!CheckIfResetRequired())
               AlarmsReset = TRUE;

            if (!LastHDState.OnePB && !LastHDState.BothPB &&
             !LastHDState.DoorOpen && !LastHDState.Trigger)
            {
               Action = NEXT_MENU;
               MessageResults->NextMenu.CloseParam = HD_ADVANCE;
               LastHDState.uls = TRUE;    /* If still FALSE, will cause */
            }                             /* message to be sent again. */
            else
            {
               RecordAlarm( EQ2 );  /* Another reason for not ready, alarm */
            }
         }
         break;

      default:
         break;

   }
   return( Action );
}

void ResetHDAlarms(void)
{
   if(AlarmDetectedFlag == TRUE)
   {
      AlarmDetectedFlag = FALSE;
      AlarmOff();
      CycleAbort = FALSE;
      ClearAlarmFlag();       /* Clear Alarm flag                 */
      ClearGeneralAlarm();         /* Remove GeneralAlarm,suspect,&reject signals*/
      AlarmCounter = 0;     /* Also need to do this, was in StartPB() */
      WeldState = PBSTATE;  /* ClearAlarm() code will test this */
      ClearSetupAlarms();   /* Clear out previous alarms */
      ClearFinalResults();
   }
   else
      Beep(ERRORBEEP);
   
}

UINT16 HDWaitPBs( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* palm buttons.                                                            */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch( Message )
   {
      case ONE_PB_PRESSED:  /* One PB pressed, wait for other one */
      case BOTH_PB_PRESSED:

         /* If this is the first sight of PBs in here, then try to clear */
         /* those alarms that should be cleared at the start of a cycle. */

         if (!HornDownEventTimer[0].Count)
         {
            /* The following code was imported from WeldManager().  Seems */
            /* appropriate NOT to get WeldManager() involved, because we */
            /* aren't welding. */

            if(AlarmDetectedFlag == TRUE)
            {
               AlarmDetectedFlag = FALSE;
               AlarmOff();
               CycleAbort = FALSE;
               ClearAlarmFlag();       /* Clear Alarm flag                 */
               ClearGeneralAlarm();         /* Remove GeneralAlarm,suspect,&reject signals*/
            }
            AlarmCounter = 0;     /* Also need to do this, was in StartPB() */
            WeldState = PBSTATE;  /* ClearAlarm() code will test this */
            ClearSetupAlarms();   /* Clear out previous alarms */
            //ClearFinalResults();  TODO: This line was commented out for downspeed tuning testing. Not sure what the consequences are of doing this.
         }

         if (Message == ONE_PB_PRESSED)
            HDStartTimer( 0, PALMBUTTON_STAGGER_TIME, PB_SPLIT_EVENT );
         else
         {
            Action = NEXT_MENU;   /* Got what we want, get out now */
            MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         }
         break;

      case NO_PB_PRESSED:                 /* Must have had it & lost it */
         RecordAlarm( EQ12 );
         Action = NEXT_MENU;
         break;

      case TIMER_EXPIRED:
         switch( Timer )
         {
            case 0:
               if (Id == PB_SPLIT_EVENT)
               {
                  RecordAlarm( EQ12 );    /* Didn't get second PB */
                  Action = NEXT_MENU;     /* Start switch time alarm */
               }
               break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            default:
               break;
         }
         break;

      case DOOR_OPEN:
      case TRIGGER_ON:
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_OFF:
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_MANUAL;  /* Go manual mode */
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDWaitULS( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the upper limit switch to be cleared.                                    */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_OFF:
         Action = NEXT_MENU;      /* What we want, get out */
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TIMER_EXPIRED:
         switch (Timer)
         {
            case 0:
               if (Id == NO_UL_CLEAR_EVENT)  /* Didn't leave upper limit */
               {
                  RecordAlarm( NC1 );
                  Action = NEXT_MENU;
               }
               break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            default:
               break;
         }
         break;

      case ECYCLE_ABORT_ON:
         RecordAlarm( NC7 );
         Action = NEXT_MENU;
         break;

      case DOOR_OPEN:
         RecordAlarm( EQ4 );

         if (CurrentSetup.Actuator == AE)/* On AE, could be we hit     */
            RecordAlarm( EQ3 );          /* trigger without ULS clear, */
                                         /* so send alarm for this.    */
         Action = NEXT_MENU;
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDWaitPart( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the part contact.                                                        */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         if (!Manual)
         {
            Action = NEXT_MENU;
         }
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         if (!Manual)
            RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( NC7 );
            Action = NEXT_MENU;
         }
         break;

      case DOOR_OPEN:         /* Really shouldn't happen past UL */
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case PART_CONTACT:      /* This is good, get out */
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TRIGGER_ON:        /* Should do PART_CONTACT first, but if not, */
         Beep(TRIGGERBEEP);   /* just skip ahead to show results */
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_RESULT;
         break;

      case TIMER_EXPIRED:
         if (!Timer && Id == HD_DISPLAY_UPDATE)
         {
            Action = DISPLAY_UPDATE;
            HornDownEventTimer[0].Count = HD_UPDATE_RATE; /* repeat */
         }
         break;

      case BAD_TRIGGER:             /* Should really see TRIGGER_ON msg */
         if (!Manual)               /* first and get this on result */
         {                          /* screen, but test here just in case */
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20);
			VGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;
   }
   Menu = NULL;
   return( Action );
}

UINT16 HDWaitTrigger( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* trigger condition.                                                       */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         if (!Manual)
         {
            Action = NEXT_MENU;
         }
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         if (!Manual)
            RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( NC7 );
            Action = NEXT_MENU;
         }
         break;

      case DOOR_OPEN:         /* Really shouldn't happen past UL */
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case TRIGGER_ON:
         Beep(TRIGGERBEEP);
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TIMER_EXPIRED:
         if (!Timer && Id == HD_DISPLAY_UPDATE)
         {
            Action = DISPLAY_UPDATE;
            HornDownEventTimer[0].Count = HD_UPDATE_RATE; /* repeat */
         }
         break;

      case BAD_TRIGGER:             /* Should really see TRIGGER_ON msg */
         if (!Manual)               /* first and get this on result */
         {                          /* screen, but test here just in case */
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20); 
			VGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;
   }
   Menu = NULL;
   return( Action );
}

UINT16 HDShowResult( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the correct time to display final results.                               */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );
   
   switch(Message)
   {
      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( CM15 );
			VGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

   case TRIGGER_OFF: /* Lost trigger, time how long */
      if ((((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES)
    		  || (CurrentSetup.Actuator == MICROC)
    		  || (CurrentSetup.Actuator == MICRO)) && (KeepHornDown.boolEAN == TRUE))
    		  || (CurrentSetup.Actuator == AE)) {
         HDStartTimer(0, TRIGGERLOSTTIME, TRIGGER_LOST_EVENT);
      }
      break;

      case TRIGGER_ON:
         HornDownEventTimer[0].Count = 0;   /* Trigger back, stop timing */
         break;

   case TIMER_EXPIRED:
      switch (Timer) {
      case 0: /* Lost trigger too long, alarm */
         if (Id == TRIGGER_LOST_EVENT) {
            if (!Manual) {
               ActualHoldTime = MAX_TRIGGER_LOST_TIME - HornDownEventTimer[2].Count;
               RecordAlarm( CM1);
               Action = RESTART_HD;
               MessageResults->ExitHD.ExitKey = 0;
            }
            else
               Action = NEXT_MENU;
         }
         break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
         break;
            default:
               break;
         }
         break;

      case BAD_TRIGGER:
         if (!Manual)
         {
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20); /* case. */
			VGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;

   }
   Menu = NULL;
   return( Action );
}

void HDSplitMessage( UINT32 *Message, UINT16 *Timer, UINT16 *Id )
/****************************************************************************/
/*                                                                          */
/* Takes a given message and splits out the data field, which is assumed to */
/* indicate a timer # and a timer ID.  (If the message isn't TIMER_EXPIRED, */
/* nobody is going to look at the Timer and Id anyway).  After the timer    */
/* and Id are copied out, the data field is cleared so that the Message     */
/* variable may be used in a switch/case.                                   */
/*                                                                          */
/****************************************************************************/
{
   *Timer = (*Message & TIMER_NUM_FIELD) >> TIMER_NUM_BITPOS; /* Get timer */
   *Id = (*Message & TIMER_ID_FIELD) >> TIMER_ID_BITPOS;      /* Get ID */

   *Message &= (MESSAGE_TYPE_FIELD | MESSAGE_CODE_FIELD); /* Clear data */
}
   
void DoHornDownFunc(void)
/****************************************************************************/
/*Description:                                                              */
/* This function performs the Horn Down operation. Horn Down Process is     */
/* Exited when user presses any of the Bottom buttons ( Run, Setup, Main,-  */
/* Graphs ) or in any erroneous condtions (eg: Trigger lost).               */
/****************************************************************************/
{
   if ((GetCurrentSequenceType() == HORNDOWN) && (HornDownFlag == TRUE))
	   	   return;
   if (UserIOAlarmMenu || StateMachineDisabled)
      ExitMenuAndEnableWeld();
   VGAHornDown = FALSE;
   VGAEstopFlag = FALSE;
   VGAHDAlarm = FALSE;

   if (!VGAHornVarEntry)
   {
      KeepHornDown.boolEAN = TRUE;  /* set TRUE on each entry to do-horn-down */
      RTTransitionDist = CurrentPreset.RTDist;
      RapidTraverseState = FALSE;
   } 
   else
   {
      VGAHornVarEntry = FALSE;  
      StartStateMachine();
      SetReady(); 
   }
      
   /* First, set up LastHDState structure the way we think the system */
   /* should be now.  Any change from this will cause a message to be */
   /* sent. */

   LastHDState.OnePB = LastHDState.BothPB = LastHDState.Estop = FALSE;
   LastHDState.OnPart = LastHDState.Trigger = LastHDState.DoorOpen = FALSE;
   LastHDState.uls = TRUE;
   LastHDState.ECycleAbort = LastHDState.PwrOff = FALSE;
   LastHDState.Unused = 0;       /* Fill in all bits */
   
   /* Now try to take over the state machine.  Can only do this if the */
   /* system is ready.  Disable ints first in case system goes to "Not */
   /* Ready" just after we do the test. */
   SR sr = EnterCritical();
   if (GetReadyStatus()/*WeldState == READYSTATE*/&& !HornDownFlag && CurrentSetup.HandHeld == FALSE) {
      HornDownEventTimer[0].Count = 0; /* Make sure timers shut off */
      HornDownEventTimer[1].Count = 0;
      HornDownEventTimer[2].Count = 0;
      HornDownEventTimer[3].Count = 0;
      HDPosition = 0;                     /* Reasonable initial value */
      HDCollectVelData = FALSE;           /* Don't collect vel data yet */
      HDReadyState = TRUE;                /* Horn down starts checking pressure at ready */
      SystemPressureCheck = PRESSURE_CHECK_TIME1; /* setup .25 second timer */
      HornDownFlag = TRUE;                /* Shut down state machine */
      CurrentSequence = HORNDOWN;         /* Some code looks at this */
      UpdateKeyMask(HDMODEMASK);  /* Mask off keys we don't want to allow */
      ClearReady();

      /* Save trigger force even if AE, just won't mean anything */

      SaveTriggerForce = RunningPreset.TriggerForce;
      RunningPreset.TriggerForce = MinLimit.TriggerForce;
      VGAHornDown = TRUE;
      /* Clear Keypad buffer */
      ClearKeypadBuffer(FALSE);
   }
   ExitCritical(sr);
   /* Horn Down can be started */
   if (VGAHornDown) {
      /* Replaces MenuInfo Menu with VGA Menus */
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC)
    		  || (CurrentSetup.Actuator == MICRO))
         VGAHDMenu = HornDownStartAED;
      else                             /* Don't know what actuator this is */
         VGAHDMenu = HornDownStartAE;     /* default to simplest */
      VGAHDMenu.OpenMenu(&VGAHDMenu);
      VGAAction = NEXT_MSG;
   }
   else
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}    


void ProcessHDButtonPress1(void)            //For retract button
{
   VGAAction = NEXT_MENU;
   VGAMessageResults.NextMenu.CloseParam = 0;
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) ||
        (CurrentSetup.Actuator == MICRO))
   	VGAMessageResults.NextMenu.NextMenu  = (struct MenuInfo *) &HornDownStartAED;
   else
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
    VGAProcessHornDownMsg();
}

void ProcessHDButtonPress2(void)            //For toggle and choice press
{
   VGAAction = NEXT_MENU;
   VGAMessageResults.NextMenu.CloseParam = HD_RESTART;
   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) ||
      (CurrentSetup.Actuator == MICRO))
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *) &HornDownStartAED;
   else
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   VGAProcessHornDownMsg();   
}

void ProcessHDButtonPress3(void)            
{
   VGAAction = EXIT_HD;
   VGAHornVarEntry = TRUE;
   VGAProcessHornDownMsg();   
   VGAHornDown = TRUE;
}

void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage)
{
   UINT32  Message;
   UINT32  MsgUseId;

   Message = RvtsMessage & ~MESSAGE_NEW;
   /* If this message is one that should only appear in the buffer once, */
   /* clear flag now so it can be put in the buffer again. */

   MsgUseId = (Message & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   if (MsgUseId)
      MessageUseFlags[MsgUseId-1] = 0;  /* MsgUseId=0 when no flag needed */
   
   VGAAction =  VGAHDMenu.ProcessMessage( &VGAHDMenu, Message, &VGAMessageResults );
   VGAProcessHornDownMsg();
}

void RestartHornDown(void)
{
   UINT32 CloseParam = 0;
   VGAHDMenu.CloseMenu(CloseParam);
   Inp.Trigger = FALSE; /* Nobody else will do this, so do it here */
   VGAAction = NEXT_MSG;
   VGAEstopFlag = FALSE;
   VGAHDAlarm = FALSE;

   /* First, set up LastHDState structure the way we think the system */
   /* should be now.  Any change from this will cause a message to be */
   /* sent. */

   LastHDState.OnePB = LastHDState.BothPB = LastHDState.Estop = FALSE;
   LastHDState.OnPart = LastHDState.Trigger = LastHDState.DoorOpen = FALSE;
   LastHDState.uls = TRUE;
   LastHDState.ECycleAbort = LastHDState.PwrOff = FALSE;
   LastHDState.Unused = 0; /* Fill in all bits */

   HornDownEventTimer[0].Count = 0; /* Make sure timers shut off */
   HornDownEventTimer[1].Count = 0;
   HornDownEventTimer[2].Count = 0;
   HornDownEventTimer[3].Count = 0;
   HDPosition = 0; /* Reasonable initial value */
   HDCollectVelData = FALSE; /* Don't collect vel data yet */
   HDReadyState = TRUE; /* Horn down starts checking pressure at ready */
   SystemPressureCheck = PRESSURE_CHECK_TIME1; /* setup .25 second timer */
   HornDownFlag = TRUE; /* Shut down state machine */
   CurrentSequence = HORNDOWN; /* Some code looks at this */
   UpdateKeyMask(HDMODEMASK); /* Mask off keys we don't want to allow */
   ClearReady();

   VGAHornDown = TRUE;
   /* Replaces MenuInfo Menu with VGA Menus */
   if ((CurrentSetup.Actuator == AED)
         || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == MICRO))
      VGAHDMenu = HornDownStartAED;
   else 								/* Don't know what actuator this is */
      VGAHDMenu = HornDownStartAE;     /* default to simplest */

   VGAHDMenu.OpenMenu(&VGAHDMenu);
   VGAAction = NEXT_MSG;
}

void VGAProcessHornDownMsg (void)
/****************************************************************************/
/*Description:                                                              */
/* This function processes Horn down messages.                              */
/****************************************************************************/
{
   UINT32 CloseParam;

   switch (VGAAction)  
   {
      case NEXT_MENU:
        CloseParam = VGAMessageResults.NextMenu.CloseParam;
      VGAHDMenu.CloseMenu(CloseParam);
      VGAHDMenu = *VGAMessageResults.NextMenu.NextMenu;

      /*Refresh Menus ID */
      HDMenuID = VGAHDMenu.FullMenuID;

      VGAHDMenu.OpenMenu(&VGAHDMenu);
      VGAAction = NEXT_MSG;
      break;

   case EXIT_HD:
      CloseParam = 0;
      VGAHDMenu.CloseMenu(CloseParam);
      RunningPreset.TriggerForce = SaveTriggerForce; /* Restore to orig */
      CurrentSequence = WELD; /* Next call should do this anyway */
      SelectWeldSequence(); /* Restart state machine */
      WeldState = NOP; /* Restore this after tampering */
      //ResetStateMachine();
      StartStateMachine();
      SetReady();
      Inp.Trigger = FALSE; /* Nobody else will do this, so do it here */
      HornDownFlag = FALSE;
      VGAHornDown = FALSE;
      VGAAction = NEXT_MSG;
      break;
   case RESTART_HD:
      RestartHornDown();
      break;

   case NEXT_MSG:
   default:
      break;
   }
}

/*=========================================================================*/
/***********************************END*************************************/
/*=========================================================================*/
