/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/USBFolder.cpp_v   1.22   16 Apr 2015 06:01:12   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/USBFolder.cpp_v  $
 * 
 *    Rev 1.22   16 Apr 2015 06:01:12   sesharma
 * Fix for date button click showing blank screen on second page of power supply folder.
 * 
 *    Rev 1.21   14 Mar 2015 11:50:58   amaurya
 * PrepareListFromLog() function return type changed
 * 
 *    Rev 1.20   02 Jan 2015 06:34:22   rjamloki
 * numbers replaced by macros
 * 
 *    Rev 1.19   28 Nov 2014 08:32:18   rjamloki
 *  Changes to delete hidden files for Event and WeldData files.
 * 
 *    Rev 1.18   14 Nov 2014 02:54:04   rjamloki
 * CUSBFolder::MouseClick() changed to resolve Usb Recall issue.
 * 
 *    Rev 1.17   20 Oct 2014 05:48:38   RJamloki
 *  Macro  (MAX_ALLOWED_WELD_LOG replaced by variable to support Control level D related changes
 * 
 *    Rev 1.16   25 Sep 2014 12:00:28   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.15   26 Aug 2014 07:47:22   rjamloki
 * Modified column width for weldhistory pdf
 * 
 *    Rev 1.14   28 Jul 2014 14:17:40   rjamloki
 * review comments,memory leak taken care
 * 
 *    Rev 1.13   22 Jul 2014 08:24:14   akaushal
 * GetStartingEventCount() function changed for VGA file path.
 * 
 *    Rev 1.12   09 Jul 2014 07:08:34   akaushal
 * CUSBFolder::MouseClick() function modified to check change conditions.PrepareUSBHistoryList(),
 * GetStartingEventCount(),PrepareListFromLog() changed.
 * 
 *    Rev 1.11   09 Jun 2014 11:55:26   rjamloki
 * Parameter column width changed
 * 
 *    Rev 1.10   27 May 2014 06:32:44   amaurya
 * Added Column width for Weld History PDF
 * 
 *    Rev 1.9   20 May 2014 11:07:22   rjamloki
 * New function added for deletion.
 * 
 *    Rev 1.8   07 May 2014 13:10:52   akaushal
 * deletion functions for  Event History and Weld Data
 * 
 *    Rev 1.7   23 Apr 2014 11:26:12   akaushal
 * Added the functionality to read from  WeldHistory.log file
 * 
 *    Rev 1.6   21 Apr 2014 13:44:34   akaushal
 * Function added to create event log list from file 
 * 
 *    Rev 1.5   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:36 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:05:28 rjamloki   
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:34 rjamloki   
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:40 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "USBFolder.h"
#include "VgaTitle.h"
#include "VgaBottomMenu.h"
#include "WeldingHistory.h"
#include "HistoryGraphs.h"
#include "VGA.h"
#include "EventLog.h"
#include "VGAButton.h"
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

#ifndef _WIN32_WCE
#define ZLIB_WINAPI
#endif


extern jmp_buf env;
#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
	error_handler (HPDF_STATUS   error_no,
	HPDF_STATUS   detail_no,
	void         *user_data);
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
void DeleteEventHistory(int Address);
void DeleteWeldHistory(int Address);
extern int TotalDataInFile;
extern CString HistoryDataFileName;
extern bool WeldDataLogFile;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUSBFolder * CUSBFolder::thisPointer;

CUSBFolder::CUSBFolder(CString FileName,CString FilePath,int EnumID,int Function_Id)
{
	Name=FileName;
	Path=FilePath;
	text=FileName;
	LastFolderPath=Path;
	TitleID=EnumID;
	Fun_Id=Function_Id;
	thisPointer = this;
}
CString CUSBFolder::ThirdHierTitle;
CString CUSBFolder::SecondHierTitle;
CString CUSBFolder::PreviousFileName;
CString CUSBFolder::LastFilePath;
CString CUSBFolder::LastFolderPath;
CString CUSBFolder::HistoryGraphPath;

CUSBFolder::~CUSBFolder()
{

}

/*****************************************************************************/
/*                                                                           */  
/*  This function Draws a USB Folder type object When any USB Folder type    */
/*  object is found in menu/submenu item list for current page.              */
/*****************************************************************************/
void CUSBFolder::Draw(CDC *pDC)
{
	int ButtonColour=CChildView::Button_Color;
	DrawRect(pDC, ButtonColour, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, DisplayName,true);
}

/*************************************************************************************/
/*                                                                                   */
/* This function is called when any USB Folder type object is clicked by the user    */
/* The function checks the hierarchy level of the folder and prepares new menu		 */
/* accordingly The menu items   are stored and displayed as new menu                 */
/*************************************************************************************/
bool CUSBFolder::MouseClick(const CPoint &p, CChildView *view)
{
	UINT32 HisMask = 0;
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}
	if(!CChildView::ISUSBPresent)
	{
		CVgaMenu * menu;
		if (theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, menu))
		{
			theApp.menuName=CVgaBottomMenu::mainMenuID;
			theApp.MenuPointer=menu;
			CChildView::thisPtr->ModifyObjectList(menu); 
		}
		view->Invalidate();
		return true;
	}

	CString TempStr=DisplayName;

	if(Fun_Id==FOLDERHIERARCHYTWO)
		ThirdHierTitle=TempStr;
	if(Fun_Id<FOLDERHIERARCHYTHREE)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		CString argv=Path;
		CString DirSpec;  
		DirSpec=argv+_T("\\*");
		hFind = FindFirstFile(DirSpec, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
		{
			return true;
		} 
		else 
		{
			if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,Fun_Id+1)))
			{
				FindClose(hFind);
				if(Fun_Id==FOLDERHIERARCHYTWO)
					PreviousFileName=DisplayName.SpanExcluding(_T("-"));
				if(Fun_Id==FOLDERHIERARCHYONE)
					SecondHierTitle=TempStr;

				view->menupointers.AddTail(theApp.MenuPointer);
				view->menusname.AddTail(theApp.menuName);
				view->menus.AddTail(1);
				view->PrepareUSBList(Path,Fun_Id+1,TitleID);
				view->Invalidate();
				return true;
			}
			while (FindNextFile(hFind, &FindFileData) != 0) 
			{
				if((FindFileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY )&&(view->ValidFolderName(FindFileData.cFileName,Fun_Id+1)))
				{
					FindClose(hFind);
					if(Fun_Id==FOLDERHIERARCHYTWO)
						PreviousFileName=DisplayName.SpanExcluding(_T("-"));
					if(Fun_Id==FOLDERHIERARCHYONE)
						SecondHierTitle=TempStr;

					view->menupointers.AddTail(theApp.MenuPointer);
					view->menusname.AddTail(theApp.menuName);
					view->menus.AddTail(1);
					view->PrepareUSBList(Path,Fun_Id+1,TitleID);

					view->Invalidate();
					return true;
				}
			}
		}
	}
	else if(Fun_Id == USBPRESETFOLDER)
	{
		CChildView::LastUSBPresetFolder = Path +"\\Presets";
		theApp.menuName=view->menusname.RemoveTail();
		page_no=view->menus.RemoveTail();
		theApp.MenuPointer=view->menupointers.RemoveTail();
		view->ModifyObjectList(theApp.MenuPointer); 
		view->Invalidate();
	}
	else
	{
		CWeldingHistory::LeftMostParameter = 1;
		HisParameterCounts = 0;
		if(CChildView::ControlLevel >= LEVEL_C)	
			HisMask = HistorySetUp | MANDATORY_PARAM_MASK_LEVELC;   
		else
			HisMask = HistorySetUp | MANDATORY_PARAM_MASK_BELOWLEVELC;   
		for(int i = 0; i < MAX_VIEW_HISTORYPARAM; i++)
		{
			if((HisMask & (1 << i)) == (1 << i))
			{
				HisParameterMap[HisParameterCounts] = CChildView::thisPtr->Parameter_ID[i];
				HisParameterCounts++;
			}
		}
		
		CVgaMenu *menu;
		if (theApp.menus.Lookup(CChildView::thisPtr->USBGraphMenu, menu))
		{
			view->menupointers.AddTail(theApp.MenuPointer);
			view->menusname.AddTail(theApp.menuName);
			view->menus.AddTail(page_no);//fix for date button click showing blank screen on second
										 //page of power supply folder			
			theApp.menuName = CChildView::thisPtr->USBGraphMenu;
			theApp.MenuPointer = menu;
		}
		/* here show history screen*/
		CChildView::thisPtr->EnableUSBGraph=true;
		PrepareUSBHistoryList(Path,view,7,7);

	}
	return true;
}

