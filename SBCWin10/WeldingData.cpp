/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingData.cpp_v   1.13   16 Apr 2015 06:06:52   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/WeldingData.cpp_v  $
 * 
 *    Rev 1.13   16 Apr 2015 06:06:52   sesharma
 * Hard-coded strings removed.
 * 
 *    Rev 1.12   26 Jan 2015 13:41:22   rjamloki
 * Removed printfs
 * 
 *    Rev 1.11   10 Nov 2014 02:52:34   rjamloki
 * CWeldingData::Draw() changed .
 * 
 *    Rev 1.10   09 Jul 2014 07:26:54   akaushal
 * PrintAlarms1() GetAlarms1() function removed.
 * 
 *    Rev 1.9   09 Jun 2014 12:07:48   rjamloki
 * removed printing function.
 * 
 *    Rev 1.8   20 May 2014 11:17:06   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.7   07 May 2014 13:18:42   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.6   21 Apr 2014 13:55:08   akaushal
 * ONEHEADINGGAP,TWOHEADINGGAP,ABSGAP removed
 * 
 *    Rev 1.5   28 Mar 2014 14:33:24   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     26 Mar 2014 14:27:14 rjamloki      
 * removed debugging printf 
 *
 *    Rev 1.3     05 Mar 2014 14:14:06 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:06:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:48 amaurya    
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:16 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "WeldingData.h"
#include "XmlElement.h"
//libharu headers starts
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <exception>
#include "hpdf.h"
#include "zlib.h"
#include "png.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "RunScreen.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CArray<CString,CString &> PresetString;
bool CWeldingData::ValueFlag=false;

extern CList<CString,CString>tempHistoryList;
extern CList<CString,CString>tempWeldList;
extern CList<CString,CString>tempGraphsList;
extern CList<CString,CString>tempScreenGraphsList;
extern CList<CString,CString>tempRunScreenList;
extern POSITION RunScreenTemp_pos;
extern POSITION ScreenGraphsTemp_pos;
extern POSITION GraphsTemp_pos;
extern POSITION HistoryTemp_pos;
extern POSITION WeldTemp_pos;
//CWeldData::CWeldData()
//{}
/**********************************************************************************/
/*                                                                                */
/*  This function is called from CChildView class to Stores	Weld data to be       */
/*  printed	on Graphs printout or on WeldData or on WeldHistory Printouts.		  */														 
/*																				  */
/**********************************************************************************/
CWeldingData::CWeldingData(unsigned char * &data, int & length,bool PrintData)
{	
	Lang_Index=CChildView::Language_Index;
	TotalCyclesPrinted=0;
	HistoryObjectNum=0;
	HistoryContinued=false;
	int j =0;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
	//	data+=9;		
	//	length-=9;

	TotalColoumn = *data++;
	//printf("\n TotalColoumn in polling=%d",TotalColoumn);
	length--;

	/* Storing Total Coloumn Ids.*/
	AllParamIDs =new int[TotalColoumn];
	for(j =0;j<TotalColoumn;j++)
	{
		AllParamIDs[j]=*data++;
		//printf("\n AllParamIDs in polling=%d",AllParamIDs[j]);
		length--;
	}
	ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);

//	printf("\n ReceivedUniversalCount in polling=%d",ReceivedUniversalCount);    //4
	Parameter_Value =new CString[1];
	TotalCycles=*data++;
//	printf("const_TotalCycles = %d \n",TotalCycles);
	length--;
	//printf("\n TotalCycles in polling=%d",TotalCycles);
	ParamCount=TotalColoumn;
//	printf("TotalColoumn*TotalCycles +1 = %d\n",TotalColoumn*TotalCycles +1);
	AllParamValues =new CString[TotalColoumn*TotalCycles +1];
	Mode_PresetString=new CString[TotalCycles+1];
	Time_String=new CString[TotalCycles+1];
	Date_String=new CString[TotalCycles+1];

	NoCycleAlarms=new int[TotalCycles+1];
	OverloadAlarms=new int[TotalCycles+1];
	EquipmentFailureAlarms=new int[TotalCycles+1];
	CycleModifiedAlarms=new int[TotalCycles+1];
	CalibrateAlarms=new int[TotalCycles+1];
	Warnings=new int[TotalCycles+1];
	RejectBitResult=new int[TotalCycles+1];
	SuspectBitResult=new int[TotalCycles+1];

	Units=CChildView::metric;
	/*Storing data of all cycles.*/
	int index=0;
	for(int i=0;i<TotalCycles;i++)
	{
//		printf("traverse TotalCycles \n");
		TextColour = *data++;	//Storing text colour for each cycle.
//		printf("\n TextColour=%d",TextColour);  //1
		length--;

		/*Storing Weld Data.*/
		//		printf("\n");
		for(j =0;j<TotalColoumn;j++)
		{
			AllParamValues[index] =GetWeldDataString(data, length);
			/*for(int g=0;g<AllParamValues[index].GetLength ();g++)
			printf(" %c",AllParamValues[index].GetAt (g));*/
			index++;
		}

		/*Storing Mode Preset String for each cycle.*/
		*(Mode_PresetString+i) =GetMode_PresetString(data, length);

		/*Storing Date and Time String for each cycle.*/
		StoreDate_Time(data,length,Date_String+i,Time_String+i);
		StoreAlarmInformation(data,length,i);
	}

	PresetNumber  =CChildView::PresetNum;

