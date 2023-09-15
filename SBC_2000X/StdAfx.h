/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/StdAfx.h_v   1.12   16 Apr 2015 05:59:48   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/StdAfx.h_v  $
 * 
 *    Rev 1.12   16 Apr 2015 05:59:48   sesharma
 * Removed commented code.
 * 
 *    Rev 1.11   12 Dec 2014 06:05:10   RJamloki
 * ERRMSGBOX macro added for socket error debugging.
 * 
 *    Rev 1.10   28 Nov 2014 08:31:40   rjamloki
 *  #pragma warning( disable : 4996 ) to suppress warnings related to sprintf
 * 
 *    Rev 1.9   01 Oct 2014 10:53:22   AnPawar
 * Path changed
 * 
 *    Rev 1.8   18 Aug 2014 07:50:32   rjamloki
 * Added RUN_ON_SBC macro.
 * 
 *    Rev 1.7   22 Jul 2014 08:25:16   akaushal
 * Changes for VGA file path .
 * 
 *    Rev 1.6   20 May 2014 11:03:22   rjamloki
 * Macro to disable printf.  
 * 
 *    Rev 1.5   28 Mar 2014 14:33:10   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:32 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:05:26 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:36 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:00 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_STDAFX_H__6F1ED807_2E41_4DDC_AC85_4B46243B0C80__INCLUDED_)
#define AFX_STDAFX_H__6F1ED807_2E41_4DDC_AC85_4B46243B0C80__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _WIN32	// let's complain about this only when we are using eVC++
#if (_WIN32_WCE <= 200)
#error : This project does not support MFCCE 2.00 or earlier, because it requires CControlBar, available only in MFCCE 2.01 or later
#endif
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#if defined(_WIN32_WCE) && (_WIN32_WCE >= 211) && (_AFXDLL)
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>		// MFC template collections
#include <afxmt.h>		// MFC multi-threading

//This will suppress the warning related to the use of sprintf
//and _itoa.Another way is to declare macro _CRT_SECURE_NO_WARNINGS in
//project properties->c/c++ presprocessor
#pragma warning( disable : 4996 ) 
/*stringification macro XSTR(1000) is "1000" */
#define XSTR(s) str(s)
#define str(s) #s
#define DISABLEPRINTF
#define RUN_ON_SBC
//#define ERRMSGBOX
#ifdef _WIN32_WCE
#define USBDISK "\\USBDisk\\"
#define DISK   "\\Disk\\"
#define USBDISKDRIVE "\\USBDisk"
#define DISKDRIVE   "\\Disk"
#else
#define USBDISK "D:\\"
#define DISK   "C:\\Branson\\"
#define USBDISKDRIVE "D:"
//#define DISKDRIVE   "C:"

//#define USBDISK "G:\\"
//#define DISK   "C:\\Branson\\"
//#define USBDISKDRIVE "G:"
//#define DISKDRIVE   "C:\\Branson\\"
#endif
#include <IPHlpApi.h>
//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6F1ED807_2E41_4DDC_AC85_4B46243B0C80__INCLUDED_)
