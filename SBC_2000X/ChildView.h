/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ChildView.h_v   1.45   29 Aug 2016 13:54:24   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ChildView.h_v  $
 * 
 *    Rev 1.45   29 Aug 2016 13:54:24   RJamloki
 * Added PRESSURESTEPDOWN_ALARM define and bool AuthorityCheckLogOut flag for the pressure hold step button
 * 
 *    Rev 1.44   21 Dec 2015 15:23:38   RJamloki
 * remove CChildView::OpAuthority
 *
 *    Rev 1.43   17 Nov 2015 17:06:36   RJamloki
 * Added a static variable to store the OpAuth
 *
 *    Rev 1.42   21 Apr 2015 16:57:54   rjamloki
 * Increased file path length define values to accomodate the full file paths of language and execuatable files we put in system config file.
 *
 *    Rev 1.41   16 Apr 2015 17:44:40   rjamloki
 * Removed unused HandleAlarmChangeInPolling(int TempAlarmCount) function.
 *
 *    Rev 1.40   16 Apr 2015 05:54:36   sesharma
 * MOUSE_DETECT_TIMER to auto hide the cursor if mouse is not plugged in.
 *
 *    Rev 1.39   01 Apr 2015 12:54:32   amaurya
 * WELDHISTORYPARAMWIDTH changed to 38 to avoid overlap for max cycle number string
 *
 *    Rev 1.38   28 Mar 2015 04:07:58   RJamloki
 * PRESET_BARCODE_START_ID moved to ChildView.h.
 *
 *    Rev 1.37   11 Mar 2015 09:25:52   amaurya
 * SIZEOFPRESETDATA macro changed as preset size increased due to the addition of setup limit parameters.PrintStreamingSetup() added to print setup limit to WeldSetup PDF.
 *
 *    Rev 1.36   02 Feb 2015 07:06:56   amaurya
 * Removed the declaration of CopyAllFlag.
 *
 *    Rev 1.35   30 Jan 2015 08:13:06   amaurya
 * USBPresetName_temp list added to keep USB preset name temporary on copyall button click.
 *
 *    Rev 1.34   26 Jan 2015 13:28:54   rjamloki
 * Added macros for statemachine start timer.
 *
 *    Rev 1.33   06 Jan 2015 07:59:04   AnPawar
 * Checking the estop reset login menu before starting state machine.
 *
 *    Rev 1.32   06 Jan 2015 05:12:02   AnPawar
 * defines for estop menu and reset menu.
 *
 *    Rev 1.31   02 Jan 2015 04:56:42   rjamloki
 * declarations related to usb preset copy all functionality
 *
 *    Rev 1.30   12 Dec 2014 06:05:52   RJamloki
 * HORNCLAMPMENU and ESTOPRESETMENU macros added.
 *
 *    Rev 1.29   11 Dec 2014 06:48:22   RJamloki
 * ENABLED_STR_ID  and DISABLED_STR_ID macros added.
 *
 *    Rev 1.28   28 Nov 2014 08:29:52   rjamloki
 * UpdateWeldHiddenFile() and UpdateEventHiddenFile() functions added and return type of initialiseTimer function changed(Coverity issue)
 *
 *    Rev 1.27   14 Nov 2014 10:38:44   AnPawar
 *  macros defined for downspeed tuning screen.
 *
 *    Rev 1.26   14 Nov 2014 02:53:26   rjamloki
 * EVENTTEXTSPACING macro changed.PdfWithImage() declaration changed.
 *
 *    Rev 1.25   10 Nov 2014 02:48:20   rjamloki
 * AssignFontForPrinting() and CStringToUTF() declaration added,LanguageEnum added and macros added.
 *
 *    Rev 1.24   20 Oct 2014 05:40:02   RJamloki
 *  SendLOGWeldData() prototype changed to resolve weld data missing issue and new macros defined for max allowed presets in control level d
 *
 *    Rev 1.23   01 Oct 2014 10:46:48   AnPawar
 * Changes for disk full and weld data log.Removed function declaration for VQS.
 *
 *    Rev 1.22   26 Sep 2014 10:39:28   rjamloki
 * added macros for preset strings length
 *
 *    Rev 1.21   25 Sep 2014 12:04:56   AnPawar
 * New Macros defined MINUTES_ID and DAY_ID
 *
 *    Rev 1.20   11 Sep 2014 09:43:18   rjamloki
 * Added event reason in enum ResponseType.
 *
 *    Rev 1.19   05 Sep 2014 06:57:56   amaurya
 * Changes for Level C.
 *
 *    Rev 1.18   02 Sep 2014 03:24:44   rjamloki
 *  USBMemoryFull falg and  ClearListOnUSBFullAlarm added for usb memory full alarm
 *
 *    Rev 1.17   26 Aug 2014 07:46:12   rjamloki
 * Added a macro SEVENWELDLINEGAP
 *
 *    Rev 1.16   18 Aug 2014 07:38:00   rjamloki
 * Added downspeed enable flag.
 *
 *    Rev 1.15   28 Jul 2014 13:33:32   rjamloki
 * added CString PowerSupplyIp and return type of print() function changed to boolean.
 *
 *    Rev 1.14   22 Jul 2014 08:08:20   akaushal
 * Weld and Event PDF page limit increased.
 *
 *    Rev 1.13   09 Jul 2014 06:47:08   akaushal
 * Some macro added.Added new variable in class.
 *
 *    Rev 1.12   09 Jun 2014 11:37:06   rjamloki
 * CChildview class modified.Added enums,removed printing variables.
 *
 *    Rev 1.11   27 May 2014 06:21:28   amaurya
 * updated macros for column and spacing.
 *
 *    Rev 1.10   20 May 2014 10:54:08   rjamloki
 * SIZEOFPRESETDATA macro changed.
 *
 *    Rev 1.9   07 May 2014 13:03:06   akaushal
 * Idle Logout time and Logon Screen
 *
 *    Rev 1.8   23 Apr 2014 11:21:26   akaushal
 * Changes for live data loggin and live Parameter heading in PDF
 *
 *    Rev 1.7   21 Apr 2014 13:29:36   akaushal
 * Added macros for diagnostic IO.Added declaration and variables for event log.
 *
 *    Rev 1.6   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.5     26 Mar 2014 14:21:34 rjamloki
 * GetCurrentFilePath(char *) declaraton changed.To create PDF with specific record type
 *
 *    Rev 1.4     05 Mar 2014 14:13:14 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.3     27 Feb 2014 01:07:52 jerryw.wang
 * Added some variables and heading Data function for the Alarm Log Screen and Event History Screen. Added the MenuType for the button arrangement on the specific Menu.
 *
 *    Rev 1.2     03 Jan 2014 09:04:46 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:18 amaurya
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:42 amaurya
 * Initial Revision.
