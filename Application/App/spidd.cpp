/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/spidd.cpp_v   1.30   Nov 16 2017 16:26:32   RJamloki  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/spidd.cpp_v  $
 * 
 *    Rev 1.30   Nov 16 2017 16:26:32   RJamloki
 * Arrange if conditions stamens
 * 
 *    Rev 1.29   Oct 10 2017 14:16:30   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.28   16 Apr 2015 07:18:08   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.27   09 Apr 2015 05:30:52   RJamloki
 * Removed InitForceEstimateBuffer initialization from ReadActADC function.
 * 
 *    Rev 1.26   30 Mar 2015 05:37:30   rjamloki
 * Removed unused macros and door open
 * 
 *    Rev 1.25   16 Feb 2015 01:18:52   amaurya
 * clearing force estimate buffer once
 * 
 *    Rev 1.24   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.23   08 Jan 2015 02:53:38   AnPawar
 * ReadPSADC function changed to fix digitalfiltering for power sample
 * 
 *    Rev 1.22   28 Nov 2014 07:41:00   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.21   10 Nov 2014 11:23:34   RJamloki
 * Added defines for DAC values
 * 
 *    Rev 1.20   10 Nov 2014 04:59:42   AnPawar
 * ReadACTADC() function added . Added variable for io test.
 * 
 *    Rev 1.19   06 Oct 2014 06:45:44   AnPawar
 * changes for act ADC.
 * 
 *    Rev 1.18   03 Oct 2014 06:12:50   rjamloki
 * SetDigTune() function changed
 * 
 *    Rev 1.17   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.16   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.15   28 Jul 2014 12:40:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.14   11 Jun 2014 12:08:50   rjamloki
 * Digpot redundant functions removed
 * 
 *    Rev 1.13   21 May 2014 10:52:38   rjamloki
 * Changes related to Weld Trigger by Distance
 * 
 *    Rev 1.12   21 May 2014 03:41:36   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.11   07 May 2014 10:42:36   rjamloki
 * Recording an event on ShutDown() function.
 * 
 *    Rev 1.10   23 Apr 2014 13:49:34   akaushal
 * Reading Force and Pressure in one go. Added diagnostic for Actuator ADC read.
 * 
 *    Rev 1.9   21 Apr 2014 13:49:04   rjamloki
 * Code Cleanup
 * 
 *    Rev 1.8   14 Apr 2014 09:51:22   rjamloki
 * Changes to use AD7689 adc driver, Commented PVP functionality, cleaned up.
 * 
 *    Rev 1.7   26 Mar 2014 12:35:32   rjamloki
 * DIGPOT_MAX_VAL,DIGPOT_CENTER_VAL macro changed.WritePSDAC(),GetSpringForce(),SetDigPot() function changed
 * 
 *    Rev 1.6   06 Mar 2014 11:04:00   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:44   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:54   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:52   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: spidd.c

 Functions:
 1. InitPSNovram
 2. InitPVP
 3. InitBarGraph
 4. InitACTNovram

 The Digital Pot will be on Channel 12. The bit stream is 8 bits.
 It will set the center freq.
*/
 /*---------------------------- INCLUDE FILES -------------------------------*/

#include "mansensr.h"

#include "fpled.h"
#include "digout.h"
#include "preset.h"
#include "qsm.h"
#include "spidd.h"
#include "alarms.h"
#include "sc.h"
#include "ready.h"
#include "state.h"
#include "statedrv.h"
#include "snsrcalb.h"
#include "ticks.h"
#include "weld.h"
#include "getmsg.h"
#include "interpol.h"
#include "weld_obj.h"
#include "actnvram.h"
#include "battram.h"
#include "AD7890.h"
#include "TLV5604.h"
#include "menuhorn.h"
#include "psnvram.h"

