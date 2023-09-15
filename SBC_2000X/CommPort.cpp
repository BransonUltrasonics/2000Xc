/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/CommPort.cpp_v   1.30   21 Apr 2015 17:00:46   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/CommPort.cpp_v  $
 * 
 *    Rev 1.30   21 Apr 2015 17:00:46   rjamloki
 * ReadEnResponse function fixed for xporter working.
 * 
 *    Rev 1.29   16 Apr 2015 05:55:10   sesharma
 * SBC-WC Communication design changed.
 * 
 *    Rev 1.28   09 Apr 2015 04:19:16   RJamloki
 * Added retries for UI host commands in case of command and response function code mismatch
 * 
 *    Rev 1.27   08 Apr 2015 13:06:12   AnPawar
 * Changes to resolve WC-SBC UDP time out issue.
 * 
 *    Rev 1.26   30 Mar 2015 06:19:00   rjamloki
 * Corrected ReadResponse and ReadUIResponse functions for infinite loop conditions.
 * 
 *    Rev 1.25   28 Mar 2015 04:17:54   RJamloki
 * Polling Host Command retries increased. WeldDataCmd flag removed.
 * 
 *    Rev 1.24   26 Jan 2015 13:30:14   rjamloki
 * Polling command Timeout during estop is changed to 2 seconds.
 * 
 *    Rev 1.23   12 Dec 2014 06:05:42   RJamloki
 * Condition for debugging message added.
 * 
 *    Rev 1.22   11 Dec 2014 07:16:48   RJamloki
 * Error string changed.
 * 
 *    Rev 1.20   28 Nov 2014 08:30:20   rjamloki
 * Unused variable removed(Coverity Issue)
 * 
 *    Rev 1.19   20 Oct 2014 05:41:12   RJamloki
 *  new flag WeldDataCmdFlag defined and ReadCharacter(),SendPollingHostCommand() functions changed to resolve weld data missing issue.
 * 
 *    Rev 1.18   18 Aug 2014 07:39:22   rjamloki
 * Added RUN_ON_SBC define for easy switching between PC and SBC
 * 
 *    Rev 1.17   30 Jul 2014 04:38:14   rjamloki
 * SendUIHostCommand function fixed to used SetUIRequest function.
 * 
 *    Rev 1.16   28 Jul 2014 13:34:50   rjamloki
 * added new  socket for user interface.
 * 
 *    Rev 1.15   22 Jul 2014 08:22:50   akaushal
 * Removed the static destination IP.
 * 
 *    Rev 1.14   20 Jun 2014 10:53:08   akaushal
 * Increased the time for large waiting commands like cold start and config actuator.
 * 
 *    Rev 1.13   09 Jun 2014 11:37:38   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.12   20 May 2014 10:54:30   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.11   07 May 2014 13:21:20   akaushal
 * Code cleanup.
 * 
 *    Rev 1.10   23 Apr 2014 11:22:00   akaushal
 * Added timeout for serial receive.ReadSerialResponse(),ReadSerialCharacter()  added for receiving serial data
 * 
 *    Rev 1.9   21 Apr 2014 13:30:24   akaushal
 * CCommPort() modified for serial initialization and removed unused variables. 
 * 
 *    Rev 1.8   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.7     26 Mar 2014 14:22:04 rjamloki      
 * ip address changed
 *
 *    Rev 1.6     07 Mar 2014 11:15:36 rjamloki      
 * Modify User Changes.
 *
 *    Rev 1.5     06 Mar 2014 11:30:40 rjamloki      
 * Add new User ID function
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
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/



#include "stdafx.h"
#include "Application.h"
#include "CommPort.h"
#include "HostCommand.h"
#include "ChildView.h"
#include "SBC.h"

#ifdef DISABLEPRINTF
#define printf
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCommPort * CCommPort::thisPtr;
bool CCommPort::CommPortNotready=false;
bool CCommPort::OnPollingTime=true;

