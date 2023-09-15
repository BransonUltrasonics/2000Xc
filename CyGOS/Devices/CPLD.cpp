// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/CPLD.cpp_v   1.9   26 Jan 2015 23:35:42   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//

#include "CPLD.h"
#include "assert.h"
#include "stdio.h"
#include "Board.h"
#include "CPU.h"

CPLD * CPLD::thisPtr = 0;// = new CPLD();
Latch * CPLD::Latches[NumLatches];

#define CHIPSELCT_PIN3 		  	 3
#define WAITSTATES_CPLD_CS3   	 1
#define DATABUSWIDTH_CPLD_CS3  	 8
#define CPLD_BASEADDRESS	  	 0x08200000

/*
 * CPLD: Constructs a CPLD object. At the time of construction, Latches are
 * initialized and set up with default values. For the 2000XSWC, 6 latches are
 * used and that is hard coded into the Init function.
 */
CPLD::CPLD()
{
	CPLD::thisPtr = this;
	Init();
	//TODO - Come up with safe defaults for latches at powerup
	SetSafeDefaults();
}
CPLD::~CPLD()
{
}

void CPLD::SetupChipSelect()
{
	Board::cs3 = (Board::CS3 *)CPLD_BASEADDRESS;
	CPU::SetupChipSelect(CHIPSELCT_PIN3, WAITSTATES_CPLD_CS3, DATABUSWIDTH_CPLD_CS3, Board::cs3);
}

CPLD * CPLD::GetCPLD()
{
   if(thisPtr)
      return thisPtr;
   CPLD * Cpld = new CPLD();
   return Cpld;
}
/*
 * Init: Initializes the CPLD with six latches as per 2000XSWC hardware.
 */
void CPLD::Init()
{
	for (int ii = 0; ii < NumLatches; ii++)
	{
		Latches[ii] = new Latch();
		Latches[ii]->SetCS(ii);
	}
}
/*
 * SetSafeDefaults: Setup each latch with safe default values for after
 * powerup.
 */
void CPLD::SetSafeDefaults()
{
	Latches[0]->SetPins(L0Safe);
	Latches[1]->SetPins(L1Safe);
	Latches[2]->SetPins(L2Safe);
	Latches[3]->SetPins(L3Safe);
	Latches[4]->SetPins(L4Safe);
	Latches[5]->SetPins(L5Safe);
	Latches[3]->SetPins(0xC0);
}
/*
 * GetEncoderValue: Linear Encoder data is stored maintained in the CPLD as a 24 bit
 * word. Only 8 bits of FlexBus data connect to the CPLD so the act of reading
 * is segmented into three parts. Because of a latch inside the CPLD, make sure
 * reading always starts with the upper section or else readings will be incorrect.
 * It returns metric value.
 */
uint32 CPLD::GetEncoderValue()
{
	uint32 LEData = 0;
	LEData |= Board::cs3->LE1 << 16;
	LEData |= Board::cs3->LE2 << 8;
	LEData |= Board::cs3->LE3;
	return LEData;
}

/*
 * ZeroEncoderValue: Clears the 24 bit linear encoder data on CPLD.
 */
void CPLD::ZeroEncoderValue()
{
	Board::cs3->ZeroEnc = 0;
}

/*
 * SetBuzzer: A latch inside the CPLD controls whether or not the buzzer is
 * on.  This function is used to change the state of that latch.
 * @param value: bool true for buzzer on and bool false for buzzer off
 */
void CPLD::SetBuzzer(bool value)
{
	Board::cs3->Buzzer = value ? 0xFF : 0;
}
/*
 * SetDout: This is the primary function to be used for setting digital outputs.
 * @param Dout: Specifies the signal to be set.  Look at the enums in the CPLD.h
 * file for signal names.  Try to use this function bsed on enum parameters and
 * not numbers for readability sake.
 * @param value: bool true for Active and bool false for Inactive.
 */
void CPLD::SetDout(int Dout, bool value)
{
	ASSERT(Dout < (8 * NumLatches) && Dout >= 0);
	Latches[Dout / 8]->SetPin(Dout % 8, value);
}
/*
 * GetDin: Returns the state of a given signal.
 * @param Din: Digital input to be read.  Use a value from an enum in CPLD.h for
 * this parameter.
 * @return bool: true for Active and false for Inactive
 */
