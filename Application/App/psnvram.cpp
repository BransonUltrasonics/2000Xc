/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/psnvram.cpp_v   1.21   Oct 10 2017 13:10:42   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/psnvram.cpp_v  $
 * 
 *    Rev 1.21   Oct 10 2017 13:10:42   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.20   Jun 07 2017 13:54:28   RJamloki
 * Remove compuweld in comments
 * 
 *    Rev 1.19   09 May 2016 12:47:30   RJamloki
 * CurrentSetup.SerialPort change from COMPUWELD to RS232DISABLED
 * 
 *    Rev 1.18   16 Apr 2015 17:13:38   rjamloki
 * Fixed StoreEstopHwVersion for calculating righ address of EstopHwVersion in macchip. 
 * 
 *    Rev 1.17   16 Apr 2015 15:08:34   rjamloki
 * Added initializations for weld history setup in ReCallPSNovram function.
 * 
 *    Rev 1.16   16 Apr 2015 07:28:00   rjamloki
 * Fixed ReCallPSNovram to put Estop Hw selection in mac chip
 * 
 *    Rev 1.15   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.14   11 Dec 2014 08:36:40   AnPawar
 * ps lifetime assigned and clearing all preset name during fram init. 
 * 
 *    Rev 1.13   28 Nov 2014 07:39:56   rjamloki
 * Changes to avoid warnings.
 * 
 *    Rev 1.12   14 Nov 2014 05:28:34   rjamloki
 * ReCallPSNovram() changed to copy default power supply serial number.
 * 
 *    Rev 1.11   10 Nov 2014 04:56:24   AnPawar
 * Removed empty functions.Moved the power supply data from FRAM to MAC chip.
 * 
 *    Rev 1.10   26 Sep 2014 03:37:30   rjamloki
 * InitializeFRAM modified to Create default executive
 * 
 *    Rev 1.9   05 Sep 2014 06:33:06   rjamloki
 * Added contol level c cases.
 * 
 *    Rev 1.8   28 Jul 2014 12:40:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.7   11 Jun 2014 12:07:48   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 03:35:32   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   06 Mar 2014 11:03:58   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:38   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:45:44   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: psnvram.c

 ---------------------------- DESCRIPTION -----------------------------------
    
   Functions:                                                                                                                              
       1. ReadPSData
       2. WritePSData                                                         
     
   PSNovram is 32 bytes X24C45 on PCS8 
   The NovramPS Structure -
       Model Number
       Actuator Type
       PS Wattage
       PS Freq
       PS Lifetime Counters
       PS Serial Number
       SW Version
      
   Read Structure from Novram at power up read. Then copy the data into fram
   Write Structure to Novram when powering down write, store is automatic

                                    
 --------------------------- INCLUDE FILES ----------------------------------
*/
       
#include "portable.h"
#include "string.h"

#include "qsm.h"
#include "menu.h"
#include "psnvram.h"
#include "preset.h"
#include "ticks.h"
#include "alarms.h"
#include "ready.h"
#include "spidd.h"
#include "battram.h"
#include "command.h"
#include "SystemManagerTask.h"
#include "snsrcalb.h"
#include "menu.h"
#include "stdio.h"
#include "battram.h"
#include "menu3.h"
#include "A1025R.h"
#include "version_change.h"

/*
 ------------------------------- GLOBAL DATA ------------------------------
                        (scope is global to ALL files)
*/

PSNOVRAMDATA PSNvRamData;//Keeps the power supply data read from Mac chip.
MacChipData  NvRamData; //MAC chip memory map

UINT16 OldNovramInstalledFlag=FALSE;                                       /* G Supposing the NEW PSNovram is installed. That's the reason for assigning the FALSE value to this flag */
UINT8 ModelNumberLowByte;
UINT8 ModelNumberHighByte;                                                 /* G For helping on detecting which Novram is installed on the system controller */
                                                                           /* G The control level code is read from the PSNovram and then assigned to this variable */

/* ------------------------- EXTERNAL DATA --------------------------------*/

extern DEPOT_FLAGS  *DepotFlag;

/*
 ------------------------------ LOCAL DEFINES -----------------------------
*/                                                              

#define RELEASE2 1
/*                                      
 ------------------------------- LOCAL DATA -------------------------------
*/

/*
 ---------------------------------- CODE ----------------------------------
*/
/*****************************************************************************/
/*                                                                           */
/*  This function is called from SBC screen or at the time of FRAM           */
/*  initialization to store the PS Life time counter to MAC Chip.            */
/*****************************************************************************/
void StorePSLifeTimeCount(void)
{
   PSNvRamData.PSLifeTime = CurrentSetup.PSLifetime;
   int LifeTimeAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)&PSNvRamData.PSLifeTime) - ((UINT8*)&PSNvRamData));
   MacChipPtr->Write(LifeTimeAddr , (unsigned char *)&PSNvRamData.PSLifeTime, sizeof(PSNvRamData.PSLifeTime));
}

