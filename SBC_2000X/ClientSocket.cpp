/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ClientSocket.cpp_v   1.4   28 Mar 2014 14:32:56   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ClientSocket.cpp_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:14 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:46 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:18 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:42 amaurya      
 * Initial Revision.
*/


#include "stdafx.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CClientSocket::CClientSocket(SOCKET afd)
{
	fd = afd;
	NonBlock();
}

CClientSocket::~CClientSocket()
{
}