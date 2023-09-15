/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_hornscan.cpp_v   1.17   08 Jan 2015 03:18:20   AnPawar  $ */
/****************************************************************************/ 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/dups_hornscan.cpp_v  $
 * 
 *    Rev 1.17   08 Jan 2015 03:18:20   AnPawar
 * printf removed
 * 
 *    Rev 1.16   28 Nov 2014 07:34:32   rjamloki
 * memset the structure DUPS_MSGBUF to zero.
 * 
 *    Rev 1.15   20 Oct 2014 06:19:34   AnPawar
 * NUMPASSES define removed.
 * 
 *    Rev 1.14   06 Oct 2014 06:30:32   AnPawar
 * removed DUPS_ManagerTask.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.13   03 Oct 2014 05:53:40   rjamloki
 *  function renamed q_send() to SendMessage() and using RTOS::DelayMs() in place of tm_wkafter()
 * 
 *    Rev 1.12   11 Sep 2014 10:50:30   rjamloki
 * defines moved to top of file
 * 
 *    Rev 1.11   28 Jul 2014 12:43:42   rjamloki
 * added support for horn scan amplitude and current graph
 * 
 *    Rev 1.10   15 Jul 2014 18:08:46   hasanchez
 * Changes about the horn scan.
 * 
 *    Rev 1.9   11 Jun 2014 11:28:54   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:47:54   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 02:59:08   rjamloki
 * removed static from function HS_FindPhaseIndex def
 * 
 *    Rev 1.6   06 Mar 2014 11:03:46   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:20   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:32   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.3   03 Jan 2014 08:45:22   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:   DUPS HornScan

   Filename:      dups_hornscan.c

   Function name: 

            Written by: Rherring 
                  Date: 06/29/00
              Language:  "C"                              


 ------------------------------ DESCRIPTION -------------------------------

   This file deals with DUPS Horn Scan functions

 ----------------------------- INCLUDE FILES ------------------------------*/

#include "dups_api.h"
#include "qdef.h"
#include "dups.h"
#include "param.h"
#include "portable.h"
#include "graphs.h"
#include "string.h"
#include "FrontPanelKeypadTask.h"
#include "keypad.h"
#include "digout.h"
#include "getmsg.h"
#include "ticks.h"
#include "menu.h"
#include "menu5.h"
#include "inputs.h"
#include "spidd.h"
#include "statedrv.h"
#include "selctkey.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "DUPS_ManagerTask.h"
#include "ascii.h"

/*---------------------------- EXTERNAL DATA -------------------------------*/

extern UINT8    HS_KeyPressed;
extern BOOLEAN HornScanOL;
extern INBITS Inp;

extern BOOLEAN VGAHornScanOLD;
extern BOOLEAN VGAAbortHornScan;

/*----------------------------- LOCAL DEFINES ------------------------------*/

#define HS_MIDCOEF            (HS_NUMCOEFS/2)
#define HS_SCALEFACT          32768
#define HS_CLUSTERPTS         10
#define HS_HALFWINDOWSIZE     2
#define HS_FAILLIMIT          3
#define HS_loop               40
#define PRINTBUFSIZE 10000

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/


/*----------------------------- GLOBAL DATA --------------------------------*/

SINT8 DUPS_ScanStep = HORNSCANIDLE;
const SINT16 HS_FiltCoefs[] = {  -157,-361,-465,-152,     /* Filter coff used to smooth graph*/
                                 850,2548,4552,6190,
                                 6824,
                                 6190,4552,2548,850,
                                 -152,-465,-361,-157  };

/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/
SINT8   PrintBuffer[PRINTBUFSIZE];
UINT16 *HornScanRawFrequency = (UINT16 *)PrintBuffer;
SINT16 *HornScanRawCurrent = (SINT16 *) &PrintBuffer[2000];
SINT16 *HornScanRawPhase =   (SINT16 *) &PrintBuffer[4000];
SINT16 *HornScanRawAmp = (SINT16 *) &PrintBuffer[6000];
static  UINT16 count = 0;

extern SINT32 DigTuneValue;           /* This is what user edits */


/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/
void UpdateFrequencyResonance(void);

/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/

