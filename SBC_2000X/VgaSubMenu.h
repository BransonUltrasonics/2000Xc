/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaSubMenu.h_v   1.2   28 Mar 2014 14:33:22   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaSubMenu.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:28 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:14 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_)
#define AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaSubMenu : public CVgaMenuItem  
{
public:
	CVgaSubMenu(CXmlElement * e);
	virtual ~CVgaSubMenu();
   CString submenu;
   CString menuNak;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGASUBMENU_H__F86048ED_FAF7_4939_B005_7E357A4AFA54__INCLUDED_)