*/


// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_)
#define AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_

#include "ScreenKeypad.h"
#include "HostCommand.h"
#include "USBFolder.h"
#include "HistoryData.h"
#include "UserID.h"
#include "EventHistoryData.h"
#include "hpdf.h"

#ifndef _WIN32_WCE
#define ERRORBEEP Beep(5000,100)
#else
#define ERRORBEEP
#endif

#define COLOR_NONE		-1
#define Black_DEFAULT	0
#define Black			1
#define Blue			2
#define Red				3
#define Green			4
#define Brown			5
#define Magenta		    6
#define Cyan			7
#define Dark_Gray		8
#define Gray			9
#define Yellow			10
#define White			11
#define SUCCESS          3
#define COMM_ERROR       2
#define NO_VALID_DATA     1

#define MENUENTRY_PER_PAGE    3
#define CORDLENGTH            2
#define CORDLENGTH1            3
#define ALPHAENTRYTIMER		  1
#define Pollingtimer		  2
#define BOTTOMHALFTIMER		   3
#define MessageScreenTimer	   4
#define PASSWORDTIMER		   5
#define PrinterStatusTimer    6
#define ERROR_MESSAGE_TIMER	7
#define USBSTATUSTIMER		   8
#define USBSTATUSTIMER1		   11
#define GETPRINTINGPARAMTIMER	9
#define LanguageSelectionTimer 10
#define DIAGNOSTICS_USERIO_TIMER 12
#define IDLELOGOUT_TIMER         13
#define START_SM_TIMER           14
#define MOUSE_DETECT_TIMER       15
#define POLLINGTIME			200
#define PrinterStatusTime	1000
#define USBSTATUSTIME		1000
#define MESSAGESCRNTIME		1000
#define DIAGNOSE_REFRESH_TIME 1000
#define IDLE_LOGOUT_TIME    10000

#define START_SM_TIME       2200    /* At Application start up we are sending state machine start command to WC after 2 seconds of
									first polling command, as polling timer is 200 ms, we need to initilize the state  machine timer with the value 2000+200=2200 ms*/
#define Page_No_Rect CRect(500,0,640,40)
#define VGA_Rect CRect(0 + XOFFSET, 0 + XOFFSET, 640 + XOFFSET, 480 + YOFFSET)
#define MESSAGESCRNRECT CRect(120,120,	520,360)
#define MESSAGESCRN_BLACKRECT CRect(119,119,521,361)
#define MAXSCRNButton_Height				380
#define MaxItemIn1ColMenu				   4
#define REDUCED_BUTTON_WIDTH			   170
#define MENU_BUTTON_WIDTH				   210
#define BUTTON_HEIGHT					   40
#define BUTTON_HEIGHT_Text				   30
#define MaxItems_PerPage				   8
#define left_coordinate_Radio			   100
#define left_coordinate_Not_Radio		26
#define left_coordinate_ItemIn1ColMenu	220
#define left_coordinate_2Col_Not_Radio	336
#define left_coordinate_2Col_Radio		360
#define top_coordinate_1_Button			60
#define Max_Text_1_Coloum				   10
#define BUTTON_GAP						   34
#define Y_CORDINATE_BACK_NEXT			   390
#define X_CORDINATE_BACK_NEXT			   530
#define BUTTON_WIDTH_BACK_NEXT			90
#define BUTTON_GAP_BACK_NEXT			   20
#define MAX_PSPRESET					      16
#define NextButtonRect	CRect(X_CORDINATE_BACK_NEXT,Y_CORDINATE_BACK_NEXT,X_CORDINATE_BACK_NEXT+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define BackButtonRect CRect(20,Y_CORDINATE_BACK_NEXT,BUTTON_WIDTH_BACK_NEXT+20,BUTTON_HEIGHT+Y_CORDINATE_BACK_NEXT)
#define ExitButtonRect CRect(260,Y_CORDINATE_BACK_NEXT,260+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define ExitWithSaveButtonRect CRect(220,Y_CORDINATE_BACK_NEXT,220+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)
#define SaveButtonRect CRect(330,Y_CORDINATE_BACK_NEXT,330+BUTTON_WIDTH_BACK_NEXT,Y_CORDINATE_BACK_NEXT+BUTTON_HEIGHT)

