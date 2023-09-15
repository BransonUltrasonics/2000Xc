/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenuItem.cpp_v   1.10   02 Feb 2015 09:33:34   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenuItem.cpp_v  $
 * 
 *    Rev 1.10   02 Feb 2015 09:33:34   amaurya
 * VgaMenuItem.cpp new function defined  CVgaMenuItem::GetPSString
 * 
 *    Rev 1.9   26 Jan 2015 13:40:46   rjamloki
 * Added Try catch in DrawText
 * 
 *    Rev 1.8   10 Nov 2014 02:52:20   rjamloki
 * CVgaMenuItem() changed for Japaneese Font.
 * 
 *    Rev 1.7   28 Jul 2014 14:39:30   rjamloki
 * review comment fix.
 * 
 *    Rev 1.6   09 Jun 2014 12:05:32   rjamloki
 * Variable initialization in constructor.Draw_Pressed_Released_Button() changed
 * 
 *    Rev 1.5   20 May 2014 11:15:06   rjamloki
 * Function CVgaMenuItem::GetString() changed
 * 
 *    Rev 1.4   21 Apr 2014 13:54:04   akaushal
 * Added return values to GetRadio_Value(),GetSelectedRadio(),GetMultiChoiceFlag() .
 * 
 *    Rev 1.3   28 Mar 2014 14:33:20   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:58 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:26 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:12 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VgaMenuItem.h"
#include "XmlElement.h"
#include "Variable.h"
#include "TextIOFile.h"
#include "VgaRadioButton.h"
#include "VGA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CFont CVgaMenuItem::fontArray[2];
bool CVgaMenuItem::initialized = false;
CPen CVgaMenuItem::penBlack1;
CPen CVgaMenuItem::penWhite1;
CPen CVgaMenuItem::penDark_Gray1;
bool CVgaMenuItem::Japaneseflag=false;
int CVgaMenuItem::VGAPointer;

CVgaMenuItem::CVgaMenuItem()
{
	ObjectPageNum = 0;
	objectType = 0;
	PSType = 0;
	PageNumber = PAGEALL;
	MenuType = BottomMenu_Id;
	EnumID = 0;
	RectShow = 0;
	AccessLevel = 0;
	ModeSet = 0;
	ExpertSet = 0;
	IsDraw = false;
	pressed1 = false;
	if (!initialized)
	{	
		initialized = true;

		CString Japan_string=L"\x65e5\x672c\x8a9e\x0";
		if((CTextFileIO::sststring[0].CompareNoCase(Japan_string)))
			Japaneseflag=false;
		else
			Japaneseflag=true;


		if(!Japaneseflag)
		{
			fontArray[SmallFont].CreateFont(20 , 8, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
				FALSE, FALSE, FALSE,CTextFileIO::CurrentFontChar_Set /*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE,CTextFileIO::CurrentFontName /*_T("Arial")*/);

			fontArray[Bigfont].CreateFont(26 , 0, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
				FALSE, FALSE, FALSE,CTextFileIO::CurrentFontChar_Set /*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, CTextFileIO::CurrentFontName/*_T("Arial")*/);

		}
		else
		{		
			fontArray[SmallFont].CreateFont(20 , 0, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
				FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("MS Gothic"));

			fontArray[Bigfont].CreateFont(26 , 0, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
				FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("MS Gothic"));

		}

		penBlack1.CreatePen(PS_SOLID, 1, CChildView::Color_Array[Black]);
		penWhite1.CreatePen(PS_SOLID, 1,CChildView::Color_Array[White] );
		penDark_Gray1.CreatePen(PS_SOLID, 1,RGB(192,192,192));
	}	

}

CVgaMenuItem::~CVgaMenuItem()
{
}

void CVgaMenuItem::AddCondition(CXmlElement * element)
{
	CString varName = element->GetAttribute("variable");
	CVariable * var = theApp.GetVariable (varName);
	CCondition * cond = var->CreateCondition(element);
	if(cond!=0)
		conditions.AddTail(cond);
}
void CVgaMenuItem::DrawRect(CDC *pDC, int colour, const CRect &rect)
{
	pDC->FillSolidRect(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,CChildView::Color_Array[colour]);
}

