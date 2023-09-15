/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/actnvram.cpp_v   1.22   Nov 06 2017 09:31:38   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/actnvram.cpp_v  $
 * 
 *    Rev 1.22   Nov 06 2017 09:31:38   RJamloki
 * Added comment for MICROC ID and fix code review revision comments
 * 
 *    Rev 1.21   Oct 09 2017 14:27:34   RJamloki
 * added CurrentSetup.Actuator=MICROC in if stament that, evaluae actuartor id's
 * 
 *    Rev 1.20   16 Apr 2015 07:18:52   rjamloki
 * Fixed unused extern warning
 * 
 *    Rev 1.19   08 Jan 2015 03:18:18   AnPawar
 * printf removed
 * 
 *    Rev 1.18   06 Oct 2014 06:28:32   AnPawar
 * removed delay from NVRWriteEWEN().CheckForActChange() function changed.
 * 
 *    Rev 1.17   11 Sep 2014 10:48:22   rjamloki
 * removed redundant Actuator_Novram_Exist flag.
 * 
 *    Rev 1.16   18 Aug 2014 01:36:56   rjamloki
 * Added MICRO and AE support. Defaulted to AE.
 * 
 *    Rev 1.15   28 Jul 2014 12:36:36   rjamloki
 * psos.h removed
 * 
 *    Rev 1.14   15 Jul 2014 17:28:58   hasanchez
 * Changes about the freq offset
 * 
 *    Rev 1.13   09 Jul 2014 10:35:16   rjamloki
 * removed Load Cell support
 * 
 *    Rev 1.12   20 Jun 2014 14:57:12   rjamloki
 * Fixed SetActID function. Removed possible delays from Act Nov Ram access.
 * 
 *    Rev 1.11   11 Jun 2014 11:17:20   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   21 May 2014 10:47:44   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.9   21 May 2014 02:49:58   rjamloki
 * extern variables clean up, removed redundant inclusion
 * 
 *    Rev 1.8   21 Apr 2014 13:16:48   rjamloki
 * Part number corrected in header name
 * 
 *    Rev 1.7   14 Apr 2014 09:53:00   rjamloki
 * Removed QSMMap and fixed to use driver functions
 * 
 *    Rev 1.6   06 Mar 2014 11:03:44   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:14   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:18   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*--------------------------- INCLUDE FILES ----------------------------------*/

#include "qdef.h"

#include "qsm.h"
#include "menu.h"
#include "actnvram.h"
#include "preset.h"
#include "snsrcalb.h"
#include "ticks.h"
#include "spidd.h"
#include "alarms.h"
#include "ready.h"
#include "menu7a.h"
#include "digout.h"
#include "rdyweld1.h"
#include "version.h"
#include "psnvram.h"
#include "AT93C66.h"
#include "RTOS.h"
#include "fpled.h"
/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */

const UINT16 DefPress[] = { 20, 165, 311, 457, 602, 748, 894, 1039, 1185, 1331,
      1476 };

/* 1000 count offset built in for AED/AES only*/
const UINT16 AEDDefLoad[] = { 1041, 2124, 3207, 4289, 5372, 6454, 7537, 8619,
      9701, 10787, 11887 };

