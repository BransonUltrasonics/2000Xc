/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/AlarmButton.cpp_v   1.7   11 Dec 2014 06:47:54   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/AlarmButton.cpp_v  $
 * 
 *    Rev 1.7   11 Dec 2014 06:47:54   RJamloki
 * Code Formatting.
 * 
 *    Rev 1.6   25 Sep 2014 12:00:30   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.5   09 Jul 2014 06:41:34   akaushal
 * CAlarmButton::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.4   28 Mar 2014 14:32:52   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:12:38 rjamloki 
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:44 rjamloki  
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:26 rjamloki  
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya  
 * Initial Revision.
*/

#include "stdafx.h"

#include "AlarmButton.h"
#include "VGA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlarmButton::CAlarmButton(CXmlElement * e)
{
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	Text1=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID1"));
	Text2=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID2"));
	/*Storing Co-Ordinates of Text box.*/
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
	Rect = CRect(X1,Y1,X2,Y2);
	MenuName= e->GetAttribute("menuname");
	TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.
	BoxColor = _ttoi(e->GetAttribute("BoxColor"));//Storing Fill color of text box.
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

CAlarmButton::~CAlarmButton()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in menu/submenu item list for current page .								 */
/*																					 */
/*************************************************************************************/
void CAlarmButton::Draw(CDC *pDC)
{

	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ") + text;

	SetRect(Rect);
	if(BoxColor == 0)
		BoxColor=CChildView::Back_Color;

	DrawRect(pDC, BoxColor, rect); //Draw Alarm Button.
	Draw_Pressed_Released_Button(pDC);
	if(TextColor==0)
		TextColor=CChildView::TextColor;

	/*Draw Text with Text color and Font.*/
	DrawText(pDC, SmallFont, TextColor, rect, TempText,true);
}

bool CAlarmButton::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	CVgaMenu * menu;
	if (theApp.menus.Lookup(MenuName, menu))
	{
		view->menusname.AddTail(theApp.menuName);
		view->menus.AddTail(page_no);
		view->menupointers.AddTail(theApp.MenuPointer);
		page_no=1;
		theApp.menuName = MenuName;
		theApp.MenuPointer=menu;
		CChildView::thisPtr->ModifyObjectList(menu);   
	}
	view->Invalidate();
	return true;
}