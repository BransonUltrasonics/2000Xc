/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/EventHistoryData.h_v   1.7   09 Jul 2014 06:52:54   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/EventHistoryData.h_v  $
 * 
 *    Rev 1.7   09 Jul 2014 06:52:54   akaushal
 * Removed inclusion of Eventhistory.h.
 * 
 *    Rev 1.6   11 Jun 2014 06:45:44   rjamloki
 * CEventHistoryData() declaration changed in class CEventHistoryData.Event_History changed to Event_Log
 * 
 *    Rev 1.5   09 Jun 2014 11:42:32   rjamloki
 * Column width macro changed.
 * 
 *    Rev 1.4   27 May 2014 06:29:50   amaurya
 * Code CleanUp
 * 
 *    Rev 1.3   20 May 2014 10:56:50   rjamloki
 * CEventHistoryData class changed.
 * 
 *    Rev 1.2   21 Apr 2014 13:36:14   akaushal
 * EventHistoryData class modified.Constructors modified. 
 * 
 *    Rev 1.1   28 Mar 2014 14:33:00   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.0    26 Feb 2014 02:18:18 jerryw.wang     
 * Initial Revision.
 */
#if !defined(AFX_EVENTHISTORYDATA_H__1CEBEBE9_C0CC_47E2_9B56_A997F4A05049__INCLUDED_)
#define AFX_EVENTHISTORYDATA_H__1CEBEBE9_C0CC_47E2_9B56_A997F4A05049__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EventLog.h"
#include "VgaMenuItem.h"
#include "RunScreen.h"
#include "UserID.h" 
#define EventParamRect_Width  120

class CEventHistoryData
{
public:
	CEventHistoryData(struct Event_Log *&EventHistoryData);
	CEventHistoryData(unsigned char * data);
	CEventHistoryData();
	void DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo);
	~CEventHistoryData();
	virtual void Draw(CDC *pDC);
	Event_Log EventHistoryObj;
	void SetParameters(void);
protected:
	   int Lang_Index;
	   virtual bool MouseClick(const CPoint &p, CChildView *view);
public:
	int TextColour;
	CString *Parameter_Value;
};

#endif // !defined(AFX_EVENTHISTORYDATA_H__1CEBEBE9_C0CC_47E2_9B56_A997F4A05049__INCLUDED_)
