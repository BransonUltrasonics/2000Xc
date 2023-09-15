/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/graphs.h_v   1.12   08 Apr 2015 13:51:20   AnPawar  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/graphs.h_v  $
 * 
 *    Rev 1.12   08 Apr 2015 13:51:20   AnPawar
 * Changed define for Pressure Tick on graph.
 * 
 *    Rev 1.11   08 Jan 2015 03:12:26   AnPawar
 * Macros removed
 * 
 *    Rev 1.10   28 Nov 2014 07:55:34   rjamloki
 * FormatDataLine() removed.
 * 
 *    Rev 1.9   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
 * 
 *    Rev 1.8   28 Jul 2014 13:03:08   rjamloki
 * psos.h removed
 * 
 *    Rev 1.7   11 Jun 2014 12:54:16   rjamloki
 * renamed QVGA to VGA
 * 
 *    Rev 1.6   21 May 2014 10:49:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:12   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:06   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename: GRAPHS.H


            Written by: Gert Reitmayer  
                  Date: 9/14/96  
              Language:  "C"
 
----------------------------- REVISIONS ------------------------------------



------------------------ DESCRIPTION ----------------------------------*/

#include "qdef.h"
#include "weld_obj.h"
#include "preset.h"

/* DEFINES and function prototypes for the printer functions */

#ifndef GRAPHS_H
#define GRAPHS_H



                                              
/* constants for 1ms_data */          

#define COMPRESS          400.0   /* divisor for 1ms data              */
#define PRETRIGMAXLIM     100     /* max point before trigger          */
#define PRETRIGMINLIM     1       /* min point before trigger          */
#define MAXVELIN          5000    /* max velocity in in/s              */
#define MAXVELMM          127000  /* max velocity in mm/s              */
#define MAXNUMSIZE        50      /* Max number of welds in FRAM      */
#define MAXALARMS         500     /* Maximum number of alarms possible */
                           
/* Alarms */               
                           
#define SETUPEA1       0       
#define SETUPEA2       32      
#define SETUPEA3       64      
#define SETUPEA4       96      
#define SETUPEA5       128     
#define SETUPEA6       160     
#define SETUPEA7       192     
#define SETUPEA8       224
#define SETUPEA9       256
#define SETUPEA10      288
                      
#define NCALARM        0
#define OLALARM        32
#define EQALARM        64
#define CMALARM        96
#define CAALARM        128
#define WAALARM        160 
#define PRALARM        192
#define PSALARM        224




/* offset indices for MESS_LABEL 
   added to MESS_LABEL to point to corrrect text */

#define LABEL_AMPL     0
#define LABEL_POW      1
#define LABEL_FREQU    2
#define LABEL_DIST_IN  3
#define LABEL_FORCE_LB 4
#define LABEL_VELOC_IN 5
#define LABEL_DIST_MM  6
#define LABEL_FORCE_KG 7
#define LABEL_VELOC_MM 8

/* defines for printer init commands */

#define CHAR_PROP      2   // proportional
#define CHAR_NARROW    4   // condensed or 17 cpi
#define CHAR_FAT       8   // bold printout
#define CHAR_BROAD     32  // broad
#define CHAR_UNDER     128 // underline
#define PORTNUM        0   // 0=lpt1 used with biosprint (borland function) 
#define STATUS         2

/* defines for the graph printing */

#define LINE_LENGTH    400                        // number of pts.
#define FIELD_LENGTH   (LINE_LENGTH+21)           // field length exceeding 400
#define BORDER_LEFT    2                          // start of left border
#define BORDER_RIGHT   (BORDER_LEFT+LINE_LENGTH)  // start of right border
#define FINALLINE      137
#define MISCLINE       24
#define LINELENGTH     135
#define LABELLENGTH    145
#define BOTTOMLENGTH    90
#define BOTTOMTEXT      20




/* length of a line: 2 dots tick, 1 dot line vert, 400 dots values
   1 dot line vert. */

/* In printing the setup parameters switch to metric output */

