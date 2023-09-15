/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Check.h_v   1.2   28 Mar 2014 14:32:56   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Check.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:46 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:42 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_)
#define AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CCheck : public CVgaMenuItem  
{
public:
   CCheck(CXmlElement * e);
   virtual ~CCheck();
   int IsSelected;
   int X_CoOrdinate;
   int Y_CoOrdinate;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   int Font;
   int TextColor;
   
};

#endif // !defined(AFX_CHECK_H__698727CC_8AE7_4482_8BF8_0CA8A9D38A51__INCLUDED_)
