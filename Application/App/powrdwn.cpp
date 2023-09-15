/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/powrdwn.cpp_v   1.12   10 Nov 2014 04:55:26   AnPawar  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/powrdwn.cpp_v  $
 * 
 *    Rev 1.12   10 Nov 2014 04:55:26   AnPawar
 * PrePowerDown() setting pressure to 0.12.F review change.
 * 
 *    Rev 1.11   26 Sep 2014 03:11:06   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.10   11 Sep 2014 11:02:14   rjamloki
 * Updated Fram EventHistoryCount in power down
 * 
 *    Rev 1.9   05 Sep 2014 05:03:44   rjamloki
 * PrePowerdown change to store wled count in preset info object
 * 
 *    Rev 1.8   28 Jul 2014 12:36:42   rjamloki
 * psos.h removed
 * 
 *    Rev 1.7   11 Jun 2014 12:00:34   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.6   21 May 2014 10:48:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:34:38   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:46   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: powrdwn.c

 ---------------------------- DESCRIPTION ----------------------------------**/
#include "qdef.h"
#include "preset.h"
#include "battram.h"
#include "powrdwn.h"
#include "mansensr.h"
#include "dups_api.h"
#include "string.h"
#include "digout.h"
#include "Events.h"


/**-------------------------EXTERNAL DATA------------------------------------**/

extern BOOLEAN        PDownDelay;
extern UINT16         InitPrinterOnceOnPowerup;

/**-------------------------LOCAL GLOBAL DATA--------------------------------**/


void PrePowerDown(void)
/*-----------------------------------------------*/
/* This function saves all necessary information */
/* before physically shutting off the system     */
/*-----------------------------------------------*/
{
   UINT32 FramStatus;
  
   SETUPS_Ver1200 * FRAMCurrentPreset = CalculatePresetAddress(CURRENT_PRESET_INDEX);
   //If we loose even reason due to power down we need to make sure we dont loose the
   //event
   FRAMEventHistoryObj.EventHistoryCount += EventHistCountTemp;
/* Put the proportional valve into a safe mode before power is lost */
   SetPV(SHUT_DOWN_VALUE, FORCE_CALIBRATION);
   SetPressureValue  = 0 ;
/* First save the weld counter in the current preset */
   FRAMCurrentPreset->WeldCount = CurrentPreset.WeldCount;
   FRAMPresetInfo[0].WeldCount = CurrentPreset.WeldCount;

/* Store CurrentSetup Parameter Change from DRAM to BATTRAM */
   FramStatus = FramAccess(FRAM_WRITE, CONFIG_SECTION,(UINT8 *)&CurrentSetup, (UINT32)FRAM1200_CONFIG_START, sizeof(CurrentSetup));

/* Save the BUCMENU stuff into BATTRAM now */
   memcpy(BUCMenuFRAM, &BUCMenuRAM, sizeof(BUCMENU_1200) );

   PDownDelay = TRUE;
   SVOff();                           /* Release SV, send horn home   */
   PSIdle();                          /* Turn off the sonics          */

/* TRUE: This will reset printer flags when */
/* the system is powered up the next time.  */
 
   InitPrinterOnceOnPowerup = TRUE;

   PowerDownSystem();  /* Release the power relay here */
      while(TRUE);  /* Wait here pretty much forever, after all someone did power down, right? */

} /* PrePowerDown */