#define MAINMENU						0
#define SCREENSETUPMENU					1
#define COLORSETUP						2
#define FOLDERHIERARCHYONE				3
#define FOLDERHIERARCHYTWO				4
#define FOLDERHIERARCHYTHREE			5
#define FOLDERHIERARCHYFOUR			    6
#define VGAHistoryObject				33
#define VGAHistoryGraphObject			37
#define USBPRESETSCRN					9
#define VIEWPRESET						10
#define HISTORYGRAPHSCREEN			    11
#define USBPRESETFOLDER				    12
#define HSCOMPAREGRAPHSCRN				13
#define VGAPSHISTORY					14
#define VIEWCURRENTPRESET				15
#define USBHISTORY                      13
#define PSNAMELENGTH                    12
#define LOGINMENU                       601
#define CHANGEPASSWORDMENU              600
#define CHANGEPASSWORDMENUSYSCONFIG     632
#define WRONGUSERPASSWORD_MSG           611
#define CHANGEPASSWORD_SBC_MSG          619
#define ADDUSER_SBC_MSG                 620
#define MODIFYUSER_SBC_MSG              621
#define HORNCLAMPMENU                   633
#define ESTOPRESETMENU                  645
#define HORNDOWN_MENU                   179
#define DIAGNOSTIC_MENU                 166
#define ESTOP_MENU						249
#define RESET_MENU						248
#define ESTOPLOGINRESET_MENU            645
#define PRESSURESTEPDOWN_ALARM			660

#define USERNAME_ID						2701
#define PASSWORD_ID						1015
#define OLDPASSWORD_ID					4010
#define NEWPASSWORD_ID					4011
#define CONFIRMPASSWORD_ID				4012
#define USERID_ID						2702
#define USERLEVEL_ID					4013
#define STATUS_ID						2704
#define OPAUTHORITY_ID					4021
#define PASSEXPTIME_ID					4025
#define IDLELOGOUTTIME_ID				4026
#define USERSTATUS_ID					2704
#define PASSWORDEXP_ID					4025
#define BLANKBUTTON_ID					4086
#define MINUTES_ID						4251
#define DAYS_ID							4249
#define VALIDATE_ID						2959
#define LOCK_ID							2962
#define DOWNSPEEDCYCLE_EID				533
#define DOWNSPEEDUPDATE_EID				534
#define DOWNSPEEDUPDATE_EID_HD			583
#define DOWNSPEED_MENU_ID				178
#define HORN_DOWN_ENABLEID				401
#define ENABLED_STR_ID					4317
#define DISABLED_STR_ID					1179
#define INTEGERLENGTH					4
#define PRINTERNOTAVILABLE				0
#define PRINTERONLINE					1

#define Level_D							80
#define LEVEL_C							112

/* defines for screen setup*/
#define MAX_VGA_Y_VALUE					480
#define MAX_VGA_X_VALUE					640
#define ActualCalibCordinate_Xa			45
#define ActualCalibCordinate_Ya			433
#define WELD_PROCESS_ERROR	   			0x8001

#define SETUPID							0
#define GRAPHLISTSINGLEGRAPHID			1
#define GRAPHLISTDUALGRAPHID			2
#define GRAPHLISTTHREEGRAPHID			3
#define GRAPHLISTFOURGRAPHID			4
#define PRINTLISTGRAPHID				5
#define POWERGRAPHID					6
#define COLDISTANCEID					7
#define VELOCITYGRAPHID					8
#define FORCEGRAPHID					9
#define AMPLITUDEGRAPHID				10
#define FREQUENCYGRAPHID				11
#define WELDHISTORYID					12
#define WELDDATAONSAMPLEID				13
#define WELDDATAPRINTNOWID				14
#define	SCREENGRAPHS					15
#define	DUPSPRESET						16
#define	PRINTTABLEID					17
#define HORNSCANID						18
#define HSCGRAPHONE						19
#define HSCGRAPHTWO						20
#define HSCGRAPHTHREE					21
#define	HSCGRAPHFOUR					22

#define USERID							30
#define EVENTHISTORYID					31
#define ALARMLOGID						32
#define EVENTLIST						33
#define WELD_HISTORY_ID					34
#define COPYALL_PRESET_TOUSB			35
#define COPYALL_PRESET_TOUSB_OK			36

