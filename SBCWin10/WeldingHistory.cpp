/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingHistory.cpp_v   1.27   16 Apr 2015 06:08:12   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingHistory.cpp_v  $
 * 
 *    Rev 1.27   16 Apr 2015 06:08:12   sesharma
 * Removed the hard-coded strings.
 * 
 *    Rev 1.26   08 Apr 2015 13:09:58   AnPawar
 * DrawHeading() and DrawLOGWeldData() functions to print PressureA and PressureB in pdf.
 * 
 *    Rev 1.25   01 Apr 2015 12:58:22   amaurya
 * change in functions HistoryAlarm() and HistoryAlarmPDF() functions to fix the blank pdf issue in case of large number of alarms.
 * 
 *    Rev 1.24   05 Jan 2015 05:31:24   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.23   11 Dec 2014 06:52:10   RJamloki
 * DrawLOGWeldData() changed to read Powersupply serial number and actuator serial number from welddata.log file.
 * 
 *    Rev 1.22   28 Nov 2014 08:35:16   rjamloki
 *  Warnings removed and Coverity fix
 * 
 *    Rev 1.21   14 Nov 2014 02:54:54   rjamloki
 * Removed Unused Variables.DrawLOGWeldData(),DrawHeading(),HistoryAlarmPDF() changed to support multibyte language.
* 
*    Rev 1.20   10 Nov 2014 02:52:46   rjamloki
* DrawLOGWeldData(),CWeldingHistory::DrawHeading(),CWeldingHistory::DrawLOGParameterHeading() and HistoryAlarmPDF() changed for multilanguage PDF support.
* 
*    Rev 1.19   20 Oct 2014 05:52:04   RJamloki
*  DrawHeading() function changed to support actuator serial number and to resolve pdf overwrite issue.
* 
*    Rev 1.18   06 Oct 2014 03:29:52   rjamloki
*  change in DrawLOGWeldData() function to fix wrong force unit in pdf 
* 
*    Rev 1.17   01 Oct 2014 10:56:40   AnPawar
* CWeldingHistory::DrawHeading() function changed
* 
*    Rev 1.16   05 Sep 2014 07:06:56   amaurya
* Corrected the list traverse in DrawHistoryData().Modified DrawParameterHeadings().
* 
*    Rev 1.15   26 Aug 2014 07:52:08   rjamloki
* Added DrawHeading() function,DrawLOGParameterHeading() and DrawLogWeldData() changed.
* 
*    Rev 1.14   22 Aug 2014 12:40:28   rjamloki
* pdf history column temporary fix
* 
*    Rev 1.13   28 Jul 2014 14:42:22   rjamloki
* CWeldingHistory::DrawLOGWeldData(HPDF_Page * page,HPDF_Doc  * pdf,HPDF_Font def_font,bool UnitFlag) return type changed.
* 
*    Rev 1.12   09 Jul 2014 07:28:18   akaushal
* DrawHistoryData(),DrawLOGWeldData() changed.HistoryAlarm(),HistoryAlarmPDF() added.
* 
*    Rev 1.11   09 Jun 2014 12:08:20   rjamloki
*  Variable initialization in constructor.Changes for weld history setup
* 
*    Rev 1.10   27 May 2014 18:14:08   akaushal
* Updated Weld setup code for spacing in display
* 
*    Rev 1.9   27 May 2014 06:28:42   amaurya
* Updated code for column width on Display screen and PDF
* 
*    Rev 1.8   20 May 2014 11:17:40   rjamloki
* Changed the data logging
* 
*    Rev 1.7   07 May 2014 13:16:32   akaushal
* added margin on the weld history pdf
* 
*    Rev 1.6   23 Apr 2014 12:02:18   akaushal
* Code updation for Live data logging and code cleanup
* 
*    Rev 1.5   21 Apr 2014 13:56:50   akaushal
* LOGWeldHistoryList stores weld data object from log file 
* PrepareLOGHistoryList() reads log file and add object to list.
*  DrawLOGWeldData() this function prepare PDF from weld data list. DrawLOGParameterHeading() this function print heading in PDF.
* 
*    Rev 1.4   28 Mar 2014 14:33:24   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.3     05 Mar 2014 14:14:06 rjamloki  
* Screens and PDF working
*
*    Rev 1.2     03 Jan 2014 09:06:30 rjamloki  
* Header Fix and added command to assign ip.
*
*    Rev 1.1     18 Dec 2013 10:00:36 rjamloki     
* Initial Test version.SBC to WC serial communication.
*
*    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
* Initial Revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "WeldingHistory.h"
#include  "ChildView.h"
#include "WeldingData.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include "hpdf.h"
#include "zlib.h"
#include "png.h"
#include "UserId.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifndef _WIN32_WCE
#define ZLIB_WINAPI
#endif

extern jmp_buf env;
#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
   extern error_handler(HPDF_STATUS   error_no,
   HPDF_STATUS   detail_no,
   void         *user_data);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern int eventname;
extern char Historyfname[64];
extern int HistorySetUp;
extern POSITION HistoryTemp_pos;
extern POSITION WeldTemp_pos;
extern CList<CString,CString> tempHistoryList;
extern CList<CString,CString> tempWeldList;
unsigned int CWeldingHistory::TotalDataInFile;
bool CWeldingHistory::WeldSpaceFullFlag =  false;
int CWeldingHistory::TopMostData;
int CWeldingHistory::SelectedWeldData;
int CWeldingHistory::LeftMostParameter;
int CWeldingHistory::SelectedWeldId=1;

CString CWeldingHistory::FilePath;
CString CWeldingHistory::Path;
int CWeldingHistory::CurrentDisplayWeldCount;
//bool CWeldingHistory::LiveHeaderFlag = true;

TCHAR CWeldingHistory::ParameterUnitUSCS[MAXPARAMVALUES][MAXPARAMUNITLENGTH];
TCHAR CWeldingHistory::ParameterUnitMetric[MAXPARAMVALUES][MAXPARAMUNITLENGTH];


int YCoordinate = TWOWELDLINEGAP;
//bool HeaderFlag = true;
int PageCount = 1;

