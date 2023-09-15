/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/SystemManagerTask.cpp_v   1.21   16 Apr 2015 07:18:08   rjamloki  $ */
/****************************************************************************/

/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/SystemManagerTask.cpp_v  $
 * 
 *    Rev 1.21   16 Apr 2015 07:18:08   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.20   08 Apr 2015 13:46:44   AnPawar
 * Changes to update ram variables for Prestrigger, Amp Step, Pressure Step.
 * 
 *    Rev 1.19   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.18   11 Dec 2014 08:37:24   AnPawar
 * learing udi string after every weld.
 * 
 *    Rev 1.17   28 Nov 2014 07:41:24   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.16   10 Nov 2014 05:16:22   AnPawar
 * CurrentSetup variable created.
 * 
 *    Rev 1.15   06 Oct 2014 06:47:00   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.14   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.13   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.12   05 Sep 2014 05:16:18   rjamloki
 * Function calls refrencing compressed preset replaced with new functions.
 * 
 *    Rev 1.11   28 Jul 2014 12:55:42   rjamloki
 * separated force and pressure calibration table updates in Act Novram
 * 
 *    Rev 1.10   09 Jul 2014 13:42:48   rjamloki
 * Removed PrintData and VgaHWAvail checks.
 * 
 *    Rev 1.9   11 Jun 2014 12:13:38   rjamloki
 * Merged globals from sysmngr.cpp and removed sysmngr.cpp
 * 
 *    Rev 1.8   21 May 2014 10:48:12   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   26 Mar 2014 12:38:48   rjamloki
 * removed extern declaration,SystemManagerTask::SystemManagerTask(),SystemManagerTask::Run() function changed,Tick() removed
 * 
 *    Rev 1.6   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:46   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:56   rjamloki
 * Preset changes to support 1000 preset.
 *
 *    Rev 1.3   03 Jan 2014 08:45:54   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: SystemManagerTask.cpp

 -------------------------------- DESCRIPTION --------------------------------
*/





#include "qdef.h"
#include "string.h"
#include "names.h"                            /* application object definitions     */
#include "opcodes.h"                          /* intertask opcodes definitions      */
#include "genrlmsg.h"                         /* generic message type               */
#include "preset.h"
#include "param.h"
#include "wldstate.h"
#include "statedrv.h"
#include "prsetmsg.h"
#include "nvm_msg.h"
#include "weld_obj.h"
#include "battram.h"
#include "keypad.h"
#include "digout.h"
#include "menu3.h"
#include "SystemManagerTask.h"
#include "selctkey.h"
#include "limits.h"
#include "weld_msg.h"
#include "genalarm.h"
#include "spidd.h"
#include "snsrcalb.h"
#include "actnvram.h"
#include "menu7a.h"
#include "serial.h"
#include "psnvram.h"
#include "alsetup.h"
#include "util.h"
#include "graphs.h"
#include "ready.h"
#include "getmsg.h"
#include "SystemManagerTask.h"
#include "RTOS.h"
#include "WeldManagerTask.h"
#include "menu1.h"
#include "RVTSHandlerTask.h"
#include "command.h"
/* */


extern UINT8 ReadOnlyFlag;

#define COUNTS_PER_INCH 1024.0*10000.0            /* 10000 counts per inch multiplied by a scaling factor */
UINT8 UpdateRunningPreset;
UINT16 WeldDataOffset;
UINT8  WarningDetectedFlag;
UINT32 ActualPeakPower;
SINT32 ActualForceMax;
SINT32 WeldForceEnd;
BOOLEAN LastWeldResultsUpdated = FALSE;   // Used by C++ run screen
UINT32                     SysmQueueId;
UINT32                     SysmPtId;
UINT8                     *PresetDataPtr;      /* Current destination of rcvd data            */
SYSM_MSG_QUEUE_TYPE        SysmMsgOut;
SYSM_MSG_QUEUE_TYPE        SysmMsgIn;
CONFIGSETUP CurrentSetup;
SystemManagerTask *SystemManagerTask::thisPtr;

#define SYSMNGRTASK_FIFOSIZE 10
#define COUNTS_PER_INCH 1024.0*10000.0

   SystemManagerTask::SystemManagerTask() :
      Task("SysMngr", T_SIZE_1024), SysMNGRTaskQ(SYSMNGRTASK_FIFOSIZE, "SysmQ")
/****************************************************************************/
/* Description:-                                                            */
/* RVTSHandlerTask Constructor                                                     */
/****************************************************************************/
{
   thisPtr = this;
   SysmQueueId = (UINT32) &SysMNGRTaskQ;
}

SystemManagerTask::~SystemManagerTask()
/****************************************************************************/
/* Description:-                                                            */
/* RVTSHandlerTask destructor                                              */
/****************************************************************************/
{

}

