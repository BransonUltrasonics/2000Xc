/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ListBox.cpp_v   1.15   02 Jan 2015 04:59:44   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/ListBox.cpp_v  $
 * 
 *    Rev 1.15   02 Jan 2015 04:59:44   rjamloki
 * changes to support preset copy all functionality
 * 
 *    Rev 1.14   11 Dec 2014 06:50:22   RJamloki
 * CListBoxObject::Draw() changed to initialize CurrentPresetName to NULL ,if the selected preset number is not valid.
 * 
 *    Rev 1.13   20 Oct 2014 05:46:06   RJamloki
 * Macro MAX_PRESET_POSSIBLE replaced by variable  Max_Preset_Possible to display 16 presets in control level D
 * 
 *    Rev 1.12   01 Oct 2014 10:50:22   AnPawar
 * CListBoxObject::Draw() function changed.
 * 
 *    Rev 1.11   26 Sep 2014 10:40:56   rjamloki
 * changes for preset name strings
 * 
 *    Rev 1.10   02 Sep 2014 03:27:18   rjamloki
 *  Added GlobalPresetSelection variable to keep the selected preset   number from menu
 * 
 *    Rev 1.9   09 Jul 2014 06:59:00   akaushal
 * CListBoxObject() function changed.
 * 
 *    Rev 1.8   09 Jun 2014 11:48:56   rjamloki
 * Variable initialization in constructor.    
 * 
 *    Rev 1.7   20 May 2014 10:59:30   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.6   07 May 2014 13:18:26   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.5   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.4     05 Mar 2014 14:13:20 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:04:58 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:30 rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:24 amaurya
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:48 amaurya
 * Initial Revision.
*/
#include "stdafx.h"
#include "SBC.h"
#include "ListBox.h"
#include "XmlElement.h"
#include "Variable.h"
#include "Toggle.h"

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

CString CListBoxObject::CurrentPresetName;
CString CListBoxObject::CurrentSequencePresetName;
bool CListBoxObject::SequencingScreen=false;
extern int GlobalPresetSelection;

CListBoxObject::CListBoxObject(CXmlElement * e)
{
	ID = 0;
	CurrentRunningSequencePreset = 0;
	ListBox_Color = _ttoi(e->GetAttribute("Color"));//Fillcolor for list box rectangle.
	/*Storing Co-ordinates for list box.*/
	X1_CoOrdinate =  _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate =  _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate =  _ttoi(e->GetAttribute("Y2"));

	TotalText = _ttoi(e->GetAttribute("TotalText"));//Number of text to be display.

	ListBoxText.SetSize(TotalText+1);
	PresetInfoText.SetSize (TotalText);
	Type=_ttoi(e->GetAttribute("type"));
	MaxPreset=_ttoi(e->GetAttribute("MaxPresetDisplay")); 
	if(Type==PRESETINFOSCREEN)
	{
		PresetInfoText[0]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID1"));
		PresetInfoText[1]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID2"));
		PresetInfoText[2]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID3"));
		PresetInfoText[3]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID4"));
		PresetInfoText[4]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID5"));
		PresetInfoText[5]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID6"));		
		PresetInfoText[6]=CVgaMenuItem ::LinearSearch(e->GetAttribute("StrID7"));		
	}
	RectShow=false;
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
	rect = CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,X2_CoOrdinate+1,Y2_CoOrdinate+1);

}

CListBoxObject::~CListBoxObject()
{
	//	delete []ListBoxText;
	if(ListBoxText.GetSize()>0)
		ListBoxText.RemoveAll();
	if(PresetInfoText.GetSize()>0)
		PresetInfoText.RemoveAll();
	SequencingScreen=false;
}