extern int CurrentCountToReadWeld;

/********************************************************************************************/
/* This function is used to prepare history list. the function checks for the file			*/
/*	WeldData.log in the path passed as argument. If file is found then it reads the file	*/
/*	and prepares the list																	*/
/********************************************************************************************/
bool CUSBFolder::PrepareUSBHistoryList(CString Path,CChildView *view, int StartingPoint, int Count)
{
	static CString PathVar = "";
	WeldDataLogFile = true;
	while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount()>0)
	{
		CHistoryData *obj1 = CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();//delete
		free(obj1);
	}
	while(CWeldingHistory::thisHisPtr->WeldHistoryList.GetCount()>0)
		delete CWeldingHistory::thisHisPtr->WeldHistoryList.RemoveHead();
	if(view != NULL)
		PathVar = Path;
	Path = PathVar;
	CVgaMenu *menu=theApp.MenuPointer;
	LastFilePath=Path;
	HistoryGraphPath=Path;
	int x=0;
	while(x!=1)
	{
		if(LastFilePath.Right(1)==("\\"))
			x++;
		LastFilePath.Delete(LastFilePath.GetLength()-1,1);
	}
	CHistoryGraphs::HistoryDataPath=Path;
	Path=Path+"\\WeldData.log";
	CFile f;
	CFileException e;

	if( !f.Open( Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE(_T("\n !! GENERIC"));
		else if(e.m_cause==CFileException::badPath   )
			TRACE(_T("\n !! bad path"));
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE(_T("\n !! too many files open"));
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE(_T("\n !! file not found"));
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE(_T("\n !! access denied"));
		else if(e.m_cause==CFileException::diskFull      )
			TRACE(_T("\n !! disc full"));
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE(_T("\n !! invalid file"));
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
	}
	else
	{	
		if(f.GetLength()==0)
		{
			POSITION pos = menu->items.GetHeadPosition();
			CVgaMenuItem *object= 0;
			int count=0;
			while (pos)
			{
				object= menu->items.GetNext(pos);
				if((object->GetType()==CVgaMenu::VGAMsgScrnObject))
				{
					count++;
					if(count==2)
					{
						CMsgScreen *ptr=(CMsgScreen *)object;
						view->ShowMessageScreen(object->text);
						break;
					}
				}
			}
			f.Close();
			theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
			page_no=CChildView::thisPtr->menus.RemoveTail();
			theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
			CChildView::thisPtr->PrepareUSBList(CUSBFolder::LastFilePath,FOLDERHIERARCHYTHREE,TitleID);
			CChildView::thisPtr->Invalidate();
			return false;
		}
		unsigned int NoOfBytesRead=0;
		if((StartingPoint <= 0) || (Count == 0))
			return false;
		if(StartingPoint <= Count)
			Count = StartingPoint;

		StartingPoint = StartingPoint - Count;
		unsigned long UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
		unsigned long WeldHeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
		unsigned long TotalValidHeaderSize = WeldHeaderSize + sizeof(char) + 2*UnitObjectSize;
		unsigned long ObjectSize = sizeof(int) + sizeof(bool) + 3*sizeof(char)+ sizeof(CHistoryData);
		CHistoryData* object = NULL; 

		int  size= sizeof(CHistoryData);
		bool FirstObject = true;

		bool USBMetric;
		if(NoOfBytesRead!=f.GetLength())
		{	
			int ID;
			UINT32 TotalObjectCount,/*TotalHeaderCount*/WriteObjectIndex;
			char Comma,NextComma;	
			if(FirstObject)
			{
				f.SeekToBegin();
				FirstObject = false;
				NoOfBytesRead+=f.Read(&TotalObjectCount,sizeof(UINT32));
				NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
				NoOfBytesRead+=f.Read(&WriteObjectIndex,sizeof(UINT32));
				NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
				NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);
				NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);
				NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
				if(view != NULL)
				{
					if((int)TotalObjectCount <= Count)
						Count = TotalObjectCount;
					StartingPoint = TotalObjectCount - Count;
					CurrentCountToReadWeld = TotalObjectCount;
					TotalDataInFile = TotalObjectCount;
				}
				//Go to the endof file
			}
			f.Seek((StartingPoint)*ObjectSize + TotalValidHeaderSize,CFile::begin);
			while((Count--) && (NoOfBytesRead!=f.GetLength()))
			{
				object =new CHistoryData();
				NoOfBytesRead+=f.Read(&ID,sizeof(int));
				NoOfBytesRead+=f.Read(&Comma,sizeof(char));
				NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

				NoOfBytesRead+=f.Read(&Comma,sizeof(char));
				NoOfBytesRead+=f.Read(object,size);
				NoOfBytesRead+=f.Read(&Comma,sizeof(char));
				object->Units=USBMetric;
				object->UniqueId=ID;

				CWeldingHistory::thisHisPtr->USBWeldHistoryList.AddHead(object);
				CWeldingHistory::thisHisPtr->TotalCycle++;
				//OldUnits=USBMetric;
			}
		}
		if(object != NULL)
		{
			CWeldingHistory::thisHisPtr->TotalColoumn=object->TotalColoumn;
			CWeldingHistory::thisHisPtr->Parameter_ID=new int[object->TotalColoumn];
			for(int param=0;param<object->TotalColoumn;param++)	//Storing parameters ID.
				CWeldingHistory::thisHisPtr->Parameter_ID[param]=object->USBParamIDs[param];
		}
		f.Close();

		if(view != NULL) {
			page_no=1;
			view->ModifyObjectList(theApp.MenuPointer); 
			view->Invalidate();
		}
	}
	return (true);
}


