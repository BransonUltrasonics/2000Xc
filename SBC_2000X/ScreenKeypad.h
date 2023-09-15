/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ScreenKeypad.h_v   1.14   08 Apr 2015 13:08:42   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ScreenKeypad.h_v  $
 * 
 *    Rev 1.14   08 Apr 2015 13:08:42   AnPawar
 * MaxInputDigits variable added to restrict max input digits in variable entery field.
 * 
 *    Rev 1.13   28 Nov 2014 08:31:32   rjamloki
 * Added space bar support
 * 
 *    Rev 1.12   11 Sep 2014 09:48:28   rjamloki
 *  Event Reason keypad related changes
 * 
 *    Rev 1.11   02 Sep 2014 03:32:02   rjamloki
 * Added DisabledChars to keep not allowed keys on alpha keypad
 * 
 *    Rev 1.10   18 Aug 2014 07:49:12   rjamloki
 * Removed redundant Str_New_Ptr
 * 
 *    Rev 1.9   28 Jul 2014 14:11:56   rjamloki
 *  added function  void LookforBarcodeScan(int Address);
 * 
 *    Rev 1.8   09 Jul 2014 08:16:40   akaushal
 * Changes for full keyboard.
 * 
 *    Rev 1.7   09 Jun 2014 11:52:46   rjamloki
 * function declaration changed in  CScreenKeypad  class
 * 
 *    Rev 1.6   07 May 2014 13:09:20   akaushal
 * Array size changed.
 * 
 *    Rev 1.5   21 Apr 2014 13:44:04   akaushal
 * Added variables to change password. 
 * 
 *    Rev 1.4   28 Mar 2014 14:33:10   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:32 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:24 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:36 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:00 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_SCREENKEYPAD_H__8177D0BE_80C4_484F_A575_4D65FB2CFCBF__INCLUDED_)
#define AFX_SCREENKEYPAD_H__8177D0BE_80C4_484F_A575_4D65FB2CFCBF__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChildView;
#define ALPHAKEYPAD 8 // match it with MenuType enum in vgaMenu.h
#define TOTAL_KEYPAD_COLOUMN(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(10):(3))


#define TOTAL_KEYPAD_ROW		5
#define DAYCHAR			2
#define LEAPYEARVALUE	29
#define MAXTIMECHAR		5
#define MAXDATECHAR		8
#define NUL             0x00
#define LINESIZE        20
#define MinLimit_Year   0                     
#define MinLimit_Month  1                   
#define MinLimit_Day    1                    
#define MinLimit_Hour   0                     
#define MinLimit_Minute 0   
#define MaxLimit_Year   99                      
#define MaxLimit_Month  12                                                   
#define MaxLimit_Day    31                                                     
#define MaxLimit_Hour   23                                                    
#define MaxLimit_Minute 59  
#define CENTURY         2000  
#define NULL_PTR        0L  
#define MAX_ALPHA_BUFF  51

#define Boundry_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(24,49,631,431)):(CRect(104,48,542,424)))

#define Bounding_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(25, 50,630,430)):(CRect(105, 49,541,423)))				

#define Current_Value_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(40,100,290,136)):(CRect(118,100,294,136)))					

#define New_Value_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(350,100,600,136)):(CRect(118,180,294,216)))					

#define Keypad_Title_Rect			CRect(100, 48,536, 65)

#define Current_Value_String_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(40, 75,290,100)):(CRect(118, 75,294,100)))				

#define New_Value_String_Rect(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(CRect(350,75,600,100)):(CRect(118,155,235,180)))

#define SINGLE_TEXT_BOX_RECT		CRect(40,100,600,136)
#define Button_Off_Rect				CRect(176,354,234,412)
#define Error_rect					CRect(104,232,320,350)
#define Error_Str_rect				CRect(104,232,320,271)
#define PassWordError_Str_rect		CRect(40,75,275,130)
#define Min_Value_Str_rect			CRect(120,271,320,310)
#define Max_Value_Str_rect			CRect(120,310,320,350)
#define OFF_Rect					CRect(176,354,234,412)
#define MessageRect					CRect(120,120,520,360)
#define Left_Of_Keys(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(36):(326))		

