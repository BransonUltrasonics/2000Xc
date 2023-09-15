/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ChildView.cpp_v   1.62   21 Dec 2015 15:07:24   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ChildView.cpp_v  $
 * 
 *    Rev 1.62   21 Dec 2015 15:07:24   RJamloki
 * Remove CChildView::OpAuthority from AuthCheckClampFunc 
 *
 *    Rev 1.61   17 Nov 2015 17:12:14   RJamloki
 * Re declare the static variable, needed by the compiler
 *
 *    Rev 1.60   29 Apr 2015 16:06:42   rjamloki
 * Initializing DownspeedMenuName to WeldSetup Menu ID at startup
 *
 *    Rev 1.59   21 Apr 2015 16:52:08   rjamloki
 * Fixed SystemConfig.cfg file parsing. Taking the Max file path defines into account while parsing
 *
 *    Rev 1.58   16 Apr 2015 17:42:18   rjamloki
 * Fixed back color for UDI and Batch count draw area on run result screen.
 *
 *    Rev 1.57   16 Apr 2015 14:16:22   rjamloki
 * Coverity fixes done before release
 *
 *    Rev 1.56   16 Apr 2015 05:53:54   sesharma
 * Included "InputDevices.h" file and added new timer MOUSE_DETECT_TIMER to auto hide the cursor if mouse is not plugged in and 1ms Sleep added to avoid heavy i/o operation at file write and Coverity fixes.
 *
 *    Rev 1.55   09 Apr 2015 04:16:06   RJamloki
 * Added Pressure A nad B strings initialization for PDF in DrawFirstScreen
 *
 *    Rev 1.54   03 Apr 2015 06:34:52   amaurya
 * change in OnKeyDown() function, check for runresults screen removed to allow barcode entery on all screens.
 *
 *    Rev 1.53   01 Apr 2015 12:53:54   amaurya
 * checking status machine status before idle log out in OnTimer function and change in analyzepolling response function to not display batch count if it is disabled.
 *
 *    Rev 1.52   28 Mar 2015 06:56:06   amaurya
 * Change in OnTimer function in idle logout case, checking the automation and authority check condition before idle logout.
 *
 *    Rev 1.51   28 Mar 2015 04:01:34   RJamloki
 * WeldDataCmdFlag removed after PollingCommand Retries have been increased.
 *
 *    Rev 1.50   27 Mar 2015 11:04:54   amaurya
 * Max weld data request in single command increased to 50.
 *
 *    Rev 1.49   14 Mar 2015 11:49:38   amaurya
 * change in function CChildView::OnLButtonDown() to avoid mouse click on object with rectshow=0
 *
 *    Rev 1.48   11 Mar 2015 09:25:42   amaurya
 * PrintStreamingSetup() added to print setup limit to WeldSetup PDF.PrintVQSLimits() removed.
 *
 *    Rev 1.47   11 Feb 2015 06:17:32   amaurya
 * changes to fix the button rename issue on udi enter after e stop
 *
 *    Rev 1.46   03 Feb 2015 07:24:08   amaurya
 * PrintingThread() changed to delete the USBPresetName_temp list and to make Overwritepreset flag false.
 *
 *    Rev 1.45   02 Feb 2015 09:31:42   amaurya
 * change in function CChildView::GetPrintingParameters() to get the correct power supply name
 *
 *    Rev 1.44   02 Feb 2015 07:06:44   amaurya
 * Removed the redundant and unused CopyAllFlag.
 *
 *    Rev 1.43   30 Jan 2015 08:12:56   amaurya
 * AnalyzePollingResponse() changed to display "PleaseWait" message screen on downspeed change.
 *
 *    Rev 1.42   26 Jan 2015 13:28:00   rjamloki
 * Starting State machine After view is created
 *
 *    Rev 1.41   06 Jan 2015 07:59:02   AnPawar
 * Checking the estop reset login menu before starting state machine.
 *
 *    Rev 1.40   06 Jan 2015 05:10:48   AnPawar
 * in printing thread if the current menu is not estop or reset then start the state machine.
 *
 *    Rev 1.39   05 Jan 2015 05:31:24   rjamloki
 * changes to handle e-stop while creating pdf
 *
 *    Rev 1.38   02 Jan 2015 04:56:04   rjamloki
 * AddSaveExit() function changed for confirmation screen on login and changes in printing thread to support usb copy all functionality
 *
 *    Rev 1.37   12 Dec 2014 06:06:12   RJamloki
 * CheckAvailablDiskSpace() changed to add condition for UsbGlobalFlag to display alarm UsbNearlyFull.
 *
 *    Rev 1.36   11 Dec 2014 06:48:14   RJamloki
 * Removed the case for SBC application close on ESCAPE buttotn click .Change to keep the event histry and welddata count in the hidden file.
 * 				DrawFirstScreen() changed to read the validated and non validated string from Main.gui file On powerUp.
 *
 *    Rev 1.35   28 Nov 2014 08:29:44   rjamloki
 * coverity issues and New Alarms Disk memory nearly full and usb memory nearly full alarms added and estop related changes.
 *
 *    Rev 1.34   14 Nov 2014 02:53:12   rjamloki
 * PdfWithImage() ,CreateNewPDFDoc() changed to handle pdf font.
*
*    Rev 1.33   10 Nov 2014 02:48:06   rjamloki
* Polling data response length changed,AssignFontForPrinting() and CStringToUTF() added for multilanguage PDF support.AnalyzePollingResponse() changed for UDIScan.
*
*    Rev 1.32   20 Oct 2014 05:38:46   RJamloki
* added 	ActSerialNumber and PrintOnAlarmAndSample() function changed to resolve welddata missing issue.
*
*    Rev 1.31   06 Oct 2014 03:22:04   rjamloki
* file path changed
*
*    Rev 1.30   01 Oct 2014 10:46:04   AnPawar
* File path changed.Changes for disk full and weld data log.Removed code for VQS.
*
*    Rev 1.29   26 Sep 2014 09:23:30   rjamloki
* Size Fix for new Branson Logo
*
*    Rev 1.28   25 Sep 2014 12:04:12   AnPawar
* DrawRect changed for run result screen
*
*    Rev 1.27   11 Sep 2014 09:42:18   rjamloki
* AnalyzePollingResponse() function modified for event description menu.
*
*    Rev 1.26   05 Sep 2014 12:11:26   rjamloki
* Fix for login button.
*
*    Rev 1.25   05 Sep 2014 06:57:22   amaurya
* Changes for Level C.Corrected the list traverse in AnalyzePollingResponse()
*
*    Rev 1.24   02 Sep 2014 03:24:42   rjamloki
*  USBMemoryFull falg and  ClearListOnUSBFullAlarm added for usb memory full alarm
*
*    Rev 1.23   26 Aug 2014 07:45:20   rjamloki
* Change The PDF Heading to "2000Xc"
*
*    Rev 1.22   18 Aug 2014 07:35:10   rjamloki
* Changes to get downspeed flag value. Fix for lost focus on keypad.
*
*    Rev 1.21   28 Jul 2014 13:31:06   rjamloki
* added boolean flag PDFException and SavePDFtoUSB() functions to handle usb exception.
*
*    Rev 1.20   22 Jul 2014 12:31:06   rjamloki
* Making disable flag false after pdf printing is over and before view invalidate
*
*    Rev 1.19   22 Jul 2014 08:07:34   akaushal
* Changes for VGA file path .
*
*    Rev 1.18   09 Jul 2014 06:46:18   akaushal
* Variables added to store status of automation,basicexpert,
* userchange condition,batch count.DrawFirstScreen(),
* AnalyzePollingResponse(),BuildPrintList(),PrintingThread(),
* SendUSBEventLogs(),SendLOGWeldData(),
* MakeLOGWeldData(),AddSaveExit() function changed.
*
*    Rev 1.17   11 Jun 2014 06:43:44   rjamloki
* SendPollingCommand() changed
*
*    Rev 1.16   09 Jun 2014 11:36:40   rjamloki
* initialized variables in constructors.Removed unused printing functions.Coverity fixes
*
*    Rev 1.15   27 May 2014 17:58:16   akaushal
* Added HistorySetup variable to get Setup info. at powerup
*
*    Rev 1.14   27 May 2014 06:20:30   amaurya
* updated macros for column and spacing.
*
*    Rev 1.12   20 May 2014 10:53:44   rjamloki
* SendLOGWeldData() function changed.
*
*    Rev 1.11   07 May 2014 13:03:06   akaushal
* Idle Logout time and Logon Screen
*
*    Rev 1.10   23 Apr 2014 11:19:48   akaushal
* Changes for saving heading parameters and live data to a pdf
*
*    Rev 1.9   21 Apr 2014 13:28:06   akaushal
* Added function for weld data and event data log and PDF.
*
*    Rev 1.8   28 Mar 2014 14:32:56   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.7     26 Mar 2014 14:20:56 rjamloki
* duplicate userid list removed,Convert_To_Pdf_SetUp() function removed it was for testing PDF.GetCurrentFilePath() function uses hardcoded string for power supply name.
*
*    Rev 1.6     05 Mar 2014 14:13:12 rjamloki
* Screens and PDF working
*
*    Rev 1.5     27 Feb 2014 01:03:08 jerryw.wang
* Added the buttons process for the Alarm Log and Event History.
*
*    Rev 1.4     03 Jan 2014 09:04:46 rjamloki
* Header Fix and added command to assign ip.
*
*    Rev 1.3     19 Dec 2013 06:16:50 rjamloki
* Changed macros to build on both EVC and VC++.
*
*    Rev 1.2     18 Dec 2013 10:00:28 rjamloki
* Initial Test version.SBC to WC serial communication.
*
*    Rev 1.1     05 Jun 2013 09:33:18 amaurya
* Initial Revision 2.
*
*    Rev 1.0     03 Apr 2013 10:09:42 amaurya
* Initial Revision.
*/


// ChildView.cpp : implementation of the CChildView class
#include "stdafx.h"
#include "AlarmButton.h"
#include "AlarmLog.h"
#include "AlarmLogData.h"
#include "Application.h"
#include "BottomHalf.h"
#include "Check.h"
#include "ChildView.h"
#include "CommPort.h"
#include "EtherPort.h"
#include "EventLog.h"
#include "hpdf.h"
#include "ListBox.h"
#include "MsgScreen.h"
#include "Mylanguage.h"
#include "png.h"
#include "RadioMenu.h"
#include "RunScreen.h"
#include "shellapi.h"
#include "Table.h"
#include "Text.h"
#include "Toggle.h"
#include "USBFolder.h"
#include "UserID.h"
#include "UserIDTable.h"
#include "VGA.h"
#include "VgaAlphanumeric.h"
#include "VgaBottomMenu.h"
#include "VgaButton.h"
#include "VgaChoice.h"
#include "VgaMenuItem.h"
#include "VgaScreenSetup.h"
#include "VgaSubMenu.h"
#include "VgaTitle.h"
#include "VgaVariable.h"
#include "WeldingHistory.h"
#include "zlib.h"
#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hpdf.h"
#include "ScreenKeypad.h"
#include "InputDevices.h"

#ifndef _WIN32_WCE
#define SYSTEMVERSIONPATH "C:\\Program Files (x86)\\Branson\\2000Xc\\ReleaseVersion.txt"
#else
#define SYSTEMVERSIONPATH "Disk\\ReleaseVersion.txt"
#endif
#ifdef DISABLEPRINTF
#define printf
#endif

#ifndef _WIN32_WCE
#define ZLIB_WINAPI
#endif

jmp_buf env;
bool PDFExceptionFlag = false;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif

   error_handler (HPDF_STATUS   error_no,
   HPDF_STATUS   detail_no,
   void         *user_data)
{
   printf ("ERROR: error_no=%04X, detail_no=%u\n",
      (HPDF_UINT)error_no, (HPDF_UINT)detail_no);
   PDFExceptionFlag = true;
   //vAfxMsgBox(_T("PDF could not be saved to USB"));
}
//libharu headers end




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ABSGAP			            15
#define SIZEOFVQSPRESETDATA		64
#define MAX_PRESET		         17
#define SIZEOFVQSSYSCON          8
#define STREAMINGSETUPPAGE      11
#define MAXINTLEN				10

#define DIAG_IO_POLL_BIT		0x08 //To notify WC that Diagnostic IO screen is opened
#define SCREENSETUP_POLL_BIT	0x02//to notify WC that Screen setup screen is opened
#define POLLING_DATA_RESPONSE_LEN 33//Polling data response length
#define SKIP_EVENTCHECK_POWERUP 20//To skip checking for events at power up for couple of pollings.
#define MAX_WELDDATA_REQUEST_COUNT 50//Max weld data request in single command
/////////////////////////////////////////////////////////////////////////////
// CChildView

#define PREVTRUE 0x1
#define CURRTRUE 0x2
#define WASESTOPPRESSED 0x3
#define EVENT_HISTORY_SIZE 52
#define MAX_EVENT_STORAGE_WC 100
extern void logOutFun(int ID);
extern void GetGraphData(unsigned char RequestType);
extern CMapStringToString values;
extern bool ProcessAlarmMenu(CVgaButton *);
extern CList<CString,CString> tempHistoryList;
extern CList<CString,CString> tempWeldList;
extern CList<CString,CString> tempHornScanList;
extern CList<CString,CString> tempGraphsList;
extern CList<CString,CString> tempScreenGraphsList;
extern CList<CString,CString> tempSetupList;
extern CList<CString,CString> tempScanGraphDataList;
extern CList<CString,CString> tempRunScreenList;
extern CList<CString,CString> tempEventHistoryList;
extern bool SaveWeldHistoryPdf(void);

//extern CTypedPtrList<CPtrList, IDDataList *> IDDataNewList;
extern CList<CString,CString> tempUserIDList;
extern POSITION RunScreenTemp_pos;
extern POSITION ScreenGraphsTemp_pos;
extern POSITION GraphsTemp_pos;
extern POSITION HistoryTemp_pos;
extern POSITION WeldTemp_pos;
extern POSITION HornScanTemp_pos;
extern POSITION ScanGraphsDataTemp_pos;
extern POSITION SetupTemp_pos;
extern POSITION DUPSTemp_pos;
extern POSITION SequenceTemp_pos;
extern POSITION UserIDTemp_pos;
extern int userid_list_status;

extern POSITION EventHistoryTemp_pos;
extern int YCoordinate;
extern CString EventDataFileName;
extern char Historyfname[64];
extern int eventname;
extern CString GlobalScanString;
extern int MaxDigitsUdiScan;
CString newMenuName="0";
char fname[256];
int CChildView::MenuType;
static int SkipEventCheckCount = 0 ;//To skip asking for events in first fiew pollings after power up
int HistorySetUp;
CString GraphTitle;
extern void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);
extern void SetHornScanObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);
CChildView* CChildView::thisPtr;
volatile bool creating_pdf=false;
bool PrintingAbortedOnEstop = false;
int Max_Preset_Possible;
int CChildView::Max_Allowed_Weld_Log = 0;
UDISCANSTATUS UdiStatus;
CString WaitForUDIScan = "";
CString MdyFormat = "",DmyFormat = "",PleaseWait = "",NotApplicable = "";
CString BatchCountText = "";
CString OkButtonText = "";
extern CString PsSerialNoStrHdr;
extern CString ActSerialNoStrHdr;
extern CString UserIdStrHdr;
extern CString PresetStrHdr;
extern CString PresetRevStrHdr;
extern CString SetAmpAStrHdr;
extern CString SetAmpBStrHdr;
extern CString TriggerForceStrHdr;
extern CString ActAssmNoStrHdr;
extern CString PsAssmNoStrHdr;
extern CString StackAssmNoStrHdr;
extern CString ValidatedStr;
extern CString NonValidatedStr;
extern int PresetCount;
extern unsigned char *StoredPresetListData;
extern CString PressureAStrHdr;
extern CString PressureBStrHdr;

int CChildView::UniversalCountWeldHiddenFile;
char FontPath[100] ="C:\\Program Files (x86)\\Branson\\2000Xc\\Fonts\\";
bool EstopPressedFlag;
bool UsbTimerStatus = false;//Flag  indicates that USB setup parameters are initialized at power up
void  SendResetTimeOutCommand(void);
CChildView::CChildView(): WaitForUSBData(false, true)
{
   PDFParamWidth = new int [MAXPARAMVALUES];
   AuthorityCheckSartUp = 1;
   LoginScreenFlag = true;
   EventFlag = false;
   listbuild = false;
   CBottomHalf::HornDownScreenPresent=false;
   ViewGraphWeldData=0;
   USBAlarm=false;
   USBMemoryFull=false;
   SBCDiskFull=false;
   RunResultScreen=false;
   AlarmScreenOnCalibration=false;
   IsAlarmScreen=false;
   AlarmPresent=false;
   DisableFlag =false;
   thisPtr = this;
   IsLanguageMenu=false;
   page_no=1;
   GraphOneRequestValue=2;
   GraphTwoRequestValue=0;
   LowerPMCLimit=0;
   UpperPMCLimit=0;
   PMCDisable=false;
   HornScanPlzWait=false;
   CommandForAlarmButton=false;
   USBGlobalFlag=false;
   StorageFormatGlobalFlag = false;
   LargeWaitingTime=false;
   PollingTimeOnMsgScrn=false;
   CurrMenuList=NULL;
   MenuNameID="";
   AlarmMenuIdentifier="";
   AlarmMenuName="";
   OverWritePreset=false;
   CopyPresetNum =0;
   OverWritePSPreset=false;
   OverWritePresetNum=0;
   BrowseUSB=false;
   MenuUSBDraw=false;
   BottomHalfScreen=false;
   DiagIOScreen = false;
   StringDebugFlag=false;
   EnableUSBGraph=false;
   AlarmUpdateRequired=false;
   CurrentFilepath = "";
   IdleLogoutTime = 0 ;
   ScanA_On = false;
   ScanB_On = false;
   ScanC_On = false;
   CurrentScan_On = false;
   Sys_FileSize = 0;
   PasswordRequired = false;
   GraphWeldDataIdArray = NULL;
   WeldDataIdArray = NULL;
   UniversalCount = 0;
   UniversalCountWeldHiddenFile = 0;
   UniqueID = -1;
   WeldOnChangedPreset = false;
   IsPageSizeMenu = false;
   GlobalCycleCount = 0;
   ExtPreset = false;
   PresentWeldCount = 0;
   PresentAlarmCount = 0;
   mainMenuAddress = -1;
   GraphsMenu_Address = -1;
   WeldSetup_Address = -1;
   WeldResults_Address = -1;
   Total_Objects = 0;
   BaseWeldCount = 0;
   TempBaseWeldCount = 0;
   PresentPresetNum = -1;
   TempPresetNum = -1;
   Total_Text_Objects = 0;
   EventDataFileName = "";
   EventDataFileName = EventDataFileName + DISK + "EventLog.log";
   HistoryDataFileName = "";
   HistoryDataFileName = HistoryDataFileName + DISK + "WeldData.log";
   DownspeedEnable = false;
   ActSerialNumber = "";
   PresetBarCodeStart = "";
   USBMemoryNearlyFull = false;
   DISKMemoryNearlyFull = false;
   PresetNameCount = 0;
   PresetListBuff = NULL;
   FoundPresetToCopy = false;
   CopyAllPresetAddress_Ok = 0;
   CancelButtonFlag = false;
   USBCheckCopyAllFlag = false;
   PresetName = "";
   PresetOverwriteCheckedFlag = false;
   //coverity 11578
   AuthorityCheck = false;
   MemoryfullCont_Stop = false;
   TemporaryAlarmCount = 0;
   SetupMenuPointer = 0;
   SequenceMenuPointer = 0;
   DisplayLockFlag = false;
   ScanA_Present = false;
   ScanB_Present = false;
   ScanC_Present = false;
   CurrentScan_Present = false;
   PDFFontName = 0;
   CopyAllPresetAddress = 0;


}
CVgaMenuItem *GlobalAlarmObject=NULL;
int CChildView::StartWeldData;
CStringArray CChildView::WeldDataPatamStringID;
CStringArray CChildView::EventDataPatamStringID;
CStringArray CChildView::UserIDPatamStringID;
CString CChildView::PSName;
CList<CString, CString>CChildView::USBPresetNames;
CList<CString, CString>CChildView::USBPresetName_temp;
int CChildView::TotalUSBPreset;
int CChildView::SelectedUSBPreset=0;
int CChildView::SelectedPowerPreset=CChildView::CurrentPresetNum;
bool CChildView::LastSelectedPresetFrom;
bool CChildView::PMCScreen=false;
CString CChildView::ScanString;
int CChildView::TempCount=0;
bool CChildView::ColdStartInProcess=false;
CString CChildView::mainmenu_string;
CString CChildView::WeldResult_string;
CString CChildView::WeldSetup_string;
CString CChildView::Graphs_string;
int CChildView::Currentlanguage=0;
bool CChildView::RunResultScreen=false;
bool CChildView::WasRunResultScreen=false;
bool CChildView::PowerUpSBC=false;
bool CChildView::PollingTimeOnMsgScrn;
bool CChildView::LargeWaitingTime;
bool CChildView::USBGlobalFlag;
bool CChildView::StorageFormatGlobalFlag;
bool CChildView::DownspeedEnable = false;
bool CChildView::USBOverWritePreset = false;
struct CChildView::PrintValues Setup,Welddata,WeldHistory,PowerGraph,ColDistance,VelocityGraph,
   ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence;

struct CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
   USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

bool CChildView::CommandForAlarmButton;
struct CChildView::PrintingSetup PrintSetup;
CString CChildView::USBSelectedPresetName;
CString CChildView::PSPresetText[MAX_PSPRESET];
CString CChildView::LastUSBPresetFolder;

int CChildView::ColumnPerPage;
int CChildView::ButtonType;
int CChildView::RowPerPage;
int CChildView::HWconfiguration;
int CChildView::SWconfiguration;
int CChildView::Securitylevel;
int CChildView::UserChangeCond;
int CChildView::WeldMode;
int CChildView::Actuator;
int CChildView::ControlLevel;
int CChildView::AccessLevelSystem;
int CChildView:: ExitButtonFlag;
int CChildView::SaveButtonFlag;
int CChildView::LoginButtonFlag;
int CChildView::LogoutButtonFlag;
int CChildView::ViewGraphGlobalCount;
int CChildView::PMCMaxVdata;
int CChildView::CurrentSequencePreset=0;
bool CChildView::PMCDisable;
int CChildView::LowerPMCLimit;
int CChildView::UpperPMCLimit;
bool CChildView::ISUSBPresent;
bool CChildView::SaveRecallPresetScrn;
bool CChildView::ContinuePrinting;
int CChildView::BasicExpert;
bool CChildView::Automation;

CString *CChildView::Parameter_Heading;
CString *CChildView::Parameter_Event_Heading;
CString *CChildView::Parameter_UserID_Heading;
CString *CChildView::Parameter_UserID_HeadingS;
CString *CChildView::Parameter_Units_Metric;
CString *CChildView::Parameter_Units_USCS;
int *CChildView::Parameter_ID;
int *CChildView::EventParameter_ID;
int *CChildView::UserIDParameter_ID;
int CChildView::TotalTextHeading;
CString *CChildView::Parameter_Alarm_Heading;
int *CChildView::AlarmLogPara_ID;
int CChildView::TotalAlarmHeading;
int *CChildView::EventLogPara_ID;
int CChildView::TotalEventHeading;
int *CChildView::UserIDPara_ID;
int CChildView::TotalUserIDHeading;
int CChildView::TotalEventTextHeading;
int CChildView::TotalUserIDTextHeading;
int CChildView::BotomHalfRefreshTime=0;
bool CChildView::ActColdStartFlag =false;
bool CChildView::IsNewScreenPointer=false;
bool CChildView::BottomHalfTimerOn=false;
bool CChildView::powerup=false;
int CChildView::TextColor=Black;
int CChildView::Button_Color=Gray;
int CChildView::TitleBarColor=Blue;
int CChildView::Back_Color=White;
int CChildView::Highlight_Color=Green;
bool CChildView::SysInfoScreen=false;
bool CChildView::Start_Screen=0;
int CChildView::Language_Index=0;
bool CChildView::IsTwoSecExpired=false;
bool CChildView::metric=false;
bool CChildView::PasswordFlag=false;
bool CChildView::AutoRefreshon =false;
bool CChildView::BatchEnabled = false;
bool CChildView::ScreenSetupFlag=false;
bool CChildView::DisableFlag=false;
int CChildView::RAMCalibCordinate_Xa;
int CChildView::RAMCalibCordinate_Ya;
int CChildView::RAMCalibCordinate_Xb;
int CChildView::RAMCalibCordinate_Yb;
int CChildView::CurrentPresetNum=1; //one by default
int CChildView::WeldCycleCount;
int CChildView::PresetNum;
int CChildView::BatchCount;
UDISCANSTATUS CChildView::PrevUDIStatus = UDISCAN_OFF;
int CChildView::AlarmCount;
int CChildView::GraphOneRequestValue=0;
int CChildView::GraphTwoRequestValue=0;
int CChildView::Presettrack=0;
int CChildView::MaxPreset=0;
bool CChildView::LoginScreenFlag=false;
DWORD CChildView::Color_Array[]={
   RGB(0,0, 0),//ColorNone
   RGB(0, 0, 0),//Black
   RGB(0, 0, 255),//Blue
   RGB(255,0,0),//Red
   RGB(0,255,0),//Green
   RGB(128,42,42),//Brown
   RGB(255,0,255),//Magenta
   RGB(0,255,255),//Cyan
   RGB(88,88,88),//Dark_Gray
   RGB(127,127,127),//gray
   RGB(255,255,0),//Yellow
   RGB(255,255,255)//white
};

const char * const Languages[] = {
   "\\Languages\\English.lan",
   "\\Languages\\ChineseSiml.lan",
   "\\Languages\\ChineseTrad.lan",
   "\\Languages\\French.lan",
   "\\Languages\\German.lan",
   "\\Languages\\Italian.lan",
   "\\Languages\\Japanese.lan",
   "\\Languages\\Korean.lan",
   "\\Languages\\Spanish.lan",
   0
};



CChildView::~CChildView()
{
   BottomHalfTimerOn=true;
   while (keypadList.GetCount())
      delete keypadList.RemoveHead();

   menusname.RemoveAll();
   menus.RemoveAll();
   menupointers.RemoveAll();

   delete []Parameter_Heading;
   delete []Parameter_Units_Metric;
   delete []Parameter_Units_USCS;
   delete []Parameter_ID;
   delete []PDFParamWidth;
   delete []EventLogPara_ID;
   delete []Parameter_UserID_HeadingS;

   while(USBPresetNames.GetCount())
      USBPresetNames.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers
BEGIN_MESSAGE_MAP(CChildView, CWnd)
   ON_WM_PAINT()
   ON_WM_LBUTTONDOWN()
   ON_COMMAND(ID_MAINMENU, OnMainMenu)
   ON_WM_ERASEBKGND()
   ON_WM_KEYDOWN()
   ON_WM_TIMER()
   ON_WM_LBUTTONUP()
   ON_WM_CREATE()
END_MESSAGE_MAP()



BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
   if (!CWnd::PreCreateWindow(cs))
      return FALSE;

   cs.style &= ~WS_BORDER;
   cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
      AfxGetApp()->LoadStandardCursor(IDC_ARROW),HBRUSH(COLOR_WINDOW) , NULL);
   powerup=true;
   DrawFirstScreen();//Getting First MenuScreen.
   return TRUE;
}

/*******************************************/
/*this function is for drawing the screen .*/
/*******************************************/

void CChildView::OnPaint()
{
   CPaintDC dc1(this); // device context for painting
   CDC * pDC = &dc1;
   CDC dc;
   CDC* pDrawDC =pDC;

   CBitmap bitmap;
   CBitmap* pOldBitmap = NULL;
   if (!pDC->IsPrinting())
   {
      // draw to offscreen bitmap for fast looking repaints
      if (dc.CreateCompatibleDC(pDC))
      {
         if (bitmap.CreateCompatibleBitmap(pDC, MAX_VGA_X_VALUE+2*XOFFSET,
            MAX_VGA_Y_VALUE+2*XOFFSET))
         {
            pDrawDC = &dc;
            pOldBitmap = dc.SelectObject(&bitmap);
         }
      }
   }

   CBrush brush;
   if(theApp.GraphsDataList.GetCount()>0)
      brush.CreateSolidBrush(Color_Array[White]);
   else
      brush.CreateSolidBrush(Color_Array[Back_Color]);
   CBrush * oldBrush;
   oldBrush = pDrawDC->SelectObject(&brush);
   pDrawDC->Rectangle(VGA_Rect);
   pDrawDC->SelectObject(oldBrush);

   if(OnKeypadScreen_flag==true)
      DrawKeypad(pDrawDC);//draw keypad.
   else
   {
      theApp.DrawMenu(pDrawDC);
   }
   DrawPageNumber(pDrawDC);
   if((CChildView::thisPtr->BottomHalfScreen)&&(!OnKeypadScreen_flag))
   {
      //		printf("\n BottomHalfScreen");
      int TempColor=TextColor;
      POSITION pos = CBottomHalf::BottomMenuPointer->items.GetHeadPosition();
      while(pos)
      {
         CVgaMenuItem *Object = CBottomHalf::BottomMenuPointer->items.GetNext(pos);
         if(Object->IsDraw)
         {
            if(CChildView::TextColor==White)
               CChildView::TextColor=Black;
            Object->Draw(pDrawDC);
         }
      }
      TextColor=TempColor;
   }

   pDC->BitBlt(0,0,MAX_VGA_X_VALUE+2*XOFFSET,MAX_VGA_Y_VALUE+2*XOFFSET,&dc,0,0,SRCCOPY);
   if(pOldBitmap) {
      dc.SelectObject(pOldBitmap);
      bitmap.DeleteObject();
   }
   brush.DeleteObject();
   SetFocus();//FIx for some time key down event(Key Board) not working
   PowerUpSBC=false;
}



