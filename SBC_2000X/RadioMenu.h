/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RadioMenu.h_v   1.4   27 May 2014 18:06:44   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RadioMenu.h_v  $
 * 
 *    Rev 1.4   27 May 2014 18:06:44   akaushal
 * updation for History Setup button input 
 * 
 *    Rev 1.3   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:26 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:05:04 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_)
#define AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;
//#define MAXRADIOINDEX  14

class CRadioMenu : public CVgaMenuItem  
{
public:
   CRadioMenu(CXmlElement * e);
   virtual ~CRadioMenu();
   CStringArray RadioMenuStr;
   CStringArray RadioMenuStrID;
   CString VarText;
   CString FormatString(CString text);
   CString StrtextID;
   CString submenu;
   int RadioIndex;
   int multiChoiceFlag;
   UINT32 multiChoiceValue;
   bool Insertunitflag;
   int Format;
   void SetSelectedRadioIndex(CVgaMenu * CurrMenuLst);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

};

#endif // !defined(AFX_RADIOMENU_H__888BA3BF_DB3B_4191_A62E_1A1727F3DD26__INCLUDED_)
