/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/command.h_v   1.35   Jun 07 2017 11:46:34   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/command.h_v  $
 * 
 *    Rev 1.35   Jun 07 2017 11:46:34   RJamloki
 * Added define MAX_LOWER_FLOW_VALVE_LEN 2 for small flow valve indicator
 * 
 *    Rev 1.34   26 May 2016 16:22:28   RJamloki
 * Added a login response 
 * EXECUTIVE_PASSWORD_CHANGE
 * 
 *    Rev 1.33   16 Dec 2015 14:26:36   RJamloki
 * Add defines SEND_HORN_CLAMP_STATUS  & SEND_HORN_CLAMP_STATUS_SIZE                 
 * 
 *    Rev 1.32   17 Nov 2015 16:11:58   RJamloki
 * Added an extra item for operation authority
 * “Reset Horn Clamp Alarm”
 * 
 *    Rev 1.31   08 Apr 2015 13:51:06   AnPawar
 * Changes for Pressure Stepping in MAP_ID enum.
 * 
 *    Rev 1.30   27 Mar 2015 11:13:58   amaurya
 * MAXACKLENGTH increased to 30720.This increment is done to accommodate 50 weld cycle data plus 1 graph data.
 * 
 *    Rev 1.29   16 Mar 2015 02:58:14   amaurya
 * AMP1_FIX_ID added to MAP_ID enum for setuplimit parameter Amplitude.
 * 
 *    Rev 1.28   11 Mar 2015 09:21:50   amaurya
 * Setup parameter IDs added to MAP_ID enum.
 * 
 *    Rev 1.27   02 Jan 2015 06:28:48   rjamloki
 * TWEAK_DOWN_ID and TWEAK_UP_ID added in enum MAP_ID
 * 
 *    Rev 1.26   02 Jan 2015 04:14:22   rjamloki
 * COPY_ALL_PRESET_COMMAND,COPY_ALL_PRESET_COMMAND_SIZE,MAXPRESET_TO_SEND macros defined to preset copy all and FirmwareUploadAllowed flag added
 * 
 *    Rev 1.25   11 Dec 2014 08:32:28   AnPawar
 * ack buffer size increased to 16kb.and defines for ps sn and act sn
 * 
 *    Rev 1.24   14 Nov 2014 05:23:08   rjamloki
 * MIN_IDLELOGOUTTIME macro added.
 * 
 *    Rev 1.23   10 Nov 2014 04:39:02   AnPawar
 * Added new commands .Enum for UDI scan status.
 * 
 *    Rev 1.22   20 Oct 2014 06:38:22   AnPawar
 * Removed defines and declarations related to VQS.
 * 
 *    Rev 1.21   03 Oct 2014 06:21:32   rjamloki
 * UnitFormat variable added in map structure
 * 
 *    Rev 1.20   26 Sep 2014 03:02:00   rjamloki
 * Added define for max permitted wrong attempts during login
 * 
 *    Rev 1.19   11 Sep 2014 11:23:42   rjamloki
 * coverity and review fixes
 * 
 *    Rev 1.18   05 Sep 2014 04:08:56   rjamloki
 * define changes due to removal of compressed preset
 * 
 *    Rev 1.17   22 Aug 2014 06:55:16   rjamloki
 * Adedd HOLD_FORCE_MAX in enum MAP_ID. Map structure definition moved to header file.
 * 
 *    Rev 1.16   18 Aug 2014 01:49:58   rjamloki
 * packed user id structures
 * 
 *    Rev 1.15   07 Aug 2014 16:00:32   tayars
 * Added flag to tell SBC to update.
 * 
 *    Rev 1.14   28 Jul 2014 13:02:12   rjamloki
 * Added udi scan command
 * 
 *    Rev 1.13   09 Jul 2014 14:52:28   rjamloki
 * Added enums for preset locked and validation status.
 * 
 *    Rev 1.12   20 Jun 2014 14:07:20   rjamloki
 * Added pressure and flow control IDs in Map Ids enum
 * 
 *    Rev 1.11   11 Jun 2014 12:47:10   rjamloki
 * Added return code for VGA after maximum user added, increased user id buffer to maximum 
 * 
 *    Rev 1.10   27 May 2014 10:15:38   amaurya
 * Increased the number of userid details per udp packet
 * 
 *    Rev 1.9   21 May 2014 10:49:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 04:06:12   rjamloki
 * Added Weld and Event History delete commands
 * 
 *    Rev 1.7   07 May 2014 10:47:10   rjamloki
 * Added some enums for user login and pasword change.
 * 
 *    Rev 1.6   21 Apr 2014 13:27:08   rjamloki
 * Login verification, Event and alam logging implementation added
 * 
 *    Rev 1.5   26 Mar 2014 12:43:02   rjamloki
 * macro GET_USERNAME_PASSWORD_SIZE changed.MAXUSERID macro added
 * 
 *    Rev 1.4   05 Mar 2014 13:56:58   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 05:00:06   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:47:34   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      command.h
  ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

