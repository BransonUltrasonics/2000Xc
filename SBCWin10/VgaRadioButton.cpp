/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaRadioButton.cpp_v   1.7   25 Sep 2014 12:02:48   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaRadioButton.cpp_v  $
 * 
 *    Rev 1.7   25 Sep 2014 12:02:48   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.6   09 Jul 2014 07:17:04   akaushal
 * CVgaRadioButton:: MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.5   27 May 2014 18:11:46   akaushal
 * Updated code to get multiple choice from GUI.
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
#include "VgaRadioButton.h"
#include "XmlElement.h"
#include "Variable.h"
#include "Application.h"
#include "VGA.h"
#include "RadioMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVgaRadioButton::CVgaRadioButton(CXmlElement * e)
{
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	Selected=false;
	value=_ttoi(e->GetAttribute("Value"));
	//value = 1 << ( _ttoi(e->GetAttribute("Value")) );
	multiChoiceFlag = _ttoi(e->GetAttribute("multipleChoiceFlag"));
   if(multiChoiceFlag == 1)
   {
	   value = 1 << ( _ttoi(e->GetAttribute("Value")) );
   }
	ID=0;
	Format=_ttoi((e->GetAttribute("format")));
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

CVgaRadioButton::~CVgaRadioButton()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a RadioButton object When any RadioButton type object is     */
/*  found in menu/submenu item list for current page. this function draws an empty   */
/*  rectangle if the radiobutton is not selected and a filled rectengle if the radio */
/*  button id selected.																 */
/*************************************************************************************/
void CVgaRadioButton::Draw(CDC *pDC)
{
	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	text=FormatString(text);

	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	CVgaMenuItem::DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	if(!Selected)
	{	
		CBrush brushYellow;
		brushYellow.CreateSolidBrush(CChildView::Color_Array[CChildView::Back_Color]);
		CBrush * oldBrush;
		oldBrush = pDC->SelectObject(&brushYellow);
		CPen pen,pen1;
		pen.CreatePen(PS_SOLID,2,Black);
		pDC->SelectObject(&pen);
		pDC->Rectangle( CRect(rect.left-20,rect.top+16,rect.left-10,rect.top+26));
		pen1.CreatePen(PS_NULL,2,Black);
		pDC->SelectObject(&pen1);
		pDC->SelectObject(oldBrush);
		brushYellow.DeleteObject();
		pen.DeleteObject();
		pen1.DeleteObject();
	}
	else
		pDC->FillSolidRect(rect.left-20,rect.top+16,10,10,Black);
}


/**********************************************************************************/
/*                                                                                */
/*  This function is called when any RadioButton object is clicked by the user    */
/* it displays the currently clicked radio button as selected and de selectes the */
/* previously selected radio Button.                                              */
/**********************************************************************************/

bool CVgaRadioButton:: MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	if( multiChoiceFlag == 1 )
		SetVariable_Value_multi_radio_button(p,view);
	else
		SetVariable_Value_radio_button(p,view);

	view->Invalidate ();
	ERRORBEEP;
	return true;
}


void CVgaRadioButton::SetSelected(bool radio_state)
{
	Selected=radio_state;
}

int CVgaRadioButton::GetRadioValue()
{
	return value;
}

int CVgaRadioButton::GetMultiChoiceFlag()
{
	return multiChoiceFlag;
}

bool CVgaRadioButton::GetSelected()
{
	return Selected;
}



