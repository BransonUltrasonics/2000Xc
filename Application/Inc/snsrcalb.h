/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/snsrcalb.h_v   1.15   Nov 29 2017 15:05:34   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/snsrcalb.h_v  $
 * 
 *    Rev 1.15   Nov 29 2017 15:05:34   RJamloki
 * Update quick cal pressure to 35 PSI
 * 
 *    Rev 1.14   Nov 06 2017 16:32:38   RJamloki
 * Set pressure for quick calibration to 31PSI
 * 
 *    Rev 1.13   Oct 11 2017 12:10:44   RJamloki
 * DOWNSPEED STEP for quick calibration, micro c
 * 
 *    Rev 1.12   14 Oct 2016 10:36:54   RJamloki
 * updating change to release version v12.2
 * 
 *    Rev 1.11   05 Oct 2016 10:25:32   RJamloki
 * Added pressure calibration const for 1.5" issue fix
 * 
 *    Rev 1.10   28 Feb 2015 21:44:52   rjamloki
 * Force cal downspeed fix started at 20%
 * 
 *    Rev 1.9   28 Nov 2014 07:56:38   rjamloki
 * PressureInit() removed.
 * 
 *    Rev 1.8   10 Nov 2014 04:42:54   AnPawar
 * added CALIBSTAGE enum.
 * 
 *    Rev 1.7   06 Oct 2014 11:45:30   rjamloki
 * Removed BuildPVTTable function
 * 
 *    Rev 1.6   09 Jul 2014 13:22:28   rjamloki
 * Maximun steps limited to 125
 * 
 *    Rev 1.5   20 Jun 2014 13:56:06   rjamloki
 * Added calibration default defines for AES
*/

/*                                                                          */
/*------------------------- Defines ----------------------------------------*/
#ifndef SNSRCALB_H
#define SNSRCALB_H
enum CALSTATUS {  
   CAL_PASSED = 1,                 /*                                       */
   CAL_FAILED,                     /*                                       */
   CAL_ABORTED,
   CAL_NOT_ALLOWED };              /*
                                */

enum CALIBSTAGE {
	             CALIBRATION_SAVED,
	             CALIB_INIT,
	             CALIBRATION_END
                };

#define SPRING_RATE_SIZE       40
#define MAX_VECTOR_SIZE        31   /* accomodates 6-inch stroke */
#define PVSTART       (45220-3500)  /* 7.74% above minimum; see InitForce2 function */
#define PVADJUST1      5544         /* 12.26% adjustment; see InitForce3 function */
#define PVADJUST2      4522         /* 10% adjustment; see CollectForceData function */

#define LOW_60PSI    48000     //   16 bit D/A inputs from 0 to 65535 Verified
                               //   using #5 AEF actuator
#define HIGH_60PSI   -16333    //   Velocity table has a 65535 offset added to it   
#define LC_OFFSET      1000         /* Offset in version 6.XX and 8.06 and above */   

#define MAX_MENUS 15

#define CAL_FLOW_STEPS 100 //(20%downspeed)This is the starting setting for clippard motor on AES during force calibration. This controls
					//the flow and thus the down speed of horn. Increase this number for decreasing the down speed. Decrease this
					//number for increasing the down speed.Limit(0 - 125)
#define CAL_FLOW_STEPS_2 86 //(30%downspeed)

#define CAL_FLOW_STEPS_INC 2//Steps to increase every 250 ms if desired downspeed is not acheived while waiting
							//for trigger in force calibration.
#define CAL_FLOW_STEPS_MAX 125//Minimum flow
#define CAL_FLOW_STEPS_MIN 0//Maximum flow

//pressure Calibration settings for AES
#define CAL_PRESSURE_MAX 1000 //100 Psi.
#define CAL_PRESSURE_MIN 100 //10 Psi.
#define CAL_PRESSURE_STEPS_INC 1 //1 PSI

//pressure Calibration settings for AES
#define CAL_PRESSURE_1 250
#define CAL_PRESSURE_2 700
#define CAL_PRESSURE_3 350
//pressure settings during Force Calibration for AES
#define CAL_PRESSURE_4 250
#define CAL_PRESSURE_5 700

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void BuildPressureTable(void);
void VerifyPressureTable(void);
void BuildVelocityTable(void);
void CalibFinalCleanup(void);
void UpdateSpringRate(void);
void CalibrationInit(void);
void ShowCalibrationAbort(void);
void GetDefSpringRateTable(void);
void DistanceVerifyInit(UINT32);
void BuildDefaultSpringRate(void);
void InitForce1(void);
void InitForce2(void);
void InitForce3(void);
void CheckSpringRate(void);
void TestTimer(void);
void ExitCalWait(void);
void InitCalWait(void);
void InitCalTimer(void);
void Reading1(void);
void Reading2(void);
void ReadA2D2(UINT32);
void ReadLoadCell(void);
void CollectForceData(void);
void CalExitPB(void);
UINT16 CalibrationAllowed(void);
void DisplayNextScreen(void);
void UpdateDownSpeed(void);
void UpdateNVRSpringRate(void);
void VGARequestPressureCal(void);
void VGARequestForceCal(void);
void ForceCalibrationInit(void);
void SelectPressureCalSequence(void);
void SelectForceCalSequence(void);
void InitForceCalMenus(void);
void InitPressureCalMenus(void);
void SaveCalibPressure(void);

#ifdef SNSRCALB                  /******************************************/
#define Snsrtype                 /* This cute little trick will allow all  */
#else                            /* uninitialized variables to be defined  */
#define Snsrtype  extern         /* in one file.  In Main.c GLOBAL should  */
#endif                           /* be defined.                            */
                                 /******************************************/

/*-------------  Global variables  --------------------------*/
Snsrtype UINT16 LoadCellOffset;
extern double  SpringRateSlope;
#endif
