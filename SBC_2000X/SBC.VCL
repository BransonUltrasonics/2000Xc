<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: SBC - Win32 (WCE x86) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP340.tmp" with contents
[
/nologo /W3 /D "_i386_" /D UNDER_CE=400 /D _WIN32_WCE=400 /D "WCE_PLATFORM_STANDARDSDK" /D "UNICODE" /D "_UNICODE" /D "_X86_" /D "x86" /D "NDEBUG" /D "_WIN32_WCE_CEPC" /D "_AFXDLL" /FR"X86Rel/" /Fp"X86Rel/SBC.pch" /Yu"stdafx.h" /Fo"X86Rel/" /Gs8192 /GF /O2 /c 
"C:\Ankur\from Yugal\Mar 5\SBC merged\SBC_ethernet25feb_EventHistory\SBC.cpp"
]
Creating command line "cl.exe @C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP340.tmp" 
Creating temporary file "C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP341.tmp" with contents
[
"C:\Program Files\Windows CE Tools\wce400\STANDARDSDK\Lib\X86\iphlpapi.lib" lpngce.lib zlibce.lib libhpdf.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"wWinMainCRTStartup" /incremental:no /pdb:"X86Rel/SBC.pdb" /out:"X86Rel/SBC.exe" /subsystem:windowsce,4.00 /MACHINE:IX86 
".\X86Rel\AlarmButton.obj"
".\X86Rel\AlarmLog.obj"
".\X86Rel\AlarmLogData.obj"
".\X86Rel\Application.obj"
".\X86Rel\BitCondition.obj"
".\X86Rel\BitmaskVariable.obj"
".\X86Rel\BottomHalf.obj"
".\X86Rel\Check.obj"
".\X86Rel\ChildView.obj"
".\X86Rel\ClientSocket.obj"
".\X86Rel\CommPort.obj"
".\X86Rel\Condition.obj"
".\X86Rel\Connection.obj"
".\X86Rel\Date.obj"
".\X86Rel\EnumCondition.obj"
".\X86Rel\EnumVariable.obj"
".\X86Rel\EtherPort.obj"
".\X86Rel\EventHistory.obj"
".\X86Rel\EventHistoryData.obj"
".\X86Rel\HistoryData.obj"
".\X86Rel\HistoryGraphs.obj"
".\X86Rel\HostCommand.obj"
".\X86Rel\Line.obj"
".\X86Rel\ListBox.obj"
".\X86Rel\LocalChoice.obj"
".\X86Rel\MainFrame.obj"
".\X86Rel\MsgScreen.obj"
".\X86Rel\Mylanguage.obj"
".\X86Rel\PrintText.obj"
".\X86Rel\Queue.obj"
".\X86Rel\RadioMenu.obj"
".\X86Rel\RunScreen.obj"
".\X86Rel\SBC.obj"
".\X86Rel\ScreenKeypad.obj"
".\X86Rel\ServerSocket.obj"
".\X86Rel\StdAfx.obj"
".\X86Rel\Table.obj"
".\X86Rel\TcpSocket.obj"
".\X86Rel\Text.obj"
".\X86Rel\TextBox.obj"
".\X86Rel\TextIOFile.obj"
".\X86Rel\Time.obj"
".\X86Rel\Toggle.obj"
".\X86Rel\USBFolder.obj"
".\X86Rel\UserID.obj"
".\X86Rel\UserIDTable.obj"
".\X86Rel\UserIDTableData.obj"
".\X86Rel\Variable.obj"
".\X86Rel\VGAAdd_Back_Next_Button.obj"
".\X86Rel\VgaAlphanumeric.obj"
".\X86Rel\VgaBottomMenu.obj"
".\X86Rel\VgaButton.obj"
".\X86Rel\VgaChoice.obj"
".\X86Rel\VgaCompareGraph.obj"
".\X86Rel\VgaDigitalInput.obj"
".\X86Rel\VgaDrawGraph.obj"
".\X86Rel\VgaMenu.obj"
".\X86Rel\VgaMenuItem.obj"
".\X86Rel\VgaRadioButton.obj"
".\X86Rel\VgaScreenSetup.obj"
".\X86Rel\VgaSubMenu.obj"
".\X86Rel\VgaTitle.obj"
".\X86Rel\VgaVariable.obj"
".\X86Rel\VgaViewPreset.obj"
".\X86Rel\WeldingData.obj"
".\X86Rel\WeldingHistory.obj"
".\X86Rel\XmlElement.obj"
".\X86Rel\XmlFile.obj"
".\X86Rel\SBC.res"
".\X86Rel\EventLog.obj"
]
Creating command line "link.exe @C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP341.tmp"
<h3>Output Window</h3>
Compiling...
SBC.cpp
C:\Ankur\from Yugal\Mar 5\SBC merged\SBC_ethernet25feb_EventHistory\hpdf_config.h(39) : warning C4005: 'UNDER_CE' : macro redefinition
        C:\Program Files\Windows CE Tools\wce400\STANDARDSDK\mfc\include\wce.h(279) : see previous definition of 'UNDER_CE'
