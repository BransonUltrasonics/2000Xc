/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/rxcharrcv.h_v   1.1   18 Aug 2014 02:43:56   rjamloki  $*/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/rxcharrcv.h_v  $
 * 
 *    Rev 1.1   18 Aug 2014 02:43:56   rjamloki
 * Header correction for compilation
 * 
 *    Rev 1.0   18 Aug 2014 01:30:44   rjamloki
 * Initial revision.
 */
#include "portable.h"
typedef enum
   {
   SEND_BUFFER = 0u,
   WAIT_FOR_START,
   WAIT_FOR_STX,
   GET_MESSAGE_SIZE,
   GET_MESSAGE_TYPE,
   START_TO_ACCUMULATE,
   WAIT_FOR_CHECKSUM,
   WAIT_FOR_DLE,
   WAIT_FOR_END_MESSAGE,
   CONTINUE_TO_ACCUMULATE,
   RCV_BUFFER_SIZER = 255,
   } RCV_BUFFER_STATUS_TYPE;


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void InitReceiveBuffer(void);
void CommAsciiCharRcvd(UINT8 ByteReceived , BOOLEAN EchoChar = TRUE);
