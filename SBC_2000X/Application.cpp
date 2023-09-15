/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Application.cpp_v   1.70   Dec 05 2017 12:05:12   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Application.cpp_v  $
 * 
 *    Rev 1.70   Dec 05 2017 12:05:12   RJamloki
 * Update to version 12.3 release
 * 
 *    Rev 1.69   Nov 16 2017 16:36:06   RJamloki
 * Updated version to v12.3O
 * 
 *    Rev 1.68   Nov 07 2017 09:57:36   RJamloki
 * Update version to 12.3N
 * 
 *    Rev 1.67   Nov 07 2017 09:45:24   RJamloki
 * Update version to 12.3M
 * 
 *    Rev 1.66   Oct 09 2017 10:36:36   RJamloki
 * Update version to 12.3L
 * 
 *    Rev 1.65   Jun 23 2017 13:13:48   RJamloki
 * Update to version v12.2
 * 
 *    Rev 1.64   Jun 19 2017 13:47:46   RJamloki
 * Update to version v12.2I
 * 
 *    Rev 1.63   Jun 08 2017 12:12:38   RJamloki
 * Update Version v12.2H
 * 
 *    Rev 1.62   May 25 2017 19:36:00   RJamloki
 * Update version 12.2G
 * 
 *    Rev 1.61   25 Aug 2016 12:56:32   RJamloki
 * Updated version release from bucket #2 v12.2
 * 
 *    Rev 1.60   13 Jun 2016 09:50:00   RJamloki
 * Updated to test version 12.2E sunrise bucket #2
 * 
 *    Rev 1.59   27 May 2016 14:03:54   RJamloki
 * Update version
 * 
 *    Rev 1.58   06 May 2016 12:40:52   RJamloki
 * Change version to Ver12.2D
 * 
 *    Rev 1.57   17 Dec 2015 11:47:14   RJamloki
 * change version to 12.1K
 * 
 *    Rev 1.56   May 05 2015 12:35:08   builder
 * Changed version string to 12.0 for official release
 * 
 *    Rev 1.55   29 Apr 2015 16:05:16   rjamloki
 * Changed Version to 12I10
 * 
 *    Rev 1.54   21 Apr 2015 16:50:42   rjamloki
 * Version fixed to 12.I.9
 * 
 *    Rev 1.53   16 Apr 2015 19:40:34   rjamloki
 * Version string changed to 12.I.8
 * 
 *    Rev 1.52   16 Apr 2015 17:38:52   rjamloki
 * Version string changed to 12.I.7
 * 
 *    Rev 1.51   16 Apr 2015 05:53:02   sesharma
 * Version string changed to 12.I.6.
 * 
 *    Rev 1.50   09 Apr 2015 04:09:14   RJamloki
 * UI Host command retries are moved to lower level in CommPort.cpp
 * 
 *    Rev 1.49   01 Apr 2015 12:53:04   amaurya
 * version string changed to 12.I.5
 * 
 *    Rev 1.48   30 Mar 2015 06:25:32   rjamloki
 * SendUISerialHostCommand corrected to delete response.
 * 
 *    Rev 1.47   27 Mar 2015 11:05:06   amaurya
 * Coverty fix 12562.
 * 
 *    Rev 1.46   13 Mar 2015 06:34:56   amaurya
 *  Version changed to 12.I.4.  
 * 
 *    Rev 1.45   11 Mar 2015 09:25:32   amaurya
 * Changed to give popup if there is no ip address configured on the SBC or network adapter is disabled.
 * 
 *    Rev 1.44   05 Feb 2015 07:06:56   amaurya
 * Version changed to 12.I.3.
 * 
 *    Rev 1.43   30 Jan 2015 08:12:42   amaurya
 * Version Changed.
 * 
 *    Rev 1.42   26 Jan 2015 13:26:12   rjamloki
 * SendUIHostCommand is changed to retry.
 * 
 *    Rev 1.41   08 Jan 2015 05:00:02   AnPawar
 * version string changed
 * 
 *    Rev 1.40   05 Jan 2015 06:03:58   rjamloki
 * version string changed
 * 
 *    Rev 1.39   02 Jan 2015 04:55:20   rjamloki
 * version string changed
 * 
 *    Rev 1.38   12 Dec 2014 06:06:02   RJamloki
 * Version level changed.
 * 
 *    Rev 1.37   11 Dec 2014 06:48:04   RJamloki
 * Version Changed.
 * 
 *    Rev 1.36   28 Nov 2014 08:29:34   rjamloki
 * version string changed
 * 
 *    Rev 1.35   17 Nov 2014 08:19:18   RJamloki
 * Ver 12.G.2 For mongle horde testing
 * 
 *    Rev 1.34   14 Nov 2014 02:52:58   rjamloki
 * Version String changed.
 * 
 *    Rev 1.33   10 Nov 2014 02:47:30   rjamloki
 *  Version string changed.
 * 
 *    Rev 1.32   20 Oct 2014 05:37:52   RJamloki
 * version string changed
 * 
 *    Rev 1.31   06 Oct 2014 08:50:34   AnPawar
 * Version string changed
 * 
 *    Rev 1.30   06 Oct 2014 03:21:24   rjamloki
 * version string changed
 * 
 *    Rev 1.29   01 Oct 2014 10:45:36   AnPawar
 * version changed.
 * 
 *    Rev 1.28   25 Sep 2014 12:03:26   AnPawar
 * Version string changed.
 * 
 *    Rev 1.27   11 Sep 2014 09:40:34   rjamloki
 * version changed
 * 
 *    Rev 1.26   02 Sep 2014 03:21:02   rjamloki
 * version string changed
 * 
 *    Rev 1.25   26 Aug 2014 07:40:58   rjamloki
 * Version string changed to 12.E.2
 * 
 *    Rev 1.24   22 Aug 2014 12:37:24   rjamloki
 * Version 12.E.1
 * 
 *    Rev 1.23   18 Aug 2014 07:33:12   rjamloki
 * Version 12.D.3
 * 
 *    Rev 1.22   28 Jul 2014 16:02:04   rjamloki
 * version string changed
 * 
 *    Rev 1.21   28 Jul 2014 13:27:34   rjamloki
 * coverity fix
 * 
 *    Rev 1.20   22 Jul 2014 08:06:58   akaushal
 * version changed.
 * 
 *    Rev 1.19   10 Jul 2014 14:17:54   tayars
 * Updated software version to 12.D
 * 
 *    Rev 1.18   09 Jul 2014 06:42:58   akaushal
 * Version string changed. 
 * 
 *    Rev 1.17   20 Jun 2014 10:56:34   akaushal
 * Changed version string..
 * 
 *    Rev 1.16   09 Jun 2014 11:35:24   rjamloki
 * version string changed.Initialized variable in constructor.
 * 
 *    Rev 1.15   27 May 2014 06:19:34   amaurya
 * Changed version string.
 * 
 *    Rev 1.14   20 May 2014 10:51:48   rjamloki
 * Version changed
 * 
 *    Rev 1.13   07 May 2014 13:18:24   akaushal
 * Macro for printf disable .
 * 
 *    Rev 1.11   23 Apr 2014 11:17:46   akaushal
 * SendUiSerialHostCommand() function changed for serial communication
 * 
 *    Rev 1.10   21 Apr 2014 13:27:26   akaushal
 * Changed version string.Corrected the getMacAddress(). 
 * 
 *    Rev 1.9   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.8     26 Mar 2014 14:20:12 rjamloki      
 * version string changed to 12.6     .
 *
 *    Rev 1.7     07 Mar 2014 11:15:36 rjamloki      
 * Modify User Changes.
 *
 *    Rev 1.6    06 Mar 2014 13:36:42 ygupta      
 * Changed Version Label string to 12.A
 *
 *    Rev 1.5     05 Mar 2014 14:13:10 rjamloki      
 * Screens and PDF working
 *
 *    Rev 1.4     03 Jan 2014 09:04:44 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.3     19 Dec 2013 06:16:50 rjamloki      
 * Changed macros to build on both EVC and VC++.
 *
 *    Rev 1.2     18 Dec 2013 10:00:28 rjamloki      
 * Initial Test version.SBC to WC serial communication.
 *
 *    Rev 1.1     05 Jun 2013 09:33:16 amaurya      
 * Initial Revision 2.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "Application.h"
