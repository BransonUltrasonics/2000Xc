/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/EventLog.h_v   1.20   08 Apr 2015 13:07:08   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/EventLog.h_v  $
 * 
 *    Rev 1.20   08 Apr 2015 13:07:08   AnPawar
 * changes for pressure stepping events.
 * 
 *    Rev 1.19   01 Apr 2015 12:55:06   amaurya
 * added new event code EVENT_AUTHORITY_CHECK_CHANGED in EventTypes enum. 
 * 
 *    Rev 1.18   11 Mar 2015 09:27:16   amaurya
 * Setup limit parameters added to enum PARAM.
 * 
 *    Rev 1.17   30 Jan 2015 08:14:00   amaurya
 * DisplayPosition member added to class EventDescription to keep the position of showing parameter name.
 * 
 *    Rev 1.16   02 Jan 2015 04:58:10   rjamloki
 * macro  MAX_EVENT_DISP_SIZE defined to display only 100 events on sbc
 * 
 *    Rev 1.15   11 Dec 2014 06:49:54   RJamloki
 * Unused Events removed from enum EventTypes.
 * 
 *    Rev 1.14   28 Nov 2014 08:30:56   rjamloki
 * variables added in CEventLog class to keep Event count in hidden files.
 * 
 *    Rev 1.13   10 Nov 2014 02:49:44   rjamloki
 * EventDescEng and ParamDescEng new members added for JSON.DOWNSPEEDPLR and  DOWNSPEEDMLR added to enum param.
 * 
 *    Rev 1.12   20 Oct 2014 05:45:00   RJamloki
 * New macros defined for max allowed weld logs in control level D and C
 * 
 *    Rev 1.11   06 Oct 2014 03:24:48   rjamloki
 *  added TotalEventTypes variable in EventDescription class and macro values changed.
 * 
 *    Rev 1.10   01 Oct 2014 10:49:24   AnPawar
 * Structure for event on web services  
 * 
 *    Rev 1.9   11 Sep 2014 09:46:00   rjamloki
 *  Event_Log structure modified
 * 
 *    Rev 1.8   05 Sep 2014 06:59:40   amaurya
 * Corrected the recursive inclusion.
 * 
 *    Rev 1.7   28 Jul 2014 13:55:54   rjamloki
 * CEventLog::CreateEventPDF() modefied to support usbexception
 * 
 *    Rev 1.6   09 Jul 2014 06:56:00   akaushal
 * Event_Log struct added.And added some macros.
 * 
 *    Rev 1.5   27 May 2014 06:30:40   amaurya
 * Added flag for Event History Log full
 * 
 *    Rev 1.4   07 May 2014 13:07:04   akaushal
 * Code cleanup 
 * 
 *    Rev 1.3   21 Apr 2014 13:37:24   akaushal
 * Variables and Funtion declaration added for drawing log and creating PDF.
 * 
 *    Rev 1.2   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     05 Mar 2014 14:13:18 rjamloki  
 * Screens and PDF working
 *
 *    Rev 1.0     26 Feb 2014 02:18:18 jerryw.wang     
 * Initial Revision.
*/

#if !defined(AFX_EVENTLOG_H__566C2B5F_79CD_4FCF_AC0A_1CD0345DD1C5__INCLUDED_)
#define AFX_EVENTLOG_H__566C2B5F_79CD_4FCF_AC0A_1CD0345DD1C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VgaMenuItem.h"
#include "UserID.h"
#include "hpdf.h"

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

#define EventLogMaxCyclePerScreen 8
#define MAXSERIALNUMBER_LEN 13
#define MAX_ALLOWED_EVENT_LOG  100000
#define MAX_EVENT_DISP_SIZE 100
#define MAX_ALLOWED_WELD_LEVEL_C  100000
#define MAX_ALLOWED_WELD_LEVEL_D  50
#define MAX_EVENT_IN_ONE_PACKET 10
#define MAX_EVENT_ENTRIES 100
//Parameter IDs start point taken from WC param.h. Parameter IDs are handy if the
//the parameter name or some other string needs to be displayed on event decripton.
//WC loggs the parameter ID as par of event log.
#define CURRENT_SETUP_OFFSET 1024
#define HORN_DOWN_OFFSET     2048
#define DUPS_PARAM_OFFSET    3072
#define VGA_PARAM_OFFSET     4096