CCommPort::CCommPort(const CString & port, int speed)
{
	SenderAddr.sin_family = 0;
	SenderAddr.sin_port = 0;
	strncpy(SenderAddr.sin_zero,"",1);
	SenderAddr.sin_addr.S_un.S_addr = 0;
	SenderAddr.sin_addr.S_un.S_un_b.s_b1 = 0;
	SenderAddr.sin_addr.S_un.S_un_b.s_b2 = 0;
	SenderAddr.sin_addr.S_un.S_un_b.s_b3 = 0;
	SenderAddr.sin_addr.S_un.S_un_b.s_b4 = 0;
	SenderAddr.sin_addr.S_un.S_un_w.s_w1 = 0;
	SenderAddr.sin_addr.S_un.S_un_w.s_w2 = 0;

	Reader.fd_count = 0;
	Writer.fd_count = 0;
	NumByteRead = 0;
	handle = NULL;
	length = 0;
	code = 0;
	rxindex = 0;
	checksum = 0;
	ack = false;

	state = STATE_WAIT_ACKNAK;
	thisPtr = this;
	started = false;
#ifdef RUN_ON_SBC
	do
	{
		handle = CreateFile(port, GENERIC_READ | GENERIC_WRITE,
		0, 0, OPEN_EXISTING, 0, 0);
	}while(handle == INVALID_HANDLE_VALUE);

	if (handle == INVALID_HANDLE_VALUE)
	{
		CommPortNotready=true;
		return;
	}
	else
		CommPortNotready=false;

	SetupComm(handle, 4096, 4096);
	DCB dcb;
	BOOL b = GetCommState(handle, &dcb);
	DWORD err = GetLastError();
	dcb.BaudRate = speed;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = FALSE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fDsrSensitivity = FALSE;
	b = SetCommState(handle, &dcb);
	err = GetLastError();
	PurgeComm(handle, PURGE_TXCLEAR | PURGE_RXCLEAR);
    COMMTIMEOUTS tm = { 1/*10*/, 1/*10*/,1/* 10*/, 1/*10*/, 1/*10*/ };	// one millisecond for timeout
	SetCommTimeouts(handle, &tm);
#else
	CommPortNotready=false;
#endif	
	
	unsigned short PortNum = UDPPORTNUM;
	UdpRxBufSize = sizeof(UdpRxBuf);
	SenderAddrSize = sizeof (SenderAddr);

	timeOut.tv_sec=0;        //timeout in seconds
	timeOut.tv_usec = 1000; //timeout in microseconds

	// Initialize Winsock
	int iResult;
	UdpSocketPO = INVALID_SOCKET;
#ifdef RUN_ON_SBC
	IN_ADDR dest_ip;
	dest_ip.S_un.S_addr = CApplication::ip_addr;
	dest_ip.S_un.S_un_b.s_b4 = dest_ip.S_un.S_un_b.s_b4 + 1; //WC ipaddr = SBC ipaddr + 1;*/
	UdpSockWCAddr.sin_family = AF_INET;                 // Address family to use
	UdpSockWCAddr.sin_port = htons(PortNum);              // Port num to use
	UdpSockWCAddr.sin_addr.s_addr = dest_ip.S_un.S_addr ; // IP address to use */
#else
	UdpSockWCAddr.sin_family = AF_INET;                   // Address family to use
	UdpSockWCAddr.sin_port = htons(PortNum);               // Port num to use
	UdpSockWCAddr.sin_addr.s_addr = inet_addr("172.24.121.226"); // IP address to use
#endif

	// Create a SOCKET for connecting to server
	UdpSocketPO = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (UdpSocketPO == INVALID_SOCKET) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in creating socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}

	sockaddr_in BindAddr;//Bind address
	memset(&BindAddr,0,sizeof(BindAddr));
    //Bind the socket to any address and the specified port.
    BindAddr.sin_family = AF_INET;
    BindAddr.sin_port = htons(PortNum);
    BindAddr.sin_addr.s_addr = htonl(INADDR_ANY);    

    iResult = bind(UdpSocketPO , (SOCKADDR *) &BindAddr, sizeof (BindAddr));
    if (iResult == SOCKET_ERROR) 
    {
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in binding socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
        closesocket(UdpSocketPO);
        exit(1);
    }

	PortNum = UDPPORTNUMUI;//Source Port number for UI host Command
	//Create a SOCKET for connecting to server
	UdpSocketUI = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (UdpSocketUI == INVALID_SOCKET) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in creating UI socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}

	memset(&BindAddr,0,sizeof(BindAddr));
    //Bind the socket to any address and the specified port.
    BindAddr.sin_family = AF_INET;
    BindAddr.sin_port = htons(PortNum);
    BindAddr.sin_addr.s_addr = htonl(INADDR_ANY);    

    iResult = bind(UdpSocketUI , (SOCKADDR *) &BindAddr, sizeof (BindAddr));
    if (iResult == SOCKET_ERROR) 
    {
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in binding UI socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
        closesocket(UdpSocketUI);
        exit(1);
    }

	PortNum = UDPPORTNUMEN;//Source Port number for En host Command
	//Create a SOCKET for connecting to server
	UdpSocketEN = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (UdpSocketEN == INVALID_SOCKET) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in creating UI socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}

	memset(&BindAddr,0,sizeof(BindAddr));
    //Bind the socket to any address and the specified port.
    BindAddr.sin_family = AF_INET;
    BindAddr.sin_port = htons(PortNum);
    BindAddr.sin_addr.s_addr = htonl(INADDR_ANY);    

    iResult = bind(UdpSocketEN , (SOCKADDR *) &BindAddr, sizeof (BindAddr));
    if (iResult == SOCKET_ERROR) 
    {
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in binding UI socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
        closesocket(UdpSocketEN);
        exit(1);
    }

	printf("\n com port constructor done");
	AfxBeginThread(Thread, 0);
}

