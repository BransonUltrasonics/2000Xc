/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitmaskVariable.cpp_v   1.6   20 May 2014 10:52:44   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitmaskVariable.cpp_v  $
 * 
 *    Rev 1.6   20 May 2014 10:52:44   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.5   07 May 2014 13:18:24   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.4   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:12 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:44 rjamloki      
 * Header Fix and added command to assign ip.
 * 
 *    Rev 1.1     18 Dec 2013 10:00:28 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "BitmaskVariable.h"
#include "XmlElement.h"
#include "BitCondition.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CBitmaskVariable::CBitmaskVariable(CXmlElement * element)
{
	value = 0;
	name = element->GetAttribute("name");
	address = element->GetAttribute("address");
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * bit = element->children.GetNext(pos);
		ASSERT(bit->tag == "bit");
		CString bitname = bit->GetAttribute("name");
		CString value = bit->GetAttribute("value");
		values.SetAt(bitname, value);

	}
}

CBitmaskVariable::~CBitmaskVariable()
{
}

CCondition * CBitmaskVariable::CreateCondition(CXmlElement *element)
{
	CBitCondition * condition = new CBitCondition();
	condition->variable = this;
	CString attr;
	attr = element->GetAttribute("Mask1bitset");
	if (attr != "")
	{
		//	printf("\n Mask1bitset");
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		//condition->bitState = true;
		condition->Mask1= _ttoi(bitNumber);
		condition->Cond1 = _ttoi(bitNumber);
		condition->CaseValue=0;
		return condition;
	}

	attr = element->GetAttribute("Mask1bitclear");
	if (attr != "")
	{
		//	printf("\n Mask1bitclear");
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		////condition->bitState = false;
		condition->Mask1= _ttoi(bitNumber);
		condition->CaseValue=0;
		condition->Cond1 = ~(_ttoi(bitNumber));
		return condition;
	}

	attr = element->GetAttribute("Mask2bitset");
	if (attr != "")
	{
		//	printf("\n Mask2bitset");
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		//condition->bitState = true;
		condition->Mask2= _ttoi(bitNumber);
		condition->Cond2 = _ttoi(bitNumber);
		condition->CaseValue=0;
		return condition;
	}

	attr = element->GetAttribute("Mask2bitclear");
	if (attr != "")
	{
		//	printf("\n Mask2bitclear");
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		////condition->bitState = false;
		condition->Mask2= _ttoi(bitNumber);
		condition->CaseValue=0;
		condition->Cond2 = ~(_ttoi(bitNumber));
		return condition;
	}


	attr = element->GetAttribute("Modeset");
	if (attr != "")
	{
		//	printf("\n Modeset");
		CString bitNumber;
		values.Lookup(attr, bitNumber);
		condition->bitValue =_ttoi(bitNumber);
		condition->CaseValue=1;
		return condition;
	}
	delete condition;
	ASSERT(0);
	return 0;
}
