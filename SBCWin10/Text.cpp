/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Text.cpp_v   1.8   18 Aug 2014 07:51:50   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Text.cpp_v  $
 * 
 *    Rev 1.8   18 Aug 2014 07:51:50   rjamloki
 * Changed constructor to add text position
 * 
 *    Rev 1.7   28 Jul 2014 14:14:18   rjamloki
 * Getipaddress function removed
 * 
 *    Rev 1.6   09 Jul 2014 07:05:50   akaushal
 * Removed unused variable in GetIPAddress().
 * 
 *    Rev 1.5   07 May 2014 13:09:50   akaushal
 * code cleanup
 * 
 *    Rev 1.4   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:34 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:26 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "Text.h"
#include "XmlElement.h"
#include "Variable.h"
#include <WinSock.h>
#include "VGA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CText::CText(CString str,int tx1,int ty1,int tx2,int ty2)
{
	X1 = tx1;
	Y1 = ty1;
	X2 = tx2;
	Y2 = ty2;
	RectShow=0;
	text=str;
	SubText=CChildView::thisPtr->CurrentLanguageName;
	SubText=SubText.SpanExcluding(_T("."));
	rect.SetRect(X1,Y1,X2,Y2);
}
CText::CText(CXmlElement * e)
{
	rect = CRect(0,0,0,0);
	X1 = _ttoi(e->GetAttribute("X1"));
	Y1 = _ttoi(e->GetAttribute("Y1"));
	X2 = _ttoi(e->GetAttribute("X2"));
	Y2 = _ttoi(e->GetAttribute("Y2"));
	Rect = CRect(X1,Y1,X2,Y2);
	rect = CRect(X1,Y1,X2,Y2);
	SetRect(rect);
	RectShow=0;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	FunName=e->GetAttribute("funname");
	if(FunName!="")
	{
		void *ptr;
		CString (*rmn)(CString);
		if(functionCall.Lookup(FunName,ptr))
		{
			rmn = (CString (*)(CString))ptr;
			SubText=rmn(SubText);
		}
	}
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

CText::~CText()
{

}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Text object When any Text type object is                */
/*  found in menu/submenu item list for current page                              */
/**********************************************************************************/
void CText::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText + SubText,false);
}

bool CText::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}
