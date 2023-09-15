/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TcpSocket.cpp_v   1.6   06 Oct 2014 03:27:36   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TcpSocket.cpp_v  $
 * 
 *    Rev 1.6   06 Oct 2014 03:27:36   rjamloki
 * in function SetBufferSizes() buffer size changed to 64k
 * 
 *    Rev 1.5   09 Jun 2014 11:53:12   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:10   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:34 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:26 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1    05 Jun 2013 09:33:38 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "Application.h"
#include "TcpSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpSocket::CTcpSocket()
{
	fd = 0;
}

CTcpSocket::~CTcpSocket()
{
}

void CTcpSocket::NonBlock()
{
	unsigned long val = 1;
	Ioctl(FIONBIO, &val);
}

bool CTcpSocket::SetSockOpt(int name, const void *value, int len)
{
	return setsockopt(fd, SOL_SOCKET, name, (const char *) value, len) == 0;
}

bool CTcpSocket::Ioctl(long cmd, u_long *argp)
{
	return ioctlsocket(fd, cmd, argp) == 0;
}

bool CTcpSocket::IsSet(fd_set &set) const
{
	return FD_ISSET(fd, &set) != FALSE;
}

void CTcpSocket::FdSet(fd_set &set) const
{
	FD_SET(fd, &set);
}

void CTcpSocket::FdClr(fd_set &set) const
{
	FD_CLR(fd, &set);
}

bool CTcpSocket::IsClosed() const
{
	return fd == INVALID_SOCKET;
}

void CTcpSocket::SetBufferSizes()
{
	int opt = 64 * 1024;//Looks like the cause of TCP window full error when event and weld history
						//is requested from WC on JSON request. Every time
						//the error is observed WC has received 16 K only from SBC.	
						//SBC in sunrise have 480 MB ram so increasing this size should not affect any thing
	if (!SetSockOpt(SO_SNDBUF, &opt, sizeof(opt)))
		app->Trace("Ethernet: TCPSocket::SetBufferSizes send\n");
	opt = 1024;		// 1K for receive
	if (!SetSockOpt(SO_RCVBUF, &opt, sizeof(opt)))
		app->Trace("Ethernet: TCPSocket::SetBufferSizes recv\n");
}

void CTcpSocket::Close()
{
	if (fd != INVALID_SOCKET)
	{
		closesocket(fd);
		fd = INVALID_SOCKET;
	}
}

int CTcpSocket::Write(const char * buf, int len)
{
	int result = send(fd, buf, len, 0);
	if (result > 0)		// Write was successful
		return result;
	if (result == 0)	// This should never happen!
	{
		app->Trace("Ethernet: Huh?? write() returned 0??? Please report this!");
		return -1;
	}
	int error = WSAGetLastError();	// Transient error?
	if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
		return 0;
	// Must be a fatal error.
	return -1;
}

int CTcpSocket::Read(char * buf, int len)
{
	//	return >= 0 - OK
	//	return -1 - EOF
	/*
	int ret = recv(fd, buffer, 250, 0);
	if (ret > 0)	// Read was successful.
	return ret;
	// read() returned 0, meaning we got an EOF.
	if (ret == 0)
	{
	app->Trace("Ethernet: WARNING: EOF on socket read (connection broken by peer)\n");
	return -1;
	}
	// read returned a value < 0: there was an error of some kind
	int error = WSAGetLastError();
	if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
	return 0;	// ok with these errors
	// here we don't know what happened, so let's just report the error
	app->Trace("Ethernet: TCPSocket::read: error - disconnecting...\n");
	*/
	return -1;
}
