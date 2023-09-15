/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/beep.h_v   1.7   16 Apr 2015 07:31:02   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/beep.h_v  $
 * 
 *    Rev 1.7   16 Apr 2015 07:31:02   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.6   11 Feb 2015 06:40:52   amaurya
 * changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.5   26 Sep 2014 03:00:48   rjamloki
 * Removed psos references
*/
/*
------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      beep.h


            Written by: Laura Markure  
                  Date: 4/23/96  
              Language:  "C"

----------------------------- REVISIONS ------------------------------------



----------------------------- DESCRIPTION -----------------------------------

*/

/***   ***   Things needed by all files to deal with Beeper   ***   ***/

 
/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/  

/*
 ------------------------------- DEFINES ---------------------------------------
*/
#ifndef BEEP_H_
#define BEEP_H_
#include "portable.h"
enum BEEPS { ALARMBEEP, ERRORBEEP, TRIGGERBEEP, SYSTEMBEEP, CONFIRMBEEP,ESTOPBEEP, ALLBEEP };

#define ALARMBEEPTIME          5        /* ON time for alarm beep (ms)   */
#define ERRORBEEPTIME          5        /* ON time for error beep (ms)   */
#define TRIGGERBEEPTIME        7        /* ON time for trigger beep (ms) */
#define SYSTEMBEEPTIME         20       /* ON time for trigger beep (ms) */
#define ESTOPBEEPTIME          20       /* ON Time for Estop beep (ms)   */
#define BEEPOFFTIME            10       /* OFF time for all beepers (ms) */
#define CONFIRMBEEPTIME        3        /* ON time for alarm beep (ms)   */

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           



/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void CheckBeeper(void);
void TurnOffBeeper(void);
void Beep(enum BEEPS Type);
extern SINT16 NumberOfBeeps;

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif
