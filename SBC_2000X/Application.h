/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Application.h_v   1.5   Jun 04 2019 15:41:02   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Application.h_v  $
 * 
 *    Rev 1.5   Jun 04 2019 15:41:02   RJamloki
 * Fix delete file and function assingment
 * 
 *    Rev 1.5   23 Apr 2014 11:18:20   akaushal
 * SendUiSerialHostCommand() function changed for serial communication
 * 
 *    Rev 1.4   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:10 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:44 rjamloki      
 * Header Fix and added command to assign ip.
 * 
 *    Rev 1.1     05 Jun 2013 09:33:16 amaurya     
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/



#if !defined(AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_)
#define AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_

#include "stdafx.h"
#include <iptypes.h>
#include "resource.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Application.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CApplication

class CCommPort;
class CEtherPort;
class CHostCommand;

class CApplication : public CWinApp
{
public:
	void SendWeldData(unsigned char *&data,int length);
	CHostCommand * SendEnHostCommand(CHostCommand *request);

	CHostCommand * SendUiHostCommand(CHostCommand * request);
	CHostCommand * SendPollingHostCommand(CHostCommand * request);
	CHostCommand * SendUiSerialHostCommand(CHostCommand * request);
	virtual void Trace(const CString & str) = 0;
	bool GetBottomMenuAddress(bool *Start_Screen,int *WeldResults_Address,int *mainMenuAddress,int *WeldSetup_Address,int *GraphsMenu_Address,int *Langauage_Index,bool *metric);
	CEtherPort * ether;
	static unsigned long ip_addr;
    static unsigned long mask_addr;
    static unsigned long gateway_addr;
	static int mac_addr_len;
	static BYTE mac_addr[MAX_ADAPTER_ADDRESS_LENGTH];
	static void getAdapterInfo(void);
	static CString getIPAddress(CString);
	static CString getMacAddress(CString);
protected:
	void InitTasks();
	CCommPort * com;
	

	CApplication();
	enum 
	{
		ACK = 0x06,
		NAK = 0x15
	};
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApplication)
	public:
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(CApplication)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CApplication * app;
extern int page_no;
extern bool OnKeypadScreen_flag;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLICATION_H__C3A98B50_A3AB_4F4A_B9AD_E04D1E17BFB0__INCLUDED_)