int GetStartingEventCount()
{
	UINT32 RetVal = 0;
	CFile pFile;
	UINT32 TotalObjectCount = 0,ReadObjectIndex = 0;
	char Comma = 0;
	unsigned long HeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
	unsigned long ObjectSize = sizeof(CEventHistoryData) + sizeof(char); // <EventRecord{n},>

	CString Path = DISK;
	CString PathHidden = DISK;
	Path = Path + "EventLog.log";
	PathHidden = PathHidden + "EventHiddenFile.log";
		
	if(pFile.Open(Path,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))
	{
		unsigned long size = (unsigned long)pFile.GetLength();
		pFile.SeekToBegin();
		if(size < HeaderSize)
		{
			pFile.Write(&TotalObjectCount,sizeof(UINT32));
			pFile.Write(&Comma,sizeof(char));
			pFile.Write(&ReadObjectIndex,sizeof(UINT32));
			pFile.Write(&Comma,sizeof(char));

			CEventLog::EventHistoryglobalCount = 0;
			CEventLog::SuccessfullyWrittenEventRecord = 0; // 0 in case file does not exist
			CEventLog::CurrentDisplayEventCount = 0;
		}
		else //if(size >= HeaderSize)
		{
			pFile.Read(&TotalObjectCount,sizeof(UINT32));
			pFile.Read(&Comma,sizeof(char));
			pFile.Read(&ReadObjectIndex,sizeof(UINT32));
			pFile.Read(&Comma,sizeof(char));
			CEventLog::EventHistoryglobalCount = TotalObjectCount;
			CEventLog::SuccessfullyWrittenEventRecord = TotalObjectCount; // if data in file then 
			CEventLog::CurrentDisplayEventCount = ReadObjectIndex;
		}

		pFile.Close();
		RetVal = TotalObjectCount;
	}
	else
	{
		printf("File Cannot be created\n");
	}

	if(pFile.Open(PathHidden,CFile::modeRead))//if file exists then take the count from file
	{
		UINT32 Temp;
		pFile.SeekToBegin();
		pFile.Read(&Temp,sizeof(UINT32));
		CEventLog::EventHistoryUniversalCount = CEventLog::EventHistoryRamCount = Temp;
		pFile.Close();
	}
	else if(pFile.Open(PathHidden,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))//create and hide the file
	{  
		pFile.SeekToBegin();
		CEventLog::EventHistoryUniversalCount = CEventLog::EventHistoryRamCount = TotalObjectCount;
		pFile.Write(&TotalObjectCount,sizeof(UINT32));
		pFile.Close();
		SetFileAttributes(PathHidden,FILE_ATTRIBUTE_HIDDEN);
	}

	return (RetVal);
}

