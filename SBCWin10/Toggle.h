/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Toggle.h_v   1.6   29 Aug 2016 15:01:40   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Toggle.h_v  $
 * 
 *    Rev 1.6   29 Aug 2016 15:01:40   RJamloki
 * define prototype function void PressureStepDownClick(int Value) for pressure step button
 * 
 *    Rev 1.5   28 Nov 2014 08:32:10   rjamloki
 * New CString Menuname and NoCommandFun added to support confirmation screen on toggle buttons.
 * 
 *    Rev 1.4   05 Sep 2014 07:01:58   amaurya
 * Added a declaration of function.
 * 
 *    Rev 1.3   18 Aug 2014 07:57:08   rjamloki
 * Added DownSpeedTune click handler declaration.
 * 
 *    Rev 1.2   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:28 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_)
#define AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
class CXmlElement;

class CToggle : public CVgaMenuItem  
{
public:
	CToggle(CXmlElement * e);
	virtual ~CToggle();
   static bool SequencingON;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
public:
   bool Toggle_Value;
   CString Toggle_Text1;
   CString Toggle_Text2;
   CString Toggle_Text;
   CString FunName;
   CString NoCommandFun;
   CString MenuName;
};

void DownspeedTuneClick(int Value);
void AutomationClick(int Value);
void DrawPresetValidMsg(CToggle *ptr);
void PressureStepDownClick(int Value);
#endif // !defined(AFX_TOGGLE_H__45C0132D_8514_4DD3_AE55_BDC23E01D7AC__INCLUDED_)
