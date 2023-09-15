/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/alsetup.cpp_v   1.9   05 Sep 2014 04:34:02   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/alsetup.cpp_v  $
 * 
 *    Rev 1.9   05 Sep 2014 04:34:02   rjamloki
 * ClearSetupAlarm function changed to used FRAmPresetInfo object
 * 
 *    Rev 1.8   09 Jul 2014 10:41:08   rjamloki
 * ClearSetup Alarm function changed to clear batch count.
 * 
 *    Rev 1.7   11 Jun 2014 11:17:20   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:47:46   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 02:50:28   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:16   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:30   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:18   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
                                     
/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:   SETUP_ALARMS                                            */
/*                                                                          */
/*   Filename:      genalarm.c                                              */
/*                                                                          */
/*   Function name:                                                         */

/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with Setup Alarms and their submenus                     */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "weld_obj.h"
#include "genalarm.h"
#include "keypad.h"
#include "display.h"
#include "selctkey.h"
#include "alarms.h"
#include "alsetup.h"
#include "WeldManagerTask.h"
#include "battram.h"
#include "command.h"

/*------------------------------ GLOBAL DATA -------------------------------*/
/*                     (scope is global to ALL files)                       */

SETUP_DATA_ALARMS SetupData;
#define ALARMGROUPSNUMBER 17


/*----------------------------- EXTERNAL DATA ------------------------------*/


extern UINT16 VerifyPresetInProcess;

UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);



/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/

UINT16 TotalSetupAlarmCount;

static UINT16  SetupAlarmCount;

MENUEND endlistSE = { TRUE };


/*--------------------------------- CODE -----------------------------------*/


/* --  Setup Alarms  --*/

UINT16 GetSetupAlarmCount(void)
/****************************************************************************/
/*                                                                          */
/*  VerifyPresetInProcess is checked here to ensure that the weldmngr (OP_  */
/*  RESET) is not calling VerifyPreset (and therefore calling ClearSetup    */
/*  Alarms) while TestReady State is calling CheckIfResetRequired(), which  */
/*  looks at the SetData.structure which ClearSetupAlarm clears.  This will */
/*  happen every once in a while, while there are still setup alarms but    */
/*  the damn user is still pressing the reset key anyway.                   */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Retval = TRUE;

   if (VerifyPresetInProcess == FALSE) {
      CountSetupAlarms();
      Retval = SetupAlarmCount;
   }
   return(Retval);
}



UINT8 CheckForSetupAlarms(void)
{
   UINT8 AlarmDetected = FALSE;

   if ( (SetupData.SetupErrorAlarms1 &= SETUPGROUP1MASK) ||
        (SetupData.SetupErrorAlarms2 &= SETUPGROUP2MASK) ||
        (SetupData.SetupErrorAlarms3 &= SETUPGROUP3MASK) ||
        (SetupData.SetupErrorAlarms4 &= SETUPGROUP4MASK) ||
        (SetupData.SetupErrorAlarms5 &= SETUPGROUP5MASK) ||
        (SetupData.SetupErrorAlarms6 &= SETUPGROUP6MASK) ||
        (SetupData.SetupErrorAlarms7 &= SETUPGROUP7MASK) ||
        (SetupData.SetupErrorAlarms8 &= SETUPGROUP8MASK) ||
        (SetupData.SetupErrorAlarms9 &= SETUPGROUP9MASK) ||
        (SetupData.SetupErrorAlarms10 &= SETUPGROUP10MASK) )
         AlarmDetected = TRUE;

   return(AlarmDetected);
}


void ClearSetupAlarms(void)
{
   SetupData.SetupErrorAlarms1 = 0;
   SetupData.SetupErrorAlarms2 = 0;
   SetupData.SetupErrorAlarms3 = 0;
   SetupData.SetupErrorAlarms4 = 0;
   SetupData.SetupErrorAlarms5 = 0;
   SetupData.SetupErrorAlarms6 = 0;
   SetupData.SetupErrorAlarms7 = 0;
   SetupData.SetupErrorAlarms8 = 0;
   SetupData.SetupErrorAlarms9 = 0;
    //Batch Count clear handling on alarm reset:
   //1- Which preset we are clearing the alarm for
   //2- How will preset change go into FRAM
   //3- Running preset or current preset
   //4- What if after the alarm comes and user increases the batch counter before resetting the alarm

   //First check the required authority
   if(CheckOperatorAuthority(RstBatchCount) == TRUE)
   {
	   if((CurrentPreset.BatchFunction == TRUE) && (CurrentPreset.BatchCountReset == TRUE) &&
		  ((SetupData.SetupErrorAlarms10 &  SETUPGROUP10MASK) == BIT12) &&
		  (CurrentPreset.CurrBatchCount >= CurrentPreset.BatchCount)){
		   CurrentPreset.CurrBatchCount = 0;
		   //update the FRAM slot 0 right away
		   
		   FRAMPresetInfo[CURRENT_PRESET_INDEX].CurrBatchCount = 0;
		   if (CurrentPreset.PresetUpdateComplete == TRUE){//If it is a non asterisk preset then update the active preset slot also
		   	   FRAMPresetInfo[CurrentSetup.ActivePreset].CurrBatchCount = 0;			   
		   }
		   //update the Running Preset right away as no need to update whole Running preset at all
		   RunningPreset.CurrBatchCount = 0;
	   }
   }
   SetupData.SetupErrorAlarms10 = 0;
   SetupAlarmDetectedFlag = FALSE;
   TotalAlarmCount = 0;
}

UINT16 SendAlarmBits(UINT8 * to)
/************************************************************************/
/*                                                                      */
/* This  function sends generated alarm bit position to SBC.            */
/*                                                                      */
/************************************************************************/
{
   UINT16 length =0;
   
   length += AddToBuffer(&to, (UINT8)(ALARMGROUPSNUMBER));

   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms1));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms2));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms3));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms4));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms5));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms6));	  

   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms7));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms8));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms9));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms10));	  

   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.EquipmentFailureAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.OverloadAlarms));	  

   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.RejectBitResult));
	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.SuspectBitResult));

   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.CycleModifiedAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.NoCycleAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.Warnings));

   return (length);
}

void CountSetupAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopySetupAlarm;

   SetupAlarmCount = 0;
   SetupData.SetupErrorAlarms1 &= SETUPGROUP1MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms1;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms2 &= SETUPGROUP2MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms2;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms3 &= SETUPGROUP3MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms3;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms4 &= SETUPGROUP4MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms4;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms5 &= SETUPGROUP5MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms5;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms6 &= SETUPGROUP6MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms6;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms7 &= SETUPGROUP7MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms7;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms8 &= SETUPGROUP8MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms8;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms9 &= SETUPGROUP9MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms9;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms10 &= SETUPGROUP10MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms10;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
}