int GetStartingWeldCount(void)
{
	//Column width for the PDF's
	
	CString PathHidden = DISK;
	UINT32 TotalObjectCount = 0;
	PathHidden = PathHidden + "WeldDataHidden.log";
    CChildView::thisPtr->PDFParamWidth[0] =45;
	CChildView::thisPtr->PDFParamWidth[1] =45;
	CChildView::thisPtr->PDFParamWidth[2] =96;
	CChildView::thisPtr->PDFParamWidth[3] =35;
	CChildView::thisPtr->PDFParamWidth[4] =35;
	CChildView::thisPtr->PDFParamWidth[5] =35;
	CChildView::thisPtr->PDFParamWidth[6] =54;
	CChildView::thisPtr->PDFParamWidth[7] =54;
	CChildView::thisPtr->PDFParamWidth[8] =54;
	CChildView::thisPtr->PDFParamWidth[9] =40;
	CChildView::thisPtr->PDFParamWidth[10] =40;
	CChildView::thisPtr->PDFParamWidth[11] =40;
	CChildView::thisPtr->PDFParamWidth[12] =40;
	CChildView::thisPtr->PDFParamWidth[13] =40;
	CChildView::thisPtr->PDFParamWidth[14] =37;
	CChildView::thisPtr->PDFParamWidth[15] =37;
	CChildView::thisPtr->PDFParamWidth[16] =37;
	CChildView::thisPtr->PDFParamWidth[17] =35;
	CChildView::thisPtr->PDFParamWidth[18] =35; 
	CChildView::thisPtr->PDFParamWidth[19] =35;
	CChildView::thisPtr->PDFParamWidth[20] =35;
	CChildView::thisPtr->PDFParamWidth[21] =35;  
	CChildView::thisPtr->PDFParamWidth[22] =32;
	CChildView::thisPtr->PDFParamWidth[23] =32;
	CChildView::thisPtr->PDFParamWidth[24] =32;
	CChildView::thisPtr->PDFParamWidth[25] =32;
	CChildView::thisPtr->PDFParamWidth[26] =32;
	CChildView::thisPtr->PDFParamWidth[27] =32;
	CChildView::thisPtr->PDFParamWidth[28] =32;
	CChildView::thisPtr->PDFParamWidth[29] =32;
	CChildView::thisPtr->PDFParamWidth[30] =32;

	unsigned long RetVal = 0;
	unsigned long ValidDataCount = 0;
	unsigned long InValidDataBytes = 0;
	unsigned long HeaderObjectSize = 2*(sizeof(char) + sizeof(UINT32));
	unsigned long UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
	unsigned long StartOffset = HeaderObjectSize + 2*UnitObjectSize + sizeof(char);
	unsigned long ObjectSize  = sizeof(int)+sizeof(char)+sizeof(bool)+sizeof(char)+sizeof(CHistoryData)+sizeof(char);
	CFile f;
	if (f.Open(HistoryDataFileName,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))
	{
		unsigned long size = (unsigned long)f.GetLength();
		if(size == 0)
		{
			UINT32 ReadObjectIndex = 0,ByteCount = 0;
			unsigned char *  TempBuf = new unsigned char[HeaderObjectSize+2*UnitObjectSize+1];
			unsigned char * BufPtr = TempBuf; 
			char NextComma = ',';	

			CString UnitUSCS,UnitMetrics;
			int i;

			for(int k=0;k<CChildView::TotalTextHeading;k++)
			{
				UnitMetrics =CChildView::Parameter_Units_Metric[k];
				UnitUSCS =CChildView::Parameter_Units_USCS[k];

				for( i=0;i<UnitMetrics.GetLength();i++)
				{

					CWeldingHistory::ParameterUnitMetric[k][i] = UnitMetrics.GetAt(i);
					CWeldingHistory::ParameterUnitMetric[k][i+1]='\0';
				}

				for( i=0;i<UnitUSCS.GetLength();i++)
				{

					CWeldingHistory::ParameterUnitUSCS[k][i] = UnitUSCS.GetAt(i);
					CWeldingHistory::ParameterUnitUSCS[k][i+1]='\0';
				}
			}

			memcpy(BufPtr,&TotalObjectCount,sizeof(UINT32));	//4+0 = 4
			ByteCount+=sizeof(UINT32);
			BufPtr+=sizeof(UINT32);
			memcpy(BufPtr,&NextComma,sizeof(char));				//4+1 = 5
			ByteCount+=sizeof(char);
			BufPtr+=sizeof(char);								
			memcpy(BufPtr,&/*TotalHeaderCount*/ReadObjectIndex,sizeof(UINT32));	//5+4 = 9
			ByteCount+=sizeof(UINT32);
			BufPtr+=sizeof(UINT32);
			memcpy(BufPtr,&NextComma,sizeof(char));				//9+1 = 10
			ByteCount+=sizeof(char);
			BufPtr+=sizeof(char);
			memcpy(BufPtr,&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);	//350+10 = 360
			BufPtr+=UnitObjectSize;
			ByteCount+=UnitObjectSize;
			memcpy(BufPtr,&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);	//360+350 = 710
			BufPtr+=UnitObjectSize;
			ByteCount+=UnitObjectSize;
			memcpy(BufPtr,&NextComma,sizeof(char));										//710+1 = 711
			ByteCount+=sizeof(char);													//HeaderSize
			BufPtr+=sizeof(char);

			f.Write(TempBuf,ByteCount);
			CWeldingHistory::thisHisPtr->TotalDataInFile = 0;
			CWeldingHistory::CurrentDisplayWeldCount = 0;
			f.Close();
			delete[] TempBuf;
		}
		else
		{
			f.SeekToBegin();
			int NoOfBytesRead = 0;
			if(NoOfBytesRead!=f.GetLength())
			{	
				UINT32 TotalObjectCount,/*TotalHeaderCount*/ReadObjectIndex,TotalSizeOfValidObjects;
				char NextComma;	
				NoOfBytesRead+=f.Read(&TotalObjectCount,sizeof(UINT32));
				NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
				NoOfBytesRead+=f.Read(/*TotalHeaderCount*/&ReadObjectIndex,sizeof(UINT32));
				NoOfBytesRead+=f.Read(&NextComma,sizeof(char));

				TotalSizeOfValidObjects = HeaderObjectSize + /*TotalHeaderCount*/ReadObjectIndex * UnitObjectSize + sizeof(char) + TotalObjectCount * ObjectSize;
				ValidDataCount = TotalObjectCount;
				if(size>TotalSizeOfValidObjects)
					InValidDataBytes = size - TotalSizeOfValidObjects;

				CWeldingHistory::thisHisPtr->TotalDataInFile = ValidDataCount;
				CWeldingHistory::CurrentDisplayWeldCount = ReadObjectIndex;

				if(InValidDataBytes)
				{
					printf("Invalid Weld History File: Correct it by %d",InValidDataBytes);
				}
				printf("Everything is fine WeldHistory Count is %d\n",ValidDataCount);
				f.Close();
				RetVal = ValidDataCount;
			}
		}
	}
	else
	{
		printf("File Cannot be created\n");
		RetVal = 0;
	}

	if(f.Open(PathHidden,CFile::modeRead))//if file exists then take the count from file
	{
		UINT32 Temp;
		f.SeekToBegin();
		f.Read(&Temp,sizeof(UINT32));
		CChildView::thisPtr->UniversalCount = CChildView::thisPtr->UniversalCountWeldHiddenFile = Temp;
		f.Close();
	}
	else if(f.Open(PathHidden,CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite))//create and hide the file
	{  
		f.SeekToBegin();
		CChildView::thisPtr->UniversalCount = CChildView::thisPtr->UniversalCountWeldHiddenFile = TotalObjectCount;
		f.Write(&TotalObjectCount,sizeof(UINT32));
		f.Close();
		SetFileAttributes(PathHidden,FILE_ATTRIBUTE_HIDDEN);
	}

	return (RetVal);

}

