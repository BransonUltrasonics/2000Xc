/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextBox.h_v   1.2   28 Mar 2014 14:33:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextBox.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:28 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_)
#define AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CTextBox : public CVgaMenuItem  
{
public:	
   CTextBox(CXmlElement * e);
	virtual ~CTextBox();
   int BoxColor;
protected:
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);
private:
	CRect Rect;
	int ID;
	int TextColor;
	int TextFont;

};

#endif // !defined(AFX_TEXTBOX_H__8217EC8F_40BB_4BD7_9B90_29A5EF0C8722__INCLUDED_)
