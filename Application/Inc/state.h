/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/state.h_v   1.14   16 Apr 2015 07:35:04   rjamloki  $ */
#ifndef STATE_H
#define STATE_H
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
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/state.h_v  $
 * 
 *    Rev 1.14   16 Apr 2015 07:35:04   rjamloki
 * Removed redundant HIGH_PRESSURE define
 * 
 *    Rev 1.13   27 Mar 2015 11:14:56   amaurya
 * added CONFIRMREJECTSTATE in WELDSTATES enum.
 * 
 *    Rev 1.12   11 Mar 2015 09:24:12   amaurya
 * RejectAlarmConfirm changed to ConfirmReject
 * 
 *    Rev 1.11   11 Feb 2015 06:46:50   amaurya
 * changes for reject confirm input
 * 
 *    Rev 1.10   08 Jan 2015 03:09:58   AnPawar
 * Macro value changed for PRESSURE_TOLLERENCE_PB
 * 
 *    Rev 1.9   17 Nov 2014 10:10:30   RJamloki
 * Defined pressure tolerance for PB state
 * 
 *    Rev 1.8   07 Aug 2014 16:06:22   tayars
 * Added new state for downspeed tune
 * 
 *    Rev 1.7   09 Jul 2014 13:24:18   rjamloki
 * Added defines and flags to check PartPresent and PartClamp active
 * 
 *    Rev 1.6   20 Jun 2014 13:38:10   rjamloki
 * Added SetCalForceST and SetCalPressureST states for AES calibration
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
/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:                                                             */

/* Filename:      state.h                                                   */


/*---------------------------- REVISIONS -----------------------------------*/
/*                                                                          */
/*------------------------------ DESCRIPTION -------------------------------*/


 

/*----------------------------- INCLUDE FILES ------------------------------*/
#include "portable.h"

/*-------------------------------- DEFINES ---------------------------------*/


#define NMBR_OF_STATES    50
#define FAILED1           -1
#define FAILED2           -2


#define TRIGGER_TIMEOUT           10000   /* Max time between ULS & trigger */
#define TRIGGERLOSTTIME           150     /* Time (ms) before trigger is considered lost */
#define NEGTRIGGERLOSTDISTANCE    2000    /* .2" of upward travel after trigger */
#define TRIGGERLOSTDISTANCE       2500    /* 1/4" of travel after trigger with less than */
#define TRIGGERLOSTFORCE          350     /* 35 lbs of force                             */
#define UPPERLIMIT_TIMEOUT        4000    /* Max time between PB's & ULS    */
#define PALMBUTTON_STAGGER_TIME   200     /* Max time between the two PB's  */
#define PBEXITTIME                6000    /* Time before pb's must be rlsd  */
#define MAX_WELD_TIME             30000   /* Absolute max weld time         */
#define MAX_HOLD_TIME             30000   /* Absolute max hold time         */
#define MAX_ABDELAY_TIME          2000    /* Absolute max AB delay time     */
#define MAX_AB_TIME               2000    /* Absolute max AB time           */
#define PART_PRESENTCHECK_TIME    4000   /* for this time duration in pre ready if the part
										 present signal is active alarm needs to be raised*/
#define PART_CLAMPCHECK_TIME      4000   /* for this time duration in pre ready if the part
										 clamp signal is active alarm needs to be raised*/

#ifdef STATES                     /******************************************/
#define Statetype                 /* This cute little trick will allow all  */
#else                             /* uninitialized variables to be defined  */
#define Statetype  extern         /* in one file.  In Main.c GLOBAL should  */
#endif                            /* be defined.                            */
                                  /******************************************/
#define LOW_PRESSURE              200
#define PRESSURE_TOLLERANCE       30
#define PRESSURE_TOLLERANCE_SE277 30
#define PRESSURE_TOLLERENCE_PB	  20 //Pressure tolerance checked at PB state.

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  This first section of variables are those that must be updated from     */
/*  within the 1 ms interrupt handler.                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/

Statetype BOOLEAN CycleAbort, DistFlag;
extern    BOOLEAN ContinueFlag;

/*-------------  End of 1 ms interrupt variables  --------------------------*/