const UINT16 MICRODefLoad[]={999,1432,1866,2299,2733,3167,3601,4034,4468,4902,5336}; 
const SINT32 DefForce3in[] = { 46603, 18473, -9657, 0, 0, 0, 0, 0, 0, 0, 0 };
const SINT32 DefForce2in[] = { 20712, -7418, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/* 1000 count offset built in for AED/AES SBEAM*/
const UINT16 DefSBeam[] = { 950, 1880, 2810, 3740, 4670, 5600, 6530, 7460, 8390, 9320, 10250 };

UINT8 NovramEnable = FALSE;
struct act_nvr NVR;
SINT16 ForceTableCylFactor, VelocityTableCylFactor;

/*------------------------- EXTERNAL DATA ----------------------------------*/

/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define ACTBAUDRATE           23    // 24.6.../(2*20) = 524.3kHz
#define MAX_ACTNVRAM_RETRIES  2
#define DEFCALDATE            0x19
#define DELAY_ACT_NOVRAM      7

#define PSI2DAC               65535.0/90.0
/* The force factor = (cyl*cyl/(cyl*cyl -shaft * shaft))*PSI2DAC */
/* divide by 10 so that pressure can be kept in 1/10 PSI, multiply by 256 to keep accuracy */

#define FORCEFACTORSIZE1_5        (SINT16)(((1.5*1.5/(1.5*1.5 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE2_0        (SINT16)(((2.0*2.0/(2.0*2.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE2_5        (SINT16)(((2.5*2.5/(2.5*2.5 - 0.625 * 0.625))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE3_0        (SINT16)(((3.0*3.0/(3.0*3.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE3_25       (SINT16)(((3.25*3.25/(3.25*3.25 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE4_0        (SINT16)(((4.0*4.0/(4.0*4.0 - 0.75 * 0.75))*PSI2DAC)/10)<<8

#define FORCEFACTORSIZE_32        (SINT16)(((1.3*1.3/(1.3*1.3 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_40        (SINT16)(((1.57*1.57/(1.57*1.57 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_50        (SINT16)(((1.97*1.97/(1.97*1.97 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_63        (SINT16)(((2.48*2.48/(2.48*2.48 - 0.75 * 0.75))*PSI2DAC)/10)<<8
#define FORCEFACTORSIZE_80        (SINT16)(((3.15*3.15/(3.15*3.15 - 0.75 * 0.75))*PSI2DAC)/10)<<8

#define VELFACTORSIZE1_5           FORCEFACTORSIZE1_5
#define VELFACTORSIZE2_0           20500 /* set using AEF # 6 */
#define VELFACTORSIZE2_5           FORCEFACTORSIZE2_0
#define VELFACTORSIZE3_0           18455
#define VELFACTORSIZE3_25          FORCEFACTORSIZE3_25
#define VELFACTORSIZE4_0           FORCEFACTORSIZE4_0

#define VELFACTORSIZE_32           FORCEFACTORSIZE_32
#define VELFACTORSIZE_40           FORCEFACTORSIZE_40
#define VELFACTORSIZE_50           FORCEFACTORSIZE_50
#define VELFACTORSIZE_63           FORCEFACTORSIZE_63
#define VELFACTORSIZE_80           FORCEFACTORSIZE_80

#define AE_VERIFY_ADDR    0x00ff        /* Novram address used to verify AE actuator being present */

//-------------------------- LOCAL DATA ------------------------------------


enum ACTUATOR Actuator;

//----------------------------- CODE ---------------------------------------


void ActPowerUp(void) {
   UINT16 i = 0;
   UINT16 j = 0;
   UINT32 temp1 = 0;
   UINT32 temp2 = 0;

   NovramEnable = TRUE;
   /* make sure 1ms queues are done */
   RTOS::DelayMs(5);

   if (ActNovramExists()) {
      NVR.ActId = ReadNVR(0);
      NVR.DefStrokeLength = ReadNVR(3);
      NVR.StrokeLength = ReadNVR(0x53);
      NVR.DefCylSize = ReadNVR(4);
      NVR.CylSize = ReadNVR(0x54);
      NVR.CalibDefPass = ReadNVR(0xA3);
      NVR.CalibPass = ReadNVR(0xA4);
      NVR.EncoderType = (ENCODER) ReadNVR((UINT16) ENCODER_ADDR);

      for (i = 0; i < MAXSERIALNUM; i++) {
         NVR.DefSerNum[i] = ReadNVR(i + 5);
         NVR.SerNum[i] = ReadNVR(i + 0x55);
      }
      for (i = 0; i < 11; i++) {
         NVR.DefLoadCell[i] = ReadNVR(i + 0x1C);
         NVR.LoadCell[i] = ReadNVR(i + 0x6C);
         NVR.DefPressure[i] = ReadNVR(i + 0x27);
         NVR.Pressure[i] = ReadNVR(i + 0x77);
      }
      for (i = 0, j = 0; i < FORCE_TABLE_SIZE; i++, j += 2) {
         temp2 = ReadNVR(j + 0x33); // MSB
         temp2 = temp2 << 16; // Default Force Table
         temp1 = ReadNVR(j + 0x32); // LSB
         NVR.DefForce[i] = temp1 | temp2;
         temp2 = ReadNVR(j + 0x83); // MSB
         temp2 = temp2 << 16; // Force Table
         temp1 = ReadNVR(j + 0x82); // LSB
         NVR.Force[i] = temp1 | temp2;
      }
      temp2 = ReadNVR(0x3F); // MSB
      temp2 = temp2 << 16; // Default Calibrated Stroke Length
      temp1 = ReadNVR(0x3E); // LSB
      NVR.DefCalStrokeLen = temp1 | temp2;
      temp2 = ReadNVR(0x8F); // MSB
      temp2 = temp2 << 16; // Calibrated Stroke Length
      temp1 = ReadNVR(0x8E); // LSB
      NVR.CalStrokeLen = temp1 | temp2;
      NVR.DefCalSysPressure = ReadNVR(0x40);
      NVR.CalSysPressure = ReadNVR(0x90);

      NVR.DefSpringRateSlope = ReadNVR(0x42);
      NVR.SpringRateSlope = ReadNVR(0x92);
      NVR.DefCalHomeOffset = ReadNVR(0x41);
      NVR.CalHomeOffset = ReadNVR(0x91);

      NVR.PSVersion = ReadNVR(0xa5);
      NVR.ForceGauge = ReadNVR(0xa6);
      if (NVR.ForceGauge != SBEAM) {
         NVR.ForceGauge = SBEAM; /* SBEAM is the default */
         SetForceGauge(NVR.ForceGauge);
      }
      for (i = 0; i < 3; i++) {
         NVR.DefCalDate[i] = ReadNVR(i + 0x19);
         NVR.CalDate[i] = ReadNVR(i + 0x69);
      }
      UpdateCylinderFactor();
   } else
      ActRecover();

   InitBarGraph();
   NovramEnable = FALSE;
}

UINT16 GetActId(void) {
   UINT16 Convert;
   switch (NVR.ActId) {
   case NVR_AE: 
      Convert=AE; // ae
      break;
   case NVR_AED:
      Convert = AED; // aed
      CurrentSetup.HandHeld = FALSE; /* Force handheld off */
      DealWithHandHeldChange(); /* Pretend menu turned it off */
      break;
   case NVR_MICRO: 
      Convert=MICRO; // micro
      CurrentSetup.HandHeld = FALSE;     /* Force handheld off */
      DealWithHandHeldChange();          /* Pretend menu turned it off */
      break;
   case NVR_MICROC:
      Convert=MICROC; // MICRO C ID for sunrise micro c actuator
      CurrentSetup.HandHeld = FALSE;     /* Force handheld off */
      DealWithHandHeldChange();          /* Pretend menu turned it off */
      break;
   case NVR_AES:
      Convert = AES; // aes
      CurrentSetup.HandHeld = FALSE; /* Force handheld off */
      DealWithHandHeldChange(); /* Pretend menu turned it off */
      break;
	default:
	  Convert=AE; // ae
      break;
   }
   return (Convert);
}

UINT32 GetActLifeTime(void) {
   return NVR.ActualLifeTime;
}

UINT16 GetDefStrokeLength(void) {
   return (NVR.DefStrokeLength);
}

UINT16 GetStrokeLength(void) {
   return (NVR.StrokeLength);
}

UINT16 GetDefCylSize(void) {
   return (NVR.DefCylSize);
}

UINT16 GetCylSize(void) {
   return (NVR.CylSize);
}

enum ENCODER GetEncoderType(void) {
   return (NVR.EncoderType);
}

void SetActId(UINT16 Data) {
   if ( (Data == NVR_AED)|| (Data == NVR_AES) ||(Data==NVR_MICRO) || (Data==NVR_MICROC) ) // 3,5  aed, aes
   {
      NVRWriteSetup();
      NVRWriteVerify(Data, 0);
      NVR.ActId = Data;
      NVRCommandEWDS();
   } else {
      NVR.ActId=NVR_AE;      /* 1 default ae */
   }
}

void SetDefStrokeLength(UINT16 Data) {
   NVRWriteSetup();
   NVRWriteVerify(Data, 3);
   NVR.DefStrokeLength = Data;
   NVRCommandEWDS();
}

void SetStrokeLength(UINT16 Data) {
   NVRWriteSetup();
   NVRWriteVerify(Data, 0x53);
   NVR.StrokeLength = Data;
   NVRCommandEWDS();
}

void SetDefCylSize(UINT16 Data) {
   NVRWriteSetup();
   NVRWriteVerify(Data, 4);
   NVR.DefCylSize = Data;
   NVRCommandEWDS();
}

void SetCylSize(UINT16 Data) {
   NVRWriteSetup();
   NVRWriteVerify(Data, 0x54);
   NVR.CylSize = Data;
   NVRCommandEWDS();
}

void SetDefCalStrokeLength(UINT32 Data)
/****************************************************************************/
/*                                                                          */
/* This function is called from DoColdStartPlus.                            */
/*                                                                          */
/****************************************************************************/
{
   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;

   UINT16 Address = 0x3E;

   NVRWriteSetup(); // enable write

   temp = Data; // 32 bits
   LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part

   temp = (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData = (UINT16) (temp >> 16);

   NVRWriteVerify(LsbData, Address); // Data, Address
   NVRWriteVerify(MsbData, Address + 1); // Data, Address
   NVRCommandEWDS();
}

void SetDefCalSysPressure(SINT16 Data)
/****************************************************************************/
/*                                                                          */
/* This function is called from DoColdStartPlus. Default pressure = 60PSI   */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16) Data, 0x40);
   NVR.DefCalSysPressure = Data;
   NVRCommandEWDS();
}

