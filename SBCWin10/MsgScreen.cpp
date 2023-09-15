/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MsgScreen.cpp_v   1.6   20 May 2014 11:00:30   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/MsgScreen.cpp_v  $
 * 
 *    Rev 1.6   20 May 2014 11:00:30   rjamloki
 * Macro to disable printf. 
 * 
 *    Rev 1.5   07 May 2014 13:18:38   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.4   28 Mar 2014 14:33:04   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:22 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     18 Dec 2013 10:00:30 rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.0     03 Apr 2013 10:09:50 amaurya
 * Initial Revision.
 */
#include "stdafx.h"
#include "VGA.h"
#include "MsgScreen.h"

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


/****************************************************************************/
/*                                                                          */
/*  This function creates a CVGAMsgScreen object When any CVGAMsgScreen     */
/*  type object is found in  menu/submenu item list							*/
/*																		    */ 
/****************************************************************************/
CMsgScreen::CMsgScreen(CXmlElement * e)
{
	//Back color for Message Window.
	FillColor=_ttoi(e->GetAttribute("FillColor"));
	ResponseType=_ttoi(e->GetAttribute("Response"));
	RectShow=1;

	/*Storing Co-ordinated for message window*/
	X1_CoOrdinate = _ttoi(e->GetAttribute("X1"));
	Y1_CoOrdinate = _ttoi(e->GetAttribute("Y1"));
	X2_CoOrdinate = _ttoi(e->GetAttribute("X2"));
	Y2_CoOrdinate = _ttoi(e->GetAttribute("Y2"));

	/*Storing Duration to Display message screen.*/
	Time = _ttoi(e->GetAttribute("Time"));

	//Message text font.
	TextFont = _ttoi(e->GetAttribute("TextFont"));
	//Message text Color.
	TextColor =_ttoi(e->GetAttribute("TextColor"));

	/*Storing Text for message screen.*/
	MsgLine1ID=e->GetAttribute("textID1");
	MsgLine1 = CVgaMenuItem ::LinearSearch(MsgLine1ID);//First line Text.
	text=MsgLine1;
	MsgLine1.TrimRight();
	MsgLine1.TrimLeft();

	MsgLine2ID=e->GetAttribute("textID2");
	MsgLine2 = CVgaMenuItem ::LinearSearch(MsgLine2ID);//Second Line Text.
	MsgLine2.TrimRight();
	MsgLine2.TrimLeft();

	MsgLine3ID=e->GetAttribute("textID3");
	MsgLine3 = CVgaMenuItem ::LinearSearch(MsgLine3ID);//Third Line Text.
	submenu= e->GetAttribute("submenu");
	menunak= e->GetAttribute("menunak");
	MsgLine3.TrimRight();
	MsgLine3.TrimLeft();

	/*Chacking for empty Text line*/
	for(int i=0;i<2;i++)
	{
		if(MsgLine3=="\0")
		{
			MsgLine3=MsgLine2;
			MsgLine2=MsgLine1;
			MsgLine1="\0";
		}
	}
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

CMsgScreen::~CMsgScreen()
{

}


/**********************************************************************************/
/*                                                                                */
/*  This function Draws a CVGAMsgScreen object When any CVGAMsgScreen type object */
/*  is found in menu/submenu item list for current page .						  */
/*																		 		  */
/**********************************************************************************/
void CMsgScreen::Draw(CDC *pDC)
{
	CChildView::DisableFlag=true;
	rect=CRect(X1_CoOrdinate,Y1_CoOrdinate,X2_CoOrdinate,Y2_CoOrdinate);

	/*Drawing Message Rectangle in specified color*/
	DrawRect(pDC, Black, CRect(X1_CoOrdinate-1,
		Y1_CoOrdinate-1,
		X2_CoOrdinate+1,
		Y2_CoOrdinate+1));
	DrawRect(pDC, FillColor, CRect(X1_CoOrdinate,
		Y1_CoOrdinate,
		X2_CoOrdinate,
		Y2_CoOrdinate));

	/*Drawing Message Text*/
	if(CChildView::thisPtr->StringDebugFlag)
	{
		DrawText(pDC, Bigfont,TextColor , CRect(X1_CoOrdinate,
			Y1_CoOrdinate+40,	
			X2_CoOrdinate,
			Y1_CoOrdinate+70), MsgLine1ID + MsgLine1,true);
		DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
			Y1_CoOrdinate+70,	
			X2_CoOrdinate,
			Y1_CoOrdinate+100), MsgLine2ID + MsgLine2,true);
		DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
			Y1_CoOrdinate+100,	
			X2_CoOrdinate,
			Y1_CoOrdinate+130), MsgLine3ID + MsgLine3,true);
	}
	else
	{
		DrawText(pDC, Bigfont,TextColor , CRect(X1_CoOrdinate,
			Y1_CoOrdinate+40,	
			X2_CoOrdinate,
			Y1_CoOrdinate+70), MsgLine1,true);
		DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
			Y1_CoOrdinate+70,	
			X2_CoOrdinate,
			Y1_CoOrdinate+100), MsgLine2,true);
		DrawText(pDC, Bigfont, TextColor, CRect(X1_CoOrdinate,
			Y1_CoOrdinate+100,	
			X2_CoOrdinate,
			Y1_CoOrdinate+130), MsgLine3,true);
	}

	if(Time != 0)//if time is not equal to zero then initialise timer 4.
	{
		//printf("\n InitialiseTimer");
		CChildView::InitialiseTimer(MessageScreenTimer,Time); 
	}

	/*If time is zero but IsNewScreenPointer is true then also 
	initialise timer 4.(Actuator Cold Start).*/
	/*else if((Time == 0)&&(CChildView::IsNewScreenPointer))
	{
	CChildView::InitialiseTimer(MessageScreenTimer,0);
	CChildView::ActColdStartFlag =true;
	}*/
}

bool CMsgScreen::MouseClick(const CPoint &p, CChildView *view)
{
	return false;
}
