/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaChoice.cpp_v   1.13   26 Jan 2015 13:39:36   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaChoice.cpp_v  $
 * 
 *    Rev 1.13   26 Jan 2015 13:39:36   rjamloki
 * Removed redundant for loop
 * 
 *    Rev 1.12   25 Sep 2014 12:02:50   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.11   28 Jul 2014 14:35:08   rjamloki
 * void CheckPrinterOnline(int Choice_value)  function  removed
 * 
 *    Rev 1.10   09 Jul 2014 07:14:22   akaushal
 * CVgaChoice::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.9   09 Jun 2014 12:02:28   rjamloki
 * Variable initialization in constructor. 
 * 
 *    Rev 1.8   20 May 2014 11:12:44   rjamloki
 * Function CheckStorageFormat() removed  
 * 
 *    Rev 1.7   07 May 2014 13:14:56   akaushal
 * Code Cleanup
 * 
 *    Rev 1.6   21 Apr 2014 13:52:52   akaushal
 * CheckStorageFormat() function added to check whether Binary or PDF 
 * 
 *    Rev 1.5   28 Mar 2014 14:33:18   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:40 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:06:24 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     19 Dec 2013 06:16:52 rjamloki      
 * Changed macros to build on both EVC and VC++.
 *
 *    Rev 1.1     18 Dec 2013 10:00:34 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:10 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "VgaChoice.h"
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CChildView::PrintingSetup PrintSetup;

CVgaChoice::CVgaChoice(CXmlElement * e)
{
	Choice_value = 0;
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	FunName=e->GetAttribute("FunName");
	ChoiceText1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
	ChoiceText2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
	ChoiceText="";
	submenu=e->GetAttribute("menu");
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

CVgaChoice::~CVgaChoice()
{

}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Choice object When any Choice type object is found in   */
/*  menu/submenu item list for current page                                       */
/**********************************************************************************/
void CVgaChoice::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
		rect.top,
		(rect.right+90),
		rect.bottom));
	DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom), ChoiceText,false);
}

bool CVgaChoice::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	int length =INTEGERLENGTH;
	unsigned char data[INTEGERLENGTH + 1];
	union 
	{
		short i;
		char c[2];
	} u;
	u.i=EnumID;
	data[1]=u.c[0];
	data[0]=u.c[1];
	union {
		int choice_value;
		char y[INTEGERLENGTH];
	} v;
	int tempvalue = Choice_value;
	if((Choice_value & 1) == 1)
	{
		Choice_value &= ~(1);
	}
	else
	{
		Choice_value |= 1;
	}
	v.choice_value=Choice_value;//object->GetRadio_Value();//getting radio value to char array.
	data[2]=(char)v.y[1];
	data[3]=(char)v.y[0];
	unsigned char * data1 = (unsigned char *) &data[0];
	CHostCommand * request = new CHostCommand(SetValue_FunID, data1, length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		char ch=CHostCommand::AckNak();
		data1 = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
		{
			int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
			if(refresh)
			{
				theApp.GetSystemVariable();   
			}
			Choice_value=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
			if(FunName!="")
			{
				void *ptr;
				void (*rmn)(int);
				if(functionCall.Lookup(FunName,ptr))
				{
					rmn = (void (*)(int))ptr;
					rmn(Choice_value);
				}
			}
			if(Choice_value)
			{
				if(submenu!="")
				{
					CVgaMenu * menu;
					if (theApp.menus.Lookup(submenu, menu))
					{
						view->menupointers.AddTail(theApp.MenuPointer);
						view->menusname.AddTail(theApp.menuName);
						view->menus.AddTail(page_no);
						page_no=1;   
						theApp.menuName = submenu;
						theApp.MenuPointer=menu;
					}		
				}

				ChoiceText = "=" + ChoiceText2;
			}
			else
			{
				ChoiceText = "=" + ChoiceText1;
			}
			{
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
			}
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
			view->Invalidate ();
		}
		else
		{
			Choice_value=tempvalue;
			view->ProcessNak(data1,length,(int)this,0);
		}
		delete response;
	}
	return true;
}


void PMCScreenCheck(int Choice_value)
{
	if(Choice_value)
	{
		CChildView::thisPtr->PMCScreen=true;
		CChildView::thisPtr->PMCDisable=true;
	}
	else
	{
		CChildView::thisPtr->PMCScreen=false;
		CChildView::thisPtr->PMCDisable=!CChildView::thisPtr->PMCDisable;
	}
}
