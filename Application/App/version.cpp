/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/version.cpp_v   1.85   Dec 05 2017 12:08:50   RJamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/version.cpp_v  $
 * 
 *    Rev 1.85   Dec 05 2017 12:08:50   RJamloki
 * Update to version 12.3 release
 * 
 *    Rev 1.84   Nov 16 2017 16:31:08   RJamloki
 * Updated version to v12.3O
 * 
 *    Rev 1.83   Nov 07 2017 10:01:50   RJamloki
 * Update version to 12.3N
 * 
 *    Rev 1.82   Nov 07 2017 09:49:50   RJamloki
 * Update version to 12.3M
 * 
 *    Rev 1.81   Oct 18 2017 16:33:36   RJamloki
 * Updated version to v12.3L
 * 
 *    Rev 1.80   Jun 23 2017 13:22:30   RJamloki
 * Update to version v12.2
 * 
 *    Rev 1.79   Jun 21 2017 09:08:58   RJamloki
 * Hard coded reallocation memory changed to dynamic reallocation memory
 * 
 *    Rev 1.78   Jun 19 2017 13:14:00   RJamloki
 * Update to version v12.2I
 * 
 *    Rev 1.77   Jun 07 2017 17:00:52   RJamloki
 * change config variable to LowerFlowValveFlag
 * 
 *    Rev 1.76   Jun 07 2017 12:04:06   RJamloki
 * update FRAMConfigSetup.LowerFlowValve name
 * 
 *    Rev 1.75   Jun 06 2017 09:30:26   RJamloki
 * Update to version v12.2H
 * 
 *    Rev 1.74   May 25 2017 19:31:00   RJamloki
 * Update version 12.2G
 * 
 *    Rev 1.73   May 25 2017 17:57:56   RJamloki
 * Update relloating of memory for new config settings
 * 
 *    Rev 1.72   25 Aug 2016 13:23:28   RJamloki
 * Updated to version 12.2 release for bucket #2
 * 
 *    Rev 1.71   13 Jun 2016 09:58:04   RJamloki
 * Updated version 12.2E test for sunrise #2
 * 
 *    Rev 1.70   27 May 2016 13:59:12   RJamloki
 * Update version
 * 
 *    Rev 1.69   06 May 2016 16:29:14   RJamloki
 * Updated Version to Ver12.2D
 * 
 *    Rev 1.65   16 Dec 2015 14:16:00   RJamloki
 * Updated to 12.1K
 * 
 *    Rev 1.64   26 Oct 2015 10:33:36   LMarkure
 * Only updated the version on the system information screen
 * 
 *    Rev 1.63   May 05 2015 11:26:20   builder
 * Version string changed to 12.0 for the second Official Release
 * 
 *    Rev 1.62   30 Apr 2015 12:11:48   rjamloki
 * Version string changed to 12.I.9
 * 
 *    Rev 1.61   Apr 27 2015 14:04:02   builder
 * Version string change for official release 12.0
 * 
 *    Rev 1.60   16 Apr 2015 18:56:12   rjamloki
 * Build 12I8 for Two Pole Estop  boards
 * 
 *    Rev 1.59   16 Apr 2015 17:14:48   rjamloki
 * Changed version string to 12.I.7 for.Single Pole Estop Final release
 *
 *    Rev 1.58   16 Apr 2015 07:30:02   rjamloki
 * Version string changed. Fix for coverity issue 12555
 * 
 *    Rev 1.57   01 Apr 2015 13:02:52   amaurya
 * version string changed to 12.I.5
 * 
 *    Rev 1.56   16 Mar 2015 06:54:28   rjamloki
 * Upgrade routine cleaned up for 12.I.4
 * 
 *    Rev 1.55   03 Mar 2015 15:33:54   rjamloki
 * version 12.J for double pole estop testing
 *
 *    Rev 1.54   16 Feb 2015 02:31:10   amaurya
 * version string changed to 12.EOW
 * 
 *    Rev 1.53   05 Feb 2015 07:09:04   amaurya
 * Version changed to 12.I.3.
 * 
 *    Rev 1.52   03 Feb 2015 16:24:14   rjamloki
 * Label 12.I.2
 * 
 *    Rev 1.51   03 Feb 2015 07:23:06   amaurya
 * Assigning Min and Max values to old preset after 12.i changes.
 * 
 *    Rev 1.50   02 Feb 2015 07:08:28   amaurya
 * Changed for making the HoldPressure default value for each preset.
 * 
 *    Rev 1.49   30 Jan 2015 08:11:08   amaurya
 * version changed and new function defined After12IChange_2.
 * 
 *    Rev 1.48   21 Jan 2015 09:37:20   amaurya
 * new function defined After12IChanges().
 * 
 *    Rev 1.47   09 Jan 2015 10:07:18   rjamloki
 * version string changed
 * 
 *    Rev 1.46   08 Jan 2015 02:41:16   AnPawar
 * version changed and new function defined After12HChanges()
 * 
 *    Rev 1.45   05 Jan 2015 05:05:42   rjamloki
 * version string changed
 * 
 *    Rev 1.44   05 Jan 2015 04:28:32   rjamloki
 * version string changed
 * 
 *    Rev 1.43   02 Jan 2015 04:10:56   rjamloki
 * version string changed
 * 
 *    Rev 1.42   12 Dec 2014 05:31:50   RJamloki
 * Version changed to 12.H
 * 
 *    Rev 1.41   11 Dec 2014 08:37:44   AnPawar
 * version string changed.Welding history is preserved when code is updated to a newer version.
 * 
 *    Rev 1.40   28 Nov 2014 07:41:52   rjamloki
 * version changed.newly added downspeed limit alarms added to AlarmPtrFRAM.
 * 
 *    Rev 1.39   17 Nov 2014 09:59:04   RJamloki
 * Version string changed for 12.G.2
 * 
 *    Rev 1.38   14 Nov 2014 10:29:04   AnPawar
 * bit mask changed for down speed tuning in function  After12FChanges()
 * 
 *    Rev 1.37   14 Nov 2014 05:27:46   rjamloki
 * Version string changed.After12GChanges() added.
 * 
 *    Rev 1.36   12 Nov 2014 17:05:56   tayars
 * Added tuning fixes for using the real preset and horndown using tuned value
 * 
 *    Rev 1.35   11 Nov 2014 06:10:00   AnPawar
 * Added power on crc change event
 * 
 *    Rev 1.34   10 Nov 2014 05:00:00   AnPawar
 * Version string changed.CheckForVersionChange() function changed.After12FChanges() function added.
 * 
 *    Rev 1.33   20 Oct 2014 06:31:58   AnPawar
 * version string changed.
 * 
 *    Rev 1.32   06 Oct 2014 08:50:00   AnPawar
 * Version string changed
 * 
 *    Rev 1.31   06 Oct 2014 06:47:48   AnPawar
 * version string changed
 * 
 *    Rev 1.30   03 Oct 2014 06:14:06   rjamloki
 * version string changed
 * 
 *    Rev 1.29   26 Sep 2014 03:43:14   rjamloki
 * Version 12.E.5
 * 
 *    Rev 1.28   11 Sep 2014 11:10:44   rjamloki
 * Version changed to 12.E.4
 * 
 *    Rev 1.27   05 Sep 2014 05:20:42   rjamloki
 * Version chnaged to 12.E.3
 * 
 *    Rev 1.26   05 Sep 2014 01:38:36   rjamloki
 * Version 12.E.2 is same as 12.E.1. Checking in this file to keep SBC and WC versions at same level.
 * 
 *    Rev 1.25   22 Aug 2014 10:08:10   rjamloki
 * 12.E.1 webservices
 * 
 *    Rev 1.24   22 Aug 2014 07:03:40   rjamloki
 * Version 12.D.4 with hold force addition in weld results
 * 
 *    Rev 1.23   07 Aug 2014 15:47:22   tayars
 * New version string 12.D.3 for downspeed tuning
 * 
 *    Rev 1.22   28 Jul 2014 12:56:08   rjamloki
 * version 12.D.2
 * 
 *    Rev 1.21   15 Jul 2014 16:47:32   hasanchez
 * Change to version 12.D.1
 * 
 *    Rev 1.20   10 Jul 2014 14:23:48   tayars
 * Updated version string to 12.D
 * 
 *    Rev 1.19   09 Jul 2014 11:47:10   rjamloki
 * Version changed to 12.C.4
 * 
 *    Rev 1.18   20 Jun 2014 14:20:36   rjamloki
 * Version label updated to 12.C.3
 * 
 *    Rev 1.17   16 Jun 2014 08:56:00   rjamloki
 * Changed version label to 12.C.2
 * 
 *    Rev 1.16   11 Jun 2014 12:15:54   rjamloki
 * version change to 12.C.1
 * 
 *    Rev 1.15   27 May 2014 10:14:26   amaurya
 * Changed version to 12.C
 * 
 *    Rev 1.14   21 May 2014 10:53:06   rjamloki
 * Changed version string
 * 
 *    Rev 1.13   21 May 2014 03:54:44   rjamloki
 * version string updated
 * 
 *    Rev 1.12   23 Apr 2014 13:47:26   akaushal
 * Changed verion to 12.A.3
 * 
 *    Rev 1.11   21 Apr 2014 13:47:30   rjamloki
 * Version string updated to 12.B
 * 
 *    Rev 1.10   14 Apr 2014 10:25:24   rjamloki
 * Changed the version label to 12.7
 * 
 *    Rev 1.9   26 Mar 2014 12:39:56   rjamloki
 * version changed to 12.6,GetCurrentHwCnfg() declaration removed.CheckForVersionChange() function changed
 * 
 *    Rev 1.8   07 Mar 2014 11:11:12   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.7   06 Mar 2014 13:39:02   ygupta
 * Changed version string to 12.A
 * 
 *    Rev 1.6   05 Mar 2014 13:56:48   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.5   10 Feb 2014 05:59:56   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.4   03 Jan 2014 08:45:56   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION ------------------------------

     Module name: 

        Filename: version.c

      Written by:  
            Date: 06/02/2004 
        Language: "C"

 -------------------------------- DESCRIPTION --------------------------------
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "menu.h"
#include "dups.h"
#include "menu3.h"
#include "alarms.h"
#include "string.h"
#include "preset.h"
#include "battram.h"
#include "inports.h"
#include "outports.h"
#include "dups_api.h"
#include "version_change.h"
#include "psnvram.h"
#include "command.h"
#include "Events.h"
#include "Board.h"//included for flash CRC calculation
#include "genalarm.h"
#include "actnvram.h"
#include "DebugNew.h"
#include "util.h"
#include "NandFlash.h"
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define ALL_PRESETS        36
#define DEFAULT_SEEKTIME   500
#define DEFAULT_RAMPTIME   80
#define DEFAULT_SAMPLEVAL  1
#define VER_800            800
#define CURRENT_FRAM_VERSION FRAM_VER1209