#define	Top_CoOrdinate_Key(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(145):(74))	

#define	Width_Of_Key(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(48):(58))	

#define	Gap_Of_Key(KeypadType) ((((KeypadType)==(ALPHAKEYPAD))||((KeypadType)==(VGA_PASSWORD))||\
((KeypadType)==(SaveScanA))||((KeypadType)==(SaveScanB))||((KeypadType)==(SaveScanC)))?(9):(12))

#define COLDSTART_INPROCESSID  307
#define MAX_CHARS_LOGIN 11
class CVgaMenuItem;
class CXmlElement;

class CScreenKeypad  
{
public:
	bool KeyOffFlag;
	bool ShiftKeyEnable;
	static int NoOfWeldresult;
	static char	AlphaBuf[MAX_ALPHA_BUFF];//LINESIZE+1];       /*Original value buffer*/
	static int IsPassword_Accepted;
	static bool Qualityflag;
	bool CurrentTextOnly;
	static char login_userID[MAX_CHARS_LOGIN];  /*userID buffer*/
	static char login_password[MAX_CHARS_LOGIN];  /*password buffer*/
	/* new added for change password function           */
	static char Assign_UserID[MAX_CHARS_LOGIN];
	static char Old_Password[MAX_CHARS_LOGIN];
	static char New_Password[MAX_CHARS_LOGIN];
	static char Confirm_Password[MAX_CHARS_LOGIN];

	static void SetVariableStrings(CXmlElement * e);
	static CString StrME_1,StrME_2,StrME_3,StrME_4,StrME_5,Str_Reenter,StrPassTitle,
		StrEnterPass,StrConfirmPass,StrPassIncorrect,Str_Off;
	static CString StrME_1ID,StrME_2ID,StrME_3ID,StrME_4ID,StrME_5ID,Str_ReenterID,
		StrPassTitleID,StrEnterPassID,StrConfirmPassID,StrPassIncorrectID,Str_OffID,HornTitleID;
	CString Str_Curr,Str_CurrID;
	CString Str_New,Str_NewID;
	CString VariableTitleID,AlphaTitleID;
	static CString TempPassword;
	CString PassWordMenu;
	CScreenKeypad(int type1,int Pointer,unsigned char *&data,CString* Object_Text);
	CScreenKeypad(int type1,unsigned char *&data,CString* Object_Text,int ID,CVgaMenuItem *ptr);
	virtual ~CScreenKeypad();
	static void VGAAlphaEntry(CDC *pDC);
	bool MouseClick(const CPoint &p, CChildView *view,CDC *pDC);
	void Draw(CDC *pDC);
	void DrawPressedkey(CPoint point, CDC *pDC);

	typedef   int      UINT8;  
	typedef   UINT8    BYTE;            /* 8-bit  unsigned quantity  */
	typedef   int      UINT16;          /* 16-bit unsigned quantity  */
	typedef   int      UINT32;          /* 32-bit unsigned quantity  */
	typedef   char     SINT8;           /* 8-bit  signed quantity    */
	typedef   int      SINT16;          /* 16-bit signed quantity    */
	typedef   int      SINT32;     

	enum ERRORCODES
	{
		TIMERFAILED1 = 1,    /* No timers available             */
		TIMERFAILED2,        /* Time requested was 0            */
		MINRANGE,
		MAXRANGE,
		IDXRANGE,            /* Index out of range              */
		PTRRANGE,            /* Pointer out of range            */
		NOVALUE	,			/* No value entered after ClearKey */
		PassInvalid
	};        

