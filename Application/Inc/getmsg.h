/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/getmsg.h_v   1.7   11 Jun 2014 12:53:42   rjamloki  $ */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/getmsg.h_v  $
 * 
 *    Rev 1.7   11 Jun 2014 12:53:42   rjamloki
 * minor clean up of moving externs
 * 
 *    Rev 1.6   21 May 2014 10:49:06   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:12   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:06   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: getmsg.h

   Function name:

 --------------------------------- REVISIONS --------------------------------

 ------------------------------- DEFINES ---------------------------------------
*/
#include "keypad.h"

/* The following #defines set up the format of menu messages */

/* Message Type: 0-15, 1=Keyboard chr, 2=Select Key, 3=Control Message  */
/* Message Code: For keyboard chr, ASCII value of key.                  */
/*               For select key, 1-3 for Sel1-Sel3, 0 for TermSelectKey */
/*               For control message, code indicates type of message    */
/* Message Data: Any data that needs to accompany message               */
/* Message_use_id: Unique identifier for those messages that can only   */
/*                 appear in the message buffer once. If use_id is 0,   */
/*                 then message may appear in buffer multiple times.    */

#define MESSAGE_NEW           0x80000000

#define MESSAGE_TYPE_FIELD    0x0F000000
#define MESSAGE_TYPE_BITPOS   24

#define MESSAGE_CODE_FIELD    0x00FF0000
#define MESSAGE_CODE_BITPOS   16

#define MESSAGE_DATA_FIELD    0x0000FF00
#define MESSAGE_DATA_BITPOS   8

#define MESSAGE_USE_ID_FIELD  0x0000000F
#define MESSAGE_USE_ID_BITPOS 0

#define NUM_MSG_USE_FLAGS    15    /* Used to define flag array size */

/* Definitions for non-ASCII keycodes */

#define SETUP_KEY_CODE    0x80
#define RESET_KEY_CODE    0x81
#define TEST_KEY_CODE     0x82
#define MAIN_KEY_CODE     0x83
#define DATA_KEY_CODE     0x84
#define VIEW_KEY_CODE     0x85
#define PRINT_KEY_CODE    0x86
#define HORNDOWN_KEY_CODE 0x87
#define RUN_KEY_CODE      0x88
#define RIGHT_KEY_CODE    0x89
#define LEFT_KEY_CODE     0x8A
#define PG_UP_KEY_CODE    0x8B
#define PG_DOWN_KEY_CODE  0x8C
#define UP_KEY_CODE       0x8D
#define DOWN_KEY_CODE     0x8E

/* Definitions for control messages */

#define UPDATE_DISPLAY_CODE        0x01

/* Definition of data field in TIMER_EXPIRED messages */

#define TIMER_NUM_FIELD    (0xF0 << MESSAGE_DATA_BITPOS)
#define TIMER_NUM_BITPOS   MESSAGE_DATA_BITPOS + 4
#define TIMER_ID_FIELD     (0x0F << MESSAGE_DATA_BITPOS)
#define TIMER_ID_BITPOS    MESSAGE_DATA_BITPOS

/* Definitions for message types */

#define CHR_RECEIVED_MSG   1
#define SELECT_MSG         2
#define CONTROL_MSG        3
#define SPECIAL_MSG        4


#define ENTER_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (0x0D << MESSAGE_CODE_BITPOS))
#define SETUP_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (SETUP_KEY_CODE << MESSAGE_CODE_BITPOS))
#define RESET_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (RESET_KEY_CODE << MESSAGE_CODE_BITPOS))
#define TEST_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (TEST_KEY_CODE << MESSAGE_CODE_BITPOS))
#define MAIN_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (MAIN_KEY_CODE << MESSAGE_CODE_BITPOS))
#define DATA_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (DATA_KEY_CODE << MESSAGE_CODE_BITPOS))
#define VIEW_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (VIEW_KEY_CODE << MESSAGE_CODE_BITPOS))
#define PRINT_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (PRINT_KEY_CODE << MESSAGE_CODE_BITPOS))
#define HORNDOWN_KEY      ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (HORNDOWN_KEY_CODE << MESSAGE_CODE_BITPOS))
#define RUN_KEY           ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (RUN_KEY_CODE << MESSAGE_CODE_BITPOS))
#define GOBACK_KEY        ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (0x1B << MESSAGE_CODE_BITPOS))
#define RIGHT_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (RIGHT_KEY_CODE << MESSAGE_CODE_BITPOS))
#define LEFT_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (LEFT_KEY_CODE << MESSAGE_CODE_BITPOS))
#define UP_KEY            ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (UP_KEY_CODE << MESSAGE_CODE_BITPOS))
#define DOWN_KEY          ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (DOWN_KEY_CODE << MESSAGE_CODE_BITPOS))
#define PG_UP_KEY         ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (PG_UP_KEY_CODE << MESSAGE_CODE_BITPOS))
#define PG_DOWN_KEY       ((CHR_RECEIVED_MSG << MESSAGE_TYPE_BITPOS) | (PG_DOWN_KEY_CODE << MESSAGE_CODE_BITPOS))

