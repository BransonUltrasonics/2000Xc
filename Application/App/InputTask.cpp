/*
 $Header:   D:/databases/VMdb/archives/DCX/Weld Controller/Wupload
 C/Application/InputTask.cpp_v   1.4   10 Sep 2012 03:11:38   rjamloki  $
 */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/InputTask.cpp_v  $
 * 
 *    Rev 1.39   Oct 09 2017 16:53:52   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.38   16 Apr 2015 07:18:00   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.37   08 Apr 2015 13:43:18   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.36   27 Mar 2015 11:07:36   amaurya
 * HoldForceMax changed to HoldForceEnd as per code review comment.
 * 
 *    Rev 1.35   16 Feb 2015 01:17:20   amaurya
 * diagnostics added to trace recalibrate actuator alarm
 * 
 *    Rev 1.34   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.33   21 Jan 2015 09:38:34   amaurya
 * InputTask::Run() changed.
 * 
 *    Rev 1.32   08 Jan 2015 03:01:00   AnPawar
 * removed unused variables
 * 
 *    Rev 1.31   02 Jan 2015 04:03:16   rjamloki
 * changes related to e_stop new hardware
 * 
 *    Rev 1.30   11 Dec 2014 08:35:34   AnPawar
 * disable debug printf.
 * 
 *    Rev 1.29   28 Nov 2014 07:36:08   rjamloki
 * InputTask::Run() function changed.Removed unused variables.
 * 
 *    Rev 1.28   17 Nov 2014 09:54:36   RJamloki
 * Printing sbc ready flag in 'W' option
 * 
 *    Rev 1.27   10 Nov 2014 11:13:38   RJamloki
 * Added load cell display test for debug menu.
 * 
 *    Rev 1.26   10 Nov 2014 04:50:34   AnPawar
 * Added function header.Added some new input options.
 * 
 *    Rev 1.25   20 Oct 2014 06:20:00   AnPawar
 * InputTask::Run() function changed
 * 
 *    Rev 1.24   06 Oct 2014 06:34:50   AnPawar
 * InputTask::Run() function changed
 * 
 *    Rev 1.23   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.22   11 Sep 2014 10:53:00   rjamloki
 * Coverity fix,initialize argument in WeldHisTestTask constructor
 * 
 *    Rev 1.21   05 Sep 2014 04:47:56   rjamloki
 * Added diagnostic to calculate preset read write timing. Fram Init will not default the Actuator Novram now.
 * 
 *    Rev 1.20   18 Aug 2014 01:40:16   rjamloki
 * Added support for factory test commands
 * 
 *    Rev 1.19   07 Aug 2014 16:16:16   tayars
 * variable name changes
 * 
 *    Rev 1.18   28 Jul 2014 12:45:20   rjamloki
 * Added WatchDog trigger in flash erase and program callbacks to avoid watchdog reset during firmware upload
 * 
 *    Rev 1.17   09 Jul 2014 11:02:14   rjamloki
 * Added nandflash test diagnostic.
 * 
 *    Rev 1.16   20 Jun 2014 14:50:20   rjamloki
 * Added options for setting flow and pressure.
 * 
 *    Rev 1.15   16 Jun 2014 08:31:58   rjamloki
 * Added diagnostic to read act adc.
 * 
 *    Rev 1.14   11 Jun 2014 11:32:20   rjamloki
 * Added test cases to simulate weld data and testing AES WC Dspi communication
 * 
 *    Rev 1.13   27 May 2014 10:12:48   amaurya
 * Added ADC diagnostic function
 * 
 *    Rev 1.12   21 May 2014 10:47:58   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.11   21 May 2014 03:07:24   rjamloki
 * coverity fixes and added diagnostics for inputs from cpld
 * 
 *    Rev 1.10   07 May 2014 10:21:14   rjamloki
 * Case added to explicitly initialize Network Interface.
 * 
 *    Rev 1.9   23 Apr 2014 13:49:12   akaushal
 * Enable Disable debug at start and end of input task
 * 
 *    Rev 1.8   21 Apr 2014 13:30:14   rjamloki
 * Test code added for event and alarm
 * 
 *    Rev 1.7   14 Apr 2014 09:58:30   rjamloki
 * Cleaned up, moved board specific ADC and DAC classes to qsm.h
 * 
 *    Rev 1.6   26 Mar 2014 12:19:00   rjamloki
 * added function EnterTime().Added new cases in InputTask::Run() function.TLV5604PB::WriteOutput(),TLV5604PB::WriteOutputs(),MCP3208PB::ReadInput() ,class MCP3208PB,MCP3208PB::ReadInputs(),MCP3208PB::Volts(),class TLV5604PB added.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:26   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:38   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:28   rjamloki
 * Header Fix.
 * 
 *    Rev 1.1   05 Jun 2013 08:37:58   amaurya
 * Initial revision 2.
 *
 *    Revision 1.8  2013/05/24 23:12:08  Ellery
 * *** empty log message ***
 *
 *    Revision 1.6  2013/05/22 23:01:30  Ellery
 * Finished basic application code support for all peripherals.  Need to test in India and Dallas next to see what mistakes I have made so far.  Drivers which may need modification are: TLV5604, MCP3208, CAT93C66, AD7890, NAND Flash and Linear Encoder.
 * Modified file structure so CPLD.cpp and CPLD.h are now part of /Devices in CyGOS and no longer in application.  This way, the devices could modify the SPI chip select latch inside the CPLD without needing to make that function call in the application.  This also prevents interrupts from allowing a context switch to overwrite the SPI CS.
 *
 *    Revision 1.5  2013/05/21 21:30:46  Ellery
 * Basic driver support for TLV5604, MCP3208, AD7890, CAT93C66, Linear Encoder and Digital I/O.
 * Application code has support for Digital I/O and Linear Encoder.  Need to update all NVRam, PS Analog and Actuator Analog related software before testing.
 *
 *	  Revision 1.4  2013/05/21 19:52:50  Ellery
 * First Revision for Dallas testing
 *
 * 	  Revision 1.3  2013/05/17 15:55:27  Ellery
 * First Revision for Dallas testing
 *
 * 	  Revision 1.2  2013/05/15 21:56:40  Ellery
 * First Revision for Dallas testing
 *
 *	  Revision 1.1  2013/05/14 15:02:57  Ellery
 * First Revision for Dallas testing
 *
 *    Rev 1.0   03 Apr 2013 06:15:54   amaurya
 * Initial revision.
 *
 */

