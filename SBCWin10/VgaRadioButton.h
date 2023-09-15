/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaRadioButton.h_v   1.4   27 May 2014 18:13:02   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaRadioButton.h_v  $
 * 
 *    Rev 1.4   27 May 2014 18:13:02   akaushal
 * Added a variable to support Multiple choice from Main.gui
 * 
 *    Rev 1.3   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:14:00 rjamloki  
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:28 rjamloki  
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:14 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_)
#define AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaRadioButton : public CVgaMenuItem  
{
public:
   bool GetSelected();
   int GetRadioValue();
   int GetMultiChoiceFlag();
   void SetSelected(bool radio_state);
   CVgaRadioButton(CXmlElement * e);
   virtual ~CVgaRadioButton();
   bool Selected;
   int ID;
   UINT32 value;
   int Format;
   CString FormatString(CString text);
   int multiChoiceFlag;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

private:
   void SetVariable_Value_radio_button(const CPoint &p,CChildView *view);
   void SetVariable_Value_multi_radio_button(const CPoint &p,CChildView *view);

};

#endif // !defined(AFX_VGARADIOBUTTON_H__21FD686F_EB9D_44C7_9DA7_99E5A5CB02DA__INCLUDED_)
