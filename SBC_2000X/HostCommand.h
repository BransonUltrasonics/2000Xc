/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HostCommand.h_v   1.11   22 Dec 2015 10:42:52   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/HostCommand.h_v  $
 * 
 *    Rev 1.11   22 Dec 2015 10:42:52   RJamloki
 * Adding #define GET_HORN_CLAMP_STATUS for horn clamp alarm reset command, also merging to the trunk, base from final version Ver12.0
 * 
 *    Rev 1.9.1.6   21 Dec 2015 13:10:18   RJamloki
 * Add #define GET_HORN_CLAMP_STATUS for horn clamp alarm reset
 * 
 *    Rev 1.9.1.5   27 Mar 2015 11:03:44   amaurya
 * GET_SOFTWARE_VERSION command added to reset serial timeout on WC.
 * 
 *    Rev 1.9.1.4   02 Jan 2015 04:58:56   rjamloki
 * macro  COPY_ALL_PRESET_COMMAND defined for copy all preset command
 * 
 *    Rev 1.9.1.3   10 Nov 2014 02:50:26   rjamloki
 * MAXSCAN_LEN macro added.
 * 
 *    Rev 1.9.1.2   26 Sep 2014 09:39:04   rjamloki
 * Added defines for string Ids in OL title
 * 
 *    Rev 1.9.1.1   25 Sep 2014 12:07:26   AnPawar
 * new macros defined.
 * 
 *    Rev 1.9.1.0   28 Jul 2014 16:14:44   rjamloki
 * defined macros BARCODESCAN_CMD and MAXSCAN_LEN
 * 
 *    Rev 1.9   09 Jul 2014 06:58:16   akaushal
 * added new command GET_NUMBER_OF_USERS.
 * 
 *    Rev 1.8   09 Jun 2014 11:48:28   rjamloki
 * Macro added to check state machine status
 * 
 *    Rev 1.7   27 May 2014 06:31:46   amaurya
 * Added a new command for Weld/Event Memory Full
 * 
 *    Rev 1.6   20 May 2014 10:58:54   rjamloki
 * Command added to delete Event History ,Weld History and Logout.
 * 
 *    Rev 1.5   21 Apr 2014 13:37:54   akaushal
 * Macros modified and added for login and change password. 
 * 
 *    Rev 1.4   28 Mar 2014 14:33:02   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:20 rjamloki
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:58 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:24 amaurya    
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:48 amaurya   
 * Initial Revision.
 */
#if !defined(AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_)
#define AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define GetQualityLimits_FunId	   137
#define PowerSupply_FunId		   280
#define GetMenuAddress_FunId	   1000
#define GetMenuData_FunId		   1001
#define GetSubMenuData_FunId	   1002
#define SetTime_FunId			   1003
#define SetDate_FunId			   1004
#define GetChoice_FunId			   1005
#define GetAlpha_FunId			   1006
#define SetAlpha_FunId			   1007
#define GetVariable_FunId		   1008
#define SetVariable_FunId		   1009
#define SetRadio_FunId			   1010
#define GetToggle_FunId			   1011
#define GetRadioMenu_FunId		   1012
#define GetRadioLarge_FunId	       1013
#define SetRadioLarge_FunId	       1014
#define VGAButton_FunId			   1015
#define GetPollingData_FunId	   1016
#define GetWeldResults_FunId	   1017
#define SetPassword_FunId		   1018
#define PresetScrButton_FunId      1019
#define GetPasswordMenus_FunId	   1020
#define GetAlarmMenu_FunId		   1021
#define GetAlarmObject_FunId	   1022
#define GetWeldStateString_FunId   1023
#define GetWeldData				   1024
#define GetWeldSetup_FunId		   1025
#define WeldDataHeadings_FunId     1026
#define PrintingParameter_FunId    1027
#define UpLoadPreset_FunId		   1028
#define DownLoadPresetFun_Id	   1029
#define PowerMatchCurve_FunId 	   1030
#define SequencingPreset_FunId	   1031
#define ErrorBeep_FunId			   1032
#define GenerateAlarm_FunId		   1033
#define GETUSBVIEWPRESET_FunId	   1034
#define GETPSVIEWPRESET_FunId	   1035
#define GetWeldingStatus		   1036
#define GetPollingData_FunResponse 1038
#define GetEptrVariable_FunId      1050
#define SetValue_FunID             1051 
#define GetVariableData_FunID      1052
#define GetBottomMenuData_FunID    1053
#define GetWeldData_FunID		   1054
#define GetWeldStateStrings_FunId  1055	
#define PowerMatchCurve_FunctionId 1056
#define GETPSVIEWPRESETSCREEN_FunId  1057
#define GetAlarmSetupFlag          1058
#define GetAlarmMenuItems_FunId    1059
#define GetWeldSetupPrint_FunID    1060
#define GETUSBVIEWPRESETFunId	   1061
#define RESETALARMS_FUNID          1062
#define STATEMACHINE_ENABLED       1063
#define CHECKSTATEMACHINE          1064
#define GetSysVariable_FunId       1100

