/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu.h_v   1.21   Oct 10 2017 15:45:00   RJamloki  $ */
#ifndef MENU_H
#define MENU_H
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu.h_v  $
 * 
 *    Rev 1.21   Oct 10 2017 15:45:00   RJamloki
 * Added enum  MICROC = BIT10 for new micro c actuator
 * 
 *    Rev 1.20   May 25 2017 17:33:22   RJamloki
 * Update secret key array size number
 * 
 *    Rev 1.19   06 May 2016 17:35:32   RJamloki
 * Added RS232 functionality
 * 
 *    Rev 1.18   16 Apr 2015 15:00:56   rjamloki
 * defined defaults for weld history setup
 * 
 *    Rev 1.17   16 Apr 2015 07:33:58   rjamloki
 * Added hw config enums in Mask1
 * 
 *    Rev 1.16   08 Apr 2015 13:51:50   AnPawar
 * define added for Pressure Step. RUN_PARAM enum updated for Pressure Stepping
 * 
 *    Rev 1.15   02 Jan 2015 04:16:22   rjamloki
 * PRESSURE2 added in enum FORMAT
 * 
 *    Rev 1.14   14 Nov 2014 05:23:30   rjamloki
 * NUMBER_OF_CODES macro changed as SetTableToDefault added to secretcode array .
 * 
 *    Rev 1.13   03 Oct 2014 06:23:52   rjamloki
 *  AMP_DECAY_PERCENT_DEFAULT  macro removed  
 * 
 *    Rev 1.12   11 Sep 2014 11:24:34   rjamloki
 * Added STRING format for event support
 * 
 *    Rev 1.11   05 Sep 2014 04:13:20   rjamloki
 * Added level C in Control Level enum
 * 
 *    Rev 1.10   22 Aug 2014 06:56:16   rjamloki
 * Added hold force in run param list
 * 
 *    Rev 1.9   09 Jul 2014 13:13:02   rjamloki
 * Added all authorities in LEVEL enum.
 * 
 *    Rev 1.8   11 Jun 2014 12:55:56   rjamloki
 * QVGA to VGA renaming
 * 
 *    Rev 1.7   27 May 2014 10:15:52   amaurya
 * Added mandatory colums in RUN_PARAM enum
 * 
 *    Rev 1.6   21 May 2014 10:49:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:16   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:32   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*                        
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:          

   Filename: menu.h

   Function name:

 --------------------------------- REVISIONS --------------------------------


 ------------------------------ INCLUDE FILES --------------------------------*/

#include "portable.h"
#include "PARAM.h"
#include "stdlib.h"





#define WC2000XTEST
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/


#define ENDLIST       -1
#define LINESIZE      20         /* Size of display line in characters     */
#define VGA_LINESIZE 62         /* mAX: Size of display line in VGA      */
#define MESSAGESIZE (LINESIZE+1) /* Size of display message include nul    */
#define TITLESIZE     14         /* Max # of chars on top line with page # */
#define MAXSUBMENUS   35         /* Max # of entries under any one menu    */
#define MAX_MENU_ITEMS 40        /* Max # of entries with some fudge space */
#define DISPLAY_LINES  4         /* Number of lines on the display device  */
#define MENULINES      3         /* Number of lines to display menus on    */
#define NUM_SEL_KEYS   3

//#define NULL           0          /* Nothing, empty, void(management),Nada */
#define RADIOLINKSIZE  12         /* Max # of sub menus to be linked       */
#define RADIOLINKLARGE 32         /* Max # of sub menus for DUPS Menu      */
#define ROWSIZE 10
#define COLUMNSIZE 5
#define LANGSIZE 5
#define ASIAN_LANGUAGE_START 5

//#define MAXSCROLLMENUS 22
//#define SCROLLBUFFERSIZE ((LINESIZE+1) * MAXSCROLLMENUS +1)
#define SCROLLBUFFERSIZE ((LINESIZE+1) * RMAXPARAMETERS +1)