void DigTuneStore(void);
/*------------------------------ CODE --------------------------------------*/



void HS_Resonance(void)
/***********************************************************************************/
/* This function calculates the resonance frequency of the horn.If no resonance is */
/* found,then this function performs the abort process.                            */ 
/***********************************************************************************/
{
   enum DUPS_RESULTS status = DUPS_OTHER;
   DUPS_MSGBUF outMsg;
   memset(&outMsg, 0, sizeof(DUPS_MSGBUF));
/* Initially, check to see if any zero crossings exist */

   if ((status = HS_CrossingExists(HornScanRawPhase, (HornScanInfo.NumScanPoints + HS_NUMCOEFS)))
              == DUPS_SUCCESS )  
      {
     /* Apply a low pass filter to smooth some of the high frequency noise */
     /* in the raw phase data                                              */
     
      HS_FirFilt( HornScanRawPhase, (HornScanInfo.NumScanPoints + HS_NUMCOEFS));
     
     
     /*  Find the resonance points i.e, points around the zero crossing */
     
      HS_4Clusters();
      /*Update the strings for series and parallel freq.*/
      UpdateFrequencyResonance();
      } // End of 'if' statement

// another if because this decision depends on the result of first if()
   
   if (status == DUPS_SUCCESS)
      outMsg.data1 = HORNSCANCOMPLETED;
   else 
      {
      outMsg.data1 = HORNSCANABORTED;             
      UpdateKeyMask(HSSUBMENUMASK);      /* Enable all keys*/
      SendFakeKeyPress(UPDATEDISPLAY);  /* Update the dispaly*/
      }
   outMsg.mt = DUPS_MSGHORNSCANSTEP;
   DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
} /* End of HS_Resonance(void)*/

void HS_FirFilt( SINT16 vector[], UINT16 vectsize)
/**************************************************************************************/
/* This function applies a low pass filter to smooth some of the high frequency noise */
/* in the raw phase data.                                                             */ 
/**************************************************************************************/

{
  UINT16 index1,  // Points to location to store filtered value
         index2;  // Selects co-efficient and filter input.

  SINT32 filtsum; // Holder for filter calculation.

  for( index1 = 0; index1 < (vectsize - HS_NUMCOEFS); index1++)
  {
     filtsum = 0;

     for(index2 =0; index2 < HS_NUMCOEFS; index2++)
     filtsum  = filtsum + (HS_FiltCoefs[index2] * vector[index1 + index2]);

     vector[index1] = filtsum/ HS_SCALEFACT;
  }
    return;
} /* End of HS_FirFilt( SINT16 vector[], UINT16 vectsize) */



enum DUPS_RESULTS HS_CrossingExists (SINT16 vector[], SINT16 vectsize)
/**************************************************************************************/
/* This function checks to see if any zero crossings exist throughout the scan.       */
/**************************************************************************************/
{
   UINT16 index;
   enum DUPS_RESULTS status = DUPS_OTHER;
   SINT16 maxval = -1;
   SINT16 minval = 1;

   for (index =0; index < vectsize; index++)
      {
      if (vector[index] > maxval)
         maxval = vector[index];
      if (vector[index] < minval)
         minval = vector[index];   
      }

   if ((maxval > 0) && (minval < 0))
      status = DUPS_SUCCESS;    // Crossings exist.

   return status;
} /* End of  HS_CrossingExists (SINT16 vector[], SINT16 vectsize) */



