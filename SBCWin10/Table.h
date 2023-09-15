/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Table.h_v   1.2   28 Mar 2014 14:33:10   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Table.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:10   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:26 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_)
#define AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CTable : public CVgaMenuItem  
{
public:
	CTable(CXmlElement * e);
	virtual ~CTable();
   static int HighLightString;
	void Print(CDC *pDC, CPoint point);
	void CopyVGATableData(CTable *object);
	void GetHornScanData_for_CompareData(CDC *pDC,bool IsPrint);
	CString RowHeading[9];
	CString ColoumnHeading[3];
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
	//int ParamID;
	CTable();
	CString CompareData[9][3];
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_TABLE_H__EE6A255E_CF6A_4C6B_A31F_61BFB65E5BA9__INCLUDED_)