#define FILLCHAR     ' '
#define VISIBLE      0
#define INVISIBLE    1

#define NOCHAR 0              /* Means display no characters in FormatStr */
#define NUM_OUTPUT_DEVICES 2  /* VF screen & terminal */

#define VF_DEVICE          0
#define VF_DEVICE_BIT      1

#define TERM_DEVICE        1
#define TERM_DEVICE_BIT    2

#define BARGRAPH_VFD       0
#define BARGRAPH_VGA      1
#define RATE_SLOWEST  BIT0
#define RATE_SLOW     BIT1
#define RATE_NORMAL   BIT2
#define RATE_FAST     BIT3
#define RATE_FASTEST  BIT4

#define MIN_TRIGGER_FORCE_DEFAULT_2IN  50
#define MIN_TRIGGER_FORCE_DEFAULT_3IN 100
#define GAIN_FACTOR_DEFAULT         1421
#define VELOCITY_PC_DEFAULT         1
#define FORCE_PC_DEFAULT_2IN        49
#define FORCE_PC_DEFAULT_3IN        99
#define IDLE_SPEED_DEFAULT          30
#define RT_COMP_DEFAULT             50
#define PRESSURE_STEP_AT_EXTERNAL   0x7d
#define AMP_STEP_AT_EXTERNAL        0x7d
#define ENERGY_BRAKE_TIME_DEFAULT   1000
#define ENERGY_BRAKE_AMP_DEFAULT    10 
#define LEAVINGHOMEFORCEMICROLO     3
#define LEAVINGHOMEFORCEMICROHI     7

#define NUMBER_OF_CODES             50 /* # of secret codes in menu.c */

#define SCAN_NONE           (UINT8)0xFF
#define XSCALEMINVALUE   400
#define XSCALEMAXVALUE   60100

#define DEFAULT_WELDHISTORY_COLUMNSETP_AEC 		0xFFFFDE00
#define DEFAULT_WELDHISTORY_COLUMNSETP_NONAEC	0xFFCFDE00

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

enum LineNums { ClrAll, Clr1, Clr2, Clr3, Clr4, Clr123 };


typedef struct {
   UINT16  Low;
   UINT16  Hi;
} UNION_UINT16;

typedef union {
   BOOLEAN        boolEAN;
   UNION_UINT16   Uint16;
} UNION_BOOL_UINT16;

extern UNION_BOOL_UINT16 KeepHornDown;           /* TRUE to keep horn down after PB release */


enum LEVEL {                      /* Security level of user                */
   OPERATOR,                      /* Lowest level of security              */
   TECHNICIAN,                    /* Middle level of security              */
   SUPERVISOR = 2,
   EXECUTIVE =4,
   MAINTENANCE =8,                  /* Highest level of customer security    */
   BRANSON =16,                       /* Level for Branson personnel only    */
   NOAUTH =32};

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
   LONGTIME,
   PRESSURE2,
   ON_OFF,
   STRING,
};

/* The following structures are used to set up the variable format table, */
/* see notes in MENU.C */

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

extern struct var_format_def2 VarFormatTable[];

enum CTRL_LEVEL {                /* Lowest model this feature will be on   */
   LEVEL_DEPOT = 0x001,
   LEVEL_t     = 0x010,          /*                                        */
   LEVEL_e     = 0x020,          /*                                        */
   LEVEL_a     = 0x030,          /*                                        */
   LEVEL_ea    = 0x040,          /*                                        */
   LEVEL_d     = 0x050,          /*                                        */
   LEVEL_f     = 0x060,          /*                                        */
   LEVEL_c     = 0x070,          /*                                        */
   LEVEL_TEST  = 0x0ffff         /* Make sure 16 bit value so nvram as     */
   };                            /* configured from Fisher Rosemont works  */


