/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/iotest332.cpp_v   1.24   Oct 09 2017 16:59:08   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/iotest332.cpp_v  $
 * 
 *    Rev 1.24   Oct 09 2017 16:59:08   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.23   16 Apr 2015 07:18:00   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.22   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.21   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.20   02 Jan 2015 04:04:12   rjamloki
 * SetDACChannel(),comment corrected
 * 
 *    Rev 1.19   28 Nov 2014 07:36:26   rjamloki
 * Removed unused Variables.memset the structure DUPS_MSGBUF to zero.
 * 
 *    Rev 1.18   10 Nov 2014 04:51:14   AnPawar
 * added new factory test commands.
 * 
 *    Rev 1.17   20 Oct 2014 06:20:34   AnPawar
 * WritePortA() function changed
 * 
 *    Rev 1.16   06 Oct 2014 06:37:12   AnPawar
 * removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.15   03 Oct 2014 05:58:00   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.14   26 Sep 2014 03:26:14   rjamloki
 * Fixes to pass labview test
 * 
 *    Rev 1.13   18 Aug 2014 01:41:02   rjamloki
 * Cleaned up for Sunrise
 * 
 *    Rev 1.12   28 Jul 2014 12:40:46   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.11   09 Jul 2014 11:05:04   rjamloki
 * serial command handler function added.
 * 
 *    Rev 1.10   11 Jun 2014 11:46:00   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:47:58   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:07:40   rjamloki
 * coverity fixes and extern variables clean up
 * 
 *    Rev 1.7   21 Apr 2014 13:31:10   rjamloki
 * Enable/Disable beeper functionality added
 * 
 *    Rev 1.6   14 Apr 2014 10:02:18   rjamloki
 * Fixed to use CPLD buffers.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:26   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:38   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

#include "qdef.h"
#include "battram.h"
#include "beep.h"
#include "util.h"
#include "inports.h"
#include "outports.h"
#include "serial.h"
#include "actnvram.h"
#include "portable.h"
#include "ascii.h"
#include "psnvram.h"
#include "iotest332.h"
#include "fpled.h"
#include "keypad.h"
#include "mansensr.h"
#include "menu5.h"
#include "spidd.h"
#include "menu.h"
#include "snsrcalb.h"
#include "command.h"
#include "rtclock.h"
#include "param.h"
#include "menu7a.h"
#include "state.h"
#include "dups_api.h"
#include "statedrv.h"
#include "stdlib.h"
#include "stdio.h"
#include "A1025R.h"
#include "UndefPrintf.h"
#include "inputs.h"
#include "CPLD.h"
#include "Terminal.h"
#include "DUPS_ManagerTask.h"
#include "encoder.h"
#include "qsm.h"
#include "digout.h"
#include "InputTask.h"

#define MAXCASE                     71       /* Maximum number of commands allowed            */
#define DIAG_BUFFER_SIZE            40       /* RS-232 buffer size                            */
#define BS                          0x08     /* No this isn't Bill Surprenant, its Back Space */
#define STROBELOW                   0x08
#define STROBEHIGH                  0x09
#define NMBR_CHARS_ON_VFDISPLAY     (LINESIZE*DISPLAY_LINES)   /* Chars on display            */
#define NUM_MSGS                    16       /* Number of text strings output / pass in help  */
#define DUPS_WAIT_TIME              3000     /* Wait for 3 seconds                            */

/*---------------------------------------LOCAL  DATA-----------------------------------------**/

struct CALDATA
{
   UINT16 Date[3];
   SINT16 Loadcell[11];
   UINT16 Springrate;
   UINT32 Stroke;
   SINT16 SystemPressure;
   SINT16 PressureTable[11];
   SINT16 Offset;
};

SINT8  *WritePrtCntl;
SINT8  *WritePrtc;
struct  CALDATA CalData;
UINT16  SerialMqueueValue;
STR     DiagBuffer[DIAG_BUFFER_SIZE];        /* Input data coming through serial port         */
UINT32  CmdNumber;                           /* Command # comming in from serial port         */
signed char   Inptr = -1;                          /* Used to put data into DiagBuffer              */
BOOLEAN DisplayHelpFlag = FALSE;
BOOLEAN ExtraDataFlag = TRUE;                /* Assume extra data                             */       
BOOLEAN IOTestFlag = FALSE;                  /* DUPS needs call from 1 ms int handler         */       
BOOLEAN DUPSPendingFlag = FALSE;
UINT8   ExtraData;
BOOLEAN DiagStopFlag;
UINT8   SavedOutptr;
UINT32  GlobalValue;
SINT16  DUPSWaitTime;

const STR    DiagPrompt[]      = "\r\n2000 >";
const STR    DiagSyntaxError[] = "\r\nI don't have a clue what you are asking for.  Please try again.";
const STR    ControlLevelStr[] = "\r\nControl Level = ";
const STR    WattStr[]         = "\r\nWattage = ";
const STR    FrequencyStr[]    = "\r\nFrequency = ";
const STR    LifetimeStr[]     = "\r\nLifetime Counter = ";
const STR    SerialNumberStr[] = "\r\nSerial Number = ";
const STR    NoDataStr[]       = "\r\n Where's the Data?";
const STR    DisabledStr[]     = "\r\n Sorry, Command not implemented yet";
const STR    FRAMPassedStr[]    = " Passed\r\n"; 
const STR    FRAMFailedStr[]    = " Failed\r\n"; 
const STR    DUPSFailedStr[]   = " = DUPS Failed\r\n2000 >"; 
const STR    DUPSPassed1Str[]  = " watts  "; 
const STR    DUPS15KStr[]      = " 15 kHz\r\n2000 >"; 
const STR    DUPS20KStr[]      = " 20 kHz\r\n2000 >"; 
const STR    DUPS30KStr[]      = " 30 kHz\r\n2000 >"; 
const STR    DUPS40KStr[]      = " 40 kHz\r\n2000 >"; 


const STR    PSSerialNumberStr[]   = "\r\n S/N="; 
const STR    ActuatorStr[]         = " ID="; 
const STR    GainFactorStr[]       = "  Gain factor="; 
const STR    StrokeStr[]           = " Stroke="; 
const STR    DiameterStr[]         = " Diameter="; 
const STR    VersionStr[]          = " Version="; 
const STR    DefaultStr[]          = "\r\n---Default Cal---"; 
const STR    UserStr[]             = "\r\n----User Cal----"; 
const STR    DateStr[]             = " Date: "; 
const STR    LCTableStr[]          = " LC Table="; 
const STR    SpringrateStr[]       = " Springrate slope="; 
const STR    StrokeLengthStr[]     = " Stroke length="; 
const STR    SystemPressureStr[]   = " System pressure="; 
const STR    PressureCountStr[]    = " A/D pressure count="; 
const STR    PressureTableStr[]    = " Pressure table="; 
const STR    ForceCountStr[]       = " A/D force count="; 
const STR    OffsetStr[]           = " Home Offset="; 
const STR    aeStr[]               = "ae"; 
const STR    aedStr[]              = "aed"; 
const STR    aesStr[]              = "aes";
const STR    aefStr[]              = "aef"; 
const STR    MicroStr[]            = "MICRO";
const STR    MicrocStr[]           = "MICROC";
const STR    UnknownStr[]          = "UNKNOWN\r\n"; 
const STR    Diameter1_5Str[]      = "1.5 in  "; 
const STR    Diameter2_0Str[]      = "2.0 in  "; 
const STR    Diameter2_5Str[]      = "2.5 in  "; 
const STR    Diameter3_0Str[]      = "3.0 in  "; 
const STR    Diameter3_25Str[]     = "3.25 in  "; 
const STR    Diameter4_0Str[]      = "4.0 in  "; 
const STR    Diameter32Str[]       = "32 mm  ";
const STR    Diameter40Str[]       = "40 mm  "; 
const STR    Diameter50Str[]       = "50 mm  "; 
const STR    Diameter63Str[]       = "63 mm  "; 
const STR    Diameter80Str[]       = "80 mm  "; 
const STR    Stroke4Str[]          = "4.0 in  "; 
const STR    Stroke5Str[]          = "5.0 in  "; 
const STR    Stroke6Str[]          = "6.0 in  "; 
const STR    Stroke2Str[]          = "2.0 in  "; 
const STR    Stroke8Str[]          = "8.0 in  ";
const STR    Stroke50Str[]         = "50 mm  ";  
const STR    Stroke70Str[]         = "70 mm  ";
const STR    Stroke75Str[]         = "75 mm  ";
const STR    Stroke80Str[]         = "80 mm  "; 
const STR    Stroke100Str[]        = "100 mm  "; 
const STR    Stroke125Str[]        = "125 mm  "; 
const STR    Stroke160Str[]        = "160 mm  "; 
const STR    CalibratePassStr[]    = " Calibration=Pass\r\n"; 
const STR    CalibrateFailStr[]    = " Calibration=Fail\r\n"; 
const STR    CalibrateFactoryStr[] = " Calibration=Factory\r\n";
const STR    EncoderStr[]          = " Encoder Type = ";  


/* Help Messages (must all be same length string, programmer is too lazy to do it right) */


const STR    MoreStr[]       = "--More--  Press any key   ";
const STR    FTHelp0Str[]    = "The syntax is:          \r\n";
const STR    FTHelp1Str[]    = "FT xx yy                \r\n";
const STR    FTHelp2Str[]    = "  xx is the command #   \r\n";
const STR    FTHelp3Str[]    = "  yy write data         \r\n";
const STR    FT00Str[]       = "00 R Print Status         ";
const STR    FT01Str[]       = "01 W Print Data           ";
const STR    FT02Str[]       = "02 W Print Interface      ";
const STR    FT03Str[]       = "03 R Keyboard             ";
const STR    FT04Str[]       = "04 R Amplitude            ";
const STR    FT05Str[]       = "05 R Power                ";
const STR    FT06Str[]       = "06 R Memory               ";
const STR    FT07Str[]       = "07 R Frequency            ";
const STR    FT08Str[]       = "08 R 10V Ref              ";
const STR    FT09Str[]       = "09 R Ext Amp              ";
const STR    FT10Str[]       = "10 R Ext Freq             ";
const STR    FT11Str[]       = "11 R Ground               ";
const STR    FT12Str[]       = "12 R Nvram                ";
const STR    FT13Str[]       = "13 W Erase Nvram          ";
const STR    FT14Str[]       = "14 R Test FRAM             ";
const STR    FT15Str[]       = "15 W Erase FRAM            ";
const STR    FT16Str[]       = "16 W Initialize FRAM       ";
const STR    FT17Str[]       = "17 W Beep On              ";
const STR    FT18Str[]       = "18 W Beep Off             ";
const STR    FT19Str[]       = "19 W Set Amplitude D/A    ";
const STR    FT20Str[]       = "20 W Set Freq Offset D/A  ";
const STR    FT21Str[]       = "21 W Digital Pot          ";
const STR    FT22Str[]       = "22 R U79 Port A           ";
const STR    FT23Str[]       = "23 W U79 Port B           ";
const STR    FT24Str[]       = "24 R U79 Port C           ";
const STR    FT25Str[]       = "25 W U67 Port A           ";
const STR    FT26Str[]       = "26 R U67 Port B           ";
const STR    FT27Str[]       = "27 W U67 Port C           ";
const STR    FT28Str[]       = "28 W/R DUPS Link          ";
const STR    FT29Str[]       = "29 R TPU                  ";
const STR    FT30Str[]       = "30 W TPU channel 1 & 11   ";
const STR    FT31Str[]       = "31 W Write Message on VF  ";
const STR    FT32Str[]       = "32 W Clear VF Display     ";
const STR    FT33Str[]       = "33 W Write Full Display   ";
const STR    FT34Str[]       = "34 W/R SPI Bus            ";
const STR    FT35Str[]       = "35 W Actuator Interface   ";
const STR    FT36Str[]       = "36 W Actuator Interface   ";
const STR    FT37Str[]       = "37 W Actuator Interface   ";
const STR    FT38Str[]       = "38 W Leds                 ";
const STR    FT39Str[]       = "39 W Bargraph             ";
const STR    FT40Str[]       = "40 W Make Not Ready       ";
const STR    FT41Str[]       = "41 W Shut off FT cmds     ";
const STR    FT42Str[]       = "42 W Restore User I/O     ";
const STR    FT43Str[]       = "43 R CRC on P/S Novram    ";
const STR    FT44Str[]       = "44 R CRC on Act Novram    ";
const STR    FT45Str[]       = "45 R CRC on FRAM 1 of 16   ";
const STR    FT46Str[]       = "46 R CRC on program flash ";
const STR    FT47Str[]       = "47 F Execute function     ";
const STR    FT48Str[]       = "48 F Disable beepers      ";
const STR    FT49Str[]       = "49 F Enable beepers       ";
const STR    FT50Str[]       = "50 F View calibration     ";
const STR    FT51Str[]       = "51 Not Available          ";
const STR    FT52Str[]       = "52 F Actuator Cold Start  ";
const STR    FT53Str[]       = "53 F Cold Start           ";
const STR    FT54Str[]       = "54 F Cold Start Plus      ";
const STR    FT55Str[]       = "55 W Set Time HH:MM       ";
const STR    FT56Str[]       = "56 W Set date MM/DD/YY    ";
const STR    FT57Str[]       = "57 R Display memory       ";
const STR    FT58Str[]       = "58 W Write to memory      ";
const STR    FT59Str[]       = "59 F Reset 1001R board    ";
const STR    FT60Str[]       = "60 F Force SBCReadyFlag   ";
const STR    FT61Str[]       = "61 W Micro Home Force     ";
const STR    FT62Str[]       = "62 R Linear Encoder       ";
const STR    FT63Str[]       = "63 R RTC				  ";
const STR    FT64Str[]       = "64 R MAC Address          ";
const STR    FT65Str[]       = "65 W Set DAC              ";
const STR    FT66Str[]       = "66 R Act pressure & flow  ";
const STR    FT67Str[]       = "67 R Actuator Novram      ";
const STR    FT68Str[]       = "68 W AES FlowValue        ";
const STR    FT69Str[]       = "69 W AES PressureValue    ";
const STR    FT70Str[]       = "70 W Actuator Novram     ";
const STR    LastStr[]       = "\r\n\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r";
const STR    CrStr[]         = "\r";