#include "InputTask.h"
#include "CyGOS.h"
#include "Board.h"
#include "CPU.h"
#include "Flash.h"
#include "command.h"
#include "state.h"
#include "digout.h"
#include "ALARMS.h"
#include "ready.h"
#include "dups_api.h"
#include "DUPS_ManagerTask.h"
#include "DUPS.h"
#include "UndefPrintf.h"
#include "FIFO.h"
#include "rtclock.h"
#include "CPLD.h"
#include "TLV5604.h"
#include "SPI.h"
#include "AT93C66.h"
#include "AD7890.h"
#include "CRC.h"
#include "assert.h"
#include "inports.h"
#include "actnvram.h"
#include "battram.h"
#include "psnvram.h"
#include "FrontPanelKeypadTask.h"
#include "states.h"
#include "qsm.h"
#include "TaskManager.h"
#include "inputs.h"
#include "ready.h"
#include "WeldManagerTask.h"
#include "mansensr.h"
#include "NandFlash.h"
#include "rxcharrcv.h"
#include "Terminal.h"
#include "Events.h"
#include "statedrv.h"
#include "weld_obj.h"
#include "spidd.h"

#define IPDCPINTERFACE 172, 24, 121, 226
#define DEFAULTNETMASK 255, 255, 254, 0
#define DEFAULTGATEWAY 172, 24, 120, 1

extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern INPUT_PORT_P1_UNION_TYPE LastInputP1;
extern INPUT_PORT_P0_UNION_TYPE LastInputP0;
extern UINT16 ADPressure;
extern INBITS Inp;
extern BOOLEAN JustPoweredUpFlag;
extern SINT32 EncoderPos;
extern SINT32 DownspeedTuneCycles;
extern UserID useridData;

void ConfigureAef();
void InitializeFRAM();
void BackupCurrentSetupChange();
void SetDefaultUserData(void);

BOOLEAN TestTestFlag = FALSE;

/** @brief InputTask::InputTask
 *
 *  Constructor of class InputTask.
 *
 *  @param void
 *  @return void
 */
InputTask::InputTask() :
      Task("Input", 3072)
{
   pprintf("\nI exist\n");
}

/** @brief InputTask::PrintHelp
 *
 *  This function print the available options on input
 *
 *  @param void
 *  @return void
 */
void InputTask::PrintHelp()
{
   pprintf("\n\n");
   pprintf("? - This help\n");
   pprintf("M - Print memory allocation\n");
   pprintf("T - Show task status\n");
   pprintf("F - ReFlash Board\n");
   pprintf("r - Read flash chip\n");
   pprintf("1 - Run tests\n");
   pprintf("2 - Update Checksum\n");
   pprintf("\n\n");
}

/** @brief EraseCallback
 *
 *  This  is callback function to erase flash.
 *  Offset address and length is passed as argument.
 *  This function also triggers the external watchdog
 *
 *  @param int offset
 *  @param int length
 *  @return void
 */
void EraseCallback(int offset, int length)
{
   pprintf("Erase: %08X of %08X\n", offset, length);
   TriggerExternalWatchDog();
}

/** @brief ProgramCallback
 *
 *  This is callback function to program flash.
 *  Offset address and length is passed as argument.
 *  This function also triggers the external watchdog
 *
 *  @param int offset
 *  @param int length
 *  @return void
 */
void ProgramCallback(int offset, int length)
{
   if (((offset & 0xFFFF) == 0) || (offset == length))
      pprintf("Program: %08X of %08X\n", offset, length);
   TriggerExternalWatchDog();
}

/** @brief InputTask::ProgramBootFlash
 *
 *  This used to program the flash using tftp server.
 *  Address of the server is entered first.Then
 *  default filename Bootload_WC.bin is received.
 *
 *  @param int intf
 *  @return void
 */
void InputTask::ProgramBootFlash(int intf)
{
   char fileName[20];
   pprintf("\n enter tftp server ip address");
   memset(fileName, 0, sizeof(fileName));
   gets(fileName);
   ip_addr srvr;
   char * ipPtr = fileName;
   int a, b, c, d;
   a = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   b = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   c = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   d = atoi(ipPtr);
   srvr.addr = MakeIP(a, b, c, d);
   strcpy(fileName, "BootLoad_WC.bin");
   Flash * flash = Board::GetFlash();
   ASSERT(flash);
   CyGOS::DisableWatchDog();
   CyGOS::StopTimer(1);
   int length = (int) __FLASH_SIZE;
   UINT8 * data = new uint8[length];
   printf("Receiving file '%s':...", fileName);
   CyGOS::TftpReceive(intf, fileName, &length, data, srvr);
   pprintf("Length %d\n", length);
   DelayMs(100);
   if (length > 0) {
      CyGOS::Stop();
      pprintf("Programming Address %08X\n", 0);
      pprintf("Flash %08X\n", flash);
      flash->Unlock(0, length);
      flash->Erase(0, length, EraseCallback);
      flash->Program(0, data, length, ProgramCallback);
      flash->Lock(0, length);
      DelayMs(50);
      CPU::Restart();
      while (1)
         ;
   }
   delete data;
   delete flash;
}

/** @brief InputTask::ProgramFlash
 *
 *  This used to program the flash using tftp server.
 *  Address of the server is entered first.Then
 *  default filename App_SUNRISE.bin is received.
 *
 *  @param int intf
 *  @return void
 */
void InputTask::ProgramFlash(int intf)
{
   char fileName[30];
   pprintf("\n enter tftp server ip address");
   memset(fileName, 0, sizeof(fileName));
   gets(fileName);
   ip_addr srvr;
   char * ipPtr = fileName;
   int a, b, c, d;
   a = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   b = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   c = atoi(ipPtr);
   ipPtr = strchr(ipPtr, '.') + 1;
   d = atoi(ipPtr);
   srvr.addr = MakeIP(a, b, c, d);
   strcpy(fileName, "App_SUNRISE.bin");
   Flash * flash = Board::GetFlash();
   ASSERT(flash);
   int length = (int) __FLASH_SIZE;
   uint8 * data = new uint8[length];
   printf("Receiving file '%s':...", fileName);
   CyGOS::TftpReceive(intf, fileName, &length, data, srvr);
   pprintf("Length %d\n", length);
   if (length > 0) {
      CyGOS::Stop();
      pprintf("Programming Address %08X\n", __FLASH_ROM);
      pprintf("Flash %08X\n", flash);
      flash->Unlock(__FLASH_ROM, length);
      flash->Erase(__FLASH_ROM, length, EraseCallback);
      flash->Program(__FLASH_ROM, data, length, ProgramCallback);
      flash->Lock(__FLASH_ROM, length);
      DelayMs(50);
      pprintf("\n Waiting for Restart after flash program...\n ");
      CyGOS::Restart();
      while (1)
         ;
   }
   else
      pprintf("\n Length too short");
   delete data;
   delete flash;
}

