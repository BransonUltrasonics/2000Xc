/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryData.cpp_v   1.16   26 Jan 2015 13:32:08   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HistoryData.cpp_v  $
 * 
 *    Rev 1.16   26 Jan 2015 13:32:08   rjamloki
 * Removed printf
 * 
 *    Rev 1.15   28 Nov 2014 08:31:06   rjamloki
 * Removed Warnings and commented code.
 * 
 *    Rev 1.14   14 Nov 2014 02:53:52   rjamloki
 * extern int HistorySetUp removed.
 * 
 *    Rev 1.13   10 Nov 2014 02:49:56   rjamloki
 * DrawUSBHistory() changed for UDIScan length.
 * 
 *    Rev 1.12   28 Jul 2014 13:59:32   rjamloki
 * added macro MAX_ALARM_STRING_LEN
 * 
 *    Rev 1.11   09 Jul 2014 06:56:40   akaushal
 * Function CHistoryData(),InitilizeAllValues() changed.
 * 
 *    Rev 1.10   09 Jun 2014 11:44:30   rjamloki
 * Variable initialization in constructor.Changes for weld histroy setup.
 * 
 *    Rev 1.9   27 May 2014 18:02:24   akaushal
 * History Setup Updated for Weld Result screen
 * 
 *    Rev 1.8   27 May 2014 06:31:20   amaurya
 * Updated the code for Column width on display and pdf
 * 
 *    Rev 1.7   20 May 2014 10:57:48   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.6   07 May 2014 13:18:26   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.5   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     26 Mar 2014 14:22:30 rjamloki     
 * removed debugging printf
 *
 *    Rev 1.3     05 Mar 2014 14:13:18 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:56 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:22 amaurya     
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya    
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "HistoryData.h"
#include "WeldingHistory.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define MAX_ALARM_STRING_LEN 8

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHistoryData::CHistoryData()
{
	Lang_Index = 0;
	TextColour = Black;
	UniqueId = 0;
	TotalColoumn = 0;
	Units = 0;
}

