/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/getmsg.cpp_v   1.16   08 Jan 2015 03:18:22   AnPawar  $ */

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/getmsg.cpp_v  $
 * 
 *    Rev 1.16   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.15   28 Nov 2014 07:35:48   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.14   06 Oct 2014 06:33:52   AnPawar
 * SendMsg() function changed.Using cygos function for queue read write.
 * 
 *    Rev 1.13   03 Oct 2014 05:57:58   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.12   26 Sep 2014 03:14:24   rjamloki
 * Removed psos references
 * 
 *    Rev 1.11   28 Jul 2014 12:36:38   rjamloki
 * psos.h removed
 * 
 *    Rev 1.10   11 Jun 2014 11:31:34   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.9   21 May 2014 10:47:56   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.8   21 May 2014 03:05:48   rjamloki
 * coverity fix
 * 
 *    Rev 1.7   26 Mar 2014 12:15:56   rjamloki
 * SendMsg() function changed,SendFakeKeyPress() function changed
 * 
 *    Rev 1.6   06 Mar 2014 11:03:48   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:24   rjamloki
 * Screens and PDf working
 *
 *    Rev 1.4   10 Feb 2014 04:59:36   rjamloki
 * Preset changes to support 1000 preset.
 *  
 *    Rev 1.3   03 Jan 2014 08:45:26   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Module name: Manage Display

 Filename:  getmsg.c was fpsmangr.c


 Written by: Mark Lazarewicz
 Date: 1/30/96
 Language: Microtec "C"
 ------------------------------ DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
 */
#include "qdef.h"
#include "genrlmsg.h"
#include "ticks.h"
#include "fpkp_msg.h"
#include "keypad.h"
#include "menu.h"
#include "getmsg.h"
#include "snsrcalb.h"
#include "stdio.h"

/* For qvga support */
#include "RVTSHandlerTask.h"
#include "opcodes.h"
#include "UndefPrintf.h"
#include "FrontPanelStateCoordinatorTask.h"
/*
 ---------------------------- FUNCTIONS PROTOTYPES -------------------------
 */

void ShowEstopMessageOn(void); /* External functions */
void ShowEstopMessageOff(void);

/*
 ------------------------------- EXTERNAL DATA ---------------------------------
 */

/*
 ------------------------------- LOCAL DEFINES ---------------------------------
 */

struct MessageLogItem /* Def of a message log item */
{
      UINT32 Message; /* Message being logged */
      UINT32 Time; /* Time it was read */
      UINT32 Sender; /* Address of message sender */
      UINT32 Receiver; /* Return address from GetMsg() call */
};

#define MSG_LOG_SIZE 100      /* Number of messages to save in log */

/*
 ------------------------------- GLOBAL DATA ---------------------------------
 (scope is global to ALL files)
 */

extern BOOLEAN VGAHornDown;
extern UINT32 ReadOnlyTimer;

UINT8 MsgExtra; /* Kludge.  This is global storage for extra byte */
/* that comes with 8-bit messages and provides */
/* additional information. */

struct MessageLogItem MessageLog[MSG_LOG_SIZE]; /* Saves info last messages */
UINT16 MsgLogInPtr = 0; /* Pointer into circular log buffer */
BOOLEAN MsgLogWrapped = FALSE;

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
 */

static void LogMenuMessage(UINT32 Message, UINT32 Sender, UINT32 Receiver);
static void PrintMsgLogItem(UINT16 Item, UINT32 TimeZero);

/*
 -------------------------------- PRIVATE GLOBAL DATA ----------------------------------
 */
static UINT16 GetMsgFlag;
static struct MenuMessage HoldingMsg; /* Temporary storage for chr */
/* read from queue but not */
/* used by calling func yet. */
static BOOLEAN GotHoldingMsg = FALSE;

/* Each flag in the array below is TRUE if its corresponding message is in */
/* the message queue. */