#define PRINTSEQUENCE					23
#define PRINT_HISTORY_DATA				24
#define PARAMETERSTARTXCORD				75
#define PARAMETERSTARTYCORD				250
#define PRINTWELDSTARTXCORD				5
#define PRINTWELDSTARTYCORD				20
#define PARAMWIDTH						69
#define PARAMWIDTHLIVE					28
#define WELDHISTORYPARAMWIDTH  		    38    //as max no of weld cycle no i can get = 2147483647,Increased to not to overlap Cycle no with String "Alarm"
#define GRAPHPARAMWIDTH					100
#define ONELINEGAP						25
#define TWOLINEGAP						50
#define THREELINEGAP					75
#define FIVELINEGAP						125
#define ONEWELDLINEGAP		            20
#define TWOWELDLINEGAP					40
#define THREEWELDLINEGAP				60
#define FOURWELDLINEGAP					80
#define FIVEWELDLINEGAP					100
#define SIXWELDLINEGAP					120
#define SEVENWELDLINEGAP				160        //210
#define HEADERHEIGHT					70
#define MAXXCOORDINATE					1114
#define MAXYCOORDINATE					1500
#define PAGESTARTCORDINATE				100
#define DEFAULTMINPAGE					1
#define DEFAULTMAXPAGE					2
#define WELDDATA						1
#define FIRST25WELDDATA					12     //25
#define LAST25WELDDATA					140    //153
#define NEXT25WELDDATA					268
#define GRAPHTEXTSTARTXCORDINATE		100
#define GRAPHTEXTSTARTYCORDINATE		1190
#define EVENTTEXTSPACING				65
#define HORNSCANTEXTSTARTYCORDINATE		1325
#define HORNSCANTEXTSPACING				50
#define METRIC		                  	1
#define USCS		                  	0
#define NORMALFONT	                    2
#define BOLDFONT		                3
#define ZERO		                  	0
#define ONE				                1
#define TWO								2
#define ZEROPOINT						CPoint(0,0)
#define PRINTNOWGRAPHCORD				CPoint(200,550)
#define PRINTSCREENGRAPHCORD			CPoint(325,550)
#define PRINTHSGRAPHCORD				CPoint(225,200)
#define PRINTHSCGRAPHCORD				CPoint(200,600)
#define YEARMONTHFOLDERNAME				7
#define YEARSIZE						4
#define MONTHSIZE						2
#define DATESIZE						2
#define WELDINPROGRESS					1
#define PIXPERINCH						150
#define EUROPEANSMALLFONT				23
#define EUROPEANBIGFONT					23
#define EUROPEANWELDDATAFONT			18
#define EUROPEANWELDDATASMALLFONT		16
#define TRADITIONALSMALLFONT			21
#define TRADITIONALBIGFONT				21
#define TRADITIONALWELDDATAFONT			20
#define SIMPLIFIEDSMALLFONT				23
#define SIMPLIFIEDBIGFONT				23
#define SIMPLIFIEDWELDDATAFONT			19
#define JAPANESESMALLFONT				20
#define JAPANESEBIGFONT					20
#define JAPANESEWELDDATAFONT			16
#define KOREANSMALLFONT					22
#define KOREANBIGFONT					22
#define KOREANWELDDATAFONT				17
#define HISTORYVALIDATIONFAILEDALARM	1
#define SBCDISKFULLALARM				8
#define USBOFFLINEALARM					2
#define USBFULLALARM					4
#define USBNEARLYFULLALARM				16
#define DISKMEMORYNEARLYFULLALARM		32
#define ALARMBUTTONRECT					CRect(2,4,160,38)
#define ALARMBUTTONRECT_RE				CRect(0,0,160,38)

#define CALIBX(point,HPIX) (point * HPIX)/PIXPERINCH
#define CALIBY(point,VPIX) (point * VPIX)/PIXPERINCH
#define Calib(p, HorPix,VerPix) CRect(CALIBX(p.left,HorPix),CALIBY(p.top,VerPix),CALIBX(p.right,HorPix),CALIBY(p.bottom,VerPix))
#define CalibPoint(p, HorPix,VerPix) CPoint(CALIBX(p.x,HorPix),CALIBY(p.y,VerPix))
#define Font(Font,nHorz) ((nHorz<300)? (Font) : (Font+3))

#define TOP_COORDINATE_1_BUTTON			60
#define TOP_COORDINATE_4_BUTTON			312
#define MEDIUM_BUTTON_WIDTH				170
#define LEFT_COORDINATE_1_BUTTON		20
#define LCOORDINATE_COL1_FACTOR			185
#define LCOOR_LARGEBUTTON_FACTOR		45
#define LCOOR_RADIO_FACTOR				60

#define SEQUENCESCREEN					2
#define PRESETSCREEN					1
#define POWERPRESETSCREEN				3
#define USBPRESETSCREEN					4
#define PRESETINFOSCREEN				0
#define VARMAXMINLENGTH					2
#define DATE_LENGTH						6

//Belew defines are changed to keep maximum possible file paths for 2000X executable and Language files in config files.
//We can add more folders inside the current paths with the changed define values
//Right now below are the paths from where executable is ran and Language name is picked.
//These paths goes in system config file and language utility also reads them from config file
//"C:\Program Files\Branson\2000Xc\
//"C:\Program Files\Branson\2000Xc\Languages"
#define MAXEXESIZE						255
#define MAXLANGNAME						255
#define MAXSECURITYSIZE					255
#define MAXPASSSIZE						12
#define MAXRADIOINDEX					20

#define PSPresetSelected				0
#define USBPresetSelected				1
#define VARIABLE_COORDINATE1			80
#define VARIABLE_COORDINATE2			310
#define VARIABLE_COORDINATE3			350
#define VARIABLE_COORDINATE4			380
#define VARIABLE_COORDINATE5			390
#define VARIABLE_WIDTH					225

