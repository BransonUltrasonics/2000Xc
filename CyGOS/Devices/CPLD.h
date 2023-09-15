// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/CPLD.h_v   1.8   26 Jan 2015 23:36:44   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//


#ifndef CPLD_H_
#define CPLD_H_

#include "CpuDefs.h"
class Latch;
#define NumLatches 6
#define NumBuffers 5

#define L0Safe 0
#define L1Safe 0
#define L2Safe 0
#define L3Safe 0xC1
#define L4Safe 0x39
#define L5Safe 0xE7


class CPLD
{
public:
	CPLD();
	virtual ~CPLD();
	static void Init();
	static CPLD * thisPtr;
	static void SetSafeDefaults();
	static void SetDout(int Dout, bool value);
	static bool GetDin(int Dout);
	static unsigned char GetBuffer(int buffer);
	static uint32 GetEncoderValue();
	static void ZeroEncoderValue();
	static void SetBuzzer(bool value);
	static CPLD * GetCPLD();
	static Latch * Latches[NumLatches];
	static unsigned char GetLatch(int LatchNum);
	static void SetLatch(int LatchNum, unsigned char val);
	static bool ReadDoutState(int);
	static unsigned char ReadMajorVer();
	static unsigned char ReadMinorVer();
	static void SetupChipSelect();
};

class Latch
{
public:
	Latch();
	virtual ~Latch();
	void SetCS(int CS);
	void SetPin(int pin, bool value);
	void SetPins(unsigned char value);
	int GetCS();
	unsigned char GetState();
protected:
	/*
	 * cs: Chip select for a particular latch, unimportant after a Latch is
	 * set up.
	 */
	int cs;
	/*
	 * state: State is a shadow register which holds the value of all outputs
	 * for a Latch.
	 */
	unsigned char state;
	/*
	 * latch: Pointer to the location in memory which must be written to so
	 * FlexBus addressing will be handled properly.
	 */
	volatile unsigned char * latch;
};

enum Din1
{
	Run_Sig = 0, Seek_Sig, Mem_Store_Sig, Mem_Clear_Sig, OL_Input_Sig, Pwr_On_Sig, Pwr_Off_Sig, J3_17_Input_Sig
};
enum Din2
{
	EmptyIn2 = 8, ULS_Sig, E_STOP2_24V_SIG, Ext_LS_Sig, PB1_Sig, PB2_Sig, E_Stop_Sig, EmptyIn1,
};
enum Din3
{
	J3_1_Input_Sig = 16, EmptyIn3, J3_31_Input_Sig, Ext_Reset_Sig, J3_32_Input_Sig, J3_33_Input_Sig, J3_19_Input_Sig, Cycle_Abort_Sig,
};

enum Din4
{
	Row1 = 24, Row0, EmptyIn5, EmptyIn4, SV_Hi_Fail, SV_Lo_Fail, Ext_Seek_In, SV_ON,
};

enum Din5
{
	Nand_Busy = 32, HSB, EmptyIn11, EmptyIn10, EmptyIn9, EmptyIn8, EmeptyIn7, EmptyIn6
};

//U24
enum Dout1
{
	Bank1 = 0, Bank2, Bank3, Bank4, Bank5, Bank6, Empty0, Seg1H,
};
//U4
enum Dout2
{
	Seg1A = 8, Seg1B, Seg1C, Seg1D, Seg2A, Empty7, Empty8, Empty9,
};
//U59
enum Dout3
{
	SEEK_OUT_SIG = 16, RUN_OUT_SIG, OL_RESET_SIG, TEST_OUT_SIG, SV1, SV2, SV3, SV4,
};

//test it(Act2 CS). Some addition here. App code changes??
enum Dout4
{
	Latch_OE = 24, TRSEnable, MemStoreOut, Trig_Sw_Actv, SVDrive_Lo, Pwr_Off_Delay, NAND_WP, Flash_WP,
};

//U29
enum Dout5
{
	Act_Clear = 32, TP64, TP65, Reject, Suspect, PB_Release, TP66, TP67,
};

//U22
enum Dout6
{
	Gen_Alarm = 40, ReadySig, Weld_On, TP68, TP69, J3_8, J3_22, J3_36,
};
#endif

