
/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/Events.cpp_v   1.12   08 Apr 2015 13:42:46   AnPawar  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/Events.cpp_v  $
 * 
 *    Rev 1.12   08 Apr 2015 13:42:46   AnPawar
 * Changes for Pressure Stepping and Record Event for Authority Check Change. 
 * 
 *    Rev 1.11   01 Apr 2015 13:01:52   amaurya
 * RESERVED0 replaced with EVENT_AUTHORITY_CHECK_CHANGED for authority check event.
 * 
 *    Rev 1.10   11 Mar 2015 09:15:08   amaurya
 * Setup limits parameters added to  ParameterID_Format[] for event description preparation.
 * 
 *    Rev 1.9   30 Jan 2015 08:09:48   amaurya
 * HOLD_PRESSURE_FLAG added ParameterID_Format[].
 * 
 *    Rev 1.8   08 Jan 2015 03:02:48   AnPawar
 * printf removed and flowcontrol format changed to percent
 * 
 *    Rev 1.7   02 Jan 2015 04:01:10   rjamloki
 * PRESSURE2 added in ParameterID_Format[] for weld and hold pressure
 * 
 *    Rev 1.6   28 Nov 2014 07:35:04   rjamloki
 * Eventreason pop up removed for EVENT_PARAMETER_CHANGED.
 * 
 *    Rev 1.5   11 Nov 2014 06:07:12   AnPawar
 * Cleaned up to remove extra events
 * 
 *    Rev 1.4   10 Nov 2014 04:48:50   AnPawar
 * Removed events from EventIDGroup array.Added new parameter format in ParameterID_Format array.
 * 
 *    Rev 1.3   06 Oct 2014 06:32:30   AnPawar
 * EventIDGroup array changed.SetEventReason(),WriteEventHistory() function changed.
 * 
 *    Rev 1.2   03 Oct 2014 06:04:58   rjamloki
 * included file WebService.h
 * 
 *    Rev 1.1   26 Sep 2014 03:25:22   rjamloki
 * Added change reason required for History and Event log clear
 * 
 *    Rev 1.0   11 Sep 2014 10:54:48   rjamloki
 * Initial revision.
*/

#include "Events.h"
#include "param.h"
#include "menu.h"
#include "util.h"
#include "command.h"
#include "ALARMS.H"
#include "graphs.h"
#include "WebService.h"

BOOLEAN EventReasonFlag = FALSE;
BOOLEAN VGAEventReasonFlag = FALSE;
UINT32 EventHistCountTemp = 0;
UINT32 EventNumRequiresReason = 0;
char EventReasonString[52];
EDIT_PARAM_TYPE EventParameterID;
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
UINT8 ParamNewVal[MAX_EVENTDATA_LEN];
UINT8 ParamOldVal[MAX_EVENTDATA_LEN];
UINT16 DisableFlagOldValue;
UINT16 DisableFlagNewValue;
UINT16 RadioIndexOld;
UINT16 RadioIndexNew;
UINT16 PresetRevValidationEvent;
DataType Type;

