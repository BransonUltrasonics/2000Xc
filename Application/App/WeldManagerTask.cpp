/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/WeldManagerTask.cpp_v   1.48   Oct 10 2017 15:36:46   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/WeldManagerTask.cpp_v  $
 * 
 *    Rev 1.49   Mar 13 2020 16:46:00   rvite
 * added call to SetTrigger() to communicate that the weld data is ready to be sent via DIC
 *
 *    Rev 1.48   Oct 10 2017 15:36:46   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.47   Jun 07 2017 14:28:08   RJamloki
 * Fixes from code review 5/29/2017 bucket 3
 * 
 *    Rev 1.46   Jan 12 2017 15:36:24   RJamloki
 * Added fix from special v12.1S1 to v12.3 bucket 3
 * 
 *    Rev 1.45   26 Aug 2016 10:53:02   RJamloki
 * Don't send when UserId is "N/A" to serial port fro sunrise bucket #2 release
 * 
 *    Rev 1.44   30 May 2016 12:50:28   RJamloki
 * Added UserID & Part-ID to serial output
 * 
 *    Rev 1.43   09 May 2016 13:34:16   RJamloki
 * Added RS232 functionality for version 12.2
 * 
 *    Rev 1.37   16 Apr 2015 07:18:10   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.36   09 Apr 2015 05:35:46   RJamloki
 * Removed PMC limit alarm checks from from FINALDATASTATE.
 * 
 *    Rev 1.35   01 Apr 2015 13:03:26   amaurya
 * making abortflag false if usboffline flag is true, to fix the Palm Buttons does not start cycle after USB Memory Failure alarm reset.
 * 
 *    Rev 1.34   27 Mar 2015 11:12:18   amaurya
 * Added CONFIRMREJECTSTATE in OP_WELDER_STATE_CHANGE message handling.
 * 
 *    Rev 1.33   11 Mar 2015 09:20:20   amaurya
 * CheckPrinterStatus() removed.
 * 
 *    Rev 1.32   11 Feb 2015 06:30:56   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.31   21 Jan 2015 09:36:52   amaurya
 * changed to run invalidated preset in automation mode.
 * 
 *    Rev 1.30   08 Jan 2015 03:18:30   AnPawar
 * printf removed
 * 
 *    Rev 1.29   12 Dec 2014 05:32:16   RJamloki
 * Disabled checking limit alarms for down speed cycles
 * 
 *    Rev 1.28   11 Dec 2014 08:38:28   AnPawar
 * copying ps sn and act sn to welding result.
 * 
 *    Rev 1.27   28 Nov 2014 07:43:10   rjamloki
 * Warning Fix.Removed Unused Variables.
 * 
 *    Rev 1.26   10 Nov 2014 05:00:44   AnPawar
 * WeldManagerTask::Run() function changed .In UpdateRPreset() function checking running preset 12.F review comment.
 * 
 *    Rev 1.25   03 Nov 2014 11:48:22   tayars
 * Changes made for code review
 * 
 *    Rev 1.24   06 Oct 2014 06:48:54   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.23   03 Oct 2014 06:02:44   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.22   26 Sep 2014 03:14:28   rjamloki
 * Removed psos references
 * 
 *    Rev 1.21   25 Sep 2014 14:13:10   tayars
 * Fixed issue where downspeed wasn't getting set properly when recalling a preset.
 * 
 *    Rev 1.20   11 Sep 2014 11:12:08   rjamloki
 * Coverity fixes
 * 
 *    Rev 1.19   05 Sep 2014 05:28:54   rjamloki
 * RecallExtPreset has given argument to differetiate between external preset and sequencing
 * 
 *    Rev 1.18   18 Aug 2014 01:48:50   rjamloki
 * Added MICRO support. Removed checks based on CurrentSetup.SerialPort.
 * 
 *    Rev 1.17   07 Aug 2014 15:50:46   tayars
 * Added check for downspeed tune flag when not in ready
 * 
 *    Rev 1.16   28 Jul 2014 12:59:42   rjamloki
 * Setting preset validated and locked to false on validation status change
 * 
 *    Rev 1.15   15 Jul 2014 18:14:24   hasanchez
 * Changes related to the extra beep
 * 
 *    Rev 1.14   09 Jul 2014 12:22:56   rjamloki
 * Added CheckForPresetvalidation function
 * 
 *    Rev 1.13   20 Jun 2014 14:12:00   rjamloki
 * Updating global flow and pressure values on running preset update.
 * 
 *    Rev 1.12   11 Jun 2014 12:38:58   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.11   27 May 2014 10:14:38   amaurya
 * Added alarm for History validation
 * 
 *    Rev 1.10   21 May 2014 10:48:16   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 03:56:00   rjamloki
 * extern variables clean up and coverity fixes
 * 
 *    Rev 1.8   14 Apr 2014 09:39:52   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.7   26 Mar 2014 12:41:44   rjamloki
 * WeldManagerTask::WeldManagerTask() function changed
 * 
 *    Rev 1.6   06 Mar 2014 11:04:02   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:50   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 05:00:00   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:46:00   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: WeldManagerTask.cpp

 -------------------------------- DESCRIPTION --------------------------------
*/





/* ------------------------------ INCLUDE FILES --------------------------------*/
#include "WeldManagerTask.h"
#include "FIFO.h"
#include "qdef.h"
#include "actnvram.h"
#include "names.h"
#include "opcodes.h"             /* incoming message opcodes            */
#include "preset.h"
#include "prsetmsg.h"
#include "psnvram.h"
#include "menu1.h"
#include "ipsatype.h"
#include "menu.h"
#include "WeldManagerTask.h"            /* Weld event definitions              */
#include "wldstate.h"
#include "genrlmsg.h"            /* generic message type                */
#include "graphs.h"              /* generic message type                */
#include "weld_msg.h"
#include "keypad.h"
#include "beep.h"
#include "fpkp_msg.h"
#include "state.h"
#include "statedrv.h"
#include "selctkey.h"
#include "snsrcalb.h"
#include "alarms.h"
#include "ready.h"
#include "digout.h"
#include "fpled.h"
#include "getmsg.h"
#include "display.h"
#include "rtclock.h"
#include "alsetup.h"
#include "mansensr.h"
#include "util.h"
#include "dups_api.h"
#include "vpreset1.h"
#include "menu7a.h"
#include "actnvram.h"
#include "menu3.h"
#include "serial.h"
#include "inports.h"
#include "outports.h"
#include "spidd.h"
#include "genalarm.h"
#include "stdio.h"
#include "command.h"
#include "SystemManagerTask.h"
#include "fmtstrs.h"
#include "UndefPrintf.h"
#include "RVTSHandlerTask.h"
#include "command.h"
#include "WeldHold.h"
#include "FlowLookupTable.h"
#include "Events.h"
#include "ipscdmsg.h"
#include"DIComm2000Xc.h"

