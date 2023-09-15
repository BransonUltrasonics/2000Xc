/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MainFrame.h_v   1.6   16 Apr 2015 05:58:00   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MainFrame.h_v  $
 * 
 *    Rev 1.6   16 Apr 2015 05:58:00   sesharma
 * OnDevicechange() function added to auto hide the cursor if mouse is not plugged in.
 * 
 *    Rev 1.5   30 Jan 2015 08:15:08   amaurya
 * Fix for USB Autoplay. 
 * 
 *    Rev 1.4   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:22 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:00 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:26 amaurya
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:50 amaurya
 * Initial Revision.
*/

#if !defined(AFX_MAINFRAME_H__C68B5D6D_127D_4965_9B94_B4C7D30163B9__INCLUDED_)
#define AFX_MAINFRAME_H__C68B5D6D_127D_4965_9B94_B4C7D30163B9__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ChildView.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members

#ifndef _WIN32
	CCeCommandBar m_wndCommandBar;
#endif
	CStatusBar m_wndStatusBar;
	CChildView m_wndView;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CMainFrame)
	afx_msg LRESULT OnDevicechange(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__C68B5D6D_127D_4965_9B94_B4C7D30163B9__INCLUDED_)
