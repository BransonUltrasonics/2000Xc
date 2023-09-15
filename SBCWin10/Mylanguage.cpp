/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Mylanguage.cpp_v   1.3   28 Mar 2014 14:33:04   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Mylanguage.cpp_v  $
 * 
 *    Rev 1.3   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:24 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:52 amaurya
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "Mylanguage.h"
#include "TextIOFile.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMylanguage::CMylanguage(int X1,int Y1,int X2,int Y2)
{
	X1_CoOrdinate =  X1;
	Y1_CoOrdinate =  Y1;
	X2_CoOrdinate =  X2;
	Y2_CoOrdinate = Y2; 
	ListBox_Color=White;
}

CMylanguage::~CMylanguage()
{

}
bool CMylanguage::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
void CMylanguage::Draw(CDC *pDC)
{

	/*Draw list box rectangle with list box color* /
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,
	X2_CoOrdinate+1,Y2_CoOrdinate+1));
	DrawRect(pDC, ListBox_Color, CRect(X1_CoOrdinate,Y1_CoOrdinate,
	X2_CoOrdinate,Y2_CoOrdinate));
	int Y_CoOrdinate = Y1_CoOrdinate;
	int j=0,count=0;;
	int MaxLanguageDisplay=MAX_LANGUAGE_DISPLAYED;
	if(CChildView::Currentlanguage >=(MaxLanguageDisplay))
	{
	// Update no of Strings Displayed
	count=CChildView::Currentlanguage -(MaxLanguageDisplay);
	count++;
	}

	for(int i=count;i<(CChildView::TotalLanguage);i++)
	{
	//Index can't br greater than Total lang.
	if(i==CChildView::TotalLanguage)
	break;

	// Don't Dispaly more than 11 language
	if(j>=11)
	break;

	int Selectfont=CTextFileIO::SstFont[i];
	int FontSize=CTextFileIO::SstFontSize[i];

	/*Draw green background and "<"	mark on current Preset.* /			
	if((CChildView::Currentlanguage == (i)))
	{
	//Drawing HighLight Background.
	DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
	Y_CoOrdinate,
	X2_CoOrdinate,
	Y_CoOrdinate+31));

	}
	// Draw Font Strings
	CVgaMenuItem::DrawTextFont(pDC, FontSize,Selectfont, CChildView::TextColor, 
	CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
	CTextFileIO::Sstlanguage[i],false);
	Y_CoOrdinate +=ListBox_OneLineHeight;
	j++;
	}*/
}