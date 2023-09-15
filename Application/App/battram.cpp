/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/battram.cpp_v   1.33   Nov 06 2017 09:44:32   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/battram.cpp_v  $
 * 
 *    Rev 1.33   Nov 06 2017 09:44:32   RJamloki
 * Added MICROC ID to every Actuator ID’s Validation
 * 
 *    Rev 1.32   Oct 09 2017 15:25:56   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.31   Jun 07 2017 15:33:00   RJamloki
 * change config variable to PressureStepDownFlag
 * 
 *    Rev 1.30   May 25 2017 16:57:34   RJamloki
 * Update new default settings
 * 
 *    Rev 1.29   01 Sep 2016 13:16:24   RJamloki
 * Reupdate to version manager
 * 
 *    Rev 1.28   25 Aug 2016 13:38:24   RJamloki
 * Set CurrentSetup.PressureStepDown= FALSE to turn off pressure stepping
 * 
 *    Rev 1.27   09 May 2016 10:55:56   RJamloki
 * CurrentSetup.SerialPort change from COMPUWELD to RS232DISABLED
 * 
 *    Rev 1.26   18 Jan 2016 16:11:10   RJamloki
 * Issue 1148 memory on on checksum cold start
 * 
 *    Rev 1.25   16 Apr 2015 15:03:20   rjamloki
 * Weld history setup defaults initialized in FixFram function
 * 
 *    Rev 1.24   16 Apr 2015 07:19:54   rjamloki
 * Fix for coverity issue 12537
 * 
 *    Rev 1.23   08 Apr 2015 13:42:12   AnPawar
 * Comment changed for DownspeedTune variable.
 * 
 *    Rev 1.22   27 Mar 2015 11:06:40   amaurya
 * DisplayRefreshButton variable removed as we removed theRedundant SetDisplayRefreshButton function.
 * 
 *    Rev 1.21   16 Mar 2015 05:47:32   rjamloki
 * Downspeed tuning is disabled by default
 * 
 *    Rev 1.20   08 Jan 2015 03:18:18   AnPawar
 * printf removed
 * 
 *    Rev 1.19   12 Dec 2014 05:28:56   RJamloki
 * DownSpeedTune default value is made true
 * 
 *    Rev 1.18   11 Dec 2014 08:34:34   AnPawar
 * making ps lifetime 0 in fixfram()
 * 
 *    Rev 1.17   14 Nov 2014 05:29:44   rjamloki
 * ClearOutFram() changed.
 * 
 *    Rev 1.16   10 Nov 2014 04:44:14   AnPawar
 * ClearOutFram() Checks for unvalid UserID table before clearing it.
 * 
 *    Rev 1.15   03 Oct 2014 05:49:44   rjamloki
 *  BUCMenuRAM.AmpDecayPercent removed
 * 
 *    Rev 1.14   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.13   05 Sep 2014 04:35:04   rjamloki
 * Added level c check in CheckFramDefaults function
 * 
 *    Rev 1.12   18 Aug 2014 01:36:02   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.11   28 Jul 2014 12:38:32   rjamloki
 * Review Comment fixes
 * 
 *    Rev 1.10   15 Jul 2014 16:43:34   hasanchez
 * Changes about the special menu
 * 
 *    Rev 1.9   11 Jun 2014 11:17:20   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:47:46   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 02:50:40   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.6   07 Mar 2014 11:11:10   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.5   05 Mar 2014 13:56:16   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:30   rjamloki
 * Preset changes to support 1000 preset.
 *
 *    Rev 1.3   03 Jan 2014 08:45:18   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*   
 ------------------------------ MODULE DESCRIPTION -----------------------------

 Module name:

 Filename:       battram.c

 Function name:  FramAccess

 
 Written by:     Mark Lazarewicz
 Date:           12/04/95
 Language:       Microtec "C"

 -------------------------- DESCRIPTIONS ------------------------------------

 This function reads 1 or more bytes of data from BATRAM to SRAM and
 also writes 1 or more bytes of data from SRAM to BATRAM.

 ----------------------------- PSUEDOCODE --------------------------------------

 ---------------------------- INCLUDE FILES ------------------------------------*/

