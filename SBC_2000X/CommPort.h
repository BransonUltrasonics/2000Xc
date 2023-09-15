/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/CommPort.h_v   1.13   16 Apr 2015 05:55:46   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/CommPort.h_v  $
 * 
 *    Rev 1.13   16 Apr 2015 05:55:46   sesharma
 * New functions declarations added for new SBC-WC Communication design.
 * 
 *    Rev 1.12   28 Mar 2015 04:22:52   RJamloki
 * UDP socket receive buffer size increased to 30720 to get 50 cycles weld data at a time.
 * 
 *    Rev 1.11   11 Dec 2014 06:48:42   RJamloki
 * UDP socket receive buffer size increased.
 * 
 *    Rev 1.10   20 Oct 2014 05:42:06   RJamloki
 * WeldDataCmdFlag variable added.
 * 
 *    Rev 1.9   28 Jul 2014 13:37:42   rjamloki
 * function and macro declaration for new ui socket.
 * 
 *    Rev 1.8   07 May 2014 13:18:26   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.7   23 Apr 2014 11:22:32   akaushal
 * ReadSerialResponse(),ReadSerialCharacter() added for receiving serial data
 * 
 *    Rev 1.6   21 Apr 2014 13:30:52   akaushal
 * Removed unused variables.
 * 
 *    Rev 1.5   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:14 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:04:48 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:28 rjamloki      
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:18 amaurya      
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_)
#define AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Queue.h"

#define UDPPORTNUMPO 46000  //Source UDP port number used for polling commands
#define UDPPORTNUMUI 46001  //Source UDP port number used for UI Host Commands
#define UDPPORTNUMEN 46002  //Source UDP port number used for En Host Commands
#define UDPPORTNUM   46000  //Destination port number on WeldController for all UDP commands
#define RECVBUFFSIZE 30720  //UDP socket receive buffer size

class CCommPort  
{
	enum CHANNEL_STATE {
		STATE_WAIT_ACKNAK,	// waiting for ACK or NAK
		STATE_WAIT_FIRST_DLE,	// waiting for first DLE
		STATE_WAIT_STX,		// waiting for STX after DLE
		STATE_WAIT_LENGTH1,	// waiting for upper byte of length
		STATE_WAIT_LENGTH2,	// waiting for lower byte of length
		STATE_WAIT_CODE1,	// waiting for upper byte of command code
		STATE_WAIT_CODE2,	// waiting for lower byte of command code
		STATE_WAIT_DISPLOCK,
		STATE_WAIT_DATA,
		STATE_WAIT_CRC,
		STATE_WAIT_SECOND_DLE,	// waiting for second DLE
		STATE_WAIT_ETX,		// waiting for ETX after DLE
		};
	enum {	ACK = 0x06,
		NAK = 0x15,
		DLE = 0x10,
		STX = 0x02,
		ETX = 0x03 };
public:
	SOCKET UdpSocketPO;//Socket used for polling commands and responses
	SOCKET UdpSocketUI;//Socket used for UI host command and responses
	SOCKET UdpSocketEN;//Socket used for En host command and responses
	struct sockaddr_in UdpSockWCAddr;//Destination socket address for Polling, UI and EN commands
	struct sockaddr_in SenderAddr;//temp object to be used with recvfrom socket API.
    int SenderAddrSize;
    timeval timeOut;
	FD_SET Reader;
    FD_SET Writer;

	unsigned char UdpRxBuf[RECVBUFFSIZE]; 
	short UdpRxBufSize;
	short NumByteRead;	

	CQueue uiRxQueue;	
	CHostCommand * SendEnHostCommand(CHostCommand *request);
	CHostCommand * SendUiHostCommand(CHostCommand *command);
	CHostCommand * SendPollingHostCommand(CHostCommand *command);
    bool SendSerialRequest(CHostCommand *request);
	bool ReadSerialResponse(CHostCommand *response);
	int ReadSerialCharacter(void);
	CCommPort(const CString & port, int speed);
	virtual ~CCommPort();
	static bool OnPollingTime;
	static bool CommPortNotready;
protected:
	bool started;
	void SendUiHostCommand();
	void SendEnHostCommand();	
	void SendPollingHostCommand();
	static UINT Thread(LPVOID);
	void Thread();
	int ReadCharacter();
	int ReadUiCharacter();
	int ReadEnCharacter();
	bool ReadResponse(CHostCommand * response);	
	bool ReadUiResponse(CHostCommand * response);
	bool ReadEnResponse(CHostCommand * response);
	bool SendRequest(CHostCommand *request);
	bool SendUIRequest(CHostCommand *request);
	bool SendEnRequest(CHostCommand *request);
	void CleanUpOldResponses(SOCKET Sock);
	static CCommPort * thisPtr;
	HANDLE handle;
	CQueue PollingTxQueue;		// Polling thread transmit queue
	CQueue PollingRxQueue;		// Polling thread receive queue
	CQueue enTxQueue;		// En thread transmit queue
	CQueue enRxQueue;		// En thread receive queue
	CQueue uiTxQueue;		// UI thread transmit queue
		// UI thread receive queue
	CEvent PollingTxEvent;
	CEvent PollingRxEvent;
	CEvent enTxEvent;
	CEvent enRxEvent;
	CEvent uiTxEvent;
	CEvent uiRxEvent;
	CEvent exitEvent;
	//unsigned char rxbuf[RECVBUFFSIZE];
	//short rxbufsize;		// receiver buffer size
	CHANNEL_STATE state;		// receiver state machine
	short length;			// host command length
	short code;			// host command code
	short rxindex;			// pointer into receiver buffer
	char checksum;			// host command checksum
	bool ack;			// true if response was ACK
};

#endif // !defined(AFX_COMMPORT_H__D10DE348_0BFE_46FD_AEDE_2753B1750730__INCLUDED_)
