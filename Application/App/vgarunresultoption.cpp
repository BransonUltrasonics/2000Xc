/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgarunresultoption.cpp_v   1.5   08 Apr 2015 13:47:18   AnPawar  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/vgarunresultoption.cpp_v  $
 * 
 *    Rev 1.5   08 Apr 2015 13:47:18   AnPawar
 * Changes for Pressure Stepping
 * 
 *    Rev 1.4   26 Sep 2014 03:11:10   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.3   22 Aug 2014 07:06:20   rjamloki
 * Hold force addition for weld result column selection
 * 
 *    Rev 1.2   18 Aug 2014 01:36:08   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.1   28 Jul 2014 12:40:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.0   11 Jun 2014 13:21:26   rjamloki
 * Initial revision.
 * 
 *    Rev 1.6   21 May 2014 10:48:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:36:36   rjamloki
 * extern variables clean up and coverity fixes
 * 
 *    Rev 1.4   05 Mar 2014 13:56:40   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:50   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:46   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: vgarunresultoption.c

      Written by:  
            Date:  
        Language: "C"

  -------------------------------- DESCRIPTION --------------------------------







  ------------------------------ INCLUDE FILES --------------------------------
*/

#include <string.h>
#include "menu.h"
#include "param.h"
#include "portable.h"
#include "preset.h"
#include "beep.h"
#include "menu1.h"
#include "battram.h"
#include "graphs.h"
#include "command.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/
#define INDEX_START     2
#define MAX_DISPLAYED_PARAM  5 

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */
enum WeldParamColoum  { NOT_DISPLAY = BIT0,    /*Display position on RunResultScreen.*/
                            COLUMN1 =BIT1,
                            COLUMN2 =BIT2,
                            COLUMN3 =BIT3,
                            COLUMN4 =BIT4
                            };

UINT16 StoreSelectedItem;
SINT8 VGAWeldParamStr[VGA_LINESIZE];
/*InitializeRunResultParameters*/               
//UINT16 ResultDisplayPos[MAXSCROLLMENUS];
UINT16 ResultDisplayPos[RMAXPARAMETERS];
	/* 0---*/
	/* 1---*/
	/* 2 -Display postion of Time        */
	/* 3 -Display postion of PeakPwr     */
	/* 4 -Display postion of Energy      */
	/* 5 -Display postion of Velocity Aed*/
	/* 6 -Display postion of Velocity Aef*/
	/* 7 -Display postion of Weld Abs    */
	/* 8 -Display postion of Total Abs   */
	/* 9 -Display postion of Weld Col    */
	/* 10-Display postion of Total Col   */
	/* 11-Display postion of Set Amp A   */
	/* 12-Display postion of Set Amp B   */
	/* 13-Display postion of Set Force A */
	/* 14-Display postion of Set Force B */
	/* 15-Display postion of Weld Force  */
	/* 16-Display postion of Act Press   */
	/* 17-Display postion of Freq Min    */
	/* 18-Display postion of Freq Max    */
	/* 19-Display postion of Freq Start  */
	/* 20-Display postion of Freq End    */
	/* 21-Display postion of Freq Chg    */
    /* 22-Display postion of PresetNum   */

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

UINT16 SelectedDisplayItem = 0;/*Stores the value of currently selected    */
                             /*RADIOMENU item.*/

UINT16 IsDisplay;  /*VPtr of all RADIO items, Store current display */
                          /*position of selected item.                     */
UINT16 IsDisplay1;
/*

 ----------------------------- EXTERNAL FUNCTIONS ----------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT16 RadioIndex;
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

MENUEND endWeldResultSetup = {TRUE};/*Local Type variables*/

/*
 --------------------------- GLOBAL FUNCTION PROTOTYPES -------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

void SaveWeldParamState(void);
void ChangeDisplayColumn (void);
void GetSelectedDisplayParam(UINT16 TempGlobalCommandID);

/*
 ---------------------------------- CODE -------------------------------------
*/


//Change in GetCurrentscreenType() and make currentscreen=MENU_SCREEN for  WeldResultsSumbmenu.

