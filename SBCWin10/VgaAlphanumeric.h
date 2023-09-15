/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaAlphanumeric.h_v   1.7   11 Sep 2014 09:51:32   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaAlphanumeric.h_v  $
 * 
 *    Rev 1.7   11 Sep 2014 09:51:32   rjamloki
 * CurrentTextOnly flag added for Event Reason keypad
 * 
 *    Rev 1.6   02 Sep 2014 03:34:10   rjamloki
 *  Added CString CharNotAllowed to read the characters not allowed from main.gui
 * 
 *    Rev 1.5   18 Aug 2014 08:03:22   rjamloki
 * defined NO_COLOR
 * 
 *    Rev 1.4   28 Jul 2014 14:30:18   rjamloki
 * changes for clamp on alarm user verification menu
 * 
 *    Rev 1.3   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:40 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:24 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:10 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_)
#define AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;
#define NO_COLOR -1
class CVgaAlphanumeric : public CVgaMenuItem  
{
public:
   CVgaAlphanumeric(CXmlElement * e);
   virtual ~CVgaAlphanumeric();
   CString Alpha_Text;
   int CharAllowed;
   int CharHidden;
   CString TitleKeyPad;
   CString MenuNak;
   CString MenuAck;
   int ShowValue;
   CString CurrentString;
   CString NewString;
   CString CurrentAlphaValue;
   CString FunName;
   CString CharNotAllowed;
   bool UseOtherColor;
   bool CurrentTextOnly;
   int FillColor;
   int X1,Y1,X2,Y2;
   CRect Rect;
   void ClearAlphaString(void);
   CString GetAlphaString(void);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC *pDC);
};

#endif // !defined(AFX_VGAALPHANUMERIC_H__E59CF875_A20C_4BCB_9F33_8E35978DD160__INCLUDED_)
