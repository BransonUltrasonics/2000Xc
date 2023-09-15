/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaTitle.h_v   1.7   03 Feb 2015 07:25:44   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaTitle.h_v  $
 * 
 *    Rev 1.7   03 Feb 2015 07:25:44   amaurya
 * LoginButtonEnable and LogoutButtonEnable variable declaration removed.
 * 
 *    Rev 1.6   09 Jul 2014 07:25:34   akaushal
 * Variables added to CVgaTitle class. 
 * 
 *    Rev 1.5   11 Jun 2014 10:51:28   rjamloki
 * New members added in class.  
 * 
 *    Rev 1.4   27 May 2014 06:46:58   amaurya
 * Added flags for Bottom Menu disable and Alarm Flag disable
 * 
 *    Rev 1.3   28 Mar 2014 14:33:22   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     27 Feb 2014 02:00:08 jerryw.wang    
 * Added the MenuTypes variable for the buttons arrangement on the specific menu. 
 *
 *    Rev 1.1     03 Jan 2014 09:06:28 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     03 Apr 2013 10:10:14 amaurya      
 * Initial Revision.
 *
*/

#if !defined(AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_)
#define AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define Title_Rect CRect(1+XOFFSET, 0+YOFFSET, 639+XOFFSET, 40+YOFFSET)
#define DEFAULT_NO_ROWS    4
#define DEFAULT_NO_COLUMNS    2
#define DEFAULT_BUTTONTYPE    2
#define MAXTITLE  16
#include "ChildView.h"
#include "VgaMenuItem.h"

class CXmlElement;

class CVgaTitle : public CVgaMenuItem  
{
public:
   CVgaTitle(CString Title);
	CVgaTitle(CXmlElement * element);
	virtual ~CVgaTitle();
   CStringArray TitleArray;
   int ButtonTypes;
   int rows;
   int columns;
   int ExitFlag;
   int SaveFlag;
   bool BottomHalfPresent;
   bool BottomMenuDisable;
   bool DrawAlarmButton;
   bool MenuTypes;
   CString FunName;
   CString argument;
protected:
   bool MouseClick(const CPoint &p, CChildView *view);
	friend void MyFunc(CVgaTitle  *);
	virtual void Draw(CDC * pDC) ;
   CString justify;
	bool pageinfo;
};

#endif // !defined(AFX_VGATITLE_H__2D23F0E5_60ED_4343_8C39_A46F67189311__INCLUDED_)
