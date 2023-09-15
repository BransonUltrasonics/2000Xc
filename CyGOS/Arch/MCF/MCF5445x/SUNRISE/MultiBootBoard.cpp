// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Arch/MCF/MCF5445x/WC/MultiBootBoard.cpp_v   1.4   11 Dec 2014 08:30:16   AnPawar  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3 MultiBoot loader.
//
// This module provides board-specific functions for common MultiBoot tasks.
//
// TODO Everything is copied from M54455EVB, only flash and SDRAM settings are verified. The rest must be checked.

#include "SerialBootTask.h"
#include "CyGOS.h"
#include "Board.h"
#include "FlashM29W320E.h"
#include "LED.h"
#include "RTOS.h"
#include "CPU.h"
#include "MultiBootCpu.h"
#include "string.h"
#include "FlashM29W128G.h"
#include "MMU.h"

extern char __USER_FLASH_ROM[];
extern char __USER_FLASH_RAM[];

void SerialBootTask::Init(void * romBase)
{
	romBase = NULL;
	list.AddTail(Board::GetFlash());
}

void SerialBootTask::PrintData()
{
	printf("Ethernet 0 MAC address: ");
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
			printf(":");
		printf("%02X", __ETHERNET_MAC0[i]);
	}
	printf("\n");
	printf("Ethernet 1 MAC address: ");
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
			printf(":");
		printf("%02X", __ETHERNET_MAC1[i]);
	}
	printf("\n");
}

void SerialBootTask::PrintPrompts()
{
	if (Board::EthCount() > 0)
		printf("<3>\t\t\tTFTP download the app using Ethernet 0\n");
	if (Board::EthCount() > 1)
		printf("<4>\t\t\tTFTP download the app using Ethernet 1\n");
	if (Board::EthCount() > 0)
		printf("<5>\t\t\tTFTP download the boot loader using Ethernet 0\n");
	if (Board::EthCount() > 1)
		printf("<6>\t\t\tTFTP download the boot loader using Ethernet 1\n");
	if (Board::EthCount() > 0)
		printf("<7>\t\t\tTFTP download the versioned app using Ethernet 0\n");
	if (Board::EthCount() > 1)
		printf("<8>\t\t\tTFTP download the versioned app using Ethernet 1\n");
	if (memcmp(__ETHERNET_MAC0, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
		printf("<M>\t\t\tEnter Ethernet 0 MAC address\n");
	if (memcmp(__ETHERNET_MAC1, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
		printf("<m>\t\t\tEnter Ethernet 1 MAC address\n");
	if ((memcmp(__ETHERNET_MAC0, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
			|| (memcmp(__ETHERNET_MAC1, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0))
		printf("<0>\t\t\tSet Ethernet 0 and 1 MAC addresses to defaults\n");

	printf("<T>\t\t\t Set Default TFTP Server\n");

}

unsigned short * SerialBootTask::FlashAddress(unsigned short * ramAddress)
{
	return (unsigned short *) ((((int) ramAddress) & 0x00FFFFFF) | 0x00000000);
}

static void SetMacToDefaults(Flash * flash, unsigned char * mac,
		const char * addr)
{
	printf("\nEthernet MAC address: ");
	for (int i = 0; i < 6; i++)
	{
		if (i != 0)
			printf(":");
		printf("%02X", addr[i] & 0xFF);
	}
	printf("\n");
	unsigned short * wptr = (unsigned short *) mac;
	wptr = SerialBootTask::FlashAddress(wptr);
	if (memcmp(wptr, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
	{
		ASSERT(flash);
		flash->UnlockChip();
		CyGOS::DelayMs(100);
		bool program = flash->Program(wptr, (void *) addr, 6);
		ASSERT(program);
		flash->LockChip();
		CyGOS::DelayMs(100);
	}
	else
		printf("Already initialized\n");
}

bool SerialBootTask::CheckPrompts(int ch)
{
	switch (ch)
	{
	case '0':
		SetMacToDefaults(flash, __ETHERNET_MAC0, "\x00\xC6\x05\x00\x38\x01");
		SetMacToDefaults(flash, __ETHERNET_MAC1, "\x00\xC6\x05\x00\x38\x02");
		return true;
	case 'M':
		if (memcmp(__ETHERNET_MAC0, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
		{
			EnterMacAddress(__ETHERNET_MAC0);
			return true;
		}
		break;
	case 'm':
		if (memcmp(__ETHERNET_MAC1, "\xFF\xFF\xFF\xFF\xFF\xFF", 6) == 0)
		{
			EnterMacAddress(__ETHERNET_MAC1);
			return true;
		}
		break;
	case '3':
		if (Board::EthCount() > 0)
			TftpDownload(0, true);
		break;
	case '4':
		if (Board::EthCount() > 1)
			TftpDownload(1, true);
		break;
	case '5':
		if (Board::EthCount() > 0)
			TftpDownload(0, false);
		break;
	case '6':
		if (Board::EthCount() > 1)
			TftpDownload(1, false);
		break;
	case '7':
		if (Board::EthCount() > 1)
			TftpDownloadVersioned(0, true);
		break;
	case '8':
		if (Board::EthCount() > 1)
			TftpDownloadVersioned(1, true);
		break;
	case 'T':
		EnterTftpServerAddr(__DEFAULT_TFTPSERVER);
			return true;
	}
	return false;
}

void SerialBootTask::ExecuteFlash()
{
	MMU::RemapCodeData(true,true);
	DisableInterrupts();
	unsigned long * flash = (unsigned long *) __USER_FLASH_ROM;
	// Each image has following entry point locations:
	// flash[0] - Application start from RAM (address)*(flash + 0)
	// flash[1] - Application start from flash (address)*(flash + 1)
	flash += 1;
	pprintf("\n flash pointer %08X %08X", flash, __USER_FLASH_ROM);
	void (*p)() = (void (*)()) (*flash);
	pprintf("\n Transferring to address %p\n", p);
	p();
}

void SerialBootTask::MoveImageToSdram()
{
	MMU::RemapCodeData(true,true);
	// All local variables should be static so that when memcpy  copies SDRAM
	// contents around, the variables will not overlap the new program image.
	// Variables allocated on stack could be anywhere, including the new code
	// area.
	RTOS::Stop();
	printf("\nCopying RAM image to right place...\n");
	// just in case, reset the flash.
	MultiBootCpu::WriteProtectCs();
	bootImageFlash = (unsigned int) __USER_FLASH_RAM;
	static unsigned long * flash = (unsigned long *) __USER_FLASH_RAM;
	memcpy((void *) bootImageFlash, bootImageBuffer, bootImageLength);
	// Each image has following entry point locations:
	// flash[0] - Application start from RAM (address)
	// flash[1] - Application start from flash (address)
	void (*p)() = (void (*)()) (*flash);
	printf("Transferring to address %p\n", p);
	p();
}