/********************************************************************************************/
/* This function is used to prepare history list. the function checks for the file			*/
/*	EventLog.log in the path passed as argument. If file is found then it reads the file	*/
/*	and prepares the list. At-most 100 data can be read at a time.							*/
/********************************************************************************************/
void PrepareListFromLog(CString Path,int Count,int StartingPoint, bool Event_Or_Weld, bool Head_Or_Tail,bool ListPdf)
{
	int ObjectSize;
	int  size = 0;
	unsigned long HeaderSize;
	CFile f;
	CFileException e;
	unsigned int NoOfBytesRead=0;
	if((StartingPoint <= 0) || (Count == 0))
		return;
	if(StartingPoint <= Count)
		Count = StartingPoint;


	if(Event_Or_Weld)
	{
		HeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
		size= sizeof(CEventHistoryData);
		ObjectSize = size + sizeof(char);
		if(Count == (-1)) //read from End
			StartingPoint = CEventLog::SuccessfullyWrittenEventRecord;
	}	

	else
	{
		Path=HistoryDataFileName;
		ObjectSize = size= sizeof(int) + sizeof(bool) + 3*sizeof(char)+ sizeof(CHistoryData);
		if(Count == (-1)) //read from End
			StartingPoint = 0;
	}	


	if( !f.Open( Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
	{
#ifdef _DEBUG
		if(e.m_cause==CFileException::generic)
			TRACE(_T("\n !! GENERIC"));
		else if(e.m_cause==CFileException::badPath   )
			TRACE(_T("\n !! bad path"));
		else if(e.m_cause==CFileException::tooManyOpenFiles    )
			TRACE(_T("\n !! too many files open"));
		else if(e.m_cause==CFileException::fileNotFound )
			TRACE(_T("\n !! file not found"));
		else if(e.m_cause==CFileException::accessDenied       )
			TRACE(_T("\n !! access denied"));
		else if(e.m_cause==CFileException::diskFull      )
			TRACE(_T("\n !! disc full"));
		else if(e.m_cause==CFileException::invalidFile   )
			TRACE(_T("\n !! invalid file"));
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
	}
	else
	{	
		if(f.GetLength()==0)
		{
			f.Close();
			return;
		}
		//StartingPoint = StartingPoint - Count; //Find the location from where to read

		if(Event_Or_Weld)
		{
			char Comma;	
			CEventHistoryData* object; 
			if(Head_Or_Tail)
			{
				StartingPoint = StartingPoint - Count;
				f.Seek(StartingPoint*ObjectSize + HeaderSize,CFile::begin);
				while((NoOfBytesRead!=f.GetLength()) && (Count--))
				{
					object =new CEventHistoryData();
					NoOfBytesRead+=f.Read(object,size);
					NoOfBytesRead+=f.Read(&Comma,sizeof(char));
					object->Parameter_Value = NULL;
					object->SetParameters();
					CEventLog::thisHisPtr->EventLogList.AddHead(object);
				}
			}
			else
			{
				for(int i = 1;i<=Count;i++)
				{
					f.Seek((MAX_ALLOWED_EVENT_LOG -i) *ObjectSize + HeaderSize,CFile::begin);
					object =new CEventHistoryData();
					NoOfBytesRead+=f.Read(object,size);
					NoOfBytesRead+=f.Read(&Comma,sizeof(char));
					object->Parameter_Value = NULL;
					object->SetParameters();
					CEventLog::thisHisPtr->EventLogList.AddTail(object);
				}
			}
		}
		else
		{
			StartingPoint = StartingPoint - Count; 
			if(ListPdf)
				Head_Or_Tail =true;
			while(CWeldingHistory::thisHisPtr->LOGWeldHistoryList.GetCount())
				delete CWeldingHistory::thisHisPtr->LOGWeldHistoryList.RemoveHead();

			//while(CWeldingHistory::thisHisPtr->USBWeldHistoryList.GetCount())
			//delete CWeldingHistory::thisHisPtr->USBWeldHistoryList.RemoveHead();

			CWeldingHistory::thisHisPtr->TotalCycle = 0;
			f.SeekToBegin();
			unsigned long UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
			unsigned long WeldHeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
			unsigned long TotalValidHeaderSize = WeldHeaderSize + 2*UnitObjectSize + sizeof(char) ;
			CHistoryData* object = NULL; 

			int  size= sizeof(CHistoryData);
			bool FirstObject = true;
			bool USBMetric;
			if(NoOfBytesRead!=f.GetLength())
			{	
				int ID;
				UINT32 TotalObjectCount,/*TotalHeaderCount*/WriteObjectIndex;
				char Comma,NextComma;	
				if(FirstObject)
				{
					FirstObject = false;
					NoOfBytesRead+=f.Read(&TotalObjectCount,sizeof(UINT32));
					NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
					NoOfBytesRead+=f.Read(&WriteObjectIndex,sizeof(UINT32));
					NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);
					NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);
					NoOfBytesRead+=f.Read(&NextComma,sizeof(char));

					f.Seek((StartingPoint)*ObjectSize + TotalValidHeaderSize,CFile::begin);
					//Go to the endof file
				}
				if(Head_Or_Tail)
				{
					f.Seek((StartingPoint)*ObjectSize + TotalValidHeaderSize,CFile::begin);
					while((Count--) && (NoOfBytesRead!=f.GetLength()))
					{
						object =new CHistoryData();
						NoOfBytesRead+=f.Read(&ID,sizeof(int));
						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						NoOfBytesRead+=f.Read(object,size);
						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						object->Units=USBMetric;
						object->UniqueId=ID;
						if(ListPdf)
							CWeldingHistory::thisHisPtr->LOGWeldHistoryList.AddHead(object);
						else
							CWeldingHistory::thisHisPtr->USBWeldHistoryList.AddHead(object);
						CWeldingHistory::thisHisPtr->TotalCycle++;
						//OldUnits=USBMetric;
					}
				}
				else
				{
					for(int i = 1;i<=Count;i++)
					{
						f.Seek((CChildView::Max_Allowed_Weld_Log -i) *(LONGLONG)ObjectSize + TotalValidHeaderSize,CFile::begin);
						object =new CHistoryData();

						NoOfBytesRead+=f.Read(&ID,sizeof(int));
						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						NoOfBytesRead+=f.Read(object,size);
						NoOfBytesRead+=f.Read(&Comma,sizeof(char));
						object->Units=USBMetric;
						object->UniqueId=ID;
						CWeldingHistory::thisHisPtr->USBWeldHistoryList.AddTail(object);
						CWeldingHistory::thisHisPtr->TotalCycle++;
					}

				}

			}
			if(object != NULL)
			{
				CWeldingHistory::thisHisPtr->TotalColoumn=object->TotalColoumn;

				if(CWeldingHistory::thisHisPtr->Parameter_ID != NULL) {
				   delete [] CWeldingHistory::thisHisPtr->Parameter_ID;
				   CWeldingHistory::thisHisPtr->Parameter_ID = NULL;
				}
				CWeldingHistory::thisHisPtr->Parameter_ID=new int[object->TotalColoumn];
				for(int param=0;param<object->TotalColoumn;param++)	//Storing parameters ID.
					CWeldingHistory::thisHisPtr->Parameter_ID[param]=object->USBParamIDs[param];
			}
		}
		f.Close();
	}
}

