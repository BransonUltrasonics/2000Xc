/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/alarms.cpp_v   1.27   16 Apr 2015 07:19:18   rjamloki  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/alarms.cpp_v  $
 * 
 *    Rev 1.27   16 Apr 2015 07:19:18   rjamloki
 * Setting cycle number to zero for aborted cycles in alarm log
 * 
 *    Rev 1.26   30 Jan 2015 08:09:14   amaurya
 * NonSetupAlarmIDs[] changed.
 * 
 *    Rev 1.25   08 Jan 2015 03:18:18   AnPawar
 * printf removed
 * 
 *    Rev 1.24   02 Jan 2015 03:58:40   rjamloki
 * duplicate alarm codes corrected
 * 
 *    Rev 1.23   11 Dec 2014 08:34:28   AnPawar
 * changed the alarm ids.
 * 
 *    Rev 1.22   28 Nov 2014 07:31:56   rjamloki
 * Change to avoid warnings.
 * 
 *    Rev 1.21   10 Nov 2014 04:43:52   AnPawar
 * Added Downspeed reject limit alarm in NonSetupAlarmIDs array,
 * 
 *    Rev 1.20   20 Oct 2014 06:16:10   AnPawar
 * alarm code changed in NonSetupAlarmIDs array
 * 
 *    Rev 1.19   03 Oct 2014 05:48:52   rjamloki
 * GetAlarmLogData()  function changed to correct cycle counter
 * 
 *    Rev 1.18   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.17   11 Sep 2014 10:48:48   rjamloki
 * moved event related things to event.cpp file
 * 
 *    Rev 1.16   05 Sep 2014 04:31:08   rjamloki
 * Recording events on control level c and above
 * 
 *    Rev 1.15   18 Aug 2014 01:37:28   rjamloki
 * Cleaned up and added comments
 * 
 *    Rev 1.14   07 Aug 2014 15:29:56   tayars
 * Added support for the event reason
 * 
 *    Rev 1.13   28 Jul 2014 12:38:32   rjamloki
 * Review Comment fixes
 * 
 *    Rev 1.12   09 Jul 2014 14:53:54   rjamloki
 * Added numbers in Alarm ID table for PartClamp and part Presnt active NC alarms,
 * 
 *    Rev 1.11   11 Jun 2014 11:17:20   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   27 May 2014 10:11:56   amaurya
 * Added login logout event
 * 
 *    Rev 1.9   21 May 2014 10:47:44   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 02:50:12   rjamloki
 * coverity fix event log data1 and data2 fix
 * 
 *    Rev 1.7   07 May 2014 10:18:06   rjamloki
 * GetEventID() GetAlarmLogData() GetEventHistoryData() RecordEvents() function  changed to record event data.
 * 
 *    Rev 1.6   23 Apr 2014 13:51:34   akaushal
 * Added code for alarm ID and boundary checking. 
 * 
 *    Rev 1.5   21 Apr 2014 13:19:24   rjamloki
 * Event and Alarm logging implementation added
 * 
 *    Rev 1.4   05 Mar 2014 13:56:14   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:18   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
                                                                            

/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with Alarms and their submenus                           */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "string.h"
#include "weld_obj.h"
#include "genalarm.h"
#include "battram.h"
#include "alarms.h"
#include "alsetup.h"
#include "sc.h"
#include "menu7a.h"
#include "WeldManagerTask.h"
#include "command.h"
#include "statedrv.h"


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                     (scope is global to ALL files)                       */

UINT8 AlarmDetectedFlag = FALSE, SetupAlarmDetectedFlag = FALSE;
ALARM_MASKS *AlarmPtrFRAM;
ALARM_MASKS AlarmPtrRam;

/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/

UINT16 TotalAlarmCount;

