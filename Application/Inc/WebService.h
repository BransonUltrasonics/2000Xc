/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/WebService.h_v   1.13   May 25 2017 18:18:30   RJamloki  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/WebService.h_v  $
 * 
 *    Rev 1.13   May 25 2017 18:18:30   RJamloki
 * Update function prototypes
 * 
 *    Rev 1.12   16 Apr 2015 07:36:20   rjamloki
 * DataType fixes as per review comments
 * 
 *    Rev 1.10   09 Apr 2015 04:55:02   RJamloki
 * Removed unused error codes
 * 
 *    Rev 1.9   27 Mar 2015 11:15:08   amaurya
 * MAX_ALARM_PERREQUEST macro added to send 50 alarm data when both From and To fied in the post data is 0.
 * 
 *    Rev 1.8   11 Mar 2015 09:24:34   amaurya
 * MAX_NUMBER_OF_USERIOINDEX macro changed as rejectconfirminput added to userio pin.
 * 
 *    Rev 1.7   30 Jan 2015 08:08:04   amaurya
 * GetPSVersionNum() added to prepare and send version number to JSON Client.
 * 
 *    Rev 1.6   11 Dec 2014 08:33:38   AnPawar
 * GetValAndIncrementBuffer function declaration changed
 * 
 *    Rev 1.5   28 Nov 2014 07:56:58   rjamloki
 * MAX_NUMBER_OF_USERIO and MAX_NUMBER_OF_USERIOINDEX macro added.Three new error codes added to ServiceErrorCode enum.Enum WCSBCCOMMErrorCodes added for internal 
 * check issues between SBC and WC communication
 * 
 *    Rev 1.4   10 Nov 2014 04:43:18   AnPawar
 * changes for web services.
 * 
 *    Rev 1.3   20 Oct 2014 06:41:16   AnPawar
 * changes for web services.
 * 
 *    Rev 1.2   06 Oct 2014 06:50:40   AnPawar
 * ServiceErrorCode enum changed.Function declaration in WebService class changed.
 * 
 *    Rev 1.1   03 Oct 2014 06:29:22   rjamloki
 * New error codes and macros defined
 * 
 *    Rev 1.0   22 Aug 2014 08:06:10   rjamloki
 * Initial revision.
*/


#ifndef WEBSERVICE_H_
#define WEBSERVICE_H_
#include "portable.h"
#include "CyGOS.h"
#include "menu.h"
#include "Events.h"

#define MAX_JSONRESPONSE		90 * 1024
#define MAX_SBC_RESPONSEBUFFLEN  1 * 1024 *1024
#define MAX_EVENTHISTORYPER_REQUEST 50
#define MAX_WELDHISTORYPER_REQUEST  50
#define MAX_ALARM_PERREQUEST		50
#define MAX_USER_PERREQUEST		    50  //Define added for maximum user id can requested from Web service.
#define SBC_CONNECTION_RETRYCOUNT   5
#define SBC_DATA_RETRYCOUNT   		100//makes the total wait one second
#define MAX_EXPECTED_JSONDATA_LEN   5000
#define MAX_NUMBER_OF_USERIO        9
#define MAX_NUMBER_OF_USERIOINDEX   15
#define USERIO_MISSINGPART_ID       9
#define USERIO_PARTPRESENT_ID       13
#define USERIO_CONFIRMREJECT_ID     14
#define MAXBUFFSIZEOFWELDDATA       64

#define JSON_SRCPORT 4000
#define MAXNOOFALARMS    	224       //28*8(8 types of alarms and 1 thru 27 bit of error variable can have alarm)

enum EventLogElementIDs
{
   EVENTLOG_EVENTNUM = 1,
   EVENTLOG_PRESETNO,
   EVENTLOG_REV,
   EVENTLOG_USERID,
   EVENTLOG_EVENTID,
   EVENTLOG_PSSERIALNUMBER,
   EVENTLOG_TS,
   EVENTLOG_EVENTREASON,
   EVENTLOG_EVENTDESCRIPTION,
};

enum UserIdElementIDs
{
   USERID_USERID = 1,
   USERID_PASSWORD,
   USERID_USERLEVEL,
   USERID_STATUS,
   USERID_PASSEXPTIME,
   USERID_ISFIRSTTIMELOGIN,
   USERID_CREATEMODIFYTIME,
};

