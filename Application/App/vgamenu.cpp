/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgamenu.cpp_v   1.29   Oct 10 2017 15:01:34   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgamenu.cpp_v  $
 * 
 *    Rev 1.29   Oct 10 2017 15:01:34   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.28   Jun 29 2017 14:32:44   RJamloki
 * change user level to Branson
 * 
 *    Rev 1.27   11 May 2016 12:07:36   RJamloki
 * Change function SendMenuPtrs for Executive or Supervisor when no user login if dongle connected
 * 
 *    Rev 1.26   30 Apr 2015 12:49:44   ygupta
 * Modified BottomMenuProcess function to cleanup Tunning screen variables in case of user is going to bottom menu from tunning screen through Alarm screen.
 * 
 *    Rev 1.25   30 Apr 2015 12:08:38   rjamloki
 * Setting HdParams to zero on bottom menu handler.
 * 
 *    Rev 1.24   16 Apr 2015 07:18:08   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.23   08 Apr 2015 13:47:00   AnPawar
 * Changes for Pressure Stepping
 * 
 *    Rev 1.22   01 Apr 2015 13:03:02   amaurya
 * change in function VGASendPollingData() to not display batch count on runresults screen if it is disabled.
 * 
 *    Rev 1.21   30 Mar 2015 05:32:04   rjamloki
 * RESPONSE_TYPE enum added in which all VGAPollingPointer values are defined.
 * 
 *    Rev 1.20   16 Mar 2015 06:16:02   rjamloki
 * Clearing Downspeed flags and temp hd parameters after estop reset
 * 
 *    Rev 1.19   11 Feb 2015 06:30:56   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.18   30 Jan 2015 08:11:20   amaurya
 * VGASendPollingData() changed to disply "please wait" message on downspeed cahnge.
 * 
 *    Rev 1.17   26 Jan 2015 20:07:50   rjamloki
 * Latching etsop pressed until reset. Sending nonzero polling pointer until estop is reset.
 * 
 *    Rev 1.16   05 Jan 2015 04:27:18   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.15   11 Dec 2014 08:41:20   AnPawar
 * changes for coldstart complete.
 * 
 *    Rev 1.14   28 Nov 2014 07:42:38   rjamloki
 * VGASendPollingData() changed.
 * 
 *    Rev 1.13   14 Nov 2014 10:29:42   AnPawar
 * HdmenuToTuning flag added for automated down speed tuning
 * 
 *    Rev 1.12   14 Nov 2014 05:27:32   rjamloki
 * automaion and operator level condition removed to allow in to the weld setup menu.
 * 
 *    Rev 1.11   10 Nov 2014 05:00:14   AnPawar
 * VGASendPollingData() , VGAPrintParameters() function changed. 
 * 
 *    Rev 1.10   20 Oct 2014 06:37:24   AnPawar
 * VGASendPollingData() function changed
 * 
 *    Rev 1.9   26 Sep 2014 03:11:10   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.8   11 Sep 2014 17:00:22   rjamloki
 * VGASendPolling data changed to assert event reason menu after estop reset if a reason is pending
 * 
 *    Rev 1.7   11 Sep 2014 11:11:26   rjamloki
 * Added Event reason bit in VGAPollingPointer
 * 
 *    Rev 1.6   05 Sep 2014 05:22:22   rjamloki
 * BasicExpert, Automation and Authority check disabled for control level lesser than c
 * 
 *    Rev 1.5   22 Aug 2014 07:04:46   rjamloki
 * Trigforce define changed
 * 
 *    Rev 1.4   18 Aug 2014 01:47:34   rjamloki
 * Added MICRO and AE support
 * 
 *    Rev 1.3   07 Aug 2014 15:48:40   tayars
 * Added changes for downspeed tuning and event reason.
 * 
 *    Rev 1.2   28 Jul 2014 12:57:12   rjamloki
 * Added clamp alarm bit in VAG Polling pointer
 * 
 *    Rev 1.1   09 Jul 2014 14:58:32   rjamloki
 * Added batch counters in polling response data.
 * 
 *    Rev 1.0   11 Jun 2014 13:21:26   rjamloki
 * Initial revision.
 * 
 *    Rev 1.11   27 May 2014 18:24:14   rjamloki
 * Sending Weld History Setup in Print Parameters
 * 
 *    Rev 1.10   27 May 2014 10:13:50   amaurya
 * Added WeldHistory setup in PrintParams
 * 
 *    Rev 1.9   21 May 2014 10:48:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:36:10   rjamloki
 * prevented display lock before user log in
 * 
 *    Rev 1.7   07 May 2014 10:39:26   rjamloki
 * Removed DigPotKey.
 * 
 *    Rev 1.6   21 Apr 2014 13:53:22   rjamloki
 * Weld sample data and usb flags added to code
 * 
 *    Rev 1.5   26 Mar 2014 12:29:44   rjamloki
 * printf removed from function VGASendPollingData()
 * 
 *    Rev 1.4   05 Mar 2014 13:56:40   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:50   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:46   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------     

     Module name:

        Filename: vgamenu.c

      Written by: JOY MD 
            Date: 04/17/2003 
        Language: "C"
     
 -------------------------------- DESCRIPTION --------------------------------


 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include <string.h>