#define DEF_ADDTEXT    0x80
#define DEF_METRIC     0xC0
#define DEF_DIV        0xA0
#define ENERGYPOINT    9999


/* Max Page sizes */

//#define MAXPAGE11      57   /*-- 66  WeldsPerPage: subtract 9 lines for HEADER --*/
//#define MAXPAGE14      75   /*-- 84  WeldsPerPage: subtract 9 lines for HEADER --*/
//#define MAXPAGEA4      61   /*-- 70  WeldsPerPage: subtract 9 lines for HEADER --*/
//#define MAXPAGE17      93   /*-- 102 WeldsPerPage: subtract 9 lines for HEADER --*/
//#define MAXPAGECONT    999
//#define MINPAGESIZE    10

                      
/* Line Length for 1 line data */

#define LINE70         70
#define LINE80         80
#define LINE110        110
#define LINE135        135


#define SIZEOFHISTBRAM (50 * sizeof(WELD_DATA)


/* Graph label const */                     
#define STARTLABEL    -0.100
#define LABELINT      -100
#define INCLABEL       10
#define LABELWIDTH6    6 
#define LABELWIDTH5    5
#define LABELWIDTH7    7
#define LABELWIDTH8    8
#define VALUEDIV       10000.0
#define VALUEDIV2      1000.0
#define FREQMAX41      41000
#define FREQMIN39      39000
#define LABELNUM       12
#define LABELSIZE      15

#define HISTORYDATA     50
#define GRAPHUPPERLIMIT 172 
#define WELDTIMEMAX     30000

/* Velocity graph const */
#define MAXFILTERSAMPLE  6
#define MAXFILT16SAMPLE  14
#define MAXFILT4SAMPLE   2
#define SQWITHDIGITAL    100 
#define WITHDIGITAL      3
#define WITHOUTDIGITAL   4
#define FILTERVEL16      14
#define FILTERVEL8       6
#define FILTERVEL4       2
#define SHIFTVEL2        2
#define SHIFTVEL3        3
#define SHIFTVEL4        4
#define SHIFTVEL5        5
#define SHIFTVEL6        6

#define MAXVELPOINTUSCS    16000
#define MAXVELPOINTMETRIC  450000

#define PRINTSCR0       0     
#define PRINTSCR1       1     
#define PRINTSCR2       2
#define PRINTSCR3       3
#define PRINTSCR4       4
#define PRINTSCR5       5
#define PRINTSCR6       6
#define PRINTSCR7       7
#define PRINTSCR8       8
#define PRINTSCR9       9
#define PRINTSCR10      10
#define PRINTSCR11      11
#define PRINTSCR12      12
#define PRINTSCR13      13
#define PRINTSCR14      14
#define PRINTSCR15      15
#define PRINTSCR16      16
#define PRINTSCR17      17
#define PRINTSCR18      18
#define PRINTSCR19      19
#define PRINTSCR20      20
#define PRINTSCR21      21
#define PRINTSCR22      22
#define PRINTSCR23      23
#define PRINTSCR24      24
#define PRINTSCR25      25
#define PRINTSCR26      26
#define PRINTSCR27      27
#define PRINTSCRSIZE    25

/* Line Feed and Carriage return counts*/
#define LFCR            1
#define LFCR2           2
#define LFCR3           3
#define LFCR4           4
#define LFCR5           5
#define LFCR6           6