/* System include files */
#include   "portable.h"

/* Function include files */
#include   "spidd.h"
#include   "weld_obj.h"
#include   "battram.h"
#include   "rtclock.h"
#include   "menu7a.h"
#include   "ready.h"
#include   "alarms.h"
#include   "actnvram.h"
#include   "psnvram.h"
#include   "dups_api.h"
#include   "string.h"
#include   "menu.h"
#include   "preset.h"
#include   "param.h"
#include   "snsrcalb.h"
#include   "selctkey.h"
#include   "menu7.h"
#include   "menu1.h"
#include   "alsetup.h"
#include   "SystemManagerTask.h"
#include   "stdio.h"
#include   "Events.h"
#include "UndefPrintf.h"
/*
 ---------------------------- LOCAL DEFINES  -----------------------------------
 */

/* ---------------------LOCAL TYPE DECLARATIONS ------------------------- */

/* ----------------------- PRIVATE GLOBAL DATA -------------------------- */
BUCMENU_1200 *BUCMenuFRAM;
//extern const SCRN_CALIB_CORDINATE ActualCalibPts;

DEPOT_FLAGS *DepotFlag = (DEPOT_FLAGS *) FRAM1200_DEPOT_START;

/*--------------------------- EXTERNAL DATA ----------------------------- */
extern UINT16 PresetHasBeenOKed;
/*------------------------------- CODE -----------------------------------*/

FRAM_STATUS_TYPE FramAccess(FRAM_ACCESS_TYPE Request, FRAM_SECTION_TYPE SecID,
      UINT8 *DataPointer, UINT32 Offset, UINT16 ByteCount) { /* Start of function */

   UINT8 *FRAMPointer; /* points to BATTRAM data location for read or write */
   FRAM_STATUS_TYPE CompletionStatus = FRAM_STATUS_OK;
   CONFIGSETUP *SetupPtr;

   SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

   if (ByteCount == 0) /* Check for zero byte count */
      CompletionStatus = FRAM_STATUS_BAD_ARG;
   else {
      switch (SecID) {
      case SYSTEM_SECTION:
      case PRESET_SECTION:
      case CONFIG_SECTION:
         FRAMPointer = (UINT8 *) Offset;
         break;

      case HORN_SECTION:
         FRAMPointer = (UINT8 *) ((UINT8 *)FRAM1200_HORNGRAPH_START + Offset);
         break;

      case HISTORY_SECTION:
         FRAMPointer = (UINT8 *) ((UINT8 *)FRAM1200_HISTORY_START + Offset);
         break;

      case NOTASSIGNED_SECTION:
         FRAMPointer = (UINT8 *) ((UINT8 *)FRAM1200_NOTASSIGNED_START + Offset);
         break;

      default:
         CompletionStatus = FRAM_STATUS_BAD_ARG;
      }
   }

   if (CompletionStatus == FRAM_STATUS_OK) {
      switch (Request) {
      case FRAM_READ:
         while (ByteCount > 0) {
            *DataPointer = *FRAMPointer;
            FRAMPointer++;
            DataPointer++;
            ByteCount--;
         }
         break;
      case FRAM_WRITE:
         while (ByteCount > 0) {
            *FRAMPointer = *DataPointer;
            FRAMPointer++;
            DataPointer++;
            ByteCount--;
         }
         if (SecID == HISTORY_SECTION) {
            CurrentSetup.WeldHistoryPtr = (UINT32) FRAMPointer;
            SetupPtr->WeldHistoryPtr = (UINT32) FRAMPointer;
         }
         break;
      default:
         CompletionStatus = FRAM_STATUS_BAD_ARG;
      }
   }
   return (CompletionStatus);
}