/* This enum is required for the automatic conversion process from ver 6.00 or 7.02 to ver 8.00 and above */

enum MODEL_V600 {     
   MODEL1 = 1,     
   MODEL2,           
   MODEL3,           
   MODEL4,           
   MODEL5,           
   MODEL6,           
   MODEL7    }; 
   
   
enum ACTUATOR {                   /* What actuator is required             */
   AE = BIT1,                     /*                                       */
   AO = BIT2,                     /*                                       */
   AED = BIT3,                     /*                                       */
   AOD = BIT4,                     /*                                       */
   AES = BIT5,                     /*                                       */
   MICRO = BIT6,                   /* Replaced AOS with MICRO               */
   AEF = BIT7,                     /*                                       */
   AOF = BIT8,                     /*                                       */
   HGUN = BIT9,
   MICROC = BIT10,
   DONTCARE = 65535u};            /*                                       */

/* Reordered frequency designators and changed values from 1 to 4 per conversation
   with Barry Kymer on 9-8-00 */
enum FREQTYPE {                   /* What PS frequency                     */
   FREQ15KHZ = 1,                 /*                                       */
   FREQ20KHZ,                     /*                                       */
   FREQ30KHZ,
   FREQ40KHZ,
   FREQ50KHZ,                     /* Reserve for future                    */
   FREQ60KHZ};                    /* For Ahmet special                     */             

enum MODES {                      /* All possible welding modes            */
   TIMEMODE = BIT0,               /* TIMEMODE   = 0x0001                   */
   ENERGYMODE = BIT1,             /* ENERGYMODE = 0x0002                   */
   PKPOWERMODE = BIT2,            /* PKPOWERMODE = 0x0004                  */
   COLLAPSEMODE = BIT3,           /* COLLAPSEMODE = 0x0008                 */
   ABSOLUTEMODE = BIT4,           /* ABSOLUTEMODE = 0x0010                 */
   GRDDETECTMODE = BIT5,          /* GRDDETECTMODE = 0x0020                */
   TECMODE = BIT6,                /* TECMODE = 0x0040                      */
   CONTINUOUSMODE = BIT7,         /* CONTINUOUSMODE = 0x0080               */
   ALLMODES = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 };
 

enum PAGESIZE {                   /* All possible PAGE SIZE                */
   PAGESIZE11 = BIT0,             /* PAGESIZE11 = 0x0001                   */
   PAGESIZE14 = BIT1,             /* PAGESIZE17 = 0x0002                   */
   PAGESIZEA4 = BIT2,             /* PAGESIZEA4 = 0x0004                   */
   PAGESIZE17 = BIT4 };           /* PAGESIZE16 = 0x0010                   */

enum  MASK1  {
   DUPS = 0x1L,                   //DUPS - BIT0
   LE = 0x2L,                     //Encoder - BIT1
   CONF = 0x4L,                   //Configured - BIT2         
   PC1025SP = BIT4,               /* 1025 board with Single Pole Estop  hardware*/
   PC1025DP = BIT5,               /* 1025 board with Double Pole Estop  hardware*/
   VGA = 0x0040L                  /* VGA  H/W*/    
   };             

enum  MASK2 {
   EC   = 0x1L,                   /* Error code */
   CUS  = 0x2L,                   /* Custom */ 
   WS   = 0x4L,                   /* Weld Status */
   DEPO = 0x8L,                   /* Depot */ 

   V_OL = 0x10L,                  /* Voltage overload */
   C_OL = 0x20L,                  /* Current overload */
   F_OL = 0x40L,                  /* Frequency overload */
   P_OL = 0x80L,                  /* Phase overload */
   HE   = 0x100L,                 /* Hold enabled */
   ALR  = 0x200L,                 /* Alarms */ 
   VEL  = 0x400L,                 /* velocity reporting */ 
   HH   = BIT11,                  /* Handheld enabled */ 
   EP_E = BIT12,                  /* External preset enabled. */
   HSC  = BIT13,                  /* HSC menu Enabled. */ 
   SBL_EN = BIT14,                /* SBL enabled globally */
   CAL  = BIT15,                  /* Recal code 300 reporting */
   };

