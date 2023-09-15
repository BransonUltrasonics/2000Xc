/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/DUPS_ManagerTask.cpp_v   1.21   30 Jan 2015 08:09:38   amaurya  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/DUPS_ManagerTask.cpp_v  $
 * 
 *    Rev 1.21   30 Jan 2015 08:09:38   amaurya
 * DUPS_MsgHornScanStep() changed.
 * 
 *    Rev 1.20   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.19   02 Jan 2015 04:00:20   rjamloki
 * removed continue from DUPS_ManagerTask::Run() 
 * 
 *    Rev 1.18   11 Dec 2014 08:34:52   AnPawar
 * event on horn scan complete.
 * 
 *    Rev 1.17   28 Nov 2014 07:35:28   rjamloki
 * memset the structure DUPS_MSGBUF to zero.
 * 
 *    Rev 1.16   10 Nov 2014 04:48:04   AnPawar
 * DUPS_ManagerTask::Run() function modified to check dups diagnostic message.
 * 
 *    Rev 1.15   06 Oct 2014 06:30:56   AnPawar
 *  Using cygos function for queue read write.
 * 
 *    Rev 1.14   03 Oct 2014 05:57:56   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.13   11 Sep 2014 10:51:06   rjamloki
 * passed argument 0 in UpdateCurrentPresetAndSetup function to avoid false parameter change event.
 * 
 *    Rev 1.12   05 Sep 2014 04:41:30   rjamloki
 * Ignoring dups commands after power up dups communication failure
 * 
 *    Rev 1.11   28 Jul 2014 12:43:42   rjamloki
 * added support for horn scan amplitude and current graph
 * 
 *    Rev 1.10   09 Jul 2014 10:47:28   rjamloki
 * Merged code from dups_manager.cpp. dups_manager.cpp removed.
 * 
 *    Rev 1.9   21 May 2014 10:47:54   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   14 Apr 2014 09:56:08   rjamloki
 * Fixed serial port for DUPS communication
 * 
 *    Rev 1.7   26 Mar 2014 12:11:50   rjamloki
 * DUPS_ManagerTask::DUPS_ManagerTask() function changed
 * 
 *    Rev 1.6   06 Mar 2014 11:03:46   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:22   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Module name:   DUPS Manager Task

 Filename:      DUPS_ManagerTask.cpp

 Function name:

 ------------------------------ DESCRIPTION -------------------------------


 This file has the code start DUPS Manager task.

 ----------------------------- INCLUDE FILES ------------------------------*/
#include "DUPS_ManagerTask.h"
#include "FIFO.h"
#include "qdef.h"
#include "DUPS.h"
#include "ready.h"
#include "stdio.h"
#include "Serial.h"
#include "digout.h"
#include "weld.h"
#include "ascii.h"
#include "psnvram.h"
#include "root.h"
#include "util.h"
#include "getmsg.h"
#include "FrontPanelKeypadTask.h"
#include "selctkey.h"
#include "UndefPrintf.h"
#include "vga_uart.h"
#include "Events.h"

#define DUPSTASK_FIFOSIZE 10
#define PSFREQ15     15
#define PSFREQ20     20
#define PSFREQ30     30
#define PSFREQ40     40

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern SINT16 *HornScanRawCurrent;
extern SINT16 *HornScanRawAmp;
extern SINT16 *HornScanRawPhase;
extern BOOLEAN IsRecalledPreset;
extern UINT16 ResonanceFreqEnable[];
extern BOOLEAN SBLMinLimitReached;
extern BOOLEAN SBLMaxLimitReached;
extern UINT16 ShowHSAbort;
extern void CharReceived(UART_CHANNEL * , UINT8 );
extern UART_CHANNEL channelB;
extern SINT32 DigTuneValue;
/*----------------------------- GLOBAL DATA --------------------------------*/
SINT32 ActualSBLMinFreq;
SINT32 ActualSBLMaxFreq;
UINT32 DupsQid; /* Queue id initialized in roots.c */
DUPS_CMDBUF DUPS_CmdBuf;
DUPS_RESPONSEBUF DUPS_RspBuf;
DUPS_RAWWELDSTATUS DUPS_RawWeldStatus;
DUPS_RAWPARAMSET DUPS_RawParamSet;
DUPS_DOWNLOADPARAMCMD DUPS_DownloadParamCmd;
DUPS_UPLOADPARAMRSP DUPS_UploadParamRsp;
HORNSCANPOINT HornScanPoint;
DUPS_CURRENTPARAMSET DUPS_HostParamSet; /* Declare the DUPS Host preset struct */
STR DUPS_HostParamSetName[DUPS_PARAMSETNAMELEN + 1]; /*DUPS host preset name*/

/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/
SINT32 DUPS_PerD2C(SINT32 DUPSPer);
SINT32 DUPS_PerC2D(SINT32 COPPer);
void UpdateScanDateandTime(void);
void InitSBL(void);
void UpdateSBL(void);

DUPS_ManagerTask *DUPS_ManagerTask::thisPtr;

DUPS_ManagerTask::DUPS_ManagerTask() :
      Task("DUPS", T_SIZE_2048), DUPS_ManagerTaskQ(DUPSTASK_FIFOSIZE, "DupsQ"), Port(1536 * 2, 1536)
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   DupsQid = (UINT32) &DUPS_ManagerTaskQ;
}

DUPS_ManagerTask::~DUPS_ManagerTask()
/****************************************************************************/
/* Description:-                                                            */
/* DUPS_ManagerTask destructor                                              */
/****************************************************************************/
{

}