//	printf("PresetNumber = %d \n",PresetNumber);  //0
	ColumnHeading = new CString[CChildView::TotalTextHeading];
	for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalTextHeading;TextHeadingNo++)
		ColumnHeading[TextHeadingNo]=CChildView::Parameter_Heading[TextHeadingNo];
}

/**********************************************************************************/
/*                                                                                */
/*  This function is called from CVGARunScreen class to Stores					  */
/*  weld data for one cycle														  */
/*																				  */
/**********************************************************************************/
CWeldingData::CWeldingData(unsigned char * &data, int & length)
{
	//	printf("\n CWeldData");
	TextColour = *data++;	//Storing text colour.
	//printf("\n TextColour in const=%d",TextColour);
	length--;
	//	Lang_Index=CChildView::Language_Index;
	Parameter_Value =new CString[CRunScreen::Displayable_columns];//CString[VGARunScreen::Displayable_columns];
	Mode_PresetString=new CString[1];
	Time_String=new CString[1];
	Date_String=new CString[1];
	AllParamValues=new CString[1];
	AllParamIDs=new int[1];

	NoCycleAlarms=new int[1];
	OverloadAlarms=new int[1];
	EquipmentFailureAlarms=new int[1];
	CycleModifiedAlarms=new int[1];
	CalibrateAlarms=new int[1];
	Warnings=new int[1];
	RejectBitResult=new int[1];
	SuspectBitResult=new int[1];

	Units=CChildView::metric;	
	/*Storing Weld Data of one cycle.*/
	//printf("\n");
	for (int para_num=0;para_num< CRunScreen::Displayable_columns/*VGARunScreen::Displayable_columns*/; para_num++)
	{
		Parameter_Value[para_num]=GetWeldDataString(data, length);	
		/*	for(int g=0;g<Parameter_Value[para_num].GetLength ();g++)
		printf(" %c",Parameter_Value[para_num].GetAt (g));*/
	}

	/*Storing Mode Preset String for each cycle.*/
	*Mode_PresetString =GetMode_PresetString(data, length);

	/*Storing Date and Time String for each cycle.*/
	StoreDate_Time(data,length,Date_String,Time_String);
	StoreAlarmInformation(data,length,0);
	PresetNumber  =CChildView::PresetNum;

	ColumnHeading = new CString[CChildView::TotalTextHeading];
	for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalTextHeading;TextHeadingNo++)
		ColumnHeading[TextHeadingNo]=CChildView::Parameter_Heading[TextHeadingNo];

}

/**********************************************************************************/
/*                                                                                */
/*  This function is called from CVGARunScreen class to Stores	Weld Data		  */
/*  to update RunScreen.														  */
/*																				  */
/**********************************************************************************/
CWeldingData::CWeldingData(unsigned char * &data, int & length,int TotalColoumn)
{
	Lang_Index=CChildView::Language_Index;
	ParamCount=TotalColoumn;
	TextColour = *data++;	//Storing text colour.
	//printf("\n TextColour in constructor=%d",TextColour);
	length--;
	Parameter_Value =new CString[CRunScreen::Displayable_columns];
	AllParamValues =new CString[TotalColoumn];
	Mode_PresetString=new CString[1];
	Time_String=new CString[1];
	Date_String=new CString[1];
	AllParamIDs =new int[1];

	NoCycleAlarms=new int[1];
	OverloadAlarms=new int[1];
	EquipmentFailureAlarms=new int[1];
	CycleModifiedAlarms=new int[1];
	CalibrateAlarms=new int[1];
	Warnings=new int[1];
	RejectBitResult=new int[1];
	SuspectBitResult=new int[1];

	Units=CChildView::metric;
	//printf("\n");
	/*Storing All coloumns data of one cycle.*/
	for(int j =0;j<TotalColoumn;j++)
	{
		AllParamValues[j] =GetWeldDataString(data, length);
		/*for(int g=0;g<AllParamValues[j].GetLength ();g++)
		printf(" %c",AllParamValues[j].GetAt (g));*/
	}

	//Storing Weld Data of one cycle to be Shown on screen.
	for (int para_num=0;para_num< CRunScreen::Displayable_columns; para_num++)
	{
		//	printf("\n param_num");
		if(CRunScreen::Parameter_ID[para_num] == 0)
			Parameter_Value[para_num]="---";
		else
			for(int i =0 ;i<TotalColoumn;i++)
			{
				//	printf("\n param_num inside");
				if(CRunScreen::Parameter_ID[para_num] == CRunScreen::ID_Array[i])
				{
					//printf("\n value match");
					Parameter_Value[para_num]=AllParamValues[i];
				}
			}
	}
	//	printf("\n date");

	/*Storing Mode Preset String for one cycle.*/
	*Mode_PresetString =GetMode_PresetString(data, length);

	/*Storing Date and Time String for each cycle.*/
	StoreDate_Time(data,length,Date_String,Time_String);
	StoreAlarmInformation(data,length,0);

	PresetNumber  = CChildView::PresetNum;
	ColumnHeading = new CString[CChildView::TotalTextHeading];
	for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalTextHeading;TextHeadingNo++)
		ColumnHeading[TextHeadingNo]=CChildView::Parameter_Heading[TextHeadingNo];
}