/* printer related function */
#define DIST_STR_SIZE     7
#define TESTKEYREPEATTIME  400 /* Slightly more then actual repeat time  */
#define TAB                0x09
#define COMMA              ','
#define SPACE              32
#define CRLF               "\r\n"
#define WELDMNGRTASK_FIFOSIZE 10
#define ASCIILENGTH 132

void UpdateRPreset(void);
BOOLEAN CheckVerifyPresetRequired (void);
BOOLEAN CheckPresetValidation();
UINT32 GetCurrentHwCnfg (void);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
STR StrWeldStateLine[VGA_LINESIZE];
STR RS232DataLine[ASCIILENGTH];
UINT8 CheckPrinterStatus = FALSE;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT16 PresetHasBeenOKed;
extern BOOLEAN ResetRecall_UpdateFlag;
extern BOOLEAN VerifyPresetRequired;
UINT8 weld_data_flag = 0;
BOOLEAN UpdateFlag = TRUE;
WELD_DATA FinalResults;
UINT16 PresetNeedsToBeUpdated = FALSE;
UINT16 TestKeyRepeat;
UINT16 PowerUpPresetReceived = FALSE;
WMGR_MSG_QUEUE_TYPE WmgrMsg;
UINT32 WmgrQid;

static UINT16 BeepFlag;
static UINT32 LastCycleTimer;

extern WMGR_MSG_QUEUE_TYPE WmgrMsg;
extern STR StrWeldStateLine[VGA_LINESIZE];
extern UINT8  AETrigger;
extern UINT16 AlarmCounter;
extern INBITS Inp;
extern enum WELDSTATES WeldState;
extern UINT16 TestTimerCounter;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT16   ResetReceivedFlag;
extern UINT16   TestModeAllowed;
extern BOOLEAN  TestSonicsFlag, HornDownFlag, SonicsOnFlag;
extern UINT16   CalibrationPassed;
extern UINT32 SystemTimer;
extern UINT16  ReadyAlreadySet;
extern BOOLEAN ActuatorChanged;
extern BOOLEAN VGAHDAlarm;
extern BOOLEAN ResetRecall_UpdateFlag;
extern BOOLEAN VerifyPresetRequired;
extern BOOLEAN WeldingStopInsideMenu;
extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN VGAWeldStartData;
extern BOOLEAN VGAUSBOfflineFlag;
extern BOOLEAN VGAHistoryValidatedFlag;
extern UINT32 TotalCycleTime;
extern BOOLEAN WindowSetupFlag;
extern BOOLEAN VGADISKFullFlag;
extern UINT8 weld_data_flag;
extern BOOLEAN UpdateFlag;
extern UINT16 TestKeyRepeat;
extern UINT16 PowerUpPresetReceived;
extern WMGR_MSG_QUEUE_TYPE WmgrMsg;
extern void UpdateRPreset(void);
extern BOOLEAN CheckVerifyPresetRequired (void);
extern void ResetHDAlarms(void);
extern BOOLEAN IsCalibGoingOn(void);
extern UINT32 GetCurrentHwCnfg (void);
extern void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
extern SINT8 * Trim_FillChar(SINT8 Str_temp[]);
extern SINT32 DownspeedTuneCycles;
extern BOOLEAN DownspeedTuneFlag;
extern BOOLEAN UpdateOnBatchCountChange;

WeldManagerTask *WeldManagerTask::thisPtr;

WeldManagerTask::WeldManagerTask() :
   Task("WeldMngr", T_SIZE_1024), WELDMNGRTaskQ(WELDMNGRTASK_FIFOSIZE, "WMGRQ")
/****************************************************************************/
/* Description:-                                                            */
/* WeldManagerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   WmgrQid = (UINT32) &WELDMNGRTaskQ;
//   DiComPtr= new DIComm(0);
}

WeldManagerTask::~WeldManagerTask()
/****************************************************************************/
/* Description:-                                                            */
/* WeldManagerTask destructor                                              */
/****************************************************************************/
{

}

