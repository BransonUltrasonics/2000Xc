/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/testing.cpp_v   1.22   Oct 10 2017 14:47:34   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/testing.cpp_v  $
 * 
 *    Rev 1.22   Oct 10 2017 14:47:34   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.21   11 Dec 2014 08:37:34   AnPawar
 * removed unused declaration.
 * 
 *    Rev 1.20   28 Nov 2014 07:41:34   rjamloki
 * Changes for special presets.
 * 
 *    Rev 1.19   14 Nov 2014 05:28:00   rjamloki
 * VGASaveMinimumPreset() changed.
 * 
 *    Rev 1.18   10 Nov 2014 04:59:52   AnPawar
 * DoFRAMColdStartStuff() function removed . 12.F. review change.
 * 
 *    Rev 1.17   06 Oct 2014 06:47:26   AnPawar
 * removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.16   26 Sep 2014 03:11:10   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.15   11 Sep 2014 11:10:02   rjamloki
 * Coverity fixes
 * 
 *    Rev 1.14   05 Sep 2014 05:19:54   rjamloki
 * Functions referencing compresses preset replaced with new function.
 * 
 *    Rev 1.13   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.12   28 Jul 2014 12:36:44   rjamloki
 * psos.h removed
 * 
 *    Rev 1.11   15 Jul 2014 16:40:06   hasanchez
 * Changes about the special menu.
 * 
 *    Rev 1.10   09 Jul 2014 13:43:44   rjamloki
 * Removed DataPrinting Checks.
 * 
 *    Rev 1.9   11 Jun 2014 12:14:30   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:48:12   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 03:43:34   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.6   14 Apr 2014 09:39:50   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.5   26 Mar 2014 12:39:20   rjamloki
 * removed declaration,CreateRapidTravAlarms(),variable PeakPower.Changed RecallColdStart(),RecallColdstartPreset(),VGAOverwritePresetCheck() function changed
 * 
 *    Rev 1.4   05 Mar 2014 13:56:46   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:56   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:54   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Test Functions                                              */
/*                                                                          */
/* Filename:    Testing.c                                                   */
/*                                                                          */
/* Function Name: Create Presets                                            */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains all the code to deal with creating special presets  */
/* used for testing.  It will add an entry in the diagnostic menu when      */
/* enabled via a hidden code.  This entry will allow choices of what type   */
/* of special preset to create.                                             */
/*                                                                          */
/*                                                                          */
/*   BankSwitch - swap presets 1-16 with presets 17-32                      */
/*   ColdStartAll - does a cold start and then saves it in presets 1-16     */
/*   CreateSetup - create 16 presets with setup alarm keeping control level */
/*                 in mind and what presets are available                   */
/*   CreateUnique - create 16 presets with unique name and weld time        */
/*                                                                          */
/*                                                                          */


/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define ABSOLUTE_ENERGY_MIN       1      /*      1 =     0.1 j  */
#define ABSOLUTE_ABS_MIN        125      /*    125 =  0.0125 in */
#define ABSOLUTE_ENERGY_MAX  999990      /* 999990 =  99,999 j  */
#define ABSOLUTE_TIME_MAX     65535      /*  65535 =  65.535 s  */
#define ABSOLUTE_COL_MAX      65535      /*  65535 =  6.5535 in */
#define ABSOLUTE_ABS_MAX      65535      /*  65535 =  6.5355 in */
#define ABSOLUTE_MAX_FORCE    65535      /*  65535 =  6535.5 lb */


/*------------------------------ INCLUDES ----------------------------------*/

#include "qdef.h"
#include "opcodes.h"                  /* intertask opcodes definitions      */
#include "nvm_msg.h"
#include "util.h"
#include "preset.h"
#include "battram.h"
#include "menu.h"
#include "menu3.h"
#include "menu7a.h"
#include "menu7.h"
#include "menu1.h"
#include "getmsg.h"
#include "selctkey.h"
#include "ready.h"
#include "serial.h"
#include "weld_obj.h"
#include "alsetup.h"
#include "fpled.h"
#include "actnvram.h"
#include "alarms.h"
#include "spidd.h"
#include "beep.h"
#include "digout.h"
#include "dups_api.h"
#include "string.h"
#include "dups.h"
#include "limits.h"
#include "command.h"
#include "statedrv.h"
#include "WeldManagerTask.h"
#include "ticks.h"
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/


/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                      */

//UINT16 ColdStartInProcess;
UINT16 TestingMenuFlag = FALSE;
UINT16 SpecialMenuFlag = FALSE;

TESTING_PRESET_TYPE CreatePresetType;
UINT32 SavePresetType;
BOOLEAN VGARestoreColdStartFlag = FALSE; 
BOOLEAN VGARestoreErrorFlag = FALSE; 
BOOLEAN VGAOverwritePresetFlag = FALSE;
BOOLEAN VGAOverwriteErrorFlag = FALSE;
BOOLEAN VGACreateStartFlag = FALSE;
BOOLEAN VGACreateStartErrorFlag = FALSE;


/* ------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                      (scope is global to THIS file)                      */


/****************************************************************************/
/*                                                                          */
/*  Because these menus are intended for Mongrel horde and repair only,     */
/*  languages other than English are not needed at this time.  For the      */
/*  same reason they will remain in this file, keeping a complete module    */
/*  in one file as much as practical.                                       */
/*                                                                          */
/****************************************************************************/



/*------------------------------ EXTERNAL DATA -----------------------------*/ 

extern UINT8 ActivePreset;
extern WELD_OBJECT *MsDataPtr;
extern BOOLEAN IsRecalledPreset;

MENUEND endlistTesting = { TRUE };

extern BOOLEAN IsGraphDrawing;
extern enum WELDSTATES WeldState;
//extern CONFIRM_SCREEN_TYPE ConfirmType;

extern BOOLEAN NextMenuFlag;      

/*---------------------- EXTERNAL FUNCTION PROTOTYPES ----------------------*/

void SaveSpecialPreset (UINT32 SaveCond);

/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/

void CreateAbsoluteMinValues(void);
void CreateAbsoluteMaxValues(void);
void RecallColdstartPreset(UINT32);