FORMAT ParameterID_Format[]={
		   /*ALLEMPTY*/ ON_OFF,                  /* Must be first entry in list           */
		   /*ABAMP*/ PERCENT,
		   /*ABSOLUTE*/ON_OFF,
		   /*ABDELAY*/TIME,
		   /*ABFLAG*/ ON_OFF,
		   /*ABTIME*/ TIME,
		  /*ABSCUTOFFDIST*/DISTANCE,
		  /* ABSCUTOFFFLAG*/ON_OFF,
		   /*ABSDIST*/DISTANCE,
		   /*ABSMLR*/DISTANCE,
		   /*ABSMLS*/DISTANCE,
		   /*ABSPLR*/DISTANCE,
		   /*ABSPLS*/DISTANCE,
		   /*ACTCLEARDIST*/DISTANCE,
		   /*ACTCLEARFLAG*/ON_OFF,
		   /*AMP1*/PERCENT,
		   /*AMPTRIGABSVALUE*/PERCENT,
		   /*AMPTRIGCOLVALUE*/DISTANCE,
		   /*AMPTRIGEXTFLAG*/ ON_OFF,
		   /*AMPTRIGTIMEVALUE*/TIME,
		   /*AMPTRIGENERVALUE*/ENERGYDIV10,
		   /*AMPTRIGPOWERVALUE*/PERCENTX10,
		   /*AMP2FLAG*/ON_OFF,
		   /*AMP2*/PERCENT,
		   /*AMPSCRUBTIME*/PERCENT,
		   /*AUTOSCALEFLAG*/ON_OFF,
		   /*AUTOTRIGFLAG*/ON_OFF,
		   /*BATCHFUNCTION*/ON_OFF,
		   /*BATCHCOUNTWITHALARM*/ON_OFF,
		   /*BATCHCOUNTRESET*/ON_OFF,
		   /*BATCHCOUNT*/COUNTER,
		   /*CURRBATCHCOUNT*/COUNTER,
		   /*PS_ACTASSEMBLYNUM*/STRING,
		   /*PS_PSASSEMBLYNUM*/STRING,
		   /*PS_STACKASSEMBLYNUM*/STRING,
		   /*FLOWCONTROL*/PERCENT,
		   /*COLCUTOFFFLAG*/ON_OFF,
		   /*COLLCUTOFFDIST*/DISTANCE,
		   /*COLDIST*/DISTANCE,
		   /*COLMLR*/DISTANCE,
		   /*COLMLS*/DISTANCE,
		   /*COLPLR*/DISTANCE,
		   /*COLPLS*/DISTANCE,
		  /*CONTROLLIMITSFLAG*/ON_OFF,
		   /*CYCLEABORTFLAG*/ON_OFF,
		   /*DATETIME*/TIMEDATE,
		   /*DIGITALFILTERFLAG*/ON_OFF,
		   /*EBTIME*/TIME,
		   /*ENERGYBRAKING*/ON_OFF,
		   /*ENERGYCOMPFLAG*/ON_OFF,
		   /*ENERGYMAXVQS*/ENERGY,
		   /*ENERGYMINVQS*/ENERGY,
		  /*ENERGYML*/ENERGY,
		   /*ENERGYMLR*/ENERGY,
		   /*ENERGYMLS*/ENERGY,
		   /*ENERGYPL*/ENERGY,
		   /*ENERGYPLR*/ENERGY,
		   /*ENERGYPLS*/ENERGY,
		   /*EXTTRGDELAY*/ON_OFF,
		   /*FREQMLR*/FREQUENCY,
		   /*FREQMLS*/FREQUENCY,
		   /*FREQPLR*/FREQUENCY,
		   /*FREQPLS*/FREQUENCY,
		   /*PS_FREQOFFSET*/FREQOFFSET,
		   /*FREQOFFSETFLAG*/ON_OFF,
		   /*SBLMINFREQLIM*/FREQUENCY,
		   /*SBLMAXFREQLIM*/FREQUENCY,
		   /*PS_SBLMINFREQ*/FREQUENCY,
		   /*PS_SBLMAXFREQ*/FREQUENCY,
		   /*SBLFREQFLAG*/FREQUENCY,
		   /*GENERALALARMFLAG*/ON_OFF,
		   /*GROUNDDETECTFLAG*/ON_OFF,
		   /*HOLDFORCE*/FORCE,
		   /*WELDPRESSURE*/PRESSURE2,
		   /*HOLDPRESSURE*/PRESSURE2,
		   /*HOLDTIMEFLAG*/ON_OFF,
		   /*HORNID*/STRING,
		   /*MAXTIMEOUT*/TIME,
		   /*MISSINGPARTFLAG*/ON_OFF,
		   /*MISSINGMINFLAG*/ON_OFF,
		   /*MISSINGMAXFLAG*/ON_OFF,
		   /*MISSINGPARTMIN*/DISTANCE,
		   /*MISSINGPARTMAX*/DISTANCE,
		   /*PEAKPWR*/PERCENTX10,
		   /*PEAKPOWERCUTOFF*/ PERCENTX10,
		   /*PEAKPWRCUTOFFFLAG*/ON_OFF,
		   /*PEAKPWRMAXVQS*/PERCENTX10,
		   /*HOLDTIME*/TIME,
		   /*PEAKPWRMINVQS*/PERCENTX10,
		   /*PRESETID*/INTEGER,
		   /*POWERMLR*/PERCENTX10,
		   /*POWERMLS*/PERCENTX10,
		   /*POWERPLR*/PERCENTX10,
		   /*POWERPLS*/PERCENTX10,
		   /*MPRESSURELIMIT*/PRESSURE,
		   /*PS_PPRESSURELIMIT*/PRESSURE,
		   /*PPRESSURELIMITFLAG*/ON_OFF,
		   /*PRESSURELIMIT*/PRESSURE,
		   /*PRESETUPDATECMPLT*/ON_OFF,
		   /*PRETRIGFLAG*/INTEGER,
		   /*PRETRIGAMP*/PERCENT,
		   /*PRETRIGDELAY*/TIME,
		   /*PRETRIGDELAYFLAG*/ON_OFF,
		   /*PRETRIGDIST*/DISTANCE,
		   /*PRETRIGDISTANCEFLAG*/ON_OFF,
		   /*REJECTLIMITS*/ON_OFF,
		   /*REJECTLIMITSFLAG*/ON_OFF,
		   /*PEAKPOWER*/PERCENTX10,
		   /*REJRESET_REQFLAG*/ON_OFF,
		   /*RTDIST*/DISTANCE,
		   /*RTFLAG*/ON_OFF,
		   /*SCRUBTIME*/TIME,
		   /*SCRUBTIMEFLAG*/ON_OFF,
		   /*SEEKFUNFLAG*/ON_OFF,
		   /*SUSPECTLIMITS*/ON_OFF,
		   /*SUSPECTLIMITSFLAGS*/ON_OFF,
		   /*SUSRESET_REQ*/ON_OFF,
		   /*TESTAMP*/PERCENT,
		   /*TIMEMLR*/TIME,
		   /*TIMEMLS*/TIME,
		   /*TIMEPLR*/TIME,
		   /*TIMEPLS*/TIME,
		   /*TRIGGERDELAY*/TIME,
		   /*TRSDISTMLR*/DISTANCE,
		   /*TRSDISTMLS*/DISTANCE,
		   /*TRSDISTPLR*/DISTANCE,
		   /*TRSDISTPLS*/DISTANCE,
		   /*WELDTRIGGER*/FORCE,
		   /*TRIGGERDISTANCE*/DISTANCE,
		   /*TRIGGERFORCE*/FORCE,
		   /*TRIGGERDELAYFLAG*/ON_OFF,
		   /*TOTALABS_MAXVQS*/DISTANCE,
		   /*TOTALABS_MINVQS*/DISTANCE,
		   /*TOTALCOL_MAXVQS*/DISTANCE,
		   /*TOTALCOL_MINVQS*/DISTANCE,
		   /*TOTALCYC_TIMEMAXVQS*/TIME,
		   /*TOTALCYC_TIMEMINVQS*/TIME,
		   /*VALIDATEPS*/ON_OFF,
		   /*LOCKPS*/ON_OFF,
		   /*VELOCITYMLR*/VELOCITY,
		   /*VELOCITYPLR*/VELOCITY,
		   /*VERIFIED*/ON_OFF,
		   /*WELDCOL_MAXVQS*/DISTANCE,
		   /*WELDCOL_MINVQS*/DISTANCE,
		   /*WELDCOUNT*/COUNTER,
		   /*WELDENERGY*/ENERGY,
		   /*WELDMODE*/INTEGER,
		   /*WRITEIN1*/STRING,
		   /*WRITEIN2*/STRING,
		   /*WELDFORCEMLR*/FORCE,
		   /*WELDFORCEMLS*/FORCE,
		   /*WELDFORCEPLR*/FORCE,
		   /*WELDFORCEPLS*/FORCE,
		   /*WELDFORCEMAXVQS*/FORCE,
		   /*WELDFORCEMINVQS*/FORCE,
		   /*WELDSTATUSFLAG*/ON_OFF,
		   /*XSCALETIME*/TIME,
		   /*WELDTIMEMINVQS*/TIME,
		   /*WELDTIMEMAXVQS*/TIME,
		   /*PRESETCONFIGNUM*/INTEGER,
		   /*HWCONFIG*/INTEGER,
		   /*PMCHIGHLIMIT*/PERCENT,
		   /*PMCLOWLIMIT*/PERCENT,
		   /*PMCTIMEOUT*/INTEGER,
		   /*PMCCYCLECOUNT*/COUNTER,
		   /*PMCENABLED*/ON_OFF,
		   /*PMCPLUS_BANDFLAG*/ON_OFF,
		   /*PMCMINUS_BANDFLAG*/ON_OFF,
		   /*VQSLIMIT*/ON_OFF,
		   /*PS_FREQUENCY*/FREQUENCY,
		   /*POWER*/PERCENT,
		   /*VARIANT*/INTEGER,
		   /*DIPFLAG*/ON_OFF,
		   /*SWDIPSETTING*/ON_OFF,
		   /*SEEKAMPLITUDE*/PERCENT,
		   /*SEEKRAMPTIME*/TIME,
		   /*SEEKTIME*/TIME,
		   /*WELDTIME*/TIME,
		   /*SEEKFREQLIMITHIGH*/FREQUENCY,
		   /*SEEKFREQLIMITLOW*/FREQUENCY,
		   /*SEEKPHASELOOP*/INTEGER,
		   /*SEEKPHASELOOPCF*/INTEGER,
		   /*SEEKAMPLOOPC1*/INTEGER,
		   /*SEEKAMPLOOPC2*/INTEGER,
		   /*WELDAMPLITUDE*/PERCENT,
		   /*WELDRAMPTIME*/TIME,
		   /*WELDPHASELOOP*/INTEGER,
		   /*WELDPHASELOOPCF*/INTEGER,
		   /*WELDAMPLOOPC1*/INTEGER,
		   /*WELDAMPLOOPC2*/INTEGER,
		   /*WELDFREQLIMITHIGH*/FREQUENCY,
		   /*WELDFREQLIMITLOW*/FREQUENCY,
		   /*WELDPHASELIMIT*/INTEGER,
		   /*WELDPHASELIMIT_TIME*/TIME,
		   /*PMCDATA*/ON_OFF,
		   /*REV*/INTEGER,
		   /*XXCANTCHANGEXX*/ON_OFF,                /* For run screen if things cant change  */
		   /*SAVEPRESETZERO*/ON_OFF,
		   /*MAXFORCEMLR*/FORCE,
		   /*MAXFORCEMLS*/FORCE,
		   /*MAXFORCEPLR*/FORCE,
		   /*MAXFORCEPLS*/FORCE,
		   /*AMPLITUDESTEPFLAG*/ON_OFF,
		   /*AMPTRIGDISTVALUE*/DISTANCE,
		   /*AMPTRIGFORCEVALUE*/FORCE,
		   /*FORCESTEPFLAG*/ON_OFF,
		   /*AMPMODESTEPFLAG*/INTEGER,
		   /*DUPSMEMFLAG*/ ON_OFF,
		   /*DUPS_SEEK_FLAG*/ ON_OFF,
		   /*DOWNSPEEDPLR,*/VELOCITY,
		   /*DOWNSPEEDMLR(*/VELOCITY,
		   /*HOLD_PRESSURE_FLAG*/ON_OFF,
		   /*WELDPRESSURE_PLT*/PRESSURE2,
		   /*WELDPRESSURE_MLT*/PRESSURE2,
		   /*DOWNSPEED_PLT,*/PERCENT,
		   /*DOWNSPEED_MLT*/PERCENT,
		   /*HOLDPRESSURE_PLT*/PRESSURE2,
		   /*HOLDPRESSURE_MLT*/PRESSURE2,
		   /*HOLDTIME_PLT*/TIME,
		   /*HOLDTIME_MLT*/TIME,
		   /*AMPA_PLT*/PERCENT,
		   /*AMPA_MLT*/PERCENT,
		   /*TRIGFORCE_PLT*/FORCE,
		   /*TRIGFORCE_MLT*/FORCE,
		   /*WELDTIME_PLT*/TIME,
		   /*WELDTIME_MLT*/TIME,
		   /*WELDENERGY_PLT*/ENERGY,
		   /*WELDENERGY_MLT*/ENERGY,
		   /*PEAKPOWER_PLT*/PERCENTX10,
		   /*PEAKPOWER_MLT*/PERCENTX10,
		   /*COLLAPSEDIST_PLT*/DISTANCE,
		   /*COLLAPSEDIST_MLT*/DISTANCE,
		   /*ABSDIST_PLT*/DISTANCE,
		   /*ABSDIST_MLT*/DISTANCE,
		   /*SCRUBTIME_PLT*/TIME,
		   /*SCRUBTIME_MLT*/TIME,
		   /*SCRUBAMP_PLT*/PERCENT,
		   /*SCRUBAMP_MLT*/PERCENT,
		   /*TRIGDIST_PLT*/DISTANCE,
		   /*TRIGDIST_MLT*/DISTANCE,
		   /*PRESSURE_TRIGABSVALUE*/PERCENT,
		   /*PRESSURE_TRIGCOLVALUE*/DISTANCE,
		   /*PRESSURE_TRIGEXTFLAG*/ ON_OFF,
		   /*PRESSURE_TRIGTIMEVALUE*/TIME,
		   /*PRESSURE_TRIGENERVALUE*/ENERGYDIV10,
		   /*PRESSURE_TRIGPOWERVALUE*/PERCENTX10,
		   /*PRESSURE2_FLAG*/INTEGER,
		   /*PRESSURE_2*/PRESSURE2,
		   /*PRESSURE_1*/PRESSURE2,
		   /*AMP_1*/PERCENT,
		   /*PRSTPARMDEFID*/INTEGER,//Default argument for UpdateCurrentPresetAndSetup function.
            };


