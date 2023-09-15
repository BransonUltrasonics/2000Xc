/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EtherPort.h_v   1.4   28 Mar 2014 14:33:00   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EtherPort.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:33:00   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:16 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:56 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:22 amaurya   
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya     
 * Initial Revision.
 */


#if !defined(AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_)
#define AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CServerSocket;
class CConnection;

class CEtherPort  
{
public:
	void Stop();
	CEtherPort();
	virtual ~CEtherPort();
	CTypedPtrArray<CPtrArray, CConnection *> clients;
protected:
	void CleanupConnections();
	void ProcessInput();
	void ProcessExceptions();
	void NewConnection();
	void AcceptNewConnections();
	bool PollNonblock();
	void PrepareFDSets();
	void SleepIfNoClients();
	void Thread();
	static UINT Thread(LPVOID);

	static CEtherPort * thisPtr;
	CServerSocket * server;
	
	int port;
	fd_set input_set;
	fd_set output_set;
	fd_set exc_set;
	volatile bool stop;
};

#endif // !defined(AFX_ETHERPORT_H__83BE352A_A69E_49F3_9A3C_C862AD3B657E__INCLUDED_)