	enum ALPHA_KEYPADID 
	{
		KEYPAD_EXCLAMATION = 0,KEYPAD_AT,KEYPAD_HASH,KEYPAD_DOLLAR,KEYPAD_PERCENT,
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
		KEYPAD_SHIFT,KEYPAD_BACKSPACE,KEYPAD_RIGHTARROW,KEYPAD_ENTER,KEYPAD_INC,KEYPAD_DEC,
		KEYPAD_OFF,KEYPAD_NONE,KEYPAD_SPACEBAR
	};

	enum EXT_KEYBOARDID{
		VK_CLOSEPARENTHESIS = 0x1030,
		VK_EXCLAMATION,
		VK_AT,
		VK_HASH,
		VK_DOLLAR,
		VK_PERCENT,
		VK_CIRCUMFLEX,
		VK_AMPERSAND,
		VK_ASTERISK,
		VK_OPENPARENTHESIS,		
		VK_SPACEBAR = 0x20,
		VK_0 = 0x30,
		VK_1,
		VK_2,
		VK_3,
		VK_4,
		VK_5,
		VK_6,
		VK_7,
		VK_8,
		VK_9,
		VK_A = 0x1041,
		VK_B,
		VK_C,
		VK_D,
		VK_E,
		VK_F,
		VK_G,
		VK_H,
		VK_I,
		VK_J,
		VK_K,
		VK_L,
		VK_M,
		VK_N,
		VK_O,
		VK_P,
		VK_Q,
		VK_R,
		VK_S,
		VK_T,
		VK_U,
		VK_V,
		VK_W,
		VK_X,
		VK_Y,
		VK_Z,
		VK_TILDE = 0xC0,
		VK_ACUTE = 0x10C0,//Shift + Tilde == 0x1000 + 0xC0
		VK_HYPHENN = 0xBD,
		VK_UNDERSCORE = 0x10BD,
		VK_EQUALS = 0xBB,
		VK_PLUS = 0x10BB,
		VK_OPENBRACKET= 0xDB,
		VK_OPENBRACE = 0x10DB,
		VK_CLOSEBRACKET = 0xDD,
		VK_CLOSEBRACE = 0x10DD,
		VK_QUESTIONMARK = 0xBF,
		VK_VERTICALBAR = 0x10DC,
		VK_SEMICOLONN = 0xBA,
		VK_COLON = 0x10BA,
		VK_APOSTROPHEE = 0xDE,
		VK_FORWARDSLASH = 0x10BF,
		VK_COMMAA = 0xBC,
		VK_LESSTHAN = 0x10BC,
		VK_PERIODD = 0xBE,
		VK_GREATERTHAN = 0x10BE,
		VK_a = 0x41,VK_b,VK_c,VK_d,VK_e,VK_f,VK_g,VK_h,VK_i,VK_j,
		VK_k,VK_l,VK_m,VK_n,VK_o,VK_p,VK_q,VK_r,VK_s,VK_t,
		VK_u,VK_v,VK_w,VK_x,VK_y,VK_z,
		VK_SHIFT1 = 0x1000,
		VK_BACKSPACE = 0x08,
		VK_RIGHTARROW = 0x27,
		VK_ENTER = 0x0D,
		VK_ENTER1 = 0x100D,
		VK_INC = 0x26 ,
		VK_DEC = 0x28,
		VK_NUM0 = 0x60,
		VK_NUM1,
		VK_NUM2,
		VK_NUM3,
		VK_NUM4,
		VK_NUM5,
		VK_NUM6,
		VK_NUM7,
		VK_NUM8,
		VK_NUM9,
		VK_NUMASTRISK = 0x6A,
		VK_NUMPLUS ,
		VK_NUMMINUS = 0x6D,
		VK_NUMPERIOD,
		VK_NUMFORWARDSLASHH,
		VK_OFFF,
		VK_NONE,
	};