void BankSwitchPresets(void);
void CreateRejectSuspectAlarms(UINT16);
void DisplayExecutionMessage(void);

/*--------------------------------- CODE -----------------------------------*/


void CreateAbsoluteMinValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will create absolute minimums for parameter so that the    */
/*  user can create their own practical minimum.                             */
/*                                                                           */
/*  I DONT THINK I NEED ABSOLUTE MINIMUMS!!                                  */
/*  Please note that limit the value of the variable, especially in the      */
/*  Specials Function.                                                       */                                                                           
/*****************************************************************************/
{
   MinLimit.WeldEnergy = ABSOLUTE_ENERGY_MIN;      /* 50 = 5.0 J              */
   MinLimit.EnergyPL = ABSOLUTE_ENERGY_MIN;        /* energy plus limit       */
   MinLimit.EnergyML = ABSOLUTE_ENERGY_MIN;        /* energy minus limit      */
   MinLimit.AbsDist = ABSOLUTE_ABS_MIN;            /* 1250 = 0.1250"          */
   MinLimit.ABSCutoffDist = ABSOLUTE_ABS_MIN;      /* 1250 = 0.1250"          */
   MinLimit.EnergyPLS = ABSOLUTE_ENERGY_MIN;       /*                         */
   MinLimit.EnergyMLS = ABSOLUTE_ENERGY_MIN;       /*                         */
   MinLimit.EnergyPLR = ABSOLUTE_ENERGY_MIN;       /*                         */
   MinLimit.EnergyMLR = ABSOLUTE_ENERGY_MIN;       /*                         */
   MinLimit.AbsPLS = ABSOLUTE_ABS_MIN;             /*                         */
   MinLimit.AbsMLS = ABSOLUTE_ABS_MIN;             /*                         */
   MinLimit.AbsPLR = ABSOLUTE_ABS_MIN;             /*                         */
   MinLimit.AbsMLR = ABSOLUTE_ABS_MIN;             /*                         */
   MinLimit.TrsDistPLS = ABSOLUTE_ABS_MIN;         /*                         */
   MinLimit.TrsDistMLS = ABSOLUTE_ABS_MIN;         /*                         */
   MinLimit.TrsDistPLR = ABSOLUTE_ABS_MIN;         /*                         */
   MinLimit.TrsDistMLR = ABSOLUTE_ABS_MIN;         /*                         */
   MinLimit.AmpTrigEnerValue=ABSOLUTE_ENERGY_MIN;  /* 10 = 1.0 J              */
//   MinLimit.ForceTrigEnerValue=ABSOLUTE_ENERGY_MIN;/*                         */
   MinLimit.PreTriggerDistance = ABSOLUTE_ABS_MIN;        /* 1250 = 0.1250"          */
   MinLimit.ActClrDistance = ABSOLUTE_ABS_MIN;                                  
   MinLimit.MissingPartMin = ABSOLUTE_ABS_MIN;     /* 1250 = 0.1250"          */
   MinLimit.MissingPartMax = ABSOLUTE_ABS_MIN;     /* 1250 = 0.1250"          */
   MinLimit.PresetUpdateComplete=FALSE;
   
   strcpy(MinLimit.PresetID, "MINIMUM");
   
  // SaveCompressedPreset( (PRESET_COMPRESSED *)  PRESET_N_START(PRESET_MIN), &MinLimit);  this was removed because we dont want to start the machine with the Absolute Values
}



void CreateAbsoluteMaxValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will create new absolute maximum values for parameters so  */
/*  users can define their own maximum value.  Only those maximums that are  */
/*  different from standard maximums need be in this function.               */
/*  Please note that limit the value of the variable, especially in the      */
/*  Specials Function. Updated by Jerry Wang                                 */
/*****************************************************************************/
{
   SINT32  MaxStrokeLength = ABSOLUTE_ABS_MAX;   /* Allow up to 6.5355"          */
   SINT32  MaxEnergy = ABSOLUTE_ENERGY_MAX;      /* Max value even for 4000 Watt */
   UINT32  MaxForce = ABSOLUTE_MAX_FORCE;

   MaxLimit.WeldTime = ABSOLUTE_TIME_MAX;        /*                              */
   MaxLimit.WeldEnergy = MaxEnergy;              /* 10 = 1.0 J                   */
   MaxLimit.EnergyPL = MaxEnergy;                /* TEC mode energy plus limit   */
   MaxLimit.EnergyML = MaxEnergy;                /* TEC mode energy minus limit  */
   MaxLimit.ScrubTime = ABSOLUTE_TIME_MAX;       /* Ground detect, scrub time    */
   MaxLimit.ColDist = ABSOLUTE_COL_MAX;          /* 1 = 0.0001"                  */
   MaxLimit.AbsDist = MaxStrokeLength;           /* 40000 = 4.0"                 */
   MaxLimit.ABSCutoffDist = MaxStrokeLength;     /* 40000 = 4.0"                 */
   MaxLimit.ColCutoffDist = ABSOLUTE_COL_MAX;    /* 1000 = 0.1"                  */
   MaxLimit.HoldTime = ABSOLUTE_TIME_MAX;        /*                              */
   MaxLimit.AbDelay = ABSOLUTE_TIME_MAX;         /*                              */
   MaxLimit.AbTime = ABSOLUTE_TIME_MAX;          /*                              */
   MaxLimit.MaxTimeout = ABSOLUTE_TIME_MAX;      /*                              */
   MaxLimit.TriggerDelay = ABSOLUTE_TIME_MAX;    /*                              */
   MaxLimit.EnergyPLS = MaxEnergy;               /*                              */
   MaxLimit.EnergyMLS = MaxEnergy;               /*                              */
   MaxLimit.EnergyPLR = MaxEnergy;               /*                              */
   MaxLimit.EnergyMLR = MaxEnergy;               /*                              */
   MaxLimit.TimePLS = ABSOLUTE_TIME_MAX;         /*                              */     
   MaxLimit.TimeMLS = ABSOLUTE_TIME_MAX;         /*                              */
   MaxLimit.TimePLR = ABSOLUTE_TIME_MAX;         /*                              */
   MaxLimit.TimeMLR = ABSOLUTE_TIME_MAX;         /*                              */
   MaxLimit.ColPLS = ABSOLUTE_COL_MAX;           /*                              */
   MaxLimit.ColMLS = ABSOLUTE_COL_MAX;           /*                              */
   MaxLimit.ColPLR = ABSOLUTE_COL_MAX;           /*                              */
   MaxLimit.ColMLR = ABSOLUTE_COL_MAX;           /*                              */
   MaxLimit.AbsPLS = MaxStrokeLength;            /*                              */
   MaxLimit.AbsMLS = MaxStrokeLength;            /*                              */
   MaxLimit.AbsPLR = MaxStrokeLength;            /*                              */
   MaxLimit.AbsMLR = MaxStrokeLength;            /*                              */
   MaxLimit.TrsDistPLS = MaxStrokeLength;        /*                              */
   MaxLimit.TrsDistMLS = MaxStrokeLength;        /*                              */
   MaxLimit.TrsDistPLR = MaxStrokeLength;        /*                              */
   MaxLimit.TrsDistMLR = MaxStrokeLength;        /*                              */
   MaxLimit.AmpTrigTimeValue = ABSOLUTE_TIME_MAX;/*                              */
   MaxLimit.AmpTrigEnerValue = MaxEnergy;        /*                              */
   MaxLimit.AmpTrigColValue = ABSOLUTE_COL_MAX;  /*                              */
//   MaxLimit.ForceTrigTimeValue= ABSOLUTE_TIME_MAX;/*                             */
//   MaxLimit.ForceTrigEnerValue= MaxEnergy;       /*                              */
//   MaxLimit.ForceTrigColValue =ABSOLUTE_COL_MAX; /*                              */
   MaxLimit.PreTriggerDistance = MaxStrokeLength;       /*                              */
   MaxLimit.RTDist = MaxStrokeLength;            /*                              */
   MaxLimit.ActClrDistance= MaxStrokeLength;     /*                              */
   MaxLimit.MissingPartMin= MaxStrokeLength;     /* 40000 = 4.0"                 */
   MaxLimit.MissingPartMax= MaxStrokeLength;     /* 40000 = 4.0"                 */
   MaxLimit.WeldCount = 999999999;               /*                              */
   MaxLimit.XScaleTime = XSCALEMAXVALUE;         /*  max x-axis scale value      */

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AES) ||
		(CurrentSetup.Actuator == MICROC) ||
		(CurrentSetup.Actuator == MICRO))
   {
//      MaxLimit.HoldForce = MaxForce;        /*                              */
      if(CurrentSetup.Actuator == MICRO)
         MaxLimit.TriggerForce =MICRO_MAXFORCE_40MM;/*Restrict the max trigger force to 135 lbs.*/
      else
         MaxLimit.TriggerForce = MaxForce;  /*                              */
      MaxLimit.WeldForcePLS = MaxForce;     /*                              */
      MaxLimit.WeldForceMLS = MaxForce;     /*                              */
      MaxLimit.WeldForcePLR = MaxForce;     /*                              */
      MaxLimit.WeldForceMLR = MaxForce;     /*                              */
//      MaxLimit.AmpTrigForceValue = MaxForce;/*                              */
//      MaxLimit.WeldForce = MaxForce;        /*                              */
//      MaxLimit.Force2 = MaxForce;           /*                              */
   }
   MaxLimit.PresetUpdateComplete = FALSE;
   
   //SaveCompressedPreset( (PRESET_COMPRESSED *)  PRESET_N_START(PRESET_MAX), &MaxLimit); This will be removed because we dont want to start the machine with the Absolute Values
}

void RecallColdStart(UINT32)
/****************************************************************************/
/*                                                                          */
/* Recalls the cold start preset and loads it into the current preset.      */
/*                                                                          */
/****************************************************************************/
{
  
   Readpreset(PRESET_COLDSTART_INDEX, &CurrentPreset);
}



void CreateSuspectAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE1, SE3, SE5, SE12, SE50, SE58, SE66, SE67                            */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.WeldMode = ENERGYMODE;           /* Put in energy mode     */
   CurrentPreset.SuspectLimitsFlag = 1;           /* Suspect limits on      */
   CurrentPreset.SuspectLimits = ~LimitMask;      /* Set mask               */
   CurrentPreset.TimePLS = 6500;                  /* Create crossed time    */               
   CurrentPreset.TimeMLS = 7000;                  /* values SE1, SE50 & SE58*/
   CurrentPreset.EnergyPLS = 100;                 /* Create crossed energy  */
   CurrentPreset.EnergyMLS = 999;                 /* values SE3             */
   CurrentPreset.PowerPLS = 75;                   /* Create crossed peak    */                       
   CurrentPreset.PowerMLS = 88;                   /* power values SE5 SE66  */                       
   CurrentPreset.ColPLS = 4;                      /* Create crossed         */               
   CurrentPreset.ColMLS = 5000;                   /* collapse values SE12   */               
   CurrentPreset.PeakPwrCutoffFlag = 0;           /* Turn on Peak power SE67*/           
   CurrentPreset.ControlLimitsFlag = 1;           /* Turn on control limits */
}



void CreateRejectAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE2, SE4, SE6, SE9, SE11, SE59, SE65                                   */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.WeldMode = ENERGYMODE;           /* Put in energy mode     */
   CurrentPreset.RejectLimitsFlag = 1;            /* Reject limits on       */
   CurrentPreset.RejectLimits = ~LimitMask;       /* Set mask               */
   CurrentPreset.TimePLR = 6500;                  /* Create crossed time    */               
   CurrentPreset.TimeMLR = 7000;                  /* values SE2, SE59       */
   CurrentPreset.EnergyPLR = 100;                 /* Create crossed energy  */
   CurrentPreset.EnergyMLR = 999;                 /* values SE4             */
   CurrentPreset.PowerPLR = 75;                   /* Create crossed peak    */                       
   CurrentPreset.PowerMLR = 88;                   /* power values SE6 SE65  */                       
   CurrentPreset.AbsPLR = 5000;                   /* Create crossed         */
   CurrentPreset.AbsMLR = 7500;                   /* absolute values SE9    */
   CurrentPreset.ColPLR = 4;                      /* Create crossed         */               
   CurrentPreset.ColMLR = 5000;                   /* collapse values SE11   */               
   CurrentPreset.PeakPwrCutoffFlag = 0;           /* Turn on Peak power     */           
}



void CreateMissingPartAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE150, SE152, SE151, SE163, SE162                                      */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.SuspectLimitsFlag = 1;           /* Suspect limits on      */
   CurrentPreset.SuspectLimits = ~LimitMask;      /* Set mask               */
   CurrentPreset.MissingPartFlag = 1;             /* Turn on missing part   */
   CurrentPreset.MissingMinFlag = 0;              /* cycle aborts           */
   CurrentPreset.MissingMaxFlag = 0;
   CurrentPreset.CycleAbortFlag = 1;
   CurrentPreset.MissingPartMin = 20000;          /* Create SE150 & SE152   */
   CurrentPreset.MissingPartMax = 10000;
   CurrentPreset.TrsDistMLS = 15000;              /* Create SE151           */                       
   CurrentPreset.AbsPLS = 15001;                  /* Create SE162 & SE163   */               
}



void CreateRejectSuspectAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE2, SE74, SE75, SE76, SE77, SE78, SE79, SE80                          */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.WeldMode = ENERGYMODE;           /* Put in energy mode     */
   CurrentPreset.RejectLimitsFlag = 1;            /* Reject limits on       */
   CurrentPreset.SuspectLimitsFlag = 1;           /* Suspect limits on      */
   CurrentPreset.RejectLimits = ~LimitMask;       /* Set mask               */
   CurrentPreset.SuspectLimits = ~LimitMask;      /* Set mask               */
   CurrentPreset.TimePLR = 6000;                  /* Create crossed time    */               
   CurrentPreset.TimeMLS = 6300;                  /* values SE74, SE76      */
   CurrentPreset.TimePLS = 6500;                  /* Create crossed time    */               
   CurrentPreset.TimeMLR = 7000;                  /* values SE75, SE2, SE77 */
   CurrentPreset.EnergyPLR = 99;                  /* Create crossed energy  */
   CurrentPreset.EnergyMLS = 999;                 /* values SE78, SE80      */
   CurrentPreset.EnergyPLS = 100;                 /* Create crossed energy  */
   CurrentPreset.EnergyMLR = 999;                 /* values SE79            */
}



void CreateRapidTraverseAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE177, SE179, SE181, SE183, SE184                                      */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.RTFlag = 1;                        /* Turn on rapid trav   */
   CurrentPreset.RTDist = 10000;                    /* RT dist = 1.0" SE177 */
                                                    /* SE179, SE181, SE183  */
                                                    /* SE184                */
   CurrentPreset.RejectLimitsFlag = 1;              /* Reject limits on     */
   CurrentPreset.SuspectLimitsFlag = 1;             /* Suspect limits on    */
   CurrentPreset.RejectLimits = ~LimitMask;         /* Set reject mask      */
   CurrentPreset.SuspectLimits = ~LimitMask;        /* Set suspect mask     */
}



void CreateForceAlarms(UINT16 LimitMask)
/****************************************************************************/
/*                                                                          */
/* This function create the following suspect alarms in the current preset. */
/*   SE13, SE14, SE99, SE100, SE204, SE205, SE206, SE207, SE243             */
/*                                                                          */
/****************************************************************************/
{
   CurrentPreset.RejectLimitsFlag = 1;              /* Reject limits on     */
   CurrentPreset.SuspectLimitsFlag = 1;             /* Suspect limits on    */
   CurrentPreset.RejectLimits = ~LimitMask;         /* Set reject mask      */
   CurrentPreset.SuspectLimits = ~LimitMask;        /* Set suspect mask     */
//   CurrentPreset.Force2 = 2000;                     /* 200 lbs              */
   CurrentPreset.WeldForcePLR = 1000;               /* 100 lbs  SE200       */
   CurrentPreset.WeldForcePLS = 950;                /* 95 lbs   SE201       */
   CurrentPreset.WeldForceMLR = 2800;               /* 280 lbs  SE202       */
   CurrentPreset.WeldForceMLS = 2850;               /* 285 lbs  SE203       */
//   CurrentPreset.Force2Flag = 0xfffb;               /* Turn on force steping*/
//   CurrentPreset.ForceTrigTimeValue = 2000;         /* 2 sec SE243          */
}

