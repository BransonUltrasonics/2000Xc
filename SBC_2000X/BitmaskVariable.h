/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitmaskVariable.h_v   1.2   28 Mar 2014 14:32:54   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitmaskVariable.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:46 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0    03 Apr 2013 10:09:42 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_)
#define AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Variable.h"

class CXmlElement;

class CBitmaskVariable : public CVariable  
{
public:
	CBitmaskVariable(CXmlElement * element);
	virtual ~CBitmaskVariable();

protected:
	CMapStringToString values;
	virtual CCondition * CreateCondition(CXmlElement * element);
};

#endif // !defined(AFX_BITMASKVARIABLE_H__0844E3FB_01C4_488A_8FCB_C0568E988F72__INCLUDED_)
