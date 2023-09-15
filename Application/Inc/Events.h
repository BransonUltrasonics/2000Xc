
/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/Events.h_v   1.5   01 Apr 2015 13:04:12   amaurya  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/Events.h_v  $
 * 
 *    Rev 1.5   01 Apr 2015 13:04:12   amaurya
 * added RESERVED0 replaced with EVENT_AUTHORITY_CHECK_CHANGED in EventTypes enum for authority check event.
 * 
 *    Rev 1.4   28 Nov 2014 07:55:16   rjamloki
 * EVENT_AUTHORITYLEVELCHANGES removed from enum EventTypes.
 * 
 *    Rev 1.3   11 Nov 2014 06:14:04   AnPawar
 * Cleaned up to remove extra events
 * 
 *    Rev 1.2   20 Oct 2014 06:38:50   AnPawar
 * EventTypes enum changed
 * 
 *    Rev 1.1   03 Oct 2014 06:23:12   rjamloki
 *  struct JsonEventLog declared
 * 
 *    Rev 1.0   11 Sep 2014 11:26:48   rjamloki
 * Initial revision.
*/

#ifndef EVENTS_H_
#define EVENTS_H_
#include "menu.h"
#include "rtclock.h"
#include "portable.h"
#include "command.h"

#define MAX_EVENT_ENTRIES 100
#define MAX_EVENT_IN_ONE_PACKET 10
#define EVENTHISTORYINITIALIZED_CHECKSUM 0xABEF23CE
#define MAX_EVENTREASON_LEN 52//Including null
#define MAX_EVENTDATA_LEN 12 //Including null
#define MAX_EVENTID_STR_LEN 6 //Including null

struct FRAMEventHistory;

enum EventTypes {
	EVENT_PARAMETER_CHANGED_ONVALIDATEDPS,
	EVENT_PRESETVALIDATION_BITSET,
	EVENT_NEWUSER_CREATED,
	EVENT_USER_MODIFIED,
	EVENT_RTC_CHANGED,
	EVENT_FACTORY_AUTOMATION_MODE,
	EVENT_HARDWARE_ASSEMBLY_NUMBER_CHANGED,
	EVENT_HARDWARE_VERIFY_CHANGED,
	EVENT_SOFTWAREVERSION_CHANGED,
	EVENT_AUTHORITY_CHECK_CHANGED,
	EVENT_ACTCOLD_START,
	EVENT_LOWBATTERY,
	EVENT_CALIBRATION,
	EVENT_PRESET_VALIDATION_BIT_CLEARED,
	EVENT_RESERVED1,
	EVENT_RESERVED2,
	EVENT_RESERVED3,
	EVENT_POWERON_CRC_CHANGED,
	EVENT_CLOCK_LOST,
	EVENT_RESERVED4,
	EVENT_PARAMETER_CHANGED,
	EVENT_RESERVED5,
	EVENT_RESERVED6,
	EVENT_RESERVED7,
	EVENT_RESERVED8,
	EVENT_RESERVED9,
	EVENT_RESERVED10,
	EVENT_HORN_SCAN_COMPLETED,
	EVENT_RESERVED11,
	EVENT_RESERVED12,
	EVENT_RESERVED13,
	EVENT_RESERVED14,
	EVENT_RESERVED15,
	EVENT_RESERVED16,
	EVENT_RESERVED17,
	EVENT_RESERVED18,
	EVENT_USERLOGIN,
	EVENT_USERLOGOUT,
	EVENT_RESERVED19,
	EVENT_RESERVED20,
	EVENT_RESERVED21,
	EVENT_RESERVED22,
	EVENT_FIRMWARE_UPLOAD,
	EVENT_EVENT_ERROR,

};




typedef struct{
	UINT32 EventNum; //Event Number 0
	UINT16 PresetNo; // Present Number 4
	UINT16 Rev; //Revision Number 6
	UINT8 UserId[6]; //USER Id 8
	UINT8 EventId[6]; //Event ID 14
	UINT8 PSSerialNumber[14]; //Power Supply Serial Number 20
	char DataNew[MAX_EVENTDATA_LEN]; //Data One 34
	char DataOld[MAX_EVENTDATA_LEN]; //Data Two 46
	RTCTime TS; // Event Record Creation Time 58
	UINT8 EventReason[MAX_EVENTREASON_LEN];//66
	UINT16 ParameterId;
	UINT16 EventHistoryCRC; //CRC of the Data above to check the data above is valid or not 50
}__attribute__((__packed__)) Event_Log;

typedef struct JsonEventLog
{
	UINT32   EventNum;      //Event Number
	UINT16   PresetNo;      // Present Number
	UINT16   Rev;              //Revision Number
	UINT8    UserId[6];    //USER Id
	UINT8    EventId[6];      //Event ID
	UINT8    PSSerialNumber[14]; //Power Supply Serial Number
	RTCTime  TS;  // Event Record Creation Time
	UINT8 	EventReason[MAX_EVENTREASON_LEN];
   UINT8    EventDescription[200]; //49
}__attribute__((__packed__)) JsonEvent_Log;

struct FRAMEventHistory {
	Event_Log EventHistoryObjs[MAX_EVENT_ENTRIES];
	SINT16 CircularIndex; //Circular Index goes between 0-99, and contains the index of latest event entry made in EventHistoryObjs Array above.
	//(– 1) means no event logged
	UINT32 EventHistoryCount; // Event Counter Incremented with each event logged.
	UINT32 EventHistoryCheckSum;//To check whether event are ever written or not.
};

struct EventIDs {
	UINT16 EventID;
	UINT8 EventReasonMask;
	void (*Function)(SINT32, SINT32, EDIT_PARAM_TYPE);
};

extern UINT32 EventHistCountTemp;
extern BOOLEAN EventReasonFlag, VGAEventReasonFlag;
extern char EventReasonString[52];
extern FRAMEventHistory FRAMEventHistoryObj;
void RecordEvents(enum EventTypes, char *, char *);
void RecordEvents(EventTypes Events, UINT32 Data1, UINT32 Data2);
void RecordParamChangeEvent(void *, void *, DataType);
void AddModifyUserEventRecord(UINT8 operation, UINT8);
void AssemblyNumberChangeEventRecord(void);
void ComponentVerifyChangeEventRecord(void);
UINT32 ReadEventHistory(Event_Log *, UINT32, UINT32);
extern UserID useridData;
extern FORMAT ParameterID_Format[];
extern EventIDs EventIDGroup[];
extern UINT8 ParamNewVal[MAX_EVENTDATA_LEN], ParamOldVal[MAX_EVENTDATA_LEN];
extern UINT16 DisableFlagOldValue, DisableFlagNewValue;
extern UINT16 RadioIndexNew, RadioIndexOld;
extern DataType Type;
extern EDIT_PARAM_TYPE EventParameterID;
extern UINT16 PresetRevValidationEvent;

#endif /* EVENTS_H_ */