CCommPort::~CCommPort()
{
	closesocket(UdpSocketPO);
	closesocket(UdpSocketUI);
	closesocket(UdpSocketEN);
}

UINT CCommPort::Thread(LPVOID)
{
	thisPtr->Thread();
	return 0;
}

void CCommPort::Thread()
{
	exitEvent.ResetEvent();
	started = true;
	for (;;)
	{	
		HANDLE event[4];
		event[0] = exitEvent;
		event[1] = uiTxEvent;
		event[2] = PollingTxEvent;
		event[3] = enTxEvent;


		DWORD dw = WaitForMultipleObjects(sizeof(event) / sizeof(HANDLE),
			event, FALSE, INFINITE);
		if (dw == WAIT_OBJECT_0)
			break;
		if (dw == (WAIT_OBJECT_0 + 1)){
			SendUiHostCommand();
		}
		if (dw == (WAIT_OBJECT_0 + 2))
		{
			SendPollingHostCommand();
		}
		if (dw == (WAIT_OBJECT_0 + 3))
		{
			SendEnHostCommand();
		}

	}
}

CHostCommand * CCommPort::SendUiHostCommand(CHostCommand *command)
{
	while(uiRxQueue.queue.GetCount()>0)
	{
		delete uiRxQueue.queue.RemoveTail();
	}

	uiTxQueue.AddCommand(command);
	uiRxEvent.ResetEvent();
	uiTxEvent.SetEvent();

	if(!started)
	{
		WaitForSingleObject(uiRxEvent, 3000);
		uiTxEvent.SetEvent();
	}

	int timeout = 5000;
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))
		timeout = 60000;

	WaitForSingleObject(uiRxEvent,timeout);
	uiRxEvent.ResetEvent();
	CHostCommand * response = uiRxQueue.GetCommand();
	return response;
}

CHostCommand * CCommPort::SendPollingHostCommand(CHostCommand *command)
{
	int Pollingtime = 1000;
    if(CChildView::PollingTimeOnMsgScrn)
		Pollingtime = 2000;
	PollingTxQueue.AddCommand(command);

	while(PollingRxQueue.queue.GetCount()>0)
		delete PollingRxQueue.queue.RemoveTail();
	PollingRxEvent.ResetEvent();
	PollingTxEvent.SetEvent();
	if(!started)
	{
		WaitForSingleObject(PollingRxEvent,Pollingtime);
		PollingTxEvent.SetEvent();
	}
	WaitForSingleObject(PollingRxEvent,Pollingtime);
	PollingRxEvent.ResetEvent();
	CHostCommand * response = PollingRxQueue.GetCommand();
	return response;
}

CHostCommand * CCommPort::SendEnHostCommand(CHostCommand *request)
{
	enTxQueue.AddCommand(request);
	enRxEvent.ResetEvent();
	enTxEvent.SetEvent();
	if (!started)
	{
		WaitForSingleObject(enRxEvent, 5000);
		enTxEvent.SetEvent();
	}
	WaitForSingleObject(enRxEvent, 1000);
	enRxEvent.ResetEvent();
	CHostCommand * response = enRxQueue.GetCommand();
	return response;
}

