/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGAAdd_Back_Next_Button.h_v   1.2   28 Mar 2014 14:33:16   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGAAdd_Back_Next_Button.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:22 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:08 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_)
#define AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"

#define NextButtonRect	CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define BackButtonRect CRect(20,Y_CORDINATE_BACK_NEXT,BUTTON_WIDTH_BACK_NEXT+20,BUTTON_HEIGHT+Y_CORDINATE_BACK_NEXT)

class CVGAAdd_Back_Next_Button : public CVgaMenuItem  
{
public:
	CVGAAdd_Back_Next_Button(int type);
	virtual ~CVGAAdd_Back_Next_Button();

protected:
virtual bool MouseClick(const CPoint &p, CChildView *view);
virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGAADD_BACK_NEXT_BUTTON_H__D9F166AA_46F4_407E_A4EF_E39A913F98ED__INCLUDED_)
