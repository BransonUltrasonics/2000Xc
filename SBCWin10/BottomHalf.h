/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BottomHalf.h_v   1.2   28 Mar 2014 14:32:54   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BottomHalf.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:46 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:42 amaurya     
 * Initial Revision.
*/


#if !defined(AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_)
#define AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

//#define HORNDOWN_ID  401

class CXmlElement;

class CBottomHalf : public CVgaMenuItem  
{
public:
   CBottomHalf(CXmlElement * e);
   virtual ~CBottomHalf();
   static CRect BottomHalfRect;
   CString submenu;
   int Refresh;
   static int BottomHalfId;
   static CVgaMenu *BottomMenuPointer;
   int RefreshTime;
   int Bottomtype;
   static bool HornDownScreenPresent;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   int X1_CoOrdinate;
   int Y1_CoOrdinate;
   int X2_CoOrdinate;
   int Y2_CoOrdinate;
   int FillColor;
};

#endif // !defined(AFX_BOTTOMHALF_H__C8E60D5F_E125_4426_A679_D59D1A861457__INCLUDED_)
