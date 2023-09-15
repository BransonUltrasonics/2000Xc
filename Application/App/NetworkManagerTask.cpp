/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/NetworkManagerTask.cpp_v   1.23   16 Apr 2015 07:18:02   rjamloki  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/NetworkManagerTask.cpp_v  $
 * 
 *    Rev 1.23   16 Apr 2015 07:18:02   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.22   27 Mar 2015 15:12:36   RJamloki
 * Changes after serial communication is also incorporated in determining SBC Timeout
 * 
 *    Rev 1.21   11 Feb 2015 06:30:54   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.20   21 Jan 2015 09:38:20   amaurya
 * making SBCReadyFlag true,if we receive any command from sbc.
 * 
 *    Rev 1.19   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.18   28 Nov 2014 07:38:38   rjamloki
 * changed to remove warning "unused variable".
 * 
 *    Rev 1.17   17 Nov 2014 10:40:38   RJamloki
 * Changes for checking SBC Idle
 * 
 *    Rev 1.16   10 Nov 2014 04:54:20   AnPawar
 * NetworkManagerTask::Run() function changed.Added function header . 12.F review change. 
 * 
 *    Rev 1.15   06 Oct 2014 06:40:50   AnPawar
 * removed ck_qsend.h file inclusion.Using cygos function for queue read write.
 * 
 *    Rev 1.14   03 Oct 2014 05:58:04   rjamloki
 * unction renamed q_send() to SendMessage() 
 * 
 *    Rev 1.13   05 Sep 2014 05:01:26   rjamloki
 * Removed redundant globals. 
 * 
 *    Rev 1.12   11 Jun 2014 11:58:46   rjamloki
 * VGAMenResponse size allocated in constructor
 * 
 *    Rev 1.11   21 May 2014 10:48:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.10   21 May 2014 03:34:12   rjamloki
 * removed redundant ram buffers
 * 
 *    Rev 1.9   07 May 2014 10:24:30   rjamloki
 * Code cleanup and added some checks for Network interface start.
 * 
 *    Rev 1.8   21 Apr 2014 13:39:22   rjamloki
 * Interface port for serial connection changed to 0
 * 
 *    Rev 1.7   26 Mar 2014 12:27:14   rjamloki
 * TransmitNAK() function changed
 * 
 *    Rev 1.6   06 Mar 2014 11:03:56   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.5   05 Mar 2014 13:56:34   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.4   10 Feb 2014 04:59:46   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:45:40   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

#include "NetworkManagerTask.h"
#include "PortManagerTask.h"
#include "Serial.h"
#include "vga_uart.h"
#include "command.h"
#include "stdio.h"
#include "Socket.h"
#include "ASSERT.h"
#include "Ethernet.h"
#include "CyGOS.h"
#include "FIFO.h"
#include "TcpIp.h"
#include "RVTSHandlerTask.h"
#include "statedrv.h"
#include "InputTask.h"
#define pprintf printf

extern UINT8 ValidCommand;
extern UART_CHANNEL channelA;
extern UART_CHANNEL channelC;
extern enum WELDSTATES WeldState;
extern void SerialSend(UART_CHANNEL * channel, UINT8 * data, UINT16 length);

Ethernet *Netif;
UINT8 * VGAMenuResponseBuff;
SINT32 Fd;
sockaddr_in SA;
SINT32 SockId,Timer;
SINT32 SAlen = sizeof(SA), Len = 0, Flags = 0;
int cliLen,newFd;
BOOLEAN Disconnect = TRUE;
fd_set Input_set;
fd_set Exc_set;
timeval Timeout;


/** @brief CreateAndBindSocket
 *
 *  Function creates a UDP socket and bind it to port SOURCE_UDPPORT
 *
 *  @param void
 *  @return void
 */