#include "CommPort.h"
#include "EtherPort.h"
#include "ChildView.h"
#include "HostCommand.h"
#include "ServerSocket.h"
#include "Connection.h"
#include "VGA.h"

#ifdef DISABLEPRINTF
#define printf
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApplication


CApplication * app;

CApplication::CApplication()
{
	app = this;
	ether = NULL;
	com = NULL;
}

BEGIN_MESSAGE_MAP(CApplication, CWinApp)
	//{{AFX_MSG_MAP(CApplication)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/*This Version String needs to be changed when ever */
/*there is a new version level assigned	.			*/
char Version[7]="12.4";

unsigned long CApplication::ip_addr = 0;
unsigned long CApplication::mask_addr = 0;
unsigned long CApplication::gateway_addr = 0;
int CApplication::mac_addr_len = 0;
BYTE CApplication::mac_addr[MAX_ADAPTER_ADDRESS_LENGTH];

void CApplication::InitTasks()
{

	getAdapterInfo(); //get all the network information 
	printf("in InitTasks()");
	CString port = GetProfileString(_T("Setup"), _T("Port"), _T("\\\\.\\COM2"));
	int speed = GetProfileInt(_T("Setup"), _T("Speed"), CBR_115200);
	com = new CCommPort("\\com2:", CBR_115200);
	ether = new CEtherPort();
	printf("\n returned from inittasks");

}

