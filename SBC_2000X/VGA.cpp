/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGA.cpp_v   1.36   Nov 03 2017 15:20:16   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VGA.cpp_v  $
 * 
 *    Rev 1.36   Nov 03 2017 15:20:16   RJamloki
 * Fix bug when using previous version of v12.3 on startup
 * 
 *    Rev 1.35   Oct 09 2017 10:53:28   RJamloki
 * Path code for support old version when updating for micro c
 * 
 *    Rev 1.34   Jun 29 2017 14:09:16   RJamloki
 * You must login to the system even if automation is ON
 * 
 *    Rev 1.33   29 Aug 2016 14:22:42   RJamloki
 * Added a PressureStepDownClick pointer function
 * 
 *    Rev 1.32   16 Dec 2015 15:08:26   RJamloki
 * Remove autorithy data from GetSystemVariable
 * 
 *    Rev 1.31   17 Nov 2015 17:00:12   RJamloki
 * Received the operator authority variables from WC
 * 
 *    Rev 1.30   16 Apr 2015 06:03:42   sesharma
 * Included the new file InputDevices.h and calling MouseDetect() function  to support auto hide of cursor if mouse is not plugged in and coverity fix.
 * 
 *    Rev 1.29   28 Mar 2015 04:42:58   RJamloki
 * StartSensorCal() added to send Cal Full System screen entered indication to WC.
 * 
 *    Rev 1.28   11 Feb 2015 06:22:06   amaurya
 * changes to handle multiple instances of 2000Xc and event display after alarm reset
 * 
 *    Rev 1.27   30 Jan 2015 08:15:20   amaurya
 * CheckVerifiedPreset() added.
 * 
 *    Rev 1.26   02 Jan 2015 05:02:30   rjamloki
 *  StopStateMachine() function added
 * 
 *    Rev 1.25   11 Dec 2014 06:51:28   RJamloki
 * CVGAApp::Clean() changed to avoid memory click.
 * 
 *    Rev 1.24   28 Nov 2014 08:32:34   rjamloki
 *  Unused functions removed
 * 
 *    Rev 1.23   20 Oct 2014 05:49:56   RJamloki
 * Control level D related changes.
 * 
 *    Rev 1.22   06 Oct 2014 03:28:28   rjamloki
 *  GetNKBinDate() function removed and file path changed
 * 
 *    Rev 1.21   01 Oct 2014 10:54:16   AnPawar
 * GetVQSWindow() removed.File path changed
 * 
 *    Rev 1.20   26 Sep 2014 09:27:38   rjamloki
 * Fixed callinvalidate type
 * 
 *    Rev 1.19   25 Sep 2014 12:10:52   AnPawar
 * PrepareFunctionMapTable() function changed
 * 
 *    Rev 1.18   11 Sep 2014 09:49:34   rjamloki
 * ParseXmlTree() function modified.CreateEventDesc(),CreateParamDesc() function made.
 * 
 *    Rev 1.17   05 Sep 2014 07:03:02   amaurya
 * GetSystemVariable() and PrepareFunctionMapTable() modified.
 * 
 *    Rev 1.16   18 Aug 2014 08:01:34   rjamloki
 * Added handler for DownSpeed tune screen
 * 
 *    Rev 1.15   28 Jul 2014 14:24:18   rjamloki
 * added SwUpgrade function
 * 
 *    Rev 1.14   22 Jul 2014 08:11:48   akaushal
 * sendNetworkInfo() function added.
 * 
 *    Rev 1.13   09 Jul 2014 07:10:36   akaushal
 * ReadXML(),GetSystemVariable(),PrepareFunctionMapTable() function changed
 * 
 *    Rev 1.12   11 Jun 2014 10:49:52   rjamloki
 * added for weld column setup and Weld result screen.
 * 
 *    Rev 1.11   09 Jun 2014 11:59:58   rjamloki
 * Removed printing functions and externs. 
 * 
 *    Rev 1.10   27 May 2014 06:45:28   amaurya
 * Added new command for Reset Sensor Calibration
 * 
 *    Rev 1.9   20 May 2014 11:09:56   rjamloki
 * CVGAApp::ReadXML() and PrepareFunctionMapTable() changed
 * 
 *    Rev 1.8   07 May 2014 13:13:00   akaushal
 * Safely remove sbc and weld data deletion added
 * 
 *    Rev 1.7   21 Apr 2014 13:50:20   akaushal
 * Added function for button click in PrepareFunctionMapTable().Code added to safely close console.
 * 
 *    Rev 1.6   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.5     06 Mar 2014 11:30:44 rjamloki   
 * Add new User ID function
 *
 *    Rev 1.4     05 Mar 2014 14:13:36 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:07:26 rjamloki  
 * Header fix.
 *
 *    Rev 1.2     18 Dec 2013 10:00:34 rjamloki  
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:40 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:06 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "BitmaskVariable.h"
#include "ChildView.h"
#include "EnumCondition.h"
#include "EnumVariable.h"
#include "HostCommand.h"
#include "LocalChoice.h"
#include "MainFrame.h"
#include "Text.h"
#include "Toggle.h"
#include "VGA.h"
#include "VgaBottomMenu.h"
#include "VgaMenu.h"
#include "XmlElement.h"
#include "VgaVariable.h"
#include <WinCon.h>
#include "InputDevices.h"

#ifdef DISABLEPRINTF
	#define printf
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CList<CString,CString> tempList;
CList<CString,CString> tempWeldList;
CList<CString,CString> tempHistoryList;
CList<CString,CString> tempGraphsList;
CList<CString,CString> tempScreenGraphsList;
CList<CString,CString> tempHornScanList;
CList<CString,CString> tempScanGraphDataList;
CList<CString,CString> tempSetupList;
CList<CString,CString> tempDUPSList;
CList<CString,CString> tempSequenceList;
CList<CString,CString> tempRunScreenList;
CList<CString,CString> tempUserIDList;
CList<CString,CString> tempEventHistoryList;
/////////////////////////////////////////////////////////////////////////////
// CVGAApp

BEGIN_MESSAGE_MAP(CVGAApp, CWinApp)
	//{{AFX_MSG_MAP(CVGAApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

FILE *consolePtr;
CVGAApp::CVGAApp()
{
	logOpen = false;
	gui = 0;
	total=0;
	menuName = "Language Menu";
	TotalLangElement=0;
	configFile = NULL;
	MenuPointer = NULL;
	m_hMutex = NULL;
	consolePtr = NULL;
}

CVGAApp::~CVGAApp()
{
	//logOpen = false;
	if(!tempList.IsEmpty())
	{	tempList.RemoveAll();
	}

	if(!tempWeldList.IsEmpty())
	{	tempWeldList.RemoveAll();
	}

	if(!tempHistoryList.IsEmpty())
	{	tempHistoryList.RemoveAll();
	}

	if(!tempGraphsList.IsEmpty())
	{	tempGraphsList.RemoveAll();
	}

	if(!tempScreenGraphsList.IsEmpty())
	{	tempScreenGraphsList.RemoveAll();
	}

	if(!tempHornScanList.IsEmpty())
	{	tempHornScanList.RemoveAll();
	}

	if(!tempScanGraphDataList.IsEmpty())
	{	tempScanGraphDataList.RemoveAll();
	}

	if(!tempSetupList.IsEmpty())
	{	tempSetupList.RemoveAll();
	}

	if(!tempDUPSList.IsEmpty())
	{	tempDUPSList.RemoveAll();
	}

	if(!tempSequenceList.IsEmpty())
	{	tempSequenceList.RemoveAll();
	}

	if(!tempRunScreenList.IsEmpty())
	{	tempRunScreenList.RemoveAll();
	}
	if(!tempUserIDList.IsEmpty())
	{	tempUserIDList.RemoveAll();
	}
	if(!tempEventHistoryList.IsEmpty())
	{	tempEventHistoryList.RemoveAll(); 
	}

	if(gui)delete gui;
	// ExitInstance();
}