int CWeldingData::CycleCount=0;

CWeldingData::~CWeldingData()
{

	delete []Date_String;
	delete []Time_String;
	delete []Mode_PresetString;
	delete []AllParamValues;
	delete []AllParamIDs;
	delete []Parameter_Value;
	delete []ColumnHeading;
	delete []NoCycleAlarms;
	delete []OverloadAlarms;
	delete []EquipmentFailureAlarms;
	delete []CycleModifiedAlarms;
	delete []CalibrateAlarms;
	delete []Warnings;
	delete []RejectBitResult;
	delete []SuspectBitResult;
}


/**************************************************************************/
/*																		  */
/*  This function Draws a Weld Data of one cycle						  */
/*													  					  */
/**************************************************************************/
void CWeldingData::Draw(CDC *pDC)
{
	CString paramValStr = "";
	CRect ParamValueRect;
	CycleCount++;		//Increment the cycle count to draw the data in next raw.

	if(CycleCount>MAXCYCLEPERSCREEN)
		CycleCount=1;	//maximum seven cycles can be displayed on the screen.

	/*Drawing parameter Values.*/
	for (int Index = 0; Index <(CRunScreen::Displayable_columns)/*(VGARunScreen::Displayable_columns) */; Index++)
	{
		ParamValueRect =CRect((RUN_RESULT_TBL_START_X + Index * ParamRect_Width),
			(RUN_RESULT_TBL_START_Y+LINE_GAP*(CycleCount+3)),
			(RUN_RESULT_TBL_START_X + (Index+1) * ParamRect_Width),
			(RUN_RESULT_TBL_START_Y+LINE_GAP*(CycleCount+4)));
		CVgaMenuItem::DrawRect(pDC,CChildView::Back_Color, ParamValueRect);
		paramValStr = Parameter_Value[Index];
		//if value string exceeds 12 than truncate string to 12 charactes and replace last 
		//two characters with .. (fix specifically for UDI string)
		if(paramValStr.GetLength() > MAXPARAMVALDISPLEN)
		{
			paramValStr.SetAt(MAXPARAMVALDISPLEN-2,'.');
			paramValStr.SetAt(MAXPARAMVALDISPLEN-1,'.');
			paramValStr = paramValStr.Left(MAXPARAMVALDISPLEN);
		}
		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, paramValStr,false);
	}
}

/**********************************************************************************/
/*                                                                                */
/*  This function is called when any WeldData object is clicked by the user       */
/* this function will do nothing.												  */	
/**********************************************************************************/
bool CWeldingData::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}


/****************************************************************************************************/
/* Tis function prints the weld data that is required on the graphs printouts. The function			*/
/* prints the following values.																		*/
/* 1.Cycle number.																					*/
/* 2.Date String																					*/
/* 3.Time dtring.																					*/
/* 4.All weld parameters with their units.															*/
/* 5.All parameter values. If any weld parameter is not supported the "n/a" string is printed as	*/
/* its value.																						*/
/****************************************************************************************************/
void CWeldingData::Print(CDC *pDC ,CChildView *view)
{	
	CString CycleNumber,TimeString,DateString;
	if(GraphsTemp_pos!=NULL)
	{	CycleNumber=tempGraphsList.GetNext(GraphsTemp_pos);
	DateString=tempGraphsList.GetNext(GraphsTemp_pos);
	TimeString =tempGraphsList.GetNext(GraphsTemp_pos);
	}
	else
	{  CycleNumber=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
	DateString=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
	TimeString=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);
	}


	/*Print Mode Preset String.*/
	CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,MODEPRESETSTRINGRECT, *Mode_PresetString,false,Lang_Index);

	CString CycleNumber_str,Date_str,Time_str;

	/* Prepare Cycle number,Date and Time strings to be printed.*/
	CycleNumber_str=CycleNumber/*[Lang_Index]*/+AllParamValues[0];
	Date_str=DateString/*[Lang_Index]*/+(*Date_String);
	Time_str=TimeString/*[Lang_Index]*/+(*Time_String);

	/*Print Cycle Number,Date and Time string.*/
	CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CYCLENUMSTRRECT , CycleNumber_str,false,Lang_Index);
	CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,TIMESTRRECT , Time_str,false,Lang_Index);
	CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,DATESTRRECT , Date_str,false,Lang_Index);

	int XCord=PARAMETERSTARTXCORD ;
	int Ycord=PARAMETERSTARTYCORD ;

	//int TotalDataHeading= view->PrintGraphIDList.RemoveHead();
	int TotalDataHeading= view->GraphWeldDataIdArray[0];
	/*Printing weld data headings and weld data.*/
	for(int value =1;value<=TotalDataHeading;value++)
	{	
		//	int IDValue=view->PrintGraphIDList.RemoveHead();
		int IDValue=view->GraphWeldDataIdArray[value];
		for(int printvalue =0;printvalue<ParamCount;printvalue++)
		{
			if(*(AllParamIDs+printvalue)==IDValue)
			{	
				CString ParamValue =*(AllParamValues+printvalue);

				for(int i=0;i<CChildView::TotalTextHeading;i++)
				{
					if(*(CChildView::Parameter_ID +i)==IDValue)
					{
						CString Str = *(ColumnHeading+i);
						Str.TrimLeft();
						Str.TrimRight();
						CString ParameterString2;
						/*Break heading string in to two strings.*/
						CString ParameterString1 = Str.SpanExcluding(_T(" "));
						if(ParameterString1.GetLength()<Str.GetLength())
							ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
						else
						{
							ParameterString1 = Str.SpanExcluding(_T("."));
							ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
						}
						/*Drawing Headings.*/
						CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,Ycord,XCord+XCORDINC ,Ycord), ParameterString1,true,Lang_Index);
						CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,Ycord+ONELINEGAP ,XCord+XCORDINC ,Ycord+ONELINEGAP ), ParameterString2,true,Lang_Index);

						/*Drawing Units.*/
						if(CChildView::metric)
							CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,Ycord+TWOLINEGAP ,XCord+XCORDINC ,Ycord+TWOLINEGAP ),  *(CChildView::Parameter_Units_Metric+i),true,Lang_Index);
						else
							CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,Ycord+TWOLINEGAP ,XCord+XCORDINC ,Ycord+TWOLINEGAP ),  *(CChildView::Parameter_Units_USCS+i),true,Lang_Index);

						/*Print n/a if there is no value for particular coloumn.*/
						if(ParamValue.Find(_T("---"))>=0)
							ParamValue = NotApplicable;
						CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,Ycord+THREELINEGAP ,XCord+XCORDINC ,Ycord+THREELINEGAP ),ParamValue  ,true,Lang_Index);
						XCord+=GRAPHPARAMWIDTH ;
						if(XCord>MAXXCOORDINATE)
						{
							XCord=PARAMETERSTARTXCORD ;
							Ycord=PARAMETERSTARTYCORD +FIVELINEGAP ;
						}
					}
				}
			}
		}
	}
}


