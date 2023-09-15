/+ACo- +ACQ-Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/weldhold.cpp+AF8-v   1.32   Oct 10 2017 15:31:04   RJamloki  +ACQ- +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKg-
+ACQ-Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/weldhold.cpp+AF8-v  +ACQ-
 +ACo- 
 +ACo-    Rev 1.32   Oct 10 2017 15:31:04   RJamloki
 +ACo- added CurrentSetup.Actuator+AD0-MICROC in if statement that, evaluate actuator id's
 +ACo- 
 +ACo-    Rev 1.31   16 Apr 2015 07:18:10   rjamloki
 +ACo- Diagnostic code removed
 +ACo- 
 +ACo-    Rev 1.30   09 Apr 2015 05:32:58   RJamloki
 +ACo- Removed redundant weld and hold pressure update.
 +ACo- 
 +ACo-    Rev 1.29   08 Apr 2015 13:48:22   AnPawar
 +ACo- Changes for Pressure Stepping.
 +ACo- 
 +ACo-    Rev 1.28   30 Mar 2015 03:31:20   rjamloki
 +ACo- HoldForceMax changed to HoldForceEnd.
 +ACo- 
 +ACo-    Rev 1.27   16 Feb 2015 02:31:54   amaurya
 +ACo- calling PBReleaseOn() function at the end of weld to test actuator recalibrate alarm
 +ACo- 
 +ACo-    Rev 1.26   11 Feb 2015 06:30:56   amaurya
 +ACo- Changes to debug recalibrate actuator alarm issue
 +ACo- 
 +ACo-    Rev 1.25   08 Jan 2015 03:18:30   AnPawar
 +ACo- printf removed
 +ACo- 
 +ACo-    Rev 1.24   02 Jan 2015 04:13:26   rjamloki
 +ACo- StopAHold() function changed
 +ACo- 
 +ACo-    Rev 1.23   12 Dec 2014 05:32:02   RJamloki
 +ACo- Disabled Horn clamp for downspeed cycles
 +ACo- 
 +ACo-    Rev 1.22   11 Dec 2014 08:38:20   AnPawar
 +ACo- removed commented code
 +ACo- 
 +ACo-    Rev 1.21   28 Nov 2014 07:43:02   rjamloki
 +ACo- Warning Fix.
 +ACo- 
 +ACo-    Rev 1.20   10 Nov 2014 05:00:32   AnPawar
 +ACo- StartAHold() function doing SVoff() when hornclamp is false.12.F review change. 
 +ACo- 
 +ACo-    Rev 1.19   20 Oct 2014 06:34:10   AnPawar
 +ACo- StopAHold() and StopHold() function changed
 +ACo- 
 +ACo-    Rev 1.18   03 Oct 2014 06:18:12   rjamloki
 +ACo- StartAHold() function changed
 +ACo- 
 +ACo-    Rev 1.17   26 Sep 2014 03:39:12   rjamloki
 +ACo- Assigned DUPSOverloadType for menu display
 +ACo- 
 +ACo-    Rev 1.16   18 Aug 2014 01:48:22   rjamloki
 +ACo- Added MICRO Support. Corrected conditions in CheckForTriggerLost function for AE.
 +ACo- 
 +ACo-    Rev 1.15   28 Jul 2014 12:59:10   rjamloki
 +ACo- changes related to clamp on alarm
 +ACo- 
 +ACo-    Rev 1.14   15 Jul 2014 17:18:30   hasanchez
 +ACo- Changes about the Frequency offset
 +ACo- 
 +ACo-    Rev 1.13   09 Jul 2014 11:57:12   rjamloki
 +ACo- Removed Setting Pressure value at the end of hold as it is donein preready
 +ACo- 
 +ACo-    Rev 1.12   20 Jun 2014 14:14:52   rjamloki
 +ACo- Global SetPressure value for AES is updated to hold pressure on WeldOff states enetry.
 +ACo- 
 +ACo-    Rev 1.11   11 Jun 2014 12:40:30   rjamloki
 +ACo- removed redundant globals
 +ACo- 
 +ACo-    Rev 1.10   21 May 2014 10:53:14   rjamloki
 +ACo- Changes related to Weld Trigger by Distance
 +ACo- 
 +ACo-    Rev 1.9   21 May 2014 03:55:48   rjamloki
 +ACo- extern variables clean up and coverity fixes
 +ACo- 
 +ACo-    Rev 1.8   14 Apr 2014 10:27:12   rjamloki
 +ACo- Fixed to use right CPLD functions.
 +ACo- 
 +ACo-    Rev 1.7   26 Mar 2014 12:41:06   rjamloki
 +ACo-  removed macro and printf enabled.
 +ACo- 
 +ACo-    Rev 1.6   06 Mar 2014 11:04:02   rjamloki
 +ACo- Add User ID Functionality
 +ACo- 
 +ACo-    Rev 1.5   05 Mar 2014 13:56:50   rjamloki
 +ACo- Screens and PDf working
 +ACo- 
 +ACo-    Rev 1.4   10 Feb 2014 05:00:00   rjamloki
 +ACo- Preset changes to support 1000 preset.
 +ACo- 
 +ACo-    Rev 1.3   03 Jan 2014 08:45:58   rjamloki
 +ACo- Header Fix.
 +ACo-
 +ACo-
 +ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKg-/
/+ACo---------------------------- MODULE DESCRIPTION ---------------------------+ACo-/
/+ACo-                                                                          +ACo-/
/+ACo- Module name: Weldhold                                                    +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo- Filename:    Weldhold.c                                                  +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo- Function Name: State machine code                                        +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-          Written by:   Barry E. Kymer                                    +ACo-/
/+ACo-                Date:   03-15-96                                          +ACo-/
/+ACo-            Language:   +ACI-C+ACI-                                               +ACo-/
/+ACo------------------------------ DESCRIPTION ----------------------------------+ACo-/

/+ACo- This module contains the code for the weld state, hold state.            +ACo-/


/+ACo------------------------------ PSEUDO CODE --------------------------------+ACo-/


/+ACo----------------------------- LOCAL+AF8-EQUATES -------------------------------+ACo-/

+ACM-define ABRAMPDOWNTIME        10 /+ACo- Time from Allan Roberts - 20 ms   08-08-96  +ACo-/
                                 /+ACo- Changed to 10 ms by Kevin Klein   04-16-97  +ACo-/
+ACM-define AMPSTEPTRIGGERTIME     2 /+ACo- If amp trigger occurs before this time-alarm+ACo-/
+ACM-define ENCODERFAILTIME       25 /+ACo- Time a minimum distance must be reached in  +ACo-/
+ACM-define ENCODERDETECTDISTANCE 50 /+ACo- Minimum distance within ENCODERFAILTIME     +ACo-/
+ACM-define FORCE+AF8-DEBOUNCE+AF8-TIME    9 /+ACo- Time (ms) a new force exists before being   +ACo-/
                                 /+ACo- considered a new max force (should be less  +ACo-/
                                 /+ACo- than minimum weld time so a value is always +ACo-/
                                 /+ACo- displayed)                                  +ACo-/


+ACM-define ALTERNATEHOLDTIME     10 /+ACo- Time to catch overloads if hold disabled    +ACo-/

+ACM-define AMPWINDOW 2            // I'm going to open a window  2+ACU- relative
                               // to Amp1 and Amp2
                                    
/+ACo------------------------------- INCLUDES ----------------------------------+ACo-/

+ACM-include +ACI-names.h+ACI-
+ACM-include +ACI-portable.h+ACI-
+ACM-include +ACI-state.h+ACI-
+ACM-include +ACI-menu.h+ACI-
+ACM-include +ACI-preset.h+ACI-
+ACM-include +ACI-weld+AF8-obj.h+ACI-
+ACM-include +ACI-alarms.h+ACI-
+ACM-include +ACI-weldhold.h+ACI-
+ACM-include +ACI-timer.h+ACI-
+ACM-include +ACI-statedrv.h+ACI-
+ACM-include +ACI-digout.h+ACI-
+ACM-include +ACI-outports.h+ACI-
+ACM-include +ACI-fpled.h+ACI-
+ACM-include +ACI-mansensr.h+ACI-
+ACM-include +ACI-util.h+ACI-
+ACM-include +ACI-ready.h+ACI-
+ACM-include +ACI-menu7a.h+ACI-
+ACM-include +ACI-dups+AF8-api.h+ACI-
+ACM-include +ACI-ready.h+ACI-
+ACM-include +ACI-weld.h+ACI-
+ACM-include +ACI-stdio.h+ACI-
+ACM-include +ACI-CPLD.h+ACI-


/+ACo--------------------------- PRIVATE GLOBAL DATA ---------------------------+ACo-/
struct PORT0 Port0+ADs-
struct PORT1 Port1+ADs-
struct PORT2 Port2+ADs-
static SINT16   SonicStepTimer+ADs-
static SINT16   SonicTimer, HoldTimer, ScrubTimer+ADs-
static SINT16   WeldPressureTimer+ADs-
static SINT16   SeekDelay+ADs-
static UINT16   DelayStartFlag +AD0- TRUE+ADs-

static BOOLEAN  WeldPressureFlag, ScrubTimerFlag+ADs-

enum OL+AF8-PENDING+AHs-
      NOT+AF8-PENDING,
      WELD+AF8-OL,
      SEEK+AF8-OL,
      AB+AF8-OL+AH0AOw-

static enum OL+AF8-PENDING OlPending +AD0- NOT+AF8-PENDING+ADs-

static SINT32   RampStartValue, RampStopValue, RampDiff+ADs-
static SINT32   RampTime, RampRunningTime+ADs-
static SINT32   EnergyBrakeTimer+ADs-
static SINT32   AmpRampTime, AmpRampTime10, AmpRampTime25, AmpRampTime50, AmpRampTime95+ADs-

static void UpdateOLType(SINT32 OverloadReason)+ADs-

BOOLEAN         SeekEndFlag, RampUpDirection, RampEndFlag+ADs-
BOOLEAN         GroundDetectFlag+ADs-

SINT16 TriggerLostTimerFlag, TriggerLostTimerID+ADs-

UINT16 EncoderFailTimer+ADs-
UINT16 ActualABDelay+ADs-
UINT16 MaxForceDebounce+ADs-
UINT16 NewMaxForce+ADs-

SINT32 TriggerLostTime+ADs-/+ACo- Time (after 150ms) when trigger was declared lost +ACo-/
SINT32 TriggerLostForce+ADs-/+ACo- Force when trigger was declared lost             +ACo-/
SINT32 ActualAfterburstTime+ADs-
SINT32 ActualHoldTime+ADs-
UINT32 ActualSeekTime+ADs-
UINT32 ABOverloadPower+ADs-
SINT32 AccurateCollapse+ADs-
SINT32 AccurateAbsolute+ADs-
SINT32 AmpRamp+ADs-
SINT32 NextRampValue+ADs-
SINT32 EBOverloadTimer+ADs-
SINT32 EBOverloadPower+ADs-
SINT32 EBOverloadFreq+ADs-  

BOOLEAN TriggerLostHistoryFlag, TriggerLostFlag+ADs-
BOOLEAN AmpStepReachedFlag +AD0- FALSE, PressureStepReachedFlag +AD0- FALSE, HornReturnFlag +AD0- TRUE+ADs-
SINT32 CurrentPower+ADs-                   /+ACo- weldhold, ready  +ACo-/
UINT8 CollectEnergyFlag +AD0- FALSE+ADs-
SINT32  ActualTriggerForce+ADs-
SINT32  ActualFreqEnd+ADs-
BOOLEAN ClampOnAlarm +AD0- FALSE+ADs-

void VerifySBL(void)+ADs- 

extern WELD+AF8-OBJECT +ACo-MsDataPtr+ADs-
extern SINT32 Distance1+ADs-               /+ACo- Distance 1-3 used to determine part contact+ACo-/


extern SINT32   EncoderPos+ADs-
extern SINT32   AccumulatedEnergy, EnergyInJoules, EnergyCalc+ADs-
extern SINT32   CurrentForce+ADs-
extern UINT16   TestKeyRepeat+ADs-
extern UINT16   TestModeAllowed+ADs-
extern SINT32   CurrentFreqIn+ADs-        /+ACo- Value being read by 7890          +ACo-/
extern UINT32   CurrentPowerIn+ADs-         /+ACo- Value being read by 7890          +ACo-/
extern UINT32   CurrentAmpIn+ADs-
extern SINT32   EnergyNeeded+ADs-
extern UINT16   Update5ms+ADs-
extern UINT8    AETrigger+ADs-
extern INBITS   Inp+ADs-
extern UINT16   HornReturnCount+ADs-
extern UINT16   PartContactFlag+ADs-       
extern BOOLEAN  CycleAbort+ADs-
extern SINT16   PeakPower+ADs-
extern enum WELDSTATES WeldState+ADs-
extern BUCMENU+AF8-1200 BUCMenuRAM+ADs-
extern BOOLEAN ECycleHistFlag+ADs-
extern BOOLEAN MissingPartFlag+ADs-
extern BOOLEAN DownspeedTuneFlag+ADs-
/+ACo- DUPS related stuff +ACo-/

DUPS+AF8-WELDSTATUS WeldOLStatus+ADs-
DUPS+AF8-WELDSTATUS SeekOLStatus+ADs-
DUPS+AF8-WELDSTATUS ABOLStatus+ADs-



//- ---------------------------  MY WINDOW -------------------------------

SINT32 +ACo-A+AF8-Setup+AD0AJg-RunningPreset.Amp1+ADs-            
SINT32 +ACo-B+AF8-Setup+AD0AJg-RunningPreset.Amp2+ADs-                  
SINT32 +ACo-LastA+AD0AJg-WeldingResults.ActualAmplitudeStart+ADs- 
SINT32 +ACo-LastB+AD0AJg-WeldingResults.ActualAmplitudeEnd+ADs- 

//-------------------------------- CODE ----------------------------------


void DisplayTestPower(SINT16 Power) 
+AHs-
   SINT16 LedPower +AD0- 0+ADs-

   if (CurrentSetup.TestMultiplier +AD0APQ- TESTTIMEx1) +AHs-
      LedPower +AD0- Power+ADs-
   +AH0-
   else if (CurrentSetup.TestMultiplier +AD0APQ- TESTTIMEx2) +AHs-
      LedPower +AD0- Power +ACo- 2+ADs-
   +AH0-
   else if (CurrentSetup.TestMultiplier +AD0APQ- TESTTIMEx3) +AHs-
      LedPower +AD0- Power +ACo- 3+ADs-
   +AH0-
   LedPower /+AD0- POWERDIV+ADs-
   UpdateBarGraph(LedPower)+ADs-
+AH0-