void DUPS_ManagerTask::Run()
{
   DelayMs(100);
   DUPS_MSGBUF InMsg;
   enum DUPS_RESULTS status = DUPS_SUCCESS;

   Port.Init(2, 19200, 3, 3, FALSE);
   BOOLEAN PowerSupplyPresent = TRUE;
   BOOLEAN InDiagnosticMode = FALSE;
   while (TRUE) /* Wait forever for a message */
   {
	   if(InDiagnosticMode)
	   {		   
		   unsigned char ch = 0;
		   DUPS_ManagerTask::thisPtr->Port.Receive(0, ch, -1);
		   CharReceived(&channelB, ch);
	   }
	   else  if (DUPS_ManagerTaskQ.Read(this, InMsg, -1) == TRUE) {
         status = DUPS_OTHER;
         if(InMsg.mt == DUPS_MSGSENABLEDIAGNOSTIC)
         {
        	 InDiagnosticMode = TRUE;       
        	 PowerSupplyPresent = FALSE;
        	 status = DUPS_SUCCESS;
         }
         else if(PowerSupplyPresent)
         {
			 switch (InMsg.mt) {
				 case DUPS_MSGINITINTERFACE: {
					status = DUPS_MsgInitInterface();
					if(status != DUPS_SUCCESS)
					  PowerSupplyPresent = FALSE;
					break;
				 }

				 case DUPS_MSGUPLOADHWID: {
					status = DUPS_MsgUploadHWId();
					break;
				 }

				 case DUPS_MSGUPLOADSWID: {
					status = DUPS_MsgUploadSWId();
					break;
				 }

				 case DUPS_MSGSELECTPARAMSETNUM: {
					status = DUPS_MsgSelectParamSetNum((UINT8) InMsg.data1);
					break;
				 }

				 case DUPS_MSGREQUESTPARAMSETNUM: {
					status = DUPS_MsgReqParamSetNum();
					break;
				 }

				 case DUPS_MSGDOWNLOADPARAMSET: {
					status = DUPS_MsgDownloadParamSet((UINT8) InMsg.data1);
					break;
				 }

				 case DUPS_MSGUPLOADPARAMSET: {
					status = DUPS_MsgUploadParamSet((UINT8) InMsg.data1);
					break;
				 }

				 case DUPS_MSGDOWNLOADLIBRARYNAME: {
					status = DUPS_MsgDownloadLibraryName();
					break;
				 }

				 case DUPS_MSGUPLOADLIBRARYNAME: {
					status = DUPS_MsgUploadLibraryName();
					break;
				 }

				 case DUPS_MSGUPLOADLASTWELDSTATUS: {
					status = DUPS_MsgUploadWeldStatus((DUPS_WELDSTATUS *) InMsg.data2);
					break;
				 }

				 case DUPS_MSGUPLOADRELEASE: {
					status = DUPS_MsgUploadReleaseId();
					break;
				 }

				 case DUPS_MSGDOWNLOADSTARTSCAN: {
					status = DUPS_MsgDownloadStartScan();
					break;
				 }

				 case DUPS_MSGHORNSCANSTEP: {
					status = DUPS_MsgHornScanStep(InMsg.data1);
					break;
				 }

				 case DUPS_MSGHORNSCANABORT:
					status = DUPS_SUCCESS;
					break;

				 case DUPS_MSGUPLOADSCANPOINT: {
					status = DUPS_MsgUploadScanPt();
					break;
				 }
				 default: {
					status = DUPS_OTHER;
					break;
				 }
			 } /* End of switch(InMsg.mt) */
        }
         if (status != DUPS_SUCCESS) {
			  RecordAlarm(EQ15);
		   }
      } /* End of if (  q_ receive -- ) */
   } /* End of while(TRUE) */
}

/*------------------------------ CODE --------------------------------------*/
enum DUPS_RESULTS DUPS_MsgUploadHWId(void)
/******************************************************************************/
/* This function sends a command to DUPS to Upload HWId and get the power     */
/* supply Frequency and power supply Watts.                                   */
/******************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = sizeof(DUPS_CmdBuf.Count) + sizeof(DUPS_CmdBuf.Cmd);
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADHWID; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      DUPS_Info.PowerSupplyFreq = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      switch (DUPS_Info.PowerSupplyFreq) {
      case PSFREQ15:
         DUPS_Info.FreqConversion = DUPS_15KHZ;
         CurrentSetup.PSFreq = FREQ15KHZ;
         HornScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         HornScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MinScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         HS_MinScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         break;

      case PSFREQ20:
         DUPS_Info.FreqConversion = DUPS_20KHZ;
         CurrentSetup.PSFreq = FREQ20KHZ;
         HornScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         HornScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MinScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         HS_MinScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         break;

      case PSFREQ30:
         DUPS_Info.FreqConversion = DUPS_30KHZ;
         CurrentSetup.PSFreq = FREQ30KHZ;
         HornScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         HornScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MinScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         HS_MinScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
         break;

      case PSFREQ40:
         DUPS_Info.FreqConversion = DUPS_40KHZ;
         CurrentSetup.PSFreq = FREQ40KHZ;
         HornScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         HornScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MinScanInfo.StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         HS_MinScanInfo.StopFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
         break;

      default:
         break;
      }

      DUPS_Info.PowerSupplyWatts = (DUPS_RspBuf.Rsp_Data[2] * 0x100) + DUPS_RspBuf.Rsp_Data[3];
      CurrentSetup.PSWatt = DUPS_Info.PowerSupplyWatts;
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadHWId(void) */

enum DUPS_RESULTS DUPS_MsgUploadSWId(void)
/******************************************************************************/
/*                                                                            */
/* This function sends a command to DUPS to Upload SWId and get the Program   */
/* ID and the Flash Version.  Currently only DUPS version 1.x or 2.x will be  */
/* accepted.  All others will result in Failure of: Ultrasonic P/S and the    */
/* system will revert to an analog power supply.                              */
/*                                                                            */
/******************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 PgID;
   UINT16 FlashVersion;
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADSWID; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      PgID = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      FlashVersion = (DUPS_RspBuf.Rsp_Data[2] * 0x100) + DUPS_RspBuf.Rsp_Data[3];
      if ((PgID / 100 == 1 && !FlashVersion) || (PgID / 100 == 2 && !FlashVersion)) /* If progrsam version is 1 or 2 */
      { /* and Flash version = 0         */
         DUPS_Info.ProgramId = PgID;
         DUPS_Info.FlashVersion = FlashVersion;
      }
      else
         status = DUPS_OTHER;
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadSWId(void) */