void SetCalStrokeLength(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from DoColdStartPlus and Cal Sensors.            */
/*                                                                          */
/****************************************************************************/
{
   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;

   UINT16 Address = 0x8E;

   NVRWriteSetup(); // enable write

   temp = NVR.CalStrokeLen; // 32 bits
   LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part

   temp = (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData = (UINT16) (temp >> 16);

   NVRWriteVerify(LsbData, Address); // Data, Address
   NVRWriteVerify(MsbData, Address + 1); // Data, Address
   NVRCommandEWDS();
}

void SetCalSysPressure(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from DoColdStartPlus and Cal Sensors.            */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalSysPressure, 0x90);
   NVRCommandEWDS();
}

void SetPSVersionNVR(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when the Power Supply Version Number needs to be */
/* saved to the Novram.  This function is called after a successful         */
/* Calibrate Sensors, when the "checksum" is done, or at power up when a    */
/* Version 6 actuator is detected.                                          */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVR.PSVersion = CurrentVersion;
   NVRWriteVerify(NVR.PSVersion, 0xa5);
   NVRCommandEWDS();
}

void UpdateDefCalStrokeLength(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;

   UINT16 Address = 0x3E;

   NVRWriteSetup(); // enable write

   temp = NVR.CalStrokeLen; // 32 bits
   LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part

   temp = (temp & 0x0FFFF0000); // Isolated the MSB part
   MsbData = (UINT16) (temp >> 16);

   NVRWriteVerify(LsbData, Address); // Data, Address
   NVRWriteVerify(MsbData, Address + 1); // Data, Address
   NVR.DefCalStrokeLen = NVR.CalStrokeLen;

   NVRCommandEWDS();
}

void UpdateDefCalSysPressure(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = 0x0040;

   NVRWriteSetup();
   NVRWriteVerify(NVR.CalSysPressure, Address);
   NVR.DefCalSysPressure = NVR.CalSysPressure;
   NVRCommandEWDS();

}

void UpdateDefCalHomeOffset(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = 0x0041;

   NVRWriteSetup();
   NVRWriteVerify(NVR.CalHomeOffset, Address);
   NVR.DefCalHomeOffset = NVR.CalHomeOffset;
   NVRCommandEWDS();

}

void SetDefSerNum(UINT8 *Ptr) {
   UINT16 i = 0;

   NVRWriteSetup();

   for (i = 0; i < MAXSERIALNUM; i++) {
      NVRWriteVerify(((UINT16) Ptr[i]), i + 5); // Data, Address
      NVR.DefSerNum[i] = Ptr[i];
   }
   NVRCommandEWDS();
}

void SetSerNum(SINT8 *Ptr) {
   UINT16 i = 0;

   NVRWriteSetup();

   for (i = 0; i < MAXSERIALNUM; i++) {
      NVRWriteVerify((UINT16) *Ptr, i + 0x55); // Data, Address
      NVR.SerNum[i] = *Ptr++;
   }

   NVRCommandEWDS();
}

void SetLoadCell(void) // You want to update CurrentSetup, first
{
   UINT16 i = 0;
   UINT16 Address = 0x006C;

   NVRWriteSetup();

   for (i = 0; i < 11; i++) {
      NVRWriteVerify(NVR.LoadCell[i], Address++); // Data, Address
   }
   NVRCommandEWDS();
}

void UpdateDefForce(void) {
   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;
   UINT16 i = 0;
   UINT16 j = 0;

   UINT16 Address = 0x32;

   NVRWriteSetup(); // enable write

   for (i = 0, j = 0; i < FORCE_TABLE_SIZE; i++, j += 2) {
      temp = NVR.Force[i]; // 32 bits
      LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part
      NVR.DefForce[i] = temp;

      temp = (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData = (UINT16) (temp >> 16);

      NVRWriteVerify(LsbData, j + Address); // Data, Address
      NVRWriteVerify(MsbData, j + Address + 1); // Data, Address
   }

   NVRCommandEWDS(); // disable novram
}

void SetDefForce(void) {
   /* Load the default table based on cylinder type */

   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;
   UINT16 i = 0;
   UINT16 j = 0;

   UINT16 Address = 0x32;

   NVRWriteSetup(); // enable write

   for (i = 0, j = 0; i < FORCE_TABLE_SIZE; i++, j += 2) {
      if (NVR.CylSize == SIZE2_0) //
         temp = DefForce2in[i]; // 32 bits
      else
         /* default to 3in cylinder */
         temp = DefForce3in[i]; // 32 bits
      LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part
      NVR.DefForce[i] = temp;

      temp = (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData = (UINT16) (temp >> 16);

      NVRWriteVerify(LsbData, j + Address); // Data, Address
      NVRWriteVerify(MsbData, j + Address + 1); // Data, Address
   }

   NVRCommandEWDS(); // disable novram
}

void SetForceNVR(void) {
   UINT32 temp = 0;
   UINT16 LsbData = 0;
   UINT16 MsbData = 0;
   UINT16 i = 0;
   UINT16 j = 0;

   UINT16 Address = 0x82;

   NVRWriteSetup();

   for (i = 0, j = 0; i < FORCE_TABLE_SIZE; i++, j += 2) {
      temp = NVR.Force[i]; // 32 bits
      LsbData = (UINT16) (temp & 0x0FFFF); // Isolated the LSB part

      temp = (temp & 0x0FFFF0000); // Isolated the MSB part
      MsbData = (UINT16) (temp >> 16);

      NVRWriteVerify(LsbData, j + Address); // Data, Address
      NVRWriteVerify(MsbData, j + Address + 1); // Data, Address
   }

   NVRCommandEWDS();
}



//------------------------------------------------------------------------
// Performs actual write of EWEN bit, assuming QSPI configuration is
// already correct.
//------------------------------------------------------------------------
void NVRWriteEWEN(void) {
	ActNvRam->WriteEnable(true);
	// write time delay
//	RTOS::DelayMs(10);
}

//------------------------------------------------------------------------ 
// NVRCommandEWDS: This function disables a write to the NovRam
//------------------------------------------------------------------------
void NVRCommandEWDS(void) {
	ActNvRam->WriteEnable(false);
	NovramEnable = FALSE;
}

/****************************************************************************/
/*                                                                          */
/* Configures the QSPI for writes to the Novram. Also enables writes to the */
/* Novram. This function should be called before NVRWriteVerify() and       */
/* WriteNovram(). Note that NVRCommandEWDS() should be called after writes  */
/* are finished to reset to QSPI configuration.                             */
/*                                                                          */
/****************************************************************************/
void NVRWriteSetup(void) {
	NovramEnable = TRUE;
	NVRWriteEWEN();
}

/****************************************************************************/
/*                                                                          */
/* Writes the Data to the indicated Address of the Novram, reads the data   */
/* back and verifies that it was written correctly. Writes multiple times   */
/* until MAX_ACTNVRAM_RETRIES attempted or until data is read back          */
/* properly.                                                                */
/*                                                                          */
/****************************************************************************/
void NVRWriteVerify(UINT16 Data, UINT16 Address) {
	UINT8 RetryCount = 0;
	UINT16 ReadBack;
	do {
		NVRWriteNovram(Data, Address);
		ReadBack = ReadNVR(Address);
		RetryCount++;
		GlobalRetryCounter++;
	} while ((Data != ReadBack) && (RetryCount < MAX_ACTNVRAM_RETRIES));
	if ((Data != ReadBack) && (Address != AE_VERIFY_ADDR)) {
		RecordErrorCode(ERRORCODE60_EQ10);
		RecordAlarm(EQ10); /* Actuator Novram alarm, couldn't write */
	}
}

void NVRWriteNovram(UINT16 Data, UINT16 Address)
/****************************************************************************/
/*                                                                          */
/* Performs a three-word write to actuator Novram.  Use this function only  */
/* if configuration of QSPI already set up, as in the middle of a series of */
/* transfers.                                                               */
/*                                                                          */
/****************************************************************************/
{

	ActNvRam->Write(Address, Data);
	RTOS::DelayMs(10);
}

//------------------------------------------------------------------------
//  ReadNVR: This function returns a 16 bit data from a given address
//
//  NOTE: Assumes QSPI configuration is already set up
//------------------------------------------------------------------------
UINT16 ReadNVR(UINT16 Address) {
	UINT16 ReadVal;
	ReadVal = ActNvRam->Read(Address);
	return ReadVal;
}


// ------------------------------------------------------------------------
// This function copys the Current pressure table, which is in the 
// CurrentSetup, to the NovRam.  
// ------------------------------------------------------------------------

void SetPressure(void) // You want to update CurrentSetup first
{
   UINT16 Address = 0x77; // with the a new pressure table, before you
   UINT16 i = 0; // call to this function.

   NVRWriteSetup();

   for (i = 0; i < 11; i++) {
      NVRWriteVerify(NVR.Pressure[i], Address++);
   }

   NVRCommandEWDS();
}

//------------------------------------------------------------------------
//
// This function sets the default pressure
//
//------------------------------------------------------------------------

void SetDefPressure(void) {
   UINT16 Address = 0x0027;
   UINT16 i = 0;

   NVRWriteSetup();

   for (i = 0; i < 11; i++) {
      NVRWriteVerify(DefPress[i], Address++); // (Data, Address)
      NVR.DefPressure[i] = DefPress[i];
   }

   NVRCommandEWDS();
}

void SetDefLoadCell(void)
/* Load the flash defaults into the Actuator novram, check if SBEAM or Loadcell */
{
   UINT16 Address = 0x001C;
   UINT16 i = 0;

   NVRWriteSetup();

   for (i = 0; i < 11; i++) 
   {
       switch (NVR.ActId) {
            case NVR_MICRO:
               if(GetEncoderType()== ENCODER_ENGLISH)//2000X micro std prod
               {
            		NVRWriteVerify(DefSBeam[i], Address++); // (Data, Address)
            		NVR.DefLoadCell[i] = DefSBeam[i];
               }
               else//2000X micro special
               {
                    NVRWriteVerify(MICRODefLoad[i], Address++); // (Data, Address)
                    NVR.DefLoadCell[i]=MICRODefLoad[i];
               }
               break;
			default:
			   NVRWriteVerify(DefSBeam[i], Address++); // (Data, Address)
			   NVR.DefLoadCell[i]=DefSBeam[i];
			   break;
   	   }
   }   
   NVRCommandEWDS();
}

/********************************************************************/
void GetDefPressure(void) {
   int i;

   for (i = 0; i < 11; i++)
      NVR.Pressure[i] = NVR.DefPressure[i];
}

void GetDefLoadCell(void) {
   int i;

   for (i = 0; i < 11; i++)
      NVR.LoadCell[i] = NVR.DefLoadCell[i];
}

void GetDefForce(void) {
   int i;

   for (i = 0; i < FORCE_TABLE_SIZE; i++)
      NVR.Force[i] = NVR.DefForce[i];
}

void GetDefCalStrokeLen(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when resetting Calibration                       */
/*                                                                          */
/****************************************************************************/
{
   NVR.CalStrokeLen = NVR.DefCalStrokeLen;
}

void GetDefHomeOffset(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when resetting Calibration                       */
/*                                                                          */
/****************************************************************************/
{
   NVR.CalHomeOffset = NVR.DefCalHomeOffset;
}

void UpdateDefPressure(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = 0x0027;
   UINT16 i;

   NVRWriteSetup();

   for (i = 0; i < 11; i++) {
      NVRWriteVerify(NVR.Pressure[i], Address++); // (Data, Address)
      NVR.DefPressure[i] = NVR.Pressure[i];
   }

   NVRCommandEWDS();
}

void UpdateDefLoadCell(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = 0x001C;
   UINT16 i;

   NVRWriteSetup();

   for (i = 0; i < 11; i++) {
      NVRWriteVerify(NVR.LoadCell[i], Address++); // (Data, Address)
      NVR.DefLoadCell[i] = NVR.LoadCell[i];
   }

   NVRCommandEWDS();
}

/****************************************************************************/
/* This function returns max. weld force for given actuator type and size   */
/* at appropriate pressure applied                                          */
/*                                                                          */
/****************************************************************************/
SINT32 GetMaxForce(void) {
   SINT32 TempMax = 0;
   if (NVR.ActId==NVR_MICRO)
   {
      TempMax=AED_MAXFORCE_40MM;/* Force micro to 40 mm cylinder */    
   }
   else if ((NVR.ActId == NVR_AED) || (NVR.ActId == NVR_AES) || (NVR.ActId == NVR_MICROC)) {
      switch (NVR.CylSize) {
      case SIZE1_5:
         TempMax = AED_MAXFORCE_1_5IN;
         break;

      case SIZE2_0:
         TempMax = AED_MAXFORCE_2_0IN;
         break;

      case SIZE2_5:
         TempMax = AED_MAXFORCE_2_5IN;
         break;

      case SIZE3_0:
         TempMax = AED_MAXFORCE_3_0IN;
         break;

      case SIZE3_25:
         TempMax = AED_MAXFORCE_3_25IN;
         break;

      case SIZE4_0:
         TempMax = AED_MAXFORCE_4_0IN;
         break;

      case SIZE_32:
         TempMax = AED_MAXFORCE_32MM;
         break;

      case SIZE_40:
         TempMax = AED_MAXFORCE_40MM;
         break;

      case SIZE_50:
         TempMax = AED_MAXFORCE_50MM;
         break;

      case SIZE_63:
         TempMax = AED_MAXFORCE_63MM;
         break;

      case SIZE_80:
         TempMax = AED_MAXFORCE_80MM;
         break;

      default: /* In case of an Error */
         TempMax = AED_MAXFORCE_CUSTOM; /* For MAX Custom  */
         break;
      }
   }
   return (TempMax);
}

//------------------------------------------------------------------------
// This Function returnes a TRUE if the data in NVRAM is valid
// IT CHECKS if: Actuator Id, StrokeLength, CylSize have valid values.
//               For AED/AES, also checks serial #, LoadCell table.
//
// Note: For AE there is no Novram, so NVR structure should have been
//       manually filled in with something reasonable before calling this
//       function.
//
//------------------------------------------------------------------------

BOOLEAN CheckNvrValid(void) {
   BOOLEAN Valid = FALSE;
   UINT16 i = 0;

   if( (NVR.ActId==NVR_AED)||(NVR.ActId==NVR_AES)||(NVR.ActId==NVR_MICRO)||(NVR.ActId==NVR_MICROC))  // Testing Actuator Id
   {
      Valid = TRUE;
   }
   switch (NVR.StrokeLength) {
   case LENGTH_4:
      break;
   case LENGTH_5:
      break;
   case LENGTH_6:
      break;
   case LENGTH_2:
      break;
   case LENGTH_8:
      break;
   case LENGTH_80:
      break;
   case LENGTH_70:
      break;
   case LENGTH_100:
      break;
   case LENGTH_125:
      break;
      /*case LENGTH_160:
       break;*/
   case LENGTH_50:
      break;
   case LENGTH_75:
      break;
   case CUSTOMLEN:
      break;
   default:
      RecordErrorCode(ERRORCODE30_EQ10);
      Valid = FALSE;
      break;
   }
   switch (NVR.CylSize) {
   case CUSTOMSIZE:
      break;
   case SIZE1_5:
      break;
   case SIZE2_0:
      break;
   case SIZE2_5:
      break;
   case SIZE3_0:
      break;
   case SIZE3_25:
      break;
   case SIZE4_0:
      break;
   case SIZE_32:
      break;
   case SIZE_40:
      break;
   case SIZE_50:
      break;
   case SIZE_63:
      break;
   case SIZE_80:
      break;
   default:
      RecordErrorCode(ERRORCODE20_EQ10);
      Valid = FALSE;
      break;
   }
   if ((NVR.ActId == NVR_AED)||(NVR.ActId == NVR_AES)||(NVR.ActId == NVR_MICRO)||(NVR.ActId == NVR_MICROC))
   {
      for (i = 0; i < (MAXSERIALNUM - 1); i++) // Ascii can't be more than 128; Testing Serial Number
      {
         if ((NVR.SerNum[i] > 127) || (NVR.SerNum[i] < ' ')) {
            RecordErrorCode(ERRORCODE10_EQ10);
            Valid = FALSE;
         }
      }
      for (i = 1; i < 11; i++) // Each next element has to be larger than its previous
      {
         if (NVR.LoadCell[i] <= NVR.LoadCell[i - 1]) {
            RecordErrorCode(ERRORCODE50_EQ10);
            Valid = FALSE;
         }
         if (NVR.Pressure[i] <= NVR.Pressure[i - 1]) {
            RecordErrorCode(ERRORCODE40_EQ10);
            Valid = FALSE;
         }
      }
   }
   return (Valid);
}

BOOLEAN CheckForActChange(void)
// -------------------------------------------------------------------------
// Compares current actuator type, as read from EEPROM on actuator, to
// contents of CurrentSetup, which should contain type of previous actuator.
// If actuator has changed, records appropriate alarms.
// -------------------------------------------------------------------------
{
   BOOLEAN Changed = FALSE;
   UINT16 i = 0;

   if (CurrentSetup.Actuator != GetActId()) /* See if type has changed */
   {
      Changed = TRUE;
      CurrentSetup.Actuator = GetActId();
      if( (CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (CurrentSetup.ControlLevel < LEVEL_c) )
	  {
    	  RecordAlarm(EQ14); /* Wrong Actuator */
    	  ClearReady();
	  }
      else if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO))
      {
         if (CurrentSetup.ControlLevel < LEVEL_d) {
            RecordAlarm(EQ14); /* Wrong Actuator */
            ClearReady();
         } else {
            RecordAlarm(EQ24); /* Actuator Type */
            RecordErrorCode(ERRORCODE600_EQ20);
            RecordAlarm(EQ20); /* Recalibrate Actuator */
         }
      } else
         RecordAlarm(EQ24); /* Actuator Type */

      /* Changing from non-AE to AE, set stroke length & cyl size to */
      /* defaults for AE. Changing AE to non-AE, set up min/max. */

      CurrentSetup.StrokeLen = GetStrokeLength();
      CurrentSetup.CylinDiameter = GetCylSize();
      SetMaxMinValues();

   } else if (CurrentSetup.Actuator != AE) /* Same type, but check serial #s */
   {
	   if((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (CurrentSetup.ControlLevel < LEVEL_c)){
		   RecordAlarm(EQ14); /* Wrong Actuator */
		   ClearReady();
	   }
	   else if ((((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO)) && (CurrentSetup.ControlLevel < LEVEL_d)))
	   {
         RecordAlarm(EQ14); /* Wrong Actuator */
         ClearReady();
      } else {
         for (i = 0; i < MAXSERIALNUM && !Changed; i++) {
            if (NVR.SerNum[i] != (UINT16) CurrentSetup.ActSerialNumber[i]){
               Changed = TRUE;
            }
         }
      }

      if (Changed) {
         RecordErrorCode(ERRORCODE100_EQ20);
         RecordAlarm(EQ20); /* Recalibrate Actuator */
      }
   } else /* was AE before, is AE now */
   {
      /* NVR structure was filled in with defaults for AE, since AE has no */
      /* Novram.  Here we just make sure NVR matches CurrentSetup, in case */
      /* anybody looks at NVR. */

      NVR.StrokeLength = CurrentSetup.StrokeLen;
      NVR.CylSize = CurrentSetup.CylinDiameter;
   }

   if ((CurrentSetup.Actuator == AED) || /* Set up these all the time, just */
   (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
   {
      /* If stroke length or cylinder size changed with this actuator, */
      /* update CurrentSetup and adjust max/min settings. */
      if (CurrentSetup.StrokeLen != GetStrokeLength()
            || CurrentSetup.CylinDiameter != GetCylSize()) {
         CurrentSetup.StrokeLen = GetStrokeLength();
         CurrentSetup.CylinDiameter = GetCylSize();
         SetMaxMinValues();
      }
   }

   if (Changed == TRUE) {
      // Update Encoder Settings 
      if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC))
      {
         EnableMetricEncoder();
      }
      else if(CurrentSetup.Actuator == MICRO)
      {
		if(CurrentSetup.USEncoder!=TRUE) EnableUSEncoder();
	 }
   }
   switch (CurrentSetup.Actuator) {
   case AE :
	   for(i = 0; i < MAXSERIALNUM; i++) {
		  CurrentSetup.ActSerialNumber[i] = ' ';
	   }
	   CurrentSetup.ActSerialNumber[i] = NULL;  /* CurrentSetup is bigger than */
   break;
   case AED:
   case MICRO:
   case MICROC:
   case AES:
      for (i = 0; i < MAXSERIALNUM; i++) {
         CurrentSetup.ActSerialNumber[i] = NVR.SerNum[i];
      }
      CurrentSetup.ActSerialNumber[i] = NULL; /* CurrentSetup is bigger than */
      break; /* MAXSERNUM, so room for NULL */

   default:
      for (i = 0; i < MAXSERIALNUM; i++) {
         CurrentSetup.ActSerialNumber[i] = "Bad act.  "[i];
      }
      CurrentSetup.ActSerialNumber[i] = NULL; /* CurrentSetup is bigger than */
      /* MAXSERNUM, so room for NULL */
   }
   return (Changed);
}

void InitSetupFromAct(void)
// -------------------------------------------------------------------------
// To Recover in case of a problem in the FRAM, the following code copies
// ActuatorId, StrokeLength, CylinderSize, and SerialNumber from act Novram.
// -------------------------------------------------------------------------
{
   UINT16 i = 0;
   CurrentSetup.Actuator = GetActId();
   CurrentSetup.StrokeLen = NVR.StrokeLength;
   CurrentSetup.CylinDiameter = NVR.CylSize;
   for (i = 0; i < MAXSERIALNUM; i++) {
      CurrentSetup.ActSerialNumber[i] = NVR.SerNum[i];
   }
   CurrentSetup.ActSerialNumber[i] = NULL; /* CurrentSetup is bigger than */
}

void ActRecover(void)
//------------------------------------------------------------------------
//    Sets NVR structure to known, reasonable values in the event that
//    actuator Novram either doesn't exist or has invalid information.
//    Note that since these "reasonable" values are not written to EEPROM,
//    they will be lost at power-off.
//
//
//------------------------------------------------------------------------
{
   if ( (NVR.ActId != NVR_AED) && (NVR.ActId != NVR_AES) && (NVR.ActId != NVR_MICRO) && (NVR.ActId != NVR_MICROC) )
   {
      NVR.ActId = NVR_AE;
   }

   if(NVR.ActId==NVR_MICRO)
   {
      if(GetEncoderType()==ENCODER_ENGLISH)//2000X micro std prod
         NVR.StrokeLength = LENGTH_50;
      else
         NVR.StrokeLength = LENGTH_2;//2000X micro special
      
      NVR.CylSize=SIZE_40;

   }
   else
   {
      NVR.StrokeLength = LENGTH_4;
      NVR.CylSize = SIZE3_0;
   }

}

UINT16 ActNovramExists(void)
/****************************************************************************/
/*                                                                          */
/* This function returns 1 if it's an AED/F/S actuator, 0 for an AE. First,   */
/* it attempts to read the actuator ID from Novram. If a valid ID comes     */
/* back, then we assume the Novram exists. If not, then we might have a     */
/* blank Novram, so we try to write to it. If we get back what we wrote,    */
/* then we have Novram, otherwise we don't.                                 */
/*                                                                          */
/* NOTE: QSPI configuration must already be set up (for 3-word xfers),      */
/*       though Novram writes need not be enabled. Function exits with the  */
/*       same configuration as on entry, but Novram writes will be turned   */
/*       off.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Val = 0;
   UINT16 TestValue = 0x55AA;

   NVR.ActId = ReadNVR(0); // First, see if this looks valid
   NVR.ActId = ReadNVR(0); // Read twice in case first read no good

   if( (NVR.ActId != NVR_AED) && (NVR.ActId != NVR_AES) && (NVR.ActId!=NVR_MICRO) && (NVR.ActId!=NVR_MICROC) )
   {
      NVRWriteSetup();
      NVRWriteVerify(TestValue, AE_VERIFY_ADDR);

      Val = ReadNVR(AE_VERIFY_ADDR);

      if (Val == TestValue) // It's an AED; there is a chunk of memory to write to.
         Val = 1;
      else
         Val = 0;
		NVRCommandEWDS(); /* Disable writes again */
   } else
      Val = 1; // Got valid act ID, assume we have Novram.
   return (Val);
}

/***---  Test functions  ---***/

void TestWriteToNvram(void)
/***************************************************************************/
/*                                                                         */
/*  This function will write an incrementing number into the actuator      */
/*  novram.  This will wipe out the novram completely.                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;

   NVRWriteSetup();

   for (i = 0; i < 0xff; i++) {
      NVRWriteVerify(i, i);
   }
}

void TestReadFromNvram(void)
/***************************************************************************/
/*                                                                         */
/*  This function will read from the novram.  It expects to read the       */
/*  incrementing number that TestWriteToNvram() wrote.  If an error is     */
/*  discovered the variable ChecksumRet will contain the last address      */
/*  that was in error.                                                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;
   UINT16 Val = 0;

   ChecksumRet = 0;
   for (i = 0; i < 0xff; i++) {
      Val = ReadNVR(i);
      if (Val != i) {
         ChecksumRet = i; /* A place to put a breakpoint */
      }
   }
}