C:\Ankur\from Yugal\Mar 5\SBC merged\SBC_ethernet25feb_EventHistory\SBC.cpp(1283) : warning C4800: 'unsigned char' : forcing value to bool 'true' or 'false' (performance warning)
Linking...
Creating temporary file "C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP344.tmp" with contents
[
/nologo /o"X86Rel/SBC.bsc" 
".\X86Rel\StdAfx.sbr"
".\X86Rel\AlarmButton.sbr"
".\X86Rel\AlarmLog.sbr"
".\X86Rel\AlarmLogData.sbr"
".\X86Rel\Application.sbr"
".\X86Rel\BitCondition.sbr"
".\X86Rel\BitmaskVariable.sbr"
".\X86Rel\BottomHalf.sbr"
".\X86Rel\Check.sbr"
".\X86Rel\ChildView.sbr"
".\X86Rel\ClientSocket.sbr"
".\X86Rel\CommPort.sbr"
".\X86Rel\Condition.sbr"
".\X86Rel\Connection.sbr"
".\X86Rel\Date.sbr"
".\X86Rel\EnumCondition.sbr"
".\X86Rel\EnumVariable.sbr"
".\X86Rel\EtherPort.sbr"
".\X86Rel\EventHistory.sbr"
".\X86Rel\EventHistoryData.sbr"
".\X86Rel\HistoryData.sbr"
".\X86Rel\HistoryGraphs.sbr"
".\X86Rel\HostCommand.sbr"
".\X86Rel\Line.sbr"
".\X86Rel\ListBox.sbr"
".\X86Rel\LocalChoice.sbr"
".\X86Rel\MainFrame.sbr"
".\X86Rel\MsgScreen.sbr"
".\X86Rel\Mylanguage.sbr"
".\X86Rel\PrintText.sbr"
".\X86Rel\Queue.sbr"
".\X86Rel\RadioMenu.sbr"
".\X86Rel\RunScreen.sbr"
".\X86Rel\SBC.sbr"
".\X86Rel\ScreenKeypad.sbr"
".\X86Rel\ServerSocket.sbr"
".\X86Rel\Table.sbr"
".\X86Rel\TcpSocket.sbr"
".\X86Rel\Text.sbr"
".\X86Rel\TextBox.sbr"
".\X86Rel\TextIOFile.sbr"
".\X86Rel\Time.sbr"
".\X86Rel\Toggle.sbr"
".\X86Rel\USBFolder.sbr"
".\X86Rel\UserID.sbr"
".\X86Rel\UserIDTable.sbr"
".\X86Rel\UserIDTableData.sbr"
".\X86Rel\Variable.sbr"
".\X86Rel\VGAAdd_Back_Next_Button.sbr"
".\X86Rel\VgaAlphanumeric.sbr"
".\X86Rel\VgaBottomMenu.sbr"
".\X86Rel\VgaButton.sbr"
".\X86Rel\VgaChoice.sbr"
".\X86Rel\VgaCompareGraph.sbr"
".\X86Rel\VgaDigitalInput.sbr"
".\X86Rel\VgaDrawGraph.sbr"
".\X86Rel\VgaMenu.sbr"
".\X86Rel\VgaMenuItem.sbr"
".\X86Rel\VgaRadioButton.sbr"
".\X86Rel\VgaScreenSetup.sbr"
".\X86Rel\VgaSubMenu.sbr"
".\X86Rel\VgaTitle.sbr"
".\X86Rel\VgaVariable.sbr"
".\X86Rel\VgaViewPreset.sbr"
".\X86Rel\WeldingData.sbr"
".\X86Rel\WeldingHistory.sbr"
".\X86Rel\XmlElement.sbr"
".\X86Rel\XmlFile.sbr"
".\X86Rel\EventLog.sbr"]
Creating command line "bscmake.exe @C:\DOCUME~1\AMaurya\LOCALS~1\Temp\RSP344.tmp"
Creating browse info file...
<h3>Output Window</h3>



<h3>Results</h3>
SBC.exe - 0 error(s), 2 warning(s)
</pre>
</body>
</html>
