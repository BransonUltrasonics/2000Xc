/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/EventLog.cpp_v   1.25   13 Mar 2015 06:34:46   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/EventLog.cpp_v  $
 * 
 *    Rev 1.25   13 Mar 2015 06:34:46   amaurya
 * Issue fixed for coverty issue 12552.
 * 
 *    Rev 1.24   11 Mar 2015 09:27:24   amaurya
 *  GetNameFromID() prototype changed.
 * 
 *    Rev 1.23   30 Jan 2015 08:13:52   amaurya
 * CreateEventPDF() changed to display changed parameter name along with event description.
 * 
 *    Rev 1.22   06 Jan 2015 05:12:30   AnPawar
 * stop saving pdf is estop is pressed
 * 
 *    Rev 1.21   05 Jan 2015 05:31:24   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.20   28 Nov 2014 08:30:48   rjamloki
 * CEventLog::EventHistoryUniversalCountint CEventLog::EventHistoryRamCount global variables added to keep TotalEventCount in hidden files and Coverity fix
 * 
 *    Rev 1.19   14 Nov 2014 10:40:34   AnPawar
 * CreateEventPDF() function changed for multi language support.
 * 
 *    Rev 1.19   14 Nov 2014 02:53:40   rjamloki
 * CreateEventPDF() changed.
* 
*    Rev 1.18   10 Nov 2014 02:49:28   rjamloki
* JsonEvent_Desc[] removed.CreateEventPDF() and DrawEventParameterHeading() changed for Multilanguage PDF Support.
* 
*    Rev 1.17   20 Oct 2014 05:43:54   RJamloki
*  DrawEventParameterHeading function changed to correct date heading.
* 
*    Rev 1.16   06 Oct 2014 03:24:06   rjamloki
*  modified parameters of JsonEvent_Desc[] and JsonParam_Desc[] arrays
* 
*    Rev 1.15   01 Oct 2014 10:48:56   AnPawar
* CreateEventPDF() function changed.Added ID array and string array for web services.
* 
*    Rev 1.14   25 Sep 2014 12:06:58   AnPawar
* CreateEventPDF() function changed for invalid event and parameter id handling. 
* 
*    Rev 1.12   11 Sep 2014 09:45:20   rjamloki
* CreateEventPDF() function modified for event reason and description.
* 
*    Rev 1.11   05 Sep 2014 06:59:10   amaurya
* Corrected the list traverse in DrawEventData().
* 
*    Rev 1.10   28 Jul 2014 13:55:06   rjamloki
* CEventLog::CreateEventPDF() modefied to handle usb exception.
* 
*    Rev 1.9   22 Jul 2014 08:21:20   akaushal
* Changes for VGA file path .
* 
*    Rev 1.8   09 Jul 2014 06:53:50   akaushal
* Function PrepareEventListForPDF(),CreateEventPDF(),
* DrawEventParameterHeading() changed.
* 
*    Rev 1.7   09 Jun 2014 11:43:50   rjamloki
* Variable initialization in constructor.Changes for Time and Date format in PDF.
* 
*    Rev 1.6   27 May 2014 06:30:22   amaurya
* Modified PDF function to save Oldest to Latest events.
* 
*    Rev 1.5   20 May 2014 10:57:24   rjamloki
* CreateEventPDF() function changed. 
* 
*    Rev 1.4   07 May 2014 13:07:04   akaushal
* Code cleanup 
* 
*    Rev 1.3   21 Apr 2014 13:36:48   akaushal
* Function added to make PDF and draw heading.Unused UpdateEventData() removed.  
* 
*    Rev 1.2   28 Mar 2014 14:33:00   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.1     05 Mar 2014 14:13:18 rjamloki    
* Screens and PDF working
*
*    Rev 1.0     26 Feb 2014 02:18:18 jerryw.wang     
* Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "EventLog.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include "hpdf.h"
#include "zlib.h"
#include "png.h"
#include "VGA.h"


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