#include "dups_api.h"
#include "digout.h"
#include "menu.h"
#include "menu5.h"
#include "display.h"
#include "opcodes.h"
#include "statedrv.h"
#include "selctkey.h"
#include "beep.h"
#include "param.h"
#include "ticks.h"
#include "state.h"
#include "sc.h"
#include "snsrcalb.h"
#include "ipsatype.h"
#include "command.h"
#include "rtclock.h"
#include "util.h"
#include "graphs.h"
#include "prsetprn.h"
#include "preset.h"
#include "inports.h"
#include "alarms.h"
#include "vga_uart.h"
#include "command.h"
#include "weldhold.h"
#include "mansensr.h"
#include "Events.h"
#include "menuhorn.h"
#include "RVTSHandlerTask.h"
#include "WeldManagerTask.h"
#include "FlowLookupTable.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define EXIT_HD        1   /* Causes exit from HD mode */
#define WELDCOLUMN_COUNT_3 3
#define WELDCOLUMN_COUNT_5 5
#define WELDCOLUMN_COUNT_6 6
#define WELDCOLUMN_COUNT_7 7
#define WELDCOLUMN_COUNT_8 8
#define WELDCOLUMN_COUNT_12 12
#define WELDCOLUMN_COUNT_13 13
#define WELDCOLUMN_COUNT_14 14
#define WELDCOLUMN_COUNT_15 15
#define WELDCOLUMN_COUNT_16 16
#define RTRIGFORCE 32
#define EQRECALIB_BIT 340
#define WARNINGALARM8_BIT 520

#define CM_NOT_REQ_RESET_EXCLUDE_CM1 (CM_NOT_REQ_RESET & 0xFFFFFFFD)
/*
 ------------------------------- GLOBAL DATA ---------------------------------
*/
/*                       (scope is global to ALL files)                     */

BOOLEAN IsGraphDataAvail = FALSE;    // Is new Graph Data is available to display.
BOOLEAN LastWeld = FALSE;            // IS there any weld staus needs to be refreshed.
                                     // in RUN_RESULT_SCREEN. 
BOOLEAN VGAEstopDisplay = FALSE;
UINT16 DisplayNextMenu = TRUE;       // If FALSE Don't display Next Menu just beep only.
MENU * VGACalibPointer;
BOOLEAN NextMenuFlag = FALSE;
BOOLEAN CSCompleteFlag = FALSE;
BOOLEAN ChkSumCompleteFlag = FALSE;
BOOLEAN StartCalibFlag=FALSE;
UINT16 ActType =0;
BOOLEAN VGAUSBFullStatus = FALSE;
BOOLEAN VGA_ScreenDiagFlag = FALSE;
/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UserID CurrentUser;
extern ESTOP_STATE EStopState;
extern BOOLEAN CalActErrorFlag;
extern UINT8 CheckPrinterStatus;
extern SINT32 StoreCycleCount;
extern BOOLEAN VGACalAllowed;
extern BOOLEAN VGASnsrCalibAllowed;
extern BOOLEAN VGAHDAlarm;
extern BOOLEAN StateMachineDisabled;
extern BOOLEAN VGATestKeyPressed;
extern BOOLEAN VGAEstopOn;
extern BOOLEAN VGAEstopOff;
extern BOOLEAN VGAEstopReset;
extern BOOLEAN VGACalibKey;
extern BOOLEAN VGACalAborted;
extern BOOLEAN VGADebugDataFlag;
extern BOOLEAN VGADigitalChoiceTestFlag;
extern BOOLEAN VGADigitalChoiceWaitFlag;
extern BOOLEAN VGAColdStartFlag;
extern BOOLEAN VGAColdStartErrorFlag;
extern BOOLEAN VGAActStartFlag;
extern BOOLEAN VGAActStartErrorFlag;
extern BOOLEAN VGARestoreColdStartFlag; 
extern BOOLEAN VGARestoreErrorFlag; 
extern BOOLEAN VGAOverwritePresetFlag;
extern BOOLEAN VGAOverwriteErrorFlag;
extern BOOLEAN VGACreateStartFlag;
extern BOOLEAN VGACreateStartErrorFlag;
extern BOOLEAN VGAChecksum;
extern BOOLEAN VGAWeldStartData;
extern INBITS Inp;
extern UINT16  LangIndex;              /*Language Index*/
extern UINT16  CalibrationPassed;
extern UINT16 DiagFlag;
extern UINT16 VGAAction;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN PresetStatusMenuFlag;

extern UINT16 EstopHistoryFlag;
/*VGA Host COmmand related variables*/
extern BUCMENU_1200 BUCMenuRAM;
extern BOOLEAN CurrentPresetParameterChanged;
extern BOOLEAN SystemParameterChgdFlag;
extern SINT32 DownspeedTuneCycles;
extern BOOLEAN DownspeedTuneFlag;
extern BOOLEAN DownspeedTuneFlagHD;
extern BOOLEAN DownSpeedSetFlag;
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

