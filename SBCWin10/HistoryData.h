/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryData.h_v   1.11   11 Dec 2014 06:49:02   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryData.h_v  $
 * 
 *    Rev 1.11   11 Dec 2014 06:49:02   RJamloki
 * Code Formatting.
 * 
 *    Rev 1.10   10 Nov 2014 02:50:10   rjamloki
 * MAXPARAMVALDISPLEN macro added.MAXPARAMVALUELENGTH macro changed.
 * 
 *    Rev 1.9   01 Oct 2014 10:49:50   AnPawar
 * File inclusion removed.
 * 
 *    Rev 1.8   09 Jul 2014 06:57:40   akaushal
 * AlarmString added in CHistoryData class.
 * 
 *    Rev 1.7   09 Jun 2014 11:45:04   rjamloki
 * Macro changed.
 * 
 *    Rev 1.6   27 May 2014 18:17:04   akaushal
 * Removed the unused virtual function
 * 
 *    Rev 1.4   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:18 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:56 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:22 amaurya     
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:48 amaurya     
 * Initial Revision.
*/


#if !defined(AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_)
#define AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "WeldingData.h"
//#include "WeldHistory.h"

#define HISTORY_TBL_START_X  20
#define HISTORY_TBL_START_Y  30

#define MAXDATETIMELENGTH	 10
#define MAXMODEPRESETLENGTH  50
//#define MAXPARAMUNITLENGTH	 6
#define MAXPARAMVALUELENGTH	 19
#define MAXPARAMVALDISPLEN	 12

class CHistoryData  //: public CVfdObject 
{
public:
//	TCHAR ParameterUnit[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
	TCHAR USBTimeStr[MAXDATETIMELENGTH];
	TCHAR USBDateStr[MAXDATETIMELENGTH];
	short USBParamIDs[MAXPARAMVALUES];
	TCHAR USBAllParamValues[MAXPARAMVALUES][MAXPARAMVALUELENGTH];
	TCHAR USBMode_PresetString[MAXMODEPRESETLENGTH];
	short Lang_Index;
	short TextColour;
	int UniqueId;
	short TotalColoumn;
	bool Units;
    int AlarmString[8];

	void InitilizeAllValues();
	CHistoryData();
	void CopyToUSB(CString Str1, TCHAR* Str2);
	CHistoryData(int Difference,unsigned char * &data, int & length);
	CHistoryData(unsigned char * &data, int & length);
	~CHistoryData();
	void StoreDate_Time(unsigned char *&data, int &length);
	void DrawUSBHistory(CDC *pDC,int LeftMostParameter, int LineNo);
	CString GetMode_PresetString(unsigned char * &data,int & length);
	CString GetWeldDataString(unsigned char * &data,int & length);
	 bool MouseClick(const CPoint &p, CChildView *view);
	 void Draw(CDC *pDC);

};
extern UINT32 HisParameterMap[32];
extern UINT32 HisParameterCounts;
#endif // !defined(AFX_HISTORYDATA_H__CF9F213E_F74B_4805_9859_31558156CA24__INCLUDED_)

