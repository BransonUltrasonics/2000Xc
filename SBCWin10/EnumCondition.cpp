/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumCondition.cpp_v   1.41   Jun 29 2017 14:16:02   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumCondition.cpp_v  $
 * 
 *    Rev 1.41   Jun 29 2017 14:16:02   RJamloki
 * Only No User can apply the automation mode, supervisor and executive can change settings weld setup and system configuration
 * 
 *    Rev 1.40   22 Dec 2015 11:03:32   RJamloki
 * Removing the prints from function AuthCheckClampFunc
 *
 *    Rev 1.39   21 Dec 2015 13:44:42   RJamloki
 * Remove global variable CChildView::OpAuthority and use local variable OpAuthorityCrt in function AuthCheckClampFunc
 *
 *    Rev 1.38   16 Dec 2015 15:39:04   RJamloki
 * Reset horn clamp alarm conditions
 *
 *    Rev 1.37   17 Nov 2015 17:17:28   RJamloki
 * Operator exception if Reset Horn Clamp Alarm is enabled and authority check
 *
 *    Rev 1.36   27 Mar 2015 11:04:06   amaurya
 * Barcode start check condition moved to ScreenKeypad.cpp,so that to reflect the barcode start change on screen immideately.
 *
 *    Rev 1.35   11 Mar 2015 09:26:14   amaurya
 * ReadUSBStoredPresetStrings() and GetUSBPresetScrn() changed to change the preset extension to .prst.
 *
 *    Rev 1.34   11 Feb 2015 06:18:20   amaurya
 * CheckForNameDisplay() and CheckForReasonDisplay() functions added to handle event display after alarm reset
 *
 *    Rev 1.33   02 Feb 2015 09:32:40   amaurya
 * EnumCondition.cpp CEnumCondition::Evaluate function change to get the correct power supply name
 *
 *    Rev 1.32   30 Jan 2015 08:13:40   amaurya
 * fix for creating folder name with powersupply name.
 *
 *    Rev 1.31   26 Jan 2015 13:31:16   rjamloki
 * Fix for save recall screen crashing some times.
 *
 *    Rev 1.30   02 Jan 2015 04:57:32   rjamloki
 * CopyPowerPresetToList() function changed to support copy all functionality
 *
 *    Rev 1.29   11 Dec 2014 06:50:06   RJamloki
 * DisableColdStartFlag() changed to call GetSystemVariable() after cold start.
 *
 *    Rev 1.28   28 Nov 2014 08:30:12   rjamloki
 * Warnings removed and WELD_HISTORY_SETUP_ID changed to WELD_HISTORY_SETUP_ENABLE_ID(Review Comments)
 *
 *    Rev 1.27   10 Nov 2014 02:49:04   rjamloki
 * CEnumCondition::Evaluate() changed to initialize presetbarcodestart variable.
 *
 *    Rev 1.26   20 Oct 2014 05:43:02   RJamloki
 * Evaluate function changed to store actuator serial number.
 *
 *    Rev 1.25   06 Oct 2014 03:23:24   rjamloki
 * GetNKBinDate() function removed
 *
 *    Rev 1.24   01 Oct 2014 10:48:22   AnPawar
 * DisableColdStartFlag() function changed.File path changed.
 *
 *    Rev 1.23   26 Sep 2014 09:24:26   rjamloki
 * Added title case in check func condition
 *
 *    Rev 1.22   25 Sep 2014 12:06:06   AnPawar
 * func check condition for variable type.
 *
 *    Rev 1.21   05 Sep 2014 12:12:00   rjamloki
 * Changes for level C.
 *
 *    Rev 1.20   05 Sep 2014 06:58:32   amaurya
 * Corrected the code that checks the automation condition.
 *
 *    Rev 1.19   02 Sep 2014 03:27:18   rjamloki
 *  Added GlobalPresetSelection variable to keep the selected preset   number from menu
 *
 *    Rev 1.18   18 Aug 2014 07:41:20   rjamloki
 * Renaming as per review comments. Fix for estop reset crash on view current setup.
 *
 *    Rev 1.17   28 Jul 2014 16:12:34   rjamloki
 * corrected deleting parameter id
 *
 *    Rev 1.16   28 Jul 2014 13:40:28   rjamloki
 * added function bool AuthCheckClampFunc(CVgaAlphanumeric *ptr)
 *
 *    Rev 1.15   22 Jul 2014 12:58:00   rjamloki
 * Fixed CheckOperatorFunc comment
 *
 *    Rev 1.14   22 Jul 2014 12:32:30   rjamloki
 * Added conditions for authority based message screen display.
 *
 *    Rev 1.13   09 Jul 2014 06:49:48   akaushal
 * Function EvaluateChangeCond(),CheckSupervisorFunc(),
 * CheckOperatorFunc() added.Evaluate() changed.
 *
 *    Rev 1.12   09 Jun 2014 11:39:42   rjamloki
 * Enum decration for datatypes.Coverity fixes.
 *
 *    Rev 1.11   27 May 2014 17:59:52   akaushal
 * Updated the Code to get HistorySetup info. at every updation of setup
 *
 *    Rev 1.10   20 May 2014 10:54:58   rjamloki
 * AuthCheckLoginFunc() and AuthCheckLogoutFunc() added.
 *
 *    Rev 1.9   07 May 2014 13:05:46   akaushal
 * infinite loops removed
 *
 *    Rev 1.8   23 Apr 2014 11:23:22   akaushal
 * functionality added to get default value from WC for Digital Buttons
 *
 *    Rev 1.7   21 Apr 2014 13:33:28   akaushal
 * Evaluate() function modified for Long Radio Values and diagnostic input status.
 *
 *    Rev 1.6   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.5     07 Mar 2014 11:15:36 rjamloki
 * Modify User Changes.
 *
 *    Rev 1.4     05 Mar 2014 14:13:16 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.3     03 Jan 2014 09:04:54  rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.2     18 Dec 2013 10:00:28  rjamloki
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:20 amaurya
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya
 * Initial Revision.
*/
#include "stdafx.h"
#include "EnumCondition.h"
#include "VGA.h"
#include "BottomHalf.h"
#include "Date.h"
#include "EnumVariable.h"
#include "HostCommand.h"
#include "ListBox.h"
#include "LocalChoice.h"
#include "RadioMenu.h"
#include "RunScreen.h"
#include "ScreenKeypad.h"
#include "Text.h"
#include "TextBox.h"
#include "Time.h"
#include "Toggle.h"
#include "Variable.h"
#include "VgaAlphanumeric.h"
#include "VgaBottomMenu.h"
#include "VgaButton.h"
#include "VgaChoice.h"
#include "VgaDigitalInput.h"
#include "VgaMenu.h"
#include "VgaMenuItem.h"
#include "VgaRadioButton.h"
#include "VgaSubMenu.h"
#include "VgaTitle.h"
#include "VgaVariable.h"
#include "VgaViewPreset.h"
#include "WeldingHistory.h"
#include "MsgScreen.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define VIEW_CURRSETUP_MENUID 259
#define WELD_HISTORY_SETUP_ENABLE_ID 259

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CChildView::PrintingSetup PrintSetup;
extern void SetGraphObjectMember(unsigned char * &data, int & length,CVgaDrawGraph * Graph);
extern int HistorySetUp;
extern int GlobalPresetSelection;
CEnumCondition::CEnumCondition()
{
        enumflagvalue = -1;
        EnumValue = -1;
        StringID = -1;
        CalibMenuIndex = -1;
        EnableCommand = false;
        CalibMenuIndexAED = -1;
        AEDActuatorValue = -1;
}

CEnumCondition::~CEnumCondition()
{

}
/*************************************************************************************/
/*                                                                                   */
/* Function to check Enumvariable conditions like Op_ChangeCond,Th_ChangeCond,       */
/* Su_ChangeCond, Ex_ChangeCond, Br_ChangeCond, NoAuth_ChangeCond                    */
/*************************************************************************************/

