/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/mansensr.cpp_v   1.42   Oct 10 2017 10:41:04   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/mansensr.cpp_v  $
 * 
 *    Rev 1.42   Oct 10 2017 10:41:04   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.41   30 Apr 2015 12:07:40   rjamloki
 * Forcing the horn down menu weld pressure change on Downspeed cycle initiated from Horn Down menu.
 * 
 *    Rev 1.40   09 Apr 2015 05:21:34   RJamloki
 * AlarmEQ25 is renamed to PressureUpdateEnable
 * 
 *    Rev 1.39   08 Apr 2015 13:43:52   AnPawar
 * Changes for Hold Pressure in UpdatePressureValue() and flow in SendFlowValToAES().
 * 
 *    Rev 1.38   27 Mar 2015 11:08:00   amaurya
 * Updated comment as per code review.
 * 
 *    Rev 1.37   16 Mar 2015 07:01:28   rjamloki
 * Fixed UpdateFlowValue and UpdateFlowValueHornDown to give Please Wait on down speed changed without looking for tuning enabled
 * 
 *    Rev 1.36   13 Mar 2015 06:08:02   amaurya
 * UpdateFlowValueHornDown() added which is called when flow control is changed from horn down Menu.It updates the global flow value to be send to AES actuator. It also updates the flag to say the preset downspeed has been changed without being tuned.Also comments added for UpdateFlowValueHornDown().
 * 
 *    Rev 1.35   11 Feb 2015 06:35:56   amaurya
 * Fix for down speed change,hanging on please wait screen
 * 
 *    Rev 1.34   03 Feb 2015 16:22:28   rjamloki
 * Calling SetDownspeedTuneFlag() after Current Preset down speed is updated in UpdateFlowValueHornDown function.
 * 
 *    Rev 1.33   03 Feb 2015 07:22:34   amaurya
 * UpdateFlowValueHornDown() changed for downspeed change event.
 * 
 *    Rev 1.32   30 Jan 2015 08:10:06   amaurya
 * UpdateFlowValueHornDown() changed to create event on holdpressure change.
 * 
 *    Rev 1.31   08 Jan 2015 03:00:02   AnPawar
 * UpdatePressureValueHornDown function changed to keep hold pressure and weld pressure at horn down screen
 * 
 *    Rev 1.30   12 Dec 2014 05:29:48   RJamloki
 * Sending Flow and Pressure values in different miliseconds to AES
 * 
 *    Rev 1.29   11 Dec 2014 08:35:56   AnPawar
 * checking the horndown seq before changing downspeed.
 * 
 *    Rev 1.28   28 Nov 2014 07:36:56   rjamloki
 * SetPV() changed to remove warning "unused variable".
 * 
 *    Rev 1.27   14 Nov 2014 10:25:36   AnPawar
 *   change in function UpdateFlowValueHornDown() for down speed tuning
 * 
 *    Rev 1.26   14 Nov 2014 05:29:18   rjamloki
 * UpdateFlowValueHornDown() changed
 * 
 *    Rev 1.25   10 Nov 2014 04:51:50   AnPawar
 * ManageSensors() function changed.
 * 
 *    Rev 1.24   03 Nov 2014 11:46:50   tayars
 * Code review changes. Made it so that if the same value for downspeed is set twice from SBC, it will not invalidate the tuning.
 * 
 *    Rev 1.23   06 Oct 2014 06:38:34   AnPawar
 * removed some defines.removed psnvram.h file inclusion.
 * ManageSensors(),SendPressureAndFlowValToAES() 
 * function changed.
 * 
 *    Rev 1.22   03 Oct 2014 06:08:32   rjamloki
 * SetCurrentAmp() and SetCurrentFreqOffset() functions changed and DupsBid variable removed
 * 
 *    Rev 1.21   26 Sep 2014 13:01:22   rjamloki
 * Changes to send raw dac count to AES for better pressure resolution
 * 
 *    Rev 1.20   25 Sep 2014 14:10:52   tayars
 * Fix for issue when recalling preset and downspeed doesn't get set properly.
 * 
 *    Rev 1.19   05 Sep 2014 06:32:10   rjamloki
 * Fix to change downspeed correctly from horn down menu
 * 
 *    Rev 1.18   18 Aug 2014 01:41:48   rjamloki
 * Changed function names as per review comments
 * 
 *    Rev 1.17   07 Aug 2014 15:35:08   tayars
 * Added support for downspeed tuning.
 * 
 *    Rev 1.16   28 Jul 2014 12:46:50   rjamloki
 * Live update of pressure and flow is only allowed in Horn Down menu.
 * 
 *    Rev 1.15   09 Jul 2014 11:07:40   rjamloki
 * Menu4.h removed
 * 
 *    Rev 1.14   20 Jun 2014 14:45:56   rjamloki
 * Added global flow and pressure values.
 * 
 *    Rev 1.13   16 Jun 2014 08:37:58   rjamloki
 * Added SendPressureAndFlowValToAES function call in ManageSensors function.
 * 
 *    Rev 1.12   11 Jun 2014 11:46:36   rjamloki
 * Added function to send pressure and flow settings to AES board
 * 
 *    Rev 1.11   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:08:02   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.9   07 May 2014 10:22:14   rjamloki
 * CENTER_FREQ macro changed.
 * 
 *    Rev 1.8   30 Apr 2014 09:24:56   lmarkure
 * Corrected AmpTable and FreqTable to 10Bit, deleted unused and commented out code.
 * 
 *    Rev 1.7   14 Apr 2014 10:12:30   rjamloki
 * Fixed file inclusion and cleaned up
 * 
 *    Rev 1.6   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:28   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:40   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:32   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Name: Mansensr.c
 ----------------------------- DESCRIPTION --------------------------------

   These functions interface to the DACs and ADCs.

 ---------------------------- LOCAL_EQUATES -------------------------------*/