void CVgaMenuItem::DrawText(CDC *pDC, int FontSize, int color,
	const CRect &rect, const CString &text,bool Center_Text)
{	

	TRY
	{
		CRect r(rect);
		r.OffsetRect(XOFFSET, YOFFSET);

		if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
		{
			int nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
			int nVert = pDC->GetDeviceCaps(LOGPIXELSY);
			r =Calib(rect,nHorz,nVert);
			FontSize=Font(FontSize,nHorz);
		}

		CFont *OldFont=pDC->SelectObject(&fontArray[FontSize]);
		if((color>White)||(color<COLOR_NONE))
			color=Black;
		pDC->SetTextColor(CChildView::Color_Array[color]);
		pDC->SetBkMode(TRANSPARENT);
		CSize size = pDC->GetTextExtent(text);

		CString TempText=text;
		if(CChildView::thisPtr->StringDebugFlag)
		{
			int TempLength=TempText.GetLength();
			TCHAR ch=' ';
			while((size.cx >= r.Width()) && (TempLength>0))
			{
				TempText.SetAt(TempLength-1,ch);
				TempText.TrimRight();
				size=pDC->GetTextExtent(TempText);
				TempLength=TempText.GetLength();

			}
		}
		if(Center_Text==true)
			size.cx = r.left + (r.Width() - size.cx) / 2;
		else
			size.cx = r.left;// + (r.Width() - size.cx) ;
		size.cy = r.top + (r.Height() - size.cy) / 2;
		pDC->ExtTextOut(size.cx, size.cy,ETO_OPAQUE   ,NULL, TempText,NULL);
		pDC->SelectObject(OldFont);
	}
	CATCH_ALL(E) 
	{
		printf("\n caught exception");
	}
	END_CATCH_ALL
}

/******************************************************************/
/* this function sets the type  of the the called object          */
/*****************************************************************/
void CVgaMenuItem::SetType(int type)
{
	objectType = type;
}

/******************************************************************/
/* this function returns the type of the the called object       */
/*****************************************************************/
int CVgaMenuItem::GetType() const
{
	return objectType;
}

void CVgaMenuItem::SetRect(const CRect &r)
{
	rect=r;
}

/********************************************************************************/
/* this function returns the rectangle dimentions of the the called object      */
/********************************************************************************/
const CRect & CVgaMenuItem::GetRect() const
{
	return rect;
}

/************************************************************************************/
/* this function draws the button in pressed or released state.						*/
/* if the button is in the released state it draws in pressed state and vice-versa  */
/************************************************************************************/
void CVgaMenuItem::Draw_Pressed_Released_Button(CDC *pDC)
{
	
	if (pressed1)
		pDC->SelectObject(&penBlack1);
	else
	{
		if(CChildView::Back_Color == White)
			pDC->SelectObject(&penDark_Gray1);  // Dark_Gray Color on White BackGround
		else
			pDC->SelectObject(&penWhite1);
	}
	pDC->MoveTo(rect.left , rect.top);
	pDC->LineTo(rect.right , rect.top );
	pDC->MoveTo(rect.left + 1 , rect.top + 1 );
	pDC->LineTo(rect.right , rect.top + 1 );
	pDC->MoveTo(rect.left , rect.top );
	pDC->LineTo(rect.left, rect.bottom );
	pDC->MoveTo(rect.left + 1 , rect.top + 1 );
	pDC->LineTo(rect.left + 1 , rect.bottom );
	CPen * oldPen;
	if (pressed1)
	{
		if(CChildView::Back_Color == White)
			oldPen = pDC->SelectObject(&penDark_Gray1);  // Dark_Gray Color on White BackGround
		else
			oldPen = pDC->SelectObject(&penWhite1);
	}
	else
		oldPen = pDC->SelectObject(&penBlack1);
	pDC->MoveTo(rect.right - 1 , rect.top );
	pDC->LineTo(rect.right - 1 , rect.bottom );
	pDC->MoveTo(rect.right - 2 , rect.top + 1 );
	pDC->LineTo(rect.right - 2 , rect.bottom );
	pDC->MoveTo(rect.left , rect.bottom - 1 );
	pDC->LineTo(rect.right , rect.bottom - 1 );
	pDC->MoveTo(rect.left + 1 , rect.bottom - 2 );
	pDC->LineTo(rect.right , rect.bottom - 2 );
	pDC->SelectObject(oldPen);
}


void CVgaMenuItem::SetPageNum(int PageNum)
{
	ObjectPageNum=PageNum;
}
int CVgaMenuItem::GtPageNum()
{
	return ObjectPageNum;
}

/******************************************************************************************/
/* this function returns the button state(pressed/released) of the the called object      */
/******************************************************************************************/
bool CVgaMenuItem::GetButtonState1()
{
	return pressed1;
}

void CVgaMenuItem::SetButtonState1(bool pressedState)
{
	pressed1 = pressedState;
}

