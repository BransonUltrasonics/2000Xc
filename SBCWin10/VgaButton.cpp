/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaButton.cpp_v   1.63   30 Aug 2016 14:09:48   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaButton.cpp_v  $
 * 
 *    Rev 1.63   30 Aug 2016 14:09:48   RJamloki
 * Removing comments from bucket #2 debug testing
 * 
 *    Rev 1.62   26 May 2016 15:09:36   RJamloki
 * Added EXECUTIVE_PASSWORD_CHANGE button functionality
 * 
 *    Rev 1.61   29 Apr 2015 16:12:54   rjamloki
 * Fixed return menu for down speed tune menu by initializing DownspeedMenuName to WeldSetup Menu ID on Down Speed button handler. 
 * 
 *    Rev 1.60   16 Apr 2015 14:18:18   rjamloki
 * Coverity fixes done before release
 * 
 *    Rev 1.59   16 Apr 2015 06:04:20   sesharma
 * Coverity fix and hard-coded strings removed.
 * 
 *    Rev 1.58   08 Apr 2015 14:23:40   AnPawar
 * Changes for pressure stepping events in PrepareDescription() function and functions headers added.
 * 
 *    Rev 1.57   03 Apr 2015 06:36:38   amaurya
 * before creating pdf checking wheather data is present in file or not to avoid blain pdf.
 * 
 *    Rev 1.56   01 Apr 2015 12:57:36   amaurya
 * changes in PrepareDescription() to add authority check event.
 * 
 *    Rev 1.55   28 Mar 2015 04:48:32   RJamloki
 * Change to display NAK message if weld is going on and user try to enter into the Cal Full system screen.
 * 
 *    Rev 1.54   13 Mar 2015 06:33:36   amaurya
 * Comments added as it was fixed for coverty issue.
 * 
 *    Rev 1.53   11 Mar 2015 09:28:10   amaurya
 * CopyPresetToPowerSupply(),WriteDataToUSBFile(),DeleteSelectedUSBPreset()changed to change the preset extension to .prst.
 * 
 *    Rev 1.52   11 Feb 2015 06:24:08   amaurya
 * change in DisplayEventDesciption() function to handle event details display issue after alarm reset
 * 
 *    Rev 1.51   03 Feb 2015 07:25:18   amaurya
 * OverwritePreset() changed to append a space before the preset name in case of button click for copy all preset.
 * 
 *    Rev 1.50   02 Feb 2015 07:07:10   amaurya
 * Removed the redundant and unused CopyAllFlag.
 * 
 *    Rev 1.49   30 Jan 2015 08:48:50   amaurya
 * Change in WritedatatoUsbFile() ,to opening file in read only mode.
 * 
 *    Rev 1.48   30 Jan 2015 08:15:40   amaurya
 * OverwritePreset() changed to modify the overwrite message on copyall button click.CopyAllPreset() changed to copy all the USB preset name to a temporary list.DisplayEventDesciption() changed to display parameter name along with event description.
 * 
 *    Rev 1.47   26 Jan 2015 13:38:48   rjamloki
 * Fix for pointing to right event on list before displaying description
 * 
 *    Rev 1.46   06 Jan 2015 05:12:52   AnPawar
 * check before creating pdf again.
 * 
 *    Rev 1.45   05 Jan 2015 05:31:24   rjamloki
 * changes to handle e-stop while creating pdf
 * 
 *    Rev 1.44   02 Jan 2015 06:35:30   rjamloki
 * numbers replaced by macros in function ShowPowerSupplyMessageScreen()
 * 
 *    Rev 1.43   02 Jan 2015 05:03:12   rjamloki
 * CopyAllPreset() and CopyPresetOnOKOrCancelButton() functions added to support preset copy all
 * 
 *    Rev 1.42   12 Dec 2014 06:04:44   RJamloki
 * ExitDownspeedtune() changed to get system variable values from WC after clicked on exit button on downspeed tune screen.
 * 
 *    Rev 1.41   11 Dec 2014 06:51:40   RJamloki
 * DiagUserIO() changed to get welding status from WC.
 * 
 *    Rev 1.40   28 Nov 2014 08:32:52   rjamloki
 * Warnings removed and Coverity fix
 * 
 *    Rev 1.39   14 Nov 2014 10:42:10   AnPawar
 * changes for automated down speed tuning and horn down screen
 * 
 *    Rev 1.38   14 Nov 2014 02:54:30   rjamloki
 * SaveDownspeedtune() and SaveWeldHistoryPdf() changed.
* 
*    Rev 1.37   10 Nov 2014 02:51:54   rjamloki
* AlarmUpButton() and AlarmDownButton() changed to modify Up and down Arrow functionality. SaveWeldHistoryPdf() changed for multilanguage PDf Support.PrepareDescription() changed.
* 
*    Rev 1.36   20 Oct 2014 05:51:06   RJamloki
* PresetDownExecute()  HistoryScreenUpButton() HistoryScreenDownButton() ShowPowerSupplyMessageScreen() HistoryDownButton() functions changed to display presets as per control level D
* 
*    Rev 1.35   06 Oct 2014 03:29:02   rjamloki
* TotalParamTypes used instead of macro in PrepareDescription function
* 
*    Rev 1.34   01 Oct 2014 10:56:12   AnPawar
* SendCommandForQualityWindow() call removed.File path changed.PrepareDescription() function changed 
* 
*    Rev 1.33   26 Sep 2014 09:30:32   rjamloki
* OverWritePreset fixed to not give false Overwrite popup when copying prset from usb to Powersupply
* 
*    Rev 1.32   25 Sep 2014 12:11:28   AnPawar
* DisplayEventDesciption() function changed and new functionality added for powesupply overload titles
* 
*    Rev 1.31   11 Sep 2014 09:52:44   rjamloki
* SendEventReasonString(), DisplayEventDesciption(), PrepareDescription() function created.  
* 
*    Rev 1.30   08 Sep 2014 05:22:02   rjamloki
* Corrected the mouseclick function for login button .
* 
*    Rev 1.29   05 Sep 2014 12:13:16   rjamloki
* Fix for login button.
* 
*    Rev 1.28   05 Sep 2014 07:03:28   amaurya
* ShowPowerSupplyMessageScreen() and MouseClick() modified. 
* 
*    Rev 1.27   02 Sep 2014 04:07:10   rjamloki
* 1000 ps related changes
* 
*    Rev 1.26   27 Aug 2014 03:21:26   rjamloki
* SaveWeldHistory pdf fixed for repeated weld data in next pdf document
* 
*    Rev 1.25   26 Aug 2014 07:49:26   rjamloki
* SaveWeldHistoryPdf() changed to increase the Font size for weldhistory pdf.
* 
*    Rev 1.24   18 Aug 2014 08:04:48   rjamloki
* Added DownSpeed tune screen handlers
* 
*    Rev 1.23   01 Aug 2014 05:17:12   rjamloki
* memory delete fix in SendCommandForSave and HandleVGASaveButton functions. 
* 
*    Rev 1.22   28 Jul 2014 14:31:40   rjamloki
* added function void SwUpGrade(int arg)
* 
*    Rev 1.21   22 Jul 2014 08:11:06   akaushal
* Changes for VGA file path .
* 
*    Rev 1.20   09 Jul 2014 07:12:58   akaushal
* CVgaButton::MouseClick() function modified to check change conditions.Changes for wrap around events and weld history.DisableStateMachine() added.GetIdleLogoutTime(),
* GetAuthorityCheck() removed.
* 
*    Rev 1.19   11 Jun 2014 10:50:28   rjamloki
* WeldResultColSetup() function added
* 
*    Rev 1.17   09 Jun 2014 12:01:36   rjamloki
* Printing function removed
* 
*    Rev 1.16   28 May 2014 08:06:32   rjamloki
* weld history fix on next pdf creation after 100 pages
* 
*    Rev 1.15   27 May 2014 06:45:54   amaurya
* Code change for Long Wait on Reset Sensor calibration
* 
*    Rev 1.14   20 May 2014 11:11:38   rjamloki
* LogOutFun() and PrepareListForLOG() changed.
* 
*    Rev 1.13   07 May 2014 13:14:28   akaushal
*  Login code updated.
* 
*    Rev 1.12   23 Apr 2014 11:27:12   akaushal
* Updated the Weld Screen navigation functions and save PDF functions
* 
*    Rev 1.11   21 Apr 2014 13:52:00   akaushal
* GetRadioInfo() function changed for 16 or more radio buttons.HandleVGASaveButton(),PresetNumberExecute() function for selecting a preset in Save/Recall Preset. SendCommandForDigitalOutput() function modified to send diagnostic button status.EventScreen button function changed.SendCommandForEventLog() function changed.Login functionality added in SendCommandForUserLogin() function.PrepareListForLOG() function added.
* 
*    Rev 1.10   28 Mar 2014 14:33:18   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.9     26 Mar 2014 14:26:48 rjamloki   
* RecallUserIDProcess() was changed.
*
*    Rev 1.8     07 Mar 2014 11:15:38 rjamloki   
* Modify User Changes.
*
*    Rev 1.7     06 Mar 2014 11:30:44 rjamloki   
* Add new User ID function
*
*    Rev 1.6     05 Mar 2014 14:13:40 rjamloki   
* Screens and PDF working
*
*    Rev 1.5     27 Feb 2014 01:34:10 jerryw.wang   
* Added the button process for Alarm Log screen and Event History screen. Added the Digtial Output process.
*
*    Rev 1.4     03 Jan 2014 09:06:24 rjamloki   
* Header Fix and added command to assign ip.
*
*    Rev 1.3     19 Dec 2013 06:16:52 rjamloki  
* Changed macros to build on both EVC and VC++.
*
*    Rev 1.2     18 Dec 2013 10:00:34 rjamloki   
* Initial Test version.SBC to WC serial communication.
*
*    Rev 1.1     05 Jun 2013 09:33:44 amaurya   
* Initial Revision 2.
*
*    Rev 1.0     03 Apr 2013 10:10:10 amaurya      
* Initial Revision.
*/
#include "stdafx.h"
#include "VgaButton.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VgaRadioButton.h"
#include "HostCommand.h"
#include "Application.h"
#include "VgaScreenSetup.h"
#include "ListBox.h"
#include "WeldingHistory.h"
#include "MsgScreen.h"
#include "BottomHalf.h"
#include "LocalChoice.h"
#include "Table.h"
#include "Toggle.h"
#include "VgaBottomMenu.h"
#include "USBFolder.h"
#include "HistoryGraphs.h"
#include "VgaTitle.h"
#include "Text.h"
#include "ScreenKeypad.h"
#include "VGA.h"
#include "VgaAlphanumeric.h"
#include "AlarmLog.h"
#include "EventLog.h"
#include "UserIDTable.h"
#include "RadioMenu.h"
#include "UserID.h"
#include <exception>
#include "hpdf.h"
#include "zlib.h"
#include "png.h"
#include "stdlib.h"
#include "Childview.h"
#include "VgaVariable.h"
#include "VgaViewPreset.h"
#include "EnumCondition.h"
#ifdef DISABLEPRINTF
#define printf
#endif
//#define TESTING_WITHOUT_DUPS

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

UINT32 HisParameterMap[32];
UINT32 HisParameterCounts;
short HSCurrentGraph[GRAPH_WIDTH];
short HSAmpGraph[GRAPH_WIDTH];
CString EventChangeMenuName="";
CString DownspeedMenuName="";
char SavedPgNum ;

#define MAXSERIALNUMBER_LEN 13
#define NUM_RADIO_BUTTONS_LONG_VAL 15 //macros to check if we have more than 16 radio buttons on page
#define PRESET_NUM_SELECT_ID 220
#define PRESET_INFO_SELECT_ID 226
#define MAX_EVENT_OBJECTS_PER_PAGE 8
#define MIN_HISTORY_FILESIZEPDF 963
#define MIN_EVENT_FILESIZEPDF 10
#define DESCRIPTION_TEXT_ID 4219
#define DESCRIPTION1_TEXT_ID 4274
#define DESCRIPTION2_TEXT_ID 4275
#define REASON_TEXT_ID 4221
#define REASON_BUTTON_TEXT_ID 4220
#define PARAMETER_FIELD_ID 4332
#define PARAMETER_BUTTON_TEXT_ID 4331
#define DESCRIPTION_ARRAY_SIZE 6
void IvvalidateMessage(int Address);
int GetRadioInfo(unsigned char *&data);
void SendGetSetCommand(unsigned short getSetValue,unsigned short index,int Address);
void RecallUserIDProcess(int);
void PresetNumberExecute(int);
int Check_Password(char *,char *,char * ,bool ,bool);
void ProcessNak(int Address);
void DisplayMessage(int);
void SendCommandForVGAButtons(int ID);
bool SaveWeldHistoryPdf(void);
int userid_list_status=0;
extern CChildView::PrintingSetup PrintSetup;
POSITION RunScreenTemp_pos,HistoryTemp_pos,GraphsTemp_pos,WeldTemp_pos,HornScanTemp_pos,ScanGraphsDataTemp_pos,ScreenGraphsTemp_pos,SetupTemp_pos,DUPSTemp_pos,SequenceTemp_pos,UserIDTemp_pos,EventHistoryTemp_pos;
extern CList<CString,CString> tempGraphsList;
extern CList<CString,CString> tempHistoryList;
extern CList<CString,CString> tempWeldList;
extern CList<CString,CString> tempHornScanList;
extern CList<CString,CString> tempScanGraphDataList;
extern CList<CString,CString> tempScreenGraphsList;
extern CList<CString,CString> tempSetupList;
extern CList<CString,CString> tempDUPSList;
extern CList<CString,CString> tempSequenceList;
extern CString OkButtonText;
//extern CList<CString,CString> tempUserIDList;


extern int YCoordinate;
char Historyfname[64];
char CurrentUser[MAX_CHARS_LOGIN]="";
bool UserLoggedinFlag ;
int eventname ;
extern int PageCount;
int GlobalPresetSelection = 1;


CString EventDataFileName;
CString HistoryDataFileName;

int PresetVerify;
int PresetCount = 0;
int CurrentCountToReadWeld = 0;
int CurrentCountToReadEvent = 0;
bool WeldDataLogFile = false;
bool InitialScreenOverlap = false;
bool DownFlagEnd = false;
bool FlagSecondOverlap = false;
bool FlagInitialScreen = false;
bool FlagReachedStart = false;
bool ReasonDisplayFlag = false;
bool NameDisplayFlag = false;
static bool WrapAroundFlag = false; 
static bool WrapAroundWeldFlag = false; 
int TotalDataInFile = 0;
int  TotalDisplayData = 0;
int  ReadLimit = 0;
int  PreviousIndex = 0;
int  TotalCountRead = 0;
int TotalDisplayWeldData = 0;
int TotalWeldCountRead = 0;
int PreviousIndexWeld = 0;
static bool UpFlagErrorBeep = false,DownFlagErrorBeep = false;
unsigned char *StoredPresetListData  = NULL;
CString PrepareDescription(int ParamID,int EventID,CString Data,bool JsonReq);
char *UserLevelArr[DESCRIPTION_ARRAY_SIZE] = {"Operator","Technician","Supervisor","Executive","Branson"};
char *AuthorityChangeArr[DESCRIPTION_ARRAY_SIZE] = {"No Authority","Reset Alarm","Run Unvalidated Preset","Recall Preset","Calibration","Reset Batch Count"};
char *HWVerifyArr[DESCRIPTION_ARRAY_SIZE] = {"Off","P/S Assembly","Actuator Assembly","Stack Assembly","Ground Detect Mode","Verify"};
char *ActuatorArr[DESCRIPTION_ARRAY_SIZE] = {"Passed","Failed","Aborted"," "," "," "};
char *ForceArr[DESCRIPTION_ARRAY_SIZE] = {"Reset Required","P/S Assembly","Actuator Assembly","Stack Assembly","Ground Detect Mode","Ground Detect Mode"};
char *PressureArr[DESCRIPTION_ARRAY_SIZE] = {"Pressure","P/S Assembly","Actuator Assembly","Stack Assembly","Ground Detect Mode","Ground Detect Mode"};
char *PretriggerArr[DESCRIPTION_ARRAY_SIZE] = {"Off","Auto","Dist","Time:","Absolute Mode","Ground Detect Mode"};
char *WeldmodeChangedArr[DESCRIPTION_ARRAY_SIZE] = {"Time Mode","Energy Mode","PeakPower Mode","Collapse Mode","Absolute Mode","Ground Detect Mode"};
char *AmplitudeArr[DESCRIPTION_ARRAY_SIZE] = {"Step","Fixed","PeakPower Mode","Collapse Mode","Absolute Mode","Ground Detect Mode"};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVgaButton::CVgaButton(CString str,int X1,int Y1,int X2,int Y2,CString Fun)
{
   Activated = false;
   text=str;
   RectShow=1;
   Rect=CRect(X1,Y1,X2,Y2);
   SetRect(Rect);
   FunName=Fun;
   MenuName="";
   argument="";
   ObjectPageNum=PAGEALL;
   ArrowType=false;
   ArrowTypeDown=false;
   ScreenArrowUp=false;
   ScreenArrowDown=false;
   LeftArrow=false;
   RightArrow=false;
   DigitalOutput = false;
   Disable = false;
}

CVgaButton::CVgaButton(CXmlElement * e)
{
   textID=e->GetAttribute("textID");
   text=CVgaMenuItem ::LinearSearch(textID);
   /*Storing Co-ordinates*/
   int X1 = _ttoi(e->GetAttribute("X1"));
   int Y1 = _ttoi(e->GetAttribute("Y1"));
   int X2 = _ttoi(e->GetAttribute("X2"));
   int Y2 = _ttoi(e->GetAttribute("Y2"));
   ArrowType = _ttoi(e->GetAttribute("ArrowType")) != 0;
   ArrowTypeDown = _ttoi(e->GetAttribute("ArrowTypeDown")) != 0;
   ScreenArrowUp = _ttoi(e->GetAttribute("ScreenArrowUp")) != 0;
   ScreenArrowDown = _ttoi(e->GetAttribute("ScreenArrowDown")) != 0;
   LeftArrow = _ttoi(e->GetAttribute("LeftArrowType")) != 0;
   RightArrow = _ttoi(e->GetAttribute("RightArrowType")) != 0;
   DigitalOutput = _ttoi(e->GetAttribute("DigitalOutput")) != 0;
   FunName=e->GetAttribute("funname");
   argument=e->GetAttribute("argumentname");
   MenuName=e->GetAttribute("menuname");
   MenuNak=e->GetAttribute("menunak");
   RectShow=_ttoi(e->GetAttribute("Rectshow"));
   Disable = _ttoi(e->GetAttribute("Disable")) != 0;
   Rect=CRect(X1,Y1,X2,Y2);
   SetRect(Rect);
   Activated = false;
   ObjectPageNum=PAGEALL;
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

}

CVgaButton::~CVgaButton()
{

}

void CVgaButton::Draw(CDC *pDC)
{
   CString TempText = text;
   if(CChildView::thisPtr->StringDebugFlag)
      TempText = textID + _T(" ")+ text;
   TRACE(_T("\n Button text %s"),TempText);
   if(RectShow)
   {
      //		printf("RectShow\n");
      if(DigitalOutput)
      {
         if(Activated)
            DrawRect(pDC, Green, rect);
         else
            DrawRect(pDC, Red, rect);
      }
      else
         DrawRect(pDC, CChildView::Button_Color, rect);
      Draw_Pressed_Released_Button(pDC);
      if(ArrowType)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+17,rect.TopLeft( ).y+34), CPoint(rect.TopLeft( ).x+27,rect.TopLeft( ).y+16),CPoint(rect.TopLeft( ).x+38,rect.TopLeft( ).y+34) ,pDC);
      }
      else if(ArrowTypeDown)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+17,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+27,rect.TopLeft( ).y+34),CPoint(rect.TopLeft( ).x+38,rect.TopLeft( ).y+16) ,pDC);
      }
      else if(ScreenArrowUp)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+29), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+11),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+29) ,pDC);
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+39), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+21),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+39) ,pDC);
      }
      else if(ScreenArrowDown)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+11), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+29),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+11) ,pDC);
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+21), CPoint(rect.TopLeft( ).x+25,rect.TopLeft( ).y+39),CPoint(rect.TopLeft( ).x+36,rect.TopLeft( ).y+21) ,pDC);
      }
      else if(LeftArrow)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+25),CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+34) ,pDC);
      }
      else if(RightArrow)
      {
         DrawArrow(CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+16), CPoint(rect.TopLeft( ).x+35,rect.TopLeft( ).y+25),CPoint(rect.TopLeft( ).x+15,rect.TopLeft( ).y+34) ,pDC);
      }
      else
      {
         DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
      }
   }
   else
   {
      DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText+SubText,false);
   }
}

void CVgaButton::DrawArrow(CPoint Start, CPoint Middle, CPoint End,CDC *pDC)
{
   CPen *oldPen;
   CPen NewPen;
   NewPen.CreatePen(PS_SOLID,2,CChildView::Color_Array[CChildView::TextColor]);
   oldPen = pDC->SelectObject(&NewPen);
   pDC->MoveTo(Start.x+XOFFSET,Start.y+XOFFSET);
   pDC->LineTo(Middle.x+XOFFSET,Middle.y+XOFFSET);
   pDC->LineTo(End.x+XOFFSET,End.y+XOFFSET);
   pDC->MoveTo(End.x-1+XOFFSET,End.y+XOFFSET);
   pDC->LineTo(Middle.x+XOFFSET, Middle.y-1+XOFFSET);
   pDC->LineTo(Start.x+1+XOFFSET,Start.y+XOFFSET);
   pDC->SelectObject(oldPen);
   NewPen.DeleteObject();
}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any VGAbutton object is clicked by the user            */
/* This funtion sends a host command to get the new toggled string and displays it.  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/*************************************************************************************/

bool CVgaButton::MouseClick(const CPoint &p, CChildView *view)
{
   if(view->CheckChangeConditions(this) == false)
   {
      CChildView::ErrorBeep();//gives the error beep
      return true;
   }

   if(Disable)
      return true;

   CVgaMenu * menu;
   CString Lastmenu = "";
   if(MenuName!="")
   {
      if (theApp.menus.Lookup(MenuName, menu))
      {
         view->menupointers.AddTail(theApp.MenuPointer);
         view->menusname.AddTail(theApp.menuName);
         view->menus.AddTail(page_no);
         page_no=1;
         Lastmenu = theApp.menuName;
         theApp.menuName = MenuName;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu);
      }
   }
   if(FunName!="")
   {
      if(argument!="")
      {
         void *ptr;
         void (*rmn)(int);
         if(functionCall.Lookup(FunName,ptr))
         {
            rmn = (void (*)(int))ptr;
            rmn(EnumID);
         }
      }
      else
      {
         void *ptr;
         void (*rmn)(int);
         if(functionCall.Lookup(FunName,ptr))
         {
            rmn = (void (*)(int))ptr;
            int Address=(int)this;
            rmn(Address);
         }
      }
   }
   else
   {
      if(MenuName!="")
      {
         view->Invalidate();
         return true;
      }
      //Exit botton handled here
      theApp.menuName=view->menusname.RemoveTail();
      page_no=view->menus.RemoveTail();
      theApp.MenuPointer=view->menupointers.RemoveTail();
      {
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
      }
      view->Invalidate();
   }
   //This is to fix the login butoon on main menu not invlaidating the 
   //view because its added at the tail of main menu list.
   if((theApp.menuName == CVgaBottomMenu::mainMenuID) || (Lastmenu == CVgaBottomMenu::mainMenuID))
      view->Invalidate();
   return true;
}

void ExitSystemProgram(int Address)
{
   theApp.ExitInstance();
   exit(1);
}


void ExitWindowProgram(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch == theApp.ACK)
      {
         theApp.ExitInstance();
         exit(1);
      }
      else
      {
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
      CChildView::thisPtr->Invalidate();
   }

}

/*****************************************************************************/
/*	 Function called from MouseClick function for Save Button to save		 */
/*	 selected radio or large radio button informationand and then go to 	 */
/*	 previous submenu screen.												 */
/*****************************************************************************/

void HandleVGASaveButton(int Address)
{
   //Here Host command to set the information will be send to 332.
   unsigned char *data= new unsigned char[INTEGERLENGTH * 2];
   printf("in HandleVGASaveButton() \n");
   int length= GetRadioInfo(data);

   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);//Sending Host Command.
   delete []data;//coverity 11716
   if (response)
   { 
      //printf(" response ,");
      char ch=CHostCommand::AckNak();
      length = response->GetDataLength();//Getting Length.
      data = response->GetData();//Getting Data.
      if(ch == theApp.ACK)
      {
         //printf(" theApp.ACK ,");
         if(length!=0)
         {
            //printf(" length!=0 ,");
            int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
            if(Refresh)
            {
               theApp.GetSystemVariable();
            }
          
            //printf(" value = %d, ID =%d",value,ID);
            theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
            page_no=CChildView::thisPtr->menus.RemoveTail();
            theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
            {
               CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
            }
         }
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   else
      ERRORBEEP;   
}

void SendCommandForSave(int ID)
{
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();	
   unsigned char *data= new unsigned char[INTEGERLENGTH * 2];
   int length = GetRadioInfo(data);//Getting the information about Currently selected button.
   union 
   {
      short i;
      char c[2];
   } u;

   u.i= ID;

   data[1]=u.c[0];
   data[0]=u.c[1];	
   CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);//Sending Host Command.
   delete []data;//coverity 11715
   if (response)
   { 
      char ch=CHostCommand::AckNak();
      length = response->GetDataLength();//Getting Length.
      data = response->GetData();//Getting Data.
      if(ch == theApp.ACK)
      {
         if(length!=0)
         {
            
            theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
            page_no=CChildView::thisPtr->menus.RemoveTail();
            theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
            {
               CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
            }
         }
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   else
      ERRORBEEP;   
}

/*****************************************************************************/
/*	 Function called from MouseClick function for Save Button				 */
/*	 to get currently selected radio or large radio button information.      */
/*   Returns the number of bytes to send.Return value is useful in           */
/*   multiple choice radio menu with more than 16 radio buttons              */ 
/*****************************************************************************/
int GetRadioInfo(unsigned char *&data)
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   CVgaMenuItem * object =0;
   int count=0, RetVal = INTEGERLENGTH;
   //printf("in GetRadioInfo()");
   union {
      int Radio_value;
      char y[INTEGERLENGTH];
   } v;
   v.Radio_value = 0;

   data[2]=(char)v.y[1];
   data[3]=(char)v.y[0];

   menu1=theApp.MenuPointer;

   POSITION pos = menu1->items.GetHeadPosition();
   while (pos)
   {
      object= menu1->items.GetNext(pos);
      if((object->GetType())==(CVgaMenu::RADIO_BUTTON)
         ||(object->GetType())==(CVgaMenu::RADIOLARGE))
      {

         CVgaRadioButton *ptr=(CVgaRadioButton *)object;
         union 
         {
            short i;
            char c[2];
         } u;
         u.i= ptr->EnumID;
         data[1]=u.c[0];
         data[0]=u.c[1];

         if(object->GetSelectedRadio()) 
         {
            v.Radio_value = v.Radio_value|ptr->value;
            //printf(" v.Radio_value = %d \n",v.Radio_value);
            data[2]=(char)v.y[1];
            data[3]=(char)v.y[0];
         }
         count++;
      }
   }
   if(count > NUM_RADIO_BUTTONS_LONG_VAL) 
   {
      data[2]=(char)0;
      data[3]=(char)0;
      data[7]=(char)v.y[0];
      data[6]=(char)v.y[1];
      data[5]=(char)v.y[2];
      data[4]=(char)v.y[3];
      RetVal = (INTEGERLENGTH * 2);
   }

   //printf("\n %X,%X,%X,%X,%X,%X ",data[0],data[1],data[4],data[5],data[6],data[7]);
   return RetVal ;
}

void ResetSensorCalib(int ID)
{
   CChildView::LargeWaitingTime = true;
   SendCommandForVGAButtons(ID);
   CChildView::LargeWaitingTime = false;
}


/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 on Message Screen OK Button .              */
/**********************************************************************************/
void SendCommandForVGAButtons(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CChildView::LargeWaitingTime = true;
   CHostCommand * response = app->SendUiHostCommand(request);
   CChildView::LargeWaitingTime = false;
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID1=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);		
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Save,Recall,delete      */
/*  preset No.                                                                    */
/**********************************************************************************/

void SendCommandForVGAButtonsPreset(int Address)
{


   CVgaButton *ptr=(CVgaButton *)Address;
   int Temp = CChildView::CurrentPresetNum;
   printf("in SendCommandForVGAButtonsPreset\n");
   printf("CListBoxObject::CurrentPresetName.GetLength() = %d \n",CListBoxObject::CurrentPresetName.GetLength());
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
   { 
      CChildView::ErrorBeep();
      return;
   }
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value=GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         if(Refresh)
         {
            theApp.GetSystemVariable();
            CChildView::thisPtr->MaxPreset=1;				
         }
         int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
   }

   CChildView::CurrentPresetNum =Temp;
   printf("CChildView::CurrentPresetNum = %d\n",CChildView::CurrentPresetNum);
   CChildView::thisPtr->Invalidate();
}

void SendCommandForRecallPreset(int Address)
{
   printf("in SendCommandForRecallPreset\n");
   CVgaButton *ptr=(CVgaButton *)Address;
   int Temp = CChildView::CurrentPresetNum;
   printf("CListBoxObject::CurrentPresetName.GetLength() = %d \n",CListBoxObject::CurrentPresetName.GetLength());
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
   { 
      CChildView::ErrorBeep();
	  CChildView::thisPtr->RunResultScreen=false;
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->Invalidate();
      return;
   }
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value=GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CChildView::LargeWaitingTime = true;
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   CChildView::LargeWaitingTime =false;
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int Refresh=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         if(Refresh)
         {
            theApp.GetSystemVariable();
            CChildView::thisPtr->MaxPreset=1;			
         }
         int value=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         {
            CChildView::thisPtr->RunResultScreen=true;
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      else if(ch==theApp.NAK)
      {
		 CChildView::thisPtr->RunResultScreen=false;
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
         CChildView::thisPtr->Invalidate();
      }
      delete response;
   }

   //printf("CChildView::CurrentPresetNum = %d\n",CChildView::CurrentPresetNum);
   CChildView::CurrentPresetNum =Temp;

   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  verifying current       */
/*  preset No.                                                                    */
/**********************************************************************************/

void SendCommandForVerifyPreset(int ID)
{
   int Temp = CChildView::CurrentPresetNum;
   CVgaMenu * menu;
   if((CListBoxObject::CurrentPresetName.GetLength()<=1))
   { 
      CChildView::ErrorBeep();
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      return;
   }
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value=GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         theApp.GetSystemVariable(); 
		 data = data + 3;
		 length = length - 3;
         int ResponseType = CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
         menu=theApp.MenuPointer;
         CVgaMenuItem *object;

         POSITION pos1=menu->items.GetHeadPosition();
         while (pos1)
         {
            object= menu->items.GetNext(pos1);
            if(object->GetType()==CVgaMenu::VGAMsgScrnObject)
            {
               CMsgScreen *ptr=(CMsgScreen *)object;
               if(ResponseType==ptr->ResponseType)
               {
                  object->IsDraw=true;
               }
               else
               {
                  object->IsDraw=false;	
               }
            }
         }	
         CChildView::CurrentPresetNum =Temp;
         CChildView::thisPtr->Invalidate();
      }
      delete response;
   }
}

void SendCommandForVGAButtonsSavePreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i= ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;
   v.value=GlobalPresetSelection; 
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   CChildView::LargeWaitingTime = true;
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   CChildView::LargeWaitingTime = false;
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         //CChildView::thisPtr->SaveVQSData();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      }
      else if(ch==theApp.NAK)
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,(int)ptr,0);
      }
      delete response;
   }

   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  displaying Screen       */
/*  Setup Menu.                                                                   */
/**********************************************************************************/

void BuildLocalScreenSetupMenu(int Address)
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   bool ShowScreenSetup =true;
   CHostCommand * request = new CHostCommand(GetWeldingStatus,0,0);
   CHostCommand * response = app->SendUiHostCommand(request);
   //printf("in BuildLocalScreenSetupMenu response=%x\n",response);
   //it checks wc is in weld ready state,if it is not then screen setup will not appear
   if(response)
   {
      char ch=CHostCommand::AckNak();
     
      if(ch==theApp.NAK)
      {
         //printf("ch==theApp.NAK ");
         ShowScreenSetup=false;
      }
      delete response;
   }
   //printf("ShowScreenSetup=%x \n",ShowScreenSetup);
   if(!ShowScreenSetup)
   {
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      return;
   }
   CChildView::ScreenSetupFlag=true;
   CChildView::thisPtr->mutex.Lock();
   CVgaMenuItem * object =0;
   object = new CVgaScreenSetup();
   object->SetType(CVgaMenu::BottomMenu_Id);
   object->IsDraw=true;
   menu1->items.AddTail(object);
   POSITION pos = menu1->items.GetHeadPosition();
   object = menu1->items.GetHead();
   while(pos)
   {
      if(object->GetType()== CVgaMenu::BottomMenu_Id)			
      {
         object->IsDraw =false;
         object->RectShow=false;
      }
      object=menu1->items.GetNext(pos);
   }
   CChildView::thisPtr->Total_Objects=3;
   page_no=1;
   CChildView::LogoutButtonFlag = 0;
   CChildView::LoginButtonFlag = 0;
   CChildView::thisPtr->RecalculateMenuItemsLayout(MAXSCRNButton_Height,menu1);
   CChildView::thisPtr->mutex.Unlock();
   CChildView::thisPtr->Invalidate();
}

void ExitColorMenu(int Address)
{
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CVgaMenu * menu;
   page_no=1;
   {
      menu=theApp.MenuPointer;
      POSITION pos = menu->items.GetHeadPosition();
      CVgaMenuItem *object = menu->items.GetHead();
      while(pos)
      {
         if(object->GetType()== CVgaMenu::BottomMenu_Id)			
         {
            object->IsDraw =false;
            object->RectShow=false;
         }
         object=menu->items.GetNext(pos);
      }
   }
   CChildView::thisPtr->ScreenSetupFlag=true;
   CChildView::thisPtr->Invalidate();
}

void ButtonColor(int Address)
{
   CChildView::thisPtr->Button_Color++;
   if(CChildView::thisPtr->Button_Color>11)
      CChildView::thisPtr->Button_Color=1;
   /* checking if button color is the same as backgroung color or text color
   , if found then it is incremented */
   while((CChildView::thisPtr->Button_Color== CChildView::thisPtr->TextColor) || (CChildView::thisPtr->Button_Color == CChildView::thisPtr->Back_Color) || (CChildView::thisPtr->Button_Color== CChildView::thisPtr->TitleBarColor))
   {
      CChildView::thisPtr->Button_Color++;
      if(CChildView::thisPtr->Button_Color>11)
         CChildView::thisPtr->Button_Color=1;
   }
   CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void BackgroundColor(int Address)
{
   CChildView::thisPtr->Back_Color++;
   if(CChildView::thisPtr->Back_Color>11)
      CChildView::thisPtr->Back_Color=1;
   /* checking if Back_Color color is the same as button color or text color
   , if found then it is incremented */
   while((CChildView::thisPtr->Back_Color== CChildView::thisPtr->TextColor) || (CChildView::thisPtr->Back_Color == CChildView::thisPtr->Button_Color) 
      || (CChildView::thisPtr->Back_Color == CChildView::thisPtr->TitleBarColor) ||(CChildView::thisPtr->Back_Color == CChildView::thisPtr->Highlight_Color)
      || (CChildView::thisPtr->Back_Color == Black) || (CChildView::thisPtr->Back_Color == Red))
   {
      CChildView::thisPtr->Back_Color++;
      if(CChildView::thisPtr->Back_Color>11)
         CChildView::thisPtr->Back_Color=1;
   }
   CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void DefaultColor(int Address)
{
   CChildView::thisPtr->TextColor = Black;
   CChildView::thisPtr->TitleBarColor = Blue;
   CChildView::thisPtr->Button_Color= Gray;
   CChildView::thisPtr->Back_Color= White;
   CChildView::thisPtr->Highlight_Color=Green;
   CChildView::thisPtr->SaveData();
   //  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void TextColor(int Address)
{
   CChildView::thisPtr->TextColor++;
   if(CChildView::thisPtr->TextColor>11)
      CChildView::thisPtr->TextColor=1;
   /* checking if TextColor color is the same as button color or back color
   , if found then it is incremented */
   while((CChildView::thisPtr->TextColor== CChildView::thisPtr->Back_Color) || (CChildView::thisPtr->TextColor == CChildView::thisPtr->Button_Color) || (CChildView::thisPtr->TextColor == CChildView::thisPtr->Highlight_Color))
   {
      CChildView::thisPtr->TextColor++;
      if(CChildView::thisPtr->TextColor>11)
         CChildView::thisPtr->TextColor=1;
   }
   CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void TitleColor(int Address)
{
   CChildView::thisPtr->TitleBarColor++;
   if(CChildView::thisPtr->TitleBarColor>11)
      CChildView::thisPtr->TitleBarColor=1;
   /* checking if TitleBarColor color is the same as back color  or button color*/
   while((CChildView::thisPtr->TitleBarColor==CChildView::thisPtr->Back_Color) || 
      (CChildView::thisPtr->TitleBarColor==CChildView::thisPtr->Button_Color) || 
      (CChildView::thisPtr->TitleBarColor==White))
   {
      CChildView::thisPtr->TitleBarColor++;
      if(CChildView::thisPtr->TitleBarColor>11)
         CChildView::thisPtr->TitleBarColor=1;
   }
   CChildView::thisPtr->SaveData();
   CChildView::thisPtr->Invalidate();
}

void HighLightColor(int Address)
{
   CChildView::thisPtr->Highlight_Color++;
   if(CChildView::thisPtr->Highlight_Color>11)
      CChildView::thisPtr->Highlight_Color=2;
   /* checking if Highlight_Color color is the same as Back Color or black or white or red
   , if found then it is incremented */
   while((CChildView::thisPtr->Highlight_Color==CChildView::thisPtr->Back_Color)|| 
      (CChildView::thisPtr->Highlight_Color==Black)|| 
      (CChildView::thisPtr->Highlight_Color==White)||
      (CChildView::thisPtr->Highlight_Color==Red))
   {
      CChildView::thisPtr->Highlight_Color++;
      if(CChildView::thisPtr->Highlight_Color>11)
         CChildView::thisPtr->Highlight_Color=2;
   }
   CChildView::thisPtr->SaveData();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to WC & responsible for  Modifying current        */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/
void GetPreset(int ID,int PresetCount)
{
   int StringID = ID;
   int length =3;
   unsigned char data1[3];
   union
   {
      short i;
      char c[2];
   } u;
   u.i=StringID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   data1[2]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetEptrVariable_FunId,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         if(ID==!StringID)//If ID doesn't match, delete response
         {
            delete response;
            return ;
         }
         int Datatype=*data++;length--;
         bool Eptr;
         union 
         {
            bool i;
            char c;
         } u;
         u.c = *data++;length--;
         Eptr=u.i;
         if(Eptr==false)
         {
            delete response; 
         }
         else
         {
            CVgaMenu * menu1;
            {
               menu1=theApp.MenuPointer;
               POSITION pos = menu1->items.GetHeadPosition();
               CVgaMenuItem * item;
               while(pos)
               {
                  item = menu1->items.GetNext(pos);
                  if(item->GetType() == CVgaMenu::VGA_LISTBOX)
                  {
                     CListBoxObject *ptr=(CListBoxObject *)item;
                     if(length>1)
                     {
                        if(ptr->Type == PRESETINFOSCREEN)
                        {
                           for(int i=0;i<(ptr->TotalText-2);i++)
                           {
                              ptr->ListBoxText[i]="";
                              CString Str=" : "+ CVgaMenuItem::GetString(data, length);
                              ptr->ListBoxText[i]=ptr->PresetInfoText[i] + Str;
                              ptr->ListBoxText[i].TrimLeft();
                              ptr->ListBoxText[i].TrimRight();
                           }
                           int PresetVerify=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                           if(PresetVerify)
                           {
                              CString Str= ptr->PresetInfoText[ptr->TotalText-1] ;   
                              ptr->ListBoxText[ptr->TotalText-2] = Str ; 
                           }
                           else
                           {
                              CString Str = ptr->PresetInfoText[ptr->TotalText-2]; 
                              ptr->ListBoxText[ptr->TotalText-2] =  Str ;       
                           }
                           ptr->ListBoxText[ptr->TotalText-2].TrimLeft();
                           ptr->ListBoxText[ptr->TotalText-2].TrimRight();
                           ptr->ListBoxText [ptr->TotalText-1]="";
                        }
                        else
                        {
                           ptr->CurrentRunningSequencePreset=CChildView::CurrentSequencePreset ;
                           for(int i=0;i<ptr->TotalText;i++)
                           {
                              ptr->ListBoxText[i]=CVgaMenuItem::GetString(data, length);
                              ptr->ListBoxText[i].TrimLeft();
                              ptr->ListBoxText[i].TrimRight();
                           }
                        }
                     }
                     else
                     {
                        for(int i=0;i<ptr->TotalText;i++)
                        {
                           ptr->ListBoxText[i]="";
                        } 
                     } 
                  } 
               }
            }
         }
      }
   } 
}

void SendPresetNumberSetCommand(int ID)
{	
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value = GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      delete response;
   }
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetDownExecute(int ID)
{
   if(GlobalPresetSelection >= Max_Preset_Possible)
   {
      CChildView::thisPtr->ErrorBeep();
      return ;
   }
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;
   GlobalPresetSelection++;
   v.value = GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      delete response;
   }

   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetUpExecute(int ID)
{
   if(GlobalPresetSelection <=1)
   {
      CChildView::thisPtr->ErrorBeep();
      return ;
   }
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   GlobalPresetSelection--;
   v.value = GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         
         page_no=1;
         {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      delete response;
   }

   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetPageDownExecute(int ID)
{

   if(CChildView::thisPtr->CurrentPresetNum + MAX_PRESET_PER_SCREEN >= MaxPresetNum_InListBox)
   {
      CChildView::thisPtr->CurrentPresetNum = 1;
   }
   else
      CChildView::thisPtr->CurrentPresetNum = CChildView::thisPtr->CurrentPresetNum + MAX_PRESET_PER_SCREEN;

   if((GlobalPresetSelection + MAX_PRESET_PER_SCREEN) <= Max_Preset_Possible) 
      GlobalPresetSelection += MAX_PRESET_PER_SCREEN;
   //else 
   // 	GlobalPresetSelection = (Max_Preset_Possible - MAX_PRESET_PER_SCREEN);

   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value = GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ID1=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         {
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
         }
      }
      delete response;
   }

   CChildView::thisPtr->Invalidate();
}
/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Modifying current       */
/*  preset No Information in List Box.                                            */
/**********************************************************************************/

void PresetPageUpExecute(int ID)
{

   if(CChildView::thisPtr->CurrentPresetNum - MAX_PRESET_PER_SCREEN <= 1)
   {
      CChildView::thisPtr->CurrentPresetNum = 1;
   }
   else
      CChildView::thisPtr->CurrentPresetNum = CChildView::thisPtr->CurrentPresetNum - MAX_PRESET_PER_SCREEN;
   if(GlobalPresetSelection > MAX_PRESET_PER_SCREEN) 
      GlobalPresetSelection -= MAX_PRESET_PER_SCREEN;
   else 
      GlobalPresetSelection = 1;

   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value = GlobalPresetSelection;
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         
         page_no=1;
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      }
      delete response;
   }

   CChildView::thisPtr->Invalidate();
}
void SequenceUpButton(int Address)
{
   if(CChildView::thisPtr->CurrentSequencePreset<=1)
   {
      CChildView::thisPtr->ErrorBeep();
      return ;
   }
   CChildView::thisPtr->CurrentSequencePreset=	CChildView::thisPtr->CurrentSequencePreset-1;
   CChildView::thisPtr->Invalidate();
}

void PresetNumberExecute(int value)
{
   int num=value;
   int ID =PRESET_NUM_SELECT_ID;

   CChildView::thisPtr->CurrentPresetNum = 1;
   GlobalPresetSelection = num;
   int length =INTEGERLENGTH;
   unsigned char data1[5];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   union {
      int value;
      char y[INTEGERLENGTH];
   } v;

   v.value = GlobalPresetSelection;
   printf("current preset=%d\n",v.value);
   data1[2]=(char)v.y[1];
   data1[3]=(char)v.y[0];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   printf("command sent\n");
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
         page_no=1;
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      }
      delete response;
   }
   CChildView::LargeWaitingTime = true;
   GetPreset(ID,GlobalPresetSelection);
   CChildView::LargeWaitingTime = false;
   SendPresetNumberSetCommand(PRESET_INFO_SELECT_ID);
   CChildView::thisPtr->Invalidate();
}


void SequenceDownButton(int Address)
{
   if(CChildView::thisPtr->CurrentSequencePreset>=MaxSequencePresetNum_InListBox)
   {
      CChildView::thisPtr->ErrorBeep();
      return ;
   }


   if((CListBoxObject::CurrentSequencePresetName.GetLength()>2)||
      (CChildView::thisPtr->CurrentSequencePreset==0))
      CChildView::thisPtr->CurrentSequencePreset=CChildView::thisPtr->CurrentSequencePreset+1;
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  continue welding from   */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void ContinueSequence(int ID)
{
   if((CChildView::thisPtr->CurrentSequencePreset!=0))//&&(CVfdToggle::SequencingON))
   {
      CString temp;
      int num =0;
      CString ListBoxPreset=CListBoxObject::CurrentSequencePresetName;
      ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+2);
      if(ListBoxPreset.GetLength()>1)
      {
         num = CChildView::thisPtr->CurrentSequencePreset;
      }
      if(num!=0)
      {
         int length =INTEGERLENGTH;
         unsigned char data1[5];
         union 
         {
            short i;
            char c[2];
         } u;
         u.i=ID;
         data1[1]=u.c[0];
         data1[0]=u.c[1];

         union {
            int value;
            char y[INTEGERLENGTH];
         } v;
         v.value=(num-1);//object->GetRadio_Value();//getting radio value to char array.
         data1[2]=(char)v.y[1];
         data1[3]=(char)v.y[0];

         unsigned char * data = (unsigned char *) &data1[0];
         CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
         CHostCommand * response = app->SendUiHostCommand(request);
         if (response)
         {
            char ch=CHostCommand::AckNak();
            length = response->GetDataLength();//Getting Length.
            if(ch==theApp.ACK)//If Ack.
            {	
               page_no=1;
               CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
            }
            delete response;	
         }
      }
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  Insert                  */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void InsertEditSequencePreset(int ID)
{
   //printf(" InsertEditSequencePreset \n ");
   int TotalPreset=0;
   char PresetNum[66];//Reserve space for Two byte enum ID , tow byte preset number maximum presets 30
   CList<int,int>PresetNumbers;
   int i=0;
   UINT16 TempPresetNum;
   CVgaMenu * menu1;
   if((CListBoxObject::CurrentPresetName.GetLength()>1))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
      CVgaMenuItem * Object;
      while(pos)
      {
         Object = menu1->items.GetNext(pos);
         if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
         {
            CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
               for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
               {						
                  CString ListBoxPreset=obj->ListBoxText[Num];
                  //printf(" ListBoxPreset = %s \n",ListBoxPreset);
                  ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
                  if(ListBoxPreset.GetLength()>1)
                  {
                     TempPresetNum = _ttoi(ListBoxPreset);
                     PresetNumbers.AddTail(TempPresetNum);
                  }
               }
            }
         }
      }
      bool CommandSendRequired=false;
      if((PresetNumbers.GetCount()!=MaxSequencePresetNum_InListBox)&&(CChildView::thisPtr->CurrentSequencePreset))
      {
         pos = menu1->items.GetHeadPosition();
         while(pos)
         {
            Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
            {
               CListBoxObject *obj=(CListBoxObject*)Object;
               if(obj->Type==PRESETSCREEN)
               {
                  if(CChildView::thisPtr->CurrentPresetNum>0)
                  {							
                     int presetnum=_ttoi(obj->ListBoxText[CChildView::thisPtr->CurrentPresetNum-1]);
                     POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
                     if((PresetNumbers.GetCount()==CChildView::thisPtr->CurrentSequencePreset-1)
                        &&(CChildView::thisPtr->CurrentSequencePreset!=1))
                     {
                        PresetNumbers.AddTail(presetnum);
                     }
                     else if(CChildView::thisPtr->CurrentSequencePreset!=1)
                     {
                        PresetNumbers.InsertBefore(pos,presetnum);
                     }
                     else
                     {
                        PresetNumbers.AddHead(presetnum);
                     }
                     CommandSendRequired=true;
                  }
               }
            }
         }
      }

      if(CommandSendRequired)
      {
         int length = (int)PresetNumbers.GetCount();
         length = length * 2;//every preset num is two byte long
         length += 2;//2 byte enum ID 
         union 
         {
            short i;
            char c[2];
         } u;
         u.i=ID;
         PresetNum[1]=u.c[0];
         PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t+=2)
         {
            TempPresetNum = PresetNumbers.RemoveHead();
            PresetNum[t]= (char)(TempPresetNum >> 8);
            PresetNum[t + 1]= (char)(TempPresetNum);
         }
         length+=2;
         unsigned char * data = (unsigned char *) &PresetNum[0];
         CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
         CHostCommand * response = app->SendUiHostCommand(request);
         if (response)
         {
            char ch=CHostCommand::AckNak();
            length = response->GetDataLength();//Getting Length.
            if(ch==theApp.ACK)//If Ack.
            {
               int Temp= CChildView::thisPtr->CurrentPresetNum;
               int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
               {
                  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
               }
               CChildView::thisPtr->CurrentPresetNum=Temp;
               CChildView::CurrentSequencePreset=temp;
            }

            delete response;	
         }

      }
   }
   else
      CChildView::ErrorBeep();//gives the error beep
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  replacing               */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void ReplaceEditSequencePreset(int ID)
{
   int TotalPreset=0;
   char PresetNum[66];
   CList<int,int>PresetNumbers;	
   int i=0;
   UINT16 TempPresetNum;
   CVgaMenu * menu1;
   if((CListBoxObject::CurrentPresetName.GetLength()>1))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
      CVgaMenuItem * Object;
      while(pos)
      {
         Object = menu1->items.GetNext(pos);
         if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
         {
            CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
               for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
               {
                  CString ListBoxPreset=obj->ListBoxText[Num];
                  ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
                  if(ListBoxPreset.GetLength()>1)
                  {
                     TempPresetNum = _ttoi(ListBoxPreset);
                     PresetNumbers.AddTail(TempPresetNum);
                  }
               }
            }
         }
      }

      bool CommandSendRequired=false;
      if((!PresetNumbers.IsEmpty())&&(CChildView::thisPtr->CurrentSequencePreset)
         &&(CListBoxObject::CurrentSequencePresetName.GetLength()>2))
      {
         pos = menu1->items.GetHeadPosition();
         while(pos)
         {
            Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
            {
               CListBoxObject *obj=(CListBoxObject*)Object;
               if(obj->Type==PRESETSCREEN)
               {
                  if(CChildView::thisPtr->CurrentPresetNum>0)
                  {

                     int presetnum=_ttoi(obj->ListBoxText[CChildView::thisPtr->CurrentPresetNum-1]);
                     POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
                     PresetNumbers.SetAt(pos, presetnum);
                     CommandSendRequired=true;
                  }
               }
            }
         }
      }

      if(CommandSendRequired)
      {
         int length =PresetNumbers.GetCount();
         length = length * 2;//every preset num is two byte long
         length += 2;//2 byte enum ID 
         union 
         {
            short i;
            char c[2];
         } u;
         u.i=ID;
         PresetNum[1]=u.c[0];
         PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t+=2)
         {
            TempPresetNum = PresetNumbers.RemoveHead();
            PresetNum[t]= (char)(TempPresetNum >> 8);
            PresetNum[t + 1]= (char)(TempPresetNum);
         }
         length+=2;
         unsigned char * data = (unsigned char *) &PresetNum[0];
         CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
         CHostCommand * response = app->SendUiHostCommand(request);
         if (response)
         {
            char ch=CHostCommand::AckNak();
            length = response->GetDataLength();//Getting Length.
            if(ch==theApp.ACK)//If Ack.
            {
               int Temp= CChildView::thisPtr->CurrentPresetNum;
               int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
               {
                  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
               }
               CChildView::thisPtr->CurrentPresetNum=Temp;
               CChildView::CurrentSequencePreset=temp;
            }

            delete response;	
         }

      }
   }
    else
      CChildView::ErrorBeep();//gives the error beep
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & responsible for  delete                  */
/*  particular preset sequence.                                                   */
/**********************************************************************************/

void DeleteEditSequencePreset(int ID)
{
  
   char PresetNum[66];
   CList<int,int>PresetNumbers;
   UINT16 TempPresetNum;
  
   CVgaMenu * menu1;
   if((CChildView::thisPtr->CurrentSequencePreset>0)&&(CListBoxObject::CurrentSequencePresetName.GetLength()>2))
   {
      menu1=theApp.MenuPointer;
      POSITION pos = menu1->items.GetHeadPosition();
      CVgaMenuItem * Object;
      while(pos)
      {
         Object = menu1->items.GetNext(pos);
         if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
         {
            CListBoxObject *obj=(CListBoxObject*)Object;
            if(obj->Type==SEQUENCESCREEN)
            {
               for(int Num =0;Num<MaxSequencePresetNum_InListBox;Num++)
               {	
                  CString ListBoxPreset=obj->ListBoxText[Num];
                  ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
                  if(ListBoxPreset.GetLength()>1)
                  {
                     TempPresetNum = _ttoi(ListBoxPreset);
                     PresetNumbers.AddTail(TempPresetNum);
                  }
               }
            }
         }
      }
      bool CommandSendRequired=false;

      if(!PresetNumbers.IsEmpty())
      {
         pos = menu1->items.GetHeadPosition();
         while(pos)
         {
            Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
            {
               CListBoxObject *obj=(CListBoxObject*)Object;
               if(obj->Type==SEQUENCESCREEN)
               {
                  if(CChildView::thisPtr->CurrentSequencePreset>0)
                  {							
                     CString ListBoxPreset=obj->ListBoxText[CChildView::thisPtr->CurrentSequencePreset-1];
                     ListBoxPreset.Delete(0,ListBoxPreset.Find(L".",0)+1);
                     if(ListBoxPreset.GetLength()>1)
                     {							
                        POSITION pos =PresetNumbers.FindIndex(CChildView::thisPtr->CurrentSequencePreset-1);
                        PresetNumbers.RemoveAt(pos);
                        CommandSendRequired=true;
                     }
                  }

               }
            }
         }
      }

      if(CommandSendRequired)
      {
         int length = (int)PresetNumbers.GetCount();
         length = length * 2;//every preset num is two byte long
         length += 2;//2 byte enum ID 
         union 
         {
            short i;
            char c[2];
         } u;
         u.i=ID;
         PresetNum[1]=u.c[0];
         PresetNum[0]=u.c[1];
         PresetNum[2]=(char)PresetNumbers.GetCount();
         for(int t=3;t<=length;t+=2)
         {
            TempPresetNum = PresetNumbers.RemoveHead();
            PresetNum[t]= (char)(TempPresetNum >> 8);
            PresetNum[t + 1]= (char)(TempPresetNum);
         }
         length+=2;
         unsigned char * data = (unsigned char *) &PresetNum[0];
         CHostCommand * request = new CHostCommand(SetValue_FunID, data, length);
         CHostCommand * response = app->SendUiHostCommand(request);
         if (response)
         {
            char ch=CHostCommand::AckNak();
            length = response->GetDataLength();//Getting Length.
            if(ch==theApp.ACK)//If Ack.
            {
               int Temp= CChildView::thisPtr->CurrentPresetNum;
               int temp=CChildView::thisPtr->CurrentSequencePreset;
               page_no=1;
               {
                  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
               }
               CChildView::thisPtr->CurrentPresetNum=Temp;
               if((temp>1))
                  CChildView::CurrentSequencePreset=temp;
            }

            delete response;	
         }

      }
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function is responsible for displaying VQS Screen                        */
/*                                                                                */
/**********************************************************************************/

void ShowQualityScreen(int Address)
{
   CWnd *pWndPrev;
   // Determine if a window with the class name exists...
   if (pWndPrev = CWnd::FindWindow(NULL,_T("VQS")))
   {
      // If so, does it have any popups?
      pWndPrev->GetLastActivePopup();
      // Bring the application to the foreground
      pWndPrev->SetForegroundWindow();
   }

}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & On Ack, ErrorBeep()         */
/*  function is executed.                                                               */
/**********************************************************************************/

void SendCommandForButton(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         CChildView::thisPtr->ErrorBeep();
      }
      else if(ch==theApp.NAK)
      {
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & builds Menu Items.          */
/*                                                                                */
/**********************************************************************************/

void SendCommandForButtons(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
		  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	  else if(ch==theApp.NAK)
		  CChildView::thisPtr->ProcessNak(data,length,0,0);
	  delete response;
   }
   CChildView::thisPtr->Invalidate();
}

//
void SendCommandForDigitalOutput(int Address)
{
   int ID = Address;
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * Object;
   CHostCommand * request ;
   CHostCommand * response ;
   int length = INTEGERLENGTH;
   union GetSetUser un;
   unsigned char data1[4];
   un.struct1.s1 = ID;
   data1[1]=un.struct2.c[0];
   data1[0]=un.struct2.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   bool oldSate;
   while(pos)
   {
      Object = menu1->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGA_Button_OBJECT)
      {
         CVgaButton *obj=(CVgaButton*)Object;
         if(obj->EnumID == Address)
         {

            //If we dont get response or we get nak then no need to change the state.Restore old state. 
            oldSate = obj->Activated;
            if(obj->Activated == true)
               obj->Activated = false;
            else
               obj->Activated = true;

            un.struct1.s2 = (short)obj->Activated;
            data1[3]=un.struct2.c[2];
            data1[2]=un.struct2.c[3]; 
            request = new CHostCommand(SetValue_FunID,data,length);
            response = app->SendUiHostCommand(request);
            if(response)
            {
               char ch=CHostCommand::AckNak();
               data = response->GetData();
               length = response->GetDataLength();					
               if(ch==theApp.ACK)
               {
                  CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
               }
               else if(ch==theApp.NAK)
               {
                  CChildView::thisPtr->ProcessNak(data,length,0,0);
                  obj->Activated = oldSate;
               }
               delete response;

            }
            else
            {
               obj->Activated = oldSate;
            }
            printf(" obj->Activated = %d EnumID = %d \n",obj->Activated,obj->EnumID);
         }
         //printf("EnumID = %d \n", obj->EnumID);

      } 
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID & starts BottomHalf Timer     */
/*  for Scan start.                                                               */
/**********************************************************************************/
void StartScan(int ID)
{
   CVgaMenu * menu1,*menu;
   menu1=theApp.MenuPointer ;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * object;
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         printf("\n start scan cmd 4 %d %d", SetValue_FunID, ID);
         CChildView::thisPtr->DisableFlag=true;
         while (pos)
         {
            object = menu1->items.GetNext(pos);
            if(object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)object;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               if(theApp.menus.Lookup(obj->submenu, menu))
               {
                  POSITION pos1 = menu->items.GetHeadPosition();
                  while (pos1)
                  {
                     object = menu->items.GetNext(pos1);
                     if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                     {
                        CVgaButton *ptr=(CVgaButton *)object;
                        if(ptr->argument==".")
                        {
                           ptr->text=CChildView::ScanString;
                           break;
                        }
                     }
                  }
               }

            }
         }

      }
      else if(ch==theApp.NAK)
      {
         printf("\n start scan cmd 5 %d %d", SetValue_FunID, ID);
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 with Menu ID, executes some function on    */
/*  controller side.                                                              */
/**********************************************************************************/

void WeldRetract(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      delete response;
   }
   CChildView::thisPtr->Invalidate();

}

/**********************************************************************************/
/*                                                                                */
/*  This function Sends command to 332 for Testing Menus items.                   */
/*  .                                                                             */
/**********************************************************************************/

void SendCommandForTestingMenu(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      CChildView::thisPtr->menusname.RemoveTail();
      CChildView::thisPtr->menus.RemoveTail();
      CChildView::thisPtr->menupointers.RemoveTail();
      delete response;
   }
   CChildView::thisPtr->Invalidate();

}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & stops horn scan, displays Message        */
/*  accordingly.                                                                  */
/**********************************************************************************/

void HornScanAbort(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   CChildView::thisPtr->DisableFlag=false;
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & build menu items according to type of    */
/*  actuator.                                                                     */
/**********************************************************************************/
void SendSpecialMenuCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();	
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
}



/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 & build menu items according to type of    */
/*  actuator.                                                                     */
/**********************************************************************************/
void SendHornDownCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   printf("in SendHornDownCommand ");

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   printf(",response=%x ",response);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
    
      if(ch==theApp.ACK)
      {
         printf(",ch==theApp.ACK"); 
         CBottomHalf::HornDownScreenPresent=true;
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CString MenuName="";
         CVgaMenu * menu1=theApp.MenuPointer;
         POSITION pos = menu1->items.GetHeadPosition();
         CVgaMenuItem * Object;
         while(pos)
         {
            Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)Object;
               MenuName=obj->submenu;
               CVgaMenu * menu;
               if (theApp.menus.Lookup(MenuName, menu))
               {
                  CBottomHalf::BottomMenuPointer=menu;
               }
               CChildView::thisPtr->MenuNameID=MenuName;
               CBottomHalf::BottomHalfId=obj->EnumID;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               break;
            }
         }
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         printf(",ch==theApp.NAK"); 	   
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CChildView::thisPtr->ProcessNak(data,length,0,0);
         CChildView::thisPtr->Invalidate();
      }
      delete response;
   }
}