static UINT16  NoCycleAlarmCount;
static UINT16  OverloadAlarmCount;
static UINT16  EquipmentFailureAlarmCount;
static UINT16  CycleModifiedAlarmCount;
static UINT16  SuspectAlarmCount;
static UINT16  RejectAlarmCount;
static UINT16  CalibrateAlarmCount;
static UINT16  WarningCount;

MENUEND endlistGA = { TRUE };
enum ERRORCODE_ARG ErrorCode;
UINT16 ErrorCodeFlag;

static AlarmLog AlarmLogData;

char LoggedInUsrId[6] = "N/A";


UINT16 SetupAlarmIDs[MAX_SETUP_ALARMGROUP][MAX_ALARM_ONEGROUP] = {\
	{0x207 ,0x208 ,0x209 ,0x20A ,0x20B ,0x20C ,0x20D ,0x20E ,0x20F ,0x210 ,0x211 ,0x212 ,0x213 ,0x214 ,0x215 ,0x216 ,0x217 ,0x218 ,0x219 ,0x21A ,0x21B ,0x21C ,0x21D ,0x21E ,0x21F ,0x220 ,0x221 },\
	{0x222 ,0x223 ,0x224 ,0x225 ,0x226 ,0x227 ,0x228 ,0x229 ,0x22A ,0x22B ,0x22C ,0x22D ,0x22E ,0x22F ,0x230 ,0x231 ,0x232 ,0x233 ,0x234 ,0x235 ,0x236 ,0x237 ,0x238 ,0x239 ,0x23A ,0x23B ,0x23C },\
	{0x23D ,0x23E ,0x23F ,0x240 ,0x241 ,0x00  ,0x00  ,0x242 ,0x243 ,0x244 ,0x245 ,0x246 ,0x247 ,0x248 ,0x249 ,0x24A ,0x24B ,0x24C ,0x24D ,0x24E ,0x24F ,0x250 ,0x251 ,0x252 ,0x253 ,0x254 ,0x255 },\
	{0x256 ,0x257 ,0x258 ,0x259 ,0x25A ,0x25B ,0x25C ,0x25D ,0x25E ,0x25F ,0x260 ,0x261 ,0x262 ,0x263 ,0x264 ,0x265 ,0x266 ,0x267 ,0x268 ,0x000 ,0x000 ,0x000 ,0x269 ,0x26A ,0x26B ,0x26C ,0x26D },\
	{0x26E ,0x26F ,0x270 ,0x271 ,0x272 ,0x273 ,0x274 ,0x275 ,0x276 ,0x277 ,0x278 ,0x279 ,0x27A ,0x27B ,0x27C ,0x27D ,0x27E ,0x000 ,0x27F ,0x280 ,0x281 ,0x282 ,0x283 ,0x284 ,0x285 ,0x286 ,0x287 },\
	{0x288 ,0x289 ,0x28A ,0x28B ,0x28C ,0x28D ,0x28E ,0x28F ,0x290 ,0x291 ,0x292 ,0x293 ,0x294 ,0x295 ,0x296 ,0x297 ,0x298 ,0x299 ,0x29A ,0x29B ,0x29C ,0x29D ,0x29E ,0x29F ,0x2A0 ,0x2A1 ,0x2A2 },\
	{0x2A3 ,0x2A4 ,0x2A5 ,0x2A6 ,0x2A7 ,0x2A8 ,0x2A9 ,0x2AA ,0x2AB ,0x2AC ,0x2AD ,0x2AE ,0x2AF ,0x2B0 ,0x2B1 ,0x2B2 ,0x2B3 ,0x2B4 ,0x2B5 ,0x2B6 ,0x2B7 ,0x2B8 ,0x000 ,0x000 ,0x2B9 ,0x2BA ,0x2BB },\
	{0x2BC ,0x2BD ,0x2BE ,0x2BF ,0x2C0 ,0x2C1 ,0x2C2 ,0x2C3 ,0x2C4 ,0x2C5 ,0x2C6 ,0x2C7 ,0x2C8 ,0x2C9 ,0x2CA ,0x2CB ,0x2CC ,0x2CD ,0x2CE ,0x2CF ,0x2D0 ,0x2D1 ,0x2D2 ,0x2D3 ,0x2D4 ,0x2D5 ,0x2D6 },\
	{0x2D7 ,0x2D8 ,0x2D9 ,0x2DA ,0x000 ,0x2DB ,0x000 ,0x2DC ,0x2DD ,0x2DE ,0x2DF ,0x203 ,0x2E0 ,0x2E1 ,0x2E2 ,0x2E3 ,0x2E4 ,0x2E5 ,0x2E6 ,0x2E7 ,0x2E8 },\
	{0x2E9 ,0x2EA ,0x2EB ,0x2EC ,0x2ED ,0x2EE ,0x2EF ,0x2F0 ,0x2F1 ,0x2F2 ,0x2F3 ,0x2F4 ,0x2F5 ,0x2F6 ,0x2F7 ,0x2F8 ,0x2F9 },\
};

