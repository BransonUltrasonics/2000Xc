/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/command.cpp_v   1.79   Nov 06 2017 11:02:40   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/command.cpp_v  $
 * 
*    Rev 1.80   Feb 27 2020 rvite
 * Added Ethernet and Record Options to Map[] for buttons, changed the WC address to SBC - 10
 *
 *    Rev 1.79   Nov 06 2017 11:02:40   RJamloki
 * Fix hard code numbers for micro c actuator id
 * 
 *    Rev 1.78   Oct 09 2017 15:48:06   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.77   Jun 07 2017 16:53:50   RJamloki
 * change config variable to LowerFlowValveFlag
 * 
 *    Rev 1.76   Jun 07 2017 15:40:44   RJamloki
 * change config variable to PressureStepDownFlag
 * 
 *    Rev 1.75   Jun 07 2017 11:27:34   RJamloki
 * Fixes from code review 5/29/2017 bucket 3
 * 
 *    Rev 1.74   Jun 01 2017 16:52:22   RJamloki
 * Adding ID's descriptive to actual command
 * 
 *    Rev 1.73   May 25 2017 16:24:18   RJamloki
 * Update new commands for webservices and small flow valve
 * 
 *    Rev 1.72   01 Sep 2016 13:10:06   RJamloki
 * Reupdated to version manager
 * 
 *    Rev 1.71   25 Aug 2016 15:39:12   RJamloki
 * updated PRESSURESTEPDOWN,SetAuthorityForFirmware,CheckForLogInButtonDisplay
 * from bucket #2 release v12.2
 * 
 *    Rev 1.70   26 May 2016 16:34:48   RJamloki
 * Added EXECUTIVE_PASSWORD_CHANGE functionality
 * 
 *    Rev 1.69   09 May 2016 12:00:36   RJamloki
 * Updated function for Turning off Authority Check (logoff NA)
 * 
 *    Rev 1.67   17 Dec 2015 11:39:56   RJamloki
 * Adding a missing variable UINT8 GetAuthorityCrt = 0; for
 * ahutority check
 * 
 *    Rev 1.66   16 Dec 2015 13:56:58   RJamloki
 * Add to VerifyLengthAndCode a case and lenght validation 
 * SEND_HORN_CLAMP_STATUS_SIZE
 * 
 *    Rev 1.65   16 Dec 2015 13:46:54   RJamloki
 * Add a command to function ProcessVGAHostCommand SEND_HORN_CLAMP_STATUS 
 * 
 *    Rev 1.64   16 Dec 2015 13:30:02   RJamloki
 * Remove from function SendConditionVariable the one byte 
 * FRAMUserIdObj.GlobalOpAuth buffer data
 * 
 *    Rev 1.63   16 Dec 2015 13:17:10   RJamloki
 * Function update for SetClampAlarmMenuValue
 * release the horn clamp alarm
 * 
 *    Rev 1.62   17 Nov 2015 16:45:34   RJamloki
 * Added an extra condition to validate if reset horn clamp and operator are active.
 * Send the operation authority variables to the SBC when it boots or request
 * 
 *    Rev 1.61   30 Apr 2015 12:06:24   rjamloki
 * In XMLDataResponse function UpdateCurrentPresetAndSetup() call is avoided on Pressure and Downspeed change from HornDown menu.
 * 
 *    Rev 1.60   16 Apr 2015 07:20:22   rjamloki
 * Fix for technician weld setup limits change not allowed in locked preset issue, minimum trigger force issue
 * 
 *    Rev 1.58   09 Apr 2015 08:10:54   amaurya
 * Increasing the Count in else condition instead of for loop itself,this was causing actual position of user to shift by one more index in ChangePassword() function.
 * 
 *    Rev 1.56   08 Apr 2015 13:42:30   AnPawar
 * Updated MAP and MinMap array for Pressure Stepping and Record Event for Authority Check Change.
 * 
 *    Rev 1.55   03 Apr 2015 07:13:06   amaurya
 * CurrentPreset.Amp2Flag removed from map array id 114, this was causing all the step values set to on after changing amplitude tracker issue 1038
 * 
 *    Rev 1.54   01 Apr 2015 13:01:04   amaurya
 * SetAuthorityForFirmware() function change for authority check event.
 * 
 *    Rev 1.53   30 Mar 2015 06:01:26   rjamloki
 * UnitFormat field of POWERMLS changed to PERCENTX10.
 * 
 *    Rev 1.52   27 Mar 2015 11:06:52   amaurya
 * WELD_HISTORY_COUNT increased to 50.50 cycle data  sbc can get from wc.
 * 
 *    Rev 1.51   16 Mar 2015 05:49:26   rjamloki
 * Removed unused variables from SetupValid function
 * 
 *    Rev 1.50   13 Mar 2015 06:06:38   amaurya
 * AMP1_FIX_ID added to fix the weld setup amplitude setup limit issue as setup limits were not working for amp1.Comments added for SetupValid().
 * 
 *    Rev 1.48   11 Feb 2015 06:30:52   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.47   03 Feb 2015 07:22:08   amaurya
 * CheckForLogInButtonDisplay() added to checks whether to display Login Button on Main menu.
 * 
 *    Rev 1.46   02 Feb 2015 09:25:48   amaurya
 * SetArrayData function changed to remove the trailing spaces in ps serial number
 * 
 *    Rev 1.45   02 Feb 2015 07:08:04   amaurya
 * ColdStartPlus() changed to add condition foe AES actuator.
 * 
 *    Rev 1.44   30 Jan 2015 08:09:26   amaurya
 * HOLD_PRESSURE_FLAG added to MAP array.
 * 
 *    Rev 1.43   21 Jan 2015 09:38:46   amaurya
 * Changed to send weld data after starting of state machine.
 * 
 *    Rev 1.42   08 Jan 2015 03:02:48   AnPawar
 * printf removed and flowcontrol format changed to percent
 * 
 *    Rev 1.41   06 Jan 2015 05:24:48   AnPawar
 * GetPresetNames function argument type changed
 * 
 *    Rev 1.40   05 Jan 2015 04:27:18   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.39   02 Jan 2015 06:29:50   rjamloki
 * numbers replaced TWEAK_DOWN_ID and TWEAK_UP_ID in XMLDataResponse() function
 * 
 *    Rev 1.38   02 Jan 2015 03:59:32   rjamloki
 * GetPresetNames_USB() function and COPY_ALL_PRESET_COMMAND added to support preset copy all and changes related to firmware upload and weld and hold pressure and preset revesion number
 * 
 *    Rev 1.37   12 Dec 2014 05:29:16   RJamloki
 * Moved TweakUp and down functions to FlowLookUptable.cpp
 * 
 *    Rev 1.36   11 Dec 2014 08:34:44   AnPawar
 * User ID on system info and tweak + and - downspeed changes.
 * 
 *    Rev 1.35   28 Nov 2014 07:33:40   rjamloki
 * WELD_HISTORY_COUNT macro changed to avoid weld data loss.EstopResetLogin,ClearUserIdOnClamp and ClearPasswordOnClamp added to MAP array.
 * 			  VGADOWNLOAD_PRESET command change to add condition for Technician Cannot Overwrite a Locked Preset.VGA_PRINTERROR_COMMAND command case change to add DiskMemoryNearlyfull and UsbMemoryNearlyFull alarms.EstopResetLogin() added to verify the user id and password on Estop reset confirmation screen.
 * 
 *    Rev 1.34   14 Nov 2014 10:22:44   AnPawar
 * changes for down speed tuning.
 * 
 *    Rev 1.33   14 Nov 2014 05:29:56   rjamloki
 * MIN_IDLELOGOUTTIME macro removedSendMinMaxData() changed to send minmax value of flowcontrol.
 * 
 *    Rev 1.32   10 Nov 2014 04:46:56   AnPawar
 * Removed Branson user checks.Added new IDs for Downspeed reject limit in Map structure.
 * 
 *    Rev 1.31   03 Nov 2014 11:44:58   tayars
 * Fixes for code review. Added temp variable for Flow so that if the same value is set twice, it will not invalidate the flow tuning.
 * 
 *    Rev 1.30   20 Oct 2014 06:17:08   AnPawar
 * Branson login password changed.Removed 
 * MINCLAMPDELAY and MAXCLAMPDELAY.Modified Map structure.XMLDataProcess(),SendConditionVariable() function changed.SEND_QUALITYLIMITS_DATA case and SendQualityLimitsData()
 * 
 *    Rev 1.29   06 Oct 2014 06:29:16   AnPawar
 * removed ck_qsend.h,FrontPanelKeypadTask.h,ticks.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.28   03 Oct 2014 05:51:56   rjamloki
 * New variable for unit format is added in MAP structure and VGADiskFull Flag added for DiskFull Alarm
 * 
 *    Rev 1.27   26 Sep 2014 03:24:44   rjamloki
 * Added variable in map to show Overload type
 * 
 *    Rev 1.26   11 Sep 2014 16:50:06   rjamloki
 * Corrected broken GETNETWORKINFO command in previous checkin.
 * 
 *    Rev 1.25   11 Sep 2014 10:49:36   rjamloki
 * changes for event support
 * 
 *    Rev 1.24   05 Sep 2014 04:36:26   rjamloki
 * Removed Compressed preset and changes to support 1000 preset
 * 
 *    Rev 1.23   22 Aug 2014 06:59:16   rjamloki
 * Added Param id in min max table to be used by web services
 * 
 *    Rev 1.22   18 Aug 2014 01:37:58   rjamloki
 * user name removed
 * 
 *    Rev 1.21   07 Aug 2014 15:31:26   tayars
 * Added support for both event reason and downspeed tuning.
 * 
 *    Rev 1.20   28 Jul 2014 12:42:36   rjamloki
 * added udi scan and clamp on alarm support, review fixes.
 * 
 *    Rev 1.19   09 Jul 2014 14:55:38   rjamloki
 * Addded Parmeter IDs in Map table.
 * 
 *    Rev 1.18   20 Jun 2014 14:54:56   rjamloki
 * Seperated Pressure and Force calibration handlers.
 * 
 *    Rev 1.17   16 Jun 2014 08:30:44   rjamloki
 * Removed SendPressureAndFlowValToAES function from map as its now called periodacillay from ManageSensors function.
 * 
 *    Rev 1.16   11 Jun 2014 11:18:06   rjamloki
 * Removed redundant globals, VGA MenuResponse size increased for sonics disable issue
 * 
 *    Rev 1.15   27 May 2014 10:12:14   amaurya
 * Added alarm for History validation
 * 
 *    Rev 1.14   21 May 2014 10:47:52   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.13   21 May 2014 02:51:20   rjamloki
 * coverity fixes, tracker fixes
 * 
 *    Rev 1.12   07 May 2014 10:18:40   rjamloki
 * Changes for password change,first time login,password expire.Check for mulptiple users with same name and ID.
 * 
 *    Rev 1.11   23 Apr 2014 13:52:28   akaushal
 * Corrected the code for getting network address.
 * 
 *    Rev 1.10   21 Apr 2014 13:26:40   rjamloki
 * Login verification, Event and alam logging implementation added
 * 
 *    Rev 1.9   14 Apr 2014 09:54:06   rjamloki
 * Fixed include and define for SBC Ethernet interface
 * 
 *    Rev 1.8   26 Mar 2014 12:03:50   rjamloki
 * variables and function added to display p/s ip and p/s mac.
 * 
 *    Rev 1.7   07 Mar 2014 11:11:10   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.6   06 Mar 2014 11:03:44   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:18   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:32   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.3   03 Jan 2014 08:45:20   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 *  ---------------------------- MODULE DESCRIPTION -------------------------------
 * 
 * Module name:  IPS_Command_Handler
 * 
 * Filename:     command.c
 * 
 * 
 * Written by:  Mark Lazarewicz
 *  Date:  03/11/96
 *  Language:  Microtec "C"
 * 
 * ------------------------------- DESCRIPTION -----------------------------------
 * This module handles host commands. See the IRS for more information.
 * ------------------------------- PSEUDO CODE -----------------------------------
 * 
 * ------------------------------ INCLUDE FILES ----------------------------------
 */

#include "qdef.h"           /* general hardware defines, etc..   */
#include "string.h"
#include "names.h"          /* task objects                      */
#include "opcodes.h"
#include "serial.h"
#include "command.h"        /* function prototype     */
#include "SystemManagerTask.h"       /* function prototypes    */
#include "psnvram.h"        /* function prototypes    */
#include "menu6.h"          /* function prototypes    */
#include "root.h"           /* function prototypes    */
#include "mansensr.h"
/* inbound messages */
#include "genrlmsg.h"
#include "ipscdmsg.h"
#include "selctkey.h"

/* outbound messages */
#include "nvm_msg.h"

/* called interfaces */
#include "battram.h"        /* battram_test() prototype  */
#include "ticks.h"
/* typedef include */
#include "weld_obj.h"
#include "preset.h"
#include "menu3.h"
#include "limits.h"
#include "menu7a.h"
#include "param.h"
#include "menu7.h"
#include "fpled.h"
#include "alsetup.h"
#include "ready.h"
#include "menu1.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "menu.h"
#include "menu2.h"
#include "rtclock.h"
#include "ipsatype.h"
#include "getmsg.h"
#include "graphs.h"
#include "util.h"
#include "alarms.h"
#include "dups.h"
#include "dups_api.h"
#include "time.h"
#include "statedrv.h"
#include "WeldManagerTask.h"
#include "keypad.h"
#include "digout.h"
#include "beep.h"
#include "portable.h"
#include "rdyweld1.h"
#include "stdio.h"
#include "RTOS.h"
#include "keypad.h"
#include "weldhold.h"
#include "PRSETPRN.H"
#include "NetworkManagerTask.h"
#include "weld.h"
#include "FlowLookupTable.h"
#include "Events.h"
#include "DUPS_ManagerTask.h"
#include "inports.h"
#include "outports.h"
#include "WebService.h"
#include "FrontPanelKeypadTask.h"
#include "RVTSHandlerTask.h"
#include "ticks.h"
#include "ascii.h"
#include "selctkey.h"
#include "InputTask.h"
#include "menuhorn.h"
#include "DIButtonsUI.h"

#define  WELD_HISTORY         1
#define  WELD_HISTORY_COUNT   50//max number of cycles data sbc can get from WC.
#define  USCS                 0
#define  METRIC2              1
#define  METRIC3              2
#define WELDTRIG_ENABLEID     115
#define VALIDATEPS_ENABLEID   525
#define LOCKPS_ENABLEID       526
#define PRESETNUMBER_SIZE     2

#define WELDHISTSETUPMIN    512
#define WELDHISTSETUPMAX    2140134912
/* ------------------------ EXTERNAL DATA --------------------------------- */
extern INBITS Inp;
extern enum WELDSTATES WeldState;
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH + 1]; /* Now defined in Version.c */
extern BOOLEAN IsGraphDrawing;
extern BOOLEAN ReadyFlag;
extern UINT16 PresetEnableFlags[MAX_POSSIBLE_PRESET + 1]; /* TRUE: Preset is valid   FALSE: Preset is not valid */
extern UINT16 LangIndex;
extern UINT16 RadioIndex;
extern UINT32 RadioIndexL;
extern DEPOT_FLAGS *DepotFlag;
extern UINT32 KeyMask;
extern UINT16 RapidTraverseState;
extern UINT8 LimitChanged;
extern UINT8 *VGAAckBuf;
extern SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH + 1];
extern SINT32 DownspeedTuneCycles;
BOOLEAN FirmwareUploadAllowed = FALSE;
/* Stuff for graph host command */
extern UINT16 WeldDataCount;
extern WELD_OBJECT *MsPointer;
extern SINT32 val2[MAX_WELD_SAMPLES];
extern UNION_BOOL_UINT16 PressureStepEnableFlag;

UINT8 ChangePassword(void);
UINT8 Check_ExistingUserDetails(UINT8, SINT32);

/*
 *  ------------------------------- PROTOTYPES ------------------------------------
 */
void SetDefaultUserData(void);
void SaveActSerialNum(void);
void SetAuthorityForFirmware(void);

UINT16 ComputeAuthorization(void);
UINT16 CreateGraphHeader(UINT16, UINT8 Buffer[]);
UINT16 SendMenuPtrs(UINT8 * to);
UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len);
void ProcessAlarmItems(UINT16 ID);
UINT16 SystemPresetReport1(UINT8 * AckBuf);
UINT16 SystemPresetReport2(UINT8 * AckBuf);
UINT16 SystemPresetReport3(UINT8 * AckBuf);
UINT16 SystemPresetReport4(UINT8 * AckBuf);
UINT16 SystemPresetReport5(UINT8 * AckBuf);
UINT16 DupsPresetReport1(UINT8 * AckBuf);
UINT16 DupsPresetReport2(UINT8 * AckBuf);
UINT16 PrintSeqPresetInfo(UINT8 * AckBuf);
UINT16 CreateSameBufferACK(UINT8 * AckBuf, UINT16 Function, UINT16 len);
UINT16 VGAPrintParameters(UINT8 * to);
UINT16 VGAPrintGraphInfo(UINT8 * to);
UINT16 VGAWeldDataInfo(UINT8 * to);
void ClearPMCData(void);
void AddToPMCData(void);
void SetHoldPressure(void);


UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
UINT16 LangStrLen(SINT8 * str);
//Min Max added for JSON values verification
UINT16 PSFrequencyMinValue = FREQ15KHZ;
UINT16 PSFrequencyMaxValue = FREQ60KHZ;
SINT32 BooleanMinValue = 0;
SINT32 BooleanMaxValue = 1;
UINT16 WeldScaleIndexMinValue = WELDTIMEx1;
UINT16 WeldScaleIndexMaxValue = WELDTIMEx3;
UINT16 BooleanMinValue16 = 0;
UINT16 BooleanMaxValue16 = 1;

UINT16 HWVerifyMinValue = 1;
UINT16 HWVerifyMaxValue = 7;
UINT16 GetInputMinValue = INPUT_DISABLED;
UINT16 GetInputMaxValue = INPUT_CONFIRM_REJECT;
UINT16 GetOutputMinValue = OUTPUT_DISABLED;
UINT16 GetOutputMaxValue = OUTPUT_UDIREADY;
SINT32 HistorySetupMinValue = WELDHISTSETUPMIN;
SINT32 HistorySetupMaxValue = WELDHISTSETUPMAX;
UINT16 AmplitudeModeMinValue = 0;
UINT16 AmplitudeModeMaxValue = 1;
UINT16 PretriggerModesMinValue = 0;
UINT16 PretriggerModesMaxValue = 3;
UINT16 OperatorAuthMinValue = 0;
UINT16 OperatorAuthMaxValue = 31;
SINT32 HdMinPressure = 0;
/*
 *  --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
 */
/* inbound messages to the mich queue */
typedef union {
	GENERIC_MSG generic;
	HOST_CMD_WELD_MSG host_cmd;
} RSCH_MSG_QUEUE_TYPE;

UINT32 RschQid;

/*------------------ LOCAL FUNCTION DECLARATIONS ---------------------------*/

UINT16 ConvertWeldData(WELD_DATA *Ver8WeldData, UINT8 *StrSPCData);
BOOLEAN CheckForParameterError(UINT16 Value);
UINT16 XMLDataProcess(UINT8 * to, UINT16 TempID, UINT16 ID);
void CheckforDisplayLock(void);

/*------------------- PRIVATE GLOBAL DATA ----------------------------------*/

WELD_DATA7_02 SPCData;
UINT8 *SPCDataPtr;
UINT8 RcvChecksum;
UINT32 ErrorResponseMinLimit, ErrorResponseMaxLimit;
UINT32 ErrorID;
UINT32 NackError;
UINT16 HostPresetEmpty = TRUE; /*TRUE: if preset data is send from host terminal*/
BOOLEAN ResetFailed = FALSE; /*TRUE: in case of any Non-Resetable alarm.*/
BOOLEAN ResetAlarmProcessed = FALSE; /* TRUE: After process the ResetKey in weldmngr*/
Ver1200Setups HostPreset;/*Store the data sent from the Host terminal.*/
BOOLEAN VGA_ScreenCalibFlag = FALSE;
BOOLEAN WindowSetupFlag = FALSE;
BOOLEAN VGA_ReadyFlag;
BOOLEAN VGAHistoryValidatedFlag = FALSE;
BOOLEAN VGAUSBOfflineFlag = FALSE;
BOOLEAN VGAUSBFullFlag = FALSE;
BOOLEAN VGADISKFullFlag = FALSE;
UINT16 ViewDupsPresent = FALSE;
BOOLEAN CurrentPresetParameterChanged = FALSE;
BOOLEAN OnboardDiag = FALSE; /* For standard software make sure diagnostics are disabled */
UINT8 DateArr[4];
UINT8 TimeArr[3];
UINT8 FlowValveAEDEmulationIndicatorStr[MAX_LOWER_FLOW_VALVE_LEN];
UINT16 GlobalCommandID;
STR PresetListBoxBuffer[VGA_LINESIZE];
STR LineBuffer[LINESIZE + 1];
UINT8 PasswdEntryFlag;
BOOLEAN SystemParameterChgdFlag = FALSE;
SINT32 PassExpTimeMax = MAX_PASSEXPTIME;
SINT32 PassExpTimeMin = MIN_PASSEXPTIME;
SINT32 IdleLogoutTimeMax = MAX_IDLELOGOUTTIME;
SINT32 IdleLogoutTimeMin = MIN_IDLELOGOUTTIME;
SINT32 MinPresetNumber = 1;
SINT32 MaxPresetNumber = MAX_POSSIBLE_PRESET;
SINT32 SelectedPresetNumber;
char ip_addr[16]; // added for GetPsip()
char mac_addr[20]; // added for GetMac()
BOOLEAN UserLoggedIn = FALSE;
UserID useridData;
enum OpAuth userOpAuth;
UserID CurrentUser;
enum OpAuth CurrUserOpAuth;
char CurrUserID[MAX_USERNAME_LEN];
char Assign_UserID[MAX_USERNAME_LEN];
char CurrPassword[MAX_PASSWORD_LEN];
char Old_Password[MAX_PASSWORD_LEN];
char New_Password[MAX_PASSWORD_LEN];
char Confirm_Password[MAX_PASSWORD_LEN];
UINT16 HWverifySetup = 0;
char UDIString[MAX_UDISTRING_LEN];
BOOLEAN UDIScanRecived = false;
UINT16 DUPSOverloadType;
char CurrUserID_For_SysInfo[MAX_USERNAME_LEN];

/*------------------------------- CODE -------------------------------------*/

UINT16 SendArrayData(UINT8 ** to, UINT16 TempID);

void GetRS232Index(void);
void SetRS232Index(void);
void HDSavePreset(void);
void EstopResetLogin(void);
void GetDownSpeed();
void SetEventReason();
void ClearReasonString(void);
void SetEventReasonFlag(void);
void ClearPasswordOnClamp(void);
void ClearUserIdOnClamp(void);
void SetClampAlarmMenuValue(void);
void SendSelectedPreset(void);
void ReadOut(void);
void DiagnoseIn(void);
void DiagnoseOut(void);
void GetUserLevel(void);
void SetUserLevel(void);
void SetOpAuthority(void);
void GetOpAuthority(void);
void GetWeldHistSetup(void);
void SetWeldHistSetup(void);
void GetCylinderIndex(void);
void GetStrokeLenIndex(void);
void GetCalData(void);
void UpdateRunTopLine(void);
BOOLEAN DigitalPotEntry(void);
void InitWeldParamOption(void);
void SetCylinderDiameter(void);
void SetStrokeLen(void);
void SetBeeperCondition(void);
void CheckForPrintingOrWelding(void);
void CheckForCustomAct(void);
void SaveWeldParamState(void);
void BuildWeldColumnStr(void);
void GetInput(void);
void GetOutput(void);
void SetInputSelection(void);
void SetOutputSelection(void);
void OkToDefault(void);
void ChangeDisplayColumn(void);
void GetWeldScaleIndex(void);
void SetWeldScaleIndex(void);
void SetTestScaleIndex(void);
UINT8 VerifyUsernamePassword(void);
void GetWeldMode(void);
void SetWeldMode(void);
void PrepareAmplitudeRadioMenu(void);
void SetAmplitudeModes(void);
void PreparePretriggerRadioMenu(void);
void SetPretriggerModes(void);
void PreparePressureRadioMenu(void);
void SetPressureModes(void);
void ChangeDUPSSubParamList(void);
void ChangeFreqOffsetSign(void);
void VarDigTuneStore(void);
void GetPresetNum(void);
void SaveNamedPreset(void);
void SetPresetClearFlags(void);
void ProcessPresetClear(void);
void PreparePrstSaveTitle(void);
void ProcessPresetRecall(void);
UINT16 ProcessPresetVerify(UINT8 **);
void PreparePrstInfoString(void);
void PresetSaveOk(void);
void PresetSaveCancel(void);
void EraseSeqList(void);
void EraseSeqList1(void);
void GetSequenceNos(void);
void SetAmpControlValue(void);
void SetFreqControlValue(void);
void SetupAmpModeStepFlag(void);
void VGAPasswordEntry(void);
void SetupOption(void);
UINT16 PasswordSave(UINT8 ** to);
void VGATestCheckSum(void);
void GetRTRamp(void);
void SetRTrRamp(void);
void GetReturnRamp(void);
void SetreturnRamp(void);
void GetStartRamp(void);
void SetstartRamp(void);
void UpdateCalibDefault(void);
void ResetHornScanValue(void);
void CopyToFRAM(void);
void SetDiagFlag(void);
void ProduceBeep(void);
void GetRunSelection(void);
void GetClearSelection(void);
void GetSeekSelection(void);
void GetStoreSelection(void);
void DisableDiagnostics(void);
void ColdStartEnable(void);
void EnableActColdStart(void);
void DebugReadMemory(void);
void VGADigitalPotChoiceDone(void);
BOOLEAN DigitalFreqEntry(void);
void VGARecallMinimumPreset(void);
void VGARecallMaximumPreset(void);
void VGARecallColdStartPreset(void);
void VGASaveMinimumPreset(void);
void VGASaveMaximumPreset(void);
void VGASaveColdstartPreset(void);
void VGARestoreMinMaxPreset(void);
void RestoreFactoryColdstart(void);
void EnableHornScanStart(void);
void DUPS_StartHS(void);
void ProcessHSAbort1(void);
void DoHornDownFunc(void);
void ProcessHDButtonPress2(void);
void ProcessHDButtonPress1(void); //For retract button
void BottomMenuProcess(void);
void ProcessWindowSetup(void); //for Window Setup
void EnableWelding(void);
void DoColdStart(void);
void VGAActColdStart(void);
void VGARestoreColdStart(void);
void VGACreateColdStartPreset(void);
void EnableCreateStart(void);
void OverwritePresetCheck(void);
void VGAOverwriteAllPreset(void);
void BankSwitchPresets(void);
void CreateGraphData(void);
void VGADebugColdStart(void);
void VGAConfigureFromBUCMenu(void);
void UpdateTestAmp(void);
void SetDigtalPot(void);
void ResetSensorCalb(void);
void SBCReadA2D3(void);
void VGARequestActCal(void);
void SCInitialize(void);
void ManualSCInitialize(void);
void VGACloseCalibration(void);
void DisableCalActKey1(void);
void SBCReadA2D4(void);
void SaveCalibPressure(void);
void CalibFinalCleanup(void);
void SBCReadA2DLC2(void);
void SBCReadA2D1(void);
void VGABuildForceTable(void);
void BuildPressureTable(void);
void GetCurrentPresetNames(void);
void GetBatchCountInfo(void);
UINT16 SendWeldState(UINT8 * to);
UINT16 WeldParams(UINT8 * *Response, UINT16 WeldCount, BOOLEAN ParamFlag);
void SetRunScreenParam(void);
UINT16 VGASendPollingData(UINT8 * to);
void ProcessHDButtonPress3(void);
UINT16 ProcessWeldGraphValue(UINT8 WeldGraphDataReq, UINT8 WeldCount);
UINT16 SendPMCValue(UINT8 * AckBuf);
UINT16 SystemViewPresetReport(UINT8 * AckBuf);
void VGAAlarmReset(UINT32 dummy);
void GetCalStatus(void);
void ChangeBaseAndWordLength(void);
void SetPSFrequency(void);
void GetPSIpAddress(void);
void GetPSMacAddress(void);
int PasswordExpDays(RTCTime *);
int julian(int, int, int);
void ClearCurrentBatchCount();
void GetPresetValidated();
void SetPresetValidated();
void GetPresetLocked();
void SetPresetLocked();
void SetAutomationUserId();
void SetUDIflag(void);
void SendCurrentUserId();
void SendLowerFlowValve();
void EnableStartSensorCal();
void UpdatePressureOnHornDownEntry();
void UpdateFlowOnHornDownEntry();
BOOLEAN SBCReadyFlag = FALSE;
extern BOOLEAN AllParamColumnFlag;
extern UINT16 WorkingPasswordFlag;
extern UINT16 SystemPres60PSI;
extern UINT16 SystemPres80PSI;
extern STR PSFreqTxt[5];
extern UINT32 HWConfiguration;
extern UINT32 SWConfiguration;
extern RTCTime RTCMenu;
extern UINT16 DisplayNextMenu;
extern UINT16 HHInactive1;
extern SINT32 WelderAddrMinValue;
extern SINT32 WelderAddrMaxValue;

SINT32 MinPartClampDelay = 0;
SINT32 MaxPartClampDelay = 10000;
SINT32 MinPSWatt = 100;
SINT32 MaxPSWatt = 9999;
extern SINT32 MinLimitForcePC;
extern SINT32 MinLimitMinTrigForce;
extern SINT32 MaxLimitMinTrigForce;
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UINT16 FlagPretriggerDist;
extern UINT16 FlagPretriggerTime;
extern UINT16 FlagPretriggerAmpl; // this flag is for pretrigger amplitude
extern UINT16 AmpCntrlExt, AmpCntrlInt;
extern UNION_BOOL_UINT16 AmpControlInternal;
extern SINT8 AssignNamePresetBuffer[MESSAGESIZE];
extern STR InfoLine2[VGA_LINESIZE];
extern STR InfoLine3[VGA_LINESIZE];
extern STR InfoLine4[VGA_LINESIZE];
extern STR InfoLine5[VGA_LINESIZE];
extern STR InfoLine6[VGA_LINESIZE];
extern UINT16 OldSameNameAvailable;
extern UINT16 NewSameNameAvailable;

extern STR NewSameName[];
extern STR OldSameName[];
extern UINT16 TempSequenceNos;
extern enum LEVEL AccessLevel;
extern SINT32 MinBUCFactoryDefaults;
extern SINT32 MaxBUCFactoryDefaults;
extern SINT32 MinLimitGainFactor;
extern SINT32 MaxLimitGainFactor;
extern SINT32 MinLimitIdleSpeed;
extern SINT32 MaxLimitIdleSpeed;
extern SINT32 DigTuneValue;
extern SINT32 MinDigTuneValue, MaxDigTuneValue;
extern SINT32 FMemoryBargraph;
extern SINT32 FActualBargraph;
extern BOOLEAN VGARunSelected, VGAClearSelected, VGASeekSelected,
		VGAStoreSelected;
extern SINT32 DebugPtr;
extern SINT32 DebugLowValue, DebugHighValue;
extern UINT16 BransonFunctionFlag;
extern UINT16 SpecialMenuFlag;
extern UINT16 TestingMenuFlag;
extern UINT16 DebugPasswordFlag;
extern BOOLEAN ForceDigitalTuneTest;
extern SINT32 SaveDigTuneValue;
extern UINT16 DiagFlag;
extern UINT16 ResonanceFreqEnable[];
extern SINT32 WorkingForceSet; /* Temporary target pressure         */
extern SINT32 RTTransitionDist; /* Rapid Traverse Transition distance */
extern UINT16 HDShowPressure; /* Controls display of sys pressure */
extern BOOLEAN VGAHornDown;
extern SINT32 HornDownVelocity;
extern SINT32 HDPosition; /* Same as EncoderPos but never < 0 */
extern SINT32 CurrentForce; /* Actual horndown force */
extern UINT16 HDShowForce; /* Controls display of force item */
extern UINT16 HDShowVelocity; /* Controls display of velocity item */
extern UINT16 HDMenuID;
SINT32 UserIdIndex = 0;//Index of Currently Logged in user in UserId array.
extern UINT8 FreqType[DUPS_NUMRESONANCES];
extern BOOLEAN HSStartFlag;
extern SINT32 CurrentFreqIn;
extern SINT32 PowerTest;
extern SINT32 UserPressure[3];
extern SINT32 ForceGaugeReadingMin;
extern SINT32 ForceGaugeReadingMax;
extern SINT32 LoadCellReadingMin; /* Lowest acceptable loadcell reading */
extern SINT32 LoadCellReadingMax; /* Highest acceptable reading         */
extern SINT32 ForceV[];
extern STR FailedByValue;
extern STR StrWeldStateLine[VGA_LINESIZE];
extern STR CurrentPresetName;
extern STR BatchCountInfo[VGA_LINESIZE];
extern UINT16 TotalCycle;
extern UINT8 PrevHornState;
extern BOOLEAN VGAHornScanOLD;
extern BOOLEAN DebugBase;
extern BOOLEAN DebugBytes;
extern STR DebugTitle[VGA_LINESIZE];
extern STR DebugText1[VGA_LINESIZE];
extern STR DebugText2[VGA_LINESIZE];
extern STR DebugText3[VGA_LINESIZE];
extern STR DebugText4[VGA_LINESIZE];
extern UINT32 ActualPeakPower;
extern SINT32 WeldForceEnd;
extern SINT32 TestTime;
extern SINT32 MaximumForce;
extern SINT32 FreqChg, TestTime, PowerTest;
extern SINT32 PTSTimer;
extern SINT32 OverloadPower, OverloadFreq;
extern SINT32 ActualForceMax;
extern SINT32 ActualSBLMinFreq, ActualSBLMaxFreq;
extern SINT32 ActualValuePMC1, ActualValuePMC2;
extern UINT16 BinEnable, HexEnable;
extern UINT8 MenuNxtPointer;
extern BOOLEAN VGAUSBFullStatus;
extern BOOLEAN VGA_ScreenDiagFlag;
extern void  ExitMenuAndEnableWeld (void);
void CheckForLogInButtonDisplay(void);
BOOLEAN TempPresetValidated;
BOOLEAN TempPresetLocked;
UINT16 ShowLogInButton = 0, ShowLogOutButton = 0;
UINT16 GlobalFunctionCode;//keeps the last command requested from menu
extern UINT16 PresetCheck;//contains the number of preset being displayed using View Preset button
					 //on USB memory screen.

//Below Flag becomes true when user is on CalSensors screen. If this flag is true TestReady function
//should not check for incorrect pressure, should not auto correct pressure to avoid regulator buzzing sound and shoul not give alarms either. The assumption is that user is going to start the
//sensor calibration and should not be interrupted. This flag becomes false when bottom menu click is detected to resume normal operation of incorrect pressure checking.
BOOLEAN StartingSensorCal = FALSE;

UINT16 GetPresetNames_USB(UINT8 * AckBuf,UINT16 ReceiveValuePtr);

typedef enum {
	WELDHISTORY, /* Summary of last 50 welds   */
	WELDSUMMARY, /* Information for each weld  */
	POWERGRAPH, /* Graph of Power vs Time     */
	AMPGRAPH, /* Graph of Amplitude vs Time */
	FREQGRAPH, /* Graph of Frequency vs Time */
	COLDISTGRAPH, /* Graph of Distance vs Time  */
	VELOCITYGRAPH, /* Graph of Velocity vs Time  */
	FORCEGRAPH, /* Graph of Force vs Time     */
	PRESETPRN, /* Prints out the Preset and System variables */
	FINALRESULTS, /* Summary of last weld       */
	ONEMSDATA, ABSDISTGRAPH, HORNSCAN, DUPSPRESET, SEQUENCEPRESET
} MSG_GRAPH_TYPE;

void GetTime(void) {
	SetupOption();
	TimeArr[0] = (UINT8) RTCMenu.Hour;
	TimeArr[1] = (UINT8) RTCMenu.Minute;
}

void GetDate(void) {
	SetupOption();
	if (CurrentSetup.Units == TRUE) /*Display Time in the DD/MM/YY format.*/
	{
		DateArr[0] = (UINT8) RTCMenu.Day;
		DateArr[1] = (UINT8) RTCMenu.Century_Month;
		DateArr[2] = (UINT8) RTCMenu.Years;
	} else /*Display Time in MM/DD/YY format*/
	{
		DateArr[0] = (UINT8) RTCMenu.Century_Month;
		DateArr[1] = (UINT8) RTCMenu.Day;
		DateArr[2] = (UINT8) RTCMenu.Years;
	}
}

void TimeSet(void) {
	char Data1[MAX_EVENTDATA_LEN] ="", Data2[MAX_EVENTDATA_LEN]="";
	RTClock::GetCurrentTime(&RTCMenu); //Get the preset time and date
	//If you set the Time and Data is not in range(after cold start)
	if ((RTCMenu.Century_Month < 1) || (RTCMenu.Century_Month > 12))
		RTCMenu.Century_Month = 1;
	if ((RTCMenu.Day < 1) || (RTCMenu.Day > 31))
		RTCMenu.Day = 1;
	if (RTCMenu.Years > 99)
		RTCMenu.Years = 0;
	sprintf(Data1,"%02d:%02d",RTCMenu.Hour,RTCMenu.Minute);
	RTCMenu.Hour = (SINT32) TimeArr[0];
	RTCMenu.Minute = (SINT32) TimeArr[1];
	sprintf(Data2,"%02d:%02d",RTCMenu.Hour,RTCMenu.Minute);
	RTClock::SetCurrentTime(&RTCMenu);
	RecordEvents(EVENT_RTC_CHANGED, Data1, Data2);
}

void DateSet(void) {
	char Data1[MAX_EVENTDATA_LEN]="", Data2[MAX_EVENTDATA_LEN]="";
	RTClock::GetCurrentTime(&RTCMenu); // Get the present Time and Data.
	if(CurrentSetup.Units)
		sprintf(Data1,"%02d/%02d/%02d",RTCMenu.Day,RTCMenu.Century_Month,RTCMenu.Years);
	else
		sprintf(Data1,"%02d/%02d/%02d",RTCMenu.Century_Month,RTCMenu.Day,RTCMenu.Years);

	RTCMenu.Century_Month = (SINT32) DateArr[0];
	RTCMenu.Day = (SINT32) DateArr[1];
	RTCMenu.Years = (SINT32) DateArr[2];
	if(CurrentSetup.Units)
		sprintf(Data2,"%02d/%02d/%02d",RTCMenu.Day,RTCMenu.Century_Month,RTCMenu.Years);
	else
	    sprintf(Data2,"%02d/%02d/%02d",RTCMenu.Century_Month,RTCMenu.Day,RTCMenu.Years);
	RTClock::SetCurrentTime(&RTCMenu);
	RecordEvents(EVENT_RTC_CHANGED, Data1, Data2);
}

const MAP
		Map[] = {
				/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
				/* ID    Variable Pointer                    Variable Pointer to flag   Pointer to                    Function 1              Function2                           comment                             */
				/*                                             Type     to see if       disable/enable                                                                                                                */
				/*                                                    Display Line      flag                                                                                                                          */
				/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
				{UNITS			    ,  0, &CurrentSetup.Units, boolean, NULL, NULL, NULL,
						          	      UpdateRunTopLine, INTEGER }, //UnitsChoice
				{STARTSCREEN	    ,  1, &CurrentSetup.StartScreen, boolean, NULL, NULL, NULL, NULL , INTEGER}, //VGAStartScreenChoice
				{RS232SETUP		    ,  2,&RadioIndex, UInt16, NULL, NULL, GetRS232Index,SetRS232Index,INTEGER }, //serial port
				{WELDERADDRVALUE    ,  3,&CurrentSetup.WelderAddrValue, sint32, NULL,
									      &CurrentSetup.WelderAddrFlag, NULL, NULL, INTEGER }, //WelderAddr
				{GENERALALARMFLAG   ,  4,&CurrentPreset.GeneralAlarmLFlag, UInt16, NULL, NULL,
										  NULL, NULL, INTEGER }, //GeneralAlarmChoice
				{TIMEDATA			,  5,&TimeArr, arr, NULL, NULL, GetTime, TimeSet, INTEGER }, //TimeOfDay
				{DATEDATA			,  6,&DateArr, arr, NULL, NULL, GetDate, DateSet, INTEGER }, //MonthDateYear
				{AMPCONTROL		    ,  7,&CurrentSetup.AmpControl, boolean, NULL, NULL, NULL,
										  SetAmpControlValue, INTEGER }, //AmpControl
				{EXTRACOOLING	    ,  8,&CurrentSetup.ExtraCooling, boolean, NULL, NULL, NULL,
										  NULL, INTEGER }, //ExtraCoolingOpt
				{HANDHELD		    ,  9,&CurrentSetup.HandHeld, boolean, NULL, NULL, NULL,
									      DealWithHandHeldChange, INTEGER }, //HandHeld
				{PLCCONTROLFLAG     , 10,&CurrentSetup.PLCControlFlag, boolean,
										  (UINT16*) &CurrentSetup.PLCControlMenuFlag, NULL, NULL,
										  DealWithHandHeldChange, INTEGER }, //PLCControl
				{EXTPRESETS		    , 11,&CurrentSetup.ExtPresets, boolean, NULL, NULL, NULL,
										  DealWithExtPresetChange, INTEGER }, //ExtPresets
				{DIGITALFILTERFLAG  , 12,&CurrentPreset.DigitalFilterFlag, UInt16, NULL, NULL,
										  NULL, NULL, INTEGER }, //DigitalFilter
				{FREQCONTROL		, 13,&CurrentSetup.FreqControl, boolean, NULL, NULL, NULL,
										  SetFreqControlValue, INTEGER }, //FreqControl
				{PSLIFETIMECOUNTER	, 14,&CurrentSetup.PSLifetime, sint32, NULL, NULL, NULL, NULL, INTEGER }, //PSLifetime
				{OVERLOADCOUNTER	, 15,&CurrentSetup.Overload, sint32, NULL, NULL, NULL, NULL, INTEGER }, //Overloads
				{GENERALALARMCOUNTER, 16,&CurrentSetup.GenAlarmCount, sint32, NULL, NULL, NULL,
										  NULL, INTEGER }, //GeneralAlarm
				{PSWATT				, 17,&CurrentSetup.PSWatt, sint32, NULL, NULL,
										  GetPowerSupplyInfo, NULL, INTEGER }, //FrequencyWatts
				{ALLEMPTY			, 18,&RadioIndex, UInt16, NULL, NULL, GetCalStatus, NULL, INTEGER }, //CalibrationPass
				{ALLEMPTY			, 19,&DateArr, arr, NULL, NULL, GetCalData, NULL, INTEGER }, //CalibrationDate
				{ALLEMPTY			, 20,&ps_ver, str, NULL, NULL, GetSerialNumbers, NULL, INTEGER }, //PowerSupplyVersion
				{ALLEMPTY			, 21,&RadioIndex, UInt16, NULL, NULL, LoadActuatorType, NULL, INTEGER }, //ActuatorType
				{ALLEMPTY			, 22,&RadioIndex, UInt16, NULL, NULL, GetControlLevel, NULL, INTEGER }, //ControlLevelType
				{PSSERIALNUMBER		, 23,&CurrentSetup.PSSerialNumber, arr, NULL, NULL, NULL,
										  StorePSSerialNumber,STRING }, //PowerSupplySerialNumber / SetPSSerNum
				{ACTSERIALNUMBER	, 24,&CurrentSetup.ActSerialNumber, arr, NULL, NULL, NULL,
										  SaveActSerialNum,STRING }, //ActuatorSerialNumber / SetActSerNum

				{ALLEMPTY			, 25,NULL, nothing, &SystemPres60PSI, NULL, NULL, NULL,INTEGER }, //SetPressure60PSI
				{ALLEMPTY			, 26,NULL, nothing, &SystemPres80PSI, NULL, NULL, NULL,INTEGER }, //SetPressure80PSI
				{ALLEMPTY			, 27,&RadioIndex, UInt16, NULL, NULL, GetCylinderIndex,
										 SetCylinderDiameter,INTEGER }, //CylinderDiameter
				{ALLEMPTY			, 28,&RadioIndex, UInt16, NULL, NULL, GetStrokeLenIndex,
										  SetStrokeLen,INTEGER }, //CylinderStroke
				{ALLEMPTY			, 29,&DUPS_Info.LibraryName, str, NULL, NULL, NULL, NULL,INTEGER }, //VGALibraryBlockName
				{ALLEMPTY			, 30,&WorkingPasswordFlag, UInt16, NULL, NULL, SetupOption,
										  VGAPasswordEntry,INTEGER }, //VGAPasswordChoice
				{USBGLOBALFLAG		, 31,&CurrentSetup.USBGlobalFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBGlobalToggle
				{USBWDSAMPLEVALUE	, 32,&CurrentSetup.USBWDSampleValue, sint32, NULL,
										  &CurrentSetup.USBWDSampleFlag, NULL, NULL,INTEGER }, //USBWeldDataSample
				{USBWDALARMFLAG		, 33,&CurrentSetup.USBWDAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBWeldDataAlarm
				{USBPGSAMPLEVALUE	, 34,&CurrentSetup.USBPGSampleValue, sint32, NULL,
										  &CurrentSetup.USBPGSampleFlag, NULL, NULL,INTEGER }, //USBPowerSample
				{USBPGALARMFLAG		, 35,&CurrentSetup.USBPGAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBPowerAlarm
				{USBCDGSAMPLEVALUE	, 36,&CurrentSetup.USBCDGSampleValue, sint32, NULL,
										  &CurrentSetup.USBCDGSampleFlag, NULL, NULL,INTEGER }, //USBDistanceSample
				{USBCDGALARMFLAG	, 37,&CurrentSetup.USBCDGAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBDistanceAlarm
				{USBVGSAMPLEVALUE	, 38,&CurrentSetup.USBVGSampleValue, sint32, NULL,
										  &CurrentSetup.USBVGSampleFlag, NULL, NULL,INTEGER }, //USBVelocitySample
				{USBVGALARMFLAG		, 39,&CurrentSetup.USBVGAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBVelocityAlarm
				{USBFGSAMPLEVALUE	, 40,&CurrentSetup.USBFGSampleValue, sint32, NULL,
										  &CurrentSetup.USBFGSampleFlag, NULL, NULL,INTEGER }, //USBForceSample
				{USBFGALARMFLAG		, 41,&CurrentSetup.USBFGAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBForceAlarm
				{USBAGSAMPLEVALUE	, 42,&CurrentSetup.USBAGSampleValue, sint32, NULL,
										  &CurrentSetup.USBAGSampleFlag, NULL, NULL,INTEGER }, //USBAmplitudeSample
				{USBAGALARMFLAG		, 43,&CurrentSetup.USBAGAlarmFlag, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //USBAmplitudeAlarm
				{USBFREQGSAMPLEVALUE, 44,&CurrentSetup.USBFreqGSampleValue, sint32, NULL,
										  &CurrentSetup.USBFreqGSampleFlag, NULL, NULL,INTEGER }, //USBFreqSample
				{USBFREQGALARMFLAG	, 45,&CurrentSetup.USBFreqGAlarmFlag, boolean, NULL, NULL,
										  NULL, NULL,INTEGER }, //USBFreqAlarm
				{WELD_CYCLE_COUNT	, 46,NULL, nothing, NULL, NULL, NULL, VGAResetWeldCounterOk,COUNTER }, //VGAWeldCountResetOk
				{BEEPERTRIGGER		, 47,&CurrentSetup.BeeperTrigger, UInt16, &HHInactive1, NULL,
										  SetBeeperCondition, NULL,INTEGER }, //BeeperTrigger
				{BEEPERRELEASE		, 48,&CurrentSetup.BeeperRelease, UInt16,
										  (UINT16*) &CurrentSetup.HandHeld, NULL, NULL, NULL,INTEGER }, //BeeperRelease
				{BEEPERERROR		, 49,&CurrentSetup.BeeperError, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //BeeperError
				{BEEPERALARM		, 50,&CurrentSetup.BeeperAlarm, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //BeeperAlarm
				{PSFREQUENCY		, 51,&RadioIndex, UInt16, NULL, NULL, GetPSFreq,SetPSFrequency,INTEGER }, //SetPSFreq

				{PSWATT				, 52,&CurrentSetup.PSWatt, sint32, NULL, NULL, NULL,
										  StorePSWattage,WATTS }, //SetPSWatts
				{PSTYPE				, 53,&CurrentSetup.PSType, boolean, NULL, NULL, NULL, NULL,INTEGER }, //SetPsChoice
				{ALLEMPTY			, 54,&LineBuffer, arr, NULL, NULL, NULL, NULL,INTEGER }, //PasswordSaveCommand
				{ALLEMPTY			, 55,NULL, nothing, NULL, NULL, NULL,
										  CheckForPrintingOrWelding,INTEGER }, //VGAActIOMenu

				{ULSLOGICCUSTOM		, 56,&CurrentSetup.ULSLogicCustom, boolean, NULL, NULL, NULL,
										  CheckForCustomAct,INTEGER }, //ULS
				{GNDDETLOGIC		, 57,&CurrentSetup.GndDetLogicCustom, boolean, NULL, NULL,
										  NULL, CheckForCustomAct,INTEGER }, //GndDet

				{ALLEMPTY			, 58,&BUCMenuRAM.VelocityPC, sint32, NULL, NULL, NULL, NULL,VELOCITY }, //SetVelocityPC
				{ALLEMPTY			, 59,&BUCMenuRAM.ForcePC, sint32, NULL, NULL, NULL, NULL,FORCE }, //SetForcePC
				{MINTRIGFORCE		, 60,&CurrentSetup.MinTrigForce, sint32, NULL, NULL, NULL,
										  NULL,FORCE }, //SetMinTrigger
				{METRIC3FLAG		, 61,&CurrentSetup.Metric3Flag, boolean, NULL,
										  (UINT16 *) &CurrentSetup.Units, NULL, UpdateRunTopLine,INTEGER }, //MetricChoice
				{ALLEMPTY			, 62,NULL, nothing, NULL, NULL, NULL,
										  CheckForPrintingOrWelding,INTEGER }, //VGAUserIOMenu
				{WELDSCALEINDEX		, 63,&RadioIndex, UInt16, NULL, NULL, GetWeldScaleIndex,
										  SetWeldScaleIndex,INTEGER }, //WeldScaleChoice
				{ALLEMPTY			, 64,&RadioIndex, UInt16, NULL, NULL, GetTestScaleIndex,
										  SetTestScaleIndex,INTEGER }, //TestScaleChoice

				{ALLEMPTY			, 65,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //TimeDisplay
				{ALLEMPTY			, 66,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //PkPwrDisplay
				{ALLEMPTY			, 67,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //EnergyDisplay
				{ALLEMPTY			, 68,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //VelocityDisplayAed
				{ALLEMPTY			, 69,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //VelocityDisplayAef
				{ALLEMPTY			, 70,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //FreqMinDisplay
				{ALLEMPTY			, 71,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //FreqMaxDisplay
				{ALLEMPTY			, 72,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //FreqStartDisplay
				{ALLEMPTY			, 73,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //FreqEndDisplay
				{ALLEMPTY			, 74,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
						               	  SaveWeldParamState,INTEGER }, //FreqChgDisplay
				{ALLEMPTY			, 75,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //SetAmpADisplay
				{ALLEMPTY			, 76,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //SetAmpBDisplay`
				{ALLEMPTY			, 77,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //WeldAbsDisplay
				{ALLEMPTY			, 78,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //ActPressDisplay
				{ALLEMPTY			, 79,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //TotalAbsDisplay
				{ALLEMPTY			, 80,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //WeldColDisplay
				{ALLEMPTY			, 81,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //TotalColDisplay
				{ALLEMPTY			, 82,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //WeldForceDisplay
				{ALLEMPTY			, 83,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //SetPressureADisplay,
				{ALLEMPTY			, 84,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //SetPressureBDisplay,
				{ALLEMPTY			, 85,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //PresetNumDisplay
				{ALLEMPTY			, 86,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //CycleTimeDisplay
				{ALLEMPTY			, 87,&RadioIndex, UInt16, NULL, NULL, NULL,
										  ChangeDisplayColumn,INTEGER }, //VGARadioColumnOk

				{J3_32_IN			, 88,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_32_Input
				{J3_33_IN			, 89,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_33_Input
				{J3_19_IN			, 90,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_19_Input
				{J3_17_IN			, 91,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_17_Input
				{J3_31_IN			, 92,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_31_Input
				{J3_1_IN			, 93,&RadioIndex, UInt16, NULL, NULL, GetInput,
										  SetInputSelection,INTEGER }, //J3_1_Input

				{J3_8_OUT			, 94,&RadioIndex, UInt16, NULL, NULL, GetOutput,
										  SetOutputSelection,INTEGER }, //J3_8_OutputSwap & J3_8_Output
				{J3_36_OUT			, 95,&RadioIndex, UInt16, NULL, NULL, GetOutput,
										  SetOutputSelection,INTEGER }, //J3_36_OutputSwap & J3_36_Output
				{J3_22_OUT			, 96,&RadioIndex, UInt16, NULL, NULL, GetOutput,
										  SetOutputSelection,INTEGER }, //J3_22_Output

				{USERINLOGIC		, 97,&CurrentSetup.UserInLogic, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //InputsActiveState
				{PARTCLAMPDELAY		, 98,&CurrentSetup.PartClampDelay, sint32, NULL, NULL, NULL, NULL,INTEGER }, //Part Clamp Delay

				{ALLEMPTY			, 99,NULL, nothing, NULL, NULL, NULL, OkToDefault,INTEGER }, //VGADefaultIOOk

				{ALLEMPTY			, 100,&CurrentPreset.WeldMode, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //WeldSetupChoice /*not to be used*/
				{WELDMODE			, 101,&RadioIndex, UInt16, NULL, NULL, GetWeldMode,
										  SetWeldMode,INTEGER }, //WeldModeMenuTime
				{WELDTIME			, 102,&CurrentPreset.WeldTime, sint32, NULL, NULL, NULL, NULL,TIME }, //VGAWeldTimeTime
				{HOLDTIME			, 103,&CurrentPreset.HoldTime, sint32, NULL,
										  &CurrentPreset.HoldTimeFlag, NULL, NULL,TIME }, //VGAHoldTime1
				{TRIGGERFORCE		, 104,&CurrentPreset.TriggerForce, sint32,
						        		  &FlagTriggerByForce, NULL, SetupTriggerFlags, NULL,FORCE }, //VGATriggerForce
				{EXTTRGDELAY		, 105,&CurrentPreset.ExtTrgDelay, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGAExtTriggerDelayChoice

				{AMPSTEPFLAG		, 106,&RadioIndex, UInt16, NULL, NULL,
										  PrepareAmplitudeRadioMenu, SetAmplitudeModes,INTEGER }, //radioAmplitudeMode
				{AMP_1				, 107,&CurrentPreset.Amp1, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi, NULL, NULL, NULL,PERCENT }, //AmplitudeA
				{AMP2				, 108,&CurrentPreset.Amp2, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi, NULL, NULL, NULL,PERCENT }, //AmplitudeB
				{AMPTRIGTIMEVALUE	, 109,&CurrentPreset.AmpTrigTimeValue, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi,
										  &CurrentPreset.Amp2Flag, NULL, SelectAmpTriggerTime,TIME }, //AmpStepAtTime
				{AMPTRIGENERVALUE	, 110,&CurrentPreset.AmpTrigEnerValue, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi,
										  &CurrentPreset.Amp2Flag, NULL, SelectAmpTriggerEnergy,ENERGYDIV10 }, //AmpStepAtEner
				{AMPTRIGPOWERVALUE	, 111,&CurrentPreset.AmpTrigPowerValue, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi,
										  &CurrentPreset.Amp2Flag, NULL, SelectAmpTriggerPower,PERCENTX10 }, //AmpStepAtPower
				{AMPTRIGCOLVALUE	, 112,&CurrentPreset.AmpTrigColValue, sint32,
										  &AmplitudeStepEnableFlag.Uint16.Hi,
										  &CurrentPreset.Amp2Flag, NULL, SelectAmpTriggerDist,DISTANCE }, //AmpStepAtDist
				{AMPTRIGEXTFLAG		, 113,&CurrentPreset.AmpTrigExtFlag, UInt16, &AmpStepEnable,
										  NULL, SetupAmpModeStepFlag, SelectAmpTriggerExt,INTEGER }, //AmpStepExt(choice)
				{AMP1				, 114,&CurrentPreset.Amp1, sint32, &AmpCntrlInt,
										 NULL, SetAmpControlValue, NULL,PERCENT }, //VGAAmplitude1
				{WELDTRIGGER		, 115,&CurrentPreset.WeldTrigger, boolean, NULL, NULL,
										  SetupTriggerFlags, NULL,INTEGER }, //radioPretriggerMode
				{WELDENERGY			, 116,&CurrentPreset.WeldEnergy, sint32, NULL, NULL, NULL,
										  NULL,ENERGYDIV10 }, //VGAWeldEnergyEnergy
				{PEAKPWR			, 117,&CurrentPreset.PeakPwr, sint32, NULL, NULL, NULL, NULL,PERCENTX10 }, //VGAPeakPowerPP
				{COLDIST			, 118,&CurrentPreset.ColDist, sint32, NULL, NULL, NULL, NULL,DISTANCE }, //VGACollapseColl
				{ABSDIST			, 119,&CurrentPreset.AbsDist, sint32, NULL, NULL, NULL, NULL,DISTANCE }, //VGAAbsoluteAbs
				{SCRUBTIME			, 120,&CurrentPreset.ScrubTime, sint32, NULL,
										  &CurrentPreset.ScrubTimeFlag, NULL, NULL,TIME }, //VGAScrubTimeGndDet
				{AMPSCRUBTIME		, 121,&CurrentPreset.AmpScrubTime, sint32, NULL, NULL, NULL,
										  NULL,PERCENT }, //AmpGroundDetect
				{ABFLAG				, 122,&CurrentPreset.AbFlag, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //VGAAfterburstChoice
				{ABDELAY			, 123,&CurrentPreset.AbDelay, sint32, NULL, NULL, NULL, NULL,TIME }, //ABDelayTime
				{ABTIME				, 124,&CurrentPreset.AbTime, sint32, NULL, NULL, NULL, NULL,TIME }, //ABTimeTime
				{ABAMP				, 125,&CurrentPreset.AbAmp, sint32,
										  &AmpControlInternal.Uint16.Hi, NULL,
										  SetAmpControlValue, NULL,PERCENT }, //ABAmplitude
				{PRETRIGFLAG		, 126,&RadioIndex, UInt16, NULL, NULL,
										  PreparePretriggerRadioMenu, SetPretriggerModes,INTEGER }, //radioPretriggerMode
				{PRETRIGDIST		, 127,&CurrentPreset.PreTriggerDistance, sint32, &FlagPretriggerDist,
										  NULL, NULL, NULL,DISTANCE }, //varPretrigDist
				{PRETRIGDELAY		, 128,&CurrentPreset.PreTrigDelay, sint32,
										  &FlagPretriggerTime, NULL, NULL, NULL,TIME }, //varPretrigTime
				{PRETRIGAMP			, 129,&CurrentPreset.PreTrigAmp, sint32, &FlagPretriggerAmpl,
										  NULL, NULL, NULL,PERCENT }, //varPretrigAmplitude
				{PMCENABLED			, 130,&CurrentPreset.PMCEnabled, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGAPwrMatchCurve

				///***************************************************************************************************** VGARejectLimitsChoice ************************************************************************************/
				{REJECTLIMITSFLAG	, 131,&CurrentPreset.RejectLimitsFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //VGARejectLimitsChoice
				{REJRESET_REQFLAG	, 132,&CurrentPreset.RejResetRequiredFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //ResetRequiredRLimit
				{TIMEPLR			, 133,&CurrentPreset.TimePLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,TIME }, //PTimeREnergy
				{TIMEMLR			, 134,&CurrentPreset.TimeMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,TIME }, //MTimeREnergy
				{ENERGYPLR			, 135,&CurrentPreset.EnergyPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,ENERGYDIV10 }, //PEnergyRTime
				{ENERGYMLR			, 136,&CurrentPreset.EnergyMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,ENERGYDIV10 }, //MEnergyRTime
				{POWERPLR			, 137,&CurrentPreset.PowerPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,PERCENTX10 }, //PPkPowerRLimit
				{POWERMLR			, 138,&CurrentPreset.PowerMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,PERCENTX10 }, //MPkPowerRLimit
				{COLPLR				, 139,&CurrentPreset.ColPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //PColDistRLimit
				{COLMLR				, 140,&CurrentPreset.ColMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //MColDistRLimit
				{ABSPLR				, 141,&CurrentPreset.AbsPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //PAbsDistRLimit
				{ABSMLR				, 142,&CurrentPreset.AbsMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //MAbsDistRLimit
				{TRSDISTPLR 		, 143,&CurrentPreset.TrsDistPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //PTrigDistRLimit
				{TRSDISTMLR			, 144,&CurrentPreset.TrsDistMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,DISTANCE }, //MTrigDistRLimit
				{WELDFORCEPLR		, 145,&CurrentPreset.WeldForcePLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RejectLimits, NULL, NULL,FORCE }, //PMaxForceRLimit
				{WELDFORCEMLR		, 146,&CurrentPreset.WeldForceMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
									      &CurrentPreset.RejectLimits, NULL, NULL,FORCE }, //MMaxForceRLimit
				{PS_SBLMAXFREQ		, 147,&CurrentPreset.SBLMaxFreq, sint32,
										  &CurrentSetup.SBLEnable, &CurrentPreset.SBLFreqFlags,
										  NULL, NULL,FREQUENCY }, //PSBLFreqLimit
				{PS_SBLMINFREQ		, 148,&CurrentPreset.SBLMinFreq, sint32,
										  &CurrentSetup.SBLEnable, &CurrentPreset.SBLFreqFlags,
										  NULL, NULL,FREQUENCY }, //MSBLFreqLimit

				///***************************************************************************************************** VGASuspectLimitsChoice *************************************************************************************/
				{SUSPECTLIMITSFLAGS	, 149,&CurrentPreset.SuspectLimitsFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //VGASuspectLimitsChoice
				{SUSRESET_REQ		, 150,&CurrentPreset.SusResetRequired, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //ResetRequiredSLimit
				{TIMEPLS			, 151,&CurrentPreset.TimePLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,TIME }, //PTimeSEnergy
				{TIMEMLS			, 152,&CurrentPreset.TimeMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,TIME }, //MTimeSEnergy
				{ENERGYPLS			, 153,&CurrentPreset.EnergyPLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,ENERGYDIV10 }, //PEnergySTime
				{ENERGYMLS			, 154,&CurrentPreset.EnergyMLS, sint32,
								  		  &CurrentPreset.SuspectLimitsFlag,
								  		  &CurrentPreset.SuspectLimits, NULL, NULL,ENERGYDIV10 }, //MEnergySTime
				{POWERPLS			, 155,&CurrentPreset.PowerPLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,PERCENTX10 }, //PPkPowerSLimit
				{POWERMLS			, 156,&CurrentPreset.PowerMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,PERCENTX10 }, //MPkPowerSLimit
				{COLPLS				, 157,&CurrentPreset.ColPLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //PColDistSLimit
				{COLMLS				, 158,&CurrentPreset.ColMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //MColDistSLimit
				{ABSPLS				, 159,&CurrentPreset.AbsPLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //PAbsDistSLimit
				{ABSMLS				, 160,&CurrentPreset.AbsMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //MAbsDistSLimit
				{TRSDISTPLS			, 161,&CurrentPreset.TrsDistPLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //PTrigDistSLimit
				{TRSDISTMLS			, 162,&CurrentPreset.TrsDistMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,DISTANCE }, //MTrigDistSLimit
				{WELDFORCEPLS		, 163,&CurrentPreset.WeldForcePLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,FORCE }, //PMaxForceSLimit
				{WELDFORCEMLS		, 164,&CurrentPreset.WeldForceMLS, sint32,
										  &CurrentPreset.SuspectLimitsFlag,
										  &CurrentPreset.SuspectLimits, NULL, NULL,FORCE }, //MMaxForceSLimit

				///***************************************************************************************************** VGAForceChoiceStep / Fixed ************************************************************************************/
				{ALLEMPTY			, 165,&RadioIndex, UInt16, NULL, NULL, PreparePressureRadioMenu,
										  SetPressureModes,INTEGER }, //radioPressureMenu
				{BEEPERESTOP		, 166,&CurrentSetup.BeeperEstop, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //BeeperAlarm
				{HORNCLAMP			, 167,&CurrentSetup.HornClamp, boolean, NULL, NULL, NULL, NULL,INTEGER },
				{UDISCAN			, 168,&CurrentSetup.UDIScan, boolean, NULL, NULL, NULL, SetUDIflag,INTEGER },
				{AUTOMATION			, 169,&CurrentSetup.Automation, boolean, NULL, NULL, NULL, SetAutomationUserId,INTEGER },
				{MEMORYFULL			, 170,&CurrentSetup.MemoryFull, boolean, NULL, NULL, NULL, NULL,INTEGER },
				{USERIDTABLE		, 171,&CurrentSetup.UserIDTable, boolean, NULL, NULL, NULL,
										   NULL,INTEGER },
				{AUTHORITYCHECK		, 172,&CurrentSetup.AuthorityCheck, boolean, NULL, NULL, NULL,
										  SetAuthorityForFirmware,INTEGER },

				///***************************************************************************************************** EnergyBrakingChoice  *******************************************************************************************/
				{ENERGYBRAKING		, 173,&CurrentPreset.EnergyBraking, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //EnergyBrakingChoice
				{EBTIME				, 174,&CurrentPreset.EBTime, sint32, NULL, NULL, NULL, NULL,TIME }, //EBTime
				{TRIGGERDISTANCE	, 175,&CurrentPreset.TriggerDistance, sint32, &FlagTriggerByDist,
										  NULL, SetupTriggerFlags, NULL,DISTANCE }, //VGATriggerForce
				{ALLEMPTY			, 176,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_21
				{SEEKFUNFLAG		, 177,&CurrentPreset.SeekFunFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGAPostWeldSeekChoice

				///***************************************************************************************************** VGAFreqOffsetChoice  *******************************************************************************************/
				{FREQOFFSETFLAG		, 178,&CurrentPreset.FreqOffsetFlag, UInt16, &FreqControlInt,
										  NULL, SetFreqControlValue, NULL,INTEGER }, //VGAFreqOffsetChoice
				{PS_FREQOFFSET		, 179,&CurrentPreset.FreqOffset, sint32,
										  &FreqControlInternal.Uint16.Hi, NULL, NULL, NULL,FREQOFFSET }, //FreqOffset

				///***************************************************************************************************** VGAActClearOutputChoice  ***************************************************************************************/
				{ACTCLEARFLAG		, 180,&CurrentPreset.ActClrFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGAActClearOutputChoice
				{ACTCLEARDIST		, 181,&CurrentPreset.ActClrDistance, sint32, NULL, NULL, NULL,
										  NULL,DISTANCE }, //Distance

				///***************************************************************************************************** VGAControlLimitsChoice1 /Choice2 *******************************************************************************/
				{CONTROLLIMITSFLAG	, 182,&CurrentPreset.ControlLimitsFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //VGAControlLimitsChoice1 /Choice2
				{ENERGYCOMPFLAG		, 183,&CurrentPreset.EnergyCompFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //EnergyCompChoice
				{ENERGYPL			, 184,&CurrentPreset.EnergyPL, sint32, NULL, NULL, NULL, NULL,ENERGY }, //MaxEnergyComp
				{ENERGYML			, 185,&CurrentPreset.EnergyML, sint32, NULL, NULL, NULL, NULL,ENERGY }, //MinEnergyComp
				{PEAKPOWERCUTOFF	, 186,&CurrentPreset.PeakPwrCutoff, sint32, NULL,
										  &CurrentPreset.PeakPwrCutoffFlag, NULL, NULL,PERCENTX10 }, //PeakPowerCutoff
				{ABSCUTOFFDIST		, 187,&CurrentPreset.ABSCutoffDist, sint32, NULL,
										  &CurrentPreset.ABSCutoffFlag, NULL, NULL,DISTANCE }, //ABSCutoff
				{COLLCUTOFFDIST		, 188,&CurrentPreset.ColCutoffDist, sint32, NULL,
										  &CurrentPreset.ColCutoffFlag, NULL, NULL,DISTANCE }, //CollapseCutoff

				///***************************************************************************************************** VGACycleAbortsChoice1 /Choice2 **********************************************************************************/
				{CYCLEABORTFLAG		, 189,&CurrentPreset.CycleAbortFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGACycleAbortsChoice1 /Choice2
				{GROUNDDETECTFLAG	, 190,&CurrentPreset.GndDetectFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //GndDetChoice
				{MISSINGPARTFLAG	, 191,&CurrentPreset.MissingPartFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //MissingPart
				{MISSINGPARTMAX		, 192,&CurrentPreset.MissingPartMax, sint32, NULL,
										  &CurrentPreset.MissingMaxFlag, NULL, NULL,DISTANCE }, //MissingPartMaximum
				{MISSINGPARTMIN		, 193,&CurrentPreset.MissingPartMin, sint32, NULL,
										  &CurrentPreset.MissingMinFlag, NULL, NULL,DISTANCE }, //MissingPartMinimum

				{RTFLAG				, 194,&CurrentPreset.RTFlag, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //VGARapidTraverseChoice
				{RTDIST				, 195,&CurrentPreset.RTDist, sint32, &CurrentPreset.RTFlag,
										  NULL, NULL, NULL,DISTANCE }, //StepAtRTDist
				{ALLEMPTY			, 196,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_34
				///********************************************************************************************************************** DigitalUPS **************************************************************************************/
				{DUPSMEMFLAG		, 197,&DUPS_Info.DUPSMemFlag, boolean, NULL, NULL, NULL,
										  DUPS_ModifySWDipSetting,INTEGER }, //MemorySetup
				{WELDRAMPTIME		, 198,&CurrentPreset.DUPS_HostParamSet.WeldRampTime, sint32,
										  NULL, NULL, NULL, ChangeDUPSSubParamList,TIME }, //RTime
				{SEEKTIME			, 199,&CurrentPreset.DUPS_HostParamSet.SeekTime, sint32, NULL,
										  NULL, NULL, ChangeDUPSSubParamList,TIME }, //STime
				{DUPS_SEEK_FLAG		, 200,&DUPS_Info.DUPSSeekFlag, boolean, NULL, NULL, NULL,
									  DUPS_ModifySWDipSetting,INTEGER }, //DupsTimedSeek
				{SWDIPSETTING		, 201,&DUPS_Info.DUPSMemRstFlag, boolean, NULL, NULL, NULL,
									  DUPS_ModifySWDipSetting,INTEGER }, //MemoryResetSetup
				{WELDSTATUSFLAG		, 202,&CurrentPreset.WeldStatusFlag, boolean, NULL, NULL,
										  NULL, UpdateWS_Config,INTEGER }, //DupsWeldStatus

				///********************************************************************************************************************** VGAForceRampsMenu *******************************************************************************/
				{ALLEMPTY			, 203,&RadioIndex, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //WeldFRate
				{ALLEMPTY			, 204,&RadioIndex, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //StepFRate
				{ALLEMPTY			, 205,&RadioIndex, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //HoldFRate
				{MAXTIMEOUT			, 206,&CurrentPreset.MaxTimeout, sint32, NULL, NULL, NULL,
										  NULL,TIME }, //VGAMaxTimeout

				{PS_FREQOFFSET		, 207,NULL, nothing, NULL, NULL, NULL, ChangeFreqOffsetSign,FREQOFFSET }, //ChangeFreqSign
				{AMPCONTROL			, 208,&CurrentSetup.AmpControl, boolean, &AmpCntrlExt, NULL,
										  SetAmpControlValue, ProduceBeep,INTEGER }, //AmplitudeExt
				{FREQCONTROL		, 209,&CurrentSetup.FreqControl, boolean,
										  &FreqControlExternal, NULL, SetFreqControlValue,
										  ProduceBeep,INTEGER }, //VGAFreqOffsetExt
				{WRITEIN1			, 210,&CurrentPreset.WriteIn1, arr, NULL, NULL, NULL, NULL,STRING }, //VGAWriteInSubmenu
				{WRITEIN2			, 211,&CurrentPreset.WriteIn2, arr, NULL, NULL, NULL, NULL,STRING }, //VGAWriteInSubmenu
				{ALLEMPTY			, 212,&DebugTitle, str, NULL, NULL, NULL, NULL,INTEGER }, //TitleDebug
				{ALLEMPTY			, 213,&DebugBase, boolean, &BinEnable, NULL, NULL,
										  ChangeBaseAndWordLength,INTEGER }, //toggleDebugBaseBinary

				///********************************************************************************************************************** VGAPresetsChoice ********************************************************************************/
				{ALLEMPTY			, 214,&VGAPresetNum, UInt16, NULL, NULL,
										  PreparePrstInfoString, PreparePrstSaveTitle,INTEGER }, //VGAPresetSave
				{ALLEMPTY			, 215,&VGAPresetNum, UInt16, NULL, NULL, GetPresetNum, NULL,INTEGER }, //VGAPresetsChoice
				{ALLEMPTY			, 216,&VGAPresetNum, UInt16, NULL, NULL, NULL, SaveNamedPreset,INTEGER }, //VGAAutoName
				{ALLEMPTY			, 217,&OldSameName, str, &OldSameNameAvailable, NULL, NULL,
										  SaveNamedPreset,INTEGER }, //VGASameNameAsOld
				{ALLEMPTY			, 218,&NewSameName, str, &NewSameNameAvailable, NULL, NULL,
										  SaveNamedPreset,INTEGER }, //VGASameNameAsNew
				{ALLEMPTY			, 219,&AssignNamePresetBuffer, arr, NULL, NULL, NULL,
										  SaveNamedPreset,INTEGER }, //VGAAssignName

				{ALLEMPTY			, 220,&PresetListBoxBuffer, arr, NULL, NULL, NULL, NULL,INTEGER }, //SendVGAListBox
				{ALLEMPTY			, 221,&VGAPresetNum, UInt16, NULL, NULL, NULL,
										  SetPresetClearFlags,INTEGER }, //VGAPresetClear
				{ALLEMPTY			, 222,&VGAPresetNum, UInt16, NULL, NULL, NULL,
										  ProcessPresetClear,INTEGER }, //VGAClearOk
				{ALLEMPTY			, 223,&VGAPresetNum, UInt16, NULL, NULL, NULL,
										  ProcessPresetRecall,INTEGER }, //VGAPresetRecall
				{ALLEMPTY			, 224,&VGAPresetNum, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //VGAPresetVerify
				{ALLEMPTY			, 225,&PresetListBoxBuffer, arr, NULL, NULL, NULL, NULL,INTEGER }, //VGAPresetInfo
				{ALLEMPTY			, 226,&VGAPresetNum, UInt16, NULL, NULL, NULL,
										  PreparePrstInfoString,INTEGER }, //VGAPresetInfo
				{ALLEMPTY			, 227,&VGAPresetNum, UInt16, NULL, NULL, NULL, PresetSaveOk,INTEGER }, //VGASaveOk
				{ALLEMPTY			, 228,&VGAPresetNum, UInt16, NULL, NULL, NULL,
										  PresetSaveCancel,INTEGER }, //VGASaveCancel
				{ALLEMPTY			, 229,NULL, nothing, NULL, NULL, NULL, EraseSeqList1,INTEGER }, //Erase Sequencing list

				///********************************************************************************************************************** VGASequenceEnable *********************************************************************************/
				{ALLEMPTY			, 232,&TempSequenceNos, UInt16, NULL, NULL, GetSequenceNos,
										  NULL,INTEGER }, //VGASequenceEnable
				{SEQUENCEENABLE		, 233,&CurrentSetup.SequenceEnable, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //SeqEnableToggle
				{ALLEMPTY			, 234,NULL, nothing, NULL, NULL, NULL, EraseSeqList,INTEGER }, //Erase Sequencing list
				{ALLEMPTY			, 235,&PresetListBoxBuffer, arr, NULL, NULL, NULL, NULL,INTEGER }, //SendSeqListBox
				{SEQUENCELIST		, 236,&CurrentSetup.SequenceList, arr, NULL, NULL, NULL, NULL,INTEGER }, //Store Seq. List
				{SEQUENCENOS		, 237,&CurrentSetup.SequenceNos, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //Change Seq.List

                { PRESSURE2_FLAG, 238, &RadioIndex, UInt16, NULL, NULL, PreparePressureRadioMenu, SetPressureModes, INTEGER },   //radioPressureMenu
                { PRESSURE_1, 239, &CurrentPreset.WeldPressure, sint32, &PressureStepEnableFlag.Uint16.Hi, NULL, NULL,
                						  UpdatePressureValue, PRESSURE2 },    //WeldPressure
                { PRESSURE_2, 240, &CurrentPreset.Pressure2, sint32, &PressureStepEnableFlag.Uint16.Hi, NULL, NULL, NULL,
                						  PRESSURE2 },    //Pressure2
                { PRESSURE_TRIGTIMEVALUE, 241, &CurrentPreset.PressureTrigTimeValue, sint32, &PressureStepEnableFlag.Uint16.Hi,
					  &CurrentPreset.Pressure2Flag, NULL, SelectPressureTriggerTime, INTEGER },    //PressureStepAtTime
                { PRESSURE_TRIGENERVALUE, 242, &CurrentPreset.PressureTrigEnerValue, sint32, &PressureStepEnableFlag.Uint16.Hi,
					  &CurrentPreset.Pressure2Flag, NULL, SelectPressureTriggerEnergy, INTEGER },    //PressureStepAtEner
                { PRESSURE_TRIGPOWERVALUE, 243, &CurrentPreset.PressureTrigPowerValue, sint32, &PressureStepEnableFlag.Uint16.Hi,
					  &CurrentPreset.Pressure2Flag, NULL, SelectPressureTriggerPower, INTEGER },    //PressureStepAtPower
                { PRESSURE_TRIGCOLVALUE, 244, &CurrentPreset.PressureTrigColValue, sint32, &PressureStepEnableFlag.Uint16.Hi,
					  &CurrentPreset.Pressure2Flag, NULL, SelectPressureTriggerDist, DISTANCE },    //PressureStepAtCol
                { PRESSURE_TRIGEXTFLAG, 245, &CurrentPreset.PressureTrigExtFlag, UInt16, &PressureStepEnable, NULL,
					  SetupPressureFixedOrStepFlag, SelectPressureTriggerExt, INTEGER },    //PressureStepExt(choice)

				///********************************************************************************************************************** VGAPrintingChoice *********************************************************************************/
				{ALLEMPTY			, 254,NULL, nothing, NULL, NULL, NULL, NULL,INTEGER }, //VGAPrintingChoice
				{OPERATORAUTH		, 255,&RadioIndex, UInt16, NULL, NULL, GetOpAuthority,
										  SetOpAuthority,INTEGER }, //Oerator Authority
				{AUTOSCALEFLAG		, 257,&CurrentPreset.AutoScaleFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //XAutoScale
				{XSCALETIME			, 258,&CurrentPreset.XScaleTime, sint32, NULL, NULL, NULL,
										  NULL,TIME },
				{HISTORYSETUP			, 259,&RadioIndexL, Uint32, NULL, NULL, GetWeldHistSetup,
										  SetWeldHistSetup,INTEGER },
				{BARCODESTART		, 260,&CurrentSetup.BarcodeStart, arr, NULL, NULL, NULL, NULL,STRING }, //VGAWriteInSubmenu
				{BASICEXPERT		, 261,&CurrentSetup.BasicExpert, boolean, NULL, NULL, NULL,
										  NULL,INTEGER }, //BeeperAlarm
				{ ALLEMPTY,262, NULL, nothing, NULL, NULL, NULL, SpeedDown,INTEGER },
				{STACKASSEMBLYNUM   , 263,&CurrentSetup.StackAssemblyNum, arr, NULL, NULL, NULL,
										   AssemblyNumberChangeEventRecord,STRING }, //PowerSupplySerialNumber / SetPSSerNum
				{HWVERIFY			, 264,&CurrentSetup.HWVerify, UInt16, NULL, NULL, GetCurrentHWVerify, ComponentVerifyChangeEventRecord,INTEGER }, //FreqEndDisplay
				{BATCHFUNCTION		, 265,&CurrentPreset.BatchFunction, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //BatchEnable
				{BATCHCOUNTWITHALARM, 266,&CurrentPreset.BatchCountWithAlarm, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //Batch count with alarm
				{BATCHCOUNTRESET	, 267,&CurrentPreset.BatchCountReset, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //Reset Batch count on alarm reset
				{BATCHCOUNT			, 268,&CurrentPreset.BatchCount, sint32, NULL, NULL, NULL,
										  NULL,COUNTER },//Batch count settings
				{PPRESSURELIMITFLAG	, 269,&CurrentPreset.PressureLimitFlag, UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //VGASuspectLimitsChoice
				{MPRESSURELIMIT		, 270,&CurrentPreset.MPressureLimit, sint32,
										  &CurrentPreset.PressureLimitFlag,
										  &CurrentPreset.PressureLimits, NULL, NULL,PRESSURE },
				{PS_PPRESSURELIMIT	, 271,&CurrentPreset.PPressureLimit, sint32,
										  &CurrentPreset.PressureLimitFlag,
										  &CurrentPreset.PressureLimits, NULL, NULL,PRESSURE },
				{WELDPRESSURE, WELD_PRESSURE_ID,&CurrentPreset.WeldPressure, sint32, NULL, NULL, NULL,
										  UpdatePressureValue, PRESSURE2 },
				{HOLDPRESSURE		, 273,&CurrentPreset.HoldPressure, sint32, &CurrentPreset.HoldPressureFlag, NULL, NULL,
										  SetHoldPressure,PRESSURE2 },
				{FLOWCONTROL, FLOW_CONTROL_ID,&TempFlowValue, sint32, NULL, NULL, GetDownSpeed,
										  UpdateFlowValue, PERCENT },
				{ALLEMPTY			, 275,&CurrentSetup.Reserved, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //BeeperAlarm
				{ ALLEMPTY          , 276, NULL, nothing, NULL, NULL, NULL, SpeedUp,INTEGER },
				{ALLEMPTY					, 277,&useridData.Password, arr, NULL, NULL, NULL, NULL,INTEGER }, //user password
				{ALLEMPTY					, 278,&useridData.UserId, arr, NULL, NULL, NULL, NULL,INTEGER }, //user id
				{ALLEMPTY					, 279,&RadioIndex, UInt16, NULL, NULL, GetUserLevel,
										  SetUserLevel,INTEGER }, //user level
				{ALLEMPTY					, 280,&useridData.Status, boolean, NULL, NULL, NULL, NULL,INTEGER }, //user status
				{ALLEMPTY					, 281,&useridData.PassExpTime, Uint32, NULL, NULL, NULL, NULL,INTEGER }, //password expire
				{ALLEMPTY					, 282,&FRAMUserIdObj.ActiveUserIDCount, sint32, NULL, NULL, NULL, NULL,INTEGER }, //ChoosePageSize
				{IDLELOGOUTTIME		, 283,&CurrentSetup.IdleLogoutTime, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //WeldsPerPageVar
				{ALLEMPTY					, 284,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_8
				{ALLEMPTY					, 285,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_22
				{ALLEMPTY					, 286,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_36
				{ALLEMPTY					, 287,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_1
				{ALLEMPTY					, 288,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_17
				{ALLEMPTY					, 289,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_19
				{ALLEMPTY					, 290,&ip_addr, arr, NULL, NULL, GetPSIpAddress, NULL,INTEGER }, //Print ip addr
				{ALLEMPTY					, 291,&mac_addr, arr, NULL, NULL, GetPSMacAddress, NULL,INTEGER }, //Print Mac Addr
				{ALLEMPTY					, 292,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_31
				{ALLEMPTY					, 293,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_32
				{ALLEMPTY					, 294,&RadioIndex, UInt16, NULL, NULL, DiagnoseIn, NULL,INTEGER }, // diagnostic input J3_33
				{ALLEMPTY					, 295,&SelectedPresetNumber, sint32, NULL, NULL,
										  SendSelectedPreset, NULL,INTEGER },
				{ALLEMPTY					, 296,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_5
				{ALLEMPTY					, 297,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_6
				{ALLEMPTY					, 298,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_20
				{ALLEMPTY					, 299,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //User ID column
				{ALLEMPTY					, 300,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //User ID column
				{ALLEMPTY					, 301,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
										  SaveWeldParamState,INTEGER }, //User ID column
				{AUTOREFRESH		, 302,&CurrentSetup.AutoRefresh, boolean, NULL, NULL, NULL,
										  NULL,INTEGER },

				///********************************************************************************************************************** VGABUCMenu *******************************************************************************************/
				{PSLIFETIMECOUNTER	, 303,&CurrentSetup.PSLifetime, sint32, NULL, NULL, NULL,
										  StorePSLifeTimeCount,COUNTER }, //SetPSLife
				{OVERLOADCOUNTER	, 304,&CurrentSetup.Overload, sint32, NULL, NULL, NULL, NULL,COUNTER }, //SetOverloads
				{GENERALALARMCOUNTER, 305,&CurrentSetup.GenAlarmCount, sint32, NULL, NULL, NULL,
										  NULL,COUNTER }, //SetGenAlarms
				{ALLEMPTY			, 306,&BUCMenuRAM.Reserved, sint32, NULL, NULL, NULL,
										  NULL,INTEGER },
				{ALLEMPTY			, 307,(void*) &BUCFactoryDefaults, sint32, NULL, NULL, NULL,
										  VGATestCheckSum,INTEGER }, //VGAFactoryDefaults
				{PMCTIMEOUT			, 308,&CurrentPreset.PMCTimeout, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //VGAPwrCurveTimeout
				{ALLEMPTY			, 309,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_35
				{ALLEMPTY			, 310,&RadioIndex, UInt16, NULL, NULL, GetRTRamp, SetRTrRamp,INTEGER }, //SetRTRamp
				{ALLEMPTY			, 311,&RadioIndex, UInt16, NULL, NULL, GetReturnRamp,
										  SetreturnRamp,INTEGER }, //SetReturnRamp
				{ALLEMPTY			, 312,&RadioIndex, UInt16, NULL, NULL, GetStartRamp,
										  SetstartRamp,INTEGER }, //SetStartRamp
				{IDLESPEED			, 313,&CurrentSetup.IdleSpeed, sint32, NULL, NULL, NULL, NULL,INTEGER }, //SetIdleSpeed
				{GAINFACTOR			, 314,&CurrentSetup.GainFactor, sint32, NULL, NULL, NULL, NULL,INTEGER }, //SetGainFactor
				{ALLEMPTY			, 315,NULL, nothing, NULL, NULL, NULL, UpdateCalibDefault,INTEGER }, //VGAUpdateCalDef
				{ALLEMPTY			, 316,&BUCMenuRAM.EnergyBrakingTime, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //SetEnergyBrakingTime
				{ALLEMPTY			, 317,&BUCMenuRAM.EnergyBrakingAmp, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //SetEnergyBrakingPercent
				{SEEKAMPLITUDE		, 318,&CurrentPreset.DUPS_HostParamSet.SeekAmplitude, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,PERCENT }, //AmplitudeFn
				{SEEKRAMPTIME		, 319,&CurrentPreset.DUPS_HostParamSet.SeekRampTime, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,TIME }, //SeekRampTimeVar
				{SEEKFREQLIMITHIGH	, 320,&CurrentPreset.DUPS_HostParamSet.SeekFreqLimitHigh,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,FREQUENCY }, //FreqHighVar
				{SEEKFREQLIMITLOW	, 321,&CurrentPreset.DUPS_HostParamSet.SeekFreqLimitLow,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,FREQUENCY }, //FreqLowVar
				{SEEKPHASELOOP		, 322,&CurrentPreset.DUPS_HostParamSet.SeekPhaseLoop, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //PhsLoop
				{SEEKPHASELOOPCF	, 323,&CurrentPreset.DUPS_HostParamSet.SeekPhaseLoopCF,
									      sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //SeekPhsLoopCF
				{SEEKAMPLOOPC1		, 324,&CurrentPreset.DUPS_HostParamSet.SeekAmplitudeLoopC1,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //AmplLoopC1
				{SEEKAMPLOOPC2		, 325,&CurrentPreset.DUPS_HostParamSet.SeekAmplitudeLoopC2,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //AmplLoopC2
				{WELDAMPLITUDE		, 326,&CurrentPreset.DUPS_HostParamSet.WeldAmplitude, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,PERCENT }, //WeldAmplitude
				{WELDRAMPTIME		, 327,&CurrentPreset.DUPS_HostParamSet.WeldRampTime, sint32,
											NULL, NULL, NULL, DUPS_QueuedDownloadPS,TIME }, //RampTime
				{WELDPHASELOOP		, 328,&CurrentPreset.DUPS_HostParamSet.WeldPhaseLoop, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //WeldPhaseLoop
				{WELDPHASELOOPCF	, 329,&CurrentPreset.DUPS_HostParamSet.WeldPhaseLoopCF,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //PhsLoopCF
				{WELDAMPLOOPC1		, 330,&CurrentPreset.DUPS_HostParamSet.WeldAmplitudeLoopC1,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //WeldAmpLoopC1
				{WELDAMPLOOPC2		, 331,&CurrentPreset.DUPS_HostParamSet.WeldAmplitudeLoopC2,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //WeldAmpLoopC2
				{WELDFREQLIMITHIGH	, 332,&CurrentPreset.DUPS_HostParamSet.WeldFreqLimitHigh,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,FREQUENCY }, //WeldHighVar
				{WELDFREQLIMITLOW	, 333,&CurrentPreset.DUPS_HostParamSet.WeldFreqLimitLow,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,FREQUENCY }, //WeldLowVar
				{WELDPHASELIMIT		, 334,&CurrentPreset.DUPS_HostParamSet.WeldPhaseLimit, sint32,
										  NULL, NULL, NULL, DUPS_QueuedDownloadPS,INTEGER }, //PhsLimit
				{WELDPHASELIMIT_TIME, 335,&CurrentPreset.DUPS_HostParamSet.WeldPhaseLimitTime,
										  sint32, NULL, NULL, NULL, DUPS_QueuedDownloadPS,TIME }, //PhaseLimits
				{ALLEMPTY			, 336,&HornScanInfo.MaximumAmplitude, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //SAmplitude
				{ALLEMPTY			, 337,&HornScanInfo.MaximumCurrent, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //SCurrent
				{ALLEMPTY			, 338,&HornScanInfo.StartFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //FreqStartVar
				{ALLEMPTY			, 339,&HornScanInfo.StopFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //FreqEndVar
				{ALLEMPTY			, 340,&HornScanInfo.FreqStep, sint32, NULL, NULL, NULL, NULL,INTEGER }, //FreqStepVar
				{ALLEMPTY			, 341,&HornScanInfo.TimeDelay, sint32, NULL, NULL, NULL, NULL,INTEGER }, //TimeDelayVar
				{ALLEMPTY			, 342,NULL, nothing, NULL, NULL, NULL, ResetHornScanValue,INTEGER }, //VGAResetScanValues
				{ALLEMPTY			, 343,&AlarmPtrRam.SetupGroup1, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg1
				{ALLEMPTY			, 344,&AlarmPtrRam.SetupGroup2, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg2
				{ALLEMPTY			, 345,&AlarmPtrRam.SetupGroup3, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg3
				{ALLEMPTY			, 346,&AlarmPtrRam.SetupGroup4, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg4
				{ALLEMPTY			, 347,&AlarmPtrRam.SetupGroup5, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg5
				{ALLEMPTY			, 348,&AlarmPtrRam.SetupGroup6, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg6
				{ALLEMPTY			, 349,&AlarmPtrRam.SetupGroup7, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg7
				{ALLEMPTY			, 350,&AlarmPtrRam.SetupGroup8, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg8
				{ALLEMPTY			, 351,&AlarmPtrRam.SetupGroup9, sint32, NULL, NULL, NULL,
								          CopyToFRAM,INTEGER }, //Seg9
				{ALLEMPTY			, 352,&AlarmPtrRam.SetupGroup10, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //Seg10
				{ALLEMPTY			, 353,&AlarmPtrRam.Overload, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //olg1
				{ALLEMPTY			, 354,&AlarmPtrRam.NoCycle, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //ncg1
				{ALLEMPTY			, 355,&AlarmPtrRam.EquipmentFailure, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //eqg1
				{ALLEMPTY			, 356,&AlarmPtrRam.CycleModified, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //cmg1
				{ALLEMPTY           , 357,&AlarmPtrRam.Reject, sint32, NULL, NULL, NULL, CopyToFRAM,INTEGER }, //prg1
				{ALLEMPTY			, 358,&AlarmPtrRam.Suspect, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //psg1
				{ALLEMPTY			, 359,&AlarmPtrRam.Warning, sint32, NULL, NULL, NULL,
										  CopyToFRAM,INTEGER }, //wag1
				///************************************************************************************************************* VGABransonDefaultMenu **********************************************************************************************/
				{ALLEMPTY			, 378,NULL, nothing, NULL, NULL, NULL, OkToDefault,INTEGER }, //VGADefaultsActuator
				{ALLEMPTY			, 379,NULL, nothing, NULL, NULL, NULL, OkToDefault,INTEGER }, //VGADefaultsBBR
				{ALLEMPTY			, 380,NULL, nothing, NULL, NULL, NULL, OkToDefault,INTEGER }, //VGADefaultsPrinting
				{ALLEMPTY			, 381,NULL, nothing, NULL, NULL, NULL, OkToDefault,INTEGER }, //VGADefaultsGlobal

				///************************************************************************************************************* VGADiagnosticMenu1  ***********************************************************************************************/
				{DIGTUNEFLAG		, 382,&CurrentSetup.DigTuneFlag, UInt16, NULL, NULL,
										  SetDiagFlag, NULL,INTEGER }, //VGADigitalTuneChoice
				{ALLEMPTY			, 383,NULL, nothing, NULL, NULL, DisableDiagnostics,
										  ColdStartEnable,INTEGER }, //VGAColdStartOk
				{ALLEMPTY			, 384,&DigTuneValue, sint32, NULL, NULL, NULL, VarDigTuneStore,INTEGER }, //DigitalFrequency
				{ACT_COLD_START		, 385,NULL, nothing, NULL, NULL, DisableDiagnostics,
										  EnableActColdStart,INTEGER }, //VGAActStartOk
				{ALLEMPTY			, 386,NULL, nothing, &BransonFunctionFlag, NULL, NULL,
										  DisableDiagnostics,INTEGER }, //VGABransonFuncSubmenu
				{ALLEMPTY			, 387,&DebugPtr, sint32, &DebugPasswordFlag, NULL, NULL,
						                  DebugReadMemory,INTEGER }, //Debug
				{ALLEMPTY			, 388,NULL, nothing, &SpecialMenuFlag, NULL, NULL, NULL,INTEGER }, //VGASpecialsSubmenu
				{ALLEMPTY			, 389,NULL, nothing, &TestingMenuFlag, NULL, NULL, NULL,INTEGER }, //VGATestingSubmenu
				{ALLEMPTY			, 390,NULL, nothing, NULL, NULL, NULL, VGARecallMinimumPreset,INTEGER }, //VGARecallMinMsg
				{ALLEMPTY			, 391,NULL, nothing, NULL, NULL, NULL, VGARecallMaximumPreset,INTEGER }, //VGARecallMaxMsg
				{ALLEMPTY			, 392,NULL, nothing, NULL, NULL, NULL,
										  VGARecallColdStartPreset,INTEGER }, //VGARecallColdStartMsg
				{ALLEMPTY			, 393,NULL, nothing, NULL, NULL, NULL, VGASaveMinimumPreset,INTEGER }, //VGASaveMinMsg
				{ALLEMPTY			, 394,NULL, nothing, NULL, NULL, NULL, VGASaveMaximumPreset,INTEGER }, //VGASaveMaxMsg
				{ALLEMPTY			, 395,NULL, nothing, NULL, NULL, NULL, VGASaveColdstartPreset,INTEGER }, //VGASaveColdstartMsg
				{ALLEMPTY			, 396,NULL, nothing, NULL, NULL, NULL, VGARestoreMinMaxPreset,INTEGER }, //VGARestoreMinMaxMsg
				{ALLEMPTY			, 397,NULL, nothing, NULL, NULL, VGARestoreColdStart,
										  RestoreFactoryColdstart,INTEGER }, //VGARestoreColdstartText
				{ALLEMPTY			, 398,NULL, nothing, NULL, NULL, NULL, EnableHornScanStart,INTEGER }, //VGAsubmenuHornscan
				{ALLEMPTY			, 399,NULL, nothing, NULL, NULL, NULL, DUPS_StartHS,INTEGER }, //VGAHSStart
				{ALLEMPTY			, 400,NULL, nothing, NULL, NULL, NULL, ProcessHSAbort1,INTEGER }, //VGAHSAbort

				/******************************************************************************************************** Horn Down  *********************************************************************************************************/
				{ALLEMPTY			, 401,NULL, nothing, NULL, NULL, DoHornDownFunc,
										  DoHornDownFunc,INTEGER }, //HornDown
				/* ** VGAHDStartMenuAEF ** */
				{ALLEMPTY			, 402,&KeepHornDown.boolEAN, boolean, NULL, NULL, NULL,
										  ProcessHDButtonPress2,INTEGER }, //HDTriggerToggle
				{HORNDOWNSPD		, 403,&CurrentSetup.HornDownSpd, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //HDDownSpeedSet
				{ALLEMPTY			, 404,&WorkingForceSet, sint32, NULL, NULL, NULL, NULL,INTEGER }, //HDWorkingForce
				{ALLEMPTY			, 405,&RapidTraverseState, UInt16, NULL, NULL, NULL, NULL,INTEGER }, //VGAHDRapidTraverse
				{ALLEMPTY			, 406,&RTTransitionDist, sint32, NULL, NULL, NULL, NULL,INTEGER }, //RTTransition
				/* ** VGAHDStartMenuAED ** */
				{ALLEMPTY			, 407,&CurrentPressure, sint32, &HDShowPressure, NULL, NULL,
										  NULL,INTEGER }, //HDSysPres
				{ALLEMPTY			, 408,NULL, nothing, &KeepHornDown.Uint16.Hi, NULL, NULL,
										  ProcessHDButtonPress1,INTEGER }, //VGARetractButton

				/***************************************************************************************************** Bottom Menu Commands ***************************************************************************************************/
				{ALLEMPTY			, 409,NULL, nothing, NULL, NULL, NULL, BottomMenuProcess,INTEGER }, //VGATheMainMenu
				{ALLEMPTY			, 410,NULL, nothing, NULL, NULL, NULL, BottomMenuProcess,INTEGER }, //WeldModeSelectMenu
				{ALLEMPTY			, 411,NULL, nothing, NULL, NULL, NULL, BottomMenuProcess,INTEGER }, //GraphMenu
				{ALLEMPTY			, 412,NULL, nothing, NULL, NULL, NULL, BottomMenuProcess,INTEGER }, //VGARunMenu

				/***************************************************************************************************** cold start & testing submenu *******************************************************************************************/
				{ALLEMPTY			, 413,NULL, nothing, NULL, NULL, DoColdStart, NULL,INTEGER }, //DoColdStart
				{ALLEMPTY			, 414,NULL, nothing, NULL, NULL, VGAActColdStart, NULL,INTEGER }, //ActColdStart
				{ALLEMPTY			, 415,NULL, nothing, NULL, NULL, VGACreateColdStartPreset,
										  EnableCreateStart,INTEGER }, //VGACreateColdstartText
				{ALLEMPTY			, 416,NULL, nothing, NULL, NULL, VGAOverwriteAllPreset,
										  OverwritePresetCheck,INTEGER }, //VGAUniquePresetsText
				{ALLEMPTY			, 417,NULL, nothing, NULL, NULL, VGAOverwriteAllPreset,
										  OverwritePresetCheck,INTEGER }, //VGASetupAlarmsText
				{ALLEMPTY			, 418,NULL, nothing, NULL, NULL, VGAOverwriteAllPreset,
										  OverwritePresetCheck,INTEGER }, //VGAColdStartAllText
				{ALLEMPTY			, 419,NULL, nothing, NULL, NULL, NULL, BankSwitchPresets,INTEGER }, //VGABankSwitchText
				{ALLEMPTY			, 420,NULL, nothing, NULL, NULL, NULL, CreateGraphData,INTEGER }, //VGACreateGraphDataText

				{TESTAMP			, 421,&CurrentPreset.TestAmp, sint32, NULL, NULL, NULL,
										  UpdateTestAmp,PERCENT }, //TestAmplitude
				{ALLEMPTY			, 422,NULL, nothing, NULL, NULL, VGAConfigureFromBUCMenu, NULL,INTEGER }, //VGACheckSum
				{ALLEMPTY			, 423,NULL, nothing, NULL, NULL, VGADebugColdStart, NULL,INTEGER }, //VGACheckSum(VGAFactoryDefaults)
				{ALLEMPTY			, 424,NULL, nothing, NULL, NULL, SetDigtalPot, NULL,INTEGER }, //VGADigitalChoiceTestMenu

				/******************************************************************************************************** Calibration Menu  *************************************************************************************************/
				{ALLEMPTY			, 425,NULL, nothing, NULL, NULL, NULL, ResetSensorCalb,INTEGER }, //VGAResetSensorOk
				{ALLEMPTY			, 426,NULL, nothing, NULL, NULL, NULL, VGARequestPressureCal,INTEGER }, //QVGAsubCalibSensor
				{ALLEMPTY			, 427,&UserPressure[0], sint32, NULL, NULL, NULL, NULL,INTEGER }, //GaugeReading
				{ALLEMPTY			, 428,NULL, nothing, NULL, NULL, NULL, SBCReadA2D3,INTEGER }, //VGAsubContinue2
				{ALLEMPTY			, 429,NULL, nothing, NULL, NULL, NULL, VGARequestActCal,INTEGER }, //VGAsubmenuCalActuator
				{ALLEMPTY			, 430,NULL, nothing, NULL, NULL, NULL, SCInitialize,INTEGER }, //VGAsubmenuStartSw1
				{ALLEMPTY			, 431,NULL, nothing, NULL, NULL, NULL, ManualSCInitialize,INTEGER }, //VGAsubmenuManual1
				{ALLEMPTY			, 432,NULL, nothing, NULL, NULL, NULL, DisableCalActKey1,INTEGER }, //VGAsubContinueForce1 / VGAsubContinue5A
				{ALLEMPTY			, 433,NULL, nothing, NULL, NULL, VGARequestActCal,
										  VGACloseCalibration,INTEGER }, //VGAsubCFM3
				{ALLEMPTY			, 434,NULL, sint32, &ErrorCodeFlag, NULL, NULL, NULL,INTEGER }, //ErrorCodeInfo
				{ALLEMPTY			, 435,&UserPressure[1], sint32, NULL, NULL, NULL, NULL,INTEGER }, //GaugeReading1
				{ALLEMPTY			, 436,NULL, nothing, NULL, NULL, NULL, SBCReadA2D4,INTEGER }, //VGAsubContinue4
				{ALLEMPTY			, 437,&UserPressure[2], sint32, NULL, NULL, NULL,
											BuildPressureTable,INTEGER }, //GaugeReading3
				{ALLEMPTY			, 438,NULL, nothing, NULL, NULL, NULL, SaveCalibPressure,INTEGER }, //VGAsubContinue5B
				{ALLEMPTY			, 439,NULL, nothing, NULL, NULL, NULL, CalibFinalCleanup,INTEGER }, //VGAsubContinueFail13
				{ALLEMPTY			, 440,&ForceV[0], sint32, NULL, NULL, NULL, NULL,INTEGER }, //varLoadCellReading1
				{ALLEMPTY			, 441,NULL, nothing, NULL, NULL, NULL, SBCReadA2D1,INTEGER }, //VGAsubContinue8
				{ALLEMPTY			, 442,&ForceV[1], sint32, NULL, NULL, NULL, NULL,INTEGER }, //varLoadCellReading3
				{ALLEMPTY			, 443,&ForceV[2], sint32, NULL, NULL, NULL, NULL,INTEGER }, //varLoadCellReading3AEF
				{ALLEMPTY			, 444,NULL, nothing, NULL, NULL, NULL, SBCReadA2DLC2,INTEGER }, //VGAsubBlank12
				{ALLEMPTY			, 445,NULL, nothing, NULL, NULL, NULL, VGABuildForceTable,INTEGER }, //VGAsubContinue12
				{ALLEMPTY			, 446,&FailedByValue, str, NULL, NULL, NULL, NULL,INTEGER }, //GaugeReading3
				/******************************************************************************************************** Weld Result Screen ***********************************************************************************************/
				{ACTIVEPRESET   	, 447,&CurrentSetup.ActivePreset, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //PresetNameText(Preset Number)
				{ALLEMPTY			, 448,&CurrentPresetName, arr, NULL, NULL,
										  GetCurrentPresetNames, NULL,INTEGER }, //PresetNameText(Preset Name)
				{ALLEMPTY			, 449,&StrWeldStateLine, arr, NULL, NULL, NULL, NULL,INTEGER }, //WeldStateText
				{WELDPARAMOPTION0	, 450,&CurrentSetup.WeldParamOption[0], UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldParamName1
				{WELDPARAMOPTION1	, 451,&CurrentSetup.WeldParamOption[1], UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldParamName2
				{WELDPARAMOPTION2	, 452,&CurrentSetup.WeldParamOption[2], UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldParamName3
				{WELDPARAMOPTION3	, 453,&CurrentSetup.WeldParamOption[3], UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldParamName4
				{WELDPARAMOPTION4	, 454,&CurrentSetup.WeldParamOption[4], UInt16, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldParamName5
				{ALLEMPTY			, 455,NULL, nothing, NULL, NULL, NULL, NULL,INTEGER }, //Param No.
				{ALLEMPTY			, 456,NULL, nothing, NULL, NULL, NULL, ProcessWindowSetup,INTEGER }, //Window Setup
				{ALLEMPTY			, 457,&DebugText1, str, NULL, NULL, NULL, NULL,INTEGER }, //textDebugData1
				{ALLEMPTY			, 458,&DebugText2, str, NULL, NULL, NULL, NULL,INTEGER }, //textDebugData2
				{ALLEMPTY			, 459,&DebugText3, str, NULL, NULL, NULL, NULL,INTEGER }, //textDebugData3
				{ALLEMPTY			, 460,&DebugText4, str, NULL, NULL, NULL, NULL,INTEGER }, //textDebugData4
				{ALLEMPTY			, 461,&DebugBase, boolean, &HexEnable, NULL, NULL,
										  ChangeBaseAndWordLength,INTEGER }, //toggleDebugBase
				{ALLEMPTY			, 462,&DebugBytes, boolean, NULL, NULL, NULL,
										  ChangeBaseAndWordLength,INTEGER }, //toggleDebugBytes
				{PMCHIGHLIMIT		, 463,&CurrentPreset.PMCHighLimit, sint32, NULL,
										  &CurrentPreset.PMCPlusBandFlag, NULL, NULL,PERCENT }, //VGAPwrUpperBand
				{PMCLOWLIMIT		, 464,&CurrentPreset.PMCLowLimit, sint32, NULL,
										  &CurrentPreset.PMCMinusBandFlag, NULL, NULL,PERCENT }, //VGAPwrLowerBand
				{ALLEMPTY			, 465,NULL, nothing, NULL, NULL, NULL, ClearPMCData,INTEGER }, //PMCDATACLEAR
				{ALLEMPTY			, 466,NULL, nothing, NULL, NULL, NULL, AddToPMCData,INTEGER }, //ADDTOPMCDATA
				/************************************************************************************** Alarm menu system *******************************************************************************************/
				{ALLEMPTY			, 467,&ActualHoldTime, sint32, NULL, NULL, NULL, NULL,INTEGER }, //TrigLostTimeHold
				{ALLEMPTY			, 468,&WeldingResults.ActualWeldTime, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //CM4Actual
				{ALLEMPTY			, 469,&WeldingResults.TotalEnergy, sint32, NULL, NULL, NULL,
									      NULL,INTEGER }, //CM6Actual
				{ALLEMPTY			, 470,&WeldingResults.ActualWeldCollapse, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //CM8Actual
				{ALLEMPTY			, 471,&ActualPeakPower, sint32, NULL, NULL, NULL, NULL,INTEGER }, //CM10Actual / PeakPwrActual
				{ALLEMPTY			, 472,&TriggerLostTime, sint32, NULL, NULL, NULL, NULL,INTEGER }, //TrigLostTime
				{ALLEMPTY			, 473,&WeldingResults.ActualAmplitudeEnd, sint32, NULL, NULL,
											NULL, NULL,INTEGER }, //CM16ActualAmpB
				{ALLEMPTY			, 474,&WeldingResults.ActualAmplitudeStart, sint32, NULL,
										   NULL, NULL, NULL,INTEGER }, //CM18ActualAmpA
				{ALLEMPTY			, 475,&WeldForceEnd, sint32, NULL, NULL, NULL, NULL,INTEGER }, //CM22ActualWeldForce
				{ALLEMPTY			, 476,&WeldingResults.ActualWeldCollapse, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //CM23Actual
				{ALLEMPTY			, 477,&RadioIndex, UInt16, NULL, NULL, ReadOut, DiagnoseOut,INTEGER }, // diagnostic output J3_4
				//   {477,  &CurrentPreset.AmpTrigForceValue,  sint32,  &AmplitudeStepEnableFlag.Uint16.Hi,&CurrentPreset.Amp2Flag,NULL,      SelectAmpTriggerForce  },   //AmpStepAtForce
				{ALLEMPTY			, 478,&Inp.PresetCode, sint32, NULL, NULL, NULL, NULL,INTEGER }, //ExtPresetRecalled
				{ACTASSEMBLYNUM		, 479,&CurrentSetup.ActAssemblyNum, arr, NULL, NULL, NULL,AssemblyNumberChangeEventRecord,STRING },
				{PSASSEMBLYNUM		, 480,&CurrentSetup.PSAssemblyNum, arr, NULL, NULL, NULL,AssemblyNumberChangeEventRecord,STRING },
				{ALLEMPTY			, 481,&MaximumForce, sint32, NULL, NULL, NULL, NULL,INTEGER }, //MaximumForceInfo
				{ALLEMPTY			, 482,&FinalResults.ActualTotalAbs, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //AbsDistActual
				{ALLEMPTY			, 483,&FinalResults.ActualWeldCollapse, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //WeldColDistActual
				{ALLEMPTY			, 484,&TestTime, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTestTime
				{ALLEMPTY			, 485,&PowerTest, sint32, NULL, NULL, NULL, NULL,INTEGER }, //TestPower
				{ALLEMPTY			, 486,&FreqChg, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTestFreqChg
				{ALLEMPTY			, 487,&WeldOLStatus.ErrorCurrent, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //OverloadTestDUPSCurrent
				{ALLEMPTY			, 488,&WeldOLStatus.ErrorFrequency, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //OverloadTestDUPSFreqAct
				{ALLEMPTY			, 489,&WeldOLStatus.ErrorPSV, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTestDUPSPhaseAct
				{ALLEMPTY			, 490,&PTSTimer, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTimePTrg
				{ALLEMPTY			, 491,&OverloadPower, sint32, NULL, NULL, NULL, NULL,INTEGER }, //PTOverloadPeakPwr
				{ALLEMPTY			, 492,&OverloadFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //PTOverloadFreq
				{ALLEMPTY			, 493,&ActualSeekTime, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTimeSeek
				{ALLEMPTY			, 494,&FinalResults.FrequencyChange, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //OverloadFreqChg
				{ALLEMPTY			, 495,&FinalResults.ActualWeldTime, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //OverloadTime
				{ALLEMPTY			, 496,&ActualAfterburstTime, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadTimeAB
				{ALLEMPTY			, 497,&ABOverloadPower, sint32, NULL, NULL, NULL, NULL,INTEGER }, //ABOverloadPeakPwr
				{ALLEMPTY			, 498,&ABOLStatus.ErrorCurrent, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadABDUPSCurrent
				{ALLEMPTY			, 499,&ABOLStatus.ErrorFrequency, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //OverloadABDUPSFreqAct
				{ALLEMPTY			, 500,&ABOLStatus.ErrorPSV, sint32, NULL, NULL, NULL, NULL,INTEGER }, //OverloadABDUPSPhaseAct
				{ALLEMPTY			, 501,&EBOverloadTimer, sint32, NULL, NULL, NULL, NULL,INTEGER }, //EBOverloadTime
				{ALLEMPTY			, 502,&EBOverloadPower, sint32, NULL, NULL, NULL, NULL,INTEGER }, //EBOverloadPeakPwr
				{ALLEMPTY			, 503,&EBOverloadFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //EBOverloadFreqChg
				{ALLEMPTY			, 504,&FinalResults.TotalEnergy, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //PeakEnergyActual
				{ALLEMPTY			, 505,&FinalResults.ActualTotalCollapse, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //ColDistActual
				{ALLEMPTY			, 506,&FinalResults.ActualTriggerDistance, sint32, NULL, NULL,
										  NULL, NULL,INTEGER }, //ActualTrigDist
				{ALLEMPTY			, 507,&ActualForceMax, sint32, NULL, NULL, NULL, NULL,INTEGER }, //ActualWeldForce
				{ALLEMPTY			, 508,&FinalResults.ActualWeldTime, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //ActualTime
				{ALLEMPTY			, 509,&ActualSBLMinFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //MActualFreq
				{ALLEMPTY			, 510,&ActualSBLMaxFreq, sint32, NULL, NULL, NULL, NULL,INTEGER }, //PActualFreq
				{ALLEMPTY			, 511,&ActualValuePMC1, sint32, NULL, NULL, NULL, NULL,INTEGER }, //PPmcActual
				{ALLEMPTY			, 512,&ActualValuePMC2, sint32, NULL, NULL, NULL, NULL,INTEGER }, //MPmcActual
				{PRETRIGFLAG		, 513,&CurrentPreset.PreTrigFlag, UInt16, NULL, NULL, NULL,
										  NULL,INTEGER }, //AlarmPretriggerChoice
				{ALLEMPTY			, 515,NULL, nothing, NULL, NULL, CheckforDisplayLock, NULL,INTEGER }, //DisplayLock Chk on Exit
				{ALLEMPTY			, 516,NULL, UInt16, &DUPS_Info.DUPSFlag, NULL, NULL, NULL,INTEGER }, //Digital UPS
				{ALLEMPTY			, 517,&SBCVersionLabel, arr, NULL, NULL, NULL, NULL,INTEGER }, //SBC Version
				{ALLEMPTY			, 518,&SWVersionLabel, arr, NULL, NULL, NULL, NULL,INTEGER }, //332 SW Version
				{ALLEMPTY			, 519,&MenuNxtPointer, Uint8, NULL, NULL, NULL, NULL,INTEGER }, //Next menu in calibration
				{ALLEMPTY			, 522,NULL, nothing, NULL, NULL, NULL, VGARequestForceCal,INTEGER },
				{ALLEMPTY			, 523,BatchCountInfo, arr, NULL, NULL, GetBatchCountInfo, NULL,INTEGER },
				{BATCH_COUNT		, 524,NULL, nothing, NULL, NULL, NULL, ClearCurrentBatchCount,INTEGER },
				{VALIDATEPS			, 525,&TempPresetValidated, boolean, NULL, NULL, GetPresetValidated, SetPresetValidated,INTEGER},
				{LOCKPS				, 526,&TempPresetLocked, boolean, NULL, NULL, GetPresetLocked, SetPresetLocked,INTEGER },
				{ALLEMPTY			, 527,NULL, nothing, NULL, NULL, NULL, SetClampAlarmMenuValue,INTEGER },
				{ALLEMPTY			, 528,&useridData.UserId, arr, NULL, (UINT16*)(&CurrentSetup.AuthorityCheck), ClearUserIdOnClamp, NULL,INTEGER }, //username
				{ALLEMPTY			, 529,&useridData.Password, arr, NULL, (UINT16*)(&CurrentSetup.AuthorityCheck), ClearPasswordOnClamp, NULL,INTEGER }, //user password
				{ALLEMPTY			, 530,&EventReasonString, arr, NULL, NULL, ClearReasonString, NULL,INTEGER },
				{ALLEMPTY			, 531,NULL, nothing, NULL, NULL, NULL, SetEventReasonFlag,INTEGER },
				{ALLEMPTY			, 532,&CurrentSetup.DownspeedTune, boolean, NULL, NULL, NULL, NULL,INTEGER },
				{ALLEMPTY			, 533,&DownspeedTuneCycles, sint32, NULL, NULL, NULL, NULL,INTEGER },
				{ALLEMPTY			, 534,NULL, nothing, NULL, NULL, NULL, SaveDownSpeedTune,INTEGER },
				{ALLEMPTY			, 535,NULL, nothing, NULL, NULL, NULL, ExitDownSpeedTune,INTEGER },
				{ALLEMPTY			, 536,NULL, nothing, NULL, NULL, NULL, SetDownspeedTuneFlag,INTEGER },
				{ALLEMPTY			, 537,&LastDownSpeedValue, sint32, NULL, NULL, NULL, NULL,INTEGER },
				{ALLEMPTY			, 538,&RadioIndex, UInt16, NULL, NULL, BuildWeldColumnStr,
									SaveWeldParamState,INTEGER }, //Hold Force column
				{ALLEMPTY			, 539, &DUPSOverloadType, Uint8, NULL, NULL, NULL, NULL, INTEGER },
				{DOWNSPEEDPLR		, 540,&CurrentPreset.VelocityPLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RVelLimitMask, NULL, NULL,VELOCITY }, //PDownspeedRLimit
				{DOWNSPEEDMLR		, 541,&CurrentPreset.VelocityMLR, sint32,
										  &CurrentPreset.RejectLimitsFlag,
										  &CurrentPreset.RVelLimitMask, NULL, NULL,VELOCITY }, //MDownspeedRLimit
			    {ALLEMPTY			, 542,&FinalResults.ActualDownspeed, sint32, NULL, NULL, NULL,
										  NULL,INTEGER }, //ActualTime
                {ALLEMPTY			, 543,NULL, nothing, NULL, NULL, NULL, EstopResetLogin,INTEGER },
				{ALLEMPTY			, 544,&useridData.UserId, arr, NULL, NULL, ClearUserIdOnClamp, NULL,INTEGER }, //username
				{ALLEMPTY			, 545,&useridData.Password, arr, NULL, NULL, ClearPasswordOnClamp, NULL,INTEGER }, //user password
				{ALLEMPTY			, 546,&CurrUserID_For_SysInfo, arr, NULL, NULL, SendCurrentUserId, NULL,INTEGER }, //user id
				{ALLEMPTY			, 547,NULL, nothing, NULL, NULL, NULL, HDSavePreset,INTEGER },
				{HOLD_PRESSURE_FLAG	, 548,&CurrentPreset.HoldPressureFlag, UInt16, NULL, NULL, NULL, SetHoldPressure,INTEGER }, //Hold Pressure Choice
				{ALLEMPTY			, 549 ,NULL, nothing, &ShowLogInButton , NULL,	CheckForLogInButtonDisplay, NULL, INTEGER},
				{ALLEMPTY			, 550 ,NULL, nothing, &ShowLogOutButton , NULL,	CheckForLogInButtonDisplay, NULL , INTEGER},
				{WELDPRESSURE_PLT	, 551,&CurrentPreset.WeldPressurePLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PRESSURE2},
				{WELDPRESSURE_MLT	, 552,&CurrentPreset.WeldPressureMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PRESSURE2},
				{DOWNSPEED_PLT		, 553,&CurrentPreset.DownspeedPLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PERCENT},
				{DOWNSPEED_MLT		, 554,&CurrentPreset.DownspeedMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PERCENT},
				{HOLDPRESSURE_PLT	, 555,&CurrentPreset.HoldPressurePLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PRESSURE2},
				{HOLDPRESSURE_MLT	, 556,&CurrentPreset.HoldPressureMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PRESSURE2},
				{HOLDTIME_PLT		, 557,&CurrentPreset.HoldTimePLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, TIME},
				{HOLDTIME_MLT		, 558,&CurrentPreset.HoldTimeMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, TIME},
				{AMPA_PLT			, 559,&CurrentPreset.AmpAPLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PERCENT},
				{AMPA_MLT			, 560,&CurrentPreset.AmpAMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, PERCENT},
				{TRIGFORCE_PLT		, 561,&CurrentPreset.TrigForcePLT, sint32, &FlagTriggerByForce,
										  &CurrentPreset.SetupLimits, SetupTriggerFlags, SetupLimitChanged, FORCE},
				{TRIGFORCE_MLT		, 562,&CurrentPreset.TrigForceMLT, sint32, &FlagTriggerByForce,
										  &CurrentPreset.SetupLimits, SetupTriggerFlags, SetupLimitChanged, FORCE},
				{WELDTIME_PLT		, 563,&CurrentPreset.WeldTimePLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, TIME},
				{WELDTIME_MLT		, 564,&CurrentPreset.WeldTimeMLT, sint32, NULL, &CurrentPreset.SetupLimits, NULL, SetupLimitChanged, TIME},
				{WELDENERGY_PLT		, 565,&CurrentPreset.WeldEnergyPLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, ENERGYDIV10},
				{WELDENERGY_MLT		, 566,&CurrentPreset.WeldEnergyMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, ENERGYDIV10},
				{PEAKPOWER_PLT		, 567,&CurrentPreset.PeakPowerPLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, PERCENTX10},
				{PEAKPOWER_MLT		, 568,&CurrentPreset.PeakPowerMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, PERCENTX10},
				{COLLAPSEDIST_PLT	, 569,&CurrentPreset.CollapseDistPLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, DISTANCE},
				{COLLAPSEDIST_MLT	, 570,&CurrentPreset.CollapseDistMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, DISTANCE},
				{ABSDIST_PLT		, 571,&CurrentPreset.AbsDistPLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, DISTANCE},
				{ABSDIST_MLT		, 572,&CurrentPreset.AbsDistMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, DISTANCE},
				{SCRUBTIME_PLT		, 573,&CurrentPreset.ScrubTimePLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, TIME},
				{SCRUBTIME_MLT		, 574,&CurrentPreset.ScrubTimeMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, TIME},
				{SCRUBAMP_PLT		, 575,&CurrentPreset.ScrubAmpPLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, PERCENT},
				{SCRUBAMP_MLT		, 576,&CurrentPreset.ScrubAmpMLT, sint32, NULL, &CurrentPreset.SetupLimits2, NULL, SetupLimitChanged, PERCENT},
				{TRIGDIST_PLT		, 577,&CurrentPreset.TrigDistancePLT, sint32, &FlagTriggerByDist,
										  &CurrentPreset.SetupLimits2, SetupTriggerFlags, SetupLimitChanged, DISTANCE},
				{TRIGDIST_MLT		, 578,&CurrentPreset.TrigDistanceMLT, sint32, &FlagTriggerByDist,
										  &CurrentPreset.SetupLimits2, SetupTriggerFlags, SetupLimitChanged, DISTANCE},
				{WELDPRESSURE_HD	, 579,&HdParams.WeldPressure, sint32, NULL, NULL, UpdatePressureOnHornDownEntry, UpdatePressureHornDown, PRESSURE2 },
				{FLOWCONTROL_HD		, 580,&HdParams.TempDownSpeed, sint32, NULL, NULL, UpdateFlowOnHornDownEntry, UpdateFlowValueHornDown, PERCENT },
				{ALLEMPTY			, 581,NULL, nothing, NULL, NULL, NULL, SpeedDownHD,INTEGER },
				{ALLEMPTY			, 582,NULL, nothing, NULL, NULL, NULL, SpeedUpHD,INTEGER },
				{ALLEMPTY			, 583,NULL, nothing, NULL, NULL, NULL, SaveDownSpeedTuneHD,INTEGER },
				{ALLEMPTY			, 584,NULL, nothing, NULL, NULL, NULL, EnableStartSensorCal,INTEGER },
				{ALLEMPTY			, 585,NULL, nothing, NULL, NULL, NULL, ExitDownSpeedTuneHD,INTEGER },
				{PRESSURESTEPDOWN	, 586,&CurrentSetup.PressureStepDownFlag, boolean, NULL, NULL, NULL, NULL , INTEGER}, //Pressure Stepping Down
				{LOWERFLOWVALVE		, 587,&FlowValveAEDEmulationIndicatorStr, arr, NULL, NULL, SendLowerFlowValve, NULL,INTEGER }, // lower flow valve indicator
				{WEBSERVICEAUTOMATIONFLAG		, 588,&CurrentSetup.WebServiceAutomation, boolean, NULL, NULL, NULL, NULL , INTEGER}, //WebService Automation
				{WEBSERVICEAUTHORITYCHECKFLAG	, 589,&CurrentSetup.WebServiceAutorityCheck, boolean, NULL, NULL, NULL, NULL , INTEGER}, //WebService AutorityCheck
				{ALLEMPTY	, 591,&RecordOptions.SysConfig, boolean, NULL, NULL, NULL, NULL , INTEGER},
				{ALLEMPTY	, 592,&RecordOptions.WeldRes1, boolean, NULL, NULL, NULL, NULL , INTEGER},
				{ALLEMPTY	, 593,&RecordOptions.WeldRes2, boolean, NULL, NULL, NULL, NULL , INTEGER},
				{ALLEMPTY	, 594,&RecordOptions.Preset1, boolean, NULL, NULL, NULL, NULL , INTEGER},
				{ALLEMPTY	, 595,&RecordOptions.Preset2, boolean, NULL, NULL, NULL, NULL , INTEGER},
				{ALLEMPTY   , 596,&EthernetOptions.Host, boolean, NULL, NULL, NULL,NULL,INTEGER },
				{ALLEMPTY   , 597,&EthernetOptions.WebSrv, boolean, NULL, NULL, NULL,NULL,INTEGER },
				{ALLEMPTY   , 598,&EthernetOptions.Gateway, boolean, NULL, NULL, NULL,NULL,INTEGER },
				{ALLEMPTY,-1, 0, arr, 0, 0, 0, NULL, INTEGER }
				};

const MINMAXMAP
		MinMap[] = {
				/*-----------------------------------------------------------------------------------------------------------*/
				/*  ID   Minimum Limit Pointer               Maximum Limit Pointer                          comment          */
				/*-----------------------------------------------------------------------------------------------------------*/
				{UNITS, 0, &BooleanMinValue, &BooleanMaxValue , NULL}, //System Unit
				{STARTSCREEN, 1, &BooleanMinValue, &BooleanMaxValue , NULL}, //Weld Results or Main Menu
				{WELDERADDRVALUE, 3, &WelderAddrMinValue, &WelderAddrMaxValue , NULL}, //WelderAddr
				{GENERALALARMFLAG   ,  4,(SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL}, //GeneralAlarmChoice
				{AMPCONTROL, 7, &BooleanMinValue, &BooleanMaxValue , NULL}, //Amplitude Control Internal or External
				{EXTRACOOLING,  8,&BooleanMinValue, &BooleanMaxValue,NULL },
				{HANDHELD, 9,&BooleanMinValue, &BooleanMaxValue,NULL},
				{EXTPRESETS	, 11,&BooleanMinValue, &BooleanMaxValue,NULL},
				{DIGITALFILTERFLAG  , 12,(SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL }, //DigitalFilter
				{USBGLOBALFLAG, 31, &BooleanMinValue, &BooleanMaxValue , NULL}, //USB Storage Status
				{USBWDSAMPLEVALUE, 32, &MinSampleValue, &MaxSampleValue , NULL}, //USBWeldDataSample
				{USBWDALARMFLAG, 33, &BooleanMinValue, &BooleanMaxValue , NULL}, //SaveOn Alarm Flag
				{USBPGSAMPLEVALUE, 34, &MinSampleValue, &MaxSampleValue , NULL}, //USBPowerSample
				{USBPGALARMFLAG, 35, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBPowerAlarmFlag
				{USBCDGSAMPLEVALUE, 36, &MinSampleValue, &MaxSampleValue , NULL}, //USBDistanceSample
				{USBCDGALARMFLAG, 37, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBDistanceAlarmFlag
				{USBVGSAMPLEVALUE, 38, &MinSampleValue, &MaxSampleValue , NULL}, //USBVelocitySample
				{USBVGALARMFLAG, 39, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBVelocitySaveOnAlarmFlag
				{USBFGSAMPLEVALUE, 40, &MinSampleValue, &MaxSampleValue , NULL}, //USBForceSample
				{USBFGALARMFLAG, 41, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBForceSaveOnAlarmFlag
				{USBAGSAMPLEVALUE, 42, &MinSampleValue, &MaxSampleValue , NULL}, //USBAmplitudeSample
				{USBAGALARMFLAG, 43, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBAmplitudeSaveOnAlarm
				{USBFREQGSAMPLEVALUE, 44, &MinSampleValue, &MaxSampleValue , NULL}, //USBFreqSample
				{USBFREQGALARMFLAG, 45, &BooleanMinValue, &BooleanMaxValue , NULL}, //USBFreqSampleSaveOnAlarmFlag
				{BEEPERTRIGGER, 47, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{BEEPERRELEASE, 48, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{BEEPERERROR, 49,(SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16,NULL}, //BeeperError
			    {BEEPERALARM, 50,(SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16,NULL},
				{PSWATT, 52, (SINT32*) &MinPSWatt, &MaxPSWatt , NULL}, //SetPSWatts
				{ULSLOGICCUSTOM, 56,&BooleanMinValue, &BooleanMaxValue , NULL}, //ULS
				{GNDDETLOGIC, 57,&BooleanMinValue, &BooleanMaxValue , NULL}, //Ground Detect
				{ALLEMPTY, 58, &MinLimitVelocityPC, &MaxLimitVelocityPC , NULL}, //SetVelocityPC
				{ALLEMPTY, 59, &MinLimitForcePC, &CurrentSetup.MinTrigForce , NULL}, //SetForcePC
				{MINTRIGFORCE, 60, &MinLimitMinTrigForce, &MaxLimitMinTrigForce , NULL}, //SetMinTrigger
				{METRIC3FLAG, 61, &BooleanMinValue, &BooleanMaxValue , NULL}, //Metric Decimals
				{WELDSCALEINDEX, 63, (SINT32*)&WeldScaleIndexMinValue,(SINT32*) &WeldScaleIndexMaxValue , NULL}, //Weld Scale
				{J3_32_IN, 88, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_33_IN, 89, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_19_IN, 90, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_17_IN, 91, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_31_IN, 92, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_31_IN, 92, (SINT32*)&GetInputMinValue,(SINT32*) &GetInputMaxValue , NULL},
				{J3_1_IN, 93, (SINT32*)&GetInputMinValue,(SINT32*)&GetInputMaxValue , NULL},
				{J3_8_OUT, 94, (SINT32*)&GetOutputMinValue,(SINT32*)&GetOutputMaxValue , NULL},
				{J3_36_OUT, 95, (SINT32*)&GetOutputMinValue,(SINT32*)&GetOutputMaxValue , NULL},
				{J3_22_OUT, 96, (SINT32*)&GetOutputMinValue,(SINT32*)&GetOutputMaxValue , NULL},
				{USERINLOGIC, 97, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{PARTCLAMPDELAY, 98, &MinPartClampDelay, &MaxPartClampDelay , NULL}, //SVDelay
				{WELDMODE, 101, (SINT32*) &MinLimit.WeldMode, (SINT32*) &MaxLimit.WeldMode , NULL}, //VGAWeldMode
				{WELDTIME, 102, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAWeldTime
				{HOLDTIME, 103, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAHoldTime
				{TRIGGERFORCE, 104, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGATriggerForce
				{EXTTRGDELAY, 105, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{AMPSTEPFLAG, 106,(SINT32*) &AmplitudeModeMinValue,(SINT32*) &AmplitudeModeMaxValue , NULL}, //AmplitudStepOrFixed
				{AMP_1, 107, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //AmplitudeA
				{AMP2, 108, &MinLimit.Amp2, &MaxLimit.Amp2 , NULL}, //AmplitudeB
				{AMPTRIGTIMEVALUE, 109, &MinLimit.AmpTrigTimeValue, &MaxLimit.AmpTrigTimeValue , NULL}, //AmpStepAtTime
				{AMPTRIGENERVALUE, 110, &MinLimit.AmpTrigEnerValue, &MaxLimit.AmpTrigEnerValue , NULL}, //AmpStepAtEner
				{AMPTRIGPOWERVALUE, 111, &MinLimit.AmpTrigPowerValue, &MaxLimit.AmpTrigPowerValue , NULL}, //AmpStepAtPower
				{AMPTRIGCOLVALUE, 112, &MinLimit.AmpTrigColValue, &MaxLimit.AmpTrigColValue , NULL}, //AmpStepAtDist
				{AMPTRIGEXTFLAG, 113, (SINT32*)&BooleanMaxValue16, (SINT32*)&BooleanMaxValue16  , NULL},
				{AMP1, 114, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAAmplitude1
				{WELDTRIGGER, 115, &BooleanMinValue, &BooleanMaxValue , NULL},
				{WELDENERGY, 116, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAWeldEnergyEnergy
				{PEAKPWR, 117, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAPeakPowerPP
				{COLDIST, 118, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGACollapseColl
				{ABSDIST, 119, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAAbsoluteAbs
				{SCRUBTIME, 120, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //VGAScrubTimeGndDet
				{AMPSCRUBTIME, 121, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //AmpGroundDetect
				{ABFLAG, 122, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{ABDELAY, 123, &MinLimit.AbDelay, &MaxLimit.AbDelay , NULL}, //ABDelayTime
				{ABTIME, 124, &MinLimit.AbTime, &MaxLimit.AbTime , NULL}, //ABTimeTime
				{ABAMP, 125, &MinLimit.AbAmp, &MaxLimit.AbAmp , NULL}, //ABAmplitude
				{PRETRIGFLAG,126, (SINT32*)&PretriggerModesMinValue,(SINT32*) &PretriggerModesMaxValue, NULL},//Pretriggermode
				{PRETRIGDIST, 127, &MinLimit.PreTriggerDistance, &MaxLimit.PreTriggerDistance , NULL}, //varPretrigDist
				{PRETRIGDELAY, 128, &MinLimit.PreTrigDelay, &MaxLimit.PreTrigDelay , NULL}, //varPretrigTime
				{PRETRIGAMP, 129, &MinLimit.PreTrigAmp, &MaxLimit.PreTrigAmp , NULL}, //varPretrigAmplitude
				{PMCENABLED, 130, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{REJECTLIMITSFLAG, 131, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{REJRESET_REQFLAG, 132, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				/******************************** VGARejectLimitsChoice *******************************************************/
				{TIMEPLR, 133, &MinLimit.TimePLR, &MaxLimit.TimePLR , NULL}, //PTimeREnergy
				{TIMEMLR, 134, &MinLimit.TimeMLR, &MaxLimit.TimeMLR , NULL}, //MTimeREnergy
				{ENERGYPLR, 135, &MinLimit.EnergyPLR, &MaxLimit.EnergyPLR , NULL}, //PEnergyRTime
				{ENERGYMLR, 136, &MinLimit.EnergyMLR, &MaxLimit.EnergyMLR , NULL}, //MEnergyRTime
				{POWERPLR, 137, &MinLimit.PowerPLR, &MaxLimit.PowerPLR , NULL}, //PPkPowerRLimit
				{POWERMLR, 138, &MinLimit.PowerMLR, &MaxLimit.PowerMLR , NULL}, //MPkPowerRLimit
				{COLPLR, 139, &MinLimit.ColPLR, &MaxLimit.ColPLR , NULL}, //PColDistRLimit
				{COLMLR, 140, &MinLimit.ColMLR, &MaxLimit.ColMLR , NULL}, //MColDistRLimit
				{ABSPLR, 141, &MinLimit.AbsPLR, &MaxLimit.AbsPLR , NULL}, //PAbsDistRLimit
				{ABSMLR, 142, &MinLimit.AbsMLR, &MaxLimit.AbsMLR , NULL}, //MAbsDistRLimit
				{TRSDISTPLR, 143, &MinLimit.TrsDistPLR, &MaxLimit.TrsDistPLR , NULL}, //PTrigDistRLimit
				{TRSDISTMLR, 144, &MinLimit.TrsDistMLR, &MaxLimit.TrsDistMLR , NULL}, //MTrigDistRLimit
				{WELDFORCEPLR, 145, &MinLimit.WeldForcePLR, &MaxLimit.WeldForcePLR , NULL}, //PMaxForceRLimit
				{WELDFORCEMLR, 146, &MinLimit.WeldForceMLR, &MaxLimit.WeldForceMLR , NULL}, //MMaxForceRLimit
				{PS_SBLMAXFREQ, 147, &CurrentPreset.SBLMinFreqLim,
					&CurrentPreset.SBLMaxFreqLim , NULL}, //PSBLFreqLimit
				{PS_SBLMINFREQ, 148, &CurrentPreset.SBLMinFreqLim,
					&CurrentPreset.SBLMaxFreqLim , NULL}, //MSBLFreqLimit
				{SUSPECTLIMITSFLAGS, 149, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{SUSRESET_REQ, 150, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},

				/************************************* VGASuspectLimitsChoice *************************************************/
				{TIMEPLS, 151, &MinLimit.TimePLS, &MaxLimit.TimePLS , NULL}, //PTimeSEnergy
				{TIMEMLS, 152, &MinLimit.TimeMLS, &MaxLimit.TimeMLS , NULL}, //MTimeSEnergy
				{ENERGYPLS, 153, &MinLimit.EnergyPLS, &MaxLimit.EnergyPLS , NULL}, //PEnergySTime
				{ENERGYMLS, 154, &MinLimit.EnergyMLS, &MaxLimit.EnergyMLS , NULL}, //MEnergySTime
				{POWERPLS, 155, &MinLimit.PowerPLS, &MaxLimit.PowerPLS , NULL}, //PPkPowerSLimit
				{POWERMLS, 156, &MinLimit.PowerMLS, &MaxLimit.PowerMLS , NULL}, //MPkPowerSLimit
				{COLPLS, 157, &MinLimit.ColPLS, &MaxLimit.ColPLS , NULL}, //PColDistSLimit
				{COLMLS, 158, &MinLimit.ColMLS, &MaxLimit.ColMLS , NULL}, //MColDistSLimit
				{ABSPLS, 159, &MinLimit.AbsPLS, &MaxLimit.AbsPLS , NULL}, //PAbsDistSLimit
				{ABSMLS, 160, &MinLimit.AbsMLS, &MaxLimit.AbsMLS , NULL}, //MAbsDistSLimit
				{TRSDISTPLS, 161, &MinLimit.TrsDistPLS, &MaxLimit.TrsDistPLS , NULL}, //PTrigDistSLimit
				{TRSDISTMLS, 162, &MinLimit.TrsDistMLS, &MaxLimit.TrsDistMLS , NULL}, //MTrigDistSLimit
				{WELDFORCEPLS, 163, &MinLimit.WeldForcePLS, &MaxLimit.WeldForcePLS , NULL}, //PMaxForceSLimit
				{WELDFORCEMLS, 164, &MinLimit.WeldForceMLS, &MaxLimit.WeldForceMLS , NULL}, //MMaxForceSLimit
				{BEEPERESTOP, 166, (SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{HORNCLAMP, 167,&BooleanMinValue,&BooleanMaxValue , NULL},
				{UDISCAN, 168,&BooleanMinValue,&BooleanMaxValue , NULL},
				{AUTOMATION, 169,&BooleanMinValue,&BooleanMaxValue , NULL},
				{MEMORYFULL, 170,&BooleanMinValue,&BooleanMaxValue , NULL},
				{USERIDTABLE, 171,&BooleanMinValue,&BooleanMaxValue , NULL},
				{AUTHORITYCHECK, 172,&BooleanMinValue,&BooleanMaxValue , NULL},
				{ENERGYBRAKING, 173,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				/************************************* VGAForceChoiceStep / Fixed *********************************************/
				//   {166, &MinLimit.WeldForce,                &MaxLimit.WeldForce                    , NULL},    //WeldForceA
				//   {167, &MinLimit.Force2,                   &MaxLimit.Force2                       , NULL},    //WeldForceB
				//   {168, &MinLimit.ForceTrigTimeValue,       &MaxLimit.ForceTrigTimeValue           , NULL},    //ForceStepAtTime
				//   {169, &MinLimit.ForceTrigEnerValue,       &MaxLimit.ForceTrigEnerValue           , NULL},    //ForceStepAtEner
				//   {170, &MinLimit.ForceTrigPowerValue,      &MaxLimit.ForceTrigPowerValue          , NULL},    //ForceStepAtPower
				//   {171, &MinLimit.ForceTrigColValue,        &MaxLimit.ForceTrigColValue            , NULL},    //ForceStepAtCol
				/************************************* EnergyBrakingChoice  ***************************************************/
				{EBTIME, 174, &MinLimit.EBTime, &MaxLimit.EBTime , NULL}, //EBTime
				{TRIGGERDISTANCE, 175, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //Trigger Distance
				{SEEKFUNFLAG, 177, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{FREQOFFSETFLAG, 178, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				/************************************ VGAFreqOffsetChoice  *****************************************************/
				{PS_FREQOFFSET, 179, &MinLimit.FreqOffset, &MaxLimit.FreqOffset , NULL}, //FreqOffset
				{ACTCLEARFLAG, 180, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},

				/************************************ VGAActClearOutputChoice  *************************************************/
				{ACTCLEARDIST, 181, &MinLimit.ActClrDistance, &MaxLimit.ActClrDistance , NULL}, //Distance
				{CONTROLLIMITSFLAG, 182,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16  , NULL},
				{ENERGYCOMPFLAG, 183,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16  , NULL},
				/****************************** VGAControlLimitsChoice1 /Choice2 ***********************************************/
				{ENERGYPL, 184, &MinLimit.EnergyPL, &MaxLimit.EnergyPL , NULL}, //MaxEnergyComp
				{ENERGYML, 185, &MinLimit.EnergyML, &MaxLimit.EnergyML , NULL}, //MinEnergyComp
				{PEAKPOWERCUTOFF, 186, &MinLimit.PeakPwrCutoff, &MaxLimit.PeakPwrCutoff , NULL}, //PeakPowerCutoff
				{ABSCUTOFFDIST, 187, &MinLimit.ABSCutoffDist, &MaxLimit.ABSCutoffDist , NULL}, //ABSCutoff
				{COLLCUTOFFDIST, 188, &MinLimit.ColCutoffDist, &MaxLimit.ColCutoffDist , NULL}, //CollapseCutoff
				{CYCLEABORTFLAG, 189, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{GROUNDDETECTFLAG, 190, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{MISSINGPARTFLAG, 191, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				/********************************** VGACycleAbortsChoice1 /Choice2 **********************************************/
				{MISSINGPARTMAX, 192, &MinLimit.MissingPartMax, &MaxLimit.MissingPartMax , NULL}, //MissingPartMaximum
				{MISSINGPARTMIN, 193, &MinLimit.MissingPartMin, &MaxLimit.MissingPartMin , NULL}, //MissingPartMinimum
				{RTFLAG, 194, (SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				{RTDIST, 195, &MinLimit.RTDist, &MaxLimit.RTDist , NULL}, //StepAtRTDist
				{DUPSMEMFLAG, 197, &BooleanMinValue,&BooleanMaxValue , NULL},

				/********************************************* DigitalUPS ********************************************************/
				{WELDRAMPTIME, 198, &DUPS_MinParamSet.WeldRampTime,
					&DUPS_MaxParamSet.WeldRampTime , NULL}, //RTime
				{SEEKTIME, 199, &DUPS_MinParamSet.SeekTime, &DUPS_MaxParamSet.SeekTime , NULL}, //STime
				{DUPS_SEEK_FLAG, 200, &BooleanMinValue,&BooleanMaxValue, NULL},
				{SWDIPSETTING, 201, &BooleanMinValue,&BooleanMaxValue, NULL},
				{WELDSTATUSFLAG, 202, &BooleanMinValue,&BooleanMaxValue, NULL},
				/***************************************** VGAForceRampsMenu *****************************************************/
				{MAXTIMEOUT, 206, &MinLimit.MaxTimeout, &MaxLimit.MaxTimeout , NULL}, //VGAMaxTimeout
				{PRESSURE2_FLAG, 238, (SINT32*) &BooleanMinValue16,(SINT32*) &BooleanMaxValue16,NULL },
                {PRESSURE_1, 239,  &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax},
				{PRESSURE_2, 240, &MinLimit.Pressure2, &MaxLimit.Pressure2, NULL},    //Pressure2
				{PRESSURE_TRIGTIMEVALUE, 241, &MinLimit.PressureTrigTimeValue, &MaxLimit.PressureTrigTimeValue, NULL},    //PressureStepAtTime
				{PRESSURE_TRIGENERVALUE, 242, &MinLimit.PressureTrigEnerValue, &MaxLimit.PressureTrigEnerValue, NULL},    //PressureStepAtEner
				{PRESSURE_TRIGPOWERVALUE, 243, &MinLimit.PressureTrigPowerValue, &MaxLimit.PressureTrigPowerValue, NULL},    //PressureStepAtPower
				{PRESSURE_TRIGCOLVALUE, 244, &MinLimit.PressureTrigColValue, &MaxLimit.PressureTrigColValue, NULL},    //PressureStepAtCol
				{PRESSURE_TRIGEXTFLAG, 245, (SINT32*)&BooleanMaxValue16,(SINT32*)&BooleanMaxValue16, NULL},    //PressureStepExt(choice)

				{OPERATORAUTH, 255,(SINT32*)&OperatorAuthMinValue,(SINT32*) &OperatorAuthMaxValue, NULL},
				{AUTOSCALEFLAG, 257,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16, NULL},

				/************************************** VGAPrintingChoice ********************************************************/
				{XSCALETIME, 258, &MinLimit.XScaleTime, &MaxLimit.XScaleTime , NULL}, //PrinterScaling
				{HISTORYSETUP, 259, &HistorySetupMinValue, &HistorySetupMaxValue , NULL},
				{BASICEXPERT, 261,&BooleanMinValue,&BooleanMaxValue, NULL},
				{HWVERIFY, 264,(SINT32*)&HWVerifyMinValue,(SINT32*)&HWVerifyMaxValue, NULL},
				{BATCHFUNCTION, 265,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16, NULL},
				{BATCHCOUNTWITHALARM, 266,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16, NULL},
				{BATCHCOUNTRESET, 267,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16, NULL},
				{BATCHCOUNT, 268, &MinLimit.BatchCount, &MaxLimit.BatchCount , NULL}, //BatchCount
				{PPRESSURELIMITFLAG, 269,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16, NULL},
				{MPRESSURELIMIT, 270, &MinLimit.MPressureLimit, &MaxLimit.MPressureLimit , NULL}, //-Pressure Limit
				{PS_PPRESSURELIMIT, 271, &MinLimit.PPressureLimit, &MaxLimit.PPressureLimit , NULL}, //+Pressure Limit
				{WELDPRESSURE, 272, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax}, //WeldPressure
				{HOLDPRESSURE, 273, &MinSetupLim, &MaxSetupLim, PreSetupLimitMinMax}, //HoldPressure
				{FLOWCONTROL, 274, &MinSetupLim, &MaxSetupLim , PreSetupLimitMinMax},
				{ALLEMPTY, 281, &PassExpTimeMin, &PassExpTimeMax , NULL}, //Password expire time
				{IDLELOGOUTTIME, 283, &IdleLogoutTimeMin, &IdleLogoutTimeMax , NULL}, //Idle logouttime expire time
				{ALLEMPTY, 295, &MinPresetNumber, &MaxPresetNumber , NULL},// added for preset number mannual entry
				{AUTOREFRESH, 302, &BooleanMinValue,&BooleanMaxValue, NULL},
				{PSLIFETIMECOUNTER, 303, &MinLimitMin, &MaxLimitMax , NULL}, //SetPSLife
				{OVERLOADCOUNTER, 304, &MinLimitMin, &MaxLimitMax , NULL}, //SetOverloads
				{GENERALALARMCOUNTER, 305, &MinLimitMin, &MaxLimitMax , NULL}, //SetGenAlarms
				{ALLEMPTY, 307, &MinBUCFactoryDefaults, &MaxBUCFactoryDefaults , NULL}, //VGAFactoryDefaults
				{PMCTIMEOUT, 308, &MinLimit.PMCTimeout, &MaxLimit.PMCTimeout , NULL}, //VGAPwrCurveTimeout
				{IDLESPEED, 313, &MinLimitIdleSpeed, &MaxLimitIdleSpeed , NULL}, //SetIdleSpeed
				{GAINFACTOR, 314, &MinLimitGainFactor, &MaxLimitGainFactor , NULL}, //SetGainFactor
				{ALLEMPTY, 316, &EnergyBrakeTimeMin, &EnergyBrakeTimeMax , NULL}, //SetEnergyBrakingTime
				{ALLEMPTY, 317, &EnergyBrakePercentMin, &EnergyBrakePercentMax , NULL}, //SetEnergyBrakingPercent
				{SEEKAMPLITUDE, 318, &DUPS_MinParamSet.SeekAmplitude,
					&DUPS_MaxParamSet.SeekAmplitude , NULL}, //AmplitudeFn
				{SEEKRAMPTIME, 319, &DUPS_MinParamSet.SeekRampTime,
					&DUPS_MaxParamSet.SeekRampTime , NULL}, //SeekRampTimeVar
				{SEEKFREQLIMITHIGH, 320, &DUPS_MinParamSet.SeekFreqLimitHigh,
					&DUPS_MaxParamSet.SeekFreqLimitHigh , NULL}, //FreqHighVar
				{SEEKFREQLIMITLOW, 321, &DUPS_MinParamSet.SeekFreqLimitLow,
					&DUPS_MaxParamSet.SeekFreqLimitLow , NULL}, //FreqLowVar
				{SEEKPHASELOOP, 322, &DUPS_MinParamSet.SeekPhaseLoop,
					&DUPS_MaxParamSet.SeekPhaseLoop , NULL}, //PhsLoop
				{SEEKPHASELOOPCF, 323, &DUPS_MinParamSet.SeekPhaseLoopCF,
					&DUPS_MaxParamSet.SeekPhaseLoopCF , NULL}, //SeekPhsLoopCF
				{SEEKAMPLOOPC1, 324, &DUPS_MinParamSet.SeekAmplitudeLoopC1,
					&DUPS_MaxParamSet.SeekAmplitudeLoopC1 , NULL}, //AmplLoopC1
				{SEEKAMPLOOPC2, 325, &DUPS_MinParamSet.SeekAmplitudeLoopC2,
					&DUPS_MaxParamSet.SeekAmplitudeLoopC2 , NULL}, //AmplLoopC2
				{WELDAMPLITUDE, 326, &DUPS_MinParamSet.WeldAmplitude,
					&DUPS_MaxParamSet.WeldAmplitude , NULL}, //WeldAmplitude
				{WELDRAMPTIME, 327, &DUPS_MinParamSet.WeldRampTime,
					&DUPS_MaxParamSet.WeldRampTime , NULL}, //RampTime
				{WELDPHASELOOP, 328, &DUPS_MinParamSet.WeldPhaseLoop,
					&DUPS_MaxParamSet.WeldPhaseLoop , NULL}, //WeldPhaseLoop
				{WELDPHASELOOPCF, 329, &DUPS_MinParamSet.WeldPhaseLoopCF,
					&DUPS_MaxParamSet.WeldPhaseLoopCF , NULL}, //PhsLoopCF
				{WELDAMPLOOPC1, 330, &DUPS_MinParamSet.WeldAmplitudeLoopC1,
					&DUPS_MaxParamSet.WeldAmplitudeLoopC1 , NULL}, //WeldAmpLoopC1
				{WELDAMPLOOPC2, 331, &DUPS_MinParamSet.WeldAmplitudeLoopC2,
					&DUPS_MaxParamSet.WeldAmplitudeLoopC2 , NULL}, //WeldAmpLoopC2
				{WELDFREQLIMITHIGH, 332, &DUPS_MinParamSet.WeldFreqLimitHigh,
					&DUPS_MaxParamSet.WeldFreqLimitHigh , NULL}, //WeldHighVar
				{WELDFREQLIMITLOW, 333, &DUPS_MinParamSet.WeldFreqLimitLow,
					&DUPS_MaxParamSet.WeldFreqLimitLow , NULL}, //WeldLowVar
				{WELDPHASELIMIT, 334, &DUPS_MinParamSet.WeldPhaseLimit,
					&DUPS_MaxParamSet.WeldPhaseLimit , NULL}, //PhsLimit
				{WELDPHASELIMIT_TIME, 335, &DUPS_MinParamSet.WeldPhaseLimitTime,
					&DUPS_MaxParamSet.WeldPhaseLimitTime , NULL}, //PhaseLimits
				{ALLEMPTY, 336, &HS_MinScanInfo.MaximumAmplitude,
					&HS_MaxScanInfo.MaximumAmplitude , NULL}, //SAmplitude
				{ALLEMPTY, 337, &HS_MinScanInfo.MaximumCurrent,
					&HS_MaxScanInfo.MaximumCurrent , NULL}, //SCurrent
				{ALLEMPTY, 338, &HS_MinScanInfo.StartFreq, &HS_MaxScanInfo.StartFreq , NULL}, //FreqStartVar
				{ALLEMPTY, 339, &HS_MinScanInfo.StopFreq, &HS_MaxScanInfo.StopFreq , NULL}, //FreqEndVar
				{ALLEMPTY, 340, &HS_MinScanInfo.FreqStep, &HS_MaxScanInfo.FreqStep , NULL}, //FreqStepVar
				{ALLEMPTY, 341, &HS_MinScanInfo.TimeDelay, &HS_MaxScanInfo.TimeDelay , NULL}, //TimeDelayVar
				{ALLEMPTY, 343, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg1
				{ALLEMPTY, 344, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg2
				{ALLEMPTY, 345, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg3
				{ALLEMPTY, 346, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg4
				{ALLEMPTY, 347, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg5
				{ALLEMPTY, 348, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg6
				{ALLEMPTY, 349, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg7
				{ALLEMPTY, 350, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg8
				{ALLEMPTY,351, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg9
				{ALLEMPTY, 352, &AlarmPtrMin, &AlarmPtrMax , NULL}, //Seg10
				{ALLEMPTY, 353, &AlarmPtrMin, &AlarmPtrMax , NULL}, //olg1
				{ALLEMPTY, 354, &AlarmPtrMin, &AlarmPtrMax , NULL}, //ncg1
				{ALLEMPTY, 355, &AlarmPtrMin, &AlarmPtrMax , NULL}, //eqg1
				{ALLEMPTY, 356, &AlarmPtrMin, &AlarmPtrMax , NULL}, //cmg1
				{ALLEMPTY, 357, &AlarmPtrMin, &AlarmPtrMax , NULL}, //prg1
				{ALLEMPTY, 358, &AlarmPtrMin, &AlarmPtrMax , NULL}, //psg1
				{ALLEMPTY, 359, &AlarmPtrMin, &AlarmPtrMax , NULL}, //wag1
				{DIGTUNEFLAG, 382,(SINT32*)&BooleanMinValue16,(SINT32*)&BooleanMaxValue16 , NULL},
				/************************************** VGADiagnosticMenu1  ************************************************/
				{ALLEMPTY, 384, &MinDigTuneValue, &MaxDigTuneValue , NULL}, //DigitalFrequency
				{ALLEMPTY, 387, &DebugLowValue, &DebugHighValue , NULL}, //Debug
				///********************************************* Horn Down  ***************************************************/

				{ALLEMPTY, 406, &MinLimit.RTDist, &MaxLimit.RTDist , NULL}, //RTTransition
				{TESTAMP, 421, &MinLimit.TestAmp, &MaxLimit.TestAmp , NULL}, //TestAmplitude
				{ALLEMPTY, 427, &ForceGaugeReadingMin, &ForceGaugeReadingMax , NULL}, //GaugeReading
				{ALLEMPTY, 434, NULL, NULL , NULL}, //ErrorCodeInfo
				{ALLEMPTY, 435, &ForceGaugeReadingMin, &ForceGaugeReadingMax , NULL}, //GaugeReading1
				{ALLEMPTY, 437, &ForceGaugeReadingMin, &ForceGaugeReadingMax , NULL}, //GaugeReading3
				{ALLEMPTY, 440, &LoadCellReadingMin, &LoadCellReadingMax , NULL}, //varLoadCellReading1
				{ALLEMPTY, 442, &LoadCellReadingMin, &LoadCellReadingMax , NULL}, //varLoadCellReading3
				{ALLEMPTY, 443, &LoadCellReadingMin, &LoadCellReadingMax , NULL}, //varLoadCellReading3AEF
				{PMCHIGHLIMIT, 463, &MinLimit.PMCHighLimit, &MaxLimit.PMCHighLimit , NULL}, //VGAPwrUpperBand
				{PMCLOWLIMIT, 464, &MinLimit.PMCLowLimit, &MaxLimit.PMCLowLimit , NULL}, //VGAPwrLowerBand
				{ALLEMPTY, 467, &ActualHoldTime, &ActualHoldTime , NULL}, //TrigLostTimeHold
				{ALLEMPTY, 468, &WeldingResults.ActualWeldTime,
					&WeldingResults.ActualWeldTime , NULL}, //CM4Actual
				{ALLEMPTY, 469, &WeldingResults.TotalEnergy, &WeldingResults.TotalEnergy , NULL}, //CM6Actual
				{ALLEMPTY, 470, &WeldingResults.ActualWeldCollapse,
					&WeldingResults.ActualWeldCollapse , NULL}, //CM8Actual
				{ALLEMPTY, 471, (SINT32*)&ActualPeakPower, (SINT32*)&ActualPeakPower , NULL}, //CM10Actual
				{ALLEMPTY, 472, &TriggerLostTime, &TriggerLostTime , NULL}, //TrigLostTime
				{ALLEMPTY, 473, &WeldingResults.ActualAmplitudeEnd,
					&WeldingResults.ActualAmplitudeEnd , NULL}, //CM16ActualAmpB
				{ALLEMPTY, 474, &WeldingResults.ActualAmplitudeStart,
					&WeldingResults.ActualAmplitudeStart , NULL}, //CM18ActualAmpA
				{ALLEMPTY, 475, &WeldForceEnd, &WeldForceEnd , NULL}, //CM22ActualWeldForce
				{ALLEMPTY, 476, &WeldingResults.ActualWeldCollapse,
					&WeldingResults.ActualWeldCollapse , NULL}, //CM23Actual
				{ALLEMPTY, 478, &Inp.PresetCode, &Inp.PresetCode , NULL}, //ExtPresetRecalled
				{ALLEMPTY, 481, &MaximumForce, &MaximumForce , NULL}, //MaximumForceInfo
				{ALLEMPTY, 482, &FinalResults.ActualTotalAbs,
					&FinalResults.ActualTotalAbs , NULL}, //AbsDistActual
				{ALLEMPTY, 483, &FinalResults.ActualWeldCollapse,
					&FinalResults.ActualWeldCollapse , NULL}, //WeldColDistActual
				{ALLEMPTY, 484, &TestTime, &TestTime , NULL}, //OverloadTestTime
				{ALLEMPTY, 485, &PowerTest, &PowerTest , NULL}, //TestPower
				{ALLEMPTY, 486, &FreqChg, &FreqChg , NULL}, //OverloadTestFreqChg
				{ALLEMPTY, 487, &WeldOLStatus.ErrorCurrent, &WeldOLStatus.ErrorCurrent , NULL}, //OverloadTestDUPSCurrent
				{ALLEMPTY, 488, &WeldOLStatus.ErrorFrequency,
					&WeldOLStatus.ErrorFrequency , NULL}, //OverloadTestDUPSFreqAct
				{ALLEMPTY, 489, &WeldOLStatus.ErrorPSV, &WeldOLStatus.ErrorPSV , NULL}, //OverloadTestDUPSPhaseAct
				{ALLEMPTY, 490, &PTSTimer, &PTSTimer , NULL}, //OverloadTimePTrg
				{ALLEMPTY, 491, &OverloadPower, &OverloadPower , NULL}, //PTOverloadPeakPwr
				{ALLEMPTY, 492, &OverloadFreq, &OverloadFreq , NULL}, //PTOverloadFreq
				{ALLEMPTY, 493, (SINT32*)&ActualSeekTime, (SINT32*)&ActualSeekTime , NULL}, //OverloadTimeSeek
				{ALLEMPTY, 494, &FinalResults.FrequencyChange,
					&FinalResults.FrequencyChange , NULL}, //OverloadFreqChg
				{ALLEMPTY, 495, &FinalResults.ActualWeldTime,
					&FinalResults.ActualWeldTime , NULL}, //OverloadTime
				{ALLEMPTY, 496, &ActualAfterburstTime, &ActualAfterburstTime , NULL}, //OverloadTimeAB
				{ALLEMPTY, 497, (SINT32*)&ABOverloadPower, (SINT32*)&ABOverloadPower , NULL}, //ABOverloadPeakPwr
				{ALLEMPTY, 498, &ABOLStatus.ErrorCurrent, &ABOLStatus.ErrorCurrent , NULL}, //OverloadABDUPSCurrent
				{ALLEMPTY, 499, &ABOLStatus.ErrorFrequency, &ABOLStatus.ErrorFrequency , NULL}, //OverloadABDUPSFreqAct
				{ALLEMPTY, 500, &ABOLStatus.ErrorPSV, &ABOLStatus.ErrorPSV , NULL}, //OverloadABDUPSPhaseAct
				{ALLEMPTY, 501, &EBOverloadTimer, &EBOverloadTimer , NULL}, //EBOverloadTime
				{ALLEMPTY, 502, &EBOverloadPower, &EBOverloadPower , NULL}, //EBOverloadPeakPwr
				{ALLEMPTY, 503, &EBOverloadFreq, &EBOverloadFreq , NULL}, //EBOverloadFreqChg
				{ALLEMPTY, 504, &FinalResults.TotalEnergy, &FinalResults.TotalEnergy , NULL}, //PeakEnergyActual
				{ALLEMPTY, 505, &FinalResults.ActualTotalCollapse,
					&FinalResults.ActualTotalCollapse , NULL}, //ColDistActual
				{ALLEMPTY, 506, &FinalResults.ActualTriggerDistance,
					&FinalResults.ActualTriggerDistance , NULL}, //ActualTrigDist
				{ALLEMPTY, 507, &ActualForceMax, &ActualForceMax , NULL}, //ActualWeldForce
				{ALLEMPTY, 508, &FinalResults.ActualWeldTime,
					&FinalResults.ActualWeldTime , NULL}, //ActualTime
				{ALLEMPTY, 509, &ActualSBLMinFreq, &ActualSBLMinFreq , NULL}, //MActualFreq
				{ALLEMPTY, 510, &ActualSBLMaxFreq, &ActualSBLMaxFreq , NULL}, //PActualFreq
				{ALLEMPTY, 511, &ActualValuePMC1, &ActualValuePMC1 , NULL}, //PPmcActual
				{ALLEMPTY, 512, &ActualValuePMC2, &ActualValuePMC2 , NULL}, //MPmcActual
				{VALIDATEPS , 525,&BooleanMinValue, &BooleanMaxValue,NULL},
				{LOCKPS , 526,&BooleanMinValue, &BooleanMaxValue,NULL},
				{DOWNSPEEDPLR, 540, &MinLimit.VelocityPLR, &MaxLimit.VelocityPLR , NULL},
				{DOWNSPEEDMLR, 541, &MinLimit.VelocityMLR, &MaxLimit.VelocityMLR , NULL},
				{HOLD_PRESSURE_FLAG	, 548,(SINT32*)&BooleanMinValue16, (SINT32*)&BooleanMaxValue16 , NULL},
				{WELDPRESSURE_PLT, 551, &MinLimit.WeldPressure, &MaxLimit.WeldPressure , NULL},
				{WELDPRESSURE_MLT, 552, &MinLimit.WeldPressure, &MaxLimit.WeldPressure , NULL},
				{DOWNSPEED_PLT, 553, &MinLimit.Downspeed, &MaxLimit.Downspeed , NULL},
				{DOWNSPEED_MLT, 554, &MinLimit.Downspeed, &MaxLimit.Downspeed , NULL},
				{HOLDPRESSURE_PLT, 555, &MinLimit.HoldPressure, &MaxLimit.HoldPressure , NULL},
				{HOLDPRESSURE_MLT, 556, &MinLimit.HoldPressure, &MaxLimit.HoldPressure , NULL},
				{HOLDTIME_PLT, 557, &MinLimit.HoldTime, &MaxLimit.HoldTime , NULL},
				{HOLDTIME_MLT, 558, &MinLimit.HoldTime, &MaxLimit.HoldTime , NULL},
				{AMPA_PLT, 559, &MinLimit.Amp1, &MaxLimit.Amp1, NULL},
				{AMPA_MLT, 560, &MinLimit.Amp1, &MaxLimit.Amp1, NULL},
				{TRIGFORCE_PLT, 561, &CurrentSetup.MinTrigForce, &MaxLimit.TriggerForce, NULL},
				{TRIGFORCE_MLT, 562, &CurrentSetup.MinTrigForce, &MaxLimit.TriggerForce, NULL},
				{WELDTIME_PLT, 563, &MinLimit.WeldTime, &MaxLimit.WeldTime , NULL},
				{WELDTIME_MLT, 564, &MinLimit.WeldTime, &MaxLimit.WeldTime , NULL},
				{WELDENERGY_PLT, 565, &MinLimit.WeldEnergy, &MaxLimit.WeldEnergy, NULL},
				{WELDENERGY_MLT, 566, &MinLimit.WeldEnergy, &MaxLimit.WeldEnergy, NULL},
				{PEAKPOWER_PLT , 567, &MinLimit.PeakPwr, &MaxLimit.PeakPwr, NULL},
				{PEAKPOWER_MLT , 568, &MinLimit.PeakPwr, &MaxLimit.PeakPwr, NULL},
				{COLLAPSEDIST_PLT, 569, &MinLimit.ColDist, &MaxLimit.ColDist, NULL},
				{COLLAPSEDIST_MLT, 570, &MinLimit.ColDist, &MaxLimit.ColDist, NULL},
				{ABSDIST_PLT, 571, &MinLimit.AbsDist, &MaxLimit.AbsDist, NULL},
				{ABSDIST_MLT, 572, &MinLimit.AbsDist, &MaxLimit.AbsDist, NULL},
				{SCRUBTIME_PLT, 573, &MinLimit.ScrubTime, &MaxLimit.ScrubTime, NULL},
				{SCRUBTIME_MLT, 574, &MinLimit.ScrubTime, &MaxLimit.ScrubTime, NULL},
				{SCRUBAMP_PLT, 575, &MinLimit.AmpScrubTime, &MaxLimit.AmpScrubTime, NULL},
				{SCRUBAMP_MLT, 576, &MinLimit.AmpScrubTime, &MaxLimit.AmpScrubTime, NULL},
				{TRIGDIST_PLT, 577, &MinLimit.TriggerDistance, &MaxLimit.TriggerDistance, NULL},
				{TRIGDIST_MLT, 578, &MinLimit.TriggerDistance, &MaxLimit.TriggerDistance, NULL},
				{WELDPRESSURE_HD, 579, &HdMinPressure, &MaxLimit.WeldPressure, NULL}, //WeldPressureHD
				{FLOWCONTROL_HD, 580, &MinLimit.Downspeed, &MaxLimit.Downspeed, NULL}, //downspeed HD
				{PRESSURESTEPDOWN,586,&BooleanMinValue, &BooleanMaxValue , NULL}, //Pressure step down
				{ALLEMPTY, -1, 0, 0 , NULL}
};

/*
 *Purpose:
 *	This function sends configuration values necessary
 *	for SBC startup.Control level,Actuator type,weld mode,
 *	security level,software config. , hardware config. ,
 *	units,auto refresh,password flag,sequence enable,
 *	basic Expert mode authority check,automation ,user
 *	conditions ,idle logout time.More data can be send
 *	if needed.
 *Input Argument:
 *	 uint8 *to :pointer to received data
 *Return :
 *   uint16 length :number of bytes added to output buffer.
 */
UINT16 SendConditionVariable(UINT8 * to) {
	UINT8 UnitsAndAutoRefresh = 0;
	UINT16 length = 0; // length of data in output buffer
	length += AddToBuffer(&to, (UINT8) CurrentSetup.ControlLevel);

	length += AddToBuffer(&to, (UINT8) (CurrentSetup.Actuator>>EIGHT));
	length += AddToBuffer(&to, (UINT8) (CurrentSetup.Actuator));

	length += AddToBuffer(&to, (UINT8) CurrentPreset.WeldMode);
	length += AddToBuffer(&to, (UINT8) CurrentSetup.SecurityLevel);
	length += AddToBuffer(&to, (UINT8) AccessLevel);
	length += AddToBuffer(&to, (UINT8) ((SWConfiguration) >> 24));
	length += AddToBuffer(&to, (UINT8) ((SWConfiguration) >> 16));
	length += AddToBuffer(&to, (UINT8) ((SWConfiguration) >> 8));
	length += AddToBuffer(&to, (UINT8) (SWConfiguration));
	length += AddToBuffer(&to, (UINT8) ((HWConfiguration) >> 24));
	length += AddToBuffer(&to, (UINT8) ((HWConfiguration) >> 16));
	length += AddToBuffer(&to, (UINT8) ((HWConfiguration) >> 8));
	length += AddToBuffer(&to, (UINT8) (HWConfiguration));

	printf("CurrentSetup.ControlLevel = %2X\n", CurrentSetup.ControlLevel);          // Diagnostic messages on the debug port
	printf("CurrentSetup.Actuator = %2X\n", CurrentSetup.Actuator);
	printf("CurrentPreset.WeldMode = %2X\n", CurrentPreset.WeldMode);
	printf("CurrentSetup.SecurityLevel = %2X\n", CurrentSetup.SecurityLevel);
	printf("AccessLevel = %2X\n", AccessLevel);

	if (CurrentSetup.Units)
		UnitsAndAutoRefresh = 0x01;
	else
		UnitsAndAutoRefresh = 0x00;

	if (CurrentSetup.AutoRefresh)
		UnitsAndAutoRefresh = UnitsAndAutoRefresh | 0x10;
	else
		UnitsAndAutoRefresh = UnitsAndAutoRefresh | 0x00;

	length += AddToBuffer(&to, (UINT8) UnitsAndAutoRefresh); //Units and AutoRefresh;

	if (CurrentSetup.PassWordFlag)
		length += AddToBuffer(&to, (UINT8) 1);
	else
		length += AddToBuffer(&to, (UINT8) 0);

	if(CurrentSetup.MemoryFull == CONTINUE)
		length += AddToBuffer(&to, 1);
	else
		length += AddToBuffer(&to, 0);

	length += AddToBuffer(&to, (UINT8) (CurrentSetup.SequenceEnable));
	length += AddToBuffer(&to, (UINT8) CurrentSetup.BasicExpert);
	length += AddToBuffer(&to, (UINT8) CurrentSetup.Automation);

	length += AddToBuffer(&to, (UINT8) CurrentSetup.AuthorityCheck);
	if(CurrentSetup.Automation == OFF){
		if(CurrentSetup.AuthorityCheck == TRUE){
			length += AddToBuffer(&to, (UINT8) ((CurrentSetup.IdleLogoutTime) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentSetup.IdleLogoutTime) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentSetup.IdleLogoutTime) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentSetup.IdleLogoutTime));
		}
	}
	UINT16 userCond = 0;
	if(CurrentPreset.Locked)
		userCond = LOCKED;
	else
		userCond = UNLOCKED;

	if(CurrentPreset.Validated)
		userCond |= VALIDATED;
	else
		userCond |= UNVALIDATED;

	userCond = (userCond << 8) | CurrentUser.UserLevel;
	length += AddToBuffer(&to, (UINT8) (userCond>>8));
	length += AddToBuffer(&to, (UINT8) (userCond));

	InitWeldParamOption();
	if(CurrentSetup.ControlLevel < LEVEL_c)
	{
		MaxPresetNumber = MAX_POSSIBLE_PRESET_BELOW_C;
		if(CurrentSetup.ActivePreset > MAX_POSSIBLE_PRESET_BELOW_C)
		{
			CurrentSetup.ActivePreset = 0;
			UpdateRunningPreset = TRUE;
			ReadPreset(CurrentSetup.ActivePreset, FALSE);
			WritePreset(CURRENT_PRESET_INDEX);                           /* Update Running Preset */
			UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
			DUPS_DownloadCurrPS();
			RefreshDUPSParam ();
			ResetRecall_UpdateFlag = TRUE;
			ResetStateMachine();
			StartStateMachine();
		}
	}
	else
		MaxPresetNumber = MAX_POSSIBLE_PRESET;

	return length;
}

UINT16 XMLDataProcess(UINT8 * to, UINT16 PositionInMap, UINT16 ID)
/**************************************************************************/
/* This function provides data of different types required to display menu*/
/* according to ID sent by SBC side.                                      */
/**************************************************************************/
{
	UINT16 length = 0; // length of data in output buffer
	UINT8 Uint8Var;
	UINT16 Uint16Var;
	UINT32 Uint32Var;
	UINT16 DisableFlag = 0;
	UINT16 EnableFlag = FALSE;
	UINT32 Uint32PowerTest;
	length += AddToBuffer(&to, (UINT8) (ID >> 8));
	length += AddToBuffer(&to, (UINT8) ID);
	Uint8Var = Map[PositionInMap].DataType;
	length += AddToBuffer(&to, (UINT8) Uint8Var);
	if (Map[PositionInMap].Function1 != NULL) {
		Map[PositionInMap].Function1();
	}
	if (Map[PositionInMap].Eptr != 0)
		EnableFlag = (*(Map[PositionInMap].Eptr));
	if ((Map[PositionInMap].Eptr == 0) || (EnableFlag == TRUE)) {
		if (Map[PositionInMap].Eptr != 0) {
			length += AddToBuffer(&to, (UINT8) EnableFlag);
		} else {
			length += AddToBuffer(&to, (UINT8) 1);
		}

		switch (Map[PositionInMap].DataType) {
		case Uint8:
		case sint8:
			Uint8Var = *((UINT8*) (Map[PositionInMap].Vptr));
			length += AddToBuffer(&to, (UINT8) Uint8Var);
			break;
		case boolean:
			Uint8Var = *((BOOLEAN*) (Map[PositionInMap].Vptr));
			length += AddToBuffer(&to, (UINT8) Uint8Var);
			break;
		case UInt16:
		case sint16:
			Uint16Var = *((UINT16*) (Map[PositionInMap].Vptr));
			length += AddToBuffer(&to, (UINT8) (Uint16Var >> 8));
			length += AddToBuffer(&to, (UINT8) Uint16Var);

			break;
		case Uint32:
		case sint32:
			Uint32Var = *((UINT32*) (Map[PositionInMap].Vptr));
			if(Map[PositionInMap].DisableFlag)
				DisableFlag = *((UINT16*) (Map[PositionInMap].DisableFlag));
			if ((ID == AMP1_FIX_ID && (CurrentPreset.Amp2Flag & BIT0)
					&& (CurrentPreset.WeldMode != CONTINUOUSMODE)) ||
					(ID == WELD_PRESSURE_ID && (CurrentPreset.Pressure2Flag & BIT0)) ||
					(ID == XSCALE_SET && (CurrentPreset.WeldMode == TIMEMODE)
					&& (CurrentPreset.AutoScaleFlag & BIT0))) {
						length += AddToBuffer(&to, 0);
				}
				else {
					length += AddToBuffer(&to, 1);
					if (Map[PositionInMap].DisableFlag == NULL) {
						length += AddToBuffer(&to, 0);
						length += AddToBuffer(&to, 0);

					} else {
						length += AddToBuffer(&to, (UINT8) (DisableFlag >> 8));
						length += AddToBuffer(&to, (UINT8) (DisableFlag));
					}
					if((ID == ERRORCODE_ID)&&(ErrorCodeFlag == TRUE))
					{
						length += AddToBuffer(&to, (UINT8) (ErrorCode >> 24));
						length += AddToBuffer(&to, (UINT8) (ErrorCode >> 16));
						length += AddToBuffer(&to, (UINT8) (ErrorCode >> 8));
						length += AddToBuffer(&to, (UINT8) (ErrorCode));
					}
					else if (ID == POWER_TEST) {
						Uint32PowerTest = Uint32Var;
						Uint32PowerTest = (Uint32PowerTest * CurrentSetup.PSWatt
							/ 1000);
					length += AddToBuffer(&to, (UINT8) (Uint32PowerTest >> 24));
					length += AddToBuffer(&to, (UINT8) (Uint32PowerTest >> 16));
					length += AddToBuffer(&to, (UINT8) (Uint32PowerTest >> 8));
					length += AddToBuffer(&to, (UINT8) (Uint32PowerTest));
				} else {
					length += AddToBuffer(&to, (UINT8) (Uint32Var >> 24));
					length += AddToBuffer(&to, (UINT8) (Uint32Var >> 16));
					length += AddToBuffer(&to, (UINT8) (Uint32Var >> 8));
					length += AddToBuffer(&to, (UINT8) (Uint32Var));
				}
				if (ID == PSFREQ_WATTINFO) {
					length += AddToBuffer(&to, (UINT8) LangStrLen(PSFreqTxt));
					length += AddToBufferString(&to, ((SINT8*) (PSFreqTxt)),
							LangStrLen(PSFreqTxt));
				}
			}
			break;
		case str:
			length += AddToBuffer(&to, (UINT8) LangStrLen(
					((SINT8*) (Map[PositionInMap].Vptr))));
			length += AddToBufferString(&to,
					((SINT8*) (Map[PositionInMap].Vptr)), LangStrLen(
							((SINT8*) (Map[PositionInMap].Vptr))));
			break;
		case arr:
			length += SendArrayData(&to, PositionInMap);
			break;
		case nothing: // no data have been added to buffer.
		default:
			break;
		}
	} else {
		length += AddToBuffer(&to, (UINT8) 0);
	}
	return length;
}

UINT16 XMLDataResponse(UINT16 PositionInMap, UINT8 *ReceiveValuePtr,
		UINT8 * to, UINT16 ID)
/****************************************************************************/
/* This function receives data from SBC side and stores it into the desired */
/* place according to Map ID sent by SBC side. As Map ID corresponds to a   */
/* set of structure information and according to corresponding data types   */
/* of Map IDs,1-byte, 2-byte, 4-byte, array or boolean data type are being  */
/* stored and for this a no. of different type pointers are taken here that */
/* point to same location where data have to be stored.                     */
/****************************************************************************/
{
	UINT8 *Uint8Ptr = (UINT8 *) (Map[PositionInMap].Vptr);
	BOOLEAN *BoolPtr = (BOOLEAN *) (Map[PositionInMap].Vptr);
	UINT16 *Uint16Ptr = (UINT16 *) (Map[PositionInMap].Vptr);
	UINT32 *Uint32Ptr = (UINT32 *) (Map[PositionInMap].Vptr);
	UINT16 *DisablePtr = (UINT16*) (Map[PositionInMap].DisableFlag);
	UINT8 *Arr = (UINT8 *) (Map[PositionInMap].Vptr);
	UINT8 *Value = (UINT8 *) ReceiveValuePtr;
	UINT16 length = 0; // length of data in output buffer
	memset(ParamNewVal, 0, sizeof(ParamNewVal));
	memset(ParamOldVal, 0, sizeof(ParamOldVal));
	DisableFlagOldValue = 0;
	DisableFlagNewValue = 0;
	Type = nothing;

   switch (Map[PositionInMap].DataType) {
	case boolean:
		Type = boolean;
		if (*Value)
		   {
			strcpy((char*)ParamOldVal,"OFF");
			strcpy((char*)ParamNewVal,"ON");
			*BoolPtr = TRUE;
		   }
		else
		   {
			strcpy((char*)ParamOldVal,"ON");
			strcpy((char*)ParamNewVal,"OFF");
		    *BoolPtr = FALSE;
		   }

		if (*Value != 0) //Send back Toggle value
			length += AddToBuffer(&to, (UINT8) 1);
		else
			length += AddToBuffer(&to, (UINT8) 0);

		if ((ID == UNIT_SET) || (ID == WELDTRIG_ENABLEID ) || (ID == VALIDATEPS_ENABLEID ) || ( ID == LOCKPS_ENABLEID )) //send a byte as either 1 in case of Unit change or  0 in other case
			length += AddToBuffer(&to, (UINT8) 1);
		else
			length += AddToBuffer(&to, (UINT8) 0);

		break;

	case Uint8:
	case sint8:
		memcpy(ParamOldVal, Uint8Ptr, sizeof(UINT8));
		memcpy(ParamNewVal, Value, sizeof(UINT8));
		Type = Uint8;
		*Uint8Ptr = (UINT8) (*Value);
		break;

	case UInt16:
	case sint16:
		if (ID != DIGITAL_TUNE_CHOICE || DigitalPotEntry()) {

			memcpy(ParamOldVal, Uint16Ptr, sizeof(UINT16));
			memcpy(ParamNewVal, Value, sizeof(UINT16));
			Type = UInt16;
			*Uint16Ptr = ((UINT16) (*Value) << 8) + (UINT16) (*(Value + 1));
			if (ID == DIGITAL_TUNE_CHOICE)
				VGADigitalPotChoiceDone();
			if ((ID == WELDMODE_SET) || (ID == PRST_RECALL) || (ID
					== PASSWD_ENTRY))
				length += AddToBuffer(&to, (UINT8) 1);
			else
				length += AddToBuffer(&to, (UINT8) 0);

			length += AddToBuffer(&to, (UINT8) ((*Uint16Ptr) >> 8));//TODO: Here the bug found by coverity is fixed.
																	//The affect of this fix on already working application needs to be
																	//monitored.
			length += AddToBuffer(&to, (UINT8) (*Uint16Ptr));
			if (ID == PRST_VERIFY)
				length += ProcessPresetVerify(&to);
		} else {
			NackError = WELDER_PROCESS_ERROR;
			ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
			ErrorResponseMaxLimit = 0;
		}
		break;

	case Uint32:
	case sint32:
		if(DisablePtr){
			DisableFlagOldValue = *DisablePtr;
			*DisablePtr = ((UINT16) (*Value) << 8) + (UINT16) (*(Value + 1));
			DisableFlagNewValue =  *DisablePtr;
		}
		Value = Value + 2;
		memcpy(ParamOldVal, Uint32Ptr, sizeof(UINT32));
		memcpy(ParamNewVal, Value, sizeof(UINT32));
		Type = Uint32;
		*Uint32Ptr = ((UINT32) (*Value) << 24)
				+ ((UINT32) (*(Value + 1)) << 16) + ((UINT32) (*(Value + 2))
				<< 8) + ((UINT32) (*(Value + 3)));
		break;
	case arr:
		strncpy((char*) ParamOldVal, (char *) Arr, sizeof(ParamOldVal) - 1);
		/* The 0th element of the array contains the length of the array*/
		if((UINT8) (*Value) < sizeof(ParamNewVal))
			strncpy((char*) ParamNewVal, (char *) (Value+1), (UINT8) (*Value));
		else
			strncpy((char*) ParamNewVal, (char *) (Value+1), sizeof(ParamNewVal) - 1);
       	Type = arr;
		length += SetArrayData(&to, Value, Arr);
		break;

	case nothing:
		if (ID == PARAMETER_NUM) {
			SetRunScreenParam();
			length += WeldParams(&to, TotalCycle, AllParamColumnFlag);
		}
		break;
	default: // no data manipulation
		break;
	}

	length += AddToBuffer(&to, (UINT8) (ID >> 8));
	length += AddToBuffer(&to, (UINT8) ID);

	EventParameterID = (PARAM) Map[PositionInMap].ParameterId;
	if (Map[PositionInMap].Function2 != NULL) {
		Map[PositionInMap].Function2();
		    if (Uint16Ptr == &RadioIndex)
				memcpy(ParamOldVal, &RadioIndexOld, sizeof(UINT16));
		    if((ID != TWEAK_UP_ID) && (ID != TWEAK_DOWN_ID) && (ID != TWEAK_DOWNHD_ID)
		    		&& (ID != TWEAK_UPHD_ID) && (ID != WELD_PRESSURE_ID_HD) && (ID != FLOW_CONTROL_ID_HD) && (NackError != WELDER_PROCESS_ERROR))
		    	UpdateCurrentPresetAndSetup((PARAM) Map[PositionInMap].ParameterId);

	}
	else if ((Map[PositionInMap].DataType != nothing) && (ID != PRST_VERIFY))
		UpdateCurrentPresetAndSetup((PARAM) Map[PositionInMap].ParameterId);

	if (!DisplayNextMenu) {
		DisplayNextMenu = TRUE;
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
		ErrorResponseMaxLimit = 0;
	}
	return length;
}



/***************************************************************************
*                                                                         
*   Purpose:
*
*	This function checks the preset param id and the tweakLimit mask.If the bit for that
*	parameter is set then return false and don't invalidate preset
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
BOOLEAN SetupValid() {
	BOOLEAN Retval = FALSE;
	UINT16 MinMask = 0;
	UINT16 MaxMask = 0;
	if((CurrentPreset.Validated == FALSE) || (VGAHornDown == TRUE))
		Retval = FALSE;
	else
	{
		switch (GlobalCommandID) {
		case WELD_PRESSURE_ID:
		case PRESSUREMODE_SET:
			MaxMask = CurrentPreset.SetupLimits & WELDPRESSURE_PBIT;
			MinMask = CurrentPreset.SetupLimits & WELDPRESSURE_MBIT;
			if (!(MaxMask == WELDPRESSURE_PBIT))
				Retval = TRUE;
			else if (!(MinMask == WELDPRESSURE_MBIT))
				Retval = TRUE;
			break;
		case FLOW_CONTROL_ID:
			MaxMask = CurrentPreset.SetupLimits & DOWNSPEED_PBIT;
			MinMask = CurrentPreset.SetupLimits & DOWNSPEED_MBIT;
			if (!(MaxMask == DOWNSPEED_PBIT))
				Retval = TRUE;
			else if (!(MinMask == DOWNSPEED_MBIT))
				Retval = TRUE;
			break;
		case HOLD_PRESSURE_ID:
			MaxMask = CurrentPreset.SetupLimits & HOLDPRESSURE_PBIT;
			MinMask = CurrentPreset.SetupLimits & HOLDPRESSURE_MBIT;
			if (!(MaxMask == HOLDPRESSURE_PBIT))
				Retval = TRUE;
			else if (!(MinMask == HOLDPRESSURE_MBIT))
				Retval = TRUE;
			break;
		case HOLDTIME_ID:
			MaxMask = CurrentPreset.SetupLimits & HOLDTIME_PBIT;
			MinMask = CurrentPreset.SetupLimits & HOLDTIME_MBIT;
			if (!(MaxMask == HOLDTIME_PBIT))
				Retval = TRUE;
			else if (!(MinMask == HOLDTIME_MBIT))
				Retval = TRUE;
			break;
		case AMP1_ID:
		case AMP1_FIX_ID:
			MaxMask = CurrentPreset.SetupLimits & AMPA_PBIT;
			MinMask = CurrentPreset.SetupLimits & AMPA_MBIT;
			if (!(MaxMask == AMPA_PBIT))
				Retval = TRUE;
			else if (!(MinMask == AMPA_MBIT))
				Retval = TRUE;
			break;
		case TRIGGERFORCE_ID:
			MaxMask = CurrentPreset.SetupLimits & TRIGFORCE_PBIT;
			MinMask = CurrentPreset.SetupLimits & TRIGFORCE_MBIT;
			if (!(MaxMask == TRIGFORCE_PBIT))
			{
				Retval = TRUE;
			}
			else if (!(MinMask == TRIGFORCE_MBIT))
			{
				Retval = TRUE;
			}
			break;
		case WELDTIME_ID:
			MaxMask = CurrentPreset.SetupLimits & WELDTIME_PBIT;
			MinMask = CurrentPreset.SetupLimits & WELDTIME_MBIT;
			if (!(MaxMask == WELDTIME_PBIT))
				Retval = TRUE;
			else if (!(MinMask == WELDTIME_MBIT))
				Retval = TRUE;
			break;
		case WELDENERGY_ID:
			MaxMask = CurrentPreset.SetupLimits2 & WELDENERGY_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & WELDENERGY_MBIT;
			if (!(MaxMask == WELDENERGY_PBIT))
				Retval = TRUE;
			else if (!(MinMask == WELDENERGY_MBIT))
				Retval = TRUE;
			break;
		case PEAKPWR_ID:
			MaxMask = CurrentPreset.SetupLimits2 & PEAKPWR_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & PEAKPWR_MBIT;
			if (!(MaxMask == PEAKPWR_PBIT))
				Retval = TRUE;
			else if (!(MinMask == PEAKPWR_MBIT))
				Retval = TRUE;
			break;
		case COLDIST_ID:
			MaxMask = CurrentPreset.SetupLimits2 & COLDIST_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & COLDIST_MBIT;
			if (!(MaxMask == COLDIST_PBIT))
				Retval = TRUE;
			else if (!(MinMask == COLDIST_MBIT))
				Retval = TRUE;
			break;
		case ABSDIST_ID:
			MaxMask = CurrentPreset.SetupLimits2 & ABSDIST_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & ABSDIST_MBIT;
			if (!(MaxMask == ABSDIST_PBIT))
				Retval = TRUE;
			else if (!(MinMask == ABSDIST_MBIT))
				Retval = TRUE;
			break;
		case SCRUBTIME_ID:
			MaxMask = CurrentPreset.SetupLimits2 & SCRUBTIME_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & SCRUBTIME_MBIT;
			if (!(MaxMask == SCRUBTIME_PBIT))
				Retval = TRUE;
			else if (!(MinMask == SCRUBTIME_MBIT))
				Retval = TRUE;
			break;
		case AMPSCRUBTIME_ID:
			MaxMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & AMPSCRUBTIME_MBIT;
			if (!(MaxMask == AMPSCRUBTIME_PBIT))
				Retval = TRUE;
			else if (!(MinMask == AMPSCRUBTIME_MBIT))
				Retval = TRUE;
			break;
		case TRIGGERDISTANCE_ID:
			MaxMask = CurrentPreset.SetupLimits2 & TRIGDIST_PBIT;
			MinMask = CurrentPreset.SetupLimits2 & TRIGDIST_MBIT;
			if (!(MaxMask == TRIGDIST_PBIT))
				Retval = TRUE;
			else if (!(MinMask == TRIGDIST_MBIT))
				Retval = TRUE;
			break;
		};
	}

	return Retval;
}

UINT16 SendMinMaxData(UINT8 * to, UINT16 PositionInMap)
/**************************************************************************/
/* This function provides minimum and maximum values for a variable entry */
/* according to Map ID sent by SBC side.                                  */
/**************************************************************************/

{
	UINT16 length = 0;
	SINT32 Max, Min;

	Max = *((SINT32 *) (MinMap[PositionInMap].ptrmax));
	Min = *((SINT32 *) (MinMap[PositionInMap].ptrmin));
	if ((GlobalCommandID == AMP1_FIX_ID
			&& (CurrentPreset.Amp2Flag & BIT0) && (CurrentPreset.WeldMode
			!= CONTINUOUSMODE)) ||
			(GlobalCommandID == WELD_PRESSURE_ID && (CurrentPreset.Pressure2Flag & BIT0)) ||
	    	(GlobalCommandID == XSCALE_SET && (CurrentPreset.WeldMode
					== TIMEMODE) && (CurrentPreset.AutoScaleFlag & BIT0))
			|| (GlobalCommandID == RT_DIST && !(RapidTraverseState & BIT0))
			|| (MinMap[PositionInMap].ptrmax == MinMap[PositionInMap].ptrmin)) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
		ErrorResponseMaxLimit = 0;
	} else if (GlobalCommandID == DIGITAL_FREQ) {
		DiagFlag = FALSE; //Disable diagnostics
		ForceDigitalTuneTest = FALSE;
		if (CurrentSetup.DigTuneFlag && DigitalPotEntry()) {
			ResetStateMachine(); /* Position is at original value, */
			StartStateMachine(); /* don't need to force Test.      */
			if (DigitalFreqEntry())/*Make sure in READY first */
				SaveDigTuneValue = DigTuneValue;
			else {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
				ErrorResponseMaxLimit = 0;
			}
		} else {
			NackError = WELDER_PROCESS_ERROR;
			ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
			ErrorResponseMaxLimit = 0;
		}
	}

	if (!NackError)/*Editable VARIABLE */
	{
		if ((VGAHornDown) && (GlobalCommandID != WELD_PRESSURE_ID_HD) && (GlobalCommandID != FLOW_CONTROL_ID_HD)) {
			ProcessHDButtonPress3();
			ResetStateMachine(); /* Stop the State machine*/
			ClearReady();
		}
		length += AddToBuffer(&to, (UINT8) (Min >> 24));
		length += AddToBuffer(&to, (UINT8) (Min >> 16));
		length += AddToBuffer(&to, (UINT8) (Min >> 8));
		length += AddToBuffer(&to, (UINT8) (Min));

		length += AddToBuffer(&to, (UINT8) (Max >> 24));
		length += AddToBuffer(&to, (UINT8) (Max >> 16));
		length += AddToBuffer(&to, (UINT8) (Max >> 8));
		length += AddToBuffer(&to, (UINT8) (Max));
	}
	return (length);
}

UINT16 SendArrayData(UINT8 ** to, UINT16 PositionInMap)
/**************************************************************************/
/* This function provides array type values for different menus           */
/* according to GlobalCommandID sent by SBC side.                         */
/**************************************************************************/
{
	UINT16 Index;
	UINT16 Index1;
	SINT8 TempStr1[10];
	UINT16 length = 0;

	if (GlobalCommandID == PRST_LISTING) {
	    Index = VGAPresetNum;
		for (Index1 = 0; (Index <= MaxPresetNumber) && (Index1 < MAX_PRESET_PER_SCREEN); Index1++) {
         	strncpy(PresetListBoxBuffer, (char*) PresetNamePtrs[Index], VGA_LINESIZE - 1);
			length += AddToBuffer(to, strlen(PresetListBoxBuffer));
			length += AddToBufferString(to, PresetListBoxBuffer, strlen(
					PresetListBoxBuffer));
			Index++;
		}
	} else if (GlobalCommandID == PRST_INFO) {
		if ((PresetEnableFlags[VGAPresetNum] == TRUE) && (VGAPresetNum > 0)) {
			/* Display the Date when preset was saved. */
			length += AddToBuffer(to, strlen(InfoLine4));
			length += AddToBufferString(to, InfoLine4, strlen(InfoLine4));
			/* Display the Time when preset was saved. */
			length += AddToBuffer(to, strlen(InfoLine5));
			length += AddToBufferString(to, InfoLine5, strlen(InfoLine5));
			/* Display the weld count of the preset. */
			length += AddToBuffer(to, strlen(InfoLine6));
			length += AddToBufferString(to, InfoLine6, strlen(InfoLine6));
			/* Display the verify status. */
			if (InfoLine3[0] == '1')
			{
				length += AddToBuffer(to, (UINT8) 1);
			}
			else{
				length += AddToBuffer(to, (UINT8) 0);
			}
			if (InfoLine2[0] == '1'){
				length += AddToBuffer(to, (UINT8) 1);
			}
			else
			{
				length += AddToBuffer(to, (UINT8) 0);
			}
		} else{
			length += AddToBuffer(to, 0);			
		}
	} else if (GlobalCommandID == SEQUENCE_LISTING) {
		for (Index = 0; Index < MAX_SEQUENCE_NOS; Index++) {
			sprintf(TempStr1, "%2d", Index + 1);
			strcat(TempStr1, ". ");
			strcpy(PresetListBoxBuffer, TempStr1);
			if (Index < CurrentSetup.SequenceCount) {
				Index1 = CurrentSetup.SequenceList[Index];
				strncat(PresetListBoxBuffer, (char*)PresetNamePtrs[Index1], sizeof(PresetListBoxBuffer) - strlen(PresetListBoxBuffer) -  1);
				length += AddToBuffer(to, strlen(PresetListBoxBuffer));
				length += AddToBufferString(to, PresetListBoxBuffer, strlen(
						PresetListBoxBuffer));
			} else {
				length += AddToBuffer(to, strlen(PresetListBoxBuffer));
				length += AddToBufferString(to, PresetListBoxBuffer, strlen(
						PresetListBoxBuffer));
			}
		}
	} else if (GlobalCommandID == TIME_INFO || GlobalCommandID == DATE_INFO
			|| GlobalCommandID == CALIBRATE_INFO) {
		if (GlobalCommandID == DATE_INFO || GlobalCommandID == CALIBRATE_INFO) //For Date Array
			Index = 3;
		else
			//for Time Array
			Index = 2;
		length += AddToBuffer(to, (UINT8) Index);
		length += AddToBufferString(to, ((SINT8*) (Map[PositionInMap].Vptr)),
				(UINT8) Index);
	} else {
		length += AddToBuffer(to, (UINT8) strlen(
				((SINT8*) (Map[PositionInMap].Vptr))));
		length += AddToBufferString(to, ((SINT8*) (Map[PositionInMap].Vptr)),
				strlen(((SINT8*) (Map[PositionInMap].Vptr))));
	}
	return (length);
}

UINT16 SetArrayData(UINT8 ** to, UINT8 *Value, UINT8 *Arr)
/**************************************************************************/
/* This function sets array type values for different menus               */
/* according to GlobalCommandID.                                          */
/**************************************************************************/
{
	UINT16 length = 0, i;
	UINT8 ArrayLength;

	ArrayLength = (UINT8) (*Value);
	if (GlobalCommandID == SEQUENCE_LIST_UPDATE) {
		CurrentSetup.SequenceCount = ArrayLength;
		if (CurrentSetup.SequenceNos >= CurrentSetup.SequenceCount)
			CurrentSetup.SequenceNos = 0;
	}
	if (GlobalCommandID == PASSWD_SAVE) {
		Value++;
		PasswdEntryFlag = (UINT8) (*Value);
		ArrayLength--;
	}
	if (GlobalCommandID == PSSERIAL_NUMID)
		if (ArrayLength > SERIALLENGTH)
			NackError = PARAMETER_ERROR;
		else
            for (i = 1; i <= ArrayLength; i++) /* Test serial number for printable ascii */
			{
				if ((*(Value + i)) < ' ' ) {
					NackError = PARAMETER_ERROR;
					break;
				}
			}

	if (GlobalCommandID == ACTSERIAL_NUMID)
		if (ArrayLength > MAXSERIALNUM)
			NackError = PARAMETER_ERROR;

	if (!NackError) {
		if (GlobalCommandID == SEQUENCE_LIST_UPDATE)
		{
			Value++;
			/*Preset number is now 16 bit so we are sending 16 bit array
			It needs to be taken care differently*/
			for (i = 0; i < (ArrayLength * 2); i += 2){

				*(Arr + i) = (UINT8) (*Value);
				 Value++;
				*(Arr + i + 1) = (UINT8) (*Value);
				 Value++;
			}
		}
		else{
			for (i = 0; i < ArrayLength; i++) {
				Value++;
				*(Arr + i) = (UINT8) (*Value);
			}
			*(Arr + i) = '\0';
		}
	}
	if (GlobalCommandID == PASSWD_SAVE)
		length += PasswordSave(to);
	return (length);
}

UINT16 SendBargraphData(UINT8 **to, SINT32 *VPtr)
/**************************************************************************/
/* This function provides Bargraph position information.                  */
/**************************************************************************/
{
	UINT16 length = 0;
	UINT32 Index;
	UINT8 Value = (UINT8) (*VPtr);

	switch (Value) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		Index = Value;
		break;
	default:
		Index = 13;
		break;
	}
	length += AddToBuffer(to, (UINT8) (Index >> 24));
	length += AddToBuffer(to, (UINT8) (Index >> 16));

	length += AddToBuffer(to, (UINT8) (Index >> 8));
	length += AddToBuffer(to, (UINT8) Index);

	return (length);
}

UINT16 ScanInfoStatus(UINT8 **to)
/**************************************************************************/
/* This function provides HornScan status information.                    */
/**************************************************************************/
{
	UINT16 length = 0;

	switch (HornScanInfo.ScanStatus) {
	case DUPS_SCANINPROG:
		if (PrevHornState != DUPS_SCANINPROG)
			PrevHornState = DUPS_SCANINPROG;
		length += AddToBuffer(to, (UINT8) 1);
		length += AddToBuffer(to, (UINT8) 1);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		break;

	case DUPS_SCANDATAAVAIL:
		if (PrevHornState != DUPS_SCANDATAAVAIL) {
			EnableWelding();
			PrevHornState = DUPS_SCANDATAAVAIL;
		}
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 1);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		break;

	case DUPS_NOSCAN:
		if (PrevHornState != DUPS_NOSCAN) {
			EnableWelding();
			PrevHornState = DUPS_NOSCAN;
		}
		if (VGAHornScanOLD) {
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 1);
			length += AddToBuffer(to, (UINT8) 0);
		} else {
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 1);
			length += AddToBuffer(to, (UINT8) 0);
			length += AddToBuffer(to, (UINT8) 0);
		}
		break;

	case DUPS_SCANSCOMPLETE:
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 1);
		break;

	default:
		length += AddToBuffer(to, (UINT8) 1);
		length += AddToBuffer(to, (UINT8) 1);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		length += AddToBuffer(to, (UINT8) 0);
		break;
	}
	return (length);
}

UINT16 SendBottomHalfData(UINT8 *to, UINT16 BottomHalfID)
/**************************************************************************/
/* This function provides data for formation of Bottom Half screen        */
/**************************************************************************/
{
	UINT16 length = 0, i;
	UINT32 Uint32PowerTest;
	switch (BottomHalfID) {
	case DIGITAL_TUNE_CHOICE:
		length += AddToBuffer(&to, (UINT8) 0);
		length += AddToBuffer(&to, (UINT8) 2);
		length += SendBargraphData(&to, &FMemoryBargraph);
		length += SendBargraphData(&to, &FActualBargraph);
		length += AddToBuffer(&to, (UINT8) 6);
		length += AddToBuffer(&to, (UINT8) (1));
		length += AddToBuffer(&to, (UINT8) (1));
		GetRunSelection();
		length += AddToBuffer(&to, (UINT8) (VGARunSelected));
		GetClearSelection();
		length += AddToBuffer(&to, (UINT8) (VGAClearSelected));
		GetSeekSelection();
		length += AddToBuffer(&to, (UINT8) (VGASeekSelected));
		GetStoreSelection();
		length += AddToBuffer(&to, (UINT8) (VGAStoreSelected));
		break;

	case HS_START:
		length += AddToBuffer(&to, (UINT8) 6);
		for (i = 0; i < DUPS_NUMRESONANCES; i++) // Resonance frequency value
		{
			length += AddToBuffer(&to,
					(UINT8) ((HornScanInfo.ResonanceFreqs[i]) >> 24));
			length += AddToBuffer(&to,
					(UINT8) ((HornScanInfo.ResonanceFreqs[i]) >> 16));
			length += AddToBuffer(&to,
					(UINT8) ((HornScanInfo.ResonanceFreqs[i]) >> 8));
			length
					+= AddToBuffer(&to,
							(UINT8) (HornScanInfo.ResonanceFreqs[i]));
		}

		length += AddToBuffer(&to, (UINT8) 6);
		for (i = 0; i < DUPS_NUMRESONANCES; i++) // Resonance frequency type either series or parallel
		{
			length += AddToBuffer(&to, (UINT8) (FreqType[i]));
		}
		length += AddToBuffer(&to, (UINT8) 13);

		for (i = 0; i < DUPS_NUMRESONANCES; i++)
			length += AddToBuffer(&to, (UINT8) (ResonanceFreqEnable[i])); //Enable Flag
		if (HSStartFlag)
			length += ScanInfoStatus(&to);
		else
			for (i = 0; i < 6; i++)
				length += AddToBuffer(&to, (UINT8) (0));
		length += AddToBuffer(&to, (UINT8) (1)); // to show exit button
		break;

	case HORN_DOWN_MENU:
		length += AddToBuffer(&to, (UINT8) HDMenuID);
		switch (HDMenuID) {
		case RESULT_MENU:
			length += AddToBuffer(&to, (UINT8) (4)); //Enable Flag
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentPressure));

			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 24));
			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 16));
			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 8));
			length += AddToBuffer(&to, (UINT8) (HDPosition));

			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentForce));

			length += AddToBuffer(&to, (UINT8) ((HornDownVelocity) >> 24));
			length += AddToBuffer(&to, (UINT8) ((HornDownVelocity) >> 16));
			length += AddToBuffer(&to, (UINT8) ((HornDownVelocity) >> 8));
			length += AddToBuffer(&to, (UINT8) (HornDownVelocity));

			length += AddToBuffer(&to, (UINT8) (5));
			length += AddToBuffer(&to, (UINT8) (HDShowPressure));
			length += AddToBuffer(&to, (UINT8) (1));
			length += AddToBuffer(&to, (UINT8) (HDShowForce));
			length += AddToBuffer(&to, (UINT8) (HDShowVelocity));
			length += AddToBuffer(&to, (UINT8) (KeepHornDown.Uint16.Hi));
			break;

		case RESULT_MENU_AE:
			length += AddToBuffer(&to, (UINT8) (0));
			length += AddToBuffer(&to, (UINT8) (1));
			length += AddToBuffer(&to, (UINT8) (KeepHornDown.Uint16.Hi));
			break;

		case REFRESH_MENU_AEF2:
			length += AddToBuffer(&to, (UINT8) (3)); //Enable Flag
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentPressure));

			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 24));
			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 16));
			length += AddToBuffer(&to, (UINT8) ((HDPosition) >> 8));
			length += AddToBuffer(&to, (UINT8) (HDPosition));

			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentForce) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentForce));

			length += AddToBuffer(&to, (UINT8) (3));

			length += AddToBuffer(&to, (UINT8) (HDShowPressure));
			length += AddToBuffer(&to, (UINT8) (1));
			length += AddToBuffer(&to, (UINT8) (HDShowForce));

			break;

		case REFRESH_MENU_AEF1:
		case REFRESH_MENU_AED:
			length += AddToBuffer(&to, (UINT8) (1)); //Enable Flag
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 24));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 16));
			length += AddToBuffer(&to, (UINT8) ((CurrentPressure) >> 8));
			length += AddToBuffer(&to, (UINT8) (CurrentPressure));
			length += AddToBuffer(&to, (UINT8) (1));
			length += AddToBuffer(&to, (UINT8) (HDShowPressure));
			break;

		case REFRESH_MENU_AE:
			length += AddToBuffer(&to, (UINT8) (0));
			length += AddToBuffer(&to, (UINT8) (0));
			break;
		default:
			break;
		}
		break;
	case TEST_AMPLITUDE:
		length += AddToBuffer(&to, (UINT8) 0);
		length += AddToBuffer(&to, (UINT8) 4);

		Uint32PowerTest = PowerTest;
		Uint32PowerTest = (Uint32PowerTest * CurrentSetup.PSWatt / 1000);
		length += AddToBuffer(&to, (UINT8) ((Uint32PowerTest) >> 24));
		length += AddToBuffer(&to, (UINT8) ((Uint32PowerTest) >> 16));
		length += AddToBuffer(&to, (UINT8) ((Uint32PowerTest) >> 8));
		length += AddToBuffer(&to, (UINT8) (Uint32PowerTest));

		length += AddToBuffer(&to, (UINT8) ((CurrentFreqIn) >> 24));
		length += AddToBuffer(&to, (UINT8) ((CurrentFreqIn) >> 16));
		length += AddToBuffer(&to, (UINT8) ((CurrentFreqIn) >> 8));
		length += AddToBuffer(&to, (UINT8) (CurrentFreqIn));

		length += SendBargraphData(&to, &FMemoryBargraph);
		length += SendBargraphData(&to, &FActualBargraph);
		length += AddToBuffer(&to, (UINT8) 8);
		length += AddToBuffer(&to, (UINT8) (1));
		length += AddToBuffer(&to, (UINT8) (1));
		length += AddToBuffer(&to, (UINT8) (1));
		length += AddToBuffer(&to, (UINT8) (1));
		GetRunSelection();
		length += AddToBuffer(&to, (UINT8) (VGARunSelected));
		GetClearSelection();
		length += AddToBuffer(&to, (UINT8) (VGAClearSelected));
		GetSeekSelection();
		length += AddToBuffer(&to, (UINT8) (VGASeekSelected));
		GetStoreSelection();
		length += AddToBuffer(&to, (UINT8) (VGAStoreSelected));
		break;
	default: // no data have been provided to buffer
		break;
	}
	return (length);
}

void ProcessWindowSetup(void) {
	if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE)) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
		ErrorResponseMaxLimit = 0;
	} else {
		WindowSetupFlag = TRUE;
		VGA_ReadyFlag = ReadyFlag;
		ReadyFlag = FALSE;
		ResetStateMachine();
		ClearReady();
		FirmwareUploadAllowed = FALSE;
	}
}
void CheckforDisplayLock(void) {
	if ((Inp.DisplayLockFlag) && (UserLoggedIn == TRUE)) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = SHOW_MAIN_MENU;
		ErrorResponseMaxLimit = 0;
	}
}

UINT16 ProcessHostCommand(UINT32 Value32, UINT16 Function, UINT8 *DataPointer,
		UINT16 CommandCount, UINT8 * AckBuf, SOURCE_TASK_ID_TYPE Source_Task)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds reply for General Host commands and writes data in  */
/* in buffer                                                                */
/*Input Parameters:-                                                        */
/* Value32: First four data bytes are mostly pointer value                  */
/* Function: Host command Function number                                   */
/* Datapointer: Pointer to the host command data                            */
/* CommandCount: Nos of data bytes in a command                             */
/* AckBuf: Buffer where reply is written                                    */
/* Source_Task: Identifies source task from where the command came          */
/*Returns length of the bytes written to the buffer                         */
/****************************************************************************/

{
	FP_KEY_PRESSED_MSG FpkpQueue;

	UINT16 i, Count, j;
	UINT16 NoAckOrNak = FALSE;
	UINT16 SubFunction = 0;

	/* ActionFlags are used for commands that change more than 1 variable to
	 defer the actions until all parameter limit tests have been performed.
	 This is to prevent partial implementation of a command with a parameter
	 error.   */
	UINT16 ActionFlags[MAXACTIONFLAGS];
	UINT32 Params[MAXACTIONFLAGS];
	UINT8 Value8;
	UINT16 Value16;
	UINT8 *Host8;
	UINT8 *TempPtr;
	UINT16 *Host16;
    int	TempVar;

	memset(Params, 0, sizeof(Params));
	for (Count = 0; Count < MAXACTIONFLAGS; Count++)
		ActionFlags[Count] = FALSE; /* zero all action flags */

	i = 0;
	switch (Function) {

	case DOWNLOAD_CURRENT_PRESET: /* Copy the data to HostPreset structure.*/
		if (CommandCount == DOWNLOADCOMMAND_SIZE) {
			memcpy((UINT8 *) &HostPreset, (UINT8 *) DataPointer,
		                  sizeof(Ver1200Setups));
			HostPresetEmpty = FALSE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case UPLOAD_CURRENT_PRESET:
		if (CommandCount == UPLOADCOMMAND_SIZE) {

			
		    TempPtr = (UINT8 *)Readpreset(CURRENT_PRESET_INDEX);			
			/*Data in the Preset 0 is same as Current Preset Except some
			 nonmatching members.Send the data in compressed form from
			 compressed preset only.*/
			i = 0;
			AckBuf[i++] = ACK;
			AckBuf[i++] = DLE;
			AckBuf[i++] = STX;
			/* Increment index over byte count */
			i += 2;
			/* fill in function */
			AckBuf[i++] = (UINT8) (Function >> 8);
			AckBuf[i++] = (UINT8) Function;
			/* fill in Error */
			AckBuf[i++] = (UINT8) Inp.DisplayLockFlag;
			/*Fill the Preset Data*/
			for (j = 0; j < sizeof(Ver1200Setups); j++)
				AckBuf[i++] = *TempPtr++;
			/* fill in byte count */
			AckBuf[3] = (UINT8) ((i - 3) >> 8);
			AckBuf[4] = (UINT8) (i - 3);
			/* compute checksum */
			AckBuf[i] = 0;
			for (j = 3; j < i; j++)
				AckBuf[i] ^= AckBuf[j];
			i++;
			/* add DLE, ETX to message */
			AckBuf[i++] = DLE;
			AckBuf[i++] = ETX;
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case REQUEST_GRAPH_DATA:
		if (CommandCount == GRAPHCOMMAND_SIZE) {
			Host16 = (UINT16 *) DataPointer;
			Value16 = *Host16;
			i = 0;
			AckBuf[i++] = ACK;
			AckBuf[i++] = DLE;
			AckBuf[i++] = STX;
			i += 2; /* Increment index over byte count */
			AckBuf[i++] = (UINT8) (Function >> BYTE3SHIFT); /* fill in function */
			AckBuf[i++] = (UINT8) Function;
			AckBuf[i++] = (UINT8) Inp.DisplayLockFlag; /* fill in display lock info */

			switch (Value16) { /*Fill the graph Data*/
			case POWERGRAPH:
				SetupVals(POWGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case AMPGRAPH:
				SetupVals(AMPLIGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case FREQGRAPH:
				SetupVals(FREQUGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case COLDISTGRAPH:
				SetupVals(DISTINGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case VELOCITYGRAPH:
				SetupVals(VELINGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case FORCEGRAPH:
				SetupVals(FORCELBGRAPH, val2);
				i += CreateGraphHeader(Value16, &AckBuf[i]);
				for (j = 0; j < MsPointer->count; j++) {
					AckBuf[i++] = (UINT8) (val2[j] >> BYTE3SHIFT);
					AckBuf[i++] = (UINT8) (val2[j]);
				}
				break;

			case HORNSCAN:
				NackError = ILLEGAL_COMMAND; /* Until Hornscan done */
				break;

			default:
				NackError = ILLEGAL_COMMAND;
			}

			if (!NackError) {
				AckBuf[3] = (UINT8) ((i - 3) >> BYTE3SHIFT);/* fill in byte count */
				AckBuf[4] = (UINT8) (i - 3);

				AckBuf[i] = 0; /* compute checksum   */
				for (j = 3; j < i; j++)
					AckBuf[i] ^= AckBuf[j];
				i++;

				AckBuf[i++] = DLE; /* add DLE, ETX to message */
				AckBuf[i++] = ETX;
				NoAckOrNak = TRUE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case RESET_ALARMS:

		if (CommandCount == RESETALARMS_SIZE) {
			if ((KeyMask & RESETKEYMASK) == RESETKEYMASK)
			/*Check if Reset key is enabled */
			{
				ResetFailed = FALSE;
				ResetAlarmProcessed = FALSE;
				FpkpQueue.key = ResetKey;
				/*Send the key to FPK_TASK */
				FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
				FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(0, *((FPKP_MSG_QUEUE_TYPE*) &FpkpQueue), 0);
				while (!ResetAlarmProcessed)/*Wait to Key processing in weldmngr*/
					RTOS::DelayMs(SECONDS_TO_TICKS( 1 ) * MILLS_PER_TICK);
				if (ResetFailed)/*Check for any non-resetable alarm*/
					NackError = HARDWARE_FAILURE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case RECALL_PRESET:
		Host8 = (UINT8 *) DataPointer;
		if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
				&& (IsGraphDrawing == FALSE)) { // Ok to recall preset since no weld in progress
			if (PresetEnableFlags[*Host8]) {
				RecallPreset(*Host8);
				SystemParameterChgdFlag = TRUE;
			} else
				NackError = PARAMETER_ERROR;
		} else {
			/* PARAMETER_ERROR is temporary pending Ver9 and verbose error messages. */
			NackError = PARAMETER_ERROR;
		}
		break;

	case SET_CURRENT_PRESET_PARAMETERS:

		/* Extract number of parms from message */
		Host16 = (UINT16 *) DataPointer;
		Value16 = *Host16;
		Host16++; /* Point to 1st PARMID */

		/* Process each parameter */
		for (Count = 0; Count < Value16; Count++) {
			/* Break out of for loop if error encountered */
			if (NackError)
				break;

			/* Switch on Parm Id */
			SubFunction = *Host16;
			switch (SubFunction) {
			case WELDTIME:

				Host16++; /* Point to number of bytes for this parameter */
				Host16++; /* Point to 1st parameter byte */
				Value32 = *(SINT32 *) Host16;

				/* Store upper and lower bounds in case of error */
				ErrorResponseMinLimit = MinLimit.WeldTime;
				ErrorResponseMaxLimit = MaxLimit.WeldTime;
				SubFunction = WELDTIME;

				if (Value32 >= (UINT32)MinLimit.WeldTime) {
					if (Value32 <= (UINT32)MaxLimit.WeldTime) {
						ActionFlags[0] = TRUE;
						Params[0] = Value32;
					} else
						NackError = MAX_ERROR;
				} else
					NackError = MIN_ERROR;

				Host16 += 2; /* Point to next PARMID */
				break;

			case HOLDTIME:

				Host16++; /* Point to number of bytes for this parameter */
				Host16++; /* Point to 1st parameter byte */
				Value32 = *(SINT32 *) Host16;

				/* Store upper and lower bounds in case of error */
				ErrorResponseMinLimit = MinLimit.HoldTime;
				ErrorResponseMaxLimit = MaxLimit.HoldTime;
				SubFunction = HOLDTIME;

				if (!Value32)
					ActionFlags[1] = TRUE;

				else if (Value32 >= (UINT32)MinLimit.HoldTime) {
					if (Value32 <= (UINT32)MaxLimit.HoldTime) {
						ActionFlags[2] = TRUE;
						Params[2] = Value32;
					} else
						NackError = MAX_ERROR;
				} else
					NackError = MIN_ERROR;

				Host16 += 2; /* Point to next PARMID */
				break;

			case PEAKPOWER:

				Host16++; /* Point to number of bytes for this parameter */
				Host16++; /* Point to 1st parameter byte */
				Value32 = *(SINT32 *) Host16;

				/* Store upper and lower bounds in case of error */
				ErrorResponseMinLimit = MinLimit.PeakPwr;
				ErrorResponseMaxLimit = MaxLimit.PeakPwr;
				SubFunction = PEAKPOWER;

				if (Value32 >= (UINT32)MinLimit.PeakPwr) {
					if (Value32 <= (UINT32)MaxLimit.PeakPwr) {
						ActionFlags[3] = TRUE;
						Params[3] = Value32;
					} else
						NackError = MAX_ERROR;
				} else
					NackError = MIN_ERROR;

				Host16 += 2; /* Point to next PARMID */
				break;
			case ABSOLUTE:
				Host16++; /* Point to number of bytes for this parameter */
				Host16++; /* Point to 1st parameter byte */
				Value32 = *(SINT32 *) Host16;

				/* Store upper and lower bounds in case of error */
				ErrorResponseMinLimit = MinLimit.AbsDist;
				ErrorResponseMaxLimit = MaxLimit.AbsDist;
				SubFunction = ABSOLUTE;
				if ((CurrentSetup.ExtPresets == TRUE)
						|| (CurrentSetup.SequenceEnable == TRUE))
					NackError = PARAMETER_ERROR;
				else {
					if (Value32 >= (UINT32)MinLimit.AbsDist) {
						if (Value32 <= (UINT32)MaxLimit.AbsDist) {
							ActionFlags[4] = TRUE;
							Params[4] = Value32;
						} else
							NackError = MAX_ERROR;
					} else
						NackError = MIN_ERROR;

				}
				Host16 += 2; /* Point to next PARMID */
				break;

			default:
				NackError = PARAMETER_ERROR;
				break;
			}
		}
		if (!NackError) {
			/* SET_WELD_TIME was 1st parameter */
			if (ActionFlags[0]) {
				CurrentPreset.WeldTime = Params[0];
				UpdateCurrentPreset(WELDTIME, 0, 0); /* Save to Fram */
				CurrentPresetParameterChanged = TRUE;
			}

			/* SET_HOLD_TIME is 2nd parameter */
			if (ActionFlags[1])
				/* value of 0 turns off hold time */
				CurrentPreset.HoldTimeFlag = TRUE; /* Disable Flag */

			if (ActionFlags[2]) {
				CurrentPreset.HoldTime = Params[2];
				CurrentPreset.HoldTimeFlag = FALSE;
			}
			UpdateCurrentPreset(HOLDTIME, 0, 0); /* Save to Fram */
			CurrentPresetParameterChanged = TRUE;
			/* Peak power is 3rd parameter */
			if (ActionFlags[3]) {
				CurrentPreset.PeakPwr = Params[3];
				UpdateCurrentPreset(PEAKPOWER, 0, 0); /* Save to Fram */
				CurrentPresetParameterChanged = TRUE;
			}
			if (ActionFlags[4]) {
				CurrentPreset.AbsDist = Params[4];
				UpdateCurrentPreset(ABSOLUTE, 0, 0); /* Save to Fram */
				CurrentPresetParameterChanged = TRUE;
			}
		}
		break;

		/* Set -Energy suspect limit */
	case SET_ENERGYMLS:

		ErrorResponseMinLimit = MinLimit.EnergyMLS;
		ErrorResponseMaxLimit = MaxLimit.EnergyMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MENERGYBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.EnergyMLS) {
			if (Value32 <= (UINT32)MaxLimit.EnergyMLS) {
				CurrentPreset.EnergyMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MENERGYBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ENERGYMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Energy suspect limit */
	case SET_ENERGYPLS:

		ErrorResponseMinLimit = MinLimit.EnergyPLS;
		ErrorResponseMaxLimit = MaxLimit.EnergyPLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PENERGYBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.EnergyPLS) {
			if (Value32 <= (UINT32)MaxLimit.EnergyPLS) {
				CurrentPreset.EnergyPLS = Value32;
				CurrentPreset.SuspectLimits &= (~PENERGYBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ENERGYPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Energy reject limit */
	case SET_ENERGYMLR:

		ErrorResponseMinLimit = MinLimit.EnergyMLR;
		ErrorResponseMaxLimit = MaxLimit.EnergyMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MENERGYBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.EnergyMLR) {
			if (Value32 <= (UINT32)MaxLimit.EnergyMLR) {
				CurrentPreset.EnergyMLR = Value32;
				CurrentPreset.RejectLimits &= (~MENERGYBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ENERGYMLR, 0, 0); /* Save to Fram */
		break;

		/* Set +Energy reject limit */
	case SET_ENERGYPLR:

		ErrorResponseMinLimit = MinLimit.EnergyPLR;
		ErrorResponseMaxLimit = MaxLimit.EnergyPLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PENERGYBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.EnergyPLR) {
			if (Value32 <= (UINT32)MaxLimit.EnergyPLR) {
				CurrentPreset.EnergyPLR = Value32;
				CurrentPreset.RejectLimits &= (~PENERGYBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ENERGYPLR, 0, 0); /* Save to Fram */
		break;

		/* Set -Time suspect limit */
	case SET_TIMEMLS:

		ErrorResponseMinLimit = MinLimit.TimeMLS;
		ErrorResponseMaxLimit = MaxLimit.TimeMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MTIMEBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.TimeMLS) {
			if (Value32 <= (UINT32)MaxLimit.TimeMLS) {
				CurrentPreset.TimeMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MTIMEBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(SUSPECTLIMITS, 0, 0); /* Save to Fram */
		break;

		/* Set +Time suspect limit */
	case SET_TIMEPLS:

		ErrorResponseMinLimit = MinLimit.TimePLS;
		ErrorResponseMaxLimit = MaxLimit.TimePLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PTIMEBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.TimePLS) {
			if (Value32 <= (UINT32)MaxLimit.TimePLS) {
				CurrentPreset.TimePLS = Value32;
				CurrentPreset.SuspectLimits &= (~PTIMEBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(SUSPECTLIMITS, 0, 0); /* Save to Fram */
		break;

		/* Set -Time reject limit */
	case SET_TIMEMLR:

		ErrorResponseMinLimit = MinLimit.TimeMLR;
		ErrorResponseMaxLimit = MaxLimit.TimeMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MTIMEBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.TimeMLR) {
			if (Value32 <= (UINT32)MaxLimit.TimeMLR) {
				CurrentPreset.TimeMLR = Value32;
				CurrentPreset.RejectLimits &= (~MTIMEBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(REJECTLIMITS, 0, 0); /* Save to Fram */
		break;

		/* Set +Time reject limit */
	case SET_TIMEPLR:

		ErrorResponseMinLimit = MinLimit.TimePLR;
		ErrorResponseMaxLimit = MaxLimit.TimePLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PTIMEBIT; /* Turn Flag Off   */

		else if (Value32 >= (UINT32)MinLimit.TimePLR) {
			if (Value32 <= (UINT32)MaxLimit.TimePLR) {
				CurrentPreset.TimePLR = Value32;
				CurrentPreset.RejectLimits &= (~PTIMEBIT); /* Turn Flag On    */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(REJECTLIMITS, 0, 0); /* Save to Fram */
		break;

	case START_WELD_DATA:
		if ((UINT16)Source_Task == (UINT16)SERIAL_INTERRUPT) {
			/* Request to start or stop sending weld data asynchronously over the link. */
			Host8 = (UINT8 *) DataPointer;
			Value8 = *Host8;
			if (Value8 == STOPASYNCWELDDATA || Value8 == STARTASYNCWELDDATA) {
				Host8++; /* point to send now flag */
				if (!(*Host8 == SENDNOWOFF || *Host8 == SENDNOWON)) /* test for over limit */
					NackError = PARAMETER_ERROR;
				else {
					CurrentSetup.SerialPort = RS232DISABLED;
					UpdateCurrentPreset(SENDWELDDATA, 0, 0);

					if (Value8 == STOPASYNCWELDDATA) {
						if (*Host8 == SENDNOWON) {
							i = ConvertWeldData(&FinalResults, AckBuf);
							LimitChanged = FALSE;
							NoAckOrNak = TRUE;
						}
					}
				}
			} else
				NackError = PARAMETER_ERROR;
		}
		else if ((UINT16)Source_Task == (UINT16)WELD_MGR) {
			/* Request to send weld data over the link. */
			i = ConvertWeldData((WELD_DATA*) DataPointer, AckBuf);
			NoAckOrNak = TRUE;
		} else
			NackError = INVALID_SOURCE;
		break;

	case SET_PEAKPOWER_CUTOFF:

		ErrorResponseMinLimit = MinLimit.PeakPwrCutoff;
		ErrorResponseMaxLimit = MaxLimit.PeakPwrCutoff;

		if (!Value32)
			/* a value of 0 disables the cutoff */
			CurrentPreset.PeakPwrCutoffFlag = BIT0; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.PeakPwrCutoff) {
			if (Value32 <= (UINT32)MaxLimit.PeakPwrCutoff) {
				CurrentPreset.PeakPwrCutoff = Value32;
				CurrentPreset.PeakPwrCutoffFlag = FALSE; /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(PEAKPOWERCUTOFF, 0, 0); /* Save to Fram */
		break;

	case SET_COLLDIST_CUTOFF:

		ErrorResponseMinLimit = MinLimit.ColCutoffDist;
		ErrorResponseMaxLimit = MaxLimit.ColCutoffDist;

		if (!Value32)
			/* a value of 0 disables the cutoff */
			CurrentPreset.ColCutoffFlag = BIT0; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.ColCutoffDist) {
			if (Value32 <= (UINT32)MaxLimit.ColCutoffDist) {
				CurrentPreset.ColCutoffDist = Value32;
				CurrentPreset.ColCutoffFlag = FALSE; /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(COLLCUTOFFDIST, 0, 0); /* Save to Fram */
		break;

		/* Set -Power Suspect Limit */
	case SET_MPOWER_SLIMIT:

		ErrorResponseMinLimit = MinLimit.PowerMLS;
		ErrorResponseMaxLimit = MaxLimit.PowerMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MPKPOWERBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.PowerMLS) {
			if (Value32 <= (UINT32)MaxLimit.PowerMLS) {
				CurrentPreset.PowerMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MPKPOWERBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(POWERMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Power Suspect Limit */
	case SET_PPOWER_SLIMIT:

		ErrorResponseMinLimit = MinLimit.PowerPLS;
		ErrorResponseMaxLimit = MaxLimit.PowerPLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PPKPOWERBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.PowerPLS) {
			if (Value32 <= (UINT32)MaxLimit.PowerPLS) {
				CurrentPreset.PowerPLS = Value32;
				CurrentPreset.SuspectLimits &= (~PPKPOWERBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(POWERPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Power Reject Limit */
	case SET_MPOWER_RLIMIT:

		ErrorResponseMinLimit = MinLimit.PowerMLR;
		ErrorResponseMaxLimit = MaxLimit.PowerMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MPKPOWERBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.PowerMLR) {
			if (Value32 <= (UINT32)MaxLimit.PowerMLR) {
				CurrentPreset.PowerMLR = Value32;
				CurrentPreset.RejectLimits &= (~MPKPOWERBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(POWERMLR, 0, 0); /* Save to Fram */
		break;

		/* Set +Power Reject Limit */
	case SET_PPOWER_RLIMIT:

		ErrorResponseMinLimit = MinLimit.PowerPLR;
		ErrorResponseMaxLimit = MaxLimit.PowerPLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PPKPOWERBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.PowerPLR) {
			if (Value32 <= (UINT32)MaxLimit.PowerPLR) {
				CurrentPreset.PowerPLR = Value32;
				CurrentPreset.RejectLimits &= (~PPKPOWERBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(POWERPLR, 0, 0); /* Save to Fram */
		break;

		/* Set -Collapse Suspect Limit */
	case SET_MCOLLAPSE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.ColMLS;
		ErrorResponseMaxLimit = MaxLimit.ColMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MCOLDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.ColMLS) {
			if (Value32 <= (UINT32)MaxLimit.ColMLS) {
				CurrentPreset.ColMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MCOLDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(COLMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Collapse Suspect Limit */
	case SET_PCOLLAPSE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.ColPLS;
		ErrorResponseMaxLimit = MaxLimit.ColPLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PCOLDISTBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.ColPLS) {
			if (Value32 <= (UINT32)MaxLimit.ColPLS) {
				CurrentPreset.ColPLS = Value32;
				CurrentPreset.SuspectLimits &= (~PCOLDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(COLPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Collapse Reject Limit */
	case SET_MCOLLAPSE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.ColMLR;
		ErrorResponseMaxLimit = MaxLimit.ColMLR;

		if (!Value32)
			/* a value of 0 disaables the limit */
			CurrentPreset.RejectLimits |= MCOLDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.ColMLR) {
			if (Value32 <= (UINT32)MaxLimit.ColMLR) {
				CurrentPreset.ColMLR = Value32;
				CurrentPreset.RejectLimits &= (~MCOLDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(COLMLR, 0, 0); /* Save to Fram */
		break;

		/* Set +Collapse Reject Limit */
	case SET_PCOLLAPSE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.ColPLR;
		ErrorResponseMaxLimit = MaxLimit.ColPLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PCOLDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.ColPLR) {
			if (Value32 <= (UINT32)MaxLimit.ColPLR) {
				CurrentPreset.ColPLR = Value32;
				CurrentPreset.RejectLimits &= (~PCOLDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(COLPLR, 0, 0); /* Save to Fram */
		break;

		/* Set -Absolute Suspect Limit */
	case SET_MABSOLUTE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.AbsMLS;
		ErrorResponseMaxLimit = MaxLimit.AbsMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MABSDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.AbsMLS) {
			if (Value32 <= (UINT32)MaxLimit.AbsMLS) {
				CurrentPreset.AbsMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MABSDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ABSMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Absolute Suspect Limit */
	case SET_PABSOLUTE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.AbsPLS;
		ErrorResponseMaxLimit = MaxLimit.AbsPLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PABSDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.AbsPLS) {
			if (Value32 <= (UINT32)MaxLimit.AbsPLS) {
				CurrentPreset.AbsPLS = Value32;
				CurrentPreset.SuspectLimits &= (~PABSDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ABSPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Absolute Reject Limit */
	case SET_MABSOLUTE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.AbsMLR;
		ErrorResponseMaxLimit = MaxLimit.AbsMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MABSDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.AbsMLR) {
			if (Value32 <= (UINT32)MaxLimit.AbsMLR) {
				CurrentPreset.AbsMLR = Value32;
				CurrentPreset.RejectLimits &= (~MABSDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ABSMLR, 0, 0); /* Save to Fram */

		break;

		/* Set +Absolute Reject Limit */
	case SET_PABSOLUTE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.AbsPLR;
		ErrorResponseMaxLimit = MaxLimit.AbsPLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PABSDISTBIT;/* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.AbsPLR) {
			if (Value32 <= (UINT32)MaxLimit.AbsPLR) {
				CurrentPreset.AbsPLR = Value32;
				CurrentPreset.RejectLimits &= (~PABSDISTBIT);/* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ABSPLR, 0, 0); /* Save to Fram */
		break;

		/* Set -Trigger Distance Suspect Limit */
	case SET_MTRIGDIST_SLIMIT:

		ErrorResponseMinLimit = MinLimit.TrsDistMLS;
		ErrorResponseMaxLimit = MaxLimit.TrsDistMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MTRIGDISTBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.TrsDistMLS) {
			if (Value32 <= (UINT32)MaxLimit.TrsDistMLS) {
				CurrentPreset.TrsDistMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MTRIGDISTBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(TRSDISTMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Trigger Distance Suspect Limit */
	case SET_PTRIGDIST_SLIMIT:

		ErrorResponseMinLimit = MinLimit.TrsDistPLS;
		ErrorResponseMaxLimit = MaxLimit.TrsDistPLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PTRIGDISTBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.TrsDistPLS) {
			if (Value32 <= (UINT32)MaxLimit.TrsDistPLS) {
				CurrentPreset.TrsDistPLS = Value32;
				CurrentPreset.SuspectLimits &= (~PTRIGDISTBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(TRSDISTPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Trigger Distance Reject Limit */
	case SET_MTRIGDIST_RLIMIT:

		ErrorResponseMinLimit = MinLimit.TrsDistMLR;
		ErrorResponseMaxLimit = MaxLimit.TrsDistMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MTRIGDISTBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.TrsDistMLR) {
			if (Value32 <= (UINT32)MaxLimit.TrsDistMLR) {
				CurrentPreset.TrsDistMLR = Value32;
				CurrentPreset.RejectLimits &= (~MTRIGDISTBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(TRSDISTMLR, 0, 0); /* Save to Fram */
		break;

		/* Set +Trigger Distance Reject Limit */
	case SET_PTRIGDIST_RLIMIT:

		ErrorResponseMinLimit = MinLimit.TrsDistPLR;
		ErrorResponseMaxLimit = MaxLimit.TrsDistPLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PTRIGDISTBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.TrsDistPLR) {
			if (Value32 <= (UINT32)MaxLimit.TrsDistPLR) {
				CurrentPreset.TrsDistPLR = Value32;
				CurrentPreset.RejectLimits &= (~PTRIGDISTBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(TRSDISTPLR, 0, 0); /* Save to Fram */
		break;

		/* Set -Weld Force Suspect Limit */
	case SET_MMAXFORCE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.WeldForceMLS;
		ErrorResponseMaxLimit = MaxLimit.WeldForceMLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= MFORCEBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.WeldForceMLS) {
			if (Value32 <= (UINT32)MaxLimit.WeldForceMLS) {
				CurrentPreset.WeldForceMLS = Value32;
				CurrentPreset.SuspectLimits &= (~MFORCEBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(MAXFORCEMLS, 0, 0); /* Save to Fram */
		break;

		/* Set +Weld Force Suspect Limit */
	case SET_PMAXFORCE_SLIMIT:

		ErrorResponseMinLimit = MinLimit.WeldForcePLS;
		ErrorResponseMaxLimit = MaxLimit.WeldForcePLS;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.SuspectLimits |= PFORCEBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.WeldForcePLS) {
			if (Value32 <= (UINT32)MaxLimit.WeldForcePLS) {
				CurrentPreset.WeldForcePLS = Value32;
				CurrentPreset.SuspectLimits &= (~PFORCEBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(MAXFORCEPLS, 0, 0); /* Save to Fram */
		break;

		/* Set -Weld Force Reject Limit */
	case SET_MMAXFORCE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.WeldForceMLR;
		ErrorResponseMaxLimit = MaxLimit.WeldForceMLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= MFORCEBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.WeldForceMLR) {
			if (Value32 <= (UINT32)MaxLimit.WeldForceMLR) {
				CurrentPreset.WeldForceMLR = Value32;
				CurrentPreset.RejectLimits &= (~MFORCEBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(MAXFORCEMLR, 0, 0); /* Save to Fram */
		break;

		/* Set +Weld Force Reject Limit */
	case SET_PMAXFORCE_RLIMIT:

		ErrorResponseMinLimit = MinLimit.WeldForcePLR;
		ErrorResponseMaxLimit = MaxLimit.WeldForcePLR;

		if (!Value32)
			/* a value of 0 disables the limit */
			CurrentPreset.RejectLimits |= PFORCEBIT; /* Turn Flag Off */

		else if (Value32 >= (UINT32)MinLimit.WeldForcePLR) {
			if (Value32 <= (UINT32)MaxLimit.WeldForcePLR) {
				CurrentPreset.WeldForcePLR = Value32;
				CurrentPreset.RejectLimits &= (~PFORCEBIT); /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(MAXFORCEPLR, 0, 0); /* Save to Fram */
		break;

		/* Set Actuator Clear */
	case SET_ACTUATOR_CLEAR:

		ErrorResponseMinLimit = MinLimit.ActClrDistance;
		ErrorResponseMaxLimit = MaxLimit.ActClrDistance;

		if (!Value32)
			/* a value of 0 disables the function */
			CurrentPreset.ActClrFlag = FALSE;

		else if (Value32 >= (UINT32)MinLimit.ActClrDistance) {
			if (Value32 <= (UINT32)MaxLimit.ActClrDistance) {
				CurrentPreset.ActClrDistance = Value32;
				CurrentPreset.ActClrFlag = TRUE; /* Turn Flag On */
			} else
				NackError = MAX_ERROR;
		} else
			NackError = MIN_ERROR;

		if (!NackError)
			UpdateCurrentPreset(ACTCLEARDIST, 0, 0); /* Save to Fram */
		break;

	case CHECKSUM_ERROR: /* Bad data received */
		NackError = BAD_CHECKSUM;
		break;

		/* SPECIAL BRANSON COMMANDS */

	case ONBOARD_DIAGNOSTICS: /* Special host command to start */
		OnboardDiag = TRUE; /* diagnostics through the serial port */
		break;

	case SET_PS_SERIALNUMBER:
		/* Point to serial number */
		Host8 = (UINT8 *) DataPointer;
		/* Test serial number for printable ascii */
		for (i = 0; i < SERIALLENGTH; i++) {
			if (Host8[i] < ' ') {
				NackError = PARAMETER_ERROR;
				break;
			}
		}

		if (!NackError) {
			/* Copy serial number */
			for (i = 0; i < SERIALLENGTH; i++)
				CurrentSetup.PSSerialNumber[i] = Host8[i];
			StorePSSerialNumber();
			GetSerialNumbers();
			SystemParameterChgdFlag = TRUE;
		}
		break;

	case SET_PS_MODELNUMBER:
		/* Load authorization code */
		Host8 = (UINT8 *) DataPointer;
		Value16 = (Host8[3] << 8) + Host8[4];
		if (Value16 != ComputeAuthorization())
			NackError = INVALID_AUTH_CODE;
		else {
			if (DUPS_Info.DUPSFlag != TRUE) {
				Host16 = (UINT16 *) DataPointer;
				Value16 = *Host16;
				Value8 = Host8[2];
				/* use switch to check for legal power supply wattage values */
				switch (Value16) {
				case 200: /*  200W */
				case 400: /*  400W */
				case 800: /*  800W */
				case 1100: /* 1100W */
				case 1500: /* 1500W */
				case 2200: /* 2200W */
				case 3300: /* 3300W */
				case 4000: /* 4000W */
				case 6000: /* 6000W */
					break;
				default:
					NackError = PARAMETER_ERROR;
					break;
				}

				/* test for legal frequency designator */
				switch (Value8) {
				case FREQ15KHZ:
				case FREQ20KHZ:
				case FREQ30KHZ:
				case FREQ40KHZ:
				case FREQ50KHZ:
				case FREQ60KHZ:
					break;
				default:
					NackError = PARAMETER_ERROR;
					break;
				}

				if (!NackError) {
					CurrentSetup.PSWatt = Value16;
					CurrentSetup.PSFreq = Value8;
					StorePSWattage();
					StorePSFrequency();
					GetPowerSupplyInfo();
				}
			} else
				NackError = PARAMETER_ERROR;
		}
		break;

	case SET_CONTROLLEVEL:
		Host16 = (UINT16 *) DataPointer;
		Host16++; /* point to authorization code */
		Value16 = *Host16;
		if (Value16 == ComputeAuthorization()) {
			/* Test for valid control level value */
			Host16--; /* point to control level */
			Value16 = *Host16;
			switch (Value16) {
			case LEVEL_t:
			case LEVEL_e:
			case LEVEL_a:
			case LEVEL_ea:
			case LEVEL_d:
			case LEVEL_c:
			case LEVEL_f:
			case LEVEL_TEST:
				DepotFlag->IsADepot = FALSE;
				CurrentSetup.ControlLevel = Value16;
				break;
			case LEVEL_DEPOT:
				DepotFlag->WasADepot = TRUE;
				DepotFlag->IsADepot = TRUE;
				CurrentSetup.ControlLevel = LEVEL_t;
				break;

			default:
				NackError = PARAMETER_ERROR;
				break;
			}
		} else
			NackError = INVALID_AUTH_CODE;

		if (!NackError) {
			StorePSControlLevel();
			ColdStartPlus();
			GetControlLevel();
			SystemParameterChgdFlag = TRUE;
		}
		break;

	case SET_ACT_SERIALNUMBER:
		Host8 = (UINT8 *) DataPointer;
		Count = strlen((SINT8 *) Host8);
		if (Count < MAXSERIALNUM) {
			strcpy(CurrentSetup.ActSerialNumber, (SINT8 *) Host8);
			SaveActSerialNum();
		} else
			NackError = PARAMETER_ERROR;
		break;

	case SET_ACT_MODELNUMBER:
		/* Load authorization code */
		Host8 = (UINT8 *) DataPointer;
		Value16 = (Host8[1] << 8) + Host8[2];
		if (Value16 != ComputeAuthorization())
			NackError = INVALID_AUTH_CODE;
		else {
			Value8 = *Host8;
			switch (Value8) {
            case NVR_AE:
                  CurrentSetup.Actuator = AE; // ae
               break;
			case NVR_AED:
				CurrentSetup.Actuator = AED; // aed
				break;
			case NVR_AES:
				CurrentSetup.Actuator = AES; // aes
				break;
			case NVR_MICRO:
				CurrentSetup.Actuator = MICRO; // MICRO
				break;
			case NVR_MICROC:
				CurrentSetup.Actuator = MICROC; // MICROC ID for sunrise micro c actuator
				break;
			default:
				NackError = PARAMETER_ERROR;
				break;
			}
			if (!NackError) {
				SetActId((UINT16) Value8); // Should be a num between 1 to 6
				SystemParameterChgdFlag = TRUE;
			}
		}
		break;

	case RESET_PSLIFETIMECOUNTER:
		CurrentSetup.PSLifetime = 0;
		StorePSLifeTimeCount();
		break;

	case RESET_OVERLOADCOUNTER:
		CurrentSetup.Overload = 0;
		break;

	case RESET_GENALARMCOUNTER:
		CurrentSetup.GenAlarmCount = 0;
		break;

	case SET_ACTUATOR_CYLINDERDIAMETER:
		/* Load authorization code */
		Host8 = (UINT8 *) DataPointer;
		Value16 = (Host8[2] << 8) + Host8[3];
		if (Value16 != ComputeAuthorization())
			NackError = INVALID_AUTH_CODE;
		else {
			Host16 = (UINT16 *) DataPointer;
			Value16 = *Host16;
			/* use switch to check for legal values */
			switch (Value16) {
			case CUSTOMSIZE:
			case SIZE1_5:
			case SIZE2_0:
			case SIZE2_5:
			case SIZE3_0:
			case SIZE3_25:
			case SIZE_32:
			case SIZE_40:
			case SIZE_50:
			case SIZE_63:
			case SIZE_80:
				CurrentSetup.CylinDiameter = Value16;
				SetCylinderIndex();
				break;

			default:
				NackError = PARAMETER_ERROR;
				break;
			}
		}
		break;

	case SET_ACTUATOR_STROKELENGTH:
		/* Load authorization code */
		Host8 = (UINT8 *) DataPointer;
		Value16 = (Host8[2] << 8) + Host8[3];
		if (Value16 != ComputeAuthorization())
			NackError = INVALID_AUTH_CODE;
		else {
			Host16 = (UINT16 *) DataPointer;
			Value16 = *Host16;
			/* use switch to check for legal values */
			switch (Value16) {
			case CUSTOMLEN:
			case LENGTH_4:
			case LENGTH_5:
			case LENGTH_6:
			case LENGTH_2:
			case LENGTH_8:
			case LENGTH_70:
			case LENGTH_75:
			case LENGTH_80:
			case LENGTH_100:
			case LENGTH_125:
			case LENGTH_50:
				CurrentSetup.StrokeLen = Value16;
				SetStrokeLenIndex();
				break;

			default:
				NackError = PARAMETER_ERROR;
				break;
			}
		}
		break;

	case UPLOAD_REMOTE_CONFIG_PARMS:

		for (i = 0; i < 15; i++)
			AckBuf[i] = 0;
		AckBuf[0] = ACK;
		AckBuf[1] = DLE;
		AckBuf[2] = STX;
		/* fill in count */
		AckBuf[3] = 0;
		AckBuf[4] = 25;
		/* fill in function */
		AckBuf[5] = (UINT8) (Function >> 8);
		AckBuf[6] = (UINT8) Function;
		/* fill in PS serial number */
        TempVar = strlen(CurrentSetup.PSSerialNumber);
        for (i = 7; (i < (SERIALLENGTH + 7)); i++)
        {
        	if(i < (TempVar + 7))
        		AckBuf[i] = CurrentSetup.PSSerialNumber[i - 7];
            else
                AckBuf[i] = 0;
        }

		/* fill in SWVersion Number */
		for (i = 19; i < 24; i++)
			AckBuf[i] = 0;
		/* fill in control level */
		AckBuf[24] = 0;
		if (DepotFlag->IsADepot)
			AckBuf[25] = (UINT8) LEVEL_DEPOT;
		else
			AckBuf[25] = (UINT8) CurrentSetup.ControlLevel;
		/* fill in Weld Data Flag */
		AckBuf[26] = 0;
		AckBuf[27] = (UINT8) CurrentSetup.SerialPort;
		/* fill in checksum */
		AckBuf[28] = 0;
		for (i = 3; i < 28; i++)
			AckBuf[28] ^= AckBuf[i];
		AckBuf[29] = DLE;
		AckBuf[30] = ETX;
		i = UPLOAD_REMOTE_CONFIG_PARMS_SIZE;
		NoAckOrNak = TRUE;

		break; /* continue while forever */

	default:
		/* unknown opcode */
		NackError = INVALID_OPCODE;
		break;
	} /* opcode switch */

	if (NoAckOrNak == FALSE) {
		if (NackError) {
			/* Generate NACK error response */
			i = XmitNack((IPS_ACTION_ID_TYPE) Function,
					(EDIT_PARAM_TYPE) SubFunction, NackError,
					ErrorResponseMinLimit, ErrorResponseMaxLimit, AckBuf);
		} else {
			SendFakeKeyPress(UPDATEDISPLAY);
			AckBuf[0] = ACK;
			AckBuf[1] = DLE;
			AckBuf[2] = STX;
			/* fill in count */
			AckBuf[3] = 0;
			AckBuf[4] = 5;
			/* fill in function */
			AckBuf[5] = (UINT8) (Function >> 8);
			AckBuf[6] = (UINT8) Function;
			/* fill in DisplayLock */
			AckBuf[7] = (UINT8) Inp.DisplayLockFlag;
			/* fill in checksum */
			AckBuf[8] = 0;
			for (i = 3; i < 8; i++)
				AckBuf[8] ^= AckBuf[i];
			AckBuf[9] = DLE;
			AckBuf[10] = ETX;
			i = ACK_REPLY_SIZE;
		}
	}

	return i;
}

UINT16 ProcessVGAHostCommand(UINT32 Value32, UINT16 Function,
		UINT8 *DataPointer, UINT16 CommandCount)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds reply for VGA hostcommand and writes data in buffer */
/*Input Parameters:-                                                        */
/* Value32: First four data bytes are mostly pointer value                  */
/* Function: Host command Function number                                   */
/* Datapointer: Pointer to the host command data                            */
/* CommandCount: Nos of data bytes in a command                             */
/*Returns length of the bytes written to the buffer                         */
/****************************************************************************/

{
	FP_KEY_PRESSED_MSG FpkpQueue;
	UINT8 accept_reject = 0xff;
	UINT16 Position;
	UINT16 i, j;
	UINT16 NoAckOrNak = FALSE;
	UINT16 Value16;
	SINT32 VarValue;
	UINT8 *Host8;
	UINT8 * SendMenuResponse = VGAMenuResponseBuff;
	UINT8 *TempPtr;
	UINT16 len;
	UINT16 SubFunction;
	UINT16 StructID;
	UINT8 TempMenuNxtPointer;
	Ver1200Setups * TempPresetPtr;//used to read the revision of preset slot being overwritten.
	int Offset = 0;
	unsigned long ip_addr;
	unsigned long mask_addr;
	unsigned long gateway_addr;
	UINT8 GetNetworkInfo = 0;
	UINT8 GetAuthorityCrt = 0;
	union {
		struct {
			unsigned long a1;
			unsigned long a2;
			unsigned long a3;
		} s;
		char c[12];
	} u;
	static SINT32 PresentCount = 0;
	UINT16 GetSetVal = 0;
	i = 0;
	unsigned char cc = 0;
	GlobalFunctionCode = Function;
	SubFunction = 0;

	switch (Function) {

	case SEND_MENU_PTRS: // Send Bottom button pointers and Initial Info
		if (CommandCount == MENU_PTRS_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			for (i = 0; i < SBC_SW_VERSION_LENTGH; i++) {
				SBCVersionLabel[i] = Host8[i];
			}
			SBCVersionLabel[i] = '\0';
			len = SendMenuPtrs(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case START_RUNCYCLE: // Start state machine
		if (CommandCount == START_RUNCYCLE_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if (*Host8 == STATE_MACH_ON) {
				SBCReadyFlag = TRUE;
				if (WindowSetupFlag) {
					WindowSetupFlag = FALSE;
					ReadyFlag = VGA_ReadyFlag;
					ResetStateMachine();
					StartStateMachine();
					SetReady();
				} else {
					StartStateMachine();
					ReadyFlag = VGA_ReadyFlag;
					if (ReadyFlag == TRUE)
						SetReady();
				}
			} else if (*Host8 == STATE_MACH_OFF) {
				SBCReadyFlag = FALSE;
				VGA_ReadyFlag = ReadyFlag;
				StopStateMachine(); /* Stop the State machine*/
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_CONDN_VAR: //Send condition Variable
		if (CommandCount == SEND_CONDN_VAR_SIZE) {
			len = SendConditionVariable(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_STRUCTURE_DATA:
		if (CommandCount == SEND_STRUCTURE_DATA_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			StructID = ((UINT16) (*Host8) << 8) + (UINT16) (*(Host8 + 1));
			TempMenuNxtPointer = (UINT8) (*(Host8 + 2));
			for (Position = 0; Map[Position].Struct_ID != -1; Position++) {
				if (Map[Position].Struct_ID == StructID) {
					break;
				}
			}
			if (Map[Position].Struct_ID == -1) {
				NackError = ILLEGAL_COMMAND;
			} else {
				if (StructID == MENU_SYNC) /*Menu Sync in Calibration*/
					MenuNxtPointer = TempMenuNxtPointer;
				GlobalCommandID = StructID;
				len = XMLDataProcess(SendMenuResponse, Position, StructID);
			}
			if (!NackError) {
				i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
				NoAckOrNak = TRUE;
			}
		} else {
			NackError = ILLEGAL_COMMAND;
		}
		break;

	case RECEIVE_STRUCTURE_DATA:
		if (CommandCount <= RECEIVE_STRUCTURE_DATA_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			StructID = ((UINT16) (*Host8) << 8) + (UINT16) (*(Host8 + 1));
			len = 0;
			for (Position = 0; Map[Position].Struct_ID != -1; Position++) {
				if (Map[Position].Struct_ID == StructID) {
					break;
				}
			}
			if (Map[Position].Struct_ID == -1) {
				NackError = ILLEGAL_COMMAND;
			} else {
				GlobalCommandID = StructID;
				len += XMLDataResponse(Position, &Host8[2], SendMenuResponse,
						StructID);

			}
			if (!NackError) {
				i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
				NoAckOrNak = TRUE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_MIN_MAX_COMMAND:
		if (CommandCount == SEND_MIN_MAX_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			StructID = ((UINT16) (*Host8) << 8) + (UINT16) (*(Host8 + 1));
			for (Position = 0; MinMap[Position].Struct_ID != -1; Position++) {
				if (MinMap[Position].Struct_ID == StructID)
					break;
			}
			if (MinMap[Position].Struct_ID == -1) {
				NackError = ILLEGAL_COMMAND;
			} else {
				GlobalCommandID = StructID;
				if (MinMap[Position].Function1 != NULL)
						MinMap[Position].Function1(StructID);

				if(!NackError)
					len = SendMinMaxData(SendMenuResponse, Position);
			}
			if (!NackError) {
				i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
				NoAckOrNak = TRUE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case BOTTOMHALF_COMMAND:
		if (CommandCount == BOTTOMHALF_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			StructID = ((UINT16) (*Host8) << 8) + (UINT16) (*(Host8 + 1));
			for (Position = 0; Map[Position].Struct_ID != -1; Position++)
				if (Map[Position].Struct_ID == StructID)
					break;
			if (Map[Position].Struct_ID != -1) {
				len = SendBottomHalfData(SendMenuResponse, StructID);
				if (!NackError) {
					i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
					NoAckOrNak = TRUE;
				}
			} else {
				NackError = ILLEGAL_COMMAND;
			}
		} else {
			NackError = ILLEGAL_COMMAND;
		}
		break;

	case WELD_DATA_COMMAND:
		// Send Weld data and graph data command
		if (CommandCount == WELD_DATA_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if ((Host8[0] == WELD_HISTORY) && (Host8[1] == WELD_HISTORY_COUNT) &&
					(WeldState > READYSTATE)) {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
				ErrorResponseMaxLimit = 0;
			} else {
				len = ProcessWeldGraphValue(Host8[0], Host8[1]);
				if (!NackError) {
					i = CreateSameBufferACK(VGAAckBuf, Function, len);
					NoAckOrNak = TRUE;
				} else
					NackError = ILLEGAL_COMMAND;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case VGA_POLLING_COMMAND:
		if (CommandCount == POLLING_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if ((Host8[0] & VGA_SCREENCALIB) && !(VGA_ScreenCalibFlag)) {
				VGA_ScreenCalibFlag = TRUE;
				VGA_ReadyFlag = ReadyFlag;
				ReadyFlag = FALSE;
				ResetStateMachine();
				ClearReady();
			} else if (!(Host8[0] & VGA_SCREENCALIB) && (VGA_ScreenCalibFlag)) {
				VGA_ScreenCalibFlag = FALSE;
				ReadyFlag = VGA_ReadyFlag;
				ResetStateMachine();
				StartStateMachine();
				SetReady();
			}
			if (Host8[0] & VGA_USBFULLALARM)
				VGAUSBFullStatus = TRUE;
			else
				VGAUSBFullStatus = FALSE;
			if ((Host8[0] & VGA_SCREENUSERDIAG)
					&& (VGA_ScreenDiagFlag == FALSE)) {
				VGA_ScreenDiagFlag = TRUE;
				VGA_ReadyFlag = ReadyFlag;
				ReadyFlag = FALSE;
				ResetStateMachine();
				ClearReady();
				SaveUserIOState();
				ClearGeneralAlarm();
			} else if (!(Host8[0] & VGA_SCREENUSERDIAG) && (VGA_ScreenDiagFlag
					== TRUE)) {
				VGA_ScreenDiagFlag = FALSE;
				ReadyFlag = VGA_ReadyFlag;
				SetGeneralAlarm();
				RestoreUserIOState();
				ResetStateMachine();
				StartStateMachine();
				SetReady();
			}

			len = VGASendPollingData(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case PROCESS_ALARM_ITEM:
		// Process Alarm Item
		if (CommandCount == PROCESS_ALARM_ITEM_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			StructID = ((UINT16) (*Host8) << 8) + (UINT16) (*(Host8 + 1));
			ProcessAlarmItems(StructID);
			len = 0;
			if (!NackError) {
				i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
				NoAckOrNak = TRUE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_ALARMBIT_COMMAND:
		// Send alarm bit  status
		if (CommandCount == SEND_ALARMBIT_COMMAND_SIZE) {
			VGAAlarmReset(1);
			len = SendAlarmBits(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_WELDER_STATE_CMD: // Send Weld State
		if (CommandCount == SEND_WELDER_STATE_COMMAND_SIZE) {
			len = SendWeldState(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_START_WELD_DATA: // Send Weld Start Data
		if (CommandCount == SEND_START_WELD_DATA_COMMAND_SIZE) {
			i = ConvertWeldData(&FinalResults, VGAAckBuf);
			LimitChanged = FALSE;
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_SETUPPRINT_DATA: // Send Weld Start Data
		if (CommandCount == SEND_SETUPPRINT_DATA_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if (((Host8[0] >= 1) && (Host8[0] <= 5)) || (Host8[0] == 11))
				PrintLineHeight = 13;
			switch (Host8[0]) {
			case 1:
				len = SystemPresetReport1(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 2:
				len = SystemPresetReport2(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 3:
				len = SystemPresetReport3(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 4:
				len = SystemPresetReport4(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 5:
				len = DupsPresetReport1(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 6:
				len = DupsPresetReport2(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 7:
				len = VGAWeldDataInfo(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 8:
				len = VGAPrintGraphInfo(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 10:
				len = PrintSeqPresetInfo(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;

			case 11:
				len = SystemPresetReport5(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
				break;
			}
			PrintLineHeight = 23;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case SEND_PRINT_PARAM: // Send Print Parameters
		if (CommandCount == SEND_PRINT_PARAM_COMMAND_SIZE) {
			len = VGAPrintParameters(SendMenuResponse);
			i = CreateACK(VGAAckBuf, Function, SendMenuResponse, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case VGADOWNLOAD_PRESET: /* Copy the data to HostPreset structure.*/
		if ((CommandCount == DOWNLOADCOMMAND_SIZE + PRESETNUMBER_SIZE)) {
			Host8 = (UINT8 *) DataPointer;
			Value16 = *((UINT8*) (Host8));
			Value16 = Value16 << 8;
			Value16 |= *((UINT8*) (Host8 + 1));
			if (Value16 <= MAX_POSSIBLE_PRESET) {
				Host8 += 2;
				if ((CurrentSetup.AuthorityCheck == FALSE)
						|| (CurrentUser.UserLevel > TECHNICIAN)) {

				   TempPresetPtr = Readpreset(Value16);
               //Increment revision vefore saving to some slot from usb
               ((SETUPS_Ver1200*) (Host8))->Rev = TempPresetPtr->Rev + 1;
					SavePreset(Value16, (SETUPS_Ver1200*) (Host8));
					CopyInfoFromPreset((SETUPS_Ver1200*) (Host8), Value16);
					GetPresetNames(Value16);
				} else {
					/* Technician Cannot Overwrite a Locked Preset*/
					if ((PresetEnableFlags[Value16] == TRUE)
							&& (FRAMPresetInfo[Value16].Locked == TRUE)
							&& (CurrentSetup.SecurityLevel < SUPERVISOR)) {
						NackError = WELDER_PROCESS_ERROR;
						ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
						ErrorResponseMaxLimit = 0;
					} else {
					   TempPresetPtr = Readpreset(Value16);
					   //Increment revision before saving to some slot from usb
					   ((SETUPS_Ver1200*) (Host8))->Rev = TempPresetPtr->Rev + 1;
						SavePreset(Value16, (SETUPS_Ver1200*) (Host8));
						CopyInfoFromPreset((SETUPS_Ver1200*) (Host8), Value16);
						GetPresetNames(Value16);
					}
				}

			} else {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
				ErrorResponseMaxLimit = 0;
			}

		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case VGAUPLOAD_PRESET:
		if (CommandCount == UPLOADCOMMAND_SIZE + PRESETNUMBER_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			Value16 = *((UINT8*) (Host8));
			Value16 = Value16 << 8;
			Value16 |= *((UINT8*) (Host8 + 1));
			Host8 += 2;
			if (Value16 <= MAX_POSSIBLE_PRESET) {
				if (NackError != WELDER_PROCESS_ERROR) {
					i = 0;
					VGAAckBuf[i++] = ACK;
					VGAAckBuf[i++] = DLE;
					VGAAckBuf[i++] = STX;
					/* Increment index over byte count */
					i += 2;
					/* fill in function */
					VGAAckBuf[i++] = (UINT8) (Function >> 8);
					VGAAckBuf[i++] = (UINT8) Function;
					/* fill in display lock */
					VGAAckBuf[i++] = (UINT8) Inp.DisplayLockFlag;
					TempPtr = (UINT8*) Readpreset(Value16);
					/*Fill the Preset Data*/
					for (j = 0; j < sizeof(SETUPS_Ver1200); j++)
						VGAAckBuf[i++] = *TempPtr++;
					/* fill in byte count */
					VGAAckBuf[3] = (UINT8) ((i - 3) >> 8);
					VGAAckBuf[4] = (UINT8) (i - 3);
					/* compute checksum */
					VGAAckBuf[i] = 0;
					for (j = 3; j < i; j++)
						VGAAckBuf[i] ^= VGAAckBuf[j];
					i++;
					/* add DLE, ETX to message */
					VGAAckBuf[i++] = DLE;
					VGAAckBuf[i++] = ETX;
					NoAckOrNak = TRUE;
				}
			} else {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
				ErrorResponseMaxLimit = 0;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case PMC_COMMAND: // Process PMC feature related commands
		if (CommandCount == PMC_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if (Host8[0] == SENDPMCDATA) {
				len = SendPMCValue(&VGAAckBuf[8]); //Send PMC graph data
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
			} else
				NackError = ILLEGAL_COMMAND;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case VGA_ERRORBEEP_COMMAND: // Produce Error beep
		if (CommandCount == VGA_ERRORBEEP_COMMAND_SIZE)
			Beep(ERRORBEEP);
		else
			NackError = ILLEGAL_COMMAND;
		break;

	case GENERATEALARM_COMMAND:
		if (CommandCount == GENERATEALARM_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			if (Host8[0] & BIT0) {
				VGAHistoryValidatedFlag = TRUE;
				RecordSetupAlarm(SE302);
			}

			if (Host8[0] & BIT1) {
				VGAUSBOfflineFlag = TRUE;
				RecordAlarm(EQ27);
			}
			if (Host8[0] & BIT2) {
				VGAUSBFullFlag = TRUE;
				RecordAlarm(EQ13);
			}

			if (Host8[0] & BIT3) {
				VGADISKFullFlag = TRUE;
				RecordAlarm(EQ16);
			}
			if (Host8[0] & BIT4)
				RecordAlarm(W12);

			if (Host8[0] & BIT5)
				RecordAlarm(W13);
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case PSPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
		if (CommandCount == PSPRESET_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			Host8++;
			Value16 = *((UINT8*) (Host8));
			Value16 = Value16 << 8;
			Value16 |= *((UINT8*) (Host8 + 1));
			Host8 += 2;
			if (CheckForDups()) {
				ViewDupsPresent = TRUE;
			}
			if (NackError != WELDER_PROCESS_ERROR) {
				NackError = ILLEGAL_COMMAND;
				Readpreset(Value16, &CurrentViewPreset);
				PresetCheck = Value16;
				len = SystemViewPresetReport(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				ViewDupsPresent = FALSE;
				NoAckOrNak = TRUE;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case COPY_ALL_PRESET_COMMAND: 	
			if (CommandCount == COPY_ALL_PRESET_COMMAND_SIZE) {
				Host8 = (UINT8 *) DataPointer;			
				Value16 =(UINT16) (Host8[0] << 8 | Host8[1]);				
				len = GetPresetNames_USB(&VGAAckBuf[8],Value16);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				NoAckOrNak = TRUE;
			} else
				NackError = ILLEGAL_COMMAND;
			break;

	case USBPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
		Host8 = (UINT8 *) DataPointer;
		switch (*Host8++) {
		case VIEWPRESETPARTONE:
			if ((CommandCount == DOWNLOADCOMMAND_SIZE + 1) || (CommandCount
					== DOWNLOADDUPS_SIZE + 1) || (CommandCount
					== SEND_SETUPPRINT_DATA_COMMAND_SIZE)) {			
				if (CheckForDups()) {
					ViewDupsPresent = TRUE;
				}
				PresetCheck = 0;
			    memcpy((UINT8 *) &CurrentViewPreset, Host8, sizeof(SETUPS_Ver1200));
				len = SystemViewPresetReport(&VGAAckBuf[8]);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
				ViewDupsPresent = FALSE;
				NoAckOrNak = TRUE;

			} else
				NackError = ILLEGAL_COMMAND;
			break;

		default:
			NackError = ILLEGAL_COMMAND;
			break;
		}
		break;

	case VGA_SCREENSETUP_COMMAND: // Check if entry allowed in screen setup
		if (CommandCount == VGA_SCREENSETUP_COMMAND_SIZE) {
			/* Check for the Ready or Pre-Ready state. */
			if ((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
				ResetStateMachine();
				ClearReady();
			} else {
				Beep(ERRORBEEP);
				NackError = ILLEGAL_COMMAND;
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case VGA_RESET_ALARMS: //for reset alarms
		if (CommandCount == VGA_RESET_ALARMS_SIZE) {
			if ((KeyMask & RESETKEYMASK) == RESETKEYMASK)
			/*Check if Reset key is enabled */
			{
				FpkpQueue.key = ResetKey;
				/*Send the key to FPK_TASK */
				FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
				FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(0, *((FPKP_MSG_QUEUE_TYPE*) &FpkpQueue), 0);
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case GET_NETWORK_INFO:
		//Case to assign ip to WC board
		if (CommandCount == GET_NETWORK_INFO_SIZE) {
			for (i = 0; i < 12; i++)
				u.c[i] = *(DataPointer + i);
			ip_addr = u.s.a1;
			mask_addr = u.s.a2;
			gateway_addr = u.s.a3;
			CyGOS::SetupAddress(ETHERNET_INTERFACE_WCTOSBC, ip_addr - WC_TO_SBC_OFFSET, mask_addr); // to assign IP to Ethernet interface 0.
			CyGOS::SetGW(ETHERNET_INTERFACE_WCTOSBC, gateway_addr);
			GetNetworkInfo = 1;
			i = CreateACK(VGAAckBuf, Function, &GetNetworkInfo, 1);
			NoAckOrNak = TRUE;
		}
		break;
	case SEND_SOFTWARE_VERSION:
		if (CommandCount == SEND_SOFTWARE_VERSION_SIZE) {
			len = strlen(SWVersionLabel);
			i = CreateACK(VGAAckBuf, Function, (UINT8*) SWVersionLabel, len);
			NoAckOrNak = TRUE;
		}
		break;
	case SEND_HORN_CLAMP_STATUS:
		if (CommandCount == SEND_HORN_CLAMP_STATUS_SIZE) {
			GetAuthorityCrt = FRAMUserIdObj.GlobalOpAuth;
			i = CreateACK(VGAAckBuf,Function,&GetAuthorityCrt,sizeof(GetAuthorityCrt));
			NoAckOrNak = TRUE;
		}
		break;
	case USERID_DATA_COMMAND:
		if (CommandCount == USERID_DATA_LEN) {
			Host8 = (UINT8 *) DataPointer;
			PresentCount = *((UINT16*) (Host8 + 2));
			GetSetVal = *((UINT16*) Host8);
			Host8 = (UINT8*) Host8 + 4; //offset of 4 bytes
			if ((PresentCount > FRAMUserIdObj.UserIDGlobalCount) && (PresentCount != 0xFFFF)) // in the range and valid count
			{
				len = ProcessUserIdData(VGAAckBuf, (UINT8*) NULL, 0); //Large Count Value
				CreateSameBufferACK(VGAAckBuf, Function, len); //Send a 0xFFFFFFFF Count
			} else if (GetSetVal == SETUSERDATA) //Receive the data from SBC
			{
				if (PresentCount == 0xFFFF) {
					
					accept_reject=Check_ExistingUserDetails(ADD,0);
					if (accept_reject == ACCEPTED) {

						useridData.IsFirstTimeLogin = FIRST_TIME_LOGIN;
						useridData.UnSuccessFullAttempts = 0;
						memcpy(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount], &useridData,
							sizeof(UserID));
						FRAMUserIdObj.GlobalOpAuth = userOpAuth;
						RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount].CreateModifyTime);
						FRAMUserIdObj.UserIDGlobalCount = FRAMUserIdObj.UserIDGlobalCount + 1;
						if (useridData.Status == Enabled)
							FRAMUserIdObj.ActiveUserIDCount++;
						AddModifyUserEventRecord(ADD, 0);
					}
				} else {
					accept_reject = Check_ExistingUserDetails(MODIFY,
							PresentCount - 1);

					if ((accept_reject == ACCEPTED)) {
						if (FRAMUserIdObj.UserDetail[PresentCount - 1].Status
								!= useridData.Status) {
							if (useridData.Status == Enabled)
								FRAMUserIdObj.ActiveUserIDCount++;
							else
								FRAMUserIdObj.ActiveUserIDCount--;
						}

						AddModifyUserEventRecord(MODIFY, PresentCount - 1);
						if(CurrentUser.UserLevel>=EXECUTIVE){
						   useridData.IsFirstTimeLogin = EXECUTIVE_PASSWORD_CHANGE;
						}
						useridData.UnSuccessFullAttempts = 0;
						memcpy(
								(UINT8*) &FRAMUserIdObj.UserDetail[PresentCount
										- 1], (UINT8*) &useridData,
								sizeof(UserID));
						FRAMUserIdObj.GlobalOpAuth = userOpAuth;
						RTClock::GetCurrentTime(
								&FRAMUserIdObj.UserDetail[PresentCount - 1].CreateModifyTime);
					}
				}
				SetDefaultUserData();
			} else if (GetSetVal == GETUSERDATA) //send the data to SBC
			{
				if (PresentCount == 0xFFFF) {
					SetDefaultUserData();
				} else if (PresentCount <= FRAMUserIdObj.UserIDGlobalCount) //
				{
					memcpy(
							(UINT8*) &useridData,
							(UINT8*) &FRAMUserIdObj.UserDetail[PresentCount - 1],
							sizeof(UserID));
					userOpAuth = FRAMUserIdObj.GlobalOpAuth;
				}
			}
			cc = accept_reject;
			i = CreateACK(VGAAckBuf, Function, &cc, 1);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case EVENTALARM_COMMAND:
		if (CommandCount == EVENTALARM_COMMAND_SIZE) {
			Host8 = (UINT8 *) DataPointer;
			UINT8 EventorAlarm = Host8[0];
			SINT32 DataSentCount = (*((UINT32*) (Host8 + 1)));
			SINT32 LogsCount = (*((UINT32*) (Host8 + 5)));
			if (EventorAlarm) {
				len = ProcessEventHistoryDataCommand(VGAAckBuf, LogsCount,
						DataSentCount);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
			} else {
				len = ProcessAlarmLogDataCommand(VGAAckBuf, LogsCount,
						DataSentCount);
				i = CreateSameBufferACK(VGAAckBuf, Function, len);
			}
			NoAckOrNak = TRUE;
		} else {
			NackError = ILLEGAL_COMMAND;
		}
		break;
	case USERLIST_COMMAND:
		//new implementation
		if (CommandCount == USERLIST_COMMAND_SIZE) {
			RTOS::DelayMs(300);
			Host8 = (UINT8 *) DataPointer;
			PresentCount = (UINT32) Host8[0];
			if (FRAMUserIdObj.UserIDGlobalCount < DATAINONEPACKET
					* PresentCount) //Check for the Data Total packet available
				len = ProcessUserIdData(VGAAckBuf,
						(UINT8*) FRAMUserIdObj.UserDetail,
						(SINT32) (MAXUSERID + 1)); // no more data to send
			else
				len = ProcessUserIdData(VGAAckBuf,
						(UINT8*) FRAMUserIdObj.UserDetail,
						(SINT32) DATAINONEPACKET);
			i = CreateSameBufferACK(VGAAckBuf, Function, len);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case GET_USERID_PASSWORD: //Case to process data of username ,password
	{
		if (CommandCount == GET_USERID_PASSWORD_SIZE) {
			strncpy(CurrUserID, (char*) (DataPointer), sizeof(CurrUserID) - 1);
			strncpy(CurrPassword, (char *) (DataPointer + sizeof(CurrUserID)), sizeof(CurrPassword) - 1);
			UINT8 ids = WRONG_NAME_PASSWORD;
			if(WebService::JsonUserLoggedIn == FALSE)
				ids = VerifyUsernamePassword();
		    else
		    	ids = ALREADY_LOGGED_IN_THROUGH_WEBSERVICES; //Needs better error code
			i = CreateACK(VGAAckBuf, Function, &ids, 1);
			if (ids == CORRECT_NAME_PASSWORD) {
				RecordEvents(EVENT_USERLOGIN, CurrUserID, "");
			}
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
	}
		break;
	case CHANGE_PASSWORD: {
		UINT8 response = 0xff;
		if (CommandCount == CHANGE_PASSWORD_SIZE) {
			Offset = 0;
			strncpy(Assign_UserID, (char*) (DataPointer + Offset),
					sizeof(Assign_UserID) - 1);
			Offset = sizeof(Assign_UserID);
			strncpy(Old_Password, (char*) (DataPointer + Offset),
					sizeof(Old_Password) - 1);
			Offset = Offset + sizeof(Old_Password);
			strncpy(New_Password, (char*) (DataPointer + Offset),
					sizeof(New_Password) - 1);
			Offset = Offset + sizeof(New_Password);
			strncpy(Confirm_Password, (char*) (DataPointer + Offset),
					sizeof(Confirm_Password) - 1);
			response = ChangePassword();
			i = CreateACK(VGAAckBuf, Function, &response, 1);
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
	}
		break;
	case LOGOUT_COMMAND:
		if (CommandCount == LOGOUT_COMMAND_SIZE) {
			UINT8 response = 0xff;
			char * Data1;
			if (CurrentSetup.Automation) {
				Data1 = AutomationUsrId;
			} else {
				Data1 = CurrentUser.UserId;
			}
			RecordEvents(EVENT_USERLOGOUT, Data1, "");

			SBCReadyFlag = FALSE;
			i = CreateACK(VGAAckBuf, Function, &response, 1);
			UserLoggedIn = FALSE;
			FirmwareUploadAllowed = FALSE;
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case WELD_HISTORY_DELETE:
		if (CommandCount == DELETE_WELDHISTORY_SIZE) {
			UINT8 response = 0xff;
			i = CreateACK(VGAAckBuf, Function, &response, 1);
			ClearHistoryInBbram();
			WeldingResults.CycleCount = 0;
			FramVerInfo.PollingCommandCounter = 0;
			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case EVENT_HISTORY_DELETE:
		if (CommandCount == DELETE_EVENTHISTORY_SIZE) {
			UINT8 response = 0xff;
			VarValue = FRAMEventHistoryObj.EventHistoryCount;
			memset((UINT8*) &FRAMEventHistoryObj, 0,
					sizeof(struct FRAMEventHistory));
			PowerUpEventHistoryDataCheck();//set the counters to 0 and -1
			i = CreateACK(VGAAckBuf, Function, &response, 1);

			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case NUMBER_OF_USERS_COMMAND:
		if (CommandCount == NUMBER_OF_USERS_COMMAND_SIZE) {
			UINT8 response[2];
			response[0] = FRAMUserIdObj.UserIDGlobalCount & 0xff;//lsb
			response[1] = (FRAMUserIdObj.UserIDGlobalCount >> 8) & 0xff;
			i = CreateACK(VGAAckBuf, Function, response, 2);

			NoAckOrNak = TRUE;
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	case CHECKSTATEMACHINE:
		if (CommandCount == CHECKSTATEMACHINE_SIZE) {
			if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE)) {
				NackError = WELDER_PROCESS_ERROR;
				ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
				ErrorResponseMaxLimit = 0; // for sending Welding on process
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case UDISCAN_COMMAND:
		if (CommandCount == UDISCAN_COMMAND_SIZE) {
			if (CurrentSetup.BarcodeStart[0] == (*(char*) (DataPointer))) {
				//recall preset
				int presetNum = atoi((const char*) (DataPointer + 1));
				if (presetNum <= MAX_POSSIBLE_PRESET) {
					VGAPresetNum = presetNum;
					ProcessPresetRecall();
				}
			} else {
				if (WeldState == PREREADYSTATE)
					UDIScanRecived = true;
				strncpy(UDIString, (char *) DataPointer, sizeof(UDIString) - 1);
			}
		} else
			NackError = ILLEGAL_COMMAND;
		break;
	case EXIT_USERIO_COMMAND:
		if (CommandCount == EXIT_USERIO_COMMAND_SIZE) {
			if (StateMachineDisabled)
				ExitMenuAndEnableWeld();
		} else
			NackError = ILLEGAL_COMMAND;
		break;

	default:
		/* unknown opcode */
		NackError = INVALID_OPCODE;
		break;
	} /* opcode switch */

	if (NoAckOrNak == FALSE) {
		if (NackError) {
			/* Generate NACK error response */
			i = XmitNack((IPS_ACTION_ID_TYPE) Function,
					(EDIT_PARAM_TYPE) SubFunction, NackError,
					ErrorResponseMinLimit, ErrorResponseMaxLimit, VGAAckBuf);
		} else {
			SendFakeKeyPress(UPDATEDISPLAY);
			VGAAckBuf[0] = ACK;
			VGAAckBuf[1] = DLE;
			VGAAckBuf[2] = STX;
			/* fill in count */
			VGAAckBuf[3] = 0;
			VGAAckBuf[4] = 5;
			/* fill in function */
			VGAAckBuf[5] = (UINT8) (Function >> 8);
			VGAAckBuf[6] = (UINT8) Function;
			/* fill in DisplayLock */
			VGAAckBuf[7] = (UINT8) Inp.DisplayLockFlag;
			/* fill in checksum */
			VGAAckBuf[8] = 0;
			for (i = 3; i < 8; i++)
				VGAAckBuf[8] ^= VGAAckBuf[i];
			VGAAckBuf[9] = DLE;
			VGAAckBuf[10] = ETX;
			i = ACK_REPLY_SIZE;
		}
	}
	Value32 = 0;
	GlobalFunctionCode = 0;
	return i;
}

/* Function assign default value when new user is added
 * the values are auto incremented if global count
 * increases
 */
void SetDefaultUserData() {
	SINT32 id = FRAMUserIdObj.UserIDGlobalCount;
	if( FRAMUserIdObj.UserIDGlobalCount < 0 || FRAMUserIdObj.UserIDGlobalCount > 999 )
		id = 0;

	sprintf(useridData.UserId,"%s%ld","DF",id);
	strcpy(useridData.Password, "123ABC#abc");
	useridData.Status = (ActiveStatus) 1;
	useridData.UserLevel = OPERATOR;
	useridData.PassExpTime = 30; //Set default to maximum
}



UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds ACK command and writes the same to the buffer       */
/****************************************************************************/
{
	UINT16 i, j;
	i = 0;
	AckBuf[i++] = ACK;
	AckBuf[i++] = DLE;
	AckBuf[i++] = STX;
	/* Increment index over byte count */
	i += 2;
	/* fill in function */
	AckBuf[i++] = (UINT8) (Function >> 8);
	AckBuf[i++] = (UINT8) Function;
	AckBuf[i++] = (UINT8) Inp.DisplayLockFlag;
	/* fill in the data */
	if (len > 0) {
		memcpy(&AckBuf[i], response, len);
		i += len;
	}
	/* fill in byte count */
	AckBuf[3] = (UINT8) ((i - 3) >> 8);
	AckBuf[4] = (UINT8) (i - 3);
	/* compute checksum */
	AckBuf[i] = 0;
	for (j = 3; j < i; j++)
		AckBuf[i] ^= AckBuf[j];
	i++;
	/* add DLE, ETX to message */
	AckBuf[i++] = DLE;
	AckBuf[i++] = ETX;
	return i;
}

UINT16 CreateSameBufferACK(UINT8 * AckBuf, UINT16 Function, UINT16 len)
/****************************************************************************/
/*Description:-                                                             */
/* This function builds ACK command and writes the same to the buffer       */
/****************************************************************************/
{
	UINT16 i, j;
	i = 0;
	AckBuf[i++] = ACK;
	AckBuf[i++] = DLE;
	AckBuf[i++] = STX;
	i = i + 2;
	AckBuf[i++] = (UINT8) (Function >> 8);
	AckBuf[i++] = (UINT8) (Function);
	AckBuf[i++] = (UINT8) Inp.DisplayLockFlag;
	i = i + len;
	/* fill in byte count */
	AckBuf[3] = (UINT8) ((i - 3) >> 8);
	AckBuf[4] = (UINT8) (i - 3);
	/* compute checksum */
	AckBuf[i] = 0;
	for (j = 3; j < i; j++)
		AckBuf[i] ^= AckBuf[j];
	i++;
	/* add DLE, ETX to message */
	AckBuf[i++] = DLE;
	AckBuf[i++] = ETX;
	return i;
}

UINT16 XmitNack(IPS_ACTION_ID_TYPE Function, EDIT_PARAM_TYPE Subfunction,
		UINT32 Error, UINT32 Info1, UINT32 Info2, UINT8 *NackBuf) {
	UINT16 i = 0, j;
	NackBuf[i++] = NAK;
	NackBuf[i++] = DLE;
	NackBuf[i++] = STX;
	/* Increment index over byte count */
	i += 2;
	/* fill in function */
	NackBuf[i++] = (UINT8) (Function >> 8);
	NackBuf[i++] = (UINT8) Function;
	/* fill in DisplayLock */
	NackBuf[i++] = (UINT8) Inp.DisplayLockFlag;
	/* fill in Error */
	NackBuf[i++] = (UINT8) (Error >> 24);
	NackBuf[i++] = (UINT8) (Error >> 16);
	NackBuf[i++] = (UINT8) (Error >> 8);
	NackBuf[i++] = (UINT8) Error;
	/* test for Set Current Preset Parameters function */
	if (Function == SET_CURRENT_PRESET_PARAMETERS) {
		/* fill in subfunction */
		NackBuf[i++] = (UINT8) (Subfunction >> 8);
		NackBuf[i++] = (UINT8) Subfunction;
	}
	/* test for Data Follows = 1 */
	if ((Error & 1)) {
		/* fill in informative parameter no. 1 */
		NackBuf[i++] = (UINT8) (Info1 >> 24);
		NackBuf[i++] = (UINT8) (Info1 >> 16);
		NackBuf[i++] = (UINT8) (Info1 >> 8);
		NackBuf[i++] = (UINT8) Info1;
		/* fill in informative parameter no. 2 */
		NackBuf[i++] = (UINT8) (Info2 >> 24);
		NackBuf[i++] = (UINT8) (Info2 >> 16);
		NackBuf[i++] = (UINT8) (Info2 >> 8);
		NackBuf[i++] = (UINT8) Info2;
		if (Function == VERIFY_PRESET) {
			/* fill in param id */
			NackBuf[i++] = (UINT8) (ErrorID >> 24);
			NackBuf[i++] = (UINT8) (ErrorID >> 16);
			NackBuf[i++] = (UINT8) (ErrorID >> 8);
			NackBuf[i++] = (UINT8) (ErrorID);

		}
	}
	/* fill in byte count */
	NackBuf[3] = 0;
	NackBuf[4] = i - 3;
	/* compute checksum */
	NackBuf[i] = 0;
	for (j = 3; j < i; j++)
		NackBuf[i] ^= NackBuf[j];
	i++;
	/* add DLE, ETX to message */
	NackBuf[i++] = DLE;
	NackBuf[i++] = ETX;
	return i;
}

UINT16 ComputeAuthorization(void)
/* Use PS serial number to compute authorization code for RCS commands. */
{
	UINT16 i, Sum = 0;
	for (i = 0; i < SERIALLENGTH; i++)
		Sum += CurrentSetup.PSSerialNumber[i];
	return Sum;
}

void ColdStartPlus(void)
/****************************************************************************/
/*                                                                          */
/* This function sets up the factory defaults. After this function is called*/
/* a long calibration must be run.                                          */
/*                                                                          */
/****************************************************************************/
{
	FixFram();
	SetBucMenuToFactoryDefault();
	if ( (CurrentSetup.Actuator==AED) ||
		       (CurrentSetup.Actuator == AES) ||
			   (CurrentSetup.Actuator == MICROC) ||
		       (CurrentSetup.Actuator == MICRO))
   {
	  SetDefCalSysPressure((SINT16)LOW_PRESSURE);
	  SetDefCalStrokeLength(DEF_CAL_LENGTH);
	  SetDefPressure();
	  SetDefLoadCell();
	  SetDefForce();
	  NvrCopyDeftoNon();   /* copy actuator def novram settings to working novram settings */
	  UpdateNVRSpringRate();
	  SetPSVersionNVR();
	  BuildDefaultSpringRate();
   }
}

UINT16 ConvertWeldData(WELD_DATA *Ver8WeldData, UINT8 *StrSPCData) {

	UINT8 ByteToCopy;
	UINT16 Index = 0, Retval;

	/* Convert WeldData to 7.02 format for Compuweld */
	SPCData.CycleCount = Ver8WeldData->CycleCount;
	memcpy(&SPCData.CycleTime, &Ver8WeldData->CycleTime, sizeof(struct t_time));
	memcpy(&SPCData.CycleDate, &Ver8WeldData->CycleDate, sizeof(struct t_date));
	SPCData.ActualWeldTime = Ver8WeldData->ActualWeldTime;
	SPCData.TotalEnergy = Ver8WeldData->TotalEnergy;
	SPCData.ActualDistance = Ver8WeldData->ActualTotalAbs;
	SPCData.ActualWeldCollapse = Ver8WeldData->ActualWeldCollapse;
	SPCData.ActualTotalCollapse = Ver8WeldData->ActualTotalCollapse;
	SPCData.ActualFreqStart = Ver8WeldData->ActualFreqStart;
	SPCData.ActualFreqEnd = Ver8WeldData->ActualFreqEnd;
	SPCData.FrequencyChange = Ver8WeldData->FrequencyChange;
	SPCData.FrequencyMin = Ver8WeldData->FrequencyMin;
	SPCData.FrequencyMax = Ver8WeldData->FrequencyMax;
	SPCData.ActualDownspeed = Ver8WeldData->ActualDownspeed;
	SPCData.ActualTriggerDistance = Ver8WeldData->ActualTriggerDistance;
	SPCData.RejectBitResult = Ver8WeldData->RejectBitResult;
	SPCData.SuspectBitResult = Ver8WeldData->SuspectBitResult;
	SPCData.NoCycleAlarms = Ver8WeldData->NoCycleAlarms;
	SPCData.OverloadAlarms = Ver8WeldData->OverloadAlarms;
	SPCData.EquipmentFailureAlarms = Ver8WeldData->EquipmentFailureAlarms;
	SPCData.CycleModifiedAlarms = Ver8WeldData->CycleModifiedAlarms;
	SPCData.PresetNum = (UINT8) (Ver8WeldData->PresetNum);
	if (CurrentSetup.Units) {
		if (CurrentSetup.Metric3Flag)
			SPCData.Unit = METRIC3;
		else
			SPCData.Unit = METRIC2;
	} else
		SPCData.Unit = USCS;
	SPCData.Language = (UINT8) (LangIndex);
	SPCData.LimitChangedFlag = LimitChanged;
	SPCData.Warnings = Ver8WeldData->Warnings;
	SPCData.ActualAmplitudeStart = Ver8WeldData->ActualAmplitudeStart;
	SPCData.ActualAmplitudeEnd = Ver8WeldData->ActualAmplitudeEnd;
	SPCData.Weldmode = Ver8WeldData->Weldmode;
	SPCData.PSActControlFlags = Ver8WeldData->PSActControlFlags;
	SPCData.PeakPower = Ver8WeldData->PeakPower;
	SPCData.WeldPressure = Ver8WeldData->WeldPressure;
	SPCData.WeldForceEnd = Ver8WeldData->WeldForceEnd;
	SPCData.HoldForceMax = Ver8WeldData->HoldForceEnd;
	SPCData.TotalCycleTime = Ver8WeldData->CycleTimeResult;
	SPCData.TrigForce = Ver8WeldData->TrigForce;

	SPCDataPtr = (UINT8 *) &SPCData;
	StrSPCData[Index++] = DLE;
	StrSPCData[Index++] = STX;
	StrSPCData[Index++] = 0; // count is 16bits

	if (CurrentSetup.WelderAddrFlag == 0) { /* 0:Welder ID on */
		StrSPCData[Index++] = (UINT8) (sizeof(WELD_DATA7_02) + 4);
		StrSPCData[Index++] = (CurrentSetup.WelderAddrValue & 0x0ff00) >> 8;
		StrSPCData[Index++] = (CurrentSetup.WelderAddrValue & 0x0ff);
		StrSPCData[Index++] = 0; // function number is 16bits
		StrSPCData[Index++] = 26;
		for (ByteToCopy = 0; ByteToCopy < (sizeof(WELD_DATA7_02)); ByteToCopy++) {
			StrSPCData[Index++] = *(SPCDataPtr + ByteToCopy);
		}
		Retval = SPCSIZE + 2; /* Add in for welder ID */
	} else { /* This is compatable with original Compuweld - DON'T CHANGE IT */
		StrSPCData[Index++] = (UINT8) (sizeof(WELD_DATA7_02) + 2);
		StrSPCData[Index++] = 0; // function number is 16bits
		StrSPCData[Index++] = 26;
		for (ByteToCopy = 0; ByteToCopy < (sizeof(WELD_DATA7_02) - 1); ByteToCopy++) {
			StrSPCData[Index++] = *(SPCDataPtr + ByteToCopy);
		}
		Retval = SPCSIZE;
	}

	StrSPCData[Index++] = 0; // chksum
	StrSPCData[Index++] = DLE;
	StrSPCData[Index] = ETX;
	return (Retval);
}

/* Store the MIN_ERROR or MAX_ERROR in ErrorType to send in NAK response */
#define STORE_MIN_ERROR     (*ErrorType = MIN_ERROR)
#define STORE_MAX_ERROR     (*ErrorType = MAX_ERROR)

BOOLEAN CheckForParameterError(UINT16 Value)
/*****************************************************************************/
/*                                                                           */
/* This function checks, whether the passing parameter contain a valid value.*/
/* If not, the function returns TRUE.                                        */
/*                                                                           */
/*****************************************************************************/
{
	BOOLEAN RetVal = FALSE;
	if (CurrentSetup.ControlLevel == LEVEL_f) {
		switch (Value) {
		case RATE_SLOWEST:
		case RATE_SLOW:
		case RATE_NORMAL:
		case RATE_FAST:
		case RATE_FASTEST:
			break;
		default:
			RetVal = TRUE;
			break;
		}
	}
	return (RetVal);
}

UINT16 CreateGraphHeader(UINT16 Type, UINT8 Buffer[])
/*****************************************************************************/
/*                                                                           */
/*  This function will fill in the graph header in the passed buffer.  It    */
/*  will return the number of bytes added to the passed buffer.  The header  */
/*  format is:                                                               */
/*                                                                           */
/*  bytes  description                                                       */
/*  -----  ---------------------------------------------------               */
/*    2    graph type (first passed argument)                                */
/*    4    trigger delay tick mark referenced from trigger point (ms)        */
/*    4    amplitude step tick mark referenced from trigger point (ms)       */
/*    4    force step tick mark referenced from trigger point (ms)           */
/*    4    end of sonics tick mark referenced from trigger point (ms)        */
/*    4    end of hold time tick mark referenced from trigger point (ms)     */
/*    2    number of y values (should be less than or equal to 400)          */
/*    2    x start value (always -0.100 ms before trigger point)             */
/*    2    x step value (ms * 100).  For example 188 = 1.88 ms               */
/*                                                                           */
/*****************************************************************************/
{
	UINT16 Count = 0;
	UINT32 TriggerDelay = 0; /* TEMP for now */
	UINT16 Increment;
	double XStep;
	WELD_DATA LastResults;

	/* Graph type */
	Buffer[Count++] = (UINT8) (Type >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) Type;

	/* Trigger delay tick mark */
	Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE1SHIFT);
	Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE2SHIFT);
	Buffer[Count++] = (UINT8) (TriggerDelay >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) TriggerDelay;

	/* Amplitude step tick mark */
	Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE1SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE2SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->AmpStepAtTime >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) MsPointer->AmpStepAtTime;

	/* Pressure step tick mark */
	Buffer[Count++] = (UINT8) (MsPointer->PressureStepAtTime >> BYTE1SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->PressureStepAtTime >> BYTE2SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->PressureStepAtTime >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) MsPointer->PressureStepAtTime;

	/* End of sonics tick mark */
	GetLastWeldData(&LastResults);
	Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE1SHIFT);
	Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE2SHIFT);
	Buffer[Count++] = (UINT8) (LastResults.ActualWeldTime >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) LastResults.ActualWeldTime;

	/* End of hold time tick mark */
	Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE1SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE2SHIFT);
	Buffer[Count++] = (UINT8) (MsPointer->HoldEndAtTime >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) MsPointer->HoldEndAtTime;

	/* Number of Y values */
	Buffer[Count++] = (UINT8) (WeldDataCount >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) WeldDataCount;

	/* X start value */
	Buffer[Count++] = (SINT8) (-100 >> BYTE3SHIFT);
	Buffer[Count++] = (SINT8) -100;

	/* X step value */
	XStep = (MsPointer->IncrementPts + 0.005) * 100; /* Round off, then X 100 */
	Increment = (UINT16) XStep;
	Buffer[Count++] = (UINT8) (Increment >> BYTE3SHIFT);
	Buffer[Count++] = (UINT8) Increment;

	return (Count);
}

void SetBucMenuToFactoryDefault(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will initialize the variables stored in FRAM that are       */
/*  accessed via the BUC menu.                                               */
/*                                                                           */
/*****************************************************************************/
{
	BUCMenuFRAM = (BUCMENU_1200*) FRAM1200_BUCMENU_START;

	BUCMenuRAM.VelocityPC = VELOCITY_PC_DEFAULT;
	BUCMenuFRAM->VelocityPC = VELOCITY_PC_DEFAULT;
	BUCMenuRAM.VelocityReporting = FALSE; /* Default velocity reporting to off */
	BUCMenuFRAM->VelocityReporting = FALSE;
	BUCMenuFRAM->RecalCode300 = TRUE;
	BUCMenuRAM.RecalCode300 = TRUE;

	/* Default values for EnergyBraking */
	BUCMenuRAM.EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
	BUCMenuRAM.EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
	BUCMenuFRAM->EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
	BUCMenuFRAM->EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
	BUCMenuFRAM->MicroHomeForce = LEAVINGHOMEFORCEMICROLO;

	CurrentSetup.IdleSpeed = IDLE_SPEED_DEFAULT;
	UpdateCylDefaults(); /* This will update ForcePC in FRAM based on cylinder */

	GetAlarmMask(); /* Fix all alarm masks */
}

UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code)
/*******************************************************************/
/*                                                                 */
/*  This function will Check the Length and Code of command.       */
/*  and return true if correct else return false.                  */
/*******************************************************************/
{
	UINT8 ValidLengthAndCode = FALSE;
	length += DEFAULT_COMMAND_SIZE;
	switch (code) {
	case DOWNLOAD_CURRENT_PRESET: /* Copy the data to HostPreset structure.*/
		if (length == DOWNLOADCOMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case VERIFY_PRESET:
		if (length == VERIFYCOMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case UPLOAD_CURRENT_PRESET:
		if (length == UPLOADCOMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case REQUEST_GRAPH_DATA:
		if (length == GRAPHCOMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case RESET_ALARMS:
		if (length == RESETALARMS_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case RECALL_PRESET:
		if (length == RECALL_PRESET_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_CURRENT_PRESET_PARAMETERS:
		if (length <= SET_CURRENT_PRESET_PARAMETERS_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case START_WELD_DATA:
		if (length == START_WELD_DATA_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_ENERGYMLS:
	case SET_ENERGYPLS:
	case SET_ENERGYMLR:
	case SET_ENERGYPLR:
	case SET_TIMEMLS:
	case SET_TIMEPLS:
	case SET_TIMEMLR:
	case SET_TIMEPLR:
	case SET_PEAKPOWER_CUTOFF:
	case SET_COLLDIST_CUTOFF:
	case SET_MPOWER_SLIMIT:
	case SET_PPOWER_SLIMIT:
	case SET_MPOWER_RLIMIT:
	case SET_PPOWER_RLIMIT:
	case SET_MCOLLAPSE_SLIMIT:
	case SET_PCOLLAPSE_SLIMIT:
	case SET_MCOLLAPSE_RLIMIT:
	case SET_PCOLLAPSE_RLIMIT:
	case SET_MABSOLUTE_SLIMIT:
	case SET_PABSOLUTE_SLIMIT:
	case SET_MABSOLUTE_RLIMIT:
	case SET_PABSOLUTE_RLIMIT:
	case SET_MTRIGDIST_SLIMIT:
	case SET_PTRIGDIST_SLIMIT:
	case SET_MTRIGDIST_RLIMIT:
	case SET_PTRIGDIST_RLIMIT:
	case SET_MMAXFORCE_SLIMIT:
	case SET_PMAXFORCE_SLIMIT:
	case SET_MMAXFORCE_RLIMIT:
	case SET_PMAXFORCE_RLIMIT:
	case SET_ACTUATOR_CLEAR:
		if (length == SET_PARAMETER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case CHECKSUM_ERROR: /* Bad data received */
		if (length == CHECKSUM_ERROR_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case ONBOARD_DIAGNOSTICS: /* Special host command to start */
		if (length == ONBOARD_DIAGNOSTICS_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case SET_PS_SERIALNUMBER:
		if (length <= SET_PS_SERIALNUMBER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_PS_MODELNUMBER:
		if (length == SET_PS_MODELNUMBER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_CONTROLLEVEL:
		if (length == SET_CONTROLLEVEL_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_ACT_SERIALNUMBER:
		if (length <= SET_ACT_SERIALNUMBER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_ACT_MODELNUMBER:
		if (length == SET_ACT_MODELNUMBER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case RESET_PSLIFETIMECOUNTER:
		if (length == RESET_PSLIFETIMECOUNTER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case RESET_OVERLOADCOUNTER:
		if (length == RESET_OVERLOADCOUNTER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case RESET_GENALARMCOUNTER:
		if (length == RESET_GENALARMCOUNTER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_ACTUATOR_CYLINDERDIAMETER:
		if (length == SET_ACTUATOR_CYLINDERDIAMETER_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SET_ACTUATOR_STROKELENGTH:
		if (length == SET_ACTUATOR_STROKELENGTH_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case UPLOAD_REMOTE_CONFIG_PARMS:
		if (length == UPLOAD_REMOTE_CONFIG_PARMS_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_MENU_PTRS:
		if (length == MENU_PTRS_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case START_RUNCYCLE:
		if (length == START_RUNCYCLE_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_CONDN_VAR:
		if (length == SEND_CONDN_VAR_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_STRUCTURE_DATA:
		if (length == SEND_STRUCTURE_DATA_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case RECEIVE_STRUCTURE_DATA:
		ValidLengthAndCode = TRUE;
		break;

	case SEND_MIN_MAX_COMMAND:
		if (length == SEND_MIN_MAX_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case BOTTOMHALF_COMMAND:
		if (length == BOTTOMHALF_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case VGA_POLLING_COMMAND:
		if (length == POLLING_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case WELD_DATA_COMMAND:
		if (length == WELD_DATA_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case PROCESS_ALARM_ITEM:
		if (length == PROCESS_ALARM_ITEM_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_ALARMBIT_COMMAND:
		if (length == SEND_ALARMBIT_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_WELDER_STATE_CMD:
		if (length == SEND_WELDER_STATE_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case SEND_START_WELD_DATA:
		if (length == SEND_START_WELD_DATA_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_SETUPPRINT_DATA:
		if (length == SEND_SETUPPRINT_DATA_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case SEND_PRINT_PARAM:
		if (length == SEND_PRINT_PARAM_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case PMC_COMMAND:
		if (length == PMC_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case VGA_ERRORBEEP_COMMAND:
		if (length == VGA_ERRORBEEP_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case GENERATEALARM_COMMAND:
		if (length == GENERATEALARM_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case VGA_SCREENSETUP_COMMAND:
		if (length == VGA_SCREENSETUP_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case VGA_RESET_ALARMS:
		if (length == VGA_RESET_ALARMS_SIZE)
			ValidLengthAndCode = TRUE;
		break;

	case VGADOWNLOAD_PRESET: /* Copy the data to HostPreset structure.*/
		if ((length == DOWNLOADCOMMAND_SIZE + PRESETNUMBER_SIZE))
			ValidLengthAndCode = TRUE;
		break;

	case VGAUPLOAD_PRESET:
		if (length == (UPLOADCOMMAND_SIZE +2))
			ValidLengthAndCode = TRUE;
		break;

	case USBPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
		if ((length == DOWNLOADCOMMAND_SIZE + 1) || (length
				== DOWNLOADDUPS_SIZE + 1) || (length
				== SEND_SETUPPRINT_DATA_COMMAND_SIZE))
			ValidLengthAndCode = TRUE;
		break;

	case PSPRESET_COMMAND: /* Copy the data to VIEWPreset structure.*/
		if (length == PSPRESET_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case GET_NETWORK_INFO:
		if (length == GET_NETWORK_INFO_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case SEND_SOFTWARE_VERSION:
		if (length == SEND_SOFTWARE_VERSION_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case USERID_DATA_COMMAND:
		if (length == USERID_DATA_LEN)
			ValidLengthAndCode = TRUE;
		break;
	case EVENTALARM_COMMAND:
		if (length == EVENTALARM_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case USERLIST_COMMAND:
		if (length == USERLIST_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case GET_USERID_PASSWORD:
		if (length == GET_USERID_PASSWORD_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case CHANGE_PASSWORD:
		if (length == CHANGE_PASSWORD_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case LOGOUT_COMMAND:
		if(length == LOGOUT_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case WELD_HISTORY_DELETE:
		if (length == DELETE_WELDHISTORY_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case EVENT_HISTORY_DELETE:
		if (length == DELETE_EVENTHISTORY_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case NUMBER_OF_USERS_COMMAND:
		if (length == NUMBER_OF_USERS_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case CHECKSTATEMACHINE:
		if (length == CHECKSTATEMACHINE_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case UDISCAN_COMMAND:
		if (length == UDISCAN_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	 case EXIT_USERIO_COMMAND:
		 if (length ==EXIT_USERIO_COMMAND_SIZE)
		 		ValidLengthAndCode = TRUE;
		  break;
	case COPY_ALL_PRESET_COMMAND:
		if (length == BOTTOM_MENU_COMMAND_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	case SEND_HORN_CLAMP_STATUS:
		if (length == SEND_HORN_CLAMP_STATUS_SIZE)
			ValidLengthAndCode = TRUE;
		break;
	default:
		ValidLengthAndCode = FALSE;
	}
	return ValidLengthAndCode;
}

void SendSelectedPreset(void) {
	SelectedPresetNumber = VGAPresetNum;
}

void GetPSIpAddress(void) {
	static char *ip_addrs;
	ip_addrs = CyGOS::GetIPAddressStr(ETHERNET_INTERFACE_WCTOSBC);
	strncpy(ip_addr, ip_addrs, sizeof(ip_addr) - 1);

}
void GetPSMacAddress(void) {
	unsigned char *mac_addrs;
	mac_addrs = CyGOS::GetMacAddress(ETHERNET_INTERFACE_WCTOSBC);
	sprintf(mac_addr, "%02X%02X%02X%02X%02X%02X", mac_addrs[0], mac_addrs[1],
			mac_addrs[2], mac_addrs[3], mac_addrs[4], mac_addrs[5]);
}

/* This function checks existing username and userid before adding newuser
 * reply ACCEPTED if no same usename and useid available in existing userid database
 * otherwise reply cause of rejection
 * In case of modify user reply ACCEPTED if no change in current username and user id
 * otherwise reply USER_NAME_AND_ID_CHANGE_NOT_PERMITTED
 */
UINT8 Check_ExistingUserDetails(UINT8 operation, SINT32 position) {
	bool id = false;
	UINT8 response = ACCEPTED;
	if (operation == MODIFY) {
		if ( (strcmp(FRAMUserIdObj.UserDetail[position].UserId, useridData.UserId) == 0)) {
		} else// the else part will never execute in modify user case,because we are handling this situation
		{ // in main.gui by deactivating corresponding buttons.
			response = USER_NAME_AND_ID_CHANGE_NOT_PERMITTED;
		}
	}
	else {
		for (UserIdIndex = 0; UserIdIndex < FRAMUserIdObj.UserIDGlobalCount; UserIdIndex++) {

			if (strcmp(FRAMUserIdObj.UserDetail[UserIdIndex].UserId, useridData.UserId) == 0) {
				id = true;
			}
		}
		if (id) {
			response = ID_EXIST;
		}
		if (FRAMUserIdObj.ActiveUserIDCount > (MAXIMUM_ACTIVE_USERS - 1))
			response = MAX_ACTIVE_USERS;
		if (FRAMUserIdObj.UserIDGlobalCount > (MAXIMUM_USERS - 1))
			response = MAXIMUM_USERS_ADDED;
	}
	return response;
}

/*
 * Function checks the authority of operator to do the operation specified in param Func
 * Returns TRUE if the operator is allowed to do the specified operation in param Func
 * else returns FALSE;
 */
BOOLEAN CheckOperatorAuthority(OpAuth Func)
{
	BOOLEAN RetVal = FALSE;
	if((CurrentSetup.Automation == ON) || (CurrentSetup.AuthorityCheck == FALSE) ||
	(CurrentUser.UserLevel > OPERATOR) ||(CurrUserOpAuth & Func) == (Func))
		RetVal = TRUE;

	return RetVal;

}
/* This function search the username in existing userid database if found,then
 * after matching username and password,if matched then only change the password
 * and returns ACCEPTED if password changed successfully otherwise returns cause of rejection
 */
UINT8 ChangePassword(void) {
	SINT32 Count = 0;
	UINT8 Response = 0xff;
	BOOLEAN IsUserExist = FALSE;
	BOOLEAN IsPasswordChanged = FALSE;
	if (strcmp(New_Password, Confirm_Password) != 0)//this condition can be commented,because we have already checked on SBC side
		Response = NEW_CONFIRM_PASSWORD_NOT_MATCH;//so this condition will never met.
	else
	{
		for (Count = 0; (Count < FRAMUserIdObj.UserIDGlobalCount) && (IsUserExist == FALSE); ) {
			if (strcmp(Assign_UserID, FRAMUserIdObj.UserDetail[Count].UserId) == 0) {
				IsUserExist = TRUE;
			}
			else
				Count++;
		}
		if (IsUserExist)// if user exists then only match password
			if (strcmp(FRAMUserIdObj.UserDetail[Count].Password, Old_Password) == 0) {
				strcpy(FRAMUserIdObj.UserDetail[Count].Password, New_Password);
				FRAMUserIdObj.UserDetail[Count].IsFirstTimeLogin = 0x55;//any garbage value but not 10.
				IsPasswordChanged = TRUE;
				RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[Count].CreateModifyTime);//update the time
			}
		if (IsPasswordChanged)
			Response = ACCEPTED;
		else// find the cause of rejection,either user does not exist or username and password do not match
		{
			if (IsUserExist == FALSE)// user does not exist
				Response = NAME_NOT_EXIST;
			else
				//user exist but password not match
				Response = NAME_PASSWORD_NOT_MATCH;
		}
	}
	return Response;
}

/* Verify the user name and password.If there is no user then comparison
 * is made against the default username and password.If one or more users
 * are present then comparison is made with all of them.
 * returns 1 if verified otherwise 2.This function assigns security level
 * to current setup.The user operator level is copied to currentsetup
 * security level
 */
UINT8 VerifyUsernamePassword(void) {
	UINT8 ids = (UINT8) WRONG_NAME_PASSWORD; //take default as not verified
	UINT32 created_days = 0;
	int i = 0;
	RTClock::GetCurrentTime(&RTCMenu);
	for (i = 0; i < FRAMUserIdObj.UserIDGlobalCount; i++) {
		/* new condition included for number of unsuccessfull attempts*/
		if ((strcmp(CurrUserID, FRAMUserIdObj.UserDetail[i].UserId) == 0)
				&& (strcmp(CurrPassword, FRAMUserIdObj.UserDetail[i].Password)
						!= 0)) {
			FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts++;
			if ((FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts
					>= MAX_UNSUCCESSFULL_LOGIN_ATTEMPTS)
					&& (FRAMUserIdObj.UserDetail[i].Status == Enabled)) {
				FRAMUserIdObj.UserDetail[i].Status = Disabled;
				FRAMUserIdObj.ActiveUserIDCount--;
				ids = (UINT8) MAX_WRONG_ATTEMPTS;
			}
		} else if ((strcmp(CurrUserID, FRAMUserIdObj.UserDetail[i].UserId) == 0)
				&& (strcmp(CurrPassword, FRAMUserIdObj.UserDetail[i].Password)
						== 0)) {
			FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts = 0;
			if ((CurrentSetup.Automation == ON)
					&& (FRAMUserIdObj.UserDetail[i].UserLevel < SUPERVISOR)) {
				ids = (UINT8) LOW_AUTHORITY_ERROR;
			} else if (FRAMUserIdObj.UserDetail[i].Status == Enabled) {
				if(FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin != FIRST_TIME_LOGIN)
					UserLoggedIn = TRUE;
				ids = (UINT8) CORRECT_NAME_PASSWORD;
				memcpy(&CurrentUser, &FRAMUserIdObj.UserDetail[i],
						sizeof(UserID));
				CurrUserOpAuth = FRAMUserIdObj.GlobalOpAuth;
				CurrentSetup.SecurityLevel
						= FRAMUserIdObj.UserDetail[i].UserLevel;
				created_days = PasswordExpDays(
						&FRAMUserIdObj.UserDetail[i].CreateModifyTime);
				FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts = 0;
				if(CurrentUser.UserLevel >= SUPERVISOR)
					FirmwareUploadAllowed = TRUE;
				else
					FirmwareUploadAllowed = FALSE;
			} else
				ids = (UINT8) WRONG_NAME_PASSWORD;//user is disabled.
			//No need to check others.Password matched
			break;
		}
	}

	if ((FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin == FIRST_TIME_LOGIN)
			&& (ids == CORRECT_NAME_PASSWORD))//the user verified and he he the firs time user
	{
		ids = (UINT8) FIRST_TIME_LOGIN;
	}

	if ((ids == CORRECT_NAME_PASSWORD) && (created_days
			>= FRAMUserIdObj.UserDetail[i].PassExpTime))//usr exists and his password expires
		ids = (UINT8) PASSWORD_EXPIRED;

	if ((FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin == EXECUTIVE_PASSWORD_CHANGE)
			&& (ids == CORRECT_NAME_PASSWORD))//the user verified and he was change by executive
	{
		ids = (UINT8) EXECUTIVE_PASSWORD_CHANGE;
	}

	return ids;
}

/* This function calculates how many days back
 * the user was created/modified.
 */
int PasswordExpDays(RTCTime *usr)
 {
	int day1,day2;
	struct Date
	{
		UINT8 day;
		UINT8 month;
		UINT8 year;
	};
	Date created,current;
	current.day=(UINT8) RTCMenu.Day;
	current.month = (UINT8) RTCMenu.Century_Month;
	current.year = (UINT8) RTCMenu.Years;
	created.day=(UINT8) usr->Day;
	created.month=(UINT8) usr->Century_Month;
	created.year=(UINT8) usr->Years;	
	day1=julian(created.year+2000, created.month, created.day);
	day2=julian(current.year+2000,current.month,current.day);
	return day2-day1;
	
 }

/*
 * Function copies the ID of user who enables the Automation in Automation user ID for future
 * weld, event and alarm logs.
 */
void SetAutomationUserId() {
	if (CurrentSetup.Automation == ON)
	{
		strncpy(AutomationUsrId, CurrentUser.UserId,
				sizeof(CurrentUser.UserId) - 1);
		RecordEvents(EVENT_FACTORY_AUTOMATION_MODE,"OFF","ON");
	}
	else
	{
		FirmwareUploadAllowed = FALSE;//you need to relogin to upload software,if you put the system in automation
		RecordEvents(EVENT_FACTORY_AUTOMATION_MODE,"ON","OFF");
	}
}

/* Function is called after receving UDI scan from menu.
 *If UDI Scan is enabled in current setup it makes the global flag true/false for state machine.
 */
void SetUDIflag(void)
{
	if(CurrentSetup.UDIScan == ON){
		 UDIScanRecived = FALSE;
		 if(WeldState == READYSTATE)
			 ClearReady();
	}
	else
	{
		 UDIScanRecived = TRUE;
		 VgaUDiStatus = UDISCAN_OFF;
		 memset(UDIString, 0, sizeof(UDIString));

	}
}

/*This function calculates the JulianDay on a given date*/
int julian(int year, int month, int day) { 
	  int a = (14 - month) / 12; 
	  int y = year + 4800 - a; 
	  int m = month + 12 * a - 3; 
	   /*starting from georgian calender date*/
	  return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
}

/* Function clears the UserID on horm clamp confirmation screen.
 */
void ClearUserIdOnClamp(void)
{
	useridData.UserId[0] = 0;
}

/* Function clears the Password on horm clamp confirmation screen.
 */
void ClearPasswordOnClamp(void)
{
	useridData.Password[0] = 0;
}

/* Function verifies the user id and password on horn clamp release from clamp confirmation
 *	menu. For supervisor and above user id and password it makes the ClampOnAlarm flag false
 * to release the horn.
 */
void SetClampAlarmMenuValue(void) {
	SINT32 I;
	BOOLEAN ExitFlag = FALSE;
	if (CurrentSetup.AuthorityCheck == FALSE) {
		//if autority check is not enabled reset the horn automatic
		ClampOnAlarm = FALSE;
	}
	else
	{
		if( ((FRAMUserIdObj.GlobalOpAuth & RADIO_5)!=0) || (CurrentUser.UserLevel!=OPERATOR) ){
		  ClampOnAlarm = FALSE;
		} else {
		  for (I = 0; I < FRAMUserIdObj.UserIDGlobalCount; I++) { //loop trough the user list
			if ((FRAMUserIdObj.UserDetail[I].Status == Enabled) && (FRAMUserIdObj.UserDetail[I].UserLevel >= TECHNICIAN))
			{
				if ((strcmp(useridData.UserId, FRAMUserIdObj.UserDetail[I].UserId) == 0) &&
					(strcmp(useridData.Password, FRAMUserIdObj.UserDetail[I].Password) == 0) &&
					(ExitFlag == FALSE))
				{
					if (FRAMUserIdObj.UserDetail[I].IsFirstTimeLogin != FIRST_TIME_LOGIN)
						ClampOnAlarm = FALSE;
					ExitFlag = TRUE;
				}
			}
		  }
		}
	}
	if (ClampOnAlarm == TRUE) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
		ErrorResponseMaxLimit = 0;
	}
}

/* Function verifies the user id and password on Estop reset confirmation screen.
 */
void EstopResetLogin(void) {
	SINT32 i;
	BOOLEAN ExitFlag = FALSE;
	for (i = 0; i < FRAMUserIdObj.UserIDGlobalCount && (!ExitFlag); i++) {
		if ((FRAMUserIdObj.UserDetail[i].Status == Enabled) && (FRAMUserIdObj.UserDetail[i].UserLevel >= SUPERVISOR)) {
			if ((strcmp(useridData.UserId,
					FRAMUserIdObj.UserDetail[i].UserId) == 0)
					&& (strcmp(useridData.Password,
							FRAMUserIdObj.UserDetail[i].Password) == 0)) {
				if (FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin
						!= FIRST_TIME_LOGIN) {
					VGAEstopLoginFlag = FALSE;
				    ResetStateMachine();
					StartStateMachine();
					SBCReadyFlag = TRUE;
					ReadyFlag = VGA_ReadyFlag;
				}
				ExitFlag = TRUE;
			}
		}
	}
	if(VGAEstopLoginFlag == TRUE) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
		ErrorResponseMaxLimit = 0;
	}
}

void ClearReasonString(void)
/* This function clears the last event reason entered by user.
*/
{
	EventReasonString[0] = 0;
}

void SetEventReasonFlag(void)
/* This function is called when user enters the event reason from menu.
*/
{
	SetEventReason();
}
void GetCurrentHWVerify(void)
{
/* This function is called when user enters the H/w verify settings from menu.
*/
	RadioIndexOld = CurrentSetup.HWVerify;
}

/*
 * This function creates a default user with executive level whenever FRAM is intialized.
 * this function also increments the global user count.
 */
void CreateDefaultExecutive(void)
{
	int index  = 0;
	if(strncmp(FRAMUserIdObj.UserDetail[index].UserId , "ADMIN", strlen("ADMIN")))//check if first user is not admin
	{
		strcpy(FRAMUserIdObj.UserDetail[index].UserId,"ADMIN");
		strcpy(FRAMUserIdObj.UserDetail[index].Password, "123456Aa#");
		FRAMUserIdObj.UserDetail[index].Status = (ActiveStatus) 1;
		FRAMUserIdObj.UserDetail[index].UserLevel = EXECUTIVE;
		FRAMUserIdObj.UserDetail[index].PassExpTime = MAX_PASSEXPTIME; //Set default to maximum
		FRAMUserIdObj.UserDetail[index].IsFirstTimeLogin = FIRST_TIME_LOGIN;
		RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[index].CreateModifyTime);
		if(FRAMUserIdObj.UserIDGlobalCount < 1)//just an extra precaution
		{
			FRAMUserIdObj.UserIDGlobalCount++;
			FRAMUserIdObj.ActiveUserIDCount++;
		}
	}
}

void GetDownSpeed(void)
{
	TempFlowValue = CurrentPreset.Downspeed;
}

/***************************************************************************
*
*   Purpose:
*	Authority check ensures that users logging into the power supply only have access to
*	features dependent on their authority level. Set to Yes to enables authority level functions
*	and menus.
*
*   Entry condition:
*	void
*
*   Exit condition:
*	void
*
***************************************************************************/
void SetAuthorityForFirmware(void)
{
	if(CurrentSetup.AuthorityCheck == FALSE)
	{
		FirmwareUploadAllowed = FALSE;
		RecordEvents(EVENT_AUTHORITY_CHECK_CHANGED,"ON","OFF");
		strcpy(CurrentUser.UserId,"N/A");
		CurrentUser.UserLevel = BRANSON;
		CurrUserOpAuth =(OpAuth)0;
		CurrentUser.Status = Enabled;
		CurrentUser.PassExpTime = MAX_PASSEXPTIME;   //Set default to maximum
		UserLoggedIn = TRUE;
	}
	else
	{
		RecordEvents(EVENT_AUTHORITY_CHECK_CHANGED,"OFF","ON");
		if(strcmp(CurrUserID,"")==0)strcpy(CurrUserID,"N/A");
		strcpy(CurrentUser.UserId,CurrUserID);
	}
}

/*This handler function sets the user Id need to be shown on system information screen*/
void SendCurrentUserId()
{
	strncpy(CurrUserID_For_SysInfo, CurrentUser.UserId,sizeof(CurrentUser.UserId) - 1);
}

/***************************************************************************
*
*   Purpose:
*	This handler function sets the lower flow valve need to be shown on system information screen
*   the 'S' indicate slow, it mean that the flow can work with 2% and up downspeed
*   the 'N' indicate fast, it mean that the flow can work with 15% and up downspeed
*   the LowerFlowValve when is TRUE indicate that we are going to apply the formula for 1.5" and 2.0" cylinders
*
*   Entry condition:
*	void
*
*   Exit condition:
*	void
*
***************************************************************************/
void SendLowerFlowValve(void)
{
	if (CurrentSetup.LowerFlowValveFlag == TRUE)
	{
		FlowValveAEDEmulationIndicatorStr[ZERO]='S';
	}
	else
	{
		FlowValveAEDEmulationIndicatorStr[ZERO]='F';
	}
	FlowValveAEDEmulationIndicatorStr[ONE]='\0';
}

/*This handler function prepare and fill the preset data in the buffer and send it to SBC */
UINT16 GetPresetNames_USB(UINT8 * AckBuf,UINT16 ReceiveValuePtr)
{
	UINT16 length = 0;
	UINT32 i;
	UINT32 j;
	UINT8 * AckBuffTempPtr = AckBuf + 8;//Advanced here to have space for number of presets read and up to which preset num has been read.
    for(i = ReceiveValuePtr, j = 0; i <= MAX_POSSIBLE_PRESET && j < MAXPRESET_TO_SEND; i++)
    {
    	if (PresetEnableFlags[i] == TRUE)
    	{
    		Readpreset(i, (Ver1200Setups*)(AckBuffTempPtr + (sizeof(SETUPS_Ver1200) * j)));
    		length += sizeof(SETUPS_Ver1200);
    		j++;
    	}
    }
    memcpy(AckBuf, &(j),sizeof(UINT32)); //send the total count
    length+=sizeof(UINT32);
    memcpy(AckBuf+ 4,&(i),sizeof(UINT32));
    length+=sizeof(UINT32);
    return length;

}


/*This handler function checks whether to display Login Button on Main menu*/
void CheckForLogInButtonDisplay(void)
{
	if(CurrentSetup.AuthorityCheck == FALSE)
	{
		ShowLogInButton  = TRUE;
		ShowLogOutButton = FALSE;
	}
	else
	{
		ShowLogInButton  = FALSE;
		ShowLogOutButton = TRUE;
	}
}


/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when SaveToPreset button is clicked in Horn
*	Down screen
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/ 
void HDSavePreset(void)
{
	if((CurrentPreset.Downspeed != HdParams.DownSpeed) || (CurrentPreset.TunedPreset != HdParams.DownSpeedTuned)
				|| (CurrentPreset.TunedFlowValue != HdParams.TunedFlowValue)) //coverity fix 12564
	{
	 	EventParameterID = FLOWCONTROL;
	   	Type = sint32;
	   	memset(ParamNewVal, 0, sizeof(ParamNewVal));
	   	memset(ParamOldVal, 0, sizeof(ParamOldVal));
	   	memcpy(ParamOldVal, (UINT32*)&CurrentPreset.Downspeed, sizeof(UINT32));
	   	CurrentPreset.Downspeed = HdParams.DownSpeed;
	   	CurrentPreset.TunedFlowValue = HdParams.TunedFlowValue;
	   	CurrentPreset.TunedPreset = HdParams.DownSpeedTuned;
	   	memcpy(ParamNewVal, (UINT32*)&CurrentPreset.Downspeed, sizeof(UINT32));
		GlobalCommandID = FLOW_CONTROL_ID;
	   	UpdateCurrentPresetAndSetup(FLOWCONTROL);
	}

	if((CurrentPreset.WeldPressure != HdParams.WeldPressure))
	{
	 	EventParameterID = WELDPRESSURE;
	   	Type = sint32;
	   	memset(ParamNewVal, 0, sizeof(ParamNewVal));
	   	memset(ParamOldVal, 0, sizeof(ParamOldVal));
	   	if(HdParams.WeldPressure < MinLimit.WeldPressure)
	   		HdParams.WeldPressure = MinLimit.WeldPressure;
	   	memcpy(ParamOldVal, (UINT32*)&CurrentPreset.WeldPressure, sizeof(UINT32));
	   	CurrentPreset.WeldPressure = HdParams.WeldPressure;
	   	memcpy(ParamNewVal, (UINT32*)&CurrentPreset.WeldPressure, sizeof(UINT32));
		GlobalCommandID = WELD_PRESSURE_ID;
		if((!CurrentPreset.HoldPressureFlag))
			  CurrentPreset.HoldPressure = CurrentPreset.WeldPressure;
	   	UpdateCurrentPresetAndSetup(WELDPRESSURE);
	}
}
/***************************************************************************
*
*   Purpose:
*	This function is called whenever hold pressure is changed from menu or
*	hold pressure settings default/on changed from menu.
*	It makes Hold Pressure equal to Weld Pressure if HoldPressure is changed
*	from default to on.
*
*   Entry condition:
*	void
*
*   Exit condition:
*	void
*
***************************************************************************/

void SetHoldPressure(void)
{
	if((!CurrentPreset.HoldPressureFlag))
		 CurrentPreset.HoldPressure = CurrentPreset.WeldPressure;
}

/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called on Cal Full Sensors confirmation button click on menu.
*	It makes a flag true to disable checking for inaccurate pressure alarms.
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void EnableStartSensorCal()
{
	if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE)) {
		NackError = WELDER_PROCESS_ERROR;
		ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
		ErrorResponseMaxLimit = 0;
	} else {
		StartingSensorCal = TRUE;
		ResetStateMachineIndex();
		ClearReady();
	}
}


/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when horn down screen is entered. It updates 
*	the variable mapped in MAP table for Presure Display
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/ 
void UpdatePressureOnHornDownEntry()
{
	if(SetPressureValue == 0)
		HdParams.WeldPressure = 0;
	else if(HdParams.WeldPressure == 0)
		HdParams.WeldPressure = CurrentPreset.WeldPressure; //Get initial value from Current Preset
}

/***************************************************************************
*                                                                         
*   Purpose:
*	This function is called when horn down screen is entered. It updates the 
*	variable mapped in MAP table for Flow Display
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/  
void UpdateFlowOnHornDownEntry()
{
	if(HdParams.TempDownSpeed == 0)
	{
		HdParams.TempDownSpeed = HdParams.DownSpeed = CurrentPreset.Downspeed; //Get initial value from Current Preset
		HdParams.DownSpeedTuned = CurrentPreset.TunedPreset;
		if(CurrentPreset.TunedPreset)
			HdParams.TunedFlowValue = CurrentPreset.TunedFlowValue;
		else
			HdParams.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
	}
	else
	{
		HdParams.TempDownSpeed =  HdParams.DownSpeed;
	}
}



/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "command.ut"
#endif
/* FOR UNIT TEST ONLY */

/* FOR INTEGRATION TEST ONLY */
#ifdef INCLUDE_INTEGRATION_TEST
#include "command.it"
#endif
/* FOR INTEGRATION TEST ONLY */
