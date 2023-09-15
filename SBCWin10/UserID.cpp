/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserID.cpp_v   1.9   09 Jul 2014 07:09:04   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserID.cpp_v  $
 * 
 *    Rev 1.9   09 Jul 2014 07:09:04   akaushal
 * GetRTCTime() function changed
 * 
 *    Rev 1.8   09 Jun 2014 11:55:52   rjamloki
 * GetRTCTime() changed.DecimalToBCD() removed
 * 
 *    Rev 1.7   27 May 2014 18:08:48   akaushal
 * Updated the format for Date to mm/dd/yy
 * 
 *    Rev 1.6   20 May 2014 11:08:40   rjamloki
 * Macro to disable printf.  
 * 
 *    Rev 1.5   07 May 2014 13:11:58   akaushal
 * Date format updated to MM:DD:YY
 * 
 *    Rev 1.4   21 Apr 2014 13:47:30   akaushal
 * Added function to support PDF creation in asian language.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     26 Mar 2014 14:24:32 rjamloki   
 * toLittleEndian() function added as ntohl and ntohs not working in event history removed UserID::TotalCycles,UserID::index,UserID::LastCycleFlag variables 
 *
 *    Rev 1.1     06 Mar 2014 11:30:44 rjamloki  
 * Add new User ID function
 *
 *    Rev 1.0     05 Mar 2014 14:43:16 rjamloki      
 * Initial Revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "UserID.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern POSITION UserIDTemp_pos;


//CTypedPtrList<CPtrList, UserID *> IDDataNewList;
extern CList<CString,CString> tempUserIDList;

void GetRTCTime(RTCTime * CreateModifyTime,char * Buff)
{
	UINT8 sec = CreateModifyTime -> Second;
	UINT8 min = CreateModifyTime -> Minute;
	UINT8 hrs = CreateModifyTime -> Hour;
	sprintf(Buff,"%02d:%02d:%02d",hrs, min, sec);
}

void GetRTCDate(RTCTime *CreateModifyTime,char * Buff)
{
	UINT8 dat = CreateModifyTime -> Day;
	UINT8 day = CreateModifyTime -> Weekdays;
	UINT8 mon = CreateModifyTime -> Century_Month;
	UINT8 yrs = CreateModifyTime -> Years;	

	if(CChildView::metric) //DD:MM:YY
		sprintf(Buff,"%02d/%02d/%02d", dat ,mon, yrs);
	else  //MM:DD:YY 		
   		sprintf(Buff,"%02d/%02d/%02d", mon ,dat, yrs);
}

int unicode2UTF(int unicode,int *length)
{
	//printf("unicode2UTF \n");
	int UTF8Code = 0x00;

	if ( unicode <= 0x7F)   // Max 0x7F  unicode character
	{
		UTF8Code = unicode;
		*length = 1;
	}

	else if(unicode < 0x7FF)  // Max 0x7FF unicode character 
	{
		UTF8Code = ((0xC000 | (( 0x07C0 & unicode)<<2)) | (0x80| (0x3F & unicode))); //lower 6bits with first Byte and Upper 5 bits with second Byte
		*length = 2;
	}

	else if (unicode < 0xFFFF)   // Max 0xFFFF unicode character 
	{
		UTF8Code = ((0xE00000 | ((0xF000 & unicode)) <<4) | (0x8000 | (( 0x0FC0 & unicode)<<2)) | (0x80| (0x3F & unicode)));
		*length = 3;
	}

	return UTF8Code;
}

int unicodeToUTF8(int unicode ,unsigned char *UTF8)
{
	*((int *)UTF8) = 0L;

	if( unicode <= 0x7F )
	{
		UTF8[0] = 0x7F & unicode;
		return 1;
	}

	if( unicode > 0x7F && unicode<= 0x7FF )
	{
		UTF8[0] = 0xC0 | (0x1F & (unicode >> 6)); //msb
		UTF8[1] = 0x80 | (0x3F & unicode);
		return 2;
	}

	if( unicode > 0x7FF && unicode <= 0xFFFF )
	{
		UTF8[0] = 0xE0 | (0x0F & (unicode >> 12)); //msb
		UTF8[1] = 0x80 | (0x3F & (unicode >> 6)) ;
		UTF8[2] = 0x80 | (0x3F & unicode);
		//printf("unicode = %X  utf8 = %X %X %X \n",unicode,UTF8[0],UTF8[1],UTF8[2]);
		return 3;
	}

	return 0; 
}

