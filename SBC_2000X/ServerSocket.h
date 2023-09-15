/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ServerSocket.h_v   1.4   28 Mar 2014 14:33:10   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ServerSocket.h_v  $
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

#if !defined(AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_)
#define AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_

#include "TcpSocket.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConnection;

class CServerSocket : public CTcpSocket  
{
public:
	CConnection * Accept(struct sockaddr_in & sock);
	int Select(fd_set & input) const;
	CServerSocket(int port);
	virtual ~CServerSocket();

protected:
	void Linger();
	void Listen();
	void ReuseAddress();
	void Bind(int port);
};

#endif // !defined(AFX_SERVERSOCKET_H__E8A31428_E0A8_4F03_8BB8_1185C1F0DA25__INCLUDED_)