void CreateAndBindSocket(void)
{
   Fd = socket(AF_INET, SOCK_DGRAM, PF_INET);
   ASSERT(Fd != INVALID_SOCKET);
   //Socket address to be bind with socket descriptor
   sockaddr_in Sa;
   //socket family
   Sa.sin_family = AF_INET;
   //this becomes the source port for sending MB ppacket
   Sa.sin_port = htons((UINT16)SOURCE_UDPPORT);
   //source ip from which MB packet will be send
   Sa.sin_addr.s_addr = Netif -> ipaddr.addr;
   if (bind(Fd, (sockaddr *) &Sa, sizeof(Sa)) < 0)
      pprintf("Bind NetworkManagerTask socket\n");
}

/** @brief CloseSocket
 *
 *  Function first checks a valid socket and then close the socket.
 *
 *  @param void
 *  @return void
 */
void CloseSocket(void)
{
   if(Fd != INVALID_SOCKET){
      lwip_close(Fd);
      Fd = INVALID_SOCKET;
   }
}

/** @brief NonBlock
 *
 *  Function makes a socket non blocking
 *
 *  @param void
 *  @return void
 */
void NonBlock(void)
{
   UINT32 Val = 1;
   if(lwip_ioctl(Fd, FIONBIO, &Val) < 0)
      pprintf("socket nonblocking failed\n");
}

/** @brief Block
 *
 *  Function makes a socket non blocking
 *
 *  @param void
 *  @return void
 */
void Block(void)
{
   SINT32 Val = 0;
   if(lwip_ioctl(Fd, FIONBIO, &Val) < 0)
      pprintf("socket blocking failed\n");
}

/** @brief TransmitNAK
 *
 *  This function prepares a NAK and send it on socket.
 *
 *  @param UART_CHANNEL* pointer to struct that stores command info.
 *  @return void
 */
void TransmitNAK(UART_CHANNEL * channel)
{
   UINT8 ch;
   int Index = 0;
   UINT8 checksum = 0x00;
   char SerialTxBuff[1500];

   SerialTxBuff[Index++] = NAK;
   SerialTxBuff[Index++] = DLE;
   SerialTxBuff[Index++] = STX;

   ch = 0x00;
   checksum ^= ch;
   SerialTxBuff[Index++] = ch;

   ch = 0x05;
   checksum ^= ch;
   SerialTxBuff[Index++] = ch;

   ch = channel->code >> 8;
   checksum ^= ch;
   SerialTxBuff[Index++] = ch;

   ch = channel->code & 0xFF;
   checksum ^= ch;
   SerialTxBuff[Index++] = ch;

   ch = 0x00;
   checksum ^= ch;
   SerialTxBuff[Index++] = ch;
   SerialTxBuff[Index++] = checksum;
   SerialTxBuff[Index++] = DLE;
   SerialTxBuff[Index++] = ETX;
   if(channel == &channelA)//Is it UDP communication
       sendto(Fd, SerialTxBuff, Index-1, Flags, (sockaddr *)&SA, sizeof(SA));
   else
	   SerialSend(channel, (UINT8*)SerialTxBuff, Index-1);
}

/** @brief VgaSerialMessageQueue send bytes on socket.
 *
 *  This function sends data bytes on socket.
 *
 *  @param UART_CHANNEL* pointer to struct that stores command info.
 *  @param UINT8* pointer to data to be sent.
 *  @param UINT16 length of data.
 *  @return void
 */
void VgaSerialMessageQueue(UART_CHANNEL * channel, UINT8 * data, UINT16 length)
{
   sendto(Fd, data, length, Flags, (sockaddr *) &SA, sizeof(SA));
   //Start checking SBC timeout after replying something
   NetworkManagerTask::thisptr->SbcTimeOutCounter = 0;//first clear the time out
   NetworkManagerTask::thisptr->CheckSBCTimeOut = TRUE;//now start checking it again.
   channel = NULL;
}


/** @brief ProcessCommand processes the command received.
 *
 *  The assumption here is that the welder receives next request only after
 *  this one is processed, so as long as we guarantee that on the other end
 *  we don't go into transmitter FIFO buffer overruns and we won't get stuck
 *  in the interrupt handler.
 *
 *  @param UART_CHANNEL* pointer to struct that stores command info.
 *  @return void
 */