#define CENTER_OFFSET  500 
#define CENTER_FREQ    512
#define BARGRATE1MS 1
#define BEEPERRATE48MS 12
#define DIVIDEBY2 1
#define DIVIDEBY8 3
#define DIVIDEBY16 4
#define DIVIDEBY32 5
#define FLOAT_TO_INT 10
#define BARGRATE24MS 6
#define MAX_FORCE 1000
#define MAX_VELOCITY_SETTING 1024  /* max downspeed value that can be set from the menus */

//WC software sends 16 bit SPI frame to transfer either pressure or flow value to AES CPU3.
//The first four bits in the frame represents the value being transferred.
//Right now maximum flow value 125 in steps can be transferred and Maximum Pressure value 1023 in dac raw count can
//be transferred. These values can easily accommodate in remaining  12 bits of 16 bit frame.
#define AES_PRESSUREVAL_MSBBITS  0xA000
#define AES_FLOWVAL_MSBBITS		 0x5000
#define MAX_DAC_VAL_AES  		 1023
#define MAX_PRESSURE_VAL		 1000 //100 Psi.
//#define INCLUDE_UNIT_TEST 1


/*------------------------------ INCLUDES ----------------------------------*/


#include "mansensr.h"

#include "beep.h"
#include "qsm.h"
#include "sc.h"
#include "preset.h"
#include "spidd.h"
#include "state.h"
#include "statedrv.h"
#include "inports.h"
#include "weld.h"
#include "weld_obj.h"
#include "interpol.h"
#include "menu7a.h"
#include "menu.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "outports.h"
#include "digout.h"
#include "stdio.h"
#include "fpled.h"
#include "ready.h"
#include "battram.h"
#include "FlowLookupTable.h"
#include "psnvram.h"
#include "menuhorn.h"

/*------------------------------ GLOBAL DATA -------------------------------*/
/*                       (scope is global to ALL files)                     */