Statetype BOOLEAN  FailFlag, AbortFlag, SystemOK, TimerFlag;
Statetype BOOLEAN  StepTimeFlag, ABTimeFlag, ABTimeDelayFlag, SonicsAbort;
Statetype BOOLEAN  WTimeFlag, PTSTimerFlag, DUPSOkFlag, DepotLevel;
Statetype BOOLEAN  HTimeFlag, PDownDelay, TriggerDelayFlag;
Statetype BOOLEAN  StaggerFlag, AlarmsReset, TestTimerFlag;
Statetype BOOLEAN  StopFlag, ActClrFlag, StartTestFlag;
Statetype BOOLEAN  PBExitFlag, ULSExitFlag;
Statetype BOOLEAN  OKToAdvance, ExitClearMemFlag, EnergyBrakeFlag;
Statetype BOOLEAN  PartPresentExitFlag, PartClampExitFlag;
Statetype BOOLEAN  PartClampInpStatus, PartPresentInpStatus;
Statetype SINT16   InitTime, TimeOff;
Statetype SINT16   TrsEnd, TrsTime, UlsTime;
Statetype SINT16   MaxWTime, MaxHTime;
Statetype SINT16   MaxDTime, MaxABTime;
Statetype SINT16   Stagger;



enum WELDSTATES {                 /* Available weld states                 */
   NOP,                           /*                                       */
   POWERUPSEEKSTATE,              /* added for dups                        */
   PREREADYSTATE,                 /*                                       */
   READYSTATE,                    /*                                       */
   PBSTATE,                       /*                                       */
   DOWNSTROKESTATE,               /*                                       */
   WAITFORULSCLEARSTATE,          /*                                       */
   WAITFORPTSSTATE,               /* Pre-trigger state                     */
   WAITFORTRSSTATE1,              /*                                       */
   WAITFORTRSSTATE2,              /*                                       */
   WAITFORTRSSTATE3,              /* Horn down                             */
   TRIGGEREDSTATE,                /*                                       */
   TRIGGERDELAYSTATE,             /* A delay after trigger & before sonics */
   WELDTIMESTATE,                 /*                                       */
   WELDTIME2STATE,                /*                                       */
   ENDOFSONICS,                   /*                                       */
   HOLDTIMESTATE,                 /*                                       */
   PROCESSALARMSSTATE,            /* Check all process alarms              */
   AFTERBURSTDELAYSTATE,          /*                                       */
   AFTERBURSTTIMESTATE,           /*                                       */
   TESTMODESTATE,                 /*                                       */
   UPSTROKESTATE,                 /*                                       */
   WAITFORULSMADESTATE,           /*                                       */
   POWERDOWNSTATE,                /*                                       */
   DATAPACKETFULL,                /*                                       */
   NEWSTATE,                      /* A new state has been entered          */
   EMERGENCYSTOP,
   WAITFORCONTINUE,               /*                                       */
   CALTIMERSTATE1,                /*                                       */
   CALTIMERSTATE2,                /*                                       */
   MENUSYNCSTATE,
   READA2D1STATE,
   READA2D2STATE,
   READA2D3STATE,
   CALREADYSTATE,
   FINAL1MSSTATE,                 /* All final data will be sent here      */
   FINALDATASTATE,                /* All final data will be sent here      */
   UPDATEDATASTATE,               /* All updated data will be sent here    */
   SEEKSTATE,                     /*                                       */
   UPDATESTATE,                   /* Parameter update, new RunningPreset   */
   UPDATEALARMSTATE,
   RAMPSONICSSTATE,               /* State to ramp sonics up or down       */
   EMERGENCYSTOPRESET,            /* added 2/25/97                         */
   VERIFYDATASTATE,               /* Setup alarm data will be sent here    */
   CLEARMEMORYSTATE,              /* Clear P/S frequency memory            */
   WAITFORPARTCLAMPINPUTSTATE,     /* wait for PartClamp input upto 30sec.*/
   EXTTRIGDELAYSTATE,             /* Delay after the trigger state.        */
   SETCALPRESSURESTATEAES,
   SETCALFORCESTATEAES,
   CONFIRMREJECTSTATE,
   EXTEND_WELDSTATES = 65535u     /* Force values to be 16 bit             */
   };


enum ACTIONS  {
   NORM,                      /* Normal state, move on to next value        */
   FAIL,                      /* Set FailFlag for later checking            */
   ABORT,                     /* Set AbortFlag for later checking           */
   JUMP,                      /* This state is complete, go to next state   */
   ALJUMPNORM,                /* This state is complete, go to next state,with alarms  */
   POP,                       /* Return to PUSHed state previously saved    */
   PUSH,                      /* Save current state index for possible POP  */
   END,                       /* This is the end of the sub state list      */
   ALJUMP,                    /* Alarm condition, abort this sub state      */
   ALNORM  };                 /* Alarm condition, but continue sub state    */