void ProcessCommand(UART_CHANNEL * channel)
{
   RVTS_MSG RvtsMsg;
   if (channel->checksum == 0)   // good checksum
   {
	  if(channel == &channelC)
	  	PortManagerTask::thisptr->CheckSBCTimeOut = FALSE;
      ValidCommand= TRUE;
      RvtsMsg.common.source_task = (SOURCE_TASK_ID_TYPE)SERIAL_INTERRUPT;
      RvtsMsg.channel = channel;
      RvtsMsg.common.opcode = OP_TOUCH_SCRN_MSG_READY;
      RVTSHandlerTask::thisPtr->RVTSTaskQ.Write(0, *((RVTS_MSG_QUEUE_TYPE*) &RvtsMsg), 0);
   }
   else
      TransmitNAK(channel);
}

/** @brief CharReceived checks received bytes
 *
 *  This function makes a command from received bytes and verify it.
 *  If command is not valid NAK is sent.
 *
 *  @param UART_CHANNEL* pointer to struct that stores command info.
 *  @param UINT8 received byte.
 *  @return void
 */
void CharReceived(UART_CHANNEL * channel, UINT8 ch)
{
    switch (channel->state)
   {
   case STATE_WAIT_FIRST_DLE :
      if (ch == DLE){
         channel->state = STATE_WAIT_STX;
      }
     else if(ValidCommand)
      {
         ValidCommand=FALSE;
         TransmitNAK(channel);
      }
     break;


   case STATE_WAIT_STX :
      if (ch == STX){
         channel->state = STATE_WAIT_LENGTH1;
      }
      else
     {
         channel->state = STATE_WAIT_FIRST_DLE;
       if(ValidCommand)
      {
         ValidCommand=FALSE;
         TransmitNAK(channel);
      }
      break;
     }
      channel->checksum = 0;
      break;

   case STATE_WAIT_LENGTH1 :
      channel->length = ch << 8;
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_LENGTH2;
      break;

   // here we ignore the command that has more than RX buffer size
   // worth of data, nowhere to store it so might just throw it away...
   case STATE_WAIT_LENGTH2 :
      channel->length |= ch;

      channel->checksum ^= ch;
      if (channel->length > channel->rxbufsize + 4)
         channel->state = STATE_WAIT_FIRST_DLE;
      else
         channel->state = STATE_WAIT_CODE1;
      break;

   case STATE_WAIT_CODE1 :
      channel->code = ch << 8;
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_CODE2;
      break;

   case STATE_WAIT_CODE2 :
      channel->code |= ch;
      channel->checksum ^= ch;
      channel->rxindex = 0;
      channel->length -= 4;
     if(!VerifyLengthAndCode(channel->length,channel->code))
     {
        channel->state = STATE_WAIT_FIRST_DLE;
        if(ValidCommand)
        {
           ValidCommand=FALSE;
           TransmitNAK(channel);
        }
        break;
     }
     else{
        //pprintf("Verified");
     }
      if (channel->length == 0)  // no data, just length and code
         channel->state = STATE_WAIT_CRC;
      else
         channel->state = STATE_WAIT_DATA;
      break;

   case STATE_WAIT_DATA :
      channel->rxbuf[channel->rxindex++] = ch;
      channel->checksum ^= ch;
      if (channel->rxindex >= channel->length)
         channel->state = STATE_WAIT_CRC;
      break;

   case STATE_WAIT_CRC :
      channel->checksum ^= ch;
      channel->state = STATE_WAIT_SECOND_DLE;
      break;

   case STATE_WAIT_SECOND_DLE :
      if (ch == DLE)
         channel->state = STATE_WAIT_ETX;
      else
     {
         channel->state = STATE_WAIT_FIRST_DLE;
       if(ValidCommand)
      {
         ValidCommand=FALSE;
         TransmitNAK(channel);
      }

     }
      break;

   case STATE_WAIT_ETX :
      if (ch == ETX){
         ProcessCommand(channel);
      }
     else if(ValidCommand)
      {
         ValidCommand=FALSE;
         TransmitNAK(channel);
      }

      channel->state = STATE_WAIT_FIRST_DLE;
      break;

   default :
      channel->state = STATE_WAIT_FIRST_DLE;
      }
}