/*****************************************************************************/
/*                                                                           */
/*  This function is called from Secret password or Host command to store    */
/*  control level in MAC Chip.                                               */
/*****************************************************************************/
void StorePSControlLevel(void)
{
  PSNvRamData.ControlLevel = CurrentSetup.ControlLevel;
  int ControlLevelAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)&PSNvRamData.ControlLevel) - ((UINT8*)&PSNvRamData));
  MacChipPtr->Write(ControlLevelAddr , (unsigned char *)&PSNvRamData.ControlLevel, sizeof(PSNvRamData.ControlLevel));
}

/*****************************************************************************/
/*                                                                           */
/*  This function is called to store PSWattage in MAC chip from host command */
/*  or at power up after the DUPS communication is established or from       */
/*  secret passwords.                                                        */
/*****************************************************************************/
void StorePSWattage(void)
{
   PSNvRamData.PSWatts = CurrentSetup.PSWatt;
   int PsWattAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)&PSNvRamData.PSWatts) - ((UINT8*)&PSNvRamData));
   MacChipPtr->Write(PsWattAddr , (unsigned char *)&PSNvRamData.PSWatts, sizeof(PSNvRamData.PSWatts));
}

/*****************************************************************************/
/*                                                                           */
/*  This function is called to store PSFreq in MAC chip from host command    */
/*  or at power up after the DUPS communication is established or from       */
/*  secret passwords.                                                        */
/*****************************************************************************/
void StorePSFrequency(void)
{
   PSNvRamData.PSFrequency = CurrentSetup.PSFreq;
   int PsFreqAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)&PSNvRamData.PSFrequency) - ((UINT8*)&PSNvRamData));
   MacChipPtr->Write(PsFreqAddr , (unsigned char *)&PSNvRamData.PSFrequency, sizeof(PSNvRamData.PSFrequency));
}

/*******************************************************************************/
/*                                                                             */
/*  This function is called to store PSSerialnum in MAC chip from host command */
/*  or from secret passwords.                                                  */
/*******************************************************************************/
void StorePSSerialNumber(void)
{
   strncpy(PSNvRamData.PSSerialNum, CurrentSetup.PSSerialNumber, sizeof(PSNvRamData.PSSerialNum) - 1);
   int SerialNumAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)PSNvRamData.PSSerialNum) - ((UINT8*)&PSNvRamData));
   MacChipPtr->Write(SerialNumAddr , (unsigned char *)PSNvRamData.PSSerialNum, sizeof(PSNvRamData.PSSerialNum));
}

/*********************************************************************************/
/*                                                                               */
/*  This function is called to store the ESTOP H/W type (Single pole or two pole)*/
/*  in MAC chip from secret password or from Debug serial port.                  */
/*  or from secret passwords.                                                    */
/*********************************************************************************/
void StoreEstopHwVersion(UINT16 Version)
{
   int EstopHwVerAddr = MACCHIP_DATASTART_ADDRESS + (((UINT8*)&NvRamData.EstopTwoPoleHW) - ((UINT8*)&NvRamData.NvMData));
   MacChipPtr->Write(EstopHwVerAddr , (unsigned char *)&Version, sizeof(Version));
}

/*********************************************************************************
* This function is called from root function at power up. It reads the control level,
*  wattage ,frequency and board's Estop HW information from MAC chip. It creates the
*  default for those if the values are not in expected range.
*********************************************************************************/
void ReCallPSNovram(void)
{
	BOOLEAN FirstTimeFlag = FALSE;
	int Readlen = MACCHIP_RWDATA_LEN;
	MacChipPtr->Read(MACCHIP_DATASTART_ADDRESS, (unsigned char *) &NvRamData, Readlen, 3);
	if (memcmp(NvRamData.CheckSumStr, "PSNVR", 5) != 0) {//if this is first time we are switching power supply data from
														//fram to mac chip
		PSNvRamData = NvRamData.NvMData; //have whatever you have for switch case below
		memcpy(NvRamData.CheckSumStr, "PSNVR", 5);
		memset(NvRamData.SpareArr, 0, sizeof(NvRamData.SpareArr));
		FirstTimeFlag = TRUE;
	}
	else {
		PSNvRamData = NvRamData.NvMData;
	}

	if ((NvRamData.EstopTwoPoleHW != ONE_POLE_ESTOP) && (NvRamData.EstopTwoPoleHW != TWO_POLE_ESTOP)) {
		//First time determine the Estop HW based on  VERBEFOREESTOPCHANGE define
		if (CURRENT_ESTOP_SWVERSION <= ONEPOLE_ESTOP_REFVERSION)
			NvRamData.EstopTwoPoleHW = ONE_POLE_ESTOP;
		else
			NvRamData.EstopTwoPoleHW = TWO_POLE_ESTOP;
		FirstTimeFlag = TRUE; //want the updated value to be written in PSnovra,
		//Do some other useful stuffs required for this build
		CONFIGSETUP *SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
		if(SetupPtr->Actuator == AES || SetupPtr->Actuator == MICROC)
			SetupPtr->WeldHistSetup = DEFAULT_WELDHISTORY_COLUMNSETP_AEC;//Set all columns in weld history to show up as Default.
	    else
	    	SetupPtr->WeldHistSetup = DEFAULT_WELDHISTORY_COLUMNSETP_NONAEC;
	}

	switch (PSNvRamData.ControlLevel) {
	case LEVEL_t:
	case LEVEL_e:
	case LEVEL_ea:
	case LEVEL_a:
	case LEVEL_d:
	case LEVEL_f:
	case LEVEL_c:
	case LEVEL_TEST:
	case MODEL1:
	case MODEL2:
	case MODEL3:
	case MODEL4:
	case MODEL5:
		break;
	default:
		PSNvRamData.ControlLevel = LEVEL_t;
		RecordAlarm(EQ11);
	}
	/** been powered up.  If so, then set IsADepot and WasADepot flags to FALSE. **/
	/** Also call ColdStartPlus() to set all min/max and factory default values. **/
	if ((PSNvRamData.PSWatts == 0x0ffff)
			&& (PSNvRamData.PSFrequency == 0x0ffff)
			&& (PSNvRamData.PSSerialNum[7] == -1) /* A random location in S/N */
			&& (PSNvRamData.ControlLevel == LEVEL_TEST)) {
		InitializeFRAM(); //This call is expected in fresh board where all values are ff in mac chip eeprom location
		//Below is to prevent garbage display of ps serial number on system information page
		//start with default serial number and control level d for the first time
		strncpy(NvRamData.NvMData.PSSerialNum, "DEF1234", sizeof(NvRamData.NvMData.PSSerialNum) - 1);
		strncpy(PSNvRamData.PSSerialNum, "DEF1234",	sizeof(PSNvRamData.PSSerialNum) - 1);
		NvRamData.NvMData.ControlLevel = PSNvRamData.ControlLevel = LEVEL_d;
	}

	if (FirstTimeFlag)
		MacChipPtr->Write(MACCHIP_DATASTART_ADDRESS, (unsigned char *) &NvRamData, MACCHIP_RWDATA_LEN);
}



