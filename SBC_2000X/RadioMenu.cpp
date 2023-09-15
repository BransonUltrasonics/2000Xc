/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RadioMenu.cpp_v   1.10   25 Sep 2014 12:00:30   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RadioMenu.cpp_v  $
 * 
 *    Rev 1.10   25 Sep 2014 12:00:30   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.9   09 Jul 2014 07:01:20   akaushal
 * CRadioMenu::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.8   27 May 2014 18:06:24   akaushal
 * updation for History Setup button input 
 * 
 *    Rev 1.7   20 May 2014 11:01:32   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.6   07 May 2014 13:18:38   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.5   21 Apr 2014 13:41:28   akaushal
 * Changed the construtor to create 20 radio 
 * buttons.SetSelectedRadioIndex() function                     modified. 
 * 
 *    Rev 1.4   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:26 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:04 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:3 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "SBC.h"
#include "RadioMenu.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaRadioButton.h"
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
extern CMapStringToString values;

CRadioMenu::CRadioMenu(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	StrtextID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(e->GetAttribute("textID"));
	// GetUnit_Value(this,EnumID);

	multiChoiceValue = 0;
	multiChoiceFlag = _ttoi(e->GetAttribute("multipleChoiceFlag"));

	Insertunitflag=false;
	VarText="";
	RadioMenuStr.SetSize(MAXRADIOINDEX);
	RadioMenuStrID.SetSize(MAXRADIOINDEX);
	RadioIndex=0;
	RadioMenuStrID[0]=e->GetAttribute("StrID1");
	RadioMenuStr[0]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[0]);

	RadioMenuStrID[1]=e->GetAttribute("StrID2");
	RadioMenuStr[1]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[1]);

	RadioMenuStrID[2]=e->GetAttribute("StrID3");
	RadioMenuStr[2]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[2]);

	RadioMenuStrID[3]=e->GetAttribute("StrID4");
	RadioMenuStr[3]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[3]);

	RadioMenuStrID[4]=e->GetAttribute("StrID5");
	RadioMenuStr[4]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[4]);

	RadioMenuStrID[5]=e->GetAttribute("StrID6");
	RadioMenuStr[5]= CVgaMenuItem ::LinearSearch(RadioMenuStrID[5]);

	RadioMenuStrID[6]=e->GetAttribute("StrID7");
	RadioMenuStr[6]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[6]);

	RadioMenuStrID[7]=e->GetAttribute("StrID8");
	RadioMenuStr[7]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[7]);

	RadioMenuStrID[8]=e->GetAttribute("StrID9");
	RadioMenuStr[8]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[8]);

	RadioMenuStrID[9]=e->GetAttribute("StrID10");
	RadioMenuStr[9]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[9]);

	RadioMenuStrID[10]=e->GetAttribute("StrID11");
	RadioMenuStr[10]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[10]);

	RadioMenuStrID[11]=e->GetAttribute("StrID12");
	RadioMenuStr[11]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[11]);

	RadioMenuStrID[12]=e->GetAttribute("StrID13");
	RadioMenuStr[12]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[12]);

	RadioMenuStrID[13]=e->GetAttribute("StrID14");
	RadioMenuStr[13]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[13]);

	RadioMenuStrID[14]=e->GetAttribute("StrID15");
	RadioMenuStr[14]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[14]);

	RadioMenuStrID[15]=e->GetAttribute("StrID16");
	RadioMenuStr[15]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[15]);

	RadioMenuStrID[16]=e->GetAttribute("StrID17");
	RadioMenuStr[16]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[16]);

	RadioMenuStrID[17]=e->GetAttribute("StrID18");
	RadioMenuStr[17]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[17]);

	RadioMenuStrID[18]=e->GetAttribute("StrID19");
	RadioMenuStr[18]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[18]);

	RadioMenuStrID[19]=e->GetAttribute("StrID20");
	RadioMenuStr[19]=CVgaMenuItem ::LinearSearch(RadioMenuStrID[19]);

	RectShow=_ttoi(e->GetAttribute("Rectshow"));
	submenu = e->GetAttribute("menu");
	CString str=e->GetAttribute("format");
	CString Formatvalue;
	values.Lookup(str, Formatvalue);
	Format=_ttoi(Formatvalue);
	//Format=_ttoi((e->GetAttribute("format")));
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

