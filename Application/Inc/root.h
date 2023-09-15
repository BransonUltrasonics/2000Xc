/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/root.h_v   1.6   11 Mar 2015 09:23:56   amaurya  $ */
#ifndef ROOT_H
#define ROOT_H
#include "Task.h"
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: 

   Filename:  root.h


            Written by: Mark Lazarewicz 
                  Date: 1/6/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/
#include "portable.h"
#define FAST_CLK               5   /* Actuator A/D clk 2.41Mhz */
#define SLOW_CLK               8
#define CLOCK_PHASE            1   /* Need to invert phase because of timing error */
/* used to slow down actuator a/d clock */
#define INVERTCLK 0
#define SLOWSPEED 7 /* 1.722Mhz */
#define SLOWERSPEED 8 /* 1.51Mhz */
#define AUTHORITY_CHECK_DISABLE_SEQUENCE 3
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
                                 
typedef enum
   {
   SYS_STARTUP_PASS,
   SYS_STARTUP_FAIL
   } SYS_STARTUP_STATUS_TYPE;


/*      
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
class RootTask: public Task
{
public:
	RootTask();
	void root(void);
protected:
	void Run();
};

void StartAppTasks();
extern BOOLEAN ActuatorPresent;
void InitMemStoreInterrupt();
void InitExternalWatchDogPort();
void TriggerExternalWatchDog();
void SetupEPortForSensingPowerDown();
void InitSafetyTimer();
void DisableSafetyTimer();
BOOLEAN CheckForAuthorityCheckDisable(void);
extern BOOLEAN FramInitialized;
#endif /* ROOT_H */