enum EventChangeReasons
{
	CHANGING_REASON_REQ = BIT(0),
	CHANGING_VALIDATED_PRESET = BIT(1),
};



EventIDs EventIDGroup[] = {
	  {/*EVENT_PARAMETER_CHANGED_ONVALIDATEDPS*/100, (CHANGING_REASON_REQ  | CHANGING_VALIDATED_PRESET),NULL},
	  {/*EVENT_PRESETVALIDATION_BITSET*/101,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_NEWUSER_CREATED*/102,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_USER_MODIFIED*/103,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_RTC_CHANGED*/104,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_FACTORY_AUTOMATION_MODE*/105,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_HARDWARE_ASSEMBLY_NUMBER_CHANGED*/106,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_HARDWARE_VERIFY_CHANGED*/107,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_SOFTWAREVERSION_CHANGED*/108,0,NULL},
	  {/*EVENT_AUTHORITY_CHECK_CHANGED*/109,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_ACTCOLD_START*/110,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_LOWBATTERY*/111,0,NULL},
	  {/*EVENT_CALIBRATION*/112,CHANGING_REASON_REQ,NULL},
	  {/*EVENT_PRESET_VALIDATION_BIT_CLEARED*/113,CHANGING_REASON_REQ,NULL},
      {/*EVENT_RESERVED1*/114,0,NULL},
      {/*EVENT_RESERVED2*/115,0,NULL},
      {/*EVENT_RESERVED3*/116,0,NULL},
      {/*EVENT_POWERON_CRC_CHANGED*/117,0,NULL},
      {/*EVENT_CLOCK_LOST*/118,0,NULL},
      {/*EVENT_RESERVED4*/119,0,NULL},
      {/*EVENT_PARAMETER_CHANGED*/202,0,NULL},
      {/*EVENT_RESERVED5*/203,0,NULL},
      {/*EVENT_RESERVED6*/204,0,NULL},
      {/*EVENT_RESERVED7 */208,0,NULL},
      {/*EVENT_RESERVED8*/209,0,NULL},
      {/*EVENT_RESERVED9*/301,0,NULL},
      {/*EVENT_RESERVED10*/302,0,NULL},
      {/*EVENT_HORN_SCAN_COMPLETED*/303,0,NULL},
      {/*EVENT_RESERVED11*/304,0,NULL},
      {/*EVENT_RESERVED12*/305,0,NULL},
      {/*EVENT_RESERVED13*/307,0,NULL},
      {/*EVENT_RESERVED14*/308,0,NULL},
      {/*EVENT_RESERVED15*/309,0,NULL},
      {/*EVENT_RESERVED16*/405,0,NULL},
      {/*EVENT_RESERVED17*/406,0,NULL},
      {/*EVENT_RESERVED18*/407,0,NULL},
      {/*EVENT_USERLOGIN*/ 501,0,NULL},
      {/*EVENT_USERLOGOUT*/502,0,NULL},
      {/*EVENT_RESERVED19*/409,0,NULL},
      {/*EVENT_RESERVED20*/410,0,NULL},
      {/*EVENT_RESERVED21*/414,0,NULL},
      {/*EVENT_RESERVED22*/415,0,NULL},
      {/*EVENT_FIRMWARE_UPLOAD,*/416,0,NULL},
      {/*EVENT_EVENT_ERROR*/ 999,0,NULL},
};