char Heading_Specific[20] = {1,2,29,9,10,11,12,14,15,16,17,22,30,23,24,25,26,27,28};
bool UnitHeadingPos = false;
bool heading_draw = false;
char Heading_Str[256];
CString Time,Date;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeldingHistory * CWeldingHistory::thisHisPtr;
CWeldingHistory *HistoryObj = NULL;
CString PsSerialNoStrHdr = _T("");
CString ActSerialNoStrHdr = _T("");
CString UserIdStrHdr = _T("");
CString PresetStrHdr = _T("");
CString PresetRevStrHdr = _T("");
CString SetAmpAStrHdr = _T("");
CString SetAmpBStrHdr = _T("");
CString TriggerForceStrHdr = _T("");
CString ActAssmNoStrHdr = _T("");
CString PsAssmNoStrHdr = _T("");
CString StackAssmNoStrHdr = _T("");
CString ValidatedStr = _T("");
CString NonValidatedStr = _T("");
CString PressureAStrHdr = _T("");
CString PressureBStrHdr = _T("");


CWeldingHistory::CWeldingHistory(CXmlElement * e)
{
   SelectedDataUnit = 0;
   USBHistory = false;
   Parameter_ID = 0;
   TotalColoumn = 0;
   Units = 0;
   TotalCycle = 0;
   UpButtonPressed = false;
   DownButtonPressed = false;
   LeftButtonPressed = false;
   RightButtonPressed = false;
   ScreenUpButtonPressed = false;
   GraphsButtonPressed = false;
   ExitButtonPressed = false;
   lang_index = 0;
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      CString tag = element->GetTag();
      if (tag == "condition")
      {
         AddCondition(element);
      }
      else
         ASSERT(FALSE);
   }
   thisHisPtr=this;
   CWeldingHistory::LeftMostParameter=1;
   Parameter_ID=new int[32];
   for(int i = 0; i < 31;i++)
   {
      Parameter_ID[i] = i+1;
   }
   ScreenDownButtonPresssed = false;
}

CWeldingHistory::CWeldingHistory()
{
   SelectedDataUnit = 0;
   TotalColoumn = 0;
   Units = 0;
   TotalCycle = 0;
   UpButtonPressed = false;
   DownButtonPressed = false;
   LeftButtonPressed = false;
   RightButtonPressed = false;
   ScreenUpButtonPressed = false;
   GraphsButtonPressed = false;
   ExitButtonPressed = false;
   lang_index = 0;
   USBHistory=true;
   Parameter_ID=new int[32];
   for(int i = 0; i < 31;i++)
   {
      Parameter_ID[i] = i+1;
   }
   ScreenDownButtonPresssed = false;
}

/***********************************************************************/
/* This function is called when History data list needs to be updated. */
/*																	   */	
/***********************************************************************/
void CWeldingHistory::UpdateWeldData(unsigned char *&data, int &length)
{
   //	data+=9;//Co-ordinates for rectangle.
   //	length-=9;
   int TotalColoumn = *data++;length--;
   data+=TotalColoumn; //skip the bytes
   length -= TotalColoumn;
   data = data + 4;
   length = length - 4;
   int Cycle = *data++;
   TotalCycle +=Cycle;
   length--;

   //storing parameters whose ID matches with displayable parameter ID 
   for(int cycle =0;cycle<Cycle;cycle++)
   {
      CWeldingData * obj = new CWeldingData(TotalColoumn,data, length);
      WeldHistoryList.AddTail(obj);
   }
}

CWeldingHistory::~CWeldingHistory()
{
   if(Parameter_ID != NULL) {
      delete []Parameter_ID;
      Parameter_ID = NULL;
   }
   while(WeldHistoryList.GetCount()>0)
      delete WeldHistoryList.RemoveHead();
   while(USBWeldHistoryList.GetCount()>0)
   {
      CHistoryData *obj1 = USBWeldHistoryList.RemoveHead();//delete
      free(obj1);
   }
   while(LOGWeldHistoryList.GetCount()>0)
   {
      CHistoryData *obj2 = LOGWeldHistoryList.RemoveHead();//delete
      free(obj2);
   }

}


/****************************************************************************************/
/*  This function draws the Weld-History screen.										*/
/*  the function checks if the button is pressed or not, if found then draws it in      */
/*  pressed state.																		*/
/*																						*/
/****************************************************************************************/
void CWeldingHistory::Draw(CDC *pDC)
{
   DrawHistoryData(pDC);
}


