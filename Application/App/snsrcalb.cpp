/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/snsrcalb.cpp_v   1.33   Nov 16 2017 16:20:56   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/snsrcalb.cpp_v  $
 * 
 *    Rev 1.33   Nov 16 2017 16:20:56   RJamloki
 * Updated 20% down speed comments
 * 
 *    Rev 1.32   Nov 06 2017 16:27:14   RJamloki
 * Code review update compact code and remove dead code
 * 
 *    Rev 1.31   Oct 10 2017 13:53:46   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.30   14 Oct 2016 10:23:22   RJamloki
 * Assing fix to version release v12.2
 * 
 *    Rev 1.29   05 Oct 2016 09:47:50   RJamloki
 * Cylinder 1.5" fix increase pressure when flow valve is open 100%
 * 
 *    Rev 1.28   01 May 2015 09:32:24   ygupta
 * Modified VGABUildForceTable to have MICRO actuator use NumberOfLoadCellPoints as 2 instaed of 3 as the calibration is off in case of 3.
 * 
 *    Rev 1.27   09 Apr 2015 05:28:20   RJamloki
 * Fix for recal 990..Made InitForceEstimateBuffer true at places where Partcontact flag is getting initialized to false
 * 
 *    Rev 1.26   27 Mar 2015 11:10:50   amaurya
 * DoorOpen Removed
 * 
 *    Rev 1.25   13 Mar 2015 06:09:10   amaurya
 * Making StartingSensorCal flag false to reenable inaccurate pressure alarms.
 * 
 *    Rev 1.24   03 Feb 2015 07:22:50   amaurya
 * BuildDefaultSpringRate() changed.
 * 
 *    Rev 1.23   08 Jan 2015 06:21:48   AnPawar
 * in CalibFinalCleanup function changing setflowvalue based on preset is tuned or not
 * 
 *    Rev 1.22   28 Nov 2014 07:40:50   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.21   10 Nov 2014 04:59:32   AnPawar
 * CalibFinalCleanup() function changed.
 * 
 *    Rev 1.20   06 Oct 2014 11:50:26   rjamloki
 * Removed BuildPVTTable function and force table update.
 * 
 *    Rev 1.19   06 Oct 2014 06:45:22   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.18   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.17   11 Sep 2014 11:09:40   rjamloki
 * Added Coverity fix and calibration events
 * 
 *    Rev 1.16   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.15   07 Aug 2014 15:41:56   tayars
 * Change for flow lookup
 * 
 *    Rev 1.14   28 Jul 2014 12:52:10   rjamloki
 * added authority check on sensor calibration, removed redundant table updated during calibration
 * 
 *    Rev 1.13   09 Jul 2014 11:39:32   rjamloki
 * Added Authority check on Act Calibration. Removed Load cell support.
 * 
 *    Rev 1.12   20 Jun 2014 14:24:46   rjamloki
 * Added support for AES Pressure and Force Calibration
 * 
 *    Rev 1.11   16 Jun 2014 08:51:42   rjamloki
 * Merged changes from vgasensorcalib.cpp and vgacalib.cpp.
 * 
 *    Rev 1.10   11 Jun 2014 12:07:50   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:48:12   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:41:22   rjamloki
 * coverity fixes
 * 
 *    Rev 1.7   23 Apr 2014 13:50:24   akaushal
 * Checking boundary condition for ForceV and DistanceV arrays
 * 
 *    Rev 1.6   26 Mar 2014 12:34:56   rjamloki
 * DisplayNextScreen(),TestTimer(),ExitCalWait(),CalExitPB() function changed
 * 
 *    Rev 1.5   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:44   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:52   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION -----------------------------
                                                                          
 Module name: Sensor Calibration                                          
                                                                          
 Filename:    Snsrcalb.c                                                   
                                                                          
 Function Name: Calibration code                                          
                                                                          
          Written by:   Bill Truchsess                                    
                Date:   04-15-96                                          
            Language:   "C"                                               
  ----------------------------------------------------------------------------*/



/*----------------------------- DESCRIPTION --------------------------------*/


/*  This module includes the support functions for the sensor calibration.  */
/*  The calibration can be aborted, pass, or failed.                        */



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define INCLUDE_UNIT_TEST
#define MAX_TABLE_PTS          (10+1)
#define MAXCALIBRATIONERROR    20
#define NOVRAMFAILED           (EQ10&(~EQG1))   /* BIT10 of equipment failure */
#define SPRINGRATEINDEX        0x800   /* 0.2048 in */
#define CALIBRATION_TIMER      3000    /* 3 secs */
#define COUNTS_PER_INCH        10000
#define MAXDISTANCEERROR       400
#define CALBAVESIZE            16
#define LC_DELAY               15000   /* 15 secs */
#define INIT_PV_DELAY          2000    /* 2 secs */
#define PSI_RANGE              40      /* +/- 4PSI */
#define FORCE_RANGE            30      /* +/- 3 lbs */
#define FORCE_ACCURACY_RANGE   10      /* +/- 1 lbs */
#define SPRINGRATE_RANGE       3       /* 3 A/D counts/ 0.2048in */
#define KPA_CONVERT            6.69    /* convert PSI */
#define NEWTON_CONVERT         4.448
#define MINIMUM_FORCE          10
#define ROUNDING_CORRECTION    10
#define OFF_THE_PART           100     /* 0.0100 in. off the part */
#define SPRINGRATE_TIMEOUT     9000    /* 9 seconds assume part contact */
#define PSI_CORRECTION         100     /* correct for table offset */
#define MIN_AD_LOADCELL        0       // was 500     /* minimum value before spring rate calculated */
#define MAX_AD_LOADCELL        3000    /* maximum value */
#define MINIMUM_NUMBER         2       /* need at least 3 points to generate a springrate */
#define SPRING_RATE_AVERAGE    3       /* average last 4 points to extend springrate table*/
#define MIN_STROKE_LEN         6145
#define ONE_SECOND             1000
#define DOWNSPEEDTIMEOUT       350
#define DEF_HORNWEIGHTLC       350 /* typical hornweight value loadcell*/
#define DEF_HORNWEIGHTSB       160 /* typical hornweight value sbeam*/
#define MINDOWNSPEED           3
#define MAXDOWNSPEED           99
#define LEAVINGHOMEFORCE       12
#define LEAVINGHOMEFORCE15KHZ  36
//#define LEAVINGHOMEFORCEMICRO  03
#define ONE_POSITION           2048
#define ONE_INCH               10000
#define FORCE_ON_THE_PART      250  /* 25lbs */
/*  equations used to calculate the Velocity table entries 
              LOW_60PSI + ((HIGH_60PSI - LOW_60PSI)*1)/256 = 45219
              LOW_60PSI + ((HIGH_60PSI - LOW_60PSI)*100)/256 = 15728
    to calculate entries for 80PSI use 59637 and 30146 in the above equation
*/

#define CAL_DOWNSPEED         	20     		/* calibrate sensors at 20% downspeed */
#define PSIALLOWED             	3     	 	/* 3PSI */
#define PSI2DAC               	(65535.0/90.0)
#define RATIOMETRICITY 			1.25   		/* per load cell spec sheet */
#define LCSENSITIVITY 			0.020   	/* volts per psi per load cell spec sheet */
#define VOLTSPERBIT 			0.004883  	/* 10 volts divided by 2048 */
#define PI 3.141593
#define SPRINGRATE       		5.6  		/* 5.6  lbs per inch */
#define SPRINGRATEMICRO  		6.5  		/* 6.5  lbs per inch */
#define SPRINGRATEMICROC 		3.75  		/* 3.75 lbs per inch */
#define CALIBRATION_IDLE_VALUE 	80
#define LBSPERCNT 				0.432
#define GREATERTHENNOISE 		2
#define PRESSURE_CALIB 			1
#define FORCE_CALIB	   			2

/*------------------------------ INCLUDES ----------------------------------*/