	enum FORMAT {                     /*  US Format (units)  SI Format (units) */
		PERCENT,                       /*        xxx     %          xxx     %   */
		FORCE,                         /*       xxxx    lb         xxxx     N   */
		FORCEDIV10,                    /*     xxxx.x    lb         xxxx     N   */
		TIME,                          /*     xx.xxx     S       xx.xxx     S   */
		PRESSURE,                      /*        xxx    PSI         xxx   KPA   */
		DISTANCE,                      /*     x.xxxx    in      xxx.xxx    mm   */
		DISTANCE3,                     /*     x.xxxx    in       xx.xxx    mm   */
		FREQUENCY,                     /*      xxxxx    Hz        xxxxx    Hz   */
		FREQOFFSET,                    /*       Sxxx    Hz         Sxxx    Hz   */
		ENERGY,                        /*     xxxxxx     j       xxxxxx     j   */
		COUNTER,                       /*  xxxxxxxxx          xxxxxxxxx         */
		VELOCITY,                      /*      xx.xx  in/s        xxx.x  mm/s   */
		WATTS,                         /*      xxxx   W            xxxx  W      */
		BARGRAPH,                      /* [____|____]        [____|____]        */
		TIMEDATE,                      /* xx:xx xx/xx/xx                        */
		PERCENTX10,
		ENERGYDIV10,
		INTEGER,
		LONGTIME 
	};
	enum FIRSTKEYPRESS
	{
		KEY_NONE = 0,
		KEY_INC_DEC,
		KEY_NUMBER,
		KEY_OFF,
	};

	struct var_format_def1
	{
		SINT8   Units[5];       /* Name of units, up to 4 chrs */
		UINT8   LeftDigits;     /* Max # of digits left of decimal point */
		UINT8   RightDigits;    /* # of digits right of decimal point */
		UINT8   Increment;      /* Change in value with + or - keypress */
		BOOLEAN ShowSign;       /* TRUE to display + or - sign */
		SINT32  ConvMult;       /* Conversion multiplier */
		SINT32  ConvDiv;        /* Conversion divisor */
	};

	struct var_format_def2
	{
		struct var_format_def1 English;
		struct var_format_def1 Metric;
	};

	static struct VInf
	{
		int		Length	;				//	Text length in characters
		CString Keypad_title;			//	string, total count Length * BytesPerChar
		UINT16		Format	;			//	Variable format, enum FORMAT
		UINT16		Digits	;			//	Number of digits to display
		bool		Metric	;			//	TRUE - use metric formatting
		SINT32		Value;				//	Current value
		SINT32		MinVal	;			//	Minimum value
		SINT32		MaxVal	;			//	Maximum value
		SINT32		ID	;				//	Variable ID
		SINT16		Disable	;			//	TRUE if variable can be disabled
		SINT16		Disableflag ;		//	flag	Pointer to disable/enable flag
		SINT16		Bitmask	;			//	Bit used for this variable enable
		SINT32		NewVal;				//	
		int			 Sign;				//	 +-1 for formats which show sign, else 0 */
		UINT8		 Size;				/* Max # of chrs in ASCII representation */
		UINT16		StartPos;			/* Position on line where # should appear */
		CString    FunName;
		int      MaxInputDigits;		
	};
	struct AInf
	{
		CString Alpha_Keypad_title;
		CString		Current_Alpha_Value;
		int		MaxLength;
		bool	Hide;
		int		PARAM_ID;
		CString MenuNak;
		CString MenuAck;
		CString    FunName;
	};

	struct ALPHA_NUM_KEY
	{
		int KeyNum;
		int KeyCode;
	};
	CString DisabledChars;
	static int ConvertInternalExternal( SINT32 Value, enum FORMAT format );
	static int ConvertExternalInternal( SINT32 Number, enum FORMAT format );
	static void FormatNum(SINT32 Number,  char String[] );
	static CString FormatNumber(SINT32 Number,  char String[] ,enum FORMAT format,bool ChkUnitflag,bool Insertunitflag1);
	static bool InsertProperUnits(CVgaMenuItem *ptr,enum FORMAT format,int type);
	static CString InsertWeldParamUnit(CString string,enum FORMAT format);
	static CString InsertWeldParamUnitsString(bool metric,enum FORMAT format);
	bool VGAVarEntryMode( int KeyPressed,CDC *pDC,CChildView *view );
	bool ProcessKeypadfromKeyboard(int Key,CChildView *view,CDC *pDC);
	int ConvertKeyForNumKeyboard(int Key);
	static int ConvertKeyForAlphaKeyboard(int Key);
	static  bool ProcessBarcodeSCAN(int Key,CChildView *view,CDC *pDC);
	static bool ProcessBarcodeSCANCharacters(int KeyPressed,CChildView *view,CDC *pDC);
	static bool RestoreKeypad(void);
protected:

