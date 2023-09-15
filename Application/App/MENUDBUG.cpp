/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/MENUDBUG.cpp_v   1.18   Nov 16 2017 14:59:22   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/MENUDBUG.cpp_v  $
 * 
 *    Rev 1.18   Nov 16 2017 14:59:22   RJamloki
 * Added comments to cases switches
 * 
 *    Rev 1.17   Nov 06 2017 14:52:36   RJamloki
 * Added checksum code for micro c functionality code review update
 * 
 *    Rev 1.16   Oct 10 2017 11:39:12   RJamloki
 * Added checksum code for micro c functionality
 * 
 *    Rev 1.15   28 Nov 2014 07:38:00   rjamloki
 * Removed unused function declaration.
 * 
 *    Rev 1.14   03 Oct 2014 06:11:28   rjamloki
 * AmpDecayPercentMin and  AmpDecayPercentMax variables removed
 * 
 *    Rev 1.13   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.12   05 Sep 2014 04:54:36   rjamloki
 * Checksum handler function changed to configure level C
 * 
 *    Rev 1.11   18 Aug 2014 01:36:04   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.10   28 Jul 2014 12:40:46   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.9   20 Jun 2014 14:37:04   rjamloki
 * Removed redundant functions. Aded support for configuring AES from BUC menu.
 * 
 *    Rev 1.8   11 Jun 2014 11:56:14   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:48:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:33:28   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   05 Mar 2014 13:56:32   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:44   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  --------------------------- MODULE DESCRIPTION ---------------------------

   Module name: Menu debug
   Filename:    Menudbug.c

   Function Name: Menus for debuggging and performance testing

  ----------------------------- DESCRIPTION--------------------------------

   This temp menu file will allow testing parameters to be set

  ----------------------------- PSEUDO CODE --------------------------------



  ---------------------------- LOCAL_EQUATES -------------------------------



  ------------------------------ INCLUDES ----------------------------------*/

#include <string.h>
#include "param.h"
#include "preset.h"
#include "menu.h"
#include "menu3.h"
#include "menu6.h"
#include "snsrcalb.h"
#include "state.h"
#include "statedrv.h"
#include "rtclock.h"
#include "psnvram.h"
#include "actnvram.h"
#include "keypad.h"
#include "getmsg.h"
#include "menu7a.h"
#include "command.h"
#include "graphs.h"
#include "battram.h"
#include "alarms.h"
#include "beep.h"
#include "dups_api.h"
#include "dups.h"

/*----------------------------- LOCAL DEFINES ------------------------------*/

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

SINT32 MinLimitMin = 0;
SINT32 MaxLimitMax = 999999999;
SINT32 AlarmPtrMin = 0;
SINT32 AlarmPtrMax = 0x0fffffff;
SINT32 EnergyBrakeTimeMin = 10;
SINT32 EnergyBrakeTimeMax = 1000;
SINT32 EnergyBrakePercentMin = 5;
SINT32 EnergyBrakePercentMax = 100;
 SINT32 BUCFactoryDefaults = 0;


BUCMENU_1200 BUCMenuRAM;
//UINT16 DUPS_LockTemp[DUPS_NUMPARAMSET];
UINT16 ChecksumRet;
BOOLEAN VGAChecksum = FALSE;
BOOLEAN PresetStatusMenuFlag = FALSE;

/*-------------------------- Function Prototypes ---------------------------*/

void GetRTRamp(void);
void GetReturnRamp(void);
void GetStartRamp(void);
void CopyToFRAM(void);

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern BOOLEAN NextMenuFlag, ChkSumCompleteFlag;

//extern UINT16 DUPS_Lock[];
extern DEPOT_FLAGS *DepotFlag;

SINT32 MinLimitForcePC = 49;
SINT32 MinLimitVelocityPC = 1;
SINT32 MaxLimitVelocityPC = 10;
SINT32 MinLimitGainFactor = 100;
SINT32 MaxLimitGainFactor = 3000;
SINT32 MinLimitMinTrigForce = 50;
SINT32 MaxLimitMinTrigForce = 500;
SINT32 MinLimitIdleSpeed = 10;
SINT32 MaxLimitIdleSpeed = 100;

