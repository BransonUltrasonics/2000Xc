/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLog.h_v   1.5   09 Jun 2014 11:33:28   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLog.h_v  $
 * 
 *    Rev 1.5   09 Jun 2014 11:33:28   rjamloki
 * CreatePDF() function declaration changed .
 * 
 *    Rev 1.4   27 May 2014 06:37:24   amaurya
 * Code Cleanup.
 * 
 *    Rev 1.3   21 Apr 2014 13:25:48   akaushal
 * Removed the UpdateAlarmData() declarariton.And CreatePDF() added.
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

#if !defined(AFX_ALARMLOG_H__89927B57_C7C0_4DA6_B519_07EE8592A27F__INCLUDED_)
#define AFX_ALARMLOG_H__89927B57_C7C0_4DA6_B519_07EE8592A27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
//#include "RunScreen.h"
#include "AlarmLogData.h"

#define LeftButton_Rect CRect(45,370,95,420)
#define ScreenUpButton_Rect CRect(105,370,155,420)
#define UpButton_Rect CRect(165,370,215,420)
#define DownButton_Rect CRect(225,370,275,420)
#define ScreenDownButton_Rect CRect(285,370,335,420)
#define RightButton_Rect CRect(345,370,395,420)
#define GraphsButton_Rect CRect(X_CORDINATE_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define UpArrowRect CPoint(180,404), CPoint(190, 386),CPoint(201,404)
#define DownArrowRect CPoint(240,386), CPoint(250,404),CPoint(261,386)
#define LeftArrowRect CPoint(80,386), CPoint(60,395),CPoint(80,404)
#define RightArrowRect CPoint(360,386), CPoint(380,395),CPoint(360,404)
#define ScreenUpArrow1Rect CPoint(120,398), CPoint(130, 382),CPoint(141,398)
#define ScreenUpArrow2Rect CPoint(120,408), CPoint(130, 392),CPoint(141,408)
#define ScreenDownArrow1Rect CPoint(300,382), CPoint(310,398 ),CPoint(321,382)
#define ScreenDownArrow2Rect CPoint(300,392), CPoint(310, 408),CPoint(321,392)

#define AlarmLogMaxCyclePerScreen 8

class CXmlElement;

class CAlarmLog : public CVgaMenuItem   
{
public:
	CAlarmLog(CXmlElement * e);
	virtual ~CAlarmLog();

	void DrawParameterHeadings(CDC * pDC);
	int *Parameter_ID;
	int TotalColoumn;
	static int TopMostData;
	void DrawAlarmData(CDC *pDC);
	int TotalCycle;
	CAlarmLog(unsigned char * &data, int & length);
	CAlarmLog();
	CTypedPtrList<CPtrList, CAlarmLogData *> AlarmLogList;
    void CreatePDF(HPDF_Doc *& pdf,HPDF_Page *& page);
	static int SelectedAlarmData;
	static int LeftMostParameter;
	static CAlarmLog * thisHisPtr;
protected:
   bool UpButtonPressed;
   bool DownButtonPressed;
   bool LeftButtonPressed;
   bool RightButtonPressed;
   bool ScreenUpButtonPressed;
   bool ScreenDownButtonPresssed;
   bool GraphsButtonPressed;
   bool ExitButtonPressed;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
private:
   int lang_index;
};

#endif // !defined(AFX_ALARMLOG_H__89927B57_C7C0_4DA6_B519_07EE8592A27F__INCLUDED_)
