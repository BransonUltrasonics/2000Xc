/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/MENU3.cpp_v   1.25   08 Apr 2015 13:44:34   AnPawar  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/MENU3.cpp_v  $
 * 
 *    Rev 1.25   08 Apr 2015 13:44:34   AnPawar
 * Changes to update ram variables for Prestrigger, Amp Step, Pressure Step.
 * 
 *    Rev 1.24   27 Mar 2015 11:08:44   amaurya
 * DoorOpen Removed
 * 
 *    Rev 1.23   28 Feb 2015 21:40:28   rjamloki
 * Preset recall from low priority task is protected
 * 
 *    Rev 1.22   11 Feb 2015 06:36:34   amaurya
 * change in function RecallAndVerifyPreset() to fix the verify status in list box
 * 
 *    Rev 1.21   30 Jan 2015 08:10:16   amaurya
 * MAX_2DIGITNUM,MIN_3DIGITNUM,MAX_3DIGITNUM macros moved to header file.
 * 
 *    Rev 1.20   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.19   06 Jan 2015 05:24:48   AnPawar
 * GetPresetNames function argument type changed
 * 
 *    Rev 1.18   02 Jan 2015 04:06:14   rjamloki
 * PresetClear() function changed for preset revesion
 * 
 *    Rev 1.17   11 Dec 2014 08:36:06   AnPawar
 * return type changed to remove warning.
 * 
 *    Rev 1.16   28 Nov 2014 07:37:32   rjamloki
 * Removed unused extern variable.
 * 
 *    Rev 1.15   20 Oct 2014 06:21:30   AnPawar
 * Level D preset changes
 * 
 *    Rev 1.14   06 Oct 2014 06:39:36   AnPawar
 * removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.13   03 Oct 2014 06:09:14   rjamloki
 *  WebService.h included and RecallPreset() function changed
 * 
 *    Rev 1.12   26 Sep 2014 03:27:02   rjamloki
 * Changes to recall 31 presets from IO
 * 
 *    Rev 1.11   11 Sep 2014 10:59:44   rjamloki
 * Added GetWeldMode2 to keep last weld mode for event record.
 * 
 *    Rev 1.10   05 Sep 2014 04:52:00   rjamloki
 * Changes for level c and 1000 presets.
 * 
 *    Rev 1.9   28 Jul 2014 12:40:46   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.8   09 Jul 2014 13:31:20   rjamloki
 * Removed redundant DataPrinting and VGAHWAvail checks.
 * 
 *    Rev 1.7   11 Jun 2014 11:54:32   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:08:46   rjamloki
 * coverity fixes
 * 
 *    Rev 1.4   05 Mar 2014 13:56:30   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:42   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:36   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu3.c

   Function name:                  

  ------------------------------- DESCRIPTION ---------------------------------

            This file will deal with presets, both loading and saving.

  --------------------------- INCLUDE FILES --------------------------------  */

#include "portable.h"
#include "menu.h"
#include "graphs.h"
#include "preset.h"
#include "keypad.h"
#include "beep.h"
#include "selctkey.h"
#include "weld_obj.h"
#include "getmsg.h"
#include "display.h"
#include "battram.h"
#include "util.h"
#include "menu3.h"
#include "statedrv.h"
#include "dups_api.h"
#include "alarms.h"
#include "ready.h"
#include "WeldManagerTask.h"
#include "digout.h"
#include "dups.h"
#include "alsetup.h"
#include "weld_msg.h"
#include "serial.h"
#include "menu1.h"
#include "RVTSHandlerTask.h"
#include "WebService.h"
/* ----------------------------- EXTERNAL DATA ------------------------------ */


extern BOOLEAN UpdateFlag; 
extern UINT16 AlarmCounter;

extern UINT8 UpdateRunningPreset;
extern UINT16 WeldDataOffset;
extern UINT16   PrinterTotalCount;
extern UINT8  LimitChanged;

extern enum WELDSTATES WeldState;
void RefreshDUPSParam ();

/* ------------------------------- LOCAL DEFINES ------------------------------- */

#define NAMELEN (PRESETLEN - 1)      
#define MAX_LEVEL_t    1      
#define MAX_LEVEL_e    5      
#define MAX_LEVEL_ea  12      
#define MAX_LEVEL_d   16
#define MAX_LEVEL_f   16
#define MAX_LEVEL_c   1000

#define MAX_PS_EXT   (31 + 1) //The maximum preset number which can be selected from external IO

#define WAIT_2SEC     2000
#define WAIT_4SEC     4000