#define Distance_RequestValue			64
#define Power_RequestValue				2
#define Velocity_RequestValue			32
#define Force_RequestValue				16
#define Amplitude_RequestValue			8
#define Frequency_RequestValue			4
#define MaxPresetNum_InListBox			11
#define MAX_PRESET_BELOW_C				16
#define MAX_PRESET_IN_C					1000
#define MAX_THREEDIGIT_PRESET			999
#define MAX_TWODIGIT_PRESET				99

#define MIN_LENGHT_TWODIGIT_PRESET		2
#define MIN_LENGHT_THREEDIGITPRESET		3
#define MIN_LENGHT_FOURDIGITPRESET		4

#define MAX_PRESET_PER_SCREEN			11
#define MaxSequencePresetNum_InListBox	30
#define HornScan_RequestValue			128

#define SIZEOFPRESETDATA	    1247
#define PRESETSIZE_WITHOUTDUPS	1035
#define PresetNameStrPos		200
#define PresetPos				331

#define MAXSYSFILE_LEN				10
#define MAX_WELD_PDF_PAGES			2000
#define MAX_EVENT_PDF_PAGES			2000

#define WAITFORUDI_STRINGID			4299
#define LOGINT_STRINGID				4008
#define LOGOUT_STRINGID				4076
#define EVENTHISTORY_STRINGID		2689
#define USERID_STRINGID				4304
#define WELDHISTORY_STRINGID		4305
#define BARCODE_BUTTON_POSITION		14
#define BATCH_COUNT_BUTTON_POSITION 3
#define PRESET_BARCODE_START_ID		260

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CPrintText;
#include "VgaMenuItem.h"
#include "VgaMenu.h"
class CXmlElement;
class CWeldingData;
class CVgaDrawGraph;
class CTable;
class CUSBFolder;
class CWeldingHistory;
enum UDISCANSTATUS
	{
		UDISCAN_WAITING = 1,
		UDISCAN_RECEIVED,
		UDISCAN_OFF,
	};