void HS_4Clusters(void)
/**************************************************************************************/
/* This function finds the resonance points around the zero crossing.                 */
/**************************************************************************************/
{
   UINT8  found = FALSE;             //Flag for search logic
   UINT16 i,j,k,numfails;            //Loop and Indexing.
   UINT16 temp_Freq[HS_CLUSTERPTS];  // Frequency Indexes for cluster points.
   SINT16 temp_Phase[HS_CLUSTERPTS]; // Phase Indexes for cluster points.
   SINT32 Freq1;
   BOOLEAN  ExitFlag = FALSE;

   i= j= k= numfails= 0;

/* Do the operation either 
    1. Until six resonant frequencies are found or
    2. The index is equalled or exceeded.(Index being Number Of Scan Points - 2)*/

   while ((k < DUPS_NUMRESONANCES) && 
          (i < (HornScanInfo.NumScanPoints - HS_HALFWINDOWSIZE)))
      {
  /* Execute the for loop checking in each loop for a cluster.
     Increment 'numfails' if a cluster is not found and if a cluster is 
     found copy the corresponding values of the frequency and phase arrays
     to the temporary arrays
  */
      for (i = HS_HALFWINDOWSIZE; i < HornScanInfo.NumScanPoints - HS_HALFWINDOWSIZE; i++)
         {
         if ((HornScanRawPhase[i - HS_HALFWINDOWSIZE] > 0) && (HornScanRawPhase[i + HS_HALFWINDOWSIZE] < 0))
            {
            found =  TRUE;  //Cluster is found.
            HornScanInfo.ResonanceFreqType[k] = FREQ_SERIES;
            numfails = 0;
            }
         else if((HornScanRawPhase[i - HS_HALFWINDOWSIZE] < 0) && (HornScanRawPhase[i + HS_HALFWINDOWSIZE] > 0))   
            {
            found = TRUE;   //Cluster is found
            HornScanInfo.ResonanceFreqType[k] = FREQ_PARALLEL;
            numfails = 0;
            }
         else
            numfails++;
            
         if (found)
            { 
            temp_Freq[j] = HornScanRawFrequency[i];
            temp_Phase[j++] = HornScanRawPhase[i];
            }

/* the following is to make sure that we don't overflow the cluster vectors*/

         if (j >= HS_CLUSTERPTS)      //Too many points, so force analysis.
            numfails = HS_FAILLIMIT;
   
         if (found && (numfails >= HS_FAILLIMIT))  //Found end of cluster.      
            {
            HornScanInfo.ResonanceFreqs[k++] = HS_X4YZero(temp_Freq,temp_Phase,j);
            found = FALSE;
            numfails = 0;
            j = 0;
            }

         if (k >= DUPS_NUMRESONANCES)
            break;
      } //End of for loop to search for clusters.
   } // End of while still looking for resonance frequencies.
      
/* Here some special code for horn scan to autosave in Digital Tune */
/* Use 'j' as max number of resonances found */

   while (HornScanInfo.ScanStatus != DUPS_SCANSCOMPLETE) {
      RTOS::DelayMs( MS_TO_TICKS( 100 ) * MILLS_PER_TICK);
   }
  
   i=0;
   while (ExitFlag == FALSE) {
      if (HornScanInfo.ResonanceFreqType[i] == FREQ_PARALLEL){ /* Found a parallel one */
         Freq1 = HornScanInfo.ResonanceFreqs[i];
         DigTuneValue = Freq1;
         CurrentSetup.DigTuneFlag |= BIT0;         /* Turn on digital tune */
         ExitFlag = TRUE;
      }
      if (++i >= k) ExitFlag = TRUE; 
      //if (++i >= j) ExitFlag = TRUE;  /*  this condition could turn the cycle to overload because 
   }
   DigTuneStore();                /*    HS It will only save the new resonance frecuency if found a Parallel frecuency */
   SetDigTune();
                                 /* the stop of the software */  
      
} /* End of HS_4Clusters(void)*/



UINT16 HS_X4YZero(UINT16 xcap[], SINT16 ycap[],UINT16 vectsize)
/**************************************************************************************/
/* This function does linear regression to fit the line and finds the x intercept for */
/* y i.e., value of Frequency where phase is zero.                                    */
/**************************************************************************************/

{
   UINT16 i;                      //Loop control
   double sxy,                    //Sum of (x*y)
          sx,sy,                  //Mean of x, mean of y.
          sx2;                    //Sum of x^2
   double slope,                   //Slope of line.
          y_intcept;               //Intercept.

   sxy= sx= sy= sx2 =0;

   for(i=0;i<vectsize;i++)
   {
     sx= sx + xcap[i];
     sy= sy + ycap[i];
     sxy= sxy + (xcap[i] * ycap[i]);
     sx2= sx2 + (xcap[i] * xcap[i]);
   }   
   slope = (sxy - ( (sx * sy)/ vectsize))/(sx2 - ((sx * sx) / vectsize) );
   y_intcept  = (sy / vectsize)  - (slope * (sx/ vectsize)); 
   return -(y_intcept/slope);
} /* End of HS_X4YZero*/
  