/********************************************************************************************/	
/*  This function checks the hierarchy level of the USB Folder and creates the string to be	*/
/* displayed. If Hierarchy level is one, it displays the name as it is.					    */
/* If Level is two it checks for the month in the string and will add appropriate string	*/
/* to get display name.																		*/
/* If hierarchy level is three it then combines the day string with its month string to		*/
/* get the display name																		*/
/*********************************************************************************************/
CString CUSBFolder::GetDiaplayName(int HierarchyLevel)
{
	switch(HierarchyLevel)
	{
	case FOLDERHIERARCHYONE:
		{
			DisplayName=Name;
			break;
		}

	case FOLDERHIERARCHYTWO:
		{
			char Month[3];
			Month[0]= (char)Name.GetAt(5);
			Month[1]=(char)Name.GetAt(6);
			Month[2]='\0';	
			int MONTH = atoi(&Month[0]);
			CString Year = Name.Left(4);
			if(CChildView::Language_Index>Asian_Language_Start)
				Year =Year+" "+CChildView::thisPtr->AllMonthStrings[0]/*Year_String[CChildView::Language_Index]*/;
			switch(MONTH)
			{
			case JAN:
				DisplayName=CChildView::thisPtr->AllMonthStrings[JAN] /*Str_Jan[CChildView::Language_Index] */+ "-"+Year+">";
				break;

			case FEB:
				DisplayName= CChildView::thisPtr->AllMonthStrings[FEB]/*Str_Feb[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case MAR:
				DisplayName= CChildView::thisPtr->AllMonthStrings[MAR] /*Str_March[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case APR:
				DisplayName= CChildView::thisPtr->AllMonthStrings[APR]/*Str_April[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case MAY:
				DisplayName= CChildView::thisPtr->AllMonthStrings[MAY]/*Str_May[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case JUN:
				DisplayName= CChildView::thisPtr->AllMonthStrings[JUN]/*Str_June[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case JUL:
				DisplayName= CChildView::thisPtr->AllMonthStrings[JUL]/*Str_July[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case AUG:
				DisplayName= CChildView::thisPtr->AllMonthStrings[AUG]/*Str_Aug[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case SEP:
				DisplayName= CChildView::thisPtr->AllMonthStrings[SEP]/*Str_Sept[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case OCT:
				DisplayName= CChildView::thisPtr->AllMonthStrings[OCT]/*Str_Oct[CChildView::Language_Index] */+ "-"+Year+">";
				break;

			case NOV:
				DisplayName= CChildView::thisPtr->AllMonthStrings[NOV]/*Str_Nov[CChildView::Language_Index]*/ + "-"+Year+">";
				break;

			case DEC:
				DisplayName= CChildView::thisPtr->AllMonthStrings[DEC]/*Str_Dec[CChildView::Language_Index]*/ + "-"+Year+">";

				break;
			}
			break;
		}

	case FOLDERHIERARCHYTHREE:
		{
			if(CChildView::Language_Index>Asian_Language_Start)
				DisplayName= PreviousFileName + " " + Name+ " "+ CChildView::thisPtr->AllMonthStrings[DEC+1]/*Day_String[CChildView::Language_Index]*/;
			else
				DisplayName= PreviousFileName + " " + Name;
			break;
		}

	default:
		{
			DisplayName=Name;
			return DisplayName;
			break;
		}
	}return DisplayName;
}


