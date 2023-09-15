/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLogData.h_v   1.6   09 Jul 2014 07:29:34   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLogData.h_v  $
 * 
 *    Rev 1.6   09 Jul 2014 07:29:34   akaushal
 * Removed inclusion of Eventhistory.h.
 * 
 *    Rev 1.5   11 Jun 2014 06:42:46   rjamloki
 * macro ALARMLOGINONEPACKET changed to ALARM_IN_ONE_PACKET.
 * 
 *    Rev 1.4   09 Jun 2014 11:34:54   rjamloki
 * removed unused CreateUserObjectList() declaration
 * 
 *    Rev 1.3   27 May 2014 06:17:00   amaurya
 * Code Cleanup
 * 
 *    Rev 1.2   21 Apr 2014 13:26:58   akaushal
 * AlarmLog structure added.AlarmLogData modified for displaying Log.
 * 
 *    Rev 1.1   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.0     26 Feb 2014 02:18:18 jerryw.wang      
 * Initial Revision.
*/

#if !defined(AFX_ALARMLOGDATA_H__ED5D463F_4A9E_41C1_8A2D_C4DDED1A4841__INCLUDED_)
#define AFX_ALARMLOGDATA_H__ED5D463F_4A9E_41C1_8A2D_C4DDED1A4841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RunScreen.h"
#include "VgaMenuItem.h"
#include "ScreenKeypad.h"
#include "UserID.h"

#define ALARM_IN_ONE_PACKET 10
#define MAX_ALARM_COUNT 100

struct AlarmLog
{
   UINT32 AlarmNum;		//Alarm Counter
   UINT32 CycleNum;		//Weld Cycle Number during which Alarm logged.
   UINT32 PresetRevNum;		//Preset Revision number.
   UINT16 PresetNum;		//Current Preset number at the time of Alarm.
   UINT16 AlarmID;	//AlarmID. Manual shall describe the meaning of the Alarm ID.
   INT8 UserID[6];		//Logged In User ID at the time of Alarm.
   INT8 ActuatorAssemblyID[14];	//Actuator Assembly Number.
   INT8 PSAssemblyID[14];	//Power Supply Assembly Number.
   RTCTime TS;			// Date and Time when Alarm was logged.
   UINT8 bitStuff[1];
   UINT16 AlarmLogCRC; //CRC of the Data above to check the data above is valid or not
};

class CAlarmLogData
{
public:
	CAlarmLogData(struct AlarmLog *&data);
   CAlarmLogData();
	void DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo);
	virtual ~CAlarmLogData();
	virtual void Draw(CDC *pDC);
    static CAlarmLogData * thisPtr;
    AlarmLog AlarmLogObj;
protected:
	   int Lang_Index;
	   virtual bool MouseClick(const CPoint &p, CChildView *view);

public:
	int TextColour;
	CString * Parameter_Value;
};

#endif // !defined(AFX_ALARMLOGDATA_H__ED5D463F_4A9E_41C1_8A2D_C4DDED1A4841__INCLUDED_)
