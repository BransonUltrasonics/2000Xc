/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaVariable.h_v   1.7   08 Apr 2015 13:09:38   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaVariable.h_v  $
 * 
 *    Rev 1.7   08 Apr 2015 13:09:38   AnPawar
 * MaxInputDigits variable added in VgaVariable class to fix the max input digits issue in batch count field.
 * 
 *    Rev 1.6   27 Mar 2015 11:01:40   amaurya
 * DisableDrawText added.This value filled from Main.gui. If it is 1 then we shall not draw any value in vga variable value field.
 * 
 *    Rev 1.5   28 Nov 2014 08:34:16   rjamloki
 * New CString MenuNak added in CVgaVariable class to support nak message
 * 
 *    Rev 1.4   18 Aug 2014 08:17:12   rjamloki
 * Added TextOnButton flag to be decided by gui file.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:14:04 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_)
#define AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"

class CXmlElement;

class CVgaVariable : public CVgaMenuItem  
{
public:
	CVgaVariable(CXmlElement * element);
	virtual ~CVgaVariable();
	CString Variable_Text;
	int IDVariable;
	CString Keypad_title;			
	int		Format;			
	int		Digits;			
	int		Value;				
	int		MinVal;			
	int		MaxVal;			
	int		Disable;			
	int		Bitmask;			
	int		NewVal;
	int		ID;				//	Variable ID
   int TextType;
   int DisableFlag;
   bool Insertunitflag;
   bool TextOnButton;
   int  DisableDrawText;
   int  Unitshow; 
   CString MenuNak;
   CString CurrentString,CurrentStringID;
   CString NewString,NewStringID;
   CString FunName;
   int MaxInputDigits;   
   int X1,Y1,X2,Y2;
   CRect Rect;
protected:
   bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
	
};

#endif // !defined(AFX_VGAVARIABLE_H__482403E8_6776_4BB9_812B_5C17F569B447__INCLUDED_)