/** @brief AutoTest
 *
 *	Function test the Actuator NVRAM
 *
 *  @param void
 *  @return void
 */
void AutoTest()
{
   pprintf("Testing ACT NVRAM...\n");
   int errors = 0;
   NVRWriteSetup();
   UINT16 nvram[0x100];
   for (UINT16 Address = 0; Address <= 0xFF; Address++) {
      nvram[Address] = ReadNVR(Address);
      if (Address == 0)
         pprintf("\n act ID %d", nvram[Address]);
   }
   pprintf("Done reading old data\n");
   for (UINT16 Address = 0; Address <= 0xFF; Address++)
      NVRWriteNovram((Address << 8) | Address, Address);
   for (UINT16 Address = 0; Address <= 0xFF; Address++) {
      UINT16 read = ReadNVR(Address);
      UINT16 expect = (Address << 8) | Address;
      if (read != expect) {
         errors++;
         pprintf("%02X %04X %04X\n", Address, read, expect);
      }
   }
   pprintf("Done writing address data\n");
   for (UINT16 Address = 0; Address <= 0xFF; Address++)
      NVRWriteNovram(~((Address << 8) | Address), Address);
   for (UINT16 Address = 0; Address <= 0xFF; Address++) {
      UINT16 read = ReadNVR(Address);
      UINT16 expect = ~((Address << 8) | Address);
      if (read != expect) {
         errors++;
         pprintf("%02X %04X %04X\n", Address, read, expect);
      }
   }
   pprintf("Done writing inverted address data\n");
   for (UINT16 Address = 0; Address <= 0xFF; Address++)
      NVRWriteNovram(nvram[Address], Address);
   for (UINT16 Address = 0; Address <= 0xFF; Address++) {
      UINT16 read = ReadNVR(Address);
      UINT16 expect = nvram[Address];
      if (read != expect) {
         errors++;
         pprintf("%02X %04X %04X\n", Address, read, expect);
      }
   }
   printf("Done writing old data back\n");
   printf("NVRAM test: ");
   if (errors)
      printf("%d errors\n", errors);
   else
      printf("No errors\n");

   UINT16 Data1 = 0xAABB, Addr1 = 10;
   pprintf("\n writing %04X at Address %d", Data1, Addr1);
   NVRWriteNovram(Data1, Addr1);

   pprintf("\n readin at Address %d", Addr1);
   pprintf("\n read %04X", ReadNVR(Addr1));

   Data1 = 0x6699, Addr1 = 10;
   pprintf("\n writing %04X at Address %d", Data1, Addr1);
   NVRWriteNovram(Data1, Addr1);

   pprintf("\n readin at Address %d", Addr1);
   pprintf("\n read %04X", ReadNVR(Addr1));
   NVRCommandEWDS();

}


/** @brief auto_add
 *
 *	Function to add Users with default values for testing purpose. Function is called on pressing option
 * ';' on Hyper terminal and adds 100 new users at once.
 *
 *  @param void
 *  @return void
 */
void auto_add(void)
{
	int i=0;
	int users=0;
	UINT32 Data1;	//was inside for loop
	for(i=FRAMUserIdObj.UserIDGlobalCount;i<995;i++)
    {
    	SetDefaultUserData();
        memcpy(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount], &useridData,
		sizeof(UserID));
		RTClock::GetCurrentTime(&FRAMUserIdObj.UserDetail[FRAMUserIdObj.UserIDGlobalCount].CreateModifyTime);
		FRAMUserIdObj.UserIDGlobalCount = FRAMUserIdObj.UserIDGlobalCount + 1;
		if(useridData.Status == Enabled)
			FRAMUserIdObj.ActiveUserIDCount++;
		Data1 = (useridData.UserId[0]<<24 | useridData.UserId[1]<<16 \
			| useridData.UserId[3]<<8 | useridData.UserId[4]);
					printf(".");
		users++;
		if(users>=99)
		  break;
    }
}

/** @brief NandFlash::NandFlashTest
 *
 *	Function to test Nand flash
 *
 *  @param void
 *  @return void
 */
