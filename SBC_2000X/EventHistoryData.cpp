/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/EventHistoryData.cpp_v   1.11   11 Sep 2014 09:44:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/EventHistoryData.cpp_v  $
 * 
 *    Rev 1.11   11 Sep 2014 09:44:12   rjamloki
 * CEventHistoryData() function modified for event description and reason.
 * 
 *    Rev 1.10   28 Jul 2014 13:52:50   rjamloki
 * default colour black added in CEventHistoryData constructor
 * 
 *    Rev 1.9   11 Jun 2014 06:45:08   rjamloki
 * CEventHistoryData::CEventHistoryData() function argument name changed.   
 * 
 *    Rev 1.8   09 Jun 2014 11:41:46   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.7   27 May 2014 18:01:02   akaushal
 * Updated the Data receive code to receive correct data
 * 
 *    Rev 1.6   27 May 2014 06:29:34   amaurya
 * Updated display function call
 * 
 *    Rev 1.5   20 May 2014 10:56:20   rjamloki
 *  Constructor added. 
 * 
 *    Rev 1.4   07 May 2014 13:06:26   akaushal
 * Time and Date updates
 * 
 *    Rev 1.3   21 Apr 2014 13:35:20   akaushal
 * CEventHistoryData() constructor modified.SetParameters() added. 
 * 
 *    Rev 1.2   28 Mar 2014 14:33:00   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     05 Mar 2014 14:13:16 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.0    26 Feb 2014 02:18:18 jerryw.wang    
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "EventHistoryData.h"
#include "EventLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventHistoryData::CEventHistoryData()
{
	TextColour = Black;
	Parameter_Value = NULL;
	memset(&EventHistoryObj, 0, sizeof(EventHistoryObj));
	Lang_Index = 0;
	Parameter_Value = NULL;
}
CEventHistoryData::CEventHistoryData(unsigned char * data)
{
	Lang_Index = 0;
	Parameter_Value = NULL;
	int Offset = 0;
	memset(&EventHistoryObj, 0, sizeof(EventHistoryObj));
	EventHistoryObj.EventNum = ((UINT32)data[0] << 24) | ((UINT32)data[1] << 16) | ((UINT32)(data[2]) << 8) | ((UINT32)data[3]); //0
	EventHistoryObj.PresetNo = ((UINT16)data[4] << 8) | ((UINT16)data[5]); //4
	EventHistoryObj.Rev      = ((UINT16)data[6] << 8) | ((UINT16)data[7]); //6
	strncpy((char*)EventHistoryObj.UserId,(char*)&data[8], sizeof(EventHistoryObj.UserId) - 1); //8	
	strncpy((char*)EventHistoryObj.EventId,(char*)&data[14], sizeof(EventHistoryObj.EventId) - 1); //14
	strncpy((char*)EventHistoryObj.PSSerialNumber,(char*)&data[20], sizeof(EventHistoryObj.PSSerialNumber) - 1); //20
	strncpy((char*)EventHistoryObj.DataNew,(char*)&data[34], sizeof(EventHistoryObj.DataNew) - 1); //34
	strncpy((char*)EventHistoryObj.DataOld,(char*)&data[46], sizeof(EventHistoryObj.DataOld) - 1); //46	
	EventHistoryObj.TS.Century_Month = data[63]; //42
	EventHistoryObj.TS.Day = data[61];
	EventHistoryObj.TS.Hour = data[60];
	EventHistoryObj.TS.Minute = data[59];
	EventHistoryObj.TS.Second = data[58];
	EventHistoryObj.TS.Weekdays = data[62];
	EventHistoryObj.TS.Years = data[64];
	strncpy((char*)EventHistoryObj.EventReason,(char*)&data[65], 51); //20
	EventHistoryObj.ParameterId = ((UINT16)data[117] << 8) | ((UINT16)data[118]);
	EventHistoryObj.EventHistoryCRC = 0;
	TextColour = Black;
}
CEventHistoryData::CEventHistoryData(struct Event_Log *&EventHistoryData)
{
	Lang_Index = 0;
	char timeBuff[32]={0};
	TextColour = Black;
	Parameter_Value = new CString[/*CEventLog::thisHisPtr->TotalColoumn*/11];
	memset(&EventHistoryObj, 0, sizeof(EventHistoryObj));
	EventHistoryObj.PresetNo = ntohs(EventHistoryData -> PresetNo);
	EventHistoryObj.Rev = ntohs(EventHistoryData ->Rev);
	EventHistoryObj.EventNum = ntohl(EventHistoryData -> EventNum);
	strncpy((char*)EventHistoryObj.DataNew,(char*)EventHistoryData -> DataNew, sizeof(EventHistoryObj.DataNew) - 1); //34
	strncpy((char*)EventHistoryObj.DataOld,(char*)EventHistoryData -> DataOld, sizeof(EventHistoryObj.DataOld) - 1); //46
	EventHistoryObj.TS.Years = EventHistoryData->TS.Years;
	EventHistoryObj.TS.Century_Month = EventHistoryData->TS.Century_Month;
	EventHistoryObj.TS.Day = EventHistoryData->TS.Day;
	EventHistoryObj.TS.Hour = EventHistoryData->TS.Hour;
	EventHistoryObj.TS.Minute = EventHistoryData->TS.Minute;
	EventHistoryObj.TS.Second = EventHistoryData->TS.Second;
	strcpy((char*)EventHistoryObj.UserId, (char*)EventHistoryData -> UserId);
	strcpy((char*)EventHistoryObj.EventId , (char*)EventHistoryData -> EventId);
	strcpy((char*)EventHistoryObj.PSSerialNumber, (char*)EventHistoryData -> PSSerialNumber);
	strncpy((char*)EventHistoryObj.EventReason, (char*)EventHistoryData -> EventReason, sizeof(EventHistoryObj.EventReason) - 1);
	EventHistoryObj.ParameterId = ntohs(EventHistoryData ->ParameterId);
	EventHistoryObj.EventHistoryCRC = 0;
	Parameter_Value[0].Format(_T("%u"),EventHistoryObj.EventNum);
	GetRTCTime(&(EventHistoryData->TS), timeBuff);
	Parameter_Value[1] = CString(timeBuff);
	GetRTCDate(&(EventHistoryData->TS), timeBuff);
	Parameter_Value[2] = CString(timeBuff);
	Parameter_Value[5] = CString((char*)(EventHistoryObj.EventId));
	sprintf(timeBuff,"%d",(EventHistoryObj.DataOld));
	Parameter_Value[8] = CString((char*)(timeBuff));
	sprintf(timeBuff,"%d",(EventHistoryObj.DataNew));
	Parameter_Value[9] = CString((char*)(timeBuff));
	Parameter_Value[4] = CString((char*)(EventHistoryObj.UserId));
	Parameter_Value[6].Format(_T("%d"), EventHistoryObj.PresetNo);
	Parameter_Value[7].Format(_T("%d"),EventHistoryObj.Rev);
	Parameter_Value[3] = CString((char*)(EventHistoryObj.PSSerialNumber));
	Parameter_Value[10] = CString((char*)(EventHistoryObj.EventReason));


}