void DisplayWeldPower(SINT16 Power) 
+AHs-
   SINT16 LedPower +AD0- 0+ADs-

   if (CurrentSetup.TimeMultiplier +AD0APQ- WELDTIMEx1) +AHs-
      LedPower +AD0- Power+ADs-
   +AH0-
   else if (CurrentSetup.TimeMultiplier +AD0APQ- WELDTIMEx2) +AHs-
      LedPower +AD0- Power +ACo- 2+ADs-
   +AH0-
   else if (CurrentSetup.TimeMultiplier +AD0APQ- WELDTIMEx3) +AHs-
      LedPower +AD0- Power +ACo- 3+ADs-
   +AH0-
   LedPower /+AD0- POWERDIV+ADs-
   UpdateBarGraph(LedPower)+ADs-
+AH0-



BOOLEAN CheckForTriggerLost(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This function will check to see if trigger has been lost.  It will take +ACo-/
/+ACo-  the passed value (Force-the current required force) and compare it with +ACo-/
/+ACo-  the current actual force.  If the required force is less then the       +ACo-/
/+ACo-  actual force for more then 150ms a Trigger Lost error has occured.  A   +ACo-/
/+ACo-  TRUE will be returned if trigger has been lost, a FALSE will be         +ACo-/
/+ACo-  returned if all is okay.                                                +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  If trigger was lost and then restored within the 150ms all is okay and  +ACo-/
/+ACo-  the 150ms timer is reset.                                               +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  Also, this function will check for MAX force.                           +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  NOTE: As agreed to by B. Kymer, C. Linley, N. Galer, B.Jalbert, N. Wu,  +ACo-/
/+ACo-        and L. Markure, trigger will not be considered lost until the     +ACo-/
/+ACo-        actual force is at or below the part contact force, which is      +ACo-/
/+ACo-        currently defined the same as the minimum trigger force.          +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   BOOLEAN RetVal +AD0- FALSE+ADs- /+ACo- Return value, assume okay for now   +ACo-/
	SINT32 TRSLostTime+ADs-
	if ((CurrentSetup.Actuator +AD0APQ- AED) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- AES) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICRO) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICROC)) +AHs-
		if (CurrentPreset.WeldTrigger +AD0APQ- TRIGGERBY+AF8-FORCE) +AHs-
			if (CurrentForce +ADw- MinLimit.TriggerForce) +AHs-
				if (TriggerLostHistoryFlag +AD0APQ- FALSE) +AHs- /+ACo- Was trigger already lost    +ACo-/
					StartUpTimer(TRIGGERLOSTTIMER)+ADs-
					TriggerLostHistoryFlag +AD0- TRUE+ADs-
				+AH0- else +AHs-
					TRSLostTime +AD0- GetUpTimer(TRIGGERLOSTTIMER)+ADs-
					if (TRSLostTime +AD4- (SINT32) TRIGGERLOSTTIME) +AHs-/+ACo- See if time to great  +ACo-/
						RetVal +AD0- TRUE+ADs- /+ACo- FALSE means trigger lost error NOW+ACE- +ACo-/
						if (TriggerLostTime +AD0APQ- 0) +AHs- /+ACo- Test to ensure only updated once +ACo-/
							TriggerLostTime +AD0- GetUpTimer(SONICSTIMER)+ADs-/+ACo- Get cycle time right now    +ACo-/
						+AH0-
						TriggerLostForce +AD0- CurrentForce+ADs- /+ACo- Get force as of right now   +ACo-/
					+AH0-
				+AH0-
			+AH0- else +AHs- /+ACo- Trigger Ok now, but was it ok before+ACo-/
				if (TriggerLostHistoryFlag +AD0APQ- TRUE) +AHs-
					ResetUpTimer(TRIGGERLOSTTIMER)+ADs-
					TriggerLostHistoryFlag +AD0- FALSE+ADs-
				+AH0-
			+AH0-

			/+ACo----  Check for safety condition +AFs-less then 35 lbs with 1/4+ACI- travel+AF0-  ---+ACo-/

			if ((CurrentForce +ADw- TRIGGERLOSTFORCE) +ACYAJg- (EncoderPos +AD4- (WeldingResults.ActualTriggerDistance
							 (SINT32) TRIGGERLOSTDISTANCE))) +AHs-
				SVOff()+ADs- /+ACo- Immediately turn off SV  +ACo-/
				RecordErrorCode(ERRORCODE200+AF8-EQ20)+ADs-
				RecordAlarm(EQ20)+ADs- /+ACo- Record alarm            +ACo-/
				AbortFlag +AD0- TRUE+ADs-  /+ACo- Abort state sequence    +ACo-/
			+AH0-

			/+ACo----  Check for safety condition +AFs-lifting off the part 1/4+ACIAXQ-  ---+ACo-/

			if (WeldingResults.ActualTriggerDistance +AD4- (SINT32) TRIGGERLOSTDISTANCE) +AHs-
				if (EncoderPos +ADw- (WeldingResults.ActualTriggerDistance - (SINT32) TRIGGERLOSTDISTANCE)) +AHs-
					SVOff()+ADs- /+ACo- Immediately turn off SV  +ACo-/
					RecordErrorCode(ERRORCODE400+AF8-EQ20)+ADs-
					RecordAlarm(EQ20)+ADs- 	/+ACo- Record alarm             +ACo-/
					AbortFlag +AD0- TRUE+ADs- 	/+ACo- Abort state sequence     +ACo-/
				+AH0-
			+AH0-

		+AH0- else +AHs-
			if (EncoderPos +ADw- (WeldingResults.ActualTriggerDistance
					- (SINT32) TRIGGERLOSTDISTANCE)) +AHs-
				if (TriggerLostHistoryFlag +AD0APQ- FALSE) +AHs- /+ACo- Was trigger already lost    +ACo-/
					StartUpTimer(TRIGGERLOSTTIMER)+ADs-
					TriggerLostHistoryFlag +AD0- TRUE+ADs-
				+AH0- else +AHs-
					TRSLostTime +AD0- GetUpTimer(TRIGGERLOSTTIMER)+ADs-
					if (TRSLostTime +AD4- (SINT32) TRIGGERLOSTTIME) +AHs-/+ACo- See if time to great  +ACo-/
						RetVal +AD0- TRUE+ADs- /+ACo- FALSE means trigger lost error NOW+ACE- +ACo-/
						if (TriggerLostTime +AD0APQ- 0) +AHs- /+ACo- Test to ensure only updated once +ACo-/
							TriggerLostTime +AD0- GetUpTimer(SONICSTIMER)+ADs-/+ACo- Get cycle time right now    +ACo-/
						+AH0-
						TriggerLostForce +AD0- 0+ADs- /+ACo- 0lbs for AE   +ACo-/
					+AH0-
				+AH0-
			+AH0- else +AHs- /+ACo- Trigger Ok now, but was it ok before+ACo-/
				if (TriggerLostHistoryFlag +AD0APQ- TRUE) +AHs-
					ResetUpTimer(TRIGGERLOSTTIMER)+ADs-
					TriggerLostHistoryFlag +AD0- FALSE+ADs-
				+AH0-
			+AH0-
		+AH0-
	+AH0- else +AHs- /+ACo- AE trigger lost  +ACo-/
		if (AETrigger +AD0APQ- FALSE) +AHs-
			if (TriggerLostHistoryFlag +AD0APQ- FALSE) +AHs- /+ACo- Was trigger already lost    +ACo-/
				StartUpTimer(TRIGGERLOSTTIMER)+ADs-
				TriggerLostHistoryFlag +AD0- TRUE+ADs-
			+AH0- else +AHs-
				TRSLostTime +AD0- GetUpTimer(TRIGGERLOSTTIMER)+ADs-
				if (TRSLostTime +AD4- (SINT32) TRIGGERLOSTTIME) +AHs-/+ACo- See if time to great  +ACo-/
					RetVal +AD0- TRUE+ADs- /+ACo- FALSE means trigger lost error NOW+ACE- +ACo-/
					if (TriggerLostTime +AD0APQ- 0) +AHs- /+ACo- Test to ensure only updated once +ACo-/
						TriggerLostTime +AD0- GetUpTimer(SONICSTIMER)+ADs-/+ACo- Get cycle time right now    +ACo-/
					+AH0-
					TriggerLostForce +AD0- 0+ADs- /+ACo- 0lbs for AE   +ACo-/
				+AH0-
			+AH0-
		+AH0- else +AHs- /+ACo- Trigger Ok now, but was it ok before+ACo-/
			if (TriggerLostHistoryFlag +AD0APQ- TRUE) +AHs-
				ResetUpTimer(TRIGGERLOSTTIMER)+ADs-
				TriggerLostHistoryFlag +AD0- FALSE+ADs-
			+AH0-
		+AH0-
	+AH0-

	return (RetVal)+ADs-
+AH0-



void CheckForSafety(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This function will check to see if horn has traveled 1/4+ACI- after part    +ACo-/
/+ACo-  contact and still have not built up at least 35 lbs of force.  If this  +ACo-/
/+ACo-  occurs, the cycle will be aborted and an alarm will be generated.  This +ACo-/
/+ACo-  function will be called while waiting for trigger.  Once trigger has    +ACo-/
/+ACo-  been reached then CheckForTriggerLost will be called.                   +ACo-/
/+ACo-  returned if all is okay.                                                +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  Note:  The variable Distance1 is set in spidd.c when part contact is    +ACo-/
/+ACo-         determined.                                                      +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   if (((CurrentSetup.Actuator +AD0APQ- AED) +AHwAfA-
        (CurrentSetup.Actuator +AD0APQ- AES) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICRO) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICROC))+ACYAJg- (RunningPreset.WeldTrigger +AD0APQ- TRIGGERBY+AF8-FORCE))
   +AHs-
      if ( (CurrentForce +ADw- TRIGGERLOSTFORCE) +ACYAJg-
           (CycleAbort +AD0APQ- FALSE) +ACYAJg-
           (PartContactFlag +AD0APQ- TRUE) +ACYAJg-
           (EncoderPos +AD4- (Distance1  (SINT32) TRIGGERLOSTDISTANCE)) ) +AHs-
           SVOff()+ADs-                                  /+ACo- Immediately turn off SV  +ACo-/
           RecordErrorCode( ERRORCODE900+AF8-EQ20 )+ADs-
           RecordAlarm(EQ20)+ADs-                        /+ACo- Record alarm             +ACo-/
           AbortFlag +AD0- TRUE+ADs-                         /+ACo- Abort state sequence     +ACo-/
      +AH0-
   +AH0-
+AH0-


