/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/timer.h_v   1.4   05 Mar 2014 13:57:38   rjamloki  $ */


/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*                                                                          */
/*                                                                          */

enum  UPTIMERS { /* This group of timer timers will be used for counting up */
   CYCLETIMER=1,        /* Cycle time starting with clearing upper limit    */
   SONICSTIMER,         /* Sonics on time from trigger                      */
   VELOCITYTIMER,       /* Timer used to calculate downstroke velocity      */
   TRIGGERLOSTTIMER,    /* Timer used to determine if trigger really lost   */
   TIMER1,              /* Extra timer                                      */
   TIMER2,              /* Extra timer                                      */
   TIMERX };            /* Last entry in timer list                         */


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

UINT16  GetCycleTime(void);
void    ValidateLinkedList(UINT16 CallerID);
void    InitTimer(void);
SINT16  StartTimer(UINT16 PassedTime, BOOLEAN *Flag, UINT16 Use);
BOOLEAN UpdateTimers(void);
void    StopTimer(UINT16 Id);
//void    LogError(enum ERRORCODES ErrorCode);

void   IncrementUpTimer(void);
void   ResetUpTimer(enum UPTIMERS TimerID);
void   StartUpTimer(enum UPTIMERS TimerID);
void   ReStartUpTimer(enum UPTIMERS TimerID);
void   StopUpTimer(enum UPTIMERS TimerID);
SINT32 GetUpTimer(enum UPTIMERS TimerID);