/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define INCLUDE_UNIT_TEST
#define DIGTUNE_DAC_CENTER_VAL 0x200
#define MAX_TABLE_PTS 11
/* frequency bar graph defines */
#define LESSTHENBAR 0
#define GREATERTHENBAR 12
#define FilterIndex8 8
#define LOADCELLDELAY 63
#define REFOKAY 1000
#define PART_CONTACT_FILTER 2
#define WELD_FILTER 3                /* Changed from 1 to 3 for doing the filtering on force and fixing the Actuator's oscillation readings */
#define FIVE_LB 15
#define POWERUP_PRESSURE      -100   /* Value to determine first reading of Home Pressure   */
#define AD_NEG_OFFSET 3796           /* Needed for negative force values  */
#define AD_OFFSET 300                /* Needed to compensate for negative force values  */
#define MAXADC 0xFFFF
#define HALFVOLT 1638
#define MAX_DAC_OUTPUTRAW 1023 //max raw value which can be driven on TLV
#define MIN_EXT_AMP 10
#define MAX_EXT_AMP 100
#define MAXFILTERVAL_AMPSAMPLE 1000
#define MAXFILTERVAL_POWERSAMPLE 1333
#define MAX_FILTER_POINT 3
#define MAX_FILTER_INDEX 2
#define ENCODER_QUARTER_INCH 1250
#define ENCODER_SIX_INCH     60000



/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */
// Digital filter 3point throw away the high and low values
UINT16 FilterAmp[MAX_FILTER_POINT];
UINT16 FilterPower[MAX_FILTER_POINT];
UINT16 FilterFreq[MAX_FILTER_POINT];
UINT16 FilterMem[MAX_FILTER_POINT];
UINT16 FilterForce[MAX_FILTER_POINT];

UINT16 FilterAmpPtr = 0;
UINT16 FilterPowerPtr = 0;
UINT16 FilterFreqPtr = 0;
UINT16 FilterMemPtr = 0;
UINT16 FilterForcePtr = 0;
UINT16 TenVoltRef = 0;

//variables for iotest
UINT16 TestAdPressure = 0;
UINT16 TestAdForce = 0;

#if INCLUDE_UNIT_TEST
UINT16 TestForceData1[1024];
UINT16 TestForceData2[1024];
UINT16 TestPressureData[1024];
UINT16 TestPowerData[1024];
UINT16 TestAmplitudeData[1024];
UINT16 TestFrequencyData[1024];
#endif


UINT16 TriggerMet = FALSE;

BOOLEAN FirstTime;
BOOLEAN InitForceEstimateBuffer;
SINT16 LoadCellIndex;
UINT16 ADForce;
UINT16 ADPressure;
SINT16 AlarmHornWeight = 0; /* Created on an ErrorCode 300, used in the Debug menu */
SINT32 Distance1; /* Distance 1-3 used to determine part contact*/
UINT16 PartContactFlag;
SINT16 LoadCellCountDown = LOADCELLDELAY;

/* Inputs to the 332  */
UINT32 CurrentPowerIn; /* Value being read by 7890   */
UINT32 CurrentAmpIn; /* Value being read by 7890   */
UINT32 CurrentMemIn; /* Value being read by 7890   */
SINT32 CurrentFreqIn; /* Value being read by 7890   */
SINT32 CurrentPressure; /* Current pressure           */
SINT32 HomePressure = POWERUP_PRESSURE; /* Home pressure              */
SINT32 CurrentForce; /* Current pressure           */
SINT16 ExtFreqOffset; /* external frequency offset  */
UINT16 ExtAmp; /* external amplitude control */

/* ---------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                          (scope is global to THIS file)                  */

static UINT16 AmpSample = 0;
static UINT16 PowerSample = 0;
static UINT16 Shift_Amount = PART_CONTACT_FILTER;


// ------------------ Data For the Digital Filters --------------------

static UINT32 BufferAmp[FilterIndex8] = { 0,0,0,0,0,0,0,0 }; // Amp Buffer init. to 0.
static UINT32 BufferPower[FilterIndex8] = { 0,0,0,0,0,0,0,0 }; // Power Buffer init. to 0.
static UINT16 BufferFreq[FilterIndex8] = { 0,0,0,0,0,0,0,0 }; // Freq Buffer init. to 0.
static UINT16 ForceEstimateBuffer[4] = { 0, 0, 0, 0 };

static UINT32 *aptr = BufferAmp;
static UINT32 *pptr = BufferPower;
static UINT16 *fptr = &BufferFreq[0];

static UINT32 AmpSum = 0;
static UINT32 FrqSum = 0;
static UINT32 PwrSum = 0;

// ------------------- End of Digital Filter Data ---------------------


/*------------------------- EXTERNAL DATA ----------------------------------*/

extern BUCMENU_1200 BUCMenuRAM;
extern SINT32 EncoderPos;
extern SINT32 FActualBargraph, FMemoryBargraph;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;