void CEventHistoryData::SetParameters()
{
	char timeBuff[32];
	Parameter_Value = new CString[/*CEventLog::thisHisPtr->TotalColoumn*/11];
	
	Parameter_Value[0].Format(_T("%u"),EventHistoryObj.EventNum);
	GetRTCTime(&(EventHistoryObj.TS), timeBuff);
	Parameter_Value[1] = CString(timeBuff);
	GetRTCDate(&(EventHistoryObj.TS), timeBuff);
	Parameter_Value[2] = CString(timeBuff);
	Parameter_Value[5] = CString((char*)(EventHistoryObj.EventId));
	Parameter_Value[9] = CString((char*)(EventHistoryObj.DataOld));
	Parameter_Value[8] = CString((char*)(EventHistoryObj.DataNew));
	Parameter_Value[4] = CString((char*)(EventHistoryObj.UserId));
	Parameter_Value[6].Format(_T("%d"), EventHistoryObj.PresetNo);
	Parameter_Value[7].Format(_T("%d"),EventHistoryObj.Rev);
	Parameter_Value[3] = CString((char*)(EventHistoryObj.PSSerialNumber));
	Parameter_Value[10] = CString((char*)(EventHistoryObj.EventReason));
	


}

CEventHistoryData::~CEventHistoryData()
{
	if(Parameter_Value) {
		delete[] Parameter_Value;
	}
}

void CEventHistoryData::Draw(CDC *pDC)
{

}

/****************************************************************************/
/* This function draws the Event Log when Power supply history is drawn.	*/
/****************************************************************************/
void CEventHistoryData::DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo)
{
	CRect ParamValueRect;

	int ColumnNo=0;
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * EventParamRect_Width),
		(LINE_GAP*(LineNo+3)),
		(HISTORY_TBL_START_X + (ColumnNo+1) * EventParamRect_Width),
		(LINE_GAP*(LineNo+4)));

	CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[0],false);
	ColumnNo++;

	for (int Index = LeftMostParameter; Index <(LeftMostParameter+4) ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * EventParamRect_Width),
			(LINE_GAP*(LineNo+3)),
			(HISTORY_TBL_START_X + (ColumnNo+1) * EventParamRect_Width),
			(LINE_GAP*(LineNo+4)));

		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[Index],false);
		ColumnNo++;

	}
}

bool CEventHistoryData::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