void CApplication::getAdapterInfo(void)
{
	/*get subnet mask and gateway address*/
	printf("in getAdapterkInfo \n");
	DWORD result;
	PIP_ADAPTER_INFO adapterInfo = NULL;
	ULONG size = 0;
	result = GetAdaptersInfo( adapterInfo, &size );
	//called with adapterInfo = NULL and size = 0 to get the size of buffer needed
	if( result == ERROR_BUFFER_OVERFLOW )
	{
		if( !(adapterInfo = (PIP_ADAPTER_INFO)malloc(size)) )
		{
			AfxMessageBox(_T("Mac_error Insufficient Memory"));
			if (adapterInfo)
				free(adapterInfo);
			theApp.ExitInstance();	
			exit(1);
		}
		result = GetAdaptersInfo( adapterInfo, &size);
	}

	if( result != NO_ERROR )
	{
		AfxMessageBox(_T("Enable n/w connection"));
		theApp.ExitInstance();
		exit(1);
	}
	if( size == 0 )
		adapterInfo = NULL;

	if( adapterInfo == NULL )
		printf("No Interfaces Present.\n");

	if (adapterInfo != NULL)
	{
		mac_addr_len = adapterInfo->AddressLength;
		CApplication::ip_addr = inet_addr(adapterInfo->IpAddressList.IpAddress.String);
		CApplication::mask_addr = inet_addr(adapterInfo->IpAddressList.IpMask.String);
		CApplication::gateway_addr = inet_addr(adapterInfo->GatewayList.IpAddress.String);
		memcpy(mac_addr,adapterInfo->Address,mac_addr_len);
	}

#ifdef RUN_ON_SBC
	if(adapterInfo && adapterInfo->DhcpEnabled) //coverity fix 12562
	{
		//coverity 12563 automatically fixed with the fix of issue 12562
		AfxMessageBox(_T("Please select static IP configuration and Manually assign ip"));
		if (adapterInfo)
			free(adapterInfo);
		theApp.ExitInstance();			
		exit(1);
	}
#endif
	if (adapterInfo)
		free(adapterInfo);
}

/*Return CString repesenting the ip address of local machine in format 123.456.789.000 
*this function should be called after getAdapterInfo() is called.
*/
CString CApplication::getIPAddress(CString str)
{
	IN_ADDR addr;
	if(ip_addr == 0)	
		return (str = "");
	addr.S_un.S_addr = CApplication::ip_addr;
	str = " = " + CString(inet_ntoa(addr));
	return str;
}