typedef const struct substates {
   BOOLEAN *ValuePtr;         /* Pointer to value to be used for evaluation */
   enum    ACTIONS True;      /* What to do if value evaluates to TRUE      */
   enum    ACTIONS False;     /* What to do if value evaluates to FALSE     */
   UINT32  Alarm;             /* Alarm code if there was an alarm condition */
   SINT16  Trace;             /* Code for trace buffer                      */
   } SSTATES;

typedef const struct states {
   SSTATES *ptr;              /* Pointer to sub state structure             */
   SINT16  *STimer;           /* Pointer to timer value for this state      */
   void    (*PassPtr)(void) ; /* Pointer to function to call every pass     */
   void    (*EntryPtr)(void); /* Pointer to function to call on entry       */
   void    (*NextPtr)(void);  /* Pointer to function to call on normal exit */
   void    (*AlarmPtr)(void); /* Pointer to function to call on alarm exit  */
   enum WELDSTATES state;     /* State currently in                         */
   } STATE;



typedef struct portdata {
   BOOLEAN uls;             /* Upper limit switch                           */
   BOOLEAN trs;             /* Trigger switch if AE, Force trigger if EP    */
   BOOLEAN OnePB;           /* Either palm button, but not both             */
   BOOLEAN BothPB;          /* Both palm buttons                            */
   BOOLEAN SingleStart;     /* 1 PB, trigger switch or ext sig(8.1S = OnePB)*/
   BOOLEAN PwrOn;           /* The power is on and okay                     */
   BOOLEAN PwrOff;          /* A power off has been requested by the user   */
   BOOLEAN OL;              /* Power supply overload                        */
   BOOLEAN Estop;           /* Emergency stop                               */
   BOOLEAN lls;             /* Lower limit switch                           */
   BOOLEAN GndDet;          /* Ground detect                                */
   BOOLEAN ECycleAbort;     /* External cycle abort input                   */  
   BOOLEAN Trigger;         /* Logical trigger AE or EP                     */  
   BOOLEAN Reserved1;        /* Reserved1   									*/
   BOOLEAN ExternalReset;   /* External reset                               */
   BOOLEAN ExternalTrigger; /* External Force or amplitude step trigger     */
   BOOLEAN PSRun;           /* Power supply run signal                      */
   BOOLEAN PSSeek;          /* Power supply seek signal                     */
   BOOLEAN PSStore;         /* Power supply store signal                    */
   BOOLEAN PSClear;         /* Power supply clear signal                    */
   SINT32  PresetCode;      /* External Selection of Preset                 */
   BOOLEAN SonicDisable;    /* Sonics Disable signal                        */
   BOOLEAN MemReset;        /* Menmory Reset signal                         */
   BOOLEAN PartClamped;     /*   Part Clamped input signal                 */
   BOOLEAN ExtTrgDelay;     /* External trigger delay signal                */
   BOOLEAN DisplayLockFlag; /* Display Lock Signal                          */
   BOOLEAN Preset1;	     	 /* For J3-32's contribution to the preset code  */
   BOOLEAN Preset2;		    /* For J3-33's contribution to the preset code  */
   BOOLEAN Preset4;	       /* For J3-19's contribution to the preset code  */
   BOOLEAN Preset8;	       /* For J3-17's contribution to the preset code  */
   BOOLEAN Preset16;     	 /* For J3-31's contribution to the preset code  */
   BOOLEAN BitBucket;		 /* For when an input is disabled.               */
   BOOLEAN SyncIn;   		 /* Sync In input signal.                        */
   BOOLEAN PartPresent;     /* Part Present input signal.                   */
   BOOLEAN ConfirmReject; /* Reject Alarm Confirm input signal.       */
   }  INBITS;


   enum WELD_SEQUENCE_TYPE {
        NONEDEFINED,                 /* Default when nothing defined yet       */
        WELD,                        /* Any weld sequence                      */
        CALIBRATION,                 /* Force or distance calibration          */
        SC,                          /* added actuator system calibration      */
        POWERCAL,                    /* added power calibration                */
        DEBUG,                       /* Debug sequence                         */
        HORNDOWN,                    /* Horn down sequence                     */
        TESTMODE,                    /* Test Mode sequence                     */
        POWERDOWN,                   /* Power down sequence                    */
        POWERUP  };                  /* Power up sequence                      */



//#ifndef STATES

