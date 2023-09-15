/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Toggle.cpp_v   1.17   29 Aug 2016 15:13:26   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Toggle.cpp_v  $
 * 
 *    Rev 1.17   29 Aug 2016 15:13:26   RJamloki
 * Added pressure hold step button function
 * 
 *    Rev 1.16   16 Apr 2015 06:00:26   sesharma
 * Run result screen flag is made false in UpdateSW_Config() function to make sure login after idle logout on run results screen set the right flag status.
 * 
 *    Rev 1.15   28 Nov 2014 08:32:00   rjamloki
 * Added function headers and Warning removed
 * 
 *    Rev 1.14   10 Nov 2014 02:51:14   rjamloki
 * MemoryFull_ContStop() changed.
 * 
 *    Rev 1.13   20 Oct 2014 05:47:50   RJamloki
 * Macros replaced by variables to support Control level D related changes
 * 
 *    Rev 1.12   25 Sep 2014 12:00:28   AnPawar
 * MouseClick() function changed
 * 
 *    Rev 1.11   05 Sep 2014 07:01:08   amaurya
 * Added new function AutomationClick().AuthorityCheckFunc() function modified.
 * 
 *    Rev 1.10   18 Aug 2014 07:56:22   rjamloki
 * Added DownSpeedTune click handler
 * 
 *    Rev 1.9   28 Jul 2014 14:16:28   rjamloki
 * void BasicExpertClick(int Value) function changed
 * 
 *    Rev 1.8   09 Jul 2014 07:07:06   akaushal
 * CToggle::MouseClick() function modified to check change conditions.MemoryFull_ContStop(),BasicExpertClick() function added
 * 
 *    Rev 1.7   09 Jun 2014 11:54:58   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.6   20 May 2014 11:06:56   rjamloki
 * AuthorityCheckFunc() function added.
 * 
 *    Rev 1.5   07 May 2014 13:10:24   akaushal
 * code cleanup and start screen flag to indicate initial screen
 * 
 *    Rev 1.4   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:36 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:28 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1    18 Dec 2013 10:00:34 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/
#include "stdafx.h"
#include "SBC.h"
#include "Toggle.h"
#include "XmlElement.h"
#include "Variable.h"
#include "VGA.h"
#include "VgaButton.h"
#include "WeldingHistory.h"
#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void ProcessSequence(int ID);
extern CChildView::PrintValues Setup,Welddata, WeldHistory,PowerGraph,ColDistance,VelocityGraph,
	ForceGraph,AmplitudeGraph,FrequencyGraph,PrintSequence;

extern CChildView::USBValues  USBWelddata,USBPowerGraph,USBColDistance,USBVelocityGraph,
	USBForceGraph,USBAmplitudeGraph,USBFrequencyGraph;

extern void logOutFun(int ID);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
bool CToggle::SequencingON=false;
/***************************************************************************************/
/*                                                                                     */
/*  This function parse the XML Doccument for toggle objects and takes the textid and  */
/* function name  menu name and enumconditions from the XML                            */
/***************************************************************************************/

CToggle::CToggle(CXmlElement * e)
{
	Toggle_Value = false;
	rect = CRect(0, 0, 0, 0);
	RectShow=1;
	textID=e->GetAttribute("textID");
	text=CVgaMenuItem ::LinearSearch(textID);
	FunName=e->GetAttribute("FunName");
	Toggle_Text1=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID1"));
	Toggle_Text2=CVgaMenuItem ::LinearSearch(e->GetAttribute("ID2"));
	NoCommandFun = e->GetAttribute("NoCommandFun");
	MenuName = e->GetAttribute("menuname");
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

}

CToggle::~CToggle()
{

}

/*************************************************************************************/
/*                                                                                   */
/*  This function draws the toggle object of selected colour and displays the text on*/
/* the button.
/*************************************************************************************/

void CToggle::Draw(CDC *pDC)
{
	CString TempText = text;
	if(CChildView::thisPtr->StringDebugFlag)
		TempText = textID + _T(" ")+ text;

	DrawRect(pDC, CChildView::Button_Color, rect);
	Draw_Pressed_Released_Button(pDC);
	DrawText(pDC, SmallFont, CChildView::TextColor, rect, TempText,true);
	DrawRect(pDC, CChildView::Back_Color, CRect(rect.right,
		rect.top,
		(rect.right+130),
		rect.bottom));
	DrawText(pDC, SmallFont, CChildView::TextColor, CRect(rect.right,
		rect.top,
		(rect.right+100),
		rect.bottom), Toggle_Text,false);


}

