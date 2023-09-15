/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/util.cpp_v   1.17   Oct 10 2017 14:55:54   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/util.cpp_v  $
 * 
 *    Rev 1.17   Oct 10 2017 14:55:54   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.16   Jun 07 2017 14:18:14   RJamloki
 * remove RemoveExtraSpaces return parameter
 * 
 *    Rev 1.15   12 May 2016 12:14:12   RJamloki
 * function RemoveExtraSpaces updated 2
 * 
 *    Rev 1.14   10 May 2016 16:35:04   RJamloki
 * Change function RemoveExtraSpaces
 * 
 *    Rev 1.11   16 Apr 2015 07:29:38   rjamloki
 * removed redundant functions
 * 
 *    Rev 1.10   26 Sep 2014 03:11:10   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.9   18 Aug 2014 01:47:10   rjamloki
 * Added Numout2 to for non prefixed int to string conversion
 * 
 *    Rev 1.8   28 Jul 2014 12:40:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.7   09 Jul 2014 11:45:34   rjamloki
 * Removed redudant Weld.h inclusion
 * 
 *    Rev 1.6   21 May 2014 10:48:14   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:54:36   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:48   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:56   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:56   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Util                                                        */
/*                                                                          */
/* Filename:    Util.c                                                      */
/*                                                                          */
/* Function Name: Utility function used just about anywhere                 */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-28-95                                          */
/*            Language:   "C"                                               */
/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains general purpose functions.                          */



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define MAXPARAMCHANGED            10
#define MAX_ACCEPT_PRESS          900 /* outside this pressure range we will reduce */
#define MIN_ACCEPT_PRESS          300 /* signal to PV                               */
#define PRESSURE_POINTS             5 /* Number of 1/4 sec points before considered stable */
#define UPDATE_PRESSURE_TOLERANCE   5 /* Tolerance (in tenths of PSI) before stable */
#define NOT_INITIALIZED        0xffff /* Actuator novram has not been written to */

/*------------------------------ INCLUDES ----------------------------------*/

#include "portable.h"
#include "actnvram.h"
#include "preset.h"
#include "string.h"
#include "param.h"
#include "psnvram.h"
#include "spidd.h"
#include "actnvram.h"
#include "menu7a.h"
#include "state.h"
#include "mansensr.h"
#include "digout.h"
#include "rtclock.h"
#include "battram.h"
#include "snsrcalb.h"
#include "menu6.h"
#include "root.h"
#include "weld.h"
#include "util.h"
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

/*----------------------------- GLOBAL DATA --------------------------------*/

SINT16 ForceTableDelta = 0,VelocityTableDelta = 0;
enum  PARAM ParamChanged[MAXPARAMCHANGED];/* Array to hold indexes of param's changed */

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SINT32 DistanceOffset;
extern SINT32 Distance1;
/*-------------------------------- CODE ------------------------------------*/

void strsub(SINT8 string[], SINT8 old, SINT8 newCh)
/***************************************************************************/
/*                                                                         */
/*  This function will replace all 'old' characters in the passed string   */
/*  with the 'new' passed character.                                       */
/*                                                                         */
/***************************************************************************/
{
   SINT16 len, index = 0;

   len = strlen(string);
   while (index <= len) {
      if (string[index] == old) string[index] = newCh;
      index++;
   }
}

void RemoveExtraSpaces(UINT8 string[])
/***************************************************************************/
/*                                                                         */
/*  This function will remove extra spaces in a string leaving only one    */
/*  within a group.  For example:                                          */
/*  "  ABC  DEF     GHIJK  +  112 "  would be replaced with                */
/*  "ABC DEF GHIJK +112"                                                   */
/*                                                                         */
/*  Notes:                                                                 */
/*  1) One special exception.  All spaces between a sign (+/-) and any     */
/*     character will be removed.                                          */
/*  2) The remaining part of the string will be null terminated.           */
/*  3) All leading spaces before the first alpha/numeric character will    */
/*     be eliminated.                                                      */
/*  4) All trailing spaces will be eliminated.                             */
/*                                                                         */
/***************************************************************************/
{
   SINT16 len, SrcIndex = 0, DstIndex = 0;
   UINT16 SpaceFound = TRUE;  /* Setting to TRUE eliminates leading spaces */

   len = strlen((SINT8 *)string);
   while (SrcIndex < len) {
      if (string[SrcIndex] == ' ') {
         if (SpaceFound == TRUE) {
            SrcIndex++;
         }
         else {
            SpaceFound = TRUE;
            string[DstIndex++] = ' ';
         }
      }
      else {
         if ((string[SrcIndex] == '+') || (string[SrcIndex] == '-') ){
            SpaceFound = TRUE;
            string[DstIndex++] = string[SrcIndex++];
         }
         else {
            string[DstIndex++] = string[SrcIndex++];
            SpaceFound = FALSE;
         }
      }
   }
   if (string[DstIndex - 1] == ' ')   /* Check for trailing space */
      string[DstIndex - 1] = 0;
   else
      string[DstIndex] = 0;
}