enum ADVANCE {                    /* Conditions to advance to next menu    */
   SELECTKEY,                     /*  - when the Select key is pressed     */
   PALMBUTTONS,                   /*  - when palm buttons & trigger exist  */
   TEST,                          /*  - when the Test button is hit        */
   FLAG    };                     /*  - when Flag is set TRUE              */ 

enum NAME_PRESET {
   NAME_MODE = 1,                 /* Auto name using current weld mode     */
   NAME_CURRENT,                  /* Auto name using current preset name   */
   NAME_NEW   };                  /* Auto name using dest. preset name     */

enum PRESET_FUNCTION {
   FUNCTION_CLEAR = 1,            /* Preset function - Clear               */
   FUNCTION_RECALL,               /* Preset function - Recall              */
   FUNCTION_INFO,                 /* Preset function - Information         */
   FUNCTION_VERIFY,               /* Preset function - Verify              */
   FUNCTION_SAVE  };              /* Preset function - Save                */


enum MENUS {
   _TITLE = 1,
   _TEXT,
   _SUBMENU,                      /* Submenus on a new display page        */
   _HSUBMENU,                     /* Submenus scrolled on a horizontal line*/
   _HHMM,
   _DATE,
   _CHOICE,
   _ALPHA,
   _VARIABLE,                     /* Variable of type signed short         */
   _RADIO,
   _RADIOMENU,
   _TOGGLE,                       /* 2 choices, but not ON/OFF, no submenu */
   _HVARIABLE,                    /* Variable scrolled on a horizontal line*/
   _ALARM,
   _RADIOLARGEMENU,               /* Currently used for DUPS only          */
   _RADIOLARGE,                   /* Used in conjunction with RADIOLARGEMENU */
   _GRAPH,
   _MENUEND,
   _VGATEXT,
   _VGATEXTBOX,
   _VGALINE,
   _VGARUNSCREEN,
   _VGABUTTON,
   _VGABOTTOMHALF,
   _VGACHECK,
   _VGAGRAPH,
   _VGALISTBOX,
   _VGAMSGSCREEN,
   _VGAPOINTER,
   _VGATABLE,
   _RSPARAMETER   };

enum RUN_PARAM {
   WELDRESULTS = 0,
   RCYCLECOUNT,
   RUSERID,
   RUDISCAN,
   RPRESETNUM,
   RPRESETREV,
   RPRESETVALIDATED,
   RACTASSEMBLYNUM,
   RPSASSEMBLYNUM,
   RSTACKASSEMBLYNUM,
   RTIME,
   RPKPWR,
   RENERGY,
   RVELOCITY_AED,
   RVELOCITY_AEF,
   RWABSDIST,
   RTABSDIST,
   RWCOLDIST,
   RTCOLDIST,
   RAMPSTART,
   RAMPEND,
   RPRESSUREA,
   RPRESSUREB,
   RFORCE,
   RSYSPRESS,
   RFREQMIN,
   RFREQMAX,
   RFREQSTART,
   RFREQEND,
   RFREQCHG,
   RCYCLETIME,
   RHOLDFORCEMAX,//31
   RMAXPARAMETERS,
   RUNPARAMSIZER = 65535 };