/*****************************************************************************/
/* Function is used to get starting information at power up.				 */
/*****************************************************************************/
void CChildView::DrawFirstScreen()
{
   printf("in CChildView::DrawFirstScreen()");
   CChildView::ColdStartInProcess=false;
   bool GetFirstScreen=false;
   while(!GetFirstScreen)
      GetFirstScreen=app->GetBottomMenuAddress(&Start_Screen,&WeldResults_Address,
      &mainMenuAddress,&WeldSetup_Address,
      &GraphsMenu_Address,&Language_Index,&metric);
   printf("GetBottomMenuAddress() completed\n");
   GetRAMData();
   printf(" GetRAMData()\n");
   printf("CurrentLanguageName = %s \n",CurrentLanguageName);
   theApp.PrepareStringFromUnicodeText(CurrentLanguageName,true,true);
   WaitForUDIScan =  CVgaMenuItem ::LinearSearch(XSTR(WAITFORUDI_STRINGID));
   PsSerialNoStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PSSERNUM_HEADING_STRID));
   ActSerialNoStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(ACSERNUM_HEADING_STRID));
   UserIdStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(USERID_HEADING_STRID));
   PresetStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PRESETNUM_HEADING_STRID));
   PresetRevStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PRESETREV_HEADING_STRID));
   SetAmpAStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(SETAMPA_HEADING_STRID));
   SetAmpBStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(SETAMPB_HEADING_STRID));
   TriggerForceStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(TRIFORCE_HEADING_STRID));
   ActAssmNoStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(ACTASSMNO_HEADING_STRID));
   PsAssmNoStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PSASSM_HEADING_STRID));
   StackAssmNoStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(STACKASSM_HEADING_STRID));
   ValidatedStr = CVgaMenuItem ::LinearSearch(XSTR(VALIDATED_ID));
   NonValidatedStr	= CVgaMenuItem ::LinearSearch(XSTR(NONVALIDATED_ID));
   MdyFormat = CVgaMenuItem ::LinearSearch(XSTR(MMDDYY_ID));
   DmyFormat = CVgaMenuItem ::LinearSearch(XSTR(DDMMYY_ID));
   PleaseWait =CVgaMenuItem ::LinearSearch(XSTR(PLEASEWAIT_ID));
   BatchCountText = CVgaMenuItem ::LinearSearch(XSTR(BATCHCOUNTTEXT_ID));
   OkButtonText = CVgaMenuItem ::LinearSearch(XSTR(OK_BUTTONTEXT_ID));
   PressureAStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PRESSUREA_HEADING_STRID));
   PressureBStrHdr =  CVgaMenuItem ::LinearSearch(XSTR(PRESSUREB_HEADING_STRID));
   NotApplicable = CVgaMenuItem ::LinearSearch(XSTR(NOTAPPLICABLETEXT_ID));

   AssignFontForPrinting();
   printf(" PrepareStringFromUnicodeText()\n");
   theApp.GetSystemVariable();
   printf(" GetSystemVariable()\n");
   CChildView::AccessLevelSystem=USER_OPERATOR;
   theApp.ReadXML();
   printf(" ReadXML()\n");
   GetStartingEventCount();
   GetStartingWeldCount();
   GetDownspeedtuneFlag();
   DownspeedMenuName = CVgaBottomMenu::WeldSetup_ID;
   if((ReadStartUpVersionString()==true) &&
      (ReadSystemVersionString()==true) )
   {
      GetWeldDataIdArray(false);
      GetGraphWeldDataIdArray(false);
      WaitForPrintData.ResetEvent();
      AfxBeginThread(CChildView::PrintingThread,0); //start it while printing
      /* Start the USB Thread and Reset the USB Event.*/
      WaitForUSBData.ResetEvent();
      AfxBeginThread(WriteDataToUSB, 0  ); //start it when writing data to USB
      WaitForEtherNetAlarmHandle.ResetEvent();
      AfxBeginThread(EtherNetAndAlarmHandle, 0  );
	  AfxBeginThread(CChildView::SendSerialCommand,0);
   }
   else
   {
      theApp.menuName = CVgaBottomMenu::MenuErrorID;
      CVgaMenu * menu;
      if (theApp.menus.Lookup(theApp.menuName, menu))
      {
         theApp.MenuPointer=menu;
         ModifyObjectList(menu);
      }
   }
}

void PdfWithImage(HPDF_Doc * pdf,HPDF_Page * page,HPDF_Font *def_font)
{

   HPDF_Image image;
#ifdef _WIN32_WCE
   image = HPDF_LoadPngImageFromFile2 (*pdf, "\\Disk\\bransonLogo.png");
#else
   image = HPDF_LoadPngImageFromFile2 (*pdf, "C:\\Program Files (x86)\\Branson\\2000Xc\\bransonLogo.png");
#endif

   /* Draw image to the canvas. (normal-mode with actual size.)*/
   HPDF_Page_DrawImage (*page, image, HPDF_Page_GetWidth(*page)-170.0f,HPDF_Page_GetHeight(*page)-35.0f, (HPDF_REAL)(HPDF_Image_GetWidth (image)/4), (HPDF_REAL)(HPDF_Image_GetHeight (image)/4));
   HPDF_Page_SetLineWidth (*page,2);
   HPDF_Page_MoveTo (*page, 2, HPDF_Page_GetHeight(*page)-THREEWELDLINEGAP);
   HPDF_Page_LineTo (*page, HPDF_Page_GetWidth(*page)-10, HPDF_Page_GetHeight(*page)-THREEWELDLINEGAP) ;
   HPDF_Page_Stroke (*page);
   HPDF_Page_SetFontAndSize (*page, *def_font,15);
   int x = (int)HPDF_Page_GetWidth(*page)-150;
   CChildView::DrawPDFText(page,x,TWOWELDLINEGAP+10,"2000Xc");

}
/* this function is used to enable state machine on button click*/
void EnableStateMachine(int ID)
{

   printf("enabling state machine\n");
   CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
   CChildView::thisPtr->Invalidate();

}

/*Function to start and Stop state machine
* arg1 bool state : true to start state machine
* flase to stop state machine
* return false 1.If response is not received
* 2.If NAK is received
*/
bool CChildView::SendCommandForStateMachineEnable(STATEMACHINESTATE state)
{
   printf("in SendCommandForStateMachineEnable \n");
   CHostCommand * request = new CHostCommand(STATEMACHINE_ENABLED,(unsigned char *)(&state),STATEMACHINE_ENABLED_SIZE);
   CHostCommand * response = app->SendUiHostCommand(request);

   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch==theApp.ACK)
      {
         delete response;
         return true;
      }
      else
      {
         delete response;
         return false;
      }
   }
   return false;
}

/*Function used to check any running cycles on WC
Return true if WC state is Ready or PreReady*/
bool CChildView::GetStateMachineStatus(void)
{
   printf("in GetStateMachineStatus()\n");
   CHostCommand * request = new CHostCommand(CHECKSTATEMACHINE,0,0);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      if(ch==theApp.ACK) //no running cycles
      {
         delete response;
         return true;
      }
      else
      {
         delete response;
         return false;
      }
   }
   return false;
}

/****************************************************************************/
/*    Function is called when user presses the left mouse button or presses */
/*    any  button on the screen.                                            */
/****************************************************************************/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   if(ScreenSetupFlag!=true)//calibration will not apply on Screen setup screen.
      point= CalibratePoint(point);

   CDC*pDC = GetDC();
   if(OnKeypadScreen_flag)
   {
      if(!DisableFlag)
      {

         CVgaMenuItem * object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
         POSITION pos1 = menu1->items.GetHeadPosition();
         while(pos1)
         {
            object = menu1->items.GetNext(pos1);
            if(object->GetType() == CVgaMenu::BottomMenu_Id)
            {
               break;
            }
         }
         if (object->MouseClick(point, this))
         {
            ReleaseDC(pDC);
            return;
         }
         else
         {
            CScreenKeypad *object=keypadList.GetTail();
            object->DrawPressedkey(point, pDC);
            ReleaseDC(pDC);
            return;
         }
      }
      else
      {
         ReleaseDC(pDC);
         return;
      }
   }

   CVgaMenuItem * object;


   /*	If disable flag is ON then only confirm screen button */
   /*  will be processed,other will be ignored.              */
   if(DisableFlag)
   {
      bool MessgObject=false;
      POSITION pos1 = menu1->items.GetHeadPosition();
      while (pos1)
      {
         object = menu1->items.GetNext(pos1);
         while((!object->IsDraw)&&(pos))
         {
            object = menu1->items.GetNext(pos);
         }
         if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
         {
            MessgObject=true;
         }
         else if(((object->GetType() == CVgaMenu::VGA_Button_OBJECT)||(object->GetType() == CVgaMenu::ALPHA)) && MessgObject && object->RectShow )
         {
            if (object->GetRect().PtInRect(point))
            {
               object->SetButtonState1(true) ;
               object->Draw(pDC);
               DisableFlag=false;
               ReleaseDC(pDC);
               return;
            }
         }
      }
   }
   pos = menu1->items.GetHeadPosition();
   while (pos)
   {
      object = menu1->items.GetNext(pos);
      if((object->GetType() == CVgaMenu::VGABottomHalfObject)&&(object->GetRect().PtInRect(point)))
      {

         if(MenuNameID!="")
         {
            if(!theApp.menus.Lookup(MenuNameID, menu1))
            {
               return;
            }
            POSITION pos1=menu1->items.GetTailPosition();
            object = menu1->items.GetPrev(pos1);
            object = menu1->items.GetPrev(pos1);
            if((object->PSType == CVgaMenu::VGA_Button_OBJECT)&&(object->RectShow))
            {
               if(object->GetRect().PtInRect(point))
               {
                  if(!DisableFlag)
                  {
                     if(object->MouseClick(point, this))
                     {
                        object->SetButtonState1(true) ;
                        object->Draw(pDC);
                        if(object->GetButtonState1()==true)
                           object->SetButtonState1(false) ;

                     }
                  }
                  ReleaseDC(pDC);
                  return;
               }
            }
            pos1 = menu1->items.GetHeadPosition();
            while (pos1)
            {
               object = menu1->items.GetNext(pos1);
               if((object->GetType() == CVgaMenu::VGA_Button_OBJECT)&&(object->RectShow)&&(object->IsDraw))
               {
                  if(object->GetRect().PtInRect(point))
                  {
                     if(object->MouseClick(point, this))
                     {
                        object->SetButtonState1(true) ;
                        object->Draw(pDC);
                        if(object->GetButtonState1()==true)
                           object->SetButtonState1(false) ;
                        DisableFlag=false;
                        ReleaseDC(pDC);
                        return;
                     }
                  }
               }
            }
            ReleaseDC(pDC);
            return;
         }
      }
   }


   /*	If disable flag is off then process other buttons.*/
   if(!DisableFlag)
   {
      object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
      pos = menu1->items.GetHeadPosition();
      if (pos)
      {
         object = menu1->items.GetNext(pos);
         if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
         {
            if (object->GetRect().PtInRect(point))
            {
               object->SetButtonState1(true) ;
               object->Draw(pDC);
               ReleaseDC(pDC);
               return;
            }

         }
      }
      pos = menu1->items.GetHeadPosition();
      while (pos)
      {
         object = menu1->items.GetNext(pos);
         while((!object->IsDraw)&& pos)
         {
            object = menu1->items.GetNext(pos);
         }
         if((object->GetType() == CVgaMenu::COLORSETUP_ID)
            ||(object->GetType() == CVgaMenu::BottomMenu_Id))
         {
            if (object->MouseClick(point, this))
            {
               ReleaseDC(pDC);
               return;
            }
         }
      }
      if(AlarmUpdateRequired)
      {
         if (GlobalAlarmObject->GetRect().PtInRect(point))
         {
            GlobalAlarmObject->SetButtonState1(true) ;
            GlobalAlarmObject->Draw(pDC);
            ReleaseDC(pDC);
            return;
         }
      }
      /* If Current screen is not keypad screen process menu button*/
      if(!OnKeypadScreen_flag)
      {

         pos = menu1->items.GetHeadPosition();
         object = menu1->items.GetNext(pos);
         //Counting the objects except VGA Buttons.
         int Current_page_no=page_no;//adding page no.
         while (pos)
         {
            object = menu1->items.GetNext(pos);
            while((!object->IsDraw) && pos)
            {
               object = menu1->items.GetNext(pos);
            }
            if( (object->PSType!=CVgaMenu::TITLE)&&((object->GtPageNum()== Current_page_no)
               ||(object->GtPageNum()== CVgaMenuItem::PAGEALL)))
            {
               if (object->GetRect().PtInRect(point))
               {
                  if((object->PSType==CVgaMenu::TITLE) ||
                     (object->PSType == CVgaMenu::TEXT) ||
                     (object->PSType == CVgaMenu::VGATEXT)
                     ||(object->PSType==CVgaMenu::VGATableObject)
                     ||(object->PSType== CVgaMenu::VGABottomHalfObject))
                  {
                     ReleaseDC(pDC);
                     return;
                  }
                  if((object->RectShow))
                  {
                     object->SetButtonState1(true) ;
                  }

                  if((object->PSType != CVgaMenu::VGATOOLMAP))
                  {
                     object->Draw(pDC);
                  }
                  ReleaseDC(pDC);
                  return;
               }
            }
         }
      }
      //process keypad.
      ReleaseDC(pDC);
   }
}

void CChildView::OnMainMenu()
{
   Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
   return FALSE;
}

/******************************************************************/
/*      Function giving the rectangle To the Back next button.    */
/******************************************************************/
void CChildView::Back_Next_Button_Layout()
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   /*Give co-ordinates to back,next,exit and save buttons.*/
   POSITION pos = menu1->items.GetTailPosition();
   while (pos)
   {
      CVgaMenuItem * object = menu1->items.GetPrev(pos);
      int type = object->GetType();
      if (type == CVgaMenu::NEXT)
      {
         object->SetRect(NextButtonRect);
      }

   }
   pos = menu1->items.GetTailPosition();
   while (pos)
   {
      CVgaMenuItem * object = menu1->items.GetPrev(pos);
      int type = object->GetType();
      if (type == CVgaMenu::BACK)
      {
         object->SetRect(BackButtonRect);
      }
   }
}
/***********************************************************************************/
/*  Function adding the Back Next button in the list According to the Object Count */
/*  To be Display.																   */
/***********************************************************************************/
void CChildView::Add_Back_Next_Button()
{

   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   if(Total_Text_Objects<Max_Text_1_Coloum)
   {

      CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
      mutex.Lock();

      while(menu1->items.GetCount()>0)
      {
         CVgaMenuItem *Obj = menu1->items.GetHead();
         int type = Obj->GetType();
         if((type==CVgaMenu::NEXT)||(type==CVgaMenu::BACK))
         {
            delete menu1->items.RemoveHead();
         }
         else
         {
            TempDataList.AddTail(Obj);
            menu1->items.RemoveHead();
         }
      }
      POSITION pos2 = TempDataList.GetHeadPosition();
      while(pos2)
      {
         CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
         menu1->items.AddTail(Obj);
      }
      while(TempDataList.GetCount())
         TempDataList.RemoveHead();


      if((page_no>1))
      {
          menu1->items.AddTail(CVgaMenu::CreateObjectBack_Next(CVgaMenu::BACK));
      }
      if(Total_Objects >(page_no*RowPerPage*ColumnPerPage))
      {
         menu1->items.AddTail(CVgaMenu::CreateObjectBack_Next(CVgaMenu::NEXT));

      }
   }
   mutex.Unlock();
}

/*********************************************************/
/*    Function is called at left mouse button up.        */
/*********************************************************/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   if(ScreenSetupFlag!=true)
      point= CalibratePoint(point);

   CDC*pDC = GetDC();
   CVgaMenuItem * object;
   POSITION pos = menu1->items.GetHeadPosition();

   /*Reinitialize idle logout timer if mouse is clicked*/
   if(LoginScreenFlag == false)
   {
      if(IdleLogoutTime>0)
         CChildView::InitialiseTimer(IDLELOGOUT_TIMER,IdleLogoutTime);
   }

   /*checking if bottom menu is clicked */
   if(pos)
   {
      object = menu1->items.GetNext(pos);
      if((object->GetType() == CVgaMenu::VGA_Button_OBJECT))
      {
         if (object->GetRect().PtInRect(point))
         {
            if(object->MouseClick(point, this))
            {
               object->SetButtonState1(false) ;
               ReleaseDC(pDC);
               return;
            }
         }
      }
      else if(object->GetType() == CVgaMenu::BottomMenu_Id)
      {
         if(object->MouseClick(point, this))
         {
            ReleaseDC(pDC);
            return;
         }
      }

   }
   if(AlarmUpdateRequired)
   {
      if(GlobalAlarmObject->GetButtonState1()==true)
      {
         GlobalAlarmObject->SetButtonState1(false) ;
         GlobalAlarmObject->Draw_Pressed_Released_Button(pDC);//draw button in released condition.
         if(GlobalAlarmObject->MouseClick(point, this))
         {
            ReleaseDC(pDC);
            return;
         }
      }
   }
   pos = menu1->items.GetHeadPosition();
   if(!OnKeypadScreen_flag)
   {
      while (pos)
      {
         object = menu1->items.GetNext(pos);


         if(object->GetButtonState1()==true)
         {
            object->SetButtonState1(false) ;
            if((object->PSType!=CVgaMenu::VGATOOLMAP))
               object->Draw_Pressed_Released_Button(pDC);//draw button in released condition.

            //DisplayLockFlag = 0;

            if((DisplayLockFlag &&((( object->AccessLevel > USER_OPERATOR)&&(object->PSType== CVgaMenu::SUBMENU))
               ||(object->PSType==CVgaMenu::HHMM)||(object->PSType== CVgaMenu::DATE)
               ||(object->PSType==  CVgaMenu::CHOICE)||(object->PSType==  CVgaMenu::ALPHA)
               ||(object->PSType==  CVgaMenu::VARIABLE)||(object->PSType==  CVgaMenu::RADIO_BUTTON)
               ||(object->PSType==  CVgaMenu::RADIOMENU )||(object->PSType== CVgaMenu::TOGGLE)
               ||((object->PSType == CVgaMenu::VGA_Button_OBJECT)&&(object->AccessLevel > USER_OPERATOR)))))/* Display Lock Active ?*/
            {
               ErrorBeep();
               CVgaMenu *menu;
               printf("DisplayLockFlag = %d\n",DisplayLockFlag);
               printf("AccessLevel = %d\n",object->AccessLevel);
               printf("PSType = %d\n",object->PSType);

               CString str = object->text;//Coverity Fix
               if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
               {
                  AccessLevelSystem=USER_OPERATOR;
                  menusname.AddTail(theApp.menuName);
                  menus.AddTail(page_no);
                  menupointers.AddTail(theApp.MenuPointer);
                  page_no=1;
                  ModifyObjectList(menu);
                  theApp.menuName=CVgaBottomMenu::mainMenuID;
                  theApp.MenuPointer=menu;
               }
               ReleaseDC(pDC);
               Invalidate();
               return;
            }
            else
            {
               if(object->MouseClick(point, this))
               {
                  ReleaseDC(pDC);
                  return;
               }
            }
         }
      }
   }
   else if(OnKeypadScreen_flag)//process keypad
   {
      CVgaMenuItem * object=menu1->items.GetHead();//Bottom menu or screen set up screen processed.
      POSITION pos1 = menu1->items.GetHeadPosition();
      while(pos1)
      {
         object = menu1->items.GetNext(pos1);
         if(object->GetType() == CVgaMenu::BottomMenu_Id)
         {
            break;
         }
      }
      if (object->MouseClick(point, this))
      {
         //			printf("\n MouseClick");
         ReleaseDC(pDC);
         return;
      }
      else
      {
         CScreenKeypad *object=keypadList.GetTail();
         object->MouseClick(point, this,pDC);
      }
   }
   ReleaseDC(pDC);
}

/********************************************/
/* This function will prepare keypad list.  */
/********************************************/

void CChildView::BuildCompleteKeypadList(int type,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr)
{
   while (keypadList.GetCount())
      delete keypadList.RemoveHead();
   keypadList.AddTail(new CScreenKeypad(type,data,Object_Text,ID,ptr));
}
/*****************************************************/
/*   Function called from OnPaint to draw keypad.    */
/*****************************************************/
void CChildView::DrawKeypad(CDC*pDrawDC)
{
   CScreenKeypad *object1=keypadList.GetTail();
   object1->Draw(pDrawDC);
   CVgaMenu * menu1;
   menu1=theApp.MenuPointer;
   POSITION pos = menu1->items.GetHeadPosition();
   CVgaMenuItem * object=menu1->items.GetNext(pos);
   object->Draw(pDrawDC);
   while(pos)
   {
      object=menu1->items.GetNext(pos);
      if(object->GetType()== CVgaMenu::BottomMenu_Id)
      {
         object->Draw(pDrawDC);
         return;
      }

   }
}

/*****************************************************************************/
/*  This function will handle different timers used i.e. for keypad,		 */
/*  for Polling command,for message screen,for bottom half refresh.			 */
/*****************************************************************************/
void CChildView::OnTimer(UINT nIDEvent)
{
   switch(nIDEvent)
   {

   case ALPHAENTRYTIMER:
      {
         KillTimer(ALPHAENTRYTIMER);
         CDC * pDC=GetDC();
         IsTwoSecExpired=true;
         if(OnKeypadScreen_flag)
            CScreenKeypad::VGAAlphaEntry(pDC);
         ReleaseDC(pDC);
      }
      break;

   case Pollingtimer:
      {

         KillTimer(Pollingtimer);
         SendPollingCommand();
         if(MenuUSBDraw)
            MenuUSBDraw=false;
      }
      break;

   case BOTTOMHALFTIMER:
      {
         if(OnKeypadScreen_flag)
         {
            KillTimer(BOTTOMHALFTIMER);
            BottomHalfTimerOn=false;
            CChildView::thisPtr->BottomHalfScreen=false;

         }
         else
         {
            KillTimer(BOTTOMHALFTIMER);
            CVgaMenu * menu1=theApp.MenuPointer;
            CString MenuName=theApp.menuName;
            int type=-1;
            POSITION pos = menu1->items.GetHeadPosition();
            CVgaMenuItem * Object;
            while(pos)
            {
               Object = menu1->items.GetNext(pos);
               if(Object->GetType() == CVgaMenu::VGABottomHalfObject)
               {
                  CBottomHalf *obj=(CBottomHalf*)Object;
                  type=obj->Bottomtype;
                  break;
               }
            }
            if(type==0)
            {
               KillTimer(BOTTOMHALFTIMER);
               if(CBottomHalf::BottomMenuPointer!=0)
                  menu1=CBottomHalf::BottomMenuPointer;
               int length =2;
               unsigned char data1[2];
               union
               {
                  short i;
                  char c[2];
               } u;
               u.i=CBottomHalf::BottomHalfId;
               data1[1]=u.c[0];
               data1[0]=u.c[1];
               unsigned char * data = (unsigned char *) &data1[0];
               CHostCommand * request = new CHostCommand(GetBottomMenuData_FunID, data, length);
               CHostCommand * response = app->SendPollingHostCommand(request);
               if(response)
               {
                  char ch=CHostCommand::AckNak();
                  data = response->GetData();
                  length = response->GetDataLength();
                  if(ch==ACK)
                  {
                     int MenuID=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);

                     char TempArrayfg[10];
                     CString Temp=_itoa(MenuID,TempArrayfg,10);
                     //printf("menuID=%d MenuNameID=%S temp=%S \n",MenuID,MenuNameID,Temp);
                     if(!((MenuNameID == XSTR(HORNDOWN_MENU)) || (MenuNameID == XSTR(DIAGNOSTIC_MENU))))
                     {
                        if(IdleLogoutTime>0)
                           CChildView::InitialiseTimer(IDLELOGOUT_TIMER,IdleLogoutTime);
                     }
                     if((MenuID!=0) && (MenuNameID!=Temp))
                     {
                        if(!theApp.menus.Lookup(Temp, menu1))
                        {
                           //printf("\n return");
                           // return;
                        }
                        MenuNameID=Temp;
                        printf("MenuNameID=%d \n",MenuNameID);
                        CBottomHalf::BottomMenuPointer = menu1;
                     }

                     POSITION pos = menu1->items.GetHeadPosition();
                     int count =0;

                     CString String1,String2;
                     int NoOFText=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     printf("NoOFText=%d ",NoOFText);
                     int *ID=new int[NoOFText];
                     for(int i=0;i<NoOFText;i++)
                     {
                        ID[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                     }
                     int NoOFChoice=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     printf("NoOFChoice=%d ",NoOFChoice);
                     int *Value=new int[NoOFChoice];
                     for(int j=0;j<NoOFChoice;j++)
                     {
                        Value[j]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     }
                     DisableFlag = false;
                     while(pos)
                     {
                        Object = menu1->items.GetNext(pos);
                        if(Object->GetType() == CVgaMenu::RADIOMENU)
                        {
                           CRadioMenu * ptr= (CRadioMenu *)Object;
                           CString Temptext=ptr->VarText;
                           for(int i=0;i<=(MAXRADIOINDEX-1);i++)
                           {
                              if(i==ID[count])
                              {
                                // printf(" ID[count] = %d \n",ID[count]);
                                 ptr->RadioIndex = ID[count];
                                 ptr->VarText = ptr->RadioMenuStr[i];
                              }

                           }
                           SetDimension(ptr,count);
                           Object->IsDraw=true;
                           count++;
                        }
                        else if(Object->GetType() == CVgaMenu::VGACheck)
                        {
                           CCheck *Checkpointer= (CCheck *)Object;
                           Checkpointer->IsSelected=Value[count];
                           Object->IsDraw=true;
                           count++;

                        }
                        else if(Object->GetType() == CVgaMenu::VARIABLE)
                        {
                           CVgaVariable *ptr=(CVgaVariable *)Object;
                           CString Temp;
                           char TempArray[LINESIZE+1]="                    ";
                           ID[count] = CScreenKeypad::ConvertInternalExternal( ID[count],(CScreenKeypad::FORMAT)ptr->Format);
                           ptr->Insertunitflag=false;
                           CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,Object->GetType());
                           Temp=CScreenKeypad::FormatNumber(ID[count],TempArray,(CScreenKeypad::FORMAT)ptr->Format,false,ptr->Insertunitflag);
                           ptr->IsDraw = (Value[count] != 0);
                           SetDimension(ptr,count);
                           ptr->Variable_Text= " = " +Temp;
                           count++;
                        }
                        else if(Object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                        {

                           CheckConditions(Object);
                           Object->IsDraw = (Value[count] != 0);
                           if(Object->IsDraw)
                           {
                              DisableFlag = true;
                              Object->RectShow=true;
                           }
                           else
                           {
                              DisableFlag = false;
                              Object->RectShow=false;
                           }
                           count++;
                        }
                        else
                        {
                           Object->IsDraw=true;
                        }
                        if(Object->GetType()==CVgaMenu::BottomMenu_Id)
                           Object->IsDraw=false;

                     }

                     delete []ID;
                     if(NoOFChoice>0)
                        delete[]Value;
                     Invalidate();
                  }

                  delete response;
               }

               break;
            }
            else if(type==1)
            {
               KillTimer(BOTTOMHALFTIMER);

               if(CBottomHalf::BottomMenuPointer!=0)
                  menu1=CBottomHalf::BottomMenuPointer;

               int length =2;
               int count =0,Temp1=0;
               unsigned char data1[2];
               union
               {
                  short i;
                  char c[2];
               } u;
               u.i=CBottomHalf::BottomHalfId;
               data1[1]=u.c[0];
               data1[0]=u.c[1];
               unsigned char * data = (unsigned char *) &data1[0];
               CHostCommand * request = new CHostCommand(GetBottomMenuData_FunID, data, length);
               CHostCommand * response = app->SendPollingHostCommand(request);
               if(response)
               {
                  char ch=CHostCommand::AckNak();
                  data = response->GetData();
                  length = response->GetDataLength();
                  if(ch==ACK)
                  {
                     int NoOFVariables=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *val=new int[NoOFVariables];
                     for(int i=0;i<NoOFVariables;i++)
                     {
                        val[i]= CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                     }
                     int NoOfFreqType=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *FreqType=new int[NoOfFreqType];
                     for(int k=0;k<NoOfFreqType;k++)
                     {
                        FreqType[k]= CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     }

                     int NoOFEnable=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     int *Enable=new int[NoOFEnable];
                     for(int j=0;j<NoOFEnable;j++)
                     {
                        Enable[j]= CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                     }

                     pos = menu1->items.GetHeadPosition();
                     while(pos)
                     {
                        Object = menu1->items.GetNext(pos);
                        if(Object->GetType() == CVgaMenu::VARIABLE)
                        {
                           CVgaVariable *ptr=(CVgaVariable *)Object;
                           CString Temp;
                           char TempArray[LINESIZE+1]="                    ";
                           val[count] = CScreenKeypad::ConvertInternalExternal( val[count],(CScreenKeypad::FORMAT)ptr->Format);
                           if(FreqType[count]!=0)
                           {
                              if(FreqType[count]==1)
                                 ptr->text=Str_Parallel;
                              else
                                 ptr->text=Str_Series;

                              CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,Object->GetType());
                              Temp=CScreenKeypad::FormatNumber(val[count],TempArray,(CScreenKeypad::FORMAT)ptr->Format, (ptr->Unitshow != 0),ptr->Insertunitflag);
                              ptr->Variable_Text= " = " +Temp;
                              SetDimension(ptr,count);
                              ptr->IsDraw = (Enable[count] != 0);
                           }
                           else
                              ptr->text="";
                           count++;
                        }
                        else if(Object->GetType() == CVgaMenu::VGA_Button_OBJECT)
                        {
                           Object->IsDraw = (Enable[count] != 0);
                           if(Temp1==0)
                           {
                              if(!Object->IsDraw)
                              {
                                 Object->RectShow=false;
                                 CChildView::BotomHalfRefreshTime=3000;
                              }
                              else
                              {
                                 Object->RectShow=true;
                                 CChildView::BotomHalfRefreshTime=100;
                              }
                              CheckConditions(Object);
                              Temp1++;
                           }
                           CVgaButton *ptr=(CVgaButton *)Object;
                           if(ptr->argument=="1")
                           {
                              CString TempStr=ptr->GetText();
                              if(CChildView::TempCount==0)
                              {
                                 CChildView::ScanString=ptr->GetText();
                                 CChildView::TempCount++;
                              }
                              if(TempStr.Find(_T("..............."),0)!=(-1))
                                 TempStr=CChildView::ScanString;
                              ptr->SetText(TempStr +".");
                           }
                           else if((ptr->argument=="2" && (Object->IsDraw))||
                              (ptr->argument=="3" && (Object->IsDraw)))
                              DisableFlag = false;
                           count++;

                        }
                        else if(Object->GetType()==CVgaMenu::BottomMenu_Id)
                           Object->IsDraw=false;

                     }
                     delete []Enable;
                     delete []val;
                     delete []FreqType;
                     Invalidate();
                  }
                  delete response;
               }
               break;
            }

            break;
         }
         BottomHalfTimerOn=false;
         KillTimer(BOTTOMHALFTIMER);

      }
      break;
   case MessageScreenTimer:
      {
         KillTimer(MessageScreenTimer);
         theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
         page_no=CChildView::thisPtr->menus.RemoveTail();
         theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
         CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
		 /*if(CScreenKeypad::RestoreKeypad())
			 OnKeypadScreen_flag = true;*/
         DisableFlag = false;
         RedrawWindow(  NULL, NULL,  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
      }
      break;

   case PASSWORDTIMER:
      {
         KillTimer(PASSWORDTIMER);
         if(CScreenKeypad::IsPassword_Accepted==1)//password matched,go to desired menu
         {
            page_no=1;
            ModifyObjectList(theApp.MenuPointer);
            theApp.GetSystemVariable();
         }
         else if(CScreenKeypad::IsPassword_Accepted==2) //password mismatched,go to previous menu.
         {
            theApp.menuName=menusname.RemoveTail();
            page_no=menus.RemoveTail();
            theApp.MenuPointer=menupointers.RemoveTail();
            ModifyObjectList(theApp.MenuPointer);
         }
         CScreenKeypad::AlphaBuf[0] = NULL;
         DisableFlag  = false;
         OnKeypadScreen_flag=false;
         RedrawWindow(  NULL, NULL,  RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE );
      }
      break;

   case ERROR_MESSAGE_TIMER:
      {
         KillTimer(ERROR_MESSAGE_TIMER);
         DisableFlag=false;
         Invalidate();
      }
      break;

   case USBSTATUSTIMER1:
      {
         if(USBPresent())
         {
            USBAlarm=false;
            if(!ISUSBPresent)
            {
               ISUSBPresent=true;
               MenuUSBDraw=true;
               USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
               USBPowerGraph.BaseCount= UniversalCount;
               USBColDistance.BaseCount=UniversalCount;
               USBVelocityGraph.BaseCount=UniversalCount;
               USBForceGraph.BaseCount=UniversalCount;
               USBAmplitudeGraph.BaseCount=UniversalCount;
               USBFrequencyGraph.BaseCount=UniversalCount;
               if(!OnKeypadScreen_flag)
               {
                  if(MenuUSBDraw)
                  {
                     ModifyObjectList(theApp.MenuPointer);
                  }
                  Invalidate();
               }
            }
         }
         else
         {
            if(ISUSBPresent)
            {
               ISUSBPresent=false;
               MenuUSBDraw=true;
               if(!OnKeypadScreen_flag)
               {
                  if(MenuUSBDraw)
                     ModifyObjectList(theApp.MenuPointer);
                  if(!creating_pdf)
                     Invalidate();
               }
               SendPollingCommand();
            }
            if((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
               ||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
               ||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
               ||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
               ||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
               ||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
               ||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))
               USBAlarm=true;
            else
               USBAlarm=false;
         }
 		 UsbTimerStatus = true;
      }
      break;
   case USBSTATUSTIMER:
      {
         if(USBPresent())
         {
            USBAlarm=false;
            if(!ISUSBPresent)
            {
               ISUSBPresent=true;
               USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
               USBPowerGraph.BaseCount= UniversalCount;
               USBColDistance.BaseCount=UniversalCount;
               USBVelocityGraph.BaseCount=UniversalCount;
               USBForceGraph.BaseCount=UniversalCount;
               USBAmplitudeGraph.BaseCount=UniversalCount;
               USBFrequencyGraph.BaseCount=UniversalCount;
               if(!OnKeypadScreen_flag)
                  Invalidate();
            }
         }
         else
         {
            if(ISUSBPresent)
            {
               ISUSBPresent=false;
               if(!OnKeypadScreen_flag)
                  Invalidate();
               /*This is done because sometimes the OS does't responds
               (for abt 5 sec's when USB is pulled out. So get new Global
               count before any other action */
               //					SendPollingCommand();
            }

            if((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
               ||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
               ||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
               ||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
               ||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
               ||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
               ||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))
               USBAlarm=true;
            else
               USBAlarm=false;

         }
      }
      break;
   case DIAGNOSTICS_USERIO_TIMER:
      {
         KillTimer(DIAGNOSTICS_USERIO_TIMER);
         ModifyObjectList(theApp.MenuPointer);
         Invalidate();
      }
      break;
   case IDLELOGOUT_TIMER:
      {

		  if((CChildView::Automation == false)&&(CChildView::thisPtr->AuthorityCheckSartUp == true))
		  {
			  if(CChildView::thisPtr->GetStateMachineStatus() == true)
			  {
				  CVgaMenu *menu;
				  KillTimers(IDLELOGOUT_TIMER);
				  if(CChildView::thisPtr->BottomHalfTimerOn)
					  CChildView::thisPtr->KillTimers(BOTTOMHALFTIMER);
				  CChildView::thisPtr->BottomHalfTimerOn=false;
				  CChildView::thisPtr->BottomHalfScreen=false;
				  RunResultScreen = false;//In case we are in runresult screen while idle logout time occurs we need to make sure that we disable the runresult screen flag
				  logOutFun(0);
				  CString MenuName = XSTR(LOGINMENU);
				  if (theApp.menus.Lookup(MenuName, menu))
				  {
					  page_no=1;
					  theApp.menuName = MenuName;
					  theApp.MenuPointer = menu;
					  CChildView::thisPtr->ModifyObjectList(menu);
				  }
				  CChildView::LoginScreenFlag = true;
				  DisableFlag = false;/*in event reason popup we are making it true
				  which disables login button in case of idle logout if event reason
				  popup is already on screen.*/
				  Invalidate();
			  }
			  else if(IdleLogoutTime>0)
			  {
				  InitialiseTimer(IDLELOGOUT_TIMER,IdleLogoutTime);
			  }
		  }
	  }
      break;
   case START_SM_TIMER:
	   {
		   KillTimer(START_SM_TIMER);
		   if((CChildView::thisPtr->AuthorityCheckSartUp==false)||(CChildView::Automation == true))
			   while(!SendCommandForStateMachineEnable(STATE_MACH_ON));
	   }
	   break;
	case MOUSE_DETECT_TIMER:
	   {
		   MouseDetect(false);
	   }
	   break;
   }
}