/***---  End of Test functions  ---***/

// ----------------------------------------------------------------------
// This function Copys the default side of the NovRam to its non. 
// You want to use it, probably, only once on serial # initialization.
// ex: Default Cylinder Size --> Cylinder Size.
// ----------------------------------------------------------------------

void NvrCopyDeftoNon(void) {
   UINT16 i;
   UINT16 Val = 0;

   NVRWriteSetup();

   for (i = 3; i < 0x53; i++) {
      Val = ReadNVR(i);
      NVRWriteVerify(Val, (i + 0x50));
   }

   NVRCommandEWDS();
}

void SetCalibPass(UINT16 Val) {
   UINT16 Address = 0xA4;

   NVRWriteSetup();
   NVRWriteVerify(Val, Address);
   NVR.CalibPass = Val;
   NVRCommandEWDS();
}

UINT16 GetCalibPass(void) {
   return (NVR.CalibPass);
}

void SetCalibrationDate(UINT16 *Ptr) { // 0 Month
   UINT16 Address = 0x69; // 1 Day
   UINT16 i = 0; // 2 Year

   NVRWriteSetup();

   for (i = 0; i < 3; i++) {
      NVRWriteVerify(Ptr[i], i + Address);
      NVR.CalDate[i] = Ptr[i];
   }

   NVRCommandEWDS();
}