void WeldManagerTask::Run()
{
/*---------------------------------------------------------------*/
   /*            Define and Initialize Local Variables              */
   FRONT_PANEL_USER_REQUEST_MSG FpscMsg;
   FP_KEY_PRESSED_MSG           FPKeyMsg;
   WELD_DATA_MSG                WeldDataMsg;
   HOST_COMMAND_MSG             ReadWeldDataResponseMsg;
   RTCTime RTCWeld;
   BOOLEAN ExternalPresetAlarm = FALSE; /* Assume the external preset is available */
   UINT16 NextPreset;

   FpscMsg.common.opcode       = OP_FRONT_PANEL_KEYPRESS;
   FpscMsg.common.pointer_flag = NO_DATA_PTR;
   FpscMsg.common.source_task  = FPKP_SOURCE_TASK;

    /* Form the message, OP_READ_WELD_DATA_RESPONSE with the */
    /* sware_log_return_data_ptr and send to RSCH queue      */

   ReadWeldDataResponseMsg.byte_count          = sizeof(WELD_DATA);
   ReadWeldDataResponseMsg.common.opcode       = (MSG_OPCODE_TYPE)START_WELD_DATA;
   ReadWeldDataResponseMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
   ReadWeldDataResponseMsg.common.source_task  = (SOURCE_TASK_ID_TYPE)WELD_MGR;
   ReadWeldDataResponseMsg.data_pointer        = &FinalResults;
   DelayMs(100);
   while (TRUE)
   {
      /* Wait for an event of epic proportions to continue */

      /* Check msg queue */
      WELDMNGRTaskQ.Read(this, WmgrMsg, -1);

      ExternalPresetAlarm = FALSE; /* Assume the external preset is available */

      switch (WmgrMsg.GenericMsg.common.opcode) {

         case OP_TEST_KEY_PRESSED:
            if ((SystemTimer - LastCycleTimer) <= TESTKEYREPEATTIME) {
               TestKeyRepeat = TRUE;
               if ((WeldingResults.OverloadAlarms & OL1) ==
                   (OL1 & ALARMCODEMASK) ) {
                  Beep(ERRORBEEP);
                  PSReset();
                  TestModeAllowed = FALSE;    /* An overload, stop further  */
               }                              /* testing as low as repeating*/
            }
            else {
               TestKeyRepeat = FALSE;
               if (AETrigger == FALSE) {
                  if ((WeldingResults.OverloadAlarms & OL1) ==
                      (OL1 & ALARMCODEMASK) ) {
                     TestModeAllowed = FALSE; /* Test mode ok now, door is shut */
                  }
                  else {
                     TestModeAllowed = TRUE; /* Test mode ok now, door is shut */
                  }
               }
            }
            LastCycleTimer = SystemTimer;
            if ( ((GetReadyStatus() == TRUE) || (TestSonicsFlag == TRUE)) &&
                 (TestModeAllowed == TRUE) ) {
               if (HornDownFlag == TRUE || VGAHDAlarm || DownspeedTuneFlag == TRUE ||
            		   (EventReasonFlag == TRUE) || (VGAEstopLoginFlag == TRUE)) {
                  Beep(ERRORBEEP);
               }
               else if (!Get_GetMsgFlag())        
                  Beep(ERRORBEEP);
               else if (TestSonicsFlag == FALSE) {
                  SelectTestSequence();
                  TestSonicsFlag = TRUE;
                  StartTestFlag = TRUE;

                  /*If VGA H/W available send TestKey to vga queue*/
                  if(IsHWConfigured(VGA))
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = TestKey;
                     RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 20);
                  }
                  SendFakeKeyPress(TestKey);    /* Tell menu system ok      */
               }
               else {
                  switch (SonicsOnFlag) {

                     case TRUE:                 /* Sonics still on          */
                        TestTimerCounter = 0;               /* Reset timer                      */
                        break;

                     case FALSE:               /* Sonics gone off already  */
                        StartTestFlag = TRUE;
                        break;
                     default:
                        break;
                  }
               }
            }
            else {
               if (TestKeyRepeat == FALSE) /* Only beep if we cant get into */
                  {
                     Beep(ERRORBEEP);     /* test because of something besides */
                  }
            }                          /* overload.  This prevents multiple */
            break;                     /* beeps when the test key is held   */
                                       /* and there is an overload.         */

         case OP_RESET_KEY_PRESSED:
            if ((WeldState == READYSTATE) || (WeldState == PREREADYSTATE)) {
               if ( (CheckAlarmFlag() == TRUE) || (AlarmDetectedFlag == TRUE) ) {
                  BeepFlag = FALSE;      /* Start off assuming we will reset */
               }
               else BeepFlag = TRUE;

   /*---   First clear out alarms which can be reset   ---*/
               DownspeedTuneCycles = 0; //velocity calib counter

               if(SetupData.SetupErrorAlarms9 & BIT270)
                  CheckPrinterStatus = TRUE;
               ClearSetupAlarms();

               ClearWeldingResultsAlarms();
               ClearFinalResultsAlarms();

               ResetReceivedFlag = TRUE;
               TrigSwActv();                      /* safety circuit input            */
               TestModeAllowed = TRUE;

   /*---  Now see if any non-resetable alarms remain  ---*/

               if (ClearAlarm(FinalResults.EquipmentFailureAlarms) != TRUE) {
                  BeepFlag = TRUE;
               }

               if ((FinalResults.EquipmentFailureAlarms == 0) &&
                   (FinalResults.CalibrateAlarms == 0) &&
                   (AlarmDetectedFlag == TRUE) ) {
                  PSIdle();
                  PSReset();
                  AlarmDetectedFlag = FALSE;

/*--------------------------------------------------------------------------*/
/*  The Reset key was pressed while still in test mode.  Let's make it look */
/*  like the test mode has ended (at least look like the test key is no     */
/*  longer pressed and sonics have timed out).  To turn on sonics again the */
/*  test key must be pressed again.  This is to fix DCS # 2446.             */
/*--------------------------------------------------------------------------*/
                  if (TestSonicsFlag == TRUE) {
                     TestModeAllowed = FALSE;
                  }
                  ClearAlarmFlag();                 /* Clear Alarm flag */
                  ClearGeneralAlarm();              /* Remove GeneralAlarm,suspect,&reject signals*/
                  if((RunScreenFlag == TRUE) && (MenuCounter == 1))
                     SendFakeKeyPress(UPDATEDISPLAY);
                  AlarmOff();                       /* Turn off Reset led               */
               }
            }
            else
               BeepFlag = TRUE;
            if ((GetCurrentSequenceType() == HORNDOWN) && (HornDownFlag == TRUE))
            {
               ResetHDAlarms();
               BeepFlag = FALSE;
            }
            if (BeepFlag == FALSE)        /* By now, either beep or display   */
            {                             /* the Reset Complete message, we   */
                                          /* must do exactly one of them.     */
               if (RunScreenFlag)
                  SendFakeKeyPress(ResetKey);  /* If on RunScreen or submenu, */
                                               /* react on-screen to reset.   */
               ReadyAlreadySet = FALSE;
               CycleAbort = FALSE;
               if(VGAUSBOfflineFlag)
            	   AbortFlag = FALSE;
               AlarmDetectedFlag = FALSE;
               ClearAlarmFlag();        /* Clear Alarm flag                 */
               ClearGeneralAlarm();     /* Remove GeneralAlarm,suspect,&reject signals*/
               AlarmOff();              /* Turn off Reset led               */
            }
            else {
               Beep(ERRORBEEP);

/*----  Here we need to send Updated Alarm Data over to the System Manager  ----*/

               CountAlarms();
               AlarmCounter = TotalAlarmCount;   /* Carry this count into RecordAlarm       */
                                                 /* This allow reset to clear the counter   */
                                                 /* even if a cycle is not run.  DCS # 3544 */
               if (TotalAlarmCount != 0) {  /* Update to latest count if not 0 */
                  WeldDataMsg.common.opcode = OP_READ_ALARM_DATA;
                  SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldDataMsg), 10);
                  ResetFailed = TRUE;/*Used in Host command.*/
               }
            }
            VGAHistoryValidatedFlag = FALSE;
            VGAUSBOfflineFlag = FALSE;
            VGAUSBFullFlag = FALSE;
            ResetAlarmProcessed = TRUE;/*Used in Host command.*/
            break;

         case OP_MAIN_KEY_PRESSED:
            SendFakeKeyPress(MainKey);
            break;

         case OP_RUN_KEY_PRESSED:
            SendFakeKeyPress(RunKey);
            break;

         case OP_STOP_TEST:
            PSIdle();                    /* Turn off sonics              */
            TestTimerFlag = TRUE;        /* Advance state machine        */
            SelectWeldSequence();        /* Restore weld sequence        */
            StartStateMachine();         /* Start the state machine here */
            TestSonicsFlag = FALSE;      /* Clear flag to show test done */
            if (CheckIfResetRequired() == FALSE)
               SetReady();               /* Output Welder Ready signal   */
            break;

         case OP_POWERDOWN:         /* Received power switch is set to off  */
            break;

         case OP_CALIB_START:       /* Received when Calib/Diag selected from main menu */
            break;

         case OP_GOBACK_KEY_PRESSED:
            SendFakeKeyPress(GoBackKey);
            break;

         case OP_START_WELD_DATA:
            weld_data_flag =1;
            break;

         case OP_STOP_WELD_DATA:
            weld_data_flag = 0;
            break;

         case OP_HERE_IS_PRESET:
            /* return the buffer allocated by the SysManager task */
            PresetNeedsToBeUpdated = TRUE;
            FormatRunScreenTopLine();