/**********************************************************************************************/
/* this function handles the mouse click if it is on the Weld-History screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */	
/**********************************************************************************************/	
bool CWeldingHistory::MouseClick(const CPoint &p, CChildView *view)
{
   return true;
}
/****************************************************************************************/
/*																						*/
/* The following function is used to Draw history data. The function checksthe Top most	*/
/* Data and the Left Most PArameter on the screen and displays next seven weld data		*/
/* from the Top most weld data.															*/
/****************************************************************************************/
void CWeldingHistory::DrawHistoryData(CDC *pDC)
{	
   CRunScreen::Displayable_columns=5;
   int LineNo=1;
   int TotalCyclesDrawn=0;
   if(USBWeldHistoryList.GetCount())
   {
      POSITION pos = USBWeldHistoryList.GetHeadPosition();
      LineNo=1;
      for(int CurrentPos = 1 ; (CurrentPos < TopMostData) && pos; CurrentPos++)
         USBWeldHistoryList.GetNext(pos);
      DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+3)),
         (HISTORY_TBL_START_X + WELDHISTORYCOLUMNWIDTH - 12),
         (HISTORY_TBL_START_Y+LINE_GAP*(SelectedWeldData+4))));
      while(pos)
      {	
         if(TotalCyclesDrawn==MAXCYCLEPERSCREEN)
            break;
         CHistoryData * Obj = USBWeldHistoryList.GetNext(pos);
         if(LineNo==SelectedWeldData)
         {
            SelectedDataUnit=Obj->Units;
            SelectedWeldId=Obj->UniqueId;
         }
         Obj->DrawUSBHistory(pDC,LeftMostParameter, LineNo);
         TotalCyclesDrawn++;
         LineNo++;
      }
   }
   DrawParameterHeadings(pDC);
}
/********************************************************************************************/	
/* The following function is used to draw parameter headings on the Weld history screen.	*/
/* The function checks for the unit of the selected weld data and draws the unit accordingly*/
/*																							*/
/********************************************************************************************/
void CWeldingHistory::DrawParameterHeadings(CDC *pDC)
{
   if(LeftMostParameter>(TotalColoumn-4))
      LeftMostParameter=1;
   CHistoryData * Obj ;
   int pos ;
   POSITION Pos;

   if(USBWeldHistoryList.GetCount())
   {
      pos = SelectedWeldData;
      Pos = USBWeldHistoryList.GetHeadPosition();
      Obj = USBWeldHistoryList.GetHead();
      while((pos--) && Pos)
         Obj = USBWeldHistoryList.GetNext(Pos);
   }
   int X1 = 20;
   int Y1 =60;
   int Width =160;
   int Height = 30;
   CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
   CRect UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
   DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Heading[0],false);
   X1 += Width;
   int DisplayCount = 1;
   for(int index = LeftMostParameter; (unsigned int)index < HisParameterCounts ; index++)
   {
      TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
      UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
      for(int index1 = 1 ; index1 < CChildView::TotalTextHeading ; index1++)
      {
         int ID;
         ID = HisParameterMap[index];
         if(ID == CChildView::Parameter_ID[index1])
         {
            //printf("\n%S = %d",CChildView::Parameter_Heading[index1],CChildView::Parameter_ID[index1]);
            DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Heading[index1],false);
            if(SelectedDataUnit)
               DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_Metric[index1],false);
            else
               DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_USCS[index1],false);
            X1 +=Width;
            DisplayCount++;
         }
         if(Parameter_ID[index] ==0) 
         {
            DrawText(pDC, SmallFont, Black, TextRect, "****",false);
            X1 +=Width;
            DisplayCount++;
         }
      }
   }
   CPen *oldPen;
   CPen NewPen;
   NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[Black]);
   oldPen = pDC->SelectObject(&NewPen);
   pDC->MoveTo(20,Y1+2*Height+10);
   pDC->LineTo(620,Y1+2*Height+10);
   pDC->SelectObject(oldPen);
   NewPen.DeleteObject();
}


int CWeldingHistory::PrepareWeldHistoryList(CString Path,int StartingPoint,int Count, HPDF_Doc  &pdf,HPDF_Page &page,HPDF_Font &def_font,bool UnitFlag)
{
   int PdfPageCount = 1;

   if(StartingPoint < 0 || (Count == 0))
      return false;

   while(CWeldingHistory::thisHisPtr->LOGWeldHistoryList.GetCount()>0)
   {
      CHistoryData *obj1 = CWeldingHistory::thisHisPtr->LOGWeldHistoryList.RemoveHead();//delete
      free(obj1);
   }

   CFile f;
   CFileException e;

   if( !f.Open(Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {
#ifdef _DEBUG
      if(e.m_cause==CFileException::generic)
         TRACE(_T("\n !! GENERIC"));
      else if(e.m_cause==CFileException::badPath   )
         TRACE(_T("\n !! bad path"));
      else if(e.m_cause==CFileException::tooManyOpenFiles    )
         TRACE(_T("\n !! too many files open"));
      else if(e.m_cause==CFileException::fileNotFound )
         TRACE(_T("\n !! file not found"));
      else if(e.m_cause==CFileException::accessDenied       )
         TRACE(_T("\n !! access denied"));
      else if(e.m_cause==CFileException::diskFull      )
         TRACE(_T("\n !! disc full"));
      else if(e.m_cause==CFileException::invalidFile   )
         TRACE(_T("\n !! invalid file"));
      afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
   }
   else
   {	
      if(f.GetLength()==0)
      {
         f.Close();
         return false;
      }


      unsigned long UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
      unsigned long WeldHeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
      unsigned long TotalValidHeaderSize = WeldHeaderSize + 2*UnitObjectSize + sizeof(char) ;
      int  size= sizeof(CHistoryData);
      unsigned long ObjectSize = sizeof(int) + sizeof(bool) + 3*sizeof(char) + size;
      f.SeekToBegin();

      unsigned int NoOfBytesRead=0;

      HistoryObj = new CWeldingHistory();
      HistoryObj->TotalCycle=0;
      if(HistoryObj->Parameter_ID != 0) {
         delete [](HistoryObj->Parameter_ID);
         HistoryObj->Parameter_ID = NULL;
      }


      CHistoryData* object = NULL;

      bool USBMetric;
      UINT32 TotalObjectCount,/*TotalHeaderCount*/WriteObjectIndex;
      char Comma;	
      if(NoOfBytesRead!=f.GetLength())
      {
         int ID;

         NoOfBytesRead+=f.Read(&TotalObjectCount,sizeof(UINT32));
         NoOfBytesRead+=f.Read(&Comma,sizeof(char));
         NoOfBytesRead+=f.Read(&WriteObjectIndex,sizeof(UINT32));
         NoOfBytesRead+=f.Read(&Comma,sizeof(char));
         NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);
         NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);
         NoOfBytesRead+=f.Read(&Comma,sizeof(char));

         //StartingPoint = StartingPoint - Count;
         f.Seek((StartingPoint)*(LONGLONG)ObjectSize + TotalValidHeaderSize,CFile::begin);

         while((Count--) && (NoOfBytesRead!=f.GetLength() && !EstopPressedFlag ))
         {
            object =new CHistoryData();
            NoOfBytesRead+=f.Read(&ID,sizeof(int));
            NoOfBytesRead+=f.Read(&Comma,sizeof(char));
            NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

            NoOfBytesRead+=f.Read(&Comma,sizeof(char));
            NoOfBytesRead+=f.Read(object,size);
            NoOfBytesRead+=f.Read(&Comma,sizeof(char));
            object->Units=USBMetric;
            object->UniqueId=ID;

            HistoryObj->LOGWeldHistoryList.AddTail(object);
            HistoryObj->TotalCycle++;
         }
      }
	  if(object)
	  {
		  HistoryObj->TotalColoumn=object->TotalColoumn;
		  HistoryObj->Units = object->Units;
	  }
      if(HistoryObj->Parameter_ID != NULL)
      {
         delete[] HistoryObj->Parameter_ID;
         HistoryObj->Parameter_ID = NULL;
      }
	  if(object)//Coverity 12390
	  {
		HistoryObj->Parameter_ID=new int[object->TotalColoumn];
		for(int param=0;param<object->TotalColoumn;param++)//Storing parameters ID.
		{
			 HistoryObj->Parameter_ID[param]=object->USBParamIDs[param];
		}
	  }
      f.Close();


      PdfPageCount = DrawLOGWeldData(&page,&pdf,&def_font,UnitFlag); 
	  delete HistoryObj;
   }
   
   if(PdfPageCount)
      PdfPageCount = PageCount;
   if(PageCount >= MAX_WELD_PDF_PAGES)
      PageCount = 1;
   return PdfPageCount;
}