enum DUPS_RESULTS DUPS_MsgSelectParamSetNum(UINT8 psNum)
/********************************************************************************/
/* This function sends a command to DUPS to select the DUPS parameter set number*/
/********************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS; //DUPS_MsgUploadParamSet(psNum);

   if (status == DUPS_SUCCESS) {
      DUPS_CmdBuf.DLE_Byte = DLE;
      DUPS_CmdBuf.STX_Byte = STX;
      DUPS_CmdBuf.Count = 0x0005;
      DUPS_CmdBuf.Cmd = DUPS_CMDSELECTPARAMSETNUM; /* Set up command */
      DUPS_CmdBuf.Cmd_Data[0] = psNum;

      status = DUPS_DataXfer();
      DUPS_CurrPSStatus = status;
      /*Set DUPS working Preset*/
      if (status == DUPS_SUCCESS) {
         CurrentSetup.DUPS_WorkingPreset = (UINT16) psNum;
         IsRecalledPreset = TRUE;
      }
   }

   return status;
}

enum DUPS_RESULTS DUPS_MsgReqParamSetNum(void)
/********************************************************************************/
/* This function sends a command to DUPS to request a DUPS parameter set number*/
/********************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;
   UINT8 *ps;

   ps = (UINT8 *) &DUPS_CurrentParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDREQUESTPARAMSETNUM; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      if (DUPS_Info.ActiveWorkNum != DUPS_RspBuf.Rsp_Data[0]) {
         DUPS_Info.ActiveWorkNum = DUPS_RspBuf.Rsp_Data[0];
         for (i = 0; i < sizeof(DUPS_CurrentParamSet); i++)
            ps[i] = 0; /*clear current param set */
      }
   }
   else {
      DUPS_Info.ActiveWorkNum = DUPS_PARAMSETUNDEF;
      for (i = 0; i < sizeof(DUPS_CurrentParamSet); i++)
         ps[i] = 0; /*clear current param set */
   }
   return status;
} /* End of SINT16 DUPS_MsgRequestParamSetNum(void) */

enum DUPS_RESULTS DUPS_MsgUploadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to upload a parameter set and the uploaded  */
/* parameter values are stored in the Current Parameter set with the frequency       */
/* conversion values.                                                                */
/*************************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;

   DUPS_UPLOADPARAMRSP *pc = (DUPS_UPLOADPARAMRSP *) &DUPS_RspBuf.Rsp_Data;
   DUPS_CURRENTPARAMSET *cp = &DUPS_CurrentParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0005;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADPARAMSET; /* Set up command */
   DUPS_CmdBuf.Cmd_Data[0] = psNum;

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      /*  for (i = 0; i < DUPS_PARAMSETNAMELEN; i++)
       DUPS_ParamSetName[psNum][i] = pc -> ParameterSetName[i];
       DUPS_ParamSetName[psNum][i] = '\0';
       strcpy(DUPS_ParamSetName[DUPS_CURRPARAMSET], DUPS_ParamSetName[psNum]);*/

      cp->Frequency = DUPS_FreqD2C(pc->Frequency);
      cp->Power = pc->Power;
      cp->Variant = pc->Variant;
      cp->DipFlag = 0; //at: pc ->  Paramset. DipFlag;
      // set both source and destination SW DIPs to be sure
      cp->SWDipSetting = pc->Paramset.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
      cp->SeekAmplitude = DUPS_PerD2C(pc->Paramset.SeekAmplitude);
      cp->SeekRampTime = pc->Paramset.SeekRampTime;
      cp->SeekTime = pc->Paramset.SeekTime;
      cp->SeekFreqLimitHigh = DUPS_FreqD2C(pc->Paramset.SeekFreqLimitHigh);
      cp->SeekFreqLimitLow = DUPS_FreqD2C(pc->Paramset.SeekFreqLimitLow);
      cp->SeekPhaseLoop = pc->Paramset.SeekPhaseLoop;
      cp->SeekPhaseLoopCF = pc->Paramset.SeekPhaseLoopCF;
      cp->SeekAmplitudeLoopC1 = pc->Paramset.SeekAmplitudeLoopC1;
      cp->SeekAmplitudeLoopC2 = pc->Paramset.SeekAmplitudeLoopC2;
      cp->WeldAmplitude = DUPS_PerD2C(pc->Paramset.WeldAmplitude);
      cp->WeldRampTime = pc->Paramset.WeldRampTime;
      cp->WeldPhaseLoop = pc->Paramset.WeldPhaseLoop;
      cp->WeldPhaseLoopCF = pc->Paramset.WeldPhaseLoopCF;
      cp->WeldAmplitudeLoopC1 = pc->Paramset.WeldAmplitudeLoopC1;
      cp->WeldAmplitudeLoopC2 = pc->Paramset.WeldAmplitudeLoopC2;
      cp->WeldFreqLimitHigh = DUPS_FreqD2C(pc->Paramset.WeldFreqLimitHigh);
      cp->WeldFreqLimitLow = DUPS_FreqD2C(pc->Paramset.WeldFreqLimitLow);
      cp->WeldPhaseLimit = pc->Paramset.WeldPhaseLimit;
      cp->WeldPhaseLimitTime = pc->Paramset.WeldPhaseLimitTime;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPSTOREMEMATWLDEND) /* Check for bit4 if set flag = True*/
         DUPS_Info.DUPSMemFlag = TRUE;
      else
         /*Update status in DUPS Info*/
         DUPS_Info.DUPSMemFlag = FALSE;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPAUTOSEEK)/* Check for bit6 if set flag = True*/
         DUPS_Info.DUPSSeekFlag = TRUE;
      else
         DUPS_Info.DUPSSeekFlag = FALSE;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPCLEARMEMATRST) /* Check for bit3 if set flag = True*/
         DUPS_Info.DUPSMemRstFlag = TRUE;
      else
         /*Update status in DUPS Info*/
         DUPS_Info.DUPSMemRstFlag = FALSE;
      CurrentPreset.DUPS_HostParamSet = DUPS_CurrentParamSet;
      UpdateCurrentPresetAndSetup((PARAM)0);
   } //if (status == DUPS_SUCCESS
   DUPS_CurrPSStatus = status; /* DUPS manager is now available */
   IsRecalledPreset = FALSE;
   return status;
} /* End of SINT16 DUPS_MsgUploadParamSet(psNum) */

