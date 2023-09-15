/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menutest.cpp_v   1.9   28 Nov 2014 07:38:46   rjamloki  $ */
/****************************************************************************/ 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menutest.cpp_v  $
 * 
 *    Rev 1.9   28 Nov 2014 07:38:46   rjamloki
 * changed to remove warning "unused variable".
 * 
 *    Rev 1.8   06 Oct 2014 06:40:26   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.7   03 Oct 2014 06:02:44   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.6   11 Jun 2014 11:57:42   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.5   21 May 2014 03:34:02   rjamloki
 * extern variables clean up and coverity fixes
 * 
 *    Rev 1.4   14 Apr 2014 09:39:58   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.3   05 Mar 2014 13:56:34   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:40   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
   ---------------------------- MODULE DESCRIPTION --------------------------

   Module name: menutest.c

   Filename:

   Function name:

  ----------------------------- INCLUDE FILES ------------------------------*/

#include <string.h>
#include "portable.h"
#include "menu.h"
#include "param.h"
#include "preset.h"
#include "mansensr.h"
#include "keypad.h"
#include "fpled.h"
#include "beep.h"
#include "genrlmsg.h"
#include "getmsg.h"
#include "state.h"
#include "statedrv.h"
#include "opcodes.h"

#include "display.h"
#include "selctkey.h"
#include "menutest.h"
#include "menu7a.h"
#include "WeldManagerTask.h"

/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT16 LangIndex;
extern SINT32 FMemoryBargraph;
extern SINT32 FActualBargraph;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern INBITS Inp;

#define DIAGUPDATE 250
#define VGADIAGUPDATE 500

/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                       (scope is global to THIS file)                     */

UINT8 VGALatchPSStore = FALSE;
static SINT8 * TestBuffer1[LANGUAGE_MAX];    /* initialized to 0 by startup */

static GENERIC_MSG WeldMsgOut;

static SINT16 DiagCountDown = 20;
static SINT16 DiagCountDown2 = 20;
static SINT32 FMemoryLatch = 0, FActualLatch = 0;

STR TestPowerBufName[VGA_LINESIZE];

STR *Str_TestPower[] =   { TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName };

STR TestFrequencyBufName[VGA_LINESIZE];

STR *Str_TestFrequency[] =   { TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName };

/*--------------------------- EXTERN FUNCTION PROTOTYPES --------------------*/
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

/*---------------------------------- CODE ----------------------------------*/

void UpdateTestAmp(void)
{
   SetCurrentAmp(CurrentPreset.TestAmp);  /* Output new value right now!   */
}   

/****************************************************************************/



static void UpdateTestLine(void)
{
   if (LangIndex < ASIAN_LANGUAGE_START)  //If not Asian Language
   {
   TestBuffer1[LangIndex][2] = LatchPSRun ? '|' : 0x7F;
   TestBuffer1[LangIndex][8] = LatchPSSeek ? '|' : 0x7F;
   TestBuffer1[LangIndex][13] = LatchPSClear ? '|' : 0x7F;
   TestBuffer1[LangIndex][19] = LatchPSStore ? '|' : 0x7F;
   if(VGALatchPSStore) TestBuffer1[LangIndex][19] = '|';
   }
   else
   {
      StrCpyTwoBytes(TestBuffer1[LangIndex], " ");
   }

}



void InitTestBuffers(void)
{
   int i;
   static STR * initvalues[] = {
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F"  };
   static STR testlinestorage[LANGUAGE_MAX][62];
   for (i = 0; i < LANGUAGE_MAX; i++)
      {
      TestBuffer1[i] = testlinestorage[i];
      strncpy(TestBuffer1[i], initvalues[i], sizeof(testlinestorage[0]) - 1);
      }
}



BOOLEAN DoTestMode( UINT8 *ExitKey, BOOLEAN *DidTest )
/****************************************************************************/
/*                                                                          */
/* This function implements Test Mode.  Returns TRUE if system should       */
/* jump to another menu due to a Run, Main, Print, or Setup keypress.       */
/* The key pressed will be returned in ExitKey.  If Test Mode terminated by */
/* GoBack, FALSE will be returned, and previous menu should be displayed.   */
/*                                                                          */
/* On exit, DidTest will be TRUE unless routine terminated immediately due  */
/* to welder not ready.                                                     */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN  RetVal = FALSE;
   DidTest = NULL;
   ExitKey = NULL;
   return(RetVal);
}



void VGAExitTestSequence(void)
/***************************************************************************/
/*Description:                                                             */
/* Exit from the Test sequence.                                            */
/***************************************************************************/
{
  if (CurrentSequence == TESTMODE)    /* Still in test state */
  {
    WeldMsgOut.common.opcode = OP_STOP_TEST;
        WeldManagerTask::thisPtr->WELDMNGRTaskQ.WriteRetry(0, *((WMGR_MSG_QUEUE_TYPE*) &WeldMsgOut), 50);
  }       
}



void UpdateDiagScreen(void){

   BOOLEAN Changed1 = FALSE;
   BOOLEAN Changed2 = FALSE;
   

   if ((Inp.PSRun == TRUE) && (LatchPSRun == FALSE)) {
      LatchPSRun = TRUE;
      Changed1 = TRUE;
   }   
   else if ((Inp.PSRun == FALSE) && (LatchPSRun == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSRun = FALSE;
         Changed2 = TRUE;
      }
   }

   if ((Inp.PSSeek == TRUE) && (LatchPSSeek == FALSE)) {
      LatchPSSeek = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSSeek == FALSE) && (LatchPSSeek == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSSeek = FALSE;
         Changed2 = TRUE;
      }
   }
   
   if ((Inp.PSClear == TRUE) && (LatchPSClear == FALSE)) {
      LatchPSClear = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSClear == FALSE) && (LatchPSClear == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSClear = FALSE;
         Changed2 = TRUE;
      }
   }
   
   if ((Inp.PSStore == TRUE) && (LatchPSStore == FALSE)) {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSStore == FALSE) && (LatchPSStore == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSStore = FALSE;
         Changed2 = TRUE;
      }   
   }

/* Now need to check FMemoryBargraph and FActualBargraph for changes */

   if (--DiagCountDown2 <= 0) {
      if(CurrentSetup.VGAHWPresent)
         DiagCountDown2 = VGADIAGUPDATE;
      else
         DiagCountDown2 = DIAGUPDATE;
         
      if (FMemoryBargraph != FMemoryLatch) {
         FMemoryLatch = FMemoryBargraph;
         Changed1 = TRUE;
      }

      if (FActualBargraph != FActualLatch) {
         FActualLatch = FActualBargraph;
         Changed1 = TRUE;
      }
   }
   
   if (Changed1 == TRUE) {
      if(CurrentSetup.VGAHWPresent)
         DiagCountDown = VGADIAGUPDATE;
      else
      {   
         DiagCountDown = DIAGUPDATE;
         UpdateTestLine();
         SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update */
      }   
   }
   else if (Changed2 == TRUE) {
      if (!CurrentSetup.VGAHWPresent)
      {
         UpdateTestLine();
         SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update */
      }
   }
}