/* At Power-up this function is used to check whether the stored Events are valid or invalid
 * Once validated, this will not change until next ColdStart
 */
void PowerUpEventHistoryDataCheck(void)
{
   if(FRAMEventHistoryObj.EventHistoryCheckSum !=  EVENTHISTORYINITIALIZED_CHECKSUM){
      //CLEAR  FramEventHistoryObj in FRAM.
      FRAMEventHistoryObj. CircularIndex = -1;
      FRAMEventHistoryObj. EventHistoryCount = 0;
      FRAMEventHistoryObj. EventHistoryCheckSum = EVENTHISTORYINITIALIZED_CHECKSUM;
   }
}


/* this function fills the Event information and other relevant data to the structure.
 *
 * @parameter EventCode : event code has the information of Event ID
 * @return : No return value
 */
void GetEventHistoryData(UINT16 EventCode, char * OldData, char * NewData, Event_Log * EventHistoryData)
{
   RTCTime PresentTime;
   char EventID[MAX_EVENTID_STR_LEN];
   memset(EventID, 0 , sizeof(EventID));
   strncpy(EventID,"EV", sizeof(EventID) - 1);
   Numout2(EventCode, 10, &EventID[2], 3);
   //Update Time
   RTClock::GetCurrentTime(&PresentTime);
   EventHistoryData->TS.Years          = PresentTime.Years;
   EventHistoryData->TS.Century_Month  = PresentTime.Century_Month;
   EventHistoryData->TS.Day            = PresentTime.Day;
   EventHistoryData->TS.Hour           = PresentTime.Hour;
   EventHistoryData->TS.Minute         = PresentTime.Minute;
   EventHistoryData->TS.Second         = PresentTime.Second;

   EventHistoryData->EventNum      = FRAMEventHistoryObj.EventHistoryCount + EventHistCountTemp + 1;
   EventHistoryData->PresetNo      = CurrentSetup.ActivePreset;
   EventHistoryData->Rev  =  (PresetRevValidationEvent > 0)?PresetRevValidationEvent:CurrentPreset.Rev;
   EventHistoryData->ParameterId = EventParameterID;
   memset(EventHistoryData->EventReason, 0 , sizeof(EventHistoryData->EventReason));

   strncpy(EventHistoryData->DataOld, OldData,sizeof(EventHistoryData->DataOld)-1);
   strncpy(EventHistoryData->DataNew , NewData,sizeof(EventHistoryData->DataNew)-1);
   strncpy((char*)EventHistoryData->EventId, EventID, sizeof(EventHistoryData->EventId) - 1);
   strncpy((char*)EventHistoryData->PSSerialNumber, CurrentSetup.PSSerialNumber, sizeof(EventHistoryData->PSSerialNumber) - 1);
   if(CurrentSetup.Automation)
   	   strncpy((char*)EventHistoryData->UserId, AutomationUsrId, sizeof(EventHistoryData->UserId) - 1);
   else
   	   strncpy((char*)EventHistoryData->UserId, CurrentUser.UserId, sizeof(EventHistoryData->UserId) - 1);

   EventHistoryData->EventHistoryCRC = ByteCRC((UINT8*)EventHistoryData,sizeof(Event_Log) - sizeof(UINT16));

}
/***************************************************************************
*Purpose:                                                                  *
*   This function is called when user enters event reason from main menu   *
*   system configuration and logs an event                                 *
*   occurs                                                                 *
*Entry condition:                                                          *
*   Entry condition:                                                       *
*    none                                                                  *
*Exit condition:                                                           *
*   none                                                                   *
****************************************************************************/
void SetEventReason()
{
	SINT32 Indx;
	BOOLEAN ExitFlag = FALSE;
	SINT16 SearchIndex = FRAMEventHistoryObj.CircularIndex;
	if(strlen(EventReasonString) > 0){
		for(Indx = 0; (Indx < MAX_EVENT_ENTRIES) && (ExitFlag == FALSE); Indx++) {
			if(FRAMEventHistoryObj.EventHistoryObjs[SearchIndex].EventNum == EventNumRequiresReason) {
				strncpy((char*)FRAMEventHistoryObj.EventHistoryObjs[SearchIndex].EventReason,
						EventReasonString, sizeof(EventReasonString) - 1);
				memset(EventReasonString, 0 , sizeof(EventReasonString));//reset reason string
				EventNumRequiresReason = 0;
				ExitFlag = TRUE;
			}
			SearchIndex = (SearchIndex + 1) % MAX_EVENT_ENTRIES;
		}
		FRAMEventHistoryObj.EventHistoryCount += EventHistCountTemp;
		EventHistCountTemp = 0;
		EventReasonFlag = FALSE;
	}
	else
		VGAEventReasonFlag = TRUE;
}


