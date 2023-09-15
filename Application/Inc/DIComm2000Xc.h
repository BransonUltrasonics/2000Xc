/*
 * DIComm2000Xc.h
 *
 *  Created on: Mar 15, 2020
 *      Author: rvite
 */

#ifndef INC_DICOMM2000XC_H_
#define INC_DICOMM2000XC_H_
#include "portable.h"
#include "DIProtocol.h"
#include "DIProtocolInterface.h"
#include "DIButtonsUI.h"
#include "WeldManagerTask.h"	// To access WELD_DATA & CONFIGSETUP

#define DI_SOCKET_PORT 65100
#define DI_SERVER_IP MakeIP(150, 150, 150, 50)
#define DI_CLIENT_IP_MIN MakeIP(150, 150, 150, 10)
#define DI_CLIENT_IP_MAX MakeIP(150, 150, 150, 20)

extern BOOLEAN bFlag;
extern SINT8 MachType[DIProtocol::STRING32_SIZE];
extern SINT8 DateTimeFormated[DIProtocol::STRING32_SIZE];
extern DIProtocol::RECORD_INFO RecordList[RECORD_NUM][RECORD_SIZE];


/*
 * DIComm2000Xc Class, is a wrapper for DIComm Class
 */
class DIComm2000Xc
{
private:
	static BOOLEAN WeldTriggered;

public:
	SINT8	*WriteKeepAliveBuffer,
			*ReadKeepAliveBuffer,
			*WriteConfigBuffer,
			*WriteDataBuffer;

	DIProtocolInterface *ProtocolPtr;
	UINT16 Port;
	SINT16 Socket;
	SINT32 Interface;
	SINT8 PrintBuffer[500];

	DIComm2000Xc(SINT32);
	~DIComm2000Xc(void);

	BOOLEAN IsDIEnabled(void);
	SINT16 IsNetworkReady();
	BOOLEAN IsChekedToSend(SINT32 Record, BOOLEAN IsPowerUp);
	void DISetEnable(BOOLEAN);
	void DISetAlarm(void);
	SINT16 OpenSocket(void);
	SINT16 DataInSocket(void);
	SINT32 ReadSocket(SINT8 *ReadDest, UINT16 Size);
	SINT32 WriteSocket(SINT8 *WriteSource, UINT16 Size);
	void CloseSocket(void);

	void DelayMs(int);

	static void SetTrigger(BOOLEAN);
	BOOLEAN GetTrigger(void);
	static void FormatDateTime(SINT8 *, t_date, t_time);

// This functions will be overriden by the common DIC Communication handler
	virtual void Loop(void)= 0;
	virtual void Timer(void)= 0;
};



#endif /* INC_DICOMM2000XC_H_ */