#define DELETE_WELD_HISTORY        1105
#define DELETE_EVENT_HISTORY       1106

/*Ver.12*/
//command numbers
#define GET_HORN_CLAMP_STATUS      1204
#define USERIDSETUP                1090
#define GET_NUMBER_OF_USERS        1202
#define EVENTLOGSETUP	           1092
#define ALARM_MEMORYFULL           1093
#define NETINFO_FunID              1200 
#define USERID_DATA                1096
#define USERLOGIN_FUNID            1101
#define CHANGEPASSWORD_FUNID       1102
#define NETINFO_FunID              1200
#define GET_SOFTWARE_VERSION       1201
#define MODIFY_USER                1097
#define BARCODESCAN_CMD			   1098
#define CURRENTSTR_ID			   522
#define PHASESTR_ID                4298	 
#define VOLTAGESTR_ID              4296
#define FREQUENCYSTR_ID			   1857
#define OVERLOADSTR_ID             2196
#define ADDUSER_DATA               0xFFFF
#define GETDATA                    1
#define SETDATA                    2
#define LOGOUT_FUNID               1103
#define EXIT_USERIO_COMMAND        1203
#define COPY_ALL_PRESET_COMMAND    1099
//command length
#define NETINFO_LEN                12
#define USERLOGIN_LEN              22
#define CHANGEPASSWORD_LEN         44
#define USERID_DATA_LEN            4
#define USERLIST_COMMAND_SIZE      1
#define MODIFY_USER_COMMAND_SIZE   6
#define LOGOUT_LEN                 1
#define DEL_WELD_HIS_LEN           1
#define DEL_EVENT_HIS_LEN          1
#define STATEMACHINE_ENABLED_SIZE  1
#define EXIT_USERIO_COMMAND_SIZE   1

#define ERASESEQUENCE			01
#define CONTINUESEQUENCE		02
#define EDITSEQUENCE		   	03
#define GetChoice_length		5
#define GetVariable_length		4
#define SETUPSTARTPAGE			1
#define SETUPENDPAGE			5
#define DUPSSTARTPAGE			5
#define DUPSENDPAGE				6
#define WELDDATAID				7
#define GRAPHID					8
#define HORNSCANPRINTTEXTID	9
#define PMCENABLEDISABLE		01
#define PMCCLEARGRAPH			02
#define PMCADDAVGGRAPH			03
#define PMCGETAVGGRAPH			04
#define MAXSCANBUFF_LEN			25
#define MAXSCAN_LEN				19//max scan len permitted right now is 18 cchar. We have spacce reserved up to 24 for future.

class CHostCommand  
{
	
	enum {	ACK = 0x06,
		NAK = 0x15,
		DLE = 0x10,
		STX = 0x02,
		ETX = 0x03 };
	enum CHANNEL_STATE {
		STATE_WAIT_ACKNAK,	// waiting for ACK or NAK
		STATE_WAIT_FIRST_DLE,	// waiting for first DLE
		STATE_WAIT_STX,		// waiting for STX after DLE
		STATE_WAIT_LENGTH1,	// waiting for upper byte of length
		STATE_WAIT_LENGTH2,	// waiting for lower byte of length
		STATE_WAIT_CODE1,	// waiting for upper byte of command code
		STATE_WAIT_CODE2,	// waiting for lower byte of command code
		STATE_WAIT_DISPLOCK,
		STATE_WAIT_DATA,
		STATE_WAIT_CRC,
		STATE_WAIT_SECOND_DLE,	// waiting for second DLE
		STATE_WAIT_ETX,		// waiting for ETX after DLE
		};
public:
	unsigned char * buffer;
	short code;	
	bool CharRec(unsigned char ch);
	bool StartWeldDataCharReceived(unsigned char ch);
	int x;
	static char AckNak() ;
	bool CharReceived(unsigned char ch);
	void SetData(short c, unsigned char *data, int length);
	unsigned char * GetData() const;
	unsigned char * GetBuffer() const;
	DWORD GetBufLength() const;
	int GetDataLength() const;
	CHostCommand(bool addAck);
	CHostCommand(short code1, unsigned char * data, int length);
	~CHostCommand();
	static bool ack;
protected:
	static bool dle;
	
	unsigned char * d;
	int len;
	CHANNEL_STATE state;		// receiver state machine
	unsigned char DispLock;
		// host command code
	unsigned char * rxbuf;		// receiver buffer data (for data part of command)
	short rxindex;			// pointer into receiver buffer
	char checksum;			// host command checksum
};

#endif // !defined(AFX_HOSTCOMMAND_H__1C6E4F17_E9CF_4BA0_B848_C3D57BA47C77__INCLUDED_)