/* this function records the  event that are generated to the NVRAM memory
 * This function implements a circular queue and adds new Event at the end of the list
 *
 * @parameter EventCode : Event code has the information of EventID
 * @parameter Data1 : Initial Value of the data change that caused an event
 * @parameter Data2 : Final Value of the data change that caused an event
 * @return : No return value
 */
void WriteEventHistory(UINT16 EventCode, char * Data1,char * Data2,UINT8 reqMask)
{

   Event_Log EventHistoryData;
   //Update Circular Index
   FRAMEventHistoryObj.CircularIndex = (FRAMEventHistoryObj.CircularIndex + 1) % MAX_EVENT_ENTRIES; //starts with 0
   GetEventHistoryData(EventCode, Data1, Data2, &EventHistoryData);
   memcpy(&FRAMEventHistoryObj.EventHistoryObjs[FRAMEventHistoryObj.CircularIndex],&EventHistoryData,sizeof(Event_Log));

   UINT8 condMask = CHANGING_REASON_REQ;
   if(CurrentPreset.Validated )
   	   condMask |= CHANGING_VALIDATED_PRESET;
   if((EventReasonFlag == TRUE) || ((reqMask != 0) && (reqMask & condMask) == reqMask)){
	   if(strlen(WebService::ChangeReason) > 0)
	   {
		   strncpy((char*)FRAMEventHistoryObj.EventHistoryObjs[FRAMEventHistoryObj.CircularIndex].EventReason,
				   WebService::ChangeReason, MAX_EVENTREASON_LEN - 1);
		   FRAMEventHistoryObj.EventHistoryCount++;
	   }
	   else
	   {
		   EventHistCountTemp++;
		   if(EventNumRequiresReason == 0)
			   EventNumRequiresReason = EventHistoryData.EventNum;
		   EventReasonFlag = TRUE;
		   VGAEventReasonFlag = TRUE;
	   }
   }
   else
	   FRAMEventHistoryObj.EventHistoryCount++;

}