/* If not ready do not update the running preset check the UpdateDispFlag
   on the next palm button pressed */
            break;

         case OP_WELDER_STATE_CHANGE:
            switch (WmgrMsg.WeldMsg.state) {

               case PREREADYSTATE:
                  if (DUPSChangePending == TRUE)
                     {                   
                     	DUPS_DownloadCurrPS(); /* download is pending always when we get here */
                     	DUPSChangePending = FALSE;
                     }
                  break;

               case READYSTATE:

                  break;

               case PBSTATE:
                  if((CurrentSetup.ExtPresets == TRUE) && (Inp.PresetCode != 0))
                  {
                     /* External Preset Changed*/
                     if(RecallExtPreset((UINT16)Inp.PresetCode, FALSE) == TRUE){ /* Preset Not Available Alarm */
                        PresetNeedsToBeUpdated = TRUE; /* need to verify the new preset */
                     }
                     else
                        ExternalPresetAlarm = TRUE;
                  }
                  else if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                           CurrentSetup.SequenceCount != 0)
                  {
                     NextPreset = (UINT16)CurrentSetup.SequenceList[CurrentSetup.SequenceNos];
                     if(RecallExtPreset(NextPreset, TRUE) == TRUE) /* Preset Not Available Alarm */
                        PresetNeedsToBeUpdated = TRUE; /* need to verify the new preset */
                     else
                        ExternalPresetAlarm = TRUE;
                  }
                  else if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                          CurrentSetup.SequenceCount == 0)
                  {
                     RecordSetupAlarm(SE299);
                     ExternalPresetAlarm = TRUE;
                  }
                  if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                           CurrentSetup.ExtPresets == TRUE)       //External Preset Enable
                  {
                     RecordSetupAlarm(SE297);
                     ExternalPresetAlarm = TRUE;
                  }
                 if (VGAUSBOfflineFlag)   // Check for USB offline
                 {
                    RecordAlarm(EQ27);
                   VGAUSBOfflineFlag = FALSE;
                   ExternalPresetAlarm = TRUE;
                 }
                 if (VGAHistoryValidatedFlag)
                 {
                	 RecordSetupAlarm(SE302);
                     VGAHistoryValidatedFlag = FALSE;
                     ExternalPresetAlarm = TRUE;
                 }

                 if(VGAUSBFullFlag)
                 {
                    RecordAlarm(EQ13);
                    VGAUSBFullFlag = FALSE;
                    ExternalPresetAlarm = TRUE;
                 }
                 if(VGADISKFullFlag)
                 {
                    RecordAlarm(EQ16);
                    VGADISKFullFlag = FALSE;
                    ExternalPresetAlarm = TRUE;
                  }

                  if (ExternalPresetAlarm == TRUE)
                  {
                     SendSetupData();           /* Notify display system of impending doom */
                     PresetHasBeenOKed = FALSE;
                     AlarmDetectedFlag = TRUE;
                     CountSetupAlarms();
                     ResetStateMachine();     /* Start back at ready     */
                     StartStateMachine();     /* Allows alarms every PB  */
                  }
                  else //(ExternalPresetAlarm == FALSE) No alarm so far
                  {
                     if(PresetNeedsToBeUpdated == TRUE)
                     {
                     UpdateRPreset();
                     }

                     if(AlarmDetectedFlag == TRUE){
                        AlarmDetectedFlag = FALSE;
                        AlarmOff();                       /* Turn off Reset led               */
                        ClearGeneralAlarm();              /* Remove GeneralAlarm,suspect,&reject signals*/
                        ClearWeldingResultsAlarms();
                        ClearFinalResultsAlarms();
                        if((RunScreenFlag == TRUE) && (MenuCounter == 1))
                           SendFakeKeyPress(UPDATEDISPLAY);
                     }

                     if (CheckVerifyPresetRequired() ) {
                        StopStateMachine();         /* Stop state machine      */
                        if ( VerifyPreset()==FALSE ) { /* CALL VERIFY PRESET      */
                           StartStateMachine();     /* Start state machine     */
                           UpdateFlag = FALSE;      /* Clear flag              */
                           VerifyPresetRequired = FALSE;
                        }
                        else {      /* Preset bad, what do we do now? */
                           ResetStateMachine();     /* Start back at ready     */
                           StartStateMachine();     /* Allows alarms every PB  */
                        }
                     }
                     //Check For Preset validation
                     if(CurrentPreset.Verified == TRUE){
                    	 if(CheckPresetValidation() == FALSE){
                    		 ResetStateMachine();     /* Start back at ready     */
                    		 StartStateMachine();     /* Allows alarms every PB  */
                    	 }
                     } 
                  }
                  PresetHasBeenOKed = TRUE;  /* Allow the state machine to advance */
                  break;

               case WAITFORPARTCLAMPINPUTSTATE:
                  break;

               case DOWNSTROKESTATE:
               case WAITFORPTSSTATE:
                  break;

               case TRIGGEREDSTATE:
                  if ((CurrentSequence == CALIBRATION) || (CurrentSequence == SC)) {

                     if(IsCalibGoingOn())
                     {
                        FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                        FPKeyMsg.key = VGACALIB_KEY;
                        RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 20);
                     }
                     else
                     {
                        if(CalibrationPassed == CAL_PASSED)
                           SendFakeKeyPress( Select3Key );  /* advance to pass screen */

                        else if(CalibrationPassed == CAL_FAILED)
                          SendFakeKeyPress( Select1Key );  /* advance to fail screen */
                     }
                  }
                  break;

               case EXTTRIGDELAYSTATE:
                  break;

               case TRIGGERDELAYSTATE:
                  break;

               case WELDTIMESTATE:
                  break;

               case ENDOFSONICS:
                  break;

               case HOLDTIMESTATE:
                  break;

               case PROCESSALARMSSTATE:
                  if(!DownspeedTuneFlag)//Avoid checking process alarms during tune cycles
                     CheckProcessLimits();
                  break;

               case AFTERBURSTTIMESTATE:
                  break;

               case AFTERBURSTDELAYSTATE:
                  break;

               case NOP:
               case TESTMODESTATE:
                  break;

               case WAITFORULSMADESTATE:
                  break;

               case SEEKSTATE:
                  break;

               case EMERGENCYSTOPRESET:
                  ActPowerUp();     /* Read current actuator settings */

                  /* Note: If there is no actuaor Novram, then ActPowerUp    */
                  /* will write some reasonable initial values to NVR.       */
                  /* Therefore, if CheckNvrValid() fails, it must be because */
                  /* it is processing data actually read from Novram, not    */
                  /* the "fake" information supplied by ActPowerUp().  It is */
                  /* therefore safe to conclude that we have an AED actuator.*/

                  if (((NVR.ActId==NVR_AED)||(NVR.ActId == NVR_AES) || (NVR.ActId==NVR_MICRO)|| (NVR.ActId==NVR_MICROC))
                       && (CurrentSetup.ControlLevel >= LEVEL_d)) {
                     if (!CheckNvrValid())
                     {
                        ActRecover(); /* Put something in there that makes sense */
                        RecordAlarm( EQ10 );  /* Actuator Novram */
                        RecordAlarm( EQ20 );  /* Recalibrate Actuator */
                     }

                     CheckForHornChange();    /* Is the horn weight different when returning */
                  }                           /* from EStop                                  */
                  ActuatorChanged = CheckForActChange();

                  if(CurrentSetup.Actuator != AE )
                     TrsDisabled();
                  else
                     TrsEnabled();

                  if ((CurrentSequence == CALIBRATION) || (CurrentSequence == SC))
                  {
                     SendFakeKeyPress(MainKey);   /* Tell menu system all done    */
                  }
                  else if (DUPSOkFlag == FALSE)
                     SendFakeKeyPress(GoBackKey);   /* exit hornscan menu    */
                 if(ClampOnAlarm == TRUE){
                	 PushIndex();
                	 SelectWeldSequence();        /* Then get out                 */
                	 PopIndex();
                 }
                 else
                	 SelectWeldSequence();        /* Then get out                 */
                  SVOff();                     /* Bring horn back home         */

              /* Don't go in ready state if VGA HW Present and not powered up.*/
              if((!WindowSetupFlag) && ((!CurrentSetup.VGAHWPresent)||((CurrentSetup.VGAHWPresent)&&(IsHWConfigured(VGA)))))
                 StartStateMachine();

                  if(HornDownFlag) {
                     AbortFlag = TRUE;
                     HornDownFlag = FALSE;
                     SendFakeKeyPress(MainKey);   /* Tell menu system all done    */
                  }
                  else if(TestSonicsFlag) {
                        PSIdle();               /* Turn off sonics          */
                        TestTimerFlag = TRUE;   /* Advance state machine    */
                        TestSonicsFlag = FALSE; /* Clear flag to show done  */
                        SendFakeKeyPress(MainKey);  /* Tell menu system all done    */
                  }
                  /* Send fake key 'MainKey' if User IO Menu is displayed. */
                  else if(WeldingStopInsideMenu)
                     SendFakeKeyPress(MainKey);
                  else if(UserIOAlarmMenu)
                     SendFakeKeyPress(RunKey);

                  else if(Get_GetMsgFlag() == FALSE)
                     SendFakeKeyPress(GoBackKey); /* Tell menu system all done    */
                  else
                     SendFakeKeyPress(UPDATEDISPLAY);  /* Tell menu system all done    */

                   /*If VGA H/W available send ESTOPMSGRESET to vga queue*/
                  if(IsHWConfigured(VGA))
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = ESTOPMSGRESET;
                     RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 20);
                  }
                  break;

               case WAITFORCONTINUE:
               case CALTIMERSTATE1:
               case CALTIMERSTATE2:
               case READA2D1STATE:
               case READA2D2STATE:
               case READA2D3STATE:
               case CALREADYSTATE:
                  break;

               case MENUSYNCSTATE:
               case SETCALPRESSURESTATEAES:
               case SETCALFORCESTATEAES:
                  break;
               case CONFIRMREJECTSTATE:
                   break;

               case UPDATEALARMSTATE:
                  FinalResults.EquipmentFailureAlarms = WeldingResults.EquipmentFailureAlarms;
                  FinalResults.RejectBitResult = WeldingResults.RejectBitResult;
                  FinalResults.SuspectBitResult = WeldingResults.SuspectBitResult;
                  FinalResults.NoCycleAlarms =  WeldingResults.NoCycleAlarms;
                  FinalResults.OverloadAlarms = WeldingResults.OverloadAlarms;
                  FinalResults.CycleModifiedAlarms = WeldingResults.CycleModifiedAlarms;
                  FinalResults.CalibrateAlarms = WeldingResults.CalibrateAlarms;
                  FinalResults.Warnings = WeldingResults.Warnings;

