/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Line.h_v   1.2   28 Mar 2014 14:33:04   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Line.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:58 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:48 amaurya      
 * Initial Revision.
 */
 


#if !defined(AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_)
#define AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CLine : public CVgaMenuItem  
{
public:
   CLine(CXmlElement * e);
   virtual ~CLine();

protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);

private:
   int LineColor;
   int X1_CoOrdinate;
   int X2_CoOrdinate;
   int Y1_CoOrdinate;
   int Y2_CoOrdinate;
};

#endif // !defined(AFX_LINE_H__FF8720B7_1798_4E89_8D0B_47B5A2F31B3B__INCLUDED_)