void BankSwitchPresets(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will swap presets 1-16 with preset 17-32.  In the process  */
/*  of doing this the RunningPreset will be lost, because it will be used as */
/*  the temp buffer when swapping.  To swap A and B the process will be:     */
/*                                                                           */
/*      1) Recall A into CurrentPreset                                       */
/*      2) Move A into RunningPreset                                         */
/*      3) Recall B into CurrentPreset                                       */
/*      4) Save CurrentPreset (B) into A                                     */
/*      5) Save RunningPreset (A) into B                                     */
/*                                                                           */
/*****************************************************************************/
{
  /* UINT16  PresetIndex;
   
   for (PresetIndex = 1; PresetIndex <= MAX_PRESETS; PresetIndex++) {
      RecallCompressedPreset( PRESET_N_START(PresetIndex));
      memcpy(&RunningPreset, &CurrentPreset, sizeof(CurrentPreset) );
      RecallCompressedPreset( PRESET_N_START(PresetIndex+MAX_PRESETS));
      SaveCompressedPreset( PRESET_N_START(PresetIndex), &CurrentPreset);
      SaveCompressedPreset( PRESET_N_START(PresetIndex+MAX_PRESETS), &RunningPreset);
   }   
   GetPresetNames(); */    /* Make sure bank of new names are visible in menus */ 
}



void VGARecallMinimumPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will recall the minimum preset and load it into the current*/
/*  preset.  It will create a new minimum preset so values can be lowered.   */
/*                                                                           */
/*****************************************************************************/
{
	CurrentPreset.PresetUpdateComplete = FALSE;                            /*if we are not updating we will change the status to updating*/
	Readpreset(PRESET_MIN_INDEX, &CurrentPreset);                   /*we are recalling the the current min limits on Current preset*/
	CreateAbsoluteMinValues();                                             /*we are openning the limits to the absolute limits*/
    DUPS_DownloadCurrPS();
}



void VGARecallMaximumPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will recall the maximum preset and load it into the current*/
/*  preset.  It will create a new maximum preset so values can be raised.    */
/*                                                                           */
/*****************************************************************************/
{
	CurrentPreset.PresetUpdateComplete = FALSE;                            /*if we are not updating we will change the status to updating*/
	Readpreset(PRESET_MAX_INDEX, &CurrentPreset);
	CreateAbsoluteMaxValues();  
    DUPS_DownloadCurrPS(); 
}

void RecallColdstartPreset(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will recall the coldstart preset and put it in the current */
/*  preset.                                                                  */
/*                                                                           */
/*****************************************************************************/
{
    Readpreset(PRESET_COLDSTART_INDEX, &CurrentPreset);
    DUPS_DownloadCurrPS();
}

void VGARecallColdStartPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will recall the coldstart preset and put it in the current */
/*  preset.                                                                  */
/*                                                                           */
/*****************************************************************************/
{
   CurrentPreset.PresetUpdateComplete = FALSE;							/*we are updating the coldstart it to save this value on running*/
   Readpreset(PRESET_COLDSTART_INDEX, &CurrentPreset);
   CurrentPreset.PresetUpdateComplete = FALSE;							/*we are updating the coldstart*/
   DUPS_DownloadCurrPS();
  
}


void VGASaveMinimumPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will save the current preset as the new minimum preset.    */
/*                                                                           */
/*****************************************************************************/
{
	strcpy(CurrentPreset.PresetID, "MINIMUM");					/*We name the preset*/
	memcpy(&MinLimit,&CurrentPreset,sizeof(SETUPS_Ver1200));				/*We move the current preset to min Limit */
	MinLimit.PresetUpdateComplete = TRUE;
	SavePreset( PRESET_MIN_INDEX, &MinLimit);           /*saving the preset min*/
	CurrentPreset.PresetUpdateComplete = FALSE;
}


void VGASaveMaximumPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will save the current preset as the new maximum preset.    */
/*                                                                           */
/*****************************************************************************/
{
        strcpy(CurrentPreset.PresetID, "MAXIMUM");					/*We name the preset*/
		memcpy(&MaxLimit,&CurrentPreset,sizeof(SETUPS_Ver1200));				/*We move the current preset to min Limit */
		MaxLimit.PresetUpdateComplete = TRUE;
		SavePreset( PRESET_MAX_INDEX, &MaxLimit);                /*saving the preset min*/
		CurrentPreset.PresetUpdateComplete = FALSE;
}


void VGASaveColdstartPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will save the current preset as the new coldstart preset.  */
/*                                                                           */
/*****************************************************************************/
{
   	SavePreset( PRESET_COLDSTART_INDEX, &CurrentPreset);   
}



void VGARestoreMinMaxPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will restore the normal factory defaults for the minimum   */
/*  and maximum presets.  This will wipe out any custom minimum or maximum   */
/*  values that may have been created using SaveMinimuPreset() or Save       */
/*  MaximumPreset().                                                         */
/*                                                                           */
/*****************************************************************************/
{
	strcpy(MinLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   	strcpy(MaxLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
    SetMaxMinValues();
    DUPS_DownloadCurrPS();
}




void CreateGraphData(void)
/*****************************************************************************/
/*                                                                           */
/*   This function will fill the graph buffers with pre-canned data.  This   */
/*   is designed to aid in the debugging the new host command for graphs.    */
/*   The graphs will be filled as follows:                                   */
/*                                                                           */
/*   Amplitude graph - 400 points creating 10 cycles of a saw tooth wave     */
/*   Collapse graph - 400 points of a downramp                               */
/*   Force graph - 400 points of an upramp                                   */
/*   Frequency graph - 400 at a fixed value of 19950                         */
/*   Power graph - 400 points creating 8 cycles of a square wave             */
/*                                                                           */
/*   Because MsDataPtr is looking at the empty buffer ready to run the next  */
/*   cycle, this function will call ChangeDataStorage() to flip it, fill in  */
/*   the graph data, and then call ChangeDataStorage() to put it back.  This */
/*   means that the buffer that was used for the last weld cycle will be     */
/*   filled with the fake graph data.  So the sequence of operation is:      */
/*          1) Run a cycle                                                   */
/*          2) Press the select key to activate this function                */
/*          3) Now the fake graphs can be printed or sent out via the        */
/*             graph host command.                                           */
/*          4) If another cycle is run, this function will have to be called */
/*             again.                                                        */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x, j, n, m;

   ChangeDataStorage();
   MsDataPtr->count = MAX_WELD_SAMPLES;
   for (x = 0; x < MAX_WELD_SAMPLES; x++) {
       MsDataPtr->Freq[x] = 19950;                            /* Fixed value */
       MsDataPtr->Force[x] = x * 10;                          /* Up ramp     */
       MsDataPtr->Dist[x] = WeldingResults.ActualTriggerDistance +
                          ((MAX_WELD_SAMPLES - x) * 20);      /* Down ramp   */
   }
   n = MAX_WELD_SAMPLES / 8;
   for (x = 0; x < MAX_WELD_SAMPLES; x+=n) {    /* 8 cycles of a square wave */
      m = 0;
      for (j = x; m < n; j++) {
         if (m++ < (n / 2))
            MsDataPtr->Power[j] = 250;
         else   
            MsDataPtr->Power[j] = 750;
      }
   }
   FinalResults.PeakPower = 750;
   WeldingResults.PeakPower = 750;
   n = MAX_WELD_SAMPLES / 10;
   for (x = 0; x < MAX_WELD_SAMPLES; x+=n) {    /* 10 cycles of a sawtooth   */
      m = 0;
      for (j = x; m < n; j++) {
         if (m++ < (n - 2))
            MsDataPtr->Amp[j] = (m * 25);
         else if ((m - 1) < (n - 1))  
            MsDataPtr->Amp[j] = 667;
         else MsDataPtr->Amp[j] = 333;
      }
   }
   ChangeDataStorage();
   
}


/*****************************************************************************/
/*****************************      VGA Menu     ****************************/
/*****************************************************************************/

void DisplayExecutionMessage (void)
/****************************************************************************/
/*Description:                                                              */
/* This function display the 'Function Executed' message upto two seconds   */
/* for VFD and touch scrren.                                                */
/****************************************************************************/
{
   /* Wait for 2 seconds. */
   WaitMessage( SECONDS_TO_TICKS(2));
   SendFakeKeyPress(UPDATEDISPLAY);/* Go back to prev. screen.*/
   
}

void ConfrmOverwritePreset(UINT32 PresetType)
/****************************************************************************/
/*Description:                                                              */
/* if user Saves currently active Preset, then again asks for users         */ 
/* confirmation                                                             */
/****************************************************************************/
{
   SavePresetType = PresetType;
}

void VGACreateColdStartPreset(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the current preset with default values and     */
/*  then save it in preset 35.                                               */
/*                                                                           */
/*****************************************************************************/
{
   strncpy(CurrentPreset.PresetID, "COLD START",sizeof(CurrentPreset.PresetID)-1); /* Name it             */
   SavePreset( PRESET_COLDSTART_INDEX, &CurrentPreset);
  
}

void VGACreateUniquePresets(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will create 16 presets all different.   Their names will   */
/*  include the preset number as well as the weld time.  For the DUPS, the   */
/*  starting ramp will also contain the preset number as well.               */
/*                                                                           */
/*  Preset #     Weld Time   Preset Name   Starting Ramp                     */
/*  --------     ---------   -----------   -------------                     */
/*      1        1.001       Preset 01        0.111                          */
/*      2        1.002       Preset 02        0.222                          */
/*      3        1.003       Preset 03        0.333                          */
/*      4        1.004       Preset 04        0.444                          */
/*      5        1.005       Preset 05        0.555                          */
/*      6        1.006       Preset 06        0.666                          */
/*      7        1.007       Preset 07        0.777                          */
/*      8        1.008       Preset 08        0.888                          */
/*      9        1.009       Preset 09        0.999                          */
/*     10        1.010       Preset 10        1.000                          */
/*     11        1.011       Preset 11        0.011                          */
/*     12        1.012       Preset 12        0.012                          */
/*     13        1.013       Preset 13        0.013                          */
/*     14        1.014       Preset 14        0.014                          */
/*     15        1.015       Preset 15        0.015                          */
/*     16        1.016       Preset 16        0.016                          */
/*                                                                           */
/*****************************************************************************/
{
   //PRESET_COMPRESSED * CompressedPreset;

   RecallColdstartPreset(0);
   IsRecalledPreset = FALSE;
   CurrentPreset.WeldTime = 1001;
   strcpy(CurrentPreset.PresetID, "Preset 01");          /* Name it             */
   ActivatePreset(1);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 111;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 111;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1002;
   strcpy(CurrentPreset.PresetID, "Preset 02");          /* Name it             */
   ActivatePreset(2);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 222;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 222;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1003;
   strcpy(CurrentPreset.PresetID, "Preset 03");          /* Name it             */
   ActivatePreset(3);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 333;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 333;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1004;
   strcpy(CurrentPreset.PresetID, "Preset 04");          /* Name it             */
   ActivatePreset(4);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 444;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 444;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1005;
   strcpy(CurrentPreset.PresetID, "Preset 05");          /* Name it             */
   ActivatePreset(5);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 555;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 555;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1006;
   strcpy(CurrentPreset.PresetID, "Preset 06");          /* Name it             */
   ActivatePreset(6);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 666;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 666;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1007;
   strcpy(CurrentPreset.PresetID, "Preset 07");          /* Name it             */
   ActivatePreset(7);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 777;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 777;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1008;
   strcpy(CurrentPreset.PresetID, "Preset 08");          /* Name it             */
   ActivatePreset(8);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 888;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 888;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1009;
   strcpy(CurrentPreset.PresetID, "Preset 09");          /* Name it             */
   ActivatePreset(9);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 999;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 999;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1010;
   strcpy(CurrentPreset.PresetID, "Preset 10");          /* Name it             */
   ActivatePreset(10);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 1000;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 1000;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1011;
   strcpy(CurrentPreset.PresetID, "Preset 11");          /* Name it             */
   ActivatePreset(11);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 11;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 11;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1012;
   strcpy(CurrentPreset.PresetID, "Preset 12");          /* Name it             */
   ActivatePreset(12);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 12;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 12;
   SaveSpecialPreset (NAME_CURRENT);

   CurrentPreset.WeldTime = 1013;
   strcpy(CurrentPreset.PresetID, "Preset 13");          /* Name it             */
   ActivatePreset(13);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 13;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 13;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1014;
   strcpy(CurrentPreset.PresetID, "Preset 14");          /* Name it             */
   ActivatePreset(14);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 14;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 14;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1015;
   strcpy(CurrentPreset.PresetID, "Preset 15");          /* Name it             */
   ActivatePreset(15);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 15;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 15;
   SaveSpecialPreset(NAME_CURRENT);

   CurrentPreset.WeldTime = 1016;
   strcpy(CurrentPreset.PresetID, "Preset 16");          /* Name it             */
   ActivatePreset(16);
   CurrentSetup.ActivePreset = ActivePreset;
   //CompressedPreset =  PRESET_N_START(ActivePreset);
   //CompressedPreset->WeldRampTime = 16;
   CurrentPreset.DUPS_HostParamSet.WeldRampTime = 16;
   SaveSpecialPreset(NAME_CURRENT);
   
   ResetStateMachine();
   StartStateMachine();
}

void VGACreateSetupAlarmPresets(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will create 16 presets.  Each will have various amounts of */
/*  setup alarms.  Each preset will start with a cold start.                 */
/*                                                                           */
/*  Preset #     Setup Alarms                                  Preset Name   */
/*  --------     -------------------------------------------   -----------   */
/*      1        SE259                                         AE Only       */
/*      2        SE268                                         Invalid       */
/*      3        SE119                                         ENERGYCOMP    */
/*      4        SE1, SE3, SE5, SE12, SE50, SE58, SE66, SE67   SUSPECT       */
/*      5        SE2, SE4, SE6, SE9, SE11, SE49, SE51          REJECT        */
/*      6        SE2, SE74, SE75, SE76, SE77, SE78, SE79, SE80 SUSP/REJ      */
/*      7        SE15                                          TIME Mode     */
/*      8        SE48                                          ENER Mode     */
/*      9        SE37                                          PKPWR Mode    */
/*     10        SE169                                         ABS Mode      */
/*     11        SE40                                          GDDET Mode    */
/*     12        SE42                                          COLL Mode     */
/*     13        SE45, SE54, SE150, SE151, SE152, SE162,                     */
/*               SE163, SE165                                  MissinPart    */
/*     14        SE177, SE179, SE181, SE183, SE184             Rapid Trav    */
/*     15        SE13, SE14, SE99, SE100, SE204, SE205,        Force         */
/*               SE206, SE207, SE243                                         */
/*     16        SE1, SE2, SE3, SE4, SE5, SE6, SE9,            29+ Alarms    */
/*               SE11, SE12, SE49, SE50, SE51, SE58,                         */
/*               SE66, SE67, SE74, SE75, SE76, SE77,                         */
/*               SE78, SE79, SE80, SE163, SE165,                             */
/*               SE177, SE179, SE181, SE183, SE184,                          */
/*               SE200, SE201, SE202, SE203, SE243                           */
/*                                                                           */
/*****************************************************************************/
{
   UINT16  LimitsMask;

/****    ****    Preset # 1    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = COLLAPSEMODE;          /* Put in collapse mode  */
   strcpy(CurrentPreset.PresetID, "AE Only");      /* Name it               */
   ActivatePreset(1);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 2    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = 0xffff;                /* Put in illegal mode   */
   strcpy(CurrentPreset.PresetID, "Invalid");      /* Name it               */
   ActivatePreset(2);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 3    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.EnergyCompFlag = 1;               /* Turn on energy comp   */
   CurrentPreset.ControlLimitsFlag = 1;            /* Turn on control limits*/
   CurrentPreset.EnergyPL =  1000;                 /* Create crossed values */
   CurrentPreset.EnergyML =  2000;
   strcpy(CurrentPreset.PresetID, "ENERGYCOMP");   /* Name it EnergyComp    */
   ActivatePreset(3);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);

/****    ****    Preset # 4    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT |
                 MCOLDISTBIT |PCOLDISTBIT | MTIMEBIT | PTIMEBIT);
   CreateSuspectAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "SUSPECT");      /* Name it                */
   ActivatePreset(4);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);

/****    ****    Preset # 5    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT |
                 MCOLDISTBIT |PCOLDISTBIT | MTIMEBIT | PTIMEBIT |
                 MABSDISTBIT | PABSDISTBIT);
   CreateRejectAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "REJECT");       /* Name it                */
   ActivatePreset(5);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 6    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT);
   CreateRejectSuspectAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "SUSP/REJ");     /* Name it              */
   ActivatePreset(6);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 7    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = TIMEMODE;              /* Put in time mode      */
   strcpy(CurrentPreset.PresetID, "TIME Mode");    /* Name it               */
   CurrentPreset.Amp2Flag = 0xfffb;                /* Amp step on time      */
   CurrentPreset.AmpTrigTimeValue=2000;            /* SE15                  */
   ActivatePreset(7);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 8    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = ENERGYMODE;            /* Put in energy mode   */
   strcpy(CurrentPreset.PresetID, "ENER Mode");    /* Name it              */
   CurrentPreset.Amp2Flag = 0xfff7;                /* Amp step on energy   */
   CurrentPreset.AmpTrigEnerValue=2000;            /* SE48                  */
   ActivatePreset(8);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 9    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = PKPOWERMODE;           /* Put in peak pwr mode */
   strcpy(CurrentPreset.PresetID, "PKPWR Mode");   /* Name it              */
   CurrentPreset.Amp2Flag = 0xffef;                /* Amp step on power    */
   CurrentPreset.AmpTrigPowerValue=100;            /* SE48                 */
   CurrentPreset.PeakPwr = 10;                     /* Ask for 10 %         */
   ActivatePreset(9);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 10    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = ABSOLUTEMODE;          /* Put in absolute mode */
   strcpy(CurrentPreset.PresetID, "ABS Mode");     /* Name it              */
   CurrentPreset.CycleAbortFlag = 1;               /* Turn on cycle aborts */
   CurrentPreset.MissingPartFlag = 1;              /* Turn on missing part */
   CurrentPreset.MissingMaxFlag = 0;               /* Turn on max settings */
   CurrentPreset.MissingPartMax = 10000;           /* SE169                */
   ActivatePreset(10);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 11    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = GRDDETECTMODE;         /* Put in grd det mode  */
   strcpy(CurrentPreset.PresetID, "GDDET Mode");   /* Name it              */
   CurrentPreset.Amp2Flag = 0xffef;                /* Amp step on power    */
   CurrentPreset.PeakPwrCutoffFlag = 0;            /* Turn on pk pwr cutoff*/           
   CurrentPreset.AmpTrigPowerValue=100;            /* SE40                 */
   CurrentPreset.ControlLimitsFlag = 1;            /* Control limits on    */
   ActivatePreset(11);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 12    ****    ****/
   RecallColdstartPreset(0);
   CurrentPreset.WeldMode = COLLAPSEMODE;          /* Put in collapse mode */
   strcpy(CurrentPreset.PresetID, "COLL Mode");    /* Name it              */
   CurrentPreset.Amp2Flag = 0xffdf;                /* Amp step on collapse */
   CurrentPreset.AmpTrigColValue=10000;            /* SE42                 */
   ActivatePreset(12);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 13    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT);
   CreateMissingPartAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "MissinPart");   /* Name it              */
   ActivatePreset(13);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 14    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT);
   CreateRapidTraverseAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "Rapid Trav");   /* Name it              */
   ActivatePreset(14);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 15    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MFORCEBIT | PFORCEBIT);
   CreateForceAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "Force");        /* Name it              */
   ActivatePreset(15);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);


