/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTable.cpp_v   1.21   16 Apr 2015 06:01:50   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTable.cpp_v  $
 * 
 *    Rev 1.21   16 Apr 2015 06:01:50   sesharma
 * Moved the extern strings to UserIDTable.h file.
 * 
 *    Rev 1.20   06 Jan 2015 05:12:40   AnPawar
 * changes for date format string
 * 
 *    Rev 1.19   05 Jan 2015 05:31:24   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.18   11 Dec 2014 06:51:08   RJamloki
 * CreatePDF() changed to read text from Main.gui.
 * 
 *    Rev 1.17   28 Nov 2014 08:32:26   rjamloki
 * Unused variables removed(Coverity Issue)
 * 
 *    Rev 1.16   14 Nov 2014 02:54:18   rjamloki
 * CUserIDTable::CreatePDF() changed.
* 
*    Rev 1.15   10 Nov 2014 02:51:38   rjamloki
* CreatePDF() and DrawUserIDHeading() changed for multilanguage PDF support.
* 
*    Rev 1.14   25 Sep 2014 12:09:32   AnPawar
* user level added in pdf.
* 
*    Rev 1.13   05 Sep 2014 07:02:26   amaurya
* Corrected the list traverse in DrawUserIDData()
* 
*    Rev 1.12   18 Aug 2014 07:59:08   rjamloki
* Draw changes after removing user name
* 
*    Rev 1.11   28 Jul 2014 14:22:54   rjamloki
* memory leak taken care.
* 
*    Rev 1.10   09 Jul 2014 07:10:06   akaushal
* DrawUserIDHeading() function changed
* 
*    Rev 1.9   09 Jun 2014 11:56:40   rjamloki
* Variable initialization in constructor.DrawUserIDHeading() changed
* 
*    Rev 1.8   27 May 2014 18:10:02   akaushal
* Checks for memory allocation
* 
*    Rev 1.7   27 May 2014 06:44:50   amaurya
* User ID List cleanUp updated
* 
*    Rev 1.6   20 May 2014 11:09:20   rjamloki
* Macro to disable printf. 
* 
*    Rev 1.5   07 May 2014 13:18:40   akaushal
* Macro for printf disable .
* 
*    Rev 1.4   21 Apr 2014 13:48:24   akaushal
* Removed unused UpdateUserData().
* 
*    Rev 1.3   28 Mar 2014 14:33:14   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.2     26 Mar 2014 14:25:46 rjamloki   
* CreatePDF() added .CreateUserObjectList() moved from vgabutton.cpp to here
*
*    Rev 1.     06 Mar 2014 11:30:44 rjamloki   
* Add new User ID function
*
*    Rev 1.     05 Mar 2014 14:43:16 rjamloki      
* Initial Revision.
*/
#include "stdafx.h"
#include "SBC.h"
#include "UserIDTable.h"
#include "VgaButton.h"
#include "UserID.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CUserIDTable::TopMostData;
int CUserIDTable::SelectedUserIDData;
int CUserIDTable::LeftMostParameter;

CUserIDTable * CUserIDTable::thisPtr;


CUserIDTable::CUserIDTable(CXmlElement * e)
{
   Parameter_ID = NULL;
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
   thisPtr=this;
   CUserIDTable::LeftMostParameter=1;
}