bool CWeldingHistory::DrawLOGWeldData(HPDF_Page * page,HPDF_Doc  * pdf,HPDF_Font *def_font,bool UnitFlag)
{
   bool PDFCreateStatus = true;
   int  size= sizeof(CHistoryData);
   CHistoryData *object = NULL;
   CString ParamValue = "";
   POSITION pos;
   int XCord=PRINTWELDSTARTXCORD ; 
   char STR[256];
   int CheckUnit;
   static int LastCheckUnit = 0;
   static bool DrawPresetString = true;
   static bool DrawPresetRev = true;
   static bool DrawPresetNo = true;
   static bool DrawUserId = true;
   static bool DrawAmpA = true;
   static bool DrawAmpB = true;
   static bool DrawTrigger = true;
   static bool DrawActuatorAssm = true;
   static bool DrawPowerSupply = true;
   static bool DrawStackAssm = true;
   static bool DrawPwrSupSr = true;
   static bool DrawActSr = true;
   static bool DrawValidStr = true;
   static bool DrawPressureA = true;
   static bool DrawPressureB = true;
   CString ValidStr = "";
   static CString LastMode = "";
   CString	FirstMode = "";
   int AlarmCount = 0;
   CString FirstUserId = "";
   static CString LastuserId = "";
   CString FirstPresetno = "";
   static CString LastPresetno = "";
   CString FirstRev = "";
   CString FirstAmpA = "";
   CString FirstAmpB = "";
   CString FirstTrigger = "";
   CString FirstActuatorassm = "";
   CString FirstPowerSupply = "";
   CString FirstStackassm = "";
   CString FirstValidStr = "";
   CString FirstPressureA = "";
   CString FirstPressureB = "";
   static CString LastRev = "";
   static CString LastAmpA = "";
   static CString LastAmpB = "";
   static CString LastTrigger = "";
   static CString LastActuatorassm = "";
   static CString LastPowerSupply = "";
   static CString LastStackassm = "";
   static CString LastPwrSupSr = "";
   static CString LastActSr = "";
   static CString LastValidStr = "";
   static CString LastPressureA = "";
   static CString LastPressureB = "";

   CString WeldHistoryStr =  CVgaMenuItem ::LinearSearch(XSTR(WELDHISTORY_STRINGID));	

   pos = HistoryObj->LOGWeldHistoryList.GetHeadPosition();
   for(int i = 1; i <= HistoryObj->LOGWeldHistoryList.GetCount() && PDFCreateStatus  && (!EstopPressedFlag);i++)
   {
      object = HistoryObj->LOGWeldHistoryList.GetNext(pos);


      FirstRev = object->USBAllParamValues[4];
      if(FirstRev.Compare(LastRev))
         DrawPresetRev = true;
      else
         DrawPresetRev = false; 
      LastRev = object->USBAllParamValues[4];

      FirstUserId = object->USBAllParamValues[1];
      if(FirstUserId.Compare(LastuserId))
         DrawUserId = true;
      else
         DrawUserId = false; 
      LastuserId = object->USBAllParamValues[1];

      FirstPresetno = object->USBAllParamValues[3];
      if(FirstPresetno.Compare(LastPresetno))
         DrawPresetNo = true;
      else
         DrawPresetNo = false; 
      LastPresetno = object->USBAllParamValues[3];

      FirstAmpA = object->USBAllParamValues[18];
      if(FirstAmpA.Compare(LastAmpA))
         DrawAmpA = true;
      else
         DrawAmpA = false; 
      LastAmpA = object->USBAllParamValues[18];

      FirstAmpB = object->USBAllParamValues[19];
      if(FirstAmpB.Compare(LastAmpB))
         DrawAmpB = true;
      else
         DrawAmpB = false; 
      LastAmpB = object->USBAllParamValues[19];

      FirstTrigger = object->USBAllParamValues[31];
      if(FirstTrigger.Compare(LastTrigger))
         DrawTrigger = true;
      else
         DrawTrigger = false; 
      LastTrigger = object->USBAllParamValues[31];

      FirstActuatorassm = object->USBAllParamValues[6];
      if(FirstActuatorassm.Compare(LastActuatorassm))
         DrawActuatorAssm = true;
      else
         DrawActuatorAssm = false; 
      LastActuatorassm = object->USBAllParamValues[6];

      FirstPowerSupply = object->USBAllParamValues[7];
      if(FirstPowerSupply.Compare(LastPowerSupply))
         DrawPowerSupply = true;
      else
         DrawPowerSupply = false; 
      LastPowerSupply = object->USBAllParamValues[7];

      FirstStackassm = object->USBAllParamValues[8];
      if(FirstStackassm.Compare(LastStackassm))
         DrawStackAssm = true;
      else
         DrawStackAssm = false; 
      LastStackassm = object->USBAllParamValues[8];

      if(object->USBAllParamValues[32] != LastPwrSupSr)
		  DrawPwrSupSr = true;
	  else 
		  DrawPwrSupSr = false;
	  LastPwrSupSr = object->USBAllParamValues[32]; 

	  if(object->USBAllParamValues[33] != LastActSr)
		  DrawActSr = true;
	  else
		  DrawActSr = false;
	  LastActSr = object->USBAllParamValues[33];
	  
	  CString str = object->USBAllParamValues[5];
	  if(str != "Yes")
		  ValidStr = ValidatedStr;
	  else 
		  ValidStr = NonValidatedStr;

	  if(ValidStr != LastValidStr)
		  DrawValidStr = true;
	  else
		  DrawValidStr = false;
	  LastValidStr = ValidStr;

	  FirstPressureA = object->USBAllParamValues[20];
      if(FirstPressureA.Compare(LastPressureA))
         DrawPressureA = true;
      else
         DrawPressureA = false; 
      LastPressureA = object->USBAllParamValues[20];

	   FirstPressureB = object->USBAllParamValues[21];
      if(FirstPressureB.Compare(LastPressureB))
         DrawPressureB = true;
      else
         DrawPressureB = false; 
      LastPressureB = object->USBAllParamValues[21];

      if(DrawPresetRev || DrawUserId|| DrawPresetNo|| DrawAmpA || DrawAmpB || DrawTrigger || 
		 DrawActuatorAssm|| DrawPowerSupply || DrawStackAssm || DrawValidStr || DrawPwrSupSr || DrawActSr || DrawPressureA || DrawPressureB)
      { 
         UnitHeadingPos = true;
         DrawPresetRev = false;
         DrawUserId = false;
         DrawPresetNo = false;
         DrawAmpA = false;
         DrawAmpB = false;
         DrawActuatorAssm = false;
         DrawTrigger = false;
         DrawPowerSupply = false;
         DrawStackAssm = false;
		 DrawPwrSupSr = false;
		 DrawActSr = false;
		 DrawValidStr = false;
		 DrawPressureA = false;
		 DrawPressureB = false;
         DrawHeading(object,page,object->Units,pdf,def_font);

         if(i>1)
            YCoordinate += FOURWELDLINEGAP;

      }

      HistoryObj->Units = object->Units;

      if(UnitFlag == true) // print the header
      {
         LastCheckUnit = !object->Units;
         UnitFlag = false;
      }
      CheckUnit = object->Units;
      if((YCoordinate > (HPDF_Page_GetHeight(*page)- TWOWELDLINEGAP)))
      {

         HPDF_Page_SetLineWidth (*page,2);
         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
         if(PageCount>=MAX_WELD_PDF_PAGES)
         {
            PDFCreateStatus = CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
            PageCount = 1;


         }
         else
         {
            *page = HPDF_AddPage (*pdf);
            HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
            PdfWithImage(pdf,page,def_font);
            HPDF_Page_SetFontAndSize (*page, *def_font,25);
            CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
            CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
            HPDF_Page_SetFontAndSize (*page, *def_font,7);
            PageCount++;
            if(i>1)
               UnitHeadingPos = false;

         }

         XCord=PRINTWELDSTARTXCORD;
         YCoordinate =FOURWELDLINEGAP;
         if((CheckUnit==LastCheckUnit))
         {
            DrawLOGParameterHeading(HistoryObj->Units,page);
            YCoordinate+=FOURWELDLINEGAP;
         }
         HPDF_Page_SetLineWidth (*page,2);
         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
         if(i>1)
            UnitHeadingPos = false;
      }
      if((CheckUnit!=LastCheckUnit) )
      {

         if((YCoordinate + FIVEWELDLINEGAP) >=  HPDF_Page_GetHeight(*page))
         { 
            if(PageCount >= MAX_WELD_PDF_PAGES)
            {
               PDFCreateStatus = CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
               PageCount = 1;
            }
            else
            {
               *page = HPDF_AddPage (*pdf);
               HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
               PdfWithImage(pdf,page,def_font);
               HPDF_Page_SetFontAndSize (*page, *def_font,25);
               CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
               CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
               HPDF_Page_SetFontAndSize (*page, *def_font,7);
               XCord=PRINTWELDSTARTXCORD;
               YCoordinate =FOURWELDLINEGAP; //FOURWELDLINEGAP
               PageCount++;
               if(i>1)
                  UnitHeadingPos = false;

            }

         }

         if(i>1)
            UnitHeadingPos = false;
         DrawLOGParameterHeading(HistoryObj->Units,page);
         if(UnitHeadingPos)
         {
            UnitHeadingPos = false;
            YCoordinate+=SEVENWELDLINEGAP;//FOURWELDLINEGAP
         }
         else
            YCoordinate+=FOURWELDLINEGAP;

      }
      LastCheckUnit =	object->Units;
      FirstMode= object->USBMode_PresetString;
      if(FirstMode.Compare(LastMode))
         DrawPresetString = true;
      else
         DrawPresetString = false; 
      LastMode = object->USBMode_PresetString;

      if(DrawPresetString)
      {
         DrawPresetString=false;
         sprintf(STR,"%S",object->USBMode_PresetString);
         CChildView::DrawPDFText(page,XCord,YCoordinate,STR);
         YCoordinate += ONEWELDLINEGAP;
      }

      if((YCoordinate > (HPDF_Page_GetHeight(*page)- TWOWELDLINEGAP)))
      {

         HPDF_Page_SetLineWidth (*page,2);
         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
         if(PageCount>=MAX_WELD_PDF_PAGES)
         {
            PDFCreateStatus = CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
            PageCount = 1;
         }
         else
         {
            *page = HPDF_AddPage (*pdf);
            HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
            PdfWithImage(pdf,page,def_font);
            HPDF_Page_SetFontAndSize (*page, *def_font,25);
            CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
            CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
            HPDF_Page_SetFontAndSize (*page, *def_font,7);
            PageCount++;
            if(i>1)
               UnitHeadingPos = false;
         }

         XCord=PRINTWELDSTARTXCORD;
         YCoordinate =FOURWELDLINEGAP;
         DrawLOGParameterHeading(HistoryObj->Units,page);
         YCoordinate+=FOURWELDLINEGAP;
         HPDF_Page_SetLineWidth (*page,2);
         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
      }

      ParamValue =object->USBAllParamValues[0];

      sprintf(STR,"%s",ParamValue);
      if(object->TextColour == Red)
         HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
      CChildView::DrawPDFText(page,XCord,YCoordinate,STR); 

      XCord+=TWOWELDLINEGAP; 


      CString time = object->USBTimeStr;
      sprintf(STR,"%s",time);
      if(object->TextColour == Red)
         HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
      CChildView::DrawPDFText(page,XCord,YCoordinate,STR);  

      XCord+=TWOWELDLINEGAP; 

      CString date = object->USBDateStr;
      sprintf(STR,"%s",date);
      if(object->TextColour == Red)
         HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
      CChildView::DrawPDFText(page,XCord,YCoordinate,STR); 

      XCord+=CChildView::thisPtr->PDFParamWidth[0]; 
      for(int k = 1;k < 19;k++){
         for(int j = 1;j<HistoryObj->TotalColoumn;j++) 
         {
            if(Heading_Specific[k] == j){
               ParamValue =object->USBAllParamValues[j];
               if(ParamValue.Find(_T("---"))>=0)
                  ParamValue = NotApplicable;
               sprintf(STR,"%s",ParamValue);
               if(object->TextColour == Red)
                  HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
               CChildView::DrawPDFText(page,XCord,YCoordinate,STR); 
               HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);
               XCord+=CChildView::thisPtr->PDFParamWidth[j];
            }
         }
      }

      if(object->TextColour == Red) 
         AlarmCount=HistoryAlarm(i,object->USBAllParamValues[0],pdf,page,def_font,object);

      XCord=PRINTWELDSTARTXCORD;
	  YCoordinate +=ONEWELDLINEGAP;
   
      AlarmCount = 0;

      if((YCoordinate > (HPDF_Page_GetHeight(*page)- TWOWELDLINEGAP)) && !(i == HistoryObj->LOGWeldHistoryList.GetCount()) )
      {
         HPDF_Page_SetLineWidth (*page,2);

         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
         if(PageCount >= MAX_WELD_PDF_PAGES)
         {
            PDFCreateStatus = CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
            PageCount = 1;
         }
         else
         {
            *page = HPDF_AddPage (*pdf);
            HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
            PdfWithImage(pdf,page,def_font);
            HPDF_Page_SetFontAndSize (*page, *def_font,25);
            CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
            CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
            HPDF_Page_SetFontAndSize (*page, *def_font,7);
            XCord=PRINTWELDSTARTXCORD;
            YCoordinate =FOURWELDLINEGAP;
            PageCount++;
            if(i>1)
               UnitHeadingPos = false;
         }
         UnitFlag = true;
         HPDF_Page_SetLineWidth (*page,2);
         HPDF_Page_MoveTo (*page, 2,10);
         HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
         HPDF_Page_Stroke (*page);
      }
      PDFCreateStatus = CChildView::thisPtr->USBPresent();
   }
   return PDFCreateStatus;
}