UINT16 NonSetupAlarmIDs[MAX_ALARMGROUP_EXCLUDINGSETUP][MAX_ALARM_ONEGROUP] = {\
	{0x551 ,0x552 ,0x553 ,0x554 ,0x555 ,0x556 ,0x557 ,0x558 ,0x559 ,0x55A ,0x55B ,0x55C ,0x55D ,0x55E},\
	{0x507 ,0x508 ,0x503 ,0x504 ,0x509 ,0x50A ,0x50B ,0x50C ,0x50D ,0x50E ,0x50F ,0x510 ,0x505 ,0x506 ,0x507, 0x508, 0, 0x511 ,0x512 ,0x513 ,0x514 ,0x515},\
	{0xB22 ,0xB23 ,0xB21 ,0x020 ,0x022 ,0xB26 ,0xB24 ,0xB25 ,0xB27 ,0x017},\
	{0x701 ,0x000 ,0x708 ,0x702 ,0x000 ,0x709 ,0x70A ,0x706 ,0x70C ,0x70D ,0x70E ,0x70F ,0x703 ,0x710 ,0x711 ,0x000 ,0x000 ,0x716 },\
	{0x621 ,0x604 ,0x602 ,0x603 ,0x605 ,0x622 ,0x623 ,0x624 ,0x625 ,0x626 ,0x627 ,0x628 ,0x629 ,0x62A ,0x62B ,0x62C ,0x601 ,0x62D ,0x62E ,0x62F ,0x630 ,0x631 ,0x609 ,0x632 ,0x633 ,0x634 ,0x635 ,0x636 ,0x637 ,0x638},\
	{0x301 ,0x303 ,0x304 ,0x305 ,0x306 ,0x307 ,0x308 ,0x309 ,0x30A ,0x30B ,0x30C ,0x30D ,0x30E ,0x317 ,0x302 ,0x30F ,0x310 ,0x311 ,0x312 ,0x313 ,0x314 ,0x315 ,0x316},\
	{0x417, 0x418, 0x419, 0x41A, 0x41B, 0x41C, 0x41D, 0x41E, 0x41F, 0x420, 0x421, 0x422, 0x423},\
};