/*
 ------------------------------- DEFINES ---------------------------------------
*/
#ifndef COMMAND_H_
#define COMMAND_H_

#include "menu.h"
#include "ipsatype.h"
#include "Names.h"
#include "rtclock.h"
#include "preset.h"
#define MAXIMUM_USERS 1000
#define MAXIMUM_ACTIVE_USERS  500
#define SERIALLENGTH 12                  /* Number bytes in PS Serial Number */ 
#define MAXACKLENGTH 30720               /* Maximum ACK Buffer length
										 This increment is done to accommodate 50 weld cycle data plus 1 graph data*/
#define SERIAL_MAXACKLENGTH 2048
#define MAXACTIONFLAGS 10
#define STOPASYNCWELDDATA  0
#define STARTASYNCWELDDATA 1
#define SENDNOWOFF 0
#define SENDNOWON  1
#define PROCESSPASSWORDSCREEN 1
#define VGA_PRINTERON 0x01
#define VGA_SCREENCALIB 0x02
#define VGA_USBFULLALARM 0x04
#define VGA_SCREENUSERDIAG	0x08
#define VGA_HISTORYVALIDATIONFAILED	0x01
#define MAX_VERSION_LENGTH 10
#define PMCDATACLEAR 2
#define ADDTOPMCDATA 3
#define SENDPMCDATA 4
#define VIEWPRESETPARTONE 1
#define VIEWPRESETPARTTWO 2
#define MIN_PASSEXPTIME 1
#define MAX_PASSEXPTIME 99999
#define MIN_IDLELOGOUTTIME  2
#define MAX_IDLELOGOUTTIME 99999

#define ACKBUF_HEADER 8;
/* DLE,STX,FUN(2 bytes),CNT(2 bytes), CHKSUM,DLE,ETX */
#define SPCSIZE  (sizeof(WELD_DATA7_02) + 9) /* Welder Id (2 bytes) not included */ 

#define UPLOADCOMMAND_SIZE      9 /* DLE,STX,FUN(2 bytes),CNT(2 bytes),CHKSUM,DLE,ETX */
#define DOWNLOADCOMMAND_SIZE    (sizeof(Ver1200Setups) + 9)
#define DOWNLOADDUPS_SIZE       (sizeof(Ver1200Setups) + sizeof(DUPS_CURRENTPARAMSET) + DUPS_PARAMSETNAMELEN + 9)
#define RESETALARMS_SIZE        9
#define VERIFYCOMMAND_SIZE      9
#define GRAPHCOMMAND_SIZE      11
#define BYTE1SHIFT             24  /* Highest byte of 4  */
#define BYTE2SHIFT             16  /* 2nd high byte of 4 */
#define BYTE3SHIFT             8   /* 3rd high byte of 4 */
#define VEL_POINTS             3   /* # of points used per velocity calculation */
#define MSPERSEC           10000   /* ms/sec x 10 to increase resolution */