/* this function is called to read the last LogsCount number of Event records \\
 * from the NVRAM and fills the buffer passed in the Logdata.
 *
 * @parameter LogData : Buffer where the Event records are copied
 * @parameter LogsCount : Count of Events that needs to be copied
 * @return TotalEvenyHistoryRead :Count of copied Events
 */
UINT32 ReadEventHistory(Event_Log * LogData, UINT32 LogsCount,UINT32 EventCounter)
{

    UINT32 Length = 0;
    UINT32 Index = 0, Indx1 = 0;
    SINT32 Indx2 = 0;
    Event_Log* Address = NULL;

    EventCounter = EventCounter % MAX_EVENT_ENTRIES; // for more than 100 event records on SBC
													// Index should wrap around
    // error checking. Cold Start Condition or No data
    if((FRAMEventHistoryObj.CircularIndex < 0) || (FRAMEventHistoryObj.CircularIndex > MAX_EVENT_ENTRIES) ||
    		(LogsCount == 0) || (LogsCount > MAX_EVENT_IN_ONE_PACKET))
       Length = 0;
    else {
	    Index = EventCounter + LogsCount - 1;
	   // then we can send the data without hitting the end of the list.
	    if(Index < MAX_EVENT_ENTRIES) {
	       Address = &FRAMEventHistoryObj.EventHistoryObjs[EventCounter];
	       for(Indx1 = 0; Indx1 < LogsCount; Indx1++) // copy previous LogsCount data
	          memcpy(LogData + Indx1, Address + Indx1, sizeof(Event_Log));
	       Length = LogsCount;
	    }
	    else {
	       Indx2 = 0;
	       Index = EventCounter;
	       Length = MAX_EVENT_ENTRIES - EventCounter;
	       Address = &FRAMEventHistoryObj.EventHistoryObjs[Index];
	       for(Indx1 = 0; Indx1 < Length; Indx1++, Indx2++)  // In this case Event Counter will be less than EVENTSINONEPACKET
	             memcpy(LogData + Indx2, Address + Indx1, sizeof(Event_Log));

	       Length = LogsCount - Length;
	       Index = 0;
	       Address = &FRAMEventHistoryObj.EventHistoryObjs[Index]; //Roll back to the end of the buffer
		   for (Indx1 = 0; Indx1 < Length; Indx2++, Indx1++)
	          memcpy(LogData + Indx2,Address + Indx1, sizeof(Event_Log));
	       Length = LogsCount;
	    }
    }
    return Length;
}