extern  SSTATES Initial[];
extern  SSTATES Ready[];
extern  SSTATES ReadyTest[];
extern  SSTATES CheckReady[];
extern  SSTATES PalmButtons[];
extern  SSTATES PalmButton[];
extern  SSTATES CalbPBs[];
extern  SSTATES WaitUls1[];
extern  SSTATES WaitUls2[];
extern  SSTATES WaitPartClampInput[];
extern  SSTATES ExtTrigDelay[];
extern  SSTATES PreTrigger[];
extern  SSTATES WaitTrs1[];
extern  SSTATES WaitTrs2[];
extern  SSTATES WaitTrs1PT[];
extern  SSTATES WaitTrs2PT[];
extern  SSTATES TrigDelay[];
extern  SSTATES Weld1[];
extern  SSTATES Weld1A[];
extern  SSTATES Weld2[];
extern  SSTATES EnerBrake[];
extern  SSTATES SonicsOff[];
extern  SSTATES Hold[];
extern  SSTATES AlterHold[];
extern  SSTATES Limits[];
extern  SSTATES Nop[];
extern  SSTATES PowerDown[];
extern  SSTATES PowerDown1[];
extern  SSTATES WaitTime[];
extern  SSTATES AdjustDone[];
extern  SSTATES MenuSync[];
extern  SSTATES FinalData[];
extern  SSTATES ConfirmRejectSST[];
extern  SSTATES DebugState[];
extern  SSTATES Power1[];
extern  SSTATES Power2[];
extern  SSTATES Power3[];
extern  SSTATES PwrPage1[];
extern  SSTATES PwrPage2[];
extern  SSTATES Trigger[];
extern  SSTATES PwrTrigger[];
extern  SSTATES SeekWait[];
extern  SSTATES ParamUpdate[];
extern  SSTATES Initial[];
extern  SSTATES PChkAct[];
extern  SSTATES PChkPwrSup[];
extern  SSTATES PChkCntrls[];
extern  SSTATES PChkStack[];
extern  SSTATES ClearMem[];

/* SSTATES added for 1 cycle start */

extern  SSTATES ReadyHH[];
extern  SSTATES CheckReadyHH[];
extern  SSTATES PalmButtonsHH[];
extern  SSTATES WeldHH;
extern  SSTATES SonicsOffHH;
extern  SSTATES TriggerHH[];
extern  SSTATES ABDelayHH[];
extern  SSTATES ABTimeHH[];
extern  SSTATES SeekHH;
extern  SSTATES SeekWaitHH[];
extern  SSTATES CalWaitUls1[];
extern  SSTATES CalTrigger[];