#define SNSRCALB 
#include "qdef.h"
#include <stdlib.h>
#include "names.h" 
#include "alarms.h" 
#include "interpol.h"
#include "wldstate.h"
#include "preset.h"
#include "beep.h"
#include "string.h"
#include "rtclock.h"
#include "ready.h"
#include "keypad.h"
#include "digout.h"
#include "getmsg.h"
#include "selctkey.h"
#include "spidd.h"
#include "actnvram.h"
#include "FrontPanelKeypadTask.h"
#include "param.h"
#include "mansensr.h"
#include "menucalb.h"
#include "genrlmsg.h"
#include "statedrv.h"

#include "util.h"
#include "snsrcalb.h"
#include "SystemManagerTask.h"
#include "sc.h"
#include "state.h"
#include "weld_obj.h"

#include "qsm.h"
#include "menu.h"
#include "menu7a.h"
#include "encoder.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "WeldManagerTask.h"
#include "RVTSHandlerTask.h"
#include "Events.h"
#include "ticks.h"
#include "FlowLookupTable.h"

/*------------------------------ GLOBAL DATA -------------------------------*/
/*                       (scope is global to ALL files)                     */

SINT16 CalTimer;
UINT16 TimerLoopCounter;
UINT16 CalibrationPassed;
UINT16 SpringRateTimeout;
UINT16 UpdateCalbAve = 5;
UINT16 CalbAveIndex = 0;
UINT16 MicroHomeForce;
BOOLEAN CalTimerFlag;
extern SINT16 ForceTableDelta;
CALIBSTAGE ForceCalibrationEventFlag = CALIBRATION_SAVED;
BOOLEAN PlsWaitTimerFlag;                   /* Please Wait Timer Flag */
BOOLEAN AdvanceMenuFlag = FALSE;
SINT32 DistanceV[MAX_VECTOR_SIZE];
SINT32 ForceV[MAX_VECTOR_SIZE];
SINT32 ForceVcnts[MAX_VECTOR_SIZE];
SINT32 AdCntsLC[MAX_VECTOR_SIZE];
SINT32 PVDacCnts[MAX_VECTOR_SIZE];
SINT16 PVPCountsLb;
SINT16 LCCountsLb;
SINT16 TempPressureTable[MAX_CAL_PTS] ;
SINT32 TempForceTable[MAX_CAL_PTS] ;
SINT16 TempLoadCellTable[MAX_CAL_PTS] ;
UINT16 TempSpringRateTable[SPRING_RATE_SIZE] ;
UINT16 NoPressureFlag = TRUE;
UINT16 RawPVPValue;
SINT32 AdCntsPSI[3];
double  SpringRateSlope;
UINT16 CheckDownSpeed = 0; 
BOOLEAN VGACalAllowed = FALSE;
BOOLEAN VGASnsrCalibAllowed = FALSE;
const SINT32 Velocity60PSI3in[] = {LOW_60PSI, HIGH_60PSI};
const SINT32 Velocity60PSI2in[] = {49250, -16333}; /* values for restrictor verified on AEF # 6*/

const UINT16 MICRODefSpringRate[]={312,323,331,340,348,357,365,374,382,390,
								   398,406,414,422,430,438,446,454,462,470,
								   478,486,494,502,510,518,526,534,542,550,
								   558,566,574,582,590,598,606,614,622,630};

SINT32 CalibrationStep = PRESSURE_CALIB;
extern UINT16 Mode;
/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */


static SINT16 TemporaryCalSysPressure;
static GENERIC_MSG WeldMsgOut;
static UINT16 PVControlSignal;
static UINT16 CollectForceDataDelay;
static UINT16 CollectForceDataIndex;
static SINT32 TempTriggerForce;
static WELD_STATE_MSG calbmsg;
extern UINT32 CalbAve[];
static UINT16 AvePressure[CALBAVESIZE];
static UINT32 TemporaryCalStrokeLen;

/* structure used by LinearReg function */
struct Regression {
       double  slope;
       double  intercept;
       double  variance;
       } ;

extern UINT32 CurrentVelocity;
extern UINT16 PartContactFlag;
extern SINT32 HomePressure;
extern UINT8  MainKeyFlag;
extern BOOLEAN SpringRateComplete;
extern UINT16  ADForce,ADPressure;
extern SINT16 LoadCellIndex;
extern enum WELDSTATES WeldState;

extern INBITS Inp;

extern SINT32  UserPressure[3];
extern SINT32  EncoderPos;
extern SINT32  CurrentForce;
extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT32 CalbAve[];
extern BOOLEAN VGASnsrCalibAllowed;
extern UINT8 MenuNxtPointer;
void CheckforCalib (void);

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

void CheckForNoPressure(void);
struct Regression LinearReg(SINT32* x, SINT32* y, UINT16 n);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);

/*-------------------------------- CODE ------------------------------------*/

void PressureCalibrationInit(void)
/****************************************************************************/
/*                                                                          */
/* This function is called if calibration is allowed. This initializes the  */
/* calibrate pressure sensor variables. All outputs are set to there initial*/
/* conditions                                                               */
/*                                                                          */
/* Inputs :  StrMX_26                                                       */
/*           NVR.PressureTable                                              */
/*                                                                          */
/* Outputs : PassFailStr - displayed when pressure sensor calibration fails */
/*           AdvanceMenuFlag - used to keep the menu task in sink with the  */
/*                             calibration state machince                   */
/*           SpringRateTimeout - Timeout used if part contact not made      */
/*           TempPressureTable - save last pressure table incase calibration*/
/*                               is aborted                                 */
/*           CalibrationPassed - assume calibration will be aborted         */
/*                                                                          */
/****************************************************************************/
{

   UINT16 Index;
   CalibrationStep = PRESSURE_CALIB;
   Mode = STARTSWITCHES;
   UserPressure[0] = 0; /* Set illegal for later verification        */
   UserPressure[1] = 0; /* Set illegal for later verification        */
   UserPressure[2] = 0;

   AdvanceMenuFlag = FALSE;
   CalibrationPassed = CAL_ABORTED; /* assume calibration will be aborted */

   InitPressureCalMenus();
   SelectPressureCalSequence(); /* Initialize State Sequence for Calibration */

   for (Index = 0; Index < MAX_TABLE_PTS; Index++)
      TempPressureTable[Index] = NVR.Pressure[Index];
   NoPressureFlag = TRUE;
   GetDefPressure(); /* Update pressure with defaults */
}

void ForceCalibrationInit(void)
/****************************************************************************/
/*                                                                          */
/* This function is called if calibration is allowed. This initializes the  */
/* calibrate Force sensor variables. All outputs are set to there initial   */
/* conditions                                                               */
/*                                                                          */
/* Inputs :  StrMX_26                                                       */
/*           NVR.LoadCell                                                   */
/*           NVR.Force                                                      */
/*                                                                          */
/* Outputs : PassFailStr - displayed when pressure sensor calibration fails */
/*           AdvanceMenuFlag - used to keep the menu task in sink with the  */
/*                             calibration state machince                   */
/*           SpringRateComplete - Flag set when part contact is made        */
/*           PlsWaitTimerFlag - used to advance the state machine           */
/*           ForceV[1] - second entered loadcell reading             */
/*           LCADcnts[1] - second A/D reading from the loadcell     */
/*           NoPressureFlag - used to abort calibration when there is no    */
/*                            pressure                                      */
/*           TimerLoopCounter - used to wait for first loadcell point to    */
/*                              settled out                                 */
/*           SpringRateTimeout - Timeout used if part contact not made      */
/*           TempLoadCellTable - save last loadcell table incase calibration*/
/*                               is aborted                                 */
/*           TempForceTable - save last force table in case calibration is  */
/*                               aborted                                    */
/*           CalibrationPassed - assume calibration will be aborted         */
/*                                                                          */
/****************************************************************************/
{

   UINT16 Index;
   CalibrationStep = FORCE_CALIB;
   CheckDownSpeed = 0;
   ForceTableDelta = 0;
   CurrentVelocity = 0;
   NoPressureFlag = TRUE;
   TimerLoopCounter = INIT_PV_DELAY;
   PartContactFlag = FALSE;
   InitForceEstimateBuffer = TRUE;
   AdvanceMenuFlag = FALSE;
   SpringRateComplete = FALSE;
   PlsWaitTimerFlag = TRUE; /* Please Wait Timer Flag */
   SpringRateTimeout = 0;
   CalibrationPassed = CAL_PASSED; /* assume calibration will be aborted */
   ForceCalibrationEventFlag = CALIB_INIT;   
   Mode = STARTSWITCHES;
   InitForceCalMenus();
   SelectForceCalSequence(); /* Initialize State Sequence for Calibration */

   /* Save current tables in case of failure */
   GetDefSpringRateTable(); /* save current springrate table */

   for (Index = 0; Index < MAX_TABLE_PTS; Index++)
      TempLoadCellTable[Index] = NVR.LoadCell[Index];
   for (Index = 0; Index < FORCE_TABLE_SIZE; Index++)
      TempForceTable[Index] = NVR.Force[Index];

   GetDefLoadCell();
   GetDefForce();

   TempTriggerForce = RunningPreset.TriggerForce;
   RunningPreset.TriggerForce = MinLimit.TriggerForce;
}


void GetDefSpringRateTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Save springrate table in case calibration is aborted. Called when the    */
/* calibration sequence is initialized                                      */
/*                                                                          */
/* Inputs : CurrentSetup.SpringRateTable                                    */
/*                                                                          */
/* Outputs : TempSpringRateTable                                            */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;

   for(Index = 0; Index < SPRING_RATE_SIZE; Index++){
      TempSpringRateTable[Index] = CurrentSetup.SpringRateTable[Index];
   }
}


void BuildDefaultSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when a checksum is done, an upgrade is done, and */
/* when Actuator cold start is done                                         */
/*                                                                          */
/* Inputs : ADForce                                                         */
/*          CurrentSetup.GainFactor                                         */
/*                                                                          */
/* Outputs : CurrentSetup.SpringRateTable                                   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;
   UINT32 Distance = 0;
   UINT16 LeavingHomeForce;

   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) || (CurrentSetup.Actuator == MICRO)) { /* and we have an encoder (AED,aes)       */
      CurrentSetup.SpringRateTable[0] = ADForce;
   } 
   else
      CurrentSetup.SpringRateTable[0] = DEF_HORNWEIGHTSB;
   
   if(CurrentSetup.Actuator == MICRO || CurrentSetup.Actuator == MICROC)
      LeavingHomeForce = MicroHomeForce;
   else
   {
      switch (CurrentSetup.PSFreq) {
         default:
         case FREQ20KHZ:
         case FREQ40KHZ:
         case FREQ30KHZ:
         case FREQ60KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE;
         break;

         case FREQ15KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE15KHZ;
         break;
      }
   }

   /* convert SpringRateSlope to a double in case the stroke was not long enough or */
   /* a cal actuator is performed to update for a new horn weight                 */
   SpringRateSlope = (double)NVR.SpringRateSlope / 1024.0;
   SpringRateSlope /= 10000.0; /* Adjust for 1/10000 units */

   /* Calculate Default Spring Rate Table. */
      for(Index = 1; Index < SPRING_RATE_SIZE; Index++)
      {
         Distance = Distance + SPRINGRATEINDEX;
         CurrentSetup.SpringRateTable[Index] = CurrentSetup.SpringRateTable[0]
              + (UINT16)(SpringRateSlope *(double)Distance) + LeavingHomeForce;
      }
   
   UpdateCurrentPreset(SAVECURRENTSETUP,0,0);  /* save springrate to BBram */
}


void UpdateNVRSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when a checksum is done or an upgrade is done    */
/*                                                                          */
/* Inputs : ADForce                                                         */
/*          CurrentSetup.GainFactor                                         */
/*                                                                          */
/* Outputs : NVR.CalHomeOffset                                              */
/*           NVR.DefCalHomeOffset                                           */
/*                                                                          */
/****************************************************************************/ 
{
   
   NVR.CalHomeOffset = ADForce;
   SetCalHomeOffset();
   NVR.DefCalHomeOffset = ADForce;
   SetDefCalHomeOffset();
   SpringRateSlope = RATIOMETRICITY*(LCSENSITIVITY/PI)*
                             (((double)CurrentSetup.GainFactor/1000.0)/VOLTSPERBIT);

   if(CurrentSetup.Actuator == MICRO)
   {
      SetDefSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICRO));
      SetCalSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICRO));
   }
   else if(CurrentSetup.Actuator == MICROC)
   {
	  SetDefSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICROC));
	  SetCalSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICROC));
   }
   else
   {
      SetDefSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATE));
      SetCalSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATE));
   }

}



void BuildPressureTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Called from menu system after entering the third pressure value. It takes*/
/* takes the three pressure values and their corresponding A/D values and   */
/* builds a pressure table.                                                 */
/*                                                                          */
/* Inputs : UserPressure[] - 3 pressure sensor readings                     */
/*          AdCntsPSI[]    - 3 corresponding A/D readings                   */   
/*                                                                          */
/* Outputs: NVR.Pressure - update                                           */
/*          CalibrationPassed                                               */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index, PressureAverage;
   double TBLStep;
   /* structure used by LinearReg function */
   struct Regression Reg;

   CalibrationPassed = CAL_PASSED;

      /* Get A/D average for 3rd A/D reading */
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
     PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsPSI[2] = (SINT32)PressureAverage;

      /* Get best fit to 3 pressure points */
   Reg = LinearReg(AdCntsPSI, UserPressure, 3);

      /* Build table to be used with processor's interpolation instructions. */
      /* This requires an x-axis table step of 256. */
   TBLStep = 0.0;
   for(Index = 0; Index < MAX_TABLE_PTS; Index++)
   {
      NVR.Pressure[Index] = (SINT16)(TBLStep*Reg.slope+Reg.intercept);
      TBLStep += 256.0;
   }      
      /* Set illegal for later verification */
   UserPressure[0] = UserPressure[1] = 0;
   VerifyPressureTable();
}


STR FailedByValue[VGA_LINESIZE];

void VerifyPressureTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Pressure table must be within +/- 2 PSI                                  */
/*                                                                          */
/* Inputs : HomePressure                                                    */
/*          UserPressure[2]                                                 */
/*          CurrentSetup.Units                                              */
/*                                                                          */
/* Outputs : CalibrationPassed                                              */
/*           PassFailStr                                                    */
/*           UserPressure[2]                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 ErrorValue, TensPlace;
   UINT8 TempVal;
   SINT8 TempStr[10];

   UpdateKeyMask(CALMODEMASK);
   if(CalibrationPassed != CAL_ABORTED)
   {
      if((HomePressure < (UserPressure[2] - PSI_RANGE)) ||
         (HomePressure > (UserPressure[2] + PSI_RANGE)))
      {
         CalibrationPassed = CAL_FAILED;

         if(HomePressure < UserPressure[2])
         {
            StrCpyTwoBytes(FailedByValue, "-");
            ErrorValue = UserPressure[2] - HomePressure;
         }
         else
         {
            StrCpyTwoBytes(FailedByValue, "+");
            ErrorValue = HomePressure - UserPressure[2];
         }
         if(CurrentSetup.Units == TRUE)      /* convert value to metric */
         {
            ErrorValue = (UINT16)((double)ErrorValue * KPA_CONVERT);
         }
         if(ErrorValue < 100)
         {
            StrCatTwoBytes(FailedByValue, " ");
            TempVal = 0x30 + (ErrorValue/10);
            sprintf(TempStr, "%d", TempVal);
               StrCatTwoBytes(FailedByValue, TempStr);
         }
         else
         {
            if(ErrorValue > 999) ErrorValue = 999; /* there is only 2 places for the error */
               TensPlace = ErrorValue/100;
            TempVal = 0x30 + (ErrorValue / 100);
            sprintf(TempStr, "%d", TempVal);
            StrCatTwoBytes(FailedByValue, TempStr);
            TempVal = 0x30 + ((ErrorValue - (TensPlace * 100)) / 10);

            sprintf(TempStr, "%d", TempVal);
            StrCatTwoBytes(FailedByValue, TempStr);
         }
         if(CurrentSetup.Units == TRUE)      /* convert value to metric */
         {
            StrCatTwoBytes(FailedByValue, "k");
            StrCatTwoBytes(FailedByValue, "p");
            StrCatTwoBytes(FailedByValue, "a");
         }
         else
         {
            StrCatTwoBytes(FailedByValue, "P");
            StrCatTwoBytes(FailedByValue, "S");
            StrCatTwoBytes(FailedByValue, "I");
         }
      }   
      else
      {
		 CalibrationPassed = CAL_PASSED;   /* continue to loadcell calibration */
         SaveCalibPressure();
         WeldMsgOut.common.opcode = OP_NVM_WRITE_PRESSURE_PARAMETERS;  /* update to actnvram */
		 SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldMsgOut), 20);
      }
      UserPressure[2] = 0;    /* Set illegal for later verification        */
      DisplayNextScreen();
   }
   StrCatTwoBytes(FailedByValue, '\0');
}



