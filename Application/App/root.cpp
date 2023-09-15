/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/root.cpp_v   1.39   Oct 10 2017 13:20:18   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/root.cpp_v  $
 * 
 *    Rev 1.39   Oct 10 2017 13:20:18   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.38   Jun 29 2017 14:23:20   RJamloki
 * When no user it must assign the level security Branson
 * 
 *    Rev 1.37   Jun 07 2017 14:01:02   RJamloki
 * remove compuweld comments
 * 
 *    Rev 1.36   09 May 2016 13:02:20   RJamloki
 * Ajust RS232 output
 * 
 *    Rev 1.35   16 Apr 2015 07:28:32   rjamloki
 * Updating HwConfig based on Estop Hw in root
 * 
 *    Rev 1.34   08 Apr 2015 13:45:50   AnPawar
 * Changes to update ram variables for Prestrigger, Amp Step, Pressure Step.
 * 
 *    Rev 1.33   01 Apr 2015 13:02:16   amaurya
 * changes for authority check event if authority check is disabled due to password recovery jumper.
 * 
 *    Rev 1.32   30 Mar 2015 05:42:20   rjamloki
 * Making SecurityLevel Branson at startup in case of Authority check disabled so that all menu items remain visible.
 * 
 *    Rev 1.31   13 Mar 2015 06:08:58   amaurya
 * CheckForAuthorityCheckDisable() added to check the jumper between J3_1_Input_Sig and digital output ReadySig.root() Changed to disable authority check and automation on power up.
 * 
 *    Rev 1.30   30 Jan 2015 08:33:32   amaurya
 * root() changed .
 * 
 *    Rev 1.29   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.28   11 Dec 2014 08:36:58   AnPawar
 * disabling debug
 * 
 *    Rev 1.27   28 Nov 2014 07:40:04   rjamloki
 * Removed unused extern variable.
 * 
 *    Rev 1.26   10 Nov 2014 04:57:04   AnPawar
 * RootTask::root() removed FRAM initialization check.
 * 
 *    Rev 1.25   03 Nov 2014 11:47:44   tayars
 * Attempt to set the proper value at startup for the flow valve.
 * 
 *    Rev 1.24   20 Oct 2014 06:23:48   AnPawar
 * root() function changed
 * 
 *    Rev 1.23   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.22   11 Sep 2014 11:04:12   rjamloki
 * Added RTC battery failure event
 * 
 *    Rev 1.21   05 Sep 2014 05:07:00   rjamloki
 * Added Nandflash init in root.
 * 
 *    Rev 1.20   18 Aug 2014 01:45:44   rjamloki
 * Added MICRO and AE support. Removed checking for Actuator recalibrate alarm.
 * 
 *    Rev 1.19   07 Aug 2014 15:53:06   tayars
 * Make it so at power up the flow is set to the last saved value.
 * 
 *    Rev 1.18   28 Jul 2014 12:51:12   rjamloki
 * bbram to fram renaming
 * 
 *    Rev 1.17   15 Jul 2014 16:45:42   hasanchez
 * Changes about the special menu
 * 
 *    Rev 1.16   09 Jul 2014 12:38:38   rjamloki
 * Root run function cleaned up.
 * 
 *    Rev 1.15   20 Jun 2014 14:32:50   rjamloki
 * Updating global Pressure and flow values at power up from current preset.
 * 
 *    Rev 1.14   16 Jun 2014 08:48:54   rjamloki
 * Removed SendPressureAndFlowValToAES function calling from root.
 * 
 *    Rev 1.13   11 Jun 2014 12:07:48   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.12   27 May 2014 10:14:08   amaurya
 * Added flag for first time FRAM init
 * 
 *    Rev 1.11   21 May 2014 10:48:10   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:37:26   rjamloki
 * extern variables clean up, removed unused file inclusion and code
 * 
 *    Rev 1.9   07 May 2014 10:41:08   rjamloki
 * RootTask::root() function changed.
 * 
 *    Rev 1.8   23 Apr 2014 13:57:28   akaushal
 * Disabled debug statements after root execution
 * 
 *    Rev 1.7   14 Apr 2014 10:21:04   rjamloki
 * Added initialization for for PAL timer, 24 volt sensing , mem store interrupt and external watchdog.
 * 
 *    Rev 1.6   26 Mar 2014 12:31:38   rjamloki
 * removed printf from RootTask::root()
 * 
 *    Rev 1.5   05 Mar 2014 13:56:42   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:52   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:48   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*
  ------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:   Root
                                        
   Filename:      root.c

   Function name: root

            Written by: Mark Lazarewicz 
                  Date: 1/10/96
              Language:  "C"                              

  ---------------------------- DESCRIPTION -----------------------------------

   This is the "root" of the Branson 332 Welder board software.

  ----------------------------- PSEUDO CODE -----------------------------------


  --------------------------- INCLUDE FILES ----------------------------------