SINT32 MinBUCFactoryDefaults = 0;
SINT32 MaxBUCFactoryDefaults = 999999999;

SINT32 GlobalRetryCounter = 0;

/*-------------------------------- CODE ------------------------------------*/

void CopyToFRAM(void)
{
    AlarmPtrFRAM = (ALARM_MASKS *)FRAM1200_ALARM_START;

    AlarmPtrFRAM->SetupGroup1 = AlarmPtrRam.SetupGroup1;
    AlarmPtrFRAM->SetupGroup2 = AlarmPtrRam.SetupGroup2;
    AlarmPtrFRAM->SetupGroup3 = AlarmPtrRam.SetupGroup3;
    AlarmPtrFRAM->SetupGroup4 = AlarmPtrRam.SetupGroup4;
    AlarmPtrFRAM->SetupGroup5 = AlarmPtrRam.SetupGroup5;
    AlarmPtrFRAM->SetupGroup6 = AlarmPtrRam.SetupGroup6;
    AlarmPtrFRAM->SetupGroup7 = AlarmPtrRam.SetupGroup7;
    AlarmPtrFRAM->SetupGroup8 = AlarmPtrRam.SetupGroup8;
    AlarmPtrFRAM->SetupGroup9 = AlarmPtrRam.SetupGroup9;
    AlarmPtrFRAM->SetupGroup10 = AlarmPtrRam.SetupGroup10;
    AlarmPtrFRAM->Overload = AlarmPtrRam.Overload;
    AlarmPtrFRAM->NoCycle = AlarmPtrRam.NoCycle;
    AlarmPtrFRAM->EquipmentFailure = AlarmPtrRam.EquipmentFailure;
    AlarmPtrFRAM->CycleModified = AlarmPtrRam.CycleModified;
    AlarmPtrFRAM->Reject = AlarmPtrRam.Reject;
    AlarmPtrFRAM->Suspect = AlarmPtrRam.Suspect;
    AlarmPtrFRAM->Warning = AlarmPtrRam.Warning;
}


void SavePSSerialNum(void)
{
   StorePSSerialNumber();     /* Write to Novram */
   GetSerialNumbers();        /* Update strings for Sys Info menu */
}



void SaveActSerialNum(void)
{
   UINT16 i;
   CONFIGSETUP *FRAMPtr;

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

/* Note: The CurrentSetup.ActSerialNumber member is larger than MAXSERIALNUM */
/*       allowing a NULL terminator to be added at location MAXSERIALNUM.    */

   CurrentSetup.ActSerialNumber[MAXSERIALNUM] = 0;   /* make sure terminated */

   i = strlen(CurrentSetup.ActSerialNumber);
   while (i < MAXSERIALNUM)
      CurrentSetup.ActSerialNumber[i++] = ' ';

   for (i=0; i<=MAXSERIALNUM; i++) {
      FRAMPtr->ActSerialNumber[i] = CurrentSetup.ActSerialNumber[i];
   }
   SetSerNum(CurrentSetup.ActSerialNumber);
   GetSerialNumbers();
}

void UpdateCalibDefault(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration values are saved to the defaults*/
/*                                                                          */
/* Inputs :                                                                 */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
   RTCTime RTCCal;

   Beep(CONFIRMBEEP);

   UpdateDefPressure();
   UpdateDefLoadCell();
   UpdateDefForce();
   UpdateDefCalSysPressure();
   UpdateDefCalStrokeLength();
   UpdateDefSpringRateSlope();
   UpdateDefCalHomeOffset();
   RTClock::GetCurrentTime(&RTCCal);   /* Get date when calibration complete */
   DateArray[0] = RTCCal.Century_Month;
   DateArray[1] = RTCCal.Day;
   DateArray[2] = RTCCal.Years;
   SetDefCalibDate(DateArray);     
   SetCalibPass((UINT16) CALIBDEFAULT);
   Beep(CONFIRMBEEP);
}


