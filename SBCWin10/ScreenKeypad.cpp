/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ScreenKeypad.cpp_v   1.36   17 Jun 2016 10:48:24   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ScreenKeypad.cpp_v  $
 * 
 *    Rev 1.36   17 Jun 2016 10:48:24   RJamloki
 * Don't show value when alphanumeric is PASSWORD_ID
 * 
 *    Rev 1.35   16 Apr 2015 19:42:50   rjamloki
 * Background color fix for UDI scan
 * 
 *    Rev 1.34   16 Apr 2015 05:59:10   sesharma
 * Coverity fix and removed hard-codeed strings from the code.
 * 
 *    Rev 1.33   08 Apr 2015 13:08:20   AnPawar
 * change in VGAVarEntryMode() function to restrict max input digits in variable field.
 * 
 *    Rev 1.32   03 Apr 2015 06:35:48   amaurya
 * change in ProcessBarcodeSCANCharacters() function to allow barcode entery on all screens and checking max aray length to fix garbage character issue.
 * 
 *    Rev 1.31   27 Mar 2015 11:02:16   amaurya
 * Condition added to update barcode string immediately after entering new value.Clear the UDI string on preset barcode character start character change.
 * 
 *    Rev 1.30   11 Mar 2015 09:27:42   amaurya
 * Chenged to diplay "New Value" text on SBC UI screen.
 * 
 *    Rev 1.29   11 Feb 2015 06:21:12   amaurya
 * fix for down speed change please wait going into infinite loop
 * 
 *    Rev 1.28   26 Jan 2015 13:37:14   rjamloki
 * Drawing barcode right after getting enter key. Fix for Runresult screen not updating after going to column setup.
 * 
 *    Rev 1.27   02 Jan 2015 05:01:58   rjamloki
 * ProcessBarcodeSCANCharacters() function changed to fix duplicate weld count on run screen and var_format_def2 VarFormatTable[] changed to display weld and hold pressure as whole number
 * 
 *    Rev 1.26   12 Dec 2014 06:05:32   RJamloki
 * ProcessPressedAlphakey() to display password on horn clamp and e-stop screen.
 * 
 *    Rev 1.25   11 Dec 2014 06:50:38   RJamloki
 * ProcessPressedAlphakey() changed to not to display cursur after any data entered upto it's maximum length.
 * 
 *    Rev 1.24   28 Nov 2014 08:31:22   rjamloki
 * Added space bar support
 * 
 *    Rev 1.23   10 Nov 2014 02:51:04   rjamloki
 * LookforBarcodeScan() and ProcessBarcodeSCANCharacters() changed for UdiScan.
 * 
 *    Rev 1.22   01 Oct 2014 10:52:20   AnPawar
 * SendCommandForQualityWindow() function call removed.
 * 
 *    Rev 1.21   25 Sep 2014 12:08:34   AnPawar
 * changes for caps lock and shift key
 * 
 *    Rev 1.20   11 Sep 2014 09:48:26   rjamloki
 *  Event Reason keypad related changes
 * 
 *    Rev 1.19   05 Sep 2014 07:00:38   amaurya
 * Enable large waiting time in SendCommandForPassword()
 * 
 *    Rev 1.18   02 Sep 2014 03:32:02   rjamloki
 * Added DisabledChars to keep not allowed keys on alpha keypad
 * 
 *    Rev 1.17   18 Aug 2014 07:48:22   rjamloki
 * Fix for char allowed in main.gui not working.
 * 
 *    Rev 1.16   28 Jul 2014 14:10:42   rjamloki
 * adde function bool CScreenKeypad::ProcessBarcodeSCAN(int Key,CChildView *view,CDC *pDC)
 * 
 *    Rev 1.15   22 Jul 2014 08:12:36   akaushal
 * Changes for VGA file path .
 * 
 *    Rev 1.14   09 Jul 2014 07:04:58   akaushal
 * Full keyboard support.Changes for access level and large waiting time.
 * 
 *    Rev 1.13   20 Jun 2014 10:55:36   akaushal
 * Added password for AES and added pleasewait screen in SendCommandForPassword function.
 * 
 *    Rev 1.12   11 Jun 2014 06:47:14   rjamloki
 * StoreIdleLogoutTime function to store idle logout time.  
 * 
 *    Rev 1.11   09 Jun 2014 11:52:16   rjamloki
 * Variable initialization in constructor.Coverity fixes.
 * 
 *    Rev 1.10   20 May 2014 11:02:46   rjamloki
 * Macro to disable printf.  
 * 
 *    Rev 1.9   07 May 2014 13:09:20   akaushal
 * Array size changed.
 * 
 *    Rev 1.8   23 Apr 2014 11:25:08   akaushal
 * Code Cleanup
 * 
 *    Rev 1.7   21 Apr 2014 13:43:30   akaushal
 * Added functionality for selecting preset and change password.
 * 
 *    Rev 1.6   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.5     07 Mar 2014 11:15:36 rjamloki     
 * Modify User Changes.
 *
 *    Rev 1.4     05 Mar 2014 14:13:32 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:05:24 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:32 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:34 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:00 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "Application.h"
#include "ScreenKeypad.h"
#include "ChildView.h"
#include "VgaMenu.h"
#include "VgaMenuItem.h"
#include "VgaVariable.h"
#include "RadioMenu.h"
#include "VgaAlphanumeric.h"
#include "VgaButton.h"
#include "Time.h"
#include "Date.h"
#include "VgaSubMenu.h"
#include "VgaBottomMenu.h"
#include "VGA.h"
#include "useridtable.h"

#ifdef DISABLEPRINTF
#define printf
#endif


extern CChildView::PrintValues Setup,WeldHistory,PowerGraph,ColDistance,VelocityGraph,
ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence,Welddata;

extern CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

extern void PresetNumberExecute(int);

#define strnset _strnset

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define USERNAME_ID 2701
#define PASSWORD_ID 1015
#define OLDPASSWORD_ID 4010
#define NEWPASSWORD_ID 4011
#define CONFIRMPASSWORD_ID 4012
#define PRESET_NUM_EXECUTE 4086// added for presetnumber execute
#define ACT_SNO 1084
#define ALPHA_NUMKEYPROP_LENGTH 100
extern CChildView::PrintingSetup PrintSetup;
extern CList<CString,CString> tempRunScreenList;
extern POSITION RunScreenTemp_pos;
extern POSITION HistoryTemp_pos;
extern CList<CString,CString> tempHistoryList;
extern UDISCANSTATUS UdiStatus;
int MaxDigitsUdiScan = 0;//The variable keeps count of udi scan characters. If the run screen is switched before getting the enter character 
						//this count is made 0 again. That means user has to reenter the new scan and old scanned characters
						//are discarded.

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CScreenKeypad::CScreenKeypad()
{
	KeyOffFlag = false;
	ShiftKeyEnable = false;
	Object_Text_pointer = NULL;
	PresetPointer = 0;
	type = 0;
	ID_type = 0;
	CurrentTextOnly = false;//Coverity 11602
	DisabledChars.Empty();
}
CString GlobalScanString;
CString CScreenKeypad::StrME_1,CScreenKeypad::Str_Off,CScreenKeypad::StrME_2,
CScreenKeypad::StrME_3,CScreenKeypad::StrME_4,CScreenKeypad::StrME_5,
CScreenKeypad::Str_Reenter,CScreenKeypad::StrPassTitle,CScreenKeypad::StrEnterPass,
CScreenKeypad::StrConfirmPass,CScreenKeypad::StrPassIncorrect;	
CString CScreenKeypad::StrME_1ID,CScreenKeypad::StrME_2ID,CScreenKeypad::StrME_3ID,
CScreenKeypad::StrME_4ID,CScreenKeypad::StrME_5ID,CScreenKeypad::Str_ReenterID,
CScreenKeypad::StrPassTitleID,CScreenKeypad::StrEnterPassID,
CScreenKeypad::StrConfirmPassID,CScreenKeypad::StrPassIncorrectID,
CScreenKeypad::Str_OffID,CScreenKeypad::HornTitleID;
bool    CScreenKeypad::showScreenKeypad;
int     CScreenKeypad::NoOfWeldresult=0;
bool    CScreenKeypad::Qualityflag=false;
int     CScreenKeypad::IsPassword_Accepted=0;
CString CScreenKeypad::TempPassword;
char	CScreenKeypad::EditLine[LINESIZE+1]="           ";
int 	CScreenKeypad::TypedVal = 0;
CRect	CScreenKeypad::PressedKeyRect=CRect(0,0,0,0);
bool    CScreenKeypad::DPFlag = false;
int     CScreenKeypad::DecimalCount = 0;
int		CScreenKeypad::DigitCounter = 0;
int		CScreenKeypad::pointer;
int		CScreenKeypad::TotalDigits = 0;
bool	CScreenKeypad::MaxDigitFlag = false;
static enum CScreenKeypad::FIRSTKEYPRESS FirstKeyPress = CScreenKeypad::KEY_NONE;	
bool	CScreenKeypad::ErrorDisplayed ;
bool	CScreenKeypad::pressed=false;
char	CScreenKeypad::FILLCHAR =' ';
bool	CScreenKeypad::OnKeypadScreen = false;
int		CScreenKeypad:: PrevPressedAlphaNumKey=KEYPAD_NONE;
int		CScreenKeypad:: Index=0;             
int		CScreenKeypad:: MaxDigit=0;      
int		CScreenKeypad::  KeyCount;					/*Store the key pressed count of same key*/
char	CScreenKeypad:: AlphaBuf[MAX_ALPHA_BUFF];       /*Original value buffer*/
char    CScreenKeypad:: OutputLine[MAX_ALPHA_BUFF]="_"; 
bool    CScreenKeypad:: EntryFlag=false;       /*TRUE when value is entered successfully.*/
char    CScreenKeypad::login_userID[MAX_CHARS_LOGIN];
char    CScreenKeypad::login_password[MAX_CHARS_LOGIN];
char	CScreenKeypad:: Assign_UserID[MAX_CHARS_LOGIN];
char	CScreenKeypad:: Old_Password[MAX_CHARS_LOGIN];
char	CScreenKeypad:: New_Password[MAX_CHARS_LOGIN];
char	CScreenKeypad:: Confirm_Password[MAX_CHARS_LOGIN];
bool    CScreenKeypad:: ExtKeyBoard = false;
int CScreenKeypad::type = 0;

char CScreenKeypad::AlphaNumKeyProp[][5]={"!","@","#","$","%","^","&","*", "(",")",
		"1","2","3","4","5","6","7","8", "9","0",
		"A","B","C","D","E","F","G","H", "I","J",
		"K","L","M","N","O","P","Q","R", "S","T",
		"U","V","W","X","Y","Z","SFT","<--", "-->","ENT","~","`", "-","_","=","+","[","{","]","}","?","|", ";",":",
		"'","/",",","<",".",">",
		"a","b","c","d","e","f","g","h", "i","j",
		"k","l","m","n","o","p","q","r", "s","t",
		"u","v","w","x","y","z","SFT","<--", "-->","ENT"};