enum DUPS_RESULTS DUPS_MsgDownloadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to download the current parameter set.      */
/* Dependent values are converted back to DUPS units.                                */
/*************************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;

   DUPS_DOWNLOADPARAMCMD *pc = (DUPS_DOWNLOADPARAMCMD *) &DUPS_CmdBuf.Cmd_Data;
   DUPS_CURRENTPARAMSET *cp = &DUPS_CurrentParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = sizeof(DUPS_DOWNLOADPARAMCMD) + 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDDOWNLOADPARAMSET; /* Set up command */

   pc->ParameterSetNum = psNum;

   strcpy((char*) pc->ParameterSetName, "DEFAULT            ");

   pc->Frequency = DUPS_FreqC2D(cp->Frequency);
   pc->Power = cp->Power;
   pc->Variant = cp->Variant;

   pc->Paramset.DipFlag = 0; //at: cp->DipFlag;
   // set both source and destination SW DIPs to be sure
   pc->Paramset.SWDipSetting = cp->SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
   pc->Paramset.SeekAmplitude = DUPS_PerC2D(cp->SeekAmplitude);
   pc->Paramset.SeekRampTime = cp->SeekRampTime;
   pc->Paramset.SeekTime = cp->SeekTime;
   pc->Paramset.SeekFreqLimitHigh = DUPS_FreqC2D(cp->SeekFreqLimitHigh);
   pc->Paramset.SeekFreqLimitLow = DUPS_FreqC2D(cp->SeekFreqLimitLow);
   pc->Paramset.SeekPhaseLoop = cp->SeekPhaseLoop;
   pc->Paramset.SeekPhaseLoopCF = cp->SeekPhaseLoopCF;
   pc->Paramset.SeekAmplitudeLoopC1 = cp->SeekAmplitudeLoopC1;
   pc->Paramset.SeekAmplitudeLoopC2 = cp->SeekAmplitudeLoopC2;
   pc->Paramset.WeldAmplitude = DUPS_PerC2D(cp->WeldAmplitude);
   pc->Paramset.WeldRampTime = cp->WeldRampTime;
   pc->Paramset.WeldPhaseLoop = cp->WeldPhaseLoop;
   pc->Paramset.WeldPhaseLoopCF = cp->WeldPhaseLoopCF;
   pc->Paramset.WeldAmplitudeLoopC1 = cp->WeldAmplitudeLoopC1;
   pc->Paramset.WeldAmplitudeLoopC2 = cp->WeldAmplitudeLoopC2;
   pc->Paramset.WeldFreqLimitHigh = DUPS_FreqC2D(cp->WeldFreqLimitHigh);
   pc->Paramset.WeldFreqLimitLow = DUPS_FreqC2D(cp->WeldFreqLimitLow);
   pc->Paramset.WeldPhaseLimit = cp->WeldPhaseLimit;
   pc->Paramset.WeldPhaseLimitTime = cp->WeldPhaseLimitTime;

   status = DUPS_DataXfer();
   DUPS_CurrPSStatus = status; /* Now dups manager is available */
   /*Set DUPS working Preset*/
   if (status == DUPS_SUCCESS) {
      IsRecalledPreset = FALSE;
   }
   return status;
} /* End of SINT16 DUPS_MsgDownloadParamSet(psNum) */

enum DUPS_RESULTS DUPS_MsgUploadLibraryName(void)
/*************************************************************************************/
/* This function sends a command to DUPS to upload the Library name of the Parameter */
/* sets.                                                                             */
/*************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADLIBRARYNAME; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      for (i = 0; i < DUPS_LIBRARYNAMELEN; i++)
         DUPS_Info.LibraryName[i] = DUPS_RspBuf.Rsp_Data[i];
      DUPS_Info.LibraryName[i] = '\0';
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadLibraryName(void) */

enum DUPS_RESULTS DUPS_MsgDownloadLibraryName(void)
/***************************************************************************************/
/* This function sends a command to DUPS to download the Library name of the Parameter */
/* sets.                                                                               */
/***************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = (DUPS_LIBRARYNAMELEN + 4);
   DUPS_CmdBuf.Cmd = DUPS_CMDDOWNLOADLIBRARYNAME; /* Set up command */

   for (i = 0; i < DUPS_LIBRARYNAMELEN; i++)
      DUPS_CmdBuf.Cmd_Data[i] = DUPS_Info.LibraryName[i];

   status = DUPS_DataXfer();
   return status;
} /* End of SINT16 DUPS_MsgDownloadLibraryName(void) */

enum DUPS_RESULTS DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS *outbuf)
/*************************************************************************************/
/* This function sends a command to DUPS to Upload the last weld parameters values   */
/* and stores it in the buffer provided by the API function with frequency dependent */
/* conversion values.                                                                */
/*************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;

   DUPS_RAWWELDSTATUS *inbuf = (DUPS_RAWWELDSTATUS *) &DUPS_RspBuf.Rsp_Data;
   /* caller's storage in from DUPS*/

   outbuf->OpStatus = DUPS_PENDING;
   outbuf->DataStatus = DUPS_PENDING;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADLASTWELDSTATUS; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      for (i = 0; i < DUPS_PARAMSETNAMELEN; i++)
         outbuf->ParameterSetName[i] = inbuf->ParameterSetName[i];

      outbuf->Frequency = DUPS_Info.PowerSupplyFreq;
      outbuf->Power = DUPS_Info.PowerSupplyWatts;
      outbuf->Variant = 0; /* As per comment from IRS */

      outbuf->SeekStartFrequency = DUPS_FreqD2C(inbuf->SeekStartFrequency);
      outbuf->SeekStopFrequency = DUPS_FreqD2C(inbuf->SeekStopFrequency);
      outbuf->SeekMemoryFrequency = DUPS_FreqD2C(inbuf->SeekMemoryFrequency);
      outbuf->WeldStartFrequency = DUPS_FreqD2C(inbuf->WeldStartFrequency);
      outbuf->WeldStopFrequency = DUPS_FreqD2C(inbuf->WeldStopFrequency);
      outbuf->WeldMemoryFrequency = DUPS_FreqD2C(inbuf->WeldMemoryFrequency);
      outbuf->WeldTime = inbuf->WeldTime;
      outbuf->WeldEnergy = inbuf->WeldEnergy;
      outbuf->Temperature = inbuf->Temperature;
      outbuf->State = inbuf->State;
      outbuf->ErrorState = inbuf->ErrorState;
      outbuf->ErrorReason = inbuf->ErrorReason;
      outbuf->ErrorFrequency = DUPS_FreqD2C(inbuf->ErrorFrequency);
      outbuf->ErrorPower = inbuf->ErrorPower;
      outbuf->ErrorCurrent = DUPS_PerD2C(inbuf->ErrorCurrent);
      outbuf->ErrorPSV = DUPS_PerD2C(inbuf->ErrorPSV * 8); // 0..255 convert to 0..2047
      // might need also sign modification
      outbuf->ErrorAmplitude = inbuf->ErrorAmplitude;
      outbuf->ErrorTime = inbuf->ErrorTime;

   }
   outbuf->OpStatus = status;
   outbuf->DataStatus = status;
   return status;
} /* End of SINT16 DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS *outbuf) */