extern enum WELDSTATES WeldState;
extern INBITS Inp;
extern BOOLEAN PoweredUp;
extern UINT32 CurrentVelocity;
extern UINT16 ResetReceivedFlag;

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

static void CheckEPSignals(void);
static UINT16 ForceEstimator(UINT16 NewSample);
static BOOLEAN PartContactMade(void);

static UINT16 GetFilterValue(UINT16 TableValue[]);
UINT16 DigFilterPressure(UINT16 Element);
//---------------------------------- CODE ----------------------------------


void WritePVP(UINT16 PVPValue)
{
	PVPValue  = 0;
}  


void InitPVP(void){
/* Actuator DAC 420 PVP Control */
/* need to remove some of registers once isr is running */
/* called when disabling digital pot */

}
 


void ReadACTADC(void)
{
/* This function is dependent on which actuator is attached. When an AE   */
/* actuator is attached, the door switch is checked when at ULS. If an    */
/* AED is attached, the pressure sensor and loadcell must be read. This   */
/* function will determine when partcontact and trigger conditions are met*/
/* when an AED actuator is attached. See SRS for complete algorithm       */ 
   SINT32 TempForce, TempPressure;
   SINT32 RawVals[2];
   if( ((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICRO) || (CurrentSetup.Actuator == MICROC))
      && (CurrentSetup.ControlLevel >= LEVEL_d))
   {
	   ActAdc->ReadInputs(1, (int *)RawVals);
	   TempForce = RawVals[0];
	   TempPressure = RawVals[1];

	   if(OnboardDiag)
	   {
		   TestAdPressure = TempPressure;
		   TestAdForce = TempForce;
	   }

	   ADPressure = DigFilterPressure((TempPressure & 0x0800) ? 0 : (UINT16)(TempPressure & 0x07FF));

	   if (TempForce & 0x800)
		   FilterForce[FilterForcePtr++] = (TempForce & 0xfff) - AD_NEG_OFFSET;
	   else
		   FilterForce[FilterForcePtr++] = (TempForce & 0x7ff) + AD_OFFSET;

	   LoadCellIndex = ADForce + ((GetFilterValue(FilterForce) - ADForce) >> Shift_Amount);

	   if(FilterForcePtr > MAX_FILTER_INDEX) FilterForcePtr = 0;

	   ADForce = LoadCellIndex;
	   CurrentPressure = GetInterpolatedSINT16(NVR.Pressure,ADPressure);

	   if (Inp.uls)
	   {
		   CurrentForce = 0;
		   Shift_Amount = PART_CONTACT_FILTER;
		   Distance1 = 0;

		   if (CurrentSequence != WELD || WeldState == READYSTATE)
			   CheckEPSignals();
	   }
	   else
	   {
		   LoadCellCountDown = LOADCELLDELAY;
		   LoadCellIndex -= GetSpringForce();
		   if (LoadCellIndex <= 0)
		   {
			   LoadCellIndex = 0;
			   CurrentForce = 0;
		   }
		   else
		   {
			   CurrentForce = GetInterpolatedSINT16(NVR.LoadCell, LoadCellIndex) - LoadCellOffset;
		   }

          if(CurrentForce < 0)
            CurrentForce = 0;

		   if (!Inp.Trigger)
		   {
			   if (EncoderPos >= ENCODER_QUARTER_INCH && EncoderPos < ENCODER_SIX_INCH)
			   {

				   if (!PartContactFlag)
					   PartContactFlag = PartContactMade();

				   if (PartContactFlag && Distance1 == 0)
				   {
					   Distance1 = EncoderPos;
					   Shift_Amount = WELD_FILTER;
				   }
				   if(HornDownFlag){
					   if (PartContactFlag && CurrentForce >= RunningPreset.TriggerForce)
						   Inp.Trigger = TRUE;
				   }
				   else
				   {
					   if((RunningPreset.WeldTrigger == TRIGGERBY_DISTANCE) && Inp.BothPB && (EncoderPos >= RunningPreset.TriggerDistance)){
							Inp.Trigger = TRUE;
							PartContactFlag = TRUE;
							WeldingResults.ActualTriggerDistance = EncoderPos;      /* Save position for coll calc */
					   }
					   else if ((RunningPreset.WeldTrigger == TRIGGERBY_FORCE) && PartContactFlag && CurrentForce >= RunningPreset.TriggerForce)
						   Inp.Trigger = TRUE;
				   }
			   }
		   }
	   }
   }

   else                                                                    /* an ae actuator    Copied from original rel 2.0 */
   {
	   if (Inp.uls && Inp.Trigger)
		   Inp.Trigger = FALSE;
   }
}


