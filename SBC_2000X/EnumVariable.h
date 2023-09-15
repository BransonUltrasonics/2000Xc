/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumVariable.h_v   1.4   18 Aug 2014 07:44:42   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumVariable.h_v  $
 * 
 *    Rev 1.4   18 Aug 2014 07:44:42   rjamloki
 * Renaming as per review comments.
 * 
 *    Rev 1.3   09 Jul 2014 06:52:08   akaushal
 * modified enum CONDITION.
 * 
 *    Rev 1.2   28 Mar 2014 14:33:00   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1    03 Jan 2014 09:04:56 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0    03 Apr 2013 10:09:46 amaurya     
 * Initial Revision.
*/


#if !defined(AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_)
#define AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Variable.h"

class CXmlElement;

enum CONDITION
{
    SECURITY_CONDITION,
    CONTROLLEVEL_CONDITION,
    ACTUATOR_CONDITION,
    ENABLEID_CONDITION,
    CHECKFUN_CONDITION,
    RUNSCREEN_CONDITION,
	BASICEXPERT_CONDITION,
	OPERATOR_CONDITION,
	TECHNICIAN_CONDITION,
	SUPERVISOR_CONDITION,
	EXECUTIVE_CONDITION,
	BRANSON_CONDITION,
	NOAUTHORITY_CONDITION,
	AUTOMATION_CONDITION,
	ACCESS_CONDITION
};

class CEnumVariable : public CVariable  
{
public:
	CEnumVariable(CXmlElement * element);
	virtual ~CEnumVariable();
  // CMapStringToString values;
	CComboBox * combo;
protected:
	virtual CCondition * CreateCondition(CXmlElement *element);

};

#endif // !defined(AFX_ENUMVARIABLE_H__E42A1622_4133_4CED_8CD5_8BB8334699B3__INCLUDED_)