#define MAX_EVENTREASON_LEN 52//Including null
#define MAX_EVENTDATA_LEN 12 //Including null
#define MAX_DESCRIPTION_PERLINE 45
#define MAX_DESCRIPTION_PERLINE_PDF 100

#pragma pack(push, 1)
struct Event_Log
{
	UINT32   EventNum;      //Event Number
	UINT16   PresetNo;      // Present Number
	UINT16   Rev;              //Revision Number
	UINT8    UserId[6];    //USER Id
	UINT8    EventId[6];      //Event ID
	UINT8    PSSerialNumber[14]; //Power Supply Serial Number
	UINT8    DataNew[MAX_EVENTDATA_LEN];      //Data One 34
	UINT8    DataOld[MAX_EVENTDATA_LEN];      //Data Two 38
	RTCTime  TS;  // Event Record Creation Time
	UINT8 	EventReason[MAX_EVENTREASON_LEN];
	UINT16 ParameterId;
	UINT16   EventHistoryCRC; //CRC of the Data above to check the data above is valid or not
};
#pragma pack(pop)

#pragma pack(push, 1)
struct JsonEventLog
{
	UINT32   EventNum;      //Event Number
	UINT16   PresetNo;      // Present Number
	UINT16   Rev;              //Revision Number
	UINT8    UserId[6];    //USER Id
	UINT8    EventId[6];      //Event ID
	UINT8    PSSerialNumber[14]; //Power Supply Serial Number
	RTCTime  TS;  // Event Record Creation Time
	UINT8 	EventReason[MAX_EVENTREASON_LEN];
   UINT8    EventDescription[200]; //49
};
#pragma pack(pop)

class CXmlElement;
class CEventHistoryData;
class EventDescription
{
public:
	CString EventID;
	CString EventDesc;//Language specific event description
	CString EventDescEng;//Event Description in English for JSON
	CString DisplayPosition;
	CString Str1,Str2;
	EventDescription(CXmlElement * e);
	CString GetEventID();
	CString GetEventDescription(bool InEnglish = false);
};

class ParamDescription
{
public:
	CString ParamID;
	CString ParamDesc;
	CString ParamDescEng;//Param Description in English for JSON
	CString Str[6];
	ParamDescription(CXmlElement * e);
	CString GetParamID();
	CString GetParamDescription(bool InEnglish = false);	
};

class CEventLog : public CVgaMenuItem
{
public:
	CEventLog(CXmlElement * e);
	virtual ~CEventLog();
	
	
	void DrawParameterHeadings(CDC * pDC);
	//	bool USBHistory;
	int *Parameter_ID;
	int TotalColoumn;
	static int TopMostData;
	static int EventHistoryglobalCount;
	static bool EventHistoryFullFlag;
	static int TotalCycles;
	static int SuccessfullyWrittenEventRecord;
	static int CurrentDisplayEventCount;
	static int EventHistoryUniversalCount;
	static int EventHistoryRamCount;
	void DrawEventData(CDC *pDC);
	int TotalCycle;
	CEventLog(unsigned char * &data, int & length);
	CEventLog();
	CTypedPtrList<CPtrList, CEventHistoryData *> EventLogList;
	CMutex EventListMutex;
	//	CMutex EventLogFileMutex;
	static int SelectedEventData;
	static int LeftMostParameter;
	static CEventLog * thisHisPtr;
	void DrawEventLOGData(HPDF_Page * page = NULL,HPDF_Doc  * pdf = NULL);
	void DrawEventParameterHeading(HPDF_Page * page = NULL);
	bool PrepareEventListForPDF(CString ,int,int);
	bool CreateEventPDF();  
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

enum EventTypes {
	  EVENT_PARAMETER_CHANGED_ONVALIDATEDPS = 100,
      EVENT_PRESETVALIDATION_BITSET = 101,
      EVENT_NEWUSER_CREATED = 102,
      EVENT_USER_MODIFIED = 103,
      EVENT_RTC_CHANGED = 104,
      EVENT_FACTORY_AUTOMATION_MODE = 105,
      EVENT_HARDWARE_ASSEMBLY_NUMBER_CHANGED = 106,
      EVENT_HARDWARE_VERIFY_CHANGED = 107,
      EVENT_SOFTWAREVERSION_CHANGED = 108,
	  EVENT_AUTHORITY_CHECK_CHANGED = 109,
      EVENT_ACTCOLD_START = 110,
      EVENT_LOWBATTERY = 111,
      EVENT_CALIBRATION = 112,
      EVENT_PRESET_VALIDATION_BIT_CLEARED = 113,
      EVENT_POWERON_CRC_CHANGED = 117,
      EVENT_CLOCK_LOST = 118,
      EVENT_PARAMETER_CHANGED = 202,
      EVENT_HORN_SCAN_COMPLETED = 303,
      EVENT_PROGRAMFIRMWARE = 407,
      EVENT_USERLOGIN = 501,
      EVENT_USERLOGOUT = 502,
      EVENT_FIRMWARE_UPLOAD = 416,
	  EVENT_EVENT_ERROR = 999,
};

enum DisplayPosition{
	SEPARATE,
	BEFORE_EVENT_DESCRIPTION,
	AFTER_EVENT_DESCRIPTION,
	DO_NOT_DISPLAY
};