enum RADIOMASK {
   RADIO_0 = 0x0001,   
   RADIO_1 = 0x0002,   
   RADIO_2 = 0x0004,   
   RADIO_3 = 0x0008,   
   RADIO_4 = 0x0010,   
   RADIO_5 = 0x0020,   
   RADIO_6 = 0x0040,
   RADIO_7 = 0x0080,
   RADIO_8 = 0x0100,
   RADIO_9 = 0x0200,
   RADIO_10 = 0x0400,
   RADIO_11 = 0x0800,
   RADIO_12 = 0x1000,
   RADIO_13 = 0x2000,
   RADIO_14 = 0x4000,
   RADIO_15 = 0x8000,
   RADIO_16 = 0x10000,
   RADIO_17 = 0x20000,
   RADIO_18 = 0x40000,
   RADIO_19 = 0x80000,
   RADIO_20 = 0x100000,
   RADIO_21 = 0x200000,
   RADIO_22 = 0x400000,
   RADIO_23 = 0x800000,
   RADIO_24 = 0x1000000,
   RADIO_25 = 0x2000000,
   RADIO_26 = 0x4000000,
   RADIO_27 = 0x8000000,
   RADIO_28 = 0x10000000,
   RADIO_29 = 0x20000000,
   RADIO_30 = 0x40000000,
   RADIO_31 = 0x80000000,
   RADIOSIZER = 0xFFFFFFFF }; 

enum RS232_MASK {
   ASCIICOMMA = RADIO_0,
   ASCIITAB = RADIO_1,
   ASCIISPACE = RADIO_2,
   RS232DISABLED = RADIO_3 };


enum GRAPH_TYPE {
   POWER_GRAPH,
   FREQUENCY_GRAPH,
   AMPLITUDE_GRAPH,
   FORCE_GRAPH,
   VELOCITY_GRAPH,
   COL_DIST_GRAPH,
   POWER_COL_GRAPH,
   POWER_FORCE_GRAPH,
   FORCE_COL_GRAPH   
   };

enum COLOR {
   COLOR_DEFAULT = 0,
   COLOR_BLACK,
   COLOR_BLUE,
   COLOR_RED,
   COLOR_GREEN,
   COLOR_BROWN,
   COLOR_MAGENTA,
   COLOR_CYAN,
   COLOR_LIGHTGREY,
   COLOR_GREY,
   COLOR_YELLOW,
   COLOR_WHITE
   };    

enum FONT {
   FONT_DEFAULT = 0,
   FONT_1,
   FONT_2
   };    
 
typedef struct menu0 {  
   const void     *ptr;                  /* Pointer to one of the next structures */
   enum     MENUS type;            /* Which structure is it pointing to     */
   } MENU;


typedef struct menu1 {             /* Text only, top line title             */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   CenterFlag;            /* TRUE if should center justify field   */
   UINT16   PageFlag;              /* TRUE if page information should show  */
   UINT16   CaseFlag;              /* TRUE if text should be uppercased     */
   } TITLE;


typedef struct menu2 {             /* Text only, lines 2-4, information     */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   JustifyFlag;           /* TRUE:Right justify  FALSE:Left justify*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   } TEXT;

typedef struct menu3 {             /* Text used as a choice for sub menus   */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func1)(UINT32);      /* Function to execute before menu called*/
   UINT32   Arg;                   /* Argument for function call above      */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   enum     ADVANCE next;          /* SELECTKEY/PALMBUTTONS/TEST/FLAG       */
   BOOLEAN  *flag;                 /* Pointer to Flag if FLAG is selected   */
   UINT16   Timeout;               /* Length of time to display menu        */
   UINT16   UpdateTime;            /* Time before display is updated        */
   void     (*func2)(void);        /* Function to execute after menu called */
   } SUBMENU;


typedef struct menu4 {             /* Text used as a choice for sub menus   */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Vptr;                 /* ?                                     */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   enum     ADVANCE next;          /* SELECTKEY/PALMBUTTONS/TEST/FLAG       */
   BOOLEAN  *flag;                 /* Pointer to Flag if FLAG is selected   */
   void     (*func2)(void);        /* Function to execute before menu call  */
   } HSUBMENU;


typedef struct menu5 {             /* Text with time                        */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   SINT32   *Hour;                 /* Pointer to hour in 24 hour format     */
   SINT32   *Minute;               /* Pointer to minutes                    */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } HHMM;