#define LANGUAGE_COUNT  8  /* Maximum number of button on the keypad screen */
#define SEND_MENU_PTRS          1000
#define SEND_BOTTOM_MENU_DATA   1001
#define PROCESS_SUBMENU         1002
#define SET_TIME                1003
#define SET_DATE                1004
#define PROCESS_CHOICE          1005
#define SEND_ALPHA_DATA         1006
#define SET_ALPHA_VALUE         1007
#define SEND_VARIABLE_DATA      1008
#define SET_VARIABLE_VALUE      1009
#define PROCESS_RADIO           1010
#define PROCESS_TOGGLE          1011
#define PROCESS_RADIOMENU       1012
#define PROCESS_RADIOLARGEMENU  1013
#define PROCESS_RADIOLARGE      1014
#define PROCESS_VGABUTTON       1015 
#define POLLING_COMMAND         1016
#define VGA_HOST_COMMAND        1000
#define WELD_GRAPH_COMMAND      1017
#define PROCESS_PASSWORD_SAVE   1018
#define PROCESS_PRESET_COMMAND  1019
#define CHECK_PASSWORD_COMMAND  1020
#define PROCESS_ALARM           1021 
#define SEND_ALARM_MENU         1022
#define SEND_WELDER_STATE       1023
#define SEND_START_WELD_DATA    1024 
#define SEND_PRINT_DATA         1025   
#define WELD_PARAM_NAME         1026
#define SEND_PRINT_PARAM        1027
#define VGAUPLOAD_PRESET        1028
#define VGADOWNLOAD_PRESET      1029
#define VGAPMC_COMMAND          1030 
#define VGASEQUENCING_COMMAND   1031
#define VGA_ERRORBEEP_COMMAND   1032
#define GENERATEALARM_COMMAND   1033
#define VGA_USBPRESET_COMMAND   1034 
#define VGA_PSPRESET_COMMAND    1035 
#define VGA_SCREENSETUP_COMMAND 1036
#define VGA_HSABORT_COMMAND     1037
#define VGA_POLLING_COMMAND     1038


#define SEND_STRUCTURE_DATA     1050   //to be adjusted accordingly.
#define RECEIVE_STRUCTURE_DATA  1051   //to be adjusted accordingly.
#define SEND_MIN_MAX_COMMAND    1052   //to be adjusted accordingly.
#define BOTTOMHALF_COMMAND      1053   //to be adjusted accordingly.
#define SEND_CONDN_VAR          1100   //to be adjusted accordingly.
#define WELD_DATA_COMMAND       1054
#define SEND_WELDER_STATE_CMD   1055
#define PMC_COMMAND             1056
#define PSPRESET_COMMAND        1057 
#define SEND_ALARMBIT_COMMAND   1058
#define PROCESS_ALARM_ITEM      1059 
#define SEND_SETUPPRINT_DATA    1060
#define USBPRESET_COMMAND       1061
#define VGA_RESET_ALARMS        1062
#define START_RUNCYCLE          1063
#define CHECKSTATEMACHINE       1064
#define GET_NETWORK_INFO        1200
#define SEND_SOFTWARE_VERSION   1201
#define GET_USERID_PASSWORD     1101
#define CHANGE_PASSWORD         1102
#define USERLIST_COMMAND        1090
#define EVENTALARM_COMMAND      1092
#define USERID_DATA_COMMAND     1096
#define LOGOUT_COMMAND          1103
#define WELD_HISTORY_DELETE     1105
#define EVENT_HISTORY_DELETE    1106
#define NUMBER_OF_USERS_COMMAND 1202
#define UDISCAN_COMMAND         1098
#define EXIT_USERIO_COMMAND     1203
#define COPY_ALL_PRESET_COMMAND 1099
#define SEND_HORN_CLAMP_STATUS  1204

#define SETUSERDATA             0x02
#define GETUSERDATA             0x01

