/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ListBox.h_v   1.2   28 Mar 2014 14:33:04   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ListBox.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1    03 Jan 2014 09:04:58 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0    03 Apr 2013 10:09:48 amaurya
 * Initial Revision.
*/
#if !defined(AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_)
#define AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_PRESETS_DISPLAYED 11
#define ListBox_OneLineHeight	31

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CListBoxObject : public CVgaMenuItem  
{
public:
	CListBoxObject(CXmlElement * e);
	virtual ~CListBoxObject();
	int CurrentRunningSequencePreset;
	static bool SequencingScreen;
	int TotalText;
   int MaxPreset;
	//CString * ListBoxText;
   CStringArray ListBoxText;
   CStringArray PresetInfoText;
	static CString CurrentPresetName;
	static CString CurrentSequencePresetName;
   int Type;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;

private:
	

	int ID;
	int ListBox_Color;
	int X1_CoOrdinate;
	int X2_CoOrdinate;
	int Y1_CoOrdinate;
	int Y2_CoOrdinate;
};

#endif // !defined(AFX_LISTBOX_H__DB6EB6F6_40CC_42AF_ABD7_DC91A6E635E0__INCLUDED_)