void CCommPort::SendUiHostCommand()
{
	CHostCommand * command = uiTxQueue.GetCommand();

	if (!command)
	{
		uiTxEvent.ResetEvent();
		return;
	}
	int retries = 10;
	for(int i = 0; i < retries; i ++)
	{
		if (!SendUIRequest(command))
			continue;
			
		CHostCommand * response = new CHostCommand(false);

		if (ReadUiResponse(response) && (response->code == command->code))
		{
			if((command->code == GetEptrVariable_FunId)/* ||(command->code == SetValue_FunID) ||(command->code == GetVariableData_FunID)*/ )
			{
				unsigned char * CmdDataPtr = command->GetData();
				unsigned char * ResponseDataPtr = response->GetData();
				short SendEnableID = CmdDataPtr[1] | (CmdDataPtr[0] << 8);
				short ReceiveEnableID = ResponseDataPtr[1] | (ResponseDataPtr[0] << 8);
				if(SendEnableID != ReceiveEnableID)
				{					
					delete response;
					response = 0;				
					continue;					
				}
			}
			uiRxQueue.AddCommand(response);			
			uiRxEvent.SetEvent(); 
			return;
		}
		delete response;
	}
	uiRxQueue.AddCommand(0);
	uiRxEvent.SetEvent();
}

void CCommPort::SendPollingHostCommand()
{
	int  retries = 4;
	
	CHostCommand * command = PollingTxQueue.GetCommand();
	if (!command)
	{
		PollingTxEvent.ResetEvent();
		return;
	}
	for (int i = 0; i <retries; i++)
	{
		if (!SendRequest(command))		
			continue;

		CHostCommand * response = new CHostCommand(false);
		if (ReadResponse(response) && (response->code == command->code))
		{
			delete command;
			PollingRxQueue.AddCommand(response);			
			PollingRxEvent.SetEvent();
			return;
		}
		delete response;
	}
	delete command;
	PollingRxQueue.AddCommand(0);
	PollingRxEvent.SetEvent();
	return;
}

void CCommPort::SendEnHostCommand()
{
	CHostCommand * command = enTxQueue.GetCommand();
	if (!command)
	{
		enTxEvent.ResetEvent();		
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		if (!SendEnRequest(command))
			continue;
		CHostCommand * response = new CHostCommand(false);
		if (ReadEnResponse(response))
		{
			delete command;
			enRxQueue.AddCommand(response);
			enRxEvent.SetEvent();			
			return;
		}
		delete response;
	}
	delete command;
	enRxQueue.AddCommand(0);
	enRxEvent.SetEvent();
}

bool CCommPort::SendUIRequest(CHostCommand *request)
{
	int iResult;
	unsigned char * cmd = request->GetBuffer();
	DWORD length = request->GetBufLength();
	CleanUpOldResponses(UdpSocketUI);	
	iResult = sendto(UdpSocketUI,(const char *)cmd, length, 0, (SOCKADDR *) & UdpSockWCAddr, sizeof (UdpSockWCAddr));
	if (iResult == SOCKET_ERROR) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in sending data on UI socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		closesocket(UdpSocketUI);
		exit(1);
	}
	
	if (length != iResult)	
	{
		return false;
	}
	return true;
}

bool CCommPort::SendRequest(CHostCommand *request)
{
	int iResult;
	unsigned char * cmd = request->GetBuffer();
	DWORD length = request->GetBufLength();	
	CleanUpOldResponses(UdpSocketPO);
	iResult = sendto(UdpSocketPO,(const char *)cmd, length, 0, (SOCKADDR *) & UdpSockWCAddr, sizeof (UdpSockWCAddr));
	if (iResult == SOCKET_ERROR) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in sending data on socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		closesocket(UdpSocketPO);
		exit(1);
	}
	
	if (length != iResult)	
	{
		return false;
	}
	return true;
}

bool CCommPort::SendEnRequest(CHostCommand *request)
{
	int iResult;
	unsigned char * cmd = request->GetBuffer();
	DWORD length = request->GetBufLength();	
	CleanUpOldResponses(UdpSocketEN);
	iResult = sendto(UdpSocketEN,(const char *)cmd, length, 0, (SOCKADDR *) & UdpSockWCAddr, sizeof (UdpSockWCAddr));
	if (iResult == SOCKET_ERROR) 
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Error in sending data on socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		closesocket(UdpSocketEN);
		exit(1);
	}
	
	if (length != iResult)	
	{
		return false;
	}
	return true;
}

