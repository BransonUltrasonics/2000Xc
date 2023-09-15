/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/1MS_DATA.cpp_v   1.10   28 Jul 2014 12:31:42   rjamloki  $ */
/******************************************************************************/ 
/*                                                                            */
/*                                                                            */
/*     Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation        */
/*     Copying of this software is expressly forbidden, without the prior     */
/*     written consent of Branson Ultrasonics Corporation.                    */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/**************************                         ***************************/
/*******************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/1MS_DATA.cpp_v  $
 * 
 *    Rev 1.10   28 Jul 2014 12:31:42   rjamloki
 * Changes to collect Amplitude points during horn scan
 * 
 *    Rev 1.9   09 Jul 2014 10:27:14   rjamloki
 * Menu4.h is removed
 * 
 *    Rev 1.8   11 Jun 2014 11:17:18   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   21 May 2014 10:47:44   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.6   21 May 2014 02:49:26   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.5   14 Apr 2014 09:52:02   rjamloki
 * Removed QSMMap pointer
 * 
 *    Rev 1.4   05 Mar 2014 13:56:14   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:28   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:16   rjamloki
 * Header Fix.
 *
 *
 *******************************************************************************/

#include "qdef.h"
#include "preset.h"
#include "weld_obj.h"
#include "state.h"
#include "util.h"
#include "graphs.h"
#include "dups_api.h"
#include "portable.h"
#include "ready.h"
#include "WeldManagerTask.h"

//#define TEST_DATA 1
#define MAXSAMPLE   400
UINT32 UIWeldtime;
/*---------------------------- EXTERNAL INFO -------------------------------*/

extern UINT16    GraphCurrentlySelected;


/*---------------------------- GLOBAL DATA ---------------------------------*/

WELD_OBJECT *MsPointer;
SINT32  DistTime[MAX_WELD_SAMPLES];
SINT32  TempDistTime;
UINT16  WeldDataCount;
SINT32  val1[MAX_WELD_SAMPLES];
SINT32  val2[MAX_WELD_SAMPLES];
SINT32  val3[MAX_WELD_SAMPLES];
BOOLEAN CheckCollection = TRUE;    /* TRUE: data copied to val array */
UINT16  GreaterPt;
SINT32  ForceDigValue = DIGITALFORCEVALUE;

/**-------------------------------------------------------------------------**
 ** For the PC version the array val[MAX_WELD_SAMPLES] is filled with test  **
 ** values and are recalibrated, if not input units (in,lb) are to be used. **                                                  
 **-------------------------------------------------------------------------**/