void HistoryLeftButton(int Address)
{
   if(CWeldingHistory::thisHisPtr->LeftMostParameter>1)
      CWeldingHistory::thisHisPtr->LeftMostParameter--;
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void HistoryRightButton(int Address)
{
   if(CWeldingHistory::thisHisPtr->LeftMostParameter < (int)(HisParameterCounts -3))
   {
      CWeldingHistory::thisHisPtr->LeftMostParameter++;
   } 
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void AlarmLogRightButton(int Address)
{
   if(CAlarmLog::thisHisPtr->LeftMostParameter<(CAlarmLog::thisHisPtr->TotalColoumn)-4)
      CAlarmLog::thisHisPtr->LeftMostParameter++;
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void AlarmLogLeftButton(int Address)
{
   if(CAlarmLog::thisHisPtr->LeftMostParameter>1)
      CAlarmLog::thisHisPtr->LeftMostParameter--;
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void AlarmScreenUpButton(int Address)
{
   if(CAlarmLog::thisHisPtr->TopMostData>AlarmLogMaxCyclePerScreen)
   {
      (CAlarmLog::thisHisPtr->TopMostData)-=AlarmLogMaxCyclePerScreen;
      CAlarmLog::thisHisPtr->SelectedAlarmData=1;
   }
   else if(CAlarmLog::thisHisPtr->TopMostData!=1)
   {
      CAlarmLog::thisHisPtr->TopMostData=1;
      CAlarmLog::thisHisPtr->SelectedAlarmData=1;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void AlarmScreenDownButton(int Address)
{
   if(((CAlarmLog::thisHisPtr->TotalCycle)> AlarmLogMaxCyclePerScreen)&&
      ((CAlarmLog::thisHisPtr->TopMostData)+ AlarmLogMaxCyclePerScreen <=(CAlarmLog::thisHisPtr->TotalCycle)))
   {
      (CAlarmLog::thisHisPtr->TopMostData)+=AlarmLogMaxCyclePerScreen;
      CAlarmLog::thisHisPtr->SelectedAlarmData=1;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void AlarmUpButton(int Address)
{
   if((CAlarmLog::thisHisPtr->SelectedAlarmData)==1)
   {
      if((CAlarmLog::thisHisPtr->TopMostData)>1)
      {
         CAlarmLog::thisHisPtr->TopMostData -= AlarmLogMaxCyclePerScreen;
         CAlarmLog::thisHisPtr->SelectedAlarmData = AlarmLogMaxCyclePerScreen;
      }
      else
         CChildView::ErrorBeep();
   }
   else
      CAlarmLog::thisHisPtr->SelectedAlarmData--;
   CChildView::thisPtr->Invalidate();
}

void AlarmDownButton(int Address)
{
   if((CAlarmLog::thisHisPtr->SelectedAlarmData)==AlarmLogMaxCyclePerScreen)
   {
      if(((CAlarmLog::thisHisPtr->TotalCycle)-(CAlarmLog::thisHisPtr->TopMostData))>=AlarmLogMaxCyclePerScreen)
      {
         CAlarmLog::thisHisPtr->TopMostData += AlarmLogMaxCyclePerScreen;
         CAlarmLog::thisHisPtr->SelectedAlarmData = 1;
      }
      else
         CChildView::ErrorBeep();
   }
   else
      if((((CAlarmLog::thisHisPtr->SelectedAlarmData)+(CAlarmLog::thisHisPtr->TopMostData))<=(CAlarmLog::thisHisPtr->TotalCycle))
         &&((CAlarmLog::thisHisPtr->SelectedAlarmData)!=AlarmLogMaxCyclePerScreen))
         CAlarmLog::thisHisPtr->SelectedAlarmData++;
      else
         CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void EventLogRightButton(int Address)
{
   if(CEventLog::thisHisPtr->LeftMostParameter<(CEventLog::thisHisPtr->TotalColoumn)-4)
      CEventLog::thisHisPtr->LeftMostParameter++;
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void EventLogLeftButton(int Address)
{
   if(CEventLog::thisHisPtr->LeftMostParameter>1)
      CEventLog::thisHisPtr->LeftMostParameter--;
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void EventUpButton(int Address)
{
   if(CEventLog::thisHisPtr->SelectedEventData == 1)
   {
      if(CEventLog::thisHisPtr->TopMostData > 1)
      {
         CEventLog::thisHisPtr->TopMostData -= MAX_EVENT_OBJECTS_PER_PAGE;
         CEventLog::thisHisPtr->SelectedEventData = MAX_EVENT_OBJECTS_PER_PAGE;
      }
      else
         CChildView::ErrorBeep();
   }
   else
      CEventLog::thisHisPtr->SelectedEventData--;
   CChildView::thisPtr->Invalidate();
}

void EventScreenUpButton(int Address)
{
   if(CEventLog::thisHisPtr->TopMostData > MAX_EVENT_OBJECTS_PER_PAGE)
   {
      (CEventLog::thisHisPtr->TopMostData) -= MAX_EVENT_OBJECTS_PER_PAGE;
      CEventLog::thisHisPtr->SelectedEventData = 1;
   }
   else if(CEventLog::thisHisPtr->TopMostData != 1)
   {
      CEventLog::thisHisPtr->TopMostData = 1;
      CEventLog::thisHisPtr->SelectedEventData = 1;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

void EventDownButton(int Address)
{
	if((CEventLog::thisHisPtr->SelectedEventData)==MAX_EVENT_OBJECTS_PER_PAGE)
	{
		if((CEventLog::TotalCycles - CEventLog::thisHisPtr->TopMostData) >= MAX_EVENT_OBJECTS_PER_PAGE)
		{
			CEventLog::thisHisPtr->TopMostData += MAX_EVENT_OBJECTS_PER_PAGE;
			CEventLog::thisHisPtr->SelectedEventData = 1;
		}
		else
			CChildView::ErrorBeep();
	}
	else
		if(((CEventLog::thisHisPtr->SelectedEventData+CEventLog::thisHisPtr->TopMostData) <= CEventLog::TotalCycles)
			&&((CEventLog::thisHisPtr->SelectedEventData) != MAX_EVENT_OBJECTS_PER_PAGE))
			CEventLog::thisHisPtr->SelectedEventData++;
		else
			CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void EventScreenDownButton(int Address)
{
	if(((CEventLog::TotalCycles) > MAX_EVENT_OBJECTS_PER_PAGE)&&
		((CEventLog::thisHisPtr->TopMostData)+ MAX_EVENT_OBJECTS_PER_PAGE <=(CEventLog::TotalCycles)))
	{
		(CEventLog::thisHisPtr->TopMostData)+=MAX_EVENT_OBJECTS_PER_PAGE;
		CEventLog::thisHisPtr->SelectedEventData=1;
	}
	else
		CChildView::ErrorBeep();
	CChildView::thisPtr->Invalidate();
}

void HistoryScreenUpButton(int Address)
{
   int Count = 0 ;
   DownFlagErrorBeep = false;
   bool FlagWrap = false;
   TotalDisplayWeldData = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;  //index of total overwrite
   (CWeldingHistory::thisHisPtr->TopMostData)-=MAXCYCLEPERSCREEN;
   CWeldingHistory::thisHisPtr->SelectedWeldData=1;
   if(WrapAroundWeldFlag)
   {

      //if(FlagInitialScreen)  //To disable the Up button just after the initial screen
      // UpFlagErrorBeep = true;
      if(!UpFlagErrorBeep){
         TotalWeldCountRead = TotalWeldCountRead - MAXCYCLEPERSCREEN; //Status Counter
         PreviousIndexWeld  = CurrentCountToReadWeld;   //To store the address at the temporary variable.
      }

      if((!UpFlagErrorBeep) && CurrentCountToReadWeld <= CChildView::Max_Allowed_Weld_Log )  //Now read the next eight data
         CurrentCountToReadWeld = CurrentCountToReadWeld + MAXCYCLEPERSCREEN;

      if((!UpFlagErrorBeep) &&(TotalDisplayWeldData < MAXCYCLEPERSCREEN) && (TotalDisplayWeldData > 0))  //End Of UPbutton and store the previous address
      {
         if(CurrentCountToReadWeld > CChildView::Max_Allowed_Weld_Log){
            CurrentCountToReadWeld = PreviousIndexWeld;
            FlagReachedStart = true;
            FlagWrap =true;
         }
      }
      else
      {
         if((!UpFlagErrorBeep) && CurrentCountToReadWeld > CChildView::Max_Allowed_Weld_Log){   //110 case
            CurrentCountToReadWeld = CurrentCountToReadWeld - CChildView::Max_Allowed_Weld_Log;
            if(TotalDisplayWeldData == 0)  //200case
               UpFlagErrorBeep = true;
         }
      }


      if((!UpFlagErrorBeep) && CurrentCountToReadWeld < MAXCYCLEPERSCREEN) // for  overlap only
      {
         while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
            delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();
         int Present = CurrentCountToReadWeld;		
         Count = CurrentCountToReadWeld;
         PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
         Count = MAXCYCLEPERSCREEN- CurrentCountToReadWeld;
         CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log - Count;
         PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, false);  //to write in tail
         CurrentCountToReadWeld = Present;

      }

      else if( CurrentCountToReadWeld >= MAXCYCLEPERSCREEN && (!UpFlagErrorBeep)) 
      {
         while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
            delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();

         if  (((CChildView::Max_Allowed_Weld_Log - CurrentCountToReadWeld) < MAXCYCLEPERSCREEN) && (FlagWrap))   // check the  initial screen Wrap(101 case)
         { 
            int temp = 0;
            temp = CurrentCountToReadWeld;
            CurrentCountToReadWeld = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;
            Count = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;
            PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            Count = MAXCYCLEPERSCREEN -  CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;
            CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log ;     
            PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, false);  //to write in tail
            CurrentCountToReadWeld = temp + MAXCYCLEPERSCREEN;
         }
         else
         {
            Count = MAXCYCLEPERSCREEN;   
            PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
         }
      }

      if((CurrentCountToReadWeld == TotalDisplayWeldData) || (TotalWeldCountRead <= 0) && (FlagWrap))    //to tackle the continuous pressing of forward button
      {
         UpFlagErrorBeep = true;
         TotalWeldCountRead = 0;
      }

      if(UpFlagErrorBeep)  //for error beep
         CChildView::ErrorBeep();
   }   //End of Wrap Condition

   else
   {
      if((CurrentCountToReadWeld < TotalDataInFile) && !UpFlagErrorBeep)
      {
         Count = MAXCYCLEPERSCREEN;

         if((CurrentCountToReadWeld+Count) < (TotalDataInFile))
         {
            CurrentCountToReadWeld+=Count;
            CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveAll();
            if(WeldDataLogFile == false) {
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            }
            else {
               CUSBFolder::thisPointer->PrepareUSBHistoryList("",NULL,CurrentCountToReadWeld,Count);
            }
         }
         else if ((CurrentCountToReadWeld+Count) >= TotalDataInFile)
         {
            Count = TotalDataInFile - CurrentCountToReadWeld;
            CurrentCountToReadWeld +=Count;
            CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveAll();
            if(WeldDataLogFile == false) {
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            }
            else {
               CUSBFolder::thisPointer->PrepareUSBHistoryList("",NULL,CurrentCountToReadWeld,Count);
            }
            if(Address >= 0)
               CWeldingHistory::thisHisPtr->SelectedWeldData = 1;//MAXCYCLEPERSCREEN;
            else
               CWeldingHistory::thisHisPtr->SelectedWeldData = MAXCYCLEPERSCREEN;
            UpFlagErrorBeep = true;
         }
      }
      else if(CWeldingHistory::thisHisPtr->TopMostData!=1)
      {
         CWeldingHistory::thisHisPtr->TopMostData=1;
         CWeldingHistory::thisHisPtr->SelectedWeldData=1;
      }
      else
      {
         CChildView::ErrorBeep();
         CWeldingHistory::thisHisPtr->SelectedWeldData=1;
      }
   }
   CChildView::thisPtr->Invalidate();
}

void HistoryScreenDownButton(int Address)
{
   int Count = 0 ;
   int StartAddForUP = 0;
   int Diff = 0 ;
   bool FlagStop = false ;
   UpFlagErrorBeep = false;
   FlagInitialScreen = false;
   TotalDisplayWeldData = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount; 
   (CWeldingHistory::thisHisPtr->TopMostData)=1;
   CWeldingHistory::thisHisPtr->SelectedWeldData=1;
   if(WrapAroundWeldFlag)
   {

      if(!DownFlagErrorBeep)
         TotalWeldCountRead = TotalWeldCountRead + MAXCYCLEPERSCREEN; //Status Counter

      if((TotalWeldCountRead >= CChildView::Max_Allowed_Weld_Log))    //for Non Boundry case
      {
         DownFlagErrorBeep = true;
         TotalWeldCountRead = TotalWeldCountRead - MAXCYCLEPERSCREEN;	  
      }

      if((!DownFlagErrorBeep) && CurrentCountToReadWeld >= MAXCYCLEPERSCREEN)  //Now read the next eight data
         CurrentCountToReadWeld = CurrentCountToReadWeld - MAXCYCLEPERSCREEN;  

      if((!DownFlagErrorBeep) && (CurrentCountToReadWeld < MAXCYCLEPERSCREEN) && (CurrentCountToReadWeld > 0)) // for drop down overlap only
      {
         while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
            delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();
         if(TotalDisplayWeldData < MAXCYCLEPERSCREEN )  //for case 101-107
         {
            if((CChildView::Max_Allowed_Weld_Log - TotalWeldCountRead) < 16)   //check it
            {                                                                       //to stop at the end of down
               Count = CurrentCountToReadWeld - TotalDisplayWeldData;
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
               DownFlagErrorBeep = true;
            }
            else
            {
               Count = CurrentCountToReadWeld;
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
               Count = MAXCYCLEPERSCREEN - CurrentCountToReadWeld;
               CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log ;
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, false);  //to write in tail
               CurrentCountToReadWeld = CurrentCountToReadWeld - Count + MAXCYCLEPERSCREEN;  
            }

         }
         else         //for case 194
         {
            Count = CurrentCountToReadWeld;
            StartAddForUP = CurrentCountToReadWeld;
            PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            Count = MAXCYCLEPERSCREEN - CurrentCountToReadWeld;
            CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log ;
            Diff =  CurrentCountToReadWeld -TotalDisplayWeldData;
            if((Diff <=7) &&(CurrentCountToReadWeld > TotalDisplayWeldData))    // 199 case
            {
               Count = Diff;
               DownFlagErrorBeep = true;  
               FlagStop = true;
            }
            PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, false);  //to write in tail
            if(FlagStop)
               CurrentCountToReadWeld = StartAddForUP ;  //to provide the base add for up button
            else
               CurrentCountToReadWeld = CurrentCountToReadWeld - Count + MAXCYCLEPERSCREEN;  
         }

      }
      else if( CurrentCountToReadWeld >= MAXCYCLEPERSCREEN && (!DownFlagErrorBeep))
      {
         while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
            delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();
         Count = MAXCYCLEPERSCREEN; 
         if(TotalDisplayWeldData < MAXCYCLEPERSCREEN )
         {
            if(CurrentCountToReadWeld - TotalDisplayWeldData < MAXCYCLEPERSCREEN ){  //To stop at the end 104 case
               Count = CurrentCountToReadWeld - TotalDisplayWeldData;
               DownFlagErrorBeep = true;
            }
         }
         else
         {
            Diff =  CurrentCountToReadWeld -TotalDisplayWeldData;
            if((Diff <=7) &&(CurrentCountToReadWeld > TotalDisplayWeldData)){    // 116 case
               Count = Diff;
               DownFlagErrorBeep = true;   
            }
         }
         PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
      }
      else if((!DownFlagErrorBeep) && (CurrentCountToReadWeld == 0) ) // for Multiple of 8 case
      {
         while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
            delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();
         CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log; 
         Count = MAXCYCLEPERSCREEN;
         PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
         //CurrentCountToReadWeld = CurrentCountToReadWeld - Count ; 
      }
      if(DownFlagErrorBeep)  //for error beep
         CChildView::ErrorBeep();


   } //End of Wrap Around routine

   else
   {
      if(!DownFlagErrorBeep && (CurrentCountToReadWeld>0))
      {
         Count = MAXCYCLEPERSCREEN;
         if((CurrentCountToReadWeld-Count) >= MAXCYCLEPERSCREEN)
         {
            CurrentCountToReadWeld-=MAXCYCLEPERSCREEN;
            CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveAll();
            if(WeldDataLogFile == false) {
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            }
            else {
               CUSBFolder::thisPointer->PrepareUSBHistoryList("",NULL,CurrentCountToReadWeld,Count);
            }
         }
         else if (((CurrentCountToReadWeld-Count) < MAXCYCLEPERSCREEN) && ((CurrentCountToReadWeld-Count) > 0))
         {
            CurrentCountToReadWeld = CurrentCountToReadWeld - Count;
            Count = CurrentCountToReadWeld;
            CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveAll();
            if(WeldDataLogFile == false) {
               PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
            }
            else {
               CUSBFolder::thisPointer->PrepareUSBHistoryList("",NULL,CurrentCountToReadWeld,Count);
            }
            DownFlagErrorBeep = true;
         }
      }
      else
         CChildView::ErrorBeep();
   }
   CChildView::thisPtr->Invalidate();
}

/*Function executed when single up is clicked in power supply weld history screen*/
void HistoryUpButton(int Address)
{
   if((CWeldingHistory::thisHisPtr->SelectedWeldData)==1)
   {
      HistoryScreenUpButton(-1);
      if(!UpFlagErrorBeep)
         CWeldingHistory::thisHisPtr->SelectedWeldData = MAXCYCLEPERSCREEN;
   }
   else if((CWeldingHistory::thisHisPtr->SelectedWeldData)>1)
      CWeldingHistory::thisHisPtr->SelectedWeldData--;
   CChildView::thisPtr->Invalidate();

}

void HistoryDownButton(int Address)
{
   if((CWeldingHistory::thisHisPtr->SelectedWeldData)==MAXCYCLEPERSCREEN)
   {
      HistoryScreenDownButton(1);
      CWeldingHistory::thisHisPtr->SelectedWeldData = 1;
   }

   else if(((CWeldingHistory::thisHisPtr->SelectedWeldData)!=MAXCYCLEPERSCREEN) \
      && (CWeldingHistory::thisHisPtr->SelectedWeldData < CurrentCountToReadWeld) && DownFlagErrorBeep == false)
   {
      if((DownFlagErrorBeep))
      {
         if(CurrentCountToReadWeld > CWeldingHistory::thisHisPtr->SelectedWeldData)
            CWeldingHistory::thisHisPtr->SelectedWeldData++;
         else
            CChildView::ErrorBeep();
      }
      else
         CWeldingHistory::thisHisPtr->SelectedWeldData++;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}


void ShowPowerSupplyMessageScreen(int Address)
{
   HisParameterCounts = 0;
   CWeldingHistory::LeftMostParameter = 1;
   UINT32 HisMask = 0;
   if(CChildView::ControlLevel >= LEVEL_C)	
      HisMask = HistorySetUp | MANDATORY_PARAM_MASK_LEVELC;   
   else
      HisMask = HistorySetUp | MANDATORY_PARAM_MASK_BELOWLEVELC;   
   for(int i = 0; i < MAX_VIEW_HISTORYPARAM; i++)
   {
      if((HisMask & (1 << i)) == (1 << i))
      {
         HisParameterMap[HisParameterCounts] = CChildView::thisPtr->Parameter_ID[i];
         HisParameterCounts++;
      }
   }
   if((CWeldingHistory::LeftMostParameter + 3) > (int)HisParameterCounts)
      CWeldingHistory::LeftMostParameter = 1;

   //Menu has two message screen.Response value will indicate which message to be displayed
   //If WeldHistory log file has no records then show "no valid data" otjerwise show
   //"please wait".
   int ResponseType = 0 ;
   if( CWeldingHistory::thisHisPtr->TotalDataInFile > 0)
      ResponseType = 1;
   else
      ResponseType = 0;
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   WeldDataLogFile = false;
   TRY
   {
      CString Temp;
      CVgaMenuItem *object;
      CVgaButton *ptr=(CVgaButton *)Address;
      CChildView::thisPtr->EnableUSBGraph=false;
      POSITION pos1=menu->items.GetHeadPosition();
      while (pos1)
      {
         object= menu->items.GetNext(pos1);
         if(object->GetType()==CVgaMenu::VGAMsgScrnObject)
         {
            CMsgScreen *ptr=(CMsgScreen *)object;
            if(ptr->ResponseType == ResponseType)
            {
               Temp=object->text;
               CDC *pDC=CChildView::thisPtr->GetDc();
               CChildView::thisPtr->EnableWindow(false);

               /*Drawing Message Rectangle in specified color*/
               CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
               CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

               /*Drawing Message Text*/
               CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Temp,true);
               CChildView::thisPtr->ReleaseDc(pDC);	
               CChildView::thisPtr->DisableFlag=true;
               CChildView::thisPtr->InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
               CChildView::thisPtr->EnableWindow(true);
            }
         }
         else if(object->GetType()==CVgaMenu::VGAHISTORYOBJECT)
         {
            CWeldingHistory *Runptr=(CWeldingHistory *)object;
            while(Runptr->USBWeldHistoryList.GetCount()>0)
            {
               CHistoryData *obj1 = Runptr->USBWeldHistoryList.RemoveHead();//delete
               free(obj1);
            }
            while(Runptr->WeldHistoryList.GetCount()>0)
            {
               delete Runptr->WeldHistoryList.RemoveHead();
            }
            TotalDisplayWeldData = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;  //index of total overwrite
            TotalDataInFile = CWeldingHistory::thisHisPtr->TotalDataInFile;  //maximum count of data
            int Count = 0;
            TotalWeldCountRead = 0;
            UpFlagErrorBeep = true;
            DownFlagErrorBeep = false;
            if(CChildView::thisPtr->MemoryfullCont_Stop)
            {
               if((TotalDataInFile > CChildView::Max_Allowed_Weld_Log) )
                  WrapAroundWeldFlag = true;
            }


            if(TotalDataInFile <= CChildView::Max_Allowed_Weld_Log) // it does not matter the bit is true or false we need to read accordingly
            {
               if(TotalDataInFile > MAXCYCLEPERSCREEN)
               {
                  CurrentCountToReadWeld = TotalDataInFile;
                  Count = MAXCYCLEPERSCREEN;
                  PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
                  //CurrentCountToReadWeld = CurrentCountToReadWeld + Count;   // take note
               }
               else
               {
                  CurrentCountToReadWeld = TotalDataInFile;
                  Count = TotalDataInFile;
                  DownFlagErrorBeep = true;
                  PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
               }	
               CWeldingHistory::thisHisPtr->SelectedWeldData = 1;
               //CurrentCountToReadWeld = CurrentCountToReadWeld + Count;   // take note

            }
            else // Overwrite has happened
            {
               CurrentCountToReadWeld = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;

               if((CurrentCountToReadWeld !=0) && (CurrentCountToReadWeld < MAXCYCLEPERSCREEN))
               {
                  while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
                     delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();

                  Count = CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;
                  PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
                  Count = MAXCYCLEPERSCREEN -  CWeldingHistory::thisHisPtr->CurrentDisplayWeldCount;
                  CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log ;     
                  PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, false);  //to write in tail
                  CurrentCountToReadWeld = CurrentCountToReadWeld - Count ;  
                  InitialScreenOverlap = true; //flag set to mark 1st overwrite.
               }
               else   //normal case
               {
                  Count = MAXCYCLEPERSCREEN;
                  if(CurrentCountToReadWeld == 0)
                     CurrentCountToReadWeld = CChildView::Max_Allowed_Weld_Log;
                  while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
                     delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();
                  PrepareListFromLog(_T("WeldData.log"),Count, CurrentCountToReadWeld, false, true);//to write in head
                  CurrentCountToReadWeld = CurrentCountToReadWeld - Count ;
               }

               CurrentCountToReadWeld = CurrentCountToReadWeld + MAXCYCLEPERSCREEN; //To compensate the effect, as i am Decrementing the index at the start of butndown pressed.
               PreviousIndexWeld = CurrentCountToReadWeld;
               CWeldingHistory::thisHisPtr->SelectedWeldData = 1;
            }


         }
      } 
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
      CChildView::thisPtr->Invalidate();
   }
   CATCH_ALL(E)
   {
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The error: ");
      x += szCause;
      //AfxMsgBox(x);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
      CChildView::thisPtr->Invalidate();
   }
   END_CATCH_ALL
}

void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph)
{
   int i=0;
   Graph->GraphData.GraphColour=*data++;length--;
   for(i=0;i<20;i++)
      Graph->GraphData.CycleCount[i]='\0';
   CString str=CChildView::thisPtr->CycleCountString;//CVgaMenuItem ::LinearSearch(Graph->CycleCountID);
   _tcscpy(Graph->GraphData.CycleCount,str.Mid(0,19));
   Graph->SetGraphRequestValue(Graph->GraphData.graph_type);
   for( i=0;i<20;i++)
      Graph->GraphData.SystemPressure[i]='\0';
   Graph->AlreadyPrinted=false;
   Graph->Lang_Index=0;//CChildView::Language_Index;
   Graph->No_Graph_String=" ";
   CVgaDrawGraph::GraphCount++;
   Graph->GraphData.GraphNum=CVgaDrawGraph::GraphCount;
   Graph->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   for(short len=0;len<Graph->GraphData.DataLength;len++)
   {
      Graph->GraphData.graphdata[len]=(short)*data++;
      length--;
   }
   Graph->Store_VData_HData(data,length);
   Graph->StoreTickData(data,length);
   for(int q=0;q<7;q++)
   {
      Graph->GraphData.TickData[q]=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);	

   }

   union{ 
      int i;
      bool ExtraByte;
   }u;
   u.i=*data++;
   Graph->GraphData.ExtraText=u.ExtraByte; 
   length--;
   u.i=*data++;
   Graph->GraphData.ManualStr=u.ExtraByte;
   length--;
   TCHAR TemproryCycle[20];
   CVgaMenuItem::GetCharString (data,length,TemproryCycle);
   i=0;
   while(Graph->GraphData.CycleCount[i]!='\0')
   {
      i++;
   }
   for(int j=0;i<19;i++,j++)
   {
      Graph->GraphData.CycleCount[i]=TemproryCycle[j];
   }
   Graph->GraphData.CycleCount[i]='\0';
   CVgaMenuItem::GetCharString (data,length,Graph->GraphData.SystemPressure);
}

void GraphRefresh(int Address)
{
   CVgaMenu * menu;
   int i = 0;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition();
   if(CChildView::thisPtr->ViewGraphGlobalCount==CChildView::thisPtr->UniversalCount)
   {
      return ;//true;
   }

   CVgaDrawGraph::GraphCount=0;
   while(theApp.GraphsDataList.GetCount()>0)
      theApp.GraphsDataList.RemoveHead();
   if(CChildView::thisPtr->ViewGraphWeldData)
   {
      delete CChildView::thisPtr->ViewGraphWeldData;
      CChildView::thisPtr->ViewGraphWeldData=0;
   }
   unsigned char RequestType = (char)126;
   int length =2;
   unsigned char data1[2];
   data1[0]=(char)RequestType;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      CChildView::thisPtr->ViewGraphGlobalCount=CChildView::thisPtr->UniversalCount;
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {		//store graph data
         while ((POSI)&&(length>0))
         {
            object= menu->items.GetNext(POSI);
            if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetGraphObjectMember(data,length,ptr);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  for(i=0;i<20;i++)
                     ptr->GraphData.GRAPHTITLE[i]='\0';
                  for( i=0;i<20;i++)
                     ptr->GraphData.CycleCount[i]='\0';
                  for( i=0;i<20;i++)
                     ptr->GraphData.SystemPressure[i]='\0';
                  ptr->AlreadyPrinted=false;
                  ptr->Lang_Index=0;//CChildView::Language_Index;
                  ptr->No_Graph_String=" ";
                  ptr->GraphCount++;
                  ptr->GraphData.GraphNum =ptr->GraphCount;
                  ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else
               {
                  data-=CORDLENGTH;
                  length+=CORDLENGTH;
               }
            }
         }
         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
         while(pos)
         {
            CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
            if((CChildView::thisPtr->GraphOneRequestValue==0)&&(CChildView::thisPtr->GraphTwoRequestValue==0))
            {
               if(Graph->GraphData.GraphRequestValue==2)
                  Graph->GraphData.GraphNum=1;
               CChildView::thisPtr->GraphOneRequestValue=2;
            }
            else
            {						
               if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
                  Graph->GraphData.GraphNum=1;
               else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
                  Graph->GraphData.GraphNum=2;
            }
         }
      }
      else 
         CChildView::thisPtr->ErrorBeep();
      delete response;
      /************************/
      int length =CORDLENGTH;
      unsigned char data1[CORDLENGTH];
      data1[0]=(char)01;//(++TotalGraphRequestValue);
      data1[1]=(char)01;
      unsigned char * data = (unsigned char *) &data1[0];
      request = new CHostCommand(GetWeldData_FunID, data, length);
      response= app->SendUiHostCommand(request);
      if(response)
      {
         char ch=CHostCommand::AckNak();
         length = response->GetDataLength();//Getting Length.
         if(ch==theApp.ACK)
         {
            //view->ViewGraphWelddataLength=length;
            CChildView::thisPtr->ViewGraphWeldData=response;
         }
         else
            delete response;
         //delete view->ViewGraphWeldData;
      }
      /*********************/
   }
   CChildView::thisPtr->Invalidate();
}

/******************************************************************************************/
/* This function is responsible to get graph data. the function is called when the user   */
/* clicks on any of the graph button or on the refresh button							  */
/*																						  */	
/******************************************************************************************/
void GetGraphData(unsigned char RequestType)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition();
   int i = 0;
   POSITION pos;
   /* of 2 graphs are present  and refresh is required*/	
   int graph_num1,graph_num2;
   int GraphRequestValue1,GraphRequestValue2;
   pos = theApp.GraphsDataList.GetHeadPosition();
   CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
   graph_num1= obj->GraphData.GraphNum;
   GraphRequestValue1 = obj->GraphData.GraphRequestValue;
   if(theApp.GraphsDataList.GetCount()==2)
   {
      obj = theApp.GraphsDataList.GetNext(pos);
      graph_num2= obj->GraphData.GraphNum;
      GraphRequestValue2 = obj->GraphData.GraphRequestValue;
   }

   int length =2;
   unsigned char data1[2];
   data1[0]=(char)RequestType;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {		//store graph data
         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();

         while ((POSI)&&(length>0))
         {
            object= menu->items.GetNext(POSI);
            if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if((ValueAfterParamID==ptr->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetGraphObjectMember(data,length,ptr);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  for(i=0;i<20;i++)
                     ptr->GraphData.GRAPHTITLE[i]='\0';
                  for( i=0;i<20;i++)
                     ptr->GraphData.CycleCount[i]='\0';
                  for( i=0;i<20;i++)
                     ptr->GraphData.SystemPressure[i]='\0';
                  ptr->AlreadyPrinted=false;
                  ptr->Lang_Index=0;//CChildView::Language_Index;
                  ptr->No_Graph_String=" ";
                  ptr->GraphCount++;
                  ptr->GraphData.GraphNum = ptr->GraphCount;
                  ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else
               {
                  data-=CORDLENGTH;
                  length+=CORDLENGTH;
               }

            }
         }
         pos = theApp.GraphsDataList.GetHeadPosition();
         while(pos)
         {
            CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
            if(obj->GraphData.GraphRequestValue == GraphRequestValue1)
               obj->GraphData.GraphNum =graph_num1;
            else if(obj->GraphData.GraphRequestValue == GraphRequestValue2)
               obj->GraphData.GraphNum =graph_num2;
         }

         if(theApp.GraphsDataList.GetCount()>1)
            if( (((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)%2)
               == (((theApp.GraphsDataList.GetTail())->GraphData.GraphNum)%2))
               if( ((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)
                  > ((theApp.GraphsDataList.GetTail())->GraphData.GraphNum))

                  ((theApp.GraphsDataList.GetHead())->GraphData.GraphNum)--;
               else
                  ((theApp.GraphsDataList.GetTail())->GraphData.GraphNum)--;
      }
      else 
      {
         CChildView::thisPtr->ErrorBeep();
      }
      delete response;
   }
   else
      ERRORBEEP;

}

/*****************************************************************************************/
/* This function works with getgraph data to get Graph data when user clicks on any graph */
/* button or on the refresh button.														 */
/*																						 */			
/*****************************************************************************************/
void GetData(unsigned char RequestValue)
{
   bool Is_Present=false;int temp=0;
   if(CChildView::thisPtr->AutoRefreshon)
   {
      if(theApp.GraphsDataList.GetCount()==2)
      {		
         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
         CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
         if( RequestValue == obj->GraphData.GraphRequestValue)
         {
            if(RequestValue ==CChildView::thisPtr->GraphOneRequestValue)
            {
               CChildView::thisPtr->GraphOneRequestValue=CChildView::thisPtr->GraphTwoRequestValue;
               CChildView::thisPtr->GraphTwoRequestValue=0;
            }
            else if(RequestValue ==CChildView::thisPtr->GraphTwoRequestValue)
               CChildView::thisPtr->GraphTwoRequestValue=0;
            Is_Present=true;
            theApp.GraphsDataList.RemoveHead();
         }
         obj = theApp.GraphsDataList.GetNext(pos);

         if( RequestValue == obj->GraphData.GraphRequestValue)
         {
            if(RequestValue ==CChildView::thisPtr->GraphOneRequestValue)
            {
               CChildView::thisPtr->GraphOneRequestValue=CChildView::thisPtr->GraphTwoRequestValue;
               CChildView::thisPtr->GraphTwoRequestValue=0;
            }
            else if(RequestValue ==CChildView::thisPtr->GraphTwoRequestValue)
               CChildView::thisPtr->GraphTwoRequestValue=0;
            Is_Present=true;
            theApp.GraphsDataList.RemoveTail();
         }

         if(Is_Present)
         {
            POSITION pos = theApp.GraphsDataList.GetHeadPosition();
            while(pos)
            {
               CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
               obj->GraphData.GraphNum=1;
               temp +=obj->GraphData.GraphRequestValue;
            }
            GetGraphData(temp);
         }
         else
         {	
            TRACE(_T("\n\n\n graph req value new %d "),RequestValue);
            int GraphNum1,GraphNum2;int Req;
            pos = theApp.GraphsDataList.GetHeadPosition();
            CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
            GraphNum1= obj->GraphData.GraphNum;Req = obj->GraphData.GraphRequestValue;

            obj = theApp.GraphsDataList.GetNext(pos);
            GraphNum2= obj->GraphData.GraphNum;
            if(GraphNum2 >GraphNum1)
               Req = obj->GraphData.GraphRequestValue;
            RequestValue +=Req;
            GetGraphData(RequestValue);
         }
      }
      else
      {
         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
         CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
         if(( RequestValue != obj->GraphData.GraphRequestValue)/*&&(obj->GraphData.graph_type !=VGA_NOGRAPH)*/)
            RequestValue +=obj->GraphData.GraphRequestValue;
         GetGraphData(RequestValue);
      }
   }
   else
   {
      int GraphNum1=0;int GraphNum2=0;

      if((RequestValue==CChildView::thisPtr->GraphOneRequestValue)||(RequestValue==CChildView::thisPtr->GraphTwoRequestValue))
      {

         POSITION pos = theApp.GraphsDataList.GetHeadPosition();
         while(pos)
         {
            CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
            if((RequestValue==CChildView::thisPtr->GraphOneRequestValue)
               &&(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
            {
               if(CChildView::thisPtr->GraphTwoRequestValue!=0)
               {
                  obj->GraphData.GraphNum=0;
                  CChildView::thisPtr->GraphOneRequestValue=0;
               }

            }
            else if((RequestValue==CChildView::thisPtr->GraphTwoRequestValue)
               &&(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
            {
               if(CChildView::thisPtr->GraphOneRequestValue!=0)
               {
                  obj->GraphData.GraphNum=0;
                  CChildView::thisPtr->GraphTwoRequestValue=0;
               }
            }
         }
         pos = theApp.GraphsDataList.GetHeadPosition();
         while(pos)
         {
            CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
            if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
            {
               if(CChildView::thisPtr->GraphTwoRequestValue==0)
               {
                  if((obj->GraphData.GraphNum%2==0))
                     obj->GraphData.GraphNum--;
                  if(obj->GraphData.GraphNum<0)
                     obj->GraphData.GraphNum+=2;

               }

            }

            else if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
            {
               if(CChildView::thisPtr->GraphOneRequestValue==0)
               {
                  if((obj->GraphData.GraphNum%2==0))
                     obj->GraphData.GraphNum--;
                  if(obj->GraphData.GraphNum<0)
                     obj->GraphData.GraphNum+=2;

               }
            }
         }
         return;

      }

      POSITION pos = theApp.GraphsDataList.GetHeadPosition();
      while(pos)
      {
         CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
         if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue))
         {
            GraphNum1=obj->GraphData.GraphNum;

         }
         else if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue))
         {
            GraphNum2=obj->GraphData.GraphNum;

         }
      }
      pos = theApp.GraphsDataList.GetHeadPosition();
      while(pos)
      {
         CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
         if(obj->GraphData.GraphRequestValue==RequestValue)
         {
            if((GraphNum1>GraphNum2))
            {

               CChildView::thisPtr->GraphTwoRequestValue=RequestValue;
               if(GraphNum2!=0)
                  obj->GraphData.GraphNum=GraphNum2+2;
               else
                  obj->GraphData.GraphNum=GraphNum1+1;

            }
            else
            {	
               CChildView::thisPtr->GraphOneRequestValue=RequestValue;
               if(GraphNum1!=0)
                  obj->GraphData.GraphNum=GraphNum1+2;
               else
                  obj->GraphData.GraphNum=GraphNum2+1;

            }

         }
         if((obj->GraphData.GraphRequestValue!=CChildView::thisPtr->GraphTwoRequestValue)&&(obj->GraphData.GraphRequestValue!=CChildView::thisPtr->GraphOneRequestValue))
            obj->GraphData.GraphNum=0;
      }


   }
}

void Color_DistanceGraph(int Address)
{
   GetData(Distance_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Power_Graph(int Address)
{
   GetData(Power_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Velocity_Graph(int Address)
{
   GetData(Velocity_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Force_Graph(int Address)
{
   GetData(Force_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Amplitude_Graph(int Address)
{
   GetData(Amplitude_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void Frequency_Graph(int Address)
{
   GetData(Frequency_RequestValue);
   CChildView::thisPtr->Invalidate();
}

void ExitEventHistoryMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
      theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->PMCScreen=false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void ExitAlarmLogMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
      theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->PMCScreen=false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   //theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   //theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   //CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void ModifyUserMenuEntry(int Address)
{
   //while(theApp.GraphsDataList.GetCount()>0)
   //	  theApp.GraphsDataList.RemoveHead();
   //CChildView::thisPtr->PMCScreen=false;
   //theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   //page_no=CChildView::thisPtr->menus.RemoveTail();
   //theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void ExitGraphMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
      theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->PMCScreen=false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
   CChildView::thisPtr->Invalidate();
}

void ExitBandLimitsMenu(int Address)
{
   while(theApp.GraphsDataList.GetCount()>0)
      theApp.GraphsDataList.RemoveHead();
   CChildView::thisPtr->Invalidate();
}

/**********************************************************************************/
/*                                                                                */
/*  This function sends command to 332 on Message Screen OK Button .              */
/**********************************************************************************/
void AddToAverageCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         	
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}


void SetHornScanObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph)
{
   Graph->GraphData.GraphColour=*data++;length--;
   short len;
   Graph->SetGraphRequestValue(Graph->GraphData.graph_type);
   for(int i=0;i<20;i++)
      Graph->GraphData.SystemPressure[i]='\0';
   Graph->AlreadyPrinted=false;
   Graph->Lang_Index=0;//CChildView::Language_Index;
   Graph->No_Graph_String=" ";
   Graph->GraphCount++;
   Graph->GraphData.GraphNum =Graph->GraphCount;

   /*Take out phase data*/
   Graph->GraphData.DataLength=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   for(len=0;len<(Graph->GraphData.DataLength);len++)
   {
      Graph->GraphData.graphdata[len]=(short)*data++;
      length--;
   }
   Graph->Store_VData_HData(data,length);
   Graph->StoreDate_Time(data,length);

   /*Take out current data*/
   int DataLength =CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   for(len=0;len<(DataLength);len++)
   {
      HSCurrentGraph[len]=(short)*data++;
      printf("%d, ",HSCurrentGraph[len]);
      length--;
   }

   /*Take out amplitude data*/
   DataLength =CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   for(len=0;len<(DataLength);len++)
   {
      HSAmpGraph[len]=(short)*data++;
      printf("%d, ",HSAmpGraph[len]);
      length--;
   }

}

/** @brief Send command for Horn Scan data.
*
*  This function is called when Scan Graph button is clicked.Function
*  send command to requesting for Scan Data. 
*
*  @param int,enable ID.
*  @return void.
*/
void SendCommandForHSCGraph(int ID)
{
   CVgaMenu * menu = theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   unsigned char RequestType = (char)(ID);
   int length =2;
   int i = 0;
   unsigned char data1[2];
   data1[0]=(char)RequestType;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {		//store graph data
         while ((pos1)&&(length>0))
         {
            object= menu->items.GetNext(pos1);
            if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetHornScanObjectMember(data,length,ptr);
                  ptr->HSCompareGraph =false;
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else if(ValueAfterParamID>PMC_GRAPH)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  for( i=0;i<20;i++)
                     ptr->GraphData.SystemPressure[i]='\0';
                  ptr->AlreadyPrinted=false;
                  ptr->Lang_Index=0;//CChildView::Language_Index;
                  ptr->No_Graph_String=" ";
                  ptr->GraphCount++;
                  ptr->GraphData.GraphNum =ptr->GraphCount;

                  for( i=0;i<20;i++)
                     ptr->GraphData.GRAPHTITLE[i]='\0';
                  for( i=0;i<20;i++)
                     ptr->GraphData.CycleCount[i]='\0';
                  ptr->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                  theApp.GraphsDataList.AddTail(ptr);
               }
               else
               {
                  data-=CORDLENGTH;
                  length+=CORDLENGTH;
               }
            }
         }
      }
      else 
         CChildView::thisPtr->ErrorBeep();
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanAButton(int ID)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
  
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
   int length =2;
   bool ValidGraphPresent=false;
   unsigned char data1[2];
   data1[0]=(char)ID;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {	
         while ((pos1)&&(length>0))
         {
            object= menu->items.GetNext(pos1);
            if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ValidGraphPresent =true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
            }
         }	
      }
      delete response;
   }
   if(ValidGraphPresent)
   {
      CString Path = DISK;
      Path = Path + "HornScanA.txt";
      KeypadType=SaveScanA;

      CString s1="  ";
      CFile f;
      CFileException e;
      if( !f.Open( Path, CFile::modeReadWrite , &e ) )
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
         unsigned char data[15];
         UINT k = f.Read(data,15);
         if(k > 10)
         {		
            unsigned char * data1 = data;
            int len = (int)f.GetLength();
            s1 = CVgaMenuItem::GetString(data1,len);
         }
         f.Close();
      }
      unsigned char *s=0;
      CString *p=&s1;
      OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
      CChildView::thisPtr->Invalidate();
   }
   else
   {	
      CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanBButton(int ID)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
   int length =2;
   bool ValidGraphPresent=false;
   unsigned char data1[2];
   data1[0]=(char)ID;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {	
         while ((pos1)&&(length>0))
         {
            object= menu->items.GetNext(pos1);
            if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ValidGraphPresent =true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
            }
         }	
      }
      delete response;
   }
   if(ValidGraphPresent)
   {
      CString Path = DISK;
      Path = Path + "HornScanB.txt";
      KeypadType=SaveScanB;

      CString s1="  ";
      CFile f;
      CFileException e;
      if( !f.Open( Path, CFile::modeReadWrite , &e ) )
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
         unsigned char data[15];
         UINT k = f.Read(data,15);
         if(k > 10)
         {		
            unsigned char * data1 = data;
            int len = (int)f.GetLength();
            s1 = CVgaMenuItem::GetString(data1,len);
         }
         f.Close();
      }

      unsigned char *s=0;
      CString *p=&s1;
      OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
      CChildView::thisPtr->Invalidate();
   }
   else
   {	
      CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}

/*************************************************************************/
/* This function will check for valid Scan Graph data and store it into  */
/* appropriate text file or gives a error message screen.				 */
/*************************************************************************/
void HandleSaveScanCButton(int ID)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION pos1=menu->items.GetHeadPosition();
   int KeypadType=0;
   CString No_Valid_Graph="";
   int length =2;
   bool ValidGraphPresent=false;
   unsigned char data1[2];
   data1[0]=(char)ID;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {	
         while ((pos1)&&(length>0))
         {
            object= menu->items.GetNext(pos1);
            if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
            {

               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ValidGraphPresent =true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
            }
         }	
      }
      delete response;
   }
   if(ValidGraphPresent)
   {
      CString Path = DISK;
      Path = Path + "HornScanC.txt";
      KeypadType=SaveScanC;

      CString s1="  ";
      CFile f;
      CFileException e;
      if( !f.Open( Path, CFile::modeReadWrite , &e ) )
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
         unsigned char data[15];
         int k =f.Read(data,15);
         if(k>10)
         {	
            unsigned char * data1 = data;
            int len = (int)f.GetLength();
            s1 =CVgaMenuItem::GetString(data1,len);
         }
         f.Close();
      }

      unsigned char *s=0;
      CString *p=&s1;
      OnKeypadScreen_flag=true;
      CChildView::thisPtr->BuildCompleteKeypadList(KeypadType,s,p,ID,0);
      CChildView::thisPtr->Invalidate();

   }
   else
   {	
      CChildView::thisPtr->ShowMessageScreen(No_Valid_Graph);
   }
}


/********************************************************************************/
/* This function will prepare the scan graph list for Compare graph screen or   */
/* to print the compare graph according to the availability of the valid graphs.*/
/********************************************************************************/
void CompareGraph_and_Data(int ID)
{ 	
   CVgaMenu * menu;
   CString No_Valid_Graph="";
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   bool IsPrint=false;
   POSITION pos1=menu->items.GetHeadPosition();
   if(ID==1)
   {
      IsPrint = true;
   }
   else
      IsPrint = false;
   CString s3,s2,s1;
   int TempCount=0;
   int NoOfGraphs=0;
   CFile f1;
   CFileException e1;
   TCHAR* pFileName1;
#ifndef _WIN32_WCE
   pFileName1 = _T("C:\\Branson\\HornScanA.txt");
#else
   pFileName1 = _T("Disk\\HornScanA.txt");
#endif

   if( !f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
   {
#ifdef _DEBUG
      if(e1.m_cause==CFileException::generic)
         TRACE(_T("\n !! GENERIC"));
      else if(e1.m_cause==CFileException::badPath   )
         TRACE(_T("\n !! bad path"));
      else if(e1.m_cause==CFileException::tooManyOpenFiles    )
         TRACE(_T("\n !! too many files open"));
      else if(e1.m_cause==CFileException::fileNotFound )
         TRACE(_T("\n !! file not found"));
      else if(e1.m_cause==CFileException::accessDenied  )
         TRACE(_T("\n !! access denied"));
      else if(e1.m_cause==CFileException::diskFull      )
         TRACE(_T("\n !! disc full"));
      else if(e1.m_cause==CFileException::invalidFile   )
         TRACE(_T("\n !! invalid file"));
      afxDump << "File could not be opened " << e1.m_cause << "\n";
#endif
   }
   else
   {
      unsigned char *c = new unsigned char[(int)f1.GetLength()];
      unsigned char *c1 = c;
      UINT k = f1.Read(c,(UINT)f1.GetLength());
      if(k > 20)
      {
         int length = (int)f1.GetLength();
         s1 = CVgaMenuItem::GetString(c,length);
         while ((pos1))
         {
            object= menu->items.GetNext(pos1);
            if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==1))
            {

               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetHornScanObjectMember(c,length,ptr);
                  ptr->GraphData.GraphColour =Blue;
                  ptr->HSCompareGraph=true;
                  ptr->HS_CompareGraphNum =ONE;
                  if(IsPrint)
                  {	
                     CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
                  }
                  else
                     theApp.GraphsDataList.AddTail(ptr);
                  NoOfGraphs++;
                  CChildView::thisPtr->ScanA_Present=true;
                  CChildView::thisPtr->ScanA_On=true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
               TempCount++;
               break;
            }
            else
            {
               TempCount++;
            }

         }

      }
      f1.Close();
      delete []c1;

   }
   TempCount=0;
   pos1=menu->items.GetHeadPosition();
   CFile f;
   CFileException e;
   TCHAR* pFileName;
#ifndef _WIN32_WCE
   pFileName = _T("C:\\Branson\\HornScanB.txt");
#else
   pFileName = _T("Disk\\HornScanB.txt");
#endif

   if( !f.Open( pFileName, CFile::modeReadWrite , &e ) )
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
      unsigned char *c2=new unsigned char[(int)f.GetLength()];
      unsigned char *c1=c2;
      UINT j = f.Read(c2,(UINT)f.GetLength());
      if(j > 20)
      {
         int length = (int)f.GetLength();
         s2 = CVgaMenuItem::GetString(c2,length);
         while ((pos1))
         {
            object= menu->items.GetNext(pos1);
            if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==2))
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c2,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetHornScanObjectMember(c2,length,ptr);
                  ptr->GraphData.GraphColour =Red;
                  ptr->HSCompareGraph=true;
                  ptr->HS_CompareGraphNum =2;
                  if(IsPrint)
                  {	
                     CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
                  }
                  else
                     theApp.GraphsDataList.AddTail(ptr);
                  NoOfGraphs++;
                  CChildView::thisPtr->ScanB_Present=true;
                  CChildView::thisPtr->ScanB_On=true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
               TempCount++;
            }
            else
            {
               TempCount++;
            }
         }
      }
      f.Close();
      delete []c1;
   }

   TempCount=0;
   pos1=menu->items.GetHeadPosition();
   CFile f2;
   CFileException e2;
   TCHAR* pFileName2;
#ifndef _WIN32_WCE
   pFileName2 = _T("C:\\Branson\\HornScanC.txt");
#else
   pFileName2 = _T("Disk\\HornScanC.txt");
#endif

   if( !f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
   {
#ifdef _DEBUG
      if(e2.m_cause==CFileException::generic)
         TRACE(_T("\n !! GENERIC"));
      else if(e2.m_cause==CFileException::badPath   )
         TRACE(_T("\n !! bad path"));
      else if(e2.m_cause==CFileException::tooManyOpenFiles    )
         TRACE(_T("\n !! too many files open"));
      else if(e2.m_cause==CFileException::fileNotFound )
         TRACE(_T("\n !! file not found"));
      else if(e2.m_cause==CFileException::accessDenied       )
         TRACE(_T("\n !! access denied"));
      else if(e2.m_cause==CFileException::diskFull      )
         TRACE(_T("\n !! disc full"));
      else if(e2.m_cause==CFileException::invalidFile   )
         TRACE(_T("\n !! invalid file"));
      afxDump << "File could not be opened " << e2.m_cause << "\n";
#endif
   }
   else
   {
      unsigned char *c1=new unsigned char[(int)f2.GetLength()];
      unsigned char *c=c1;
      UINT i = f2.Read(c1,(UINT)f2.GetLength());
      if(i > 20)
      {
         int length = (int)f2.GetLength();
         s3 = CVgaMenuItem::GetString(c1,length);
         while ((pos1))
         {
            object= menu->items.GetNext(pos1);
            // while(length>0)
            {
               if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==3))
               {
                  CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                  int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(c1,length,CORDLENGTH);

                  if(ValueAfterParamID==ptr->GraphType)
                  {
                     ptr->GraphData.graph_type=ValueAfterParamID;
                     SetHornScanObjectMember(c1,length,ptr);
                     ptr->GraphData.GraphColour =Green;
                     ptr->HSCompareGraph=true;
                     ptr->HS_CompareGraphNum =3;
                     if(IsPrint)
                     {	
                        CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
                     }
                     else
                        theApp.GraphsDataList.AddTail(ptr);
                     NoOfGraphs++;
                     CChildView::thisPtr->ScanC_Present=true;
                     CChildView::thisPtr->ScanC_On=true;
                  }
                  else if(ValueAfterParamID>ptr->GraphType)
                  {
                     No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                  }
                  TempCount++;
               }
               else
               {
                  TempCount++;
               }
            }
         }

      }
      f2.Close();
      delete []c;
   }

   int length =2;
   TempCount=0;
   pos1=menu->items.GetHeadPosition();
   unsigned char data1[2];
   data1[0]=(char)HornScan_RequestValue;
   data1[1]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
  
   CHostCommand * request = new CHostCommand(GetWeldData_FunID/*GetWeldResults_FunId*/, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {	
         while ((pos1)&&(length>0))
         {
            object= menu->items.GetNext(pos1);
            if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==4))
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  SetHornScanObjectMember(data,length,ptr);
                  ptr->GraphData.GraphColour =Black;
                  ptr->HSCompareGraph=true;
                  ptr->HS_CompareGraphNum =4;
                  if(IsPrint)
                  {
                     CChildView::thisPtr->HSGraphPrintList.AddTail(ptr);
                  }
                  else
                     theApp.GraphsDataList.AddTail(ptr);
                  NoOfGraphs++;
                  CChildView::thisPtr->CurrentScan_Present=true;
                  CChildView::thisPtr->CurrentScan_On=true;
               }
               else if(ValueAfterParamID>ptr->GraphType)
               {
                  No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
               }
               TempCount++;
            }
            else
            {
               TempCount++;
            }
         }
      }

      delete response;
   }
   if(NoOfGraphs==0 && !IsPrint)
   {
      CDC *pDC=CChildView::thisPtr->GetDc();
      /*Drawing Message Rectangle in specified color*/
      CVgaMenuItem::DrawRect(pDC, Black, MESSAGESCRN_BLACKRECT);
      CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

      /*Drawing Message Text*/
      CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,No_Valid_Graph/*Str_NoValidGraph[CChildView::Language_Index]*/ ,true);
      CChildView::thisPtr->ReleaseDc(pDC);	
      CChildView::thisPtr->InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
      CChildView::thisPtr->DisableFlag=true;
   }

   if(!IsPrint)
   {

   }
   else
   {	
      switch(NoOfGraphs)
      {
      case 1:
         CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHONE);
         break;
      case 2:
         CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHTWO);
         break;
      case 3:
         CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHTHREE);
         break;
      case 4:
         CChildView::thisPtr->PrintInfoList.AddTail(HSCGRAPHFOUR);
         break;
      }
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}