typedef struct menu6 {             /* Text with date                        */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   SINT32   *Month;                /* Pointer to month  JAN = 1             */
   SINT32   *Date;                 /* Pointer to date                       */
   SINT32   *Year;                 /* Pointer to year   1995=95, 2003=03    */ 
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } DATE;


typedef struct menu7 {             /* Text with 2 choices, submenu with ON  */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   BOOLEAN  *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   *Rptr;                 /* Pointer to return value (TRUE/FALSE)  */
   STR      **Sptr1;               /* Pointer to choice 1 string (FALSE)    */
   STR      **Sptr2;               /* Pointer to choice 2 string (TRUE)     */
   MENU     *Mptr;                 /* Pointer to sub menus (if choice 2)    */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   SINT16   Timeout;               /* Length of time to display menu        */
   SINT16   UpdateTime;            /* Time before display is updated        */
   void     (*func)(void);         /* Pointer to function to execute        */
   } CHOICE;             


typedef struct menu8 {             /* Text, selecting alpha characters      */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **TtlPtr;              /* Pointer to string for title in entry  */
   STR      **Pptr;                /* Pointer to string to use as prompt    */
   UINT16   NumChar;               /* Number of characters allowed          */
   UINT16   StartPos;              /* Position on display line for entry    */
   UINT16   Hide;                  /* TRUE if entry should not be displayed */
   SINT8    *Rptr;                 /* Pointer to return string              */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } ALPHA;


typedef struct menu9 {             /* Text with a variable (short) field    */
/****************************************************************************/
/*  Text string to contain ampersands (&&) where the units should be disp.  */
/****************************************************************************/

   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   disable;               /* TRUE if variable can be disabled      */
   UINT16   *DisableFlag;          /* Pointer to disable/enable flag        */
   UINT16   BitMask;               /* Bit used for this variable enable     */
   enum     FORMAT format;         /* PERCENT/FORCE/TIME/DISTANCE/FREQUENCY */
   UINT16   digits;                /* Number of digits to display (0=all)   */
   UINT16   Security;              /* TRUE:Security on, supress display (*) */
   SINT32   *Vptr;                 /* Pointer to value                      */
   SINT32   *ptrmin;               /* Pointer to minimum value accepted     */
   SINT32   *ptrmax;               /* Pointer to maximum value accepted     */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } VARIABLE;


typedef struct menu10 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow two or more (up to 10) sub menu items to be   */
/*  linked.  This means if any item in the list is turned on all other      */
/*  items in the list will be turned off.  Only one item can be selected.   */
/****************************************************************************/
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   *Vptr;                 /* Pointer to value                      */
   enum     MODES Value;           /* Value                                 */
   enum     RADIOMASK RadioMask;   /* Which index in list is this entry     */
   STR      **Sptr1;               /* Pointer to string (OFF = FALSE)       */
   STR      **Sptr2;               /* Pointer to string (ON = TRUE)         */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } RADIO;                      

                                 
typedef struct menu11 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow displaying of a choice of radio menus.        */
/*  Selecting the choice will bring up a list menus allowing the choice to  */
/*  be changed.  This structure only deals with displaying the choice.      */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **Cptr[RADIOLINKSIZE]; /* Pointers to strings of all choices    */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func2)(void);        /* Function to execute after menu called */
   } RADIOMENU;                  

                                 
typedef struct menu12 {            /* Text with 2 choices other then ON/OFF */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1 ;                /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   BOOLEAN  *Eptr;                 /* Pointer to flag to see if display line*/
   BOOLEAN  *Rptr;                 /* Pointer to return value (TRUE/FALSE)  */
   STR      **Sptr1;               /* Pointer to choice 1 string (FALSE)    */
   STR      **Sptr2;               /* Pointer to choice 2 string (TRUE)     */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } TOGGLE;                 