const STR  * HelpStr[] = {FTHelp0Str, FTHelp1Str, FTHelp2Str, FTHelp3Str,
                          FT00Str, FT01Str, FT02Str, LastStr,
                          FT03Str, FT04Str, FT05Str, LastStr,
                          FT06Str, FT07Str, FT08Str, LastStr,
                          FT09Str, FT10Str, FT11Str, LastStr,
                          FT12Str, FT13Str, FT14Str, LastStr,
                          FT15Str, FT16Str, FT17Str, LastStr,
                          FT18Str, FT19Str, FT20Str, LastStr,
                          FT21Str, FT22Str, FT23Str, LastStr,
                          FT24Str, FT25Str, FT26Str, LastStr,
                          FT27Str, FT28Str, FT29Str, LastStr,
                          FT30Str, FT31Str, FT32Str, LastStr,
                          FT33Str, FT34Str, FT35Str, LastStr,
                          FT36Str, FT37Str, FT38Str, LastStr,
                          FT39Str, FT40Str, FT41Str, LastStr,
                          FT42Str, FT43Str, FT44Str, LastStr,
                          FT45Str, FT46Str, FT47Str, LastStr,
                          FT48Str, FT49Str, FT50Str, LastStr,
                          FT51Str, FT52Str, FT53Str, LastStr,
                          FT54Str, FT55Str, FT56Str, LastStr,
                          FT57Str, FT58Str, FT59Str, LastStr,
                          FT60Str, FT61Str, FT62Str, LastStr,
                          FT63Str, FT64Str, FT65Str, LastStr,
                          FT66Str, FT67Str, FT68Str, LastStr,
                          FT69Str, FT70Str, NULL };
                          
/*-------------------------------------------------------------------------*/                          
/*                                                                         */
/*  Lookup Tables.  The "hardware" method of computing CRCs involves bit   */
/*  manipulations, which is very inefficient for a software computation.   */
/*  Instead of computing the CRC bit-by-bit, a 256-element lookup table    */
/*  can be used to perform the equivalent of 8 bit operations at a time.   */
/*  (This is described in "Byte-wise CRC Calculations" in IEEE Micro,      */
/*  June 1983, pp. 40-50.)  For a CRC-16, the lookup table consists of 256 */
/*  2-byte WORDs (see below, or the CRC16.PAS unit for the actual table,   */
/*  or the CRCTable program for computation of the lookup table for the    */
/*  x16 + x15 + x2 + 1 generator polynomial):                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/                          

const UINT16 CRCTable[256] = 
 {0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241, 0xC601, 0x06C0,
  0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440, 0xCC01, 0x0CC0, 0x0D80, 0xCD41,
  0x0F00, 0xCFC1, 0xCE81, 0x0E40, 0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0,
  0x0880, 0xC841, 0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41, 0x1400, 0xD4C1,
  0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641, 0xD201, 0x12C0, 0x1380, 0xD341,
  0x1100, 0xD1C1, 0xD081, 0x1040, 0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1,
  0xF281, 0x3240, 0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41, 0xFA01, 0x3AC0,
  0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840, 0x2800, 0xE8C1, 0xE981, 0x2940,
  0xEB01, 0x2BC0, 0x2A80, 0xEA41, 0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1,
  0xEC81, 0x2C40, 0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041, 0xA001, 0x60C0,
  0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240, 0x6600, 0xA6C1, 0xA781, 0x6740,
  0xA501, 0x65C0, 0x6480, 0xA441, 0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0,
  0x6E80, 0xAE41, 0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41, 0xBE01, 0x7EC0,
  0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40, 0xB401, 0x74C0, 0x7580, 0xB541,
  0x7700, 0xB7C1, 0xB681, 0x7640, 0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0,
  0x7080, 0xB041, 0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440, 0x9C01, 0x5CC0,
  0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40, 0x5A00, 0x9AC1, 0x9B81, 0x5B40,
  0x9901, 0x59C0, 0x5880, 0x9841, 0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1,
  0x8A81, 0x4A40, 0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641, 0x8201, 0x42C0,
  0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040};


typedef struct framaddress {
   UINT8   *Start;
   UINT32  Size;
} FRAMADDRESS;

#define NUM_FRAM_SEGMENTS  16

const FRAMADDRESS FRAMAddr[NUM_FRAM_SEGMENTS] = {
/* Starting Address           Number of Bytes                        Segment use       */
/* -------------------------- ---------------                        ----------------- */
  {(UINT8*)FRAM1200_START_ADDRESS,      FRAM1200_RES_SIZE,         },/* reserved              */
  {(UINT8*)FRAM1200_ALARM_START,        FRAM1200_ALARM_SIZE,        },/* buc menu alarms   */
  {(UINT8*)FRAM1200_DUPSLOCK_START,     FRAM1200_DUPSLOCK_SIZE,     },/* DUPS lock status  */ 
  {(UINT8*)FRAM1200_UNUSED_START,       FRAM1200_UNUSED_SIZE,       },/* unused 			*/
  {(UINT8*)FRAM1200_UNUSED_START,       FRAM1200_UNUSED_SIZE,      },/*  unused 			*/
  {(UINT8*)FRAM1200_HORNSCAN_START,     FRAM1200_HORNSCAN_SIZE,     },/* Horn scan         */
  {(UINT8*)FRAM1200_DUPSBACKUP_START,   FRAM1200_DUPSBACKUP_SIZE,   },/* Dups backup       */
  {(UINT8*)FRAM1200_BUCMENU_START,      FRAM1200_BUCMENU_SIZE,      },/* BUC menu          */
  {(UINT8*)FRAM1200_DEPOT_START,        FRAM1200_DEPOT_SIZE,        },/* Depot flags       */
  {(UINT8*)FRAM1200_UNUSED_START,	   FRAM1200_UNUSED_SIZE,		  },/* unused  			 */
  {(UINT8*)FRAM1200_UNUSED_START,       FRAM1200_UNUSED_SIZE,       },/* unused            */
  {(UINT8*)FRAM1200_CONFIG_START,       FRAM1200_CONFIG_SIZE,       },/* System config     */
  {(UINT8*)FRAM1200_PRESET_START,       FRAM1200_PRESET_SIZE,       },/* Presets           */
  {(UINT8*)FRAM1200_HORNGRAPH_START,    FRAM1200_HORNGRAPH_SIZE,    },/* Horn scan graph   */
  {(UINT8*)FRAM1200_NOTASSIGNED_START,  FRAM1200_NOTASSIGNED_SIZE,  },/* unused            */
  {(UINT8*)FRAM1200_HISTORY_START,      FRAM1200_HISTORY_SIZE,      },/* Weld history      */
};


/**---------------------------------EXTERNAL AND GLOBAL DATA---------------------------**/

extern UINT32 CurrentAmpIn;
extern SINT32 CurrentFreqIn;
extern UINT32 CurrentPowerIn;        
extern UINT32 CurrentMemIn;
extern SINT32 CurrentFreqIn;
extern UINT16 ExtAmp;
extern SINT16 ExtFreqOffset;
extern UINT16 TenVoltRef;
extern UINT8  PortRegisterA;                                                        // U67
extern UINT8  PortRegisterB;                                                        // U79
extern UINT8  PortRegisterC;                                                        // U67
extern struct act_nvr NVR;
extern UINT16 CRC(UINT8 *, UINT32);
extern RTCTime RTCMenu;
extern UINT16 ADPressure, ADForce;
extern DUPS_INFO DUPS_Info;
extern DAC * PsDac;
extern UINT16 TestAdPressure;
extern UINT16 TestAdForce;
void ReadMACAddressFromEEPRom(UINT8 * macPtr);

/**----------------------------------- Prototypes -------------------------------------**/

void DoPSNovramCRC(void);
void DoActNovramCRC(void);
void DoFRAMCRC(void);
void DoFlashCRC(void);
void DisableBeepers(void);
void EnableBeepers(void);
void SetTime(void);
void SetDate(void);
void DumpCalibrationData(void);
void DumpAllCalibrationData(void);
void ReadMemory(void);
void WriteMemory(void);
void CheckDUPS(void);
void VGADoColdStart(void);
//void HdwInit(void);
void START(void);
void SetSBCReadyFlag(void);
void SetSpringRateMicro(void);
void SetSpringRateMicroFT(UINT8);
void GetLinearEncoder(void);
void GetRTCData(void);
void GetMacAddress(void);
void SetDACChannel(void);
void GetActPressurAndForce(void);
void ReadActNovramAddress(void);
void SetAESFlowValue(void);
void SetAESPressureValue(void);
void WriteToActNovramAddress(void);

/*----------------------------------------------------------------------------------*/
/* This structure contains elements to fill up the table which hold the parameters  */
/* for all inputs, outputs and functions to be passed through the serial port.      */
/*----------------------------------------------------------------------------------*/

typedef enum CommandType{                                          /* Enum for testcommand structure                            */
   READ,                                                   /* Read variable or I/O port                                 */
   FUNC,                                                   /* Call a function                                           */
   DISAB                                                   /* Command not implemented yet                               */
   }COMMANDTYPE;

typedef  struct testcommands {
   COMMANDTYPE Command ;                              /* From the enum command type defined above.                 */
   void             *Variable;
   void (*Function)(void);                                 /* Pointer to function to call on normal exit                */
  } TESTCOMMAND; 


   