static struct CScreenKeypad::var_format_def2 VarFormatTable[] =
{
	{{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "%   ", 3, 0,  1, FALSE,   1,    1 }},
	{{ "lb  ", 4, 0,  1, FALSE, 1, 10 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
	{{ "lb  ", 4, 1,  1, FALSE, 1,  1 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
	{{ "s   ", 2, 3,  1, FALSE, 1,  1 }, { "s   ", 2, 3,  1, FALSE,   1,    1 }},
	{{ "PSI ", 3, 1,  1, FALSE, 1,  1 }, { "kPa ", 3, 0,  1, FALSE, 689, 1000 }},
	{{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 2,  1, FALSE, 254, 1000 }},
	/* DISTANCE3, requires special handling for 7-character strings */
	{{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 3,  1, FALSE, 254,  100 }},
	{{ "Hz  ", 5, 0,  1, FALSE, 1,  1 }, { "Hz  ", 5, 0,  1, FALSE,   1,    1 }},
	{{ "Hz  ", 4, 0,  1,  TRUE, 1,  1 }, { "Hz  ", 4, 0,  1,  TRUE,   1,    1 }},
	{{ "J   ", 3, 1,  1, FALSE, 1,  1 }, { "J   ", 3, 1,  1, FALSE,   1,    1 }},
	{{ "    ", 9, 0,  1, FALSE, 1,  1 }, { "    ", 9, 0,  1, FALSE,   1,    1 }},
	{{ "in/s", 2, 1,  1, FALSE, 1, 10 }, { "mm/s", 4, 0,  1, FALSE, 254, 1000 }},
	{{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }},
	{{ "    ", 5, 0,  1, FALSE, 1,  1 }, { "    ", 5, 0,  1, FALSE,   1,    1 }},
	{{ "    ", 2, 0,  1, FALSE, 1,  1 }, { "    ", 2, 0,  1, FALSE,   1,    1 }},
	{{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "%   ", 3, 1,  1, FALSE,   1,    1 }},
	{{ "J   ", 5, 0,  1, FALSE, 1, 10 }, { "J   ", 5, 0,  1, FALSE,   1,   10 }},
	{{ "    ", 4, 0,  1, FALSE, 1,  1 }, { "    ", 4, 0,  1, FALSE,   1,    1 }},
	{{ "s   ", 8, 3,  1, FALSE, 1,  1 }, { "s   ", 8, 3,  1, FALSE,   1,    1 }},
	{{ "PSI ", 3, 0,  1, FALSE, 1,  10 }, { "kPa ", 3, 0,  1, FALSE,  689, 1000 }},
};

// Array of all SBC key on Keypad.
int CScreenKeypad::Alpha_key_no[10][10]={
		KEYPAD_EXCLAMATION ,KEYPAD_AT,KEYPAD_HASH,KEYPAD_DOLLAR,KEYPAD_PERCENT,
		KEYPAD_CIRCUMFLEX,KEYPAD_AMPERSAND,KEYPAD_ASTERISK,KEYPAD_OPENPARENTHESIS,KEYPAD_CLOSEPARENTHESIS,
		KEYPAD_1,KEYPAD_2,KEYPAD_3,KEYPAD_4,KEYPAD_5,
		KEYPAD_6,KEYPAD_7,KEYPAD_8,KEYPAD_9,KEYPAD_0,
		KEYPAD_A,KEYPAD_B,KEYPAD_C,KEYPAD_D,KEYPAD_E,KEYPAD_F,KEYPAD_G,KEYPAD_H,KEYPAD_I,KEYPAD_J,
		KEYPAD_K,KEYPAD_L,KEYPAD_M,KEYPAD_N,KEYPAD_O,KEYPAD_P,KEYPAD_Q,KEYPAD_R,KEYPAD_S,KEYPAD_T,
		KEYPAD_U,KEYPAD_V,KEYPAD_W,KEYPAD_X,KEYPAD_Y,KEYPAD_Z,
		KEYPAD_SHIFT1,KEYPAD_BACKSPACE1,KEYPAD_RIGHTARROW1,KEYPAD_ENTER1,
		KEYPAD_TILDE,KEYPAD_ACUTE,KEYPAD_HYPHEN,KEYPAD_UNDERSCORE,KEYPAD_EQUALS,KEYPAD_PLUS,
		KEYPAD_OPENBRACKET,KEYPAD_OPENBRACE,KEYPAD_CLOSEBRACKET,KEYPAD_CLOSEBRACE,
		KEYPAD_QUESTIONMARK,KEYPAD_VERTICALBAR,KEYPAD_SEMICOLON,KETPAD_COLON,KEYPAD_APOSTROPHE,
		KEYPAD_FORWARDSLASH,KEYPAD_COMMA,KEYPAD_LESSTHAN,KEYPAD_PERIOD,KEYPAD_GREATERTHAN,
		KEYPAD_a,KEYPAD_b,KEYPAD_c,KEYPAD_d,KEYPAD_e,KEYPAD_f,KEYPAD_g,KEYPAD_h,KEYPAD_i,KEYPAD_j,
		KEYPAD_k,KEYPAD_l,KEYPAD_m,KEYPAD_n,KEYPAD_o,KEYPAD_p,KEYPAD_q,KEYPAD_r,KEYPAD_s,KEYPAD_t,
		KEYPAD_u,KEYPAD_v,KEYPAD_w,KEYPAD_x,KEYPAD_y,KEYPAD_z,
		KEYPAD_SHIFT,KEYPAD_BACKSPACE,KEYPAD_RIGHTARROW,KEYPAD_ENTER,
	};

//struct containing the SBC KeyCode and external Keyboard keycode.
static struct  CScreenKeypad::ALPHA_NUM_KEY KeyProp[] = {
	CScreenKeypad::KEYPAD_CLOSEPARENTHESIS,CScreenKeypad::VK_CLOSEPARENTHESIS,
	CScreenKeypad::KEYPAD_EXCLAMATION,CScreenKeypad::VK_EXCLAMATION,
	CScreenKeypad::KEYPAD_AT,CScreenKeypad::VK_AT,
	CScreenKeypad::KEYPAD_HASH,CScreenKeypad::VK_HASH,
	CScreenKeypad::KEYPAD_DOLLAR,CScreenKeypad::VK_DOLLAR,
	CScreenKeypad::KEYPAD_PERCENT,CScreenKeypad::VK_PERCENT,	
	CScreenKeypad::KEYPAD_CIRCUMFLEX,CScreenKeypad::VK_CIRCUMFLEX,
	CScreenKeypad::KEYPAD_AMPERSAND,CScreenKeypad::VK_AMPERSAND,
	CScreenKeypad::KEYPAD_ASTERISK,CScreenKeypad::VK_ASTERISK,
	CScreenKeypad::KEYPAD_OPENPARENTHESIS,CScreenKeypad::VK_OPENPARENTHESIS,
	CScreenKeypad::KEYPAD_1,CScreenKeypad::VK_1,
	CScreenKeypad::KEYPAD_2,CScreenKeypad::VK_2,
	CScreenKeypad::KEYPAD_3,CScreenKeypad::VK_3,
	CScreenKeypad::KEYPAD_4,CScreenKeypad::VK_4,
	CScreenKeypad::KEYPAD_5,CScreenKeypad::VK_5,
	CScreenKeypad::KEYPAD_6,CScreenKeypad::VK_6,
	CScreenKeypad::KEYPAD_7,CScreenKeypad::VK_7,
	CScreenKeypad::KEYPAD_8,CScreenKeypad::VK_8,
	CScreenKeypad::KEYPAD_9,CScreenKeypad::VK_9,
	CScreenKeypad::KEYPAD_0,CScreenKeypad::VK_0,
	CScreenKeypad::KEYPAD_A ,CScreenKeypad::VK_A,
	CScreenKeypad::KEYPAD_B ,CScreenKeypad::VK_B,
	CScreenKeypad::KEYPAD_C ,CScreenKeypad::VK_C,
	CScreenKeypad::KEYPAD_D ,CScreenKeypad::VK_D,
	CScreenKeypad::KEYPAD_E ,CScreenKeypad::VK_E,
	CScreenKeypad::KEYPAD_F ,CScreenKeypad::VK_F,
	CScreenKeypad::KEYPAD_G ,CScreenKeypad::VK_G,
	CScreenKeypad::KEYPAD_H ,CScreenKeypad::VK_H,
	CScreenKeypad::KEYPAD_I ,CScreenKeypad::VK_I,
	CScreenKeypad::KEYPAD_J ,CScreenKeypad::VK_J,
	CScreenKeypad::KEYPAD_K ,CScreenKeypad::VK_K,
	CScreenKeypad::KEYPAD_L ,CScreenKeypad::VK_L,
	CScreenKeypad::KEYPAD_M ,CScreenKeypad::VK_M,
	CScreenKeypad::KEYPAD_N ,CScreenKeypad::VK_N,
	CScreenKeypad::KEYPAD_O ,CScreenKeypad::VK_O,
	CScreenKeypad::KEYPAD_P ,CScreenKeypad::VK_P,
	CScreenKeypad::KEYPAD_Q ,CScreenKeypad::VK_Q,
	CScreenKeypad::KEYPAD_R ,CScreenKeypad::VK_R,
	CScreenKeypad::KEYPAD_S ,CScreenKeypad::VK_S,
	CScreenKeypad::KEYPAD_T ,CScreenKeypad::VK_T,
	CScreenKeypad::KEYPAD_U ,CScreenKeypad::VK_U,
	CScreenKeypad::KEYPAD_V ,CScreenKeypad::VK_V,
	CScreenKeypad::KEYPAD_W ,CScreenKeypad::VK_W,
	CScreenKeypad::KEYPAD_X ,CScreenKeypad::VK_X,
	CScreenKeypad::KEYPAD_Y ,CScreenKeypad::VK_Y,
	CScreenKeypad::KEYPAD_Z ,CScreenKeypad::VK_Z,
	CScreenKeypad::KEYPAD_TILDE,CScreenKeypad::VK_TILDE,
	CScreenKeypad::KEYPAD_ACUTE,CScreenKeypad::VK_ACUTE,
	CScreenKeypad::KEYPAD_HYPHEN,CScreenKeypad::VK_HYPHENN,
	CScreenKeypad::KEYPAD_UNDERSCORE,CScreenKeypad::VK_UNDERSCORE,
	CScreenKeypad::KEYPAD_EQUALS,CScreenKeypad::VK_EQUALS,
	CScreenKeypad::KEYPAD_PLUS,CScreenKeypad::VK_PLUS,
	CScreenKeypad::KEYPAD_OPENBRACKET,CScreenKeypad::VK_OPENBRACKET,
	CScreenKeypad::KEYPAD_OPENBRACE,CScreenKeypad::VK_OPENBRACE,
	CScreenKeypad::KEYPAD_CLOSEBRACKET,CScreenKeypad::VK_CLOSEBRACKET,
	CScreenKeypad::KEYPAD_CLOSEBRACE,CScreenKeypad::VK_CLOSEBRACE,
	CScreenKeypad::KEYPAD_QUESTIONMARK,CScreenKeypad::VK_QUESTIONMARK,
	CScreenKeypad::KEYPAD_VERTICALBAR,CScreenKeypad::VK_VERTICALBAR,
	CScreenKeypad::KEYPAD_SEMICOLON,CScreenKeypad::VK_SEMICOLONN,
	CScreenKeypad::KETPAD_COLON,CScreenKeypad::VK_COLON,
	CScreenKeypad::KEYPAD_APOSTROPHE,CScreenKeypad::VK_APOSTROPHEE,
	CScreenKeypad::KEYPAD_FORWARDSLASH,CScreenKeypad::VK_FORWARDSLASH,
	CScreenKeypad::KEYPAD_COMMA,CScreenKeypad::VK_COMMAA,
	CScreenKeypad::KEYPAD_LESSTHAN,CScreenKeypad::VK_LESSTHAN,
	CScreenKeypad::KEYPAD_PERIOD,CScreenKeypad::VK_PERIODD,
	CScreenKeypad::KEYPAD_GREATERTHAN,CScreenKeypad::VK_GREATERTHAN,
	CScreenKeypad::KEYPAD_a,CScreenKeypad::VK_a,
	CScreenKeypad::KEYPAD_b,CScreenKeypad::VK_b,
	CScreenKeypad::KEYPAD_c,CScreenKeypad::VK_c,
	CScreenKeypad::KEYPAD_d,CScreenKeypad::VK_d,
	CScreenKeypad::KEYPAD_e,CScreenKeypad::VK_e,
	CScreenKeypad::KEYPAD_f,CScreenKeypad::VK_f,
	CScreenKeypad::KEYPAD_g,CScreenKeypad::VK_g,
	CScreenKeypad::KEYPAD_h,CScreenKeypad::VK_h,
	CScreenKeypad::KEYPAD_i,CScreenKeypad::VK_i,
	CScreenKeypad::KEYPAD_j,CScreenKeypad::VK_j,
	CScreenKeypad::KEYPAD_k,CScreenKeypad::VK_k,
	CScreenKeypad::KEYPAD_l,CScreenKeypad::VK_l,
	CScreenKeypad::KEYPAD_m,CScreenKeypad::VK_m,
	CScreenKeypad::KEYPAD_n,CScreenKeypad::VK_n,
	CScreenKeypad::KEYPAD_o,CScreenKeypad::VK_o,
	CScreenKeypad::KEYPAD_p,CScreenKeypad::VK_p,
	CScreenKeypad::KEYPAD_q,CScreenKeypad::VK_q,
	CScreenKeypad::KEYPAD_r,CScreenKeypad::VK_r,
	CScreenKeypad::KEYPAD_s,CScreenKeypad::VK_s,
	CScreenKeypad::KEYPAD_t,CScreenKeypad::VK_t,
	CScreenKeypad::KEYPAD_u,CScreenKeypad::VK_u,
	CScreenKeypad::KEYPAD_v,CScreenKeypad::VK_v,
	CScreenKeypad::KEYPAD_w,CScreenKeypad::VK_w,
	CScreenKeypad::KEYPAD_x,CScreenKeypad::VK_x,
	CScreenKeypad::KEYPAD_y,CScreenKeypad::VK_y,
	CScreenKeypad::KEYPAD_z,CScreenKeypad::VK_z,
	CScreenKeypad::KEYPAD_SHIFT,CScreenKeypad::VK_SHIFT1,
	CScreenKeypad::KEYPAD_BACKSPACE,CScreenKeypad::VK_BACKSPACE,
	CScreenKeypad::KEYPAD_RIGHTARROW,CScreenKeypad::VK_RIGHTARROW,
	CScreenKeypad::KEYPAD_ENTER,CScreenKeypad::VK_ENTER,
	CScreenKeypad::KEYPAD_INC,CScreenKeypad::VK_INC,
	CScreenKeypad::KEYPAD_DEC,CScreenKeypad::VK_DEC,
	CScreenKeypad::KEYPAD_0,CScreenKeypad::VK_NUM0,
	CScreenKeypad::KEYPAD_1,CScreenKeypad::VK_NUM1,
	CScreenKeypad::KEYPAD_2,CScreenKeypad::VK_NUM2,
	CScreenKeypad::KEYPAD_3,CScreenKeypad::VK_NUM3,
	CScreenKeypad::KEYPAD_4,CScreenKeypad::VK_NUM4,
	CScreenKeypad::KEYPAD_5,CScreenKeypad::VK_NUM5,
	CScreenKeypad::KEYPAD_6,CScreenKeypad::VK_NUM6,
	CScreenKeypad::KEYPAD_7,CScreenKeypad::VK_NUM7,
	CScreenKeypad::KEYPAD_8,CScreenKeypad::VK_NUM8,
	CScreenKeypad::KEYPAD_9,CScreenKeypad::VK_NUM9,
	CScreenKeypad::KEYPAD_ASTERISK,CScreenKeypad::VK_NUMASTRISK,
	CScreenKeypad::KEYPAD_PLUS,CScreenKeypad::VK_NUMPLUS,
	CScreenKeypad::KEYPAD_HYPHEN,CScreenKeypad::VK_NUMMINUS,
	CScreenKeypad::KEYPAD_PERIOD,CScreenKeypad::VK_NUMPERIOD,
	CScreenKeypad::KEYPAD_FORWARDSLASH,CScreenKeypad::VK_NUMFORWARDSLASHH,
	CScreenKeypad::KEYPAD_ENTER1,CScreenKeypad::VK_ENTER1,
	CScreenKeypad::KEYPAD_SPACEBAR,CScreenKeypad::VK_SPACEBAR,
	-1,-1,
};
struct CScreenKeypad::VInf VarInfo;
static struct CScreenKeypad::AInf AlphaInfo;
CScreenKeypad::~CScreenKeypad()
{
	CScreenKeypad::Qualityflag=false;
	
}

/**
 * This function is used when message screen is displayed on screen keypad.OnKeypadScreen_flag is set to false when 
 * nack is received from WC.Till the message screen is displayed OnKeypadScreen_flag remain flase.
 * This flag is set to true in ontimer function.
 */
bool CScreenKeypad::RestoreKeypad(void)
{
	bool ret = false;
	if(showScreenKeypad)
		ret =  true;
	else
		ret = false;
	return ret;
}
/*********************************************************************************************/
/* this function is called when keypad list is prepared for any variable, alpha numeric       */
/* date or time object.																		  */
/* arg1: type of the object																	  */
/* arg2: pointer to the structure of the respestive object									  */
/* arg3: data for the object																  */
/* arg4: object text to be displayed as the keypad title.									  */
/*																							  */
/**********************************************************************************************/

CScreenKeypad::CScreenKeypad(int type1,int Pointer,unsigned char *&data,CString* Object_Text)
{
	KeyOffFlag = false;
	ShiftKeyEnable = false;
	Object_Text_pointer = NULL;
	PresetPointer = 0;
	type = 0;
	ID_type = 0;
	CurrentTextOnly = false;
	DisabledChars.Empty();
}

CScreenKeypad::CScreenKeypad(int type1,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr)
{
	PresetPointer = 0;
	CChildView::IsTwoSecExpired = true;
	ShiftKeyEnable=false;
	KeyOffFlag=false;
	InitializedValues();
	OutputLine[LINESIZE] = 0;
	FirstKeyPress = KEY_NONE;
	VarInfo.Value= -1;//VarInfo.Value;
	type=type1;
	ID_type=ID;
	pointer=(int)ptr;
	Object_Text_pointer=Object_Text;
	VarInfo.Metric=CChildView::metric;
	CurrentTextOnly = false;
	DisabledChars.Empty();
	
	if (type==CVgaMenu::HHMM)
	{
		CVgaTime *PtrTime=(CVgaTime *)ptr;
		
		VarInfo.Keypad_title =PtrTime->text;
		VariableTitleID = PtrTime->textID;
		Str_Curr=PtrTime->CurrentString ;
		Str_CurrID=PtrTime->CurrentStringID;
		Str_New=PtrTime->NewString ;
		Str_NewID=PtrTime->NewStringID;
		strcpy(CScreenKeypad:: OutputLine,"HH:MM");
		VarInfo.Disable=0;
	}
	if(type==CVgaMenu::DATE)
	{
		CDate *ptrDate=(CDate *)ptr;
		VarInfo.Keypad_title = ptrDate->text ;
		VariableTitleID =ptrDate->textID;
		Str_Curr=ptrDate->CurrentString ;
		Str_CurrID=ptrDate->CurrentStringID;
		Str_New=ptrDate->NewString ;
		Str_NewID=ptrDate->NewStringID;
		if (CChildView::metric== false)
			strcpy( OutputLine,"MM/DD/YY"); 
		else
			strcpy( OutputLine,"DD/MM/YY");
		VarInfo.Disable=0;
	}
	/*getting variable information.*/
	if(type==CVgaMenu::VARIABLE)
	{
		CVgaVariable *ptrvariable =(CVgaVariable *)ptr;
		AlphaInfo.Hide=false;
		int length =40;
		Str_Curr=ptrvariable->CurrentString ;
		Str_CurrID=ptrvariable->CurrentStringID;
		Str_New=ptrvariable->NewString ;
		Str_NewID=ptrvariable->NewStringID;
		VarInfo.Keypad_title = ptrvariable->Keypad_title ;
		VariableTitleID =ptrvariable->textID;
		VarInfo.Format=ptrvariable->Format;//	Variable format, enum FORMAT 2 bytes
		VarInfo.Digits= ptrvariable->Digits ;//	Number of digits to display
		VarInfo.NewVal = ptrvariable->NewVal ;	//	Current value
		VarInfo.MinVal = ptrvariable->MinVal ;//	Minimum value
		VarInfo.MaxVal = ptrvariable->MaxVal ;//Maximum value
		VarInfo.ID = ptrvariable->ID ;	//Variable ID
		VarInfo.Disable	= ptrvariable->Disable ;//TRUE if variable can be disabled
		VarInfo.Disableflag = ptrvariable->DisableFlag ; //flag	Pointer to disable/enable flag
		VarInfo.Bitmask = ptrvariable->Bitmask ;//Bit used for this variable enable
		VarInfo.FunName = ptrvariable->FunName;
		VarInfo.MaxInputDigits = ptrvariable->MaxInputDigits;		
		struct var_format_def1 *FormatPtr;
		if (VarInfo.Metric)                         /* Point to format info */
			FormatPtr = &VarFormatTable[ VarInfo.Format].Metric;
		else
			FormatPtr = &VarFormatTable[ VarInfo.Format].English;
		
		VarInfo.MinVal = ConvertInternalExternal( VarInfo.MinVal,(FORMAT)VarInfo.Format );
		VarInfo.MaxVal = ConvertInternalExternal( VarInfo.MaxVal,(FORMAT)VarInfo.Format);
		VarInfo.NewVal = ConvertInternalExternal( VarInfo.NewVal,(FORMAT)VarInfo.Format);
		
		/* Convert energey format if it's too large to show to one */
		/* decimal place. */
		if (VarInfo.Format == ENERGY && (VarInfo.NewVal >= 10000 ||
			VarInfo.MaxVal >= 10000 || VarInfo.MinVal >= 10000))
			ConvertVariableFormat( ENERGY, ENERGYDIV10 );      
		
		if (VarInfo.Digits)  /* Find where on line to put # */
		{
			VarInfo.StartPos = (LINESIZE - VarInfo.Digits);
			VarInfo.Size = LINESIZE + 1 - VarInfo.StartPos;
		}
		else
		{
			VarInfo.Size = VarSize( (FORMAT)VarInfo.Format );
			VarInfo.StartPos = LINESIZE + 1 - VarInfo.Size;
		}
		/* Some special rules on value entry if sign display is forced */
		/* (as for FREQOFFSET format).  Value being entered is stored */
		/* as an absolute value during the entry process, with the sign */
		/* contained in VarInfo.Sign.  Sign will stay the same as it */
		/* was when item was selected, unless Inc/Dec keys used. */
		if (FormatPtr->ShowSign)
		{
			if (VarInfo.NewVal < 0)
			{
				VarInfo.NewVal = - VarInfo.NewVal;
				VarInfo.Sign = -1;
			}
			else
				VarInfo.Sign = 1;
		}
		else
			VarInfo.Sign = 0;	       
		
		if (VarInfo.Disable)
			VarInfo.Disableflag&= ~(VarInfo.Bitmask);
		
		
		char ValueLine[LINESIZE+1] = "                    "; 
		SINT32 NewVal;			
		if (VarInfo.Sign == -1)
			NewVal = -VarInfo.NewVal;
		else
			NewVal = VarInfo.NewVal;
		
		FormatNum( NewVal,  ValueLine);				
		SplitString(ValueLine, " ", Temp_Str);
	}
	
	if(type==CVgaMenu::ALPHA)
	{
		CVgaAlphanumeric *ptrAlphanumeric =(CVgaAlphanumeric *)ptr;
		CurrentTextOnly = ptrAlphanumeric->CurrentTextOnly;
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		int Titlelength =40;
		Str_Curr=ptrAlphanumeric->CurrentString ;
		Str_New=ptrAlphanumeric->NewString ;
		AlphaInfo.Alpha_Keypad_title=ptrAlphanumeric->TitleKeyPad ;
		AlphaTitleID=ptrAlphanumeric->textID;
		AlphaInfo.Current_Alpha_Value = ptrAlphanumeric->CurrentAlphaValue;
		int lengthDummy = INTEGERLENGTH;
		AlphaInfo.MaxLength=ptrAlphanumeric->CharAllowed ; 
		union {
			bool hid;
			int integer;
		} hide_union;
		hide_union.integer= ptrAlphanumeric->CharHidden ; 
		AlphaInfo.Hide=hide_union.hid;
		AlphaInfo.MenuNak=ptrAlphanumeric->MenuNak;
		AlphaInfo.MenuAck=ptrAlphanumeric->MenuAck;
		AlphaInfo.FunName = ptrAlphanumeric->FunName;
		DisabledChars = ptrAlphanumeric->CharNotAllowed;
		VarInfo.Disable=0;
	}
	
	if(type == VGA_PASSWORD)
	{
		PressedKeyRect=CRect(0,0,0,0);
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		AlphaInfo.Hide=true;
		VarInfo.Disable=0;
		AlphaInfo.MaxLength=12;
		PassWordMenu="";
		if((pointer!=0)&&(pointer!=1))
		{
			
			switch(ptr->GetType())
			{
				case CVgaMenu::SUBMENU:
				{
					CVgaSubMenu *ptr1=(CVgaSubMenu *)ptr;
					PassWordMenu=ptr1->submenu;
				}
				break;
				case CVgaMenu::BottomMenu_Id:
				{
					CVgaBottomMenu *Bottom=(CVgaBottomMenu *)ptr;
					PassWordMenu=Bottom->BottomSubmenu;
				}
				break;
				case CVgaMenu::VGA_Button_OBJECT:
				{
					CVgaButton * VgaButtonptr=(CVgaButton *)ptr;
					PassWordMenu=VgaButtonptr->MenuName;
				}
				break;
			}
		}
	}
	if(type==SaveScanA||type == SaveScanB || type==SaveScanC)
	{
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		AlphaInfo.Alpha_Keypad_title=CChildView::thisPtr->Str_HornId;//Str_HornId[CChildView::Language_Index];
		AlphaInfo.Current_Alpha_Value =*Object_Text_pointer;
		AlphaInfo.MaxLength=10;
		AlphaInfo.Hide=false;
		VarInfo.Disable=0;
	}
	
}
/*****************************************************************************/
/* This function draws the keypad screen for variable or alphanumeric menu   */
/* item. The function display the title information as well as the current   */
/* value of the variable in the current value box. It draws the keypad button*/ 
/* in Released format                                                        */
/*                                                                           */
/* Parameters                                                                */
/* *pDC : Device context object to draw keypad                               */
/*****************************************************************************/


void CScreenKeypad::Draw(CDC *pDC)
{
	int left =Left_Of_Keys(type);
	int top=Top_CoOrdinate_Key(type);
	
	char strline2[][4]={" 1 "," 2 "," 3 "," 4 "," 5 "," 6 "," 7 "," 8 "," 9 ","INC",
		" 0 ","DEC", "ESC", ".","ENT",NULL,NULL,NULL};
	int count=0;int keyid=0;
	CString VariableTitle=VarInfo.Keypad_title;
	CString AlphaTitle= AlphaInfo.Alpha_Keypad_title;
	CString TempTitlePass = StrPassTitle;
	CString TempEnterPass = StrEnterPass;
	CString TempConfirmPass = StrConfirmPass;
	CString TempCurr = Str_Curr;
	CString TempNew = Str_New;
	CRect keypadrect;
	/*Draw bounding rectangle */
	pDC->SelectObject(&CVgaMenuItem::penBlack1);
	pDC->Rectangle(Boundry_Rect(type));//19+XOFFSET,43+YOFFSET,630+XOFFSET,430+YOFFSET);
	CVgaMenuItem::DrawRect(pDC, Blue,  Bounding_Rect(type));//bounding RECT BLUE
	
	//Draw Box to type text
	if(CurrentTextOnly) 
	{		
		CVgaMenuItem::DrawRect(pDC, White,SINGLE_TEXT_BOX_RECT); //Draw a bigger rectangle 
	}
	else
	{
		//Draw current value rectangle on left
		if(type != VGA_PASSWORD)
			CVgaMenuItem::DrawRect(pDC, White,  Current_Value_Rect(type));
		//Draw new value rect on right
		CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect(type));
	}

	//Draw the title text
	if(CChildView::thisPtr->StringDebugFlag)
	{
		VariableTitle=VariableTitleID + _T(" ") + VarInfo.Keypad_title;
		if((type==CVgaMenu::ALPHA))
		{
			AlphaTitle = AlphaTitleID+ _T(" ") + AlphaInfo.Alpha_Keypad_title;
		}
		else
			AlphaTitle = HornTitleID + _T(" ") + AlphaInfo.Alpha_Keypad_title;
		TempTitlePass = StrPassTitleID + _T(" ")+ StrPassTitle;
		TempEnterPass = StrEnterPassID + _T(" ")+ StrEnterPass;
		TempConfirmPass= StrConfirmPassID + _T(" ")+ StrConfirmPass;
		TempCurr= Str_CurrID + _T(" ")+ Str_Curr;
		TempNew = Str_NewID + _T(" ")+ Str_New;
	}
	if(type == VGA_PASSWORD)
	{
		CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect, 
			TempTitlePass/*[CChildView::Language_Index]*/,true);
		
		if(pointer!=1)
			CVgaMenuItem::DrawText(pDC, SmallFont, White,New_Value_String_Rect(type), 
			TempEnterPass/*[CChildView::Language_Index]*/,false);
		else
			CVgaMenuItem::DrawText(pDC, SmallFont, White,New_Value_String_Rect(type),
			TempConfirmPass/*[CChildView::Language_Index]*/,false);
	}
	else if((type!=CVgaMenu::ALPHA)&&(type!=SaveScanA)&&(type != SaveScanB)&&( type!=SaveScanC))
		CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect, 
		VariableTitle,true);
	else if((type==CVgaMenu::ALPHA)||(type==SaveScanA||type == SaveScanB || type==SaveScanC))
	{
		CVgaMenuItem::DrawText(pDC, Bigfont, White,Keypad_Title_Rect,AlphaTitle,true);
		if(AlphaTitleID != XSTR(PASSWORD_ID))  
		   CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect(type),AlphaInfo.Current_Alpha_Value ,false);
	}
	if(type == CVgaMenu::DATE)//CScreenObject::DATE)
	{
		CString text_obj=*Object_Text_pointer;
		text_obj.Delete(0,2);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect(type),
			TempCurr,false);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect(type), 
			TempNew,false);
		CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect(type),
			text_obj ,false);
	}
	else if(type == CVgaMenu::HHMM)
	{
		CString text_obj=*Object_Text_pointer;
		text_obj.Delete(0,2);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect(type), 
			TempCurr,false);
		CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect(type), 
			TempNew,false);
		CVgaMenuItem::DrawText(pDC, SmallFont, Black, Current_Value_Rect(type),text_obj ,false);
	}
	else if((type != VGA_PASSWORD))
	{
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Current_Value_String_Rect(type),
			TempCurr,false);
		//If CurrentTextOnly flag is true then no need of new value title
		if((type==CVgaMenu::ALPHA) && (!CurrentTextOnly))
		{
			CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect(type), 
			TempNew,false);
		}
		if((type==CVgaMenu::VARIABLE) && (!CurrentTextOnly))
		{
			CVgaMenuItem::DrawText(pDC, SmallFont, White, New_Value_String_Rect(type), 
			TempNew,false);
		}

	}
	pDC->SetBkMode(TRANSPARENT);		
	for(int j=0;j<TOTAL_KEYPAD_ROW  ;j++)
	{
		for(int k=0;k<TOTAL_KEYPAD_COLOUMN(type) ;k++)
		{
			keypadrect=CRect(left,top,left+Width_Of_Key(type),top+Width_Of_Key(type));
			OffsetRect(pDC,&keypadrect,CChildView::Color_Array[Gray]);
			pressed = false;
			Draw_Pressed_Released_Button(pDC, &keypadrect);
			if(((type ==CVgaMenu::ALPHA)||(type == VGA_PASSWORD)
				||(type==SaveScanA||type == SaveScanB || type==SaveScanC)))
			{
				if(ShiftKeyEnable)
					CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,
					AlphaNumKeyProp[count + TOTAL_KEYPAD_ROW *TOTAL_KEYPAD_COLOUMN(type) ],true);
				else
					CVgaMenuItem::DrawText(pDC, SmallFont,Black,keypadrect,
					AlphaNumKeyProp[count],true);
			}
			else
			{
				CVgaMenuItem::DrawText(pDC, SmallFont, Black,keypadrect,strline2[count],true);
					
			}
			left+=Width_Of_Key(type) + Gap_Of_Key(type);
			count++;
		}
		left=Left_Of_Keys(type);
		top+=Width_Of_Key(type) + Gap_Of_Key(type);
	}
	///DRAWING DECIMAL POINT
	CVgaMenuItem::DrawRect(pDC, Black,  CRect(420+YOFFSET,375+XOFFSET,
		420+YOFFSET+3,375+XOFFSET+3));
	
	//drawing rect of "off"
	if((VarInfo.Disable==1)&&(VarInfo.ID!=1))
	{
		CVgaMenuItem::DrawRect(pDC, Gray,  Button_Off_Rect);
		CVgaMenuItem::DrawText(pDC, SmallFont,Black,OFF_Rect,Str_Off/* "OFF"*/,true);
		Draw_Pressed_Released_Button(pDC, &OFF_Rect);
	}
	if(type!=CVgaMenu::VARIABLE)
	{
		if((type==CVgaMenu::ALPHA) && (CurrentTextOnly))
			CVgaMenuItem::DrawText(pDC, SmallFont,Black,Current_Value_Rect(type), OutputLine,false); 
		else
			CVgaMenuItem::DrawText(pDC, SmallFont,Black,New_Value_Rect(type), OutputLine,false); 
	}
	else
		CVgaMenuItem::DrawText(pDC,SmallFont,Black,New_Value_Rect(type), EditLine,false);
	if(ErrorDisplayed)
		ErrorDisplayed=false;
	if(type==CVgaMenu::VARIABLE)
	{ 	
		DisplayVGAMinMax(pDC);
		CVgaMenuItem::DrawText(pDC, SmallFont, Black,Current_Value_Rect(type),Temp_Str ,false);
		VGADisplayCurrentNewValue(pDC);/*Display the Existing Value*/
	}
}

