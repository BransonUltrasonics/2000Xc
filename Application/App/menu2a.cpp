/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu2a.cpp_v   1.23   17 Nov 2015 16:32:42   RJamloki  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu2a.cpp_v  $
 * 
 *    Rev 1.23   17 Nov 2015 16:32:42   RJamloki
 * Get/Set the radio button option for the reset horn clamp alert
 * 
 *    Rev 1.22   27 Mar 2015 11:08:30   amaurya
 * Header comment added for SetWeldMode(),GetOpAuthority(),SetOpAuthority().
 * 
 *    Rev 1.21   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.20   28 Nov 2014 07:37:24   rjamloki
 * Added Default case in GetUserLevel().
 * 
 *    Rev 1.19   10 Nov 2014 11:20:38   RJamloki
 * Removed branson level from menu.
 * 
 *    Rev 1.18   10 Nov 2014 04:52:34   AnPawar
 * Removed CPLD extern.
 * 
 *    Rev 1.17   20 Oct 2014 06:21:06   AnPawar
 * GetWeldMode2() renamed to StoreOldWeldMode()
 * 
 *    Rev 1.16   26 Sep 2014 03:26:42   rjamloki
 * Operator authority is made global
 * 
 *    Rev 1.15   11 Sep 2014 11:01:02   rjamloki
 * Coverity and review fixes.
 * 
 *    Rev 1.14   18 Aug 2014 01:39:00   rjamloki
 * Removed struct in front of now packed user id object definition.
 * 
 *    Rev 1.13   28 Jul 2014 12:47:58   rjamloki
 * globals moved to command.cpp where they are actually used.
 * 
 *    Rev 1.12   09 Jul 2014 11:13:02   rjamloki
 * Removed redundant HwVerify setup functions.
 * 
 *    Rev 1.11   11 Jun 2014 11:54:30   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.10   27 May 2014 10:13:08   amaurya
 * Updated functions to save hostory setup in Current Setup
 * 
 *    Rev 1.9   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:08:36   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   07 May 2014 10:23:10   rjamloki
 *  ReadOut() function changed.Default password changed to username=Branson , password=1234. 
 * 
 *    Rev 1.6   21 Apr 2014 13:32:38   rjamloki
 * Diagnostic IO implementation added
 * 
 *    Rev 1.5   06 Mar 2014 11:03:50   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:30   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:42   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:34   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu2a.c

   Function name:

 ------------------------------- DESCRIPTION ---------------------------------

        This file will deal with the weld setup modes.

 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "keypad.h"
#include "param.h"                      
#include "selctkey.h"
#include "getmsg.h"
#include "command.h"
#include "cpld.h"
#include "Events.h"
#include "digout.h"
/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT16 RadioIndex;
extern UINT32 RadioIndexL;
extern UserID useridData;

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/
void FormatRunScreenTopLine(void);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/