void SetDefCalibDate(UINT16 *Ptr)
/****************************************************************************/
/*                                                                          */
/* This function is called form the system information screen, when update  */
/* calibrate tables is selected                                             */
/*                                                                          */
/* Outputs : NVR.DefCalDate 0 = Month, 1 = Day, 2 = Year                    */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = DEFCALDATE;
   UINT16 i = 0;

   NVRWriteSetup();

   for (i = 0; i < 3; i++) {
      NVRWriteVerify(Ptr[i], i + Address);
      NVR.DefCalDate[i] = Ptr[i];
   }
   NVRCommandEWDS();
}

void UpdateCylinderFactor(void)
/****************************************************************************/
/*                                                                          */
/* This function is called at power up and EStop. It updates the cylinder   */
/* and velocity table                                                       */
/* Outputs : CylinderFactor                                                 */
/*                                                                          */
/****************************************************************************/
{
   switch (NVR.CylSize) {
   case SIZE1_5:
      ForceTableCylFactor = FORCEFACTORSIZE1_5;
      VelocityTableCylFactor = VELFACTORSIZE1_5;
      break;
   case SIZE2_0:
      ForceTableCylFactor = FORCEFACTORSIZE2_0;
      VelocityTableCylFactor = VELFACTORSIZE2_0;
      break;
   case SIZE2_5:
      ForceTableCylFactor = FORCEFACTORSIZE2_5;
      VelocityTableCylFactor = VELFACTORSIZE2_5;
      break;
   case SIZE3_0:
      ForceTableCylFactor = FORCEFACTORSIZE3_0;
      VelocityTableCylFactor = VELFACTORSIZE3_0;
      break;
   case SIZE3_25:
      ForceTableCylFactor = FORCEFACTORSIZE3_25;
      VelocityTableCylFactor = VELFACTORSIZE3_25;
      break;
   case SIZE4_0:
      ForceTableCylFactor = FORCEFACTORSIZE4_0;
      VelocityTableCylFactor = VELFACTORSIZE4_0;
      break;
   case SIZE_32:
      ForceTableCylFactor = FORCEFACTORSIZE_32;
      VelocityTableCylFactor = VELFACTORSIZE_32;
      break;
   case SIZE_40:
      ForceTableCylFactor = FORCEFACTORSIZE_40;
      VelocityTableCylFactor = VELFACTORSIZE_40;
      break;
   case SIZE_50:
      ForceTableCylFactor = FORCEFACTORSIZE_50;
      VelocityTableCylFactor = VELFACTORSIZE_50;
      break;
   case SIZE_63:
      ForceTableCylFactor = FORCEFACTORSIZE_63;
      VelocityTableCylFactor = VELFACTORSIZE_63;
      break;
   case SIZE_80:
      ForceTableCylFactor = FORCEFACTORSIZE_80;
      VelocityTableCylFactor = VELFACTORSIZE_80;
      break;
   default:
      ForceTableCylFactor = FORCEFACTORSIZE3_0;
      VelocityTableCylFactor = VELFACTORSIZE3_0;
      break;
   }
}

