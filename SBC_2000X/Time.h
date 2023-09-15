/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Time.h_v   1.2   28 Mar 2014 14:33:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Time.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:28 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_)
#define AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CVgaTime : public CVgaMenuItem  
{
public:
   CVgaTime(CXmlElement * e);
   virtual ~CVgaTime();
   CString Time_Text;
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString Str_Reenter,Str_ReenterID;
   CString StrInvalidEntry,StrInvalidEntryID;
protected:

   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_TIME_H__0B012D1A_F0BA_4F99_9A02_D5608619D8AF__INCLUDED_)
