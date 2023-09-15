/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextIOFile.h_v   1.2   28 Mar 2014 14:33:12   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextIOFile.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:28 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/

#ifndef _TEXTFILEIO_H_
#define _TEXTFILEIO_H_
#define LF 13
#define EOF_FILE   65535
#pragma once

//#include <stdio.h>
#include <string>
//using namespace std;
//#include <windows.h>
//#include <tchar.h>

#define TOTALANGINDEX   2
#define  FONTNAMEINDEX  3
#define  CHARSETINDEX   4
#define FLAGFILEINDEX   5

class CTextFileIO
{
public:
   int count;
   static int Languagearray;
   static int fontcount;
   static int FontSizeCount;
   wint_t indicator;
   static int no_of_strings;
   static int gh;
   fpos_t pos;
   static CStringArray sstID;
   static CStringArray sststring;
   static int SstFont[50];
   static int SstFontSize[50];
   static CString CurrentFontName;
   static int CurrentFontChar_Set;
public:
   ~CTextFileIO(void);
public:
   CTextFileIO(CString filename,WCHAR *mode,bool FirstTime);

public:
   // Open the file
   BOOL OpenW(CString  filename,  WCHAR *mode,bool FirstTime);

private:
   // Internale FILE object 
   FILE* _file;
   CString s;
public:

   // Read aline from a UNICODE file
   // Return value:if end of file,return value is false,else is true
   wint_t _ReadLine(CString s, wint_t eol=L'\n', wint_t eof=WEOF);
   // Unicode version of read line
   void ReadLineW(bool FirstTime,bool skipFirstLine);


public:
   // Text file encoding type enum
   enum EncodingType {ANSI,UTF16_LE,UTF16_BE,UTF32_LE,UTF32_BE,UTF_8};
private:
   // File encoding type
   EncodingType encodingType;
public:
   // Check file encoding type
   static EncodingType CheckFileEncodingTypeW(const WCHAR* const filename);

public:
   // Get current open file's encoding type
   CTextFileIO::EncodingType GetEncodingType(void)
   {
      return encodingType;
   }
   // Omit file encoding tag
   int OmitEncodingTag(EncodingType type);
   // Indicate file can be read or not
   bool _IsValidate;
public:

   // Check file is validate to read
   bool IsValidate(void)
   {
      return _IsValidate;
   }

};

#endif