// The one and only CVGAApp object
CVGAApp theApp;
int page_no;
bool OnKeypadScreen_flag;
HANDLE CVGAApp::hProcess=NULL;
CMapStringToPtr functionCall;


extern void ResetSensorCalib(int Address);
extern bool AuthCheckLoginFunc(CVgaButton *ptr);
extern void AuthorityCheckFunc(int value);
extern void MemoryFull_ContStop(int value);
extern bool AuthCheckLogoutFunc(CVgaButton *ptr);
extern void ChangeStartScreen(int value);
extern void SendCommandForChangePassword(int ID);
extern bool USBCheckFunction(CVgaButton *);
extern bool RefreshCheck(CVgaButton *);
extern void ExitSystemProgram(int Address);
extern void ExitColorMenu(int Address);
extern void ButtonColor(int Address);
extern void BackgroundColor(int Address);
extern void DefaultColor(int Address);
extern void TextColor(int Address);
extern void TitleColor(int Address);
extern void HighLightColor(int Address);
extern void ShowQualityScreen(int Address);
extern void HandleVGASaveButton(int Address);
extern void SendCommandForVGAButtonsPreset(int Address);
extern void SendCommandForRecallPreset(int Address);
extern void BuildLocalScreenSetupMenu(int Address);
extern void HistoryLeftButton(int Address);
extern void HistoryRightButton(int Address);
extern void HistoryScreenUpButton(int Address);
extern void HistoryUpButton(int Address);
extern void SendCommandForVGAButtonsSavePreset(int Address);
extern void HistoryDownButton(int Address);
extern void ShowPowerSupplyMessageScreen(int Address);
extern void HistoryScreenDownButton(int Address);
extern void GraphRefresh(int Address);
extern void Color_DistanceGraph(int Address);
extern void Power_Graph(int Address);
extern void Frequency_Graph(int Address);
extern void ExitEventHistoryMenu(int Address);
extern void ExitAlarmLogMenu(int Address);
extern void ExitGraphMenu(int Address);
extern void ExitBandLimitsMenu(int Address);
extern void Amplitude_Graph(int Address);
extern void Velocity_Graph(int Address);
extern void Force_Graph(int Address);
extern void ExitAlarmMenu(int Address);
extern void AlarmErrorBeep(int Address);
extern void ProcessColorSetup(int Address);
extern void ExitWindowProgram(int Address);
extern void WeldHistoryPrintNow(int Address);
extern void GraphsWeldNow(int Address);
extern void SetUpPrintNow(int Address);
extern void PowerPresetUpPressed(int Address);
extern void PowerPresetDownPressed(int Address);
extern void USBPresetUpPressed(int Address);
extern void USBPresetDownPressed(int Address);
extern void OverWriteOkButton(int Address);
extern void CopyPowerPreset(int Address);
extern void OverWriteCancelButton(int Address);
extern void ProcessUSBMemoryScreen(int Address);
extern void CopyAllPowerPreset(int Address);
extern void DeleteUSBPreset(int Address);
extern void CopyUSBPreset(int Address);
extern void BowseUSBFolder(int Address);
extern void ViewPowerPreset(int Address);
extern void USBForceSampleGraph(int Address);
extern void USBColDistanceGraph(int Address);
extern void USBAmplitudeGraphSample(int Address);
extern void USBPowerGraphSample(int Address);
extern void USBVelocityGraphSample(int Address);
extern void USBFrequencyGraphSample(int Address);
extern void USBWeldData(int Address);
extern void USBRecall(int Address);
extern void ExitHistoryMenu(int Address);
extern void HandleFolderHierarchyExit(int Address);
extern void ProcessHistoryGraph(int Address);
extern void ProcessUSBVelocityGraph(int Address);
extern void ProcessUSBFrquencyGraph(int Address);
extern void ProcessUSBColDistanceGraph(int Address);
extern void ProcessUSBForceGraph(int Address);
extern void ProcessUSBPowerGraph(int Address);
extern void ProcessUSBAmplitudeGraph(int Address);
extern void ExitHistoryGraph(int Address);
extern void SendVQSLimitQualityCommand(int Address);
extern void ProcessDebugMenuScreen(int Address);
extern void ModifyPowerSupplyName(int Address);
extern void ProcessDiagnosticScreen(int Address);
extern void ProcessResetAlarms(int Address);
extern void ProcessSoftwareMismatchError(int Address);
extern void CompareGraph_and_Data(int ID);
extern void SendCommandForSave(int ID);
extern void SendCommandForVGAButtons(int ID);
extern void PresetUpExecute(int ID);
extern void PresetPageDownExecute(int ID);
extern void PresetPageUpExecute(int ID);
extern void PresetDownExecute(int ID);
extern void ContinueSequence(int ID);
extern void InsertEditSequencePreset(int ID);
extern void ReplaceEditSequencePreset(int ID);
extern void DeleteEditSequencePreset(int ID);
extern void SendCommandForVerifyPreset(int ID);
extern void SendCommandForButton(int ID);
extern void SendCommandForButtons(int ID);
extern void SendCommandForDigitalOutput(int ID);
extern void StartScan(int ID);
extern void HornScanAbort(int ID);
extern void WeldRetract(int ID);
extern void SendCommandForTestingMenu(int ID);
extern void SendSpecialMenuCommand(int ID);
extern void SendHornDownCommand(int ID);
extern void AutoRefreshGraph(int ID);
extern void ProcessSequence(int ID);
extern void PMCScreenCheck(int ID);
extern void AddToAverageCommand(int ID);
extern void SendCommandForHSCGraph(int ID);
extern void HandleSaveScanAButton(int ID);
extern void HandleSaveScanBButton(int ID);
extern void HandleSaveScanCButton(int ID);
extern void SendAlarmMenuCommand(int ID);
extern void USBForceGraphSaveAlarm(int ID);
extern void USBDistanceGraphSaveAlarm(int ID);
extern void USBAmplitudeGraphSaveAlarm(int ID);
extern void USBPowerGraphSaveAlarm(int ID);
extern void USBVelocityGraphSaveAlarm(int ID);
extern void USBFrequencyGraphSaveAlarm(int ID);
extern void USBWeldDataSaveAlarm(int ID);
extern void USBGlobalFlagOn_Off(int ID);
extern void ProcessExtPrest(int ID);
extern void UpdateSW_Config(int ID);
extern void ProcessHornSignature(int ID);
extern void HornScanA(int ID,CLocalChoice *ptr);
extern void HornScanB(int ID,CLocalChoice *ptr);
extern void HornScanC(int ID,CLocalChoice *ptr);
extern void CurrentHornScan(int ID,CLocalChoice *ptr);
extern void CopyScanData(int ID,CLocalChoice *ptr);
extern bool AddPowerGraph(CVgaButton *ptr);
extern void SequenceUpButton(int Address);
extern void SequenceDownButton(int Address);
extern bool AddAvgPowerGraph(CVgaButton *ptr);
extern bool SendCommandForViewGraphs(CVgaButton *ptr);
extern bool ScanAOnOff(CLocalChoice *ptr);
extern bool CurrentScanOnOff(CLocalChoice *ptr);
extern bool ScanBOnOff(CLocalChoice *ptr);
extern bool ScanCOnOff(CLocalChoice *ptr);
extern bool ProcessAlarmMenu(CVgaButton *ptr);
extern bool ProcessAlarmExit(CVgaButton *ptr);
extern bool GetCurrentPresetScrn(CVgaButton *ptr);
extern bool GetPSPresetScrn(CVgaButton *ptr);
extern bool GetUSBPresetScrn(CVgaButton *ptr);
extern bool DisableColdStartFlag(CVgaButton *ptr);
extern bool CopyPowerPresetToList(CVgaButton *ptr);
extern bool EnableColdStartFlag(CVgaButton *ptr);
extern bool ProcessColorSetupScreen(CVgaButton *ptr);
extern bool ProcessUSBGraphButtonDisplay(CVgaButton *ptr);
extern bool AddStartUpVersion(CVgaButton *ptr);
extern bool AddSystemVersion(CVgaButton *ptr);
extern void SendCommandForUserID(int ID);
extern void SendCommandForUserLogin(int ID);
extern void SendCommandForEventLog(int ID);
extern void logOutFun(int ID);
extern void DiagUserIO(int ID);
extern void RecallAlarmLogProcess(int ID);
extern void AlarmLogLeftButton(int Address);
extern void AlarmLogRightButton(int Address);
extern void AlarmScreenUpButton(int Address);
extern void AlarmScreenDownButton(int Address);
extern void AlarmUpButton(int Address);
extern void AlarmDownButton(int Address);
extern void RecallEventLogProcess(int ID);
extern void EventLogRightButton(int Address);
extern void EventLogLeftButton(int Address);
extern void EventScreenUpButton(int Address);
extern void EventScreenDownButton(int Address);
extern void EventUpButton(int Address);
extern void EventDownButton(int Address);
extern void RecallUserIDProcess(int ID);
extern void UserIDScreenUpButton(int Address);
extern void UserIDScreenDownButton(int Address);
extern void UserIDUpButton(int Address);
extern void UserIDDownButton(int Address);
extern void SendNewUser(int Address);
extern void ModifyUser(int Address);
extern void DefaultUser(int Address);
extern void SendModifyUser(int Address);
extern void SendCommandForWeldHistory(int Address);
extern void ChangePassword(int ID);
extern void DeleteWeldHistory(int Address);
extern void DeleteEventHistory(int Address);
extern void StoreIdleLogoutTime(int Address);
extern void WeldResultColSetup(int Address);
extern void WeldResultScreen(int Address);
extern void EnableStateMachine(int ID);
extern void StopStateMachine(int ID);
extern void BasicExpertClick(int Value);
extern bool CheckOperatorFunc(CVgaButton *ptr);
extern bool CheckSupervisorFunc(CVgaButton *ptr);
extern bool CheckForNameDisplay(CVgaButton *ptr);
extern bool CheckForReasonDisplay(CVgaButton *ptr);
extern bool CheckDisplayChangePWButton(CVgaButton *ptr);
extern void SwUpGrade(int arg);
extern void DisplayEventDesciption(int Address);
/////////////////////////////////////////////////////////////////////////////
// CVGAApp initialization
FILE * DebugFilePtr;
/*
Function called at startup ad provided the IP for weld controllert through serial communication
*/
void sendNetworkInfo(void)
{
	unsigned char net_data[12] ; 
	union 
	{
		struct
		{
			unsigned long a1;      	
			unsigned long a2;
			unsigned long a3; 
		}s;
		
		char c[12];
	}u;
	
	//printf("in sendNetworkInfo \n");
	u.s.a1=(CApplication::ip_addr);
	u.s.a2=(CApplication::mask_addr);
	u.s.a3=(CApplication::gateway_addr);
	
	//copy all the 3 address to union
    for(int i = 0;i < 12 ; i++)
		net_data[i]=u.c[i];	
	
	CHostCommand * request = new CHostCommand(NETINFO_FunID,net_data,NETINFO_LEN);
	CHostCommand * response = NULL;
    bool AddressSent=false;
	unsigned char * data;
	int length =0;
	char ch =0;
	while(!AddressSent)
	{
		//printf("sending network info \n");
		response = app->SendUiSerialHostCommand(request);
		if( response )
		{
			length = response->GetDataLength();
			ch=CHostCommand::AckNak();
			data = response->GetData();
			if(ch==theApp.ACK)
			{
				if( data[0] == 0x1 )
                {
					AddressSent = true;
					//printf("network info send success \n");
				}				
				
			}
			else if(ch==theApp.NAK)
				printf("network info NAK  \n");
		}
		Sleep(2000);
	}
   if(response != NULL)
	delete response;
    //printf("sendNetworkInfo done\n");
}