/*--------------------------------- CODE -----------------------------------*/
/*-------------------------------------------------------------------------*/
/*                                                                         */
/*  Lookup Tables.  The "hardware" method of computing CRCs involves bit   */
/*  manipulations, which is very inefficient for a software computation.   */
/*  Instead of computing the CRC bit-by-bit, a 256-element lookup table    */
/*  can be used to perform the equivalent of 8 bit operations at a time.   */
/*  (This is described in "Byte-wise CRC Calculations" in IEEE Micro,      */
/*  June 1983, pp. 40-50.)  For a CRC-16, the lookup table consists of 256 */
/*  2-byte WORDs (see below, or the CRC16.PAS unit for the actual table,   */
/*  or the CRCTable program for computation of the lookup table for the    */
/*  x16 + x15 + x2 + 1 generator polynomial):                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/
const UINT16 CRCTable[256] =
 {0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0,
  0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41,
  0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0,
  0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1,
  0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341,
  0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1,
  0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0,
  0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1, 0xE981, 0x2940,
  0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1,
  0xEC81, 0x2C40, 0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041, 0xA001, 0x60C0,
  0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740,
  0xA501, 0x65C0, 0x6480, 0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0,
  0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01, 0x7EC0,
  0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541,
  0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0,
  0x7080, 0xB041, 0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440, 0x9C01, 0x5CC0,
  0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40,
  0x9901, 0x59C0, 0x5880, 0x9841, 0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1,
  0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0,
  0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};

UINT16 ByteCRC(UINT8 * Ptr, UINT32 Length)
/*****************************************************************************/
/*                                                                           */
/*   The following is a little cryptic (but executes very quickly).          */
/*   The algorithm is as follows:                                            */
/*   1. exclusive-or the input byte with the low-order byte of               */
/*      the CRC register to get an INDEX                                     */
/*   2. shift the CRC register eight bits to the right                       */
/*   3. exclusive-or the CRC register with the contents of                   */
/*      Table[INDEX]                                                         */
/*   4. repeat steps 1 through 3 for all bytes}                              */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 CRCRegister = 0;
   UINT8  Index;
   while(Length-- > 0){
      Index = (UINT8)((CRCRegister ^ * Ptr++) & 0xff);
      CRCRegister = CRCRegister >> 8;
      CRCRegister = CRCRegister ^ CRCTable[Index];
   }
   return(CRCRegister);
}

void PowerUpAlarmLogDataCheck(void)
/* At Power-up this function is used to check whether the stored alarms are valid or invalid
 * Once validated, this will not change until next ColdStart
 */
{
   if(FRAMAlarmLogObj.AlarmLogCheckSum !=  ALARMLOGINITIALIZED_CHECKSUM)
   {
      //CLEAR  FramAlarmLogObj in FRAM.
      FRAMAlarmLogObj. CircularIndex = -1;
      FRAMAlarmLogObj. AlarmLogCount = 0;
      FRAMAlarmLogObj. AlarmLogCheckSum = ALARMLOGINITIALIZED_CHECKSUM;
   }
}

UINT32 GetAlarmID(UINT32 AlarmCode, BOOLEAN SetupAlarm)
{
   UINT32 AlarmType = ALARMTYPE(AlarmCode);
   UINT32 SerBit = ALARMCODE(AlarmCode);
   UINT32 AlarmID = 0;
   UINT16 AlarmNum = 0;
   BOOLEAN ExitFlag = FALSE;
   for(int i = 0; (i < MAX_ALARM_ONEGROUP) && (ExitFlag == FALSE); i++){
	   if((SerBit >> i ) & 0x1){
		   AlarmNum = i;
		   ExitFlag = TRUE;
	   }
   }

   if(SetupAlarm)
   {
	  if((AlarmType > 0) && (AlarmType <= MAX_SETUP_ALARMGROUP) && (AlarmNum < MAX_ALARM_ONEGROUP)
			  && (AlarmNum > 0))
		  AlarmID = SetupAlarmIDs[AlarmType - 1][AlarmNum - 1];
   }
   else
   {
	  if((AlarmType > 0) && (AlarmType <= MAX_ALARMGROUP_EXCLUDINGSETUP) && (AlarmNum < MAX_ALARM_ONEGROUP)
			  && (AlarmNum > 0))
		   AlarmID = NonSetupAlarmIDs[AlarmType - 1][AlarmNum - 1];
   }

   return AlarmID;
}