/*************************************************************************************/
/*                                                                                   */
/*  This function is called when any toggle object is clicked by the user            */
/* This funtion sends a host command to get the new toggled string and displays it.  */
/* If NAK is obtained as the response then the funstion justs BEEPS indicating a NAK */
/*************************************************************************************/

bool CToggle::MouseClick(const CPoint &p, CChildView *view)
{
	if(view->CheckChangeConditions(this) == false)
	{
		CChildView::ErrorBeep();//gives the error beep
		return true;
	}

	int length =INTEGERLENGTH-1;
	unsigned char data[INTEGERLENGTH];
	union 
	{
		short i;
		char c[2];
	} u;
	u.i=EnumID;
	data[1]=u.c[0];
	data[0]=u.c[1];
	data[2]=(char)(!Toggle_Value);
	unsigned char * data1 = (unsigned char *) &data[0];

	if(NoCommandFun == "")
	{
		CHostCommand * request = new CHostCommand(SetValue_FunID, data1, length);
		CHostCommand * response = app->SendUiHostCommand(request);
		if (response)
		{
			char ch=CHostCommand::AckNak();
			data1 = response->GetData();
			length = response->GetDataLength();
			if(ch==ACK)
			{
				int OneByteValue=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
				Toggle_Value = (OneByteValue != 0) ;
				if(FunName!="")
				{
					void *ptr;
					void (*rmn)(int);
					if(functionCall.Lookup(FunName,ptr))
					{
						rmn = (void (*)(int))ptr;
						rmn(Toggle_Value);
					}
				}

				if(Toggle_Value)
					Toggle_Text= " = " + Toggle_Text1;
				else
					Toggle_Text= " = " + Toggle_Text2;

				int refresh=CVgaMenuItem::Convert_Char_To_Integer(data1,length,3);
				if(refresh)
				{
					theApp.GetSystemVariable();
					view->MaxPreset=1;	
					view->ModifyObjectList(theApp.MenuPointer);
				}

				int ID=CVgaMenuItem::Convert_Char_To_Integer(data1,length,2);
				CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
				view->Invalidate();
			}
			else
				view->ProcessNak(data1,length,0,0);
			delete response;
		}
	}
	else
	{
		void *ptr;
		void (*rmn)(CToggle*);
		if(functionCall.Lookup(NoCommandFun,ptr))
		{
			rmn = (void (*)(CToggle*))ptr;
			rmn(this);
		}	
	}
	return true;
}

/** @brief USBForceGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in force graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBForceGraphSaveAlarm(int value)
{
	USBForceGraph.USBOnAlarmValue = (value != 0);
}

/** @brief USBDistanceGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in distance graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBDistanceGraphSaveAlarm(int value)
{
	USBColDistance.USBOnAlarmValue = (value != 0);
}

/** @brief USBAmplitudeGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in amplitude graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBAmplitudeGraphSaveAlarm(int value)
{
	USBAmplitudeGraph.USBOnAlarmValue = (value != 0);
}

/** @brief USBPowerGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in power graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBPowerGraphSaveAlarm(int value)
{
	USBPowerGraph.USBOnAlarmValue = (value != 0);
}

/** @brief USBVelocityGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in velocity graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBVelocityGraphSaveAlarm(int value)
{
	USBVelocityGraph.USBOnAlarmValue = (value != 0);
}

/** @brief USBFrequencyGraphSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in frequency graph in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBFrequencyGraphSaveAlarm(int value)
{
	USBFrequencyGraph.USBOnAlarmValue = (value != 0);
}

/** @brief USBWeldDataSaveAlarm
*
*  This function is called when toggle button "Save on Alarm"
*  is clicked in weld data in Streaming setup
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBWeldDataSaveAlarm(int value)
{
	USBWelddata.USBOnAlarmValue = (value != 0);
}


/** @brief USBGlobalFlagOn_Off
*
*  This function is called when toggle button "USB"
*  is clicked in Streaming data setup menu
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void USBGlobalFlagOn_Off(int value)
{
	CChildView::thisPtr->USBGlobalFlag = (value != 0);
}

/** @brief ProcessExtPrest
*
*  This function is called when toggle button "Ext Presets"
*  is clicked.
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void ProcessExtPrest(int value)
{
	CChildView::thisPtr->ExtPreset = (value != 0);
	theApp.GetSystemVariable();
	while(CChildView::thisPtr->GetPrintingParameters(true));
}

/** @brief UpdateSW_Config
*
*  This function is called when toggle button "Hand held"
*  and "Weld status"is clicked.
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void UpdateSW_Config(int value)
{
	CChildView::RunResultScreen = false;//function called as main menu title handler. 
										//Run result screen flag is made false here to make sure login after idle logout on run results
										//screen set the right flag status.
	theApp.GetSystemVariable();
}

/** @brief ChangeStartScreen
*
*  This function is called when toggle button "Start Screen"
*  is clicked.
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void ChangeStartScreen(int value)
{
	CChildView::thisPtr->Start_Screen = (value != 0);
}

/** @brief AuthorityCheckFunc
*
*  This function is called when toggle button "Authority Check"
*  is clicked.
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void AuthorityCheckFunc(int value)
{
	CChildView::thisPtr->AuthorityCheckLogOut = true;
    CChildView::thisPtr->AuthorityCheck = (value != 0);
	theApp.GetSystemVariable();
}


/** @brief MemoryFull_ContStop
*
*  This function is called on memory full button.The value is stroed in 
*  MemoryfullCont_Stop flag.If this flag is set then the event and history 
*  file is overwritten after 100,000 records.When 100,000 events or welds 
*  are crossed then alarm flags are set.
*
*  @param toggle value of button either 1 or 0.If 1 then records will 
*         overwritten.If 0 then alarm will generate.
*  @return void.
*/
void MemoryFull_ContStop(int value)
{
    CChildView::thisPtr->MemoryfullCont_Stop = (value != 0);
	printf("CChildView::thisPtr->MemoryfullCont_Stop = %d \n",CChildView::thisPtr->MemoryfullCont_Stop);
	if(value)//1 continue
	{
		CEventLog::EventHistoryFullFlag   = false;
		CWeldingHistory::WeldSpaceFullFlag = false;		
	}
	else
	{

		if(CWeldingHistory::TotalDataInFile >= (unsigned int)CChildView::Max_Allowed_Weld_Log)
			CWeldingHistory::WeldSpaceFullFlag = true;
		else
			CWeldingHistory::WeldSpaceFullFlag = false;

		if(CEventLog::EventHistoryglobalCount >= MAX_ALLOWED_EVENT_LOG) 
			CEventLog::EventHistoryFullFlag   = true;
		else
			CEventLog::EventHistoryFullFlag   = false;
	}
}