BOOL CVGAApp::InitInstance()
{

	m_hMutex = CreateMutex( NULL, FALSE,_T("_2000XC_UTIL_"));
	
	if ( GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return FALSE;
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	
	// Mouse Detect First Time
	MouseDetect(true);	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	/*Attach console to app*/
	AllocConsole() ;
	consolePtr = freopen( "CON", "w", stdout );
	//DebugFilePtr = _wfreopen( _T("DebugFile.txt"), _T("w"), stdout );
	InitTasks();

#ifdef RUN_ON_SBC
	sendNetworkInfo(); //send ip,mask,gateway to wc
#endif
	
	printf("\n returned from Sendnetwork Info");
	PrepareFunctionMapTable();

	
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;


	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();


	return TRUE;
}

// This implementation is for VGA only
void CVGAApp::Trace(const CString &str)
{
	TRACE(_T("%s\n"), str);
}
int CVGAApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if(m_hMutex)
	{
		::ReleaseMutex(m_hMutex);
		::CloseHandle(m_hMutex);
	}
	//fclose(DebugFilePtr);
	if(consolePtr)
		fclose(consolePtr);
	FreeConsole();
	Clean();
	return CApplication::ExitInstance();
}

/**********************************************************************************/
/*                                                                                */
/* This function Reads whole XML document in CArchive Class & draws first menu screen.  */
/**********************************************************************************/

bool CVGAApp::ReadXML()
{
	CFile F;

	if( !F.Open(_T("C:\\Program Files\\Branson\\2000Xc\\Main.gui"), CFile::modeRead)) 
	{	
		return false;
	}
	CArchive arc(&F,CArchive::load);
	if (gui)
		delete gui;

	gui = file.Read(arc);
	if (gui)
	{
		  printf("\n parsing "); 
		ParseXmlTree(gui);
		// printf("\n menulook entry");
	}
	else
	{
		AfxMessageBox(_T("Parsing can'not be done."));
		exit(1); 
	}
	//Authority check i5 enabled so display login screen
	if(CChildView::thisPtr->AuthorityCheckSartUp == true)
	{
    	menuName = XSTR(LOGINMENU);
		CChildView::thisPtr->LoginScreenFlag = true;
	}
	else
	{
		CChildView::thisPtr->LoginScreenFlag = false;
		if(CChildView::thisPtr->Start_Screen==MAINMENU)
		{
			menuName = CVgaBottomMenu::mainMenuID;
		}
		else
		{
			CChildView::thisPtr->RunResultScreen = true;
			menuName = CVgaBottomMenu::WeldResults_ID;
		}
	}

	CVgaMenu * menu;

	if (menus.Lookup(menuName, menu))
	{
			printf("\n menulook");
		CChildView::thisPtr->menusname.AddTail(menuName);
		CChildView::thisPtr->menus.AddTail(1);
		CChildView::thisPtr->menupointers.AddTail(menu);
		MenuPointer=menu;
		CChildView::thisPtr->ModifyObjectList(menu);   
	}
	return true;

}

/**********************************************************************************/
/*                                                                                */
/*  This function Parse whole XML document & calls constructor of menu items one  */
/*   by one.	                                                                  */
/**********************************************************************************/

