/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingHistory.h_v   1.24   16 Apr 2015 06:08:48   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingHistory.h_v  $
 * 
 *    Rev 1.24   16 Apr 2015 06:08:48   sesharma
 * New macro NOTAPPLICABLETEXT_ID added.
 * 
 *    Rev 1.23   08 Apr 2015 13:10:26   AnPawar
 *  macros added for PressureA and PressureB headings in pdf.
 * 
 *    Rev 1.22   01 Apr 2015 12:59:06   amaurya
 * HistoryAlarm() and HistoryAlarmPDF() prototype change to fix the blank pdf issue in case of large number of alarms.
 * 
 *    Rev 1.21   11 Mar 2015 09:28:20   amaurya
 * Macros added to display OK button on first time login screen.
 * 
 *    Rev 1.20   26 Jan 2015 13:42:18   rjamloki
 * Added macro for please wait string id
 * 
 *    Rev 1.19   06 Jan 2015 05:13:16   AnPawar
 * defines for date format ID
 * 
 *    Rev 1.18   02 Jan 2015 06:36:30   rjamloki
 * macros defined for  MAX_VIEW_HISTORYPARAM,MANDATORY_PARAM_MASK_LEVELC and MANDATORY_PARAM_MAS
 * 
 *    Rev 1.17   11 Dec 2014 06:52:20   RJamloki
 * VALIDATED_ID and NONVALIDATED_ID macro added.
 * 
 *    Rev 1.16   28 Nov 2014 08:35:24   rjamloki
 * PrepareWeldHistoryList() function removed and macros for pdf header string ids changed
 * 
 *    Rev 1.15   14 Nov 2014 02:52:28   rjamloki
 * Macros added for WeldHistory Pdf.
 * 
 *    Rev 1.14   10 Nov 2014 02:53:00   rjamloki
 * ACSERNUM_HEADING_STRID and PSSERNUM_HEADING_STRID macros added.
 * 
 *    Rev 1.13   20 Oct 2014 05:52:54   RJamloki
 * DrawHeading() function prototype changed.
 * 
 *    Rev 1.12   26 Aug 2014 07:53:44   rjamloki
 * Added  void DrawHeading(CHistoryData* object,HPDF_Page * page,int Unit) 
 * 
 *    Rev 1.11   28 Jul 2014 14:43:08   rjamloki
 * CWeldingHistory::DrawLOGWeldData(HPDF_Page * page,HPDF_Doc  * pdf,HPDF_Font def_font,bool UnitFlag) return type changed
 * 
 *    Rev 1.10   09 Jul 2014 07:28:46   akaushal
 * Added declarations and variables in CVgaMenuItem
 * 
 *    Rev 1.9   09 Jun 2014 12:08:48   rjamloki
 * macro added for setup mask
 * 
 *    Rev 1.8   27 May 2014 06:15:56   amaurya
 * Added flag fpr Weld History Log full
 * 
 *    Rev 1.7   20 May 2014 11:18:12   rjamloki
 * Changed function declaration in class CWeldingHistory 
 * 
 *    Rev 1.6   07 May 2014 13:17:04   akaushal
 * added a flag to display units on PDF
 * 
 *    Rev 1.5   23 Apr 2014 11:47:00   akaushal
 * Added a global count to keep track of Weld Data in log file
 * 
 *    Rev 1.4   21 Apr 2014 13:57:28   akaushal
 * Variables and function declaration added for preparing log file and PDF. Units to distinguish between date format.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:14:06 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.1    03 Jan 2014 09:06:30 rjamloki  
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_)
#define AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "VgaMenuItem.h"
#include "ChildView.h"
#include "RunScreen.h"
#include "WeldingData.h"

#define LeftButton_Rect CRect(45,370,95,420)
#define ScreenUpButton_Rect CRect(105,370,155,420)
#define UpButton_Rect CRect(165,370,215,420)
#define DownButton_Rect CRect(225,370,275,420)
#define ScreenDownButton_Rect CRect(285,370,335,420)
#define RightButton_Rect CRect(345,370,395,420)
#define GraphsButton_Rect CRect(X_CORDINATE_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT-100,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitButton_Rect CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define UpArrowRect CPoint(180,404), CPoint(190, 386),CPoint(201,404)
#define DownArrowRect CPoint(240,386), CPoint(250,404),CPoint(261,386) 
#define LeftArrowRect CPoint(80,386), CPoint(60,395),CPoint(80,404)
#define RightArrowRect CPoint(360,386), CPoint(380,395),CPoint(360,404)
#define ScreenUpArrow1Rect CPoint(120,398), CPoint(130, 382),CPoint(141,398) 
#define ScreenUpArrow2Rect CPoint(120,408), CPoint(130, 392),CPoint(141,408) 
#define ScreenDownArrow1Rect CPoint(300,382), CPoint(310,398 ),CPoint(321,382) 
#define ScreenDownArrow2Rect CPoint(300,392), CPoint(310, 408),CPoint(321,392) 
#define MAXPARAMUNITLENGTH	 7
#define WELDHISTORYMASK 0XFFCFDFFE
#define WELDHISTORYCOLUMNWIDTH 800
#define ACSERNUM_HEADING_STRID 2562
#define PSSERNUM_HEADING_STRID 2561
#define USERID_HEADING_STRID 2702
#define PRESETNUM_HEADING_STRID 1840
#define PRESETREV_HEADING_STRID 4038
#define SETAMPA_HEADING_STRID 4059
#define SETAMPB_HEADING_STRID 4060
#define TRIFORCE_HEADING_STRID 4308
#define ACTASSMNO_HEADING_STRID 4149
#define PSASSM_HEADING_STRID 4150
#define STACKASSM_HEADING_STRID 4151
#define VALIDATED_ID 2960
#define NONVALIDATED_ID 2961
#define DDMMYY_ID 4321
#define MMDDYY_ID 4322
#define PLEASEWAIT_ID 1758
#define BATCHCOUNTTEXT_ID 4277
#define OK_BUTTONTEXT_ID 1124
#define PRESSUREA_HEADING_STRID 4390
#define PRESSUREB_HEADING_STRID 4391
#define NOTAPPLICABLETEXT_ID 1897