extern  STATE   TopOfList; 
extern  STATE   ReadySt;   
extern  STATE   PreReadyTestSt;   
extern  STATE   ReadyTestSt;   
extern  STATE   PBState;   
extern  STATE   OnePBState;   
extern  STATE   WaitUls;
extern  STATE   WaitUlsUp;
extern  STATE   WaitPartClampST;
extern  STATE   WaitTrs1DST;
extern  STATE   WaitTrs2DST;
extern  STATE   WaitTrs1ST;
extern  STATE   WaitTrs2ST;
extern  STATE   WaitTrs1DSTPT;
extern  STATE   WaitTrs2DSTPT;
extern  STATE   WaitTrs1STPT;
extern  STATE   WaitTrs2STPT;
extern  STATE   WaitTrsST3;
extern  STATE   UpdateState;
extern  STATE   PreTrsDST;
extern  STATE   PreTrsST;
extern  STATE   TriggerST; 
extern  STATE   CalTriggerST; 
extern  STATE   ExtTrigDelayST;
extern  STATE   ExtTrigDelaySTDist;
extern  STATE   TrigDelayST; 
extern  STATE   TrigDelaySTDist;
extern  STATE   SonicsOn1ST; 
extern  STATE   SonicsOn1STDist;
extern  STATE   SonicsOn1DST; 
extern  STATE   SonicsOn1DSTDist;
extern  STATE   SonicsOn1A; 
extern  STATE   SonicsOn2ST; 
extern  STATE   SonicsOn2STDist;
extern  STATE   SonicsOn2DST; 
extern  STATE   SonicsOn2DSTDist;
extern  STATE   SonicsOn3DST; 
extern  STATE   SonicsOn3DSTDist;
extern  STATE   SonicsOn3ST; 
extern  STATE   SonicsOn3STDist;
extern  STATE   SonicsOn3A;
extern  STATE   SonicsOn3ADist;
extern  STATE   SonicsOn3B;
extern  STATE   SonicsOn3BDist;
extern  STATE   SonicsOn3CST;
extern  STATE   SonicsOn3CSTDist;
extern  STATE   SonicsOn3CDST;
extern  STATE   SonicsOn3CDSTDist;
extern  STATE   SonicsOn4ST; 
extern  STATE   SonicsOn4STDist;
extern  STATE   SonicsOn4DST; 
extern  STATE   SonicsOn4DSTDist;
extern  STATE   SonicsOn5;
extern  STATE   SonicsOn5Dist;
extern  STATE   SonicsOn6; 
extern  STATE   SonicsOn6Dist;
extern  STATE   SonicsOn7ST; 
extern  STATE   SonicsOn7STDist;
extern  STATE   SonicsOn7DST; 
extern  STATE   SonicsOn7DSTDist;
extern  STATE   SonicsOn8ST;
extern  STATE   SonicsOn8STDist;
extern  STATE   SonicsOn8DST;
extern  STATE   SonicsOn8DSTDist;
extern  STATE   SonicsOn9ST; 
extern  STATE   SonicsOn9STDist;
extern  STATE   SonicsOn9DST; 
extern  STATE   SonicsOn9DSTDist;
extern  STATE   WeldOffST;  
extern  STATE   EnerBrakeST;  
extern  STATE   EnerBrakeSTDist;
extern  STATE   EnerBrakeHHST;  
extern  STATE   PLCBrakeHHST;  
extern  STATE   HoldTimeST;  
extern  STATE   HoldTimeSTDist;
extern  STATE   HoldTimeDST;  
extern  STATE   HoldTimeDSTDist;
extern  STATE   FakeHold;
extern  STATE   FakeHoldDist;
extern  STATE   CheckLimitsST;  
extern  STATE   ABDelayST;
extern  STATE   ABTimeST;
extern  STATE   RampSonicsST;
extern  STATE   SeekState;  
extern  STATE   PreReady;  
extern  STATE   EndOfList; 
extern  STATE   NopList;   
extern  STATE   TestST;   
extern  STATE   StartData;   
extern  STATE   StopData;
extern  STATE   StopDataTune;
extern 	STATE   StopDataTuneHD;
extern  STATE   PowerOn1;   
extern  STATE   PowerOn2;   
extern  STATE   PowerOn3;   
extern  STATE   PowerOn4;   
extern  STATE   PowerOn5;   
extern  STATE   PowerOn6;   
extern  STATE   PwrDown;   
extern  STATE   MenuSyncST;
extern  STATE 	SetCalPressureST;
extern  STATE   CalTopOfList;
extern  STATE   PwrPage1Wait; 
extern  STATE   PwrPage2Wait; 
extern  STATE   PwrPage3Wait; 
extern  STATE   CollectPwr1;  
extern  STATE   CollectPwr2;  
extern  STATE   CollectPwr3;  
extern  STATE   VerifyPwr;  
extern  STATE   VerifyPower;  
extern  STATE   PwrTriggerST;
extern  STATE   CalReadySt;  
extern  STATE   CalPBState2;
extern  STATE   CalWaitUls;  
extern  STATE   CalWaitTrsST;
extern  STATE   CalWaitTime1;  
extern  STATE   CalWaitTime2;  
extern  STATE   CalEndOfList;
extern  STATE   DistanceST1;
extern  STATE   DistanceST2;
extern  STATE   ClearMemST;
extern  STATE   DebugDelayST;
extern  STATE   DebugTrigST;
extern  STATE   FinalDataST;
extern  STATE   ConfirmRejectST;
extern  STATE   SCWaitUls;  
extern  STATE   SCDone;
extern  STATE   SCDeflection;
extern  STATE   SCWaitTrsST;
extern  STATE   SCEndOfList;

extern  STATE	SetCalForceST;
/* States added for 1 cycle start condition */

extern STATE    PreReadyHHST;
extern STATE    ReadyHHST;
extern STATE    PBStateHHST;
extern STATE    SonicsOnHHST;
extern STATE    PLCOnHHST;
extern STATE    SonicsOn2HHST;
extern STATE    PLCOn2HHST;
extern STATE    SonicsOn3HHST;
extern STATE    SonicsOn4HHST;
extern STATE    SonicsOnGD1ST;
extern STATE    SonicsOnGD2ST;
extern STATE    SonicsOnPP1ST;
extern STATE    SonicsOnPP2ST;
extern STATE    HoldTimeHHST;
extern STATE    PLCTimeHHST;
extern STATE    FakeHoldHHST;
extern STATE    WeldOffHHST;
extern STATE    ABDelayHHST;
extern STATE    ABTimeHHST;
extern STATE    SeekStateHH;  
extern STATE    TriggerHHST; 

//#endif
#endif
