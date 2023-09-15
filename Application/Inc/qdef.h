/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/qdef.h_v   1.3   06 Oct 2014 06:49:54   AnPawar  $ */
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/qdef.h_v  $
 * 
 *    Rev 1.3   06 Oct 2014 06:49:54   AnPawar
 * SendMessage() declaration removed.ERROR_CALLER_TYPE enum defined.
 * 
 *    Rev 1.2   03 Oct 2014 06:27:40   rjamloki
 * function renamed q_send() to SendMessage() and tm_wkafter() function removed
 * 
 *    Rev 1.1   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
 * 
 *    Rev 1.0   28 Jul 2014 14:56:18   rjamloki
 * Initial revision.
 *****************************************************************************/
/*
 --------------------------- MODULE DESCRIPTION ---------------------------
 Filename:    qdef.h
----------------------------- DESCRIPTION --------------------------------

 This module contains the Queue(fifo object) read/write type and error codes.

----------------------------- PSEUDO CODE --------------------------------

---------------------------- LOCAL_EQUATES -------------------------------*/

#if __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------*/
/* Don't allow this file to be included more than once.                */
/*---------------------------------------------------------------------*/
#ifndef _QDEF_H
#define _QDEF_H

#include "portable.h"


/* task stack size type */
typedef enum {
               T_SIZE_0    = 0,
               T_SIZE_128  = 128,
               T_SIZE_256  = 256,
               T_SIZE_512  = 512,
               T_SIZE_1024 = 1024,
               T_SIZE_2048 = 2048,
               T_SIZE_4096 = 4096,
               T_SIZE_8192 = 8192,
               T_SIZE_16384= 16384
             } T_STACK_SIZE_TYPE;
/* a symbol indicating the identity    */
/* of the manage error calling routine */
typedef enum
		{
		ACCESS_CONTROL_OUTPUT_PORTS = 0u,
		ALARM_DATABASE_MANAGER,
		ALARM_MONITOR,
		ASYNC_ACTIVE_CONNECTION,
		ASCII_DIAGS_INTERFACE_MANAGER,
		ASCII_DIAGS_STATE_COORDINATOR,
		BATTRAM_DEFAULT_CHECK,
		COMM_PASSWORD,
		COMM_QUEUE_STRING,
		COMM_XMT_STRING,
		COMM_ACTIVE_SESSION,
		COMM_INBOUND_MSG_ROUTER,
		COMM_OUTBOUND_MSG_ROUTER,
		DIAGNOSTICS_MANAGER,
		DISPLAY_STARTUP_MESSAGE,
		DUAL_PORT_RAM_MGR,
		EEPROM_ACCESS,
		EEPROM_MEMCPY,
		ERROR_LOG_HANDLER,
		EXCEPTION_HANDLER,
		FIPS_RX_HANDLER,
		FIPS_TX_HANDLER,
		FPSP_PORT_MANAGER,
		FPSP_SHELL,
		FRONT_PANEL_DISPLAY_MANAGER,
		FRONT_PANEL_KEY_PAD_MANAGER,
		FRONT_PANEL_KEY_PAD_TASK,
		FRONT_PANEL_STATE_COORDINATOR,
		INIT_PROCESS_FP_KEYPAD_INTERRUPT,
		MANAGE_TIMERS,
		MONITOR_INPUT_PORTS,
		NVM_MANAGER,
		PRINTER_MANAGER,
		PROCESS_FP_KEYPAD_INTERRUPT,
		QUEUE_PRINT,
		VGA_INTERRUPT,
		READ_FRONT_PANEL_KEYPAD,
		REMOTE_SERIAL_COMMAND_HANDLER,
		ROOT,
		SERIAL_INTERRUPT,
		SPI_DRIVER,
		SRAM_ACCESS,
		STATE_MACHINE,
		STATION_HARDWARE_MANAGER,
		SWARE_LOG_HANDLER,
		SYS_MANAGER,
		TRANSLATE_ASCII_TO_FP_KP,
		TOUCH_SCRN_MODULE,
		UART_RCV_BUF,
		VERIFY_PASSWORD,
		WELD_DATA_PRINT_MGR,
		WELD_MGR,
		WD_TICKLE,
		MAX_NUMBER_OF_ERROR_CALLERS,
		ERROR_CALLER_SIZER = 32768
	 } ERROR_CALLER_TYPE;


#endif
UINT16 SerialMessageQueue(UINT8 * buf, UINT16 cnt);
extern UINT16 QReadyFlag;
#if __cplusplus
}
#endif

