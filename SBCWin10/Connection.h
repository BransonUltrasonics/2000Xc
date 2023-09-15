/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Connection.h_v   1.9   30 Jan 2015 08:13:30   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Connection.h_v  $
 * 
 *    Rev 1.9   30 Jan 2015 08:13:30   amaurya
 *  REQFORSBCVERSION macro added to get SBC version number through webservice.
 * 
 *    Rev 1.8   11 Dec 2014 06:49:42   RJamloki
 * AddSeparator() declaration addded.
 * 
 *    Rev 1.7   28 Nov 2014 08:30:30   rjamloki
 * JSonDataReply() argument type changed coverity issue.
 * 
 *    Rev 1.6   10 Nov 2014 02:48:50   rjamloki
 * Enum Member name changed.
 * 
 *    Rev 1.5   01 Oct 2014 10:47:52   AnPawar
 * Changes for web services
 * 
 *    Rev 1.4   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.3     05 Mar 2014 14:13:14 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.2     03 Jan 2014 09:04:48 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.1     05 Jun 2013 09:33:20 amaurya      
 * Initial  *    Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_)
#define AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_
#include "ClientSocket.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define EVENTLOGFIELDID   1   //FieldId for eventlog to be send to SBC
#define WELDHISTORYFIELDID   2   //FieldId for weldhistory to be send to SBC
#define REQFOREVENTLOGCOUNT   3
#define REQFORWELDLOGCOUNT   4
#define REQFORSBCVERSION   5

class CHostCommand;

class CConnection : public CClientSocket  
{
	enum {
		COM_PORT_OPTION	= 44,
		SET_BAUDRATE	= 1,
		SET_DATASIZE	= 2,
		SET_PARITY	= 3,
		SET_STOPSIZE	= 4,

		SE	= 240,
		SB	= 250,
		WILL	= 251,
		WONT	= 252,
		DO	= 253,
		DONT	= 254,
		IAC	= 255,
		};
	enum CONN_STATE {
		STATE_NORMAL,
		STATE_NORMAL2,
		STATE_IAC,
		STATE_SINGLE,
		STATE_SB,
		STATE_COMPORT,
		STATE_WAITIAC,
		STATE_SE
		};
   struct JsonPacket
	{
		int FieldId;
		int From;
		int To;
	};
 	struct JsonSBCDataHandshakepacket
	{
		int TotalExpectedData;
	};
public:
	void CloseConnection();
	void ProcessInput();
	CConnection(SOCKET fd);
	virtual ~CConnection();

protected:
	CONN_STATE state;
	CHostCommand * request;
	void CharReceived(char ch);
    bool JsonDataRequest(JsonPacket * JTestPacket);
    void JSonDataReply(char * buff, size_t Len);
	char delimiter;
	bool ProcessInputEx();  
	char inbuf[4096];
	int inbuflen;
	char outbuf[4096];
	int outbuflen;
    int RetriesForData;
    int PrepareBufferForWebService(CString Path ,int StartingPoint,int Count,bool Event_Or_Weld);
    void AddSeparator(char * Str, int Seperator);
 };

#endif // !defined(AFX_CONNECTION_H__159C1FFE_31DD_45AA_A467_1E667DB45C4C__INCLUDED_)