	CScreenKeypad();
	enum 
	{
		ACK = 0x06,
		NAK = 0x15
	};
private:
	static int pointer;
	static bool showScreenKeypad;
	static bool pressed;
	static bool OnKeypadScreen; 
	static bool ErrorDisplayed;
	static CRect PressedKeyRect;
	static int		PrevPressedAlphaNumKey;
	static int		MaxDigit;
	static int		TypedVal ;
	static int		DecimalCount;
	static int		DigitCounter;
	static int		TotalDigits ;
	static int    KeyCount; 
	static int    Index;  
	static bool  EntryFlag;       /*TRUE when value is entered successfully.*/
	static bool		MaxDigitFlag ;
	static bool		DPFlag;
	static char		EditLine[LINESIZE+1];
	static char		FILLCHAR;
	static char	OutputLine[MAX_ALPHA_BUFF];      /*Display buffer char displayed'*'-*/
	static int type;
	static int Alpha_key_no[10][10];
	static char AlphaNumKeyProp[][5];
	/*   in case of Password Entry*/
	static bool ExtKeyBoard;
	char Temp_Str[21];
	char buffer[25];
	CString* Object_Text_pointer;
	int PresetPointer;	
	int ID_type;

	void SendCommandForPassword(CChildView *view,int FunID,CDC *pDC);
	void HandleEnterOnPassword(CChildView *view,CDC *pDC);
	void HandleEnterOnSaveScanKeypad(CChildView *view,CDC *pDC);
	void CopyString(char *dest,char   *source);
	void VGADisplayCurrentNewValue(CDC *pDC);
	void DisplayVGAMinMax(CDC *pDC);
	void ConvertVariableFormat(enum FORMAT Format1,enum FORMAT Format2);
	void VGAVarEntryIncDecMode(int KeyPressed,CDC *pDC);
	void UpdateDateIfValid(CDC *pDC);
	void Draw_Pressed_Released_Button(CDC *pDC,CRect rect);
	void OffsetRect(CDC *pDC, CRect rect, COLORREF col);
	void VGADateEntry( int KeyPressed,CDC *pDC);
	void VGATimeEntry(int KeyPressed,CDC *pDC);
	void DisplayVGAMinMaxError(enum ERRORCODES ECode,CDC *pDC);
	void VGAAlphaEntryMode(int KeyPressed,CChildView *view,CDC *pDC);
	void UpdateTimeIfValid(CDC *pDC);
	static void DrawString(CDC *pDC, char string[MAX_ALPHA_BUFF], bool BigRect = false);
	void SplitString(char Split_Str[],char Split_Char[], char Splited_Str[]);
	bool ProcessPressedAlphakey(int KeyPressed,int type,CChildView *view,CDC *pDC);
	bool ProcessKeypad(int x, int y, CChildView *view,CDC *pDC);
	bool CheckForLeapYear(int  Year);
	bool CheckForValidDate(char* OutputLine,int Day, int Month,int Year);
	int myatoi(char s[]);
	int GetInteger(unsigned char *&data, int bytes);
	int VarSize(enum FORMAT format);
	void InitializedValues();
};

void LookforBarcodeScan(int Address);

#endif // !defined(AFX_SCREENKEYPAD_H__E92BFF74_AA6F_11D9_B39E_00B0D02A48D6__INCLUDED_)