/*Return CString repesenting the mac address of local machine in format XXXXXXXXXXXX 
*this function should be called after getAdapterInfo() is called.
*/
CString CApplication::getMacAddress(CString str)
{
	if(mac_addr_len == 0)
		return (str = "");

	char *byte_arr = new char[mac_addr_len*2+1];
	sprintf(byte_arr,"%02X%02X%02X%02X%02X%02X",mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
	str = " = " +CString(byte_arr);
	delete[] byte_arr;
	return str;
}


int CApplication::ExitInstance() 
{
	delete com;
	delete ether;
	return CWinApp::ExitInstance();
}

bool CApplication::GetBottomMenuAddress(bool *Start_Screen,int *WeldResults_Address,int *mainMenuAddress,int *WeldSetup_Address,int *GraphsMenu_Address,int *Langauage_Index,bool * metric)
{
	TRACE(_T("\n CApplication::GetBottomMenuAddress"));
	if(CCommPort::CommPortNotready)
		return false;
	char data1[8];
	for(int i=0;i<6;i++)
		data1[i]=Version[i];
	unsigned char *data=(unsigned char*) &data1[0];
	int length = 6;
	CHostCommand * command = new CHostCommand(GetMenuAddress_FunId, data, length);
	CHostCommand * response = SendUiHostCommand(command);
	printf("response1 %u \n",response);
	if (!response)
		return false;
	printf("response2 %d \n",response->code);
	if(response->code!=GetMenuAddress_FunId)
	{
		delete response;
		return false;
	}
	char ch=CHostCommand::AckNak();
	data = response->GetData();//Getting Data.
	if(ch==ACK)//If Ack.
	{	
		*Langauage_Index=*data++;
		union 
		{
			bool i;
			char c;
		} v;
		v.c = *data++;
		*Start_Screen=v.i;
		delete response;
		return true;
	}
	else
	{
		delete response;
		return false;
	}
}


CHostCommand * CApplication::SendUiHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	CHostCommand *response;
	bool Done = false;
	/* keep orignal value of disableflag before changing it*/
	bool LatchDisableFlag = CChildView::DisableFlag;
	/* making this flag true disables mouse clicks so no other command can be sent while waiting for reply  
	   for previous ui command.*/
	CChildView::DisableFlag = true;   	                                                

	response =  com->SendUiHostCommand(request);
	if(response)
	{
		int ResponseCode=response->code;
		if(ResponseCode!=FunctionID)
		{
			/* here send this command again to get correct function number*/
			delete response;
			response = 0;			
		}

	}

	CChildView::DisableFlag = LatchDisableFlag;

	delete request;
	return response;

}

CHostCommand * CApplication::SendEnHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	printf("EnFunctionID=%d \n",FunctionID);
	CHostCommand *response =  com->SendEnHostCommand(request);
	return response;
}

CHostCommand * CApplication::SendPollingHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
//	printf("FunctionID=%d \n",FunctionID);
	CHostCommand *response =  com->SendPollingHostCommand(request);

	if(response)
	{
		int ResponseCode=response->code;
		if(ResponseCode!=FunctionID)
		{	/* here send this command again to get correct function number*/
			delete response;
			return 0;
		}
		else
			return response;
	}
	return response;

}

void CApplication::SendWeldData(unsigned char *&data,int length)
{	
	for (int i = 0; i <=ether->clients.GetUpperBound();i++)
	{
		if(ether->clients.GetAt(i)!=NULL)
			send(ether->clients.GetAt(i)->fd, (char* )data, length, 0);
	}

}

CHostCommand * CApplication::SendUiSerialHostCommand(CHostCommand *request)
{
	int FunctionID= request->code;
	CHostCommand *response = new CHostCommand(false);
	if(com->SendSerialRequest(request))
	{
		//if serial write is completed wait for response;    
		if(response && (com->ReadSerialResponse(response)))
		{
			int ResponseCode=response->code;
			if(ResponseCode!=FunctionID)
			{
				/* here send this command again to get correct function number*/
				delete response;
				return 0;
			}
			else
				return response;
		}
	}
	if(response)
		delete response;
	return 0;
}
