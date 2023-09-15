/*
 * DIComm.cpp
 *
 *  Created on: Mar 14, 2020
 *      Author: rvite
 *  Implementation of DI Communication Class
 * this implementation may be used in all the welders, is hardware and platform independent
 */

#include "DIComm.h"
#include "string.h"
#include "DIPrint.h"


DIComm::DIComm(SINT32 InterfaceID) : DIComm2000Xc(InterfaceID)
{
		thisPtr= this;

		ClientStatus= Init;

		return;
}

DIComm::~DIComm(void)
{
	return;
}



void DIComm::Loop(void)
{
	static SINT16 BuffLen= 0, Waiting= 0;
	SINT16 BufferSize, Byte, NetReadyState, Status;
	UINT16 Record, Var, i;
	char CharToNum[10];
	BOOLEAN IsAliveReceived, IsAliveSent, IsReady, bFail= FALSE;
	static BOOLEAN PowerUpFlag;


	switch (ClientStatus)
		{
/*****************************************************************************************************/
// Sets Initial Parameters
/*****************************************************************************************************/
			case Init:
				KeepAlive_Client_Status.Connection= AliveReadyToSend;
				KeepAlive_Client_Status.Counter= 0;

				KeepAlive_Server_Status.Connection= ServerAlive;
				KeepAlive_Server_Status.Counter= 0;

				Config_Client_Status.Connection= StartSending;
				Config_Client_Status.Counter= 0;

				Data_Client_Status.Connection= StartSending;
				Data_Client_Status.Counter= 0;

				ClientStatus= WaitToEnableDI;	// Next State for Connection

				PowerUpFlag= TRUE;

				// Tests Packets
#if 0
				BufferSize= ProtocolPtr->GetAliveFrame(WriteKeepAliveBuffer);
				PrintBufferf(WriteKeepAliveBuffer, BufferSize);
				DelayMs(5);

				for (i= 0; i < RECORD_NUM; i++) // 3 record
				{	BufferSize= ProtocolPtr->GetConfigFrame(WriteConfigBuffer, i);
					PrintBufferf(WriteConfigBuffer, BufferSize);
					DelayMs(5);

					BufferSize= ProtocolPtr->GetDataFrame(WriteDataBuffer, i);
					PrintBufferf(WriteDataBuffer, BufferSize);
					DelayMs(5);
				}
#endif
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "\nINITIALIZING...\n");
#endif
				break;

/*****************************************************************************************************/
// Waits until user enables GateWay in UI
/*****************************************************************************************************/
			case WaitToEnableDI:
				IsReady= IsDIEnabled();
				if 	(IsReady == TRUE)
					ClientStatus= WaitingToEnableNetwork;
				else
				{	DelayMs(100);
					ClientStatus= WaitToEnableDI;
				}

#ifdef DEBUGING_MODE
	if (IsReady)
		sprintf(PrintBuffer, "\nDI ENABLE STATE:  ENABLED\n");
	else
		sprintf(PrintBuffer, "\rWAITING FOR DI TO ENABLE(%03d)", ++Waiting);
#endif
				break;

/*****************************************************************************************************/
// Waits until Network is Configured
/*****************************************************************************************************/
			case WaitingToEnableNetwork:
				NetReadyState= IsNetworkReady();
				switch (NetReadyState)
				{	case 0://Netwotk is Ready
						ClientStatus= OpenConnection;	// Network enabled
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "\nNETWORK READY\n");
#endif
						break;
					case -1:// Network Not Ready
					default:
						ClientStatus= WaitingToEnableNetwork;	// Wait for setting Network
//						DelayMs(100);	// Waits until Network is configured and enabled
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "\rWAITING FOR NETWORK(%03d)", ++Waiting);
	if (Waiting >= 1000)
		Waiting= 0;
#endif
						break;
					case -2:// IP Address Error
						DISetEnable(FALSE);

						// Set Alarm
						DISetAlarm();
						ClientStatus= WaitToEnableDI; //Wait until DI Option is Enable
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "\nBAD IP ADDRESS. SET IT IN WINDOWS AND POWER CYCLE\nMACHINE SHOULD BE IN SUBNET 150.150.150.XX\nWITH XX IN RANGE 20-29\n");
#endif
						break;
				}
				break;

/*****************************************************************************************************/
// Creates a socket
/*****************************************************************************************************/
			case OpenConnection:
				int Status;
				Status= OpenSocket();
				if (Status == 0)// Socket created and conneceted
				{	ClientStatus= CheckServerStatus;
					KeepAlive_Server_Status.Connection= WaitForAlive;
					KeepAlive_Server_Status.Counter= 0;
				}
				else
				{		ClientStatus= Init;
				}
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "CONNECTION STATE:(%s) CODE:(%d)\n", Status? "FAIL" : "SUCCESS", Status);
#endif
				break;