const TESTCOMMAND Inputs[MAXCASE] = {
/* -Command--   Variable         Function                  */
/* #     Type   Pointer          Pointer                   */
/*      ------- ---------------- ---------------           */

/* Printer Interface */
/* 0*/ {DISAB,   NULL,   		  NULL,                  },/* Reads printer status lines (ACKNLG,BUSY,SELECT,PE,ERROR)  */
/* 1*/ {DISAB,   NULL,            NULL,       			 },/* Writes one byte to printer interface(J40 PDATA1 to PDATA8)*/
/* 2*/ {DISAB,   NULL,            NULL,    				 },/* Writes to printer interface (J40 INIT,STROBE)             */
/* 3*/ {FUNC,   NULL,            ReadKeypad,             },/* Reads the Keypad and writes the data byte to the RS232    */

/* A to D Converter */
/* 4*/ {READ,   &CurrentAmpIn,   Read32,                 },/* Reads the A to D channel VIN1 (AMPLITUDE)                 */
/* 5*/ {READ,   &CurrentPowerIn, Read32,                 },/* Reads the A to D channel VIN2 (POWER)                     */
/* 6*/ {READ,   &CurrentMemIn,   Read32,                 },/* Reads the A to D channel VIN3 (MEMORY)                    */
/* 7*/ {READ,   &CurrentFreqIn,  Read32,                 },/* Reads the A to D channel VIN4 (FREQUENCY)                 */
/* 8*/ {READ,   &TenVoltRef,     Read16,                 },/* Reads the A to D channel VIN5 (10V REF)                   */
/* 9*/ {READ,   &ExtAmp,         Read16,                 },/* Reads the A to D channel VIN6 (EXTERNAL AMPLITUDE)        */
/*10*/ {READ,   &ExtFreqOffset,  Read16,                 },/* Reads the A to D channel VIN7 (EXTERNAL FREQUENCY)        */
/*11*/ {DISAB,  NULL,            NULL,                   },/* Reads the A to D channel VIN8 (GROUND)                    */

/* PS NOVRAM */
/*12*/ {FUNC,   NULL,            MyReadNVR,              },/* Reads the power supply NOVRAM                             */
/*13*/ {FUNC,   NULL,            EraseNVR,               },/* Erases the power suppy NOVRAM                             */ 

/* FRAM */
/*14*/ {FUNC,   NULL,            TestFram,            },/* Tests the FRAM                                             */
/*15*/ {FUNC,   NULL,            ClearOutFram,        },/* Clear the FRAM                                             */
/*16*/ {FUNC,   NULL,            InitializeFRAM,          },/* Initialize the FRAM                                        */

/* BEEPER */
/*17*/ {FUNC,   NULL,            TurnOnBeep,             },/* Turns on the beeper                                       */
/*18*/ {FUNC,   NULL,            TurnOffBeeper,          },/* Turns off the beeper                                      */

/* D to A Converter */
/*19*/ {FUNC,   NULL,            DiagAmplitude,          },/* Write data to VOUTA (amplitude)                           */
/*20*/ {FUNC,   NULL,            DiagFreqOffset,         },/* Write data to VOUTB (freq offset)                         */

/* Digital Pot */
/*21*/ {FUNC,   NULL,            DiagDigTune,             },/* Write data to the digital pot controller chip             */

/* U79 Ports */
/*22*/ {FUNC,   NULL,            ReadPortA,              },/* Reads U79 Port A                                          */
/*23*/ {FUNC,   NULL,            WritePortB,             },/* Write one byte to U79 port B                              */
/*24*/ {FUNC,   NULL,            ReadPortC,              },/* Reads U79 Port C                                          */

/* U67 ports */
/*25*/ {FUNC,   NULL,            WritePortA,             },/* Write one byte to U67 port A Control signals              */
/*26*/ {FUNC,   NULL,            ReadPortB,              },/* Reads U67 Port B                                          */
/*27*/ {FUNC,   NULL,            WritePortC,             },/* Write one byte to U67 port C control signals              */

/* DUPS Serial link */
/*28*/ {FUNC,   NULL,            StartDUPS,              },/* Function to write to DUPS serial port then read back info */

/* TPU */
/*29*/ {DISAB,  NULL,            NULL,                   },/* Read                                                      */
/*30*/ {DISAB,  NULL,            NULL,               	 },/* Write                                                     */

/* VF Display */
/*31*/ {DISAB,   NULL,            NULL,            		 },       /* Write message to VF display                               */
/*32*/ {DISAB,   NULL,            NULL,          		 },/* Clear VF display                                          */
/*33*/ {DISAB,   NULL,            NULL,           		 },        /* Write Full display                                        */

/* SPI Bus */
/*34*/ {DISAB,  NULL,            NULL,                   },/* Func                                                      */

/* Actuator Interface */
/*35*/ {DISAB,  NULL,            NULL,                   },/* Func                                                      */
/*36*/ {DISAB,  NULL,            NULL,                   },/* Func                                                      */
/*37*/ {DISAB,  NULL,            NULL,                   },/* Write                                                     */

/* Bargraph */
/*38*/ {FUNC,   NULL,            WriteLeds,              },/* Write to leds                                             */
/*39*/ {FUNC,   NULL,            WriteBargraph,          },/* Write to bargraph                                         */

/* Misc */
/*40*/ {FUNC,   NULL,            DiagReady,              },/* Make system ready / not ready                             */
/*41*/ {FUNC,   NULL,            ShutOffFT,              },/* Shut off the factory test commands                        */
/*42*/ {FUNC,   NULL,            RestoreUserIO,          },/* Restore the User I/O selections back to factory default   */

/* CRC checks */
/*43*/ {FUNC,   NULL,            DoPSNovramCRC,          },/* Do power supply novram CRC check                          */
/*44*/ {FUNC,   NULL,            DoActNovramCRC,         },/* Do actuator novram CRC check                              */
/*45*/ {FUNC,   NULL,            DoFRAMCRC,               },/* Do FRAM CRC check in one of 16 blocks                      */
/*46*/ {FUNC,   NULL,            DoFlashCRC,             },/* Do CRC check over entire range of program flash           */

/* Misc */
/*47*/ {DISAB,  NULL,            NULL,                   },/* Execute a function from flash                             */
/*48*/ {FUNC,   NULL,            DisableBeepers,         },/* Disable all beepers in the system configuration           */
/*49*/ {FUNC,   NULL,            EnableBeepers,          },/* Enable all beepers in the system configuration            */
/*50*/ {FUNC,   NULL,            DumpAllCalibrationData, },/* Display calibration data                                  */
/*51*/ {DISAB,  NULL,            NULL,                   },/* Remove VGA                                               */
/*52*/ {FUNC,   NULL,            BuildDefaultSpringRate, },/* Actuator cold start                                       */
/*53*/ {FUNC,   NULL,            VGADoColdStart,         },/* Cold start                                                */
/*54*/ {FUNC,   NULL,            ColdStartPlus,          },/* Cold start plus (effectively configuration or checksum)   */

/* Real time clock */
/*55*/ {FUNC,   NULL,            SetTime,                },/* Set real time clock time                                  */
/*56*/ {FUNC,   NULL,            SetDate,                },/* Set real time clock date                                  */

/* Memory access   */
/*57*/ {FUNC,   NULL,            ReadMemory,             },/* Read 4 bytes of memory, FRAM or flash                      */
/*58*/ {FUNC,   NULL,            WriteMemory,            },/* Write up to 4 bytes of memory or FRAM                      */
/*59*/ {FUNC,   NULL,            START,                  },/* Resets software, by restarting the 332 code    			*/
/*60*/ {FUNC,   NULL,            SetSBCReadyFlag,        },/* Forces the SBCReadyFlag to be set because of FT 59		*/
/*61*/ {FUNC,   NULL,            SetSpringRateMicro,     },/* Sets the Micro leaving home force to passed value 		*/

/* Linear Encoder  */
/*62*/ {FUNC,   NULL,            GetLinearEncoder,       },/* Get the current value of linear encoder */

/* test RTC  */
/*63*/ {FUNC,   NULL,            GetRTCData,       },/* Get the current RTC data */

/* Read MacAddr  */
/*64*/ {FUNC,   NULL,            GetMacAddress,       },/* Get the Mac Addrss */

/* set DAC channel  */
/*65*/ {FUNC,   NULL,            SetDACChannel,       },/* Set value to PS dac channel */

/* Get Act presure and force  */
/*66*/ {FUNC,   NULL,            GetActPressurAndForce,       },/* Read act SPI signals */

/* reas act novram address  */
/*67*/ {FUNC,   NULL,            ReadActNovramAddress,       },/* Read act Novram address */

/* set aes flow value  */
/*68*/ {FUNC,   NULL,            SetAESFlowValue,       },/*Set flow value  */

/* set aes pressure value  */
/*69*/ {FUNC,   NULL,            SetAESPressureValue,       },/*Set pressure value  */

/* set aes pressure value  */
/*70*/ {FUNC,   NULL,           WriteToActNovramAddress,       }/*Write on act novram */
};


/**----------------------------CODE------------------------------------------**/



void DiagnosticInput(UINT8 ByteReceived, BOOLEAN EchoChar)
/********************************************************************************/
/*                                                                              */
/*  This function is called when a serial character is received and OnboardDiag */
/*  == TRUE.  This allows this function to intercept the characters and use     */
/*  them as input for the onboard diagnostics.  The characters will be placed   */
/*  in a local buffer where DiagnosticsCmd() can deal with them.  All successive*/
/*  spaces will be reduced to one space to save buffer space.  If the end of    */
/*  the buffer is reached all future characters will be thrown away.            */
/*                                                                              */
/*  Exit Condition:  Inptr - pointing to last character entered into buffer     */
/*                                                                              */
/********************************************************************************/
{
   if (DisplayHelpFlag == FALSE) {
      if (ByteReceived == ' ') {
         if (DiagBuffer[Inptr] != ' ') {                                                      /* Not another space so save it */
            if (Inptr < (DIAG_BUFFER_SIZE - 1)) Inptr++;
            DiagBuffer[Inptr] = ByteReceived;
            if(EchoChar)
            	SerialMqueueValue = SerialMessageQueue((UINT8*)&DiagBuffer[Inptr],(UINT16) 1);    /* Echo chars */
         }
      }
      else if (ByteReceived == ESC) {
         SerialMqueueValue = SerialMessageQueue((UINT8*)DiagPrompt, sizeof(DiagPrompt));
         for (Inptr = 0; Inptr < DIAG_BUFFER_SIZE; Inptr++) {
            DiagBuffer[Inptr] = 0;
         }
         Inptr = -1;
      }
      else {
         if (ByteReceived == BS) {
            DiagBuffer[Inptr] = ByteReceived;
            SerialMqueueValue = SerialMessageQueue((UINT8*)&DiagBuffer[Inptr],(UINT16) 1);    /* Echo BS    */
            DiagBuffer[Inptr] = ' ';
            SerialMqueueValue = SerialMessageQueue((UINT8*)&DiagBuffer[Inptr],(UINT16) 1);    /* Echo space */
            DiagBuffer[Inptr] = ByteReceived;
            SerialMqueueValue = SerialMessageQueue((UINT8*)&DiagBuffer[Inptr],(UINT16) 3);    /* Echo BS    */
            Inptr--;
         }
         else if (Inptr < (DIAG_BUFFER_SIZE - 1)) {
            Inptr++;
            DiagBuffer[Inptr] = ByteReceived;
            if ((DiagBuffer[Inptr] != '\r') && (DiagBuffer[Inptr] != '\n') )                  /* If not CR or LF */
            {
            	if(EchoChar)
            		SerialMqueueValue = SerialMessageQueue((UINT8*)&DiagBuffer[Inptr],(UINT16) 1); /* Echo chars */
            }
            else
               DiagnosticsCmd();                                                              /* It is now a complete command so deal with it    */
         }
         else {
            DiagBuffer[Inptr] = CR;
            DiagnosticsCmd();                                                                 /* Buffer full, try to execute what we have so far */
         }   
      }
   }
   else Inptr++;
}



