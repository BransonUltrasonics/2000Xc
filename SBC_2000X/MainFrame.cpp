/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MainFrame.cpp_v   1.8   16 Apr 2015 05:57:28   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MainFrame.cpp_v  $
 * 
 *    Rev 1.8   16 Apr 2015 05:57:28   sesharma
 * OnDevicechange() function added to auto hide the cursor if mouse is not plugged in.
 * 
 *    Rev 1.7   28 Mar 2015 04:33:06   RJamloki
 * CMainframe::WindowProc() functioning explained
 * 
 *    Rev 1.6   30 Jan 2015 08:15:04   amaurya
 * Fix for USB Autoplay. 
 * 
 *    Rev 1.5   22 Jul 2014 08:25:56   akaushal
 * PreCreateWindow() function changed to remove menu bar and title from VGA.
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
 * Initial  Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:50 amaurya
 * Initial Revision.
*/

#include "stdafx.h"
#include "Application.h"
#include "MainFrame.h"
#include <Dbt.h>
#include "InputDevices.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const DWORD dwAdornmentFlags = 0; // exit button

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const UINT m_uiAutoRun = ::RegisterWindowMessage(_T("QueryCancelAutoPlay"));
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

	BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
		//{{AFX_MSG_MAP(CMainFrame)
		ON_WM_CREATE()
		ON_WM_SETFOCUS()
		//}}AFX_MSG_MAP
		ON_MESSAGE(WM_DEVICECHANGE, &CMainFrame::OnDevicechange)
	END_MESSAGE_MAP()
	/*
	static UINT indicators[] =
	{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS
	};
	*/
	/////////////////////////////////////////////////////////////////////////////
	// CMainFrame construction/destruction

	CMainFrame::CMainFrame()
	{
	}

	CMainFrame::~CMainFrame()
	{
	}

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
		// create a view to occupy the client area of the frame
		if (!m_wndView.Create(NULL, NULL,AFX_WS_DEFAULT_VIEW  ,
			CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
		{
			TRACE0("Failed to create view window\n");
			return -1;
		}
#if 0
		if(!m_wndCommandBar.Create(this) ||
			!m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
			!m_wndCommandBar.AddAdornments(dwAdornmentFlags))
		{
			TRACE0("Failed to create CommandBar\n");
			return -1;      // fail to create
		}

		m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);
#endif
		/*
		if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
		{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
		}
		*/
		return 0;
	}

	BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
	{

		// Create a window without min/max buttons or sizable border 
		cs.style = WS_POPUP ; //WS_OVERLAPPED  | WS_BORDER | 
		cs.cy = 540;//::GetSystemMetrics(SM_CYSCREEN) ; 
		cs.cx =660;// ::GetSystemMetrics(SM_CXSCREEN) ; 
		cs.y = 0;//((cs.cy*2 ) - cs.cy) / 2; 
		cs.x = 0;//((cs.cx*2 ) - cs.cx) / 2;
		if(cs.hMenu!=NULL)
		{
			::DestroyMenu(cs.hMenu);
			cs.hMenu=NULL;
		}
		if (!CFrameWnd::PreCreateWindow(cs))
			return FALSE;
		// TODO: Modify the Window class or styles here by modifying
		//  the CREATESTRUCT cs
		cs.lpszClass = AfxRegisterWndClass(0);
		return TRUE;
	}

	/////////////////////////////////////////////////////////////////////////////
	// CMainFrame diagnostics

#ifdef _DEBUG
	void CMainFrame::AssertValid() const
	{
		CFrameWnd::AssertValid();
	}

	void CMainFrame::Dump(CDumpContext& dc) const
	{
		CFrameWnd::Dump(dc);
	}

#endif //_DEBUG

	/////////////////////////////////////////////////////////////////////////////
	// CMainFrame message handlers
	void CMainFrame::OnSetFocus(CWnd* pOldWnd)
	{
		// forward focus to the view window
		m_wndView.SetFocus();
	}

	BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
	{
		// let the view have first crack at the command
		if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
			return TRUE;
		// otherwise, do default handling
		return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	}


	/******************************************************************************************************/
    /*  Purpose                                                                                           */                               	                                              
    /*	   This function is used To ignore USB auto play message sent by windows whenever USB disk is      */
	/* plugged in. This is registered as an handler for windows QueryCancelAutoPlay event 				  */							                                                      
    /* *Entry condition:                                                                                  */
    /*      Takes UINT message, specifies the windows message to be processed.                            */
    /*      WPARAM  wParam,LPARAM lParam provides additional information used in processing the message   */
    /* Exit condition:                                                                                    */
    /*    return true if message type is USB auto play message and the message in not processed           */
    /*    else process the windows message by calling the function CFrameWnd::WindowProc()                */
    /******************************************************************************************************/
	LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == m_uiAutoRun) { 
			return TRUE;
		}		
		return CFrameWnd::WindowProc(message, wParam, lParam);
	}

	/******************************************************************************************************/
    /*  Purpose                                                                                           */                               	                                              
    /*	   This function is called when a removable device is plugged in or out in SBC. We are using this */
	/* function to detect whether mouse  is plugged in or out.	A 5 second timer is started as soon as    */
	/* windows report a device change event by calling this function. After 5 seconds are expired 2000Xc  */
	/* application checks whether mouse is currently plugged on or not in the system. If yes it enables   */
	/* the mouse cursor. If no it removes the mouse cursor.												  */
    /* Entry condition:                                                                                   */ 
    /*        WPARAM  wParam,LPARAM lParam provides additional information used in processing the message */
    /******************************************************************************************************/
	afx_msg LRESULT CMainFrame::OnDevicechange(WPARAM wParam, LPARAM lParam)
	{

		if(wParam == DBT_DEVNODES_CHANGED)
		{
			MouseTimerInit();
		}

		return 0;
	}