/* General numbers in pr_print */
#define PRINTERHEAD7   7
#define PIXEL7TO0      255
#define PIXEL6TO1      126
#define PIXEL7TO3      248
#define PIXEL76        192
#define PIXEL7         128
#define PIXEL7TO5      224
#define POSITION0      0
#define POSITION2      60
#define POSITION16     480
#define POSITION13     390
#define POSITION10     300
#define POSITION11     330
#define POSITION12     360
#define POSITION27     810
#define POSITION41     1230
#define RESOLUTION     10
#define DATESIZE       9
#define MAX16INT       65534
#define ALARMTOPRINT   9
#define SINTINEL       3
#define BYTESIZE       8
#define ROUNDOFF       5
#define BITMOVE        1
#define OFFSET1        1
#define OFFSET2        2
#define OFFSET3        3
#define OFFSET4        4
#define OFFSET8        8
#define OFFSET5        5
#define OFFSET6        6
#define OFFSET7        7
#define OFFSET9        9
#define OFFSET10       10
#define NUM10DOT       10.0
#define VERTICALTICK   5
#define HORIZTICK      8
#define BOXSIZE        22
#define NUM100DOT      100.0
#define NUM100         100
#define NUM330         330
#define NUM254         25.4
#define NUM135         135
#define ENDGRAPH       401
#define NUM200         200
#define TESTSIZE       140
#define CONV254        254
#define TICKTRIG       0
#define TICKAMP        1
#define TICKPRESSURE   2
#define TICKSONIC      3
#define TICKHOLD       4
#define TICKSEEK       5
#define TICKSCRUB      6

/*-- Related to Gauge Pressure --*/
#define PSITOKPA       6.89
#define PSISTR          " psi"
#define KPASTR          " kPa"

#define VELMAX1000     1000
#define VELMAX3000     3000
#define VELMAX6000     6000

#define DIGITALFORCEVALUE   16


/**-----------------------------------------------------------------**
 **                    Structure Decalarations                      ** 
 **-----------------------------------------------------------------**/                       

typedef float FLOAT;

enum WHICHGRAPH {       
     AMPLIGRAPH,
     POWGRAPH,
     FREQUGRAPH,
     DISTINGRAPH,
     FORCELBGRAPH,
     VELINGRAPH,
     DISTMMGRAPH,
     FORCENGRAPH,
     VELMMGRAPH,
     ABSINGRAPH,
     ABSMMGRAPH,
     CURRENTGRAPH,
     POW_DISTMMGRAPH,
     POW_DISTINGRAPH,
     POW_FORCENGRAPH,
     POW_FORCELBGRAPH,
     FORCEN_DISTMMGRAPH,
     FORCELB_DISTINGRAPH,
     PHASEGRAPH,
     PMC_GRAPH,
     HSAMP_GRAPH,
     NO_VALID_GRAPH
};           

enum GRAPHID{
   VGAPOWERGRAPH,
   VGAFREQUENCYGRAPH,
   VGAAMPLITUDEGRAPH,
   VGAFORCEGRAPH,
   VGAVELOCITYGRAPH,
   VGACOLDISTGRAPH,
   VGAHORNSCANGRAPH
};




/* pr_kalib.c for sorting the input values */
struct STRComp{     
    UINT16 higher;
    UINT16 lower;
    };

/* PrintSummary function */
struct SummaryStruct{
        UINT8           b_yes_no        :    1;     // 1 = yes
        UINT8           b_unit          :    1;     // 0 = inch,
                                                    // 1 = metric
        UINT8           b_resolution     :    1;    // 0 = condensed
                                                    // 1 = not condensed
        UINT8           b_number        :    8;     // number of summaries
    };

/* PrintGraph function */
struct GraphicStruct{
        UINT8           b_yes_no        :    1;    // 1 = with graphic print
                                                   // 0 = without graphics
        UINT8           b_unit          :    1;    // 0 = inch, 1 = metric
//    UINT8           b_which_graph   :    4;     which graph to be printed
    };

/* printing the trailer at the bottom of the page */
struct BottomStruct{
    UINT8               b_yes_no        :    1;    // with or without bottom lines
    };

/* printing history values (not yet activated) */
struct HistoryStruct{
    UINT8               b_yes_no        :    1;    // with or without setup
    UINT8               b_every_page    :    1;
    };

/* global information is stored */
struct GeneralStruct{
    UINT8               b_printer_type    :    3;    // several printer types available
                                                                // 0 = Epson LQ
                                                                // 1 = Epson FX
                                                                // 2 = IBM Proprinter
    UINT8               b_language        :    4;    // max 7 languages
                                                                // 0 = english
                                                                // 1 = german
                                                                // 2 = french
    UINT8               b_welds_per_page  :    8;   // lines per page
    };