enum ServiceErrorCode
{
   SUCCESS = 0,
   ALREADY_LOGGED_IN,//1
   NOT_LOGGED_IN,//2
   WRONGNAME_PASSWORD,//3
   FIRSTTIMELOGIN,//4
   PRESET_NOT_VERIFIED,//5
   SYSTEM_BUSY,//6
   EXCEEDS_LIMITS,//7
   MISMATCH_PARAMID,//8
   DATA_NOT_FOUND_IN_SPECIFIEDRANGE,//9
   EXCEEDS_ACTIVEUSER,//10
   EXCEEDS_TOTALUSER,//11
   INVALID_PASSWORD,//12
   LARGENO_OF_DATA_REQUSTED,//13
   USERID_CHANGE_NOT_PERMITTED,//14
   INVALID_SECURITYLEVEL,//15
   PASSWORDEXPIRED,//16
   USEREXIST,//17
   MAXWRONGATTEMPTS,//18
   SBC_CONNECTION_TIMEOUT,//19
   REASON_REQUIRED,//20
   PRESET_NOT_ENABLED,//21
   INVALID_SERVICE_DATA,//22
   INVALID_JSON_FORMAT,//23//All the parsing error as per service
   AUTOMATION_ENABLED,//24
   SBC_DATA_TIMEOUT,//25
   INVALID_USERIO_INPUT, //26
   INVALID_ACTUATOR_FOR_USERIO_INPUT, //27
   AUTHORITY_CHECK_OFF, //28
};

enum TimeOrDateRet
{
	VALID = 1,
	INVALID,
};
enum UserIOIndex {
   ASSIGNED = 1, NOTASSIGNED,
};
enum AlarmElementId
{
	ALARMLOG_ALARMNUM = 1,
	ALARMLOG_CYCLENUM,
	ALARMLOG_PRESETREVNUM,
	ALARMLOG_PRESETNUM,
	ALARMLOG_ALARMID,
	ALARMLOG_USERID,
	ALARMLOG_ACTASSEMBLYID,
	ALARMLOG_PSASSEMBLYID,
	ALARMLOG_TS,
};

//These error codes are used internally between to check issues between SBC and WC communication. We service client
//get the appropriate error code based on these.
enum WCSBCCOMMErrorCodes
{
   COMM_OK = 1,
   CONNECTION_TIMEDOUT = -2,//tcp connection with sbc is failed
   DATA_NOT_IN_SPECIFIEDRANGE = -3,//SBC does not have in the range it was requested
   DATA_REQUEST_TIMEOUT = -4,//no data is received from sbc in specified time out (1 second currently) or request could not be sent to SBC
};

struct JsonPacket
{
	SINT32 FileId;
	SINT32 From;
	SINT32 To;
};

struct JsonSBCDataHandshakepacket
{
	SINT32 TotalExpectedData;
};
struct JsonTempUserId
{
   SINT8 UserId[6];
   SINT8 Password[11];
   enum LEVEL UserLevel;
   enum ActiveStatus Status;
   UINT32 PassExpTime;
};
enum Service
{
	SERVICE_LOGIN = 1,
	SERVICE_LOGOUT,
	SERVICE_SETUSER,
	SERVICE_UPDATEUSER,
	SERVICE_GETUSER,
	SERVICE_SETPRESET,
	SERVICE_GETPRESET,
	SERVICE_SETSYSTEMCONFIG,
	SERVICE_GETSYSTEMCONFIG,
	SERVICE_GETWELDRESULT,
	SERVICE_GETWELDHISTORY,
	SERVICE_GETEVENTHISTORY,
	SERVICE_SAVEPRESET,
	SERVICE_RECALLPRESET,
	SERVICE_VERIFYPRESET,
	SERVICE_GETEVENTCOUNT,
	SERVICE_GETHISTORYCOUNT,
	SERVICE_GETALARMLOG,
	SERVICE_GETUSERCOUNT,
	SERVICE_CLEARPRESET,
	SERVICE_GETALARMCOUNT,
	SERVICE_GETPSVERSIONNUM,
};

typedef SINT8 * (*JsonGetCmdHandler)(ip_addr PeerAddr);
typedef SINT8 * (*JsonSetCmdHandler)(SINT8 * JsonStr);
typedef SINT8 * JsonResponsePtr;
struct JSONGetHandler
{
	SINT8 * ServiceName;
	JsonGetCmdHandler Handler;
};

struct JSONSetHandler
{
	SINT8 * ServiceName;
	JsonSetCmdHandler Handler;
	Service ServiceID;
};