enum DUPS_RESULTS DUPS_MsgUploadReleaseId(void)
/*************************************************************************************/
/* This function send a command to DUPS to Upload the release ID of DUPS and check   */
/* for ID = 0x1111                                                                   */
/*************************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADRELEASE; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      if (DUPS_RspBuf.Rsp_Data[0] == 0x11 && DUPS_RspBuf.Rsp_Data[1] == 0x11) {
         DUPS_Info.ProgramId = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      }
      else
         status = DUPS_OTHER;
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadReleaseId(void) */

enum DUPS_RESULTS DUPS_MsgDownloadStartScan(void)
/*****************************************************************************************/
/* This function sends a command to DUPS to start a horn scan. All input scan parameters */
/* are converted back to DUPS units before downloading. Also all scan output paramters   */
/* buffers are initialised.                                                              */
/*****************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 i;
   DUPS_MSGBUF outMsg;
   memset(&outMsg, 0, sizeof(DUPS_MSGBUF));
   DUPS_STARTSCANCMD *sp = (DUPS_STARTSCANCMD *) &DUPS_CmdBuf.Cmd_Data;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = /*DUPS_CMDHEADER*/0x0004 + sizeof(DUPS_STARTSCANCMD);
   DUPS_CmdBuf.Cmd = DUPS_CMDDOWNLOADSTARTSCAN; /* Set up command */

   /* transfer the values from hornsacn info to scanparams struct */
   sp->StartFreq = DUPS_FreqC2D(HornScanInfo.StartFreq);
   sp->StopFreq = DUPS_FreqC2D(HornScanInfo.StopFreq);
   sp->FreqStep = DUPS_FreqC2D(HornScanInfo.FreqStep);
   sp->TimeDelay = HornScanInfo.TimeDelay;
   sp->MaximumAmplitude = DUPS_PerC2D(HornScanInfo.MaximumAmplitude);
   sp->MaximumCurrent = DUPS_PerC2D(HornScanInfo.MaximumCurrent);

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      ClearReady();
      for (i = 0; i <= DUPS_HORNSCANMAXPOINTS; i++){
         HornScanRawCurrent[i] = 0xFFFF;
         HornScanRawPhase[i] = 0xFFFF;
         HornScanRawAmp[i] = 0xFFFF;
      }

      //  Clear the old scan data in BBram
      HornScanInfo.NumScanPoints = 0;
      for (i = 0; i < DUPS_NUMRESONANCES; i++) {
         HornScanInfo.ResonanceFreqs[i] = 0;
         HornScanInfo.ResonanceFreqType[i] = FREQ_NONE;
         ResonanceFreqEnable[i] = 0;
      }
      HornScanInfo.ScanStatus = DUPS_SCANINPROG;
      UpdateScanDateandTime();

      DUPS_RAM2FRAM();

      outMsg.data1 = HORNSCANCOLLECTING;
      outMsg.mt = DUPS_MSGHORNSCANSTEP; /*send message */
      DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
   }
   else
      HornScanInfo.ScanStatus = DUPS_NOSCAN;
   return status;
}

enum DUPS_RESULTS DUPS_MsgHornScanStep(SINT16 scanStep)
/*************************************************************************************/
/* This function processes the Scan data depending on the current state of the scan  */
/* i.e, HORNSCANCOLLECTING,HORNSCANCALCULATING etc.                                  */
/*************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_OTHER;
   DUPS_MSGBUF outMsg;
   memset(&outMsg, 0, sizeof(DUPS_MSGBUF));
   UINT16 i;
   char D1[MAX_EVENTDATA_LEN];
   switch (scanStep) {
   case HORNSCANCOLLECTING:
      HornScanInfo.ScanStatus = DUPS_SCANINPROG;
      outMsg.mt = DUPS_MSGUPLOADSCANPOINT;
      DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
      status = DUPS_SUCCESS;
      break;

   case HORNSCANCALCULATING:
      HornScanInfo.ScanStatus = DUPS_SCANSCOMPLETE;
      ShowHSAbort = FALSE;
      HS_Resonance();
      status = DUPS_SUCCESS;
      break;

   case HORNSCANCOMPLETED:	  
	  memset(D1, 0 , sizeof(D1));
      HS_Decimate(HornScanRawCurrent, HornScanRawPhase,HornScanRawAmp, (HornScanInfo.NumScanPoints - HS_NUMCOEFS), HornScanCurrent,
            HornScanPhase,HornScanAmp);
      UpdateKeyMask(HSSUBMENUMASK);
      HornScanInfo.ScanStatus = DUPS_SCANDATAAVAIL;
      UpdateScanDateandTime(); /* Update RTC parameters after scan*/
      SendFakeKeyPress(UPDATEDISPLAY);
      DUPS_RAM2FRAM();
      UpdateSBL();
      status = DUPS_SUCCESS;
      Numout2(DigTuneValue, 10, D1, MAX_EVENTDATA_LEN - 1);
      RecordEvents(EVENT_HORN_SCAN_COMPLETED, D1,"");
      CurrentPresetParameterChanged = TRUE;
      break;

   case HORNSCANABORTED:
      for (i = 0; i <= DUPS_HORNSCANMAXPOINTS; i++){ //  initialize temporary work area pointers
         HornScanRawCurrent[i] = 0xFFFF;
         HornScanRawPhase[i] = 0xFFFF;
         HornScanRawAmp[i] = 0xFFFF;
      }

      HornScanInfo.NumScanPoints = 0;
      for (i = 0; i < DUPS_NUMRESONANCES; i++) {
         HornScanInfo.ResonanceFreqs[i] = 0;
         HornScanInfo.ResonanceFreqType[i] = FREQ_NONE;
         ResonanceFreqEnable[i] = 0;
      }
      HornScanInfo.ScanStatus = DUPS_NOSCAN;
      SendFakeKeyPress(UPDATEDISPLAY);
      status = DUPS_SUCCESS;
      InitSBL();
      CurrentPresetParameterChanged = TRUE;
      break;

   default:
      status = DUPS_OTHER;
      outMsg.mt = DUPS_MSGHORNSCANABORT;
      DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
      break;
   } /* End of switch(scanStep) */
   return status;
} /* End of SINT16 DUPS_MsgDownloadStartScan(void) */