void ClearOutFram(void)
/* -------------------------------- DESCRIPTION ----------------------------------- */
/*                                                                                  */
/*  This function clears out all of battery backed ram starting from FRAM1200_START_  */
/*  ADDRESS and going for FRAM1200_SIZE bytes.                                        */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/
{
   UINT8 *FramPtr; /* points to BATTRAM data location for write */
   UINT32 ByteCount;
   FRAMUserID * UserIdSectionPtr;
   FRAMEventHistory * EventHistoryPtr;
   FramPtr = (UINT8 *) FRAM1200_START_ADDRESS;
   UINT32 OldEventCount ;
   SINT16 OldCircularIndex;
   for (ByteCount = 0; ByteCount < FRAM1200_SIZE;) {
	   if(FramPtr == FRAM1200_USERIDDATA_START)//Check if user id section in FRAM is valid. Clear only if it is not valid
	   {
		   UserIdSectionPtr = (FRAMUserID *)FRAM1200_USERIDDATA_START;
		   if(!strncmp(UserIdSectionPtr->UserDetail[0].UserId , "ADMIN", strlen("ADMIN")))//check if first user is admin
		   {
			   //Skip clearing user id section
			   FramPtr += sizeof(FRAMUserID);
			   ByteCount += sizeof(FRAMUserID);
		   }
		   else//so that we don't trap into infinite loop
		   {
			   ByteCount++;
			   *FramPtr++ = 0;
		   }
	   }
	   else if((FramPtr == FRAM1200_EVENTDATA_START) && (FramPtr != FRAM1200_START_ADDRESS))//Coverity 12537. Can't be pointing to ReservedStart due to memset below
	   {
		   EventHistoryPtr = (FRAMEventHistory *) FramPtr;
		   //need to clear event log but preserve the count for SBC
		   OldEventCount = EventHistoryPtr->EventHistoryCount;
		   OldCircularIndex = EventHistoryPtr->CircularIndex;
		   if(EventHistoryPtr->EventHistoryCheckSum ==  EVENTHISTORYINITIALIZED_CHECKSUM){
			   //CLEAR  FramEventHistoryObj in FRAM.
			   memset(EventHistoryPtr,0,sizeof(FRAMEventHistory));
			   FRAMEventHistoryObj. CircularIndex = OldCircularIndex;
		       FRAMEventHistoryObj. EventHistoryCount = OldEventCount;
		       FRAMEventHistoryObj. EventHistoryCheckSum = EVENTHISTORYINITIALIZED_CHECKSUM;
		       FramPtr += sizeof(FRAMEventHistory); //200
		       ByteCount += sizeof(FRAMEventHistory); //200
		   }
		   else//so that we don't trap into infinite loop
		   {
			   ByteCount++;
			   *FramPtr++ = 0;
		   }
	   }
	   else//user id section is just after event log so it will go into else
	   {
		   ByteCount++;
		   *FramPtr++ = 0;
	   }
   }
}