/****    ****    Preset # 16    ****    ****/
   RecallColdstartPreset(0);
   LimitsMask = (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT |
                 MCOLDISTBIT |PCOLDISTBIT | MTIMEBIT | PTIMEBIT |
                 MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT);
   CreateSuspectAlarms(LimitsMask);
   CreateRejectAlarms(LimitsMask);
   CreateRejectSuspectAlarms(LimitsMask);
   CreateMissingPartAlarms(LimitsMask);
   CreateRapidTraverseAlarms(LimitsMask);
   CreateForceAlarms(LimitsMask);
   strcpy(CurrentPreset.PresetID, "29 ALARMS");   /* Name it              */
   ActivatePreset(16);
   CurrentSetup.ActivePreset = ActivePreset;
   SaveSpecialPreset(NAME_CURRENT);
   
   ResetStateMachine();
   StartStateMachine();
}

void VGAColdstartAllPresets(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the current preset with default values and     */
/*  then save it in presets 1-16.                                            */
/*                                                                           */
/*****************************************************************************/
{
   UINT16  PresetIndex;
   
   RecallColdstartPreset(0);
   for (PresetIndex=1; PresetIndex <= MAX_POSSIBLE_PRESET; PresetIndex++) {
     ActivatePreset(PresetIndex);
     CurrentSetup.ActivePreset = ActivePreset;
     SaveSpecialPreset(NAME_CURRENT);
   }
   
   ResetStateMachine();
   StartStateMachine();
}

void VGARestoreFactoryColdstart(UINT32)
/*****************************************************************************/
/*                                                                           */
/*  This function will restore the normal factory defaults for the cold      */
/*  start values.  This will wipe out any custom created cold start values   */
/*  that may have been created using SaveColdstartPreset().                  */
/*                                                                           */
/*  Notes:                                                                   */
/*      1) The current DoColdStart should be renamed CreateColdstart         */
/*      2) CreateColdstart should be called when control level is set        */
/*      3) CreateColdstart should be called to restore factory (here)        */
/*      4) Doing a coldstart should call a new function called DoColdStart   */
/*         which is similiar to the current DoColdStart except it recalls    */
/*         the PRESET_COLDSTART instead of calling SetDefaultValues.         */
/*                                                                           */
/*****************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE)){
      StopStateMachine();     /* Perform cold start only if not */
      VGARestoreColdStartFlag = TRUE;
   }
   else
   {
      VGARestoreErrorFlag = TRUE;
   }