void NandFlash::NandFlashTest() {

	pprintf("\n going for allocation");
	pprintf("\n going for allocation");
	pprintf("\n going for allocation");
	pprintf("\n going for allocation");
	UINT8 * Page = new UINT8[4096];
	UINT8 * Block = new UINT8[4096 * 128];

	pprintf("\n done allocation");
	pprintf("\n done allocation");
	pprintf("\n done allocation");
	pprintf("\n done allocation");

	int Cnt1, Cnt2, Cnt3;
	UINT32 LogicalNandAddress = 0;
	NandAddress PhysicalNandAddress;
	UINT8 RetCode;
	bool status = true;

	pprintf("\n testing Block erase");
	LogicalNandAddress = 0;
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	NandPtr->ExtractAddress(LogicalNandAddress, &PhysicalNandAddress);
	RetCode = NandPtr->BlockErase(PhysicalNandAddress);
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	pprintf("\n Block Erase time = %d us return code %02X", Cnt2 - Cnt1,
			RetCode);

	memset(Page, 0xAA, 4096);
	memset(Block, 0x55, 4096 * 128);

	pprintf("\n testing page program");
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	NandPtr->ExtractAddress(LogicalNandAddress, &PhysicalNandAddress);
	RetCode = NandPtr->PageProgram(PhysicalNandAddress, Page, 4096);
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	pprintf("\n page program time = %d us return code %02X", Cnt2 - Cnt1,
			RetCode);

	memset(Page, 0x00, 4096);
	pprintf("\n testing page read");
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	RetCode = NandPtr->ReadPage(PhysicalNandAddress, Page, 4096);
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	pprintf("\n page read time = %d us return code %02X", Cnt2 - Cnt1, RetCode);

	for (int i = 0; i < 4096; i++) {
		if (*(Page + i) != 0xAA) {
			pprintf("\n page read verification failed %02X %d", *(Page + i), i);
			status = false;
			break;
		}
	}

	if(status)
		pprintf("\n page read OK");

	pprintf("\n testing Block erase");
	LogicalNandAddress = 0;
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	NandPtr->ExtractAddress(LogicalNandAddress, &PhysicalNandAddress);
	RetCode = NandPtr->BlockErase(PhysicalNandAddress);
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	pprintf("\n Block Erase time = %d us return code %02X", Cnt2 - Cnt1,
			RetCode);

	LogicalNandAddress = 0;
	pprintf("\n testing Block write");
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	for (Cnt3 = 0; Cnt3 < 128; Cnt3++) {
		NandPtr->ExtractAddress(LogicalNandAddress, &PhysicalNandAddress);
		RetCode = NandPtr->PageProgram(PhysicalNandAddress, Block + (Cnt3 * 4096),
				4096);
		LogicalNandAddress += 4096;
		while (!cpld->GetDin(Nand_Busy))//wait for flash ready. Failing without it in block read test
		         ;
	}
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	pprintf("\n Block Program time = %d us return code %02X", Cnt2 - Cnt1,
			RetCode);

	memset(Block, 0x00, 4096 * 128);

	pprintf("\n testing Block read");
	LogicalNandAddress = 0;
	Cnt1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
	status = true;
	for (Cnt3 = 0; Cnt3 < 128; Cnt3++) {
		NandPtr->ExtractAddress(LogicalNandAddress, &PhysicalNandAddress);
		RetCode = NandPtr->ReadPage(PhysicalNandAddress, Block + (Cnt3 * 4096),
				4096);
		LogicalNandAddress += 4096;
		while (!cpld->GetDin(Nand_Busy))//wait for flash ready. Failing without it in block read test
			;
	}
	Cnt2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);

	pprintf("\n Block Read time = %d us return code %02X", Cnt2 - Cnt1, RetCode);

	for (int i = 0; (i < (4096 * 128)); i++) {
		if (*(Block + i) != 0x55) {
			pprintf("\n Block read verification failed %02X  %d", *(Block + i),
					i);
			status = false;
			break;
		}
	}
	if(status)
			pprintf("\n block read OK");
	delete Page;
	delete Block;
}


/** @brief SetDefaultConfigAll
 *
 *	Function to set default value on Fram initialization
 *
 *  @param void
 *  @return void
 */
void SetDefaultConfigAll()
{
   pprintf("Input task 'R' ");
   InitializeFRAM();
   pprintf(" InitializeFRAM() ");
   DisableCode300();
   pprintf(" DisableCode300() ");
   //ConfigureAed();
   pprintf(" ConfigureAed() ");
   SetContLeveld();
   pprintf(" SetContLeveld() ");
   VelocityOn();
   pprintf(" VelocityOn() ");
   //ConfigSBeam();
   pprintf("AlramLogClear()EventhistoryClear()");
   PowerUpAlarmLogDataCheck();
   PowerUpEventHistoryDataCheck();

   PSNvRamData.PSFrequency = FREQ20KHZ;
   PSNvRamData.PSWatts = 2500;
   PSNvRamData.Actuator = NVR_AED;
   PSNvRamData.ControlLevel = LEVEL_d;
   strcpy(PSNvRamData.PSSerialNum, "DEF1234");

   pprintf("\n\n **** Reset Complete ****\n\n");
}


/** @brief AD7689A1025::Volts
 *
 *	Function converts the raw ADC value to double based on the channel ch.
 *
 *  @param in ch
 *  @param int raw
 *  @return double
 */
double AD7689A1025::Volts(int ch, int raw)
{
   if (ch == 0 || ch == 3 || ch == 4 || ch == 5)
   {
      raw ^= 0x800;
      return ((raw / 4096.0) * 5.0 - 2.5) * 4;
   }
   else {
      raw <<= 1;
      return (raw / 4096.0) * 10;
   }
}

//#ifdef SEND_FDATA_TEST

BOOLEAN WeldResTest = FALSE;
BOOLEAN SimPress = FALSE;
SINT32 MyPressure = 0;
extern UINT8 FramDummy2[8192];

/** @brief SendFdataTest
 *
 *  This function fills dummy data in welding structure
 *
 *  @param void
 *  @return void
 */
void SendFdataTest()
{
	WeldResTest = true;
	WeldingResults.ActualFreqEnd = 199450;
	WeldingResults.ActualAmplitudeEnd = 23;
	WeldingResults.ActualAmplitudeStart = 10;
	WeldingResults.ActualFreqStart = 199250;
	WeldingResults.ActualTotalAbs = 234;
	WeldingResults.ActualTotalCollapse = 345;
	WeldingResults.ActualTriggerDistance = 237;
	WeldingResults.ActualDownspeed = 123;
	WeldingResults.ActualWeldAbs = 290;
	WeldingResults.ActualWeldTime = 2345;
	WeldingResults.CalibrateAlarms = 0;
	WeldingResults.FrequencyChange = 5;
	WeldingResults.FrequencyMax = 20500;
	WeldingResults.FrequencyMin = 19250;
	WeldingResults.HoldForceEnd = 230;
	WeldingResults.PeakPower = 30;
	WeldingResults.PresetNum = 1;
	WeldingResults.SetPressureA = 780;
	WeldingResults.SetPressureB = 790;
	WeldingResults.TotalCycleTime = 5000;
	WeldingResults.TotalEnergy = 450;
	WeldingResults.TrigForce = 100;
	WeldingResults.WeldForceEnd = 600;
	WeldingResults.WeldPressure = 780;
	WeldingResults.Weldmode = TIMEMODE;

	if(SBCReadyFlag == TRUE){
		//WeldingResults.ActualWeldTime = 1;
		SendFData();
	}
	WeldResTest = false;
}

//#endif
class WeldHisTestTask: public Task
{
public:
	/** @brief WeldHisTestTask::WeldHisTestTask
	 *
	 *  Constructor of class WeldHisTestTask
	 *
	 *  @param void
	 *  @return void
	 */
	WeldHisTestTask():Task("testTask", 1024), Q(10, "Test")
	{
		thisPtr = this;
		ch = 0;
	}