enum DUPS_RESULTS DUPS_MsgUploadScanPt(void)
/***************************************************************************************/
/* This function sends a command to DUPS to upload scan point data. Uploaded scan data */
/* is stored in struct and raw buffer. This function starts the abort process if       */
/* 'goback' key is pressed during scan, Estop occurs, or an overload occurs.           */
/***************************************************************************************/
{  
 
   enum DUPS_RESULTS  status = DUPS_OTHER;
   DUPS_MSGBUF  outMsg;
   memset(&outMsg, 0, sizeof(DUPS_MSGBUF));
   HORNSCANPOINT *ptData = (HORNSCANPOINT *) &DUPS_RspBuf.Rsp_Data;
  /* transfer the scan parameter set scan into cmd buf */

   DUPS_HORNSCANCMD  *ScanCmd = (DUPS_HORNSCANCMD *) &DUPS_CmdBuf.Cmd_Data;
  /*   Set up the databytes in the proper order */

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004 + sizeof(DUPS_HORNSCANCMD);
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADSCAN;   /* Set up command */

   ScanCmd->PointIndex = HornScanInfo.NumScanPoints;

   if ((HS_KeyPressed == GoBackKey) || (Inp.Estop == TRUE) ||
       (VGAAbortHornScan == TRUE))
   {
      VGAAbortHornScan = FALSE;
      HSReset();
      if(Inp.Estop == TRUE){
         SendFakeKeyPress(GoBackKey);
      }   
      DUPS_HornScanAbort();
      status = DUPS_SUCCESS;
   } 
   else if (HornScanOL == TRUE){ /* check for overload */  
      VGAHornScanOLD = TRUE;
      HSReset();
      DUPS_HornScanAbort();
      UpdateKeyMask(HSSUBMENUMASK); 
      RTOS::DelayMs(MS_TO_TICKS(2000) * MILLS_PER_TICK);
      HornScanOL = FALSE;
      status = DUPS_SUCCESS;
   } 
   else
   {
      if((status = DUPS_DataXfer()) == DUPS_SUCCESS
         && DUPS_ScanStep != HORNSCANABORTED)
      {
         if(ptData -> Status == HornScanPointValid
         || ptData -> Status == HornScanPointLast)
         {  
            HornScanRawPhase[HornScanInfo.NumScanPoints] = ptData -> Phase;
            HornScanRawCurrent[HornScanInfo.NumScanPoints] = ptData -> Current;
            HornScanRawFrequency[HornScanInfo.NumScanPoints] = ptData -> Frequency;
            HornScanRawAmp[HornScanInfo.NumScanPoints] = ptData ->Amplitude;
            HornScanInfo.NumScanPoints++;
         }


         if( ptData -> Status == HornScanPointLast
         || HornScanInfo.NumScanPoints > DUPS_HORNSCANMAXPOINTS)
         {
         outMsg.data1 = HORNSCANCALCULATING;
         outMsg.mt = DUPS_MSGHORNSCANSTEP;
         DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
         count=0;
         }
         else // scan point may be invalid or valid
         {  
            if(ptData -> Status == HornScanPointNotValid) // check is it invalid
            {
               if(count < HS_loop)       // check is it invalid for 40 times.
               {
                  outMsg.mt = DUPS_MSGUPLOADSCANPOINT;
                  DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
                  count++;
               } // end of if - invalid point - upload it again
               else      // it is invalid for 40 times then abort scan
               {
                  outMsg.data1 = HORNSCANABORTED;             
                  UpdateKeyMask(HSSUBMENUMASK);
                  SendFakeKeyPress(UPDATEDISPLAY);
                  outMsg.mt = DUPS_MSGHORNSCANSTEP;
                  DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
                  count=0;
               }
            } // end of if - it is invalid point
            else        
            {    //it is valid point - upload next
               outMsg.mt = DUPS_MSGUPLOADSCANPOINT;
               DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);
               count=0;
            } // end of else - valid point uplaod next
         }
      } // end of if Datatxfr is successful
      else
      {    //Datatxfr is not successful
       /* clear up printer buffers house keeping */
         outMsg.data1 = HORNSCANABORTED;             
         UpdateKeyMask(HSSUBMENUMASK);
         SendFakeKeyPress(UPDATEDISPLAY);
         outMsg.mt = DUPS_MSGHORNSCANSTEP;
         DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, outMsg, 0);

        if (status == DUPS_SUCCESS)
        status = DUPS_OTHER;
      }    // abort scan
   }// end of else goback key is not pressed - uplaod scan point
   return status;
} /* End of SINT16 DUPS_MsgUploadScanpt(void) */


