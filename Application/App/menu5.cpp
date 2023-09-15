/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu5.cpp_v   1.20   16 Apr 2015 07:25:18   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu5.cpp_v  $
 * 
 *    Rev 1.20   16 Apr 2015 07:25:18   rjamloki
 * Fix for coverity issue 12215
 * 
 *    Rev 1.19   11 Mar 2015 09:16:32   amaurya
 * Fix for state machine remains off if user choose to escape from start freq change on diagnostic or horn signature menu.
 * 
 *    Rev 1.18   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.17   28 Nov 2014 07:37:42   rjamloki
 * Code clean up.Removed unused extern variables.
 * 
 *    Rev 1.16   10 Nov 2014 11:21:22   RJamloki
 * Fix for debug menu display.
 * 
 *    Rev 1.15   10 Nov 2014 04:52:56   AnPawar
 * unused function CloseCalibration() removed,12.F review change.Crirical section removed from DigitalPotEntry() and DigitalFreqEntry(),12.F review change.
 * 
 *    Rev 1.14   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.13   18 Aug 2014 01:42:52   rjamloki
 * Cleaned up for right display in Debug Menu
 * 
 *    Rev 1.12   28 Jul 2014 12:36:40   rjamloki
 * psos.h removed
 * 
 *    Rev 1.11   11 Jun 2014 11:56:12   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 03:09:04   rjamloki
 * coverity fixes
 * 
 *    Rev 1.8   14 Apr 2014 09:39:54   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.7   26 Mar 2014 12:22:20   rjamloki
 * DigitalPotEntry() function changed,DigitalFreqEntry() function 
 * 
 *    Rev 1.6   06 Mar 2014 11:03:52   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:42   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:36   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

 Module name:

 Filename: menu5.c

 This file will deal with the Calibrate and Diagnostic functions.

 --------------------------- INCLUDE FILES --------------------------------*/

#include "qdef.h"
#include "string.h"
#include "ticks.h"
#include "selctkey.h"
#include "menu5.h"
#include "digout.h"
#include "preset.h"
#include "sc.h"
#include "weld_obj.h"
#include "spidd.h"
#include "statedrv.h"
#include "FrontPanelKeypadTask.h"
#include "beep.h"
#include "getmsg.h"
#include "util.h"
#include "fpled.h"
#include "menu.h"
#include "menutest.h"
#include "dups_api.h"
#include "snsrcalb.h"
#include "actnvram.h"
#include "command.h"
#include "stdio.h"

extern char __SDRAM_BASE[];
extern char __SDRAM_SIZE[];
/*----------------------------- LOCAL_DEFINES ------------------------------*/

#define MAXDIGITALFREQ 50
#define MINDIGITALFREQ -50
#define DIGITALFREQINC 1
#define START_OF_RAM  ((SINT32)__SDRAM_BASE)       /* Beginning of RAM               */
#define END_OF_RAM    (START_OF_RAM + ((SINT32)__SDRAM_SIZE) - 16)    /* 16 bytes from end of RAM       */
                                     /* because debug reads 16 at once */
                                     

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */

STR    DebugTitle[VGA_LINESIZE];
STR    DebugText1[VGA_LINESIZE];
STR    DebugText2[VGA_LINESIZE];
STR    DebugText3[VGA_LINESIZE];
STR    DebugText4[VGA_LINESIZE];
STR  *DebugTitleMsg[] = { DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle };

STR  *DebugText1Msg[] = { DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1 };

STR  *DebugText2Msg[] = { DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2 };

STR  *DebugText3Msg[] = { DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3 };

STR  *DebugText4Msg[] = { DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4 };



BOOLEAN VGADebugDataFlag = FALSE;
UINT16 DryCycleFlag = FALSE;
UINT16 DiagFlag = FALSE;
UINT16 DebugPasswordFlag = FALSE;
BOOLEAN DebugBase;
BOOLEAN DebugBytes;

SINT32 FMemoryBargraph = 6;
SINT32 FMemoryBargraphMin = 0;
SINT32 FMemoryBargraphMax = 12;
SINT32 FActualBargraph = 6;
SINT32 FActualBargraphMin = 0;
SINT32 FActualBargraphMax = 12;

