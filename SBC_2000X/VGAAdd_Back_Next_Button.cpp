/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGAAdd_Back_Next_Button.cpp_v   1.6   13 Mar 2015 06:33:46   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGAAdd_Back_Next_Button.cpp_v  $
 * 
 *    Rev 1.6   13 Mar 2015 06:33:46   amaurya
 * Change to avoid page no go below 1.
 * 
 *    Rev 1.5   25 Sep 2014 12:00:26   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.4   09 Jul 2014 07:11:08   akaushal
 * CVGAAdd_Back_Next_Button::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:38 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:22 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:08 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VGAAdd_Back_Next_Button.h"
#include "Application.h"
#include "ChildView.h"
#include "VgaMenuItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVGAAdd_Back_Next_Button::CVGAAdd_Back_Next_Button(int type)
{
	SetType(type);
	pressed1=false;
	ObjectPageNum=PAGEALL;
	RectShow=1;
}

CVGAAdd_Back_Next_Button::~CVGAAdd_Back_Next_Button()
{

}

/****************************************************************************/
/* this function is used to draw next or previous button when called.		*/
/****************************************************************************/
void CVGAAdd_Back_Next_Button::Draw(CDC *pDC)
{
	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	int type=GetType();
	if(type == CVgaMenu::NEXT)
		DrawText(pDC, Bigfont, CChildView::TextColor, rect, " >> ",true);
	else if(type ==CVgaMenu::BACK)
		DrawText(pDC, Bigfont, CChildView::TextColor, rect, " << ",true);
}
/*********************************************************************************/
/* This function is called when the user clicks on next/previous button.		 */
/* The function accordingly increments or decrements the page number and draws	 */	
/* the new screen																 */
/*********************************************************************************/

bool CVGAAdd_Back_Next_Button::MouseClick(const CPoint &p, CChildView *view)
{	
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	int type=GetType();
	pressed1=false;
	CDC*pDC=view->GetDc();
	Draw_Pressed_Released_Button(pDC);
	view->ReleaseDc(pDC);

	/* for OnLButtonUp*/
	if(type== CVgaMenu::NEXT)//next
	{
		/*releasing button*/
		int Total_Pages=(view->Total_Objects)/(MaxItems_PerPage);
		int remender=(view->Total_Objects)%(MaxItems_PerPage);
		if(remender!=0)
			Total_Pages++;
		if(page_no<Total_Pages)
			page_no++;
		else
			page_no=Total_Pages;
		view->Invalidate();
		//return true;

	}
	else if(type==CVgaMenu::BACK)//prev
	{
		/*releasing button*/
		if(page_no>1)
			page_no--;
		else
			page_no=1;
		view->Invalidate();
	}
	return true;
}