void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr);


/* ---------------------------- LOCAL TYPE DECLARATIONS ------------------------ */

const STR  Digits[] = "0123456789ABCDEF";      /* Used by Numout */

UINT16  OldSameNameAvailable;              /* TRUE: writing to existing preset */
UINT16  NewSameNameAvailable;              /* FALSE: writing to clear preset   */
UINT8 SeqActionType;

/* ----------------------------- GLOBAL DATA --------------------------------- */
/*                      (scope is global to ALL files)                         */




SINT8 AssignNamePresetBuffer[MESSAGESIZE];
WELD_DATA_MSG   WeldHistoryMsg;

UINT16  PresetEnableFlags[MAX_POSSIBLE_PRESET + 1];    /* TRUE: Preset is valid   FALSE: Preset is not valid */
BOOLEAN IsRecalledPreset = FALSE;
BOOLEAN ResetRecall_UpdateFlag = FALSE;
BOOLEAN ConfirmPresetFlag = FALSE;

/*---------------------------- PRIVATE GLOBAL DATA ----------------------------*/
/*                        (scope is global to THIS file)                       */

static BOOLEAN ValidControlLevel(UINT16 PresetNumber);

UINT32 PresetFunction;
SINT32 InfoMonth, InfoDay, InfoYear;
SINT32 InfoHour, InfoMinute;
SINT32 InfoCount;

STR PresetBufEngName[VGA_LINESIZE];

STR NewSameName[VGA_LINESIZE];
STR OldSameName[VGA_LINESIZE];

STR *PresetBuffer[] =   { PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName };
                           
/** This structure needs to grow when more than 16 presets are used **/

STR * PresetNamePtrs[MAX_POSSIBLE_PRESET+1];
STR SequenceName1[LINESIZE];
STR SequenceName2[LINESIZE];
STR SequenceName3[LINESIZE];
STR SequenceName4[LINESIZE];
STR SequenceName5[LINESIZE];
STR SequenceName6[LINESIZE];
STR SequenceName7[LINESIZE];
STR SequenceName8[LINESIZE];
STR SequenceName9[LINESIZE];
STR SequenceName10[LINESIZE];
STR SequenceName11[LINESIZE];
STR SequenceName12[LINESIZE];
STR SequenceName13[LINESIZE];
STR SequenceName14[LINESIZE];
STR SequenceName15[LINESIZE];
STR SequenceName16[LINESIZE];
STR SequenceName17[LINESIZE];
STR SequenceName18[LINESIZE];
STR SequenceName19[LINESIZE];
STR SequenceName20[LINESIZE];
STR SequenceName21[LINESIZE];
STR SequenceName22[LINESIZE];
STR SequenceName23[LINESIZE];
STR SequenceName24[LINESIZE];
STR SequenceName25[LINESIZE];
STR SequenceName26[LINESIZE];
STR SequenceName27[LINESIZE];
STR SequenceName28[LINESIZE];
STR SequenceName29[LINESIZE];
STR SequenceName30[LINESIZE];
UINT8 SequencePresetSelected;

const STR *SequencePtrs[] = {  SequenceName1,     /* 0 index is not really used */
                               SequenceName1,
                               SequenceName2,
                               SequenceName3,
                               SequenceName4,
                               SequenceName5,
                               SequenceName6,
                               SequenceName7,
                               SequenceName8,
                               SequenceName9,
                               SequenceName10,
                               SequenceName11,
                               SequenceName12,
                               SequenceName13,
                               SequenceName14,
                               SequenceName15,
                               SequenceName16,
                               SequenceName17,
                               SequenceName18,
                               SequenceName19,
                               SequenceName20,
                               SequenceName21,
                               SequenceName22,
                               SequenceName23,
                               SequenceName24,
                               SequenceName25,
                               SequenceName26,
                               SequenceName27,
                               SequenceName28,
                               SequenceName29,
                               SequenceName30 };



