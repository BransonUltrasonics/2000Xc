/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/pr_label.cpp_v   1.6   28 Nov 2014 07:39:00   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/pr_label.cpp_v  $
 * 
 *    Rev 1.6   28 Nov 2014 07:39:00   rjamloki
 * changed to remove warning "unused variable".
 * 
 *    Rev 1.5   11 Jun 2014 12:00:34   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.4   21 May 2014 03:34:42   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.3   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: pr_label.c

 ---------------------------- DESCRIPTION -----------------------------------
*/

#include "string.h"
#include "preset.h"
#include "util.h"
#include "portable.h"
#include "graphs.h"

#define LABELVAL 12
#define METRICRESOLUTION  10000
#define ENGRESOLUTION  1000
#define STARTBOTTOMGRAPH "-0.100"
#define LONGWELDTIME  20000
#define LONGSTARTGRAPH "0.000"
#define MINUSSTR  "-"

/**-------------------------LOCAL DATA------------------------------------**/

UINT32 UIValue;
SINT32 tempval;
UINT32 UIMax = 0, UIMin = 0;
SINT8 CVal[10], Minus[1];
SINT8 ComboVal[LABELVAL];


/**--------------------------------------------------------------**
 ** Constant global array to hold information for the  vertical  **
 ** labels. The first array subscript is the  number of labels   **
 ** available. The following items are the maximum labels, then  ** 
 ** the minimum labels follow. This information is held for each **
 ** possible graph.                                              **
 **--------------------------------------------------------------**/


const UINT32 UILabels[LABELNUM][LABELSIZE] =
{

/*  number of labels, 1st label_high, 2nd label_high...label_low..*/
/*0  AMPLITUDE        */   { 5,   200,    400,    600,    800,   1000,       0, 0, 0, 0, 0},          
/*1  POWER            */   { 6,   100,    200,    400,    800,   1000,    1200, 0, 0, 0,  0, 0, 0},   
/*2 FREQ 60/40/30/20/15k*/ { 5, 15375,  20450,  30750,  40900,   61500,   14625,   19450, 29250, 38900, 58500}, 
/*3  COLLAPSE  USCS   */   { 7,   100,    200,    600,   1200,   2400,    6000,   10000, 0, 0, 0, 0, 0, 0, 0},  
/*4  FORCE     Pound  */   { 7,    40,    100,    200,    400,    800,    1000,   1300, 0, 0, 0, 0, 0, 0,0},  
/*5  VELOCITY  USCS   */   { 2,  3000,   6000,      0,      0},                                                      
/*6  COLLAPSE  Metric */   { 7,  2500,   5000,  15000,  30000,  60000,  150000,  250000, 0, 0, 0, 0, 0, 0, 0},  
/*7  FORCE     Newton */   { 7,   200,    400,    800,   1600,   3200,    4400,  5500, 0, 0, 0, 0, 0, 0, 0},  
/*8  VELOCITY  Metric */   { 2,100000, 150000,      0,      0},
/*9  ABSOLUTE  USCS   */   { 7,  2500,   5000,   7500,  10000,  20000,   40000,   60000, 0, 0, 0, 0, 0, 0, 0},  
/*10 ABSOLUTE Metric  */   { 7, 60000, 130000, 190000, 250000, 500000, 1000000, 1500000, 0, 0, 0, 0, 0, 0, 0},
/*11 HORN SCAN (use force for debug) */ { 6,    40,    100,    200,    400,    800,    1000, 0, 0, 0, 0, 0, 0}  
};



/**--------------------------------------------------------**
 ** This function searches for the maximum and the minimum **
 ** label of the choosen graph.                            **
 ** IN: index of the choosen graph c_which_graph           **
 ** index of the maximum value of the input value array    **
 ** ui_number pointer to maximum and minimum label         **
 ** p_maxlabel,p_minlabel.                                 **
 ** OUT: maxlabel                                          **
 **--------------------------------------------------------**/
void   GetMaxMinLabel(UINT16 CWhichGraph,
                      SINT32 *Data,
                      UINT16 UINumber,
                      UINT32 *PMaxlabel,
                      UINT32 *PMinlabel)
{
   UINT32 UIMaxIndex, *PUIValue;
   SINT32 UIMaxval = 0;
   UINT16 count;
 
   /* find maximum value of data */
   for(count = 0; count < UINumber; count++)
      if(Data[count] > UIMaxval) UIMaxval = Data[count];

   /* convert tenths of pounds to pounds for label selection */
   if(CWhichGraph == FORCELBGRAPH)
      UIMaxval = (UIMaxval + 5) / 10;

   /*-- find the appropriate vert. label --*/
   UIMaxIndex = UILabels[CWhichGraph][0];
   PUIValue = (UINT32 *)UILabels[CWhichGraph];

   for(count = 1; count <= UIMaxIndex; count++){
      UIMax = *(PUIValue + count);
      UIMin = *(PUIValue + UIMaxIndex + count);
      if( UIMaxval <= (SINT32)UIMax) break;
   }

   *PMaxlabel = UIMax;
   *PMinlabel = UIMin;

}