/****************************************************************************************/
/* This function is used to make new files if the files are not created or if Weld		*/
/* data file is found corrupted															*/
/****************************************************************************************/
void CUSBFolder::ClearAllFiles()
{
	CFile f;
	CFileException e;

	CString Path = HistoryGraphPath+"\\";
	CString FileName="PowerGraph.log";
	CString GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="ColDistGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="VelocityGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="ForceGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="AmpGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);

	FileName="FreqGraph.log";
	GraphPath=	Path+FileName;
	f.Remove(GraphPath);
}

void DeleteEventHistory(int Address)
{
	CFile pFile;
	CString Path = EventDataFileName;
	int length = 0;
	unsigned char * data;
	char ch = 0;
	data = (unsigned char*)&ch;
	pFile.Remove(Path);
	Path  = DISK ;
	Path = Path +  "EventHiddenFile.log";
	pFile.Remove(Path);
	//Sleep(100);
	GetStartingEventCount();
	//Sleep(400);
	CHostCommand * request = new CHostCommand( DELETE_EVENT_HISTORY , data, DEL_EVENT_HIS_LEN  );
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		printf("\n data length = %d, data = ",length,*data);
		if(ch == theApp.ACK)
		{  
			if(*data==0xff)
			{
				printf("EVENT HISTORY DELETED\n"); 
			}  
			CEventLog::EventHistoryFullFlag = false;
			CEventLog::EventHistoryglobalCount = 0;
			CEventLog::SuccessfullyWrittenEventRecord = 0;
		}
		else if(ch == theApp.NAK)
		{
			printf("\n theApp.NAK");
		}
      delete response;
	} 
	CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
	CChildView::thisPtr->Invalidate(); 
}