extern UINT8 FRAMspare[35];
extern PSNOVRAMDATA PSNvRamDataFram;
extern CONFIGSETUP CurrentSetupSpare;
extern UINT8 FramDummy1[8192];
extern UINT8 FramInitDone[24];
extern UINT8 FramDummy2[8192];

/*
 ------------------------------- GLOBAL DATA ---------------------------------
*/
/*                       (scope is global to ALL files)                     */

const UINT16 CurrentVersion = 1200; /* Current version/revision in binary, no decimal */
SINT8 SWVersionLabel[SW_VERSION_LENTGH + 1] = "12.4";

/*
 ------------------------------- EXTERNAL DATA -------------------------------
 */
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*    struct VER_INFO               VersionNum,  void (*VerUpdateFunc)() */
const struct VER_INFO Ver_Info[] = {
		{VERMIN,               Nothing},
		{CURRENT_FRAM_VERSION, Nothing},
        {VERMAX,               Nothing}
};


/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES --------------------
 */
// UINT32 GetCurrentHwCnfg(void);
/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

void CheckForVersionChange (void)
/***************************************************************************/
/*                                                                         */
/*  This function is called on the powerup and check if the new version    */
/*  software is downloaded then it will update the Newly added variable of */
/*  latest version with the default values. This function will update the  */
/*  last saved data according to the latest software version.               */
/*                                                                         */
/***************************************************************************/
{
	UINT32 OldFlashCRC, CurrFlashCRC;
	SINT32 Indx = 0;
	CurrentSetup.ControlLevel = PSNvRamData.ControlLevel;//this is done to make sure we have control level value
														//before we record event.
	strncpy(CurrentSetup.PSSerialNumber, PSNvRamData.PSSerialNum, MAXSERIALNUMBER_LEN - 1);
	//At this point user is not known and N/A should go with all events before login
	strcpy(CurrentUser.UserId,"N/A");

	if((CURRENT_FRAM_VERSION != FramVerInfo.FramVersion))//mismatch in fram versions
	{
		if(CURRENT_FRAM_VERSION < FramVerInfo.FramVersion)
		{
			CONFIGSETUP *SetupPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
			SetupPtr->FRAMInitialized = 0;
		}
		if(CURRENT_FRAM_VERSION > FramVerInfo.FramVersion)
		{
			Convert_1208_to_1209();
		}
	}

	Indx = 0;
	//Now check if it is fresh board the old software version may have some garbage
	while((Indx < (SINT32)sizeof(SWVersionLabelOld)) && (SWVersionLabelOld[Indx] != 0))//Coverity 12555
	{
		//checking for valid printable ascii excluding null and Del
		 if ((SWVersionLabelOld[Indx] > 126) || (SWVersionLabelOld[Indx] < ' '))
			 SWVersionLabelOld[Indx] = 0;
		 else
			 Indx++;
	}

	if(strncmp(SWVersionLabelOld, SWVersionLabel, sizeof(SWVersionLabel)))
	{
		RecordEvents(EVENT_SOFTWAREVERSION_CHANGED,SWVersionLabelOld,SWVersionLabel);
		memcpy(SWVersionLabelOld,SWVersionLabel,sizeof(SWVersionLabel));
	}
	FramVerInfo.FramVersion = CURRENT_FRAM_VERSION;
	memset(&FramVerInfo.Resreved , 0, sizeof(FramVerInfo.Resreved));

	//Check for CRC changes now. Reading flash here. It will delay the power up a bit.
	OldFlashCRC = FramVerInfo.FlashCRC;//this is where we take old saved CRC from FRAM. On fresh board its quite possible
									  //to be all 0's or all FFs
	SINT32 CodeSize = (SINT32)__TEXT_END - (SINT32)__TEXT_START;
	SINT32 FlashOffset = (SINT32)__TEXT_START - (SINT32)__FLASH_RAM;
	CurrFlashCRC = ByteCRC((UINT8 *)(__FLASH_ROM + FlashOffset), (UINT32)CodeSize);
	if(CurrFlashCRC != OldFlashCRC)
	{
		RecordEvents(EVENT_POWERON_CRC_CHANGED,OldFlashCRC,CurrFlashCRC);
		FramVerInfo.FlashCRC = CurrFlashCRC;
	}
}


