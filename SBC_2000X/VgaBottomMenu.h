/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaBottomMenu.h_v   1.2   28 Mar 2014 14:33:18   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaBottomMenu.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:18   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:24 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.     03 Apr 2013 10:10:10 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_)
#define AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WeldResult_rect CRect(8+XOFFSET,444+YOFFSET,156+XOFFSET,476+YOFFSET)
#define Weldsetup_rect CRect(326+XOFFSET,444+YOFFSET,472+XOFFSET,476+YOFFSET)
#define Graphs_rect CRect(484+XOFFSET,444+YOFFSET,630+XOFFSET,476+YOFFSET)
#define Bottom_MainMenu_rect CRect(168+XOFFSET,444+YOFFSET,314+XOFFSET,476+YOFFSET)
#define Bottom_Menu_Rect CRect(1+XOFFSET,440+YOFFSET,639+XOFFSET,480+YOFFSET)
#include "ChildView.h"
#include "VgaMenuItem.h"
class CXmlElement;

class CVgaBottomMenu : public CVgaMenuItem  
{
public:
   CVgaBottomMenu(int DrawRectonly);
   CVgaBottomMenu();
   virtual ~CVgaBottomMenu();
   static bool pressedbutton;
   static bool SendCommandForBottomMenu(int ID,int Address);
   static void InitializeBottomMenuMembers(CXmlElement * element);
   static CString mainMenuID;
   static CString GraphsMenu_ID;
   static CString WeldSetup_ID;
   static CString WeldResults_ID;
  // CString submenu;
   static int mainMenuCommandID;
   static int GraphsMenu_CommandID;
   static int WeldSetup_CommandID;
   static int WeldResults_CommandID;
   static CString MenuErrorID;
   CString BottomSubmenu;
   static CString mainMenuStringID,GraphsMenuStringID,WeldSetupStringID,WeldResultsStringID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
private:

   static bool GraphPressed1;
   static bool MainMenuPressed1;
   static bool WeldSetupPressed1;
   static bool WeldResultPressed1;
};

#endif // !defined(AFX_VGABOTTOMMENU_H__F77EF087_2BF5_43EC_A539_E6D97B828C4B__INCLUDED_)