/*****************************************************************************************************/
/* the function checks the position of the mouse click. if the user has clicked on any keypad button */
/* then this function draws that keypad button in the pressed state.                                 */
/*																									 */
/*****************************************************************************************************/
void CScreenKeypad::DrawPressedkey(CPoint point, CDC *pDC)
{
	PressedKeyRect=CRect(0,0,0,0);
	int left =Left_Of_Keys(type);
	int top=Top_CoOrdinate_Key(type);
	CRect keyrect;
	for(int j=0;j<TOTAL_KEYPAD_ROW;j++)
	{
		for(int k=0;k<TOTAL_KEYPAD_COLOUMN(type);k++)
		{
			keyrect=CRect(left,top,left+Width_Of_Key(type),top+Width_Of_Key(type));
			if(keyrect.PtInRect(point))
			{
				PressedKeyRect =keyrect;
				pressed=true;
				Draw_Pressed_Released_Button(pDC,&keyrect);
				break;
			}
			left+=Width_Of_Key(type) + Gap_Of_Key(type);
		}
		left=Left_Of_Keys(type);
		top+=Width_Of_Key(type) + Gap_Of_Key(type);
	}
	if(((VarInfo.Disable==1)&&(VarInfo.ID!=1))
		&& OFF_Rect.PtInRect(point))
	{
		PressedKeyRect =OFF_Rect;
		pressed=true;
		Draw_Pressed_Released_Button(pDC,&OFF_Rect);
	}
}

/**********************************************************************************/
/* this function is called when the user releases the left mouse button if		  */
/* keypad is active. if the user has pressed any button then this function draws  */
/* that button in the released state.											  */
/**********************************************************************************/

void CScreenKeypad::Draw_Pressed_Released_Button(CDC *pDC, CRect rect)
{
	//CPen * oldPen;
	if (pressed)
		pDC->SelectObject(&CVgaMenuItem::penBlack1);
	else
		pDC->SelectObject(&CVgaMenuItem::penWhite1);
	pDC->MoveTo(rect.left, rect.top );
	pDC->LineTo(rect.right , rect.top );
	pDC->MoveTo(rect.left + 1 , rect.top + 1);
	pDC->LineTo(rect.right , rect.top + 1);
	pDC->MoveTo(rect.left , rect.top );
	pDC->LineTo(rect.left , rect.bottom );
	pDC->MoveTo(rect.left + 1 , rect.top + 1 );
	pDC->LineTo(rect.left + 1 , rect.bottom );
	if (pressed)
		pDC->SelectObject(&CVgaMenuItem::penWhite1);
	else
		pDC->SelectObject(&CVgaMenuItem::penBlack1);
	pDC->MoveTo(rect.right - 1 , rect.top );
	pDC->LineTo(rect.right - 1 , rect.bottom );
	pDC->MoveTo(rect.right - 2 , rect.top + 1 );
	pDC->LineTo(rect.right - 2 , rect.bottom );
	pDC->MoveTo(rect.left , rect.bottom - 1 );
	pDC->LineTo(rect.right , rect.bottom - 1 );
	pDC->MoveTo(rect.left + 1 , rect.bottom - 2 );
	pDC->LineTo(rect.right , rect.bottom - 2 );
	//pDC->SelectObject(oldPen);
}


void CScreenKeypad::OffsetRect(CDC *pDC,CRect rect, COLORREF col)
{
	CRect r(rect);
	//r.OffsetRect(XOFFSET, YOFFSET);
	pDC->FillSolidRect(&r,col);
}

/********************************************************************************************************/
/* This function is called when the user clicks on keypad. the function checks the key pressed key and  */
/* calls the function ProcessKeypad() for its processing												*/
/********************************************************************************************************/
bool CScreenKeypad::MouseClick(const CPoint &point, CChildView *view,CDC*pDC )
{
	if(pressed==true)
		pressed=false;
	Draw_Pressed_Released_Button(pDC, PressedKeyRect);
	int left =Left_Of_Keys(type);
	int top=Top_CoOrdinate_Key(type);
	int i=0;
	CRect keypadrect;
	for(int j=0;j<TOTAL_KEYPAD_ROW;j++)
	{
		for(int k=0;k<TOTAL_KEYPAD_COLOUMN(type);k++)
		{
			keypadrect=CRect(left,top,left+Width_Of_Key(type),top+Width_Of_Key(type));
			if(keypadrect==PressedKeyRect)
			{
				i++;
				if(ProcessKeypad(j,k,view,pDC))
					view->Invalidate();
				break;									
			}
			if(i>0)
				break;
			left+=Width_Of_Key(type) + Gap_Of_Key(type);
		}
		left = Left_Of_Keys(type);
		top += Width_Of_Key(type) + Gap_Of_Key(type);
	}
	if(((VarInfo.Disable==1)&&(VarInfo.ID!=1)) 
		&& (PressedKeyRect==OFF_Rect))
		ProcessKeypad(5,0,view,pDC);
	return 0;
}


/****************************************************************************/
/* This function processes the keypad screen entries. It checks for INC/DEC */
/* key pressed or Digits key pressed and process them accordingly. It will  */
/* remain in the function unless and until ENT or ESC key is pressed on the */
/* keypad. One can also get out from this function by pressing bottom button*/
/*                                                                          */
/****************************************************************************/
bool CScreenKeypad::ProcessKeypad(int x, int y,CChildView *view,CDC *pDC)
{
	int Num_key_no[][3]={KEYPAD_1,KEYPAD_2,KEYPAD_3,KEYPAD_4,KEYPAD_5,KEYPAD_6,KEYPAD_7,KEYPAD_8,KEYPAD_9,KEYPAD_INC,KEYPAD_0,
	KEYPAD_DEC,KEYPAD_BACKSPACE,KEYPAD_PERIOD,KEYPAD_ENTER,KEYPAD_OFF};
	bool exit;
	printf("\nKeypress %d, %d, %d ",x,y,Alpha_key_no[x][y]);
	if(type == CVgaMenu::HHMM)//Time
		exit=ProcessPressedAlphakey( Num_key_no[x][y] , type,view,pDC);          
	else if(type == CVgaMenu::DATE)//_DATE
		exit=ProcessPressedAlphakey( Num_key_no[x][y] , type,view,pDC);
	else if(type!=CVgaMenu::VARIABLE){ // Alpha, ScanA,SacnB,SacnC,Password
		if(ShiftKeyEnable)
			x += TOTAL_KEYPAD_ROW;
		exit=ProcessPressedAlphakey( Alpha_key_no[x][y] , type,view,pDC);
	}
	else // Variable
		exit =VGAVarEntryMode( Num_key_no[x][y],pDC,view);
	if(exit)
		OnKeypadScreen_flag=false;
	return exit;
}

/****************************************************************************/
/* This function processes the key code coming from external keyboard and   */
/* convert it to ALPHA_KEYPADID enum value.									*/
/* function only handle the numeric keys									*/
/****************************************************************************/
int CScreenKeypad::ConvertKeyForNumKeyboard(int Key)
{
	int SBCKey = KEYPAD_NONE;
	int x = 0;
	while(KeyProp[x].KeyCode != -1)
	{
		if(KeyProp[x].KeyCode == Key){
			SBCKey = KeyProp[x].KeyNum;
			break;
		}
		x++;
	}
	return SBCKey;
}

/****************************************************************************/
/* This function processes the key code coming from external keyboard and   */
/* convert it to ALPHA_KEYPADID enum value. This function also handle the   */
/* Capslock ans shift key pressed along with any other key as keycode is    */
/*same for 'A' and 'a' for example.function handles the alphsnumeric keys also*/
/****************************************************************************/
int CScreenKeypad::ConvertKeyForAlphaKeyboard(int Key)
{
	int SBCKey = KEYPAD_NONE;
	bool CapsLock = false;
	bool ShiftKey = false;
	
	int x = 0;
	if(Key == 0x10)//Only the ShiftKey is pressed on Keyboard.
		return SBCKey;
	if (GetKeyState(VK_SHIFT) & 0x8000  ) //Shift key is pressed with other keys
		ShiftKey = true;
	if (GetKeyState(VK_CAPITAL) & 0x01 ) // Caps lock is ON
		CapsLock = true;
	int smallKey = Key;
	if(ShiftKey)
		smallKey += VK_SHIFT1;
	/*Only for characters a-z with Capslock on.When a-z comes make them A-Z.
	  If Shift is pressed with a-z then no need to make A-Z*/
	if(CapsLock && Key >= CScreenKeypad::VK_a && Key <= CScreenKeypad::VK_z)
	{
		if(ShiftKey==false)
			smallKey += VK_SHIFT1;
		else
			smallKey -= VK_SHIFT1;
	}
	Key = smallKey;

	while(KeyProp[x].KeyCode != -1)
	{
		if(KeyProp[x].KeyCode == Key){
			SBCKey = KeyProp[x].KeyNum;
			break;
		}
		x++;
	}
	return SBCKey;
}

/****************************************************************************/
/* This function is called from OnKeyDown function whenver user presses any  */
/* Key on keyboard while keypad is open on the SBC screen.                   */
/* This function will call functions to covert the Key code into SBC Key format */
/*first and then based on keypad type on SBC it will call functions to process*/
/* Numeric or alpha numeric keypad.											*/
/****************************************************************************/
bool CScreenKeypad::ProcessKeypadfromKeyboard(int Key,CChildView *view,CDC *pDC)
{
	bool exit = false;
	int SBCKey = KEYPAD_NONE;	
	ExtKeyBoard = true;
	if((type==ALPHAKEYPAD)||(type==VGA_PASSWORD)||(type==SaveScanA)||(type==SaveScanB)||(type==SaveScanC)){
		SBCKey = ConvertKeyForAlphaKeyboard(Key);
		if(SBCKey != KEYPAD_NONE)
			exit=ProcessPressedAlphakey( SBCKey , type,view,pDC);
	}
	else{
		SBCKey = ConvertKeyForNumKeyboard(Key);		
		if(SBCKey != KEYPAD_NONE)
		{
			if((type == CVgaMenu::HHMM)||(type == CVgaMenu::DATE))
				exit =ProcessPressedAlphakey( SBCKey,type,view,pDC);
			else
			{	
				exit =VGAVarEntryMode( SBCKey,pDC,view);
				Index++;/*Increment the index value*/
				MaxDigit++;
			}
		}
	}
	if(exit)
		OnKeypadScreen_flag=false;
	ExtKeyBoard = false;
	return exit;
}

/****************************************************************************/
/* This function is called from OnKeyDown function whenver user Scans a barcode  */
/* on Weld result screen on the SBC screen.                   */
/* This function will call functions to covert the Key code into SBC Key format */
/*first and then based on keypad type on SBC it will call functions to process*/
/* alpha numeric characters.											*/
/****************************************************************************/
bool CScreenKeypad::ProcessBarcodeSCAN(int Key,CChildView *view,CDC *pDC)
{
	bool exit = false;
	int SBCKey = KEYPAD_NONE;	
	SBCKey = ConvertKeyForAlphaKeyboard(Key);
	if(SBCKey != KEYPAD_NONE)
		exit = ProcessBarcodeSCANCharacters( SBCKey ,view,pDC);
	return exit;
}