void GetAlarmLogData(UINT32 AlarmCode, bool SetupAlarm)
/* this function fills the Alarm information and other relevant data to the structure.
 *
 * @parameter AlarmCode : alarm code has the information of Alarm Code and Alarm Type
 * @parameter SetupAlarm : Setup alarm tells whether the Alarm is General or Setup Alarm
 * @return : No return value
 */
{
   UINT32 AlarmID = GetAlarmID(AlarmCode,SetupAlarm);
   RTCTime PresentTime;
   SINT16 CurrStateIndex = *CurrentIndexPointer;
   //Update Time
   RTClock::GetCurrentTime(&PresentTime);
   AlarmLogData.TS.Years          = PresentTime.Years;
   AlarmLogData.TS.Century_Month  = PresentTime.Century_Month;
   AlarmLogData.TS.Day            = PresentTime.Day;
   AlarmLogData.TS.Hour           = PresentTime.Hour;
   AlarmLogData.TS.Minute         = PresentTime.Minute;
   AlarmLogData.TS.Second         = PresentTime.Second;

   AlarmLogData.AlarmID       = AlarmID;
   AlarmLogData.AlarmNum      = FRAMAlarmLogObj.AlarmLogCount;   
   //Don't show the cycle number in Alarm log if trigger is not reached or cycle is aborted or not in weld sequence.
   if((CurrentSequence == WELD) && (CycleAbort == FALSE) && (WeldSequence[CurrStateIndex]->state >= TRIGGEREDSTATE))
	   AlarmLogData.CycleNum = CurrentPreset.WeldCount + 1;
   else
	   AlarmLogData.CycleNum = 0;
   AlarmLogData.PresetNum     = CurrentSetup.ActivePreset;
   AlarmLogData.PresetRevNum  = CurrentPreset.Rev;

   strcpy((char*)&AlarmLogData.ActuatorAssemblyID,(char*)&CurrentPreset.ActAssemblyNum);
   strcpy((char*)&AlarmLogData.PSAssemblyID,(char*)&CurrentPreset.PSAssemblyNum);
   if(CurrentSetup.Automation)
	   strncpy((char*)&AlarmLogData.UserID, AutomationUsrId, sizeof(AlarmLogData.UserID) - 1);
   else
	   strcpy((char*)&AlarmLogData.UserID, CurrentUser.UserId);
   AlarmLogData.AlarmLogCRC = ByteCRC((UINT8*)&AlarmLogData,sizeof(AlarmLog) - sizeof(UINT16));
}


void WriteAlarmLog(UINT32 AlarmCode, bool SetupAlarm)
/* this function records the  alarm that are generated to the NVRAM memory
 * This function implements a circular queue and adds new Alarm at the end of the list
 *
 * @parameter AlarmCode : alarm code has the information of Alarm Code and Alarm Type
 * @parameter SetupAlarm : Setup alarm tells whether the Alarm is General or Setup Alarm
 * @return : No return value
 */
{
   //Update Circular Index
   FRAMAlarmLogObj.AlarmLogCount++;
   FRAMAlarmLogObj.CircularIndex = (FRAMAlarmLogObj.CircularIndex + 1) % MAX_ALARM_ENTRIES; //starts with 0
   GetAlarmLogData(AlarmCode,SetupAlarm);
   memcpy(&FRAMAlarmLogObj.AlarmLogObjs[FRAMAlarmLogObj.CircularIndex],&AlarmLogData,sizeof(AlarmLog));
}