#define MENU_PTRS_COMMAND_SIZE                15
#define BOTTOM_MENU_COMMAND_SIZE              13
#define PROCESS_SUBMENU_COMMAND_SIZE          13
#define SET_TIME_COMMAND_SIZE                 15 
#define SET_DATE_COMMAND_SIZE                 16 
#define PROCESS_CHOICE_COMMAND_SIZE           14   
#define ALPHA_DATA_COMMAND_SIZE               13
#define SET_ALPHA_COMMAND_SIZE                14  
#define VARIABLE_DATA_COMMAND_SIZE            13 
#define SET_VARIABLE_COMMAND_SIZE             21 
#define PROCESS_RADIO_COMMAND_SIZE            15
#define PROCESS_TOGGLE_COMMAND_SIZE           14 
#define PROCESS_RADIOMENU_COMMAND_SIZE        13
#define PROCESS_RADIOLARGEMENU_COMMAND_SIZE   13
#define PROCESS_RADIOLARGE_COMMAND_SIZE       15
#define UPLOAD_REMOTE_CONFIG_PARMS_SIZE       31
#define ACK_REPLY_SIZE                        11 
#define WELD_GRAPH_COMMAND_SIZE               11
#define WELD_DATA_COMMAND_SIZE                11
#define PROCESS_VGABUTTON_COMMAND_SIZE        13 
#define PROCESS_PRESET_COMMAND_SIZE           14
#define POLLING_COMMAND_SIZE                  10 
#define PROCESS_ALARM_COMMAND_SIZE            13
#define SEND_ALARM_MENU_COMMAND_SIZE          9
#define SEND_WELDER_STATE_COMMAND_SIZE        9 
#define SEND_START_WELD_DATA_COMMAND_SIZE     9
#define SEND_PRINT_DATA_COMMAND_SIZE          10
#define WELD_PARAM_NAME_COMMAND_SIZE          9
#define SEND_PRINT_PARAM_COMMAND_SIZE         9
#define VGAPMC_COMMAND_SIZE                   10
#define VGASEQUENCING_COMMAND_SIZE            10
#define VGA_ERRORBEEP_COMMAND_SIZE            9
#define GENERATEALARM_COMMAND_SIZE            10
#define VGA_PSPRESET_COMMAND_SIZE             11
#define VGA_SCREENSETUP_COMMAND_SIZE          9  
#define VGA_HSABORT_COMMAND_SIZE              9 

#define SEND_STRUCTURE_DATA_SIZE              12
#define RECEIVE_STRUCTURE_DATA_SIZE           80 //17 + 25 for storing 30 sequencing preset
#define SEND_CONDN_VAR_SIZE                   9
#define SEND_MIN_MAX_COMMAND_SIZE             11
#define BOTTOMHALF_COMMAND_SIZE               11
#define PMC_COMMAND_SIZE                      10
#define SEND_SETUPPRINT_DATA_COMMAND_SIZE     10
#define PSPRESET_COMMAND_SIZE                 12
#define START_RUNCYCLE_COMMAND_SIZE           10
#define GET_NETWORK_INFO_SIZE                 21 //9+4+4+4
#define GET_USERID_PASSWORD_SIZE              31 //9+11+11
#define CHANGE_PASSWORD_SIZE                  53//9+11+11+11+11
#define USERLIST_COMMAND_SIZE                 10 //10
#define EVENTALARM_COMMAND_SIZE               18 //10
#define USERID_DATA_LEN                       13 //52+9
#define LOGOUT_COMMAND_SIZE                   10
#define DELETE_WELDHISTORY_SIZE               10
#define DELETE_EVENTHISTORY_SIZE              10
#define NUMBER_OF_USERS_COMMAND_SIZE          10
#define CHECKSTATEMACHINE_SIZE                9
#define UDISCAN_COMMAND_SIZE                  34 //25+9
#define EXIT_USERIO_COMMAND_SIZE              10
#define COPY_ALL_PRESET_COMMAND_SIZE          13

#define RECALL_PRESET_COMMAND_SIZE                 10
#define SET_CURRENT_PRESET_PARAMETERS_COMMAND_SIZE 26
#define START_WELD_DATA_COMMAND_SIZE               11
#define SET_PARAMETER_COMMAND_SIZE                 13
#define CHECKSUM_ERROR_COMMAND_SIZE                 9
#define ONBOARD_DIAGNOSTICS_COMMAND_SIZE            9
#define SET_PS_SERIALNUMBER_COMMAND_SIZE           21
#define SET_PS_MODELNUMBER_COMMAND_SIZE            14
#define SET_CONTROLLEVEL_COMMAND_SIZE              13
#define SET_ACT_SERIALNUMBER_COMMAND_SIZE          19
#define SET_ACT_MODELNUMBER_COMMAND_SIZE           12
#define RESET_PSLIFETIMECOUNTER_COMMAND_SIZE        9
#define RESET_OVERLOADCOUNTER_COMMAND_SIZE          9
#define RESET_GENALARMCOUNTER_COMMAND_SIZE          9
#define SET_ACTUATOR_CYLINDERDIAMETER_COMMAND_SIZE 13
#define SET_ACTUATOR_STROKELENGTH_COMMAND_SIZE     13
#define UPLOAD_REMOTE_CONFIG_PARMS_COMMAND_SIZE     9
#define DEFAULT_COMMAND_SIZE                        9
#define MAX_ALPHA_ITOM_COMMAND_SIZE                25
#define SBC_SW_VERSION_LENTGH                       6
#define SEND_ALARMBIT_COMMAND_SIZE                  9
#define PROCESS_ALARM_ITEM_COMMAND_SIZE            11
#define VGA_RESET_ALARMS_SIZE                       9
#define SW_VERSION_LENTGH    						6
#define ETHERNET_INTERFACE_WCTOSBC 					0
#define SEND_SOFTWARE_VERSION_SIZE                  9
#define SEND_HORN_CLAMP_STATUS_SIZE                 9