/*****************************************************************************************************/
// Checks if server is alive
// define when to receive if waiting
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
		case CheckServerStatus:
			switch (KeepAlive_Server_Status.Connection)
			{	case WaitForAlive: //Initial Connection
				case ServerAlive: // Checks if a keep alive packet is ready to be received
				default:
					ClientStatus= IsReadyToReceiveAlive;	// Next State for Connection
#ifdef DEBUGING_MODE
	//strcpy(PrintBuffer, "Waiting for:");
	strcpy(PrintBuffer, "");
#endif
					break;
				case ServerTimedOut: //Reset Connections
					ClientStatus= ClosingConnection;	// Next State for Connection
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "TIMEOUT KEEP ALIVE NOT RECEIVED FROM SERVER - CONNECTION RESET\n");
#endif
					break;
			}
			break;

/*****************************************************************************************************/
// Receives Keep Alive packet
/*****************************************************************************************************/
			case IsReadyToReceiveAlive:
				BuffLen= DataInSocket();
				if (BuffLen > 0) // Data available in socket
				{	ClientStatus= ReceivingAlive;	// Go to Receive Packet
#ifdef DEBUGING_MODE
//	sprintf(PrintBuffer, "READY TO RECEIVE (%d)BYTES: ", BuffLen);
	strcpy(PrintBuffer, "");
#endif
				}
				else
				{	ClientStatus= IsReadyToSendAlive;	// Next State for Connection
#ifdef DEBUGING_MODE
//	sprintf(PrintBuffer, "Receive KA(%d) / ", KeepAlive_Server_Status.Counter);
	strcpy(PrintBuffer, "");
#endif
				}
				break;
/*****************************************************************************************************/
// Receives Keep Alive packet
/*****************************************************************************************************/
			case ReceivingAlive:
				if 	(IsDIEnabled() == FALSE)
				{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, " RECEPTION CANCELLED - DI DISABLED - CONNECTION RESET\n");
#endif
				}
				else
				{	BuffLen= ReadSocket(ReadKeepAliveBuffer, PREAMBLE_HEADER_SIZE);
					IsAliveReceived= (memcmp(ReadKeepAliveBuffer, WriteKeepAliveBuffer, PREAMBLE_HEADER_SIZE) == 0);
					if (IsAliveReceived == TRUE)
					{	ClientStatus= CheckServerStatus;	// Next State for Connection
						KeepAlive_Server_Status.Counter= 0;
						KeepAlive_Server_Status.Connection= ServerAlive;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "KA <- (%d)B\n", BuffLen);
#ifdef SHOW_DATA
	int i;
//	strcat(PrintBuffer, "\n");
	for (i= 0; i< BuffLen; i++)
	{	Byte= ReadKeepAliveBuffer[i] & 0xFF;
		sprintf(CharToNum, "%u ", Byte);
		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");
#endif
#endif
					}
					else
					{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "NOT KEEP ALIVE - RESET CONNECTION\n");
#endif
					}
				}
				break;

/*****************************************************************************************************/
// If Timed Out Writes Keep Alive message to the Socket
/*****************************************************************************************************/
		case IsReadyToSendAlive:
			// call method to know if ready to send KeepAlive
			// GetEnableToSend(Alive);
			switch (KeepAlive_Client_Status.Connection)
			{	case AliveReadyToSend: // Checks if is ready to send keep alive packet
					ClientStatus= SendingAlive;
#ifdef DEBUGING_MODE
//	sprintf(PrintBuffer, "READY TO SEND KEEP ALIVE (%d): ", KeepAlive_Client_Status.Counter);
	strcpy(PrintBuffer, "");
#endif
					break;
				case AliveWaittingToSend:
				default:
					ClientStatus= IsReadyToSendConfig;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "");
//strcpy(PrintBuffer, "CHECK IF READY TO SEND CONFIG \n");
#endif
					break;
			}

			break;

/*****************************************************************************************************/
// Sends Keep Alive packet
/*****************************************************************************************************/
			case SendingAlive:
				if 	(IsDIEnabled() == FALSE)
				{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "KEEP ALIVE TRANSMITION CANCELLED - DI DISABLED - RESET CONNECTION\n");
#endif
				}
				else
				{	BuffLen= WriteSocket((SINT8 *)WriteKeepAliveBuffer, PREAMBLE_HEADER_SIZE);
					IsAliveSent= (BuffLen == PREAMBLE_HEADER_SIZE);
					if (IsAliveSent == TRUE)
					{	ClientStatus= CheckServerStatus;
						KeepAlive_Client_Status.Counter= 0;
						KeepAlive_Client_Status.Connection= AliveWaittingToSend;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "KA -> (%d)B\n", BuffLen);
#ifdef SHOW_DATA
	int i;
	for (i= 0; i< BuffLen; i++)
	{	Byte= WriteKeepAliveBuffer[i] & 0xFF;
		sprintf(CharToNum, "%u ", Byte);
		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");
#endif
#endif
					}
					else
					{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "FAILED TO SEND KEEP ALIVE - RESET CONNECTION\n");
#endif
					}
				}
				break;

