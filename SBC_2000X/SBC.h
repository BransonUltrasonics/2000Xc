/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/SBC.h_v   1.8   01 Oct 2014 10:51:50   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/SBC.h_v  $
 * 
 *    Rev 1.8   01 Oct 2014 10:51:50   AnPawar
 * GetVQSWindow() declaration removed
 * 
 *    Rev 1.7   21 Apr 2014 13:43:02   akaushal
 * Removed unused variables.
 * 
 *    Rev 1.6   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.5     05 Mar 2014 14:13:28 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.4     03 Jan 2014 09:05:06 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.3     19 Dec 2013 06:16:50 rjamloki     
 * Changed macros to build on both EVC and VC++.
 *
 *    Rev 1.2     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:30 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:56 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_)
#define AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "Application.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSBCApp:
// See SBC.cpp for the implementation of this class
//

void AfxMsgBox(CString x);
class CXmlElement;
#include "Variable.h"
#include "VgaMenu.h"
#include "ObjectMap.h"
#include "XmlFile.h"
#include "TextIOFile.h"
#include "VgaDrawGraph.h"

#ifdef _WIN32_WCE
class CSBCApp : public CApplication
{
public:
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
   void Trace(const CString & str);
   CSBCApp();
   virtual ~CSBCApp();
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
   //void CreateSpecialMenu(CXmlElement * gui);
   CXmlFile file;
   CXmlElement * gui;
   CObjectMap<CVgaMenu> menus;
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

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CSBCApp)
   public:
   virtual BOOL InitInstance();
   virtual int ExitInstance();
   //}}AFX_VIRTUAL
   //{{AFX_MSG(CSBCApp)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

extern CSBCApp theApp;
extern CMapStringToPtr functionCall;
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBC_H__89F7163D_8049_4414_B1E2_80499808B46F__INCLUDED_)
