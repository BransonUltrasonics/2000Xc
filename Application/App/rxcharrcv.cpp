/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/rxcharrcv.cpp_v   1.7   08 Jan 2015 03:18:28   AnPawar  $*/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/rxcharrcv.cpp_v  $
 * 
 *    Rev 1.7   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.6   28 Nov 2014 07:40:32   rjamloki
 * Removed unused variables.
 * 
 *    Rev 1.5   10 Nov 2014 04:58:10   AnPawar
 * CommAsciiCharRcvd() function changed
 * 
 *    Rev 1.4   06 Oct 2014 06:44:10   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.3   03 Oct 2014 06:02:42   rjamloki
 *  CkQSend() function renamed to SendMessageWithWait()
 * 
 *    Rev 1.2   26 Sep 2014 03:11:08   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.1   18 Aug 2014 02:25:46   rjamloki
 * Header correction for compilation
 * 
 *    Rev 1.0   18 Aug 2014 01:31:18   rjamloki
 * Initial revision.
 */

#include "rxcharrcv.h"           /* Own interface                        */
#include "ipscdmsg.h"
#include "ipsatype.h"
#include "preset.h"
#include "serial.h"
#include "iotest332.h"
#include "ascii.h"
#include "RemoteSerialCommandHandlerTask.h"
#include "DUPS_ManagerTask.h"

/*
 ------------------------------- EXTERNAL DATA ---------------------------------*/
                                                                 
extern UINT8  RcvChecksum;
extern BOOLEAN OnboardDiag;
extern BOOLEAN PoweredUp;
/*
 ------------------------------- LOCAL DEFINES ---------------------------------
*/
#define MESSAGECOUNT 1
#define STARTCOUNT 4
#define START_OF_MESSAGE 0x10  /* DLE */
#define DLE              0x10  /* DLE */
#define STX              0x02  /* STX */
#define END_OF_MESSAGE   0x03  /* ETX */
#define ETX              0x03  /* ETX */
/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                                      
struct RcBuff
   {
   UINT16            Function;    /* Host Command ID      */
   SINT16            Count;       /* Number of chars in receive buffer */
   UINT8             CharPtr[sizeof(SETUPS_Ver1200)]; /* Pointer into current buffer   */
   UINT8             CheckSum;    /*  */
   } ReceiveBuffer;

HOST_COMMAND_MSG  ReadHostMsg;
UINT32 HostPtId;      /* Receiver partition ID */
UINT16 CommandStarted = FALSE;

/*
 -------------------------------- GLOBAL DATA ----------------------------------
*/    

RCV_BUFFER_STATUS_TYPE RcvBufferStatus = WAIT_FOR_START;
UINT16 MessageLength;
UINT16 ReceiveCounter = 0;
UINT8 *HostDataPtr;      /* Current destination of data            */

/*
 --------------------------------- CODE ----------------------------------------
*/                