bool CCommPort::ReadUiResponse(CHostCommand *response)
{
	int i = 0;	
	int ch = 0;
	NumByteRead = 0;
	for (;;)
	{
		if (i == 0)
			ch = ReadUiCharacter();
		else
			ch = UdpRxBuf[i];		
		i++;	
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
			return true;
		if (i >= NumByteRead)//Parsed everyhting but did not find any thing good
			return false;

	}
}

bool CCommPort::ReadResponse(CHostCommand *response)
{
	int i = 0; 
	int j = 0;
	int ch = 0;
	NumByteRead = 0;
	for (;;)
	{
		if(i == 0)
			ch = ReadCharacter();
		else
			ch = UdpRxBuf[i]; 
		i++;
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
			return true;
		if (i >= NumByteRead)//Parsed everyhting but did not find any thing good
			return false;
	}
}

bool CCommPort::ReadEnResponse(CHostCommand *response)
{
	int i = 0; 
	int j = 0;
	int ch = 0;
	NumByteRead = 0;
	for (;;)
	{
		if(i == 0)
			ch = ReadEnCharacter();
		else
			ch = UdpRxBuf[i]; 

		if(i==0 && ch == DLE)
		{
            j = 1;//index 0 is DLE. Start getting data from index 1
            while(!(response->StartWeldDataCharReceived(ch & 0xFF)) )
            {
                if(j >= NumByteRead)//Parsed everything but did not find anything good
                     return false;
                ch = UdpRxBuf[j];                 
                j++;
            }
			return true;
		}
		i++;
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
			return true;
		if (i >= NumByteRead)//Parsed everyhting but did not find any thing good
			return false;
	}
}


int CCommPort::ReadUiCharacter()
{
	int total =0 ;
	int retries = 50;//150;
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//(CVGAButtons::ColdStartInProcess))
		retries = 3000;
	timeOut.tv_usec = 10000;
	for (int i = 0; i < retries; i++)
	{
		FD_ZERO(&Reader);  // Initialize the Read socket set.
		FD_SET(UdpSocketUI, &Reader);
		if((total = select(0, &Reader, NULL, NULL, &timeOut)) == SOCKET_ERROR)
		{
#ifdef ERRMSGBOX
			CString errstr = "";
			errstr.Format(_T("Error in select UI socket. error no.%d"),WSAGetLastError());
			AfxMessageBox(errstr);
#endif
			closesocket(UdpSocketUI);
			exit(1);
		}
		
		if(total > 0 && FD_ISSET(UdpSocketUI, &Reader))
		{
			NumByteRead = recvfrom(UdpSocketUI,(char *)UdpRxBuf, UdpRxBufSize, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);			
			if (NumByteRead == SOCKET_ERROR) 
			{
#ifdef ERRMSGBOX
				CString errstr = "";
				errstr.Format(_T("Error in receiving data from UI socket. error no.%d"),WSAGetLastError());
				AfxMessageBox(errstr);
#endif
				closesocket(UdpSocketUI);
				exit(1);
			}
			if(NumByteRead >= 1)
			{
				i = UdpRxBuf[0];
				return i & 0xFF;
			}
		} 
		Sleep(1);		
	}
	return -1;
}