UINT8 ConfirmResponse;
UINT8 ActivePreset;
/* Minimum Control Level required to recall a preset. */
UINT16 PresetControlLevel[MAX_PS_EXT] = { LEVEL_t,  /* Minimum Control Level for preset 0 */
                                             LEVEL_t,  /* Minimum Control Level for preset 1 */ 
                                             LEVEL_t,  /* Minimum Control Level for preset 2 */
                                             LEVEL_ea, /* Minimum Control Level for preset 3 */
                                             LEVEL_ea, /* Minimum Control Level for preset 4 */
                                             LEVEL_ea, /* Minimum Control Level for preset 5 */
                                             LEVEL_ea, /* Minimum Control Level for preset 6 */
                                             LEVEL_ea, /* Minimum Control Level for preset 7 */
                                             LEVEL_ea, /* Minimum Control Level for preset 8 */
                                             LEVEL_ea, /* Minimum Control Level for preset 9 */
                                             LEVEL_ea, /* Minimum Control Level for preset 10 */
                                             LEVEL_ea, /* Minimum Control Level for preset 11 */
                                             LEVEL_ea, /* Minimum Control Level for preset 12 */
                                             LEVEL_d,  /* Minimum Control Level for preset 13 */
                                             LEVEL_d,  /* Minimum Control Level for preset 14 */
                                             LEVEL_d,  /* Minimum Control Level for preset 15 */
                                             LEVEL_d,  /* Minimum Control Level for preset 16 */
                                             LEVEL_c,  /* Minimum Control Level for preset 17 */
											 LEVEL_c,  /* Minimum Control Level for preset 18 */
											 LEVEL_c,  /* Minimum Control Level for preset 19 */
											 LEVEL_c,  /* Minimum Control Level for preset 20 */
											 LEVEL_c,  /* Minimum Control Level for preset 21 */
											 LEVEL_c,  /* Minimum Control Level for preset 22 */
											 LEVEL_c,  /* Minimum Control Level for preset 23 */
											 LEVEL_c,  /* Minimum Control Level for preset 24 */
											 LEVEL_c,  /* Minimum Control Level for preset 25 */
											 LEVEL_c,  /* Minimum Control Level for preset 26 */
											 LEVEL_c,  /* Minimum Control Level for preset 27 */
											 LEVEL_c,  /* Minimum Control Level for preset 28 */
											 LEVEL_c,  /* Minimum Control Level for preset 29 */
											 LEVEL_c,  /* Minimum Control Level for preset 30 */
											 LEVEL_c  /* Minimum Control Level for preset  31 */
										};


/* --------------------------------- CODE ---------------------------------- */



UINT8 ValidPresetCharacter(SINT8 Character)
{
   UINT8 ValidChar = TRUE;     /* Assume Valid Character */

   if(((Character >= 0x1) && (Character <= 0xF)) || ((Character >= 0x10) && (Character <= 0x1F)) ||
		   (Character >= 0x7F))//non printable char range except NULL
	   ValidChar = FALSE;
   else
   {
      switch(Character)
      {
         //\ / : * ? " < > |  Invalid chars in file name
         case '\\':
         case '/':
         case ':':
         case '*':
         case '?':
         case '"':
         case '<':
         case '>':
         case '|':
        	 ValidChar = FALSE;
        	 break;
         default:
            break;
      }
   }
   return(ValidChar);
}

static BOOLEAN ValidControlLevel(UINT16 PresetNumber)
/***************************************************************************/
/*                                                                         */
/*  This function determines if a preset number is valid for the Control   */
/*  Level of the system                                                    */
/*                                                                         */
/*  Input: CurrentSetup.ControlLevel - used to determine status of Preset  */
/*         EnableFlags                                                     */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN ValidNumber = TRUE;     /* Assume Valid Number */

   switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         if(PresetNumber > MAX_LEVEL_t) 
            ValidNumber = FALSE;
         break;
      case LEVEL_e:
         if(PresetNumber > MAX_LEVEL_e) 
            ValidNumber = FALSE;
         break;
      case LEVEL_ea:
         if(PresetNumber > MAX_LEVEL_ea) 
            ValidNumber = FALSE;
         break;
      case LEVEL_d:
         if(PresetNumber > MAX_LEVEL_d) 
            ValidNumber = FALSE;
         break;
      case LEVEL_f:
         if(PresetNumber > MAX_LEVEL_f) 
            ValidNumber = FALSE;
         break;
      case LEVEL_c:
		 if(PresetNumber > MAX_LEVEL_c)
		   ValidNumber = FALSE;
		 break;
      default:
         ValidNumber = FALSE;
         break;
   }
   return(ValidNumber);
}