enum LEVEL AccessLevel = OPERATOR;
enum UDISCANSTATUS VgaUDiStatus = UDISCAN_OFF;
//Enum represents the values which WC send to SBC in VGAPollingPointer.
enum RESPONSE_TYPE {
	INVALID = -1,
	RESPONSE_NONE = 0x00000000,
	ESTOP_OFF = 0x01000000,
	ESTOP_PRESSED_CONT = 0x02000000,
	MSG_SCREEN = 0x03000000,
	MSG_NAK_SCREEN = 0x04000000,
	CALIB_START_FLAG_ON = 0x05000000,
	CALIB_START_FLAG_OFF = 0x06000000,
	ESTOP_PRESSED_FIRST = 0x07000000,
	RESET_KEY = 0x08000000,
	TESTKEYPRESSED = 0x09000000,
	CUR_PRESET_PARAM_CHANGED = 0x0A000000,
	CLAMP_ALARM = 0x0B000000,
	EVENT_REASON_FLAG = 0x0C000000,
	DOWNSPEED_NEW_FLAG = 0x0D000000 ,
	ESTORESET_LOGIN = 0x0E000000,
	DOWNSPEEDFLAG = 0x0F000000,
	DOWNSPEEDFLAG_MSG = 0x10000000,
	DOWNSPEED_NEW_HD_FLAG = 0x11000000,
	GET_SYSTEM_VAR = 0x40000000,
	CALIB_NEXT = 0x00000001,
	ESTOP_LOGIN_NEXT = 0x00000002,
	DISP_LOCK = 0x80000000,
	RESPONSETYPE_MASK = 0xFF000000,
	ESTOP_NONE = 0x20000000,//If estop is not reset yet then never send RESPONSE_NONE. Send this code instead.
};

/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES -----------------------
*/
void VGAExitTestSequence(void);


/* Alarms*/

/*Emergency stop functions*/
void  ExitMenuAndEnableWeld (void);

/*VGA Host Command Function prototype*/
UINT16 SendMenuPtrs(UINT8 * to);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void InitWeldParamOption(void);
void VGAProcessHornDownMsg (void);
void ClearPMCData(void);
void VGARequestActCal(void);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
UINT16 LangStrLen(SINT8 * str);
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
extern WELD_DATA       FinalResults;

/*
 ---------------------------------- CODE -------------------------------------
*/


void ProcessAlarmItems (UINT16 AlarmPosition)
/****************************************************************************/
/*Description:-                                                             */
/* This function processes the Alarm item.                                  */
/*Input Parameters:-                                                        */
/* ID: This is basically Bit position of alarm sent by SBC.                 */
/*Output:-                                                                  */
/*If condition fulfilled than NACKERROR with additional two parameters      */
/****************************************************************************/
{
       /* need to check if calibration is allowed before */
       /* updating the screen. ALARM type does not allow */
       /* a function to be run before menu is displayed  */

       if ((AlarmPosition == EQRECALIB_BIT/*&EQRecalibrateActuator*/) ||
           (AlarmPosition == WARNINGALARM8_BIT/*&WA8text*/))
       {
          VGARequestActCal();
       }
}

void BottomMenuProcess (void)
/****************************************************************************/
/*Description:-                                                             */
/* This function processes Bottom button press                              */
/*Input Parameters:-                                                        */
/* GlobalCommandID:  CommandID of the  Menu                                           */
/*Output:-                                                                  */
/* Bootom menu entry                                                        */
/* or NACKERROR with additional two parameters                              */
/****************************************************************************/
{
   PresetStatusMenuFlag = FALSE;
   StartingSensorCal = FALSE;
   if (GlobalCommandID == RUN_MENU) //VGARunMenu
         AccessLevel = OPERATOR;
   else if (GlobalCommandID == MAIN_MENU) //VGATheMainMenu
         AccessLevel = OPERATOR;
   else if (GlobalCommandID == WELDMODE_MENU) //WeldModeSelectMenu
   {
      if((Inp.DisplayLockFlag) && (UserLoggedIn == TRUE))
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_MAIN_MENU;
         ErrorResponseMaxLimit = 0;
      }
      else if((CurrentSetup.PassWordFlag & BIT0) && (AccessLevel < MAINTENANCE))
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_SCREEN;
         ErrorResponseMaxLimit = 0;
      }
   }     
   else if (GlobalCommandID == GRAPH_MENU) //GraphMenu
         AccessLevel = OPERATOR;
         
   if ((GlobalCommandID == MAIN_MENU) ||
        (GlobalCommandID == WELDMODE_MENU) ||
        (GlobalCommandID == GRAPH_MENU)||
        (GlobalCommandID == RUN_MENU))
   {     
      DiagFlag = FALSE;    //Disable diagnostics
      if(VGACalAllowed)
         SCFinalCleanup();
      else if(VGASnsrCalibAllowed)
         CalibFinalCleanup();   
             /*If we are in TEST sequence Exit from there*/
      if(CurrentSequence == TESTMODE)
      {
         VGAExitTestSequence();
         //SendFakeKeyPress(GoBackKey);
      }
      if(!DUPSOkFlag)
         EnableWelding();
      /* Reset the state machine and keymask when exit from UserIOMenu. */ 
      if(StateMachineDisabled)
         ExitMenuAndEnableWeld();            
      if (VGAHornDown)   
      {
         VGAAction = EXIT_HD;
         VGAProcessHornDownMsg();
         if(EventReasonFlag)
        	 VGAEventReasonFlag = TRUE;
      }
      memset(&HdParams, 0 , sizeof(HdParams));
      if(DownspeedTuneFlag)
      {
    	  if(DownspeedTuneFlagHD)
    		  ExitDownSpeedTuneHD();
    	  else
    		  ExitDownSpeedTune();
    	  DownspeedTuneCycles = 0;
    	  DownspeedTuneFlag = FALSE;
    	  DownspeedTuneFlagHD = FALSE;
      }
   }   
}