/*********************************************************/
/*	This Function is to initialise different timers.     */
/*********************************************************/
UINT_PTR CChildView::InitialiseTimer(int TimerID,int Time)
{

   if(TimerID == ALPHAENTRYTIMER)
   {
      IsTwoSecExpired=false;
      return thisPtr->SetTimer(ALPHAENTRYTIMER,Time,NULL);
   }
   else if(TimerID == Pollingtimer)
      return	thisPtr->SetTimer(Pollingtimer,Time,NULL);
   else if(TimerID == BOTTOMHALFTIMER)
      return	thisPtr->SetTimer(BOTTOMHALFTIMER,Time,NULL);
   else if(TimerID == MessageScreenTimer)
      return	thisPtr->SetTimer(MessageScreenTimer,Time,NULL);
   else if(TimerID == PASSWORDTIMER)
      return	thisPtr->SetTimer(PASSWORDTIMER,Time,NULL);
   else if(TimerID == ERROR_MESSAGE_TIMER)
      return thisPtr->SetTimer(ERROR_MESSAGE_TIMER,Time,NULL);
   else if(TimerID == USBSTATUSTIMER)
      return	thisPtr->SetTimer(USBSTATUSTIMER,Time,NULL);
   else if(TimerID == GETPRINTINGPARAMTIMER)
      return	thisPtr->SetTimer(GETPRINTINGPARAMTIMER,Time,NULL);
   else if(TimerID == LanguageSelectionTimer)
      return	thisPtr->SetTimer(LanguageSelectionTimer,Time,NULL);
   else if(TimerID == USBSTATUSTIMER1)
      return	thisPtr->SetTimer(USBSTATUSTIMER1,Time,NULL);
   else if(TimerID == DIAGNOSTICS_USERIO_TIMER)
      return  thisPtr->SetTimer(DIAGNOSTICS_USERIO_TIMER,Time,NULL);
   else if(TimerID == IDLELOGOUT_TIMER)
      return  thisPtr->SetTimer(IDLELOGOUT_TIMER,Time,NULL);
   else if(TimerID == START_SM_TIMER)
	  return  thisPtr->SetTimer(START_SM_TIMER,Time,NULL);
   else if(TimerID == MOUSE_DETECT_TIMER)
	  return  thisPtr->SetTimer(MOUSE_DETECT_TIMER,Time,NULL);
   return 0;
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
   bool Done = false;
   CDC*pDC = GetDC();
   if(OnKeypadScreen_flag)
   {
      if(!DisableFlag)
      {
         CScreenKeypad *object=keypadList.GetTail();
         Done =object->ProcessKeypadfromKeyboard( nChar,CChildView::thisPtr,pDC);
         if (Done)Invalidate();
		 ReleaseDC(pDC);
         return;
      }
   }
   else if(CChildView::ControlLevel >= LEVEL_C)
   {
      Done = CScreenKeypad::ProcessBarcodeSCAN( nChar,CChildView::thisPtr,pDC);
   }
   ReleaseDC(pDC);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CWnd::OnCreate(lpCreateStruct) == -1)
      return -1;
   InitialiseTimer(Pollingtimer,POLLINGTIME);
   InitialiseTimer(START_SM_TIMER,START_SM_TIME);
   return 0;
}

/************************************************/
/*	Function to kill Timer of particular ID		*/
/************************************************/
void CChildView::KillTimers(int TimerID)
{
   thisPtr->KillTimer(TimerID);

}

/****************************************************/
/*			Function to Calibrate Screen Points.	*/
/****************************************************/
CPoint CChildView::CalibratePoint(CPoint p)
{
   if((RAMCalibCordinate_Xa==0 )&&(RAMCalibCordinate_Ya==0))
      return p;
   CPoint RetCordValue = p;
   float FinalCord, TempVal;
   float DX1 = CVgaScreenSetup::DX1;
   float DY1 = CVgaScreenSetup::DY1;
   /*Calculation for the x- Coordinate:*/
   TempVal = ((float) ActualCalibCordinate_Xa +
      DX1*(p.x - RAMCalibCordinate_Xa));
   if(TempVal < 0)
      FinalCord = 0;
   else if(TempVal > MAX_VGA_X_VALUE)
      FinalCord = MAX_VGA_X_VALUE;
   else
      FinalCord = TempVal;
   RetCordValue.x = (int) FinalCord;

   /*Calculation for the y- Coordinate:*/
   TempVal = ((float) ActualCalibCordinate_Ya +
      DY1*(p.y - RAMCalibCordinate_Ya));
   if(TempVal < 0)
      FinalCord = 0;
   else if(TempVal > MAX_VGA_Y_VALUE)
      FinalCord = MAX_VGA_Y_VALUE;
   else
      FinalCord = TempVal;
   RetCordValue.y= (int)TempVal;
   return RetCordValue;
   /* code for screen setup ends */
}

/****************************************************************/
/*	Function to Get color setup and Calibrate point at powerup.	*/
/****************************************************************/
void CChildView::GetRAMData()
{
   CFile f;
   CFileException e;
   TCHAR* pFileName;
#ifndef _WIN32_WCE
   pFileName = _T("C:\\Branson\\SystemConfig.cfg");
#else
   pFileName = _T("Disk\\SystemConfig.cfg");
#endif

   if( !f.Open( pFileName, CFile::modeRead , &e ) )
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
	  AfxMessageBox(_T("SystemConfig.cfg is file is missing from \"C:\\Branson\"  folder"));
	  theApp.ExitInstance();
	  exit(0);
   }
   else
   {
      char Comma =',';
      int Temprorylen=0;
      int FileSize = (int)f.GetLength();
      int SysFileSize=FileSize;
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);
      unsigned char * data1 = data;
	  bool FileFormatOk = false;
      if(FileSize >2)
      {

         Sys_FileSize=*data1++;FileSize--;
         char temp=' ';
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < MAXEXESIZE))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentExecutable[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;

         }
		 if(!FileFormatOk || (Temprorylen < (int)strlen("2000Xc.exe")))
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         CurrentExecutable[Temprorylen]='\0';

         temp=' ';Temprorylen=0;FileFormatOk=false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < MAXLANGNAME))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentLanguageName[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk || (Temprorylen < (int)strlen(".lan")))
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         CurrentLanguageName[Temprorylen]='\0';

         temp=' ';Temprorylen=0;FileFormatOk=false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < MAXSECURITYSIZE))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               SecurityFile[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }

		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         SecurityFile[Temprorylen]='\0';
		 FileFormatOk = false;
         if(FileSize>=1)
         {
			unsigned char c = *data1++;
            PasswordRequired = (c != 0);
            data1++;
			FileFormatOk = true;
         }
         FileSize--;
         FileSize--;

		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < MAXPASSSIZE))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               CurrentPassword[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         CurrentPassword[Temprorylen]='\0';
         char TempString[20];
         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }

		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         TextColor=atoi(TempString);
         if((TextColor<1)||(TextColor>11))
         {
            TextColor=Black;
         }

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
         TempString[Temprorylen]='\0';
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         Button_Color=atoi(TempString);
         if((Button_Color<1)||(Button_Color>11))
         {
            Button_Color=Gray;
         }

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         TitleBarColor=atoi(TempString);
         if((TitleBarColor<1)||(TitleBarColor>11))
         {
            TitleBarColor=Blue;
         }

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         Back_Color=atoi(TempString);
         if((Back_Color<1)||(Back_Color>11))
         {
            Back_Color=White;
         }

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
         TempString[Temprorylen]='\0';
         Highlight_Color=atoi(TempString);
         if((Highlight_Color<1)||(Highlight_Color>11))
         {
            Highlight_Color=Green;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         CVgaScreenSetup::DX1 = (float)atof(TempString);

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         CVgaScreenSetup::DY1 = (float)atof(TempString);

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         RAMCalibCordinate_Xa=atoi(TempString);

         temp=' ';Temprorylen=0;FileFormatOk = false;
         while((temp!=',')&&(FileSize>=1)&&(Temprorylen < sizeof(TempString)))
         {
            temp=*data1++;FileSize--;
            if(temp!=',')
            {
               TempString[Temprorylen]=temp;
               Temprorylen++;
            }
			else
				FileFormatOk = true;
         }
		 if(!FileFormatOk)
		 {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
		 }
         TempString[Temprorylen]='\0';
         RAMCalibCordinate_Ya=atoi(TempString);
		 delete []data;
      }
	  else
	  {
		   delete []data;
		   f.Close();
		   AfxMessageBox(_T("Incorrect SystemConfig.cfg file"));
		   theApp.ExitInstance();
		   exit(0);
	  }
      f.Close();

   }

}

/**********************************************************************************/
/*Function to Store colorsetup and Screen Calibration information on Flash memory.*/
/**********************************************************************************/
void CChildView::SaveData()
{

   CFile f;
   CFileException e;
   TCHAR* pFileName;
#ifndef _WIN32_WCE
   pFileName = _T("C:\\Branson\\SystemConfig.cfg");
#else
   pFileName = _T("Disk\\SystemConfig.cfg");
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
      char Comma =',';
      f.SeekToBegin();
      int length=0;
      f.Write (&Sys_FileSize,sizeof(char));
      while(CurrentExecutable[length]!='\0')
      {
         length++;
      }
      f.Write(&CurrentExecutable,length);
      f.Write(&Comma,sizeof(char));

      length=0;
      while(CurrentLanguageName[length]!='\0')
      {
         length++;
      }
      f.Write(&CurrentLanguageName,length);
      f.Write(&Comma,sizeof(char));

      length=0;
      while(SecurityFile[length]!='\0')
      {
         length++;
      }
      f.Write(&SecurityFile,length);
      f.Write(&Comma,sizeof(char));

      f.Write(&PasswordRequired,sizeof(bool));
      f.Write(&Comma,sizeof(char));

      length=0;
      while(CurrentPassword[length]!='\0')
      {
         length++;
      }
      f.Write(&CurrentPassword,length);
      f.Write(&Comma,sizeof(char));

      char buffer[20];
      _itoa(TextColor, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(Button_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(TitleBarColor, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(Back_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(Highlight_Color, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      sprintf(buffer,"%f",CVgaScreenSetup::DX1);
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      sprintf(buffer,"%f",CVgaScreenSetup::DY1);
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(RAMCalibCordinate_Xa, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);

      f.Write(&Comma,sizeof(char));

      _itoa(RAMCalibCordinate_Ya, buffer, 10 );
      length=0;
      while(buffer[length]!='\0')
      {
         length++;
      }
      f.Write(&buffer,length);
      f.Write(&Comma,sizeof(char));

      f.Close();
   }
}

/*****************************************************************************/
/*    Function To send Polling Command at every 200 miliseconds.			 */
/*****************************************************************************/
void CChildView::SendPollingCommand()
{
   if(!HornScanPlzWait)
   {
      int PollingData =0;

      if(CChildView::ScreenSetupFlag)
         PollingData = SCREENSETUP_POLL_BIT;

      if(CChildView::DiagIOScreen == true)
      {
         PollingData |= DIAG_IO_POLL_BIT;
      }

      int length = 1;//length of pointer to be send to 332.
      unsigned char * data = (unsigned char *) &PollingData;
      CCommPort::OnPollingTime=true;
      CHostCommand * request = new CHostCommand(GetPollingData_FunResponse, data,length);
      CHostCommand * response = app->SendPollingHostCommand(request);
      if (response)
      {
         char ch=CHostCommand::AckNak();
         data = response->GetData();//Getting Data.
         length = response->GetDataLength();//Getting Length.
         if((ch==ACK)&&(length == POLLING_DATA_RESPONSE_LEN))
            AnalyzePollingResponse(data,length);
         else
            InitialiseTimer(Pollingtimer,POLLINGTIME);
         delete response;
      }
      else
      {
         InitialiseTimer(Pollingtimer,POLLINGTIME);
      }

      int Alarms=0;

      if(USBAlarm)
      {
         if(((!USBWelddata.USBSampleDisable)         ||   (USBWelddata.USBOnAlarmValue)
            ||(!USBPowerGraph.USBSampleDisable)    ||   (USBPowerGraph.USBOnAlarmValue)
            ||(!USBColDistance.USBSampleDisable)   ||   (USBColDistance.USBOnAlarmValue)
            ||(!USBVelocityGraph.USBSampleDisable) ||   (USBVelocityGraph.USBOnAlarmValue)
            ||(!USBForceGraph.USBSampleDisable)    ||   (USBForceGraph.USBOnAlarmValue)
            ||(!USBAmplitudeGraph.USBSampleDisable)||	(USBAmplitudeGraph.USBOnAlarmValue)
            ||(!USBFrequencyGraph.USBSampleDisable)||	(USBFrequencyGraph.USBOnAlarmValue))&&(USBGlobalFlag))
            USBAlarm=true;
         else
            USBAlarm=false;
         if(USBAlarm)
            Alarms +=USBOFFLINEALARM;
      }
      if((CWeldingHistory::WeldSpaceFullFlag == true) || (CEventLog::EventHistoryFullFlag == true))
         Alarms+=HISTORYVALIDATIONFAILEDALARM;
      if(USBMemoryFull)
         Alarms +=USBFULLALARM;
      if(SBCDiskFull)
         Alarms +=SBCDISKFULLALARM;
      if(USBMemoryNearlyFull)
      {
         Alarms +=USBNEARLYFULLALARM;
         USBMemoryNearlyFull = FALSE;
      }
      if(DISKMemoryNearlyFull)
      {
         Alarms +=DISKMEMORYNEARLYFULLALARM;
         DISKMemoryNearlyFull = FALSE;
      }
      if(Alarms!=0)
         SendCommandAlarms(Alarms);
   }
   else
      InitialiseTimer(Pollingtimer,POLLINGTIME);
}


/*****************************************************************************/
/*	Function To analyze polling response and to take necessary step          */
/*  according to the response.												 */
/*****************************************************************************/
void CChildView::AnalyzePollingResponse(unsigned char *&data, int &length)
{
   char TempArray[10];
   static bool PresetStatusUpdated = false;
   int TempWeldCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
   int TempUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
   int TempPresetNum = (((UINT16)*data) << 8) | (*(data + 1));
   length-=2;
   data += 2;
   int TempAlarmCount = CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
   TemporaryAlarmCount=TempAlarmCount;
   length -=3;
   StartWeldData =*data++;
   int TempResponseType=*data++;
   static UINT8 EstopPressed = 0;
   length--;
   bool ConditionVariableRequired=false;
   if((TempResponseType & 0x80))
      DisplayLockFlag=true;
   else
      DisplayLockFlag=false;
   static int ReplyCnt = 0;
   ReplyCnt++;
   static int TempResponseType1	 = 0;
   if(TempResponseType1 != TempResponseType)
   {
	   TempResponseType1 = TempResponseType;
	   printf("\n --%08X %d--", TempResponseType, ReplyCnt);
   }

   if((TempResponseType & GET_SYSTEM_VAR))
      ConditionVariableRequired=true;
   else
      ConditionVariableRequired=false;
   int ResponseType = TempResponseType & 0x3F;
   int Pointer=(CVgaMenuItem::Convert_Char_To_Integer(data,length,1));
   int TempEventGlobalCount = (CVgaMenuItem::Convert_Char_To_Integer(data,length,0));
   int TempSetBatchCount = (CVgaMenuItem::Convert_Char_To_Integer(data,length,0));
   int TempBatchCount = (CVgaMenuItem::Convert_Char_To_Integer(data,length,0));
   UdiStatus = (UDISCANSTATUS)(CVgaMenuItem::Convert_Char_To_Integer(data,length,0));

   if((PresentWeldCount != TempUniversalCount) ||  (PresentAlarmCount != TempAlarmCount))
   {
      if(CChildView::LoginScreenFlag == false)
      {
         //weld count changed so reset idle timer
         if(IdleLogoutTime>0)
            CChildView::InitialiseTimer(IDLELOGOUT_TIMER,IdleLogoutTime);
      }
   }
   PresentAlarmCount=TempAlarmCount;
   PresentWeldCount=TempUniversalCount;
   PresentPresetNum=TempPresetNum;

   if(powerup)
   {
	  if((CEventLog::EventHistoryRamCount == 0)||(CEventLog::EventHistoryRamCount >TempEventGlobalCount))
        CEventLog::EventHistoryRamCount = CEventLog::EventHistoryUniversalCount = TempEventGlobalCount;
	  if((UniversalCount == 0)&&(TempUniversalCount<=MAX_WELDDATA_REQUEST_COUNT)){}
	  else if(( UniversalCount == 0)||(UniversalCount>TempUniversalCount))
      	UniversalCount = UniversalCountWeldHiddenFile = TempUniversalCount;
	  else if(TempUniversalCount - UniversalCount > MAX_WELDDATA_REQUEST_COUNT)
		  UniversalCountWeldHiddenFile = TempUniversalCount - MAX_WELDDATA_REQUEST_COUNT;
      WeldCycleCount = TempWeldCount;
      PresetNum = TempPresetNum;
      AlarmCount =0;
      powerup=false;
      InitialiseTimer(USBSTATUSTIMER1,USBSTATUSTIME);
      while(GetPrintingParameters(true));
      GetPowerSupplyName();
      LastUSBPresetFolder=USBDISK + PowerSupply+"\\Presets";
      PowerUpSBC=true;
   }

   if(ConditionVariableRequired)
   {
      ConditionVariableRequired=false;
      theApp.GetSystemVariable();
      GetPowerSupplyName();
   }

   //if Estop was pressed
   if(((EstopPressed & 0x3) == WASESTOPPRESSED) && (ResponseType == NONE))
	   ResponseType = ESTOP_RESET;
   switch(ResponseType)
   {
   case NONE:
      {
         if(Pointer == 0)
            break;
         else
         {
            break;
         }
      }
      break;

   case TESTKEYPRESSED:
      {
         CChildView::RunResultScreen=false;
         CBottomHalf::HornDownScreenPresent=true;
         ScreenSetupFlag=false;
         OnKeypadScreen_flag=false;
         DisableFlag=false;
         CVgaDrawGraph::GraphCount=0;

         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();

         CWnd *pWndPrev;
         CVgaMenu * menu;
         // Determine if a window with the class name exists...

         if (pWndPrev = CWnd::FindWindow(NULL,_T("2000Xc")))
            pWndPrev->SetForegroundWindow();

         CString submenu=theApp.SpecialMenu[ResponseType];

         if (theApp.menus.Lookup(submenu, menu))
         {
            page_no=1;
            ModifyObjectList(menu);
            theApp.menuName = submenu;
            theApp.MenuPointer=menu;
         }

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
         Invalidate();
      }
      break;

   case ESTOP_PRESSED_CONT:
      printf("estop cont");
   case ESTOP_PRESSED_FIRST:
      PollingTimeOnMsgScrn=true;
   case ESTOP_OFF:
      {
		 EstopPressedFlag = true;
         EstopPressed = EstopPressed|CURRTRUE;
         //printf("EstopPressed= %d #1\n",EstopPressed);
         if((EstopPressed & 0x3) == CURRTRUE)
         {
            newMenuName = theApp.menuName;
            EstopPressed |= PREVTRUE;
 		    CChildView::RunResultScreen = false;
            printf("EstopPressed= %d newMenuName=%S #2\n",EstopPressed,newMenuName);
         }
         //printf("case 7 appmenuname=%S menuname=%S EstopPressed=%d \n",theApp.menuName,newMenuName,EstopPressed);
         ScreenSetupFlag=false;
         OnKeypadScreen_flag=false;
         DisableFlag=true;
         CWnd *pWndPrev;
         CVgaMenu * menu;
         // Determine if a window with the class name exists...
         if (pWndPrev = CWnd::FindWindow(NULL,_T("2000Xc")))
            pWndPrev->SetForegroundWindow();
         CString submenu=theApp.SpecialMenu[ResponseType];
         if (theApp.menus.Lookup(submenu, menu))
         {
            page_no=1;
            ModifyObjectList(menu);
            theApp.menuName = submenu;
            theApp.MenuPointer=menu;
         }
         Invalidate();

      }
      break;
   case MSG_SCREEN://Show Message screen
      {
         CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
            if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
            {
               CMsgScreen *ptr=(CMsgScreen *)object;
               if(ptr->submenu!="")
               {
                  if (theApp.menus.Lookup(ptr->submenu, menu))
                  {
                     page_no=1;
                     theApp.menuName = ptr->submenu;
                     theApp.MenuPointer=menu;
                     ModifyObjectList(menu);
                  }
               }
            }
            else
            {
               DisableFlag=false;
            }
            Invalidate();
         }
      }
      break;
   case MSG_NAK_SCREEN://Show Message screen nak screen
      {

         CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
            if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
            {
               CMsgScreen *ptr=(CMsgScreen *)object;
               if(ptr->menunak!="")
               {
                  if (theApp.menus.Lookup(ptr->menunak, menu))
                  {
                     page_no=1;
                     theApp.menuName = ptr->menunak;
                     theApp.MenuPointer=menu;
                     ModifyObjectList(menu);
                  }
               }
               Invalidate();
            }
         }

      }
      break;
   case CALIB_START_FLAG_ON:
      {
         CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
         int ActTyp=0;
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
            if((object->GetType() == CVgaMenu::VGA_Button_OBJECT))
            {
               if(Pointer==ActTyp)
               {
                  CVgaButton *ptr=(CVgaButton *)object;
                  if(ptr->MenuName!="")
                  {
                     if (theApp.menus.Lookup(ptr->MenuName, menu))
                     {
                        page_no=1;
                        ModifyObjectList(menu);
                        theApp.menuName = ptr->MenuName;
                        theApp.MenuPointer=menu;
                     }
                  }
               }
               ActTyp++;
            }
            else
            {
               DisableFlag=false;
            }
            Invalidate();
         }
      }
      break;
   case CALIB_START_FLAG_OFF:
      {
         CVgaMenu * menu;
         menu=theApp.MenuPointer;
         CVgaMenuItem * object=menu->items.GetHead();
         int ActTyp=0;
         POSITION pos = menu->items.GetHeadPosition();
         while(pos)
         {
            object = menu->items.GetNext(pos);
            if(object->GetType() == CVgaMenu::VGA_Button_OBJECT)
            {
               if(Pointer==ActTyp)
               {
                  CVgaButton *ptr=(CVgaButton *)object;
                  if(ptr->MenuNak!="")
                  {
                     if (theApp.menus.Lookup(ptr->MenuNak, menu))
                     {
                        page_no=1;
                        ModifyObjectList(menu);
                        theApp.menuName = ptr->MenuNak;
                        theApp.MenuPointer=menu;
                     }
                  }
               }
               ActTyp++;
               Invalidate();
            }
         }
      }
      break;
   case ESTOP_RESET://Show Main Menu screen
      {
         printf("Childview.cpp Main menu");
         CBottomHalf::HornDownScreenPresent=false;
         DisableFlag=false;
         CVgaDrawGraph::GraphCount=0;
         while(theApp.GraphsDataList.GetCount()>0)
            theApp.GraphsDataList.RemoveHead();
         OnKeypadScreen_flag=false;
         PollingTimeOnMsgScrn=false;
         menusname.RemoveAll();
         menus.RemoveAll();
         menupointers.RemoveAll();
         theApp.GetSystemVariable();
         CVgaMenu * menu;
         CVgaBottomMenu::SendCommandForBottomMenu(CVgaBottomMenu::mainMenuCommandID,(int)this);
         printf("appmenuname=%S menuname=%S \n",theApp.menuName,newMenuName);
         if((newMenuName != XSTR(LOGINMENU)) && (newMenuName != XSTR(CHANGEPASSWORDMENU)))//CChildView::LoginScreenFlag == false )
            newMenuName = CVgaBottomMenu::mainMenuID;

         if (theApp.menus.Lookup(newMenuName, menu))
         {
            AccessLevelSystem=USER_OPERATOR;
            menusname.AddTail(theApp.menuName);
            menus.AddTail(page_no);
            menupointers.AddTail(theApp.MenuPointer);
            page_no=1;
            ModifyObjectList(menu);
            theApp.menuName= newMenuName;
            theApp.MenuPointer=menu;
            EstopPressed = 0;
            newMenuName = "0";
            Invalidate();
         }
		 //printing is aborted and estop reset login screen is not required
		 if(PrintingAbortedOnEstop && !(Pointer == ESTOP_LOGIN_NEXT))
		 {
			 PrintingAbortedOnEstop = false;
			 EnableStateMachine(0);
		 }

      }
      break;
   case CUR_PRESET_PARAM_CHANGED:
      {
         if(Pointer == 0)
         {
            ModifyObjectList(theApp.MenuPointer);
            Invalidate();
         }
      }
      break;
   case CLAMP_ALARM:
      {

         printf("ClamponAlarm");
         CVgaMenu * menu;
         CString submenu=theApp.SpecialMenu[ResponseType];
         if((theApp.menuName != submenu)&&(theApp.menuName != XSTR(LOGINMENU) ))
         {
            if (theApp.menus.Lookup(submenu, menu))
            {
               page_no=1;
               ModifyObjectList(menu);
               theApp.menuName = submenu;
               theApp.MenuPointer=menu;
            }
            Invalidate();
         }
      }
      break;
   case EVENT_REASON_FLAG:
      {
         //printf("reason for change");
         CVgaMenu * menu;
         CString submenu=theApp.SpecialMenu[ResponseType];
         if((theApp.menuName != submenu)&&(theApp.menuName != XSTR(LOGINMENU) ))
         {
            //save the current menu pointer and page number
            EventChangeMenuName = theApp.menuName;
            SavedPgNum = page_no;
            if (theApp.menus.Lookup(submenu, menu))
            {
               menusname.AddTail(theApp.menuName);
               menus.AddTail(page_no);
               menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               ModifyObjectList(menu);
               theApp.menuName = submenu;
               theApp.MenuPointer=menu;
            }
            Invalidate();
         }
      }
      break;
   case DOWNSPEED_NEW_FLAG :
      {
         CVgaMenu * menu;
         CString submenu=theApp.SpecialMenu[ResponseType];
         if((theApp.menuName != submenu)&&(theApp.menuName != XSTR(LOGINMENU) ))
         {
            printf("DOWNSPEED_NEW_FLAG \n");
            //save the current menu pointer and page number
            DownspeedMenuName = theApp.menuName;
            if (theApp.menus.Lookup(submenu, menu))
            {
               menusname.AddTail(theApp.menuName);
               menus.AddTail(page_no);
               menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               theApp.menuName = submenu;
               theApp.MenuPointer=menu;
               ModifyObjectList(menu);
            }
            Invalidate();
         }
      }
      break;
   case ESTORESET_LOGIN :
	  {
		 CVgaMenu * menu;
         CString submenu=theApp.SpecialMenu[ResponseType];
         if((theApp.menuName != submenu)&&(theApp.menuName != XSTR(LOGINMENU) ))
         {
            printf("ESTORESET_LOGIN \n");
            //save the current menu pointer and page number
            DownspeedMenuName = theApp.menuName;
            if (theApp.menus.Lookup(submenu, menu))
            {
               menusname.AddTail(theApp.menuName);
               menus.AddTail(page_no);
               menupointers.AddTail(theApp.MenuPointer);
               page_no=1;
               theApp.menuName = submenu;
               theApp.MenuPointer=menu;
               ModifyObjectList(menu);
            }
            Invalidate();
         }
		 PrintingAbortedOnEstop = false;
	  }
	  break;
   case DOWNSPEEDFLAG:
	   {
         CVgaMenu * menu;
		 CString submenu=theApp.SpecialMenu[ResponseType];
		 if(theApp.menuName != submenu)
		 {
			if (theApp.menus.Lookup(submenu, menu))
			{
				menusname.AddTail(theApp.menuName);
				menus.AddTail(page_no);
				menupointers.AddTail(theApp.MenuPointer);
				page_no=1;
				theApp.menuName = submenu;
				theApp.MenuPointer=menu;
				ModifyObjectList(menu);
			}
			Invalidate();
		 }
	   }
      break;
   case DOWNSPEEDFLAG_MSG:
	   {
		   CVgaMenu * menu;
		   menu = menupointers.RemoveTail();
		   page_no = menus.RemoveTail();
		   ModifyObjectList(menu);
		   theApp.menuName = menusname.RemoveTail();
		   theApp.MenuPointer = menu;
		   printf("\n page_no dsdone %d ", page_no);
	   }
	   DisableFlag = false;
	   Invalidate();
	   break;
   case DOWNSPEED_NEW_HD_FLAG :
	   {
		   CVgaMenu * menu;
		   CString submenu=theApp.SpecialMenu[ResponseType];
		   if((theApp.menuName != submenu)&&(theApp.menuName != XSTR(LOGINMENU) ))
		   {
			   printf("DOWNSPEED_NEW_HD_FLAG \n");
			   //save the current menu pointer and page number
			   DownspeedMenuName = theApp.menuName;
			   if (theApp.menus.Lookup(submenu, menu))
			   {
				   menusname.AddTail(theApp.menuName);
				   menus.AddTail(page_no);
				   menupointers.AddTail(theApp.MenuPointer);
				   page_no=1;
				   theApp.menuName = submenu;
				   theApp.MenuPointer=menu;
				   ModifyObjectList(menu);
			   }
			   Invalidate();
		   }
	   }
	   break;
   default:
	   break;
   }

   /*Check for Current Screen i.e RunScreen or Graph Screen.*/
   bool GraphScreen = false;

   if(theApp.GraphsDataList.GetCount()>0)
      GraphScreen=true;


   if(TempPresetNum !=PresetNum)
   {
      PresetStatusUpdated = false;
      if(!ExtPreset)
      {
         if(GetPrintingParameters(true) == false)
            PresetStatusUpdated = true;

      }
      else
         while(GetPrintingParameters(false));
   }

   if((GraphScreen && AutoRefreshon)&&(!CChildView::PMCScreen)&&(TempUniversalCount!=UniversalCount)) // In case of sequencing ,also check count change
   {
      int temp =0;
      POSITION pos = theApp.GraphsDataList.GetHeadPosition();
      bool GraphScrn=true;
      while(pos)
      {
         CVgaDrawGraph *obj =theApp.GraphsDataList.GetNext(pos);
         if(obj->GraphData.graph_type == NO_VALID_GRAPH)
         {
            GraphScrn=false;
            page_no=1;
            GraphOneRequestValue=2;
            while(theApp.GraphsDataList.GetCount()>0)
               theApp.GraphsDataList.RemoveHead();
            ModifyObjectList(theApp.MenuPointer);
            Invalidate();
            break;
         }
         temp +=obj->GraphData.GraphRequestValue;

      }
      if(GraphScrn)
      {
         GetGraphData(temp);
         Invalidate();
      }

   }
   if((GraphScreen && CChildView::PMCScreen)&&(TempUniversalCount!=UniversalCount)) // In case of sequencing ,also check count change
   {
      page_no=1;
      while(theApp.GraphsDataList.GetCount()>0)
         theApp.GraphsDataList.RemoveHead();
      CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
      Invalidate();
   }
   if((TempPresetNum !=PresetNum) && RunResultScreen)
   {
      //Send host command to get the Weld State data.
      theApp.GetSystemVariable();
      int length1 = 0;//length of pointer to be send to 332.
      CCommPort::OnPollingTime=false;
      CVgaMenu * menu;
      menu=theApp.MenuPointer;
      CHostCommand * request = new CHostCommand(GetWeldStateStrings_FunId, 0, 0);
      CHostCommand * response = app->SendPollingHostCommand(request);
      if (response)
      {
         char ch=CHostCommand::AckNak();
         unsigned char *data2 = response->GetData();//Getting Data.
         length1 = response->GetDataLength();//Getting Length.
         if(ch==ACK)//If Ack.
         {
            if(length1>0)
            {
               CDC *pDC=GetDC();
			   CVgaMenuItem::DrawRect(pDC, Back_Color,CRect(30,50,620,75));
               ReleaseDC(pDC);
               CString String = CVgaMenuItem::GetString(data2, length1);
               int PresetNumber=CVgaMenuItem::Convert_Char_To_Integer(data2,length1,2);
               CString Temprory=_itoa(PresetNumber,TempArray,10);
               CString PresentPresetString =CVgaMenuItem::GetString(data2, length1);
               POSITION pos1=menu->items.GetHeadPosition();
               int Temp =0;
               while (pos1)
               {
                  CVgaMenuItem *object= menu->items.GetNext(pos1);
                  int type = object->GetType();
                  if(TempPresetNum !=PresetNum)
                  {
                     if((type == CVgaMenu::VGA_Button_OBJECT)&&(Temp==0))//CScreenObject::VGATEXT)
                     {
                        PresetNum=	TempPresetNum;
                        CVgaButton *ptr=(CVgaButton *)object;
                        ptr->SubText="";
                        ptr->SubText=Temprory;
                        CDC *pDC=GetDC();
                        object->Draw(pDC);
                        Temp++;
                        ReleaseDC(pDC);
                        object= menu->items.GetNext(pos1);
                        type = object->GetType();
                     }

                     if((type == CVgaMenu::VGA_Button_OBJECT)&&(Temp==1))//CScreenObject::VGA_WELDSTATE)
                     {
                        CVgaButton *ptr=(CVgaButton *)object;
                        PresentPresetString.TrimLeft();
                        PresentPresetString.TrimRight();
                        ptr->SubText="";
                        ptr->SubText=PresentPresetString;
                        CDC *pDC=GetDC();
                        object->Draw(pDC);
                        Temp++;
                        ReleaseDC(pDC);
                        object= menu->items.GetNext(pos1);
                        type = object->GetType();
                     }
                     if((type == CVgaMenu::VGA_Button_OBJECT))
                     {
                        while((object->ModeSet!=CChildView::WeldMode) && (type == CVgaMenu::VGA_Button_OBJECT) && pos1)
                        {
                           object= menu->items.GetNext(pos1);
                           type = object->GetType();
                        }
                        if(type == CVgaMenu::VGA_Button_OBJECT)
                        {
                           CVgaButton *ptr=(CVgaButton *)object;
                           ptr->SubText="";
                           ptr->SubText=String;
                           CDC *pDC=GetDC();
                           object->Draw(pDC);
                           Temp++;
                           ReleaseDC(pDC);
                        }
                     }
                  }
               }
            }

         }
         delete response;
      }
   }

   if( CChildView::ControlLevel >= LEVEL_C)
   {
	   if(((TempBatchCount != BatchCount) || (WasRunResultScreen != RunResultScreen)) && RunResultScreen)
	   {
		   CString Temp1= _itoa(TempBatchCount,TempArray,10);
		   CString Temp2 = _itoa(TempSetBatchCount,TempArray,10);
		   CString BatchDrawText = Temp1 + "/" + Temp2;
		   if(Temp2 == "0")//batch count disabled
			   BatchDrawText = "";//do not display anything
		   CVgaMenu * menu = theApp.MenuPointer;
		   POSITION pos1= menu->items.GetHeadPosition();
		   CDC *pDC=GetDC();
		   CVgaMenuItem::DrawRect(pDC, Back_Color,CRect(30,70,370,100));
		   ReleaseDC(pDC);
		   int Temp = 0;
		   while (pos1)
		   {
			   CVgaMenuItem *object= menu->items.GetNext(pos1);
			   int type = object->GetType();
			   if((type == CVgaMenu::VGA_Button_OBJECT) && (Temp == BATCH_COUNT_BUTTON_POSITION))
			   {
				   CVgaButton *ptr=(CVgaButton *)object;
				   ptr->SubText =  BatchDrawText;
				   if( BatchDrawText == "")
					   ptr->text= "";
				   else
					   ptr->text = BatchCountText;
				   CDC *pDC=GetDC();
				   object->Draw(pDC);
				   ReleaseDC(pDC);
			   }
			   Temp++;
		   }
		   BatchCount = TempBatchCount;
	   }
      if(WasRunResultScreen != RunResultScreen)
      {
         WasRunResultScreen = RunResultScreen;
         if(!WasRunResultScreen)
            PrevUDIStatus = UDISCAN_OFF;
         if(RunResultScreen && (UdiStatus == UDISCAN_WAITING))
            MaxDigitsUdiScan = 0;
      }
      CString UDIDrawText;
      if(((PrevUDIStatus != UdiStatus) || (TempUniversalCount!=UniversalCount)) && RunResultScreen)
      {
         bool UpdateUdiText = true;
         switch(UdiStatus)
         {
         case UDISCAN_WAITING:
            UDIDrawText = WaitForUDIScan;
            break;
         case UDISCAN_OFF:
         default:
            UDIDrawText = "";
			if(PrevUDIStatus == UDISCAN_OFF)
				GlobalScanString = "";
            break;
         case UDISCAN_RECEIVED:
            UpdateUdiText = false;
            break;
         };

         if(UpdateUdiText)
         {
            CVgaMenu * menu = theApp.MenuPointer;
            POSITION pos1= menu->items.GetHeadPosition();
            CDC *pDC=GetDC();
            CVgaMenuItem::DrawRect(pDC, Back_Color,CRect(10,395,370,425));
            ReleaseDC(pDC);
            int Temp = 0;
            while (pos1)
            {
               CVgaMenuItem *object= menu->items.GetNext(pos1);
               int type = object->GetType();
               if((type == CVgaMenu::VGA_Button_OBJECT) && (Temp == BARCODE_BUTTON_POSITION))
               {
                  CVgaButton *ptr=(CVgaButton *)object;
                  ptr->text =  UDIDrawText;
                  CDC *pDC=GetDC();
                  object->Draw(pDC);
                  ReleaseDC(pDC);
               }
               Temp++;
            }
         }
         PrevUDIStatus = UdiStatus;
      }

   }

   if((TempUniversalCount!=UniversalCount)&&(UsbTimerStatus))
   {
      USBMutex.Lock();
      if(PrintOnAlarmAndSample())
         UniversalCount=TempUniversalCount;
      USBMutex.Unlock();
   }

  if((CEventLog::EventHistoryRamCount != TempEventGlobalCount) && (SkipEventCheckCount >= SKIP_EVENTCHECK_POWERUP) && (!CEventLog::EventHistoryFullFlag))
   {
      //ask for more data and add to list
      int length2 = 9;

	  int EventCount = TempEventGlobalCount - CEventLog::EventHistoryRamCount;
      if(EventCount > MAX_EVENT_STORAGE_WC)
      {
         CEventLog::EventHistoryglobalCount = TempEventGlobalCount - MAX_EVENT_STORAGE_WC; //if eventcount>100,then starting point wont be 0
      }
      unsigned char CommandData[9];
      unsigned char * data3 = (unsigned char *) &CommandData[0];
      if(EventCount < 0)
      {
         printf("ERROR : EVENTHISTORY COUNT Less than 0\n");
         EventCount = 0;
         CEventLog::EventHistoryglobalCount = TempEventGlobalCount;
      }
      if(EventCount > MAX_EVENT_IN_ONE_PACKET)
      {
         printf("ERROR : EVENTHISTORY COUNT More than expected\n");
         EventCount = MAX_EVENT_IN_ONE_PACKET;
      }
      if(EventCount)
      {
         //	EventCount = 1;
         CommandData[0] = ((char) 1);
         *((int*)(CommandData+1)) = (int)htonl(CEventLog::EventHistoryUniversalCount); //Starting point
         *((int*)(CommandData+5)) =(int) htonl(EventCount); //Count of data
         CHostCommand * request = new CHostCommand(EVENTLOGSETUP, data3, length2);   //1054
         CHostCommand * response = app->SendUiHostCommand(request);
         printf("RequestSent and Response Recieved\n");
         //			CEventLog::thisHisPtr->EventListMutex.Lock();
         if(response)
         {

            printf("Response Positive");
            char ch=CHostCommand::AckNak();
            data3 = response->GetData();
            int logTotalCycles = *((int*)(data3));	//number of Data.
            data3+=sizeof(int);
            int TotalCycles = htonl(logTotalCycles);

            CEventLog::thisHisPtr->TotalCycle = TotalCycles;
            if(ch==ACK)
            {
               //struct Event_Log * EventHistoryData = (struct Event_Log*)data;
               for(int i = 0;i < TotalCycles; i++)
               {
                  if(CEventLog::EventHistoryglobalCount >= MAX_ALLOWED_EVENT_LOG) //100000 limit
                  {
                     if(CChildView::thisPtr->MemoryfullCont_Stop)/*if(check for overwrite_bitset)*/
                        CEventLog::EventHistoryFullFlag = false;
                     else
                     {
                        CEventLog::EventHistoryFullFlag = true;
                        break;
                     }
                  }
                  CEventHistoryData * obj =  new CEventHistoryData((unsigned char*)data3);
                  EventHistoryList.AddTail(obj);
                  CEventLog::EventHistoryglobalCount++;
				  CEventLog::EventHistoryRamCount++;
                  data3 += sizeof(Event_Log) ;
                  printf("*%d",sizeof(Event_Log));
               }
               printf("EventHistoryList.GetCount = %d \n",EventHistoryList.GetCount());
               delete response;
            }
            else // No Ack
               delete response;
         }
         printf("Added the all event history To the Listsuccessfully \n");
         WaitForUSBData.SetEvent();
      }
   }
   else
      SkipEventCheckCount++;



   if(!CommandForAlarmButton && TempAlarmCount!=0)
   {
      GetAlarmButton();
      AlarmCount=TempAlarmCount;
   }
   else
   {
      WaitForEtherNetAlarmHandle.SetEvent();

   }

   if(PresetStatusUpdated == true)
      PresetNum = TempPresetNum;
   /*Again Initialise the polling timer.*/
   InitialiseTimer(Pollingtimer,POLLINGTIME);
}

/*****************************************************************************/
/*		Function to process the NAK response of any host command.			 */
/*****************************************************************************/
void CChildView::ProcessNak(unsigned char *&data, int &length,int Address,int FunID)
{
   int WeldProcessError =CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
   if(WeldProcessError == WELD_PROCESS_ERROR)
   {
      int ErrorCode=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
      switch(ErrorCode)
      {
      case ACCESS_NOT_ALLOWED:
         {
            ErrorBeep();
            OnKeypadScreen_flag=false;
         }
         break;
      case REFRESH_MENU:
         {
            ErrorBeep();
            OnKeypadScreen_flag=false;
            theApp.menuName=menusname.RemoveTail();
            page_no=menus.RemoveTail();
            theApp.MenuPointer=menupointers.RemoveTail();
            ModifyObjectList(theApp.MenuPointer);
            Invalidate();

         }
         break;
      case SHOW_MSG_SCREEN:
         {
            CVgaMenu * menu;
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
               if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->submenu!="")
                  {
                     if (theApp.menus.Lookup(ptr->submenu, menu))
                     {
                        page_no=1;
                        ModifyObjectList(menu);
                        theApp.menuName = ptr->submenu;
                        theApp.MenuPointer=menu;
                        Invalidate();
                     }
                  }
                  break;
               }
            }
         }
         break;
      case SHOW_PASSWORD_SCREEN:
         {
            OnKeypadScreen_flag=true;
            unsigned char *s=0;
            menusname.AddTail(theApp.menuName);
            menus.AddTail(page_no);
            menupointers.AddTail(theApp.MenuPointer);
            BuildCompleteKeypadList(VGA_PASSWORD,s,0,PASSWORDCOMMAND,(class CVgaMenuItem *)Address);
            Invalidate();
         }
         break;
      case SHOW_PASSWORD_ENTRY1:
         {
            OnKeypadScreen_flag=true;
            unsigned char *s;
            BuildCompleteKeypadList(VGA_PASSWORD,s,0,PASSWORDCOMMAND,0);
            Invalidate();
         }
         break;
      case SHOW_PASSWORD_ENTRY2:
         {
            CScreenKeypad::TempPassword = CScreenKeypad::AlphaBuf;
            OnKeypadScreen_flag=true;
            unsigned char *s;
            BuildCompleteKeypadList(VGA_PASSWORD,s,0,PASSWORDCOMMAND,(class CVgaMenuItem *)1);
            Invalidate();
         }
         break;
      case SHOW_WELDINGON_MESSAGE:
         {
            CString NakMenu;
            CVgaMenuItem *item=(CVgaMenuItem *)Address;
            switch(item->GetType())
            {
            case CVgaMenu::VGA_Button_OBJECT:
               {
                  CVgaButton *ptr=(CVgaButton *)Address;
                  NakMenu=ptr->MenuNak ;
               }
               break;
            case CVgaMenu::ALPHA:
               {
                  CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)Address;
                  NakMenu=ptr->MenuNak ;
               }
               break;
			case CVgaMenu::VARIABLE:
				{
					CVgaVariable *ptr=(CVgaVariable *)Address;
					NakMenu=ptr->MenuNak ;
				}
				break;
            }
            page_no=1;
            CVgaMenu * menu;
            if (theApp.menus.Lookup(NakMenu, menu))
            {
               CChildView::thisPtr->menusname.AddTail(theApp.menuName);
               CChildView::thisPtr->menus.AddTail(page_no);
               CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
               CChildView::thisPtr->ModifyObjectList(menu);
               theApp.menuName = NakMenu;
               theApp.MenuPointer=menu;
            }

         }
         break;
      case COLSETUP_MSG_SCREEN:
         {
            CVgaMenu * menu;
            menu=theApp.MenuPointer;
            CVgaMenuItem * object=menu->items.GetHead();
            POSITION pos = menu->items.GetHeadPosition();
            while(pos)
            {
               object = menu->items.GetNext(pos);
               if(object->GetType() == CVgaMenu::VGAMsgScrnObject)
               {
                  CMsgScreen *ptr=(CMsgScreen *)object;
                  if(ptr->submenu!="")
                  {
                     if (theApp.menus.Lookup(ptr->submenu, menu))
                     {
                        menusname.AddTail(theApp.menuName);
                        menus.AddTail(page_no);
                        menupointers.AddTail(theApp.MenuPointer);
                        page_no=1;
                        ModifyObjectList(menu);
                        theApp.menuName = ptr->submenu;
                        theApp.MenuPointer=menu;
                        Invalidate();
                     }
                  }
                  break;
               }
            }
         }
         break;
      default:
         ErrorBeep();
         break;
      }
   }
}

