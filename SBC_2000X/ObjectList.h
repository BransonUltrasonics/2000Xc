/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ObjectList.h_v   1.2   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ObjectList.h_v  $
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


#if !defined(AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class ObjectList: Template class maintains a list of objects that are stored
 * in the list using pointers. All objects are destroyed when the list object
 * is destroyed.
 */
template <class Object>
class CObjectList : public CTypedPtrList<CPtrList, Object *>
{
public:
	/**
	 * ~CObjectList: Destroy the list object.
	 */
	~CObjectList()
	{
		DeleteAll();
	}
	/**
	 * DeleteAll: Remove and destroy all objects that were stored in this
	 * list.
	 */
	void DeleteAll()
	{
		POSITION pos = GetHeadPosition();
		while (pos)
			delete GetNext(pos);
	}
};

#endif // !defined(AFX_OBJECTLIST_H__020C5DA3_C1E6_11D7_BF52_00500406C138__INCLUDED_)