UINT16 AddToBuffer(UINT8 * * to, SINT8 byte)
/****************************************************************************/
/*Description:-                                                             */
/* This function writes a byte to the buffer                                */
/*Input Parameters:-                                                        */
/* to:  Address of the buffer                                               */
/* byte: Value to be written                                                */
/*Output:-                                                                  */
/* Length of the byte                                                       */
/****************************************************************************/
{
	UINT8 * ptr = *to;
	*ptr++ = byte;
	*to = ptr;
	return sizeof(byte);
}

UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length)
/****************************************************************************/
/*Description:-                                                             */
/* This function writes specified number of bytes from the start of string  */
/* to the buffer                                                            */                                                   
/*Input Parameters:-                                                        */
/* to:  address of the buffer                                               */  
/* string:                                                                  */
/* length: Length of the bytes to be written                                */                                
/*Output:-                                                                  */
/* Length of the bytes written                                              */
/****************************************************************************/
{
	UINT16 i;
	for (i = 0; i < length; i++)
		AddToBuffer(to, *string++);
	return length;
}

void ClearPMCData(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function clears Power match curve data                              */
/****************************************************************************/
{
   UINT16 i;
   StoreCycleCount = 0;
   CurrentPreset.PMCCycleCount = 0;
   for (i = 0; i < PMCDATAPOINTS; i++){
      CurrentPreset.PMCData[i] = 0xFF;
   }
}

UINT16 SendMenuPtrs(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* This function sends Language, start screen, Unit, Time & Date and Bottom */
/* Menu pointers in response to 1000 command from SBC                       */
/*Input Parameters:-                                                        */
/* to:  buffer where data is to be written                                  */
/*Returns length of the bytes written to the buffer                         */
/****************************************************************************/
{
   RTCTime Welder_Clock;

   UINT16 length, i;		// length of data in output buffer
   UpdateHWConfiguration(VGA, TRUE);

   CurrentSetup.VGAHWPresent = TRUE;    //VGA HW detected
   //StartStateMachine();                 //Start State machines

   InitWeldParamOption();
   length = 0;
   length += AddToBuffer(&to, (UINT8) LangIndex);   //Language
   if (CurrentSetup.StartScreen)
      length += AddToBuffer(&to, 1);   //Run Screen
   else
      length += AddToBuffer(&to, 0);   //Main Screen
   if (CurrentSetup.Units)
      length += AddToBuffer(&to, 1);   //Metric Units
   else
      length += AddToBuffer(&to, 0);   //English Units
   RTClock::GetCurrentTime(&Welder_Clock);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Hour);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Minute);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Second);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Century_Month);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Day);
   length += AddToBuffer(&to, (UINT8) Welder_Clock.Years);
   for (i = 1; i <= 16; i++)
      length += AddToBuffer(&to, 0);   //English Units

   if (CurrentSetup.ControlLevel < LEVEL_c) {
      CurrentSetup.BasicExpert = EXPERT;
      CurrentSetup.Automation = OFF;
      CurrentSetup.AuthorityCheck = FALSE;
   }

   if (CurrentSetup.AuthorityCheck == FALSE) {
      //no need for login set current user to ?
      strcpy(CurrentUser.UserId, "N/A");
      if (CheckForAuthorityCheckDisable()==FALSE)
      {
    	CurrentUser.UserLevel = BRANSON;
      }
      else{
        CurrentUser.UserLevel = EXECUTIVE;
      }
      CurrUserOpAuth =(OpAuth)0;
      CurrentUser.Status = Enabled;
      CurrentUser.PassExpTime = MAX_PASSEXPTIME;   //Set default to maximum
      UserLoggedIn = TRUE;
   }
   else if (CurrentSetup.Automation == ON) {
      UserLoggedIn = TRUE;
      strncpy(CurrentUser.UserId, AutomationUsrId, sizeof(CurrentUser.UserId) - 1);
   }
   return length;
}

void MoveToNextCalibMenu(void)
/***************************************************************************/
/*Description:                                                             */
/* brings next calibration Screen depends on the calibration status.       */
/***************************************************************************/
{
   if(CalibrationPassed == CAL_PASSED)
      StartCalibFlag=TRUE;
   else
   {
      if(CalActErrorFlag)
         SCFinalCleanup();
      StartCalibFlag=FALSE;
   } 
}


UINT16 ExitHDForResetRequiredAlarms(void)
/****************************************************************************/
/*                                                                          */
/* This function will check to see if a reset is required.  If a reset is   */
/* required then a TRUE will be returned, otherwise a FALSE will be         */
/* returned.                                                                */
/*                                                                          */
/****************************************************************************/
{
	UINT16 ResetRequiredFlag = FALSE;          /* Assume reset not required */

	/*---  Here, check alarms which always require reset  ---*/

	if ( ((FinalResults.OverloadAlarms & OL_RESET) != 0) ||
	   ((FinalResults.EquipmentFailureAlarms & EQ_NO_RESET) != 0) ||
	   ((FinalResults.EquipmentFailureAlarms & EQ_RESET) != 0) ||
	   ((FinalResults.CalibrateAlarms & CA_NO_RESET) != 0) ) {
	 ResetRequiredFlag = TRUE;         
	}
	if(ResetRequiredFlag == FALSE)
	{

	/*--  Check alarms which require reset only if Reset Required = On  --*/

		if (RunningPreset.GeneralAlarmLFlag == TRUE) {   /* See if globally required */
			if ( ((FinalResults.NoCycleAlarms & NC_NOT_REQ_RESET) != 0) ||
				((FinalResults.OverloadAlarms & OL_NOT_REQ_RESET) != 0) ||
				((FinalResults.EquipmentFailureAlarms & EQ_NOT_REQ_RESET) != 0) ||
				((FinalResults.CycleModifiedAlarms & CM_NOT_REQ_RESET_EXCLUDE_CM1) != 0) ||
				(FinalResults.RejectBitResult != 0) ||
				(FinalResults.SuspectBitResult != 0) ||
				(FinalResults.CalibrateAlarms != 0)) {
				ResetRequiredFlag = TRUE;
			}
		}
		if((FinalResults.CycleModifiedAlarms & CM15) == (CM15 & ALARMCODEMASK))
			ResetRequiredFlag = TRUE;
	}
   return(ResetRequiredFlag);
}

