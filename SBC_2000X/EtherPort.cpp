/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EtherPort.cpp_v   1.9   28 Jul 2014 13:44:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EtherPort.cpp_v  $
 * 
 *    Rev 1.9   28 Jul 2014 13:44:06   rjamloki
 * review fixed
 * 
 *    Rev 1.8   09 Jun 2014 11:41:10   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.7   20 May 2014 10:55:28   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.6   07 May 2014 13:18:26   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.5   28 Mar 2014 14:33:00   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:16 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:04:56 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     02 Jan 2014 09:15:40 rjamloki      
 * Header Test.
 *
 *    Rev 1.1     05 Jun 2013 09:33:22 amaurya     
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya      
 * Initial Revision.
*/


#include "stdafx.h"
#include "Application.h"
#include "EtherPort.h"
#include "ServerSocket.h"
#include "Connection.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEtherPort * CEtherPort::thisPtr;

CEtherPort::CEtherPort()
{
	port = 0;
	input_set.fd_count = 0;
	exc_set.fd_count = 0;
	output_set.fd_count = 0;
	stop = false;
	thisPtr = this;
	server = new CServerSocket(4000);
	AfxBeginThread(Thread, 0);
}

CEtherPort::~CEtherPort()
{
	delete server;

}

UINT CEtherPort::Thread(LPVOID)
{
	thisPtr->Thread();
	return 0;
}

void CEtherPort::Thread()
{
	printf("Ethernet: Opening serial server connection.");
	stop = false;
	while (!stop)
	{
		SleepIfNoClients();
	//	printf("\n CEther thread");
		PrepareFDSets();
		if (!PollNonblock())
		{
			app->Trace("Ethernet: Select poll nonblock.");
			return;
		}
		AcceptNewConnections();
		ProcessExceptions();
		ProcessInput();
		Sleep(100);
	}
	app->Trace("Ethernet: Closing server connection.");
}

void CEtherPort::SleepIfNoClients()
{
	if (clients.GetSize() == 0)
	{
		app->Trace("Ethernet: No connections. Going to sleep.");
		FD_ZERO(&input_set);
		server->FdSet(input_set);
		if (server->Select(input_set) < 0)
			app->Trace("Ethernet: Sleep: Select error");
		else
			app->Trace("Ethernet: New connection. Waking up.");
	}
}

void CEtherPort::PrepareFDSets()
{
	FD_ZERO(&input_set);
	FD_ZERO(&output_set);
	FD_ZERO(&exc_set);

	server->FdSet(input_set);

	for (int i = 0; i < clients.GetSize(); i++)
	{
		CConnection * connection = clients[i];
		connection->FdSet(input_set);
		connection->FdSet(output_set);
		connection->FdSet(exc_set);
	}
}

bool CEtherPort::PollNonblock()
{
	struct timeval null_time = { 0, 0 };
	if (select(0, &input_set, &output_set, &exc_set, &null_time) < 0)
		return false;
	return true;
}

void CEtherPort::AcceptNewConnections()
{
	if (server->IsSet(input_set))
		NewConnection();
}

void CEtherPort::NewConnection()
{
	struct sockaddr_in peer;
	CConnection * newClient = server->Accept(peer);
	if (!newClient)
	{
		app->Trace("Ethernet: Accept error.");
		return;
	}
	clients.Add(newClient);
	app->Trace("Ethernet: Got new connection.");
}

void CEtherPort::ProcessExceptions()
{
	for (int i = 0; i < clients.GetSize(); i++)
	{
		CConnection * client = clients[i];
		if (client->IsSet(exc_set))
		{
			client->FdClr(input_set);
			client->FdClr(output_set);
			client->CloseConnection();
		}
	}
	CleanupConnections();
}

void CEtherPort::ProcessInput()
{
	for (int i = 0; i < clients.GetSize(); i++)
	{
		CConnection * client = clients[i];
		if (client->IsSet(input_set))
			client->ProcessInput();
	}
	CleanupConnections();
}

void CEtherPort::CleanupConnections()
{
	for (int i = clients.GetUpperBound(); i >= 0; i--)
	{
		CConnection * client = clients[i];
		if (client->IsClosed())
		{
			delete client;
			clients.RemoveAt(i);
		}
	}
}

void CEtherPort::Stop()
{
	stop = true;
}