void EnterTrigDly(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo- This function will do the delay after trigger is reached.  It will first +ACo-/
/+ACo- try to set the force to the trigger force to keep the force constant on  +ACo-/
/+ACo- the part.                                                                +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   TriggerDelayTimer +AD0- StartTimer(RunningPreset.TriggerDelay,
                                  +ACY-TriggerDelayFlag, 40)+ADs-
+AH0-



void ExitTrigDly(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo- This function will deal with the force after the trigger delay has timed +ACo-/
/+ACo- out.  It will set the force to the weld force value.                     +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
//   SetPV((UINT16)RunningPreset.WeldForce, TRG+AF8-TO+AF8-FORCE+AF8-A)+ADs-
+AH0-



void CheckControlLimitsD(UINT16 EncoderCheck)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo- This function will check the control limits.  If they are globally off   +ACo-/
/+ACo- then only the max timeout will be checked.  If they are globally on,     +ACo-/
/+ACo- then each one will be checked to see if it is on.  If it is on, then the +ACo-/
/+ACo- values will be checked to determine if the cycle should be aborted.  In  +ACo-/
/+ACo- any case the max timeout will be checked.  If max timeout is disabled,   +ACo-/
/+ACo- unless is not allowed in the current weld mode, a default value will be  +ACo-/
/+ACo- used.  If enabled then the user defined value will be used.              +ACo-/
/+ACo- The passed argument 'EncoderCheck' will be used to determine if the      +ACo-/
/+ACo- encoder should be checked for movement.  If it should be checked (TRUE)  +ACo-/
/+ACo- and the value is less than ENCODERDETECTDISTANCE then alarm EQ1 will be  +ACo-/
/+ACo- recorded.                                                                +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  moved out of states. The final data was not being updated correctly     +ACo-/
/+ACo-  and the next cycles weld time was shorter.                              +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/
+AHs-

   CheckControlLimits()+ADs-                  /+ACo- Call non distance checks first +ACo-/

/+ACo------  Check Encoder to be sure its still working correctly  -----+ACo-/

   if (EncoderCheck +AD0APQ- TRUE) +AHs-
      if (EncoderPos +ADw- ENCODERDETECTDISTANCE) +AHs-
         EncoderFailTimer+ADs-
         if (EncoderFailTimer +AD4APQ- ENCODERFAILTIME) +AHs-
            RecordAlarm(EQ1)+ADs-
         +AH0-
      +AH0-
   +AH0-

/+ACo--- Check for Absolute Distance before trigger (Absolute Mode only)  --+ACo-/
/+ACo--  If the EncoderPos value is larger than MaxLimit.AbsDist (could    -+ACo-/
/+ACo--  also be negative, which isn't allowed here either) then the       -+ACo-/
/+ACo--  encoder is not working correctly, so make alarm Encoder Failed    -+ACo-/


   if (RunningPreset.WeldMode +AD0APQ- ABSOLUTEMODE) +AHs-
      if ( (EncoderPos +AD4APQ- RunningPreset.AbsDist) +ACYAJg-
           (WeldingResults.ActualTriggerDistance +AD0APQ- 0) ) +AHs- 
           if (EncoderPos +AD4- MaxLimit.AbsDist) +AHs-
              RecordAlarm(EQ1)+ADs-           /+ACo- If not triggered yet +ACo-/
           +AH0-
           else +AHs-
              RecordAlarm(NC9)+ADs-           /+ACo- If not triggered yet +ACo-/
           +AH0-
      +AH0-
   +AH0-
   else +AHs-
      if (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE) +AHs- /+ACo- Control limits on ? +ACo-/


/+ACo-----  Next check for Absolute Distance Cutoff (All mode but Absolute) ----+ACo-/

         if ((RunningPreset.ABSCutoffFlag +ACY- /+ACo-BSCutoff.BitMask+ACo-/BIT0) +AD0APQ- 0) +AHs-
            if (EncoderPos +AD4APQ- RunningPreset.ABSCutoffDist) +AHs-
               if (WeldingResults.ActualTriggerDistance +ACEAPQ- 0) +AHs- 
                  AccurateAbsolute +AD0- EncoderPos+ADs-
                  RecordAlarm(W6)+ADs-            /+ACo- If already triggered +ACo-/
               +AH0-
               else +AHs-
                  RecordAlarm(NC9)+ADs-           /+ACo- If not triggered yet +ACo-/
               +AH0-
            +AH0-
         +AH0-   
      +AH0-
   +AH0-


/+ACo------  First see if Control limits are even enabled  -----+ACo-/

   if (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE) +AHs-


/+ACo------  Next check for Collapse Distance Cutoff  -----+ACo-/

      if ( ((RunningPreset.ColCutoffFlag +ACY- /+ACo-ABSCutoff.BitMask+ACo-/BIT0) +AD0APQ- 0) +ACYAJg-
            (RunningPreset.WeldMode +ACEAPQ- COLLAPSEMODE) ) +AHs-
         if (WeldingResults.ActualTriggerDistance +ACEAPQ- 0)+AHs- /+ACo- If already triggered +ACo-/
            if ((EncoderPos - WeldingResults.ActualTriggerDistance) +AD4APQ- RunningPreset.ColCutoffDist) +AHs-
               RecordAlarm(W9)+ADs-
               AccurateCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs-
            +AH0-
         +AH0-
      +AH0-   
   +AH0-
+AH0-



void CheckControlLimits(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo- This function will check the control limits.  If they are globally off   +ACo-/
/+ACo- then only the max timeout will be checked.  If they are globally on,     +ACo-/
/+ACo- then each one will be checked to see if it is on.  If it is on, then the +ACo-/
/+ACo- values will be checked to determine if the cycle should be aborted.  In  +ACo-/
/+ACo- any case the max timeout will be checked.  If max timeout is disabled,   +ACo-/
/+ACo- unless is not allowed in the current weld mode, a default value will be  +ACo-/
/+ACo- used.  If enabled then the user defined value will be used.              +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  moved out of states. The final data was not being updated correctly     +ACo-/
/+ACo-  and the next cycles weld time was shorter.                              +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/
+AHs-
   SINT32  TempTimeValue+ADs-

   TempTimeValue +AD0- GetUpTimer(SONICSTIMER)+ADs-

/+ACo------  Now see if Control limits are even enabled  -----+ACo-/

   if (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE) +AHs-


/+ACo------  Now check for Peak Power Cutoff  -----+ACo-/

      if ((RunningPreset.PeakPwrCutoffFlag +ACY- /+ACo-PeakPowerCutoff.BitMask+ACo-/BIT0) +AD0APQ- 0) +AHs-
         if ( (RunningPreset.PeakPwrCutoff +ADwAPQ- PeakPower) +ACYAJg-
              (RunningPreset.WeldMode +ACEAPQ- PKPOWERMODE) ) +AHs-
            RecordAlarm(W5)+ADs-
         +AH0-
      +AH0-


/+ACo------  Next deal with TEC mode (Energy compensation)                 -----+ACo-/

      if ( (RunningPreset.EnergyCompFlag +AD0APQ- TRUE)     +ACYAJg-
           (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE)  +ACYAJg-   /+ACo-TRUE +AD0-On+ACo-/
           (CurrentSetup.ControlLevel +AD4APQ- LEVEL+AF8-e)      +ACYAJg-
           (CycleAbort +AD0APQ- FALSE)                      +ACYAJg-
           (RunningPreset.WeldMode +AD0APQ- TIMEMODE) ) +AHs-
         if (EnergyInJoules-3 +AD4APQ- RunningPreset.EnergyML) +AHs-
            if ((TempTimeValue - 1) +AD4- RunningPreset.WeldTime) +AHs-
               RecordAlarm(W7)+ADs-
            +AH0-
            else if (TempTimeValue +AD0APQ- RunningPreset.WeldTime) +AHs-
               SonicsAbort +AD0- TRUE+ADs-               /+ACo- Stop sonics             +ACo-/
            +AH0-
         +AH0-
         if (EnergyInJoules-3 +AD4APQ- RunningPreset.EnergyPL) +AHs-
            RecordAlarm(W2)+ADs-
         +AH0-
      +AH0-
   +AH0-

/+ACo------  For safety, now check on max timeout (Control Limits on/off)  -----+ACo-/

   if ((WeldState +AD0APQ- WELDTIMESTATE) +AHwAfA- (WeldState +AD0APQ- WELDTIME2STATE))+AHs-
      if ((/+ACo-MaxTimeout.mode+ACo-/(ENERGYMODE +AHw- PKPOWERMODE +AHw- COLLAPSEMODE +AHw- ABSOLUTEMODE +AHw-GRDDETECTMODE) +ACY- RunningPreset.WeldMode) +AD0APQ- RunningPreset.WeldMode) +AHs-
         if (TempTimeValue +AD4APQ- RunningPreset.MaxTimeout) +AHs- 
            RecordAlarm(CM3)+ADs-
         +AH0-
      +AH0-
   +AH0-
   
/+ACoAKgAq-   +ACoAKgAq-   Now some test code to determine the starting ramp   +ACoAKgAq-   +ACoAKgAq-/

   AmpRampTime+ADs-
   if ( ((CurrentAmpIn/10) +AD4APQ- 95) +ACYAJg- (AmpRampTime95 +AD0APQ- 0) ) AmpRampTime95 +AD0- AmpRampTime+ADs-
   if ( ((CurrentAmpIn/10) +AD4APQ- 50) +ACYAJg- (AmpRampTime50 +AD0APQ- 0) ) AmpRampTime50 +AD0- AmpRampTime+ADs-
   if ( ((CurrentAmpIn/10) +AD4APQ- 25) +ACYAJg- (AmpRampTime25 +AD0APQ- 0) ) AmpRampTime25 +AD0- AmpRampTime+ADs-
   if ( ((CurrentAmpIn/10) +AD4APQ- 10) +ACYAJg- (AmpRampTime10 +AD0APQ- 0) ) AmpRampTime10 +AD0- AmpRampTime+ADs-
+AH0-



void CheckCycleAborts(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo- This function will check the cycle aborts.  If they are globally on      +ACo-/
/+ACo- then each one will be checked to see if it is on.  If it is on, then the +ACo-/
/+ACo- values will be checked to determine if the cycle should be aborted.      +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/
/+ACo-  moved out of states. The final data was not being updated correctly     +ACo-/
/+ACo-  and the next cycles weld time was shorter.                              +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/
+AHs-

/+ACo------  First check for External Cycle Abort   -----+ACo-/

   if (ECycleHistFlag +AD0APQ- TRUE) +AHs-
      if (GetUpTimer(SONICSTIMER) +AD4APQ- 1) +AHs-
         RecordAlarm(CM15)+ADs-           /+ACo- After trigger  +ACo-/
      +AH0-
      else +AHs-
         RecordAlarm(NC7)+ADs-            /+ACo- Before trigger +ACo-/
      +AH0-
   +AH0-

/+ACo------  Next see if Cycle Aborts are even enabled  -----+ACo-/

   if (RunningPreset.CycleAbortFlag +AD0APQ- TRUE) +AHs-


/+ACo------  Next check for Ground Detect Cutoff  -----+ACo-/

/+ACo---------------------------------------------------------------------------+ACo-/
/+ACo-  Think about a timer when ground detect is active.  If ground detect     +ACo-/
/+ACo-  goes away before the timer expires, then ignore the ground detect input.+ACo-/
/+ACo-  This will help ensure we stop sonics only when really needed and not    +ACo-/
/+ACo-  when there is a small hole in the material.  (See Bill Surprenant)      +ACo-/
/+ACo-  Must check ground detect input before trigger in ground detect mode     +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/
      if ((RunningPreset.GndDetectFlag +AD0APQ- TRUE) +ACYAJg-
              (RunningPreset.WeldMode +ACEAPQ- GRDDETECTMODE))+AHs-
         if (Inp.GndDet +AD0APQ- TRUE) +AHs-
            if (GetUpTimer(SONICSTIMER) +AD4APQ- 1) +AHs-
               RecordAlarm(CM2)+ADs-           /+ACo- After trigger  +ACo-/
            +AH0-
            else +AHs-
               RecordAlarm(NC12)+ADs-          /+ACo- Before trigger +ACo-/
            +AH0-
         +AH0-
      +AH0-
   +AH0-
/+ACo- need to check for ground detect before trigger in ground detect mode +ACo-/
   if((RunningPreset.WeldMode +AD0APQ- GRDDETECTMODE) +ACYAJg-
      (Inp.GndDet +AD0APQ- TRUE)) +AHs-
      if (GetUpTimer(SONICSTIMER) +ADw- 1) +AHs-
         RecordAlarm(NC12)+ADs-          /+ACo- Before trigger +ACo-/
      +AH0-
   +AH0-
+AH0-



void  CheckEnergyComp(void)
+AHs-
/+ACo------  First see if Control limits are even enabled  -----+ACo-/

   if ( (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE) +ACYAJg-
        (RunningPreset.EnergyCompFlag +AD0APQ- TRUE)    +ACYAJg-
        (CurrentSetup.ControlLevel +AD4APQ- LEVEL+AF8-e)     +ACYAJg-
        (RunningPreset.WeldMode +AD0APQ- TIMEMODE)      +ACYAJg-
        (CycleAbort +AD0APQ- FALSE) ) +AHs-
           if (WeldingResults.TotalEnergy +ADw- RunningPreset.EnergyML) +AHs-
              RecordAlarm(CM21)+ADs-
           +AH0-
           if ((WeldingResults.ActualWeldTime - 1) +AD4- RunningPreset.WeldTime) +AHs-
              RecordAlarm(W7)+ADs-
           +AH0-
   +AH0-
+AH0-

/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-
+ACo-
+ACo-   Purpose:
+ACo-	This function will check the various Pressure triggers and see if it
+ACo-   is time to switch to the second Pressure. If it is time, then the
+ACo-   switch will be done.
+ACo-
+ACo-   Entry condition:
+ACo-	void
+ACo-
+ACo-   Exit condition:
+ACo-	void
+ACo-
+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
void CheckForPressureStepping(void)
+AHs-
   if (((RunningPreset.Pressure2Flag +ACY- BIT0) +AD0APQ- BIT0)
         +ACYAJg- (PressureStepReachedFlag +AD0APQ- FALSE)) +AHs-
      switch (RunningPreset.Pressure2Flag) +AHs-
      case ((UINT16) +AH4-BIT2): /+ACo- Stepping enabled on time          +ACo-/
         if ((WeldPressureTimer +ACEAPQ- FALSE) +ACYAJg- (WeldPressureFlag +AD0APQ- FALSE)) +AHs-
            SetPressureValue +AD0- CurrentPreset.Pressure2+ADs-
            PressureStepReachedFlag +AD0- TRUE+ADs-
            MsDataPtr-+AD4-PressureStepAtTime +AD0- RunningPreset.PressureTrigTimeValue+ADs-
            WeldPressureTimer +AD0- 0+ADs- /+ACo- Turn off flag to prevent further checking+ACo-/
         +AH0-
         break+ADs-

      case ((UINT16) +AH4-BIT3): /+ACo- Stepping enabled on energy        +ACo-/
         if (RunningPreset.PressureTrigEnerValue +ADwAPQ- EnergyInJoules) +AHs-
            SetPressureValue +AD0- CurrentPreset.Pressure2+ADs-
            PressureStepReachedFlag +AD0- TRUE+ADs-
            MsDataPtr-+AD4-PressureStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
         +AH0-
         break+ADs-

      case ((UINT16) +AH4-BIT4): /+ACo- Stepping enabled on peak power    +ACo-/
         if (RunningPreset.PressureTrigPowerValue +ADwAPQ- PeakPower) +AHs-
            SetPressureValue +AD0- CurrentPreset.Pressure2+ADs-
            PressureStepReachedFlag +AD0- TRUE+ADs-
            MsDataPtr-+AD4-PressureStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
         +AH0-
         break+ADs-

      case ((UINT16) +AH4-BIT5): /+ACo- Stepping enabled on collapse dist +ACo-/
         if (RunningPreset.PressureTrigColValue
               +ADwAPQ- (EncoderPos - WeldingResults.ActualTriggerDistance)) +AHs-
            SetPressureValue +AD0- CurrentPreset.Pressure2+ADs-
            PressureStepReachedFlag +AD0- TRUE+ADs-
            MsDataPtr-+AD4-PressureStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
         +AH0-
         break+ADs-

      case PRESSURE+AF8-STEP+AF8-AT+AF8-EXTERNAL: /+ACo- Stepping enabled on external in   +ACo-/
         if (Inp.ExternalTrigger +AD0APQ- TRUE) +AHs-
            SetPressureValue +AD0- CurrentPreset.Pressure2+ADs-
            PressureStepReachedFlag +AD0- TRUE+ADs-
            MsDataPtr-+AD4-PressureStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
         +AH0-
         break+ADs-

      default:
         break+ADs-
      +AH0-
   +AH0-

+AH0-

void CheckForForceStepping(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-   This function will check the various force triggers and see if it is  +ACo-/
/+ACo-   time to switch to the second force.  If it is time, then the switch   +ACo-/
/+ACo-   will be done.                                                         +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-   It will then check the various amplitude triggers and see if it is    +ACo-/
/+ACo-   time to switch to the second amplitude.  If it is time, then the      +ACo-/
/+ACo-   switch will be done.                                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if ( ((RunningPreset.Amp2Flag +ACY- BIT0) +AD0APQ- BIT0) +ACYAJg-  /+ACo- If stepping on and +ACo-/
         (CurrentSetup.AmpControl +AD0APQ- TRUE)        +ACYAJg-  /+ACo- amp is internal +ACY-  +ACo-/
         (AmpStepReachedFlag +AD0APQ- FALSE) ) +AHs-            /+ACo- not stepped yet    +ACo-/

/+ACo- save ampA(amplitudestart) to final results before switching to ampB  +ACo-/
/+ACo- must subtract 1 from time(power supply delays sonics for 1ms +ACo-/
      switch (RunningPreset.Amp2Flag) +AHs-
         case ((UINT16)+AH4-BIT2):                 /+ACo- Stepping enabled on time          +ACo-/
            if (GetUpTimer(SONICSTIMER) +AD4APQ- RunningPreset.AmpTrigTimeValue) +AHs-
               if (GetUpTimer(SONICSTIMER) +ADw- AMPSTEPTRIGGERTIME) +AHs-
                  RecordAlarm(NC10)+ADs-
               +AH0-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- RunningPreset.AmpTrigTimeValue+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT3):                 /+ACo- Stepping enabled on energy        +ACo-/
            if (RunningPreset.AmpTrigEnerValue +ADwAPQ- EnergyInJoules) +AHs-
               if (GetUpTimer(SONICSTIMER) +ADw- AMPSTEPTRIGGERTIME) +AHs-
                  RecordAlarm(NC10)+ADs-
               +AH0-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) -1)+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT4):                 /+ACo- Stepping enabled on peak power    +ACo-/
            if (RunningPreset.AmpTrigPowerValue +ADwAPQ- PeakPower) +AHs-
               if (GetUpTimer(SONICSTIMER) +ADw- AMPSTEPTRIGGERTIME) +AHs-
                  RecordAlarm(NC10)+ADs-
               +AH0-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT5):                 /+ACo- Stepping enabled on collapse dist +ACo-/
            if (RunningPreset.AmpTrigColValue +ADwAPQ- (EncoderPos - WeldingResults.ActualTriggerDistance)) +AHs-

/+ACo-- This check removed to fix DCS +ACM- 2045.  By definition of collapse, the -+ACo-/
/+ACo-- step condition could not occur before trigger because there can be no -+ACo-/
/+ACo-- collapse before trigger.                                               +ACo-/

               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case AMP+AF8-STEP+AF8-AT+AF8-EXTERNAL:                  /+ACo- Stepping enabled on external in   +ACo-/
            if (Inp.ExternalTrigger +AD0APQ- TRUE) +AHs-
               if (GetUpTimer(SONICSTIMER) +ADw- AMPSTEPTRIGGERTIME) +AHs-
                  RecordAlarm(NC10)+ADs-
               +AH0-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-

         default:
            break+ADs-
      +AH0-
   +AH0-
   CheckForPressureStepping()+ADs-
+AH0-



void StartSonic1(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with turning on the sonics for     +ACo-/
/+ACo-  the first weld pressure.  Two conditions can exist: 1) Amplitude step  +ACo-/
/+ACo-  is enabled or 2) Amplitude step is disabled.                           +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Amplitude step enabled:  SonicStepTimer+AD0-timer id for time of step one  +ACo-/
/+ACo-                           SonicTimer+AD0-timer id for total sonics on time  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Amplitude step disabled: SonicStepTimer+AD0-timer id total sonics on time  +ACo-/
/+ACo-                           SonicTimer+AD0-timer id for total sonics on time  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   UINT16  FirstTimeValue+ADs-

/+ACo---   Before doing anything, make 1 final check for missing part  --+ACo-/
   if(RunningPreset.WeldTrigger +ACEAPQ- TRIGGERBY+AF8-DISTANCE)
	   WeldingResults.ActualTriggerDistance +AD0- EncoderPos+ADs-      /+ACo- Save position for coll calc +ACo-/
   AccurateCollapse +AD0- 0+ADs-
   AccurateAbsolute +AD0- 0+ADs-
   MissingPartFlag +AD0- CheckForMissingPartMin()+ADs-
   if (MissingPartFlag +AD0APQ- TRUE) +AHs-       /+ACo- If TRUE, alarm and abort cycle  +ACo-/
      RecordAlarm(NC8)+ADs-
   +AH0-
   else +AHs-                               /+ACo- If FALSE, then proceed normally +ACo-/
      CollectEnergyFlag +AD0- TRUE+ADs-
      DelayStartFlag +AD0- TRUE+ADs-
      CoolValOn()+ADs-   

/+ACo------ Deal with the new cycle trigger stuff -----+ACo-/
   /+ACo- check for encoder failed (but only if cycle not aborted) +ACo-/
      if (CycleAbort +AD0APQ- FALSE) +AHs-
         if (( (CurrentSetup.Actuator +AD0APQ- AED) +AHwAfA-
              (CurrentSetup.Actuator +AD0APQ- AES) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICRO) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICROC)) +ACYAJg- (EncoderPos +ADw- ENCODERDETECTDISTANCE))
            RecordAlarm(EQ1)+ADs-
      +AH0-

      StartUpTimer(SONICSTIMER)+ADs-
      WeldingResults.ActualFreqStart +AD0- CurrentFreqIn+ADs- /+ACo- Get starting frequency  +ACo-/
      CheckFrequencyLimits()+ADs-

      PeakPower +AD0- 0+ADs-                           /+ACo- Reset last peak power +ACo-/

      SetCurrentAmp(RunningPreset.Amp1)+ADs-       /+ACo- Initial amplitude           +ACo-/
      PSRun()+ADs-                                 /+ACo- Start sonics                +ACo-/
      AmpRampTime +AD0- 0+ADs-
      AmpRampTime10 +AD0- 0+ADs-
      AmpRampTime25 +AD0- 0+ADs-
      AmpRampTime50 +AD0- 0+ADs-
      AmpRampTime95 +AD0- 0+ADs-
      