/*************************************************************************************/
/* This function is called from ProcessBarcodeSCAN function whenver a barcode        */
/* character is received. Function will first check for Enter key, if enter key      */
/* has come from barcode that means the barcode is complete. If Enter key has come   */
/* and Barcode string has some characters in it then it will process the barcode.    */
/* Processing barcode contains few steps:											 */
/* 1.> Display the Barcode on Weld result screen.									 */
/* 2.> Send a command to Wc to handle the barcode.									 */
/* If the Barcode character is not Enter key then fill the characters in a string    */
/* for later processing. The max characters that we can handle is 25 characters      */
/* as that is the max length for serial number or preset name. if scan length is bigger*/
/* then void all previous characters and start from one.							 */
/*************************************************************************************/
bool CScreenKeypad::ProcessBarcodeSCANCharacters(int KeyPressed,CChildView *view,CDC *pDC)
{
	char AlphaNumChar;

	static CString BarcodeString = "";
	if(MaxDigitsUdiScan == 0)
		BarcodeString = "";
	// Check for End character i.e. Enter key and make sure the Barcode string is not null.
	if(((KeyPressed == KEYPAD_ENTER)||(KeyPressed == KEYPAD_ENTER1))&&(BarcodeString.GetLength() > 0))
	{
		GlobalScanString = BarcodeString;
		if(CChildView::thisPtr->RunResultScreen)//show udi scan on run result screen
		{				
			CVgaMenu * menu = theApp.MenuPointer;
			POSITION pos1= menu->items.GetHeadPosition();					   
			CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color,CRect(10,395,370,425));   
			int Temp = 0;
			while (pos1)
			{
				CVgaMenuItem *object= menu->items.GetNext(pos1);			
				int type = object->GetType();
				if((type == CVgaMenu::VGA_Button_OBJECT) && (Temp == BARCODE_BUTTON_POSITION))
				{
					CVgaButton *ptr=(CVgaButton *)object;

					if((GlobalScanString.GetLength() > 0)  && (GlobalScanString.GetAt(0) != CChildView::thisPtr->PresetBarCodeStart.GetAt(0)))
					{		
						ptr->text= GlobalScanString;		
					}
					else if(UdiStatus == UDISCAN_WAITING)
					{
						ptr->text= WaitForUDIScan; 
					}
					else
						ptr->text="";    
					object->Draw(pDC);				                				
				}
				Temp++;
			}
		}

		unsigned char data[MAXSCANBUFF_LEN];
		memset(data,0,sizeof(data));
		sprintf((char *)(data),"%s",GlobalScanString);
		CHostCommand * request = new CHostCommand(BARCODESCAN_CMD ,data,MAXSCANBUFF_LEN);
		CHostCommand * response = app->SendUiHostCommand(request);
		if(response)
		{
			delete response;		
		}

		// First Display the Scan String on Weld Results screen and then send the command to WC
		// with Scan string where WC can recall a preset or advance the state machine if waiting for scan.
		MaxDigitsUdiScan = 0;
		BarcodeString = "";
		return true;
	}

	if(KeyPressed!=KEYPAD_ENTER)
	{
		MaxDigitsUdiScan++;
		if(MaxDigitsUdiScan < MAXSCAN_LEN)
		{

			if(KeyPressed<ALPHA_NUMKEYPROP_LENGTH)
			{
				// Get the Character from AlphaNumKeyProp table for received code.
				AlphaNumChar = (char)AlphaNumKeyProp[KeyPressed][0];
				BarcodeString+=AlphaNumChar;
			}			
			//Fill the space character in Barcode String.				
			else
				BarcodeString += " ";	
		}

	}	

	return false;
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the Alpha key pressed on the keypad screen.*/
/*  On pressing the key again with in one sec key toggling will take place.*/
/*  Else on pressing other key the char will display on the next position. */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGAAlphaEntryMode(int KeyPressed,CChildView *view,CDC *pDC)
{
	char AlphaNumChar;
	if(ExtKeyBoard == false)
		KeyCount = 1;

	/*Esc if value is entered at 0th index of OutputLine Buffer*/
	if((PrevPressedAlphaNumKey != KEYPAD_NONE))
	{				
		if(AlphaInfo.Hide && OutputLine[MaxDigit] != '_' &&
			OutputLine[MaxDigit] != '*' )
			OutputLine[MaxDigit] = '*';
		Index++;/*Increment the index value*/
		MaxDigit++;
	}		
	if(KeyPressed==KEYPAD_DEC)
		AlphaNumChar=' ';
	else
		AlphaNumChar = (char)AlphaNumKeyProp[KeyPressed][0];

	//Storing the char value on array and display it on screen
	/*Display the cursor at next position if cursor is not displayed*/                
	if((MaxDigit < (AlphaInfo.MaxLength - 1)) ) //&& (CurrentTextOnly == false)
		OutputLine[MaxDigit + 1] = '_';
	if(MaxDigit == (AlphaInfo.MaxLength - 1))/*Don't display the cursor after*/
		OutputLine[MaxDigit+1] = FILLCHAR;   /*entering max char.*/

	if(MaxDigit < AlphaInfo.MaxLength)
	{
		OutputLine[MaxDigit] = AlphaNumChar;
		AlphaBuf[Index] = AlphaNumChar;/*store the value in original buffer*/
		OutputLine[MaxDigit+2] = NUL;
		DrawString(pDC, OutputLine, CurrentTextOnly);
	}
	PrevPressedAlphaNumKey = KeyPressed;
	/*Store the currently pressed key */
}
		
