/*
 * DIComm2000Xc.cpp
 *
 *  Created on: Mar 16, 2020
 *      Author: rvite
 */
#include"DIComm2000Xc.h"
//#include "DIButtonsUI.h"
#include "CyGOS.h"
#include "Ethernet.h"
#include "time.h"

BOOLEAN DIComm2000Xc::WeldTriggered;
BOOLEAN bFlag= FALSE;
SINT8 MachType[DIProtocol::STRING32_SIZE]= "2000Xc";
SINT8 DateTimeFormated[DIProtocol::STRING32_SIZE]= "YYYY.MM.DD hh:mm:ss";
DIProtocol::RECORD_INFO RecordList[RECORD_NUM][RECORD_SIZE]=
{	{	{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "UserId", (SINT8 *)&FinalResults.UserId},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "ActAssyN", (SINT8 *)&FinalResults.ActAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "PSAssyN", (SINT8 *)&FinalResults.PSAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "StackAssyN", (SINT8 *)&FinalResults.StackAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING13_SIZE, "ActSerialN", (SINT8 *)&FinalResults.ActSerialNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING13_SIZE, "PsSerialN", (SINT8 *)&FinalResults.PsSerialNum},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "PS Watts", (SINT8 *)&CurrentSetup.PSWatt},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "PS Freq", (SINT8 *)&CurrentSetup.PSFreq},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING32_SIZE, "PS Machine", (SINT8 *)MachType}, //&CurrentSetup.MachType},
		{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "CycleCount", (SINT8 *)&FinalResults.CycleCount},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING32_SIZE, "Date&Time", (SINT8 *)&DateTimeFormated[0]},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "WeldTime", (SINT8 *)&FinalResults.ActualWeldTime},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "TotalEnerg", (SINT8 *)&FinalResults.TotalEnergy},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "WeldAbs", (SINT8 *)&FinalResults.ActualWeldAbs},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "TotalAbs", (SINT8 *)&FinalResults.ActualTotalAbs},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "WeldColl", (SINT8 *)&FinalResults.ActualWeldCollapse},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "TotalColl", (SINT8 *)&FinalResults.ActualTotalCollapse},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "FreqStart", (SINT8 *)&FinalResults.ActualFreqStart},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "FreqChange", (SINT8 *)&FinalResults.FrequencyChange},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "FreqMin", (SINT8 *)&FinalResults.FrequencyMin},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "FreqMax", (SINT8 *)&FinalResults.FrequencyMax},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "DownSpeed", (SINT8 *)&FinalResults.ActualDownspeed},
		{DIProtocol::TYPE_USINT, DIProtocol::BYTE_SIZE, "Weldmode", (SINT8 *)&FinalResults.Weldmode},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "PeakPower", (SINT8 *)&FinalResults.PeakPower},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "WeldPress", (SINT8 *)&FinalResults.WeldPressure},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "WeldFEnd", (SINT8 *)&FinalResults.WeldForceEnd},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "HoldFEnd", (SINT8 *)&FinalResults.HoldForceEnd},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "TrigForce", (SINT8 *)&FinalResults.TrigForce},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "CycleTime", (SINT8 *)&FinalResults.TotalCycleTime},
	},
	{	{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "CycleCount", (SINT8 *)&FinalResults.CycleCount},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "UserId", (SINT8 *)&FinalResults.UserId},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "PresetNum", (SINT8 *)&FinalResults.PresetNum},
		{DIProtocol::TYPE_DINT, DIProtocol::DWORD_SIZE, "PresetRev", (SINT8 *)&FinalResults.PresetRev},
		{DIProtocol::TYPE_UINT, DIProtocol::WORD_SIZE, "PresetVal", (SINT8 *)&FinalResults.PresetValidated},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "ActAssyN", (SINT8 *)&FinalResults.ActAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "PSAssyN", (SINT8 *)&FinalResults.PSAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "StackAssyN", (SINT8 *)&FinalResults.StackAssemblyNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING13_SIZE, "ActSerialN", (SINT8 *)&FinalResults.ActSerialNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING13_SIZE, "PsSerialN", (SINT8 *)&FinalResults.PsSerialNum},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING25_SIZE, "UDIScan", (SINT8 *)&FinalResults.UDIScan},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "RejectBitR", (SINT8 *)&FinalResults.RejectBitResult},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "SuspctBitR", (SINT8 *)&FinalResults.SuspectBitResult},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "NoCycAlarm", (SINT8 *)&FinalResults.NoCycleAlarms},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "OverLAlarm", (SINT8 *)&FinalResults.OverloadAlarms},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "EFailAlarm", (SINT8 *)&FinalResults.EquipmentFailureAlarms},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "CyclMAlarm", (SINT8 *)&FinalResults.CycleModifiedAlarms},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "CalibAlarm", (SINT8 *)&FinalResults.CalibrateAlarms},
		{DIProtocol::TYPE_UDINT, DIProtocol::DWORD_SIZE, "Warnings", (SINT8 *)&FinalResults.Warnings},
		{DIProtocol::TYPE_STRING, DIProtocol::STRING12_SIZE, "PresetName", (SINT8 *)&FinalResults.PresetName},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	},
	{	{DIProtocol::TYPE_NONE, DIProtocol::NULL_SIZE, "", NULL},
	}
};