void SetupVals( enum WHICHGRAPH GraphSelected, SINT32 *Data )
{
  UINT16  DiffCt = 0;         /*-- start point in circular buffer         --*/
  UINT16  InsertFakePt = 0;   /*-- insert fake point for peak power       --*/
  UINT16  count = 0;

  UINT16  TempCopyPts = 0;    /*-- All these Temp variable is simply for  --*/
  UINT16  TempNewPreCt = 0;   /*-- faster processing. Accessing MsPOinter --*/
  SINT32  TempActTriggerDistance = 0;/*-- in a for loop uses much more time.     --*/
  SINT32  TempConvertVal = 0;
  UINT16  TempPeakPower = 0;         
  double  TempIncrementPts = 0;    /*-- number of point to skip collecting--*/
  BOOLEAN TempBufferWrap = 0;      /*-- did the 100ms buffer overflow?    --*/ 
  UINT16  TempPointsUpTillHold = 0;/*-- points up till holdtime           --*/             
  UINT16  TempEndOfSonicCt = 0;    /*-- points un till weldtime           --*/                 

  /*-- Temporary values initialized --*/
  TempCopyPts = MsPointer->CopyPts;
  TempNewPreCt = MsPointer->NewPreCt;
  TempIncrementPts = MsPointer->IncrementPts;
  TempActTriggerDistance = FinalResults.ActualTriggerDistance;
  TempPeakPower = FinalResults.PeakPower;
  TempBufferWrap = MsPointer->BufferWrapFlag;
  TempPointsUpTillHold = MsPointer->PointsUpTillHold;            
  TempEndOfSonicCt = MsPointer->EndOfSonicCt;                  

  /*-- If points before trigger is less than 100ms --*/
  /*-- then we need to pad difference with zeros   --*/

  DiffCt = TempCopyPts - TempNewPreCt;

  CheckCollection = FALSE;
  UIWeldtime = MsPointer->TotalPts;
  WeldDataCount = MsPointer->count;


  switch(GraphSelected)
  {


     case AMPLIGRAPH:          
  
                     /*-- AMPLITUDE IN PERCENTAGE  --*/


      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
           Data[count] = MsPointer->Amp[(count + TempNewPreCt) % TempCopyPts];
        }
      }
      else{
         /*-- pad with zeros --*/
         for(count = 0; count < DiffCt; count++){
            Data[count] = 0;
         }
       
         for(count = DiffCt; count < TempCopyPts; count++){
           Data[count] = MsPointer->Amp[count - DiffCt];
         }
       }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Amp[count];
      }

      break;





    case POWGRAPH:

                     /*-- POWER IN PERCENTAGE --*/
      

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Power[(count + TempNewPreCt) % TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Power[count - DiffCt];
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Power[count];
      }


      /*-- Check and insert a point on the Peak Power graph      --*/
      /*-- This will assure  that the Peak Power value displayed --*/
      /*-- on the one line data will be in the graph. This is    --*/
      /*-- unorthodox, but I was forced by the powers that be.   --*/

      InsertFakePt = (UINT16)((MsPointer->PeakPowerAtTime + 100) /
                     TempIncrementPts);
      Data[InsertFakePt] = TempPeakPower;
      GreaterPt = TempPeakPower;

      /*-- Make sure no number is greater than the PeakPower --*/
      for(count = 0; count < WeldDataCount; count++){
        if(Data[count] > GreaterPt)
           Data[count] = GreaterPt;
      }

      break;




    case  FREQUGRAPH:

                     /*-- FREQUENCY IN HERTZ --*/
      
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
          for(count = 0; count < TempCopyPts; count++){ 
           Data[count] = MsPointer->Freq[(count + TempNewPreCt) %
                        TempCopyPts];
         }
      }
      else{
         /*-- pad with zeros --*/
         for(count = 0; count < DiffCt; count++){
            Data[count] = 0;
         }

         for(count = DiffCt; count < TempCopyPts; count++){ 
            Data[count] = MsPointer->Freq[count - DiffCt];
          }
      }


       for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Freq[count];
      }
      break;





    case DISTINGRAPH:

      
                  /*-- COLLAPSE DISTANCE IN INCHES --*/

      for(count = 0; count < TempCopyPts; count++){
        Data[count] = 0;
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = (MsPointer->Dist[count] - TempActTriggerDistance);
         if(Data[count] < 0) Data[count] = 0;
      }

      break;



     case FORCELBGRAPH:

           
                     /*-- FORCE IN POUNDS --*/

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){
           Data[count] = MsPointer->Force[(count + TempNewPreCt) % TempCopyPts];
        }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }
        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Force[count - DiffCt];
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] = MsPointer->Force[count];
      }

      /* Change resolution if digital filtering is on */
      if(RunningPreset.DigitalFilterFlag == TRUE){
        DigitalFilterFunction(Data, ForceDigValue);
      }                                   
      break;




    case VELINGRAPH:    
      
                     /*-- VELOCITY IN INCHES PER SECOND --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          DistTime[count] = MsPointer->Dist[(count + TempNewPreCt) %
                            TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           DistTime[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          DistTime[count] = MsPointer->Dist[count - DiffCt];
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
          DistTime[count] = MsPointer->Dist[count];
      }



      for(count = OFFSET3; count <  WeldDataCount; count++){
         TempDistTime = (DistTime[count] - DistTime[count - OFFSET3]);
         if(TempDistTime >= 0)
            Data[count] = ((TempDistTime * VALUEDIV) /
                                (OFFSET3 * RESOLUTION * TempIncrementPts));
         else
            Data[count] = 0;
      }

      Data[0] = Data[1] = Data[2] = Data[3];


      /* Change resolution if digital filtering is on */
      DigitalFilterFunction(Data, ForceDigValue);
      break;




    case DISTMMGRAPH:    
 
                     /*-- COLLAPSE DISTANCE IN MILLIMETERS --*/
      
      for(count = 0; count < TempCopyPts; count++){
        Data[count] = 0;
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         Data[count] =((MsPointer->Dist[count] - TempActTriggerDistance) * 254) / 10;
         if(Data[count] < 0) Data[count] = 0;
      }
      break;



    case FORCENGRAPH:    
                     /*-- FORCE IN NEWTONS --*/
   
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){
          TempConvertVal = MsPointer->Force[(count + TempNewPreCt) %
                           TempCopyPts];
           Data[count] = (SINT32)PoundToNewton(TempConvertVal);
        }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          TempConvertVal = MsPointer->Force[(count - DiffCt)];
          Data[count] = (SINT32)PoundToNewton(TempConvertVal);
         }
      }


      for(count = TempCopyPts; count < WeldDataCount; count++){
         TempConvertVal = MsPointer->Force[count];
         Data[count] = (SINT32)PoundToNewton(TempConvertVal);
      }

      /* Change resolution if digital filtering is on */
      if(RunningPreset.DigitalFilterFlag == TRUE){
         DigitalFilterFunction(Data, ForceDigValue);
      }
      break;




    case VELMMGRAPH:    
                     /*-- VELOCITY IN MILLIMETERS PER SECOND --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          DistTime[count] = ((MsPointer->Dist[(count + TempNewPreCt) %
                              TempCopyPts] * CONV254) / INCLABEL);
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           DistTime[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          DistTime[count] = ((MsPointer->Dist[count - DiffCt] * CONV254) /
                              INCLABEL);
         }
      }


       for(count = TempCopyPts; count < WeldDataCount; count++){
          DistTime[count] = ((MsPointer->Dist[count] * CONV254) / INCLABEL);
       }


      for(count = OFFSET3; count <  WeldDataCount; count++){
         TempDistTime = (DistTime[count] - DistTime[count - OFFSET3]);
         if(TempDistTime >= 0)
            Data[count] = ((TempDistTime * VALUEDIV) /
                                (OFFSET3 * RESOLUTION * TempIncrementPts));
         else
            Data[count] = 0;
      }
      
      Data[0] = Data[1] = Data[2] = Data[3];
      
      /* Change resolution if digital filtering is on */
      DigitalFilterFunction(Data, ForceDigValue);
      break;



    case ABSINGRAPH:

                           /*-- ABSOLUTE DISTANCE IN INCHES --*/

      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Dist[(count + TempNewPreCt) %
                            TempCopyPts];
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = MsPointer->Dist[count - DiffCt];
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         if(MsPointer->Dist[count] > 0)  /* dist is 0 after holdtime */
           Data[count] = MsPointer->Dist[count];
         else
           Data[count] = 0;
      }


      for(count = 0; count < WeldDataCount; count++){
         Data[count] -= (TempActTriggerDistance - 500);
         if(Data[count] < 0)
            Data[count] = 0;
      }


      break;





    case ABSMMGRAPH:    
 
                     /*-- ABSOLUTE DISTANCE IN MILLIMETERS --*/
      
      /*-- Reorder Circular Buffer --*/
      if(TempBufferWrap == TRUE){
        for(count = 0; count < TempCopyPts; count++){ 
          Data[count] = ((MsPointer->Dist[(count + TempNewPreCt) %
                         TempCopyPts] * CONV254) / INCLABEL);
         }
      }
      else{
        /*-- pad with zeros --*/
        for(count = 0; count < DiffCt; count++){
           Data[count] = 0;
        }

        for(count = DiffCt; count < TempCopyPts; count++){ 
          Data[count] = ((MsPointer->Dist[count - DiffCt] * CONV254) /
                              INCLABEL);
         }
      }

      for(count = TempCopyPts; count < WeldDataCount; count++){
         if(MsPointer->Dist[count] > 0)  /* dist is 0 after holdtime */
           Data[count] =((MsPointer->Dist[count] * CONV254) /
                                  INCLABEL);
         else
           Data[count] = 0;

      }
      break;


     case PHASEGRAPH:
     
        for(count = 0; count < DUPS_HORNSCANPOINTS; count++)
           Data[count] = (UINT32)HornScanPhase[count];
        break;   


     case CURRENTGRAPH:
                                  
        for(count = 0; count < DUPS_HORNSCANPOINTS; count++)
           Data[count] = (UINT32)HornScanCurrent[count];
      break;

     case HSAMP_GRAPH:
        for(count = 0; count < DUPS_HORNSCANPOINTS; count++)
        {
           Data[count] = (UINT32)(HornScanAmp[count]);
        }
      break;

    default:
      break;


  }/* switch..*/


    /*-- If digital filtering is ON stop use points up til hold --*/
    /*-- otherwise, use total points collected --*/

    if((GraphSelected == AMPLIGRAPH)   ||
       (GraphSelected == POWGRAPH)     ||
       (GraphSelected == FREQUGRAPH)){
       if((RunningPreset.DigitalFilterFlag == TRUE) &&
          (TempEndOfSonicCt > 0)){
          WeldDataCount = TempEndOfSonicCt;
       }
    }
    else
    if((GraphSelected == FORCELBGRAPH) ||
       (GraphSelected == FORCENGRAPH) ||
       (GraphSelected == VELINGRAPH)  ||
       (GraphSelected == VELMMGRAPH)){

       if((RunningPreset.DigitalFilterFlag == TRUE) &&
          (TempPointsUpTillHold > 0)){
          if((RunningPreset.HoldTimeFlag & BIT0) == FALSE)
            WeldDataCount = TempPointsUpTillHold;  /*-- STOP AT HOLDTIME --*/
          else
            WeldDataCount = TempEndOfSonicCt;
       }
    }


    /*-- Data collected so now you are --*/
    /*-- free to start next cycle      --*/
    CheckCollection = TRUE;



}/* setup_vals(..*/