int CEventLog::TopMostData;
int CEventLog::SelectedEventData;
int CEventLog::LeftMostParameter;
int CEventLog::EventHistoryglobalCount;
int CEventLog::EventHistoryUniversalCount;
int CEventLog::EventHistoryRamCount;
bool CEventLog::EventHistoryFullFlag;
int CEventLog::TotalCycles;
int CEventLog::SuccessfullyWrittenEventRecord;
int CEventLog::CurrentDisplayEventCount;

extern CString EventDataFileName;
extern CString PrepareDescription(int ParamID,int EventID,CString Data,bool JsonReq);
extern CString GetNameFromID(int ParamID,bool InEnglish = false);


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventLog * CEventLog::thisHisPtr;

CEventLog::CEventLog(CXmlElement * e)
{
   Parameter_ID = 0;
   TotalColoumn = 0;
   TotalCycle = 0;
   UpButtonPressed = false;
   DownButtonPressed = false;
   LeftButtonPressed = false;
   RightButtonPressed = false;
   ScreenUpButtonPressed = false;
   ScreenDownButtonPresssed = false;
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
   CEventLog::LeftMostParameter=1;
}

CEventLog::CEventLog()
{
   Parameter_ID = 0;
   TotalColoumn = 0;
   TotalCycle = 0;
   UpButtonPressed = false;
   DownButtonPressed = false;
   LeftButtonPressed = false;
   RightButtonPressed = false;
   ScreenUpButtonPressed = false;
   ScreenDownButtonPresssed = false;
   GraphsButtonPressed = false;
   ExitButtonPressed = false;
   lang_index = 0;
}

CEventLog::~CEventLog()
{
   if(Parameter_ID != NULL){
      delete Parameter_ID;;
      Parameter_ID = NULL;
   }

}

/****************************************************************************************/
/*  This function draws the Event-Log screen.										*/
/*  the function checks if the button is pressed or not, if found then draws it in      */
/*  pressed state.																		*/
/*																						*/
/****************************************************************************************/
void CEventLog::Draw(CDC *pDC)
{
   DrawEventData(pDC);
}

/**********************************************************************************************/
/* this function handles the mouse click if it is on the Event-Log screen.                  */
/* the function is called on both LButton up and LButton down .								  */
/*																							  */
/**********************************************************************************************/
bool CEventLog::MouseClick(const CPoint &p, CChildView *view)
{
   return true;
}

/****************************************************************************************/
/*																						*/
/* The following function is used to Draw Event data. The function checks the Top most	*/
/* Data and the Left Most PArameter on the screen and displays next eight Event data		*/
/* from the Top most Event data.															*/
/****************************************************************************************/
void CEventLog::DrawEventData(CDC *pDC)
{
   int LineNo=1;
   int TotalCyclesDrawn=0;
   if(EventLogList.GetCount())
   {
      POSITION pos = EventLogList.GetHeadPosition();
      for(int CurrentPos = 1 ; (CurrentPos < TopMostData) && pos ; CurrentPos++)
         EventLogList.GetNext(pos);
      DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(LINE_GAP*(SelectedEventData+3)),
         (HISTORY_TBL_START_X + 5 * ParamRect_Width + 12),
         (LINE_GAP*(SelectedEventData+4))));
      while(pos)
      {
         if(TotalCyclesDrawn==EventLogMaxCyclePerScreen)
            break;
         CEventHistoryData * Obj = EventLogList.GetNext(pos);
         Obj->DrawHistoryData(pDC,LeftMostParameter, LineNo);
         TotalCyclesDrawn++;
         LineNo++;
      }
   }
   DrawParameterHeadings(pDC);
}