/************************************************************************/
/* The conctructor is used to make history data object wen the data		*/
/* is read from USB														*/
/************************************************************************/
CHistoryData::CHistoryData(unsigned char * &data, int & length)
{	
	int j =0;
	InitilizeAllValues();
	Lang_Index=CChildView::Language_Index;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
	//data+=9;		
	//	length-=9;
	//printf("\n CHistoryData HistoryData");
	TotalColoumn = *data++;
	length--;

	//  printf("\n TotalColoumn=%d",TotalColoumn);
	/* Storing Total Coloumn Ids.*/

	for(j =0;j<TotalColoumn;j++)
	{
		USBParamIDs[j]=*data++;
		length--;
	}
	int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int TotalCycles=*data++;length--;/* must be one */
	// printf("\n TotalCycles HistoryData=%d",TotalCycles);

	Units=CChildView::metric;
	/*Storing data of all cycles.*/

	
	for(int i=0;i<TotalCycles;i++)
	{
		TextColour = *data++;	//Storing text colour for each cycle.
		length--;

		/*Storing Weld Data.*/
		for(j =0;j<TotalColoumn;j++)
		{
			CString result =GetWeldDataString(data, length);	
			CopyToUSB(result,(TCHAR*)&USBAllParamValues[j][0]);
		}


		/*Storing Mode Preset String for each cycle.*/
		CString Mode_PresetString =GetMode_PresetString(data, length);

		/*Storing Date and Time String for each cycle.*/

		StoreDate_Time(data,length);
		for(int j =0;j<MAX_ALARM_STRING_LEN;j++)
		{
			AlarmString[j] =ntohl(*((int*)data));
			data+=4;		
			length-=4;
		}
		data+=1;
		length-=1;
		CopyToUSB(Mode_PresetString,(TCHAR*)&USBMode_PresetString[0]);

	}

	CString Unit;
	for(j =0;j<TotalColoumn;j++)
	{
		for(int k=0;k<CChildView::TotalTextHeading;k++)
		{
			if(USBParamIDs[j]==CChildView::Parameter_ID[k])
			{
				if(Units)
					Unit =CChildView::Parameter_Units_Metric[k];
				else
					Unit =CChildView::Parameter_Units_USCS[k];

				for(int i=0;i<Unit.GetLength();i++)
				{
					if(Units)
					{
						CWeldingHistory::ParameterUnitMetric[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitMetric[j][i+1]='\0';
					}
					else
					{
						CWeldingHistory::ParameterUnitUSCS[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitUSCS[j][i+1]='\0';
					}
				}
			}
		}

	}


}

CHistoryData::~CHistoryData()
{

}

/*****************************************************************************/
/* this function is used to get weld data string form the data comming from	 */
/* welder. This is required because Weld data comes in syngle bye in all	 */
/* languages																 */
/*****************************************************************************/
CString CHistoryData::GetWeldDataString(unsigned char * &data,int & length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	for (int i = 0; i < strlen; i++)
	{
		union {
			unsigned char ch[2];
			TCHAR character;
		}u;
		u.ch[1]=NULL;
		u.ch[0]= *data++;
		result += (u.character);
	}
	length -= count+1;
	result.TrimRight();
	result.TrimLeft();
	//printf("result  = %S\n",result);
	return result;
}

/******************************************************************/
/* This function is used to create Date and Time string using the */
/* information comming from 332.								  */
/******************************************************************/	
void CHistoryData::StoreDate_Time(unsigned char *&data, int &length)
{
	/*Storing Date.*/
	CString Date;
	CString Time;
	char TempArray[MAXDATETIMELENGTH];

	int Temp =*data++;length--;
	CString TempDay =	_itoa(Temp,TempArray,10);
	if(TempDay.GetLength() ==1)
		TempDay = "0"+TempDay;
	if(CChildView::Language_Index <= Asian_Language_Start)
		TempDay +="/";

	Temp =*data++;length--;
	CString TempMonth = 	_itoa(Temp,TempArray,10);
	if(TempMonth.GetLength() ==1)
		TempMonth = "0"+TempMonth;
	TempMonth +="/";

	Temp =*data++;length--;
	CString TempYear = 	_itoa(Temp,TempArray,10);
	if(TempYear.GetLength() ==1)
		TempYear = "0"+TempYear;

	if(CChildView::Language_Index>Asian_Language_Start)
		Date ="20"+TempYear+"/"+TempMonth+TempDay;
	else if(Units)
		Date =TempDay+TempMonth+TempYear;
	else
		Date =TempMonth+TempDay+TempYear;


	/* Storing Time.*/
	Temp =*data++;length--;
	CString TempHour = _itoa(Temp,TempArray,10);
	if(TempHour.GetLength() ==1)
		TempHour = "0"+TempHour;
	TempHour +=":";
	Temp =*data++;length--;
	CString TempMinute = _itoa(Temp,TempArray,10);
	if(TempMinute.GetLength() ==1)
		TempMinute = "0"+TempMinute;
	TempMinute +=":";
	Temp =*data++;length--;
	CString TempSecond = _itoa(Temp,TempArray,10);
	if(TempSecond.GetLength() ==1)
		TempSecond = "0"+TempSecond;
	Time =TempHour+TempMinute+TempSecond;
	CopyToUSB(Date,(TCHAR*)&USBDateStr[0]);
	CopyToUSB(Time,(TCHAR*)&USBTimeStr[0]);
}

/****************************************************************/
/* This function is used to create the mode preset screen from	*/
/* mode numer and preset number									*/
/****************************************************************/
CString CHistoryData::GetMode_PresetString(unsigned char * &data,int & length)
{
	
	int LangIndex = Lang_Index;
	/*Getting Mode */
	int Mode_Num =*data++;
	length--;

	/*Getting Preset Number.*/
	int Preset_Num = *data++;
	length--;

	/*Getting PresetName.*/
	CString PresetName = GetWeldDataString(data,length);

	/*Preparing Mode Preset String.*/

	/////////////////////////////////////////
	CString str1 = CChildView::thisPtr->PString[0];
	CString str2 = CChildView::thisPtr->PString[1];
	CString str3 = CChildView::thisPtr->PString[2];
	CString str4 = CChildView::thisPtr->PString[3];
	CString str5 = CChildView::thisPtr->PString[4];
	CString str6 = CChildView::thisPtr->PString[5];
	CString str7 = CChildView::thisPtr->PString[6];
	CString str8 = CChildView::thisPtr->PString[7];

	CString FinalString;

	switch(Mode_Num)
	{  /* Get the weld mode string.  */
	case TIMEMODE:
		FinalString = str1;
		break;

	case ENERGYMODE:
		FinalString = str2;
		break;

	case PKPOWERMODE:
		FinalString = str3;
		break;

	case COLLAPSEMODE:
		FinalString = str4;
		break;

	case ABSOLUTEMODE:
		FinalString = str5;
		break;

	case GRDDETECTMODE:
		FinalString = str6;
		break;

	case CONTINUOUSMODE:
		FinalString = str7;
		break;

	default:
		FinalString = str1;
		break;   
	}

	FinalString +=", "+ str8;
	char pr[5];
	sprintf(pr,"%d",Preset_Num);
	FinalString +=pr;
	FinalString +=" - " +PresetName;

	

	FinalString.ReleaseBuffer();

	return FinalString;
}

/************************************************************/
/* This function is used to convert CString type object		*/
/* to char array. this is done so that data could be written*/ 
/* in USB													*/
/************************************************************/
void CHistoryData::CopyToUSB(CString Str1, TCHAR *Str2)
{
	int length = Str1.GetLength();
	for(int i=0;i<length;i++)
		*(Str2+i)= Str1.GetAt(i);
	*(Str2+length)='\0';
}

/************************************************************************************/
/* This function is used to draw one USB History weld data. Line Number is			*/	
/* passed to tell the line number of the history data on screen. Left most parameter*/
/* tells the weld data left most parameter on the screen							*/
/************************************************************************************/	
void CHistoryData::DrawUSBHistory(CDC *pDC,int LeftMostParameter, int LineNo)
{
	int DisplayCount =  1;
	CRect ParamValueRect;
	CString paramValStr ="";
	static UINT8 widthArr[32]={160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160};
	int ColumnNo=0;
	/*Drawing parameter Values.*/
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_WidthHistory),
		(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
		(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_WidthHistory),
		(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));

	CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, USBAllParamValues[0],false);
	ColumnNo=1;
	for (int Index = LeftMostParameter; Index < (int)HisParameterCounts ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_WidthHistory),
			(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
			(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
			(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));
		paramValStr = USBAllParamValues[HisParameterMap[Index]-1];
		if(paramValStr.GetLength() > MAXPARAMVALDISPLEN)
		{
			paramValStr.SetAt(MAXPARAMVALDISPLEN-2,'.');
			paramValStr.SetAt(MAXPARAMVALDISPLEN-1,'.');
			paramValStr = paramValStr.Left(MAXPARAMVALDISPLEN);
		}
		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, paramValStr,false);
		ColumnNo++;
	}
}

