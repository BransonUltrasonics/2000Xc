// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Devices/AD7689.h_v   1.0   14 Apr 2014 06:09:48   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module implements AD7689 driver.

#ifndef AD7689_H_
#define AD7689_H_

#include "ADC.h"
#include "CpuDefs.h"
class SPI;

/**
 *    Selects the ADC output
 */
enum AD7689AdcInput
{
   Adc7689Ch0,
   Adc7689Ch1,
   Adc7689Ch2,
   Adc7689Ch3,
   Adc7689Ch4,
   Adc7689Ch5,
   Adc7689Ch6,
   Adc7689Ch7,
};

class AD7689: public ADC
{
public:
   AD7689(SPI *spi, int cs, int ctar, int MaxChNumForSequencing);
   virtual ~AD7689();
   int ReadInput(int ch);
   void ReadInputs(int ch, int * RawVal);
   virtual void ReadInputsThroughSequencing(int * RawVal);
   void EnableSequencing(int MaxChNum);
   void ReadDummyInput(int Cnt);
   int MaxCh;
protected:
   SPI * spi;
   int cs;
   int ctar;
   uint16 * ChVals;
};
#endif /* AD7689_H_ */