MENUEND endlist5 = { TRUE };

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

UINT16 OrigDigTuneFlag;        /* Initial DigTune On/Off state */
SINT32 OrigDigTuneValue;       /* Initial DigTune value before editing */
SINT32 DigTuneValue;           /* This is what user edits */
SINT32 MinDigTuneValue;        /* Min value allowed in editing */
SINT32 MaxDigTuneValue;        /* Max value allowed in editing */
BOOLEAN HSNotStarted = TRUE;
UINT8 FreqType[DUPS_NUMRESONANCES];
UINT16 BinEnable,HexEnable;
UINT32 TempDebugPtr;
extern SINT32 SaveDigTuneValue;
extern BOOLEAN  ForceDigitalTuneTest;
/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

BOOLEAN DigitalFreqEntry(void);
void UpdateDigitalFreq(void);
void VGACheckDigitalTune(void);

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern struct act_nvr NVR;
extern INBITS Inp;

extern UINT16 ResonanceFreqEnable[];

extern UINT8   MainKeyFlag;
extern SINT16  BlankMenuCounter;

extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern BOOLEAN ReadyFlag;

extern BOOLEAN PSFailCode;
                         


/* Stuff for the special debug feature */

extern UINT16 ADPressure;
extern UINT16 ADForce;
extern SINT16 FailTrace, AlarmHornWeight;
extern SINT16 LastFailTrace;
extern UINT8  VGALatchPSStore;

SINT32 DebugLowValue =  0;            /* Start of quick list */
SINT32 DebugHighValue = (((unsigned int) __FRAM_START)) + FRAM_SIZE - 16;  /* End of FRAM -16      */


SINT32 DebugPtr;
STR    DebugAddr[]           = "Addr:         ";
STR    Debug00[]             = "00:                 ";
STR    Debug04[]             = "04:                 ";
STR    Debug08[]             = "08:                 ";
STR    Debug0A[]             = "0A:                 ";
STR    Debug10[]             = "10:                 ";
STR    Debug18[]             = "18:                 ";
STR    ActIdText[]           = "Act ID      ";   
STR    SerNumText[]          = "Act S/N     ";   
STR    DefSerNumText[]       = "Def act S/N ";
STR    LoadCellText[]        = "Loadcell Tbl"; 
STR    DefLoadCellText[]     = "Def L/C Tbl "; 
STR    LevelText[]           = "Cntrl Level ";    
STR    ADPressText[]         = "AD Press.   ";    
STR    ADForceText[]         = "AD Force    ";    
STR    SpringRateText[]      = "Springrate  ";    
STR    PSVerText[]           = "Cal: PS ver ";    
STR    PressureText[]        = "Pressure Tbl";    
STR    FailTraceText[]       = "Fail Code   ";    
STR    PSFailText[]          = "PSFail EVRS ";    
STR    LastFailTraceText[]   = "NotReadyCode";    
STR    HWFailText[]          = "Horn Weight ";    
STR    ForceText[]           = "Force Tbl   ";  

typedef struct DebugList {
   void      *MemPtr;       /* Pointer to memory locations          */
   STR       *TextPtr;      /* Pointer to descriptive text          */
   UINT16    Base;          /* Default number base                  */
   UINT16    Size;          /* Default word (TRUE) or long (FALSE)  */
   } DEBUGLIST;
   
