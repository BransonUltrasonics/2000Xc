/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaVariable.cpp_v   1.12   08 Apr 2015 13:09:20   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaVariable.cpp_v  $
 * 
 *    Rev 1.12   08 Apr 2015 13:09:20   AnPawar
 * Initializing MaxInputDigits variable in VgaVariable()  to fix the max input digits issue in batch count field.
 * 
 *    Rev 1.11   28 Mar 2015 04:57:24   RJamloki
 * DisableDrawText check added in Draw function.This value is taken from from Main.gui. If it is 1 then vga variable field is not drawn.
 * 
 *    Rev 1.10   28 Nov 2014 08:33:38   rjamloki
 *  Warnings removed
 * 
 *    Rev 1.9   25 Sep 2014 12:13:04   AnPawar
 * MouseClick() function changed.
 * 
 *    Rev 1.8   18 Aug 2014 08:08:20   rjamloki
 * Added suuport for Text On button.
 * 
 *    Rev 1.7   09 Jul 2014 07:26:16   akaushal
 * CVgaVariable::MouseClick() function modified to check change conditions.
 * 
 *    Rev 1.6   09 Jun 2014 12:07:00   rjamloki
 * Variable initialization in constructor
 * 
 *    Rev 1.5   07 May 2014 13:15:58   akaushal
 * Disable flag added
 * 
 *    Rev 1.4   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:14:04 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:06:28 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:36 rjamloki 
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "VgaVariable.h"
#include "XmlElement.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define PrintSelect_Rect CRect(516,2,636,38)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CMapStringToString values;

CVgaVariable::CVgaVariable(CXmlElement * e)
{
	IDVariable = 0;
	Value = 0;
	MinVal = 0;
	MaxVal = 0;
	Insertunitflag = 0;
	TextOnButton = false;
	rect = CRect(0, 0, 0, 0);
	X1 = _ttoi(e->GetAttribute("X1"));
	Y1 = _ttoi(e->GetAttribute("Y1"));
	X2 = _ttoi(e->GetAttribute("X2"));
	Y2 = _ttoi(e->GetAttribute("Y2"));
	rect = CRect( X1, Y1, X2, Y2);
	Rect = CRect( X1, Y1, X2, Y2);

	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	Keypad_title=e->GetAttribute("Keypad_title");
	CurrentStringID=e->GetAttribute("StrID1");
	CurrentString=CVgaMenuItem ::LinearSearch(CurrentStringID);
	NewStringID= e->GetAttribute("StrID2");
	NewString=CVgaMenuItem ::LinearSearch(NewStringID);
	CString str=e->GetAttribute("format");
	CString Formatvalue;
	values.Lookup(str, Formatvalue);
	Format=_ttoi(Formatvalue);
	Digits=_ttoi((e->GetAttribute("Digits")));
	Bitmask=_ttoi((e->GetAttribute("Bitmask")));
	ID=_ttoi((e->GetAttribute("ID")));
	Disable=_ttoi((e->GetAttribute("Disable")));
	RectShow=_ttoi((e->GetAttribute("Rectshow")));
	TextType=_ttoi((e->GetAttribute("TextType")));
	Unitshow=_ttoi((e->GetAttribute("Unitshow")));
	FunName=e->GetAttribute("funname");
	MaxInputDigits =_ttoi((e->GetAttribute("MaxInputDigits")));	
	TextOnButton = (_ttoi(e->GetAttribute("TextOnButton"))) != 0;
	MenuNak=e->GetAttribute("menunak");
	DisableDrawText =_ttoi((e->GetAttribute("DisableDrawText")));
	DisableFlag = 0;
	NewVal = 0;
	POSITION pos = e->children.GetHeadPosition();
	Variable_Text="";
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

CVgaVariable::~CVgaVariable()
{

}

/**********************************************************************************/
/*                                                                                */
/*  This function Draws a Variable object When any Variable type object is        */
/*  found in menu/submenu item list for current page                              */
/**********************************************************************************/

void CVgaVariable::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	CString TempStr="";
	if(RectShow)
	{
		if(CChildView::thisPtr->RunResultScreen)
			SetRect(PrintSelect_Rect);

		DrawRect(pDC, CChildView::Button_Color, rect);
		Draw_Pressed_Released_Button(pDC);
		CString str=TempText;
		TempText=TempText.SpanExcluding(_T("("));
		DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
		DrawRect(pDC,CChildView::Back_Color, CRect(rect.right,rect.top,
			(rect.right+100),rect.bottom));

		DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,rect.top,
			(rect.right+100),rect.bottom),
			Variable_Text,false);
		TempText=str;
	}
	else
	{
		if(DisableDrawText == 0)
		{
			TempStr =TempText+Variable_Text;
			DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempStr,false);
		}
	}
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any Variable object is clicked by the user          */
/* This funtion sends a host command to get the Variable information          .      */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/* If an ACK is obtained then the keypad is displayed								 */	
/*************************************************************************************/

bool CVgaVariable::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	OnKeypadScreen_flag=true;
	int length =VARMAXMINLENGTH;
	unsigned char data1[VARMAXMINLENGTH];
	union 
	{
		short i;
		char c[VARMAXMINLENGTH];
	} u;
	u.i=EnumID;
	data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
	CHostCommand * request = new CHostCommand(GetVariableData_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);

	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
		{
			this->MinVal =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			this->MaxVal =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			unsigned char * data = (unsigned char *) &Variable_Text;


			view->BuildCompleteKeypadList(GetType(),data,&Variable_Text,EnumID,this);
			view->Invalidate();
		}
		else if(ch==NAK)
		{
			view->ProcessNak(data,length,(int)this,0);
			view->Invalidate();
		}
		delete response;
	}
	return true;
}
