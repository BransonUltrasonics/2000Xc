/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/opcodes.h_v   1.5   28 Jul 2014 13:03:32   rjamloki  $ */
#ifndef OPCODES_H
#define OPCODES_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: n/a

   Filename:    opcodes.h

                    
            Written by: Mark Lazarewicz  
                  Date:  1/22/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------
                                               
                                               

  ------------------------------- DESCRIPTION -----------------------------------

   This file contains an enum typedef of all valid welder control
   message opcodes.

 ------------------------------ INCLUDE FILES ----------------------------------
*/    

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/               

/* ************************************************************************** */
/* >>>>>>>>>>>>>>>>>>>>>>>>>>> MESSAGE QUEUE TYPES <<<<<<<<<<<<<<<<<<<<<<<<<  */
/* ************************************************************************** */

typedef enum
   {                        
   OP_ASCII_COMMAND  =  0u,
   OP_ADSC_SESSION_START,
   OP_ADSC_SESSION_TERMINATE,
   OP_ADSC_EXPECT_NO_RESPONSE,
   OP_BATTRAM_READ_MIN_PRESET,          /* queues: NVMM      */
   OP_BATTRAM_READ_MAX_PRESET,          /* queues: NVMM      */
   OP_BATTRAM_READ_PRESET,              /* queues: NVMM      */
   OP_BATTRAM_RECALL_EVENT_LOG,         /* queues: NVMM      */
   OP_BATTRAM_RECALL_SWARE_LOG,         /* queues: NVMM      */
   OP_BATTRAM_WRITE_SWARE_LOG,          /* queues: NVMM      */
   OP_BATTRAM_WRITE_PRESET,             /* queues: NVMM      */
   OP_BATTRAM_WRITE_PRESET_FAIL,        /* queues: NVMM      */
   OP_BATTRAM_WRITE_PRESET_SUCCESS,     /* queues: NVMM      */
   OP_BATTRAM_WRITE_ERROR_LOG,          /* queues: NVMM      */
   OP_BATTRAM_WRITE_EVENT_LOG,          /* queues: NVMM      */
   OP_BATTRAM_WRITE_WELD_LOG,
   OP_BLINK_DISPLAY,                    /* queues: FPDM      */ 
   OP_CHANGE_PRESET_DATA,
   OP_COMM_CONTROL,
   OP_COMM_STRING,
   OP_CLEAR_ALARMS,
   OP_CLEAR_DISPLAY,
   OP_CLEAR_LOG,
   OP_ASCII_DIAG_REQ_SESSION,
   OP_DISPLAY_MESSAGE,                  /* queues: FPDM      */
   OP_DISREGARD_KEYPRESS,
   OP_DISPLAY_ASCII_SCREEN,
   OP_FPSC_SESSION_START,
   OP_FPSC_SESSION_TERMINATE,
   OP_FPSC_SESSION_STATE,
   OP_EXT_MAD_COMMAND,
   OP_FRONT_PANEL_KEYPRESS,             /* queues: FPSC      */
   OP_IPS_RESPONSE,
   OP_GOOD_PRESET,                      /* queues: NVMM      */
   OP_GOOD_MIN_PRESET,                  /* queues: NVMM      */
   OP_GOOD_MAX_PRESET,                  /* queues: NVMM      */
   OP_HERE_IS_PRESET,
   OP_HERE_IS_CURRENT_SETUP,
   OP_READ_CURRENT_SETUP,
   OP_GOOD_CURRENT_SETUP,
   OP_CHANGE_CURRENT_SETUP,
   OP_BATTRAM_READ_CURRENT_SETUP,
   OP_BATTRAM_WRITE_CURRENT_SETUP,
   OP_CURRENT_SETUP_READ_FAIL,
   OP_CURRENT_SETUP_WRITE_FAIL,
   OP_HERE_IS_WELD_DATA,                /* queues:SYSM       */
   OP_MANAGE_ERRORS_MSG,                /* queues:SYSM       */
   OP_MENU_ITEM_NOT_FOUND,
   OP_NVM_RECALL_PARAMETERS,            /* queues: NVMM      */
   OP_NVM_SECTION_WRITE,                /* queues: NVMM      */
   OP_NVM_WRITE_PRESSURE_PARAMETERS,             /* queues: NVMM      */
   OP_UAR,
   OP_UPLOAD_SYSTEM_CONFIGURATION,
   OP_PORT_DISCONNECT,
   OP_MIN_PRESET_READ_FAIL,             /* queues: NVMM      */
   OP_MAX_PRESET_READ_FAIL,             /* queues: NVMM      */
   OP_PRESET_READ_FAIL,                 /* queues: NVMM      */
   OP_PRESET_WRITE_FAIL,
   OP_PRINTER_OFFLINE,                  /* queues: PMGR      */
   OP_PRINT_NOW,                        /* queues: PMGR      */  
   OP_PRINT_ABORT,                      /* queues: PMGR      */
   OP_PROTOCOL_DEST_INFO,
   OP_RECALL_ERROR_LOG,                 /* queues: NVMM      */
   OP_RECALL_WELD_LOG,
   OP_RECALL_EXT_PRESET,                /* queues: QVGA      */
   OP_READ_ALARM_DATA,
   OP_READ_LOG,
   OP_READ_SWARE_LOG_RESPONSE,
   OP_READ_ERROR_LOG_RESPONSE, 
   OP_READ_SYSTEM_DATA_RESPONSE,
   OP_READ_WELD_DATA_RESPONSE,
   OP_RESET_WELD_ALARMS,
   OP_RESET_REQUIRED,
   OP_START_WELD_DATA,
   OP_STOP_WELD_DATA,
   OP_UPLOAD_CONFIGURATION,
   OP_RSM_COMMAND,
   OP_RSSN_MODE_CHANGE,
   OP_RESET,                            /* queues: WDTK      */
   OP_RESUME_KEYPRESS,
   OP_RUN_KEY_PRESSED,                  /* queues: WMGR      */
   OP_SERIAL_STRING,
   OP_SESSION_TERMINATE_COMMAND,
   OP_SESSION_ACTIVE,
   OP_SESSION_IDLE,
   OP_SETUP_ALARM_DATA,                 /* queues: WMGR      */
   OP_WELDER_STATE_CHANGE,              /* queues: WMGR      */
   OP_UPDATE_PARAMETERS,
   OP_START_HORNDOWN,                   /* queues: WMGR      */
   OP_TEST_KEY_PRESSED,                 /* queues: WMGR      */
   OP_RESET_KEY_PRESSED,                /* queues: WMGR      */
   OP_MAIN_KEY_PRESSED,                 /* queues: WMGR      */
   OP_GOBACK_KEY_PRESSED,               /* queues: WMGR      */
   OP_STOP_TEST,                        /* queues: WMGR      */
   OP_CALIB_POWER,                      /* queues: WMGR      */
   OP_CALIB_LOADCELL,                   /* queues: WMGR      */
   OP_CALIB_ACTUATOR,                   /* queues: WMGR      */
   OP_CALIB_START,                      /* queues: WMGR      */  
   OP_POWERDOWN,                        /* queues: WMGR      */
   OP_TIMER_EXPIRED,                    /*                   */
   OP_WHERE_IS_PRESET,
   OP_FINAL_WELD_DATA,
   OP_1MS_DATA,
   OP_CLEAR_WELDHISTORY_FRAM,
   OP_NVM_WRITE_UPGRADE600,
   OP_NVM_WRITE_UPGRADE805,
   OP_TOUCH_SCRN_MSG_READY,             /* Msg to QVGA Handler from Touch Screen */
   OP_TOUCHDATA_FROM_ISR,               /* Msg to Touch Screen Handler from Touch Screen ISR */
   OP_VGAMENUTASK_MSG,
   OP_NVM_WRITE_FORCE_PARAMETERS,
   MSG_OPCODE_SIZER = 32768u            /* force to UINT16 ! */
   } MSG_OPCODE_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* OPCODES_H */

