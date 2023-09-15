/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/util.h_v   1.12   Jun 07 2017 14:21:22   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/util.h_v  $
 * 
 *    Rev 1.12   Jun 07 2017 14:21:22   RJamloki
 * remove RemoveExtraSpaces return parameter
 * 
 *    Rev 1.11   10 May 2016 16:46:42   RJamloki
 * Change function RemoveExtraSpaces
 * 
 *    Rev 1.8   16 Apr 2015 07:35:24   rjamloki
 * Removed unused functions declarations
 * 
 *    Rev 1.7   26 Sep 2014 02:59:52   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.6   18 Aug 2014 01:51:54   rjamloki
 * Added NumOut2 declaration
 * 
 *    Rev 1.5   21 May 2014 10:49:18   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:32   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:49:38   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Util                                                        */
/*                                                                          */
/* Filename:    Util.h                                                      */
/*                                                                          */
/* Function Name: Function prototypes for util.c                            */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-28-95                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/


/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains the function prototypes for utl.c.                  */


#include "preset.h"

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void   strupr(SINT8 string[], SINT16 length);
void   strctr(SINT8 string1[], SINT8 string2[], SINT16 size);
void   strnset(SINT8 string[], SINT8 text, SINT16 size);
void   strsub(SINT8 string[], SINT8 old, SINT8 newstr);
void   RemoveExtraSpaces(UINT8 string[]);
void   MoveToCurrentPreset(SETUPS_Ver1200 *Pt1);
enum   PARAM GetParamChanged(void);
UINT16 GetPowerSupplyFrequency(void);
UINT16 GetPowerSupplyFrequencyOffset(void);
void   PutParamChanged(enum PARAM NewID);
double  PoundToNewton(SINT32 ILbs);
double  InchToMm(SINT32 IInches);
UINT16 myatoi(SINT8 s[]);
void   GetModelNumber(SINT8 Model[]);
void   GetPSInfo(SINT8 PSInfoStr[]);
void   GetCntrlLevel(SINT8 CntrlLevel[]);
SINT32 GetMaxStrokeLength(void);
void UpdateDistanceOffset(void);
BOOLEAN CheckPressure( UINT16 *TestPresFlag, UINT16 PressureValue );
void Numout(UINT32 Value, UINT8 Base, UINT8 LC, STR Ptr[], UINT8 Width);
SINT32 Numout2(UINT32 Value, UINT8 Base, STR Ptr[], UINT8 Width);
BOOLEAN AtLeastVersion806(void);
void ConfigureAed(void);
void ConfigureAef(void);
void ConfigureDummy(void);
void ConfigureActuatorBoard(UINT16 ActType, UINT16 Stroke, UINT16 Cylinder);
BOOLEAN IsConfiguredActuatorForceGauge(BOOLEAN AED_LC, BOOLEAN AEF_LC, BOOLEAN AED_SB, BOOLEAN AEF_SB);