	/** @brief WeldHisTestTask::Tick
	 *
	 *  Tick function of WeldHisTestTask
	 *
	 *  @param void
	 *  @return void
	 */
	void Tick()
	{
		static int Timer = 0;
		Timer += usecPerTick;
		if(Timer >= 500000)
		{
			Timer = 0;
			if(FramDummy2[567] == 0x55)
				Q.Write(0, 'a', 0);
		}
	}
	Fifo<char> Q;
	char ch;
	static WeldHisTestTask * thisPtr;
protected:
	/** @brief WeldHisTestTask::Run
	 *
	 *  Run function of WeldHisTestTask
	 *
	 *  @param void
	 *  @return void
	 */
	void Run()
	{
		while(true)
		{
			Q.Read(this, ch , -1);
			SendFdataTest();
		}
	}
};

WeldHisTestTask * WeldHisTestTask::thisPtr;
SETUPS_Ver1200 PresetTest;

/** @brief InputTask::Run
 *
 *  Run function of InputTask class
 *
 *  @param void
 *  @return void
 */
void InputTask::Run(void)
{
   DelayMs(500);
   PrintHelp();
   uint8 address = 0;
   bool set = true;
   int Ch;
   int Indx, I;
   int Index = 0;
   char InArr[10];
   char NVRSN[13];
   SR sr;
   char * TestBuf;
   FPKP_MSG_QUEUE_TYPE message;
   static bool outPinVal =0;
   int T1, T2, T3;
   SETUPS_Ver1200 * Test;
   double (*RawtoVoltConvFun)(int , int);
   int AdcCh7689[8];
   UINT16 FlowAndPressureVal;
   BOOLEAN FT100 = FALSE;
   const char* const NoFt = "FT100";
   struct
   {
	   PSNOVRAMDATA NvMData;//25 bytes
	   SINT8 CheckSumStr[5];//5 bytes check sum
	   UINT16 EstopTwoPoleHW;
	   //One time initializations can be done based on these values in future
	   SINT8 SpareArr[96];//98 bytes.
   } __attribute__((__packed__)) NvRamDataTest;//total 128 bytes available for read write in Mac chip eeprom area
   int NvrTestReadLen = 128;
//#ifdef SEND_FDATA_TEST
//  if(FramDummy2[567] == 0x55)
//  {
//	   DelayMs(20000);
//	   message.FpKeyPressedMsg.key = ResetKey;
//	   message.generic.common.opcode = OP_FRONT_PANEL_KEYPRESS;
//	   FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(this, message, 0);
// 	   int Prio = 29;
// 	   CyGOS::CreateTask(new WeldHisTestTask(), Prio);
//  }
//#endif

    for (;;) {
      Ch = getchar(); //Command option
      if(FT100 == FALSE) {
    	  InArr[Index] = Ch;
    	  if(InArr[Index] == NoFt[Index]) {
    		  if((Index + 1) == strlen(NoFt))
    			  FT100 = TRUE;//After FT100 the next char is for regular input task options
    		  Index++;//This is what we got so far
    		  Terminal::OutPoll(Ch);
    	  }
    	  else {
    		//Send received chars for Regular Ft Commands and labview handling
    		for(I = 0; I <= Index; I++)
    			CommAsciiCharRcvd(InArr[I] , (I > (Index - 1)));
    		Index = 0;
    	  }
    	  continue;
      }
      FT100 = FALSE;
      Index = 0;//Note:Don't change its value after this
      CyGOS::EnableDebug();
      switch (Ch) {
      case 'y':
    	  pprintf("\n enter ps num %d %d", sizeof(SETUPS_Ver1200), (int)(&CurrentPreset.PresetID)
    			  - (int)&CurrentPreset.AbAmp);
    	  Ch =   atoi(gets(InArr));
    	  pprintf("\n recalling ps %d ", Ch);
    	  if(Ch <= 1000)//Coverity 11653
    	  {
			  T1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
			  Test = Readpreset(Ch, &PresetTest);
			  T2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
			  SavePreset(Ch , &PresetTest);
			  T3 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
			  pprintf("\n read time %d us write time %d us", T2 - T1, T3 - T2);
			  pprintf("\n test->amp %d psname=%s", Test->Amp1, PresetTest.PresetID);
			  pprintf("\n enter  num 85 to simulate weld data");
    	  }
    	  Ch = atoi(gets(InArr));
    	  printf("\n gg %02X ", Ch);
    	  FramDummy2[567] = Ch;
         break;
      case '?':
         PrintHelp();
         for (int ii = 0; ii < NumLatches; ii++) {
            if (set)
               cpld->Latches[ii]->SetPins(0xFF);
            else
               cpld->Latches[ii]->SetPins(0x00);
         }
         if (set)
            set = false;
         else
            set = true;
         break;
      case 'M':
         ShowMemory();
         break;
      case 'F':
         ProgramFlash(1);
         break;
      case 'T':
         CyGOS::PrintStatus(PrintTasksWithStack);
         break;
      case 'B':
         ProgramBootFlash(1);
         break;
      case 'R':
         //			CPU::Restart();
        // SetDefaultConfigAll();
//    	strcpy((char *)FramInitDone, " ");
//    	CPU::Restart();
    	  printf("\n cl %d act %d sn %s", CurrentSetup.ControlLevel, CurrentSetup.Actuator, CurrentSetup.PSSerialNumber);
         break;
      case '/':
//    	  printf("Enter 1 to enable 0 to disable = ");
//    	  EventL++;
//          //WriteAlarmLog(1,true);
//          RecordEvents(EventTypes (EventL%EVENT_AUTHORITYLEVELCHANGES),EventL,EventL);
    	  //printf("\nEnter to test sonic dis");
    	 // T1 = atoi(gets(InArr));
    	 // printf("\n pres %d", T1);
//    	  if(T1 > 0)
//    	  {
//    	   SimPress = TRUE;
    	//   MyPressure = T1;
//    	  }
//    	  else
//    		  SimPress = FALSE;
    	  ActAdc->ReadInputs(1, (int *)AdcCh7689);
    	  pprintf("\n unfiltered force %d", AdcCh7689[0]);
    	  pprintf("\n unfiltered pressure %d", AdcCh7689[1]);
    	  pprintf("\n SetFlowValue = %d SetPressureValue = %d ReadFlowValue = %d",
    			  SetFlowValue, SetPressureValue, FlowReadValue);
    	  SetPressureValue++;
//    	  pprintf("\n set pressure value");
//    	  T1 = atoi(gets(InArr));
//    	  CurrentPreset.WeldPressure = (T1 * 10);
//    	  pprintf("\n setting %d PSI", CurrentPreset.WeldPressure / 10);
         break;
      case 'C':
         ColdStartPlus();
         break;
      case 'W':
         pprintf("\nCurrent seq = %d actid=%d hwverify=%04X \n ", CurrentSequence, NVR.ActId, CurrentSetup.HWVerify);
         pprintf("Ready %d uselogd in %d auth check %d", GetReadyStatus(), UserLoggedIn,
        		 CurrentSetup.AuthorityCheck);
         pprintf("\n SBCReady %d", SBCReadyFlag);
         break;
      case 'A':
         ConfigureAef();
         pprintf("Done\n");
         break;
      case '0'://Fresh board test
         memset((UINT8 *) (0x0B000000), 0, 512 * 1024);
         memset(&NvRamDataTest , 0xFF, 128);
         MacChipPtr->Write(MACCHIP_DATASTART_ADDRESS , (unsigned char *)&NvRamDataTest, 128);
         CPU::Restart();
         break;
      case 'E':
         RecordAlarm(EQ15);
         RecordAlarm(EQ17);
         break;
      case 'f'://fresh board test 2
         memset((UINT8 *) (0x0B000000), 0xFF, 512 * 1024);
         memset(&NvRamDataTest , 0xFF, 128);
         MacChipPtr->Write(MACCHIP_DATASTART_ADDRESS , (unsigned char *)&NvRamDataTest, 128);
         CPU::Restart();
         break;
      case '1':
    	  printf("\nEnter reading in PSI");
    	  T1 = atoi(gets(InArr));
    	  if(CurrentSetup.ControlLevel == LEVEL_c)
    	     SetPressureValue = T1 * 10;
    	  else
    	  {
    		 SetPressureValue = T1 * 10;
    	     SetPressureValue = (SetPressureValue * 1023) / 1000;
    	     SetPressureValue = (SetPressureValue | 0xA000);
    	     ActLpc->WriteReadVal(SetPressureValue &0xFFFF);
    	  }
    	  break;
      case '2':
         pprintf("Change act SN");
         strcpy(NVRSN, "BUC0000123");
         strcpy(CurrentSetup.ActSerialNumber, NVRSN);
         SetSerNum(CurrentSetup.ActSerialNumber);
         BackupCurrentSetupChange();
         break;
      case '3':
//         BUCFactoryDefaults = 163144022;
//         VGAConfigureFromBUCMenu();
    	  printf("\nEnter steps ");
    	  T1 = atoi(gets(InArr));
    	  printf("\n Enter direction 1 ACW(Open flow), 0 CW(close flow)");
		  T3 = atoi(gets(InArr));
		  if((T3 < 0) || (T3 > 1))
			T3 = 1;
		  sr  = EnterCritical();
		  if(T3)
			  SetPressureValue = 0xFF * 10;
		  else
			  SetPressureValue = 0;
		  SetFlowValue = T1;
		  ExitCritical(sr);
         pprintf("Given steps %d in direction %s\n", T1, T3?"ACW":"CW");
         break;
      case '4':
         if (cpld->GetDin(Row0))
            pprintf("Row0 Pressed\n");
         if (cpld->GetDin(Row1))
            pprintf("Row1 Pressed\n");
         if (LastInputP1.port.e_stop_signal)
            pprintf("E_Stop is Active\n");
         if (LastInputP1.port.uls_signal)
            pprintf("ULS is Active\n");
         if (LastInputP0.port.overload_input_signal)
            pprintf("Overload is Active\n");
         if (LastInputP1.port.pb1_signal)
            pprintf("PB1 is Active\n");
         if (LastInputP1.port.pb2_signal)
            pprintf("PB2 is Active\n");
         if (cpld->GetDin(PB1_Sig) || cpld->GetDin(PB2_Sig))
            pprintf("A PB is pressed\n");

         if(NvRamData.EstopTwoPoleHW == TWO_POLE_ESTOP)
         {
        	 if (!LastInputP1.port.e_stop2_signal)
        		 pprintf("estop 2 is active\n");
         }
         else
         {
        	 if (LastInputP1.port.e_stop2_signal)
        		 pprintf("Trigger SW is  active\n");
         }

         pprintf("\n LastInputP0.port.run_signal %d %d", LastInputP0.port.run_signal, Inp.BothPB);
         pprintf("AD Pressure = %d\n", ADPressure);
         pprintf("\n OL Statuse %d", Inp.OL);

         pprintf("\n CurrentSetup.DigTuneFlag %d", CurrentSetup.DigTuneFlag);
         break;
      case '5':
         pprintf("Trigger = %s\n", Inp.Trigger ? "true" : "false");
         pprintf("EStop = %s\n", Inp.Estop ? "true" : "false");
         pprintf("WeldingResults.EquipmentFailureAlarms %X,JustPoweredUpFlag %d\n",
               WeldingResults.EquipmentFailureAlarms, JustPoweredUpFlag);
         pprintf("Software Encoder = %X\n", EncoderPos);
         pprintf("Hardware Encoder = %X\n", CPLD::thisPtr->GetEncoderValue());
         break;
      case '6':
         pprintf("\n ref 10 volt %d", PsAdc->ReadInput(6));
         extern UINT16         AmpCntrlExt;
         pprintf("\n wmode %d AmprFlag %04X Amp1 %d Cs.AmpCont %d AmpCntExt %04X ",
        		 CurrentPreset.WeldMode, CurrentPreset.Amp2Flag, CurrentPreset.Amp1,
        		 CurrentSetup.AmpControl, AmpCntrlExt);

         pprintf("\n SequenceEnable %d SequenceCount %d SequenceNos %d \n",
        		 CurrentSetup.SequenceEnable , CurrentSetup.SequenceCount , CurrentSetup.SequenceNos);
           for(Indx = 0; Indx < MAX_SEQUENCE_NOS; Indx++)
        	   pprintf(" %d ",  CurrentSetup.SequenceList[Indx]);

         break;
      case '7':
         for (int array = 0; array < 64; array++)
            pprintf(" Table %d = %d", array, CurrentSetup.SpringRateTable[array]);
         for (int array = 0; array < 11; array++)
            pprintf(" LC %d", NVR.LoadCell[array]);
         break;

      case '8':
    	  if(UserLoggedIn == TRUE)
    	  {
			 message.FpKeyPressedMsg.key = TestKey;
			 message.generic.common.opcode = OP_FRONT_PANEL_KEYPRESS;
			 FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(this, message, 0);
    	  }
         break;
      case '9':
        printf("\nEnter steps ");
        T1 = atoi(gets(InArr));
        printf("\n Number of times");
        T2 = atoi(gets(InArr));
        printf("\n Enter direction 1. ACW 0. CW");
        T3 = atoi(gets(InArr));
        if((T3 < 0) || (T3 > 1))
        	T3 = 1;

        pprintf("\n Current Steps Value ", FlowReadValue);
        if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
        {
        	for(Indx = 0; Indx < T2; Indx++)
        	{
        		if(T3) //ACW
        		{
        			if((SetFlowValue + T1) >= 120)
        				SetFlowValue = 120;
        			else
        				SetFlowValue += T1;
        		}
        		else
        		{
        			if((SetFlowValue - T1) <= 0)
						SetFlowValue = 0;
					else
						SetFlowValue -= T1;
        		}
        		pprintf("\n setting steps %d direction %s ", SetFlowValue, T3?"ACW":"CW");
        		while(FlowReadValue != SetFlowValue){
        			pprintf("\n FlowReadValue %d", FlowReadValue);
        			DelayMs(100);
        		}
        		pprintf("\n wait for a while");
        		DelayMs(100);
        	}
        }
        else
        {
            CurrentPreset.Downspeed = T1;
            FlowAndPressureVal = (((T1 & 0xFF) << 8) | (CurrentPreset.WeldPressure & 0xFF));
            FlowReadValue = ActLpc->WriteReadVal(FlowAndPressureVal);
        }
         break;

      case 'D':
    	  //Toggle value on Diagnostic IO pins.
    	  printf("outPinVal = %d \n",outPinVal);

    	  cpld->SetDout(TP68,outPinVal);
    	  cpld->SetDout(TP69,outPinVal);
    	  cpld->SetDout(J3_22,outPinVal);
    	  cpld->SetDout(J3_36,outPinVal);
    	  cpld->SetDout(J3_8,outPinVal);
    	  cpld->SetDout(Gen_Alarm,outPinVal);
    	  outPinVal == TRUE ? outPinVal = FALSE : outPinVal = TRUE;
    	  break;
      case 'd':
    	  //NandFlash::Init()->NandFlashTest();
    	  void SendFakeKeyPress(KEY_CODE_TYPE Key);
    	  SendFakeKeyPress(UPDATEDISPLAY);
    	  break;
      case 'S':
         gets(NVRSN);
         address = xtoi(NVRSN);
         pprintf("\n Val = %X at address %X", ActNvRam->Read(address), address);
         break;
      case 'q':
         pprintf("\n Set PS Nvram data");
         PSNvRamData.PSFrequency = FREQ20KHZ;
         PSNvRamData.PSWatts = 2500;
         PSNvRamData.Actuator = NVR_AED;
         PSNvRamData.ControlLevel = LEVEL_d;
         //DUPSOkFlag = TRUE;
         break;
      case 'w':
    	  TestBuf = new char[1 * 1024 * 1024];
    	  sr = EnterCritical();
    	  T1 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
    	  memcpy(TestBuf, (void*)0x00040000, 1 * 1024 * 1024);
    	  T2 = Board::GetProfilerTimerCounter(PROFILER_TIMER_INSTANCE);
    	  ExitCritical(sr);
    	  delete TestBuf;
    	  printf("\n Flash to ram Copy Time %d us", T2 - T1);
         break;
      case 'n':
		if(WeldHisTestTask::thisPtr)
    	  WeldHisTestTask::thisPtr->Q.Write(this, 'a', 0);
    	  break;
      case 'Z':
    	  AutoTest();
         break;
      case 'X':
         message.FpKeyPressedMsg.key = ResetKey;
         message.generic.common.opcode = OP_FRONT_PANEL_KEYPRESS;
         FrontPanelKeypadTask::thisPtr->FrontPanelKeypadTaskQ.Write(this, message, 0);
         break;
      case 'L':
         state = true;
         cpld->SetDout(Seg1A, state);
         cpld->SetDout(Seg1B, state);
         cpld->SetDout(Seg1C, state);
         cpld->SetDout(Seg1D, state);
         cpld->SetDout(Seg1H, state);
         cpld->SetDout(Seg2A, state);
         break;
      case 'N':
         state = false;
         cpld->SetDout(Seg1A, state);
         cpld->SetDout(Seg1B, state);
         cpld->SetDout(Seg1C, state);
         cpld->SetDout(Seg1D, state);
         cpld->SetDout(Seg1H, state);
         cpld->SetDout(Seg2A, state);
         break;
      case 'O':
         state = true;
         cpld->SetDout(Bank1, state);
         cpld->SetDout(Bank2, state);
         cpld->SetDout(Bank3, state);
         cpld->SetDout(Bank4, state);
         cpld->SetDout(Bank5, state);
         cpld->SetDout(Bank6, state);
         break;
      case 'P':
         state = false;
         cpld->SetDout(Bank1, state);
         cpld->SetDout(Bank2, state);
         cpld->SetDout(Bank3, state);
         cpld->SetDout(Bank4, state);
         cpld->SetDout(Bank5, state);
         cpld->SetDout(Bank6, state);
         break;
      case 'Q':
         if (TestTestFlag)
            TestTestFlag = FALSE;
         else
            TestTestFlag = TRUE;
         break;
      case '=':
         CPU::Restart();
         break;
      case '|':
         extern char * compileDate;
         extern char * compileTime;
         printf("\nCode compiled on %s %s\n\n", compileDate, compileTime);
         break;
      case '[':

         printf("LE %ld\n Major Ver %d Minor Ver %d", cpld->GetEncoderValue(),
        		 cpld->ReadMajorVer(), cpld->ReadMinorVer());
         break;
      case ']':
         printf("Analog inputs (raw):\n");
         RawtoVoltConvFun = AD7689A1025::Volts;
         printf("AmpSample     %04X %+7.3f\n", PsAdc->ReadInput(1), RawtoVoltConvFun(1, PsAdc->ReadInput(1)));
		 printf("PowerSample   %04X %+7.3f\n", PsAdc->ReadInput(2), RawtoVoltConvFun(2, PsAdc->ReadInput(2)));
		 printf("FilterMem     %04X %+7.3f\n", PsAdc->ReadInput(3), RawtoVoltConvFun(3, PsAdc->ReadInput(3)));
		 printf("FilterFreq    %04X %+7.3f\n", PsAdc->ReadInput(0), RawtoVoltConvFun(0, PsAdc->ReadInput(0)));
		 printf("ExtAmp        %04X %+7.3f\n", PsAdc->ReadInput(5), RawtoVoltConvFun(5, PsAdc->ReadInput(5)));
		 printf("ExtFreqOffset %04X %+7.3f\n", PsAdc->ReadInput(4), RawtoVoltConvFun(4, PsAdc->ReadInput(4)));
		 printf("Ref10 volt    %04X %+7.3f\n", PsAdc->ReadInput(6), RawtoVoltConvFun(6, PsAdc->ReadInput(6)));
		 //printf("gnd    	   %04X %+7.3f\n", PsAdc->ReadInput(7), RawtoVoltConvFun(7, PsAdc->ReadInput(7)));
         break;
      case 'I':
		 CyGOS::SetupAddress(ETHERNET_INTERFACE_WCTOSBC, MakeIP(IPDCPINTERFACE), MakeIP(DEFAULTNETMASK)); // to assign IP to Ethernet interface 0.
		 CyGOS::SetGW(ETHERNET_INTERFACE_WCTOSBC, MakeIP(DEFAULTGATEWAY));
	  break;
      case 't':
         void EnterTime();
         EnterTime();
    	 pprintf("\n VGAPresetNum %d ", VGAPresetNum);
         break;
      case 'u':
    	  DownspeedTuneCycles++;
    	  if(DownspeedTuneCycles>6)
    		  DownspeedTuneCycles = 0;
    	  CurrentPresetParameterChanged = TRUE;
    	  break;
      case ';'://print  current sequence , index in sequence and current state
    	  pprintf("\n current seq %d CurIndx %d CurrState %d", CurrentSequence, *CurrentIndexPointer, WeldSequence[*CurrentIndexPointer]->state);
    	  break;
      case '*':
    	  SetDefCalSysPressure((SINT16)LOW_PRESSURE);
		  SetDefCalStrokeLength(DEF_CAL_LENGTH);
		  SetDefPressure();
		  SetDefLoadCell();
		  SetDefForce();
    	  break;
      case 'x'://control level store test in mac chip
    	  printf("\nEnter Control Level\n");
    	  CurrentSetup.ControlLevel = atoi(gets(NVRSN));
    	  StorePSControlLevel();
    	  break;
      case 'z'://serial number store test in mac chip
    	  printf("\nEnter Serial Num max 12. gets api dot take care of array size\n");
    	  gets(NVRSN);
    	  strncpy(CurrentSetup.PSSerialNumber, NVRSN, sizeof(CurrentSetup.PSSerialNumber) - 1);
    	  StorePSSerialNumber();
    	  break;
      case 'v'://ps frequency store test in mac chip
    	  printf("\nEnter ps frequency\n");
    	  CurrentSetup.PSFreq =  atoi(gets(NVRSN));
    	  StorePSFrequency();
      	  break;
      case 'l'://ps wattage store test in  mac chio
    	  printf("\nEnter ps wattage\n");
    	  CurrentSetup.PSWatt =  atoi(gets(NVRSN));
    	  StorePSWattage();
           break;
      case 'j'://life time counter store test in mac chip
    	  printf("\nEnter ps life time counter\n");
    	  CurrentSetup.PSLifetime =  atoi(gets(NVRSN));
    	  StorePSLifeTimeCount();
           break;
      case '#':
    	  printf("\n size of Psnvr %ld", sizeof(NvRamDataTest));
    	  NvrTestReadLen = 128;
    	  MacChipPtr->Read(MACCHIP_DATASTART_ADDRESS , (unsigned char *)&NvRamDataTest, NvrTestReadLen, 3);
    	  printf("\n ");
    	  printf("\n control level %d", NvRamDataTest.NvMData.ControlLevel);
    	  printf("\n ps freq  %d", NvRamDataTest.NvMData.PSFrequency);
    	  printf("\n ps watt %d", NvRamDataTest.NvMData.PSWatts);
    	  printf("\n SN %s__", NvRamDataTest.NvMData.PSSerialNum);
    	  printf("\n life time counter %ld", NvRamDataTest.NvMData.PSLifeTime);
    	  for(T1 = 0; T1 < 5; T1++)
    		  printf(" %c ", NvRamDataTest.CheckSumStr[T1]);
    	  printf("\n estop hw version %04X", NvRamDataTest.EstopTwoPoleHW);
    	  printf("\nAddr %08X %08X %08X %ld", (unsigned int)&NvRamData.NvMData, (unsigned int)&NvRamData.NvMData.PSSerialNum,
    			  (unsigned int)&NvRamData.EstopTwoPoleHW,	  sizeof(NvRamData));
    	  break;
      case '(': //Enbel admin user
    	  FRAMUserIdObj.UserDetail[0].Status = Enabled;
    	  break;
      case ')':
    	  printf("\n def load cell display test");
    	  T1 = 0;
    	  NVR.DefLoadCell[T1++] = 1046;
    	  NVR.DefLoadCell[T1++] = 2767;
    	  NVR.DefLoadCell[T1++] = 4488;
    	  NVR.DefLoadCell[T1++] = 6209;
    	  NVR.DefLoadCell[T1++] = 7930;
    	  NVR.DefLoadCell[T1++] = 9651;
    	  NVR.DefLoadCell[T1++] = 11372;
    	  NVR.DefLoadCell[T1++] = 13093;
    	  break;
      case '\'':
    	  StoreEstopHwVersion(ONE_POLE_ESTOP);
    	  break;
      case '"':
    	  StoreEstopHwVersion(TWO_POLE_ESTOP);
    	  break;
      break;
      default:
         pprintf("\nNotSupported %c", Ch);
         break;
      } //switch (ch)
      Index = 0;
      CyGOS::DisableDebug();
   } //for(;;)
}

/** @brief InputTask::Tick
 *
 *  This function is used to set dummy time on RTC
 *
 *  @param void
 *  @return void
 */
void EnterTime()
{
   char minutes[10];
   gets(minutes);
   RTCTime rt;
   rt.Hour = 5;
   rt.Minute = atoi(minutes);
   rt.Second = 0;
   rt.Century_Month = 4;
   rt.Day = 6;
   rt.Years = 14;
   rt.Weekdays = 6;
   RTClock::SetCurrentTime(&rt);
}

/** @brief InputTask::Tick
 *
 *  Tick function of InputTask class
 *
 *  @param void
 *  @return void
 */
void InputTask::Tick()
{

}