/*********************************************************************************************/
/* The following function is used to draw parameter headings on the Event Log screen.	     */
/* The function checks for the unit of the selected event data and draws the unit accordingly*/
/*																							 */
/*********************************************************************************************/
void CEventLog::DrawParameterHeadings(CDC *pDC)
{
   if(LeftMostParameter>(TotalColoumn-4))
      LeftMostParameter=1;

   int X1 = 20;
   int Y1 =60;
   int Width =120;
   int Height = 30;
   CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
   DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Event_Heading[0],false);
   X1 +=Width;

   Parameter_ID = new int[CChildView::TotalEventHeading];

   for(int index =LeftMostParameter; index<LeftMostParameter+4;index++)
   {
      TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
      memset(Parameter_ID,0,CChildView::TotalEventHeading);
      Parameter_ID[index]= index+1;
      for(int index1 =1;index1<CChildView::TotalEventHeading;index1++)
      {
         int ID;
         ID=Parameter_ID[index];
         if(ID == CChildView::EventLogPara_ID[index1])
         {
            DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_Event_Heading[index1],false);
         }

         if(Parameter_ID[index] ==0)
            DrawText(pDC, SmallFont, Black, TextRect, "****",false);
      }
      X1 +=Width;
   }
   CPen *oldPen;
   CPen NewPen;
   NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[Black]);
   oldPen = pDC->SelectObject(&NewPen);
   pDC->MoveTo(20,Y1+Height+10);
   pDC->LineTo(X1,Y1+Height+10);
   pDC->SelectObject(oldPen);
   NewPen.DeleteObject();
}

void CEventLog::DrawEventParameterHeading(HPDF_Page * page)
{
   char UnicodeStr[8192];
   int XCord=ONELINEGAP ;
   int YCord = FOURWELDLINEGAP;

   CString	Event_ColumnHeading[10];
   HPDF_Page_SetRGBFill(*page, 0.75, 0.75, 0.75);
   HPDF_Page_SetLineWidth (*page,2);

   HPDF_Page_Rectangle(*page, 2,HPDF_Page_GetHeight(*page)-110, HPDF_Page_GetWidth(*page)-10, TWOWELDLINEGAP);
   HPDF_Page_FillStroke(*page);
   for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalEventHeading;TextHeadingNo++)
      Event_ColumnHeading[TextHeadingNo]=CChildView::Parameter_Event_Heading[TextHeadingNo];
   HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);
   CString EventStr = *(Event_ColumnHeading);

   CString ParameterString1 = EventStr.SpanExcluding(_T(" "));
   CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr); 
   XCord+=EVENTTEXTSPACING; 
   CString TimeStr = (Event_ColumnHeading[2]);
   CString ParameterString2 = TimeStr.SpanExcluding(_T(" "));
   CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
   if(CChildView::metric)
      CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,"(d/m/y)");

   else
      CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,"(m/d/y)");
   XCord+=EVENTTEXTSPACING; 

   CString Datestr = (Event_ColumnHeading[1]);
   CString ParameterString3 = Datestr.SpanExcluding(_T(" "));
   CChildView::thisPtr->CStringToUTF(ParameterString3,UnicodeStr);

   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr); 	


   XCord+=EVENTTEXTSPACING; 


   for(int i = 3;i<CChildView::TotalEventHeading;i++)
   {
      CString Str = *(Event_ColumnHeading+i);

      CString ParameterString1 = Str.SpanExcluding(_T(" "));
      CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));

      CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
      CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
      CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
      CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,UnicodeStr);
      XCord+=EVENTTEXTSPACING;
   }
}