void BuildVelocityTable(void)
/****************************************************************************/ 
/*                                                                          */
/* This function updates the velocity table with default values. It is      */
/* called from MFG25 and the BUC menu factory default setting               */
/*                                                                          */
/* Inputs : NVR.CylSize                                                     */
/*                                                                          */
/* Outputs : CurrentSetup.VelocityTable                                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   if(NVR.CylSize == SIZE3_0)
   {
      CurrentSetup.VelocityTable[0] = Velocity60PSI3in[0];
      CurrentSetup.VelocityTable[1] = Velocity60PSI3in[1];
   }
   else /* use 2in table for all other cylinder sizes for Ver 7 */
   {
      CurrentSetup.VelocityTable[0] = Velocity60PSI2in[0];
      CurrentSetup.VelocityTable[1] = Velocity60PSI2in[1];
   }

}

void VGABuildForceTable(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the third force value is entered. It is     */
/* called from within the menu task. It takes the three actual force values */
/* and three corresponding A/D values and builds a table.                   */
/*                                                                          */
/* Inputs : NVR.LoadCell                                                    */
/*          ForceV[]                                                        */
/*          AdCntsLC[]                                                      */
/*                                                                          */
/* Outputs : NoPressureFlag                                                 */
/*           CalibrationPassed                                              */
/*           NVR.LoadCell                                                   */
/*           ForceV[]                                                       */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
	UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
	double  TBLStep;
	UINT16 NumberOfLoadCellPoints;
	UINT16 Index;
	struct Regression Reg;
	RTCTime RTCCal;
   if(CalibrationPassed != CAL_ABORTED)
   {
      UpdateKeyMask(CALMODEMASK);
      ReadA2D2(0);
      CalibrationPassed = CAL_PASSED;

      if ((CurrentSetup.Actuator==AED) || (CurrentSetup.Actuator == AES)||(CurrentSetup.Actuator == MICRO)||(CurrentSetup.Actuator == MICROC))
         NumberOfLoadCellPoints = 2;
      else 
         NumberOfLoadCellPoints = 3;
         
      /* Get best fit to 3 force values */
      Reg = LinearReg(AdCntsLC, ForceV, NumberOfLoadCellPoints);

      /* Build table to be used with processor's interpolation instructions. */
      /* This requires an x-axis table step of 256. */
      TBLStep = 0.0;
      for(Index=0; Index<MAX_CAL_PTS; Index++)
         {
            /* added offset to the loadcell table */
            NVR.LoadCell[Index] = (SINT16)(TBLStep*Reg.slope +(SINT16)Reg.intercept) + LoadCellOffset;
            TBLStep += 256.0;
         }

      /* Interpolate force values for collected D-to-A values */
      for(Index=0; Index<MAX_CAL_PTS; Index++)      
         /* do not have offset in when generating the PV table */
         ForceV[Index] = (GetInterpolatedSINT16(NVR.LoadCell, ForceVcnts[Index]) - LoadCellOffset);
      NoPressureFlag = TRUE;
      
      /* need to update the calibrated pressure and stroke length */
      NVR.CalSysPressure = TemporaryCalSysPressure;
      NVR.CalStrokeLen = TemporaryCalStrokeLen;
      /* need to clear the horn weight offset */
      CurrentSetup.HornWeightOffset = 0;
      SVOff();
      RTClock::GetCurrentTime(&RTCCal);    /* Get date when calibration complete */
      DateArray[0] = RTCCal.Century_Month;
      DateArray[1] = RTCCal.Day;
      DateArray[2] = RTCCal.Years;
      SetCalibrationDate(DateArray);     
      SetCalibPass((UINT16) CALIBPASSED);
      UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);
      ForceCalibrationEventFlag = CALIBRATION_END;
      WeldMsgOut.common.opcode = OP_NVM_WRITE_FORCE_PARAMETERS;  /* update to actnvram */
      SystemManagerTask::thisPtr->SysMNGRTaskQ.WriteRetry(0, *((SYSM_MSG_QUEUE_TYPE*) &WeldMsgOut), 20);
   }  
}

void SaveCalibPressure(void){
/****************************************************************************/ 
/*                                                                          */
/* This function is called from CalForceMenu5B. It will save the averaged   */
/* pressure at home.                                                        */
/*                                                                          */
/* Inputs :                                                                 */
/*                                                                          */
/* Outputs : TemporaryCalSysPressure                                        */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;    /* divide by array length */

   TemporaryCalSysPressure = GetInterpolatedSINT16(NVR.Pressure,PressureAverage);
   NVR.CalSysPressure = TemporaryCalSysPressure;
}


