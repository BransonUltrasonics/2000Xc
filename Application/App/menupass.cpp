/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menupass.cpp_v   1.11   08 Jan 2015 03:18:24   AnPawar  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menupass.cpp_v  $
 * 
 *    Rev 1.11   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.10   26 Sep 2014 03:14:26   rjamloki
 * Removed psos references
 * 
 *    Rev 1.9   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.8   09 Jul 2014 13:33:30   rjamloki
 * typo fix for MAINTENANCE
 * 
 *    Rev 1.7   21 May 2014 10:48:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 03:33:42   rjamloki
 * coverity fixes
 * 
 *    Rev 1.5   06 Mar 2014 11:03:56   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:34   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.3   10 Feb 2014 04:59:46   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menupass.c

   Function name:

  ------------------------------- DESCRIPTION ---------------------------------
 
    This file will deal with the menus for all password interaction.


  ------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include "ticks.h"                    /* Defines system tick values           */
#include "menu.h"
#include "param.h"
#include "preset.h"
#include "display.h"
#include "getmsg.h"
#include "selctkey.h"
#include "ascii.h"
#include "command.h"
#include "string.h"
/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern struct Codes SecretCode[];


extern enum LEVEL AccessLevel;
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
#define MAX_PASSWORD_CHAR       6

UINT16 WorkingPasswordFlag;   /* So real flag in CurrentSetup not changed */
                              /* until valid password is entered. */



/*
 ---------------------------- EXTERNAL FUNCTIONS -----------------------------
*/
//void UpdateDUPSRAMParamSet(void);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/
void VGAPasswordEntry(void)
/****************************************************************************/
/* Description:                                                             */
/*   Provides NACK to SBC when password becomes ON.                         */
/****************************************************************************/
{
      if(WorkingPasswordFlag == TRUE)
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_ENTRY1;
         ErrorResponseMaxLimit = 0;
      }
      else
      {
         CurrentSetup.PassWordFlag = 0;      /* User disabled passwords */
      }
} 

UINT16 PasswordSave(UINT8 ** to)
/****************************************************************************/
/* Description:                                                             */
/*   Saves password in current preset                                       */
/****************************************************************************/
{
   SINT8 PasswordBuffer[MESSAGESIZE];   /* Longer than it needs to be */
   SINT32 MisMatch;
   UINT8 Index;
   UINT16 len = 0;
   
   if(PasswdEntryFlag == 1)
   {

      for (Index=0; Index < NUMBER_OF_CODES; Index++)
      {
        if( strcmp(LineBuffer, SecretCode[Index].Password) == 0 )
         break;
      }
   
      if (Index < NUMBER_OF_CODES)
      {
         SecretCode[Index].func();
         if (SecretCode[Index].ID == NULL) {
            len += AddToBuffer(to, (UINT8)3);
         }
         else {
            len += AddToBuffer(to, (UINT8)4);
            len += AddToBuffer(to, (UINT8)(SecretCode[Index].ID>>8));
            len += AddToBuffer(to, (UINT8)SecretCode[Index].ID);
         }
      }
      else
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_ENTRY2;
         ErrorResponseMaxLimit = 0;
      }
   }
   else if(PasswdEntryFlag == 2)
   {
         AccessLevel = MAINTENANCE;
         strcpy (PasswordBuffer, LineBuffer);
         CurrentSetup.PassWordFlag = WorkingPasswordFlag;  /* Turn on for real now */
         /* Limit the maintenance password to six Chars */
         if(strlen(PasswordBuffer) > MAX_PASSWORD_CHAR)
            PasswordBuffer[MAX_PASSWORD_CHAR] = NUL;
         strcpy(CurrentSetup.PassWordID,PasswordBuffer); /* Set to new password */

         len += AddToBuffer(to, (UINT8)1);      /* Password accepted */
   }
   else
   {
         if(strlen(LineBuffer) > MAX_PASSWORD_CHAR)
            LineBuffer[MAX_PASSWORD_CHAR] = NUL;
         MisMatch = strcmp(LineBuffer, CurrentSetup.PassWordID);
         if (MisMatch)   /*Dummy password if user forgot the password.*/
            MisMatch = strcmp(LineBuffer, "#MAZN#");

         if (!MisMatch)            /* Password accepted */
         {
            AccessLevel = MAINTENANCE;
            len += AddToBuffer(to, (UINT8)1);
         }
         else                    /* Tell user password was wrong */
         {
            len += AddToBuffer(to, (UINT8)2);
         }
   }
  return (len);
}            

/****************************************************************************/
/*================================END=======================================*/
/****************************************************************************/
