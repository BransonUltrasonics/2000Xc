/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu.cpp_v   1.24   Jun 07 2017 16:57:36   RJamloki  $ */
/****************************************************************************/ 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/menu.cpp_v  $
 * 
 *    Rev 1.24   Jun 07 2017 16:57:36   RJamloki
 * change config variable to LowerFlowValveFlag
 * 
 *    Rev 1.23   Jun 07 2017 13:05:20   RJamloki
 * Update small flow valve config variable
 * 
 *    Rev 1.22   May 25 2017 17:28:02   RJamloki
 * Update new secret code number for small flow valve
 * 
 *    Rev 1.21   16 Apr 2015 07:24:08   rjamloki
 * Added Estop Hw Version selection in Select New and Old board functions
 * 
 *    Rev 1.20   02 Jan 2015 04:04:50   rjamloki
 * var_format_def2 VarFormatTable[] added PSI and Kpa for weld and hold pressure
 * 
 *    Rev 1.19   28 Nov 2014 07:36:40   rjamloki
 * InsertProperUnits() changed to remove unused pointer variable.
 * 
 *    Rev 1.18   14 Nov 2014 05:29:06   rjamloki
 * SetTableToDefault added to secretcode array.
 * 
 *    Rev 1.17   06 Oct 2014 06:39:06   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.16   03 Oct 2014 06:02:44   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.15   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.14   18 Aug 2014 01:42:18   rjamloki
 * Added dummy in place of configure AES without SBeam in SecretCode table
 * 
 *    Rev 1.13   28 Jul 2014 12:40:46   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.12   09 Jul 2014 11:09:18   rjamloki
 * Load cell and QVGA support removed. 
 * 
 *    Rev 1.11   20 Jun 2014 14:43:42   rjamloki
 * Fixed password for configuring AES with SBEAM.
 * 
 *    Rev 1.10   11 Jun 2014 11:48:08   rjamloki
 * Changes to move special function button to BUC menu from Diagnostic
 * 
 *    Rev 1.9   21 May 2014 10:48:00   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:08:20   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.7   14 Apr 2014 09:39:48   rjamloki
 * Fixed file inclusion due to renaming of led.h to fpled.h
 * 
 *    Rev 1.6   26 Mar 2014 12:21:04   rjamloki
 * static PsosReturnValue variable removed
 * 
 *    Rev 1.5   05 Mar 2014 13:56:28   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:40   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:32   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu.c

   Function name: void RemoveNull();                            
                  void DealWithScrollLeds();
                  SINT16 InsertProperUnits();
                  void DisplayMenu();
 ------------------------------- DESCRIPTION ---------------------------------

 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "qdef.h"
#include "names.h" 
#include "menu.h"
#include "menu2.h"
#include "menu5.h"
#include "menu7a.h"
#include "genrlmsg.h"
#include "fpkp_msg.h"
#include "keypad.h"
#include "preset.h"
#include "param.h"
#include "beep.h"
#include "ticks.h"
#include "selctkey.h"
#include "menu1.h"
#include "fpled.h"
#include "util.h"
#include "portable.h"
#include "weld_obj.h"
#include "getmsg.h"
#include "genalarm.h"
#include "menuhorn.h"
#include "menutest.h"
#include "statedrv.h"
#include "display.h"
#include "rtclock.h"
#include "dups_api.h"
#include "string.h"
#include "inports.h"
#include "psnvram.h"
#include "actnvram.h"
#include "ready.h"
#include "battram.h"
#include "FrontPanelStateCoordinatorTask.h"
#include "CyGOS.h"
#include "RTOS.h"
#include "CPU.h"
#include "command.h"
#include "WeldManagerTask.h"
#include "ticks.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/

#define SOLIDBLOCK  0xbe    /* Character substuted for '|' on display */
#define CHANGEDISTFORMATVAL 10000  /*Value at which distance format in Metric*/
                                      /*changes from 3 decimal to 2 decimal     */

#define CENTURY         2000
/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

UINT8    MainKeyFlag = FALSE;
UINT8    GoBackFlag = FALSE;
UINT8    PowerUpColdStart = FALSE;

UINT8    ExitMenuCounter = 0;

SINT8    ScrollBuffer[SCROLLBUFFERSIZE];

BOOLEAN  TestSonicsFlag = FALSE;
BOOLEAN  SubmenuFlag;

SINT16   MenuCounter = -1;
SINT16   HornMenuCount;
SINT16   BlankMenuCounter = 0;

SINT32   SecurityLevel = BRANSON;

// VARIABLE TYPE TABLE DEFINITION
//
// This table defines the features of various types of numerical items that
// can appear on a menu.  The source for each item is a SINT32, but there are
// many ways of converting this to text.  A DISTANCE value stored in the
// SINT32 as 54321 should be displayed as 5.4321 if USCS units are selected,
// or should be converted to metric if metric units are selected.  So
// conversion factors and the number of digits left and right of the decimal
// point must be in the table.  Also, there are items for which the entire
// available resolution is not displayed.  A VELOCITY stored as 653 will
// display as 6.5 in/s in USCS units.  The table therefore specifies a
// conversion for USCS (English) as well as Metric.  In the English
// conversion, the value in the SINT32 may be divided by 10, 100, or some
// other power of 10.
//
// Conversions are accomplished by taking the stored SINT32 (n) and finding:
//
//    x = (n * ConvMult + ConvDiv/2) / ConvDiv;
//

