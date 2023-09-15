# Microsoft Developer Studio Project File - Name="VGA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VGA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VGA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VGA.mak" CFG="VGA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VGA - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VGA - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VGA - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 "C:\Program Files\Microsoft SDK\Lib\IPHlpApi.Lib" /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "VGA - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include\IPHlpApi.h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 "C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\IPHlpApi.Lib" /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VGA - Win32 Release"
# Name "VGA - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Application.cpp
# End Source File
# Begin Source File

SOURCE=.\BitCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmaskVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\BottomHalf.cpp
# End Source File
# Begin Source File

SOURCE=.\Check.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CommPort.cpp
# End Source File
# Begin Source File

SOURCE=.\Condition.cpp
# End Source File
# Begin Source File

SOURCE=.\Connection.cpp
# End Source File
# Begin Source File

SOURCE=.\Date.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumCondition.cpp
# End Source File
# Begin Source File

SOURCE=.\EnumVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\EtherPort.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryData.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryGraphs.cpp
# End Source File
# Begin Source File

SOURCE=.\HostCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\Line.cpp
# End Source File
# Begin Source File

SOURCE=.\ListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Mylanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintText.cpp
# End Source File
# Begin Source File

SOURCE=.\Queue.cpp
# End Source File
# Begin Source File

SOURCE=.\RadioMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\RunScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\SBC.cpp
# End Source File
# Begin Source File

SOURCE=.\SBC.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ScreenKeypad.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Table.cpp
# End Source File
# Begin Source File

SOURCE=.\TcpSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\TextBox.cpp
# End Source File
# Begin Source File

SOURCE=.\TextIOFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Time.cpp
# End Source File
# Begin Source File

SOURCE=.\Toggle.cpp
# End Source File
# Begin Source File

SOURCE=.\USBFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\Variable.cpp
# End Source File
# Begin Source File

SOURCE=.\VGA.cpp
# End Source File
# Begin Source File

SOURCE=.\VGA.rc
# End Source File
# Begin Source File

SOURCE=.\VGAAdd_Back_Next_Button.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaAlphanumeric.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaBottomMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaChoice.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaCompareGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaDigitalInput.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaDrawGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaRadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaScreenSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaSubMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaVariable.cpp
# End Source File
# Begin Source File

SOURCE=.\VgaViewPreset.cpp
# End Source File
# Begin Source File

SOURCE=.\WeldingData.cpp
# End Source File
# Begin Source File

SOURCE=.\WeldingHistory.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlElement.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Application.h
# End Source File
# Begin Source File

SOURCE=.\BitCondition.h
# End Source File
# Begin Source File

SOURCE=.\BitmaskVariable.h
# End Source File
# Begin Source File

SOURCE=.\BottomHalf.h
# End Source File
# Begin Source File

SOURCE=.\BottomMenu.h
# End Source File
# Begin Source File

SOURCE=.\Check.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\CommPort.h
# End Source File
# Begin Source File

SOURCE=.\Condition.h
# End Source File
# Begin Source File

SOURCE=.\Connection.h
# End Source File
# Begin Source File

SOURCE=.\Date.h
# End Source File
# Begin Source File

SOURCE=.\EnumCondition.h
# End Source File
# Begin Source File

SOURCE=.\EnumVariable.h
# End Source File
# Begin Source File

SOURCE=.\EtherPort.h
# End Source File
# Begin Source File

SOURCE=.\HistoryData.h
# End Source File
# Begin Source File

SOURCE=.\HistoryGraphs.h
# End Source File
# Begin Source File

SOURCE=.\HostCommand.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\ListBox.h
# End Source File
# Begin Source File

SOURCE=.\LocalChoice.h
# End Source File
# Begin Source File

SOURCE=.\MainFrame.h
# End Source File
# Begin Source File

SOURCE=.\MsgScreen.h
# End Source File
# Begin Source File

SOURCE=.\Mylanguage.h
# End Source File
# Begin Source File

SOURCE=.\newres.h
# End Source File
# Begin Source File

SOURCE=.\ObjectList.h
# End Source File
# Begin Source File

SOURCE=.\ObjectMap.h
# End Source File
# Begin Source File

SOURCE=.\Pointer.h
# End Source File
# Begin Source File

SOURCE=.\PrintText.h
# End Source File
# Begin Source File

SOURCE=.\Queue.h
# End Source File
# Begin Source File

SOURCE=.\RadioMenu.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RunScreen.h
# End Source File
# Begin Source File

SOURCE=.\SBC.h
# End Source File
# Begin Source File

SOURCE=.\ScreenKeypad.h
# End Source File
# Begin Source File

SOURCE=.\ScreenObject.h
# End Source File
# Begin Source File

SOURCE=.\ScreenObjectList.h
# End Source File
# Begin Source File

SOURCE=.\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Table.h
# End Source File
# Begin Source File

SOURCE=.\TcpSocket.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\TextBox.h
# End Source File
# Begin Source File

SOURCE=.\TextIOFile.h
# End Source File
# Begin Source File

SOURCE=.\Time.h
# End Source File
# Begin Source File

SOURCE=.\Toggle.h
# End Source File
# Begin Source File

SOURCE=.\USBFolder.h
# End Source File
# Begin Source File

SOURCE=.\Variable.h
# End Source File
# Begin Source File

SOURCE=.\VGA.h
# End Source File
# Begin Source File

SOURCE=.\VGAAdd_Back_Next_Button.h
# End Source File
# Begin Source File

SOURCE=.\VgaAlphanumeric.h
# End Source File
# Begin Source File

SOURCE=.\VgaBottomMenu.h
# End Source File
# Begin Source File

SOURCE=.\VgaButton.h
# End Source File
# Begin Source File

SOURCE=.\VgaChoice.h
# End Source File
# Begin Source File

SOURCE=.\VgaCompareGraph.h
# End Source File
# Begin Source File

SOURCE=.\VgaDigitalInput.h
# End Source File
# Begin Source File

SOURCE=.\VgaDrawGraph.h
# End Source File
# Begin Source File

SOURCE=.\VgaMenu.h
# End Source File
# Begin Source File

SOURCE=.\VgaMenuItem.h
# End Source File
# Begin Source File

SOURCE=.\VgaRadioButton.h
# End Source File
# Begin Source File

SOURCE=.\VgaScreenSetup.h
# End Source File
# Begin Source File

SOURCE=.\VgaSubMenu.h
# End Source File
# Begin Source File

SOURCE=.\VgaTitle.h
# End Source File
# Begin Source File

SOURCE=.\VgaVariable.h
# End Source File
# Begin Source File

SOURCE=.\VgaViewPreset.h
# End Source File
# Begin Source File

SOURCE=.\WeldingData.h
# End Source File
# Begin Source File

SOURCE=.\WeldingHistory.h
# End Source File
# Begin Source File

SOURCE=.\XmlElement.h
# End Source File
# Begin Source File

SOURCE=.\XmlFile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VGA.ico
# End Source File
# Begin Source File

SOURCE=.\res\VGA.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