/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the valid key pressed on the keypad screen.*/
/*  For any alpha key it will call the QVGAAlphaEntryMode, for Enter key   */
/*  will enter the name if it is not null.On pressing ESC it will erase    */
/*  the last entered character.                                            */
/***************************************************************************/
bool CScreenKeypad::ProcessPressedAlphakey(int KeyPressed, int type,CChildView *view,CDC *pDC)
{
	bool Exit = FALSE;/*Return TRUE on pressing ENT or ESC at first time.*/
	int J =0;
	int i = 0;
   for(CString sItem = DisabledChars.Tokenize(_T(","),i); i >= 0; sItem = DisabledChars.Tokenize(_T(","), i))
   {
	   if(_ttoi(sItem) == (int)AlphaNumKeyProp[KeyPressed][0])
		   return false;
   }
	switch(KeyPressed)
	{
	case KEYPAD_SHIFT:
	case KEYPAD_SHIFT1:		
		ShiftKeyEnable=!ShiftKeyEnable;
		view->Invalidate();
		break;
	case KEYPAD_SPACEBAR:
	case KEYPAD_RIGHTARROW:  /* Move cursor right by one position */
	case KEYPAD_RIGHTARROW1:
		
		if( (type == CVgaMenu::ALPHA)
			||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))
		{
			printf("ProcessPressedAlphakey()\n");
			if(MaxDigit < AlphaInfo.MaxLength)
			{
				KeyPressed = KEYPAD_DEC;
				VGAAlphaEntryMode(KeyPressed,view,pDC);
				CChildView::thisPtr->Invalidate();
			}  
			else
				CChildView::ErrorBeep();
		}
		else
			CChildView::ErrorBeep();
		break;
		
	case KEYPAD_PERIOD:
		if((type ==  CVgaMenu::ALPHA
			||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC)) && MaxDigit < (AlphaInfo.MaxLength-1))//alpha
		{			
			/*Esc if value is entered at 0th index of OutputLine Buffer*/
			if(PrevPressedAlphaNumKey != KEYPAD_NONE )
			{
				if(AlphaInfo.Hide && OutputLine[MaxDigit] != '_' && 
					OutputLine[MaxDigit] != '*')
					OutputLine[MaxDigit] = '*';
				Index++;/*Increment the index value*/
				MaxDigit++;
			}
			OutputLine[MaxDigit] = '.';
			AlphaBuf[Index] = '.';
			if(MaxDigit < (AlphaInfo.MaxLength - 1))
				OutputLine[MaxDigit + 1] = '_';
			if(MaxDigit == (AlphaInfo.MaxLength - 1))/*Don't display the cursor after*/
				OutputLine[MaxDigit+1] = FILLCHAR;  
			
			OutputLine[MaxDigit+2] = FILLCHAR;
			OutputLine[MaxDigit+3] = NUL;
			//DrawString(pDC, OutputLine);
			DrawString(pDC, OutputLine, CurrentTextOnly);
			PrevPressedAlphaNumKey =  KeyPressed; 
			CChildView::thisPtr->Invalidate();
		}
		else
		{
			/* After entering max char it should beep*/
			CChildView::ErrorBeep();
		}
		break;
		
	case KEYPAD_ENTER:
	case KEYPAD_ENTER1:
		{
			if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
			{
				CChildView::thisPtr->ErrorBeep();
				CVgaMenu *menu;
				if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
				{
					CChildView::thisPtr->AccessLevelSystem=USER_OPERATOR;
					CChildView::thisPtr->menusname.AddTail(theApp.menuName);
					CChildView::thisPtr->menus.AddTail(page_no);
					CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
					page_no=1;
					CChildView::thisPtr->ModifyObjectList(menu);   
					theApp.menuName=CVgaBottomMenu::mainMenuID;
					theApp.MenuPointer=menu;   
				}                
				CChildView::thisPtr->Invalidate();
				OnKeypadScreen_flag = false;
				Exit = true;
				break;
			}
			
			TRACE(_T("\n AlphaBuf IS %s"),AlphaBuf);
			if((type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))
			{
				CChildView::IsTwoSecExpired=true;
				VGAAlphaEntry(pDC);
				HandleEnterOnSaveScanKeypad(view,pDC);
			}
			if(type ==VGA_PASSWORD)
			{
				CChildView::IsTwoSecExpired=true;
				VGAAlphaEntry(pDC);
				HandleEnterOnPassword(view, pDC);
			}
			
			if(( type ==  CVgaMenu::ALPHA)
				&& AlphaBuf[0] != NUL && OutputLine[0]!='_' )
			{
				bool SendCommand = true;
				/* Make Release Beep */
				AlphaBuf[++Index] = NULL;
				unsigned char data[MAX_ALPHA_BUFF+3];
				unsigned char * alpha_data = (unsigned char *) &data[0];
				union 
				{
					short i;
					char c[2];
				} u;
				u.i=ID_type;
				printf("screen ID %X \n",ID_type);
				alpha_data[1]=u.c[0];
				alpha_data[0]=u.c[1];
				int length_alpha=0;
				while(AlphaBuf[length_alpha]!='\0')
					length_alpha++;
				
				
				alpha_data[2]=(char)length_alpha; //first two element keep the length
				for(J=0;J<length_alpha;J++)
					alpha_data[3+J]=AlphaBuf[J];
				
				length_alpha =length_alpha+3;
				Index=-1;
				
				if(type == CVgaMenu::ALPHA)
				{
					if(AlphaTitleID == XSTR(USERID_ID))  //username ENT pressed
					{
						strcpy(login_userID, AlphaBuf);
						strcpy(Assign_UserID,AlphaBuf);
					}
					if(AlphaTitleID==XSTR(OLDPASSWORD_ID))
						strcpy(Old_Password,AlphaBuf);
					
					if(AlphaTitleID==XSTR(NEWPASSWORD_ID))
						strcpy(New_Password,AlphaBuf);
					
					if(AlphaTitleID==XSTR(CONFIRMPASSWORD_ID))
						strcpy(Confirm_Password,AlphaBuf);
					
					if(AlphaTitleID == XSTR(PASSWORD_ID))  //password ENT pressed
						strcpy(login_password, AlphaBuf);
               		if(AlphaTitleID == XSTR(ACT_SNO))
                  		CChildView::LargeWaitingTime=true;
				}
				CVgaMenu * menu1=theApp.MenuPointer;

				if( menu1->GetName() == XSTR(LOGINMENU) || menu1->GetName() == XSTR(CHANGEPASSWORDMENU) ||
					(menu1->GetName() == XSTR(CHANGEPASSWORDMENUSYSCONFIG)) || (menu1->GetName() == XSTR(ESTOPRESETMENU)) || (menu1->GetName() == XSTR(HORNCLAMPMENU)))
				{
					SendCommand = false;
					/*XML suggestion.A separate flag can be kept in alphanumeric password button.
					If that flag is set than display **** beside button*/
					if( AlphaTitleID == XSTR(PASSWORD_ID)        
						|| AlphaTitleID == XSTR(CONFIRMPASSWORD_ID) 
						|| AlphaTitleID == XSTR(OLDPASSWORD_ID) 
						|| AlphaTitleID == XSTR(NEWPASSWORD_ID) ) //if password button then show ****
						memset(AlphaBuf,'*',strlen(AlphaBuf));

					CString output_txt=(CString)AlphaBuf;
					if( AlphaTitleID == XSTR(USERID_ID)
						|| AlphaTitleID == XSTR(PASSWORD_ID)        
						|| AlphaTitleID == XSTR(CONFIRMPASSWORD_ID) 
						|| AlphaTitleID == XSTR(OLDPASSWORD_ID) 
						|| AlphaTitleID == XSTR(NEWPASSWORD_ID) )
						*Object_Text_pointer= "  = " + output_txt;
					Str_Curr="";
					Str_New="";
				}

				if(menu1->GetName() == XSTR(ESTOPRESETMENU) || (menu1->GetName() == XSTR(HORNCLAMPMENU)))
					SendCommand = true;
				if(SendCommand == true)
				{
					CHostCommand * request = new CHostCommand(SetValue_FunID, alpha_data, length_alpha);
					CHostCommand * response = app->SendUiHostCommand(request);
					
					if (response)
					{
						char ch=CHostCommand::AckNak();
						alpha_data = response->GetData();
						length_alpha = response->GetDataLength();
						if(ch==ACK)
						{
							if(type == CVgaMenu::ALPHA)
							{
								CString output=(CString)AlphaBuf;
								if(ID_type == PRESET_BARCODE_START_ID)//Condition added to update barcode string immediately after entering new value.
								{
									CChildView::thisPtr->PresetBarCodeStart = output;
									GlobalScanString = "";//Clear the string otherwise it will display the last recalled preset number
								}
								output = "= " + output;
								output.Delete(output.GetLength(),1);
								if( (menu1->GetName() != XSTR(LOGINMENU)) && (menu1->GetName() != XSTR(CHANGEPASSWORDMENU))
									&& (menu1->GetName() != XSTR(CHANGEPASSWORDMENUSYSCONFIG)))
								{
									if(output.GetLength() !=1)
										*Object_Text_pointer = output;
									else
										*Object_Text_pointer = AlphaInfo.Current_Alpha_Value;
								}
							}
							ERRORBEEP;	
							MaxDigit=-1;
							delete response;
							AlphaBuf[0] = NULL;
							OutputLine[0] =NULL;
							if(type ==CVgaMenu::ALPHA)
								Exit = TRUE; /* Enter keypressed */ 
							
							CVgaMenu * menu;
							void *ptr;
							void (*rmn)(int);
							if(functionCall.Lookup(AlphaInfo.FunName,ptr))
							{
								rmn = (void (*)(int))ptr;
								int Address=(int)this;
								rmn(Address);
							}
							if(AlphaInfo.MenuAck!="")
							{
								if (theApp.menus.Lookup(AlphaInfo.MenuAck, menu))
								{
									page_no=1;
									CChildView::thisPtr->ModifyObjectList(menu);
									theApp.menuName = AlphaInfo.MenuAck;
									theApp.MenuPointer=menu;
								}		
							}
							CChildView::thisPtr->Invalidate();
						}
						else
							CChildView::thisPtr->ProcessNak(alpha_data,length_alpha,pointer,0);
					}
				}				
			}			
            CChildView::LargeWaitingTime=false;
			if(type == CVgaMenu::HHMM && OutputLine[0] != '_' && OutputLine[0] !='H')//TIME
				/*Validate the entered value & store if valid*/
				UpdateTimeIfValid(pDC);
			
			if(type == CVgaMenu::DATE && OutputLine[0] != '_'
				&& OutputLine[0] != 'D' && OutputLine[0] != 'M')//_DATE
				/*Validate the entered value & store if valid*/
				UpdateDateIfValid(pDC);
			if(ErrorDisplayed)
				Exit = FALSE;
			else
				Exit = TRUE; /* Enter key]pressed */
		}
		break;		
	case KEYPAD_BACKSPACE:
	case KEYPAD_BACKSPACE1:
		/* Make Release Beep */
		if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
		{
			CChildView::thisPtr->ErrorBeep();  
			CVgaMenu *menu;
			if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
			{
				CChildView::thisPtr->AccessLevelSystem=USER_OPERATOR;
				CChildView::thisPtr->menusname.AddTail(theApp.menuName);
				CChildView::thisPtr->menus.AddTail(page_no);
				CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
				page_no=1;
				CChildView::thisPtr->ModifyObjectList(menu);   
				theApp.menuName=CVgaBottomMenu::mainMenuID;
				theApp.MenuPointer=menu;   
			}                
			CChildView::thisPtr->Invalidate();
			OnKeypadScreen_flag = false;
			Exit = true;
			break;
		}
		/* If ESC key is pressed before any value is entered 
		then keypad pop up should exit */
		if((type ==  CVgaMenu::ALPHA)/*||(type == CVgaMenuItem::VGA_PRESETSAVEASSIGN)*/
			||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )|| (type==SaveScanC))//_ALPHA//_ALPHA
		{
			if( (AlphaBuf[0] == NUL)||(AlphaBuf[0] =='_')
				||(OutputLine[0] == NUL)||(OutputLine[0] =='_'))
			{
				AlphaBuf[0] = NULL;
				OutputLine[0] ='_';
				FirstKeyPress = KEY_NONE;
				Exit = TRUE;
				if((type ==VGA_PASSWORD)&&(pointer !=1)&&(pointer !=0))
				{
					theApp.menuName=view->menusname.RemoveTail();
					page_no=view->menus.RemoveTail();
					theApp.MenuPointer=view->menupointers.RemoveTail();
				}
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
				
			}
			else
			{
				KeyCount = 1;
				PrevPressedAlphaNumKey = KEYPAD_BACKSPACE;
				if(MaxDigit < AlphaInfo.MaxLength)
					OutputLine[MaxDigit] = '_';
				/* Display the cursor on prev position and decrement
				the index value*/
				OutputLine[MaxDigit+1] = FILLCHAR;
				OutputLine[MaxDigit+2] = FILLCHAR;
				OutputLine[MaxDigit+3] = NUL;
				if(MaxDigit) MaxDigit--;
				/*Not increment the index if 1st column is empty*/
				if(OutputLine[0] == '_')
					PrevPressedAlphaNumKey = KEYPAD_NONE;
				
				AlphaBuf[Index] = NUL;
				if(Index) 
					Index--;
				DrawString(pDC, OutputLine,CurrentTextOnly);
				view->Invalidate();
				printf("drawstring7 OutputLine=%s \n",OutputLine);
			}
		}
		else if(type == CVgaMenu::HHMM )//_HHMM
		{
			if( OutputLine[0] == '_'|| OutputLine[0] == 'H')
				Exit = TRUE;
			else
			{ 
			/* Display the cursor on prev position and decrement
				the index value*/
				if(MaxDigit == 3) MaxDigit--;
				OutputLine[--MaxDigit] = '_';
				OutputLine[MaxDigit+1] = ' ';
				OutputLine[MaxDigit+2] = ' ';
				OutputLine[2] = ':';
				OutputLine[5] = NULL;
				DrawString(pDC, OutputLine);
				view->Invalidate();
				printf("drawstring8 OutputLine=%s \n",OutputLine);
			}
		}
		else if(type ==CVgaMenu::DATE )//_DATE
		{
			if( OutputLine[0] == '_'|| OutputLine[0] == 'M'|| OutputLine[0] == 'D')
				Exit = TRUE;
			else
			{ 
				/* Display the cursor on prev position and decrement */
				/* the index value*/
				if(MaxDigit == 3 || MaxDigit == 6) MaxDigit--;
				OutputLine[--MaxDigit] = '_';
				OutputLine[MaxDigit+1] = ' ';
				OutputLine[MaxDigit+2] = ' ';
				OutputLine[2] = '/';
				OutputLine[5] = '/';
				OutputLine[8] = NULL;
				DrawString(pDC, OutputLine);
				view->Invalidate();
				printf("drawstring9 OutputLine=%s \n",OutputLine);
			}
		}
		break;
		default:
		if((type == CVgaMenu::ALPHA)
			||(type == VGA_PASSWORD)||(type==SaveScanA)||(type == SaveScanB )||( type==SaveScanC))
		{
			if(MaxDigit < AlphaInfo.MaxLength)
			{				
				VGAAlphaEntryMode(KeyPressed,view,pDC);
				CChildView::thisPtr->Invalidate();
			}          
			else
				CChildView::ErrorBeep();
		}/*End of type _ALPHA  */
		else if(type == CVgaMenu::HHMM)
			VGATimeEntry(KeyPressed,pDC);           
		else if(type == CVgaMenu::DATE)//_DATE
			VGADateEntry(KeyPressed,pDC);		
		break;
	}/*end of switch case  */ 
	return(Exit);			            
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function sends the host command to update date , if the all the   */
/*   variables are entered and value entered for every variable is valid.  */                                             
/***************************************************************************/
void CScreenKeypad::UpdateDateIfValid(CDC *pDC)
{
	int Day, Month, Year;
	if (VarInfo.Metric == FALSE)
	{
		//Convert the variables from string to integer type.
		Month = myatoi(&OutputLine[0]);
		Day =  myatoi(&OutputLine[3]);
		Year = myatoi(&OutputLine[6]);
	}   
	else
	{
		/*Convert the variables from string to integer type.*/
		Day = myatoi(&OutputLine[0]);
		Month =  myatoi(&OutputLine[3]);
		Year = myatoi(&OutputLine[6]);
	}
	if(CheckForValidDate(OutputLine, Day, Month, Year))
		/*Check if all the variables are entered with valid value.*/
	{
		int length = DATE_LENGTH;
		unsigned char data[DATE_LENGTH];
		unsigned char * date_data = (unsigned char *) &data[0];
		union 
		{
			short i;
			char c[2];
		} u;
		u.i=ID_type;
		date_data[1]=u.c[0];
		date_data[0]=u.c[1];
		date_data[2]=(char)3;
		date_data[3]=(char)Month;
		date_data[4]=(char)Day;
		date_data[5]=(char)Year;
		
		CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			if(ch==ACK)
			{
				CString outputdate=(CString)OutputLine;
				outputdate="> "+outputdate;
				*Object_Text_pointer=outputdate;
				/*updating the date to system date*/
				SYSTEMTIME xyz;
				GetLocalTime(&xyz);
				xyz.wYear=Year+2000;
				xyz.wMonth=Month;
				xyz.wDay=Day;
				SetLocalTime(&xyz);
				int ID=CVgaMenuItem::Convert_Char_To_Integer(date_data,length,2);
				
			}
			ERRORBEEP;
			delete response;	
		}
		ErrorDisplayed = false;
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		MaxDigit=0;
		EntryFlag = true;
	}
	else
	{
		CDate *ptrDate=(CDate *)pointer;
		/*Display the error screen and initialize the variables and */
		/*Refresh the screen.                                       */
		CVgaMenuItem::DrawRect(pDC,Blue, New_Value_String_Rect(type));
		
		CString TempReenterText = ptrDate->Str_Reenter;
		if(CChildView::thisPtr->StringDebugFlag)
			TempReenterText = ptrDate->Str_ReenterID + _T(" ")+ ptrDate->Str_Reenter;
		
		CVgaMenuItem::DrawText(pDC, SmallFont, White, 
			New_Value_String_Rect(type), TempReenterText/*Str_Reenter[CChildView::Language_Index]*/,false);
		
		CVgaMenuItem::DrawRect(pDC, Red, Error_rect);
		
		CString TempInvalidText = ptrDate->StrInvalidEntry;
		if(CChildView::thisPtr->StringDebugFlag)
			TempInvalidText = ptrDate->StrInvalidEntryID + _T(" ")+ ptrDate->StrInvalidEntry;
		
		CVgaMenuItem::DrawText(pDC, SmallFont, White, 
			Error_Str_rect, TempInvalidText/*StrInvalidEntry[CChildView::Language_Index]*/,true);
		
		ErrorDisplayed = true;
		CChildView::ErrorBeep();
		PrevPressedAlphaNumKey = KEYPAD_NONE;
		Index = 0;
		MaxDigit = 0;
		KeyCount = 1;
		EntryFlag = false;
		OutputLine[MaxDigit] = '_';
		OutputLine[MaxDigit+1] = FILLCHAR;
		if (VarInfo.Metric== false)
			DrawString (pDC, "MM/DD/YY"); 
		else
			DrawString (pDC, "DD/MM/YY");
	}
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is stored to send the host comand ,if the all the        */
/*  variables are entered and value entered for    */
/*  every variable is valid.                                               */
/***************************************************************************/
void CScreenKeypad::UpdateTimeIfValid(CDC *pDC)
{
	
	bool Valid = true;
	bool EmptyColumn = false;
	int i;
	int  Hour, Min;
	/*Convert the variables fron string to integer type.*/
	Hour= myatoi(&OutputLine[0]);
	Min=  myatoi(&OutputLine[3]);
	for(i = 0; i < MAXTIMECHAR; i++)
		/*Check if any value is not entered.*/
	{
		if(OutputLine[i] == '_')
		{
			Valid = false;
			EmptyColumn = true;
			break;
		}
	}
	if ( EmptyColumn || Min < MinLimit_Minute || Min > MaxLimit_Minute || 
		Hour < MinLimit_Hour || Hour > MaxLimit_Hour)
		/*Check for the valid entry of all variables.*/ 
		Valid = false;
	if (Valid)
	{
		int length =INTEGERLENGTH+1;
		unsigned char data[INTEGERLENGTH+1];
		unsigned char * date_data = (unsigned char *) &data[0];
		//	CScreenObject::Convert_Integer_To_Char(pointer, date_data);
		union 
		{
			short i;
			char c[2];
		} u;
		u.i=ID_type;
		date_data[1]=u.c[0];
		date_data[0]=u.c[1];
		date_data[2]=(char)2;
		date_data[3]=(char)Hour;
		TRACE(_T("\n %d") ,date_data[3]);
		date_data[4]=(char)Min;
		TRACE(_T("\n %d") ,date_data[4]);
		
		CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{		
			char ch=CHostCommand::AckNak();
			if(ch==ACK)
			{
				length = response->GetDataLength();//Getting Length.
				date_data = response->GetData();//Getting Data
				CString outputtime=(CString)OutputLine;
				outputtime="> "+outputtime;
				*Object_Text_pointer=outputtime;
				
				/*updating the Time to system date*/
				SYSTEMTIME xyz;
				GetLocalTime(&xyz);
				xyz.wHour=Hour;
				xyz.wMinute=Min;
				SetLocalTime(&xyz);
				int ID=CVgaMenuItem::Convert_Char_To_Integer(date_data,length,2);
			}
			ERRORBEEP;
			delete response;	
		} 
		ErrorDisplayed = false;
		/* Make Release Beep */
		OutputLine[0] ='_';
		OutputLine[1] ='\0';
		MaxDigit=0;
		EntryFlag = true;
	}
	else
	{ 
		CVgaTime *PtrTime=(CVgaTime *)pointer;
		/*Display the error screen,initialize the variables and */
		/*Refresh the screen.                                   */
		CVgaMenuItem::DrawRect(pDC, Blue, New_Value_String_Rect(type));
		
		CString TempReenterText = PtrTime->Str_Reenter;
		if(CChildView::thisPtr->StringDebugFlag)
			TempReenterText = PtrTime->Str_ReenterID + _T(" ")+ PtrTime->Str_Reenter;
		
		CVgaMenuItem::DrawText(pDC,SmallFont, White, 
			New_Value_String_Rect(type), TempReenterText/*Str_Reenter[CChildView::Language_Index]*/,false);
		// DrawString(&ErrorStrProp, StrInvalidEntry[LangIndex]);
		CVgaMenuItem::DrawRect(pDC, Red, Error_rect);
		
		CString TempInvalidText = PtrTime->StrInvalidEntry;
		if(CChildView::thisPtr->StringDebugFlag)
			TempInvalidText = PtrTime->StrInvalidEntryID + _T(" ")+ PtrTime->StrInvalidEntry;
		
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Error_Str_rect, 
			TempInvalidText/*StrInvalidEntry[CChildView::Language_Index]*/,true);
		ErrorDisplayed = true;
		CChildView::ErrorBeep();
		PrevPressedAlphaNumKey = KEYPAD_NONE;
		Index = 0;
		MaxDigit = 0;
		KeyCount = 1;
		EntryFlag = false;
		AlphaBuf[Index] = NUL;
		OutputLine[MaxDigit] = '_';
		OutputLine[MaxDigit+1] = FILLCHAR;
		DrawString (pDC, "HH:MM");
	}
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the key pressed on the keypad screen for   */
/*  time entry.On pressing the key the respective char value is stored to  */
/*  the string for the specified var and the cursur will move to the next  */
/*  column.                                                                */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGATimeEntry(int KeyPressed,CDC *pDC)
{
	char AlphaNumChar;
	UINT8    i;  
	if(MaxDigit < MAXTIMECHAR)/*Value of Hour & minute is not entered*/
	{
		for(i = MaxDigit; i < MAXDATECHAR; i++)
			OutputLine[i] = FILLCHAR; 
		AlphaNumChar = (char)AlphaNumKeyProp[KeyPressed][0];//.CharValue[0];
		/*Storing the char value on array and display it on screen*/
		OutputLine[MaxDigit] = AlphaNumChar;
		OutputLine[DAYCHAR] = ':';      
		MaxDigit++;
		if( MaxDigit == DAYCHAR )   MaxDigit++;
		OutputLine[MaxDigit] = '_';/*Display the cursor to the next column*/
		OutputLine[MAXTIMECHAR] = NUL;
		DrawString(pDC, OutputLine);
		printf("drawstring10 OutputLine=%s \n",OutputLine);
	}
	else
		CChildView::ErrorBeep();
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function is processing the key pressed on the keypad screen for   */
/*  date entry.On pressing the key the respective char value is stored to  */
/*  the string for the specified var and the cursur will move to the next  */
/*  column.                                                                */
/*Arg1:Which Alpha key is pressed on the keypad screen.                    */
/***************************************************************************/
void CScreenKeypad::VGADateEntry(int KeyPressed,CDC *pDC)
{
	char AlphaNumChar; 
	UINT8    i;
	if(MaxDigit < MAXDATECHAR)/*If value of Day,month & Year is not entered.*/
	{
		for(i = MaxDigit; i < MAXDATECHAR; i++)
			OutputLine[i] = FILLCHAR; 
		AlphaNumChar = (char)AlphaNumKeyProp[KeyPressed][0];//.CharValue[0] ;
		OutputLine[MaxDigit] = AlphaNumChar;
		MaxDigit++;
		OutputLine[DAYCHAR] = '/';/*store the break char b/w the variables.*/
		OutputLine[MAXTIMECHAR] = '/';
		if( MaxDigit == DAYCHAR || MaxDigit == MAXTIMECHAR )   MaxDigit++;      
		OutputLine[MaxDigit] = '_';
		OutputLine[MAXDATECHAR] = NULL;
		DrawString(pDC, OutputLine);
		printf("drawstring11 OutputLine=%s \n",OutputLine);
	}
	else
		CChildView::ErrorBeep();
}

int CScreenKeypad::myatoi(char s[])
{
	int i,n;
	i = 0;
	for(n=0;s[i] >= '0' && s[i] <= '9'; i++)
		n = 10 * n + s[i] - '0';
	return n;	
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function will check that the value entered for the date variables */
/*  is valid or not.This will also take care of the date for the leap year.*/
/*Arg1:Pointer to the output line                                          */
/*Arg2:Entered value of date.                                              */
/*Arg3:Entered value of the Month.                                         */
/*Arg4:Entered value of the year.                                          */
/*Return:                                                                  */
/*  Return TRUE if all the entered variables are valid.                    */
/***************************************************************************/
bool CScreenKeypad::CheckForValidDate(char *OutputLine, int Day, int Month, int Year)
{
	bool Valid =true;
	bool EmptyColumn = false;
	UINT8 i;
	/*Store the max. days for particular months.*/
	UINT16 MonthLength[12]={ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	for( i = 0; i < MAXDATECHAR; i++)
		/*Check if any value is not entered.*/
	{
		if(OutputLine[i] == '_')//coz _ 'll dos't appear on screen of date is completly entered 
		{
			Valid = false;
			EmptyColumn = true;
			break;
		}
	}
	if(!EmptyColumn)
	{
		if ( CheckForLeapYear(Year) )
			MonthLength[1] = LEAPYEARVALUE;//if leap year then make if 29
		/*Check for the valid entry of all variables.*/ 
		if ( Month < MinLimit_Month || Month > MaxLimit_Month )
			Valid = false;
		else if ( Day < MinLimit_Day || Day > MonthLength[Month-1] )
			Valid =false;
	}
	return ( Valid );
}

/***************************************************************************/
/*Description:-                                                            */
/*  This function will check whether the entered value of the year is      */
/*  a leap year or not.                                                    */
/*Return:                                                                  */
/*  Return TRUE if the year is a leap year.                                */
/***************************************************************************/
bool CScreenKeypad::CheckForLeapYear(int Year)
{
	bool  Result;
	Year += CENTURY;
	
	if ( (Year%4) )         
		Result = false;      
	else if ( !(Year%400) ) 
		Result = true;       
	else if ( !(Year%100) ) 
		Result = false;      
	else                    
		Result = true;   
	return ( Result );
}

/***************************************************************************/
/*Descriptions:                                                            */
/*  This function handles entry of an alphanumeric data item.  The Alpha   */
/*  Num keys on the keypad enter the values in NewVlaueEntry Box if Enter  */
/*  is pressed validate the data & change into the return string value.    */
/*  For Date & Time only Numeric Values will be allowed.                   */
/*                                                                         */
/* Parameters:                                                             */
/* *pDC  - pointer to the device context                                   */                                       
/***************************************************************************/
void CScreenKeypad::VGAAlphaEntry(CDC *pDC)
{
	
	if(  PrevPressedAlphaNumKey != KEYPAD_NONE &&
		OutputLine[MaxDigit+1] != '_' && CChildView::IsTwoSecExpired)
	{
		/*Make the prev entered char to * for password entry*/
		if(AlphaInfo.Hide==true)
			OutputLine[MaxDigit] = '*';
		/*Display the cursor at next position if cursor is not displayed*/                
		if(MaxDigit < (AlphaInfo.MaxLength - 1))
			OutputLine[MaxDigit + 1] = '_';
		if(MaxDigit == (AlphaInfo.MaxLength - 1))/*Don't display the cursor after*/
			OutputLine[MaxDigit+1] = FILLCHAR;   /*entering max char.      */
		OutputLine[MaxDigit+2] = FILLCHAR;
		OutputLine[MaxDigit+3] = NUL;
		DrawString(pDC, OutputLine);
		printf("drawstring12 OutputLine=%s \n",OutputLine);
		CChildView::thisPtr->Invalidate();
	}
}


/***************************************************************************/
/* The function handles digit entry done through keypad screen. Also if the*/
/* value entered is correct, a host command is send so that the preset is  */
/* updated with the new value. If the value entered is above or below      */
/* permissible limts an error message box is displayed                     */                  
/*                                                                         */  
/*  Parameters:                                                            */
/*    KeyPressed - Points to the keypressed on Keypad                      */
/*    *pDC  - Device context object                                        */
/*  Note: Due to strange behavior of ENERGY format, it's possible for      */
/*  format type to change while inside this function.                      */
/*                                                                         */
/***************************************************************************/
bool CScreenKeypad::VGAVarEntryMode(int KeyPressed,CDC *pDC,CChildView *view)
{
	enum ERRORCODES MinMaxNoVal;
	SINT16    x;	
	bool Exit = FALSE;
	int flag;
	
	switch(KeyPressed)
	{
		/* Tests for validity of Inc/Dec: Don't allow Inc/Dec if */
		/* ClearKey pressed (NewVal == -1).  Don't allow Inc if */
		/* at max unless sign is -1, in which case NewVal is */
		/* really at min, so Inc is okay.  Don't allow Dec if at */
		/* min if sign is 0.  If sign is +-1, then allowed range */
		/* of values is -max <= NewVal <= max, so Dec is okay */
		/* unless sign is -1 and NewVal is at max. */
	case KEYPAD_INC:
	case KEYPAD_DEC:
		if (FirstKeyPress == KEY_INC_DEC || FirstKeyPress == KEY_NONE)  	
		{
			
			if (VarInfo.Disable) /* Make sure item enabled */
				VarInfo.Disableflag &= ~(VarInfo.Bitmask);			
			if ((VarInfo.NewVal == -1) || 
				((KeyPressed == KEYPAD_INC) && 
				(VarInfo.NewVal == VarInfo.MaxVal) && 
				(VarInfo.Sign!=-1))||
				//(VarInfo.->Sign != -1)) ||
				((KeyPressed == KEYPAD_DEC) && 
				(VarInfo.NewVal == VarInfo.MinVal) && 
				(!VarInfo.Sign)) ||
				((KeyPressed == KEYPAD_DEC) && 
				(VarInfo.NewVal == VarInfo.MaxVal) && 
				(VarInfo.Sign==-1)))
					CChildView::ErrorBeep();
			else
			{
				if(ErrorDisplayed)
				{
					strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
					EditLine[0] = '_';
					EditLine[LINESIZE-1] = 0;
					CVgaMenuItem::DrawRect(pDC, Blue, Error_rect);
					DisplayVGAMinMax(pDC);
					DrawString(pDC, EditLine);
					ErrorDisplayed = FALSE;
				}
				/* Call to the Key Increment/Decrement function */
				FirstKeyPress = KEY_INC_DEC;
				VGAVarEntryIncDecMode( KeyPressed,pDC);
			}
		} 
		else
		{
			//TouchScrnBeep(10);
			ERRORBEEP;
		}		                              
		break;
		
	case KEYPAD_OFF:
		if((VarInfo.Disable == 1)&&(VarInfo.ID!=1) /*&&(VarInfo.ID !=CVgaMenuItem::XXCANTCHANGEXX)*/)
		{
			if(ErrorDisplayed)
			{
				strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
				EditLine[0] = '_';
				EditLine[LINESIZE-1] = 0;
				CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
				DisplayVGAMinMax(pDC);
				DrawString(pDC, EditLine);
				ErrorDisplayed = FALSE;
			}
			KeyOffFlag=true;
			FirstKeyPress = KEY_OFF;
			VarInfo.Disableflag |= VarInfo.Bitmask;
			//             printf("\n off key pressed");
			//             printf("\n VarInfo.Disableflag=%d",VarInfo.Disableflag);
			CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect(type));
			CVgaMenuItem::DrawText(pDC, SmallFont,Black,New_Value_Rect(type), Str_Off +"                 "/*"OFF                 "*/,false);
		}
		else
			CChildView::ErrorBeep();
		break;
		
	case KEYPAD_BACKSPACE:
		if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
		{
			CChildView::thisPtr->ErrorBeep();  
			CVgaMenu *menu;
			if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
			{
				CChildView::thisPtr->AccessLevelSystem=USER_OPERATOR;
				CChildView::thisPtr->menusname.AddTail(theApp.menuName);
				CChildView::thisPtr->menus.AddTail(page_no);
				CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
				page_no=1;
				CChildView::thisPtr->ModifyObjectList(menu);   
				theApp.menuName=CVgaBottomMenu::mainMenuID;
				theApp.MenuPointer=menu;   
			}                
			CChildView::thisPtr->Invalidate();
			OnKeypadScreen_flag = false;
			Exit = true;
			break;
		}
		/*If ESC key is pressed before any value is entered then keypad
		pop up should exit*/
		if(ErrorDisplayed)
		{
			strnset(EditLine, FILLCHAR, LINESIZE);//Clear out working buffer 
			EditLine[0] = '_';
			EditLine[1] = '\0';
			EditLine[LINESIZE-1] = 0;
			CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
			DisplayVGAMinMax(pDC);
			DrawString(pDC, EditLine);
			ErrorDisplayed = FALSE;
			FirstKeyPress = KEY_NONE;
			VarInfo.Value = -1;
		}
		else if(FirstKeyPress == KEY_NONE)
		{
			Exit = TRUE;
			CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
		}
		else
		{
			VarInfo.Value = -1;  /* Reserved to mean "illegal value" */
			strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer*/
			EditLine[LINESIZE-1] = 0;
			KeyOffFlag=false;
			/* Initialize all digit entry variables */
			TypedVal = 0;
			DPFlag = FALSE;
			DecimalCount = 0;
			DigitCounter = 0;
			TotalDigits = 0;
			MaxDigitFlag = FALSE;
			FirstKeyPress = KEY_NONE;
			DrawString(pDC, "_");
		}
		break;
		
	case KEYPAD_0:
	case KEYPAD_1:
	case KEYPAD_2:
	case KEYPAD_3:
	case KEYPAD_4:
	case KEYPAD_5:
	case KEYPAD_6:
	case KEYPAD_7:
	case KEYPAD_8:
	case KEYPAD_9:
	case KEYPAD_PERIOD:
		TRACE(_T("\n TOTAL DIGITS IS %d"),TotalDigits);
		if (FirstKeyPress == KEY_NUMBER || FirstKeyPress == KEY_NONE) 
		{
			FirstKeyPress = KEY_NUMBER;
			
			if (VarInfo.Disable) /* Make sure item enabled */
				VarInfo.Disableflag &= ~(VarInfo.Bitmask);
			if(ErrorDisplayed)
			{
				strnset(EditLine, FILLCHAR, LINESIZE);/* Clear out working buffer */
				EditLine[0] = '_';
				EditLine[LINESIZE-1] = 0;
				CVgaMenuItem::DrawRect(pDC,Blue, Error_rect);
				DisplayVGAMinMax(pDC);
				DrawString(pDC, EditLine);
				ErrorDisplayed = FALSE;
			}			
			if (TotalDigits == 0) /* If first digit entered */
			{
				if (VarInfo.Sign)
				{
					if (VarInfo.Sign == 1)
					{
						TotalDigits++;
						EditLine[0] = '+';
					} 
					else EditLine[0] = '-';
				}
				VarInfo.Value = 0;
				/* Since entry value currently zero, drop to ENERGY if 
				ENERGYDIV10 */
				if (VarInfo.Format == ENERGYDIV10)
					ConvertVariableFormat( ENERGYDIV10, ENERGY);
			}   
			if (KeyPressed != KEYPAD_PERIOD) /* Digits key pressed */
			{
				/* Here's that ENERGY special case again.  Go to ENERGYDIV10 */
				/* when user tries to enter too many digits to the left of */
				/* the decimal point. */
				if (VarInfo.Format == ENERGY && MaxDigitFlag && !DPFlag)
				{
					ConvertVariableFormat( ENERGY, ENERGYDIV10);
					MaxDigitFlag = FALSE;
				}
				if (!MaxDigitFlag) /* Check for Max digit entry allowed */
				{
					EditLine[TotalDigits++]  = AlphaNumKeyProp[KeyPressed][0];//'0' + KeyPressed;
					EditLine[TotalDigits] = '_';
					EditLine[TotalDigits+1] = 0;                  
					TypedVal = (10 * TypedVal) + (AlphaNumKeyProp[KeyPressed][0] - '0');//(KeyPressed - KEYPAD_0);
					DigitCounter++;
					/* Next compute NewVal, as we would try to store it at */
					/* this moment, from TypedVal, DPFlag, and DecimalCount. */
					VarInfo.NewVal = TypedVal;
					if (DPFlag) /* Are values entered after decimal point*/
					{
						DecimalCount++;   /* # of digits after decimal point */
						
						if(VarInfo.Metric)
						{					
							for(x=DecimalCount;
							x<(VarFormatTable[VarInfo.Format].Metric.RightDigits);
							x++)
								VarInfo.NewVal *= 10;
							if(DigitCounter >= VarFormatTable[VarInfo.Format].Metric.RightDigits)
								MaxDigitFlag = TRUE; /* Max Number of digits entered */
						}
						else if(!VarInfo.Metric)
						{
							for(x=DecimalCount;
							x<(VarFormatTable[VarInfo.Format].English.RightDigits);
							x++)
								VarInfo.NewVal *= 10;
							if(DigitCounter >= VarFormatTable[VarInfo.Format].English.RightDigits)
								MaxDigitFlag = TRUE; /* Max Number of digits entered */
						}
					}
					else
					{	
						if(VarInfo.Metric)
						{
							for (x=0; x<VarFormatTable[VarInfo.Format].Metric.RightDigits; x++)
								VarInfo.NewVal *= 10;
							if((DigitCounter >= VarFormatTable[VarInfo.Format].Metric.LeftDigits)||(DigitCounter>=VarInfo.MaxInputDigits)&&(VarInfo.MaxInputDigits>0))
								MaxDigitFlag = TRUE; /* Max Number of digits entered */
						}
						else if(!VarInfo.Metric)
						{
							for (x=0; x<VarFormatTable[VarInfo.Format].English.RightDigits; x++)
								VarInfo.NewVal *= 10;
							if((DigitCounter >= VarFormatTable[VarInfo.Format].English.LeftDigits)||(DigitCounter>=VarInfo.MaxInputDigits)&&(VarInfo.MaxInputDigits>0))
								MaxDigitFlag = TRUE; /* Max Number of digits entered */
						}
					}
					if(MaxDigitFlag)
					{
						EditLine[TotalDigits] = 0;
					}
					DrawString(pDC, EditLine);
			
				}
			}			
			else /* Point key pressed */
			{
				if(!VarInfo.Metric)
				{
					if (VarFormatTable[VarInfo.Format].English.RightDigits && !DPFlag)
					{
						DPFlag = TRUE;
						if((VarInfo.Sign && (TotalDigits == 1))||
							(TotalDigits == 0))
							EditLine[TotalDigits++] = '0';
						EditLine[TotalDigits++] = '.';
						EditLine[TotalDigits] = '_';
						EditLine[TotalDigits+1] = 0;                  
						DrawString(pDC, EditLine);
						MaxDigitFlag = FALSE;
						DigitCounter = 0;
					}
					else 
						CChildView::ErrorBeep();
				}
				else if(VarInfo.Metric)
				{
					
					if (VarFormatTable[VarInfo.Format].Metric.RightDigits && !DPFlag)
					{
						DPFlag = TRUE;
						if((VarInfo.Sign && (TotalDigits == 1))||
							(TotalDigits == 0))
							EditLine[TotalDigits++] = '0';
						EditLine[TotalDigits++] = '.';
						EditLine[TotalDigits] = '_';
						EditLine[TotalDigits+1] = 0;                  
						DrawString(pDC, EditLine);
						MaxDigitFlag = FALSE;
						DigitCounter = 0;
					}
					else 
						CChildView::ErrorBeep();				
				}				
			}
		}
		break;
		
	case KEYPAD_ENTER:
		if(CChildView::thisPtr->DisplayLockFlag )/* Display Lock Active ?*/
		{
			CChildView::thisPtr->ErrorBeep();
			CVgaMenu *menu;
			if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
			{
				CChildView::thisPtr->AccessLevelSystem=USER_OPERATOR;
				CChildView::thisPtr->menusname.AddTail(theApp.menuName);
				CChildView::thisPtr->menus.AddTail(page_no);
				CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
				page_no=1;
				CChildView::thisPtr->ModifyObjectList(menu);   
				theApp.menuName=CVgaBottomMenu::mainMenuID;
				theApp.MenuPointer=menu;   
			}                
			CChildView::thisPtr->Invalidate();
			OnKeypadScreen_flag = false;
			Exit = true;
			break;
		}
		if (((VarInfo.NewVal > VarInfo.MaxVal) || /* Error chk */
			(VarInfo.NewVal < VarInfo.MinVal) ||
			(VarInfo.Value == -1))&&(KeyOffFlag==false))
		{
			if (VarInfo.Value == -1)
				MinMaxNoVal = NOVALUE;
			else if (VarInfo.NewVal > VarInfo.MaxVal)
				MinMaxNoVal = MAXRANGE;
			else MinMaxNoVal = MINRANGE;
			
			/* Another ugly kludge.  System can't display Max */
			/* for ENERGY type because it won't fit in space */
			/* allowed.  So need to convert to ENERGYDIV10 */
			/* before calling DisplayMinMaxError().  It's okay */
			/* to do this because we aren't going to keep any */
			/* of the VarInfo data anyway. */
			
			if (VarInfo.Format == ENERGY)
			{
				VarInfo.Value = 0;     /* Don't try to convert -1 */
				ConvertVariableFormat( ENERGY, ENERGYDIV10 );
			}
			
			DisplayVGAMinMaxError(MinMaxNoVal,pDC); /* Display Err Msg */
			CVgaMenuItem::DrawRect(pDC,Blue, New_Value_String_Rect(type));
			CString TempReenter = Str_Reenter;
			if(CChildView::thisPtr->StringDebugFlag)
				TempReenter = Str_ReenterID + _T(" ")+ Str_Reenter;
			
			CVgaMenuItem::DrawText(pDC, SmallFont, White, 
				New_Value_String_Rect(type), 
				TempReenter/*[CChildView::Language_Index]*/,false);
			ErrorDisplayed = TRUE;
			TypedVal = 0;
			DPFlag = FALSE;
			DecimalCount = 0;
			DigitCounter = 0;
			TotalDigits = 0;
			MaxDigitFlag = FALSE;
			
			/* Convert energey format if it's too large to show to one 
			/* decimal place. */
			if (VarInfo.Format == ENERGY && VarInfo.NewVal >= 10000)
				ConvertVariableFormat( ENERGY, ENERGYDIV10 );      
		}
		
		else  /* Entered value within permissible limits*/
		{
			if((VariableTitleID==XSTR( PRESET_NUM_EXECUTE ))&&(VarInfo.Format==INTEGER))
			{
				PresetNumberExecute(VarInfo.NewVal);//New Function Added to jump to preset Number
				printf("New value=%d\n",VarInfo.NewVal);
				Exit= true;
				break;
			}
			void *ptr;
			void (*rmn)(int);
			if(functionCall.Lookup(VarInfo.FunName,ptr))
			{
				rmn = (void (*)(int))ptr;
				int Address=(int)this;
				rmn(Address);
			}
			
			
			if (VarInfo.Sign == -1)
				VarInfo.NewVal = -VarInfo.NewVal;
			VarInfo.NewVal = ConvertExternalInternal(VarInfo.NewVal,(FORMAT)VarInfo.Format);
			flag = VarInfo.Disable? VarInfo.Disableflag : false;
			if((VarInfo.Value != VarInfo.NewVal)|| (flag == VarInfo.Disableflag)
				||((VarInfo.NewVal == 0)&&(VarInfo.MinVal == 0)))
			{
				/*Sending Host Command to save Entered Value.*/
				int length =8;
				unsigned char data[9];
				unsigned char * date_data = (unsigned char *) &data[0];
				union 
				{
					short i;
					char c[2];
				} u;
				u.i=ID_type;
				date_data[1]=u.c[0];
				date_data[0]=u.c[1];
				union {
					int disable_flag;
					char x[INTEGERLENGTH];
				} dsb;
				dsb.disable_flag=VarInfo.Disableflag;
				data[3]=(char)dsb.x[0];
				data[2]=(char)dsb.x[1];
				union {
					int Variable_Value;
					char y[INTEGERLENGTH];
				} v;
				v.Variable_Value=VarInfo.NewVal;
				for (int j = 0; j <INTEGERLENGTH ; j++)
					date_data[7-j]=(char)v.y[j];
				
				
				CHostCommand * request = new CHostCommand(SetValue_FunID, date_data, length);
				CHostCommand * response = app->SendUiHostCommand(request);
				
				if (response)
				{	
					CChildView::LargeWaitingTime=false;
					char ch=CHostCommand::AckNak();
					date_data=response->GetData();
					length = response->GetDataLength(); 
					if(ch==ACK)
					{		
						ERRORBEEP;
						view->ModifyObjectList(theApp.MenuPointer);
						if(CScreenKeypad::Qualityflag==true)
						{							
							CScreenKeypad::Qualityflag=false;
						}
						showScreenKeypad = false;
						Exit = TRUE; /* Enter keypressed */    
					}
					else if(ch==NAK)
					{
						view->ProcessNak(date_data,length,pointer,0 );	
						CChildView::thisPtr->Invalidate();
						showScreenKeypad = true;
						OnKeypadScreen_flag = false;
					}
					delete response;
				}
				else 
				{
					theApp.menuName=view->menusname.RemoveTail();
					page_no=view->menus.RemoveTail();
					theApp.MenuPointer=view->menupointers.RemoveTail();
					CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);   
					CChildView::LargeWaitingTime=false;
				}
			}
		}
		break;
	default:                
		break;
	}/*End of Inner Switch*/
	return(Exit);
	
}

/***************************************************************************/
/*                                                                         */
/*  This function handles entry of VARIABLE values using the Increase/     */
/*  Decrease keys.  It is called when an Inc or Dec key is pressed at an   */
/*  appropriate time during value entry.  When this function is called,    */
/*  there must be a number displayed on the screen in the appropriate      */
/*  position, and it must be legal to increment or decrement (depending on */
/*  which key was pressed) by at least one unit.                           */
/*                                                                         */
/*  While inside this function, the Inc/Dec keys may be used to adjust the */
/*  value of the variable. 												   */
/*                                                                         */
/*  Parameters:                                                            */
/*                                                                         */
/*    KeyPressed - which key is pressed on the keypad screen               */ 
/*      pDC  - pointer to device context                                  */                                                                    
/*  Note: Due to strange behavior of ENERGY format, it's possible for      */
/*  format type to change while inside this function.                      */
/*                                                                         */
/***************************************************************************/
void CScreenKeypad::VGAVarEntryIncDecMode(int KeyPressed,CDC *pDC)
{
	char   ValueLine[LINESIZE+1] = "                    ";
	SINT32  MinVal, MaxVal, Temp;
	char   TempLine[LINESIZE+1] = "                    ";
	
	if (VarInfo.NewVal != -1)
	{
		if (VarInfo.Sign)  /* For items with sign display, use real range */
		{
			MaxVal = VarInfo.MaxVal;
			MinVal = -VarInfo.MaxVal;
			if (VarInfo.Sign == -1)
				VarInfo.NewVal = -VarInfo.NewVal;
		}
		else
		{
			MaxVal = VarInfo.MaxVal;
			MinVal = VarInfo.MinVal;
		}
		
		Temp = VarInfo.NewVal;
		
		if (KeyPressed == KEYPAD_INC)
		{
			VarInfo.NewVal += VarFormatTable[VarInfo.Format].English.Increment;
			if (VarInfo.NewVal > MaxVal) /* Check for value above maximum*/
				VarInfo.NewVal = MaxVal; 
		}
		else
		{
			VarInfo.NewVal -= VarFormatTable[VarInfo.Format].English.Increment;
			if (VarInfo.NewVal < MinVal) /* Check for value below minimum*/
				VarInfo.NewVal = MinVal;
		}
		
		if (Temp == VarInfo.NewVal)    /* Couldn't change */
			ERRORBEEP;
		else
		{
			/* Miserable kludge: Format of ENERGY items can change */
			/* depending on value.  If over 1000.0J, need to use */
			/* ENERGYDIV10.  Do this by convert to internal, then */
			/* switch formats & convert to external.  Same idea */
			/* going from ENERGYDIV10 to ENERGY. */
			if (VarInfo.Format == ENERGY && VarInfo.NewVal >= 10000)
				ConvertVariableFormat( ENERGY, ENERGYDIV10 );
			
			else if(VarInfo.Format == ENERGYDIV10 && VarInfo.NewVal < 1000)
				ConvertVariableFormat( ENERGYDIV10, ENERGY );
			
			FormatNum(VarInfo.NewVal,ValueLine);
			VarInfo.Value=0;
            SplitString(ValueLine, " ",TempLine);         
			strcat (TempLine, "_");
			strcpy(EditLine,TempLine);
			DrawString(pDC, TempLine);
		}
		if (VarInfo.Sign)            /* If sign displayed, convert back to */
		{                             /* absolute value. */
			if (VarInfo.NewVal < 0)
			{
				VarInfo.NewVal = -VarInfo.NewVal;
				VarInfo.Sign = -1;
			}
			else
				VarInfo.Sign = 1;
		}
	}
}

/***************************************************************************/
/*                                                                         */
/*  Converts the item described by *VarInfo from one "format" to another,  */
/*  by converting to the internal storage units and then to the other      */
/*  format.  MinVal, MaxVal, NewVal, and FormatPtr are affected (but       */
/*  string size is assumed to be the same).  This function is primarily    */
/*  used when an item needs to be converted from ENERGY to ENERGYDIV10 and */
/*  vice versa because the value of the item has become too high or too    */
/*  low.                                                                   */
/*                                                                         */
/***************************************************************************/

void CScreenKeypad::ConvertVariableFormat(enum FORMAT Format1, enum FORMAT Format2)
{
	VarInfo.MinVal = ConvertExternalInternal( VarInfo.MinVal, Format1 );
	VarInfo.MinVal = ConvertInternalExternal( VarInfo.MinVal, Format2);
	VarInfo.NewVal = ConvertExternalInternal( VarInfo.NewVal, Format1 );
	VarInfo.NewVal = ConvertInternalExternal( VarInfo.NewVal, Format2 );
	VarInfo.MaxVal = ConvertExternalInternal( VarInfo.MaxVal, Format1 );
	VarInfo.MaxVal = ConvertInternalExternal( VarInfo.MaxVal, Format2);
	VarInfo.Format = Format2;
}


/****************************************************************************/
/*                                                                          */
/* Converts the value passed in to internal storage units.  Passed number   */
/* is binary form of what was entered or displayed, minus a decimal point.  */
/* Conversion may scale by factors of ten or convert units, but end result '*/
/* is suitable for storage.                                                 */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::ConvertExternalInternal(SINT32 Number, enum FORMAT format)
{ 
	bool Metric=VarInfo.Metric;
	SINT32 RetVal;
	struct var_format_def1 *FormatPtr;
	
	if (Metric)                         /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	
	/* Perform conversion from displayed units to stored units */
	
	if (Number < 0)
		RetVal = 0-((((0-Number) * FormatPtr->ConvDiv) +
		(FormatPtr->ConvMult/2))/(FormatPtr->ConvMult));
	else
		RetVal = ((Number * FormatPtr->ConvDiv) +
		(FormatPtr->ConvMult/2))/(FormatPtr->ConvMult);
	
	return( RetVal );
}


/****************************************************************************/
/*                                                                          */
/* Converts the value passed in, which is in the specified format, into a   */
/* form that can be displayed.  This may involve scaling by factors of ten  */
/* or unit conversions.  The end result is a SINT32 that can be converted  '*/
/* to ASCII and displayed, with a decimal point placed as determined by the */
/* format.                                                                  */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::ConvertInternalExternal(SINT32 Value, enum FORMAT format)
{
	bool Metric=CChildView::metric;//VarInfo.Metric;
	int RetVal;
	struct var_format_def1 *FormatPtr;
	
	if (Metric)//CChildView::metric)                         /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	
	/* Perform conversion from stored units to displayed units */
	
	if (Value < 0)
		RetVal = 0 - ((((0-Value)*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
		FormatPtr->ConvDiv);
	else
		RetVal = ((Value*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
		FormatPtr->ConvDiv;
	
	return( RetVal );
}

/****************************************************************************/
/*Description:-                                                             */
/* A series of calls to this function breaks the input string (Split_str) in*/
/* to sequence of tokens each of which is delimited by the characters in    */
/* second string (Split_Char) and splited token is available in             */
/* 'Splited_Str' string                                                     */
/*Return Value:-                                                            */
/* SINT8 *retPtr : pointer to the string from where next token needs to be  */
/*                Parsed.                                                   */
/****************************************************************************/
void CScreenKeypad::SplitString(char Split_Str[], char Split_Char[], char Splited_Str[])
{	
	unsigned int Index;
	unsigned int Index1;
	bool break_str;
	int count =0;
	bool SkipChar = true;
	
	for (Index=0; Index < strlen(Split_Str); Index++)
	{
		break_str = false;
		for(Index1 =0; Index1 < strlen(Split_Char); Index1++)
		{
			
			if(Split_Str[Index] == Split_Char[Index1] )
			{
				break_str = TRUE;
				break;
			}         
		}
		if(break_str == FALSE) 
		{
			
			Splited_Str[count]= Split_Str[Index];
			count++;
			SkipChar = FALSE;
		}
		else 
		{
			if(SkipChar == FALSE)
			{
				Splited_Str[count] = NUL;				
				break;
			}          
		}
	}
	if(Index == strlen(Split_Str))
	{		
		if(count== 0) Splited_Str[0]=NUL;
		else Splited_Str[count] = NUL;
	}	
}

/****************************************************************************/
/*                                                                          */
/* Converts the given number into an ASCII string showing a variable of the */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* Conversion to displayable units is assumed to have been done.            */
/*                                                                          */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    String[] - Output string                                              */
/*                                                                          */
/****************************************************************************/
void CScreenKeypad::FormatNum(int Number,char String[])
{
	int MaxLen=VarInfo.Size;
	bool Metric=VarInfo.Metric;
	UINT8 ChrCount, Digits;
	char *cptr;
	char SignChr;
	struct var_format_def1 *FormatPtr;
	
	if (Metric)                         /* Point to format info */
		FormatPtr = &VarFormatTable[ VarInfo.Format].Metric;
	else
		FormatPtr = &VarFormatTable[ VarInfo.Format].English;
	
	if (Number < 0)
	{
		Number = -Number;
		SignChr = '-';
	}
	else
		SignChr = '+';
	
	cptr = String;
	for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
		*cptr++ = ' ';
	
	cptr = &String[MaxLen-1];      /* Point to last chr in string */
	ChrCount = MaxLen;     /* Should already have this, but do anyway */
	Digits = FormatPtr->RightDigits;
	if (Digits)          /* If necessary, write digits to right of decimal */
	{
		while (ChrCount && Digits)
		{
			*cptr-- = (Number%10) + '0';
			Number /= 10;
			ChrCount--;
			Digits--;
		}
		if (ChrCount)
		{
			*cptr-- = '.';
			ChrCount--;
		}
	}
	if (ChrCount)     /* Write left part if space in string */
	{
		//Digits = VarFormatTable[VarInfo.Format].English.LeftDigits; /* Max # of digits to write this step */
		Digits = FormatPtr->LeftDigits;
		if (Digits > ChrCount)  /* Don't write more than there's space for */
			Digits = ChrCount;
		if (Number)
		{
			while (Digits && Number)
			{
				*cptr-- = (Number%10) + '0';
				Number /= 10;
				Digits--;
				ChrCount--;
			}
		}
		else
		{
			*cptr-- = '0';   /* Always one chr left of decimal point */
			ChrCount--;
		}
	}
	if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
		*cptr = SignChr;     /* Add sign */
}

CString CScreenKeypad::FormatNumber(int Number,char String[],enum FORMAT format,bool ChkUnitflag,bool Insertunitflag1)
{
	bool Metric=CChildView::metric;//VarInfo.Metric;
	UINT8 ChrCount, Digits;
	char *cptr;
	char *UnitText;
	char SignChr;
	struct var_format_def1 *FormatPtr;
	
	if (Metric)                         /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	
	int RetVal = FormatPtr->RightDigits;
	
	if (RetVal)
		RetVal += 1;
	
	if (FormatPtr->ShowSign)   /* Count sign if display always forced */
		RetVal += 1;
	
	RetVal += FormatPtr->LeftDigits;
	int MaxLen=RetVal;
	if (Number < 0)
	{
		Number = -Number;
		SignChr = '-';
	}
	else
		SignChr = '+';
	
	UnitText=FormatPtr->Units ;
	cptr = String;
	for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
		*cptr++ = ' ';
	
	cptr = &String[MaxLen-1];      /* Point to last chr in string */
	ChrCount = MaxLen;     /* Should already have this, but do anyway */
	Digits = FormatPtr->RightDigits;
	if (Digits)          /* If necessary, write digits to right of decimal */
	{
		while (ChrCount && Digits)
		{
			*cptr-- = (Number%10) + '0';
			Number /= 10;
			ChrCount--;
			Digits--;
		}
		if (ChrCount)
		{
			*cptr-- = '.';
			ChrCount--;
		}
	}
	if (ChrCount)     /* Write left part if space in string */
	{
		//Digits = VarFormatTable[VarInfo.Format].English.LeftDigits; /* Max # of digits to write this step */
		Digits = FormatPtr->LeftDigits;
		if (Digits > ChrCount)  /* Don't write more than there's space for */
			Digits = ChrCount;
		if (Number)
		{
			while (Digits && Number)
			{
				*cptr-- = (Number%10) + '0';
				Number /= 10;
				Digits--;
				ChrCount--;
			}
		}
		else
		{
			*cptr-- = '0';   /* Always one chr left of decimal point */
			ChrCount--;
		}		
	}		
	if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
		*cptr = SignChr;     /* Add sign */
	CString str=String;
	str.TrimLeft ();
	str.TrimRight ();
	if(ChkUnitflag)
	{
		CString temp=UnitText;
		temp.TrimLeft ();
		temp.TrimRight ();
		str+=temp;
	}
	return str;
}

bool CScreenKeypad::InsertProperUnits(CVgaMenuItem *ptr,enum FORMAT format,int type)
{
	CVgaVariable *pointer1;
	CRadioMenu *pointer2;
	CString str;
	if(type==CVgaMenu::VARIABLE)
	{
		pointer1=(CVgaVariable *)ptr;
		str=pointer1->text;
	}
	else
	{
		pointer2=(CRadioMenu *)ptr;
		str=pointer2->text;
	}	
	
	struct var_format_def1 *FormatPtr;
	char *UnitText;
	if (CChildView::metric)                 /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	int Index=0;
	
	while (str.GetAt(Index) && (str.GetAt(Index) != '('))
		Index++;
	UnitText = FormatPtr->Units;
	bool Flag;
	
	if(type==CVgaMenu::VARIABLE)
		Flag=pointer1->Insertunitflag;
	else
		Flag=pointer2->Insertunitflag;
	
	if(!Flag)
	{
		if ((str.GetAt(Index) == '('))
		{
			// printf("\n str.GetAt(Index) == '&'");
			Index++;
			for (int ChrCount=0; (ChrCount < 4) && (str.GetAt(Index) != ')'); ChrCount++)
				str.SetAt(Index++,*UnitText++);
			
			if(type==CVgaMenu::VARIABLE)
				pointer1->text=str;
			else
				pointer2->text=str;
			return true;
		}		
	}
	else
		return false;
	return false;
}

CString CScreenKeypad::InsertWeldParamUnit(CString string,enum FORMAT format)
{
	struct var_format_def1 *FormatPtr;
	char *UnitText;
	if (CChildView::metric)                 /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	int Index=0;
	
	while (string.GetAt(Index) && (string.GetAt(Index) != '&'))
		Index++;
	UnitText = FormatPtr->Units;
	if ((string.GetAt(Index) == '&'))
	{
		for (int ChrCount=0; (ChrCount < 4) && (string.GetAt(Index) == '&'); ChrCount++)
			string.SetAt(Index++,*UnitText++);
	}
	return string;
}

CString CScreenKeypad::InsertWeldParamUnitsString(bool metric,enum FORMAT format)
{
	struct var_format_def1 *FormatPtr;
	char *UnitText;
	if (metric)                 /* Point to format info */
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	UnitText = FormatPtr->Units;
	return UnitText;
}

void CScreenKeypad::DrawString(CDC *pDC, char string[], bool BigRect)
{
	CVgaMenuItem::DrawRect(pDC, White,  New_Value_Rect(CScreenKeypad::type));
	CRect r;
	if(BigRect)
		r = SINGLE_TEXT_BOX_RECT;
	else
	    r = New_Value_Rect(CScreenKeypad::type);
	r.OffsetRect(XOFFSET, YOFFSET);
	CFont KeypadFont;
	KeypadFont.CreateFont(20 , 8, 0, 0, FW_NORMAL,//FW_ULTRALIGHT,
		FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, FF_DONTCARE,_T("Arial"));
	CFont *OldFont=pDC->SelectObject(&KeypadFont);
	pDC->SetTextColor(Black);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(string,r,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
	pDC->SelectObject(OldFont);
	KeypadFont.DeleteObject();
}

/***************************************************************************/
/*  This function will display the passed error code on the keypad screen  */
/*  Three errors messages are displayed                                    */
/*    Value below minimum                                                  */
/*    Value above Maximum                                                  */
/*    No value entered                                                     */
/*                                                                         */
/* Parameters:                                                             */
/*   Ecode - Error code for the type of error to be displayed              */
/*   *pDC  -   Pointer to the device context object                        */   
/***************************************************************************/
void CScreenKeypad::DisplayVGAMinMaxError(enum ERRORCODES ECode,CDC *pDC)
{
	CChildView::ErrorBeep();
	
	char ValueBuffer[LINESIZE+1];
	SINT32 MaxVal, MinVal;
	if (VarInfo.Sign == -1)
	{
		MaxVal = -VarInfo.MinVal;
		MinVal = -VarInfo.MaxVal;
	}
	else
	{
		MaxVal = VarInfo.MaxVal;
		MinVal = VarInfo.MinVal;
	}
	if(type == VGA_PASSWORD)
		CVgaMenuItem::DrawRect(pDC,Red, PassWordError_Str_rect);
	else
		CVgaMenuItem::DrawRect(pDC,Red, Error_rect);	
	CString TempTextME1=StrME_1,TempTextME2=StrME_2,TempTextME3=StrME_3,
		TempPassIncorrect=StrPassIncorrect;
	if(CChildView::thisPtr->StringDebugFlag)
	{
		TempTextME1=StrME_1ID + _T(" ") + StrME_1;
		TempTextME2=StrME_2ID + _T(" ") + StrME_2;
		TempTextME3=StrME_3ID + _T(" ") + StrME_3;
		TempPassIncorrect = StrPassIncorrectID + _T(" ") + StrPassIncorrect;
	}
	switch (ECode)
	{
	case MINRANGE:                 /* Value entered is below minimum */
		CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,
			TempTextME1,true);/* Minimum Value string */
		break;
		
	case MAXRANGE:                 /* Value entered is above maximum */
		CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,
			TempTextME2,true);
		break;
		
	case NOVALUE:
		if(type == VGA_PASSWORD)
			CVgaMenuItem::DrawText(pDC, SmallFont, White,PassWordError_Str_rect, 
			TempTextME3,true);
		else
			CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect, 
			TempTextME3,true);
		break;
	case PassInvalid:
		
		CChildView::IsTwoSecExpired=true;
		CChildView::KillTimers(ALPHAENTRYTIMER);
		CVgaMenuItem::DrawText(pDC, SmallFont, White,PassWordError_Str_rect, TempPassIncorrect,true);
		//CChildView::thisPtr->Invalidate();
		break;
		
	default:
		CVgaMenuItem::DrawText(pDC, SmallFont, White,Error_Str_rect,"                    " 
			,true);
			break;
	}
	if(type != VGA_PASSWORD)
	{
		FormatNum(VarInfo.MinVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get minimum value */
		CString MinValueString =StrME_4;//[CChildView::Language_Index];
		if(CChildView::thisPtr->StringDebugFlag)
		{
			MinValueString = StrME_4ID + _T(" ") + StrME_4;
		}
		
		for(int i=(LINESIZE-VarInfo.Size);i<(LINESIZE);i++)
			MinValueString+=ValueBuffer[i];
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Min_Value_Str_rect,
			MinValueString,false);
		FormatNum(VarInfo.MaxVal, &ValueBuffer[LINESIZE-VarInfo.Size]); /* Get maximum value */
		CString MaxValueString =StrME_5;//[CChildView::Language_Index];
		if(CChildView::thisPtr->StringDebugFlag)
		{
			MaxValueString = StrME_5ID + _T(" ") + StrME_5;
		}
		for(int j=(LINESIZE-VarInfo.Size);j<(LINESIZE);j++)
			MaxValueString+=ValueBuffer[j];
		CVgaMenuItem::DrawText(pDC, SmallFont, White, Max_Value_Str_rect, 
			MaxValueString,false);
	}
	ERRORBEEP;
}


/***************************************************************************/
/*  This function will display the Min:/Max Value on the keypad screen     */
/*                                                                         */
/* Parameters:                                                             */
/*   Varinfo - Pointer to various context information of a variable entry  */   
/***************************************************************************/
void CScreenKeypad::DisplayVGAMinMax(CDC *pDC)
{
	char ValueBuffer[LINESIZE+1];
	SINT32 MaxVal, MinVal;
	if (VarInfo.Sign == -1)
	{
		MaxVal = -VarInfo.MinVal;
		MinVal = -VarInfo.MaxVal;
	}
	else
	{
		MaxVal = VarInfo.MaxVal;
		MinVal = VarInfo.MinVal;
	}
	FormatNum(VarInfo.MinVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get minimum value */
	
	CString MinValueString =StrME_4;//[CChildView::Language_Index];
	if(CChildView::thisPtr->StringDebugFlag)
	{
		MinValueString = StrME_4ID + _T(" ") + StrME_4;
	}
	
	for(int i=(LINESIZE-VarInfo.Size);i<(LINESIZE);i++)
		MinValueString+=ValueBuffer[i];
	
	
	CVgaMenuItem::DrawText(pDC, SmallFont, White, Min_Value_Str_rect,
		MinValueString,false);
	FormatNum(VarInfo.MaxVal,&ValueBuffer[LINESIZE-VarInfo.Size]); /* Get maximum value */
	CString MaxValueString =StrME_5;//[CChildView::Language_Index];
	if(CChildView::thisPtr->StringDebugFlag)
	{
		MaxValueString = StrME_5ID + _T(" ") + StrME_5;
	}
	for(int j=(LINESIZE-VarInfo.Size);j<(LINESIZE);j++)
		MaxValueString+=ValueBuffer[j];
	CVgaMenuItem::DrawText(pDC, SmallFont, White, Max_Value_Str_rect,
		MaxValueString,false);
}

/****************************************************************************/
/*                                                                          */
/* Returns the maximum # of characters that should be allocated to display  */
/* a value in the given format.  If the # of characters to the right of the */
/* decimal point is nonzero, a character is added to allow space for the '.'*/
/* Note that space is not provided for a sign character (+ or -) unless     */
/* the format always includes a sign.                                       */
/*                                                                          */
/****************************************************************************/
int CScreenKeypad::VarSize(enum FORMAT format)
	
{
	UINT8 RetVal;
	struct var_format_def1 *FormatPtr;
	
	if (VarInfo.Metric)
		FormatPtr = &VarFormatTable[format].Metric;
	else
		FormatPtr = &VarFormatTable[format].English;
	
	RetVal = FormatPtr->RightDigits;
	
	if (RetVal)
		RetVal += 1;
	
	if (FormatPtr->ShowSign)   /* Count sign if display always forced */
		RetVal += 1;
	
	RetVal += FormatPtr->LeftDigits;
	return( RetVal );
}

int CScreenKeypad::GetInteger(unsigned char *&data, int bytes)
{
	if(bytes == 2)
	{
		union {
			int i;
			unsigned char c[INTEGERLENGTH];
		} u;
		u.c[0]=0;
		u.c[1]=0;
		for (int i = 2; i < INTEGERLENGTH; i++)
		{
			unsigned char x=*data++;
			u.c[i] = x;
		}
		return ntohl(u.i);
	}
	else
	{
		union {
			int i;
			char c[INTEGERLENGTH];
		} u;
		for (int i = 0; i < INTEGERLENGTH; i++)
			u.c[i] = *data++;
		return ntohl(u.i);
	}
}

/***************************************************************************/
/*                                                                         */
/*  Displays the number whose information is provided in Current and New   */
/*  value rectangle.                                                       */
/*                                                                         */
/*  Parameters                                                             */
/*  VarInfo - Pointer to various context information of a variable entry   */ 
/*                                                                         */
/***************************************************************************/

void CScreenKeypad::VGADisplayCurrentNewValue(CDC *pDC)
{
	char ValueLine[LINESIZE+1] = "                    "; /* 20 spaces */
	SINT32 NewVal;
	if (VarInfo.Sign == -1)
		NewVal = -VarInfo.NewVal;
	else
		NewVal = VarInfo.NewVal;
	
	FormatNum( NewVal,  ValueLine);
	CVgaMenuItem::DrawRect(pDC,White,  New_Value_Rect(type));///new value rect
	if((TotalDigits==0)&&(FirstKeyPress != KEY_INC_DEC ))
	{
		strcpy(ValueLine, "_");   
		CVgaMenuItem::DrawText(pDC, SmallFont, Black, 
			New_Value_Rect(type),ValueLine ,false);
	}
	else
		DrawString(pDC, EditLine);
	if (VarInfo.Disable)
		VarInfo.Disableflag &= ~(VarInfo.Bitmask);
} /*End of function*/


void CScreenKeypad::CopyString(char *dest, char *source)
{
	for(int i=0;i<LINESIZE;i++)
		*(dest++)=*(source++);
	*(++dest)='\0';
}



/***************************************************************************/
/*                                                                         */
/*   Handle Enter on Password Keypad screen.Check if no value enter,Check  */
/*   for both password (entered and confirm password) will be same.        */
/***************************************************************************/
void CScreenKeypad::HandleEnterOnPassword(CChildView *view, CDC *pDC)
{
	printf("in HandleEnterOnPassword() ");
	if(AlphaBuf[0] ==NULL)
	{
		DisplayVGAMinMaxError(NOVALUE,pDC); 
		ErrorDisplayed = TRUE;
	}
	else if(pointer==0)//password entered for first time to set password.
	{
		SendCommandForPassword(view,SetValue_FunID,pDC);
		ErrorDisplayed = TRUE;
	}
	
	else if(pointer ==1)//second time password entered to confirm the set password.
	{
		if(TempPassword == AlphaBuf)//password matched.
			SendCommandForPassword(view,SetValue_FunID,pDC);//ErrorDisplayed = TRUE;
		else
		{
			DisplayVGAMinMaxError(PassInvalid,pDC); 
			ErrorDisplayed = TRUE;InitializedValues();
		}
	}
	else if((pointer !=1)&&(pointer !=0))//password entered for secure menus.
		SendCommandForPassword(view,SetValue_FunID,pDC);
}


/****************************************************************************/
/*                                                                          */
/*   Send Hostcommand for password entered and show appropriate screens		*/
/*   according to the response.											    */
/****************************************************************************/
void CScreenKeypad::SendCommandForPassword(CChildView *view,int FunID,CDC *pDC)
{
	unsigned char data[26];
	int length_pass=0;
	int t=0;
	bool VelocityOn=false,TempFlagDebugOn=false,TempFlagDebugOff=false;
	while(AlphaBuf[length_pass]!='\0')//Getting Length of password.
		length_pass++;

	union 
		{
			short i;
			char c[2];
		} u;
		u.i=ID_type;
		data[1]=u.c[0];
		data[0]=u.c[1];
		data[2]=(char)length_pass+1;
		if(pointer==0)//Enter Password Keypad Screen.
			data[3]=(char)01;
		else if(pointer==1)//Confirm Password Keypad Screen.
			data[3]=(char)02;
		else
			data[3]=(char)00;//Branson Menu & protected menu.
		for(int J=0;J<length_pass;J++)
			data[4+J]=AlphaBuf[J];
		length_pass = length_pass+4;
		
		
		char PasswordAed[]="534922868726";
		char PasswordAef[]="634922868726";
		char PassConfigAEFSBeam[]="266344672326";
		char PassConfigAEDSBeam[]="266344572326";
		char PassConfigMICROSbeam[]="266344772326";
		char PassConfigAESSbeam[]="266344772325";
		
		int temp=length_pass-4;
		if(temp == 12)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PasswordAed[t])||(AlphaBuf[t]==PasswordAef[t])
					||(AlphaBuf[t]==PassConfigAEFSBeam[t])||(AlphaBuf[t]==PassConfigAEDSBeam[t])||
					(AlphaBuf[t]==PassConfigMICROSbeam[t])||(AlphaBuf[t]==PassConfigAESSbeam[t]))
					match++;
			}
			if(match==temp)
			{
				//   printf("\n match");
				CChildView::LargeWaitingTime=true;	
				CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
				CVgaMenuItem::DrawRect(pDC, Black, CRect(119,119,521,361));
				CVgaMenuItem::DrawRect(pDC, Blue,MessageRect  );
				CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
					PleaseWait,true);
				CChildView::InitialiseTimer(PASSWORDTIMER,MESSAGESCRNTIME);
			}
			
		}
		
		char PassConfigMicroSpecial[]="101134290";
		char PassConfigMicroOriginal[]="159134348";
		
		temp=length_pass-4;
		if(temp == 9)
		{
			int match=0;
			for(int t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PassConfigMicroSpecial[t])
					||(AlphaBuf[t]==PassConfigMicroOriginal[t]))
					match++;
			}
			if(match==temp)
			{
				//   printf("\n match");
				CChildView::LargeWaitingTime=true;			
			}
			
		}
		
		char PasswordVelocityOn[]="6060099456";
		char PasswordVelocityOff[]="6030399654";
		int templen=length_pass-4;
		if(templen == 10)
		{
			int match=0;
			for(t=0;t<temp;t++)
			{
				if((AlphaBuf[t]==PasswordVelocityOn[t])||(AlphaBuf[t]==PasswordVelocityOff[t]))
					match++;
			}
			if(match==templen)
			{
				VelocityOn=true;			
			}
			
		}
		
		char PasswordStringDebugOn[]="101";
		char PasswordStringDebugOff[]="102";
		templen=length_pass-4;
		if(templen == 3)
		{
			int match=0;
			for( t=0;t<temp;t++)
			{
				if(AlphaBuf[t]==PasswordStringDebugOn[t])
					match++;
			}
			if(match==templen)
			{
				TempFlagDebugOn=true;			
			}
			match=0;
			for( t=0;t<temp;t++)
			{
				if(AlphaBuf[t]==PasswordStringDebugOff[t])
					match++;
			}
			if(match==templen)
			{
				TempFlagDebugOff=true;			
			}
			
		}
	
	for(int q=0;q<length_pass;q++)
		TRACE(_T("data is ********%d"),data[q]);
	unsigned char * pass_data = (unsigned char *) &data[0];
	Index=-1;
	CChildView::LargeWaitingTime = true;
	CHostCommand * request = new CHostCommand(FunID, pass_data, length_pass);
	CHostCommand * response = app->SendUiHostCommand(request);
	if (response)
	{
		pass_data = response->GetData();//Getting Data.
		int length = response->GetDataLength();//Getting Length.
		//		printf("\n length in receieve=%d",length);
		char ch=CHostCommand::AckNak();
		if(ch==ACK)
		{
			//		printf("\n Ack in password");
			OnKeypadScreen_flag=false;
			ErrorDisplayed = false;
			if(length>0)
			{
				//   printf("\n length>0");
				IsPassword_Accepted = *pass_data++;length--;
				//            printf("\n IsPassword_Accepted=%d",IsPassword_Accepted);
				CString MessageString,Temprory;
				//char TempArray1[10];
				if(IsPassword_Accepted==1)
				{
					
					MessageString=CChildView::thisPtr->Str_PassAccp;
					if(PassWordMenu!="")
					{
						CVgaMenu * menu;
						theApp.menuName = PassWordMenu;
						if(PassWordMenu != CVgaBottomMenu::WeldResults_ID)
							CChildView::RunResultScreen=false;
						
						if (theApp.menus.Lookup(theApp.menuName, menu))
						{
							theApp.MenuPointer=menu;
						}
					}
				}
				else if(IsPassword_Accepted==2)
				{
					
					MessageString=CChildView::thisPtr->Str_PassRej;
				}
				else if(IsPassword_Accepted==3)
				{
					
					MessageString=CChildView::thisPtr->Str_Secret;
				}
				switch(IsPassword_Accepted)
				{
				case 1:
				case 2:
					{
						CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
						CVgaMenuItem::DrawRect(pDC, Black, CRect(119,119,521,361));
						CVgaMenuItem::DrawRect(pDC, Blue,MessageRect  );
						CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
							MessageString,true);
						view->DisableFlag = true;
						ErrorDisplayed = true;
						// view->Invalidate ();
						CChildView::InitialiseTimer(PASSWORDTIMER,MESSAGESCRNTIME);
					}
					break;
				case 3:
					{
						CVgaMenuItem::DrawRect(pDC, CChildView::Back_Color, CRect(0,40,640,440));
						CVgaMenuItem::DrawRect(pDC, Black, CRect(119,119,521,361));
						CVgaMenuItem::DrawRect(pDC, Blue,MessageRect  );
						CVgaMenuItem::DrawText(pDC, Bigfont, White, MessageRect,
							MessageString,true);
						view->DisableFlag = true;
						ErrorDisplayed = true;
						// view->Invalidate ();
						theApp.GetSystemVariable();
						view->ModifyObjectList(theApp.MenuPointer);
						CChildView::InitialiseTimer(ERROR_MESSAGE_TIMER,MESSAGESCRNTIME);
					}
					break;
				case 4:
					{
						int ID=CVgaMenuItem::Convert_Char_To_Integer(pass_data,length,2);
						//printf("\n Id in case4=%d",ID);
						char TempArray[10];
						CString Temp=_itoa(ID,TempArray,10);
						CVgaMenu * menu;
						if (theApp.menus.Lookup(Temp, menu))
						{
							view->menusname.AddTail(theApp.menuName);
							view->menus.AddTail(page_no);
							view->menupointers.AddTail(theApp.MenuPointer);
							page_no=1;
							theApp.GetSystemVariable();
							view->ModifyObjectList(menu);   
							theApp.menuName = Temp;
							theApp.MenuPointer=menu;
							view->Invalidate();
						}	
					}
					break;
				}
				
				while (view->keypadList.GetCount())
					delete view->keypadList.RemoveHead();				
			}			
		}
		else	//nak
			view->ProcessNak(pass_data,length,pointer,ID_type);
		delete response;
	}
	if((CChildView::LargeWaitingTime==true)||(VelocityOn==true))
	{
		theApp.GetSystemVariable();
		view->GetWeldDataIdArray(true);
		view->GetGraphWeldDataIdArray(true);
	}
	else 
	{
		if(TempFlagDebugOn)
			CChildView::thisPtr->StringDebugFlag=true;
		else if(TempFlagDebugOff)
			CChildView::thisPtr->StringDebugFlag=false;
	}	
	CChildView::LargeWaitingTime=false;
}