CDC* CChildView::GetDc()
{
   return GetDC();
}

void CChildView::ReleaseDc(CDC *pDC)
{
   ReleaseDC(pDC);
}

/**********************************************************/
/*	This function draws the page number on the screen,	  */
/*	if menu has more then one page.						  */
/**********************************************************/
void CChildView::DrawPageNumber(CDC *pDC)
{
   if(Total_Text_Objects<MaxItemIn1ColMenu)
   {
      int Item_PerPage =MaxItems_PerPage;
      if((RowPerPage != 0)
         ||(ColumnPerPage !=0))
         Item_PerPage=RowPerPage*ColumnPerPage;
      int Total_Pages=Total_Objects/Item_PerPage;
      int remender=Total_Objects%Item_PerPage;
      if(remender!=0)
         Total_Pages++;

      int Current_page_no=page_no;      //adding page no
      if(Total_Pages>1)
      {
         char Curr_buff[MAXINTLEN * 2 + 3];//%d0f%d formatiing in curr_buff requires the current buff size to twice the digits in max int plus space for "of" plus null
         sprintf(Curr_buff,"%dof%d",Current_page_no,Total_Pages);
         CString PageString=CChildView::thisPtr->StrPage;
         PageString+=Curr_buff;
         CVgaMenuItem::DrawText(pDC, Bigfont,White, Page_No_Rect, PageString,true);
      }
   }

}

/********************************************************************************************/
/* This function is used to collect all printing related data from 332. The function is		*/
/* used for following types of print list depending upon the argument passed				*/
/* 1. Weld Setup.																			*/
/* 2. Dups Preset.																			*/
/* 3. HornScan Graph and its text.															*/
/* 4. Screen Graph.																			*/
/* 5. For All six Graphs, when user presses Print Now button.								*/
/* 6. Weld History Data and its parameter ID array.											*/
/* 7. Weld Data and its ID Array.															*/
/*																							*/
/********************************************************************************************/
void CChildView::BuildPrintList(int type)
{

   char retry=0;
   int UserIdGlobalCount=0xff;

   /* For Weld Setup */
   if(type == SETUPID)
   {
      SetupTemp_pos = tempSetupList.GetHeadPosition();
      tempSetupList.GetNext(SetupTemp_pos);
      tempSetupList.GetNext(SetupTemp_pos);
      int FUN_ID=GetWeldSetupPrint_FunID;

      for(int PAGE=SETUPSTARTPAGE;PAGE<SETUPENDPAGE;PAGE++)
      {

         int length=ONE;
         {
            unsigned char* data = (unsigned char *) &PAGE;
            CCommPort::OnPollingTime=false;
            CHostCommand * request = new CHostCommand(FUN_ID, data, length);
            CHostCommand * response = app->SendUiHostCommand(request);
            if(response)
            {
               char ch=CHostCommand::AckNak();
               data = response->GetData();
               length = response->GetDataLength();
               if(ch==ACK)
                  while (length>ZERO)
                  {
                     int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                     CPrintText * object = new CPrintText(data, length,false,ID);
                     PrintObjectList.AddTail(object);
                  }
                  delete response;
            }

         }
      }
	  PrintStreamingSetup();
	  if(!PrintInfoList.IsEmpty())
           PrintInfoList.RemoveHead();
  	  PrintInfoList.AddTail(SETUPID);
      WaitForPrintData.SetEvent();
	  return;
   }

   if(type == USERID)
   {

      UserIdGlobalCount=GetNumberOfUsers();
      printf("  globalcount=%d\n",UserIdGlobalCount);
      do{
         CUserIDTable::CreateUserObjectList();
         retry++;
         if(retry>2)
            break;

      }while(CUserIDTable::thisPtr->TotalCycle!=UserIdGlobalCount);


      if((CUserIDTable::thisPtr->TotalCycle==UserIdGlobalCount)&&(UserIdGlobalCount!=0))
      {

         if(!PrintInfoList.IsEmpty())
            PrintInfoList.RemoveHead();
         PrintInfoList.AddTail(USERID);
         WaitForPrintData.SetEvent();
         userid_list_status=SUCCESS;

      }
      else
      {

         if(UserIdGlobalCount==0)
         {
            printf("no valid data\n");
            userid_list_status=NO_VALID_DATA;
         }
         else
         {
            printf("comm error\n");
            userid_list_status=COMM_ERROR;
         }
         creating_pdf=false;
      }


   }

   if(type == EVENTLIST)
   {
      if(!PrintInfoList.IsEmpty())
         PrintInfoList.RemoveHead();
      PrintInfoList.AddTail(EVENTLIST);
      WaitForPrintData.SetEvent();

   }

   if(type == WELD_HISTORY_ID)
   {
      if(!PrintInfoList.IsEmpty())
         PrintInfoList.RemoveHead();
      PrintInfoList.AddTail(WELD_HISTORY_ID);
      WaitForPrintData.SetEvent();

   }


   if(type == ALARMLOGID)
   {
      printf("BuildAlarmLogPrintList \n");
      int length = 9;
      int RecievedLogCount = 0;
      int CurrentCycleCount = 0;
      bool FirstResponseFlag = true,LastCycleFlag = false;
      unsigned char CommandData[9];

      CommandData[0]=(char)0; //Ask For Alarm
      *((UINT32*)(CommandData+1)) = htonl(0);					//assume the count Count to be starting with 0
      *((UINT32*)(CommandData+5)) = htonl(ALARM_IN_ONE_PACKET); //assue that we have one packet of data with SBC
      while(CAlarmLog::thisHisPtr->AlarmLogList.GetCount())
         delete CAlarmLog::thisHisPtr->AlarmLogList.RemoveHead();
      do
      {
         length = 9; //length of data sent
         *((UINT32*)(CommandData+1)) = htonl(RecievedLogCount);

         unsigned char * data = (unsigned char *) &CommandData[0];
         CHostCommand * request = new CHostCommand(EVENTLOGSETUP, data, length);   //1054
         CHostCommand * response = app->SendUiHostCommand(request);
         if(response)
         {
            printf("Response Positive");
            char ch=CHostCommand::AckNak();
            data = response->GetData();
            CurrentCycleCount = *((UINT32*)(data));
            CurrentCycleCount = ntohl(CurrentCycleCount); //Data sent by WC this cycle
            if(FirstResponseFlag) //First response from WC
            {
               FirstResponseFlag = false;
               CAlarmLog::thisHisPtr->TotalCycle = CurrentCycleCount;
               RecievedLogCount = ALARM_IN_ONE_PACKET;
               printf("TotalCycle = %x\n",RecievedLogCount);
            }
            else { // if Not the first response
               RecievedLogCount += CurrentCycleCount;
               printf("RecievedLogCount = %x\n",RecievedLogCount);
            }

            if(CAlarmLog::thisHisPtr->TotalCycle == 0)
            {
               LastCycleFlag = true;
               delete response;
               printf("No data on WC\n");
               break;
            }

            if((CurrentCycleCount < ALARM_IN_ONE_PACKET) || (RecievedLogCount >= MAX_ALARM_COUNT))
               LastCycleFlag = true;
            else
               CurrentCycleCount = ALARM_IN_ONE_PACKET;

            if(ch==ACK)
            {
               data += sizeof(UINT32);//skip count and point to data
               struct AlarmLog * AlarmLogData = (struct AlarmLog*)data;
               for(int i = 0;i < CurrentCycleCount; i++)
               {
                  CAlarmLogData * obj =  new CAlarmLogData(AlarmLogData);
                  AlarmLogData++;
                  CAlarmLog::thisHisPtr->AlarmLogList.AddTail(obj);
               }
               printf("AlarmLogList.GetCount = %d \n",CAlarmLog::thisHisPtr->AlarmLogList.GetCount());
               delete response;
            }
            else // No Ack
            {
               LastCycleFlag = true;
               delete response;
               break;
            }
         }
         else // if no response
            LastCycleFlag = true;
         printf(".");
      }while(LastCycleFlag != true);
      CAlarmLog::thisHisPtr->TotalCycle =(int)CAlarmLog::thisHisPtr->AlarmLogList.GetCount();
   }
   if(type == COPYALL_PRESET_TOUSB)
   {
      if(!PrintInfoList.IsEmpty())
         PrintInfoList.RemoveHead();
      PrintInfoList.AddTail(COPYALL_PRESET_TOUSB);
      WaitForPrintData.SetEvent();

   }
    if(type == COPYALL_PRESET_TOUSB_OK)
   {
      if(!PrintInfoList.IsEmpty())
         PrintInfoList.RemoveHead();
      PrintInfoList.AddTail(COPYALL_PRESET_TOUSB_OK);
      WaitForPrintData.SetEvent();

   }

}
/********************************************************************************************/
/*  This function is used to collect the Current Setup data from WC and prepares the strings*/
/* for weld setup PDF																		*/
/********************************************************************************************/

void CChildView::PrintStreamingSetup()
{
	int FUN_ID=GetWeldSetupPrint_FunID;
	int length=ONE;
	int PAGE=STREAMINGSETUPPAGE;
	unsigned char* data = (unsigned char *) &PAGE;
	CCommPort::OnPollingTime=false;
	CHostCommand * request = new CHostCommand(FUN_ID, data, length);
	CHostCommand * response = app->SendPollingHostCommand(request);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		if(ch==ACK)
			while (length>ZERO)
			{
				int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
				CPrintText * object = new CPrintText(data, length,false,ID);
				PrintObjectList.AddTail(object);
			}
			delete response;
	}

	PrintInfoList.AddTail(SETUPID);
	WaitForPrintData.SetEvent();
}


BOOL CALLBACK _AfxAbortProc(HDC, bool x)
{
   if(x==1)
      return false;
   return TRUE;
}

/********************************************************************************************/
/* This function is called by printing thread to print the weld setup or   					*/
/* user id pdf. PrintInfoList contains the information of which pdf to be printed			*/
/* It calls OnPrint function to print all items in PrintObjectList or UserIDList     		*/
/********************************************************************************************/

bool CChildView::print()
{
   bool PDFCreateStatus = true;

   printf("\n***CChildView::Print()***");
   const char *fontname;
   HPDF_Doc  pdf;
   char STR[100];
   CString UserIdString = "";
   pdf = HPDF_New (error_handler, NULL);
   if (!pdf) {
      printf ("error: cannot create PdfDoc object\n");
      return false ;
   }

   if (setjmp(env)) {
      HPDF_Free (pdf);
      return false;
   }

   HPDF_Font def_font;


   if(PrintObjectList.GetCount() && thisPtr->PrintInfoList.GetHead()== SETUPID)
   {
      strcpy (fname,"WeldSetup");
   }
   else if(CUserIDTable::thisPtr->UserIDList.GetCount() && thisPtr->PrintInfoList.GetHead()==USERID)
   {
      strcpy (fname,"UserID");
   }

   CurrentFilepath = GetCurrentFilePath(fname);
   CreateFolder(true);
   sprintf(fname,"%s",CurrentFilepath);
   HPDF_UseUTFEncodings(pdf);
   fontname = HPDF_LoadTTFontFromFile(pdf,PDFFontName, HPDF_TRUE);
   def_font = HPDF_GetFont(pdf, fontname,"UTF-8");

   while(PrintObjectList.GetCount() && !EstopPressedFlag)
   {
      HPDF_Page page = HPDF_AddPage (pdf);
      HPDF_Page_SetFontAndSize (page, def_font, 8);
      OnPrint(NULL, NULL, &pdf, &page);
   }

   if(CUserIDTable::thisPtr->UserIDList.GetCount())
   {
      HPDF_Page page = HPDF_AddPage (pdf);
      PdfWithImage(&pdf,&page,&def_font);
      HPDF_Page_SetFontAndSize (page, def_font,25);
      UserIdString = CVgaMenuItem ::LinearSearch(XSTR(USERID_STRINGID));
      CChildView::thisPtr->CStringToUTF(UserIdString,STR);
      CChildView::DrawPDFText(&page,10,TWOWELDLINEGAP,STR);
      HPDF_Page_SetFontAndSize (page, def_font, 8);
      OnPrint(NULL, NULL, &pdf, &page);
   }
   printf("Save file");
   if(!EstopPressedFlag)
	   SavePDFToUSB(pdf,fname);
   else
   {
	   PDFCreateStatus = false;
	   HPDF_Free (pdf);
   }
   PDFCreateStatus = CChildView::thisPtr->USBPresent();
   printf("PDF Saved\n");
   return PDFCreateStatus;
   //#endif
}

/************************************************************************************/
/* This function is called from print function to print the USERID or Setup data	*/
/* in PDF.
/************************************************************************************/
void CChildView::OnPrint(CDC *pDC, CPrintInfo * x, HPDF_Doc * pdf,HPDF_Page * page)

