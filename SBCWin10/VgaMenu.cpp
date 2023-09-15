/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenu.cpp_v   1.11   09 Jul 2014 07:15:30   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenu.cpp_v  $
 * 
 *    Rev 1.11   09 Jul 2014 07:15:30   akaushal
 * CVgaMenu::Draw() changed.
 * 
 *    Rev 1.10   09 Jun 2014 12:05:00   rjamloki
 * Variable initialization in constructor.Coverity fixes
 * 
 *    Rev 1.9   27 May 2014 06:46:18   amaurya
 * Display Lock and Alarm Button disable on Login Screen
 * 
 *    Rev 1.8   20 May 2014 11:13:44   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.7   07 May 2014 13:15:30   akaushal
 *  Bottom menu disabling code for message screen
 * 
 *    Rev 1.6   21 Apr 2014 13:53:42   akaushal
 *  CVgaMenu::Draw() function changed to remove bottom menu from login message screen.
 * 
 *    Rev 1.5   28 Mar 2014 14:33:20   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:58 rjamloki   
 * Screens and PDF working
 *
 *    Rev 1.3     27 Feb 2014 01:51:48 jerryw.wang    
 * Added the XML parsed for the AlarmLog menu, EventHistory menu and VgaDigitalInput menu.
 *
 *    Rev 1.2     03 Jan 2014 09:06:26 rjamloki    
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:34 rjamloki    
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:10:12 amaurya      
 * Initial Revision.
 *
*/
#include "stdafx.h"
#include "VgaMenu.h"
#include "XmlElement.h"
#include "VgaTitle.h"
#include "VgaSubMenu.h"
#include "ChildView.h"
#include "VgaBottomMenu.h"
#include "VGAAdd_Back_Next_Button.h"
#include "VgaMenuItem.h"
#include "VgaChoice.h"
#include "Text.h"
#include "Toggle.h"
#include "RadioMenu.h"
#include "VgaVariable.h"
#include "Date.h"
#include "Time.h"
#include "VgaButton.h"
#include "VgaRadioButton.h"
#include "MsgScreen.h"
#include "ListBox.h"
#include "VgaAlphanumeric.h"
#include "BottomHalf.h"
#include "Check.h"
#include "VgaScreenSetup.h"
#include "Line.h"
#include "RunScreen.h"
#include "WeldingHistory.h"
#include "TextBox.h"
#include "VgaDrawGraph.h"
#include "Table.h"
#include "LocalChoice.h"
#include "VgaCompareGraph.h"
#include "VgaViewPreset.h"
#include "AlarmButton.h"
#include "HistoryGraphs.h"
#include "VgaDigitalInput.h"
#include "VGA.h"
#include "AlarmLog.h"
#include "EventLog.h"
#include "UserIDTable.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CVgaMenuItem *GlobalAlarmObject;
CVgaMenu::CVgaMenu()
{
	MenuType = BottomMenu_Id;
}

CVgaMenu::CVgaMenu(CXmlElement * element)
{
	MenuType = BottomMenu_Id;
	name = element->GetAttribute("name");
	POSITION pos = element->children.GetHeadPosition();
	while (pos)
	{
		CXmlElement * e = element->children.GetNext(pos);
		CString tag = e->GetTag();
		if (tag == "onenter")
			;
		else if (tag == "onexit")
			;
		else if (tag == "title")
			AddTitle(e);
		else if (tag == "submenu")
			AddSubmenu(e);
		else if(tag == "choice")
			AddChoicemenu(e);
		else if(tag == "textmenu")
			AddText(e);
		else if(tag == "togglemenu")
			AddTogglemenu(e);
		else if(tag == "radiomenu")
			AddRadioMenu(e);
		else if(tag == "variablemenu")
			AddVariableMenu(e);
		else if(tag == "Datemenu")
			AddDateMenu(e);
		else if(tag == "Timemenu")
			AddTimeMenu(e);
		else if(tag == "VgaButton")
			AddVgaButtonMenu(e);
		else if(tag == "VgaRadioButton")
			AddVgaRadioButtonMenu(e);
		else if(tag == "MsgScreen")
			AddMsgScreen(e);
		else if(tag == "ListBox") 
			AddListBox(e);
		else if(tag== "AlphaNumeric")
			AddAlphaNumeric(e);
		else if(tag=="BottomHalf")
			AddBottomHalf(e);
		else if(tag=="Check")
			AddCheck(e);
		else if(tag=="screensetup")
		{
			//printf("\n screensetup");
			AddScreenSetup(e);
		}
		else if(tag=="Line")
			AddLine(e);
		else if(tag=="RunMenu")
			AddRunMenu(e);	
		else if(tag=="HistoryMenu")
			AddHistoryObject(e);
		else if(tag=="AlarmLogMenu")
			AddAlarmLogObject(e);
		else if(tag=="EventLogMenu")
			AddEventLogObject(e);
		else if(tag=="UserIDMenu")
			AddUserIDTableObject(e);
		else if(tag=="TextBox")
			AddTextBoxObject(e);
		else if(tag=="Graph")
			AddGraphObject(e);
		else if(tag=="TableObject")
			AddTableObject(e);
		else if(tag=="LocalChoiceObject")
			AddLocalChoiceObject(e);
		else if(tag=="CompareGraph")
			AddCompareGraph();
		else if(tag=="ViewPreset")
			AddViewPreset();
		else if(tag=="AlarmButton")
			AddAlarmButton(e);
		else if(tag=="HistoryGraphMenu")
			AddHistoryGraph(e);
		else if(tag == "DigitalInputMenu")
			AddDigitalInput(e);
		else
			ASSERT(FALSE);
	}
	AddBottomMenu();
}