//max viewable parameters in weld history table. This number is based on enum RUN_PARAM in menu.h in WC code
#define MAX_VIEW_HISTORYPARAM				32 
//Below define represents the parameters which cant be configured for viewing from system config->weld history setup and always need to be shown on weld history table for control level C
//this define is based on bit fields of BIT_FLAGS structure in MENU1.h in WC code
#define MANDATORY_PARAM_MASK_LEVELC		 0x1FF   
//Below define represents the parameters which cant be configured for viewing from system config->weld history setup and always need to be shown on weld history table below control level C
//this define is based on bit fields of BIT_FLAGS structure in MENU1.h in WC code
#define MANDATORY_PARAM_MASK_BELOWLEVELC 0x009


class CXmlElement;

class CWeldingHistory : public CVgaMenuItem  
{
public:
   CWeldingHistory(CXmlElement * e);
   virtual ~CWeldingHistory();
   static TCHAR ParameterUnitUSCS[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
   static TCHAR ParameterUnitMetric[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
   static int SelectedWeldId;
   bool SelectedDataUnit;
   void DrawParameterHeadings(CDC * pDC);
   bool USBHistory;
   int *Parameter_ID;
   int TotalColoumn;
   bool Units;
   static int TopMostData;
   void DrawHistoryData(CDC *pDC);
   int TotalCycle;
   static unsigned int TotalDataInFile;
   static bool WeldSpaceFullFlag;
   TCHAR USBMode_PresetString[MAXMODEPRESETLENGTH];
   static int CurrentDisplayWeldCount;

   void UpdateWeldData(unsigned char *&data, int &length);
   CWeldingHistory(unsigned char * &data, int & length);
   CWeldingHistory();
   CTypedPtrList<CPtrList, CWeldingData *> WeldHistoryList;
   CTypedPtrList<CPtrList, CHistoryData *> USBWeldHistoryList;
   CTypedPtrList<CPtrList, CHistoryData *> LOGWeldHistoryList;

   

   static int SelectedWeldData;
   static int LeftMostParameter;
   static CWeldingHistory * thisHisPtr;	
//   bool PrepareLOGHistoryList();
   int PrepareWeldHistoryList(CString Path, int StartingPoint, int Count,HPDF_Doc  &pdf,HPDF_Page &page,HPDF_Font &def_font,bool = false);
   bool DrawLOGWeldData(HPDF_Page * page,HPDF_Doc  * pdf,HPDF_Font *def_font,bool UnitFlag = false);
   void DrawLOGParameterHeading(int Unit,HPDF_Page * page=NULL); //CHistoryData* object,
   void DrawHeading(CHistoryData* object,HPDF_Page * page,int Unit,HPDF_Doc  * pdf,HPDF_Font *def_font);
   static  CString FilePath,Path;
   int HistoryAlarm(int i,CString CycleNumString,HPDF_Doc  * pdf,HPDF_Page * page,HPDF_Font *def_font,CHistoryData *);
   int HistoryAlarmPDF(int  UIAlarmField, int IOffset,CString CycleNumString,HPDF_Doc  * pdf,HPDF_Page * page,HPDF_Font *def_font);
   //   static bool LiveHeaderFlag;//to print header if no file present in specific folder
protected:
   bool UpButtonPressed;
   bool DownButtonPressed;
   bool LeftButtonPressed;
   bool RightButtonPressed;
   bool ScreenUpButtonPressed;
   bool ScreenDownButtonPresssed;
   bool GraphsButtonPressed;
   bool ExitButtonPressed;
   virtual bool MouseClick(const CPoint &p, CChildView *view);
   virtual void Draw(CDC * pDC) ;
   private:
   int lang_index;
};

#endif // !defined(AFX_WELDINGHISTORY_H__7869CA3B_A6C6_4444_A3DD_AFF3C58B13CA__INCLUDED_)