void CWeldingHistory::DrawHeading(CHistoryData* object,HPDF_Page * page,int Unit,HPDF_Doc  * pdf,HPDF_Font *def_font) 
{
   
   CString Validted=_T("") ,NonValidated = _T("");
   WeldTemp_pos = NULL;
   WeldTemp_pos = tempWeldList.GetHeadPosition();
   tempWeldList.GetNext(WeldTemp_pos);
   Time = tempWeldList.GetNext(WeldTemp_pos);
   Date = tempWeldList.GetNext(WeldTemp_pos);
   tempWeldList.GetNext(WeldTemp_pos);
   tempWeldList.GetNext(WeldTemp_pos);
   Validted = tempWeldList.GetNext(WeldTemp_pos);
   NonValidated =tempWeldList.GetNext(WeldTemp_pos); 
   CString AmpAValue = _T(""),AmpBValue = _T(""),TrigForceValue = _T("");
   CString PressureAValue = _T(""),PressureBValue = _T("");
   char UnicodeStr[1024];
   int XCord=PRINTWELDSTARTXCORD ;
   bool found = false;
   CString HeadingStr =_T("");
   CString UnitStrAmpA = _T(""),UnitStrAmpB = _T(""),UnitStrTrigForce  =_T("");
   CString UnitStrPressureA = _T(""),UnitStrPressureB = _T("");
   CString ValidStr = _T("");

   CString WeldHistoryStr =  CVgaMenuItem ::LinearSearch(XSTR(WELDHISTORY_STRINGID));
   if((YCoordinate + FOURWELDLINEGAP) >=  HPDF_Page_GetHeight(*page))
   { 
      if(PageCount >= MAX_WELD_PDF_PAGES)
      {
         CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
         PageCount = 1;
      }
      else
      {
         *page = HPDF_AddPage (*pdf);
         HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
         PdfWithImage(pdf,page,def_font);
         HPDF_Page_SetFontAndSize (*page, *def_font,25);
         CChildView::thisPtr->CStringToUTF(WeldHistoryStr,UnicodeStr);
         CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,UnicodeStr);
         HPDF_Page_SetFontAndSize (*page, *def_font,7);
         XCord=PRINTWELDSTARTXCORD;
         YCoordinate =FOURWELDLINEGAP; 
         PageCount++;
      }
      found = true;
   }
   memset (Heading_Str, 0, 256);

   HPDF_Page_SetRGBFill(*page, 0.75, 0.75, 0.75);

   HPDF_Page_SetLineWidth (*page,2);
   HPDF_Page_Rectangle(*page, 2,HPDF_Page_GetHeight(*page)-YCoordinate-THREEWELDLINEGAP, HPDF_Page_GetWidth(*page)-450, HEADERHEIGHT);
   HPDF_Page_FillStroke(*page);
   HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);

   sprintf(UnicodeStr,"%S",object->USBAllParamValues[5]);
   if(!strcmp(UnicodeStr,"Yes"))
      ValidStr = Validted;
   else 
      ValidStr = NonValidated;

   HeadingStr.Format(_T("%s,%s,%s:%s,%s,%s,%s"),UserIdStrHdr,PresetStrHdr,PresetRevStrHdr,object->USBAllParamValues[1],object->USBAllParamValues[3],object->USBAllParamValues[4],ValidStr);
   CChildView::thisPtr->CStringToUTF(HeadingStr,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate,UnicodeStr);  

   AmpAValue  =object->USBAllParamValues[18];
   if(AmpAValue.Find(_T("---"))>=0)
      AmpAValue = NotApplicable;
   AmpBValue  =object->USBAllParamValues[19];
   if(AmpBValue.Find(_T("---"))>=0)
      AmpBValue = NotApplicable;
   TrigForceValue  =object->USBAllParamValues[31];
   if(TrigForceValue.Find(_T("---"))>=0)
      TrigForceValue = NotApplicable;
   PressureAValue  =object->USBAllParamValues[20];
   if(PressureAValue.Find(_T("---"))>=0)
      PressureAValue = NotApplicable;
   PressureBValue  =object->USBAllParamValues[21];
   if(PressureBValue.Find(_T("---"))>=0)
      PressureBValue = NotApplicable;

   if(Unit){
      UnitStrAmpA = *(CWeldingHistory::ParameterUnitMetric+18);
      UnitStrAmpB = *(CWeldingHistory::ParameterUnitMetric+19);
      UnitStrTrigForce = *(CWeldingHistory::ParameterUnitMetric+31);
	  UnitStrPressureA = *(CWeldingHistory::ParameterUnitMetric+20);
	  UnitStrPressureB = *(CWeldingHistory::ParameterUnitMetric+21);
   }
   else{
      UnitStrAmpA = *(CWeldingHistory::ParameterUnitUSCS+18);
      UnitStrAmpB = *(CWeldingHistory::ParameterUnitUSCS+19);
      UnitStrTrigForce = *(CWeldingHistory::ParameterUnitUSCS+31);
	  UnitStrPressureA = *(CWeldingHistory::ParameterUnitUSCS+20);
	  UnitStrPressureB = *(CWeldingHistory::ParameterUnitUSCS+21);
   } 

   HeadingStr.Format(_T("%s=%s%s,%s=%s%s,%s=%s%s,%s=%s%s,%s=%s%s"),SetAmpAStrHdr,AmpAValue,UnitStrAmpA,SetAmpBStrHdr,AmpBValue,UnitStrAmpB,PressureAStrHdr,PressureAValue,UnitStrPressureA,PressureBStrHdr,PressureBValue,UnitStrPressureB,TriggerForceStrHdr,TrigForceValue,UnitStrTrigForce);
   CChildView::thisPtr->CStringToUTF(HeadingStr,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP,UnicodeStr);

   HeadingStr.Format(_T("%s,%s,%s:%s,%s,%s"),ActAssmNoStrHdr,PsAssmNoStrHdr,StackAssmNoStrHdr,object->USBAllParamValues[6],object->USBAllParamValues[7],object->USBAllParamValues[8]);
   CChildView::thisPtr->CStringToUTF(HeadingStr,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+ONEHEADINGGAP,UnicodeStr);
   
   CString actstr = object->USBAllParamValues[33];
   if( actstr.Compare(_T("")) == 0)
		actstr = NotApplicable;
   

   HeadingStr.Format(_T("%s,%s:%s,%s"),PsSerialNoStrHdr,ActSerialNoStrHdr,object->USBAllParamValues[32],actstr);
   CChildView::thisPtr->CStringToUTF(HeadingStr,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+TWOHEADINGGAP,UnicodeStr);

   if(found)
   {
      found = false;
      DrawLOGParameterHeading(Unit,page);
      YCoordinate+=FOURWELDLINEGAP;
   }
}