void DeleteWeldHistory(int Address)
{
	CFile pFile;
	CString Path = HistoryDataFileName;
	int length = 0;
	unsigned char * data;
	char ch = 0;
	data = (unsigned char*)&ch;
	pFile.Remove(HistoryDataFileName);
	Path  = DISK ;
	Path = Path +  "WeldDataHidden.log";
	pFile.Remove(Path);
	Sleep(2);
	GetStartingWeldCount();
	Sleep(3);
	CHostCommand * request = new CHostCommand( DELETE_WELD_HISTORY, data, DEL_WELD_HIS_LEN );
	CHostCommand * response = app->SendUiHostCommand(request);
	if(response)
	{
		ch=CHostCommand::AckNak();
		data = response->GetData();
		length = response->GetDataLength();
		printf("\n data length = %d, data = ",length,*data);
		if(ch == theApp.ACK)
		{  
			if(*data==0xff){

				printf("WELD HISTORY DELETED\n"); }  
			CWeldingHistory::WeldSpaceFullFlag = false;
			CWeldingHistory::thisHisPtr->TotalDataInFile  = 0;
		}
		else if(ch == theApp.NAK)
		{
			printf("\n theApp.NAK");
		}
      delete response;
	}
	CChildView::thisPtr->SendCommandForStateMachineEnable(CChildView::STATE_MACH_ON);
	CChildView::thisPtr->Invalidate(); 

}