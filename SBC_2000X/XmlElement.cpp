/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlElement.cpp_v   1.2   28 Mar 2014 14:33:24   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlElement.cpp_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:18 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "SBC.h"
#include "XmlElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXmlElement::CXmlElement()
{
}

CXmlElement::~CXmlElement()
{
	while (children.GetCount() > 0)
		delete children.RemoveHead();
}

void CXmlElement::Write(const CString &fileName) const
{
	CStdioFile file;
	if (file.Open(fileName, CFile::modeWrite | CFile::modeCreate))
	{
		Write(file, 0);
	}
}

void CXmlElement::Write(CStdioFile &file, int indent) const
{
	CString line;

	Indent(file, indent);
	Write(file, "<" + tag);
	POSITION pos = attributeList.GetHeadPosition();
	while (pos)
	{
		CString param = attributeList.GetNext(pos);
		CString value;
		attributes.Lookup(param, value);
		Write(file, " " + param + "=\"" + value + "\"");
	}
	if (children.GetCount() > 0)
	{
		Write(file, ">\n");
		pos = children.GetHeadPosition();
		while (pos)
		{
			CXmlElement * e = children.GetNext(pos);
			e->Write(file, indent + 1);
		}
	}
	if (!contents.IsEmpty())
	{
		Write(file, ">" + contents + "</" + tag + ">\n");
	}
	// no text, but at least a child or attribute
	else if (children.GetCount() > 0)	// some children
	{
		Indent(file, indent);
		Write(file, "</" + tag + ">\n");
	}
	else
	{
		Write(file, "/>\n");
	}
}

void CXmlElement::Indent(CStdioFile &file, int indent) const
{
	while (indent-- > 0)
		Write(file, "        ");
}

void CXmlElement::SetAttribute(const CString & parameter, const CString & value)
{
	attributes.SetAt(parameter, value);
	attributeList.AddTail(parameter);
}

CString CXmlElement::GetAttribute(const CString & attr) const
{
	CString value;
	if (!attributes.Lookup(attr, value))
		return "";
	return value;
}

bool CXmlElement::GetBoolAttribute(const CString &attr) const
{
	CString value = GetAttribute(attr);
	return value == "true";
}
