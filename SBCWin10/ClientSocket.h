/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ClientSocket.h_v   1.4   28 Mar 2014 14:32:56   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ClientSocket.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:14 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:48 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:18 amaurya      
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_)
#define AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcpSocket.h"

class CClientSocket : public CTcpSocket
{
public:
	CClientSocket(SOCKET afd);
	virtual ~CClientSocket();

protected:
};

#endif // !defined(AFX_CLIENTSOCKET_H__DB386F53_5508_4E80_967C_8FC5C8FD7DCC__INCLUDED_)
