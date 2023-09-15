// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/ADC.h_v   1.4   11 Jun 2014 13:41:44   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This file implements generic ADC driver.

#ifndef ADC_H_
#define ADC_H_

class ADC
{
public:
	/**
	 * Read single channel in raw.
	 * @param ch Channel number, range depends on the device.
	 */
	virtual int ReadInput(int ch) = 0;
	/**
	 * Read specified channels in raw.
	 * @param ch Up to 32 bits, set if read, clear if skip the channel.
	 * @param Val Array of results in raw. All channel values are placed into
	 * their indexed locations, if channel is skipped the index is skipped as
	 * well.
	 */
	virtual void ReadInputs(int ch, int * Val) = 0;
	/**
	 * Support for adcs which gives raw values for channels in a sequence without
	 * needing to know about a specific  conversion command with channel number
	 * Derived class shall override the function in this case.Base class will do nothing
	 */
	virtual void ReadInputsThroughSequencing(int * Val)
	{
		Val = 0;
	}
};

#endif
