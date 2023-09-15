/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/names.h_v   1.6   26 Sep 2014 13:02:30   rjamloki  $ */
#ifndef NAMES_H
#define NAMES_H
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/names.h_v  $
 * 
 *    Rev 1.6   26 Sep 2014 13:02:30   rjamloki
 * Removed double header
 * 
 *    Rev 1.5   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
*/

/*
---------------------------- INCLUDE DESCRIPTION ------------------------------
                                                  
  Module name: names.h

  Filename:  names.h


           Written by: Mark Lazarewicz 
                 Date: 1/21/96 
             Language:  68000 Microtec "C" Compiler

--------------------------------- REVISIONS -----------------------------------


--------------------------------- DESCRIPTION -----------------------------------

   This file defines task names, region names, partition names, queue names,
   and semaphore names.

--------------------------------- INCLUDE FILES ---------------------------------

   NONE

---------------------------------- DEFINITIONS ----------------------------------
*/

/*
 *  region zero name
 */

#define ROOT_REGION_ZERO_NAME           "RN#0"
              

/*===========================================================================*/
/* QUEUE DEFINITIONS                                                         */
/*===========================================================================*/

#define DIAG_Q                   "DIAG"   /* Diagnostics Manager  queue                */
                                                                                         
#define FPKP_Q                   "FPKP"   /* Front Panel Key Pad queue                 */

#define FPSC_Q                   "FPSC"   /* Front Panel State Coordinator queue       */

#define RSCH_Q                   "RSCH"   /* Remote Serial Command Handler             */

#define ROOT_Q                   "ROOT"   /* The ROOT task input queue                 */

#define SYSM_Q                   "SYSM"   /* System Manager Task                       */

#define WDTK_Q                   "WDTK"   /* welder WatchDog TicK queue                */

#define WMGR_Q                   "WMGR"   /* Welder Manager queue                      */

#define PMGR_Q                   "PMGR"   /* Printer Manager queue                     */ 

#define DUPS_Q                   "DUPS"   /* DUPS manager queue                        */

#define VGA_Q                   "VGA"   /* VGA input queue                          */

#define TSRN_Q                   "TSRN"   /* Touch Screen queue                        */

#define RVTS_Q                   "RVTS"   /* Remote VGA/touchscreen queue              */

/*===========================================================================*/
/* TASK DEFINITIONS                                                          */
/*===========================================================================*/

#define DIAG_TASK                "diag"   /* Diagnostics Manager                       */

#define FPKP_TASK                "fpkp"   /* Front Panel State Manager task            */

#define FPSC_TASK                "fpsc"   /* Front Panel State Coordinator task        */

#define ROOT_TASK                "root"   /* The ROOT task                             */

#define RSCH_TASK                "rsch"   /* Remote Serial Command Handler             */

#define SYSM_TASK                "sysm"   /* SYStem Manager task                       */             

#define WDTK_TASK                "wdtk"   /* WatchDog TicK task                        */

#define WMGR_TASK                "wmgr"   /* Weld ManaGeR  task                        */

#define PMGR_TASK                "pmgr"   /* Printer Manager task                      */

#define DUPS_TASK                "dups"   /* DUPS Manager task                         */

#define VGA_TASK                "vga"   /* VGA task                                 */

#define TSRN_TASK                "tsrn"   /* Touch Screen task                         */

#define RVTS_TASK                "rvts"   /* Remote VGA/touchscreen tack               */

/*===========================================================================*/
/* SOURCE TASK DEFINITIONS                                                   */
/*===========================================================================*/
/* for all task names added above, add to this enumeration */
/*NOTE:  ALL NEW TASKS AND QUEUES NEED TO BE ADDED TO THIS LIST AND TO THE */
/*       TASK_QUEUE_NAME_TABLE IN DETERMINE_SYSTEM_OBJECT_ID.C IN THE SAME ORDER */

typedef  enum
        {
        DIAG_SOURCE_TASK = 0u,
        FPKP_SOURCE_TASK,   
        FPSC_SOURCE_TASK,
        VGA_SOURCE_TASK,
        ROOT_SOURCE_TASK,
        RSCH_SOURCE_TASK,
        SYSM_SOURCE_TASK,
        TSRN_SOURCE_TASK, 
        WDTK_SOURCE_TASK,
        WMGR_SOURCE_TASK,
        PMGR_SOURCE_TASK,
		DUPS_SOURCE_TASK,
        WC_ISR_TASK,
        RVTS_SOURCE_TASK,
        MAX_NUMBER_OF_TASKS,
        SOURCE_TASK_SIZER = 255
        } __attribute__((__packed__))SOURCE_TASK_ID_TYPE;

/*===========================================================================*/
/* SEMAPHORE  DEFINITIONS                                                    */
/*===========================================================================*/

#define VGA_SM                "qvsm"  /*  VGA Transmit semaphore            */
#define TSRN_SM                "tssm"  /*  Touch Screen Transmit semaphore    */

/*===========================================================================*/
/* PARTITION  DEFINITIONS                                                    */
/*===========================================================================*/

#define MAD_PARTITION                "MAD "     /* used for  messages */

#define READ_LOG_PARTITION           "RLOG"     /* used for reading sware log */

#define SOFTWARE_DOWNLOAD_PARTITION  "RSDM"     /* used by Remote Software Download      */


/*===========================================================================*/
/* EVENT DEFINITIONS                                                         */
/*===========================================================================*/

                    
/*--------------------------- TYPE DECLARATIONS -----------------------------*/
                                                                               
/* none */

/*------------------------ FUNCTION PROTOTYPES ------------------------------*/
          
/* none */

#endif /* NAMES_H */