UINT16 PlotSort( SINT32 *Data, struct STRComp *DataOrder, UINT16 NumSamp )
/**-------------------------------------------------------------------------**
 ** The input array Data has random numbers. These numbers are to be sorted **
 ** by value. The input array is not changed, a new array DataOrder[] holds **
 ** the indices for the row of values. It is built as a double index array  **
 ** with reference to the next higher and the next lower value.             **
 ** OUTPUT: index to maximum value                                          **
 **-------------------------------------------------------------------------**/
{
   SINT32 IVal, IOrder, IOrder1, i;
   SINT8 CFlag;

   /* prep of data*/
   for(i = 0; i < NumSamp; i++)
      DataOrder[i].higher = DataOrder[i].lower = i;

    /* init of sort algorithm*/
   if(Data[0] > Data[1]){
       DataOrder[0].lower = 1;
       DataOrder[1].higher = 0;
   }
   else{
       DataOrder[0].higher = 1;
       DataOrder[1].lower = 0;
   }

    /* start of sort algorithm*/
    IOrder = 0;
    for(IVal = 2; IVal < NumSamp; IVal++)
    {
       CFlag = 0;
       if(Data[IVal] > Data[IOrder]) {
          do{
             if(IOrder == DataOrder[IOrder].higher){
                /* insert at top*/
                DataOrder[IOrder].higher = IVal;
                DataOrder[IVal].lower = IOrder;
                CFlag = 1;
                break;
             }
             IOrder = DataOrder[IOrder].higher;
          } while(Data[IVal] > Data[IOrder]);
       }/* if(Data[IVal] > Data[IOrder])*/
       else{
          do{
             if(IOrder == DataOrder[IOrder].lower){
                /* insert at bottom*/
                DataOrder[IOrder].lower = IVal;
                DataOrder[IVal].higher = IOrder;
                CFlag = 1;
                break;
             }
             IOrder = DataOrder[IOrder].lower;
          } while(Data[IVal] <= Data[IOrder]);
          IOrder = DataOrder[IOrder].higher;
       }
       if(!CFlag){
          /* insert between two values*/
          IOrder1 = DataOrder[IOrder].lower;
          DataOrder[IOrder].lower = IVal;
          DataOrder[IVal].higher = IOrder;
          DataOrder[IOrder1].higher = IVal;
          DataOrder[IVal].lower = IOrder1;
       }
    }

    /* search for maximum value*/
    IVal = 0;
    do{
        IVal = DataOrder[IVal].higher;
    } while(IVal != DataOrder[IVal].higher);

    return(IVal);    /* return index of maximum*/
}


