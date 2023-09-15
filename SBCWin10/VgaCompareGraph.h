/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaCompareGraph.h_v   1.2   28 Mar 2014 14:33:18   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaCompareGraph.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:18   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:26 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:12 amaurya      
 * Initial Revision.
*/
#if !defined(AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_)
#define AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
#define GRAPH_START_X_CORD	100
#define GRAPH_START_Y_CORD	45
#define GRAPH_END_X_CORD	500
#define GRAPH_END_Y_CORD	389
#define HSGRAPH_HEIGHT	344

class CXmlElement;

class CVgaCompareGraph : public CVgaMenuItem  
{
public:
	CVgaCompareGraph();
	virtual ~CVgaCompareGraph();
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC * pDC) ;
};

#endif // !defined(AFX_VGACOMPAREGRAPH_H__857615F0_61F8_4C23_B7A2_8F2C7A89BE47__INCLUDED_)