///* Which graph is being printed */
//
//struct GraphicStruct GraphicInfo;
//struct BottomStruct  BottomInfo;
//struct HistoryStruct HistoryInfo;
//struct GeneralStruct GeneralInfo;


/**-----------------------------------------------------------------**
 **                    External Variables Decalarations             ** 
 **-----------------------------------------------------------------**/                       

extern SINT32 val1[];
extern SINT32 val2[];
extern SINT32 val3[];
extern struct STRComp order1[];
extern struct STRComp order2[];

extern UINT32 UIVmaxlabel, UIVminlabel, UIHmaxlabel;
extern UINT32 UIWeldtime;
extern SINT32 AddrFram;
extern UINT8  *FramHistoryPtr;
//extern UINT32 UIGraphPoints;


/**-----------------------------------------------------------------**
 **                    Global Variables Decalarations               ** 
 **-----------------------------------------------------------------**/                       



/**-----------------------------------------------------------------**
 ** Function prototypes for functions in printer files:             ** 
 ** pr_print, pr_text, pr_label, 1ms_data, prnweld, prnmangr        **                       
 **-----------------------------------------------------------------**/                       
void SetupVals( enum WHICHGRAPH GraphSelected, SINT32 *Data );
UINT16 PlotSort( SINT32 *Data, struct STRComp *DataOrder, UINT16 NumSamp );
void RecalibVal( SINT32 *Data, UINT16 CurrentGraph, UINT32 VmaxLabel,
                 UINT32 VminLabel );
/*void PrintMessText(SINT32 ii);
UINT8* GetMessText(SINT32 INumber);
void SetHorizPos(UINT16 pos);
void PrintHistory(void);
void PrintSetup(void);
void PrintGraph(void);*/
void GetMaxMinLabel(UINT16 c_which_graph, SINT32 *Data, UINT16 ui_number,
UINT32 *p_maxlabel,UINT32 *p_minlabel);
SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);
//void PrintSheet(MSG_GRAPH_TYPE);
void InitPrinterFlags(void);
void VGAPrepTickMarks(void);
void GlobalSwitch1Func(void);
void GlobalSwitch2Func(void);
void GetPtsIncrement(void);
void PostHoldtimeState(void);
void PreTrigState(void);
void DurTrigWeldHoldState(void);
void GroupAllmSObject(void);
void CombineAllData(void);
void Get1msData(void);
void AbortCurPrintFunc(void);
void PrintWeldHistory(void);
UINT16 FuncExpandData(void);
void Form_Feed_Page(void);
void CalMaxLinesPerPage(void);
void SetMaxLinesPerPage(void);
void ControlLevelText(void);
void SetThePrinterType(void);
void EmulateEPSON(void);
void InitEPSON(void);
void InitHP(void);
void InitPrinterType(void);
void Select10CPI(void);
void Select12CPI(void);
void Select17CPI(void);
void Select16LF(void);
void Select872LF(void);
void SelectEmphasized(void);
void SelectNonEmphasized(void);
void Plot8Lines(UINT8 *PixelData, UINT16 NPixelCols);
void EnablePerforationSkip(void);

void SetPrinterToDraw(void);
void PrintSummaryLevel1(void);
void PrintSummaryLevel2(void);
void EscapeCodeString(SINT8 string2[], UINT16 len);
UINT16 CheckCurrentPrintStatus(void);
void GetLastHistoryData(void);
void ClearDataStorage(void);
void GetLastWeldData( WELD_DATA *Results );
void PrintTestFunc(void);
void DigitalFilterFunction(SINT32 *Data, SINT32 ForceDigFilter);
void GetLast1LineData(void);
void GetPresetNameFunc(void);
BOOLEAN CheckForPrintHeader(void);
                                        // these indices points to messages in pr_text.c
#endif /* end of GRAPHS_H */