void CVGAApp::ParseXmlTree(CXmlElement *gui)
{
	ASSERT(gui->tag == "gui");
	POSITION pos = gui->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = gui->children.GetNext(pos);
		CString tag = element->tag;
		if (tag == "enumvariable")
		{
			CreateEnumVariable(element);
		}
		else if (tag == "bitvariable")
		{
			CreateBitVariable(element);
		}
		else if (tag == "menu")
		{
			CreateMenu(element);
		}
		else if (tag == "EventEng")
		{
			CreateEventDesc(element);
		}
		else if(tag == "ParamEng")
		{
			CreateParamDesc(element);
		}
		else if(tag=="special")
		{
			int gh=_ttoi(element->GetAttribute("name"));
			SpecialMenu.SetSize(gh);
		}
		else if(tag=="Key")
		{
			CString Temp=element->GetAttribute("name");
			SpecialMenu[total++]= element->GetAttribute("name");
		}
		else if(tag=="bottomMenu")
		{
			CVgaBottomMenu::InitializeBottomMenuMembers(element);
		}
		else if(tag=="variableinfo")
		{
			CScreenKeypad::SetVariableStrings(element);
		}
		else if(tag=="WeldDataHeading")
		{
			CChildView::thisPtr->TotalTextHeading =_ttoi(element->GetAttribute("TotalParam"));	
			//printf("\n CChildView::thisPtr->TotalTextHeading=%d",CChildView::thisPtr->TotalTextHeading);
			CChildView::thisPtr->GetAllWeldDataHeading(element);
		}
		else if(tag=="AlarmDataHeading")
		{
			CChildView::thisPtr->TotalAlarmHeading = _ttoi(element->GetAttribute("TotalParam"));
			CChildView::thisPtr->GetAlarmLogDataHeading(element);
		}
		else if(tag=="EventDataHeading")
		{
			CChildView::thisPtr->TotalEventHeading = _ttoi(element->GetAttribute("TotalParam"));
			CChildView::thisPtr->GetEventLogDataHeading(element);
		}
		else if(tag=="UserIDHeading")
	    {
		  CChildView::thisPtr->TotalUserIDTextHeading =_ttoi(element->GetAttribute("TotalParam"));	
		  //printf("TotalUserIDTextHeading = %S",CChildView::thisPtr->TotalUserIDTextHeading);
		  //printf("\n CChildView::thisPtr->TotalTextHeading=%d",CChildView::thisPtr->TotalTextHeading);
	     CChildView::thisPtr->GetAllUserIDHeading(element);
	    }
		else if(tag=="UserIDDataHeading")
		{
			CChildView::thisPtr->TotalUserIDHeading = _ttoi(element->GetAttribute("TotalParam"));
			CChildView::thisPtr->GetUserIDDataHeading(element);
		}
		else if(tag=="AlarmButtonmenu")
		{
			CChildView::thisPtr->AlarmMenuIdentifier=element->GetAttribute("name");
			/*for(int i=0;i<(CChildView::thisPtr->AlarmMenuIdentifier.GetLength ());i++)
			{
			printf(" %c",CChildView::thisPtr->AlarmMenuIdentifier.GetAt (i));
			}*/
		}
		else if(tag=="PrintStrings")
			CreatePrintStrings(element);	
		else if(tag=="AlarmsStrings")
			CreateAlarmStrings(element);	
		else if(tag=="AlarmEng")
		{	
			int TotalStrings=_ttoi(element->GetAttribute("TotalString"));

			CChildView::thisPtr->AlarmEng.SetSize(TotalStrings);
			CreateAlarmEng(element);	
		}
		else if(tag=="ManualGraphStringsList")
		{
			int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
			CChildView::thisPtr->Manual.SetSize(TotalStrings);
			CreateManualGraph(element);	
		}
		else if(tag=="GraphPrText")
		{
			int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
			CChildView::thisPtr->GraphPrText.SetSize(TotalStrings);
			CreateGraphPrText(element);
		}
		else if(tag=="PresetStrings")
		{	 int gh=_ttoi(element->GetAttribute("TotalString"));

		CChildView::thisPtr->PString.SetSize(gh);
		//	 CChildView::thisPtr->PString.FreeExtra();
		CreatePresetString(element);	
		}
		else if(tag=="LabelStrings")
		{	int gh=_ttoi(element->GetAttribute("TotalString"));
		CChildView::thisPtr->LString.SetSize(gh);
		CreateLabelStrings(element);
		}
		else if(tag=="PrintHSInfoText")
		{
			int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
			CChildView::thisPtr->PrintHSInfoText.SetSize(TotalStrings);
			CreateHSInfoText(element);
		}
		else if(tag=="OnLinePrint")
		{
			int Count=0;
			POSITION pos = element->children.GetHeadPosition();
			while (pos)
			{
				// printf("\n OnLinePrint");
				CXmlElement * e = element->children.GetNext(pos);
				ASSERT(e->tag == "PrintMenu");
				CString name = e->GetAttribute("name");
				CString value = e->GetAttribute("value");
				CVgaMenu *ptr = NULL;
				if(value!="")
				{
					if(menus.Lookup(value, ptr))//coverity 11350					
					{
						   if(Count==0)
						   {
							   CChildView::thisPtr->SetupMenuPointer=ptr;
							   CChildView::thisPtr->ModifyObjectList(ptr);
						   }
						   else if(Count==1)
						   {
							   CChildView::thisPtr->SequenceMenuPointer=ptr;
							   CChildView::thisPtr->ModifyObjectList(ptr);
						   }
						   else if(Count==2)
							   CChildView::thisPtr->USBGraphMenu=value;
					}
				}
				Count++;
				// OnLinePrintLookUpMenu.SetAt(name1, value1);
			}
		}
		else if(tag=="MonthStrings")
		{
			int TotalStrings=_ttoi(element->GetAttribute("TotalString"));
			CChildView::thisPtr->AllMonthStrings.SetSize(TotalStrings);
			CreateMonthStrings(element);
		}
		// else
		//		ASSERT(FALSE);
	}
	printf("parse XML done\n");
}

void CVGAApp::CreatePrintStrings(CXmlElement *e)
{ 	
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();

		CString Temp=element->GetAttribute("textID");

		if (tag == _T("WeldDataString"))
		{	
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempWeldList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("HistoryWeldDataString"))
		{ //printf("tag==Historywelddatastring \n");
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempHistoryList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("UserIDString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempUserIDList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
			else if(tag==_T("EventHistoryString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
			   temp1 = Temp.SpanExcluding(_T(" "));
			   len = temp1.GetLength();
			   temp1=CVgaMenuItem ::LinearSearch(temp1);
			   tempEventHistoryList.AddTail(temp1);
			   len1 = len1-len-1;
			   Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("GraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempGraphsList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("ScreenGraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempScreenGraphsList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("HornScanString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempHornScanList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintScanGraphsString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempScanGraphDataList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintSetupString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempSetupList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintDUPSString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempDUPSList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("PrintSequenceString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempSequenceList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		else if(tag==_T("RunScreenPrintString"))
		{
			CString temp1;
			int len1,len;
			len1 = Temp.GetLength();

			while(len1>0)
			{
				temp1 = Temp.SpanExcluding(_T(" "));
				len = temp1.GetLength();
				temp1=CVgaMenuItem ::LinearSearch(temp1);
				tempRunScreenList.AddTail(temp1);
				len1 = len1-len-1;
				Temp = Temp.Right(len1);
			}
		}
		//else
		//			ASSERT(FALSE);
	}

}

void CVGAApp::CreateAlarmStrings(CXmlElement *e)
{		POSITION pos = e->children.GetHeadPosition();

while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString Temp = element->GetAttribute("StringID");
	CString name = element->GetAttribute("TextID");
	CChildView::thisPtr->AlarmMap.SetAt(Temp,name);
}
}

void CVGAApp::CreateAlarmEng(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;
while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->AlarmEng.SetAt(k++,name);
}
}

void CVGAApp::CreatePresetString(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;

while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->PString.SetAt(k++,name);
	//CChildView::thisPtr->PString.Add(name);
}	
}

void CVGAApp::CreateLabelStrings(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;

while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->LString.SetAt(k++,name);
	//CChildView::thisPtr->PString.Add(name);
}	
}


void CVGAApp::CreateHSInfoText(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;
while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->PrintHSInfoText.SetAt(k++,name);
}
}

