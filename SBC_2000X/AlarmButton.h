/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/AlarmButton.h_v   1.2   28 Mar 2014 14:32:52   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/AlarmButton.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:32:52   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:44 rjamloki  
 * Header Fix and added command to assign ip. 
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_)
#define AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CAlarmButton : public CVgaMenuItem  
{
public:
	CAlarmButton(CXmlElement * e);
	virtual ~CAlarmButton();
   CString Text1;
	CString Text2;
   CString MenuName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
private:
	CRect Rect;
   int TextColor;
   int BoxColor;
};

#endif // !defined(AFX_ALARMBUTTON_H__CC4BC1B5_9A42_41F5_BB9E_58944F49C944__INCLUDED_)
