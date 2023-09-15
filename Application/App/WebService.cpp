/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/WebService.cpp_v   1.35   Oct 10 2017 15:25:22   RJamloki  $*/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/WebService.cpp_v  $
 * 
 *    Rev 1.35   Oct 10 2017 15:25:22   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.34   May 30 2017 16:02:24   RJamloki
 * Added Alarm id 38 to the getweldresult webservice method function
 * 
 *    Rev 1.33   May 25 2017 18:07:44   RJamloki
 * Update several web services fixes including authority checking
 * 
 *    Rev 1.32   12 Sep 2016 17:09:50   RJamloki
 * Remove "FLOWCONTROL" from the JSONReadOnlyIDs[] array
 * 
 *    Rev 1.31   16 Apr 2015 07:30:20   rjamloki
 * DataType and code review fixes
 * 
 *    Rev 1.29   09 Apr 2015 05:31:50   RJamloki
 * Fixed warnings and leap year logic
 * 
 *    Rev 1.28   08 Apr 2015 13:48:12   AnPawar
 * Replace ID_NOT_EXIST with MISMATCH_PARAMID.
 * 
 *    Rev 1.27   03 Apr 2015 07:14:02   amaurya
 * Added SERVICE_GETPSVERSIONNUM service to CheckRequiredCondition() to allow user to get power supply version number when authority check is enabled.
 * 
 *    Rev 1.26   01 Apr 2015 13:03:14   amaurya
 * SERVICE_GETPRESET: added in CheckRequiredConditions()function to get presetparameter values when authority check is enabled for web client request. 
 * 
 *    Rev 1.25   30 Mar 2015 05:13:56   rjamloki
 * CheckRequiredCondition added to GetPresetValue() and GetSystemConfigValue() services.
 * 
 *    Rev 1.24   27 Mar 2015 11:12:06   amaurya
 * GetAlarmLogData() changed to send latest 50 alarm data if Web command come with both From and To field zero.
 * 
 *    Rev 1.23   18 Mar 2015 09:09:16   amaurya
 * GetPSVersionNum() function changed to get SBC version number if retval is greater than zero.
 * 
 *    Rev 1.22   16 Mar 2015 06:11:56   rjamloki
 * Header corrections as per review comments
 * 
 *    Rev 1.21   13 Mar 2015 06:10:08   amaurya
 * SendTCPRequest() changed to fix coverty issue 12558.
 * 
 *    Rev 1.19   28 Feb 2015 21:42:46   rjamloki
 * Checking weldstate before recalling preset.
 * 
 *    Rev 1.18   02 Feb 2015 07:08:46   amaurya
 * Changed "PresestName" string to camel case format.
 * 
 *    Rev 1.17   30 Jan 2015 08:11:30   amaurya
 * JsonRecallPreset() changed to send preset name on success of preset recall.GetPSVersionNum() added to send version number to JSON client.
 * 
 *    Rev 1.16   08 Jan 2015 03:18:30   AnPawar
 * printf removed
 * 
 *    Rev 1.15   02 Jan 2015 04:12:30   rjamloki
 * WebService::SessionLogOut() function changed to secure firmware upload
 * 
 *    Rev 1.14   11 Dec 2014 08:38:10   AnPawar
 * changes to send ps sn and act sn in web services.
 * 
 *    Rev 1.13   28 Nov 2014 07:42:54   rjamloki
 * Changes for UserIO set.
 * 
 *    Rev 1.12   17 Nov 2014 10:00:56   RJamloki
 * Disabled setting Downspeed from web service as it requires calibration.
 * 
 *    Rev 1.11   11 Nov 2014 06:11:44   AnPawar
 * coverity fix in SystemLogin service
 * 
 *    Rev 1.10   10 Nov 2014 11:25:40   RJamloki
 * Added security level check for data transfer web services.
 * 
 *    Rev 1.9   10 Nov 2014 05:00:22   AnPawar
 * changes for web services.
 * 
 *    Rev 1.8   20 Oct 2014 06:33:44   AnPawar
 * changes for web services.
 * 
 *    Rev 1.7   06 Oct 2014 11:52:04   rjamloki
 * Fixes for GetWeldHistory service
 * 
 *    Rev 1.6   06 Oct 2014 06:48:32   AnPawar
 * changes for web services.
 * 
 *    Rev 1.5   03 Oct 2014 06:17:24   rjamloki
 *  New function added GetNumWeldData ,GetNumEvents,Tick.Added EventReason functionality in SetPresetValue() and SetSystemConfigValue()
 * 
 *    Rev 1.4   26 Sep 2014 03:39:50   rjamloki
 * Changes due to operator authority made global
 * 
 *    Rev 1.3   11 Sep 2014 11:11:48   rjamloki
 * Coverity fixes
 * 
 *    Rev 1.2   05 Sep 2014 05:29:58   rjamloki
 * SavePreset tweaked to not use compressed preset
 * 
 *    Rev 1.1   22 Aug 2014 09:22:12   rjamloki
 * Temp Fix for not checking session ID
 * 
 *    Rev 1.0   22 Aug 2014 08:06:44   rjamloki
 * Initial revision.
 */

#include "WebService.h"
#include "portable.h"
#include "CyGOS.h"
#include "command.h"
#include "ALARMS.h"
#include "menu.h"
#include "weld_obj.h"
#include "graphs.h"
#include "menu3.h"
#include "state.h"
#include "param.h"
#include "selctkey.h"
#include "Ethernet.h"
#include "PRSETPRN.H"
#include "menu.h"
#include "limits.h"
#include "util.h"
#include "statedrv.h"
#include "digout.h"
#include "ascii.h"
#include "RTOS.h"
#include "menu1.h"
#include "menu6.h"

#define JSON_IDVALUESEPERATOR  		 ','
#define JSON_STARTOFARRAY           '['
#define JSON_ENDOFARRAY             ']'
#define JSON_STARTOFOBJECT          '{'
#define JSON_ENDOFOBJECT            '}'
#define JSON_OBJECTSEPERATOR        ':'
#define MAX_KEY_SIZE 			5
#define EVENTLOGFIELDID   		1   //FieldId for eventlog to be send to SBC
#define WELDHISTORYFIELDID  	2   //FieldId for weldhistory to be send to SBC
#define REQFOREVENTLOGCOUNT   	3
#define REQFORWELDLOGCOUNT   	4
#define REQFORSBCVERSION   	5

#define MAXTIMECHAR			6
#define MAXDATECHAR			9
#define MINLIMIT_HOUR   	0
#define MINLIMIT_MINUTE 	0
#define MAXLIMIT_HOUR   	23
#define MAXLIMIT_MINUTE 	59
#define CENTURY         	2000
#define LEAPYEARVALUE		29
#define MINLIMIT_MONTH  	1
#define MINLIMIT_DAY    	1
#define MAXLIMIT_MONTH  	12
#define MAX_ASSEM_NUM_SIZE 	12
#define WELDHISTORYMASK 	0XFFCFDFFE

#define MAXALARMBITCHECK     28
#define MAXTYPEOFALARMAVAILABLE 8

#define USERIDSTRLEN      	9
#define SERVICESTRLEN      	8
#define SESSIONIDSTRLEN    	6
#define PASSWORDSTRLEN    	11
#define FROMSTRLEN         	6
#define TOSTRLEN           	4
#define EVENTSTRLEN       	14
#define PARAMIDSTRLEN      	9
#define PARAMARRAYSTRLEN  	13
#define REASONSTRLEN       	10
#define PARAMVALUESTRLEN  	12
#define PRESETNUMSTRLEN   	11
#define PRESETNAMESTRLEN  	13
#define USERLEVELSTRLEN   	11
#define STATUSSTRLEN       	8
#define PASSEXPTIMESTRLEN 	13
#define WELDDATARRSTRLEN 	14

extern UINT8 TimeArr[3];
extern SINT8 CurrUserID[11];
extern SINT8 CurrPassword[11];
extern enum WELDSTATES WeldState;
extern BOOLEAN IsGraphDrawing;
extern SINT32 ReadOnlyTimer;
extern BOOLEAN UserLoggedIn;
extern UserID useridData;
extern SINT32 UserIdIndex;
extern UINT8 DateArr[4];
extern UINT16 GlobalCommandID;
extern UINT16 VGAPresetNum;
extern UINT16 RadioIndex;
extern SINT32 UserIdIndex;
extern SINT8 AssignNamePresetBuffer[MESSAGESIZE];
extern BOOLEAN ReadyFlag;
extern BOOLEAN WindowSetupFlag;
extern DataType Type;
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH + 1];
extern int PasswordExpDays(RTCTime *usr);
extern RTCTime RTCMenu;

BOOLEAN RecallAndVerifyPreset(UINT32 PresetNum);
UINT8 Check_ExistingUserDetails(UINT8, SINT32);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
UINT16 CountActiveParameters(MENU list[]);
WELD_DATA * GetLastWeldResultPtr(void);
UINT32 GetAlarmID(UINT32 AlarmCode, BOOLEAN SetupAlarm);
void GetUnit_Values(SINT8 StrUnit_Value[], UINT16 Param, WELD_DATA * ResPtr);
void SaveNamedPreset(void);
SINT8 * Response;
SINT8 **KeyWeldResult;
SINT8 **KeyEventLog;
SINT8 **KeyUserDetail;
SINT8 **KeyAlarmLog;
BOOLEAN MatcedParamId = FALSE;
SINT32 ClientSocket = -1;
Ethernet *JsonNetif;
SINT8 * SBCResponseBuf;
SINT32 nRecords;
SINT8 *TimeKeyID = "35";
SINT8 *DateKeyID = "36";
SINT8 *PresetNameKeyID = "37";
SINT8 *AlarmKeyID = "38";
SINT8 *GloblaWeldCounterKeyID = "0";
SINT8 JsonParamValueArr[MAXBUFFSIZEOFWELDDATA];
BOOLEAN DataSet = FALSE;

SINT8 WebService::ChangeReason[MAX_EVENTREASON_LEN];
SINT8 WebService::JsonUserID[MAX_USERID_LEN];
SINT32 WebService::PostDataLen = 0;
SINT8 * WebService::PostDataPtr = 0;
BOOLEAN WebService::JsonUserLoggedIn = FALSE;
BOOLEAN WebService::RequestInProgress = FALSE;
SINT32 WebService::ResponseLength = 0;
UINT32 WebService::SessionStarttime = 0;
UINT32 WebService::SessionChecktime = 0;
UINT32 WebService::JsessionId = 0;
SINT32 WebService::AlarmArrayIndex = 0;
UINT32 WebService::AlarmArray[MAXNOOFALARMS];
BOOLEAN WebService::JsonReadyFlag = FALSE;
SINT32 WebService::NumChangeReasonRequiredIDs = 0;
SINT32 WebService::NumChangeReadonlyIDs = 0;
SINT32 WebService::NumUserIOIDs = 0;
UINT32 WebService::IdealLogOutTimeForWebClient = 0;
UserID WebService::CurrentUser;
UINT16 WebService::SecurityLevel = 0;
enum OpAuth WebService::CurrUserOpAuth;

SINT32 JsonFileCount = 0;
void PresetSaveOk(void);
void SetPresetClearFlags(void);
void ProcessPresetClear(void);
SINT8 JSONSBCVersion[SBC_SW_VERSION_LENTGH+1];

//CheckUserIOIndex array keeps the information regarding enabled UserIO bit.There are total 15 bits assigned to each UserIo.Out of 15 bits
//some bits are not assigned to some specific UserIo.In this array ,'ASSIGNED' represents that the corresponding bit(function) can be assigned to that particular userIO.
//'NOTASSIGNED' represents that the corresponding bit(function) can not be assigned to that particular userIO.
SINT32 WebService::CheckUserIOIndex[MAX_NUMBER_OF_USERIO][MAX_NUMBER_OF_USERIOINDEX] =
      { {ASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,NOTASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED},
        {ASSIGNED,ASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED},
        {ASSIGNED,ASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED},
        {ASSIGNED,ASSIGNED,NOTASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,ASSIGNED,NOTASSIGNED,NOTASSIGNED}};

//The parameters which require change reason if get changed from JSON
PARAM ChangeReasonRequiredIDs[] = { STACKASSEMBLYNUM, ACTASSEMBLYNUM, PSASSEMBLYNUM, TIMEDATA, DATEDATA, AUTOMATION,
      HWVERIFY, OPERATORAUTH };

//The parameters which are not allowed to changed from JSON
PARAM JSONDisabledIDs[] = { ACTIVEPRESET, SEQUENCELIST, SEQUENCENOS, SEQUENCEENABLE, ACT_COLD_START, WELD_CYCLE_COUNT,
      PSTYPE, WELDPARAMOPTION0, WELDPARAMOPTION1, WELDPARAMOPTION2, WELDPARAMOPTION3, WELDPARAMOPTION4,
      ACTLIFETIMECOUNTER, HORNDOWNSPD,PLCCONTROLFLAG,USERIDTABLE };

//The parameters which are only read only from JSON
PARAM JSONReadOnlyIDs[] = { ACTSERIALNUMBER, PSSERIALNUMBER,VALIDATEPS , LOCKPS ,PSFREQUENCY };

//The User IO parameters
PARAM UserIOParamIDs[] = { J3_32_IN,J3_33_IN,J3_19_IN,J3_17_IN ,J3_31_IN,J3_1_IN,J3_8_OUT,J3_36_OUT,J3_22_OUT};


//Array of GET service name and corresponding handler
JSONGetHandler JsonGetCmdHandlers[] = { { "/GetSunriseData", WebService::JSONGetHandler }, { 0, 0 } };

//Array of POST service name and corresponding handler
JSONSetHandler JsonSetCmdHandlers[] = {
   { "/SystemLogin", WebService::SystemLogin, SERVICE_LOGIN },
   { "/SystemLogout", WebService::SystemLogout, SERVICE_LOGOUT },
   { "/GetWeldResult", WebService::GetWeldResult, SERVICE_GETWELDRESULT },
   { "/GetEventHistory", WebService::GetEventHistory, SERVICE_GETEVENTHISTORY },
   { "/GetWeldHistory", WebService::GetWeldHistory, SERVICE_GETWELDHISTORY },
   { "/SetPresetValue", WebService::SetPresetValue, SERVICE_SETPRESET },
   { "/SetSystemConfigValue", WebService::SetSystemConfigValue, SERVICE_SETSYSTEMCONFIG },
   { "/GetPresetValue", WebService::GetPresetValue, SERVICE_GETPRESET },
   { "/GetSystemConfigValue", WebService::GetSystemConfigValue, SERVICE_GETSYSTEMCONFIG },
   { "/RecallPreset", WebService::JsonRecallPreset, SERVICE_RECALLPRESET },
   { "/VerifyPreset", WebService::JsonVerifyPreset, SERVICE_VERIFYPRESET },
   { "/SavePreset", WebService::SavePreset, SERVICE_SAVEPRESET },
   { "/GetUsers", WebService::GetUsers, SERVICE_GETUSER },
   { "/SetUser", WebService::SetUser, SERVICE_SETUSER },
   { "/GetNumEvents", WebService::GetNumEvents, SERVICE_GETEVENTCOUNT },
   { "/GetNumWeldData", WebService::GetNumWeldData, SERVICE_GETHISTORYCOUNT },
   { "/UpdateUser", WebService::UpdateUser, SERVICE_UPDATEUSER },
   { "/GetAlarmLogData", WebService::GetAlarmLogData, SERVICE_GETALARMLOG },
   { "/GetUserCount", WebService::GetUserCount, SERVICE_GETUSERCOUNT },
   { "/ClearPreset", WebService::ClearPreset, SERVICE_CLEARPRESET },
   { "/GetNumAlarms", WebService::GetAlarmCount, SERVICE_GETALARMCOUNT },
   { "/GetPSVersionNum", WebService::GetPSVersionNum, SERVICE_GETPSVERSIONNUM },
   { 0, 0, (Service) 0 },
};

/* void WebService::InitWebService(SINT32 Intf, SINT32 SrvrPort)
 *
 *  Purpose:
 *    This function assigns the handler functions for JSON.This Function should be called once at powerup.
 *
 *  Entry condition: Intf- The index of Ethernet module of processor
 *                   SrvrPort-The HTTP port this website belongs to.
 *
 *  Exit condition: None.
 */
void WebService::InitWebService(SINT32 Intf, SINT32 SrvrPort)
{
   JsonNetif = CyGOS::GetNetworkInterface(Intf);
   ASSERT(JsonNetif);
   //Add JSON handler
   CyGOS::AddJSONHandler(Intf, SrvrPort, JSONHandler);
   //Add timer callback for webservice sessiond
   CyGOS::AddTickCallbackForWebSite(Intf, SrvrPort, Tick);
   Response = new SINT8[MAX_JSONRESPONSE];   //100K response buffer
   SBCResponseBuf = new SINT8[MAX_SBC_RESPONSEBUFFLEN];
   ChangeReason[0] = 0;
   JsonUserID[0] = 0;
   InitJsonObjsKeys();
   NumChangeReasonRequiredIDs = sizeof(ChangeReasonRequiredIDs) / sizeof(ChangeReasonRequiredIDs[0]);
   NumChangeReadonlyIDs = sizeof(JSONDisabledIDs) / sizeof(JSONDisabledIDs[0]);
   CountActiveParameters((MENU*) RunScreenParamMenu);
   NumUserIOIDs = sizeof(UserIOParamIDs) / sizeof(UserIOParamIDs[0]);
}

/* JsonResponsePtr WebService::JSONGetHandler()
 * Purpose:
 * This is a handler function for Services using GET http command. Get Services are currently
 * unused for Sunrise
 *  Entry condition:
 *		PeerAddr : Address of the Client requesting data through JSON URI
 *  Exit condition:
 *    The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::JSONGetHandler(ip_addr PeerAddr)
{
   memset(&PeerAddr, 0, sizeof(ip_addr));
   strcpy(Response, "[\"Notfound\" , \"Notfound\"]");
   return Response;
}

/*bool  WebService::JSONHandler(SINT8 * ServiceURI, HTTPReplyHeader & Header, SINT8 * JsonStr, ip_addr PeerAddr)
 * Purpose:
 * 		JSON Handler callback. Function is called when JSON URI is received by the server.
 *  Entry condition:
 *		ServiceURI- The JSON URI based on which different services will be invoked.
 *		Header- Object which will be filled with the response length,response type etc.
 *		JsonStr- Pointer to the data sent with JSON URI i case of POST request
 *		PeerAddr- Address of the Client requesting/posting data through JSON URI
 *		DataLen - length of the received post data.
 *  Exit condition:
 *      Returns TRUE in case of valid request otherwise returns FALSE
 */