void SaveColdStartValues (void)
/*****************************************************************************/
/*                                                                           */
/*  This function will restore the normal factory defaults for the cold      */
/*  start values. First this function Make the CurrentPreset struct with     */
/*  default values and then save the preset as ColdStart preset in Fram.  */
/*                                                                           */
/*****************************************************************************/
{
   SetDefaultValues(); /* Store the default values in CurrentPreset struct. */
   CurrentPreset.PresetUpdateComplete = TRUE;
   strcpy(CurrentPreset.PresetID, "COLD START");        /* Name it              */
   SavePreset((PRESET_COLDSTART_INDEX), &CurrentPreset);
}

void Convert_1208_to_1209(void)
{

	const UINT32 CONFIGSETUP_FRAM_OFFSET_SIZE = sizeof(CONFIGSETUP)-sizeof(CONFIGSETUP_1208); //We calculate the first offset of the main system configuration
	const UINT32 CONFIGSETUP_CURRENT_OFFSET_SIZE = CONFIGSETUP_FRAM_OFFSET_SIZE + CONFIGSETUP_FRAM_OFFSET_SIZE; //We increase twice because current setup also increase

	const UINT32 FRAMPreset_Address_1208          = (UINT32)&FRAMPreset[0]       - CONFIGSETUP_FRAM_OFFSET_SIZE;
	const UINT32 FRAMspare_Address_1208           = (UINT32)&FRAMspare[0]        - CONFIGSETUP_FRAM_OFFSET_SIZE;
	const UINT32 FRAMHistory_Address_1208         = (UINT32)&FRAMHistory[0]      - CONFIGSETUP_FRAM_OFFSET_SIZE;
	const UINT32 PSNvRamDataFram_Address_1208     = (UINT32)&PSNvRamDataFram     - CONFIGSETUP_FRAM_OFFSET_SIZE;
	const UINT32 CurrentSetupSpare_Address_1208   = (UINT32)&CurrentSetupSpare   - CONFIGSETUP_FRAM_OFFSET_SIZE;
	const UINT32 FRAMPresetInfo_Address_1208      = (UINT32)&FRAMPresetInfo[0]   - CONFIGSETUP_CURRENT_OFFSET_SIZE; //here we use the second offset
	const UINT32 FlashInfo_Address_1208           = (UINT32)&FlashInfo           - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FRAMAlarmLogObj_Address_1208     = (UINT32)&FRAMAlarmLogObj     - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FRAMEventHistoryObj_Address_1208 = (UINT32)&FRAMEventHistoryObj - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FRAMUserIdObj_Address_1208       = (UINT32)&FRAMUserIdObj       - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 AutomationUsrId_Address_1208     = (UINT32)&AutomationUsrId     - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FRAMHORNGraph_Address_1208       = (UINT32)&FRAMHORNGraph       - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FRAMNotAssigned_Address_1208     = (UINT32)&FRAMNotAssigned     - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FramDummy1_Address_1208          = (UINT32)&FramDummy1          - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FramInitDone_Address_1208        = (UINT32)&FramInitDone        - CONFIGSETUP_CURRENT_OFFSET_SIZE;
	const UINT32 FramDummy2_Address_1208          = (UINT32)&FramDummy2          - CONFIGSETUP_CURRENT_OFFSET_SIZE;

	UINT8  *SdramPtr = new UINT8[FRAM_SIZE];

	//Dummy2
	UINT8 *Dummy2Ptr = (UINT8*)(&FramDummy2);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FramDummy2_Address_1208,sizeof(FramDummy2));//Copy FRAM to SDRAM
	memset(Dummy2Ptr,0,sizeof(FramDummy2));//set all zeroes in FRAM
	memcpy(Dummy2Ptr,SdramPtr,sizeof(FramDummy2));

	//InitDone
	UINT8 *InitDonePtr = (UINT8*)(&FramInitDone);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FramInitDone_Address_1208,sizeof(FramInitDone));//Copy FRAM to SDRAM
	memset(InitDonePtr,0,sizeof(FramInitDone));//set all zeroes in FRAM
	memcpy(InitDonePtr,SdramPtr,sizeof(FramInitDone));

	//Dummy1
	UINT8 *Dummy1Ptr = (UINT8*)(&FramDummy1);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FramDummy1_Address_1208,sizeof(FramDummy1));//Copy FRAM to SDRAM
	memset(Dummy1Ptr,0,sizeof(FramDummy1));//set all zeroes in FRAM
	memcpy(Dummy1Ptr,SdramPtr,sizeof(FramDummy1));

	//NotAssigned
	UINT8 *NotAssignedPtr = (UINT8*)FRAM1200_NOTASSIGNED_START;
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMNotAssigned_Address_1208,FRAM1200_NOTASSIGNED_SIZE);//Copy FRAM to SDRAM
	memset(NotAssignedPtr,0,FRAM1200_NOTASSIGNED_SIZE);//set all zeroes in FRAM
	memcpy(NotAssignedPtr,SdramPtr,FRAM1200_NOTASSIGNED_SIZE);

	//HORNGraph
	UINT8 *HORNGraphPtr = (UINT8*)FRAM1200_HORNGRAPH_START;
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMHORNGraph_Address_1208,FRAM1200_HORNGRAPH_SIZE);//Copy FRAM to SDRAM
	memset(HORNGraphPtr,0,FRAM1200_HORNGRAPH_SIZE);//set all zeroes in FRAM
	memcpy(HORNGraphPtr,SdramPtr,FRAM1200_HORNGRAPH_SIZE);

	//AutomationUsrId
	UINT8* AutomationUsrIdPtr = (UINT8*)(&AutomationUsrId);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)AutomationUsrId_Address_1208,sizeof(AutomationUsrId));//Copy FRAM to SDRAM
	memset(AutomationUsrIdPtr,0,sizeof(AutomationUsrId));//set all zeroes in FRAM
	memcpy(AutomationUsrIdPtr,SdramPtr,sizeof(AutomationUsrId));

	//UserIdObj
	FRAMUserID *UserIdObjPtr = (FRAMUserID*)FRAM1200_USERIDDATA_START;
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMUserIdObj_Address_1208,sizeof(FRAMUserIdObj));//Copy FRAM to SDRAM
	memset(UserIdObjPtr,0,sizeof(FRAMUserIdObj));//set all zeroes in FRAM
	memcpy(UserIdObjPtr,SdramPtr,sizeof(FRAMUserIdObj));

	//EventHistoryObj
	FRAMEventHistory *EventHistoryObjPtr = (FRAMEventHistory*)FRAM1200_EVENTDATA_START;
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMEventHistoryObj_Address_1208,sizeof(FRAMEventHistoryObj));//Copy FRAM to SDRAM
	memset(EventHistoryObjPtr,0,sizeof(FRAMEventHistoryObj));//set all zeroes in FRAM
	memcpy(EventHistoryObjPtr,SdramPtr,sizeof(FRAMEventHistoryObj));

	//AlarmLogObj
	FRAMAlarmLog *AlarmLogObjPtr = (FRAMAlarmLog*)(&FRAMAlarmLogObj);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMAlarmLogObj_Address_1208,sizeof(FRAMAlarmLogObj));//Copy FRAM to SDRAM
	memset(AlarmLogObjPtr,0,sizeof(FRAMAlarmLogObj));//set all zeroes in FRAM
	memcpy(AlarmLogObjPtr,SdramPtr,sizeof(FRAMAlarmLogObj));

	//FlashInfo
	FlashInfoFRAM *FlashInfoPtr = (FlashInfoFRAM*)(&FlashInfo);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FlashInfo_Address_1208,sizeof(FlashInfo));//Copy FRAM to SDRAM
	memset(FlashInfoPtr,0,sizeof(FlashInfo));//set all zeroes in FRAM
	memcpy(FlashInfoPtr,SdramPtr,sizeof(FlashInfo));

	//PresetInfo
	PRESETINFO *PresetInfoPtr = (PRESETINFO*)(&FRAMPresetInfo[0]);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMPresetInfo_Address_1208,sizeof(FRAMPresetInfo));//Copy FRAM to SDRAM
	memset(PresetInfoPtr,0,sizeof(FRAMPresetInfo));//set all zeroes in FRAM
	memcpy(PresetInfoPtr,SdramPtr,sizeof(FRAMPresetInfo));

	//CurrentSetupSpare
	CONFIGSETUP *CurrentSetupSparePtr = (CONFIGSETUP*)(&CurrentSetupSpare);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)CurrentSetupSpare_Address_1208,sizeof(CurrentSetupSpare));//Copy FRAM to SDRAM
	memset(CurrentSetupSparePtr,0,sizeof(CurrentSetupSpare));//set all zeroes in FRAM
	memcpy(CurrentSetupSparePtr,SdramPtr,sizeof(CurrentSetupSpare));

	//PSNvRamDataFram
	PSNOVRAMDATA *PSNvRamDataFramPtr = (PSNOVRAMDATA*)(&PSNvRamDataFram);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)PSNvRamDataFram_Address_1208,sizeof(PSNvRamDataFram));//Copy FRAM to SDRAM
	memset(PSNvRamDataFramPtr,0,sizeof(PSNvRamDataFram));//set all zeroes in FRAM
	memcpy(PSNvRamDataFramPtr,SdramPtr,sizeof(PSNvRamDataFram));

	//History
	UINT8* HistoryPtr = (UINT8*)(FRAM1200_HISTORY_START);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMHistory_Address_1208,FRAM1200_HISTORY_SIZE);//Copy FRAM to SDRAM
	memset(HistoryPtr,0,FRAM1200_HISTORY_SIZE);//set all zeroes in FRAM
	memcpy(HistoryPtr,SdramPtr,FRAM1200_HISTORY_SIZE);

	//Spare
	UINT8 *SparePtr = (UINT8*)(&FRAMspare[0]);
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMspare_Address_1208,sizeof(FRAMspare));//Copy FRAM to SDRAM
	memset(SparePtr,0,sizeof(FRAMspare));//set all zeroes in FRAM
	memcpy(SparePtr, SdramPtr, sizeof(FRAMspare));

	//preset
	SETUPS_Ver1200 *PresetPtr = (SETUPS_Ver1200*)FRAM1200_PRESET_START;
	memset(SdramPtr,0,sizeof(SdramPtr));//set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAMPreset_Address_1208,FRAM1200_PRESET_SIZE);//Copy FRAM to SDRAM
	memset((UINT8*)FRAM1200_PRESET_START,0,FRAM1200_PRESET_SIZE);//set all zeroes in FRAM
	memcpy(PresetPtr,SdramPtr,FRAM1200_PRESET_SIZE);

	//config setup
	CONFIGSETUP *ConfigSetupPtr = (CONFIGSETUP*)FRAM1200_CONFIG_START; //get config setup pointer
	memset(SdramPtr,0,sizeof(SdramPtr)); //set all zeroes in FRAM
	memcpy(SdramPtr,(UINT8*)FRAM1200_CONFIG_START,sizeof(CONFIGSETUP_1208)); //Copy FRAM to SDRAM
	memset((UINT8*)FRAM1200_CONFIG_START,0,sizeof(CONFIGSETUP)); //set all zeroes in FRAM
	memcpy(ConfigSetupPtr, SdramPtr, sizeof(CONFIGSETUP_1208)); //copy SDRAM to FRAM

	FRAMConfigSetup.WeldHistoryPtr = FRAMConfigSetup.WeldHistoryPtr + CONFIGSETUP_FRAM_OFFSET_SIZE;
	FRAMConfigSetup.LowerFlowValveFlag = FALSE;
	FRAMConfigSetup.WebServiceAutomation = TRUE;
	FRAMConfigSetup.WebServiceAutorityCheck = TRUE;

	delete[] SdramPtr;
}
