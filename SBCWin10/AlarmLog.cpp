/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLog.cpp_v   1.7   05 Sep 2014 06:56:36   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/AlarmLog.cpp_v  $
 * 
 *    Rev 1.7   05 Sep 2014 06:56:36   amaurya
 * Corrected the list traverse in DrawAlarmData().
 * 
 *    Rev 1.6   28 Jul 2014 13:16:14   rjamloki
 * added condition Parameter_ID!=NULL before delete operation.
 * 
 *    Rev 1.5   09 Jun 2014 11:31:58   rjamloki
 * initialized variables in constructors. CAlarmLog::DrawParameterHeadings() function changed
 * 
 *    Rev 1.4   20 May 2014 10:50:52   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.3   21 Apr 2014 13:25:12   akaushal
 * Removed unused UpdateAlarmData().
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


#include "stdafx.h"
#include "VGA.h"
#include "AlarmLog.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


int CAlarmLog::TopMostData;
int CAlarmLog::SelectedAlarmData;
int CAlarmLog::LeftMostParameter;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarmLog * CAlarmLog::thisHisPtr;

CAlarmLog::CAlarmLog(CXmlElement * e)
{
	Parameter_ID=NULL;
	TotalColoumn = 0;
	TotalCycle = 0;
	UpButtonPressed = false;
	DownButtonPressed = false;
	RightButtonPressed = false;
	LeftButtonPressed = false;
	ScreenUpButtonPressed = false;
	ScreenDownButtonPresssed = false;
	GraphsButtonPressed = false;
	ExitButtonPressed = false;
	lang_index = 0;
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
		{
			AddCondition(element);
		}
		else
			ASSERT(FALSE);
	}
	thisHisPtr=this;
	CAlarmLog::LeftMostParameter=1;
}

CAlarmLog::CAlarmLog()
{
	Parameter_ID=new int[1];
	TotalColoumn = 0;
	TotalCycle = 0;
	UpButtonPressed = false;
	DownButtonPressed = false;
	RightButtonPressed = false;
	LeftButtonPressed = false;
	ScreenUpButtonPressed = false;
	ScreenDownButtonPresssed = false;
	GraphsButtonPressed = false;
	ExitButtonPressed = false;
	lang_index = 0;
}

CAlarmLog::~CAlarmLog()
{
   if(Parameter_ID != NULL)
	   delete []Parameter_ID;
	while(AlarmLogList.GetCount()>0)
		delete AlarmLogList.RemoveHead();
}

/****************************************************************************************/
/*  This function draws the Alarm-Log screen.										*/
/*  the function checks if the button is pressed or not, if found then draws it in      */
/*  pressed state.																		*/
/*																						*/
/****************************************************************************************/
void CAlarmLog::Draw(CDC *pDC)
{
	DrawAlarmData(pDC);
}

/**********************************************************************************************/
/* this function handles the mouse click if it is on the Alarm-Log screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */
/**********************************************************************************************/
bool CAlarmLog::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

/****************************************************************************************/
/*																						*/
/* The following function is used to Draw Alarm data. The function checks the Top most	*/
/* Data and the Left Most PArameter on the screen and displays next eight alarm data		*/
/* from the Top most alarm data.															*/
/****************************************************************************************/
void CAlarmLog::DrawAlarmData(CDC *pDC)
{
	int LineNo=1;
	int TotalCyclesDrawn=0;
	if(AlarmLogList.GetCount())
	{
		POSITION pos = AlarmLogList.GetHeadPosition();
		for(int CurrentPos = 1; (CurrentPos < TopMostData) && pos ; CurrentPos++)
			AlarmLogList.GetNext(pos);
		DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(LINE_GAP*(SelectedAlarmData+3)),
			(HISTORY_TBL_START_X + 5 * ParamRect_Width + 12),
			(LINE_GAP*(SelectedAlarmData+4))));
		while(pos)
		{
			if(TotalCyclesDrawn==AlarmLogMaxCyclePerScreen)
				break;
			CAlarmLogData * Obj = AlarmLogList.GetNext(pos);
			Obj->DrawHistoryData(pDC,LeftMostParameter, LineNo);
			TotalCyclesDrawn++;
			LineNo++;
		}
	}
	DrawParameterHeadings(pDC);
}

/********************************************************************************************/
/* The following function is used to draw parameter headings on the Alarm Log screen.	*/
/* The function checks for the unit of the selected alarm data and draws the unit accordingly*/
/*																							*/
/********************************************************************************************/
void CAlarmLog::DrawParameterHeadings(CDC *pDC)
{
	if(LeftMostParameter>(TotalColoumn-4))
		LeftMostParameter=1;

	int X1 = 20;
	int Y1 =60;
	int Width =120;
	int Height = 30;
	
	CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
	DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Alarm_Heading[0],false);
	X1 +=Width;
	Parameter_ID = new int[CChildView::TotalAlarmHeading];

	for(int index =LeftMostParameter; index<LeftMostParameter+4;index++)
	{
		TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		memset(Parameter_ID,0,CChildView::TotalAlarmHeading);
		Parameter_ID[index]= index+1;
		for(int index1 =1;index1<CChildView::TotalAlarmHeading;index1++)
		{			
			int ID = Parameter_ID[index];
			if(ID == CChildView::AlarmLogPara_ID[index1])
			{
				
				DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Alarm_Heading[index1],false);
			}

			if(Parameter_ID[index] ==0)
				DrawText(pDC, SmallFont, Black, TextRect, "****",false);
		}
		X1 +=Width;
	}
	CPen *oldPen;
	CPen NewPen;
	NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[Black]);
	oldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(20,Y1+Height+10);
	pDC->LineTo(X1,Y1+Height+10);
	pDC->SelectObject(oldPen);
	NewPen.DeleteObject();
}