{
   int PrintType = 0;
   if(!PrintInfoList.IsEmpty())
      PrintType = PrintInfoList.RemoveHead();

   char UnicodeStr[8192];
   int Mid_Width,New_Xcoordinate;

   Mid_Width = ((int)HPDF_Page_GetWidth (*page))/2;

  //Coverity Issue

   if((PrintType==SETUPID)||(PrintType==DUPSPRESET))
   {
      CPrintText *object = NULL;

      if(PrintObjectList.GetCount())
      {
         object = PrintObjectList.GetHead();

         object->CoOrdinate.y-=THREELINEGAP;
         CChildView::thisPtr->CStringToUTF(object->Text,UnicodeStr);
         if(object->CoOrdinate.x >Mid_Width)
         {
            New_Xcoordinate = object->CoOrdinate.x -200;
            DrawPDFText(page,New_Xcoordinate - 100,object->CoOrdinate.y,UnicodeStr);
         }
         else
            DrawPDFText(page,object->CoOrdinate.x-50,object->CoOrdinate.y,UnicodeStr);
      }
      else
         return;

      delete PrintObjectList.RemoveHead();
      while(PrintObjectList.GetCount() && !EstopPressedFlag)
      {
         object = PrintObjectList.GetHead();
         int New_Y_Cordinate = object->CoOrdinate.y;
         if(New_Y_Cordinate !=PAGESTARTCORDINATE)
         {
            object->CoOrdinate.y-=THREELINEGAP;

            CChildView::thisPtr->CStringToUTF(object->Text,UnicodeStr);
            if(object->CoOrdinate.x >Mid_Width)
            {
               New_Xcoordinate = object->CoOrdinate.x -200;
               DrawPDFText(page,New_Xcoordinate - 100,object->CoOrdinate.y,UnicodeStr);
            }
            else
               DrawPDFText(page,object->CoOrdinate.x-50 ,object->CoOrdinate.y,UnicodeStr);

            delete PrintObjectList.RemoveHead();
         }
         else
            break;
      }
      return;
   }
   if(PrintType==USERID)
   {
      printf("PrintType==USERID\n");
      CUserIDTable::thisPtr->CreatePDF(pdf,page);
      return;
   }
}


/************************************************************************************************/
/* This function is called when polling response is received. The function compares the			*/
/* base count of each of the six graphs, weld data base count, weld history base count and		*/
/* weld seup base count with the present weld cycle number. If any of these objects is to be	*/
/* printed then command is send to 332 to get its data.											*/
/*   If Ext Preset is Off and preset changes then all the objects which have print on sample	*/
/* enabled is printed.(If weld is done on changed preset)										*/
/*   If Ext Preset is On then Preset change have no effect on printing.							*/
/*																								*/
/************************************************************************************************/
bool CChildView::PrintOnAlarmAndSample()
{
   if(USBGlobalFlag)
      USBPresent();

   int diff=PresentWeldCount-UniversalCount;
   bool USBWeldData =false;
   bool WeldData=false;
   WeldOnChangedPreset=false;
   int TotalGraphRequestValue=0;
   int TotalPrintGraphRequest=0;  //Coverity Issue
   bool WeldDataLog = true;
   bool SignalUsbThread = false;
  if(diff>MAX_WELDDATA_REQUEST_COUNT)
   {
      Welddata.BaseCount= PresentWeldCount-MAX_WELDDATA_REQUEST_COUNT;
      USBWelddata.BaseCount  =  PresentWeldCount-MAX_WELDDATA_REQUEST_COUNT;
      diff=MAX_WELDDATA_REQUEST_COUNT;
   }


   if(powerup)
   {
      Setup.BaseCount     = UniversalCount;
      PrintSequence.BaseCount=UniversalCount;
      Welddata.BaseCount  = UniversalCount+1-Welddata.PrintSampleValue;
      WeldHistory.BaseCount=UniversalCount;
      PowerGraph.BaseCount= UniversalCount;
      ColDistance.BaseCount=UniversalCount;
      VelocityGraph.BaseCount=UniversalCount;
      ForceGraph.BaseCount=UniversalCount;
      AmplitudeGraph.BaseCount=UniversalCount;
      FrequencyGraph.BaseCount=UniversalCount;

      USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
      USBPowerGraph.BaseCount= UniversalCount;
      USBColDistance.BaseCount=UniversalCount;
      USBVelocityGraph.BaseCount=UniversalCount;
      USBForceGraph.BaseCount=UniversalCount;
      USBAmplitudeGraph.BaseCount=UniversalCount;
      USBFrequencyGraph.BaseCount=UniversalCount;

   }
   else if(!diff)
      return true;

   else
   {
      if(((PresentPresetNum ==PresetNum)&&(!ExtPreset))//case for weld done on same preset
         ||(ExtPreset)) /* Weld Done On Changed Preset*/
      {

         if((PresentPresetNum!=PresetNum)&&(!ExtPreset))/* Weld Done On Changed Preset*/
         {
            WeldOnChangedPreset=true;
            TempPresetNum=PresentPresetNum;
            if(DataForUSB(WELDDATAONSAMPLEID))
               USBWeldData=true;

            if((!Welddata.PrintSampleDisable)&&(CheckForPrinting()))
            {
               WeldData=true;
            }

            if(((!PowerGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(POWERGRAPHID)))
            {

               TotalPrintGraphRequest++;
               TotalGraphRequestValue+=Power_RequestValue;
            }

            if(((!ColDistance.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(COLDISTANCEID)))
            {

               TotalGraphRequestValue+=Distance_RequestValue;
               TotalPrintGraphRequest++;
            }
            if(((!VelocityGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(VELOCITYGRAPHID)))
            {

               TotalPrintGraphRequest++;
               TotalGraphRequestValue+=Velocity_RequestValue;

            }

            if(((!ForceGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(FORCEGRAPHID)))
            {

               TotalPrintGraphRequest++;
               TotalGraphRequestValue+=Force_RequestValue;
            }

            if(((!AmplitudeGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(AMPLITUDEGRAPHID)))
            {

               TotalGraphRequestValue+=Amplitude_RequestValue;
               TotalPrintGraphRequest++;
            }

            if(((!FrequencyGraph.PrintSampleDisable)&&(CheckForPrinting()))||(DataForUSB(FREQUENCYGRAPHID)))
            {

               TotalGraphRequestValue+=Frequency_RequestValue;
               TotalPrintGraphRequest++;
            }

         }

         else
         {
            BaseWeldCount=TempBaseWeldCount;
            GlobalCycleCount=PresentWeldCount;

            if(DataForUSB(WELDDATAONSAMPLEID))
            {

               USBWeldData=true;
            }

               if((PresentAlarmCount) && (Welddata.PrintOnAlarmValue)&&(CheckForPrinting()))
               {

                  WeldData=true;
               }
               else if((!Welddata.PrintSampleDisable)&&(CheckForPrinting()))
                  if((PresentWeldCount-Welddata.BaseCount)>=Welddata.PrintSampleValue)
                  {
                     WeldData=true;
                  }

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,POWERGRAPHID,
                        Power_RequestValue,&PowerGraph);

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,COLDISTANCEID,
                        Distance_RequestValue,&ColDistance);

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,VELOCITYGRAPHID,
                        Velocity_RequestValue,&VelocityGraph);

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,FORCEGRAPHID,
                        Force_RequestValue,&ForceGraph);

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,AMPLITUDEGRAPHID,
                        Amplitude_RequestValue,&AmplitudeGraph);

                     SetRequestValue(&TotalGraphRequestValue,&TotalPrintGraphRequest,FREQUENCYGRAPHID,
                        Frequency_RequestValue,&FrequencyGraph);
         }
      }
      else if(PresentPresetNum !=PresetNum)
      {
         TempBaseWeldCount=BaseWeldCount;
         BaseWeldCount=PresentWeldCount;
         TempPresetNum=PresetNum;
      }
      int GraphsForPrint=0;
      CString SysPressureStr;
      bool ShowSysPressureStr=false;
      if((RunResultScreen)&&(TotalGraphRequestValue==0))
      {
         ++TotalGraphRequestValue;
      }

      if((TotalGraphRequestValue!=0)||(WeldData==true)||(USBWeldData)||(WeldDataLog))
      {

         /* Now Send Request For The Graphs Needed And Print Them*/
         int length =CORDLENGTH;
         unsigned char data1[CORDLENGTH];
         if(TotalGraphRequestValue!=1)
         {
            data1[0]=(char)(++TotalGraphRequestValue);
         }
         else
         {
            data1[0]=(char)(TotalGraphRequestValue);
         }

         if(RunResultScreen)
            data1[1]=(char)diff; //on run screen & for both graphs and weld data
         else if((TotalGraphRequestValue==1)&&((WeldData)||(USBWeldData)||(WeldDataLog)))
         {
            data1[1]=(char)diff;//when no graphs & only weld data
         }
         else if((TotalGraphRequestValue>1)&&((WeldData)||(USBWeldData)))
         {
            data1[1]=(char)diff; // for both graphs and weld data
         }
         else if((TotalGraphRequestValue>1)&&(!WeldData)&&(!USBWeldData))
         {
            data1[1]=(char)1;//when single weld data is required for graphs
         }
         else if(WeldDataLog)
         {
            data1[1]=(char)diff;//when single weld data is required for graphs
         }
         else
         {
            return true;/*return if nothing is required*/
         }

         CVgaMenu * menu;
         menu=theApp.MenuPointer;

         unsigned char * data = (unsigned char *) &data1[0];
         CCommPort::OnPollingTime=false;
         CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
         CHostCommand * response = app->SendPollingHostCommand(request);
         if (response)
         {
            char ch=CHostCommand::AckNak();
            data = response->GetData();//Getting Data.
            length = response->GetDataLength();//Getting Length.
            bool GraphForUSB = false;
			bool ValidGraphData = true;
            if(ch==ACK)
               while((length>0)&&(ValidGraphData))
               {
                  int DataLength=length;
                  unsigned char * DataPtr =data;
                  unsigned char * RunDataPtr =data;
                  int RunDataLength=length;
                  {
                     CWeldingData *TempPtr = new CWeldingData(data, length,true);
                     if((TempPtr->ReceivedUniversalCount!=PresentWeldCount)&&(diff!=30))
                     {
                        PresentWeldCount=TempPtr->ReceivedUniversalCount;
                        delete TempPtr;
                        delete response;
                        return false;
                     }
					 else if(TempPtr->TotalCycles == 0)//No data recived after init fram
					 {
						PresentWeldCount=TempPtr->ReceivedUniversalCount;
						delete TempPtr;
                        delete response;
                        return true;
					 }
					 else if(diff > TempPtr->TotalCycles)//some cycles ran after init fram
					 {
						diff = TempPtr->TotalCycles;
						UniversalCountWeldHiddenFile += (MAX_WELDDATA_REQUEST_COUNT - diff);
						delete TempPtr;
					 }
                     else
                     {
                        delete TempPtr;
                     }
                     if(RunResultScreen)
                     {
                        CVgaMenu * menu;
                        menu=theApp.MenuPointer;
                        POSITION pos = menu->items.GetHeadPosition();
                        while(pos)
                        {
                           CVgaMenuItem *Object = menu->items.GetNext(pos);
                           if(Object->GetType()==CVgaMenu::VGARUNSCREENOBJECT)
                           {
                              CRunScreen *obj = (CRunScreen*)Object;
                              obj->UpdateWeldData(RunDataPtr,RunDataLength,true);
                              if(!OnKeypadScreen_flag)
                              {
                                 CDC*pDC=GetDC();
                                 Object->Draw(pDC);
                                 ReleaseDC(pDC);
                              }
                              break;
                           }
                        }
                     }
                  }

                  int NoofUSBGraphs=0;
                  if(TotalPrintGraphRequest)
                  {

                     while((length>0)&&(ValidGraphData))
                     {
                        unsigned char *ptr1=data;
                        int len=length;
                        CVgaDrawGraph * PrintGraph;
                        int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(ptr1,len,CORDLENGTH);
                        switch(ValueAfterParamID)
                        {
                        case POWGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[0];
                           break;
                        case AMPLIGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[1];
                           break;
                        case FREQUGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[2];
                           break;
                        case DISTMMGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[3];
                           break;
                        case DISTINGRAPH:
                           GraphTitle = CChildView::thisPtr->LString[4];
                           break;
                        case VELMMGRAPH :
                           GraphTitle= CChildView::thisPtr->LString[5];
                           break;
                        case VELINGRAPH:
                           GraphTitle= CChildView::thisPtr->LString[6];
                           break;
                        case FORCENGRAPH :
                           GraphTitle= CChildView::thisPtr->LString[7];
                           break;
                        case FORCELBGRAPH:
                           GraphTitle= CChildView::thisPtr->LString[8];
						   break;
						default:
							ValidGraphData = false;
                           break;
                        }

						if(ValidGraphData)
						{
	                        CVgaDrawGraph * USBGraph = new CVgaDrawGraph(ValueAfterParamID);
	                        USBGraph->GraphData.graph_type=ValueAfterParamID;

	                        SetGraphObjectMember(ptr1,len,USBGraph);
	                        USBGraph->GraphCount--;

	                        if(USBGraph->GraphForUSB(this))
	                        {
	                           GraphForUSB = true;
	                           SysPressureStr="";
	                           for(int i=0;i<20;i++)
	                           {
	                              if(USBGraph->GraphData.SystemPressure[i]=='\0')
	                                 break;
	                              SysPressureStr+=USBGraph->GraphData.SystemPressure[i];
	                              if(USBGraph->GraphData.SystemPressure[i]!='\0')
	                                 ShowSysPressureStr=true;
	                           }

	                           USBGraphsList.AddTail(USBGraph);
	                           NoofUSBGraphs++;
	                        }
	                        else
	                           delete USBGraph;
						}

                        ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                        switch(ValueAfterParamID)
                        {
                        case POWGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[0];
                           break;
                        case AMPLIGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[1];
                           break;
                        case FREQUGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[2];
                           break;
                        case DISTMMGRAPH :
                           GraphTitle = CChildView::thisPtr->LString[3];
                           break;
                        case DISTINGRAPH:
                           GraphTitle = CChildView::thisPtr->LString[4];
                           break;
                        case VELMMGRAPH :
                           GraphTitle= CChildView::thisPtr->LString[5];
                           break;
                        case VELINGRAPH:
                           GraphTitle= CChildView::thisPtr->LString[6];
                           break;
                        case FORCENGRAPH :
                           GraphTitle= CChildView::thisPtr->LString[7];
                           break;
                        case FORCELBGRAPH:
                           GraphTitle= CChildView::thisPtr->LString[8];
                           break;
						default:
							ValidGraphData = false;
                           break;
                        }

						if(ValidGraphData)
						{
	                        PrintGraph = new CVgaDrawGraph(ValueAfterParamID);
	                        PrintGraph->GraphData.graph_type=ValueAfterParamID;

	                        SetGraphObjectMember(data,length,PrintGraph);
	                        PrintGraph->GraphCount--;
	                        if(PrintGraph->GraphForPrinting(this))
	                        {
	                           SysPressureStr="";
	                           for(int i=0;i<20;i++)
	                           {
	                              if(PrintGraph->GraphData.SystemPressure[i]=='\0')
	                                 break;
	                              SysPressureStr+=PrintGraph->GraphData.SystemPressure[i];
	                              if(PrintGraph->GraphData.SystemPressure[i]!='\0')
	                                 ShowSysPressureStr=true;

	                           }

	                           GraphPrintList.AddTail(PrintGraph);
	                           PrintInfoList.AddTail(POWERGRAPHID);
	                           GraphsForPrint++;
	                        }
	                        else
	                           delete PrintGraph;
						}
                     }
                  }
                  if(WeldDataLog)
                  {
                     int USBLength=DataLength;
                     unsigned char * USBPtr =DataPtr ;
                     CHistoryData* USBObject;
                     bool LatestWelddataAddedLog =false;
                     if((PresentWeldCount > UniversalCount) && (!CWeldingHistory::WeldSpaceFullFlag))
                     {
                        LatestWelddataAddedLog = MakeLOGWeldData(USBPtr, USBLength,diff);

                     }
                     if(!LatestWelddataAddedLog && (!CWeldingHistory::WeldSpaceFullFlag))
                     {
                        USBObject = new CHistoryData(USBPtr, USBLength);
                        LOGHistoryList.AddTail(USBObject);
                     }
                     SignalUsbThread = true;
                  }
                  if((GraphForUSB)||(USBWeldData))
                  {
                     printf("(GraphForUSB)||(USBWeldData)");
                     int USBLength=DataLength;
                     unsigned char * USBPtr =DataPtr ;
                     CHistoryData* USBObject;
                     bool LatestWelddataAdded =false;

                     if(((PresentWeldCount-USBWelddata.BaseCount)>=USBWelddata.USBSampleValue)||USBWelddata.USBOnAlarmValue)
                     {
                        LatestWelddataAdded = MakeUSBWeldData(USBPtr, USBLength,diff);

                     }
                     if(!LatestWelddataAdded)
                     {
                        USBObject = new CHistoryData(USBPtr, USBLength);
                        USBHistoryList.AddTail(USBObject);
                     }
                     USBGraphCountList.AddTail(NoofUSBGraphs);
                     SignalUsbThread = true;
                  }

                  for(int i=1;i<=GraphsForPrint;i++)
                  {
                     int PrintLength=DataLength;
                     unsigned char * PrintPtr =DataPtr ;
                     CWeldingData *PrintWeldDataObject = new CWeldingData(ONE,PrintPtr, PrintLength,true);
                     GraphWeldDataPrintList.AddTail(PrintWeldDataObject);
                  }
               }
               delete response;
         }
         else
            return false;
      }
   }
   if(SignalUsbThread)
      WaitForUSBData.SetEvent();
   return true;
}



void CChildView::WeldHistoryPrint(int ID)
{
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
   tempHistoryList.GetNext(HistoryTemp_pos);
   tempHistoryList.GetNext(HistoryTemp_pos);

   CChildView::thisPtr->BuildPrintList(ID);
}


void CChildView::WeldDataPrint(int ID)
{

   HistoryTemp_pos=NULL;
   GraphsTemp_pos=NULL;
   WeldTemp_pos=NULL;
   HornScanTemp_pos=NULL;
   ScanGraphsDataTemp_pos=NULL;
   ScreenGraphsTemp_pos=NULL;
   SetupTemp_pos=NULL;
   DUPSTemp_pos=NULL;
   SequenceTemp_pos=NULL;
   WeldTemp_pos = tempWeldList.GetHeadPosition();
   tempWeldList.GetNext(WeldTemp_pos);

}


void CChildView::GraphsWeldPrint(int ID)
{
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
   tempGraphsList.GetNext(GraphsTemp_pos);
   tempGraphsList.GetNext(GraphsTemp_pos);
}

void CChildView::SetUpPrint(int ID)
{
   CVgaMenu *menu=theApp.MenuPointer;
   theApp.MenuPointer=SetupMenuPointer;
   BuildPrintList(SETUPID);
   theApp.MenuPointer=menu;
}

void CChildView::SequencingPrint(int ID)
{
   CVgaMenu *menu=theApp.MenuPointer;
   theApp.MenuPointer=SequenceMenuPointer;
   BuildPrintList(PRINTSEQUENCE);
   theApp.MenuPointer=menu;
}

/************************************************************************************************/
/* This Printing thread is responsible to send the data to printer buffer. The function waits	*/
/* for any data in the printing queue. If any data is present in the queue then this thread just*/
/* calls the function Print() which does all the printing.										*/
/* This thread also checks wether the printer is present or not.								*/
/* 1.If the printer is present and Print List have data to get printed then it calls Print().	*/
/* 2.If the printer is not present then this function deletes all the data from the list to		*/
/* free the buffer.																				*/
/*																								*/
/************************************************************************************************/
UINT CChildView::PrintingThread(LPVOID)
{
   while(1)
   {
      HANDLE handle;
	  CString menuName = "";
      handle = thisPtr->WaitForPrintData;
      WaitForSingleObject(handle, INFINITE);
      bool PDFCreateStatus = true;
	  EstopPressedFlag = false;
      printf("\n Printing thread");

      if(!thisPtr->PrintInfoList.IsEmpty())
      {
         while(CUserIDTable::thisPtr->UserIDList.GetCount() || thisPtr->PrintObjectList.GetCount())
         {
            if((thisPtr->PrintInfoList.GetHead()==USERID) || (thisPtr->PrintInfoList.GetHead() == SETUPID))
            {
               if(CChildView::thisPtr->IdleLogoutTime>0)
                  CChildView::KillTimers(IDLELOGOUT_TIMER);
               creating_pdf=true;
               PDFCreateStatus = thisPtr->print();

            }
			while(CChildView::thisPtr->PrintObjectList.GetCount()>0)
				delete CChildView::thisPtr->PrintObjectList.RemoveHead();

			while(CUserIDTable::thisPtr->UserIDList.GetCount() > 0)
				delete CUserIDTable::thisPtr->UserIDList.RemoveHead();

         }

         if (thisPtr->PrintInfoList.GetCount() && (thisPtr->PrintInfoList.GetHead()==EVENTLIST))
         {
            if(CChildView::thisPtr->IdleLogoutTime>0)
               CChildView::KillTimers(IDLELOGOUT_TIMER);
            CChildView::thisPtr->EventFlag = true;
            creating_pdf=true;
            PDFCreateStatus = CEventLog::thisHisPtr->CreateEventPDF();
			while(CEventLog::thisHisPtr->EventLogList.GetCount() > 0)
				delete CEventLog::thisHisPtr->EventLogList.RemoveHead();
         }

         if (thisPtr->PrintInfoList.GetCount() && (thisPtr->PrintInfoList.GetHead()==WELD_HISTORY_ID))
         {
            if(CChildView::thisPtr->IdleLogoutTime>0)
               CChildView::KillTimers(IDLELOGOUT_TIMER);
            creating_pdf=true;
            PDFCreateStatus = SaveWeldHistoryPdf();
		    while(CWeldingHistory::thisHisPtr->LOGWeldHistoryList.GetCount()>0)
			{
				CHistoryData *obj1 = CWeldingHistory::thisHisPtr->LOGWeldHistoryList.RemoveHead();//delete
				free(obj1);
			}
		}
		 if(thisPtr->PrintInfoList.GetCount() && (thisPtr->PrintInfoList.GetHead()==COPYALL_PRESET_TOUSB))
			 CopyAllPreset();
		  if(thisPtr->PrintInfoList.GetCount() && (thisPtr->PrintInfoList.GetHead()==COPYALL_PRESET_TOUSB_OK))
		  {
			 CopyPresetOnOKOrCancelButton();
			 if(PresetCount >= CChildView::thisPtr->PresetNameCount)
			 {
				 CChildView::thisPtr->USBOverWritePreset = false;
				if(StoredPresetListData)
				{
					// Done copying all presets.
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
		}
      if(thisPtr->PrintInfoList.GetCount())
         thisPtr->PrintInfoList.RemoveHead();
	  if(!PDFCreateStatus && !EstopPressedFlag)
      {

         CVgaMenu * menu;
         if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
         {
            theApp.menuName=CVgaBottomMenu::mainMenuID;
            theApp.MenuPointer=menu;
            CChildView::thisPtr->ModifyObjectList(menu);
         }
      }
      creating_pdf=false;
      DisableFlag = false;
      CChildView::thisPtr->Invalidate();
      printf("printing over\n");
      if(CChildView::thisPtr->IdleLogoutTime>0)
         CChildView::InitialiseTimer(IDLELOGOUT_TIMER,CChildView::thisPtr->IdleLogoutTime);
 	  if(PDFCreateStatus && !EstopPressedFlag)
		 EnableStateMachine(0);
	  else if(!PDFCreateStatus && !EstopPressedFlag)
	  {
	  	 EnableStateMachine(0);
		 CChildView::thisPtr->ShowMessageScreen("USB Removed");
	  }
	  else if(EstopPressedFlag)
		  PrintingAbortedOnEstop = true;
	  menuName = theApp.menuName;
	  if(menuName != XSTR(ESTOP_MENU) && menuName != XSTR(RESET_MENU) && menuName != XSTR(ESTOPLOGINRESET_MENU))
		  EnableStateMachine(0);
	  thisPtr->WaitForPrintData.ResetEvent();
   }
   return 0;
}

/****************************************************************************************/
/* This funcion is used To get the Weld data parameters heading i.e. Parameter name		*/
/* and their units. This function is called												*/
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/* 3. On change of Units.																*/
/****************************************************************************************/

void CChildView::GetAllWeldDataHeading(CXmlElement * e)
{
   int format;
   int i=0;
   if(!powerup)
   {
      delete []Parameter_ID;
      delete []Parameter_Units_USCS;
      delete []Parameter_Units_Metric;
   }
   Parameter_Heading = new CString[TotalTextHeading];
   WeldDataPatamStringID.SetSize(TotalTextHeading);
   Parameter_Units_USCS = new CString[TotalTextHeading];
   Parameter_Units_Metric = new CString[TotalTextHeading];

   Parameter_ID = new int[TotalTextHeading];
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      WeldDataPatamStringID[i]=element->GetAttribute("textID");

      CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
      Parameter_Heading[i]=str.SpanExcluding (_T("("));
      Parameter_ID[i] = _ttoi(element->GetAttribute("Value"));
      printf("ID = %d",Parameter_ID[i]);
      CString Formatvalue;
      CString FormatString=element->GetAttribute("format");
      values.Lookup(FormatString, Formatvalue);
      if(Formatvalue!="")
      {
         format=_ttoi(Formatvalue);
         CString StrUSCS;
         StrUSCS=CScreenKeypad::InsertWeldParamUnitsString(false,(CScreenKeypad::FORMAT)format);
         StrUSCS.TrimLeft ();
         StrUSCS.TrimRight ();
         Parameter_Units_USCS[i] = _T("(")+ StrUSCS +_T(")");
         CString StrMetric=CScreenKeypad::InsertWeldParamUnitsString(true,(CScreenKeypad::FORMAT)format);
         StrMetric.TrimLeft ();
         StrMetric.TrimRight ();
         Parameter_Units_Metric[i] = _T("(")+StrMetric+_T(")");
      }
      i++;
   }
}


/****************************************************************************************/
/* This funcion is used To get the UserID parameters heading i.e. Parameter name		*/
/* and their units. This function is called												*/
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/* 3. On change of Units.																*/
/****************************************************************************************/


void CChildView::GetAllUserIDHeading(CXmlElement * e)
{
   int i=0;
   if(!powerup)
   {
      delete []UserIDParameter_ID;
   }
   Parameter_UserID_Heading = new CString[TotalUserIDTextHeading];
   UserIDPatamStringID.SetSize(TotalUserIDTextHeading);

   UserIDParameter_ID = new int[TotalUserIDTextHeading];
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      UserIDPatamStringID[i]=element->GetAttribute("textID");

      CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
      Parameter_UserID_Heading[i]=str.SpanExcluding (_T("("));
      UserIDParameter_ID[i] = _ttoi(element->GetAttribute("Value"));
      i++;
   }
}

/****************************************************************************************/
/* This funcion is used To get the Alarm Log data parameters heading i.e. Parameter name*/
/* This function is called												                */
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/****************************************************************************************/
void CChildView::GetAlarmLogDataHeading(CXmlElement * e)
{
   int i=0;
   if(!powerup)
   {
      delete []AlarmLogPara_ID;
   }

   if(!powerup)
      delete []Parameter_Alarm_Heading;
   Parameter_Alarm_Heading = new CString[TotalAlarmHeading];

   AlarmLogPara_ID = new int[TotalAlarmHeading];
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
      Parameter_Alarm_Heading[i]=str.SpanExcluding (_T("("));
      AlarmLogPara_ID[i] = _ttoi(element->GetAttribute("Value"));
      i++;
   }
}

/****************************************************************************************/
/* This funcion is used To get the Event Log data parameters heading i.e. Parameter name*/
/* This function is called												                */
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/****************************************************************************************/
void CChildView::GetEventLogDataHeading(CXmlElement * e)
{
   int i=0;
   if(!powerup)
   {
      delete []EventLogPara_ID;
   }

   if(!powerup)
      delete []Parameter_Event_Heading;
   Parameter_Event_Heading = new CString[TotalEventHeading];

   EventLogPara_ID = new int[TotalEventHeading];
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
      Parameter_Event_Heading[i]=str.SpanExcluding (_T("("));
      EventLogPara_ID[i] = _ttoi(element->GetAttribute("Value"));
      i++;
   }
}

/****************************************************************************************/
/* This funcion is used To get the User ID data parameters heading i.e. Parameter name*/
/* This function is called												                */
/* 1. On Power Up.																		*/
/* 2. On change of Language.															*/
/****************************************************************************************/
void CChildView::GetUserIDDataHeading(CXmlElement * e)
{
   int i=0;
   if(!powerup)
   {
      delete []UserIDPara_ID;
   }

   if(!powerup)
      delete []Parameter_UserID_HeadingS;
   Parameter_UserID_HeadingS = new CString[TotalUserIDHeading];

   UserIDPara_ID = new int[TotalUserIDHeading];
   POSITION pos = e->children.GetHeadPosition();
   while (pos)
   {
      CXmlElement * element = e->children.GetNext(pos);
      CString str=CVgaMenuItem ::LinearSearch(element->GetAttribute("textID"));
      Parameter_UserID_HeadingS[i]=str.SpanExcluding (_T("("));
      UserIDPara_ID[i] = _ttoi(element->GetAttribute("Value"));
      i++;
   }
}
/********************************************************************************************/
/* This function is called when the user clicks on the print button on compare graph screen	*/
/* The function makes a copy of the graphs displyed on the screen. This copy of the graphs	*/
/*is used for printing.																		*/
/********************************************************************************************/
void CChildView::CopyHSCScreenGraphs()
{
   POSITION pos = theApp.GraphsDataList.GetHeadPosition();
   int NoOfGraphs=0;
   while (pos)
   {
      CVgaDrawGraph *GraphA= new CVgaDrawGraph();
      CVgaDrawGraph::GraphCount--;
      CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
      obj->CopyGraph(GraphA);
      HSGraphPrintList.AddTail(GraphA);
      NoOfGraphs++;
   }
   switch(NoOfGraphs)
   {
   case 1:
      PrintInfoList.AddTail(HSCGRAPHONE);
      break;
   case 2:
      PrintInfoList.AddTail(HSCGRAPHTWO);
      break;
   case 3:
      PrintInfoList.AddTail(HSCGRAPHTHREE);
      break;
   case 4:
      PrintInfoList.AddTail(HSCGRAPHFOUR);
      break;
   }
}