UINT8 MessageUseFlags[NUM_MSG_USE_FLAGS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

/*
 --------------------------------- CODE ----------------------------------------
 */

/* IT IS VERY IMPORTANT THAT THE FUNCTIONS IN THIS FILE BE CALLED ONLY FROM */
/* ONE TASK.  CALLING FROM MULTIPLE TASKS CAN CAUSE UNPREDICTABLE RESULTS! */

UINT32 RcvMsg(UINT16 Flag)
/****************************************************************************/
/*                                                                          */
/* Retrieves the next message for processing by the menu task.  The         */
/* "Flag" parameter is used to find the return address on the stack, which  */
/* is just before &Flag, as well as for its normal use.                     */
/*                                                                          */
/****************************************************************************/
{
   UINT32 QWriteStatus;
   UINT32 MsgUseId;
   struct MenuMessage MenuMsg; /* Full message */

   GetMsgFlag = Flag; /* TRUE:called by DisplayMenu,        */
   /* FALSE:called by DealWithSelectKey  */

   if (GotHoldingMsg) {
      MenuMsg = HoldingMsg;
      GotHoldingMsg = FALSE;
   }
   else {
	  QWriteStatus = FrontPanelStateCoordinatorTask::thisPtr->FPSCTaskQ.Read(0, *((MenuMessage*) &MenuMsg), 0);
      if (!QWriteStatus) //ERR_NOMSG)  /* If no message, wait for one */
      {
    	 QWriteStatus = FrontPanelStateCoordinatorTask::thisPtr->FPSCTaskQ.Read(0, *((MenuMessage*) &MenuMsg), 0);
         MenuMsg.Msg |= MESSAGE_NEW; /* Note: Had to wait for this msg */
      }
   }

   /* If this message is one that should only appear in the buffer once, */
   /* clear flag now so it can be put in the buffer again. */

   MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   if (MsgUseId)
      MessageUseFlags[MsgUseId - 1] = 0; /* MsgUseId=0 when no flag needed */

   /* Before returning message, log it.  Get address that GetMsg() will     */
   /* return to by finding address of Flag on the stack and backing up to   */
   /* function return address.  This is three words: 1 for top half of Flag */
   /* (it's a UINT16 in 32-bits of space), 2 for return address.            */

   LogMenuMessage(MenuMsg.Msg, MenuMsg.Sender, *((UINT32*) (((UINT16*) &Flag) - 3)));

   return (MenuMsg.Msg);
}

UINT32 WaitMessage(UINT32 TimeWait)
/****************************************************************************/
/*                                                                          */
/* Waits the specified time for a message to be available.  If a messasge   */
/* comes in that is a control message, it will be processed locally and the */
/* routine will continue to wait for other messasges up to the time limit.  */
/* If a message comes in that can't be processed locally, it is stored for  */
/* later retrieval by a RcvMsg() call, and this function exits.             */
/*                                                                          */
/* Function returns the amount of time left to wait, in tick units.   		*/
/* This is zero if exit was caused by timeout, nonzero if caused by a       */
/* message that couldn't be processed.                                      */
/*                                                                          */
/* This function should be used in place of RTOS::DelayMs(), which may prevent */
/* the menu system from responding to important messages.                   */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotMsg, Quit;
   SINT32 FinalTime, TimeTicks, TimeRemaining;
   UINT32 QReadStatus;
   UINT32 MsgUseId;
   struct MenuMessage MenuMsg;

   /* Compute time at which to stop looking for a message */

   FinalTime = ReadOnlyTimer + TICKS_TO_MS( TimeWait );
   GotMsg = FALSE;
   Quit = FALSE;

   TimeRemaining = FinalTime - ReadOnlyTimer;

   while ((TimeRemaining > 0) && !GotMsg && !Quit) {
      if (GotHoldingMsg) {
         MenuMsg = HoldingMsg;
         GotHoldingMsg = FALSE;
         GotMsg = TRUE;
      }
      else { /* Compute time left to go, wait this long for a message */

         TimeTicks = MS_TO_TICKS( TimeRemaining );
         QReadStatus = FrontPanelStateCoordinatorTask::thisPtr->FPSCTaskQ.Read(0, *((MenuMessage*) &MenuMsg), 0);

         if (QReadStatus) {
            GotMsg = TRUE;
         }
         else {
            GotMsg = FALSE;
            Quit = TRUE; /* Timed out, don't even bother to check time */
         } /* Quit = TRUE prevents calls to q_receive with */
      } /* very short timeouts if clock and */
      /* ReadOnlyTimer are slightly out of sync */

      if (GotMsg) /* If we got a message, try to process here */
      {
         MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
         if (MsgUseId)
            MessageUseFlags[MsgUseId - 1] = 0; /* MsgUseId=0 when no flag needed */

         if (ProcessControlMessage(ConvertNewToOld(MenuMsg.Msg, &MsgExtra))) {
            GotMsg = FALSE; /* Processed, will check for more */
            LogMenuMessage(MenuMsg.Msg, MenuMsg.Sender, (UINT32) WaitMessage); /* Message used here, log */
         }
      }

      TimeRemaining = FinalTime - ReadOnlyTimer;
   }

   if (GotMsg) /* Save message where it can be retrieved */
   {
      HoldingMsg = MenuMsg;
      GotHoldingMsg = TRUE;
   }

   if (Quit || TimeRemaining < 0)
      TimeRemaining = 0; /* Result must be unsigned, should be */
   /* zero if we timed out */
   return (MS_TO_TICKS( TimeRemaining));
}