BOOLEAN CheckFramDefaults(void)
/* -------------------------------- DESCRIPTION -----------------------------------*/
/*                                                                                 */
/* This function checks to see if the battram contains the default settings.  If   */
/* it does not, then the FRAM is cleared and everything is initialized, including   */
/* the real time clock and values not affected by cold start.  Then the min/max    */
/* values are set as well as cold start values.                                    */
/*                                                                                 */
/*---------------------------------------------------------------------------------*/
{
   BOOLEAN RetVal = TRUE; /* Returns TRUE if FRAM is okay */

   /* check to see if the battram has default values and digtune is centered   */

   /* Here the first thing to do is check for old versions to determine if a conversion is needed */

   switch (PSNvRamData.ControlLevel) {
   case MODEL1:
      PSNvRamData.ControlLevel = LEVEL_t; /* Old version MODEL 1 found, convert to new version */
      break;
   case MODEL2:
      PSNvRamData.ControlLevel = LEVEL_e; /* Old version MODEL 2 found, convert to new version */
      break;
   case MODEL3:
      PSNvRamData.ControlLevel = LEVEL_ea; /* Old version MODEL 3 found, convert to new version */
      break;
   case MODEL4:
      PSNvRamData.ControlLevel = LEVEL_d; /* Old version MODEL 4 found, convert to new version */
      break;
   case MODEL5:
      PSNvRamData.ControlLevel = LEVEL_f; /* Old version MODEL 5 found, convert to new version */
      break;
   case LEVEL_t:
   case LEVEL_c:
   case LEVEL_e:
   case LEVEL_ea:
   case LEVEL_a:
   case LEVEL_d:
   case LEVEL_f:
   case LEVEL_TEST:
      break;
   default: /* Assume if no valid control level, FRAM is also bad */
      ClearOutFram();
      FixFram();
      break;
   }
   /* Here copy the BUC Menu stuff into working ram structure */
   BUCMenuFRAM = (BUCMENU_1200*) FRAM1200_BUCMENU_START;
   BUCMenuRAM.EnergyBrakingAmp = BUCMenuFRAM->EnergyBrakingAmp;
   BUCMenuRAM.EnergyBrakingTime = BUCMenuFRAM->EnergyBrakingTime;
   BUCMenuRAM.ExtSwLogicBUC = BUCMenuFRAM->ExtSwLogicBUC;
   BUCMenuRAM.ForcePC = BUCMenuFRAM->ForcePC;
   BUCMenuRAM.GndDetLogicBUC = BUCMenuFRAM->GndDetLogicBUC;
   BUCMenuRAM.ULSLogicBUC = BUCMenuFRAM->ULSLogicBUC;
   BUCMenuRAM.VelocityPC = BUCMenuFRAM->VelocityPC;
   BUCMenuRAM.VelocityReporting = BUCMenuFRAM->VelocityReporting;
   BUCMenuRAM.RecalCode300 = BUCMenuFRAM->RecalCode300;
   BUCMenuRAM.MicroHomeForce = BUCMenuFRAM->MicroHomeForce;

   /* Here copy FRAM BUC menu stuff into working ram structure */
   AlarmPtrFRAM = (ALARM_MASKS *) FRAM1200_ALARM_START;

   AlarmPtrRam.SetupGroup1 = AlarmPtrFRAM->SetupGroup1;
   AlarmPtrRam.SetupGroup2 = AlarmPtrFRAM->SetupGroup2;
   AlarmPtrRam.SetupGroup3 = AlarmPtrFRAM->SetupGroup3;
   AlarmPtrRam.SetupGroup4 = AlarmPtrFRAM->SetupGroup4;
   AlarmPtrRam.SetupGroup5 = AlarmPtrFRAM->SetupGroup5;
   AlarmPtrRam.SetupGroup6 = AlarmPtrFRAM->SetupGroup6;
   AlarmPtrRam.SetupGroup7 = AlarmPtrFRAM->SetupGroup7;
   AlarmPtrRam.SetupGroup8 = AlarmPtrFRAM->SetupGroup8;
   AlarmPtrRam.SetupGroup9 = AlarmPtrFRAM->SetupGroup9;
   AlarmPtrRam.SetupGroup10 = AlarmPtrFRAM->SetupGroup10;
   AlarmPtrRam.Overload = AlarmPtrFRAM->Overload;
   AlarmPtrRam.NoCycle = AlarmPtrFRAM->NoCycle;
   AlarmPtrRam.EquipmentFailure = AlarmPtrFRAM->EquipmentFailure;
   AlarmPtrRam.CycleModified = AlarmPtrFRAM->CycleModified;
   AlarmPtrRam.Reject = AlarmPtrFRAM->Reject;
   AlarmPtrRam.Suspect = AlarmPtrFRAM->Suspect;
   AlarmPtrRam.Warning = AlarmPtrFRAM->Warning;

/* Now check for DEPOT level */

   if(DepotFlag->IsADepot)
   {
      UpdateSWConfiguration(DEPO, TRUE);
      DepotLevel = TRUE;
   } else {
      UpdateSWConfiguration(DEPO, FALSE);
      DepotLevel = FALSE;
   }

   return (RetVal);
}