void DiagnosticsCmd(void)
/*****************************************************************************/
/* Description:-                                                             */
/*   This function scans the characters received through the serial port and */
/*   parses them to determine which command has been requested.              */
/*                                                                           */
/*   This function will be called from the DiagnosticInput function above.   */
/*   If a complete command is not received yet, then this function will      */
/*   return without doing anything.  If the command is complete, it will be  */
/*   executed and if a return value is needed that will be taken care of.    */
/*                                                                           */
/*                                                                           */
/*   Rules:   1) Extra spaces will be ignored (removed by DiagnosticInput)   */
/*            2) Syntax is: FT xx yy                                         */
/*                      where xx is between 00 and 99                        */
/*                            yy is required for some commands and is 1 byte */
/*            3) If yy is not required but is supplied, it will be ignored   */
/*            4) If yy is required and not supplied, the message "Where's    */
/*               the Data" will be sent to the terminal.                     */
/*            5) There must be a space between FT and xx and yy.             */
/*            6) When the command is complete "2000 >" will be echoed to the */
/*               terminal.                                                   */
/*            7) Input string must end with carriage return or line feed     */
/*               (can be both)                                               */
/*                                                                           */
/*****************************************************************************/
{
   BOOLEAN CRFlag = FALSE;                                                 /* Carriage Return / Line Feed Flag */
   BOOLEAN CommandOkay = TRUE;                                             /* Assume okay until otherwise told */
   signed char   i = Inptr;
   STR     InputString[6];
   UINT8   Outptr = 0;                                                     /* Used to remove data from DiagBuffer */
   
   if (Inptr != 0) {                                                       /* Look to see if a CR or LF has been received */
      while (i >= 0) {
         if ((DiagBuffer[i] == CR) || (DiagBuffer[i] == LF) ) {
            CRFlag = TRUE;                                                 /* End of line so okay to process */
         }
         i--;
      }
   }

   if (CRFlag == TRUE) {
      ExtraDataFlag = TRUE;

      /* Now check to see if command starts with 'FT' or 'HE' */
      if ((DiagBuffer[Outptr] == 'H') && (DiagBuffer[Outptr+1] == 'E') ) {
         DisplayHelpFlag = TRUE;
         IOTestFlag = TRUE;
      }   
      else {
         if (DiagBuffer[Outptr++] != 'F') CommandOkay = FALSE;
         if (DiagBuffer[Outptr++] != 'T') CommandOkay = FALSE;

                                                                           /* Next skip any spaces between FT and command number */

         while (DiagBuffer[Outptr] == ' ') {
            Outptr++;
         }
         
                                                                           /* Now work on getting the command number (might only be 1 character) */

         InputString[0] = DiagBuffer[Outptr++];
         if ((DiagBuffer[Outptr] != CR) && (DiagBuffer[Outptr] != LF) && (DiagBuffer[Outptr] != ' ') ) {
            InputString[1] = DiagBuffer[Outptr++];
            InputString[2] = '\r';
         }
         else {
            InputString[1] = '\r';
         }
         CmdNumber= Numin(10, InputString);
         if (CmdNumber >= MAXCASE) CommandOkay = FALSE;
    
                                                                           /* Next skip any spaces between command number and extra data */

         while (DiagBuffer[Outptr] == ' ') {
            Outptr++;
         }

                                                                           /* Now work on getting any extra data */

         if ((DiagBuffer[Outptr] != CR) && (DiagBuffer[Outptr] != LF) ) {
            SavedOutptr = Outptr;
            InputString[0] = DiagBuffer[Outptr++];
            if ((DiagBuffer[Outptr] != CR) && (DiagBuffer[Outptr] != LF) ) {
               InputString[1] = DiagBuffer[Outptr++];
               InputString[2] = '\r';
            }
            else {
               InputString[1] = '\r';
            }   
            ExtraData = Numin(16, InputString);
         }
         else ExtraDataFlag = FALSE;                                       /* No extra data */
                                                                           /* Alright then, if the command string is correct then execute it */
         if (CommandOkay == TRUE) {
            switch(Inputs[CmdNumber].Command) {
               case READ:
                  if (Inputs[CmdNumber].Function != NULL)  Inputs[CmdNumber].Function();
                  DiagBuffer[0] = ' ';
                  DiagBuffer[1] = '=';
                  DiagBuffer[2] = ' ';
                  Numout(GlobalValue, (UINT8)16, '0', &DiagBuffer[3], (UINT8)4) ;
                  SerialMqueueValue = SerialMessageQueue((UINT8*)DiagBuffer,(UINT16) 7);
                  break;
                
               case FUNC: 
                  if (Inputs[CmdNumber].Function != NULL)  Inputs[CmdNumber].Function();
                  break;
                  
               case DISAB:
                  SerialMqueueValue = SerialMessageQueue((UINT8*)DisabledStr, sizeof(DisabledStr));
                  break;
            }
         }      
         else {                                                            /* Command syntax not okay, yell at the clown */
            SerialMqueueValue = SerialMessageQueue((UINT8*)DiagSyntaxError, sizeof(DiagSyntaxError));
         }

/*  Output a new prompt */
         SerialMqueueValue = SerialMessageQueue((UINT8*)DiagPrompt, sizeof(DiagPrompt));
        /*  Before returning make sure buffer is cleared to all zeros and Inptr is set to -1 */
      }
      for (Inptr = 0; Inptr < DIAG_BUFFER_SIZE; Inptr++) {//coverity fix
         DiagBuffer[Inptr] = 0;
      }
      if (DisplayHelpFlag == TRUE) Inptr = 0;
      else Inptr = -1;
   }
}



void Read32(void)
/********************************************************************************/
/*                                                                              */
/*   This function reads a 32 bit value and type casts it into a 32 bit value   */
/*   in GlobalValue for conversion using Numout().                              */
/*                                                                              */
/********************************************************************************/
{
   GlobalValue = *(UINT32*)Inputs[CmdNumber].Variable;                     /* Use global variable */
}



void Read16(void)
/********************************************************************************/
/*                                                                              */
/*   This function reads a 16 bit value and type casts it into a 32 bit value   */
/*   in GlobalValue for conversion using Numout().                              */
/*                                                                              */
/********************************************************************************/
{
   GlobalValue = (UINT32) *(UINT16*)Inputs[CmdNumber].Variable;            /* Use global variable */
}



void Read8(void)
/********************************************************************************/
/*                                                                              */
/*   This function reads a 8 bit value and type casts it into a 32 bit value in */
/*   GlobalValue for conversion using Numout().                                 */
/*                                                                              */
/********************************************************************************/
{
   GlobalValue = (UINT32) *(UINT8*)Inputs[CmdNumber].Variable;             /* Use global variable */
}



UINT16 CRC(UINT8 *Ptr, UINT32 Length)
/*****************************************************************************/
/*                                                                           */
/*   The following is a little cryptic (but executes very quickly).          */
/*   The algorithm is as follows:                                            */
/*   1. exclusive-or the input byte with the low-order byte of               */
/*      the CRC register to get an INDEX                                     */
/*   2. shift the CRC register eight bits to the right                       */
/*   3. exclusive-or the CRC register with the contents of                   */
/*      Table[INDEX]                                                         */
/*   4. repeat steps 1 through 3 for all bytes}                              */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 CRCRegister = 0;
   UINT8  Index;

   while (Length-- >0) {
      Index = (UINT8)((CRCRegister ^*Ptr++) & 0xff);
      CRCRegister = CRCRegister >> 8;
      CRCRegister = CRCRegister ^ CRCTable[Index];
   }   
   return (CRCRegister);
}



void DoPSNovramCRC(void)
/****************************************************************************/
/*                                                                          */
/*  This function will read the power supply novram and then do a CRC on    */
/*  the 16 locations read.                                                  */
/*                                                                          */
/****************************************************************************/
{
   UINT16 CRCReturned;
   STR    Port[8];
   
   ReCallPSNovram();                                                       /* Go and read the novram */
   CRCReturned = CRC((UINT8*)&PSNvRamData, (UINT32)sizeof(PSNvRamData));
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)CRCReturned, 16, '0', &Port[3], 4);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 7);
}



void DoActNovramCRC(void)
/****************************************************************************/
/*                                                                          */
/*  This function will read the actuator novram and then do a CRC on the    */
/*  256 locations read.                                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT16 CRCReturned;
   STR    Port[8];
   
   ActPowerUp();                                                           /* Go and read the novram */
   CRCReturned = CRC((UINT8*)&NVR, (UINT32)sizeof(NVR));
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)CRCReturned, 16, '0', &Port[3], 4);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 7);
}



void DoFRAMCRC(void)
/****************************************************************************/
/*                                                                          */
/*  This function will do a CRC on 1 of 16 checks of the FRAM.  The value    */
/*  ExtraData will define which of the 16 to do.                            */
/*                                                                          */
/****************************************************************************/
{
   UINT16 CRCReturned;
   STR    Port[8];


   if (ExtraData > NUM_FRAM_SEGMENTS)
	  ExtraData = 0;
   else if(ExtraData > 0)
	  ExtraData -= 1;
   CRCReturned = CRC((UINT8*)FRAMAddr[ExtraData].Start, FRAMAddr[ExtraData].Size);
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)CRCReturned, 16, '0', &Port[3], 4);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 7);
}



void DoFlashCRC(void)
/****************************************************************************/
/*                                                                          */
/*  This function will do a CRC over the entire range of flash.  This may   */
/*  take a while.                                                           */
/*                                                                          */
/****************************************************************************/
{
   UINT16 CRCReturned;
   STR    Port[8];
   
   if (ExtraData > NUM_FRAM_SEGMENTS) ExtraData = 0;
   else ExtraData -= 1;
   CRCReturned = CRC((UINT8*)0x00000000, 0x0fffff);
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)CRCReturned, 16, '0', &Port[3], 4);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 7);
}



void MyReadNVR(void)
/******************************************************************************/
/* Description:                                                               */
/*    This function will call ReCallPSNovram() which reads the information    */
/*    from the Novram and puts it into global variables.  These global        */
/*    variables are contained in the array PSNvRamData.  They will be sent    */
/*    to the serial port in the following format:                             */
/*                                                                            */
/*        Control Level = xxxx                                                */
/*        Wattage = xxxx                                                      */
/*        Frequency = xxxx                                                    */
/*        Lifetime Counter = xxxx                                             */
/*        Serial Number = xx xx xx xx xx xx xx xx xx xx xx xx xx xx           */
/*                                                                            */
/******************************************************************************/
{
   UINT16 x;
   STR Converted[8]; 
   UINT32 Conversion;                                                      /*variable converts output of ReadNVR by sending it to Numout*/
   
   ReCallPSNovram();                                                       /* Go and read the novram */

   memset(Converted, 0, sizeof(Converted));
/* Control Level */

   SerialMqueueValue = SerialMessageQueue((UINT8*)ControlLevelStr, sizeof(ControlLevelStr));
   Conversion = PSNvRamData.ControlLevel;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   
/* Wattage */

   SerialMqueueValue = SerialMessageQueue((UINT8*)WattStr, sizeof(WattStr));
   Conversion = PSNvRamData.PSWatts;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   
/* Frequency */

   SerialMqueueValue = SerialMessageQueue((UINT8*)FrequencyStr, sizeof(FrequencyStr));
   Conversion = PSNvRamData.PSFrequency;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   
/* Lifetime Counter */

   SerialMqueueValue = SerialMessageQueue((UINT8*)LifetimeStr, sizeof(LifetimeStr));
   Conversion = PSNvRamData.PSLifeTime;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   
/* Serial Number */

   SerialMqueueValue = SerialMessageQueue((UINT8*)SerialNumberStr, sizeof(SerialNumberStr));
   for (x=0; x<13; x++) {
      Conversion = PSNvRamData.PSSerialNum[x];
      Numout(Conversion, 16, '0', &Converted[0], 2);
      Converted[2] = ' ';
      SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);
   }
   Converted[0] = CR;
   Converted[1] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 2);
}   


 
void EraseNVR(void)
/*******************************************************************************/
/* Description:                                                                */
/*    This function will completely erase the power supply Novram, setting all */
/*    locations to ExtraData if entered otherwise to 0x0ffff.                  */
/*                                                                             */
/*******************************************************************************/
{
   UINT32 WriteData = 0xffffffff;
   if (ExtraDataFlag == TRUE) {
	   WriteData = ExtraData;
	   WriteData = WriteData | (WriteData  << 8) | (WriteData  << 16) | (WriteData  << 24);
   }

   memset(&PSNvRamData, WriteData, sizeof(PSNvRamData));
}   


 
void TestFram(void) 
/********************************************************************************/
/* Description:                                                                 */
/*    This function will perform a non-destrutive memory test on the battery-   */
/*    backed ram.  A read will be performed to save the contents, then a series */
/*    of write/read patterns and finally restore the original contents.         */
/*                                                                              */
/********************************************************************************/
{
   UINT8  *FramPtr = (UINT8 *)FRAM1200_SYSTEM_START;                      /* Points to FRAM for write */
   UINT8  SaveFRAM;                                                         /* Save original contents  */
   volatile  UINT8  ReadFRAM;                                               /* Read value for testing  */
   UINT8  WriteFRAM;                                                        /* Write value for testing */
   UINT16 FailFlag = FALSE;                                                /* Assume all will be okay */
   SINT16 Counter = (FRAM1200_SIZE);                        /* Number of bytes to check*/
   
   while (Counter-- > 0) {
      SaveFRAM = *FramPtr;                                               /* Save original value     */

/* Write and test for 0's */
      WriteFRAM = 0;
      *FramPtr = WriteFRAM;
      ReadFRAM = *FramPtr;
      if (ReadFRAM != WriteFRAM) FailFlag = TRUE;
      
/* Write and test for 1's */
      WriteFRAM = 1;
      *FramPtr = WriteFRAM;
      ReadFRAM = *FramPtr;
      if (ReadFRAM != WriteFRAM) FailFlag = TRUE;
      
/* Write and test for values */
      WriteFRAM = (Counter % 256);
      *FramPtr = WriteFRAM;
      ReadFRAM = *FramPtr;
      if (ReadFRAM != WriteFRAM) FailFlag = TRUE;
      
      *FramPtr = SaveFRAM;                                               /* Restore original value  */
      FramPtr++;
   }   

   if (FailFlag == FALSE) {                                                /* Everything Passed       */
      SerialMqueueValue = SerialMessageQueue((UINT8*)FRAMPassedStr, sizeof(FRAMPassedStr));
   }
   else {                                                                  /* Something failed        */
      SerialMqueueValue = SerialMessageQueue((UINT8*)FRAMFailedStr, sizeof(FRAMFailedStr));
   }                                                                                                               
} 
 
 
 
void TurnOnBeep(void) 
/********************************************************************************/
/* Description-- Turn Beeper on                                                 */
/********************************************************************************/
{
	CPLD::thisPtr->SetBuzzer(true);
} 
 
 
 