void CVgaMenuItem::DrawItem(CDC *pDC)
{
	Draw(pDC);
}

CString CVgaMenuItem ::LinearSearch(CString Identifier)
{
	int location = -1;
	int i = 0;
	int ID=_ttoi(Identifier);
	if(CTextFileIO::sstID[SECSTRINDEX]=="")
	{
		AfxMessageBox(_T("Required Strings are not Found in ")+ CString(CChildView::thisPtr->CurrentLanguageName));
		theApp.Clean ();
		exit(1);

	}
	if((CTextFileIO::sstID.GetSize()==0)||(CTextFileIO::sststring.GetSize()==0))
	{
		AfxMessageBox(_T("No Strings are available in .Lan File"));
		theApp.Clean();
		exit(1);
	}
	for(i=0;i<theApp.TotalLangElement;i++)
	{
		if(_ttoi(CTextFileIO::sstID[i]) == ID)
		{
			if(CTextFileIO::sststring[i]=="")
				return Identifier;
			else
				return(CTextFileIO::sststring[i]);
		}

	}
	if(i==theApp.TotalLangElement)
		return Identifier;

	return Identifier;
}

/******************************************************************/
/* this function sets the state  of the radio object as passed    */
/******************************************************************/
void CVgaMenuItem::SetSelectedState(bool state)
{
	if(GetType()==CVgaMenu::RADIO_BUTTON)
	{
		CVgaRadioButton *ptr=(CVgaRadioButton*)this;
		ptr->SetSelected(state);
	}
}
/******************************************************************/
/* this function returns the radio value of the radio object      */
/*****************************************************************/
int CVgaMenuItem::GetRadio_Value()
{
	if(GetType()==CVgaMenu::RADIO_BUTTON)
	{
		CVgaRadioButton *ptr=(CVgaRadioButton*)this;
		return ptr->GetRadioValue();
	}
	return -1;
}
/******************************************************************/
/* this function returns the selected state  of the radio object */
/*****************************************************************/
bool CVgaMenuItem::GetSelectedRadio()
{
	if(GetType()==CVgaMenu::RADIO_BUTTON)
	{
		CVgaRadioButton *ptr=(CVgaRadioButton*)this;
		return ptr->GetSelected();
	}
	return false;
}

/**********************************************************************/
/* this function returns the multiple choice flag of the radio object */
/**********************************************************************/
int CVgaMenuItem::GetMultiChoiceFlag()
{
	if(GetType()==CVgaMenu::RADIO_BUTTON)
	{
		CVgaRadioButton *ptr=(CVgaRadioButton*)this;
		return ptr->GetMultiChoiceFlag();
	}
	return -1;
}

/*******************************************************************/
/* this function returns the text of the the called object        */
/******************************************************************/
CString CVgaMenuItem::GetText()
{
	return text;
}

void CVgaMenuItem::SetText(CString String)
{
	text = String;
}