/* *** menus for the R/T Comp, R/T Ramp, Return Ramp  *** */

void GetRTRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
//   switch(CurrentPreset.RTRamp)
//   {
//      case RATE_SLOWEST:
//         RadioIndex = 0;
//         break;
//
//      case RATE_SLOW:
//         RadioIndex = 1;
//         break;
//
//      case RATE_NORMAL:
//      default:
//         RadioIndex = 2;
//         break;
//
//      case RATE_FAST:
//         RadioIndex = 3;
//         break;
//
//      case RATE_FASTEST:
//         RadioIndex = 4;
//         break;
//   }
}

void SetRTrRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
//   switch(RadioIndex)
//   {
//      case 0:
//         CurrentPreset.RTRamp = RATE_SLOWEST;
//         break;
//
//      case 1:
//         CurrentPreset.RTRamp = RATE_SLOW;
//         break;
//
//      case 2:
//      default:
//         CurrentPreset.RTRamp = RATE_NORMAL;
//         break;
//
//      case 3:
//         CurrentPreset.RTRamp = RATE_FAST;
//         break;
//
//      case 4:
//         CurrentPreset.RTRamp = RATE_FASTEST;
//         break;
//   }
}

void GetReturnRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Return Rate choice                                                   */
/*                                                                          */
/****************************************************************************/
{
//   switch(CurrentPreset.ReturnRamp)
//   {
//      case RATE_SLOWEST:
//         RadioIndex = 0;
//         break;
//
//      case RATE_SLOW:
//         RadioIndex = 1;
//         break;
//
//      case RATE_NORMAL:
//      default:
//         RadioIndex = 2;
//         break;
//
//      case RATE_FAST:
//         RadioIndex = 3;
//         break;
//
//      case RATE_FASTEST:
//         RadioIndex = 4;
//         break;
//   }
}

void SetreturnRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
//   switch(RadioIndex)
//   {
//      case 0:
//         CurrentPreset.ReturnRamp = RATE_SLOWEST;
//         break;
//
//      case 1:
//         CurrentPreset.ReturnRamp = RATE_SLOW;
//         break;
//
//      case 2:
//      default:
//         CurrentPreset.ReturnRamp = RATE_NORMAL;
//         break;
//
//      case 3:
//         CurrentPreset.ReturnRamp = RATE_FAST;
//         break;
//
//      case 4:
//         CurrentPreset.ReturnRamp = RATE_FASTEST;
//         break;
//   }
}


void GetStartRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Start Rampe Rate choice                                              */
/*                                                                          */
/****************************************************************************/

{
//   switch(CurrentPreset.StartRamp)
//   {
//      case RATE_SLOWEST:
//         RadioIndex = 0;
//         break;
//
//      case RATE_SLOW:
//         RadioIndex = 1;
//         break;
//
//      case RATE_NORMAL:
//      default:
//         RadioIndex = 2;
//         break;
//
//      case RATE_FAST:
//         RadioIndex = 3;
//         break;
//
//      case RATE_FASTEST:
//         RadioIndex = 4;
//         break;
//   }
}

void SetstartRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
//   switch(RadioIndex)
//   {
//      case 0:
//         CurrentPreset.StartRamp = RATE_SLOWEST;
//         break;
//
//      case 1:
//         CurrentPreset.StartRamp = RATE_SLOW;
//         break;
//
//      case 2:
//      default:
//         CurrentPreset.StartRamp = RATE_NORMAL;
//         break;
//
//      case 3:
//         CurrentPreset.StartRamp = RATE_FAST;
//         break;
//
//      case 4:
//         CurrentPreset.StartRamp = RATE_FASTEST;
//         break;
//   }
}