void CalibFinalCleanup(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration is complete or aborted. It will */
/* either restore the old values on a fail or abort condition. Or it if     */
/* passes update the calibration tables.                                    */
/*                                                                          */
/* Inputs : CalibrationPassed                                               */
/*          TempSpringRateTable                                             */
/*          TempPressureTable                                               */
/*          TempLoadCellTable                                               */
/*          TempForceTable                                                  */
/*          TempTriggerForce                                                */
/*          MainKeyFlag                                                     */
/*                                                                          */
/* Outputs : DateArray                                                      */
/*           CurrentSetup.SpringRateTable                                   */
/*           NVR.Pressure                                                   */
/*           NVR.LoadCell                                                   */
/*           NVR.Force                                                      */
/*           CalibrationPassed                                              */
/*                                                                          */
/****************************************************************************/
{
	UINT16 Index;
	UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
	RTCTime RTCCal;
	UINT16 CalibStatus = CalibrationPassed;
	if (CalibrationPassed != CAL_NOT_ALLOWED) {
		SVOff(); /* Turn off SV to bring hown up      */
		RunningPreset.TriggerForce = TempTriggerForce;
		SelectWeldSequence(); /* Restore proper weld sequence*/
		StartStateMachine();
		if (CalibrationPassed == CAL_PASSED) {
			ClearCalibrationAlarms(); /* Clear any Calibration alarms      */
			SetReady();
		} else if (CalibrationPassed == CAL_ABORTED) { /* restore calibration tables */
			if (CalibrationStep == PRESSURE_CALIB) {
				for (Index = 0; Index < MAX_TABLE_PTS; Index++) {
					NVR.Pressure[Index] = TempPressureTable[Index];
				}
			} else {
				for (Index = 0; Index < SPRING_RATE_SIZE; Index++) {
					CurrentSetup.SpringRateTable[Index]
							= TempSpringRateTable[Index];
				}
				for (Index = 0; Index < MAX_TABLE_PTS; Index++) {
					NVR.LoadCell[Index] = TempLoadCellTable[Index];
				}
			}
		} else { /* Load defaults when calibration fails */
			RTClock::GetCurrentTime(&RTCCal); /* Get date when calibration complete */
			DateArray[0] = RTCCal.Century_Month;
			DateArray[1] = RTCCal.Day;
			DateArray[2] = RTCCal.Years;

			SetCalibrationDate(DateArray);
			SetCalibPass((UINT16) CALIBFAILED);
			if (CalibrationStep == PRESSURE_CALIB)//Get Default Pressure table in case of Pressure calib Fail
				GetDefPressure();
			else {//Get Default Loadcell and Force table in case of force calib Fail
				GetDefLoadCell();
				GetDefForce();
			}
		}
		/*Only Records an Event if Calibration passed or failed*/
		if (CalibrationStep == FORCE_CALIB) {
			if (((CalibStatus == CAL_PASSED) || (CalibStatus == CAL_FAILED))
					&& (ForceCalibrationEventFlag == CALIBRATION_END)) {
				EventParameterID = FORCE_CALIBRATION_PARAMID;
				RecordEvents(EVENT_CALIBRATION, CalibStatus, 0);
				ForceCalibrationEventFlag = CALIBRATION_SAVED;
			}
		} else {
			if ((CalibStatus == CAL_PASSED) || (CalibStatus == CAL_FAILED)) {
				EventParameterID = PRESSURE_CALIBRATION_PARAMID;
				RecordEvents(EVENT_CALIBRATION, CalibStatus, 0);
			}
		}
		/*before throwing main key check calibration by VFD */
		if (MainKeyFlag == FALSE && VGASnsrCalibAllowed == FALSE) {
			SendFakeKeyPress(MainKey);
		}
		CalibrationPassed = CAL_NOT_ALLOWED;
	}
	VGASnsrCalibAllowed = FALSE;
	//We dont relay need below things after we are updating live in ready
	SetPressureValue = RunningPreset.WeldPressure;
	if(CurrentPreset.TunedPreset)
	   SetFlowValue = CurrentPreset.TunedFlowValue;
   else
	   SetFlowValue = FlowLookup(CurrentPreset.Downspeed);
	StartingSensorCal = FALSE;
}



void UpdateSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called after triggerring in sensor cal or act. cal.     */
/* The strokelength must be greater then 0.8in to detect a heavy horn.      */
/*                                                                          */
/* Inputs : EncoderPos                                                      */
/*          DistanceV                                                       */
/*          ForceV                                                          */
/*          NVR.PSVersion - contains the last spring rate slope. This is    */
/*            used for Non Version 6 Cal actuator upgrade. It is also used  */
/*            when the calibration stroke length is less than one inch.     */
/*                                                                          */
/* Outputs : CurrentSetup.SpringRateTable                                   */
/*           SpringRateSlope - This is saved to the novram after a          */
/*              successful sensor calibration and during a Version 6 upgrade*/
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 LastIndex, Index, StartIndex,CompensatedIndex;
   UINT32 Distance = 0;
   struct Regression Reg;
   double GainRatio;
   UINT16 HornWeightCorrection = FALSE;
   UINT16 LeavingHomeForce;
      
   if(CurrentSetup.Actuator == MICRO || CurrentSetup.Actuator == MICROC)
	   	 LeavingHomeForce = MicroHomeForce;
   else
   {
      switch (CurrentSetup.PSFreq) {
         default:
         case FREQ20KHZ:
         case FREQ40KHZ:
         case FREQ30KHZ:
         case FREQ60KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE;
            break;
         case FREQ15KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE15KHZ;
            break;
      }
   }   

   /* convert SpringRateSlope to a double incase the stroke was not long enough or */
   /* a cal actuator is performed to update for a new horn weight                 */
   SpringRateSlope = (double)NVR.SpringRateSlope / 1024.0;
   SpringRateSlope /= 10000.0; /* Adjust for 1/10000 units */

   /* Go back one point from part contact */
   if(TemporaryCalStrokeLen > SPRINGRATEINDEX)
      LastIndex = (TemporaryCalStrokeLen/ SPRINGRATEINDEX) -1;
   else
      LastIndex = 0;

   if(LastIndex <= 3)
      /* There is not enough stroke to check for a heavy horn. */
      HornWeightCorrection = TRUE;
      
   GainRatio = (double)GAIN_FACTOR_DEFAULT / (double)CurrentSetup.GainFactor;

   /* need to correct the distance and force tables when a heavy horn is used for calibration */
   StartIndex = 0;
   for(Index=0; Index < (LastIndex +1); Index++)
   {
      if((ForceV[Index + 1] - ForceV[Index]) > GREATERTHENNOISE)
      {
         StartIndex = Index;
         Index = (LastIndex + 1); /* exit the for loop */
      }
   }

   LastIndex -= StartIndex;
   CompensatedIndex = StartIndex;
   
   for(Index=0; Index < (LastIndex + 1); Index++)
   {
      ForceV[Index] = ForceV[CompensatedIndex];
      DistanceV[Index] = DistanceV[CompensatedIndex++];
   }     
         
   Reg = LinearReg(DistanceV, ForceV, LastIndex);
   
   /* Use defaults if stroke length < 1 inch. */
   if(TemporaryCalStrokeLen > ONE_INCH){
      /* Only update springrate slope during a sensor calibration */ 
      /* or when Cal Actuator is run on a Version 6 Actuator */
      if((CurrentSequence == CALIBRATION) || ((AtLeastVersion806() == FALSE) && ((ErrorCode == ERRORCODE1100_EQ20) || (ErrorCode == ERRORCODE1200_EQ20))))
         SpringRateSlope = Reg.slope;
   }
   
   if( (LastIndex < 3) || (CurrentSequence == SC) )
   {

      /*  Use the default table except for CurrentSetup.SpringRateTable[0]  */
      /*  CurrentSetup.SpringRateTable[0] contains the load cell bias read  */
      /*  at the home position of the actuator. Do not update if hornweight */
      /*  can not be detected.                                              */
   
      for(Index = 1; Index < SPRING_RATE_SIZE; Index++)
      {   
         Distance = Distance + SPRINGRATEINDEX;
         CurrentSetup.SpringRateTable[Index] = CurrentSetup.SpringRateTable[0]
          + LeavingHomeForce + (SpringRateSlope*Distance);
      }   
   }  
   
   if(CurrentSequence == CALIBRATION)
   {
      for(Index = 1; Index < SPRING_RATE_SIZE; Index++)		 
      {
         Distance = Distance + SPRINGRATEINDEX;
            CurrentSetup.SpringRateTable[Index] = CurrentSetup.SpringRateTable[0]
              + (UINT16)(SpringRateSlope *(double)Distance) + LeavingHomeForce;
      }
   }  

   ForceV[0] = 0;       /* Set to zero so they will show up as zero lbs */
   ForceV[1] = 0;       /* on the user menus                            */
   ForceV[2] = 0;  
   
}




void InitForce1(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   InitCalWait();              /* Initialize the Calibration wait timer flag*/
}



void InitForce2(void)
/****************************************************************************/ 
/* Set the PV Control signal to 7.74% above the minimum and stage to        */
/* FORCE_CALIBRATION.  The force range is from 13.8ma to 0 ma which = 45220 */
/* to 0.  Note that the PV control signal works in reverse, so 7.74% "above"*/
/* the minimum is 45220 less 7.74%.  This function is executed on entry to  */
/* the CalWaitTime1 state.                                                  */
/****************************************************************************/
{   
   PVControlSignal = PVSTART;
   SetPV(PVControlSignal,FORCE_CALIBRATION);
   PlsWaitTimerFlag = TRUE;
}

void InitForce3(void)
/****************************************************************************/ 
/* Set the PV Control signal to 12.26% above the previous value and the     */       
/* stage to FORCE_CALIBRATION.  Start a 2 sec timer for collection of force */
/* data in the CollectForceData subroutine.  This function is executed on   */
/* entry to the CalWaitTime2 state.                                         */
/****************************************************************************/ 
{
   PVControlSignal -= PVADJUST1;
   SetPV(PVControlSignal,FORCE_CALIBRATION);
   InitCalWait();              /* Initialize the Calibration wait timer flag*/
   /* Initiate variable delay.  This is a patch for testing various delays. */
   CollectForceDataDelay = LC_DELAY;
}

void DisplayNextScreen(void)
/****************************************************************************/
/* This function is called to force the display of the next screen in       */
/* calibration.                                                             */
/****************************************************************************/
{
   calbmsg.common.opcode = OP_WELDER_STATE_CHANGE;
   calbmsg.common.source_task = WC_ISR_TASK;
   calbmsg.state = TRIGGEREDSTATE;
   WeldManagerTask::thisPtr->WELDMNGRTaskQ.Write(0, *((WMGR_MSG_QUEUE_TYPE*) &calbmsg), 0);
}

