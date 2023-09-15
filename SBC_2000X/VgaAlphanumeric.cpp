/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaAlphanumeric.cpp_v   1.15   Jun 01 2017 16:23:14   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaAlphanumeric.cpp_v  $
 * 
 *    Rev 1.15   Jun 01 2017 16:23:14   RJamloki
 * change Suffix should be Ctr not Crt
 * 
 *    Rev 1.14   17 Jun 2016 10:30:44   RJamloki
 * Don't show value when alphanumeric is PASSWORD_ID
 * 
 *    Rev 1.13   28 Nov 2014 08:32:42   rjamloki
 * Warning removed
 * 
 *    Rev 1.12   25 Sep 2014 12:00:24   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.11   11 Sep 2014 09:51:30   rjamloki
 * CurrentTextOnly flag added for Event Reason keypad
 * 
 *    Rev 1.10   02 Sep 2014 03:34:08   rjamloki
 *  Added CString CharNotAllowed to read the characters not allowed from main.gui
 * 
 *    Rev 1.9   18 Aug 2014 08:02:36   rjamloki
 * Code Review fixes . Using NO_COLOR instead of -1
 * 
 *    Rev 1.8   28 Jul 2014 14:28:22   rjamloki
 * changes for clamp on alarm user verification menu.
 * 
 *    Rev 1.7   09 Jul 2014 07:11:38   akaushal
 * CVgaAlphanumeric::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.6   09 Jun 2014 12:01:06   rjamloki
 * CVgaAlphanumeric() changed.
 * 
 *    Rev 1.5   07 May 2014 13:13:32   akaushal
 * flag to display button that cannot be clicked.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:40 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:06:22 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:34 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:08 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaAlphanumeric.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaAlphanumeric::CVgaAlphanumeric(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	X1 = _ttoi(e->GetAttribute("X1"));
	Y1 = _ttoi(e->GetAttribute("Y1"));
	X2 = _ttoi(e->GetAttribute("X2"));
	Y2 = _ttoi(e->GetAttribute("Y2"));
	rect = CRect( X1, Y1, X2, Y2);
	Rect = CRect( X1, Y1, X2, Y2);
	RectShow=_ttoi(e->GetAttribute("Rectshow"));
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	Alpha_Text="";
	TitleKeyPad=CVgaMenuItem ::LinearSearch(e->GetAttribute("TitleID"));
	CurrentString=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID1"));
	NewString=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID2"));
	CharAllowed=_ttoi(e->GetAttribute("Charallowed"));
	CharHidden=_ttoi(e->GetAttribute("Charhidden"));
	CharNotAllowed = e->GetAttribute("CharNotAllowed");
	MenuNak=e->GetAttribute("menunak");
	MenuAck=e->GetAttribute("menuack");
	ShowValue=_ttoi(e->GetAttribute("ShowValue"));
	FunName=e->GetAttribute("funname");
	CurrentTextOnly = (_ttoi(e->GetAttribute("CurrentTextOnly")) != 0);
	//UseOtherColor if this is true then text field will be filled with the FillColor
	if(e->GetAttribute("UseOtherColor")=="true")
	    UseOtherColor=true;
	else
		UseOtherColor=false;
	if(UseOtherColor)
		FillColor=_ttoi(e->GetAttribute("FillColor"));
	else
		FillColor = NO_COLOR;
	
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

CVgaAlphanumeric::~CVgaAlphanumeric()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a Alphanumeric object When any Alphanumeric type object is   */
/*  found in menu/submenu item list for current page                                 */
/*************************************************************************************/
void CVgaAlphanumeric::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	DrawRect(pDC,CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	
	if(FillColor > NO_COLOR)
		DrawRect(pDC, FillColor, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom));
	else
		DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom));
	if(ShowValue) {
		if(textID==XSTR(PASSWORD_ID)) {
			int DummyPasswordLen=Alpha_Text.GetLength();
			int DummyPasswordCtr=0;
			CString DummyPasswordStr;  
			if(DummyPasswordLen!=0)DummyPasswordStr=_T(" = ");
			for(DummyPasswordCtr=0;DummyPasswordCtr<DummyPasswordLen;DummyPasswordCtr++)DummyPasswordStr+=_T("*");
			DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
			rect.top,
			(rect.right+100),
			rect.bottom),DummyPasswordStr,false);
		} else {
			DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
			rect.top,
			(rect.right+100),
			rect.bottom),Alpha_Text,false);
		}
	}
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any Alphanumeric object is clicked by the user      */
/* This funtion sends a host command to get the Alpha string information          .  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/* If an ACK is obtained then the keypad is displayed and the new alpha string       */
/* entered is send back to 332.														 */	
/*************************************************************************************/

bool CVgaAlphanumeric::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	OnKeypadScreen_flag=true;
	unsigned char * data = (unsigned char *) &Alpha_Text;
	view->BuildCompleteKeypadList(GetType(),data,&Alpha_Text,EnumID,this);
	view->Invalidate();
	return true;
}

void CVgaAlphanumeric::ClearAlphaString(void)
{
	Alpha_Text = "";
}

/* Function returns the string stored in object.
 * First "=" is removed then string is returned */
CString CVgaAlphanumeric::GetAlphaString(void)
{
	int numReplaced;
	numReplaced = Alpha_Text.Replace('=',' ');
	if(numReplaced != 0)
		Alpha_Text.TrimLeft(' ');
	return Alpha_Text.SpanExcluding(_T("="));
}