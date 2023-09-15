/*
 * DIComm.h
 *
 *  Created on: Mar 14, 2020
 *      Author: rvite
 *  Definition of DI Communication Class
 */

#ifndef INC_DICOMM_H_
#define INC_DICOMM_H_
#define PREAMBLE_SIZE 12
#define HEADER_SIZE 8
#define CONFIG_SIZE 24
#define RECORD_SIZE 20
#define RECORD_NUM 10


#include "DIComm2000Xc.h"
#include "portable.h"

class DIComm : public DIComm2000Xc
{
private:
	enum DI_CONNECTION_STATUS
	{	Init,
		WaitToEnableDI,
		WaitingToEnableNetwork,
		OpenConnection,

		IsReadyToReceiveAlive,
		IsReadyToSendAlive,
		IsReadyToSendConfig,
		IsReadyToSendData,
		CheckServerStatus,

		SendingAlive,
		SendingConfig,
		SendingData,
		ReceivingAlive,

		ClosingConnection,
	};

	enum PACKET_CONNECTION_VALUES
	{	WaitForAlive = 0,
		ServerAlive,
		ServerTimedOut,

		AliveWaittingToStart,
		AliveReadyToSend,
		AliveWaittingToSend,

		//ConfigNotSent,
		//ConfigInProgress,
		//ConfigSent,

		//DataInProgress,
		//DataSent,

		Check,
		StartSending,
		SendingInProgress,
		EndSending,
	};

	struct PACKET_CONNECTION_STATUS
	{	PACKET_CONNECTION_VALUES Connection;
		SINT32 Counter;
	};


public:
	PACKET_CONNECTION_STATUS KeepAlive_Client_Status, KeepAlive_Server_Status, Config_Client_Status, Data_Client_Status;
	DI_CONNECTION_STATUS ClientStatus;

	DIComm *thisPtr;
	DIComm(SINT32);
	~DIComm();
	void SetUp(void);
	void CleanUp(void);
	void Loop(void);
	void Timer(void);
};
#endif /* INC_DICOMM_H_ */