/** @brief BasicExpertClick
*
*  This function is called when toggle button "Basic/Expert"
*  is clicked.This function doesnt store the value
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void BasicExpertClick(int Value)
{
	page_no = 1;
	theApp.GetSystemVariable();
}

/** @brief DownspeedTuneClick
*
*  This function is called when toggle button "Downspeed Tunning"
*  is clicked.
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void DownspeedTuneClick(int Value)
{
	CChildView::thisPtr->DownspeedEnable = (Value != 0);
}

/** @brief AutomationClick
*
*  This function is called when toggle button "Automation"
*  is clicked.This function doesnt store the value
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void AutomationClick(int Value)
{
	theApp.GetSystemVariable();
	if(CChildView::Automation)
		UserLoggedinFlag = false;
}

/** @brief DrawPresetValidMsg
 *
 *  This function is called on preset validation menu.
 *  When the preset validation button and preset locked
 *  toggle button is clicked.Function add the current menu 
 *  pointer the menu pointers list.
 *
 *  @param1 CToggle *ptr,pointer to this toggle button.
 *  @return void.
 */
void DrawPresetValidMsg(CToggle *ptr)
{
	CVgaMenu *menu;
	CString NextMenu = ptr->MenuName;
	if (theApp.menus.Lookup(NextMenu, menu))
    {
		CChildView::thisPtr->menusname.AddTail(theApp.menuName);
		CChildView::thisPtr->menus.AddTail(page_no);
		CChildView::thisPtr->menupointers.AddTail(theApp.MenuPointer);
		CChildView::thisPtr->ModifyObjectList(menu);

		page_no=1;
        theApp.menuName = NextMenu;
        theApp.MenuPointer = menu;
    }
	CChildView::thisPtr->Invalidate();
}

/** @brief Down step pressure Click
*
*  This function is called when toggle button "Basic/Expert"
*  is clicked.This function doesnt store the value
*
*  @param toggle value 0 or 1.
*  @return void.
*/
void PressureStepDownClick(int Value)
{
    CString MenuName;
	CVgaMenu *menu;
    CString Lastmenu = "";
	MenuName = XSTR(PRESSURESTEPDOWN_ALARM);
    if(Value==1){
	  if (theApp.menus.Lookup(MenuName, menu))
      {
	   page_no=1;
       Lastmenu = theApp.menuName;
       theApp.menuName = MenuName;
       theApp.MenuPointer=menu;
       CChildView::thisPtr->ModifyObjectList(menu);
	   CChildView::thisPtr->Invalidate();
	  }
	}
}
