// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Arch/MCF/MCF5445x/FEC.h_v   1.3   14 Apr 2014 07:34:26   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module declares architecture-specific FEC object.

#ifndef FEC_H_
#define FEC_H_

#include "FecBase.h"

/**
 * class FEC: Fast Ethernet Controller driver implementation for the MCF532x
 * family.
 */
class FEC : public FecBase
{
public:
	FEC(int chan, MII * mi, bool rmii, unsigned char * macAddr = 0);
	virtual ~FEC();
	int GetChannel() const
	{
		return channel;
	}
	static FEC * fecs[2];
protected:

	static void IntHandler0(int vector, void * frame);
	static void IntHandler1(int vector, void * frame);

};

#endif