/***************************************************************************
*   Purpose:
*	This function is called from the function SetWeldMode it stores the old
*   weld mode value in RadioIndexOld variable for event record
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void StoreOldWeldMode(void)
{
   switch(CurrentPreset.WeldMode){
   case TIMEMODE:
       RadioIndexOld = 0;
      break;
    case ENERGYMODE:
    	 RadioIndexOld = 1;
      break;
    case PKPOWERMODE:
    	 RadioIndexOld = 2;
      break;
    case COLLAPSEMODE:
    	 RadioIndexOld = 3;
      break;
    case ABSOLUTEMODE:
    	 RadioIndexOld = 4;
      break;
    case GRDDETECTMODE:
    	 RadioIndexOld = 5;
      break;
   }
}

/***************************************************************************
*   Purpose:
*	This function get weld mode from preset and assign it in RadioIndex
*	SBC uses this variable to weld mode in weld setup menu.
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void GetWeldMode(void)
{
   switch(CurrentPreset.WeldMode){
   case TIMEMODE:
      RadioIndex = 0;
      break;
    case ENERGYMODE:
      RadioIndex = 1;
      break;
    case PKPOWERMODE:
      RadioIndex = 2;
      break;
    case COLLAPSEMODE:
      RadioIndex = 3;
      break;
    case ABSOLUTEMODE:
      RadioIndex = 4;
      break;
    case GRDDETECTMODE:
      RadioIndex = 5;
      break;
   }
}

/***************************************************************************
*   Purpose:
*	This function set weld mode in preset based on RadioIndex.
*	SBC set RadioIndex variable from weld setup menu.
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void SetWeldMode(void)
{
   StoreOldWeldMode();
   switch(RadioIndex){
   case 0:
      CurrentPreset.WeldMode = TIMEMODE;
      break;
   case 1:
      CurrentPreset.WeldMode = ENERGYMODE;
      break;
   case 2:
      CurrentPreset.WeldMode = PKPOWERMODE;
      break;
   case 3:
      CurrentPreset.WeldMode = COLLAPSEMODE;
      break;
   case 4:
      CurrentPreset.WeldMode = ABSOLUTEMODE;
      break;
   case 5:
      CurrentPreset.WeldMode = GRDDETECTMODE;
      break;
   }
   FormatRunScreenTopLine();
}

/***************************************************************************
*   Purpose:
*	Function prepares the RadioIndxe value for Menu based on current
*	Operator authority setting
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void GetOpAuthority(void)
{
   RadioIndex = 0;

   if( (FRAMUserIdObj.GlobalOpAuth & RADIO_0) != 0  )
      RadioIndex |= RADIO_0;

   if( (FRAMUserIdObj.GlobalOpAuth & RADIO_1) != 0  )
      RadioIndex |= RADIO_1;

   if( (FRAMUserIdObj.GlobalOpAuth & RADIO_2) != 0  )
      RadioIndex |= RADIO_2;

   if( (FRAMUserIdObj.GlobalOpAuth & RADIO_3) != 0  )
      RadioIndex |= RADIO_3;

   if( (FRAMUserIdObj.GlobalOpAuth & RADIO_4) != 0  )
      RadioIndex |= RADIO_4;

   if ((FRAMUserIdObj.GlobalOpAuth & RADIO_5) != 0)
	   RadioIndex |= RADIO_5;
}

/***************************************************************************
*   Purpose:
*	Function sets the Operator Authority settings received from Menu
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void SetOpAuthority(void)
{
	userOpAuth = (enum OpAuth)0;

   if( (RadioIndex & RADIO_0) != 0 )
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)ResetAlarm);

   if( (RadioIndex & RADIO_1) != 0 )
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)RunInvalidatedPreset);

   if( (RadioIndex & RADIO_2) != 0 )
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)RecalPreset);

   if( (RadioIndex & RADIO_3) != 0 )
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)Calibration);

   if( (RadioIndex & RADIO_4) != 0 )
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)RstBatchCount);
   
   if ((RadioIndex & RADIO_5) != 0)
	   userOpAuth = (enum OpAuth)((int)userOpAuth | (int)RstHornClampAlarm);

	if(FRAMUserIdObj.GlobalOpAuth != userOpAuth) {//the operator authority changed
			 EventParameterID = AUTHORITY_CHANGE;
			 RecordEvents(EVENT_USER_MODIFIED,FRAMUserIdObj.GlobalOpAuth, userOpAuth);
			 FRAMUserIdObj.GlobalOpAuth = userOpAuth;
		}
}

/***************************************************************************
*   Purpose:
*	Function sets the user level settings received from Menu
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void SetUserLevel(void) {
	switch (RadioIndex) {
	case 0:
		useridData.UserLevel = OPERATOR;
		break;
	case 1:
		useridData.UserLevel = TECHNICIAN;
		break;
	case 2:
		useridData.UserLevel = SUPERVISOR;
		break;
	case 3:
		useridData.UserLevel = EXECUTIVE;
		break;
	}
}

/***************************************************************************
*   Purpose:
*	Function prepares the RadioIndex value for Menu based on current
*	user level setting
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void GetUserLevel(void) {
	switch (useridData.UserLevel) {
	case OPERATOR:
		RadioIndex = 0;
		break;
	case TECHNICIAN:
		RadioIndex = 1;
		break;
	case SUPERVISOR:
		RadioIndex = 2;
		break;
	case EXECUTIVE:
		RadioIndex = 3;
		break;
	default: break;
	}
}

/***************************************************************************
*   Purpose:
*	Get Weld History Setup bits from current setup and send to SBC
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void GetWeldHistSetup(void)
{
   RadioIndexL = CurrentSetup.WeldHistSetup;
}

/***************************************************************************
*   Purpose:
*	Assigns Weld History Setup bits to current setup.
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void SetWeldHistSetup(void)
{
	CurrentSetup.WeldHistSetup = RadioIndexL;
}

/***************************************************************************
*   Purpose:
*	ReadOut function reads the logic on CPLD latches. Its called during IO Diagnostic
*	from menu.
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void ReadOut(void)
{
	switch (GlobalCommandID) {
	case DIAGJ3_4OUT:
        RadioIndex = (UINT16) cpld->ReadDoutState(SVDrive_Lo);
		break;
	case DIAGJ3_5OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(Reject);
		break;
	case DIAGJ3_6OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(Gen_Alarm);
		break;
	case DIAGJ3_8OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(J3_8);
		break;
	case DIAGJ3_20OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(Suspect);
		break;
	case DIAGJ3_21OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(ReadySig);
		break;
	case DIAGJ3_22OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(J3_22);
		break;
	case DIAGJ3_34OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(PB_Release);
		break;
	case DIAGJ3_35OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(Weld_On);
		break;
	case DIAGJ3_36OUT:
		RadioIndex = (UINT16) cpld->ReadDoutState(J3_36);
		break;
	}
}

/***************************************************************************
*   Purpose:
*   This function sets the logic on diagnostic output pins.RadioIndex
*   variable holds the logic to be set.
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void DiagnoseOut(void) {
	switch (GlobalCommandID) {
	case DIAGJ3_4OUT: //SOL_VALVE_SRC
		cpld->SetDout(SVDrive_Lo/*SVLowOut*/, (bool) (RadioIndex));
		cpld->SetDout(SV1 /*SVHiOut*/, (bool) (!RadioIndex));
		break;
	case DIAGJ3_5OUT:
		cpld->SetDout(Reject, (bool) RadioIndex);
		break;
	case DIAGJ3_6OUT:
		cpld->SetDout(Gen_Alarm, (bool) RadioIndex);
		break;
	case DIAGJ3_8OUT:
		cpld->SetDout(J3_8, (bool) RadioIndex);
		break;
	case DIAGJ3_20OUT:
		cpld->SetDout(Suspect, (bool) RadioIndex);
		break;
	case DIAGJ3_21OUT:
		cpld->SetDout(ReadySig, (bool) RadioIndex);
		break;
	case DIAGJ3_22OUT:
		cpld->SetDout(J3_22, (bool) RadioIndex);
		break;
	case DIAGJ3_34OUT:
		cpld->SetDout(PB_Release, (bool) RadioIndex);
		break;
	case DIAGJ3_35OUT:
		cpld->SetDout(Weld_On, (bool) RadioIndex);
		break;
	case DIAGJ3_36OUT:
		cpld->SetDout(J3_36, (bool) RadioIndex);
		break;
	}
}

/***************************************************************************
*   Purpose:
*   This function returns the logic on Diagnostic input pins.
*   RadioIndex variable holds the logic to be set.
*
*   Entry condition:
*	void
*   Exit condition:
*	void
***************************************************************************/
void DiagnoseIn(void)
{
	switch (GlobalCommandID) {
	case DIAGJ3_1IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_1_Input_Sig);
		break;
	case DIAGJ3_32IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_32_Input_Sig);
		break;
	case DIAGJ3_33IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_33_Input_Sig);
		break;
	case DIAGJ3_19IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_19_Input_Sig);
		break;
	case DIAGJ3_17IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_17_Input_Sig);
		break;
	case DIAGJ3_31IN:
		RadioIndex = (UINT16) CPLD::GetDin(J3_31_Input_Sig);
		break;
	}
}