typedef struct menu13 {            /* Text with 2 choices other then ON/OFF */
   STR     **Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT8    *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   *DisableFlag;          /* Pointer to disable/enable flag        */
   void     (*func1)(void);        /* Function to execute before menu called*/
   enum     FORMAT format;         /* PERCENT/FORCE/TIME/DISTANCE/FREQUENCY */
   UINT16   Security;              /* TRUE:Security on, supress display (*) */
   SINT32   *Vptr;                 /* Pointer to value                      */
   enum PARAM ID;                  /* Unique identifier for this parameter  */
   enum RUN_PARAM Index;           /* Unique identifier for this parameter  */
   void     (*func2)(void);        /* Pointer to function to execute        */
   } HVARIABLE;


typedef struct menu14 {            /* Text only, lines 2-4, information     */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT32   BitLoc;                /* Bit Mask used for this menu enable    */
   UINT32   *Aptr;                 /* Pointer to General Alarm Variable     */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } ALARM;


typedef struct menu15 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow displaying of a choice of radio menus.        */
/*  Selecting the choice will bring up a list menus allowing the choice to  */
/*  be changed.  This structure only deals with displaying the choice.      */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINANCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if it should look at EnableValue */
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **Cptr[RADIOLINKLARGE];/* Pointers to strings of all choices    */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func2)(void);        /* Function to execute after menu called */
   } RADIOLARGEMENU;


typedef struct menu16 {            /* Radio(large) menus linked together    */
/****************************************************************************/
/*  This structure will allow two or more (up to 10) sub menu items to be   */
/*  linked.  This means if any item in the list is turned on all other      */
/*  items in the list will be turned off.  Only one item can be selected.   */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   UINT16   *Lptr;                 /* Pointer to locked array               */
   UINT16   *Vptr;                 /* Pointer to value                      */
   UINT16   Value;                 /* Value                                 */
   STR      **Sptr1;               /* Pointer to string (OFF = FALSE)       */
   STR      **Sptr2;               /* Pointer to string (ON = TRUE)         */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } RADIOLARGE;

typedef struct menu17 {
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;
   enum     PARAM ID;              /*Param ID*/
   }GRAPH;

typedef struct menu18 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */ 
   enum     COLOR TextColor;       /* Text Color*/
   } VGATEXT;
   
typedef struct menu19 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR fillcolor;       /* Text Box fill Color                   */
   enum     COLOR TextColor;       /* Text Color                            */
   } VGATEXTBOX;

typedef struct menu20 {            /* Text only, lines 2-4, information     */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     COLOR Linecolor;       /* Line Color                            */
   } VGALINE;

typedef struct menu21 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   *CycleCount;           /* Pointer to Cycle Count variable       */
   BOOLEAN  *AllColumnFlag;        /* Pointer to send all columns or not    */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */  
   } VGARUNSCREEN;

typedef struct menu22 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */
   } VGABUTTON;

typedef struct menu23 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   BOOLEAN  RefreshReq;            /* Flag to see if refresh required       */
   UINT16   RefreshInterval;       /* Refresh Intervalin msec               */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     COLOR fillcolor;       /* Text Box fill Color                   */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   } VGABOTTOMHALF;

typedef struct menu24 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   XCoordinate;           /* X Co-ordinate                         */
   UINT16   YCoordinate;           /* Y Co-ordinate                         */
   BOOLEAN  *Selected;             /* Whether selected or not               */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */
   } VGACHECK;

typedef struct menu25 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR LineColor;       /* Line Color                            */  
   } VGAGRAPH;

typedef struct menu26 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   *AddlInfo;             /* Pointer to additional Info            */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     COLOR fillcolor;       /* Fill Color                            */  
   } VGALISTBOX;

