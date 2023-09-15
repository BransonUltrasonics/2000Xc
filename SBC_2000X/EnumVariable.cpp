/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumVariable.cpp_v   1.8   28 Nov 2014 08:30:38   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumVariable.cpp_v  $
 * 
 *    Rev 1.8   28 Nov 2014 08:30:38   rjamloki
 * Warning removed
 * 
 *    Rev 1.7   18 Aug 2014 07:43:10   rjamloki
 * Renaming and fixes as per review
 * 
 *    Rev 1.6   09 Jul 2014 06:51:20   akaushal
 * Function CEnumVariable::CreateCondition() changed.
 * 
 *    Rev 1.5   09 Jun 2014 11:40:40   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.4   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3    05 Mar 2014 14:13:16 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2    03 Jan 2014 09:04:54 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1    18 Dec 2013 10:00:30 rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya     
 * Initial Revision.
*/


#include "stdafx.h"
#include "SBC.h"
#include "EnumVariable.h"
#include "XmlElement.h"
#include "EnumCondition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMapStringToString values;

CEnumVariable::CEnumVariable(CXmlElement * element)
{
	combo = NULL;
	value = 0;
	name = element->GetAttribute("name");
	address = element->GetAttribute("address");
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		ASSERT(e->tag == "enum");
		CString name1 = e->GetAttribute("name");
		CString value1 = e->GetAttribute("value");
		values.SetAt(name1, value1);
	}
}

CEnumVariable::~CEnumVariable()
{

}

/*************************************************************************************/
/*                                                                                   */
/* Function to Create EnumVariables conditions like ControlLevel,Actuator,Securitylevel 
/* and Enable Flag.  
/*  							
/*************************************************************************************/
CCondition * CEnumVariable::CreateCondition(CXmlElement *element)
{
	CEnumCondition * condition = new CEnumCondition();
	condition->variable = this;
	CString attr;
	attr = element->GetAttribute("valueset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = SECURITY_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Accset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = ACCESS_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}

	attr = element->GetAttribute("cntset");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CONTROLLEVEL_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}

	attr = element->GetAttribute("actset");   
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = ACTUATOR_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("ExpertSet");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = BASICEXPERT_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Op_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = OPERATOR_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Th_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = TECHNICIAN_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Su_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = SUPERVISOR_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Ex_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = EXECUTIVE_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Br_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = BRANSON_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("NoAuth_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = NOAUTHORITY_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Auto_ChangeCond");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = AUTOMATION_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}
	attr = element->GetAttribute("Enable");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = ENABLEID_CONDITION;
		condition->EnableCommand = (_ttoi(bitNumber) != 0);
		condition->CalibMenuIndex=0;
		condition->CalibMenuIndexAED=0;
		condition->EnumValue=0;
		attr=element->GetAttribute("EnableId");
		if (attr != "")
			condition->StringID=_ttoi(attr);

		attr=element->GetAttribute("AEDActuatorValue");
		if (attr != "")
		{
			CString bitNumber;
			values.Lookup(attr, bitNumber);
			condition->EnumValue = _ttoi(bitNumber);
		}
		if(condition->EnumValue)
		{
			attr=element->GetAttribute("CalibMenuIndex");
			if (attr != "")
				condition->CalibMenuIndex=_ttoi(attr);
			else
				condition->CalibMenuIndex=0;

			attr=element->GetAttribute("CalibMenuIndexAED");
			if (attr != "")
				condition->CalibMenuIndexAED=_ttoi(attr);
			else
				condition->CalibMenuIndexAED=0;
		}

		return condition;
	}
	attr = element->GetAttribute("CheckForFunction");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = CHECKFUN_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		condition->FunName=element->GetAttribute("funname");
		return condition;
	}
	attr = element->GetAttribute("SendRunScreenColumn");
	if (attr != "")
	{
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->enumflagvalue = RUNSCREEN_CONDITION;
		condition->EnumValue = _ttoi(bitNumber);
		return condition;
	}	
	delete condition;
	ASSERT(FALSE);
	return 0;
}