#define ACCESS_NOT_ALLOWED 1
#define SHOW_MAIN_MENU 2
#define REFRESH_MENU 3
#define SHOW_PREV_MENU 4
#define SHOW_PASSWORD_SCREEN 5
#define SHOW_PASSWORD_ENTRY1 6
#define SHOW_PASSWORD_ENTRY2 7
#define DUPS_NOT_UPLOADED 8
#define PS_MISMATCH 9
#define DUPS_NOT_DOWNLOADED 10
#define DUPS_NOT_AVAILABLE  11
#define SHOW_WELDINGON_MESSAGE   11
#define SHOW_MSG_SCREEN          4
#define COLSETUP_MSG_SCREEN   12

#define NO_DATA_COMMAND_SIZE 9
#define ACK 0x06
#define NAK 0x15

/* Error Codes Returned to Controller from Command Parser  */

#define INVALID_SOURCE       0x00002
#define BAD_CHECKSUM         0x00004
#define MAX_ERROR            0x00008+1      /* add 1 for data follows */
#define MIN_ERROR            0x00010+1      /* add 1 for data follows */
#define INVALID_OPCODE       0x00020
#define PARAMETER_ERROR      0x00040
#define UNIMPLEMENTED_OPCODE 0x00080
#define INVALID_SYS_CONFIG   0x00200
#define HARDWARE_FAILURE     0x00800
#define INVALID_AUTH_CODE    0x02000
#define ILLEGAL_COMMAND      0x04000
#define WELDER_PROCESS_ERROR 0x08001


#define REFRESH_MENU_AED   179
#define REFRESH_MENU_AE    181
#define REFRESH_MENU_AEF2  182
#define RESULT_MENU        183
#define RESULT_MENU_AE     184
#define REFRESH_MENU_AEF1  175

#define MAX_LOWER_FLOW_VALVE_LEN 2
#define MAX_USERNAME_LEN 11
#define MAX_PASSWORD_LEN 11
#define MAX_UDISTRING_LEN 25
#define MAX_UNSUCCESSFULL_LOGIN_ATTEMPTS 4
#define MAX_USERID_LEN 6

#define DUPS_OL_MENUSHIFT 4
//Additional data other than defined in enum RUN_PARAM sent to SBC as part of weld results
#define TRIGFORCEPARAM 32
#define PSSERIALNUMPARAM 33
#define ACTSERIALNUMPARAM 34

#define MAXPRESET_TO_SEND      10

typedef enum DATA_TYPE {
	nothing, Uint8, sint8, UInt16, sint16, Uint32, sint32, boolean, str, arr
}DataType;

/* MapIDs list*/