void CollectForceData(void)
/****************************************************************************/
/* This function is called by the state machine each pass through the       */
/* CalWaitTime2 state.                                                      */
/****************************************************************************/
{
	UINT16 Index;
	SINT32 LoadCellAverage;

   ReadLoadCell(); /* Get average load cell A-to-D reading */
   /* wait for operator data input */
   if(!CollectForceDataDelay) return;
     
      /* Wait 2 seconds to collect data */
      if(!(--CollectForceDataDelay))
      {
         LoadCellAverage = 0;
         for(Index=0; Index<CALBAVESIZE; Index++)
            LoadCellAverage += CalbAve[Index];           
         LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

         PVDacCnts[CollectForceDataIndex] = PVControlSignal;
         ForceVcnts[CollectForceDataIndex++] = LoadCellAverage;

         PVControlSignal -= PVADJUST2;   /* Increase force by 10% */
         SetPV(PVControlSignal,FORCE_CALIBRATION);

         if(CollectForceDataIndex == 4 || CollectForceDataIndex == 8)
            /* force screen to advance */
            DisplayNextScreen();
         else
            /* Initiate variable delay.  This is a patch for testing various delays. */
            CollectForceDataDelay = LC_DELAY;
      }
      
}

void CheckSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   /* check for no movement */
   UpdateDownSpeed();
   if((PartContactFlag == FALSE) || (CurrentForce < FORCE_ON_THE_PART))
   {
      if(EncoderPos > ONE_POSITION)
      {
    	  if(((UINT16) (EncoderPos/ SPRINGRATEINDEX) - 1) < MAX_VECTOR_SIZE ){
    		  ForceV[(UINT16) (EncoderPos/ SPRINGRATEINDEX) - 1] = ADForce;
    		  DistanceV[(UINT16) (EncoderPos/ SPRINGRATEINDEX) - 1] = EncoderPos;
    	  }
      }   
   }   
   else
   {
      TemporaryCalStrokeLen = EncoderPos;
      InitForce1();
      UpdateSpringRate();
      SpringRateComplete = TRUE;
      NoPressureFlag = FALSE; 
      UpdateKeyMask(CALMODEMASK);
   }
}                            

void UpdateDownSpeed(void)
/****************************************************************************/ 
/*                                                                          */
/* check for no movement                                                    */                                             
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   if((Mode != MANUAL) && (CheckDownSpeed++ == DOWNSPEEDTIMEOUT))
   {
      CheckDownSpeed = 0;
      if((SpringRateComplete == FALSE) && (CurrentVelocity < MINDOWNSPEED))
      {
	    if(SetFlowValue == 0)
	    {
	    	if(GetCurrentSequenceType() == CALIBRATION)
	    	{
	    		SetPressureValue += CAL_PRESSURE_STEPS_INC;
	        	if(SetPressureValue >= CAL_PRESSURE_MAX)
	        	{
	        		SetPressureValue = CAL_PRESSURE_MAX;
	        	}
	    	}
	    }
	    else
	    {
	    	SetFlowValue -= CAL_FLOW_STEPS_INC;
	    	if(SetFlowValue <= CAL_FLOW_STEPS_MIN)
	    	{
               SetFlowValue = CAL_FLOW_STEPS_MIN;
	    	}
	    }
      }
   }
}

void TestTimer(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{

   UINT16 Index;
   FP_KEY_PRESSED_MSG  FPKeyMsg;
   
   if(Inp.BothPB == FALSE)
   {
      SVOff();                            /* Turn off SV to bring hown up      */
      CalibrationPassed = CAL_ABORTED;
      SendFakeKeyPress(CALIBRATION_ABORTED);
      /* If VGA H/W is available send Message to the VGA queue*/
      if(IsHWConfigured(VGA))
      {
         FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
         FPKeyMsg.key = CALIBRATION_ABORTED;                        
         RVTSHandlerTask::thisPtr->RVTSTaskQ.WriteRetry(0, *((RVTS_MSG_QUEUE_TYPE*) &FPKeyMsg), 20);
      }     

/* Put state machine back */
      for(Index = 0; Index < SPRING_RATE_SIZE; Index++)
      {
         CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
      }
      for(Index = 0; Index < MAX_TABLE_PTS; Index++)
      {
         NVR.LoadCell[Index] = TempLoadCellTable[Index];
      }
      for(Index = 0; Index < FORCE_TABLE_SIZE; Index++){
         NVR.Force[Index] = TempForceTable[Index];
      }
      PlsWaitTimerFlag = FALSE;   /* Advances the state machine */
   }
    /* check for no movement */
   UpdateDownSpeed();
   CurrentVelocity = VelocityEstimator(EncoderPos);
   if(Inp.uls == FALSE)
   {
      if(SpringRateComplete == FALSE) 
      {
         CheckSpringRate();
      }
      else 
      {
         if(TimerLoopCounter-- <= 0)
         {
            PlsWaitTimerFlag = FALSE;   /* Advances the state machine */
            TriggerBeep();
         }
         if(TimerLoopCounter < 400)
         {
            if(UpdateCalbAve++ > 3)
            {
               UpdateCalbAve = 0;
               CalbAve[CalbAveIndex++] = LoadCellIndex;
               if(CalbAveIndex >= CALBAVESIZE)
                  CalbAveIndex = 0;
            }
         }
      }
   }    
   else
   {
      ZeroEncoder();
   }
}

void ReadLoadCell(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{

   if(NoPressureFlag == FALSE)
      CheckForNoPressure();
   if(UpdateCalbAve++ > 3){
      UpdateCalbAve = 0;
      AvePressure[CalbAveIndex] = ADPressure;
      CalbAve[CalbAveIndex++] = LoadCellIndex;
      if(CalbAveIndex >= CALBAVESIZE)
      {
         CalbAveIndex = 0;
      }
   }
}

void ExitCalWait(void)
/****************************************************************************/
/*                                                                          */
/*  CalTimerFlag is used to sync the menu with the state machine.  When the */
/*  state machine times out, CalTimerFlag is set to TRUE.  This is what the */
/*  menu system is waiting for to proceed with the next menu.               */
/*                                                                          */
/****************************************************************************/
{
   CalTimerFlag = TRUE;        /* Initialize timer flag here                */
}

void InitCalWait(void)
/****************************************************************************/
/*                                                                          */
/*  CalTimerFlag is used to sync the menu with the state machine.  When the */
/*  state machine times out, CalTimerFlag is set to TRUE.  This is what the */
/*  menu system is waiting for to proceed with the next menu.  The CalTimer */
/*  Flag is cleared here.                                                   */
/*                                                                          */
/****************************************************************************/
{
   PlsWaitTimerFlag = TRUE;
   CalTimerFlag = FALSE;       /* Initialize timer flag here                */
}

void InitCalTimer(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/* 02jun99: Separated AED & AEF code - cmc                                  */
/****************************************************************************/ 
{
   if(CalibrationPassed == CAL_PASSED)
   {
      CalTimer = CALIBRATION_TIMER;/* Initialize the calibration timer */
      CalbAveIndex = 0;
      UpdateCalbAve = 5;
      PlsWaitTimerFlag = TRUE;    /* Please Wait Timer Flag */
   }
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
   InitCalWait();
}

void SBCReadA2D3(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;   /* divide by array length */

   AdCntsPSI[0] = (SINT32)PressureAverage;

}

void SBCReadA2D4(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;       /* divide by array length */

   AdCntsPSI[1] = (SINT32)PressureAverage;
}

void SBCReadA2D1(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 Index;
SINT32 LoadCellAverage;

   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;
   CollectForceDataIndex = 1;
   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsLC[0] = LoadCellAverage;
   ForceVcnts[0] = LoadCellAverage;
   PVDacCnts[0] = PVControlSignal;

   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
}

void SBCReadA2DLC2(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 Index;
SINT32 LoadCellAverage;

   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;

   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsLC[1] = LoadCellAverage;
   ForceVcnts[4] = LoadCellAverage;
   PVDacCnts[4] = PVControlSignal;
   CollectForceDataIndex++;
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
   if ((CurrentSetup.Actuator == AED)||
      (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      VGABuildForceTable();
}


void ReadA2D2(UINT32 MenuExtra)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
	UINT16 Index;
	SINT32 LoadCellAverage;
	MenuExtra = 0;
   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;

   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;     /* divide by array length */

   AdCntsLC[2] = LoadCellAverage;
   ForceVcnts[8] = LoadCellAverage;
   PVDacCnts[8] = PVControlSignal;
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
}



void CheckForNoPressure(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;
   
   if((EncoderPos < (SINT32)(TemporaryCalStrokeLen - OFF_THE_PART)) &&
      (NoPressureFlag == FALSE))
   {
      NoPressureFlag = TRUE; 
      CalibrationPassed = CAL_ABORTED;

      SVOff();                            /* Turn off SV to bring hown up      */
      SendFakeKeyPress(CALIBRATION_ABORTED);
 /* Put state machine back */
	   if (CalibrationStep == PRESSURE_CALIB) {
			for (Index = 0; Index < MAX_TABLE_PTS; Index++) {
				NVR.Pressure[Index] = TempPressureTable[Index];
			}
	   } else {
	   	for (Index = 0; Index < SPRING_RATE_SIZE; Index++) {
			CurrentSetup.SpringRateTable[Index] =
					TempSpringRateTable[Index];
	   	}
	   	for (Index = 0; Index < MAX_TABLE_PTS; Index++) {
				NVR.LoadCell[Index] = TempLoadCellTable[Index];
	    }
	   }
	}
}

void CalExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when both palm buttons have */
/*  been pressed in the calibration weld sequence.  					   */
/*                                                                         */
/***************************************************************************/
{
   
   SetPV(CAL_DOWNSPEED,HOME_TO_DWNSPD);   
   EnableSVOn();                        /* Enable SV valve                 */
   SVOn();                              /* Turn on SV to bring down hown   */
   ZeroEncoder();
}

void SelectPressureCalSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Pressure Sensor Calibration state sequence.                 */
/*                                                                         */
/* Caveats : Must make sure to update menusync states when submenues are added*/
/* or deleted.                                                             */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i = 0, SaveStateMachineFlag;

   ResetStateMachine(); /* Turn off the state machine first */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);

   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO)) {
      WeldSequence[i++] = &CalTopOfList; /* enter the sequence of states */

      /* CalForceMenu1 wait for next menu to be displayed */
      /*----------------------*/
      /* CAL PRESSURE         */
      /* Set Regulator For    */
      /* Reading of 10-30 psi */
      /*             Continue */
      /*----------------------*/
      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu2 wait for next menu to be displayed */
      /*----------------------*/
      /* CAL PRESSURE         */
      /* Enter Gauge Reading  */
      /*                = xxx */
      /*             Continue */
      /*----------------------*/

      //WeldSequence[i++] = &CalWaitTime3;

      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu3 wait for next menu to be displayed */
      /*----------------------*/
      /* CAL PRESSURE         */
      /* Set Regulator For    */
      /* Reading of 50-80 psi */
      /*             Continue */
      /*----------------------*/
      //WeldSequence[i++] = &CalWaitTime3;
      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu4 wait for next menu to be displayed */
      /*----------------------*/
      /* CAL PRESSURE         */
      /* Enter Gauge Reading  */
      /*                = xxx */
      /* ____________Continue */
      /*----------------------*/
      //WeldSequence[i++] = &CalWaitTime3;
      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu5 wait for next menu to be displayed */

      /*----------------------*/
      /* CAL PRESSURE         */
      /* Set Regulator to     */
      /* 20-30 PSI(138kPA)    */
      /* ____________Continue */
      /*----------------------*/
      //WeldSequence[i++] = &CalWaitTime3;
      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu5A wait for next menu to be displayed */

      /*----------------------*/
      /* CAL PRESSURE         */
      /* Enter Gauge Reading  */
      /*                = xxx */
      /*                      */
      /*----------------------*/

      WeldSequence[i++] = &CalEndOfList;
   }
   else	if( (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC) )
   {
	   WeldSequence[i++] = &CalTopOfList; /* enter the sequence of states */
		/*----------------------*/
		/* CAL PRESSURE         */
		/* Please Wait Screen    */
		/*----------------------*/
		WeldSequence[i++] = &SetCalPressureST;/* Set pressure to 25 psi */
		WeldSequence[i++] = &MenuSyncST;
		/*----------------------*/
		/* CAL PRESSURE         */
		/* Enter Gauge Reading  */
		/*                = xxx */
		/*             Continue */
		/*----------------------*/
		WeldSequence[i++] = &SetCalPressureST;/* Set pressure to 70 psi*/
		WeldSequence[i++] = &MenuSyncST;
		/* CalForceMenu3 wait for next menu to be displayed */
		/*----------------------*/
		/* CAL PRESSURE         */
		/* Please Wait Screen   */
		/*              		*/
		/*----------------------*/
		WeldSequence[i++] = &SetCalPressureST;/* Set pressure to 30 psi*/
		WeldSequence[i++] = &MenuSyncST;
		WeldSequence[i++] = &CalEndOfList;
   }
   CurrentSequence = CALIBRATION;
   SetStateMachineFlag(SaveStateMachineFlag);

   UpdateKeyMask(CALMODEMASK);
   StopDataCollection(); /* Stop the weld data collection */

   ClearAbort();
   StartStateMachine(); /* Start the state machine here     */
}

void SelectForceCalSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Force Sensor Calibration state sequence.                    */
/*                                                                         */
/* Caveats : Must make sure to update menusync states when submenues are added*/
/* or deleted.                                                             */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i = 0, SaveStateMachineFlag;

   ResetStateMachine(); /* Turn off the state machine first */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);

   if ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO)) {
      WeldSequence[i++] = &CalTopOfList; /* enter the sequence of states */

      /* Needs to Set Pressure and down speed for AES  */
      //WeldSequence[i++] = &MenuSyncST;

      WeldSequence[i++] = &MenuSyncST;
      /*----------------------*/
      WeldSequence[i++] = &CalPBState2; /* CAL SENSORS          */
      WeldSequence[i++] = &CalWaitUls; /* Set 35PSI(107kpa)    */
      WeldSequence[i++] = &CalWaitTrsST; /* Press Start Switches */
      // needed to advance the menu          /* Until Beep is Heard  */
      WeldSequence[i++] = &CalTriggerST; /*----------------------*/

      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu8 wait for next menu to be displayed */
      /* need 1st force applied here and wait for Enter key flag */
      WeldSequence[i++] = &CalWaitTime1; /*----------------------*/
      /* CAL SENSORS          */
      /* Enter Load Cell      */
      /* Reading        = xxx */
      /* ____________Continue */
      /*----------------------*/

      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu9A wait for timeout here */
      /* need 2nd force applied here and wait for Enter key flag */
      WeldSequence[i++] = &CalWaitTime1; /*----------------------*/
      /* CAL SENSORS          */
      /* Set Regulator to     */
      /* 50PSI(345kpa)        */
      /*             Continue */
      /*----------------------*/

      WeldSequence[i++] = &MenuSyncST;
      /* CalForceMenu10 wait for next menu to be displayed */
      /*----------------------*/
      /* CAL SENSORS          */
      /* Reenter Load Cell    */
      /* Reading        = xxx */
      /* ____________Continue */
      /*----------------------*/
      WeldSequence[i++] = &CalWaitTime2;
      /*----------------------*//*----------------------*/
      /* CAL SENSORS          *//* CAL SENSORS          */
      /* Calibration Failed   *//* Calibration          */
      /* See Manual Section   *//* Successful           */
      /* X-YY.       Continue *//* ____________Continue */
      /*----------------------*//*----------------------*/

      /* End of Calibration sequence */
      WeldSequence[i] = &CalEndOfList;
   }
   else if(CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC)
   {
	   WeldSequence[i++] = &CalTopOfList; /* enter the sequence of states */
	   WeldSequence[i++] = &MenuSyncST;//please wait
	   WeldSequence[i++] = &SetCalForceST;//set pressure 25PSI and down speed to 20%
	   WeldSequence[i++] = &CalPBState2; /* CAL SENSORS          */
	   WeldSequence[i++] = &CalWaitUls; /* Set 35PSI(107kpa)    */
	   WeldSequence[i++] = &CalWaitTrsST; /* Press Start Switches */
		// needed to advance the menu          /* Until Beep is Heard  */
	   WeldSequence[i++] = &CalTriggerST; /*next menu*/
	   WeldSequence[i++] = &CalWaitTime1;
	   WeldSequence[i++] = &MenuSyncST;  //please wait

	   WeldSequence[i++] = &SetCalForceST;//set pressure to 70PSI
	   WeldSequence[i++] = &CalWaitTime2;
	   WeldSequence[i]   = &CalEndOfList;
	   SetFlowValue = CAL_FLOW_STEPS;//Setting the calibration flow value in advance as soon as the Force calibration
								     //is initiated from Menu.
   }
   CurrentSequence = CALIBRATION;
   SetStateMachineFlag(SaveStateMachineFlag);

   UpdateKeyMask(CALMODEMASK);
   StopDataCollection(); /* Stop the weld data collection */

   ClearAbort();
   StartStateMachine(); /* Start the state machine here     */
}

UINT16 CalibrationAllowed(void)
{
   UINT16 Allowed = FALSE;

   if(((WeldState == READYSTATE) || (WeldState == PREREADYSTATE))&&
     (CurrentSequence == WELD))
   {
      if((Inp.OnePB == FALSE) &&
        ((WeldingResults.EquipmentFailureAlarms & NOVRAMFAILED) == 0) &&
        (Inp.uls == TRUE))
        Allowed = TRUE;
   }
   return(Allowed);
 
}



void ShowCalibrationAbort(void)
{
   CalibrationPassed = CAL_NOT_ALLOWED;
   SetReady();
   SelectWeldSequence();               /* Restore proper weld sequence      */
   StartStateMachine();
   RTOS::DelayMs( MS_TO_TICKS( 3000) * MILLS_PER_TICK);
   if(MainKeyFlag == FALSE)
   {
      SendFakeKeyPress(GoBackKey);
      SendFakeKeyPress(MainKey);
   }
}


void VGARequestActCal(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the selection is made. Need to*/
/* make sure not ready for calibration                                      */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   VGACalAllowed = FALSE;
   if((CheckOperatorAuthority(Calibration) == TRUE) && CalibrationAllowed() == TRUE)
   {
      ClearReady();        /* Remove Welder Ready signal*/
      VGACalAllowed = TRUE;
	  CheckforCalib();
   }
   CalibrationPassed = CAL_NOT_ALLOWED;
   if(VGACalAllowed == FALSE)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}

void VGACloseCalibration(void)
/*************************************************************************/
/*Description:                                                           */
/* clean up the Calibration Procedure & start the state machines.        */
/*                                                                       */
/*************************************************************************/
{
   PlsWaitTimerFlag = FALSE;
   /*Here Calibration is Closed Move to Main Menu*/
   SCFinalCleanup();
}

BOOLEAN IsCalibGoingOn(void)
/*****************************************************************************/
/*Description:                                                               */
/* Returns TRUE if either VGA Act. or Sensor Calibration is going on        */
/*****************************************************************************/
{
   BOOLEAN CalbFlag = FALSE;
   if(VGACalAllowed || VGASnsrCalibAllowed) CalbFlag = TRUE;

   return(CalbFlag);
}

void VGARequestPressureCal(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the Pressure Cal Sensor    	*/
/* selection is made                                                                     */
/*                                                                          */
/* Output: CalibrationPassed                                                */
/*                                                                          */
/****************************************************************************/
{
   VGASnsrCalibAllowed = FALSE;
   if((CheckOperatorAuthority(Calibration) == TRUE) && (CalibrationAllowed() == TRUE))
   {
      VGASnsrCalibAllowed = TRUE;
      PressureCalibrationInit();   /* Initialize State Sequence for Calibration */
      ClearReady();        /* Remove Welder Ready signal to prevent a cycle*/
	  CheckforCalib();
   }
   else{
      CalibrationPassed = CAL_NOT_ALLOWED;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}

void VGARequestForceCal(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the Force Cal Sensor    		*/
/* selection is made                                                                     */
/*                                                                          */
/* Output: CalibrationPassed                                                */
/*                                                                          */
/****************************************************************************/
{
   VGASnsrCalibAllowed = FALSE;
   if((CheckOperatorAuthority(Calibration) == TRUE) && (CalibrationAllowed() == TRUE))
   {
      VGASnsrCalibAllowed = TRUE;
      ForceCalibrationInit();   /* Initialize State Sequence for Calibration */
      ClearReady();        /* Remove Welder Ready signal to prevent a cycle*/
	  CheckforCalib();
   }
   else{
      CalibrationPassed = CAL_NOT_ALLOWED;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}

void SetCalibrationPressureEntry()
{
   AdvanceMenuFlag = FALSE;
}

/****************************************************************************/
/*                                                                          */
/*   This function will set the calibration pressure for AES Actuator.       */
/*                                                                          */
/****************************************************************************/
void SetCalibrationPressure(void)
{
   static int PlsWaitTimer = 0;
   switch(MenuNxtPointer)
   {
      case 0:
         ++PlsWaitTimer;       
         SetPressureValue = CAL_PRESSURE_1;
         break;
      case 2:
         ++PlsWaitTimer;         
         SetPressureValue = CAL_PRESSURE_2;
         break;
      case 4:        
         ++PlsWaitTimer;
         SetPressureValue = CAL_PRESSURE_3;
         break;
      default:
         PlsWaitTimer = 0;

   };
   if(PlsWaitTimer > CALIBRATION_TIMER)//The time we want to keep the user at Please Wait screen
                     //after setting the pressure
   {
      DisplayNextScreen();
      AdvanceMenuFlag = TRUE;
      PlsWaitTimer = 0;
   }
}

void SetCalibrationForceEntry()
{
   AdvanceMenuFlag = FALSE;
}

/****************************************************************************/
/*                                                                          */
/*   This function will set pressure and flow for the Force calibration     */
/*   for AES Actuator.                                                      */
/*                                                                          */
/****************************************************************************/
void SetCalibrationForce(void)
{
   static int PlsWaitTimer = 0;
   switch(MenuNxtPointer)
   {
      case 2:
         ++PlsWaitTimer;         
         SetPressureValue = CAL_PRESSURE_4;
         SetFlowValue = CAL_FLOW_STEPS;//steps
         break;
      case 5:        
         ++PlsWaitTimer;
         SetPressureValue = CAL_PRESSURE_5;
         break;
      default:
         PlsWaitTimer = 0;
   };

   if((PlsWaitTimer > CALIBRATION_TIMER) && (FlowReadValue == SetFlowValue))
   {
      DisplayNextScreen();
      AdvanceMenuFlag = TRUE;
      PlsWaitTimer = 0;
   }
}
struct Regression LinearReg(SINT32* x, SINT32* y, UINT16 n)
/****************************************************************************/
/* LinearReg returns the slope of the best least squares fit.  x is the     */
/* independent variable and y is the dependent variable.  The slope is delta*/
/* y/delta x.                                                               */
/****************************************************************************/
{
double  Sxy=0.0, Sx2=0.0;
double  Mx=0.0, My=0.0;
double  xn, error, error2;
SINT32 *xsav, *ysav;
struct Regression Reg;
UINT16 Index;

   xsav = x;
   ysav = y;
   
   /* compute the sums and the means */
   for(Index=0; Index<n; Index++)
   {
      Sxy = Sxy + (double)(*x)*(double)(*y);
      Sx2 = Sx2 + (double)(*x)*(double)(*x);
      Mx = Mx + (double)(*x);
      My = My + (double)(*y);
      x++;
      y++;
   }
   xn = (double)n;
   if(n > 0) //coverity fix suspected divide by zero
   {
	   Mx /= xn;
	   My /= xn;
   }
   
   /* compute the slope */
   Reg.slope = (Sxy - xn*Mx*My)/(Sx2 - xn*Mx*Mx);

   /* compute the y intercept */
   Reg.intercept = My - Reg.slope*Mx;

   /* Restore pointers to array beginnings */
   x = xsav;
   y = ysav;

   /* compute the variance */
   error2 = 0.0;
   for(Index=0; Index<n; Index++)
   {
      error = *y - (Reg.intercept + Reg.slope*(*x));
      error2 = error2 + error*error;
      x++;
      y++;
   }

   Reg.variance = error2/(double)(n-2);
   return Reg;
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "G:\332\ut\snsrcalb.ut"
#endif
/* End of include for unit test */