INBITS         Inp;
UINT16         VelocityIndex;
UINT16         BarGCount = 1;
UINT16         BeepRCount = 1;
UINT16         FreqValue;
UINT16         ForceRamp = 1; 
BOOLEAN        RTFlag = FALSE;
UINT16         RTStep = 0;
UINT16         AmpTable[2] = { 0, 2610 }; /* scaled for 10Bit DAC */
UINT16         FreqTable[5] = {0,261,522,784,1044}; /* scaled for 10Bit DAC */
UINT16         LastForceValue;
SINT16         NumberOfForceSteps = 0;
UINT32         ForceStepSize = 0;
UINT16         CurrentAmpOut;
SINT32         DistanceOffset;
SINT32 		   SetPressureValue;
SINT32		   SetFlowValue;
SINT32 		   FlowReadValue;//This variable keeps track of the number of steps driven by AES board to the
							//stepper motor. It doesn't know that actually the desired flow is achieved or not.
SINT32         LastDownSpeedValue = 0;
SINT32         TempFlowValue;
/*----- New code BEK 07-18-06 -----*/

RAMP  RampPV;
extern BOOLEAN PressureUpdateEnable;
/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */

static UINT16  SpiElement = 0;

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/


#if INCLUDE_UNIT_TEST
   void TestBarGraph(void);
#endif                             

void ProcessEstop(void);


/*
 ------------------------------- EXTERNAL DATA ------------------------------------
*/

extern enum    WELD_SEQUENCE_TYPE CurrentSequence;
extern enum  WELDSTATES WeldState;
extern UINT16 PresetNeedsToBeUpdated;
extern BOOLEAN DownspeedTuneFlag, DownspeedTuneFlagHD;
/*-------------------------------- CODE ------------------------------------*/



/*--------------debug code-----------*/
UINT16 PVPIndex = 0;
UINT16 TempPVP[128];
SINT8   CheckPrinter;
SINT8   *ReadPrta; 
BOOLEAN DownSpeedChanged, DownSpeedChangedHd;
BOOLEAN DownSpeedSetFlag;
BOOLEAN DSdone;
#define PVP_MASK  0x7f
/*--------------end debug code-------*/

void ManageSensors(void)
/****************************************************************************/ 
/*                                                                          */    
/* The function is called from the 1ms interrupt. It povides the interface  */
/* between the logical interfaces and the physical interfaces including     */
/* A/Ds, D/As, Power Supply Novram, Actuator Novram, digital pot and        */
/* Bargraph.  These are serial devices that are configured on the QSPI      */
/*                                                                          */
/*                                                                          */    
/****************************************************************************/ 
{
   if(NovramEnable == FALSE)
   {

	 if (BarGCount++ >= BARGRATE1MS) {
		WriteBarGraph();
		BarGCount = 1;
	 }

      switch(SpiElement++){
         case(0):
            ReadACTADC();
            MonitorInputPorts();
            ProcessEstop();
            break;

         case(1):
            GetInputData(&Inp); /*----------  Get input data first  ----------*/
            if((WeldingResults.PSActControlFlags & BIT2) == FALSE){ /* external amp */
               if(CurrentSequence == TESTMODE)
                  FreqValue = CENTER_FREQ; /* set frequency offset to */
               else
                  FreqValue = 1023 - ExtFreqOffset;
            }
            if(((WeldingResults.PSActControlFlags & BIT0) == FALSE) && (WeldState != SEEKSTATE)){ /* external amp */
               if(CurrentSequence == TESTMODE)
                  CurrentAmpOut = GetInterpolatedUINT16(AmpTable,CurrentPreset.TestAmp);
               else
                  CurrentAmpOut = GetInterpolatedUINT16(AmpTable,ExtAmp);
            }
            if(OnboardDiag == FALSE) //to avoid overwrite data to this channels during iotest
            	WritePSDAC(FreqValue,CurrentAmpOut);

            break;

         case(2):
            MonitorInputPorts();
			SendPressureValToAES(); //Update Pressure to Actuator.
            break;
         case(3):
			SendFlowValToAES(); //Update Flow to Actuator.
            GetInputData(&Inp);

		    if (BeepRCount++ >= BEEPERRATE48MS) {
			  CheckBeeper();
			  BeepRCount = 1;
		    }
            SpiElement = 0;
            break;
     
         default:
            SpiElement = 0;
            break;
      }
   }
}

