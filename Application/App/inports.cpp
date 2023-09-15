/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/inports.cpp_v   1.31   26 Oct 2015 10:32:36   LMarkure  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/inports.cpp_v  $
 * 
 *    Rev 1.31   26 Oct 2015 10:32:36   LMarkure
 * Added buffer for external seek input, deleted unused code
 * 
 *    Rev 1.30   16 Apr 2015 07:22:28   rjamloki
 * Debounce input buffer initialization moved to InitMonitorInputPorts function
 * 
 *    Rev 1.29   08 Apr 2015 13:43:04   AnPawar
 * Removed warning for incorrect comment format.
 * 
 *    Rev 1.28   30 Mar 2015 05:53:42   rjamloki
 * Dooropen removed
 * 
 *    Rev 1.27   16 Mar 2015 07:04:38   rjamloki
 * Renamed RejectAlarmConfirm to ConfirmReject. FIx for estop on IMI boards.
 * 
 *    Rev 1.26   03 Mar 2015 15:36:48   rjamloki
 * Second estop pole is checked for non AE actuator only
 * 
 *    Rev 1.25   11 Feb 2015 06:30:52   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.24   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.23   02 Jan 2015 04:03:16   rjamloki
 * changes related to e_stop new hardware
 * 
 *    Rev 1.22   28 Nov 2014 07:35:58   rjamloki
 * initialized the arguments to zero.
 * 
 *    Rev 1.21   10 Nov 2014 04:50:16   AnPawar
 * Removed CPLD extern.Removed QReadyFlag and check associated with it.
 * 
 *    Rev 1.20   06 Oct 2014 06:34:20   AnPawar
 * removed FrontPanelKeypadTask.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.19   03 Oct 2014 05:57:58   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.18   26 Sep 2014 03:14:24   rjamloki
 * Removed psos references
 * 
 *    Rev 1.17   18 Aug 2014 01:39:42   rjamloki
 * Added support for AE trigger
 * 
 *    Rev 1.16   28 Jul 2014 12:36:40   rjamloki
 * psos.h removed
 * 
 *    Rev 1.15   09 Jul 2014 10:55:28   rjamloki
 * Removed printing flags. Added support for part present in GetInputData function
 * 
 *    Rev 1.14   11 Jun 2014 11:31:40   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.13   27 May 2014 10:12:40   amaurya
 * Minor cleanup
 * 
 *    Rev 1.12   21 May 2014 10:47:58   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.11   21 May 2014 03:07:16   rjamloki
 * Logic 1 check for signals read from fpga.
 * 
 *    Rev 1.10   07 May 2014 10:20:46   rjamloki
 * MonitorInputPorts() function changed.
 * 
 *    Rev 1.9   23 Apr 2014 13:50:02   akaushal
 * Checking Overload signal active high
 * 
 *    Rev 1.8   14 Apr 2014 09:57:56   rjamloki
 * Fixed memory store interrupt handler
 * 
 *    Rev 1.7   26 Mar 2014 12:18:00   rjamloki
 * GetInputData() function changed ,static PsosReturnValue variable removed.
 * 
 *    Rev 1.6   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:26   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:38   rjamloki
 * Preset changes to support 1000 preset.
 *
 *    Rev 1.3   03 Jan 2014 08:45:28   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------


 ------------------------------- DESCRIPTION -----------------------------------

 This routine monitors the input ports P0_IN and P1_IN and P2_IN.
 If a change is detected a message is sent to the ????
 manager which will act upon the change.  Currently 10 ms of debouncing
 is performed. This routine is called from the tick ISR.


 ------------------------------ INCLUDE FILES ----------------------------------
 */

#include "qdef.h"
#include "digout.h"
#include "inputs.h"                 /* typedefs for welder input ports      */
#include "inports.h"                /* function prototypes                  */
#include "preset.h"                 /* function prototypes                  */
#include "ready.h"
#include "alarms.h"
#include "fpled.h"
#include "outports.h"
#include "dups_api.h"
#include "dups.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "CPLD.h"
#include "keypad.h"
#include "CPU.h"
#include "A1025R.h"
#include "command.h"
#include "FrontPanelKeypadTask.h"
#include "statedrv.h"
#include "InputTask.h"
#include "psnvram.h"

