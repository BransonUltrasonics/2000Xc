/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weld_obj.h_v   1.12   08 Apr 2015 13:58:14   AnPawar  $ */
#ifndef WELD_OBJ_H
#define WELD_OBJ_H
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weld_obj.h_v  $
 * 
 *    Rev 1.12   08 Apr 2015 13:58:14   AnPawar
 * Changes for Pressure Stepping.
 * 
 *    Rev 1.11   27 Mar 2015 11:15:18   amaurya
 * HoldForceMax changed to HoldForceEnd as per code review comment.
 * 
 *    Rev 1.10   30 Jan 2015 08:08:16   amaurya
 * Added comment for BIT5 of PSActControlFlags variable which specify the On/Off status for HoldTime.
 * 
 *    Rev 1.9   11 Dec 2014 08:33:46   AnPawar
 * new weld structure WELD_DATA_BEFORE12H defined
 * 
 *    Rev 1.8   07 Aug 2014 16:07:40   tayars
 * Changed variable names.
 * 
 *    Rev 1.7   28 Jul 2014 13:04:38   rjamloki
 * Added udiscan array in weld_data object
 * 
 *    Rev 1.6   27 May 2014 10:21:54   amaurya
 * Added UDI scan in WELD_DATA object
 * 
 *    Rev 1.5   21 May 2014 10:49:20   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------
                                           
   Module name: WELD_OBJ

   Filename: weld_obj.h 

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------


*/
/* ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "qdef.h"            /* fundamental data object types       */
#include "preset.h"
#include "state.h"
#include "time.h"


#define MAX_WELD_SAMPLES     400
#define PACKET_MAX           50

#define HOLDALARMMASK			 (BIT0)
#define AMPSTEPALARMMASK    	 (BIT1)
#define PRESSURESTEPALARMMASK    (BIT2)
#define SEEKALARMMASK       	 (BIT3)
#define MANUALSCALEFLAG     	 (BIT4)
#define ALLALARMMASK             (HOLDALARMMASK | AMPSTEPALARMMASK | PRESSURESTEPALARMMASK | SEEKALARMMASK)


typedef struct weldObject
{
   UINT16  Power[MAX_WELD_SAMPLES];            /* Power (in percent)                              */
   UINT16  Amp[MAX_WELD_SAMPLES];              /* Amplitude (in percent)                          */
   UINT16  Freq[MAX_WELD_SAMPLES];             /* Frequency (Hz) 20K:19450-20450, 40K:38900-40900 */
   UINT16  Force[MAX_WELD_SAMPLES];            /* Force (always lb's)                             */
   SINT32  Dist[MAX_WELD_SAMPLES];             /* Distance (always in's)                          */
   UINT16  count;
   SINT32  HoldEndAtTime;
   SINT32  SeekEndAtTime;
   SINT32  AmpStepAtTime;
   SINT32  PressureStepAtTime;
   SINT32  PeakPowerAtTime;
   SINT32  ScrubStartAtTime;
   UINT16  PrintBottomFlags;
   UINT32  TotalPts;
   double  IncrementPts;
   UINT16  CopyPts;
   UINT16  NewPreCt;
   BOOLEAN BufferWrapFlag;    /* 100ms buffer wrapped around         */     
   double  NewInc;
   UINT16  PointsUpTillHold;  /* Points collected through hold time  */
   UINT16  EndOfSonicCt;      /* Points collected through hold time  */
   BOOLEAN DontPrintGraph;    /* Can't "Print Now" unless there is a good cycle  */
}  WELD_OBJECT;




typedef struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   //New
   SINT8   UserId[12];
   UINT16  PresetNum;
   SINT32  PresetRev;
   UINT16  PresetValidated;
   SINT8   ActAssemblyNum[12];
   SINT8   PSAssemblyNum[12];
   SINT8   StackAssemblyNum[12];
   SINT8   ActSerialNum[13];
   SINT8   PsSerialNum[13];
   SINT8   UDIScan[25];
   //
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualWeldAbs;            /* you are by looking at the weld     */
   SINT32  ActualTotalAbs;           /* history print out.     BEK 12-04-97*/
   SINT32  ActualWeldCollapse;       
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   UINT32  CycleTimeResult;                 /* Added on 04/13/00 SCM */
   SINT32  ActualDownspeed;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT32  CalibrateAlarms;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart;
   SINT32  ActualAmplitudeEnd;
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Pressure stepping on 0-off        */
   	   	   	   	   	   	   	   	   /* BIT5: 1-Hold time was on during cycle,0-Hold time was off during cycle*/
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceEnd;
   UINT16  SetPressureA;
   UINT16  SetPressureB;
   UINT16  TrigForce;

   SINT8   PresetName[PRESETLEN+1]; /* One more character added to store '*'. */
   UINT32  TotalCycleTime;

} WELD_DATA;

/* Just to copy the fram weld history before 12.G.2 to 12.H. It can be removed
after release version is stable*/
typedef struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   //New
   SINT8   UserId[12];
   UINT16  PresetNum;
   SINT32  PresetRev;
   UINT16  PresetValidated;
   SINT8   ActAssemblyNum[12];
   SINT8   PSAssemblyNum[12];
   SINT8   StackAssemblyNum[12];
   SINT8   UDIScan[25];
   //
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualWeldAbs;            /* you are by looking at the weld     */
   SINT32  ActualTotalAbs;           /* history print out.     BEK 12-04-97*/
   SINT32  ActualWeldCollapse;
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   UINT32  CycleTimeResult;                 /* Added on 04/13/00 SCM */
   SINT32  ActualDownspeed;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT32  CalibrateAlarms;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart;
   SINT32  ActualAmplitudeEnd;
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Force stepping on 0-off        */
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceMax;
   UINT16  SetForceA;
   UINT16  SetForceB;
   UINT16  TrigForce;

   SINT8   PresetName[PRESETLEN+1]; /* One more character added to store '*'. */
   UINT32  TotalCycleTime;

} WELD_DATA_BEFORE12H;

typedef  struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualDistance;           /* you are by looking at the weld     */
   SINT32  ActualWeldCollapse;       /* history print out.     BEK 12-04-97*/
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   SINT32  ActualDownspeed;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT8   PresetNum;
   UINT8   Language;
   UINT8   Unit;
   UINT8   LimitChangedFlag;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart;
   SINT32  ActualAmplitudeEnd;
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Force stepping on 0-off        */
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceMax;
   UINT32  TotalCycleTime;
   UINT16  TrigForce;

} __attribute__((__packed__))WELD_DATA7_02;

typedef struct
{
   UINT32  SetupErrorAlarms1;
   UINT32  SetupErrorAlarms2;
   UINT32  SetupErrorAlarms3;
   UINT32  SetupErrorAlarms4;
   UINT32  SetupErrorAlarms5;
   UINT32  SetupErrorAlarms6;
   UINT32  SetupErrorAlarms7;
   UINT32  SetupErrorAlarms8;
   UINT32  SetupErrorAlarms9;
   UINT32  SetupErrorAlarms10;

} SETUP_DATA_ALARMS;

#endif

void   CheckProcessLimits(void);
UINT32 VerifyPreset(void);
WELD_DATA  * GetWeldDataPointer(WELD_DATA  * weldDataPtr);