/****************************************************************************************************/
/* This function prints the weld data that is required on the weld result and Weld History			*/
/* printouts. The function prints the following values.												*/
/* 1.Cycle number.																					*/
/* 2.Date String																					*/
/* 3.Time dtring.																					*/
/* 4.Applicable weld parameters with their units.													*/
/* 5.Corresponding parameter values. 																*/
/****************************************************************************************************/
int CWeldingData::PrintWeldData(CDC *pDC, int YCord, bool DrawUnits, bool DrawPresetString, int HISTORYPAGENO,CChildView *view)
{	
	CString TimeString=tempWeldList.GetNext(WeldTemp_pos);
	CString DateString=tempWeldList.GetNext(WeldTemp_pos);

	/*Printing Weld Data.*/
	int XCord=PRINTWELDSTARTXCORD;
	int YCoordinate = YCord; 
	int value =0;
	//int TotalDataHeading= view->PrintWeldDataIDList.RemoveHead();
	int TotalDataHeading= view->WeldDataIdArray[0];
	int *IDArray =new int[TotalDataHeading];

	for(value =0;value<TotalDataHeading;value++)
		*(IDArray+value)=view->WeldDataIdArray[value+1];

	//*(IDArray+value)=view->PrintWeldDataIDList.RemoveHead();
	CString CycleNumString =" ";



	if(DrawUnits)
	{
		/*drawing cycle count, date and time strings*/
		CString Str = *(ColumnHeading);
		CString ParameterString1 = Str.SpanExcluding(_T(" "));
		CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));

		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD,XCord+XCORDINC ,PRINTWELDSTARTYCORD), ParameterString1,true,Lang_Index);
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+ONEHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+ONEHEADINGGAP ), ParameterString2,true,Lang_Index);


		CString ParamValue =AllParamValues[0];
		CycleNumString=ParamValue;

		if(YCoordinate==PRINTWELDSTARTYCORD)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCoordinate+FOURWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCoordinate+FOURWELDLINEGAP),ParamValue  ,true,Lang_Index);
		else if(DrawPresetString)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCoordinate+ONEWELDLINEGAP),ParamValue  ,true,Lang_Index);
		else
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCoordinate,XCord+XCORDINC-ABSGAP ,YCoordinate),ParamValue  ,true,Lang_Index);

		XCord+=PARAMWIDTH ;
		XCord+=40;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,PRINTWELDSTARTYCORD+ONEHEADINGGAP ,XCord+XCORDINC-ABSGAP ,PRINTWELDSTARTYCORD+ONEHEADINGGAP ), TimeString,true,Lang_Index);


		if(YCoordinate==PRINTWELDSTARTYCORD)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCoordinate+FOURWELDLINEGAP,XCord+XCORDINC -ABSGAP,YCoordinate+FOURWELDLINEGAP),*Time_String  ,true,Lang_Index);
		else if(DrawPresetString)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC -ABSGAP,YCoordinate+ONEWELDLINEGAP),*Time_String  ,true,Lang_Index);
		else
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCoordinate,XCord+XCORDINC -ABSGAP,YCoordinate),*Time_String  ,true,Lang_Index);

		XCord+=PARAMWIDTH ;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+ONEHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+ONEHEADINGGAP ), DateString,true,Lang_Index);
		if(Units)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+TWOHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+TWOHEADINGGAP ), "(d/m/y)",true,Lang_Index);
		else
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+TWOHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+TWOHEADINGGAP ), "(m/d/y)",true,Lang_Index);
		if(YCoordinate==PRINTWELDSTARTYCORD)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+FOURWELDLINEGAP,XCord+XCORDINC ,YCoordinate+FOURWELDLINEGAP),*Date_String  ,true,Lang_Index);
		else if(DrawPresetString)
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC ,YCoordinate+ONEWELDLINEGAP),*Date_String  ,true,Lang_Index);
		else
			CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate,XCord+XCORDINC ,YCoordinate),*Date_String  ,true,Lang_Index);

		XCord+=PARAMWIDTH ;

		for(value =0;value<TotalDataHeading;value++)
		{	
			int IDValue=*(IDArray+value);
			for(int printvalue =0;printvalue<ParamCount;printvalue++)
			{
				if(*(AllParamIDs+printvalue)==IDValue)
				{	
					CString ParamValue =*(AllParamValues+printvalue);
					for(int i=0;i<CChildView::TotalTextHeading;i++)
					{
						if(*(CChildView::Parameter_ID +i)==IDValue)
						{
							if(DrawUnits)
							{	
								CString Str = *(ColumnHeading+i);
								CString ParameterString1 = Str.SpanExcluding(_T(" "));
								CString ParameterString2 = Str.Right(Str.GetLength()-(1+ParameterString1.GetLength()));
								CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD,XCord+XCORDINC ,PRINTWELDSTARTYCORD), ParameterString1,true,Lang_Index);
								CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+ONEHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+ONEHEADINGGAP ), ParameterString2,true,Lang_Index);
								if(Units)
									CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+TWOHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+TWOHEADINGGAP ),  *(CChildView::Parameter_Units_Metric+i),true,Lang_Index);
								else
									CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,PRINTWELDSTARTYCORD+TWOHEADINGGAP ,XCord+XCORDINC ,PRINTWELDSTARTYCORD+TWOHEADINGGAP ),  *(CChildView::Parameter_Units_USCS+i),true,Lang_Index);
								CString ParamValue =AllParamValues[printvalue];
								if(ParamValue.Find(_T("---"))>=0)
									ParamValue = NotApplicable;
								if(YCoordinate==PRINTWELDSTARTYCORD)
									CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+FOURWELDLINEGAP,XCord+XCORDINC ,YCoordinate+FOURWELDLINEGAP),ParamValue  ,true,Lang_Index);
								else //if(DrawPresetString)
									CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC ,YCoordinate+ONEWELDLINEGAP),ParamValue  ,true,Lang_Index);
								//else
								//DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate,XCord+XCORDINC ,YCoordinate),ParamValue  ,true,Lang_Index);

								XCord+=PARAMWIDTH ;
							}
							break;
						}
						if(DrawPresetString)
						{
							DrawPresetString=false;
							if(YCoordinate==PRINTWELDSTARTYCORD)
								CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-3*PARAMWIDTH-TWOLINEGAP,YCoordinate+THREEWELDLINEGAP,XCord-3*PARAMWIDTH-TWOLINEGAP,YCoordinate+THREEWELDLINEGAP),*Mode_PresetString  ,false,Lang_Index);
							else
								CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-3*PARAMWIDTH-TWOLINEGAP,YCoordinate,XCord-3*PARAMWIDTH-TWOLINEGAP,YCoordinate),*Mode_PresetString  ,false,Lang_Index);

						}
					}
				}
			}
		}
		delete []IDArray;
		if(YCoordinate==PRINTWELDSTARTYCORD)
			return(	PrintAlarms(0,pDC,YCoordinate+FOURWELDLINEGAP,view,false,false,CycleNumString));
		else if(DrawPresetString)
			return(	PrintAlarms(0,pDC,YCoordinate+TWOWELDLINEGAP,view,false,false,CycleNumString));
		else
			return(	PrintAlarms(0,pDC,YCoordinate+ONEWELDLINEGAP,view,false,false,CycleNumString));
	}
	else if(DrawPresetString)
	{	
		int XCord=PRINTWELDSTARTXCORD ;
		int YCoordinate = YCord; 
		DrawPresetString=false;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate,XCord,YCoordinate),*Mode_PresetString  ,false,Lang_Index);
		CString ParamValue =AllParamValues[0];
		CycleNumString =ParamValue;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCoordinate+ONEWELDLINEGAP),ParamValue  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;
		XCord+=40;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCoordinate+ONEWELDLINEGAP),*(Time_String)  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;

		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC ,YCoordinate+ONEWELDLINEGAP),*(Date_String)  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;
		for(int value =0;value<TotalDataHeading;value++)
		{	
			int IDValue=*(IDArray+value);
			for(int printvalue =0;printvalue<ParamCount;printvalue++)
			{
				if(*(AllParamIDs+printvalue)==IDValue)
				{	
					CString ParamValue =*(AllParamValues+printvalue);
					if(ParamValue.Find(_T("---"))>=0)
						ParamValue = NotApplicable;
					CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate+ONEWELDLINEGAP,XCord+XCORDINC ,YCoordinate+ONEWELDLINEGAP),ParamValue  ,true,Lang_Index);
					XCord+=PARAMWIDTH ;
					break;
				}
			}
		}
      delete []IDArray;
		return(	PrintAlarms(0,pDC,YCoordinate+ONEWELDLINEGAP,view,false,false,CycleNumString));
	}
	else
	{
		int XCord=PRINTWELDSTARTXCORD ;
		int YCoordinate = YCord; 
		CString ParamValue =AllParamValues[0];
		CycleNumString=ParamValue;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCoordinate,XCord+XCORDINC-ABSGAP ,YCoordinate),ParamValue  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;
		XCord+=40;
		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCoordinate,XCord+XCORDINC-ABSGAP ,YCoordinate),*(Time_String)  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;

		CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate,XCord+XCORDINC ,YCoordinate),*(Date_String)  ,true,Lang_Index);
		XCord+=PARAMWIDTH ;

		for(int value =0;value<TotalDataHeading;value++)
		{	
			int IDValue=*(IDArray+value);
			for(int printvalue =0;printvalue<ParamCount;printvalue++)
			{
				if(*(AllParamIDs+printvalue)==IDValue)
				{	
					CString ParamValue =*(AllParamValues+printvalue);
					if(ParamValue.Find(_T("---"))>=0)
						ParamValue = NotApplicable;
					CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord,YCoordinate,XCord+XCORDINC ,YCoordinate),ParamValue  ,true,Lang_Index);
					XCord+=PARAMWIDTH ;
					break;
				}
			}
		}
      delete []IDArray;
		return(	PrintAlarms(0,pDC,YCoordinate,view,false,false,CycleNumString));
	}
}