void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr)
/*****************************************************************************/
/*   Numout1 converts a number from binary to an ascii string suitable for   */
/*   printing or display.                                                    */
/*      Value:   The number whose ascii representation is desired            */
/*      Base:    What base to display in (2-16)                              */
/*      LC:      Leading character (usually space, zero or NULL)             */
/*      Width:   The number of character positions to convert                */
/*      StrAdr:  Address of the buffer where to put the ascii string         */
/*                                                                           */
/*   If the 'Value' is too large to be represented in 'Width' characters of  */
/*   the chosen 'Base', then only the least significant digits will be put   */
/*   into the string.   A null will be added at the end of the converted     */
/*   string.                                                                 */
/*****************************************************************************/
{
   UINT16   I;

   for (I = 1; I <= Width; I++) {
      StrAdr[Width-I] = Digits[Value % Base];
      Value /= Base;
   }
   StrAdr[Width] = NULL;
   I = 0;
   while ((StrAdr[I] == '0') && (I < (Width-1)) ) { 
      StrAdr[I] = LC;
      I++;
   }
}


void GetPresetNames(UINT16 PresetNum)
/*****************************************************************************/
/*  This function will get the name of preset number passed in PresetNum parameter*/
/*  into the string array PresetPtrs.  Invalid names will be set to NULL.    */
/*  The preset number will be added to the start of the string by the func-  */
/*  tion Numout1().  This function does not read in each preset so the       */
/*  current preset is not lost.  This function should be called whenever the */
/*  list of names needs to be updated such as saving or clearing a preset.   */
/*****************************************************************************/
{
   UINT16 x, i;
   bool ValidPreset = TRUE;
   STR               LocalPresetNames[LINESIZE];
   UINT8 Width;
   Ver1200Setups *Preset;
   x = PresetNum;
   Preset = Readpreset(PresetNum);
   //For Naming the Preset
   if (Preset->PresetID[0] != NULL)
       {
          ValidPreset = TRUE;                     /* Assume Valid Name */
          for (i = 0; i < NAMELEN && ValidPreset; i++) {
             if (Preset->PresetID[i] != 0) {
                if (!ValidPresetCharacter(Preset->PresetID[i])) {
                   if(!ValidControlLevel(x))
                   {
                      ValidPreset =  FALSE;
                      Preset->PresetID[0] = NULL; /* Invalid Name, Clear Name */
                   }
                }
             }
             else {
                ValidPreset = FALSE; /* Terminate Loop, Preset Valid */
             }
          }
       }

       //fix the width for number in name string.
       if((x > 0) && (x <= MAX_2DIGITNUM))
          Width = 2;
       else if((x >= MIN_3DIGITNUM) && (x <= MAX_3DIGITNUM))
          Width = 3;
       else
          Width = 4;

       if (Preset->PresetID[0] != NULL)       /* Preset name is okay */
       {
          PresetEnableFlags[x] = TRUE;
          Numout1(x, 10, '0', Width, LocalPresetNames);
          strcat(LocalPresetNames, " ");
          strncat(LocalPresetNames, Preset->PresetID, LINESIZE - strlen(LocalPresetNames) - 1);
       }
       else
       {
          Numout1(x, 10, '0', Width, LocalPresetNames);
          PresetEnableFlags[x] = FALSE;
       }
       LocalPresetNames[NAMELEN + 5] = NULL;        /* Make sure string is terminated */
       strcpy((char*)PresetNamePtrs[x],(char*)LocalPresetNames); // save the name information in RAM
}

void GetPresetNames(void)
/*****************************************************************************/
/*  This function will get te names of all the valid presets and put them    */
/*  into the string array PresetPtrs.  Invalid names will be set to NULL.    */
/*  The preset number will be added to the start of the string by the func-  */
/*  tion Numout1().  This function does not read in each preset so the       */
/*  current preset is not lost.  This function should be called whenever the */
/*  list of names needs to be updated such as saving or clearing a preset.   */
/*****************************************************************************/
{
   UINT16            i,x;
   UINT16            ValidPreset;
   STR               LocalPresetNames[LINESIZE];
   UINT8 Width;
   
   Ver1200Setups *PresetPtr;
   for (x =1; x <= MAX_POSSIBLE_PRESET; x++) {
      
      PresetPtr = Readpreset(x); // Read the preset and get data into RAM
      //Get Preset Names
      if (PresetPtr->PresetID[0] != NULL)
      {
         ValidPreset = TRUE;                     /* Assume Valid Name */
         for (i = 0; i < NAMELEN && ValidPreset; i++) {
            if (PresetPtr->PresetID[i] != 0) {
               if (!ValidPresetCharacter(PresetPtr->PresetID[i])) {
                  if(!ValidControlLevel(x))
                  { 
                     ValidPreset =  FALSE;
                     PresetPtr->PresetID[0] = NULL; /* Invalid Name, Clear Name */
                  }
               }
            }
            else
               ValidPreset = FALSE; /* Terminate Loop, Preset Valid */
         }                                                                 
      }

      //fix the width for number in name string.
      if((x > 0) && (x <= MAX_2DIGITNUM))
         Width = 2;
      else if((x >= MIN_3DIGITNUM) && (x <= MAX_3DIGITNUM))
         Width = 3;
      else
         Width = 4;

      if (PresetPtr->PresetID[0] != NULL)       /* Preset name is okay */
      {
         PresetEnableFlags[x] = TRUE;
         Numout1(x, 10, '0', Width, LocalPresetNames);
         strcat(LocalPresetNames, " ");
         strncat(LocalPresetNames, PresetPtr->PresetID, LINESIZE - strlen(LocalPresetNames) - 1);
      }
      else
      {
         Numout1(x, 10, '0', Width, LocalPresetNames);
         PresetEnableFlags[x] = FALSE;
      }
      LocalPresetNames[NAMELEN+5] = NULL;        /* Make sure string is terminated */
      /* +3 is for number & space       */
      strcpy((char*)PresetNamePtrs[x],(char*)LocalPresetNames); // save the name information in RAM
   }
}



