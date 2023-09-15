/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Queue.cpp_v   1.6   20 May 2014 11:01:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Queue.cpp_v  $
 * 
 *    Rev 1.6   20 May 2014 11:01:12   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.5   07 May 2014 13:18:38   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.4   28 Mar 2014 14:33:06   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:24 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:04 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:28 amaurya     
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "Queue.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CQueue::CQueue()
{
	mutex.Unlock();
	//	dataAvailable.ResetEvent();
}

CQueue::~CQueue()
{
}
/*
HANDLE CQueue::event() const
{
return dataAvailable;
}
*/
void CQueue::AddCommand(CHostCommand *command)
{
	mutex.Lock();
	queue.AddHead(command);
	mutex.Unlock();
}

CHostCommand * CQueue::GetCommand()
{
	mutex.Lock();
	CHostCommand * command = 0;
	if (queue.GetCount() > 0)
	{
		//printf(" ,count=%d ,",queue.GetCount() );
		command = queue.RemoveHead();
	}
	else
	{
		//printf(" ,count = 0 ");
	}
	mutex.Unlock();
	return command;
}
/*
void CQueue::PulseEvent()
{
dataAvailable.PulseEvent();
}

void CQueue::WaitEvent()
{
WaitForSingleObject(dataAvailable, INFINITE);
}
*/