bool CEnumCondition::EvaluateChangeCond(CVgaMenuItem *item) const
{
        bool ret=true;
        switch(enumflagvalue)
        {
                case OPERATOR_CONDITION:        //Current User is Operator
                        if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_OPERATOR )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case TECHNICIAN_CONDITION:      //Current user is Tech
                if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_TECHNICIAN )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case SUPERVISOR_CONDITION:      //Current User is Supervisor
                if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_SUPERVISOR )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case EXECUTIVE_CONDITION:       //Current User is Executive
                if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_EXECUTIVE )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case BRANSON_CONDITION: //Current user is Branson
                if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_BRANSON )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case NOAUTHORITY_CONDITION:     // No user is logged in
                if((EnumValue != 0) && ((CChildView::UserChangeCond & 0xFF) == USER_NO_USER )){
                                if(((CChildView::UserChangeCond & 0xFFFFFF00) & (EnumValue << 8)) != (EnumValue << 8))
                                        ret = false;
                }
                break;
        case AUTOMATION_CONDITION:      // Automation Check
                if ((CChildView::Automation == true) && (EnumValue != 0) && (CChildView::Securitylevel >= USER_BRANSON) )
                {
                        if(EnumValue != 0xFF)
                                ret = false;
                }
                break;
        }
        return ret;
}
/*************************************************************************************/
/* Function to check Enumvariable conditions like ControlLevel,Actuator,Securitylevel*/
/* FunCheck and Enable Flag.                                                                                 */
/*************************************************************************************/
bool CEnumCondition::Evaluate(CVgaMenuItem *item) const
{
        switch(enumflagvalue)
        {
        case SECURITY_CONDITION:
                {
                        if(EnumValue> CChildView::Securitylevel)//Checking Securitylevel
                        {

                                return false;
                        }
                }
                break;
        case CONTROLLEVEL_CONDITION:
                {
                        if(CChildView::ControlLevel < EnumValue)//Checking ControlLevel
                        {
                                return false;
                        }
                }
                break;
        case ACTUATOR_CONDITION:
                {
                        if (!(EnumValue & CChildView::Actuator)) //Checking Actuator
                        {
                                return false;
                        }
                }
                break;
        case ENABLEID_CONDITION://Checking Enable Flag
                {
                        if(EnableCommand)
                        {
                                int length =3;
                                unsigned char data1[3];
                                union
                                {
                                        short i;
                                        char c[2];
                                } u;
                                u.i=StringID;
                                data1[1]=u.c[0];
                                data1[0]=u.c[1];

                                if(EnumValue!=0)
                                {
                                        if((EnumValue & CChildView::Actuator)==CChildView::Actuator)
                                                data1[2]=(char)CalibMenuIndexAED;
                                        else
                                                data1[2]=(char)CalibMenuIndex;
                                }
                                else
                                        data1[2]=(char)0;

                                unsigned char * data = (unsigned char *) &data1[0];
                                //Send Command if enable flag is true
                                CHostCommand * request = new CHostCommand(GetEptrVariable_FunId,data,length);
                                CHostCommand * response = app->SendUiHostCommand(request);
                                if(response)
                                {
                                        char ch=CHostCommand::AckNak();
                                        data = response->GetData();
                                        length = response->GetDataLength();

                                        if(ch==theApp.ACK)
                                        {
                                                int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                if(ID==!StringID)//If ID doesn't match, delete response
                                                {
                                                        delete response;
                                                        return false;
                                                }
                                                int Datatype=*data++;length--;
                                                bool Eptr;
                                                union
                                                {
                                                        bool i;
                                                        char c;
                                                } u;
                                                u.c = *data++;length--;
                                                Eptr=u.i;
                                                if(Eptr==false)
                                                {
                                                        delete response;
                                                        return false;
                                                }
                                                else
                                                {

                                                        switch(Datatype)
                                                        {
                                                        case NONE:// if nothing
                                                                {
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::VGA_Button_OBJECT:
                                                                                {
                                                                                        CVgaButton *ptr=(CVgaButton *)item;
                                                                                        ptr->EnumID=ID;

                                                                                }
                                                                                break;

                                                                        }

                                                                }
                                                                break;
                                                        case UINT8_TYPE:
                                                        case SINT8_TYPE:
                                                                {
                                                                        int OneByteValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);

                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::TEXT:
                                                                                {
                                                                                        CText *ptr=(CText *)item;
                                                                                        char TempArray[10];
                                                                                        CString Temp=_itoa(OneByteValue,TempArray,10);
                                                                                        ptr->text += Temp;
                                                                                        ptr->EnumID=ID;


                                                                                }
                                                                                break;
                                                                        case CVgaMenu::RADIOMENU:
                                                                                {
                                                                                        CRadioMenu *ptr=(CRadioMenu *)item;
                                                                                        ptr->VarText= " > ";
                                                                                        for(int i=0;i<=MAXRADIOITEMS;i++)
                                                                                        {
                                                                                                if(i==OneByteValue)
                                                                                                {
                                                                                                        ptr->RadioIndex = OneByteValue;
                                                                                                        ptr->EnumID=ID;
                                                                                                        ptr->VarText = ptr->RadioMenuStr[i];
                                                                                                }
                                                                                        }

                                                                                }
                                                                                break;

                                                                        }
                                                                }
                                                                break;
                                                        case UINT16_TYPE:
                                                        case SINT16_TYPE:
                                                                {
                                                                        int TwoByteValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::CHOICE:
                                                                                {
                                                                                        CVgaChoice *ptr1=(CVgaChoice *)item;
                                                                                        ptr1->EnumID=ID;
                                                                                        ptr1->Choice_value=TwoByteValue;
                                                                                        if(TwoByteValue)
                                                                                        {
                                                                                                ptr1->ChoiceText = "=" + ptr1->ChoiceText2;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr1->ChoiceText = "=" + ptr1->ChoiceText1;
                                                                                        }
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::TOGGLE:
                                                                                {
                                                                                        CToggle *ptr=(CToggle *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        if(TwoByteValue)
                                                                                        {
                                                                                                ptr->Toggle_Value=true;
                                                                                                ptr->Toggle_Text = "=" + ptr->Toggle_Text1 ;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr->Toggle_Value=false;
                                                                                                ptr->Toggle_Text = "=" + ptr->Toggle_Text2 ;
                                                                                        }

                                                                                }
                                                                                break;
                                                                        case CVgaMenu::VGA_DIGITALINPUT:
                                                                                {
                                                                                        CVgaDigitalInput *ptr=(CVgaDigitalInput *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        ptr->Activated = (TwoByteValue != 0);
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::RADIOMENU:
                                                                                {
                                                                                        CRadioMenu *ptr=(CRadioMenu *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        if( ptr->multiChoiceFlag == 1)
                                                                                        {
                                                                                                ptr->VarText= "";
                                                                                                ptr->multiChoiceValue = TwoByteValue;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr->VarText= " > ";
                                                                                                for(int i=0;i<=MAXRADIOITEMS;i++)
                                                                                                {
                                                                                                        if(i==TwoByteValue)
                                                                                                        {
                                                                                                                ptr->RadioIndex = TwoByteValue;
                                                                                                                ptr->VarText = ptr->RadioMenuStr[i];
                                                                                                        }
                                                                                                }
                                                                                        }
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::TEXT:
                                                                                {
                                                                                        char TempArray[10];
                                                                                        CText *ptr=(CText *)item;
                                                                                        CString Temp=_itoa(TwoByteValue,TempArray,10);
                                                                                        ptr->text += Temp;
                                                                                        ptr->EnumID=ID;
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::VGA_Button_OBJECT:
                                                                                {
                                                                                        char TempArray[10];
                                                                                        CVgaButton *ptr=(CVgaButton *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        CString Temp=_itoa(TwoByteValue,TempArray,10);

                                                                                        ptr->SubText= Temp;
                                                                                        if( ptr->DigitalOutput == true )
                                                                                                ptr->Activated = (TwoByteValue != 0);
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::SUBMENU:
                                                                                {
                                                        GlobalPresetSelection = TwoByteValue;
                                                                                        CChildView::CurrentPresetNum = 1;
                                                                                }
                                                                                break;
                                                                        case  CVgaMenu::TITLE:
                                                                                {
                                                                                        CChildView::CurrentSequencePreset =TwoByteValue;
                                                                                        if(CChildView::CurrentSequencePreset==0)
                                                                                                CChildView::CurrentSequencePreset=1;
                                                                                        CListBoxObject::SequencingScreen=true;
                                                                                }
                                                                                break;
                                                                        }
                                                                }
                                                                break;
                                                        case UINT32_TYPE:
                                                        case SINT32_TYPE:
                                                                {
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::VARIABLE:
                                                                                {
                                                                                        int ShowValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                        CVgaVariable *ptr=(CVgaVariable *)item;
                                                                                        if(ShowValue)
                                                                                        {
                                                                                                int DisableFlag=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                                                                int FourBytes=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                                                                                                char TempArray[LINESIZE+1]="                    ";
                                                                                                ptr->NewVal = FourBytes;
                                                                                                FourBytes = CScreenKeypad::ConvertInternalExternal( FourBytes,(CScreenKeypad::FORMAT)ptr->Format);
                                                                                                CString Temp;
                                                                                                bool Insertunitflag1=false;
                                                                                                int type=item->GetType();
                                                                                                ptr->Insertunitflag=false;

                                                                                                Insertunitflag1=CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,type);
                                                                                                ptr->Keypad_title = ptr->text ;
                                                                                                int Format1=ptr->Format;
                                                                                                if (ptr->Format == CScreenKeypad::ENERGY && (FourBytes >= 10000))
                                                                                                {
                                                                                                        FourBytes = CScreenKeypad::ConvertExternalInternal( FourBytes, CScreenKeypad::ENERGY );
                                                                                                        FourBytes = CScreenKeypad::ConvertInternalExternal( FourBytes, CScreenKeypad::ENERGYDIV10 );
                                                                                                        Format1 = CScreenKeypad::ENERGYDIV10;
                                                                                                }
                                                                                                bool b = (ptr->Unitshow != 0);
                                                                                                Temp=CScreenKeypad::FormatNumber(FourBytes,TempArray,(CScreenKeypad::FORMAT)Format1,b,ptr->Insertunitflag);
                                                                                                Temp.TrimLeft ();
                                                                                                Temp.TrimRight ();


                                                                                                if(ptr->TextType)
                                                                                                {
                                                                                                        ptr->Variable_Text="";
                                                                                                        ptr->text=CVgaMenuItem::GetString(data,length);
                                                                                                        ptr->Variable_Text+=Temp;
                                                                                                        ptr->Variable_Text+="W";
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        ptr->Variable_Text="";

                                                                                                        if ((ptr->Disable))
                                                                                                        {
                                                                                                                ptr->DisableFlag=DisableFlag;
                                                                                                                if(((DisableFlag & ptr->Bitmask) == ptr->Bitmask))
                                                                                                                {
                                                                                                                        ptr->Variable_Text= " = "+ CScreenKeypad::Str_Off;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                        ptr->Variable_Text= " = " +Temp;
                                                                                                                }

                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                                if(ptr->TextOnButton)
                                                                                                                {
                                                                                                                        ptr->Variable_Text = "" ;
                                                                                                                        ptr->text = Temp;
                                                                                                                }
                                                                                                                else
                                                                                                                        ptr->Variable_Text= " = " +Temp;

                                                                                                        }
                                                                                                }
                                                                                                ptr->EnumID=ID;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr->EnumID=ID;
                                                                                                int type=item->GetType();
                                                                                                ptr->Insertunitflag=false;
                                                                                                CScreenKeypad::InsertProperUnits(ptr,(CScreenKeypad::FORMAT)ptr->Format,type);
                                                                                                ptr->Variable_Text=" = "+CString("***");
                                                                                        }
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::RADIOMENU:
                                                                                {
                                                                                        data+=3;//we need the long value only
                                                                                        int LongValue=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                                                                                        CRadioMenu *ptr=(CRadioMenu *)item;

                                                                                        ptr->EnumID=ID;

                                                                                        if(ptr->EnumID == WELD_HISTORY_SETUP_ENABLE_ID)
                                                                                        {
                                                                                                HistorySetUp = LongValue;
                                                                                                printf("HistorySetUp = %d",HistorySetUp);
                                                                                        }
                                                                                        if( ptr->multiChoiceFlag == 1)
                                                                                        {
                                                                                                ptr->VarText= "";
                                                                                                ptr->multiChoiceValue = LongValue;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr->VarText= " > ";
                                                                                                for(int i=0;i<=MAXRADIOITEMS;i++)
                                                                                                {
                                                                                                        if(i==LongValue)
                                                                                                        {
                                                                                                                ptr->RadioIndex = LongValue;
                                                                                                                ptr->VarText = ptr->RadioMenuStr[i];
                                                                                                        }
                                                                                                }

                                                                                        }
                                                                                }
                                                                                break;
                                                                        }
                                                                }
                                                                break;
                                                        case BOOLEAN_TYPE:
                                                                {
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::TOGGLE:
                                                                                {
                                                                                        CToggle *ptr=(CToggle *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        bool metric;
                                                                                        union
                                                                                        {
                                                                                                bool i;
                                                                                                char c;
                                                                                        } u;
                                                                                        u.c = *data++;length--;
                                                                                        metric=u.i;
                                                                                        if(metric==true)
                                                                                        {
                                                                                                ptr->Toggle_Value=true;
                                                                                                ptr->Toggle_Text = " = "+ ptr->Toggle_Text1 ;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                ptr->Toggle_Value=false;
                                                                                                ptr->Toggle_Text = " = " + ptr->Toggle_Text2 ;
                                                                                        }

                                                                                }
                                                                                break;
                                                                        }

                                                                }
                                                                break;
                                                        case STR_TYPE:
                                                                {
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::TEXT:
                                                                                {
                                                                                        CText *ptr=(CText *)item;
                                                                                        CString str=CVgaMenuItem::GetString(data,length);
                                                                                        ptr->SubText = str;
                                                                                        ptr->EnumID=ID;
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::VGA_Button_OBJECT:
                                                                                {
                                                                                        CVgaButton *ptr=(CVgaButton *)item;

                                                                                        CString str=CVgaMenuItem::GetString(data,length);
                                                                                        ptr->EnumID=ID;
                                                                                        ptr->text = str;

                                                                                }
                                                                                break;
                                                                        case CVgaMenu::TITLE:
                                                                                {
                                                                                        CVgaTitle *ptr=(CVgaTitle *)item;
                                                                                        ptr->text=CVgaMenuItem::GetString(data,length);
                                                                                }
                                                                                break;
                                                                        }

                                                                }
                                                                break;
                                                        case ARR_TYPE:
                                                                {
                                                                        int DateArray[20];
                                                                        char TempArray[10];
                                                                        switch(item->GetType())
                                                                        {
                                                                        case CVgaMenu::DATE:
                                                                                {
                                                                                        CDate *ptr=(CDate *)item;
                                                                                        int lengthofData=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                        ptr->EnumID=ID;
                                                                                        if(ptr->RectShow)
                                                                                                ptr->Date_Text=" > ";
                                                                                        else
                                                                                                ptr->Date_Text=" ";
                                                                                        for(int j=0;j<lengthofData;j++)
                                                                                        {
                                                                                                if(j!=0)
                                                                                                {
                                                                                                        ptr->Date_Text+="/";
                                                                                                }
                                                                                                DateArray[j]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                                CString TempDay=_itoa(DateArray[j],TempArray,10);
                                                                                                if(TempDay.GetLength() ==1)
                                                                                                        TempDay = "0"+TempDay;
                                                                                                ptr->Date_Text+=TempDay;
                                                                                        }

                                                                                }
                                                                                break;
                                                                        case CVgaMenu::HHMM:
                                                                                {
                                                                                        CVgaTime *ptr=(CVgaTime *)item;
                                                                                        int lengthofData=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                        ptr->Time_Text=" > ";
                                                                                        ptr->EnumID=ID;
                                                                                        for(int i=0;i<lengthofData;i++)
                                                                                        {
                                                                                                if(i!=0)
                                                                                                {
                                                                                                        ptr->Time_Text +=":";
                                                                                                }
                                                                                                DateArray[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                                CString TempTime=_itoa(DateArray[i],TempArray,10);
                                                                                                if(TempTime.GetLength() ==1)
                                                                                                        TempTime = "0"+TempTime;
                                                                                                ptr->Time_Text+=TempTime;

                                                                                        }

                                                                                }
                                                                                break;
                                                                        case CVgaMenu::VGA_LISTBOX: //recallpreset
                                                                                {
                                                                                        PresetVerify = 0;
                                                                                        CListBoxObject *ptr=(CListBoxObject *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        if(length>1)
                                                                                        {
                                                                                                if(ptr->Type == PRESETINFOSCREEN)
                                                                                                {
                                                                                                        for(int i=0;i<(ptr->TotalText-4);i++)
                                                                                                        {
                                                                                                                ptr->ListBoxText[i]="";
                                                                                                                CString Str=" : "+ CVgaMenuItem::GetString(data, length);
                                                                                                                ptr->ListBoxText[i]=ptr->PresetInfoText[i] + Str;
                                                                                                                ptr->ListBoxText[i].TrimLeft();
                                                                                                                ptr->ListBoxText[i].TrimRight();

                                                                                                        }
                                                                                                        PresetVerify=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                                                                                                        if(PresetVerify)
                                                                                                        {
                                                                                                                CString Str= ptr->PresetInfoText[ptr->TotalText-3] ;
                                                                                                                ptr->ListBoxText[ptr->TotalText-4] = Str ;
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                                CString Str = ptr->PresetInfoText[ptr->TotalText-4];
                                                                                                                ptr->ListBoxText[ptr->TotalText-4] =  Str ;
                                                                                                        }
                                                                                                        ptr->ListBoxText[ptr->TotalText-4].TrimLeft();
                                                                                                        ptr->ListBoxText[ptr->TotalText-4].TrimRight();

                                                                                                        int PresetValidated=CVgaMenuItem::Convert_Char_To_Integer(data,length, 3);
                                                                                                        if( CChildView::ControlLevel >= LEVEL_C)
                                                                                                        {
                                                                                                                if(PresetValidated)
                                                                                                                {
                                                                                                                        CString Str= ptr->PresetInfoText[ptr->TotalText-1] ;
                                                                                                                        ptr->ListBoxText[ptr->TotalText-3] = Str ;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                        CString Str = ptr->PresetInfoText[ptr->TotalText-2];
                                                                                                                        ptr->ListBoxText[ptr->TotalText-3] =  Str;
                                                                                                                }
                                                                                                        }
                                                                                                        ptr->ListBoxText[ptr->TotalText-3].TrimLeft();
                                                                                                        ptr->ListBoxText[ptr->TotalText-3].TrimRight();
                                                                                                        ptr->ListBoxText [ptr->TotalText-1]="";
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        ptr->CurrentRunningSequencePreset=CChildView::CurrentSequencePreset ;
                                                                                                        for(int i=0;i<ptr->TotalText && length > 0;i++)
                                                                                                        {
                                                                                                                ptr->ListBoxText[i]=CVgaMenuItem::GetString(data, length);
                                                                                                                ptr->ListBoxText[i].TrimLeft();
                                                                                                                ptr->ListBoxText[i].TrimRight();
                                                                                                        }
                                                                                                }
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                for(int i=0;i<ptr->TotalText;i++)
                                                                                                {
                                                                                                        ptr->ListBoxText[i]="";
                                                                                                }
                                                                                        }
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::ALPHA:
                                                                                {
                                                                                        CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)item;
                                                                                        CString str = "";
                                                                                        ptr->EnumID=ID;
                                                                                        if(ptr->EnumID == POWERSUPPLYSERIALNOID)
                                                                                                str=CVgaMenuItem::GetPSString(data,length);
                                                                                        else
                                                                                                str=CVgaMenuItem::GetString(data,length);
                                                                                        ptr->Alpha_Text = "=" + str;
                                                                                        ptr->CurrentAlphaValue = str;
                                                                                }

                                                                                break;
                                                                        case CVgaMenu::TEXT:
                                                                                {
                                                                                        CText *ptr=(CText *)item;
                                                                                        CString str = "";
                                                                                        ptr->EnumID=ID;
                                                                                        if(ptr->EnumID == POWERSUPPLYSERIALNOID)
                                                                                                str=CVgaMenuItem::GetPSString(data,length);
                                                                                        else
                                                                                                str=CVgaMenuItem::GetString(data,length);

                                                                                        ptr->SubText = str;

                                                                                        if(ptr->EnumID == POWERSUPPLYSERIALNOID)
                                                                                        {
                                                                                           //str.TrimLeft();
                                               str.TrimRight();
                                                                               CChildView::thisPtr->PowerSupply = str;
                                                                                        }
                                                                                        if(ptr->EnumID == POWERSUPPLY_IP_ID)
                                                                                                CChildView::thisPtr->PowerSupplyIp = str;
                                                        if(ptr->EnumID == ACTSERIALNO_ID)
                                                                                                CChildView::thisPtr->ActSerialNumber = str;
                                                                                }
                                                                                break;
                                                                        case CVgaMenu::VGA_Button_OBJECT:
                                                                                {
                                                                                        CVgaButton *ptr=(CVgaButton *)item;
                                                                                        ptr->EnumID=ID;
                                                                                        ptr->SubText="";
                                                                                        CString str=CVgaMenuItem::GetString(data,length);
                                                                                        str.TrimLeft();
                                                                                        str.TrimRight();
                                                                                        ptr->SubText = " " + str;

                                                                                }
                                                                                break;
                                                                        }

                                                                }
                                                                break;
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                CChildView::thisPtr->ProcessNak(data,length,0,0);
                                        }
                                        delete response;
                                }
                                return true;
                        }
                        else
                        {
                                switch(item->GetType())
                                {
                                case CVgaMenu::VGABottomHalfObject:
                                        {
                                                CBottomHalf *ptr=(CBottomHalf *)item;
                                                ptr->EnumID = StringID;
                                        }
                                        break;
                                case CVgaMenu::VGA_Button_OBJECT:
                                        {
                                                CVgaButton *ptr=(CVgaButton *)item;
                                                ptr->EnumID=StringID;

                                        }
                                        break;
                                case CVgaMenu::CHOICE:
                                        {
                                                CLocalChoice *ptr=(CLocalChoice *)item;
                                                ptr->EnumID=StringID;
                                        }
                                        break;
                                default:
                                        item->EnumID =StringID;
                                }

                        }

                }
                break;
        case CHECKFUN_CONDITION://Checking for function
                {
                        switch(item->GetType())
                        {
                        case CVgaMenu::VGA_Button_OBJECT:
                                {
                                        CVgaButton *ptr=(CVgaButton *)item;
                                        void *pointer;
                                        bool (*rmn)(CVgaButton *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CVgaButton *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;
                        case CVgaMenu::CHOICE:
                                {
                                        CLocalChoice *ptr=(CLocalChoice *)item;
                                        void *pointer;
                                        bool (*rmn)(CLocalChoice *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CLocalChoice *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;

                                        case CVgaMenu::ALPHA:
                                {
                                        CVgaAlphanumeric *ptr=(CVgaAlphanumeric *)item;
                                        void *pointer;
                                        bool (*rmn)(CVgaAlphanumeric *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CVgaAlphanumeric *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;
                        case CVgaMenu::VGAMsgScrnObject:
                                {
                                        CMsgScreen *ptr=(CMsgScreen *)item;
                                        void *pointer;
                                        bool (*rmn)(CMsgScreen *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CMsgScreen *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;
                        case CVgaMenu::VARIABLE:
                                {
                                        CVgaVariable *ptr=(CVgaVariable *)item;
                                        void *pointer;
                                        bool (*rmn)(CVgaVariable *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CVgaVariable *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;
                        case CVgaMenu::TITLE:
                                {
                                        CVgaTitle *ptr=(CVgaTitle *)item;
                                        void *pointer;
                                        bool (*rmn)(CVgaTitle *);
                                        if(functionCall.Lookup(FunName,pointer))
                                        {
                                                rmn = (bool (*)(CVgaTitle *))pointer;
                                                return rmn(ptr);
                                        }
                                }
                                break;
                        }
                }
                break;
        case RUNSCREEN_CONDITION:
                {
                        switch(item->GetType())
                        {
                        case CVgaMenu::VGARUNSCREENOBJECT:
                                {
                                        CRunScreen *ptr=(CRunScreen *)item;
                                        int length =VARMAXMINLENGTH;
                                        unsigned char data1[2];
                                        union
                                        {
                                                short i;
                                                char c[2];
                                        } u;
                                        u.i= ptr->RunID ;
                                        data1[1]=u.c[0];
                                        data1[0]=u.c[1];

                                        unsigned char * data = (unsigned char *) &data1[0];
                                        //Send Command if enable flag is true
                                        CHostCommand * request = new CHostCommand(SetValue_FunID,data,length);
                                        CHostCommand * response = app->SendUiHostCommand(request);
                                        if(response)
                                        {
                                                char ch=CHostCommand::AckNak();
                                                data = response->GetData();
                                                length = response->GetDataLength();
                                                if(ch==theApp.ACK)
                                                {
                                                        ptr->Displayable_columns=*data++;length--;

                            if(ptr->Parameter_ID != NULL) { // If memory already exist delete it
                                delete[] ptr->Parameter_ID;
                                        ptr->Parameter_ID = NULL;
                                }
                                                        ptr->Parameter_ID=new int[ptr->Displayable_columns];
                                                        for(int param=0;param<ptr->Displayable_columns;param++) //Storing parameters ID.
                                                        {
                                                                ptr->Parameter_ID[param]=*data++;
                                                                length--;
                                                        }
                                                        ptr->ReceivedUniversalCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                                                        ptr->TotalCycles=*data++;//Numbers of cycle for which weld data is to be shown.
                                                        length--;

                                                        while(ptr->WeldDataList.GetCount()>0)
                                                                delete ptr->WeldDataList.RemoveHead();

                                                        for(int cycle =0;cycle<ptr->TotalCycles;cycle++)
                                                        {
                                                                CWeldingData * obj = new CWeldingData(data, length);
                                                                ptr->WeldDataList.AddTail(obj);
                                                        }

                                                }
                                                delete response;
                                                return true;
                                        }
                                }
                                break;
                        }
                }
                break;
        case BASICEXPERT_CONDITION:
                item->ExpertSet=EnumValue;
                if(EnumValue == 1)
                        printf("1");
                if(CChildView::BasicExpert == 0)
                        return true;
                if(CChildView::BasicExpert > EnumValue)//Checking Securitylevel
                {

                        return false;
                }
                break;
        case OPERATOR_CONDITION:
                break;
        case TECHNICIAN_CONDITION:
                break;
        case SUPERVISOR_CONDITION:
                break;
        case EXECUTIVE_CONDITION:
                break;
        case BRANSON_CONDITION:
                break;
        case NOAUTHORITY_CONDITION:
                break;
        case AUTOMATION_CONDITION:      // No user is logged in
                break;
        case ACCESS_CONDITION:
                item->AccessLevel=EnumValue;
                break;
        }
        return true;
}

bool RefreshCheck(CVgaButton *ptr)
{
        if(CChildView::thisPtr->AutoRefreshon)
        {
                ptr->IsDraw =false;
                ptr->RectShow =false;
                return false;
        }
        else
        {
                if(CChildView::thisPtr->AlarmCount)
                {
                        ptr->IsDraw =false;
                        ptr->RectShow =false;
                        return false;
                }
                else
                {
                        ptr->IsDraw=true;
                        ptr->RectShow =true;
                        return true;
                }

        }
}

bool ScanAOnOff(CLocalChoice *ptr)
{
        ptr->ChoiceText=" > ";
        if(CChildView::thisPtr->ScanA_On)
        {
                ptr->ChoiceText += ptr->ChoiceText2 ;
        }
        else
        {
                ptr->ChoiceText += ptr->ChoiceText1 ;
        }
        return true;
}

bool ScanBOnOff(CLocalChoice *ptr)
{
        ptr->ChoiceText=" > ";
        if(CChildView::thisPtr->ScanB_On)
        {
                ptr->ChoiceText +=ptr->ChoiceText2 ;
        }
        else
        {
                ptr->ChoiceText +=ptr->ChoiceText1 ;
        }
        return true;
}

bool ScanCOnOff(CLocalChoice *ptr)
{
        ptr->ChoiceText=" > ";
        if(CChildView::thisPtr->ScanC_On)
        {
                ptr->ChoiceText += ptr->ChoiceText2 ;
        }
        else
        {
                ptr->ChoiceText += ptr->ChoiceText1 ;
        }
        return true;
}


bool CurrentScanOnOff(CLocalChoice *ptr)
{
        ptr->ChoiceText=" > ";
        if(CChildView::thisPtr->CurrentScan_On)
        {
                ptr->ChoiceText +=ptr->ChoiceText2 ;
        }
        else
        {
                ptr->ChoiceText +=ptr->ChoiceText1 ;
        }
        return true;
}

bool AddPowerGraph(CVgaButton *ptr)
{
        CVgaMenu * menu;
        int i = 0;
        menu=theApp.MenuPointer;
        CVgaMenuItem *object;
        POSITION pos1=menu->items.GetHeadPosition();
        CChildView::thisPtr->ViewGraphWeldData=0;
        CVgaDrawGraph::GraphCount=0;
        while(theApp.GraphsDataList.GetCount()>0)
                theApp.GraphsDataList.RemoveHead();
        unsigned char RequestType = (char)(2);
        int length =2;
        unsigned char data1[2];
        data1[0]=(char)RequestType;
        data1[1]=(char)0;
        unsigned char * data = (unsigned char *) &data1[0];

        CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
        CHostCommand * response = app->SendUiHostCommand(request);
        if (response)
        {
                char ch=CHostCommand::AckNak();
                data = response->GetData();//Getting Data.
                length = response->GetDataLength();//Getting Length.
                if(ch==theApp.ACK)//If Ack.
                {               //store graph data
                        while ((pos1)&&(length>0))
                        {
                                object= menu->items.GetNext(pos1);
                                if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
                                {
                                        CVgaDrawGraph * ptr1 = (CVgaDrawGraph * )object;
                                        int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                                        if((ValueAfterParamID==ptr1->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                                        {

                                                ptr1->GraphData.graph_type=ValueAfterParamID;
                                                SetGraphObjectMember(data,length,ptr1);
                                                theApp.GraphsDataList.AddTail(ptr1);
                                        }
                                        else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr1->GraphType)
                                        {
                                                ptr1->GraphData.graph_type=ValueAfterParamID;
                                                for(i=0;i<20;i++)
                                                        ptr1->GraphData.SystemPressure[i]='\0';
                                                ptr1->AlreadyPrinted=false;
                                                ptr1->Lang_Index=0;//CChildView::Language_Index;
                                                ptr1->No_Graph_String=" ";
                                                ptr1->GraphCount++;
                                                ptr1->GraphData.GraphNum =ptr1->GraphCount;

                                                for( i=0;i<20;i++)
                                                        ptr1->GraphData.GRAPHTITLE[i]='\0';
                                                for( i=0;i<20;i++)
                                                        ptr1->GraphData.CycleCount[i]='\0';
                                                ptr1->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;//CVgaMenuItem ::LinearSearch(ptr->NoGraphID);
                                                theApp.GraphsDataList.AddTail(ptr1);
                                        }
                                        else
                                        {
                                                data-=CORDLENGTH;
                                                length+=CORDLENGTH;
                                        }
                                }
                        }
                }
                else
                        CChildView::thisPtr->ErrorBeep();
                delete response;
        }
        return true;
}

bool AddAvgPowerGraph(CVgaButton *ptr)
{
        if(theApp.GraphsDataList.GetCount())
                if((theApp.GraphsDataList.GetCount()==1)&& CChildView::thisPtr->PMCScreen)
                {
                        CVgaMenu * menu;
                        menu=theApp.MenuPointer;
                        CVgaMenuItem *object;
                        POSITION POSI=menu->items.GetHeadPosition();
                        int length =1;
                        unsigned char data1=(char)04;
                        unsigned char * data = (unsigned char *) &data1;

                        CHostCommand * request = new CHostCommand(PowerMatchCurve_FunctionId, data, length);
                        CHostCommand * response = app->SendUiHostCommand(request);
                        if (response)
                        {
                                char ch=CHostCommand::AckNak();
                                data = response->GetData();//Getting Data.
                                length = response->GetDataLength();//Getting Length.
                                if(ch==theApp.ACK)//If Ack.
                                {          //store graph data

                                        while ((POSI)&&(length>0))
                                        {
                                                object= menu->items.GetNext(POSI);
                                                if(object->GetType()==CVgaMenu::VGA_GRAPH_OBJECT)
                                                {
                                                        CVgaDrawGraph * ptr1 = (CVgaDrawGraph *)object;
                                                        int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                                                        if(ValueAfterParamID==NO_VALID_GRAPH)
                                                        {
                                                                delete response;
                                                                return true;
                                                        }
                                                        if(ValueAfterParamID==ptr1->GraphType)
                                                        {
                                                                ptr1->GraphData.graph_type=ValueAfterParamID;
                                                                int TempVar =*data++;
                                                                if(TempVar>0)
                                                                        CChildView::thisPtr->PMCDisable =true;
                                                                else
                                                                        CChildView::thisPtr->PMCDisable =false;
                                                                length--;
                                                                ptr1->PMCCycleCount=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                                int TimeCount =CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                                CChildView::thisPtr->LowerPMCLimit=*data++;
                                                                length--;
                                                                CChildView::thisPtr->UpperPMCLimit=*data++;
                                                                length--;
                                                                ptr1->GraphData.DataLength=0;

                                                                if(ptr1->PMCCycleCount !=0)
                                                                {
                                                                        short graphdatalength=0;
                                                                        for(short len=0;len<400;len++)
                                                                        {
                                                                                if(*data!=0xFF)
                                                                                {
                                                                                        ptr1->GraphData.graphdata[len]=(short)*data++;
                                                                                        graphdatalength++;
                                                                                }
                                                                                else
                                                                                        data++;
                                                                                length--;
                                                                        }
                                                                        ptr1->GraphData.DataLength=graphdatalength;


                                                                }
                                                                if(ptr1->GraphData.DataLength==0)
                                                                {
                                                                        CChildView::thisPtr->LowerPMCLimit=0;
                                                                        CChildView::thisPtr->UpperPMCLimit=0;

                                                                }
                                                                CChildView::thisPtr->PMCMaxVdata=*data++;

                                                                length--;length--;
                                                                ptr1->RecalculateAverageGraph(CChildView::thisPtr);
                                                                theApp.GraphsDataList.AddTail(ptr1);
                                                        }
                                                        else
                                                        {
                                                                data-=CORDLENGTH;
                                                                length+=CORDLENGTH;
                                                        }

                                                }
                                        }
                                }
                                else
                                {
                                        CChildView::thisPtr->ErrorBeep();
                                }
                                delete response;
                        }

                }
                return true;
}

bool ProcessAlarmMenu(CVgaButton *pointer)
{
        CVgaMenu * menu;
        menu=theApp.MenuPointer;
        CVgaMenuItem *object=0;
        bool show=false;
        while(theApp.GraphsDataList.GetCount()>0)
                theApp.GraphsDataList.RemoveHead();
        POSITION pos=menu->items.GetHeadPosition();
        while(pos)
        {
                object=menu->items.GetNext(pos);
                if((object->EnumID==-1)||(object->PSType==CVgaMenu::BottomMenu_Id))
                        object->IsDraw=true;
                else
                {
                        object->IsDraw=false;
                }
        }
        if(theApp.menuName!=CVgaBottomMenu::WeldResults_ID)
                CChildView::thisPtr->RunResultScreen=false;
        CHostCommand * request = new CHostCommand(GetAlarmSetupFlag, 0, 0);
        CHostCommand * response = app->SendUiHostCommand(request);

        if(response)
        {
                char ch=CHostCommand::AckNak();
                CChildView::thisPtr->IsAlarmScreen =true;
                CChildView::thisPtr->AlarmUpdateRequired=false;
                unsigned char *data = response->GetData();
                int length = response->GetDataLength();
                int AlarmBit=0,position=0,location=0;
                int Temprory=0,TitlePosition=0;

                if(ch==theApp.ACK)
                {
                        int NoOfFlags=CVgaMenuItem::Convert_Char_To_Integer(data,length,3);
                        int *FlagArray=new int[NoOfFlags];
                        TitlePosition=0;
                        bool SetupAlarmFlag=false;
                        for(int i=0;i<NoOfFlags;i++)
                        {
                                FlagArray[i]=CVgaMenuItem::Convert_Char_To_Integer(data,length,0);
                                AlarmBit=FlagArray[i];
                                for(int j=0;j<=31;j++)
                                {
                                        Temprory=AlarmBit%2;
                                        AlarmBit=(AlarmBit)/2;

                                        if(Temprory == 1)
                                        {
                                                location = position;
                                                POSITION pos=menu->items.GetHeadPosition();

                                                while(pos)
                                                {
                                                        object=menu->items.GetNext(pos);
                                                        if(object->GetType()==CVgaMenu::VGA_Button_OBJECT)
                                                        {
                                                                CVgaButton *ptr=(CVgaButton *)object;
                                                                if(location==ptr->EnumID)
                                                                {
                                                                        ptr->IsDraw=true;
                                                                        if(pointer==ptr)
                                                                                show=true;
                                                                        break;
                                                                }
                                                        }
                                                }

                                                if((i>=0)&&(i<SETUP_ALARM_END))
                                                {
                                                        TitlePosition=SETUP_ALARM;
                                                        SetupAlarmFlag=true;
                                                }
                                                else
                                                {
                                                        if(!SetupAlarmFlag)
                                                                TitlePosition=i-SETUP_ALARM_END;
                                                }
                                        }
                                        position++;
                                }
                        }

                        delete []FlagArray;
                        POSITION pos=menu->items.GetHeadPosition();
                        while(pos)
                        {
                                object=menu->items.GetNext(pos);
                                if(object->GetType()==CVgaMenu::TITLE)
                                {
                                        CVgaTitle *ptr=(CVgaTitle *)object;
                                        CString str=ptr->TitleArray[TitlePosition];
                                        ptr->text=ptr->TitleArray[TitlePosition];
                                        object->IsDraw=true;
                                        break;
                                }
                        }
                }
                delete response;
        }
        return show;
}

bool SendCommandForViewGraphs(CVgaButton *ptr)
{
        CVgaMenu * menu;
        int i = 0;
        menu=theApp.MenuPointer;
        CVgaMenuItem *object;
        POSITION pos1=menu->items.GetHeadPosition();
        CChildView::thisPtr->ViewGraphWeldData=0;
        CVgaDrawGraph::GraphCount=0;
        if(CChildView::thisPtr->AutoRefreshon)
        {
                CVgaDrawGraph::GraphCount=0;
                while(theApp.GraphsDataList.GetCount()>0)
                        theApp.GraphsDataList.RemoveHead();
                unsigned char RequestType = (char)(CChildView::thisPtr->GraphOneRequestValue +CChildView::thisPtr->GraphTwoRequestValue);
                int length =2;
                unsigned char data1[2];
                data1[0]=(char)RequestType;
                data1[1]=(char)0;
                unsigned char * data = (unsigned char *) &data1[0];

                CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
                CHostCommand * response = app->SendUiHostCommand(request);
                if (response)
                {
                        char ch=CHostCommand::AckNak();
                        data = response->GetData();//Getting Data.
                        length = response->GetDataLength();//Getting Length.
                        if(ch==theApp.ACK)//If Ack.
                        {               //store graph data
                                while ((pos1)&&(length>0))
                {
                                        object= menu->items.GetNext(pos1);
                                        if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
                                        {
                                                CVgaDrawGraph * ptr1 = (CVgaDrawGraph * )object;
                                                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                                                if((ValueAfterParamID==ptr1->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                                                {
                                                        ptr1->GraphData.graph_type=ValueAfterParamID;
                                                        SetGraphObjectMember(data,length,ptr1);
                                                        theApp.GraphsDataList.AddTail(ptr1);
                                                }
                                                else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr1->GraphType)
                                                {
                                                        ptr1->GraphData.graph_type=ValueAfterParamID;
                                                        for( i=0;i<20;i++)
                                                                ptr1->GraphData.SystemPressure[i]='\0';
                                                        ptr1->AlreadyPrinted=false;
                                                        ptr1->Lang_Index=0;
                                                        ptr1->No_Graph_String=" ";
                                                        ptr1->GraphCount++;
                                                        ptr1->GraphData.GraphNum =ptr1->GraphCount;

                                                        for( i=0;i<20;i++)
                                                                ptr1->GraphData.GRAPHTITLE[i]='\0';
                                                        for( i=0;i<20;i++)
                                                                ptr1->GraphData.CycleCount[i]='\0';
                                                        ptr1->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;
                                                        theApp.GraphsDataList.AddTail(ptr1);
                                                        break;
                                                }
                                                else
                                                {
                                                        data-=CORDLENGTH;
                                                        length+=CORDLENGTH;
                                                }
                                        }
                }
                                POSITION pos = theApp.GraphsDataList.GetHeadPosition();
                                while(pos)
                                {
                                        CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
                                        if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
                                                Graph->GraphData.GraphNum=1;
                                        else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
                                                Graph->GraphData.GraphNum=2;
                                        else
                                                Graph->GraphData.GraphNum=0;
                                }
                        }
                        else
                                CChildView::thisPtr->ErrorBeep();
                        delete response;
                }
                CChildView::thisPtr->Invalidate();
        }
        else
        {
                pos1=menu->items.GetHeadPosition();
                CVgaDrawGraph::GraphCount=0;
                while(theApp.GraphsDataList.GetCount()>0)
                        theApp.GraphsDataList.RemoveHead();
                unsigned char RequestType = (char)126;
                int length =2;
                int i = 0;
                unsigned char data1[2];
                data1[0]=(char)RequestType;
                data1[1]=(char)0;
                unsigned char * data = (unsigned char *) &data1[0];

                CHostCommand * request = new CHostCommand(GetWeldData_FunID, data, length);
                CHostCommand * response = app->SendUiHostCommand(request);
                if (response)
                {

                        char ch=CHostCommand::AckNak();
                        data = response->GetData();//Getting Data.
                        length = response->GetDataLength();//Getting Length.
                        if(ch==theApp.ACK)//If Ack.
                        {               //store graph data
                                CChildView::thisPtr->ViewGraphGlobalCount=CChildView::thisPtr->UniversalCount;
                                while ((pos1)&&(length>0))
                                {
                                        object= menu->items.GetNext(pos1);
                                        if(object->PSType==CVgaMenu::VGA_GRAPH_OBJECT)
                                        {
                                                CVgaDrawGraph * ptr2 = (CVgaDrawGraph *)object;
                                                int ValueAfterParamID=CVgaMenuItem::Convert_Char_To_Integer(data,length,CORDLENGTH);
                                                if((ValueAfterParamID==ptr2->GraphType)&&(ValueAfterParamID!=NO_VALID_GRAPH))
                                                {
                                                        ptr2->GraphData.graph_type=ValueAfterParamID;
                                                        SetGraphObjectMember(data,length,ptr2);
                                                        theApp.GraphsDataList.AddTail(ptr2);
                                                }
                                                else if(ValueAfterParamID==NO_VALID_GRAPH && ValueAfterParamID==ptr2->GraphType)
                                                {
                                                        ptr2->GraphData.graph_type=ValueAfterParamID;
                                                        for(i=0;i<20;i++)
                                                                ptr2->GraphData.SystemPressure[i]='\0';
                                                        ptr2->AlreadyPrinted=false;
                                                        ptr2->Lang_Index=0;
                                                        ptr2->No_Graph_String=" ";
                                                        ptr2->GraphCount++;
                                                        ptr2->GraphData.GraphNum =ptr2->GraphCount;
                                                        for( i=0;i<20;i++)
                                                                ptr2->GraphData.GRAPHTITLE[i]='\0';
                                                        for( i=0;i<20;i++)
                                                                ptr2->GraphData.CycleCount[i]='\0';
                                                        ptr2->No_Graph_String=CChildView::thisPtr->Str_NoValidGraph;
                                                        theApp.GraphsDataList.AddTail(ptr2);
                                                }
                                                else
                                                {
                                                        data-=CORDLENGTH;
                                                        length+=CORDLENGTH;
                                                }
                                        }
                                }
                                POSITION pos = theApp.GraphsDataList.GetHeadPosition();
                                while(pos)
                                {
                                        CVgaDrawGraph *Graph= theApp.GraphsDataList.GetNext(pos);
                                        if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphOneRequestValue)
                                                Graph->GraphData.GraphNum=1;
                                        else if(Graph->GraphData.GraphRequestValue==CChildView::thisPtr->GraphTwoRequestValue)
                                                Graph->GraphData.GraphNum=2;
                                        else
                                                Graph->GraphData.GraphNum=0;
                                }
            }
                        else
                                CChildView::thisPtr->ErrorBeep();
                        delete response;

                        /****************************/
                        unsigned char data1[CORDLENGTH];
                        data1[0]=(char)01;
                        data1[1]=(char)01;
                        int length=CORDLENGTH;
                        unsigned char * data = (unsigned char *) &data1[0];
                        request = new CHostCommand(GetWeldData_FunID, data, length);
                        response= app->SendUiHostCommand(request);
                        if(response)
                        {
                                char ch=CHostCommand::AckNak();
                                if(ch==theApp.ACK)
                                {
                                        CChildView::thisPtr->ViewGraphWeldData=response;
                                }
                else
                        delete response;
                        }
                }
                CChildView::thisPtr->Invalidate();
        }
        return true;
}


bool ProcessAlarmExit(CVgaButton *ptr)
{
        ptr->IsDraw=true;
        ptr->SetType(CVgaMenu::VGA_VGAEXITBUTTON);
        ptr->PSType=CVgaMenu::VGA_Button_OBJECT;
        return true;
}


bool GetCurrentPresetScrn(CVgaButton *ptr)
{
        char TempArray[10];
        CString Temp=_itoa(ptr->EnumID,TempArray,10);
        Temp=CVgaMenuItem ::LinearSearch(Temp);
        CChildView::thisPtr->ShowMessageScreen(Temp);
        CVgaMenu * menu;


        CVgaMenu * mainMenuPtr;
        CVgaMenu * viewSetupPtr;
        int page=1;

        //main menu lookup
        CString ViewSetupID = XSTR(VIEW_CURRSETUP_MENUID);
        if (!theApp.menus.Lookup(CVgaBottomMenu::mainMenuID, mainMenuPtr))
        {
                return false;
        }

        if (theApp.menus.Lookup(ViewSetupID, viewSetupPtr))
        {
                //related to tail menu
                CChildView::thisPtr->menusname.AddTail(CVgaBottomMenu::mainMenuID);
                CChildView::thisPtr->menus.AddTail(page);
                CChildView::thisPtr->menupointers.AddTail(mainMenuPtr);
                //assign to current
                page_no=1;
                theApp.menuName=ViewSetupID;
                theApp.MenuPointer=viewSetupPtr;
        }

        menu=theApp.MenuPointer;
        CVgaMenuItem *object=0;
        CVgaMenuItem *ViewPresetobject=0;
        POSITION pos=menu->items.GetHeadPosition();
        while(pos)
        {
                object= menu->items.GetNext(pos);
                if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
                {
                        if(object->PSType==CVgaMenu::COLORSETUP_ID)
                        {
                                ViewPresetobject = object;
                                CVgaViewPreset *ptr1=(CVgaViewPreset *)object;
                                while (ptr1->ViewPresetTextList.GetCount())
                                        delete ptr1->ViewPresetTextList.RemoveHead();
                                CChildView::thisPtr->Total_Objects=0;
                                ptr1->Page_No=ONE;
                                object->SetPageNum(0);
                                object->IsDraw=true;
                        }
                        else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id))
                        {
                                object->IsDraw=true;
                        }
                        else
                        {
                                object->IsDraw=false;
                        }
                }
        }
    ptr->IsDraw=false;
        page_no=ONE;
        int length=CORDLENGTH1;
        unsigned char data1[CORDLENGTH1];
        data1[ZERO]=(char)1;
        data1[ONE]=(char)0;
        data1[TWO]=(char)0;
        unsigned char * data = (unsigned char *) &data1[ZERO];
        CHostCommand * request = new CHostCommand(GETPSVIEWPRESETSCREEN_FunId, data, length);
        CHostCommand * response = app->SendUiHostCommand(request);
        if(response)
        {
                char ch=CHostCommand::AckNak();
                data = response->GetData();
                length = response->GetDataLength();
                if(ch==theApp.ACK)
                        while (length>ZERO)
                        {
                                // Preparing list.//
                                int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                CPrintText * object1 = new CPrintText(data, length,true,ID);
                                CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
                                obj->ViewPresetTextList.AddTail(object1);
                        }
                        delete response;
        }
        //Call function to arrange the co-ordinates of object to show on screen.//
   if(ViewPresetobject)
           ((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();
    return false;
}

bool EnableColdStartFlag(CVgaButton *ptr)
{
        CChildView::LargeWaitingTime=true;
        CChildView::ColdStartInProcess=true;
        return false;
}

bool DisableColdStartFlag(CVgaButton *ptr)
{
        CChildView::ColdStartInProcess=false;
        CChildView::thisPtr->MaxPreset=1;
        theApp.GetSystemVariable();
        return false;
}

void AutoRefreshGraph(int ToggleValue)
{
        if(ToggleValue)
                CChildView::thisPtr->AutoRefreshon=true;
        else
                CChildView::thisPtr->AutoRefreshon=false;
}

void ProcessSequence(int ToggleValue)
{
        if(ToggleValue)
        {
                CToggle::SequencingON=true;
        }
        else
        {
                CToggle::SequencingON=false;
        }
}

bool USBCheckFunction(CVgaButton *ptr)
{
        if(!CChildView::thisPtr->ISUSBPresent)
        {
                ptr->IsDraw =false;
                return false;
        }
        else
        {
                ptr->IsDraw =true;
                return true;
        }

}

/***************************************************************************
*Purpose:
*   Function return true when authority check is not required and system is
*   in automation mode.Login button will be drawn if return value is true.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool AuthCheckLoginFunc(CVgaButton *ptr)
{
        if((CChildView::thisPtr->AuthorityCheck == false)|| (CChildView::Automation == true))
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/***************************************************************************
*Purpose:
*   Function return true when authority check is required and system is not
*   in automation mode.Logout button will be drawn if return value is true.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool AuthCheckLogoutFunc(CVgaButton *ptr)
{
        if((CChildView::thisPtr->AuthorityCheck == true) && (CChildView::Automation == false))
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}


/***************************************************************************
*Purpose:
*   Function return true when if user is OPERATOR.The button will be
*   displayed in true condition.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool CheckOperatorFunc(CVgaButton *ptr)
{
        if((CChildView::Securitylevel == USER_OPERATOR)||(CChildView::Securitylevel == USER_TECHNICIAN))
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/***************************************************************************
*Purpose:
*   Function return true when if user is OPERATOR.The msg screen will be
*   displayed in true condition.
*Entry condition:
*   CMsgScreen *ptr:pointer to MsgScreen object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool CheckOperatorFunc(CMsgScreen *ptr)
{
        if(CChildView::Securitylevel == USER_OPERATOR)
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}


/***************************************************************************
*Purpose:
*   Function return true when if user is SUPERVISOR or above.The button
*   will be displayed in true condition.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool CheckSupervisorFunc(CVgaButton *ptr)
{
        if(CChildView::Securitylevel >= USER_SUPERVISOR)
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/***************************************************************************
*Purpose:
*   Function return true when if user is SUPERVISOR or above.The MsgScreen
*   will be displayed in true condition.
*Entry condition:
*   CMsgScreen *ptr:pointer to MsgScreen object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool CheckSupervisorFunc(CMsgScreen *ptr)
{
        if(CChildView::Securitylevel >= USER_SUPERVISOR)
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/***************************************************************************
*Purpose:
*   Function return true when authority check is required.
*   Username and password button will be drawn if return value is true.
*Entry condition:
*   CVgaAlaphanumneric *ptr:pointer to alphanumeric object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool AuthCheckClampFunc(CVgaAlphanumeric *ptr)
{
	int OpAuthorityCrt=0;
    if(CChildView::thisPtr->AuthorityCheck == true)
	{
	    CHostCommand *request = new CHostCommand(GET_HORN_CLAMP_STATUS,0,0);
        CHostCommand *response = app->SendUiHostCommand(request);
        if(response)
         {
          char ch=CHostCommand::AckNak();
          if(ch==ACK)
          {
		   unsigned char *data = response->GetData();
		   OpAuthorityCrt=*data;
	      }
          delete response;
        }
		if( ((OpAuthorityCrt & BIT5)!=0) || (CChildView::Securitylevel!=USER_OPERATOR) )
		{
		    ptr->IsDraw =false;
		    return false;
		}
		else
		{
			ptr->IsDraw =true;
			return true;
		}
	}
	else
	{
			ptr->IsDraw =false;
			return false;
	}
}

/**************************************************************************************************
*Purpose:
*   Function return true if parameter name is present and needs to be displayed separate.The button
*   will be displayed in true condition.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
****************************************************************************************************/
bool CheckForNameDisplay(CVgaButton *ptr)
{
        if(NameDisplayFlag)
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/***************************************************************************
*Purpose:
*   Function return true when if reason is present in event details.The button
*   will be displayed in true condition.
*Entry condition:
*   CVgaButton *ptr:pointer to button object.
*Exit condition:
*   bool: true/false
***************************************************************************/
bool CheckForReasonDisplay(CVgaButton *ptr)
{
        if(ReasonDisplayFlag)
        {
                ptr->IsDraw =true;
                return true;
        }
        else
        {
                ptr->IsDraw =false;
                return false;
        }
}

/*Function return true if change password button is to be displayed on
 *Sys Config Page else returns false
*/
bool CheckDisplayChangePWButton(CVgaButton *ptr)
{
        if(CChildView::Securitylevel == (1 << (USER_BRANSON - 1))
                || (CChildView::thisPtr->AuthorityCheckSartUp == FALSE))
        {
                ptr->IsDraw = false;
                return false;
        }
        else
        {
                ptr->IsDraw =true;
                return true;
        }
}

void ReadUSBStoredPresetStrings(CChildView *view)
{
        view->CreateFolder(true);
        CString PSName =view->PowerSupply;
        CString Path=CChildView::LastUSBPresetFolder;
        if(!view->IsFolderPresent(Path,"Presets"))
        {
                CString TempPath= Path;
                CreateDirectory(TempPath,NULL);
        }

        WIN32_FIND_DATA FindFileData;
        HANDLE hFind = INVALID_HANDLE_VALUE;

        CString DirSpec;
        DirSpec=Path+_T("\\*.prst");
        hFind = FindFirstFile(DirSpec, &FindFileData);
        CChildView::thisPtr->TotalUSBPreset=0;
        CString FileName;
        if(view->ValidFolderName(FindFileData.cFileName, USBPRESETSCRN))
        {
                FileName=FindFileData.cFileName;
                if(FileName.Find(_T("Preset"),0)!=(-1))
                {
                        if(FileName.GetLength()>10)
                        {
                                FileName.Delete(0,6);
                                int t =FileName.Find(_T(".prst"),0);
                                if(t!=(-1))
                                        FileName.Delete(t,5);

                                CChildView::thisPtr->USBPresetNames.AddTail(FileName);
                                CChildView::thisPtr->TotalUSBPreset++;
                        }
                }

        }
        while (FindNextFile(hFind, &FindFileData) != 0)
    {
                FileName=FindFileData.cFileName;
                if(view->ValidFolderName(FindFileData.cFileName, USBPRESETSCRN))
                {
                        if(FileName.Find(_T("Preset"),0)!=(-1))
                        {
                                if(FileName.GetLength()>10)
                                {
                                        FileName.Delete(0,6);
                                        int t =FileName.Find(_T(".prst"),0);
                                        if(t!=(-1))
                                                FileName.Delete(t,5);

                                        CChildView::thisPtr->USBPresetNames.AddTail(FileName);
                                        CChildView::thisPtr->TotalUSBPreset++;
                                }
                        }
                }
        }
}

bool CopyPowerPresetToList(CVgaButton *ptr)
{
        CVgaMenu *menu1=theApp.MenuPointer;
        CVgaMenuItem * Object;
        POSITION pos = menu1->items.GetHeadPosition();
        while(pos)
        {
                Object = menu1->items.GetNext(pos);
                if(Object->GetType() == CVgaMenu::VGA_LISTBOX)
                {
                        CListBoxObject *obj=(CListBoxObject*)Object;
                        for(int i =0;i<obj->TotalText;i++)
                                CChildView::thisPtr->PSPresetText[i]= obj->ListBoxText[i];
                        break;
                }
        }
        CChildView::thisPtr->USBpstMutex.Lock();
        while(CChildView::thisPtr->USBPresetNames.GetCount())
                CChildView::thisPtr->USBPresetNames.RemoveHead();
        ReadUSBStoredPresetStrings(CChildView::thisPtr);
        CChildView::thisPtr->USBpstMutex.Unlock();
        return true;
}

bool GetPSPresetScrn(CVgaButton *ptr)
{
        //printf("in GetPSPresetScrn\n");
        char TempArray[10];
        CString Temp=_itoa(ptr->EnumID,TempArray,10);
        Temp=CVgaMenuItem ::LinearSearch(Temp);
        CChildView::thisPtr->ShowMessageScreen(Temp);
        CVgaMenu * menu;
        menu=theApp.MenuPointer;
        CVgaMenuItem *object=0;
        CVgaMenuItem *ViewPresetobject=0;
        POSITION pos=menu->items.GetHeadPosition();
        while(pos)
        {
                object= menu->items.GetNext(pos);
                if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
                {
                        if(object->PSType==CVgaMenu::COLORSETUP_ID)
                        {
                                ViewPresetobject = object;
                                CVgaViewPreset *ptr1=(CVgaViewPreset *)object;
                                while (ptr1->ViewPresetTextList.GetCount())
                                        delete ptr1->ViewPresetTextList.RemoveHead();
                                CChildView::thisPtr->Total_Objects=0;
                                ptr1->Page_No=ONE;
                                object->SetPageNum(0);
                                object->IsDraw=true;
                        }
                        else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id))
                        {
                                object->IsDraw=true;
                        }
                        else
                        {
                                object->IsDraw=false;
                        }
                }
        }
        ptr->IsDraw=false;
        page_no=ONE;
        int length=CORDLENGTH1;
        unsigned char data1[CORDLENGTH1];
        data1[ZERO]=(char)1;
        data1[ONE]=(char)(GlobalPresetSelection>>8);;
        data1[TWO]=(char)GlobalPresetSelection;
        unsigned char * data = (unsigned char *) &data1[ZERO];
        CHostCommand * request = new CHostCommand(GETPSVIEWPRESETSCREEN_FunId, data, length);
        CHostCommand * response = app->SendUiHostCommand(request);
        if(response)
        {
                char ch=CHostCommand::AckNak();
                data = response->GetData();
                length = response->GetDataLength();
                if(ch==theApp.ACK)
                        while (length>ZERO)
                        {
                                // Preparing list.//
                                int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                CPrintText * object1 = new CPrintText(data, length,true,ID);
                                CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
                                obj->ViewPresetTextList.AddTail(object1);
                        }
                        delete response;
        }
        //Call function to arrange the co-ordinates of object to show on screen.//
   if(ViewPresetobject)
           ((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();
        return false;
}

bool GetUSBPresetScrn(CVgaButton *ptr)
{
        char TempArray[10];
        CString Temp=_itoa(ptr->EnumID,TempArray,10);
        Temp=CVgaMenuItem ::LinearSearch(Temp);
        CChildView::thisPtr->ShowMessageScreen(Temp);
        CString PresetNameStr =CChildView::USBSelectedPresetName;
        CString pFileName=CChildView::LastUSBPresetFolder + "\\Preset"+CChildView::USBSelectedPresetName+".prst";
        CFile f;
        CFileException e;
        char ch1=0;
        if( f.Open( pFileName, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
        {
                CVgaMenu * menu;
                menu=theApp.MenuPointer;
                CVgaMenuItem *object=0;
                CVgaMenuItem *ViewPresetobject=0;
                POSITION pos=menu->items.GetHeadPosition();
                while(pos)
                {
                        object= menu->items.GetNext(pos);
                        if(object->GetType()!=CVgaMenu::VGA_ALARMBUTTON)
                        {
                                if(object->PSType==CVgaMenu::COLORSETUP_ID)
                                {
                                        ViewPresetobject=object;
                                        CVgaViewPreset *ptr1=(CVgaViewPreset *)object;
                                        while (ptr1->ViewPresetTextList.GetCount())
                                                delete ptr1->ViewPresetTextList.RemoveHead();
                                        CChildView::thisPtr->Total_Objects=0;
                                        ptr1->Page_No=ONE;
                                        object->SetPageNum(0);
                                        object->IsDraw=true;
                                }
                                else if((object->GetType()==CVgaMenu::TITLE)||(object->PSType==CVgaMenu::BottomMenu_Id))
                                {
                                        object->IsDraw=true;
                                }
                                else
                                {
                                        object->IsDraw=false;
                                }
                        }
                }
                ptr->IsDraw=false;
                page_no=ONE;
                int  size = SIZEOFPRESETDATA;
                int ObjectSize = sizeof(bool)+ sizeof(char)+ size + sizeof(char);
                int StartingPointer =sizeof(bool)+ sizeof(char);
                char ch[SIZEOFPRESETDATA+2] ;
                ch[0]=(char)1;
                f.SeekToBegin();
                int length = (int)(f.GetLength());
                if((length> ObjectSize))
                {
                        f.Close();
                        CChildView::ErrorBeep();
                        theApp.menuName=CChildView::thisPtr->menusname.RemoveTail();
                        page_no=CChildView::thisPtr->menus.RemoveTail();
                        theApp.MenuPointer=CChildView::thisPtr->menupointers.RemoveTail();
                        CChildView::thisPtr->ModifyObjectList(theApp.MenuPointer);
                        CChildView::thisPtr->Invalidate();
                        return false;
                }
                if((length==(PRESETSIZE_WITHOUTDUPS+3))||(length==ObjectSize))
                {
                        f.Seek(StartingPointer, CFile::begin );
                        int t=f.Read(&ch[1],length-3);

                        length = length-2;
                        bool GotResponse =false;
                        unsigned char * data = (unsigned char *) &ch[0];
                        CHostCommand * request = new CHostCommand(GETUSBVIEWPRESETFunId, data, length);
                        CHostCommand * response = app->SendUiHostCommand(request);
                        if(response)
                        {
                                char ch=CHostCommand::AckNak();
                                data = response->GetData();
                                length = response->GetDataLength();
                                if(ch==theApp.ACK)
                                {
                                        GotResponse=true;
                                        while (length>ZERO)
                                        {
                                                // Preparing list.//
                                                int ID=CVgaMenuItem::Convert_Char_To_Integer(data,length,2);
                                                CPrintText * object1 = new CPrintText(data, length,true,ID);
                                                CVgaViewPreset *obj = (CVgaViewPreset*)ViewPresetobject;
                                                obj->ViewPresetTextList.AddTail(object1);
                                        }
                                }
                delete response;
                        }
                        //Call function to arrange the co-ordinates of object to show on screen.//
         if(ViewPresetobject)
                           ((CVgaViewPreset*)ViewPresetobject)->ArrangeCoOrdinate();

                }
        }
        return false;
}


bool ProcessColorSetupScreen(CVgaButton *ptr)
{
        CVgaMenu *menu=theApp.MenuPointer;
        CVgaMenuItem *object= 0;
        POSITION pos = menu->items.GetHeadPosition();
        while (pos)
        {
                object = menu->items.GetNext(pos);
                int type = object->GetType();
                if(type==CVgaMenu::VGATEXTBOX)
                {
                        CTextBox *Textptr=(CTextBox *)object;
                        Textptr->BoxColor=CChildView::thisPtr->Highlight_Color;
                        break;
                }
        }
        return true;
}

bool ProcessUSBGraphButtonDisplay(CVgaButton *ptr)
{
        if(CChildView::thisPtr->EnableUSBGraph)
        {
                ptr->IsDraw =true;
                ptr->RectShow =1;
                return true;
        }
        else
        {
                ptr->RectShow =0;
                ptr->IsDraw =false;
                return false;
        }
}


bool AddStartUpVersion(CVgaButton *ptr)
{
        ptr->SubText = CChildView::thisPtr->StartUpVerFileName;
        ptr->IsDraw =true;
        return true;
}

bool AddSystemVersion(CVgaButton *ptr)
{
        ptr->SubText = CChildView::thisPtr->SystemVerFileName;
        ptr->IsDraw =true;
        return true;
}

