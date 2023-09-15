/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/LocalChoice.h_v   1.2   28 Mar 2014 14:33:04   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/LocalChoice.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:58 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:50 amaurya
 * Initial Revision.
*/

#if !defined(AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_)
#define AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;


class CLocalChoice : public CVgaMenuItem  
{
public:
	CLocalChoice(CXmlElement * e);
	virtual ~CLocalChoice();
   CString ChoiceText1;
	CString ChoiceText2;
	CString ChoiceText;
   CString FunName;
   int TextColor;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
private:
   CRect Rect;
};

#endif // !defined(AFX_LOCALCHOICE_H__88D3C4DF_8339_4C8B_808E_DD6C456A8328__INCLUDED_)
