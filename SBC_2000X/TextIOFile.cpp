/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextIOFile.cpp_v   1.11   28 Nov 2014 08:31:54   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/TextIOFile.cpp_v  $
 * 
 *    Rev 1.11   28 Nov 2014 08:31:54   rjamloki
 *  Warnings removed
 * 
 *    Rev 1.10   30 Jul 2014 04:39:06   rjamloki
 * Corrected Checking fseek return value
 * 
 *    Rev 1.9   28 Jul 2014 14:15:22   rjamloki
 * review comments fix.
 * 
 *    Rev 1.8   09 Jun 2014 11:54:20   rjamloki
 * Coverity fixes.
 * 
 *    Rev 1.7   20 May 2014 11:04:20   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.6   07 May 2014 13:18:40   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.5   28 Mar 2014 14:33:12   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:34 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:05:28 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:32 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:38 amaurya     
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:02 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "TextIOFile.h"
#include "ChildView.h"
#include "SBC.h"
#include "VGA.h"

#ifdef DISABLEPRINTF
#define printf
#endif


CStringArray CTextFileIO::sstID;
CStringArray CTextFileIO::sststring;
int CTextFileIO::SstFont[50];
int CTextFileIO::SstFontSize[50];
int CTextFileIO::Languagearray=0;
int CTextFileIO::fontcount=0;
int CTextFileIO::FontSizeCount=0;
int CTextFileIO::no_of_strings;
int CTextFileIO::gh;
CString CTextFileIO::CurrentFontName;
int CTextFileIO::CurrentFontChar_Set;

CTextFileIO::~CTextFileIO(void)
{
	if(sstID.GetSize()>0)
	{
		//printf("\n sstID");
		sstID.RemoveAll();
	}
	if(sststring.GetSize()>0)
	{
		// printf("\n sststring");
		sststring.RemoveAll();
	}
	if(_file)
	{
		fclose(_file);
	}
}

CTextFileIO::CTextFileIO(CString filename,  WCHAR *mode,bool FirstTime)
{
	indicator=' ';
	no_of_strings=0;
	gh=0;
	pos=0;

	count=0;//

	encodingType=CTextFileIO::CheckFileEncodingTypeW(filename);
	_IsValidate = (OpenW(filename,mode,FirstTime) != 0);

}



// Open file,UNICODE version
BOOL CTextFileIO::OpenW(CString  filename, WCHAR *mode,bool FirstTime)
{
	_file=_wfopen(filename,mode);
	if(_file==NULL)
	{
		AfxMessageBox(_T("Can't open file '") + filename + _T("'"));
		// Again Open the File
		filename=_T("Disk\\languages\\English.lan");
		_file=_wfopen(filename,L"rb");
	}
	// Seek  file pos
	if(wcschr(mode,L'r')!=NULL)
	{
		if(OmitEncodingTag(encodingType)==-1)
			return FALSE;
	}

	return TRUE;
}

// Read a line from file,return value is UNICODE string
wint_t CTextFileIO::_ReadLine(CString s1, wint_t eol, wint_t eof)
{

	int length=1;
	fgetpos( _file, &pos );
	long position = (long)pos;
	// read one wide char at a time & Calculate Length
	while (true)
	{
		// read wide char
		wint_t c = fgetwc(_file);
		if(feof(_file))
		{
			break;
		}
		// check for EOL
		if (c == eol) 
		{
			fgetpos( _file, &pos );
			break;
		}

		length++;
	};
	int i=length;

	int count=0;
	// Allocate the Buffer according to length
	LPTSTR p = s.GetBuffer(i);
	if(fseek(_file,(long)position,SEEK_SET) == 0)
	{
		while (true)
		{
			if(feof(_file))
				break;
			// read wide char
			wint_t c = fgetwc(_file);
			// check for EOL
			if (c == eol) 
			{
				p[count]='\0';	
				s.ReleaseBuffer();
				return c;
			}
			else
			{
				// Skip lineFeed char        
				if((c!=LF))
					p[count++]=c;
			}
		}
	}

	return eof;
}


// Unicode version of read line
void CTextFileIO::ReadLineW(bool FirstTime,bool skipFirstLine)
{
	//printf("in CTextFileIO::ReadLineW() count=%d\n",count);
	bool bResult=false;
	CString ws;
	if(this->_file == NULL)
	{     	
		printf("NULL pointer CTextFileIO::ReadLineW\n");
		return;
	}
	while (!feof(_file))
	{

		//printf("\n getfile");
		indicator=_ReadLine(s);
		//Exit if EOF of file is found.
		if(indicator==EOF_FILE)
			break;
		ws=s;
		count++;
		//printf("ws=%s count=%d\n",ws,count);

		if(count==TOTALANGINDEX)
		{
			//printf("count==TOTALANGINDEX\n");
			if(ws=="")
			{
				AfxMessageBox(_T("No total No of strings found in .lan file"));
				theApp.Clean ();
				exit(1);
			}
			int fg=_ttoi(ws);
			//printf("\n fg=%d",fg);
			sstID.SetSize(fg);
			sststring.SetSize(fg);
			theApp.TotalLangElement=fg;
		}
		else if(count==FONTNAMEINDEX)
		{
			// printf("count==FONTNAMEINDEX\n");
			CurrentFontName=ws;
		}
		else if(count==CHARSETINDEX)
		{
			//printf("count==CHARSETINDEX\n");
			CurrentFontChar_Set=_ttoi(ws);
			//printf("\n CurrentFontChar_Set=%d",CurrentFontChar_Set);
		}
		else if(count>FLAGFILEINDEX)
		{
			//printf("count>FLAGFILEINDEX no_of_strings=%d \n", no_of_strings);

			sstID[no_of_strings++]=ws.SpanExcluding(_T(","));
			//printf("SpanExcluding()\n");

			int index=ws.Find (_T(","));
			//printf("Find()\n");

			index=ws.GetLength ()-index;
			//printf("GetLength()\n");

			CString str=ws.Right(index-1);
			//printf("Right()\n");

			index=str.Find (_T(","));
			//printf("Find()\n");

			index=str.GetLength ()-index;
			//printf("GetLength()\n");

			str= str.Right(index-1);
			//printf("Right()\n");

			sststring[gh++]=str;


			fgetpos( _file, &pos );
			//printf("fgetpos()\n");

			fseek(_file,(long)pos,SEEK_SET);
			//printf("fseek()\n");
		}

	}
	if(_file)
	{
		fclose(_file);
		//printf("file closed\n");
	}
}

// Check file encoding type
CTextFileIO::EncodingType CTextFileIO::CheckFileEncodingTypeW(const WCHAR* const filename)
{
	FILE* _file=_wfopen(filename,L"rb");
	// Read first 4 byte for testing
	BYTE* buf=new BYTE[4];
	size_t nRead=fread((void*)buf,sizeof(BYTE),4,_file);
	//printf("\n nRead=%d",nRead);
	if((nRead==0)||(nRead==2))
	{
		AfxMessageBox(_T("No .lan file found in SystemConfig.cfg or in /Disk Folder"));
		theApp.Clean ();
		exit(1);
	}
	// Close file
	fclose(_file);

	BYTE utf16_le[]={0xFF,0xFE};
	if(memcmp(buf,&utf16_le,2)==0)
	{
		delete []buf;
		return UTF16_LE;
	}
	delete []buf;
	return ANSI;
}


// Omit file encoding tag
int CTextFileIO::OmitEncodingTag(EncodingType type)
{
	int nResult=0;
	nResult=fseek(_file,2,SEEK_SET);
	return nResult;
}