enum MAP_ID {
	UNIT_SET = 0,
	TIME_INFO = 5,
	DATE_INFO = 6,
	PSFREQ_WATTINFO = 17,
	CALIBRATE_INFO = 19,
	PSSERIAL_NUMID = 23,
	ACTSERIAL_NUMID,
	PASSWD_ENTRY = 30,
	PASSWD_SAVE = 54,
	TIMEDISPLAY = 65,
	PKPWRDISPLAY,
	ENERGYDISPLAY,
	VELOCITYDISPLAYAED,
	VELOCITYDISPLAYAEF,
	FREQMINDISPLAY,
	FREQMAXDISPLAY,
	FREQSTARTDISPLAY,
	FREQENDDISPLAY,
	FREQCHGDISPLAY,
	SETAMPADISPLAY,
	SETAMPBDISPLAY,
	WELDABSDISPLAY,
	ACTPRESSDISPLAY,
	TOTALABSDISPLAY,
	WELDCOLDISPLAY,
	TOTALCOLDISPLAY,
	WELDFORCEDISPLAY,
	SETPRESSUREADISPLAY,
	SETPRESSUREBDISPLAY,
	PRESETNUMDISPLAY,
	CYCLETIMEDISPLAY,
	J3_32IN = 88,
	J3_33IN,
	J3_19IN,
	J3_17IN,
	J3_31IN,
	J3_1IN,
	J3_8OUT,
	J3_36OUT,
	J3_22OUT,
	RESTORE_USERIO = 99,
	WELDMODE_SET = 101,
	WELDTIME_ID = 102,
	HOLDTIME_ID = 103,
	TRIGGERFORCE_ID = 104,
	AMP1_ID = 107,
	AMP1_FIX_ID = 114,
	WELDENERGY_ID = 116,
	PEAKPWR_ID = 117,
	COLDIST_ID = 118,
	ABSDIST_ID = 119,
	SCRUBTIME_ID = 120,
	AMPSCRUBTIME_ID = 121,
	TRIGGERDISTANCE_ID = 175,
	DIAGJ3_21OUT = 176,
	DIAGJ3_34OUT = 196,
	AMP_CNTL_SET = 208,
	FREQ_CNTL_SET,
	AUTO_NAME = 216,
	SAME_NAMEAS_OLD,
	SAME_NAMEAS_NEW,
	ASSIGN_NAME,
	PRST_LISTING,
	PRST_RECALL = 223,
	PRST_VERIFY,
	PRST_INFO,
	SEQUENCE_LISTING = 235,
	SEQUENCE_LIST_UPDATE,
	PRESSUREMODE_SET = 239,
	XSCALE_SET = 258,
	TWEAK_DOWN_ID = 262,
	WELD_PRESSURE_ID = 272,
	HOLD_PRESSURE_ID = 273,
	FLOW_CONTROL_ID = 274,
	TWEAK_UP_ID = 276,
	DIAGJ3_8OUT = 284,
	DIAGJ3_22OUT = 285,
	DIAGJ3_36OUT = 286,
	DIAGJ3_1IN = 287,
	DIAGJ3_17IN = 288,
	DIAGJ3_19IN = 289,
	DIAGJ3_31IN = 292,
	DIAGJ3_32IN = 293,
	DIAGJ3_33IN = 294,
	DIAGJ3_5OUT = 296,
	DIAGJ3_6OUT = 297,
	DIAGJ3_20OUT = 298,
	USR_ID_COL = 299,
	UDI_COL = 300,
	PRESETREV_COL = 301,
	DIAGJ3_35OUT = 309,
	RESTORE_ACTUATOR = 378,
	RESTORE_FRAM,
	RESTORE_PRINTING,
	RESTORE_GLOBAL,
	DIGITAL_TUNE_CHOICE = 382,
	DIGITAL_FREQ = 384,
	RECALL_MIN_MSG = 390,
	RECALL_MAX_MSG,
	RECALL_COLDSTART_MSG,
	SAVE_MIN_MSG,
	SAVE_MAX_MSG,
	SAVE_COLDSTART_MSG,
	RESTORE_MINMAX_MSG,
	RESTORE_COLDSTART_MSG,
	HORN_SCAN_MENU,
	HS_START,
	HORN_DOWN_MENU = 401,
	RT_DIST = 406,
	MAIN_MENU = 409,
	WELDMODE_MENU,
	GRAPH_MENU,
	RUN_MENU,
	UNIQUE_PRST = 416,
	SETUP_ALARM,
	COLDSTART_ALL,
	TEST_AMPLITUDE = 421,
	CALIB_SENSOR = 426,
	CALIB_ACTUATOR = 429,
	ERRORCODE_ID = 434,
	PARAMETER_NUM = 455,
	DIAGJ3_4OUT = 477,
	POWER_TEST = 485,
	MENU_SYNC = 519,
	BATCHCOUNT_INFO = 523,
	HOLDFORCE_MAX = 538,
	WELDPRESSURE_PLT_ID = 551,
	WELDPRESSURE_MLT_ID = 552,
	DOWNSPEED_PLT_ID = 553,
	DOWNSPEED_MLT_ID = 554,
	HOLDPRESSURE_PLT_ID = 555,
	HOLDPRESSURE_MLT_ID = 556,
	HOLDTIME_PLT_ID = 557,
	HOLDTIME_MLT_ID = 558,
	AMPA_PLT_ID = 559,
	AMPA_MLT_ID = 560,
	TRIGFORCE_PLT_ID = 561,
	TRIGFORCE_MLT_ID = 562,
	WELDTIME_PLT_ID = 563,
	WELDTIME_MLT_ID = 564,
	WELDENERGY_PLT_ID = 565,
	WELDENERGY_MLT_ID = 566,
	PEAKPOWER_PLT_ID = 567,
	PEAKPOWER_MLT_ID = 568,
	COLLAPSEDIST_PLT_ID = 569,
	COLLAPSEDIST_MLT_ID = 570,
	ABSDIST_PLT_ID = 571,
	ABSDIST_MLT_ID = 572,
	SCRUBTIME_PLT_ID = 573,
	SCRUBTIME_MLT_ID = 574,
	SCRUBAMP_PLT_ID = 575,
	SCRUBAMP_MLT_ID = 576,
	TRIGDIST_PLT_ID = 577,
	TRIGDIST_MLT_ID = 578,
	WELD_PRESSURE_ID_HD = 579,
	FLOW_CONTROL_ID_HD = 580,
	TWEAK_DOWNHD_ID = 581,
	TWEAK_UPHD_ID = 582,
};

