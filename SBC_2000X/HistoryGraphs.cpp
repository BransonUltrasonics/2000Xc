/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryGraphs.cpp_v   1.5   09 Jun 2014 11:47:26   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryGraphs.cpp_v  $
 * 
 *    Rev 1.5   09 Jun 2014 11:47:26   rjamloki
 * Variable initialization in constructor.
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
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:48 amaurya     
 * Initial Revision.
*/


#include "stdafx.h"
#include "SBC.h"
#include "HistoryGraphs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistoryGraphs::CHistoryGraphs()
{
	Graph1ID=0;
	Graph2ID=0;
	LastGraphDisplayed=0;
	lang_index = 0;
}

CString CHistoryGraphs::HistoryDataPath;
CHistoryGraphs::~CHistoryGraphs()
{
	while(HistoryGraphList.GetCount())
		free(HistoryGraphList.RemoveHead());
}

void CHistoryGraphs::Draw(CDC *pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(CChildView::thisPtr->Color_Array[White]);
	CBrush * oldBrush;
	oldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(CRect(0 + XOFFSET, 40 + XOFFSET, 640 + XOFFSET, 480 + YOFFSET));
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	DisplayGraphs(pDC);
}


/**********************************************************************************************/
/* this function handles the mouse click if it is on the Weld-History screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */	
/**********************************************************************************************/	
bool CHistoryGraphs::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

void CHistoryGraphs::DisplayGraphs(CDC *pDC)
{
	CVgaDrawGraph::GraphBoundary=false;
	POSITION pos = HistoryGraphList.GetHeadPosition();
	while(pos)
	{	
		CVgaDrawGraph *Object = HistoryGraphList.GetNext(pos);
		if(Object->GraphData.graph_type==Graph1ID)
		{
			Object->HSCompareGraph=false;
			Object->GraphData.GraphNum=1;
			Object->DrawGraphBoundary(pDC);//Draw Graph boundary only once in case of dual graph.
			Object->drawgraph(pDC);
			Object->DrawTickMarks(pDC);
			Object->DrawHLabel(pDC);
			Object->DrawVLabel(pDC);
			CVgaDrawGraph::GraphBoundary=true;
		}
		if(Object->GraphData.graph_type==Graph2ID)
		{
			Object->HSCompareGraph=false;
			Object->GraphData.GraphNum=2;
			Object->drawgraph(pDC);
			Object->YAxis2Graduation(pDC);
			Object->DrawVLabel(pDC);
		}
	}
	CVgaDrawGraph::GraphBoundary=false;
}