*/
 
                 
#include "qdef.h"
#include "opcodes.h"             /* opcode typedef for the welder board         */

/* library initialization routines prototypes */
#include "rtclock.h"
#include "root.h"               
#include "ticks.h"
#include "inports.h"
#include "outports.h"
#include "battram.h"
#include "state.h"
#include "statedrv.h"
#include "util.h"
#include "psnvram.h"
#include "menu.h"
#include "actnvram.h"
#include "WeldManagerTask.h"
#include "weld_obj.h"
#include "qsm.h"
#include "alarms.h"
#include "menu3.h"
#include "ready.h"
#include "graphs.h"
#include "digout.h"
#include "serial.h"
#include "snsrcalb.h"
#include "SystemManagerTask.h"
#include "wc_isr.h"
#include "menu7a.h"
#include "menu2.h"
#include "mansensr.h"
#include "menutest.h"
#include "menu7.h"
#include "version_change.h"
#include "preset.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "InputTask.h"
#include "fpled.h"
#include "CPU.h"
#include "CPLD.h"
#include "A1025R.h"
#include "RTOS.h"
#include "rxcharrcv.h"
#include "NandFlash.h"
#include "Events.h"
#include "WebService.h"
//#define INCLUDE_UNIT_TEST

#ifdef INCLUDE_UNIT_TEST
                    /* call unit test driver */
 extern unit_test();
#endif

extern BOOLEAN* GetInputPtr(UINT16 InputBit);
BOOLEAN ActuatorPresent = TRUE;
BOOLEAN FramInitialized = FALSE;

/*
--------------------------- EXTERNAL DATA ----------------------------------
*/

extern PSNOVRAMDATA PSNvRamData;
extern UINT16 PresetNeedsToBeUpdated;
extern UINT16 PowerUpPresetReceived;
extern UINT8  *FramHistoryPtr;
extern UINT16 WeldDataOffset;
extern UINT32 ActualPeakPower;
extern SINT32 ActualForceMax;
extern UINT8 UpdateRunningPreset;
extern BOOLEAN ActuatorChanged;

//UINT16 SetStateMachineFlag(UINT16 Flag);

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/


#define HALF_A_SECOND            500
#define FOUR_SECONDS             4000
#define MESSAGE_DELAY            (FOUR_SECONDS)

#define TEMP_FPDM_PRIORITY       254
#define TEMP_ROOT_PRIORITY       253
#define MODE_MASK                0x700
#define NEW_INTERRUPT_MODE       0x400

/* indicates to suspend this task */
#define THIS_TASK                0

#define MAX_STARTUP_ALARMS       10   /* Sets size of StartupAlarms[] array */

#define LASTWELD 49


/*
------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

/*
----------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/


/*
------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
                                 

/*                           
-------------------------- EXTERNAL FUNCTIONS -------------------------------
*/
/*
------------------------ LOCAL FUNCTION PROTOTYPES -------------------------
*/


/*
------------------------------- CODE ---------------------------------------
*/

RootTask::RootTask() :
   Task("Root", T_SIZE_4096)
/****************************************************************************/
/* Description:-                                                            */
/* Roottask Constructor                                                     */
/****************************************************************************/
{


}