void SystemManagerTask::Run()
{
	 SYSM_MSG_QUEUE_TYPE SysmMsgIn;
	   SYSM_MSG_QUEUE_TYPE SysmMsgOut;
	   UINT32 FramOffset;
	   FRAM_STATUS_TYPE FRAMRetVal;
	   void *FramPointer;
	   RTOS::DelayMs(100);
	   while (TRUE) {
	      SystemManagerTask::thisPtr->SysMNGRTaskQ.Read(0, SysmMsgIn, -1);
	      {
	         switch (SysmMsgIn.generic_msg.common.opcode) {
	         case OP_DISPLAY_MESSAGE:
	            break;
	         case OP_GOOD_CURRENT_SETUP:
	            break;
	         case OP_BATTRAM_READ_CURRENT_SETUP:
	            break;
	         case OP_BATTRAM_WRITE_PRESET:
	            
                SavePreset(SysmMsgIn.NvmAccessMsg.offset,&CurrentPreset);
                CopyInfoFromPreset(&CurrentPreset, SysmMsgIn.NvmAccessMsg.offset);
	            break;
	         /* read preset */
	         case OP_BATTRAM_READ_PRESET:
	          /* Read Preset Table from BATTRAM to DRAM */
                Readpreset(SysmMsgIn.NvmAccessMsg.offset,&CurrentPreset);
	            CurrentPreset.PresetID[PRESETLEN - 1] = 0;
	            //Update ram variables related to Pre trigger Amp, Amp step and Pressure step
	             SetupPretriggerFlags();
	             SetupAmplitudeStepFlag();
	             SetupPressureStepFlag();
	               /* Have message queue data point to new buffer */

	               /* 16 Presets are read at Power Up ONLY then PRESET_ZERO is read last */
	               if( ((SysmMsgIn.NvmAccessMsg.offset == PRESET_0)
	                   || UpdateRunningPreset) && !ReadOnlyFlag)
	               {
	                  SysmMsgOut.PresetTablePtrMsg.common.opcode =  OP_HERE_IS_PRESET;
	                  SysmMsgOut.PresetTablePtrMsg.common.source_task = SYSM_SOURCE_TASK;
	                  SysmMsgOut.PresetTablePtrMsg.msg_pointer = PresetDataPtr;
	                  SysmMsgOut.PresetTablePtrMsg.byte_count = 0;
	                  SysmMsgOut.PresetTablePtrMsg.partition_id = SysmPtId;
	                  SysmMsgOut.PresetTablePtrMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
	                  WeldManagerTask::thisPtr->WELDMNGRTaskQ.WriteRetry(0, *((WMGR_MSG_QUEUE_TYPE*) &SysmMsgOut), 50);
	                  UpdateRunningPreset = FALSE;
	               }
	            break;
	         case OP_GOOD_MIN_PRESET:
	            break;
	         case OP_GOOD_MAX_PRESET:
	            break;
	         case OP_MIN_PRESET_READ_FAIL:
	            break;
	         case OP_MAX_PRESET_READ_FAIL:
	            break;
	         case OP_CURRENT_SETUP_READ_FAIL:
	            break;
	         case OP_PRESET_READ_FAIL:
	            break;
	         case OP_WHERE_IS_PRESET:
	            break;
	         case OP_FINAL_WELD_DATA:
	            /* Calculate to correct offset for Weld data */
	            FramHistoryPtr = (UINT8 *) FRAM1200_HISTORY_START;
	            AddrFram = (SINT32)FramHistoryPtr;
	            if(WeldDataOffset == 0)
	               WeldDataOffset = CurrentSetup.WeldHistoryPtr - AddrFram;
	            else if (WeldDataOffset >= WELD_DATA_SIZE_800)
	               WeldDataOffset = 0;
	            FramOffset = WeldDataOffset;
	            WeldDataOffset += sizeof(WELD_DATA);

	            /* Change to SINT32 (32 bit) Variables for menu pointers */
	            ActualPeakPower = FinalResults.PeakPower;
	            ActualForceMax = FinalResults.WeldForceEnd;
	            WeldForceEnd = FinalResults.WeldForceEnd;

	           /* Update Cycle Count */
				FRAMPresetInfo[CURRENT_PRESET_INDEX].WeldCount = FinalResults.CycleCount;
				CurrentPreset.WeldCount = FinalResults.CycleCount;      /* Now save in current */
				//save batch count in FRAM slot 0
            	FRAMPresetInfo[CURRENT_PRESET_INDEX].CurrBatchCount = CurrentPreset.CurrBatchCount;
	/***   Save preset now so updated preset count is not lost (Japan's fix)   ***/
	            if (CurrentPreset.PresetUpdateComplete == TRUE){	               
	            	FRAMPresetInfo[CurrentSetup.ActivePreset].WeldCount = FinalResults.CycleCount;
	            	FRAMPresetInfo[CurrentSetup.ActivePreset].CurrBatchCount = CurrentPreset.CurrBatchCount;
				}

	/***   End of preset count Fix   ***/

	            FramPointer = &FinalResults;
	            FRAMRetVal = FramAccess( FRAM_WRITE, HISTORY_SECTION, (UINT8*)FramPointer, FramOffset, sizeof(WELD_DATA) );
	            memset(UDIString, 0, sizeof(UDIString));
	            LastWeldResultsUpdated = FALSE;   /* Causes latest result data */
	                                              /* to be fetched for display */

	            if(RunScreenFlag && MenuCounter == 1)
	            {
	               if(AlarmDetectedFlag)
	                  SendFakeKeyPress(UPDATEDISPLAY);
	               else
	                  SendFakeKeyPress(UPDATELINE4);
	            }
	            StartStateMachine();
	            break;
	         case OP_SETUP_ALARM_DATA:
	            SetupAlarmDetectedFlag = CheckForSetupAlarms();
	            if (SetupAlarmDetectedFlag == TRUE) {
	               CountSetupAlarms();
	            }
	            if ((RunScreenFlag) && (MenuCounter == 1)) {
	               if (SetupAlarmDetectedFlag == TRUE)
	                  SendFakeKeyPress(UPDATEDISPLAY);
	               else
	                  SendFakeKeyPress(UPDATELINE4);
	            }
	            break;
	         case OP_READ_ALARM_DATA:
	            AlarmDetectedFlag = TRUE;
	            CountAlarms();
	            if(RunScreenFlag && MenuCounter == 1)
	            {
	               SendFakeKeyPress(UPDATELINE2);
	            }

	            break;
	         case OP_PRESET_WRITE_FAIL:
	            break;
	         case OP_CHANGE_PRESET_DATA:
                SavePreset(CURRENT_PRESET_INDEX, &CurrentPreset);
	            SysmMsgOut.NvmAccessMsg.common.source_task = SYSM_SOURCE_TASK;
	            SysmMsgOut.PresetTablePtrMsg.common.opcode = OP_HERE_IS_PRESET;
	            SysmMsgOut.NvmAccessMsg.offset = PRESET_0;
	            SysmMsgOut.NvmAccessMsg.data_pointer = PresetDataPtr;
	            SysmMsgOut.NvmAccessMsg.byte_count = 0;
	            SysmMsgOut.PresetTablePtrMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
	            SysmMsgOut.NvmAccessMsg.partition_id = SysmPtId;

	            /* send out just-formed message to Weld Manager */
	            WeldManagerTask::thisPtr->WELDMNGRTaskQ.WriteRetry(0, *((WMGR_MSG_QUEUE_TYPE*) &SysmMsgOut), 50);
	            BackupCurrentSetupChange();
	            break;
	         case OP_CHANGE_CURRENT_SETUP://Intentional Fall Through
	            BackupCurrentSetupChange();
	            break;
	         case OP_CLEAR_WELDHISTORY_FRAM:
	            ClearHistoryInBbram();
	            break;
	         case OP_NVM_WRITE_PRESSURE_PARAMETERS:
	        	 /* update to actnvram  when pressure calibration is successful*/
				 SetPressure();
				 SetPSVersionNVR();
	        	 break;
	         case OP_NVM_WRITE_FORCE_PARAMETERS:
	        	 SetLoadCell();
	        	 SetForceNVR();
	        	 SetCalStrokeLength();
	        	 SetCalSysPressure();
	        	 SetCalSpringRateSlope((UINT16)(SpringRateSlope * COUNTS_PER_INCH));
	        	 SetCalHomeOffset();
	        	 SetPSVersionNVR();
	            break;
	         case OP_NVM_WRITE_UPGRADE600:
	            SetCalSpringRateSlope((UINT16)(SpringRateSlope * COUNTS_PER_INCH));
	            SetCalHomeOffset();
	            SetPSVersionNVR();
	            break;
	         case OP_NVM_WRITE_UPGRADE805:
	            SetLoadCell();
	            SetPSVersionNVR();
	            break;
	         default:
	            break;
				} /* end of switch(SysmMsgIn.generic_msg.common.opcode) */
			} /* end of while(FOREVER) */
		}
}
void BackupCurrentSetupChange(void)
{
   CONFIGSETUP *FRAMPtr;
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   BUCMenuFRAM=(BUCMENU_1200*) FRAM1200_BUCMENU_START;
   memcpy(FRAMPtr, &CurrentSetup, sizeof(CurrentSetup) ); /* Save entire setup even if only 1 thing changed */
   memcpy(BUCMenuFRAM, &BUCMenuRAM, sizeof(BUCMenuRAM) ); /* Save BUC menu while we're at it */
}
void CheckHistoryPtrBound(void)
/*-----------------------------------------------------------------------------*/
/* This function Checks to make sure bounds are not exceeded by WeldHistoryPtr */
/*-----------------------------------------------------------------------------*/
{
   SINT32 Start, End;

   // Calculate bounds for the weld data.
   Start = (SINT32)FRAM1200_HISTORY_START;
   End   = Start + (NMBR_OF_WELD_HISTORY * sizeof(WELD_DATA));
   if((CurrentSetup.WeldHistoryPtr < Start) ||
      (CurrentSetup.WeldHistoryPtr > End)){
      CurrentSetup.WeldHistoryPtr = (SINT32)FRAM1200_HISTORY_START;
   }
}