/+ACoAKg-  +ACoAKg- This timer is the total length of time Sonics are on  +ACoAKg-  +ACoAKg-/

      FirstTimeValue +AD0- RunningPreset.WeldTime+ADs- /+ACo- Control limits off so no Energy Comp +ACo-/

/+ACo----- Deal with amplitude stepping (Consider Energy Comp)  ----+ACo-/

      if (RunningPreset.ControlLimitsFlag +AD0APQ- TRUE) +AHs-
         if (RunningPreset.EnergyCompFlag +AD0APQ- TRUE) +AHs-
            FirstTimeValue +AD0- ((RunningPreset.WeldTime)  ((RunningPreset.WeldTime ) +AD4APg- 1))+ADs- /+ACo- Assume Step is off, Energy Comp is ON +ACo-/
            if (FirstTimeValue +AD4APQ- MAXWELDTIME  1) FirstTimeValue+AD0-MAXWELDTIME+ADs- 
         +AH0-
         else +AHs-
            FirstTimeValue +AD0- RunningPreset.WeldTime+ADs-   /+ACo- Assume Step is off, Energy Comp is off   +ACo-/
         +AH0-
      +AH0-

      SonicTimer +AD0- StartTimer(FirstTimeValue, +ACY-WTimeFlag, 7)+ADs-
      if (SonicTimer +AD0APQ- FAILED1) +AHs-
         SonicTimer +AD0- 0+ADs-
      +AH0-
      else if (SonicTimer +AD0APQ- FAILED2) +AHs-
         SonicTimer +AD0- 0+ADs-
      +AH0-
      AmpStepReachedFlag +AD0- FALSE+ADs-
      PressureStepReachedFlag +AD0- FALSE+ADs-

      if ((RunningPreset.Amp2Flag +ACY- BIT0) +AD0APQ- BIT0) +AHs- /+ACo- See if amplitude step is on +ACo-/
         switch (RunningPreset.Amp2Flag) +AHs-
            case ((UINT16)+AH4-BIT2):                    /+ACo- Stepping enabled on time          +ACo-/
               FirstTimeValue +AD0- (RunningPreset.AmpTrigTimeValue)+ADs-/+ACo- Step is on   +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT3):                    /+ACo- Stepping enabled on energy        +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT4):                    /+ACo- Stepping enabled on peak power    +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT5):                    /+ACo- Stepping enabled on collapse dist +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT6):                    /+ACo- Stepping enabled on amplitude     +ACo-/
               break+ADs-
   
            case AMP+AF8-STEP+AF8-AT+AF8-EXTERNAL:                       /+ACo- Stepping enabled on external in   +ACo-/
               break+ADs-
     
            default:
               break+ADs-
         +AH0-
      +AH0-
   
/+ACoAKg-  +ACoAKg- This timer is the length of time for Sonic1 state  +ACoAKg-  +ACoAKg-/

      SonicStepTimer +AD0- StartTimer(FirstTimeValue, +ACY-StepTimeFlag, 17)+ADs-
      if (SonicStepTimer +AD0APQ- FAILED1) +AHs-
         SonicStepTimer +AD0- 0+ADs-
      +AH0-
      else if (SonicStepTimer +AD0APQ- FAILED2) +AHs-
         SonicStepTimer +AD0- 0+ADs-
      +AH0-

      /+ACoAKg-  +ACoAKg- This timer is started for duration defined by Step at Time trigger in Pressure Step menu  +ACoAKg-  +ACoAKg-/
         if ((RunningPreset.Pressure2Flag +ACY- BIT0) +AD0APQ- BIT0) +AHs-
            WeldPressureTimer +AD0- StartTimer(RunningPreset.PressureTrigTimeValue, +ACY-WeldPressureFlag, 19)+ADs-
            if (WeldPressureTimer +AD0APQ- FAILED1)
                WeldPressureTimer +AD0- 0+ADs-
            else if (WeldPressureTimer +AD0APQ- FAILED2)
                WeldPressureTimer +AD0- 0+ADs-
         +AH0-
         else +AHs-
            WeldPressureTimer +AD0- FALSE+ADs-
            WeldPressureFlag +AD0- FALSE+ADs-
         +AH0-
   +AH0-
+AH0-

   

void StartSonic1A(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with turning on the sonics for     +ACo-/
/+ACo-  CONTINUOUS mode.                                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   SetSAS()+ADs-                                /+ACo- Output Sonics Active signal +ACo-/
   StartUpTimer(SONICSTIMER)+ADs-
   
   WeldingResults.ActualFreqStart +AD0- CurrentFreqIn+ADs- /+ACo- Get starting frequency  +ACo-/
   CheckFrequencyLimits()+ADs-
   PeakPower +AD0- 0+ADs-                           /+ACo- Reset last peak power +ACo-/
   WeldingResults.ActualWeldTime +AD0- 0+ADs-      /+ACo- Reset last actual weld time +ACo-/

   SetCurrentAmp(RunningPreset.Amp1)+ADs-       /+ACo- Initial amplitude           +ACo-/
   PSRun()+ADs-                                 /+ACo- Start sonics                +ACo-/
   WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
+AH0-



void CheckSonics1D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to sonic state 2.                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-

   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/

   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-


void CheckSonics1(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to sonic state 2.                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-

   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/

   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-


void CheckSonics1A(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should turn off sonics in CONTINUOUS mode only.                        +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Note:  This function must check for continuous power rating being      +ACo-/
/+ACo-         exceeded.                                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
+AH0-




void StartSonic2(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If RunningPreset.Amp2Flag BIT0 is TRUE then   +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-

   if ( ((RunningPreset.Amp2Flag +ACY- BIT0) +AD0APQ- BIT0) +ACYAJg-  /+ACo- If stepping on and +ACo-/
         (CurrentSetup.AmpControl +AD0APQ- TRUE)        +ACYAJg-  /+ACo- amp is internal +ACY-  +ACo-/
         (AmpStepReachedFlag +AD0APQ- FALSE) ) +AHs-            /+ACo- not stepped yet    +ACo-/

/+ACo- save ampA before switching to ampB +ACo-/
/+ACo- must subtract 1 from time(power supply delays sonics for 1ms +ACo-/
      switch (RunningPreset.Amp2Flag) +AHs-
         case ((UINT16)+AH4-BIT2):                 /+ACo- Stepping enabled on time          +ACo-/
            if (GetUpTimer(SONICSTIMER) +AD4APQ- RunningPreset.AmpTrigTimeValue) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- RunningPreset.AmpTrigTimeValue+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT3):                 /+ACo- Stepping enabled on energy        +ACo-/
            if (RunningPreset.AmpTrigEnerValue +ADwAPQ- EnergyInJoules) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT4):                 /+ACo- Stepping enabled on peak power    +ACo-/
            if (RunningPreset.AmpTrigPowerValue +ADwAPQ- PeakPower) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT5):                 /+ACo- Stepping enabled on collapse dist +ACo-/
            if (RunningPreset.AmpTrigColValue +ADwAPQ- (EncoderPos -WeldingResults.ActualTriggerDistance)) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case ((UINT16)+AH4-BIT7):                 /+ACo- Stepping enabled on absolute dist +ACo-/
            if (RunningPreset.AmpTrigAbsValue +ADwAPQ- (EncoderPos -WeldingResults.ActualTriggerDistance)) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         case AMP+AF8-STEP+AF8-AT+AF8-EXTERNAL:                  /+ACo- Stepping enabled on external in   +ACo-/
            if (Inp.ExternalTrigger +AD0APQ- TRUE) +AHs-
               AmpStepReachedFlag +AD0- TRUE+ADs-
               WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
               SetCurrentAmp(RunningPreset.Amp2)+ADs-
               MsDataPtr-+AD4-AmpStepAtTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
            +AH0-
            break+ADs-
   
         default:
            break+ADs-
      +AH0-
   +AH0-
   CheckForPressureStepping()+ADs-
+AH0-



void CheckSonics2D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state (TIME MODE only).                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/

   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-




void CheckSonics2(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state (TIME MODE only).                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/

   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void StartSonic3(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with turning on the sonics for     +ACo-/
/+ACo-  the first weld pressure.  Two conditions can exist: 1) Amplitude step  +ACo-/
/+ACo-  is enabled or 2) Amplitude step is disabled.                           +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Amplitude step enabled:  SonicStepTimer+AD0-timer id for time of step one  +ACo-/
/+ACo-                           SonicTimer+AD0-timer id for total sonics on time  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Amplitude step disabled: SonicStepTimer+AD0-timer id total sonics on time  +ACo-/
/+ACo-                           SonicTimer+AD0-timer id for total sonics on time  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  NOTE: ENERGY MODE, ABSOLUTE MODE, COLLAPSE MODE, PEAK POWER MODE +ACY-     +ACo-/
/+ACo-  GROUND DETECT ONLY                                                     +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   UINT16  FirstTimeValue+ADs-

/+ACo---   Before doing anything, make 1 final check for missing part  --+ACo-/
   if(RunningPreset.WeldTrigger +ACEAPQ- TRIGGERBY+AF8-DISTANCE)
	 WeldingResults.ActualTriggerDistance +AD0- EncoderPos+ADs-      /+ACo- Save position for coll calc +ACo-/
   AccurateCollapse +AD0- 0+ADs-
   AccurateAbsolute +AD0- 0+ADs-
   MissingPartFlag +AD0- CheckForMissingPartMin()+ADs-
   if (MissingPartFlag +AD0APQ- TRUE) +AHs-       /+ACo- If TRUE, alarm and abort cycle  +ACo-/
      RecordAlarm(NC8)+ADs-
   +AH0-
   else +AHs-                               /+ACo- If FALSE, then proceed normally +ACo-/
      if (RunningPreset.WeldMode +AD0APQ- ENERGYMODE) +AHs-
         EnergyCalc +AD0- (100000 / CurrentSetup.PSWatt)+ADs-
         if (RunningPreset.WeldEnergy +AD4APQ- 2000) +AHs- /+ACo- Prevent overflow, lose a little accuracy +ACo-/
            EnergyNeeded +AD0- RunningPreset.WeldEnergy +ACo- EnergyCalc+ADs-  /+ACo- Convert to energy units   +ACo-/
         +AH0-
         else +AHs-      /+ACo- Overflow not a problem here, keep accuracy instead  +ACo-/
            EnergyNeeded +AD0- RunningPreset.WeldEnergy +ACo- 100000+ADs- /+ACo- 1/10's of millejoules +ACo-/
            EnergyNeeded /+AD0- CurrentSetup.PSWatt+ADs-    /+ACo- Convert to energy units   +ACo-/
         +AH0-
      +AH0-   
      CollectEnergyFlag +AD0- TRUE+ADs-
      DelayStartFlag +AD0- TRUE+ADs-

/+ACo------ Deal with the new cycle trigger stuff -----+ACo-/

      CoolValOn()+ADs-

/+ACo- check for encoder failed (but only if cycle not aborted) +ACo-/

      if (CycleAbort +AD0APQ- FALSE) +AHs-
         if ( ((CurrentSetup.Actuator +AD0APQ- AED) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- AES)
		 +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICRO) +AHwAfA- (CurrentSetup.Actuator +AD0APQ- MICROC)) +ACYAJg- (EncoderPos +ADw- ENCODERDETECTDISTANCE))
            RecordAlarm(EQ1)+ADs-
      +AH0-
      GroundDetectFlag +AD0- FALSE+ADs-
      ScrubTimerFlag +AD0- FALSE+ADs-
      StartUpTimer(SONICSTIMER)+ADs-
      WeldingResults.ActualFreqStart +AD0- CurrentFreqIn+ADs- /+ACo- Get starting frequency  +ACo-/
      CheckFrequencyLimits()+ADs-
      PeakPower +AD0- 0+ADs-                           /+ACo- Reset last peak power +ACo-/

      MissingPartFlag +AD0- CheckForMissingPartMin()+ADs-
   
      SetCurrentAmp(RunningPreset.Amp1)+ADs-       /+ACo- Initial amplitude           +ACo-/
      PSRun()+ADs-                                 /+ACo- Start sonics                +ACo-/
      FirstTimeValue +AD0- (RunningPreset.MaxTimeout  1)+ADs-        /+ACo- use user supplied value  +ACo-/
      
      if ((/+ACo-MaxTimeout.mode+ACo-/(ENERGYMODE +AHw- PKPOWERMODE +AHw- COLLAPSEMODE +AHw- ABSOLUTEMODE +AHw-GRDDETECTMODE) +ACY- RunningPreset.WeldMode) +AD0APQ-   /+ACo- If weld mode allows        +ACo-/
            RunningPreset.WeldMode) +AHs-                     /+ACo- timeout, then and only then+ACo-/
         FirstTimeValue +AD0- (RunningPreset.MaxTimeout  1)+ADs- /+ACo- use user supplied value    +ACo-/
      +AH0-
      else +AHs-
         FirstTimeValue +AD0- (DEFAULT+AF8-MAXTIMEOUT  1)+ADs-
      +AH0-
   