void RootTask::Run()
{
	root();
	Suspend();
}

void RootTask::root(void)
{
   UINT8  StartupAlarmCount, Index;
   UINT32 StartupAlarms[MAX_STARTUP_ALARMS];  /* Array to store alarm codes */
   UINT32 FramOffset;
   UINT32 FramStatus;
   UINT16 x;
   SetStateMachineFlag(TRUE);
   /* set initial values for initialized static data */
   InitTestBuffers();
   InitializeOutputPorts();
   RTOS::SetTickHandler(MinMsInt);
   InitQsm();
   SetSegs(0xff3f);
   SetBanks(0x0000);
   NandFlash::Init();
   /* Will store alarms in array during startup until system is ready */
   /* to record them. */

   StartupAlarmCount = 0;     /* No startup alarms yet */

     /* Read & check power supply configuration */
   ReCallPSNovram();
   StartupAlarms[StartupAlarmCount] = VerifyPSNovram();
   if (StartupAlarms[StartupAlarmCount])
      StartupAlarmCount++;

   /* Read & check actuator configuration */
   ActPowerUp();        /* Read actuator data into global NVR structure */

   /* add offset to be used during calibration and in spidd */
   LoadCellOffset = LC_OFFSET;

   /* Note: If there is no actuaor Novram, then ActPowerUp will write some */
   /* reasonable initial values to NVR.  Therefore, if CheckNvrValid()     */
   /* fails, it must be because it is processing data actually read from   */
   /* Novram, not the "fake" information supplied by ActPowerUp().  It is  */
   /* therefore safe to conclude that we have an AED actuator. */

   if ( ( (NVR.ActId==NVR_AED) || (NVR.ActId==NVR_MICRO) || (NVR.ActId==NVR_MICROC) ||
          (NVR.ActId == NVR_AES)) && (PSNvRamData.ControlLevel >= LEVEL_d))
   {
      if (!CheckNvrValid())
      {
         ActRecover();   /* Put something in there that makes sense */
         StartupAlarms[StartupAlarmCount++] = EQ10;   /* Actuator Novram */
         StartupAlarms[StartupAlarmCount++] = EQ20;   /* Recalibrate Actuator */
      }
   }   
   /* If 'SwVersion' is changed update the newly added parameters with default values.*/
   CheckForVersionChange();
   CurrentSetup.PSFreq = PSNvRamData.PSFrequency;   
   if (!CheckFramDefaults())
      StartupAlarms[StartupAlarmCount++] = EQ8;
   
   UpdateRunningPreset = FALSE;
   /************  Read Min Preset Table from BATTRAM to DRAM  **************/
   Readpreset(PRESET_MIN_INDEX, &MinLimit);

   /************  Read Max Preset Table from BATTRAM to DRAM  **************/
   Readpreset(PRESET_MAX_INDEX, &MaxLimit);

   /***********  Read Current Setup Table from BATTRAM to DRAM  ************/

   FramStatus = FramAccess(FRAM_READ, CONFIG_SECTION, (UINT8 *)&CurrentSetup, (UINT32)FRAM1200_CONFIG_START, sizeof(CurrentSetup));
   
   /***** Check if fram initialized, if not reinitialize it and generate an alarm *****/
   if(CurrentSetup.FRAMInitialized != FRAM_INIT) {
      InitializeFRAM();
      CheckFramDefaults();
      StartupAlarms[StartupAlarmCount++] = EQ8;
   }

   CurrentSetup.ControlLevel = PSNvRamData.ControlLevel;
   CurrentSetup.PSWatt = PSNvRamData.PSWatts;
   CurrentSetup.PSFreq = PSNvRamData.PSFrequency;   
   strncpy(CurrentSetup.PSSerialNumber, PSNvRamData.PSSerialNum, sizeof(CurrentSetup.PSSerialNumber) - 1);

   /* Intialize User I/O input pointers.*/
   CurrentSetup.J3_32Ptr = GetInputPtr(CurrentSetup.J3_32In);
   CurrentSetup.J3_33Ptr = GetInputPtr(CurrentSetup.J3_33In);
   CurrentSetup.J3_19Ptr = GetInputPtr(CurrentSetup.J3_19In);
   CurrentSetup.J3_17Ptr = GetInputPtr(CurrentSetup.J3_17In);
   CurrentSetup.J3_31Ptr = GetInputPtr(CurrentSetup.J3_31In);
   CurrentSetup.J3_1Ptr = GetInputPtr(CurrentSetup.J3_1In);

   /************  Read Preset Table from BATTRAM to DRAM  ******************/
       
   Readpreset(PRESET_RUNNING_INDEX, &CurrentPreset);   /* first we load the running preset */
   if ((CurrentPreset.PresetUpdateComplete == FALSE) && (CurrentPreset.WeldTime != 0) )/* if we have not finished the update of preset then will load thise values and change the status to complete or if the value is empty */
   {
		CurrentPreset.PresetUpdateComplete = TRUE;
   }
   else	
   {   
		Readpreset( CURRENT_PRESET_INDEX, &CurrentPreset);       /* if the status is finished we will load the values of preset_0_start  */
   }

   /* Calculate to correct offset for last cycle's Weld data */
   FramHistoryPtr = (UINT8 *) FRAM1200_HISTORY_START;
   AddrFram = (SINT32)FramHistoryPtr;
   //Make sure WeldHistoryPtr is in bounds
   CheckHistoryPtrBound();
   WeldDataOffset = CurrentSetup.WeldHistoryPtr - AddrFram;
   if(WeldDataOffset != 0)
      FramOffset = WeldDataOffset - sizeof(WELD_DATA);
   else
      FramOffset = (LASTWELD * sizeof(WELD_DATA));
   FramStatus = FramAccess(FRAM_READ, HISTORY_SECTION, (UINT8 *)&WeldingResults, FramOffset, sizeof(WELD_DATA));
   UpdateWS_Config();           /* updates swconfiguration with weld status information */
   if(NvRamData.EstopTwoPoleHW == ONE_POLE_ESTOP)
	   UpdateHWConfiguration(PC1025SP, TRUE);
   else
	   UpdateHWConfiguration(PC1025DP, TRUE);
   InitMonitorInputPorts();//As estop hardware type in known by now we can initialize input denouncing buffer accordingly
// need to copy all final results at power up
   memcpy(&FinalResults, &WeldingResults, sizeof(WELD_DATA) );
// need to clear alarms from last cycle
   WeldingResults.EquipmentFailureAlarms = 0;
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.CycleModifiedAlarms = 0;
   WeldingResults.CalibrateAlarms = 0;
   WeldingResults.Warnings = 0;

   PresetNeedsToBeUpdated = TRUE;
   FormatRunScreenTopLine();

   /*Populate PMC Average data points*/
   if (!((CurrentSetup.ActivePreset > PRESET_0) &&
       (CurrentSetup.ActivePreset <= MAX_POSSIBLE_PRESET)))
   {
      // Initialize PMC data points
      for (x = 0; x < PMCDATAPOINTS; x++) {         
         CurrentPreset.PMCData[x] = 0xFF;
      }
      CurrentPreset.PMCCycleCount = 0;
   }
   UpdateRPreset();
   PowerUpPresetReceived = TRUE;

   switch (CurrentSetup.SerialPort) {
      case ASCIICOMMA:
      case ASCIITAB:
      case ASCIISPACE:
      case RS232DISABLED:
         break;
      default:          /* If none valid, then default to disabled */
    	  CurrentSetup.SerialPort = RS232DISABLED;
   }
   InitReceiveBuffer();
   /* Now can record alarms we've been saving up */

   for (Index=0; Index<StartupAlarmCount; Index++)
      RecordAlarm( StartupAlarms[Index] );

   /* Update the 'SWConfiguration' for external preset selection(EP_E). */
   DealWithExtPresetChange();
   /*-- Needed to Initalize MsDataPtr and MsPointer pointers --*/
   /*-- to point to DataGroup0 and DataGroup1 respectively   --*/
   /*-- Also initalize graph variables to zeros at power up. --*/
   ClearDataStorage();
   ActuatorChanged = CheckForActChange();
   if(CurrentSetup.Actuator != AE )
      TrsDisabled();
   else
      TrsEnabled();

   /* Change to SINT32 (32 bit) Variables for menu pointers */
   ActualPeakPower = FinalResults.PeakPower;
   ActualForceMax = FinalResults.WeldForceEnd;

   InitWeldSequencer();
   SetPressureValue = CurrentPreset.WeldPressure;
   SetFlowValue = CurrentPreset.TunedFlowValue;
   TempFlowValue = CurrentPreset.Downspeed;
   //Update ram variables related to Pre trigger Amp, Amp step and Pressure step
   SetupPretriggerFlags();
   SetupAmplitudeStepFlag();
   SetupPressureStepFlag();
   /* Password recovery,at power up if authority check is enabled or system in automation and control level is c or higher
    * then check for authority check function is called to detect the jumper between J3_1 and J3_21
    * if jumper is found then  disable the authority check and automation and record the events with
    * reason PRK Jumper */
   if (((CurrentSetup.AuthorityCheck == TRUE) || (CurrentSetup.Automation == ON)) && (CurrentSetup.ControlLevel >= LEVEL_c)) {
		if (CheckForAuthorityCheckDisable()) {
			if(CurrentSetup.AuthorityCheck == TRUE)
			{
			 CurrentSetup.AuthorityCheck = FALSE;
			 /*Update the fram copy, now sbc needs not to be power up to recover password*/
			 FRAMConfigSetup.AuthorityCheck = FALSE;
			 strcpy(WebService::ChangeReason, "PRK Jumper");//A trick to not popup event reason screen at power up
			 EventParameterID = AUTHORITYCHECK;
			 RecordEvents(EVENT_AUTHORITY_CHECK_CHANGED,"ON","OFF");
			 memset(WebService::ChangeReason , 0,sizeof(WebService::ChangeReason));
			}
			if (CurrentSetup.Automation == ON) {
				CurrentSetup.Automation = OFF;
				/*Update the fram copy, now sbc needs not to be power up to recover password*/
				FRAMConfigSetup.Automation = FALSE;
				strcpy(WebService::ChangeReason, "PRK Jumper");//A trick to not popup event reason screen at power up
				EventParameterID = AUTOMATION;
				RecordEvents(EVENT_FACTORY_AUTOMATION_MODE, "ON", "OFF");
				memset(WebService::ChangeReason , 0,sizeof(WebService::ChangeReason));
			}
		}
   }
   if (CurrentSetup.AuthorityCheck == FALSE) CurrentSetup.SecurityLevel = BRANSON;
   StartAppTasks();
   InitMemStoreInterrupt();
   SetupEPortForSensingPowerDown();
   InitSafetyTimer();
   CyGOS::DisableDebug();
   CheckForRTCBattery();
   GetPresetNames();
   RTOS::SetTickHandler(0);
}



