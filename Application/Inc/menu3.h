/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu3.h_v   1.9   30 Jan 2015 08:06:58   amaurya  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu3.h_v  $
 * 
 *    Rev 1.9   30 Jan 2015 08:06:58   amaurya
 * MAX_2DIGITNUM,MIN_3DIGITNUM,MAX_3DIGITNUM macro added.
 * 
 *    Rev 1.8   06 Jan 2015 05:24:24   AnPawar
 * GetPresetNames function argument type changed
 * 
 *    Rev 1.7   11 Dec 2014 08:32:44   AnPawar
 * return type changed to remove warning
 * 
 *    Rev 1.6   20 Oct 2014 06:39:44   AnPawar
 * removed unused extern
 * 
 *    Rev 1.5   03 Oct 2014 06:24:32   rjamloki
 *  RecallPreset() function prototype changed
 * 
 *    Rev 1.4   05 Sep 2014 04:24:58   rjamloki
 * Added define for max preset display on menu
*/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu3.h

   Function name:           


 --------------------------------- REVISIONS --------------------------------*/


#include "Preset.h"



#define MAX_PRESET_PER_SCREEN 11

#define MAX_2DIGITNUM 99
#define MIN_3DIGITNUM 100
#define MAX_3DIGITNUM 999
UINT8  ValidPresetCharacter(SINT8 Character);
void   GetPresetNames(void);
void   GetPresetNames(UINT16 PresetNum );
void   ActivatePreset(UINT32);
void   DisplayActivePreset(void);
void   AppendPresetNumber(void);
SINT32 GetParameter(UINT16 WeldModeType);
UINT8  TestParameter(UINT16 WeldType, SINT32 ParamVal);
void   SaveSameNamePreset(void);
void   AutoNamePreset(void);
UINT8  IsPresetEnabled(UINT16 PresetNumber);
void   SaveAutoNamedPreset(UINT32);
void   AssignNameFunction(void);
void   ClearPresets(UINT32);
SINT32   RecallPreset(UINT32);

BOOLEAN RecallExtPreset(UINT16 PresetCode , BOOLEAN Sequencing);
void   SetConfirmOK(UINT32);
void   SetConfirmCancel(UINT32);
void   ClearHistoryInBbram(void);
void   PresetClear(UINT16 presetNumber);
UINT16 CheckForDups(void);
extern STR * PresetNamePtrs[MAX_POSSIBLE_PRESET+1];
BOOLEAN RecallAndVerifyPreset (UINT32 PresetNum);
extern BOOLEAN ResetRecall_UpdateFlag;