/*
 * Constructor Initializes the DIComm2000Xc Class attributes
 */
DIComm2000Xc::DIComm2000Xc(SINT32 InterfaceID)
{
	int	Record, Var;
	SINT16 Status;
	BOOLEAN bFail= FALSE;
	Interface= InterfaceID;

	WriteKeepAliveBuffer= new SINT8[PREAMBLE_SIZE+HEADER_SIZE];
	ReadKeepAliveBuffer= new SINT8[PREAMBLE_SIZE+HEADER_SIZE];
	WriteConfigBuffer= new SINT8[PREAMBLE_SIZE+HEADER_SIZE+CONFIG_SIZE*RECORD_SIZE];
	WriteDataBuffer= new SINT8[PREAMBLE_SIZE+HEADER_SIZE+CONFIG_SIZE*RECORD_SIZE];

	ProtocolPtr= new DIProtocol();

	for (Record= 0; Record < RECORD_NUM; Record++)
		for (Var= 0; Var < RECORD_SIZE; Var++)
		{	Status= ProtocolPtr->InitProtocol(RecordList[Record][Var].Type, RecordList[Record][Var].Size, RecordList[Record][Var].Tag, RecordList[Record][Var].ValueAddress, Record, Var);
			if (Status == -1)
				bFail = TRUE;
		}
	ProtocolPtr->GetAliveFrame(WriteKeepAliveBuffer);

	return;
}


/*
 * Destructor
 */
DIComm2000Xc::~DIComm2000Xc()
{
	delete ReadKeepAliveBuffer;
	delete WriteKeepAliveBuffer;
	delete WriteConfigBuffer;
	delete WriteDataBuffer;

	delete ProtocolPtr;

	return;
}


void DIComm2000Xc::DelayMs(int TimeMs)
{
	CyGOS::DelayMs(TimeMs);
	return;
}

void DIComm2000Xc::SetTrigger(BOOLEAN bValue)
{
	WeldTriggered= bValue;
	return;
}

BOOLEAN DIComm2000Xc::GetTrigger(void)
{
	return WeldTriggered;
}

void DIComm2000Xc::FormatDateTime(SINT8 *Formated, t_date date, t_time time)
{
	sprintf(Formated, "20%d.%d.%d.%d:%d:%d", date.year, date.month, date.day, time.hour, time.minute, time.second);
	return;
}


/***********************************************************************
 * IsNetworkReady
 *
 * Purpose: Check the following
 * DI Mode is enabled,
 * Network is configured,
 * IP is in range,
 * Interface is pingeable
 *
 * Returns
 * 0: Network is Ready
 *
 */
SINT16 DIComm2000Xc::IsNetworkReady()
{	SINT16 ReturnVal;
	static Ethernet *Network= CyGOS::GetNetworkInterface(Interface);
	ip_addr IPAddress= Network->ipaddr;

	BOOLEAN IsSet= IPAddress.addr != 0,
			IsUp= Network->up,
			InAddress=	(IPAddress.addr >= DI_CLIENT_IP_MIN) && (IPAddress.addr < DI_CLIENT_IP_MAX);

	if (IsSet && IsUp) //
	{	if (InAddress == TRUE) // All is set
		{	Port= DI_SOCKET_PORT + IPAddress.addr - DI_CLIENT_IP_MIN; // Set Port
			ReturnVal = 0;
		}
		else
		{	ReturnVal = -2; // IP Address Error
		}
	}
	else
		ReturnVal = -1; // Wait

	return (ReturnVal);
}

/***********************************************************************/
void DIComm2000Xc::DISetAlarm(void)
{
	// Pending to set Alarm IP Error
}

/***********************************************************************/
void DIComm2000Xc::DISetEnable(BOOLEAN EnableStatus)
{
	EthernetOptions.Gateway = EnableStatus;// Disable DI Option
}

/***********************************************************************
 * IsChekedToSend
 *
 * Checks if the record is marked to be sent in UI
 *
 */
BOOLEAN DIComm2000Xc::IsChekedToSend(SINT32 Record, BOOLEAN IsPowerUp)
{
	switch (Record)
	{	case 0:
			return RecordOptions.SysConfig && IsPowerUp;
			break;
		case 1:
			return RecordOptions.WeldRes1 && !IsPowerUp;
			break;
		case 2:
			return RecordOptions.WeldRes2 && !IsPowerUp;
			break;
		case 3:
			return RecordOptions.Preset1 && !IsPowerUp;
			break;
		case 4:
			return RecordOptions.Preset2 && !IsPowerUp;
			break;
		default:
			return FALSE;
	}
}