#define MAX_LIST_ENTRIES   16   /* Arbitrary limit, can be any practical size */
#define HEX      1
#define DECIMAL  2
#define BINARY   3
#define BASE10  0

  
DEBUGLIST   QuickList[MAX_LIST_ENTRIES] = {
/* Address                          Text               Base     Size    */
/* -----------------------------    -------------      -------  -----   */
  {&NVR.ActId,                      ActIdText,         DECIMAL, TRUE},     /* Quick List Entry 0  */
  {&NVR.SerNum,                     SerNumText,        HEX,     TRUE},     /* Quick List Entry 1  */
  {&NVR.DefSerNum,                  DefSerNumText,     HEX,     TRUE},     /* Quick List Entry 2  */
  {&NVR.LoadCell,                   LoadCellText,      DECIMAL, TRUE},     /* Quick List Entry 3  */
  {&CurrentSetup.ControlLevel,      LevelText,         HEX,     TRUE},     /* Quick List Entry 4  */
  {&ADPressure,                     ADPressText,       DECIMAL, TRUE},     /* Quick List Entry 5  */
  {&ADForce,                        ADForceText,       DECIMAL, TRUE},     /* Quick List Entry 6  */
  {&CurrentSetup.SpringRateTable,   SpringRateText,    DECIMAL, TRUE},     /* Quick List Entry 7  */
  {&NVR.PSVersion,                  PSVerText,         DECIMAL, TRUE},     /* Quick List Entry 8  */
  {&NVR.Pressure,                   PressureText,      DECIMAL, TRUE},     /* Quick List Entry 9  */
  {&NVR.DefLoadCell,                DefLoadCellText,   DECIMAL, TRUE},     /* Quick List Entry 10 */
  {&LastFailTrace,                  LastFailTraceText, DECIMAL, TRUE},     /* Quick List Entry 11 */
  {&FailTrace,                      FailTraceText,     DECIMAL, TRUE},     /* Quick List Entry 12 */
  {&PSFailCode,                     PSFailText,        BINARY,  TRUE},     /* Quick List Entry 13 */
  {&AlarmHornWeight,                HWFailText,        DECIMAL, TRUE},     /* Quick List Entry 14 */
  {&NVR.Force,                      ForceText,         DECIMAL, TRUE},	  /* Quick List Entry 15 */
};


/*-------------------------------- CODE ------------------------------------*/



void SetDiagFlag(void)
{
   DiagFlag = TRUE;
   LatchPSRun = LatchPSSeek = LatchPSClear = LatchPSStore = FALSE;
   Inp.PSStore = FALSE;  /* Clear here, set by ISR */
   VGALatchPSStore = FALSE;
   UpdateDigitalFreq();
   //Fix for state machine remains off if user choose to escape from start freq change on diagnostic or horn signature menu
   if (!CheckStateMachine())
   {
        if ((CurrentSetup.DigTuneFlag & BIT0) && (ForceDigitalTuneTest == FALSE) && (SaveDigTuneValue == DigTuneValue))
        {
           ResetStateMachine();  /* Position is at original value, */
           StartStateMachine();  /* don't need to force Test.      */
        }
   }
}



