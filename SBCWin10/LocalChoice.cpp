/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/LocalChoice.cpp_v   1.6   25 Sep 2014 12:00:30   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/LocalChoice.cpp_v  $
 * 
 *    Rev 1.6   25 Sep 2014 12:00:30   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.5   09 Jul 2014 06:59:40   akaushal
 * CLocalChoice::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3    05 Mar 2014 14:13:20 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2    03 Jan 2014 09:04:58 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1    18 Dec 2013 10:00:30 rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0    03 Apr 2013 10:09:50 amaurya
 * Initial Revision.
*/


#include "stdafx.h"
#include "VGA.h"
#include "LocalChoice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLocalChoice::CLocalChoice(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	FunName=e->GetAttribute("FunName");
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
	Rect = CRect(X1,Y1,X2,Y2);
	TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.
	ChoiceText1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
	ChoiceText2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
	ChoiceText="";
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
}

CLocalChoice::~CLocalChoice()
{

}

void CLocalChoice::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	SetRect(Rect);
	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	if(TextColor==White)
		TextColor=CChildView::TextColor;
	DrawText(pDC, SmallFont, TextColor, rect, TempText+ChoiceText,true);
}

bool CLocalChoice::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	if(FunName!="")
	{
		void *ptr;
		void (*rmn)(int,CLocalChoice *);
		if(functionCall.Lookup(FunName,ptr))
		{
			rmn = (void (*)(int,CLocalChoice *))ptr;
			rmn(EnumID,this);
		}
	}
	return true;
}