// DoColdStart()
}

void RestoreFactoryColdstart(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will restore the normal factory defaults for the cold      */
/*  start values.  This will wipe out any custom created cold start values   */
/*  that may have been created using SaveColdstartPreset().                  */
/*                                                                           */
/*  Notes:                                                                   */
/*      1) The current DoColdStart should be renamed CreateColdstart         */
/*      2) CreateColdstart should be called when control level is set        */
/*      3) CreateColdstart should be called to restore factory (here)        */
/*      4) Doing a coldstart should call a new function called DoColdStart   */
/*         which is similiar to the current DoColdStart except it recalls    */
/*         the PRESET_COLDSTART instead of calling SetDefaultValues.         */
/*                                                                           */
/*****************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE)){
      StopStateMachine();     /* Perform cold start only if not */
      VGARestoreColdStartFlag = TRUE;
   }
   else
   {
      VGARestoreErrorFlag = TRUE;
   }
}

void VGARestoreColdStart (void)
{
   SetDefaultValues(); /* Min/Max values now messes up the currentpreset.                    */
   strncpy(CurrentPreset.PresetID, "COLD START",sizeof(CurrentPreset.PresetID)-1); /* Name it             */
   SavePreset( PRESET_COLDSTART_INDEX, &CurrentPreset);
   ResetStateMachine();
   StartStateMachine();
   NextMenuFlag = TRUE;
   DUPS_DownloadCurrPS();
}

