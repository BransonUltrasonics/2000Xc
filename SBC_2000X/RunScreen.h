/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RunScreen.h_v   1.6   14 Mar 2015 07:02:18   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RunScreen.h_v  $
 * 
 *    Rev 1.6   14 Mar 2015 07:02:18   amaurya
 * Header file removed in order to fix the coverty issue 12550.
 * 
 *    Rev 1.5   09 Jun 2014 11:51:00   rjamloki
 *  Macro changed.
 * 
 *    Rev 1.4   27 May 2014 18:07:40   akaushal
 * Added a macro for Weld History Spacing
 * 
 *    Rev 1.3   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:26 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:05:04 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_)
#define AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define RUN_RESULT_TBL_START_X  8
#define RUN_RESULT_TBL_START_Y  50//100
#define LINE_GAP  30
#define ParamRect_Width	120
#define ParamRect_WidthHistory	160
#define MAXCYCLEPERSCREEN	7

#include "VgaMenuItem.h"
//coverity fix 12550
#include "WeldingData.h"

class CXmlElement;
class CRunScreen : public CVgaMenuItem  
{
public:
	CRunScreen(CXmlElement * e);
	virtual ~CRunScreen();
	int ReceivedUniversalCount;
	void UpdateWeldData(unsigned char *&data,int &length,bool Constructor);
	static int Displayable_columns;
//	static int TotalColumn;
	static int *ID_Array;
	static int  *Parameter_ID;
	CTypedPtrList<CPtrList, CWeldingData *> WeldDataList;
	int TotalCycles;
	int RunID;
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

//private:
   
};

#endif // !defined(AFX_RUNSCREEN_H__1A7E24D2_65AD_4696_BB64_326F3E11062C__INCLUDED_)