void CVGAApp::CreateManualGraph(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;
while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->Manual.SetAt(k++,name);
}
}

void CVGAApp::CreateGraphPrText(CXmlElement *e)
{	POSITION pos = e->children.GetHeadPosition();
int k=0;
while (pos)
{
	CXmlElement * element = e->children.GetNext(pos);
	CString name = element->GetAttribute("textID");
	name=CVgaMenuItem ::LinearSearch(name);
	CChildView::thisPtr->GraphPrText.SetAt(k++,name);
}
}

void CVGAApp::CreateMonthStrings(CXmlElement *e)
{	
	POSITION pos = e->children.GetHeadPosition();
	int k=0;
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString name = element->GetAttribute("textID");
		name=CVgaMenuItem ::LinearSearch(name);
		CChildView::thisPtr->AllMonthStrings.SetAt(k++,name);
	}
}

void CVGAApp::CreateEnumVariable(CXmlElement *element)
{
	CEnumVariable * var = new CEnumVariable(element);
	variables.SetAt(var->name, var);
}

void CVGAApp::CreateBitVariable(CXmlElement *element)
{

	CBitmaskVariable * var = new CBitmaskVariable(element);
	variables.SetAt(var->name, var);
}

void CVGAApp::CreateMenu(CXmlElement *element)
{
	CVgaMenu * menu = new CVgaMenu(element);
	menus.SetAt(menu->GetName(), menu);
}
/**************************************************************************************/
/* This function is called from the ParseXmlTree function at powerup and stores       */
/* Event Description strings based on event id and text id given in main to gui file  */
/**************************************************************************************/
void CVGAApp::CreateEventDesc(CXmlElement * element)
{
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		EventDescription * ed = new EventDescription(e);
		eds.SetAt(ed->GetEventID(), ed);
	}	
}
/**********************************************************************************************/
/* This function is called from the ParseXmlTree function at powerup and stores               */
/* Parameter Description strings based on parameter id and text id given in main to gui file  */
/**********************************************************************************************/
void CVGAApp::CreateParamDesc(CXmlElement * element)
{
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		ParamDescription * pd = new ParamDescription(e);
		pds.SetAt(pd->GetParamID(), pd);
	}	
	
}


void CVGAApp::DrawMenu(CDC *pDC)
{
	//  CVgaMenu * menu;
	//   if (menus.Lookup(menuName, menu))
	if(MenuPointer!=NULL)
	{	
		//if(menuName != "Language Menu")
		{

			CChildView::thisPtr->Add_Back_Next_Button();
		}
		CChildView::thisPtr->Back_Next_Button_Layout();
		// printf("\n menu draw");
		MenuPointer->Draw(pDC);      
	}
	else
	{
		return;
	}

}

CVariable * CVGAApp::GetVariable(const CString &varName) const
{
	CVariable * var;
	if (variables.Lookup(varName, var))
	{
		return var;
	}
	return 0;
}


void CVGAApp::Clean()
{
	menuName = CVgaBottomMenu::mainMenuID;
	CChildView::BottomHalfTimerOn=true;
	if (gui)
	{
		//	printf("\n gui");
		delete gui;
		gui = 0;
	}
	if(!functionCall.IsEmpty())
	{
		//printf("\n functionCall");
		functionCall.RemoveAll();
	}
	//printf("\n menus");
	menus.DeleteAll();
	variables.DeleteAll();
	pds.DeleteAll();
	eds.DeleteAll();

	while(GraphsDataList.GetCount()>0)
		delete GraphsDataList.RemoveHead();

	/* while(CChildView::thisPtr->PrintWeldHistoryList2.GetCount()>0)
	delete CChildView::thisPtr->PrintWeldHistoryList2.RemoveHead();*/

	CWnd *pWndPrev;
	if (pWndPrev = CWnd::FindWindow(NULL,_T("VQS")))
	{
		//printf("\n PostMessage");
		CloseHandle(hProcess);// Closing Handle of VQS Application
		pWndPrev->PostMessage(WM_CLOSE,0,0);
	}
}

/**********************************************************************************/
/*                                                                                */
/*  This function will send Host Command to 332 & gets all variables at Start up  */
/*   	                                                                          */
/**********************************************************************************/

void CVGAApp::GetSystemVariable()
{
	CHostCommand * request = new CHostCommand(GetSysVariable_FunId,0,0);
	CHostCommand * response = app->SendUiHostCommand(request);
	printf("in GetSystemVariable reponse=%X",response);
	if(response)
	{
		char ch=CHostCommand::AckNak();
		unsigned char *data = response->GetData();
		int length = response->GetDataLength();
		int ResponseLengthCtr = length; 	
		if(ch==ACK)
		{
			CChildView::ControlLevel=*data++;length--;
			if(CChildView::ControlLevel < LEVEL_C)
				CChildView::Max_Allowed_Weld_Log = MAX_ALLOWED_WELD_LEVEL_D;
			else
				CChildView::Max_Allowed_Weld_Log = MAX_ALLOWED_WELD_LEVEL_C;
			
		    printf("\n length %d \n",ResponseLengthCtr);
			
			if ( (ResponseLengthCtr == MICROC_WITH_AUTHENTIFICATION_SYSTEM_VARIABLES_SIZE) || (ResponseLengthCtr == MICROC_WITHOUT_AUTHENTIFICATION_SYSTEM_VARIABLES_SIZE) )
			{
				CChildView::Actuator=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
			}
			else
			{
				CChildView::Actuator=*data++;length--;
			}

			CChildView::WeldMode=*data++;length--;
			CChildView::Securitylevel=*data++;length--;
			CChildView::AccessLevelSystem=*data++;length--;
			CChildView::SWconfiguration=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			CChildView::HWconfiguration=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
			printf("\n controlLevel = %d \n", CChildView::ControlLevel);
			printf("Actuator = %d \n", CChildView::Actuator);
			if( CChildView::ControlLevel < LEVEL_C)
				Max_Preset_Possible = MAX_PRESET_BELOW_C;
			else
				Max_Preset_Possible = MAX_PRESET_IN_C;
			/* union 
			{
			bool i;
			char c;
			} u;
			u.c = *data++;length--;
			CChildView::metric=u.i;*/
			unsigned char temp = *data++;
			length--;
			if((temp & 0x01) == 0x01 )
				CChildView::metric = true;
			else
				CChildView::metric = false;

			if((temp & 0x10) == 0x10 )
				CChildView::AutoRefreshon = true;
			else
				CChildView::AutoRefreshon = false;
			union 
			{
				bool i;
				char c;
			} u1;
			u1.c = *data++;length--;
			CChildView::PasswordFlag=u1.i; 
            u1.c = *data++;length--;
            CChildView::thisPtr->MemoryfullCont_Stop = u1.i;
			if(CChildView::ControlLevel < LEVEL_C)
				CChildView::thisPtr->MemoryfullCont_Stop = true;
			unsigned char c = *data++;
			CToggle::SequencingON = (c != 0); 
			length--;

			CChildView::BasicExpert = CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
			printf("BasicExpert=%d\n",CChildView::BasicExpert);
			CChildView::Automation = (CVgaMenuItem::Convert_Char_To_Integer(data,length,3) != 0);
			printf("CChildView::Automation=%d\n",CChildView::Automation);		
			CChildView::thisPtr->AuthorityCheckSartUp = (CVgaMenuItem::Convert_Char_To_Integer(data,length,3) != 0);

			printf("CChildView::thisPtr->AuthorityCheckSartUp=%d \n",CChildView::thisPtr->AuthorityCheckSartUp);

			CChildView::thisPtr->IdleLogoutTime = 0;
			if(CChildView::Automation == false)
			{
				if(CChildView::thisPtr->AuthorityCheckSartUp == true)
					CChildView::thisPtr->IdleLogoutTime = CVgaMenuItem::Convert_Char_To_Integer(data,length,0)*60*1000;
			}
			
			printf("CChildView::thisPtr->IdleLogoutTime =%d \n",CChildView::thisPtr->IdleLogoutTime);
			int UserCond = CVgaMenuItem::Convert_Char_To_Integer(data,length,2);

			//CChildView::UserChangeCond |= USER_SUPERVISOR;//USER_TECHNICIAN;//USER_OPERATOR;//CChildView::Securitylevel;
			//UserCond = 2 + 4 + 16 ;
            
			CChildView::UserChangeCond = UserCond; //(UserCond >>8);

			CChildView::thisPtr->AuthorityCheck = CChildView::thisPtr->AuthorityCheckSartUp;
		}
	}
	printf("CL = %d,ACT=%d ,WldMD=%d,SecLvl=%d ,AccLvlSys=%d ,SWConf=%d ,HWConf=%d \n", CChildView::ControlLevel,CChildView::Actuator,CChildView::WeldMode,CChildView::Securitylevel,CChildView::AccessLevelSystem,CChildView::SWconfiguration,CChildView::HWconfiguration);

}