/*----  Here we need to send Updated Alarm Data over to the System Manager  ----*/

                  WeldDataMsg.common.opcode = OP_READ_ALARM_DATA;
                  SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldDataMsg), 10);
                  break;

               case FINALDATASTATE:
/*----  Get date and time so we can time stamp the weld data  ----*/
				  RTClock::GetCurrentTime(&RTCWeld);
                  FinalResults.CycleDate.day = RTCWeld.Day;
                  FinalResults.CycleDate.month = RTCWeld.Century_Month;
                  FinalResults.CycleDate.year = RTCWeld.Years;
                  FinalResults.CycleTime.hour = RTCWeld.Hour;
                  FinalResults.CycleTime.minute = RTCWeld.Minute;
                  FinalResults.CycleTime.second = RTCWeld.Second;

/*----  Load Final Data with current WeldMode, PresetNum & Preset Name. ----*/
                  FinalResults.Weldmode = RunningPreset.WeldMode;
                  FinalResults.PresetNum = CurrentSetup.ActivePreset;
                  strcpy(FinalResults.PresetName, RunningPreset.PresetID);
                  if(!RunningPreset.PresetUpdateComplete)
                     strcat(FinalResults.PresetName, "*");

/* Last, but not least, total cycle time... */
                  FinalResults.CycleTimeResult = TotalCycleTime;
                  strncpy(FinalResults.ActSerialNum, CurrentSetup.ActSerialNumber, sizeof(FinalResults.ActSerialNum) - 1);
                  strncpy(FinalResults.PsSerialNum, CurrentSetup.PSSerialNumber, sizeof(FinalResults.PsSerialNum) - 1);
                  /*----  Here we need to send Final Data over to the System Manager  ----*/

                  WeldDataMsg.common.opcode = OP_FINAL_WELD_DATA;
                  SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldDataMsg), 20);

                  if (!IsHWConfigured(VGA))
                  {
                     StopAtEndOfCycle();
                  }

                  switch (CurrentSetup.SerialPort) {
                    case ASCIICOMMA:
                      SendSerialPort(COMMA);
                      break;
                    case ASCIITAB:
                      SendSerialPort(TAB);
                      break;
                    case ASCIISPACE:
                      SendSerialPort(SPACE);
                      break;
                    case RS232DISABLED:
                    default:
                      // No code here, nothing to do!
                      break;
                  }

                  VGAWeldStartData = TRUE;