class WebService
{
public:
	static bool JSONHandler(SINT8 * ServiceURI, HTTPReplyHeader & Header, SINT8 * JsonStr, ip_addr PeerAddr, int DataLen);
	static void InitWebService(SINT32 Intf, SINT32 SrvrPort);
	//JSON Handlers for specific service
	static JsonResponsePtr JSONGetHandler(ip_addr PeerAddr);
	//JSON set data handlers for specific service
	static JsonResponsePtr SystemLogin(SINT8 * JsonStr);
	static JsonResponsePtr SystemLogout(SINT8 * JsonStr);
	static JsonResponsePtr GetWeldResult(SINT8 * JsonStr);
	static JsonResponsePtr GetEventHistory(SINT8 * JsonStr);
	static JsonResponsePtr GetWeldHistory(SINT8 * JsonStr);
	static JsonResponsePtr SetPresetValue(SINT8 * JsonStr);
	static JsonResponsePtr GetPresetValue(SINT8 * JsonStr);
	static JsonResponsePtr GetSystemConfigValue(SINT8 * JsonStr);
	static JsonResponsePtr SetSystemConfigValue(SINT8 * JsonStr);
	static JsonResponsePtr JsonRecallPreset(SINT8 * JsonStr);
	static JsonResponsePtr JsonVerifyPreset(SINT8 * JsonStr);
	static JsonResponsePtr SavePreset(SINT8 * JsonStr);
	static JsonResponsePtr GetUsers(SINT8 * JsonStr);
	static JsonResponsePtr SetUser(SINT8 * JsonStr);
	static JsonResponsePtr GetNumEvents(SINT8 * JsonStrr);
	static JsonResponsePtr GetNumWeldData(SINT8 * JsonStr);
	static JsonResponsePtr UpdateUser(SINT8 * JsonStr);
	static JsonResponsePtr GetAlarmLogData(SINT8 * JsonStr);
	static JsonResponsePtr GetUserCount(SINT8 * JsonStr);
	static JsonResponsePtr GetAlarmCount(SINT8 * JsonStr);
	static JsonResponsePtr GetPSVersionNum(SINT8 * JsonStr);
	static JsonResponsePtr AddOrModifyUser(SINT8 * JsonStr,UINT8 Operation);
	static JsonResponsePtr ClearPreset(SINT8 * JsonStr);
	static JsonResponsePtr GetSystemConfigorPresetValue(SINT8 * JsonStr, Service ServiceId);
	static void GetValAndIncrementBuffer(SINT8 ** Buff, SINT32 FindChar,SINT8 *DestinationBuff);
	static ServiceErrorCode CheckRequiredConditions(Service ServiceCode); //SECURITY
	static ServiceErrorCode CheckReasonRequired(Service ServiceCode, PARAM ParamID); // SERVICES NEED A REASON
	static ServiceErrorCode CheckParmeterID(Service ServiceCode, PARAM ParamID); // CHECK PARAMETER SECURITY
	static ServiceErrorCode CheckServiceData(Service ServiceCode); //JSON FORMAT
	static void Tick(int callbackus);
	static void SessionLogOut();
	static UINT8 VerifyUsernamePassword(void);
	static BOOLEAN CheckOperatorAuthority(OpAuth Func);
	static SINT8 ChangeReason[MAX_EVENTREASON_LEN];
	static void SendMinMaxValue(SINT32 ParamId,UINT16 PositionInMap,SINT32 Min,SINT32 Max);
	static SINT32 PostDataLen;
	static SINT8 * PostDataPtr;
	static SINT8 JsonUserID[MAX_USERID_LEN];
	static BOOLEAN JsonUserLoggedIn;
	static BOOLEAN RequestInProgress;
	static SINT32 ResponseLength;
	static UINT32 SessionStarttime;
	static UINT32 SessionChecktime;
	static UINT32 JsessionId;
	static UserID CurrentUser;
	static UINT16 SecurityLevel;
	static enum OpAuth CurrUserOpAuth;
	static void SetDisableFlagStatus(UINT16 *DisableFlagSet,PARAM ParamID);
	static void SetParamValue(UINT16 PositionInMap, UINT32 ReceiveValue);
	static void GetAlarmFromOffset(SINT32 AlarmString,UINT32 AlarmType);
	static SINT32 AlarmArrayIndex;
	static UINT32 AlarmArray[MAXNOOFALARMS];
	static BOOLEAN JsonReadyFlag;
	static SINT32 NumChangeReasonRequiredIDs;
	static SINT32 NumChangeReadonlyIDs;
	static SINT32 CheckUserIOIndex[MAX_NUMBER_OF_USERIO][MAX_NUMBER_OF_USERIOINDEX];
    static SINT32 NumUserIOIDs;
	static UINT32 IdealLogOutTimeForWebClient;
};


extern JSONGetHandler JsonGetCmdHandlers[];
extern JSONSetHandler JsonSetCmdHandlers[];
void InitJsonObjsKeys();
SINT32 CreateTcpSocket();
SINT32 SendTCPRequest(SINT32 FieldId,SINT32 From,SINT32 To);
SINT32 Check_Password(SINT8 *p1);
ServiceErrorCode stringsplit(const SINT8 * string,enum FORMAT format,
		 BOOLEAN Metric, SINT32 * val);
SINT32 CheckTimeValue(const SINT8 * string);
SINT32 CheckDateValue(const SINT8 * string);
BOOLEAN CheckForLeapYear(SINT32 Year);
void SkipSpace(SINT8 *&Source);
#endif /* WEBSERVICE_H_ */