BOOLEAN KeyAvailable(UINT16 Flag)
/****************************************************************************/
/*                                                                          */
/* Returns FALSE if no keys available, TRUE if there are keys available.    */
/* Unfortunately, to find out if queue holding keypresses is empty, must    */
/* try to read something.  May then end up with a character we don't know   */
/* what to do with.  In this case, it gets put in HoldingMsg and returned   */
/* by GetMsg() ahead of any other keypresses.                               */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotMsg;
   bool QReadStatus;
   struct MenuMessage MenuMsg;

   GetMsgFlag = Flag; /* TRUE:called by DisplayMenu,        */
   /* FALSE:called by DealWithSelectKey  */

   if (GotHoldingMsg) /* Got a chr right here, so certainly available */
      GotMsg = TRUE;
   else {
      /* Check keypad queue and return whether keypress or not */
	   QReadStatus = FrontPanelStateCoordinatorTask::thisPtr->FPSCTaskQ.Read(0, *((MenuMessage*) &MenuMsg), 0);

      if (QReadStatus) 
      {
         GotMsg = TRUE;
         HoldingMsg = MenuMsg;
         GotHoldingMsg = TRUE;
      }
      else /* If queue empty, just return */
         GotMsg = FALSE;

   }
   return (GotMsg);
}

void ClearKeypadBuffer(UINT16 Flag)
/****************************************************************************/
/*                                                                          */
/* This function reads all the keys that are in the key queue and throws    */
/* them away. Exception: If one of these is the Test key, this is NOT       */
/* thrown away, see explanation below.                                      */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotKey;
   BOOLEAN TestFlag;
   UINT8 NewKey = MAX_NUMBER_OF_KEY_CODES;//initialize to some default value
   UINT8 MsgUseIndex;

   TestFlag = FALSE;

   do {
      GotKey = KeyAvailable(Flag);
      if (GotKey)
         NewKey = GetMsg(Flag);

      /* TestKey is at present processed initially by WeldManager, which    */
      /* will go ahead and put the system in test mode before the menu task */
      /* knows what's happening. WeldManager then sends a Test keypress to  */
      /* the menu task. It's very important not to throw this out or the    */
      /* system could end up in Test mode with the menus showing weld mode. */
      /* So, if we find a TestKey here, we stuff it back into the queue     */
      /* after clearing the other keypresses. */

      if (NewKey == TestKey)
         TestFlag = TRUE;

   } while (GotKey);

   /* No messages now in buffer, clear all use flags */

   for (MsgUseIndex = 0; MsgUseIndex < NUM_MSG_USE_FLAGS; MsgUseIndex++)
      MessageUseFlags[MsgUseIndex] = 0;

   if (TestFlag)
      SendMsg(TEST_KEY);
}

UINT16 old_mode;

void SendMsg(UINT32 Msg)
/****************************************************************************/
/*                                                                          */
/* Stores the given message in the message queue for the menu task.         */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN DoSend;
   UINT32 MsgUseId;
   UINT32 MsgType;
   bool QWriteStaus;
   struct MenuMessage MenuMsg;
   VGAMENUTASK_MSG VGAmenuMsg;

   QWriteStaus = false;

   MenuMsg.Msg = Msg & ~MESSAGE_NEW;
   MenuMsg.Sender = *((&Msg) - 1); /* Gets return address in SendMsg() caller */
   MenuMsg.Unused1 = 0;
   MenuMsg.Unused2 = 0;

   MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   MsgType = (MenuMsg.Msg & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;

   /* If this field of message has a nonzero # in it, then this message */
   /* should only be placed in the buffer if it isn't already there.  Check */
   /* appropriate flag to see if it is, don't send in this case.  Test must */
   /* be done with interrupts off in case message is placed in buffer by */
   /* another task after test but flag set TRUE. */

   if (MsgUseId) {
      SR sr = EnterCritical();
      if (!MessageUseFlags[MsgUseId - 1]) {
         MessageUseFlags[MsgUseId - 1] = TRUE;
         DoSend = TRUE;
      }
      else
         DoSend = FALSE;
      ExitCritical(sr);
   }
   else
      DoSend = TRUE;

   if (DoSend) {
      if (VGAHornDown) {
         if (MsgType == CONTROL_MSG || MsgType == SPECIAL_MSG) {
            VGAmenuMsg.common.opcode = OP_VGAMENUTASK_MSG;
            VGAmenuMsg.message = MenuMsg.Msg;
            QWriteStaus = RVTSHandlerTask::thisPtr->RVTSTaskQ.Write(0, *((RVTS_MSG_QUEUE_TYPE*) &VGAmenuMsg), 0);
         }
      }
      else {
    	  QWriteStaus = FrontPanelStateCoordinatorTask::thisPtr->FPSCTaskQ.Write(0, *((MenuMessage*) &MenuMsg), 0);
      }
      if ((QWriteStaus == false) && MsgUseId) /* If queue was full, */
               MessageUseFlags[MsgUseId - 1] = 0; /* msg not really put in. */
   }
}

UINT16 Get_GetMsgFlag(void)
{
   return (GetMsgFlag);
}

BOOLEAN ProcessControlMessage(UINT8 Message)
/****************************************************************************/
/*                                                                          */
/* Provides default processing for control messages.  Takes a message code  */
/* as input, returns TRUE if the message was successfully processed.  This  */
/* routine should be called to handle any control messages not processed    */
/* explicitly by a particular menu.                                         */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN RetVal;

   switch (Message) {
   case TERMDATAOUTPUT:
      RetVal = TRUE;
      break;

   case UPDATETERMALARM:
      RetVal = TRUE;
      break;

   case ESTOPMSGON:
      ShowEstopMessageOn();
      RetVal = TRUE;
      break;

   case ESTOPMSGOFF:
      ShowEstopMessageOff();
      RetVal = TRUE;
      break;

   case CALIBRATION_ABORTED:
      ShowCalibrationAbort();
      RetVal = TRUE;
      break;

   default:
      RetVal = FALSE;
   }

   return (RetVal);
}

UINT8 GetMsg(UINT16 Flag)
{
   return (ConvertNewToOld(RcvMsg(Flag), &MsgExtra));
}

void SendFakeKeyPress(KEY_CODE_TYPE Key)
{
   SendMsg(ConvertOldToNew(Key, 0));
}

static void LogMenuMessage(UINT32 Message, UINT32 Sender, UINT32 Receiver)
{
   if (Message != UPDATE_TERM_ALARM) /* Don't log these, too many */
   {
      MessageLog[MsgLogInPtr].Message = Message;
      MessageLog[MsgLogInPtr].Time = ReadOnlyTimer;
      MessageLog[MsgLogInPtr].Sender = Sender;
      MessageLog[MsgLogInPtr++].Receiver = Receiver;

      if (MsgLogInPtr >= MSG_LOG_SIZE) {
         MsgLogInPtr = 0;
         MsgLogWrapped = TRUE;
      }
   }
}

UINT32 ConvertOldToNew(KEY_CODE_TYPE Key, UINT8 Extra)
{
   UINT32 Msg;
   UINT32 MsgType;
   UINT32 MsgCode;
   UINT32 MsgData;
   UINT32 MsgUseId;

   MsgData = Extra;
   MsgUseId = 0;

   if (Key > FIRSTCONTROLMESSAGE) {
      MsgType = CONTROL_MSG;
      MsgCode = Key - UPDATEDISPLAY + UPDATE_DISPLAY_CODE;

      /* Set use id for messages that should only be in */
      /* buffer once at any given time. */

      if (Key >= UPDATEDISPLAY && Key <= UPDATETERMALARM && Key != TERMDATAOUTPUT)
         MsgUseId = Key - UPDATEDISPLAY + 1;
   }
   else {
      MsgType = CHR_RECEIVED_MSG; /* This usually true from here on */

      if (Key <= KEY_9)
         MsgCode = Key + '0';
      else if (Key >= SetupKey && Key <= RunKey) {
         if (Key == GoBackKey)
            MsgCode = 0x1B; /* ESC */
         else
            MsgCode = Key - SetupKey + SETUP_KEY_CODE;
      }
      else if (Key >= Select1Key && Key <= Select3Key) {
         MsgType = SELECT_MSG;
         MsgCode = Key - Select1Key + 1;
      }
      else if (Key >= RightKey && Key <= DownKey)
         MsgCode = Key - RightKey + RIGHT_KEY_CODE;
      else if (Key >= TermUpKey && Key <= TermDownKey)
         MsgCode = Key - TermUpKey + UP_KEY_CODE;
      else if (Key == DPointKey)
         MsgCode = '.';
      else if (Key == IncKey)
         MsgCode = '+';
      else if (Key == DecKey)
         MsgCode = '-';
      else if (Key == ClearKey)
         MsgCode = 8; /* backspace */
      else if (Key == EnterKey)
         MsgCode = 13; /* carriage return */
      else if (Key == TermDataKey)
         MsgCode = DATA_KEY_CODE;
      else if (Key == TermSelectKey) {
         MsgType = SELECT_MSG;
         MsgCode = 0; /* single select key */
      }
      else
         MsgCode = 0;
   }

   Msg = (MsgType << MESSAGE_TYPE_BITPOS) | (MsgCode << MESSAGE_CODE_BITPOS) | (MsgData << MESSAGE_DATA_BITPOS)
         | (MsgUseId << MESSAGE_USE_ID_BITPOS);

   return (Msg);
}

