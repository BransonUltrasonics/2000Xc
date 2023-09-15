// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Arch/MCF/MCF5445x/WC/BoardNet.cpp_v   1.3   14 Apr 2014 07:39:02   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This object encapsulates board-specific network initialization.

#include "Board.h"
#include "LAN8701.h"
#include "KSZ8863RLL.h"
#include "assert.h"

bool Board::rmii = false;
Ethernet * Board::eth[2];

MII * Board::GetMII(int channel)
{
	switch (channel)
	{
	case 0:
		return new KSZ8863RLL(0, 0x00);//Verify channel and number
	case 1:
		return new KSZ8863RLL(1, 0x00);
	default:
		CRASH("Bad MII channel");
	}
	return 0;
}