void ActivatePreset(UINT32 PresetNum)
/*****************************************************************************/
/*  This function will set ActivePreset equal to the passed argument.  This  */
/*  global is used for saving a preset.  It will also fill two strings with  */
/*  preset names.  NewSameName will be filled with the name of the preset    */
/*  that was just made active.  OldSameName will be filled with the preset   */
/*  that is current.  Both of these can be displayed when saving presets.    */
/*  Besides auto naming and assigning a name, these two names can be chosen, */
/*  allowing a preset to be saved using an existing name.  If the names are  */
/*  the same only one will be displayed.                                     */
/*****************************************************************************/
{
   SINT32 NConCat;
   ActivePreset = PresetNum;
   if (PresetEnableFlags[PresetNum] == TRUE)
   {
      strcpy(NewSameName, "\"");                        /* Start with a quote                       */
      NConCat = VGA_LINESIZE - strlen(NewSameName) - 1;
      strncat(NewSameName, (char*)&PresetNamePtrs[ActivePreset][3], NConCat);/* Put into SameName in case that is picked */
      NConCat = VGA_LINESIZE - strlen(NewSameName) - 1;
      strncat(NewSameName, "\"", NConCat);               /* End with a quote                         */
      NewSameNameAvailable = TRUE;                      /* Allow name to be displayed               */
   }
   else
   {
      NewSameName[0] = NULL;                            /* Remove all signs of old string           */
      NewSameNameAvailable = FALSE;                     /* Prevent display of name                  */
   }   
   if (CurrentPreset.PresetID[0] != NULL)
   {
      strcpy(OldSameName, "\"");                        /* Start with a quote                       */
      NConCat = VGA_LINESIZE - strlen(OldSameName) - 1;
      strncat(OldSameName, CurrentPreset.PresetID, NConCat);      /* Put into SameName in case that is picked */
      NConCat = VGA_LINESIZE - strlen(OldSameName) - 1;
      strncat(OldSameName, "\"", NConCat);                        /* End with a quote                         */
      if (strcmp(NewSameName, OldSameName))             /* If both strings are different            */
         OldSameNameAvailable = TRUE;                   /* then we need both                        */
      else
         OldSameNameAvailable = FALSE;                  /* Otherwise eliminate one                  */
   }
   else OldSameNameAvailable = FALSE;                   /* Prevent display of name                  */
}