CUserIDTable::CUserIDTable()
{
   Parameter_ID=new int[1];
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

CUserIDTable::~CUserIDTable()
{
   if(Parameter_ID)
      delete []Parameter_ID;
   while(UserIDList.GetCount()>0)
      delete UserIDList.RemoveHead();
}

void CUserIDTable::Draw(CDC *pDC)
{
   DrawUserIDData(pDC);
}

bool CUserIDTable::MouseClick(const CPoint &p, CChildView *view)
{
   return true;
}

void CUserIDTable::DrawUserIDData(CDC *pDC)
{
   //	CRunScreen::Displayable_columns=5;
   int LineNo=1;
   int TotalCyclesDrawn=0;
   if(UserIDList.GetCount())
   {
      POSITION pos = UserIDList.GetHeadPosition();
      for(int CurrentPos = 1 ; (CurrentPos < TopMostData) && pos; CurrentPos++)
         UserIDList.GetNext(pos);
      DrawRect(pDC, CChildView::Highlight_Color, CRect(8,(LINE_GAP*(SelectedUserIDData+3)),
         (HISTORY_TBL_START_X + 5 * ParamRect_Width + 12),
         (LINE_GAP*(SelectedUserIDData+4))));
      while(pos)
      {
         if(TotalCyclesDrawn==MaxUserIDPerScreen)
            break;
         CUserIDTableData * Obj = UserIDList.GetNext(pos);
         Obj->DrawTableData(pDC,LeftMostParameter, LineNo);
         TotalCyclesDrawn++;
         LineNo++;
      }
   }
   DrawParameterHeadings(pDC);
}

void CUserIDTable::DrawParameterHeadings(CDC *pDC)
{
   /*if(LeftMostParameter>(TotalColoumn-4))
   LeftMostParameter=1;*/

   int X1 = 20;
   int Y1 =60;
   int Width =170;
   int Height = 30;
   CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
   DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_UserID_HeadingS[0],false);
   X1 +=Width;
   Parameter_ID = new int[CChildView::TotalUserIDHeading];

   for(int index = LeftMostParameter; index < LeftMostParameter + 3; index++)
   {
      TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
      memset(Parameter_ID,0,CChildView::TotalUserIDHeading);
      Parameter_ID[index]= index+1;
      for(int index1 =1;index1<CChildView::TotalUserIDHeading;index1++)
      {
         int ID;
         ID=Parameter_ID[index];
         if(ID == CChildView::UserIDPara_ID[index1])
         {
            DrawText(pDC, SmallFont, Black, TextRect, CChildView::Parameter_UserID_HeadingS[index1],false);
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

void CUserIDTable::DrawUserIDHeading(HPDF_Doc *& pdf,HPDF_Page *& page)
{

   HPDF_Page_SetRGBFill(*page, 0.75, 0.75, 0.75);
   HPDF_Page_SetLineWidth (*page,2);
   HPDF_Page_Rectangle(*page, 2,HPDF_Page_GetHeight(*page)-110, HPDF_Page_GetWidth(*page)-10, TWOWELDLINEGAP);
   HPDF_Page_FillStroke(*page);
   HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);
   UserIDTemp_pos = NULL;
   UserIDTemp_pos = tempUserIDList.GetHeadPosition();
   CString TimeString,DateString;
   char UnicodeStr[8192];   
   TimeString = tempUserIDList.GetNext(UserIDTemp_pos);
   DateString = tempUserIDList.GetNext(UserIDTemp_pos);
   CString UserID_ColumnHeading[4];

   for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalUserIDTextHeading;TextHeadingNo++)
      UserID_ColumnHeading[TextHeadingNo]=CChildView::Parameter_UserID_Heading[TextHeadingNo];
   CString Str = *(UserID_ColumnHeading);
   CString ParameterString1 = Str.SpanExcluding(_T(" "));
   CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
   int XCord=0,YCord=0; 
   XCord = FIVEWELDLINEGAP;
   YCord = FOURWELDLINEGAP;
   CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
   CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,UnicodeStr);
   XCord += THREEWELDLINEGAP;
   CChildView::thisPtr->CStringToUTF(TimeString,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
   XCord += THREEWELDLINEGAP;
   CChildView::thisPtr->CStringToUTF(DateString,UnicodeStr);
   CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
   
   if(CChildView::metric)   
	  CChildView::thisPtr->CStringToUTF(DmyFormat,UnicodeStr);   
   else 
	   CChildView::thisPtr->CStringToUTF(MdyFormat,UnicodeStr);
     
  
   CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,UnicodeStr);
   XCord += THREEWELDLINEGAP;

   for(int i = 1;i<CChildView::TotalUserIDTextHeading;i++)
   {
      CString Str = *(UserID_ColumnHeading+i);
      CString ParameterString1 = Str.SpanExcluding(_T(" "));
      CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
      CChildView::thisPtr->CStringToUTF(ParameterString1,UnicodeStr);
      CChildView::DrawPDFText(page,XCord,YCord,UnicodeStr);
      CChildView::thisPtr->CStringToUTF(ParameterString2,UnicodeStr);
      CChildView::DrawPDFText(page,XCord,YCord+ONEWELDLINEGAP,UnicodeStr);
      XCord += THREEWELDLINEGAP;
   }
}

void CUserIDTable::CreatePDF(HPDF_Doc *& pdf,HPDF_Page *& page)
{
   int CurrentDataCount = 1;
   int YCord = FIVEWELDLINEGAP;
   int XCord = FIVEWELDLINEGAP;

   char STR[256]; 
   CUserIDTableData *object = NULL;
   HPDF_Font def_font;
   const char *fontname;
   CString UserIdString = CVgaMenuItem ::LinearSearch(XSTR(USERID_STRINGID));	
   fontname = HPDF_LoadTTFontFromFile(*pdf, CChildView::thisPtr->PDFFontName, HPDF_TRUE);
   def_font = HPDF_GetFont(*pdf, fontname,"UTF-8");
   DrawUserIDHeading(pdf,page);

   while((UserIDList.GetCount() > 0) && (!EstopPressedFlag))
   {
      object = UserIDList.GetHead();

      XCord = FIVEWELDLINEGAP; 
      YCord += ONEWELDLINEGAP;
      if(YCord > HPDF_Page_GetHeight(*page)-100)
      {
         *page = HPDF_AddPage (*pdf);
         PdfWithImage(pdf,page,&def_font);
         HPDF_Page_SetFontAndSize (*page, def_font,25);
         CChildView::thisPtr->CStringToUTF(UserIdString,STR);
         CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
         HPDF_Page_SetFontAndSize (*page, def_font, 8);
         DrawUserIDHeading(pdf,page);
         YCord = SIXWELDLINEGAP;			   
      }

      sprintf(STR,"%d",CurrentDataCount);
      CChildView::DrawPDFText(page,XCord,YCord,STR);
      XCord += THREEWELDLINEGAP;

      GetRTCTime(&object->userIdData.CreateModifyTime,STR);
      CChildView::DrawPDFText(page,XCord,YCord,STR);

      XCord += THREEWELDLINEGAP;

      GetRTCDate(&object->userIdData.CreateModifyTime,STR);
      CChildView::DrawPDFText(page,XCord,YCord,STR);

      XCord += THREEWELDLINEGAP;


      CChildView::DrawPDFText(page,XCord,YCord,object->userIdData.UserId);

      XCord += THREEWELDLINEGAP;

      ActiveStatus StatusFlag = object->userIdData.Status;
      if(StatusFlag == Enabled)
         sprintf(STR,"%S",CVgaMenuItem::LinearSearch(XSTR(ENABLED_STR_ID)));
      else
         sprintf(STR,"%S",CVgaMenuItem::LinearSearch(XSTR(DISABLED_STR_ID)));

      CChildView::DrawPDFText(page,XCord,YCord,STR);

      XCord += THREEWELDLINEGAP;

      CString userLevelstr = object->GetUserLvlStr(object->userIdData.UserLevel);
      sprintf(STR,"%S",userLevelstr);
      CChildView::DrawPDFText(page,XCord,YCord,STR);

      delete UserIDList.RemoveHead(); 	
      CurrentDataCount++;
   }
}

/*CreateUserObjectList function gets user ID data from WC.
At a time this function will bring maximum 18 user data.
This function also clears the UserIDList that is displayed
on "User ID Setup" screen*/
void CUserIDTable::CreateUserObjectList(void)
{
   int length = 0;
   CUserIDTable::LeftMostParameter = 1;
   CUserIDTable::SelectedUserIDData = 1;
   CUserIDTable::TopMostData = 1;
   CUserIDTable::thisPtr->TotalColoumn = CChildView::TotalUserIDHeading;
   printf("type == USERID\n");
   length =1;
   int DATA_Count = 0;	
  
   unsigned char CommandData[1];
  
   UINT32 TotalCycles = 0;
   bool LastCycleFlag = false;
   while(CUserIDTable::thisPtr->UserIDList.GetCount())
      delete CUserIDTable::thisPtr->UserIDList.RemoveHead();
   if(!creating_pdf)
      CChildView::thisPtr->ShowMessageScreen(PleaseWait);
   do 
   {

      length =1;
      CommandData[0]=(char)DATA_Count++;
      unsigned char * data = (unsigned char *) &CommandData[0];
      CHostCommand * request = new CHostCommand(USERIDSETUP, data, length);   //1054
      CHostCommand * response = app->SendUiHostCommand(request);
      if(response)
      { 	  
         printf("Response Positive");
         char ch=CHostCommand::AckNak();
         data = response->GetData();
         length = response->GetDataLength();
         printf(" length = %d ,",length);
         int logTotalCycles = *((int*)(data));	//number of Data.
         TotalCycles = ntohl(logTotalCycles); //,sizeof(logTotalCycles));

         if(TotalCycles != 0)
         {
            (data)+= sizeof(UINT32);
            length-=sizeof(UINT32);
         }
         else
         {
            LastCycleFlag = true;
            delete response;
            break; //return;
         }
         if(TotalCycles < DATAINONEPACKET){
            LastCycleFlag = true;
         }
         if(ch==ACK)
         {
            printf("ch==ACK\n");
            struct UserIDStruct * IDTable = (struct UserIDStruct*)data;
           
            for(UINT32 i = 0;i < TotalCycles; i++)
            {
               CUserIDTableData * tableObj = new CUserIDTableData(IDTable);
               CUserIDTable::thisPtr->UserIDList.AddTail(tableObj);
               IDTable++;
            }

            delete response;
         }

         else // No Ack
         {
            delete response;
            break;
         }	
      }
   }
   while(LastCycleFlag != true);	
   CUserIDTable::thisPtr->TotalCycle = (int)CUserIDTable::thisPtr->UserIDList.GetCount();

}