void DisableCalActKey1(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is used to disable the menus to the actuator calibration   */
/* sequence when waiting for an event from the state machine.               */
/*                                                                          */
/****************************************************************************/ 
{
   UpdateKeyMask(DISABLESEL3);
}

void EnableWelding(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the Horn Scan submenu is      */
/* removed.                                                                 */
/*                                                                          */
/****************************************************************************/
{
   if(HSNotStarted == FALSE){
      HSNotStarted = TRUE;
      ResetStateMachine();
      StartStateMachine();
      SetReady();
      DUPSOkFlag = TRUE; 
      UpdateKeyMask(WELDMODEMASK); 
   }      
}


BOOLEAN DigitalPotEntry(void)
/****************************************************************************/
/*                                                                          */
/* Tests for READY state before entering Digital Pot adjustment screen.  If */
/* system is READY, turns off state machine to make sure it stays that way, */
/* returns TRUE.  If not ready, returns FALSE. Also sets up the following:  */
/*                                                                          */
/*    OrigDigTuneFlag - Zero if Digital Tune was off when selected           */
/*    DigTuneValue - Current pot position. This is what user will edit       */
/*    OrigDigTuneValue - Pot position when Digital Tune selected             */
/*                                                                          */
/****************************************************************************/
{
   SINT32  CurrentDigTune;
   UINT32  FreqAtCenter;
   BOOLEAN DoDigTune;

   /* Must disable interrupts here or system could go to "not ready" */
   /* between test of ready flag and shutdown of state machine. */
   if (!GetReadyStatus())
      DoDigTune = FALSE;

   else {
      StopStateMachine();
      DoDigTune = TRUE;
      ReadyFlag = TRUE; /* Kludge: System needs to "think" it is READY */
      /* (or it won't run Test, etc) although hardware */
      /* output should say it isn't. */

      OrigDigTuneFlag = CurrentSetup.DigTuneFlag & BIT0;

      if (OrigDigTuneFlag) /* If not in use now, orig */
         CurrentDigTune = CurrentSetup.DigTune; /* position is "centered" */
      else
         CurrentDigTune = 0;

      /* Compute here the current start frequency and min/max range. */
      /* Range of values for CurrentSetup.DigTune is the same for all */
      /* power supplies to make use easier, but this means that here */
      /* we need to check power supply type to determine frequency.  */

      FreqAtCenter = GetPowerSupplyFrequency();

      switch (CurrentSetup.PSFreq) {
      case FREQ20KHZ:
         DigTuneValue = CurrentDigTune / 6 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 499;
         MaxDigTuneValue = FreqAtCenter + 500;
         break;
      case FREQ15KHZ:
         DigTuneValue = CurrentDigTune / 8 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 374;
         MaxDigTuneValue = FreqAtCenter + 375;
         break;
      case FREQ30KHZ:
         DigTuneValue = CurrentDigTune / 4 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 749;
         MaxDigTuneValue = FreqAtCenter + 750;
         break;
      case FREQ60KHZ:
         DigTuneValue = CurrentDigTune / 2 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 1499;
         MaxDigTuneValue = FreqAtCenter + 1500;
         break;
      case FREQ40KHZ:
      default:
         DigTuneValue = CurrentDigTune / 3 + FreqAtCenter;
         MinDigTuneValue = FreqAtCenter - 999;
         MaxDigTuneValue = FreqAtCenter + 1000;
         break;
      }
      OrigDigTuneValue = DigTuneValue;
   }
   return (DoDigTune);
}

UINT8 DigTunePressTest(void)
/****************************************************************************/
/*                                                                          */
/* Implements the screen that forces the user to press Test after changing  */
/* the position of the digital pot.                                         */
/*                                                                          */
/* Return: Key used to exit Test screen (GoBack, Main, Run, etc). If ESTOP  */
/*         caused exit from "Press Test To Confirm" screen, then return     */
/*         value will be zero.                                              */
/*                                                                          */
/****************************************************************************/
{
   UINT8    NewKey;
   UINT8    ExitFlag;

   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;

   BOOLEAN   DidTest;
   UINT8     ExitKey;
   BOOLEAN   JumpMenu;
   BOOLEAN  EstopHappened;          /* Need this to escape screen on ESTOP */

   EstopHappened = FALSE;

   MenuCounter++;

   SaveLine1[VF_DEVICE] = 1;
   SaveLine1[TERM_DEVICE] = 1;

   SaveSelectKey1 = 1;
   SaveSingleSelect = 1;

   UpdateLED(OFFLED, OFF);

   ExitFlag = FALSE;

   while (ExitFlag != TRUE) {
      NewKey = GetMsg(TRUE);

      switch (NewKey) {
      case TestKey:
         JumpMenu = DoTestMode(&ExitKey, &DidTest);

            ExitFlag = TRUE;                 /* Always exiting */

            if (!JumpMenu)             /* Fill in key for this case */
               ExitKey = GoBackKey;

            break;

         case ResetKey:
            break;         /* Should never happen */

         case ESTOPMSGON:
            ShowEstopMessageOn();
            EstopHappened = TRUE;
            break;

         case ESTOPMSGOFF:
            ShowEstopMessageOff();
            EstopHappened = TRUE;
            break;

            /* If ESTOP pushed & released, UPDATEDISPLAY will be sent */
            /* here, use this as cue to get out. */

         case UPDATEDISPLAY:
            if (EstopHappened)
            {
               ExitFlag = TRUE;
               ExitKey = 0;
            }
            break;

         default:
            if (NewKey > FIRSTCONTROLMESSAGE)  /* Try to process */
               ProcessControlMessage( NewKey );
            else
               Beep(ERRORBEEP);  /* Inappropriate keypress, beep */
            break;

      }
   }
   MenuCounter--;
   return( ExitKey );
}



void DigitalPotChoiceDone(void)
/****************************************************************************/
/*                                                                          */
/* This function is called after the user has selected On or Off for        */
/* Digital Tune (or may have opted to leave original value via GoBack).  If */
/* user turned Digital Tune On, submenu has already been displayed at this  */
/* point, and it took care of turning the state machine back on.  This      */
/* function needs to take action only if current setting is Off.  If it was */
/* originally Off, just restart state machine.  If it was originally On,    */
/* user will be forced to press the Test key.                               */
/*                                                                          */
/* One exception: May have been On, user selected & hit GoBack.  In this    */
/* case, setting is On but submenu wasn't displayed.  Here just re-enable   */
/* state machine.                                                           */
/*                                                                          */
/****************************************************************************/
{
   UINT8   ExitKey;
   UINT32  FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   if (!(CurrentSetup.DigTuneFlag & BIT0))  /* If now Off ... */
   {
      /* If was originally On and DigTune changed, make */
      /* user push Test key */

      if (OrigDigTuneFlag && (FreqAtCenter != (UINT32)OrigDigTuneValue))
      {
         CenterDigTune();
         CurrentSetup.DigTune = 0;
         UpdateCurrentPreset( DIGITALFREQ, CurrentSetup.DigTune, TRUE );

         ExitKey = DigTunePressTest();  /* Make 'em press Test */

         if (ExitKey && (ExitKey != GoBackKey))
         {
            MainKeyFlag = TRUE;  /* Causes return to Main Menu */

            if (ExitKey != MainKey)  /* From there, go to right place */
            {
               SendFakeKeyPress( (KEY_CODE_TYPE)ExitKey );
               BlankMenuCounter = 1;      /* Block display of Main Menu */
            }
         }
      }
      else     /* No change, just allow welding & go */
      {
         ResetStateMachine();
         StartStateMachine();
      }
   }
   else if (!CheckStateMachine())
   {
      ResetStateMachine();   /* Covers On + GoBack case and anything */
      StartStateMachine();   /* else we haven't thought of. */
   }
}



BOOLEAN DigitalFreqEntry(void)
/****************************************************************************/
/*                                                                          */
/* This function is called before the user can select the Start Frequency   */
/* item on the Digital Tune entry screen.  It makes sure system is in READY */
/* before item can be selected, then stops state machine.                   */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN AllowSelect;

   /* Must disable interrupts here or system could go to "not ready" */
   /* between test of ready flag and shutdown of state machine. */
   if (!GetReadyStatus())
      AllowSelect = FALSE;

   else {
      if (CheckStateMachine()) /* Will be running if user already */
      { /* tested first value, is now about to */
         StopStateMachine(); /* try another one. */
         ReadyFlag = TRUE; /* Kludge, see comment at similar one above */
      }
      AllowSelect = TRUE;
   }
   return (AllowSelect);
}

void DigTuneStore(void)
/****************************************************************************/
/*                                                                          */
/* Converts Start Frequency entered by user back into digital pot position  */
/* for storage in the CurrentSetup.  Note that this function runs after     */
/* the call to UpdateCurrentPreset(), so DigitalFrequency had to have       */
/* ID of XXCANTCHANGE so that UpdateCurrentPreset() wouldn't be called and  */
/* passed the wrong value.  Here UpdateCurrentPreset() called directly.     */
/*                                                                          */
/****************************************************************************/
{
   SINT32 FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq) {
   case FREQ20KHZ:
      CurrentSetup.DigTune = (DigTuneValue - FreqAtCenter) * 6;
      break;
   case FREQ15KHZ:
      CurrentSetup.DigTune = (DigTuneValue - FreqAtCenter) * 8;
      break;
   case FREQ30KHZ:
      CurrentSetup.DigTune = (DigTuneValue - FreqAtCenter) * 4;
      break;
   case FREQ60KHZ:
      CurrentSetup.DigTune = (DigTuneValue - FreqAtCenter) * 2;
      break;
   case FREQ40KHZ:
   default:
      CurrentSetup.DigTune = (DigTuneValue - FreqAtCenter) * 3;
      break;
   }

   UpdateCurrentPreset( DIGITALFREQ, CurrentSetup.DigTune, TRUE );
}