/+ACoAKg-  +ACoAKg- This timer is the total length of time Sonics are on  +ACoAKg-  +ACoAKg-/

      SonicTimer +AD0- StartTimer(FirstTimeValue, +ACY-WTimeFlag, 7)+ADs-
      if (SonicTimer +AD0APQ- FAILED1) +AHs-
         SonicTimer +AD0- 0+ADs-
      +AH0-
      else if (SonicTimer +AD0APQ- FAILED2) +AHs-
         SonicTimer +AD0- 0+ADs-
      +AH0-
      AmpStepReachedFlag +AD0- FALSE+ADs-
      PressureStepReachedFlag +AD0- FALSE+ADs-
   
      if ((RunningPreset.Amp2Flag +ACY- BIT0) +AD0APQ- BIT0) +AHs- /+ACo- See if amplitude step is on +ACo-/
         switch (RunningPreset.Amp2Flag) +AHs-
            case ((UINT16)+AH4-BIT2):              /+ACo- Stepping enabled on time          +ACo-/
               FirstTimeValue +AD0- (RunningPreset.AmpTrigTimeValue)+ADs-/+ACo- Step is on   +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT3):              /+ACo- Stepping enabled on energy        +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT4):              /+ACo- Stepping enabled on peak power    +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT5):              /+ACo- Stepping enabled on absolute dist +ACo-/
               break+ADs-
   
            case ((UINT16)+AH4-BIT6):              /+ACo- Stepping enabled on amplitude     +ACo-/
               break+ADs-
   
            case AMP+AF8-STEP+AF8-AT+AF8-EXTERNAL:                 /+ACo- Stepping enabled on external in   +ACo-/
               break+ADs-
       
            default:
               break+ADs-
        +AH0-
      +AH0-
/+ACoAKg-  +ACoAKg- This timer is the length of time for Sonic1 state  +ACoAKg-  +ACoAKg-/

      SonicStepTimer +AD0- StartTimer(FirstTimeValue, +ACY-StepTimeFlag, 17)+ADs-
      if (SonicStepTimer +AD0APQ- FAILED1) +AHs-
         SonicStepTimer +AD0- 0+ADs-
      +AH0-
      else if (SonicStepTimer +AD0APQ- FAILED2) +AHs-
         SonicStepTimer +AD0- 0+ADs-
      +AH0-
       /+ACoAKg-  +ACoAKg- This timer is started for duration defined by Step at Time trigger in Pressure Step menu  +ACoAKg-  +ACoAKg-/
            if ((RunningPreset.Pressure2Flag +ACY- BIT0) +AD0APQ- BIT0) +AHs-
               WeldPressureTimer +AD0- StartTimer(RunningPreset.PressureTrigTimeValue, +ACY-WeldPressureFlag, 19)+ADs-
               if (WeldPressureTimer +AD0APQ- FAILED1)
                  WeldPressureTimer +AD0- 0+ADs-
               else if (WeldPressureTimer +AD0APQ- FAILED2)
                  WeldPressureTimer +AD0- 0+ADs-
            +AH0-
            else +AHs-
               WeldPressureTimer +AD0- FALSE+ADs-
               WeldPressureFlag +AD0- FALSE+ADs-
            +AH0-

   +AH0-
+AH0-