int CCommPort::ReadCharacter()
{

	int retries = 20;
	int total=0;
	timeOut.tv_usec = 10000;
	if(CChildView::PollingTimeOnMsgScrn)//estop case 
		retries=200;
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//cold start and hidden menus
		retries = 6000;

	for (int i = 0; i < retries; i++)
	{
		FD_ZERO(&Reader);  // Initialize the Read socket set.
		FD_SET(UdpSocketPO, &Reader);		
		if ((total = select(0,&Reader, NULL, NULL, &timeOut)) == SOCKET_ERROR)
		{
#ifdef ERRMSGBOX
			CString errstr = "";
			errstr.Format(_T("Error in select socket. error no.%d"),WSAGetLastError());
			AfxMessageBox(errstr);
#endif
			closesocket(UdpSocketPO);	
			exit(1);
		}

		if(total>0 && FD_ISSET(UdpSocketPO, &Reader))
		{
			NumByteRead = recvfrom(UdpSocketPO,(char *)UdpRxBuf,UdpRxBufSize, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
			if (NumByteRead == SOCKET_ERROR) 
			{
#ifdef ERRMSGBOX
				CString errstr = "";
				errstr.Format(_T("Error in receiving from socket. error no.%d"),WSAGetLastError());
				AfxMessageBox(errstr);
#endif
				closesocket(UdpSocketPO);
				exit(1);
			}		
			if (NumByteRead >= 1)
			{
				i = UdpRxBuf[0];			
				return i & 0xFF;
			}
		}		
		Sleep(1);		
	}
	return -1;
}


int CCommPort::ReadEnCharacter()
{

	int retries = 20;
	int total=0;
	timeOut.tv_usec = 10000;
	for (int i = 0; i < retries; i++)
	{
		FD_ZERO(&Reader);  // Initialize the Read socket set.
		FD_SET(UdpSocketEN, &Reader);		
		if ((total = select(0,&Reader, NULL, NULL, &timeOut)) == SOCKET_ERROR)
		{
#ifdef ERRMSGBOX
			CString errstr = "";
			errstr.Format(_T("Error in select socket. error no.%d"),WSAGetLastError());
			AfxMessageBox(errstr);
#endif
			closesocket(UdpSocketEN);	
			exit(1);
		}

		if(total>0 && FD_ISSET(UdpSocketEN, &Reader))
		{
			NumByteRead = recvfrom(UdpSocketEN,(char *)UdpRxBuf,UdpRxBufSize, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);
			if (NumByteRead == SOCKET_ERROR) 
			{
#ifdef ERRMSGBOX
				CString errstr = "";
				errstr.Format(_T("Error in receiving from socket. error no.%d"),WSAGetLastError());
				AfxMessageBox(errstr);
#endif
				closesocket(UdpSocketEN);
				exit(1);
			}		
			if (NumByteRead >= 1)
			{
				i = UdpRxBuf[0];			
				return i & 0xFF;
			}
		}		
		Sleep(1);		
	}
	return -1;
}

/*
This function is called before sending any command to WC to clean up the leftovers of previous commands
*/
void CCommPort::CleanUpOldResponses(SOCKET Sock)
{
	int total = 0;
	timeOut.tv_sec = 0;
	timeOut.tv_usec = 1000;//1 ms is sufficient to check socket leftovers
	int MaxCleanUpRetries = 10;
	while(MaxCleanUpRetries)
	{
		FD_ZERO(&Reader);  // Initialize the Read socket set.
		FD_SET(Sock, &Reader);
		if((total = select(0, &Reader, NULL, NULL, &timeOut)) == SOCKET_ERROR)
		{
			#ifdef ERRMSGBOX
				CString errstr = "";
				errstr.Format(_T("Error in select UI socket. error no.%d"),WSAGetLastError());
				AfxMessageBox(errstr);
			#endif
			closesocket(Sock);
			exit(1);
		}		
		if(total > 0 && FD_ISSET(Sock, &Reader))	
			recvfrom(Sock,(char *)UdpRxBuf, UdpRxBufSize, 0, (SOCKADDR *) & SenderAddr, &SenderAddrSize);		
		else
			break;//no leftover exit from here
		--MaxCleanUpRetries;
	}
}

bool CCommPort::SendSerialRequest(CHostCommand *request)
{
	unsigned char * cmd = request->GetBuffer();
	DWORD length = request->GetBufLength();
	DWORD dw;

	WriteFile(handle, cmd, length, &dw, 0);
	FlushFileBuffers(handle);
	if (length != dw)	
		return false;

	return true;
}


bool CCommPort::ReadSerialResponse(CHostCommand *response)
{
	int i = 0;
	for (;;)
	{
		int ch = ReadSerialCharacter();
		if(i==0 && ch == DLE)
		{
			while(!(response->StartWeldDataCharReceived(ch & 0xFF)))
			{
				ch = ReadSerialCharacter();
			}
			return true;
		}
		i++;
		if (i >= 32)
			i = 1;
		if (ch == -1)	// timeout
			return false;
		if (response->CharReceived(ch & 0xFF))
			return true;

	}
}

int CCommPort::ReadSerialCharacter()
{
	int retries = 250;//150;
	int i =0 ;
	if((CChildView::LargeWaitingTime)||(CChildView::ColdStartInProcess))//(CVGAButtons::ColdStartInProcess))
		retries = 1500;
	for (i = 0; i < retries; i++)
	{
		DWORD recvd;
		char ch;
		ReadFile(handle, &ch, 1, &recvd, 0);
		if(recvd == 1)
		{
			i = ch;
			return i & 0xFF;
		}
		Sleep(20);
	}
	return -1;
}