bool WebService::JSONHandler(SINT8 * ServiceURI, HTTPReplyHeader & Header, SINT8 * JsonStr, ip_addr PeerAddr,
      int DataLen)
{
   BOOLEAN RetVal = TRUE;
   BOOLEAN HandlerFound = FALSE;
   SINT32 Indx = 0;
   SINT8 * ServiceName = 0;
   Service ServiceID;
   JsessionId = 0;
   ServiceErrorCode ErrorCode;
   ResponseLength = 0;
   if ((CurrentSetup.ControlLevel >= LEVEL_c) && !WindowSetupFlag) { //check if lavel c and not window setup
      ServiceName = strstr(ServiceURI, "Services");
      if (ServiceName) ServiceName = ServiceName + SERVICESTRLEN;
      Header.contentType = typeJSON;
      sprintf(Response, "{\"ErrorCode\":%d}", NOT_LOGGED_IN);
      Header.data = Response;
      if (JsonStr) { // if no json data goto json no page found
         while ((JsonSetCmdHandlers[Indx].ServiceName != 0) && (HandlerFound == FALSE)) {
            if (stricmp(JsonSetCmdHandlers[Indx].ServiceName, ServiceName) == 0) {
               PostDataLen = DataLen; //post data size
               PostDataPtr = JsonStr; // pos jason string data
               ServiceID = JsonSetCmdHandlers[Indx].ServiceID; // get the enum id services
               // this function check if the service id has a valid json format for example login, logout, etc.
               ErrorCode = CheckServiceData(JsonSetCmdHandlers[Indx].ServiceID); //check the json service enum id
               // if no json error continue
               if (ErrorCode == SUCCESS)
               {
            	  RequestInProgress = TRUE;
                  if(CurrentSetup.WebServiceAutorityCheck == TRUE)
                  {
                  	  if (CurrentSetup.AuthorityCheck == FALSE)
                  	  {
                		  sprintf(Response, "{\"ErrorCode\":%d}", AUTHORITY_CHECK_OFF);
                  	  }
                  	  else if (ServiceID != SERVICE_LOGIN)
                  	  {
                  		  if ((JsessionId == 0) || (SessionStarttime == 0))   //Authority check toggled from Menu requires login from webservice
                  		  {
                  			  sprintf(Response, "{\"ErrorCode\":%d}", NOT_LOGGED_IN); // not login or session time expired
                  		  }
                  		  else if ((SessionStarttime == JsessionId) && ((ReadOnlyTimer - SessionChecktime)<=WebService::IdealLogOutTimeForWebClient ))
                  		  {
                  			  SessionChecktime = ReadOnlyTimer;   //first take readonlytimer in temp
                  			  Header.data = JsonSetCmdHandlers[Indx].Handler(JsonStr); //run service function
                  		  }
                  	  }
                  	  else //login services function
                  	  {
                  		  Header.data = JsonSetCmdHandlers[Indx].Handler(JsonStr); //run login service function parameter the json data to the function
                  	  }
                  }
                  else // no autority check
                  {
                	  if (ServiceID == SERVICE_LOGIN)
                	  {
                		  sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%d}", SUCCESS, "Sid", 0); //{"ErrorCode":0,"Sid",0} not login
                	  }
              		  else if (ServiceID == SERVICE_LOGOUT)
              		  {
              		    sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode); //{"ErrorCode":0} not logout
              		  }
                	  else
                	  {
                		  Header.data = JsonSetCmdHandlers[Indx].Handler(JsonStr);
                	  }
                  }
               }
               else //if error send the error code by json format
               {
                  sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode);
               }
               Header.statusCode = httpOk;
               RequestInProgress = FALSE;
               RetVal = HandlerFound = TRUE;
            }
            Indx++;
         }
      }
      else {
         while ((JsonGetCmdHandlers[Indx].ServiceName != 0) && (HandlerFound == FALSE)) {
            if (stricmp(JsonGetCmdHandlers[Indx].ServiceName, ServiceName) == 0) {
               Header.data = JsonGetCmdHandlers[Indx].Handler(PeerAddr);
               Header.statusCode = httpOk;
               RetVal = HandlerFound = TRUE;
            }
            Indx++;
         }        
      }
	  RetVal = HandlerFound;
      if (ResponseLength > 0)
         Header.contentLength = ResponseLength;
      else
         Header.contentLength = strlen(Header.data);

   }
   else
   {
      RetVal = FALSE;
   }
   ChangeReason[0] = 0;
   WebService::IdealLogOutTimeForWebClient  = CurrentSetup.IdleLogoutTime* 60 * 1000;
   return RetVal;
}

/* void InitJsonObjsKeys()
 * Purpose:
 * This Function is called by InitWebService() to initialize the JsonObject KeyId.
 * It is used to create object for CycleNumber JSONObjectType.
 *  Entry condition:
 *		None
 *  Exit condition:
 *      None
 */
void InitJsonObjsKeys()
{
   SINT32 WeldResult_Count = ACTSERIALNUMPARAM + 1;
   SINT32 EventLog_Count = EVENTLOG_EVENTDESCRIPTION + 1;
   SINT32 UserIdDetail_Count = USERID_CREATEMODIFYTIME + 1;
   SINT32 Alarm_Count = ALARMLOG_TS + 1;
   SINT32 I, J;
   KeyWeldResult = new SINT8*[WeldResult_Count];
   for (I = 0; I < WeldResult_Count; ++I)
      KeyWeldResult[I] = new SINT8[MAX_KEY_SIZE];

   KeyEventLog = new SINT8*[EventLog_Count];
   for (I = 0; I < WeldResult_Count; ++I)
      KeyEventLog[I] = new SINT8[MAX_KEY_SIZE];

   KeyUserDetail = new SINT8*[UserIdDetail_Count];
   for (I = 0; I < UserIdDetail_Count; ++I)
      KeyUserDetail[I] = new SINT8[MAX_KEY_SIZE];
   KeyAlarmLog = new SINT8*[Alarm_Count];
   for (I = 0; I < Alarm_Count; ++I)
      KeyAlarmLog[I] = new SINT8[MAX_KEY_SIZE];

   for (J = RCYCLECOUNT; J <= ACTSERIALNUMPARAM; J++) {
      sprintf(KeyWeldResult[J], "%ld", J);
   }
   for (J = EVENTLOG_EVENTNUM; J <= EVENTLOG_EVENTDESCRIPTION; J++) {
      sprintf(KeyEventLog[J], "%ld", J);
   }
   for (J = USERID_USERID; J <= USERID_CREATEMODIFYTIME; J++) {
      sprintf(KeyUserDetail[J], "%ld", J);
   }
   for (J = ALARMLOG_ALARMNUM; J <= ALARMLOG_TS; J++) {
      sprintf(KeyAlarmLog[J], "%ld", J);
   }
}

/*
 * Function verifies the JSON syntax and do some preliminary error checking before the WebService request is sent
 * to its handler function
 */