/***********************************************************************
 *
 */
BOOLEAN DIComm2000Xc::IsDIEnabled(void)
{
	return EthernetOptions.Gateway;
}


/*
Ethernet *DIComm2000Xc::GetNetwork(SINT32 InterfaceID)
{
	return CyGOS::GetNetworkInterface(InterfaceID);
}

*/

/******************************************************************************/
/* OpenSocket
 * Creates and connects a socket.
 * param void
 * return void
 */
SINT16 DIComm2000Xc::OpenSocket(void)
{	UINT32 Val = 1;
	SINT16 Status, nTrays= 10;
	sockaddr_in ClientService;

	Socket= lwip_socket(AF_INET, SOCK_STREAM, 0);
//	RTOS::DelayMs(10);
	if (Socket != INVALID_SOCKET)
	{	lwip_ioctl(Socket, FIONBIO, &Val);
		ClientService.sin_family = AF_INET;
		ClientService.sin_port = htons(Port);	// Socket Port 65100 + Machine Number
		ClientService.sin_addr.s_addr= DI_SERVER_IP; //Server Address: MakeIP(150, 150, 150, 50);//
		for (Status= -1; (nTrays > 0) && (Status != 0); nTrays--)
		{	Status= lwip_connect(Socket, (sockaddr *) &ClientService, sizeof(ClientService));
			//RTOS::DelayMs(10);
		}
		if (Status == 0)
			return 0; // All is Ok
		else // Socket Not connected
		{	lwip_close(Socket);
			return -2;
		}
	}
	else // Socket Not Created
		return -1;// Something went wrong
}

/******************************************************************************/
/* DataInSocket
 * Checks if data is available in an open socket.
 * param void
 * return void
 */
SINT16 DIComm2000Xc::DataInSocket(void)
{	SINT16 ReadSize;

	lwip_ioctl(Socket, FIONREAD, &ReadSize);
	return ReadSize;
}

/******************************************************************************/
/* ReadSocket
 * Reads a packet to an open socket.
 * param void
 * return void
 */
SINT32 DIComm2000Xc::ReadSocket(SINT8 *ReadDest, UINT16 Size)
{	SINT32 BuffLen= 0, flags= MSG_DONTWAIT;

	BuffLen= lwip_recv(Socket, ReadDest, Size, flags);

	return BuffLen;
}

/******************************************************************************/
/* WriteSocket
 * Writes a packet to an open socket.
 * param void
 * return void
 */
SINT32 DIComm2000Xc::WriteSocket(SINT8 *WriteSource, UINT16 Size)
{	SINT32 BuffLen= 0, flags= 0;

	BuffLen= lwip_send(Socket, WriteSource, Size, flags);

	return BuffLen;
}

/******************************************************************************/
/* CloseSocket
 * Function first checks a valid socket and then close the socket.
 * param void
 * return void
 */
void DIComm2000Xc::CloseSocket(void)
{
	if (Socket != INVALID_SOCKET)
	{	lwip_close(Socket);
		Socket= INVALID_SOCKET;
		//Connection= INVALID_CONNECTION;
	}
}

/******************************************************************************/
/* CloseSocket
 * Function first checks a valid socket and then close the socket.
 * param void
 * return void
 */

#if 0
void DIComm2000Xc::PrintRecord(SINT16 RecordID)
{	char PrintStr[512], NumToStr[256], ByteToStr[4];
	int BytePos, VarID= 0;
	DIProtocol::RECORD_INFO Var= RecordList[RecordID][VarID];

	sprintf(PrintStr, "Record(%d): ", RecordID);
	CyGOS::EnableDebug();
	puts(PrintStr);
	CyGOS::DisableDebug();

	for (VarID= 0; (Var.Type != DIProtocol::TYPE_NONE) && (VarID < RECORD_SIZE); VarID++)
	{	Var= RecordList[RecordID][VarID];
		if (Var.Type != DIProtocol::TYPE_STRING)
		{	strcpy(NumToStr, "");
#if 0
			for (BytePos= 0; BytePos < Var.Size; BytePos++)
			{	sprintf(ByteToStr, "%02X ", *(&Var.Value[BytePos]));
				strcat(NumToStr, ByteToStr);
			}
#endif
		}
		else
			strcpy(NumToStr, (char *)Var.Value);
		sprintf(PrintStr, "Var(%d): Type(%d): Size(%d): Tag(%s): Value(%s)\n", VarID, Var.Type, Var.Size, Var.Tag, NumToStr);
		CyGOS::EnableDebug();
			puts(PrintStr);
		CyGOS::DisableDebug();
		DelayMs(100);
	}

}
#endif
