// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/LPC1758.h_v   1.1   14 Apr 2014 07:26:04   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module implements LPC1758 driver.

#ifndef LPC1758_H_
#define LPC1758_H_
#include "CpuDefs.h"

class SPI;

class LPC1758
{
public:
	LPC1758(SPI *spi, int cs, int ctar);
	virtual ~LPC1758();
	int WriteReadVal(int WriteVal);
protected:
	SPI * spi;
	int cs;
	int ctar;
};

#endif /* LPC1758_H_ */