/*
 * Watchdog port gets initialized in the startup code also.
 * Doing it again doesn't harm.(Everybody knows what was done in startup code)
 */
void InitExternalWatchDogPort()
{
	MCF_PAD_PAR_UART &= ~MCF_PAD_PAR_UART_PAR_U1RTS; //Configure U4 pin (U1RTS) as GPIO
	MCF_GPIO_PDDR_UART |= MCF_GPIO_PDDR_UART_PDDR_UART6;//Set data direction out
	TriggerExternalWatchDog();//Trigger initially
}

/*
 * Set the PODR reg to reverse the logic on PUART6.
 */
void TriggerExternalWatchDog()
{
	if(MCF_GPIO_PPDSDR_UART & MCF_GPIO_PPDSDR_UART_PPDSDR_UART6)//check if current pin state is high
		MCF_GPIO_PODR_UART &= ~MCF_GPIO_PODR_UART_PODR_UART6;//set new state in PODR reg
	else //If low
		MCF_GPIO_PODR_UART |= MCF_GPIO_PODR_UART_PODR_UART6;//set new state in PODR reg
}

/*
 * Purpose:
 * Configure EPORT registers such that IRQ7 pin(AB13) can be used to detect the 24 volt sensor
 * output. IRQ7 is configured such that no interrupt is generated. IRQ7 pin is polled by 1 ms task.
 */
