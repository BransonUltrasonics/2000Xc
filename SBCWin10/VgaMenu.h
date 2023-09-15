/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenu.h_v   1.5   09 Jul 2014 07:16:04   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/VgaMenu.h_v  $
 * 
 *    Rev 1.5   09 Jul 2014 07:16:04   akaushal
 * changed enum MENUS.
 * 
 *    Rev 1.4   28 Mar 2014 14:33:20   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:58 rjamloki    
 * Screens and PDF working
 *
 *    Rev 1.2     27 Feb 2014 01:55:12 jerryw.wang   
 * Added the AddAlarmLogObject, AddEventLogObject and AddDigitalInput functon.
 *
 *    Rev 1.1     03 Jan 2014 09:06:26 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:12 amaurya      
 * Initial Revision.
 *
 */

#if !defined(AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_)
#define AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectList.h"
#include "VgaMenuItem.h"
#include "Condition.h"
class CXmlElement;

class CVgaMenu  
{
public:
   CVgaMenu();
   void Draw(CDC * pDC) const;
   CVgaMenu(CXmlElement * element);
   virtual ~CVgaMenu();
   const CString & GetName() const
   {
      return name;
   }
   CObjectList<CVgaMenuItem> items;
   enum MENUS 
   {
      BottomMenu_Id=0,
      TITLE = 1,
      TEXT,
      SUBMENU,                       
      HSUBMENU,                     
      HHMM=5,
      DATE,
      CHOICE,
      ALPHA,
      VARIABLE,                           
      RADIO_BUTTON=10,
      RADIOMENU,
      TOGGLE,                      
      HVARIABLE,                  
      ALARM,
      RADIOLARGEMENU=15,                  
      RADIOLARGE,
      SCREENSETUP,
      MENU_END,
      VGATEXT = 19,
      VGATEXTBOX = 20,
      VGALINE = 21,
      VGARUNSCREENOBJECT =22,
      VGA_Button_OBJECT =23,
      VGABottomHalfObject =24,
      VGACheck,
      VGA_GRAPH_OBJECT =26,
      VGA_LISTBOX =27,
      VGAMsgScrnObject,
      VGAPointerObject,
      VGATableObject,
      VGAUSBFolder,

      VGAHISTORYOBJECT,
      COLORSETUP_ID,
      VGA_VGAEXITBUTTON,
      VGA_VGASAVEBUTTON,
      VGA_ALARMBUTTON,

      VGA_DIGITALINPUT = 39,
      VGA_DIGITALOUTPUT = 40,
	  VGAALARMLOGOBJECT,
      VGAEVENTLOGOBJECT,
      NEXT=7000,
      BACK=7001,
      VGATOOLMAP,
	  VGAUSERIDTABLEOBJECT,
	  VGA_LOGINBUTTON,
	  VGA_LOGOUTBUTTON
   }MenuType;
   static CVgaMenuItem* CreateObjectBack_Next(int exit_type);
protected:
   void AddSubmenu(CXmlElement * e);
   void AddTitle(CXmlElement * e);
   void AddBottomMenu();
   void AddChoicemenu(CXmlElement * e);
   void AddText(CXmlElement * e);
   void AddTogglemenu(CXmlElement * e);
   void AddRadioMenu(CXmlElement * e);
   void AddVariableMenu(CXmlElement * e); 
   void AddDateMenu(CXmlElement * e);
   void AddTimeMenu(CXmlElement * e);
   void AddVgaButtonMenu(CXmlElement * e);
   void AddVgaRadioButtonMenu(CXmlElement * e);
   void AddMsgScreen(CXmlElement * e);
   void AddListBox(CXmlElement * e);
   void AddAlphaNumeric(CXmlElement * e);
   void AddBottomMenu(CXmlElement *e);
   void AddBottomHalf(CXmlElement * e);
   void AddCheck(CXmlElement * e);
   void AddScreenSetup(CXmlElement * e);
   void AddLine(CXmlElement * e);
   void AddRunMenu(CXmlElement * e);
   void AddHistoryObject(CXmlElement * e);
   void AddAlarmLogObject(CXmlElement * e);
   void AddEventLogObject(CXmlElement * e);
   void AddUserIDTableObject(CXmlElement * e);
   void AddTextBoxObject(CXmlElement * e);
   void AddGraphObject(CXmlElement * e);
   void AddTableObject(CXmlElement * e);
   void AddLocalChoiceObject(CXmlElement * e);
   void AddCompareGraph();
   void AddViewPreset();
   void AddAlarmButton(CXmlElement * e);
   void AddHistoryGraph(CXmlElement * e);
   void AddDigitalInput(CXmlElement * e);
   void AddDigitalOutput(CXmlElement * e);
   CString name;
};

#endif // !defined(AFX_VGAMENU_H__2B0FD33E_4F8D_48B2_84B9_2EFE9F0D8676__INCLUDED_)
