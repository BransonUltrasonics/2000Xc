/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlElement.h_v   1.3   28 Mar 2014 14:33:24   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/XmlElement.h_v  $
 * 
 *    Rev 1.3   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     03 Jan 2014 09:06:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:01:10 rjamloki      
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:18 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_)
#define AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CXmlElement  
{
   friend class CSBCApp;
   friend class CEnumVariable;
   friend class CBitmaskVariable;
   friend class CVgaMenu;
   friend class CVgaTitle;
   friend class CVgaSubMenu;
   friend class CVgaChoice;
   friend class CText;
   friend class CToggle;
   friend class CRadioMenu;
   friend class CVgaVariable;
   friend class CDate;
   friend class CVgaTime;
   friend class CVgaButton;
   friend class CVgaRadioButton;
   friend class CMsgScreen;
   friend class CListBoxObject;
   friend class CVgaAlphanumeric;
   friend class CBottomHalf;
   friend class CCheck;
   friend class CLine;
   friend class CRunScreen;
   friend class CWeldingHistory;
public:
   bool GetBoolAttribute(const CString & attr) const;
   CString GetAttribute(const CString & attr) const;
   const CString & GetTag() const
   {
      return tag;
   }
   void Write(const CString & fileName) const;
   void SetTag(const CString & t)
   {
      tag = t;
   }
   void SetContents(const CString & c)
   {
      contents = c;
   }
   void SetAttribute(const CString & parameter, const CString & value);
   void AddChild(CXmlElement * e)
   {
      children.AddTail(e);
   }
   CXmlElement();
   virtual ~CXmlElement();


   void Indent(CStdioFile & file, int indent) const;
   void Write(CStdioFile & file, int indent) const;
   void Write(CStdioFile &file, const CString & string) const
   {
		//file.WriteString(string);
		//TRACE(string);
   }
   CString tag;
   CString contents;
   CMapStringToString attributes;
   CStringList attributeList;
   CTypedPtrList<CPtrList, CXmlElement *> children;
};

#endif // !defined(AFX_XMLELEMENT_H__3C4D3E7C_5E50_40ED_978D_A923EC4A3EA2__INCLUDED_)