UINT16 GetDefSpringRateSlope(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                     */
/*                                                                          */
/* Outputs: NVR.DefSpringRateSlope used before sensor calibration is done,  */
/*          during a checksum,  or when resetting calibration tables        */
/****************************************************************************/
{

   NVR.SpringRateSlope = NVR.DefSpringRateSlope;
   return (NVR.SpringRateSlope);
}

void GetDefCalSysPressure(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when resetting calibration tables                */
/*                                                                          */
/****************************************************************************/
{

   NVR.CalSysPressure = NVR.DefCalSysPressure;
}

void SetDefSpringRateSlope(UINT16 Data)
/****************************************************************************/
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                      */
/*                                                                          */
/* Outputs: NVR.DefSpringRateSlope used before sensor calibration is done or*/
/*          when resetting calibration tables                               */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16) Data, 0x42);
   NVR.DefSpringRateSlope = Data;
   NVRCommandEWDS();
}

void SetCalSpringRateSlope(UINT16 Data)
/****************************************************************************/
/*                                                                          */
/* This function is called from Sensor Calibration.                         */
/*                                                                          */
/* Outputs: NVR.SpringRateSlope - used in sensor calibration and actuator   */
/*          calibration.                                                    */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify((UINT16) Data, 0x92);
   NVR.SpringRateSlope = Data;
   NVRCommandEWDS();
}