void TurnOffBeep(void) 
/********************************************************************************/
/* Description-- Turn Beeper off                                                */
/********************************************************************************/
{
	CPLD::thisPtr->SetBuzzer(false);                                          /* Turn Beeper off       */
} 
 
 
 
void WritePrinterData(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write ExtraData to the printer data port.                */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      *(UINT8 *)WritePrtc = ExtraData;
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }

}



void WritePrinterControl(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write ExtraData to the printer data port.                */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      switch (ExtraData) {
         case 0:
            *(UINT8 *)WritePrtCntl = STROBELOW;
            break;
         case 1:
            *(UINT8 *)WritePrtCntl = STROBEHIGH;
            break;
         case 2:
            *(UINT8 *)WritePrtCntl = STROBELOW;
            *(UINT8 *)WritePrtCntl = 0x0B;                                 /*-- set INIT high --*/
            break;
         case 3:
            *(UINT8 *)WritePrtCntl = STROBEHIGH;
            *(UINT8 *)WritePrtCntl = 0x0B;                                 /*-- set INIT high --*/
         break;
         default:
            *(UINT8 *)WritePrtCntl = 0x0B;                                 /*-- set INIT high --*/
            break;
      }
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void WriteBargraph(void)
/********************************************************************************/
/*                                                                              */
/* This funtion will write the ExtraData to the bargraph.  The data should be   */
/* in the range of 0 to 100 percent.                                            */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      UpdateBarGraph(ExtraData);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void WritePortA(void)
/********************************************************************************/
/*                                                                              */
/*  Write the ExtraData to Port A global variable for U67.                      */
/*                                                                              */
/********************************************************************************/
{
	//indexes representing the bit number. Index value representing the
	//output to modify based on the value(ExtraData) coming from lab view software.
   int LabViewOutput[8] = {Act_Clear, Trig_Sw_Actv, 0, Reject, Suspect, PB_Release, Pwr_Off_Delay, TRSEnable};
   if (ExtraDataFlag == TRUE) {
	   PortRegisterA = ExtraData;
	    for(int i = 0; i < 8; i++){
	      if(LabViewOutput[i] > 0)
	    	  //Kludge to pass Lab view. Lab view assumes if it is writing 0 to active low signals.The output should
	    	  //actually be high and vice versa.
	    	  if((LabViewOutput[i] == Reject) || (LabViewOutput[i] == Suspect) || (LabViewOutput[i] == PB_Release)
	    			  || (LabViewOutput[i] == Act_Clear))
	    		  cpld->SetDout(LabViewOutput[i] , !((PortRegisterA >> i) & 1));
	    	  else
	    		  cpld->SetDout(LabViewOutput[i] , ((PortRegisterA >> i) & 1));
	    }
 	   //cpld->SetLatch(2, PortRegisterA);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void WritePortB(void)
/********************************************************************************/
/*                                                                              */
/*  Write the ExtraData to Port B global variable for U79.                      */
/*                                                                              */
/********************************************************************************/
{

	//indexes representing the bit number. Index value representing the
	//output to modify based on the value(ExtraData) coming from lab view software.
   int LabViewOutput[8] = {SEEK_OUT_SIG, RUN_OUT_SIG, OL_RESET_SIG, TEST_OUT_SIG, SV1, SV2, SV3, SV4};
   if (ExtraDataFlag == TRUE) {
      PortRegisterB = ExtraData;
      for(int i = 0; i < 8; i++){
    	  if(LabViewOutput[i] > 0)
    		  cpld->SetDout(LabViewOutput[i] , ((PortRegisterB >> i) & 1));
      }
      //cpld->SetLatch(2, PortRegisterB);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void WritePortC(void)
/********************************************************************************/
/*                                                                              */
/*  Write the ExtraData to Port C global variable for U67.                      */
/*                                                                              */
/********************************************************************************/
{
	//indexes representing the bit number. Index value representing the
	//output to modify based on the value(ExtraData) coming from lab view software.
   int LabViewOutput[8] = {Gen_Alarm, ReadySig, Weld_On, 0, J3_22, J3_8, J3_36, 0};
   if (ExtraDataFlag == TRUE) {
      PortRegisterC = ExtraData;
      for(int i = 0; i < 8; i++){
    	  if(LabViewOutput[i] > 0)
    		  cpld->SetDout(LabViewOutput[i] , ((PortRegisterC >> i) & 1));
      }
      //cpld->SetLatch(5, PortRegisterC);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void ReadPortA(void)
/********************************************************************************/
/*                                                                              */
/*  Reads Port A of U79 and sends value to serial port.                         */
/*                                                                              */
/********************************************************************************/
{
   STR   Port[8];
   INPUT_PORT_P0_UNION_TYPE PortValue;
   //Here read the value and make it compatible with lab view expectation
   //Below mask is based on Sunrise CPLD code Main.vhd rev 1.3 and Sunrise 913-242-1025R board
   UINT8 PortAInvertMask = 0x8F;
   PortValue.value = (cpld->GetBuffer(0) ^ PortAInvertMask);
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)PortValue.value, 16, '0', &Port[3], 2);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 5);
}



void ReadPortB(void)
/********************************************************************************/
/*                                                                              */
/*  Reads Port B of U67 and sends value to serial port.                         */
/*                                                                              */
/********************************************************************************/
{
   STR  Port[8];
   INPUT_PORT_P2_UNION_TYPE PortValue;
   //Here read the value and make it compatible with lab view expectation
   //Below mask is based on Sunrise CPLD code Main.vhd rev 1.3 and Sunrise 913-242-1025R board
   UINT8 PortBInvertMask = 0xFD;
   PortValue.value = (cpld->GetBuffer(2) ^ PortBInvertMask);
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)PortValue.value, 16, '0', &Port[3], 2);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 5);
}



void ReadPortC(void)
/********************************************************************************/
/*                                                                              */
/*  Reads Port C of U79 and sends value to serial port.                         */
/*                                                                              */
/********************************************************************************/
{
   STR  Port[8];
   INPUT_PORT_P1_UNION_TYPE PortValue;
   //Here read the value and make it compatible with lab view expectation
   //Below mask is based on Sunrise CPLD code Main.vhd rev 1.3 and Sunrise 913-242-1025R board
   UINT8 PortCInvertMask = 0xB9;
   PortValue.value = (cpld->GetBuffer(1) ^ PortCInvertMask);
   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)PortValue.value, 16, '0', &Port[3], 2);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 5);
}



void ReadKeypad(void)
/********************************************************************************/
/*                                                                              */
/*  This functions reads the keypad and returns the result in the serial port.  */
/*                                                                              */
/********************************************************************************/
{
   KEY_CODE_TYPE Key;
   STR           Port[8];

   Key = (KEY_CODE_TYPE)(cpld->GetBuffer(3) & 0x03);//return row1 and row0 status here

   Port[0] = ' ';
   Port[1] = '=';
   Port[2] = ' ';
   Numout((UINT32)Key, 16, '0', &Port[3], 2);
   SerialMqueueValue = SerialMessageQueue((UINT8*)Port, 5);
}