/*****************************************************************************************************/
// Checks if is ready to send configuration packet
/*****************************************************************************************************/
		case IsReadyToSendConfig:
			// call method to know if ready to send Config
			// GetEnableToSend(Config);
			switch (Config_Client_Status.Connection)
			{	case StartSending:
					ClientStatus= SendingConfig;
					Config_Client_Status.Counter= 0;
					Config_Client_Status.Connection= SendingInProgress;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "C -> : R(%ld) ", Config_Client_Status.Counter+1);
#endif
					break;
				case SendingInProgress:
					Config_Client_Status.Counter++;
					if (Config_Client_Status.Counter < MAX_NUM_OF_RECORDS)
					{	ClientStatus= SendingConfig;
						Config_Client_Status.Connection = SendingInProgress;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "C >>: R(%ld) ", Config_Client_Status.Counter+1);
#endif
					}
					else
					{	ClientStatus= IsReadyToSendData;
						Config_Client_Status.Counter= MAX_NUM_OF_RECORDS;
						Config_Client_Status.Connection = EndSending;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "C >|: (%ld) RECORDS SENT\n", Config_Client_Status.Counter);
#endif
					}
					break;
				case EndSending:
				default:
					ClientStatus= IsReadyToSendData;
#ifdef DEBUGING_MODE
//	strcpy(PrintBuffer, "C <SKIP> \n ");
	strcpy(PrintBuffer, "");
#endif
					break;
			}
			break;

/*****************************************************************************************************/
// Sends Configuration packet
/*****************************************************************************************************/
		case SendingConfig:
			if 	(IsDIEnabled() == FALSE)
			{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "CONFIG TRANSMITION CANCELLED - DI DISABLED - CONNECTION RESET\n");
#endif
			}
			else
			{	Record= Config_Client_Status.Counter; // Load Config buffer form Record#
				BufferSize= ProtocolPtr->GetConfigFrame(WriteConfigBuffer, Record);
				BuffLen= WriteSocket(WriteConfigBuffer, BufferSize);
				if (BuffLen != BufferSize)
				{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "FAILED TO SEND CONFIG - CONNECTION RESET\n");
#endif
				}
				else
				{	ClientStatus= CheckServerStatus;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "CONFIG SENT: (%d) BYTES, RECORD(%d)\n", BuffLen, Record+1);
#ifdef SHOW_DATA
	for (i= 0; i< 20; i++) // Preamble + Header
	{	Byte= *(UINT8 *)(WriteConfigBuffer+i) & 0xFF;
		sprintf(CharToNum, "%u ", Byte);
		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");
if (BuffLen > 20)
{	int	Var= 0,
		Start= 20+ 24*Var;
//	sprintf(CharToNum, "Var:%d - %s", Var+1, CharToNum);
	for (i= Start; i< Start + 24; i++) //BuffLen
	{	Byte= *(UINT8 *)(WriteConfigBuffer+i) & 0xFF;
		sprintf(CharToNum, ischar(Byte)?"'%c' " : "%u ", Byte);
		strcat(PrintBuffer, CharToNum);
	}
}
	strcat(PrintBuffer, "\n");
#endif
#endif
				}
			}
			break;
/*****************************************************************************************************/
// Checks if is ready to send Data packet
/*****************************************************************************************************/
		case IsReadyToSendData:
			// Check if trigger for send Data*******************************************************?????
			switch(Data_Client_Status.Connection)
			{	case Check: // Start sending Data
					ClientStatus= CheckServerStatus;
					if (GetTrigger() == TRUE) // Send Data at power up or weld cycle
					{
						Data_Client_Status.Connection= StartSending;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "TRIGGER WELD CYCLE\n");
#endif
					}
					else
					{
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "Trigger...\r");
	strcpy(PrintBuffer, "");
#endif
					}
					break;
				case StartSending: // Starts sending Data records
				{	ClientStatus= SendingData;
					Data_Client_Status.Counter= 0;
					Data_Client_Status.Connection= SendingInProgress;
#ifdef DEBUGING_MODE
//sprintf(PrintBuffer, "DATA SEND STARTED: RECORD(%ld) DATE:TIME(%s)", Data_Client_Status.Counter+1, DateTimeFormated);
	sprintf(PrintBuffer, "DATA SEND STARTED: RECORD(%ld)", Data_Client_Status.Counter+1);
#endif
				}
					break;
				case SendingInProgress: // Continues sending pending Data records
					Data_Client_Status.Counter++;
					if (Data_Client_Status.Counter < MAX_NUM_OF_RECORDS)
					{	ClientStatus= SendingData;
						Data_Client_Status.Connection = SendingInProgress;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "DATA SEND INPROGRESS: RECORD(%ld) ", Data_Client_Status.Counter+1);
