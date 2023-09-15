/*
 * DIProtocol.h
 *
 *  Created on: Jan 26, 2020
 *      Author: rvite
 */

#ifndef INC_DIPROTOCOL_H_
#define INC_DIPROTOCOL_H_
#include "DIProtocolInterface.h"
#include "portable.h"

// Definition for record data sizes
#define RECORD_SIZE 20
#define RECORD_NUM 10

// Definition of Packet Sizes
#define PREAMBLE_HEADER_SIZE  20
#define PREAMBLE_SIZE  12
#define HEADER_SIZE  8
#define RESERVED_SIZE  4
#define CONFIG_SIZE  24

#define CONFIG_TYPE_LEN 1
#define CONFIG_SIZE_LEN 2
#define CONFIG_TAG_LEN 11
#define CONFIG_RES_LEN 10

// Definition of
#define FILLZERO		0x00
#define FILLBLANK		0xFF
#define LSB 0
#define MSB 1

//#define STD_RECORD_SIZE 20
//#define NUM_OF_RECORDS  10

#define EXTENDED_RECORD_SIZE 21
#define MAX_RECORD_SIZE 20
#define LAST_RECORD_SIZE 11
#define MAX_NUM_OF_RECORDS  10

class DIProtocol : public DIProtocolInterface
{
private:

public:
// Definition for Different Load Types
enum LOAD_TYPE
	{	LOAD_TYPE_CONFIG= 1,
		LOAD_TYPE_DATA= 2,
		LOAD_TYPE_KEEP_ALIVE= 3
	};
// Definition for variable types
enum VAR_TYPE
	{	TYPE_NONE = -1,
		TYPE_BOOL = 0,
		TYPE_BYTE= 2,
		TYPE_WORD= 3,
		TYPE_DWORD= 4,
		TYPE_LWORD= 5,
		TYPE_SINT= 6,
		TYPE_INT= 7,
		TYPE_DINT= 8,
		TYPE_LINT= 9,
		TYPE_USINT= 10,
		TYPE_UINT= 11,
		TYPE_UDINT= 12,
		TYPE_ULINT= 13,
		TYPE_REAL= 14,
		TYPE_LREAL= 15,
		TYPE_STRING= 16,
		TYPE_LSTRING= 17,
		TYPE_ENUM= 25,
		TYPE_ARRAY= 26,
		TYPE_USERDEF= 28
	};

// Definition for variable sizes
enum VAR_SIZE
	{	NULL_SIZE = 0,
		BYTE_SIZE = 1,
		WORD_SIZE = 2,
		DWORD_SIZE = 4,
		QWORD_SIZE = 8,
		STRUCT8_SIZE= 8,
		STRING12_SIZE = 12,
		STRING13_SIZE = 13,
		STRING25_SIZE = 25,
		STRING32_SIZE = 32
	};

// Structure for describing record variables: Type, Size, Tag, ValueAddress.
struct RECORD_INFO
	{	SINT8 Type;
		SINT16 Size;
		SINT8 Tag[CONFIG_TAG_LEN];
		SINT8 *ValueAddress;
	};

	BOOLEAN IsEndian;

	RECORD_INFO RecordInfoPtr[RECORD_NUM][RECORD_SIZE];

	DIProtocol();
	~DIProtocol();

	BOOLEAN IsBigEndian(void);
	SINT16 GetAliveFrame(SINT8 *);
	SINT16 GetConfigFrame(SINT8 *, SINT16);
	SINT16 GetDataFrame(SINT8 *, SINT16);
	SINT16 InitProtocol(SINT8 , SINT16 , SINT8 [11], SINT8 *, SINT16 , SINT16);
private:
	void SetEndian(void);
	void bufset(SINT8 *, SINT8 , SINT16);
	void bufcpyrev(SINT8 *, SINT8 *, SINT16);
	void bufcpy(SINT8 *, SINT8 *, SINT16);
	void SetPreambleHeader(SINT8 *BufferPtr, LOAD_TYPE LoadType, SINT16 LoadSize, SINT16 RecordID);
};
#endif /* INC_DIPROTOCOL_H_ */