/******************************************************************/
/* This function is used to create Date and Time string using the */
/* information comming from 332.								  */
/******************************************************************/
void CWeldingData::StoreDate_Time(unsigned char *&data, int &length, CString* Date ,CString* Time)
{
	/*Storing Date.*/
	char TempArray[10];

	int Temp =*data++;length--;
	//	printf("\n date1=%d",Temp);
	CString TempDay =	_itoa(Temp,TempArray,10);
	if(TempDay.GetLength() ==1)
		TempDay = "0"+TempDay;
	if(CChildView::Language_Index <= Asian_Language_Start)
		TempDay +="/";

	Temp =*data++;length--;
	//	printf("\n date2=%d",Temp);
	CString TempMonth = 	_itoa(Temp,TempArray,10);
	if(TempMonth.GetLength() ==1)
		TempMonth = "0"+TempMonth;
	TempMonth +="/";

	Temp =*data++;length--;
	//	printf("\n date3=%d",Temp);
	CString TempYear = 	_itoa(Temp,TempArray,10);
	if(TempYear.GetLength() ==1)
		TempYear = "0"+TempYear;

	if(CChildView::Language_Index>Asian_Language_Start)
		*Date ="20"+TempYear+"/"+TempMonth+TempDay;
	else if(Units)
		*Date =TempDay+TempMonth+TempYear;
	else
		*Date =TempMonth+TempDay+TempYear;

	/* Storing Time.*/
	Temp =*data++;length--;
	//	printf("\n Time1=%d",Temp);
	CString TempHour = _itoa(Temp,TempArray,10);
	if(TempHour.GetLength() ==1)
		TempHour = "0"+TempHour;
	TempHour +=":";
	Temp =*data++;length--;
	//printf("\n Time2=%d",Temp);
	CString TempMinute = _itoa(Temp,TempArray,10);
	if(TempMinute.GetLength() ==1)
		TempMinute = "0"+TempMinute;
	TempMinute +=":";
	Temp =*data++;length--;
	CString TempSecond = _itoa(Temp,TempArray,10);
	if(TempSecond.GetLength() ==1)
		TempSecond = "0"+TempSecond;
	*Time =TempHour+TempMinute+TempSecond;
}

