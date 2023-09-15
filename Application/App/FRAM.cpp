/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FRAM.cpp_v   1.21   16 Mar 2015 03:53:40   rjamloki  $
*/
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/FRAM.cpp_v  $
 * 
 *    Rev 1.21   16 Mar 2015 03:53:40   rjamloki
 * Minor Reordering after preset size increment.
 * 
 *    Rev 1.20   11 Dec 2014 08:35:12   AnPawar
 * decreased the size of FRAMNotAssigned array.
 * 
 *    Rev 1.19   28 Nov 2014 07:35:40   rjamloki
 * FramVersionInfo variable changed to FramVerInfo.
 * 
 *    Rev 1.18   10 Nov 2014 04:49:32   AnPawar
 * Added FramVerInfo 
 * 
 *    Rev 1.17   26 Sep 2014 03:14:24   rjamloki
 * Removed psos references
 * 
 *    Rev 1.16   11 Sep 2014 10:51:36   rjamloki
 * Added OldSoftwareVersion for version change event
 * 
 *    Rev 1.15   05 Sep 2014 04:45:44   rjamloki
 * Removed compressed preset. Added FRAMPresetInfo object to keep frequently changing preset information.
 * 
 *    Rev 1.14   18 Aug 2014 01:39:00   rjamloki
 * Removed struct in front of now packed user id object definition.
 * 
 *    Rev 1.13   28 Jul 2014 12:44:16   rjamloki
 * Fixed FRAM preset size. Increased FRAMHorngraph buffer to support Amp and Current graph for Horn Scan
 * 
 *    Rev 1.12   09 Jul 2014 15:06:42   rjamloki
 * Added Automation user id in FRAM
 * 
 *    Rev 1.11   21 May 2014 10:47:56   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:05:16   rjamloki
 * Added function for FRAM chip select
 * 
 *    Rev 1.9   07 May 2014 10:20:22   rjamloki
 * User count,Number of enabled user and UserID array are now kept in a structure.
 * 
 *    Rev 1.8   21 Apr 2014 13:28:42   rjamloki
 * Event and Alarm log tables created in FRAM
 * 
 *    Rev 1.7   07 Mar 2014 11:11:10   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.6   05 Mar 2014 13:56:24   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.5   03 Jan 2014 08:45:26   rjamloki
 * Header Fix.
 * 
 *    Rev 1.4   19 Dec 2013 06:10:24   rjamloki
 * Header fixes.
 * 
 *    Rev 1.3   18 Dec 2013 10:03:38   rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.2   17 Dec 2013 01:04:02   rjamloki
 * Header fixes.
 *
 *    Rev 1.1   05 Jun 2013 08:37:56   amaurya
 * Initial revision 2.
 *
 * Revision 1.1  2013/05/14 15:02:50  Ellery
 * First Revision for Dallas testing
 *
 *    Rev 1.0   03 Apr 2013 06:14:38   amaurya
 * Initial revision.
 *
 ******************************************************************************/
#include "preset.h"
#include "Alarms.h"
#include "weld_obj.h"
#include "psnvram.h"
#include "NandFlash.h"
#include "command.h"
#include "A1025R.h"
#include "CPU.h"
#include "Events.h"
#include "battram.h"

SINT8 SWVersionLabelOld[SW_VERSION_LENTGH + 1]__attribute__((section (".FRAM")));
FramVersionInfo FramVerInfo __attribute__((section (".FRAM")));
UINT8 ReservedStart[0xFF - sizeof(FramVersionInfo)]__attribute__((section (".FRAM")));
UINT8 SystemStart[0x0800]__attribute__((section (".FRAM")));
ALARM_MASKS FRAMAlarmMasks __attribute__((section (".FRAM")));
UINT8 FRAMDUPSLock[64]__attribute__((section (".FRAM")));
UINT8 FRAMDUPStoCOPS[64]__attribute__((section (".FRAM")));
UINT8 FRAMCOPStoDUPS[32]__attribute__((section (".FRAM")));
UINT8 FRAMHORNSCAN_START[128]__attribute__((section (".FRAM")));
UINT8 FRAMDUPSBackup[16]__attribute__((section (".FRAM")));
BUCMENU_1200 FRAMBUCMenu __attribute__((section (".FRAM")));
DEPOT_FLAGS FRAMDEPOTFlags __attribute__((section (".FRAM")));
UINT8 FRAMUnUsed[100]__attribute__((section (".FRAM")));
CONFIGSETUP FRAMConfigSetup __attribute__((section (".FRAM")));

SETUPS_Ver1200 FRAMPreset[37]__attribute__((section (".FRAM")));
UINT8 FRAMspare[35]__attribute__((section (".FRAM")));
WELD_DATA FRAMHistory[50] __attribute__((section (".FRAM")));

//This PsNvRamData object is spare. Its here to keep the fram memory layout unchanged after 12.F.
//The actual place for this object is eeprom area of mac chip. It is used to initialize PsNvramData ram object if we are upgrading after
//12.F
PSNOVRAMDATA PSNvRamDataFram  __attribute__((section (".FRAM")));
//A variable with the name "CurrentSetup" is defined in RAM for 12.G and this var below is just here to keep the fram layout same.
//FRAMConfigSetup above is already storing the setup data. CurrentSetup ram variable is initialize from FRAMConfigSetup at power up.
//Every change in CurrentSetup ram variable through menu is going to  FRAMConfigSetup through OP_CHANGE_CURRENT_SETUP and
//OP_CHANGE_CURRENT_PRESET messages.
CONFIGSETUP CurrentSetupSpare __attribute__((section (".FRAM")));
PRESETINFO FRAMPresetInfo[1001 + NUM_SPECIAL_PRESET] __attribute__((section(".FRAM")));

struct FlashInfoFRAM FlashInfo  __attribute__((section (".FRAM")));
FRAMAlarmLog FRAMAlarmLogObj __attribute__ ((section (".FRAM")));
FRAMEventHistory FRAMEventHistoryObj __attribute__ ((section (".FRAM")));
FRAMUserID FRAMUserIdObj __attribute__ ((section (".FRAM")));
char AutomationUsrId[11] __attribute__ ((section (".FRAM")));
UINT8 FRAMHORNGraph[2400]__attribute__((section (".FRAM")));
UINT8 FRAMNotAssigned[0x07AC]__attribute__((section (".FRAM")));
UINT8 FramDummy1[8192] __attribute__((section (".FRAM")));
UINT8 FramInitDone[24] __attribute__((section (".FRAM")));
UINT8 FramDummy2[8192] __attribute__((section (".FRAM")));


void SetupFramChipSelect()
{
	CPU::SetupChipSelect(CHIPSELCT_PIN1, WAITSTATES_FRAM_CS1, DATABUSWIDTH_FRAM_CS1, (void *) FRAM_BASEADDRESS);
}