void DiagFreqOffset(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write the ExtraData out to the D/A converter for freq    */
/*  offset.                                                                     */
/*                                                                              */
/********************************************************************************/
{
   SetCurrentFreqOffset(ExtraData);
}

         

void DiagAmplitude(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write the ExtraData out to the D/A converter for amp-    */
/*  litude.                                                                     */
/*                                                                              */
/********************************************************************************/
{
   SetCurrentAmp(ExtraData);
}

         

void DiagDigTune(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write the ExtraData out to the digital pot.  If the      */
/*  value is zero the pot will be decremented and if the value is not zero the  */
/*  pot will be incremented.                                                    */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
     IoTestData(ExtraData);
     SetDigTune();
   }   
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void EraseVFScreen(void)
/********************************************************************************/
/*                                                                              */
/*  This function will clear the VF display and then set the cursor to position */
/*  1 on line 1 and make sure its invisible.                                    */
/*                                                                              */
/********************************************************************************/
{
}



void WriteLeds(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write to the leds using ExtraData as follows:            */
/*                                                                              */
/*         BIT0: Reset         BIT3: Right              0: turn led off         */
/*         BIT1: Up            BIT4: Left               1: turn led on          */
/*         BIT2: Down          BIT5: Zero percent                               */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      if (ExtraData & BIT0) UpdateLED(RESETLED, ON);
      else UpdateLED(RESETLED, OFF);

      if (ExtraData & BIT1) UpdateLED(UPLED, ON);
      else UpdateLED(UPLED, OFF);

      if (ExtraData & BIT2) UpdateLED(DOWNLED, ON);
      else UpdateLED(DOWNLED, OFF);

      if (ExtraData & BIT3) UpdateLED(RIGHTLED, ON);
      else UpdateLED(RIGHTLED, OFF);

      if (ExtraData & BIT4) UpdateLED(LEFTLED, ON);
      else UpdateLED(LEFTLED, OFF);

      if (ExtraData & BIT5) UpdateLED(ZEROPERCENTLED, ON);      /* This will get overwritten */
      else UpdateLED(ZEROPERCENTLED, OFF);                      /* if still in ready mode    */
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void ReadTPU(void)
/********************************************************************************/
/*                                                                              */
/*   This function will read the memstore and dig pot channels of the TPU.      */
/*                                                                              */
/********************************************************************************/
{
   ;
}



void WriteTPU(void)

{

}  



void DiagReady(void)
/********************************************************************************/
/*                                                                              */
/*  This function will make the system not ready when ExtraFlag is 1 by setting */
/*  DiagStopFlag.  All other values will set DiagStopFlag to FALSE.  This will  */
/*  make the system ready if NOTHING ELSE is also keeping it from ready.        */
/*                                                                              */
/********************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      if (ExtraData == TRUE) DiagStopFlag = TRUE;
      else DiagStopFlag = FALSE;
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void ShutOffFT(void)
/********************************************************************************/
/*                                                                              */
/*  This function will set the OnBoardDiag flag to FALSE, disabling the factory */
/*  test.   Serial commands will no longer be intercepted and will go back to   */
/*  the 'Host'.                                                                 */
/*                                                                              */
/********************************************************************************/
{
   OnboardDiag = FALSE;                                         /* Diagnostics disabled through the serial port */
}



void RestoreUserIO(void)
/********************************************************************************/
/*                                                                              */
/*  This function will restore the User I/O settings and custom actuator switch */
/*  logic back to the factory default.                                          */
/*                                                                              */
/********************************************************************************/
{
   SetUserIOToFactoryDefault();
}



void DisableBeepers(void)
/********************************************************************************/
/*                                                                              */
/*   Disable all beepers in system configuration menu.                          */
/*                                                                              */
/********************************************************************************/
{
   FRAM_STATUS_TYPE   FramCompletionStatus;
   
   CurrentSetup.BeeperTrigger = 0;
   CurrentSetup.BeeperError = 0;
   CurrentSetup.BeeperAlarm = 0;
   CurrentSetup.BeeperEstop = 0;
   FramCompletionStatus = FramAccess(FRAM_WRITE, CONFIG_SECTION, (UINT8 *)&CurrentSetup, (UINT32)FRAM1200_CONFIG_START, sizeof(CurrentSetup) );
}



void EnableBeepers(void)
/********************************************************************************/
/*                                                                              */
/*   Enable all beepers in system configuration menu.                           */
/*                                                                              */
/********************************************************************************/
{
   FRAM_STATUS_TYPE   FramCompletionStatus;
   
   CurrentSetup.BeeperTrigger = 1;
   CurrentSetup.BeeperError = 1;
   CurrentSetup.BeeperAlarm = 1;
   CurrentSetup.BeeperEstop = 1;
   FramCompletionStatus = FramAccess(FRAM_WRITE, CONFIG_SECTION, (UINT8 *)&CurrentSetup, (UINT32)FRAM1200_CONFIG_START, sizeof(CurrentSetup) );
}



void SetTime(void)
/********************************************************************************/
/*                                                                              */
/*  This command will set the time in 24-hour format using the ExtraData.       */
/*  Hours and minutes must be separated by ':' and be 2 digits each.  HH:MM.    */
/*  There will be no error checking.                                            */
/*                                                                              */
/********************************************************************************/
{
   UINT8  Count = 0, Index;
   STR    InputBuffer[10];
   UINT16 ExitFlag = FALSE;

   if (ExtraDataFlag == TRUE) {
      Index = SavedOutptr;
      while (ExitFlag == FALSE) {                 /* Get hours first */
         if (DiagBuffer[Index] != ':') {
            InputBuffer[Count] = DiagBuffer[Index];
            Index++;
            Count++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      RTClock::GetCurrentTime(&RTCMenu);//first get the current time so we dont garbage other values than
										 //hour and minute.
      RTCMenu.Hour = (SINT32) Numin(10, InputBuffer);   
        // RtcWrite(SECONDS, 0);                       /* Zero seconds while at it   */
                                                  /* This also starts the clock */
                                                  /* if not already running     */

      Count = 0;
      Index++;                                    /* Get past ':'    */
      ExitFlag = FALSE;
      while (ExitFlag == FALSE) {                 /* Get minutes now */
         if (DiagBuffer[Index] != CR) {
            InputBuffer[Count] = DiagBuffer[Index];
            Count++;
            Index++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      RTCMenu.Minute = (SINT32) Numin(10, InputBuffer);   
      RTClock::SetCurrentTime(&RTCMenu);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void SetDate(void)
/********************************************************************************/
/*                                                                              */
/*  This command will set the date using the ExtraData.  Month, date and year   */
/*  must be separated by "/" and each must be 2 digits each.  MM/DD/YY.         */
/*  There will be no error checking.                                            */
/*                                                                              */
/********************************************************************************/
{
   UINT8  Count = 0, Index;
   STR    InputBuffer[10];
   UINT16 ExitFlag = FALSE;

   if (ExtraDataFlag == TRUE) {
      Index = SavedOutptr;
      while (ExitFlag == FALSE) {                 /* Get month first */
         if (DiagBuffer[Index] != '/') {
            InputBuffer[Count] = DiagBuffer[Index];
            Index++;
            Count++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      RTCMenu.Century_Month = (SINT32) Numin(10, InputBuffer);

      Count = 0;
      Index++;                                    /* Get past '/'    */
      ExitFlag = FALSE;
      while (ExitFlag == FALSE) {                 /* Get date now */
         if (DiagBuffer[Index] != '/') {
            InputBuffer[Count] = DiagBuffer[Index];
            Count++;
            Index++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      RTCMenu.Day = (SINT32) Numin(10, InputBuffer);   

      Count = 0;
      Index++;                                    /* Get past '/'    */
      ExitFlag = FALSE;
      while (ExitFlag == FALSE) {                 /* Get year now */
         if (DiagBuffer[Index] != CR) {
            InputBuffer[Count] = DiagBuffer[Index];
            Count++;
            Index++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      RTCMenu.Years = (SINT32) Numin(10, InputBuffer);
      RTClock::SetCurrentTime(&RTCMenu);

   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void DumpCalibrationData(void)
/********************************************************************************/
/*                                                                              */
/*  This function will take the data in the global structure and format it in   */
/*  the following way:                                                          */
/*                                                                              */
/*  ---- Cal---- Date: MM/DD/YY                                                 */
/*  LC Table=xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx                  */
/*  Springrate slope=xxxx  Stroke length=x.xxxx"                                */
/*  System pressure=xxxx  Pressure table=xxxx yyyy                              */
/*  Home offset=xxxx                                                            */
/*                                                                              */
/********************************************************************************/
{
   UINT16 x;
   STR Converted[8]; 
   UINT32 Conversion;  /*variable converts output of ReadNVR by sending it to Numout*/
   memset(Converted, 0, sizeof(Converted));
/* Date */

   SerialMqueueValue = SerialMessageQueue((UINT8*)DateStr, sizeof(DateStr));
   Conversion = CalData.Date[0];                  /* Get month */
   Numout(Conversion, 10, ' ', &Converted[0], 2);
   Converted[2] = '/';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);
   
   Conversion = CalData.Date[1];                  /* Get date */
   Numout(Conversion, 10, '0', &Converted[0], 2);
   Converted[2] = '/';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);
   
   Conversion = CalData.Date[2];                  /* Get year */
   Numout(Conversion, 10, '0', &Converted[0], 2);
   Converted[2] = CR;
   Converted[3] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 4);
   
/* LC Table */

   SerialMqueueValue = SerialMessageQueue((UINT8*)LCTableStr, sizeof(LCTableStr));
   for (x=0; x<11; x++) {
      Conversion = CalData.Loadcell[x];
      Numout(Conversion, 16, '0', &Converted[0], 4);
      Converted[4] = ' ';
      SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   }
   Converted[0] = CR;
   Converted[1] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 2);
   
/* Springrate slope */

   SerialMqueueValue = SerialMessageQueue((UINT8*)SpringrateStr, sizeof(SpringrateStr));
   Conversion = CalData.Springrate;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = ' ';
   Converted[5] = ' ';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 6);
   
/* Stroke length */

   SerialMqueueValue = SerialMessageQueue((UINT8*)StrokeLengthStr, sizeof(StrokeLengthStr));
   Conversion = (CalData.Stroke / 10000);         /* Work on left of decimal */
   Numout(Conversion, 10, ' ', &Converted[0], 2);
   Converted[2] = '.';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);

   Conversion = (CalData.Stroke % 10000);         /* Work on right of decimal */
   Numout(Conversion, 10, '0', &Converted[0], 4);
   Converted[4] = '"';
   Converted[5] = CR;
   Converted[6] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 7);

/* System pressure */

   SerialMqueueValue = SerialMessageQueue((UINT8*)SystemPressureStr, sizeof(SystemPressureStr));
   Conversion = CalData.SystemPressure;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = ' ';
   Converted[5] = ' ';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 6);
   
/* Pressure table */

   SerialMqueueValue = SerialMessageQueue((UINT8*)PressureTableStr, sizeof(PressureTableStr));
   for (x=0; x<11; x++) {
      Conversion = CalData.PressureTable[x];
      Numout(Conversion, 16, '0', &Converted[0], 4);
      Converted[4] = ' ';
      SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   }
   Converted[0] = CR;
   Converted[1] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 2);
   
/* Home offset */

   SerialMqueueValue = SerialMessageQueue((UINT8*)OffsetStr, sizeof(OffsetStr));
   Conversion = CalData.Offset;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 6);
}



void DumpAllCalibrationData(void)
/********************************************************************************/
/*                                                                              */
/*  This function will format all calibration data and send it out the serial   */
/*  port.  It will first send out the actuator information:                     */
/*                                                                              */
/*  S/N="ABCDEFGHIJ"  41 42 43 44 45 46 47 48 49 4A 00                          */
/*  ID=ae or aef or aed or Unknown  Gain factor=1.421                           */
/*  Stroke=4.0 in  Diameter=3.00 in  Version=900                                */
/*  Calibration=Pass, Fail or Factory                                           */
/*  A/D pressure count  A/D force count                                         */
/*                                                                              */
/*  Then DumpCalibrationData will be called twice, the first time for the       */
/*  factory default values and the second time for the user run calibration.    */
/*                                                                              */
/********************************************************************************/
{
   UINT16 x;
   STR Converted[12]; 
   UINT32 Conversion;                              /*variable converts output of ReadNVR by sending it to Numout*/
   
   ReCallPSNovram();                               /* Go and read the novram */

/* Serial number (output as ASCII "abcdefghij" , then output as hex 00 00 ... ) */

   SerialMqueueValue = SerialMessageQueue((UINT8*)PSSerialNumberStr, sizeof(PSSerialNumberStr));
   for (x=0; x<(MAXSERIALNUM); x++) {
      Converted[x] = (UINT8)NVR.SerNum[x];
   }
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, MAXSERIALNUM);
   Converted[0] = ' ';
   Converted[1] = ' ';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 2);
   
   for (x=0; x<MAXSERIALNUM; x++) { 
      Conversion = NVR.SerNum[x];
      Numout(Conversion, 16, '0', &Converted[0], 2);
      Converted[2] = ' ';
      SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);
   }

   Converted[0] = CR;
   Converted[1] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 2);
   
/* Actuator ID (output as ASCII - ae, aed, aef,MICRO or UNKNOWN) */

   SerialMqueueValue = SerialMessageQueue((UINT8*)ActuatorStr, sizeof(ActuatorStr));
   switch (NVR.ActId) {
      case NVR_AE: 
         SerialMqueueValue = SerialMessageQueue((UINT8*)aeStr, sizeof(aeStr));
         break;
       case NVR_AED:
		  SerialMqueueValue = SerialMessageQueue((UINT8*)aedStr, sizeof(aedStr));
         break;
      case NVR_MICRO:
		  SerialMqueueValue = SerialMessageQueue((UINT8*)MicroStr, sizeof(MicroStr));
         break;
      case NVR_MICROC:
		  SerialMqueueValue = SerialMessageQueue((UINT8*)MicrocStr, sizeof(MicrocStr));
         break;
      case NVR_AES:
        SerialMqueueValue = SerialMessageQueue((UINT8*)aesStr, sizeof(aesStr));
         break;
      default:
         SerialMqueueValue = SerialMessageQueue((UINT8*)UnknownStr, sizeof(UnknownStr));
         break;
   }

/*  Gain factor */

   SerialMqueueValue = SerialMessageQueue((UINT8*)GainFactorStr, sizeof(GainFactorStr));
   Conversion = (CurrentSetup.GainFactor / 1000);
   Numout(Conversion, 10, ' ', &Converted[0], 2);
   Converted[2] = '.';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);

   Conversion = (CurrentSetup.GainFactor % 1000);
   Numout(Conversion, 10, '0', &Converted[0], 3);
   Converted[3] = CR;
   Converted[4] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 5);
   
/* Stroke length */

   SerialMqueueValue = SerialMessageQueue((UINT8*)StrokeStr, sizeof(StrokeStr));
   switch(NVR.StrokeLength)
   {
      case LENGTH_4:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke4Str, sizeof(Stroke4Str));
         break;
      case LENGTH_5:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke5Str, sizeof(Stroke5Str));
         break;
      case LENGTH_6:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke6Str, sizeof(Stroke6Str));
         break;
      case LENGTH_2:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke2Str, sizeof(Stroke2Str));
         break;
      case LENGTH_50:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke50Str, sizeof(Stroke50Str));
         break;
      case LENGTH_8:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke8Str, sizeof(Stroke8Str));
         break;
      case LENGTH_80:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke80Str, sizeof(Stroke80Str));
         break;
      case LENGTH_100:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke100Str, sizeof(Stroke100Str));
         break;
      case LENGTH_125:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke125Str, sizeof(Stroke125Str));
         break;
/*      case LENGTH_160:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Stroke160Str, sizeof(Stroke160Str));
         break;*/
      default:
         SerialMqueueValue = SerialMessageQueue((UINT8*)UnknownStr, sizeof(UnknownStr));
         break;
   }

/* Diameter (format as x.xx in or xx mm) */

   SerialMqueueValue = SerialMessageQueue((UINT8*)DiameterStr, sizeof(DiameterStr));
   switch(NVR.CylSize)
   {            
      case SIZE1_5:  
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter1_5Str, sizeof(Diameter1_5Str));
         break;
              
      case SIZE2_0:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter2_0Str, sizeof(Diameter2_0Str));
         break;
           
      case SIZE2_5:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter2_5Str, sizeof(Diameter2_5Str));
         break;
                   
      case SIZE3_0:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter3_0Str, sizeof(Diameter3_0Str));
         break;
              
      case SIZE3_25:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter3_25Str, sizeof(Diameter3_25Str));
         break;
           
      case SIZE4_0:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter4_0Str, sizeof(Diameter4_0Str));
         break;
           
      case SIZE_40:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter40Str, sizeof(Diameter40Str));
         break;
           
      case SIZE_50:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter50Str, sizeof(Diameter50Str));
         break;
           
      case SIZE_63:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter63Str, sizeof(Diameter63Str));
         break;
           
      case SIZE_80:
         SerialMqueueValue = SerialMessageQueue((UINT8*)Diameter80Str, sizeof(Diameter80Str));
         break;
           
      default:                                    /* In case of an Error */
         SerialMqueueValue = SerialMessageQueue((UINT8*)UnknownStr, sizeof(UnknownStr));
         break;   
   }

/* Version (format as x.xx)*/

   SerialMqueueValue = SerialMessageQueue((UINT8*)VersionStr, sizeof(VersionStr));
   Conversion = (NVR.PSVersion / 100);
   Numout(Conversion, 10, ' ', &Converted[0], 2);
   Converted[2] = '.';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 3);

   Conversion = (NVR.PSVersion % 100);
   Numout(Conversion, 10, '0', &Converted[0], 2);
   Converted[2] = CR;
   Converted[3] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 4);
   