/********************************************************************************/
/* This function will prepare Graph list to show Graphs on the screen	    	*/
/* according to "ON" Graphs Button on the screen.						        */	
/********************************************************************************/	
void EditGraphList(int ID,bool On_Off,int graphNum)
{
   if((!On_Off))
   {
      CTypedPtrList<CPtrList, CVgaDrawGraph *> HSGraphDataList;

      while(theApp.GraphsDataList.GetCount())
      {
         CVgaDrawGraph *obj =theApp.GraphsDataList.GetHead();
         if(obj->HS_CompareGraphNum != graphNum)
         {
            HSGraphDataList.AddTail(obj);
            theApp.GraphsDataList.RemoveHead();
         }
         else
            theApp.GraphsDataList.RemoveHead();
      }
      POSITION pos = HSGraphDataList.GetHeadPosition();
      while(pos)
      {
         CVgaDrawGraph *obj = HSGraphDataList.GetNext(pos);
         theApp.GraphsDataList.AddTail(obj);
      }
   }
   else if(On_Off)
   {
      CVgaMenu * menu;
      CString No_Valid_Graph="";
      menu=theApp.MenuPointer;
      CVgaMenuItem *object;
      int TempCount=0;
      POSITION pos1=menu->items.GetHeadPosition();
      CString Path = DISK;
      bool GraphPresent =false;
      switch(graphNum)
      {
      case ONE:
         {
            Path = Path + "HornScanA.txt";
            if(CChildView::thisPtr->ScanA_Present)
            {
               GraphPresent =true;
               TempCount=1;
            }
         }
         break;
      case 2:
         {
            Path = Path + "HornScanB.txt";
            if(CChildView::thisPtr->ScanB_Present)
            {
               GraphPresent =true;
               TempCount=2;
            }
         }
         break;
      case 3:
         {
            Path = Path + "HornScanC.txt";
            if(CChildView::thisPtr->ScanC_Present)
            {
               GraphPresent =true;
               TempCount=3;
            }
         }
         break;
      case 4:
         {
            int length =2;
            unsigned char data1[2];
            data1[0]=(char)ID;
            data1[1]=(char)0;
            unsigned char * data = (unsigned char *) &data1[0];
           
            CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
            CHostCommand * response = app->SendUiHostCommand(request);
            if (response)
            {
               char ch=CHostCommand::AckNak();
               data = response->GetData();//Getting Data.
               length = response->GetDataLength();//Getting Length.
               if(ch==theApp.ACK)//If Ack.
               {	
                  while ((pos1)&&(length>0))
                  {
                     object= menu->items.GetNext(pos1);
                     if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(TempCount==4))
                     {
                        CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                        int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                        if(ValueAfterParamID==ptr->GraphType)
                        {
                           ptr->GraphData.graph_type=ValueAfterParamID;
                           SetHornScanObjectMember(data,length,ptr);
                           GraphPresent=false;
                           ptr->GraphData.GraphColour =Black;
                           ptr->HSCompareGraph=true;
                           ptr->HS_CompareGraphNum =4;
                           theApp.GraphsDataList.AddTail(ptr);
                        }
                        else if(ValueAfterParamID>ptr->GraphType)
                        {
                           No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                        }
                        TempCount++;
                     }
                     else
                     {
                        TempCount++;
                     }
                  }
               }
               delete response;
            }
         }
         break;
      }	
      if(GraphPresent)
      {
         CFile f;
         CFileException e;
         if( !f.Open( Path, CFile::modeReadWrite , &e ) )
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
            unsigned char *Data=new unsigned char[(int)f.GetLength()];
            unsigned char *Dummy = Data;
            UINT k = f.Read(Data,(UINT)f.GetLength());
            if(k > 20)
            {
               int length = (int)f.GetLength();
               int Temp=0;

               CString HS_ID1 =CVgaMenuItem::GetString(Data,length);
               while ((pos1))
               {
                  object= menu->items.GetNext(pos1);
                  if((object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)&&(Temp==TempCount))
                  {
                     CVgaDrawGraph * ptr = (CVgaDrawGraph * )object;
                     int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(Data,length,CORDLENGTH);
                     if(ValueAfterParamID==ptr->GraphType)
                     {
                        ptr->GraphData.graph_type=ValueAfterParamID;
                        SetHornScanObjectMember(Data,length,ptr);
                        ptr->GraphData.GraphColour =graphNum+1;
                        ptr->HSCompareGraph=true;
                        ptr->HS_CompareGraphNum = graphNum;
                        theApp.GraphsDataList.AddTail(ptr);
                     }
                     else if(ValueAfterParamID>ptr->GraphType)
                     {
                        No_Valid_Graph=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                     }
                     Temp++;
                  }
                  else
                  {
                     Temp++;
                  }
               }
            }
            delete []Dummy;
            f.Close();
         }
      }
   }
}


void HornScanA(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanA_Present) 
   {
      CChildView::thisPtr->ScanA_On =!CChildView::thisPtr->ScanA_On;
      EditGraphList(ID,CChildView::thisPtr->ScanA_On, 1);
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void HornScanB(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanB_Present)
   {
      CChildView::thisPtr->ScanB_On =!CChildView::thisPtr->ScanB_On;
      EditGraphList(ID,CChildView::thisPtr->ScanB_On, 2);
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void HornScanC(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->ScanC_Present)
   {
      CChildView::thisPtr->ScanC_On =!CChildView::thisPtr->ScanC_On;
      EditGraphList(ID,CChildView::thisPtr->ScanC_On, 3);
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

void CurrentHornScan(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->CurrentScan_Present)
   {
      CChildView::thisPtr->CurrentScan_On = !CChildView::thisPtr->CurrentScan_On;
      EditGraphList(ID,CChildView::thisPtr->CurrentScan_On, 4);
   }
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}


void CopyScanData(int ID,CLocalChoice *ptr)
{
   if(CChildView::thisPtr->USBPresent())
   {
      CChildView::thisPtr->EnableWindow(false);
      CDC *pDC=CChildView::thisPtr->GetDc();
      /*Drawing Message Rectangle in specified color*/
      CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
      CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

      /*Drawing Message Text*/
      CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,ptr->ChoiceText1/*StrM5_35[CChildView::Language_Index]*/,true);
      CChildView::thisPtr->ReleaseDc(pDC);
      CChildView::thisPtr->CreateFolder(true);        
      CString	Path= USBDISK + CChildView::thisPtr->PowerSupply;

      CString TempPath =   Path +"\\"+"Horn Signature";
      if(!CChildView::thisPtr->IsFolderPresent(Path,"Horn Signature"))
         CreateDirectory(TempPath,NULL);			      

#ifndef _WIN32_WCE
      TCHAR* pFileName1= _T("C:\\Branson\\HornScanA.txt");
      TCHAR* pFileName2= _T("C:\\Branson\\HornScanB.txt");
      TCHAR* pFileName3= _T("C:\\Branson\\HornScanC.txt");
#else
      TCHAR* pFileName1= _T("\\Disk\\HornScanA.txt");
      TCHAR* pFileName2= _T("\\Disk\\HornScanB.txt");
      TCHAR* pFileName3= _T("\\Disk\\HornScanC.txt");
#endif
      bool ScanAPresent=false,ScanBPresent=false,ScanCPresent=false;
      CFileException e1,e2,e3;
      CFile f1,f2,f3;
      if( f1.Open( pFileName1, CFile::modeReadWrite , &e1 ) )
      {

         ScanAPresent=true;
         f1.Close();
         CopyFile(pFileName1,(TempPath+"\\"+_T("HornScanA.txt")),false);

      }
      if( f2.Open( pFileName2, CFile::modeReadWrite , &e2 ) )
      {

         ScanBPresent=true;
         f2.Close();
         CopyFile(pFileName2,(TempPath+_T("\\HornScanB.txt")),false);
      }

      if( f3.Open( pFileName3, CFile::modeReadWrite , &e3 ) )
      {
         ScanCPresent=true;
         f3.Close();
         CopyFile(pFileName3,(TempPath+_T("\\HornScanC.txt")),false);
      }
      if((!ScanAPresent) && (!ScanBPresent) && (!ScanCPresent))
         CChildView::thisPtr->ShowMessageScreen(ptr->ChoiceText2);
      CChildView::thisPtr->EnableWindow(true);
      CChildView::thisPtr->Invalidate();

   }
   else
   {
      char TempArray[10];
      CString Temp=_itoa(ID,TempArray,10);
      Temp=CVgaMenuItem ::LinearSearch(Temp);
      CChildView::thisPtr->ShowMessageScreen(Temp);
   }

}

void ExitAlarmMenu(int Address)
{
   CChildView::thisPtr->IsAlarmScreen =false;
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
      CChildView::thisPtr->RunResultScreen=true;
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   if(CChildView::thisPtr->AlarmCount!=0)
      CChildView::thisPtr->AlarmUpdateRequired=true;
   else
      CChildView::thisPtr->AlarmUpdateRequired=false;  //Coverity Issue
     CChildView::thisPtr->Invalidate();
}


void SendAlarmMenuCommand(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;

   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(GetAlarmMenuItems_FunId,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         //printf("\n Nak");
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();	
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
   CChildView::thisPtr->Invalidate();
}


void AlarmErrorBeep(int Address)
{
   CHostCommand * request = new CHostCommand(ErrorBeep_FunId, 0, 0);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
      delete response;
}

void ProcessColorSetup(int Address)
{
   CChildView::ScreenSetupFlag=false;
   CChildView::thisPtr->Invalidate();
}

void WeldHistoryPrintNow(int Address)
{	

   CVgaButton *ptr=(CVgaButton *)Address;
   int type = ptr->EnumID;		//12
   HistoryTemp_pos=NULL;
   GraphsTemp_pos=NULL;
   WeldTemp_pos=NULL;
   HornScanTemp_pos=NULL;
   ScanGraphsDataTemp_pos=NULL;
   ScreenGraphsTemp_pos=NULL;
   SetupTemp_pos=NULL;
   DUPSTemp_pos=NULL;
   SequenceTemp_pos=NULL;

   HistoryTemp_pos = tempHistoryList.GetHeadPosition();
   CString PrinterPower_str,StrM5_35;

   PrinterPower_str = tempHistoryList.GetNext(HistoryTemp_pos);

   StrM5_35 = tempHistoryList.GetNext(HistoryTemp_pos);

   //if((PrintSetup.IsPrinting)&&(CChildView::thisPtr->PrinterPresent))
   //{	if(CChildView::thisPtr->PrinterPresent)
   //	CChildView::thisPtr->ShowMessageScreen(StrM5_35);
   printf("calling BuildPrintList \n");
   CChildView::thisPtr->BuildPrintList(type);
   //}
   //else if(!CChildView::thisPtr->PrinterPresent)
   //		CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void GraphsWeldNow(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   
   HistoryTemp_pos=NULL;
   GraphsTemp_pos=NULL;
   WeldTemp_pos=NULL;
   HornScanTemp_pos=NULL;
   ScanGraphsDataTemp_pos=NULL;
   ScreenGraphsTemp_pos=NULL;
   SetupTemp_pos=NULL;
   DUPSTemp_pos=NULL;
   SequenceTemp_pos=NULL;

   GraphsTemp_pos = tempGraphsList.GetHeadPosition();
   CString PrinterPower_str;
   PrinterPower_str = tempGraphsList.GetNext(GraphsTemp_pos);
   CChildView::thisPtr->ShowMessageScreen(PrinterPower_str);
}

void SetUpPrintNow(int Address)
{
	if(creating_pdf)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
		theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		CChildView::thisPtr->ErrorBeep();
		CChildView::thisPtr->Invalidate();
	}
	else
	{
		if(CChildView::thisPtr->ISUSBPresent == true)
		{
			if(CChildView::thisPtr->GetStateMachineStatus() == true)		
			{
				CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);

				SetupTemp_pos = tempSetupList.GetHeadPosition();
				CString PrinterPower_str,StrM5_35;
				PrinterPower_str = tempSetupList.GetNext(SetupTemp_pos);
				StrM5_35 = tempSetupList.GetNext(SetupTemp_pos);
				CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
				creating_pdf=true;
				CChildView::thisPtr->BuildPrintList(SETUPID);
				theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
				page_no=CChildView::thisPtr->menus.RemoveTail();
				theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
				CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
			}
			else
			{
				ProcessNak(Address);
				DisplayMessage(0);	//Display Weld Cycle Running	
				CChildView::thisPtr->Invalidate();
			}
		}
		else
		{
			ProcessNak(Address);
			DisplayMessage(3);	//connect usb
			CChildView::thisPtr->Invalidate();
		} 
	}

}

void PowerPresetUpPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
   if(GlobalPresetSelection <=1)
   {
      CChildView::ErrorBeep();
      return ;
   }
   CChildView::thisPtr->SelectedPowerPreset = 1;
   GlobalPresetSelection--;
   SendPresetNumberSetCommand(PRESET_INFO_SELECT_ID);
   GetPreset(PRESET_NUM_SELECT_ID,GlobalPresetSelection);
   CChildView::thisPtr->Invalidate();
}

void PowerPresetDownPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
   if(GlobalPresetSelection >= Max_Preset_Possible)
   {
      CChildView::ErrorBeep();
      return ;
   }
   CChildView::thisPtr->SelectedPowerPreset = 1;
   GlobalPresetSelection++;
   SendPresetNumberSetCommand(PRESET_INFO_SELECT_ID);
   GetPreset(PRESET_NUM_SELECT_ID,GlobalPresetSelection);
   CChildView::thisPtr->Invalidate();
}

void USBPresetUpPressed(int Address)
{
   if(CChildView::thisPtr->SelectedUSBPreset<=1)
   {
      if(CChildView::thisPtr->SelectedUSBPreset==1)
         CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
      CChildView::ErrorBeep();

      return ;
   }
   CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
   CChildView::thisPtr->SelectedUSBPreset=CChildView::thisPtr->SelectedUSBPreset-1;
   CChildView::thisPtr->Invalidate();
}

void USBPresetDownPressed(int Address)
{
   CChildView::thisPtr->LastSelectedPresetFrom=USBPresetSelected;
   if(CChildView::thisPtr->SelectedUSBPreset==CChildView::thisPtr->TotalUSBPreset)
   {
      CChildView::ErrorBeep();
      return ;
   }
   CChildView::thisPtr->SelectedUSBPreset=CChildView::thisPtr->SelectedUSBPreset+1;
   CChildView::thisPtr->Invalidate();
}

bool CopyPresetToPowerSupply(CChildView *view)
{
   CString	pFileName=CChildView::thisPtr->LastUSBPresetFolder + "\\Preset"+ CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1))+".prst";
   CFile f;
   CFileException e;
   char ch1=0;
   if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {
      int  size= SIZEOFPRESETDATA;
      int ObjectSize = sizeof(bool)+ sizeof(char)+ size + sizeof(char);
      int StartingPointer =sizeof(bool)+ sizeof(char);
      char ch[SIZEOFPRESETDATA+3] ;
      ch[0]=(char)(GlobalPresetSelection>>8);
      ch[1] = (char)(GlobalPresetSelection);
      f.SeekToBegin();
      int length = (int)f.GetLength();
      if(length > ObjectSize)
      {
         f.Close();
         CChildView::ErrorBeep();
         return false;
      }
      f.Seek(StartingPointer, CFile::begin );
      f.Read(&ch[2],length-3);
	  length = length-1;
      f.Close();
      unsigned char * data = (unsigned char *) &ch[0];
      CHostCommand * request = new CHostCommand(DownLoadPresetFun_Id, data,length);
      CHostCommand * response = app->SendUiHostCommand(request);
      if (response)
      {
         ch1=CHostCommand::AckNak();
         length = response->GetDataLength();//Getting Length.
         if(ch1==theApp.ACK)//If Ack.
         {
            CString Temp2 = CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1];
            if(Temp2.GetLength()>2)
               Temp2.Delete(2,(CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]).GetLength()-2);
            CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]= Temp2+" "+ CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1));
         }
         delete response;
      }
   }
   else
      CChildView::ErrorBeep();
   if(ch1==theApp.ACK)
      return true;
   else
   {
	   CChildView::ErrorBeep();
	   return false;
   }
}

bool OverwritePreset(int PSPreset, int USBPreset,CChildView *view,int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
	CVgaMenu *menu;
	int SpacePos, MinPresetNameLen;
	POSITION pos = NULL;
	CString PresetNametoCheck = "";
	int TotalPresetCountinTempList = CChildView::thisPtr->USBPresetName_temp.GetCount();
	int Count = 0;
	if(USBPreset)
	{
		CChildView::thisPtr->USBpstMutex.Lock();
		if(CChildView::thisPtr->USBOverWritePreset)
			Count = TotalPresetCountinTempList;
		else
			Count = CChildView::thisPtr->TotalUSBPreset;
		for(int i =0;i<Count;i++)
		{
			if(CChildView::thisPtr->USBOverWritePreset)
				PresetNametoCheck = CString(_T(" "))+CChildView::thisPtr->PresetName;
			else
				PresetNametoCheck = CChildView::thisPtr->PSPresetText[PSPreset-1];
			CString S=PresetNametoCheck;	                          	
			SpacePos = S.Find(_T(" "), 0);
			if(SpacePos != -1)
				S.Delete(0, SpacePos + 1);

			CString USBPressetName = "";
			if(CChildView::thisPtr->USBOverWritePreset)
				USBPressetName=CChildView::thisPtr->USBPresetName_temp.GetAt(CChildView::thisPtr->USBPresetName_temp.FindIndex(i));
			else
				USBPressetName=CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(i));
			
			printf(" %d %S, ",i,USBPressetName);
			USBPressetName.TrimLeft();
			USBPressetName.TrimRight();

			if(S==USBPressetName)
			{
				CChildView::thisPtr->OverWritePresetNum=i+1;
				CChildView::thisPtr->OverWritePreset=true;
				CChildView::thisPtr->CopyPresetNum = PSPreset;
				printf("MenuNak = %S\n",ptr->MenuNak);
				if(ptr->MenuNak!="")
				{
					if (theApp.menus.Lookup(ptr->MenuNak, menu))
					{
						view->menupointers.AddTail(theApp.MenuPointer);
						view->menusname.AddTail(theApp.menuName);
						view->menus.AddTail(page_no);
						page_no=1;
						theApp.menuName = ptr->MenuNak;
						theApp.MenuPointer=menu;
						CChildView::thisPtr->ModifyObjectList(menu);
						char buf[5];
						sprintf(buf,"%d ",CChildView::thisPtr->OverWritePresetNum);
						CVgaMenuItem * Object;
						pos = menu->items.GetHeadPosition();
						while(pos)
						{
							Object = menu->items.GetNext(pos);
							if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
							{
								CMsgScreen *obj=(CMsgScreen*)Object;
								obj->MsgLine1="";
								obj->MsgLine3="";
								pos = CChildView::thisPtr->USBPresetNames.GetHeadPosition();
								CString USBPressetName = "";
								if(CChildView::thisPtr->USBOverWritePreset)
									USBPressetName=CChildView::thisPtr->USBPresetName_temp.GetAt(CChildView::thisPtr->USBPresetName_temp.FindIndex(i));
								else
									USBPressetName=CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(i));
								printf(" %d %S, ",i,USBPressetName);
								obj->MsgLine2=obj->text + " "+ buf + USBPressetName + " ?";
								printf("msgbox %S\n",obj->MsgLine2);
								break;
							}
						}
					}		
				}
				printf("invalidate\n");
				CChildView::thisPtr->USBpstMutex.Unlock();
				CChildView::thisPtr->Invalidate();
				
				return true;
			}
		}
		CChildView::thisPtr->USBpstMutex.Unlock();
		return false;
	}
	else
	{
		if((GlobalPresetSelection > MAX_TWODIGIT_PRESET) && (GlobalPresetSelection <= MAX_THREEDIGIT_PRESET))
			MinPresetNameLen = MIN_LENGHT_THREEDIGITPRESET;
		else if(GlobalPresetSelection > MAX_THREEDIGIT_PRESET)
			MinPresetNameLen = MIN_LENGHT_FOURDIGITPRESET;
		else
			MinPresetNameLen = MIN_LENGHT_TWODIGIT_PRESET;		

		if(CChildView::thisPtr->PSPresetText[PSPreset-1].GetLength()>MinPresetNameLen)//CChildView::thisPtr->PSPresetText
		{
			CChildView::thisPtr->OverWritePresetNum++;
			CChildView::thisPtr->OverWritePSPreset=true;
			CChildView::thisPtr->OverWritePreset=true;
			CChildView::thisPtr->CopyPresetNum = PSPreset;
			if(ptr->MenuNak!="")
			{
				if (theApp.menus.Lookup(ptr->MenuNak, menu))
				{
					view->menupointers.AddTail(theApp.MenuPointer);
					view->menusname.AddTail(theApp.menuName);
					view->menus.AddTail(page_no);
					page_no=1;
					theApp.menuName = ptr->MenuNak;
					theApp.MenuPointer=menu;
					CChildView::thisPtr->ModifyObjectList(menu);
					CVgaMenuItem * Object;
					POSITION pos = menu->items.GetHeadPosition();
					while(pos)
					{
						Object = menu->items.GetNext(pos);
						if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
						{
							CMsgScreen *obj=(CMsgScreen*)Object;
							obj->MsgLine1="";
							obj->MsgLine3="";
							obj->MsgLine2=obj->text +CChildView::thisPtr->PSPresetText[PSPreset-1] +" ?";
							break;
						}
					}
				}		
			}
			CChildView::thisPtr->Invalidate();
			return true;
		}
		return false;
	}
}

void WriteDataToUSBFile(CChildView *view,unsigned char * &data, int & length)
{
	/*Getting Preset name from the data.*/
	unsigned char * ch ;
	unsigned char *CH = data;
	CString S;
	if(length==SIZEOFPRESETDATA)
		CH +=PresetPos;
	else
		CH +=PresetNameStrPos;

	ch=CH;

	if(*ch ==0)
		S += ' ';
	while(*ch !=0)
		S +=(char) *ch++;


	CChildView::thisPtr->PSName =view->PowerSupply;
	CString	pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+S+".prst";
	CFile f;
	CFileException e;
	if(f.Open( pFileName,CFile::modeRead, &e ) )
	{
		int Temp = (int)f.GetLength();
		if(Temp>length)
		{
			f.Close();
			CFile::Remove(pFileName);
		}
		else
			f.Close();
	}

	if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
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
		char Comma =',';
		f.Write(&CChildView::metric,sizeof(bool));
		f.Write(&Comma,sizeof(char));
		char dataarray[SIZEOFPRESETDATA+1];
		int i=0;
		while(length>0)
		{
			dataarray[i] =*data++;
			length--;
			i++;
		}
		f.Write(&dataarray,i);
		f.Write(&Comma,sizeof(char));
		f.Close();
	}

}

void CopyPresetToUSB(CChildView *view,int PresetNumber)
{
   if((PresetNumber<1)||((CChildView::thisPtr->PSPresetText[PresetNumber-1]).GetLength() < 4))
   {
      CChildView::ErrorBeep();
      return;
   }
   else
   {
      /*Send Command To get Preset Data.*/

      int length = 2;
      unsigned char data1[2];
      union 
      {
         short i;
         char c[2];
      } u;

      u.i=GlobalPresetSelection + PresetNumber - 1;//getting radio value to char array.
      data1[1]=(char)u.c[0];
      data1[0]=(char)u.c[1];
      unsigned char * data = (unsigned char *) &data1[0];


      CHostCommand * request = new CHostCommand(UpLoadPreset_FunId, data,length);
      CChildView::LargeWaitingTime = true;
      CHostCommand * response = app->SendUiHostCommand(request);
      CChildView::LargeWaitingTime = false;
      if (response)
      {
         char ch=CHostCommand::AckNak();
         data = response->GetData();//Getting Data.
         length = response->GetDataLength();//Getting Length.
         if(ch==theApp.ACK)//If Ack.
         {
            WriteDataToUSBFile(view,data,length);
         }
         delete response;

      }
   }

}

void CopyPowerPreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
   CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   CChildView *view=CChildView::thisPtr;
   if((CChildView::thisPtr->SelectedPowerPreset>0) /*&& (SelectedUSBPreset)*/)
   {
      CString S=CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1];
      int Temp = GlobalPresetSelection + CChildView::thisPtr->SelectedPowerPreset - 1;
      if(((Temp < Max_Preset_Possible) && (S.GetLength()>MIN_LENGHT_THREEDIGITPRESET)) || ((Temp > MAX_THREEDIGIT_PRESET) && (S.GetLength() > MIN_LENGHT_FOURDIGITPRESET)))
      {
         if(!OverwritePreset(CChildView::thisPtr->SelectedPowerPreset, 1,view,Address))
         {
            view->ShowMessageScreen(StrM5_35);
            CopyPresetToUSB(view,CChildView::thisPtr->SelectedPowerPreset);
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
            CChildView::thisPtr->Invalidate();
         }
      }
      else
         CChildView::ErrorBeep();
      return ;
   }
   else if(!CChildView::thisPtr->TotalUSBPreset)
   {
      CString S =(CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]);
      S.Delete(0,3);
      if(S.GetLength()>0)
      {	
         CopyPresetToUSB(view,CChildView::thisPtr->SelectedPowerPreset);
         CChildView::thisPtr->SelectedUSBPreset=1;
         CChildView::thisPtr->USBPresetNames.AddTail(S);
         CChildView::thisPtr->TotalUSBPreset++;
         CChildView::thisPtr->Invalidate();
      }
      else
         CChildView::thisPtr->ErrorBeep();
   }
   else
      CChildView::thisPtr->ErrorBeep();
}

void OverWriteOkButton(int Address)
{
	CChildView *view=CChildView::thisPtr;
	CVgaButton *ptr=(CVgaButton *)Address;
	char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
	StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	printf("OverWriteOkButton\n");
	if(CChildView::thisPtr->USBOverWritePreset == true)
	{
		CChildView::thisPtr->CopyAllPresetAddress_Ok = Address;
		if(PresetCount < CChildView::thisPtr->PresetNameCount)
			 CChildView::thisPtr->BuildPrintList(COPYALL_PRESET_TOUSB_OK);
		else
		{
			CChildView::thisPtr->USBOverWritePreset = false;			
			if(StoredPresetListData)
			{
				delete StoredPresetListData;
				CChildView::thisPtr->PresetListBuff = NULL;
				StoredPresetListData = NULL;
				PresetCount = 0;
				CChildView::thisPtr->USBCheckCopyAllFlag = false;
				while(CChildView::thisPtr->USBPresetName_temp.GetCount())
					CChildView::thisPtr->USBPresetName_temp.RemoveHead();
			}
		}
	}
	else
	{
		if(CChildView::thisPtr->OverWritePSPreset)
		{
			CopyPresetToPowerSupply(view);
			CChildView::thisPtr->OverWritePreset=false;
			CChildView::thisPtr->OverWritePSPreset=false;
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
			page_no=CChildView::thisPtr->menus.RemoveTail();
			theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
			CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			view->Invalidate();
			return ;
		}

		view->ShowMessageScreen(StrM5_35);
		CopyPresetToUSB(view,CChildView::thisPtr->CopyPresetNum);

		if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
			CChildView::thisPtr->CopyPresetNum++;
		if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
			CChildView::thisPtr->CopyPresetNum++;
		if(!CChildView::thisPtr->USBOverWritePreset  ||CChildView::thisPtr->CopyPresetNum >MaxPresetNum_InListBox )//||OverwritePreset(CopyPresetNum, 1,view))
		{
			CChildView::thisPtr->CopyPresetNum=0;
			CChildView::thisPtr->USBOverWritePreset=false;
			CChildView::thisPtr->OverWritePreset=false;
		}
	}
	
	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
	CChildView::thisPtr->Invalidate();
}
void CopyPresetOnOKOrCancelButton()
{
	int i = 0;
	char PresetNameBuf[13];
	int length = SIZEOFPRESETDATA;
	
	CVgaButton *ptr=(CVgaButton *)CChildView::thisPtr->CopyAllPresetAddress;
	char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
	StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
	if(CChildView::thisPtr->CChildView::thisPtr->PresetOverwriteCheckedFlag)
	{
		CChildView::thisPtr->CChildView::thisPtr->PresetOverwriteCheckedFlag = false;
		if(CChildView::thisPtr->CancelButtonFlag)
		{
			CChildView::thisPtr->CancelButtonFlag = false;
			CChildView::thisPtr->PresetListBuff += SIZEOFPRESETDATA;
		}
		else
			WriteDataToUSBFile(CChildView::thisPtr,CChildView::thisPtr->PresetListBuff,length);

		PresetCount++;
	}

	for(i = PresetCount;i<CChildView::thisPtr->PresetNameCount && !CChildView::thisPtr->USBCheckCopyAllFlag;i++)
	{
		CString DiskStr = USBDISK;
		CChildView::thisPtr->CheckAvailablDiskSpace(DiskStr);
		if(CChildView::thisPtr->USBCheckCopyAllFlag)
		{
		
			CString errstr = "";
			errstr.Format(_T("USB Memory Full"));
			AfxMessageBox(errstr);
			return;
		}
		length = SIZEOFPRESETDATA;
		memcpy(PresetNameBuf,CChildView::thisPtr->PresetListBuff+331,13);
		CChildView::thisPtr->PresetName = CString(PresetNameBuf);
		CChildView::thisPtr->PresetName.TrimLeft();
		CChildView::thisPtr->PresetName.TrimRight();

		if(!OverwritePreset(PresetCount+1, 1,CChildView::thisPtr,CChildView::thisPtr->CopyAllPresetAddress_Ok))
		{
			WriteDataToUSBFile(CChildView::thisPtr,CChildView::thisPtr->PresetListBuff,length);
			PresetCount++;
		}
		else
		{
			if(CChildView::thisPtr->CancelButtonFlag)
			{
				CChildView::thisPtr->CancelButtonFlag = false;
				CChildView::thisPtr->PresetListBuff += SIZEOFPRESETDATA;
			}
			else
				WriteDataToUSBFile(CChildView::thisPtr,CChildView::thisPtr->PresetListBuff,length);
			PresetCount++;
			break;
		}
	}
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);  
}
void OverWriteCancelButton(int Address)
{
	CChildView *view=CChildView::thisPtr;
	CVgaButton *ptr=(CVgaButton *)Address;
	char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
	StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	if(CChildView::thisPtr->USBOverWritePreset == true)
	{
		CChildView::thisPtr->CancelButtonFlag = true;
		CChildView::thisPtr->CopyAllPresetAddress_Ok = Address;
		if(PresetCount < CChildView::thisPtr->PresetNameCount)
			 CChildView::thisPtr->BuildPrintList(COPYALL_PRESET_TOUSB_OK);
		else
		{
			CChildView::thisPtr->USBOverWritePreset = false;			
			if(StoredPresetListData)
			{
				delete StoredPresetListData;
				CChildView::thisPtr->PresetListBuff = NULL;
				StoredPresetListData = NULL;
				PresetCount = 0;	
				while(CChildView::thisPtr->USBPresetName_temp.GetCount())
					CChildView::thisPtr->USBPresetName_temp.RemoveHead();
			}
		}
	}
	else
	{
		if(CChildView::thisPtr->OverWritePSPreset)
		{
			CChildView::thisPtr->OverWritePreset=false;
			CChildView::thisPtr->OverWritePSPreset=false;
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
			page_no=CChildView::thisPtr->menus.RemoveTail();
			theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
			CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
			CChildView::thisPtr->Invalidate();
			return ;
		}
		CChildView::thisPtr->ShowMessageScreen(StrM5_35);
	
		if(CChildView::thisPtr->CopyPresetNum==MaxPresetNum_InListBox)
			CChildView::thisPtr->CopyPresetNum++;
		if(!CChildView::thisPtr->USBOverWritePreset  ||(CChildView::thisPtr->CopyPresetNum) >MaxPresetNum_InListBox )//||OverwritePreset(CopyPresetNum, 1,view))
		{
			CChildView::thisPtr->CopyPresetNum=0;
			CChildView::thisPtr->USBOverWritePreset=false;
			CChildView::thisPtr->OverWritePreset=false;
		}
	}
	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);      
	CChildView::thisPtr->Invalidate();
}

void ProcessUSBMemoryScreen(int Address)
{
	CChildView::thisPtr->SelectedPowerPreset=CChildView::thisPtr->CurrentPresetNum;
	CChildView::thisPtr->LastSelectedPresetFrom=PSPresetSelected;
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	CChildView::thisPtr->Invalidate();
}
void CopyAllPowerPreset(int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
	char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
	StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
	int Strating_PresetNum = 1;
	unsigned char data1[4];
	int length = 0;
	//coverity fix 12551 
	int TotalPresetData = 0;
	int PresetLength = SIZEOFPRESETDATA;
	CChildView::thisPtr->PresetNameCount = 0;
	CChildView::thisPtr->USBOverWritePreset = true;
	int PresetIndexText = 0;
	if(StoredPresetListData)
	{
		delete StoredPresetListData;		
		CChildView::thisPtr->PresetListBuff = NULL;
		StoredPresetListData = NULL;
	}
	union {
		int value;
		char y[INTEGERLENGTH];
	} v;
	CString PresetNameData = "";
	CChildView::thisPtr->PresetListBuff = new unsigned char[MAXPRESETBUFFSIZE];
	StoredPresetListData = CChildView::thisPtr->PresetListBuff;
	int offset = 0;
	do{
		v.value = Strating_PresetNum;
		data1[0]=(char)v.y[1];
		data1[1]=(char)v.y[0];
		unsigned char * data = (unsigned char *) &data1[0];
		//coverity fix 12553
		CHostCommand * request = new CHostCommand(COPY_ALL_PRESET_COMMAND,data,INTEGERLENGTH);
		CHostCommand * response = app->SendUiHostCommand(request);
		int PresetPosCount = 0;
		if(response)
		{
			char ch=CHostCommand::AckNak();
			if(ch==theApp.ACK)
			{
				data = response->GetData();
				int logPresetData = *((int*)(data));	//number of Data.
				data+=4;
				int presetindex = *((int*)(data));	//number of Data.
				TotalPresetData = ntohl(logPresetData);
				PresetIndexText = ntohl(presetindex);
				data+=sizeof(int);
				for(int i = 0;i<TotalPresetData;i++ )
				{
					CChildView::thisPtr->PresetNameCount++; //This counter is to keep total no of preset data available.
					PresetPosCount++; //This counter is to keep the total no of preset data we received from wc inorder to increment the position of buffer. 
				}
				memcpy(CChildView::thisPtr->PresetListBuff + offset,data,SIZEOFPRESETDATA*PresetPosCount);
				offset += SIZEOFPRESETDATA*PresetPosCount;
				Strating_PresetNum=PresetIndexText;
			}
			else
			{
				delete response;
				break;
			}

			}
		}
		while(TotalPresetData == 10 && PresetIndexText <=1000);
		CChildView::thisPtr->CopyAllPresetAddress = Address;
		CChildView::thisPtr->BuildPrintList(COPYALL_PRESET_TOUSB);
	//}
	//else
	//{
	//	ProcessNak(Address);
	//	DisplayMessage(0);	//Display Weld Cycle Running	
	//	CChildView::thisPtr->Invalidate();
	//}
}
void CopyAllPreset()
{
	PresetCount = 0;
	CVgaButton *ptr=(CVgaButton *)CChildView::thisPtr->CopyAllPresetAddress;
	char TempArray[10];
	CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
	StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
	CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
	int length = 0;
	char PresetNameBuf[13];
	EstopPressedFlag = false;
	CChildView::thisPtr->USBCheckCopyAllFlag = false;
	int Count_UsbPresetName = 0;
	while(CChildView::thisPtr->USBPresetName_temp.GetCount())
		CChildView::thisPtr->USBPresetName_temp.RemoveHead();
	Count_UsbPresetName = CChildView::thisPtr->USBPresetNames.GetCount();
	for(int k = 0;k<Count_UsbPresetName;k++)
		CChildView::thisPtr->USBPresetName_temp.AddTail(CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(k)));
	
	for(int i = 0;i<CChildView::thisPtr->PresetNameCount && !EstopPressedFlag && !CChildView::thisPtr->USBCheckCopyAllFlag;i++)
	{
		CString DiskStr = USBDISK;
		CChildView::thisPtr->CheckAvailablDiskSpace(DiskStr);
		if(CChildView::thisPtr->USBCheckCopyAllFlag)
		{
		
			CString errstr = "";
			errstr.Format(_T("USB Memory Full"));
			AfxMessageBox(errstr);
			return;
		}
		memcpy(PresetNameBuf,CChildView::thisPtr->PresetListBuff+331,13);
		CChildView::thisPtr->PresetName = CString(PresetNameBuf);
		CChildView::thisPtr->PresetName.TrimLeft();
		CChildView::thisPtr->PresetName.TrimRight();
		if(!OverwritePreset(i+1, 1,CChildView::thisPtr,CChildView::thisPtr->CopyAllPresetAddress))
		{
			CChildView::thisPtr->FoundPresetToCopy = true;
			length = SIZEOFPRESETDATA;
			WriteDataToUSBFile(CChildView::thisPtr,CChildView::thisPtr->PresetListBuff,length);
			PresetCount++;
		}
		else 
		{
			CChildView::thisPtr->PresetOverwriteCheckedFlag = true;		
			return;
		}

	}		
	if(CChildView::thisPtr->FoundPresetToCopy)
	{
		CChildView::thisPtr->FoundPresetToCopy = false;
		CChildView::thisPtr->USBOverWritePreset = false;
		PresetCount = 0;
		while(CChildView::thisPtr->USBPresetName_temp.GetCount())
			CChildView::thisPtr->USBPresetName_temp.RemoveHead();
		CChildView::thisPtr->USBCheckCopyAllFlag = false;
		CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
		CChildView::thisPtr->Invalidate();		
	}
}

void DeleteSelectedUSBPreset(CChildView *view,int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   char TempArray[10];
   CString StrM5_35=_itoa(ptr->EnumID,TempArray,10);
   StrM5_35=CVgaMenuItem ::LinearSearch(StrM5_35);
   /* Showing message screen.*/
   view->GetDc();

   view->ShowMessageScreen(StrM5_35);
   CChildView::DisableFlag=true;
   CChildView::InitialiseTimer(ERROR_MESSAGE_TIMER,200);

   CChildView::PSName =view->PowerSupply;
   CString	pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+ CChildView::USBPresetNames.GetAt(CChildView::USBPresetNames.FindIndex(CChildView::SelectedUSBPreset-1))+".prst";
   CFile f;
   CFileException e;
   bool FileFound=false;
   if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {
      FileFound=true;
      f.Close();		
   }
   if(FileFound)
      CFile::Remove(pFileName);
   else
      CChildView::ErrorBeep();
}

void DeleteUSBPreset(int Address)
{
   if(CChildView::thisPtr->SelectedUSBPreset>0)
   {
      DeleteSelectedUSBPreset(CChildView::thisPtr,Address);
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      int Temp=	CChildView::thisPtr->SelectedUSBPreset;
      int Temp1 =CChildView::thisPtr->SelectedPowerPreset;
      if(CChildView::thisPtr->USBPresetNames.GetCount()>=Temp)
      {
         CChildView::thisPtr->SelectedUSBPreset=Temp;
      }
      else if(CChildView::thisPtr->USBPresetNames.GetCount()>0)
      {
         CChildView::thisPtr->SelectedUSBPreset=1;
      }
      else if(CChildView::thisPtr->USBPresetNames.GetCount()==0)
         CChildView::thisPtr->SelectedUSBPreset=0;
      CChildView::thisPtr->SelectedPowerPreset=Temp1;
      CChildView::thisPtr->Invalidate();
   }  
   else
      CChildView::ErrorBeep();
}

void CopyUSBPreset(int Address)
{
   CVgaMenu *menu1=theApp.MenuPointer;
   if((CChildView::thisPtr->SelectedPowerPreset>0) && (CChildView::thisPtr->SelectedUSBPreset))
   {

      if(!OverwritePreset(CChildView::thisPtr->SelectedPowerPreset, 0,CChildView::thisPtr,Address))
      {
         if(CopyPresetToPowerSupply(CChildView::thisPtr))
         {
            CVgaMenuItem * Object;
            POSITION pos = menu1->items.GetHeadPosition();
            while(pos)
            {
               Object = menu1->items.GetNext(pos);
               if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
               {
                  CListBoxObject *obj=(CListBoxObject*)Object;
                  for(int i =0;i<obj->MaxPreset;i++)
                     obj->ListBoxText[i]=CChildView::thisPtr->PSPresetText[i];
                  break;
               }
            }
            CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
            CChildView::thisPtr->Invalidate();
         }
         else
            CChildView::thisPtr->Invalidate();
      }
   }
   else
      CChildView::ErrorBeep();
}

/******************************************************************************/
/* This Function will Browes the USB Memory and prepare the USB memory screen.*/
/******************************************************************************/
void BrowesUSBFolder(CChildView *view,int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;

   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;

   CString argv=_T(USBDISKDRIVE);
   CString DirSpec;  
   DirSpec=argv+_T("\\*");
   hFind = FindFirstFile(DirSpec, &FindFileData);
   if (hFind == INVALID_HANDLE_VALUE) 
   {
      FindClose(hFind);
      return ;
   } 
   else 
   {
      if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
      {
         FindClose(hFind);
         view->PrepareUSBList(USBDISKDRIVE,USBPRESETFOLDER,ptr->EnumID);
         view->Invalidate();
         return ;
      }
      while (FindNextFile(hFind, &FindFileData) != 0) 
      {
         if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
         {
            FindClose(hFind);
            view->PrepareUSBList(USBDISKDRIVE,USBPRESETFOLDER,ptr->EnumID);
            view->Invalidate();
            return ;
         }
      }
   }

}