UINT16 GetPowerSupplyFrequency(void)
/****************************************************************************/   
/*                                                                          */
/* This function will get the power supply frequency from the NOVRAM and    */
/* return the value in hertz (i.e. 19950, 39900).                           */
/*                                                                          */
/****************************************************************************/   
{
   UINT16  Frequency;


   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         Frequency = CENTER15KHZ;
         break;
      case FREQ20KHZ:
         Frequency = CENTER20KHZ;
         break;
      case FREQ30KHZ:
         Frequency = CENTER30KHZ;
         break;
      case FREQ60KHZ:
         Frequency = CENTER60KHZ;
         break;   
      case FREQ40KHZ:
      default:
         Frequency = CENTER40KHZ;
         break;
   }
   return(Frequency);
}


UINT16 GetPowerSupplyFrequencyOffset(void)
/****************************************************************************/   
/*                                                                          */
/* This function will get the power supply frequency from the NOVRAM and    */
/* return the offset value in hertz (i.e. 500 for 20KHz etc                 */
/*                                                                          */
/****************************************************************************/   
{
   UINT16  Frequency;


   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         Frequency = FREQ15_OFF;
         break;
      case FREQ20KHZ:
         Frequency = FREQ20_OFF;
         break;
      case FREQ30KHZ:
         Frequency = FREQ30_OFF;
         break;
      case FREQ60KHZ:
         Frequency = FREQ60_OFF;
         break;   
      case FREQ40KHZ:
      default:
         Frequency = FREQ40_OFF;
         break;
   }
   return(Frequency);
}


/*---------------------------------------------------------*/
/* This function takes a  value that is stored  in integer */
/* form representing inches and converts it into a float   */
/* value representing millimeter for display               */
/*---------------------------------------------------------*/
double InchToMm(SINT32 IInches)
{
   double FVal;
    FVal = ((double)IInches * 25.4)/10000;
    return(FVal);
}
/* conversion of a SINT32 lbs-force value in a SINT32 Newton value*/



/*----------------------------------------------------------*/
/* This function takes a  value that is stored  in integer  */
/* form representing lbs-force and converts it into a float */
/* value representing Newton for display.  Input value is   */
/* in tenths of pounds.                                     */
/*----------------------------------------------------------*/
double PoundToNewton(SINT32 ILbs)
{
    double IVal;
    IVal = (double)(((ILbs * 4448) + 5000)/10000);
    return(IVal);
}

void FormatIntToAscii(SINT8 Str[], UINT8 length, UINT16 val)
{
   UINT8 i;
   for (i = 0; i < length - 1; i++)
      Str[i] = FILLCHAR;
   Str[i] = 0x00;
   while(val != 0)        
   {
      Str[--i] = (val%10) + 0x30;
      val /= 10;
   }
}

SINT8 * TrimLeadingBlanks(SINT8 Str_temp[])
/****************************************************************************/
/*Description:-                                                             */
/* Trim the leading spaces in the Input string and returns string pointer   */
/****************************************************************************/
{
   SINT8 *StrPtr= NULL_PTR;
   UINT16 Index;

   for(Index=0; Index < strlen(Str_temp); Index++)
   {
      if(Str_temp[Index]!=' ')
      {
         StrPtr = &Str_temp[Index]; 
         break;
      }
   }

   return(StrPtr); 
}