/*
 * Set trigger flag for DI
 */
                  DIComm2000Xc::FormatDateTime(DateTimeFormated, FinalResults.CycleDate, FinalResults.CycleTime);
                  DIComm2000Xc::SetTrigger(TRUE);
                  break;

               case WAITFORULSCLEARSTATE:
               case WAITFORTRSSTATE1:
               case WAITFORTRSSTATE2:
               case WAITFORTRSSTATE3:
               case WELDTIME2STATE:
               case RAMPSONICSSTATE:
               case POWERDOWNSTATE:
               default:
                  break;
               case EMERGENCYSTOP:
                  SVOff();                     /* Bring horn back home         */
                  PSIdle();                    /* Turn off sonics          */
                  CoolValOff();
                  /*If VGA H/W available send ESTOPMSGON to vga queue*/
                  if(IsHWConfigured(VGA))
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = ESTOPMSGON;
                     RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 20);
                  }
                  break;
            }
            break;

         default:
            break;
      } /* end switch (WmgrMsg.GenericMsg.common.opcode) */
   } /* end while */
} /* end of WeldManager task */

void FormatRunScreenTopLine(void)
/****************************************************************************/
/*                                                                          */
/* Creates the text that should appear on the top line of the run screen.   */
/* StrTopLine must be updated for all the languages                      */
/*                                                                          */
/****************************************************************************/
{
   SINT8 TempStr[LINESIZE+1];
   STR *TempStrTrim;
   SINT8 TempStr1[VGA_LINESIZE];
      switch (CurrentPreset.WeldMode)
      {
         case TIMEMODE:
            FormatStr2(TempStr, 0, NOCHAR, 2,
                    (CurrentPreset.WeldTime / 1000),
                     '.', 3, (CurrentPreset.WeldTime % 1000) );
            TempStr[LINESIZE] = 0;
            StrCpyTwoBytes(TempStr1, TempStr);
            TempStrTrim = Trim_FillChar(TempStr1);
            strncpy(StrWeldStateLine, TempStrTrim, sizeof(StrWeldStateLine) - 1);//Coverity 11297

            break;
         case ENERGYMODE:
            if(CurrentPreset.WeldEnergy < 10000)
               FormatStr2(TempStr, 0, NOCHAR, 4,
                         (CurrentPreset.WeldEnergy / 10),
                          '.', 1, (CurrentPreset.WeldEnergy % 10) );
            else
               FormatStr1(TempStr, 0, 5,
               (CurrentPreset.WeldEnergy / 10), NOCHAR);
            TempStr[LINESIZE] = 0;
            StrCpyTwoBytes(TempStr1, TempStr);
            TempStrTrim = Trim_FillChar(TempStr1);
            strncpy(StrWeldStateLine, TempStrTrim,sizeof(StrWeldStateLine)-1);
            break;
         case PKPOWERMODE:
            FormatStr2(TempStr, 0, NOCHAR,3, (CurrentPreset.PeakPwr/10),
                           '.', 1, (CurrentPreset.PeakPwr % 10) );
            TempStr[LINESIZE] = 0;
            StrCpyTwoBytes(TempStr1, TempStr);
            TempStrTrim = Trim_FillChar(TempStr1);
            strncpy(StrWeldStateLine, TempStrTrim, VGA_LINESIZE - 1);
            break;
         case COLLAPSEMODE:
            if ( (CurrentSetup.Actuator == AED)   ||
                 (CurrentSetup.Actuator == AES)   ||
				 (CurrentSetup.Actuator == MICRO) ||
                 (CurrentSetup.Actuator == MICROC) )
            {
               FormatVariables( CurrentPreset.ColDist, DISTANCE, TempStr,
               DIST_STR_SIZE, CurrentSetup.Units );
               TempStr[DIST_STR_SIZE] = 0;
               strcpy(StrWeldStateLine, TempStr);
            }
            else
            {
            	strcpy(StrWeldStateLine, "");
            }
            break;
         case ABSOLUTEMODE:
            if ( (CurrentSetup.Actuator == AED)   ||
                 (CurrentSetup.Actuator == AES)   ||
				 (CurrentSetup.Actuator == MICRO) ||
                 (CurrentSetup.Actuator == MICROC) )
            {
               FormatVariables( CurrentPreset.AbsDist, DISTANCE, TempStr,
               DIST_STR_SIZE, CurrentSetup.Units );
               TempStr[DIST_STR_SIZE] = 0;
               strcpy(StrWeldStateLine, TempStr);
            }
            else
            {
         strcpy(StrWeldStateLine, "");
            }
            break;
         case GRDDETECTMODE:
      strcpy(StrWeldStateLine, "");
            break;
         case CONTINUOUSMODE:
      strcpy(StrWeldStateLine, "");
            break;
         default:
      strcpy(StrWeldStateLine, "");
            break;
      }
}