void CVGAApp::PrepareStringFromUnicodeText(CString Str,bool FirstTime,bool skipFirstLine)
{
	CString name="C:\\Program Files\\Branson\\2000Xc"/*+\\languages\\")*/+Str;
	configFile=new CTextFileIO(name,L"rb",FirstTime);
	//printf("CTextFileIO()\n");
	TRACE(_T("CTextFileIO()\n"));

	configFile->ReadLineW(FirstTime,skipFirstLine);
	//printf("ReadLineW()\n");
}

void CVGAApp::PrepareFunctionMapTable()
{
	void (*Pointer)(int)=ExitSystemProgram;
	void *ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitSystemProgram"),ptr);

	Pointer=ExitColorMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitColorMenu"),ptr);

	Pointer=ButtonColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ButtonColor"),ptr);

	Pointer=BackgroundColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BackgroundColor"),ptr);

	Pointer=DefaultColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DefaultColor"),ptr);

	Pointer=TextColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("TextColor"),ptr);

	Pointer=TitleColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("TitleColor"),ptr);

	Pointer=HighLightColor;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HighLightColor"),ptr);

	Pointer=BuildLocalScreenSetupMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BuildLocalScreenSetupMenu"),ptr);

	Pointer=HandleVGASaveButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleVGASaveButton"),ptr);

	Pointer=SendCommandForVGAButtonsPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtonsPreset"),ptr);

	Pointer=SendCommandForRecallPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForRecallPreset"),ptr);

	Pointer=HistoryLeftButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryLeftButton"),ptr);

	Pointer=HistoryRightButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryRightButton"),ptr);

	Pointer=HistoryScreenUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryScreenUpButton"),ptr);

	Pointer=HistoryScreenDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryScreenDownButton"),ptr);

	Pointer=HistoryUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryUpButton"),ptr);

	Pointer=HistoryDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HistoryDownButton"),ptr);

	Pointer=ShowPowerSupplyMessageScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ShowPowerSupplyMessageScreen"),ptr);

	Pointer=SequenceUpButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequenceUpButton"),ptr);

	Pointer=SequenceDownButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SequenceDownButton"),ptr);

	Pointer=ShowQualityScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ShowQualityScreen"),ptr);

	Pointer=GraphRefresh;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("GraphRefresh"),ptr);

	Pointer=SendCommandForVGAButtonsSavePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtonsSavePreset"),ptr);

	Pointer=Color_DistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Color_DistanceGraph"),ptr);

	Pointer=Power_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Power_Graph"),ptr);

	Pointer=Velocity_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Velocity_Graph"),ptr);

	Pointer=Force_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Force_Graph"),ptr);

	Pointer=Amplitude_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Amplitude_Graph"),ptr);

	Pointer=Frequency_Graph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("Frequency_Graph"),ptr);

	Pointer=ExitEventHistoryMenu;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("ExitEventHistoryMenu"),ptr);

	Pointer=ExitAlarmLogMenu;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("ExitAlarmLogMenu"),ptr);

   Pointer=ExitGraphMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitGraphMenu"),ptr);

	Pointer=ExitBandLimitsMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitBandLimitsMenu"),ptr);

	Pointer=ExitAlarmMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitAlarmMenu"),ptr);

	Pointer=AlarmErrorBeep;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AlarmErrorBeep"),ptr);

	Pointer=ProcessColorSetup;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessColorSetup"),ptr);

	/*Pointer=ProcessPollingTimeMsgScrn;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessPollingTimeMsgScrn"),ptr);*/

	Pointer=PresetDownExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetDownExecute"),ptr);

	Pointer=PresetUpExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetUpExecute"),ptr);

	Pointer=PresetPageDownExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetPageDownExecute"),ptr);

	Pointer=PresetPageUpExecute;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PresetPageUpExecute"),ptr);

	Pointer=ContinueSequence;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ContinueSequence"),ptr);

	Pointer=InsertEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("InsertEditSequencePreset"),ptr);  

	Pointer=ReplaceEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ReplaceEditSequencePreset"),ptr);

	Pointer=DeleteEditSequencePreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteEditSequencePreset"),ptr);

	Pointer=SendCommandForSave;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForSave"),ptr);

	Pointer=SendCommandForVerifyPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVerifyPreset"),ptr);

	Pointer=SendCommandForButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForButton"),ptr);

	Pointer=SendCommandForButtons;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForButtons"),ptr);

	Pointer=SendCommandForDigitalOutput;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("SendCommandForDigitalOutput"),ptr);

	Pointer=StartScan;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("StartScan"),ptr);

	Pointer=HornScanAbort;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HornScanAbort"),ptr);

	Pointer=WeldRetract;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldRetract"),ptr);

	Pointer=SendCommandForTestingMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForTestingMenu"),ptr);

	Pointer=SendSpecialMenuCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendSpecialMenuCommand"),ptr);

	Pointer=SendHornDownCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendHornDownCommand"),ptr);

	Pointer=SendCommandForVGAButtons;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForVGAButtons"),ptr);

	Pointer=AutoRefreshGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AutoRefreshGraph"),ptr);

	Pointer=ProcessSequence;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessSequence"),ptr);

	Pointer=PMCScreenCheck;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PMCScreenCheck"),ptr);

	Pointer=AddToAverageCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AddToAverageCommand"),ptr);

	Pointer=SendCommandForHSCGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForHSCGraph"),ptr);

	Pointer=HandleSaveScanAButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanAButton"),ptr);

	Pointer=HandleSaveScanBButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanBButton"),ptr);

	Pointer=HandleSaveScanCButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleSaveScanCButton"),ptr);

	Pointer=CompareGraph_and_Data;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CompareGraph_and_Data"),ptr);

	Pointer=SendAlarmMenuCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendAlarmMenuCommand"),ptr);

	Pointer=USBForceGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBForceGraphSaveAlarm"),ptr);

	Pointer=USBDistanceGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBDistanceGraphSaveAlarm"),ptr);

	Pointer=USBAmplitudeGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBAmplitudeGraphSaveAlarm"),ptr);

	Pointer=USBPowerGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPowerGraphSaveAlarm"),ptr);

	Pointer=USBVelocityGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBVelocityGraphSaveAlarm"),ptr);

	Pointer=USBFrequencyGraphSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBFrequencyGraphSaveAlarm"),ptr);

	Pointer=USBWeldDataSaveAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBWeldDataSaveAlarm"),ptr);

	Pointer=USBGlobalFlagOn_Off;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBGlobalFlagOn_Off"),ptr);

	Pointer=ProcessExtPrest;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessExtPrest"),ptr);

	Pointer=UpdateSW_Config;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("UpdateSW_Config"),ptr);

	Pointer=ExitWindowProgram;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitWindowProgram"),ptr);

	Pointer=WeldHistoryPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldHistoryPrintNow"),ptr);

	Pointer=GraphsWeldNow;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("GraphsWeldNow"),ptr);

	Pointer=SetUpPrintNow;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetUpPrintNow"),ptr);

	Pointer=PowerPresetUpPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerPresetUpPressed"),ptr);

	Pointer=PowerPresetDownPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PowerPresetDownPressed"),ptr);

	Pointer=USBPresetUpPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPresetUpPressed"),ptr);

	Pointer=USBPresetDownPressed;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPresetDownPressed"),ptr);

	Pointer=OverWriteOkButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("OverWriteOkButton"),ptr);

	Pointer=CopyPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyPowerPreset"),ptr);

	Pointer=OverWriteCancelButton;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("OverWriteCancelButton"),ptr);

	Pointer=ProcessUSBMemoryScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBMemoryScreen"),ptr);

	Pointer=CopyAllPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyAllPowerPreset"),ptr);

	Pointer=DeleteUSBPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteUSBPreset"),ptr);

	Pointer=CopyUSBPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CopyUSBPreset"),ptr);

	Pointer=BowseUSBFolder;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BowseUSBFolder"),ptr);

	Pointer=ViewPowerPreset;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ViewPowerPreset"),ptr);

	Pointer=USBForceSampleGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBForceSampleGraph"),ptr);

	Pointer=USBColDistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBColDistanceGraph"),ptr);

	Pointer=USBAmplitudeGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBAmplitudeGraphSample"),ptr);

	Pointer=USBPowerGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBPowerGraphSample"),ptr);

	Pointer=USBVelocityGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBVelocityGraphSample"),ptr);

	Pointer=USBFrequencyGraphSample;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBFrequencyGraphSample"),ptr);

	Pointer=USBWeldData;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBWeldData"),ptr);

	Pointer=ModifyPowerSupplyName;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ModifyPowerSupplyName"),ptr);

	Pointer=USBRecall;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("USBRecall"),ptr);

	Pointer=ExitHistoryMenu;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitHistoryMenu"),ptr);

	Pointer=HandleFolderHierarchyExit;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("HandleFolderHierarchyExit"),ptr);

	Pointer=ProcessHistoryGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessHistoryGraph"),ptr);

	Pointer=ProcessUSBVelocityGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBVelocityGraph"),ptr);

	Pointer=ProcessUSBFrquencyGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBFrquencyGraph"),ptr);

	Pointer=ProcessResetAlarms;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessResetAlarms"),ptr);

	Pointer=ProcessUSBColDistanceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBColDistanceGraph"),ptr);

	Pointer=ProcessUSBForceGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBForceGraph"),ptr);

	Pointer=ProcessUSBPowerGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBPowerGraph"),ptr);

	Pointer=ProcessUSBAmplitudeGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessUSBAmplitudeGraph"),ptr);

	Pointer=ExitHistoryGraph;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitHistoryGraph"),ptr);

	Pointer=ProcessDiagnosticScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessDiagnosticScreen"),ptr);

	Pointer=ProcessHornSignature;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessHornSignature"),ptr);

	Pointer=SendVQSLimitQualityCommand;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendVQSLimitQualityCommand"),ptr);

	Pointer=ProcessDebugMenuScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessDebugMenuScreen"),ptr);

	Pointer=ProcessSoftwareMismatchError;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ProcessSoftwareMismatchError"),ptr);

	CString (*Pointer1)(CString)=CApplication::getIPAddress ;
	ptr = (void*)Pointer1;        
	functionCall.SetAt (_T("getIPAddress"),ptr);

	bool (*Pointer3)(CVgaButton *)=RefreshCheck;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("RefreshCheck"),ptr);

	Pointer3=AddPowerGraph;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddPowerGraph"),ptr);

	Pointer3=AddAvgPowerGraph;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddAvgPowerGraph"),ptr);

	Pointer3=ProcessAlarmMenu;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessAlarmMenu"),ptr);

	Pointer3=SendCommandForViewGraphs;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("SendCommandForViewGraphs"),ptr);

	Pointer3=ProcessAlarmExit;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessAlarmExit"),ptr);

	Pointer3=GetCurrentPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetCurrentPresetScrn"),ptr);

	Pointer3=GetPSPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetPSPresetScrn"),ptr);

	Pointer3=GetUSBPresetScrn;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("GetUSBPresetScrn"),ptr);

	Pointer3=DisableColdStartFlag;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("DisableColdStartFlag"),ptr);

	Pointer3=EnableColdStartFlag;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("EnableColdStartFlag"),ptr);

	Pointer3=USBCheckFunction;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("USBCheckFunction"),ptr);

	Pointer3=CopyPowerPresetToList;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("CopyPowerPresetToList"),ptr);

	/*Pointer3=ProcessDebugMenuScreen;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessDebugMenuScreen"),ptr);
	*/

	Pointer3=ProcessColorSetupScreen;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessColorSetupScreen"),ptr);

	Pointer3=ProcessUSBGraphButtonDisplay;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("ProcessUSBGraphButtonDisplay"),ptr);

	Pointer3=AddStartUpVersion;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddStartUpVersion"),ptr);

	Pointer3=AddSystemVersion;
	ptr = (void*)Pointer3;        
	functionCall.SetAt (_T("AddSystemVersion"),ptr);	

	bool (*Pointer4)(CLocalChoice *)=ScanAOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanAOnOff"),ptr);

	Pointer4=ScanBOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanBOnOff"),ptr);

	Pointer4=ScanCOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("ScanCOnOff"),ptr);

	Pointer4=CurrentScanOnOff;
	ptr = (void*)Pointer4;        
	functionCall.SetAt (_T("CurrentScanOnOff"),ptr);

	void (*Pointer5)(int,CLocalChoice *)=HornScanA;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanA"),ptr);

	Pointer5=HornScanB;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanB"),ptr);

	Pointer5=HornScanC;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("HornScanC"),ptr);

	Pointer5=CurrentHornScan;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("CurrentHornScan"),ptr);

	Pointer5=CopyScanData;
	ptr = (void*)Pointer5;        
	functionCall.SetAt (_T("CopyScanData"),ptr);

	/*Added for Ver.12*/
	Pointer=SendCommandForUserID;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForUserID"),ptr);

	//login button function
    Pointer=SendCommandForUserLogin;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForUserLogin"),ptr);
	
	Pointer=SendCommandForEventLog;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForEventLog"),ptr);
	
	Pointer=SendCommandForChangePassword;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendCommandForChangePassword"),ptr);

	Pointer1=CApplication::getMacAddress ; //mac address;
	ptr = (void*)Pointer1;        
	functionCall.SetAt (_T("getMacAddress"),ptr);
	
	Pointer=RecallAlarmLogProcess;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("RecallAlarmLogProcess"),ptr);

	Pointer=AlarmLogLeftButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmLogLeftButton"),ptr);

	Pointer=AlarmLogRightButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmLogRightButton"),ptr);

	Pointer=AlarmScreenUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmScreenUpButton"),ptr);

	Pointer=AlarmScreenDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmScreenDownButton"),ptr);

	Pointer=AlarmUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmUpButton"),ptr);

	Pointer=AlarmDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("AlarmDownButton"),ptr);

	Pointer=RecallEventLogProcess;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("RecallEventLogProcess"),ptr);

	Pointer=EventLogRightButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventLogRightButton"),ptr);

	Pointer=EventLogLeftButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventLogLeftButton"),ptr);

	Pointer=EventScreenUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventScreenUpButton"),ptr);

	Pointer=EventScreenDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventScreenDownButton"),ptr);

	Pointer=EventUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventUpButton"),ptr);

	Pointer=EventDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("EventDownButton"),ptr);       

	Pointer=RecallUserIDProcess;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("RecallUserIDProcess"),ptr);

	Pointer=UserIDScreenUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("UserIDScreenUpButton"),ptr);

	Pointer=UserIDScreenDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("UserIDScreenDownButton"),ptr);

	Pointer=UserIDUpButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("UserIDUpButton"),ptr);

	Pointer=UserIDDownButton;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("UserIDDownButton"),ptr);

	Pointer1=CApplication::getMacAddress ; //mac address;
	ptr = (void*)Pointer1;        
	functionCall.SetAt (_T("getMacAddress"),ptr);

	Pointer=logOutFun; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("logOutFun"),ptr);

	Pointer=ChangePassword; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ChangePassword"),ptr);

	Pointer=DiagUserIO; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DiagUserIO"),ptr);

	Pointer=SendNewUser; 
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("SendNewUser"),ptr);

	Pointer=ModifyUser; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ModifyUser"),ptr);

	Pointer=DefaultUser; 
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("DefaultUser"),ptr);

	Pointer=SendModifyUser; 
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("SendModifyUser"),ptr);

	Pointer=SendCommandForWeldHistory;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("SendCommandForWeldHistory"),ptr);

	Pointer=ChangeStartScreen;
	ptr = (void*)Pointer;
	functionCall.SetAt (_T("ChangeStartScreen"),ptr);

	Pointer=DeleteWeldHistory; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteWeldHistory"),ptr);

	Pointer=DeleteEventHistory; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DeleteEventHistory"),ptr);
	
	Pointer3=AuthCheckLogoutFunc; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("AuthCheckLogoutFunc"),ptr);
	
	Pointer3=AuthCheckLoginFunc; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("AuthCheckLoginFunc"),ptr);
	
    Pointer=AuthorityCheckFunc;
    ptr = (void*)Pointer;
	functionCall.SetAt (_T("AuthorityCheckFunc"),ptr);

    Pointer=MemoryFull_ContStop;
    ptr = (void*)Pointer;
	functionCall.SetAt (_T("MemoryFull_ContStop"),ptr);

	Pointer=ResetSensorCalib;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ResetSensorCalib"),ptr);

	Pointer=StoreIdleLogoutTime;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("StoreIdleLogoutTime"),ptr);

	Pointer=WeldResultColSetup;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldResultColSetup"),ptr);

	Pointer=WeldResultScreen;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("WeldResultScreen"),ptr);	

	Pointer=EnableStateMachine; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("EnableStateMachine"),ptr);

	Pointer=StopStateMachine; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("StopStateMachine"),ptr);
	
	Pointer=BasicExpertClick;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("BasicExpertClick"),ptr);

	Pointer3=CheckOperatorFunc; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckOperatorFunc"),ptr);
	
	Pointer3=CheckSupervisorFunc; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckSupervisorFunc"),ptr);

	Pointer3=CheckForReasonDisplay; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckForReasonDisplay"),ptr);

	Pointer3=CheckForNameDisplay; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckForNameDisplay"),ptr);

	Pointer3=CheckDisplayChangePWButton; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckNoBransonFunc"),ptr);
	
	Pointer=LookforBarcodeScan;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("LookforBarcodeScan"),ptr);
	
	Pointer = SwUpGrade;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SwUpGrade"),ptr);

	Pointer = SendClampAlarm;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendClampAlarm"),ptr);

	bool (*Pointer6)(CVgaAlphanumeric *)=AuthCheckClampFunc;
	ptr = (void*)Pointer6;
	functionCall.SetAt (_T("AuthCheckClampFunc"),ptr);
	Pointer=DownSpeedTuneFunc;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DownSpeedTuneFunc"),ptr);

	Pointer=SaveDownspeedtune;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SaveDownspeedtune"),ptr);

	Pointer=ExitDownspeedtune;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitDownspeedtune"),ptr);

	Pointer3=CheckDownspeedFlag; 
	ptr = (void*)Pointer3;
	functionCall.SetAt (_T("CheckDownspeedFlag"),ptr);

	Pointer = DownspeedTuneClick;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DownspeedTuneClick"),ptr);
	
	Pointer = SetDownspeedFlag;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetDownspeedFlag"),ptr);
	
	Pointer = SendEventReasonString;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendEventReasonString"),ptr);

	Pointer = AutomationClick;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AutomationClick"),ptr);
	
	Pointer = DisplayEventDesciption;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("DisplayEventDesciption"),ptr);

	Pointer = ExitMenuAndEnableWeld;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("ExitMenuAndEnableWeld"),ptr);

	Pointer = AddUnitToUser;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("AddUnitToUser"),ptr);

	Pointer = GetOLString;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("GetOLString"),ptr);

	bool (*Pointer7)(CVgaTitle *)=callInvalidate;
	ptr = (void*)Pointer7;
	functionCall.SetAt (_T("callInvalidate"),ptr);

	void (*PointerToggle)(CToggle *)=DrawPresetValidMsg;
	ptr = (void*)PointerToggle;        
	functionCall.SetAt (_T("DrawPresetValidMsg"),ptr);

	Pointer = SetValidated;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetValidated"),ptr);
	
	Pointer = CancelValidated;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CancelValidated"),ptr);

	Pointer = SetLocked;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SetLocked"),ptr);

	Pointer = CancelLocked;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CancelLocked"),ptr);

	Pointer = SendEstopLogin;
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("SendEstopLogin"),ptr);

	Pointer=CheckVerifiedPreset; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("CheckVerifiedPreset"),ptr);

	Pointer=StartSensorCal; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("StartSensorCal"),ptr);

	Pointer=PressureStepDownClick; 
	ptr = (void*)Pointer;        
	functionCall.SetAt (_T("PressureStepDownClick"),ptr);
}

void AfxMsgBox(CString x)
{
	int Returnvalue = AfxMessageBox(x,MB_SETFOREGROUND | MB_OK);
	if(Returnvalue==IDOK)
	{
		CWnd *pWndPrev;
		// Determine if a window with the class name exists...
		if (pWndPrev = CWnd::FindWindow(NULL,_T("2000Xc")))
			pWndPrev->SetForegroundWindow();
	}
}