void SetupEPortForSensingPowerDown()
{
	MCF_EPORT_EPIER &= ~(MCF_EPORT_EPIER_EPIE7);//Make sure no interrupts
	MCF_EPORT_EPPAR &= ~(MCF_EPORT_EPPAR_EPPA7(7));//Clear EPPA7 bits
	MCF_EPORT_EPDDR &= ~(MCF_EPORT_EPDDR_EPDD7);// Clear EPDD7 bit in EPPDR register to configure IRQ7 line as input.
}

/*
 * Purpose:
 * To initialize external interrupt on memory store signal from DUPS.
 */
void InitMemStoreInterrupt()
{
	CPU::InitExternalInterrupt(MemStoreIntHandler, MEMSTORE_EXTINT_NUM, 0, 0,
			CpuIntModeEdgeFalling , true);//Enable interrupt immediately . Memstore line
										//shall be stable at this point.
}

/*
 * Initialization to drive 1ms_timer line for PAL at 1 khz.
 */
void InitSafetyTimer()
{
	//Configure G1 as T0OUT
	MCF_PAD_PAR_TIMER |= (MCF_PAD_PAR_TIMER_PAR_T0IN(MCF_PAD_PAR_TIMER_PAR_T0IN_T0OUT));
	MCF_DTIM_DTMR(0) = MCF_DTIM_DTMR_CLK(1)| MCF_DTIM_DTMR_PS(__SYSTEM_CLOCK - 1)
			| MCF_DTIM_DTMR_OM | MCF_DTIM_DTMR_FRR; //clock source 125 Mhz/Toggle output/Restart

	MCF_DTIM_DTXMR(0) |= MCF_DTIM_DTXMR_HALTED;//stop counting when core halted/Increment by one
	MCF_DTIM_DTRR(0) = 500; //0.5ms on 0.5 ms off (1 Khz)
	MCF_DTIM_DTCN(0) = 0;
	MCF_DTIM_DTMR(0) |= MCF_DTIM_DTMR_RST;
}

