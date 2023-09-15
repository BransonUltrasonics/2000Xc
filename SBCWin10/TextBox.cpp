/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextBox.cpp_v   1.5   09 Jun 2014 11:53:40   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextBox.cpp_v  $
 * 
 *    Rev 1.5   09 Jun 2014 11:53:40   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:34 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:28 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "TextBox.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/*************************************************************************************/
/*                                                                                   */
/*  This function creates a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in  menu/submenu item list                                                 */
/*************************************************************************************/
CTextBox::CTextBox(CXmlElement * e)
{
	ID = 0;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	/*Storing Co-Ordinates of Text box.*/
	int X1 = _ttoi(e->GetAttribute("X1"));
	int Y1 = _ttoi(e->GetAttribute("Y1"));
	int X2 = _ttoi(e->GetAttribute("X2"));
	int Y2 = _ttoi(e->GetAttribute("Y2"));
	Rect = CRect(X1,Y1,X2,Y2);
	TextFont = _ttoi(e->GetAttribute("TextFont"));//Storing Font of the text.	
	BoxColor = _ttoi(e->GetAttribute("BoxColor"));//Storing Fill color of text box.
	TextColor = _ttoi(e->GetAttribute("TextColor"));//storing Text color.

	if(BoxColor == 0)
		BoxColor=CChildView::Back_Color;
	if(TextFont > SmallFont)
		TextFont = Bigfont;

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

CTextBox::~CTextBox()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a CVGATextBox object When any CVGATextBox type object is	 */
/*  found in menu/submenu item list for current page .								 */
/*																					 */
/*************************************************************************************/
void CTextBox::Draw(CDC *pDC)
{ 
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	SetRect(Rect);
	DrawRect(pDC, BoxColor, rect);//Draw Text box rectangle with box color.
	if(TextColor==0)
		TextColor=CChildView::TextColor;

	/*Draw Text with Text color and Font.*/
	DrawText(pDC, TextFont, TextColor, rect, TempText,true);


}
bool CTextBox::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}