void ReadPSADC(void)
{
	SINT32 PsAdcVals[8];
	PsAdc->ReadInputsThroughSequencing((int*)PsAdcVals);
	AmpSample = PsAdcVals[1];
    PowerSample = PsAdcVals[2];
    FilterMem[FilterMemPtr++] = PsAdcVals[3];

   if(FilterMemPtr > MAX_FILTER_INDEX)
      FilterMemPtr = 0;                                  /* Freq Out of supply */

   FilterFreq[FilterFreqPtr++] = PsAdcVals[0];
   if(FilterFreqPtr > MAX_FILTER_INDEX)
      FilterFreqPtr = 0;                                /* Freq Out of supply */

   ExtAmp = PsAdcVals[5];
   ExtFreqOffset = PsAdcVals[4];

   UINT16 Ref10Volt = 0;

   if((WeldingResults.PSActControlFlags & BIT0) == FALSE)                  /* external amp */
   {
	     UINT32 temp = ExtAmp;

	     //Scaling to 100.5% so our values will round up
    	 temp = (temp * 201) / (MAXADC * 2);
         ExtAmp = (UINT16)temp;
         if(ExtAmp > MAX_EXT_AMP) ExtAmp = MAX_EXT_AMP;
         if(ExtAmp < MIN_EXT_AMP) ExtAmp = MIN_EXT_AMP;
   }
   if((WeldingResults.PSActControlFlags & BIT2) == FALSE)                  /* external amp */
   {
	   UINT32 temp = 0;

	   temp = ExtFreqOffset;
	   temp = (temp * MAX_DAC_OUTPUTRAW) / MAXADC;
	   ExtFreqOffset = temp;
   }
                                                                           /* check if value is positive:0 - 0x7ff = 0 - 10v = 0 - 100% for ampitude */
                                                                           /* and power  do 3 point filter */
   if(PoweredUp == FALSE)
   {
	  Ref10Volt =  PsAdcVals[6];
      if ((Ref10Volt & 0x8000) == 0x8000)
      {
         TenVoltRef = REFOKAY;
      }
      else
      {
         TenVoltRef = Ref10Volt * REFOKAY / MAXADC;
      }
   }
   else
   {
      if(RunningPreset.DigitalFilterFlag == TRUE)                          // Digital Filter is ON:
      {
         CurrentAmpIn = DigFilterAmp(AmpSample);
         CurrentAmpIn = (CurrentAmpIn * MAXFILTERVAL_AMPSAMPLE) / MAXADC;

         CurrentPowerIn = DigFilterPower(PowerSample);
         CurrentPowerIn = (CurrentPowerIn * MAXFILTERVAL_POWERSAMPLE) / MAXADC;
      }
      else                                                                 // Digital Filter is OFF:
      {
                                                                           // AMP CASE -----------------------------------------
         FilterAmp[FilterAmpPtr++] = AmpSample;
         if(FilterAmpPtr > MAX_FILTER_INDEX) FilterAmpPtr = 0;

         CurrentAmpIn = GetFilterValue(FilterAmp);
         CurrentAmpIn = (CurrentAmpIn * MAXFILTERVAL_AMPSAMPLE) / MAXADC;
                                                                           // POWER CASE ---------------------------------------
         FilterPower[FilterPowerPtr++] = PowerSample;
         if(FilterPowerPtr > MAX_FILTER_INDEX)
            FilterPowerPtr = 0;

         CurrentPowerIn = GetFilterValue(FilterPower);
         CurrentPowerIn = (CurrentPowerIn * MAXFILTERVAL_POWERSAMPLE) / MAXADC;
      }

      CurrentMemIn = GetFilterValue(FilterMem);
      //This function is used to determine which voltage range the memory is in
      //based on one volt increments with edges on half volts i.e. 4.5V to 5.5V
      //Incoming frequency is inverted so take the max value, subtract raw value,
      FMemoryBargraph = (MAXADC - CurrentMemIn - HALFVOLT) * 20 / MAXADC - 3;
      if (FMemoryBargraph < LESSTHENBAR)
    	  FMemoryBargraph = LESSTHENBAR;
      else if (FMemoryBargraph > GREATERTHENBAR)
    	  FMemoryBargraph = GREATERTHENBAR;

      CurrentFreqIn = GetFilterValue(FilterFreq);
      FActualBargraph = (MAXADC - CurrentFreqIn - HALFVOLT) * 20 / MAXADC - 3;
      if (FActualBargraph < LESSTHENBAR)
    	  FActualBargraph = LESSTHENBAR;
      else if (FActualBargraph > GREATERTHENBAR)
    	  FActualBargraph = GREATERTHENBAR;

         switch (CurrentSetup.PSFreq) {
            default:
            case FREQ20KHZ:
               CurrentFreqIn = CENTER20KHZ + SWING_20KHZ - (CurrentFreqIn * SWING_20KHZ * 2) / MAXADC;
               break;

            case FREQ40KHZ:
               CurrentFreqIn = CENTER40KHZ + SWING_40KHZ - (CurrentFreqIn * SWING_40KHZ * 2) / MAXADC;
               break;

            case FREQ15KHZ:
               CurrentFreqIn = CENTER15KHZ + SWING_15KHZ - (CurrentFreqIn * SWING_15KHZ * 2) / MAXADC;
               break;

            case FREQ30KHZ:
               CurrentFreqIn = CENTER30KHZ + SWING_30KHZ - (CurrentFreqIn * SWING_30KHZ * 2) / MAXADC;
               break;

            case FREQ60KHZ:
               CurrentFreqIn = CENTER60KHZ + SWING_60KHZ - (CurrentFreqIn * SWING_60KHZ * 2) / MAXADC;
               break;
         }

      if(RunningPreset.DigitalFilterFlag == TRUE)
         CurrentFreqIn = DigFilterFreq(CurrentFreqIn);
   }
 }

