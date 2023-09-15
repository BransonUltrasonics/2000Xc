/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/USBFolder.h_v   1.9   14 Mar 2015 11:50:40   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/USBFolder.h_v  $
 * 
 *    Rev 1.9   14 Mar 2015 11:50:40   amaurya
 * PrepareListFromLog() function return type changed
 * 
 *    Rev 1.8   28 Jul 2014 14:20:04   rjamloki
 * childview.h file removed.
 * 
 *    Rev 1.7   20 May 2014 11:08:08   rjamloki
 * added new member to class CUSBFolder.
 * 
 *    Rev 1.6   23 Apr 2014 11:26:34   akaushal
 * Added the functionality to read from  WeldHistory.log file
 * 
 *    Rev 1.5   21 Apr 2014 13:46:52   akaushal
 * Added function declaration to create event log.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:36 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:30 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:40 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0    03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_)
#define AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12

class CUSBFolder  : public CVgaMenuItem//CVfdObject
{
public:
	static CString ThirdHierTitle;
	static CString SecondHierTitle;
	static CString LastFolderPath;
	static CString HistoryGraphPath;
	static CString LastFilePath;
	static CString PreviousFileName;
	static CUSBFolder * thisPointer;
	//static int FolderHierchy;
	CString GetDiaplayName(int HierarchyLevel);
	bool PrepareUSBHistoryList(CString Path,CChildView *view,int,int);
	CUSBFolder(CString FileName,CString FilePath,int Address,int Function_Id);
	virtual ~CUSBFolder();
	CString Name;
	CString Path;
	CString DisplayName;
   int TitleID;
   int Fun_Id;
protected:
	void ClearAllFiles();
//	void PrepareUSBList(CChildView *view);
	virtual bool MouseClick(const CPoint &p, CChildView *view);
	virtual void Draw(CDC *pDC);

private:

	
};


void PrepareListFromLog(CString ,int,int, bool, bool,bool = false);
int GetStartingEventCount(void);
//void WeldLiveDataPDFObject(void);
int GetStartingWeldCount(void);
#endif // !defined(AFX_USBFOLDER_H__60024736_DC41_49B6_BA8D_7B1B82BC5AC1__INCLUDED_)