void SetCurrentAmp(SINT32 Amplitude)   /* weldhold, profile  */
{
	CurrentAmpOut = (Amplitude * 1023) / 100;
}


void SetCurrentFreqOffset(SINT32 FreqOffset)  
/****************************************************************************/ 
/*                                                                          */
/* This function is called when entering the weld state and exiting the     */
/* weld state. FrequencyCenter is dependent on the Power Supply Frequency.  */
/* This offsets the value to a positive number.                             */
/*                                                                          */
/* Input: FreqOffset - user entered value, 0 = center frequency             */
/*        CurrentSetup.PSFreq - Power Supply frequency                      */
/*        FreqTable - table that converts user value to D/A value           */
/*                                                                          */
/* Output: FreqValue - value outputted to the D/A.                          */
/*                                                                          */
/****************************************************************************/ 
{
    SINT32 maxDAC = 1023;
    switch (CurrentSetup.PSFreq) {
    case FREQ60KHZ:
		FreqOffset = ((FreqOffset + SWING_60KHZ) * maxDAC) / (2 * SWING_60KHZ);
           break;
    case FREQ40KHZ:
		FreqOffset = ((FreqOffset + SWING_40KHZ) * maxDAC) / (2 * SWING_40KHZ);
           break;
    case FREQ30KHZ:
		FreqOffset = ((FreqOffset + SWING_30KHZ) * maxDAC) / (2 * SWING_30KHZ);
           break;
    case FREQ20KHZ:
		FreqOffset = ((FreqOffset + SWING_20KHZ) * maxDAC) / (2 * SWING_20KHZ);
           break;
    case FREQ15KHZ:
		FreqOffset = ((FreqOffset + SWING_15KHZ) * maxDAC) / (2 * SWING_15KHZ);
           break;
    default:
    		FreqOffset = CENTER_FREQ;
           break;
    }
    FreqValue = FreqOffset;
}

void SetPV(UINT16 InitVel, enum STAGE Stage)
{
	InitVel = 0;
	Stage = RT_TO_DWNSPD;	//only to remove warning
}

void InitializePV( void ){

}

/****************************************************************************/
/*                                                                          */
/* This function is called when flow control is changed from weld setup Menu*/
/*It updates the global flow value to be send to AES actuator. It also      */
/* updates the flag to say the preset downspeed has been changed without    */
/* being tuned. So whenever the user recalls a preset that hasn't been      */
/* tuned, it will use the downspeed setting instead of the tuned one.       */
/****************************************************************************/
void UpdateFlowValue(void)
{
   if(((CurrentSetup.DownspeedTune == TRUE) && (CurrentPreset.TunedPreset == FALSE)) ||
	  ((CurrentSetup.DownspeedTune == TRUE) && (TempFlowValue != CurrentPreset.Downspeed)))
   {
		if ((WeldState != PREREADYSTATE) && (WeldState != READYSTATE)) {
			NackError = WELDER_PROCESS_ERROR;
			ErrorResponseMinLimit = SHOW_WELDINGON_MESSAGE;
			ErrorResponseMaxLimit = 0; // for sending Welding on process
			return;
		} else {
			DownSpeedChanged = TRUE;
		}
   }
   if(TempFlowValue != CurrentPreset.Downspeed){
      CurrentPreset.Downspeed = TempFlowValue;
      SetFlowValue = CurrentPreset.TunedFlowValue = FlowLookup(CurrentPreset.Downspeed);
      CurrentPreset.TunedPreset = FALSE;
   }
   if(DownSpeedChanged)
   {
	   SetDownspeedTuneFlag();
	   DownSpeedSetFlag = TRUE;
   }
   else if(SetFlowValue != FlowReadValue)//whether or not tuning is enabled please wait should come
	   DownSpeedSetFlag = TRUE;

}

