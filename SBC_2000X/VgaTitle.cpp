/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaTitle.cpp_v   1.13   03 Feb 2015 07:25:32   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaTitle.cpp_v  $
 * 
 *    Rev 1.13   03 Feb 2015 07:25:32   amaurya
 * LoginButtonEnable and LogoutButtonEnable variable removed.
 * 
 *    Rev 1.12   28 Nov 2014 08:33:18   rjamloki
 *  Warnings removed
 * 
 *    Rev 1.11   28 Jul 2014 14:40:48   rjamloki
 * added	LogoutButtonEnable = false; LoginButtonEnable = false; 
 * 
 *    Rev 1.10   09 Jul 2014 07:24:34   akaushal
 * CVgaTitle() changed.
 * 
 *    Rev 1.9   11 Jun 2014 10:50:54   rjamloki
 * Added function call on draw title. 
 * 
 *    Rev 1.8   09 Jun 2014 12:06:30   rjamloki
 * Variable initialization in constructor
 * 
 *    Rev 1.7   27 May 2014 06:46:46   amaurya
 * Display Lock and Alarm Button disable on Login Screen
 * 
 *    Rev 1.6   21 Apr 2014 13:54:42   akaushal
 * CVgaTitle::Draw() function to initialize DIAGNOSTICS_USERIO timer.
 * 
 *    Rev 1.5   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:14:00 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.3     27 Feb 2014 01:58:00 jerryw.wang  
 * Added the MenuTypes variable for the buttons arrangement on the specific menu.
 *
 *    Rev 1.2     03 Jan 2014 09:06:28 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:36 rjamloki   
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:14 amaurya      
 * Initial Revision.
 * 
*/

#include "stdafx.h"
#include "SBC.h"
#include "VGA.h"
#include "VgaTitle.h"
#include "XmlElement.h"
#include "Variable.h"

//#include "GUIDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVgaTitle::CVgaTitle(CString Title)
{
	text = Title;
	RectShow=1;
	rows = DEFAULT_NO_ROWS;
	columns = DEFAULT_NO_COLUMNS;
	ButtonTypes = DEFAULT_BUTTONTYPE;
	ExitFlag = 0;
	SaveFlag = 0;
	ObjectPageNum=PAGEALL;
	BottomHalfPresent = false;
	BottomMenuDisable = false;
	DrawAlarmButton = true;
	MenuTypes = false;
	pageinfo = false;	
}

CVgaTitle::CVgaTitle(CXmlElement * element)
{
	textID=element->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	TitleArray.SetSize(MAXTITLE);
	RectShow=1;
	text.MakeUpper();
	justify = element->GetAttribute("justify");
	pageinfo = element->GetBoolAttribute("pageinfo");
	rows = _ttoi(element->GetAttribute("RowPerPage"));
	columns = _ttoi(element->GetAttribute("ColumnPerPage"));
	ButtonTypes = _ttoi(element->GetAttribute("Buttontype"));
	MenuTypes = _ttoi(element->GetAttribute("MenuType")) != 0;
	ExitFlag=_ttoi(element->GetAttribute("ExitFlag"));
	SaveFlag=_ttoi(element->GetAttribute("SaveFlag"));
	CString MenuPresent=element->GetAttribute("BottomHalfPresent");
	BottomMenuDisable = _ttoi(element->GetAttribute("BottomMenuDisable")) != 0;
	FunName=element->GetAttribute("FunName");
	argument=element->GetAttribute("argumentname");
	if(element->GetAttribute("DrawAlarmButton") == "false")
		DrawAlarmButton = false;
	else
		DrawAlarmButton = true;

	if(MenuPresent!="")
		BottomHalfPresent = _ttoi(MenuPresent) != 0;
	else
		BottomHalfPresent = false;
	ObjectPageNum=PAGEALL;
	POSITION pos = element->children.GetHeadPosition();
	int i=0;
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		CString tag = e->GetTag();
		if (tag == "condition")
			AddCondition(e);
		else if(tag=="titles")
		{
			CString TitleString = e->GetAttribute("TitleID");
			TitleArray[i]= CVgaMenuItem ::LinearSearch(TitleString);
			i++;
		}
		else
			ASSERT(FALSE);
	}
}

CVgaTitle::~CVgaTitle()
{

}

void CVgaTitle::Draw(CDC *pDC) 
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	if(BottomHalfPresent==true)
		CChildView::thisPtr->BottomHalfScreen=true;
	else
		CChildView::thisPtr->BottomHalfScreen=false;

	if(CChildView::thisPtr->DiagIOScreen == true)
	{
		CChildView::InitialiseTimer(DIAGNOSTICS_USERIO_TIMER,DIAGNOSE_REFRESH_TIME);
	}

	if(FunName!="")
	{
		if(argument!="")
		{
			void *ptr;
			void (*rmn)(int);
			if(functionCall.Lookup(FunName,ptr))
			{
				rmn = (void (*)(int))ptr;
				rmn(EnumID);
			}
		}
		else
		{
			void *ptr;
			void (*rmn)(int);
			if(functionCall.Lookup(FunName,ptr))
			{
				rmn = (void (*)(int))ptr;
				int Address=(int)this;
				rmn(Address);
			}
		}
	}

	rect=Title_Rect;
	DrawRect(pDC,CChildView::TitleBarColor, Title_Rect);
	CVgaMenuItem::DrawText(pDC, Bigfont, White, Title_Rect,TempText,true);

}

bool CVgaTitle::MouseClick(const CPoint &p, CChildView *view)
{
	// do nothing, no clicking on menu title
	return false;
}

void WeldResultScreen(int Address)
{
	CChildView::RunResultScreen=true;
}