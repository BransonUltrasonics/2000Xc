/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MsgScreen.h_v   1.2   28 Mar 2014 14:33:04   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MsgScreen.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:52 amaurya
 * Initial Revision.
*/
#if !defined(AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_)
#define AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CMsgScreen : public CVgaMenuItem  
{
public:
   CMsgScreen(CXmlElement * e);
   virtual ~CMsgScreen();
   CString submenu;
   CString menunak;
   int ResponseType;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
public:
   int FillColor;
   int X1_CoOrdinate;
   int X2_CoOrdinate;
   int Y1_CoOrdinate;
   int Y2_CoOrdinate;
   int Time;
   int TextFont;
   int TextColor;
   CString MsgLine1,MsgLine2,MsgLine3;
   CString MsgLine1ID,MsgLine2ID,MsgLine3ID;
};

#endif // !defined(AFX_MSGSCREEN_H__FC9B3150_8285_4BF1_B7BE_B01ABF8FE1E2__INCLUDED_)