//void UpdateDUPSPresetStatus(UINT16 DupsPrstNum, UINT16 DupsStatus) {
   //   UINT16 cnt;
   //   switch(DUPS_LockTemp[DupsPrstNum])
   //   {
   //      case DUPS_PARAMSETLOCKED: // Source.
   //
   //         switch(DupsStatus)
   //         {
   //            case DUPS_PARAMSETLOCKED:
   //            // Locked to Locked. No changes occur.
   //               break;
   //
   //            case DUPS_PARAMSETAVAIL:
   //               PresetClear(DUPS_FindCOP4DUPS(DupsPrstNum));
   //               break;
   //
   //            case DUPS_PARAMSETSAVED:
   //               Beep(ERRORBEEP); // Condition not allowed.Report error beep.
   //               break;
   //
   //            default:
   //               break;
   //         }
   //         break;
   //
   //      case DUPS_PARAMSETAVAIL:         //source
   //
   //         switch( DupsStatus )
   //         {
   //            case DUPS_PARAMSETLOCKED:  // Destination.
   //               break;
   //
   //            case DUPS_PARAMSETAVAIL:
   //            // Avail to Avail. No changes occur.
   //               break;
   //
   //            case DUPS_PARAMSETSAVED:
   //               Beep(ERRORBEEP); // Condition not allowed.Report error beep.
   //               break;
   //
   //            default:
   //               break;
   //         }
   //         break;
   //
   //      case DUPS_PARAMSETSAVED:   // source
   //
   //         switch( DupsStatus )
   //         {
   //            case DUPS_PARAMSETLOCKED:  //Destination
   //               break;
   //
   //            case DUPS_PARAMSETAVAIL:
   //               PresetClear(DUPS_FindCOP4DUPS(DupsPrstNum));
   //               break;
   //
   //            case DUPS_PARAMSETSAVED:
   //            // Saved to Saved. No changes occur.
   //               break;
   //
   //            default:
   //               break;
   //         }
   //         break;
   //
   //      default:
   //         break;
   //   }
   //
   //   DUPS_RAM2FRAM();
   //   for(cnt=0;cnt<DUPS_NUMPARAMSET;cnt++)
   //   DUPS_LockTemp[cnt] =  DUPS_Lock[cnt];

//} //End of function


void VGATestCheckSum(void)
/****************************************************************************/
/* VGA checksum Initiation function for VGA                                 */
/****************************************************************************/
{
   SINT32 temp;
   SINT32 temp1;
   SINT32 checksum;
   SINT32 checksum1 = 0;
   SINT32 x = 1000000;

   temp1 = BUCFactoryDefaults;
   checksum = (temp1 / 10000000);
   temp1 -= (checksum * 10000000);

   while (x >= 1) {
      temp = temp1 / x;
      checksum1 = checksum1 + temp;
      temp1 -= (temp * x);
      x = x / 10;
   }

    BUCFactoryDefaults -= (checksum * 10000000);
   if ((BUCFactoryDefaults != 0) && (checksum == checksum1))
      VGAChecksum = TRUE;
   else
      BUCFactoryDefaults = 0;

}

