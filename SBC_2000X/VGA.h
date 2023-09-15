/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGA.h_v   1.10   Nov 03 2017 15:28:08   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGA.h_v  $
 * 
 *    Rev 1.10   Nov 03 2017 15:28:08   RJamloki
 * Added defines for fix bug when using previous version of v12.3 on startup 
 * 
 *    Rev 1.9   Oct 09 2017 10:58:16   RJamloki
 * Added define to support micro c id actuator data
 * 
 *    Rev 1.8   11 Feb 2015 06:23:16   amaurya
 * m_hMutex handler added to handle multiple instances of 2000Xc application
 * 
 *    Rev 1.7   01 Oct 2014 10:55:38   AnPawar
 * GetVQSWindow() declaration removed
 * 
 *    Rev 1.6   11 Sep 2014 09:50:18   rjamloki
 * added new members variables and function in CVGAApp class
 * 
 *    Rev 1.5   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:38 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:06:08 rjamloki  
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     19 Dec 2013 06:16:50 rjamloki  
 * Changed macros to build on both EVC and VC++.
 *
 *    Rev 1.1     05 Jun 2013 09:33:42 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:06 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_)
#define AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Application.h"
void AfxMsgBox(CString x);
class CXmlElement;
#include "Variable.h"
#include "VgaMenu.h"
#include "ObjectMap.h"
#include "XmlFile.h"
#include "TextIOFile.h"
#include "VgaDrawGraph.h"
#include "EventLog.h"

#define MICROC_WITH_AUTHENTIFICATION_SYSTEM_VARIABLES_SIZE 23
#define MICROC_WITHOUT_AUTHENTIFICATION_SYSTEM_VARIABLES_SIZE 27

/////////////////////////////////////////////////////////////////////////////
// CVGAApp:
// See VGA.cpp for the implementation of this class
//
#ifndef _WIN32_WCE
class CVGAApp : public CApplication
{
private:
	HANDLE m_hMutex;
public:
	void Trace(const CString & str);
	CVGAApp();
BOOL InitInstance();
int ExitInstance();
    ~CVGAApp();


//   CMapStringToString OnLinePrintLookUpMenu;
   CTypedPtrList<CPtrList, CVgaDrawGraph *> GraphsDataList;  
   int TotalLangElement;
   void PrepareFunctionMapTable();
   CTextFileIO *configFile;
   CStringArray SpecialMenu;
   CVgaMenu *MenuPointer;
   int total;
   void PrepareStringFromUnicodeText(CString Str,bool FirstTime,bool skipFirstLine);
   void GetSystemVariable();

   static HANDLE hProcess;
   void Clean();
   CObjectMap<CVariable> variables;
   void CreateMenu(CXmlElement * element);
   void CreateBitVariable(CXmlElement * element);
   void CreateEnumVariable(CXmlElement * element);
   void CreatePrintStrings(CXmlElement * element);
   void CreateAlarmStrings(CXmlElement * element);
   void CreateAlarmEng(CXmlElement * element);
   void CreatePresetString(CXmlElement * element);
   void CreateLabelStrings(CXmlElement * element);
   void CreateManualGraph(CXmlElement * element);
   void CreateGraphPrText(CXmlElement * element);
   void CreateHSInfoText(CXmlElement *e);
   void ParseXmlTree(CXmlElement * gui);
   void CreateMonthStrings(CXmlElement *e);
   void CreateEventDesc(CXmlElement * element);
    void CreateParamDesc(CXmlElement * element);
   //void CreateSpecialMenu(CXmlElement * gui);
   CXmlFile file;
   CXmlElement * gui;
   CObjectMap<CVgaMenu> menus;
   CObjectMap<EventDescription> eds;
   CObjectMap<ParamDescription> pds;
   CString menuName;
   CVariable * GetVariable(const CString & varName) const;
   void DrawMenu(CDC * pDC);
   bool ReadXML();
   enum 
   {
      ACK = 0x06,
      NAK = 0x15
   };
protected:
   bool logOpen;
   CSocket log;
   CMutex logMutex;
   CStringList logData;
	DECLARE_MESSAGE_MAP()
};

extern CVGAApp theApp;
extern CMapStringToPtr functionCall;
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGA_H__8C4E6ACD_AEDC_4E4A_B9F0_0138E81A7B92__INCLUDED_)