void CWeldingHistory::DrawLOGParameterHeading(int Unit,HPDF_Page * page) 
{
   CString ParameterString1;
   CString ParameterString2;
   CString Str;

   int XCord=PRINTWELDSTARTXCORD ;
   int Unit_Heading_Gap = 0;
   CString TimeString,DateString;
   HistoryTemp_pos = NULL;
   HistoryTemp_pos = tempHistoryList.GetHeadPosition();
   tempHistoryList.GetNext(HistoryTemp_pos);
   tempHistoryList.GetNext(HistoryTemp_pos);
   TimeString = tempHistoryList.GetNext(HistoryTemp_pos);
   DateString = tempHistoryList.GetNext(HistoryTemp_pos);
   char UnicodeStr[8192];

   HPDF_Page_SetRGBFill(*page, 0.75, 0.75, 0.75);

   HPDF_Page_SetLineWidth (*page,2);

   if(UnitHeadingPos)
   {
      HPDF_Page_Rectangle(*page, 2,HPDF_Page_GetHeight(*page)-YCoordinate-140, HPDF_Page_GetWidth(*page)-10, THREEWELDLINEGAP); 
      Unit_Heading_Gap = UNITHEADINGGAP;
   }
   else
   {
      HPDF_Page_Rectangle(*page, 2,HPDF_Page_GetHeight(*page)-YCoordinate-THREEWELDLINEGAP, HPDF_Page_GetWidth(*page)-10, HEADERHEIGHT);
      Unit_Heading_Gap = 0;
   }
   HPDF_Page_FillStroke(*page);
   HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);

   Str = *(CChildView::Parameter_Heading);
   ParameterString1 = Str.SpanExcluding(_T(" "));
   ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));



   CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+Unit_Heading_Gap,UnicodeStr);


   CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+ONEHEADINGGAP+Unit_Heading_Gap,UnicodeStr); 
   XCord+=TWOWELDLINEGAP; 

   CChildView::thisPtr->CStringToUTF(TimeString,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+ONEHEADINGGAP+Unit_Heading_Gap,UnicodeStr); 
   XCord+=TWOWELDLINEGAP; 

   CChildView::thisPtr->CStringToUTF(DateString,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+ONEHEADINGGAP+Unit_Heading_Gap,UnicodeStr); 	

   if(Unit)
      CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+TWOHEADINGGAP+Unit_Heading_Gap,"(d/m/y)"); 	
   else	
      CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+TWOHEADINGGAP+Unit_Heading_Gap,"(m/d/y)");

   XCord+=CChildView::thisPtr->PDFParamWidth[0]; 

   for(int k = 1;k < 19;k++){
      for(int locCount = 0 ; locCount <	CChildView::TotalTextHeading; locCount++)
      {
         if(Heading_Specific[k] == locCount){
            CString Str = (CChildView::Parameter_Heading[locCount]);
            CString ParameterString1 = Str.SpanExcluding(_T(" "));
            CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
            CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
            CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+Unit_Heading_Gap,UnicodeStr);  
            CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
            CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+ONEHEADINGGAP+Unit_Heading_Gap,UnicodeStr); 
            if(Unit)
            {
               CChildView::thisPtr->CStringToUTF(*(CWeldingHistory::ParameterUnitMetric+locCount),UnicodeStr);
               CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+TWOHEADINGGAP+Unit_Heading_Gap,UnicodeStr); 
            }
            else
            {
               CChildView::thisPtr->CStringToUTF(*(CWeldingHistory::ParameterUnitUSCS+locCount),UnicodeStr);
               CChildView::DrawPDFText(page,XCord,YCoordinate+ONEWELDLINEGAP+TWOHEADINGGAP+Unit_Heading_Gap,UnicodeStr);
            }
            XCord+=CChildView::thisPtr->PDFParamWidth[locCount];
            break;
         }
      }
   }
}

