/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaScreenSetup.h_v   1.3   28 Mar 2014 14:33:22   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaScreenSetup.h_v  $
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

#if !defined(AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_)
#define AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VgaMenuItem.h"
#include "ChildView.h"

#define ScrnCalibButtonLabel1_rect CRect(40,384,50,394)
#define ScrnCalibButtonLabel2_rect CRect(586,87,596,97)
#define ScrnCalibButton2_rect CRect(564,16,624,76)
#define ScrnCalibDot2_rect CRect(586,40,596,50)
#define ScrnCalibButton2_BoundingRect CRect(563,15,625,77)
#define ScrnCalibButton1_rect CRect(16,404,76,464)
#define ScrnCalibDot1_rect CRect(40,428,50,438)
#define ScrnCalibButton1_BoundingRect CRect(15,403,77,465)
#define StrTouchButton2_rect CRect(0,200,640,240)/* x made to 200 instead of 160*/
#define StrTouchButton1_rect CRect(0,200,640,240)/* x made to 200 instead of 160*/
#define StrScrnAlign_rect CRect(0,160,640,200)
#define DoneButton_Rect CRect(235,200,405,240)
#define Color_Setup_Rect CRect(235,274,405,314)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)

class CXmlElement;

class CVgaScreenSetup : public CVgaMenuItem  
{
public:
   static float DY1;
	static float DX1;
	virtual void Draw(CDC *pDC);
   static void SetScreenMemberVariable(CXmlElement * e);
	CVgaScreenSetup();
	virtual ~CVgaScreenSetup();
	static CString Str_ScreenSetup,Str_TouchButton1,Str_TouchButton2,Str_ScrnAlign,Str_Done,Str_Exit;
   static CString Str_ScreenSetupID,Str_TouchButton1ID,Str_TouchButton2ID,
      Str_ScrnAlignID,Str_DoneID,Str_ExitID;
	static struct CalibCordinate{
		int Xa;
		int Ya;
		int Xb;
		int Yb;
	};
protected:
	virtual bool MouseClick(const CPoint &p, CChildView *view);
private:
	int lang_index;
	
	static bool button_1_pressed1;
	static bool button_2_released1;
	static bool Exit_pressed1;
	static bool Done_pressed1;
};

#endif // !defined(AFX_VGASCREENSETUP_H__D51B287E_140B_4F98_85E4_1219CDDBAEF1__INCLUDED_)
