/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/PrintText.h_v   1.4   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/PrintText.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:33:06   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:24 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:04 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:28 amaurya    
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_)
#define AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MaxAlarmString	256

#include "ChildView.h"
#define PRINTSPACEPAGE  35
#define PRINTSPACEPAGE2  32
#define TEXT_ONECOLOUMNWIDTH	400

class CPrintText  
{
public:
   CString textID;
   static CString Manual[9][5];
	static	CString GraphPrText[5][9];
	static	CString AlarmEng[MaxAlarmString];
	static CString AlarmGer[MaxAlarmString];
	static CString AlarmSpn[MaxAlarmString];
	static CString AlarmItl[MaxAlarmString];
	static CString AlarmFr[MaxAlarmString];
	static CString AlarmChS[MaxAlarmString];
	static CString AlarmChT[MaxAlarmString];
	static CString AlarmJpn[MaxAlarmString];
	static CString AlarmKor[MaxAlarmString];
	int PageNo;
	void Draw(CDC *pDC);
	CPoint CoOrdinate;
	int TextFont;
	CPrintText(unsigned char * &data, int &length,bool ViewPreset);
   CPrintText(unsigned char * &data, int &length,bool ViewPreset,int ID);
	CPrintText();
	virtual ~CPrintText();
	CString Text;
	int Lang_Index;
   CString VGAFormatString(CString str1,CString str2);
   CString VGAFormatString2(CString str1,CString str2);
private:
	

	CString GetString(unsigned char *&data, int &length);
	int Convert_Char_To_Integer(unsigned char *&data, int &length);
	CString RemoveNull(CString str);
};

#endif // !defined(AFX_PRINTTEXT_H__FD6DC23C_E60C_410D_9D30_23A5FF668499__INCLUDED_)