void CheckSonics3D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2 (ENERGY MODE only).               +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (AccumulatedEnergy +AD4APQ- EnergyNeeded) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, energy value reached     +ACo-/
   +AH0-

   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics3(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2 (ENERGY MODE only).               +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (AccumulatedEnergy +AD4APQ- EnergyNeeded) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, energy value reached     +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics3A(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  ABSOLUTE MODE ONLY                                                     +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (EncoderPos +AD4APQ- RunningPreset.AbsDist) +AHs-
      AccurateAbsolute +AD0- EncoderPos+ADs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics3B(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  COLLAPSE MODE ONLY                                                     +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (EncoderPos +AD4- WeldingResults.ActualTriggerDistance) +AHs-
      if ((EncoderPos - WeldingResults.ActualTriggerDistance) +AD4APQ- RunningPreset.ColDist) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, collapse value reached +ACo-/
         AccurateCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs-
      +AH0-
   +AH0-
   else +AHs-  /+ACo- Here, as per conversation with Kevin K., start a 10 ms       +ACo-/
           /+ACo- timer.  If the collapse is still negative, then create some  +ACo-/
           /+ACo- kind of an alarm.  We guess this will only happened once in  +ACo-/
           /+ACo- the life of the product, long after we remember talking      +ACo-/
           /+ACo- about it.       BEKymer   08-12-96 (after Kevin returned     +ACo-/
           /+ACo- from Mid Ohio)                                               +ACo-/
      +ADs-
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics3CD(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  PEAK POWER MODE ONLY                                                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (PeakPower +AD4APQ- RunningPreset.PeakPwr) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics3C(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  PEAK POWER MODE ONLY                                                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (PeakPower +AD4APQ- RunningPreset.PeakPwr) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics8D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  GROUND DETECT MODE ONLY                                                +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (Inp.GndDet +AD0APQ- TRUE) +AHs-
      if (GroundDetectFlag +AD0APQ- FALSE) +AHs-
         GroundDetectFlag +AD0- TRUE+ADs-
         if ((RunningPreset.ScrubTime     +ACEAPQ- 0) +ACYAJg-
              (RunningPreset.ScrubTimeFlag +AD0APQ- 0)) //Scrub Time(s) isn't Off
         +AHs-
            ScrubTimer +AD0- StartTimer(RunningPreset.ScrubTime,
                                    +ACY-ScrubTimerFlag, 60)+ADs-
            SetCurrentAmp(RunningPreset.AmpScrubTime)+ADs-
            MsDataPtr-+AD4-ScrubStartAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
         +AH0-
      +AH0-
      else if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-
   else if (GroundDetectFlag +AD0APQ- TRUE) +AHs- /+ACo- Had Grd Detect, but lost it, check anyway +ACo-/
      if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-   
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics8(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking to decide when we    +ACo-/
/+ACo-  should move on to stop sonic state 2.                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  GROUND DETECT MODE ONLY                                                +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(DelayStartFlag +AD0APQ- TRUE)+AHs-
      DelayStartFlag +AD0- FALSE+ADs-
      SetSAS()+ADs-
      ActualTriggerForce +AD0- CurrentForce+ADs-
   +AH0-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (Inp.GndDet +AD0APQ- TRUE) +AHs-
      if (GroundDetectFlag +AD0APQ- FALSE) +AHs-
         GroundDetectFlag +AD0- TRUE+ADs-
         if ((RunningPreset.ScrubTime     +ACEAPQ- 0) +ACYAJg-
              (RunningPreset.ScrubTimeFlag +AD0APQ- 0))  //Scrub Time(s) isn't Off
         +AHs-
            ScrubTimer +AD0- StartTimer(RunningPreset.ScrubTime,
                                    +ACY-ScrubTimerFlag, 60)+ADs-
            SetCurrentAmp(RunningPreset.AmpScrubTime)+ADs-
            MsDataPtr-+AD4-ScrubStartAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
         +AH0-
      +AH0-
      else if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-
   else if (GroundDetectFlag +AD0APQ- TRUE) +AHs- /+ACo- Had Grd Detect, but lost it, check anyway +ACo-/
      if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-   
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics4D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  ENERGY MODE ONLY                                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (AccumulatedEnergy +AD4APQ- EnergyNeeded) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, energy value reached     +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics4(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  ENERGY MODE ONLY                                                       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (AccumulatedEnergy +AD4APQ- EnergyNeeded) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, energy value reached     +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics5(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  ABSOLUTE DISTANCE MODE ONLY                                            +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (EncoderPos +AD4APQ- RunningPreset.AbsDist) +AHs-
      AccurateAbsolute +AD0- EncoderPos+ADs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics6(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  COLLAPSE DISTANCE MODE ONLY                                            +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (EncoderPos +AD4- WeldingResults.ActualTriggerDistance) +AHs-
      if ((EncoderPos - WeldingResults.ActualTriggerDistance) +AD4APQ- RunningPreset.ColDist) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, collapse value reached +ACo-/
         AccurateCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs-
      +AH0-
   +AH0-
   else +AHs-  /+ACo- Here, as per conversation with Kevin K., start a 10 ms       +ACo-/
           /+ACo- timer.  If the collapse is still negative, then create some  +ACo-/
           /+ACo- kind of an alarm.  We guess this will only happened once in  +ACo-/
           /+ACo- the life of the product, long after we remember talking      +ACo-/
           /+ACo- about it.       BEKymer   08-12-96 (after Kevin returned     +ACo-/
           /+ACo- from Mid Ohio)                                               +ACo-/
      +ADs-
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics7D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  PEAK POWER MODE ONLY                                                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (PeakPower +AD4APQ- RunningPreset.PeakPwr) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics7(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  PEAK POWER MODE ONLY                                                   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (PeakPower +AD4APQ- RunningPreset.PeakPwr) +AHs-
      SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, distance value reached    +ACo-/
   +AH0-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics9D(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  GROUND DETECT MODE ONLY                                                +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimitsD(FALSE)+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (Inp.GndDet +AD0APQ- TRUE) +AHs-
      if (GroundDetectFlag +AD0APQ- FALSE) +AHs-
         GroundDetectFlag +AD0- TRUE+ADs-
         if ((RunningPreset.ScrubTime     +ACEAPQ- 0) +ACYAJg-
              (RunningPreset.ScrubTimeFlag +AD0APQ- 0))  //Scrub Time(s) isn't Off
         +AHs-
            ScrubTimer +AD0- StartTimer(RunningPreset.ScrubTime,
                                    +ACY-ScrubTimerFlag, 60)+ADs-
            SetCurrentAmp(RunningPreset.AmpScrubTime)+ADs-
            MsDataPtr-+AD4-ScrubStartAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
         +AH0-
      +AH0-   
      else if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-
   else if (GroundDetectFlag +AD0APQ- TRUE) +AHs- /+ACo- Had Grd Detect, but lost it, check anyway +ACo-/
      if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-   
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void CheckSonics9(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the weld during the second    +ACo-/
/+ACo-  weld pressure.  When this state is reached either of two things        +ACo-/
/+ACo-  happened: Thing1-the first amplitude step has timed out, or Thing2-    +ACo-/
/+ACo-  the total sonics time has expired.  We know the difference by checking +ACo-/
/+ACo-  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then +ACo-/
/+ACo-  Thing1 happened.  If it is FALSE then Thing2 happened.                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  GROUND DETECT MODE ONLY                                                +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(Update5ms +AD4APQ- 3)+AHs-
      CheckFrequencyLimits()+ADs-
      DisplayWeldPower(CurrentPowerIn)+ADs-
      CheckCycleAborts()+ADs-
   +AH0-
   if (CurrentPowerIn +AD4- (UINT32)PeakPower) +AHs-
      PeakPower +AD0- CurrentPowerIn+ADs-
      MsDataPtr-+AD4-PeakPowerAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   +AH0-
   CheckControlLimits()+ADs-
   CheckForForceStepping()+ADs-     /+ACo-----  Deal with Force stepping Here  ----+ACo-/
   if (Inp.GndDet +AD0APQ- TRUE) +AHs-
      if (GroundDetectFlag +AD0APQ- FALSE) +AHs-
         GroundDetectFlag +AD0- TRUE+ADs-
         if ((RunningPreset.ScrubTime     +ACEAPQ- 0) +ACYAJg-
             (RunningPreset.ScrubTimeFlag +AD0APQ- 0))  //Scrub Time(s) isn't Off
         +AHs-
            ScrubTimer +AD0- StartTimer(RunningPreset.ScrubTime,
                                    +ACY-ScrubTimerFlag, 60)+ADs-
            SetCurrentAmp(RunningPreset.AmpScrubTime)+ADs-
            MsDataPtr-+AD4-ScrubStartAtTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
         +AH0-
      +AH0-
      else if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-
   else if (GroundDetectFlag +AD0APQ- TRUE) +AHs- /+ACo- Had Grd Detect, but lost it, check anyway +ACo-/
      if (ScrubTimerFlag +AD0APQ- FALSE) +AHs-
         SonicsAbort +AD0- TRUE+ADs-         /+ACo- Stop sonics, ground detect is active+ACo-/
      +AH0-
   +AH0-   
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
+AH0-



void StopSonic1(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with whatever needs dealing with   +ACo-/
/+ACo-  after the first amplitude step.                                        +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
+AH0-



void StopSonic2(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This replaces the original StopSonic2 function which has been renamed  +ACo-/
/+ACo-  to StopAllSonic().  This function will determine if energy braking     +ACo-/
/+ACo-  is on.  If braking is not on then StopAllSonic() is called and         +ACo-/
/+ACo-  everything is as it was.  If energy braking is on then this function   +ACo-/
/+ACo-  exits and does nothing.  The energy braking state (which is then next) +ACo-/
/+ACo-  will call StopAllSonic() after the proper amp ramp has outputted.      +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if (RunningPreset.EnergyBraking +AD0APQ- FALSE)  /+ACo- Not on, proceed as before +ACo-/
      StopAllSonic()+ADs-
+AH0-



void StopAllSonic(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with turning off the sonics after  +ACo-/
/+ACo-  the second weld pressure. In timemode only.                            +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Total collapse will be updated here in case there is no hold time.  If +ACo-/
/+ACo-  hold time is on, total collapse will be rewritten.                     +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   UINT16  FirstTimeValue, EBTimeValue+ADs-

   PSIdle()+ADs-                                /+ACo- Stop sonics                 +ACo-/
   ClearSAS()+ADs-                              /+ACo- Output Sonics Active signal +ACo-/
 
   if (AccurateAbsolute +AD0APQ- 0) +AHs-
      WeldingResults.ActualWeldAbs +AD0- EncoderPos+ADs-
      WeldingResults.ActualTotalAbs +AD0- EncoderPos+ADs-
   +AH0-
   else +AHs-
      WeldingResults.ActualWeldAbs +AD0- AccurateAbsolute+ADs-
      WeldingResults.ActualTotalAbs +AD0- AccurateAbsolute+ADs-
   +AH0-

   if (AccurateCollapse +AD0APQ- 0) +AHs-
      WeldingResults.ActualWeldCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs- /+ACo- Determine collapse    +ACo-/
      WeldingResults.ActualTotalCollapse +AD0- WeldingResults.ActualWeldCollapse+ADs-
   +AH0-
   else +AHs-
      WeldingResults.ActualWeldCollapse +AD0- AccurateCollapse+ADs-
      WeldingResults.ActualTotalCollapse +AD0- AccurateCollapse+ADs-
   +AH0-
   CollectEnergyFlag +AD0- FALSE+ADs-
   if(AmpStepReachedFlag +AD0APQ- FALSE)
      WeldingResults.ActualAmplitudeStart +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
   else +AHs-
      WeldingResults.ActualAmplitudeEnd +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs-
      MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-AMPSTEPALARMMASK)+ADs- /+ACo- Amp step reached, so remove alarm flag +ACo-/
   +AH0-

   if(PressureStepReachedFlag +AD0APQ- TRUE)
      MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-PRESSURESTEPALARMMASK)+ADs- /+ACo- Pressure step reached, so remove alarm flag +ACo-/

   if ((WeldingResults.PSActControlFlags +ACY- BIT0) +AD0APQ- BIT0) +AHs-  /+ACo- If internal amp control only +ACo-/
      +ACo-LastA +AD0- +ACo-A+AF8-Setup+ADs-
      +ACo-LastB +AD0- +ACo-B+AF8-Setup+ADs-
   +AH0-
   else +AHs-
      +ACo-LastA +AD0- 0+ADs-
      +ACo-LastB +AD0- 0+ADs-
   +AH0-


/+ACo---------------------------------------------------------------------------+ACo-/

   WeldingResults.PeakPower +AD0- (PeakPower)+ADs-
   //SetCurrentFreqOffset(0)+ADs-     /+ACo- clear frequency offset  +ACo-/                            
   if (WTimeFlag +AD0APQ- TRUE) +AHs-
      StopTimer(SonicTimer)+ADs-
   +AH0-



/+ACo---------------------------------------------------------------------------+ACo-/
/+ACo- The following approach will be used to determine if the actual weld time +ACo-/
/+ACo- should be reported or if the requested weld time will be used instead.   +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-     If trigger has been reached, (it must have been reached or we would  +ACo-/
/+ACo-     not be here, right+ACE-), (SonicsAbort +AD0APQ- TRUE or CycleAbort +AD0APQ- TRUE)    +ACo-/
/+ACo-     then use actual time.  If (SonicsAbort +AD0APQ- FALSE and CycleAbort       +ACo-/
/+ACo-     +AD0APQ- FALSE) then use the requested time.  If energy comp is turned     +ACo-/
/+ACo-     on and time is extended use actual time.  If time is not extended    +ACo-/
/+ACo-     then use the requested time.   If PLCControl is in effect then use   +ACo-/
/+ACo-     the actual time also.                                                +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-     Note: We need to CheckEnergyComp() first because this is what will   +ACo-/
/+ACo-     create the W7 alarm which we want to check in TIMEMODE.  We get the  +ACo-/
/+ACo-     actual time before we call CheckEnergyComp() because it needs the    +ACo-/
/+ACo-     time to decide if time was actually extended.                        +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo---------------------------------------------------------------------------+ACo-/

   if (AccumulatedEnergy +AD4- 20000) +AHs-
      WeldingResults.TotalEnergy +AD0- (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt))+ADs-
   +AH0-
   else +AHs-
      WeldingResults.TotalEnergy +AD0- (AccumulatedEnergy +ACo- CurrentSetup.PSWatt) / 100000+ADs-
   +AH0-
   WeldingResults.ActualWeldTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
   CheckEnergyComp()+ADs-

   if (RunningPreset.EnergyBraking +AD0APQ- 1) EBTimeValue +AD0- RunningPreset.EBTime+ADs-
   else EBTimeValue +AD0- 0+ADs-

   switch (RunningPreset.WeldMode) +AHs-
      case TIMEMODE:               /+ACo- TIME mode only           +ACo-/
         FirstTimeValue +AD0- ((RunningPreset.WeldTime)  ((RunningPreset.WeldTime ) +AD4APg- 1))+ADs- /+ACo- Energy Comp ON, time extended +ACo-/
         if (FirstTimeValue +AD4APQ- MAXWELDTIME) +AHs-
            FirstTimeValue +AD0- MAXWELDTIME+ADs-
         +AH0-

         if ( (SonicsAbort +AD0APQ- TRUE) +AHwAfA- (CycleAbort +AD0APQ- TRUE) +AHwAfA-
              (CurrentSetup.PLCControlFlag +AD0APQ- TRUE) ) +AHs-
            WeldingResults.ActualWeldTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
            if ((WeldingResults.ActualWeldTime - 1) +AD0APQ- RunningPreset.WeldTime) +AHs-
               WeldingResults.ActualWeldTime +AD0- RunningPreset.WeldTime+ADs-
            +AH0-
            if ((WeldingResults.ActualWeldTime  1) +AD4APQ- FirstTimeValue) +AHs-
               WeldingResults.ActualWeldTime +AD0- FirstTimeValue+ADs-
            +AH0-
         +AH0-
         else if ( (RunningPreset.ControlLimitsFlag +AD0APQ- FALSE) +AHwAfA-
                   (RunningPreset.EnergyCompFlag +AD0APQ- FALSE) ) +AHs-
            WeldingResults.ActualWeldTime +AD0- RunningPreset.WeldTime  EBTimeValue+ADs-
         +AH0-
         else if ((WeldingResults.Warnings +ACY- W7) +AD0APQ- (W7 +ACY- ALARMCODEMASK)) +AHs-
            WeldingResults.ActualWeldTime +AD0- GetUpTimer(SONICSTIMER)+ADs-
            if ((WeldingResults.ActualWeldTime - 1) +AD4APQ- FirstTimeValue) +AHs-
               WeldingResults.ActualWeldTime +AD0- FirstTimeValue  EBTimeValue+ADs-
            +AH0-
            if ((WeldingResults.ActualWeldTime  1) +AD4APQ- FirstTimeValue) +AHs-
               WeldingResults.ActualWeldTime +AD0- FirstTimeValue  EBTimeValue+ADs-
            +AH0-
         +AH0-
         else +AHs-
            WeldingResults.ActualWeldTime +AD0- RunningPreset.WeldTime  EBTimeValue+ADs-
         +AH0-
         break+ADs-

      default:                     /+ACo- All other modes but TIME +ACo-/
         if ((WeldingResults.CycleModifiedAlarms +ACY- CM3) +AD0APQ- (CM3 +ACY- ALARMCODEMASK)) +AHs-
            WeldingResults.ActualWeldTime +AD0- RunningPreset.MaxTimeout  EBTimeValue+ADs-
         +AH0-
         else +AHs-
            WeldingResults.ActualWeldTime +AD0- GetUpTimer(SONICSTIMER)  EBTimeValue+ADs-
         +AH0-
         break+ADs-

   +AH0-

   DisplayWeldPower(PeakPower)+ADs-

   WeldingResults.ActualFreqEnd +AD0- CurrentFreqIn+ADs-     /+ACo- Get final frequency   +ACo-/
   CheckFrequencyLimits()+ADs-
   WeldingResults.FrequencyChange +AD0- WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart+ADs-
   WeldingResults.WeldForceEnd +AD0- (UINT16) CurrentForce+ADs-


/+ACo---  Now make sure there the final max force is greater than trigger  --+ACo-/

   if ( (CurrentSetup.Actuator +AD0APQ- AED) +AHwAfA-
        (CurrentSetup.Actuator +AD0APQ- AES) +AHwAfA-
		(CurrentSetup.Actuator +AD0APQ- MICROC) +AHwAfA-
        (CurrentSetup.Actuator +AD0APQ- MICRO) ) 
   +AHs-

      if (CurrentForce +ADw- RunningPreset.TriggerForce) 
      +AHs-
         WeldingResults.WeldForceEnd +AD0- (UINT16) CurrentForce+ADs-
       	//Trigger by force only
       	if(RunningPreset.WeldTrigger +AD0APQ- TRIGGERBY+AF8-FORCE)
      		RecordAlarm(CM22)+ADs-
      +AH0-   
   +AH0-

/+ACo--- The next line is a quick fix for Kevin  12-15-98  --+ACo-/

/+ACo-   WeldingResults.WeldForceEnd +AD0- WeldingResults.WeldForceEnd+ADs-  +ACo-/

/+ACo--- End of quick fix  --+ACo-/

   if (CurrentSetup.ExtraCooling +AD0APQ- FALSE) +AHs-
      CoolValOff()+ADs-
   +AH0-
+AH0-



void AlStopSonics(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with turning off the sonics after  +ACo-/
/+ACo-  an alarm has been generated.                                           +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   PSIdle()+ADs-                                /+ACo- Stop sonics                 +ACo-/
   ClearSAS()+ADs-                              /+ACo- Output Sonics Active signal +ACo-/
   WeldingResults.ActualWeldCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs- /+ACo- Determine collapse    +ACo-/
   CollectEnergyFlag +AD0- FALSE+ADs-

   if(AmpStepReachedFlag +AD0APQ- TRUE)
      MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-AMPSTEPALARMMASK)+ADs- /+ACo- Amp step reached, so remove alarm flag +ACo-/
   if(PressureStepReachedFlag +AD0APQ- TRUE)
      MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-PRESSURESTEPALARMMASK)+ADs- /+ACo- Pressure step reached, so remove alarm flag +ACo-/

   if ((WeldingResults.PSActControlFlags +ACY- BIT0) +AD0APQ- BIT0) +AHs-  /+ACo- If internal amp control only +ACo-/
      +ACo-LastA +AD0- +ACo-A+AF8-Setup+ADs-
      +ACo-LastB +AD0- +ACo-B+AF8-Setup+ADs-
   +AH0-
   else +AHs-
      +ACo-LastA +AD0- 0+ADs-
      +ACo-LastB +AD0- 0+ADs-
   +AH0-

   if (WTimeFlag +AD0APQ- TRUE) +AHs-
      StopTimer(SonicTimer)+ADs-
   +AH0-
   WeldingResults.ActualWeldTime +AD0- (GetUpTimer(SONICSTIMER) - 1)+ADs-
   if(RunningPreset.Amp2Flag +AD0APQ- (UINT16)+AH4-BIT2)+AHs-
      WeldingResults.ActualWeldTime+ADs-
   +AH0-

   WeldingResults.PeakPower +AD0- (PeakPower)+ADs-
   if (AccumulatedEnergy +AD4- 20000) +AHs-
      WeldingResults.TotalEnergy +AD0- (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt))+ADs-
   +AH0-
   else +AHs-
      WeldingResults.TotalEnergy +AD0- (AccumulatedEnergy +ACo- CurrentSetup.PSWatt) / 100000+ADs-
   +AH0-
   DisplayWeldPower(PeakPower)+ADs-

   WeldingResults.ActualFreqEnd +AD0- CurrentFreqIn+ADs-     /+ACo- Get final frequency   +ACo-/
   CheckFrequencyLimits()+ADs-
   WeldingResults.FrequencyChange +AD0- WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart+ADs-
   CheckEnergyComp()+ADs-
   TriggerLostFlag +AD0- FALSE+ADs-

   if(Inp.OL +AD0APQ- TRUE) +AHs-  /+ACo- do not abort overloads +ACo-/
      PSReset()+ADs-
   +AH0-
      
/+ACo--- The next line is a quick fix for Kevin  12-15-98  --+ACo-/

   WeldingResults.WeldForceEnd +AD0- (UINT16) CurrentForce+ADs-
/+ACo-   WeldingResults.WeldForceEnd +AD0- WeldingResults.WeldForceEnd+ADs-   +ACo-/

/+ACo--- End of quick fix  --+ACo-/

+AH0-



void AlStopTest(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This is the function that will deal with turning off the sonics in      +ACo-/
/+ACo-  test mode after an overload alarm has been generated.                   +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   PSIdle()+ADs-                                 /+ACo- Stop sonics                 +ACo-/
   StartTestFlag +AD0- FALSE+ADs-
   DisplayTestPower(PeakPower)+ADs-
   if (TestKeyRepeat +AD0APQ- TRUE)
      TestModeAllowed +AD0- FALSE+ADs-               /+ACo- Disallow more test mode     +ACo-/
+AH0-                                            /+ACo- repeat vs pressing again    +ACo-/



void StartBrake(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the start of energy braking.  +ACo-/
/+ACo-  It will clear the timer and set the amplitude to the first value of    +ACo-/
/+ACo-  calculated ramp using the specified end value in the BUC menu variable +ACo-/
/+ACo-  the actual measured ramp time when sonics were turned on.              +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Exit:   AmpRamp +AD0- 10 times ms step value in percent                    +ACo-/
/+ACo-          NextRampValue +AD0- Amp value just output                          +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  Future Options:                                                        +ACo-/
/+ACo-      To have 3 different ramps choices use:                             +ACo-/
/+ACo-               AmpRampTime10 - for fastest ramp                          +ACo-/
/+ACo-               AmpRampTime25 - for medium ramp (or 2 +ACo- AmpRampTime10)    +ACo-/
/+ACo-               AmpRampTime50 - for slowest ramp (or 4 +ACo- AmpRampTime10)   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   SINT32   AmpDrop+ADs-

   EnergyBrakeTimer +AD0- 0+ADs-
   EnergyBrakeFlag +AD0- FALSE+ADs-
   EBOverloadTimer +AD0- 0+ADs-
   AmpDrop +AD0- (CurrentAmpIn  5)+ADs-/+ACo- Already multiplied by 10 for more accuracy +ACo-/
   AmpRamp +AD0- AmpDrop / RunningPreset.EBTime+ADs-  /+ACo- 10 times ramp step value      +ACo-/
   NextRampValue +AD0- (CurrentAmpIn - AmpRamp)+ADs-
   SetCurrentAmp(NextRampValue/POWERDIV)+ADs-
+AH0-



void CheckBrake(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with handling the timing for the   +ACo-/
/+ACo-  energy braking.  When the time set in the BUC menu variable is         +ACo-/
/+ACo-  reached this state will end.  Also, if the requested amplitude is      +ACo-/
/+ACo-  reached before the time expires the state will end early.  Each pass   +ACo-/
/+ACo-  the amp value will be decreased by AmpRamp percent.  The exit code     +ACo-/
/+ACo-  will call StopAllSonic() which will finally turn off the sonics.       +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   UINT32   TempAmpIn+ADs-
   
   if (++EnergyBrakeTime- +AD4APQ- BUCMenuRAM.EnergyBrakingTime) +AHs-
      EnergyBrakeFlag +AD0- TRUE+ADs-
   +AH0-
   TempAmpIn +AD0- ((CurrentAmpIn  5) / POWERDIV)+ADs- /+ACo- Drop tenths and round to whole percent +ACo-/
   if (TempAmpIn +ADwAPQ- (UINT32)BUCMenuRAM.EnergyBrakingAmp) +AHs-
      EnergyBrakeFlag +AD0- TRUE+ADs-
   +AH0-
   if (NextRampValue +AD4- AmpRamp) NextRampValue +AD0- (NextRampValue - AmpRamp)+ADs-
   if (NextRampValue +ADw- 50) NextRampValue +AD0- 50+ADs-  /+ACo- Request no less than 5+ACU- +ACo-/
   SetCurrentAmp(NextRampValue/POWERDIV)+ADs-
   EBOverloadTimer+ADs-
   if (Inp.OL +AD0APQ- TRUE) +AHs-            /+ACo- If overload detected save Power +ACY- Freq. +ACo-/
      EBOverloadPower +AD0- CurrentPowerIn+ADs-
      EBOverloadFreq +AD0- CurrentFreqIn+ADs-
   +AH0-
+AH0-



void StartHold(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the hold time.                +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
	cpld-+AD4-SetDout(OL+AF8-RESET+AF8-SIG, true)+ADs-

   HoldTimer +AD0- StartTimer(RunningPreset.HoldTime, +ACY-HTimeFlag, 8)+ADs-
   if (HoldTimer +AD0APQ- FAILED1) +AHs-
      HoldTimer +AD0- 0+ADs-
   +AH0-
   else if (HoldTimer +AD0APQ- FAILED2) +AHs-
      HoldTimer +AD0- 0+ADs-
   +AH0-
   ActualHoldTime +AD0- 0+ADs-
   if (CycleAbort +AD0APQ- FALSE) +AHs-
      MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-HOLDALARMMASK)+ADs- /+ACo- Hold started, so remove alarm flag +ACo-/
   +AH0-
+AH0-



void StartAHold(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the ALTERNATE hold state.     +ACo-/
/+ACo-  This state is required when the normal hold state is not used.  This   +ACo-/
/+ACo-  allows checking of overloads when the overload occurs within the last  +ACo-/
/+ACo-  few ms of the weld.                                                    +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
	cpld-+AD4-SetDout(OL+AF8-RESET+AF8-SIG, true)+ADs-
   HoldTimer +AD0- StartTimer(ALTERNATEHOLDTIME, +ACY-HTimeFlag, 8)+ADs-
   if (HoldTimer +AD0APQ- FAILED1) +AHs-
      HoldTimer +AD0- 0+ADs-
   +AH0-
   else if (HoldTimer +AD0APQ- FAILED2) +AHs-
      HoldTimer +AD0- 0+ADs-
   +AH0-
   ActualHoldTime +AD0- 0+ADs-

   if(CurrentSetup.HornClamp +AD0APQ- FALSE)
	   SVOff()+ADs-
 /+ACo-  SVOff()+ADs-//removed due to horm clamp functionality. It get called when hold time is off from menu
---  Because there will be no Stop Hold state, get final numbers here ---+ACo-/

   WeldingResults.ActualTotalAbs +AD0- EncoderPos+ADs-
   MsDataPtr-+AD4-HoldEndAtTime +AD0- WeldingResults.ActualWeldTime+ADs-
   
   SetCurrentFreqOffset(0)+ADs-                                 
+AH0-



void CheckHold(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking the hold to see if   +ACo-/
/+ACo-  trigger has been lost.                                                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   TriggerLostFlag +AD0- CheckForTriggerLost()+ADs-
   CheckCycleAborts()+ADs-
   ActualHoldTime+ADs-
+AH0-


void StopAHold(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with an overload occuring in the   +ACo-/
/+ACo-  fake hold state. It is needed inorder to get the DUPS info.            +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-   
	 SetPressureValue +AD0- RunningPreset.WeldPressure+ADs-
	 //Update Hold Force in results with Force sample at end of hold
	 WeldingResults.HoldForceEnd +AD0- (UINT16) CurrentForce+ADs-
	 //For Trigger By distance the PB release is made active here. We Don't need any check here as for Trigger By
	 //force the signal is already made active in trigger state.
	 PBReleaseOn()+ADs-
+AH0-


 
void StopHold(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the end of the hold time.     +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   WeldingResults.ActualTotalAbs +AD0- EncoderPos+ADs-
   WeldingResults.ActualTotalCollapse +AD0- EncoderPos - WeldingResults.ActualTriggerDistance+ADs- /+ACo- Determine collapse    +ACo-/

   //Update Hold Force in results with Force sample at end of hold
   WeldingResults.HoldForceEnd +AD0- (UINT16) CurrentForce+ADs-

/+ACo- when no trigger lost or cycle abort alarms use the requested hold time +ACo-/
   if ((WeldingResults.CycleModifiedAlarms +ACY- (CM1+AHw-CM15)) +AD0APQ- FALSE) +AHs-
      ActualHoldTime +AD0- RunningPreset.HoldTime+ADs-
   +AH0-
   MsDataPtr-+AD4-HoldEndAtTime +AD0- WeldingResults.ActualWeldTime  ActualHoldTime+ADs-
   if ((HoldTimer +ACEAPQ- 0) +ACYAJg- (HTimeFlag +AD0APQ- TRUE)) +AHs-
      StopTimer(HoldTimer)+ADs-
   +AH0-
   SetCurrentFreqOffset(0)+ADs-
   SetPressureValue +AD0- RunningPreset.WeldPressure+ADs-
   //For Trigger By distance the PB release is made active here. We Don't need any check here as for Trigger By
   //force the signal is already made active in trigger state.
   PBReleaseOn()+ADs-
+AH0-

void StartChkLimit(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with start of check limit		   +ACo-/
/+ACo-  Sets the ClampOnAlarm flag value to true initially					   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if(+ACE-DownspeedTuneFlag)//Disable Horn Clamp in DownSpeed tune cycle
      ClampOnAlarm +AD0- TRUE+ADs-
+AH0-

void ExitChkLimit(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is normal exit code of check limit state and brings the  horn up  +ACo-/
/+ACo-	on no limit alarm													   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
	 SVOff()+ADs-/+ACo- Turn off SV to bring hown up    +ACo-/
+AH0-

/+ACo------------------------------------------------------------------------+ACo-/
/+ACo-----------  Below here is the code to deal with After Burst  ----------+ACo-/
/+ACo------------------------------------------------------------------------+ACo-/


void StartABDly(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the start of the delay        +ACo-/
/+ACo-  between hold and after burst.                                          +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   SINT16 TimerReturn+ADs-

   TimerReturn +AD0- StartTimer((UINT16)RunningPreset.AbDelay, +ACY-ABTimeFlag, (UINT16)40)+ADs-
   if (TimerReturn +AD0APQ- FAILED1) +AHs-
//      LogError(TIMERFAILED1)+ADs-
   +AH0-
   else if (TimerReturn +AD0APQ- FAILED2) +AHs-
//      LogError(TIMERFAILED2)+ADs-
   +AH0-
   ActualABDelay +AD0- 0+ADs-
   ABTimeDelayFlag +AD0- TRUE+ADs-
+AH0-



void TestABDly(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with checking for hornreturn time  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACo-  This function will wait for the DUPS data collection if and overload   +ACo-/
/+ACo-  occured prior to this state.                                           +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
//   TestActClr()+ADs-
   if (Inp.uls +AD0APQ- FALSE)+AHs-
      HornReturnCount+ADs-
      if(HornReturnCount +AD4- UPPERLIMIT+AF8-TIMEOUT)
         HornReturnFlag +AD0- FALSE+ADs-
   +AH0-
   ActualABDelay+ADs-
   if (IsDUPSDataCollectionComplete() +AD0APQ- TRUE) +AHs-
      DUPSOkFlag +AD0- TRUE+ADs-
   +AH0-
   else +AHs-
      DUPSOkFlag +AD0- FALSE+ADs-
   +AH0-
   if ( (DUPSOkFlag +AD0APQ- TRUE) +ACYAJg- (ABTimeFlag +AD0APQ- FALSE) ) +AHs-
      ABTimeDelayFlag +AD0- FALSE+ADs-
   +AH0-
   else ABTimeDelayFlag +AD0- TRUE+ADs-
+AH0-



void StopABDly(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the end of the delay between  +ACo-/
/+ACo-  hold and after burst.                                                  +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   ActualABDelay+ADs-
+AH0-



void ALStopABD(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with an abnormal end to the delay  +ACo-/
/+ACo-  between hold and after burst.                                          +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
+AH0-



void StartABTme(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the start of the after burst. +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   SINT16 TimerReturn+ADs-


   TimerReturn +AD0- StartTimer((UINT16)RunningPreset.AbTime - ABRAMPDOWNTIME,
                                +ACY-ABTimeFlag, (UINT16)41)+ADs-
   SetCurrentAmp(RunningPreset.AbAmp)+ADs-      /+ACo- Initial amplitude           +ACo-/

   if(CycleAbort +AD0APQ- FALSE) +AHs-      /+ACo- do not want to turn on sonics for 1ms +ACo-/
      PSRun()+ADs-                    /+ACo- Start sonics             +ACo-/
   +AH0-
   ActualAfterburstTime +AD0- 0+ADs-
+AH0-



void TestABTme(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This is the function that will deal with checking for horn return time, +ACo-/
/+ACo-  while doing the afterburst.                                             +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
//   TestActClr()+ADs-
   if (Inp.uls +AD0APQ- FALSE)+AHs-
      HornReturnCount+ADs-
      if(HornReturnCount +AD4- UPPERLIMIT+AF8-TIMEOUT)
         HornReturnFlag +AD0- FALSE+ADs-
   +AH0-
   ActualAfterburstTime+ADs-
   if (CurrentPowerIn +AD4- ABOverloadPower) +AHs-
      ABOverloadPower +AD0- CurrentPowerIn+ADs-
   +AH0-
+AH0-



void StopABTme(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the end of the after burst.   +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   RampStartValue +AD0- RunningPreset.AbAmp+ADs-      /+ACo- Ramp start value           +ACo-/
   RampStopValue +AD0- 5+ADs-                         /+ACo- Go until 5 +ACU-               +ACo-/
   RampTime +AD0- ABRAMPDOWNTIME+ADs-                 /+ACo- How long to ramp down      +ACo-/
   RampUpDirection +AD0- FALSE+ADs-                   /+ACo- Say +ACI-ramp down+ACI-            +ACo-/
   RampRunningTime +AD0- 0+ADs-                       /+ACo- Initial ramp counter       +ACo-/
   RampDiff +AD0- RampStartValue - RampStopValue+ADs- /+ACo- Change in value            +ACo-/
   RampEndFlag +AD0- FALSE+ADs-
   if (Inp.OL +AD0APQ- TRUE) +AHs-
      if (CurrentSetup.ExtraCooling +AD0APQ- FALSE) +AHs-
         CoolValOff()+ADs- //  Solves 1968+ADs- It was PSIdle
      +AH0-
      PSReset()+ADs-
   +AH0-
   else +AHs-
      ActualAfterburstTime +AD0- ABRAMPDOWNTIME+ADs- /+ACo- Offset by ramp down time   +ACo-/
   +AH0-                                          /+ACo- unless an O/L occurred     +ACo-/
+AH0-



void RampOff(void)
+AHs-
   SINT32 RampValue+ADs-

   if (Inp.uls +AD0APQ- FALSE)+AHs-
      HornReturnCount+ADs-
      if(HornReturnCount +AD4- UPPERLIMIT+AF8-TIMEOUT)
         HornReturnFlag +AD0- FALSE+ADs-
   +AH0-
   RampRunningTime +AD0- 1000+ADs-

/+ACo-----   Stop if we timed out, before reaching the actual end of ramp   ----+ACo-/

   if ((RampRunningTime / 1000) +AD4APQ- RampTime) +AHs-
      PSIdle()+ADs-     // Stop sonics
      RampEndFlag +AD0- TRUE+ADs-
   +AH0-
   else switch (RampUpDirection) +AHs-
      case FALSE:                             /+ACo- Ramp Down                  +ACo-/
         RampValue +AD0- (((RampRunningTime / RampTime) +ACo- RampDiff)  50) / 1000+ADs-
         RampValue +AD0- (RampStartValue - RampValue)+ADs-
         SetCurrentAmp(RampValue)+ADs-
         if (RampValue +ADwAPQ- RampStopValue) +AHs-
            PSIdle()+ADs-                         /+ACo- Stop sonics                +ACo-/
            RampEndFlag +AD0- TRUE+ADs-
         +AH0-
         break+ADs-

      case TRUE:                              /+ACo- Ramp Up                    +ACo-/
         RampValue +AD0- (((RampRunningTime / RampTime) +ACo- RampDiff)  50) / 1000+ADs-
         RampValue +AD0- (RampStartValue  RampValue)+ADs-
         SetCurrentAmp(RampValue)+ADs-
         if (RampValue +AD4APQ- RampStopValue) +AHs-
            PSIdle()+ADs-                         /+ACo- Stop sonics                +ACo-/
            RampEndFlag +AD0- TRUE+ADs-
         +AH0-
         break+ADs-

      default:
         break+ADs-
   +AH0-
   if (Inp.OL +AD0APQ- TRUE) +AHs-
      PSReset()+ADs-
   +AH0-
+AH0-



void ALStopABT(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the abnormal end of after     +ACo-/
/+ACo-  burst.                                                                 +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   PSIdle()+ADs-                                /+ACo- Stop sonics                 +ACo-/
   if (Inp.OL +AD0APQ- TRUE) +AHs-
      PSReset()+ADs-
   +AH0-
+AH0-



void StartSeek(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the start of seek.            +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   SeekDelay +AD0- SEEKDELAYTIME+ADs-               /+ACo- Load up counter with delay   +ACo-/
   ActualSeekTime +AD0- 0+ADs-
   SeekEndFlag +AD0- FALSE+ADs-
+AH0-



void CheckSeek(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This is the function that will be called every pass while seeking.      +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  Notes: External cycle abort is checked here instead of calling          +ACo-/
/+ACo-         CheckControlLimits because during seek we don't want to risk     +ACo-/
/+ACo-         hitting peak power cutoff, energy compensation, or max timeout   +ACo-/
/+ACo-         while we're seeking.                                             +ACo-/
/+ACo-                                                                          +ACo-/
/+ACo-         Overload is checked here instead of the state table to prevent   +ACo-/
/+ACo-         an afterburst overload showing up also as a seek overload.       +ACo-/
/+ACo-         Doing it here allows the SEEKDELAYTIME to pass before a check is +ACo-/
/+ACo-         done, giving the power supply time to react to the reset from    +ACo-/
/+ACo-         the afterburst overload.                                         +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
//   TestActClr()+ADs-
   if (ECycleHistFlag +AD0APQ- TRUE) +AHs-          /+ACo- Check on external cycle abort +ACo-/
      RecordAlarm(CM15)+ADs-
   +AH0-
   if (Inp.uls +AD0APQ- FALSE)+AHs-
      HornReturnCount+ADs-
      if(HornReturnCount +AD4- UPPERLIMIT+AF8-TIMEOUT)
         HornReturnFlag +AD0- FALSE+ADs-
   +AH0-
   if (SeekDelay-- +ADwAPQ- 0) +AHs- 
      if (IsDUPSDataCollectionComplete() +AD0APQ- TRUE) +AHs-
         DUPSOkFlag +AD0- TRUE+ADs-
         PSSeek()+ADs-                        /+ACo- Start seek +ACo-/
         MsDataPtr-+AD4-PrintBottomFlags +ACYAPQ- (+AH4-SEEKALARMMASK)+ADs- /+ACo- Seek started, so remove alarm flag +ACo-/
         if (ActualSeekTime +AD4APQ- MAXSEEKTIME) +AHs-
            ActualSeekTime--+ADs-
            SeekEndFlag +AD0- TRUE+ADs-
         +AH0-
         if (Inp.OL +AD0APQ- TRUE) +AHs-
            RecordAlarm(OL8)+ADs-
            SeekEndFlag +AD0- TRUE+ADs-
         +AH0-
      +AH0-
      else +AHs-
         DUPSOkFlag +AD0- FALSE+ADs-
      +AH0-
   +AH0-
+AH0-



void StopSeek(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
/+ACo-                                                                         +ACo-/
/+ACo-  This is the function that will deal with the end of seek.              +ACo-/
/+ACo-                                                                         +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
+AHs-
   if (CurrentSetup.ExtraCooling +AD0APQ- FALSE) +AHs-
      CoolValOff()+ADs-                           /+ACo- Dont forget the cooling valve+ACo-/
   +AH0-
   if (Inp.OL +AD0APQ- TRUE) +AHs-                    /+ACo- do not abort overloads      +ACo-/
      RecordAlarm(OL8)+ADs-
      PSReset()+ADs-
      MsDataPtr-+AD4-SeekEndAtTime +AD0- WeldingResults.ActualWeldTime 
                                 ActualHoldTime  
                                 ActualABDelay  ActualAfterburstTime 
                                 SEEKDELAYTIME  ActualSeekTime+ADs-
   +AH0-
   else +AHs-
      PSIdle()+ADs-                             /+ACo- Stop sonics                 +ACo-/
      MsDataPtr-+AD4-SeekEndAtTime +AD0- WeldingResults.ActualWeldTime 
                                 ActualHoldTime 
                                 ActualABDelay  ActualAfterburstTime 
                                 SEEKDELAYTIME  MAXSEEKTIME+ADs-
   +AH0-

   ResetUpTimer(TRIGGERLOSTTIMER)+ADs-
+AH0-



void CheckFrequencyLimits(void) 
+AHs-
   if (CurrentFreqIn +ADwAPQ- WeldingResults.FrequencyMin) 
      WeldingResults.FrequencyMin +AD0- CurrentFreqIn+ADs-
   if (CurrentFreqIn +AD4APQ- WeldingResults.FrequencyMax)
      WeldingResults.FrequencyMax +AD0- CurrentFreqIn+ADs-
   VerifySBL()+ADs-
+AH0-



void StartDUPSDataCollection(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This function will initiate the weld data collection from the DUPS.     +ACo-/
/+ACo-  The structure which is used is based on what the current weld state is. +ACo-/
/+ACo-  A check will be done to see if there is communication with DUPS and to  +ACo-/
/+ACo-  see if CurrentPreset.WeldStatusFlag is TRUE, except for TESTMODESTATE.  +ACo-/
/+ACo-  If there is no DUPS available, then the OpStatus of each structure is   +ACo-/
/+ACo-  set to DUPS+AF8-SUCCESS.                                                    +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-

   WeldOLStatus.OpStatus +AD0- DUPS+AF8-SUCCESS+ADs-  /+ACo- If no DUPS, then assume +ACo-/
   SeekOLStatus.OpStatus +AD0- DUPS+AF8-SUCCESS+ADs-  /+ACo- everything is okay.     +ACo-/
   ABOLStatus.OpStatus +AD0- DUPS+AF8-SUCCESS+ADs-    /+ACo-                         +ACo-/

   if (DUPS+AF8-Info.DUPSFlag +AD0APQ- TRUE) +AHs-
      switch (WeldState) +AHs-

         case TESTMODESTATE:          /+ACo- Test overload +ACo-/
            WeldOLStatus.OpStatus +AD0- DUPS+AF8-PENDING+ADs-
            DUPS+AF8-GetLastWeldStatus(+ACY-WeldOLStatus)+ADs-
            OlPending +AD0- WELD+AF8-OL+ADs-
            break+ADs-

         case WAITFORPTSSTATE:        /+ACo- Pretrigger overload +ACo-/
         case WAITFORTRSSTATE1:       /+ACo- Pretrigger overload +ACo-/
         case WAITFORTRSSTATE2:       /+ACo- Pretrigger overload +ACo-/
         case WELDTIMESTATE:          /+ACo- Weld overload +ACo-/
         case POWERUPSEEKSTATE:       /+ACo- Power up seek overload +ACo-/
         default:
            if (RunningPreset.WeldStatusFlag +AD0APQ- TRUE)  +AHs-
               WeldOLStatus.OpStatus +AD0- DUPS+AF8-PENDING+ADs-
               DUPS+AF8-GetLastWeldStatus(+ACY-WeldOLStatus)+ADs-
               OlPending +AD0- WELD+AF8-OL+ADs-
            +AH0-
            break+ADs-

         case SEEKSTATE:              /+ACo- Seek overload +ACo-/
            if (RunningPreset.WeldStatusFlag +AD0APQ- TRUE)  +AHs-
               SeekOLStatus.OpStatus +AD0- DUPS+AF8-PENDING+ADs-
               DUPS+AF8-GetLastWeldStatus(+ACY-SeekOLStatus)+ADs-
               OlPending +AD0- SEEK+AF8-OL+ADs-
            +AH0-
            break+ADs-
         case AFTERBURSTTIMESTATE:    /+ACo- AB overload +ACo-/
            if (RunningPreset.WeldStatusFlag +AD0APQ- TRUE)  +AHs-
               ABOLStatus.OpStatus +AD0- DUPS+AF8-PENDING+ADs-
               DUPS+AF8-GetLastWeldStatus(+ACY-ABOLStatus)+ADs-
               OlPending +AD0- AB+AF8-OL+ADs-
            +AH0-
            break+ADs-
      +AH0-
   +AH0-
+AH0-


BOOLEAN IsDUPSDataCollectionComplete(void)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This function will check the OpStatus member of each of the DUPS+AF8-WELD   +ACo-/
/+ACo-  STATUS structures.  If none of the three are waiting for data then a    +ACo-/
/+ACo-  TRUE will be returned.  If any are waiting then a FALSE will be         +ACo-/
/+ACo-  returned.                                                               +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   BOOLEAN  RetVal +AD0- TRUE+ADs-           /+ACo- Assume for now not waiting for data +ACo-/

   if (DUPS+AF8-Info.DUPSFlag +AD0APQ- FALSE) 
      RetVal +AD0- TRUE+ADs-
   else if (WeldOLStatus.OpStatus +AD0APQ- DUPS+AF8-PENDING)+AHs-
      RetVal +AD0- FALSE+ADs-
    +AH0-
   else if (SeekOLStatus.OpStatus +AD0APQ- DUPS+AF8-PENDING)+AHs-
      RetVal +AD0- FALSE+ADs-
   +AH0-
   else if (ABOLStatus.OpStatus +AD0APQ- DUPS+AF8-PENDING)+AHs-
      RetVal +AD0- FALSE+ADs-
   +AH0-
   if(RetVal +AD0APQ- TRUE)
      +AHs-
      switch(OlPending)
         +AHs-
         case(WELD+AF8-OL):
            if(WeldOLStatus.OpStatus +AD0APQ- DUPS+AF8-SUCCESS)
               +AHs-
               UpdateOLType(WeldOLStatus.ErrorReason)+ADs-
			   OlPending +AD0- NOT+AF8-PENDING+ADs-
			   +AH0-
            break+ADs-
            
         case(AB+AF8-OL):
            if(ABOLStatus.OpStatus +AD0APQ- DUPS+AF8-SUCCESS)
               +AHs-
               UpdateOLType(ABOLStatus.ErrorReason)+ADs-
			   OlPending +AD0- NOT+AF8-PENDING+ADs-
			   +AH0-
            break+ADs-
            
         case(SEEK+AF8-OL):
            if(SeekOLStatus.OpStatus +AD0APQ- DUPS+AF8-SUCCESS)
               +AHs-
               UpdateOLType(SeekOLStatus.ErrorReason)+ADs-
			   OlPending +AD0- NOT+AF8-PENDING+ADs-
			   +AH0-
            break+ADs-
         
         default: /+ACo- not waiting for any data +ACo-/
		    OlPending +AD0- NOT+AF8-PENDING+ADs-
            break+ADs-
         +AH0-    
      +AH0-   
   return(RetVal)+ADs-
+AH0-


static void UpdateOLType(SINT32 OverloadReason)
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
/+ACo-                                                                          +ACo-/
/+ACo-  This function will receives the type of overload that occurred. Then    +ACo-/
/+ACo-  updates the SWConfiguration inorder to show the proper overload title   +ACo-/
/+ACo-  line.                                                                   +ACo-/
/+ACo-                                                                          +ACo-/
/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACo-/
+AHs-
   switch(OverloadReason)
   +AHs-
      case DUPS+AF8-CURRENTOVERLOAD:         /+ACo- Current Overload +ACo-/
         UpdateSWConfiguration(C+AF8-OL,TRUE)+ADs-
         UpdateSWConfiguration(V+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(F+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(P+AF8-OL,FALSE)+ADs-
         DUPSOverloadType +AD0- (C+AF8-OL +AD4- DUPS+AF8-OL+AF8-MENUSHIFT)+ADs-
         break+ADs-   
      
      case DUPS+AF8-VOLTAGEOVERLOAD:         /+ACo- Voltage Overload +ACo-/
         UpdateSWConfiguration(C+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(V+AF8-OL,TRUE)+ADs-
         UpdateSWConfiguration(F+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(P+AF8-OL,FALSE)+ADs-
         DUPSOverloadType +AD0- (V+AF8-OL +AD4APg- DUPS+AF8-OL+AF8-MENUSHIFT)+ADs-
         break+ADs-   
      
      case DUPS+AF8-FREQLIMITSEEKLOW:         /+ACo- Freq Overload +ACo-/
      case DUPS+AF8-FREQLIMITSEEKHIGH:
      case DUPS+AF8-FREQLIMITWELDLOW:
      case DUPS+AF8-FREQLIMITWELDHIGH:
         UpdateSWConfiguration(C+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(V+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(F+AF8-OL,TRUE)+ADs-
         UpdateSWConfiguration(P+AF8-OL,FALSE)+ADs-
         DUPSOverloadType +AD0- (F+AF8-OL +AD4- DUPS+AF8-OL+AF8-MENUSHIFT)+ADs-
         break+ADs-   
      
      case DUPS+AF8-PHASELIMIT:         /+ACo- Phase Overload +ACo-/
      default:
         UpdateSWConfiguration(C+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(V+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(F+AF8-OL,FALSE)+ADs-
         UpdateSWConfiguration(P+AF8-OL,TRUE)+ADs-
         DUPSOverloadType +AD0- (P+AF8-OL +AD4- DUPS+AF8-OL+AF8-MENUSHIFT)+ADs-
         break+ADs-   
   +AH0-
+AH0-

/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-
+ACo-   Purpose:
+ACo-  This is the entry function for WeldOffState.
+ACo-
+ACo-   Entry condition:
+ACo-  void
+ACo-   Exit condition:
+ACo-  void
+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
void WeldOffStateEntry()
+AHs-
	SetPressureValue +AD0- RunningPreset.HoldPressure+ADs-
+AH0-

/+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-
+ACo-   Purpose:
+ACo-   This is the entry function for WeldOffState in Hand Held Mode
+ACo-
+ACo-   Entry condition:
+ACo-  void
+ACo-   Exit condition:
+ACo-  void
+ACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAqACoAKgAq-/
void WeldOffHHStateEntry()
+AHs-
	SetPressureValue +AD0- RunningPreset.HoldPressure+ADs-
+AH0-