/*==========================================================================*/
/*     RADIO STRUCTURE FOR RADIO SCREEN TO SELECT DISPLAY POSITION          */
/*==========================================================================*/



/*==========================================================================*/
/*          FUNCTIONS TO PROCESS WELD RESULT SETUP SCREEN                   */
/*==========================================================================*/


void SaveWeldParamState(void)
/***************************************************************************/
/*Description:                                                             */
/*   This function will be called by the radio structure if the value is   */
/*   changed successfully and user exited the screen by pressing Save      */
/*   button.It stores the currently selected position of parameter in      */
/*   respective array.                                                     */
/***************************************************************************/
{
    UINT16 index, SelectedItem = 0;
    CONFIGSETUP *FRAMPtr;
      
    FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
    
    switch (RadioIndex)
    {
       case 0:
          IsDisplay1 = RADIO_0;
          SelectedItem = 0;         
       break;
       case 1:
          IsDisplay1 = RADIO_1;
          SelectedItem = 1;         
       break;
       case 2:
          IsDisplay1 = RADIO_2;
          SelectedItem = 2;         
       break;
       case 3:
          IsDisplay1 = RADIO_3;
          SelectedItem = 3;         
       break;
       case 4:
          IsDisplay1 = RADIO_4;
          SelectedItem = 4;         
       break;
    }
    if(!((SelectedItem) &&   ( CurrentSetup.WeldParamOption[SelectedItem] != 0 ))) 
    {
       GetSelectedDisplayParam(GlobalCommandID);
       ResultDisplayPos[SelectedDisplayItem] = IsDisplay1;   
       for(index=1;index < MAX_DISPLAYED_PARAM; index++)
          CurrentSetup.WeldParamOption[index]=0;
       
       for(index=INDEX_START; index < RMAXPARAMETERS; index++)
       {
           if(ResultDisplayPos[index] == COLUMN1)
              CurrentSetup.WeldParamOption[1]= index;
           else if(ResultDisplayPos[index] == COLUMN2)
              CurrentSetup.WeldParamOption[2]= index;
           else if(ResultDisplayPos[index] == COLUMN3)
              CurrentSetup.WeldParamOption[3]= index;
           else if(ResultDisplayPos[index] == COLUMN4)
              CurrentSetup.WeldParamOption[4]= index;   
       }
      /*Update all the current setup and BUCMenu variables */
      FRAMPtr->WeldParamOption[1] = CurrentSetup.WeldParamOption[1];
      FRAMPtr->WeldParamOption[2] = CurrentSetup.WeldParamOption[2];
      FRAMPtr->WeldParamOption[3] = CurrentSetup.WeldParamOption[3];
      FRAMPtr->WeldParamOption[4] = CurrentSetup.WeldParamOption[4];
    }
    else
    {
       GetSelectedDisplayParam(GlobalCommandID);
       NackError = WELDER_PROCESS_ERROR;
       ErrorResponseMinLimit = COLSETUP_MSG_SCREEN;
       ErrorResponseMaxLimit = 0;    
    }
}

void GetSelectedDisplayParam(UINT16 TempGlobalCommandID)
/***************************************************************************/
/*Description:                                                             */
/*   When user selects any of the RADIOMENU paramenter in WeldResultSetup  */
/*   Menu then this function will be called.It will store the value of     */
/*   selected parameter into a variable for altering its display position. */
/***************************************************************************/

