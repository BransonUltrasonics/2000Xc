/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Text.h_v   1.3   18 Aug 2014 07:55:26   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Text.h_v  $
 * 
 *    Rev 1.3   18 Aug 2014 07:55:26   rjamloki
 * Changed constructor to add text position
 * 
 *    Rev 1.2   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:26 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_)
#define AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CText : public CVgaMenuItem  
{
public:
	CText(CString str,int X1,int Y1,int X2,int Y2);
	CText(CXmlElement * e);
	virtual ~CText();
	CString SubText;
	CString FunName;
	CRect Rect;
	int X1;
	int Y1;
	int X2;
	int Y2;
protected:
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_TEXT_H__32A5A362_F631_4B5F_9AF7_D97B746B9636__INCLUDED_)