void BowseUSBFolder(int Address)
{
   BrowesUSBFolder(CChildView::thisPtr,Address);
}

void ViewPowerPreset(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   CVgaMenu *menu=theApp.MenuPointer;
   if(CChildView::thisPtr->SelectedUSBPreset>=1){
      printf("\n  CChildView::thisPtr->USBSelectedPresetName %S", CChildView::thisPtr->USBSelectedPresetName);
      printf("\n  CChildView::thisPtr->USBPresetNames.GetCount() %d ", CChildView::thisPtr->USBPresetNames.GetCount());
      if(CChildView::thisPtr->USBPresetNames.GetCount() > 0)
         CChildView::thisPtr->USBSelectedPresetName=CChildView::thisPtr->USBPresetNames.GetAt(CChildView::thisPtr->USBPresetNames.FindIndex(CChildView::thisPtr->SelectedUSBPreset-1));
      else
         CChildView::thisPtr->SelectedUSBPreset = 0;
   }
   CVgaMenuItem * Object;
   CString Menuname,MenuNak;
   POSITION pos = menu->items.GetHeadPosition();
   while(pos)
   {
      Object = menu->items.GetNext(pos);

      if(Object->GetType() == CVgaMenu::VGAMsgScrnObject)
      {
         CMsgScreen * MsgScreen=(CMsgScreen *)Object;
         Menuname=MsgScreen->submenu;
         MenuNak=MsgScreen->menunak;
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         break;
      }
   }
   switch(CChildView::thisPtr->LastSelectedPresetFrom)
   {
   case PSPresetSelected:
      {
         if((CChildView::thisPtr->PSPresetText[CChildView::thisPtr->SelectedPowerPreset-1]).GetLength()>3)
         {
            if (theApp.menus.Lookup(Menuname, menu))
            {
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               page_no=1;
               theApp.menuName = Menuname;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu);
            }
         }
         else
         {
            CChildView::ErrorBeep();
            return;
         }
      }
      break;
   case USBPresetSelected:
      {
         if(CChildView::thisPtr->SelectedUSBPreset>=1)
         {
            if (theApp.menus.Lookup(MenuNak, menu))
            {
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               page_no=1;
               theApp.menuName = MenuNak;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu);
            }
         }
         else
         {
            CChildView::ErrorBeep();
            return;
         }			
      }
      break;
   }
   CChildView::thisPtr->Invalidate();
}

void USBRecall(int Address)
{
   CVgaButton *ptr=(CVgaButton*)Address;
   WrapAroundWeldFlag = false;
   DownFlagErrorBeep = false;
   if(!CChildView::ISUSBPresent)
   {
      CChildView::ErrorBeep();
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
      return ;
   }				
   /* For USB */
   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   CString argv=_T(USBDISKDRIVE);
   CString DirSpec;  
   DirSpec=argv+_T("\\*");
   hFind = FindFirstFile(DirSpec, &FindFileData);
   if (hFind == INVALID_HANDLE_VALUE) 
   {
      FindClose(hFind);
      return ;
   } 
   else 
   {
      if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(CChildView::thisPtr->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
      {
         FindClose(hFind);
         CChildView::thisPtr->PrepareUSBList(USBDISKDRIVE,FOLDERHIERARCHYONE,ptr->EnumID);
         CChildView::thisPtr->Invalidate();
         return ;
      }
      while (FindNextFile(hFind, &FindFileData) != 0) 
      {
         if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(CChildView::thisPtr->ValidFolderName(FindFileData.cFileName,FOLDERHIERARCHYONE)))
         {
            FindClose(hFind);
            CChildView::thisPtr->PrepareUSBList(USBDISKDRIVE,FOLDERHIERARCHYONE,ptr->EnumID);
            CChildView::thisPtr->Invalidate();
            return ;
         }
      }
   }
   /*USB code ends here*/
   return ;
}

void ExitHistoryMenu(int Address)
{
   TRY
   {
      if(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
         CChildView::thisPtr->Invalidate();
         return ;
      }
      if(!CChildView::ISUSBPresent)
      {
         CVgaMenu * menu;
         if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
         {
            theApp.menuName=CVgaBottomMenu::mainMenuID;
            theApp.MenuPointer=menu;
            CChildView::thisPtr->ModifyObjectList(menu); 
            CChildView::thisPtr->Invalidate();
         }
         return ;
      }
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      //CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFilePath,FOLDERHIERARCHYTHREE,ptr->EnumID);
      CChildView::thisPtr->Invalidate();
   }
   CATCH_ALL(E)
   {
      TCHAR szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The error: ");
      x += szCause;
      AfxMsgBox(x);
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID,menu))
      {
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
      }
   }
   END_CATCH_ALL
}

void HandleFolderHierarchyExit(int Address)
{
   CVgaMenu *menu;
   menu=theApp.MenuPointer;
   bool flag=false;
   int Fun_Id = 0,TitleID = 0;
   POSITION pos =menu->items.GetHeadPosition();
   CVgaMenuItem *Obj;// =view->menuEntryList.GetNext(pos);
   while(pos)
   {
      Obj =menu->items.GetNext(pos);
      if(Obj->GetType()==CVgaMenu::SUBMENU)
      {
         CUSBFolder *ptr=(CUSBFolder *)Obj;
         flag=true;
         Fun_Id=ptr->Fun_Id;
         TitleID=ptr->TitleID;
         break;
      }
   }
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   if((Fun_Id >FOLDERHIERARCHYONE)&&(Fun_Id<=FOLDERHIERARCHYFOUR))
   {
      if(flag == true)
      {
         CUSBFolder *object =(CUSBFolder*)Obj;
         CString PreviousPath = object->Path;
         int x=0;
         while(x!=2)
         {
            if(PreviousPath.Right(1)==("\\"))
               x++;
            PreviousPath.Delete(PreviousPath.GetLength()-1,1);
         }
         CChildView::thisPtr->PrepareUSBList(PreviousPath,Fun_Id-1,TitleID);
         CChildView::thisPtr->Invalidate();
      }
      else
      {
         if(!CChildView::ISUSBPresent)
         {
            CVgaMenu * menu;
            if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
            {
               theApp.menuName=CVgaBottomMenu::mainMenuID;
               theApp.MenuPointer=menu;
               CChildView::thisPtr->ModifyObjectList(menu); 
               CChildView::thisPtr->Invalidate();
               return;
            }
         }
         int x=0;
         while(x!=1)
         {
            if(CUSBFolder::LastFolderPath.Right(1)==("\\"))
               x++;
            CUSBFolder::LastFolderPath.Delete(CUSBFolder::LastFolderPath.GetLength()-1,1);
         }
         CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFolderPath,Fun_Id,TitleID);
         CChildView::thisPtr->Invalidate();
      }
   }
   else
   {
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      CChildView::thisPtr->Invalidate();
   }
}

bool AddGraphIfFound(CString GraphPath, CChildView *view)
{
   CVgaMenu *menu=theApp.MenuPointer;
   CFile f;
   CFileException e;

   if( f.Open( GraphPath, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {	
      if(!f.GetLength())
      {
         f.Close();
         return false;
      }
      f.SeekToBegin();
      CVgaDrawGraph * tempGraph= new CVgaDrawGraph();
      int  size= sizeof(tempGraph->GraphData);
      delete tempGraph;
      char Comma;

      int ObjectSize = sizeof(int)+ sizeof(Comma)+ size + sizeof(Comma);
      int NoOfGraphObjects = ((int)f.GetLength())/ObjectSize;
      int ID;
	  bool GraphAdded = false;//coverity 12571
      for(int GraphNum =0;GraphNum<NoOfGraphObjects;GraphNum++)
      {
         f.SeekToBegin();
         f.Seek( (ObjectSize*GraphNum),CFile::begin);
         f.Read(&ID,sizeof(int));
		 
         if(ID==CWeldingHistory::thisHisPtr->SelectedWeldId)
         {	
            CVgaDrawGraph * Graph= new CVgaDrawGraph();
            CVgaDrawGraph::GraphCount--;
            f.Read(&Comma,sizeof(char));
            f.Read(&(Graph->GraphData),size);
            POSITION pos = menu->items.GetHeadPosition();
			GraphAdded = false;//coverity 12571
            while (pos)
            {
               CVgaMenuItem * object = menu->items.GetNext(pos);
               int type = object->GetType();
               if(type ==VGAHistoryGraphObject)
               { 
                  CHistoryGraphs *obj = (CHistoryGraphs *)object;
                  obj->HistoryGraphList.AddTail(Graph);
				  GraphAdded = true;//coverity 12571
                  if(obj->HistoryGraphList.GetCount()==1)
                  {
                     obj->Graph1ID=Graph->GraphData.graph_type;
                     obj->LastGraphDisplayed=Graph->GraphData.graph_type;
                     obj->Graph2ID=-1;
                  }
                  break;
               }
            }
			if(!GraphAdded)//coverity 12571
				delete Graph;
         }
      }
      f.Close();
   }
   return false;
}

bool PrepareHistoryGraphList(CChildView *view)
{
   CVgaMenu *menu=theApp.MenuPointer;
   CString Path = CUSBFolder::HistoryGraphPath+"\\";

   CString FileName="PowerGraph.log";
   CString GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   FileName="ColDistGraph.log";
   GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   FileName="VelocityGraph.log";
   GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   FileName="ForceGraph.log";
   GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   FileName="AmpGraph.log";
   GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   FileName="FreqGraph.log";
   GraphPath=	Path+FileName;
   AddGraphIfFound(GraphPath,view);

   POSITION pos = menu->items.GetHeadPosition();
   CVgaMenuItem * object;
   while (pos)
   {
      object = menu->items.GetNext(pos);
      int type = object->GetType();
      if(type ==VGAHistoryGraphObject)
      {
         CHistoryGraphs *obj = (CHistoryGraphs *)object;
         if(obj->HistoryGraphList.GetCount()>0)
            return true;
         else
            return false;
         break;
      }
   }
   return false;
}

void ProcessHistoryGraph(int Address)
{  
   CVgaMenu *menu=theApp.MenuPointer;
   CString StrM5_35,Str_NoValidGraph;
   POSITION pos1 = menu->items.GetHeadPosition();
   CVgaMenuItem *Object= 0;
   int count=0;
   while (pos1)
   {
      Object= menu->items.GetNext(pos1);
      if((Object->GetType()==CVgaMenu::VGAMsgScrnObject))
      {
         count++;
        
         if(count==1)
         {
            StrM5_35=Object->text;
         }
         else
         {
            Str_NoValidGraph=Object->text;
         }

      }
      else if(Object->GetType()==VGAHistoryGraphObject)
      {
         while(((CHistoryGraphs *)Object)->HistoryGraphList.GetCount())
            free(((CHistoryGraphs *)Object)->HistoryGraphList.RemoveHead()); 				
      }
   }
   CChildView::thisPtr->ShowMessageScreen(StrM5_35);
   if(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount())
   {
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->ShowMessageScreen(Str_NoValidGraph);
      return ;
   }

   if(!CChildView::ISUSBPresent)
   {	
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
      {
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
         return;
      }
   }


   if(!PrepareHistoryGraphList(CChildView::thisPtr))
   {
      CChildView::thisPtr->ShowMessageScreen(Str_NoValidGraph);
      theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
      page_no=CChildView::thisPtr->menus.RemoveTail();
      theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
   }
   else
   {		
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
      CChildView::thisPtr->Invalidate();
   }
}

void UpdateScreenGraphs(int Type)
{
   CVgaMenu *menu=theApp.MenuPointer;
   CVgaMenuItem *object= 0;
   POSITION pos = menu->items.GetHeadPosition();
   while (pos)
   {
      object = menu->items.GetNext(pos);
      int type = object->GetType();
      if(type ==VGAHistoryGraphObject)
      {
         CHistoryGraphs *ptr=(CHistoryGraphs *)object;
         if(ptr->Graph1ID == Type)
         {
            if(ptr->Graph2ID !=-1)
            {
               ptr->Graph1ID=ptr->Graph2ID;
               ptr->LastGraphDisplayed=ptr->Graph2ID;
               ptr->Graph2ID=-1;
            }
         }
         else if(ptr->Graph2ID == Type)
         {
            ptr->Graph2ID=-1;
            ptr->LastGraphDisplayed=ptr->Graph1ID;
         }
         else
         {
            POSITION pos = ptr->HistoryGraphList.GetHeadPosition();
            while(pos)
            {	
               CVgaDrawGraph *Object = ptr->HistoryGraphList.GetNext(pos);
               if(Object->GraphData.graph_type==Type)
               {
                  if(ptr->Graph2ID!=ptr->LastGraphDisplayed)
                     ptr->Graph2ID = Type;
                  else
                     ptr->Graph1ID = Type;

                  ptr->LastGraphDisplayed=Type;
                  break;
               }
            }
         }
         break;
      }
   }

}

void ProcessUSBVelocityGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=VELMMGRAPH;
   else
      type=VELINGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBFrquencyGraph(int Address)
{
   UpdateScreenGraphs(FREQUGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBColDistanceGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=DISTMMGRAPH;
   else
      type=DISTINGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBForceGraph(int Address)
{
   int type;
   if(CChildView::thisPtr->metric)
      type=FORCENGRAPH;
   else
      type=FORCELBGRAPH;
   UpdateScreenGraphs(type);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBPowerGraph(int Address)
{
   UpdateScreenGraphs(POWGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ProcessUSBAmplitudeGraph(int Address)
{
   UpdateScreenGraphs(AMPLIGRAPH);
   CChildView::thisPtr->Invalidate();
}

void ExitHistoryGraph(int Address)
{
   if(!CChildView::ISUSBPresent)
   {	
      CVgaMenu * menu;
      if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
      {
         page_no=1;
         theApp.menuName=CVgaBottomMenu::mainMenuID;
         theApp.MenuPointer=menu;
         CChildView::thisPtr->ModifyObjectList(menu); 
         CChildView::thisPtr->Invalidate();
         return;
      }
   }
   
   theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
   page_no=CChildView::thisPtr->menus.RemoveTail();
   theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer); 
   CChildView::thisPtr->Invalidate();
}

void ProcessDiagnosticScreen(int Address)
{
   CString MenuName="";
   CVgaMenu * menu1=theApp.MenuPointer;
   CChildView::thisPtr->DiagIOScreen = false;
   POSITION pos = menu1->items.GetHeadPosition();
   CChildView::thisPtr->KillTimers(DIAGNOSTICS_USERIO_TIMER);
   printf(" ProcessDiagnosticScreen() diag timer killed ");
   CVgaMenuItem * Object;
   while(pos)
   {
      Object = menu1->items.GetNext(pos);
      if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
      {
         CBottomHalf *obj=(CBottomHalf*)Object;
         MenuName=obj->submenu;
         CVgaMenu * menu;
         if (theApp.menus.Lookup(MenuName, menu))
         {
            CBottomHalf::BottomMenuPointer=menu;
         }
         CChildView::thisPtr->MenuNameID=MenuName;
         CBottomHalf::BottomHalfId=obj->EnumID;
         CChildView::BotomHalfRefreshTime=obj->RefreshTime;
         break;
      }
   }
   CChildView::thisPtr->Invalidate();
}

void ProcessHornSignature(int ID)
{
   int length =2;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];

   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   printf("\n hs1 ,");
   if(response)
   {
      printf(" hs2 ,");
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         printf(" hs3 ,");
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
         CString MenuName="";
         CVgaMenu * menu1=theApp.MenuPointer;
         POSITION pos = menu1->items.GetHeadPosition();
         CVgaMenuItem * Object;
         while(pos)
         {
            Object = menu1->items.GetNext(pos);
            if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
            {
               CBottomHalf *obj=(CBottomHalf*)Object;
               MenuName=obj->submenu;
               CVgaMenu * menu;
               if (theApp.menus.Lookup(MenuName, menu))
               {
                  CBottomHalf::BottomMenuPointer=menu;
               }
               CChildView::thisPtr->MenuNameID=MenuName;
               CBottomHalf::BottomHalfId=obj->EnumID;
               CChildView::thisPtr->BottomHalfScreen=true;
               CChildView::BotomHalfRefreshTime=obj->RefreshTime;
               break;
            }
         } 
         CChildView::thisPtr->Invalidate();
      }
      else if(ch==theApp.NAK)
      {
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();	
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ProcessNak(data,length,0,0);
      }
      delete response;
   }
}

void ProcessResetAlarms(int Address)
{			
   CHostCommand * request = new CHostCommand(RESETALARMS_FUNID,0,0);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      delete response;
   }
}

void ProcessSoftwareMismatchError(int Address)
{			
    //AfxMessageBox(_T("mismatch3"));
   theApp.Clean ();
  // AfxMessageBox(_T("mismatch5"));
   exit(1);
}


void SendCommandForUserID(int ID)
{
	if(creating_pdf)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
		theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		CChildView::thisPtr->ErrorBeep();
		CChildView::thisPtr->Invalidate();
	}
	else
	{
		if(CChildView::thisPtr->ISUSBPresent == true)
		{
			if(CChildView::thisPtr->GetStateMachineStatus() == true)        
			{
				CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);			
				while(CUserIDTable::thisPtr->UserIDList.GetCount())
					delete CUserIDTable::thisPtr->UserIDList.RemoveHead();
				printf("in SendCommandForUserID ID=%d",ID);	
				CChildView::thisPtr->ShowMessageScreen2(PleaseWait);
				creating_pdf=true;
				CChildView::thisPtr->BuildPrintList(USERID);			
				printf("...####...status=%d\n",userid_list_status);				
				if((userid_list_status==NO_VALID_DATA)||(userid_list_status==COMM_ERROR))//some error in retreiving data
				{
					CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
					printf("comm failure\n");
					ProcessNak(ID);			
					DisplayMessage(userid_list_status);	
					CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
					CChildView::thisPtr->Invalidate();
				}
			} 
			else
			{
				printf("else block\n");
				ProcessNak(ID);	
				DisplayMessage(0);
				CChildView::thisPtr->Invalidate();
			}
		}
		else
		{
			ProcessNak(ID);
			DisplayMessage(3);	//connect usb
			CChildView::thisPtr->Invalidate();
		} 
	}
}


void SendCommandForEventLog(int Address)
{
	if(creating_pdf)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
		theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		CChildView::thisPtr->ErrorBeep();
		CChildView::thisPtr->Invalidate();
	}
	else
	{
		while(CEventLog::thisHisPtr->EventLogList.GetCount())
			delete CEventLog::thisHisPtr->EventLogList.RemoveHead();
		CFile f;
		CFileException e;
		if(CChildView::thisPtr->ISUSBPresent == true)
		{
			if(CChildView::thisPtr->GetStateMachineStatus() == true )		 
			{		
				if((f.Open( EventDataFileName, CFile::modeRead ,&e) ) && f.GetLength()>MIN_EVENT_FILESIZEPDF)
				{
					CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);
					f.Close();
					SetupTemp_pos = NULL;
					SetupTemp_pos = tempSetupList.GetHeadPosition();
					CString StrM5_35;
					tempSetupList.GetNext(SetupTemp_pos);
					StrM5_35 = tempSetupList.GetNext(SetupTemp_pos);
					CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
					creating_pdf=true;
					CChildView::thisPtr->BuildPrintList(EVENTLIST);
				}
				else
				{
					ProcessNak(Address);
					DisplayMessage(1);	//Display No valid data
					CChildView::thisPtr->Invalidate();
				}
			}
			else
			{
				ProcessNak(Address);
				DisplayMessage(0);	//Display Weld Cycle Running	
				CChildView::thisPtr->Invalidate();
			}
		}
		else
		{
			ProcessNak(Address);
			DisplayMessage(3);	//connect usb
			CChildView::thisPtr->Invalidate();
		} 
	}
}

void SendCommandForChangePassword(int Address)//remove the argument int from main.gui,otherwise ProcessNak function will not work
{
   printf("in SendCommandForUser change password ID=%d",Address);
   CChildView::LoginScreenFlag=false;
   int Response=0xff;
   unsigned char * data;
   int length = CHANGEPASSWORD_LEN;
   unsigned char data1[CHANGEPASSWORD_LEN];
   memset(data1,0,sizeof(data1));

   CString MenuNak;
   CString MenuName;
   CString UserName=CurrentUser;

   CVgaMenu *menu1=CChildView::thisPtr->menupointers.GetTail();
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();
   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::ALPHA)
      {
         CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
         if( ptr->textID == XSTR(USERID_ID  ))
         {			
            strcpy(CScreenKeypad::Assign_UserID,CurrentUser);
            ptr->Alpha_Text=" = "+ UserName;

         }
         else
            ptr->ClearAlphaString();
      }
   }
   strcpy((char *)(data1),CScreenKeypad::Assign_UserID);	
   strcpy((char *)(data1+11),CScreenKeypad::Old_Password);	
   strcpy((char*)(data1+22),CScreenKeypad::New_Password);	
   strcpy((char*)(data1+33),CScreenKeypad::Confirm_Password);
   if(strcmp(CScreenKeypad::Old_Password,CScreenKeypad::New_Password)==0)
	   Response = PASSWORD_CANNOT_BE_SAME;
   else
   		Response=Check_Password( CScreenKeypad::Old_Password,NULL,NULL,false,false);//first checks for old password strength,may be skipped	
   if(Response==ACCEPTED)
      Response=Check_Password(CScreenKeypad::New_Password,CScreenKeypad::Confirm_Password,CScreenKeypad::Assign_UserID,true,true);//checks for everything
   if(Response!=0)//Nak from sbc side
   {			    	
      ProcessNak(Address);
      DisplayMessage(Response);			   
   }


   if(Response==0)//if password strength is good then only sends the command
   {
      CHostCommand * request = new CHostCommand(CHANGEPASSWORD_FUNID,data1,length );
      CHostCommand * response = app->SendUiHostCommand(request);	
      if(response)
      {
         printf(" in response \n");
         char ch=CHostCommand::AckNak();
         if(ch==theApp.ACK)
         {
            printf(" login ACK  \n");
            data = response->GetData();
            length = response->GetDataLength();
            Response=*data;
            printf("\n data length = %d, data = %d",length,*data);
            if(Response!=0)// if any error on wc side then only display the error message.
            {  
               ProcessNak(Address);
               DisplayMessage(Response);			
            }

         }
         else if(ch==theApp.NAK)
            printf(" login NAK  \n");
         delete response;
      }
   }
   /* clears the buffers....*/

   memset(CScreenKeypad::Assign_UserID,0,sizeof(CScreenKeypad::Assign_UserID));
   memset(CScreenKeypad::Old_Password,0,sizeof(CScreenKeypad::Old_Password));
   memset(CScreenKeypad::New_Password,0,sizeof(CScreenKeypad::New_Password));
   memset(CScreenKeypad::Confirm_Password,0,sizeof(CScreenKeypad::Confirm_Password));	
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   This function is executed when user clicks login button on login screen
*Entry condition:
*   int Address:a pointer to the login button VGA holding the enable ID of button
*Exit condition:
*   none
***************************************************************************/
void SendCommandForUserLogin(int Address)
{
  
   int length = USERLOGIN_LEN;// 11 usr,11 pwd
   unsigned char data[USERLOGIN_LEN];
   unsigned char *data1;
   CVgaMenu *menu;
   CString MenuNak;
   CString MenuName;

   CVgaMenu *menu1=CChildView::thisPtr->menupointers.GetTail();
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();
   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::ALPHA)
      {
         CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
         if( ptr->textID == XSTR(USERID_ID))
         {			
            sprintf(CScreenKeypad::login_userID,"%s",ptr->GetAlphaString());
            printf("current name=%s\n",CScreenKeypad::login_userID);
            ptr->Alpha_Text=" = "+ ptr->GetAlphaString();

         }
         else
            ptr->ClearAlphaString();
      }
   }

   memset(data,0,USERLOGIN_LEN);
   strcpy((char *)(data),CScreenKeypad::login_userID);
   strcpy((char *)(data+11),CScreenKeypad::login_password);

   CHostCommand * request = new CHostCommand(USERLOGIN_FUNID,data,length);//coverty issue
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      printf(" in response \n");
      char ch=CHostCommand::AckNak();
      if(ch==theApp.ACK)
      {
         data1 = response->GetData();
         length = response->GetDataLength();
         printf("\n data length = %d, data = %x",length,*data1);
         if((*data1==WRONG_NAME_PASSWORD)
            ||(*data1==FIRST_TIME_LOGIN)
            ||(*data1==PASSWORD_EXPIRED)
            ||(*data1==LOW_AUTHORITY_EORROR)
            ||(*data1==MAX_WRONG_ATTEMPTS)
            ||(*data1==ALREADY_LOGGED_IN_THROUGH_WEBSERVICES)
			||(*data1==EXECUTIVE_PASSWORD_CHANGE)) //incorrect password or username,or first time login,low authority,
         {
            if((*data1==FIRST_TIME_LOGIN)||(*data1==PASSWORD_EXPIRED)||(*data1==EXECUTIVE_PASSWORD_CHANGE))
               strcpy(CurrentUser,CScreenKeypad::login_userID);
            ProcessNak(Address);//take the control to menunak
            if(*data1==WRONG_NAME_PASSWORD)     // incorrect username or password
               DisplayMessage(1);
            else if(*data1==FIRST_TIME_LOGIN)
               DisplayMessage(0);//first time login *data=10
            else if(*data1==PASSWORD_EXPIRED)
               DisplayMessage(3);
			else if(*data1==EXECUTIVE_PASSWORD_CHANGE)
               DisplayMessage(7);
            else if(*data1==LOW_AUTHORITY_EORROR)
               DisplayMessage(4);
            else if(*data1==MAX_WRONG_ATTEMPTS)
               DisplayMessage(5);
            else if(*data1==ALREADY_LOGGED_IN_THROUGH_WEBSERVICES)
               DisplayMessage(6);
			CChildView::thisPtr->Invalidate();
         }
         else
         {   
            strcpy(CurrentUser,CScreenKeypad::login_userID);
            theApp.GetSystemVariable();
            UserLoggedinFlag = true;
            if(CChildView::thisPtr->Start_Screen==MAINMENU)//if main menu
            {
               MenuName = CVgaBottomMenu::mainMenuID;
            }
            else
            {
               CChildView::thisPtr->RunResultScreen=true;
               MenuName = CVgaBottomMenu::WeldResults_ID;
            }

            if (theApp.menus.Lookup(MenuName, menu))
            {
               page_no=1;
               theApp.menuName = MenuName;
               theApp.MenuPointer = menu;
               CChildView::thisPtr->ModifyObjectList(menu);
            }
            CChildView::LoginScreenFlag = false;
            while(!CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON));
            if(CChildView::thisPtr->IdleLogoutTime>0)
               CChildView::InitialiseTimer(IDLELOGOUT_TIMER,CChildView::thisPtr->IdleLogoutTime);	
         }
         printf(" login ACK  \n");
      }
      else if(ch==theApp.NAK)
      {
         printf(" login NAK  \n");
      }
      delete response;
   }
   memset(CScreenKeypad::login_userID,0,sizeof(CScreenKeypad::login_userID));
   memset(CScreenKeypad::login_password,0,sizeof(CScreenKeypad::login_password));
   CChildView::thisPtr->Invalidate();
}

void ChangePassword(int ID)// clears the associated buffers
{
   CVgaMenu *menu1=theApp.MenuPointer;
   CVgaMenuItem * object = 0;
   CString UserName=CurrentUser;	
   POSITION pos = menu1->items.GetHeadPosition();

   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::ALPHA)
      {
         CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
         if( ptr->textID == XSTR(USERID_ID  ))
         {			
            strcpy(CScreenKeypad::Assign_UserID,CurrentUser);
            ptr->Alpha_Text=" = "+ UserName;

         }
         else
            ptr->ClearAlphaString();


      }
   }
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   This function is executed when user clicks on logout button this will set 
*   the LoginScreenFlag which is used to remove alarm button and bottom menu 
*   from "Login" and "Change Password" screen.This function also clears the 
*   string in login screen
*Entry condition:
*   int ID:an integer holding the enable ID of button
*Exit condition:
*   none
***************************************************************************/
void logOutFun(int ID)
{
	CChildView::LoginScreenFlag = true;
	UserLoggedinFlag = false;
	CVgaMenu *menu1=theApp.MenuPointer;
	CVgaMenuItem * object = 0;
	POSITION pos = menu1->items.GetHeadPosition();
	int length = LOGOUT_LEN;
	unsigned char * data;
	char ch = 0;
	data = (unsigned char*)&ch;
	if(CChildView::thisPtr->GetStateMachineStatus() == true)
	{
		CHostCommand * request = new CHostCommand(LOGOUT_FUNID, data,length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if(response)
		{
			CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);
			ch=CHostCommand::AckNak();
			data = response->GetData();
			length = response->GetDataLength();
			printf("\n data length = %d, data = ",length,*data);
			if(ch == theApp.ACK)
			{
				memset(CurrentUser,0,sizeof(CurrentUser));
				while(pos)
				{   
					object = menu1->items.GetNext(pos);  
					if(object->GetType()== CVgaMenu::ALPHA)
					{
						CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
						ptr->ClearAlphaString();
					}
				}
				CChildView::thisPtr->AlarmUpdateRequired = false;
			}
			else if(ch == theApp.NAK)
			{
				printf("\n NAK");
			}
			delete response;
		}
	}
	else if(ID != 0)
	{
		 CChildView::thisPtr->ErrorBeep();
		 ProcessNak(ID);
         DisplayMessage(0);	//Display Weld Cycle Running	
	}
	CChildView::thisPtr->Invalidate();
}

void DisableStateMachine(int ID)
{
   CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);
   CChildView::thisPtr->Invalidate();
}

void StopStateMachine(int ID)
{
	if(CChildView::thisPtr->GetStateMachineStatus() == true)
	{
		 CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);
		 CChildView::thisPtr->AlarmUpdateRequired = false;// on login screen no alarm button required
	}
	else
	{
		ProcessNak(ID);
		DisplayMessage(0);
	}
	CChildView::thisPtr->Invalidate();

}

void DiagUserIO(int ID)
{ 

	CHostCommand * request = new CHostCommand(GetWeldingStatus,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);   
	if(response)
	{
		char ch=CHostCommand::AckNak();     
		if(ch==theApp.ACK)
		{
			CChildView::thisPtr->DiagIOScreen = true;
			printf(" DiagIOScreen = %d \n", CChildView::thisPtr->DiagIOScreen);
			CChildView::thisPtr->SendPollingCommand();
			if(CChildView::thisPtr->BottomHalfTimerOn)
				CChildView::thisPtr->KillTimers(BOTTOMHALFTIMER);
			CChildView::thisPtr->BottomHalfTimerOn=false;
			CChildView::thisPtr->BottomHalfScreen=false;

		}	
		else if(ch==theApp.NAK)
		{
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
			page_no=CChildView::thisPtr->menus.RemoveTail();
			theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();

		}
		delete response;
	}
	CChildView::thisPtr->Invalidate();  
}

void RecallAlarmLogProcess(int ID)
{
   CAlarmLog::LeftMostParameter = 1;
   CAlarmLog::SelectedAlarmData = 1;
   CAlarmLog::TopMostData = 1;
   CAlarmLog::thisHisPtr->TotalColoumn = CChildView::TotalAlarmHeading;
   printf("RecallAlarmLogProcess\n");
   while(CAlarmLog::thisHisPtr->AlarmLogList.GetCount())
      delete CAlarmLog::thisHisPtr->AlarmLogList.RemoveHead();
   CChildView::thisPtr->BuildPrintList(ALARMLOGID);
   printf("Called BuildPrintList \n");
   CChildView::thisPtr->Invalidate();
}