UINT32 ReadAlarmLog(AlarmLog * LogData, UINT32 LogsCount)
/* this function is called to read the last MAX_ALARM_ENTRIES number of Alarm Logs \\
 * from the NVRAM and fills the buffer passed in the Logdata.
 *
 * @parameter LogData : Buffer where the Alarm logs are copied
 * @parameter LogsCount : Count of Alarms that needs to be copied
 * @return TotalAlarmsLogRead :Count of copied alarms
 */
{
   UINT32 Length = 0, CurrentIndex = 0, Indx1 = 0;
   SINT32 Indx2;
   AlarmLog * Address;
   if(FRAMAlarmLogObj.CircularIndex < 0)//Cold Start Condition
   {
      CurrentIndex = 0;
      Length = 0;
   }
   else
   {
      CurrentIndex = (UINT32)FRAMAlarmLogObj.CircularIndex;
      Address = &FRAMAlarmLogObj.AlarmLogObjs[CurrentIndex];
	   if((FRAMAlarmLogObj.CircularIndex < 0) || (FRAMAlarmLogObj.CircularIndex > MAX_ALARM_ENTRIES)) // error checking
	   {
			Length = 0;
	   }
	  else
	   {
	   if(FRAMAlarmLogObj.AlarmLogCount < LogsCount ) // Data is less than MAX_ALARM_ENTRIES
	       LogsCount = FRAMAlarmLogObj.AlarmLogCount;

	   if((FRAMAlarmLogObj.AlarmLogCount-1) <= CurrentIndex) //<100, Not written back to 0 location
	   {
	      for(Indx1 = 0; Indx1 < LogsCount; Indx1++)
	         memcpy((LogData +  Indx1),(Address - Indx1),sizeof(AlarmLog)); // No roll back at end
	      Length+= LogsCount;
	   }
	   else { //I need to roll back from index 0 to 99th index
		  Indx2 = 0;
	      for(Indx1 = 0; Indx1 <= CurrentIndex; Indx1++, Indx2++)
	      {
	      	memcpy((LogData + Indx2),(Address - Indx1),sizeof(AlarmLog));
	      }
	      Length += FRAMAlarmLogObj.CircularIndex;
	      Address = &FRAMAlarmLogObj.AlarmLogObjs[MAX_ALARM_ENTRIES - 1];
	      for(Indx1 = 0; Indx1 < (UINT32)(MAX_ALARM_ENTRIES - FRAMAlarmLogObj.CircularIndex - 1); Indx1++, Indx2++)
	      {
	      	memcpy((LogData + Indx2),(Address - Indx1),sizeof(AlarmLog));
	      }
	      Length += (MAX_ALARM_ENTRIES - FRAMAlarmLogObj.CircularIndex);
	   }
	  }
   }
   return Length;
}


UINT8 IfAlarmEnabled(UINT32 AlarmCopy, UINT32 BitMask)
{
   UINT8 AlarmEnabled = FALSE;

   if(AlarmCopy & BitMask)
      AlarmEnabled = TRUE;

   return(AlarmEnabled);   
}


/* --  No Cycle Alarms  --*/

void CountNoCycleAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyNoCycleAlarm;

   FinalResults.NoCycleAlarms &= AlarmPtrFRAM->NoCycle;
   CopyNoCycleAlarm = FinalResults.NoCycleAlarms;
   if (CopyNoCycleAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyNoCycleAlarm & AlarmMask)
            NoCycleAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Overload Alarms  --*/

void CountOverloadAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyOverloadAlarm;

   FinalResults.OverloadAlarms &= AlarmPtrFRAM->Overload;
   CopyOverloadAlarm = FinalResults.OverloadAlarms;
   if (CopyOverloadAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyOverloadAlarm & AlarmMask)
            OverloadAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Equipment Failure Alarms  --*/

void CountEquipmentFailureAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyEquipmentFailureAlarm;

   FinalResults.EquipmentFailureAlarms &= AlarmPtrFRAM->EquipmentFailure;
   CopyEquipmentFailureAlarm = FinalResults.EquipmentFailureAlarms;
   if (CopyEquipmentFailureAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if(CopyEquipmentFailureAlarm & AlarmMask)
            EquipmentFailureAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}

/* --  Cycle Modified Alarms  --*/

void CountCycleModifiedAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyCycleModifiedAlarms;

   FinalResults.CycleModifiedAlarms &= AlarmPtrFRAM->CycleModified;
   CopyCycleModifiedAlarms = FinalResults.CycleModifiedAlarms;
   if (CopyCycleModifiedAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyCycleModifiedAlarms & AlarmMask)
            CycleModifiedAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Warning Alarms  --*/