void VarDigTuneStore(void)
{
   DigTuneStore();
   if (IsHWConfigured(VGA))
      VGACheckDigitalTune();
}




void DebugReadMemory(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will be called when a value has been entered in the Debug  */
/*  entry in the DIAG menu.  It will read memory from the location specified */
/*  and format it for display in the submenu which it will call.             */
/*                                                                           */
/*  The formated output for base 16 and 2 bytes will be:                     */
/*      DebugText1:   00:    xxxx     xxxx                                   */
/*      DebugText2:   04:    xxxx     xxxx                                   */
/*      DebugText3:   08:    xxxx     xxxx                                   */
/*      DebugText4:   0C:    xxxx     xxxx                                   */
/*                                                                           */
/*  where:  xx is a 2-digit hex value for each byte                          */
/*                                                                           */
/*****************************************************************************/
{
   UINT32 Value, *Ptr, Mask;
   UINT8  QuickListFlag = FALSE;
   UINT8  i, Offset, Shift, *Tmp;
   UINT8  Base, Width, LC, FirstByte;

   #define LOOP       2       /* Number of values/line         */
   #define SPACING    9       /* Max # of digits/value + space */

   TempDebugPtr = DebugPtr;
/* First validate entered range.  Only allow RAM and FRAM */

   if (DebugPtr < MAX_LIST_ENTRIES) {     /* Test for quick list entry */
      strncpy(DebugTitle, QuickList[DebugPtr].TextPtr, VGA_LINESIZE -  1);
      DebugBase = QuickList[DebugPtr].Base;
      DebugBytes = QuickList[DebugPtr].Size;
      DebugPtr = (SINT32)QuickList[DebugPtr].MemPtr;
      QuickListFlag = TRUE;
   }
   else
   /* Bring Debug pointer to the even address*/
   DebugPtr = DebugPtr - (DebugPtr%2);
   
   if(DebugBase == BINARY ){
      HexEnable = FALSE;
      BinEnable = TRUE;
   }
   else{
      HexEnable = TRUE;
      BinEnable = FALSE;
   }

   if (((DebugPtr >= START_OF_RAM) && (DebugPtr <= END_OF_RAM))
        || (DebugPtr >=(SINT32)FRAM1200_SYSTEM_START)) {

/* Create title line */
      if (QuickListFlag == FALSE) {
         strcpy(DebugTitle, DebugAddr);
         Numout((UINT32)DebugPtr, 16, '0', &DebugTitle[5], 6);  
      }
      
/* Now setup variables for either hex, decimal or binary */
      switch (DebugBase) {
         case HEX:
         default:
            LC = '0';                      /* display leading zeros */
            Base = 16;
            break;

         case DECIMAL:
            LC = ' ';                      /* no leading zeros displayed */
            Base = 10;
            break;
            
         case BINARY:
            LC = '0';                      /* leading zeros displayed */
            Base = 2;
            break;
            
      }  

      strcpy(DebugText1, Debug00);
      Ptr = (UINT32*)DebugPtr;
      switch (DebugBytes) {
         case TRUE:              /* 2 bytes */
         default:
            Mask = 0xffff0000;
            Shift = 16;
            if (DebugBase == HEX) Width = 4;       /* 4 digits/byte for Hex     */
            else if (DebugBase == BINARY) Width=8; /* 8 digits/byte for binary  */
            else Width = 5;                        /* 5 digits/byte for decimal */
            strcpy(DebugText2, Debug04);
            strcpy(DebugText3, Debug08);
            strcpy(DebugText4, Debug0A);
            break;
         
         case FALSE:             /* 4 bytes */
            Mask = 0xffffffff;
            Shift = 0;
            Width = 8;                          /* 8 digits per byte */
            strcpy(DebugText2, Debug08);
            strcpy(DebugText3, Debug10);
            strcpy(DebugText4, Debug18);
            break;
         
      }   
      FirstByte = 4;       			/* Start first output here:Point to 00: and have a space*/
      Offset = FirstByte;           /* Handle line 1 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL){
        	 Offset += Numout2((UINT32)Value, Base, &DebugText1[Offset], Width);
         }
         else{
        	 Numout((UINT32)Value, Base, LC, &DebugText1[Offset], Width);
        	 Offset += Width;//Jump Max width formatted by NumOut for Value
         }
         DebugText1[Offset] = ' ';//A space before second value on display
         Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
      
      Offset = FirstByte;           /* Handle line 2 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL)
             Offset += Numout2((UINT32)Value, Base, &DebugText2[Offset], Width);
         else{
        	 Numout((UINT32)Value, Base, LC, &DebugText2[Offset], Width);
        	 Offset += Width;//Jump Max width formatted by NumOut for Value
         }
         DebugText2[Offset] = ' ';//A space before second value on display
         Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
   
      Offset = FirstByte;           /* Handle line 3 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL)
             Offset += Numout2((UINT32)Value, Base, &DebugText3[Offset], Width);
         else{
        	 Numout((UINT32)Value, Base, LC, &DebugText3[Offset], Width);
        	 Offset += Width;//Jump Max width formatted by NumOut for Value
         }
         DebugText3[Offset] = ' ';//A space before second value on display
         Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
   
      Offset = FirstByte;           /* Handle line 4 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL)
			 Offset += Numout2((UINT32)Value, Base, &DebugText4[Offset], Width);
		 else{
			 Numout((UINT32)Value, Base, LC, &DebugText4[Offset], Width);
			 Offset += Width;//Jump Max width formatted by NumOut for Value
		 }
		 DebugText4[Offset] = ' ';//A space before second value on display
		 Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
      if(IsHWConfigured(VGA))
         VGADebugDataFlag = TRUE;
   }
   else {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = REFRESH_MENU;
      ErrorResponseMaxLimit = 0;
   }
}

void ChangeBaseAndWordLength(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will be called when a value of a memory location has to     */
/*  display in either hex or decimal and also word length either in four     */
/*  bytes or in eight bytes.                                                 */
/*                                                                           */
/*****************************************************************************/
{
   UINT32 Value, *Ptr, Mask;
   UINT8  i, Offset, Shift, *Tmp;
   UINT8  Base, Width, LC, FirstByte;

   if (((DebugPtr >= START_OF_RAM) && (DebugPtr <= END_OF_RAM)) 
        || (DebugPtr >=(SINT32)FRAM1200_SYSTEM_START)) {
      if(TempDebugPtr <= 15){ //coverity fix
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      else{
      /* Now setup variables for either hex, decimal or binary */
      switch (DebugBase) {
         case HEX:
         default:
            LC = '0';                      /* display leading zeros */
            Base = 16;
            break;

         case BASE10:
            LC = ' ';                      /* no leading zeros displayed */
            Base = 10;
            break;
            
         case BINARY:
            LC = '0';                      /* leading zeros displayed */
            Base = 2;
            break;
            
      }  

      strcpy(DebugText1, Debug00);
      Ptr = (UINT32*)DebugPtr;

      switch (DebugBytes) {
         case TRUE:              /* 2 bytes */
         default:
            Mask = 0xffff0000;
            Shift = 16;
            if (DebugBase == HEX) Width = 4;       /* 4 digits/byte for Hex     */
            else if (DebugBase == BINARY) Width=8; /* 8 digits/byte for binary  */
            else Width = 5;                        /* 5 digits/byte for decimal */
            strcpy(DebugText2, Debug04);
            strcpy(DebugText3, Debug08);
            strcpy(DebugText4, Debug0A);
            break;
         
         case FALSE:             /* 4 bytes */
            Mask = 0xffffffff;
            Shift = 0;
            Width = 8;                          /* 8 digits per byte */
            strcpy(DebugText2, Debug08);
            strcpy(DebugText3, Debug10);
            strcpy(DebugText4, Debug18);
            break;
         
      }   
      FirstByte = 4;       			/* Start first output here:Point to 00: and have a space*/
	  Offset = FirstByte;           /* Handle line 1 output here */
	  for (i=0; i<LOOP; i++) {
		Value = *Ptr;              /* Always read 4 bytes         */
		Value = (Value & Mask);    /* Strip off what not needed   */
		Value = (Value >> Shift);  /* Shift what left for display */
		if(DebugBase == DECIMAL){
		 Offset += Numout2((UINT32)Value, Base, &DebugText1[Offset], Width);
		}
		else{
		 Numout((UINT32)Value, Base, LC, &DebugText1[Offset], Width);
		 Offset += Width;//Jump Max width formatted by NumOut for Value
		}
		DebugText1[Offset] = ' ';//A space before second value on display
		Offset += 1;
		if (DebugBytes == TRUE) {
		   Tmp = (UINT8 *)Ptr;
		   Tmp += 2;
		   Ptr = (UINT32 *)Tmp;
		}
		else Ptr++;
	  }
      
      Offset = FirstByte;           /* Handle line 2 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL)
             Offset += Numout2((UINT32)Value, Base, &DebugText2[Offset], Width);
         else{
        	 Numout((UINT32)Value, Base, LC, &DebugText2[Offset], Width);
        	 Offset += Width;//Jump Max width formatted by NumOut for Value
         }
         DebugText2[Offset] = ' ';//A space before second value on display
         Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
   
      Offset = FirstByte;           /* Handle line 3 output here */
	  for (i=0; i<LOOP; i++) {
		 Value = *Ptr;              /* Always read 4 bytes         */
		 Value = (Value & Mask);    /* Strip off what not needed   */
		 Value = (Value >> Shift);  /* Shift what left for display */
		 if(DebugBase == DECIMAL)
			 Offset += Numout2((UINT32)Value, Base, &DebugText3[Offset], Width);
		 else{
			 Numout((UINT32)Value, Base, LC, &DebugText3[Offset], Width);
			 Offset += Width;//Jump Max width formatted by NumOut for Value
		 }
		 DebugText3[Offset] = ' ';//A space before second value on display
		 Offset += 1;
		 if (DebugBytes == TRUE) {
			Tmp = (UINT8 *)Ptr;
			Tmp += 2;
			Ptr = (UINT32 *)Tmp;
		 }
		 else Ptr++;
	  }

      Offset = FirstByte;           /* Handle line 4 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         if(DebugBase == DECIMAL)
			 Offset += Numout2((UINT32)Value, Base, &DebugText4[Offset], Width);
		 else{
			 Numout((UINT32)Value, Base, LC, &DebugText4[Offset], Width);
			 Offset += Width;//Jump Max width formatted by NumOut for Value
		 }
		 DebugText4[Offset] = ' ';//A space before second value on display Coverity 12215
		 Offset += 1;
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
      }
     }
   }
}


void IoTestData(UINT8 ExtraData){
   DigTuneValue= (UINT32)ExtraData;
}

void UpdateFrequencyResonance(void)
/*****************************************************************************/
/* This function will update the strings for resonance frequency depends on  */
/* the Series & Parallel type.                                               */
/*****************************************************************************/
{
   UINT16 i;
   for (i=0;i<DUPS_NUMRESONANCES;i++)
   {
      if(HornScanInfo.ResonanceFreqs[i] != 0)
      {
         ResonanceFreqEnable[i] = TRUE;/* Display the frequency variable on the screen. */
         if(HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES )
         /* Display 'Series F(Hz) = XXXXX'*/
            FreqType[i] = 2;
         else if(HornScanInfo.ResonanceFreqType[i] == FREQ_PARALLEL )
         /* Display 'Parallel F(Hz) = XXXXX'*/
            FreqType[i] = 1;
         else if(HornScanInfo.ResonanceFreqType[i] == FREQ_NONE )
            FreqType[i] = 0;
      }
   }
}
