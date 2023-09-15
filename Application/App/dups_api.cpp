/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_api.cpp_v   1.17   08 Jan 2015 03:18:20   AnPawar  $ */
/****************************************************************************/

/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_api.cpp_v  $
 * 
 *    Rev 1.17   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.16   28 Nov 2014 07:34:14   rjamloki
 * Initialized all the members of the structure HS_MaxScanInfo and HS_MinScanInfo.
 * 
 *    Rev 1.15   20 Oct 2014 06:18:52   AnPawar
 * RecordEvents() removed from DUPS_StartHS() and DUPS_HornScanAbort() function.
 * 
 *    Rev 1.14   06 Oct 2014 06:29:42   AnPawar
 * removed DUPS_ManagerTask.h file inclusion.Function DUPS_DownloadCurrPS(),DUPS_DownloadParamSet() function changed.Using cygos function for queue read write.
 * 
 *    Rev 1.13   03 Oct 2014 05:53:38   rjamloki
 *  function renamed q_send() to SendMessage() and using RTOS::DelayMs() in place of tm_wkafter()
 * 
 *    Rev 1.12   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.11   11 Sep 2014 10:50:04   rjamloki
 * RecordEvent arguments changed in Horn scan start event.
 * 
 *    Rev 1.10   28 Jul 2014 12:43:42   rjamloki
 * added support for horn scan amplitude and current graph
 * 
 *    Rev 1.9   11 Jun 2014 11:28:54   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:47:54   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 02:58:56   rjamloki
 * fixed Data1 and Data2 for scan events
 * 
 *    Rev 1.6   07 May 2014 10:19:10   rjamloki
 * Record event on horn scan and horn scan abort.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:46   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:20   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:32   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:22   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Module name:   DUPS API

 Filename:      dups_api.c

 Function name:

 Written by: Sunil Patil
 Date: 6/13/00
 Language:  "C"

 ------------------------------ DESCRIPTION -------------------------------


 This file has the DUPS API functions. Any data exchange with the DUPS is
 handled by one of these functions.

 ----------------------------- INCLUDE FILES ------------------------------*/

#include "dups_api.h"
#include "qdef.h"
#include "dups.h"
#include "param.h"
#include "battram.h"
#include "preset.h"
#include "string.h"
#include "FrontPanelKeypadTask.h"
#include "state.h"
#include "statedrv.h"
#include "menu7a.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "ALARMS.H"
#include "Events.h"
#include "ticks.h"
#include "DUPS_ManagerTask.h"


/*---------------------------- EXTERNAL DATA -------------------------------*/

extern BOOLEAN HornScanOL;
extern enum WELDSTATES WeldState;
extern BOOLEAN HSNotStarted;
extern BOOLEAN VGAHornScanOLD;
/*----------------------------- LOCAL DEFINES ------------------------------*/

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

void ChangeDUPSSubParamList(void);
void RefreshDUPSParam ();
/*----------------------------- GLOBAL DATA --------------------------------*/
DUPS_WELDSTATUS DUPS_WeldStatus; /* Declare the DUPS Weld parameter struct */
DUPS_CURRENTPARAMSET DUPS_CurrentParamSet; /* Declare the DUPS Current parameter struct */
SINT16 DUPS_CurrPSStatus; /* Set to Pending for upload, DUPS_SUCCESS when complete*/

DUPS_MSGBUF DUPS_MsgBuf; /* Delcare the DUPS message buffer struct */
HS_LIMITS HS_Limits; /* Delcare the hornscan parameters limits struct */

DUPS_STARTSCANCMD DUPS_StartScanCmd; /* Declare the DUPS horn scan command struct */

DUPS_INFO DUPS_Info; /* Declare the DUPS information struct*/
HORNSCANINFO HornScanInfo; /* Declare the Hornscan Info struct */