void WritePSDAC(UINT16 FreqValue, UINT16 AmpValue)
{
// The SPILIST[PSDAC] will have use 2 of the 16 command ram registers.
// Command Register [0] will output Frequency Offset and [1] will output
// Amplitude The Maxim Max532 is used to convert the 24 serial bit
// stream into the 2 channels of analog outputs.
// The voltage swing is from -10v to +10v. The following registers need to be
// changed before the list can be executed.
	PsDac->WriteOutput(0, FreqValue);
	PsDac->WriteOutput(1, AmpValue);
}

UINT16 DigFilterPressure(UINT16 Element)
{
	static UINT16 Buffer[FilterIndex8 * 4] = { 0 };
	static UINT16 * ptr = Buffer;
	static UINT32 Sum;
	UINT16 temp;   // Last Value
	if (ptr == &Buffer[FilterIndex8 * 4 - 1])
	{
		temp = *ptr;                                  // It was the last element
		*ptr = Element;
		ptr = Buffer;
	}
	else
	{
		temp = *ptr;                                  // It was the last element
		*ptr = Element;
		++ptr;
	}
	Sum = Sum + Element - temp;
	return (UINT16) (Sum >> 5);                          // Divide by 8;  -->000
}


static UINT16 GetFilterValue(UINT16 TableValue[]){

   UINT16 FilterValue;

   
                                                                           /* throw away element 0*/
   if((TableValue[0] < TableValue[1]) && (TableValue[0] < TableValue[2])){
                                                                           /* throw away element 1 */
      if(TableValue[1] > TableValue[2]){
         FilterValue = TableValue[2];
      }
                                                                           /* throw away element 2 */
      else{
         FilterValue = TableValue[1];
      }
   }
                                                                           /* throw away element 1*/
   else if((TableValue[1] < TableValue[0]) && (TableValue[1] < TableValue[2])){
                                                                           /* throw away element 1 */
      if(TableValue[0] > TableValue[2]){
         FilterValue = TableValue[2];
      }
                                                                           /* throw away element 2 */
      else{
         FilterValue = TableValue[0];
      }
   }
                                                                           /* throw away element 2*/
   else if((TableValue[2] < TableValue[0]) && (TableValue[2] < TableValue[1])){
                                                                           /* throw away element 0 */
      if(TableValue[0] > TableValue[1]){
         FilterValue = TableValue[1];
      }
                                                                           /* throw away element 1 */
      else{
         FilterValue = TableValue[0];
      }
   }
   else if((TableValue[0] == TableValue[1]) || (TableValue[0] == TableValue[2])){
         FilterValue = TableValue[0];
   }
   else if(TableValue[1] == TableValue[2]){
         FilterValue = TableValue[1];
   }
   else FilterValue = TableValue[0];
   return(FilterValue);
}