 typedef enum PARAM {              /* All parameters which can be changed   */
   ALLEMPTY = 0,                  /* Must be first entry in list           */
   ABAMP,               
   ABSOLUTE1,                     
   ABDELAY,                     
   ABFLAG,                        
   ABTIME,                        
   ABSCUTOFFDIST,                      
   ABSCUTOFFFLAG,                 
   ABSDIST,               
   ABSMLR,                 
   ABSMLS,         
   ABSPLR,
   ABSPLS,
   ACTCLEARDIST,       
   ACTCLEARFLAG,
   AMP1,
   AMPTRIGABSVALUE,
   AMPTRIGCOLVALUE,                         
   AMPTRIGEXTFLAG,                         
   AMPTRIGTIMEVALUE,          
   AMPTRIGENERVALUE,                                       
   AMPTRIGPOWERVALUE,                              
   AMP2FLAG,                                   
   AMP2,            
   AMPSCRUBTIME,             
   AUTOSCALEFLAG,             
   AUTOTRIGFLAG,               
   BATCHFUNCTION,                 
   BATCHCOUNTWITHALARM,             
   BATCHCOUNTRESET,            
   BATCHCOUNT,             
   CURRBATCHCOUNT,                  
   PS_ACTASSEMBLYNUM,                       
   PS_PSASSEMBLYNUM,                     
   PS_STACKASSEMBLYNUM,              
   FLOWCONTROL,                        
   COLCUTOFFFLAG,                        
   COLLCUTOFFDIST,                        
   COLDIST,                        
   COLMLR,           
   COLMLS,                    
   COLPLR,               
   COLPLS,                           
   CONTROLLIMITSFLAG,                      
   CYCLEABORTFLAG,                                          
   DATETIME,                                        
   DIGITALFILTERFLAG,                                    
   EBTIME,           
   ENERGYBRAKING,                  
   ENERGYCOMPFLAG,                  
   ENERGYMAXVQS,                  
   ENERGYMINVQS,                   
   ENERGYML,                 
   ENERGYMLR,               
   ENERGYMLS,               
   ENERGYPL,          
   ENERGYPLR,             
   ENERGYPLS,                    
   EXTTRGDELAY,                    
   FREQMLR,                    
   FREQMLS,                     
   FREQPLR,                        
   FREQPLS,                    
   PS_FREQOFFSET,               
   FREQOFFSETFLAG,              
   SBLMINFREQLIM,              
   SBLMAXFREQLIM,                    
   PS_SBLMINFREQ,               
   PS_SBLMAXFREQ,                  
   SBLFREQFLAG,             
   GENERALALARMFLAG,           
   GROUNDDETECTFLAG,              
   HOLDFORCE,           
   WELDPRESSURE,                
   HOLDPRESSURE,         
   HOLDTIMEFLAG,            
   HORNID,                
   MAXTIMEOUT,               
   MISSINGPARTFLAG,            
   MISSINGMINFLAG,              
   MISSINGMAXFLAG,          
   MISSINGPARTMIN,          
   MISSINGPARTMAX,          
   PEAKPWR,                
   PEAKPOWERCUTOFF,               
   PEAKPWRCUTOFFFLAG,                    
   PEAKPWRMAXVQS,                   
   HOLDTIME,                     
   PEAKPWRMINVQS,                          
   PRESETID,                 
   POWERMLR,              
   POWERMLS,              
   POWERPLR,                 
   POWERPLS,                 
   MPRESSURELIMIT,                   
   PS_PPRESSURELIMIT,                  
   PPRESSURELIMITFLAG,                   
   PRESSURELIMIT,                   
   PRESETUPDATECMPLT,               
   PRETRIGFLAG,                       
   PRETRIGAMP,               
   PRETRIGDELAY,                
   PRETRIGDELAYFLAG,              
   PRETRIGDIST,               
   PRETRIGDISTANCEFLAG,               
   REJECTLIMITS,                        
   REJECTLIMITSFLAG,                 
   PEAKPOWER,                  
   REJRESET_REQFLAG,               
   RTDIST,                  
   RTFLAG,             
   SCRUBTIME,             
   SCRUBTIMEFLAG,             
   SEEKFUNFLAG,                    
   SUSPECTLIMITS,                    
   SUSPECTLIMITSFLAGS,                      
   SUSRESET_REQ,                      
   TESTAMP,                   
   TIMEMLR,                   
   TIMEMLS,                   
   TIMEPLR,                
   TIMEPLS,                   
   TRIGGERDELAY,            
   TRSDISTMLR,            
   TRSDISTMLS,         
   TRSDISTPLR,           
   TRSDISTPLS,                  
   WELDTRIGGER,             
   TRIGGERDISTANCE,                
   TRIGGERFORCE,           
   TRIGGERDELAYFLAG,              
   TOTALABS_MAXVQS,                  
   TOTALABS_MINVQS,                
   TOTALCOL_MAXVQS,                    
   TOTALCOL_MINVQS,                     
   TOTALCYC_TIMEMAXVQS,                
   TOTALCYC_TIMEMINVQS,                 
   VALIDATEPS,
   LOCKPS,
   VELOCITYMLR,                   
   VELOCITYPLR,                    
   VERIFIED,            
   WELDCOL_MAXVQS,             
   WELDCOL_MINVQS,             
   WELDCOUNT,               
   WELDENERGY,                
   WELDMODE,                                   
   WRITEIN1,                
   WRITEIN2,             
   WELDFORCEMLR,                
   WELDFORCEMLS,                    
   WELDFORCEPLR,                 
   WELDFORCEPLS,             
   WELDFORCEMAXVQS,                  
   WELDFORCEMINVQS,                    
   WELDSTATUSFLAG,                  
   XSCALETIME,                   
   WELDTIMEMINVQS,                    
   WELDTIMEMAXVQS,            
   PRESETCONFIGNUM,          
   HWCONFIG,            
   PMCHIGHLIMIT,                
   PMCLOWLIMIT,                     
   PMCTIMEOUT,                   
   PMCCYCLECOUNT,                    
   PMCENABLED,                   
   PMCPLUS_BANDFLAG,                  
   PMCMINUS_BANDFLAG,            
   VQSLIMIT,            
   PS_FREQUENCY,             
   POWER,                     
   VARIANT1,                
   DIPFLAG,                  
   SWDIPSETTING,             
   SEEKAMPLITUDE,            
   SEEKRAMPTIME,
   SEEKTIME,
   WELDTIME,
   SEEKFREQLIMITHIGH,                  
   SEEKFREQLIMITLOW,                 
   SEEKPHASELOOP,             
   SEEKPHASELOOPCF,                  
   SEEKAMPLOOPC1,                  
   SEEKAMPLOOPC2,                  
   WELDAMPLITUDE,
   WELDRAMPTIME,
   WELDPHASELOOP,               
   WELDPHASELOOPCF, 
   WELDAMPLOOPC1,
   WELDAMPLOOPC2,
   WELDFREQLIMITHIGH,
   WELDFREQLIMITLOW,
   WELDPHASELIMIT,
   WELDPHASELIMIT_TIME,
   PMCDATA,
   REV,
   XXCANTCHANGEXX,                /* For run screen if things cant change  */
   SAVEPRESETZERO, 
   MAXFORCEMLR,                             
   MAXFORCEMLS,                                      
   MAXFORCEPLR,                                       
   MAXFORCEPLS, 
   AMPLITUDESTEPFLAG,
   AMPTRIGDISTVALUE,
   AMPTRIGFORCEVALUE,
   FORCESTEPFLAG,
   AMPSTEPFLAG,
   DUPSMEMFLAG,
   DUPS_SEEK_FLAG,
   DOWNSPEEDPLR,
   DOWNSPEEDMLR,
   HOLD_PRESSURE_FLAG,
   WELDPRESSURE_PLT,
   WELDPRESSURE_MLT,
   DOWNSPEED_PLT,
   DOWNSPEED_MLT,
   HOLDPRESSURE_PLT,
   HOLDPRESSURE_MLT,
   HOLDTIME_PLT,
   HOLDTIME_MLT,
   AMPA_PLT,
   AMPA_MLT,
   TRIGFORCE_PLT,
   TRIGFORCE_MLT,
   WELDTIME_PLT,
   WELDTIME_MLT,
   WELDENERGY_PLT,
   WELDENERGY_MLT,
   PEAKPOWER_PLT,
   PEAKPOWER_MLT,
   COLLAPSEDIST_PLT,
   COLLAPSEDIST_MLT,
   ABSDIST_PLT,
   ABSDIST_MLT,
   SCRUBTIME_PLT,
   SCRUBTIME_MLT,
   SCRUBAMP_PLT,
   SCRUBAMP_MLT,
   TRIGDIST_PLT,
   TRIGDIST_MLT,
   PRESSURE_TRIGABSVALUE,
   PRESSURE_TRIGCOLVALUE,
   PRESSURE_TRIGEXTFLAG,
   PRESSURE_TRIGTIMEVALUE,
   PRESSURE_TRIGENERVALUE,
   PRESSURE_TRIGPOWERVALUE,
   PRESSURE2_FLAG,
   PRESSURE_2,
   PRESSURE_1, 
   AMP_1,
   PRSTPARMDEFID,   //Default argument for UpdateCurrentPresetAndSetup function.
/* PARAM_ID's from 1024 thru 2047 define parameter types used in CurrentSetup*/

   ACTIVEPRESET = CURRENT_SETUP_OFFSET,
   ACTLIFETIMECOUNTER,                                      
   ACTSERIALNUMBER,                    
   SETUP_ACTUATOR,                     
   ADVANCEDCOUNTERS,                                  
   AMPCONTROL,                                                
   BEEPERALARM,                        
   BEEPERERROR,                        
   BEEPERRELEASE,                      
   BEEPERTRIGGER,
   BAUDRATE,
   FRAMINITIALIZED,
   CUSTOMACTLOGIC,
   CONTROLLEVEL,                      
   CYCLESTART,                   
   CYLINDIAMETER,                      
   PDIGITALTUNE,                        
   DIGTUNEFLAG,                    
   EXTRACOOLING,                               
   EXTPRESETS,             
   FREQCONTROL,                  
   GENERALALARMCOUNTER,                    
   GAINFACTOR,                   
   GNDDETLOGIC,                                            
   HMENUINDEX, 
   HORNDOWNSPD,
   HORNWEIGHTOFFSET,
   USENCODER,                       
   IDLESPEED,                                                  
   LANGUAGE,
   MINTRIGFORCE,
   OVERLOADCOUNTER,                                             
   PASSWORDFLAG, 
   PASSWORDID,
   PSFREQ,                      
   PSWATT,                   
   PSLIFETIMECOUNTER,                 
   PSSERIALNUMBER,                  
   PSTYPE,                      
   PWROUTTABLE,                     
   SPARE2,                   
   SECURITYTABLE,                      
   SPARE3,
   SERIALPORT,                         
   SPRINGRATETABLE,                         
   STARTSCREEN,                      
   STROKELEN,                       
   TESTMULTIPLIER,                      
   TIMEMULTIPLIER,                     
   UNITS,                     
   ULSLOGICCUSTOM,                        
   J3_32_IN,                          
   J3_33_IN,                        
   J3_19_IN,
   J3_17_IN,                       
   USERINLOGIC,                     
   J3_36_OUT,                        
   J3_8_OUT,                  
   VELOCITYTABLE,                            
   WELDHISTORYPTR,                    
   HANDHELD,                         
   WELDPARAMOPTION0,
   WELDPARAMOPTION1, 
   WELDPARAMOPTION2, 
   WELDPARAMOPTION3,
   WELDPARAMOPTION4, 
   DUPS_WORKINGPRESET,                       
   J3_31_IN,                    
   J3_1_IN,                        
   J3_22_OUT,                         
   J3_32PTR,
   J3_33PTR,
   J3_19PTR,
   J3_17PTR,
   J3_31PTR,
   J3_1PTR,
   DUMMY1,
   WELDERADDRFLAG,
   WELDERADDRVALUE,
   SCLK7890ACT,
   CLOCKPHASE,
   SYSTEMCONTFLAG,
   PARTCLAMPDELAY,
   AUTOREFRESH,
   METRIC3FLAG,
   DISTANCEULS,
   SBLENABLE,
   USBGLOBALFLAG,
   USBWDSAMPLEFLAG,
   USBPGSAMPLEFLAG,
   USBAGSAMPLEFLAG,
   USBFREQSAMPLEFLAG,
   USBCDGSAMPLEFLAG,
   USBVGSAMPLEFLAG,
   USBFGSAMPLEFLAG,
   USBWDALARMFLAG,
   USBPGALARMFLAG,
   USBAGALARMFLAG,
   USBFREQGALARMFLAG,
   USBCDGALARMFLAG,
   USBVGALARMFLAG,
   USBFGALARMFLAG,
   USBWDSAMPLEVALUE,
   USBPGSAMPLEVALUE,
   USBAGSAMPLEVALUE,
   USBFREQGSAMPLEVALUE,
   USBCDGSAMPLEVALUE,
   USBVGSAMPLEVALUE,
   USBFGSAMPLEVALUE,
   SEQUENCEENABLE,
   SEQUENCECOUNT,
   SEQUENCELIST,
   SEQUENCENOS,
   VGAHWPRESET,
   PLCCONTROLFLAG,
   PLCCONTROLMENUFLAG,
   BASICEXPERT,
   HORNCLAMP,
   UDISCAN,
   AUTOMATION,
   MEMORYFULL,
   USERIDTABLE,
   AUTHORITYCHECK,
   BARCODESTART,
   STACKASSEMBLYNUM,
   ACTASSEMBLYNUM,
   PSASSEMBLYNUM,
   HWVERIFY,
   WELDSTORAGEFORMAT,
   BEEPERESTOP,
   VQSENABLE,
   IDLELOGOUTTIME,
   WELDHISTSETUP,
   SAVECURRENTSETUP,
   SENDWELDDATA,
   DIGITALFREQ,
/* PARAM_ID's from 2048 thru 3071 define parameters types used in Horn Down*/

   SETUP_HORNDOWNFORCE=HORN_DOWN_OFFSET,/*                                 */
   HD_TRIGGER_STATE,                   /*                                  */
   HD_RAPID_TRAVERSE,                  /*                                  */
   HD_SPEED,                           /*                                  */
   WORKING_HORNDOWNFORCE,              /*                                  */
   RT_TRANSITION,               
   PRESET_TRIGGER_FORCE,
   ALARMMASKID,                        /* Added 04-26-04                   */

/* PARAM_IDs from 3072 thru 4091 define DUPS and Horn Scan parameters      */
   DUPS_PARAMIDS    = DUPS_PARAM_OFFSET, /* Added 06-19-00                 */
   DUPS_PARAMSETNAME,
   DUPS_DIPFLAG,
   DUPS_SWDIPSETTING,
   DUPS_SEEKAMPLITUDE,
   DUPS_SEEKRAMPTIME,
   DUPS_SEEKTIME,
   DUPS_SEEKFLIMH,
   DUPS_SEEKFLIML,
   DUPS_SEEKPHLOOPI,
   DUPS_SEEKPHLOOPCF,
   DUPS_SEEKAMPLOOPC1,
   DUPS_SEEKAMPLOOPC2,
   DUPS_WELDAMPLITUDE,
   DUPS_WELDRAMPTIME,
   DUPS_WELDPHLOOPI,
   DUPS_WELDPHLOOPCF,
   DUPS_WELDAMPLOOPC1,
   DUPS_WELDAMPLOOPC2,
   DUPS_WELDFLIMH,
   DUPS_WELDFLIML,
   DUPS_WELDPHLIM,
   DUPS_WELDPHLIMTIME,

   /* Flags in SWDipSetting variable */
   DUPS_SWBIT0FLAG,
   DUPS_SWBIT1FLAG,
   DUPS_SWAMPSOURCEFLAG,
   DUPS_SWMEMFLAG,
   DUPS_SWMEMSTOREFLAG,
   DUPS_SWBIT5FLAG,
   DUPS_SWSEEKFLAG,
   DUPS_SWSEEKPWRFLAG,

  /*These parameters define Horn Scan parameters                           */
   HORN_SCANSTARTFREQ,
   HORN_SCANSTOPFREQ,
   HORN_SCANFREQSTEP,
   HORN_SCANTIMEDELAY,
   HORN_SCANMAXIMUMAMPLITUDE,
   HORN_SCANMAXIMUMCURRENT,

/* PARAM_IDs from 4096 thru 5120 define VGA parameters      */
   VGA_ACTSTARTCANCEL = VGA_PARAM_OFFSET,
   VGA_ACTSTARTOK,
   VGA_ALARMBUTTON,
   VGA_AMPLITUDEGRAPH, 
   VGA_AMPLITUDEPRINTNOW,
   VGA_AUTOREFRESH,
   VGA_BHHORNSCAN,
   VGA_BHHORNDOWN,
   VGA_BHTEST,
   VGA_BHDIAGNOSTICS,
   VGA_CALSNSRCANCEL,
   VGA_CALSNSROK,
   VGA_COLDISTGRAPH,
   VGA_COLDSTARTCANCEL,
   VGA_COLDSTARTOK,
   VGA_COLUMNSETUP,
   VGA_COMPAREHSCDATA,
   VGA_COMPAREHSCGRAPH,
   VGA_COMPAREHSCTABLE,
   VGA_COPYSCANDATA,
   VGA_DISTANCEPRINTNOW,
   VGA_FACTORYDEFAULTCANCEL,
   VGA_FACTORYDEFAULTOK,
   VGA_FORCEGRAPH,
   VGA_FORCEPRINTNOW,
   VGA_FREQPRINTNOW,
   VGA_FREQUENCYGRAPH,
   VGA_HISTORYPRINTNOW,
   VGA_HORNSCAN,
   VGA_HORNSCANABORT,
   VGA_HORNSCANGRAPH,
   VGA_HORNSCANPRINT,
   VGA_IPADDRESS,
   VGA_NOGRAPH,
   VGA_NOHSGRAPH,
   VGA_OVERWRITEPRESETCANCEL,
   VGA_OVERWRITEPRESETOK,
   VGA_POWERGRAPH,
   VGA_POWERPRINTNOW,
   VGA_PRESETCLEAR,
   VGA_PRESETCLEARCANCEL,
   VGA_PRESETCLEAROK,
   VGA_PRESETDOWN,
   VGA_PRESETINFO,
   VGA_PRESETNAME,
   VGA_PRESETRECALL,
   VGA_PRESETSAVE,
   VGA_PRESETSAVEASSIGN,
   VGA_PRESETSAVEAUTO,
   VGA_PRESETSAVECANCEL,
   VGA_PRESETSAVENEW,
   VGA_PRESETSAVEOK,
   VGA_PRESETSAVEOLD,
   VGA_PRESETUP,
   VGA_PRESETVERIFY,
   VGA_PRINTABORT,
   VGA_PRINTDUPSSETUP,
   VGA_PRINTGRAPH,
   VGA_PRINTHSCDATA,
   VGA_PMCADDAVGGRAPH,
   VGA_PMCCLEARAVGGRAPH,
   VGA_PMC,
   VGA_PMCENTERLIMITS,
   VGA_PMCGRAPH,
   VGA_PMCLOWERBAND,
   VGA_PMCTIMEOUT,
   VGA_PMCUPPERBAND,
   VGA_RADIOCOLUMNCANCEL,
   VGA_RADIOCOLUMNOK,
   VGA_REFRESHGRAPH,
   VGA_RESETSCANVALUES,
   VGA_RESETSENSORCANCEL,
   VGA_RESETSENSOROK,
   VGA_SAVESCANA,
   VGA_SAVESCANB,
   VGA_SAVESCANC,
   VGA_SEQPRINTNOW,
   VGA_SEQUENCECONTINUE,
   VGA_SEQUENCEDEFINE,
   VGA_SEQUENCEDELETE,
   VGA_SEQUENCEDOWNBUTTON,
   VGA_SEQUENCEENABLE,
   VGA_SEQUENCEERASE,
   VGA_SEQUENCEERASECANCEL,
   VGA_SEQUENCEERASEOK,
   VGA_SEQUENCEINSERT,
   VGA_SEQUENCELIST,
   VGA_SEQUENCEREPLACE,
   VGA_SEQUENCEUPBUTTON,
   VGA_SETUPPRINTNOW,
   VGA_SUMMARYPRINTNOW,
   VGA_SCREENSETUP,
   VGA_USBAMPLITUDEGRAPHSAMPLE,
   VGA_USBAMPLITUDEGRAPHALARM,
   VGA_USBDISTANCEGRAPHSAMPLE,
   VGA_USBDISTANCEGRAPHALARM,
   VGA_USBFORCEGRAPHSAMPLE,
   VGA_USBFORCEGRAPHALARM,
   VGA_USBFREQUENCYGRAPHSAMPLE,
   VGA_USBFREQUENCYGRAPHALARM,
   VGA_USBGLOBALFLAG,
   VGA_USBPOWERGRAPHSAMPLE,
   VGA_USBPOWERGRAPHALARM,
   VGA_USBVELOCITYGRAPHSAMPLE,
   VGA_USBVELOCITYGRAPHALARM,
   VGA_USBWELDDATASAMPLE,
   VGA_USBWELDDATAALARM,
   VGA_USBSETUP,
   VGA_VELOCITYGRAPH,
   VGA_VELOCITYPRINTNOW,
   VGA_VGAEXITBUTTON,
   VGA_VGANEXTBUTTON,
   VGA_VGAPREVBUTTON,
   VGA_VGASAVEBUTTON,
   VGA_VIEWGRAPHS,
   VGA_VIEWSETUPCHOICE,
   VGA_WELDRESETCOUNTCANCEL,
   VGA_WELDRESETCOUNTOK,
   VGA_WELDRETRACT,
   VGA_WELDHISTORY,
   VGA_WELDPSHISTORY,
   VGA_WELDSTATE,
   VGA_WINDOWSSETUP,
   VQSQUALITYSCREEN,

   /*user id parameters start from 6000*/
     PASSWORD_CHANGE = 6000,
     USER_LEVEL_CHANGE,
     AUTHORITY_CHANGE,
     ACTIVE_STATUS_CHANGE,
     PASSWORD_EXP_TIME,
     IDLE_LOGOUT_TIME,
     /* calibration parameters start from 6100*/
     ACT_CALIBRATION = 6100,
     FORCE_CALIBRATION_PARAMID,
     PRESSURE_CALIBRATION_PARAMID,

     /*act cold start and counters*/
     ACT_COLD_START = 6200,
     WELD_CYCLE_COUNT,
     BATCH_COUNT,

	
	WELDPRESSURE_HD = 6210,
	FLOWCONTROL_HD,

   } EDIT_PARAM_TYPE;


extern POSITION EventHistoryTemp_pos;
extern CList<CString,CString> tempEventHistoryList;


#endif // !defined(AFX_EVENTLOG_H__566C2B5F_79CD_4FCF_AC0A_1CD0345DD1C5__INCLUDED_)