/*************************************************************************************/
/*                                                                          		*/
/* This function is called when Weld Pressure is changed from weld setup Menu       */
/*It updates the global Pressure value to be send to AES actuator              		*/
/***********************************************************************************/
void UpdatePressureValue()
{
  PressureUpdateEnable = TRUE;
  if((!CurrentPreset.HoldPressureFlag))
	  CurrentPreset.HoldPressure = CurrentPreset.WeldPressure;
}


/***************************************************************************
*                                                                         
*   Purpose:
*
*	This function is called when flow control is changed from horn down Menu  
*	it updates the global flow value to be send to AES actuator. It also     
*	updates the flag to say the downspeed has been changed without
*	being tuned.
*                                                                         
*   Entry condition:                                                      
*	void
*
*   Exit condition:
*	void
*                                                                         
***************************************************************************/
void UpdateFlowValueHornDown(void)
{
	if(((CurrentSetup.DownspeedTune == TRUE) && (HdParams.DownSpeedTuned == FALSE)) ||
	  ((CurrentSetup.DownspeedTune == TRUE) && (HdParams.TempDownSpeed != HdParams.DownSpeed)))
		DownSpeedChanged = TRUE;

	if(HdParams.TempDownSpeed !=  HdParams.DownSpeed){
	  HdParams.DownSpeed = HdParams.TempDownSpeed;
	  SetFlowValue = HdParams.TunedFlowValue = FlowLookup(HdParams.DownSpeed);
	  HdParams.DownSpeedTuned = FALSE;
	}
	if(DownSpeedChanged){
	   SetDownspeedTuneFlagHD();
	   DownSpeedChangedHd = TRUE;
	   DownSpeedSetFlag = TRUE;
	}
	else if(SetFlowValue != FlowReadValue)//whether or not tuning is enabled please wait should come
	   DownSpeedSetFlag = TRUE;
}

/****************************************************************************/
/*                                                                          */
/* This function is called when Weld Pressure is changed from HD Menu       */
/*It updates the global Pressure value to be send to AES actuator           */
/****************************************************************************/
void UpdatePressureHornDown()
{
   SetPressureValue = HdParams.WeldPressure;
   PresetNeedsToBeUpdated = FALSE;
}
/****************************************************************************/
/*                                                                          */
/* This function is called every 4 ms from  ManageSensors function and      */
/* update the pressure settings for AES actuator                            */
/****************************************************************************/
void SendPressureValToAES()
{
	UINT16 PressureVal;
	if((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (CurrentSetup.ControlLevel >= LEVEL_c))
	{
		//Below if condition is to Force weld pressure change from horn down on tuning cycles initiated from horn down screen
		//during dry weld as well as hold time. If weld pressure is not changed after entering horn down screen
		//Hold pressure will be applicable during hold time for down speed tune cycle
		if((DownspeedTuneFlag) && (DownspeedTuneFlagHD) && (HdParams.WeldPressure != CurrentPreset.WeldPressure))
			SetPressureValue = HdParams.WeldPressure;
		PressureVal = (SetPressureValue * MAX_DAC_VAL_AES) / MAX_PRESSURE_VAL;
		PressureVal = (PressureVal | AES_PRESSUREVAL_MSBBITS);
		ActLpc->WriteReadVal(PressureVal);
	}
}

/****************************************************************************/
/*                                                                          */
/* This function is called every 4 ms from  ManageSensors function and      */
/* update the flow settings for AES actuator                                */
/****************************************************************************/
void SendFlowValToAES()
{
	UINT16 FlowVal;
	if((CurrentSetup.Actuator == AES || CurrentSetup.Actuator == MICROC) && (CurrentSetup.ControlLevel >= LEVEL_c))
	{
		FlowVal = (SetFlowValue | AES_FLOWVAL_MSBBITS);
		FlowReadValue = ActLpc->WriteReadVal(FlowVal);
	}
}