struct var_format_def2 VarFormatTable[] =
{
  {{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "%   ", 3, 0,  1, FALSE,   1,    1 }},
  {{ "lb  ", 4, 0,  1, FALSE, 1, 10 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "lb  ", 4, 1,  1, FALSE, 1,  1 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "s   ", 2, 3,  1, FALSE, 1,  1 }, { "s   ", 2, 3,  1, FALSE,   1,    1 }},
  {{ "PSI ", 3, 1,  1, FALSE, 1,  1 }, { "kPa ", 3, 0,  1, FALSE, 689, 1000 }},
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 2,  1, FALSE, 254, 1000 }},
  /* DISTANCE3, requires special handling for 7-character strings */
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 2, 3,  1, FALSE, 254, 100  }},
  {{ "Hz  ", 5, 0,  1, FALSE, 1,  1 }, { "Hz  ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "Hz  ", 4, 0,  1,  TRUE, 1,  1 }, { "Hz  ", 4, 0,  1,  TRUE,   1,    1 }},
  {{ "J   ", 3, 1,  1, FALSE, 1,  1 }, { "J   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "    ", 9, 0,  1, FALSE, 1,  1 }, { "    ", 9, 0,  1, FALSE,   1,    1 }},
  {{ "in/s", 2, 1,  1, FALSE, 1, 10 }, { "mm/s", 4, 0,  1, FALSE, 254, 1000 }},
  {{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 5, 0,  1, FALSE, 1,  1 }, { "    ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 2, 0,  1, FALSE, 1,  1 }, { "    ", 2, 0,  1, FALSE,   1,    1 }},
  {{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "%   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "J   ", 5, 0,  1, FALSE, 1, 10 }, { "J   ", 5, 0,  1, FALSE,   1,   10 }},
  {{ "    ", 4, 0,  1, FALSE, 1,  1 }, { "    ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "s   ", 8, 3,  1, FALSE, 1,  1 }, { "s   ", 8, 3,  1, FALSE,   1,    1 }},
  {{ "PSI ", 3, 0,  1, FALSE, 1,  10 }, { "kPa ", 3, 0,  1, FALSE,  689, 1000 }},
};

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

void DistanceULS(void);
void EnableStringDebug(void);
void DisableStringDebug(void);
void UpdateCalibDefault(void);
void SetTableToDefault(void);
void LowerPressureValveOn(void);
void LowerPressureValveOff(void);

#define BUCMENUID       10
#define DEFAULTID      128
#define DUPSMENUID      12
#define TFMENUID       129

/*--------------------------------------------------------------------------*/
/*  The following structure is for special codes that are entered while on  */
/*  main menu.  Each code will call a function. The entires required for    */
/*  each code are:                                                          */
/*                                                                          */
/*      Password - at least 8 digits, must be all numeric, no max limit     */
/*      A pointer - a pointer to keep track of digits entered so far        */
/*      A function -  a function to call when the code has been entered     */
/*      ID - if this code is required to display a menu on VGA.  In this    */
/*           case an SBC code change is probably required.  If not, set     */
/*           this field to NULL.                                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/



CODES SecretCode[NUMBER_OF_CODES] = {
/* Password       Ptr Function            ID        */
/* -------------  --- ------------------  ---       */
 {"19002726866",  0,  BUCMenu,            		BUCMENUID }, /* 0  1-900-Branson               */
 {"33284437",     0,  DebugMenu,          		NULL      }, /* 1  "DEBUGGER" on phone pad     */
 {"3492288726",   0,  InitializeFRAM,      		NULL      }, /* 2  "FIXBATTRAM" on phone pad   */
 {"534922868726", 0,  ConfigureAed,       		NULL      }, /* 3  5 + "FIXACTNVRAM"           */
 {"634922868726", 0,  ConfigureAef,       		NULL      }, /* 4  6 + "FIXACTNVRAM"           */
 {"6060099456",   0,  VelocityOn,         		NULL      }, /* 5  Code is built at power up   */
 {"6030399654",   0,  VelocityOff,        		NULL      }, /* 6  Code is built at power up   */
 {"789456123",    0,  CreateSecretCodes,  		NULL      }, /* 7  Code to enable other codes  */
 {"741236987",    0,  EnableDiagnostics,  		NULL      }, /* 8  Circle on keypad            */
 {"3228679",      0,  RestoreDefaults,    		DEFAULTID }, /* 9  Factory on keypad           */
 {"741852963",    0,  EnableTestingMenu,  		NULL      }, /* 10 Down keypad columns L to R  */
 {"963852741",    0,  EnableSpecialsMenu, 		NULL      }, /* 11 Down keypad columns R to L  */
 {"2326667569",   0,  SlowActADComm,      		NULL      }, /* 12 "ADCommSlow" on phone pad   */
 {"2326663278",   0,  FastActADComm,      		NULL      }, /* 13 "ADCommFast" on phone pad   */
 {"756937232666", 0,  SlowerActADComm,    		NULL      }, /* 14 "SlowerADComm" on phone pad */
 {"102242379",    0,  SelectOldBoard,     		NULL      }, /* 15 EDP#-old system controller  */
 {"102242594",    0,  SelectNewBoard,     		NULL      }, /* 16 EDP#-new system controller  */
 {"266344572326", 0,  ConfigAEDSbeam,     		NULL      }, /* 17 CONFIG+5+SBEAM for AED      */
 {"266344672326", 0,  ConfigAEFSbeam,     		NULL      }, /* 18 CONFIG+6+SBEAM for AEF      */
 {"26634472326",  0,  ConfigSBeam,        		NULL      }, /* 19 config actuator to SBEAM    */
 {"2663446232",   0,  ConfigLoadcell,     		NULL      }, /* 20 config actuator to Loadcell */
 {"34882623858",  0,  DistanceULS,        		NULL      }, /* 21                             */
 {"3488262388",   0,  DistanceSS,         		NULL      }, /* 22                             */
 {"38772668765",  0,  DupsControl,        		DUPSMENUID}, /* 23                             */
 {"7522668765",   0,  EnablePLCTiming,    		NULL      }, /* 24 "PLC Control"               */
 {"3622588",      0,  EnableUSEncoder,    		NULL      }, /* 25                             */
 {"3622566",      0,  EnableMetricEncoder,		NULL      }, /* 26                             */
 {"3622583",      0,  EnableTF,           		TFMENUID  }, /* 27 Enable trigger force menu   */
 {"2633300633",   0,  DisableCode300,     		NULL      }, /* 28 "Code300Off" on phone pad   */
 {"263330066",    0,  EnableCode300,      		NULL      }, /* 29 "Code300On" on phone pad    */
 {"101",          0,  EnableStringDebug,  		NULL      }, /* 30 Enable String no. display   */
 {"102",          0,  DisableStringDebug, 		NULL      }, /* 31 Disable String no. display  */
 {"266344772326", 0,  ConfigMICROSbeam,   		NULL      }, /* 32 CONFIG+7+SBEAM for MICRO    */
 {"87746472833",  0,  SetSpringRate3,     		NULL      }, /* 33 use 3 for LEAVINGHOMEFORCEMICRO */
 {"87746472834",  0,  SetSpringRate4,     		NULL      }, /* 34 use 4 for LEAVINGHOMEFORCEMICRO */
 {"22542728466",  0,  SaveCalibration,   		NULL      }, /* 35 Save calibration values     */
 {"2668539351",   0,  SetContLevelt,      		NULL      }, /* 36 Set control level to t      */
 {"2668539353",   0,  SetContLevelea,     		NULL      }, /* 37 Set control level to ea     */
 {"2668539354",   0,  SetContLeveld,      		NULL      }, /* 38 Set control level to d      */
 {"2668539355",   0,  SetContLevelf,      		NULL      }, /* 39 Set control level to f      */
 {"2668539350",   0,  SetContLeveldepot,  		NULL      }, /* 40 Set control level to depot  */
 {"2668539359",   0,  SetContLeveltest,   		NULL      }, /* 41 Set control level to test   */
 {"101134290",    0,  Config50mmMICRO,    		NULL      }, /* 42 Set New Micro Actuator      */
 {"159134348",    0,  ConfigOriginal_MICRO,		NULL      }, /* 43 Set New Micro Actuator      */
 {"229837",       0,  ConfigMaxMinValues,  		NULL      }, /* 44 Set Min max values for BAXTER*/
 {"734922868726", 0,  ConfigureDummy,       	NULL      }, /* 45  Dummy           */
 {"266344772325", 0,  ConfigAESSbeam,     		NULL      }, /* 46 CONFIG+7+SBEAM for AEF      */
 {"3492388799",   0,  SetTableToDefault,      	NULL      }, /* 47 Set default table to default values*/
 {"356966",   	  0,  LowerPressureValveOn,     NULL      }, /* 48 Lower Pressure Valve On   */
 {"3569633",      0,  LowerPressureValveOff,    NULL      }  /* 49 Lower Pressure Valve Off  */
};


/*-------------------- End of Special Codes section ------------------------*/


MENU *CurrentlyDisplayedMenu = 0;      /* Allows rest of system to peek at */
                                       /* current menu. */

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT16  DiagFlag;
extern UINT16  DebugPasswordFlag;
extern BOOLEAN DebugBase;
extern BOOLEAN DebugBytes;
extern UINT16  TestingMenuFlag;
extern UINT16  SpecialMenuFlag;
extern UINT16  BransonFunctionFlag;
extern UINT16  MicroHomeForce;

extern UINT32  KeyMask;

extern enum LEVEL AccessLevel;

extern UINT16 ResultDisplayPos[];
extern DEPOT_FLAGS  *DepotFlag;

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

static GENERIC_MSG            WeldMsgOut;
UINT32                 HWConfiguration = VGA;
UINT32                 SWConfiguration;

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

void SetTableToDefault(void)
{
	SetDefCalSysPressure((SINT16)LOW_PRESSURE);
	SetDefCalStrokeLength(DEF_CAL_LENGTH);
	SetDefPressure();
	SetDefLoadCell();
	SetDefForce();
}

void DistanceULS(void)
{
   CurrentSetup.DistanceULS = TRUE;
}

void DistanceSS(void)
{
   CurrentSetup.DistanceULS = FALSE;
}

void EnableHSCandSBL(void)
{
   UpdateSWConfiguration(HSC, TRUE);               /* Enable HSC  */
   BransonFunctionFlag = TRUE; 
   UpdateSWConfiguration(SBL_EN, TRUE);
   CurrentSetup.SBLEnable = TRUE;
}

void DisableHSCandSBL(void)
{
   UpdateSWConfiguration(HSC, FALSE);               /* Disable HSC  */
   BransonFunctionFlag = FALSE; 
   UpdateSWConfiguration(SBL_EN, FALSE);
   CurrentSetup.SBLEnable = FALSE;
}

void VelocityOn(void)
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[5].Ptr = SecretCode[5].Password;
   UpdateSWConfiguration(VEL, TRUE);               /* Set velocity reporting on  */
   BUCMenuRAM.VelocityReporting = TRUE;                                             
   BUCMenuFRAM->VelocityReporting = TRUE;                                             
}



void VelocityOff(void)
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[6].Ptr = SecretCode[6].Password;
   UpdateSWConfiguration(VEL, FALSE);              /* Set velocity reporting off */
   BUCMenuRAM.VelocityReporting = FALSE;
   BUCMenuFRAM->VelocityReporting = FALSE;
   
//   /* if Act. Type is AEF & VEL is configured, then RVELOCITY is already
//      configured reset it*/
//   for(Index = 1; Index < 5; Index++)
//   {
//      if(CurrentSetup.WeldParamOption[Index] == RVELOCITY_AEF &&
//         CurrentSetup.Actuator == AEF)
//         CurrentSetup.WeldParamOption[Index] = 0;
//   }
   ResultDisplayPos[RVELOCITY_AEF] = BIT0; //NOT_DISPLAY      
   
}



void CreateSecretCodes(void)
/***************************************************************************/
/*                                                                         */
/*  This function will create secret codes using the power supply serial   */
/*  number as part of the code.  This helps to ensure this code will only  */
/*  work on one system.  The base code below is the starting point.  All   */
/*  zeros and nines will be replaced with values from the serial number.   */
/*                                                                         */
/***************************************************************************/
{
   static STR VelocityOnStr[]  = "6060099"; /* Base code, not machine specific */
   static STR VelocityOffStr[] = "6030399"; /* Base code, not machine specific */
   UINT16 TempSum1, TempSum10, x;
   
/*  The first code is to enable velocity reporting - machine specfic */

   SecretCode[5].Ptr = VelocityOnStr;
   SecretCode[5].Password = VelocityOnStr;
   if ((CurrentSetup.PSSerialNumber[7] >= '0') && (CurrentSetup.PSSerialNumber[7] <= '9'))
      VelocityOnStr[1] = CurrentSetup.PSSerialNumber[7];
   else 
      VelocityOnStr[1] = '9';
   if ((CurrentSetup.PSSerialNumber[9] >= '0') && (CurrentSetup.PSSerialNumber[9] <= '9'))
      VelocityOnStr[3] = ('9' - CurrentSetup.PSSerialNumber[9]) + '0';
   else
      VelocityOnStr[3] = '9';
   VelocityOnStr[5] = '0';  /* Temporarily set to zero for checksum */
   VelocityOnStr[6] = '0';  /* Temporarily set to zero for checksum */
   TempSum1 = 0;
   TempSum10 = 0;
   for (x=0; x<(sizeof(VelocityOnStr)-1); x++) {  /* Start checksum calculation */
      TempSum1 += (UINT16)(VelocityOnStr[x] - '0');
      if (TempSum1 > 9) {
         TempSum10++;
         TempSum1 -= 10;
      }
   }
   VelocityOnStr[5] = (TempSum10 + '0');
   VelocityOnStr[6] = (TempSum1 + '0');
   VelocityOnStr[7] = 0;


/*  The second code is to disable velocity reporting - machine specfic*/

   SecretCode[6].Ptr = VelocityOffStr;
   SecretCode[6].Password = VelocityOffStr;
   if ((CurrentSetup.PSSerialNumber[8] >= '0') && (CurrentSetup.PSSerialNumber[8] <= '9'))
      VelocityOffStr[1] = ('9' - CurrentSetup.PSSerialNumber[8]) + '0';
   else   
      VelocityOffStr[1] = '9';
   if ((CurrentSetup.PSSerialNumber[6] >= '0') && (CurrentSetup.PSSerialNumber[6] <= '9'))
      VelocityOffStr[3] = CurrentSetup.PSSerialNumber[6];
   else
      VelocityOffStr[3] = '9';
   VelocityOffStr[5] = '0';  /* Temporarily set to zero for checksum */
   VelocityOffStr[6] = '0';  /* Temporarily set to zero for checksum */
   TempSum1 = 0;
   TempSum10 = 0;
   for (x=0; x<(sizeof(VelocityOffStr)-1); x++) { /* Start checksum calculation */
      TempSum1 += (UINT16)(VelocityOffStr[x] - '0');
      if (TempSum1 > 9) {
         TempSum10++;
         TempSum1 -= 10;
      }
   }
   VelocityOffStr[5] = (TempSum10 + '0');
   VelocityOffStr[6] = (TempSum1 + '0');
   VelocityOffStr[7] = 0;
}



void BUCMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the Branson Menu.                                             */
/*                                                                         */
/***************************************************************************/
{
   AccessLevel = BRANSON;
//   UpdateDUPSRAMParamSet(); /*Update DUPS_CurrParamSet before enter to BUC Menu */
   SpecialMenuFlag = TRUE;     /* This turns on the diagnostics via RS-232 */
   BransonFunctionFlag = TRUE;/*Display the Specials menu on Diagnostic Screen.*/
}



void DupsControl(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the DUPS controlMenu.                                         */
/*                                                                         */
/***************************************************************************/
{

   AccessLevel = BRANSON;
//   UpdateDUPSRAMParamSet(); /*Update DUPS_CurrParamSet before enter to BUC Menu */
}



void EnableTF(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the Enable trigger force                                      */
/*                                                                         */
/***************************************************************************/

{
   AccessLevel = BRANSON;
}



void DisableCode300(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the recal error code 300 to be disabled.      */
/*  This must be changed by a secret code.  The default is to have error   */
/*  code 300 enabled.                                                      */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[28].Ptr = SecretCode[28].Password;
   UpdateSWConfiguration(CAL, FALSE);           /* Turn off error code 300  */
   BUCMenuRAM.RecalCode300 = FALSE;
   BUCMenuFRAM->RecalCode300 = FALSE;
}



void EnableCode300(void)
/***************************************************************************/
/*                                                                         */
/*  This function will re-enable recal error code 300.  This is also the   */
/*  default condition.  It will be enabled whenever the system control     */
/*  level is set.                                                          */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[29].Ptr = SecretCode[29].Password;
   UpdateSWConfiguration(CAL, TRUE);            /* Turn on error code 300   */
   BUCMenuRAM.RecalCode300 = TRUE;                                             
   BUCMenuFRAM->RecalCode300 = TRUE;                                             
}

void EnableStringDebug(void)
{
}

void DisableStringDebug(void)
{
}

void EnableDiagnostics(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   OnboardDiag = TRUE;         /* This turns on the diagnostics via RS-232 */
}



void EnableTestingMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   TestingMenuFlag = TRUE;     /* This turns on the diagnostics via RS-232 */
   BransonFunctionFlag = TRUE; /*Display the Specials menu on Diagnostic Screen.*/
}



void EnableSpecialsMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   SpecialMenuFlag = TRUE;     /* This turns on the diagnostics via RS-232 */
   BransonFunctionFlag = TRUE;/*Display the Specials menu on Diagnostic Screen.*/
}



void DebugMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the debug menu.                                               */
/*                                                                         */
/***************************************************************************/
{
   DebugPasswordFlag = TRUE;    /* This will allow display in DIAG menu    */
   DebugBase = TRUE;            /* Default to number base 16 (hexidecimal) */
   DebugBytes = TRUE;           /* Default to 2 bytes                      */
   BransonFunctionFlag = TRUE; /*Display the Specials menu on Diagnostic Screen.*/
}



void RestoreDefaults(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the factory defaults menu.  This will display a list of       */
/*  functions, each will set certain groups of values back to factory      */
/*  defaults.  The groups are:                                             */
/*      User I/O - disable most, assign original ones (cycle abort &       */
/*                 display lock), set active hi/lo back to default         */
/*      Actuator settings - ULS, TRS and ground detect switch states       */
/*      FRAM settings - alarm masks, trigger setting, ramps                 */
/*      Printing - print on sample, print on alarm all off                 */
/*      Global - all of the above in one step                              */
/*                                                                         */
/***************************************************************************/
{
   AccessLevel = BRANSON;
}



void FastActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to speed up the communication speed between the 332 and the       */
/*  actuator a/d(~2.4Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.Sclk7890Act = FAST_CLK;  /* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = CLOCK_PHASE;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   FRAMPtr->Sclk7890Act = FAST_CLK;
   FRAMPtr->ClockPhase = CLOCK_PHASE;
}



void SlowActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to slow down the communication speed between the 332 and the      */
/*  actuator a/d(~1.72Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.Sclk7890Act = SLOWSPEED;  /* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = INVERTCLK;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   FRAMPtr->Sclk7890Act = SLOWSPEED;
   FRAMPtr->ClockPhase = INVERTCLK;
}

   

void SlowerActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to slow down the communication speed between the 332 and the      */
/*  actuator a/d(~1.51Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.Sclk7890Act = SLOWERSPEED;/* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = INVERTCLK;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   FRAMPtr->Sclk7890Act = SLOWERSPEED;
   FRAMPtr->ClockPhase = INVERTCLK;
                                             
}



void SelectOldBoard(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user I/O J3-36 and J3-8 selections to be  */
/*  swapped.  The new board swapped the pins and the software (again) was  */
/*  adjusted to handle it.  This puts them back on the original pin.       */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   UpdateHWConfiguration(PC1025SP, TRUE);
   CurrentSetup.SystemControllerFlag = FALSE;
   FRAMPtr->SystemControllerFlag = FALSE;
   StoreEstopHwVersion(ONE_POLE_ESTOP);
}



void SelectNewBoard(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user I/O J3-36 and J3-8 selections to be  */
/*  swapped.  The new board swapped the pins and the software (again) was  */
/*  adjusted to handle it.  This puts them back on the swapped pin.        */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   UpdateHWConfiguration(PC1025DP, TRUE);
   CurrentSetup.SystemControllerFlag = TRUE;
   FRAMPtr->SystemControllerFlag = TRUE;
   StoreEstopHwVersion(TWO_POLE_ESTOP);
}


void EnablePLCTiming(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the menu option "PLC Control" to be displayed */
/*  in the System Configuration menu right after Handheld.  This feature   */
/*  removes the trigger lost in weld and trigger lost in hold alarms,      */
/*  effectively allowing the start signal to control the weld time.  Once  */
/*  the menu is enabled, it can only be turned off by initializing the FRAM.*/
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.PLCControlMenuFlag = TRUE;
   FRAMPtr->PLCControlMenuFlag = TRUE;
}


void EnableUSEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will configure the system with a US Encoder              */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.USEncoder = TRUE;
   FRAMPtr->USEncoder = TRUE;
}


void EnableMetricEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will configure the system with a Metric Encoder          */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   CurrentSetup.USEncoder = FALSE;
   FRAMPtr->USEncoder = FALSE;
}



void ConfigSBeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user to configure the actuator interface  */
/*  board to run the SBEAM                                                 */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
}



void ConfigAEDSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to an AED  */
/*  with the SBEAM.                                                        */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_AED, LENGTH_4, SIZE3_0);
   EnableMetricEncoder();
}

void ConfigAESSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to an AES  */
/*  with the SBEAM.                                                        */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_AES, LENGTH_4, SIZE3_0);
   EnableMetricEncoder();
}


void ConfigAEFSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to an AEF  */
/*  with the SBEAM.                                                        */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_AEF, LENGTH_4, SIZE3_0);
   EnableMetricEncoder();
}



void ConfigMICROSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the SBEAM and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
   EnableUSEncoder();
}

void ConfigOriginal_MICRO(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the SBEAM and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
   EnableUSEncoder();
}

void Config50mmMICRO(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with 50mm stroke length and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO,LENGTH_50, SIZE_40);
   EnableUSEncoder();
}

void SetSpringRate3(void)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to 3 and save it in   */
/*  FRAM so at power up it can be retrieved.                                */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[33].Ptr = SecretCode[33].Password;
   BUCMenuRAM.MicroHomeForce = FALSE;                                             
   BUCMenuFRAM->MicroHomeForce = FALSE;
   MicroHomeForce = LEAVINGHOMEFORCEMICROLO;   
   RecordAlarm(W8);                                             
}



void SetSpringRate4(void)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to 4 and save it in   */
/*  FRAM so at power up it can be retrieved.                                */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   SecretCode[34].Ptr = SecretCode[34].Password;
   BUCMenuRAM.MicroHomeForce = TRUE;                                             
   BUCMenuFRAM->MicroHomeForce = TRUE;                                             
   MicroHomeForce = LEAVINGHOMEFORCEMICROHI;   
   RecordAlarm(W8);                                             
}



