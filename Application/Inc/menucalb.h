/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menucalb.h_v   1.4   28 Nov 2014 07:56:08   rjamloki  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menucalb.h

   Function name:


 --------------------------------- REVISIONS --------------------------------



 ------------------------------- DESCRIPTION ---------------------------------
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
void UpdateCalibrationState(void);
void WaitForMenu(void);
void InitCalMenus(void);

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

extern  SINT32  ForceGaugeReadingMin;// = 0;     /* Lowest acceptable force reading    */
extern SINT32  ForceGaugeReadingMax;// = 999;   /* Highest acceptable force reading   */
extern SINT32  LoadCellReadingMin;// = 0;       /* Lowest acceptable loadcell reading */
extern SINT32  LoadCellReadingMax;