/****************************************************************************/
/* This function is called when user clicks on History data. Nothing has	*/
/* to be done here.															*/
/****************************************************************************/
bool CHistoryData::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}

/****************************************************************************/
/* History data is drawn in function Draw USBHistory(), so no use of this 	*/
/* function. Definition is requires because it is derived from an abstract	*/
/*  class.																	*/
/****************************************************************************/
void CHistoryData::Draw(CDC *pDC)
{
}

/********************************************************************************/
/* The following function is used to Initilize all the Parameters. This is done */
/* so that no garbage value is written in USB									*/
/********************************************************************************/
void CHistoryData::InitilizeAllValues()
{
	int len=0;
	for(len=0;len<MAXDATETIMELENGTH;len++)
	{
		USBTimeStr[len]='\0';
		USBDateStr[len]='\0';
	}
	for(len=0;len<MAXMODEPRESETLENGTH;len++)
		USBMode_PresetString[len]='\0';
	for(len=0;len<MAXPARAMVALUES;len++)
	{
		USBParamIDs[len]='\0';
		for(int i=0;i<MAXPARAMVALUELENGTH;i++)
			USBAllParamValues[len][i]='\0';
		
	}
	for(len=0;len<MAX_ALARM_STRING_LEN;len++)
	{
		AlarmString[len]=0;
	}
}

CHistoryData::CHistoryData(int Difference,unsigned char * &data, int & length)
{	
	int j =0;
	InitilizeAllValues();
	Lang_Index=CChildView::Language_Index;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
	

	TotalColoumn = *data++;
	length--;

	/* Storing Total Coloumn Ids.*/

	for(j =0;j<TotalColoumn;j++)
	{
		USBParamIDs[j]=*data++;
		length--;
	}
	int ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int TotalCycles=*data++;length--;/* must be one */

	Units=CChildView::metric;
	/*Storing data of all cycles.*/

	//if(TotalCycles==1)
	for(int i=0;i<Difference;i++)
	{
		TextColour = *data++;	//Storing text colour for each cycle.
		length--;

		/*Storing Weld Data.*/
		for(j =0;j<TotalColoumn;j++)
		{
			CString result =GetWeldDataString(data, length);	
			CopyToUSB(result,(TCHAR*)&USBAllParamValues[j][0]);
		}


		/*Storing Mode Preset String for each cycle.*/
		CString Mode_PresetString =GetMode_PresetString(data, length);

		/*Storing Date and Time String for each cycle.*/

		StoreDate_Time(data,length);
		for(int j =0;j<MAX_ALARM_STRING_LEN;j++)
		{
			AlarmString[j] =ntohl(*((int*)data));
			data+=4;		
			length-=4;
		}
		data+=1;
		length-=1;
		CopyToUSB(Mode_PresetString,(TCHAR*)&USBMode_PresetString[0]);

	}

	CString Unit;
	for(j =0;j<TotalColoumn;j++)
	{
		for(int k=0;k<CChildView::TotalTextHeading;k++)
		{
			if(USBParamIDs[j]==CChildView::Parameter_ID[k])
			{
				if(Units)
					Unit =CChildView::Parameter_Units_Metric[k];
				else
					Unit =CChildView::Parameter_Units_USCS[k];

				for(int i=0;i<Unit.GetLength();i++)
				{
					if(Units)
					{
						CWeldingHistory::ParameterUnitMetric[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitMetric[j][i+1]='\0';
					}
					else
					{
						CWeldingHistory::ParameterUnitUSCS[j][i] = Unit.GetAt(i);
						CWeldingHistory::ParameterUnitUSCS[j][i+1]='\0';
					}
				}
			}
		}
	}
}
