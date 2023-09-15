/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Time.cpp_v   1.6   25 Sep 2014 12:00:28   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Time.cpp_v  $
 * 
 *    Rev 1.6   25 Sep 2014 12:00:28   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.5   09 Jul 2014 07:06:28   akaushal
 * CVgaTime::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3    05 Mar 2014 14:13:34 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:28 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "Time.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaMenuItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaTime::CVgaTime(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	CurrentStringID=e->GetAttribute("StrID1");
	CurrentString=CVgaMenuItem ::LinearSearch(CurrentStringID);
	NewStringID = e->GetAttribute("StrID2");
	NewString= CVgaMenuItem ::LinearSearch(NewStringID);
	Str_ReenterID=e->GetAttribute("ErrorString1ID");
	Str_Reenter= CVgaMenuItem ::LinearSearch(Str_ReenterID);
	StrInvalidEntryID=e->GetAttribute("ErrorString2ID");
	StrInvalidEntry= CVgaMenuItem ::LinearSearch(StrInvalidEntryID);
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

CVgaTime::~CVgaTime()
{

}
/***********************************************************************************/
/*                                                                                 */
/*  This function Draws a Time object When any Time type object is                 */
/*  found in menu/submenu item list for current page                               */
/***********************************************************************************/
void CVgaTime::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom));
	DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom), Time_Text,false);
}


/**********************************************************************************/
/*                                                                                */
/*  This function is called when any Time object is clicked by the user           */
/* If the Time is Editable then the keypad is displayed and the new Time          */
/* entered is send back to 332.													  */	
/**********************************************************************************/

bool CVgaTime::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	OnKeypadScreen_flag=true;
	unsigned char * data = (unsigned char *) &Time_Text;
	view->BuildCompleteKeypadList(GetType(),data,&Time_Text,EnumID,this);
	view->Invalidate();
	return true;
	//return true;
}