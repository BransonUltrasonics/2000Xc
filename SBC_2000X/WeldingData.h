/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingData.h_v   1.11   16 Apr 2015 06:07:36   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingData.h_v  $
 * 
 *    Rev 1.11   16 Apr 2015 06:07:36   sesharma
 * extern declaration for CString NotApplicable.
 * 
 *    Rev 1.10   11 Dec 2014 06:52:02   RJamloki
 * MAXPARAMVALUES vallue increased to 34 to add Powersupply serial number and actuator serial number along with each weld data.
 * 
 *    Rev 1.9   28 Nov 2014 08:35:06   rjamloki
 * recursive inclusion CChildView.h removed to fix Coverity issue
 * 
 *    Rev 1.8   26 Aug 2014 07:50:26   rjamloki
 * Added a macro UNITHEADINGGAP for weldhistory pdf.
 * 
 *    Rev 1.7   22 Aug 2014 12:38:12   rjamloki
 * Max param define changed to 32 after hold force addition
 * 
 *    Rev 1.6   09 Jul 2014 07:27:48   akaushal
 * Declaration removed from WeldingData class.
 * 
 *    Rev 1.5   27 May 2014 06:47:16   amaurya
 * Updated Macro for Maximum Column in Weld History Data
 * 
 *    Rev 1.4   21 Apr 2014 13:55:38   akaushal
 * ONEHEADINGGAP,TWOHEADINGGAP,ABSGAP macros added.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:14:06 rjamloki  
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:06:30 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_)
#define AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXPARAMVALUES          34 
#define MODEPRESETSTRINGRECT	CRect(100,100,250,125)
#define CYCLENUMSTRRECT			CRect(125,150,125,150)
#define TIMESTRRECT				CRect(125,175,125,175)
#define DATESTRRECT				CRect(125,200,125,200)
#define TIMEMODE	1
#define ENERGYMODE	2
#define PKPOWERMODE	3
#define COLLAPSEMODE	4
#define ABSOLUTEMODE	5	
#define GRDDETECTMODE	6
#define CONTINUOUSMODE	7
#define PARAMETERWIDTH 88
#define XCORDINC 85
#define RUN_RESULT_TBL_START_X  8
#define RUN_RESULT_TBL_START_Y  50
#define HISTORY_TBL_START_X  20
#define HISTORY_TBL_START_Y  30


#define NCALARM        0
#define OLALARM        32
#define EQALARM        64
#define CMALARM        96
#define CAALARM        128
#define WAALARM        160 
#define PRALARM        192
#define PSALARM        224

#define ONEHEADINGGAP	17
#define TWOHEADINGGAP	34
#define ABSGAP			15
#define UNITHEADINGGAP	68


#include "VgaMenuItem.h"
#include "HistoryData.h"


#include "hpdf.h"

class CXmlElement;

class CWeldingData : public CVgaMenuItem  
{
public:
   static bool ValueFlag;
   int HistoryObjectNum;
   int PrintAlarms(int i,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString);
   int GetAlarms(int  UIAlarmField, int IOffset,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString);
   int *NoCycleAlarms,*OverloadAlarms,*EquipmentFailureAlarms,
   *CycleModifiedAlarms,*CalibrateAlarms,*Warnings,*RejectBitResult,*SuspectBitResult;
   void StoreAlarmInformation(unsigned char * &data, int & length,int i);
   int ReceivedUniversalCount;
   CWeldingData(int NoOfCycles, unsigned char * &data, int & length,bool SelectData);
   CString* ColumnHeading;
   int UniqueId;

   int TotalColoumn;
   void DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo);
   CWeldingData(int TotalColoumn, unsigned char * &data, int & length);
   bool HistoryContinued;
   int PrintHistoryYCord;
   int TotalCyclesPrinted;
   int TotalCycles;
   CString GetMode_PresetString(unsigned char * &data,int & length);
   CString GetWeldDataString(unsigned char * &data,int & length);
   CWeldingData( unsigned char * &data,int & length,bool PrintData);
   int PresetNumber;
   bool Units;
   int PrintWeldData(CDC *pDC, int StartYCord, bool DrawUnits, bool DrawPresetString, int HISTORYPAGENO,CChildView *view);
   CString *AllParamValues;
   int *AllParamIDs;
   //CString CycleCountStr;
   void Print(CDC *pDC,CChildView *view);
   CString* Time_String;
   CString* Date_String;
   CString* Mode_PresetString;
   static int CycleCount;
   CWeldingData(unsigned char * &data, int & length);
   CWeldingData(unsigned char * &data, int & length,int TotalColoumn);
   virtual ~CWeldingData();
   virtual void Draw(CDC *pDC);
   int Parameter_ID[5];
protected:
   int Lang_Index;

   virtual bool MouseClick(const CPoint &p, CChildView *view);
public:
 
   void StoreDate_Time(unsigned char *&data, int &length, CString* Date ,CString* Time);
   int TextColour;
   CString * Parameter_Value;
   int ParamCount;


};
extern CString NotApplicable;
#endif // !defined(AFX_WELDINGDATA_H__F6B130DD_D3C9_43CB_A4FF_E893D0BAE7AA__INCLUDED_)
