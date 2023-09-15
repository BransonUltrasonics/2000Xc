/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/version_change.h_v   1.16   May 25 2017 18:03:08   RJamloki  $ */
#ifndef VERSION_CHANGE_H
#define VERSION_CHANGE_H
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/version_change.h_v  $
 * 
 *    Rev 1.16   May 25 2017 18:03:08   RJamloki
 * update function prototype and defines for ver1209
 * 
 *    Rev 1.15   16 Apr 2015 18:59:32   rjamloki
 * Estop current hw version incremented for two pole estop boards.
 * 
 *    Rev 1.14   16 Apr 2015 07:35:46   rjamloki
 * Added defines for both estop hard wares support based on CURRENT_ESTOP_SWVERSION
 * 
 *    Rev 1.13   16 Mar 2015 06:17:20   rjamloki
 * Fram version changed
 * 
 *    Rev 1.12   11 Mar 2015 09:24:22   amaurya
 * VER12 macro changed to 1207.
 * 
 *    Rev 1.11   30 Jan 2015 08:07:54   amaurya
 * Macro changed to 1206.
 * 
 *    Rev 1.10   21 Jan 2015 09:46:46   amaurya
 * Macro changed to 1205.
 * 
 *    Rev 1.9   08 Jan 2015 03:08:46   AnPawar
 * Macro value changed
 * 
 *    Rev 1.8   11 Dec 2014 08:33:30   AnPawar
 * VER12 define changed
 * 
 *    Rev 1.7   28 Nov 2014 07:56:46   rjamloki
 * VER12 macro changed to 1202.
 * 
 *    Rev 1.6   14 Nov 2014 05:23:58   rjamloki
 * VER12 macro changed to 1201.
 * 
 *    Rev 1.5   21 May 2014 10:49:20   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:32   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

           Module name:   
              Filename: version_change.h
            Written by: 
                  Date: 06/02/04 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------


 
 ------------------------------- DESCRIPTION -----------------------------------

  

 
 ------------------------------ INCLUDE FILES ----------------------------------
*/  
#include "statedrv.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

//#define FRAM_VER1208 1208
#define FRAM_VER1209 1209
//#define FRAM_VER1210 1210

#define VERMIN   0
#define VER12    1208
#define VERMAX   0xffff
//Below numbers are checked only if Mac chip is not configured for Estop HW configuration.(Single/Two pole)
#define ONEPOLE_ESTOP_REFVERSION 1208
#define CURRENT_ESTOP_SWVERSION  1209 //1208 and less are for single pole estop. any number
									  //bigger than this will configure the software to support two pole estop.
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
typedef struct VER_INFO{
   UINT16 VersionNum;
   void   (*VerUpdateFunc)(void);
};
   
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

//void UpdateToVer9(void);
//void UpdateToVer8_21(void);
void CheckForVersionChange (void);
void SaveColdStartValues (void);
void Convert_1208_to_1209(void);
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
