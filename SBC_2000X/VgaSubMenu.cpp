/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaSubMenu.cpp_v   1.8   25 Sep 2014 12:02:46   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaSubMenu.cpp_v  $
 * 
 *    Rev 1.8   25 Sep 2014 12:02:46   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.7   09 Jul 2014 07:24:02   akaushal
 * CVgaSubMenu::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.6   20 May 2014 11:15:46   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.5   07 May 2014 13:18:40   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.4   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:14:00 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:06:28 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:36 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:14 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "SBC.h"
#include "VgaSubMenu.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VGA.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVgaSubMenu::CVgaSubMenu(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	submenu = e->GetAttribute("menu");
	menuNak = e->GetAttribute("menunak");
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

CVgaSubMenu::~CVgaSubMenu()
{
}

void CVgaSubMenu::Draw(CDC *pDC) 
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	int ButtonColour=CChildView::Button_Color;
	DrawRect(pDC, ButtonColour, rect);
	Draw_Pressed_Released_Button(pDC);
	CVgaMenuItem::DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
}

bool CVgaSubMenu::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	if(submenu!="")
	{
		if((this->AccessLevel > CChildView::AccessLevelSystem)&&(CChildView::PasswordFlag))
		{
			unsigned char *s=0;
			view->menusname.AddTail(theApp.menuName);
			view->menus.AddTail(page_no);
			view->menupointers.AddTail(theApp.MenuPointer);
			//printf("\n this->AccessLevel > CChildView::AccessLevelSystem");
			OnKeypadScreen_flag=true;
			view->BuildCompleteKeypadList(VGA_PASSWORD,s,0,PASSWORDCOMMAND,this);
			view->Invalidate();
			//theApp.menuName = submenu;
		}
		else 
		{
			CVgaMenu * menu;
			if (theApp.menus.Lookup(submenu, menu))
			{
				view->menusname.AddTail(theApp.menuName);
				view->menus.AddTail(page_no);
				view->menupointers.AddTail(theApp.MenuPointer);
				page_no=1;
				CChildView::thisPtr->ModifyObjectList(menu);   
				theApp.menuName = submenu;
				theApp.MenuPointer=menu;
			}
			view->Invalidate();
		}
	}
	return true;
}