/*USER information*/
#define DATAINONEPACKET 72
#define EVENTINONEPACKET 10
#define MAXUSERID 1000

enum ActiveStatus
{
   Disabled = 0x00, Enabled,
};

enum OpAuth
{
   ResetAlarm = BIT0,
   RunInvalidatedPreset = BIT1,
   RecalPreset = BIT2,
   Calibration = BIT3,
   RstBatchCount = BIT4,
   RstHornClampAlarm = BIT5
};

typedef struct
{
   char UserId[6];
   char Password[11];
   enum LEVEL UserLevel;
   enum ActiveStatus Status;
   UINT32 PassExpTime;
   UINT8 IsFirstTimeLogin;
   UINT8 UnSuccessFullAttempts;
   RTCTime CreateModifyTime;
}__attribute__((__packed__)) UserID;

typedef struct {
	SINT32 ActiveUserIDCount;
	SINT32 UserIDGlobalCount;
	enum OpAuth GlobalOpAuth;
	UserID UserDetail[1000];
}__attribute__((__packed__)) FRAMUserID;

enum ADD_MODIFY_RESPONSE
{
	ACCEPTED,
	NAME_EXIST,
	ID_EXIST,
	NAME_ID_EXIST,
	ADD,
	MODIFY,
	NAME_NOT_EXIST,
	NAME_PASSWORD_NOT_MATCH,
	NEW_CONFIRM_PASSWORD_NOT_MATCH,
	USER_NAME_AND_ID_CHANGE_NOT_PERMITTED,
	MAXIMUM_USERS_ADDED,
	MAX_ACTIVE_USERS = 15,
};

enum LOGIN_RESPONSE
{
	CORRECT_NAME_PASSWORD = 1,
	WRONG_NAME_PASSWORD = 2,
	FIRST_TIME_LOGIN = 10,
	PASSWORD_EXPIRED = 11,
	LOW_AUTHORITY_ERROR = 12,
	MAX_WRONG_ATTEMPTS = 13,
	ALREADY_LOGGED_IN_THROUGH_WEBSERVICES = 14,
	EXECUTIVE_PASSWORD_CHANGE = 15
};

enum STATEMACHINESTATE
{
   STATE_MACH_OFF = 0,
   STATE_MACH_ON  = 1,
};

enum PresetLockStat{
	LOCKED = 8,
	UNLOCKED = 4
};

