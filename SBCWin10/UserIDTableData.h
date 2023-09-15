/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTableData.h_v   1.5   25 Sep 2014 12:10:26   AnPawar  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTableData.h_v  $
 * 
 *    Rev 1.5   25 Sep 2014 12:10:26   AnPawar
 * UserLevel enum added
 * 
 *    Rev 1.4   27 May 2014 06:45:16   amaurya
 * Removed Inheritance from data object's class
 * 
 *    Rev 1.3   21 Apr 2014 13:49:44   akaushal
 * Removed an unused Constructor from class. 
 * 
 *    Rev 1.2   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     06 Mar 2014 11:30:44 rjamloki  
 * Add new User ID function
 *
 *    Rev 1.0    05 Mar 2014 14:43:18 rjamloki      
 * Initial Revision.
*/

#if !defined(AFX_USERIDTABLEDATA_H__96DF3FE7_F894_4539_9FAA_99599116DF70__INCLUDED_)
#define AFX_USERIDTABLEDATA_H__96DF3FE7_F894_4539_9FAA_99599116DF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RunScreen.h"
#include "VgaMenuItem.h"
#include "UserID.h"

class CUserIDTableData
{
public:
	CUserIDTableData();
	int TextColour;
	CString * Parameter_Value;
	CUserIDTableData(UserIDStruct *&data);
	void DrawTableData(CDC *pDC,int LeftMostParameter, int LineNo);
	virtual ~CUserIDTableData();
	virtual void Draw(CDC *pDC);
	struct UserIDStruct userIdData;
	CString GetUserLvlStr(int);
	enum UserLevel
	{
		OPERATOR = 0,
		TECHNICIAN = 1,
		SUPERVISOR = 2,
		EXECUTIVE = 4,
		MAINTENANCE = 8,
		BRANSON = 16,
		NOLEVEL = 32,
	};
protected:
	   int Lang_Index;
	   virtual bool MouseClick(const CPoint &p, CChildView *view);
};

#endif // !defined(AFX_USERIDTABLEDATA_H__96DF3FE7_F894_4539_9FAA_99599116DF70__INCLUDED_)