/**********************************************************************************/
/*                                                                                */ 
/*  This function Draws a CVGAListBox object When any CVGAListBox type object     */
/*  is found in menu/submenu item list for current page .						  */
/*																				  */
/**********************************************************************************/
void CListBoxObject::Draw(CDC *pDC)
{

	/*Draw list box rectangle with list box color*/
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,Y1_CoOrdinate-1,
		X2_CoOrdinate+1,Y2_CoOrdinate+1));
	DrawRect(pDC, ListBox_Color, CRect(X1_CoOrdinate,Y1_CoOrdinate,
		X2_CoOrdinate,Y2_CoOrdinate));

	int Y_CoOrdinate = Y1_CoOrdinate;
	//	switch(ID)
	//	{
	//	case  VGA_PRESETNAME:
	{
		int j=0,MaxPresetDisplay=0; 
		MaxPresetDisplay=MaxPreset;
		//  int ViewUSBPreset;
		/*if(Type==1)
		MaxPresetDisplay=MAX_PRESETS_DISPLAYED;
		else if(Type==0)
		{
		MaxPresetDisplay =  TotalText;
		}
		else if(Type==2)
		{
		MaxPresetDisplay=MAX_PRESETS_DISPLAYED-1;
		}
		if((SequencingScreen)&&(Type==1))
		MaxPresetDisplay-=1;//Draw only 10 presets on Sequencing screen.*/
		if(Type==PRESETSCREEN)
		{
			//printf("in CListBoxObject::Draw , Type==PRESETSCREEN , CChildView::CurrentPresetNum =%d \n",CChildView::CurrentPresetNum);
			if(CChildView::CurrentPresetNum >MaxPresetDisplay)
				j = 0;
		}
		else if(Type==SEQUENCESCREEN)
		{
			if(CChildView::CurrentSequencePreset >10)//(MAX_PRESETS_DISPLAYED-1)
				j = (CChildView::CurrentSequencePreset -10);//MAX_PRESETS_DISPLAYED-1
		}
		else if(Type==USBPRESETSCREEN)
		{
			if((CChildView::SelectedUSBPreset==0)&&(CChildView::USBPresetNames.GetCount()>0))
				CChildView::SelectedUSBPreset=1;
			if(CChildView::SelectedUSBPreset >MaxPresetDisplay)
				j = CChildView::SelectedUSBPreset -MaxPresetDisplay;
			// ViewUSBPreset = MaxPresetDisplay;
			if(CChildView::TotalUSBPreset<MaxPresetDisplay)
				MaxPresetDisplay = CChildView::TotalUSBPreset;
		}
		else if(Type==POWERPRESETSCREEN)
		{
			if(CChildView::SelectedPowerPreset >MaxPresetDisplay)
				j = 0;
		}

		for(int i=0;i<MaxPresetDisplay;i++)
		{
			/*Draw green background and "<"	mark on current Preset.*/	
			//printf(" CListBoxObject::Draw i=%d j=%d \n",i,j);
			if((CChildView::CurrentPresetNum == (j+1))&&(Type==PRESETSCREEN))
			{
				//Drawing HighLight Background.
				DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
					Y_CoOrdinate,
					X2_CoOrdinate,
					Y_CoOrdinate+31));
				
				CurrentPresetName = ListBoxText[j];			
				if(CurrentPresetName.Find(L" ", 0) != -1)
                    CurrentPresetName.Delete(0, CurrentPresetName.Find(L" ", 0));//The name of presets in listbox are saved as Preset number a space and preset name
            	else
               		CurrentPresetName = "";
				
			}
			else if((CChildView::CurrentSequencePreset == (j+1))&&(Type==SEQUENCESCREEN))//&&(CVfdToggle::SequencingON==true))
			{
				//Drawing Background on Current Selected Preset.
				DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate+15,
					Y_CoOrdinate,
					X2_CoOrdinate-5,
					Y_CoOrdinate+31));
				CurrentSequencePresetName = ListBoxText[j];
				CurrentSequencePresetName.Delete(0,CurrentSequencePresetName.Find(L".",0));
			}
			else if((CChildView::SelectedPowerPreset == (j+1))&&(Type==POWERPRESETSCREEN))
			{
				//Drawing HighLight Background.
				DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
					Y_CoOrdinate,
					X2_CoOrdinate,
					Y_CoOrdinate+31));
			}
			else if((CChildView::SelectedUSBPreset == (j+1))&&(Type==USBPRESETSCREEN))
			{
				DrawRect(pDC, CChildView::Highlight_Color, CRect(X1_CoOrdinate,
					Y_CoOrdinate,
					X2_CoOrdinate,
					Y_CoOrdinate+31));
			}
			//Drawing "<" mark on current Running preset.
			if(Type==SEQUENCESCREEN)
			{
				if(CurrentRunningSequencePreset/*CChildView::CurrentSequencePreset*/ == (j+1)&&(CToggle::SequencingON))
					DrawText(pDC, SmallFont, CChildView::TextColor,CRect(X1_CoOrdinate,
					Y_CoOrdinate,	
					X1_CoOrdinate+10,
					Y_CoOrdinate+31), " > ",false);
			}
			if(Type==USBPRESETSCREEN)
			{
				char Number[8] ; //to keep preset more than 16
				sprintf(Number,"%d  ",j+1);
				CString Name="";
				if(CChildView::USBPresetNames.GetCount()>0)
				{
					//   printf("\n name");
					Name = Number+ CChildView::USBPresetNames.GetAt(CChildView::USBPresetNames.FindIndex(j));
					DrawText(pDC, SmallFont, CChildView::TextColor, 
						CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),Name,false);
				}
			}
			else
			{
				DrawText(pDC, SmallFont, CChildView::TextColor, 
					CRect(X1_CoOrdinate+20,Y_CoOrdinate,X1_CoOrdinate+196,Y_CoOrdinate+31),
					ListBoxText[j],false);
			}
			Y_CoOrdinate +=ListBox_OneLineHeight;
			j++;        
            if(((Type == PRESETSCREEN) || (Type == POWERPRESETSCREEN)) && ((GlobalPresetSelection + i + 1) > Max_Preset_Possible))
                 break;
           
		}
	}
}

bool CListBoxObject::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}