CRadioMenu::~CRadioMenu()
{
	if(RadioMenuStr.GetSize()>0)
		RadioMenuStr.RemoveAll();
}
/**********************************************************************************/
/*                                                                                */
/*  This function Draws a RadioMenu object When any RadioMenu type object is	  */
/*  found in menu/submenu item list for current page.							  */
/**********************************************************************************/
void CRadioMenu::Draw(CDC *pDC)
{
	if(RectShow)
	{
		if((text == "")&&(StrtextID==""))
		{

			if((VarText.GetAt(0)=='>')||((VarText.GetAt(0)=='=')))
				text=text;
			else
				text=VarText.SpanExcluding(_T(">="));
			CString str=text;
			bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
			VarText=FormatString(VarText);
			DrawRect(pDC, CChildView::Button_Color, rect);
			Draw_Pressed_Released_Button(pDC);

			CString TempText = text;
			if(CChildView::thisPtr->StringDebugFlag)
				TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;

			DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
			DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
				rect.top,
				(rect.right+100),
				rect.bottom));
			DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
				rect.top,
				(rect.right+100),
				rect.bottom), VarText,false);
			this->text=str;
		}
		else
		{
			CString str=text;
			bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
			VarText=FormatString(VarText);
			DrawRect(pDC, CChildView::Button_Color, rect);
			Draw_Pressed_Released_Button(pDC);

			CString TempText = text;
			if(CChildView::thisPtr->StringDebugFlag)
				TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;

			DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
			DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
				rect.top,
				(rect.right+100),
				rect.bottom));
			DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
				rect.top,
				(rect.right+100),
				rect.bottom), VarText,false);
			this->text=str;
		}
	}
	else
	{
		CString TempText = text;
		if(CChildView::thisPtr->StringDebugFlag)
			TempText = RadioMenuStrID[RadioIndex] + _T(" ")+ text;
		//bool Insertunitflag1=CScreenKeypad::InsertProperUnits(this, (CScreenKeypad::FORMAT)this->Format,CVgaMenu::RADIOMENU);
		DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText+VarText,false);
	}
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any RadioMenu object is clicked by the user         */
/*  The  menu items are stored and displayed as new menu.                            */
/*************************************************************************************/
bool CRadioMenu::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	if(submenu!="")
	{
		// page_no=1;
		CVgaMenu * menu;
		if (theApp.menus.Lookup(submenu, menu))
		{
			view->menusname.AddTail(theApp.menuName);
			view->menus.AddTail(page_no);
			view->menupointers.AddTail(theApp.MenuPointer);
			SetSelectedRadioIndex(menu);
			page_no=1;
			CChildView::thisPtr->ModifyObjectList(menu);
			theApp.menuName = submenu;
			theApp.MenuPointer=menu;
		}		
	}
	view->Invalidate();
	return true;
}


CString CRadioMenu::FormatString(CString text)
{
	int t=0;
	int noofchar=0;
	CString str=_T("");
	for(int b=0;b<text.GetLength();b++)
	{
		if(text.GetAt (b)== '>'|| text.GetAt(b) == '=')
		{
			t=b;
			noofchar=(text.GetLength())-t;
		}
	}
	if(noofchar>0)
	{
		return (text.Right (noofchar));
	}
	else
	{
		return str;
	}
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any RadioMenu object is clicked by the user         */
/*  & it selects currently  Radio Item.                                              */
/*************************************************************************************/
void CRadioMenu::SetSelectedRadioIndex(CVgaMenu * CurrMenuLst)
{ 
	
	if(CurrMenuLst !=NULL)
	{
		if(CurrMenuLst->items.GetCount()>0)
		{
			POSITION pos = CurrMenuLst->items.GetHeadPosition();
			CVgaMenuItem * object = CurrMenuLst->items.GetHead();
			while(pos)
			{
				if(object->GetType()==CVgaMenu::RADIO_BUTTON)
				{
					CVgaRadioButton *ptr=(CVgaRadioButton *)object;
					ptr->EnumID=EnumID;

					if(ptr->multiChoiceFlag == 1)
					{
						//printf(" RadioIndex = %d this->multiChoiceValue = %d \n",RadioIndex , this->multiChoiceValue );
                  if( (ptr->value & this->multiChoiceValue) != 0)
							ptr->Selected = true;
						else
							ptr->Selected = false;
					}
					else
					{
						if(RadioIndex==ptr->GetRadioValue())
							ptr->Selected = true;
						else
							ptr->Selected = false;
					}	
					
				}
				object=CurrMenuLst->items.GetNext(pos);
			}
		}
	}
}

