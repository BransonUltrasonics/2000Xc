/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TcpSocket.h_v   1.4   28 Mar 2014 14:33:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TcpSocket.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:34 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:26 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:38 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:0 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_)
#define AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTcpSocket  
{
public:
	int Read(char * buf, int len);
	int Write(const char * buf, int len);
	bool IsClosed() const;
	void FdClr(fd_set & set) const;
	void FdSet(fd_set & set) const;
	bool IsSet(fd_set & set) const;
	CTcpSocket();
	virtual ~CTcpSocket();
	SOCKET fd;
protected:
	void Close();
	void SetBufferSizes();
	bool Ioctl(long cmd, u_long *argp);
	bool SetSockOpt(int name, const void * value, int len);
	void NonBlock();

};

#endif // !defined(AFX_TCPSOCKET_H__C9D1249C_35DE_45BC_AC6F_511A37C1C9D4__INCLUDED_)