void SetSpringRateMicroFT(UINT8 MicroForce)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to passed value and   */
/*  save it in FRAM so at power up it can be retrieved.                     */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_1200  *BUCMenuFRAM;

   BUCMenuFRAM = ( BUCMENU_1200*) FRAM1200_BUCMENU_START;
   BUCMenuRAM.MicroHomeForce = TRUE;                                             
   BUCMenuFRAM->MicroHomeForce = TRUE;                                             
   MicroHomeForce = MicroForce;   
   RecordAlarm(W8);                                             
}



void SaveCalibration(void)
/***************************************************************************/
/*                                                                         */
/*  This function will save the most recent calibration.                   */
/*                                                                         */
/***************************************************************************/
{
   UpdateCalibDefault();
}



void SetContLevelt(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to t.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_t;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLevelea(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to ea.                        */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_ea;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveld(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to d.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_d;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLevelf(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to f.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_f;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveldepot(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to depot                      */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_t;
   DepotFlag->WasADepot = TRUE;
   DepotFlag->IsADepot = TRUE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveltest(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to test                       */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *FRAMPtr;
   
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->ControlLevel = LEVEL_TEST;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = FRAMPtr->ControlLevel;
   StorePSControlLevel();
}



void ConfigLoadcell(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user to configure the actuator interface  */
/*  board to run the LoadCell                                              */
/*                                                                         */
/***************************************************************************/
{
   //Not supported
}



void SendKeyToWeldMngr(MSG_OPCODE_TYPE Opcode, BOOLEAN State)
{
   WeldMsgOut.lword1 = State;                                      
   WeldMsgOut.common.opcode = Opcode;
   WeldManagerTask::thisPtr->WELDMNGRTaskQ.WriteRetry(0, *((WMGR_MSG_QUEUE_TYPE*) &WeldMsgOut), 50);
}



void DisplayResetMsg(void)
{
   UINT32 OrigKeyMask;

   OrigKeyMask = KeyMask;      /* Don't allow Test key to sneak between */
   KeyMask &= ~TESTKEYMASK;    /* Reset and RunKey */

   RTOS::DelayMs( SECONDS_TO_TICKS( 1 ));

      ClearKeypadBuffer(TRUE);  /* Drop keys pressed while msg on */
      SendFakeKeyPress(RunKey);
      BlankMenuCounter = 1;     /* Don't redisplay current menu before exit */
   KeyMask = OrigKeyMask;
}

void UpdateHWConfiguration(enum MASK1 HWConfig, BOOLEAN Enabled)
{

     if(Enabled)
        HWConfiguration = HWConfiguration | HWConfig;
     else 
        HWConfiguration = HWConfiguration & (~HWConfig);
        
}       

void UpdateSWConfiguration(enum MASK2 SWConfig, BOOLEAN Enabled)
{

     if(Enabled)
        SWConfiguration = SWConfiguration | SWConfig;
     else 
        SWConfiguration = SWConfiguration & (~SWConfig);
        
}

BOOLEAN IsHWConfigured(UINT16 HWType)
/***************************************************************************/
/*Description:                                                             */
/* Checks particular H/W is configured.                                    */
/*Input Parameters:                                                        */
/* HWType- H/W needs to be detected.                                       */
/***************************************************************************/
{
   BOOLEAN IsAvail = FALSE;
   
   switch(HWType)
   {
      case DUPS:
         if(HWConfiguration & DUPS)
            IsAvail = TRUE;
      break;
      case VGA:
         if(HWConfiguration & VGA)
            IsAvail = TRUE;
      break;

      default:
         IsAvail = FALSE;
      break;  
   }
   return(IsAvail);
}


BOOLEAN IsSWConfigured(UINT32 SWType)
/***************************************************************************/
/*Description:                                                             */
/* Checks particular S/W is configured.                                    */
/*Input Parameters:                                                        */
/* HWType- S/W needs to be detected.                                       */
/***************************************************************************/
{
   BOOLEAN IsAvail = FALSE;
   switch(SWType)
   {
      case EC:
         if(SWConfiguration & EC)
            IsAvail = TRUE;
      break;
      
      case CUS:
         if(SWConfiguration & CUS)
            IsAvail = TRUE;
      break;
      
      case WS:
         if(SWConfiguration & WS)
            IsAvail = TRUE;
      break;
      
      case DEPO:
         if(SWConfiguration & DEPO)
            IsAvail = TRUE;
      break;
      
      case V_OL:
         if(SWConfiguration & V_OL)
            IsAvail = TRUE;
      break;
      
      case C_OL:
         if(SWConfiguration & C_OL)
            IsAvail = TRUE;
      break;
      
      case F_OL:
         if(SWConfiguration & F_OL)
            IsAvail = TRUE;
      break;
      
      case P_OL:
         if(SWConfiguration & P_OL)
            IsAvail = TRUE;
      break;
      
      case HE:
         if(SWConfiguration & HE)
            IsAvail = TRUE;
      break;
      
      case ALR:
         if(SWConfiguration & ALR)
            IsAvail = TRUE;
      break;
      
      case VEL:
         if(SWConfiguration & VEL)
            IsAvail = TRUE;
      break;
      
      default:
           IsAvail = FALSE;
      break;
      
   }
   return(IsAvail);
}

void InsertProperUnits(SINT8 text[], enum FORMAT UnitFlag)
/***************************************************************************/
/*                                                                         */
/*  This function will remove the '&' in the passed text string and        */
/*  replace it with the proper units based on the passed UnitFlag and the  */
/*  current units selected (SI or US).  If CurrentSetup.Units equals TRUE  */
/*  then SI units are selected.                                            */
/*  Support for Asian Language provided                                    */
/*  The location where the subsitution started will be returned.           */
/*                                                                         */
/***************************************************************************/
{
   SINT8  *UnitText;
   UINT8  ChrCount;
   SINT16 Index;
   struct var_format_def1 *FormatPtr;
   if (CurrentSetup.Units)
      FormatPtr = &VarFormatTable[UnitFlag].Metric;
   else
      FormatPtr = &VarFormatTable[UnitFlag].English;

   Index = 0;
   
      while (text[Index] && (text[Index] != '&'))
         Index++;

      if (text[Index] == '&')
      {
         UnitText = FormatPtr->Units;

         for (ChrCount=0; (ChrCount < 4) && (text[Index] == '&'); ChrCount++)
            text[Index++] = *UnitText++;

      }
}

void DisplayMenu(MENU list[])
/***************************************************************************/
/*                                                                         */
/*  This function will scan through the structures which define the menus. */
/*  It will decide which entries should appear on the display at this      */
/*  time.  A list will be created which is valid for this pass only.  It   */
/*  is the intent that this function be reentrant and any sub-menu will    */
/*  simply call this function again.                                       */
/*                                                                         */
/*  The first set of switch statements will determine which things will    */
/*  appear in the menu list.  The second set will actually deal with       */
/*  putting the data and text into the buffer to be displayed.             */
/*                                                                         */
/***************************************************************************/
{
   UINT8    NewKey, i;
   UINT8    ExitFlag;

   UINT16   StartLine;              /* First line to update next pass */
   UINT16   TermStartLine;          /* First line on terminal to update next pass */
   UINT16   SaveDiagFlag;           /* Temp storage */

   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;

   BOOLEAN   DidTest;
   BOOLEAN   KeyPressed;
   UINT8     ExitKey;
   BOOLEAN   JumpMenu;

   MENU      *RestorePrevMenu;  /* Remembers menu displayed before this one */

   CONFIGSETUP *FRAMPtr;         /* Allows saving to FRAM in case of power interruption */

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   MenuCounter++;
   RestorePrevMenu = CurrentlyDisplayedMenu;
   CurrentlyDisplayedMenu = list;   /* Allow other tasks to see which menu this is */
   UpdateLED(OFFLED, OFF);          /* .. Turn off the OFF led */

   for (i=0; i < NUMBER_OF_CODES; i++) {     /* Reset all secret code pointers */
      SecretCode[i].Ptr = SecretCode[i].Password;
   }

   /* AT: if we are in CalibrateForceMenu1 and access level is below maintenance
      while we have passwords on - set access level to maintenance so we won't
      ask for password in the middle of calibration. It seems to be the step all
      calibration procedures go through, so every calibration should be covered. */

   StartLine = 1;    /* Line of display to write next */
   TermStartLine = 1;

   SaveLine1[VF_DEVICE] = 1;
   SaveLine1[TERM_DEVICE] = 1;

   SaveSelectKey1 = 1;
   SaveSingleSelect = 1;

   ExitFlag = FALSE;

   while (ExitFlag != TRUE)   /* Main menu loop */
   {                          /* Enter with StartLine set to next screen */
      if(MenuCounter == 0)    /*  line (1-4) to update, usually 1 */
         MainKeyFlag = FALSE;

      if(BlankMenuCounter > 0)  /* If counter nonzero, don't display menu */
         BlankMenuCounter--;
     
      StartLine = 1;      /* Next pass through update whole screen unless */
      TermStartLine = 1;  /* code processing keys doesn't want to do this. */

      /* Code to take some special action depending on what's in key queue: */

      /* Want to reset the access level to OPERATOR only if the system is */
      /* waiting for a keypress at the main menu.  Must not have a keypress */
      /* available because there are times when system passes through the */
      /* main menu on the way to someplace else and these times we do NOT */
      /* want to reset the access level. */

      /* Also want to throw out left/right arrow keypresses unless there */
      /* are no other keys in the buffer.  This prevents wild scrolling of */
      /* weld results due to accumulated keypresses. */

      do
      {
         KeyPressed = KeyAvailable(TRUE);

        NewKey = GetMsg(TRUE);

      } while (KeyPressed && (NewKey == LeftKey || NewKey == RightKey));

      if (NewKey < FIRSTCONTROLMESSAGE)  /* Process keypresses */
      {
         switch(NewKey)
         {

            case TestKey:
               SaveDiagFlag = DiagFlag;    /* Need to disable Diagnostics */
               DiagFlag = FALSE;           /* if going to Test. */


               JumpMenu = DoTestMode( &ExitKey, &DidTest );
               DiagFlag = SaveDiagFlag;

               if (JumpMenu && MenuCounter > 0)
               {                                 /* Force jump to next menu */
                  MainKeyFlag = TRUE;
                  ExitFlag = TRUE;
               }

               if (JumpMenu && (ExitKey != MainKey)) /* If JumpMenu TRUE will */
               {                                     /* go to Main Menu anyway */
                  SendFakeKeyPress((KEY_CODE_TYPE) ExitKey );
                  BlankMenuCounter = 1;      /* Block display of Main Menu */
               }

               break;
   
            case ResetKey:
               DisplayResetMsg();   /* Will only get this key on run screen */
               break;

                
            default:
               Beep(ERRORBEEP);
               break;
         } /* End of switch(NewKey) */
      }
      else
      {
         ProcessControlMessage(NewKey);
      }
      RTOS::DelayMs(1);
   } /* End of while ExitFlag != TRUE */

   CurrentlyDisplayedMenu = RestorePrevMenu ;
   MenuCounter--;
}

/****************************************************************************/
/*                                                                          */
/* Converts the given value into an ASCII string showing a variable of the  */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* This function, unlike FormatNumber(), performs conversion to external    */
/* units.                                                                   */
/*                                                                          */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    format - Format to display value in (PERCENT, DISTANCE, etc.)         */
/*    String[] - Output string                                              */
/*    MaxLen - Max character space in String[] (not incl. terminator)       */
/*    Metric - TRUE if value should be displayed in metric units            */
/*                                                                          */
/****************************************************************************/
void FormatVariables( SINT32 Value, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric )
{
   SINT32 Number;
   
   Number = ConvertInternalExternal( Value, format, Metric );
   if (Metric && (format == DISTANCE) && CurrentSetup.Metric3Flag)
   {
      if (Number < CHANGEDISTFORMATVAL)
      {
         Number = ConvertInternalExternal( Value, DISTANCE3, Metric );
         FormatNums( Number, DISTANCE3, String, MaxLen, Metric );
      }
      else
         FormatNums( Number, format, String, MaxLen, Metric );
   }
   else 
      FormatNums( Number, format, String, MaxLen, Metric );

}

/****************************************************************************/
/*                                                                          */
/* Converts the given number into an ASCII string showing a variable of the */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* Conversion to displayable units is assumed to have been done.            */
/* Support for Asian Language provided where each char is of two bytes      */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    format - Format to display value in (PERCENT, DISTANCE, etc.)         */
/*    String[] - Output string                                              */
/*    MaxLen - Max character space in String[] (not incl. terminator)       */
/*    Metric - TRUE if value should be displayed using metric units         */
/*                                                                          */
/****************************************************************************/
void FormatNums( SINT32 Number, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric )
{
   UINT8 ChrCount, Digits;
   SINT8 *cptr;
   SINT8 SignChr;
   struct var_format_def1 *FormatPtr;
  
   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   if (Number < 0)
   {
      Number = -Number;
      SignChr = '-';
   }
   else
      SignChr = '+';

   cptr = String;
   for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
      *cptr++ = ' ';

   cptr = &String[ChrCount-1];      /* Point to last chr in string */
   Digits = FormatPtr->RightDigits;

   if (Digits)          /* If necessary, write digits to right of decimal */
   {
      while (ChrCount && Digits)
      {
         *cptr-- = (Number%10) + '0';
         ChrCount--;
         Number /= 10;
         Digits--;
      }
      if (ChrCount)
      {
         *cptr-- = '.';
         ChrCount--;
      }
   }

   if (ChrCount)     /* Write left part if space in string */
   {
      Digits = FormatPtr->LeftDigits; /* Max # of digits to write this step */
      if (Digits > ChrCount)  /* Don't write more than there's space for */
         Digits = ChrCount;
      if (Number)
      {
         while (Digits && Number)
         {
            *cptr-- = (Number%10) + '0';
            ChrCount--;
            Number /= 10;
            Digits--;
         }
      }
      else
      {
         *cptr-- = '0';   /* Always one chr left of decimal point */
         ChrCount--;
      }
   }

   if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
   {
      *cptr = SignChr;     /* Add sign */
   }  
}



/****************************************************************************/
/*                                                                          */
/* Converts the value passed in, which is in the specified format, into a   */
/* form that can be displayed.  This may involve scaling by factors of ten  */
/* or unit conversions.  The end result is a SINT32 that can be converted  '*/
/* to ASCII and displayed, with a decimal point placed as determined by the */
/* format.                                                                  */
/*                                                                          */
/****************************************************************************/
SINT32 ConvertInternalExternal( SINT32 Value, enum FORMAT format,
 BOOLEAN Metric )
{
   SINT32 RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   /* Perform conversion from stored units to displayed units */

   if (Value < 0)
      RetVal = 0 - ((((0-Value)*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv);
   else
      RetVal = ((Value*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv;

   return( RetVal );
}



/****************************************************************************/
/*                                                                          */
/* Converts the value passed in to internal storage units.  Passed number   */
/* is binary form of what was entered or displayed, minus a decimal point.  */
/* Conversion may scale by factors of ten or convert units, but end result '*/
/* is suitable for storage.                                                 */
/*                                                                          */
/****************************************************************************/
SINT32 ConvertExternalInternal( SINT32 Number, enum FORMAT format,
 BOOLEAN Metric )
{
   SINT32 RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   /* Perform conversion from displayed units to stored units */

   if (Number < 0)
      RetVal = 0-((((0-Number) * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult));
   else
      RetVal = ((Number * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult);

   return( RetVal );
}

void ShowEstopMessageOn(void)
{
   Beep(ESTOPBEEP);
}



void ShowEstopMessageOff(void)
{
  
}



/****************************************************************************/
/*                                                                          */
/* Returns a pointer to the menu list used to generate the menu currently   */
/* being shown by DisplayMenu().  The pointer returned has the same value   */
/* as was passed to DisplayMenu() to put the menu on the screen.            */
/*                                                                          */
/* Caveats: This function only works when the current screen text was put   */
/*          there by DisplayMenu().  If GetCurrentMenu() is called during   */
/*          Horn Down, Test, or some other mode that does its own display   */
/*          output, GetCurrentMenu() will return a pointer to the last menu */
/*          output by DisplayMenu(), not the one currently on the screen.   */
/*                                                                          */
/****************************************************************************/
MENU *GetCurrentMenu(void)
{
   return( CurrentlyDisplayedMenu );                                            
}




void VFAlarmOn(void)
/****************************************************************************/
/*                                                                          */
/* Initiates blinking of the reset LED to indicate that there is an alarm.  */
/*                                                                          */
/****************************************************************************/
{
   UpdateLED(RESETLED, ON);           /* Turn Reset led on */
}

void VFAlarmOff(void)
/****************************************************************************/
/*                                                                          */
/* Stops blinking of the ALARM message in the upper left corner of the      */
/* screen.                                                                  */
/*                                                                          */
/****************************************************************************/
{
   UpdateLED(RESETLED, OFF);
}




void AlarmOn(void)
{
   VFAlarmOn();
}



void AlarmOff(void)
{
   VFAlarmOff();
}

void ConfigMaxMinValues()
{
   SetMaxMinValues();
}

void LowerPressureValveOn(void)
{
   CONFIGSETUP *FRAMPtr;
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->LowerFlowValveFlag = TRUE;
   CurrentSetup.LowerFlowValveFlag = FRAMPtr->LowerFlowValveFlag;
}

void LowerPressureValveOff(void)
{
   CONFIGSETUP *FRAMPtr;
   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   FRAMPtr->LowerFlowValveFlag = FALSE;
   CurrentSetup.LowerFlowValveFlag = FRAMPtr->LowerFlowValveFlag;
}