void AutoNamePreset(void)
{
   UINT16 StringSize, NumSize;
   SINT32 Value;
   SINT8 TempString[PRESETLEN];
   SINT8 *CPtr;
   enum FORMAT format;

   Value = 0;     /* Use this to tell if # needs to be displayed */

   switch (CurrentPreset.WeldMode)
   {
      case TIMEMODE:
         strcpy(CurrentPreset.PresetID, "Tm=");
         format = TIME;
         Value = CurrentPreset.WeldTime;
         break;

      case ENERGYMODE:
         strcpy(CurrentPreset.PresetID, "En=");
         Value = CurrentPreset.WeldEnergy;

         if (Value >= 10000)
            format = ENERGYDIV10;
         else
            format = ENERGY;
         break;
   
      case PKPOWERMODE:
         strcpy(CurrentPreset.PresetID, "PP=");
         format = PERCENTX10;
         Value = CurrentPreset.PeakPwr;
         break;
   
      case COLLAPSEMODE:
         strcpy(CurrentPreset.PresetID, "Cl=");
         format = DISTANCE;
         Value = CurrentPreset.ColDist;
         break;

      case ABSOLUTEMODE:
         strcpy(CurrentPreset.PresetID, "Ab=");
         format = DISTANCE;
         Value = CurrentPreset.AbsDist;
         break;

      case GRDDETECTMODE:
         strcpy(CurrentPreset.PresetID, "GD=");
         format = TIME;
         Value = CurrentPreset.ScrubTime;
         break;

      case CONTINUOUSMODE:
         strcpy(CurrentPreset.PresetID, "Continuous");
         break;

      default:
         strcpy(CurrentPreset.PresetID, "Bad Mode");
         break;
   }

   if (Value)
   {
      StringSize = strlen(CurrentPreset.PresetID);
      NumSize = PRESETLEN - StringSize - 3; /* 3 = 2 units chrs + 0 end */

      FormatVariables( Value, format, TempString, NumSize, CurrentSetup.Units );

      TempString[NumSize++] = '&';    /* Add units & terminator */
      TempString[NumSize++] = '&';
      TempString[NumSize++] = 0;
      InsertProperUnits( TempString, format );
      
      CPtr = TempString;
      while (*CPtr == ' ')
         CPtr++;

      StringSize = strlen(CurrentPreset.PresetID);
      strncat( CurrentPreset.PresetID, CPtr , PRESETLEN - StringSize - 1);//Leave 1 for null
   }
   StringSize = strlen(CurrentPreset.PresetID); /* Pad with spaces */
   CPtr = &CurrentPreset.PresetID[StringSize];
   while (StringSize++ < PRESETLEN-1)
      *CPtr++ = ' ';

   *CPtr = 0;     /* Supply final terminator */
}



void UseSameNamePreset(UINT32 Cond)
/*****************************************************************************/
/*                                                                           */
/*  Cond = NAME_NEW:     Use NewSameName (Name of preset your writing to)    */
/*  Cond = NAME_CURRENT: Use OldSameName (Name of preset current running)    */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 Length;

   switch (Cond) {
      case NAME_NEW:                   /* Use name of preset that exists where you are writing */
         Length = strlen(NewSameName);
         strncpy(CurrentPreset.PresetID, &NewSameName[1],sizeof(CurrentPreset.PresetID)-1);  /* Start at 1 to remove front quote */
         CurrentPreset.PresetID[Length-2] = NULL;          /* Remove back quote                */
         break;

      default:
      case NAME_CURRENT:               /* Use name that exists in the current preset           */
         Length = strlen(OldSameName);
         strncpy(CurrentPreset.PresetID, &OldSameName[1], PRESETLEN - 1);  /* Start at 1 to remove front quote */
         CurrentPreset.PresetID[Length-2] = NULL;          /* Remove back quote                */
         break;
   }
}



UINT8 IsPresetEnabled(UINT16 PresetNumber)
{
   UINT8 PresetFlag = FALSE;
 
   if (PresetNumber <= MAX_POSSIBLE_PRESET) {
      if (PresetEnableFlags[PresetNumber] == TRUE) {
         PresetFlag = TRUE;
      } 
   }
   return(PresetFlag);
}

SINT32 RecallPreset( UINT32 PresetNum )
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;
   ServiceErrorCode ErrorCode = SUCCESS;
   if (PresetEnableFlags[PresetNum])
   {
      if(((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)))
      {
    	  StopStateMachine();
         if (CurrentPreset.PresetUpdateComplete == TRUE)
            WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
           // Now if the user makes any changes and doesn't want to save the changes, he can do a recall preset 
           // which will discard the changes he made and will restore the original values.
         if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
         {  // if there was an associated Parameter set or if this is an analog power supply
            CurrentSetup.ActivePreset = PresetNum;        
            UpdateRunningPreset = TRUE;
            ReadPreset(CurrentSetup.ActivePreset, FALSE);
            WritePreset(CURRENT_PRESET_INDEX);                           /* Update Running Preset */
            UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
            DUPS_DownloadCurrPS();
            RefreshDUPSParam ();
            ResetRecall_UpdateFlag = TRUE;
            ResetStateMachine();
            StartStateMachine();
            SendFakeKeyPress(RunKey);
         }  // if there was an associated Parameter set or if this is an analog power supply
      } // end of -- Ok to recall preset since no weld in progress
      else  // can't recall preset right now because weld in progress
      {
    	  ErrorCode = SYSTEM_BUSY;
      } // else can't recall preset right now because weld in progress
   }
   else
   {
	   ErrorCode = PRESET_NOT_ENABLED;
       Beep(ERRORBEEP);
   }
   return ErrorCode;
}  // end of RecallPreset( UINT16 PresetNum )