/************************************************************************************************/
/* This function sends the host command to 332 to get all the values of the printing			*/
/* parameters. The function then stores these values to local variables so that they can be		*/
/* utilized.																					*/
/*1. The function is called on Power Up.														*/
/*2. The function is also called when Ext Preset is Off and Preset is changed.					*/
/*																								*/
/************************************************************************************************/
bool CChildView::GetPrintingParameters(bool InilitilizeBaseCount)
{
   bool RetVal = false;
   int length=0;

   unsigned char * data = (unsigned char *) &WeldSetup_Address;
   CHostCommand * request = new CHostCommand(PrintingParameter_FunId,0,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==ACK)
      {
         union {
            unsigned char CharData;
            bool BoolData;
         }u;
         if(InilitilizeBaseCount)
         {
            u.CharData=*data++;
            ExtPreset =u.BoolData;
            u.CharData=*data++;
            USBGlobalFlag=u.BoolData;
            length-=2;
            PowerSupply=CVgaMenuItem::GetPSString(data,length);

            ActSerialNumber=CVgaMenuItem::GetString(data,length);
            PresetBarCodeStart = CVgaMenuItem::GetString(data,length);

            USBWelddata.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBWelddata.USBSampleValue)
               USBWelddata.USBSampleDisable=true;
            else
               USBWelddata.USBSampleDisable=false;
            u.CharData=*data++;
            USBWelddata.USBOnAlarmValue=u.BoolData;

            USBPowerGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBPowerGraph.USBSampleValue)
               USBPowerGraph.USBSampleDisable=true;
            else
               USBPowerGraph.USBSampleDisable=false;
            u.CharData=*data++;
            USBPowerGraph.USBOnAlarmValue=u.BoolData;

            USBColDistance.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBColDistance.USBSampleValue)
               USBColDistance.USBSampleDisable=true;
            else
               USBColDistance.USBSampleDisable=false;
            u.CharData=*data++;
            USBColDistance.USBOnAlarmValue=	u.BoolData;

            USBVelocityGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBVelocityGraph.USBSampleValue)
               USBVelocityGraph.USBSampleDisable=true;
            else
               USBVelocityGraph.USBSampleDisable=false;
            u.CharData=*data++;
            USBVelocityGraph.USBOnAlarmValue=u.BoolData;

            USBForceGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBForceGraph.USBSampleValue)
               USBForceGraph.USBSampleDisable=true;
            else
               USBForceGraph.USBSampleDisable=false;
            u.CharData=*data++;
            USBForceGraph.USBOnAlarmValue=u.BoolData;

            USBAmplitudeGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBAmplitudeGraph.USBSampleValue)
               USBAmplitudeGraph.USBSampleDisable=true;
            else
               USBAmplitudeGraph.USBSampleDisable=false;
            u.CharData=*data++;
            USBAmplitudeGraph.USBOnAlarmValue=u.BoolData;

            USBFrequencyGraph.USBSampleValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            if(!USBFrequencyGraph.USBSampleValue)
               USBFrequencyGraph.USBSampleDisable=true;
            else
               USBFrequencyGraph.USBSampleDisable=false;
            u.CharData=*data++;
            USBFrequencyGraph.USBOnAlarmValue=u.BoolData;
            HistorySetUp = CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
            Setup.BaseCount=UniversalCount;
            PrintSequence.BaseCount=UniversalCount;
            Welddata.BaseCount=UniversalCount+1-Welddata.PrintSampleValue;
            WeldHistory.BaseCount=UniversalCount;
            PowerGraph.BaseCount=UniversalCount;
            ColDistance.BaseCount=UniversalCount;
            VelocityGraph.BaseCount=UniversalCount;
            ForceGraph.BaseCount=UniversalCount;
            AmplitudeGraph.BaseCount=UniversalCount;
            FrequencyGraph.BaseCount=UniversalCount;

            USBWelddata.BaseCount  = UniversalCount+1-USBWelddata.USBSampleValue;
            USBPowerGraph.BaseCount= UniversalCount;
            USBColDistance.BaseCount=UniversalCount;
            USBVelocityGraph.BaseCount=UniversalCount;
            USBForceGraph.BaseCount=UniversalCount;
            USBAmplitudeGraph.BaseCount=UniversalCount;
            USBFrequencyGraph.BaseCount=UniversalCount;
         }
         else
         {
            data+=(40);
            length-=(40);
         }

      }
      else
         RetVal = true;
      delete response;
   }
   else
   {
      Sleep(100);
      RetVal = true;
   }
   return (RetVal);
}

/************************************************************************************/
/* The followinf function is used prepare USB Folders List based on their hierarchy	*/
/* arg 1: Path of the USB folder													*/
/* arg 2: Hierarchy Level															*/
/************************************************************************************/
bool CChildView::PrepareUSBList(CString FilePath, int Fun_Id,int TitleID)
{
   char TempArray[10];
   CString Str_USBMemory=_itoa(TitleID,TempArray,10);
   Str_USBMemory=CVgaMenuItem ::LinearSearch(Str_USBMemory);
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CWeldingHistory::SelectedWeldData=1;
   CWeldingHistory::TopMostData=1;

   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;

   CString DirSpec;
   DirSpec=FilePath+_T("\\*");

   hFind = FindFirstFile(DirSpec, &FindFileData);

   CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
   while(menu->items.GetCount()>0)
   {
      CVgaMenuItem *Obj = menu->items.GetHead();
      int type = Obj->GetType();
      if((type==CVgaMenu::VGA_VGAEXITBUTTON)||(type==CVgaMenu::VGA_ALARMBUTTON)
         ||(type==CVgaMenu::BottomMenu_Id))
      {
         Obj->IsDraw=true;
         TempDataList.AddTail(Obj);
         menu->items.RemoveHead();
      }
      else
      {
         delete menu->items.RemoveHead();
      }
   }

   CVgaMenuItem * object =0;
   CString Title ;

   if((Fun_Id==FOLDERHIERARCHYONE)||(Fun_Id==USBPRESETFOLDER))
   {
      Title =	Str_USBMemory;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
      menu->items.AddTail(object);
   }

   else if(Fun_Id==FOLDERHIERARCHYTWO)
   {
      Title=CUSBFolder::SecondHierTitle;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
      menu->items.AddTail(object);
   }

   else if(Fun_Id==FOLDERHIERARCHYTHREE)
   {
      Title=CUSBFolder::ThirdHierTitle;
      object = new CVgaTitle(Title);
      object->SetType(CVgaMenu::TITLE);
      object->IsDraw=true;
      menu->items.AddTail(object);
   }

   page_no=ONE;

   if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolderName(FindFileData.cFileName, Fun_Id))
   {
      CUSBFolder  * object =0;
      object = new CUSBFolder(FindFileData.cFileName, FilePath+_T("\\")+FindFileData.cFileName,TitleID,Fun_Id);
      object->SetType(CVgaMenu::SUBMENU);
      object->IsDraw=true;
      object->RectShow=true;
      ((CUSBFolder*)object)->GetDiaplayName(Fun_Id);
      menu->items.AddTail(object);
   }
   while (FindNextFile(hFind, &FindFileData) != 0)
   {
      if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&ValidFolderName(FindFileData.cFileName, Fun_Id))
      {
         CUSBFolder  * object =0;
         object = new CUSBFolder(FindFileData.cFileName, FilePath+_T("\\")+FindFileData.cFileName,TitleID,Fun_Id);
         object->SetType(CVgaMenu::SUBMENU);
         object->IsDraw=true;
         object->RectShow=true;
         ((CUSBFolder*)object)->GetDiaplayName(Fun_Id);
         menu->items.AddTail(object);
      }
   }
   POSITION pos2 = TempDataList.GetHeadPosition();
   while(pos2)
   {
      CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
      menu->items.AddTail(Obj);
   }
   while(TempDataList.GetCount())
      TempDataList.RemoveHead();

   CChildView::RecalculateMenuItemsLayout(MAXSCRNButton_Height,menu);
   return true;
}

/************************************************************************************/
/* The following function is used to Check whether the passed File name is valid	*/
/* for the respectine hierarchy level.												*/
/* arg 1: File name to be checked													*/
/* arg 2: Hierarchy Level															*/
/************************************************************************************/
bool CChildView::ValidFolderName(CString FileName, int Fun_Id)
{
   //#ifdef _WIN32_WCE
   switch(Fun_Id)
   {
   case FOLDERHIERARCHYONE:
      {
         return true;
         break;
      }

   case FOLDERHIERARCHYTWO:
      {
         if(FileName.GetLength()!=YEARMONTHFOLDERNAME)
            return false;

         for(int i=0;i<YEARMONTHFOLDERNAME;i++)
         {
            if(i!=4)
               if(!((FileName.Mid(i,1)<='9') && (FileName.Mid(i,1)>='0')))
                  return false;
         }
         if(FileName.Mid(4,1)!="_")
            return false;
         else
            return true;
         break;
      }
   case FOLDERHIERARCHYTHREE:
      {
         if(FileName.GetLength()!=DATESIZE)
            return false;

         if(!((FileName.Mid(0,1)<='3') && (FileName.Mid(0,1)>='0')))
            return false;

         if(((FileName.Mid(0,1)=='3') && (FileName.Mid(1,1)>='2')))
            return false;

         if(!((FileName.Mid(1,1)<='9') && (FileName.Mid(1,1)>='0')))
            if(!((FileName.Mid(0,1)<'3')))
               return false;


         return true;

         break;
      }
   case FOLDERHIERARCHYFOUR:
      {

         break;
      }
   case USBPRESETFOLDER:
      {
         return true;
         break;
      }
   case USBPRESETSCRN:
      {

         if(FileName.Find(_T("Preset"),0)!=(-1))
         {
            if(FileName.GetLength()>10)
            {
			   int t =FileName.Find(L".prst",0);
               if(t!=(-1))
                  return true;
            }
         }
      }
      break;
   }
   //#endif
   return false;
}

/************************************************************************************/
/* The following function is used to write the Graph data to the USB Disk.			*/
/* the function checks the graph type and writes that graph in its respective file	*/
/*																					*/
/************************************************************************************/
bool CChildView::SendUSBGraphData()
{
   if(!USBGraphsList.GetCount())
      return false;

   if(!USBPresent())
   {
      if(USBGraphsList.GetCount())
         delete USBGraphsList.RemoveHead();
      return false;
   }

   CVgaDrawGraph *object = USBGraphsList.GetHead();

   CString Path = CurrentFilepath;
   char *TempBuf = NULL;
   CString FileName;
   int GraphType= object->GraphData.graph_type;
   switch(GraphType)
   {
   case DISTINGRAPH:
      FileName="ColDistGraph.log";
      break;

   case DISTMMGRAPH:
      FileName="ColDistGraph.log";
      break;

   case POWGRAPH:
      FileName="PowerGraph.log";
      break;

   case VELINGRAPH:
      FileName="VelocityGraph.log";
      break;

   case VELMMGRAPH:
      FileName="VelocityGraph.log";
      break;

   case FORCELBGRAPH:
      FileName="ForceGraph.log";
      break;

   case FORCENGRAPH:
      FileName="ForceGraph.log";
      break;

   case AMPLIGRAPH:
      FileName="AmpGraph.log";
      break;

   case FREQUGRAPH:
      FileName="FreqGraph.log";
      break;
   }
   CString GraphPath=	Path+FileName;

   CFile f;
   CFileException e;
   TRY
   {
      CVgaDrawGraph * tempGraph= new CVgaDrawGraph();
      int  size= sizeof(tempGraph->GraphData);
      delete tempGraph;
      char Comma=',';
      int TotalSize=sizeof(int)+sizeof(char)+size+sizeof(char);
      TempBuf =  new char[TotalSize];
      char *BufPtr = TempBuf;

      memcpy(BufPtr,&UniqueID,sizeof(int));
      BufPtr+=sizeof(int);
      memcpy(BufPtr,&Comma,sizeof(char));
      BufPtr+=sizeof(char);
      memcpy(BufPtr,&(object->GraphData),size);
      BufPtr+=size;
      memcpy(BufPtr,&Comma,sizeof(char));
      BufPtr+=sizeof(char);

      if( !f.Open( GraphPath, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
      {
         if(USBGraphsList.GetCount())
            delete USBGraphsList.RemoveHead();
         if(TempBuf)
            delete[] TempBuf;
         return false;
      }
      else
      {
         f.SeekToEnd();

         f.Write(TempBuf,TotalSize);
         f.Close();
         delete[] TempBuf;//coverity 12567
         if(USBGraphsList.GetCount())
            delete USBGraphsList.RemoveHead();
         return true;
      }

   }
   CATCH_ALL(E)
   {

      if (f.m_hFile != CFile::hFileNull)
         f.Close();
      if(TempBuf)
         delete[] TempBuf;
      ISUSBPresent=false;
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The data file could not be opened because of this error: ");
      x += szCause;
      ISUSBPresent = USBPresent();
      if(ISUSBPresent)
         USBMemoryFull = true;
      CChildView::ClearListOnUSBFullAlarm();
      AfxMsgBox(x);
      USBMemoryFull = false;
   }
   END_CATCH_ALL

      if(USBGraphsList.GetCount())
         delete USBGraphsList.RemoveHead();
   return false;
}

/************************************************************************************/
/* The following function is used when any graph on view Graph screen is to be		*/
/* printed. The function makes the copy of the graph object to be send for printing	*/
/*																					*/
/************************************************************************************/
CString CChildView::CopyScreenGraphs()
{
   CString SysPressureStr="";

   POSITION pos = theApp.GraphsDataList.GetHeadPosition();
   while (pos)
   {
      CVgaDrawGraph * obj = theApp.GraphsDataList.GetNext(pos);
      if((obj->GraphData.GraphRequestValue==GraphOneRequestValue)||
         (obj->GraphData.GraphRequestValue==GraphTwoRequestValue)||AutoRefreshon)
      {
         CVgaDrawGraph *GraphA= new CVgaDrawGraph();
         CVgaDrawGraph::GraphCount--;
         obj->CopyGraph(GraphA);

         GraphPrintList.AddTail(GraphA);
         SysPressureStr="";
         for(int i=0;i<20;i++)
         {
            if(GraphA->GraphData.SystemPressure[i]=='\0')
               break;
            SysPressureStr+=GraphA->GraphData.SystemPressure[i];
         }
      }

   }
   return SysPressureStr;
}


/************************************************************************************/
/* The following function is used to write event log to Disk. The function gets	    */
/* the path of the file by calling function GetCurrentFilePath() and writes  event  */
/* data in Event log.log. the file is created if not already present.				*/
/*																					*/
/************************************************************************************/

bool CChildView::SendUSBEventLogs()
{

   int  size= sizeof(CEventHistoryData);
   int TotalSize = sizeof(char) + size;// <EventRecord{n},>
   unsigned long HeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
   UINT32 TotalObjectCount = 0,WriteObjectIndex = 0;
   bool RetVal = false;
   //printf("\n SendDiskLogData");
   CString Path = DISK;
   CString	pFileName = Path+"EventLog.log";
   CFile f;
   CFileException e;

   if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {
      RetVal = false;
#ifdef _DEBUG
      if(e.m_cause==CFileException::generic)
         TRACE(_T("\n !! GENERIC"));
      else if(e.m_cause==CFileException::badPath)
         TRACE(_T("\n !! bad path"));
      else if(e.m_cause==CFileException::tooManyOpenFiles )
         TRACE(_T("\n !! too many files open"));
      else if(e.m_cause==CFileException::fileNotFound )
         TRACE(_T("\n !! file not found"));
      else if(e.m_cause==CFileException::accessDenied )
         TRACE(_T("\n !! access denied"));
      else if(e.m_cause==CFileException::diskFull)
         TRACE(_T("\n !! disc full"));
      else if(e.m_cause==CFileException::invalidFile)
         TRACE(_T("\n !! invalid file"));
      afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
   }
   else
   {
      if(EventHistoryList.GetCount())
      {
         char *TempBuf =  new char[TotalSize];
         char *BufPtr = TempBuf;
         CEventHistoryData * ReadObject = EventHistoryList.GetHead();
         char Comma = ',';

         f.SeekToBegin(); // Read the Saved Counters
         f.Read(&TotalObjectCount,sizeof(UINT32));
         f.Read(&Comma,sizeof(char));
         f.Read(&WriteObjectIndex,sizeof(UINT32));
         f.Read(&Comma,sizeof(char));

         //Write Data
         memcpy(BufPtr,ReadObject,size);
         BufPtr+=size;

         Comma = ',';
         //copy Comma to buffer
         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);

         f.Seek(HeaderSize+(WriteObjectIndex*TotalSize),CFile::begin);
         f.Write(TempBuf,TotalSize);
         TotalObjectCount = ++CEventLog::SuccessfullyWrittenEventRecord;
         WriteObjectIndex = CEventLog::SuccessfullyWrittenEventRecord % MAX_ALLOWED_EVENT_LOG;
         if(WriteObjectIndex == 0) CEventLog::CurrentDisplayEventCount = 0;

         // printf("\nEvent %d Is written to File at %d \n",CEventLog::SuccessfullyWrittenEventRecord,WriteObjectIndex);
         CEventLog::CurrentDisplayEventCount = WriteObjectIndex;
         f.SeekToBegin();
         f.Write(&TotalObjectCount,sizeof(UINT32));
         f.Write(&Comma,sizeof(char));
         f.Write(&WriteObjectIndex,sizeof(UINT32));
         f.Write(&Comma,sizeof(char));
         f.Close();
         CEventLog::CurrentDisplayEventCount = WriteObjectIndex;
         printf("\nEvent %d Is written to File at %d \n",CEventLog::SuccessfullyWrittenEventRecord,WriteObjectIndex);

         delete[] TempBuf;
         delete EventHistoryList.RemoveHead();
         RetVal = true;
      }
      else
         RetVal =  false;

   }
   return RetVal;
}




/************************************************************************************/
/* The following function is used to write Weld data to Disk. The function gets	    */
/* the path of the file by calling function GetCurrentFilePath() and writes the weld*/
/* data in Weld Data.log. the file is created if not already present.				*/
/*																					*/
/************************************************************************************/

bool CChildView::SendLOGWeldData()
{
   UINT32 TotalObjectCount = 0,/*TotalHeaderCount*/WriteObjectIndex = 0;
   unsigned long StartOffset = 2*(sizeof(char) + sizeof(UINT32)) + 2*(MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR)) + sizeof(char);

   CString PathStr = DISK;
   CString	pFileName=PathStr + "WeldData.log";

   CFile f;
   bool flag =false;
   CFileException e;

   if(!LOGHistoryList.GetCount())
      return false;

   CHistoryData *object1 = LOGHistoryList.GetHead();
   CHistoryData *object = new CHistoryData();

   memcpy(object,object1,sizeof(CHistoryData));

   TRY
   {
      if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
      {

#ifdef _DEBUG
         if(e.m_cause==CFileException::generic)
            TRACE(_T("\n !! GENERIC"));
         else if(e.m_cause==CFileException::badPath)
            TRACE(_T("\n !! bad path"));
         else if(e.m_cause==CFileException::tooManyOpenFiles )
            TRACE(_T("\n !! too many files open"));
         else if(e.m_cause==CFileException::fileNotFound )
            TRACE(_T("\n !! file not found"));
         else if(e.m_cause==CFileException::accessDenied )
            TRACE(_T("\n !! access denied"));
         else if(e.m_cause==CFileException::diskFull)
            TRACE(_T("\n !! disc full"));
         else if(e.m_cause==CFileException::invalidFile)
            TRACE(_T("\n !! invalid file"));
         afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		 delete object;//coverity 12573
      }
      else
      {

         char Comma =',';
         bool OldUnits;
         bool USBMetric=metric;
         printf("%d",TotalObjectCount);
         if(f.GetLength() == 0)
            printf("Error: File	Invalid\n");
         else if(f.GetLength()==StartOffset)
         {
            UniqueID =1;
            f.SeekToBegin();
            char NextComma;
            f.Read(&TotalObjectCount,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
            f.Read(&WriteObjectIndex/*TotalHeaderCount*/,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
         }
         else
         {
            f.SeekToBegin();
            char NextComma = 0;
            f.Read(&TotalObjectCount,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
            f.Read(&WriteObjectIndex/*TotalHeaderCount*/,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
            if(TotalObjectCount)
            {
               CHistoryData *TempObj = new CHistoryData();
               int ObjectSize =sizeof(CHistoryData) +sizeof(Comma);
               ObjectSize=(-ObjectSize);
               f.Seek(ObjectSize,CFile::end);
               f.Read(TempObj,sizeof(CHistoryData));
               UniqueID=TempObj->UniqueId;
               UniqueID++;
               OldUnits= TempObj->Units;
               delete TempObj;
            }
         }
         object->UniqueId=UniqueID;

         int  size= sizeof(CHistoryData);
         int TotalSize = sizeof(int)+sizeof(char)+sizeof(bool)+sizeof(char)+size+sizeof(char);
         //			if(OldUnits!=metric)
         //				TotalSize += (MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR));

         char *TempBuf =  new char[TotalSize];
         char *BufPtr = TempBuf;

         memcpy(BufPtr,&UniqueID,sizeof(int));
         BufPtr+=sizeof(int);
         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);
         memcpy(BufPtr,&metric,sizeof(bool));
         BufPtr+=sizeof(bool);

         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);

         memcpy(BufPtr,object,size);
         BufPtr+=size;

         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);

         delete object;

         f.Seek(StartOffset+((WriteObjectIndex)*TotalSize),CFile::begin);
         f.Write(TempBuf,TotalSize);
         BufPtr = TempBuf;

         TotalObjectCount = TotalObjectCount+ 1;
         WriteObjectIndex = (TotalObjectCount) % CChildView::Max_Allowed_Weld_Log ;
         CWeldingHistory::CurrentDisplayWeldCount = WriteObjectIndex;
         char NextComma = ',';
         int ByteCount = 0;

         memcpy(BufPtr,&TotalObjectCount,sizeof(UINT32));
         ByteCount+=sizeof(UINT32);
         BufPtr+=sizeof(UINT32);

         memcpy(BufPtr,&NextComma,sizeof(char));
         ByteCount+=sizeof(char);
         BufPtr+=sizeof(char);

         memcpy(BufPtr,&WriteObjectIndex/*TotalHeaderCount*/,sizeof(UINT32));
         ByteCount+=sizeof(UINT32);
         BufPtr+=sizeof(UINT32);

         memcpy(BufPtr,&NextComma,sizeof(char));
         ByteCount+=sizeof(char);
         BufPtr+=sizeof(char);

         f.SeekToBegin(); //Add updated count
         f.Write(TempBuf,ByteCount);
         f.Close();
         CWeldingHistory::CurrentDisplayWeldCount = WriteObjectIndex;
         //printf("\nHistory %d Is written to File at %d \n", CWeldingHistory::thisHisPtr->TotalDataInFile,WriteObjectIndex);
         delete[] TempBuf;

      }
   }
   CATCH_ALL(E)
   {
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The data file could not be opened because of this error in WeldData.log: ");
      x += szCause;
      ISUSBPresent=false;
      flag =true;
      SBCDiskFull = true;
      AfxMsgBox(x);
      SBCDiskFull = false;
   }
   END_CATCH_ALL

      if(flag)
      {
         if(LOGHistoryList.GetCount())
         {
            LOGHistoryList.RemoveHead();
         }
         return false;
      }
      else
      {
         if(LOGHistoryList.GetCount())
         {
            delete LOGHistoryList.RemoveHead();
         }
         return true;
      }
      return true;
}





/************************************************************************************/
/* The following function is used to write Weld data to USB Disk. The function gets	*/
/* the path of the file by calling function GetCurrentFilePath() and writes the weld*/
/* data in Weld Data.log. the file is created if not already present.				*/
/*																					*/
/************************************************************************************/

bool CChildView::SendUSBWeldData()
{
   printf("CChildView::SendUSBWeldData()\n");

   char *TempBuf1 = NULL;

   if(!USBHistoryList.GetCount())
      return false;

   if(!USBPresent())
   {
      if(USBHistoryList.GetCount())
         delete USBHistoryList.RemoveHead();
      return false;
   }

   CString	pFileName = "";
   CHistoryData *object1 = USBHistoryList.GetHead();
   CHistoryData *object = NULL;

   object = new CHistoryData();
   memcpy(object,object1,sizeof(CHistoryData));
   CurrentFilepath = GetCurrentFilePath(object);
   pFileName=CurrentFilepath + "WeldData.log";
   CreateFolder(false);

   CFile f;
   bool flag =false;
   CFileException e;
   //	printf("\n SendUsbWeldData %s ", pFileName);
   TRY
   {
      if( !f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
      {

#ifdef _DEBUG
         if(e.m_cause==CFileException::generic)
            TRACE(_T("\n !! GENERIC"));
         else if(e.m_cause==CFileException::badPath)
            TRACE(_T("\n !! bad path"));
         else if(e.m_cause==CFileException::tooManyOpenFiles )
            TRACE(_T("\n !! too many files open"));
         else if(e.m_cause==CFileException::fileNotFound )
            TRACE(_T("\n !! file not found"));
         else if(e.m_cause==CFileException::accessDenied )
            TRACE(_T("\n !! access denied"));
         else if(e.m_cause==CFileException::diskFull)
            TRACE(_T("\n !! disc full"));
         else if(e.m_cause==CFileException::invalidFile)
            TRACE(_T("\n !! invalid file"));
         afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
      }
      else
      {

         char Comma =',';//Coverty Issue OldValue not used

         UINT32 TotalObjectCount = 0,WriteObjectIndex =0,ByteCount = 0;
         int UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
         int HeaderObjectSize = sizeof(char) + sizeof(UINT32) + sizeof(char) + sizeof(UINT32);
         int size = sizeof(CHistoryData);
         int TotalSize = sizeof(int)+sizeof(char)+sizeof(bool)+sizeof(char)+size+sizeof(char);
         int HeaderSize = HeaderObjectSize+2*UnitObjectSize+sizeof(char);

         unsigned long Size = (unsigned long)f.GetLength();
         if(Size == 0)
         {
            unsigned char *  TempBuf = new unsigned char[HeaderObjectSize+2*UnitObjectSize+1];
            unsigned char * BufPtr = TempBuf;
            char NextComma = ',';
            CString UnitUSCS,UnitMetrics;
            int i;
            for(int k=0;k<CChildView::TotalTextHeading;k++)
            {
               UnitMetrics =CChildView::Parameter_Units_Metric[k];
               UnitUSCS =CChildView::Parameter_Units_USCS[k];
               for( i=0;i<UnitMetrics.GetLength();i++)
               {
                  CWeldingHistory::ParameterUnitMetric[k][i] = UnitMetrics.GetAt(i);
                  CWeldingHistory::ParameterUnitMetric[k][i+1]='\0';
               }
               for( i=0;i<UnitUSCS.GetLength();i++)
               {
                  CWeldingHistory::ParameterUnitUSCS[k][i] = UnitUSCS.GetAt(i);
                  CWeldingHistory::ParameterUnitUSCS[k][i+1]='\0';
               }
            }
            memcpy(BufPtr,&TotalObjectCount,sizeof(UINT32));	//4+0 = 4
            ByteCount+=sizeof(UINT32);
            BufPtr+=sizeof(UINT32);
            memcpy(BufPtr,&NextComma,sizeof(char));				//4+1 = 5
            ByteCount+=sizeof(char);
            BufPtr+=sizeof(char);
            memcpy(BufPtr,&WriteObjectIndex,sizeof(UINT32));	//5+4 = 9
            ByteCount+=sizeof(UINT32);
            BufPtr+=sizeof(UINT32);
            memcpy(BufPtr,&NextComma,sizeof(char));				//9+1 = 10
            ByteCount+=sizeof(char);
            BufPtr+=sizeof(char);
            memcpy(BufPtr,&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);	//350+10 = 360
            BufPtr+=UnitObjectSize;
            ByteCount+=UnitObjectSize;
            memcpy(BufPtr,&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);	//360+350 = 710
            BufPtr+=UnitObjectSize;
            ByteCount+=UnitObjectSize;
            memcpy(BufPtr,&NextComma,sizeof(char));										//710+1 = 711
            ByteCount+=sizeof(char);													//HeaderSize
            BufPtr+=sizeof(char);
            f.Write(TempBuf,ByteCount);
            UniqueID =1;
            delete[] TempBuf;
         }
         else
         {
            f.SeekToBegin();
            char NextComma;
            f.Read(&TotalObjectCount,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
            f.Read(&WriteObjectIndex,sizeof(UINT32));
            f.Read(&NextComma,sizeof(char));
            if(TotalObjectCount)
            {
               CHistoryData *TempObj = new CHistoryData();
               //int ObjectSize =sizeof(CHistoryData) +sizeof(Comma);
               f.Seek(HeaderSize + (TotalSize*(TotalObjectCount-1))+7,CFile::begin); //read the last object
               f.Read(TempObj,sizeof(CHistoryData));

               UniqueID=TempObj->UniqueId;
               UniqueID++;//Coverity Issue OldValue not used
               delete TempObj;
            }

         }
         f.Close();

         //		object->UniqueId=UniqueID;

         TempBuf1 =  new char[TotalSize];
         char *BufPtr = TempBuf1;

         memcpy(BufPtr,&UniqueID,sizeof(int));
         BufPtr+=sizeof(int);
         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);
         memcpy(BufPtr,&metric,sizeof(bool));
         BufPtr+=sizeof(bool);

         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);
         object->UniqueId = UniqueID;
         memcpy(BufPtr,object,size);
         BufPtr+=size;

         memcpy(BufPtr,&Comma,sizeof(char));
         BufPtr+=sizeof(char);

         if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
         {
            //f.SeekToEnd();
            f.Seek((HeaderSize) + (TotalSize*TotalObjectCount),CFile::begin);
            printf("\n write whole data to USB");
            f.Write(TempBuf1,TotalSize);
            f.SeekToBegin();
            TotalObjectCount++;
            f.Write(&TotalObjectCount,sizeof(UINT32));
            f.Close();

         }
         delete[] TempBuf1;

      }
   }
   CATCH_ALL(E)
   {

      if (f.m_hFile != CFile::hFileNull)
         f.Close();
      if(TempBuf1)
         delete[] TempBuf1;
      TCHAR  szCause[255];
      E->GetErrorMessage(szCause, 255);
      CString x;
      x = _T("The data file could not be opened because of this error: ");
      x += szCause;
      ISUSBPresent=false;
      flag =true;
      ISUSBPresent=USBPresent();
      if(ISUSBPresent)
         USBMemoryFull = true;
      CChildView::ClearListOnUSBFullAlarm();
      AfxMsgBox(x);
      USBMemoryFull = false;
   }
   END_CATCH_ALL
      delete object;

   if(flag)
   {
      if(USBHistoryList.GetCount())
      {
         delete USBHistoryList.RemoveHead();
      }
      return false;
   }
   else
   {
      if(USBHistoryList.GetCount())
      {
         delete USBHistoryList.RemoveHead();
      }
      return true;
   }
}


/********************************************************************************/
/* The following function is called to check whether the passed DataID( can be	*/
/* weld data, any graph data) is required for any particular weld cycle. The	*/
/* function  returns true if data is required and false if not.					*/
/********************************************************************************/
bool CChildView::DataForUSB(int DataId)
{
   if((!ISUSBPresent)||(!USBGlobalFlag))
   {
      //printf("DataForUSB#1 \n");
      return false;
   }
   //printf("DataForUSB#2 \n");
   switch(DataId)
   {
   case WELDDATAONSAMPLEID:
      {
         //printf("DataForUSB#3 \n");
         if((PresentAlarmCount) && (USBWelddata.USBOnAlarmValue))
         {
            //printf("DataForUSB#3end \n");
            return true;
         }
         //printf("DataForUSB#4 \n");
         if(!USBWelddata.USBSampleDisable)
            if((PresentWeldCount-USBWelddata.BaseCount)>=USBWelddata.USBSampleValue)
            {
               //printf("DataForUSB#4end \n");
               return true;
            }
      }
      break;
   case COLDISTANCEID:
      {
         //printf("DataForUSB#5 \n");
         if((PresentAlarmCount) && (USBColDistance.USBOnAlarmValue))
         {
            return true;
            //printf("DataForUSB#6 \n");
         }
         else if(!USBColDistance.USBSampleDisable)
            if((((PresentWeldCount-USBColDistance.BaseCount)%(USBColDistance.USBSampleValue))==1)
               ||((PresentWeldCount-USBColDistance.BaseCount)==1)||(USBColDistance.USBSampleValue==1))
               return true;

         //printf("DataForUSB#7 \n");
      }
      break;
   case VELOCITYGRAPHID:
      {
         //printf("DataForUSB#8 \n");
         if((PresentAlarmCount) && (USBVelocityGraph.USBOnAlarmValue))
            return true;
         else if(!USBVelocityGraph.USBSampleDisable)
            if((((PresentWeldCount-USBVelocityGraph.BaseCount)%(USBVelocityGraph.USBSampleValue))==1)
               ||((PresentWeldCount-USBVelocityGraph.BaseCount)==1)||(USBVelocityGraph.USBSampleValue==1))
               return true;
         //printf("DataForUSB#9 \n");
      }
      break;
   case FORCEGRAPHID:
      {
         if((PresentAlarmCount) && (USBForceGraph.USBOnAlarmValue))
            return true;
         else if(!USBForceGraph.USBSampleDisable)
            if((((PresentWeldCount-USBForceGraph.BaseCount)%(USBForceGraph.USBSampleValue))==1)
               ||((PresentWeldCount-USBForceGraph.BaseCount)==1)||(USBForceGraph.USBSampleValue==1))
               return true;
      }
      break;
   case AMPLITUDEGRAPHID:
      {
         if((PresentAlarmCount) && (USBAmplitudeGraph.USBOnAlarmValue))
            return true;
         else if(!USBAmplitudeGraph.USBSampleDisable)
            if((((PresentWeldCount-USBAmplitudeGraph.BaseCount)%(USBAmplitudeGraph.USBSampleValue))==1)
               ||((PresentWeldCount-USBAmplitudeGraph.BaseCount)==1)||(USBAmplitudeGraph.USBSampleValue==1))
               return true;
      }
      break;
   case POWERGRAPHID:
      {
         if((PresentAlarmCount) && (USBPowerGraph.USBOnAlarmValue))
            return true;
         else if(!USBPowerGraph.USBSampleDisable)
            if((((PresentWeldCount-USBPowerGraph.BaseCount)%(USBPowerGraph.USBSampleValue))==1)
               ||((PresentWeldCount-USBPowerGraph.BaseCount)==1)||(USBPowerGraph.USBSampleValue==1))
               return true;
      }
      break;
   case FREQUENCYGRAPHID:
      {
         if((PresentAlarmCount) && (USBFrequencyGraph.USBOnAlarmValue))
            return true;
         else if(!USBFrequencyGraph.USBSampleDisable)
            if((((PresentWeldCount-USBFrequencyGraph.BaseCount)%(USBFrequencyGraph.USBSampleValue))==1)
               ||((PresentWeldCount-USBFrequencyGraph.BaseCount)==1)||(USBFrequencyGraph.USBSampleValue==1))
               return true;
      }
      break;
   }
   //printf("DataForUSB#end \n");
   return false;
}

/************************************************************************/
/* The function is called when data for USB is ready to be written		*/
/* to USB Disk. The function calls SendUSBWeldData(),SendUSBGraphData()	*/
/* for writing wEld data and Graph data respectively.					*/
/************************************************************************/
UINT CChildView::WriteDataToUSB(LPVOID)
{
   CString DiskStr;
   int TempEvent = 0;
   int TempWeld = 0;
   int NWcDiskCheckDiskCnt = 100, NUsbDiskCheckCnt = 100;//counts to decide how often we should check for available space on disks
   while(1)
   {
      {

         HANDLE handle;
		 TempWeld = 0;
		 TempEvent = 0;
         handle = thisPtr->WaitForUSBData;
         WaitForSingleObject(handle, INFINITE);
         int NoOfLOGWeldData = (int)thisPtr->LOGHistoryList.GetCount();
		 int NoOfLOGEventData = (int)thisPtr->EventHistoryList.GetCount();
         for(int WeldData1 = 0 ; WeldData1 < NoOfLOGWeldData ; WeldData1++)
		 {
            thisPtr->SendLOGWeldData();
			TempWeld++;
			NWcDiskCheckDiskCnt--;
			Sleep(1);
		 }

         int NoOfWeldData = thisPtr->USBHistoryList.GetCount();

         if(thisPtr->USBPresent())
         {
            for(int WeldData=0;WeldData<NoOfWeldData;WeldData++)
            {
               thisPtr->SendUSBWeldData();
			   NUsbDiskCheckCnt--;
               int NoOfGraphs=thisPtr->USBGraphCountList.RemoveHead();

               for(int i=0; i < NoOfGraphs;i++){
                  thisPtr->SendUSBGraphData();
				  Sleep(1);
			   }
			   Sleep(1);
            }

         }
         else /*case USB not present:: deleting USB graph list and weld data list*/
         {
            thisPtr->USBMutex.Lock();
            while (thisPtr->USBHistoryList.GetCount())
               delete thisPtr->USBHistoryList.RemoveHead();

            while(thisPtr->USBGraphsList.GetCount())
               delete thisPtr->USBGraphsList.RemoveHead();

            thisPtr->USBGraphCountList.RemoveAll();
            thisPtr->USBMutex.Unlock();

         }

         for(int j = 0; j < NoOfLOGEventData; j++)
		 {
            thisPtr->SendUSBEventLogs();
			TempEvent++;
			Sleep(1);
		 }

		 if(TempWeld > 0)
		 {
		    UpDateWeldHiddenFile(TempWeld);
			Sleep(1);
		 }

		 if(TempEvent > 0)
		 {
		    UpdateEventHiddenFile(TempEvent);
			Sleep(1);
		 }

        if(!thisPtr->EventHistoryList.GetCount() && !thisPtr->LOGHistoryList.GetCount()
            && !thisPtr->USBHistoryList.GetCount())
            thisPtr->WaitForUSBData.ResetEvent();
		if(NWcDiskCheckDiskCnt <= 0)
		{
		   NWcDiskCheckDiskCnt = 100;
		   CheckAvailablDiskSpace();
		   Sleep(1);
		}
		if(NUsbDiskCheckCnt <= 0)
		{
			DiskStr = USBDISK;
			NUsbDiskCheckCnt = 100;
			CheckAvailablDiskSpace(DiskStr);
		}
     }
   }
}
/******************************************************************/
/*  This Function will handle Alarm change in polling command.    */
/******************************************************************/
bool CChildView::HandleAlarmChange()
{
   bool drawAlarmButn = true;
   CVgaMenu * menu;
   CVgaMenuItem *object;
   menu=theApp.MenuPointer;
   POSITION pos1=menu->items.GetHeadPosition();
   while (pos1)
   {
      object= menu->items.GetNext(pos1);
      if(object->GetType() == CVgaMenu::TITLE)
      {
         CVgaTitle *ptr=(CVgaTitle *)object;
         drawAlarmButn = ptr->DrawAlarmButton;
      }
   }
   if((TemporaryAlarmCount != AlarmCount)||((AlarmUpdateRequired==false)&&(AlarmCount!=0)))
   {
      if((IsAlarmScreen ==true)&&(TemporaryAlarmCount!=AlarmCount))//Already on Alarm Screen
      {         													 //and alarm count change
         if(TemporaryAlarmCount==0)//Alarm Count Changes to zero.
         {
            AlarmCount = TemporaryAlarmCount;
            page_no=1;
            IsAlarmScreen = false;
			//Simulate main menu click and jump to main menu. This is the fix for state machine not restarting from
			//scrrens where we disable them and alarm comes.
			if(CVgaBottomMenu::SendCommandForBottomMenu(CVgaBottomMenu::mainMenuCommandID,(int)this))
			{
				if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
				{
					OnKeypadScreen_flag=false;
					CChildView::thisPtr->IsAlarmScreen =false;
					CChildView::RunResultScreen=false;
					CBottomHalf::HornDownScreenPresent=false;
					CChildView::thisPtr->PMCScreen=false;
					CChildView::AccessLevelSystem=USER_OPERATOR;
					menusname.AddTail(theApp.menuName);
					menus.AddTail(page_no);
					menupointers.AddTail(theApp.MenuPointer);
					page_no = 1;
					theApp.menuName = CVgaBottomMenu::mainMenuID;
					theApp.MenuPointer=menu;
					ModifyObjectList(menu);
					Invalidate();
				}
			}
         }
         else //Alarm Count Changes but not equal to zero.
         {
            AlarmCount = TemporaryAlarmCount;
            page_no=1;
            if(theApp.menuName==CVgaBottomMenu::WeldResults_ID)
               CChildView::thisPtr->RunResultScreen=true;
            ModifyObjectList(theApp.MenuPointer);
            IsAlarmScreen =true;
            AlarmUpdateRequired=false;
            Invalidate();
            return true;
         }

      }
      /*Alarm count changes but  user is not on Alarm Screen.*/
      else if(IsAlarmScreen ==false)
      {
         CDC*pDC=GetDC();
         AlarmCount = TemporaryAlarmCount;
         if(TemporaryAlarmCount!=0)
         {
            if(AlarmUpdateRequired==false)
            {
               if(ScreenSetupFlag)
                  return false;
            }
            if(drawAlarmButn == false)
               return false;
            AlarmUpdateRequired=true;
            GlobalAlarmObject->SetText(GetAlarmString(GlobalAlarmObject));
            GlobalAlarmObject->Draw(pDC);
         }
         else
         {
            AlarmUpdateRequired=false;
            if(ScreenSetupFlag || (drawAlarmButn==false))
               return false;
            if((theApp.GraphsDataList.GetCount()==0))
               CVgaMenuItem::DrawRect(pDC,CChildView::TitleBarColor, ALARMBUTTONRECT_RE);
            else
            {
               Invalidate();
            }
         }
         ReleaseDC(pDC);
      }

   }
   return false;
}

UINT CChildView::EtherNetAndAlarmHandle(LPVOID)
{
   while(1)
   {
      HANDLE handle;
      handle = thisPtr->WaitForEtherNetAlarmHandle;
      WaitForSingleObject(handle, INFINITE);

      //	printf("\nEtherNetAndAlarmHandle thread");
      if(thisPtr->StartWeldData==1)
      {
         thisPtr->StartWeldData=0;

         if(app->ether->clients.GetUpperBound() != -1)//>0
         {
            int length = 0;//length of pointer to be send to 332.
            CHostCommand * request = new CHostCommand(GetWeldData, 0,length);
            CHostCommand * response = app->SendEnHostCommand(request);
            if (response)
            {
               length=response->GetBufLength();
               unsigned char * buf =  response->GetBuffer();
               app->SendWeldData(buf,length);
               delete response;
            }

         }

      }
      thisPtr->HandleAlarmChange();
      thisPtr->WaitForEtherNetAlarmHandle.ResetEvent();
   }
   return 0;
}

/************************************************************************/
/* The followinf function checks for all the conditions that should be	*/
/* true for printing data.they are:										*/
/* 1. Printing On/Off													*/
/* 2. Printer present/not												*/
/* 3. Weld count !=0													*/
/* 4. Abort printing not pressed										*/
/************************************************************************/
bool CChildView::CheckForPrinting()
{

   return false;

}
/************************************************************************/
/* The following function is used to Set The request value for Graphs	*/
/* and weld data that is needed to get the data from 332.				*/
/* arg 1: Pointer to TotalGraphRequestValue								*/
/* arg 2: Total no. of graphs rewuired for present weld cycle			*/
/* arg 3: Graph ID														*/
/* arg 4: Graph request value for this Graph ID							*/
/* arg 5: Pointer to the structure for this Graph Printing Parameters	*/
/************************************************************************/
void CChildView::SetRequestValue(int *TotalGraphRequestValue, int *TotalGraph, int ID,int CurrentGraphRequestValue, PrintValues *CurrentGraph)
{
   if(((PresentAlarmCount) && (CurrentGraph->PrintOnAlarmValue)&&(CheckForPrinting())) ||(DataForUSB(ID)))
   {
      (*TotalGraphRequestValue)+=CurrentGraphRequestValue;
      (*TotalGraph)++;
   }
   else if((!CurrentGraph->PrintSampleDisable)&&(CheckForPrinting()))
      if((((PresentWeldCount-CurrentGraph->BaseCount)%(CurrentGraph->PrintSampleValue))==1)
         ||((PresentWeldCount-CurrentGraph->BaseCount)==1)||(CurrentGraph->PrintSampleValue==1))
      {
         (*TotalGraphRequestValue)+=CurrentGraphRequestValue;
         (*TotalGraph)++;
      }
}

/****************************************************************************/
/* The following function returns the current working directory For the		*/
/* USB Disk. the function checks for the current date, year and power supply*/
/* name and creates the path accordingly.									*/
/****************************************************************************/

CString CChildView::GetCurrentFilePath(char *filename)
{

   CString PathStr = USBDISK + PowerSupply + "\\" + CString(filename);

   /* getting current date, month and year*/
   int temp=0;
   char HHMMSS[7];//HHMMSS[6];
   char DDMMYY[7]; //DDMMYY[6];
   char YY[5];//YY[4];
   int i = 0;
   int j = 0;
   SYSTEMTIME SysTime;
   GetLocalTime(&SysTime);
   if(SysTime.wDay<10)
   {
      DDMMYY[0]='0';
      _itoa(SysTime.wDay,DDMMYY+1,10);
   }
   else
      _itoa(SysTime.wDay,DDMMYY,10);

   if(SysTime.wMonth<10)
   {
      DDMMYY[2]='0';
      _itoa(SysTime.wMonth,DDMMYY+3,10);
   }
   else
      _itoa(SysTime.wMonth,DDMMYY+2,10);

   _itoa(SysTime.wYear,YY,10);
   YY[4]='\0';

   DDMMYY[4] = YY[2];
   DDMMYY[5] = YY[3];
   DDMMYY[6]='\0';
   if(!CChildView::metric)
   {
      temp=DDMMYY[0];
      DDMMYY[0]=DDMMYY[2];
      DDMMYY[2]=temp;
      temp=DDMMYY[1];
      DDMMYY[1]=DDMMYY[3];
      DDMMYY[3]=temp;
   }

   YearMonthName = "";
   for(i=0;i<6;i++)
   {
      YearMonthName += DDMMYY[i];
      PathStr+= DDMMYY[i];
   }

   if(SysTime.wHour<10)
   {
      HHMMSS[0]='0';
      _itoa(SysTime.wHour,HHMMSS+1,10);

   }
   else
      _itoa(SysTime.wHour,HHMMSS,10);

   if(SysTime.wMinute<10)
   {
      HHMMSS[2]='0';
      _itoa(SysTime.wMinute,HHMMSS+3,10);
   }
   else
      _itoa(SysTime.wMinute,HHMMSS+2,10);

   if(SysTime.wSecond<10)
   {
      HHMMSS[4]='0';
      _itoa(SysTime.wSecond,HHMMSS+5,10);
   }
   else
      _itoa(SysTime.wSecond,HHMMSS+4,10);
   HHMMSS[6]='\0';

   Time = "";
   for(j=0;j<6;j++)
   {
      Time += HHMMSS[j];
      PathStr+= HHMMSS[j];
   }

   PathStr+=".pdf";
   return PathStr;
}

CString CChildView::GetCurrentFilePath(CHistoryData *object)
{

   CString PathStr = USBDISK + PowerSupply + "\\";

   CString TempDate = object->USBDateStr;
   int i = 0;
   int j =0;
   CString Year = TempDate.Right(2);
   CString Day,Month;

   if(CChildView::metric)
   {
      Day = TempDate.Left(2);
      Month= TempDate.Mid(3,2);
   }
   else
   {
      Month = TempDate.Left(2);
      Day = TempDate.Mid(3,2);
   }

   /* getting current date, month and year*/
   char YYYY_MM[YEARMONTHFOLDERNAME+1];
   char DD[3];
   int count = 0;

   YYYY_MM[count]='2';
   count++;
   YYYY_MM[count]='0';
   count++;

   for(j=0;j<Year.GetLength();j++)
   {
      YYYY_MM[count]= (char)Year.GetAt(j);
      count++;
   }

   YYYY_MM[count]='_';
   count++;
   for(j=0;j<Month.GetLength();j++)
   {
      YYYY_MM[count]= (char)Month.GetAt(j);
      count++;
   }

   YYYY_MM[count]='\0';

   for(j=0;j<Day.GetLength();j++)
   {
      DD[j] = (char)Day.GetAt(j);
   }
   DD[2]='\0';

   YearMonthName="";
   Date="";
   for(i=0;i<YEARMONTHFOLDERNAME;i++)
   {
      YearMonthName += YYYY_MM[i];
      PathStr+= YYYY_MM[i];
   }

   PathStr+="\\";

   for(i=0;i<DATESIZE;i++)
   {
      PathStr+= DD[i];
      Date+= DD[i];
   }
   PathStr+="\\";
   return PathStr;
}


/************************************************************************/
/* The following function is used to Get the Power Suply name from 332.	*/
/* the function is called at the Power up and when power supply name	*/
/* is changed.															*/
/************************************************************************/
void CChildView::GetPowerSupplyName()
{
   PowerSupply="";
   int length=0;
   unsigned char * data = (unsigned char *) &WeldSetup_Address;
   CHostCommand * request = new CHostCommand(PowerSupply_FunId,0,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      data--;
      length = response->GetDataLength();
      if(ch==ACK)
      {
         for(int	i=0;i<PSNAMELENGTH;i++)
         {
            TCHAR TempChar = *data++;
            if(TempChar==0x00)
               break;
            PowerSupply += TempChar;
         }
         PowerSupply.TrimRight();
         //PowerSupply.TrimLeft();
      }
      delete response;
   }
   else
      GetPowerSupplyName();
}

/************************************************************************/
/* The functio is used to create folders. The function firsk checks for	*/
/* the presence of the folder in USB Disk for curren working directory	*/
/* and if it is not found then a ner folder is created.					*/
/************************************************************************/
void CChildView::CreateFolder(bool CheckForPreset)
{
   CString	Path= USBDISKDRIVE;
   CString TempPath;
   if(!CheckForPreset)
   {

      if(!IsFolderPresent(Path,PowerSupply))
      {
         Path = USBDISK + PowerSupply;
         CreateDirectory(Path,NULL);
         TempPath = Path +"\\"+YearMonthName;
         CreateDirectory(TempPath,NULL);
         TempPath += "\\"+ Date;
         CreateDirectory(TempPath,NULL);
         TempPath =Path+ "\\"+"Presets";
         CreateDirectory(TempPath,NULL);
      }
      else
      {

         TempPath = USBDISK + PowerSupply;
         if(!IsFolderPresent(TempPath,YearMonthName))
         {

            TempPath= TempPath+"\\"+YearMonthName;
            CreateDirectory(TempPath,NULL);
            TempPath += "\\"+ Date;
            CreateDirectory(TempPath,NULL);
         }
         else
         {

            TempPath= USBDISK + PowerSupply+"\\"+YearMonthName;
            if(!IsFolderPresent(TempPath,Date))
            {
               TempPath= TempPath+"\\"+Date;
               CreateDirectory(TempPath,NULL);
            }
         }
         TempPath= USBDISK + PowerSupply;
         if(!IsFolderPresent(TempPath,"Presets"))
         {
            TempPath= TempPath+"\\Presets";
            CreateDirectory(TempPath,NULL);
         }
      }
   }
   else
   {
      if(!IsFolderPresent(Path,PowerSupply))
      {
         Path= USBDISK + PowerSupply;
         CreateDirectory(Path,NULL);
      }
   }
}


/*********************************************************************/
/* The following function is used check the presence of File at a	   */
/* specific path.													               */
/* arg 1: Path for the file.										            */
/* arg 2: File name to be searched								         	*/
/* A true is returned is folder is present else a false is returned. */
/*********************************************************************/
bool CChildView::IsFolderPresent(CString Path, CString FileName)
{

   WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   CString argv=Path;
   CString DirSpec;
   DirSpec=argv+_T("\\*");
   hFind = FindFirstFile(DirSpec, &FindFileData);
   if (hFind == INVALID_HANDLE_VALUE)
   {
      FindClose(hFind);
      return false;
   }
   else
   {
      if(FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )
      {
         if(FileName==FindFileData.cFileName)
         {
            FindClose(hFind);
            return true;
         }
      }
      while (FindNextFile(hFind, &FindFileData) != 0)
      {

         if(FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )
         {
            if(FileName==FindFileData.cFileName)
            {
               FindClose(hFind);
               return true;
            }
         }
      }
   }
   return false;
}

/****************************************************************/
/* This function is called to show message screen when required	*/
/* arg 1: Message to be shown.									*/
/****************************************************************/
void CChildView::ShowMessageScreen(CString Message)
{
   CDC *pDC=GetDc();
   EnableWindow(false);

   /*Drawing Message Rectangle in specified color*/
   CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
   CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

   /*Drawing Message Text*/
   CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Message,true);
   ReleaseDc(pDC);
   DisableFlag=true;
   InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
   EnableWindow(true);
}