void CountWarnings(void)
{
   UINT32 AlarmMask;
   UINT32 CopyWarningAlarms;

   FinalResults.Warnings &= AlarmPtrFRAM->Warning;
   CopyWarningAlarms = FinalResults.Warnings;
   if (CopyWarningAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyWarningAlarms & AlarmMask)
            WarningCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Calibrate Alarms  --*/

void CountCalibrateAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyCalibrateAlarms;

   FinalResults.CalibrateAlarms &= CALIBRATEMASK;
   CopyCalibrateAlarms = FinalResults.CalibrateAlarms;
   if (CopyCalibrateAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyCalibrateAlarms & AlarmMask)
            CalibrateAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


void CountSuspectResults(void)
{
   UINT32 SuspectBitResultMask;
   UINT32 CopySuspectBitResult;

   FinalResults.SuspectBitResult &= AlarmPtrFRAM->Suspect;
   CopySuspectBitResult = FinalResults.SuspectBitResult;
   if(CopySuspectBitResult != 0)
      {
      SuspectBitResultMask = BIT1;
      while(SuspectBitResultMask < BIT28)
         {
         if( CopySuspectBitResult & SuspectBitResultMask)
            SuspectAlarmCount++;
         SuspectBitResultMask <<= 1;
         }
      }
}


void CountRejectResults(void)
{
   UINT32 RejectBitResultMask;
   UINT32 CopyRejectBitResult;

   FinalResults.RejectBitResult &= (AlarmPtrFRAM->Reject | REJECTALARMMASK);
   CopyRejectBitResult = FinalResults.RejectBitResult;
   if(CopyRejectBitResult != 0)
      {
      RejectBitResultMask = BIT1;
      while(RejectBitResultMask < BIT28)
         {
         if( CopyRejectBitResult & RejectBitResultMask)
            RejectAlarmCount++;
         RejectBitResultMask <<= 1;
         }
      }
}


void CountAlarms(void)
{
   UINT16 SetupAlarmCount;
   UINT16 RejectAlarmCountFlag = FALSE;

   AlarmPtrFRAM = (ALARM_MASKS *)FRAM1200_ALARM_START;   /* Setup pointer to FRAM structure for masks  */
   TotalAlarmCount = 0;
   NoCycleAlarmCount = 0;
   OverloadAlarmCount = 0;
   EquipmentFailureAlarmCount = 0;
   CycleModifiedAlarmCount = 0;
   CalibrateAlarmCount = 0;
   WarningCount = 0;
   SuspectAlarmCount = 0;
   RejectAlarmCount = 0;

/*---  The reverse order of these checks will set the priority of which  ---*/
/*---  alarm message will appear when the select key is pressed.         ---*/

   if (FinalResults.Warnings & WARNINGMASK)                  /* Lowest priority */
      CountWarnings();

   if (FinalResults.NoCycleAlarms & NOCYCLEMASK)
      CountNoCycleAlarms();

   if (FinalResults.CycleModifiedAlarms & CYCLEMODIFIEDMASK)
      CountCycleModifiedAlarms();
      
   if (RunningPreset.SuspectLimitsFlag & BIT0) {
      if (FinalResults.SuspectBitResult & SUSPECTBITRESULTMASK)
         CountSuspectResults();
   }

   if (RunningPreset.RejectLimitsFlag & BIT0) {
      if(FinalResults.RejectBitResult & REJECTBITRESULTMASK)
         RejectAlarmCountFlag = TRUE;
   }

/*-- Count Alarms in reject group which are not really reject limits  --*/
/*--            (only if not already counted above)                   --*/

   if (FinalResults.RejectBitResult & REJECTALARMMASK) {
      RejectAlarmCountFlag = TRUE;
   }                                                    
   if (RejectAlarmCountFlag == TRUE) CountRejectResults();                             


   if (FinalResults.OverloadAlarms & OVERLOADMASK)
      CountOverloadAlarms();

   if (FinalResults.EquipmentFailureAlarms & EQUIPMENTFAILUREMASK)
      CountEquipmentFailureAlarms();

//   if (FinalResults.CalibrateAlarms & CALIBRATEMASK)  /* Highest  */TODO:coverity . if cond is always false
//      CountCalibrateAlarms();

   SetupAlarmCount = GetSetupAlarmCount();
   TotalAlarmCount = NoCycleAlarmCount + OverloadAlarmCount + 
                     EquipmentFailureAlarmCount + CycleModifiedAlarmCount + 
                     SuspectAlarmCount + RejectAlarmCount + 
                     CalibrateAlarmCount + WarningCount + SetupAlarmCount;
 
}

UINT8 CheckForAlarms(void)
{
   UINT8 AlarmDetected = FALSE;

   if((FinalResults.NoCycleAlarms & NOCYCLEMASK) ||
      (FinalResults.OverloadAlarms & OVERLOADMASK) ||
      (FinalResults.EquipmentFailureAlarms & EQUIPMENTFAILUREMASK) ||
      (FinalResults.CycleModifiedAlarms & CYCLEMODIFIEDMASK) ||
      (FinalResults.CalibrateAlarms & CALIBRATEMASK) ||
      (FinalResults.SuspectBitResult & SUSPECTBITRESULTMASK) ||
      (FinalResults.RejectBitResult & REJECTBITRESULTMASK))
         AlarmDetected = TRUE;

   return(AlarmDetected);
}


UINT8 CheckForWarnings(void)
{
   UINT8 WarningDetected = FALSE;

   if(FinalResults.Warnings & WARNINGMASK)
      WarningDetected = TRUE;
   return(WarningDetected);
}


void GetAlarmMask(void)
/****************************************************************************/
/*                                                                          */
/* This function will copy the alarm defines into FRAM where they can be     */
/* modified from the BUC menu.  This function should only be called when    */
/* the system is configured.  Any changes made from the BUC menu will be    */
/* lost when reconfiguring.                                                 */
/*                                                                          */
/****************************************************************************/
{
   AlarmPtrFRAM = (ALARM_MASKS *)FRAM1200_ALARM_START;

   AlarmPtrFRAM->SetupGroup1 = SETUPGROUP1MASK;
   AlarmPtrFRAM->SetupGroup2 = SETUPGROUP2MASK;
   AlarmPtrFRAM->SetupGroup3 = SETUPGROUP3MASK;
   AlarmPtrFRAM->SetupGroup4 = SETUPGROUP4MASK;
   AlarmPtrFRAM->SetupGroup5 = SETUPGROUP5MASK;
   AlarmPtrFRAM->SetupGroup6 = SETUPGROUP6MASK;
   AlarmPtrFRAM->SetupGroup7 = SETUPGROUP7MASK;
   AlarmPtrFRAM->SetupGroup8 = SETUPGROUP8MASK;
   AlarmPtrFRAM->SetupGroup9 = SETUPGROUP9MASK;
   AlarmPtrFRAM->SetupGroup10 = SETUPGROUP10MASK;
   AlarmPtrFRAM->Overload = OVERLOADMASK;
   AlarmPtrFRAM->NoCycle = NOCYCLEMASK;
   AlarmPtrFRAM->EquipmentFailure = EQUIPMENTFAILUREMASK;
   AlarmPtrFRAM->CycleModified = CYCLEMODIFIEDMASK;
   AlarmPtrFRAM->Reject = REJECTBITRESULTMASK;
   AlarmPtrFRAM->Suspect = SUSPECTBITRESULTMASK;
   AlarmPtrFRAM->Warning = WARNINGMASK;

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
}