bool CPLD::GetDin(int Din)
{
	bool value = false;
	unsigned char inputs = GetBuffer(Din / 8);

	Din &= 0x7;
	Din = 0x01 << Din;

	if (inputs & Din)
		value = true;

	return value;
}
/*
 * GetBuffer: Returns the state of an entire buffer which is internal to the CPLD.
 * @param buffer: (0 to 3) Number for which buffer to be read.
 * @return unsigned char: 8 bit word where each bit is the state of an input.
 * See the enums in CPLD.h for which bit and buffers correlate to which signals.
 */
unsigned char CPLD::GetBuffer(int buffer)
{
	unsigned char inputs = 0;
	ASSERT(buffer >= 0 && buffer < NumBuffers);
	switch (buffer)
	{
	case 0:
		inputs = Board::cs3->inputs1;
		break;
	case 1:
		inputs = Board::cs3->inputs2;
		break;
	case 2:
		inputs = Board::cs3->inputs3;
		break;
	case 3:
		inputs = Board::cs3->inputs4;
		break;
	case 4:
		inputs = Board::cs3->inputs5;
		break;
	default:
		CRASH("Non-existant buffer");
		break;
	}

	return inputs;
}

/*
 * ReadDoutState: This function to be used reading the current state of digital
 * outputs from Latches.
 * @param Dout: Specifies the signal to be read.  Look at the enums in the CPLD.h
 * file for signal names.  Try to use this function based on enum parameters and
 * not numbers for readability sake.
 * @return unsigned char: true for Active and bool false for Inactive.
 */
bool CPLD::ReadDoutState(int Dout)
{
	unsigned char val;
	val = Latches[Dout/8]->GetState();
	if(val & (0x01<<(Dout%8)))
	   return true;
	else
	   return false;
}
 /* GetLatch: Returns the state of shadow copy of output latches */
unsigned char CPLD::GetLatch(int LatchNum)
{
	ASSERT((LatchNum >= 0) && (LatchNum < NumLatches));
	return Latches[LatchNum]->GetState();
}

void CPLD::SetLatch(int LatchNum, unsigned char val)
{
	ASSERT((LatchNum >= 0) && (LatchNum < NumLatches));
	Latches[LatchNum]->SetPins(val);
}
/*
 * Returns the major version of CPLD software
*/
unsigned char CPLD::ReadMajorVer()
{
	return Board::cs3->MajorVer;
}

/*
 * Returns the minor version of CPLD software
*/
unsigned char CPLD::ReadMinorVer()
{
	return Board::cs3->MinorVer;
}

/*
 * Latch: Latch constructor. Sets default values for the Latch as well.
 * cs is intentially made -1 as this is used as a check later on to make sure
 * the Latch has actually been assigned to something before use.
 */
Latch::Latch()
{
	cs = -1;
	state = 0;
	latch = 0;
}
Latch::~Latch()
{
}
/*
 * SetCS: Sets a chip select value for the Latch. This chip select value
 * tells the Latch what address it is supposed to read and write.
 * @param CS: (0 to 5) Numerical chip select value which ties a software Latch
 * to a latch in hardware.
 */
void Latch::SetCS(int CS)
{
	cs = CS;
	switch (cs)
	{
	case 0:
		latch = &Board::cs3->Latch1;
		break;
	case 1:
		latch = &Board::cs3->Latch2;
		break;
	case 2:
		latch = &Board::cs3->Latch3;
		break;
	case 3:
		latch = &Board::cs3->Latch4;
		break;
	case 4:
		latch = &Board::cs3->Latch5;
		break;
	case 5:
		latch = &Board::cs3->Latch6;
		break;
	default:
		CRASH("Wrong chip select value");
		break;
	}
}
/*
 * SetPin: Sets a pin on a Latch.
 * @param pin: (0 to 7) pin to be set.
 * @param value: bool true for Active and bool false for Inactive.
 */
void Latch::SetPin(int pin, bool value)
{
	ASSERT(cs >= 0);
	ASSERT(pin >= 0 && pin < 8);
	if (value)
		state |= 0x01 << pin;
	else
		state &= ~(0x01 << pin);

	*latch = state;
}
/*
 * SetPins: Sets all pins on a Latch at once.
 * @param value: unsigned char where each bit is the state of a pin.
 */
void Latch::SetPins(unsigned char value)
{
	ASSERT(cs >= 0);
	state = value;
	*latch = state;
}
int Latch::GetCS()
{
	return cs;
}

unsigned char Latch::GetState()
{
	return state;
}
