/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/digout.h_v   1.9   16 Apr 2015 07:32:58   rjamloki  $ */
/*
 ---------------------------- MODULE DESCRIPTION ---------------------------

   Module name:  

   Filename:      digout.h


            Written by: Laura Markure  
                  Date: 3/24/96  
              Language:  "C"

 -------------------------------- REVISIONS ---------------------------------
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/digout.h_v  $
 * 
 *    Rev 1.9   16 Apr 2015 07:32:58   rjamloki
 * Added PartClampOff declaration.
 * 
 *    Rev 1.7   10 Nov 2014 04:39:22   AnPawar
 * CPLD pointer extern here.
 * 
 *    Rev 1.6   09 Jul 2014 13:03:26   rjamloki
 * Renamed SvOutOn to PartClampOutOn
 * 
 *    Rev 1.5   05 Jun 2014 14:27:12   lmarkure
 * Added RapidTraverseOff and RapidTraverseOn functions


 ------------------------------- DESCRIPTION --------------------------------



 ------------------------------ INCLUDE FILES -------------------------------
*/  


/*
 ------------------------------- DEFINES -----------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ------------------------------
*/                           


/*  
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/
#include "CPLD.h"
void LockPowerOn(void);
void PowerDownSystem(void);
void SetGeneralAlarm(void);
void ClearAuxAlarms(void);
void ClearGeneralAlarm(void);
BOOLEAN CheckGeneralAlarmFlag(void);
void SetReady(void);
void ClearReady(void);
BOOLEAN GetReadyStatus(void);
void ClearSAS(void);
void SetSAS(void);
void PSIdle(void);
void PSReset(void);
void EStopReset(void);
void HSReset(void);
void MemoryReset(void);
void ClearFreq(void);
void PSTest(void);
void PSSeek(void);
void PSRun(void);
void SVOff(void);
void SV2Off(void);
void CoolValOff(void);
void EnableSVOn(void);
void SVOn(void);
void SV1On(void);
void RapidTraverseOn(void);
void RapidTraverseOff(void);
void CoolValOn(void);
void RejectOff(void);
void RejectOn(void);
void SuspectOff(void);
void SuspectOn(void);
void ActClrOn(void);
void ActClrOff(void);
void PBReleaseOn(void);
void PBReleaseOff(void);
void TrigSwActv(void);
void TrigSwInactv(void);
void TrsEnabled(void);
void TrsDisabled(void);

void UserCfgOutputOn (UINT16 OutputConfigured);
void UserCfgOutputOff (UINT16 OutputConfigured);
void ConfirmPresetOn(void);
void ConfirmPresetOff(void);
void PartClampOutOn(void);
void PartClampOutOff(void);
void RefreshOutputStatus(UINT16);
extern CPLD * cpld;
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