void CChildView::ShowMessageScreen2(CString Message)
{
   DisableFlag=true;
   CDC *pDC=GetDc();
   EnableWindow(false);
   /*Drawing Message Rectangle in specified color*/
   CVgaMenuItem::DrawRect(pDC, Black,MESSAGESCRN_BLACKRECT);
   CVgaMenuItem::DrawRect(pDC, Blue, MESSAGESCRNRECT);

   /*Drawing Message Text*/
   CVgaMenuItem::DrawText(pDC, Bigfont,White , MESSAGESCRNRECT,Message,true);
   ReleaseDc(pDC);

   EnableWindow(true);
}

/********************************************************************/
/* The following function isused to check the presence of USB Disk	*/
/* The function returns true if USB is present else a false is		*/
/* returned.														*/
/********************************************************************/
bool CChildView::USBPresent()
{



#ifdef _WIN32_WCE
   HANDLE hFind = INVALID_HANDLE_VALUE;
   CString DirSpec="USBDisk\\";
   hFind = FindFirstFile(DirSpec, &FindFileData);
   if (hFind == INVALID_HANDLE_VALUE)
   {
      return false;
   }
   else
   {
      FindClose(hFind);
      return true;
   }
#else
   CString DirSpec = USBDISK;
   if(DRIVE_REMOVABLE == GetDriveType(DirSpec)) {
      return true;
   }
   return false;
#endif
}

void CChildView::GetAveragePowerGraph(CDC *pDC, CChildView * view)
{
   CVgaMenu * menu;
   menu=theApp.MenuPointer;
   CVgaMenuItem *object;
   POSITION POSI=menu->items.GetHeadPosition();
   int length =1;
   unsigned char data1=(char)04;
   unsigned char * data = (unsigned char *) &data1;

   CHostCommand * request = new CHostCommand(PowerMatchCurve_FunctionId, data, length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();//Getting Data.
      length = response->GetDataLength();//Getting Length.
      if(ch==theApp.ACK)//If Ack.
      {	   //store graph data

         while ((POSI)&&(length>0))
         {
            object= menu->items.GetNext(POSI);
            if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
            {
               CVgaDrawGraph * ptr = (CVgaDrawGraph *)object;
               int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
               if(ValueAfterParamID==NO_VALID_GRAPH)
               {
                  delete response;
                  return;
               }
               if(ValueAfterParamID==ptr->GraphType)
               {
                  ptr->GraphData.graph_type=ValueAfterParamID;
                  int TempVar =*data++;
                  if(TempVar>0)
                     CChildView::thisPtr->PMCDisable =true;
                  else
                     CChildView::thisPtr->PMCDisable =false;
                  length--;
                  ptr->PMCCycleCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
              	  data = data+2;
				  length = length-2;
                  CChildView::thisPtr->LowerPMCLimit=*data++;
                  length--;
                  CChildView::thisPtr->UpperPMCLimit=*data++;
                  length--;
                  ptr->GraphData.DataLength=0;

                  if(ptr->PMCCycleCount !=0)
                  {
                     short graphdatalength=0;
                     for(short len=0;len<400;len++)
                     {
                        if(*data!=0xFF)
                        {
                           ptr->GraphData.graphdata[len]=(short)*data++;
                           graphdatalength++;
                        }
                        else
                           data++;//Coverity 11378
                        length--;
                     }
                     ptr->GraphData.DataLength=graphdatalength;
                  }
                  if(ptr->GraphData.DataLength==0)
                  {
                     CChildView::thisPtr->LowerPMCLimit=0;
                     CChildView::thisPtr->UpperPMCLimit=0;

                  }
                  CChildView::thisPtr->PMCMaxVdata=*data++;

                  length--;length--;
                  if(PMCDisable)
                  {
                     ptr->RecalculateAverageGraph(CChildView::thisPtr);
                     ptr->DrawAvgPowerGraph(pDC,CChildView::thisPtr);
                  }
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
      {
         GetAveragePowerGraph(pDC,view);
      }
      delete response;
   }
}

void CChildView::ExitProgram()
{
   BottomHalfTimerOn=true;
   while (keypadList.GetCount())
      delete keypadList.RemoveHead();

   while (menuEntryList.GetCount()>0)
      delete menuEntryList.RemoveHead();

   while(PrintObjectList.GetCount()>0)
      delete PrintObjectList.RemoveHead();

   while(PrintSequenceObjectList.GetCount()>0)
      delete PrintSequenceObjectList.RemoveHead();

   while(PrintGraphTextObjectList.GetCount()>0)
      delete PrintGraphTextObjectList.RemoveHead();

   WeldAlarmStringList.RemoveAll();
   WeldHistoryAlarmStringList.RemoveAll();
   GraphAlarmStringList.RemoveAll();

   PrintInfoList.RemoveAll();

   delete []Parameter_Heading;
   delete []Parameter_Units_Metric;
   delete []Parameter_Units_USCS;
   delete []Parameter_ID;
   delete []GraphWeldDataIdArray;
   delete []WeldDataIdArray;
   delete []Parameter_Event_Heading;
   delete []Parameter_UserID_Heading;
   exit(1);
}

void CChildView::ErrorBeep()
{
   CHostCommand * request = new CHostCommand(ErrorBeep_FunId, 0, 0);
   CHostCommand * response = app->SendUiHostCommand(request);
   if (response)
      delete response;
}

void CChildView::SendCommandAlarms(int AlarmType)
{

   unsigned char  *data = (unsigned char *) &AlarmType;
   int length = 1;//length of pointer to be send to 332.
   CHostCommand * request = new CHostCommand(GenerateAlarm_FunId, data,length);
   CHostCommand * response = app->SendPollingHostCommand(request);
   if(response)
      delete response;

}

bool CChildView::MakeUSBWeldData(unsigned char *&data,int & length,int Difference)
{
   bool LatestObjectAdded =false;

   for(int i=Difference;i>=1;i--)
   {
      unsigned char *Tempdata=data;
      int TempLength=length;
      CHistoryData* USBObject;
      CWeldingData *TempPtr = new CWeldingData(i,Tempdata, TempLength,true);
      int CycleReceived = TempPtr->ReceivedUniversalCount+1-i;
      if((CycleReceived==(USBWelddata.BaseCount+USBWelddata.USBSampleValue))||((USBWelddata.USBOnAlarmValue)&&(TempPtr->TextColour==Red)))
      {
         unsigned char *Tempdata1=data;
         int TempLength1=length;
         USBObject = new CHistoryData(i,Tempdata1, TempLength1);

         if(CycleReceived==(USBWelddata.BaseCount+USBWelddata.USBSampleValue))
            USBWelddata.BaseCount+=USBWelddata.USBSampleValue;
         USBHistoryList.AddTail(USBObject);

         if(i==1)
         {
            LatestObjectAdded=true;
         }
         else
            USBGraphCountList.AddTail(0);
      }
      delete TempPtr;
   }

   return LatestObjectAdded;
}

bool CChildView::MakeLOGWeldData(unsigned char *&data,int & length,int Difference)
{
   bool LatestObjectAdded =false;

   for(int i=Difference;i>=1;i--)
   {
      unsigned char *Tempdata=data;
      int TempLength=length;
      CHistoryData* USBObject;
      CWeldingData *TempPtr = new CWeldingData(i,Tempdata, TempLength,true);
      int CycleReceived = TempPtr->ReceivedUniversalCount+1-i;
      if(CycleReceived)
      {
         unsigned char *Tempdata1=data;
         int TempLength1=length;
         USBObject = new CHistoryData(i,Tempdata1, TempLength1);
         LOGHistoryList.AddTail(USBObject);	//a new weld data object is given to USB thread for writing into the file
         if(i==1)
         {
            LatestObjectAdded=true;
         }

         //TempFileHisCount++;//increment the total weld data count here.
         ++CWeldingHistory::thisHisPtr->TotalDataInFile;
         //finally check for Max allowe data limit and make flags true to raise alarms
         if(CWeldingHistory::thisHisPtr->TotalDataInFile >= (unsigned int)CChildView::Max_Allowed_Weld_Log) //100,000 is the maximum Allowable count of weld results
         {
            if(CChildView::thisPtr->MemoryfullCont_Stop)
               CWeldingHistory::WeldSpaceFullFlag = false;
            else
            {
               CWeldingHistory::WeldSpaceFullFlag = true;
               delete TempPtr;
               return false;
            }
         }
      }
      delete TempPtr;
   }
   return LatestObjectAdded;
}


bool CChildView::GetAlarmButton()
{
   CVgaMenu *AlarmPtr;
   if(AlarmCount) //coverty fixed(not used)
   {
      CVgaMenuItem *AlarmObject=0;

      if(AlarmMenuIdentifier!="")
      {
         if(theApp.menus.Lookup(AlarmMenuIdentifier, AlarmPtr))
         {
            AlarmObject = AlarmPtr->items.GetHead();
            CAlarmButton *ptr=(CAlarmButton*)AlarmObject;
            AlarmMenuName = ptr->MenuName;
            GlobalAlarmObject=AlarmObject;
            AlarmUpdateRequired=true;
            CommandForAlarmButton=true;
            Invalidate();
            return true;
         }
      }

   }
   return false;
}

void CChildView::AddAlarmButtonInList()
{
   CVgaMenu * menu,*AlarmPtr;
   menu=theApp.MenuPointer;
   if(IsAlarmScreen||ScreenSetupFlag)
      return;

   CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
   POSITION pos = menu->items.GetHeadPosition();
   while(pos)
   {
      CVgaMenuItem *Object = menu->items.GetNext(pos);
      if(Object->GetType() ==CVgaMenu::VGA_ALARMBUTTON)
      {
         menu->items.RemoveHead();
      }
      else
      {
         TempDataList.AddTail(Object);
         menu->items.RemoveHead();
      }
   }

   POSITION pos2 = TempDataList.GetHeadPosition();
   while(pos2)
   {
      CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
      menu->items.AddTail(Obj);

   }
   while(TempDataList.GetCount())
      TempDataList.RemoveHead();


   CVgaMenuItem *AlarmObject=0;
   if(AlarmMenuIdentifier!="")
   {
      if(theApp.menus.Lookup(AlarmMenuIdentifier, AlarmPtr))
      {
         AlarmObject = AlarmPtr->items.GetHead();
         CAlarmButton *ptr=(CAlarmButton*)AlarmObject;
         AlarmMenuName=ptr->MenuName;
         AlarmObject->SetText(GetAlarmString(AlarmObject));
         menu->items.AddTail(AlarmObject);
         CDC *pDC =GetDC();
         AlarmObject->Draw(pDC);
         ReleaseDC(pDC);
      }
   }
}

CString CChildView::GetAlarmString(CVgaMenuItem *ptr)
{
   CAlarmButton *AlarmPtr=(CAlarmButton *)ptr;
   CString AlarmString= "** ";

   if(AlarmCount >9)
   {
      AlarmString+=(TCHAR)((AlarmCount/10)+48);
      AlarmString+=(TCHAR)((AlarmCount%10)+48);
   }
   else
      AlarmString+=(TCHAR)((AlarmCount)+48);

   if(AlarmCount==1)
      AlarmString+=AlarmPtr->Text1;
   else
      AlarmString+=AlarmPtr->Text2;
   return AlarmString;
}

void CChildView::GetWeldDataIdArray(bool DeletePrevious)
{
   int length =ONE;
   unsigned char data1 = (char)WELDDATAID;
   unsigned char *data;
   CHostCommand* request = new CHostCommand(GetWeldSetupPrint_FunID, &data1, length);
   CHostCommand* response = app->SendPollingHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==ACK)
      {
         int Counts=*data++;
         length--;
         if(Counts>0)
         {
            if(DeletePrevious)
               delete []WeldDataIdArray;

            WeldDataIdArray = new int[Counts+1];
            WeldDataIdArray[0]=Counts;
            for(int ID=1;ID<=Counts;ID++)
            {
               WeldDataIdArray[ID]=*data++;
               length--;
            }
         }
      }
      delete response;
   }
}


void CChildView::GetGraphWeldDataIdArray(bool DeletePrevious)
{
   int length =ONE;
   unsigned char data1 = (char)GRAPHID;
   unsigned char *data;
   CHostCommand* request = new CHostCommand(GetWeldSetupPrint_FunID, &data1, length);
   CHostCommand* response = app->SendPollingHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      data = response->GetData();
      length = response->GetDataLength();
      if(ch==ACK)
      {
         int Counts=*data++;
         length--;
         if(Counts)
         {
            if(DeletePrevious)
               delete []GraphWeldDataIdArray;

            GraphWeldDataIdArray = new int[Counts+1];
            GraphWeldDataIdArray[0]=Counts;
            for(int ID=1;ID<=Counts;ID++)
            {
               GraphWeldDataIdArray[ID]=*data++;
               length--;
            }
         }
      }
      delete response;
   }
}





/*****************************************************************************/
/*  Function Set the Rectangle for button according to the type and count.   */
/*****************************************************************************/

void CChildView::RecalculateMenuItemsLayout(int height,CVgaMenu * CurrMenuLst)
{
   CurrMenuList=CurrMenuLst;

   int items = 0;
   Total_Objects=0;
   int left_coordinate;
   int TotalObjectDraw=0;

   Total_Text_Objects=0;
   SysInfoScreen=false;

   if(listbuild == false)
      return;

   POSITION pos = CurrMenuList->items.GetHeadPosition();
   CVgaMenuItem * object = CurrMenuList->items.GetNext(pos);
   CurrMenuList->items.GetNext(pos);


   pos = CurrMenuList->items.GetHeadPosition();
   object = CurrMenuList->items.GetNext(pos);
   left_coordinate=LEFT_COORDINATE_1_BUTTON;
   int top_coordinate = TOP_COORDINATE_1_BUTTON;
   int count=0;
   int customButtonHgap = 0;
   int customButtonVgap = 0;
   int customButtonWidth = 0;
   int customButtonHeight = 0;
   if(object->GetType()==CVgaMenu::TITLE)
   {
      CVgaTitle *title=(CVgaTitle *)object;
      CChildView::RowPerPage=title->rows;
      CChildView::ColumnPerPage=title->columns;
      CChildView::ButtonType=title->ButtonTypes;
      CChildView::ExitButtonFlag=title->ExitFlag;
      CChildView::SaveButtonFlag=title->SaveFlag;
   }

   AddSaveExit(CurrMenuList);
   POSITION pos1 = CurrMenuList->items.GetHeadPosition();
   while(pos1)
   {
      object = CurrMenuList->items.GetNext(pos1);
      if(object->IsDraw == true)
      {
         int type = object->GetType();
         if(type ==VGAHistoryGraphObject)
            return;
         if (((type > CVgaMenu::TITLE) && (type < CVgaMenu::MENU_END))||
            ((type==CVgaMenu::VGA_Button_OBJECT)||((type>CVgaMenu::MENU_END)
            &&(type<=CVgaMenu::COLORSETUP_ID)) ||
            (type == CVgaMenu::VGA_DIGITALINPUT)))
            TotalObjectDraw++;
      }
   }
   if(CChildView::MenuType == false){
      if(TotalObjectDraw<=MaxItemIn1ColMenu)
      {
         CChildView::RowPerPage=MaxItemIn1ColMenu;
         CChildView::ColumnPerPage=1;
      }
   }
   GetButtonShape(customButtonHgap,customButtonVgap,customButtonWidth,customButtonHeight);

   int TempPageNum=1;
   while(pos)
   {
      object = CurrMenuList->items.GetNext(pos);
      if(object->IsDraw == true)
      {
         int type = object->GetType();
         if(type!=CVgaMenu::TITLE)
         {
            if(type==CVgaMenu::TEXT)
               Total_Text_Objects++;
            if (((type > CVgaMenu::TITLE) && (type < CVgaMenu::MENU_END))||(type==CVgaMenu::VGA_Button_OBJECT))
               items++;

            Total_Objects=items;
            if (CChildView::ColumnPerPage ==1 )
               left_coordinate+=LCOORDINATE_COL1_FACTOR;

            if(CChildView::ButtonType == RADIOTYPE)
               left_coordinate+=LCOOR_RADIO_FACTOR;

            if((type==0)||(type==1)||((type==CVgaMenu::VGA_VGAEXITBUTTON)
				||(type==CVgaMenu::VGA_VGASAVEBUTTON)||(type==CVgaMenu::VGA_ALARMBUTTON)
               &&(object->GetRect().BottomRight().y!=0)))
            {
               count++;
               object->SetPageNum(CVgaMenuItem::PAGEALL);
            }
            else if(type == CVgaMenu::VGATableObject)
            {
               count++;
               object->SetPageNum(CVgaMenuItem::PAGEALL);
            }
            else if((type == CVgaMenu::VGA_DIGITALINPUT))
            {
               count++;
               object->SetPageNum(CVgaMenuItem::PAGEALL);
            }
            else
            {

               if((object->PSType != CVgaMenu::VGA_Button_OBJECT)
                  && (object->PSType != CVgaMenu::ALPHA)
                  && (object->PSType != CVgaMenu::VARIABLE)
                  && (object->PSType != CVgaMenu::VGATEXT))
               {
                  object->SetRect(CRect(left_coordinate+XOFFSET,
                     top_coordinate+YOFFSET,
                     left_coordinate +customButtonWidth+XOFFSET ,
                     top_coordinate + customButtonHeight+YOFFSET));
               }
               else if((object->PSType == CVgaMenu::VGA_Button_OBJECT))
               {
                  CVgaButton *ptr=(CVgaButton *)object;
                  if(ptr->Rect.BottomRight().y==0 )
                     object->SetRect(CRect(left_coordinate+XOFFSET,
                     top_coordinate+YOFFSET,
                     left_coordinate +customButtonWidth+XOFFSET ,
                     top_coordinate + customButtonHeight+YOFFSET));
               }
               else if((object->PSType == CVgaMenu::ALPHA))
               {
                  CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)object;
                  if(ptr->Rect.BottomRight().y==0 )
                     object->SetRect(CRect(left_coordinate+XOFFSET,
                     top_coordinate+YOFFSET,
                     left_coordinate +customButtonWidth+XOFFSET ,
                     top_coordinate + customButtonHeight+YOFFSET));
               }
               else if((object->PSType == CVgaMenu::VARIABLE))
               {
                  CVgaVariable *ptr=(CVgaVariable *)object;
                  if(ptr->Rect.BottomRight().y==0 )
                     object->SetRect(CRect(left_coordinate+XOFFSET,
                     top_coordinate+YOFFSET,
                     left_coordinate +customButtonWidth+XOFFSET ,
                     top_coordinate + customButtonHeight+YOFFSET));
               }
               else if((object->PSType == CVgaMenu::TEXT))
               {
                  CText *ptr=(CText *)object;
                  if(ptr->Rect.BottomRight().y==0 )
                     object->SetRect(CRect(left_coordinate+XOFFSET,
                     top_coordinate+YOFFSET,
                     left_coordinate +customButtonWidth+XOFFSET ,
                     top_coordinate + customButtonHeight+YOFFSET));
               }

               count++;
               if(count!=(RowPerPage*ColumnPerPage*TempPageNum))
               {

                  if(count%ColumnPerPage !=0)
                  {
                     left_coordinate+=(customButtonWidth+customButtonHgap);

                  }
                  else
                  {
                     left_coordinate=LEFT_COORDINATE_1_BUTTON;
                     top_coordinate += (customButtonHeight+customButtonVgap);
                  }
                  object->SetPageNum(TempPageNum);
               }
               else
               {
                  object->SetPageNum(TempPageNum);
                  left_coordinate=LEFT_COORDINATE_1_BUTTON;
                  top_coordinate = TOP_COORDINATE_1_BUTTON;
                  TempPageNum++;
               }
            }
         }
      }
   }
}