typedef struct menu27 {            /*                                       */
   STR      **Tptr1;               /* Pointer to text string                */
   STR      **Tptr2;               /* Pointer to text string                */
   STR      **Tptr3;               /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   Timer;                 /* Timer in msec 0 means no timeout      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */  
   enum     COLOR fillcolor;       /* Fill Color                            */  
   } VGAMSGSCREEN;

typedef struct menu28 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   } VGAPOINTER;

typedef struct menu29 {            
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT8    NosOfRows;             /*Total number of rows in the table      */
   UINT8    NosOfColumns;          /*Total number of columns in the table   */
   void     (*func)(void);         /* Function to execute before menu called*/
   STR      **Rptr[ROWSIZE];       /* Pointers to strings of all choices    */
   STR      **Cptr[COLUMNSIZE];    /* Pointers to strings of all choices    */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   } VGATABLE;                  

typedef struct menu30 {            /* Text with 2 choices other then ON/OFF */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   enum RUN_PARAM Index;           /* Unique identifier for this parameter  */
   } RSPARAMETER;

typedef struct menuend {     
   SINT8    junk;                  /* Indicate end of list                  */
   } MENUEND;

typedef struct Codes {
   STR    *Password;             /* Pointer to the password string           */
   STR    *Ptr;                  /* Pointer to entered digits, menu will use */
   void   (*func)(void);         /* Pointer to function to execute           */
   UINT16 ID;                    /* Menu ID number if menu is displayed      */
} CODES;
   
extern const MENU TheMainMenu[];
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/



void BUCMenu(void);
void DebugMenu(void);
void VelocityOn(void);
void VelocityOff(void);
void CreateSecretCodes(void);
void RestoreDefaults(void);
void EnableTestingMenu(void);
void EnableSpecialsMenu(void);


void SlowActADComm(void);
void FastActADComm(void);
void SlowerActADComm(void);
void SelectOldBoard(void);
void SelectNewBoard(void);
void ConfigSBeam(void);
void ConfigLoadcell(void);
void DisableCode300(void);
void EnableCode300(void);

void ConfigAEDSbeam(void);
void ConfigAEFSbeam(void);
void ConfigAESSbeam(void);
void ConfigMICROSbeam(void);
void Config50mmMICRO(void);
void ConfigOriginal_MICRO(void);
void ConfigMaxMinValues(void);

void FormatVariables( SINT32 Value, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric );

void FormatNums( SINT32 Number, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric );

SINT32 ConvertInternalExternal( SINT32 Value, enum FORMAT format, BOOLEAN Metric );

SINT32 ConvertExternalInternal( SINT32 Number, enum FORMAT format,
 BOOLEAN Metric );

UINT8 WaitKeyPress(void);
void ShowEstopMessageOn(void);
void ShowEstopMessageOff(void);

MENU *GetCurrentMenu(void);


void AlarmOn(void);
void AlarmOff(void);
void EnablePLCTiming(void);
void UpdateHWConfiguration(enum MASK1 HWConfig, BOOLEAN Enabled);
void UpdateSWConfiguration(enum MASK2 SWConfig, BOOLEAN Enabled);
BOOLEAN IsHWConfigured(UINT16 HWType);
void EnableDiagnostics(void);
void DistanceSS(void);
void DupsControl(void);
void EnableHSCandSBL(void);
void DisableHSCandSBL(void);
void EnableUSEncoder(void);
void EnableMetricEncoder(void);
void EnableTF(void);
void SetSpringRate3(void);
void SetSpringRate4(void);
void SaveCalibration(void);
void DisplayChecksum(void);
void SetContLevelt(void);
void SetContLevelea(void);
void SetContLeveld(void);
void SetContLevelf(void);
void SetContLeveldepot(void);
void SetContLeveltest(void);
UINT16 USBFullCheckFunc(void);
extern const UINT16  CurrentVersion;
extern UINT16 ChecksumRet;
extern SINT32 GlobalRetryCounter;
extern SINT16  MenuCounter;
extern SINT16   BlankMenuCounter;
#endif
