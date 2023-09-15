/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Pointer.h_v   1.2   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Pointer.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:06   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:52 amaurya
 * Initial Revision.
*/


#if !defined(AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

template <class Object>
class CPointer
{
public:
	CPointer(Object * obj)
	{
		object = obj;
	}
	~CPointer()
	{
		if (object)
			delete object;
	}
	void Done()
	{
		object = 0;
	}

private:
	Object * object;
};

#endif // !defined(AFX_POINTER_H__7510F886_C14F_11D7_BF52_00500406C138__INCLUDED_)