void CommAsciiCharRcvd( UINT8  ByteReceived , BOOLEAN EchoChar)
{

    /*
    * Copy the received characters into the partition buffer. Note that we
    * will normally receive only one character at a time but that the
    * PC UART may buffer up to four characters.
    */
	DUPS_MSGBUF OutMsg;
	memset(&OutMsg, 0, sizeof(DUPS_MSGBUF));
   if (OnboardDiag == TRUE)                
      DiagnosticInput(ByteReceived, EchoChar);       /* On board diagnostics enabled */

   else        /* Host command */
   {
      switch(RcvBufferStatus)
      {
         case WAIT_FOR_START:
           if(ByteReceived == DLE)
            {
               RcvBufferStatus = WAIT_FOR_STX;
               CommandStarted = TRUE;
            }
            else if ((PoweredUp == FALSE) && (ByteReceived ==  ESC)) {
               OnboardDiag = TRUE;             /* diagnostics through the serial port */
				OutMsg.mt = DUPS_MSGSENABLEDIAGNOSTIC;
				DUPS_ManagerTask::thisPtr->DUPS_ManagerTaskQ.Write(0, OutMsg, 0);
            }
            break;

         case WAIT_FOR_STX:
            if(ByteReceived == STX)
            {
               RcvBufferStatus = GET_MESSAGE_SIZE;
               ReceiveCounter = 0;
               RcvChecksum = 0;
            }
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;

         case GET_MESSAGE_SIZE:
            switch(ReceiveCounter)
            {
               case 0:
                  MessageLength = ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  ReceiveCounter++;
                  break;
               case 1:
                  /* Subtract 4 to get number of data bytes. */
                  ReceiveBuffer.Count = MessageLength*256 + ByteReceived - 4;
                  RcvChecksum ^= ByteReceived;
                  RcvBufferStatus = GET_MESSAGE_TYPE;
                  ReceiveCounter = 0;
                  break;
            }
            break;

         case GET_MESSAGE_TYPE:
            switch(ReceiveCounter)
            {
               case 0:
                  MessageLength = ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  ReceiveCounter++;
                  break;
               case 1:
                  ReceiveBuffer.Function = MessageLength*256 + ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  if(ReceiveBuffer.Count)
                     RcvBufferStatus = START_TO_ACCUMULATE;
                  else
                  {
                     RcvBufferStatus = WAIT_FOR_CHECKSUM;
                     /* Send a NULL to command.c if there are no data bytes. */
                     ReadHostMsg.byte_count = 1;
                     ReceiveBuffer.CharPtr[0] = 0;
                  }
                  ReceiveCounter = 0;
                  break;
            }
            break;

         case START_TO_ACCUMULATE:
            ReceiveBuffer.CharPtr[ReceiveCounter++] = ByteReceived;
            RcvChecksum ^= ByteReceived;
            if(ReceiveCounter == ReceiveBuffer.Count)
            {
               /* NULL terminate data sent to command.c */
               ReceiveBuffer.CharPtr[ReceiveCounter++] = NULL;
               ReadHostMsg.byte_count = ReceiveCounter;
               RcvBufferStatus = WAIT_FOR_CHECKSUM;
            }
            break;

         case WAIT_FOR_CHECKSUM:
            ReceiveBuffer.CheckSum = ByteReceived;
            if(ByteReceived != RcvChecksum)
               ReceiveBuffer.Function = CHECKSUM_ERROR;
            RcvBufferStatus = WAIT_FOR_DLE;
            break;

         case WAIT_FOR_DLE:
            if(ByteReceived == DLE)
               RcvBufferStatus = WAIT_FOR_END_MESSAGE;
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;           

         case WAIT_FOR_END_MESSAGE:
            if(ByteReceived == ETX)
               RcvBufferStatus = SEND_BUFFER;
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;
         
         default:
            RcvBufferStatus = WAIT_FOR_START;
            break;

      }
      /*
       * Send buffer if its complete
       */
      if ( RcvBufferStatus == SEND_BUFFER ){
         RcvBufferStatus = WAIT_FOR_START;
         CommandStarted = FALSE;                                                                        
         ReceiveCounter = 0;


         ReadHostMsg.common.opcode        = (MSG_OPCODE_TYPE)ReceiveBuffer.Function;
         ReadHostMsg.data_pointer         = HostDataPtr;
         ReadHostMsg.common.pointer_flag  = DATA_PTR_DEALLOC;
         ReadHostMsg.partition_id         = HostPtId;
         memcpy(HostDataPtr,&ReceiveBuffer.CharPtr,ReadHostMsg.byte_count);
         ReadHostMsg.byte_count           = ReceiveBuffer.Count;

         RemoteSerialCommandHandlerTask::thisPtr->RTCHTaskQ.WriteRetry(0, *((RSCH_MSG_QUEUE_TYPE*) &ReadHostMsg), 100);
      }
   }
}


void InitReceiveBuffer(void)
{
    HostDataPtr = new  UINT8[128 * 16 * 8];
}