void SetDefCalHomeOffset(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from UpdateNVRDefSpringRate.                     */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.DefCalHomeOffset, 0x41);
   NVRCommandEWDS();
}

void SetCalHomeOffset(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from Sensor Calibration.                         */
/*                                                                          */
/* Outputs: NVR.SpringRateSlope - used in sensor calibration and actuator   */
/*          calibration.                                                    */
/*                                                                          */
/****************************************************************************/
{
   NVRWriteSetup();
   NVRWriteVerify(NVR.CalHomeOffset, 0x91);
   NVRCommandEWDS();
}

void SetForceGauge(UINT16 Type)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu.                           */
/*                                                                          */
/* Outputs: NVR.ForceGauge - Loadcell or SBeam.                             */
/*                                                                          */
/****************************************************************************/
{

   NVRWriteSetup();
   NVRWriteVerify(Type, 0xa6);
   NVR.ForceGauge = Type;
   NVRCommandEWDS();
}

void UpdateDefSpringRateSlope(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the Branson menu after Calibration is run   */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Address = 0x042;

   NVRWriteSetup();
   NVRWriteVerify(NVR.SpringRateSlope, Address);
   NVR.DefSpringRateSlope = NVR.SpringRateSlope;
   NVRCommandEWDS();
}

void SetEncoderType(enum ENCODER Data) {
   NVRWriteSetup();
   NVRWriteVerify(Data, ENCODER_ADDR);
   NVR.EncoderType = Data;
   NVRCommandEWDS();

}