void DisableSafetyTimer()
{
	MCF_DTIM_DTMR(0) &= ~MCF_DTIM_DTMR_RST;
}

/*  BOOLEAN CheckForAuthorityCheckDisable(void)
 *
 *   Purpose:
 *		This function is called once at power up from root() function to check the jumper between J3_1_Input_Sig
 *	 	and digital output ReadySig.
 *
 *   Entry condition:
 *		None.
 *
 *   Exit condition:
 *		Returns TRUE if jumper is found between J3_1_Input_Sig and ReadySig else return FALSE.
 */

BOOLEAN CheckForAuthorityCheckDisable(void)
{
	UINT8    ToggleCount = 0;
	BOOLEAN AuthorityCheck = FALSE;
	volatile SINT32 DelayCnt;
	UINT8 Indx;
	for (Indx = 0; Indx < AUTHORITY_CHECK_DISABLE_SEQUENCE; Indx++)
	{
		cpld->SetDout(ReadySig, false);//make Ready(J3-21) high
		for (DelayCnt = 0; DelayCnt < 10000; DelayCnt++)
			;
		//Read the digital input J3_1_Input_Sig
		if (!cpld->GetDin(J3_1_Input_Sig)) // If read 1
			ToggleCount++;
		cpld->SetDout(ReadySig, true);//make Ready(J3-21) low
		for (DelayCnt = 0; DelayCnt < 10000; DelayCnt++)
			;
		if ((cpld->GetDin(J3_1_Input_Sig))) // If read 0
			ToggleCount++;
	}


	if (ToggleCount == (AUTHORITY_CHECK_DISABLE_SEQUENCE * 2))
		AuthorityCheck = TRUE;
	return AuthorityCheck;

}