enum DUPS_RESULTS DUPS_MsgInitInterface(void)
/************************************************************************************/
/* This function does the initialization of DUPS at power up and gets the required  */
/* data for processing and initialises some DUPS data. This function also tells     */
/* whether DUPS is present, expected or not absent at power up.                     */
/************************************************************************************/

{
   enum DUPS_RESULTS status = DUPS_OTHER;
   UINT8 i = 0;

   DUPSOkFlag = FALSE; /* DUPS Initialization is in Progress */

   DUPS_FRAM2RAM(); /* initialise data in RAM from FRAM at power up*/

   while ((i++ < DUPS_INITTRIES) && (status != DUPS_SUCCESS)) {
      status = DUPS_MsgUploadReleaseId();
   }
   CurrentSetup.DUPS_WorkingPreset = DUPS_CURRPARAMSET;
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgSelectParamSetNum((UINT8) CurrentSetup.DUPS_WorkingPreset);
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadSWId();
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadHWId();

   HornScanInfo.FreqStep = HS_MinScanInfo.FreqStep;
   HornScanInfo.TimeDelay = HS_MinScanInfo.TimeDelay;
   HornScanInfo.MaximumAmplitude = HS_MinScanInfo.MaximumAmplitude;
   HornScanInfo.MaximumCurrent = HS_MinScanInfo.MaximumCurrent;

   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadLibraryName();

   /*
    At this point all of the actions for initialization have been tried.  Now we need to
    check for the results.
    */
   if (status == DUPS_SUCCESS) {
      CurrentSetup.PSType = TRUE; // DUPS is present and working
      DUPS_Info.DUPSFlag = TRUE; // DUPS is up0
      DUPS_RAM2FRAM();
      UpdateHWConfiguration(DUPS, TRUE);
      StorePSFrequency(); /* update novram with DUPS frequency setting */
      StorePSWattage(); /* update novram with DUPS wattage setting */
      SetMaxMinValues(); /* Update Min/Max based on new setting */
      FramInitialized = FALSE;
   }
   else // no DUPS detected
   {
      DUPS_Info.DUPSFlag = FALSE; // DUPS is not up
      if (CurrentSetup.PSType == TRUE) // DUPS expected but failed
      {
         UpdateHWConfiguration(DUPS, FALSE);
         RecordAlarm(EQ15);
      }
      else {
         status = DUPS_SUCCESS; // no error if DUPS not expected
         UpdateHWConfiguration(DUPS, FALSE);
      }
   }
   DUPS_CurrentParamSet = CurrentPreset.DUPS_HostParamSet;
   RefreshDUPSParam();//Refresh the Dip settings once at power up for menu
   DUPSOkFlag = TRUE; /* DUPS Initialization is Completed */
   return status;
} // end of DUPS_MsgInitInterface(void)

SINT32 DUPS_FreqC2D(SINT32 COPFreq)
/**********************************************************************************/
/* This function converts the frequency dependent values from COPS to DUPS        */
/**********************************************************************************/

{
   return ((COPFreq * 40) / DUPS_Info.FreqConversion);
} // end of DUPS_FreqC2D(SINT32 COPFreq)

SINT32 DUPS_FreqD2C(SINT32 DUPSFreq)
/**********************************************************************************/
/* This function converts the frequency dependent values from DUPS to COPS        */
/**********************************************************************************/
{
   return ((DUPSFreq * DUPS_Info.FreqConversion) / 40);
} // end of DUPS_FreqD2C(SINT32 DUPSFreq)

SINT32 DUPS_PerD2C(SINT32 DUPSPer)
/**********************************************************************************/
/* This function converts the percentage dependent values from DUPS to COPS        */
/**********************************************************************************/

{
   return ((DUPSPer * 100 + 1023) / 2047);
} // end of DUPS_PerD2C()

SINT32 DUPS_PerC2D(SINT32 COPPer)
/**********************************************************************************/
/* This function converts the percentage dependent values from COPS to DUPS        */
/**********************************************************************************/

{
   return ((COPPer * 2047 + 49) / 100);
} // end of DUPS_PerC2D()

void UpdateScanDateandTime(void)
/**********************************************************************************/
/* THis function updates the time, date, year and month after a scan is complete  */
/**********************************************************************************/

{
   RTCTime HS_Time;

   RTClock::GetCurrentTime(&HS_Time);
   HornScanInfo.Year = HS_Time.Years;
   HornScanInfo.Month = HS_Time.Century_Month;
   HornScanInfo.Day = HS_Time.Day;
   HornScanInfo.Hour = HS_Time.Hour;
   HornScanInfo.Minute = HS_Time.Minute;
} /* end of func  UpdateScanDateandTime(void)*/

