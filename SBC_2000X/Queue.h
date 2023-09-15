/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Queue.h_v   1.4   28 Mar 2014 14:33:08   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Queue.h_v  $
 * 
 *    Rev 1.4   28 Mar 2014 14:33:08   rjamloki
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

#if !defined(AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_)
#define AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHostCommand;

class CQueue  
{
public:
//	void WaitEvent();
//	void PulseEvent();
	CHostCommand * GetCommand();
	void AddCommand(CHostCommand * command);
//	HANDLE event() const;
	CQueue();
	~CQueue();
CTypedPtrList<CPtrList, CHostCommand *> queue;
protected:
	
	CMutex mutex;
//	CEvent dataAvailable;
};

#endif // !defined(AFX_QUEUE_H__D7157E8D_5951_4CFC_9245_08F123EC3129__INCLUDED_)