/***************************************************************************
*Purpose:                                                                  *
*   This is the overloaded function and called when any event occurs and   *
*   old and new values are of integer types                                *
*Entry condition:                                                          *
*   Entry condition:                                                       *
*   EventTypes Events: type of the event being logged                      *
*   UINT32 Data1: integer value of old data                                *
*   UINT32 Data2: integer value of new data                                *
*Exit condition:                                                           *
*   none                                                                   *
****************************************************************************/

void RecordEvents(EventTypes Events, UINT32 Data1, UINT32 Data2)
{
	char D1[MAX_EVENTDATA_LEN], D2[MAX_EVENTDATA_LEN];
	memset(D1, 0 , sizeof(D1));
	memset(D2, 0 , sizeof(D2));
	Numout2(Data1, 10, D1, MAX_EVENTDATA_LEN - 1);
	Numout2(Data2, 10, D2, MAX_EVENTDATA_LEN - 1);
	RecordEvents(Events, D1, D2);
}

/***************************************************************************
*Purpose:                                                                  *
*   This function is called when any event occurs                          *
*Entry condition:                                                          *
*   Entry condition:                                                       *
*   EventTypes Events: type of the event being logged                      *
*   char * Data1:pointer to string of old data                             *
*   char * Data2:pointer to string of new data                             *
*Exit condition:                                                           *
*   none                                                                   *
****************************************************************************/
void RecordEvents(EventTypes Events,char * Data1,char * Data2)
{
   UINT16 ID = 0;
   UINT8 reqMask = 0;
   if(CurrentSetup.ControlLevel >= LEVEL_c)
   {
		if((Events >= EVENT_PARAMETER_CHANGED_ONVALIDATEDPS) && (Events < EVENT_EVENT_ERROR)) {
			ID =  EventIDGroup[Events].EventID;
			reqMask = EventIDGroup[Events].EventReasonMask;
		}
		else {
			ID = EventIDGroup[EVENT_EVENT_ERROR].EventID;
			reqMask = EventIDGroup[Events].EventReasonMask;
		}
		WriteEventHistory(ID,Data1,Data2,reqMask);
   }
}

/***************************************************************************
*Purpose:                                                                  *
*   This function is called when any preset related parameter is changed   *
*   prepares the data based on data type and logs an event                 *
*Entry condition:                                                          *
*   Entry condition:                                                       *
*   DataType Type: type of the parameter being changed                     *
*   void * OldVal: pointer to old value array                              *
*   void * NewVal: pointer to new value array                              *
*Exit condition:                                                           *
*   none                                                                   *
****************************************************************************/
void RecordParamChangeEvent(void * OldVal, void * NewVal, DataType Type)
{
	UINT32 OldValue, NewValue;
	SINT8 OldParamValue[12], NewParamValue[12];
	UINT8 * Val1 = (UINT8 *)OldVal, *Val2 = (UINT8 *)NewVal;
	FORMAT ParamFormatOld, ParamFormatNew;
	ParamFormatOld = ParamFormatNew = ParameterID_Format[EventParameterID];
	memset(OldParamValue, 0, sizeof(OldParamValue));
	memset(NewParamValue, 0, sizeof(NewParamValue));

	switch (Type) {
	case Uint8:
	case sint8:
		OldValue = Val1[0];
		NewValue = Val2[0];
		break;
	case UInt16:
	case sint16:
		OldValue = ((UINT16)Val1[0] << 8) + (UINT16) (Val1[1]);
		NewValue = ((UINT16)Val2[0] << 8) + (UINT16) (Val2[1]);
		break;
	case Uint32:
	case sint32:
		OldValue = ((UINT32)Val1[0] << 24)
			+ ((UINT32) Val1[1] << 16) + ((UINT32)Val1[2]<< 8) + ((UINT32) Val1[3]);
		NewValue = ((UINT32)Val2[0] << 24)
			+ ((UINT32) Val2[1] << 16) + ((UINT32)Val2[2]<< 8) + ((UINT32) Val2[3]);
		break;
	default:
		OldValue = 0;
		NewValue = 0;
		break;
	}

	if((EventParameterID == ENERGYPLS) || (EventParameterID == ENERGYMLS)||
		(EventParameterID == ENERGYMLR) || (EventParameterID == ENERGYPLR)||
		(EventParameterID == WELDENERGY)||(EventParameterID == WELDENERGY_PLT )||(EventParameterID == WELDENERGY_MLT ))
	{
		if(OldValue > ENERGYPOINT)
			ParamFormatOld = ENERGYDIV10;
		if(NewValue > ENERGYPOINT)
			ParamFormatNew = ENERGYDIV10;
	}

	Val1 = (UINT8*)OldParamValue;
	Val2 = (UINT8*)NewParamValue;
	if((ParamFormatNew == ON_OFF)&&(Type!=boolean)) {
		if(OldValue)
			strcpy((char*)Val1,"ON");
		else
			strcpy((char*)Val1,"OFF");
		if(NewValue)
			strcpy((char*)Val2,"ON");
		else
			strcpy((char*)Val2,"OFF");

	}
	else if((ParamFormatNew == STRING)||(Type == boolean)) {
		strncpy((char*)Val1, (const char*)OldVal, sizeof(OldParamValue) - 1);
		strncpy((char*)Val2, (const char*)NewVal, sizeof(NewParamValue) - 1);

	}
	else if(DisableFlagNewValue == DisableFlagOldValue) {
		FormatVariables(OldValue, ParamFormatOld, OldParamValue,
			sizeof(OldParamValue) - 1, CurrentSetup.Units);
		FormatVariables(NewValue, ParamFormatNew, NewParamValue,
			sizeof(NewParamValue) - 1, CurrentSetup.Units);
		Val1 = (UINT8*)Trim_FillChar((SINT8*)Val1);
		Val2 = (UINT8*)Trim_FillChar((SINT8*)Val2);
	}
	else {
		if(DisableFlagNewValue<DisableFlagOldValue) {
			/*the parameter is switched from off to value*/
			strcpy((char*)Val1,"OFF");
			FormatVariables(NewValue, ParamFormatNew, NewParamValue,
				sizeof(NewParamValue) - 1, CurrentSetup.Units);
			Val2 = (UINT8*)Trim_FillChar((SINT8*)Val2);
		}
		else {
			FormatVariables(OldValue, ParamFormatOld, OldParamValue,
				sizeof(OldParamValue) - 1, CurrentSetup.Units);
			Val1 = (UINT8*)Trim_FillChar((SINT8*)Val1);
			strcpy((char*)Val2,"OFF");
		}

	}
	if(CurrentPreset.Validated == FALSE)
		RecordEvents(EVENT_PARAMETER_CHANGED, (char*)Val1, (char*)Val2);
	else
		RecordEvents(EVENT_PARAMETER_CHANGED_ONVALIDATEDPS, (char*)Val1, (char*)Val2);
}