void InitSBL(void)
/**********************************************************************************/
/* Set up initial SBL values (Horn scan will override them).                      */
/**********************************************************************************/
{
   UINT16 Offset;
   SINT32 TempPSFreq;

   Offset = GetPowerSupplyFrequencyOffset();
   TempPSFreq = GetPowerSupplyFrequency();
   CurrentPreset.SBLMinFreqLim = TempPSFreq - Offset;
   CurrentPreset.SBLMaxFreqLim = TempPSFreq + Offset;
   CurrentPreset.SBLMinFreq = CurrentPreset.SBLMinFreqLim;
   CurrentPreset.SBLMaxFreq = CurrentPreset.SBLMaxFreqLim;
   CurrentPreset.SBLFreqFlags = 0x03; //Both + and - SBL flags are off
}

void UpdateSBL(void)
/**********************************************************************************/
/* Update SBL values based on horn scan results                                   */
/**********************************************************************************/
{
   UINT8 i;
   UINT16 ResFreq, MinSerFreq, MaxSerFreq;
   UINT32 Diff;

   ResFreq = 0;
   for (i = 0; i < DUPS_NUMRESONANCES; i++) {
      if (HornScanInfo.ResonanceFreqType[i] == FREQ_PARALLEL)
         ResFreq = HornScanInfo.ResonanceFreqs[i];
   }
   // What if we didn't get any parallel frequencies?
   if (ResFreq == 0)
      ResFreq = GetPowerSupplyFrequency();
   // Get minimum series frequency
   MinSerFreq = GetPowerSupplyFrequency() - GetPowerSupplyFrequencyOffset();
   for (i = 0; i < DUPS_NUMRESONANCES; i++) {
      if ((HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES) && (HornScanInfo.ResonanceFreqs[i] < ResFreq)
            && (HornScanInfo.ResonanceFreqs[i] > MinSerFreq))
         MinSerFreq = HornScanInfo.ResonanceFreqs[i];
   }
   // Same for maximum frequency
   MaxSerFreq = GetPowerSupplyFrequency() + GetPowerSupplyFrequencyOffset();
   for (i = 0; i < DUPS_NUMRESONANCES; i++) {
      if ((HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES) && (HornScanInfo.ResonanceFreqs[i] > ResFreq)
            && (HornScanInfo.ResonanceFreqs[i] < MaxSerFreq))
         MaxSerFreq = HornScanInfo.ResonanceFreqs[i];
   }
   // Done, let's store them
   //CurrentPreset.SBLParFreq = ResFreq;
   // Either the min PS freq, or 90% of the way from parallel freq to series
   if (MinSerFreq == GetPowerSupplyFrequency() - GetPowerSupplyFrequencyOffset()) {
      CurrentPreset.SBLMinFreqLim = MinSerFreq;
   }
   else {
      Diff = ResFreq - MinSerFreq;
      Diff *= 90;
      Diff /= 100;
      CurrentPreset.SBLMinFreqLim = ResFreq - Diff;
   }
   // Either the max PS freq, or 90% of the way from parallel freq to series
   if (MaxSerFreq == GetPowerSupplyFrequency() + GetPowerSupplyFrequencyOffset()) {
      CurrentPreset.SBLMaxFreqLim = MaxSerFreq;
   }
   else {
      Diff = MaxSerFreq - ResFreq;
      Diff *= 90;
      Diff /= 100;
      CurrentPreset.SBLMaxFreqLim = ResFreq + Diff;
   }
   CurrentPreset.SBLMinFreq = CurrentPreset.SBLMinFreqLim;
   CurrentPreset.SBLMaxFreq = CurrentPreset.SBLMaxFreqLim;
   //CurrentPreset.SBLFreqFlags = 0x00; //Both + and - SBL are made ON. //Removed after code review
}

void VerifySBL(void)
{
   if (CurrentSequence == WELD) {
      if ((CurrentFreqIn < RunningPreset.SBLMinFreq) && !(SBLMinLimitReached)) {
         SBLMinLimitReached = TRUE;
         ActualSBLMinFreq = CurrentFreqIn;
      }
      if ((CurrentFreqIn > RunningPreset.SBLMaxFreq) && !(SBLMaxLimitReached)) {
         SBLMaxLimitReached = TRUE;
         ActualSBLMaxFreq = CurrentFreqIn;
      }
   }
}

BOOLEAN DUPS_HostUploadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to upload a parameter set and the uploaded  */
/* parameter values are stored in the host Parameter set with the frequency          */
/* conversion values.                                                                */
/*************************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   BOOLEAN Flag = TRUE;
   UINT8 i = 0;
   UINT16 DUPS_paramsetno = psNum;
   DUPS_UPLOADPARAMRSP *pc = (DUPS_UPLOADPARAMRSP *) &DUPS_RspBuf.Rsp_Data;
   DUPS_CURRENTPARAMSET *cp = &DUPS_HostParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = 0x0005;
   DUPS_CmdBuf.Cmd = DUPS_CMDUPLOADPARAMSET; /* Set up command */
   DUPS_CmdBuf.Cmd_Data[0] = (UINT8) DUPS_paramsetno;

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS) {
      for (i = 0; i < DUPS_PARAMSETNAMELEN; i++)
         DUPS_HostParamSetName[i] = pc->ParameterSetName[i];
      DUPS_HostParamSetName[i] = '\0';

      cp->Frequency = DUPS_FreqD2C(pc->Frequency);
      cp->Power = pc->Power;
      cp->Variant = pc->Variant;
      cp->DipFlag = 0; //at: pc ->  Paramset. DipFlag;
      // set both source and destination SW DIPs to be sure
      cp->SWDipSetting = pc->Paramset.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
      cp->SeekAmplitude = DUPS_PerD2C(pc->Paramset.SeekAmplitude);
      cp->SeekRampTime = pc->Paramset.SeekRampTime;
      cp->SeekTime = pc->Paramset.SeekTime;
      cp->SeekFreqLimitHigh = DUPS_FreqD2C(pc->Paramset.SeekFreqLimitHigh);
      cp->SeekFreqLimitLow = DUPS_FreqD2C(pc->Paramset.SeekFreqLimitLow);
      cp->SeekPhaseLoop = pc->Paramset.SeekPhaseLoop;
      cp->SeekPhaseLoopCF = pc->Paramset.SeekPhaseLoopCF;
      cp->SeekAmplitudeLoopC1 = pc->Paramset.SeekAmplitudeLoopC1;
      cp->SeekAmplitudeLoopC2 = pc->Paramset.SeekAmplitudeLoopC2;
      cp->WeldAmplitude = DUPS_PerD2C(pc->Paramset.WeldAmplitude);
      cp->WeldRampTime = pc->Paramset.WeldRampTime;
      cp->WeldPhaseLoop = pc->Paramset.WeldPhaseLoop;
      cp->WeldPhaseLoopCF = pc->Paramset.WeldPhaseLoopCF;
      cp->WeldAmplitudeLoopC1 = pc->Paramset.WeldAmplitudeLoopC1;
      cp->WeldAmplitudeLoopC2 = pc->Paramset.WeldAmplitudeLoopC2;
      cp->WeldFreqLimitHigh = DUPS_FreqD2C(pc->Paramset.WeldFreqLimitHigh);
      cp->WeldFreqLimitLow = DUPS_FreqD2C(pc->Paramset.WeldFreqLimitLow);
      cp->WeldPhaseLimit = pc->Paramset.WeldPhaseLimit;
      cp->WeldPhaseLimitTime = pc->Paramset.WeldPhaseLimitTime;

   } //if (status == DUPS_SUCCESS
   if (status != DUPS_SUCCESS)
      Flag = FALSE;
