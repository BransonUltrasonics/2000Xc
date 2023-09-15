// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Arch/MCF/MCF5445x/WC/LED.cpp_v   1.3   14 Apr 2014 07:40:02   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This object encapsulates board-specific LED handling.
//
// TODO Everything is copied from M54455EVB, only flash and SDRAM settings are verified. The rest must be checked.

#include "LED.h"
#include "MMU.h"
#include "CPU.h"
#include "assert.h"
#include "stdio.h"

volatile char * LED::lptr;

/**
 * Init: Initialize Diagnostic LED outputs for WC.
 */
void LED::Init()
{

	MCF_PAD_PAR_SSI = (MCF_PAD_PAR_SSI_PAR_TXD_GPIO | MCF_PAD_PAR_SSI_PAR_RXD_GPIO |
			MCF_PAD_PAR_SSI_PAR_BCLK_GPIO | MCF_PAD_PAR_SSI_PAR_FS_GPIO);

	MCF_GPIO_PDDR_SSI |= (MCF_GPIO_PDDR_SSI_PDDR_SSI0 | MCF_GPIO_PDDR_SSI_PDDR_SSI1
			| MCF_GPIO_PDDR_SSI_PDDR_SSI2 | MCF_GPIO_PDDR_SSI_PDDR_SSI3 );

	//lptr = (volatile char *)&MCF_GPIO_PPDSDR_ATAH;

}
//////////////////////////////////////
//WC Board specific
/*
CPU Pin  Part of LED  Color when high   Port MCF_GPIO_PPDSDR_SSI Bit
D21			LED12		Green 		  MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI1
E19			LED12		Red			  MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI3
E20			LED5		Red			  MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI2
D22			LED5		Green		  MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI0
*/
/**
 * Set: Set specified LED to specified state. DS5 is LED1 and DS6 is LED2.
 * @param led LED number, 0 - all, or 1...2
 * @param state LED state 0 - Off, 1 - Red, 2 - Green, 3 - Yellow
 */
void LED::Set(int led, int state)
{
unsigned char LEDStatus = 0;
   switch(led){
      case 1:
         MCF_GPIO_PCLRR_SSI = MCF_GPIO_PPDSDR_SSI & ~MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI0;
         MCF_GPIO_PCLRR_SSI = MCF_GPIO_PPDSDR_SSI & ~MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI2;
         switch(state){
            case LedOff:
            break;
            case LedRed:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI2);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
            case LedGreen:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI0);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
            case LedYellow:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI0 | MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI2);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
         }
      break;
      case 2:
         MCF_GPIO_PCLRR_SSI = MCF_GPIO_PPDSDR_SSI & ~MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI1;
         MCF_GPIO_PCLRR_SSI = MCF_GPIO_PPDSDR_SSI & ~MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI3;
         switch(state){
            case LedOff:
            break;
            case LedRed:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI3);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
            case LedGreen:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI1);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
            case LedYellow:
               LEDStatus = (MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI1 | MCF_GPIO_PPDSDR_SSI_PPDSDR_SSI3);
               MCF_GPIO_PPDSDR_SSI |= LEDStatus;
            break;
         }
      break;
   }
}

/**
 * SetAll: Set all LEDs to specified states.
 * @param state LED state buffer. Only 4 LSB from first byte are used.
 */
void LED::SetAll(unsigned char * state)
{
	state = 0;
//	*lptr = *state;
}