SINT32 GetMaxStrokeLength(void)
/****************************************************************************/   
/*                                                                          */
/*  This function will return the maximum stroke length (in inches) for the */
/*  value returned by GetStrokeLength().  Returned value is scaled up by    */
/*  10000.                                                                  */
/*                                                                          */
/****************************************************************************/   
{
   UINT16 Stroke;
   SINT32 RetVal;

   Stroke = GetStrokeLength();
   switch (Stroke) {
      case CUSTOMLEN:
         RetVal = 99999;         /* Keep it at 5 digits so it fits */
         break;

      case LENGTH_4:
         RetVal = 40000;
         break;

      case LENGTH_5:
         RetVal = 50000;
         break;

      case LENGTH_6:
         RetVal = 60000;
         break;

      case LENGTH_2:
         RetVal = 20000;
         break;
     
      case LENGTH_8:
         RetVal = 80000;
         break;

      case LENGTH_70:
         RetVal = 27559;
         break;

      case LENGTH_80:
         RetVal = 31496;
         break;

      case LENGTH_100:
         RetVal = 39370;
         break;

      case LENGTH_125:
         RetVal = 49212;
         break;

     /* case LENGTH_160:
         RetVal = 62992;
         break;*/

      case LENGTH_50:
         RetVal = 19685;
         break;

      case LENGTH_75:
         RetVal = 29527;
         break;

      default:
         RetVal = 40000;
         break;
   }
   return(RetVal);
}

void UpdateDistanceOffset(void)
/****************************************************************************/   
/*                                                                          */
/* This function will update distance offset correction factor which is used*/
/* in the SetPV function based on the part contact distance.  This distance */
/* offset is an estimate which results in aprox. 5.50  to 6.00 lbs/in.      */
/* and approx. three times greater for 15kHz                                */
/* depending on rounding at any given distance.                             */
/*                                                                          */
/* 1280 is added (or subtracted) to aid in rounding.  It's slightly more    */
/* than half the shift value of 2048 (shift 11).                            */
/*                                                                          */
/* This results in a correction of (+ for pos offset, - for neg offset):    */
/*                                                                          */
/*   0.5000"   3 lbs      2.0000"   11 lbs      3.5000"   19 lbs            */
/*   1.0000"   6 lbs      2.5000"   14 lbs      4.0000"   22 lbs            */
/*   1.5000"   8 lbs      3.0000"   17 lbs      4.5000"   25 lbs            */
/*                                                                          */
/*  For 15kHz                                                               */
/* This results in a correction of (+ for pos offset, - for neg offset):    */
/*                                                                          */
/*   0.5000"   7 lbs      2.0000"   29 lbs      3.5000"   51 lbs            */
/*   1.0000"  15 lbs      2.5000"   37 lbs      4.0000"   59 lbs            */
/*   1.5000"  22 lbs      3.0000"   44 lbs      4.5000"   66 lbs            */
/*                                                                          */
/*                                                                          */
/****************************************************************************/   
{
   SINT32 Temp1;
   
   Temp1 = Distance1 - NVR.CalStrokeLen;
   if (CurrentSetup.PSFreq == FREQ15KHZ)
   {
      if (Temp1 > 0) {
         DistanceOffset = ((Temp1 + (Temp1 >>1) + 640) >> 10); /* Offset is positive */
      }
      else {
         DistanceOffset = ((Temp1 - (Temp1 >>1) - 640) >> 10); /* Offset is negative */
      } 
   }   
   else  /* other than 15kHz */
   {
      if (Temp1 > 0) {
         DistanceOffset = ((Temp1 + (Temp1 >>3) + 1280) >> 11); /* Offset is positive */
      }
      else {
         DistanceOffset = ((Temp1 - (Temp1 >>3) - 1280) >> 11); /* Offset is negative */
      }   
   }  
}