UINT16 GetSpringForce(void)
/****************************************************************************/
/*                                                                          */
/* This function subtracts off the spring force from the load cell reading  */
/*                                                                          */
/* Inputs: CurrentSetup.SpringRateTable                                     */
/*         EncoderPos                                                       */
/*                                                                          */
/****************************************************************************/


{
   UINT16 Offset,SpringIndex;

   SpringIndex = (UINT16) EncoderPos>>11;                                  /* Divide by 0x800 */
   if(SpringIndex == 0) SpringIndex = 1;                                   /* this compensates for the snubber */
   Offset = CurrentSetup.SpringRateTable[SpringIndex];
   return(Offset);
}

//#define DIGTUNE_DEBUG
#ifdef DIGTUNE_DEBUG
   extern SINT32 DigTuneValue;
#endif
void CenterDigTune(void){
#ifdef DIGTUNE_DEBUG
   printf("\n cntrdigp Cstp.DigTune %ld DigTuneVal %ld", CurrentSetup.DigTune, DigTuneValue);
#endif
   /**  **  Attempt to center the digital pot and force output  **  **/
   PsDac->WriteOutput(2, DIGTUNE_DAC_CENTER_VAL);
}


void SetDigTune(void){
   /* Called at power up & when chging DigTune*/
#ifdef DIGTUNE_DEBUG
   printf("\n setdp Cstp.DigTune %ld DigTuneVal %ld", CurrentSetup.DigTune, DigTuneValue);
#endif
   //Diving by 3000 since the DigTune freqenccy is scaled between -3000 to 3000 range for all PS frequencies
   int DigTune = DIGTUNE_DAC_CENTER_VAL + ((CurrentSetup.DigTune * DIGTUNE_DAC_CENTER_VAL) / 3000);
   if (DigTune > MAX_DAC_OUTPUTRAW)
	   DigTune = MAX_DAC_OUTPUTRAW;
   else if (DigTune < 0)
	   DigTune = 0;
   PsDac->WriteOutput(2, DigTune);
}


static void CheckEPSignals(void)
/*******************************************************************************/
/*                                                                             */
/* When at home check pressure changes.                                        */
/*                                                                             */
/* Inputs: CurrentPressure - read every 4ms                                    */
/*                                                                             */
/* Outputs: HomePressure - Averaged pressure at home                           */
/*                                                                             */
/*******************************************************************************/    
{

                                                                           /* Check for expiration of home position debounce timer. */
   if ((LoadCellCountDown-- < 0) || (ResetReceivedFlag == TRUE) )
   {
      if (HomePressure != POWERUP_PRESSURE) {
         HomePressure = HomePressure + ((CurrentPressure - HomePressure) >> 2);
      }
      else {
         HomePressure = CurrentPressure;                                   /* 1st reading after power up */
      }
      LoadCellCountDown = LOADCELLDELAY;    
   }                 
}
 


UINT32 DigFilterAmp (UINT32 Element){
/**************************************************************************
   The following filter functions take an element and return the average
   of the last indexfilter(8) back; It returnes the average of the last
   8 points. Using: Sum + New - Last / 8

***************************************************************************/

   UINT32 temp;                                                            // Last Value
   if(aptr==&BufferAmp[FilterIndex8-1]){
      temp=*aptr;                                                          // Move old to temp
      *aptr=Element;
      aptr=BufferAmp;
   }
   else{
      temp=*aptr;                                                          // Move old to temp
      *aptr=Element;                                                       // Insert new into buffer
      ++aptr;
   }
   AmpSum=AmpSum+Element-temp;
   return (AmpSum>>3);                                                  // Devide by 8;  -->000
}

UINT32 DigFilterPower (UINT32 Element){
UINT32 temp;   // Last Value
   if(pptr==&BufferPower[FilterIndex8-1]){
      temp=*pptr;                                                          // It was the last element
      *pptr=Element;
         pptr=BufferPower;
   }
   else{
      temp=*pptr;                                                          // It was the last element
      *pptr=Element;
      ++pptr;
   }
   PwrSum=PwrSum+Element-temp;
   return (PwrSum>>3);                                                   // Devide by 8;  -->000
}

