/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaChoice.h_v   1.2   28 Mar 2014 14:33:18   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaChoice.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:18   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:24 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:10 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_)
#define AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CVgaChoice : public CVgaMenuItem  
{
public:
	CVgaChoice(CXmlElement * e);
	virtual ~CVgaChoice();
	CString ChoiceText1;
	CString ChoiceText2;
	CString ChoiceText;
   int Choice_value;
   CString submenu;
   CString FunName;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_VGACHOICE_H__785627E6_1006_4D1B_8B50_D4BCB05F8845__INCLUDED_)