void HS_FindPhaseIndex(SINT16 * phase, UINT16 base_index, UINT16 count,
                  UINT16 result[2])
/****************************************************************************/
/*                                                                          */
/* Locates minimum and maximum values inside the phase data.                */
/*                                                                          */
/* phase          phase data pointer                                        */
/* base_index     window starts at this index                               */
/* count          window is this long                                       */
/* result         output array containing minimum and maximum index for     */
/*                this window data (in ascending index order)               */
/*                                                                          */
/****************************************************************************/
{
    UINT16 i;
    result[0] = base_index;     // set up with first point data
    result[1] = base_index;
    for (i = 1; i < count; i++) // start from second point in range
        {
        if (phase[base_index + i] < phase[result[0]])
            result[0] = base_index + i;
        if (phase[base_index + i] > phase[result[1]])
            result[1] = base_index + i;
        }
    // swap if data is backwards
    if (result[1] < result[0])
        {
        UINT16 tmp = result[1];
        result[1] = result[0];
        result[0] = tmp;
        }
} /* end of HS_FindPhaseIndex */


/** @brief Decimate horn scan data
 *
 * This function decimates the horn scan points collected during horn scan.
 * All the parameters i.e. phase , current and amplitude is decimated.
 * Function allows to use same buffers for input and output.
 * @parameter curr_in : input current data pointer
 * @parameter phase_in : input phase data pointer
 * @parameter Amp_in : input amplitude data pointer
 * @parameter count : input data size
 * @parameter curr_out : output current data pointer
 * @parameter phase_out : output phase data pointer
 * @parameter Amp_out : output amplitude data pointer
 *
 * @return final points count, can be lower than HS_POINTCOUNT if
 *         input point count was lower.
 */
UINT16 HS_Decimate(SINT16 * curr_in, SINT16 * phase_in, SINT16 * Amp_in,UINT16 count,
           SINT16 * curr_out, SINT16 * phase_out,SINT16 * Amp_out)
{
   UINT16 windowsize;  // integer window size
   UINT16 windowext;   // 0 or 1 on half-point windows
   UINT16 windowinc;   // window size increment for each pass
   UINT16 extra;       // if more than 400, increase windowext by 1
   UINT16 kk;      // loop index for later
   UINT16 index[2];    // two indexes for minimum/maximum

   if (count < HS_POINTCOUNT)
      {
      memcpy(curr_out, curr_in, sizeof(SINT16) * count);
      memcpy(phase_out, phase_in, sizeof(SINT16) * count);
      memcpy(Amp_out, Amp_in, sizeof(SINT16) * count);
      }
   else
      {
      // algorithm should be very close, if not equal, to Bresenham's line
      // drawing

      windowsize = (count * 2) / HS_POINTCOUNT;
      windowext = 0;
      windowinc = count * 2 - windowsize * HS_POINTCOUNT;
      extra = 0;
      for (kk = 0; kk < count; kk += windowsize + windowext)
         {
         extra += windowinc;
         if (extra >= HS_POINTCOUNT)
            {
            extra -= HS_POINTCOUNT;
            windowext = 1;
            }
         else
            windowext = 0;
         HS_FindPhaseIndex(phase_in, kk, windowsize + windowext, index);
         *curr_out++ = curr_in[index[0]];
         *curr_out++ = curr_in[index[1]];
         *Amp_out++ = Amp_in[index[0]];
         *Amp_out++ = Amp_in[index[1]];
         *phase_out++ = phase_in[index[0]];
         *phase_out++ = phase_in[index[1]];
         }
      count = HS_POINTCOUNT;
      }
   return count;
} /* End of HS_Decimate */