int CWeldingHistory::HistoryAlarm(int i,CString CycleNumString,HPDF_Doc  * pdf,HPDF_Page * page,HPDF_Font *def_font,CHistoryData *object)
   /*---------------------------------------------------------*
   * There are alarm variables which code different errors.  *
   * The error messages are printed and the number of errors *
   * printed are returned                                    *
   *														   *
   * OUT: number of error messages printed                   *
   *---------------------------------------------------------*/
{
   int UIAlarms = 0;
   int temp =0;
   temp=HistoryAlarmPDF((object->AlarmString[0]), NCALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[1]), OLALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[2]), EQALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[3]), CMALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[4]), CAALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[5]), WAALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp= HistoryAlarmPDF((object->AlarmString[6]), PRALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   temp=HistoryAlarmPDF((object->AlarmString[7]), PSALARM,CycleNumString,pdf,page,def_font);
   UIAlarms +=temp;
   return(UIAlarms);
}

int CWeldingHistory::HistoryAlarmPDF(int  UIAlarmField, int IOffset,CString CycleNumString,HPDF_Doc  * pdf,HPDF_Page * page,HPDF_Font *def_font)
   /*-------------------------------------------------------------------*
   * subroutine for printing error messages. the error variables is    *
   * checked bitwise and the appropriate error message is printed.     *
   * IN:    UIAlarmField, the error cell, bitwise coded                *
   *     IOffset, the index offset for the different kinds of messages *
   * OUT: number of alarms printed                                     *
   *-------------------------------------------------------------------*/
{  
   bool PDFCreateStatus = true;
   int  UIBit;
   int count;
   int UIAlarms = 0;
   char UnicodeStr[1028];
   static CString WarningNote,Alarms;
   CString WeldHistoryStr =  CVgaMenuItem ::LinearSearch(XSTR(WELDHISTORY_STRINGID));
   if(UIAlarmField)
   {
      HistoryTemp_pos = NULL;
      HistoryTemp_pos = tempHistoryList.GetHeadPosition();
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      tempHistoryList.GetNext(HistoryTemp_pos);
      WarningNote= tempHistoryList.GetNext(HistoryTemp_pos);
      Alarms= tempHistoryList.GetNext(HistoryTemp_pos);
      /*--  There's an alarm--*/ 
      UIBit = 2;
      /*--  find Alarm and print messages --*/ 
      /*--  check bits 1 thru 27, bit 0 and last 4 bits of each word is reserved --*/ 
      for(count = 1; count <= 27 && PDFCreateStatus; count++)
      {
         if(UIAlarmField & UIBit)
         {
            /*--  Alarm message --*/
            CString Alarm1=" ";
            if(IOffset == WAALARM)
               Alarm1 = (WarningNote/*[Lang_Index] */);
            else
               Alarm1 = (Alarms);

            Alarm1 +=("   " + CChildView::thisPtr->AlarmEng[IOffset + count]);
            int XCord=PRINTWELDSTARTXCORD;
            if((YCoordinate > (HPDF_Page_GetHeight(*page)- TWOWELDLINEGAP))) 
            {
               HPDF_Page_SetLineWidth (*page,2);

               HPDF_Page_MoveTo (*page, 2,10);
               HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
               HPDF_Page_Stroke (*page);
               if(PageCount >= MAX_WELD_PDF_PAGES)
               {
                  PDFCreateStatus = CChildView::thisPtr->CreateNewPDFDoc(page,pdf,def_font);
                  PageCount = 1;
               }
               else
               {
                  *page = HPDF_AddPage (*pdf);
                  HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
                  PdfWithImage(pdf,page,def_font);
                  HPDF_Page_SetFontAndSize (*page, *def_font,25);
                  CChildView::thisPtr->CStringToUTF(WeldHistoryStr,UnicodeStr);
                  CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,UnicodeStr);
                  HPDF_Page_SetFontAndSize (*page, *def_font,7);
                  XCord=PRINTWELDSTARTXCORD;
				  YCoordinate = FOURWELDLINEGAP;
                  PageCount++;
               }

               XCord=PRINTWELDSTARTXCORD;
               YCoordinate = FOURWELDLINEGAP;
               DrawLOGParameterHeading(HistoryObj->Units,page);

			   YCoordinate+=FOURWELDLINEGAP;
               HPDF_Page_SetLineWidth (*page,2);
               HPDF_Page_MoveTo (*page, 2,10);
               HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-1, 10) ;
               HPDF_Page_Stroke (*page);
            }
            sprintf(UnicodeStr,"%s",CycleNumString);
            HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
            YCoordinate+=ONEWELDLINEGAP;
            CChildView::DrawPDFText(page,XCord,YCoordinate,UnicodeStr);
            CChildView::thisPtr->CStringToUTF(Alarm1,UnicodeStr);
            HPDF_Page_SetRGBFill(*page, 1.0, 0.0, 0.0);
            CChildView::DrawPDFText(page,XCord+WELDHISTORYPARAMWIDTH,YCoordinate,UnicodeStr);
            UIAlarms++;
         }
         UIBit <<= 1;
      }
   }
   return UIAlarms;
}

