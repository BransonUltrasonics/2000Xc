/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaButton.h_v   1.22   11 Mar 2015 09:28:30   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaButton.h_v  $
 * 
 *    Rev 1.22   11 Mar 2015 09:28:30   amaurya
 * GetNameFromID() declaration changed to send parameter name with event description while user request for evend data through webservice.
 * 
 *    Rev 1.21   30 Jan 2015 08:15:50   amaurya
 * GetNameFromID() added to extract parameter name from parameterId.
 * 
 *    Rev 1.20   02 Jan 2015 05:04:02   rjamloki
 * CopyAllPreset() and CopyPresetOnOKOrCancelButton() functions declared
 * 
 *    Rev 1.19   28 Nov 2014 08:33:10   rjamloki
 * Unused function declarations removed
 * 
 *    Rev 1.18   14 Nov 2014 02:54:40   rjamloki
 * extern CString DownspeedMenuName added.
 * 
 *    Rev 1.17   26 Sep 2014 09:31:46   rjamloki
 * Added ExitMenuSndEnableWeld prototype
 * 
 *    Rev 1.16   25 Sep 2014 12:11:58   AnPawar
 * function declarations for  AddUnitToUser(),GetOLString(), callInvalidate()
 * 
 *    Rev 1.15   11 Sep 2014 09:53:44   rjamloki
 *  Added some function declaration.
 * 
 *    Rev 1.14   05 Sep 2014 07:03:56   amaurya
 * Variable declaration added.
 * 
 *    Rev 1.13   18 Aug 2014 08:07:16   rjamloki
 * Added Function declartions related to down speed tune.
 * 
 *    Rev 1.12   28 Jul 2014 14:33:46   rjamloki
 * declared functions void SwUpGrade(int ar); void SendClampAlarm(int Address);
 * 
 *    Rev 1.11   09 Jul 2014 07:13:32   akaushal
 * Include EventLog.h
 * 
 *    Rev 1.10   11 Jun 2014 06:49:50   rjamloki
 * PrintEventHistoryToPDF() function declaration changed
 * 
 *    Rev 1.9   09 Jun 2014 12:02:00   rjamloki
 * removed unused variables from class
 * 
 *    Rev 1.8   27 May 2014 06:46:04   amaurya
 * Duplicate macro DATAINONEPACKET removed 
 * 
 *    Rev 1.7   20 May 2014 11:12:08   rjamloki
 * Externs declared
 * 
 *    Rev 1.6   21 Apr 2014 13:52:26   akaushal
 * Declaration for LiveDataFileName added. 
 * 
 *    Rev 1.5   28 Mar 2014 14:33:18   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     06 Mar 2014 11:30:44 rjamloki  
 * Add new User ID function
 *
 *    Rev 1.3     05 Mar 2014 14:13:40 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.2     27 Feb 2014 01:47:30 jerryw.wang     
 * Added the DigitalOutput and Activated variables for the Digital Output Process.
 *
 *    Rev 1.1     03 Jan 2014 09:06:24 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:10 amaurya      
 * Initial Revision.
 *
*/

#if !defined(AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_)
#define AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "ChildView.h"
#include "EventLog.h"
#include "VgaDrawGraph.h"
#include "VgaTitle.h"

#define MAXPRESETBUFFSIZE (1536 * 1024)
union GetSetUser{
		struct{
			unsigned short s1;
			unsigned short s2;
		}struct1;
		struct{
			unsigned char c[4];
		}struct2;
	};

class CXmlElement;
class CVgaScreenSetup;
class CVgaButton : public CVgaMenuItem  
{
public:
   CVgaButton(CXmlElement * e);
   CVgaButton(CString str,int X1,int Y1,int X2,int Y2,CString Fun);
   virtual ~CVgaButton();
   CRect Rect;
   CString FunName;
   CString MenuName;
   CString MenuNak;
   bool ArrowType;
   bool ArrowTypeDown;
   bool ScreenArrowUp;
   bool ScreenArrowDown;
   bool LeftArrow;
   bool RightArrow;
   bool DigitalOutput;
   bool Activated;
	bool Disable;
   CString argument;
   CString SubText;
	void PrintEventHistoryToPDF(struct Event_Log * Rcv, int Len);
   void DrawArrow(CPoint Start, CPoint Middle, CPoint End,CDC *pDC);
protected:
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;

};



extern short HSCurrentGraph[GRAPH_WIDTH];
extern short HSAmpGraph[GRAPH_WIDTH];
extern CString EventChangeMenuName;
extern CString DownspeedMenuName;
extern char SavedPgNum;
extern CString EventDataFileName;
extern CString HistoryDataFileName;
extern int PresetVerify;
extern bool UserLoggedinFlag;
void SwUpGrade(int arg);
void SendClampAlarm(int Address);
void DownSpeedTuneFunc(int Address);
void SaveDownspeedtune(int Address);
void ExitDownspeedtune(int Address);
bool CheckDownspeedFlag(CVgaButton *ptr);
void GetDownspeedtuneFlag(void);
void SetDownspeedFlag(int Address);
void SendEventReasonString(int Address);
void AddUnitToUser(int Address);
void GetOLString(int Address);
bool callInvalidate(CVgaTitle *ptr);
void ExitMenuAndEnableWeld(int Address);
void SetValidated(int Address);
void CancelValidated(int Address);
void SetLocked(int Address);
void CancelLocked(int Address);
void SendEstopLogin(int Address);
void CopyAllPreset(void);
void CopyPresetOnOKOrCancelButton(void);
void CheckVerifiedPreset(int Address);
void StartSensorCal(int Address);
CString GetNameFromID(int ParamID,bool InEnglish = false);
#endif // !defined(AFX_VGABUTTON_H__1233EE4C_1F55_45C1_B860_3C25D3CE762C__INCLUDED_)