/* Calibration - Passed, Failed or Factory */

   if(NVR.CalibPass == CALIBPASSED)
   {
      SerialMqueueValue = SerialMessageQueue((UINT8*)CalibratePassStr, sizeof(CalibratePassStr));
   }
   else if(NVR.CalibPass == CALIBFAILED)
   {
      SerialMqueueValue = SerialMessageQueue((UINT8*)CalibrateFailStr, sizeof(CalibrateFailStr));
   }
   else
   {
      SerialMqueueValue = SerialMessageQueue((UINT8*)CalibrateFactoryStr, sizeof(CalibrateFactoryStr));
   }
   
/* A/D pressure count */

   SerialMqueueValue = SerialMessageQueue((UINT8*)PressureCountStr, sizeof(PressureCountStr));
   Conversion = ADPressure;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = ' ';
   Converted[5] = ' ';
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 6);
   
/* A/D force count */

   SerialMqueueValue = SerialMessageQueue((UINT8*)ForceCountStr, sizeof(ForceCountStr));
   Conversion = ADForce;
   Numout(Conversion, 16, '0', &Converted[0], 4);
   Converted[4] = CR;
   Converted[5] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 6);
   
/* Encoder Type */

   SerialMqueueValue = SerialMessageQueue((UINT8*)EncoderStr, sizeof(EncoderStr));
   Conversion = NVR.EncoderType;
   Numout(Conversion, 16, '0', &Converted[0], 2);
   Converted[2] = CR;
   Converted[3] = LF;
   SerialMqueueValue = SerialMessageQueue((UINT8*)Converted, 4);

/*---------- Default Information ----------*/

   SerialMqueueValue = SerialMessageQueue((UINT8*)DefaultStr, sizeof(DefaultStr));
   for (x=0; x<3; x++) {
      CalData.Date[x] = NVR.DefCalDate[x];
   }
   for (x=0; x<11; x++) { 
      CalData.Loadcell[x] = NVR.DefLoadCell[x];
   }   
   CalData.Springrate = NVR.DefSpringRateSlope;
   CalData.Stroke = NVR.DefStrokeLength;
   CalData.SystemPressure = NVR.DefCalSysPressure;
   for (x=0; x<11; x++) { 
      CalData.PressureTable[x] = NVR.DefPressure[x];
   }   
   CalData.Springrate = NVR.DefSpringRateSlope;
   CalData.Offset = NVR.DefCalHomeOffset;
   DumpCalibrationData();

/*---------- User Information ----------*/

   SerialMqueueValue = SerialMessageQueue((UINT8*)UserStr, sizeof(UserStr));
   for (x=0; x<3; x++) {
      CalData.Date[x] = NVR.CalDate[x];
   }
   for (x=0; x<11; x++) { 
      CalData.Loadcell[x] = NVR.LoadCell[x];
   }
   CalData.Springrate = NVR.SpringRateSlope;
   CalData.Stroke = NVR.StrokeLength;
   CalData.SystemPressure = NVR.CalSysPressure;
   for (x=0; x<11; x++) { 
      CalData.PressureTable[x] = NVR.Pressure[x];
   }   
   CalData.Offset = NVR.CalHomeOffset;
   DumpCalibrationData();
}



void ReadMemory(void)
/********************************************************************************/
/*                                                                              */
/*  This function will read data from either the ram, FRAM or flash and send 4   */
/*  bytes out the serial port.  The syntax is:                                  */
/*                                                                              */
/*  FT 57 addr                   where addr is a 1 to 6 digit hex address       */
/*                                                                              */
/*  The response is:                                                            */
/*                                                                              */
/*  FT 57 addr = xx xx xx xx     where xx is one byte of data displayed in hex  */
/*                                                                              */
/*                                                                              */
/********************************************************************************/
{
   UINT8  Count = 0, Index;
   STR    InputBuffer[10], OutBuffer[10];
   UINT16 ExitFlag = FALSE, x;
   UINT8  *Ptr, Value;
   UINT32 PassedPtr;
   
   if (ExtraDataFlag == TRUE) {
      Index = SavedOutptr;
      while (ExitFlag == FALSE) {                 /* Get address first */
         if (DiagBuffer[Index] != CR) {
            InputBuffer[Count] = DiagBuffer[Index];
            Index++;
            Count++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      PassedPtr = Numin(16, InputBuffer);   
      PassedPtr = PassedPtr - (PassedPtr%2);      /* Bring pointer to the even address*/
      Ptr = (UINT8*)PassedPtr;
      OutBuffer[0] = '=';
      OutBuffer[1] = ' ';
      for (x=0; x<4; x++) {
         Value = *Ptr++;                          /* Always read 1 byte         */
         Numout(Value, 16, '0', &OutBuffer[2], 2);
         SerialMqueueValue = SerialMessageQueue((UINT8*)OutBuffer, 4);
         OutBuffer[0] = ' ';
      }
      OutBuffer[0] = CR;
      OutBuffer[1] = LF;
      SerialMqueueValue = SerialMessageQueue((UINT8*)OutBuffer, 2);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void WriteMemory(void)
/********************************************************************************/
/*                                                                              */
/*  This function will write data to either ram or FRAM.  Up to about 8 bytes    */
/*  can be written.  The number is limited by DIAG_BUFFER_SIZE and size of      */
/*  address being written to.  The syntax is:                                   */
/*                                                                              */
/*  FT 58 addr xx xx xx xx xx xx xx xx   where addr is a 6 digit hex address    */
/*                                             xx is one byte of data in hex    */
/*                                                                              */
/********************************************************************************/
{
   UINT8  Count = 0, Index;
   STR    InputBuffer[10];
   UINT16 ExitFlag1 = FALSE, ExitFlag2 = 0;
   UINT8  *Ptr, Value;
   UINT32 PassedPtr;
   
   if (ExtraDataFlag == TRUE) {
      Index = SavedOutptr;
      while (ExitFlag2 == FALSE) {                       /* Get address first */
         if (DiagBuffer[Index] != ' ') {
            InputBuffer[Count] = DiagBuffer[Index];
            Index++;
            Count++;
         }
         else ExitFlag2 = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag2 = TRUE;
      }
      InputBuffer[Count] = ' ';                          /* Make sure Numin stops */
      PassedPtr = Numin(16, InputBuffer);   
      PassedPtr = PassedPtr - (PassedPtr%2);             /* Set pointer to even address*/
      Ptr = (UINT8*)PassedPtr;

/* Get piece of data and write it */

      while (ExitFlag1 == FALSE) {
         while (DiagBuffer[++Index] == ' ');
         ExitFlag2 = FALSE;
         Count = 0;
         while (ExitFlag2 == FALSE) {                    /* Get data now             */
            if ( (DiagBuffer[Index] != ' ') && (DiagBuffer[Index] != CR) ){
               InputBuffer[Count] = DiagBuffer[Index];
               Index++;
               Count++;
            }
            else ExitFlag2 = TRUE;
            if (Count >= sizeof(InputBuffer) - 1) ExitFlag2 = TRUE;
         }
         InputBuffer[Count] = ' ';                       /* Make sure Numin stops */
         Value = Numin(16, InputBuffer);   
         *Ptr++ = Value;                                 /* Write data            */
         if (DiagBuffer[Index] == CR) ExitFlag1 = TRUE;  /* Terminate loop early  */
      }   
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }
}



void SetSBCReadyFlag(void)
/******************************************************************************/
/*                                                                            */
/*  This function will set the SBCReadyFlag to TRUE.  This is to override the */
/*  FT 59 command which causes the 332 system controller to reboot.  Because  */
/*  the SBC did not reboot the SBCReadyFlag does not get set again.  The SBC  */
/*  only sends it once during each power up.  This command will allow the FT  */
/*  user to bypass the SBC startup some time after the FT 59 commands was     */
/*  issued. It will also start the state machine in case it was stopped.      */
/*                                                                            */
/******************************************************************************/
{
   SBCReadyFlag = TRUE;
   StartStateMachine();
}



void SetSpringRateMicro(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will call SetSpringRateMicroFT and passed the ExtraData    */
/*  as the new LEAVING HOME FORCE value.  No testing will done on the        */
/*  value, but it be in the range of 1-100 or so.                            */
/*                                                                           */
/*****************************************************************************/
{
   if (ExtraDataFlag == TRUE) {
      SetSpringRateMicroFT(ExtraData);
   }
   else {
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
   }

}



void StartDUPS(void)
/******************************************************************************/
/*                                                                            */
/*  This function will duplicate the same thing that happens at power up.  It */
/*  will start the DUPS initialization process, then exit.  The function      */
/*  CheckDUPS will wait for the DUPS to either respond or timeout.            */
/*                                                                            */
/******************************************************************************/
{
   DUPS_MSGBUF DUPS_MsgBuf;
   memset(&DUPS_MsgBuf, 0, sizeof(DUPS_MSGBUF));
   
   DUPS_Info.DUPSFlag = FALSE;
   DUPS_MsgBuf.mt = DUPS_MSGINITINTERFACE;
  /* Initialize DUPS interface         */
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, *((DUPS_MSGBUF*) &DUPS_MsgBuf), 0);
   DUPSWaitTime = DUPS_WAIT_TIME;
   IOTestFlag = TRUE;                    /* Tell 1 ms int handler to call     */
   DUPSPendingFlag = TRUE;               /* When called, process DUPS         */
}



void CheckDUPS(void)
/******************************************************************************/
/*                                                                            */
/*  This function will wait for the DUPS to respond to the initialization     */
/*  command from StartDUPS.  Once the DUPS responds or times out the proper   */
/*  messages will be sent to the serial port.                                 */
/*                                                                            */
/******************************************************************************/
{
   UINT32 Value;
   STR    OutBuffer[8];
   
   if (--DUPSWaitTime <= 0) {            /* DUPS timed out - FAILED           */
      DUPSPendingFlag = FALSE;   
      IOTestFlag = FALSE;                /* Stop further calls from 1 ms int  */
      SerialMqueueValue = SerialMessageQueue((UINT8*)DUPSFailedStr, sizeof(DUPSFailedStr));
   }
   else if (DUPS_Info.DUPSFlag == TRUE){ /* DUPS ok so output watts & freq    */
      DUPSPendingFlag = FALSE;   
      IOTestFlag = FALSE;                /* Stop further calls from 1 ms int  */

      Value = PSNvRamData.PSWatts;       /* Convert wattage first             */
      OutBuffer[0] = '=';
      Numout(Value, 10, ' ', &OutBuffer[1], 5);
      SerialMqueueValue = SerialMessageQueue((UINT8*)OutBuffer, 6);
      SerialMqueueValue = SerialMessageQueue((UINT8*)DUPSPassed1Str, sizeof(DUPSPassed1Str));

      switch (PSNvRamData.PSFrequency) { /* Convert frequency now             */
         case FREQ15KHZ:
            SerialMqueueValue = SerialMessageQueue((UINT8*)DUPS15KStr, sizeof(DUPS15KStr));
            break;

         case FREQ20KHZ:
            SerialMqueueValue = SerialMessageQueue((UINT8*)DUPS20KStr, sizeof(DUPS20KStr));
            break;

         case FREQ30KHZ:
            SerialMqueueValue = SerialMessageQueue((UINT8*)DUPS30KStr, sizeof(DUPS30KStr));
            break;

         case FREQ40KHZ:
            SerialMqueueValue = SerialMessageQueue((UINT8*)DUPS40KStr, sizeof(DUPS40KStr));
            break;
      }
   }
}



UINT32 Numin(UINT16 Base, STR Bufferpointer[])
/********************************************************************************/
/*                                                                              */
/*'Numin' converts an ASCII string into an internal (binary) number suitable    */
/* for computation.                                                             */
/*                                                                              */
/* DESCRIPTION:                                                                 */
/* Leading blanks are ignored.  Error checking is performed.  Base is passed    */
/* and can be any value between 2 and 16.  The number is assembled until either */
/* a space or carriage return is detected.                                      */
/*                                                                              */
/********************************************************************************/
{
   BOOLEAN MoreStringFlag;
   STR     Digits[] = "0123456789ABCDEF";
   UINT32  RtrnValue=0;
   UINT8   i;
   
   while (*Bufferpointer == ' ') {      /* Eliminate leading spaces */
      Bufferpointer++;
   }
        
   MoreStringFlag=TRUE;
      
   while(MoreStringFlag==TRUE) {
      for (i=0; i<=Base-1; i++) {
         if (*Bufferpointer == Digits[i]) {
            RtrnValue= (RtrnValue*Base)+i;
         }
      }
      Bufferpointer++;
      if ( (*Bufferpointer == '\r') || (*Bufferpointer == ' ') )
         MoreStringFlag=FALSE;
   }       
   return (RtrnValue);
}
    

   
void CheckIOTest(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will be called from the 1 ms interrupt handler whenever    */
/*  the IOTestFlag is TRUE.  This function will then determine why this      */
/*  repeat call was needed.  Currently there are two reasons.  The first is  */
/*  to output the help message a managable piece at a time.  The second is   */
/*  to allow some time for the DUPS to respond to a initialize message.      */
/*                                                                           */
/*****************************************************************************/
{
   if (DisplayHelpFlag == TRUE) DisplayHelp();
   if (DUPSPendingFlag == TRUE) CheckDUPS();
}



void DisplayHelp(void) 
/*****************************************************************************/
/*                                                                           */
/*  This function will display the help string for each command.  It will    */
/*  show 4 lines then display the --more-- line and wait for the Enter key   */
/*  before displaying the next 4 and so on.   The reason for doing this is   */
/*  because the output buffer isn't very big.  This restricts the number of  */
/*  characters to about 320 per chunk.                                       */
/*                                                                           */
/*****************************************************************************/
{
   UINT16  Index, Start, Stop;
   SINT16  HelpSize, StopFlag = FALSE;
   static  BOOLEAN HelpState = 0;
   
   if (Inptr != -1) {
      HelpSize = sizeof(FT00Str);
      switch (HelpState) {
         case 0:               /* First Time entered   */
         case 1:               /* All groups but last  */
         case 2:
         case 3:
         case 4:
            Start = HelpState * NUM_MSGS;
            Stop = Start + NUM_MSGS;
            SerialMqueueValue = SerialMessageQueue((UINT8*)CrStr, sizeof(CrStr));
            for (Index=Start; Index < Stop; Index++) {
               SerialMqueueValue = SerialMessageQueue((UINT8*)HelpStr[Index], HelpSize);
            }
            SerialMqueueValue = SerialMessageQueue((UINT8*)MoreStr, sizeof(MoreStr));
            Inptr = -1;
            HelpState++;   
            break;

         case 5:               /* Final group and done */
            Start = HelpState * NUM_MSGS;
            SerialMqueueValue = SerialMessageQueue((UINT8*)CrStr, sizeof(CrStr));
            for (Index=Start; StopFlag == FALSE; Index++) {
               if (HelpStr[Index] != NULL)
                  SerialMqueueValue = SerialMessageQueue((UINT8*)HelpStr[Index], HelpSize);
               else StopFlag = TRUE;   
            }
            SerialMqueueValue = SerialMessageQueue((UINT8*)DiagPrompt, sizeof(DiagPrompt));
            HelpState = 0;
            DisplayHelpFlag = FALSE;   
            IOTestFlag = FALSE;   
            Inptr = -1;
            break;
      }
   }
}


void START(void)
{
   CyGOS::Restart();
}

/*
 * This function shall reply the test commands from serial.
 */
UINT16 SerialMessageQueue(UINT8 * Buf, UINT16 Cnt)
{
	SINT32 I;
	for(I = 0; I < Cnt; I++)
	{
		Terminal::OutPoll(Buf[I]);
		//Original implementation was filling an array then starting the transmit interrupt
		//We Can use Terminal::Out here to have same effect. Only issue is printf task
		//has lower priority
	}

	return Cnt;
}
/*
 * This function shall reply the test commands from serial.
 */
void GetLinearEncoder(void)
 {
	STR OutBuffer[20];
	memset(OutBuffer, 0, sizeof(OutBuffer));
	OutBuffer[0] = ' ';
	OutBuffer[1] = '=';
	OutBuffer[2] = ' ';

	UINT32 Value = ReadEncoder();
	sprintf(OutBuffer+strlen(OutBuffer),"%u",(unsigned int)Value);
	/*add the string to serial Q*/
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
	/*add to new line*/
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);
}

void GetRTCData(void)
{
/********************************************************************************/
/*                                                                              */
/*  This command will get the date and time. Month, date and year   			*/
/*  will be separated by "/" and each will be 2 digits each.  MM/DD/YY. 		*/
/* 	Hour, Minute and Second   													*/
/*  will be separated by ":" and each will be 2 digits each.  HH/MM/SS.			*/
/* 	Time will be in 24-hour format        									    */
/*  There will be no error checking.                                            */
/*                                                                              */
/********************************************************************************/
	STR OutBuffer[25];
	memset(OutBuffer, 0, sizeof(OutBuffer));
	OutBuffer[0] = ' ';
	OutBuffer[1] = '=';
	OutBuffer[2] = ' ';
	RTCTime RTCTest;
	RTClock::GetCurrentTime(&RTCTest);

	sprintf(OutBuffer+strlen(OutBuffer), "%02d/%02d/%02d %02d:%02d:%02d",
			RTCTest.Century_Month,RTCTest.Day,RTCTest.Years,RTCTest.Hour,RTCTest.Minute,RTCTest.Second);
	/*add the string to serial Q*/
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
	/*add to new line*/
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);
}

void GetMacAddress(void)
{
/********************************************************************************/
/*                                                                              */
/*  This command read mac address and reply on serial332.       			    */
/*  There will be no error checking.                                            */
/*                                                                              */
/********************************************************************************/
	STR OutBuffer[25];
	BYTE MacAddr[6];
	memset(OutBuffer, 0, sizeof(OutBuffer));
	OutBuffer[0] = ' ';
	OutBuffer[1] = '=';
	OutBuffer[2] = ' ';

	ReadMACAddressFromEEPRom(MacAddr);

	sprintf(OutBuffer+strlen(OutBuffer), "%02X:%02X:%02X:%02X:%02X:%02X",
			MacAddr[0],MacAddr[1],MacAddr[2],MacAddr[3],
			MacAddr[4],MacAddr[5]);

	/*add the string to serial Q*/
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
	/*add to new line*/
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);
}

void SetDACChannel(void)
{
/******************************************************************************/
/*                                                                            */
/*  This function writes frequency,amplitude and digtune value to the dac
 * channel	.													           */
/*                                                                            */
/******************************************************************************/


	PsDac->WriteOutput(0, 0);//0
	PsDac->WriteOutput(1, 1023);//1023
	PsDac->WriteOutput(2, 512);//512

}

void GetActPressurAndForce(void)
{
/******************************************************************************/
/*                                                                            */
/*  This function is used to get pressure and force 			              */
/*                                                                            */
/******************************************************************************/
	STR OutBuffer[25];
	memset(OutBuffer, 0, sizeof(OutBuffer));
	OutBuffer[0] = ' ';
	OutBuffer[1] = '=';
	OutBuffer[2] = ' ';

	sprintf(OutBuffer+strlen(OutBuffer), "%s:%d","Pressure",TestAdPressure);
	/*add the string to serial Q*/
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
	/*add to new line*/
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);

	sprintf(OutBuffer, "%s:%d","Force",TestAdForce);
	/*add the string to serial Q*/
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
	/*add to new line*/
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);

}

