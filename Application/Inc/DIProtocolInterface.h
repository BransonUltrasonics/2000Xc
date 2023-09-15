/*
 * DIProtocolInterface.h
 *
 *  Created on: Mar 3, 2020
 *      Author: rvite
 */

#ifndef INC_DIPROTOCOLINTERFACE_H_
#define INC_DIPROTOCOLINTERFACE_H_
#include "portable.h"
#include <stdlib.h>

#define RECORD_SIZE 20
#define RECORD_NUM 10
#define CONFIG_TAG_LEN 11

class DIProtocolInterface
{
public:
	virtual BOOLEAN IsBigEndian(void)= 0;
	virtual SINT16 GetAliveFrame(SINT8 *)= 0;
	virtual SINT16 GetConfigFrame(SINT8 *, SINT16)= 0;
	virtual SINT16 GetDataFrame(SINT8 *, SINT16)= 0;
//	virtual SINT16 InitProtocol(int Type, int Size, char *Tag, char *Val, int Record, int Var)= 0;
	virtual SINT16 InitProtocol(SINT8 Type, SINT16 Size, SINT8 Tag[11], SINT8 *Value, SINT16 Record, SINT16 Var)= 0;
	DIProtocolInterface(void);
	~DIProtocolInterface(void);
};
#endif /* INC_DIPROTOCOLINTERFACE_H_ */