ServiceErrorCode WebService::CheckServiceData(Service ServiceCode)
{
   ServiceErrorCode ErrorCode = INVALID_JSON_FORMAT;
   SINT8 * Sid = PostDataPtr, *JsonStr = PostDataPtr;
   SINT32 TempLen = PostDataLen;
   //TODO:Serveice Data should be parsed here to be in valid JSON format
   if (PostDataLen > MAX_EXPECTED_JSONDATA_LEN) {
      ErrorCode = INVALID_JSON_FORMAT;   //No need to Trap in parsing invalid requests
   }
   else {
      SkipSpace(JsonStr);
      ErrorCode = SUCCESS;
      //Check valid JSON syntax here
      if (JsonStr[0] != JSON_STARTOFOBJECT || (PostDataPtr[PostDataLen - 1] != JSON_ENDOFOBJECT)) //check for valid jason format
         ErrorCode = INVALID_JSON_FORMAT; // error no json
      else if (ServiceCode != SERVICE_LOGIN) { //get the session id from json format
         Sid = strnstr(JsonStr, "\"Sid\":", TempLen);
         if (Sid) {
            Sid += SESSIONIDSTRLEN;
            SkipSpace(Sid);
            JsessionId = atoi(Sid);
         }
         else
            ErrorCode = INVALID_JSON_FORMAT; // if no id invalid json
      }
      TempLen = PostDataLen - (Sid - PostDataPtr);
      JsonStr = Sid;
      //
      if (ErrorCode == SUCCESS) { // all ok continue no error
         switch (ServiceCode) {
         case SERVICE_LOGIN: //check if valid json for login
            if (!strnstr(JsonStr, "\"UserId\":", TempLen))
            {
            	ErrorCode = INVALID_JSON_FORMAT;
            }
            else if (!strnstr(JsonStr, "\"Password\":", TempLen))
            {
            	ErrorCode = INVALID_JSON_FORMAT;
            }
            break;
         case SERVICE_LOGOUT: // login only sid needed
            break;
         case SERVICE_SETUSER:
            if (!strnstr(JsonStr, "\"UserId\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"Password\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"UserLevel\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"Status\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"PassExpTime\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"UserLevel\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"Status\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PassExpTime\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_UPDATEUSER:
            if (!strnstr(JsonStr, "\"UserId\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"Password\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"UserLevel\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"Status\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"PassExpTime\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"UserLevel\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"Status\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PassExpTime\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETUSER:
            if (!strnstr(JsonStr, "\"From\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"To\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"From\":\"", TempLen))
              ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"To\":\"", TempLen))
              ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_SETPRESET:
            if (!strnstr(JsonStr, "\"ParamId\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"ParamValue\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"ParamId\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETSYSTEMCONFIG:
            if (!strnstr(JsonStr, "\"ParamId\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"ParamId\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETPRESET:
            if (!strnstr(JsonStr, "\"ParamId\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"ParamId\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_SETSYSTEMCONFIG:
            if (!strnstr(JsonStr, "\"ParamId\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"ParamValue\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"ParamId\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETWELDRESULT:
            break;
         case SERVICE_GETWELDHISTORY:
            if (!strnstr(JsonStr, "\"From\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"To\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"From\":\"", TempLen))
              ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"To\":\"", TempLen))
              ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETEVENTHISTORY:
            if (!strnstr(JsonStr, "\"From\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"To\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"From\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"To\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_SAVEPRESET:
            if (!strnstr(JsonStr, "\"PresetNum\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PresetNum\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_RECALLPRESET:
            if (!strnstr(JsonStr, "\"PresetNum\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PresetNum\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_VERIFYPRESET:
            if (!strnstr(JsonStr, "\"PresetNum\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PresetNum\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_GETEVENTCOUNT:
         case SERVICE_GETHISTORYCOUNT:
         case SERVICE_GETALARMCOUNT:
         case SERVICE_GETUSERCOUNT:
         case SERVICE_GETPSVERSIONNUM:
            break;
         case SERVICE_GETALARMLOG:
            if (!strnstr(JsonStr, "\"From\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (!strnstr(JsonStr, "\"To\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"From\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"To\":\"", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            break;
         case SERVICE_CLEARPRESET:
            if (!strnstr(JsonStr, "\"PresetNum\":", TempLen))
               ErrorCode = INVALID_JSON_FORMAT;
            else if (strnstr(JsonStr, "\"PresetNum\":\"", TempLen)) ErrorCode = INVALID_JSON_FORMAT;
            break;
         }
      }
   }
   return ErrorCode;
}

/*
 * Function checks for required authority to set or receive any parameter through webservice
 */
ServiceErrorCode WebService::CheckRequiredConditions(Service ServiceCode)
{
   ServiceErrorCode ErroCode = SUCCESS;
   //
   if (CurrentSetup.WebServiceAutorityCheck == TRUE)
   {
   	   if (CurrentSetup.AuthorityCheck == TRUE)
   	   {
   		   switch (ServiceCode) {
   		   case SERVICE_SETUSER:
   		   case SERVICE_UPDATEUSER:
   		   case SERVICE_GETUSER:
   		   case SERVICE_GETUSERCOUNT:
   			   if ((WebService::SecurityLevel != BRANSON) && (WebService::SecurityLevel != EXECUTIVE))
   			   {
   				   ErroCode = INVALID_SECURITYLEVEL;
   			   }
   			   break;
   		   case SERVICE_SETPRESET:
   		   case SERVICE_SAVEPRESET:
   		   case SERVICE_SETSYSTEMCONFIG:
   		   case SERVICE_VERIFYPRESET:
   		   case SERVICE_GETSYSTEMCONFIG:
   			   if (WebService::SecurityLevel == OPERATOR)
   			   {
   				   ErroCode = INVALID_SECURITYLEVEL;
   			   }
   			   break;
   		   case SERVICE_RECALLPRESET:
   		   case SERVICE_CLEARPRESET:
   			   if (!WebService::CheckOperatorAuthority(RecalPreset))
   			   {
   				   ErroCode = INVALID_SECURITYLEVEL;
   			   }
   			   break;
   		   case SERVICE_GETWELDHISTORY:
   		   case SERVICE_GETEVENTHISTORY:
   		   case SERVICE_GETEVENTCOUNT:
   		   case SERVICE_GETHISTORYCOUNT:
   			   if (WebService::SecurityLevel < SUPERVISOR)
   			   {
   				   ErroCode = INVALID_SECURITYLEVEL;
   			   }
   			   break;
   		   case SERVICE_GETPRESET:
   		   case SERVICE_GETPSVERSIONNUM:
   			   ErroCode = SUCCESS;
   			   break;
   		   default:
   			   ErroCode = INVALID_SERVICE_DATA;
   			   break;
   		   }
   	   }
   }
   //
   if (CurrentSetup.WebServiceAutomation == TRUE)
   {
	   if (CurrentSetup.Automation == TRUE)
	   {
		   switch (ServiceCode) {
		   case SERVICE_SETSYSTEMCONFIG:
		   case SERVICE_SAVEPRESET:
		   case SERVICE_VERIFYPRESET:
		   case SERVICE_SETUSER:
		   case SERVICE_UPDATEUSER:
		   case SERVICE_RECALLPRESET:
		   case SERVICE_CLEARPRESET:
		   case SERVICE_GETUSER:
		   case SERVICE_SETPRESET:
		   case SERVICE_GETPRESET:
			   ErroCode = AUTOMATION_ENABLED;
			   break;
		   default:
			   break;
		   }
	   }
   }
   //
   return ErroCode;
}

/*
 * Function checks for param ids or service require event reason
 */
ServiceErrorCode WebService::CheckReasonRequired(Service ServiceCode, PARAM ParamID)
{
   UINT16 Indx;
   ServiceErrorCode ErroCode = SUCCESS;
   switch (ServiceCode) {
   case SERVICE_SETPRESET:
     if ((CurrentPreset.Validated == TRUE) && (SetupValid() == FALSE))
    	  ErroCode = REASON_REQUIRED;
      break;
   case SERVICE_SETSYSTEMCONFIG:
      for (Indx = 0; Indx < NumChangeReasonRequiredIDs; Indx++) {
         if (ChangeReasonRequiredIDs[Indx] == ParamID) {
            ErroCode = REASON_REQUIRED;
            break;
         }
      }
      break;
   case SERVICE_SETUSER:
   case SERVICE_UPDATEUSER:
      ErroCode = REASON_REQUIRED;
      break;
   default:
      ErroCode = INVALID_SERVICE_DATA;
      break;
   }

   return ErroCode;
}

/*
 * Function checks whether the requested parameter ID is available for service.
 */
ServiceErrorCode WebService::CheckParmeterID(Service ServiceCode, PARAM ParamID)
{
   UINT16 Indx;
   ServiceErrorCode ErroCode = SUCCESS;
   for (Indx = 0; Indx < NumChangeReadonlyIDs; Indx++) {
      if (JSONDisabledIDs[Indx] == ParamID) {
         ErroCode = MISMATCH_PARAMID;
         break;
      }
   }

   if (ErroCode == SUCCESS) {
      switch (ServiceCode) {
      case SERVICE_SETPRESET:
         if ((ParamID >= PRSTPARMDEFID) || (ParamID < ABAMP))
            ErroCode = MISMATCH_PARAMID;
         else {
            for (Indx = 0; Indx < (sizeof(JSONReadOnlyIDs) / sizeof(JSONReadOnlyIDs[0])); Indx++) {
               if (JSONReadOnlyIDs[Indx] == ParamID) {
                  ErroCode = MISMATCH_PARAMID;
                  break;
               }
            }
         }
         break;
      case SERVICE_GETPRESET:
         if ((ParamID >= PRSTPARMDEFID) || (ParamID < ABAMP)) ErroCode = MISMATCH_PARAMID;
         break;
      case SERVICE_SETSYSTEMCONFIG:
         if ((ParamID < ACTIVEPRESET) || (ParamID > OPERATORAUTH))
            ErroCode = MISMATCH_PARAMID;
         else if (ParamID == J3_32_IN || ParamID == J3_33_IN || ParamID == J3_19_IN || ParamID == J3_17_IN
               || ParamID == J3_31_IN || ParamID == J3_1_IN || ParamID == J3_8_OUT || ParamID == J3_36_OUT
               || ParamID == J3_22_OUT) {
            if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE)) ErroCode = SYSTEM_BUSY;
         }
         //These two parameter changes are only allowed with right user levels
         else if ((ParamID == AUTHORITYCHECK) || (ParamID == AUTOMATION)) {
            if (!((JsonUserLoggedIn == TRUE) && (WebService::CurrentUser.UserLevel >= SUPERVISOR))) ErroCode = INVALID_SECURITYLEVEL;
         }
         else {
            for (Indx = 0; Indx < (sizeof(JSONReadOnlyIDs) / sizeof(JSONReadOnlyIDs[0])); Indx++) {
               if (JSONReadOnlyIDs[Indx] == ParamID) {
                  ErroCode = MISMATCH_PARAMID;
                  break;
               }
            }
         }
         break;
      case SERVICE_GETSYSTEMCONFIG:
         if ((ParamID < ACTIVEPRESET) || (ParamID > OPERATORAUTH)) ErroCode = MISMATCH_PARAMID;
         break;
      default:
         ErroCode = INVALID_SERVICE_DATA;
         break;
      }
   }
   return ErroCode;
}

/* JsonResponsePtr WebService::SystemLogin(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "SystemLogin" received from the client.
 * It is used to split the post dat for Systemlogin URI and
 * return status response by comparing the user name and PassWord
 * with the current username and PassWord.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SystemLogin(SINT8 * JsonStr)
{
   SINT8* JsonUserId = 0;
   SINT8* JsonPassword = 0;
   SINT8* Temp = 0;
   SINT8 *Temp2 = 0;
   SINT32 Id = 0;
   ServiceErrorCode ErrorCode = INVALID_SERVICE_DATA;
   //if (UserLoggedIn == FALSE) {
   if (JsonUserLoggedIn == FALSE) {
	  JsonUserId = strstr(JsonStr, "UserId\":\"");
      if (JsonUserId) {
         JsonUserId += USERIDSTRLEN;
         SkipSpace(JsonUserId);
         Temp = strnchr(JsonUserId, '"', PostDataLen - (JsonUserId - PostDataPtr));
         if (Temp) {
            Temp2 = Temp + 1;
            *Temp = '\0';
            strncpy(WebService::JsonUserID, JsonUserId, sizeof(WebService::JsonUserID) - 1);
            JsonPassword = strstr(Temp2, "Password\":\"");
            if (JsonPassword) {
               JsonPassword += PASSWORDSTRLEN;
               SkipSpace(JsonPassword);
               Temp = strnchr(JsonPassword, '"', PostDataLen - (JsonPassword - PostDataPtr));
               if (Temp) {
                  *Temp = '\0';
                  strncpy(CurrPassword, JsonPassword, sizeof(CurrPassword) - 1);
                  ErrorCode = SUCCESS;
               }
               else
                  ErrorCode = INVALID_SERVICE_DATA;
            }
         }
         else
            ErrorCode = INVALID_SERVICE_DATA;
      }
      if (ErrorCode == SUCCESS) {
         strncpy(CurrUserID, WebService::JsonUserID, sizeof(WebService::JsonUserID) - 1);
         Id = WebService::VerifyUsernamePassword();

         if (Id != CORRECT_NAME_PASSWORD) {
            CurrUserID[0] = WebService::JsonUserID[0] = 0;
            if (Id == FIRST_TIME_LOGIN)
               sprintf(Response, "{\"ErrorCode\":%d}", FIRSTTIMELOGIN);
            else if (Id == MAX_WRONG_ATTEMPTS)
               sprintf(Response, "{\"ErrorCode\":%d}", MAXWRONGATTEMPTS);
            else if (Id == LOW_AUTHORITY_ERROR)
               sprintf(Response, "{\"ErrorCode\":%d}", INVALID_SECURITYLEVEL);
            else if (Id == WRONG_NAME_PASSWORD)
               sprintf(Response, "{\"ErrorCode\":%d}", WRONGNAME_PASSWORD);
            else if (Id == PASSWORD_EXPIRED) sprintf(Response, "{\"ErrorCode\":%d}", PASSWORDEXPIRED);
         }
         else {
            SessionStarttime = SessionChecktime = ReadOnlyTimer;
            JsonUserLoggedIn = TRUE;
            sprintf(Response, "{\"ErrorCode\":%d,"
                  "\"%s\":%ld}", SUCCESS, "Sid", SessionStarttime);
         }
      }
      else
         sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode);
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ALREADY_LOGGED_IN);

   return Response;
}

/*JsonResponsePtr WebService::SystemLogout(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "SystemLogout" received from the client.
 * It is used to split the post data for SystemLogout Url and
 * return ErrorCode response by comparing the user name and Password
 * with the current user name and Password.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SystemLogout(SINT8 * JsonStr)
{
   //if ((SessionStarttime == JsessionId) && UserLoggedIn && JsonUserLoggedIn) {
   if ((SessionStarttime == JsessionId) && (JsonUserLoggedIn == TRUE)) {
      RecordEvents(EVENT_USERLOGOUT, WebService::CurrentUser.UserId, "");
      sprintf(Response, "{\"ErrorCode\":%d,\"UserId\":%s}", SUCCESS, WebService::CurrentUser.UserId);
      WebService::SessionLogOut();
   }
   else
      sprintf(Response, "{\"ErrorCode\": %d}", NOT_LOGGED_IN);
   JsonStr = 0;
   return Response;
}

/**void WebService::SessionLogOut()
 * Purpose:
 * This function is called ,when userLogOut command received from webservice client or if Session expires for the logged in user .
 * it is used to reset the SessionStartTime,JessionId etc.
 * Entry condition:
 *	None
 *  Exit condition:
 *  None
 *   */
void WebService::SessionLogOut()
{
   WebService::JsonUserID[0] = 0;
   SessionStarttime = 0;
   JsessionId = 0;
   JsonUserLoggedIn = FALSE;
}

/*JsonResponsePtr WebService::GetWeldResult(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "GetWeldResult" received from the client.
 * It is used to write Weld Result data in the response buffer after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetWeldResult(SINT8 * JsonStr)
{
   WELD_DATA WebLastWeld;
   SINT8 Str[VGA_LINESIZE];
   STR *StrTemp;
   SINT8 StrParam[LINELEN * 2];

   SINT16 CircularIndexCrt= 0;
   UINT16 AlarmIDCrt = 0;

   WebLastWeld = *(GetLastWeldResultPtr());

   sprintf(Response, "{\"%s\":%d", "ErrorCode", SUCCESS);

   //Note order of enums in enum RUN_PARAM in menu.h shall be maintained as it is. These eneums represent the
   //ids of parameters we send in weld history.
   for (SINT32 Index1 = 0; Index1 <= RHOLDFORCEMAX; Index1++) {
      if ((1 << Index1) & WELDHISTORYMASK) {
         GetUnit_Values(Str, (UINT16) (Index1), &WebLastWeld);

         if (Str[0] == 0)
            sprintf(Response + strlen(Response), ",\"%s\":\"%s\"", KeyWeldResult[Index1], "---");
         else {
            Str[LINESIZE] = 0;
            StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
            strncpy(StrParam, StrTemp, sizeof(StrParam) - 1);//Coverity 12245

            if ((Index1 == RPRESETVALIDATED) || (Index1 == RACTASSEMBLYNUM) || (Index1 == RPSASSEMBLYNUM)
                  || (Index1 == RSTACKASSEMBLYNUM) || (Index1 == RUSERID) || (Index1 == RUDISCAN)
                  || (Index1 == RFREQCHG))
               sprintf(Response + strlen(Response), ",\"%s\":\"%s\"", KeyWeldResult[Index1], StrParam);
            else
               sprintf(Response + strlen(Response), ",\"%s\":%s", KeyWeldResult[Index1], StrParam);
         }
      }
   }

   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC)) {
      FormatVariables(WebLastWeld.TrigForce, FORCE, Str, LINESIZE, CurrentSetup.Units);   // Trigger Force
      Str[LINESIZE] = 0;
      StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
      strncpy(StrParam, StrTemp, sizeof(StrParam) - 1);
      sprintf(Response + strlen(Response), ",\"%s\":%s", KeyWeldResult[TRIGFORCEPARAM], StrParam);
   }

   sprintf(Response + strlen(Response), ",\"%s\":\"%s\"", KeyWeldResult[PSSERIALNUMPARAM], WebLastWeld.PsSerialNum);
   sprintf(Response + strlen(Response), ",\"%s\":\"%s\"", KeyWeldResult[ACTSERIALNUMPARAM], WebLastWeld.ActSerialNum);
   sprintf(Response + strlen(Response), ",\"%s\":\"%02d:%02d:%02d\"", TimeKeyID, WebLastWeld.CycleTime.hour,
         WebLastWeld.CycleTime.minute, WebLastWeld.CycleTime.second);
   if (CurrentSetup.Units == TRUE)
      sprintf(Response + strlen(Response), ",\"%s\":\"%02d-%02d-%02d\"", DateKeyID, WebLastWeld.CycleDate.day,
            WebLastWeld.CycleDate.month, WebLastWeld.CycleDate.year);
   else
      sprintf(Response + strlen(Response), ",\"%s\":\"%02d-%02d-%02d\"", DateKeyID, WebLastWeld.CycleDate.month,
            WebLastWeld.CycleDate.day, WebLastWeld.CycleDate.year);
   sprintf(Response + strlen(Response), ",\"%s\":\"%s\"", PresetNameKeyID, WebLastWeld.PresetName);

   if(CheckForAlarms() == TRUE)
   {
	  CircularIndexCrt=FRAMAlarmLogObj.CircularIndex;
	  if(CircularIndexCrt>=0)
	  {
		  AlarmIDCrt = FRAMAlarmLogObj.AlarmLogObjs[CircularIndexCrt].AlarmID;
          sprintf(Response + strlen(Response), ",\"%s\":\"%X\"", AlarmKeyID, AlarmIDCrt);
	  }
   }

   strcat(Response, "}");
   JsonStr = 0;
   return Response;
}

/*JsonResponsePtr WebService::GetNumEvents(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetNumEvents" received from the client.
 * It is used to get total number of events available in the Event.log file present in
 * the SBC Disk and returns the same  in the response buffer after user authentication.
 * WC will send the Field Id = REQFOREVENTLOGCOUNT ,in order to request to get total
 * number of events available in the event log file.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetNumEvents(SINT8 * JsonStr)
{
   SINT32 RetVal = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETEVENTCOUNT);
   if (ErroCode == SUCCESS) {
      RetVal = SendTCPRequest(REQFOREVENTLOGCOUNT, 0, 0);
      if (RetVal > 0)
         sprintf(Response, "{\"ErrorCode\":%d,\"TotalEventPresent\":%ld}", SUCCESS, JsonFileCount);   //JsonFileCount
      else
      {
         if(RetVal == DATA_REQUEST_TIMEOUT)
            sprintf(Response, "{\"ErrorCode\": %d}", SBC_DATA_TIMEOUT);
         else
            sprintf(Response, "{\"ErrorCode\": %d}", SBC_CONNECTION_TIMEOUT);
      }
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   JsonStr = 0;
   return Response;
}

/*JsonResponsePtr WebService::GetEventHistory(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetEventHistory" received from the client.
 * It is used to write Event History data in the response buffer after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetEventHistory(SINT8 * JsonStr)
{
   SINT8* JsonFrom_Data = 0;
   SINT8* JsonTo_Data = 0;
   SINT32 From = 0;
   SINT32 To = 0;
   SINT32 i = 0;
   SINT32 NoofDataRequested = 0;
   SINT32 Ret, OffsetInResponse = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETEVENTHISTORY);
   if (ErroCode == SUCCESS) {
      JsonFrom_Data = strstr(JsonStr, "From\":");
      if (JsonFrom_Data) {
         JsonFrom_Data += FROMSTRLEN;
         SkipSpace(JsonFrom_Data);
         From = atoi(JsonFrom_Data);
      }
      JsonTo_Data = strstr(JsonStr, "To\":");
      if (JsonTo_Data) {
         JsonTo_Data += TOSTRLEN;
         SkipSpace(JsonTo_Data);
         To = atoi(JsonTo_Data);
      }
      NoofDataRequested = To - From + 1;
      if (NoofDataRequested <= MAX_EVENTHISTORYPER_REQUEST && NoofDataRequested >= 0) {
         Ret = SendTCPRequest(EVENTLOGFIELDID, From, To);
         if (Ret > 0) {
            OffsetInResponse = sprintf(Response, "{\"ErrorCode\":%d", SUCCESS);
            strcat(Response + OffsetInResponse, ",\"EventData\":[");
            OffsetInResponse += EVENTSTRLEN;
            JsonEvent_Log * EventResponse = (JsonEvent_Log *) SBCResponseBuf;
            for (i = 0; i < nRecords; i++) {
               strcat(Response + OffsetInResponse, "{");
               OffsetInResponse += 1;
               OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":%ld"
                     ",\"%s\":%d"
                     ",\"%s\":%d"
                     ",\"%s\":\"%s\""
                     ",\"%s\":\"%s\""
                     ",\"%s\":\"%s\""
                     ",\"%s\":\"%02d:%02d:%02d %02d-%02d-%02d\""
                     ",\"%s\":\"%s\""
                     ",\"%s\":\"%s\"", KeyEventLog[EVENTLOG_EVENTNUM], EventResponse[i].EventNum,
                     KeyEventLog[EVENTLOG_PRESETNO], EventResponse[i].PresetNo, KeyEventLog[EVENTLOG_REV],
                     EventResponse[i].Rev, KeyEventLog[EVENTLOG_USERID], EventResponse[i].UserId,
                     KeyEventLog[EVENTLOG_EVENTID], EventResponse[i].EventId, KeyEventLog[EVENTLOG_PSSERIALNUMBER],
                     EventResponse[i].PSSerialNumber, KeyEventLog[EVENTLOG_TS], EventResponse[i].TS.Hour,
                     EventResponse[i].TS.Minute, EventResponse[i].TS.Second, EventResponse[i].TS.Century_Month,
                     EventResponse[i].TS.Day, EventResponse[i].TS.Years, KeyEventLog[EVENTLOG_EVENTREASON],
                     EventResponse[i].EventReason, KeyEventLog[EVENTLOG_EVENTDESCRIPTION],
                     EventResponse[i].EventDescription);

               if (i == (nRecords - 1)) {
                  strcat(Response + OffsetInResponse, "}");
                  OffsetInResponse += 1;
               }
               else {
                  strcat(Response + OffsetInResponse, "},");
                  OffsetInResponse += 2;
               }
            }
            strcat(Response + OffsetInResponse, "]}");
            ResponseLength = OffsetInResponse + 2;
         }
         else
         {
            if(Ret == DATA_REQUEST_TIMEOUT)
               sprintf(Response, "{\"ErrorCode\": %d}", SBC_DATA_TIMEOUT);
            else if(Ret == DATA_NOT_IN_SPECIFIEDRANGE)
               sprintf(Response, "{\"ErrorCode\": %d}", DATA_NOT_FOUND_IN_SPECIFIEDRANGE);
            else
               sprintf(Response, "{\"ErrorCode\": %d}", SBC_CONNECTION_TIMEOUT);
         }
      }
      else
         sprintf(Response, "{\"ErrorCode\": %d}", LARGENO_OF_DATA_REQUSTED);
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}

/*JsonResponsePtr WebService::GetNumWeldData(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetNumWeldData" received from the client.
 * It is used to get total number of events available in the Event.log file present in
 * the SBC Disk and returns the same  in the response buffer after user authentication.
 * WC will send the Field Id = REQFORWELDLOGCOUNT ,in order to request to get total
 * number of events available in the weld log file.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetNumWeldData(SINT8 * JsonStr)
{
   SINT32 RetVal = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETHISTORYCOUNT);
   if (ErroCode == SUCCESS) {
      RetVal = SendTCPRequest(REQFORWELDLOGCOUNT, 0, 0);
      if (RetVal > 0)
         sprintf(Response, "{\"ErrorCode\":%d,\"TotalWeldDataPresent\":%ld}", SUCCESS, JsonFileCount);
      else
      {
        if(RetVal == DATA_REQUEST_TIMEOUT)
           sprintf(Response, "{\"ErrorCode\": %d}", SBC_DATA_TIMEOUT);
        else
           sprintf(Response, "{\"ErrorCode\": %d}", SBC_CONNECTION_TIMEOUT);
      }
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   JsonStr = 0;
   return Response;
}

/*JsonResponsePtr WebService::GetWeldHistory(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetWeldHistory" received from the client.
 * It is used to write Weld History data in the response buffer after user authentication.
 * Each Weld Data received from SBC ,are separated by a special character ">>"
 * So in order to print all weld data ,the receive buffer "SBCResponseBuf" is split by ">>" character.
 * Similarly if there is any alarm present in the weld data ,SBC sends another special character "@" with the same weld data.
 * So in order to print alarm data ,the receive buffer "SBCResponseBuf" is split by "@" character.
 * There is also some parameters present in the WeldData.log file ,like ForceA,ForceB,Velocitu_Aef ,that we are not sending in the Json Response.
 * So We are discarding  the values received in the corresponding Id's.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetWeldHistory(SINT8 * JsonStr)
{
   SINT8* JsonFrom_Data = 0;
   SINT8* JsonTo_Data = 0;
   SINT32 From = 0;
   SINT32 To = 0;
   SINT32 NoofDataRequested = 0;
   SINT8 * WeldDataStrt;
   SINT32 TcpResponseLen;
   SINT32 i = 0;
   SINT32 j = 1;
   SINT8 *Temp = 0;
   SINT32 AlarmString[8];
   SINT32 Indx = 0;
   SINT8 * NextWelddataPtr;
   SINT8 ValueBuff[MAXBUFFSIZEOFWELDDATA];
   memset(ValueBuff, 0, MAXBUFFSIZEOFWELDDATA);
   memset(AlarmArray, 0, MAXNOOFALARMS);
   SINT32 OffsetInResponse = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETWELDHISTORY);
   if (ErroCode == SUCCESS) {
      JsonFrom_Data = strstr(JsonStr, "From\":");
      if (JsonFrom_Data) {
         JsonFrom_Data += FROMSTRLEN;
         SkipSpace(JsonFrom_Data);
         From = atoi(JsonFrom_Data);
      }
      JsonTo_Data = strstr(JsonStr, "To\":");
      if (JsonTo_Data) {
         JsonTo_Data += TOSTRLEN;
         SkipSpace(JsonTo_Data);
         To = atoi(JsonTo_Data);
      }
      NoofDataRequested = To - From + 1;
      if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE))
         sprintf(Response, "{\"ErrorCode\": %d}", SYSTEM_BUSY);
      else if (NoofDataRequested <= MAX_WELDHISTORYPER_REQUEST && NoofDataRequested >= 0) {
         JsonReadyFlag = ReadyFlag;   //latch ready status before stopping statemachine
         StopStateMachine(); /* Stop the State machine*/
         TcpResponseLen = SendTCPRequest(WELDHISTORYFIELDID, From, To);
         if (TcpResponseLen > 0) {
            OffsetInResponse += sprintf(Response, "{\"ErrorCode\":%d", SUCCESS);
            strcat(Response + OffsetInResponse, ",\"WeldData\":[{");
            OffsetInResponse += WELDDATARRSTRLEN;
            WeldDataStrt = strchr(SBCResponseBuf, SOH);
            while (WeldDataStrt && ((WeldDataStrt - SBCResponseBuf) < TcpResponseLen)) {
               WeldDataStrt += 1;
               for (j = RCYCLECOUNT; j <= ACTSERIALNUMPARAM + 2; j++) {
                  //we are handling all array type varible here ,as we have to send its value as the JSON array format
                  if (j == RUSERID || j == RUDISCAN || j == RPRESETVALIDATED || j == RACTASSEMBLYNUM
                        || j == RPSASSEMBLYNUM || j == RSTACKASSEMBLYNUM || j == RFREQCHG || j == PSSERIALNUMPARAM || j == ACTSERIALNUMPARAM) {
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                     OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":\"%s\",", KeyWeldResult[j],
                           ValueBuff);
                  }
                  //we are handling the time and date value separately ,as we dont have enum id for time and date in enum RUN_PARAM
                  else if (j == atoi(TimeKeyID)) {
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                     OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":\"%s\",", TimeKeyID, ValueBuff);
                  }
                  else if (j == atoi(DateKeyID)) {
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                     OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":\"%s\",", DateKeyID, ValueBuff);
                  }
                  //here we are skipping the value of these three weld parameter , because we dont need these values in the response buffer.
                  else if (j == RVELOCITY_AEF)   //Need to skip this history parameter value as it is specific
                  //to AEF actuator. Function call below will increment the WeldDataStart pointer
                  //to the next values we needed.
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                  //we are sending "n/a" if we got null for any of the weld data .
                  else   //All parameters of integer type are formatted here for JSON response
                  {
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                     if (strcmp(ValueBuff, "n/a")) {
                    	 OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":%s,", KeyWeldResult[j],
                               ValueBuff);
                     }
                     else {
                         OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":\"%s\",", KeyWeldResult[j],
                               ValueBuff);
                     }
                  }
               }
               GetValAndIncrementBuffer(&WeldDataStrt,ETX, ValueBuff);
               OffsetInResponse += sprintf(Response + OffsetInResponse, "\"%s\":\"%s\"", PresetNameKeyID, ValueBuff);

               Temp = 0;
               //we are searching for the character SOH in WeldDataStrt,as we are sending this character from sbc before any new welddata read from the welddata log file.
               NextWelddataPtr = strchr(WeldDataStrt, SOH);
               //we are searching for the character BEL ,in order to know wheather there is any alarm present in the weld data or not .because
               //we are sending this special character in the buffer if we find any alarm.
               if (NextWelddataPtr)
                  Temp = strnchr(WeldDataStrt, BEL, NextWelddataPtr - WeldDataStrt);
               else
                  Temp = strnchr(WeldDataStrt, BEL, TcpResponseLen - (WeldDataStrt - SBCResponseBuf));
               if (Temp) {
                  Indx = 0;
                  AlarmArrayIndex = 0;
                  for (i = 0; i < MAXTYPEOFALARMAVAILABLE; i++) {
                     GetValAndIncrementBuffer(&WeldDataStrt, STX, ValueBuff);
                     AlarmString[i] = atoi(ValueBuff);
                     if (AlarmString[i] != 0) {
                        switch (i) {
                        case 0:
                           GetAlarmFromOffset(AlarmString[i], NCG1);
                           break;
                        case 1:
                           GetAlarmFromOffset(AlarmString[i], OLG1);
                           break;
                        case 2:
                           GetAlarmFromOffset(AlarmString[i], EQG1);
                           break;
                        case 3:
                           GetAlarmFromOffset(AlarmString[i], CMG1);
                           break;
                        case 4:
                           GetAlarmFromOffset(AlarmString[i], CAG1);
                           break;
                        case 5:
                           GetAlarmFromOffset(AlarmString[i], WAG1);
                           break;
                        case 6:
                           GetAlarmFromOffset(AlarmString[i], PRG1);
                           break;
                        case 7:
                           GetAlarmFromOffset(AlarmString[i], PSG1);
                           break;
                        }
                     }

                  }
                  WeldDataStrt += 1;   //move the pointer to next character,
                  OffsetInResponse += sprintf(Response + OffsetInResponse, ",\"%s\":\[\"%04X", "Alarm",
                        (unsigned int)AlarmArray[Indx]);
                  for (Indx = 1; Indx <= AlarmArrayIndex - 1; Indx++) {
                     OffsetInResponse += sprintf(Response + OffsetInResponse, "-%04X", (unsigned int)AlarmArray[Indx]);
                  }
                  OffsetInResponse += sprintf(Response + OffsetInResponse, "%s", "\"]");
               }

               WeldDataStrt = strchr(WeldDataStrt,SOH);
               if (WeldDataStrt && ((WeldDataStrt - SBCResponseBuf) < TcpResponseLen))
                  OffsetInResponse += sprintf(Response + OffsetInResponse, "%s", "},{");
               else
                  OffsetInResponse += sprintf(Response + OffsetInResponse, "%s", "}");

            }

            strcat(Response + OffsetInResponse, "]}");
            ResponseLength = OffsetInResponse + 2;
         }
         else
         {
              if(TcpResponseLen == DATA_REQUEST_TIMEOUT)
                 sprintf(Response, "{\"ErrorCode\": %d}", SBC_DATA_TIMEOUT);
              else if(TcpResponseLen == DATA_NOT_IN_SPECIFIEDRANGE)
                 sprintf(Response, "{\"ErrorCode\": %d}", DATA_NOT_FOUND_IN_SPECIFIEDRANGE);
              else
                 sprintf(Response, "{\"ErrorCode\": %d}", SBC_CONNECTION_TIMEOUT);
         }
         StartStateMachine();
         ReadyFlag = JsonReadyFlag;
         if (ReadyFlag == TRUE) SetReady();
      }
      else
         sprintf(Response, "{\"ErrorCode\":%d}", LARGENO_OF_DATA_REQUSTED);
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}

/*void WebService::GetAlarmFromOffset(SINT32 AlarmString,UINT32 AlarmType)
 * Purpose:
 *  This function is called from "GetWeldHistory()".
 *	AlarmString is the  alarm variables which code different errors.The error variables is
 *	checked bitwise and the appropriate Alarm code extract by calling the GetAlarmId().
 *	All the AlarmIds are store in an AlarmArray[] ,which is use to send the alarm data in the JOSN response buffer.
 *  Entry condition:
 *	AlarmString-alarm variables which code different errors .
 *	AlarmType- Type of the alarm .
 *  Exit condition:
 *  	NONE
 */
void WebService::GetAlarmFromOffset(SINT32 AlarmString, UINT32 AlarmType)
{
   SINT32 Buff = 0;
   SINT32 AlarmBit = 0;
   UINT32 AlarmCode = 0;
   SINT32 BufferPosition[MAXALARMBITCHECK]; /*--  check bits 1 thru 27 of alarm data, as bit 0 and last 4 bits of each word is reserved --*/
   for (AlarmBit = 1; AlarmBit <= 27; AlarmBit++) {
      if ((AlarmString >> AlarmBit) & 1) {
         BufferPosition[Buff] = AlarmBit;   //here we are storing all the bit position having 1 in BufferPosition[].
         Buff++;
      }
   }
   for (SINT32 data = 0; data < Buff; data++) {
      AlarmCode = AlarmType | (1 << BufferPosition[data]);
      AlarmArray[AlarmArrayIndex] = GetAlarmID(AlarmCode, FALSE);
      AlarmArrayIndex++;
   }
}

/*JsonResponsePtr WebService::SetPresetValue(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the URL "SetPresetValue" received from the client.
 * It is used to set the value of the requested PresetId and write the status to the response buffer
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request
 * Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SetPresetValue(SINT8 * JsonStr)
{
   SINT8* JsonParamId = 0, *JSonChangeReason = 0;
   SINT8* JsonParamvalue = 0;
   SINT32 ParamId = 0;
   SINT32 ParamValue = 0;
   UINT16 Position = 0;
   UINT16 MinMaxPosition;
   SINT32 Min = 0;
   SINT32 Max = 0;
   SINT32 FormattedMin = 0;
   SINT32 FormattedMax = 0;
   BOOLEAN FrqOfSetSign = 1;   //1 positive 0 negative
   SINT8 *Temp = JsonStr;
   SINT32 FormattedNumber;
   SINT32 MaxBit, MinBit;
   SINT8 *Temp1 = 0, *AfterReasonPtr = 0, *AfterArrPtr = 0, *CurlyEndPtr = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_SETPRESET);
   BOOLEAN ExitFlag = FALSE;
   if (ErroCode == SUCCESS) {
      while (JsonStr && ((PostDataLen - (Temp - PostDataPtr)) > 0)) {
         Temp = strnstr(Temp, "ParamId\":", PostDataLen - (Temp - PostDataPtr));
         if (Temp) {
            CurlyEndPtr = strnchr(Temp, '}', PostDataLen - (Temp - PostDataPtr));
            JsonParamId = Temp;
            JsonParamId += PARAMIDSTRLEN;
            SkipSpace(JsonParamId);
            ParamId = atoi(JsonParamId);
            Temp1 = JsonParamId;

            ErroCode = CheckParmeterID(SERVICE_SETPRESET, (PARAM) ParamId);
            if (ErroCode == SUCCESS)
            {
               for (Position = 0; Map[Position].Struct_ID != -1; Position++)
               {
                  if (Map[Position].ParameterId == ParamId) {
                     MatcedParamId = TRUE;
                     break;
                  }
               }
            }

            if (ErroCode != SUCCESS)
            {
               sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
               JsonStr = NULL;
            }
            else if (MatcedParamId)
            {
               GlobalCommandID = Map[Position].Struct_ID;
               ErroCode = CheckReasonRequired(SERVICE_SETPRESET, (PARAM) ParamId);
               if (ErroCode == REASON_REQUIRED) {
                  JSonChangeReason = strnstr(Temp1, "\"Reason\":\"", CurlyEndPtr - Temp1);   //find reason for current param change within closing
                  if (JSonChangeReason) {
                     JSonChangeReason += REASONSTRLEN;   //here after Reason:" pointing to reason
                     Temp = strnchr(JSonChangeReason, '"', CurlyEndPtr - JSonChangeReason);   //find the reason end with in closing
                     if (Temp) {
                        *Temp = '\0';
                        AfterReasonPtr = Temp + 1;
                        if (strlen(JSonChangeReason) > 0) {
                           strncpy(ChangeReason, JSonChangeReason,
                           MAX_EVENTREASON_LEN - 1);
                           ErroCode = SUCCESS;
                        }
                     }
                  }
               }

               MatcedParamId = FALSE;
               if (ErroCode != SUCCESS)
               {
                  sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                  JsonStr = NULL;
               }
               else
               {
                  MinMaxPosition = 0;
                  while (MinMap[MinMaxPosition].Struct_ID != -1 && !ExitFlag)
                  {
                     if (MinMap[MinMaxPosition].ParameterId == ParamId)
                     {
                        ExitFlag = TRUE;
                        if (MinMap[MinMaxPosition].Function1 != NULL) MinMap[MinMaxPosition].Function1(MinMap[MinMaxPosition].Struct_ID);
                        if (Map[Position].DataType == UInt16)
                        {
                           Max = *((UINT16 *) (MinMap[MinMaxPosition].ptrmax));
                           Min = *((UINT16 *) (MinMap[MinMaxPosition].ptrmin));

                           if (ParamId == WELDMODE) {
                              FormattedMax = Max;
                              FormattedMin = Min;
                              for (MaxBit = 0; MaxBit <= 10; MaxBit++) {
                                 if ((FormattedMax >> MaxBit) & 1)   //For Radio index type preset parameter we are sending bit position value
                                       //to the user.
                                    break;
                              }
                              for (MinBit = 0; MinBit <= 10; MinBit++) {
                                 if ((FormattedMin >> MinBit) & 1)
                                    break;
                              }
                              FormattedMax = MaxBit;
                              FormattedMin = MinBit;
                           }
                           else {
                              FormattedMax = ConvertInternalExternal(Max, Map[Position].UnitFormat, CurrentSetup.Units);
                              FormattedMin = ConvertInternalExternal(Min, Map[Position].UnitFormat, CurrentSetup.Units);
                           }

                        }
                        else {
                           Max = *((SINT32 *) (MinMap[MinMaxPosition].ptrmax));
                           FormattedMax = ConvertInternalExternal(Max, Map[Position].UnitFormat, CurrentSetup.Units);
                           Min = *((SINT32 *) (MinMap[MinMaxPosition].ptrmin));
                           FormattedMin = ConvertInternalExternal(Min, Map[Position].UnitFormat, CurrentSetup.Units);
                        }
                     }
                     MinMaxPosition++;
                  }
                  //
                  Temp1 = JsonParamId;
                  JsonParamvalue = strnstr(Temp1, "ParamValue\":", CurlyEndPtr - Temp1);
                  if (JsonParamvalue) {
                     if ((ParamId == WRITEIN1) || (ParamId == WRITEIN2) || (ParamId == PS_FREQOFFSET)) {   //freqoffset format should be "+1"/"-1"

                        JsonParamvalue = strnstr(Temp1, "ParamValue\":\"", CurlyEndPtr - Temp1);   //make sure array type parameter values start after :"
                        if (JsonParamvalue) {
                           JsonParamvalue += PARAMARRAYSTRLEN;
                           Temp = strnchr(JsonParamvalue, '"', PostDataLen - (JsonParamvalue - PostDataPtr));
                        }
                        else
                           Temp = 0;   //To assert INVALID_SERVICE_DATA error

                        if (Temp) {
                           *Temp = '\0';
                           AfterArrPtr = Temp + 1;
                           strncpy(JsonParamValueArr, JsonParamvalue, sizeof(JsonParamValueArr) - 1);
                           if (ParamId == PS_FREQOFFSET) {
                              SINT32 Sint32Val;
                              if (JsonParamValueArr[0] == '-') FrqOfSetSign = 0;
                              if (FrqOfSetSign)
                                 Sint32Val = atoi(JsonParamValueArr);
                              else
                                 Sint32Val = atoi(JsonParamValueArr + 1);
                              if ((Sint32Val >= Min) && (Sint32Val <= Max)) {
                                 if (!FrqOfSetSign) Sint32Val = -Sint32Val;
                                 *((UINT32*) (Map[Position].Vptr)) = Sint32Val;
                                 UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                                 sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                                 FrqOfSetSign = 1;
                              }
                              else {
                                 SendMinMaxValue(ParamId, Position, Min, Max);
                                 JsonStr = NULL;
                              }
                            }
                           else {
                              SINT8 *Arr = (SINT8*) (Map[Position].Vptr);
                              strncpy((SINT8*) ParamOldVal, (SINT8 *) Arr, sizeof(ParamOldVal) - 1);
                              strncpy((SINT8*) ParamNewVal, (SINT8 *) (JsonParamValueArr),
                              WRITEINLEN - 1);
                              strncpy((SINT8*) Arr, (SINT8 *) (JsonParamValueArr),
                              WRITEINLEN - 1);
                              Type = arr;
                              UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                              sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                              JsonParamvalue = 0;
                           }
                        }
                        else {
                           sprintf(Response, "{\"ErrorCode\":%d,"
                                 "\"%s\":%ld}", INVALID_SERVICE_DATA, "ParamId", ParamId);
                           JsonStr = NULL;
                        }
                     }
                     else {
                        GlobalCommandID = Map[Position].Struct_ID;
                        JsonParamvalue += PARAMVALUESTRLEN;
                        SkipSpace(JsonParamvalue);
                        ErroCode = stringsplit(JsonParamvalue, Map[Position].UnitFormat, CurrentSetup.Units, &ParamValue);
                        Temp = JsonParamvalue;
                        if (ErroCode == SUCCESS) {
                           ExitFlag = FALSE;
                           if ((ParamValue >= FormattedMin) && (ParamValue <= FormattedMax)) {
                        	   if(ParamId == HOLDPRESSURE && CurrentPreset.HoldPressureFlag == 0)CurrentPreset.HoldPressureFlag = 1;
                        	   FormattedNumber = ConvertExternalInternal(ParamValue, Map[Position].UnitFormat, CurrentSetup.Units);
                               SetParamValue(Position, FormattedNumber);
                               if (Map[Position].Function2 != NULL) Map[Position].Function2();
                               sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                               UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                           }
                           else {
                              SendMinMaxValue(ParamId, Position, Min, Max);
                              JsonStr = NULL;
                           }
                        }
                        else {
                           sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                           JsonStr = NULL;
                        }
                     }   //else end ,for SINT32 type
                  }   //if end,if paramvalue found in jsonstr
                  else {
                     ErroCode = INVALID_SERVICE_DATA;
                     sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                     JsonStr = NULL;
                  }
               }   //else end
            }   //ptr end
            else {
               ErroCode = MISMATCH_PARAMID;
               sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
               JsonStr = NULL;
            }
         }   //if end
         else
            JsonStr = NULL;
         if (AfterArrPtr) Temp = AfterArrPtr;
         if (AfterReasonPtr) Temp = AfterReasonPtr;
         AfterReasonPtr = 0;
         AfterArrPtr = 0;
      }
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   ChangeReason[0] = 0;
   return Response;
}

/*void WebService::SetDisableFlagStatus(UINT16 *DisableFlagSet,PARAM ParamID)
 * Purpose:
 * This function is called from SetPresetValue() and "SetSystemConfig()" function.
 * It is used to set the Disable flag ,after which we can set the ParamValue with the requested preset Param id.
 * Entry condition:
 *	DisableFlagSet- Pointer to disable/enable flag.
 *	ParamID- Requested Parameter id received in the post data.
 * Exit condition:
 *  None.
 */
void WebService::SetDisableFlagStatus(UINT16 *DisableFlagSet, PARAM ParamID)
{
   if (*DisableFlagSet) {
      switch (ParamID) {
      case ENERGYMLR:
         *DisableFlagSet &= (~MENERGYBIT);
         break;
      case ENERGYPLR:
         *DisableFlagSet &= (~PENERGYBIT);
         break;
      case ENERGYMLS:
         *DisableFlagSet &= (~MENERGYBIT);
         break;
      case ENERGYPLS:
         *DisableFlagSet &= (~PENERGYBIT);
         break;
      case TIMEMLS:
         *DisableFlagSet &= (~MTIMEBIT);
         break;
      case TIMEPLS:
         *DisableFlagSet &= (~PTIMEBIT);
         break;
      case TIMEMLR:
         *DisableFlagSet &= (~MTIMEBIT);
         break;
      case TIMEPLR:
         *DisableFlagSet &= (~PTIMEBIT);
         break;
      case POWERMLR:
         *DisableFlagSet &= (~MPKPOWERBIT);
         break;
      case POWERPLR:
         *DisableFlagSet &= (~PPKPOWERBIT);
         break;
      case COLMLR:
         *DisableFlagSet &= (~MCOLDISTBIT);
         break;
      case COLPLR:
         *DisableFlagSet &= (~PCOLDISTBIT);
         break;
      case ABSMLR:
         *DisableFlagSet &= (~MABSDISTBIT);
         break;
      case ABSPLR:
         *DisableFlagSet &= (~PABSDISTBIT);
         break;
      case TRSDISTMLR:
         *DisableFlagSet &= (~MTRIGDISTBIT);
         break;
      case WELDFORCEMLR:
         *DisableFlagSet &= (~MFORCEBIT);
         break;
      case WELDFORCEPLR:
         *DisableFlagSet &= (~PFORCEBIT);
         break;
      case POWERMLS:
         *DisableFlagSet &= (~MPKPOWERBIT);
         break;
      case POWERPLS:
         *DisableFlagSet &= (~PPKPOWERBIT);
         break;
      case COLMLS:
         *DisableFlagSet &= (~MCOLDISTBIT);
         break;
      case COLPLS:
         *DisableFlagSet &= (~PCOLDISTBIT);
         break;
      case ABSMLS:
         *DisableFlagSet &= (~MABSDISTBIT);
         break;
      case ABSPLS:
         *DisableFlagSet &= (~PABSDISTBIT);
         break;
      case TRSDISTMLS:
         *DisableFlagSet &= (~MTRIGDISTBIT);
         break;
      case TRSDISTPLS:
         *DisableFlagSet &= (~PTRIGDISTBIT);
         break;
      case WELDFORCEMLS:
         *DisableFlagSet &= (~MFORCEBIT);
         break;
      case WELDFORCEPLS:
         *DisableFlagSet &= (~PFORCEBIT);
         break;
      case MPRESSURELIMIT:
         *DisableFlagSet &= (~MPRESSURELIMITBIT);
         break;
      case PS_PPRESSURELIMIT:
         *DisableFlagSet &= (~PPRESSURELIMITBIT);
         break;
      case AMPTRIGTIMEVALUE:
         *DisableFlagSet = (~(BIT2)) | BIT0;
         break;
      case AMPTRIGENERVALUE:
         *DisableFlagSet = (~(BIT3)) | BIT0;
         break;
      case AMPTRIGPOWERVALUE:
         *DisableFlagSet = (~(BIT4)) | BIT0;
         break;
      case DOWNSPEEDPLR:
         *DisableFlagSet &= (~BIT2);
         break;
      case DOWNSPEEDMLR:
         *DisableFlagSet &= (~BIT1);
         break;
      case WELDPRESSURE_PLT:
    	 *DisableFlagSet &=(~WELDPRESSURE_PBIT);
    	 break;
      case WELDPRESSURE_MLT:
    	 *DisableFlagSet &=(~WELDPRESSURE_MBIT);
    	 break;
      case DOWNSPEED_PLT:
    	 *DisableFlagSet &=(~DOWNSPEED_PBIT);
    	 break;
      case DOWNSPEED_MLT:
         *DisableFlagSet &=(~DOWNSPEED_MBIT);
         break;
      case HOLDPRESSURE_PLT:
         *DisableFlagSet &=(~HOLDPRESSURE_PBIT);
         break;
      case HOLDPRESSURE_MLT:
         *DisableFlagSet &=(~HOLDPRESSURE_MBIT);
         break;
      case HOLDTIME_PLT:
         *DisableFlagSet &=(~HOLDTIME_PBIT);
         break;
      case HOLDTIME_MLT:
         *DisableFlagSet &=(~HOLDTIME_MBIT);
         break;
      case AMPA_PLT:
          *DisableFlagSet &=(~AMPA_PBIT);
          break;
      case AMPA_MLT:
          *DisableFlagSet &=(~AMPA_MBIT);
          break;
      case TRIGFORCE_PLT:
          *DisableFlagSet &=(~TRIGFORCE_PBIT);
          break;
      case TRIGFORCE_MLT:
          *DisableFlagSet &=(~TRIGFORCE_MBIT);
           break;
      case WELDTIME_PLT:
          *DisableFlagSet &=(~WELDTIME_PBIT);
          break;
      case WELDTIME_MLT:
          *DisableFlagSet &=(~WELDTIME_MBIT);
          break;
      case WELDENERGY_PLT:
          *DisableFlagSet &=(~WELDENERGY_PBIT);
          break;
      case WELDENERGY_MLT:
          *DisableFlagSet &=(~WELDENERGY_MBIT);
          break;
      case PEAKPOWER_PLT:
          *DisableFlagSet &=(~PEAKPWR_PBIT);
          break;
      case PEAKPOWER_MLT:
    	  *DisableFlagSet &=(~PEAKPWR_MBIT);
    	  break;
      case COLLAPSEDIST_PLT:
    	  *DisableFlagSet &=(~COLDIST_PBIT);
    	  break;
      case COLLAPSEDIST_MLT:
    	  *DisableFlagSet &=(~COLDIST_MBIT);
    	  break;
      case ABSDIST_PLT:
    	  *DisableFlagSet &=(~ABSDIST_PBIT);
    	  break;
      case ABSDIST_MLT:
    	  *DisableFlagSet &=(~ABSDIST_MBIT);
    	  break;
      case SCRUBTIME_PLT:
    	  *DisableFlagSet &=(~SCRUBTIME_PBIT);
    	  break;
      case SCRUBTIME_MLT:
    	  *DisableFlagSet &=(~SCRUBTIME_MBIT);
    	  break;
      case SCRUBAMP_PLT:
    	  *DisableFlagSet &=(~AMPSCRUBTIME_PBIT);
    	  break;
      case SCRUBAMP_MLT:
    	  *DisableFlagSet &=(~AMPSCRUBTIME_MBIT);
    	  break;
      case TRIGDIST_PLT:
    	  *DisableFlagSet &=(~TRIGDIST_PBIT);
    	  break;
      case TRIGDIST_MLT:
    	  *DisableFlagSet &=(~TRIGDIST_MBIT);
    	  break;
      default:
         *DisableFlagSet = 0;
         break;
      }
   }

}

/*void WebService::SendMinMaxValue(SINT32 ParamId,UINT16 PositionInMap,SINT32 Min,SINT32 Max)
 * Purpose:
 * This function is called from SetPresetValue() and "SetSystemConfig()" function.
 * It is used to send the UnitFormatted Min and Max value of the preset parameter ,if the ParamValue send by the WebClient does not
 * fall within the Minimum and Maximum range of that requested preset parameter.
 * Entry condition:
 *	PositionInMap- Position of the requested preset parameter in the MAP structure..
 *	ParamID- Requested Parameter id received in the post data.
 *	Min - Minimum value of the preset Parameter present in the MINMAXMAP structure.
 *	Max - Maximum value of the preset Parameter present in the MINMAXMAP structure.
 * Exit condition:
 *  None.
 */
void WebService::SendMinMaxValue(SINT32 ParamId, UINT16 PositionInMap, SINT32 Min, SINT32 Max)
{
   SINT8 Str[VGA_LINESIZE];
   SINT8 Str2[VGA_LINESIZE];
   memset(Str, 0, sizeof(Str));
   memset(Str2, 0, sizeof(Str2));
   SINT8 * MinStr, *MaxStr;
   FORMAT format;
   if (ParamId == WELDMODE || ParamId == WELDSCALEINDEX || ParamId == J3_32_IN || ParamId == J3_33_IN
         || ParamId == J3_19_IN || ParamId == J3_17_IN || ParamId == J3_31_IN || ParamId == J3_1_IN
         || ParamId == J3_8_OUT || ParamId == J3_36_OUT || ParamId == J3_22_OUT) {
      SINT32 MaxBit, MinBit;
      for (MaxBit = 0; MaxBit <= 13; MaxBit++) {
         if ((Max >> MaxBit) & 1)   //For Radio index type preset parameter we are sending bit position value
               //to the user.
             break;
        }
      for (MinBit = 0; MinBit <= 10; MinBit++) {
         if ((Min >> MinBit) & 1)
            break;
      }
      sprintf(Response, "{\"ErrorCode\":%d,\"ParamId\":%ld,\"Min\":%ld,\"Max\":%ld}", EXCEEDS_LIMITS, ParamId, MinBit,
            MaxBit);
   }
   else {
      format = Map[PositionInMap].UnitFormat;
      if ((format == INTEGER) || (format == COUNTER) || (format == ON_OFF)) {
         Numout2(Min, 10, Str, sizeof(Str) - 1);
         Numout2(Max, 10, Str2, sizeof(Str2) - 1);
      }
      else {
         FormatVariables(Min, format, Str, LINESIZE, CurrentSetup.Units);
         Str[LINESIZE] = 0;
         FormatVariables(Max, format, Str2, LINESIZE, CurrentSetup.Units);
         Str2[LINESIZE] = 0;
      }
      MinStr = Trim_FillChar(Str); /*remove the blanks before Value*/
      MaxStr = Trim_FillChar(Str2); /*remove the blanks before Value*/
      sprintf(Response, "{\"ErrorCode\":%d,\"ParamId\":%ld,\"Min\":%s,\"Max\":%s}", EXCEEDS_LIMITS, ParamId, MinStr,
            MaxStr);
   }
}

/*JsonResponsePtr WebService::SetSystemConfigValue(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the URL "SetSystemConfigValue" received from the client.
 * It is used to set the value of the requested SystemConfigId and write the status to the response buffer
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request
 *Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SetSystemConfigValue(SINT8 * JsonStr)
{
   SINT8* JsonParamId = 0, *JSonChangeReason = 0;
   SINT8* JsonParamvalue = 0;
   SINT32 ParamId = 0;
   SINT32 ParamValue = 0;
   UINT16 Position = 0;
   UINT16 MinMaxPosition;
   SINT32 Min = 0;
   SINT32 Max = 0;
   SINT32 FormattedMin = 0;
   SINT32 FormattedMax = 0;
   SINT8 *Temp = JsonStr;
   SINT32 ret = 0;
   SINT32 MaxBit, MinBit;
   SINT32 FormattedNumber = 0;
   SINT8 *Temp1 = 0, *AfterReasonPtr = 0, *AfterArrPtr = 0, *CurlyEndPtr = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_SETSYSTEMCONFIG);
   BOOLEAN ExitFlag = FALSE;
   SINT32 Indx = 0;

   if (ErroCode == SUCCESS) {
      while (JsonStr && ((PostDataLen - (Temp - PostDataPtr)) > 0)) {
         Temp = strstr(Temp, "ParamId\":");
         if (Temp) {
            CurlyEndPtr = strnchr(Temp, '}', PostDataLen - (Temp - PostDataPtr));
            JsonParamId = Temp;
            JsonParamId += PARAMIDSTRLEN;
            SkipSpace(JsonParamId);
            ParamId = atoi(JsonParamId);
            Temp1 = JsonParamId;

            ErroCode = CheckParmeterID(SERVICE_SETSYSTEMCONFIG, (PARAM) ParamId);
            if (ErroCode == SUCCESS) {
               for (Position = 0; Map[Position].Struct_ID != -1; Position++) {
                  if (Map[Position].ParameterId == ParamId) {
                     MatcedParamId = TRUE;
                     break;
                  }
               }
            }
            if (ErroCode != SUCCESS) {
               sprintf(Response, "{\"ErrorCode\":%d,"
                     "\"%s\":%ld}", ErroCode, "ParamId", ParamId);
               JsonStr = NULL;
            }
            else if (MatcedParamId) {
               ErroCode = CheckReasonRequired(SERVICE_SETSYSTEMCONFIG, (PARAM) ParamId);
               if (ErroCode == REASON_REQUIRED) {
                  JSonChangeReason = strnstr(Temp1, "\"Reason\":\"", CurlyEndPtr - Temp1);	//find reason for current param change within closing
                  if (JSonChangeReason) {
                     JSonChangeReason += REASONSTRLEN;					//here after Reason:" pointing to reason
                     Temp = strnchr(JSonChangeReason, '"', CurlyEndPtr - JSonChangeReason);   //find the reason end with in closing
                     if (Temp) {
                        *Temp = '\0';
                        AfterReasonPtr = Temp + 1;
                        if (strlen(JSonChangeReason) > 0) {
                           strncpy(ChangeReason, JSonChangeReason,
                           MAX_EVENTREASON_LEN - 1);
                           ErroCode = SUCCESS;
                        }
                     }
                  }
               }
               MatcedParamId = FALSE;
               if (ErroCode != SUCCESS) {
                  sprintf(Response, "{\"ErrorCode\":%d,"
                        "\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                  JsonStr = NULL;
               }
               else {
                  MinMaxPosition = 0;
                  while (MinMap[MinMaxPosition].Struct_ID != -1 && !ExitFlag) {
                     if (MinMap[MinMaxPosition].ParameterId == ParamId) {

                        ExitFlag = TRUE;
                        if (MinMap[MinMaxPosition].Function1 != NULL)
                        	MinMap[MinMaxPosition].Function1(MinMap[MinMaxPosition].Struct_ID);
                        if (Map[Position].DataType == UInt16) {
                           Max = *((UINT16 *) (MinMap[MinMaxPosition].ptrmax));

                           Min = *((UINT16 *) (MinMap[MinMaxPosition].ptrmin));

                           if (ParamId == WELDSCALEINDEX || ParamId == J3_32_IN || ParamId == J3_33_IN
                                 || ParamId == J3_19_IN || ParamId == J3_17_IN || ParamId == J3_31_IN
                                 || ParamId == J3_1_IN || ParamId == J3_8_OUT || ParamId == J3_36_OUT
                                 || ParamId == J3_22_OUT) {

                              FormattedMax = Max;
                              FormattedMin = Min;
                              for (MaxBit = 0; MaxBit <= 13; MaxBit++) {
                                 if ((FormattedMax >> MaxBit) & 1)   //For Radio index type preset parameter we are sending bit position value
                                    break;
                              }
                              for (MinBit = 0; MinBit <= 10; MinBit++) {
                                 if ((FormattedMin >> MinBit) & 1) break;
                              }
                              FormattedMax = MaxBit;
                              FormattedMin = MinBit;
                           }
                           else {
                              FormattedMax = ConvertInternalExternal(Max, Map[Position].UnitFormat, CurrentSetup.Units);
                              FormattedMin = ConvertInternalExternal(Min, Map[Position].UnitFormat, CurrentSetup.Units);
                           }
                         }
                        else {
                           Max = *((SINT32 *) (MinMap[MinMaxPosition].ptrmax));
                           FormattedMax = ConvertInternalExternal(Max, Map[Position].UnitFormat, CurrentSetup.Units);
                           Min = *((SINT32 *) (MinMap[MinMaxPosition].ptrmin));
                           FormattedMin = ConvertInternalExternal(Min, Map[Position].UnitFormat, CurrentSetup.Units);
                        }
                     }
                     MinMaxPosition++;
                  }
                  Temp1 = JsonParamId;
                  GlobalCommandID = Map[Position].Struct_ID;
                  JsonParamvalue = strnstr(Temp1, "ParamValue\":", CurlyEndPtr - Temp1);
                  if (JsonParamvalue) {
                     if (ParamId == TIMEDATA || ParamId == DATEDATA) {
                        JsonParamvalue = strnstr(Temp1, "ParamValue\":\"", CurlyEndPtr - Temp1);   //make sure array type parameter values start after :"
                        if (JsonParamvalue) {
                           JsonParamvalue += PARAMARRAYSTRLEN;
                           if (ParamId == TIMEDATA)
                              ret = CheckTimeValue(JsonParamvalue);
                           else
                              ret = CheckDateValue(JsonParamvalue);
                           AfterArrPtr = JsonParamvalue;
                           if (ret == VALID) {
                              if (Map[Position].Function2 != NULL) Map[Position].Function2();
                              sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                              UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                           }
                           else {
                              sprintf(Response, "{\"ErrorCode\":%d,"
                                    "\"%s\":%ld}", INVALID_SERVICE_DATA, "ParamId", ParamId);
                              JsonStr = NULL;
                           }
                        }
                        else {
                           sprintf(Response, "{\"ErrorCode\":%d,"
                                 "\"%s\":%ld}", INVALID_SERVICE_DATA, "ParamId", ParamId);
                           JsonStr = NULL;
                        }

                     }
                     else if ((ParamId == BARCODESTART) || (ParamId == STACKASSEMBLYNUM) || (ParamId == ACTASSEMBLYNUM)
                           || (ParamId == PSASSEMBLYNUM)) {
                        Temp1 = JsonParamId;
                        JsonParamvalue = strnstr(Temp1, "ParamValue\":\"", CurlyEndPtr - Temp1);   //make sure array type parameter values start after :"
                        if (JsonParamvalue) {
                           JsonParamvalue += PARAMARRAYSTRLEN;
                           Temp = strnchr(JsonParamvalue, '"', PostDataLen - (JsonParamvalue - PostDataPtr));
                        }
                        else
                           Temp = 0;   //To assert INVALID_SERVICE_DATA error

                        if (Temp) {
                           *Temp = '\0';
                           AfterArrPtr = Temp + 1;
                           strncpy(JsonParamValueArr, JsonParamvalue, sizeof(JsonParamValueArr) - 1);
                           SINT8 *Arr = (SINT8*) (Map[Position].Vptr);
                           strncpy((SINT8*) ParamOldVal, (SINT8 *) Arr, sizeof(ParamOldVal) - 1);
                           strncpy((SINT8*) ParamNewVal, (SINT8 *) (JsonParamValueArr), sizeof(ParamNewVal) - 1);
                           Type = arr;
                           if (ParamId == BARCODESTART)
                              strncpy((SINT8*) Arr, (SINT8 *) (JsonParamValueArr), 1);
                           else
                              strncpy((SINT8*) Arr, (SINT8 *) (JsonParamValueArr),
                              MAX_ASSEM_NUM_SIZE - 1);
                            if (Map[Position].Function2 != NULL) Map[Position].Function2();
                           UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                           sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                           JsonParamvalue = 0;
                        }
                        else {
                           sprintf(Response, "{\"ErrorCode\":%d,"
                                 "\"%s\":%ld}", INVALID_SERVICE_DATA, "ParamId", ParamId);
                           JsonStr = NULL;
                        }
                     }
                     else {
                        JsonParamvalue += PARAMVALUESTRLEN;
                        SkipSpace(JsonParamvalue);
                        ErroCode = stringsplit(JsonParamvalue, Map[Position].UnitFormat, CurrentSetup.Units,
                              &ParamValue);
                        Temp = JsonParamvalue;
                        if (ErroCode == SUCCESS) {
                           MinMaxPosition = 0;
                           ExitFlag = FALSE;

                           if ((ParamValue >= FormattedMin) && (ParamValue <= FormattedMax)) {
                                for (Indx = 0; Indx < NumUserIOIDs; Indx++) {
                                    if (UserIOParamIDs[Indx] == ParamId) {
                                    if (CheckUserIOIndex[Indx][ParamValue] == NOTASSIGNED)
                                       ErroCode = INVALID_USERIO_INPUT;
                                    else if ((ParamValue == USERIO_MISSINGPART_ID) && (ParamId == J3_8_OUT || ParamId == J3_36_OUT || ParamId == J3_22_OUT)) {
                                       if (CurrentSetup.Actuator != AED && CurrentSetup.Actuator != AES && CurrentSetup.Actuator != MICRO && CurrentSetup.Actuator != MICROC)
                                    	   ErroCode = INVALID_ACTUATOR_FOR_USERIO_INPUT;
                                    }
                                    else if ((ParamValue == USERIO_PARTPRESENT_ID || ParamValue == USERIO_CONFIRMREJECT_ID) && (ParamId != J3_22_OUT && ParamId != J3_36_OUT
                                           && ParamId != J3_8_OUT)) {
                                       if (CurrentSetup.Actuator != AED && CurrentSetup.Actuator != AES && CurrentSetup.Actuator != MICRO && CurrentSetup.Actuator != MICROC) {
                                             ErroCode =INVALID_ACTUATOR_FOR_USERIO_INPUT;
                                         }
                                        }
                                       }
                                    }

                              if (ErroCode == SUCCESS) {
                                 FormattedNumber = ConvertExternalInternal(ParamValue, Map[Position].UnitFormat,CurrentSetup.Units);
                                 SetParamValue(Position, FormattedNumber);
                                 if (Map[Position].Function2 != NULL) {
                                    Map[Position].Function2(); //run function
                                    if (Map[Position].Vptr == &RadioIndex)
                                       memcpy(ParamOldVal, &RadioIndexOld, sizeof(UINT16));
                                 }
                                 sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
                                 UpdateCurrentPresetAndSetup(Map[Position].ParameterId);
                              }
                              else {
                                 sprintf(Response, "{\"ErrorCode\":%d,"
                                       "\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                                 JsonStr = NULL;
                              }

                           }
                           else {
                              SendMinMaxValue(ParamId, Position, Min, Max);
                              JsonStr = NULL;
                           }
                        }
                        else {
                           sprintf(Response, "{\"ErrorCode\":%d,"
                                 "\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                           JsonStr = NULL;

                        }
                     }   //ELSE END IF PARAMID IS NOT OF ARRAY TYPE
                  }   //IF END ,IF "ParamValue\":" FOUND IN POST DATA
                  else {
                     ErroCode = INVALID_SERVICE_DATA;
                     sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
                     JsonStr = NULL;
                  }
               }
            }   //IF END ,IF PARAMID FOUND IN THE MAP AARAY
            else {
               ErroCode = MISMATCH_PARAMID;
               sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErroCode, "ParamId", ParamId);
               JsonStr = NULL;
            }
         }   //if end
         else
            JsonStr = NULL;
         if (AfterArrPtr) Temp = AfterArrPtr;
         if (AfterReasonPtr) Temp = AfterReasonPtr;
         AfterReasonPtr = 0;
         AfterArrPtr = 0;
      }   //while end
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   ChangeReason[0] = 0;
   return Response;
}

void WebService::SetParamValue(UINT16 PositionInMap, UINT32 ReceiveValue)
/****************************************************************************/
/* This function receives data from Web client side and stores it into the desired */
/* place according to Map ID sent by Web Client. As Map ID corresponds to a   */
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
   memset(ParamNewVal, 0, sizeof(ParamNewVal));
   memset(ParamOldVal, 0, sizeof(ParamOldVal));
   DisableFlagOldValue = 0;
   DisableFlagNewValue = 0;
   Type = nothing;
   EventParameterID = (PARAM) Map[PositionInMap].ParameterId;
   switch (Map[PositionInMap].DataType) {
   case boolean:
      Type = boolean;
      if (ReceiveValue) {
         strcpy((SINT8*) ParamOldVal, "OFF");
         strcpy((SINT8*) ParamNewVal, "ON");
         *BoolPtr = TRUE;
      }
      else {
         strcpy((SINT8*) ParamOldVal, "ON");
         strcpy((SINT8*) ParamNewVal, "OFF");
         *BoolPtr = FALSE;
      }
      break;

   case Uint8:
   case sint8:
      Type = Uint8;
      memcpy(ParamOldVal, Uint8Ptr, sizeof(UINT8));
      *Uint8Ptr = (UINT8) (ReceiveValue);
      memcpy(ParamNewVal, Uint8Ptr, sizeof(UINT8));
      break;

   case UInt16:
   case sint16:
      Type = UInt16;
      memcpy(ParamOldVal, Uint16Ptr, sizeof(UINT16));
      *Uint16Ptr = ((UINT16) (ReceiveValue));
      memcpy(ParamNewVal, Uint16Ptr, sizeof(UINT16));

      break;

   case Uint32:
   case sint32:
      Type = Uint32;
      memcpy(ParamOldVal, Uint32Ptr, sizeof(UINT32));
      *Uint32Ptr = ReceiveValue;
      if (DisablePtr) {
         DisableFlagOldValue = *DisablePtr;
         SetDisableFlagStatus(DisablePtr, Map[PositionInMap].ParameterId);
         DisableFlagNewValue = *DisablePtr;
      }

      memcpy(ParamNewVal, Uint32Ptr, sizeof(UINT32));
      break;

   default:   // no data manipulation
      break;
   }

}

/*SINT32 CheckTimeValue(const SINT8 * string)
 * Purpose:
 * This function is called from  "SetSystemConfigValue()".
 * It is used to validate the string ,received in the post data ,to set with Timedata parameter.
 * Validation means , it will receive only two characters before and after the symbol ":" and discard the rest data.
 * After this ,it will set the data with corresponding variable if the validated data falls within the Min and Max range.
 * Entry condition:
 *	string- Pointer to the ParamValue data sent with JSON URI in case of POST request
 *Exit condition:
 * Return VALID ,if the requested data falls within the min and max range , otherwise return INVALID.
 */
SINT32 CheckTimeValue(const SINT8 * string)
{
   SINT8 TimeArr1[MAXTIMECHAR];
   SINT32 MaxDigit = 0;
   SINT32 digitcount = 0;
   SINT32 decimalcount = 0;
   BOOLEAN flag = FALSE;
   BOOLEAN Valid = TRUE;
   SINT32 Hour, Min;
   SINT32 Return = 0;
   while (*string != '\0' && MaxDigit < MAXTIMECHAR) {
      if (*string != ':') {
         if (digitcount != 2 && *string != '}') {
            TimeArr1[MaxDigit] = *string;
            digitcount++;
            MaxDigit++;
         }
         if (flag && (MaxDigit < MAXTIMECHAR)) {
            if (decimalcount != 3 && *string != '}') {
               TimeArr1[MaxDigit] = *string;
               decimalcount++;
               MaxDigit++;
            }
         }
      }
      else {
         TimeArr1[MaxDigit] = *string;
         MaxDigit++;
         flag = TRUE;
      }
      TimeArr1[MAXTIMECHAR - 1] = NULL;
      string++;
   }
   Hour = atoi(&TimeArr1[0]);
   Min = atoi(&TimeArr1[3]);
   if (Min < MINLIMIT_MINUTE || Min > MAXLIMIT_MINUTE || Hour < MINLIMIT_HOUR || Hour > MAXLIMIT_HOUR)
   /*Check for the valid entry of all variables.*/
   Valid = FALSE;
   if (Valid) {
      TimeArr[0] = Hour;
      TimeArr[1] = Min;
      Return = VALID;
   }
   else
      Return = INVALID;
   return Return;
}

/*SINT32 CheckDateValue(const SINT8 * string)
 * Purpose:
 * This function is called from  "SetSystemConfigValue()".
 * It is used to validate the string ,received in the post data ,to set with Datedata parameter.
 * Validation means , it will receive only two characters before and after the symbol "/" and discard the rest data.
 * After this ,it will set the data with corresponding variable if the validated data falls within the Min and Max range.
 * Entry condition:
 *	string- Pointer to the ParamValue data sent with JSON URI in case of POST request
 *Exit condition:
 * Return VALID ,if the requested data falls within the min and max range , otherwise return INVALID.
 */
SINT32 CheckDateValue(const SINT8 * string)
{
   SINT8 JsonDateArr[MAXDATECHAR];
   SINT32 MaxDigit = 0;
   SINT32 digitcount = 0;
   SINT32 decimalcount = 0;
   SINT32 Count = 0;
   BOOLEAN flag = FALSE;
   SINT32 repeat = 0;
   BOOLEAN repeatflag = FALSE;
   BOOLEAN Valid = TRUE;
   SINT32 ret = 0;
   SINT32 Day = 0;
   SINT32 Month = 0;
   SINT32 Year = 0;
   while (*string != '\0' && MaxDigit < MAXDATECHAR) {
      if (*string != '/') {
         if (digitcount != 2 && *string != '}') {
            JsonDateArr[MaxDigit] = *string;
            digitcount++;
            MaxDigit++;
         }
         if (flag && (MaxDigit < MAXDATECHAR)) {
            if (decimalcount != 2 && *string != '}') {
               JsonDateArr[MaxDigit] = *string;
               decimalcount++;
               MaxDigit++;
            }
         }
         if (repeatflag) {
            if (Count != 3 && *string != '}') {
               JsonDateArr[MaxDigit] = *string;
               Count++;
               MaxDigit++;
            }
         }
      }
      else {
         repeat++;
         if (repeat == 2) {
            repeatflag = TRUE;
            flag = FALSE;
         }
         JsonDateArr[MaxDigit] = *string;
         MaxDigit++;
         flag = TRUE;
      }

      JsonDateArr[MAXDATECHAR - 1] = NULL;
      string++;
   }
   if (CurrentSetup.Units == FALSE) {
      //Convert the variables from string to integer type.
      Month = atoi(&JsonDateArr[0]);
      Day = atoi(&JsonDateArr[3]);
      Year = atoi(&JsonDateArr[6]);
   }
   else {
      /*Convert the variables from string to integer type.*/
      Day = atoi(&JsonDateArr[0]);
      Month = atoi(&JsonDateArr[3]);
      Year = atoi(&JsonDateArr[6]);
   }

   /*Store the max. days for particular months.*/
   UINT16 MonthLength[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (CheckForLeapYear(Year))
	   MonthLength[1] = LEAPYEARVALUE;   //if leap year then make if 29
   /*Check for the valid entry of all variables.*/
   if (Month < MINLIMIT_MONTH || Month > MAXLIMIT_MONTH)
      Valid = FALSE;
   else if (Day < MINLIMIT_DAY || Day > MonthLength[Month - 1]) Valid = FALSE;
   if (Valid) {
      DateArr[0] = Month;
      DateArr[1] = Day;
      DateArr[2] = Year;
      ret = VALID;
   }
   else
      ret = INVALID;
   return ret;

}
/***************************************************************************/
/*Description:-                                                            */
/*  This function will check whether the entered value of the year is      */
/*  a leap year or not.                                                    */
/*Return:                                                                  */
/*  Return TRUE if the year is a leap year.                                */
/***************************************************************************/
BOOLEAN CheckForLeapYear(SINT32 Year)
{
   BOOLEAN Result;
   Year += CENTURY;

   if (Year % 4)
      Result = FALSE;
   else if (Year % 100)
      Result = TRUE;
   else if (Year % 400)
      Result = FALSE;
   else
      Result = TRUE;
   return (Result);
}

/*ServiceErrorCode stringsplit(const SINT8 * string, enum FORMAT format, BOOLEAN Metric, SINT32 * ParamVal)
 * Purpose:
 * This function is called from  "SetSystemConfigValue()" and "SetPresetValue()".
 * It is used to validate the string ,received in the post data ,to set with the parameter.
 * Validation means , it will receive   Max # of characters left of decimal point and right of the decimal point
 * available in the VarFormatTable and discard the rest of the data
 * and returns the modified data .
 * Entry condition:
 *	string- Pointer to the ParamValue data sent with JSON URI in case of POST request
 *	format - Format to display value in (PERCENT, DISTANCE, etc.)
 *	Metric-  Metric - TRUE if value should be displayed using metric units
 *Exit condition:
 * Return ErrorCode .
 */
ServiceErrorCode stringsplit(const SINT8 * string, enum FORMAT format, BOOLEAN Metric, SINT32 * ParamVal)
{

   ServiceErrorCode ErrorCode = SUCCESS;
   SINT32 StrDigitCount = 0;
   SINT32 StrDecimalCount = 0;
   SINT8 ModifiedArr[20];
   SINT32 i = 0;
   SINT32 TotalDigits = 0;
   BOOLEAN MaxDigitFlag = FALSE;
   BOOLEAN DPFlag = FALSE;
   SINT32 TypedVal = 0;
   SINT32 DigitCounter = 0;
   SINT32 DecimalCount = 0;
   SINT32 x;
   SINT32 NewVal = 0;
   BOOLEAN flag = FALSE;
   while (*string != '\0' && *string != ',' && *string != '}') {
      if (*string != '.' && (*string < '0' || *string > '9')) {
         ErrorCode = INVALID_SERVICE_DATA;
         break;
      }

      if (format != INTEGER && format != COUNTER && format != ON_OFF && format != STRING && *string != '.') {
         if (flag) {
        	 if(Metric)
        	 {
        		 if (StrDecimalCount != VarFormatTable[format].Metric.RightDigits + 1) {
        			 ModifiedArr[i] = *string;
        			 StrDecimalCount++;
        			 i++;
        		 }
        	 }
        	 else
        	 {
        		 if (StrDecimalCount != VarFormatTable[format].English.RightDigits + 1) {        
        		     ModifiedArr[i] = *string;
        		     StrDecimalCount++;
        		     i++;
        		 }
        	 }

         }
         else {   //{"Sid":0,"Preset":[{"ParamId":1,"ParamValue":55},{"ParamId":3,"ParamValue":555558858}]}
            if (StrDigitCount <= VarFormatTable[format].English.LeftDigits && flag == FALSE) {
               ModifiedArr[i] = *string;
               StrDigitCount++;
               i++;
            }
         }
      }
      else {
         flag = TRUE;
         ModifiedArr[i++] = *string;
         if ((i) >= (SINT32)(sizeof(ModifiedArr) - 1)) {//Coverity 12556
            ErrorCode = INVALID_SERVICE_DATA;
            break;
         }
      }
      ModifiedArr[i] = '\0';
      string++;//Coverity 12240
   }
   if (ErrorCode == SUCCESS) {
      SINT8* stringdata = ModifiedArr;
      if ((format == INTEGER) || (format == COUNTER) || (format == ON_OFF))
         NewVal = atoi(stringdata);
      else {
         while (*stringdata != '\0') {
            if (*stringdata != '.') {
               /* Here's that ENERGY special case again.  Go to ENERGYDIV10 */
               /* when user tries to enter too many digits to the left of */
               /* the decimal point. */
               if (format == ENERGY && MaxDigitFlag && !DPFlag) {
                  format = ENERGYDIV10;
                  MaxDigitFlag = FALSE;
               }
               if (!MaxDigitFlag) /* Check for Max digit entry allowed */
               {

                  TypedVal = (10 * TypedVal) + (*stringdata - '0');
                  DigitCounter++;
                  NewVal = TypedVal;
                  if (DPFlag) /* Are values entered after decimal point*/
                  {
                     DecimalCount++; /* # of digits after decimal point */

                     if (Metric) {
                        for (x = DecimalCount; x < (VarFormatTable[format].Metric.RightDigits); x++)
                           NewVal *= 10;
                        if (DigitCounter >= VarFormatTable[format].Metric.RightDigits) MaxDigitFlag = TRUE; /* Max Number of digits entered */
                     }
                     else {
                        for (x = DecimalCount; x < (VarFormatTable[format].English.RightDigits); x++)
                           NewVal *= 10;
                        if (DigitCounter >= VarFormatTable[format].English.RightDigits) MaxDigitFlag = TRUE; /* Max Number of digits entered */
                     }
                  }
                  else {
                     if (Metric) {
                        for (x = 0; x < VarFormatTable[format].Metric.RightDigits; x++)
                           NewVal *= 10;
                        if (DigitCounter >= VarFormatTable[format].Metric.LeftDigits) MaxDigitFlag = TRUE; /* Max Number of digits entered */
                     }
                     else {
                        for (x = 0; x < VarFormatTable[format].English.RightDigits; x++)
                           NewVal *= 10;
                        if (DigitCounter >= VarFormatTable[format].English.LeftDigits) MaxDigitFlag = TRUE; /* Max Number of digits entered */
                     }
                  }
               }
            }
            else /* Point key */
            {
               if (!Metric) {
                  if (VarFormatTable[format].English.RightDigits && !DPFlag) {
                     DPFlag = TRUE;
                     if (((TotalDigits == 1)) || (TotalDigits == 0)) MaxDigitFlag = FALSE;
                     DigitCounter = 0;
                  }

               }
               else if (Metric) {
                  if (VarFormatTable[format].Metric.RightDigits && !DPFlag) {
                     DPFlag = TRUE;
                     if (((TotalDigits == 1)) || (TotalDigits == 0)) MaxDigitFlag = FALSE;
                     DigitCounter = 0;
                  }

               }
            }
            stringdata++;
         }
      }
   }
   *ParamVal = NewVal;
   return ErrorCode;
}

/*JsonResponsePtr WebService::GetSystemConfigorPresetValue(SINT8 * JsonStr, Service ServiceId)
 * Purpose:
 * This function is called from GetPresetValue() and GetSystemConfigValue().
 * It is used to  write the value of the requested PresetId and systemconfigId to the response buffer depending upon the serviceid
 * passed to it.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request
 *	ServiceId- This is the Id of the Json Service requested by the web client.
 * Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetSystemConfigorPresetValue(SINT8 * JsonStr, Service ServiceId)
{
   SINT8* JsonParamId = 0;
   SINT32 ParamId = 0;
   UINT16 Position;
   SINT8 FormattedParamValue[VGA_LINESIZE];
   FORMAT UnitType = INTEGER;
   memset(FormattedParamValue, 0, VGA_LINESIZE);
   SINT8 *STR = FormattedParamValue;
   SINT32 Val;
   BOOLEAN ArraryTypeFlag = FALSE;
   ServiceErrorCode ErrorCode;
   JsonParamId = strstr(JsonStr, "ParamId\":");
   if (JsonParamId) {
      JsonParamId += PARAMIDSTRLEN;
      SkipSpace(JsonParamId);
      ParamId = atoi(JsonParamId);
   }
   ErrorCode = CheckRequiredConditions(ServiceId);
   if(ErrorCode == SUCCESS)
   {
	   ErrorCode = CheckParmeterID(ServiceId, (PARAM) ParamId);
	   if (ErrorCode == SUCCESS) {
		   for (Position = 0; Map[Position].Struct_ID != -1; Position++) {
			   if (Map[Position].ParameterId == ParamId) {
				   MatcedParamId = TRUE;
				   UnitType = Map[Position].UnitFormat;
				   break;
			   }
		   }
	   }
	   if (ErrorCode != SUCCESS)
		   sprintf(Response, "{\"ErrorCode\":%d,"
	                      	  "\"%s\":%ld}", ErrorCode, "ParamId", ParamId);

	   else if (MatcedParamId) {
		   GlobalCommandID = Map[Position].Struct_ID;
		   if (Map[Position].Function1 != NULL) Map[Position].Function1();

		   switch (Map[Position].DataType) {
		   case Uint8:
		   case sint8:
			   FormatVariables(*((UINT8*) (Map[Position].Vptr)), UnitType, FormattedParamValue, LINESIZE, CurrentSetup.Units);
			   FormattedParamValue[LINESIZE] = 0;
			   STR = Trim_FillChar(FormattedParamValue);
			   break;
		   case boolean:
			   sprintf(STR, "%ld", *((BOOLEAN*) (Map[Position].Vptr)));
			   break;
		   case UInt16:
		   case sint16:
			   Val = *((UINT16 *) (Map[Position].Vptr));
			   FormatVariables(Val, UnitType, FormattedParamValue, LINESIZE, CurrentSetup.Units);
			   FormattedParamValue[LINESIZE] = 0;
			   STR = Trim_FillChar(FormattedParamValue);
			   break;
		   case Uint32:
		   case sint32:
			   FormatVariables(*((UINT32*) (Map[Position].Vptr)), UnitType, FormattedParamValue, LINESIZE,
					   CurrentSetup.Units);
			   FormattedParamValue[LINESIZE] = 0;
			   STR = Trim_FillChar(FormattedParamValue);
			   break;
		   case arr:
			   strncpy((SINT8*) STR, (SINT8*) (Map[Position].Vptr), sizeof(FormattedParamValue) - 1);
			   ArraryTypeFlag = TRUE;
			   break;
		   default:
			   break;

		   }
		   if (ArraryTypeFlag) {
			   if (ParamId == TIMEDATA) {
				   SINT8 time[10];
				   sprintf(time, "%d:%d", TimeArr[0], TimeArr[1]);
				   sprintf(Response, "{\"%s\":%d,"
						   "\"%s\":%ld,"
						   "\"%s\":\"%s\"}", "ErrorCode", SUCCESS, "ParamId", ParamId, "ParamValue", time);
			   }
			   else if (ParamId == DATEDATA) {
				   SINT8 date[12];
				   sprintf(date, "%d/%d/%d", DateArr[0], DateArr[1], DateArr[2]);
				   sprintf(Response, "{\"%s\":%d,"
						   "\"%s\":%ld,"
						   "\"%s\":\"%s\"}", "ErrorCode", SUCCESS, "ParamId", ParamId, "ParamValue", date);
			   }
			   else
				   sprintf(Response, "{\"%s\":%d,"
						   "\"%s\":%ld,"
						   "\"%s\":\"%s\"}", "ErrorCode", SUCCESS, "ParamId", ParamId, "ParamValue", STR);
		   	   }
		   else
			   sprintf(Response, "{\"%s\":%d,"
					   "\"%s\":%ld,"
					   "\"%s\":%s}", "ErrorCode", SUCCESS, "ParamId", ParamId, "ParamValue", STR);
	   }
	   else
	   {
		   ErrorCode = MISMATCH_PARAMID;
		   sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErrorCode, "ParamId", ParamId);
	                  	  JsonStr = NULL;
	   }
   }
   else
	   sprintf(Response, "{\"ErrorCode\":%d,\"%s\":%ld}", ErrorCode, "ParamId", ParamId);
	   	                  	  JsonStr = NULL;
   MatcedParamId = FALSE;
   return Response;
}

/*JsonResponsePtr WebService::GetPresetValue(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "GetPresetValue" received from the client.
 * It is used to  read the requested param id values from preset and write the value
 * to the response buffer.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request
 * Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetPresetValue(SINT8 * JsonStr)
{
   return GetSystemConfigorPresetValue(JsonStr, SERVICE_GETPRESET);

}

/*JsonResponsePtr WebService::GetSystemConfigValue(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "GetSystemConfigValue" received from the client.
 * It is used to  read the requested param id values from system configuration and write the values to
 * response buffer.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request
 * Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetSystemConfigValue(SINT8 * JsonStr)
{
   return GetSystemConfigorPresetValue(JsonStr, SERVICE_GETSYSTEMCONFIG);
}

/*JsonResponsePtr WebService::JsonRecallPreset(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "RecallPreset" received from the client.
 * It is used to recall the requested preset to current preset. Requested preset name is sent in reply
 * if there is no error in recalling.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request
 * Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::JsonRecallPreset(SINT8 * JsonStr)
{
   SINT8* JsonPresetnum = 0;
   UINT32 PresetNum = 0;
   UINT8 Width;UINT16 x;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_RECALLPRESET);
   if (ErroCode == SUCCESS) {
      JsonPresetnum = strstr(JsonStr, "PresetNum");
      if (JsonPresetnum) {
         JsonPresetnum += PRESETNUMSTRLEN;
         SkipSpace(JsonPresetnum);
         PresetNum = atoi(JsonPresetnum);
         x = PresetNum;
         if ((PresetNum > PRESET_0) && (PresetNum <= MAX_POSSIBLE_PRESET)) {
        	 //This extra condition here to make sure that low priority task dont stop
        	 //state machine from RecallPreset function while weld is going on. Notice the said behaviour in John's lab
        	 if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) && (IsGraphDrawing == FALSE))
        		 ErroCode = (ServiceErrorCode) RecallPreset(PresetNum);
        	 else
        		 ErroCode = SYSTEM_BUSY;
            if(ErroCode == SUCCESS)
            {
                //Skip the width for number in name string.
				if((x > 0) && (x <= MAX_2DIGITNUM))
				 Width = 2;
				else if((x >= MIN_3DIGITNUM) && (x <= MAX_3DIGITNUM))
					Width = 3;
				else
					Width = 4;
            	sprintf(Response, "{\"%s\":%d,"
                          	  "\"%s\":\"%s\"}", "ErrorCode", SUCCESS, "PresetName",PresetNamePtrs[PresetNum]+Width);
            }
            else
            	sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
         }
         else
            sprintf(Response, "{\"ErrorCode\":%d,\"Min\":%d,\"Max\":%d}", EXCEEDS_LIMITS, 1,MAX_POSSIBLE_PRESET);

      }
      else
         sprintf(Response, "{\"ErrorCode\":%d}", INVALID_JSON_FORMAT);

   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}

/*JsonResponsePtr WebService::JsonVerifyPreset(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "VerifyPreset" received from the client.
 * It is used to verify the preset requested by client through postdata.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */

JsonResponsePtr WebService::JsonVerifyPreset(SINT8 * JsonStr)
{
   SINT8* JsonPresetNum = 0;
   UINT32 PresetNumber = 0;
   BOOLEAN PresetVerified = FALSE;

   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_VERIFYPRESET);
   if (ErroCode == SUCCESS) {
      JsonPresetNum = strstr(JsonStr, "PresetNum\":");
      if (JsonPresetNum) {
         JsonPresetNum += PRESETNUMSTRLEN;
         SkipSpace(JsonPresetNum);
         PresetNumber = atoi(JsonPresetNum);
      }
      if ((PresetNumber > PRESET_0) && (PresetNumber <= MAX_POSSIBLE_PRESET)) {
         if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) && (IsGraphDrawing == FALSE))   //// Ok to recall preset since no weld in progress
            PresetVerified = RecallAndVerifyPreset(PresetNumber);
         if (PresetVerified)
            sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
         else
            sprintf(Response, "{\"ErrorCode\":%d}", PRESET_NOT_VERIFIED);
      }
      else
    	  sprintf(Response, "{\"ErrorCode\":%d,\"Min\":%d,\"Max\":%d}", EXCEEDS_LIMITS, 1,MAX_POSSIBLE_PRESET);

   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}

/*JsonResponsePtr WebService::SavePreset(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "SavePreset" received from the client.
 * It is used to assign name to the requested preset number if it is valid preset.
 * If the web client does not send any name to assign with the requested preset ,then an automatic generated name will be assigned to that preset.
 * and also send the auto generated name in the JSON Response to the client utility.
 * If any name send by the client utility ,then that preset name will be assigned to the requested preset.
 * Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SavePreset(SINT8 * JsonStr)
{
   SINT8* JsonPresetnum = 0;
   SINT8* JsonPresetname = 0;
   SINT8 *Temp = 0;
   UINT32 PresetNum = 0;
   SINT32 Indx = 0;
   SINT8 Preset_Name[PRESETLEN];
   memset(Preset_Name, 0, PRESETLEN);
   Ver1200Setups * PresetPtr;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_SAVEPRESET);
   if (ErroCode == SUCCESS) {
      JsonPresetnum = strstr(JsonStr, "PresetNum");
      if (JsonPresetnum) {
         JsonPresetnum += PRESETNUMSTRLEN;
         SkipSpace(JsonPresetnum);
         PresetNum = atoi(JsonPresetnum);
      }
      JsonPresetname = strstr(JsonStr, "PresetName\":\"");
      if (JsonPresetname) {
         JsonPresetname += PRESETNAMESTRLEN;
         SkipSpace(JsonPresetname);
         Temp = strnchr(JsonPresetname, '"', PostDataLen - (JsonPresetname - PostDataPtr));
         if (Temp) {
            *Temp = '\0';
            if (strlen(JsonPresetname) > (SINT32)(sizeof(CurrentPreset.PresetID) - 1)) {
               ErroCode = INVALID_SERVICE_DATA;
            }
            else {
               Indx = 0;
               strncpy(Preset_Name, JsonPresetname, sizeof(Preset_Name) - 1);
               while (Preset_Name[Indx]) {
                  if (!ValidPresetCharacter(Preset_Name[Indx])) {
                     ErroCode = INVALID_SERVICE_DATA;
                     break;
                  }
                  Indx++;
               }
            }
         }
         else
            ErroCode = INVALID_SERVICE_DATA;
      }
      if (ErroCode != SUCCESS)
         sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
      else {
         if ((PresetNum > PRESET_0) && (PresetNum <= MAX_POSSIBLE_PRESET)) {
            if ((CurrentSetup.AuthorityCheck == TRUE) && (WebService::SecurityLevel < SUPERVISOR)
                  && (FRAMPresetInfo[PresetNum].Locked == TRUE))
               sprintf(Response, "{\"ErrorCode\":%d}", INVALID_SECURITYLEVEL);
            else {
               VGAPresetNum = PresetNum;
               //PresetPtr = Readpreset(VGAPresetNum);

               if (strlen(Preset_Name) == 0)   //check whether preset name is given by user or not
                  GlobalCommandID = AUTO_NAME;   //if not provided by the user,then call for auto generated preset name
               else {
                  GlobalCommandID = ASSIGN_NAME;
                  strncpy(AssignNamePresetBuffer, Preset_Name, sizeof(AssignNamePresetBuffer) - 1);
               }
               if ((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) {
                  SaveNamedPreset();
                  PresetSaveOk();
                  PresetPtr = Readpreset(VGAPresetNum);
                  sprintf(Response, "{\"%s\":%d,"
                        "\"%s\":\"%s\"}", "ErrorCode", SUCCESS, "PresetName", PresetPtr->PresetID);
               }
               else
                  sprintf(Response, "{\"ErrorCode\":%d}", SYSTEM_BUSY);
            }
         }
         else
        	 sprintf(Response, "{\"ErrorCode\":%d,\"Min\":%d,\"Max\":%d}", EXCEEDS_LIMITS, 1,MAX_POSSIBLE_PRESET);
      }
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}

/*JsonResponsePtr WebService::GetUserCount(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetUserCount" received from the client.
 * It is used to get total number of Users available in the Server and returns the same  in the response buffer after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetUserCount(SINT8 * JsonStr)
{

   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETUSERCOUNT);
   if (ErroCode == SUCCESS)
      sprintf(Response, "{\"ErrorCode\":%d,\"TotalUserPresent\":%ld}", SUCCESS, FRAMUserIdObj.UserIDGlobalCount);
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   JsonStr = 0;
   return Response;
}

/*JsonResponsePtr WebService::GetUsers(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetUsers" received from the client.
 * It is used to write User data in the response buffer after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetUsers(SINT8 * JsonStr)
{
   SINT8* JsonFrom_Data = 0;
   SINT8* JsonTo_Data = 0;
   SINT32 From = 0;
   SINT32 To = 0;
   SINT32 i = 0;
   SINT32 Count = 0;

   JsonFrom_Data = strstr(JsonStr, "From\":");
   if (JsonFrom_Data) {
      JsonFrom_Data += FROMSTRLEN;
      SkipSpace(JsonFrom_Data);
      From = atoi(JsonFrom_Data);
   }
   JsonTo_Data = strstr(JsonStr, "To\":");
   if (JsonTo_Data) {
      JsonTo_Data += TOSTRLEN;
      SkipSpace(JsonTo_Data);
      To = atoi(JsonTo_Data);
   }

   if ((To == 0) && (From == 0)) {
      if (FRAMUserIdObj.UserIDGlobalCount > MAX_USER_PERREQUEST) {
         From = FRAMUserIdObj.UserIDGlobalCount - MAX_USER_PERREQUEST;
         To = FRAMUserIdObj.UserIDGlobalCount - 1;
         Count = MAX_USER_PERREQUEST;
      }
      else {
         From = 0;
         To = FRAMUserIdObj.UserIDGlobalCount;
         Count = FRAMUserIdObj.UserIDGlobalCount;
      }
   }
   else {
      if (From > FRAMUserIdObj.UserIDGlobalCount) {
         From = 0;
         if(FRAMUserIdObj.UserIDGlobalCount > MAX_USER_PERREQUEST)
        	 To = MAX_USER_PERREQUEST - 1;
         else
        	 To = FRAMUserIdObj.UserIDGlobalCount;
      }
      Count = To - From + 1;
   }
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETUSER);
   if (ErroCode == SUCCESS) {
      if (Count >= MAX_USER_PERREQUEST || (Count < 0) || (Count >FRAMUserIdObj.UserIDGlobalCount ))
         sprintf(Response, "{\"ErrorCode\":%d}", LARGENO_OF_DATA_REQUSTED);
      else if ((Count >= MAX_USER_PERREQUEST) || (From > 999) || (To > 999))
         sprintf(Response, "{\"ErrorCode\":%d}", LARGENO_OF_DATA_REQUSTED);
      else {
         sprintf(Response, "{\"ErrorCode\":%d", SUCCESS);
         strcat(Response + strlen(Response), ",\"UserDetails\":[");
         for (i = From; i <= To; i++) {
            strcat(Response + strlen(Response), "{");
            sprintf(Response + strlen(Response), "\"%s\":\"%s\""
                  ",\"%s\":\"%s\""
                  ",\"%s\":%d"
                  ",\"%s\":%d"
                  ",\"%s\":%ld"
                  ",\"%s\":%d"
                  ",\"%s\":\"%02d:%02d:%02d %02d-%02d-%02d\"", KeyUserDetail[USERID_USERID],
                  FRAMUserIdObj.UserDetail[i].UserId, KeyUserDetail[USERID_PASSWORD],
                  FRAMUserIdObj.UserDetail[i].Password, KeyUserDetail[USERID_USERLEVEL],
                  FRAMUserIdObj.UserDetail[i].UserLevel, KeyUserDetail[USERID_STATUS],
                  FRAMUserIdObj.UserDetail[i].Status, KeyUserDetail[USERID_PASSEXPTIME],
                  FRAMUserIdObj.UserDetail[i].PassExpTime, KeyUserDetail[USERID_ISFIRSTTIMELOGIN],
                  FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin, KeyUserDetail[USERID_CREATEMODIFYTIME],
                  FRAMUserIdObj.UserDetail[i].CreateModifyTime.Hour,
                  FRAMUserIdObj.UserDetail[i].CreateModifyTime.Minute,
                  FRAMUserIdObj.UserDetail[i].CreateModifyTime.Second,
                  FRAMUserIdObj.UserDetail[i].CreateModifyTime.Century_Month,
                  FRAMUserIdObj.UserDetail[i].CreateModifyTime.Day, FRAMUserIdObj.UserDetail[i].CreateModifyTime.Years);
            if (i == (Count - 1))
               strcat(Response + strlen(Response), "}");
            else
               strcat(Response + strlen(Response), "},");
            if (i == Count - 1) break;
         }
         strcat(Response + strlen(Response), "]}");
      }
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
   return Response;
}

/*JsonResponsePtr WebService::SetUser(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "SetUser" received from the client.
 * It is used to set/add a new user data after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::SetUser(SINT8 * JsonStr)
{
   ServiceErrorCode ErrorCode = CheckRequiredConditions(SERVICE_SETUSER);
   if (ErrorCode == SUCCESS) {
      AddOrModifyUser(JsonStr, ADD);
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode);

   return Response;
}

/*JsonResponsePtr WebService::UpdateUser(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "UpdateUser" received from the client.
 * It is used to Modify a user data after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::UpdateUser(SINT8 * JsonStr)
{
   ServiceErrorCode ErrorCode = CheckRequiredConditions(SERVICE_UPDATEUSER);
   if (ErrorCode == SUCCESS)
      AddOrModifyUser(JsonStr, MODIFY);
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode);

   return Response;
}

/*JsonResponsePtr WebService::AddOrModifyUser(SINT8 * JsonStr,UINT8 Operation)
 * Purpose:
 *  This function is called by Set and Update user services handler
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	Operation-ADD or Modify user
 *Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::AddOrModifyUser(SINT8 * JsonStr, UINT8 Operation)
{
   UINT8 accept_reject = 0;
   UINT8 response = -1;
   SINT8* JsonUserId = 0;
   SINT8* JsonPassword = 0;
   SINT8* jsonUserLevel = 0;
   SINT8* JsonStatus = 0;
   SINT8 *JSonChangeReason = 0;
   SINT8* JsonPass_ExpTime = 0;
   SINT8* Temp = 0;
   SINT8 *Temp2 = JsonStr;
   BOOLEAN found = FALSE;
   BOOLEAN UserLevelExceeds = FALSE;
   BOOLEAN StatusExceeds = FALSE;
   BOOLEAN PassExpTimeExceeds = FALSE;
   JsonTempUserId TempUserIdData;
   JsonTempUserId UserIdDataBackup;
   ServiceErrorCode ErrorCode = SUCCESS;
   JsonUserId = strstr(Temp2, "UserId\":\"");
   if (JsonUserId) {
      JsonUserId += USERIDSTRLEN;
      SkipSpace(JsonUserId);
      Temp = strnchr(JsonUserId, '"', PostDataLen - (JsonUserId - PostDataPtr));
      if (Temp) {
         Temp2 = Temp + 1;
         *Temp = '\0';
         if (strlen(JsonUserId) > (SINT32)(sizeof(useridData.UserId) - 1))
            ErrorCode = INVALID_SERVICE_DATA;
         else {
            strncpy(TempUserIdData.UserId, JsonUserId, sizeof(TempUserIdData.UserId) - 1);
         }
      }
      else
         ErrorCode = INVALID_SERVICE_DATA;
   }
   JsonPassword = strstr(Temp2, "Password\":\"");
   if ((ErrorCode == SUCCESS) && JsonPassword) {
      JsonPassword += PASSWORDSTRLEN;
      SkipSpace(JsonPassword);
      Temp = strnchr(JsonPassword, '"', PostDataLen - (JsonPassword - PostDataPtr));
      if (Temp) {
         Temp2 = Temp + 1;
         *Temp = '\0';
         response = Check_Password(JsonPassword);
         if (response == ACCEPTED)
            strncpy(TempUserIdData.Password, JsonPassword, sizeof(TempUserIdData.Password) - 1);
         else
            ErrorCode = INVALID_PASSWORD;
      }
      else
         ErrorCode = INVALID_SERVICE_DATA;
   }

   jsonUserLevel = strstr(Temp2, "UserLevel\":");
   if ((ErrorCode == SUCCESS) && jsonUserLevel) {
      jsonUserLevel += USERLEVELSTRLEN;
      SkipSpace(jsonUserLevel);
      TempUserIdData.UserLevel = (LEVEL) atoi(jsonUserLevel);
      if ((TempUserIdData.UserLevel < OPERATOR) || (TempUserIdData.UserLevel > EXECUTIVE))
      {
         ErrorCode = EXCEEDS_LIMITS;
         UserLevelExceeds = TRUE;
      }
      else if (TempUserIdData.UserLevel != OPERATOR && TempUserIdData.UserLevel != EXECUTIVE
            && TempUserIdData.UserLevel != TECHNICIAN && TempUserIdData.UserLevel != SUPERVISOR) ErrorCode =
            INVALID_SERVICE_DATA;
   }
   JsonStatus = strstr(Temp2, "Status\":");
   if ((ErrorCode == SUCCESS) && JsonStatus) {
      JsonStatus += STATUSSTRLEN;
      SkipSpace(JsonStatus);
      TempUserIdData.Status = (ActiveStatus) atoi(JsonStatus);

      if ((TempUserIdData.Status < Disabled) || (TempUserIdData.Status > Enabled))
      {
    	  ErrorCode = EXCEEDS_LIMITS;
    	  StatusExceeds = TRUE;
      }
   }
   JsonPass_ExpTime = strstr(Temp2, "PassExpTime\":");
   if ((ErrorCode == SUCCESS) && JsonPass_ExpTime) {
      JsonPass_ExpTime += PASSEXPTIMESTRLEN;
      SkipSpace(JsonPass_ExpTime);
      TempUserIdData.PassExpTime = atoi(JsonPass_ExpTime);
      if ((TempUserIdData.PassExpTime < MIN_PASSEXPTIME) || (TempUserIdData.PassExpTime > MAX_PASSEXPTIME))
      {
    	  ErrorCode =EXCEEDS_LIMITS;
    	  PassExpTimeExceeds = TRUE;
      }
   }
   if (ErrorCode == SUCCESS)
	   ErrorCode = CheckReasonRequired(SERVICE_SETUSER, (PARAM) 0);
   if (ErrorCode == REASON_REQUIRED) {
      JSonChangeReason = strstr(Temp2, "Reason\":\"");
      if (JSonChangeReason) {
         JSonChangeReason += REASONSTRLEN;
         Temp = strnchr(JSonChangeReason, '"', PostDataLen - (JSonChangeReason - PostDataPtr));
         if (Temp) {
            *Temp = '\0';
            if (strlen(JSonChangeReason) > 0) {
               strncpy(ChangeReason, JSonChangeReason,
               MAX_EVENTREASON_LEN - 1);
               ErrorCode = SUCCESS;
            }
         }
      }
   }
   if ((ErrorCode != SUCCESS) && (ErrorCode != EXCEEDS_LIMITS))
	   sprintf(Response, "{\"ErrorCode\":%d}", ErrorCode);
   else if(ErrorCode == EXCEEDS_LIMITS)
   {
	  if(UserLevelExceeds)
		  sprintf(Response, "{\"ErrorCode\":%d,\"MinUserLevel\":%d,\"MaxUserLevel\":%d}", EXCEEDS_LIMITS, OPERATOR,EXECUTIVE);
	  else if(StatusExceeds)
		  sprintf(Response, "{\"ErrorCode\":%d,\"MinStatus\":%d,\"MaxStatus\":%d}", EXCEEDS_LIMITS, Disabled,Enabled);
	  else if(PassExpTimeExceeds)
		  sprintf(Response, "{\"ErrorCode\":%d,\"MinPassExpTime\":%d,\"MaxPassExpTime\":%d}", EXCEEDS_LIMITS, MIN_PASSEXPTIME,MAX_PASSEXPTIME);
   }
   else   //All data is good. Now check the UserId exist
   {


	  strncpy(UserIdDataBackup.Password, useridData.Password, sizeof(useridData.Password) - 1);
	  strncpy(UserIdDataBackup.UserId, useridData.UserId, sizeof(useridData.UserId) - 1);
	  UserIdDataBackup.PassExpTime = useridData.PassExpTime;
	  UserIdDataBackup.UserLevel = useridData.UserLevel;
	  UserIdDataBackup.Status = useridData.Status;

      strncpy(useridData.Password, TempUserIdData.Password, sizeof(TempUserIdData.Password) - 1);
      strncpy(useridData.UserId, TempUserIdData.UserId, sizeof(TempUserIdData.UserId) - 1);
      useridData.PassExpTime = TempUserIdData.PassExpTime;
      useridData.UserLevel = TempUserIdData.UserLevel;
      useridData.Status = TempUserIdData.Status;
      if (Operation == ADD) {
         accept_reject = Check_ExistingUserDetails(ADD, 0);
         if (accept_reject == ACCEPTED) {
            useridData.IsFirstTimeLogin = FIRST_TIME_LOGIN;
            useridData.UnSuccessFullAttempts = 0;
            memcpy(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount], &useridData, sizeof(UserID));
            RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount].CreateModifyTime);
            FRAMUserIdObj.GlobalOpAuth = userOpAuth;
            FRAMUserIdObj.UserIDGlobalCount = FRAMUserIdObj.UserIDGlobalCount + 1;
            if (useridData.Status == Enabled) FRAMUserIdObj.ActiveUserIDCount++;
            AddModifyUserEventRecord(ADD, 0);
            sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
         }
         else
         {
        	 if (accept_reject == ID_EXIST)
        		 sprintf(Response, "{\"ErrorCode\":%d}", USEREXIST);
        	 else if (accept_reject == MAX_ACTIVE_USERS)
        		 sprintf(Response, "{\"ErrorCode\":%d}", EXCEEDS_ACTIVEUSER);
        	 else if (accept_reject == MAXIMUM_USERS_ADDED)
        		 sprintf(Response, "{\"ErrorCode\":%d}", EXCEEDS_TOTALUSER);
        	  strncpy(useridData.Password, UserIdDataBackup.Password, sizeof(UserIdDataBackup.Password) - 1);
              strncpy(useridData.UserId, UserIdDataBackup.UserId, sizeof(UserIdDataBackup.UserId) - 1);
              useridData.PassExpTime = UserIdDataBackup.PassExpTime;
        	  useridData.UserLevel = UserIdDataBackup.UserLevel;
        	  useridData.Status = UserIdDataBackup.Status;

         }
      }
      else {
         for (UserIdIndex = 0; UserIdIndex < FRAMUserIdObj.UserIDGlobalCount; UserIdIndex++) {
            if (strcmp(FRAMUserIdObj.UserDetail[UserIdIndex].UserId, useridData.UserId) == 0) {
               found = TRUE;
               break;
            }
         }
         if (found)
        	 accept_reject = Check_ExistingUserDetails(MODIFY, UserIdIndex);
         if (found && (accept_reject == ACCEPTED)) {
            if (FRAMUserIdObj.UserDetail[UserIdIndex].Status != useridData.Status) {
               if (useridData.Status == Enabled)
                  FRAMUserIdObj.ActiveUserIDCount++;
               else
                  FRAMUserIdObj.ActiveUserIDCount--;
            }
            AddModifyUserEventRecord(MODIFY, UserIdIndex);
            useridData.UnSuccessFullAttempts = 0;
            memcpy((UINT8*) &FRAMUserIdObj.UserDetail[UserIdIndex], (UINT8*) &useridData, sizeof(UserID));
            FRAMUserIdObj.GlobalOpAuth = userOpAuth;
            RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[UserIdIndex].CreateModifyTime);
            sprintf(Response, "{\"ErrorCode\":%d}", SUCCESS);
         }
         else
         {
            sprintf(Response, "{\"ErrorCode\":%d}", USERID_CHANGE_NOT_PERMITTED);
            strncpy(useridData.Password, UserIdDataBackup.Password, sizeof(UserIdDataBackup.Password) - 1);
            strncpy(useridData.UserId, UserIdDataBackup.UserId, sizeof(UserIdDataBackup.UserId) - 1);
            useridData.PassExpTime = UserIdDataBackup.PassExpTime;
            useridData.UserLevel = UserIdDataBackup.UserLevel;
            useridData.Status = UserIdDataBackup.Status;

         }
      }
   }
   return Response;
}

/*JsonResponsePtr WebService::GetAlarmCount(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetAlarmCount" received from the client.
 * It is used to get total number of alarm availble in the FRAM  and returns the same  in the response buffer after user authentication.
 * 	Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetAlarmCount(SINT8 * JsonStr)
{
   SINT32 AlarmCount = 0;
   if (FRAMAlarmLogObj.AlarmLogCount > MAX_ALARM_ENTRIES)
      AlarmCount = MAX_ALARM_ENTRIES;
   else
      AlarmCount = FRAMAlarmLogObj.AlarmLogCount;
   sprintf(Response, "{\"ErrorCode\":%d,\"TotalAlarmPresent\":%ld}", SUCCESS, AlarmCount);
   JsonStr = 0;
   return Response;
}

/*JsonResponsePtr WebService::GetAlarmLogData(SINT8 * JsonStr)
 * Purpose:
 * This is the handler function for the Url "GetAlarmLogData" received from the client.
 * It is used to send alarm data .
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI in case of POST request.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetAlarmLogData(SINT8 * JsonStr)
{
   AlarmLog * Buffer = new AlarmLog[MAX_ALARM_ENTRIES];
   SINT32 AlarmCount = 0,//number of alarms present
          ReadAlarmCount;//Number of alarms to read
   SINT8* JsonFrom_Data = 0;
   SINT8* JsonTo_Data = 0;
   SINT32 From = 0;//start point
   SINT32 To = 0;//end point
   AlarmCount = ReadAlarmLog(Buffer, (UINT32) MAX_ALARM_ENTRIES);   // Read Alarm in Local Buffer
   ServiceErrorCode ErrCode = SUCCESS;

   JsonFrom_Data = strstr(JsonStr, "From\":");
   if (JsonFrom_Data) {
      JsonFrom_Data += FROMSTRLEN;
      SkipSpace(JsonFrom_Data);
      From = atoi(JsonFrom_Data);
   }
   JsonTo_Data = strstr(JsonStr, "To\":");
   if (JsonTo_Data) {
      JsonTo_Data += TOSTRLEN;
      SkipSpace(JsonTo_Data);
      To = atoi(JsonTo_Data);
   }

   if ((To == 0) && (From == 0) && (AlarmCount > 0)) {

	   if(AlarmCount> (MAX_ALARM_PERREQUEST - 1))
	   {
		   To = AlarmCount - 1;        // SEND FIRST 50 ALARM DATA
		   From = To - (MAX_ALARM_PERREQUEST - 1);
	   }
	   else
		   To = AlarmCount - 1;   //Send all
   }
   else if((From > To) || (To >= MAX_ALARM_ENTRIES))
      ErrCode = INVALID_SERVICE_DATA;
   else if((From > (AlarmCount - 1)) || (To > (AlarmCount - 1)))
      ErrCode = DATA_NOT_FOUND_IN_SPECIFIEDRANGE;



   if (ErrCode ==  SUCCESS) {
      ReadAlarmCount = To - From + 1;
      //We have latest first in Alarm Log buffer. To keep from to consistent throughout from 0 to 0 should return
      //oldest entry. From AlarmCount - 1 To AlarmCount - 1 shall return latest entry.
      From = (AlarmCount - From - 1);
      To = (AlarmCount - To - 1);
      sprintf(Response, "{\"ErrorCode\":%d", SUCCESS);
      strcat(Response + strlen(Response), ",\"AlarmData\":[");
      for (SINT32 i = 0,Indx = From; Indx >= To; Indx--,i++) {
         strcat(Response + strlen(Response), "{");
         sprintf(Response + strlen(Response), "\"%s\":%ld"
               ",\"%s\":%ld"
               ",\"%s\":%ld"
               ",\"%s\":%d"
               ",\"%s\":\"%04X\""
               ",\"%s\":\"%s\""
               ",\"%s\":\"%s\""
               ",\"%s\":\"%s\""
               ",\"%s\":\"%02d:%02d:%02d %02d-%02d-%02d\"", KeyEventLog[ALARMLOG_ALARMNUM], Buffer[Indx].AlarmNum,
               KeyAlarmLog[ALARMLOG_CYCLENUM], Buffer[Indx].CycleNum, KeyAlarmLog[ALARMLOG_PRESETREVNUM],
               Buffer[Indx].PresetRevNum, KeyAlarmLog[ALARMLOG_PRESETNUM], Buffer[Indx].PresetNum,
               KeyAlarmLog[ALARMLOG_ALARMID], Buffer[Indx].AlarmID, KeyAlarmLog[ALARMLOG_USERID], Buffer[Indx].UserID,
               KeyAlarmLog[ALARMLOG_ACTASSEMBLYID], Buffer[Indx].ActuatorAssemblyID, KeyAlarmLog[ALARMLOG_PSASSEMBLYID],
               Buffer[Indx].PSAssemblyID, KeyAlarmLog[ALARMLOG_TS], Buffer[Indx].TS.Hour, Buffer[Indx].TS.Minute,
               Buffer[Indx].TS.Second, Buffer[Indx].TS.Century_Month, Buffer[Indx].TS.Day, Buffer[Indx].TS.Years);
         if (i == (ReadAlarmCount - 1))
            strcat(Response + strlen(Response), "}");
         else
            strcat(Response + strlen(Response), "},");

      }
      strcat(Response + strlen(Response), "]}");
   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErrCode);

   delete Buffer;
   return Response;
}

/*JsonResponsePtr WebService::ClearPreset(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "ClearPreset" received from the client.
 * It is used to clear the requested preset after user authentication.
 *  Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::ClearPreset(SINT8 * JsonStr)
{
   //VGAPresetNum
   SINT8* JsonPresetnum = 0;
   SINT32 PresetNum = 0;

   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_RECALLPRESET);
   if (ErroCode == SUCCESS) {
      JsonPresetnum = strstr(JsonStr, "PresetNum");
      if (JsonPresetnum) {
         JsonPresetnum += PRESETNUMSTRLEN;
         SkipSpace(JsonPresetnum);
         PresetNum = atoi(JsonPresetnum);

         if ((PresetNum > PRESET_0) && (PresetNum <= MAX_POSSIBLE_PRESET)) {
            VGAPresetNum = PresetNum;
            SetPresetClearFlags();
            ProcessPresetClear();
            sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
         }
         else
        	 sprintf(Response, "{\"ErrorCode\":%d,\"Min\":%d,\"Max\":%d}", EXCEEDS_LIMITS, 1,MAX_POSSIBLE_PRESET);

      }
      else
         sprintf(Response, "{\"ErrorCode\":%d}", INVALID_JSON_FORMAT);

   }
   else
      sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);

   return Response;
}
/*JsonResponsePtr WebService::GetPSVersionNum(SINT8 * JsonStr)
 * Purpose:
 *  This is the handler function for the Url "GetPSVersionNum" received from the client.
 * It is used to get power supply version number after user authentication.
 * 	Entry condition:
 *	JsonStr- Pointer to the data sent with JSON URI i case of POST request.
 *	PeerAddr- Address of the Client requesting/posting data through JSON URI.
 *  Exit condition:
 *  The pointer to buffer containing the Response in JSON format
 */
JsonResponsePtr WebService::GetPSVersionNum(SINT8 * JsonStr)
{
   GetSerialNumbers();
   SINT32 RetVal = 0;
   ServiceErrorCode ErroCode = CheckRequiredConditions(SERVICE_GETPSVERSIONNUM);
      if (ErroCode == SUCCESS) {
         RetVal = SendTCPRequest(REQFORSBCVERSION, 0, 0);
         if (RetVal > 0)
        	 sprintf(Response, "{\"%s\":%d"
        	 		   	   	   	 ",\"%s\":\"%s\""
        	 		   	   	   	 ",\"%s\":\"%s\""
        	 		   	   	   	 ",\"%s\":\"%s\"}",
        	 		   	   	   	 "ErrorCode", SUCCESS,
        	 		   	   	   	 "S/WVersion", SWVersionLabel,
        	 		   	   	   	 "SBCVersion", JSONSBCVersion,
        	 		   	   	   	 "P/SVersionNum",ps_ver);
         else
         {
           if(RetVal == DATA_REQUEST_TIMEOUT)
              sprintf(Response, "{\"ErrorCode\": %d}", SBC_DATA_TIMEOUT);
           else
              sprintf(Response, "{\"ErrorCode\": %d}", SBC_CONNECTION_TIMEOUT);
         }
      }
      else
         sprintf(Response, "{\"ErrorCode\":%d}", ErroCode);
	JsonStr = 0;
   return Response;
}

/*
 * Function increments the passed SINT8 pointer until a non space character is found. *
 */
void SkipSpace(SINT8 *&Source)
{
   while ((Source && Source[0] == ' '))
      Source++;
}

/*
 * Function extracts data from the buffer until it finds the FindChar.
 * Extracted data is stored in ValueBuff member varible of class
 */
void WebService::GetValAndIncrementBuffer(SINT8 ** Buff, SINT32 FindChar,char * DestinationBuff)
{
   SINT32 i = 0;
   SINT8 * ptr = *Buff;
   while ((*ptr != FindChar) && (i < MAXBUFFSIZEOFWELDDATA)) {
	   DestinationBuff[i] = *ptr;
      i++;
      ptr++;
   }
   ptr++;
   DestinationBuff[i] = 0;
   *Buff = ptr;
}

/*
 * Function creates TCP socket to be used to get weld history and event history data from
 * SBC
 */
SINT32 CreateTcpSocket()
{
   SINT32 Error, RetryCount;
   BOOLEAN ExitFlag = FALSE;
   sockaddr_in ClientService;
   ClientSocket = lwip_socket(AF_INET, SOCK_STREAM, PF_INET);
   ClientService.sin_family = AF_INET;
   ClientService.sin_addr.S_un.S_addr = JsonNetif->ipaddr.addr;

   ClientService.sin_port = htons(JSON_SRCPORT);
   Error = lwip_bind(ClientSocket, (sockaddr *) &ClientService, sizeof(ClientService));

   if (Error == SOCKET_ERROR) {
   }
   Error = CONNECTION_TIMEDOUT;//default value to declare connection timeout
   for (RetryCount = 0; (RetryCount < SBC_CONNECTION_RETRYCOUNT) && (ExitFlag == FALSE); RetryCount++) {
      ClientService.sin_family = AF_INET;
      ClientService.sin_port = htons(JSON_SRCPORT);
#if 1
      UINT32 SbcIP = JsonNetif->ipaddr.addr;
      SbcIP = SbcIP - 1;
#else
      UINT32 SbcIP = MakeIP(172, 16, 78, 14);
#endif
      ClientService.sin_addr.S_un.S_addr = SbcIP;
      if (lwip_connect(ClientSocket, (sockaddr *) &ClientService, sizeof(ClientService)) < 0)
         printf("Error in Connection");
      else
      {
         Error = COMM_OK;
         ExitFlag = TRUE;
      }
   }
   unsigned long val = 1;
   lwip_ioctl(ClientSocket, FIONBIO, &val);
   return Error;
}

/*
 * This function is used to send TCP request to SBC to get weld and Event History data
 */
SINT32 SendTCPRequest(SINT32 FieldId, SINT32 From, SINT32 To)
{
   *SBCResponseBuf = '\0';
   JsonPacket JTestPacket;    //Packet containg fileId,From and To pointer
   JTestPacket.FileId = FieldId;
   JTestPacket.From = From;
   JTestPacket.To = To;
   SINT32 RetVal = 0;
   SINT32 TotalData = 0;
   SINT32 DataRetryCount = SBC_DATA_RETRYCOUNT;
   JsonSBCDataHandshakepacket DatalenPacket;
   DatalenPacket.TotalExpectedData = 0;
   RetVal = CreateTcpSocket();    //Make a tcp socket to communicate with SBC
   if(RetVal == COMM_OK)
   {
      RetVal = send(ClientSocket, (SINT8*) &JTestPacket, sizeof(JTestPacket), 0);
      if (RetVal < 0)
      {
         RetVal = DATA_REQUEST_TIMEOUT;
      }
      else {
         if (FieldId == EVENTLOGFIELDID || FieldId == WELDHISTORYFIELDID) {
            do {
               RTOS::DelayMs(10);   //wait for data as the socket is non blocking. get the expected data length first
               RetVal = recv(ClientSocket, &DatalenPacket.TotalExpectedData, sizeof(DatalenPacket.TotalExpectedData), 0);
            } while ((RetVal <= 0) && (--DataRetryCount > 0));
            DataRetryCount = SBC_DATA_RETRYCOUNT;
            if (RetVal > 0 && DatalenPacket.TotalExpectedData > 0) {
               do {
                  RTOS::DelayMs(10);   //wait for data as the socket is non blocking
                  RetVal = recv(ClientSocket, SBCResponseBuf + TotalData,
                  MAX_SBC_RESPONSEBUFFLEN - TotalData, MSG_DONTWAIT);

                  if (RetVal > 0) {
                     TotalData = TotalData + RetVal;
                     DataRetryCount = SBC_DATA_RETRYCOUNT;
                     if (TotalData >= DatalenPacket.TotalExpectedData) DataRetryCount = 0;
                  }

               } while ((TotalData < DatalenPacket.TotalExpectedData) && (DataRetryCount-- > 0));
               //Done receiving data. Check the length of data received against expected
               if(TotalData < DatalenPacket.TotalExpectedData)
                  RetVal = DATA_REQUEST_TIMEOUT;
               else
                  RetVal = TotalData;
            }
            else
            {
               if(RetVal <= 0)//did not receive any thing in expected data len
                  RetVal = DATA_REQUEST_TIMEOUT;
               else if(DatalenPacket.TotalExpectedData == 0)//received some thing but the range is not correct
                  RetVal = DATA_NOT_IN_SPECIFIEDRANGE;
            }
         }
         else if (FieldId == REQFOREVENTLOGCOUNT || FieldId == REQFORWELDLOGCOUNT) {
            JsonFileCount = 0;
            do {
               RTOS::DelayMs(10);   //wait for data as the socket is non blocking
               RetVal = recv(ClientSocket, (SINT8*) &JsonFileCount, sizeof(JsonFileCount), MSG_DONTWAIT);
            } while ((RetVal <= 0) && (--DataRetryCount > 0));
            if(RetVal <= 0)//did not receive any thing from SBC
                 RetVal = DATA_REQUEST_TIMEOUT;
         }
         else if (FieldId == REQFORSBCVERSION) {
            do {
            RTOS::DelayMs(10);   //wait for data as the socket is non blocking
            RetVal = recv(ClientSocket, (SINT8*)&JSONSBCVersion, sizeof(JSONSBCVersion), MSG_DONTWAIT);
           } while ((RetVal <= 0) && (--DataRetryCount > 0));
           if(RetVal <= 0)//did not receive any thing from SBC
                 RetVal = DATA_REQUEST_TIMEOUT;
         }

         if (FieldId == EVENTLOGFIELDID)
            nRecords = TotalData / sizeof(JsonEvent_Log);
         else if (FieldId == WELDHISTORYFIELDID) SBCResponseBuf[TotalData] = 0;
		 //Coverity fix 12558
         else if ((FieldId == REQFORSBCVERSION) && (RetVal >= 0))
        	 JSONSBCVersion[RetVal] = '\0';

      }
      lwip_close(ClientSocket);
      ClientSocket = INVALID_SOCKET;
   }
   return RetVal;
}

/*
 * This function is used to verify the Password in SystemLogin service
 */
SINT32 Check_Password(SINT8 *Password1)
{

   UINT8 pwd_length = 0;
   UINT8 count = 0;
   BOOLEAN Caps = FALSE;
   BOOLEAN Small = FALSE;
   BOOLEAN Special = FALSE;
   BOOLEAN Number = FALSE;
   BOOLEAN length = FALSE;
   SINT32 RetVal;

   pwd_length = strlen(Password1);

   if (!(pwd_length >= 8 && pwd_length <= 10))
      RetVal = INVALID_PASSWORD;
   else
   {
      length = TRUE;
	  for (count = 0; count < pwd_length; count++) {
		  if (Password1[count] >= 'A' && Password1[count] <= 'Z')   //checks for atleast one caps
			 Caps = TRUE;
		  else if (Password1[count] >= 'a' && Password1[count] <= 'z')   //checks for atleast one small letter
			 Small = TRUE;
		  else if (Password1[count] >= '0' && Password1[count] <= '9')   //checks for atleast one num
			 Number = TRUE;
		  else if (Password1[count] != ' ')   //checks for special character available except space
			 Special = TRUE;
	   }

	   if (Caps && Small && Number && Special && length)
		  RetVal = ACCEPTED;
	   else
		  RetVal = INVALID_PASSWORD;
   }
   return RetVal;
}

/**
 * 	Timer handling for Sessions.
 */
void WebService::Tick(int callbackus)
{
   if ((SessionStarttime > 0) && (RequestInProgress == FALSE) && (JsonUserLoggedIn == TRUE)
         && ((ReadOnlyTimer - SessionChecktime) >= (WebService::IdealLogOutTimeForWebClient) ))
	   SessionLogOut();
   callbackus = 0;
}

UINT8 WebService::VerifyUsernamePassword(void) {
	UINT8 ids = (UINT8) WRONG_NAME_PASSWORD; //take default as not verified
	UINT32 created_days = 0;
	int i = 0;
	RTClock::GetCurrentTime(&RTCMenu);
	for (i = 0; i < FRAMUserIdObj.UserIDGlobalCount; i++) {
		/* new condition included for number of unsuccessfull attempts*/
		if ((strcmp(CurrUserID, FRAMUserIdObj.UserDetail[i].UserId) == 0) && (strcmp(CurrPassword, FRAMUserIdObj.UserDetail[i].Password)!= 0))
		{
			FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts++;
			if ((FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts
					>= MAX_UNSUCCESSFULL_LOGIN_ATTEMPTS)
					&& (FRAMUserIdObj.UserDetail[i].Status == Enabled)) {
				FRAMUserIdObj.UserDetail[i].Status = Disabled;
				FRAMUserIdObj.ActiveUserIDCount--;
				ids = (UINT8) MAX_WRONG_ATTEMPTS;
			}
		}
		else if ((strcmp(CurrUserID, FRAMUserIdObj.UserDetail[i].UserId) == 0) &&
				 (strcmp(CurrPassword, FRAMUserIdObj.UserDetail[i].Password) == 0))
		{
			FRAMUserIdObj.UserDetail[i].UnSuccessFullAttempts = 0; //reset attemps
			//if ((CurrentSetup.Automation == ON)	&& (FRAMUserIdObj.UserDetail[i].UserLevel < SUPERVISOR))
			if (FRAMUserIdObj.UserDetail[i].UserLevel < SUPERVISOR)
			{
				ids = (UINT8) LOW_AUTHORITY_ERROR;
			}
			else if (FRAMUserIdObj.UserDetail[i].Status == Enabled)
			{
				if(FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin != FIRST_TIME_LOGIN) UserLoggedIn = TRUE;
				ids = (UINT8) CORRECT_NAME_PASSWORD;
				memcpy(&WebService::CurrentUser, &FRAMUserIdObj.UserDetail[i],sizeof(UserID));
				WebService::CurrUserOpAuth = FRAMUserIdObj.GlobalOpAuth;
				WebService::SecurityLevel = FRAMUserIdObj.UserDetail[i].UserLevel;
				created_days = PasswordExpDays(&FRAMUserIdObj.UserDetail[i].CreateModifyTime);
			} else
				ids = (UINT8) WRONG_NAME_PASSWORD;//user is disabled.
			    //No need to check others.Password matched
			break;
		}
	}
	if ((FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin == FIRST_TIME_LOGIN) && (ids == CORRECT_NAME_PASSWORD)) //the user verified and he he the firs time user
	{
		ids = (UINT8) FIRST_TIME_LOGIN;
	}
	if ((ids == CORRECT_NAME_PASSWORD) && (created_days >= FRAMUserIdObj.UserDetail[i].PassExpTime)) //usr exists and his password expires
	{
		ids = (UINT8) PASSWORD_EXPIRED;
	}
	if ((FRAMUserIdObj.UserDetail[i].IsFirstTimeLogin == EXECUTIVE_PASSWORD_CHANGE) && (ids == CORRECT_NAME_PASSWORD)) //the user verified and he was change by executive
	{
		ids = (UINT8) EXECUTIVE_PASSWORD_CHANGE;
	}
	return ids;
}

BOOLEAN WebService::CheckOperatorAuthority(OpAuth Func)
{
	BOOLEAN RetValFlag = FALSE;
	if((CurrentSetup.Automation == ON) || (CurrentSetup.AuthorityCheck == FALSE) ||
	(WebService::CurrentUser.UserLevel > OPERATOR) ||(WebService::CurrUserOpAuth & Func) == (Func))
		RetValFlag = TRUE;
	return RetValFlag;

}
