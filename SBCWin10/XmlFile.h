/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlFile.h_v   1.2   28 Mar 2014 14:33:26   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlFile.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:26   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:06:32 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:18 amaurya      
 * Initial Revision.
*/	


#if !defined(AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_)
#define AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXmlElement;

class CXmlFile  
{
public:
   bool Comment;
	CXmlElement * Read(CArchive & ar);
	CXmlFile();
	virtual ~CXmlFile();

protected:
	CString ReadString();
	CString ReadIdentifier();
   void CheckStartComment();
   void CheckComment();
	CXmlElement * ReadElement();
	void Expect(char ch);
	void SkipBlanks();
	void Error(const CString &message)
	{
		throw message;
	}
	void ReadChar(bool skipBlanks = true);
	CArchive * archive;
	int lineNumber;
	char lastch;
   bool flag1;
};

#endif // !defined(AFX_XMLFILE_H__5E640096_3AF2_432D_9F54_D0383F069D54__INCLUDED_)