/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT16 ExternalCycleAbortGoneFlag;
extern UINT16 ThermalOLFlag;
extern BOOLEAN ECycleHistFlag;
extern BOOLEAN IsGraphDrawing;
extern BOOLEAN DispLockConfigured;
extern BOOLEAN PartPresentConfigured;

UINT16 ExternalResetHistory;
UINT16 MemoryResetHistory = TRUE;

BOOLEAN HornScanOL = FALSE;
UINT8 AETrigger;
UINT16 MemoryResetFlag = FALSE;
UINT16 DUPS_WaitTimer = FALSE;
/*------------------------------ LOCAL DEFINES -----------------------------*/

#define SYS_STARTUP_PASS   0
#define SYS_STARTUP_FAIL   1
#define LEVEL2C            1
#define DEBOUNCE_TIME      5    /* Actual debounce time is DEBOUNCE_TIME    */
#define PDOWN_DEBOUNCE     50
#define PB_DEBOUNCE_TIME   0    /* Additional time for palm button debounce */
#define READY_CHECK_TIME        220
#define OLRESETTHRESHOLD 2000   /* Wait time before OL is considered thermal*/
/* This time includes the debounce time     */
/* This number is twice as big as desired because */
/* both PSReset() & GetInputData() increment the  */
/* counter (ThermalOLFlag) every ms.              */

/* The following definitions specify bits that are NOT debounced */

#define NO_DEBOUNCE_0      0x0F
#define NO_DEBOUNCE_1         0
#define NO_DEBOUNCE_2         0

#define MEMCLEAR_TIMEOUT     15
#define DUPS_WAIT_TIMEOUT    500
#define STATE_NONE            0
#define START_MEMRST          1
#define DOWNLOAD_DUPS         2
#define DUPS_WAIT_MEMCLR      3
#define ALG_WAIT_MEMCLR       4

/*------------------------- LOCAL TYPE DECLARATIONS ------------------------*/
void ProcessMemoryReset(void);
/*------------------------------ GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                      */

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                      (scope is global to THIS file)                      */

INPUT_PORT_P0_UNION_TYPE LastInputP0;
INPUT_PORT_P1_UNION_TYPE LastInputP1;
INPUT_PORT_P2_UNION_TYPE LastInputP2;
INPUT_PORT_P3_UNION_TYPE LastInputP3;
static UINT8 Port0[DEBOUNCE_TIME];
static UINT8 Port1[DEBOUNCE_TIME];
static UINT8 Port2[DEBOUNCE_TIME];
static UINT8 Port3[DEBOUNCE_TIME];
static UINT16 DebounceIndex = 0;
static UINT16 PBDebounceCounter = PB_DEBOUNCE_TIME;
static UINT16 PowerDownFudgeCounter = 0; /* Extra dbounce for pdown signal */

static BOOLEAN BothPBDebounceFlag = FALSE;
static BOOLEAN PSSeekOn = FALSE;         /* Added for external seek input */

BOOLEAN ReadyOK;
extern INBITS Inp;
ESTOP_STATE EStopState;
extern BOOLEAN PartClampActive;
extern enum WELDSTATES WeldState;
UINT16 MemoryResetState = STATE_NONE;

/*---------------------------------- CODE ----------------------------------*/

