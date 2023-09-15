/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryGraphs.h_v   1.4   28 Mar 2014 14:33:02   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryGraphs.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:18 rjamloki
 * Screens and PDF working
 *   Rev 1.2     03 Jan 2014 09:04:56 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *   Rev 1.1     05 Jun 2013 09:33:22 amaurya     
 * Initial Revision 2.
 *
 *   Rev 1.0     03 Apr 2013 10:09:48 amaurya    
 * Initial Revision.
*/


#if !defined(AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_)
#define AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "VfdObject.h"
#include "ChildView.h"
//#include "DrawGraph.h"
#include "VgaMenuItem.h"


//class CDrawGraph;
class CXmlElement;
class CVgaDrawGraph;
class CHistoryGraphs  : public CVgaMenuItem//CVfdObject  
{
public:
	static CString HistoryDataPath;
	int LastGraphDisplayed;
	int Graph1ID;
	int Graph2ID;
	void DisplayGraphs(CDC *pDC);
	CHistoryGraphs();
	virtual ~CHistoryGraphs();
	
	int lang_index;
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);
	CTypedPtrList<CPtrList, CVgaDrawGraph *> HistoryGraphList;
};

#endif // !defined(AFX_HISTORYGRAPHS_H__0D7907A3_195F_4F40_9343_EA8AC563F972__INCLUDED_)