//   }
   return Flag;
} /* End of SINT16 DUPS_HostMsgUploadParamSet(psNum) */

BOOLEAN DUPS_HostDownloadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to download the host parameter set.         */
/* Dependent values are converted back to DUPS units.                                */
/*************************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;
   BOOLEAN Flag = TRUE;

   DUPS_DOWNLOADPARAMCMD *pc = (DUPS_DOWNLOADPARAMCMD *) &DUPS_CmdBuf.Cmd_Data;
   DUPS_CURRENTPARAMSET *cp = &DUPS_HostParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count = sizeof(DUPS_DOWNLOADPARAMCMD) + 0x0004;
   DUPS_CmdBuf.Cmd = DUPS_CMDDOWNLOADPARAMSET; /* Set up command */

   pc->ParameterSetNum = psNum;

   for (i = 0; i < DUPS_PARAMSETNAMELEN; i++)
      pc->ParameterSetName[i] = DUPS_HostParamSetName[i];

   pc->Frequency = DUPS_FreqC2D(cp->Frequency);
   pc->Power = cp->Power;
   pc->Variant = cp->Variant;

   pc->Paramset.DipFlag = 0; //at: cp->DipFlag;
   // set both source and destination SW DIPs to be sure
   pc->Paramset.SWDipSetting = cp->SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
   pc->Paramset.SeekAmplitude = DUPS_PerC2D(cp->SeekAmplitude);
   pc->Paramset.SeekRampTime = cp->SeekRampTime;
   pc->Paramset.SeekTime = cp->SeekTime;
   pc->Paramset.SeekFreqLimitHigh = DUPS_FreqC2D(cp->SeekFreqLimitHigh);
   pc->Paramset.SeekFreqLimitLow = DUPS_FreqC2D(cp->SeekFreqLimitLow);
   pc->Paramset.SeekPhaseLoop = cp->SeekPhaseLoop;
   pc->Paramset.SeekPhaseLoopCF = cp->SeekPhaseLoopCF;
   pc->Paramset.SeekAmplitudeLoopC1 = cp->SeekAmplitudeLoopC1;
   pc->Paramset.SeekAmplitudeLoopC2 = cp->SeekAmplitudeLoopC2;
   pc->Paramset.WeldAmplitude = DUPS_PerC2D(cp->WeldAmplitude);
   pc->Paramset.WeldRampTime = cp->WeldRampTime;
   pc->Paramset.WeldPhaseLoop = cp->WeldPhaseLoop;
   pc->Paramset.WeldPhaseLoopCF = cp->WeldPhaseLoopCF;
   pc->Paramset.WeldAmplitudeLoopC1 = cp->WeldAmplitudeLoopC1;
   pc->Paramset.WeldAmplitudeLoopC2 = cp->WeldAmplitudeLoopC2;
   pc->Paramset.WeldFreqLimitHigh = DUPS_FreqC2D(cp->WeldFreqLimitHigh);
   pc->Paramset.WeldFreqLimitLow = DUPS_FreqC2D(cp->WeldFreqLimitLow);
   pc->Paramset.WeldPhaseLimit = cp->WeldPhaseLimit;
   pc->Paramset.WeldPhaseLimitTime = cp->WeldPhaseLimitTime;

   status = DUPS_DataXfer();
   if (status != DUPS_SUCCESS) {
      Flag = FALSE;
   }
   return Flag;
} /* End of SINT16 DUPS_HostDownloadParamSet(psNum) */

void UpdateDUPS_MaxWeldFreqLimit(void)
/*************************************************************************************/
/* This function changes maximum limit of  WeldFreqLimitHigh and WeldFreqLimitLow    */
/* of DUPS_CURRENTPARAMSET according to PSfrequency.                                 */
/*************************************************************************************/
{
   switch (CurrentSetup.PSFreq) {
   case FREQ15KHZ:
      DUPS_MaxParamSet.WeldFreqLimitHigh = 375;
      DUPS_MaxParamSet.WeldFreqLimitLow = 375;
      break;
   case FREQ30KHZ:
      DUPS_MaxParamSet.WeldFreqLimitHigh = 750;
      DUPS_MaxParamSet.WeldFreqLimitLow = 750;
      break;
   case FREQ40KHZ:
      DUPS_MaxParamSet.WeldFreqLimitHigh = 1000;
      DUPS_MaxParamSet.WeldFreqLimitLow = 1000;
      break;
   case FREQ60KHZ:
      DUPS_MaxParamSet.WeldFreqLimitHigh = 1500;
      DUPS_MaxParamSet.WeldFreqLimitLow = 1500;
      break;
   case FREQ20KHZ:
   default:
      DUPS_MaxParamSet.WeldFreqLimitHigh = 500;
      DUPS_MaxParamSet.WeldFreqLimitLow = 500;
      break;
   }
}