class CChildView : public CWnd
{
public:
	bool AuthorityCheckSartUp;
	bool AuthorityCheck;
	bool AuthorityCheckLogOut;
	bool MemoryfullCont_Stop;
	UINT32 IdleLogoutTime;
	static int StartWeldData;
	int TemporaryAlarmCount;
	bool AlarmUpdateRequired;
	static CStringArray WeldDataPatamStringID;
	static CStringArray EventDataPatamStringID;
	static CStringArray UserIDPatamStringID;
	CVgaMenu *SetupMenuPointer,*SequenceMenuPointer;
	CString USBGraphMenu;
	CString Str_PMCGraphs,StrCurrent,Str_PwrAvg,Str_PMCWeld,Str_PMCCycles,Str_NoValidGraph,Str_Frequency,Str_DigitalTuneSett;
	bool StringDebugFlag,EnableUSBGraph;
	bool BottomHalfScreen;
	bool DiagIOScreen;
	CString Str_Save,Str_Exit,Str_PassAccp,Str_PassRej,Str_Secret,Str_Series,Str_Parallel;
	bool DisplayLockFlag;
	bool MenuUSBDraw;
	bool BrowseUSB;
	int CopyPresetNum;
	bool OverWritePreset;
	bool OverWritePSPreset;
	int OverWritePresetNum;
	static CString PSName;
	static CList<CString, CString>USBPresetNames;
	static CList<CString, CString>USBPresetName_temp;
	static int TotalUSBPreset;
	static int SelectedUSBPreset;
	static int SelectedPowerPreset;
	static bool LastSelectedPresetFrom;
	CString AlarmMenuIdentifier;
	CString AlarmMenuName,CycleCountString;
	static bool ContinuePrinting;
	bool ScanA_Present;
	bool ScanB_Present;
	bool ScanC_Present;
	bool CurrentScan_Present;
	bool ScanA_On;
	bool ScanB_On;
	bool ScanC_On;
	bool CurrentScan_On;
	static bool PMCScreen;
	static bool ColdStartInProcess;
	static CString mainmenu_string,WeldResult_string,WeldSetup_string,Graphs_string;
	CString PrinterPower_str_Online,PrinterPower_str_Offline;
	void SetDimension(CVgaMenuItem *ptr,int count);
	CString MenuNameID;
	int Convert_Char_To_Int(unsigned char *&data, int &length, int Bytes);
	float Convert_Char_To_Float(unsigned char *&data, int &length, int Bytes);
	char Sys_FileSize;
	char CurrentExecutable[MAXEXESIZE];
	char CurrentLanguageName[MAXLANGNAME];
	char SecurityFile[MAXSECURITYSIZE];
	bool PasswordRequired;
	char CurrentPassword[MAXPASSSIZE];
	CString StartUpVerFileName;
	CString SystemVerFileName;
	static CString ScanString;
	static int TempCount;
	CList<CString, CString> menusname;
	static int Currentlanguage;
	bool listbuild;
	CVgaMenu * CurrMenuList;
	void ModifyObjectList(CVgaMenu *);
	bool CheckConditions(CVgaMenuItem *) const;
	bool CChildView::CheckChangeConditions(CVgaMenuItem *item) const ;
	enum BUTTONTYPE{SMALL,NORMAL,LARGE,TEXTTYPE,RADIOTYPE,DEFAULT};
	static int ButtonType;
	static int MenuType;
	static int RowPerPage;
	static int ColumnPerPage;
	static int ControlLevel;
	static int Actuator;
	static int WeldMode;
	static int Securitylevel;
	static int AccessLevelSystem;
	static int SWconfiguration;
	static int HWconfiguration;
	static int ExitButtonFlag;
	static int SaveButtonFlag;
	static int BasicExpert;
	static bool Automation;
	static int UserChangeCond;
	static int LoginButtonFlag;
	static int LogoutButtonFlag;
	static int Max_Allowed_Weld_Log;
	enum STATEMACHINESTATE
	{
		STATE_MACH_OFF = 0,
		STATE_MACH_ON  = 1,
	};
	bool SendCommandForStateMachineEnable(STATEMACHINESTATE);
	bool GetStateMachineStatus(void);
	void GetButtonShape(int &Hgap,int &Vgap,int &Width,int &Height);
	void RecalculateMenuItemsLayout(int height,CVgaMenu * CurrMenuLst);
	static bool PollingTimeOnMsgScrn;
	static bool LargeWaitingTime;
	static bool USBGlobalFlag;
	static bool StorageFormatGlobalFlag;
	CMutex USBMutex;
	CMutex mutex;
	CMutex USBpstMutex;
	int * GraphWeldDataIdArray;
	int * WeldDataIdArray;
	void GetWeldDataIdArray(bool DeletePrevious);
	void GetGraphWeldDataIdArray(bool DeletePrevious);
	CString GetAlarmString(CVgaMenuItem *ptr);
	void AddAlarmButtonInList();
	bool GetAlarmButton();
	static bool CommandForAlarmButton;
	static CString USBSelectedPresetName;
	CList<CString, CString>WeldAlarmStringList;
	CList<CString, CString>WeldHistoryAlarmStringList;
	CList<CString, CString>GraphAlarmStringList;
	CTypedPtrList<CPtrList, CPrintText *> PrintObjectList;
	CTypedPtrList<CPtrList, CPrintText *> PrintSequenceObjectList;
	bool USBAlarm;
	bool USBMemoryFull;
	bool SBCDiskFull;
    bool USBMemoryNearlyFull;
    bool DISKMemoryNearlyFull;
	bool HornScanPlzWait;
	static int ViewGraphGlobalCount;
	CHostCommand * ViewGraphWeldData;
	int UniversalCount;
	static int UniversalCountWeldHiddenFile;
	bool MakeUSBWeldData(unsigned char *&data,int & length,int Difference);
	bool MakeLOGWeldData(unsigned char *&data,int & length,int Difference);
	void SendCommandAlarms(int AlarmType);
	static bool RunResultScreen;
	static bool WasRunResultScreen;
	static int PMCMaxVdata;
	static void ErrorBeep();
	static int CurrentSequencePreset;
	static bool PMCDisable;
	static int LowerPMCLimit;
	static int UpperPMCLimit;
	static int GraphTwoRequestValue;
	static int GraphOneRequestValue;
	void ExitProgram();
	static CString LastUSBPresetFolder;
	static bool ISUSBPresent;
	static bool SaveRecallPresetScrn;
	void ShowMessageScreen(CString Message);
	void ShowMessageScreen2(CString Message);
	void GetPowerSupplyName();
	static CString 	PSPresetText[MAX_PSPRESET];
	CString StrPage,Str_HornId;
	void CreateFolder(bool CheckForPreset);
	//		void CreateFolder();
	CString PowerSupply;
	CString ActSerialNumber;
	CString PresetBarCodeStart;
	CString PowerSupplyIp;
	CString Date;
	bool CheckForPrinting();
	bool DataForUSB(int DataId);
	int UniqueID;
	static int AlarmCount;
	bool WeldOnChangedPreset;
	bool ValidFolderName(CString FileName, int Fun_Id);
	bool PrepareUSBList(CString FilePath, int Fun_Id,int Address);
	bool IsPageSizeMenu;
	int GlobalCycleCount;
	bool ExtPreset;
	bool GetPrintingParameters(bool InilitilizeBaseCount);
	void PrintVQSLimits();
	bool USBPresent();
	void CopyHSCScreenGraphs();
	static CString *Parameter_Heading;
	static CString *Parameter_Event_Heading;
	static CString *Parameter_UserID_Heading;
	static CString *Parameter_UserID_HeadingS;
	static CString *Parameter_Units_USCS;
	static CString *Parameter_Units_Metric;
	static int *Parameter_ID;
	static int *EventParameter_ID;
	static int *UserIDParameter_ID;
	static int TotalTextHeading;
	static CString *Parameter_Alarm_Heading;
	static int *AlarmLogPara_ID;
	static int TotalAlarmHeading;
	static int *EventLogPara_ID;
	static int TotalEventHeading;
	int *PDFParamWidth;
	static int *UserIDPara_ID;
	static int TotalEventTextHeading;
	static int TotalUserIDTextHeading;
	static int TotalUserIDHeading;
	void GetAllWeldDataHeading(CXmlElement * e);
	void GetAlarmLogDataHeading(CXmlElement * e);
	void GetEventLogDataHeading(CXmlElement * e);
	void GetUserIDDataHeading(CXmlElement * e);
	void GetAllUserIDHeading(CXmlElement * e);
	CEvent WaitForPrintData;
	static UINT PrintingThread(LPVOID);
	CEvent WaitForUSBData;
	static UINT WriteDataToUSB(LPVOID);
	CEvent WaitForEtherNetAlarmHandle;
	static UINT EtherNetAndAlarmHandle(LPVOID);
	static UINT SendSerialCommand(LPVOID);
	bool HandleAlarmChange();
	void OnEndPrinting(CDC *, CPrintInfo *);
	void BuildPrintList(int type);
	static struct PrintValues{
		bool PrintSampleDisable;
		int PrintSampleValue;
		bool PrintOnAlarmValue;
		int BaseCount;
	};