#endif
					}
					else
					{	ClientStatus= IsReadyToSendData;
//						Data_Client_Status.Counter= 0;
						Data_Client_Status.Connection = EndSending;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "DATA SEND FINISHED: (%ld) RECORDS SENT\n", Data_Client_Status.Counter);
#endif
					}
					break;
				case EndSending: // Wait until Data Trigger is set
					SetTrigger(FALSE);

					ClientStatus= IsReadyToSendData;
					Data_Client_Status.Connection= Check;
					PowerUpFlag= FALSE;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "DATA SEND FINISHED: (%ld) RECORDS SENT\n", Data_Client_Status.Counter);
#endif
					break;
				default:
					break;
			}
			break;

/*****************************************************************************************************/
// Sends Data packet
/*****************************************************************************************************/
		case SendingData:
			// ToDo: Check if Data Record is marked to be sent
			if 	(IsDIEnabled() == FALSE)
			{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "DATA TRANSMITION CANCELLED - DI DISABLED - CONNECTION RESET\n");
#endif
			}
			else
			{	Record= Data_Client_Status.Counter;
				if (IsChekedToSend(Record, PowerUpFlag) == TRUE)
				{	BufferSize= ProtocolPtr->GetDataFrame(WriteDataBuffer, Record);
					BuffLen= WriteSocket(WriteDataBuffer, BufferSize);

					if (BuffLen != BufferSize)
					{	ClientStatus= ClosingConnection;
#ifdef DEBUGING_MODE
	strcpy(PrintBuffer, "FAILED TO SEND DATA - CONNECTION RESET\n");
#endif
					}
					else
						ClientStatus= CheckServerStatus;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "DATA SENT: (%d) BYTES, RECORD(%d)\n", BuffLen, Record+1);
#ifdef SHOW_DATA
	for (i= 0; i< 20; i++) //BuffLen
	{	Byte= *(UINT8 *)(&WriteDataBuffer[i]) & 0xFF;
		sprintf(CharToNum, "%u ", Byte);
		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");

	for (i= 20; i< BufferSize; i++) //BuffLen
	{	Byte= *(UINT8 *)(WriteDataBuffer+i) & 0xFF;
		sprintf(CharToNum, ischar(Byte)?"'%c' " : "%u ", Byte);
//		strcat(PrintBuffer, CharToNum);
	}
	strcat(PrintBuffer, "\n");
#endif
#endif
				}
				else
				{	ClientStatus= CheckServerStatus;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "DATA SKIPED: Record(%d)\n", Record+1);
#endif
				}
			}
			break;

/*****************************************************************************************************/
// Closes socket and tries a new connection
/*****************************************************************************************************/
		case ClosingConnection:
			CloseSocket();
			ClientStatus= Init;
#ifdef DEBUGING_MODE
	sprintf(PrintBuffer, "CLOSING CONNECTION: \n");
#endif
			break;

/*****************************************************************************************************/
// Default case if something was omitted
/*****************************************************************************************************/
		default:
#ifdef DEBUGING_MODE
//	sprintf(PrintBuffer, "Default State\n");
#endif
			break;
		}// switch (ClientStatus)
}



#define TIME_KEEP_ALIVE_SEND (500*1000)
#define TIME_KEEP_ALIVE_RECEIVE (500*1000)
#define TIME_KEEP_ALIVE_TOLERANCE (500*1000)

void DIComm::Timer(void)
{
	// Checks if ready to send KeepAlive again
		KeepAlive_Client_Status.Counter+= Task::usecPerTick;
		if ((KeepAlive_Client_Status.Connection == AliveWaittingToSend) && (KeepAlive_Client_Status.Counter >= TIME_KEEP_ALIVE_SEND))
		{
			KeepAlive_Client_Status.Connection= AliveReadyToSend;
		}

	// Checks if timedOut to receive KeepAlive again
	#if 1
		switch(KeepAlive_Server_Status.Connection)
		{	case WaitForAlive: // Do not do anything, waits for receiving the first KeepAlive from server
			break;
			case ServerAlive:
				KeepAlive_Server_Status.Counter+= Task::usecPerTick;
				if (KeepAlive_Server_Status.Counter >= TIME_KEEP_ALIVE_RECEIVE + TIME_KEEP_ALIVE_TOLERANCE)
				{	KeepAlive_Server_Status.Connection= ServerTimedOut;
				}
			break;
			case ServerTimedOut: // Do not do anything, connection will be closed
			default:
				break;
		}
	#endif
}
