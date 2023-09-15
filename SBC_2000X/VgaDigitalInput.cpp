/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/VgaDigitalInput.cpp_v   1.5   09 Jun 2014 12:03:24   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/VgaDigitalInput.cpp_v  $
 * 
 *    Rev 1.5   09 Jun 2014 12:03:24   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.4   23 Apr 2014 11:27:58   akaushal
 * Unused SetVariable_Value_radio_button() removed
 * 
 *    Rev 1.3   21 Apr 2014 13:53:20   akaushal
 * CVgaDigitalInput::Draw() function changed to set correct color.  
 * 
 *    Rev 1.2   28 Mar 2014 14:33:20   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     05 Mar 2014 14:13:42 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.0     26 Feb 2014 02:18:18 jerryw.wang      
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaDigitalInput.h"
#include "XmlElement.h"
#include "Variable.h"
#include "Application.h"
#include "VGA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaDigitalInput::CVgaDigitalInput(CXmlElement * e)
{
	value = 0;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	/*Storing Co-ordinates*/
	X1 = _ttoi(e->GetAttribute("X1"));
	Y1 = _ttoi(e->GetAttribute("Y1"));
	X2 = _ttoi(e->GetAttribute("X2"));
	Y2 = _ttoi(e->GetAttribute("Y2"));
	FunName=e->GetAttribute("funname");
	argument=e->GetAttribute("argumentname");
	MenuName=e->GetAttribute("menuname");
	MenuNak=e->GetAttribute("menunak");
	RectShow=_ttoi(e->GetAttribute("Rectshow"));

	Activated=false;

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

CVgaDigitalInput::~CVgaDigitalInput()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a Digital Input object When any Digital Input type object is */
/*  found in menu/submenu item list for current page. this function draws a  circle  */
/*  (LED) with red if the Digital Input I/O is not activated and a green (LED) if    */
/*  the Digital Input I/O is activated                                               */
/*************************************************************************************/
void CVgaDigitalInput::Draw(CDC *pDC)
{
	int Circle_X = 0, Circle_Y = 0, Radius = 0;
	text=FormatString(text);
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;
	rect=CRect(X1,Y1,X2,Y2);
	SetRect(rect);
	CRect r(rect);
	r.OffsetRect(XOFFSET, YOFFSET);
	CSize size = pDC->GetTextExtent(text);
	Circle_X = r.left;
	Circle_Y = r.top + (r.Height() - size.cy)/2 + size.cy/2;
	Radius = size.cy/2 + 2;
	CRect tmp_Rect = CRect(X1 + 20,Y1,X2 + 20,Y2);
	SetRect(tmp_Rect);
	CVgaMenuItem::DrawText(pDC, SmallFont, CChildView::TextColor, tmp_Rect, TempText,true);
	DWORD Color;
	if(Activated)
		Color = CChildView::Color_Array[Green];
	else
		Color = CChildView::Color_Array[Red];
	CBrush brush;
	brush.CreateSolidBrush(Color);
	pDC->SelectObject(&brush);
	pDC->Ellipse(Circle_X-Radius,Circle_Y-Radius,Circle_X+Radius,Circle_Y + Radius);
	brush.DeleteObject();
}


/**********************************************************************************/
/*                                                                                */
/*  This function is called when any RadioButton object is clicked by the user    */
/* it displays the currently clicked radio button as selected and de selectes the */
/* previously selected radio Button.                                              */
/**********************************************************************************/

bool CVgaDigitalInput:: MouseClick(const CPoint &p, CChildView *view)
{
	view->Invalidate ();
	ERRORBEEP;
	return true;
}


void CVgaDigitalInput::SetSelected(bool radio_state)
{
	Activated = radio_state;
}

int CVgaDigitalInput::GetRadioValue()
{
	return value;
}

bool CVgaDigitalInput::GetSelected()
{
	return Activated;
}

CString CVgaDigitalInput::FormatString(CString text)
{
	int t=0;
	int noofchar=0;
	CString str=_T("");
	for(int b=0;b<text.GetLength();b++)
	{
		if(text.GetAt (b)== '>'|| text.GetAt(b) == '=')
		{
			t=b;
			noofchar=(text.GetLength())-(t+1);
		}
	}
	if(noofchar>0)
	{
		return (text.Right (noofchar));
	}
	else
	{
		return text;
	}
}