BOOLEAN RecallExtPreset(UINT16 PresetCode, BOOLEAN Sequencing)
/***************************************************************************/
/*                                                                         */
/*  This function is called from the Weld Manager when a preset is         */
/*  externally selected or while definable sequence from menu is running.  */
/*  This function is for the Analog/Digital Power     					   */
/*  Supply. Return FALSE if preset not recalled.                           */
/*                                                                         */
/*  Caveat: There can be no Queue calls from this function because it is    */
/*          already called from the highest priority task.                 */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN PresetRecalled = TRUE;
   CONFIGSETUP *FRAMPtr;
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   /* check if preset is available.*/
   if (((Sequencing == FALSE) && (PresetCode < MAX_PS_EXT) && PresetEnableFlags[PresetCode] &&
       (CurrentSetup.ControlLevel >= PresetControlLevel[PresetCode])) ||
	   ((Sequencing == TRUE) && (ValidControlLevel(PresetCode) == TRUE) && PresetEnableFlags[PresetCode]))
   {
      StopStateMachine(); /*Stop the state machine.*/

      
      if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
      {
      
         CurrentSetup.ActivePreset = PresetCode;
         FRAMPtr->ActivePreset = PresetCode; /* Save in FRAM in case power lost illegally */
         Readpreset(PresetCode, &CurrentPreset);/* Read the PresetCode from Fram or flash*/
         //CopyInfoToPreset(&CurrentPreset, PresetCode);
         CurrentPreset.PresetID[PRESETLEN - 1] = 0;
         //Update ram variables related to Pre trigger Amp, Amp step and Pressure step
         SetupPretriggerFlags();
         SetupAmplitudeStepFlag();
         SetupPressureStepFlag();
         FormatRunScreenTopLine();
         /* If not ready do not update the running preset check the UpdateDispFlag
          on the next palm button pressed */
         LimitChanged = FALSE;
         SavePreset(CURRENT_PRESET_INDEX, &CurrentPreset);
         /* if ( (RunScreenFlag == FALSE) || ((RunScreenFlag == TRUE) && (MenuCounter > 1) &&
          (AdjustWeldSetupMenuFlag == TRUE)))
          SendFakeKeyPress(RunKey);
          else */
         DUPS_DownloadCurrPS();
         RefreshDUPSParam();
         SendFakeKeyPress(UPDATEDISPLAY); /* Updates preset name and # on line 2 */
         ResetRecall_UpdateFlag = TRUE;
         ConfirmPresetFlag = TRUE;
      }
      StartStateMachine(); /*Restart the state machine.*/
   }
   else  /* generate the external preset alarm */
   {
      RecordSetupAlarm(SE46); /* "Preset Not Available" alarm */    
      PresetRecalled = FALSE;
   }
   return(PresetRecalled);
}

void ClearHistoryInBbram(void)
/**---------------------------------------------**
 ** This function Clears Weld History Data from **
 ** FRAM when a Preset is recalled.            **
 **---------------------------------------------**/  
{
   UINT8 *HistFramPtr; /* points to Weld History data location in FRAM */
   UINT16 ByteCount;

   HistFramPtr = (UINT8 *) FRAM1200_HISTORY_START;

   for(ByteCount = 0; ByteCount < FRAM1200_HISTORY_SIZE; ByteCount++){
      *HistFramPtr++ = 0;
   }
   
   CurrentSetup.WeldHistoryPtr = (SINT32)(FRAM1200_HISTORY_START);

   WeldDataOffset = 0;           /*-- Reset the counter to 1 line data record --*/
   PrinterTotalCount = 0;        /*-- Reset graph data --*/
   ClearDataStorage();           /*-- Reset graph data --*/
}



void PresetClear(UINT16 presetNumber)
/*****************************************************************************/
/*  This function will clear a preset.  In reality it will simply set the    */
/*  preset name string to a NULL.  If the preset number being cleared is the */
/*  same as the one currently in use, then the name of the current preset in */
/*  zero is also set to NULL.                                                */
/*****************************************************************************/
{
   SETUPS_Ver1200 * PresetPtr;

   PresetPtr = Readpreset(presetNumber);
   PresetPtr->PresetID[0] = NULL;                          /* Make name NULL */
   PresetPtr->Validated = FALSE;
   PresetPtr->Locked = FALSE;
   PresetPtr->Rev = 0;
   SavePreset(presetNumber); //save to Slot
   if (CurrentSetup.ActivePreset == presetNumber)
   {
      CurrentSetup.ActivePreset = 0;
      strcpy(CurrentPreset.PresetID, "");                     /* Clear preset name       */
      CurrentPreset.Validated = FALSE;
      CurrentPreset.Locked = FALSE;
      CurrentPreset.Rev = 0;
      SavePreset(CURRENT_PRESET_INDEX, &CurrentPreset); /* Save Preset0            */
      CurrentPreset.PresetUpdateComplete = FALSE;
   }
}                                                