/* These are the maximum value limits for the DUPS Parameters*/
DUPS_CURRENTPARAMSET DUPS_MaxParamSet = { 0, /* Freq */
0, /* power*/
0, /* Varient */
1, /* DUPS_DIPFLAG */
0xFC, /* DUPS_SWDIPSETTING  */
100, /* DUPS_SEEKAMPLITUDE*/
1000, /* DUPS_SEEKRAMPTIME milliseconds*/
1000, /* DUPS_SEEKTIME  milliseconds*/
1000, /* DUPS_SEEKFLIMH  hertz  */
1000, /* DUPS_SEEKFLIML hertz */
500, /* DUPS_SEEKPHLOOPI */
500, /* DUPS_SEEKPHLOOPCF */
500, /* DUPS_SEEKAMPLOOPC1 */
500, /* DUPS_SEEKAMPLOOPC2 */
100, /* DUPS_WELDAMPLITUDE*/
1000, /* DUPS_WELDRAMPTIME */
500, /* DUPS_WELDPHLOOPI */
500, /* DUPS_WELDPHLOOPCF  */
500, /* DUPS_WELDAMPLOOPC1 */
500, /* DUPS_WELDAMPLOOPC2 */
1000, /* DUPS_WELDFLIMH  hertz   */
1000, /* DUPS_WELDFLIML  hertz   */
2000, /* DUPS_WELDPHLIM*/
2000 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_MaxParamSet struct */

/* These are the minimum value limits for the DUPS Parameters*/
DUPS_CURRENTPARAMSET DUPS_MinParamSet = { 0, /* Freq */
0, /* power*/
0, /* Varient */
0, /* DUPS_DIPFLAG */
0, /* DUPS_SWDIPSETTING  */
1, /* DUPS_SEEKAMPLITUDE*/
1, /* DUPS_SEEKRAMPTIME milliseconds*/
100, /* DUPS_SEEKTIME  milliseconds*/
1, /* DUPS_SEEKFLIMH  hertz  */
1, /* DUPS_SEEKFLIML hertz */
50, /* DUPS_SEEKPHLOOPI */
50, /* DUPS_SEEKPHLOOPCF */
100, /* DUPS_SEEKAMPLOOPC1 */
100, /* DUPS_SEEKAMPLOOPC2 */
1, /* DUPS_WELDAMPLITUDE*/
10, /* DUPS_WELDRAMPTIME */
50, /* DUPS_WELDPHLOOPI */
50, /* DUPS_WELDPHLOOPCF  */
100, /* DUPS_WELDAMPLOOPC1 */
100, /* DUPS_WELDAMPLOOPC2 */
1, /* DUPS_WELDFLIMH  hertz   */
1, /* DUPS_WELDFLIML  hertz   */
1, /* DUPS_WELDPHLIM*/
1 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_MinParamSet struct */
/* These are the maximum value limits for the DUPS Parameters*/

DUPS_CURRENTPARAMSET DUPS_Default15KParamSet = { 15, /* Freq */
0, /* power*/
0, /* Varient */
1, /* DUPS_DIPFLAG */
0, /* DUPS_SWDIPSETTING  */
10, /* DUPS_SEEKAMPLITUDE*/
80, /* DUPS_SEEKRAMPTIME milliseconds*/
500, /* DUPS_SEEKTIME  milliseconds*/
500, /* DUPS_SEEKFLIMH  hertz  */
500, /* DUPS_SEEKFLIML hertz */
140, /* DUPS_SEEKPHLOOPI */
200, /* DUPS_SEEKPHLOOPCF */
205, /* DUPS_SEEKAMPLOOPC1 */
370, /* DUPS_SEEKAMPLOOPC2 */
100, /* DUPS_WELDAMPLITUDE*/
80, /* DUPS_WELDRAMPTIME */
450, /* DUPS_WELDPHLOOPI */
450, /* DUPS_WELDPHLOOPCF  */
100, /* DUPS_WELDAMPLOOPC1 */
300, /* DUPS_WELDAMPLOOPC2 */
500, /* DUPS_WELDFLIMH  hertz   */
500, /* DUPS_WELDFLIML  hertz   */
1000, /* DUPS_WELDPHLIM*/
500 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_Default15KParamSet struct */

DUPS_CURRENTPARAMSET DUPS_Default20KParamSet = { 20, /* Freq */
0, /* power*/
0, /* Varient */
1, /* DUPS_DIPFLAG */
0, /* DUPS_SWDIPSETTING  */
10, /* DUPS_SEEKAMPLITUDE*/
80, /* DUPS_SEEKRAMPTIME milliseconds*/
500, /* DUPS_SEEKTIME  milliseconds*/
500, /* DUPS_SEEKFLIMH  hertz  */
500, /* DUPS_SEEKFLIML hertz */
140, /* DUPS_SEEKPHLOOPI */
200, /* DUPS_SEEKPHLOOPCF */
205, /* DUPS_SEEKAMPLOOPC1 */
370, /* DUPS_SEEKAMPLOOPC2 */
100, /* DUPS_WELDAMPLITUDE*/
80, /* DUPS_WELDRAMPTIME */
450, /* DUPS_WELDPHLOOPI */
450, /* DUPS_WELDPHLOOPCF  */
100, /* DUPS_WELDAMPLOOPC1 */
300, /* DUPS_WELDAMPLOOPC2 */
500, /* DUPS_WELDFLIMH  hertz   */
500, /* DUPS_WELDFLIML  hertz   */
1000, /* DUPS_WELDPHLIM*/
500 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_Default20KParamSet struct */

DUPS_CURRENTPARAMSET DUPS_Default30KParamSet = { 30, /* Freq */
0, /* power*/
0, /* Varient */
1, /* DUPS_DIPFLAG */
0, /* DUPS_SWDIPSETTING  */
10, /* DUPS_SEEKAMPLITUDE*/
80, /* DUPS_SEEKRAMPTIME milliseconds*/
500, /* DUPS_SEEKTIME  milliseconds*/
500, /* DUPS_SEEKFLIMH  hertz  */
500, /* DUPS_SEEKFLIML hertz */
100, /* DUPS_SEEKPHLOOPI */
200, /* DUPS_SEEKPHLOOPCF */
205, /* DUPS_SEEKAMPLOOPC1 */
370, /* DUPS_SEEKAMPLOOPC2 */
100, /* DUPS_WELDAMPLITUDE*/
80, /* DUPS_WELDRAMPTIME */
100, /* DUPS_WELDPHLOOPI */
200, /* DUPS_WELDPHLOOPCF  */
205, /* DUPS_WELDAMPLOOPC1 */
370, /* DUPS_WELDAMPLOOPC2 */
500, /* DUPS_WELDFLIMH  hertz   */
500, /* DUPS_WELDFLIML  hertz   */
1000, /* DUPS_WELDPHLIM*/
500 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_Default30KParamSet struct */

DUPS_CURRENTPARAMSET DUPS_Default40KParamSet = { 40, /* Freq */
0, /* power*/
0, /* Varient */
1, /* DUPS_DIPFLAG */
0, /* DUPS_SWDIPSETTING  */
10, /* DUPS_SEEKAMPLITUDE*/
80, /* DUPS_SEEKRAMPTIME milliseconds*/
500, /* DUPS_SEEKTIME  milliseconds*/
500, /* DUPS_SEEKFLIMH  hertz  */
500, /* DUPS_SEEKFLIML hertz */
60, /* DUPS_SEEKPHLOOPI */
200, /* DUPS_SEEKPHLOOPCF */
205, /* DUPS_SEEKAMPLOOPC1 */
370, /* DUPS_SEEKAMPLOOPC2 */
100, /* DUPS_WELDAMPLITUDE*/
80, /* DUPS_WELDRAMPTIME */
60, /* DUPS_WELDPHLOOPI */
200, /* DUPS_WELDPHLOOPCF  */
205, /* DUPS_WELDAMPLOOPC1 */
370, /* DUPS_WELDAMPLOOPC2 */
500, /* DUPS_WELDFLIMH  hertz   */
500, /* DUPS_WELDFLIML  hertz   */
1000, /* DUPS_WELDPHLIM*/
500 /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_Default40KParamSet struct */

/* This struct defines horn scan parameters maximum values */
HORNSCANINFO HS_MaxScanInfo = { 204500, /* StartFreq */
		204500, /* StopFreq */
		50, /* FreqStep*/
		100, /* TimeDelay */
		50, /* MaximumAmplitude*/
		50,/* MaximumCurrent*/
		0, 0,
		{0,0,0,0,0,0},
		{FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE},
		0, 0, 0, 0, 0};

/* This struct defines horn scan parameters minimum values */
HORNSCANINFO HS_MinScanInfo = { 194500, /* StartFreq */
194500, /* StopFreq */
1, /* FreqStep */
      10, /* TimeDelay */
      10, /* MaximumAmplitude*/
      10,  /* MaximumCurrent*/
	  0, 0,
	  {0, 0, 0, 0, 0, 0},
	  {FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE, FREQ_NONE},
	  0, 0, 0, 0, 0};

/* These arrays will be used to find DUPS Paramset and COPs Preset assigned, Locked and saved*/
//UINT8 DUPS2COP[DUPS_NUMPARAMSET]; /* DUPS_NUMPARAMSET */
//UINT8 COP2DUPS[MAX_PRESETS + 1]; /*MAX_PRESETS*/
//UINT16 DUPS_Lock[DUPS_NUMPARAMSET]; /*Avail,Locked,Saved*/

/* Location in FRAM to store Hornscan Current and phase points uploaded from DUPS, Filterd 
 and decimated - used for printing graph*/
SINT16 *HornScanCurrent = (SINT16 *) FRAM1200_HORNGRAPH_START + (2
      * DUPS_HORNSCANPOINTS); /*DUPS_HORNSCANPOINTS*/
SINT16 *HornScanAmp = (SINT16 *) FRAM1200_HORNGRAPH_START + (4
      * DUPS_HORNSCANPOINTS); /*DUPS_HORNSCANPOINTS*/
SINT16 *HornScanPhase = (SINT16 *) FRAM1200_HORNGRAPH_START;

BOOLEAN DUPSChangePending = FALSE;
enum DUPS_CHANGE DUPSChange;
UINT16 DUPSUploadPSPending;
UINT16 ResonanceFreqEnable[DUPS_NUMRESONANCES];
BOOLEAN HSStartFlag = FALSE;
/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/

/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/

/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/

/*------------------------------ CODE --------------------------------------*/

void DUPS_SelectParamSetNum(SINT32 PSNum)
/*********************************************************************************/
/* This function sends the selected parameter set number message to DUPS manager */
/*********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   DUPS_CurrPSStatus = DUPS_PENDING;

   OutMsg.mt = DUPS_MSGSELECTPARAMSETNUM;
   OutMsg.data1 = (UINT16) PSNum;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
}

void DUPS_DownloadCurrPS(void)
/*********************************************************************************/
/* This function is called from various menus to download the current parameter  */
/* set to the DUPS module.                                                       */
/*********************************************************************************/
{
   DUPS_CurrPSStatus = DUPS_PENDING; /* DUPS Manager is Busy */
   DUPS_DownloadParamSet(DUPS_CURRPARAMSET);
   DUPS_Wait4CurrPS();

}

void DUPS_QueuedDownloadPS(void)
/*********************************************************************************/
/*   This function will only call DUPS_DownloadCurrPS if the welder is in        */
/*   the preready state.  If it is in the ready state the ReadyOK flag will be   */
/*   cleared to FALSE to pull the welder out of ready and the communication      */
/*   will be queued.  If welder is any other state the communication will be     */
/*   queued  and the global flag DUPSChangePending will be set so that a         */
/*   call to verify preset or entry into the preready state will cause the call  */
/*   to DUPS_DownloadCurrPS.                                                     */
/*********************************************************************************/
{
   switch (WeldState)
   {
   case PREREADYSTATE:
      DUPS_DownloadCurrPS();
      DUPSChangePending = FALSE;
      break;
   case READYSTATE:
   default:
      if (DUPSChangePending == FALSE) /* only if we don't have upload pending */
      {
         DUPSChange = DOWNLOAD_PENDING;
         DUPSChangePending = TRUE;
      }
      break;
   }
}

void DUPS_Wait4CurrPS(void)
/*********************************************************************************/
/* This function waits for the DUPS Manager to complete an download or upload    */
/* set to the DUPS module.                                                       */
/* divide limit by 10 and wait 10 times so the waiting could be over faster      */
/*********************************************************************************/
{
   UINT16 Time = 0;

   while ((Time < DUPS_TIMELIMIT) && (DUPS_CurrPSStatus != DUPS_SUCCESS))
   {
      RTOS::DelayMs((DUPS_TIMELIMIT / 10) * MILLS_PER_TICK);
      Time += (DUPS_TIMELIMIT / 10);
   }
}

void DUPS_DownloadParamSet(UINT16 PSnum)
/***********************************************************************************/
/* This function tells the DUPS manager to download the DUPS parameter set if all  */
/* the values are within limits.                                                   */
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   // No need to DownLoad preset to DUPS if DUPS already have the same values.
   if (memcmp(&DUPS_CurrentParamSet, &CurrentPreset.DUPS_HostParamSet,
         sizeof(DUPS_CURRENTPARAMSET)) == 0)
   {
	  DUPS_CurrPSStatus = DUPS_SUCCESS;
      return;
   }
   else
   {
      // copy the DUPS parameters from current preset to DUPS_CurrentParamSet.
      DUPS_CurrentParamSet = CurrentPreset.DUPS_HostParamSet;
      RefreshDUPSParam();//Update for menu display
   }

   enum DUPS_RESULTS Status = DUPS_ChkParamLimit(); /* Check all parameters are within limit*/

   if (Status == DUPS_SUCCESS)
   {
      OutMsg.mt = DUPS_MSGDOWNLOADPARAMSET;
      OutMsg.data1 = PSnum;
      DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
   }
}

void DUPS_UploadParamSet(UINT16 PSnum)
/***********************************************************************************/
/* This function sends an Upload parameter set message to the DUPS manager.        */
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   DUPS_CurrPSStatus = DUPS_PENDING;

   OutMsg.mt = DUPS_MSGUPLOADPARAMSET;
   OutMsg.data1 = PSnum;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
}

void DUPS_HornScanAbort(void)
/***********************************************************************************/
/* This function sends an HornScan abort message to the DUPS manager.              */
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   OutMsg.data1 = HORNSCANABORTED;
   OutMsg.mt = DUPS_MSGHORNSCANSTEP;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
}

void DUPS_ModifySWDipSetting(void)
/***********************************************************************************/
/* Modify Software Dip Setting. Menu manager calls this function when software dip */
/* settings in the DUPS parameter set are modified in the Weld Setup menu          */
/***********************************************************************************/
{
   if (DUPS_Info.DUPSMemFlag)
      //      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPSTOREMEMATWLDEND;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting |= DUPS_SWDIPSTOREMEMATWLDEND;
   else
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPSTOREMEMATWLDEND;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting
            &= ~DUPS_SWDIPSTOREMEMATWLDEND;

   if (DUPS_Info.DUPSSeekFlag)
      //      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAUTOSEEK;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting |= DUPS_SWDIPAUTOSEEK;
   else
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;

   if (DUPS_Info.DUPSMemRstFlag)
      //      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPCLEARMEMATRST;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting |= DUPS_SWDIPCLEARMEMATRST;
   else
      //      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;
      CurrentPreset.DUPS_HostParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;

   ChangeDUPSSubParamList();
}

void DUPS_StartHS(void)
/**************************************************************************************/
/* Menu manager calls this function to start a horn scan. The function itself sends a */
/* start scan message                                                                 */
/**************************************************************************************/
{
   enum DUPS_RESULTS Status = DUPS_SUCCESS;
   DUPS_MSGBUF OutMsg;
   UINT16 K;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   HSStartFlag = TRUE;
   /***************************************/
   StopStateMachine();
   DUPSOkFlag = FALSE;
   HSNotStarted = FALSE;
   VGAHornScanOLD = FALSE;
   /***************************************/
   for (K = 0; K < DUPS_NUMRESONANCES; K++)
   {
      HornScanInfo.ResonanceFreqs[K] = 0;
      HornScanInfo.ResonanceFreqType[K] = FREQ_NONE;
      ResonanceFreqEnable[K] = 0; /* Don't display Resonance frequency if 0.*/
   }
   /* check the limits */
   if (HornScanInfo.StartFreq >= HornScanInfo.StopFreq)
      Status = DUPS_OTHER;
   if (Status == DUPS_SUCCESS)
   { /* frequency step calculate. Atleast should be 1*/
      while (HornScanInfo.FreqStep * DUPS_HORNSCANMAXPOINTS
            < (HornScanInfo.StopFreq - HornScanInfo.StartFreq + 1)){
         HornScanInfo.FreqStep++;
      }
      OutMsg.mt = DUPS_MSGDOWNLOADSTARTSCAN;
      UpdateKeyMask(HSMASK);
      HornScanOL = FALSE;
      DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
      HornScanInfo.ScanStatus = DUPS_SCANINPROG;
   }
}


void DUPS_GetLastWeldStatus(DUPS_WELDSTATUS *Buf)
/****************************************************************************************/
/* This function sends a message to manager to retrieve the weld status report for      */
/* the last weld.                                                                       */
/****************************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   Buf->OpStatus = DUPS_PENDING;
   Buf->DataStatus = DUPS_PENDING;

   OutMsg.mt = DUPS_MSGUPLOADLASTWELDSTATUS;
   OutMsg.data2 = (UINT32) Buf;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
}

#define IN_RANGE(value)   ((Current->value >= Low->value) && (Current->value <= High->value))

enum DUPS_RESULTS DUPS_ChkParamLimit(void)
/****************************************************************************************/
/* This function checks the maximum and minimum limits of the current parameter set     */
/* values.                                                                              */
/****************************************************************************************/
{
   enum DUPS_RESULTS Status;

   DUPS_CURRENTPARAMSET * Current = &DUPS_CurrentParamSet;
   DUPS_CURRENTPARAMSET * High = &DUPS_MaxParamSet;
   DUPS_CURRENTPARAMSET * Low = &DUPS_MinParamSet;

   if (IN_RANGE(SeekAmplitude) && IN_RANGE(SeekRampTime) && IN_RANGE(SeekTime)
         && IN_RANGE(SeekFreqLimitHigh) && IN_RANGE(SeekFreqLimitLow)
         && IN_RANGE(SeekPhaseLoop) && IN_RANGE(SeekPhaseLoopCF)
         && IN_RANGE(SeekAmplitudeLoopC1) && IN_RANGE(SeekAmplitudeLoopC2)
         && IN_RANGE(WeldAmplitude) && IN_RANGE(WeldRampTime)
         && IN_RANGE(WeldPhaseLoop) && IN_RANGE(WeldPhaseLoopCF)
         && IN_RANGE(WeldAmplitudeLoopC1) && IN_RANGE(WeldAmplitudeLoopC2)
         && IN_RANGE(WeldFreqLimitHigh) && IN_RANGE(WeldFreqLimitLow)
         && IN_RANGE(WeldPhaseLimit) && IN_RANGE(WeldPhaseLimitTime))

      Status = DUPS_SUCCESS;
   else
      Status = DUPS_OTHER;
   return Status;
}

void DUPS_FRAM2RAM(void)
/****************************************************************************************/
/*  Function initializes all the data pointers to transfer data from FRAM to RAM       */
/****************************************************************************************/
{
   UINT8 *HORN_Infoptr = (UINT8 *) FRAM1200_HORNSCAN_START;
   memcpy(&HornScanInfo, HORN_Infoptr, sizeof(HORNSCANINFO)); /* copy HORNscanInfo from FRAM */
}

void DUPS_RAM2FRAM(void)
/****************************************************************************************/
/* This function is used to store the data in FRAM                                     */
/****************************************************************************************/
{
   UINT8 *HORN_Infoptr = (UINT8 *) FRAM1200_HORNSCAN_START;
   memcpy(HORN_Infoptr, &HornScanInfo, sizeof(HORNSCANINFO)); /* copy HORNscanInfo to FRAM */
}
