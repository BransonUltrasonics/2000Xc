/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/inputs.h_v   1.7   26 Oct 2015 10:35:54   LMarkure  $ */
#ifndef INPUT_PORTS_H
#define INPUT_PORTS_H 
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 -------------------------------- REVISIONS ------------------------------------


 ------------------------------- DESCRIPTION -----------------------------------


        Type definitions for welder board input ports P0_IN and P1_IN and P2_IN


 ------------------------------ INCLUDE FILES ----------------------------------
*/    
#include "portable.h"
#include "A1025R.h"
/*  
 --------------------------------- DEFINITIONS ---------------------------------
*/


#define DEF_INIT_PORT_P0_DEBOUNCE_STATICS     0x3000    /* for initializing statics only */


/*  
 ----------------------------- TYPE DECLARATIONS -----------------------------
*/

                              
/*  
 --------------------------------- GLOBALS -------------------------------------
*/

typedef enum
        {
        POWER_OFF_SIGNAL_ACTIVE = 0,  
        POWER_OFF_SIGNAL_INACTIVE = 1,
        POWER_OFF_SIGNAL_REQ_UNKNOWN
        } POWER_OFF_SIGNAL_REQ_TYPE;

typedef enum
        {
        POWER_ON_SIGNAL_ACTIVE = 0,  
        POWER_ON_SIGNAL_INACTIVE = 1,
        POWER_ON_SIGNAL_REQ_UNKNOWN
        } POWER_ON_SIGNAL_REQ_TYPE;



                                     
/*=======================================*/                            
/* INPUT PORT 0 BIT STRUCTURE DEFINITION */
/*=======================================*/                            

typedef struct
 {
   UINT8      J3_17_signal            : 1,
              power_off_signal        : 1,  
              power_on_signal         : 1, 
              overload_input_signal   : 1,  
              mem_clear_signal        : 1,  
              mem_store_signal        : 1,  
              seek_signal             : 1,  
              run_signal              : 1;  
 } INPUT_P0_TYPE;
                              

               
/*=======================================*/                            
/* INPUT PORT 1 BIT STRUCTURE DEFINITION */                            
/*=======================================*/                            

typedef struct
 {
   UINT8      spar_bite         : 1,  /* bit 7,  */
              e_stop_signal     : 1,  /* bit 6,  */
              pb2_signal        : 1,  /* bit 5,  */
              pb1_signal        : 1,  /* bit 4,  */
              ext_ls_signal     : 1,  /* bit 3,  */
              e_stop2_signal    : 1,  /* bit 2,  */
              uls_signal        : 1,  /* bit 1,  */
              int_ls_signal     : 1;  /* bit 0,  */
 } INPUT_P1_TYPE;
                              


/*=======================================*/                            
/* INPUT PORT 2 BIT STRUCTURE DEFINITION */                            
/*=======================================*/                            

typedef struct
 {
    UINT8     ext_cycleabort_signal : 1,  /* bit 7,  */
              J3_19_signal          : 1,  /* bit 6,  */
              J3_33_signal          : 1,  /* bit 5,  */
              J3_32_signal          : 1,  /* bit 4,  */
              external_reset_signal : 1,  /* bit 3,  */
              J3_31_signal          : 1,  /* bit 2,  */
              start_signal          : 1,  /* bit 1,  */
              J3_1_signal           : 1;  /* bit 0,  */
 } INPUT_P2_TYPE;
                              
 /*=======================================*/
 /* INPUT PORT 3 BIT STRUCTURE DEFINITION */
 /*=======================================*/

 typedef struct
  {
     UINT8     spare1          : 1,  /* bit 7,  */
               ext_seek_signal : 1,  /* bit 6,  */
               spare2          : 1,  /* bit 5,  */
               spare3          : 1,  /* bit 4,  */
               spare4          : 1,  /* bit 3,  */
               spare5          : 1,  /* bit 2,  */
               spare6          : 1,  /* bit 1,  */
               spare7          : 1;  /* bit 0,  */
  } INPUT_P3_TYPE;

/* union to handle input port as a bit structure or a byte */

typedef union
        {
        UINT8           value;
        INPUT_P0_TYPE    port;
        } INPUT_PORT_P0_UNION_TYPE;
                                                             

/* union to handle input port as a bit structure or a byte */
typedef union
        {
        UINT8           value;
        INPUT_P1_TYPE    port;
        } INPUT_PORT_P1_UNION_TYPE;
      
/* union to handle input port as a bit structure or a byte */
typedef union
        {
        UINT8           value;
        INPUT_P2_TYPE    port;
        } INPUT_PORT_P2_UNION_TYPE;

typedef union
        {
        UINT8           value;
        INPUT_P3_TYPE    port;
        } INPUT_PORT_P3_UNION_TYPE;

#endif