/*****************************************************************************/
/* this function is used to get weld data string form the data comming from	 */
/* welder. This is required because Weld data comes in syngle bye in all	 */
/* languages																 */
/*****************************************************************************/
CString CWeldingData::GetWeldDataString(unsigned char * &data,int & length)
{
	CString result = "";
	int count= *data++;
	int strlen;
	strlen=count;
	//printf("\n strlen=%d",strlen);
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
//	printf("\n result=%S",result);
	return result;
}

/****************************************************************/
/* This function is used to create the mode preset screen from	*/
/* mode numer and preset number									*/
/****************************************************************/
CString CWeldingData::GetMode_PresetString(unsigned char * &data,int & length)
{
	//printf("CWeldingData::GetMode_PresetString \n");
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

	//for(int i=0;i<FinalString.GetLength();i++)
	//	printf("%c",FinalString.GetAt(i));
	//printf("\n");

	FinalString.ReleaseBuffer();

	return FinalString;

}

/**************************************************************************/
/* This function is called to make History data objects when Power supply */
/* History data comes from 332											  */
/**************************************************************************/
CWeldingData::CWeldingData(int TotalColoumn, unsigned char * &data, int & length)
{
	TextColour = *data++;	//Storing text colour.
	//printf("\n TextColour in weldhistory=%d",TextColour);
	length--;
	Lang_Index=CChildView::Language_Index;
	Parameter_Value =new CString[TotalColoumn];
	Mode_PresetString=new CString[1];
	Time_String=new CString[1];
	Date_String=new CString[1];
	AllParamValues=new CString[1];
	AllParamIDs=new int[1];
	ColumnHeading=new CString[1];

	NoCycleAlarms=new int[1];
	OverloadAlarms=new int[1];
	EquipmentFailureAlarms=new int[1];
	CycleModifiedAlarms=new int[1];
	CalibrateAlarms=new int[1];
	Warnings=new int[1];
	RejectBitResult=new int[1];
	SuspectBitResult=new int[1];

	Units=CChildView::metric;	
	//Storing Weld Data of one cycle.
	for (int para_num=0;para_num< TotalColoumn; para_num++)
		Parameter_Value[para_num]=GetWeldDataString(data, length);	

	//Storing Mode Preset String for each cycle./
	*Mode_PresetString =GetMode_PresetString(data, length);

	//Storing Date and Time String for each cycle.
	StoreDate_Time(data,length,Date_String,Time_String);
	StoreAlarmInformation(data,length,0);

	PresetNumber  =CChildView::PresetNum;

}