void UpdateRPreset(void){
   PresetHasBeenOKed = FALSE;
   PresetNeedsToBeUpdated = FALSE;
   memcpy(&RunningPreset, &CurrentPreset, sizeof(RunningPreset) );
   UpdateFlag = TRUE;
   SetPressureValue = RunningPreset.WeldPressure;
   if(RunningPreset.TunedPreset == TRUE)  // Preset has been tuned use this
      SetFlowValue = RunningPreset.TunedFlowValue;
   else //Preset downspeed has been changed without tuning
      SetFlowValue = FlowLookup(CurrentPreset.Downspeed);

   if(PowerUpPresetReceived == TRUE)
      WeldingResults.CycleCount = RunningPreset.WeldCount;
   else{
      RunningPreset.WeldCount = WeldingResults.CycleCount;
      CurrentPreset.WeldCount = WeldingResults.CycleCount;
   }
}

void ClearWeldingResultsAlarms(void)
{
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.Warnings = 0;
   WeldingResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   WeldingResults.CycleModifiedAlarms = 0;
   WeldingResults.CalibrateAlarms &= CA_NO_RESET;
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
}

void ClearFinalResultsAlarms(void)
{
   FinalResults.NoCycleAlarms = 0;
   FinalResults.OverloadAlarms = 0;
   FinalResults.Warnings = 0;
   FinalResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   FinalResults.CycleModifiedAlarms = 0;
   FinalResults.CalibrateAlarms &= CA_NO_RESET;
   FinalResults.RejectBitResult = 0;
   FinalResults.SuspectBitResult = 0;
}

BOOLEAN CheckVerifyPresetRequired (void)
/****************************************************************************/
/*                                                                          */
/* This function returns TRUE if the preset needs to be verified and return */
/* FALSE if not needs to be verified.The function checks for the HwCnfg     */
/* and UserIO alarm conditions to verify preset again.                      */
/*                                                                          */
/****************************************************************************/
{
    BOOLEAN RetVal = FALSE;
    static UINT16 LastActivePreset = 0;
    static UINT16 LastActiveWeldMode = TIMEMODE;
    /* In case of Recall preset verify preset only if
        CurrentPreset.verified= FALSE */
    if(ResetRecall_UpdateFlag)
    {
        UpdateFlag = FALSE;
        ResetRecall_UpdateFlag = FALSE;
    }
    if(CurrentPreset.Verified)
    {
       /* Verify again if HwCnfg is changed or any of the UserIOAlarm condition is TRUE */
       if(RunningPreset.HwCnfg != GetCurrentHwCnfg() || (RunningPreset.ExtTrgDelay == TRUE &&
          !IsConfigured(INPUT_EXT_TRIGDELAY)) || (RunningPreset.EnergyBraking == TRUE &&
          CurrentSetup.AmpControl == FALSE))
       {
          CurrentPreset.Verified = FALSE;
          CurrentPreset.Validated = FALSE;
          CurrentPreset.Locked = FALSE;
       }
       /* Check for MissingPart alarm condition. */
       else if ( (CurrentSetup.Actuator == AED)   ||
                 (CurrentSetup.Actuator == AES)   ||
				 (CurrentSetup.Actuator == MICRO) ||
                 (CurrentSetup.Actuator == MICROC) )
       {
          if (IsOutConfigured(OUTPUT_MISSING_PART) && ((RunningPreset.CycleAbortFlag == FALSE) ||
              (RunningPreset.MissingPartFlag == FALSE) || (RunningPreset.MissingMinFlag &&
               RunningPreset.MissingMaxFlag) ))
          {
             CurrentPreset.Verified = FALSE;
             CurrentPreset.Validated = FALSE;
             CurrentPreset.Locked = FALSE;
          }
       }
    }

    if(RunningPreset.BatchFunction == TRUE)
    {
      if((UpdateFlag == FALSE) && (VerifyPresetRequired == FALSE) && (CurrentPreset.Verified == TRUE))
       UpdateOnBatchCountChange = TRUE;
      UpdateFlag = TRUE;
    }
   
   if (((UpdateFlag) && (CurrentSequence == WELD)) ||
      (CurrentPreset.Verified == FALSE) || VerifyPresetRequired )
      RetVal = TRUE; /* Preset Needs to Verify. */

/****    Fix for version 9.04    ****/

   if ((CurrentSetup.ActivePreset != LastActivePreset)||(RunningPreset.WeldMode != LastActiveWeldMode))  {
      LastActivePreset = CurrentSetup.ActivePreset;
      LastActiveWeldMode = RunningPreset.WeldMode;
      SelectWeldSequence();                     /* Create new weld sequence*/
      SetIndex(2);                         /* Bounce index back to ready   */
      StartStateMachine();                 /* Start the state machine here */
   }
   return(RetVal);
}

/*
 * This function checks for below in a verified preset
 * 1- required authority before running a cycle on a non validated preset.
 * 2- If Preset is already validate does it suppose to run on this system or came from else where.
 * returns TRUE if preset passes above two tests else returns FALSE.
 *
 */
BOOLEAN CheckPresetValidation()
{
	BOOLEAN RetVal = TRUE;
	//If Preset is not validated does the operator have authority to run it.
	if((CurrentPreset.Validated == FALSE) && (CheckOperatorAuthority(RunInvalidatedPreset) == FALSE))
	{
		RecordSetupAlarm(SE22);
		RetVal = FALSE;
	}
	//Verify PS assembly in the Validated preset
	if((CurrentPreset.Validated == TRUE) && ((CurrentSetup.HWVerify & PS_HW_VERIFY) == PS_HW_VERIFY))
	{
		if(strcmp(CurrentPreset.PSAssemblyNum, CurrentSetup.PSAssemblyNum)){//Mismatch
			RecordSetupAlarm(SE301);
			RetVal = FALSE;
		}
	}
	//Verify Actuator assembly in the Validated preset
	if((CurrentPreset.Validated == TRUE) && ((CurrentSetup.HWVerify & ACT_HW_VERIFY) == ACT_HW_VERIFY))
	{
		if(strcmp(CurrentPreset.ActAssemblyNum, CurrentSetup.ActAssemblyNum)){//Mismatch
			RecordSetupAlarm(SE301);
			RetVal = FALSE;
		}
	}
	//Verify Stack assembly in the Validated preset
	if((CurrentPreset.Validated == TRUE) && ((CurrentSetup.HWVerify & STACK_HW_VERIFY) == STACK_HW_VERIFY))
	{
		if(strcmp(CurrentPreset.StackAssemblyNum, CurrentSetup.StackAssemblyNum)){//Mismatch
			RecordSetupAlarm(SE301);
			RetVal = FALSE;
		}
	}
	return RetVal;
}

