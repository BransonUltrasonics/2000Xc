/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weldhold.h_v   1.7   28 Jul 2014 13:04:58   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/weldhold.h_v  $
 * 
 *    Rev 1.7   28 Jul 2014 13:04:58   rjamloki
 * Added StartChkLimit and ExitChkLimit prototypes
 * 
 *    Rev 1.6   20 Jun 2014 13:31:42   rjamloki
 * Added WeldOffEntry functions prototypes.
*/



#include "dups_api.h"

#define MAXSEEKTIME          500 /* Time from Allan Roberts - 500 ms  08-08-96  */
                                 /* Back to 500ms (Kevin)  DCS #2540  05-19-98  */
#define SEEKDELAYTIME        300 /* Time before actual seek starts              */
#define DEFAULT_MAXTIMEOUT  6000 /* Max weld time - default                     */


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void    DisplayTestPower(SINT16 Power);
void    DisplayWeldPower(SINT16 Power); 
void    CheckFrequencyLimits(void);
BOOLEAN CheckForTriggerLost(void);
void    CheckForSafety(void);
void    CheckControlLimitsD(UINT16 EncoderCheck);
void    CheckControlLimits(void);
void    CheckCycleAborts(void);
void    CheckEnergyComp(void);
void    CheckForForceStepping(void);
void    EnterTrigDly(void);
void    ExitTrigDly(void);
void    StartSonic1(void);
void    CheckSonics1D(void);
void    CheckSonics1(void);
void    StartSonic1A(void);
void    CheckSonics1A(void);
void    StartSonic2(void);
void    CheckSonics2D(void);
void    CheckSonics2(void);
void    StartSonic3(void);
void    CheckSonics3D(void);
void    CheckSonics3(void);
void    CheckSonics3A(void);
void    CheckSonics3B(void);
void    CheckSonics3CD(void);
void    CheckSonics3C(void);
void    CheckSonics4D(void);
void    CheckSonics4(void);
void    CheckSonics5(void);
void    CheckSonics6(void);
void    CheckSonics7D(void);
void    CheckSonics7(void);
void    CheckSonics8D(void);
void    CheckSonics8(void);
void    CheckSonics9D(void);
void    CheckSonics9(void);
void    StopSonic1(void);
void    StopSonic2(void);
void    StopAllSonic(void);
void    AlStopSonics(void);
void    AlStopTest(void);
void    StartBrake(void);
void    CheckBrake(void);
void    AlStopSeek(void);
void    StartHold(void);
void    StartAHold(void);
void    CheckHold(void);
void    StopHold(void);
void    StopAHold(void);
void 	StartChkLimit(void);
void 	ExitChkLimit(void);
void    StartABDly(void);
void    StopABDly(void);
void    TestABDly(void);
void    ALStopABD(void);
void    StartABTme(void);
void    StopABTme(void);
void    TestABTme(void);
void    RampOff(void);
void    StartSeek(void);
void    CheckSeek(void);
void    StopSeek(void);
void    ALStopABT(void);
void    WeldOffStateEntry();
void    WeldOffHHStateEntry();
void    StartDUPSDataCollection(void);
BOOLEAN IsDUPSDataCollectionComplete(void);

extern UINT32 ActualSeekTime;
extern DUPS_WELDSTATUS WeldOLStatus;
extern DUPS_WELDSTATUS SeekOLStatus;
extern DUPS_WELDSTATUS ABOLStatus;
extern UINT32 ABOverloadPower;
extern SINT32 EBOverloadTimer;
extern SINT32 EBOverloadPower;
extern SINT32 EBOverloadFreq;
extern SINT32 ActualHoldTime;
extern SINT32 TriggerLostTime;/* Time (after 150ms) when trigger was declared lost */
extern SINT32 ActualAfterburstTime;
extern BOOLEAN AmpStepReachedFlag;
extern BOOLEAN ForceStepReachedFlag;
extern BOOLEAN HornReturnFlag;
extern BOOLEAN TriggerLostHistoryFlag, TriggerLostFlag;
extern UINT8 CollectEnergyFlag;
extern BOOLEAN SeekEndFlag;
extern BOOLEAN RampEndFlag;
extern SINT32 TriggerLostForce;/* Force when trigger was declared lost             */
extern UINT16 MaxForceDebounce;
extern UINT16 NewMaxForce;
extern UINT16 ActualABDelay;
extern UINT16 EncoderFailTimer;
extern SINT32 *A_Setup;
extern SINT32 *B_Setup;
extern SINT32 *LastA;
extern SINT32 *LastB;
extern BOOLEAN GroundDetectFlag;
extern BOOLEAN ClampOnAlarm;