/****************************************************************************/
/* This function draws the Weld History when Power supply history is drawn.	*/
/****************************************************************************/
void CWeldingData::DrawHistoryData(CDC *pDC,int LeftMostParameter, int LineNo)
{
	CRect ParamValueRect;

	int ColumnNo=0;
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
		(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
		(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
		(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));

	DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[0],false);
	ColumnNo++;

	for (int Index = LeftMostParameter; Index <(LeftMostParameter+4) ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Width),
			(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+3)),
			(HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Width),
			(HISTORY_TBL_START_Y+LINE_GAP*(LineNo+4)));

		DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[Index],false);
		ColumnNo++;

	}
}


CWeldingData::CWeldingData(int NoOfCycles, unsigned char * &data, int & length,bool SelectData)
{	
	Lang_Index=CChildView::Language_Index;
	TotalCyclesPrinted=0;
	HistoryContinued=false;
	int j =0;
	/*Type and Co_Ordinates for VGARunScreen Object	*/
	//	data+=9;		
	//	length-=9;

	TotalColoumn = *data++;
	length--;

	/* Storing Total Coloumn Ids.*/
	AllParamIDs =new int[TotalColoumn];
	for(j =0;j<TotalColoumn;j++)
	{
		AllParamIDs[j]=*data++;
		length--;
	}
	ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	Parameter_Value =new CString[1];
	TotalCycles=*data++;length--;
	ParamCount=TotalColoumn;
	AllParamValues =new CString[TotalColoumn+1];
	Mode_PresetString=new CString[1];
	Time_String=new CString[1];
	Date_String=new CString[1];
	Units=CChildView::metric;

	NoCycleAlarms=new int[1];
	OverloadAlarms=new int[1];
	EquipmentFailureAlarms=new int[1];
	CycleModifiedAlarms=new int[1];
	CalibrateAlarms=new int[1];
	Warnings=new int[1];
	RejectBitResult=new int[1];
	SuspectBitResult=new int[1];

	/*Storing data of all cycles.*/
	for(int i=0;i<NoOfCycles;i++)
	{
		TextColour = *data++;	//Storing text colour for each cycle.
		length--;
		int index=0;
		/*Storing Weld Data.*/
		for(j =0;j<TotalColoumn;j++)
		{
			AllParamValues[index] =GetWeldDataString(data, length);
			index++;
		}  

		/*Storing Mode Preset String for each cycle.*/
		*(Mode_PresetString) =GetMode_PresetString(data, length);

		/*Storing Date and Time String for each cycle.*/
		StoreDate_Time(data,length,Date_String,Time_String);
		StoreAlarmInformation(data,length,0);
	}

	PresetNumber  =CChildView::PresetNum;
	ColumnHeading = new CString[CChildView::TotalTextHeading];
	for(int TextHeadingNo=0;TextHeadingNo<CChildView::TotalTextHeading;TextHeadingNo++)
		ColumnHeading[TextHeadingNo]=CChildView::Parameter_Heading[TextHeadingNo];
}

void CWeldingData::StoreAlarmInformation(unsigned char * &data, int & length,int i)
{
	*(NoCycleAlarms+i)			=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(OverloadAlarms+i)			=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(EquipmentFailureAlarms+i)	=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(CycleModifiedAlarms+i)	=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(CalibrateAlarms+i)		=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(Warnings+i)				=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(RejectBitResult+i)		=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	*(SuspectBitResult+i)		=	CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
	int PSActControlFlags		=	*data++;
	//printf("\n PSActControlFlags in StoreAlarmInformation=%d",PSActControlFlags);
	length--;
}