#define UPDATE_DISPLAY    ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x01 << MESSAGE_CODE_BITPOS) | (1 << MESSAGE_USE_ID_BITPOS))
#define UPDATE_TOP_LINE   ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x02 << MESSAGE_CODE_BITPOS) | (2 << MESSAGE_USE_ID_BITPOS))
#define UPDATE_LINE_2     ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x03 << MESSAGE_CODE_BITPOS) | (3 << MESSAGE_USE_ID_BITPOS))
#define UPDATE_LINE_4     ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x05 << MESSAGE_CODE_BITPOS) | (5 << MESSAGE_USE_ID_BITPOS))
#define TERM_DATA_OUTPUT  ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x06 << MESSAGE_CODE_BITPOS))
#define UPDATE_TERM_ALARM ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x07 << MESSAGE_CODE_BITPOS) | (7 << MESSAGE_USE_ID_BITPOS))
#define ESTOP_MSG_ON      ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x08 << MESSAGE_CODE_BITPOS))
#define ESTOP_MSG_OFF     ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x09 << MESSAGE_CODE_BITPOS))
#define POWER_OFF         ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x0B << MESSAGE_CODE_BITPOS))
#define ESTOP_PRESSED     ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x0C << MESSAGE_CODE_BITPOS))
#define ESTOP_RELEASED    ((CONTROL_MSG << MESSAGE_TYPE_BITPOS) | (0x0D << MESSAGE_CODE_BITPOS))

#define NO_PB_PRESSED     ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x01 << MESSAGE_CODE_BITPOS))
#define ONE_PB_PRESSED    ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x02 << MESSAGE_CODE_BITPOS))
#define BOTH_PB_PRESSED   ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x03 << MESSAGE_CODE_BITPOS))
#define PART_CONTACT      ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x04 << MESSAGE_CODE_BITPOS))
#define TRIGGER_ON        ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x05 << MESSAGE_CODE_BITPOS))
#define TRIGGER_OFF       ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x06 << MESSAGE_CODE_BITPOS))
#define DOOR_OPEN         ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x07 << MESSAGE_CODE_BITPOS))
#define DOOR_CLOSED       ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x08 << MESSAGE_CODE_BITPOS))
#define UPPER_LIMIT_ON    ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x09 << MESSAGE_CODE_BITPOS))
#define UPPER_LIMIT_OFF   ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x0A << MESSAGE_CODE_BITPOS))
#define ECYCLE_ABORT_ON   ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x0B << MESSAGE_CODE_BITPOS))
#define ECYCLE_ABORT_OFF  ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x0C << MESSAGE_CODE_BITPOS))
#define TIMER_EXPIRED     ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x0D << MESSAGE_CODE_BITPOS))
#define BAD_TRIGGER       ((SPECIAL_MSG << MESSAGE_TYPE_BITPOS) | (0x0E << MESSAGE_CODE_BITPOS))


/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

UINT32 RcvMsg( UINT16 Flag );
UINT32 WaitMessage( UINT32 TimeWait );
BOOLEAN KeyAvailable( UINT16 Flag );
void ClearKeypadBuffer( UINT16 Flag );
void SendMsg(UINT32 Msg);
UINT16 Get_GetMsgFlag(void);
BOOLEAN ProcessControlMessage( UINT8 Message );
UINT8  GetMsg(UINT16);
void SendFakeKeyPress(KEY_CODE_TYPE Key);
UINT32 ConvertOldToNew( KEY_CODE_TYPE Key, UINT8 Extra );
UINT8 ConvertNewToOld( UINT32 Msg, UINT8 *Extra );
void PrintMessageLog(void);

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

extern UINT8 MsgExtra;         /* Extra info on last message stored here */
extern UINT8 MessageUseFlags[NUM_MSG_USE_FLAGS];
