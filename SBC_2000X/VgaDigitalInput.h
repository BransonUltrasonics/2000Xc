/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/VgaDigitalInput.h_v   1.1   28 Mar 2014 14:33:20   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/VgaDigitalInput.h_v  $
 * 
 *    Rev 1.1   28 Mar 2014 14:33:20   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.0   26 Feb 2014 02:18:18 jerryw.wang      
 * Initial Revision.
*/

#if !defined(AFX_VGADIGITALINPUT_H__21D51DC4_FAEB_4A52_8FC8_8CF1DD43D337__INCLUDED_)
#define AFX_VGADIGITALINPUT_H__21D51DC4_FAEB_4A52_8FC8_8CF1DD43D337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaDigitalInput : public CVgaMenuItem
{
public:
   CVgaDigitalInput(CXmlElement * e);
   virtual ~CVgaDigitalInput();
public:

   bool GetSelected();
   int GetRadioValue();
   void SetSelected(bool radio_state);

   bool Activated;
   int value;
   CString FunName;
   CString MenuName;
   CString MenuNak;
   CString argument;
   CString FormatString(CString text);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
private:
   int X1;
   int X2;
   int Y1;
   int Y2;
private:
   void SetVariable_Value_radio_button(const CPoint &p,CChildView *view);
};

#endif // !defined(AFX_VGADIGITALINPUT_H__21D51DC4_FAEB_4A52_8FC8_8CF1DD43D337__INCLUDED_)
