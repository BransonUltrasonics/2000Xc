/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Variable.h_v   1.2   28 Mar 2014 14:33:16   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Variable.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_)
#define AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Condition.h"
#include "XmlElement.h"

class CVariable  
{

public:
	CVariable();
	virtual ~CVariable();
   virtual CCondition * CreateCondition(CXmlElement * element) = 0;
   CString name;
protected:
	
	CString address;
	int value;
};

#endif // !defined(AFX_VARIABLE_H__5AC7208D_ADC2_4515_8860_5DE714FB3BAB__INCLUDED_)
