// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Arch/MCF/MCF5445x/WC/Board.h_v   1.5   09 Jul 2014 12:26:06   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This object encapsulates board-specific initialization.

#ifndef BOARD_H_
#define BOARD_H_

#include "stdlib.h"

class Ethernet;
class I2C;

// These definitions do not belong into CPU definitions file because they are
// board-specific, a board may or may not have BBRAM...
//extern unsigned char __BBRAM_START[];
//extern unsigned char __BBRAM_END[];
//extern unsigned char __BBRAM_RAM_START[];
//extern unsigned char __BBRAM_RAM_END[];

extern unsigned char __FLASH_ROM[];
extern unsigned char __FLASH_BASE[];
extern unsigned char __FLASH_SIZE[];
extern unsigned char __FLASH_END[];
extern unsigned char __TEXT_START[];
extern unsigned char __TEXT_END[];
extern unsigned char __FLASH_RAM[];

extern int __SERIAL_NUMBER;
extern unsigned char __ETHERNET_MAC[6];
extern unsigned char __ETHERNET_MAC0[6];
extern unsigned char __ETHERNET_MAC1[6];
extern unsigned char __DEFAULT_TFTPSERVER[4];

extern char __USER_FLASH_SIZE[];
extern char __USER_FLASH_RAM[];
extern char __USER_FLASH_ROM[];
#define	PRINTF_INPUT_SIZE	  25000
#define PRINTF_OUTPUT_SIZE	  25000

class MII;
class Flash;
class SPI;
typedef void (*TimerCallback)();

/**
 * Class Board: Class implements board-specific functionality. All functions
 * and data members are static, so no instance of this class is necessary.
 */
class Board
{
public:
	struct CS3
		{
			/*
			 * Addr 0x00
			 */
			unsigned char inputs1;
			unsigned char inputs1_Fill[3];
			/*
			 * Addr 0x04
			 */
			unsigned char inputs2;
			unsigned char inputs2_Fill[3];
			/*
			 * Addr 0x08
			 */
			unsigned char inputs3;
			unsigned char inputs3_Fill[3];
			/*
			 * Addr 0x0C
			 */
			unsigned char inputs4;
			unsigned char inputs4_Fill[3];
			/*
			 * Addr 0x10
			 */
			unsigned char LE1;
			unsigned char LE1_Fill[3];
			/*
			 * Addr 0x14
			 */
			unsigned char LE2;
			unsigned char LE2_Fill[3];
			/*
			 * Addr 0x18
			 */
			unsigned char LE3;
			unsigned char LE3_Fill[3];

			/*
			* Addr 0x1C
			*/
			unsigned char inputs5;
			unsigned char inputs5_Fill[3];

			/*
			 * Addr 0x20
			 */
			unsigned char Latch1;
			unsigned char Latch1_Fill[3];
			/*
			 * Addr 0x24
			 */
			unsigned char Latch2;
			unsigned char Latch2_Fill[3];
			/*
			 * Addr 0x28
			 */
			unsigned char Latch3;
			unsigned char Latch3_Fill[3];
			/*
			 * Addr 0x2C
			 */
			unsigned char Latch4;
			unsigned char Latch4_Fill[3];
			/*
			 * Addr 0x30
			 */
			unsigned char Latch5;
			unsigned char Latch5_Fill[3];
			/*
			 * Addr 0x34
			 */
			unsigned char Latch6;
			unsigned char Latch6_Fill[3];
			/*
			* Addr 0x38
			*/
			unsigned char MajorVer;
			unsigned char MajorVer_Fill[3];
			/*
			* Addr 0x3C
			*/
			unsigned char MinorVer;
			unsigned char MinorVer_Fill[3];
			/*
			* Addr 0x40
			*/
			unsigned char ZeroEnc;
			unsigned char ZeroEnc_Fill[3];
			unsigned char Fill1[4];
			/*
			 * Addr 0x48
			 */
			unsigned char Buzzer;
		};

	static void * AllocAlignedNoCache(size_t size, int align);
	static void FreeAlignedNoCache(void * ptr);
	static void Init(bool cache);
	static void UpdateLEDs(unsigned char * state);
	static void SetupSlowCS8bit(int cs, int wait, volatile void * addr);
	static MII * GetMII(int channel);
	static Flash * GetFlash();
	static SPI * GetSPI(int instance, int irqlevel, int irqprio);
	static bool rmii;
	//Timers
	static void InstallTimer(int usInterval, TimerCallback callback,
			int instance);
	static void StartTimer(int instance);
	static void StopTimer(int instance);
	//RTC
	static void InitRTC();
	static int GetRTCTime();
	static I2C * GetI2C(int instance, int level, int priority);
	static Ethernet * eth[];
	static int EthCount()
	{
		return 2;
	}
	static void InitProfilerTimer(int instance);
	inline static int GetProfilerTimerCounter(int instance) {
		return MCF_DTIM_DTCN(instance);
	}
	static void InitWD();
	static void TriggerWD();
	static volatile CS3 * cs3;
	static inline void InitBootFlashBusyReady();
	bool GetFlashStatus();
protected:
	static SPI * spi[1];
	static I2C * i2c[1];
	static int dmaTimers;
};

#endif
