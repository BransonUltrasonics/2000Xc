/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Date.h_v   1.2   28 Mar 2014 14:32:58   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Date.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:50 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya     
 * Initial Revision.
*/


#if !defined(AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_)
#define AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;
class CDate : public CVgaMenuItem  
{
public:
   CDate(CXmlElement * e);
   virtual ~CDate();
   CString Date_Text;
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString Str_Reenter,Str_ReenterID;
   CString StrInvalidEntry,StrInvalidEntryID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_DATE_H__2486C00D_741D_42F2_83F7_C8FDDE3C8348__INCLUDED_)
