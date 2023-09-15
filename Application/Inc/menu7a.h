/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu7a.h_v   1.8   Nov 06 2017 17:04:28   RJamloki  $ */
#ifndef MENU7A_H
#define MENU7A_H 
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      menu7a.h

   

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  
#include "portable.h"
/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

#define ZERO_MASK 0x0000

enum LANGUAGE_TYPE {
   ENGLISH            = 0x0001u,
   GERMAN             = 0x0002,
   SPANISH            = 0x0004,
   ITALIAN            = 0x0008,
   FRENCH             = 0x0010,
   CHINESESIMPLIFIED  = 0x0020,
   CHINESETRADITIONAL = 0x0040,
   JAPANESE           = 0x0080,
   KOREAN             = 0x0100,
   LANGUAGE_LAST = KOREAN,
   LANGUAGE_MAX = 9,
   LANGUAGESIZER = 65535 };

 enum BAUD_TYPE {
   BAUD_4800  = 0x0001u,
   BAUD_9600  = 0x0002,
   BAUD_19200 = 0x0004,
   BAUDSIZER = 65535 };

 enum CYCLINDER_SIZE {
   CUSTOMSIZE   = 0u,
   SIZE1_5      = 0x0001,
   SIZE2_0      = 0x0002,
   SIZE2_5      = 0x0004,
   SIZE3_0      = 0x0008,
   SIZE3_25     = 0x0010,
   SIZE4_0      = 0x0200, // NOT USED OBSOLETE

   SIZE_32      = 0x0400, // NEW
   SIZE_40      = 0x0020,
   SIZE_50      = 0x0040,
   SIZE_63      = 0x0080,
   SIZE_80      = 0x0100,
   
   CYCLINDERSIZER = 65535 };

 enum STROKE_LEN {
   CUSTOMLEN   = 0u,
   LENGTH_4    = 0x0001,
   LENGTH_5    = 0x0002,
   LENGTH_6    = 0x0004,
   LENGTH_2    = 0x0008,
   LENGTH_8    = 0x0010, // NOT USED OBSOLETE
   
   LENGTH_80   = 0x0020,
   LENGTH_100  = 0x0040,
   LENGTH_125  = 0x0080,
  // LENGTH_160  = 0x0100,
   LENGTH_50   = 0x0100,
   LENGTH_70   = 0x0200, //9 NEW
   LENGTH_75   = 0x0400, //10 NEW
   LENGTHSIZER = 65535 };

 enum WELDTIME_MULTIPLIER {
   WELDTIMEx1 = 0x0001u,
   WELDTIMEx2 = 0x0002,
   WELDTIMEx3 = 0x0004,
   WELDTIMESIZER = 65535 };

 enum TESTTIME_MULTIPLIER {
   TESTTIMEx1 = 0x0001u,
   TESTTIMEx2 = 0x0002,
   TESTTIMEx3 = 0x0004,
   TESTTIMESIZER = 65535 };

 enum WELD_DISABLE_MENU {
   USERIO_MENU,     // Stop State Machine in User IO Menu            
   CUSTOM_MENU  };  // and Custom menu.          

extern unsigned char IOState[];
extern BOOLEAN StateMachineDisabled;
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void GetBaudIndex(void);
void SetDumbTerminal(void);
void SetRemote(void);
void SetHost(void);
void GetWeldScaleIndex(void);
void GetTestScaleIndex(void);

void GetCylinderIndex(void);
void SetCylinderIndex(void);
void GetCylinderStrings(void);
void GetStrokeLenIndex(void);
void SetStrokeLenIndex(void);
void GetStrokeLenStrings(void);
void UpdateCylDefaults(void);

void RestoreUserIOState(void);
void SaveUserIOState(void);
#endif