/******************************************************************************/
/* This function draws text according to the passed parameters				  */
/* arg1: pointer to device context											  */
/* arg2: text color															  */
/* arg3: rectangle dimentions												  */
/* arg4: string to be drawn													  */
/* arg5: whether to be centered or not										  */	
/* arg6: Language Index														  */
/******************************************************************************/
void CVgaMenuItem::DrawPrinterText(CDC *pDC, int FontSize, int color,
	const CRect &rect, const CString &text,bool Center_Text, int Lang_Index)
{	
	CRect r(rect);
	r.OffsetRect(XOFFSET, YOFFSET);
	int nHorz;
	int nVert;
	CFont CurrentFontSize;

	if(pDC->GetDeviceCaps(TECHNOLOGY)==DT_RASPRINTER)
	{
		nHorz = pDC->GetDeviceCaps(LOGPIXELSX);
		nVert = pDC->GetDeviceCaps(LOGPIXELSY);
		r =Calib(rect,nHorz,nVert);
	}

	nHorz = pDC->GetDeviceCaps(LOGPIXELSX);

	int SmallFontsize,BigFontsize,WeldDataFontsize,SmallWeldDataFontsize;
	if(!Japaneseflag)
	{
		SmallFontsize=EUROPEANSMALLFONT;
		BigFontsize=EUROPEANBIGFONT;
		WeldDataFontsize=EUROPEANWELDDATAFONT;
		SmallWeldDataFontsize=EUROPEANWELDDATASMALLFONT;
	}
	else
	{
		SmallFontsize=JAPANESESMALLFONT;
		BigFontsize=JAPANESEBIGFONT;
		WeldDataFontsize=JAPANESEWELDDATAFONT;
		SmallWeldDataFontsize=EUROPEANWELDDATASMALLFONT;
	}  

	switch(FontSize)
	{
	case PrintSmallFont:
		{
			int FontPrinterSmall= (SmallFontsize*nHorz)/PIXPERINCH;
			CurrentFontSize.CreateFont(FontPrinterSmall , 0, 0, 0, FW_NORMAL,
				FALSE, FALSE, FALSE, CTextFileIO::CurrentFontChar_Set/*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		}
		break;

	case PrintBigFont:
		{
			int FontPrinterBig = (BigFontsize*nHorz)/PIXPERINCH;
			CurrentFontSize.CreateFont(FontPrinterBig , 0, 0, 0, FW_BOLD ,
				FALSE, FALSE, FALSE, CTextFileIO::CurrentFontChar_Set/*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		}
		break;


	case PrintWeldDataFont:
		{
			int FontPrinterWeldData = (WeldDataFontsize*nHorz)/PIXPERINCH;
			CurrentFontSize.CreateFont(FontPrinterWeldData , 0, 0, 0, FW_NORMAL ,
				FALSE, FALSE, FALSE, CTextFileIO::CurrentFontChar_Set/*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		}
		break;
	case PrintWeldDataSmallFont:
		{
			int FontPrinterSmallWeldData = (SmallWeldDataFontsize*nHorz)/PIXPERINCH;
			CurrentFontSize.CreateFont(FontPrinterSmallWeldData , 0, 0, 0, FW_NORMAL ,
				FALSE, FALSE, FALSE, CTextFileIO::CurrentFontChar_Set/*ANSI_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, FF_DONTCARE, _T("Courier New"));
		}
		break;
	}
	CFont *OldFont = pDC->SelectObject(&CurrentFontSize);
	pDC->SetTextColor(CChildView::Color_Array[color]);
	pDC->SetBkMode(TRANSPARENT);
	CSize size = pDC->GetTextExtent(text);

	CString TempText=text;
	if(CChildView::thisPtr->StringDebugFlag)
	{
		int TempLength=TempText.GetLength();
		TCHAR ch=' ';
		while((size.cx >= r.Width()) && (TempLength>0))
		{
			TempText.SetAt(TempLength-1,ch);
			TempText.TrimRight();
			size=pDC->GetTextExtent(TempText);
			TempLength=TempText.GetLength();

		}
	}

	if(Center_Text==true)
		size.cx = r.left + (r.Width() - size.cx) / 2;
	else
		size.cx = r.left;// + (r.Width() - size.cx) ;
	size.cy = r.top + (r.Height() - size.cy) / 2;
	pDC->ExtTextOut(size.cx, size.cy,ETO_OPAQUE   ,NULL, text,NULL);
	pDC->SelectObject(OldFont);

	CurrentFontSize.DeleteObject();
}

void CVgaMenuItem::GetCharString(unsigned char *&data, int &length, TCHAR *Str)
{

	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
		}u;

		u.ch[1]=NULL;
		u.ch[0]= *data++;
		*(Str+i)= (u.character);
	}
	length -= count+1;

	union {
		unsigned char ch[2];
		TCHAR character;
	}u;
	u.ch[1]=NULL;
	u.ch[0]=NULL;
	*(Str+strlen)=(u.character);

}

int CVgaMenuItem::Convert_Char_To_Integer(unsigned char *&data, int &length, int Bytes)
{
	union {
		int i;
		char c[INTEGERLENGTH];
	} u;
	if(Bytes!=0)
		for (int k = 0; k < Bytes; k++)
		{
			u.c[k] = 0;
		}
		for (int j = Bytes; j < INTEGERLENGTH; j++)
		{
			u.c[j] =*data++;
			length--;
		}
		return (ntohl(u.i ));
}

CString CVgaMenuItem::GetString(unsigned char *&data, int &length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
		}u;

		u.ch[1]=NULL;
		u.ch[0]= *data++;
		result += (u.character);
	}
	length -= (count+1);
	result.TrimRight();
	result.TrimLeft();
	return RemoveNull(result);

}

CString CVgaMenuItem::GetPSString(unsigned char *&data, int &length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
		}u;

		u.ch[1]=NULL;
		u.ch[0]= *data++;
		result += (u.character);
	}
	length -= (count+1);
	result.TrimRight();
	return result;
}

CString CVgaMenuItem::RemoveNull(CString str)
{
	int found =0;
	while(found!=(-1))
	{	
		CString str2="  ";
		found = str.Find(str2);
		if(found != -1)
			str.Delete(found,2);
	}
	return str;
}