CVgaMenu::~CVgaMenu()
{
}

void CVgaMenu::AddTitle(CXmlElement *e)
{
	CVgaTitle * title = new CVgaTitle(e);
	if (title)
	{
		title->PSType=TITLE;
		title->SetType(TITLE);
		items.AddTail(title);
	}
}

void CVgaMenu::Draw(CDC *pDC) const
{
	int y = 0;
	POSITION pos = items.GetHeadPosition();
	CString txt,funcname;
	bool disableBottomMenu = false;
	bool drawAlarmButn = true;
	//	printf("\n menu draw");
	while (pos)
	{
		CVgaMenuItem * item = items.GetNext(pos);
		int type=item->GetType();
		//disable bottom menu
		if( item->GetType()== CVgaMenu::TITLE )
		{
			CVgaTitle *ptr=(CVgaTitle *)item;
			disableBottomMenu = ptr->BottomMenuDisable;
			drawAlarmButn = ptr->DrawAlarmButton;
		}
		if((item->GtPageNum()==page_no)||(item->GtPageNum()==CVgaMenuItem::PAGEALL))
		{
			if((item->IsDraw)&&(item->GetType()!=VGA_GRAPH_OBJECT))
				item->DrawItem(pDC);
		}
		if(item->GetType() == BottomMenu_Id)
		{
			if(disableBottomMenu==true)
			{
				item->IsDraw =true;
				item->RectShow=false;			
			}	
			item->DrawItem(pDC);
		}
	}
	
		
	POSITION pos1 = theApp.GraphsDataList.GetHeadPosition();
	CVgaDrawGraph::GraphBoundary=false;
	while(pos1)
	{
		//printf("\n graph draw");
		CVgaDrawGraph *obj = theApp.GraphsDataList.GetNext(pos1);
		if(CChildView::thisPtr->AutoRefreshon)
		{
			//printf("\n Auto on type=%d",obj->GraphType);
			if((obj->GraphType==POWGRAPH)//obj->MaxGraphType)
				/*&&(menuEntryList.GetCount()>7)*/&&(!CChildView::thisPtr->PMCScreen))
			{
				//printf("\n Auto refresh on GetAveragePowerGraph");
				// obj->GraphType=obj->MaxGraphType;
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
				// obj->Draw(pDC);
				// obj->GraphType=1;
			}
			
			if ((!CChildView::thisPtr->DisableFlag) && (!CChildView::thisPtr->PMCScreen))
				obj->Draw(pDC);
			
			if(CChildView::thisPtr->PMCScreen)
			{
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
				//printf("\n PMCScreen");
				if(!CChildView::thisPtr->DisableFlag)
					obj->Draw(pDC);
			}
			
			
		}
		else
		{
			//printf("\n type Auto off=%d",obj->GraphType);
			if((obj->GraphType == 1/*obj->MaxGraphTypeobj->graph_type!=CScreenObject::VGA_HORNSCANGRAPH*/)&&(!CChildView::thisPtr->PMCScreen)
				&&((obj->GraphData.GraphRequestValue==2)&&((CChildView::thisPtr->GraphOneRequestValue==2)||(CChildView::thisPtr->GraphTwoRequestValue==2))))
			{
				//printf("\n Auto refresh off GetAveragePowerGraph");
				//obj->GraphType=obj->MaxGraphType;
				CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
				//obj->Draw(pDC);
				//obj->GraphType=1;
			}
			
			if((obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
				||(obj->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)||((obj->GraphData.graph_type)>(PMC_GRAPH))//CScreenObject::VGA_NOGRAPH)
				||/*(obj->graph_type==CScreenObject::VGA_NOHSGRAPH)||*/((obj->GraphData.graph_type == (PMC_GRAPH-1))))/*CScreenObject::VGA_HORNSCANGRAPH*///||(CVGAButtons::PMCScreen))
				if(!CChildView::thisPtr->DisableFlag)
					obj->Draw(pDC);
				
				if(CChildView::thisPtr->PMCScreen)
				{
					//printf("\n PMCScreen");
					CChildView::thisPtr->GetAveragePowerGraph(pDC,CChildView::thisPtr);
					if(!CChildView::thisPtr->DisableFlag)
						obj->Draw(pDC);
				}
		}
	}
	/*disable alarm button on screen setup and login*/
	if(  (CChildView::thisPtr->AlarmUpdateRequired)&&(!CChildView::thisPtr->ScreenSetupFlag)&&(drawAlarmButn) )
	{
		GlobalAlarmObject->SetText(CChildView::thisPtr->GetAlarmString(GlobalAlarmObject));
		GlobalAlarmObject->Draw(pDC);
	}
	
}

void CVgaMenu::AddSubmenu(CXmlElement *e)
{
	CVgaSubMenu * subMenu = new CVgaSubMenu(e);
	if (subMenu)
	{
		subMenu->PSType=SUBMENU;
		subMenu->SetType(SUBMENU);
		items.AddTail(subMenu);
	}
}

void CVgaMenu::AddBottomMenu()
{
	CVgaBottomMenu * object = 0;
	object = new CVgaBottomMenu();
	if (object)
	{
		object->PSType=BottomMenu_Id;
		object->SetType(BottomMenu_Id);
		object->IsDraw = true;
		items.AddTail(object);
	}
	
	
}

CVgaMenuItem* CVgaMenu::CreateObjectBack_Next(int exit_type)
{
	CVGAAdd_Back_Next_Button * object = 0;
	object = new CVGAAdd_Back_Next_Button(exit_type);
	if(object)
	{		
		object->PSType=exit_type;	
		object->SetType(exit_type);
		object->IsDraw = true;
	}
	return(object);
}

void CVgaMenu::AddChoicemenu(CXmlElement * e)
{
	CVgaChoice * ChoiceMenu = new CVgaChoice(e);
	if(ChoiceMenu)
	{
		ChoiceMenu->PSType=CHOICE;
		ChoiceMenu->SetType(CHOICE);
		items.AddTail(ChoiceMenu);
	}
}

void CVgaMenu::AddText(CXmlElement * e)
{
	CText * TextMenu = new CText(e);
	if(TextMenu)
	{
		TextMenu->PSType=TEXT;	
		TextMenu->SetType(TEXT);
		items.AddTail(TextMenu);
	}
}

void CVgaMenu::AddTogglemenu(CXmlElement * e)
{
	CToggle * ToggleMenu = new CToggle(e);
	if(ToggleMenu)
	{
		ToggleMenu->PSType=TOGGLE;
		if (ToggleMenu)
			ToggleMenu->SetType(TOGGLE);
		items.AddTail(ToggleMenu);
	}
}

void CVgaMenu::AddRadioMenu(CXmlElement * e)
{
	CRadioMenu * RadioMenu = new CRadioMenu(e);
	if(RadioMenu)
	{	
		RadioMenu->PSType=RADIOMENU;	
		RadioMenu->SetType(RADIOMENU);
		items.AddTail(RadioMenu);
	}
}
void CVgaMenu::AddVariableMenu(CXmlElement * e)
{
	CVgaVariable * VariableMenu = new CVgaVariable(e);
	if(VariableMenu)
	{
		VariableMenu->PSType=VARIABLE;	
		VariableMenu->SetType(VARIABLE);
		items.AddTail(VariableMenu);
	}	
}
void CVgaMenu::AddDateMenu(CXmlElement * e)
{
	CDate * DateMenu = new CDate(e);
	if(DateMenu)
	{
		DateMenu->PSType=DATE;	
		DateMenu->SetType(DATE);
		items.AddTail(DateMenu);
	}
}
void CVgaMenu::AddTimeMenu(CXmlElement * e)
{
	CVgaTime * TimeMenu = new CVgaTime(e);
	if(TimeMenu)
	{
		TimeMenu->PSType=HHMM;
		TimeMenu->SetType(HHMM);
		items.AddTail(TimeMenu);
	}

}
void CVgaMenu::AddVgaButtonMenu(CXmlElement * e)
{
	CVgaButton * VgaButtonMenu = new CVgaButton(e);
	if(VgaButtonMenu)
	{
		VgaButtonMenu->PSType=VGA_Button_OBJECT;	
		VgaButtonMenu->SetType(VGA_Button_OBJECT);
		items.AddTail(VgaButtonMenu);
	}
}

void CVgaMenu::AddVgaRadioButtonMenu(CXmlElement * e)
{
	CVgaRadioButton * VgaRadioButtonMenu = new CVgaRadioButton(e);
	if(VgaRadioButtonMenu)
	{
		VgaRadioButtonMenu->PSType=RADIO_BUTTON;
		VgaRadioButtonMenu->SetType(RADIO_BUTTON);
		items.AddTail(VgaRadioButtonMenu);
	}
}

void CVgaMenu::AddMsgScreen(CXmlElement * e)
{
	CMsgScreen * MsgScreen = new CMsgScreen(e);
	if(MsgScreen)
	{
		MsgScreen->PSType=VGAMsgScrnObject;
		MsgScreen->SetType(VGAMsgScrnObject);
		items.AddTail(MsgScreen);
	}
}

void CVgaMenu::AddListBox(CXmlElement * e)
{
	CListBoxObject * ListBoxScreen = new CListBoxObject(e);
	if(ListBoxScreen)
	{
		ListBoxScreen->PSType=VGA_LISTBOX;
		ListBoxScreen->SetType(VGA_LISTBOX);
		items.AddTail(ListBoxScreen);
	}
}
void CVgaMenu::AddAlphaNumeric(CXmlElement * e)
{
	CVgaAlphanumeric * AlphaPointer = new CVgaAlphanumeric(e);
	if(AlphaPointer)
	{
		AlphaPointer->PSType=ALPHA;	
		AlphaPointer->SetType(ALPHA);
		items.AddTail(AlphaPointer);
	}
}

void CVgaMenu::AddBottomHalf(CXmlElement * e)
{
	CBottomHalf *BottomHalf= new CBottomHalf(e);
	if(BottomHalf)
	{
		BottomHalf->PSType = VGABottomHalfObject;		
		BottomHalf->SetType(VGABottomHalfObject);
		items.AddTail(BottomHalf);
	}
}

void CVgaMenu::AddCheck(CXmlElement * e)
{
	CCheck *Checkpointer= new CCheck(e);
	if(Checkpointer)
	{
		Checkpointer->PSType = VGACheck;	
		Checkpointer->SetType(VGACheck);
		items.AddTail(Checkpointer);
	}
}

void CVgaMenu::AddScreenSetup(CXmlElement * e)
{
	CVgaScreenSetup::SetScreenMemberVariable(e);
}

void CVgaMenu::AddLine(CXmlElement * e)
{
	CLine *Linepointer= new CLine(e);
	if(Linepointer)
	{
		Linepointer->PSType = VGALINE;	
		Linepointer->SetType(VGALINE);
		items.AddTail(Linepointer);
	}
}

void CVgaMenu::AddRunMenu(CXmlElement * e)
{
	CRunScreen *Runptr=new CRunScreen(e);
	if(Runptr)
	{
		Runptr->PSType =VGARUNSCREENOBJECT;
		Runptr->SetType (VGARUNSCREENOBJECT);
		items.AddTail(Runptr);
	}
}

void CVgaMenu::AddHistoryObject(CXmlElement * e)
{
	CWeldingHistory *Runptr=new CWeldingHistory(e);
	if(Runptr)
	{
	   Runptr->PSType =VGAHISTORYOBJECT;
	   Runptr->SetType (VGAHISTORYOBJECT);
	   items.AddTail(Runptr);
	}
}

void CVgaMenu::AddAlarmLogObject(CXmlElement * e)
{
	CAlarmLog *Runptr = new CAlarmLog(e);
	if(Runptr)
	{
	    Runptr->PSType = VGAALARMLOGOBJECT;		
		Runptr->SetType(VGAALARMLOGOBJECT);
		items.AddTail(Runptr);
	}
}

void CVgaMenu::AddEventLogObject(CXmlElement * e)
{
	CEventLog *Runptr = new CEventLog(e);
	if(Runptr)
	{
	    Runptr->PSType = VGAEVENTLOGOBJECT;
		Runptr->SetType(VGAEVENTLOGOBJECT);
		items.AddTail(Runptr);
	}
}

void CVgaMenu::AddUserIDTableObject(CXmlElement * e)
{
	CUserIDTable *Runptr = new CUserIDTable(e);
	if(Runptr)
	{
		Runptr->PSType = VGAUSERIDTABLEOBJECT;	
		Runptr->SetType(VGAUSERIDTABLEOBJECT);
		items.AddTail(Runptr);
	}
}

void CVgaMenu::AddTextBoxObject(CXmlElement * e)
{
	CTextBox *Textptr=new CTextBox(e);
	if(Textptr)
	{
		Textptr->PSType =VGATEXTBOX;	
		Textptr->SetType (VGATEXTBOX);
		items.AddTail(Textptr);
	}
}

void CVgaMenu::AddGraphObject(CXmlElement * e)
{
	CVgaDrawGraph *Graphptr=new CVgaDrawGraph(e);
	if(Graphptr)
	{
		Graphptr->PSType =VGA_GRAPH_OBJECT;
		Graphptr->SetType (VGA_GRAPH_OBJECT);
		items.AddTail(Graphptr);
	}
} 


void CVgaMenu::AddTableObject(CXmlElement * e)
{
	CTable *TablePtr=new CTable(e);
	if(TablePtr)
	{
		TablePtr->PSType =VGATableObject;
		TablePtr->SetType (VGATableObject);
		items.AddTail(TablePtr);
	}
} 

void CVgaMenu::AddLocalChoiceObject(CXmlElement * e)
{
	CLocalChoice * LocalChoicePtr = new CLocalChoice(e);
	if(LocalChoicePtr)
	{
		LocalChoicePtr->PSType=CHOICE;
		LocalChoicePtr->SetType(CHOICE);
		items.AddTail(LocalChoicePtr);
	}
}

void CVgaMenu::AddCompareGraph()
{
	CVgaCompareGraph * object = 0;
	object = new CVgaCompareGraph();
	if(object)
	{
		object->PSType=CHOICE;	
		object->SetType(CHOICE);
		object->IsDraw = true;
		items.AddTail(object);
	}
}

void CVgaMenu::AddViewPreset()
{
	CVgaViewPreset * ViewPtr = new CVgaViewPreset("");
	if(ViewPtr)
	{
		ViewPtr->PSType=COLORSETUP_ID;		
		ViewPtr->SetType(COLORSETUP_ID);
		items.AddTail(ViewPtr);
	}
}

void CVgaMenu::AddAlarmButton(CXmlElement * e)
{
	CAlarmButton * AlarmButton = new CAlarmButton(e);
	if(AlarmButton)
	{
		AlarmButton->PSType=VGA_Button_OBJECT;
		AlarmButton->SetType(VGA_ALARMBUTTON);
		items.AddTail(AlarmButton);
		AlarmButton->IsDraw =true;
		AlarmButton->RectShow=true;
		AlarmButton->SetPageNum(CVgaMenuItem::PAGEALL);
	}
}

void CVgaMenu::AddHistoryGraph(CXmlElement * e)
{
	CHistoryGraphs *HisGraph=new CHistoryGraphs();
	HisGraph->PSType=VGAHistoryGraphObject;
	HisGraph->SetType(VGAHistoryGraphObject);
	HisGraph->IsDraw=true;
	HisGraph->RectShow=true;
	items.AddTail(HisGraph);
	HisGraph->SetPageNum(CVgaMenuItem::PAGEALL);
}

void CVgaMenu::AddDigitalInput(CXmlElement * e)
{
	CVgaDigitalInput * DigitalInput = new CVgaDigitalInput(e);
	if(DigitalInput)
	{
		DigitalInput->PSType = VGA_DIGITALINPUT;		
		DigitalInput->SetType(VGA_DIGITALINPUT);
		items.AddTail(DigitalInput);
	}

}