/*****************************************************************************************/
/*   Function called from MouseClick function,when user click on any radio button.       */                      
/*   This function set the pressed button value to selected and other button to deselect.*/
/*****************************************************************************************/
void CVgaRadioButton::SetVariable_Value_radio_button(const CPoint &point,CChildView *view)
{
	CVgaMenu * menu1;
	menu1=theApp.MenuPointer;
	CVgaMenuItem * object =0;
	CRect rect;
	CDC*pDC = view->GetDc();
	int num=0;
	int last_obj=((MaxItems_PerPage*page_no)+2);
	int first_obj=((MaxItems_PerPage*(page_no-1)+3));
	POSITION pos = menu1->items.GetHeadPosition();
	while (pos)
	{
		object= menu1->items.GetNext(pos);
		num++;

		if((object->GetType())==(CVgaMenu::RADIO_BUTTON)
			||(object->GetType())==(CVgaMenu::RADIOLARGE))
		{
			rect=object->GetRect();
			if(object->GetRect().PtInRect(point)&&(object->GtPageNum()==page_no))
			{

				object->SetSelectedState(true);
				if(num>=first_obj && num<=last_obj)
				{
					pDC->FillSolidRect(rect.left-20,rect.top+16,10,10,Black);//draw black rectangle
				}

			}
			else
			{
				object->SetSelectedState(false);
				if(num>=first_obj && num<=last_obj)
				{

					CBrush brushYellow;
					brushYellow.CreateSolidBrush(CChildView::Color_Array[CChildView::Back_Color]);
					CBrush * oldBrush;
					oldBrush = pDC->SelectObject(&brushYellow);

					CPen pen,pen1;
					pen.CreatePen(PS_SOLID,2,Black);
					pDC->SelectObject(&pen);
					pDC->Rectangle( CRect(rect.left-20,rect.top+16,rect.left-10,rect.top+26));
					pen1.CreatePen(PS_NULL,2,Black);
					pDC->SelectObject(&pen1);
					pDC->SelectObject(oldBrush);
					brushYellow.DeleteObject();
					pen.DeleteObject();
					pen1.DeleteObject();
				}
			}
		}
	}
	view->ReleaseDc(pDC);
}

/*****************************************************************************************/
/*   Function called from MouseClick function,when user click on any radio button.       */                      
/*   This function set the pressed button value to selected and other button remain in   */
/*   their current state                                                                 */
/*****************************************************************************************/
void CVgaRadioButton::SetVariable_Value_multi_radio_button(const CPoint &point,CChildView *view)
{
	CVgaMenu * menu1;
	menu1=theApp.MenuPointer;
	CVgaMenuItem * object =0;
	CRect rect;
	CDC*pDC = view->GetDc();
	int num=0;
	int last_obj=((MaxItems_PerPage*page_no)+2);
	int first_obj=((MaxItems_PerPage*(page_no-1)+3));
	POSITION pos = menu1->items.GetHeadPosition();
	while (pos)
	{
		object= menu1->items.GetNext(pos);
		num++;

		if((object->GetType())==(CVgaMenu::RADIO_BUTTON)
			||(object->GetType())==(CVgaMenu::RADIOLARGE))
		{
			rect=object->GetRect();
			if(object->GetRect().PtInRect(point)&&(object->GtPageNum()==page_no))
			{

				if(object->GetSelectedRadio() == false )
				{
					object->SetSelectedState(true);
					if(num>=first_obj && num<=last_obj)
					{
						pDC->FillSolidRect(rect.left-20,rect.top+16,10,10,Black);//draw black rectangle
					}
				}
				else
				{
					object->SetSelectedState(false);
					if(num>=first_obj && num<=last_obj)
					{

						CBrush brushYellow;
						brushYellow.CreateSolidBrush(CChildView::Color_Array[CChildView::Back_Color]);
						CBrush * oldBrush;
						oldBrush = pDC->SelectObject(&brushYellow);

						CPen pen,pen1;
						pen.CreatePen(PS_SOLID,2,Black);
						pDC->SelectObject(&pen);
						pDC->Rectangle( CRect(rect.left-20,rect.top+16,rect.left-10,rect.top+26));
						pen1.CreatePen(PS_NULL,2,Black);
						pDC->SelectObject(&pen1);
						pDC->SelectObject(oldBrush);
						brushYellow.DeleteObject();
						pen.DeleteObject();
						pen1.DeleteObject();
					}		
				}
			}

		}
	}
	view->ReleaseDc(pDC);
}

CString CVgaRadioButton::FormatString(CString text)
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