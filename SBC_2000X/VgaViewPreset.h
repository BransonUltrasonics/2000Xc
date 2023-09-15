/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaViewPreset.h_v   1.2   28 Mar 2014 14:33:24   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaViewPreset.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:30 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_)
#define AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

#define EXIT_RECT CRect(420,380,510,420)
#define NEXT_RECT CRect(530,380,620,420)
#define BACK_RECT CRect(310,380,400,420)
#define TOTALPAGE 6
#define FIRST_XCORD_FORTEXT	60
#define TOTALHEIGHT			300

class CXmlElement;
class CPrintText;

class CVgaViewPreset : public CVgaMenuItem  
{
public:
   CString PresetNameString;
   void ArrangeCoOrdinate();
	CTypedPtrList<CPtrList, CPrintText *> ViewPresetTextList;
   //CVgaViewPreset(CXmlElement * e,CString PresetName);
   CVgaViewPreset(CString PresetName);
   virtual ~CVgaViewPreset();
   int Page_No;
protected:
   int MaxPageDisplay;
	void DrawTextObjectsList(CDC*pDC);
	void DrawNextBackExiButton(CDC*pDC);
	void DrawPageNumber(CDC *pDC);
	CRect ExitRect;
	CRect NextRect;
	CRect BackRect;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
   static bool View_Preset_Exit_pressed;
	static bool View_Preset_Next_pressed;
	static bool View_Preset_Back_pressed;
};

#endif // !defined(AFX_VGAVIEWPRESET_H__5A187165_BE88_45F2_BDC0_719383AA1373__INCLUDED_)