void MonitorInputPorts(void)
{
   UINT8 ANDResult0, ANDResult1, ANDResult2,ANDResult3;
   UINT8 ORResult0, ORResult1, ORResult2,ORResult3;
   UINT8 SameMask0, SameMask1, SameMask2,SameMask3;
   UINT8 CurrentPort0, CurrentPort1, CurrentPort2,CurrentPort3;
   UINT16 LocalIndex;

   /**  Get the current value of the input ports **/

   CurrentPort0 = Port0[DebounceIndex] = cpld->GetBuffer(0); /* Actually read the hardware */
   CurrentPort1 = Port1[DebounceIndex] = cpld->GetBuffer(1); /* ports right here.          */
   CurrentPort2 = Port2[DebounceIndex] = cpld->GetBuffer(2);
   CurrentPort3 = Port3[DebounceIndex] = cpld->GetBuffer(3);
   if (++DebounceIndex >= DEBOUNCE_TIME)
      DebounceIndex = 0;


   /* Bitwise debounce algorithm: AND last DEBOUNCE_TIME bytes together */
   /* from each port to create ANDResultx.  OR last DEBOUNCE_TIME bytes */
   /* to create ORResultx.  If a bit is the same in all samples, it will */
   /* be either 1 in ANDResult (all samples were 1) or 0 in ORResult */
   /* all samples were 0).  Complement the ORResult, now a 1-bit in */
   /* either mask corresponds to a bit that is the same in all samples. */
   /* OR together ANDResult and ~ORResult, we have a mask of all bits */
   /* that are the same in all samples. */

   /* Having done all that, now just use this mask to strip bits out of */
   /* LastInputPx.value and substitute the new bits from the port. */

   ANDResult0 = ORResult0 = Port0[0];
   ANDResult1 = ORResult1 = Port1[0];
   ANDResult2 = ORResult2 = Port2[0];
   ANDResult3 = ORResult3 = Port3[0];
   for (LocalIndex = 1; LocalIndex < DEBOUNCE_TIME; LocalIndex++) {
      ANDResult0 &= Port0[LocalIndex];
      ANDResult1 &= Port1[LocalIndex];
      ANDResult2 &= Port2[LocalIndex];
      ANDResult3 &= Port3[LocalIndex];
      ORResult0 |= Port0[LocalIndex];
      ORResult1 |= Port1[LocalIndex];
      ORResult2 |= Port2[LocalIndex];
      ORResult3 |= Port3[LocalIndex];
   }

   SameMask0 = ANDResult0 | (~ORResult0) | NO_DEBOUNCE_0;
   SameMask1 = ANDResult1 | (~ORResult1) | NO_DEBOUNCE_1;
   SameMask2 = ANDResult2 | (~ORResult2) | NO_DEBOUNCE_2;
   SameMask3 = ANDResult3 | (~ORResult3) | NO_DEBOUNCE_2;

   LastInputP0.value = (LastInputP0.value & (~SameMask0)) | (CurrentPort0 & SameMask0);
   LastInputP1.value = (LastInputP1.value & (~SameMask1)) | (CurrentPort1 & SameMask1);
   LastInputP2.value = (LastInputP2.value & (~SameMask2)) | (CurrentPort2 & SameMask2);
   LastInputP3.value = (LastInputP3.value & (~SameMask3)) | (CurrentPort3 & SameMask3);
}

/*--------------------------- MODULE DESCRIPTION ---------------------------

 Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

 Revision #      Date          Author      Description
 ==========      ========      ======      ===========
 0             12/22/95      Mark L      Initial

 ------------------------------- DESCRIPTION -----------------------------------
 init routine for this function
 ------------------------------- PSEUDO CODE -----------------------------------
 initialize statics
 ---------------------------------- CODE ---------------------------------------
 */

UINT8 InitMonitorInputPorts(void)
{
   UINT32 Indx;
   UINT8 SysStartupStatus;

   /*---  Now begin the code...  ---*/

   SysStartupStatus = SYS_STARTUP_PASS; /* Always pass startup */

   /*---  Zeros will force a read the first time through  ---*/

   LastInputP0.value = 0;
   LastInputP1.value = 0;
   LastInputP2.value = 0;
   LastInputP3.value = 0;
   /*Estop_24 volt signal is active low for WC software and we have 10 ms of denouncing on digital input signals.
    Below initialization makes sure that we don't get false Estop indication at power up
    */
   if(NvRamData.EstopTwoPoleHW == TWO_POLE_ESTOP)
   {
	   for(Indx = 0; Indx < DEBOUNCE_TIME; Indx++)
			Port1[Indx] = BIT2;//fix for estop coming at power up for second pole of the estop
							   // BIT2 is the bit position for ESTOP second pole.
   }
   return (SysStartupStatus);
}

