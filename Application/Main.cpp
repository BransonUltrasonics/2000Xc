/*
 $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Main.cpp_v   1.19   16 Apr 2015 07:14:58   rjamloki  $
 */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        	*/
/*   This program is the property of Branson Ultrasonics Corporation      	*/
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Main.cpp_v  $
 * 
 *    Rev 1.20   13 Mar 2020 07:14:58   rvite
 * Added task DITask.
 *
 *    Rev 1.19   16 Apr 2015 07:14:58   rjamloki
 * Moved RVTS Priority above Network and Port manager tasks.
 * 
 *    Rev 1.18   30 Mar 2015 06:09:50   rjamloki
 * Interrupt handler task priority is given after root.
 * 
 *    Rev 1.17   21 Jan 2015 09:40:50   amaurya
 * Code CleanUp.
 * 
 *    Rev 1.16   10 Nov 2014 04:37:12   AnPawar
 * ReadMACAddressFromEEPRom() function changed.
 * 
 *    Rev 1.15   22 Aug 2014 08:05:18   rjamloki
 * Added web service init in main
 * 
 *    Rev 1.14   28 Jul 2014 14:59:38   rjamloki
 * Added Uploadfirmware task
 * 
 *    Rev 1.13   21 May 2014 10:54:16   rjamloki
 * Fixed Header
 * 
 *    Rev 1.12   21 May 2014 02:48:18   rjamloki
 * Moved FRAM chip select to FRAM.cpp file
 * 
 *    Rev 1.11   07 May 2014 10:55:46   rjamloki
 * RTClock() task removed
 * 
 *    Rev 1.10   21 Apr 2014 14:02:32   rjamloki
 * New task PortManagement Task added and ethernet default initialization removed
 * 
 *    Rev 1.9   14 Apr 2014 08:18:46   rjamloki
 * Added Shutdown task , Diagnostic LED task and external watchdog trigger at start. Fixed define for SBC Ethernet interface.
 * 
 *    Rev 1.8   26 Mar 2014 11:59:26   rjamloki
 * ReadMACAddressFromEEPRom() function changed to get mac address from i2c chip,RTClock() task added,StartAppTasks() function changed
 * 
 *    Rev 1.7   07 Mar 2014 11:09:28   rjamloki
 * Modify User changes.
 * 
 *    Rev 1.6   06 Mar 2014 11:03:44   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:57:46   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 05:00:36   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:56:06   rjamloki
 * Header Fix.
 * 
 *    Rev 1.1   05 Jun 2013 08:40:10   amaurya
 * Initial revision 2.
 *
 *	  Revision 1.5  2013/05/24 23:12:08  Ellery
 * *** empty log message ***
 *
 * 	  Revision 1.2  2013/05/21 19:52:50  Ellery
 * First Revision for Dallas testing
 *
 *	  Revision 1.1  2013/05/14 15:02:57  Ellery
 * First Revision for Dallas testing
 * 
 *    Rev 1.0   03 Apr 2013 06:08:40   amaurya
 * Initial revision.
 * 
 *
 */

#include "CyGOS.h"
#include "InputTask.h"
#include "Board.h"
#include "portable.h"
#include "PortManagerTask.h"
#include "RVTSHandlerTask.h"
#include "root.h"
#include "WeldManagerTask.h"
#include "SystemManagerTask.h"
#include "FrontPanelStateCoordinatorTask.h"
#include "FrontPanelKeypadTask.h"
#include "DUPS_ManagerTask.h"
#include "RemoteSerialCommandHandlerTask.h"
#include "NetworkManagerTask.h"
#include "InterruptHandlerTask.h"
#include "wc_isr.h"
#include "command.h"
//#include "Ethernet.h"
#include "LED.h"
#include "CPU.h"
#include "UndefPrintf.h"
#include "rtclock.h"
#include "CPLD.h"
#include "ticks.h"
#include "A1025R.h"
#include "ShutDownTask.h"
#include "UploadFirmWareTask.h"
#include "WebService.h"
#include "psnvram.h"
#include "DITask.h"

extern void SetupFramChipSelect();
CPLD * cpld = new CPLD();
EUI_24AA025E48 * MacChipPtr; //mac chip storage shall be used as PsNvram in 2000X

#define IPDCPINTERFACE 172, 16, 78, 125
#define DEFAULTNETMASK 255, 255, 255, 0
#define DEFAULTGATEWAY 172, 16, 78, 1
#define MAC_ADDRESS_LEN 6
#define DEFAULT_MAC_ADDR (uint8*)"\x12\xC6\x05\xDC\x1C\x01"
#define MAX_APP_TASKS 20
#define MACSTART_ADDRESS 0xFA
extern SINT8 SWVersionLabel[SW_VERSION_LENTGH + 1];