void VGAConfigureFromBUCMenu(void)
/****************************************************************************/
/* This function configure system settings based on a entered code          */
/*  XXABCDEF        XX is the checksum for all other digits                 */
/*        * A is the actuator type                                          */
/*          B is the power supply wattage                                   */
/*        * C is the actuator stroke length                                 */
/*        * D is the cylinder diameter                                      */
/*          E is the control level                                          */
/*          F&G is the power supply frequency                                 */
/*                                                                          */
/*  Note: If any item marked with an asterisk (*) is changed then all items */
/*        marked with an asterisk are updated.                              */
/*                                                                          */
/* The value returned in BUCFactoryDefaults will be xxxxRyyy where:         */
/*     xxxx is the number of times the novram was written to (390 or 391)   */
/*      yyy is the last location which failed the write test                */
/*        R is zero for now, but in the future may contain an indication    */
/*          if the novram has never been written to.                        */
/*                                                                          */
/****************************************************************************/
{
   SINT32 temp;
   UINT16 Data = 0;
   SINT32 checksum;
   CONFIGSETUP *FRAMPtr;
   UINT16 ChangeFlag = TRUE;
   BOOLEAN ActuatorChangeFlag = FALSE;
   BOOLEAN TestWriteDone = FALSE;

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   GlobalRetryCounter = 0;
   checksum = (BUCFactoryDefaults / 10000000);

   /**----------  Start of Actuator Type  ----------**/

   BUCFactoryDefaults -= (checksum * 10000000);
   temp = (BUCFactoryDefaults / 1000000);
   switch (temp) { /* actuator type */
   case 0: /* No change */
      ChangeFlag = FALSE;
      break;
   case 1: /* AED/AOD NOT SUPPORTED*/
      Data = NVR_AED;
      FRAMPtr->Actuator = AED;
      break;
   case 3: /* AED/AOD with Sbeam NOT SUPPORTED*/
      Data = NVR_AED;
      FRAMPtr->Actuator = AED;
      break;
   case 4: /* AEF with SBeam NOT SUPPORTED*/
      Data = NVR_AEF;
      FRAMPtr->Actuator = AEF;
      break;
   case 5: /* MICRO with Sbeam NOT SUPPORTED*/
      Data = NVR_MICRO;
      FRAMPtr->Actuator = MICRO;
      EnableUSEncoder();
      break;
   case 6: /* AES/ */
      Data = NVR_AES;
      FRAMPtr->Actuator = AES;
      break;
   case 7: /* MICROC */
	  Data = NVR_MICROC;
	  FRAMPtr->Actuator = MICROC;
	  FRAMPtr->LowerFlowValveFlag = TRUE;
	  CurrentSetup.LowerFlowValveFlag = FRAMPtr->LowerFlowValveFlag;
      break;
   case 8: /* AE/AO NOT SUPPORTED*/
   case 9: /* AE/AO NOT SUPPORTED*/
      Data = NVR_AE;
      FRAMPtr->Actuator = AE;
      break;
   }
   if (ChangeFlag == TRUE) {
      ActuatorChangeFlag = TRUE;
      CurrentSetup.Actuator = FRAMPtr->Actuator;
      if ( (FRAMPtr->Actuator == AED) ||(FRAMPtr->Actuator == AES) || (FRAMPtr->Actuator == MICRO) || (FRAMPtr->Actuator == MICROC) ) {
         TestWriteToNvram(); /* Erase everything currently in Novram */
         TestReadFromNvram();
         TestWriteDone = TRUE;
         SetActId(Data);
         if ((temp == 1) || (temp == 2))
            ConfigLoadcell();
         if ((temp == 3) || (temp == 4) || (temp == 5)|| (temp == 6)|| (temp == 7))
            ConfigSBeam();
      }
   } else
      ChangeFlag = TRUE;

   /**----------  Start of Wattage  NO LONGER USED  ----------**/

   /**----------  Start of Stroke length  ----------**/

   BUCFactoryDefaults -= (temp * 1000000);
   temp = (BUCFactoryDefaults / 100000);
   if (FRAMPtr->Actuator == MICRO)
   {
	  switch (temp) {
	  case 0: /*   No change */
			 ChangeFlag = FALSE;
			 break;
	  case 1: /*  50mm */
		     FRAMPtr->StrokeLen = LENGTH_50;
		     break;
	  default:
			 FRAMPtr->StrokeLen = CUSTOMLEN;
		     break;
	  }
   }
   else if (FRAMPtr->Actuator == MICROC)
   {
	  switch (temp) {
	  case 0: /*   No change */
		 ChangeFlag = FALSE;
		 break;
	  case 1: /* 70mm */
	     FRAMPtr->StrokeLen = LENGTH_70;
	     break;
	  case 2: /* 75mm */
		 FRAMPtr->StrokeLen = LENGTH_75;
		 break;
	  default:
		 FRAMPtr->StrokeLen = CUSTOMLEN;
	     break;
	  }
   }
   else if (FRAMPtr->Actuator == AED)
   {
	  switch (temp) {
	  case 0:
		 ChangeFlag = FALSE;
		 break;
   	  case 1: /*  4" */
	   	 FRAMPtr->StrokeLen = LENGTH_4;
      	 break;
   	  case 2: /*  5" */
	   	 FRAMPtr->StrokeLen = LENGTH_5;
      	 break;
   	  case 3: /*  6" */
	   	 FRAMPtr->StrokeLen = LENGTH_6;
      	 break;
   	  case 4: /*  7" */
	   	 FRAMPtr->StrokeLen = LENGTH_2;
      	 break;
   	  case 5: /*  80mm */
	   	 FRAMPtr->StrokeLen = LENGTH_80;
      	 break;
   	  case 6: /* 100mm */
	   	 FRAMPtr->StrokeLen = LENGTH_100;
      	 break;
   	  case 7: /* 125mm */
	   	 FRAMPtr->StrokeLen = LENGTH_125;
      	 break;
   	  case 8: /* 50mm */
	   	 FRAMPtr->StrokeLen = LENGTH_50;
      	 break;
   	  case 9: /* custom */
	   	 FRAMPtr->StrokeLen = CUSTOMLEN;
      	 break;
      default:
         break;
   	  }
   }
   else
   {
      switch (temp) { /* stroke length */
      case 0: /*  No change */
         if (TestWriteDone == TRUE) {
            FRAMPtr->StrokeLen = NVR.StrokeLength;
         } else {
            ChangeFlag = FALSE;
         }
         break;
      case 1: /*  4" */
         FRAMPtr->StrokeLen = LENGTH_4;
         break;
      case 2: /*  5" */
         FRAMPtr->StrokeLen = LENGTH_5;
         break;
      case 3: /*  6" */
         FRAMPtr->StrokeLen = LENGTH_6;
         break;
      case 4: /*  7" */
         FRAMPtr->StrokeLen = LENGTH_2;
         break;
      case 5: /*  80mm */
         FRAMPtr->StrokeLen = LENGTH_80;
         break;
      case 6: /* 100mm */
         FRAMPtr->StrokeLen = LENGTH_100;
         break;
      case 7: /* 125mm */
         FRAMPtr->StrokeLen = LENGTH_125;
         break;
      case 8: /* 50mm */
         FRAMPtr->StrokeLen = LENGTH_50;
         break;
      case 9: /* custom */
         FRAMPtr->StrokeLen = CUSTOMLEN;
         break;
      }
   }
   if (ChangeFlag == TRUE) {
      ActuatorChangeFlag = TRUE;
      if ( (FRAMPtr->Actuator == AED) ||(FRAMPtr->Actuator == AES) || (FRAMPtr->Actuator == MICRO) || (FRAMPtr->Actuator == MICROC) )
      {
         if (TestWriteDone == FALSE) {
            TestWriteToNvram(); /* Erase everything currently in Novram */
            TestReadFromNvram();
            TestWriteDone = TRUE;
            SetActId(Data);
         }
         SetStrokeLength(FRAMPtr->StrokeLen);
         SetDefStrokeLength(FRAMPtr->StrokeLen);
      } else /* no novram */
      {
         NVR.StrokeLength = FRAMPtr->StrokeLen;
         NVR.DefStrokeLength = FRAMPtr->StrokeLen;
      }
   } else
      ChangeFlag = TRUE;

   /**----------  Start of Cylinder diameter  ----------**/

   BUCFactoryDefaults -= (temp * 100000);
   temp = (BUCFactoryDefaults / 10000);
   if (FRAMPtr->Actuator == MICRO)
   {
	   switch (temp) {
	   case ZERO: /*   No change */
		 ChangeFlag = FALSE;
		 break;
	   case ONE: /*  40mm */
		 FRAMPtr->CylinDiameter = SIZE_40;
		 break;
	   default:
		 FRAMPtr->CylinDiameter = CUSTOMLEN;
		 break;
	   }
   }
   else if (FRAMPtr->Actuator == MICROC)
   {
	  switch (temp) {
	  case ZERO: /*   No change */
		 ChangeFlag = FALSE;
		 break;
	  case ONE: /* 32mm */
	     FRAMPtr->CylinDiameter = SIZE_32;
	     break;
	  case TWO: /* 40mm */
		 FRAMPtr->CylinDiameter = SIZE_40;
		 break;
	  default:
		 FRAMPtr->CylinDiameter = CUSTOMLEN;
	     break;
	  }
   }
   else
   {
      switch (temp) { /* cylinder diameter */
      case 0: /*   No change */
         if (TestWriteDone == TRUE) {
            FRAMPtr->CylinDiameter = NVR.CylSize;
         } else {
            ChangeFlag = FALSE;
         }
         break;
      case 1: /* 1.5" */
         FRAMPtr->CylinDiameter = SIZE1_5;
         break;
      case 2: /*   2"*/
         FRAMPtr->CylinDiameter = SIZE2_0;
         break;
      case 3: /* 2.5" */
         FRAMPtr->CylinDiameter = SIZE2_5;
         break;
      case 4: /*   3" */
         FRAMPtr->CylinDiameter = SIZE3_0;
         break;
      case 5: /* 3.25" */
         FRAMPtr->CylinDiameter = SIZE3_25;
         break;
      case 6: /*  40mm */
         FRAMPtr->CylinDiameter = SIZE_40;
         break;
      case 7: /*  50mm */
         FRAMPtr->CylinDiameter = SIZE_50;
         break;
      case 8: /*  63mm */
         FRAMPtr->CylinDiameter = SIZE_63;
         break;
      case 9: /*  80mm */
         FRAMPtr->CylinDiameter = SIZE_80;
         break;
      }
   }
   if (ChangeFlag == TRUE) {
      ActuatorChangeFlag = TRUE;
      if ( (FRAMPtr->Actuator == AED) || (FRAMPtr->Actuator == AES) || (FRAMPtr->Actuator == MICRO) || (FRAMPtr->Actuator == MICROC) ) {
         if (TestWriteDone == FALSE) {
            TestWriteToNvram(); /* Erase everything currently in Novram */
            TestReadFromNvram();
            TestWriteDone = TRUE;
            SetActId(Data);
            SetStrokeLength(FRAMPtr->StrokeLen);
            SetDefStrokeLength(FRAMPtr->StrokeLen);
         }
         SetCylSize(FRAMPtr->CylinDiameter);
         SetDefCylSize(FRAMPtr->CylinDiameter);
      } else /* no novram */
      {
         NVR.CylSize = FRAMPtr->CylinDiameter;
         NVR.DefCylSize = FRAMPtr->CylinDiameter;
      }
      CurrentSetup.CylinDiameter = FRAMPtr->CylinDiameter;
   } else
      ChangeFlag = TRUE;

   /**----------  Start of Control level  ----------**/

   BUCFactoryDefaults -= (temp * 10000);
   temp = (BUCFactoryDefaults / 1000);
   switch (temp) { /* control level */
   case 0: /* No change */
      ChangeFlag = FALSE;
      break;
   case 1: /*  t */
      FRAMPtr->ControlLevel = LEVEL_t;
      DepotFlag->IsADepot = FALSE;
      break;
   case 2: /*  e */
      FRAMPtr->ControlLevel = LEVEL_e;
      DepotFlag->IsADepot = FALSE;
      break;
   case 3: /*  ea */
      FRAMPtr->ControlLevel = LEVEL_ea;
      DepotFlag->IsADepot = FALSE;
      break;
   case 4: /*  d */
      FRAMPtr->ControlLevel = LEVEL_d;
      DepotFlag->IsADepot = FALSE;
      break;
   case 5: /*  f */
      FRAMPtr->ControlLevel = LEVEL_f;
      DepotFlag->IsADepot = FALSE;
      break;
   case 6: /* Depot (t internal) */
      FRAMPtr->ControlLevel = LEVEL_t;
      DepotFlag->WasADepot = TRUE;
      DepotFlag->IsADepot = TRUE;
      break;
   case 7: /* a */
      FRAMPtr->ControlLevel = LEVEL_a;
      DepotFlag->IsADepot = FALSE;
      break;
   case 8: /* c */
      FRAMPtr->ControlLevel = LEVEL_c;//LEVEL_t;
      DepotFlag->IsADepot = FALSE;
      break;
   case 9: /* test */
      FRAMPtr->ControlLevel = LEVEL_TEST;
      DepotFlag->IsADepot = FALSE;
      break;
   }
   if (ChangeFlag == TRUE) {
      CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
      StorePSControlLevel();
      GetControlLevel();
   } else
      ChangeFlag = TRUE;

   // Set Encoder Type in case its a Micro Actuator
   if (ActuatorChangeFlag == TRUE) {
      if (FRAMPtr->Actuator == MICRO) {
         SetEncoderType(ENCODER_ENGLISH);//2000X micro std prod
      }
   }
   /**----------  Start of Frequency  NO LONGER USED  ----------**/

   /**----------  Start of Wattage  ----------**/

   temp = BUCFactoryDefaults % 100;
   if (temp) FRAMPtr->PSWatt = temp * 100;
   CurrentSetup.PSWatt = FRAMPtr->PSWatt;
   StorePSWattage();

   GetSerialNumbers();

   if (ActuatorChangeFlag == TRUE)
   {
      if ( (FRAMPtr->Actuator == AED) ||(FRAMPtr->Actuator == AES) || (FRAMPtr->Actuator == MICRO) || (FRAMPtr->Actuator == MICROC) )
      {
         SetDefSerNum((UINT8*)&FRAMPtr->ActSerialNumber);
      }
   }
   ChkSumCompleteFlag = TRUE;
}