UINT32 DigFilterFreq (UINT16 Element){
UINT16 temp;   // Last Value
   if(fptr==&BufferFreq[FilterIndex8-1]){
      temp=*fptr;                                                          // It was the last element
      *fptr=Element;
      fptr=&BufferFreq[0];
   }
   else{
      temp=*fptr;                                                          // It was the last element
      *fptr=Element;
      ++fptr;
   }
   FrqSum=FrqSum+Element-temp;
   return (FrqSum >> 3);                                                   // Devide by 8;  -->000
}

UINT16 ForceEstimator(UINT16 NewSample)
/*************************************************************************/
/* This code does force estimating using the filter [1/16,1/8,9/16,1/4]. */
/*************************************************************************/
{
   UINT16 Temp;
   if(InitForceEstimateBuffer)
   {
	   ForceEstimateBuffer[0] = ForceEstimateBuffer[1] = ForceEstimateBuffer[2] = ForceEstimateBuffer[3] = 0;
	   InitForceEstimateBuffer = FALSE;
   }

   ForceEstimateBuffer[0] = ForceEstimateBuffer[1];
   ForceEstimateBuffer[1] = ForceEstimateBuffer[2];
   ForceEstimateBuffer[2] = ForceEstimateBuffer[3];
   ForceEstimateBuffer[3] = NewSample;

   Temp = (ForceEstimateBuffer[0] + ForceEstimateBuffer[2]) >>2;
   Temp = Temp + (ForceEstimateBuffer[2]<<1) + ForceEstimateBuffer[3];
   Temp = ( Temp + (ForceEstimateBuffer[1] >>1) ) >>2;
   return (Temp);
}

//--------------------------- END OF FILTERS -------------------------------

BOOLEAN PartContactMade(void)
/************************************************************************/
/* This is the part contact algorithm.  It is called from ReadACTADC(). */
/************************************************************************/
{
   UINT16  ForceSum;
   BOOLEAN TriggerMet;

   TriggerMet = FALSE;
   ForceSum = ForceEstimator(CurrentForce);


   if (CurrentVelocity <= (UINT32)BUCMenuRAM.VelocityPC)                           /* Have we slowed down to part contact? */
   {
      if(ForceSum > (UINT16)BUCMenuRAM.ForcePC) {                          /* Are we exerting enough pressure on the part yet? */
         TriggerMet = TRUE;
      }
   }
   return(TriggerMet);
}



void CheckForHornChange(void)
/************************************************************************/
/*                                                                      */
/* This function checks for a horn weight change from the last power    */
/* up or the last EStop. It is called from TestPO3()and from weldmanger.*/
/*                                                                      */
/* Inputs: CurrentSetup.SpringRateTable[0] - Home weight offset         */
/*                                                                      */
/* Output: Alarm generated if condition met                             */
/*         AlarmHornWeight                                              */
/*                                                                      */
/************************************************************************/
{
   UINT16 LoadCellDifference;
   BUCMENU_1200  *BUCMenuFRAM;
   
   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   if (BUCMenuFRAM->RecalCode300 == TRUE) {
      if(CurrentSetup.SpringRateTable[0] > LoadCellIndex)
      {
         LoadCellDifference = CurrentSetup.SpringRateTable[0] - LoadCellIndex;
         if(LoadCellDifference > FIVE_LB)                                  /* a 5 lb change detected */
         {
            RecordErrorCode( ERRORCODE300_EQ20 );
            RecordAlarm(EQ20);                                             /* Recal actuator             */
            AlarmHornWeight = LoadCellIndex;                               /* Used in the Debug menu     */

         }
      }
      else
      {
         LoadCellDifference = LoadCellIndex - CurrentSetup.SpringRateTable[0];


         if(LoadCellDifference > FIVE_LB)
         {
            RecordErrorCode( ERRORCODE300_EQ20 );
            RecordAlarm(EQ20);                                             /* Recal actuator             */
            AlarmHornWeight = LoadCellIndex;                               /* Used in the Debug menu     */

         }
      }
   }
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\spidd.ut"
#endif   
/* End of include for unit test */

