/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitCondition.cpp_v   1.7   09 Jul 2014 06:43:40   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitCondition.cpp_v  $
 * 
 *    Rev 1.7   09 Jul 2014 06:43:40   akaushal
 * Added new function EvaluateChangeCond() .
 * 
 *    Rev 1.6   09 Jun 2014 11:36:06   rjamloki
 * initialized variables in constructor.
 * 
 *    Rev 1.5   20 May 2014 10:52:20   rjamloki
 * Macro to disable printf.
 * 
 *    Rev 1.4   07 May 2014 13:18:24   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.3   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     05 Mar 2014 14:13:12 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.1     03 Jan 2014 09:04:44 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "BitCondition.h"
#include "Variable.h"
#include "VgaMenuItem.h"
#include "VgaMenu.h"
#include "VgaButton.h"

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
CBitCondition::CBitCondition()
{
	Mask1=0;
	Mask2=0;
	Cond1 = 0;
	Cond2 = 0;
	bitState = 0;
	bitValue = 0;
	CaseValue = 0;
}

CBitCondition::~CBitCondition()
{

}
bool CBitCondition::EvaluateChangeCond(CVgaMenuItem *) const 
{
	return true;
}

/*************************************************************************************/
/*                                                                                   */
/*Function to check Bitvariables conditions like weld mode & VGA,DEPO conditions. 
/*  							
/*************************************************************************************/

bool CBitCondition::Evaluate(CVgaMenuItem *item) const
{
	bool ret=true;
	switch(CaseValue)
	{
	case 0:
		{
			/*Checking VGA,DEPO condition */
			/*if(bitState)
			{
			ret = (varvalue & bitValue) ? false : true;
			}
			else
			{
			ret = (varvalue & bitValue) ? true : false;
			}*/
			if ((Mask1!=0)  && ((Mask1 & Cond1)!= (CChildView::HWconfiguration & Mask1)))
				ret = false;

			if ((Mask2!=0)  && ((Mask2 & Cond2)!= (CChildView::SWconfiguration & Mask2)))
				ret = false;


		}
		break;
	case 1:
		{  
			/*checking Weld mode */
			switch((item->GetType()))
			{
			case CVgaMenu::VGA_Button_OBJECT:
				{
					CVgaButton *ptr=(CVgaButton *)item;
					ptr->ModeSet=bitValue;
					// printf("\n EnumValue in vgabu=%d",EnumValue);
				}
				break;
			}
			if((CChildView::WeldMode != (bitValue & CChildView::WeldMode)) &&
				(bitValue != 0xFF))
			{
				ret=false;
			}
			else
			{
				ret=true;
			}

		}
		break;
	default:
		break;
	}
	return ret;
}