/**************************************************************/
/*This Function Checks The row and coloumn Number and Gives   */
/*Buttos Size Acorrdings to it.								  */
/**************************************************************/
void CChildView::GetButtonShape(int &Hgap, int &Vgap, int &Width, int &Height)
{
   int rows=CChildView::RowPerPage;
   int coloumns=CChildView::ColumnPerPage;
   int buttontype=CChildView::ButtonType;
   switch(rows)
   {
   case 1: Vgap = BUTTON_GAP;
      Height = BUTTON_HEIGHT;
      break;
   case 2: Vgap = BUTTON_GAP;
      Height = BUTTON_HEIGHT;
      break;
   case 3: Vgap = BUTTON_GAP;
      Height = BUTTON_HEIGHT;
      break;
   case 4: Vgap = BUTTON_GAP;
      Height = BUTTON_HEIGHT;
      break;
   case 5: Vgap = BUTTON_GAP-7;
      Height = BUTTON_HEIGHT;
      break;
   case 6: Vgap = BUTTON_GAP-14;
      Height = BUTTON_HEIGHT;
      break;
   case 7: Vgap = BUTTON_GAP-14;
      Height = BUTTON_HEIGHT-10;
      break;
   case 8: Vgap = BUTTON_GAP-14;
      Height = BUTTON_HEIGHT-18;
      break;
   case 9: Vgap = BUTTON_GAP-25;
      Height = BUTTON_HEIGHT-25;
      break;
   case 10: Vgap = BUTTON_GAP-25;
      Height = BUTTON_HEIGHT-25;
      break;
   default : ;
   }
   switch(coloumns)
   {
   case 1:
      Hgap = 70;
      Width = MENU_BUTTON_WIDTH+90;
      break;
   case 2:
      Hgap = 135;
      Width = MENU_BUTTON_WIDTH;
      break;
   case 3:
      Hgap = 25;
      Width = MEDIUM_BUTTON_WIDTH-10;
      break;
   case 4: Hgap = 40;
      Width = MEDIUM_BUTTON_WIDTH-60;
      break;
   case 5: Hgap = 20;
      Width = MEDIUM_BUTTON_WIDTH-80;
      break;
   case 6: Hgap = 25;
      Width = MEDIUM_BUTTON_WIDTH-110;
      break;
   default : ;
   }
   if(buttontype !=DEFAULT)
      switch(buttontype)
   {
      case LARGE:
         Height=BUTTON_HEIGHT;
         Width =  MENU_BUTTON_WIDTH;
         break;
      case NORMAL:
         Height = BUTTON_HEIGHT;
         Width = MEDIUM_BUTTON_WIDTH;
         break;
      case SMALL:
         Height = BUTTON_HEIGHT;
         Width = 70;
         if(coloumns ==5)
            Hgap=55;
         break;
      case TEXTTYPE:
         Height = BUTTON_HEIGHT-15;
         Width = MEDIUM_BUTTON_WIDTH-20;
         break;
      case RADIOTYPE:
         Height = BUTTON_HEIGHT-5;
         Width = MEDIUM_BUTTON_WIDTH+13;
         Hgap = 70;
         break;
      default : ;
   }
}

bool CChildView::CheckConditions(CVgaMenuItem *item) const
{
   POSITION pos = item->conditions.GetHeadPosition();
   while (pos)
   {
      CCondition * condition = item->conditions.GetNext(pos);
      if (!condition->Evaluate(item))
      {
         return false;
      }
   }
   return true;
}

/**************************************************************/
/*This Function Checks if user should be allowed to make any  */
/* changes to the clicked menu item based on the required     */
/* user authority and current conditions. Following conditions*/
/* are checked based on the data from Main.gui:
/* 1. perset is unvalidated or validated.
/* 2. Preset is locked/unlocked.
/* 3. Automation is ON/Off
/* 4. Current user authority level permits changes with combination
/*    of above three condition.
/**************************************************************/
bool CChildView::CheckChangeConditions(CVgaMenuItem *item) const
{
   POSITION pos = item->conditions.GetHeadPosition();
   while (pos)
   {
      CCondition * condition = item->conditions.GetNext(pos);
      if (!condition->EvaluateChangeCond(item))
      {
         return false;
      }
   }
   return true;
}

void CChildView::ModifyObjectList(CVgaMenu * CurrMenuLst)
{
	listbuild = false;
	CurrMenuList = CurrMenuLst;
	if(CurrMenuList !=NULL)
	{
		if(CurrMenuLst->items.GetCount()>0)
		{
			POSITION pos = CurrMenuList->items.GetHeadPosition();
			CVgaMenuItem * object = NULL;
			while(pos)
			{
				object=CurrMenuList->items.GetNext(pos);
				if(CheckConditions(object)  == true)
					object->IsDraw = true;
				else
					object->IsDraw = false;
			}
		}
	}
	listbuild = true;
	if((AlarmCount==0))
	{
		if(CurrMenuList != NULL)//coverity 12568
		{
			CTypedPtrList<CPtrList, CVgaMenuItem *> TempDataList;
			POSITION pos = CurrMenuList->items.GetHeadPosition();
			while(pos)
			{
				CVgaMenuItem *Object = CurrMenuList->items.GetNext(pos);
				if(Object->GetType() == CVgaMenu::VGA_ALARMBUTTON)
				{
					CurrMenuList->items.RemoveHead();
				}
				else
				{
					TempDataList.AddTail(Object);
					CurrMenuList->items.RemoveHead();
				}
			}

			POSITION pos2 = TempDataList.GetHeadPosition();
			while(pos2)
			{
				CVgaMenuItem *Obj = TempDataList.GetNext(pos2);
				CurrMenuList->items.AddTail(Obj);
			}

			while(TempDataList.GetCount())
				TempDataList.RemoveHead();
		}
	}
	CChildView::RecalculateMenuItemsLayout(MAXSCRNButton_Height,CurrMenuList);
}


/**************************************************************/
/*This Function Checks Save and/or Exit Button Flag from Title*/
/*Object and sets rect for Those Buttons.					  */
/**************************************************************/
void CChildView::AddSaveExit(CVgaMenu * CurrMenuLst)
{
   static bool loginBtnExist = false;
   static bool logoutBtnExist = false;

   if(ExitButtonFlag)
   {
      CVgaMenuItem *object;
      object=new CVgaButton(Str_Exit,220,390,310,430,"");
      if(SaveButtonFlag)
      {
         object->SetRect(ExitWithSaveButtonRect);
      }
      else
      {
         object->SetRect(ExitButtonRect);
      }
      object->IsDraw=true;
      object->SetType(CVgaMenu::VGA_VGAEXITBUTTON);
      object->PSType=CVgaMenu::VGA_Button_OBJECT;
      CurrMenuLst->items.AddTail(object);
   }
   if(SaveButtonFlag)
   {
      CVgaMenuItem *object;
      object=new CVgaButton(Str_Save,330,390,420,430,"HandleVGASaveButton");
      object->IsDraw=true;
      object->SetType(CVgaMenu::VGA_VGASAVEBUTTON);
      object->PSType=CVgaMenu::VGA_Button_OBJECT;
      object->SetRect(SaveButtonRect);
      object->AccessLevel=USER_MAINTENANCE;
      CurrMenuLst->items.AddTail(object);
   }
}

int CChildView::Convert_Char_To_Int(unsigned char *&data, int &length, int Bytes)
{
   union {
      int i;
      char c[INTEGERLENGTH];
   } u;
   if(Bytes!=0)
      for (int k = 0; k < Bytes; k++)
      {
         u.c[k] = 0;
      }
      for (int j = Bytes; j < INTEGERLENGTH; j++)
      {
         u.c[j] =*data++;
         length--;
      }
      return ((u.i ));
}

float CChildView::Convert_Char_To_Float(unsigned char *&data, int &length, int Bytes)
{
   union {
      float i;
      char c[INTEGERLENGTH];
   } u;
   if(Bytes!=0)
      for (int k = 0; k < Bytes; k++)
      {
         u.c[k] = 0;
      }
      for (int j = Bytes; j < INTEGERLENGTH; j++)
      {
         u.c[j] =*data++;
         length--;
      }
      return ((u.i ));
}

void CChildView::SetDimension(CVgaMenuItem *item,int count)
{
   CVgaVariable *ptr1;
   CRadioMenu *ptr2;
   if(item->GetType() == CVgaMenu::VARIABLE)
      ptr1=(CVgaVariable *)item;
   else
      ptr2= (CRadioMenu *)item;
   int X1=0,Y1=0,X2=0,Y2=0;
   switch(count)
   {
   case 0:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE2;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE2+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE2;
      }
      break;
   case 1:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE2;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE2+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE2;
      }
      break;
   case 2:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE3;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE3+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE3;
      }
      break;
   case 3:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE3;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE3+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE3;
      }
      break;
   case 4:
      {
         X1=VARIABLE_COORDINATE1;
         Y1=VARIABLE_COORDINATE5;
         X2=VARIABLE_COORDINATE1+VARIABLE_WIDTH;//VARIABLE_COORDINATE1;
         Y2=VARIABLE_COORDINATE5+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE5;
      }
      break;
   case 5:
      {
         X1=VARIABLE_COORDINATE4;
         Y1=VARIABLE_COORDINATE5;
         X2=VARIABLE_COORDINATE4+VARIABLE_WIDTH;//VARIABLE_COORDINATE4;
         Y2=VARIABLE_COORDINATE5+LEFT_COORDINATE_1_BUTTON;//VARIABLE_COORDINATE5;
      }
      break;
   }
   if(item->GetType() == CVgaMenu::VARIABLE)
      ptr1->SetRect (CRect(X1,Y1,X2,Y2));
   else
      ptr2->SetRect (CRect(X1,Y1,X2,Y2));
}

bool CChildView::ReadStartUpVersionString()
{
   bool success=true;
   CFile f;
   CFileException e;
   TCHAR* pFileName;
#ifndef _WIN32_WCE
   pFileName = _T("C:\\Branson\\Startup.txt");
#else
   pFileName = _T("Disk\\Startup.txt");
#endif

   if( !f.Open( pFileName,CFile::modeRead , &e ) )
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

      success=false;
   }
   else
   {
      char Comma =',';
      int Temprorylen=0;
      int FileSize = (int)f.GetLength();
      int SysFileSize=FileSize;
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);

      LPTSTR p = StartUpVerFileName.GetBuffer(FileSize);
      for(int count=0;count<FileSize;count++)
      {
         p[count]=data[count];
      }
      StartUpVerFileName.ReleaseBuffer( );
      int index = StartUpVerFileName.Find('=');
      StartUpVerFileName=StartUpVerFileName.Right((FileSize-index)-1);
      if((StartUpVerFileName.Find( '.' ) == -1)
         || (StartUpVerFileName.GetLength()>MAXSYSFILE_LEN))
      {
         delete []data;
         f.Close();
         success=false;
      }
      else
      {
         delete []data;
         f.Close();
         success=true;
      }
   }
   return success;
}

bool CChildView::ReadSystemVersionString()
{
   bool success=true;
   CFile f;
   CFileException e;
   TCHAR* pFileName;

   pFileName = _T(SYSTEMVERSIONPATH);

   if( !f.Open( pFileName,CFile::modeRead , &e ) )
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

      success=false;
   }
   else
   {
      int FileSize = (int)f.GetLength();
      unsigned char *data=new unsigned char[FileSize];
      f.Read(data,FileSize);
      LPTSTR p = SystemVerFileName.GetBuffer(FileSize);
      for(int count=0;count<FileSize;count++)
      {
         p[count]=data[count];
      }

      SystemVerFileName.ReleaseBuffer( );
      int index = SystemVerFileName.Find('=');
      SystemVerFileName=SystemVerFileName.Right((FileSize-index)-1);
      if((SystemVerFileName.Find( '.' ) == -1)
         || (SystemVerFileName.GetLength()>MAXSYSFILE_LEN))
      {
         delete []data;
         f.Close();
         success=false;
      }
      else
      {
         delete []data;
         f.Close();
         success=true;
      }
   }
   return success;
}


/***************************************************************************
*Purpose:
*   This function draws text in PDF according to the passed parameters.
*   The origin of the PDF coordinate system (0, 0) represents the bottom-left
*   corner of the PDF page.So page_height - (text y coordinate) will position
*   text correctly in PDF.
*Entry condition:
*   HPDF_Page *page: pointer to HPDF_Page page
*   int X_Cord: X_Cord
*   int Y_Cord: Y_Cord
*   char *STR: string to be drawn
*Exit condition:
*   none
***************************************************************************/
void CChildView::DrawPDFText(HPDF_Page *page,int X_Cord,int Y_Cord,char *STR)
{
   HPDF_Page_BeginText (*page);
   HPDF_Page_MoveTextPos (*page,(HPDF_REAL)X_Cord,HPDF_Page_GetHeight(*page)-Y_Cord);
   HPDF_Page_ShowText (*page,STR);
   HPDF_Page_EndText (*page);
   HPDF_Page_SetRGBFill(*page, 0.0, 0.0, 0.0);
}


/***************************************************************************
*Purpose:
*   When number of pages per PDF document exceed 30 then this function save
*   the current PDF doc and creates a new PDF doc.
*Entry condition:
*   HPDF_Page *page:pointer to current page in PDF.
*   HPDF_Doc *doc:pointer to current PDF under creation.
*   HPDF_Font def_font:font used for PDF.
*Exit condition:
*   none
***************************************************************************/
bool CChildView::CreateNewPDFDoc(HPDF_Page *page,HPDF_Doc  *pdf,HPDF_Font *def_font )
{
   bool PDFCreateStatus = true;

   char STR[128];
   CString WeldHistoryStr =  CVgaMenuItem ::LinearSearch(XSTR(WELDHISTORY_STRINGID));
   const char* fontname;
   PDFCreateStatus = SavePDFToUSB(*pdf,Historyfname);
   eventname++;
   *pdf = HPDF_New (error_handler, NULL);
   *page = HPDF_AddPage (*pdf);
   HPDF_Page_SetSize (*page,HPDF_PAGE_SIZE_A4, HPDF_PAGE_LANDSCAPE);

   HPDF_UseUTFEncodings(*pdf);
   fontname = HPDF_LoadTTFontFromFile(*pdf, PDFFontName, HPDF_TRUE);
   *def_font = HPDF_GetFont(*pdf, fontname, "UTF-8");
   PdfWithImage(pdf,page,def_font);
   HPDF_Page_SetFontAndSize (*page, *def_font,25);
   CChildView::thisPtr->CStringToUTF(WeldHistoryStr,STR);
   CChildView::DrawPDFText(page,10,TWOWELDLINEGAP,STR);
   HPDF_Page_SetFontAndSize(*page,*def_font,7);
   strcpy (Historyfname,"WeldHistory");
   CurrentFilepath = CChildView::thisPtr->GetCurrentFilePath(Historyfname);
   try {
      CChildView::thisPtr->CreateFolder(true);
   }
   catch(...)
   {
      CString x;
      x = _T("The File cannot be saved to USB : Folder Cannot Be Created");
      AfxMsgBox(x);
   }
   sprintf(Historyfname,"%s",CurrentFilepath);
   YCoordinate = FOURWELDLINEGAP;

   return PDFCreateStatus;

}






/***************************************************************************
*Purpose:
*   This function send command to WC to get total number of users.
*Entry condition:
*    none
*Exit condition:
*    int : number of users.
***************************************************************************/
int GetNumberOfUsers(void)
{
   unsigned char data1=(char)0;
   unsigned char * data = (unsigned char *) &data1;
   int count=0xff;
   int length=1;

   CHostCommand * request = new CHostCommand(GET_NUMBER_OF_USERS,data,length);
   CHostCommand * response = app->SendUiHostCommand(request);
   if(response)
   {
      char ch=CHostCommand::AckNak();
      unsigned char *data = response->GetData();
      length = response->GetDataLength();
      if(ch==ACK)
      {
         count=data[1]<<8;
         count=count|data[0];
      }
      delete response;
   }

   return count;
}


bool SavePDFToUSB(HPDF_Doc &pdf,char *filename)
{
   bool PDFCreateStatus = true;
   PDFExceptionFlag = false;
   try {
      /* do page description processes (do not have to check function return codes) */
      HPDF_SaveToFile (pdf, filename);
   } catch (...) {
      /*CString x;
      x = _T("The File cannot be saved to USB");
      AfxMsgBox(x);*/
      PDFCreateStatus = false;
   }
   HPDF_Free (pdf);
   extern bool PDFExceptionFlag;
   if(PDFExceptionFlag)
      PDFCreateStatus = false;
   return PDFCreateStatus;
}

/***************************************************************************
*Purpose:
*   This function clears all the pending weld and graph data supposed to be
*   written on USB.
*Entry condition:
*    When USB Memory full is detected
*Exit condition:
*    Graph and  History data list cleared.
***************************************************************************/
void CChildView::ClearListOnUSBFullAlarm(void)
{
   while(USBGraphsList.GetCount())
      delete USBGraphsList.RemoveHead();

   while(USBHistoryList.GetCount())
      delete USBHistoryList.RemoveHead();

}

void CChildView::CStringToUTF(CString Text,char *UnicodeStr)
{

   unsigned short utf8[4];
   int utf_len = 0;
   int str_len ;    //= object->Text.GetLength();
   int pos = 0;
   str_len =Text.GetLength();
   for( int j = 0;j < str_len ; j++)
   {
      utf_len = unicodeToUTF8(Text.GetAt(j) ,(unsigned char*)utf8);
      memcpy(UnicodeStr+pos ,(char*)(&utf8),utf_len);
      pos += utf_len;
   }
   UnicodeStr[pos]=0;
}


void CChildView::AssignFontForPrinting()
{
   int i = 0;
   while(Languages[i])
   {
      if(!strcmp(Languages[i],CurrentLanguageName))
         break;
      i++;
   }
   switch(i)
   {
   case ENGLISH:
      PDFFontName = strcat(FontPath,"courier.ttf");
      break;

   case CHINESESIML:
      PDFFontName = strcat(FontPath,"simsun.ttf");
      break;

   case CHINESETRAD:
      PDFFontName = strcat(FontPath,"mingliu.ttf");
      break;

   case FRENCH:
   case GERMAN:
   case ITALIAN:
   case SPANISH:
      PDFFontName = strcat(FontPath,"arial.ttf");

      break;
   case JAPANESE:
      PDFFontName = strcat(FontPath,"MS Gothic.ttf");
      break;

   case KOREAN:
      PDFFontName = strcat(FontPath,"Gulim.ttf");
      break;
   default:
      PDFFontName = strcat(FontPath,"courier.ttf");
   }
}

void CChildView::CheckAvailablDiskSpace(CString str)
{

	ULARGE_INTEGER FreeByteAvailable,TotalBytes,FreeBytes;
	__int64 AvailableDiskSpace,TotalByteAvailable,LimitedDiskSizeToBeCheck;
	int Present;
	bool * CheckPtr = &(CChildView::thisPtr->DISKMemoryNearlyFull);
	if(str == USBDISK)
	{
		ISUSBPresent = CChildView::thisPtr->USBPresent();
		if(ISUSBPresent && USBGlobalFlag)
			CheckPtr = &(CChildView::thisPtr->USBMemoryNearlyFull);

		else if(CChildView::thisPtr->USBOverWritePreset && ISUSBPresent)
			CheckPtr = &(CChildView::thisPtr->USBCheckCopyAllFlag);
		else
			CheckPtr = 0;
	}

	if(CheckPtr)
	{
		Present = GetDiskFreeSpaceEx(str,&FreeByteAvailable,&TotalBytes,&FreeBytes);
		AvailableDiskSpace = FreeByteAvailable.HighPart;
		AvailableDiskSpace = FreeByteAvailable.LowPart | (AvailableDiskSpace<<32);
		TotalByteAvailable  = TotalBytes.HighPart;
		TotalByteAvailable = TotalBytes.LowPart | (TotalByteAvailable<<32);
		LimitedDiskSizeToBeCheck = TotalByteAvailable/5; //20% available
		if(AvailableDiskSpace <= LimitedDiskSizeToBeCheck)
			*CheckPtr = true;
	}
   /*printf("Available space for caller = %I64u GB\n",AvailableDiskSpace/(1024*1024*1024));
   printf("Available space = %I64u GB\n",TotalByteAvailable /(1024*1024*1024));
   printf("80 of Available space = %I64u GB\n",LimitedDiskSizeToBeCheck /(1024*1024*1024));*/
}


/***************************************************************************
*Purpose:
*   This function updates the total weld count in WeldDataHidden file
*
*Entry condition:
*    Takes int WeldCount added in the list.
*Exit condition:
*    nothing.
***************************************************************************/

void UpDateWeldHiddenFile(int WeldCount)
{
	CString PathHidden = DISK;
	CFile pFile;
	PathHidden = PathHidden + "WeldDataHidden.log";
	CChildView::thisPtr->UniversalCountWeldHiddenFile += WeldCount;
	if(pFile.Open(PathHidden,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))//create and hide the file
	{
		pFile.SeekToBegin();
		pFile.Write(&CChildView::thisPtr->UniversalCountWeldHiddenFile,sizeof(UINT32));
		pFile.Close();
	}
}

/***************************************************************************
*Purpose:
*   This function updates the total event count in EventHiddenFille.log file
*
*Entry condition:
*    Takes int  EventCount added in the list.
*Exit condition:
*    nothing.
***************************************************************************/
void UpdateEventHiddenFile(int EventCount)
{
	CEventLog::EventHistoryUniversalCount += EventCount;
	CString PathHidden = DISK;
	CFile pFile;
	PathHidden = PathHidden + "EventHiddenFile.log";
	if(pFile.Open(PathHidden,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))//create and hide the file
	{
		pFile.SeekToBegin();
		pFile.Write(&CEventLog::EventHistoryUniversalCount,sizeof(UINT32));
		pFile.Close();
	}
}


/***************************************************************************
*Purpose:
*   This function sends get software version command serially, which tells
*   wc that sbc is alive, and wc resets the serial timeout on receiving any
*   serial command.
*
*Entry condition:
*    nothing.
*Exit condition:
*    nothing.
***************************************************************************/

void SendResetTimeOutCommand(void)
{
	CHostCommand * request = new CHostCommand(GET_SOFTWARE_VERSION,0,0);
	CHostCommand * response = NULL;
	if(request != NULL)//coverity fix 12566
		response = app->SendUiSerialHostCommand(request);
	if(response)
	  delete response;
	if(request)
	  delete request;
}

/***************************************************************************
*Purpose:
*   This thread calls SendResetTimeOut() function every second to let WC know that
*   SBC is alive.
*
*
***************************************************************************/

UINT CChildView::SendSerialCommand(LPVOID)
{
   while(1)
   {
	   SendResetTimeOutCommand();
	   Sleep(1000);
   }
   return 0;
}