void GetInputData(INBITS * InputPort)
{

   FP_KEY_PRESSED_MSG FpkpQueue;

   /* Change Input status according to logic level selected in Custom menu. */
   if (LastInputP1.port.uls_signal == CurrentSetup.ULSLogicCustom) {
      InputPort->uls = TRUE;
   }
   else {
      InputPort->uls = FALSE;
   }

   /* once two palmbuttons pressed they must be lost for PB_DEBOUNCE_TIME */
   /* Need to wait for printing to be complete when External Presets = On */
   if ((IsGraphDrawing == FALSE) || (CurrentSetup.ExtPresets == FALSE)) {
      ReadyOK = TRUE;
      if ((LastInputP1.port.pb2_signal) && (LastInputP1.port.pb1_signal)) {
         InputPort->OnePB = TRUE;
         InputPort->BothPB = TRUE;
         BothPBDebounceFlag = TRUE;
         PBDebounceCounter = 0; /* reset counter */
      }
      else if ((LastInputP1.port.pb1_signal) || (LastInputP1.port.pb2_signal)) {
         InputPort->OnePB = TRUE;
         InputPort->BothPB = FALSE;
         PBDebounceCounter++; /* start counter */
      }
      else {
         InputPort->OnePB = FALSE;
         InputPort->BothPB = FALSE;
         PBDebounceCounter++; /* start counter */
      }

      if ((InputPort->BothPB == FALSE) && (BothPBDebounceFlag == TRUE) && (PBDebounceCounter <= PB_DEBOUNCE_TIME)) {
         InputPort->OnePB = TRUE;
         InputPort->BothPB = TRUE;
      }
      else {
         BothPBDebounceFlag = FALSE;
      }
   }
   else {
      /*--------------------------------------------------------------------------*/
      /* only allow PB's to go away, but not be pressed again  */
      /*--------------------------------------------------------------------------*/

      ReadyOK = FALSE;
      if ((LastInputP1.port.pb2_signal) && (LastInputP1.port.pb1_signal) && (InputPort->BothPB == TRUE)) {
      }
      else if (((LastInputP1.port.pb1_signal) || (LastInputP1.port.pb2_signal)) && (InputPort->OnePB == TRUE)) {
         InputPort->BothPB = FALSE;
      }
      else {
         InputPort->OnePB = FALSE;
         InputPort->BothPB = FALSE;
      }
   }

   if (CurrentSetup.Actuator == AE) {
       if (LastInputP1.port.e_stop2_signal)//This is trigger switch active in case of AE actuator
       {
          InputPort->Trigger = TRUE;
          AETrigger = TRUE;
          TrigSwInactv();
       }
       else
	   {
          AETrigger = FALSE;
       }
   }
   else{
      AETrigger = FALSE;
   }

   if (LastInputP0.port.power_on_signal)
      InputPort->PwrOn = TRUE;
   else
      InputPort->PwrOn = FALSE;

   if(LastInputP0.port.power_off_signal) {
      PowerDownFudgeCounter++;
      if (PowerDownFudgeCounter >= PDOWN_DEBOUNCE) {
         InputPort->PwrOff = TRUE;
      }
   }
   else /* As soon as it goes off, reset counter to zero */
   {
      PowerDownFudgeCounter = 0;
      InputPort->PwrOff = FALSE;
   }

	if (LastInputP0.port.mem_clear_signal)
		InputPort->PSClear = TRUE;
	else
		InputPort->PSClear = FALSE;

	if (LastInputP0.port.seek_signal)
		InputPort->PSSeek = TRUE;
	else
		InputPort->PSSeek = FALSE;
	if ((LastInputP3.port.ext_seek_signal == FALSE) && (PSSeekOn == FALSE)){ /*External seek received */
	   PSSeekOn = TRUE;
	   PSSeek();     /* Start seek */
	}
	else if((PSSeekOn == TRUE) && (LastInputP0.port.seek_signal == FALSE)){  /* If seek completed */
	   PSSeekOn= FALSE;
	   PSIdle();     /* Reset seek signal to DUPS power supply*/
	}

	if (LastInputP0.port.run_signal)
		InputPort->PSRun = TRUE;
	else
		InputPort->PSRun = FALSE;


   if (LastInputP0.port.overload_input_signal) {
      InputPort->OL = FALSE;
      ThermalOLFlag = FALSE;
   }
   else {
      PSReset(); /* Start reset process         */
      if (ThermalOLFlag != 0) {
         ThermalOLFlag++; /* Start counting, P/S is slow */
         if (ThermalOLFlag >= OLRESETTHRESHOLD) { /* If non zero then    */
            RecordAlarm(EQ7);
            /* reset was attempted */
            ThermalOLFlag = FALSE;
         }
      }
      InputPort->OL = TRUE;
      HornScanOL = TRUE; /* Set incase we are in a horn scan */

   }

   // if button pressed - set our flag as well
   //if(UserLoggedIn == TRUE)//Preventing ESTOP before user login
   {
	   if (LastInputP1.port.e_stop_signal
	   || ((NvRamData.EstopTwoPoleHW == TWO_POLE_ESTOP) && (CurrentSetup.Actuator != AE) && !LastInputP1.port.e_stop2_signal)
	   ) {
		  EStopState = ESTOPBTN_PRESSED;
		  EStopReset();
	   }
   }

   // if button is released and our flag was set - set flag to released
   // so internally it will still be active

   if ((!LastInputP1.port.e_stop_signal)
   && ((NvRamData.EstopTwoPoleHW == ONE_POLE_ESTOP) || ((NvRamData.EstopTwoPoleHW == TWO_POLE_ESTOP) && (CurrentSetup.Actuator != AE) && LastInputP1.port.e_stop2_signal))
   && (EStopState == ESTOPBTN_PRESSED))
      EStopState = ESTOPBTN_RELEASED;

   // someone turned Reset LED off somewhere else?
   if ((EStopState == ESTOPBTN_RELEASED) && (ResetLedRequiredState == FALSE))
      UpdateLED(RESETLED, ON);

   // set EStop to TRUE if our flag is pressed or released
   InputPort->Estop = (EStopState != ESTOPBTN_RESET);

   /* Change Input status according to logic level selected in Custom menu. */
   if (LastInputP1.port.ext_ls_signal == CurrentSetup.GndDetLogicCustom) {
      InputPort->GndDet = TRUE;
   }
   else {
	   InputPort->GndDet = FALSE;
   }

   if (LastInputP2.port.external_reset_signal){
		InputPort->ExternalReset = TRUE;
		if (ExternalResetHistory == FALSE) {
			ExternalResetHistory = TRUE;
			//         ResetReceivedFlag = TRUE;
			FpkpQueue.key = ResetKey;
			FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
			FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(0, *((FPKP_MSG_QUEUE_TYPE*) &FpkpQueue), 0);
		}
   }
   else {
      InputPort->ExternalReset = FALSE;
	  ExternalResetHistory = FALSE;
   }

   /* Change Input status according to logic level selected in UserI/O menu. */
   if (LastInputP2.port.ext_cycleabort_signal) {
      InputPort->ECycleAbort = TRUE;
   }
   else {
	  InputPort->ECycleAbort = FALSE;
   }
   /* Assign current value in actual flag for ECycleAbort.  */
   if (InputPort->ECycleAbort == TRUE)
      ECycleHistFlag = TRUE;
   if (InputPort->ECycleAbort == FALSE)
      ExternalCycleAbortGoneFlag = TRUE;

   /* Initialize all Configurable inputs. */
   InputPort->ExtTrgDelay = FALSE; /* In case this input is not configured currently.*/
   InputPort->DisplayLockFlag = FALSE;/* In case this input is not configured currently.*/
   InputPort->ExternalTrigger = FALSE;/* In case this input is not configured currently.*/
   InputPort->SonicDisable = FALSE; /* In case this input is not configured currently.*/
   InputPort->MemReset = FALSE; /* In case this input is not configured currently.*/
   InputPort->PartClamped = FALSE; /* In case this input is not configured currently.*/
   InputPort->SyncIn = FALSE; /* In case this input is not configured currently.*/
   InputPort->Preset1 = 0; /* In case J3_32 port assigned to PresetCode */
   InputPort->Preset2 = 0; /* In case J3_33 port assigned to PresetCode */
   InputPort->Preset4 = 0; /* In case J3_19 port assigned to PresetCode */
   InputPort->Preset8 = 0; /* In case J3_17 port assigned to PresetCode */
   InputPort->Preset16 = 0; /* In case J3_31 port assigned to PresetCode */
   InputPort->PartPresent = FALSE;
   InputPort->ConfirmReject = FALSE;


   if (CurrentSetup.UserInLogic) {
      /******* Read J3-32  ******/
      if (!LastInputP2.port.J3_32_signal)
         *CurrentSetup.J3_32Ptr = TRUE;

      /******* Read J3-33  ******/
      if (!LastInputP2.port.J3_33_signal)
         *CurrentSetup.J3_33Ptr = TRUE;

      /******* Read J3-19  ******/
      if (!LastInputP2.port.J3_19_signal)
         *CurrentSetup.J3_19Ptr = TRUE;

      /******* Read J3-17  ******/
      if (!LastInputP0.port.J3_17_signal)
         *CurrentSetup.J3_17Ptr = TRUE;

      /******* Read J3-31  ******/
      if (!LastInputP2.port.J3_31_signal)
         *CurrentSetup.J3_31Ptr = TRUE;

      /******* Read J3-1  ******/
      if (!LastInputP2.port.J3_1_signal)
         *CurrentSetup.J3_1Ptr = TRUE;

      if (DispLockConfigured) {
         if (InputPort->DisplayLockFlag)
            InputPort->DisplayLockFlag = FALSE;
         else
            InputPort->DisplayLockFlag = TRUE;
      }
      else
         InputPort->DisplayLockFlag = FALSE;
   }
   else {
      /******* Read J3-32  ******/
      if (LastInputP2.port.J3_32_signal)
         *CurrentSetup.J3_32Ptr = TRUE;

      /******* Read J3-33  ******/
      if (LastInputP2.port.J3_33_signal)
         *CurrentSetup.J3_33Ptr = TRUE;

      /******* Read J3-19  ******/
      if (LastInputP2.port.J3_19_signal)
         *CurrentSetup.J3_19Ptr = TRUE;

      /******* Read J3-17  ******/
      if (LastInputP0.port.J3_17_signal)
         *CurrentSetup.J3_17Ptr = TRUE;

      /******* Read J3-31  ******/
      if (LastInputP2.port.J3_31_signal)
         *CurrentSetup.J3_31Ptr = TRUE;

      /******* Read J3-1  ******/
      if (LastInputP2.port.J3_1_signal)
         *CurrentSetup.J3_1Ptr = TRUE;
   }

   /*---------------------------------------------------------------------------*/
   /* Here deal with single start inputs.  Look at the system configuration     */
   /* variable ????????.  Until V9.0 just set it equal to (OnePB OR Ext trig)   */
   /*    BIT0:  set SingleStart = OnePB                                         */
   /*    BIT1:  set SingleStart = Trigger                                       */
   /*    BIT2:  set SingleStart = ExternalTrigger                               */
   /*                                                                           */
   /*---------------------------------------------------------------------------*/

   InputPort->SingleStart = (InputPort->OnePB || InputPort->ExternalTrigger);

   if (CurrentSetup.HandHeld == TRUE) {
      InputPort->Trigger = FALSE;
      InputPort->uls = TRUE;
      AETrigger = InputPort->SingleStart; /* This allow CheckForTriggeLost to work */
   }

   /* Read each input and  assign the proper value in the PresetCode variable.*/
   Inp.PresetCode = 0; /* Start with all zeros */
   if (InputPort->Preset1)
      InputPort->PresetCode |= BIT0;
   if (InputPort->Preset2)
      InputPort->PresetCode |= BIT1;
   if (InputPort->Preset4)
      InputPort->PresetCode |= BIT2;
   if (InputPort->Preset8)
      InputPort->PresetCode |= BIT3;
   if (InputPort->Preset16)
      InputPort->PresetCode |= BIT4;

   /* This input is edge triggered. Send the Reset signal to the power supply
    on the falling edge of this input.*/
   if (InputPort->MemReset) {
      MemoryResetHistory = FALSE;
   }
   else if (MemoryResetHistory == FALSE) {
      MemoryResetHistory = TRUE;
      if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) && (MemoryResetState == STATE_NONE))
         MemoryResetState = START_MEMRST;
   }
   if (MemoryResetState != STATE_NONE)
      ProcessMemoryReset();

   if (!InputPort->SyncIn && InputPort->Trigger)
      UserCfgOutputOff(OUTPUT_SYNC_OUT); /* Make output high if Inp.SyncIn is true and */
   else
      /* actuator is triggered.                     */
      UserCfgOutputOn(OUTPUT_SYNC_OUT);

   /* if PartClamp feature is not available Make Inp.PartClamped = TRUE
    between 'WaitSV state to Hold state . */
   if (PartClampActive == FALSE)
      InputPort->PartClamped = TRUE;

   ///In case the Part present input is not configured currently.
	//Making PartPresent true so that state machine does not get
   //affected if the part present is not configured and We can
	//use Inp.PartPresent check is sub states where ever required.
   //If it is configured its value will be according to user input.
   if(PartPresentConfigured == FALSE)
	   InputPort->PartPresent = TRUE;
}