UINT8 ConvertNewToOld(UINT32 Msg, UINT8 *Extra)
{
   UINT8 Key;
   UINT8 MsgType;
   UINT8 MsgCode;

   MsgType = (Msg & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;
   MsgCode = (Msg & MESSAGE_CODE_FIELD) >> MESSAGE_CODE_BITPOS;
   *Extra = (Msg & MESSAGE_DATA_FIELD) >> MESSAGE_DATA_BITPOS;

   switch (MsgType) {
   case CONTROL_MSG:
      if (!MsgCode)
         Key = NOKEY;
      else
         Key = MsgCode - UPDATE_DISPLAY_CODE + UPDATEDISPLAY;

      break;

   case SELECT_MSG:
      if (!MsgCode) /* individual select key from terminal */
         Key = TermSelectKey;
      else
         Key = MsgCode + Select1Key - 1;
      break;

   case CHR_RECEIVED_MSG:
      if (MsgCode >= '0' && MsgCode <= '9')
         Key = MsgCode - '0' + KEY_0;
      else if (MsgCode >= SETUP_KEY_CODE && MsgCode <= RUN_KEY_CODE) {
         if (MsgCode == DATA_KEY_CODE)
            Key = TermDataKey;
         else
            Key = MsgCode - SETUP_KEY_CODE + SetupKey;
      }
      else if (MsgCode >= RIGHT_KEY_CODE && MsgCode <= PG_DOWN_KEY_CODE)
         Key = MsgCode - RIGHT_KEY_CODE + RightKey;
      else if (MsgCode >= UP_KEY_CODE && MsgCode <= DOWN_KEY_CODE)
         Key = MsgCode - UP_KEY_CODE + TermUpKey;
      else if (MsgCode == '.')
         Key = DPointKey;
      else if (MsgCode == '+')
         Key = IncKey;
      else if (MsgCode == '-')
         Key = DecKey;
      else if (MsgCode == 8) /* backspace */
         Key = ClearKey;
      else if (MsgCode == 13) /* carriage return */
         Key = EnterKey;
      else if (MsgCode == 0x1B) /* ESC key */
         Key = GoBackKey;
      else
         Key = NOKEY;
      break;

   default:
      Key = NOKEY;
   }
   return (Key);
}

void PrintMessageLog(void)
/****************************************************************************/
/*                                                                          */
/* Prints last MSG_LOG_SIZE messages logged, not including messages which   */
/* cause the ALARM message to blink. Printout shows time that message was   */
/* received (measured from time of first message), message code, and the    */
/* address of the message sender and receiver.                              */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;
   UINT32 TimeZero;

   if (MsgLogWrapped) {
      TimeZero = MessageLog[MsgLogInPtr].Time;

      for (x = MsgLogInPtr; x < MSG_LOG_SIZE; x++)
         PrintMsgLogItem(x, TimeZero);
   }
   else
      TimeZero = MessageLog[0].Time;

   for (x = 0; x < MsgLogInPtr; x++)
      PrintMsgLogItem(x, TimeZero);

}

static void PrintMsgLogItem(UINT16 Item, UINT32 TimeZero)
/****************************************************************************/
/*                                                                          */
/* Prints the given item from the message log.                              */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Item     - Index of item in message log to print.                     */
/*    TimeZero - Time of first message, from which to measure time of later */
/*               messages.                                                  */
/*                                                                          */
/****************************************************************************/
{
	Item = 0;
	TimeZero = 0;
}
