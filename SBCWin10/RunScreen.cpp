/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RunScreen.cpp_v   1.11   16 Apr 2015 05:58:36   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/RunScreen.cpp_v  $
 * 
 *    Rev 1.11   16 Apr 2015 05:58:36   sesharma
 * Change in UpdateWeldData() function to fix duplicate weld cycles issue on weld results screen.
 * 
 *    Rev 1.10   28 Jul 2014 16:15:32   rjamloki
 * corrected parameter_id
 * 
 *    Rev 1.9   28 Jul 2014 14:06:26   rjamloki
 * review comment,memory leak care taken.
 * 
 *    Rev 1.8   09 Jun 2014 11:50:34   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.7   20 May 2014 11:01:54   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.6   07 May 2014 13:08:08   akaushal
 * code cleanup.
 * 
 *    Rev 1.5   23 Apr 2014 11:24:00   akaushal
 * Added a global count to keep track of Weld Data in log file
 * 
 *    Rev 1.4   28 Mar 2014 14:33:08   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:26 rjamloki     
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:04 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:30 rjamloki     
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:54 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "RunScreen.h"
#include "WeldingHistory.h"

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

CRunScreen::CRunScreen(CXmlElement * e)
{
	ReceivedUniversalCount = 0;
	TotalCycles = 0;
	rect = CRect(_ttoi(e->GetAttribute("X1"))+XOFFSET,
		_ttoi(e->GetAttribute("Y1"))+YOFFSET,
		_ttoi(e->GetAttribute("X2"))+XOFFSET,
		_ttoi(e->GetAttribute("Y2"))+YOFFSET);

	RunID=	_ttoi(e->GetAttribute("StructID"));	
	//printf("\n RunID=%d",RunID);
	//	Displayable_columns=CChildView::WeldParamCount;//*data++;//Displayable coloumns.
	//	printf("\n Displayable_columns=%d",CChildView::WeldParamCount);
	//	Parameter_ID=new int[Displayable_columns];

	POSITION pos = e->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * element = e->children.GetNext(pos);
		CString tag = element->GetTag();
		if (tag == "condition")
		{
			AddCondition(element);
		}
		else
			ASSERT(FALSE);
	}
	/*	length--;	
	Parameter_ID=new int[Displayable_columns];
	for(int param=0;param<Displayable_columns;param++)	//Storing parameters ID.
	{
	Parameter_ID[param]=*data++;
	length--;
	}
	ReceivedUniversalCount=Convert_Char_To_Integer(data,length,0);
	TotalCycles=*data++;//Numbers of cycle for which weld data is to be shown.
	length--;
	TRACE(_T("\n TotalCycles is %d \n"),TotalCycles);

	while(length>0)
	{
	for(int cycle =0;cycle<TotalCycles;cycle++)
	{
	CWeldData * obj = new CWeldData(data, length);
	WeldDataList.AddTail(obj);
	}
	}*/
   Parameter_ID = NULL;
}

int CRunScreen::Displayable_columns=0;
int* CRunScreen::ID_Array;
int  *CRunScreen::Parameter_ID;
CRunScreen::~CRunScreen()
{
	if(Parameter_ID != NULL) {
      delete[] Parameter_ID;
      Parameter_ID = NULL;
   }
	while (WeldDataList.GetCount()>0)
		delete WeldDataList.RemoveHead();
}

/*************************************************************************************/
/*                                                                                   */
/*  This function Draws a Weld Data When any Weld Data is found in menu/submenu item */
/*  list for current page .															 */
/*																					 */		 
/*************************************************************************************/
void CRunScreen::Draw(CDC *pDC)
{
	int X1 = 8;
	int Y1 =100;
	int Width =120;
	int Height = 30;
	CRect TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
	CRect UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
	for(int index =0; index<5;index++)
	{
		TextRect = CRect(X1,Y1,X1+Width,Y1+Height);
		UnitRect= CRect(X1,Y1+Height,X1+Width,Y1+Height+Height);
		for(int index1 =0;index1<CChildView::TotalTextHeading;index1++)
		{
			bool found =false;
			if(Parameter_ID[index] == CChildView::Parameter_ID[index1])
			{
				found =true;

				CString TempParamHeading = CChildView::Parameter_Heading[index1];
				if(CChildView::thisPtr->StringDebugFlag)
					TempParamHeading = CChildView::WeldDataPatamStringID[index1] + _T(" ")+ CChildView::Parameter_Heading[index1];

				DrawText(pDC, SmallFont, Black, TextRect, TempParamHeading,false);
				if(CChildView::metric)
					DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_Metric[index1],false);
				else
					DrawText(pDC, SmallFont, Black, UnitRect, CChildView::Parameter_Units_USCS[index1],false);
			}
			if(Parameter_ID[index] ==0)
				DrawText(pDC, SmallFont, Black, TextRect, "****",false);
		}
		X1 +=Width;
	}


	POSITION pos = WeldDataList.GetHeadPosition();
	CWeldingData::CycleCount=0;
	while(pos)
	{
		CWeldingData * Obj = WeldDataList.GetNext(pos);
		Obj->Draw(pDC);
	}
}

bool CRunScreen::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}


void CRunScreen::UpdateWeldData(unsigned char *&data, int &length, bool Constructor)
{
	int OldReceivedUniversalCountRun = ReceivedUniversalCount;//Copy the universal count when we entered the run result screen
														     //See case RUNSCREEN_CONDITION: in EnumCondition.cpp
	int TotalColoumn = *data++;length--;	
	ID_Array=new int[TotalColoumn];

	for(int columns =0;columns< TotalColoumn; columns++)
	{
		ID_Array[columns] =*data++;
		length--;
	}

	ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);	

	int TotalCycle =*data++;length--;
	//	printf("\n TotalCycle  in update=%d",TotalCycle);
	CTypedPtrList<CPtrList, CWeldingData *> TempWeldDataList;
	//storing parameters whose ID matches with displayable parameter ID 
	if(ReceivedUniversalCount > OldReceivedUniversalCountRun)//check we have new results to display
	{
		int NewCycles = ReceivedUniversalCount - OldReceivedUniversalCountRun;//number of new cycles to be added in draw list
		int SkipCycles = TotalCycle - NewCycles;//skip these many as they are already in list
		for(int cycle =0;cycle<TotalCycle;cycle++)
		{
			CWeldingData * obj = new CWeldingData(data, length,TotalColoumn);
			//	printf("\n before TempWeldDataList adding");
			if(SkipCycles-- > 0)
				delete obj;
			else
				TempWeldDataList.AddHead(obj);
			//	printf("\n After TempWeldDataList adding");
		}
		//printf("\n CWeldingData complete");
		while(TempWeldDataList.GetCount()>0)
		{
			CWeldingData * obj = TempWeldDataList.RemoveHead();
			WeldDataList.AddHead(obj);
		}
		while(WeldDataList.GetCount() > 7)
			delete WeldDataList.RemoveTail();	
	}
	delete []  ID_Array;
	
}
