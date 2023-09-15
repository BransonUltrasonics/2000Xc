/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ServerSocket.cpp_v   1.8   12 Dec 2014 06:05:22   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ServerSocket.cpp_v  $
 * 
 *    Rev 1.8   12 Dec 2014 06:05:22   RJamloki
 * Error string added.
 * 
 *    Rev 1.7   11 Dec 2014 06:50:52   RJamloki
 * app->Trace() is replaced by AfxMessageBox().
 * 
 *    Rev 1.6   06 Oct 2014 03:26:16   rjamloki
 * changed file maximum file descriptor in select api from 10 to 0,because it had no meaning.
 * 
 *    Rev 1.5   01 Oct 2014 10:52:52   AnPawar
 * CServerSocket::Select() function changed
 * 
 *    Rev 1.4   28 Mar 2014 14:33:10   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:32 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:24 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:36 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:00 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "Application.h"
#include "ServerSocket.h"
#include "Connection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CServerSocket::CServerSocket(int port)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == INVALID_SOCKET)
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Ethernet: CServerSocket::ctor: socket. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}
	ReuseAddress();
	Linger();
	Bind(port);
	NonBlock();
	Listen();

	sockaddr_in addr;
	int len = sizeof(addr);
	if (getsockname(fd, (sockaddr *) &addr, &len) == SOCKET_ERROR)
		app->Trace("getsockname error");
	CString s;
	s.Format(_T("%d.%d.%d.%d:%d"), addr.sin_addr.S_un.S_un_b.s_b1, addr.sin_addr.S_un.S_un_b.s_b2, addr.sin_addr.S_un.S_un_b.s_b3, addr.sin_addr.S_un.S_un_b.s_b4, addr.sin_port);
	app->Trace(s);
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::Bind(int port)
{
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	if (bind(fd, (const struct sockaddr *) &sa, sizeof(sa)) == SOCKET_ERROR)
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Ethernet: CServerSocket::Bind. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}
}

void CServerSocket::ReuseAddress()
{
	BOOL opt = TRUE;
	if (!SetSockOpt(SO_REUSEADDR, &opt, sizeof(opt)))
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Ethernet: CServerSocket::ReuseAddress. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}
}

void CServerSocket::Listen()
{
	if (listen(fd, 50) == SOCKET_ERROR)
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Ethernet: CServerSocket::Listen. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}
}

void CServerSocket::Linger()
{
	LINGER ld;
	ld.l_onoff = 1;
	ld.l_linger = 1000;
	if (!SetSockOpt(SO_LINGER, &ld, sizeof(ld)))
	{
#ifdef ERRMSGBOX
		CString errstr = "";
		errstr.Format(_T("Ethernet: CServerSocket::Linger. error no.%d"),WSAGetLastError());
		AfxMessageBox(errstr);
#endif
		exit(1);
	}
}

int CServerSocket::Select(fd_set &input) const
{
	return select(0, &input, 0, 0, 0);
}

CConnection * CServerSocket::Accept(sockaddr_in &sock)
{
	int size = sizeof(sock);
	SOCKET afd = accept(fd, (struct sockaddr *) &sock, &size);
	if (afd == INVALID_SOCKET)
		return 0;
	CConnection * client = new CConnection(afd);
	return client;
}