	static struct USBValues{
		bool USBSampleDisable;
		int USBSampleValue;
		bool USBOnAlarmValue;
		int BaseCount;
	};
	static	struct PrintingSetup
	{
		bool IsPrinting;
		bool IsPageSizeA4;
		int WeldsPerPage;
	};

	int PresentWeldCount;
	int PresentAlarmCount;
	static int WeldCycleCount;
	void ReleaseDc(CDC *pDC);
	CDC* CChildView::GetDc();
	static int BotomHalfRefreshTime;
	CChildView();
	virtual ~CChildView();
	bool IsLanguageMenu;
	bool AlarmScreenOnCalibration;
	bool IsAlarmScreen;
	static bool metric;
	static bool PasswordFlag;
	static bool IsTwoSecExpired;
	static bool ScreenSetupFlag;
	static bool Start_Screen;
	static bool ActColdStartFlag;
	static bool BottomHalfTimerOn;
	static bool IsNewScreenPointer;
	static bool SysInfoScreen;
	static bool DisableFlag;
	static bool AutoRefreshon;
	static bool BatchEnabled;
	static bool DownspeedEnable;
	static int Language_Index;
	static int CurrentPresetNum;
	static int RAMCalibCordinate_Xa;
	static int RAMCalibCordinate_Ya;
	static int RAMCalibCordinate_Xb;
	static int RAMCalibCordinate_Yb;
	static int TextColor;
	static int 	TitleBarColor;
	static int Button_Color;
	static int Back_Color;
	static int Highlight_Color;
	static DWORD Color_Array[12];
	int mainMenuAddress;
	int GraphsMenu_Address;
	int WeldSetup_Address;
	int WeldResults_Address;

	void WeldHistoryPrint(int ID);
	void WeldDataPrint(int ID);
	void GraphsWeldPrint(int ID);
	void SetUpPrint(int Address);
	void SequencingPrint(int Address);
	void AddSaveExit(CVgaMenu * CurrMenuLst);
	void ProcessNak(unsigned char *&data,int & length,int Address,int FunID);
	void SaveData();

	void BuildCompleteKeypadList(int type,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr);
	static void KillTimers(int TimerID);
	static CChildView * thisPtr;
	static UINT_PTR InitialiseTimer(int TimerID,int Time);

	CTypedPtrList<CPtrList, CVgaMenuItem *> menuEntryList;
	CList<int, int> menus;
	CList<CVgaMenu *,CVgaMenu *> menupointers;
	bool IsFolderPresent(CString Path, CString FileName);
	CTypedPtrList<CPtrList, CScreenKeypad *> keypadList;

	/* Graph Related Lists */
	CList<int, int> PrintInfoList;
	CTypedPtrList<CPtrList, CVgaDrawGraph *> GraphPrintList;
	CTypedPtrList<CPtrList, CVgaDrawGraph *> HSGraphPrintList;
	CMapStringToString StringMap;
	CMapStringToString AlarmMap;
	CStringArray AlarmEng,PString,Manual,GraphPrText,LString,PrintHSInfoText,AllMonthStrings;
	CList<int, int> PrintGraphIDList;
	CList<int, int> PrintWeldDataIDList;
	CTypedPtrList<CPtrList, CPrintText *> PrintGraphTextObjectList;
	CTypedPtrList<CPtrList, CTable *> TablePrintList;

	CTypedPtrList<CPtrList,CWeldingData *> PrintGraphWeldDataList2;
	CTypedPtrList<CPtrList, CWeldingData *> GraphWeldDataPrintList;
	CTypedPtrList<CPtrList, CWeldingData *> WeldDataPrintList;
	CTypedPtrList<CPtrList, CWeldingData *>PrintWeldHistoryList2;
	CTypedPtrList<CPtrList, UserID *> IDDataNewList;
	CTypedPtrList<CPtrList, CEventHistoryData *> EventHistoryList;

	int Total_Objects;
	static int PresetNum;
	static int BatchCount;
	static UDISCANSTATUS PrevUDIStatus;
	static int Presettrack;
	static int MaxPreset;
	static bool PowerUpSBC;
	void GetRAMData();
	bool ReadStartUpVersionString();
	bool ReadSystemVersionString();
	void Add_Back_Next_Button();
	void Back_Next_Button_Layout();
	void GetAveragePowerGraph(CDC *pDC, CChildView * view);
	bool EventFlag;
	CString CurrentFilepath;
	CString GetCurrentFilePath(char *);
	//CString GetCurrentFilePath();

