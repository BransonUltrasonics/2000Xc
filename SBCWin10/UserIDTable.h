/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTable.h_v   1.5   16 Apr 2015 06:02:28   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTable.h_v  $
 * 
 *    Rev 1.5   16 Apr 2015 06:02:28   sesharma
 * extern declaration added for strings removed from UserIDTable.cpp
 * 
 *    Rev 1.4   09 Jun 2014 11:57:10   rjamloki
 * CUserIDTable::DrawUserIDHeading() declaration changed
 * 
 *    Rev 1.3   21 Apr 2014 13:48:48   akaushal
 * Removed unused function declaration from class.
 * 
 *    Rev 1.2   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     26 Mar 2014 14:26:16 rjamloki    
 * declarations for function was added .declaration of thisHisPtr was changed 
 *
 *    Rev 1.0     05 Mar 2014 14:43:18 rjamloki      
 * Initial Revision.
*/

#if !defined(AFX_USERIDTABLE_H__ADA49CFF_0101_4806_AAB7_B44894922E64__INCLUDED_)
#define AFX_USERIDTABLE_H__ADA49CFF_0101_4806_AAB7_B44894922E64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
//#include "RunScreen.h"
#include "UserIDTableData.h"

#define LeftButton_Rect CRect(45,370,95,420)
#define ScreenUpButton_Rect CRect(105,370,155,420)
#define UpButton_Rect CRect(165,370,215,420)
#define DownButton_Rect CRect(225,370,275,420)
#define ScreenDownButton_Rect CRect(285,370,335,420)
#define RightButton_Rect CRect(345,370,395,420)
#define GraphsButton_Rect CRect(X_CORDINATE_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define UpArrowRect CPoint(180,404), CPoint(190, 386),CPoint(201,404)
#define DownArrowRect CPoint(240,386), CPoint(250,404),CPoint(261,386)
#define LeftArrowRect CPoint(80,386), CPoint(60,395),CPoint(80,404)
#define RightArrowRect CPoint(360,386), CPoint(380,395),CPoint(360,404)
#define ScreenUpArrow1Rect CPoint(120,398), CPoint(130, 382),CPoint(141,398)
#define ScreenUpArrow2Rect CPoint(120,408), CPoint(130, 392),CPoint(141,408)
#define ScreenDownArrow1Rect CPoint(300,382), CPoint(310,398 ),CPoint(321,382)
#define ScreenDownArrow2Rect CPoint(300,392), CPoint(310, 408),CPoint(321,392)

#define MaxUserIDPerScreen 8

class CXmlElement;

class CUserIDTable : public CVgaMenuItem  
{
public:
	//CUserIDTable();
	CUserIDTable(CXmlElement * e);
	virtual ~CUserIDTable();

void DrawParameterHeadings(CDC * pDC);
	int *Parameter_ID;
	int TotalColoumn;
	static int TopMostData;
	void DrawUserIDData(CDC *pDC);
	int TotalCycle;
	CUserIDTable(unsigned char * &data, int & length);
	CUserIDTable();
	CTypedPtrList<CPtrList, CUserIDTableData *> UserIDList;

	static int SelectedUserIDData;
	static int LeftMostParameter;
	static CUserIDTable * thisPtr;
	static void CUserIDTable::CreateUserObjectList(void);
    void CUserIDTable::CreatePDF(HPDF_Doc *& pdf,HPDF_Page *& page);
    void CUserIDTable::DrawUserIDHeading(HPDF_Doc *& pdf,HPDF_Page *& page);
   
 protected:
   bool UpButtonPressed;
   bool DownButtonPressed;
   bool LeftButtonPressed;
   bool RightButtonPressed;
   bool ScreenUpButtonPressed;
   bool ScreenDownButtonPresssed;
   bool GraphsButtonPressed;
   bool ExitButtonPressed;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
private:
   int lang_index;

};

extern CList<CString,CString> tempUserIDList;
extern POSITION UserIDTemp_pos;
extern CString MdyFormat;
extern CString DmyFormat;
extern CString PleaseWait;
#endif // !defined(AFX_USERIDTABLE_H__ADA49CFF_0101_4806_AAB7_B44894922E64__INCLUDED_)