UINT32 VerifyPSNovram(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check most of the data read from the power supply    */
/*  novram and make sure each value is valid for the particular parameter.  */
/*                                                                          */
/****************************************************************************/
{
   UINT32 AlarmCode;

   AlarmCode = 0;
   switch (PSNvRamData.ControlLevel)
    {
      case LEVEL_t:
        break;
      case LEVEL_e:
        break;
      case LEVEL_ea:
        break;
      case LEVEL_a:
        break;
      case LEVEL_d:
        break;
      case LEVEL_f:
        break;
      case LEVEL_c:
        break;
      case LEVEL_TEST:
        break;
      default:
        AlarmCode = EQ11;
    }
    
   if ((PSNvRamData.PSFrequency != FREQ15KHZ) && (PSNvRamData.PSFrequency != FREQ20KHZ) &&
        (PSNvRamData.PSFrequency != FREQ30KHZ) && (PSNvRamData.PSFrequency != FREQ40KHZ) &&
        (PSNvRamData.PSFrequency != FREQ60KHZ))
   {
      AlarmCode = EQ11;
   }           
   return( AlarmCode );
}



BOOLEAN IsValidControlLevel(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will check whether valid control level is stored in	 	 */
/*  MacChip(PsNovrma).It shall be called only after RecallPsNovRam function  */
/*  is called from Root task                                                 */
/*****************************************************************************/
{
	BOOLEAN ValidControlLevel = TRUE;
	switch (PSNvRamData.ControlLevel)
	{
    	 case LEVEL_t:
			break;
		  case LEVEL_e:
			break;
		  case LEVEL_ea:
			break;
		  case LEVEL_a:
			break;
		  case LEVEL_d:
			break;
		  case LEVEL_f:
			break;
		  case LEVEL_c:
			break;
		  case LEVEL_TEST:
			break;
		  default:
			  ValidControlLevel = FALSE;
	}
	return ValidControlLevel;
}



void InitializeFRAM(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will first clear out FRAM then install the proper defaults  */
/*  for system configuration.  It will also insure that the system does not  */
/*  think its a Depot unit.  The serial port is enabled and set to disabled.*/
/*  The system controller is set to 102-242-594 and all user I/O is set to   */
/*  factory defaults.                                                        */
/*                                                                           */
/*****************************************************************************/
{
   SINT32 TempPsLifetime = CurrentSetup.PSLifetime;
   ClearOutFram();
   FixFram();
   DepotFlag->IsADepot = FALSE;
   DepotFlag->WasADepot = FALSE;
   CurrentSetup.SerialPort = RS232DISABLED;
   CurrentSetup.PSLifetime = TempPsLifetime;
   StorePSLifeTimeCount();
   CurrentSetup.Overload = 0;
   CurrentSetup.GenAlarmCount = 0;
   CurrentSetup.FRAMInitialized = FRAM_INIT;
   BuildDefaultSpringRate();
   BackupCurrentSetupChange();
   SetUserIOToFactoryDefault();                                            /* 102-242-594 system controller*/
   CreateDefaultExecutive();
   DisableCode300();
   VelocityOn();
   PowerUpAlarmLogDataCheck();
   PowerUpEventHistoryDataCheck();
   FramInitialized = TRUE;
   GetPresetNames();
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\novram.ut"
#endif
/* End of include for unit test */