/**-------------------------------------------------------------------------**
 ** The input array has to be recalibrated. 172 dots is the maximum vertical**
 ** dot value which is equal to the maximum vertical label value.           **
 ** IN: maximum label, minimum label                                        **
 **-------------------------------------------------------------------------**/
void RecalibVal( SINT32 *Data, UINT16 CurrentGraph, UINT32 VmaxLabel,
                 UINT32 VminLabel )
{
   SINT32 i, IVal, Scale = 1;

   if(CurrentGraph == FORCELBGRAPH) Scale = 10;

   for (i = 0; i < MAX_WELD_SAMPLES; i++){
      /* calculate to 160 pixels equal to 20 lines at 8 dots*/

      IVal = 160L * (Data[i] - (SINT32)VminLabel*Scale);
      IVal /= Scale * (VmaxLabel - VminLabel);
      if(IVal <= 0) IVal = 1;
      Data[i] = IVal;
    }

} /* end of RecalibVal */



/**-------------------------------------------------------------------------**
 ** This is the digital filter routine. Its main function is to take an     **
 ** existing array of numbers and filter it. In doing so the new values are **
 ** stored in the same array. It can be called from any module in the code. **          
 ** INPUT : ForceDigValue, which is a global value that can be set from the **
 **         menu screen under the print option.                             **
 ** OUTPUT: This function returns no data.                                  **                                              **
 **-------------------------------------------------------------------------**/