int CWeldingData::PrintAlarms(int i,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString)
	/*---------------------------------------------------------*
	* There are alarm variables which code different errors.  *
	* The error messages are printed and the number of errors *
	* printed are returned                                    *
	*														   *
	* OUT: number of error messages printed                   *
	*---------------------------------------------------------*/
{
	//int count;
	int UIAlarms = 0;
	int temp =0;
	temp=GetAlarms(*(NoCycleAlarms+i), NCALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(OverloadAlarms+i), OLALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(EquipmentFailureAlarms+i), EQALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(CycleModifiedAlarms+i), CMALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(CalibrateAlarms+i), CAALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(Warnings+i), WAALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp= GetAlarms(*(RejectBitResult+i), PRALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	temp=GetAlarms(*(SuspectBitResult+i), PSALARM,pDC,YCord,view,HistoryAlarms,GraphAlarms,CycleNumString);
	YCord +=temp*ONEWELDLINEGAP;
	UIAlarms +=temp;
	return(UIAlarms);
}



int CWeldingData::GetAlarms(int  UIAlarmField, int IOffset,CDC *pDC,int YCord,CChildView *view,bool HistoryAlarms,bool GraphAlarms,CString CycleNumString)
	/*-------------------------------------------------------------------*
	* subroutine for printing error messages. the error variables is    *
	* checked bitwise and the appropriate error message is printed.     *
	* IN:    UIAlarmField, the error cell, bitwise coded                *
	*     IOffset, the index offset for the different kinds of messages *
	* OUT: number of alarms printed                                     *
	*-------------------------------------------------------------------*/
{  
	int  UIBit;
	int count;
	int UIAlarms = 0;


	static CString WarningNote,Alarms;

	if(HistoryTemp_pos!=NULL)
		WarningNote=tempHistoryList.GetNext(HistoryTemp_pos);
	else if(RunScreenTemp_pos!=NULL)
		WarningNote=tempRunScreenList.GetNext(RunScreenTemp_pos);
	else if(WeldTemp_pos!=NULL)
		WarningNote=tempWeldList.GetNext(WeldTemp_pos);
	else if(GraphsTemp_pos!=NULL)
		WarningNote=tempGraphsList.GetNext(GraphsTemp_pos);
	else if(ScreenGraphsTemp_pos!=NULL)
		WarningNote=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);



	//	WarningNote=CVgaMenuItem ::LinearSearch(WarningNote);
	if(HistoryTemp_pos!=NULL)
		Alarms=tempHistoryList.GetNext(HistoryTemp_pos);
	else if(RunScreenTemp_pos!=NULL)
		Alarms=tempRunScreenList.GetNext(RunScreenTemp_pos);
	else if(WeldTemp_pos!=NULL)
		Alarms=tempWeldList.GetNext(WeldTemp_pos);
	else if(GraphsTemp_pos!=NULL)
		Alarms=tempGraphsList.GetNext(GraphsTemp_pos);
	else if(ScreenGraphsTemp_pos!=NULL)
		Alarms=tempScreenGraphsList.GetNext(ScreenGraphsTemp_pos);


	//	Alarms=CVgaMenuItem ::LinearSearch(Alarms);
	if(GraphAlarms)
		CycleNumString =AllParamValues[0];

	if(UIAlarmField)
	{    
		/*--  There's an alarm--*/ 
		UIBit = 2;
		/*--  find Alarm and print messages --*/ 
		/*--  check bits 1 thru 27, bit 0 and last 4 bits of each word is reserved --*/ 

		for(count = 1; count <= 27; count++)
		{
			if(UIAlarmField & UIBit)
			{
				/*--  Alarm message --*/
				CString Alarm1=" ";
				if(IOffset == WAALARM)    
					Alarm1 = (WarningNote/*[Lang_Index] */);
				else
					Alarm1 = (Alarms);

				Alarm1 +=("   " + CChildView::thisPtr->AlarmEng[IOffset + count]);

				int XCord=PRINTWELDSTARTXCORD;
				if(GraphAlarms)
					XCord=PARAMETERSTARTXCORD;
				if(YCord>=MAXYCOORDINATE)
				{
					if(HistoryAlarms)
					{
						view->WeldHistoryAlarmStringList.AddTail(CycleNumString);
						view->WeldHistoryAlarmStringList.AddTail(Alarm1);
					}
					else if(GraphAlarms)
					{
						view->GraphAlarmStringList.AddTail(CycleNumString);
						view->GraphAlarmStringList.AddTail(Alarm1);
					}
					else
					{
						view->WeldAlarmStringList.AddTail(CycleNumString);
						view->WeldAlarmStringList.AddTail(Alarm1);
					}
				}
				else
				{
					if(GraphAlarms)
					{
						CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord-5,YCord+ONEWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCord+ONEWELDLINEGAP),CycleNumString  ,true,Lang_Index);
						XCord +=PARAMWIDTH;
						CVgaMenuItem::DrawPrinterText(pDC, PrintSmallFont, Black,CRect(XCord,YCord+ONEWELDLINEGAP,XCord+XCORDINC ,YCord+ONEWELDLINEGAP),Alarm1  ,false,Lang_Index);
					}
					else
					{
						CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-5,YCord+ONEWELDLINEGAP,XCord+XCORDINC-ABSGAP ,YCord+ONEWELDLINEGAP),CycleNumString  ,true,Lang_Index);
						XCord +=(PARAMWIDTH+40);
						CVgaMenuItem::DrawPrinterText(pDC, PrintWeldDataFont, Black,CRect(XCord-ABSGAP,YCord+ONEWELDLINEGAP,XCord-ABSGAP ,YCord+ONEWELDLINEGAP),Alarm1  ,false,Lang_Index);
					}
					YCord+=ONEWELDLINEGAP;
				}
				UIAlarms++;			  
			}
			UIBit <<= 1;
		}
	}
	return UIAlarms;
}