UINT16 VGASendPollingData(UINT8 * to)
/****************************************************************************/
/*Description:- Reply to the polling command                                */
/****************************************************************************/
{
    UINT16 length = 0;		// length of data in output buffer
    UINT32 VGAPollingPointer = 0;
    UINT32 SetBatchCount = 0;
    static UINT16 PreviousAlarmCount = 0;
    static SINT32 EventReasonAssertCount = 0;
    static BOOLEAN LatchVagEstop = FALSE;
    if (!IsHWConfigured(VGA))
    {
       UpdateHWConfiguration(VGA, TRUE); 
       InitWeldParamOption();
    }
  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>24)); 	  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>16));	  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>8));	  
    length += AddToBuffer(&to, (UINT8)(CurrentPreset.WeldCount));	  

    length += AddToBuffer(&to, (UINT8)((FramVerInfo.PollingCommandCounter)>>24)); 	  
    length += AddToBuffer(&to, (UINT8)((FramVerInfo.PollingCommandCounter)>>16));	  
    length += AddToBuffer(&to, (UINT8)((FramVerInfo.PollingCommandCounter)>>8));	  
    length += AddToBuffer(&to, (UINT8)(FramVerInfo.PollingCommandCounter));	  

    CheckPrinterStatus = FALSE;	  
    length += AddToBuffer(&to, (UINT8)(CurrentSetup.ActivePreset >> 8));
    length += AddToBuffer(&to, (UINT8)(CurrentSetup.ActivePreset));
    length += AddToBuffer(&to, (UINT8)((TotalAlarmCount)>>8));	  
    length += AddToBuffer(&to, (UINT8)(TotalAlarmCount));	  
    length += AddToBuffer(&to, (UINT8)(VGAWeldStartData));
    VGAWeldStartData = FALSE;	  
    
	if (((VGAHornDown) && (TotalAlarmCount > PreviousAlarmCount ))||(VGAHDAlarm == TRUE)){
		VGAHDAlarm = FALSE;
		if(ExitHDForResetRequiredAlarms() == TRUE){
			VGAPollingPointer = VGAPollingPointer | RESET_KEY;
		}
	}


	PreviousAlarmCount = TotalAlarmCount;
    if(Inp.DisplayLockFlag && (UserLoggedIn == TRUE))
       VGAPollingPointer = VGAPollingPointer | DISP_LOCK;
    else
       VGAPollingPointer = VGAPollingPointer | RESPONSE_NONE;

    if(SystemParameterChgdFlag)  /*check for control level or actuator change*/
    {
       SystemParameterChgdFlag =FALSE;
       VGAPollingPointer = VGAPollingPointer | GET_SYSTEM_VAR;
    }
    else
       VGAPollingPointer = VGAPollingPointer | RESPONSE_NONE;

    if (VGATestKeyPressed)
    {
       VGATestKeyPressed = FALSE;
       VGAPollingPointer = VGAPollingPointer | TESTKEYPRESSED;
    }
    else if (VGAEstopOn)
    {
       VGAEstopOn = FALSE;
       VGAEstopLoginFlag = FALSE;//If estop pressed during etsop reset login screen then ignore unitl next reset
       LatchVagEstop = TRUE;
       DownSpeedSetFlag = FALSE;
       if(EStopState == ESTOPBTN_PRESSED)
         VGAPollingPointer = VGAPollingPointer | ESTOP_PRESSED_FIRST;
       else
         VGAPollingPointer = VGAPollingPointer | ESTOP_PRESSED_CONT;

    }
    else if (VGAEstopOff)
    {
       VGAEstopOff = FALSE;
       VGAPollingPointer = VGAPollingPointer | ESTOP_OFF;
    }
    else if (VGAEstopReset)
    {
       VGAEstopReset = FALSE;
       if(UserLoggedIn && (CheckOperatorAuthority(ResetAlarm) == FALSE))
       {
    	   VGAEstopLoginFlag = TRUE;
    	   VGAPollingPointer |= ESTOP_LOGIN_NEXT;//let sbc know that in next poll it will receive estop login screen indication
    	   StopStateMachine();
       }
       LatchVagEstop = FALSE;
       //Restore the original preset values those were saved before going into Down speed Tune screen.
       if(DownspeedTuneFlag)
    	   PushPopPresetValues(FALSE);
       DownspeedTuneFlag = DownspeedTuneFlagHD = FALSE;

       StartingSensorCal = FALSE;
       memset(&HdParams, 0, sizeof(HdParams));
       VGAPollingPointer = VGAPollingPointer | RESET_KEY;
       if(EventReasonFlag)//In next poll again assert the reason popup
    	   VGAEventReasonFlag = TRUE;
    }
    else if((ClampOnAlarm == TRUE)&&(Inp.Estop == FALSE)&&(EstopHistoryFlag == FALSE))
    	VGAPollingPointer = VGAPollingPointer | CLAMP_ALARM;
    else if(VGAEstopLoginFlag)
    {
    	VGAPollingPointer = VGAPollingPointer | ESTORESET_LOGIN;
    }
    else if (VGACalibKey)
    {
       VGACalibKey = FALSE;
       MoveToNextCalibMenu();
       if ( (CurrentSetup.Actuator == AED)||
             (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
          VGAPollingPointer = VGAPollingPointer | CALIB_NEXT ;
       else
          VGAPollingPointer = VGAPollingPointer | RESPONSE_NONE;

       if(StartCalibFlag)
       {
         VGAPollingPointer = VGAPollingPointer | CALIB_START_FLAG_ON;
       }
       else
       {
         VGAPollingPointer = VGAPollingPointer | CALIB_START_FLAG_OFF;
       }
    }
    else if (VGACalAborted)
    {
       VGACalAborted = FALSE;
       VGACalAllowed = FALSE;
       VGASnsrCalibAllowed = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       NextMenuFlag=TRUE;
    }
    else if (VGADebugDataFlag)
    {
       VGADebugDataFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if (VGADigitalChoiceWaitFlag)
    {
       VGADigitalChoiceWaitFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if (VGADigitalChoiceTestFlag)
    {
       VGADigitalChoiceTestFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if(NextMenuFlag)
    {
      NextMenuFlag = FALSE;
      VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if(ChkSumCompleteFlag)
    {
       ChkSumCompleteFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if(CSCompleteFlag)
    {
       CSCompleteFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if (VGAColdStartFlag)
    {
       VGAColdStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
    }
    else if (VGAColdStartErrorFlag)
    {
       VGAColdStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | MSG_NAK_SCREEN;
    }
    else if (VGAActStartFlag)
    {
       VGAActStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       CSCompleteFlag = TRUE;
    }
    else if (VGAActStartErrorFlag)
    {
       VGAActStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | MSG_NAK_SCREEN;
    }
    else if (VGARestoreColdStartFlag)
    {
       VGARestoreColdStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       CSCompleteFlag = TRUE;
    }
    else if (VGARestoreErrorFlag)
    {
       VGARestoreErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | MSG_NAK_SCREEN;
    }
    else if (VGAOverwritePresetFlag)
    {
       VGAOverwritePresetFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       CSCompleteFlag = TRUE;
    }
    else if (VGAOverwriteErrorFlag)
    {
       VGAOverwriteErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | MSG_NAK_SCREEN;
    }
    else if (VGACreateStartFlag)
    {
       VGACreateStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       CSCompleteFlag = TRUE;
    }
    else if (VGACreateStartErrorFlag)
    {
       VGACreateStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | MSG_NAK_SCREEN;
    }
    else if (VGAChecksum)
    {
       VGAChecksum = FALSE;
       VGAPollingPointer = VGAPollingPointer | MSG_SCREEN;
       CSCompleteFlag = TRUE;
    }
    else if(DownSpeedChanged && CurrentSetup.DownspeedTune)
    {
    	if(DownSpeedChangedHd)
    		VGAPollingPointer = VGAPollingPointer | DOWNSPEED_NEW_HD_FLAG;
    	else
    		VGAPollingPointer = VGAPollingPointer | DOWNSPEED_NEW_FLAG;
    	DownSpeedChanged = FALSE;
    	DownSpeedChangedHd = FALSE;
    }
    else if(CurrentPresetParameterChanged)
    {
       CurrentPresetParameterChanged = FALSE;
       VGAPollingPointer = VGAPollingPointer | CUR_PRESET_PARAM_CHANGED;
    }
    else if((VGAEventReasonFlag==TRUE) && (VGAHornDown == FALSE) && (DownspeedTuneFlag == FALSE))
    {
    	VGAEventReasonFlag = FALSE;
    	EventReasonAssertCount = 2;//After an event is occurred which requires reason below bit in VGAPollingPointer
    	    	//is set. This var keeps the number of polling commands minus one we want to keep this bit set. This
    			//is done to make sure that event reason popup doesn't miss.
    	VGAPollingPointer = VGAPollingPointer | EVENT_REASON_FLAG;
    }
    else if(EventReasonAssertCount > 0)
    {
    	VGAPollingPointer = VGAPollingPointer | EVENT_REASON_FLAG;
    	EventReasonAssertCount--;
    }
    else if(DownSpeedSetFlag)
    {
    	VGAPollingPointer = VGAPollingPointer | DOWNSPEEDFLAG;
    	if(SetFlowValue != FlowReadValue)
    		DownSpeedSetFlag = TRUE;
    	else
    	{
    		DownSpeedSetFlag = FALSE;
    		DSdone = TRUE;
    	}
    }
    else if(DSdone == TRUE )
    {
    	DSdone = FALSE;
    	VGAPollingPointer = VGAPollingPointer | DOWNSPEEDFLAG_MSG;
    }

    if((LatchVagEstop == TRUE) && ((VGAPollingPointer & RESPONSETYPE_MASK) == RESPONSE_NONE))
       VGAPollingPointer = VGAPollingPointer | ESTOP_NONE;
   length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>24));
   length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>16));
   length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>8));
   length += AddToBuffer(&to, (UINT8)(VGAPollingPointer));

   length += AddToBuffer(&to, (UINT8)((FRAMEventHistoryObj.EventHistoryCount)>>24));
   length += AddToBuffer(&to, (UINT8)((FRAMEventHistoryObj.EventHistoryCount)>>16));
   length += AddToBuffer(&to, (UINT8)((FRAMEventHistoryObj.EventHistoryCount)>>8));
   length += AddToBuffer(&to, (UINT8)(FRAMEventHistoryObj.EventHistoryCount));

      if(CurrentPreset.BatchFunction)
    	  SetBatchCount = CurrentPreset.BatchCount;

   length += AddToBuffer(&to, (UINT8)((SetBatchCount)>>24));
   length += AddToBuffer(&to, (UINT8)((SetBatchCount)>>16));
   length += AddToBuffer(&to, (UINT8)((SetBatchCount)>>8));
   length += AddToBuffer(&to, (UINT8)(SetBatchCount));

   length += AddToBuffer(&to, (UINT8)((CurrentPreset.CurrBatchCount)>>24));
   length += AddToBuffer(&to, (UINT8)((CurrentPreset.CurrBatchCount)>>16));
   length += AddToBuffer(&to, (UINT8)((CurrentPreset.CurrBatchCount)>>8));
   length += AddToBuffer(&to, (UINT8)(CurrentPreset.CurrBatchCount));

   length += AddToBuffer(&to,  (UINT8)((VgaUDiStatus)>>24));
   length += AddToBuffer(&to, (UINT8)((VgaUDiStatus)>>16));
   length += AddToBuffer(&to, (UINT8)((VgaUDiStatus)>>8));
   length += AddToBuffer(&to, (UINT8)(VgaUDiStatus));

   return length;
}


UINT16 VGAPrintParameters(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA print param to the SBC                                          */
/****************************************************************************/
{
   UINT16 length = 0;
   if(CurrentSetup.ExtPresets == TRUE)  // External preset enabled byte
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   if(CurrentSetup.USBGlobalFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   length += AddToBuffer(&to, (UINT16) strlen(CurrentSetup.PSSerialNumber));
   length += AddToBufferString(&to,  CurrentSetup.PSSerialNumber,strlen(CurrentSetup.PSSerialNumber));
   
   length += AddToBuffer(&to, (UINT16) strlen(CurrentSetup.ActSerialNumber));
   length += AddToBufferString(&to,  CurrentSetup.ActSerialNumber,strlen(CurrentSetup.ActSerialNumber));
   
   length += AddToBuffer(&to, (UINT16) strlen(CurrentSetup.BarcodeStart));
   length += AddToBufferString(&to,  CurrentSetup.BarcodeStart,strlen(CurrentSetup.BarcodeStart));

   /* USB weld data Sample Value*/
   if((CurrentSetup.USBWDSampleFlag & /*USBWeldDataSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBWDSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Weld data Alarm Flag*/
   if (CurrentSetup.USBWDAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Power Graph Sample Value*/
   if((CurrentSetup.USBPGSampleFlag & /*USBPowerSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBPGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Power Graph Alarm Flag*/
   if (CurrentSetup.USBPGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Col. Distance Graph Sample Value*/
   if((CurrentSetup.USBCDGSampleFlag & /*USBDistanceSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBCDGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Col. Distance Graph Alarm Flag*/
   if (CurrentSetup.USBCDGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Velocity Graph Sample Value*/
   if((CurrentSetup.USBVGSampleFlag & /*USBVelocitySample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBVGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Velocity Graph Alarm Flag*/
   if (CurrentSetup.USBVGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Force Graph Sample Value*/
   if((CurrentSetup.USBFGSampleFlag & /*USBForceSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBFGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Force Graph Alarm Flag*/
   if (CurrentSetup.USBFGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Amplitude Graph Sample Value*/
   if((CurrentSetup.USBAGSampleFlag & /*USBAmplitudeSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBAGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Amplitude Graph Alarm Flag*/
   if (CurrentSetup.USBAGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB Freq. Graph Sample Value*/
   if((CurrentSetup.USBFreqGSampleFlag & /*USBFreqSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>24));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>16));
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>8));
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBFreqGSampleValue));
   }
   else
   {
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
      length += AddToBuffer(&to, 0);
   }
   /*USB Freq. Graph Alarm Flag*/
   if (CurrentSetup.USBFreqGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   length += AddToBuffer(&to, (UINT8)((CurrentSetup.WeldHistSetup)>>24));
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.WeldHistSetup)>>16));
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.WeldHistSetup)>>8));
   length += AddToBuffer(&to, (UINT8)(CurrentSetup.WeldHistSetup));
   return (length);
}

UINT16 VGAPrintGraphInfo(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA Weld data column ID and Misc Notes section for printing graphs */
/****************************************************************************/
{
   UINT16 length = 0;
   if(CurrentSetup.ControlLevel == LEVEL_t)
      length += AddToBuffer(&to, 0);
   else
   if(CurrentSetup.ControlLevel == LEVEL_e)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_7);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      
   }
   else /*--  WITH AED --*/ 
   if (((CurrentSetup.ControlLevel == LEVEL_d) || (CurrentSetup.ControlLevel == LEVEL_c)) &&
        ((CurrentSetup.Actuator == AED) ||
          (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)))
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RTABSDIST);
      length += AddToBuffer(&to, RWCOLDIST);
      length += AddToBuffer(&to, RTCOLDIST);
      length += AddToBuffer(&to, RTRIGFORCE);
      length += AddToBuffer(&to, RFORCE);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
      if ( (CurrentSetup.Actuator == AED)||
            (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         length += AddToBuffer(&to, RVELOCITY_AED);
   }
   else 
   if(CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
   {
      if ( (CurrentSetup.Actuator == AED)||
            (CurrentSetup.Actuator == AES)  || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQSTART);
         length += AddToBuffer(&to, RFREQEND);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AED);
      }
      else if(CurrentSetup.Actuator == AE)
	  {
		 length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
		 length += AddToBuffer(&to, RTIME);
		 length += AddToBuffer(&to, RPKPWR);
		 length += AddToBuffer(&to, RENERGY);
		 length += AddToBuffer(&to, RFREQSTART);
		 length += AddToBuffer(&to, RFREQEND);
		 length += AddToBuffer(&to, RFREQCHG);
		 length += AddToBuffer(&to, RAMPSTART);
		 length += AddToBuffer(&to, RAMPEND);
	  }
   }
   else /*--  WITHOUT ENCODER --*/ 
   if(CurrentSetup.ControlLevel == LEVEL_ea)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else /*--  WITHOUT ENCODER --*/ 
   if ( ((CurrentSetup.ControlLevel == LEVEL_d) || (CurrentSetup.ControlLevel == LEVEL_c)) &&
        ( (CurrentSetup.Actuator != AED) ||
          (CurrentSetup.Actuator != AES) || (CurrentSetup.Actuator != MICRO) || (CurrentSetup.Actuator != MICROC)) )
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else
   {
      length += AddToBuffer(&to, 0);
   }
   return(length);
}

UINT16 VGAWeldDataInfo(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Prepares VGA Weld Column IDs to be seen on Print summary and history scrn*/
/****************************************************************************/
{
   UINT16 length = 0;
   
   if(CurrentSetup.ControlLevel == LEVEL_t)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_3);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
   }
   else
   if(CurrentSetup.ControlLevel == LEVEL_e)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_5);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
   }
   else /*--  WITH ENCODER --*/ 
   if(((CurrentSetup.ControlLevel == LEVEL_d) || (CurrentSetup.ControlLevel == LEVEL_c))&&
      ((CurrentSetup.Actuator == AED)||
       (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC)))
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_12);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RTABSDIST);
      length += AddToBuffer(&to, RWCOLDIST);
      length += AddToBuffer(&to, RTCOLDIST);
      length += AddToBuffer(&to, RTRIGFORCE);
      length += AddToBuffer(&to, RFORCE);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
      if ( (CurrentSetup.Actuator == AED) ||
            (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
         length += AddToBuffer(&to, RVELOCITY_AED);
   }
   else
   if(CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
   {
      if ( (CurrentSetup.Actuator == AED) ||
            (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_12);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AED);
      }
      else if(CurrentSetup.Actuator == AE)
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
      }
   }
   else 
   if(CurrentSetup.ControlLevel == LEVEL_ea)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else /*--  WITHOUT ENCODER --*/ 
   if ( ((CurrentSetup.ControlLevel == LEVEL_d) || (CurrentSetup.ControlLevel == LEVEL_c)) &&
        ( (CurrentSetup.Actuator != AED) ||
          (CurrentSetup.Actuator != AES) || (CurrentSetup.Actuator != MICRO) || (CurrentSetup.Actuator != MICROC)))
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else
   {
      if (BUCMenuRAM.VelocityReporting == TRUE) {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RPRESSUREA);
         length += AddToBuffer(&to, RPRESSUREB);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AEF);
      }
      else {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_13);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RPRESSUREA);
         length += AddToBuffer(&to, RPRESSUREB);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
      }
   }
return(length);
}

void StrCpyTwoToOneByte(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function takes asian string and convert them to European string     */
/****************************************************************************/
{
      strcpy(to, from);
}

UINT16 LangStrLen(SINT8 * str)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strlen function for Asian Language                */
/****************************************************************************/
{
   UINT16 length = 0;
   length = strlen (str);
   return length;
}

void StrCpyTwoBytes(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function converts one byte into byte format for asian language      */
/****************************************************************************/
{
      strcpy(to, from);

}

void StrCatTwoBytes(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function adds one byte into byte format for asian language      */
/****************************************************************************/
{
      strcat(to, from);

}

void LangStrCpy(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strcpy function                                   */
/****************************************************************************/
{
      strcpy(to, from);
}

void LangStrCat(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strcat function                                   */
/****************************************************************************/
{
      strcat(to, from);
}

BOOLEAN LangCheckNull(SINT8 * Line)
/****************************************************************************/
/*Description:-                                                             */
/* This function checks for null at the start of a string                   */
/****************************************************************************/
{
   BOOLEAN VGAIsNull = FALSE;
      if (Line[0] == 0)
         VGAIsNull = TRUE;

   return (VGAIsNull);
}

UINT16 USBFullCheckFunc(void)
{
   if(VGAUSBFullStatus)
      VGAUSBFullFlag = TRUE;
   else
      VGAUSBFullFlag = FALSE;

   return(VGAUSBFullFlag);
}

/*==========================================================================*/
/*************************************End************************************/
/*==========================================================================*/      