void RecallEventLogProcess(int ID)
{
	CEventLog::LeftMostParameter = 1;
	CEventLog::SelectedEventData = 1;
	CEventLog::TopMostData = 1;
	CEventLog::thisHisPtr->TotalColoumn = CChildView::TotalEventHeading;
	TotalDataInFile = CEventLog::SuccessfullyWrittenEventRecord;
	TotalDisplayData = CEventLog::CurrentDisplayEventCount;
	int Count = 0;
	TotalCountRead = 0;
	FlagInitialScreen = true;
	WrapAroundFlag = false;
	ReadLimit = 0;
	if(CChildView::thisPtr->MemoryfullCont_Stop)
	{
		if((TotalDataInFile > MAX_ALLOWED_EVENT_LOG) ) //CChildView::thisPtr->MemoryfullCont_Stop
			WrapAroundFlag = true;
	}

	while(CEventLog::thisHisPtr->EventLogList.GetCount())
		delete CEventLog::thisHisPtr->EventLogList.RemoveHead();
	/*prepare list for 100 events*/
	CEventLog::TotalCycles = 0;
	if(TotalDataInFile <= MAX_ALLOWED_EVENT_LOG) // it does not matter the bit is true or false we need to read accordingly
	{
		if(TotalDataInFile >= MAX_EVENT_OBJECTS_PER_PAGE)
		{
			CurrentCountToReadEvent = TotalDataInFile;
			Count = MAX_EVENT_DISP_SIZE;
		}
		else
		{
			CurrentCountToReadEvent = TotalDataInFile;
			Count = TotalDataInFile;
		}
		PrepareListFromLog(EventDataFileName,Count,CurrentCountToReadEvent, true, true);
		CEventLog::TotalCycles = CEventLog::thisHisPtr->EventLogList.GetCount();
	}
	else
	{
		CurrentCountToReadEvent = CEventLog::CurrentDisplayEventCount; 
		if((CurrentCountToReadEvent !=0) && (CurrentCountToReadEvent < 8))
		{
			Count = CEventLog::CurrentDisplayEventCount;
			PrepareListFromLog(EventDataFileName,Count,CurrentCountToReadEvent, true, true,false);//to write in head
			Count = MAX_EVENT_DISP_SIZE - CEventLog::CurrentDisplayEventCount;
			CurrentCountToReadEvent = MAX_ALLOWED_EVENT_LOG ;     
			PrepareListFromLog(EventDataFileName,Count,CurrentCountToReadEvent, true, false,false);  //to write in tail
			CurrentCountToReadEvent = CurrentCountToReadEvent - Count ;  
			InitialScreenOverlap = true; //flag set to mark 1st overwrite.
			CEventLog::TotalCycles = CEventLog::thisHisPtr->EventLogList.GetCount();
		}
		else   //normal case
		{
			Count = CurrentCountToReadEvent;//MAX_EVENT_OBJECTS_PER_PAGE;
			if(CurrentCountToReadEvent == 0)
				CurrentCountToReadEvent = MAX_EVENT_DISP_SIZE;
			PrepareListFromLog(EventDataFileName,Count,CurrentCountToReadEvent, true, true,false);
			if(CurrentCountToReadEvent < MAX_EVENT_DISP_SIZE)
				Count = MAX_EVENT_DISP_SIZE - CurrentCountToReadEvent;
			else
				Count = CurrentCountToReadEvent - MAX_EVENT_DISP_SIZE;
			PrepareListFromLog(EventDataFileName,Count,TotalDataInFile, true, false,false);
			CEventLog::TotalCycles = CEventLog::thisHisPtr->EventLogList.GetCount();
		}
	}
	UpFlagErrorBeep = true;
	DownFlagErrorBeep = false;
	CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   UserIDScreenUpButton function is used to select the first entry in user list
*Entry condition:
*   int Address: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void UserIDScreenUpButton(int Address)
{
   if(CUserIDTable::thisPtr->TopMostData>MaxUserIDPerScreen)
   {
      (CUserIDTable::thisPtr->TopMostData)-=MaxUserIDPerScreen;
      CUserIDTable::thisPtr->SelectedUserIDData=1;
   }
   else if(CUserIDTable::thisPtr->TopMostData!=1)
   {
      CUserIDTable::thisPtr->TopMostData=1;
      CUserIDTable::thisPtr->SelectedUserIDData=1;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   UserIDScreenDownButton function is used to select the last entry in user 
*   list
*Entry condition:
*   int Address: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void UserIDScreenDownButton(int Address)
{
   if(((CUserIDTable::thisPtr->TotalCycle)> MaxUserIDPerScreen)&&
      ((CUserIDTable::thisPtr->TopMostData)+ MaxUserIDPerScreen <=(CUserIDTable::thisPtr->TotalCycle)))//(TopMostData+7 !=TotalCycle-1))
   {
      (CUserIDTable::thisPtr->TopMostData)+=MaxUserIDPerScreen;
      CUserIDTable::thisPtr->SelectedUserIDData=1;
   }
   else
      CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}


/***************************************************************************
*Purpose:
*   UserIDUpButton function is used to select the previous entry in user list
*Entry condition:
*   int Address: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void UserIDUpButton(int Address)
{
   if((CUserIDTable::thisPtr->SelectedUserIDData)==1)
   {
      if((CUserIDTable::thisPtr->TopMostData)>1)
         CUserIDTable::thisPtr->TopMostData--;
      else
         CChildView::ErrorBeep();
   }
   if((CUserIDTable::thisPtr->SelectedUserIDData)>1)
      CUserIDTable::thisPtr->SelectedUserIDData--;
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   UserIDDownButton function is used to select the next entry in user list
*   argument Address: an integer holding the value of enum ID of button
*Entry condition:
*   int Address: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void UserIDDownButton(int Address)
{
   if((CUserIDTable::thisPtr->SelectedUserIDData)==MaxUserIDPerScreen)
   {
      if(((CUserIDTable::thisPtr->TotalCycle)-(CUserIDTable::thisPtr->TopMostData))>=MaxUserIDPerScreen)
         CUserIDTable::thisPtr->TopMostData++;
      else
         CChildView::ErrorBeep();
   }
   else
      if((((CUserIDTable::thisPtr->SelectedUserIDData)+(CUserIDTable::thisPtr->TopMostData))<=(CUserIDTable::thisPtr->TotalCycle))
         &&((CUserIDTable::thisPtr->SelectedUserIDData)!=MaxUserIDPerScreen))
         CUserIDTable::thisPtr->SelectedUserIDData++;
      else
         CChildView::ErrorBeep();
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   DefaultUser this function will send command to WC to set default value 
*   in add user screen.
*Entry condition:
*   int ID: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void DefaultUser(int ID)
{
   SendGetSetCommand(GETDATA,ADDUSER_DATA,0);
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

/** @brief add unit in Add User and Modify user
*
*  This function will append unit days to Password expire time
*  and minutes to Idle Logout time in Add User and Modify user
*
*  @param int Address, a pointer to this VgaTitle object. 
*  @return void.
*/
void AddUnitToUser(int Address)
{
   CVgaMenu *menu1 = theApp.MenuPointer;
   CString daysSTR = CVgaMenuItem::LinearSearch(XSTR(DAYS_ID));
   CString minutesSTR = CVgaMenuItem::LinearSearch(XSTR(MINUTES_ID));
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();

   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::VARIABLE)
      {
         CVgaVariable *ptr = (CVgaVariable*)object;
         if( ptr->textID == XSTR(PASSEXPTIME_ID))
         {
            if(ptr->Variable_Text.Find(daysSTR) == -1)
               ptr->Variable_Text = ptr->Variable_Text +" "+ daysSTR;
         }
         if( ptr->textID == XSTR(IDLELOGOUTTIME_ID))
         {
            if(ptr->Variable_Text.Find(minutesSTR) == -1)
               ptr->Variable_Text = ptr->Variable_Text +" "+ minutesSTR;
         }
      }
   }
}

/***************************************************************************
*Purpose:
*   SendNewUser this function will send command to WC to save new user
*   details entered in add user screen.This will be executed when save 
*   button is clicked on add user screen.
*Entry condition:
*   int ID: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void SendNewUser(int ID)
{
   int Response=0xFF;
   char * check_password=CScreenKeypad::login_password;
   CVgaMenu *menu1=CChildView::thisPtr->menupointers.GetTail();
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();
   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::ALPHA)
      {
         CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
         if( ptr->textID == XSTR(PASSWORD_ID))
            sprintf(CScreenKeypad::login_password,"%s",ptr->GetAlphaString());
      }
   }
   Response=Check_Password(CScreenKeypad::login_password,NULL,NULL,false,false);
   if(Response!=0)
   {
      ProcessNak(ID);
      DisplayMessage(Response);
   }
   if(Response==0)
   {
      SendGetSetCommand(SETDATA,ADDUSER_DATA,ID);
      RecallUserIDProcess(0);	
   }
   memset(check_password,0,sizeof(CScreenKeypad::login_password));
   CChildView::thisPtr->Invalidate();
}


/***************************************************************************
*Purpose:
*   ModifyUser this function will send command to WC to get user ID
*   at the selected index in user list.
*Entry condition:
*   int ID: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void ModifyUser(int ID)
{
   SendGetSetCommand(GETDATA,
      htons(CUserIDTable::thisPtr->SelectedUserIDData + CUserIDTable::thisPtr->TopMostData - 1),0);
   CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   SendModifyUser this function will send command to WC to save user ID
*   details modified.This will be executed when save button is clicked
*   on modify user screen.Remove argument int from main.gui,to work 
*   function ProcessNak
*Entry condition:
*   int ID: an integer holding the value of enum ID of button
*Exit condition:
*   none
***************************************************************************/
void SendModifyUser(int ID)
{   
   int Response=0;
   char * check_password=CScreenKeypad::login_password;
   CVgaMenu *menu1=CChildView::thisPtr->menupointers.GetTail();
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();
   while(pos)
   {   
      object = menu1->items.GetNext(pos);  
      if(object->GetType()== CVgaMenu::ALPHA)
      {
         CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
         if( ptr->textID == XSTR(PASSWORD_ID)){
            sprintf(CScreenKeypad::login_password,"%s",ptr->GetAlphaString());
         }
      }
   }
   Response=Check_Password(CScreenKeypad::login_password,NULL,NULL,false,false);
   if(Response!=0)
   {
      ProcessNak(ID);
      DisplayMessage(Response);
   }
   if(Response==0)
   {
      SendGetSetCommand(SETDATA,htons(CUserIDTable::thisPtr->SelectedUserIDData + CUserIDTable::thisPtr->TopMostData - 1),ID);
      RecallUserIDProcess(0);	
   }
   memset(check_password,0,sizeof(CScreenKeypad::login_password));
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   SendGetSetCommand function sends command to wc for getting default name
*   for new user.Saving new user.Send index for modifying user in list.
*   And saving modified user data.
*Entry condition:
*   unsigned short getSetValue : 1 to get or 2 to set
*   unsigned short index : If 0xFFFF then add new user,
*   If some integer then modify user at that index.
*   int Address : address of VgaButton calling this function
*Exit condition:
*   none
***************************************************************************/
void SendGetSetCommand(unsigned short getSetValue,unsigned short index,int Address)
{
   union GetSetUser u;
   unsigned char * data;
   char ch;
   int Response=0xff;
   u.struct1.s1 = htons(getSetValue);
   u.struct1.s2 = index; //if index=0xFFFF then add new user, index=(some integer) then modify user
   CHostCommand * request = new CHostCommand(USERID_DATA, u.struct2.c,USERID_DATA_LEN);
   CHostCommand * response = app->SendUiHostCommand(request);

   if(response)
   {
      printf(" in response \n");
      ch=CHostCommand::AckNak();
      data = response->GetData();		
      Response=*data;
      if(Address!=0) //process the e
      {
         if(Response!=0)
         {
            ProcessNak(Address);
            DisplayMessage(Response);
         }
      }
      printf(" login ACK  message_no=%d\n",Response);
      if(ch == theApp.NAK)
         printf(" login NAK  \n");
      delete response;

   }
}


void RecallUserIDProcess(int id)
{
   CUserIDTable::CreateUserObjectList();
   CChildView::thisPtr->Invalidate();
}

void SendCommandForWeldHistory(int Address)
{

	CFile f;
	CFileException e;

	if(creating_pdf)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
		theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		CChildView::thisPtr->ErrorBeep();
		CChildView::thisPtr->Invalidate();
	}
	else
	{
		if(CChildView::thisPtr->ISUSBPresent == true)
		{
			if(CChildView::thisPtr->GetStateMachineStatus() == true)		 
			{
				if((f.Open( HistoryDataFileName, CFile::modeRead ,&e) ) && f.GetLength() > MIN_HISTORY_FILESIZEPDF)
				{

					CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_OFF);
					f.Close();
					SetupTemp_pos = NULL;
					SetupTemp_pos = tempSetupList.GetHeadPosition();
					CString StrM5_35;
					tempSetupList.GetNext(SetupTemp_pos);
					StrM5_35 = tempSetupList.GetNext(SetupTemp_pos);
					CChildView::thisPtr->ShowMessageScreen2(StrM5_35);
					creating_pdf=true;
					CChildView::thisPtr->BuildPrintList(WELD_HISTORY_ID); 				
				}
				else
				{

					ProcessNak(Address);
					DisplayMessage(1);	//Display No valid data
					CChildView::thisPtr->Invalidate();
				}
			}
			else
			{
				ProcessNak(Address);
				DisplayMessage(0);	//Display Weld Cycle Running	
				CChildView::thisPtr->Invalidate();
			}
		}
		else
		{
			ProcessNak(Address);
			DisplayMessage(3);	//connect usb
			CChildView::thisPtr->Invalidate();
		} 
	}

}

/***************************************************************************
*Purpose:
*   This function creates and save weld history PDF.This function is called
*   from PrintingThread 
*Entry condition:
*   none
*Exit condition:
*   bool
***************************************************************************/
bool SaveWeldHistoryPdf(void)
{
   bool PDFCreateStatus = true;
   printf("SaveWeldHistoryPdf");
   bool WrapAroundOnHistoryFile = false;

   PageCount = 1;

   HPDF_Font def_font;
   HPDF_Doc  pdf;
   HPDF_Page page;
 
   bool ExitFlag = true;
   const char *fontname;
   char STR[20];
   CString WeldHistoryStr =  CVgaMenuItem ::LinearSearch(XSTR(WELDHISTORY_STRINGID));	
   int Count = MAX_WELD_PDF_PAGES,StartingPoint = 0;
   int MaxWeldCount = CWeldingHistory::thisHisPtr->TotalDataInFile;
   pdf = HPDF_New (error_handler, NULL);
   page = HPDF_AddPage (pdf);
   HPDF_Page_SetSize (page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);
   eventname++;
   HPDF_UseUTFEncodings(pdf);
   fontname = HPDF_LoadTTFontFromFile(pdf, CChildView::thisPtr->PDFFontName, HPDF_TRUE);
   def_font = HPDF_GetFont(pdf, fontname, "UTF-8");

   PdfWithImage(&pdf,&page,&def_font);
   HPDF_Page_SetFontAndSize (page, def_font,25);
   CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
   CChildView::DrawPDFText(&page,10,TWOWELDLINEGAP,STR);

   HPDF_Page_SetFontAndSize(page,def_font,7);

   CString CurrentFilepath = "";
   int UnitFlag = true;
   int PdfPageCount=0;
   strcpy (Historyfname,"WeldHistory");
   CurrentFilepath = CChildView::thisPtr->GetCurrentFilePath(Historyfname);
   CChildView::thisPtr->CreateFolder(true);
   sprintf(Historyfname,"%s",CurrentFilepath);
   YCoordinate = FOURWELDLINEGAP;
   if(CWeldingHistory::thisHisPtr->TotalDataInFile >= (unsigned int)CChildView::Max_Allowed_Weld_Log) {
      MaxWeldCount = CChildView::Max_Allowed_Weld_Log;
      StartingPoint = CWeldingHistory::CurrentDisplayWeldCount;
   }

   do{
      Count = MAX_WELD_PDF_PAGES;
      if((StartingPoint+Count) > MaxWeldCount) 
      { //Less than 100 Data
         Count = MaxWeldCount - StartingPoint;
      }
      
	  PdfPageCount = CWeldingHistory::thisHisPtr->PrepareWeldHistoryList(HistoryDataFileName,StartingPoint,Count,pdf,page,def_font,(UnitFlag != 0));
	  PDFCreateStatus = (PdfPageCount != 0);
	  
	  if(PdfPageCount >= MAX_WELD_PDF_PAGES)
      {

         PDFCreateStatus = UnitFlag = CChildView::thisPtr->CreateNewPDFDoc(&page,&pdf,&def_font);
         Count = PdfPageCount-1;
         break;

      }
      else
         UnitFlag = false;
      StartingPoint = StartingPoint + Count;
      if(WrapAroundOnHistoryFile)
      {
         if(StartingPoint >= (CWeldingHistory::CurrentDisplayWeldCount-1))//CWeldingHistory::CurrentDisplayWeldCount
            ExitFlag = false;
      }
      else
      {
         if((StartingPoint >= (int)CChildView::Max_Allowed_Weld_Log) )
         {
            StartingPoint = 0;
            WrapAroundOnHistoryFile = true;
            MaxWeldCount = CWeldingHistory::CurrentDisplayWeldCount;//CWeldingHistory::CurrentDisplayWeldCount;
            ExitFlag = true;
         }
         else if(StartingPoint>=MaxWeldCount)
            ExitFlag = false;
         else
            ExitFlag = true; 
      }
      PDFCreateStatus = CChildView::thisPtr->USBPresent();

	}while(ExitFlag && PDFCreateStatus && !EstopPressedFlag);//StartingPoint < CWeldingHistory::thisHisPtr->TotalDataInFile

	if(PDFCreateStatus && !EstopPressedFlag)
		PDFCreateStatus = SavePDFToUSB(pdf,Historyfname);
	else
	{
		PDFCreateStatus = false;
		HPDF_Free(pdf);
	}
   return PDFCreateStatus;
}

/***************************************************************************
*Purpose:
*   This function checks the validity of password.The length,1 special character,
*   1 uppercase,1 lowercase one number.This function also compares two password 
*   entered in change password screen.Empty username is also checked.
*   Add/Modify user and Change password use this function to check username and
*   password.
*Entry condition:
*   char *Password1: 
*   char *Password2: 
*   char *userName:
*   bool StrCmp: if true it will compare Password1 and Password2 
*   bool username_check: if true then empty username is checked
*Exit condition:
*   return int : a error code to indicate the type of error
***************************************************************************/
int Check_Password(char *Password1,char *Password2,char *userName, bool StrCmp,bool username_check)
{

   unsigned char pwd_length=0;
   unsigned char count=0;
   bool Caps=false;
   bool Small=false;
   bool Special=false;
   bool Number=false;
   bool length=false;
  
   bool Comp_Pwd=true;
   pwd_length=strlen(Password1);
   if(username_check==true)
   {
      printf("user name checked=%s\n",userName);
      if(strlen(userName)==0)//no username entered
      {
         printf("rejected by username...\n");
         return INVALID_USERNAME;
      }
   }
   if(!(pwd_length>=8&&pwd_length<=10))
   {
      printf("not verified by length of password is %d and password is %s\n",pwd_length,Password1);
      return INVALID_PASSWORD;
   }
   else
      length=true;
   if(StrCmp==true)
   {
      if(strcmp(Password1,Password2)!=0)//new and confirm password are not same
      {
         printf("both password entered does not match\n");
         return PASSWORD_DOESNOTMATCH;
      }    	
   }

   for(count=0;count<pwd_length;count++)
   {
      if(Password1[count]>=65&&Password1[count]<=90)//checks for alleast one caps
         Caps=true;
      else if(Password1[count]>=97&&Password1[count]<=122)//checks for atleast one small letter
         Small=true;
      else if(Password1[count]>=48&&Password1[count]<=57)//checks for atleast one num
         Number=true;
      else if(Password1[count]!=' ')//checks for special character available except space
         Special=true;
   }

   if(Caps&&Small&&Number&&Special&&length&&Comp_Pwd)
   {
      printf(" Accepted caps=%d\n small=%d\n num=%d\n special=%d\n",Caps,Small,Number,Special);
      return ACCEPTED;
   }	
   else
   {
      printf(" Rejected caps=%d\n small=%d\n num=%d\n special=%d\n",Caps,Small,Number,Special);
      return INVALID_PASSWORD;
   }
}

void DisplayMessage(int ResponseType)
{
   CVgaMenu * menu;
   CVgaMenuItem *object;
   menu=theApp.MenuPointer; 
   POSITION pos1=menu->items.GetHeadPosition();
   while (pos1)
   {
      object= menu->items.GetNext(pos1);
      printf("type...=%d\n",object->GetType());
      if(object->GetType()==CVgaMenu::VGAMsgScrnObject)
      {
         CMsgScreen *ptr=(CMsgScreen *)object;
         if(ResponseType==ptr->ResponseType)
         {
            object->IsDraw=true;
         }
         else
         {
            object->IsDraw=false; 
         }
      }
	  if(object->GetType()==CVgaMenu::VGA_Button_OBJECT)
      { 
         //this button only appears if first time login or password validity expired
         CVgaButton *ptr=( CVgaButton *)object;
         if((ptr->textID)==XSTR(1124))
         {
            //in case of first time login or password validity expired or executive changed
            if((ResponseType==0) || (ResponseType==3) || (ResponseType==7))
            {
               object->IsDraw=true;
			   ptr->Disable = false;
			   ptr->RectShow = 1;
			   ptr->text = OkButtonText;
            }
            else
            {
               object->IsDraw=false; 
			   ptr->Disable = true;
			   ptr->text ="";
			   ptr->RectShow = 0;	  
			  
            }
         }
      }
   } 
}

/** @brief Process VgaButton NAK
*
*  This function handles the NAK consition when on VgaButton click.
*  Whenever the response of a command is NAK it has to be handled.
*  This function draws the NAK menu in menunak attribute of VgaButton.
*
*  @param int arg, a pointer to this VgaButton object.
*  @return void.
*/
void ProcessNak(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   CVgaMenu *menu;
   CString MenuNak;
   CString MenuName;
   menu = theApp.MenuPointer;
   MenuNak=ptr->MenuNak;
   if (theApp.menus.Lookup(MenuNak, menu))
   {
      page_no=1;
      theApp.menuName = MenuNak;
      theApp.MenuPointer=menu;
      CChildView::thisPtr->ModifyObjectList(menu);
   }
   CChildView::LoginScreenFlag = true;
}

void WeldResultColSetup(int Address)
{
   CChildView::RunResultScreen=false;
   CChildView::thisPtr->Invalidate();
}

/***************************************************************************
*Purpose:
*   This function make the webaddress from power supply ip address to update the s/w
and open the internet explorer whenever s/w uppgrade button is clicked.
*Entry condition:
*   int arg:
*Exit condition:
*  none
***************************************************************************/
void SwUpGrade(int arg)
{

   CString WebAddress;
#ifndef _WIN32_WCE	
  
   system( "taskkill /f /im iexplore.exe" );
   WebAddress="explorer http://"+CChildView::thisPtr->PowerSupplyIp+"/SunriseFirmwareUpload32923646.html";	  
   system(CT2A(WebAddress));
#else
   WebAddress="http://"+CChildView::thisPtr->PowerSupplyIp+"/SunriseFirmwareUpload32923646.html";
   SHELLEXECUTEINFO ShExecInfo = {0};
   ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
   ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
   ShExecInfo.hwnd = NULL;
   ShExecInfo.lpVerb = NULL;
   ShExecInfo.lpFile = _T("iesample.exe");		
   ShExecInfo.lpParameters = WebAddress;	
   ShExecInfo.lpDirectory = NULL;
   ShExecInfo.nShow = SW_HIDE;
   ShExecInfo.hInstApp = NULL;
   ShellExecuteEx(&ShExecInfo);	
#endif
}

/** @brief Send command to release horn
*
*  This function is called when Horn Release button is clicked
*  on Horn Clamp message screen. 
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void SendClampAlarm(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch == ACK)
      {
         if(theApp.menuName !=CVgaBottomMenu::WeldResults_ID)
         {
            CChildView::thisPtr->menusname.RemoveAll();
            CChildView::thisPtr->menupointers.RemoveAll();
            CChildView::thisPtr->menus.RemoveAll();
            while(theApp.GraphsDataList.GetCount()>0)
               theApp.GraphsDataList.RemoveHead();
            CVgaMenu * menu;
            if (theApp.menus.Lookup(CVgaBottomMenu::WeldResults_ID, menu))
            {
               OnKeypadScreen_flag=false;
               CChildView::thisPtr->IsAlarmScreen =false;
               CChildView::RunResultScreen=true;
               CBottomHalf::HornDownScreenPresent=false;
               CChildView::thisPtr->PMCScreen=false;
               CChildView::AccessLevelSystem=USER_OPERATOR;
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               CChildView::thisPtr->ModifyObjectList(menu);
               theApp.menuName=CVgaBottomMenu::WeldResults_ID;
               theApp.MenuPointer=menu;
            }
         }
      }
      CChildView::thisPtr->Invalidate();
      delete response;
   }
}
/** @brief Function to enable save button on Downspeed tuning menu.
*
*  This function is called when Downspeed tune menu is displayed.The function
*  enables save button when horn come down 3 times.This is done by checking
*  value of cycle.
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void DownSpeedTuneFunc(int Address)
{
   CVgaMenu * menu;
   CVgaMenuItem *object;
   menu=theApp.MenuPointer; 
   POSITION pos=menu->items.GetHeadPosition();
   bool enableSave = false;
   while (pos)
   {
      object= menu->items.GetNext(pos);

      if(object->GetType()==CVgaMenu::VARIABLE)
      {
         CVgaVariable *ptr = (CVgaVariable *)object;
         //find the blank button on downspeed tune menu and diplay the number of cycles 
         //as text of this button
			if(ptr->EnumID == DOWNSPEEDCYCLE_EID)  
			{				
				ptr->text = "";
				if(ptr->NewVal >= 1)
					enableSave = true;
			}
		}
		if(object->GetType()==CVgaMenu::VGA_Button_OBJECT)
		{
			CVgaButton *btn = (CVgaButton *)object;
			if(btn->EnumID == DOWNSPEEDUPDATE_EID || btn->EnumID == DOWNSPEEDUPDATE_EID_HD)
			{
				printf("btn enableSave=%d\n",enableSave);
				if(enableSave)
					btn->Disable = false;
				else
					btn->Disable = true;
			}
		}
	}
}

/** @brief Save velocity calibration
*
*  This function is called when save button is clicked on downspeed tune
*  screen.Function send enable id to wc.Ack indicates that the 
*  velocity calibration is done.And draw the previous menu.
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void SaveDownspeedtune(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch == ACK)
      {
         CChildView::thisPtr->menusname.RemoveAll();
         CChildView::thisPtr->menupointers.RemoveAll();
         CChildView::thisPtr->menus.RemoveAll();
         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();
         CVgaMenu * menu;
         if (theApp.menus.Lookup(DownspeedMenuName, menu))
         {
            OnKeypadScreen_flag=false;
            CChildView::thisPtr->IsAlarmScreen =false;
            CBottomHalf::HornDownScreenPresent=false;
            CChildView::thisPtr->PMCScreen=false;
            CChildView::AccessLevelSystem=USER_OPERATOR;
            CChildView::thisPtr->menusname.AddTail(theApp.menuName);
            CChildView::thisPtr->menus.AddTail(page_no);
            CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
            page_no=1;
            CChildView::thisPtr->ModifyObjectList(menu);
            theApp.menuName=DownspeedMenuName;
            theApp.MenuPointer=menu;
         }
			if(DownspeedMenuName == XSTR(DOWNSPEED_MENU_ID))
				SendHornDownCommand(HORN_DOWN_ENABLEID);
         DownspeedMenuName = CVgaBottomMenu::WeldSetup_ID;
      }
      CChildView::thisPtr->Invalidate();
      delete response;
   }
}

/** @brief Exit velocity calibration
*
*  This function is called when exit button is clicked on downspeed tune
*  screen.Function send enable id to wc.Ack indicates that the 
*  velocity calibration is aboarted.And draw the previous menu.
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void ExitDownspeedtune(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch == ACK)
      {
         CChildView::thisPtr->menusname.RemoveAll();
         CChildView::thisPtr->menupointers.RemoveAll();
         CChildView::thisPtr->menus.RemoveAll();
         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();
         CVgaMenu * menu;
         if (theApp.menus.Lookup(DownspeedMenuName, menu))
         {
            OnKeypadScreen_flag=false;
            CChildView::thisPtr->IsAlarmScreen =false;
            CBottomHalf::HornDownScreenPresent=false;
            CChildView::thisPtr->PMCScreen=false;
            CChildView::AccessLevelSystem=USER_OPERATOR;
            CChildView::thisPtr->menusname.AddTail(theApp.menuName);
            CChildView::thisPtr->menus.AddTail(page_no);
            CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
            page_no=1;
			theApp.GetSystemVariable();
            CChildView::thisPtr->ModifyObjectList(menu);
            theApp.menuName=DownspeedMenuName;
            theApp.MenuPointer=menu;
         }
			if(DownspeedMenuName == XSTR(DOWNSPEED_MENU_ID))
				SendHornDownCommand(HORN_DOWN_ENABLEID);
         DownspeedMenuName = CVgaBottomMenu::WeldSetup_ID;
      }
      CChildView::thisPtr->Invalidate();
      delete response;
   }
}

/** @brief Check condition for Downspeed Tuning button
*
*  This function is called when condition for Downspeed tuning
*  button in weld setup is evaluated.The button will be drawn if 
*	DownspeedEnable is true in System Config menu.
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return bool.
*/
bool CheckDownspeedFlag(CVgaButton *ptr)
{
   if(CChildView::thisPtr->DownspeedEnable)
   {
      ptr->IsDraw = true;
      ptr->RectShow = 1;
      return true;
   }
   else
   {
      ptr->RectShow = 0;
      ptr->IsDraw =false;
      return false;
   }
}

/** @brief Get Downspeed tuning flag vlaue
*
*  This function is called on application start to get the value of 
*  downspeedtune flag from WC.
*
*  @param void. 
*  @return void.
*/
void GetDownspeedtuneFlag(void)
{
   int length = VARMAXMINLENGTH + 1;
   int ID;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i= 532;//enable ID of DownspeedtuneFlag
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   //Send Command if enable flag is true
   CHostCommand * request = new CHostCommand(GetEptrVariable_FunId,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      length = response->GetDataLength();
      data = response->GetData();
      if(ch == ACK)
      {
         ID= CVgaMenuItem::Convert_Char_To_Integer(data,length,2);// CChildView::thisPtr->DownspeedEnable 
         int Datatype=*data++;length--;
         union 
         {
            bool i;
            char c;
         } u;
         u.c =*data++;length--;
         u.c =*data++;length--;
         CChildView::thisPtr->DownspeedEnable = u.i;  
      }
      delete response;
   }
}

