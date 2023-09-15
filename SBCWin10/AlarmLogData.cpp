/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLogData.cpp_v   1.9   28 Jul 2014 13:24:00   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLogData.cpp_v  $
 * 
 *    Rev 1.9   28 Jul 2014 13:24:00   rjamloki
 * Assigning and checking Parameter_Value!=NULL before delete.
 * 
 *    Rev 1.8   09 Jun 2014 11:34:14   rjamloki
 * initialized variables in constructor.
 * 
 *    Rev 1.7   27 May 2014 17:57:02   akaushal
 * Calling base class function to draw the column
 * 
 *    Rev 1.5   20 May 2014 10:51:18   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.4   07 May 2014 13:02:30   akaushal
 * Update the AlarmID on the Alarm Log Screen
 * 
 *    Rev 1.3   21 Apr 2014 13:26:14   akaushal
 * AlarmLogData() constructor modified.
 * 
 *    Rev 1.2   28 Mar 2014 14:32:52   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     05 Mar 2014 14:13:10 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.0    26 Feb 2014 02:18:16 jerryw.wang     
 * Initial Revision.
*/


#include "stdafx.h"
#include "VGA.h"
#include "AlarmLogData.h"
#include "AlarmLog.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAlarmLogData::CAlarmLogData(struct AlarmLog *&AlarmLogData)
{
	char timeDateBuff[32];
	TextColour = Black;
	Parameter_Value = new CString[CAlarmLog::thisHisPtr->TotalColoumn];
	AlarmLogObj.AlarmNum = ntohl(AlarmLogData ->AlarmNum);
	AlarmLogObj.TS.Years = AlarmLogData->TS.Years;
	AlarmLogObj.TS.Century_Month = AlarmLogData->TS.Century_Month;
	AlarmLogObj.TS.Day = AlarmLogData->TS.Day;
	AlarmLogObj.TS.Hour = AlarmLogData->TS.Hour;
	AlarmLogObj.TS.Minute = AlarmLogData->TS.Minute;
  	AlarmLogObj.TS.Second = AlarmLogData->TS.Second;
    AlarmLogObj.AlarmID = ntohs(AlarmLogData -> AlarmID);
	AlarmLogObj.CycleNum = ntohl(AlarmLogData -> CycleNum);
	AlarmLogObj.PresetNum = ntohs(AlarmLogData -> PresetNum);
	AlarmLogObj.PresetRevNum = ntohl(AlarmLogData -> PresetRevNum);
	strcpy((char*)AlarmLogObj.PSAssemblyID, (char*)AlarmLogData -> PSAssemblyID);
	strcpy((char*)AlarmLogObj.ActuatorAssemblyID , (char*)AlarmLogData -> ActuatorAssemblyID);
    strcpy((char*)AlarmLogObj.UserID, (char*)AlarmLogData -> UserID);
	AlarmLogObj.AlarmLogCRC = 0;
	Lang_Index = 0;
	Parameter_Value[0].Format(_T("%u"), AlarmLogObj.AlarmNum);
	GetRTCDate(&(AlarmLogObj.TS),timeDateBuff);
	Parameter_Value[1] = CString(timeDateBuff);
	GetRTCTime(&(AlarmLogObj.TS),timeDateBuff);
	Parameter_Value[2] = CString(timeDateBuff);
	Parameter_Value[3].Format(_T("%X"),  AlarmLogObj.AlarmID);
	Parameter_Value[4].Format(_T("%u"), AlarmLogObj.CycleNum);
	Parameter_Value[5] = CString((char*)(AlarmLogObj.UserID));
	Parameter_Value[6].Format(_T("%d"), AlarmLogObj.PresetNum);
	Parameter_Value[7].Format(_T("%u"), AlarmLogObj.PresetRevNum);
	Parameter_Value[8] = CString((char*)(AlarmLogObj.ActuatorAssemblyID));
	Parameter_Value[9] = CString((char*)(AlarmLogObj.PSAssemblyID));
	
}

CAlarmLogData::CAlarmLogData()
{
	AlarmLogObj.AlarmNum = 0;
	AlarmLogObj.TS.Years = 0;
	AlarmLogObj.TS.Century_Month = 0;
	AlarmLogObj.TS.Day = 0;
	AlarmLogObj.TS.Hour = 0;
	AlarmLogObj.TS.Minute = 0;
  	AlarmLogObj.TS.Second = 0;
	AlarmLogObj.AlarmID = 0;
	AlarmLogObj.CycleNum = 0;
	AlarmLogObj.PresetNum = 0;
	AlarmLogObj.PresetRevNum = 0;
	strncpy((char*)AlarmLogObj.PSAssemblyID, "",1);
	strncpy((char*)AlarmLogObj.ActuatorAssemblyID , "",1);
	strncpy((char*)AlarmLogObj.UserID,"",1);
	AlarmLogObj.AlarmLogCRC = 0;
	Lang_Index = 0;
	TextColour = Black;
	Parameter_Value = NULL;
}

CAlarmLogData::~CAlarmLogData()
{
   if(Parameter_Value)
	   delete[] Parameter_Value;
}

void CAlarmLogData::Draw(CDC *pDC)
{

}

/****************************************************************************/
/* This function draws the Alarm Log when Power supply history is drawn.	*/
/****************************************************************************/
void CAlarmLogData::DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo)
{
	CRect ParamValueRect;

	int ColumnNo=0;
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
		(LINE_GAP*(LineNo+3)),
		(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
		(LINE_GAP*(LineNo+4)));

	CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[0],false);
	ColumnNo++;

	for (int Index = LeftMostParameter; Index <(LeftMostParameter+4) ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
			(LINE_GAP*(LineNo+3)),
			(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
			(LINE_GAP*(LineNo+4)));

		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[Index],false);
		ColumnNo++;

	}
}

bool CAlarmLogData::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