void Numout(UINT32 Value, UINT8 Base, UINT8 LC, STR Ptr[], UINT8 Width)
/*****************************************************************************/
/*                                                                           */
/*  ABSTRACT                                                                 */
/*  --------                                                                 */
/*  This function converts a number from binary form to an ASCII string for  */
/*  display or printing.                                                     */
/*                                                                           */
/*  PARAMETERS                                                               */
/*  ----------                                                               */
/*     Value   The number whose ASCII representation is desired.             */
/*     Base    An integer between 2 and 16, inclusive, specifying in what    */
/*             number base 'Value' is to be interpreted.                     */
/*     LC      (Leading Character): Leading zeroes will be designated by     */
/*             'LC', which should be an ASCII character.                     */
/*     Ptr     The address of the buffer of at least 'Width' bytes, into     */
/*             which the ASCII representation is placed.                     */
/*     Width   The number of character positions desired in the ASCII format.*/
/*                                                                           */
/*  DESCRIPTION                                                              */
/*  -----------                                                              */
/*  If the 'Value' is too large to be represented in 'Width' characters of   */
/*  the chosen 'Base', then only the least significant digits will be        */
/*  represented.                                                             */
/*                                                                           */
/*  There is no error checking.  Input values must conform to the restraints:*/
/*             Base > 1 and Base < 17                                        */
/*             Width > 0                                                     */
/*                                                                           */
/*****************************************************************************/
{
   STR   Digits[] = "0123456789ABCDEF";
   UINT8 i;
   
   for (i = 1; i <= Width; i++) {
      Ptr[Width - i] = Digits[Value % Base];
      Value /= Base;
   }
   i = 0;
   while ((Ptr[i] == '0') && (i < Width-1)) {
      Ptr[i] = LC;
      i++;
   }
}

SINT32 Numout2(UINT32 Value, UINT8 Base, STR Ptr[], UINT8 Width)
/*****************************************************************************/
/*                                                                           */
/*  ABSTRACT                                                                 */
/*  --------                                                                 */
/*  This function converts a number from binary form to an ASCII string for  */
/*  display or printing without appending leading characters.                */
/*                                                                           */
/*  PARAMETERS                                                               */
/*  ----------                                                               */
/*     Value   The number whose ASCII representation is desired.             */
/*     Base    An integer between 2 and 16, inclusive, specifying in what    */
/*             number base 'Value' is to be interpreted.                     */
/*     Ptr     The address of the buffer of at least 'Width' bytes, into     */
/*             which the ASCII representation is placed.                     */
/*     Width   The number of character positions desired in the ASCII format.*/
/*																			 */
/*     Return  The number of digits in formatted data						 */
/*     																		 */
/*                                                                           */
/*  DESCRIPTION                                                              */
/*  -----------                                                              */
/*  If the 'Value' is too large to be represented in 'Width' characters of   */
/*  the chosen 'Base', then only the least significant digits will be        */
/*  represented.                                                             */
/*                                                                           */
/*  There is no error checking.  Input values must conform to the restraints:*/
/*             Base > 1 and Base < 17                                        */
/*             Width > 0                                                     */
/*                                                                           */
/*****************************************************************************/
{
   STR Digits[] = "0123456789ABCDEF";
   UINT8 i;
   BOOLEAN ExitFlag = FALSE;
   SINT32 RetVal = 0, NumDigits = 0, Temp = Value;
   for (i = 1; ((i <= Width) && (ExitFlag == FALSE)); i++) {
	  NumDigits++;
	  Temp /= Base;
	  RetVal++;
	  if(Temp == 0)
		  ExitFlag = TRUE;
   }

   for (i = 1; (i <= RetVal); i++) {
	   Ptr[RetVal - i] = Digits[Value % Base];
	   Value /= Base;
   }

   return RetVal;
}

BOOLEAN AtLeastVersion806(void)
/****************************************************************************/     
/*                                                                          */
/* This function will return true when the current software version is 8.06 */
/* or above.                                                                */
/*                                                                          */
/* Inputs: NVR.PSVersion - Software Version stored in the actuator          */
/*                                                                          */
/****************************************************************************/   
{
BOOLEAN Version806 = TRUE;

   if((NVR.PSVersion < 806) || (NVR.PSVersion >= NOT_INITIALIZED)) 
      Version806 = FALSE;
   return(Version806);
}   



void ConfigureAed(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as an aed, with 3" diameter cylinder */
/*  and 4" stroke.  It will set the actuator serial number to "BUCMMDDYY".  */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_AED, LENGTH_4, SIZE3_0);
}
void ConfigureDummy(void)
/****************************************************************************/
/*                                                                          */
/*  This function is called from the main menu as a hidden function. It     */
/*  is a dummy place holder for future.                                                                        */
/****************************************************************************/
{

}



void ConfigureAef(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as an aef, with 3" diameter cylinder */
/*  and 4" stroke.  It will set the actuator serial number to "BUCMMDDYY".  */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_AEF, LENGTH_4, SIZE3_0);
}



void ConfigureMicro(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as a MICRO with 40 mm diameter       */
/*  cylinder and 2" stroke.  It will set the actuator serial number to      */
/*  "BUCMMDDYY".                                                            */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
}