	static bool LoginScreenFlag;
	void SendPollingCommand();
	static void DrawPDFText(HPDF_Page *page,int X_Cord,int Y_Cord,char *STR);
    bool CreateNewPDFDoc(HPDF_Page *page,HPDF_Doc *pdf,HPDF_Font *def_font);
	void CStringToUTF(CString Text,char *UNICODESETSTR);
    void AssignFontForPrinting();
    char *PDFFontName;
	 enum LanguageEnum
	 {
	 	ENGLISH=0,
		CHINESESIML ,
		CHINESETRAD ,
		FRENCH ,
		GERMAN ,
		ITALIAN ,
		JAPANESE ,
		KOREAN ,
		SPANISH
	 };
    static void CheckAvailablDiskSpace(CString str = "C:\\");
	static bool USBOverWritePreset; //this flag shall be true if copyall butoon hit by the user.
	int PresetNameCount;			//this is the global count that keeps total no of preset data we received from WC.
	unsigned char *PresetListBuff;  //buffer to keep all the valid preset data.
	int CopyAllPresetAddress; //keep the menu address of CopyAll button ,in order to catch the menunak message.
	bool FoundPresetToCopy;
	int CopyAllPresetAddress_Ok;///keep adress for OverWriteOkButton().
	bool CancelButtonFlag;      //This flag becomes true if cncel button clicked by the user.
	bool USBCheckCopyAllFlag;   //this flag shall be true if storage space for usb memory is less than 20%.
	CString PresetName ;        //Keep the preset name.
	bool PresetOverwriteCheckedFlag;
	void PrintStreamingSetup();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMainMenu();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void OnPrint(CDC *pDC = NULL, CPrintInfo * = NULL,HPDF_Doc  * pdf=NULL,HPDF_Page * page=NULL);
	void OnPrepareDC(CDC *pDC, CPrintInfo *pInfo);
	void OnBeginPrinting(CDC *, CPrintInfo *);
	BOOL DoPreparePrinting(CPrintInfo *pInfo);
	BOOL OnPreparePrinting(CPrintInfo *printInfo);
	/* USB Related Lists */
	CTypedPtrList<CPtrList, CHistoryData *> USBHistoryList;
	CTypedPtrList<CPtrList, CVgaDrawGraph *> USBGraphsList;
	CTypedPtrList<CPtrList, CHistoryData *> LOGHistoryList;
	CList<int,int>USBGraphCountList;

	bool PrintOnAlarmAndSample();
	int BaseWeldCount;
	int TempBaseWeldCount;
	bool print();

	int PresentPresetNum;
	int TempPresetNum;

	//CString GetCurrentFilePath(char *);

	CString GetCurrentFilePath(CHistoryData *object);
	CString CopyScreenGraphs();
	bool SendUSBWeldData();
	bool SendUSBEventLogs();

	bool SendUSBGraphData();
	bool SendLOGWeldData();
	void ClearListOnUSBFullAlarm();

	void DrawPageNumber(CDC*pDC);
	CString YearMonthName;
	CString Time;
	enum
	{
		ACK = 0x06,
		NAK = 0x15
	};
	enum ResponseType
	{
		INVALID=-1,
		NONE ,
		ESTOP_OFF ,
		ESTOP_PRESSED_CONT ,
		MSG_SCREEN ,
		MSG_NAK_SCREEN ,
		CALIB_START_FLAG_ON ,
		CALIB_START_FLAG_OFF ,
		ESTOP_PRESSED_FIRST ,
		ESTOP_RESET ,
		TESTKEYPRESSED ,
		CUR_PRESET_PARAM_CHANGED,
		CLAMP_ALARM,
		EVENT_REASON_FLAG,
		DOWNSPEED_NEW_FLAG,
		ESTORESET_LOGIN,
		DOWNSPEEDFLAG,
		DOWNSPEEDFLAG_MSG,
		DOWNSPEED_NEW_HD_FLAG,
		GET_SYSTEM_VAR = 0x40,
		ESTOP_LOGIN_NEXT = 0x02,
	};

	enum ProcessNakErrorCode
	{
		ACCESS_NOT_ALLOWED = 1,
		REFRESH_MENU = 3,
		SHOW_MSG_SCREEN = 4,
		SHOW_PASSWORD_SCREEN = 5,
		SHOW_PASSWORD_ENTRY1 = 6,
		SHOW_PASSWORD_ENTRY2 = 7,
		SHOW_WELDINGON_MESSAGE = 11,
		COLSETUP_MSG_SCREEN = 12
	};
	static bool powerup;
	bool AlarmPresent;
	int Total_Text_Objects;
	void SetRequestValue(int *TotalGraphRequestValue, int *TotalGraph, int ID,int CurrentGraphRequestValue, PrintValues *CurrentGraph);
	void DrawKeypad(CDC*pDrawDC);
	void AnalyzePollingResponse(unsigned char *&data,int &length);

	void DrawFirstScreen();
	CPoint CalibratePoint(CPoint p);
};

void EnableStateMachine(int ID);
int GetNumberOfUsers(void);
extern volatile bool creating_pdf;
extern int Max_Preset_Possible;
bool SavePDFToUSB(HPDF_Doc &pdf,char *filename);
void PdfWithImage(HPDF_Doc  * pdf=NULL,HPDF_Page * page=NULL,HPDF_Font *def_font = NULL);
extern CString  WaitForUDIScan;
extern int HistorySetUp;
extern bool EstopPressedFlag;
void UpDateWeldHiddenFile(int);
void UpdateEventHiddenFile(int);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__04D2A820_3DAF_4495_A8E2_35B717D209D3__INCLUDED_)