{
   StoreSelectedItem = 0;
   SelectedDisplayItem = 0;/*Initializing the selected variable.*/

   switch(TempGlobalCommandID)
   {
   case TIMEDISPLAY:
         SelectedDisplayItem = RTIME;
         break;
   case PKPWRDISPLAY:
         SelectedDisplayItem = RPKPWR;
         break;
   case ENERGYDISPLAY:
         SelectedDisplayItem = RENERGY;
         break;
   case VELOCITYDISPLAYAED:
         SelectedDisplayItem = RVELOCITY_AED;
         break;
   case VELOCITYDISPLAYAEF:
         SelectedDisplayItem = RVELOCITY_AEF;
         break;
   case FREQMINDISPLAY:
         SelectedDisplayItem = RFREQMIN;
         break;
   case FREQMAXDISPLAY:
         SelectedDisplayItem = RFREQMAX;
         break;
   case FREQSTARTDISPLAY:
         SelectedDisplayItem = RFREQSTART;
         break;
   case FREQENDDISPLAY:
         SelectedDisplayItem = RFREQEND;
         break;
   case FREQCHGDISPLAY:
         SelectedDisplayItem = RFREQCHG;
         break;
   case SETAMPADISPLAY:
         SelectedDisplayItem = RAMPSTART;
         break;
   case SETAMPBDISPLAY:
         SelectedDisplayItem = RAMPEND;
         break;
   case WELDABSDISPLAY:
         SelectedDisplayItem = RWABSDIST;
         break;
   case ACTPRESSDISPLAY:
         SelectedDisplayItem = RSYSPRESS;
         break;
   case TOTALABSDISPLAY:
         SelectedDisplayItem = RTABSDIST;
         break;
   case WELDCOLDISPLAY:
         SelectedDisplayItem = RWCOLDIST;
         break;
   case TOTALCOLDISPLAY:
         SelectedDisplayItem = RTCOLDIST;
         break;
   case WELDFORCEDISPLAY:
         SelectedDisplayItem = RFORCE;
         break;
   case SETPRESSUREADISPLAY:
         SelectedDisplayItem = RPRESSUREA;
         break;
   case SETPRESSUREBDISPLAY:
         SelectedDisplayItem = RPRESSUREB;
         break;
   case PRESETNUMDISPLAY:
         SelectedDisplayItem = RPRESETNUM;
         break;
   case CYCLETIMEDISPLAY:
         SelectedDisplayItem = RCYCLETIME;
         break;
   case USR_ID_COL:
         SelectedDisplayItem = RUSERID;
         break;
   case UDI_COL:
         SelectedDisplayItem = RUDISCAN;
         break;
   case PRESETREV_COL:
         SelectedDisplayItem = RPRESETREV;
         break;
   case HOLDFORCE_MAX:
	    SelectedDisplayItem = RHOLDFORCEMAX;
         break;
   }
}/*end of GetSelectedDisplayParam()*/


void BuildWeldColumnStr(void)
/****************************************************************************/
/*Description:                                                              */
/*   This function preapares the display coloumn for each Weld parameter    */
/*   to show on the weld results options screen. This function is called    */
/*   before display the menu weld result options.                           */
/****************************************************************************/
{
    GetSelectedDisplayParam(GlobalCommandID);
    switch(ResultDisplayPos[SelectedDisplayItem])
    {
        case NOT_DISPLAY:
           RadioIndex = 0;
        break;
        case COLUMN1:
           RadioIndex = 1;
        break;
        case COLUMN2:
           RadioIndex = 2;
        break;
        case COLUMN3:
           RadioIndex = 3;
        break;
        case COLUMN4:
           RadioIndex = 4;
        break;
        default:
        break;
    }
    
}

