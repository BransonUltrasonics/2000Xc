/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ObjectMap.h_v   1.2   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ObjectMap.h_v  $
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

#if !defined(AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_)
#define AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * class CObjectMap: Template class provides storage for objects indexed by a
 * string. All objects are destroyed when the list object is destroyed.
 */
template <class Object>
class CObjectMap : public CTypedPtrMap<CMapStringToPtr, CString, Object *>
{
public:
	/**
	 * ~CObjectMap: Destroy the map object.
	 */
	~CObjectMap()
	{
		DeleteAll();
	}
	/**
	 * DeleteAll: Remove and destroy all objects that were stored in this
	 * map.
	 */
	void DeleteAll()
	{
		POSITION pos = GetStartPosition();
		while (pos)
		{
			CString key;
			Object * obj;
			GetNextAssoc(pos, key, obj);
			delete obj;
		}
		CMapStringToPtr::RemoveAll();
	}
};

#endif // !defined(AFX_OBJECTMAP_H__7510F883_C14F_11D7_BF52_00500406C138__INCLUDED_)