Task * AppTasks[MAX_APP_TASKS];


void SetLeds(int slow, int fast)
{
	LED::Set(1, slow);
	LED::Set(2, fast);
}

void ReadMACAddressFromEEPRom(UINT8 * macPtr)
/****************************************************************************/
/* Description:-                                                         */
/* This function reads the MAC Adress from EEPROM chip                   */
/****************************************************************************/
{
   int tempLen = MAC_ADDRESS_LEN;
   MacChipPtr->Read(MACSTART_ADDRESS, macPtr, tempLen, 3);
   if (tempLen < 0)
      memcpy(macPtr, DEFAULT_MAC_ADDR, MAC_ADDRESS_LEN);
}

char * compileDate = __DATE__;
char * compileTime = __TIME__;

/*   int main()
 *
 *   Purpose:
 *		This is the entry point of WC Application code. This function is called by startup assempbly routines.
 *
 *   Entry condition:
 *		None.
 *
 *   Exit condition:
 *		Never returns.
 */
int main()
{

   InitExternalWatchDogPort();
   CyGOS::RegisterWatchdogCallback(TriggerExternalWatchDog);
   pprintf("\nStart main %s %s\n", compileDate, compileTime);
   int Priority = 0;
   BYTE MacAddr[6];
   //Setup flexbus interface for FRAM
   SetupFramChipSelect();
   RTClock::InitRTC();
   MacChipPtr =  new  EUI_24AA025E48(Board::GetI2C(0, 5, 5), 0xA6);
   ReadMACAddressFromEEPRom(MacAddr);
   memset(AppTasks, 0, sizeof(AppTasks[0]) * MAX_APP_TASKS);
   //In this sequence, all WC initialization work shall take place.
#ifndef WCSBC_ONSERIAL
   CyGOS::EnableDebug();
#endif
   CyGOS::Init();						   // for basic tasks initialization

   CyGOS::CreateTask(new RootTask(), Priority);
   AppTasks[Priority++] = new Interrupt_HandlerTask();
   CyGOS::CreateTcpipTasks(Priority);
   CyGOS::AddTcpInterface(ETHERNET_INTERFACE_WCTOSBC, Priority, MacAddr); // to Initialize Ethernet related task and
   //CyGOS::SetupAddress(ETHERNET_INTERFACE_WCTOSBC, MakeIP(IPDCPINTERFACE), MakeIP(DEFAULTNETMASK)); // to assign IP to Ethernet interface 0.
   //CyGOS::SetGW(ETHERNET_INTERFACE_WCTOSBC, MakeIP(DEFAULTGATEWAY));
   CyGOS::CreateTftpClientTask(ETHERNET_INTERFACE_WCTOSBC, Priority);
   CyGOS::CreateLedTasks(1, 1, SetLeds);

   AppTasks[Priority++] = new WeldManagerTask();
   AppTasks[Priority++] = new SystemManagerTask();
   AppTasks[Priority++] = new RVTSHandlerTask();
   AppTasks[Priority++] = new PortManagerTask();
   AppTasks[Priority++] = new NetworkManagerTask(ETHERNET_INTERFACE_WCTOSBC);
   AppTasks[Priority++] = new FrontPanelStateCoordinatorTask();
   AppTasks[Priority++] = new FrontPanelKeypadTask();
   AppTasks[Priority++] = new DUPS_ManagerTask();
   AppTasks[Priority++] = new RemoteSerialCommandHandlerTask();
   AppTasks[Priority++] = new InputTask();
   CyGOS::CreateHttpServerTask(ETHERNET_INTERFACE_WCTOSBC, HTTP_PORT, Priority); // to Initialize HTTP Server task on Ethernet interface 1 required for website communication.
   AppTasks[Priority++] = new UploadFirmware();
   AppTasks[Priority++] = new DITask(ETHERNET_INTERFACE_WCTOSBC);
   AppTasks[Priority++] = new ShutDownTask();//TODO:Test it. There is something already like this in code(Powerdown state).
   WebService::InitWebService(ETHERNET_INTERFACE_WCTOSBC, HTTP_PORT);
   printf("\n\nDI BUC Communication Protocol\n");
   printf(" WC-2000X SW Version %s\n", SWVersionLabel);
   TriggerExternalWatchDog();
   CyGOS::Start(MILLS_PER_TICK * 1000);
}

void StartAppTasks()
{
   printf("\n");
   for (int i = 0; i < MAX_APP_TASKS; i++) {
      int priority = i;
      if (AppTasks[i]) {
         CyGOS::CreateTask(AppTasks[i], priority);
         printf("Started %s prio %d\n", AppTasks[i]->GetName(), i);
      }
   }
   CyGOS::InstallTimer(1000, MsInt, 1);
}