/**   Check for presence of DUPS  **/

UINT16 CheckForDups(void)
{
  return (DUPS_Info.DUPSFlag);
}


void RefreshDUPSParam ()
/*****************************************************************************/
/*                                                                           */
/* This function refresh the DUPS current parameter set from the Compress    */
/* preset values.                                                            */
/*                                                                           */
/*****************************************************************************/
{
   
   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPSTOREMEMATWLDEND) /* Check for bit4 if set flag = True*/
      DUPS_Info. DUPSMemFlag = TRUE;
   else                                /*Update status in DUPS Info*/
      DUPS_Info. DUPSMemFlag = FALSE;

   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPAUTOSEEK)/* Check for bit6 if set flag = True*/
      DUPS_Info. DUPSSeekFlag = TRUE;
   else              
      DUPS_Info. DUPSSeekFlag = FALSE;  

   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPCLEARMEMATRST) /* Check for bit3 if set flag = True*/
      DUPS_Info. DUPSMemRstFlag = TRUE;
   else                                /*Update status in DUPS Info*/
      DUPS_Info. DUPSMemRstFlag = FALSE;

}


BOOLEAN RecallAndVerifyPreset (UINT32 PresetNum)
/****************************************************************************/
/*Description:                                                              */
/*   This function Verify the selected preset from the menu structure.      */
/*   This will first recall the selcted preset if the selected preset is not*/
/*   same as the ActivePreset and then verify the preset.                   */
/*   Returns FALSE if the preset is not enabled.                            */ 
/****************************************************************************/
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;
   BOOLEAN PresetVerified = FALSE;

   if (PresetEnableFlags[PresetNum])
   {
       StopStateMachine();
       //if(PresetNum != CurrentSetup.ActivePreset)
       {
           if (CurrentPreset.PresetUpdateComplete == TRUE)
              WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
         

           if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
           {  // if there was an associated Parameter set or if this is an analog power supply
              CurrentSetup.ActivePreset = PresetNum;        
              ReadPreset(CurrentSetup.ActivePreset, TRUE);
              WritePreset(CURRENT_PRESET_INDEX);
              UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
              DUPS_DownloadCurrPS();
              RefreshDUPSParam ();
           }
           LimitChanged = FALSE;
       }
        if(DUPS_paramsetno != DUPS_PARAMSETUNDEF)
        {
            UpdateRPreset();/*Update the RunningPreset*/
            if(AlarmDetectedFlag == TRUE)
            {
               ClearSetupAlarms();
               /*Clear all the alarms before verification.*/  
               ClearGeneralAlarm();
               ClearWeldingResultsAlarms();
               ClearFinalResultsAlarms();
               ClearAlarm(FinalResults.EquipmentFailureAlarms);
               /* If all the alarms are cleared. */
               if ((FinalResults.EquipmentFailureAlarms == 0) &&
                (FinalResults.CalibrateAlarms == 0) )
               {
                  AlarmOff();     /* Turn off Reset led               */
                  AlarmDetectedFlag = FALSE;
               }
            }
            CountAlarms();
            /* Carry this count into RecordAlarm       */
            AlarmCounter = TotalAlarmCount; 
            VerifyPreset();  
            CountAlarms();
            if(TotalAlarmCount != 0)
               AlarmDetectedFlag = TRUE;
            else  AlarmOff();
            if(RunScreenFlag && MenuCounter == 1)
               SendFakeKeyPress(UPDATELINE2);              

            UpdateFlag = FALSE;
            PresetVerified = TRUE;
        }
        ResetStateMachine ();
        StartStateMachine ();
   }
   else Beep(ERRORBEEP);
   
   return(PresetVerified);
} 

void InitPresetNameBuffers()
{
   for(int i = 0; i <= MAX_POSSIBLE_PRESET; i++)
   {
	   PresetNamePtrs[i] = new STR[VGA_LINESIZE];
       memset(PresetNamePtrs[i],0x00,VGA_LINESIZE); //Set buffer to NULL
   }
}