void VGAOverwriteAllPreset (void)
/****************************************************************************/
/*Description:                                                              */
/* This function saves all the 16 presets after user conformation depends on*/
/* the selected preset type.                                                 */
/****************************************************************************/
{
   switch (SavePresetType) {
      case UNIQUEPRESET: /* Saves the unique presets. */
         VGACreateUniquePresets(0);        
         break;
      case ALARMPRESET: /* Saves the Setup alarm presets. */
         VGACreateSetupAlarmPresets(0);      
         break;
      case COLDSTARTPRESET: 
         /* Save all the preset as cold start preset. */
         VGAColdstartAllPresets(0);
         break;
   } 
}

void VGAOverwritePresetCheck(UINT32)
{
   if ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
   {
       StopStateMachine();
       VGAOverwritePresetFlag = TRUE;   
   }
   else
   {
       VGAOverwriteErrorFlag = TRUE;
   }

}

void OverwritePresetCheck (void)
{
   switch(GlobalCommandID)
   {
   case UNIQUE_PRST:
      SavePresetType = UNIQUEPRESET;
      break;
   case SETUP_ALARM:
      SavePresetType = ALARMPRESET;
      break;
   case COLDSTART_ALL:
      SavePresetType = COLDSTARTPRESET;
      break;
   }
   if ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
   {
       StopStateMachine();
       VGAOverwritePresetFlag = TRUE;   
   }
   else
   {
       VGAOverwriteErrorFlag = TRUE;
   }
}

void VGACreateColdStartPreset(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the current preset with default values and     */
/*  then save it in preset 35.                                               */
/*                                                                           */
/*****************************************************************************/
{
   DoColdStart();
   strcpy(CurrentPreset.PresetID, "COLD START");      /* Name it             */
   SavePreset( PRESET_COLDSTART, &CurrentPreset);
   NextMenuFlag = TRUE;
   
}

void VGAEnableCreateStart(UINT32)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start if weld state is either ready/pre-ready state and     */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE))
      VGACreateStartFlag = TRUE;
   else
      VGACreateStartErrorFlag = TRUE;
}

void EnableCreateStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start if weld state is either ready/pre-ready state and     */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsGraphDrawing == FALSE))
      VGACreateStartFlag = TRUE;
   else
      VGACreateStartErrorFlag = TRUE;
}