/***************************************************************************
*Purpose:                                                                  *
*   This function is called when any add/modify user related event occurs  *
*Entry condition:                                                          *
*   Entry condition:                                                       *
*   UINT8 Operation: the operation being done on user                      *
*   UINT8  Position: the position of the user being modified               *
*                                                                          *
*Exit condition:                                                           *
*   none                                                                   *
****************************************************************************/

void AddModifyUserEventRecord(UINT8 Operation,UINT8  Position)
{

	char Data1[MAX_EVENTDATA_LEN], Data2[MAX_EVENTDATA_LEN];
	switch(Operation)
	{
	case ADD:
		strncpy(Data1 , useridData.UserId, MAX_EVENTDATA_LEN - 1);
		strncpy(Data2 , "", MAX_EVENTDATA_LEN - 1);
	    RecordEvents(EVENT_NEWUSER_CREATED, Data1, Data2);

		break;
	case MODIFY:

		if((FRAMUserIdObj.UserDetail[Position].Status)!= useridData.Status) {//the status of user changed
			 EventParameterID = ACTIVE_STATUS_CHANGE;
		   if(FRAMUserIdObj.UserDetail[Position].Status == Enabled)
			   strncpy(Data1 , "Enabled", MAX_EVENTDATA_LEN - 1);
		   else
			   strncpy(Data1 , "Disabled", MAX_EVENTDATA_LEN - 1);
		   if(useridData.Status == Enabled)
			   strncpy(Data2 , "Enabled", MAX_EVENTDATA_LEN - 1);
		   else
			   strncpy(Data2 , "Disabled", MAX_EVENTDATA_LEN - 1);
		   RecordEvents(EVENT_USER_MODIFIED, Data1, Data2);
		}

		if(FRAMUserIdObj.UserDetail[Position].UserLevel != useridData.UserLevel) {//the user level changed
			EventParameterID = USER_LEVEL_CHANGE;
			 RecordEvents(EVENT_USER_MODIFIED,FRAMUserIdObj.UserDetail[Position].UserLevel, useridData.UserLevel);
		}
		if(strncmp(FRAMUserIdObj.UserDetail[Position].Password, useridData.Password, sizeof(useridData.Password) - 1)) {
			EventParameterID =  PASSWORD_CHANGE;		
			RecordEvents(EVENT_USER_MODIFIED,"", "");
		}

		break;
	default:
		break;

	}

}

void AssemblyNumberChangeEventRecord(void)
{
	RecordEvents(EVENT_HARDWARE_ASSEMBLY_NUMBER_CHANGED,(char*)ParamOldVal,(char*)ParamNewVal);
}

void ComponentVerifyChangeEventRecord(void)
{
  RecordEvents(EVENT_HARDWARE_VERIFY_CHANGED,RadioIndexOld,CurrentSetup.HWVerify);
}