void ReadActNovramAddress(void)
/********************************************************************************/
/*                                                                              */
/*  This command will read the address.									       */
/*                                                                              */
/********************************************************************************/
{
   UINT8  Count = 0, Index;
   STR    InputBuffer[10];
   UINT16 ExitFlag = FALSE;
   UINT16 ReadVal = 0;
   STR OutBuffer[15];
   memset(OutBuffer, 0, sizeof(OutBuffer));
   OutBuffer[0] = ' ';
   OutBuffer[1] = '=';
   OutBuffer[2] = ' ';
   if (ExtraDataFlag == TRUE) {
      Index = SavedOutptr;
      while (ExitFlag == FALSE) {
         if (DiagBuffer[Index] != ':') {
            InputBuffer[Count] = DiagBuffer[Index];
            Index++;
            Count++;
         }
         else ExitFlag = TRUE;
         if (Count >= sizeof(InputBuffer) - 1) ExitFlag = TRUE;
      }
      InputBuffer[Count] = ' ';                   /* Make sure Numin stops */
      ReadVal = ReadNVR(Numin(10, InputBuffer));
      sprintf(OutBuffer + strlen(OutBuffer), "%d",ReadVal);
      /*add the string to serial Q*/
      SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, strlen(OutBuffer));
      /*add to new line*/
      OutBuffer[0] = CR;
      OutBuffer[1] = LF;
      SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);
   }
   else
      SerialMqueueValue = SerialMessageQueue((UINT8*)NoDataStr, sizeof(NoDataStr));
}
void SetAESFlowValue(void) {
/******************************************************************************/
/*                                                                            */
/*  This function is used to set flow value(AES specific) 			          */
/*                                                                            */
/******************************************************************************/
	UINT8 Count = 0, Index;
	STR InputBuffer[10];
	UINT16 ExitFlag = FALSE;
	InputBuffer[0] = CR;
	InputBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) InputBuffer, 2);
	if (ExtraDataFlag == TRUE) {
		Index = SavedOutptr;
		while (ExitFlag == FALSE) {
			InputBuffer[Count] = DiagBuffer[Index];
			Index++;
			Count++;

			if (Count >= sizeof(InputBuffer) - 1)
				ExitFlag = TRUE;
		}
		InputBuffer[Count] = ' '; /* Make sure Numin stops */
		SetFlowValue = Numin(10, InputBuffer);
	} else
		SerialMqueueValue = SerialMessageQueue((UINT8*) NoDataStr,
				sizeof(NoDataStr));
}

void SetAESPressureValue(void) {
/******************************************************************************/
/*                                                                            */
/*  This function is used to set pressure value(AES specific) 			          */
/*                                                                            */
/******************************************************************************/
	UINT8 Count = 0, Index;
	STR InputBuffer[10];
	UINT16 ExitFlag = FALSE;
	InputBuffer[0] = CR;
	InputBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) InputBuffer, 2);

	if (ExtraDataFlag == TRUE) {
		Index = SavedOutptr;
		while (ExitFlag == FALSE) {
			InputBuffer[Count] = DiagBuffer[Index];
			Index++;
			Count++;

			if (Count >= sizeof(InputBuffer) - 1)
				ExitFlag = TRUE;
		}
		InputBuffer[Count] = ' '; /* Make sure Numin stops */
		SetPressureValue = Numin(10, InputBuffer) * 10;
	} else
		SerialMqueueValue = SerialMessageQueue((UINT8*) NoDataStr,
				sizeof(NoDataStr));
}

void WriteToActNovramAddress(void) {
/******************************************************************************/
/*                                                                            */
/*  This function Writes the Data to the indicated Address of the Novram	  */
/*                                                                            */
/******************************************************************************/
	UINT8 Count = 0, Index;
	STR InputBuffer[10], OutBuffer[10];
	UINT16 ExitFlag1 = FALSE, ExitFlag2 = 0;
	UINT32 Value;
	UINT16 Address;
	OutBuffer[0] = CR;
	OutBuffer[1] = LF;
	SerialMqueueValue = SerialMessageQueue((UINT8*) OutBuffer, 2);
	if (ExtraDataFlag == TRUE) {
		Index = SavedOutptr;
		while (ExitFlag2 == FALSE) { /* Get address first */
			if (DiagBuffer[Index] != ' ') {
				InputBuffer[Count] = DiagBuffer[Index];
				Index++;
				Count++;
			} else
				ExitFlag2 = TRUE;
			if (Count >= sizeof(InputBuffer) - 1)
				ExitFlag2 = TRUE;
		}
		InputBuffer[Count] = ' '; /* Make sure Numin stops */
		Address = Numin(10, InputBuffer);
		/* Get piece of data and write it */

		while (ExitFlag1 == FALSE) {
			while (DiagBuffer[++Index] == ' ' && Index < (sizeof(DiagBuffer) - 1))
				;
			ExitFlag2 = FALSE;
			Count = 0;
			while (ExitFlag2 == FALSE) { /* Get data now             */
				if ((DiagBuffer[Index] != ' ') && (DiagBuffer[Index] != CR)) {
					InputBuffer[Count] = DiagBuffer[Index];
					Index++;
					Count++;
				} else
					ExitFlag2 = TRUE;
				if (Count >= sizeof(InputBuffer) - 1)
					ExitFlag2 = TRUE;
			}
			InputBuffer[Count] = ' '; /* Make sure Numin stops */
			Value = Numin(10, InputBuffer);
			if (DiagBuffer[Index] == CR)
				ExitFlag1 = TRUE; /* Terminate loop early  */
			if(Address < 256)
			{
				NVRWriteSetup();
				NVRWriteVerify(Value, Address);
				NVRCommandEWDS();
			}
			else
				SerialMqueueValue = SerialMessageQueue((UINT8*) NoDataStr,
								sizeof(NoDataStr));
		}
	} else
		SerialMqueueValue = SerialMessageQueue((UINT8*) NoDataStr,
				sizeof(NoDataStr));

}