bool CEventLog::CreateEventPDF()
{
   bool WrapAroundOnEventFile = false;
   bool PDFCreateStatus = true;
   char STR[1024];
   HPDF_Doc  pdf;
   const char *fontname;
   pdf = HPDF_New (error_handler, NULL);
   HPDF_Page page = HPDF_AddPage (pdf);
   HPDF_Font def_font;
   HPDF_UseUTFEncodings(pdf);
   CString EventHistoryStr = CVgaMenuItem ::LinearSearch(XSTR(EVENTHISTORY_STRINGID));

   fontname = HPDF_LoadTTFontFromFile(pdf, CChildView::thisPtr->PDFFontName, HPDF_TRUE);
   def_font = HPDF_GetFont(pdf, fontname, "UTF-8");
   PdfWithImage(&pdf,&page,&def_font);
   HPDF_Page_SetFontAndSize (page, def_font,20);
   CChildView::thisPtr->CStringToUTF(EventHistoryStr,STR);
   CChildView::DrawPDFText(&page,10,TWOWELDLINEGAP,STR);
   int j;
   HPDF_Page_SetFontAndSize(page,def_font,8);
   CString CurrentFilepath = "";
   char Eventfname[64];
   strcpy (Eventfname,"EventHistory");
   CurrentFilepath = CChildView::thisPtr->GetCurrentFilePath(Eventfname);
   CChildView::thisPtr->CreateFolder(true);
   sprintf(Eventfname,"%S",CurrentFilepath);

   CString data ,EventNo,Time,Date;
   int PdfPageCount = 1;

   int XCord=ONELINEGAP ;
   int event_Ycord = SIXWELDLINEGAP;
   int StartPoint = 0,Count = MAX_EVENT_PDF_PAGES;	
   int MaxCount = CEventLog::SuccessfullyWrittenEventRecord;
   DrawEventParameterHeading(&page);

   WrapAroundOnEventFile = false;
   if(CEventLog::SuccessfullyWrittenEventRecord >= MAX_ALLOWED_EVENT_LOG) {
      MaxCount = MAX_ALLOWED_EVENT_LOG;
      StartPoint = CEventLog::CurrentDisplayEventCount;
   }


   while(CEventLog::thisHisPtr->EventLogList.GetCount())
      delete CEventLog::thisHisPtr->EventLogList.RemoveHead();
   while(CChildView::thisPtr->EventFlag && PDFCreateStatus && !EstopPressedFlag)
   {
      Count = MAX_EVENT_PDF_PAGES;
      if(MaxCount <= (StartPoint+Count))
         Count = MaxCount - StartPoint;
      PDFCreateStatus =	CChildView::thisPtr->EventFlag = PrepareEventListForPDF(EventDataFileName,StartPoint,Count);
     
      CEventHistoryData *object = NULL;

      POSITION pos;
      XCord=ONELINEGAP ; 

      pos = CEventLog::thisHisPtr->EventLogList.GetHeadPosition();
      while(pos && !EstopPressedFlag)
      {
         object = CEventLog::thisHisPtr->EventLogList.GetNext(pos);

         EventNo =object->Parameter_Value[0];
         sprintf(STR,"%S",EventNo);
         CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
         XCord+=EVENTTEXTSPACING;

         Time =object->Parameter_Value[2];
         sprintf(STR,"%S",Time);
         CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
         XCord+=EVENTTEXTSPACING;

         Date =object->Parameter_Value[1];
         sprintf(STR,"%S",Date);
         CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
         XCord+=EVENTTEXTSPACING;

         for(j =3;j<CChildView::thisPtr->TotalEventHeading;j++)
         {
            data =object->Parameter_Value[j];
            sprintf(STR,"%S",data);
            CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
            XCord+=EVENTTEXTSPACING;
         }
         XCord=ONELINEGAP;
         event_Ycord += ONEWELDLINEGAP;
         /*Write event description in PDF*/
         int tempID = 0;
         ParamDescription *Pdescr = NULL;
         EventDescription *Description = NULL;
		 DisplayPosition NameDisplayPosition = DO_NOT_DISPLAY;
		 CString ParameterName = "";
         UINT16 ParamID = 0;
         CString ParameterID ="";
         CString desc = "";
         CString EventId = "";
         //event id is string in the format EV101,remove EV
         //not the correct way to pass eventID ti atoi .correct this
         tempID = atoi((const char*)object->EventHistoryObj.EventId+2);			

         EventId.Format(_T("EV%d"),tempID);
         theApp.eds.Lookup(EventId, Description);
         if(Description == NULL)
         {   
            EventId.Format(_T("EV%d"),900);//unknown event
            theApp.eds.Lookup(EventId, Description);
         }
         if(Description!=NULL)
            desc = Description->GetEventDescription();
         ParamID = object->EventHistoryObj.ParameterId;
         ParameterID.Format(_T("%d"),ParamID);
		 //coverity fix 12557
         if(desc.GetLength() > 0 && Description != NULL)
         {
			NameDisplayPosition = (DisplayPosition)_tstoi(Description->DisplayPosition);
			if(NameDisplayPosition == SEPARATE)
				ParameterName = GetNameFromID(ParamID);
            CString DataOld = object->Parameter_Value[j+1];
            CString DataNew = object->Parameter_Value[j ];
            UINT16 ParamID = object->EventHistoryObj.ParameterId;
            if(tempID == EVENT_CALIBRATION)//calibration related events
               desc = PrepareDescription(ParamID,tempID, DataOld,false);	            
            else if(tempID == EVENT_USER_MODIFIED )
            {
               theApp.pds.Lookup(ParameterID,Pdescr);
               if(Pdescr!=NULL)
               {  
                  if(ParamID == PASSWORD_CHANGE)
                     desc = desc +" " +Pdescr->GetParamDescription();
                  else if(ParamID == AUTHORITY_CHANGE)
                     desc = Pdescr->GetParamDescription() + " " +Description->Str1 + " " + PrepareDescription(ParamID,tempID,DataOld,false) + " " +  Description->Str2 + " " +  PrepareDescription(ParamID,tempID,DataNew,false);
                  else
                     desc = desc +" " +Pdescr->GetParamDescription() + " " +Description->Str1 + " " + PrepareDescription(ParamID,tempID,DataOld,false) + " " +  Description->Str2 + " " +  PrepareDescription(ParamID,tempID,DataNew,false);
               }
            }
            else if(Description) 
			{
				if((NameDisplayPosition == DO_NOT_DISPLAY)||(NameDisplayPosition == SEPARATE))
                  desc = desc +" " + Description->Str1 + " " + PrepareDescription(ParamID,tempID,DataOld,false) + " " +  Description->Str2 + " " +  PrepareDescription(ParamID,tempID,DataNew,false);
				else if(NameDisplayPosition == BEFORE_EVENT_DESCRIPTION)
				  desc = GetNameFromID(ParamID) + " " + desc +" " + Description->Str1 + " " + PrepareDescription(ParamID,tempID,DataOld,false) + " " +  Description->Str2 + " " +  PrepareDescription(ParamID,tempID,DataNew,false);
				else if(NameDisplayPosition == AFTER_EVENT_DESCRIPTION)
				  desc =  desc + " " + GetNameFromID(ParamID) + " " + Description->Str1 + " " + PrepareDescription(ParamID,tempID,DataOld,false) + " " +  Description->Str2 + " " +  PrepareDescription(ParamID,tempID,DataNew,false) ;
			}

            if(desc.GetLength() <  MAX_DESCRIPTION_PERLINE_PDF)			 
            {
               sprintf(STR,"%S:",EventNo);
               CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
               XCord+=EVENTTEXTSPACING;
               /* print in one line*/
               CChildView::thisPtr->CStringToUTF(desc,STR);
               CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
               XCord=ONELINEGAP;
               event_Ycord += ONEWELDLINEGAP;
            }
            else
            {					
               CString Line = "", Line1;
               int Temp1  =0;
               for(CString sItem = desc.Tokenize(_T(" "),Temp1); Temp1 >= 0; sItem = desc.Tokenize(_T(" "),Temp1))
               {
                  Line += (sItem + " ");
                  if(Line.GetLength() > MAX_DESCRIPTION_PERLINE_PDF)
                  {
                     sprintf(STR,"%S:",EventNo);
                     CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
                     XCord+=EVENTTEXTSPACING;

                     CChildView::thisPtr->CStringToUTF(Line1,STR);
                     CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
                     XCord=ONELINEGAP;
                     event_Ycord += ONEWELDLINEGAP;
                     Line1 = "";
                     Line = (sItem + " ");
                  }
                  Line1 = Line;
               }
               if(Line1.GetLength() > 0)
               {
                  sprintf(STR,"%S:",EventNo);
                  CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
                  XCord+=EVENTTEXTSPACING;

                  CChildView::thisPtr->CStringToUTF(Line1,STR);
                  CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
                  XCord=ONELINEGAP;
                  event_Ycord += ONEWELDLINEGAP;
               }
            }
         }
		     /*Write parameter name  in PDF*/
		   if(ParameterName.GetLength()>0)
            {

            sprintf(STR,"%S:",EventNo);
            CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
            XCord+=EVENTTEXTSPACING;

            data = ParameterName;            
			CChildView::thisPtr->CStringToUTF(data,STR);
            CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
            XCord=ONELINEGAP;
            event_Ycord += ONEWELDLINEGAP;
            }

         /*Write event change reason in PDF*/
         if(object->Parameter_Value[10].GetLength()>0)
         {

            sprintf(STR,"%S:",EventNo);
            CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
            XCord+=EVENTTEXTSPACING;

            data = object->Parameter_Value[10];
            sprintf(STR,"%S",data);
            CChildView::DrawPDFText(&page,XCord,event_Ycord,STR);
            XCord=ONELINEGAP;
            event_Ycord += ONEWELDLINEGAP;
         }

         if(PdfPageCount >= MAX_EVENT_PDF_PAGES)
         {
		 	//coverity fix 12552
            SavePDFToUSB(pdf, Eventfname);

            pdf = NULL;
            pdf = HPDF_New (error_handler, NULL);
            page = HPDF_AddPage (pdf);
            HPDF_UseUTFEncodings(pdf);

            fontname = HPDF_LoadTTFontFromFile(pdf, CChildView::thisPtr->PDFFontName, HPDF_TRUE);
            def_font = HPDF_GetFont(pdf, fontname,"UTF-8");//UTF-8
            PdfWithImage(&pdf,&page,&def_font);
            HPDF_Page_SetFontAndSize (page, def_font,20);
            CChildView::thisPtr->CStringToUTF(EventHistoryStr,STR);
            CChildView::DrawPDFText(&page,10,TWOWELDLINEGAP,STR);
            HPDF_Page_SetFontAndSize(page,def_font,8);
            strcpy (Eventfname,"EventHistory");
            CurrentFilepath = CChildView::thisPtr->GetCurrentFilePath(Eventfname);
            CChildView::thisPtr->CreateFolder(true);
            sprintf(Eventfname,"%S",CurrentFilepath);
            DrawEventParameterHeading(&page);
            event_Ycord = SIXWELDLINEGAP;
            PdfPageCount =1;
         }
         if((event_Ycord > HPDF_Page_GetHeight(page)-100) && PdfPageCount < MAX_EVENT_PDF_PAGES)
         {
            page = HPDF_AddPage (pdf);
            PdfWithImage(&pdf,&page,&def_font);
            HPDF_Page_SetFontAndSize (page, def_font,25);
            CChildView::thisPtr->CStringToUTF(EventHistoryStr,STR);
            CChildView::DrawPDFText(&page,10,TWOWELDLINEGAP,STR);
            HPDF_Page_SetFontAndSize (page, def_font, 8);
            DrawEventParameterHeading(&page);
            event_Ycord = SIXWELDLINEGAP;
            PdfPageCount++;
         }
         delete CEventLog::thisHisPtr->EventLogList.RemoveHead();
         object = NULL;
      }
      StartPoint+=Count;
      if(WrapAroundOnEventFile)
      {
         if(StartPoint >= (CEventLog::CurrentDisplayEventCount-1))
            CChildView::thisPtr->EventFlag = false;
      }
      else
      {
         if((StartPoint >= MAX_ALLOWED_EVENT_LOG) )
         {
            StartPoint = 0;
            WrapAroundOnEventFile = true;
            MaxCount = CEventLog::CurrentDisplayEventCount;
         }
         else if(StartPoint>=MaxCount)
            CChildView::thisPtr->EventFlag = false;
         else
            CChildView::thisPtr->EventFlag = true;
      }
      PDFCreateStatus = CChildView::thisPtr->USBPresent();
   }
   if(PDFCreateStatus && !EstopPressedFlag)
	   PDFCreateStatus = SavePDFToUSB(pdf, Eventfname);
   else 
   {
	   PDFCreateStatus = false;
	   HPDF_Free (pdf);
   }

   return PDFCreateStatus;
}
bool CEventLog::PrepareEventListForPDF(CString Path ,int StartingPoint,int Count)
{
   unsigned long HeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
   unsigned long size = sizeof(CEventHistoryData);
   unsigned long ObjectSize = size + sizeof(char); // <EventRecord{n},>
   //UINT32 TotalObjectCount = 0,ReadObjectIndex = 0;
   //char Comma = 0;

   CFile f;
   CFileException e;
   unsigned int NoOfBytesRead=0;
   bool RetVal = true;
   if( !f.Open( Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
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
      if(f.GetLength()<=HeaderSize)
      {
         f.Close();
         return false ;
      }
      else
      {

         f.Seek(StartingPoint*ObjectSize + HeaderSize,CFile::begin);
         char Comma;	
         CEventHistoryData* object; 
        
         while((NoOfBytesRead!=f.GetLength()) && (Count--))
         {
            object =new CEventHistoryData();

            NoOfBytesRead+=f.Read(object,size);
            NoOfBytesRead+=f.Read(&Comma,sizeof(char));
            object->Parameter_Value = NULL;
            object->SetParameters();
            CEventLog::thisHisPtr->EventLogList.AddTail(object);
         }
      }
      f.Close();
   }
   return RetVal;
}


/* This function prepares event description from main.gui based on event id. */
EventDescription::EventDescription(CXmlElement * e)
{
   EventID = e->GetAttribute("eid");
   EventDesc = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID"));
   EventDescEng = e->GetAttribute("text");//get the English description from gui file for JSON responses
   DisplayPosition = e->GetAttribute("ParameterName");
   Str1 =  CVgaMenuItem ::LinearSearch(e->GetAttribute("textID1"));
   Str2 =  CVgaMenuItem ::LinearSearch(e->GetAttribute("textID2"));

}

CString EventDescription::GetEventID()
{
   return EventID;
}

CString EventDescription::GetEventDescription(bool InEnglish)
{
   if(InEnglish)
      return EventDescEng;
   else
      return EventDesc;
}

/* This function prepares description from main.gui based on parameter id*/
ParamDescription::ParamDescription(CXmlElement * e)
{
   ParamID = e->GetAttribute("pid");	
   ParamDesc = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID"));
   ParamDescEng = e->GetAttribute("text");//get the english description from gui file for JSON responses
   Str[0]=  CVgaMenuItem ::LinearSearch(e->GetAttribute("textID1"));
   Str[1] =  CVgaMenuItem ::LinearSearch(e->GetAttribute("textID2"));
   Str[2] = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID3"));
   Str[3] = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID4"));
   Str[4] = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID5"));
   Str[5] = CVgaMenuItem ::LinearSearch(e->GetAttribute("textID6"));
}

CString ParamDescription::GetParamID()
{
   return ParamID;
}

CString ParamDescription::GetParamDescription(bool InEnglish)
{
   if(InEnglish)
      return ParamDescEng;
   else
      return ParamDesc;
}