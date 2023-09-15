// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/MultiBoot/SerialBootTftp.cpp_v   1.2   28 Nov 2014 08:08:32   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007, 2013
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3 MultiBoot loader.
//
// This module implements the TFTP part of serial port boot loader task.

#include "SerialBootTask.h"
#include "CyGOS.h"
#include "Board.h"
#include "CPU.h"
#include "WatchDog.h"
#include "stdio.h"
#include "DebugNew.h"

void SerialBootTask::TftpDownload(int intf, bool app)
{
	int priority = 30;
	CyGOS::CreateTcpipTasks(priority);
	CyGOS::AddTcpInterface(intf, priority,
			intf == 0 ? __ETHERNET_MAC0 : __ETHERNET_MAC1);
	CyGOS::SetupInterface(intf, true, true);
	CyGOS::CreateTftpClientTask(intf, priority);
	printf("\nInitializing Ethernet");
	while (!CyGOS::IsNetworkConfigured(intf))
	{
		printf(".");
		DelayMs(50);
	}

	ProgramFlash(intf, app);
}

bool isalpha(int ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

void SerialBootTask::TftpDownloadVersioned(int intf, bool app)
{
	printf("\nApplication version? A-Z");
	int version = getchar();
	while (!isalpha(version))
	{
		version = getchar();
	}
	if (version >= 'a')
		version -= 'a' - 'A';
	int priority = 30;
	CyGOS::CreateTcpipTasks(priority);
	CyGOS::AddTcpInterface(intf, priority,
			intf == 0 ? __ETHERNET_MAC0 : __ETHERNET_MAC1);
	CyGOS::SetupInterface(intf, true, true);
	CyGOS::CreateTftpClientTask(intf, priority);
	printf("\nInitializing Ethernet");
	while (!CyGOS::IsNetworkConfigured(intf))
	{
		printf(".");
		DelayMs(50);
	}
	ProgramFlash(intf, app, version);
}

void SerialBootTask::EnterTftpServerAddr(unsigned char * TftpAddr)
{
	char TftpAsc[20];
	printf("\nEnter TFTP address in a.b.c.d format: ");
	memset(TftpAsc, 0, sizeof(TftpAsc));
	gets(TftpAsc);
	ip_addr srvr_ip;
	unsigned int TftpIP;

	char * ipPtr = TftpAsc;
	int a, b, c, d;
	a = atoi(ipPtr);
	ipPtr = strchr(ipPtr, '.') + 1;
	b = atoi(ipPtr);
	ipPtr = strchr(ipPtr, '.') + 1;
	c = atoi(ipPtr);
	ipPtr = strchr(ipPtr, '.') + 1;
	d = atoi(ipPtr);
	srvr_ip.addr = MakeIP(a, b, c, d);
	TftpIP = srvr_ip.addr;
	printf("\n TFTP Server IP = %s", srvr_ip.ToString());

	printf("\n");
	printf("Store this TFTP address? [Y/N]");
	int ch = getchar();
	unsigned short * wptr = (unsigned short *) TftpAddr;
	wptr = FlashAddress(wptr);
	if (ch == 'Y')
	{
		ASSERT(flash);
		flash->UnlockChip();
		DelayMs(100);
		bool program = flash->Program(wptr, &TftpIP, sizeof(TftpIP));
		ASSERT(program);
		flash->LockChip();
		printf("Done\n");
	}
	else
	{
		printf("Aborted\n");
	}
}

void SerialBootTask::ProgramFlash(int intf, bool app, int version)
{

	ip_addr srvr_ip;
	unsigned int SrvrIpInFlash;
	memcpy(&SrvrIpInFlash, __DEFAULT_TFTPSERVER, 4);
	srvr_ip.addr = SrvrIpInFlash;

	char fileName[30];
	strcpy(fileName,
			app ? "App_" DEFINE_BOARD ".bin" : "BootLoad_" DEFINE_BOARD ".bin");
	if (version)
		sprintf(fileName, "App%c_"DEFINE_BOARD".bin", version);
	Flash * flash = Board::GetFlash();
	ASSERT(flash);

	int length = (int) __FLASH_SIZE;
	uint8 * data = new uint8[length];

	printf("Receiving file '%s':...", fileName);
	if(srvr_ip.addr == 0xFFFFFFFF)
		CyGOS::TftpReceive(intf, fileName, &length, data);
	else
	{
		pprintf("\n From Server %s \n", srvr_ip.ToString());
		CyGOS::TftpReceive(intf, fileName, &length, data, srvr_ip);
	}

	pprintf("Length %d\n", length);
	if (length > 0)
	{
		void * address = app ? (void *) __USER_FLASH_ROM : (void *) __FLASH_ROM;
		pprintf("Programming Address %08X\n", address);
		flash->Unlock(address, length);
		flash->Erase(address, length, EraseCallback);
		flash->Program(address, data, length, ProgramCallback);
		flash->Lock(address, length);
		DelayMs(1000);
		pprintf("\n Waiting for Restart after flash program...\n ");
		WatchDog::DisableWatchDog();
		CPU::Restart();
	}
	else
		pprintf("\n Length too short");
	delete data;
	delete flash;
}