/*******************************************************/
/*                                                     */
/*   Initialized all the variables for Keypad screen.  */
/*   .											       */
/*******************************************************/
void CScreenKeypad::InitializedValues()
{
	for(int len=0;len<(LINESIZE+1);len++)
		AlphaBuf[len] = NULL;
	
	TotalDigits=0;
	EditLine[LINESIZE-1] = 0;
	TypedVal = 0;
	DPFlag = FALSE;
	DecimalCount = 0;
	DigitCounter = 0;
	TotalDigits = 0;
	MaxDigitFlag = FALSE;
	EditLine[0]='\0';
	FIRSTKEYPRESS FirstKeyPress = CScreenKeypad::KEY_NONE;	
	PrevPressedAlphaNumKey=CScreenKeypad::KEYPAD_NONE;
	Index=0;             
	MaxDigit=0;     
	KeyCount=0;          
	EntryFlag=false; 
}

/************************************************************************/
/* This function will handle Enter pressed by user on SaveScanKeypad.   */
/* Function will store the ID of scan graph to text file.				*/
/************************************************************************/
void CScreenKeypad::HandleEnterOnSaveScanKeypad(CChildView *view, CDC *pDC)
{		
	CFile f;
	CFileException e;
	CString Path = DISK;
	switch(type)
	{
	case SaveScanA:
		{
			Path = Path + "HornScanA.txt";
		}
		break;
	case SaveScanB:
		{
			Path = Path + "HornScanB.txt";
		}
		break;
	case SaveScanC:
		{
			Path = Path + "HornScanC.txt";
		}
		break;
	}
	if( !f.Open( Path,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
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
		int length =2;
		unsigned char data1[2];
		data1[0]=(char)ID_type;//HornScan_RequestValue;
		data1[1]=(char)0;
		unsigned char * data = (unsigned char *) &data1[0];
		
		CHostCommand * request = new CHostCommand(GetWeldData_FunID/*GetWeldResults_FunId*/, data, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			data = response->GetData();//Getting Data.
			length = response->GetDataLength();//Getting Length.
			if(ch==ACK)//If Ack.
			{		
				unsigned char *c =new unsigned char[length];
				unsigned char * alpha_data ;
				int length_alpha=0;
				while(AlphaBuf[length_alpha]!='\0')
					length_alpha++;
				alpha_data =new unsigned char[length_alpha+4];
				//	alpha_data[0]=(unsigned char)CChildView::Language_Index;
				/*alpha_data[1]*/alpha_data[0]=(unsigned char)length_alpha;
				for(int J=1/*2*/;J<=length_alpha+1;J++)
					alpha_data[J]=(unsigned char)AlphaBuf[J-1/*2*/];
				alpha_data[length_alpha+1/*2*/]='\0';
				
				for(int i=0;i<length;i++)
					c[i]=*data++;
				f.Write(alpha_data,length_alpha+1/*2*/);
				LONG IDLength =length_alpha+1/*2*/;
				f.Seek(IDLength, CFile::begin );
				f.Write(c,length);
				delete []c;delete []alpha_data;
			}
         delete response;
		}
		f.Close();
	}
	view->Invalidate();
}


void CScreenKeypad::SetVariableStrings(CXmlElement * e)
{
	POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		CString Temp=element->GetAttribute("stringId");
		if (tag == "variable1")
		{
			StrME_4ID=Temp;
			StrME_4=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable2")
		{
			StrME_5ID=Temp;
			StrME_5=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable3")
		{
			StrME_1ID=Temp;
			StrME_1=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable4")
		{
			StrME_2ID=Temp;
			StrME_2=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable5")
		{
			StrME_3ID=Temp;
			StrME_3=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable6")
		{
			Str_ReenterID=Temp;
			Str_Reenter=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable7")
			CChildView::thisPtr->StrPage=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable8")
		{
			StrPassTitleID=Temp;
			StrPassTitle=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable9")
		{
			StrEnterPassID=Temp;
			StrEnterPass=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable10")
		{
			StrConfirmPassID=Temp;
			StrConfirmPass=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable11")
			CChildView::thisPtr->CycleCountString=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable12")
		{
			StrPassIncorrectID=Temp;
			StrPassIncorrect=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable13")
		{
			HornTitleID=Temp;
			CChildView::thisPtr->Str_HornId=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable14")
		{
			Str_OffID=Temp;
			Str_Off=CVgaMenuItem ::LinearSearch(Temp);
		}
		else if(tag=="variable15")
			CChildView::thisPtr->PrinterPower_str_Online=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable16")
			CChildView::thisPtr->PrinterPower_str_Offline=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable17")
			CChildView::thisPtr->Str_Save=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable18")
			CChildView::thisPtr->Str_Exit=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable19")
			CChildView::thisPtr->Str_PassAccp=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable20")
			CChildView::thisPtr->Str_PassRej=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable21")
			CChildView::thisPtr->Str_Secret=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable22")
			CChildView::thisPtr->Str_Parallel=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable23")
			CChildView::thisPtr->Str_Series=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable24")
			CChildView::thisPtr->Str_PMCGraphs=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable25")
			CChildView::thisPtr->StrCurrent=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable26")
			CChildView::thisPtr->Str_PwrAvg=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable27")
			CChildView::thisPtr->Str_PMCWeld=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable28")
			CChildView::thisPtr->Str_PMCCycles=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable29")
			CChildView::thisPtr->Str_NoValidGraph=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable30")
			CChildView::thisPtr->Str_Frequency=CVgaMenuItem ::LinearSearch(Temp);
		else if(tag=="variable31")
			CChildView::thisPtr->Str_DigitalTuneSett=CVgaMenuItem ::LinearSearch(Temp);
		else
			ASSERT(FALSE);
	}
}

void USBForceSampleGraph(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBForceGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBForceGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBForceGraph.USBSampleValue	=VarInfo.NewVal;
		USBForceGraph.USBSampleDisable	=false;		
	}
}

void USBColDistanceGraph(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBColDistance.USBSampleDisable	=true;//value is dissabled
	else
	{
		USBColDistance.BaseCount=CChildView::thisPtr->UniversalCount;
		USBColDistance.USBSampleValue	=VarInfo.NewVal;
		USBColDistance.USBSampleDisable	=false;		
	}
}

void USBAmplitudeGraphSample(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBAmplitudeGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBAmplitudeGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBAmplitudeGraph.USBSampleValue=VarInfo.NewVal;
		USBAmplitudeGraph.USBSampleDisable=false;		
	}
}

void USBPowerGraphSample(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBPowerGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBPowerGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBPowerGraph.USBSampleValue=VarInfo.NewVal;
		USBPowerGraph.USBSampleDisable=false;
	}
}

void USBVelocityGraphSample(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBVelocityGraph.USBSampleDisable=true;//value is dissabled
	else
	{
		USBVelocityGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBVelocityGraph.USBSampleValue	=VarInfo.NewVal;
		USBVelocityGraph.USBSampleDisable=false;		
	}
}

void USBFrequencyGraphSample(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBFrequencyGraph.USBSampleDisable=true;//	value is dissabled
	else
	{
		USBFrequencyGraph.BaseCount=CChildView::thisPtr->UniversalCount;
		USBFrequencyGraph.USBSampleValue=VarInfo.NewVal;
		USBFrequencyGraph.USBSampleDisable	=false;		
	}
}

void USBWeldData(int Address)
{
	CScreenKeypad *ptr=(CScreenKeypad*)Address;
	if(ptr->KeyOffFlag)
		USBWelddata.USBSampleDisable=true;//	value is dissabled
	else
	{					
		USBWelddata.BaseCount=CChildView::thisPtr->UniversalCount+1-VarInfo.NewVal;
		USBWelddata.USBSampleValue=VarInfo.NewVal;
		USBWelddata.USBSampleDisable=false;		
	}
}

void ModifyPowerSupplyName(int Address)
{
	CChildView::thisPtr->GetPowerSupplyName();
}

void SendVQSLimitQualityCommand(int Address)
{
	CScreenKeypad::Qualityflag=true;
	CChildView::thisPtr->MaxPreset=1;
}

void ProcessDebugMenuScreen(int Address)
{
	CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
	CChildView::thisPtr->menusname.AddTail(theApp.menuName);
	CChildView::thisPtr->menus.AddTail(page_no);
}

void StoreIdleLogoutTime(int Address)
{
	if(VarInfo.NewVal > 0)
		CChildView::thisPtr->IdleLogoutTime = (VarInfo.NewVal * 60 * 1000);//convert entered value in millisecond	
}

void LookforBarcodeScan(int Address)
{
    CChildView::RunResultScreen=true;//Fix for the issue where On exit from column setup screen run result screen was not refeshing
    CVgaButton *ptr = (CVgaButton *)Address;	
	if((GlobalScanString.GetLength() > 0)  && (GlobalScanString.GetAt(0) != CChildView::thisPtr->PresetBarCodeStart.GetAt(0)))
	{		
	    ptr->text= GlobalScanString;		
	}
	else if(UdiStatus == UDISCAN_WAITING)
      ptr->text= WaitForUDIScan; 
	else
		ptr->text="";
}