/****************************************************************************
  Description:
  This is the external interrupt handler for memory store signal asserted by
  DUPS
****************************************************************************/
void MemStoreIntHandler(int vector, void * frame)
{
   CPU::DisableExternalInterrupt(MEMSTORE_EXTINT_NUM);/* disable interrupts on the channel */
   CPU::ClearExternalInterrupt(MEMSTORE_EXTINT_NUM);/* clear interrupt request bit */
   Inp.PSStore = TRUE;
   CPLD::thisPtr->SetDout(MemStoreOut, true);
   CPU::EnableExternalInterrupt(MEMSTORE_EXTINT_NUM);/* Enable interrupts on the channel */
   vector = 0;
   frame = NULL;
}

void ProcessMemoryReset(void)
/****************************************************************************/
/*Description:                                                              */
/*  This function sends the memory reset signal to the power supply and     */
/*  waits for the memory clear signal. In case of DUPS it first set the BIT3*/
/*  of SwDipSettings and download to the DUPS. After got the clear signal   */
/*  or record the alarm the BIT3 is cleared and again download to the DUPS. */
/****************************************************************************/
{
   switch (MemoryResetState) {
   case START_MEMRST:
      MemoryResetFlag = FALSE;
      DUPS_WaitTimer = FALSE;
      if (DUPS_Info.DUPSFlag) {
         DUPS_CurrPSStatus = DUPS_SUCCESS;
         MemoryResetState = DOWNLOAD_DUPS;
      }
      else //Analog Power supply
      {
         MemoryReset(); /* Send the memory reset signal. */
         MemoryResetState = ALG_WAIT_MEMCLR;
      }
      break;

   case DOWNLOAD_DUPS:
      //Wait until parameters are uploaded.
      if (DUPS_CurrPSStatus == DUPS_SUCCESS) {
         CurrentPreset.DUPS_HostParamSet.SWDipSetting |= DUPS_SWDIPCLEARMEMATRST;
         DUPS_CurrPSStatus = DUPS_PENDING;
         DUPS_DownloadParamSet(CurrentSetup.DUPS_WorkingPreset);
         MemoryReset(); /* Send Memory reset for DUPS. */
         MemoryResetState = DUPS_WAIT_MEMCLR;
         DUPS_WaitTimer = FALSE;
      }
      else if (DUPS_WaitTimer++ > DUPS_WAIT_TIMEOUT)
         MemoryResetState = STATE_NONE;

      break;

   case DUPS_WAIT_MEMCLR:
      if (DUPS_CurrPSStatus == DUPS_SUCCESS)/*Wait for the memory clear signal. */
      {
         if (MemoryResetFlag < MEMCLEAR_TIMEOUT && Inp.PSClear) /* If non zero then    */
            MemoryResetFlag = FALSE; /* got the memory clear signal. */
         else if (MemoryResetFlag++ >= MEMCLEAR_TIMEOUT) {
            RecordAlarm(CM17);
            /*Record MemReset alarm*/
            MemoryResetFlag = FALSE;
         }
         if (MemoryResetFlag == FALSE) {
            CurrentPreset.DUPS_HostParamSet.SWDipSetting &= ~(DUPS_SWDIPCLEARMEMATRST);
            DUPS_CurrPSStatus = DUPS_PENDING;
            DUPS_DownloadParamSet(CurrentSetup.DUPS_WorkingPreset);
            MemoryResetState = STATE_NONE;
         }
         DUPS_WaitTimer = FALSE;
      }
      else if (DUPS_WaitTimer++ > DUPS_WAIT_TIMEOUT)
         MemoryResetState = STATE_NONE;

      break;

   case ALG_WAIT_MEMCLR:
      if (MemoryResetFlag < MEMCLEAR_TIMEOUT && Inp.PSClear) /* If non zero then    */
      {
         MemoryResetFlag = FALSE;/* Got the memory clear signal.*/
         MemoryResetState = STATE_NONE;
      }
      else if (MemoryResetFlag++ >= MEMCLEAR_TIMEOUT) {
         RecordAlarm(CM17);
         /*Record MemReset alarm*/
         MemoryResetFlag = FALSE;
         MemoryResetState = STATE_NONE;
      }
      break;

   default:
      break;
   }
}
