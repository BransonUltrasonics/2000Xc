/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Line.cpp_v   1.3   28 Mar 2014 14:33:02   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Line.cpp_v  $
 * 
 *    Rev 1.3   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:20 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:04:58 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     07 Apr 2008 11:00:48 amaurya      
 * Initial Revision.
 */
#include "stdafx.h"
#include "SBC.h"
#include "Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**********************************************************************************/
/*                                                                                */
/*  This function creates a CVGALine object When any CVGALine type object is      */
/*  found in  menu/submenu item list.											  */
/**********************************************************************************/
CLine::CLine(CXmlElement * e)
{
	/*Storing Co-ordinates for Line.*/
	X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));

	LineColor=_ttoi(e->GetAttribute("LineColor"));//Line Color.
	//	length--;
}

CLine::~CLine()
{
}

/*******************************************************************************/
/*                                                                             */
/*  This function Draws a CVGALine object When any CVGALine type object        */
/*  is found in menu/submenu item list for current page .					   */
/*																			   */
/*******************************************************************************/
void CLine::Draw(CDC *pDC)
{
	rect=CRect(X1_CoOrdinate,Y1_CoOrdinate,X2_CoOrdinate,Y2_CoOrdinate);

	/*Drawing Line.*/
	CPen penLine;
	CPen *OldPen;
	penLine.CreatePen(PS_SOLID, 2, CChildView::Color_Array[LineColor]);
	OldPen = pDC->SelectObject(&penLine);
	pDC->MoveTo(X1_CoOrdinate,Y1_CoOrdinate);
	pDC->LineTo(X2_CoOrdinate,Y2_CoOrdinate);
	pDC->SelectObject(OldPen);
	penLine.DeleteObject();
}

bool CLine::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