void FormatDataLine(STR *DataLine, WELD_DATA *Results, UINT16 Metric )
{
   /****************************************************************************/
   /*                                                                          */
   /* it send to the serial port the weld data information                     */
   /* with delimit special char                                                */
   /*                                                                          */
   /****************************************************************************/
   STR  RS232DataLineTmp[ASCIILENGTH];
   // add cycles
   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   sprintf(RS232DataLineTmp,"%8u",Results->CycleCount);
   strcpy(DataLine,RS232DataLineTmp);
   //add time
   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   sprintf(RS232DataLineTmp," %02u:%02u:%02u",Results->CycleTime.hour,Results->CycleTime.minute,Results->CycleTime.second);
   strcat(DataLine,RS232DataLineTmp);
   //add time
   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   if(Metric == TRUE){        //  european date
      sprintf(RS232DataLineTmp," %02u/%02u/%02u ",Results->CycleDate.day,Results->CycleDate.month,Results->CycleDate.year);
   }
   else{                //  american date
      sprintf(RS232DataLineTmp, " %02u/%02u/%02u ",Results->CycleDate.month,Results->CycleDate.day, Results->CycleDate.year);
   }
   strcat(DataLine,RS232DataLineTmp);

   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   FormatVariables(Results->ActualWeldTime,TIME,RS232DataLineTmp,6,Metric);
   strcat(DataLine,RS232DataLineTmp);

   if(CurrentSetup.ControlLevel > LEVEL_t){
	  memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
      FormatVariables(Results->PeakPower, PERCENTX10,RS232DataLineTmp,6,Metric);
      strcat(DataLine,RS232DataLineTmp);
      memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
      if(Results->TotalEnergy > ENERGYPOINT)
         FormatVariables(Results->TotalEnergy,ENERGYDIV10,RS232DataLineTmp,6,Metric);
      else
         FormatVariables(Results->TotalEnergy, ENERGY,RS232DataLineTmp,6,Metric);
      strcat(DataLine,RS232DataLineTmp);
   }

   if ( ( (CurrentSetup.Actuator == AED)  ||
          (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO)|| (CurrentSetup.Actuator == MICROC)) &&
          (CurrentSetup.ControlLevel >= LEVEL_d) ) {
	      memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables( Results->ActualTotalAbs,DISTANCE,RS232DataLineTmp,8,Metric);
          strcat(DataLine,RS232DataLineTmp);
          memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables( Results->ActualWeldCollapse,DISTANCE,RS232DataLineTmp,9,Metric );
          strcat(DataLine,RS232DataLineTmp);
          memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables( Results->ActualTotalCollapse,DISTANCE,RS232DataLineTmp,9,Metric );
          strcat(DataLine,RS232DataLineTmp);
          strcat(DataLine," ");
   }

   if ( ( (CurrentSetup.Actuator == AED)  ||
          (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO)|| (CurrentSetup.Actuator == MICROC)) &&
          (CurrentSetup.ControlLevel >= LEVEL_d) ) {
	      memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables(Results->TrigForce,FORCE,RS232DataLineTmp,6,Metric);
          strcat(DataLine,RS232DataLineTmp);
          memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables(Results->WeldForceEnd,FORCE,RS232DataLineTmp,6,Metric);
          strcat(DataLine,RS232DataLineTmp);
   }

   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   sprintf(RS232DataLineTmp," %+3d  ",Results->FrequencyChange);
   strcat(DataLine,RS232DataLineTmp);

   memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
   if((Results->PSActControlFlags & BIT0) == BIT0) // INT
      sprintf(RS232DataLineTmp, " %3u   ", Results->ActualAmplitudeStart);
   else
      sprintf(RS232DataLineTmp, " %3s ", "Ext");
   strcat(DataLine,RS232DataLineTmp);

   if(CurrentSetup.ControlLevel > LEVEL_e){
      if((Results->PSActControlFlags & BIT0) == BIT0) {    // INT
    	 memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
         if((Results->PSActControlFlags & BIT1) == BIT1){   // STEP
            sprintf(RS232DataLineTmp, "  %3u  ", Results->ActualAmplitudeEnd);
         } else {
            sprintf(RS232DataLineTmp, "  %3s  ", "n/a");
         }
         strcat(DataLine,RS232DataLineTmp);
      }
      else{
    	 memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
         sprintf(RS232DataLineTmp, "  %3s  ", "n/a");
         strcat(DataLine,RS232DataLineTmp);
      }
   }

   if ( (( (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO)|| (CurrentSetup.Actuator == MICROC)) &&
          (CurrentSetup.ControlLevel >= LEVEL_d))) {
	      memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
          FormatVariables( Results->ActualDownspeed, VELOCITY, RS232DataLineTmp, 6, Metric );
          strcat(DataLine,RS232DataLineTmp);
   }

   if (CurrentSetup.ControlLevel >= LEVEL_c) {
	  if(strcmp(Results->UserId,"N/A")!=0){
	     memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
         sprintf(RS232DataLineTmp," %s ",Results->UserId);
         strcat(DataLine,RS232DataLineTmp);
	  }
      if(CurrentSetup.UDIScan == ON){
    	 memset(RS232DataLineTmp,'\0',(UINT32)ASCIILENGTH);
         sprintf(RS232DataLineTmp," %s ",Results->UDIScan);
         strcat(DataLine,RS232DataLineTmp);
      }
   }

}

void SendSerialPort(UINT16 Delimit)
{
   /****************************************************************************/
   /*                                                                          */
   /* it send to the serial port the weld data information                     */
   /* with delimit special char                                                */
   /*                                                                          */
   /****************************************************************************/
   if (CurrentSetup.WelderAddrFlag == 0) // See if Welder ID is on
   {
   	 memset(RS232DataLine,0,(UINT32)ASCIILENGTH);
     sprintf(RS232DataLine,"%4u ",CurrentSetup.WelderAddrValue);
     SerialMessageQueue((UINT8*)RS232DataLine,ASCIILENGTH);
   }
   memset(RS232DataLine,0,(UINT32)ASCIILENGTH);
   FormatDataLine(RS232DataLine,&FinalResults,CurrentSetup.Units);
   RemoveExtraSpaces((UINT8*)RS232DataLine);
   strsub((SINT8*)RS232DataLine,SPACE,Delimit);
   SerialMessageQueue((UINT8*)RS232DataLine,strlen(RS232DataLine));
   SerialMessageQueue((UINT8*)CRLF,2);
}
