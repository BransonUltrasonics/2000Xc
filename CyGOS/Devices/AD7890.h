// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/AD7890.h_v   1.3   14 Apr 2014 07:25:58   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module implements AD7890 driver.

#ifndef AD7890_H_
#define AD7890_H_

#include "ADC.h"

class SPI;

class AD7890: public ADC {
public:
	AD7890(SPI * spi, int cs, int ctar);
	virtual ~AD7890();
	int ReadInput(int ch);
	void ReadInputs(int ch, int * RawVal);
protected:
	SPI * spi;
	int cs;
	int ctar;
	void WriteCR(int data);
};

#endif