/** @brief Set Downspeed tuning flag.
*
*  This function is called when "Downspeed Tuning" button is clicked.Function
*  send command to set DownspeedTuneFlag on WC.This function also checks the
*  running weld cycles. 
*
*  @param void.
*  @return void.
*/
void SetDownspeedFlag(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char * data = (unsigned char *) &data1[0];
   if(CChildView::thisPtr->GetStateMachineStatus() == true)		 
   {
      CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
      CHostCommand * response = app->SendUiHostCommand(request);
      if(response)
      {
         char ch=CHostCommand::AckNak();
         if(ch == ACK)
         {
            printf("Downspeedtune flag set");
         }
         delete response;
      }
	  DownspeedMenuName = CVgaBottomMenu::WeldSetup_ID;
      CChildView::thisPtr->Invalidate();
   }
   else
   {
      ProcessNak(Address);
      DisplayMessage(0);	//Display Weld Cycle Running	
      CChildView::thisPtr->Invalidate();
   }
}

/***************************************************************************
*Purpose:
*   This function is called when save button is clicked on confirmation 
*   sceern.Function send enable id to wc.Ack indicates that the 
*   event change string is saved.And previous menu is drawn.
*Entry condition:
*   int Address:pointer to this vgabutton object 
*Exit condition:
*   none
***************************************************************************/
void SendEventReasonString(int Address)
{
   CVgaButton *ptr=(CVgaButton *)Address;
   int length =VARMAXMINLENGTH;
   unsigned char data1[2];
   union 
   {
      short i;
      char c[2];
   } u;
   u.i=ptr->EnumID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   unsigned char *data=(unsigned char*)&data1[0];
   //Send Command if enable flag is true
   CHostCommand *request=new CHostCommand(SetValue_FunID,data,length);
   CHostCommand *response=app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch == ACK)
      {
		 printf("got ack");	
         CChildView::thisPtr->menusname.RemoveTail();
         CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->menus.RemoveTail();
         while(theApp.GraphsDataList.GetCount()>0)theApp.GraphsDataList.RemoveHead();
         CVgaMenu *menu=0;
		 if(CChildView::thisPtr->AuthorityCheckLogOut == true) {
			if(CChildView::thisPtr->AuthorityCheck == true) {
				EventChangeMenuName = XSTR(LOGINMENU);
			} else {
		        EventChangeMenuName = XSTR(MAINMENU);
			}
		    SavedPgNum = 1;
		 	CChildView::thisPtr->AuthorityCheckLogOut = false;
		 }
		 if (theApp.menus.Lookup(EventChangeMenuName,menu))
         {
            OnKeypadScreen_flag=false;
            CChildView::thisPtr->IsAlarmScreen=false;
            CBottomHalf::HornDownScreenPresent=false;
            CChildView::thisPtr->PMCScreen=false;
            CChildView::AccessLevelSystem=USER_OPERATOR;			
            page_no=SavedPgNum;
            CChildView::thisPtr->ModifyObjectList(menu);
            theApp.menuName=EventChangeMenuName;
            theApp.MenuPointer=menu;
         }
      }
      CChildView::thisPtr->Invalidate();
   }
}

/***************************************************************************
*Purpose:
*   This function is called when description button is clicked on eventlist
*   sceern.
*Entry condition:
*   int Address:pointer to this vgabutton object 
*Exit condition:
*   none
***************************************************************************/
void DisplayEventDesciption(int Address)
{
	ReasonDisplayFlag = false;
	NameDisplayFlag = false;
	ParamDescription *Pdescr = NULL;
	EventDescription *Descr = NULL;
	UINT16 ParamID;
	UINT8 * IntID;
	UINT16 TempEvent;	
	CString CTempOld,CTempNew;
	CString EventID ="";
	CString EventID1 = "";
	CString Reason = "" ;
	CString DataOld = "" ;
	CString DataNew = "" ;
	CString ParameterID ="";
	CString ParamName = "";
	CString Description1 = "";
	CString Description2 = "";
	CString ParameterName = "";
	DisplayPosition NameDisplayPosition = DO_NOT_DISPLAY;
	if(CEventLog::thisHisPtr->EventLogList.GetCount() <= 0)
	{
		theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
		page_no=CChildView::thisPtr->menus.RemoveTail();
		theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
		CChildView::thisPtr->ErrorBeep();

	}
	else
	{
		CEventHistoryData *object2 = NULL;	
		object2 = CEventLog::thisHisPtr->EventLogList.GetAt(CEventLog::thisHisPtr->EventLogList.FindIndex(CEventLog::TopMostData + CEventLog::thisHisPtr->SelectedEventData-2));   
		Reason = object2->EventHistoryObj.EventReason;//Coverity Fix
		EventID = object2->EventHistoryObj.EventId;
		IntID =  object2->EventHistoryObj.EventId;
		DataOld = object2->EventHistoryObj.DataOld;
		DataNew = object2->EventHistoryObj.DataNew;
		ParamID = object2->EventHistoryObj.ParameterId;
		ParameterID.Format(_T("%d"),ParamID);	
		theApp.eds.Lookup(EventID, Descr);
		theApp.pds.Lookup(ParameterID,Pdescr);
		if(Descr == NULL)//
		{
			EventID.Format(_T("EV%d"),900);//invalid event id
			theApp.eds.Lookup(EventID, Descr);
		}
		NameDisplayPosition = (DisplayPosition)_tstoi(Descr->DisplayPosition);
		CString Description ( Descr->GetEventDescription());	
		TempEvent = atoi((char*)(IntID+2));	
		if(TempEvent == EVENT_CALIBRATION)//calibration related events
			Description = PrepareDescription(ParamID,TempEvent,DataOld,false);
		else if(TempEvent == EVENT_USER_MODIFIED )
		{

			if(Pdescr!=NULL)
			{
				if(ParamID == PASSWORD_CHANGE )
					Description = Description + " " + Pdescr->ParamDesc;
				else if(ParamID == AUTHORITY_CHANGE)
					Description =  Pdescr->ParamDesc + " "+ Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
				else
					Description = Description + " " + Pdescr->ParamDesc + " "+ Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
			}
		}
		else if(NameDisplayPosition == DO_NOT_DISPLAY)
			Description = Description + " " + Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
		else if(NameDisplayPosition == BEFORE_EVENT_DESCRIPTION)
			Description = GetNameFromID(ParamID) + " " +  Description + " " + Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
		else if(NameDisplayPosition == AFTER_EVENT_DESCRIPTION)
			Description =  Description + " " +  GetNameFromID(ParamID) + " " + Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
		else
		{
			Description = Description + " " + Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false) + " " +  Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
			ParameterName = GetNameFromID(ParamID);
		}
		/* if string is overlapping the boundries then split it into three parts*/
		if(Description.GetLength()>MAX_DESCRIPTION_PERLINE)

		{

			Description1 = Descr->Str1 + " " + PrepareDescription(ParamID,TempEvent,DataOld,false);
			Description2 = Descr->Str2 + " " +  PrepareDescription(ParamID,TempEvent,DataNew,false);
			if(TempEvent == EVENT_USER_MODIFIED)
			{
				if(Pdescr!=NULL)
				{
					if(ParamID == AUTHORITY_CHANGE)
						Description =  Pdescr->ParamDesc;
					else
						Description = Descr->GetEventDescription() + " " + Pdescr->ParamDesc;
				}
			}
			else if((NameDisplayPosition == DO_NOT_DISPLAY)||(NameDisplayPosition == SEPARATE))
				Description = Descr->GetEventDescription();
			else if (NameDisplayPosition == BEFORE_EVENT_DESCRIPTION)
				Description = GetNameFromID(ParamID) + " " + Descr->GetEventDescription();
			else if(NameDisplayPosition == AFTER_EVENT_DESCRIPTION)
				Description = Descr->GetEventDescription() + " " + GetNameFromID(ParamID) ;
			
		}

		CVgaMenu *menu1=theApp.MenuPointer;
		CVgaMenuItem * object = 0;
		POSITION pos = menu1->items.GetHeadPosition();
		while(pos)
		{   
			object = menu1->items.GetNext(pos);  
			if(object->GetType()== CVgaMenu::VGA_Button_OBJECT)
			{
				CVgaAlphanumeric *ptr = (CVgaAlphanumeric*)object;
				if( ptr->textID == XSTR(DESCRIPTION_TEXT_ID))
					ptr->text =  Description;
				else if( ptr->textID == XSTR(DESCRIPTION1_TEXT_ID))
					ptr->text =  Description1;
				else if( ptr->textID == XSTR(DESCRIPTION2_TEXT_ID))
					ptr->text =  Description2;
				else if( ptr->textID == XSTR(REASON_TEXT_ID))
					ptr->text =  Reason;
				else if(ptr->textID == XSTR(PARAMETER_FIELD_ID))
					ptr->text = ParameterName;
				else if(ptr->textID == XSTR(REASON_BUTTON_TEXT_ID))
				{
					if(Reason.GetLength()>0)
					  {
						ReasonDisplayFlag = true;
						object->IsDraw=true;
					  }
					else
						object->IsDraw=false; 
				}
				else if(ptr->textID == XSTR(PARAMETER_BUTTON_TEXT_ID))
				{
					if(ParameterName.GetLength()>0)
					{
						NameDisplayFlag = true;
						object->IsDraw=true;
					}
					else
						object->IsDraw=false;
				}
			}
		}
	}
	CChildView::thisPtr->Invalidate();
}


bool callInvalidate(CVgaTitle *ptr)
{
   GetOLString(ptr->EnumID);
   CChildView::thisPtr->Invalidate();
   return true;
}


void GetOLString(int ID)
{
   int StringID = ID;
   CString titleString = CVgaMenuItem::LinearSearch(XSTR(OVERLOADSTR_ID));
   CVgaMenu *menu1 = theApp.MenuPointer;
   CVgaMenuItem * object = 0;
   POSITION pos = menu1->items.GetHeadPosition();
   int length =3;
   unsigned char data1[3];
   union
   {
      short i;
      char c[2];
   } u;
   u.i=StringID;
   data1[1]=u.c[0];
   data1[0]=u.c[1];
   data1[2]=(char)0;
   unsigned char * data = (unsigned char *) &data1[0];
   CHostCommand * request = new CHostCommand(GetEptrVariable_FunId,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==theApp.ACK)
      {
         int ResID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);//Coverity 12119
         if(ResID==!StringID)//If ID doesn't match, delete response
         {
            delete response;
            return ;
         }
     	 data++;
		 length--;
         bool Eptr;
         union 
         {
            bool i;
            char c;
         } u;
         u.c = *data++;length--;
         Eptr=u.i;
         if(Eptr==false)
         {
            delete response; 
         }
         else
         {
            int OLtype = u.c;
            if(OLtype  & BIT1) //OL_CURRENT
               titleString = CVgaMenuItem::LinearSearch(XSTR(CURRENTSTR_ID)) +" "+titleString;
            else if(OLtype & BIT2) //OL_Frequency
               titleString = CVgaMenuItem::LinearSearch(XSTR(FREQUENCYSTR_ID))+" "+titleString;
            else if(OLtype & BIT0) //OL_VOLTAGE
               titleString = CVgaMenuItem::LinearSearch(XSTR(VOLTAGESTR_ID))+" "+titleString;
            else if(OLtype & BIT3) //Phase OL
               titleString = CVgaMenuItem::LinearSearch(XSTR(PHASESTR_ID))+" "+titleString;
            titleString.MakeUpper();
            while(pos)
            {   
               object = menu1->items.GetNext(pos);  
               if(object->GetType()== CVgaMenu::TITLE)
               {
                  CVgaTitle *ptr = (CVgaTitle*)object;
                  ptr->text = titleString;
               }
            }
         }
      }
   }
}

/***************************************************************************
*Purpose:
*   This function is called from DisplayEventDesciption function 
*   
*   
*   
*Entry condition:
*   int ParamID:the parameter id of the changed parameter
int EventID:the event id of the event
CString Data:based on this data the Cstring is prepared
*Exit condition:
*   CString PreparedString:return the CString prepared
***************************************************************************/
CString PrepareDescription(int ParamID,int EventID,CString Data,bool JsonReq)
{
   ParamDescription *Pdescr = NULL;
   UINT16 Temp,TempData;
   CString PreparedString;
   CString ParameterID = "", AppendText ="";
   bool TempFlag = false;	
   CString Pdescription ="";
  
  

   ParameterID.Format(_T("%d"),ParamID);
   theApp.pds.Lookup(ParameterID,Pdescr);
   if(Pdescr == NULL)
      return Data ;
   Pdescription = Pdescr->GetParamDescription(JsonReq);

   if((EventID == EVENT_PARAMETER_CHANGED)||	(EventID == EVENT_HARDWARE_ASSEMBLY_NUMBER_CHANGED)||
      (EventID == EVENT_HARDWARE_VERIFY_CHANGED)||(EventID == EVENT_FACTORY_AUTOMATION_MODE)||
      (EventID == EVENT_CALIBRATION)||(EventID == EVENT_PARAMETER_CHANGED_ONVALIDATEDPS)||
      (EventID == EVENT_USER_MODIFIED)||(EventID == EVENT_AUTHORITY_CHECK_CHANGED))
   {
      switch(ParamID)
      {
         /**********************************************************************
         ********* Data Preparation for Modified User *************************
         **********************************************************************/
      case USER_LEVEL_CHANGE://user level change
         TempData = _tstoi(Data);
         if(TempData<DESCRIPTION_ARRAY_SIZE)
         {
            if(JsonReq)
               PreparedString = UserLevelArr[TempData];
            else
               PreparedString =  Pdescr->Str[ TempData];
         }
         break;
      case AUTHORITY_CHANGE://operator authority change
         TempData = _tstoi(Data);
         if(TempData)
            for(Temp =0;Temp<5;Temp++)
            {
               if((TempData>>Temp)&0x1)
               {
                  if(TempFlag == true)
                     PreparedString =  PreparedString + ",";
                  if(JsonReq)
                     PreparedString = PreparedString +  AuthorityChangeArr[Temp+1];
                  else
                     PreparedString = PreparedString +  Pdescr->Str[Temp+1];						
                  TempFlag = true;	
               }
            }
         else{
            if(JsonReq)
               PreparedString = AuthorityChangeArr[0];
            else
               PreparedString = Pdescr->Str[0];
         }
         break;
      case PASSWORD_CHANGE:
         PreparedString = Data;
         break;
      case ACTIVE_STATUS_CHANGE:
         {				
            if(_T("Enabled") == Data){
               if(JsonReq)
                  PreparedString = "Enable" ;
               else
                  PreparedString =  Pdescr->Str[0];
            }
            else{
               if(JsonReq)
                  PreparedString = "Disable" ;
               else
                  PreparedString =  Pdescr->Str[1];
            }
            break;
         }

         /**********************************************************************
          ********* Data Preparation for H/W Part numbers change ***************
          **********************************************************************/
      case STACKASSEMBLYNUM:
      case ACTASSEMBLYNUM:
      case PSASSEMBLYNUM:
         {
            PreparedString =  Data;
         }
         break;
         /**********************************************************************
         ********* Data Preparation For H/W Verify Choice Menu ****************
         **********************************************************************/
	  case HWVERIFY:
		  {				
			  TempData = _tstoi(Data);
			  if(JsonReq)
				  AppendText = HWVerifyArr[5];
			  else
				  AppendText = Pdescr->Str[5];   //HWVerifyArr
			  if(TempData)
			  {
				  for(Temp =0;Temp<4;Temp++)
				  {
					  if((TempData>>Temp)&0x1)
					  {
						  if(TempFlag == true)
							  PreparedString =  PreparedString + ",";
						  if(JsonReq)
							  PreparedString = PreparedString +  HWVerifyArr[Temp+1];
						  else
							  PreparedString = PreparedString +  Pdescr->Str[Temp+1];
						  TempFlag = true;
					  }
				  }
			  }
			  if(TempFlag)
				  PreparedString = AppendText + " " + PreparedString;
			  else{
				  if(JsonReq)
					  PreparedString = HWVerifyArr[0];
				  else
					  PreparedString = Pdescr->Str[0];
			  }
			  break;
		  }
         /**********************************************************************
         ********* Data Preparation For Calibration****************************
         **********************************************************************/
      case ACT_CALIBRATION:
      case FORCE_CALIBRATION_PARAMID:
      case PRESSURE_CALIBRATION_PARAMID:
         {    
            EventDescription *Descr = NULL;
            ParameterID.Format(_T("EV%d"),EventID);
            theApp.eds.Lookup(ParameterID, Descr);				
            if(Descr!=NULL)								
            {	  
               PreparedString =  Pdescription + " " + Descr->GetEventDescription(JsonReq) + " ";
               TempData = _ttoi(Data);
               if((TempData > 0) && TempData <= DESCRIPTION_ARRAY_SIZE)
               {
                  if(JsonReq)
                     PreparedString += ActuatorArr[TempData - 1];
                  else
                     PreparedString += Pdescr->Str[TempData - 1];
               }
            }
            else
               PreparedString = Data;
         }
         break;

         /**********************************************************************
         ********* Data Preparation for weld setup parameters******************
         **********************************************************************/

         /************ Radio Menu Type Weld Setup Parameters *****************
         ********************************************************************/
      case PRETRIGFLAG:
      case WELDMODE:
      case AMPSTEPFLAG:
	  case PRESSURE2_FLAG:
         {				
            TempData = _tstoi(Data);
            if(TempData < DESCRIPTION_ARRAY_SIZE)
            {
               if(JsonReq)
               {
                  if(ParamID == PRETRIGFLAG)
                     PreparedString =  PretriggerArr[ TempData];
                  else if(ParamID == WELDMODE)
                     PreparedString =  WeldmodeChangedArr[ TempData];
                  else
                     PreparedString =  AmplitudeArr[ TempData];
               }
               else
                  PreparedString =  Pdescr->Str[ TempData];
            }

            break;
         }
         /* Reject limits Parameters*/
      case  TIMEPLR:
      case TIMEMLR:
      case POWERPLR:
      case POWERMLR:
      case ENERGYPLR:
      case ENERGYMLR:
      case  COLPLR:
      case  COLMLR:
      case ABSPLR:
      case ABSMLR:
      case TRSDISTPLR:
      case TRSDISTMLR:
      case WELDFORCEPLR:
      case WELDFORCEMLR:
      case PS_SBLMAXFREQ:
      case PS_SBLMINFREQ:
      case DOWNSPEEDPLR:
      case DOWNSPEEDMLR:
         /* Suspect limits Parameters*/
      case TIMEMLS:
      case TIMEPLS:
      case ENERGYPLS:
      case ENERGYMLS:
      case POWERPLS:
      case POWERMLS:
      case COLPLS:
      case COLMLS:
      case  ABSPLS:
      case ABSMLS:
      case TRSDISTPLS:
      case TRSDISTMLS:
      case WELDFORCEPLS:
      case WELDFORCEMLS:
      case PMCHIGHLIMIT:
      case PMCLOWLIMIT:
      case MISSINGPARTMAX:
      case MISSINGPARTMIN:
      case PEAKPOWERCUTOFF:
      case ABSCUTOFFDIST:
      case COLLCUTOFFDIST:
      case AMPSCRUBTIME:
      case AMPTRIGTIMEVALUE:
      case AMPTRIGENERVALUE:
      case AMPTRIGPOWERVALUE:
      case AMPTRIGCOLVALUE:
      case HOLDTIME:
      case MAXTIMEOUT:
      case  SCRUBTIME:
      case MPRESSURELIMIT:
      case PS_PPRESSURELIMIT:
		  /* Tweak Limits*/
	  case WELDPRESSURE_PLT:
	  case WELDPRESSURE_MLT:
	  case DOWNSPEED_PLT:
	  case DOWNSPEED_MLT:
	  case HOLDPRESSURE_PLT:
	  case HOLDPRESSURE_MLT:
	  case HOLDTIME_PLT:
	  case HOLDTIME_MLT:
	  case AMPA_PLT:
	  case AMPA_MLT:
	  case TRIGFORCE_PLT:
	  case TRIGFORCE_MLT:
	  case WELDTIME_PLT:
	  case WELDTIME_MLT:
	  case WELDENERGY_PLT:
	  case WELDENERGY_MLT:
	  case PEAKPOWER_PLT:
	  case PEAKPOWER_MLT:
	  case COLLAPSEDIST_PLT:
	  case COLLAPSEDIST_MLT:
	  case ABSDIST_PLT:
	  case ABSDIST_MLT:
	  case SCRUBTIME_PLT:
	  case SCRUBTIME_MLT:
	  case SCRUBAMP_PLT:
	  case SCRUBAMP_MLT:
	  case TRIGDIST_PLT:
	  case TRIGDIST_MLT:
		  /* Added for Pressure stepping events*/
	  case PRESSURE_TRIGTIMEVALUE:
	  case PRESSURE_TRIGENERVALUE:
	  case PRESSURE_TRIGPOWERVALUE:
	  case PRESSURE_TRIGCOLVALUE:
         {				

            if(_T("OFF")==Data)
            {
               if(JsonReq)
                  PreparedString =  "Off";
               else
                  PreparedString =  Pdescr->Str[0];
            }
            else
               PreparedString =  Data;
            break;
         }
      case DUPS_SEEK_FLAG:
      case SWDIPSETTING:
      case DUPSMEMFLAG:
      case WELDSTATUSFLAG:
      case RTFLAG:
      case WELDTRIGGER:
      case REJRESET_REQFLAG:
      case SUSRESET_REQ:
      case SUSPECTLIMITSFLAGS:
      case REJECTLIMITSFLAG:
      case FREQOFFSETFLAG:
      case  ENERGYBRAKING:
      case EXTTRGDELAY:
      case SEEKFUNFLAG:
      case PMCENABLED:
      case CYCLEABORTFLAG:
      case GROUNDDETECTFLAG:
      case MISSINGPARTFLAG:
      case ACTCLEARFLAG:
      case ENERGYCOMPFLAG:
      case CONTROLLIMITSFLAG:
      case ABFLAG:
      case BATCHCOUNTRESET:
      case BATCHCOUNTWITHALARM:
      case BATCHFUNCTION:
      case AMPTRIGEXTFLAG:
	  case AUTOSCALEFLAG:
	  case PRESSURE_TRIGEXTFLAG:
         /* System Configuration Parameters*/
      case GENERALALARMFLAG:
      case AUTOMATION:
      case PPRESSURELIMITFLAG:
	  case HOLD_PRESSURE_FLAG:
	  case DIGITALFILTERFLAG:
	  case AUTHORITYCHECK:
         {				
            if(_T("OFF")==Data)
            {
               if(JsonReq)
			   {
				   if(ParamID ==WELDTRIGGER)
					   PreparedString =  _T("Force");
				   else if(ParamID ==HOLD_PRESSURE_FLAG)
					   PreparedString =  _T("Default");
				   else
					   PreparedString =  _T("Off");
			   }
               else
                  PreparedString =  Pdescr->Str[0];
            }
            else
            {
               if(JsonReq)
			   {
				  if(ParamID ==WELDTRIGGER)
					PreparedString =  _T("Distance");
				  else
					PreparedString =  _T("On");
			   }
               else
                  PreparedString =  Pdescr->Str[1];
            }
            break;
         }
      default:
         PreparedString = Data;
         break;
      }
   }
   else
      PreparedString = Data;
   return PreparedString;
}

/***************************************************************************
*Purpose:
*   This function is used to extract parameter name from parameter ID
*   
*   
*   
*Entry condition:
*   int ParamID:the parameter id of the changed parameter
    bool InEnglish

*Exit condition:
*   CString ParameterName:return the name of the parameter
***************************************************************************/

CString GetNameFromID(int ParamID,bool InEnglish)
{
   ParamDescription *Pdescr = NULL;   
   CString ParameterID = "";  
   CString ParameterName= "";
   ParameterID.Format(_T("%d"),ParamID);
   theApp.pds.Lookup(ParameterID,Pdescr);
   if(Pdescr == NULL)
     ParameterName =  ParameterID ;
   else
   {
	   if(InEnglish)
		   ParameterName = Pdescr->ParamDescEng;
	   else
		   ParameterName = Pdescr->ParamDesc;
   }
   return ParameterName;
	  
}

/***************************************************************************
*Purpose:
*   This function is called on exit button click of userio menu and enable
*   the state machine
*   
*   
*Entry condition:
*   Entry condition:
*   int Address:pointer to this vgabutton object 
*Exit condition:
*   none
***************************************************************************/

void ExitMenuAndEnableWeld(int Address)
{
   int length = EXIT_USERIO_COMMAND_SIZE;
   unsigned char * data;
   char ch = 0;
   data = (unsigned char*)&ch;	
   CHostCommand * request = new CHostCommand( EXIT_USERIO_COMMAND, data, length  );
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
      delete response;
   CChildView::thisPtr->Invalidate();
}

/** @brief Send the Validated Confirmation.
*
*  This function is called when "OK" is clicked on message screen 
*  from preset validation menu.Function first takes out the previous
*  menu pointer that is preset validation menu.Then looks for the preset 
*  validation button and get its current value.This value is sent to WC
*  using 1051 command and the new value and text is assigned to the button.
*  This is done to execute function first and then send the command.
*
*  @param Address pointer to the vgabutton button object.
*  @return void.
*/
void SetValidated(int Address)
{
	CVgaButton *btnptr=(CVgaButton *)Address;
	CVgaMenu *menu1 = 0;
	POSITION pos = 0; 
	CVgaMenuItem * object = 0;

	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	CChildView::thisPtr->Invalidate();

	int length =INTEGERLENGTH-1;
	unsigned char data[INTEGERLENGTH];
	union 
	{
		short i;
		char c[2];
	} u;
	unsigned char * data1 = (unsigned char *) &data[0];

	CToggle *toggleptr = 0;
	menu1 = theApp.MenuPointer;
	pos = menu1->items.GetHeadPosition();
	while(pos)
	{   
		object = menu1->items.GetNext(pos);  
		if(object->GetType()== CVgaMenu::TOGGLE)
		{
			if(object->textID == XSTR(VALIDATE_ID))
			{
				toggleptr = (CToggle*)object;
				u.i = toggleptr->EnumID;
				data[1]=u.c[0];
				data[0]=u.c[1];
				data[2]=(char)(!toggleptr->Toggle_Value);
			}
		}
	}
		
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	//coverity fix 12548
	if(response && toggleptr)
	{
		char ch=CHostCommand::AckNak();
		data1 = response->GetData();
		length = response->GetDataLength();
		if(ch == ACK)
		{
			int OneByteValue = CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
			toggleptr->Toggle_Value = (OneByteValue != 0);
			if(toggleptr->Toggle_Value)
				toggleptr->Toggle_Text= " = " + toggleptr->Toggle_Text1;
			else
				toggleptr->Toggle_Text= " = " + toggleptr->Toggle_Text2;
			int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
			if(refresh)
			{
				theApp.GetSystemVariable();
				CChildView::thisPtr->MaxPreset=1;	
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
			}
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
			printf("preset validated flag set");
		}
		delete response;
	}
	CChildView::thisPtr->Invalidate();
}

/** @brief CancelValidated
*
*  This function is called when "Cancel" is clicked on message screen 
*  from preset validation menu.This function removes the menus from
*  list to display the preset validation menu.
*
*  @param Address pointer to the vgabutton button object.
*  @return void.
*/
void CancelValidated(int Address)
{
	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	CChildView::thisPtr->Invalidate();
}


/** @brief Send the Locked Confirmation.
*
*  This function is called when "OK" is clicked on message screen 
*  from preset validation menu.Function first takes out the previous
*  menu pointer that is preset validation menu.Then looks for the preset 
*  locked button and get its current value.This value is sent to WC
*  using 1051 command and the new value and text is assigned to the button.
*  This is done to execute function first and then send the command.
*
*  @param Address pointer to the vgabutton button object.
*  @return void.
*/
void SetLocked(int Address)
{
	CVgaButton *btnptr=(CVgaButton *)Address;
	CVgaMenu *menu1 = 0;
	POSITION pos = 0; 
	CVgaMenuItem * object = 0;

	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	CChildView::thisPtr->Invalidate();

	int length =INTEGERLENGTH-1;
	unsigned char data[INTEGERLENGTH];
	union 
	{
		short i;
		char c[2];
	} u;
	unsigned char * data1 = (unsigned char *) &data[0];

	CToggle *toggleptr = 0;
	menu1 = theApp.MenuPointer;
	pos = menu1->items.GetHeadPosition();
	while(pos)
	{   
		object = menu1->items.GetNext(pos);  
		if(object->GetType()== CVgaMenu::TOGGLE)
		{
			if(object->textID == XSTR(LOCK_ID))
			{
				toggleptr = (CToggle*)object;
				u.i = toggleptr->EnumID;
				data[1]=u.c[0];
				data[0]=u.c[1];
				data[2]=(char)(!toggleptr->Toggle_Value);
			}
		}
	}
		
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	//coverity fix 12546
	if(response && toggleptr)
	{
		char ch=CHostCommand::AckNak();
		data1 = response->GetData();
		length = response->GetDataLength();
		if(ch == ACK)
		{
			int OneByteValue = CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
			toggleptr->Toggle_Value = (OneByteValue != 0);
			if(toggleptr->Toggle_Value)
				toggleptr->Toggle_Text= " = " + toggleptr->Toggle_Text1;
			else
				toggleptr->Toggle_Text= " = " + toggleptr->Toggle_Text2;
			int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
			if(refresh)
			{
				theApp.GetSystemVariable();
				CChildView::thisPtr->MaxPreset=1;	
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
			}
			int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
			printf("preset locked flag set");
		}
		delete response;
	}
	CChildView::thisPtr->Invalidate();
}

/** @brief CancelLocked
*
*  This function is called when "Cancel" is clicked on message screen 
*  from preset validation menu.This function removes the menus from
*  list to display the preset validation menu.
*
*  @param Address pointer to the vgabutton button object.
*  @return void.
*/
void CancelLocked(int Address)
{
	theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
	page_no=CChildView::thisPtr->menus.RemoveTail();
	theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
	CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
	CChildView::thisPtr->Invalidate();
}


/** @brief Send command to estop reset login
*
*  This function is called when reset is clicked
*  on Estop Login message screen. 
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void SendEstopLogin(int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
	int length =VARMAXMINLENGTH;
	unsigned char data1[2];
	union 
	{
		short i;
		char c[2];
	} u;
	u.i=ptr->EnumID;
	data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
	//Send Command if enable flag is true
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		if(ch == ACK)
		{
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
			page_no=CChildView::thisPtr->menus.RemoveTail();
			theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
			CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
			
		}
		CChildView::thisPtr->Invalidate();
		delete response;
	}
}

/** @brief CheckVerifiedPreset
*
*  This function is called when Validation butoon is clicked
*  on Save/Recall screen.When preset is verified then enter in
*  validation screen ohterwise show message screen.
*
*  @param int Address, a pointer to this VgaButton object. 
*  @return void.
*/
void CheckVerifiedPreset(int Address)
{
	if(!PresetVerify)
		ProcessNak(Address);
	CChildView::thisPtr->Invalidate();
}

/** @brief StartSensorCal
*
*  This function is called when Ok button is clicked on Cal Full System Confirmation message,
*  It sends the enable id 584, which let the wc know that user is on
*  calibration full systemm screen, so wc makes StartingSensorCal flag true which
*  does not allow system pressure incorrect alarm on calibration screen.
*
*  @return void.
*/
void StartSensorCal(int Address)
{
	CVgaButton *ptr=(CVgaButton *)Address;
	int length =VARMAXMINLENGTH;
	unsigned char data1[2];
	union 
	{
		short i;
		char c[2];
	} u;
	u.i=ptr->EnumID;
	data1[1]=u.c[0];
	data1[0]=u.c[1];
	unsigned char * data = (unsigned char *) &data1[0];
	//Send Command if enable flag is true
	CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)	
	{
		char ch=CHostCommand::AckNak();
		if(ch != ACK)
		
		{
			 ProcessNak(Address);
             DisplayMessage(0);			
		}
		delete response;	
		CChildView::thisPtr->Invalidate();
	}
}