void FixFram(void)
/****************************************************************************/
/*                                                                          */
/* This function sets up the factory defaults in the event the battram is   */
/* corrupted or not initialized.  This will be similiar to ColdStartPlus()  */
/* except it will be assumed the novram is okay.  This means calibration    */
/* stuff won't be done.                                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;

   InitSetupFromAct(); /* Make sure CurrentSetup.Actuator is correct for next step */
   switch (CurrentSetup.Actuator) {
      case AED:
      case AES:
      case MICROC: // MICRO C ID for sunrise micro c actuator
         BuildVelocityTable();
         EnableMetricEncoder();
         break;
      case MICRO:
    	  BuildVelocityTable();
    	  EnableUSEncoder();
	   break;
      default:
         break;
   }

   /* Now setup some systemconfiguration stuff */
   CurrentSetup.SBLEnable = TRUE;
   CurrentSetup.Units = FALSE;
   CurrentSetup.Metric3Flag = FALSE; // default to 2 decimals as before
   CurrentSetup.DistanceULS = FALSE; // default reset encoder on start switches
   CurrentSetup.PassWordFlag = FALSE;
   CurrentSetup.Language = ENGLISH;
   CurrentSetup.WeldHistoryPtr = (SINT32) FRAM1200_HISTORY_START;
   CurrentSetup.BaudRate = BAUD_9600;
   CurrentSetup.ExtPresets = FALSE;
   CurrentSetup.HandHeld = FALSE;
   CurrentSetup.GainFactor = GAIN_FACTOR_DEFAULT;

   /*Set Default Weld Param Options for VGA */
   CurrentSetup.WeldParamOption[0] = RCYCLECOUNT;
   CurrentSetup.WeldParamOption[1] = RTIME;
   CurrentSetup.WeldParamOption[2] = RPKPWR;
   if(CurrentSetup.ControlLevel == 0)//If it is 0 means we are here when the code is down loaded for the first time.
	   	   	   	   	   	   	   	   	 //Check InitializeFram call in RecallPsNovRam function.
	   PSNvRamData.ControlLevel = CurrentSetup.ControlLevel = LEVEL_d;
   else
	   PSNvRamData.ControlLevel = CurrentSetup.ControlLevel;
   if (PSNvRamData.ControlLevel >= LEVEL_ea)
      CurrentSetup.WeldParamOption[3] = RENERGY;
   else
      CurrentSetup.WeldParamOption[3] = RAMPSTART;
   if (PSNvRamData.ControlLevel >= LEVEL_d)
      CurrentSetup.WeldParamOption[4] = RTCOLDIST;
   else
      CurrentSetup.WeldParamOption[4] = RFREQEND; /*Set Default Weld Param Options for VGA */

   if (DUPS_Info.DUPSFlag == FALSE) /* Let DUPS power up sequence decide if */
      CurrentSetup.PSType = FALSE; /* system should be configured with or  */
   else
      /* without a DUPS.                      */
      CurrentSetup.PSType = TRUE;

   CurrentSetup.SerialPort = RS232DISABLED;
   CurrentSetup.SequenceEnable = FALSE; /*Sequencing Disabled */
   CurrentSetup.SequenceCount = 0; /*Sequence list count made zero */
   CurrentSetup.SequenceNos = 0; /*Current Sequence nos made zero */
   CurrentSetup.AutoRefresh = FALSE;
   CurrentSetup.StartScreen = FALSE; /*Default to Main Menu           */
   CurrentSetup.Sclk7890Act = SLOWSPEED; /* Actuator A/D SCK  */
   CurrentSetup.ClockPhase = INVERTCLK; /* need to invert signal when using slow speed*/
   //Don't clear the pslife time on control level change*/
   //CurrentSetup.PSLifetime = 0;
   CurrentSetup.DownspeedTune = FALSE;//default off
   if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
	   CurrentSetup.WeldHistSetup = DEFAULT_WELDHISTORY_COLUMNSETP_AEC;//Set all columns in weld history to show up as Default.
   else
	   CurrentSetup.WeldHistSetup = DEFAULT_WELDHISTORY_COLUMNSETP_NONAEC;