void DigitalFilterFunction(SINT32 * Data, SINT32 ForceDigFilter)
{

   SINT32 ForcePivot = 0;   /*-- Average of values stored here             --*/
   SINT32 TempTotalVal = 0; /*-- Temporarily stores total of values added  --*/
   SINT32 TempForceValue= 0;/*-- The original ForceDigFilter is stored here--*/
   UINT16 count = 0;        /*-- Used for incrementing                     --*/


   /*-- If printing a VELOCITY graph filter points whether digital filtering --*/
   /*-- is ON or OFF. Otherwise, for any other graph check is digital filter --*/
   /*-- -ing is ON or OFF before filtering points. --*/

   if((RunningPreset.DigitalFilterFlag == TRUE) ||
      (GraphCurrentlySelected == VELINGRAPH)||
      (GraphCurrentlySelected == VELMMGRAPH)){
      
      /*-- initialize variables --*/
      TempForceValue = ForceDigFilter;
      TempTotalVal = 0;
      ForcePivot = ForceDigFilter/2; /*-- pivot is the mid point of ForceDigFilter--*/
      

      /*-- digitally filter array val contain at most 400 points --*/
      for(count = ForceDigFilter-1; count < WeldDataCount; count++){
      

         /*-- Calulate average of N points where N is ForceDigFilter --*/
         while(ForceDigFilter > 0){
           TempTotalVal += Data[count - (UINT16)(ForceDigFilter-1)];
           ForceDigFilter--;
         }
      

         /*-- Once Average is calculated store at pivot point --*/
         Data[ForcePivot++] = TempTotalVal / TempForceValue;
         TempTotalVal = 0;
         ForceDigFilter = TempForceValue;
      }
    }
}  



