/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Mylanguage.h_v   1.2   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Mylanguage.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:06   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:52 amaurya
 * Initial Revision.
*/
 

#if !defined(AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_)
#define AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
#define ListBox_OneLineHeight	31
#define MAX_LANGUAGE_DISPLAYED 11

class CMylanguage : public CVgaMenuItem  
{
public:
	CMylanguage(int X1,int Y1,int X2,int Y2);
	virtual ~CMylanguage();
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
private:
   int ListBox_Color;
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
};

#endif // !defined(AFX_MYLANGUAGE_H__37D80165_8017_4447_B393_395D928029BB__INCLUDED_)