NetworkManagerTask *NetworkManagerTask::thisptr;

/** @brief Constructor function of NetworkManagerTask class
 *
 *  This function first check the network interface then UDP socket.
 *  If UDP socket is not created then CreateAndBindSocket() function is called.
 *  After doing these steps function receives bytes UDP socket and pass to CharReceived()
 *
 *  @param int ethernet interface number on which WC and SBC socket will be made.
 *  @return void
 */
NetworkManagerTask::NetworkManagerTask(SINT32 Intf) : Task("NMT", T_SIZE_1024)
{
   Netif = CyGOS::GetNetworkInterface(Intf);
   ASSERT(Netif);
   VGAMenuResponseBuff = new UINT8[VGA_MENU_RESPONSEBUFF_SIZE];
   InterfaceNum = Intf;
   //Socket descriptor to be uses to send Modbus packet
   Fd = INVALID_SOCKET;
   thisptr = this;
   CheckSBCTimeOut = FALSE;
   SbcTimeOutCounter = 0;
   LatchSBCReady = FALSE;
   SbcTimedOut = FALSE;
}

/** @brief Destructor function of NetworkManagerTask class
 *
 *  @param void
 *  @return void
 */
NetworkManagerTask::~NetworkManagerTask()
{

}

/** @brief Run function of NetworkManagerTask class
 *
 *  This function first check the network interface then UDP socket.
 *  If UDP socket is not created then CreateAndBindSocket() function is called.
 *  After doing these steps function receives bytes UDP socket and pass to CharReceived()
 *
 *  @param void
 *  @return void
 */
void NetworkManagerTask::Run() {
	DelayMs(100);
	char SerialRxBuff[2048];
	BOOLEAN Running = FALSE;
	while (FOREVER) {
		int i;
		if ((Netif->up == false)
				|| (CyGOS::IsNetworkConfigured(InterfaceNum) == false)) {
			DelayMs(10);
			Running = FALSE;
		} else {
			if (!Running) {
				CloseSocket();
				CreateAndBindSocket();
				Block();
				Running = TRUE;
			}

			Len = recvfrom(Fd, SerialRxBuff, sizeof(SerialRxBuff), Flags,
					(sockaddr *) &SA, (int *) &SAlen);
			CheckSBCTimeOut = FALSE;//received something from SBC. So don't check for any time out
			/* check that serial communication not timed out before regaining ready state*/
			if((SbcTimedOut == TRUE) && (PortManagerTask::thisptr->SbcTimedOut == FALSE)){
			   SBCReadyFlag = LatchSBCReady;
			   SbcTimedOut = FALSE;
			}
			for (i = 0; i < Len; i++)
				CharReceived(&channelA, SerialRxBuff[i]);
		}
	}
}

/*Function is called every tick. It checks the SBC Idle timeout and make SBCReady Flag false to stop further cycling
 */
void NetworkManagerTask::Tick()
{
	if(CheckSBCTimeOut && (SbcTimeOutCounter < SBC_UDP_TIMEOUT))	{
		SbcTimeOutCounter += usecPerTick;
		if((OnboardDiag == FALSE) && (SbcTimeOutCounter >= SBC_UDP_TIMEOUT)){
			if(PortManagerTask::thisptr->SbcTimedOut)
				LatchSBCReady = PortManagerTask::thisptr->LatchSBCReady;
			else
				LatchSBCReady = SBCReadyFlag;
			SBCReadyFlag = FALSE;
			SbcTimedOut = TRUE;
			if (WeldState == READYSTATE)
				ResetStateMachineIndex();//Preready checks SBC ready flag
		}
	}

}