enum UDISCANSTATUS
{
	UDISCAN_WAITING = 1,
	UDISCAN_RECEIVED,
	UDISCAN_OFF,
};

enum PresetValidStat{
	VALIDATED = 2,
	UNVALIDATED = 1
};

typedef struct Map {
	EDIT_PARAM_TYPE ParameterId;//Added to check which params chnage should cause the preset to go invalid and non verified.
						//Main.GUI can be changed to have same  ID and Struc_ID can be removed from this structure and Map table
	int Struct_ID;
	void *Vptr;
	enum DATA_TYPE DataType;
	UINT16 *Eptr; /* Pointer to flag to see if display line*/
	UINT16 *DisableFlag; /* Pointer to disable/enable flag        */
	void (*Function1)(void); // for those with two void func(void) type functions.(Fuction 1)
	void (*Function2)(void); // for all others (Function2)
	FORMAT UnitFormat;

} MAP;

typedef struct MinMaxMap {
	EDIT_PARAM_TYPE ParameterId;//Added to check which params chnage should cause the preset to go invalid and non verified.
						//Main.GUI can be changed to have same  ID and Struc_ID can be removed from this structure and Map table
	int Struct_ID;
	SINT32 *ptrmin; /* Pointer to minimum value accepted     */
	SINT32 *ptrmax; /* Pointer to maximum value accepted     */
	void (*Function1)(UINT16);
} MINMAXMAP;


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
extern BOOLEAN UserLoggedIn;
extern UDISCANSTATUS VgaUDiStatus;

/*
 -----------------------.---- TYPE DECLARATIONS ---------------------------------
*/                           
extern FRAMUserID FRAMUserIdObj;
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
extern BOOLEAN FirmwareUploadAllowed;
BOOLEAN CheckOperatorAuthority(OpAuth Func);
void RemoteSerialCommandHandler(void);
void ColdStartPlus(void);  
//void SelectAutoPretrig(void);
//void SelectDistPretrig(void);
void SetBucMenuToFactoryDefault(void);
UINT8 VerifyLengthAndCode(SINT16 length, UINT16 code);
UINT16 ProcessUserIdData(UINT8 *, UINT8 *, SINT32);
UINT16 ProcessEventHistoryDataCommand(UINT8*, UINT32, UINT32);
UINT16 ProcessAlarmLogDataCommand(UINT8*, UINT32, UINT32);

UINT16 ProcessHostCommand(UINT32 Value32, UINT16 Function, UINT8 *DataPointer,
		UINT16 CommandCount, UINT8 * AckBuf, SOURCE_TASK_ID_TYPE Source_Task);
UINT16 ProcessVGAHostCommand(UINT32 Value32, UINT16 Function,
		UINT8 *DataPointer, UINT16 CommandCount);
UINT16 XmitNack(IPS_ACTION_ID_TYPE Function, EDIT_PARAM_TYPE Subfunction,
		UINT32 Error, UINT32 Info1, UINT32 Info2, UINT8 *AckBuf);
UINT16 SetArrayData(UINT8 ** to, UINT8 *Value, UINT8 *Arr);


void GetCurrentHWVerify(void);
void CreateDefaultExecutive(void);
BOOLEAN SetupValid();

extern enum OpAuth userOpAuth;
extern enum OpAuth CurrUserOpAuth;
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;
extern BOOLEAN ResetFailed;
extern BOOLEAN ResetAlarmProcessed;
extern UINT16 GlobalCommandID;
extern UINT8 PasswdEntryFlag;
extern BOOLEAN OnboardDiag;
extern STR LineBuffer[LINESIZE +1];
extern BOOLEAN VGAUSBFullFlag;
extern BOOLEAN SBCReadyFlag;
extern UserID CurrentUser;
extern BOOLEAN TempPresetValidated;
extern BOOLEAN TempPresetLocked;
extern UINT16 VGAPresetNum;
extern char AutomationUsrId[11];
extern char UDIString[25];
extern BOOLEAN UDIScanRecived;
extern BOOLEAN CurrentPresetParameterChanged;
extern UINT16 DUPSOverloadType;
extern  const MAP  Map[];
extern  const MINMAXMAP  MinMap[];
extern BOOLEAN StartingSensorCal;
#endif
