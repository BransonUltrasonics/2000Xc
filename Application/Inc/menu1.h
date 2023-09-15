/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu1.h_v   1.8   08 Apr 2015 13:52:08   AnPawar  $ */

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

   Filename: menu1.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

  --------------------------- TYPE DEFINITIONS-----------------------------
*/
typedef struct {
              UINT32 WRbit:1;
              UINT32 Cyclebit:1;
              UINT32 UserId:1;
              UINT32 UdiScan:1;
              UINT32 PresetRev:1;
              UINT32 PresetValidated:1;
              UINT32 ActAssemblyNum:1;
              UINT32 PsAssemblyNum:1;
              UINT32 StackAssemblyNum:1;
              UINT32 Timebit:1;
              UINT32 PkPwrbit:1;                     
              UINT32 Energybit:1;
              UINT32 VelocityAedbit:1;
              UINT32 VelocityAefbit:1;
              UINT32 WeldAbsbit:1;
              UINT32 Absbit:1;
              UINT32 WeldCollbit:1;
              UINT32 TtlCollbit:1;
              UINT32 AmpAbit:1;
              UINT32 AmpBbit:1;
              UINT32 SetPAbit:1;        //PStartbit
              UINT32 SetPBbit:1;        //PEndbit
              UINT32 SetFEndbit:1;      //FMaxbit
              UINT32 Pressbit:1;
              UINT32 FreqMinbit:1;
              UINT32 FreqMaxbit:1;
              UINT32 FreqStartbit:1;
              UINT32 FreqEndbit:1;
              UINT32 FreqChgbit:1;
              UINT32 CycleTimebit:1;
              UINT32 PresetNum:1;
              UINT32 HoldForceMax:1;
              } BIT_FLAGS;

extern const MENU RunScreenParamMenu[];
extern UINT8  RunScreenFlag;
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void DisplayCurrentPreset( SINT8 TextLine[] );
void FormatScrollingBuffer(UINT16 Index);
void GetCurrentWeldData(UINT32);
void ClearRunScreenFlag(void);
void UpdateParam(void);
void SoundBeeper(UINT32);
void SetOneLineDataBit(UINT16 OneLineIndex, UINT8 ActiveFlag);
void ClearWeldData(void);
