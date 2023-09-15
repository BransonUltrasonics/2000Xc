/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/mansensr.h_v   1.13   11 Mar 2015 09:22:44   amaurya  $ */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   mansensr                                                */
/*                                                                          */
/*   Filename:      mansensr.h                                              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/mansensr.h_v  $
 * 
 *    Rev 1.13   11 Mar 2015 09:22:44   amaurya
 * UpdateFlowValue() ,UpdatePressureValue() declaration added.
 * 
 *    Rev 1.12   03 Feb 2015 16:18:00   rjamloki
 * Removed redundant extern
 * 
 *    Rev 1.11   30 Jan 2015 08:06:46   amaurya
 * Added declaration of variable DSdone.
 * 
 *    Rev 1.10   12 Dec 2014 05:27:56   RJamloki
 * Separate functions to send flow and pressure values to AES
 * 
 *    Rev 1.9   14 Nov 2014 05:23:20   rjamloki
 * DownSpeedChanged variable added.
 * 
 *    Rev 1.8   03 Nov 2014 11:49:06   tayars
 * Changes made for code review
 * 
 *    Rev 1.7   18 Aug 2014 01:51:28   rjamloki
 * Changed function names as per review comments
*/ 


#include "portable.h"

/*****     *****     General purpose variables     *****     *****/
 
#define SHIFT_SLOWEST    6  /* divide by 64     these values are the number of times */
#define SHIFT_SLOW       5  /* divide by 32     the value is shifted     */
#define SHIFT_NORMAL     4  /* divide by 16 */
#define SHIFT_FAST       3  /* divide by 8 */
#define SHIFT_FASTEST    2  /* divide by 4 */
#define SHUT_DOWN_VALUE  0  
                         
/* this structure is used to define the possible stages of the weld cycle */
#ifndef ALREADY_DEFINED
#define ALREADY_DEFINED
enum STAGE {
   RT_TO_DWNSPD = 1,      /* rapid traverse to downspeed using RunningPreset.RTRamp            */
   TRG_TO_FORCE_A,        /* from part contact to weld force A using RunningPreset.WeldFR      */
   FORCE_A_TO_FORCE_B,    /* from weld force A to weld force B using Runningpreset.StepFR      */
   FORCE_B_TO_HOLD,       /* from Force B to hold force using RunningPreset.HoldFR             */
   HOLD_TO_HOME,          /* from hold force to home idle value using RunningPreset.ReturnRamp */
   HOME_TO_RT,            /* from home idle to rapid traverse using RunningPreset.RTRamp       */
   HOME_TO_DWNSPD,        /* from home idle to downspeed using RunningPreset.RTRamp            */
   ZERO_PSI,              /* used when psi is below the minimum allowed                        */
   FORCE_CALIBRATION };   /* calibration velocity                                              */

typedef struct R1 {
   UINT16  CurrentValue;     /* In D/A counts (0-65535)    */
   UINT16  TargetValue;      /* In D/A counts (0-65535)    */
   UINT16  ShiftValue;       /* Shift right 0-6 places     */
   UINT16  CurrentStepLimit; /* In D/A counts (0-65535)    */
   UINT16  CylinderStepLimit;/* In D/A counts (0-65535)    */
} RAMP;

void ManageSensors(void);
void SetCurrentAmp(SINT32 Amplitude);          /* weldhold, profile  */                            
void SetCurrentFreqOffset(SINT32 FreqOffset);  /* frequency offset  */                            
void SetPV(UINT16 InitVel, enum STAGE Stage);    
void InitializePV(void);
void SendPressureValToAES();
void SendFlowValToAES();
void UpdateFlowValue(void);
void UpdatePressureValue(void);
void UpdateFlowValueHornDown(void);
void UpdatePressureHornDown(void);

#define MAX_VELOCITY_PTS   101
#define MAX_FREQ_PTS       1001
#define MAX_AMP_PTS        101

#define STEPLIMIT_1_5in       4396
#define STEPLIMIT_2_0in       2157
#define STEPLIMIT_2_5in       1266
#define STEPLIMIT_3_0in       879
#define STEPLIMIT_3_25in      742
            
#define NO_LIMIT              65535
extern SINT32 	SetPressureValue;
extern SINT32   SetFlowValue;
extern SINT32   FlowReadValue;
extern SINT32 TempFlowValue;
extern BOOLEAN DownSpeedChanged;
extern BOOLEAN DownSpeedChangedHd;
extern SINT32 LastDownSpeedValue;
extern BOOLEAN DSdone;

#endif



