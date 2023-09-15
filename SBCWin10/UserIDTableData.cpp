/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTableData.cpp_v   1.12   16 Apr 2015 06:03:02   sesharma  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserIDTableData.cpp_v  $
 * 
 *    Rev 1.12   16 Apr 2015 06:03:02   sesharma
 * Coverity fix 11617.
 * 
 *    Rev 1.11   11 Dec 2014 06:51:16   RJamloki
 * CUserIDTableData() constructor changed to read text from Main.gui.
 * 
 *    Rev 1.10   28 Nov 2014 08:33:02   rjamloki
 * Function headers added
 * 
 *    Rev 1.9   26 Sep 2014 09:26:40   rjamloki
 * GetUserLevelStr fix for User level Supervisor
 * 
 *    Rev 1.8   25 Sep 2014 12:09:58   AnPawar
 * GetUserLvlStr() function added
 * 
 *    Rev 1.7   18 Aug 2014 07:59:56   rjamloki
 * User name removed
 * 
 *    Rev 1.6   09 Jun 2014 11:58:18   rjamloki
 * Variable initialization in constructor
 * 
 *    Rev 1.5   27 May 2014 06:45:04   amaurya
 * Display function changes
 * 
 *    Rev 1.4   21 Apr 2014 13:49:16   akaushal
 * Modified the constructor and draw table function.
 * 
 *    Rev 1.3   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.2     07 Mar 2014 11:15:38 rjamloki   
 * Modify User Changes.
 *
 *    Rev 1.1     06 Mar 2014 11:30:44 rjamloki   
 * Add new User ID function
 *
 *    Rev 1.0     05 Mar 2014 14:43:18 rjamloki      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "UserIDTableData.h"
#include "VgaButton.h"
#include "UserID.h"
#include "UserIDTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ParamRect_Gap 170

/** @brief CUserIDTableData::CUserIDTableData
*
*  Constructor function of class UserIDTableData.
*  This gives the initial values to userIdData structure.
*
*  @param pointer of struct UserIDStruct.
*  @return void.
*/
CUserIDTableData::CUserIDTableData(UserIDStruct *&data)
{
	userIdData.IsFirstTimeLogin = false;
	Lang_Index = 0;
	TextColour = Black;
	char timeBuff[32];
	Parameter_Value = new CString[CUserIDTable::thisPtr->TotalColoumn]; 
	strcpy((char*)userIdData.UserId, (char*)(data->UserId));
	strcpy((char*)userIdData.Password, (char*)(data->Password));
	userIdData.UserLevel = (enum UserLvl)ntohl(data->UserLevel);
	userIdData.Status = (enum ActiveStatus)ntohl(data->Status);
	userIdData.PassExpTime = ntohl(data->PassExpTime);
	userIdData.UnSuccessFullAttempts = 0;//Coverity 11617
	//date and time
	userIdData.CreateModifyTime.Years = data->CreateModifyTime.Years;
	userIdData.CreateModifyTime.Century_Month = data->CreateModifyTime.Century_Month;
	userIdData.CreateModifyTime.Day = data->CreateModifyTime.Day;
	userIdData.CreateModifyTime.Hour = data->CreateModifyTime.Hour;
	userIdData.CreateModifyTime.Minute = data->CreateModifyTime.Minute;
	userIdData.CreateModifyTime.Second = data->CreateModifyTime.Second;	
	Parameter_Value[0] = CString(userIdData.UserId);
	GetRTCDate(&(userIdData.CreateModifyTime), timeBuff);
	Parameter_Value[1] = CString(timeBuff);
	GetRTCTime(&(userIdData.CreateModifyTime), timeBuff);
	Parameter_Value[1] = Parameter_Value[1] +","+CString(timeBuff);//date and time is one string on screen

	if(userIdData.Status == Enabled)
		Parameter_Value[2] = CVgaMenuItem::LinearSearch(XSTR(ENABLED_STR_ID));
	else
		Parameter_Value[2] = CVgaMenuItem::LinearSearch(XSTR(DISABLED_STR_ID));

	Parameter_Value[3] = GetUserLvlStr(userIdData.UserLevel);
}

CUserIDTableData::~CUserIDTableData()
{
	delete[] Parameter_Value;
}

/* This is the draw function for CUserIDTableData class*/
void CUserIDTableData::Draw(CDC *pDC)
{

}

/** @brief CUserIDTableData::DrawTableData
*
*  This function is called from the function CUserIDTable::CreatePDF()
*  and CUserIDTableData::CUserIDTableData() functions
*
*  @param user level.
*  @return CString user string.
*/
CString CUserIDTableData::GetUserLvlStr(int level)
{
	CString str = "";
	switch(level)
	{
	case CUserIDTableData::OPERATOR: 
		str = "Operator"; 
		break;
	case CUserIDTableData::TECHNICIAN: 
		str = "Technician"; 
		break; 
	case CUserIDTableData::SUPERVISOR: 
		str = "Supervisor"; 
		break; 
	case CUserIDTableData::EXECUTIVE: 
		str = "Executive"; 
		break; 
	case CUserIDTableData::MAINTENANCE:
		str = "Maintenance"; 
		break; 
	case CUserIDTableData::BRANSON:
		str = "Branson"; 
		break; 
	case CUserIDTableData::NOLEVEL:
		str = "NOLEVEL"; 
		break; 
	default: 
		break; 
	}
	return str;
}

/** @brief CUserIDTableData::DrawTableData
*
*  This function draws the Alarm Log when Power supply history is drawn.
*
*  @param pointer to current device context.
*  @param leftmost parameter number.
*  @param line number.
*  @return void.
*/
void CUserIDTableData::DrawTableData(CDC *pDC,int LeftMostParameter, int LineNo)
{
	CRect ParamValueRect;

	int ColumnNo=0;
	ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Gap),
							  (LINE_GAP*(LineNo+3)),
							  (HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Gap),
							  (LINE_GAP*(LineNo+4)));

	CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[0],false);
	ColumnNo++;

	for (int Index = LeftMostParameter; Index < 4 ; Index++)
	{
		ParamValueRect =CRect((HISTORY_TBL_START_X + ColumnNo * ParamRect_Gap),
							  (LINE_GAP*(LineNo+3)),
							  (HISTORY_TBL_START_X + (ColumnNo+1) * ParamRect_Gap),
							  (LINE_GAP*(LineNo+4)));

		CVgaMenuItem::DrawText(pDC, SmallFont, TextColour, ParamValueRect, Parameter_Value[Index],false);
		ColumnNo++;

	}
}

/** @brief CUserIDTableData::MouseClick
*
*  Function executes when mouse click happens on UserIDTableData
*
*  @param reference of CPoint variable.
*  @param pointer to CChildView variable view.
*  @return bool.
*/
bool CUserIDTableData::MouseClick(const CPoint &p, CChildView *view)
{
	return true;
}