void InitWeldParamOption(void)
/***************************************************************************/
/*Description:                                                             */
/* Initializes the Weld Parameter Option                                   */
/***************************************************************************/
{
   UINT8 Index;
   UINT8 Index1;
   BOOLEAN SetFlag;
         
   
   /* Check the current Weld Param options, if they are corrupted
      or not valid then initialize*/
   CurrentSetup.WeldParamOption[0] = RCYCLECOUNT;
   for(Index = 1; Index < MAX_DISPLAYED_PARAM; Index++)
   {
      if((CurrentSetup.WeldParamOption[Index] < RUSERID) ||
         (CurrentSetup.WeldParamOption[Index] > RHOLDFORCEMAX))
         CurrentSetup.WeldParamOption[Index] = 0;
   }
   
//   for(Index=INDEX_START; Index < MAXSCROLLMENUS; Index++)
   for(Index=INDEX_START; Index < RMAXPARAMETERS; Index++)
    {
        SetFlag = FALSE;
        
        for(Index1 = 1; Index1 < MAX_DISPLAYED_PARAM; Index1++)
        {
           if(Index == CurrentSetup.WeldParamOption[Index1])
           {
              if(((CurrentSetup.Actuator == AED)||
                    (CurrentSetup.Actuator == MICRO)) &&
                  (Index == RPRESSUREA   || Index == RPRESSUREB))
              {
                 SetFlag = FALSE;
                 CurrentSetup.WeldParamOption[Index1] = 0;
              }
              else if((CurrentSetup.Actuator == AE) &&
                  (Index == RWABSDIST || Index == RTABSDIST ||
                   Index == RWCOLDIST || Index == RTCOLDIST ||
                   Index == RPRESSUREA   || Index == RPRESSUREB   ||
                   Index == RFORCE))
              {
                 SetFlag = FALSE;
                 CurrentSetup.WeldParamOption[Index1] = 0;
              }
              else  SetFlag = TRUE;
              break;
           }
           
        }
        
        if(SetFlag)
        {
           if(Index1 == 1)
              ResultDisplayPos[Index] = COLUMN1;
           else if(Index1 == 2)
              ResultDisplayPos[Index] = COLUMN2;
           else if(Index1 == 3)
              ResultDisplayPos[Index] = COLUMN3;
           else if(Index1 == 4)
              ResultDisplayPos[Index] = COLUMN4;
        }
        else
           ResultDisplayPos[Index] = NOT_DISPLAY;        
        
    }
}

void ChangeDisplayColumn (void)
/***************************************************************************/
/*Description:                                                             */
/*   This function will replace the current column with selected parameter */
/*   if any other parameter is already displayed on the same column. This  */
/*   function is called when user pressed 'Ok' button on the Confirm screen*/
/***************************************************************************/
{
   UINT16 index, SelectedItem;
   CONFIGSETUP *FRAMPtr;
   
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;

   SelectedItem = RadioIndex;
   if((SelectedItem) && ( CurrentSetup.WeldParamOption[SelectedItem] != 0 )) 
   {
      StoreSelectedItem = SelectedItem;
      /*Store the Off in currently display parameter*/
      ResultDisplayPos[CurrentSetup.WeldParamOption[StoreSelectedItem]] = NOT_DISPLAY;

      /*Store the desired column on the selected parameter.*/
      switch(StoreSelectedItem)
      {
         case 1:/*Store Column1*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN1;
         break;
         case 2:/*Store Column2*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN2;
         break;
         case 3:/*Store Column3*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN3;
         break;
         case 4:/*Store Column4*/
            ResultDisplayPos[SelectedDisplayItem] = COLUMN4;
         break;
         default:
            ResultDisplayPos[SelectedDisplayItem] = NOT_DISPLAY;
         break;
       
      }
      for(index=1;index < MAX_DISPLAYED_PARAM;index++)
         CurrentSetup.WeldParamOption[index]=0;
      for(index=INDEX_START; index < RMAXPARAMETERS; index++)
      {
         if(ResultDisplayPos[index] == COLUMN1)
         CurrentSetup.WeldParamOption[1]= index;
         else if(ResultDisplayPos[index] == COLUMN2)
         CurrentSetup.WeldParamOption[2]= index;
         else if(ResultDisplayPos[index] == COLUMN3)
         CurrentSetup.WeldParamOption[3]= index;
         else if(ResultDisplayPos[index] == COLUMN4)
         CurrentSetup.WeldParamOption[4]= index;   
      }
      /*Update all the current setup and BUCMenu variables */
      FRAMPtr->WeldParamOption[1] = CurrentSetup.WeldParamOption[1];
      FRAMPtr->WeldParamOption[2] = CurrentSetup.WeldParamOption[2];
      FRAMPtr->WeldParamOption[3] = CurrentSetup.WeldParamOption[3];
      FRAMPtr->WeldParamOption[4] = CurrentSetup.WeldParamOption[4];
   }
}

/*==========================================================================*/
/*                         END                                              */
/*==========================================================================*/






