/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/PortManagerTask.cpp_v   1.14   16 Apr 2015 07:18:02   rjamloki  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/PortManagerTask.cpp_v  $
 * 
 *    Rev 1.14   16 Apr 2015 07:18:02   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.13   27 Mar 2015 15:19:42   RJamloki
 * Using Serial link also for determining SBC Timeout.
 * 
 *    Rev 1.12   08 Jan 2015 03:18:26   AnPawar
 * printf removed
 * 
 *    Rev 1.11   10 Nov 2014 04:55:06   AnPawar
 * VgaSerialSend renamed to SerialSend
 * 
 *    Rev 1.10   06 Oct 2014 06:41:10   AnPawar
 * removed ck_qsend.h file inclusion.
 * 
 *    Rev 1.9   05 Sep 2014 05:02:22   rjamloki
 * Channel Receive buffer size increased
 * 
 *    Rev 1.8   11 Jun 2014 12:00:32   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.7   23 Apr 2014 13:53:10   akaushal
 * Funtion for sending data on serial added.
 * 
 *    Rev 1.6   14 Apr 2014 10:23:18   rjamloki
 * Fixed port number for VGA communication.
 * 
 *    Rev 1.5   06 Mar 2014 11:03:56   rjamloki
 * Add User ID Functionality
 * 
 *    Rev 1.4   05 Mar 2014 13:56:36   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   03 Jan 2014 08:45:42   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
  ---------------------------- MODULE DESCRIPTION --------------------------
   Module name:

   Filename: PortManagerTask.cpp

   Function name:


  -------------------------------- REVISIONS -------------------------------



  ----------------------------- INCLUDE FILES ------------------------------*/
#include "PortManagerTask.h"
#include "Serial.h"
#include "vga_uart.h"
#include "command.h"
#include "stdio.h"
#include "UndefPrintf.h"
#include "CyGOS.h"
#include "A1025R.h"
#include "DUPS_ManagerTask.h"
#include "RVTSHandlerTask.h"
#include "statedrv.h"
#include "InputTask.h"

#define WCSBC_PORT 0

UINT8 ValidCommand = FALSE;
// maximum needed TX buffer size is defined as
// 'as much as we can send in 50 milliseconds at highest speed that we can use,
// plus some 20 bytes more'
// 50 milliseconds is an arbitrary delay inlocal FifoWrite function when Fifo
// doesn't have space to put a byte in

#define VGABAUD 9600
#define VGADELAY 50
#define EXTRASPACE 20
#define TXABUFSIZE ((VGABAUD / 10) * 500 / VGADELAY + EXTRASPACE)

// this size should be large enough to fit any host command data part
#define RXABUFSIZE 2048
#define TXBBUFSIZE 512
#define RXBBUFSIZE 512
#define TXCBUFSIZE 512
#define RXCBUFSIZE 512
static SINT8 txAbuf[TXABUFSIZE]; // TX buffer for channel A
static SINT8 txBbuf[TXBBUFSIZE];    // TX buffer for channel B
static SINT8 txCbuf[TXCBUFSIZE];    // TX buffer for channel C
static SINT8 rxAbuf[RXABUFSIZE]; // RX buffer for channel A
static SINT8 rxBbuf[RXBBUFSIZE];    // RX buffer for channel B
static SINT8 rxCbuf[RXCBUFSIZE];    // RX buffer for channel C

UART_CHANNEL channelA = {
   0,
   txAbuf, sizeof(txAbuf),
   rxAbuf, sizeof(rxAbuf),
   0x01,
   (CHANNEL_STATE)0, 0, 0, 0, 0 };

UART_CHANNEL channelB = {
   0,
   txBbuf, sizeof(txBbuf),
   rxBbuf, sizeof(rxBbuf),
   0x10,
   (CHANNEL_STATE)0, 0, 0, 0, 0 };

UART_CHANNEL channelC = {
   0,
   txCbuf, sizeof(txCbuf),
   rxCbuf, sizeof(rxCbuf),
   0x01,
   (CHANNEL_STATE)0, 0, 0, 0, 0 };


extern void CharReceived(UART_CHANNEL * , UINT8 );
extern enum WELDSTATES WeldState;

/*
 *
 */
void SerialSend(UART_CHANNEL * channel, UINT8 * data, UINT16 length)
{
   UINT16 i;
   if(channel == &channelC){
   		//Serial command from SBC is replied here
   	   for (i = 0 ; i < length ; i++)
      		PortManagerTask::thisptr->Port.Send(0 , data[i], -1);
	   if(channel->code != GET_NETWORK_INFO){
		   PortManagerTask::thisptr->SbcTimeOutCounter = 0;//first clear the time out
		   PortManagerTask::thisptr->CheckSBCTimeOut = TRUE;//now start checking it again.
	   }
   }
   else if(channel == &channelB)
   {
      //Serial command on DUPS port is replied here. This part of code is only called
	  //when testing Dups Serial port as part of Factory Test
	   for (i = 0 ; i < length ; i++)
		   DUPS_ManagerTask::thisPtr->Port.Send(0, data[i], -1);
   }
}

PortManagerTask *PortManagerTask::thisptr;
PortManagerTask::PortManagerTask() : Task("PMT", T_SIZE_1024),Port(1536, 1536)
/****************************************************************************/
/* Description:-                                                            */
/* PortManagerTask Constructor                                              */
/****************************************************************************/
{
   Port.Init(WCSBC_PORT ,115200 , 3, 3, FALSE);
   thisptr = this;
   CheckSBCTimeOut = FALSE;
   SbcTimeOutCounter = 0;
   LatchSBCReady = FALSE;
   SbcTimedOut = FALSE;
}

PortManagerTask::~PortManagerTask()
/****************************************************************************/
/* Description:-                                                            */
/* PortManagerTask destructor                                               */
/****************************************************************************/
{

}

void PortManagerTask::Run()
{
   while(FOREVER)
   {
      unsigned char Ch = 'T';
      //Wait for character to come.
	  Port.Receive(this , Ch, -1);
	  if((SbcTimedOut == TRUE) && (NetworkManagerTask::thisptr->SbcTimedOut == FALSE))
	  	   SBCReadyFlag = LatchSBCReady;
	  SbcTimedOut = FALSE;
   	  CharReceived(&channelC, Ch);
   }
}

/****************************************************************************/
/* Description:-                                                            */
/* PortManagerTask Tick:Called every RTOS Tick and used for checking serial */
/* communication time out                              						*/
/****************************************************************************/
void PortManagerTask::Tick()
{

	if(CheckSBCTimeOut && (SbcTimeOutCounter < SBC_SERIAL_TIMEOUT))	{
		SbcTimeOutCounter += usecPerTick;
		if((OnboardDiag == FALSE) && (SbcTimeOutCounter >= SBC_SERIAL_TIMEOUT)){
			if(NetworkManagerTask::thisptr->SbcTimedOut)
				LatchSBCReady = NetworkManagerTask::thisptr->LatchSBCReady;
			else
				LatchSBCReady = SBCReadyFlag;
			SBCReadyFlag = FALSE;
			SbcTimedOut = TRUE;
			if (WeldState == READYSTATE)
				ResetStateMachineIndex();//Preready checks SBC ready flag
		}
	}

}
