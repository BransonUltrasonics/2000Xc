/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ALSETUP.H_v   1.4   21 May 2014 04:06:02   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,96,97              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   Alarms                                                  */
/*                                                                          */
/*   Filename:      alsetup.h                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/

/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- INCLUDE FILES -------------------------------*/  



/*------------------------- Function Prototypes ----------------------------*/  

UINT16 GetSetupAlarmCount(void);
UINT8 CheckForSetupAlarms(void);
void  ClearSetupAlarms(void);
void  CountSetupAlarms(void);
UINT16 SendAlarmBits(UINT8 * to);

extern SETUP_DATA_ALARMS SetupData;


/*-------------------------------- DEFINES ---------------------------------*/