void ConfigureActuatorBoard(UINT16 ActType, UINT16 Stroke, UINT16 Cylinder)
/****************************************************************************/     
/*                                                                          */
/*  This function does the real work for the three functions above.         */
/*                                                                          */
/*  Parameters: ActType  - NVR_AED, NVR_AEF, NVR_AES or NVR_MICRO                    */
/*              Stroke   - LENGTH_2 or LENGTH_4                             */
/*              Cylinder - SIZE3_0 or SIZE_40                               */
/*                                                                          */
/*  On Exit :   Entire contents of actuator novram rewritten                */
/*              Serial number changed to "BUCmmddyy*"                       */
/*                                                                          */
/****************************************************************************/     
{
   CONFIGSETUP *FRAMPtr;
   STR         SerialNumber[] = "BUC      ";
   RTCTime         RTCCal;
   UINT16      i;

   FRAMPtr = (CONFIGSETUP *) FRAM1200_CONFIG_START;
   if(ActuatorPresent == TRUE)//power up faster without Act
   {
	   TestWriteToNvram();             /* Erase everything currently in Novram */
	   TestReadFromNvram();
   }
/* Write the actuator type */
   FRAMPtr->Actuator = ActType;
   SetActId(ActType);

/* Now write the stroke length */
   FRAMPtr->StrokeLen = Stroke;
   SetStrokeLength(FRAMPtr->StrokeLen);  
   SetDefStrokeLength(FRAMPtr->StrokeLen);  

/* Now write the cylinder diameter */
   FRAMPtr->CylinDiameter = Cylinder;
   SetCylSize(FRAMPtr->CylinDiameter);     
   SetDefCylSize(FRAMPtr->CylinDiameter);     

/* Now create and then write a default serial number */
   RTClock::GetCurrentTime(&RTCCal);     /* Get date when calibration complete */
   Numout((UINT32)RTCCal.Century_Month, 10, '0', &SerialNumber[3], 2);
   Numout((UINT32)RTCCal.Day, 10, '0', &SerialNumber[5], 2);
   Numout((UINT32)RTCCal.Years, 10, '0', &SerialNumber[7], 2);
   SerialNumber[9] = '*';
   SetSerNum(SerialNumber);
   SetDefSerNum((UINT8 *)SerialNumber);

/* Now put new serial number in current setup and FRAM */
   for (i=0; i<MAXSERIALNUM; i++) {
      FRAMPtr->ActSerialNumber[i] = SerialNumber[i];
      CurrentSetup.ActSerialNumber[i] = SerialNumber[i];
   }
/* Note: The CurrentSetup.ActSerialNumber member is larger than MAXSERIALNUM */
/*       allowing a NULL terminator to be added at location MAXSERIALNUM.    */

   if(FRAMPtr->Actuator==NVR_MICRO)
   {
      if(FRAMPtr->StrokeLen == LENGTH_50)//2000X micro std prod
         SetEncoderType(ENCODER_ENGLISH);
   }
   FRAMPtr->ActSerialNumber[i] = NULL;
   CurrentSetup.ActSerialNumber[i] = NULL;
   
   GetSerialNumbers();
   BuildVelocityTable();
   SetDefCalSysPressure((SINT16)LOW_PRESSURE);
   SetDefCalStrokeLength(DEF_CAL_LENGTH);
   SetDefPressure(); 
   SetDefLoadCell();
   SetDefForce();

   NvrCopyDeftoNon();   /* copy actuator def novram settings to working novram settings */
   UpdateNVRSpringRate(); 
   SetPSVersionNVR();
   BuildDefaultSpringRate(); /* update Home Offset must */
}



BOOLEAN IsConfiguredActuatorForceGauge(BOOLEAN AED_LC, BOOLEAN AEF_LC, BOOLEAN AED_SB, BOOLEAN AEF_SB)
{
   BOOLEAN ret;
   if ( (NVR.ActId == NVR_AED) ||(NVR.ActId == NVR_AES) || (NVR.ActId == NVR_MICRO) || (NVR.ActId == NVR_MICROC))
      {
      if (NVR.ForceGauge == SBEAM)
         ret = AED_SB;
      else
         ret = AED_LC;
      }
   else
      {
      if (NVR.ForceGauge == SBEAM)
         ret = AEF_SB;
      else
         ret = AEF_LC;
      }
   return ret;
}