void VGADebugColdStart(void)
/****************************************************************************/
/* VGA coldstart after checksum Initialization                              */
/****************************************************************************/
{
   CONFIGSETUP *FRAMPtr;

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

   /*  Here starts a bunch a things that need to be done whenever configuration takes place */

   ColdStartPlus();

   /*  Here we are going to output a bunch of stuff all squeezed into the BUCFactoryDefaults for display */

   if ((FRAMPtr->Actuator == AED) ||(FRAMPtr->Actuator == AES) || (FRAMPtr->Actuator == MICRO) || (FRAMPtr->Actuator == MICROC))
      BUCFactoryDefaults = ChecksumRet + (GlobalRetryCounter * 10000); /* All is okay */
   else
      BUCFactoryDefaults = 10000000;

   GetPowerSupplyInfo();
   NextMenuFlag = TRUE;
}

void ResetHornScanValue(void)
/****************************************************************************/
/* Put Default Values for horn scan parameters                              */
/****************************************************************************/
{
   HornScanInfo. MaximumAmplitude = HS_MinScanInfo. MaximumAmplitude;
   HornScanInfo. MaximumCurrent = HS_MinScanInfo. MaximumCurrent;
   switch (CurrentSetup.PSFreq) {
   case FREQ15KHZ:
      HornScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      HornScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MaxScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MaxScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MinScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      HS_MinScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      break;
   case FREQ20KHZ:
      HornScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      HornScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MaxScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MaxScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MinScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      HS_MinScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      break;
   case FREQ30KHZ:
      HornScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      HornScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MaxScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MaxScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX15AND30);
      HS_MinScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      HS_MinScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MIN15AND30);
      break;
   case FREQ40KHZ:
   default:
      HornScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      HornScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MaxScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MaxScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MAX20AND40);
      HS_MinScanInfo. StartFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      HS_MinScanInfo. StopFreq = DUPS_FreqD2C(DUPS_MIN20AND40);
      break;
   }
   HornScanInfo. TimeDelay = HS_MinScanInfo. TimeDelay;
   //   HornScanInfo. FreqStep         =  DUPS_FreqD2C(HS_MinScanInfo. FreqStep);
   HornScanInfo.FreqStep = HS_MinScanInfo.FreqStep;
}