#ifndef WC2000XTEST
   StorePSLifeTimeCount();
#endif

   strcpy(MinLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(MaxLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(CurrentPreset.PresetID, "COLD START");  /*     it will allow restore the values as a factory*/
   
   SavePreset( PRESET_COLDSTART_INDEX, &CurrentPreset);
   SetMaxMinValues();
   SetDefaultValues();
   
   CurrentSetup.VGAHWPresent = FALSE;
   GetAlarmMask();
   SetAmpControl();
   SetFreqControl();
   if (ClearAlarm(WeldingResults.EquipmentFailureAlarms) == TRUE) {
      ClearFinalResults();
      ClearWeldData();
      AlarmDetectedFlag = FALSE;
      AlarmOff(); // Turn Reset led off
   }
   ClearSetupAlarms();
   UpdateCylDefaults();
   if (PSNvRamData.PSWatts > 3300)
      CurrentSetup.ExtraCooling = TRUE;
   else
      CurrentSetup.ExtraCooling = FALSE;
   BUCMenuRAM.VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuFRAM->VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuRAM.VelocityReporting = FALSE; /* Default velocity reporting to off */
   BUCMenuFRAM->VelocityReporting = FALSE;
   BUCMenuRAM.RecalCode300 = TRUE; /* Default recal code 300 reporting to on */
   BUCMenuFRAM->RecalCode300 = TRUE;
   /* Default values for EnergyBraking */
   BUCMenuRAM.EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuRAM.EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuFRAM->EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuFRAM->EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuFRAM->MicroHomeForce = LEAVINGHOMEFORCEMICROLO;
   CurrentSetup.Overload = 0;
   CurrentSetup.GenAlarmCount = 0;
   CurrentSetup.FRAMInitialized = FRAM_INIT;
   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0); // Updates Running Preset
   CurrentSetup.IdleSpeed = IDLE_SPEED_DEFAULT;
   BackupCurrentSetupChange();
   CurrentPreset.PresetUpdateComplete = TRUE;
   CurrentPreset.PresetID[0] = 0;       /* Ensure the preset names are blank */
   PresetHasBeenOKed = FALSE;           /* Ensure preset stored as not verified.   */ 
                                        /* Otherwise changing actuators will cause */
                                        /* every preset at power up to generate an */
                                        /* Invalid Preset alarm.                   */
   for(x=0; x <= MAX_POSSIBLE_PRESET;x++)
      SavePreset(x, &CurrentPreset);	   
   memset(FRAMPresetInfo, 0 , sizeof(FRAMPresetInfo));
   DUPS_Info.WeldStatusFlag = TRUE; /* Initialize weld status flag*/
   if (DUPS_Info.DUPSFlag) /* if DUPS Communications established */
   {
      DUPS_UploadParamSet(0); /* Upload factory default parameter set */
      DUPS_Wait4CurrPS();
	  DUPS_Info. DUPSMemFlag = TRUE;
	  DUPS_Info. DUPSSeekFlag = FALSE;
	  DUPS_Info. DUPSMemRstFlag = FALSE;
	  DUPS_ModifySWDipSetting();
      DUPS_QueuedDownloadPS();             /* setup default current parameter set */
      DUPS_Wait4CurrPS();
    }
    /* Save the ColdStart Preset. */
    strcpy(CurrentPreset.PresetID, "COLD START");        /* Name it              */
    SavePreset(PRESET_COLDSTART_INDEX, &CurrentPreset);
    CurrentPreset.PresetID[0] = 0;

    CurrentSetup.PressureStepDownFlag = FALSE;
    CurrentSetup.WebServiceAutomation = TRUE;
    CurrentSetup.WebServiceAutorityCheck = TRUE;
 }

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "battram.ut"
#endif  
/* FOR UNIT TEST ONLY */
